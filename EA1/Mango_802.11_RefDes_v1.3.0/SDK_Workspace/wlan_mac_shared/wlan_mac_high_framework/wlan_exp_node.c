/** @file wlan_exp_node.c
 *  @brief Experiment Framework
 *
 *  This contains the code for WARPnet Experimental Framework.
 *
 *  @copyright Copyright 2013-2015, Mango Communications. All rights reserved.
 *          Distributed under the Mango Communications Reference Design License
 *				See LICENSE.txt included in the design archive or
 *				at http://mangocomm.com/802.11/license
 *
 *  @author Chris Hunter (chunter [at] mangocomm.com)
 *  @author Patrick Murphy (murphpo [at] mangocomm.com)
 *  @author Erik Welsh (welsh [at] mangocomm.com)
 */
/***************************** Include Files *********************************/

#include "wlan_exp_common.h"
#include "wlan_exp_node.h"
#include "wlan_exp_transport.h"

#ifdef USE_WARPNET_WLAN_EXP

#include <xparameters.h>
#include <xil_io.h>
#include <xio.h>
#include <stdlib.h>

#ifdef XPAR_XSYSMON_NUM_INSTANCES
#include <xsysmon_hw.h>
#endif

// WARP Includes
#include "w3_userio.h"

// WLAN includes
#include "wlan_mac_event_log.h"
#include "wlan_mac_entries.h"
#include "wlan_mac_ltg.h"
#include "wlan_mac_schedule.h"
#include "wlan_mac_bss_info.h"



/*************************** Constant Definitions ****************************/

// #define _DEBUG_

#ifdef XPAR_XSYSMON_NUM_INSTANCES
#define SYSMON_BASEADDR		                               XPAR_SYSMON_0_BASEADDR
#endif


/*********************** Global Variable Definitions *************************/

extern int                 sock_unicast; // UDP socket for unicast traffic to / from the board
extern struct sockaddr_in  addr_unicast;

extern int                 sock_bcast; // UDP socket for broadcast traffic to the board
extern struct sockaddr_in  addr_bcast;

extern int                 sock_async; // UDP socket for async transmissions from the board
extern struct sockaddr_in  addr_async;


// Declared in wlan_mac_high.c
extern u8                  promiscuous_stats_enabled;
extern u8                  rx_ant_mode_tracker;


// Declared in each of the AP / STA / IBSS
extern bss_info*		   my_bss_info;

extern tx_params           default_unicast_mgmt_tx_params;
extern tx_params           default_unicast_data_tx_params;
extern tx_params           default_multicast_mgmt_tx_params;
extern tx_params           default_multicast_data_tx_params;


/*************************** Functions Prototypes ****************************/

void node_init_system_monitor(void);
int  node_init_parameters( u32 *info );
int  node_processCmd(const wn_cmdHdr* cmdHdr, void* cmdArgs, wn_respHdr* respHdr, void* respArgs, void* pktSrc, u16 dest_id, u32 eth_dev_num);

void node_ltg_cleanup(u32 id, void* callback_arg);

void create_wn_cmd_log_entry(wn_cmdHdr* cmdHdr, void * cmdArgs, u16 src_id);

int  node_process_tx_power(u32 cmd, u32 aid, int tx_power);
u8   node_process_tx_rate(u32 cmd, u32 aid, u8 tx_rate);
u8   node_process_tx_ant_mode(u32 cmd, u32 aid, u8 ant_mode);

void print_mac_address(u8 * mac_address, u8 level);


#ifdef _DEBUG_
void print_wn_node_info( wn_node_info * info );
void print_wn_parameters( wn_tag_parameter *param, int num_params );
#endif


// WARPNet buffer functions
u32 node_process_buffer_cmds(const wn_cmdHdr* cmdHdr, u32 * cmdArgs32,
                             wn_respHdr * respHdr, u32 * respArgs32, void* pktSrc, u32 eth_dev_num, u32 max_words,
	                         char * type, char * description, dl_list * source_list, u32 dest_size,
	                         u32 (*find_id)(u8 *),
	                         dl_entry * (*find_source_entry)(u8 *),
                             void (*copy_source_to_dest)(void *, void *, u64),
                             void (*zero_dest)(void *));

dl_entry * find_station_info_entry(u8 * mac_addr);
void       zero_station_info_entry(void * dest);
void       copy_station_info_to_dest_entry(void * source, void * dest, u64 time);

dl_entry * find_statistics_txrx_entry(u8 * mac_addr);
void       zero_txrx_stats_entry(void * dest);
void       copy_statistics_txrx_to_dest_entry(void * source, void * dest, u64 time);

void       zero_bss_info_entry(void * dest);
void       copy_bss_info_to_dest_entry(void * source, void * dest, u64 time);

u32        wlan_exp_get_id_in_associated_stations(u8 * mac_addr);
u32        wlan_exp_get_id_in_statistics(u8 * mac_addr);
u32        wlan_exp_get_id_in_bss_info(u8 * bssid);

// Null callback function declarations
int        wlan_exp_null_callback();
int        wlan_exp_null_init_callback(void* param);
int        wlan_exp_null_process_callback(unsigned int cmdID, void* param);



/*************************** Variable Definitions ****************************/

wn_node_info                 node_info;
static wn_tag_parameter      node_parameters[NODE_MAX_PARAMETER];

static wn_function_ptr_t     wlan_exp_init_callback                     = (wn_function_ptr_t)wlan_exp_null_init_callback;
static wn_function_ptr_t     wlan_exp_process_callback                  = (wn_function_ptr_t)wlan_exp_null_process_callback;
static wn_function_ptr_t     wlan_exp_reset_station_statistics_callback = (wn_function_ptr_t)wlan_exp_null_callback;
       wn_function_ptr_t     wlan_exp_purge_all_data_tx_queue_callback  = (wn_function_ptr_t)wlan_exp_null_callback;
       wn_function_ptr_t     wlan_exp_reset_all_associations_callback   = (wn_function_ptr_t)wlan_exp_null_callback;
       wn_function_ptr_t     wlan_exp_reset_bss_info_callback           = (wn_function_ptr_t)wlan_exp_null_callback;
static wn_function_ptr_t     wlan_exp_adjust_timebase_callback          = (wn_function_ptr_t)wlan_exp_null_callback;
       wn_function_ptr_t     wlan_exp_tx_cmd_add_association_callback   = (wn_function_ptr_t)wlan_exp_null_callback;


u32                          async_pkt_enable;
u32                          async_eth_dev_num;
pktSrcInfo                   async_pkt_dest;
wn_transport_header          async_pkt_hdr;

static u32                   wlan_exp_enable_logging = 0;



/******************************** Functions **********************************/


/*****************************************************************************/
/**
* Node Null Callbacks
*
* This function is part of the callback system for processing node commands.
* If there are no additional node commands, then this will return appropriate values.
*
* To processes additional node commands, please set the node_process_callback
*
* @param    void * param  - Parameters for the callback
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
int wlan_exp_null_callback(void* param){
	wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "WLAN Exp NULL callback\n");
	return SUCCESS;
};


int wlan_exp_null_init_callback(void* param){
	wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "WLAN Exp NULL init callback\n");
	return SUCCESS;
};


int wlan_exp_null_process_callback(unsigned int cmdID, void* param){
	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown node command: %d\n", cmdID);
	return NO_RESP_SENT;
};


/*****************************************************************************/
/**
* Node Transport Processing
*
* This function is part of the callback system for the Ethernet transport.
* Based on the Command Group field in the header, it will call the appropriate
* processing function.
*
* @param    Message to Node   - WARPNet Host Message to the node
*           Message from Node - WARPNet Host Message from the node
*           Packet Source          - Ethernet Packet Source
*           Ethernet Device Number - Indicates which Ethernet device packet came from
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void node_rxFromTransport(wn_host_message* toNode, wn_host_message* fromNode,
		                  void* pktSrc, u16 src_id, u16 dest_id, u32 eth_dev_num){
	unsigned char cmd_grp;

	unsigned int respSent = RESP_SENT;

#ifdef _DEBUG_
	xil_printf("In node_rxFromTransport() \n");
#endif

	//Helper struct pointers to interpret the received packet contents
	wn_cmdHdr* cmdHdr;
	void * cmdArgs;

	//Helper struct pointers to form a response packet
	wn_respHdr* respHdr;
	void * respArgs;

	cmdHdr  = (wn_cmdHdr*)(toNode->payload);
	cmdArgs = (toNode->payload) + sizeof(wn_cmdHdr);

	//Endian swap the command header (this is the first place we know what/where it is)
	cmdHdr->cmd     = Xil_Ntohl(cmdHdr->cmd);
	cmdHdr->length  = Xil_Ntohs(cmdHdr->length);
	cmdHdr->numArgs = Xil_Ntohs(cmdHdr->numArgs);

	// Create a log entry if logging is enabled
	if (wlan_exp_enable_logging == 1) {
		create_wn_cmd_log_entry(cmdHdr, cmdArgs, src_id);
	}

	//Outgoing response header must be endian swapped as it's filled in
	respHdr  = (wn_respHdr*)(fromNode->payload);
	respArgs = (fromNode->payload) + sizeof(wn_cmdHdr);

	cmd_grp = WN_CMD_TO_GRP(cmdHdr->cmd);
	switch(cmd_grp){
		case WARPNET_GRP:
		case NODE_GRP:
			respSent = node_processCmd(cmdHdr,cmdArgs,respHdr,respArgs,pktSrc,dest_id,eth_dev_num);
		break;
		case TRANS_GRP:
			respSent = transport_processCmd(cmdHdr,cmdArgs,respHdr,respArgs,pktSrc,eth_dev_num);
		break;
		default:
			wlan_exp_printf(WLAN_EXP_PRINT_WARNING, print_type_transport, "Unknown command group\n");
		break;
	}

	if(respSent == NO_RESP_SENT)	fromNode->length += (respHdr->length + sizeof(wn_cmdHdr));


	//Endian swap the response header before returning
	// Do it here so the transport sender doesn't have to understand any payload contents
	respHdr->cmd     = Xil_Ntohl(respHdr->cmd);
	respHdr->length  = Xil_Ntohs(respHdr->length);
	respHdr->numArgs = Xil_Ntohs(respHdr->numArgs);

	return;
}



/*****************************************************************************/
/**
* Node Send Early Response
*
* Allows a node to send a response back to the host before the command has
* finished being processed.  This is to minimize the latency between commands
* since the node is able to finish processing the command during the time
* it takes to communicate to the host and receive another command.
*
* @param    Response Header        - WARPNet Response Header
*           Packet Source          - Ethernet Packet Source
*           Ethernet Device Number - Indicates which Ethernet device packet came from
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void node_sendEarlyResp(wn_respHdr* respHdr, void* pktSrc, unsigned int eth_dev_num){
	/* This function is used to send multiple command responses back to the host
	 * under the broader umbrella of a single command exchange. The best example
	 * of this functionality is a 'readIQ' command where a single packet from
	 * the host results in many response packets returning from the board.
	 *
	 * A key assumption in the use of this function is that the underlying command
	 * from the host does not raise the transport-level ACK flag in the transport
	 * header. Furthermore, this function exploits the fact that wn_node can determine
	 * the beginning of the overall send buffer from the location of the response to
	 * be sent.
	 */

	 wn_host_message nodeResp;

#ifdef _DEBUG_
	 xil_printf("In node_sendEarlyResp() \n");
#endif

	 nodeResp.payload = (void*) respHdr;
	 nodeResp.buffer  = (void*) respHdr - ( PAYLOAD_OFFSET + sizeof(wn_transport_header) );
	 nodeResp.length  = PAYLOAD_PAD_NBYTES + respHdr->length + sizeof(wn_cmdHdr); //Extra 2 bytes is for alignment

	//Endian swap the response header before before transport sends it
	// Do it here so the transport sender doesn't have to understand any payload contents
	respHdr->cmd     = Xil_Ntohl(respHdr->cmd);
	respHdr->length  = Xil_Ntohs(respHdr->length);
	respHdr->numArgs = Xil_Ntohs(respHdr->numArgs);

#ifdef _DEBUG_
	xil_printf("sendEarlyResp\n");
	xil_printf("payloadAddr = 0x%x, bufferAddr = 0x%x, len = %d\n",nodeResp.payload,nodeResp.buffer,nodeResp.length);
#endif

	 transport_send(sock_unicast, &nodeResp, pktSrc, eth_dev_num);

}



/*****************************************************************************/
/**
* Node Commands
*
* This function is part of the callback system for the Ethernet transport
* and will be executed when a valid node commands is recevied.
*
* @param    Command Header         - WARPNet Command Header
*           Command Arguments      - WARPNet Command Arguments
*           Response Header        - WARPNet Response Header
*           Response Arguments     - WARPNet Response Arguments
*           Packet Source          - Ethernet Packet Source
*           Ethernet Device Number - Indicates which Ethernet device packet came from
*
* @return	None.
*
* @note		See on-line documentation for more information about the ethernet
*           packet structure for WARPNet:  www.warpproject.org
*
******************************************************************************/
int node_processCmd(const wn_cmdHdr* cmdHdr, void* cmdArgs, wn_respHdr* respHdr,void* respArgs, void* pktSrc, u16 dest_id, u32 eth_dev_num){
	// IMPORTANT ENDIAN NOTES:
	//   - cmdHdr is safe to access directly (pre-swapped if needed)
	//   - cmdArgs is *not* pre-swapped, since the framework doesn't know what it is
	//   - respHdr will be swapped by the framework; user code should fill it normally
	//   - respArgs will *not* be swapped by the framework, since only user code knows what it is
	//         Any data added to respArgs by the code below must be endian-safe (swapped on AXI hardware)

	int            status     = 0;
	u32          * cmdArgs32  = cmdArgs;
	u32          * respArgs32 = respArgs;

	u32            respIndex  = 0;
	u32            respSent   = NO_RESP_SENT;
    u32            max_words  = 320;                // Max number of u32 words that can be sent in the packet (~1400 bytes)
                                                    //   If we need more, then we will need to rework this to send multiple response packets

	u32            cmdID      = WN_CMD_TO_CMDID(cmdHdr->cmd);

    // Variables for functions
    u32            temp, temp2, i;
    s64            timebase_diff;
    u32            msg_cmd;
    u32            id;
    u32            flags;
    u32            serial_number;
    u32            num_blinks;
    u32            time_per_blink;
	u32            start_index;
	u32            curr_index;
	u32            next_index;
	u32            bytes_remaining;
	u32            ip_address;
	u32            size;
	u32            evt_log_size;
	u32            transfer_size;
	u32            bytes_per_pkt;
	u32            num_bytes;
	u32            num_pkts;
	u64            time;
	u64            new_time;
	u64            abs_time;
	int            power;
	u32            rate;
	u32            ant_mode;
	u32            type;

	u32            mem_addr;
	u32            mem_length;
	u32            mem_idx;

	u32            entry_size;

	u8             mac_addr[6];

	u8			   entry_mask;

    wlan_ipc_msg        ipc_msg_to_low;
    interrupt_state_t   prev_interrupt_state;

    // Populate response header
	respHdr->cmd     = cmdHdr->cmd;
	respHdr->length  = 0;
	respHdr->numArgs = 0;

	// Finish any CDMA transfers that might be occurring
	wlan_mac_high_cdma_finish_transfer();

	// Process the command
	switch(cmdID){

//-----------------------------------------------------------------------------
// WARPNet Commands
//-----------------------------------------------------------------------------

	    //---------------------------------------------------------------------
        case CMDID_WARPNET_TYPE:
        	// Return the WARPNet Type
            respArgs32[respIndex++] = Xil_Htonl( node_info.type );    

#ifdef _DEBUG_
            xil_printf("WARPNet Type = %d \n", node_info.type);
#endif

            respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
        break;
        
    
	    //---------------------------------------------------------------------
		case CMDID_NODE_INFO:
			// Return the info about the WLAN_EXP_NODE
            
            // Send node parameters
            temp = node_get_parameters( &respArgs32[respIndex], max_words, WN_TRANSMIT);
            respIndex += temp;
            max_words -= temp;
            if ( max_words <= 0 ) { xil_printf("No more space left in NODE_INFO packet \n"); };
            
            // Send transport parameters
            temp = transport_get_parameters( eth_dev_num, &respArgs32[respIndex], max_words, WN_TRANSMIT);
            respIndex += temp;
            max_words -= temp;
            if ( max_words <= 0 ) { xil_printf("No more space left in NODE_INFO packet \n"); };

#ifdef _DEBUG_
            xil_printf("NODE INFO: \n");
            for ( i = 0; i < respIndex; i++ ) {
            	xil_printf("   [%2d] = 0x%8x \n", i, respArgs32[i]);
            }
            xil_printf("END NODE INFO \n");
#endif

            // --------------------------------
            // Future parameters go here
            // --------------------------------
                        
            // Finalize response
			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;
        

	    //---------------------------------------------------------------------
		case CMDID_NODE_IDENTIFY:
			// Blink the HEX display LEDs
            //   - cmdArgs32[0] - Serial Number
            //   - cmdArgs32[1] - Number of blinks
            //   - cmdArgs32[2] - Microseconds per blink (must be an even number)
            //

			// Get command parameters
			serial_number  = Xil_Ntohl(cmdArgs32[0]);
			num_blinks     = Xil_Ntohl(cmdArgs32[1]);
			time_per_blink = (Xil_Ntohl(cmdArgs32[2]) >> 1);

			u32  left_hex;
			u32  right_hex;
			u32  hw_control;
			u32  temp_control;

			xil_printf("NODE IDENTIFY:  Num blinks = %8d   Time = %8d usec\n", num_blinks, time_per_blink);

			if ( (serial_number == CMD_PARAM_NODE_IDENTIFY_ALL) || (serial_number == node_info.serial_number) ) {
	            xil_printf("    WARPNET Node: %d    IP Address: %d.%d.%d.%d \n", node_info.node, node_info.ip_addr[0], node_info.ip_addr[1],node_info.ip_addr[2],node_info.ip_addr[3]);

				// Send the response early so that code does not time out while waiting for blinks
				//   The host is responsible for waiting until the LED blinking is done before issuing the
				//   node another command.
	            respArgs32[respIndex++] = Xil_Htonl( CMD_PARAM_SUCCESS );
	            respHdr->length        += (respIndex * sizeof(respArgs32));
				respHdr->numArgs        = respIndex;
				node_sendEarlyResp(respHdr, pktSrc, eth_dev_num);
				respSent                = RESP_SENT;

			    // Store the original value of what is under HW control
				hw_control   = userio_read_control(USERIO_BASEADDR);
            	left_hex     = userio_read_hexdisp_left(USERIO_BASEADDR);
            	right_hex    = userio_read_hexdisp_right(USERIO_BASEADDR);

            	// Need to zero out all of the HW control of the hex displays
            	temp_control = (hw_control & ( ~(W3_USERIO_CTRLSRC_HEXDISP_R | W3_USERIO_CTRLSRC_HEXDISP_L)));

            	// Blink for 10 seconds
				for (i = 0; i < num_blinks; i++){
	                userio_write_control( USERIO_BASEADDR, ( temp_control & ( ~( W3_USERIO_HEXDISP_L_MAPMODE | W3_USERIO_HEXDISP_R_MAPMODE ) ) ) );
			        userio_write_hexdisp_left(USERIO_BASEADDR, 0x00);
			        userio_write_hexdisp_right(USERIO_BASEADDR, 0x00);
					usleep(time_per_blink);

					userio_write_control(USERIO_BASEADDR, (temp_control));
	                userio_write_hexdisp_left( USERIO_BASEADDR, left_hex );
		            userio_write_hexdisp_right(USERIO_BASEADDR, right_hex );
					usleep(time_per_blink);
				}

            	// Return original pins to HW control
				userio_write_control(USERIO_BASEADDR, (hw_control));

			} else {
	            respArgs32[respIndex++] = Xil_Htonl( CMD_PARAM_ERROR );
	            respHdr->length        += (respIndex * sizeof(respArgs32));
				respHdr->numArgs        = respIndex;
			}
        break;


	    //---------------------------------------------------------------------
		case CMDID_NODE_CONFIG_SETUP:
            // NODE_CONFIG_SETUP Packet Format:
            //   - Note:  All u32 parameters in cmdArgs32 are byte swapped so use Xil_Ntohl()
            //
            //   - cmdArgs32[0] - Serial Number
            //   - cmdArgs32[1] - Node ID
            //   - cmdArgs32[2] - IP Address
            //   - cmdArgs32[3] - Unicast Port
            //   - cmdArgs32[4] - Broadcast Port
            // 

			// Only update the parameters if the serial numbers match
            if ( node_info.serial_number ==  Xil_Ntohl(cmdArgs32[0]) ) {

            	// Only update the node if it has not been configured
            	if ( node_info.node == 0xFFFF ) {
                    xil_printf("\nReconfiguring ETH %c \n", wn_conv_eth_dev_num(eth_dev_num) );

                	node_info.node = Xil_Ntohl(cmdArgs32[1]) & 0xFFFF;

                    xil_printf("  New Node ID       : %d \n", node_info.node);
                    
                    // Grab New IP Address
                    node_info.ip_addr[0]     = (Xil_Ntohl(cmdArgs32[2]) >> 24) & 0xFF;
                    node_info.ip_addr[1]     = (Xil_Ntohl(cmdArgs32[2]) >> 16) & 0xFF;
                    node_info.ip_addr[2]     = (Xil_Ntohl(cmdArgs32[2]) >>  8) & 0xFF;
                    node_info.ip_addr[3]     = (Xil_Ntohl(cmdArgs32[2])      ) & 0xFF;
                    
                    // Grab new ports
                    node_info.unicast_port   = Xil_Ntohl(cmdArgs32[3]);
                    node_info.broadcast_port = Xil_Ntohl(cmdArgs32[4]);

                    xil_printf("  New IP Address    : %d.%d.%d.%d \n", node_info.ip_addr[0], node_info.ip_addr[1],node_info.ip_addr[2],node_info.ip_addr[3]);
                    xil_printf("  New Unicast Port  : %d \n", node_info.unicast_port);
                    xil_printf("  New Broadcast Port: %d \n", node_info.broadcast_port);

                    transport_set_hw_info( eth_dev_num, node_info.ip_addr, node_info.hw_addr);

                    status = transport_config_sockets(eth_dev_num, node_info.unicast_port, node_info.broadcast_port);

                    xil_printf("\n");
                    if(status != 0) {
        				xil_printf("Error binding transport...\n");
        			} else {
        				userio_write_hexdisp_right(USERIO_BASEADDR, (userio_read_hexdisp_right( USERIO_BASEADDR ) | W3_USERIO_HEXDISP_DP ) );
        			}
                } else {
                    xil_printf("NODE_CONFIG_SETUP Packet ignored.  Network already configured for node %d.\n", node_info.node);
                    xil_printf("    Use NODE_CONFIG_RESET command to reset network configuration.\n\n");
                }
            } else {
                xil_printf("NODE_CONFIG_SETUP Packet with Serial Number %d ignored.  My serial number is %d \n", Xil_Ntohl(cmdArgs32[0]), node_info.serial_number);
            }
		break;

        
	    //---------------------------------------------------------------------
		case CMDID_NODE_CONFIG_RESET:
            // NODE_CONFIG_RESET Packet Format:
            //   - Note:  All u32 parameters in cmdArgs32 are byte swapped so use Xil_Ntohl()
            //
            //   - cmdArgs32[0] - Serial Number
            // 
            
			if (dest_id != BROADCAST_DEST_ID) {
				// Send the response early so that M-Code does not hang when IP address changes
				node_sendEarlyResp(respHdr, pktSrc, eth_dev_num);
				respSent = RESP_SENT;
			}
            
			serial_number = Xil_Ntohl(cmdArgs32[0]);

            // Only update the parameters if the serial numbers match or this it is "all serial numbers"
            if ( (node_info.serial_number ==  serial_number) || (CMD_PARAM_NODE_CONFIG_RESET_ALL == serial_number) ) {

            	if (node_info.node != 0xFFFF){

					// Reset node to 0xFFFF
					node_info.node = 0xFFFF;

					xil_printf("\n!!! Reseting Network Configuration !!! \n\n");

					// Reset transport;  This will update the IP Address back to default and rebind the sockets
					//   - See below for default IP address:  NODE_IP_ADDR_BASE + node
					node_info.ip_addr[0]      = (NODE_IP_ADDR_BASE >> 24) & 0xFF;
					node_info.ip_addr[1]      = (NODE_IP_ADDR_BASE >> 16) & 0xFF;
					node_info.ip_addr[2]      = (NODE_IP_ADDR_BASE >>  8) & 0xFF;
					node_info.ip_addr[3]      = (NODE_IP_ADDR_BASE      ) & 0xFF;  // IP ADDR = w.x.y.z

					node_info.unicast_port    = NODE_UDP_UNICAST_PORT_BASE;
					node_info.broadcast_port  = NODE_UDP_MCAST_BASE;

					transport_set_hw_info(eth_dev_num, node_info.ip_addr, node_info.hw_addr);
					transport_config_sockets(eth_dev_num, node_info.unicast_port, node_info.broadcast_port);

					// Update User IO
					xil_printf("\n!!! Waiting for Network Configuration !!! \n\n");

    				userio_write_hexdisp_right(USERIO_BASEADDR, (userio_read_hexdisp_right( USERIO_BASEADDR ) & ~W3_USERIO_HEXDISP_DP ) );
            	} else {
                    xil_printf("NODE_CONFIG_RESET Packet ignored.  Network configuration already reset on node.\n");
                    xil_printf("    Use NODE_CONFIG_SETUP command to set the network configuration.\n\n");
            	}
            } else {
                xil_printf("NODE_CONFIG_RESET Packet with Serial Number %d ignored.  My serial number is %d \n", Xil_Ntohl(cmdArgs32[0]), node_info.serial_number);
            }
		break;


	    //---------------------------------------------------------------------
		case CMDID_NODE_TEMPERATURE:
            // NODE_TEMPERATURE
            //   - If the system monitor exists, return the current, min and max temperature of the node
            //
			respArgs32[respIndex++] = Xil_Htonl(wn_get_curr_temp());
			respArgs32[respIndex++] = Xil_Htonl(wn_get_min_temp());
			respArgs32[respIndex++] = Xil_Htonl(wn_get_max_temp());

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


//-----------------------------------------------------------------------------
// Log Commands
//-----------------------------------------------------------------------------


	    //---------------------------------------------------------------------
		case CMDID_LOG_CONFIG:
            // NODE_LOG_CONFIG Packet Format:
			//   - cmdArgs32[0]  - flags
			//                     [ 0] - Logging Enabled = 1; Logging Disabled = 0;
			//                     [ 1] - Wrap = 1; No Wrap = 0;
			//                     [ 2] - Full Payloads Enabled = 1; Full Payloads Disabled = 0;
			//                     [ 3] - Log WN Cmds Enabled = 1; Log WN Cmds Disabled = 0;
			//   - cmdArgs32[1]  - mask for flags
			//
            //   - respArgs32[0] - CMD_PARAM_SUCCESS
			//                   - CMD_PARAM_ERROR

			entry_mask = wlan_exp_log_get_entry_en_mask();

			// Set the return value
			status = CMD_PARAM_SUCCESS;

			// Get flags
			temp  = Xil_Ntohl(cmdArgs32[0]);
			temp2 = Xil_Ntohl(cmdArgs32[1]);

			wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_event_log, "Configure flags = 0x%08x  mask = 0x%08x\n", temp, temp2);

			// Configure the LOG based on the flag bit / mask
			if ( ( temp2 & CMD_PARAM_LOG_CONFIG_FLAG_LOGGING ) == CMD_PARAM_LOG_CONFIG_FLAG_LOGGING ) {
				if ( ( temp & CMD_PARAM_LOG_CONFIG_FLAG_LOGGING ) == CMD_PARAM_LOG_CONFIG_FLAG_LOGGING ) {
					event_log_config_logging( EVENT_LOG_LOGGING_ENABLE );
				} else {
					event_log_config_logging( EVENT_LOG_LOGGING_DISABLE );
				}
			}

			if ( ( temp2 & CMD_PARAM_LOG_CONFIG_FLAG_WRAP ) == CMD_PARAM_LOG_CONFIG_FLAG_WRAP ) {
				if ( ( temp & CMD_PARAM_LOG_CONFIG_FLAG_WRAP ) == CMD_PARAM_LOG_CONFIG_FLAG_WRAP ) {
					event_log_config_wrap( EVENT_LOG_WRAP_ENABLE );
				} else {
					event_log_config_wrap( EVENT_LOG_WRAP_DISABLE );
				}
			}

			if ( ( temp2 & CMD_PARAM_LOG_CONFIG_FLAG_PAYLOADS ) == CMD_PARAM_LOG_CONFIG_FLAG_PAYLOADS ) {
				if ( ( temp & CMD_PARAM_LOG_CONFIG_FLAG_PAYLOADS ) == CMD_PARAM_LOG_CONFIG_FLAG_PAYLOADS ) {
					wlan_exp_log_set_mac_payload_len( MAX_MAC_PAYLOAD_LOG_LEN );
				} else {
					wlan_exp_log_set_mac_payload_len( MIN_MAC_PAYLOAD_LOG_LEN );
				}
			}

			if ( ( temp2 & CMD_PARAM_LOG_CONFIG_FLAG_WN_CMDS ) == CMD_PARAM_LOG_CONFIG_FLAG_WN_CMDS ) {
				if ( ( temp & CMD_PARAM_LOG_CONFIG_FLAG_WN_CMDS ) == CMD_PARAM_LOG_CONFIG_FLAG_WN_CMDS ) {
					wlan_exp_enable_logging = 1;
				} else {
					wlan_exp_enable_logging = 0;
				}
			}

			if ( ( temp2 & CMD_PARAM_LOG_CONFIG_FLAG_TXRX_MPDU ) == CMD_PARAM_LOG_CONFIG_FLAG_TXRX_MPDU ) {
				if ( ( temp & CMD_PARAM_LOG_CONFIG_FLAG_TXRX_MPDU ) == CMD_PARAM_LOG_CONFIG_FLAG_TXRX_MPDU ) {
					entry_mask |= ENTRY_EN_MASK_TXRX_MPDU;
				} else {
					entry_mask &= ~ENTRY_EN_MASK_TXRX_MPDU;
				}
			}

			if ( ( temp2 & CMD_PARAM_LOG_CONFIG_FLAG_TXRX_CTRL ) == CMD_PARAM_LOG_CONFIG_FLAG_TXRX_CTRL ) {
				if ( ( temp & CMD_PARAM_LOG_CONFIG_FLAG_TXRX_CTRL ) == CMD_PARAM_LOG_CONFIG_FLAG_TXRX_CTRL ) {
					entry_mask |= ENTRY_EN_MASK_TXRX_CTRL;
				} else {
					entry_mask &= ~ENTRY_EN_MASK_TXRX_CTRL;
				}
			}

			wlan_exp_log_set_entry_en_mask(entry_mask);

			// Send response of status
            respArgs32[respIndex++] = Xil_Htonl( status );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
	    break;


	    //---------------------------------------------------------------------
		case CMDID_LOG_GET_STATUS:
            // NODE_LOG_GET_INFO Packet Format:
            //   - respArgs32[0] - Next empty entry index
            //   - respArgs32[1] - Oldest empty entry index
            //   - respArgs32[2] - Number of wraps
            //   - respArgs32[3] - Flags
			//
			temp = event_log_get_next_entry_index();
            respArgs32[respIndex++] = Xil_Htonl( temp );

			temp = event_log_get_oldest_entry_index();
            respArgs32[respIndex++] = Xil_Htonl( temp );

			temp = event_log_get_num_wraps();
            respArgs32[respIndex++] = Xil_Htonl( temp );

			temp = event_log_get_flags();
            respArgs32[respIndex++] = Xil_Htonl( temp );

			// Send response of current info
			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
	    break;


	    //---------------------------------------------------------------------
		case CMDID_LOG_GET_CAPACITY:
            // NODE_LOG_GET_CAPACITY Packet Format:
            //   - respArgs32[0] - Max log size
            //   - respArgs32[1] - Current log size
            //
			temp = event_log_get_capacity();
            respArgs32[respIndex++] = Xil_Htonl( temp );

			temp = event_log_get_total_size();
            respArgs32[respIndex++] = Xil_Htonl( temp );

			// Send response of current info
			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
	    break;


	    //---------------------------------------------------------------------
		case CMDID_LOG_GET_ENTRIES:
            // NODE_LOG_GET_ENTRIES Packet Format:
            //   - Note:  All u32 parameters in cmdArgs32 are byte swapped so use Xil_Ntohl()
            //
			//   - cmdArgs32[0] - buffer id
			//   - cmdArgs32[1] - flags
            //   - cmdArgs32[2] - start_address of transfer
			//   - cmdArgs32[3] - size of transfer (in bytes)
			//                      0xFFFF_FFFF  -> Get everything in the event log
			//   - cmdArgs32[4] - bytes_per_pkt
			//
			//   Return Value:
			//     - wn_buffer
            //       - buffer_id       - uint32  - ID of the buffer
			//       - flags           - uint32  - Flags
			//       - bytes_remaining - uint32  - Number of bytes remaining in the transfer
			//       - start_byte      - uint32  - Byte index of the first byte in this packet
			//       - size            - uint32  - Number of payload bytes in this packet
			//       - byte[]          - uint8[] - Array of payload bytes
			//
			// NOTE:  The address passed via the command is the address relative to the current
			//   start of the event log.  It is not an absolute address and should not be treated
			//   as such.
			//
			//     When you transferring "everything" in the event log, the command will take a
			//   snapshot of the size of the log to the "end" at the time the command is received
			//   (ie either the next_entry_index or the end of the log before it wraps).  It will then
			//   only transfer those events.  It will not any new events that are added to the log while
			//   we are transferring the current log as well as transfer any events after a wrap.
            //

			id                = Xil_Ntohl(cmdArgs32[0]);
			flags             = Xil_Ntohl(cmdArgs32[1]);
			start_index       = Xil_Ntohl(cmdArgs32[2]);
            size              = Xil_Ntohl(cmdArgs32[3]);

            // Get the size of the log to the "end"
            evt_log_size      = event_log_get_size(start_index);

            // Check if we should transfer everything or if the request was larger than the current log
            if ( ( size == CMD_PARAM_LOG_GET_ALL_ENTRIES ) || ( size > evt_log_size ) ) {
                size = evt_log_size;
            }

            bytes_per_pkt     = max_words * 4;
            num_pkts          = (size / bytes_per_pkt) + 1;
            if ( (size % bytes_per_pkt) == 0 ){ num_pkts--; }    // Subtract the extra pkt if the division had no remainder
            curr_index        = start_index;
            bytes_remaining   = size;

#ifdef _DEBUG_
			// NOTE: The print statements are commented out b/c this command is used
			//   a lot in the inner loop of an experiment
            //
			xil_printf("EVENT LOG: Get Entries \n");
			xil_printf("    curr_index       = 0x%8x\n", curr_index);
			xil_printf("    size             = %10d\n", size);
			xil_printf("    num_pkts         = %10d\n", num_pkts);
#endif

            // Initialize constant parameters
            respArgs32[0] = Xil_Htonl( id );
            respArgs32[1] = Xil_Htonl( flags );

            // Iterate through all the packets
			for( i = 0; i < num_pkts; i++ ) {

				// Get the next address
				next_index  = curr_index + bytes_per_pkt;

				// Compute the transfer size (use the full buffer unless you run out of space)
				if( next_index > ( start_index + size ) ) {
                    transfer_size = (start_index + size) - curr_index;
				} else {
					transfer_size = bytes_per_pkt;
				}

				// Set response args that change per packet
				respArgs32[2]   = Xil_Htonl( bytes_remaining );
	            respArgs32[3]   = Xil_Htonl( curr_index );
                respArgs32[4]   = Xil_Htonl( transfer_size );

                // Unfortunately, due to the byte swapping that occurs in node_sendEarlyResp, we need to set all
                //   three command parameters for each packet that is sent.
	            respHdr->cmd     = cmdHdr->cmd;
	            respHdr->length  = 20 + transfer_size;
				respHdr->numArgs = 5;

				// Transfer data
				num_bytes = event_log_get_data( curr_index, transfer_size, (char *) &respArgs32[5] );

				// Check that we copied everything
				if ( num_bytes == transfer_size ) {
					// Send the packet
					node_sendEarlyResp(respHdr, pktSrc, eth_dev_num);
				} else {
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_event_log,
							        "Tried to get %d bytes, but only received %d @ 0x%x \n", transfer_size, num_bytes, curr_index );
				}

				// Update our current address and bytes remaining
				curr_index       = next_index;
				bytes_remaining -= transfer_size;
			}

			respSent = RESP_SENT;
		break;


		//---------------------------------------------------------------------
		case CMDID_LOG_ADD_EXP_INFO_ENTRY:
			// Add EXP_INFO entry to the log
			//
			// Message format:
			//     cmdArgs32[0]   info_type (lower 16 bits)
			//     cmdArgs32[1]   info_length (lower 16 bits)
			//     cmdArgs32[2:N] info_payload
			//
			// NOTE:  Entry data will be copied in to the log "as is" (ie it will not
			//     have any network to host order translation performed on it)
			//
			type       = (Xil_Ntohl(cmdArgs32[0]) & 0xFFFF);
			size       = (Xil_Ntohl(cmdArgs32[1]) & 0xFFFF);

			// Get the entry size
			if (size == 0) {
				entry_size = sizeof(exp_info_entry);
			} else {
				// 32-bit align size; EXP INFO structure already contains 4 bytes of the payload
				entry_size = sizeof(exp_info_entry) + (((size - 1) / 4)*4);
			}

			exp_info_entry * exp_info;

			exp_info = (exp_info_entry *) wlan_exp_log_create_entry(ENTRY_TYPE_EXP_INFO, entry_size);

			if ( exp_info != NULL ) {
				wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_event_log,
						        "Adding EXP INFO entry with type %d to log (%d bytes)\n", type, size);

				exp_info->timestamp   = get_usec_timestamp();
				exp_info->info_type   = type;
				exp_info->info_length = size;

				// Copy the data to the log entry
				if (size == 0){
					bzero((void *)(&exp_info->info_payload[0]), 4);
				} else {
					memcpy( (void *)(&exp_info->info_payload[0]), (void *)(&cmdArgs32[2]), size );
				}
			}
	    break;


	    //---------------------------------------------------------------------
		case CMDID_LOG_ADD_STATS_TXRX:
			// Add the current statistics to the log
			// TODO:  Add parameter to command to transmit stats
			temp = add_all_txrx_statistics_to_log(WN_NO_TRANSMIT);

			wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_event_log, "Added %d statistics.\n", temp);

			// Send response of oldest index
            respArgs32[respIndex++] = Xil_Htonl( temp );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
        break;


		//---------------------------------------------------------------------
		case CMDID_LOG_ENABLE_ENTRY:
			wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_event_log, "Enable Event not supported\n");
			// TODO:  THIS FUNCTION IS NOT COMPLETE
	    break;


	    //---------------------------------------------------------------------
		case CMDID_LOG_STREAM_ENTRIES:
			// Stream entries from the log
			//
			// Message format:
			//     cmdArgs32[0]   Enable = 1 / Disable = 0
			//     cmdArgs32[1]   IP Address (32 bits)
			//     cmdArgs32[2]   Host ID (upper 16 bits); Port (lower 16 bits)
			//
			temp       = Xil_Ntohl(cmdArgs32[0]);
			ip_address = Xil_Ntohl(cmdArgs32[1]);
			temp2      = Xil_Ntohl(cmdArgs32[2]);

			// Check the enable
			if ( temp == 0 ) {
				wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_event_log,
						        "Disable streaming to %08x (%d)\n", ip_address, (temp2 & 0xFFFF) );
				async_pkt_enable = temp;
			} else {
				wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_event_log,
						        "Enable streaming to %08x (%d)\n", ip_address, (temp2 & 0xFFFF) );

				// Initialize all of the global async packet variables
				async_pkt_enable = temp;

				async_pkt_dest.srcIPAddr = ip_address;
				async_pkt_dest.destPort  = (temp2 & 0xFFFF);

				async_pkt_hdr.destID     = ((temp2 >> 16) & 0xFFFF);
				async_pkt_hdr.srcID      = node_info.node;
				async_pkt_hdr.pktType    = PKTTPYE_NTOH_MSG_ASYNC;
				async_pkt_hdr.length     = PAYLOAD_PAD_NBYTES + 4;
				async_pkt_hdr.seqNum     = 0;
				async_pkt_hdr.flags      = 0;

				status = transport_config_socket( eth_dev_num, &sock_async, &addr_async, ((temp2 >> 16) & 0xFFFF));

				if (status == FAILURE) {
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_event_log, "Failed to configure socket.\n");
				}

				// Transmit the Node Info
				add_node_info_entry(WN_TRANSMIT);
			}

			// Send response
			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
        break;


//-----------------------------------------------------------------------------
// Statistics Commands
//-----------------------------------------------------------------------------


	    //---------------------------------------------------------------------
		case CMDID_STATS_CONFIG_TXRX:
            // NODE_STATS_CONFIG_TXRX Packet Format:
			//   - cmdArgs32[0]  - flags
			//                     [ 0] - Promiscuous stats collected = 1
			//                            Promiscuous stats not collected = 0
			//   - cmdArgs32[1]  - mask for flags
			//
            //   - respArgs32[0] - CMD_PARAM_SUCCESS
			//                   - CMD_PARAM_ERROR

			// Set the return value
			status = CMD_PARAM_SUCCESS;

			// Get flags
			temp  = Xil_Ntohl(cmdArgs32[0]);
			temp2 = Xil_Ntohl(cmdArgs32[1]);

			wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_stats, "Configure flags = 0x%08x  mask = 0x%08x\n", temp, temp2);

			// Configure the LOG based on the flag bit / mask
			if ( ( temp2 & CMD_PARAM_STATS_CONFIG_FLAG_PROMISC ) == CMD_PARAM_STATS_CONFIG_FLAG_PROMISC ) {
				if ( ( temp & CMD_PARAM_STATS_CONFIG_FLAG_PROMISC ) == CMD_PARAM_STATS_CONFIG_FLAG_PROMISC ) {
					promiscuous_stats_enabled = 1;
				} else {
					promiscuous_stats_enabled = 0;
				}
			}

			// Send response of status
            respArgs32[respIndex++] = Xil_Htonl( status );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
	    break;


		//---------------------------------------------------------------------
		case CMDID_STATS_GET_TXRX:
            // NODE_GET_STATS Packet Format:
			//   - cmdArgs32[0]   - buffer id
			//   - cmdArgs32[1]   - flags
            //   - cmdArgs32[2]   - start_address of transfer
			//   - cmdArgs32[3]   - size of transfer (in bytes)
			//   - cmdArgs32[4:5] - MAC Address (All 0xFF means all stats)
			// Always returns a valid WARPNet Buffer (either 1 or more packets)
            //   - buffer_id       - uint32  - buffer_id
			//   - flags           - uint32  - 0
			//   - bytes_remaining - uint32  - Number of bytes remaining in the transfer
			//   - start_byte      - uint32  - Byte index of the first byte in this packet
			//   - size            - uint32  - Number of payload bytes in this packet
			//   - byte[]          - uint8[] - Array of payload bytes

			respSent = node_process_buffer_cmds(cmdHdr, cmdArgs32, respHdr, respArgs32, pktSrc, eth_dev_num, max_words,
					                            print_type_stats, "statistics",
					                            get_statistics(),
					                            sizeof(txrx_stats_entry),
					                            &wlan_exp_get_id_in_statistics,
					                            &find_statistics_txrx_entry,
					                            &copy_statistics_txrx_to_dest_entry,
					                            &zero_txrx_stats_entry);

		break;


//-----------------------------------------------------------------------------
// Local Traffic Generator (LTG) Commands
//-----------------------------------------------------------------------------


		//---------------------------------------------------------------------
		case CMDID_LTG_CONFIG:
            // NODE_LTG_START Packet Format:
			//   - cmdArgs32[0]      - Flags
			//                         [0] - Auto-start the LTG flow
			//   - cmdArgs32[1 - N]  - LTG Schedule (packed)
			//                         [0] - [31:16] Type    [15:0] Length
			//   - cmdArgs32[N+1 - M]- LTG Payload (packed)
			//                         [0] - [31:16] Type    [15:0] Length
			//
            //   - respArgs32[0]     - CMD_PARAM_SUCCESS
			//                       - CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;

			status = CMD_PARAM_SUCCESS;
        	id     = LTG_ID_INVALID;
			flags  = Xil_Ntohl(cmdArgs32[0]);

			// Local variables
			u32            s1, s2, t1, t2;
			void *         ltg_callback_arg;
        	void *         params;

			// Get Schedule & Payload
        	// NOTE:  This allocates memory for both the schedule and payload containers.
        	//   The payload is freed as part of the node_ltg_cleanup() callback
        	//   The schedule is freed as part of this method
			params           = ltg_sched_deserialize( &(((u32 *)cmdArgs)[1]), &t1, &s1 );
			ltg_callback_arg = ltg_payload_deserialize( &(((u32 *)cmdArgs)[2 + s1]), &t2, &s2);

			if( (ltg_callback_arg != NULL) && (params != NULL) ) {

				// Configure the LTG
				id = ltg_sched_create(t1, params, ltg_callback_arg, &node_ltg_cleanup);

				if(id != LTG_ID_INVALID){
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_ltg, "Configured %d\n", id);

					if ((flags & CMD_PARAM_LTG_CONFIG_FLAG_AUTOSTART) == CMD_PARAM_LTG_CONFIG_FLAG_AUTOSTART) {
						wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_ltg, "Starting %d\n", id);
						ltg_sched_start( id );
					}

		        	// Free the memory allocated for the params (ltg_callback_arg will be freed later)
					wlan_mac_high_free(params);
				} else {
		        	status = CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;
		        	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_ltg, "Could not create LTG\n");

		        	// Free the memory allocated in the deserialize
					wlan_mac_high_free(params);
					wlan_mac_high_free(ltg_callback_arg);
				}
			} else {
	        	status = CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;

	        	// Free the memory allocated in the deserialize
	        	if (ltg_callback_arg != NULL) { wlan_mac_high_free(ltg_callback_arg); }
	        	if (params           != NULL) { wlan_mac_high_free(params); }

	        	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_ltg, "Could not allocate memory for CMDID_LTG_CONFIG\n");
			}

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );
            respArgs32[respIndex++] = Xil_Htonl( id );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


	    //---------------------------------------------------------------------
		case CMDID_LTG_START:
            // NODE_LTG_START Packet Format:
			//   - cmdArgs32[0]      - LTG ID
			//
            //   - respArgs32[0]     - CMD_PARAM_SUCCESS
			//                       - CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;

			status = CMD_PARAM_SUCCESS;
			id     = Xil_Ntohl(cmdArgs32[0]);

			// Try to start the ID
			temp2 = ltg_sched_start( id );

			if ( temp2 == 0 ) {
				if (id != CMD_PARAM_LTG_ALL_LTGS){
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_ltg, "Starting %d\n", id);
				} else {
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_ltg, "Starting all LTGs\n");
				}
			} else {
				if (id != CMD_PARAM_LTG_ALL_LTGS){
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_ltg, "Failed to start %d\n", id);
				} else {
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_ltg, "Failed to start all LTGs\n");
				}
	        	status = CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;
			}

			// Send response of current rate
            respArgs32[respIndex++] = Xil_Htonl( status );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


	    //---------------------------------------------------------------------
		case CMDID_LTG_STOP:
            // NODE_LTG_STOP Packet Format:
			//   - cmdArgs32[0]      - LTG ID
			//
            //   - respArgs32[0]     - CMD_PARAM_SUCCESS
			//                       - CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;

			status = CMD_PARAM_SUCCESS;
			id     = Xil_Ntohl(cmdArgs32[0]);

			// Try to stop the ID
			temp2 = ltg_sched_stop( id );

			if ( temp2 == 0 ) {
				if (id != CMD_PARAM_LTG_ALL_LTGS){
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_ltg, "Stopping %d\n", id);
				} else {
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_ltg, "Stopping all LTGs\n");
				}
			} else {
				if (id != CMD_PARAM_LTG_ALL_LTGS){
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_ltg, "Failed to stop %d\n", id);
				} else {
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_ltg, "Failed to stop all LTGs\n");
				}
	        	status = CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;
			}

			// Send response of current rate
            respArgs32[respIndex++] = Xil_Htonl( status );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


	    //---------------------------------------------------------------------
		case CMDID_LTG_REMOVE:
            // NODE_LTG_REMOVE Packet Format:
			//   - cmdArgs32[0]      - LTG ID
			//
            //   - respArgs32[0]     - CMD_PARAM_SUCCESS
			//                       - CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;

			status = CMD_PARAM_SUCCESS;
			id     = Xil_Ntohl(cmdArgs32[0]);

			// Try to remove the ID
			temp2 = ltg_sched_remove( id );

			if ( temp2 == 0 ) {
				if (id != CMD_PARAM_LTG_ALL_LTGS){
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_ltg, "Removing %d\n", id);
				} else {
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_ltg, "Removing all LTGs\n");
				}
			} else {
				if (id != CMD_PARAM_LTG_ALL_LTGS){
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_ltg, "Failed to remove %d\n", id);
				} else {
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_ltg, "Failed to remove all LTGs\n");
				}
	        	status = CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;
			}

			// Send response of status
            respArgs32[respIndex++] = Xil_Htonl( status );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


	    //---------------------------------------------------------------------
		case CMDID_LTG_STATUS:
            // NODE_LTG_STATUS Packet Format:
			//   - cmdArgs32[0]      - LTG ID
			//
            //   - respArgs32[0]     - CMD_PARAM_SUCCESS
			//                       - CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;
			//   - respArgs32[1]     - CMD_PARAM_LTG_RUNNING
			//                       - CMD_PARAM_LTG_STOPPED
			//   - respArgs32[3:2]   - Last start timestamp
			//   - respArgs32[5:4]   - Last stop timestamp
			//
			status = CMD_PARAM_SUCCESS;
			id     = Xil_Ntohl(cmdArgs32[0]);
			temp   = sizeof(ltg_sched_state_hdr) / 4;      // Number of return args for the header

			u32      * state;
			dl_entry * curr_tg_dl_entry;

			curr_tg_dl_entry = ltg_sched_find_tg_schedule(id);

			if(curr_tg_dl_entry != NULL){
				state  = (u32 *)((tg_schedule*)(curr_tg_dl_entry->data))->state;
			} else {
	        	status = CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;
			}

			// Send response of status
            respArgs32[respIndex++] = Xil_Htonl( status );

			if(curr_tg_dl_entry != NULL){
            	for (i = 0; i < temp; i++) {
                    respArgs32[respIndex++] = Xil_Htonl( state[i] );
            	}
            } else {
            	for (i = 0; i < temp; i++) {
                    respArgs32[respIndex++] = 0xFFFFFFFF;
            	}
            }

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


//-----------------------------------------------------------------------------
// Node Commands
//-----------------------------------------------------------------------------


	    //---------------------------------------------------------------------
		case CMDID_NODE_RESET_STATE:
            // NODE_RESET_STATE Packet Format:
			//   - cmdArgs32[0]  - Flags
			//                     [0] - NODE_RESET_LOG
			//                     [1] - NODE_RESET_TXRX_STATS
			//                     [2] - NODE_RESET_LTG
			//                     [3] - NODE_RESET_TX_DATA_QUEUE
			//                     [4] - NODE_RESET_ASSOCIATIONS
			//                     [5] - NODE_RESET_BSS_INFO
			temp   = Xil_Ntohl(cmdArgs32[0]);
			status = CMD_PARAM_SUCCESS;

			// Disable interrupts so no packets interrupt the reset
			prev_interrupt_state = wlan_mac_high_interrupt_stop();
			// Configure the LOG based on the flag bits
			if ( ( temp & CMD_PARAM_NODE_RESET_FLAG_LOG ) == CMD_PARAM_NODE_RESET_FLAG_LOG ) {
				wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_event_log, "Reset log\n");
				event_log_reset();
			}

			if ( ( temp & CMD_PARAM_NODE_RESET_FLAG_TXRX_STATS ) == CMD_PARAM_NODE_RESET_FLAG_TXRX_STATS ) {
				wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_stats, "Reseting Statistics\n");
				wlan_exp_reset_station_statistics_callback();
			}

			if ( ( temp & CMD_PARAM_NODE_RESET_FLAG_LTG ) == CMD_PARAM_NODE_RESET_FLAG_LTG ) {
				status = ltg_sched_remove( LTG_REMOVE_ALL );

				if ( status != 0 ) {
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_ltg, "Failed to remove all LTGs\n");
					status = CMD_PARAM_ERROR + CMD_PARAM_LTG_ERROR;
				} else {
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_ltg, "Removing All LTGs\n");
				}
			}

			if ( ( temp & CMD_PARAM_NODE_RESET_FLAG_TX_DATA_QUEUE ) == CMD_PARAM_NODE_RESET_FLAG_TX_DATA_QUEUE ) {
				wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_queue, "Purging all data transmit queues\n");
				wlan_exp_purge_all_data_tx_queue_callback();
			}

			if ( ( temp & CMD_PARAM_NODE_RESET_FLAG_ASSOCIATIONS ) == CMD_PARAM_NODE_RESET_FLAG_ASSOCIATIONS ) {
				wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Resetting associations\n");
				wlan_exp_reset_all_associations_callback();
			}

			if ( ( temp & CMD_PARAM_NODE_RESET_FLAG_BSS_INFO ) == CMD_PARAM_NODE_RESET_FLAG_BSS_INFO ) {
				wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Resetting BSS info\n");
				wlan_exp_reset_bss_info_callback();
			}

			// Re-enable interrupts
			wlan_mac_high_interrupt_restore_state(prev_interrupt_state);

			// Send response of success
            respArgs32[respIndex++] = Xil_Htonl( status );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


		//---------------------------------------------------------------------
		case CMDID_NODE_CONFIGURE:
            // CMDID_NODE_CONFIGURE Packet Format:
			//   - cmdArgs32[0]  - Flags
			//                     [0] - NODE_CONFIG_FLAG_DSSS_ENABLE
			//   - cmdArgs32[1]  - Flag mask
			//   - cmdArgs32[2]  - WLAN Exp debug level
			//                     [31]  - Set debug level
			//                     [7:0] - Debug level
			//
			status = CMD_PARAM_SUCCESS;

			// Get flags
			temp  = Xil_Ntohl(cmdArgs32[0]);
			temp2 = Xil_Ntohl(cmdArgs32[1]);

			wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Configure flags = 0x%08x  mask = 0x%08x\n", temp, temp2);

			// Configure the Node based on the flag bit / mask
			if ((temp2 & CMD_PARAM_NODE_CONFIG_FLAG_DSSS_ENABLE) == CMD_PARAM_NODE_CONFIG_FLAG_DSSS_ENABLE) {
				if ((temp & CMD_PARAM_NODE_CONFIG_FLAG_DSSS_ENABLE) == CMD_PARAM_NODE_CONFIG_FLAG_DSSS_ENABLE) {
					wlan_mac_high_set_dsss( 0x1 );
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Enabled DSSS\n");
				} else {
					wlan_mac_high_set_dsss( 0x0 );
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Disabled DSSS\n");
				}
			}

			temp  = Xil_Ntohl(cmdArgs32[2]);

			// Set debug print level
			if ((temp & CMD_PARAM_NODE_CONFIG_SET_WLAN_EXP_PRINT_LEVEL) == CMD_PARAM_NODE_CONFIG_SET_WLAN_EXP_PRINT_LEVEL) {
				wlan_exp_set_print_level(temp & 0xFF);
			}

			// Send response of status
            respArgs32[respIndex++] = Xil_Htonl( status );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


		//---------------------------------------------------------------------
		case CMDID_NODE_WLAN_MAC_ADDR:
            // Get / Set the wireless MAC address
			//
			// Message format:
			//     cmdArgs32[0]    Command:
			//                       - Write       (NODE_WRITE_VAL)
			//                       - Read        (NODE_READ_VAL)
			//     cmdArgs32[1:2]  MAC Address (write-only)
			//
			// Response format:
			//     respArgs32[0]   Status
			//     respArgs32[1:2] Current MAC Address
			//
			status  = CMD_PARAM_SUCCESS;
			msg_cmd = Xil_Ntohl(cmdArgs32[0]);

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
					wlan_exp_get_mac_addr(&cmdArgs32[1], &mac_addr[0]);

					// !!!! TODO !!!!
					// Need to set the MAC Address of the node; this will have to be
					// implemented for each subclass of the nodes (ie AP, STA, IBSS, etc)
					// Not sure if this should be a callback?
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Setting Wireless MAC Address not supported at this time\n");

				break;

				case CMD_PARAM_READ_VAL:
				break;

				default:
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
					status = CMD_PARAM_ERROR;
				break;
			}

			// Send response of status
            respArgs32[respIndex++] = Xil_Htonl( status );

            wlan_exp_put_mac_addr(get_wlan_mac_addr(), &respArgs32[respIndex]);
            respIndex += 2;

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


		//---------------------------------------------------------------------
		case CMDID_NODE_TIME:
			// Set / Get node time
			//
			// Message format:
			//     cmdArgs32[0]   Command:
			//                      - Write       (NODE_WRITE_VAL)
			//                      - Read        (NODE_READ_VAL)
			//                      - Add to log  (NODE_TIME_ADD_TO_LOG_VAL)
			//     cmdArgs32[1]   ID
			//     cmdArgs32[2]   New Time in microseconds - lower 32 bits (or NODE_TIME_RSVD_VAL)
			//     cmdArgs32[3]   New Time in microseconds - upper 32 bits (or NODE_TIME_RSVD_VAL)
			//     cmdArgs32[4]   Abs Time in microseconds - lower 32 bits (or NODE_TIME_RSVD_VAL)
			//     cmdArgs32[5]   Abs Time in microseconds - upper 32 bits (or NODE_TIME_RSVD_VAL)
			//
			// Response format:
			//     respArgs32[0]  Status
			//     respArgs32[1]  Time on node in microseconds - lower 32 bits
			//     respArgs32[2]  Time on node in microseconds - upper 32 bits
			//
			msg_cmd = Xil_Ntohl(cmdArgs32[0]);
			id      = Xil_Ntohl(cmdArgs32[1]);
			time    = get_usec_timestamp();
			status  = CMD_PARAM_SUCCESS;

			time_info_entry * time_entry;

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
				case CMD_PARAM_NODE_TIME_ADD_TO_LOG_VAL:
					// Get the new time
					temp     = Xil_Ntohl(cmdArgs32[2]);
					temp2    = Xil_Ntohl(cmdArgs32[3]);
					new_time = (((u64)temp2)<<32) + ((u64)temp);

					// If this is a write, then update the time on the node
					if (msg_cmd == CMD_PARAM_WRITE_VAL){
						timebase_diff = (s64)new_time - (s64)get_usec_timestamp();
						wlan_exp_adjust_timebase_callback( timebase_diff );
						wlan_mac_high_set_timestamp( new_time );
						wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set time = 0x%08x 0x%08x\n", temp2, temp);
					}

					// Get the absolute time
					temp     = Xil_Ntohl(cmdArgs32[4]);
					temp2    = Xil_Ntohl(cmdArgs32[5]);
					abs_time = (((u64)temp2)<<32) + ((u64)temp);

					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Absolute time = 0x%08x 0x%08x\n", temp2, temp);

					// Create a time info log entry
					time_entry = (time_info_entry *)wlan_exp_log_create_entry( ENTRY_TYPE_TIME_INFO, sizeof(time_info_entry) );

					if (time_entry != NULL) {
						time_entry->timestamp  = time;
						time_entry->time_id    = id;
						if ( msg_cmd == CMD_PARAM_WRITE_VAL) {
							time_entry->reason = TIME_INFO_ENTRY_WN_SET_TIME;
						} else {
							time_entry->reason = TIME_INFO_ENTRY_WN_ADD_LOG;
						}
						time_entry->new_time   = new_time;
						time_entry->abs_time   = abs_time;
					}

					// If this was a write, then update the time value so we can return it to the host
					//   This is done after the log entry to the fields are correct in the entry.
					if (msg_cmd == CMD_PARAM_WRITE_VAL){
						time = new_time;
					}
				break;

				case CMD_PARAM_READ_VAL:
				break;

				default:
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
					status = CMD_PARAM_ERROR;
				break;
			}

			temp  = time & 0xFFFFFFFF;
			temp2 = (time >> 32) & 0xFFFFFFFF;

			// Send response
			respArgs32[respIndex++] = Xil_Htonl( status );
			respArgs32[respIndex++] = Xil_Htonl( temp );
			respArgs32[respIndex++] = Xil_Htonl( temp2 );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


	    //---------------------------------------------------------------------
		case CMDID_NODE_LOW_TO_HIGH_FILTER:
			// Set node MAC low to high filter
			//
			// Message format:
			//     cmdArgs32[0]   Command
			//     cmdArgs32[1]   RX Filter
			//
			// Response format:
			//     respArgs32[0]  Status
			//
			msg_cmd = Xil_Ntohl(cmdArgs32[0]);
			temp    = Xil_Ntohl(cmdArgs32[1]);
			status  = CMD_PARAM_SUCCESS;

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set RX filter = 0x%08x\n", temp);
					wlan_mac_high_set_rx_filter_mode(temp);
			    break;

				default:
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
					status = CMD_PARAM_ERROR;
				break;
			}

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


		//---------------------------------------------------------------------
		// Case NODE_CHANNEL is implemented in the child classes


	    //---------------------------------------------------------------------
		case CMDID_NODE_RANDOM_SEED:
			// Set the random seed for the random number generator for cpu high / low
			//
			// Message format:
			//     cmdArgs32[0]   Command (only writes are supported
			//     cmdArgs32[1]   CPU High Seed Valid
			//     cmdArgs32[2]   CPU High Seed
			//     cmdArgs32[3]   CPU Low  Seed Valid
			//     cmdArgs32[4]   CPU Low  Seed
			//
			// Response format:
			//     respArgs32[0]  Status
			//
			msg_cmd = Xil_Ntohl(cmdArgs32[0]);
			status  = CMD_PARAM_SUCCESS;

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
					// Process the seed for CPU high
					temp    = Xil_Ntohl(cmdArgs32[1]);
					temp2   = Xil_Ntohl(cmdArgs32[2]);
					if (temp == CMD_PARAM_RANDOM_SEED_VALID) {
						wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set CPU High random seed = 0x%08x\n", temp2);
						srand(temp2);
					}

					// Process the seed for CPU low
					temp    = Xil_Ntohl(cmdArgs32[3]);
					temp2   = Xil_Ntohl(cmdArgs32[4]);
					if (temp == CMD_PARAM_RANDOM_SEED_VALID) {
						wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set CPU Low  random seed = 0x%08x\n", temp2);
						wlan_mac_high_set_srand(temp2);
					}
			    break;

				default:
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
					status = CMD_PARAM_ERROR;
				break;
			}

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


		//---------------------------------------------------------------------
		case CMDID_NODE_LOW_PARAM:
			// Set node MAC low to high filter
			//
			// Message format:
			//     cmdArgs32[0]    Command
			//     cmdArgs32[1]    Size in words of LOW_PARAM_MESSAGE
			//     cmdArgs32[2]    LOW_PARAM_MESSAGE
			//                       [0]   PARAM_ID
			//	                     [1:N] ARGS
			//
			// Response format:
			//     respArgs32[0]    Status
			//     respArgs32[1]    Size in words of PARAM ARGS
			//     respArgs32[2]    PARAM ID
			//     respArgs32[3:N]  PARAM ARGS
			//
			msg_cmd 		 = Xil_Ntohl(cmdArgs32[0]);
			size             = Xil_Ntohl(cmdArgs32[1]);
			temp             = 0;

			// Fix the order of all the payload words for the LOW_PARAM_MESSAGE
			for(i = 2; i < (size + 2); i++) {
				cmdArgs32[i] = Xil_Ntohl(cmdArgs32[i]);
			}

			id      = cmdArgs32[2];        // Already byte swapped in for loop above
			status  = CMD_PARAM_SUCCESS;

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
					// Send message to CPU Low
					ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_LOW_PARAM);
					ipc_msg_to_low.num_payload_words = size;
					ipc_msg_to_low.arg0				 = IPC_REG_WRITE_MODE;
					ipc_msg_to_low.payload_ptr       = &(cmdArgs32[2]);

					prev_interrupt_state = wlan_mac_high_interrupt_stop();
					ipc_mailbox_write_msg(&ipc_msg_to_low);
					wlan_mac_high_interrupt_restore_state(prev_interrupt_state);
				break;

				case CMD_PARAM_READ_VAL:
					temp2 = wlan_mac_high_read_low_param(id, &size, &(respArgs32[3]));

					if(temp2 == 0) { //Success
						// Don't set the default response
						temp = 1;

						// Add length argument to response
						respArgs32[respIndex++] = Xil_Htonl( status );
						respArgs32[respIndex++] = Xil_Htonl( size );
						respArgs32[respIndex++] = Xil_Htonl( id );
						respHdr->length += (respIndex * sizeof(respArgs32));
						respHdr->numArgs = respIndex;

						// Endian swap payload returned by CPU Low
						for(i = 0; i < size; i++) {
							respArgs32[3 + i] = Xil_Htonl(respArgs32[3 + i]);
						}

						respHdr->length  += (size * sizeof(u32));
						respHdr->numArgs += size;

					} else { //failed
						wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Parameter read failed in CPU low.\n");
						status = CMD_PARAM_ERROR + id;
					}
			    break;

				default:
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
					status = CMD_PARAM_ERROR + id;
				break;
			}

			// Send default response
			if (temp == 0) {
				respArgs32[respIndex++] = Xil_Htonl( status );

				respHdr->length += (respIndex * sizeof(respArgs32));
				respHdr->numArgs = respIndex;
			}
		break;


	    //---------------------------------------------------------------------
		case CMDID_NODE_TX_POWER:
            // CMDID_NODE_TX_POWER Packet Format:
			//   - cmdArgs32[0]      - Command
			//   - cmdArgs32[1]      - Type
			//   - cmdArgs32[2]      - Power (Shifted by TX_POWER_MIN_DBM)
			//   - cmdArgs32[3 - 4]  - MAC Address (All 0xF means all nodes)

			msg_cmd = Xil_Ntohl(cmdArgs32[0]);
			type    = Xil_Ntohl(cmdArgs32[1]);
			temp    = Xil_Ntohl(cmdArgs32[2]);
			status  = CMD_PARAM_SUCCESS;

			// Shift power value from transmission to get the power
			power = temp + TX_POWER_MIN_DBM;

			// Adjust the power so that it falls in an acceptable range
			if(power < TX_POWER_MIN_DBM){ power = TX_POWER_MIN_DBM; }
			if(power > TX_POWER_MAX_DBM){ power = TX_POWER_MAX_DBM; }

			// Process the command
			if (type == CMD_PARAM_UNICAST_VAL) {
				switch (msg_cmd) {
                    case CMD_PARAM_WRITE_VAL:
                    case CMD_PARAM_READ_VAL:
        				// Get MAC Address
        				wlan_exp_get_mac_addr(&((u32 *)cmdArgs32)[3], &mac_addr[0]);

        				// If necessary, add an association.  This is primarily for IBSS nodes where
        				//   the association table might not be set up at the time this is called.
    					// NOTE: A multicast mac_addr should *not* be added to the association table.
        				if(wlan_addr_mcast(mac_addr) == 0){
        					wlan_exp_tx_cmd_add_association_callback(&mac_addr[0]);
        				}

        				id = wlan_exp_get_id_in_associated_stations(&mac_addr[0]);

        				status = node_process_tx_power(msg_cmd, id, power);
                    break;

                    case CMD_PARAM_WRITE_DEFAULT_VAL:
    					// Set the default unicast data & management parameter
    					default_unicast_data_tx_params.phy.power = power;
    					default_unicast_mgmt_tx_params.phy.power = power;
    					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set default unicast TX power = %d dBm\n", power);
					break;

                    case CMD_PARAM_READ_DEFAULT_VAL:
    					// Get the default unicast data parameter
    					power = default_unicast_data_tx_params.phy.power;
					break;

                    default:
                    	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
    					status = CMD_PARAM_ERROR;
                    break;
				}
			} else if (type == CMD_PARAM_MULTICAST_DATA_VAL) {
				switch (msg_cmd) {
                    case CMD_PARAM_WRITE_VAL:
                    case CMD_PARAM_WRITE_DEFAULT_VAL:
    					// Set the default multicast data parameter
    					default_multicast_data_tx_params.phy.power = power;
    					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set default multicast data TX power = %d dBm\n", power);
					break;

                    case CMD_PARAM_READ_VAL:
                    case CMD_PARAM_READ_DEFAULT_VAL:
    					// Get the default multicast data parameter
    					power = default_multicast_data_tx_params.phy.power;
					break;

                    default:
                    	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
    					status = CMD_PARAM_ERROR;
                    break;
				}
			} else if (type == CMD_PARAM_MULTICAST_MGMT_VAL) {
				switch (msg_cmd) {
                    case CMD_PARAM_WRITE_VAL:
                    case CMD_PARAM_WRITE_DEFAULT_VAL:
    					// Set the default multicast management parameter
    					default_multicast_mgmt_tx_params.phy.power = power;
    					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set default multicast mgmt TX power = %d dBm\n", power);
					break;

                    case CMD_PARAM_READ_VAL:
                    case CMD_PARAM_READ_DEFAULT_VAL:
    					// Get the default multicast management parameter
    					power = default_multicast_mgmt_tx_params.phy.power;
					break;

                    default:
                    	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
    					status = CMD_PARAM_ERROR;
                    break;
				}
			} else if (type == CMD_PARAM_NODE_TX_POWER_LOW) {
				switch (msg_cmd) {
                    case CMD_PARAM_WRITE_VAL:
                    case CMD_PARAM_WRITE_DEFAULT_VAL:
        	        	// Send IPC to CPU low to set the Tx power for control frames
        			    wlan_mac_high_set_tx_ctrl_pow(power);
    					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set control packet TX power = %d dBm\n", power);
					break;

                    case CMD_PARAM_READ_VAL:
                    case CMD_PARAM_READ_DEFAULT_VAL:
                    	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Reading control packet power not currently supported\n");
    					status = CMD_PARAM_ERROR;
					break;

                    default:
                    	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
    					status = CMD_PARAM_ERROR;
                    break;
				}
			} else if (type == CMD_PARAM_NODE_TX_POWER_ALL) {
				// Set all power values:
				//     * Default Unicast Management Packet Tx Power for new associations
	            //     * Default Unicast Data Packet Tx Power for new associations
				//     * Default Multicast Management Packet Tx Power for new associations
				//     * Default Multicast Data Packet Tx Power for new associations
				//     * Control Packet Tx Power
				//     * Update the transmit power of all current associations on the node.
	        	wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set all TX power = %d dBm\n", power);

	        	// Set the default unicast power for new associations
			    default_unicast_mgmt_tx_params.phy.power   = power;
			    default_unicast_data_tx_params.phy.power   = power;

	        	// Set the default multicast power for new associations
			    default_multicast_mgmt_tx_params.phy.power = power;
			    default_multicast_data_tx_params.phy.power = power;

	        	// Send IPC to CPU low to set the Tx power for control frames
			    wlan_mac_high_set_tx_ctrl_pow(power);

			    // Update the Tx power in each current association
			    status = node_process_tx_power(CMD_PARAM_WRITE_VAL, WLAN_EXP_AID_ALL, power);
			} else {
				wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown type for NODE_TX_RATE: %d\n", type);
				status = CMD_PARAM_ERROR;
			}

			// Shift power for transmission
			temp = power - TX_POWER_MIN_DBM;

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );
            respArgs32[respIndex++] = Xil_Htonl( temp );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


	    //---------------------------------------------------------------------
		case CMDID_NODE_TX_RATE:
            // NODE_TX_RATE Packet Format:
			//   - cmdArgs32[0]      - Command
			//   - cmdArgs32[1]      - Type
			//   - cmdArgs32[2]      - Rate
			//   - cmdArgs32[3 - 4]  - MAC Address (All 0xF means all nodes)

			msg_cmd = Xil_Ntohl(cmdArgs32[0]);
			type    = Xil_Ntohl(cmdArgs32[1]);
			rate    = Xil_Ntohl(cmdArgs32[2]);
			status  = CMD_PARAM_SUCCESS;

			// Adjust the rate so that it falls in an acceptable range
			if(rate < WLAN_MAC_MCS_6M ){ rate = WLAN_MAC_MCS_6M;  }
			if(rate > WLAN_MAC_MCS_54M){ rate = WLAN_MAC_MCS_54M; }

			// Process the command
			if (type == CMD_PARAM_UNICAST_VAL) {
				switch (msg_cmd) {
                    case CMD_PARAM_WRITE_VAL:
                    case CMD_PARAM_READ_VAL:
        				// Get MAC Address
        				wlan_exp_get_mac_addr(&((u32 *)cmdArgs32)[3], &mac_addr[0]);

        				// If necessary, add an association.  This is primarily for IBSS nodes where
        				//   the association table might not be set up at the time this is called.
    					// NOTE: A multicast mac_addr should *not* be added to the association table.
        				if(wlan_addr_mcast(mac_addr) == 0){
        					wlan_exp_tx_cmd_add_association_callback(&mac_addr[0]);
        				}

        				id = wlan_exp_get_id_in_associated_stations(&mac_addr[0]);

        				rate = node_process_tx_rate( msg_cmd, id, (rate & 0xFF));

        				if ( (rate << 24) == CMD_PARAM_ERROR ) {
        					status = CMD_PARAM_ERROR;
        				}
                    break;

                    case CMD_PARAM_WRITE_DEFAULT_VAL:
    					// Set the default unicast data & management parameter
    					default_unicast_data_tx_params.phy.rate = rate;
    					default_unicast_mgmt_tx_params.phy.rate = rate;
    					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node,
    							        "Set default unicast TX rate = %d Mbps\n", wlan_lib_mac_rate_to_mbps(rate));
					break;

                    case CMD_PARAM_READ_DEFAULT_VAL:
    					// Get the default unicast data parameter
    					rate = default_unicast_data_tx_params.phy.rate;
					break;

                    default:
                    	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
    					status = CMD_PARAM_ERROR;
                    break;
				}
			} else if (type == CMD_PARAM_MULTICAST_DATA_VAL) {
				switch (msg_cmd) {
                    case CMD_PARAM_WRITE_VAL:
                    case CMD_PARAM_WRITE_DEFAULT_VAL:
    					// Set the default multicast data parameter
    					default_multicast_data_tx_params.phy.rate = rate;
    					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node,
    							        "Set default multicast data TX rate = %d Mbps\n", wlan_lib_mac_rate_to_mbps(rate));
					break;

                    case CMD_PARAM_READ_VAL:
                    case CMD_PARAM_READ_DEFAULT_VAL:
    					// Get the default multicast data parameter
    					rate = default_multicast_data_tx_params.phy.rate;
					break;

                    default:
                    	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
    					status = CMD_PARAM_ERROR;
                    break;
				}
			} else if (type == CMD_PARAM_MULTICAST_MGMT_VAL) {
				switch (msg_cmd) {
                    case CMD_PARAM_WRITE_VAL:
                    case CMD_PARAM_WRITE_DEFAULT_VAL:
    					// Set the default multicast management parameter
    					default_multicast_mgmt_tx_params.phy.rate = rate;
    					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node,
    							        "Set default multicast mgmt TX rate = %d Mbps\n", wlan_lib_mac_rate_to_mbps(rate));
					break;

                    case CMD_PARAM_READ_VAL:
                    case CMD_PARAM_READ_DEFAULT_VAL:
    					// Get the default multicast management parameter
    					rate = default_multicast_mgmt_tx_params.phy.rate;
					break;

                    default:
                    	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
    					status = CMD_PARAM_ERROR;
                    break;
				}
			} else {
				wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown type for NODE_TX_RATE: %d\n", type);
				status = CMD_PARAM_ERROR;
			}

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );
            respArgs32[respIndex++] = Xil_Htonl( rate );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


	    //---------------------------------------------------------------------
		case CMDID_NODE_TX_ANT_MODE:
            // NODE_TX_ANT_MODE Packet Format:
			//   - cmdArgs32[0]      - Command
			//   - cmdArgs32[1]      - Type
			//   - cmdArgs32[2]      - Antenna Mode
			//   - cmdArgs32[3 - 4]  - MAC Address (All 0xF means all nodes)

			msg_cmd  = Xil_Ntohl(cmdArgs32[0]);
			type     = Xil_Ntohl(cmdArgs32[1]);
			ant_mode = Xil_Ntohl(cmdArgs32[2]);
			status   = CMD_PARAM_SUCCESS;

			// NOTE:  This method assumes that the Antenna mode received is valid.
			// The checking will be done on either the host, in CPU Low or both.

			if (type == CMD_PARAM_UNICAST_VAL) {
				switch (msg_cmd) {
                    case CMD_PARAM_WRITE_VAL:
                    case CMD_PARAM_READ_VAL:
        				// Get MAC Address
        				wlan_exp_get_mac_addr(&((u32 *)cmdArgs32)[3], &mac_addr[0]);

        				// If necessary, add an association.  This is primarily for IBSS nodes where
        				//   the association table might not be set up at the time this is called.
    					// NOTE: A multicast mac_addr should *not* be added to the association table.
        				if(wlan_addr_mcast(mac_addr) == 0){
        					wlan_exp_tx_cmd_add_association_callback(&mac_addr[0]);
        				}

        				id = wlan_exp_get_id_in_associated_stations(&mac_addr[0]);

        				ant_mode = node_process_tx_ant_mode( msg_cmd, id, (ant_mode & 0xFF));

        				if ( (ant_mode << 24) == CMD_PARAM_ERROR ) {
        					status = CMD_PARAM_ERROR;
        				}
                    break;

                    case CMD_PARAM_WRITE_DEFAULT_VAL:
						// Set the default unicast data & management parameter
						default_unicast_data_tx_params.phy.antenna_mode = ant_mode;
						default_unicast_mgmt_tx_params.phy.antenna_mode = ant_mode;
						wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set default unicast TX antenna mode = %d\n", ant_mode);
					break;

                    case CMD_PARAM_READ_DEFAULT_VAL:
						// Get the default unicast data parameter
						ant_mode = default_unicast_data_tx_params.phy.antenna_mode;
					break;

                    default:
                    	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
    					status = CMD_PARAM_ERROR;
                    break;
				}
			} else if (type == CMD_PARAM_MULTICAST_DATA_VAL) {
				switch (msg_cmd) {
                    case CMD_PARAM_WRITE_VAL:
                    case CMD_PARAM_WRITE_DEFAULT_VAL:
    					// Set the default multicast data paramter
    					default_multicast_data_tx_params.phy.antenna_mode = ant_mode;
    					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set default multicast data TX antenna mode = %d\n", ant_mode);
					break;

                    case CMD_PARAM_READ_VAL:
                    case CMD_PARAM_READ_DEFAULT_VAL:
    					// Get the default multicast data parameter
    					ant_mode = default_multicast_data_tx_params.phy.antenna_mode;
					break;

                    default:
                    	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
    					status = CMD_PARAM_ERROR;
                    break;
				}
			} else if (type == CMD_PARAM_MULTICAST_MGMT_VAL) {
				switch (msg_cmd) {
                    case CMD_PARAM_WRITE_VAL:
                    case CMD_PARAM_WRITE_DEFAULT_VAL:
    					// Set the default multicast management parameter
    					default_multicast_mgmt_tx_params.phy.antenna_mode = ant_mode;
    					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set default multicast mgmt TX antenna mode = %d\n", ant_mode);
					break;

                    case CMD_PARAM_READ_VAL:
                    case CMD_PARAM_READ_DEFAULT_VAL:
    					// Get the default multicast management parameter
    					ant_mode = default_multicast_mgmt_tx_params.phy.antenna_mode;
					break;

                    default:
                    	wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
    					status = CMD_PARAM_ERROR;
                    break;
				}
			} else {
				wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown type for NODE_TX_RATE: %d\n", type);
				status = CMD_PARAM_ERROR;
			}

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );
            respArgs32[respIndex++] = Xil_Htonl( ant_mode );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


	    //---------------------------------------------------------------------
		case CMDID_NODE_RX_ANT_MODE:
            // NODE_RX_ANT_MODE Packet Format:
			//   - cmdArgs32[0]      - Command
			//   - cmdArgs32[1]      - Antenna Mode
            //
			// NOTE:  This method assumes that the Antenna mode received is valid.
			// The checking will be done on either the host, in CPU Low or both.

			msg_cmd  = Xil_Ntohl(cmdArgs32[0]);
			ant_mode = Xil_Ntohl(cmdArgs32[1]);
			status  = CMD_PARAM_SUCCESS;

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
				case CMD_PARAM_WRITE_DEFAULT_VAL:
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set RX antenna mode = %d\n", ant_mode);
	            	wlan_mac_high_set_rx_ant_mode(ant_mode);
				break;

				case CMD_PARAM_READ_VAL:
				case CMD_PARAM_READ_DEFAULT_VAL:
	            	ant_mode = rx_ant_mode_tracker;
				break;

				default:
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
					status = CMD_PARAM_ERROR;
				break;
			}

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );
            respArgs32[respIndex++] = Xil_Htonl( ant_mode );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


//-----------------------------------------------------------------------------
// Association Commands
//-----------------------------------------------------------------------------


		//---------------------------------------------------------------------
		case CMDID_NODE_GET_SSID:
			// Get the SSID
			//
			// NOTE:  This method does not force any maximum length on the SSID.  However,
			//   the rest of the framework enforces the convention that the maximum length
			//   of the SSID is SSID_LEN_MAX.
			//
			// Message format:
			//     No arguments
			//
			// Response format:
			//     respArgs32[0]       Status
			//     respArgs32[1]       SSID Length
			//     respArgs32[2:N]     SSID (packed array of ascii character values)
			//                             NOTE: The characters are copied with a straight strcpy
			//                               and must be correctly processed on the host side
			//

			// Send response
			respArgs32[respIndex++] = Xil_Htonl( CMD_PARAM_SUCCESS );

			// Return the size and current SSID
			if (my_bss_info->ssid != NULL) {
				wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "SSID = %s\n", my_bss_info->ssid);

				temp = strlen(my_bss_info->ssid);

				respArgs32[respIndex++] = Xil_Htonl( temp );

				strcpy( (char *)&respArgs32[respIndex], my_bss_info->ssid );

				respIndex       += ( temp / sizeof(respArgs32) ) + 1;
			} else {
				// Return a zero length string
				respArgs32[respIndex++] = 0;
			}

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


	    //---------------------------------------------------------------------
		// Case NODE_DISASSOCIATE      is implemented in the child classes


		//---------------------------------------------------------------------
		case CMDID_NODE_GET_STATION_INFO:
            // NODE_GET_STATION_INFO Packet Format:
			//   - cmdArgs32[0]   - buffer id
			//   - cmdArgs32[1]   - flags
            //   - cmdArgs32[2]   - start_address of transfer
			//   - cmdArgs32[3]   - size of transfer (in bytes)
			//   - cmdArgs32[4:5] - MAC Address (All 0xFF means all entries)
			//
			// Always returns a valid WARPNet Buffer (either 1 or more packets)
            //   - buffer_id       - uint32  - buffer_id
			//   - flags           - uint32  - 0
			//   - bytes_remaining - uint32  - Number of bytes remaining in the transfer
			//   - start_byte      - uint32  - Byte index of the first byte in this packet
			//   - size            - uint32  - Number of payload bytes in this packet
			//   - byte[]          - uint8[] - Array of payload bytes

			respSent = node_process_buffer_cmds(cmdHdr, cmdArgs32, respHdr, respArgs32, pktSrc, eth_dev_num, max_words,
                                                print_type_node, "station info",
                                                get_station_info_list(),
					                            sizeof(station_info_entry),
					                            &wlan_exp_get_id_in_associated_stations,
					                            &find_station_info_entry,
					                            &copy_station_info_to_dest_entry,
					                            &zero_station_info_entry);
		break;


		//---------------------------------------------------------------------
		case CMDID_NODE_GET_BSS_INFO:
            // NODE_GET_BSS_INFO Packet Format:
			//   - cmdArgs32[0]   - buffer id
			//   - cmdArgs32[1]   - flags
            //   - cmdArgs32[2]   - start_address of transfer
			//   - cmdArgs32[3]   - size of transfer (in bytes)
			//   - cmdArgs32[4:5] - MAC Address (All 0xFF means all entries)
			//
			// Always returns a valid WARPNet Buffer (either 1 or more packets)
            //   - buffer_id       - uint32  - buffer_id
			//   - flags           - uint32  - 0
			//   - bytes_remaining - uint32  - Number of bytes remaining in the transfer
			//   - start_byte      - uint32  - Byte index of the first byte in this packet
			//   - size            - uint32  - Number of payload bytes in this packet
			//   - byte[]          - uint8[] - Array of payload bytes

			// If MAC address is all zeros, then return my_bss_info
			if ((cmdArgs32[4] == 0x0) && (cmdArgs32[5] == 0x0)) {
				if (my_bss_info != NULL) {
					// Replace MAC address of command with my_bss_info BSSID
					wlan_exp_put_mac_addr(my_bss_info->bssid, &cmdArgs32[4]);
				} else {
					wlan_exp_printf(WLAN_EXP_PRINT_WARNING, print_type_node, "my_bss_info was NULL\n");
					wlan_exp_put_mac_addr(get_wlan_mac_addr(), &cmdArgs32[4]);
				}
			}

			respSent = node_process_buffer_cmds(cmdHdr, cmdArgs32, respHdr, respArgs32, pktSrc, eth_dev_num, max_words,
					                            print_type_node, "bss info",
					                            wlan_mac_high_get_bss_info_list(),
					                            sizeof(bss_info_entry),
					                            &wlan_exp_get_id_in_bss_info,
					                            &wlan_mac_high_find_bss_info_BSSID,
					                            &copy_bss_info_to_dest_entry,
					                            &zero_bss_info_entry);
		break;


//-----------------------------------------------------------------------------
// Queue Commands
//-----------------------------------------------------------------------------


		//---------------------------------------------------------------------
		case CMDID_QUEUE_TX_DATA_PURGE_ALL:
			wlan_exp_purge_all_data_tx_queue_callback();
		break;


//-----------------------------------------------------------------------------
// Memory Access Commands - For developer use only
//-----------------------------------------------------------------------------


	    //---------------------------------------------------------------------
		case CMDID_DEV_MEM_HIGH:
			// Read/write memory in CPU High
			//
			// Write Message format:
			//     cmdArgs32[0]   Command==CMD_PARAM_WRITE_VAL
			//     cmdArgs32[1]   address
			//     cmdArgs32[2]   length (number of u32 words to write)
			//     cmdArgs32[3:]   values to write (integral number of u32 words)
			// Response format:
			//	   respArgs32[0]  Status
            //
			// Read Message format:
			//     cmdArgs32[0]   Command==NODE_READ_VAL
			//     cmdArgs32[1]   address
			//     cmdArgs32[2]   length (number of u32 words to read)
			// Response format:
			//	   respArgs32[0]  Status
			//	   respArgs32[1]  Length (number of u32 values)
			//     respArgs32[2:]  Memory values (length u32 values)
			//
			msg_cmd    = Xil_Ntohl(cmdArgs32[0]);
			mem_addr   = Xil_Ntohl(cmdArgs32[1]);
			mem_length = Xil_Ntohl(cmdArgs32[2]);
			status     = CMD_PARAM_SUCCESS;
			temp       = 0;

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Write CPU High Mem\n");
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "  Addr: 0x%08x\n", mem_addr);
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "  Len:  %d\n", mem_length);

					// Don't bother if length is clearly bogus
					if(mem_length < max_words) {
						for(mem_idx = 0; mem_idx < mem_length; mem_idx++) {
							wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "  W[%2d]: 0x%08x\n", mem_idx, Xil_Ntohl(cmdArgs32[3 + mem_idx]));
							Xil_Out32((mem_addr + mem_idx*sizeof(u32)), Xil_Ntohl(cmdArgs32[3 + mem_idx]));
						}
					} else {
						wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "CMDID_DEV_MEM_HIGH write longer than 1400 bytes\n");
						status = CMD_PARAM_ERROR;
					}
				break;

				case CMD_PARAM_READ_VAL:
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Read CPU High Mem:\n");
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "  Addr: 0x%08x\n", mem_addr);
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "  Len:  %d\n", mem_length);

					// Add payload to response
					if(mem_length < max_words) {

						// Don't set the default response
						temp = 1;

						// Add length argument to response
			            respArgs32[respIndex++] = Xil_Htonl( status );
			            respArgs32[respIndex++] = Xil_Htonl( mem_length );
						respHdr->length += (respIndex * sizeof(respArgs32));
						respHdr->numArgs = respIndex;

						for(mem_idx = 0; mem_idx < mem_length; mem_idx++) {
							respArgs32[respIndex + mem_idx] = Xil_Ntohl(Xil_In32((void*)(mem_addr) + mem_idx*sizeof(u32)));
						}

						// Update response header with payload length
						respHdr->length += (mem_length * sizeof(u32));
						respHdr->numArgs += mem_length;
					} else {
						wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "CMDID_DEV_MEM_HIGH read longer than 1400 bytes\n");
					    status = CMD_PARAM_ERROR;
					}
				break;

				default:
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
					status = CMD_PARAM_ERROR;
				break;
			}

			if (temp == 0) {
				// Send default response
	            respArgs32[respIndex++] = Xil_Htonl( status );
				respHdr->length += (respIndex * sizeof(respArgs32));
				respHdr->numArgs = respIndex;
			}
		break;


	    //---------------------------------------------------------------------
		case CMDID_DEV_MEM_LOW:
			// Read/write memory in CPU Low via IPC message
			//
			// Write Message format:
			//     cmdArgs32[0]   Command==NODE_WRITE_VAL
			//     cmdArgs32[1]   address
			//     cmdArgs32[2]   length (number of u32 words to write)
			//     cmdArgs32[3:]   values to write (integral number of u32 words)
			// Response format:
			//	   respArgs32[0]  Status
            //
			// Read Message format:
			//     cmdArgs32[0]   Command==NODE_READ_VAL
			//     cmdArgs32[1]   address
			//     cmdArgs32[2]   length (number of u32 words to read)
			// Response format:
			//	   respArgs32[0]  Status
			//	   respArgs32[1]  Length (number of u32 values)
			//     respArgs32[2:]  Memory values (length u32 values)
			//
			msg_cmd    = Xil_Ntohl(cmdArgs32[0]);
			mem_addr   = Xil_Ntohl(cmdArgs32[1]);
			mem_length = Xil_Ntohl(cmdArgs32[2]);
			status     = CMD_PARAM_SUCCESS;
			temp       = 0;

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Write CPU Low Mem:\n");
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "  Addr: 0x%08x\n", mem_addr);
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "  Len:  %d\n", mem_length);

					// Don't bother if length is clearly bogus
					if(mem_length < max_words) {
						// Endian swap payload here - CPU Low requires payload that is ready to use as-is
						for(mem_idx = 0; mem_idx < mem_length+2; mem_idx++) {
							cmdArgs32[1 + mem_idx] = Xil_Ntohl(cmdArgs32[1 + mem_idx]);
						}

						temp2 = wlan_mac_high_write_low_mem(mem_length + 2, &(cmdArgs32[1]));

						if (temp2 == -1) {
							wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "CMDID_DEV_MEM_LOW write failed\n");
							status = CMD_PARAM_ERROR;
						}
					} else {
						wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "CMDID_DEV_MEM_LOW write longer than 1400 bytes\n");
						status = CMD_PARAM_ERROR;
					}
				break;

				case CMD_PARAM_READ_VAL:
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Read CPU Low Mem:\n");
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "  Addr: 0x%08x\n", mem_addr);
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "  Len:  %d\n", mem_length);

					if(mem_length < max_words) {
						temp2 = wlan_mac_high_read_low_mem(mem_length, mem_addr, &(respArgs32[2]));

						if(temp2 == 0) { //Success
							// Don't set the default response
							temp = 1;

							// Add length argument to response
				            respArgs32[respIndex++] = Xil_Htonl( status );
				            respArgs32[respIndex++] = Xil_Htonl( mem_length );
							respHdr->length += (respIndex * sizeof(respArgs32));
							respHdr->numArgs = respIndex;

							// Endian swap payload returned by CPU Low
							for(mem_idx = 0; mem_idx < mem_length; mem_idx++) {
								respArgs32[2 + mem_idx] = Xil_Htonl(respArgs32[2 + mem_idx]);
							}

							respHdr->length += (mem_length * sizeof(u32));
							respHdr->numArgs += mem_length;

						} else { //failed
							wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "CMDID_DEV_MEM_LOW read failed\n");
							status = CMD_PARAM_ERROR;
						}
					} else {
						wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "CMDID_DEV_MEM_LOW read longer than 1400 bytes\n");
					    status = CMD_PARAM_ERROR;
					}
				break;

				default:
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
					status = CMD_PARAM_ERROR;
				break;
			}

			if (temp == 0) {
				// Send default response
	            respArgs32[respIndex++] = Xil_Htonl( status );
				respHdr->length += (respIndex * sizeof(respArgs32));
				respHdr->numArgs = respIndex;
			}
		break;


//-----------------------------------------------------------------------------
// Child Commands
//-----------------------------------------------------------------------------


		//---------------------------------------------------------------------
		default:
			// Call standard function in child class to parse parameters implmented there
			respSent = wlan_exp_process_callback( cmdID, cmdHdr, cmdArgs, respHdr, respArgs, pktSrc, eth_dev_num);
		break;
	}

	return respSent;
}




/*****************************************************************************/
/**
* This method will process buffer commands and return a valid WARPNet buffer
* with the requested information.
*
* Terminology:
*    "source" - the data to be transferred.
*    "dest"   - log entry type (from wlan_mac_entries.h) that corresponds to the info
*    "entry"  - dl_list term meaning an element of the list
*
* @param    None.
*
* @return   NO_RESP_SENT
*           RESP_SENT
*
******************************************************************************/
u32 node_process_buffer_cmds(const wn_cmdHdr* cmdHdr, u32 * cmdArgs32, wn_respHdr * respHdr, u32 * respArgs32, void* pktSrc, u32 eth_dev_num, u32 max_words,
	                         char * type, char * description, dl_list * source_list, u32 dest_size,
	                         u32 (*find_id)(u8 *),
	                         dl_entry * (*find_source_entry)(u8 *),
                             void (*copy_source_to_dest)(void *, void *, u64),
                             void (*zero_dest)(void *)) {

	u32           respIndex  = 5;                // There will always be 5 return args
	u32           respSent   = NO_RESP_SENT;

	u32           i, j;

    u32           id;
	u64           time;
	u8            mac_addr[6];

	u32           size;
	u32           transfer_size;
	u32           curr_index;
	u32           next_index;
	u32           num_pkts;
	u32           bytes_per_pkt;
	u32           bytes_remaining;

	u32           total_entries;
	u32           entry_remaining;
	u32           transfer_entry_num;
	u32           entry_per_pkt;

	dl_entry	* curr_entry;
    void        * curr_dest;

	// Get MAC Address
	wlan_exp_get_mac_addr(&((u32 *)cmdArgs32)[4], &mac_addr[0]);
	id = find_id(&mac_addr[0]);

    // Initialize return values
    respArgs32[0] = cmdArgs32[0];
    respArgs32[1] = cmdArgs32[1];
	respArgs32[2] = 0;
	respArgs32[3] = 0;
	respArgs32[4] = 0;

    if ( id == WLAN_EXP_AID_NONE ) {
    	if ((Xil_Ntohl(cmdArgs32[1]) & CMD_PARAM_STATS_RETURN_ZEROED_IF_NONE) == CMD_PARAM_STATS_RETURN_ZEROED_IF_NONE) {

    		// Copy routine will fill in a zeroed entry if the source is NULL
			copy_source_to_dest(NULL, &respArgs32[respIndex], get_usec_timestamp());

			wlan_exp_printf(WLAN_EXP_PRINT_INFO, type, "Returning zeroed %s entry for node: ", description);
			wlan_exp_print_mac_address(WLAN_EXP_PRINT_INFO, &mac_addr[0]); wlan_exp_printf(WLAN_EXP_PRINT_INFO, NULL, "\n");

			// Set the return args and increment the size
			respArgs32[2]    = Xil_Htonl( dest_size );
			respArgs32[3]    = 0;
			respArgs32[4]    = Xil_Htonl( dest_size );
			respHdr->length += dest_size;
    	} else {
    		// If we cannot find the MAC address, return an empty buffer
    		wlan_exp_printf(WLAN_EXP_PRINT_INFO, type, "Could not find %s for specified node: ", description);
			wlan_exp_print_mac_address(WLAN_EXP_PRINT_INFO, &mac_addr[0]); wlan_exp_printf(WLAN_EXP_PRINT_INFO, NULL, "\n");
    	}
    } else {
		// If parameter is not the magic number to return all structures
		if ( id != WLAN_EXP_AID_ALL ) {
			// Find the source information entry
			curr_entry = find_source_entry(&mac_addr[0]);

			if (curr_entry != NULL) {
				// Copy the info to the log entry
				//   NOTE:  This assumes that the info entry in wlan_mac_entries.h has a contiguous piece of memory
				//          similar to the info structures in wlan_mac_high.h
				copy_source_to_dest(curr_entry->data, &respArgs32[respIndex], get_usec_timestamp());

				wlan_exp_printf(WLAN_EXP_PRINT_INFO, type, "Get %s entry for node: ", description);
				wlan_exp_print_mac_address(WLAN_EXP_PRINT_INFO, &mac_addr[0]); wlan_exp_printf(WLAN_EXP_PRINT_INFO, NULL, "\n");

				// Set the return args and increment the size
				respArgs32[2]    = Xil_Htonl( dest_size );
				respArgs32[3]    = 0;
				respArgs32[4]    = Xil_Htonl( dest_size );
				respHdr->length += dest_size;
			} else {
				// If we cannot find the MAC address, print a warning and return an empty buffer
				wlan_exp_printf(WLAN_EXP_PRINT_INFO, type, "Could not find %s for specified node: ", description);
				wlan_exp_print_mac_address(WLAN_EXP_PRINT_INFO, &mac_addr[0]); wlan_exp_printf(WLAN_EXP_PRINT_INFO, NULL, "\n");
			}
		} else {
			// Create a WARPNet buffer response to send all entries
			if(source_list != NULL){
				total_entries  = source_list->length;
			} else {
				total_entries  = 0;
			}

			size      = dest_size * total_entries;

			wlan_exp_printf(WLAN_EXP_PRINT_INFO, type, "Getting %d entries (%d bytes)\n", total_entries, size);

			if ( size != 0 ) {
				// Send the entries as a series of WARPNet Buffers

				// Set loop variables
				entry_per_pkt     = (max_words * 4) / dest_size;
				bytes_per_pkt     = entry_per_pkt * dest_size;
				num_pkts          = size / bytes_per_pkt + 1;
				if ( (size % bytes_per_pkt) == 0 ){ num_pkts--; }    // Subtract the extra pkt if the division had no remainder

				entry_remaining   = total_entries;
				bytes_remaining   = size;
				curr_index        = 0;
				curr_entry        = source_list->first;
				time              = get_usec_timestamp();

				// Iterate through all the packets
				for( i = 0; i < num_pkts; i++ ) {

					// Get the next index
					next_index  = curr_index + bytes_per_pkt;

					// Compute the transfer size (use the full buffer unless you run out of space)
					if( next_index > size ) {
						transfer_size = size - curr_index;
					} else {
						transfer_size = bytes_per_pkt;
					}

					if( entry_remaining < entry_per_pkt) {
						transfer_entry_num = entry_remaining;
					} else {
						transfer_entry_num = entry_per_pkt;
					}

					// Set response args that change per packet
					respArgs32[2]    = Xil_Htonl( bytes_remaining );
					respArgs32[3]    = Xil_Htonl( curr_index );
					respArgs32[4]    = Xil_Htonl( transfer_size );

					// Unfortunately, due to the byte swapping that occurs in node_sendEarlyResp, we need to set all
					//   three command parameters for each packet that is sent.
					respHdr->cmd     = cmdHdr->cmd;
					respHdr->length  = 20 + transfer_size;
					respHdr->numArgs = 5;

					// Transfer data
					curr_dest = (void *) &respArgs32[respIndex];

					for( j = 0; j < transfer_entry_num; j++ ){
						// Since this method is interruptable, we need to protect ourselves from list elements being
						// removed (we will not handle the case that list elements are added and just ignore the new
						// elements).
						if (curr_entry != NULL) {
							// Copy the info to the log entry
							//   NOTE:  This assumes that the info entry in wlan_mac_entries.h has a contiguous piece of memory
							//          similar to the info structures in wlan_mac_high.h
							copy_source_to_dest(curr_entry->data, curr_dest, time);

							// Increment the station info pointers
							curr_entry = dl_entry_next(curr_entry);
						} else {
							// Instead of transferring the information, zero out the destination
							//   NOTE:  The destination will still potentially have a timestamp
                            zero_dest(curr_dest);

							// Do not do anything to the station info pointers since we are already at the end of the list
						}

						// Increment the ethernet packet pointer
						curr_dest = (void *)(((void *)curr_dest) + dest_size);
					}

					// Send the packet
					node_sendEarlyResp(respHdr, pktSrc, eth_dev_num);

					// Update our current address and bytes remaining
					curr_index       = next_index;
					bytes_remaining -= transfer_size;
					entry_remaining -= entry_per_pkt;
				}

				respSent = RESP_SENT;
			}
		}
    }

	// Set the length and number of response args
	respHdr->length += (5 * sizeof(respArgs32));
	respHdr->numArgs = respIndex;

	return respSent;
}



/*****************************************************************************/
/**
* These methods are helper functions for node_process_buffer_cmds
*
* For each type of structure to be transferred using a WARPNet buffer, you need to
* implement the following commands:
*     dl_entry * find_*_entry(u8 * mac_addr)
*     zero_*_entry(void * dest);
*     copy_*_to_dest_entry(void * source, void * dest, u64 time);
*
* @param    See description
*
* @return   None.
*
******************************************************************************/
dl_entry * find_station_info_entry(u8 * mac_addr) {
    dl_list * source_list = get_station_info_list();

	if( source_list != NULL){
		return wlan_mac_high_find_station_info_ADDR(source_list, mac_addr);
	} else {
		return NULL;
	}
}


void zero_station_info_entry(void * dest) {

	station_info_entry * curr_entry = (station_info_entry *)(dest);

	bzero((void *)(&curr_entry->info), sizeof(station_info_base));
}



void copy_station_info_to_dest_entry(void * source, void * dest, u64 time) {

	station_info       * curr_source = (station_info *)(source);
	station_info_entry * curr_dest   = (station_info_entry *)(dest);

	// Set the timestamp for the station_info entry
	curr_dest->timestamp = time;

	// Fill in zeroed entry if source is NULL
	if (source == NULL) {
		curr_source = wlan_mac_high_malloc(sizeof(station_info));

		if (curr_source != NULL) {
			bzero(curr_source, sizeof(station_info));
		}
	}

	// Copy the source information to the destination log entry
	//   NOTE:  This assumes that the destination log entry in wlan_mac_entries.h has a contiguous piece of memory
	//          similar to the source information structure in wlan_mac_high.h
	if (curr_source != NULL) {
		memcpy( (void *)(&curr_dest->info), (void *)(curr_source), sizeof(station_info_base) );
	} else {
		wlan_exp_printf(WLAN_EXP_PRINT_WARNING, print_type_node, "Could not copy station_info to entry\n");
	}

	// Free curr_source if source was NULL
	if (source == NULL) {
		wlan_mac_high_free(curr_source);
	}
}


dl_entry * find_statistics_txrx_entry(u8 * mac_addr) {
    dl_list * source_list = get_statistics();

	if( source_list != NULL){
		return wlan_mac_high_find_statistics_ADDR(source_list, mac_addr);
	} else {
		return NULL;
	}
}


void zero_txrx_stats_entry(void * dest) {

	txrx_stats_entry * curr_entry = (txrx_stats_entry *)(dest);

	bzero((void *)(&curr_entry->stats), sizeof(statistics_txrx_base));
}



void copy_statistics_txrx_to_dest_entry(void * source, void * dest, u64 time) {

	statistics_txrx    * curr_source   = (statistics_txrx *)(source);
	txrx_stats_entry   * curr_dest     = (txrx_stats_entry *)(dest);

	// Set the timestamp for the station_info entry
	curr_dest->timestamp = time;

	// Fill in zeroed entry if source is NULL
	//   - All fields are zero except last_txrx_timestamp which is CMD_PARAM_NODE_TIME_RSVD_VAL_64
	if (source == NULL) {
		curr_source = wlan_mac_high_malloc(sizeof(statistics_txrx));

		if (curr_source != NULL) {
			bzero(curr_source, sizeof(statistics_txrx));

			curr_source->latest_txrx_timestamp = CMD_PARAM_NODE_TIME_RSVD_VAL_64;
		}
	}

	// Copy the source information to the destination log entry
	//   NOTE:  This assumes that the destination log entry in wlan_mac_entries.h has a contiguous piece of memory
	//          similar to the source information structure in wlan_mac_high.h
	if (curr_source != NULL) {
		memcpy( (void *)(&curr_dest->stats), (void *)(curr_source), sizeof(statistics_txrx_base) );
	} else {
		wlan_exp_printf(WLAN_EXP_PRINT_WARNING, "STATS", "Could not copy statistics_txrx to entry\n");
	}

	// Free curr_source if source was NULL
	if (source == NULL) {
		wlan_mac_high_free(curr_source);
	}
}


void zero_bss_info_entry(void * dest) {

	bss_info_entry * curr_entry = (bss_info_entry *)(dest);

	bzero((void *)(&curr_entry->info), sizeof(bss_info_base));
}



void copy_bss_info_to_dest_entry(void * source, void * dest, u64 time) {

	bss_info           * curr_source = (bss_info *)(source);
	bss_info_entry     * curr_dest   = (bss_info_entry *)(dest);

	// Set the timestamp for the station_info entry
	curr_dest->timestamp = time;

	// Fill in zeroed entry if source is NULL
	if (source == NULL) {
		curr_source = wlan_mac_high_malloc(sizeof(bss_info));

		if (curr_source != NULL) {
			bzero(curr_source, sizeof(bss_info));
		}
	}

	// Copy the source information to the destination log entry
	//   NOTE:  This assumes that the destination log entry in wlan_mac_entries.h has a contiguous piece of memory
	//          similar to the source information structure in wlan_mac_high.h
	if (curr_source != NULL) {
		memcpy( (void *)(&curr_dest->info), (void *)(curr_source), sizeof(bss_info_base) );
	} else {
		wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Could not copy bss_info to entry\n");
	}

	// Free curr_source if source was NULL
	if (source == NULL) {
		wlan_mac_high_free(curr_source);
	}
}




/*****************************************************************************/
/**
* This will initialize the WARPNet WLAN_EXP node with the appropriate information
* and set up the node to communicate with WARPNet on the given ethernet device. 
*
* @param    None.
*
* @return	 0 - Success
*           -1 - Failure
*
* @note		This function will print to the terminal but is not able to control any of the LEDs
*
******************************************************************************/
int wlan_exp_node_init(u32 type, u32 serial_number, u32 *fpga_dna, u32 eth_dev_num, u8 *hw_addr, u8 *wlan_hw_addr) {

    int i;
	int status = SUCCESS;
	xil_printf("------------------------\n");
	xil_printf("WARPNet v%d.%d.%d WLAN EXP v%d.%d.%d (compiled %s %s)\n", WARPNET_VER_MAJOR, WARPNET_VER_MINOR, WARPNET_VER_REV,
			   WLAN_EXP_VER_MAJOR, WLAN_EXP_VER_MINOR, WLAN_EXP_VER_REV, __DATE__, __TIME__);

	// Initialize Global variables
	//   Node must be configured using the WARPNet nodesConfig
	//   HW must be WARP v3
	//   IP Address should be NODE_IP_ADDR_BASE
    node_info.type                = type;
    node_info.node                = 0xFFFF;
    node_info.serial_number       = serial_number;
    node_info.hw_generation       = WARP_HW_VERSION;
    node_info.warpnet_design_ver  = REQ_WARPNET_HW_VER;
    
    for( i = 0; i < FPGA_DNA_LEN; i++ ) {
        node_info.fpga_dna[i]     = fpga_dna[i];
    }

    // By default, enable all subtype logging
    wlan_exp_log_set_entry_en_mask( ENTRY_EN_MASK_TXRX_CTRL|ENTRY_EN_MASK_TXRX_MPDU );

    // WLAN Exp Parameters are assumed to be initialize already
    //    node_info.wlan_hw_addr

    node_info.wlan_exp_design_ver       = REQ_WLAN_EXP_HW_VER;
    node_info.wlan_scheduler_resolution = FAST_TIMER_DUR_US;
    

    // Initialize other HW parameters not part of the node_info log entry
    node_info.eth_device      = eth_dev_num;
    
	node_info.ip_addr[0]      = (NODE_IP_ADDR_BASE >> 24) & 0xFF;
	node_info.ip_addr[1]      = (NODE_IP_ADDR_BASE >> 16) & 0xFF;
	node_info.ip_addr[2]      = (NODE_IP_ADDR_BASE >>  8) & 0xFF;
	node_info.ip_addr[3]      = (NODE_IP_ADDR_BASE      ) & 0xFF;  // IP ADDR = w.x.y.z
    
    for ( i = 0; i < ETH_ADDR_LEN; i++ ) {
        node_info.hw_addr[i]  = hw_addr[i];
    }
    
    node_info.unicast_port    = NODE_UDP_UNICAST_PORT_BASE;
    node_info.broadcast_port  = NODE_UDP_MCAST_BASE;

    node_info_set_wlan_hw_addr(wlan_hw_addr);

    // Initialize the System Monitor
    node_init_system_monitor();
    
    // Initialize Tag parameters
    node_init_parameters( (u32*)&node_info );
    

#ifdef _DEBUG_
    print_wn_node_info( &node_info );
    print_wn_parameters( (wn_tag_parameter *)&node_parameters, NODE_MAX_PARAMETER );
#endif


    // Initialize Global variables for async packet sending
    async_pkt_enable = 0;
    async_eth_dev_num = eth_dev_num;
    bzero((void *)&async_pkt_dest, sizeof(pktSrcInfo));
    bzero((void *)&async_pkt_hdr, sizeof(wn_transport_header));

    
    // Transport initialization
	//   NOTE:  These errors are fatal and status error will be displayed
	//       on the hex display.  Also, please attach a USB cable for
	//       terminal debug messages.
	status = transport_init(node_info.node, node_info.ip_addr, node_info.hw_addr, node_info.unicast_port, node_info.broadcast_port, node_info.eth_device);
	if(status != 0) {
        xil_printf("  Error in transport_init()! Exiting...\n");
        return FAILURE;
	}

#if WLAN_EXP_WAIT_FOR_ETH

	xil_printf("  Waiting for Ethernet link ... ");
	while( transport_linkStatus( eth_dev_num ) != 0 );
	xil_printf("  Initialization Successful\n");

#else

	xil_printf("  Not waiting for Ethernet link.  Current status is: ");

	if ( transport_linkStatus( eth_dev_num ) == LINK_READY ) {
		xil_printf("ready.\n");
	} else {
		xil_printf("not ready.\n");
		xil_printf("    Make sure link is ready before using WARPNet.\n");
	}

#endif

	//Assign the new packet callback
	// IMPORTANT: must be called after transport_init()
	transport_setReceiveCallback( (void *)node_rxFromTransport );

	// Call child init function
	status = wlan_exp_init_callback( type, serial_number, fpga_dna, eth_dev_num, hw_addr );

	xil_printf("End WARPNet WLAN Exp initialization\n");
	return status;
}



/*****************************************************************************/
/**
* Set the WLAN Exp callbacks
*
* @param    Pointer to the callback
*
* @return	None.
*
* @note     None.
*
******************************************************************************/
void wlan_exp_reset_all_callbacks(){
	wlan_exp_init_callback                     = (wn_function_ptr_t)wlan_exp_null_init_callback;
	wlan_exp_process_callback                  = (wn_function_ptr_t)wlan_exp_null_process_callback;
	wlan_exp_reset_station_statistics_callback = (wn_function_ptr_t)wlan_exp_null_callback;
	wlan_exp_purge_all_data_tx_queue_callback  = (wn_function_ptr_t)wlan_exp_null_callback;
	wlan_exp_reset_all_associations_callback   = (wn_function_ptr_t)wlan_exp_null_callback;
	wlan_exp_reset_bss_info_callback           = (wn_function_ptr_t)wlan_exp_null_callback;
	wlan_exp_adjust_timebase_callback          = (wn_function_ptr_t)wlan_exp_null_callback;
	wlan_exp_tx_cmd_add_association_callback   = (wn_function_ptr_t)wlan_exp_null_callback;
}


void wlan_exp_set_init_callback(void(*callback)()){
	wlan_exp_init_callback = (wn_function_ptr_t)callback;
}


void wlan_exp_set_process_callback(void(*callback)()){
	wlan_exp_process_callback = (wn_function_ptr_t)callback;
}


void wlan_exp_set_reset_station_statistics_callback(void(*callback)()){
	wlan_exp_reset_station_statistics_callback = (wn_function_ptr_t)callback;
}


void wlan_exp_set_purge_all_data_tx_queue_callback(void(*callback)()){
	wlan_exp_purge_all_data_tx_queue_callback = (wn_function_ptr_t)callback;
}


void wlan_exp_set_reset_all_associations_callback(void(*callback)()){
	wlan_exp_reset_all_associations_callback = (wn_function_ptr_t)callback;
}


void wlan_exp_set_reset_bss_info_callback(void(*callback)()){
	wlan_exp_reset_bss_info_callback = (wn_function_ptr_t)callback;
}

void wlan_exp_set_timebase_adjust_callback(void(*callback)()){
	wlan_exp_adjust_timebase_callback = (wn_function_ptr_t)callback;
}

void wlan_exp_set_tx_cmd_add_association_callback(void(*callback)()){
	wlan_exp_tx_cmd_add_association_callback = (wn_function_ptr_t)callback;
}



/*****************************************************************************/
/**
* Initialize the System Monitor if it exists
*
* @param    None
*
* @return	None
*
* @note     None
*
******************************************************************************/
void node_init_system_monitor(void) {

#ifdef XPAR_XSYSMON_NUM_INSTANCES
	u32 RegValue;

    // Reset the system monitor
    XSysMon_WriteReg(SYSMON_BASEADDR, XSM_SRR_OFFSET, XSM_SRR_IPRST_MASK);

    // Disable the Channel Sequencer before configuring the Sequence registers.
    RegValue = XSysMon_ReadReg(SYSMON_BASEADDR, XSM_CFR1_OFFSET) & (~ XSM_CFR1_SEQ_VALID_MASK);
    XSysMon_WriteReg(SYSMON_BASEADDR, XSM_CFR1_OFFSET,	RegValue | XSM_CFR1_SEQ_SINGCHAN_MASK);

    // Setup the Averaging to be done for the channels in the Configuration 0
    //   register as 16 samples:
    RegValue = XSysMon_ReadReg(SYSMON_BASEADDR, XSM_CFR0_OFFSET) & (~XSM_CFR0_AVG_VALID_MASK);
    XSysMon_WriteReg(SYSMON_BASEADDR, XSM_CFR0_OFFSET, RegValue | XSM_CFR0_AVG16_MASK);

    // Enable the averaging on the following channels in the Sequencer registers:
    //  - On-chip Temperature
    //  - On-chip VCCAUX supply sensor
    XSysMon_WriteReg(SYSMON_BASEADDR,XSM_SEQ02_OFFSET, XSM_SEQ_CH_TEMP | XSM_SEQ_CH_VCCAUX);

    // Enable the following channels in the Sequencer registers:
    //  - On-chip Temperature
    //  - On-chip VCCAUX supply sensor
    XSysMon_WriteReg(SYSMON_BASEADDR, XSM_SEQ00_OFFSET, XSM_SEQ_CH_TEMP | XSM_SEQ_CH_VCCAUX);

    // Set the ADCCLK frequency equal to 1/32 of System clock for the System Monitor/ADC
    //   in the Configuration Register 2.
    XSysMon_WriteReg(SYSMON_BASEADDR, XSM_CFR2_OFFSET, 32 << XSM_CFR2_CD_SHIFT);

    // Enable the Channel Sequencer in continuous sequencer cycling mode.
    RegValue = XSysMon_ReadReg(SYSMON_BASEADDR, XSM_CFR1_OFFSET) & (~ XSM_CFR1_SEQ_VALID_MASK);
    XSysMon_WriteReg(SYSMON_BASEADDR, XSM_CFR1_OFFSET,	RegValue | XSM_CFR1_SEQ_CONTINPASS_MASK);

    // Wait till the End of Sequence occurs
    XSysMon_ReadReg(SYSMON_BASEADDR, XSM_SR_OFFSET); /* Clear the old status */
    while (((XSysMon_ReadReg(SYSMON_BASEADDR, XSM_SR_OFFSET)) & XSM_SR_EOS_MASK) != XSM_SR_EOS_MASK);

    // TODO:  Do we need a timeout for this while loop?

#endif

}



/*****************************************************************************/
/**
* Initialize the TAG parameters structure
*
* @param    Pointer to info structure from which to pull all the tag parameter values
*
* @return	Total number of bytes of the TAG parameter structure
*
* @note     Please make sure that the *_info structure and the parameter values
*           maintain the same order
*
******************************************************************************/
int node_init_parameters( u32 *info ) {

	int              i;
	int              length;
	int              size;
	wn_tag_parameter temp_param;

    unsigned int       num_params = NODE_MAX_PARAMETER;
    wn_tag_parameter * parameters = (wn_tag_parameter *)&node_parameters;

	// Initialize variables
	length = 0;
	size   = sizeof(wn_tag_parameter);

    for( i = 0; i < num_params; i++ ) {

    	// Set reserved space to 0xFF
    	temp_param.reserved = 0xFF;

    	// Common parameter settings
    	temp_param.group    = NODE_GRP;
    	temp_param.command  = i;

    	// Any parameter specific code
    	switch ( i ) {
            case NODE_FPGA_DNA:
            case NODE_WLAN_MAC_ADDR:
    		    temp_param.length = 2;
    		break;

            default:
            	temp_param.length = 1;
    	    break;
    	}

    	// Set pointer to parameter values in info structure
        temp_param.value = &info[length];

        // Increment length so that we get the correct index in to info structure
        length += temp_param.length;

        // Copy the temp parameter to the tag parameter array
        memcpy( &parameters[i], &temp_param, size );
    }

    return ( ( size * i ) + ( length * 4 ) ) ;
}



/*****************************************************************************/
/**
*
* This function will populate a buffer with tag parameter information
*
* @param    eth_dev_num is an int that specifies the Ethernet interface to use
*           buffer is a u32 pointer to store the tag parameter information
*           max_words is a integer to specify the max number of u32 words in the buffer
*
* @return	number_of_words is number of words used of the buffer for the tag
*             parameter information
*
* @note		The tag parameters must be initialized before this function will be
*       called.  The user can modify the file to add additional functionality
*       to the WARPNet Transport.
*
******************************************************************************/
int node_get_parameters(u32 * buffer, unsigned int max_words, u8 transmit) {

    int i, j;
    int num_total_words;
    int num_param_words;

    u32 length;
    u32 temp_word;

    // NOTE:  This code is mostly portable between WARPNet components.
    //        Please modify  if you are copying this function for other WARPNet extensions    
    unsigned int       num_params = NODE_MAX_PARAMETER;
    wn_tag_parameter * parameters = (wn_tag_parameter *) &node_parameters;
    
    
    // Initialize the total number of words used
    num_total_words = 0;
    
    // Iterate through all tag parameters
    for( i = 0; i < num_params; i++ ) {

        length = parameters[i].length;
    
        // The number of words in a tag parameter is the number of value words + 2 header words
        num_param_words = length + 2;
    
        // Make sure we have space in the buffer to put the parameter
        if ( ( num_total_words + num_param_words ) <= max_words ) {
    
            temp_word = ( ( parameters[i].reserved << 24 ) | 
                          ( parameters[i].group    << 16 ) |
                          ( length                       ) );
            
            if ( transmit == WN_TRANSMIT ) {

				buffer[num_total_words]     = Xil_Htonl( temp_word );
				buffer[num_total_words + 1] = Xil_Htonl( parameters[i].command );

				for( j = 0; j < length; j++ ) {
					buffer[num_total_words + 2 + j] = Xil_Htonl( parameters[i].value[j] );
				}

            } else {
            
				buffer[num_total_words]     = temp_word;
				buffer[num_total_words + 1] = parameters[i].command;

				for( j = 0; j < length; j++ ) {
					buffer[num_total_words + 2 + j] = parameters[i].value[j];
				}
            }

            num_total_words += num_param_words;
            
        } else {
            // Exit the loop because there is no more space
            break;
        }
    }
    
    return num_total_words;
}



/*****************************************************************************/
/**
* This function will populate a buffer with tag parameter values
*
* @param    buffer is a u32 pointer to store the tag parameter information
*           max_words is a integer to specify the max number of u32 words in the buffer
*
* @return	number_of_words is number of words used of the buffer for the tag
*             parameter information
*
* @note		The tag parameters must be initialized before this function will be
*       called.  The user can modify the file to add additional functionality
*       to the WARPNet Transport.
*
******************************************************************************/
int node_get_parameter_values(u32 * buffer, unsigned int max_words) {

    int i, j;
    int num_total_words;

    u32 length;

    // NOTE:  This code is mostly portable between WARPNet components.
    //        Please modify  if you are copying this function for other WARPNet extensions
    unsigned int       num_params = NODE_MAX_PARAMETER;
    wn_tag_parameter * parameters = (wn_tag_parameter *) &node_parameters;

    // Initialize the total number of words used
    num_total_words = 0;

    // Iterate through all tag parameters
    for( i = 0; i < num_params; i++ ) {

        length = parameters[i].length;

        // Make sure we have space in the buffer to put the parameter
        if ( ( num_total_words + length ) <= max_words ) {

			for( j = 0; j < length; j++ ) {
				buffer[num_total_words + j] = parameters[i].value[j];
			}

            num_total_words += length;

        } else {
            // Exit the loop because there is no more space
            break;
        }
    }

    return num_total_words;
}



/*****************************************************************************/
/**
* These are helper functions to set some node_info fields
*
* @param    field value
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void node_info_set_wlan_hw_addr  ( u8 * hw_addr  ) {
	// Note:  Doing processing this way so that when the structure is copied and parsed in the log
	//   we do not need to mangle the address.
    node_info.wlan_hw_addr[0] = (hw_addr[2]<<24) | (hw_addr[3]<<16) | (hw_addr[4]<<8) | hw_addr[5];
    node_info.wlan_hw_addr[1] = (hw_addr[0]<<8)  |  hw_addr[1];
}


/*****************************************************************************/
/**
* These are helper functions to get some fields
*
* @param    None.
*
* @return	field value
*
* @note		None.
*
******************************************************************************/
u32  wn_get_node_id       ( void ) { return node_info.node; }
u32  wn_get_serial_number ( void ) { return node_info.serial_number; }

#ifdef XPAR_XSYSMON_NUM_INSTANCES
u32  wn_get_curr_temp     ( void ) { return XSysMon_ReadReg(SYSMON_BASEADDR, XSM_TEMP_OFFSET);     }
u32  wn_get_min_temp      ( void ) { return XSysMon_ReadReg(SYSMON_BASEADDR, XSM_MIN_TEMP_OFFSET); }
u32  wn_get_max_temp      ( void ) { return XSysMon_ReadReg(SYSMON_BASEADDR, XSM_MAX_TEMP_OFFSET); }
#else
u32  wn_get_curr_temp     ( void ) { return 0; }
u32  wn_get_min_temp      ( void ) { return 0; }
u32  wn_get_max_temp      ( void ) { return 0; }
#endif

/*****************************************************************************/
/**
* This is a helper function to clean up the LTGs owned by WLAN Exp
*
* @param    id            - LTG id
*           callback_arg  - Callback argument for LTG
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void node_ltg_cleanup(u32 id, void* callback_arg){
	wlan_mac_high_free( callback_arg );
}



/*****************************************************************************/
/**
* WLAN Mapping of MAC Addr to ID
*
* This function contains the mapping of MAC address to ID within a node for
*   - associated stations
*   - statistics
*   - bss infos
*
* @param    MAC Address
*
* @return	ID associated with that MAC address
*
* @note		None.
*
******************************************************************************/
u32  wlan_exp_get_id_in_associated_stations(u8 * mac_addr) {
	u32            id;
	dl_entry*	   entry;
	station_info * info;

	if ( wlan_addr_eq(mac_addr, bcast_addr) ) {
		id = WLAN_EXP_AID_ALL;
	} else {
		if(my_bss_info != NULL){
			if ( wlan_addr_eq(mac_addr, my_bss_info->bssid) ) {
				id = WLAN_EXP_AID_ME;
			} else {
				entry = wlan_mac_high_find_station_info_ADDR(&(my_bss_info->associated_stations), mac_addr);

				if (entry != NULL) {
					info = (station_info*)(entry->data);
		            id = info->AID;
				} else {
					id = WLAN_EXP_AID_NONE;
				}
			}
		} else {
			id = WLAN_EXP_AID_NONE;
		}
	}

	return id;
}


u32  wlan_exp_get_id_in_statistics(u8 * mac_addr) {
	u32            id;
	dl_list*       stats;
	dl_entry*	   entry;

	if ( wlan_addr_eq(mac_addr, bcast_addr) ) {
		id = WLAN_EXP_AID_ALL;
	} else {
		stats = get_statistics();

		if(stats != NULL){
			entry = wlan_mac_high_find_statistics_ADDR(stats, mac_addr);

			if (entry != NULL) {
				id = WLAN_EXP_AID_DEFAULT;            // Only returns the default AID if found
			} else {
				id = WLAN_EXP_AID_NONE;
			}
		} else {
			id = WLAN_EXP_AID_NONE;
		}
	}

	return id;
}


u32  wlan_exp_get_id_in_bss_info(u8 * bssid) {
	u32            id;
	dl_entry*	   entry;

	if ( wlan_addr_eq(bssid, bcast_addr) ) {
		id = WLAN_EXP_AID_ALL;
	} else {
		entry = wlan_mac_high_find_bss_info_BSSID(bssid);

		if (entry != NULL) {
			id = WLAN_EXP_AID_DEFAULT;
		} else {
			id = WLAN_EXP_AID_NONE;
		}
	}

	return id;
}



/*****************************************************************************/
/**
* Create WN Command Log Entry
*
* This function creates a WN Command Log Entry
*
* @param    MAC Address
*
* @return	AID associated with that MAC address
*
* @note		None.
*
******************************************************************************/
void create_wn_cmd_log_entry(wn_cmdHdr* cmdHdr, void * cmdArgs, u16 src_id) {
    // Create a new log entry for each WARPNet command and copy up to the first 10 args
	//
	u32 i;
	wn_cmd_entry* entry      = (wn_cmd_entry *)wlan_exp_log_create_entry( ENTRY_TYPE_WN_CMD, sizeof(wn_cmd_entry) );
	u32         * cmdArgs32  = cmdArgs;
	u32           num_args   = (cmdHdr->numArgs > 10) ? 10 : cmdHdr->numArgs;

	if (entry != NULL) {
		entry->timestamp = get_usec_timestamp();
		entry->command   = cmdHdr->cmd;
		entry->src_id    = src_id;
		entry->num_args  = num_args;

		// Add arguments to the entry
		for (i = 0; i < num_args; i++) {
			(entry->args)[i] = Xil_Ntohl(cmdArgs32[i]);
		}
		// Zero out any other arguments in the entry
		for (i = num_args; i < 10; i++) {
			(entry->args)[i] = 0;
		}

#ifdef _DEBUG_
		print_entry( 0, ENTRY_TYPE_WN_CMD, (void *) entry );
#endif
	}
}



/*****************************************************************************/
/**
* Process TX Power
*
* @param    cmd      - NODE_WRITE_VAL or NODE_READ_VAL
*           aid      - AID of the station or NODE_CONFIG_ALL_ASSOCIATED
*           tx_power - Power to set the node (function assumes power is valid)
* @return	power    - CMD_PARAM_ERROR on ERROR
* @note		None.
*
******************************************************************************/
int node_process_tx_power(u32 cmd, u32 aid, int tx_power) {

	int           power;
	dl_list     * curr_list;
	dl_entry	* curr_entry;
	station_info* curr_station_info;

	power = CMD_PARAM_ERROR;

	// For Writes
	if ( cmd == CMD_PARAM_WRITE_VAL ) {
		curr_list  = get_station_info_list();

		if(curr_list != NULL){
			if (curr_list->length == 0) { return tx_power; }

			curr_entry = curr_list->first;

			while(curr_entry != NULL) {
				curr_station_info = (station_info*)(curr_entry->data);

				if ( aid == WLAN_EXP_AID_ALL ) {
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node,
							        "Set TX power on AID %d = %d dBm\n", curr_station_info->AID, tx_power);
					curr_station_info->tx.phy.power = tx_power;
					power                           = tx_power;

				} else if ( aid == curr_station_info->AID ) {
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node,
							        "Set TX power on AID %d = %d dBm\n", aid, tx_power);
					curr_station_info->tx.phy.power = tx_power;
					power                           = tx_power;
					break;
				}
				curr_entry = dl_entry_next(curr_entry);
			}
		} else {
			if (aid == WLAN_EXP_AID_ALL) {
				// This is not an error because we are trying to set the rate for all
				// associations and there currently are none.
				power = tx_power;
			}
		}

	// For Reads
	} else {
		if ( aid != WLAN_EXP_AID_ALL ) {
			curr_list  = get_station_info_list();

			if (curr_list != NULL){
				curr_entry = curr_list->first;

				while(curr_entry != NULL){
					curr_station_info = (station_info*)(curr_entry->data);
					if ( aid == curr_station_info->AID ) {
						power = curr_station_info->tx.phy.power;
						break;
					}
					curr_entry = dl_entry_next(curr_entry);
				}
			}
		}

		// NOTE:  Trying to read the rate for all associations returns an error.
	}

	return power;
}



/*****************************************************************************/
/**
* Process TX Rate
*
* @param    cmd      - NODE_WRITE_VAL or NODE_READ_VAL
*           aid      - AID of the station or NODE_CONFIG_ALL_ASSOCIATED
*           tx_rate  - Rate to set the node (function assumes rate is valid)
* @return	rate     - 0xFF on ERROR
* @note		None.
*
******************************************************************************/
u8 node_process_tx_rate(u32 cmd, u32 aid, u8 tx_rate) {

	u8            rate;
	dl_list     * curr_list;
	dl_entry	* curr_entry;
	station_info* curr_station_info;

	rate = CMD_PARAM_ERROR >> 24;

	// For Writes
	if ( cmd == CMD_PARAM_WRITE_VAL ) {
		curr_list  = get_station_info_list();

		if(curr_list != NULL){
			if (curr_list->length == 0) { return tx_rate; }

			curr_entry = curr_list->first;

			while(curr_entry != NULL) {
				curr_station_info = (station_info*)(curr_entry->data);

				if ( aid == WLAN_EXP_AID_ALL ) {
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node,
							        "Set TX rate on AID %d = %d Mbps\n", curr_station_info->AID, wlan_lib_mac_rate_to_mbps(tx_rate));
					curr_station_info->tx.phy.rate = tx_rate;
					rate                           = tx_rate;

				} else if ( aid == curr_station_info->AID ) {
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node,
							        "Set TX rate on AID %d = %d Mbps\n", aid, wlan_lib_mac_rate_to_mbps(tx_rate));
					curr_station_info->tx.phy.rate = tx_rate;
					rate                           = tx_rate;
					break;
				}
				curr_entry = dl_entry_next(curr_entry);
			}
		} else {
			if (aid == WLAN_EXP_AID_ALL) {
				// This is not an error because we are trying to set the rate for all
				// associations and there currently are none.
				rate = tx_rate;
			}
		}

	// For Reads
	} else {
		if ( aid != WLAN_EXP_AID_ALL ) {
			curr_list  = get_station_info_list();

			if (curr_list != NULL){
				curr_entry = curr_list->first;

				while(curr_entry != NULL){
					curr_station_info = (station_info*)(curr_entry->data);
					if ( aid == curr_station_info->AID ) {
						rate = curr_station_info->tx.phy.rate;
						break;
					}
					curr_entry = dl_entry_next(curr_entry);
				}
			}
		}

		// NOTE:  Trying to read the rate for all associations returns an error.
	}

	return rate;
}



/*****************************************************************************/
/**
* Process TX Antenna Mode
*
* @param    cmd      - NODE_WRITE_VAL or NODE_READ_VAL
*           aid      - AID of the station or NODE_CONFIG_ALL_ASSOCIATED
*           ant_mode - Antenna mode (function assumes antenna mode is valid)
* @return	mode     - 0xFF on ERROR
* @note		None.
*
******************************************************************************/
u8 node_process_tx_ant_mode(u32 cmd, u32 aid, u8 ant_mode) {

	u8            mode;
	dl_list     * curr_list;
	dl_entry	* curr_entry;
	station_info* curr_station_info;

	mode = CMD_PARAM_ERROR >> 24;

	// For Writes
	if ( cmd == CMD_PARAM_WRITE_VAL ) {
		curr_list  = get_station_info_list();

		if(curr_list != NULL){
			if (curr_list->length == 0) { return ant_mode; }

			curr_entry = curr_list->first;

			while(curr_entry != NULL) {
				curr_station_info = (station_info*)(curr_entry->data);

				if ( aid == WLAN_EXP_AID_ALL ) {
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node,
							        "Set TX ant mode on AID %d = %d \n", curr_station_info->AID, ant_mode);
					curr_station_info->tx.phy.antenna_mode = ant_mode;
					mode                                   = ant_mode;

				} else if ( aid == curr_station_info->AID ) {
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node,
							        "Set TX ant mode on AID %d = %d \n", curr_station_info->AID, ant_mode);
					curr_station_info->tx.phy.antenna_mode = ant_mode;
					mode                                   = ant_mode;
					break;
				}
				curr_entry = dl_entry_next(curr_entry);
			}
		} else {
			if (aid == WLAN_EXP_AID_ALL) {
				// This is not an error because we are trying to set the mode for all
				// associations and there currently are none.
				mode = ant_mode;
			}
		}

	// For Reads
	} else {
		if ( aid != WLAN_EXP_AID_ALL ) {
			curr_list  = get_station_info_list();

			if(curr_list != NULL){
				curr_entry = curr_list->first;

				while(curr_entry != NULL) {
					curr_station_info = (station_info*)(curr_entry->data);
					if ( aid == curr_station_info->AID ) {
						mode = curr_station_info->tx.phy.antenna_mode;
						break;
					}
					curr_entry = dl_entry_next(curr_entry);
				}
			}
		}

		// NOTE:  Trying to read the mode for all associations returns an error.
	}

	return mode;
}







#ifdef _DEBUG_

/*****************************************************************************/
/**
* Print Tag Parameters
*
* This function will print a list of wn_tag_parameter structures
*
* @param    param      - pointer to the wn_tag_parameter list
*           num_params - number of wn_tag_parameter structures in the list
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void print_wn_parameters( wn_tag_parameter *param, int num_params ) {

	int i, j;

	xil_printf("Node Parameters: \n");

    for( i = 0; i < num_params; i++ ){
    	xil_printf("  Parameter %d:\n", i);
    	xil_printf("    Group:            %d \n",   param[i].group);
    	xil_printf("    Length:           %d \n",   param[i].length);
    	xil_printf("    Command:          %d \n",   param[i].command);

    	for( j = 0; j < param[i].length; j++ ) {
    		xil_printf("    Value[%2d]:        0x%8x \n",   j, param[i].value[j]);
    	}
    }

    xil_printf("\n");
}



/*****************************************************************************/
/**
* Print Node Info
*
* This function will print a wn_node_info structure
*
* @param    info    - pointer to wn_node_info structure to print
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void print_wn_node_info( wn_node_info * info ) {
    int i;

	xil_printf("WARPNet Node Information: \n");
    xil_printf("  WARPNet Type:       0x%8x \n",   info->type);    
    xil_printf("  Node ID:            %d \n",      info->node);
    xil_printf("  HW Generation:      %d \n",      info->hw_generation);
    xil_printf("  WARPNet HW Ver:     0x%x \n",    info->warpnet_design_ver);
    
    xil_printf("  FPGA DNA:           ");
    
    for( i = 0; i < FPGA_DNA_LEN; i++ ) {
        xil_printf("0x%8x  ", info->fpga_dna[i]);
    }
	xil_printf("\n");

	xil_printf("  Serial Number:      0x%x \n",    info->serial_number);
    xil_printf("  WLAN Exp HW Ver:    0x%x \n",    info->wlan_exp_design_ver);
        
    xil_printf("  HW Address:         "); print_mac_address(&info->hw_addr[0]); xil_printf("\n");

    xil_printf("  IP Address 0:       %d",         info->ip_addr[0]);
    
    for( i = 1; i < IP_VERSION; i++ ) {
        xil_printf(".%d", info->ip_addr[i]);
    }
	xil_printf("\n");

    xil_printf("  Unicast Port:       %d \n",      info->unicast_port);
    xil_printf("  Broadcast Port:     %d \n",      info->broadcast_port);
	xil_printf("\n");
    
}

#endif


// End USE_WARPNET_WLAN_EXP
#endif
