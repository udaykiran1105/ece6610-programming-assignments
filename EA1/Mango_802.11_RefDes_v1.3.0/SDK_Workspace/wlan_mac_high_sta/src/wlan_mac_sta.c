/** @file wlan_mac_sta.c
 *  @brief Station
 *
 *  This contains code for the 802.11 Station.
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

//Xilinx SDK includes
#include "xparameters.h"
#include "stdio.h"
#include "stdlib.h"
#include "xtmrctr.h"
#include "xio.h"
#include "string.h"
#include "xintc.h"

//WARP includes
#include "w3_userio.h"
#include "wlan_mac_ipc_util.h"
#include "wlan_mac_misc_util.h"
#include "wlan_mac_802_11_defs.h"
#include "wlan_mac_queue.h"
#include "wlan_mac_event_log.h"
#include "wlan_mac_entries.h"
#include "wlan_mac_ltg.h"
#include "wlan_mac_high.h"
#include "wlan_mac_packet_types.h"
#include "wlan_mac_eth_util.h"
#include "wlan_mac_scan_fsm.h"
#include "ascii_characters.h"
#include "wlan_mac_schedule.h"
#include "wlan_mac_dl_list.h"
#include "wlan_mac_bss_info.h"
#include "wlan_mac_sta_join_fsm.h"
#include "wlan_mac_sta.h"


// WLAN Exp includes
#include "wlan_exp.h"
#include "wlan_exp_common.h"
#include "wlan_exp_node.h"
#include "wlan_exp_node_sta.h"
#include "wlan_exp_transport.h"


/*************************** Constant Definitions ****************************/

#define  WLAN_EXP_ETH                            WN_ETH_B
#define  WLAN_EXP_NODE_TYPE                      (WARPNET_TYPE_80211_BASE + WARPNET_TYPE_80211_HIGH_STA)
#define  WLAN_EXP_TYPE_MASK                      (WARPNET_TYPE_BASE_MASK + WARPNET_TYPE_80211_HIGH_MASK)

#define  WLAN_DEFAULT_CHANNEL                    4
#define  WLAN_DEFAULT_TX_PWR                     15


/*********************** Global Variable Definitions *************************/


/*************************** Variable Definitions ****************************/

// If you want this station to try to associate to a known AP at boot, type
//   the string here. Otherwise, let it be an empty string.
static char                       access_point_ssid[SSID_LEN_MAX + 1] = "Uday Rocks";
// static char                       access_point_ssid[SSID_LEN_MAX + 1] = "";

// Common TX header for 802.11 packets
mac_header_80211_common           tx_header_common;

// Default transmission parameters
tx_params                         default_unicast_mgmt_tx_params;
tx_params                         default_unicast_data_tx_params;
tx_params                         default_multicast_mgmt_tx_params;
tx_params                         default_multicast_data_tx_params;

// Access point information
bss_info*                         my_bss_info;

// List to hold Tx/Rx statistics
dl_list		                      statistics_table;

// Tx queue variables;
static u32                        max_queue_size;
volatile u8                       pause_data_queue;

// STA channel
volatile u32                      mac_param_chan;

// MAC address
static u8 	                      wlan_mac_addr[6];

// Beacon variables
volatile u8	                      allow_beacon_ts_update;            // Allow timebase to be updated from beacons



/*************************** Functions Prototypes ****************************/


/******************************** Functions **********************************/

int main() {
	wlan_mac_hw_info *       hw_info;

	// This list of channels will be used by the active scan state machine. The STA will scan
	//  each channel looking for a network with the default SSID
	//u8                       channel_selections[11] = {1,2,3,4,5,6,7,8,9,10,11}; //Scan only 2.4GHz channels
	u8                       channel_selections[14] = {1,2,3,4,5,6,7,8,9,10,11,36,44,48}; //Scan 2.4GHz and 5GHz channels

	// Print initial message to UART
	xil_printf("\f");
	xil_printf("----- Mango 802.11 Reference Design -----\n");
	xil_printf("----- v1.3 ------------------------------\n");
	xil_printf("----- wlan_mac_sta ----------------------\n");
	xil_printf("Compiled %s %s\n\n", __DATE__, __TIME__);

	// This function should be executed first. It will zero out memory, and if that
	//     memory is used before calling this function, unexpected results may happen.
	wlan_mac_high_heap_init();

	// Initialize the maximum TX queue size
	max_queue_size = MAX_TX_QUEUE_LEN;

    // Do not allow timebase updates from beacons
	allow_beacon_ts_update = 1;

	// Unpause the queue
	pause_data_queue = 0;

	// Set my_bss_info to NULL (ie STA is not currently on a BSS)
	my_bss_info = NULL;

	//New associations adopt these unicast params; the per-node params can be
	// overridden via wlan_exp calls or by custom C code
	default_unicast_data_tx_params.phy.power             = WLAN_DEFAULT_TX_PWR;
	default_unicast_data_tx_params.phy.rate              = WLAN_MAC_MCS_18M;
	default_unicast_data_tx_params.phy.antenna_mode      = TX_ANTMODE_SISO_ANTA;

	default_unicast_mgmt_tx_params.phy.power             = WLAN_DEFAULT_TX_PWR;
	default_unicast_mgmt_tx_params.phy.rate              = WLAN_MAC_MCS_6M;
	default_unicast_mgmt_tx_params.phy.antenna_mode      = TX_ANTMODE_SISO_ANTA;

	//All multicast traffic (incl. broadcast) uses these default Tx params
	default_multicast_data_tx_params.phy.power             = WLAN_DEFAULT_TX_PWR;
	default_multicast_data_tx_params.phy.rate              = WLAN_MAC_MCS_6M;
	default_multicast_data_tx_params.phy.antenna_mode      = TX_ANTMODE_SISO_ANTA;

	default_multicast_mgmt_tx_params.phy.power             = WLAN_DEFAULT_TX_PWR;
	default_multicast_mgmt_tx_params.phy.rate              = WLAN_MAC_MCS_6M;
	default_multicast_mgmt_tx_params.phy.antenna_mode      = TX_ANTMODE_SISO_ANTA;



	// Initialize the utility library
    wlan_mac_high_init();

	// Initialize callbacks
	wlan_mac_util_set_eth_rx_callback(       	(void*)ethernet_receive);
	wlan_mac_high_set_mpdu_tx_done_callback( 	(void*)mpdu_transmit_done);
	wlan_mac_high_set_mpdu_dequeue_callback( 	(void*)mpdu_dequeue);
	wlan_mac_high_set_mpdu_rx_callback(      	(void*)mpdu_rx_process);
	wlan_mac_high_set_uart_rx_callback(      	(void*)uart_rx);
	wlan_mac_high_set_poll_tx_queues_callback(  (void*)poll_tx_queues);
	wlan_mac_ltg_sched_set_callback(         	(void*)ltg_event);

	// Set the Ethernet ecapsulation mode
	wlan_mac_util_set_eth_encap_mode(ENCAP_MODE_STA);

	// Initialize the association and statistics tables
	dl_list_init(&statistics_table);

	// Set the maximum associations
	wlan_mac_high_set_max_associations(MAX_NUM_ASSOC);

	// Ask CPU Low for its status
	//     The response to this request will be handled asynchronously
	wlan_mac_high_request_low_state();

    // Wait for CPU Low to initialize
	while( wlan_mac_high_is_cpu_low_initialized() == 0){
		xil_printf("waiting on CPU_LOW to boot\n");
	};

#ifdef USE_WARPNET_WLAN_EXP
    // NOTE:  To use the WLAN Experiments Framework, it must be initialized after
	//        CPU low has populated the hw_info structure in the MAC High framework.

	// Reset all callbacks
	wlan_exp_reset_all_callbacks();

	// Set WLAN Exp callbacks
	wlan_exp_set_init_callback(                     (void *)wlan_exp_node_sta_init);
	wlan_exp_set_process_callback(                  (void *)wlan_exp_node_sta_processCmd);
	wlan_exp_set_reset_station_statistics_callback( (void *)reset_station_statistics);
	wlan_exp_set_purge_all_data_tx_queue_callback(  (void *)purge_all_data_tx_queue);
	wlan_exp_set_reset_all_associations_callback(   (void *)reset_all_associations);
	wlan_exp_set_reset_bss_info_callback(           (void *)reset_bss_info);
	//   - Currently no timebase adjust needed; Use wlan_exp_set_timebase_adjust_callback();
    //   - wlan_exp_set_tx_cmd_add_association_callback() should not be used by the STA

	// Configure the wlan_exp framework
	wlan_exp_configure(WLAN_EXP_NODE_TYPE, WLAN_EXP_TYPE_MASK, WLAN_EXP_ETH);

	// Get the hardware info that has been collected from CPU low
	hw_info = wlan_mac_high_get_hw_info();

	// Initialize WLAN Exp
	wlan_exp_node_init(hw_info->type, hw_info->serial_number, hw_info->fpga_dna,
			           hw_info->wn_eth_device, hw_info->hw_addr_wn, hw_info->hw_addr_wlan);
#endif

	// CPU Low will pass HW information to CPU High as part of the boot process
	//   - Get necessary HW information
	memcpy((void*) &(wlan_mac_addr[0]), (void*) wlan_mac_high_get_eeprom_mac_addr(), 6);

    // Set Header information
	tx_header_common.address_2 = &(wlan_mac_addr[0]);

    // Initialize hex display
	sta_write_hex_display(0);

	// Set up channel
	mac_param_chan      = WLAN_DEFAULT_CHANNEL;
	wlan_mac_high_set_channel( mac_param_chan );

	// Set the other CPU low parameters
	wlan_mac_high_set_rx_ant_mode(RX_ANTMODE_SISO_ANTA);
	wlan_mac_high_set_tx_ctrl_pow(WLAN_DEFAULT_TX_PWR);

	// Configure CPU Low's filter for passing Rx packets up to CPU High
	//     Default is "promiscuous" mode - pass all data and management packets with good or bad checksums
	//     This allows logging of all data/management receptions, even if they're not intended for this node
	wlan_mac_high_set_rx_filter_mode(RX_FILTER_FCS_ALL | RX_FILTER_HDR_ALL);

    // Initialize interrupts
	wlan_mac_high_interrupt_init();

    // Schedule all events
    //     None at this time

	// Reset the event log
	event_log_reset();

	// Print Station information to the terminal
    xil_printf("WLAN MAC Station boot complete: \n");
    xil_printf("  Default SSID : %s \n", access_point_ssid);
    xil_printf("  Channel      : %d \n", mac_param_chan);
	xil_printf("  MAC Addr     : %02x-%02x-%02x-%02x-%02x-%02x\n\n",wlan_mac_addr[0],wlan_mac_addr[1],wlan_mac_addr[2],wlan_mac_addr[3],wlan_mac_addr[4],wlan_mac_addr[5]);

#ifdef WLAN_USE_UART_MENU
	xil_printf("\nPress the Esc key in your terminal to access the UART menu\n");
#endif

	// Start the interrupts
	wlan_mac_high_interrupt_restore_state(INTERRUPTS_ENABLED);

	// Set the default active scan channels
	wlan_mac_set_scan_channels(channel_selections, sizeof(channel_selections)/sizeof(channel_selections[0]));

	// If there is a default SSID and the DIP switch allows it, initiate a probe request
	if( (strlen(access_point_ssid) > 0) && ((wlan_mac_high_get_user_io_state()&GPIO_MASK_DS_3) == 0)) {
		wlan_mac_sta_scan_and_join(access_point_ssid, 0);
	}

	while(1){
#ifdef USE_WARPNET_WLAN_EXP
		// The wlan_exp Ethernet handling is not interrupt based. Periodic polls of the wlan_exp
		//     transport are required to service new commands. All other node activity (wired/wireless Tx/Rx,
		//     scheduled events, user interaction, etc) are handled via interrupt service routines
		transport_poll( WLAN_EXP_ETH );
#endif
	}

	// Unreachable, but non-void return keeps the compiler happy
	return -1;
}



/**
 * @brief Poll Tx queues to select next available packet to transmit
 *
 * This function is called whenever the upper MAC is ready to send a new packet
 * to the lower MAC for transmission. The next packet to transmit is selected
 * from one of the currently-enabled Tx queues.
 *
 * The reference implementation uses a simple queue prioritization scheme:
 *   - Two queues are defined: Management (MANAGEMENT_QID) and Data (UNICAST_QID)
 *     - The Management queue is for all management traffic
 *     - The Data queue is for all data to the associated AP
 *   - The code alternates its polling between queues
 *
 * This function uses the framework function dequeue_transmit_checkin() to check individual queues
 * If dequeue_transmit_checkin() is passed a not-empty queue, it will dequeue and transmit a packet, then
 * return a non-zero status. Thus the calls below terminate polling as soon as any call to dequeue_transmit_checkin()
 * returns with a non-zero value, allowing the next call to poll_tx_queues() to continue the queue polling process.
 *
 * @param None
 * @return None
 */
void poll_tx_queues(){
	u8 i;

	#define MAX_NUM_QUEUE 2

	// Are we pausing transmissions?
	if(pause_data_queue == 0){

		static u32 queue_index = 0;

		// Is CPU low ready for a transmission?
		if( wlan_mac_high_is_ready_for_tx() ) {

			// Alternate between checking the management queue and the data queue
			for(i = 0; i < MAX_NUM_QUEUE; i++) {
				queue_index = (queue_index + 1) % MAX_NUM_QUEUE;

				switch(queue_index){
					case 0:  if(dequeue_transmit_checkin(MANAGEMENT_QID)) { return; }  break;
					case 1:  if(dequeue_transmit_checkin(UNICAST_QID))    { return; }  break;
				}
			}
		}
	} else {
		// We are only currently allowed to send management frames. Typically this is caused by an ongoing
		// active scan
		if( wlan_mac_high_is_ready_for_tx() ) {
			dequeue_transmit_checkin(MANAGEMENT_QID);
		}
	}
}



/**
 * @brief Purges all packets from all Tx queues
 *
 * This function discards all currently en-queued packets awaiting transmission and returns all
 * queue entries to the free pool.
 *
 * This function does not discard packets already submitted to the lower-level MAC for transmission
 *
 * @param None
 * @return None
 */
void purge_all_data_tx_queue(){
	// Purge all data transmit queues
	purge_queue(MCAST_QID);           // Broadcast Queue
	purge_queue(UNICAST_QID);         // Unicast Queue
}




/**
 * @brief Callback to handle a packet after it was transmitted by the lower-level MAC
 *
 * This function is called when CPU Low indicates it has completed the Tx process for a packet previously
 * submitted by CPU High.
 *
 * CPU High has two responsibilities post-Tx:
 *  - Cleanup any resources dedicated to the packet
 *  - Update any statistics and log info to reflect the Tx result
 *
 * @param tx_frame_info* tx_mpdu
 *  - Pointer to the MPDU which was just transmitted
 * @param wlan_mac_low_tx_details* tx_low_details
 *  - Pointer to the array of data recorded by the lower-level MAC about each re-transmission of the MPDU
 * @param u16 num_tx_low_details
 *  - number of elements in array pointed to by previous argument
 * @return None
*/
void mpdu_transmit_done(tx_frame_info* tx_mpdu, wlan_mac_low_tx_details* tx_low_details, u16 num_tx_low_details) {
	u32                    i;
	u64                    ts_old                  = 0;
	station_info*          station 				   = NULL;


	if(my_bss_info != NULL) station = (station_info*)(my_bss_info->associated_stations.first->data);

	// Additional variables (Future Use)
	// void*                  mpdu                    = (u8*)tx_mpdu + PHY_TX_PKT_BUF_MPDU_OFFSET;
	// u8*                    mpdu_ptr_u8             = (u8*)mpdu;
	// mac_header_80211*      tx_80211_header         = (mac_header_80211*)((void *)mpdu_ptr_u8);

	// Log all of the TX Low transmissions
	for(i = 0; i < num_tx_low_details; i++) {

		if(i==0 && (tx_low_details[i].tx_start_delta < T_SLOT)){
			//This captures a subtle effect in the DCF hardware. A random backoff is calculated on the
			//first transmission of an MPDU in case a CCA_BUSY causes a deferral. If there is no deferral,
			//this slot count is not used. We can sanitize this value here by seeing if the packet transmitted
			//immediately (i.e. a time from start to accept that is less than a slot). In this case, we know
			//there was no backoff needed for this transmission. We signify this event with a num_slots value
			//of -1.
			tx_low_details[i].num_slots = -1;
		}


		// Log the TX low
		wlan_exp_log_create_tx_low_entry(tx_mpdu, &tx_low_details[i], ts_old, i);

		// Accumulate the time-between-transmissions, used to calculate absolute time of each TX_LOW event above
		ts_old += tx_low_details[i].tx_start_delta;
	}

	// Log the TX MPDU
	wlan_exp_log_create_tx_entry(tx_mpdu, mac_param_chan);

	// Update the statistics for the node to which the packet was just transmitted
	if(tx_mpdu->AID != 0) {
		wlan_mac_high_update_tx_statistics(tx_mpdu, station);
	}

	// Send log entry to wlan_exp controller immediately (not currently supported)
	//
	// if (tx_high_event_log_entry != NULL) {
    //     wn_transmit_log_entry((void *)tx_high_event_log_entry);
	// }
}



/**
 * @brief Callback to handle insertion of an Ethernet reception into the corresponding wireless Tx queue
 *
 * This function is called when a new Ethernet packet is received that must be transmitted via the wireless interface.
 * The packet must be encapsulated before it is passed to this function. Ethernet encapsulation is implemented in the mac_high framework.
 *
 * The tx_queue_list argument is a DL list, but must contain exactly one queue entry which contains the encapsulated packet
 * A list container is used here to ease merging of the list with the target queue.
 *
 * @param tx_queue_element* curr_tx_queue_element
 *  - A single queue element containing the packet to transmit
 * @param u8* eth_dest
 *  - 6-byte destination address from original Ethernet packet
 * @param u8* eth_src
 *  - 6-byte source address from original Ethernet packet
 * @param u16 tx_length
 *  - Length (in bytes) of the packet payload
 * @return 1 for successful enqueuing of the packet, 0 otherwise
 */
int ethernet_receive(tx_queue_element* curr_tx_queue_element, u8* eth_dest, u8* eth_src, u16 tx_length){
	tx_queue_buffer* 	curr_tx_queue_buffer;
	station_info* 		ap_station_info;


	// Check associations
	//     Is there an AP to send the packet to?
	if(my_bss_info != NULL){
		ap_station_info = (station_info*)((my_bss_info->associated_stations.first)->data);

		// Send the packet to the AP
		if(queue_num_queued(UNICAST_QID) < max_queue_size){

			// Send the pre-encapsulated Ethernet frame over the wireless interface
			//     NOTE:  The queue element has already been provided, so we do not need to check if it is NULL
			curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

			// Setup the TX header
			wlan_mac_high_setup_tx_header( &tx_header_common, ap_station_info->addr,(u8*)(&(eth_dest[0])));

			// Fill in the data
			wlan_create_data_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, MAC_FRAME_CTRL2_FLAG_TO_DS);

			// Setup the TX frame info
			wlan_mac_high_setup_tx_frame_info ( &tx_header_common, curr_tx_queue_element, tx_length, (TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO), UNICAST_QID );

			// Set the information in the TX queue buffer
			curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_STATION_INFO;
			curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)ap_station_info;
			curr_tx_queue_buffer->frame_info.AID         = ap_station_info->AID;

			// Put the packet in the queue
			enqueue_after_tail(UNICAST_QID, curr_tx_queue_element);



		} else {
			// Packet was not successfully enqueued
			return 0;
		}

		// Packet was successfully enqueued
		return 1;
	} else {

		// STA is not currently associated, so we won't send any eth frames
		return 0;
	}
}



/**
 * @brief Process received MPDUs
 *
 * This callback function will process all the received MPDUs.
 *
 * This function must implement the state machine that will allow a station to join the AP.
 *
 * @param  void * pkt_buf_addr
 *     - Packet buffer address;  Contains the contents of the MPDU as well as other packet information from CPU low
 * @return None
 */
void mpdu_rx_process(void* pkt_buf_addr) {

	rx_frame_info*      mpdu_info                = (rx_frame_info*)pkt_buf_addr;
	void*               mpdu                     = (u8*)pkt_buf_addr + PHY_RX_PKT_BUF_MPDU_OFFSET;
	u8*                 mpdu_ptr_u8              = (u8*)mpdu;
	mac_header_80211*   rx_80211_header          = (mac_header_80211*)((void *)mpdu_ptr_u8);

	u16                 rx_seq;
	rx_common_entry*    rx_event_log_entry       = NULL;

	dl_entry*	        associated_station_entry;
	station_info*       associated_station       = NULL;
	statistics_txrx*    station_stats            = NULL;

	u8                  unicast_to_me;
	u8                  to_multicast;
	s64                 timestamp_diff;
	u8                  is_associated            = 0;
	dl_entry*			bss_info_entry;
	bss_info*			curr_bss_info;
	u8					pre_llc_offset			 = 0;

	u8 					rate					 = mpdu_info->phy_details.mcs;
	u16 				length					 = mpdu_info->phy_details.length;


	// Log the reception
	rx_event_log_entry = wlan_exp_log_create_rx_entry(mpdu_info, mac_param_chan, rate);

	// If this function was passed a CTRL frame (e.g., CTS, ACK), then we should just quit.
	// The only reason this occured was so that it could be logged in the line above.
	if((rx_80211_header->frame_control_1 & 0xF) == MAC_FRAME_CTRL1_TYPE_CTRL){
		goto mpdu_rx_process_end;
	}

	// Determine destination of packet
	unicast_to_me = wlan_addr_eq(rx_80211_header->address_1, wlan_mac_addr);
	to_multicast  = wlan_addr_mcast(rx_80211_header->address_1);

    // If the packet is good (ie good FCS) and it is destined for me, then process it
	if( (mpdu_info->state == RX_MPDU_STATE_FCS_GOOD)){

		// Update the association information
		if(my_bss_info != NULL){
			associated_station_entry = wlan_mac_high_find_station_info_ADDR(&(my_bss_info->associated_stations), (rx_80211_header->address_2));
		} else {
			associated_station_entry = NULL;
		}

		if(associated_station_entry != NULL) {
			associated_station = (station_info*)(associated_station_entry->data);

			// Update station information
			associated_station->latest_activity_timestamp = get_usec_timestamp();
			associated_station->rx.last_power             = mpdu_info->rx_power;
			associated_station->rx.last_rate              = rate;

			is_associated = 1;
			rx_seq        = ((rx_80211_header->sequence_control)>>4)&0xFFF;
			station_stats = associated_station->stats;

			// Check if this was a duplicate reception
			//   - Received seq num matched previously received seq num for this STA
			if( (associated_station->rx.last_seq == rx_seq) ) {
				if(rx_event_log_entry != NULL){
					rx_event_log_entry->flags |= RX_ENTRY_FLAGS_IS_DUPLICATE;
				}

				// Finish the function
				goto mpdu_rx_process_end;
			} else {
				associated_station->rx.last_seq = rx_seq;
			}
		} else {
			station_stats = wlan_mac_high_add_statistics(&statistics_table, NULL, rx_80211_header->address_2);
		}

        // Update receive statistics
		if(station_stats != NULL){
			station_stats->latest_txrx_timestamp = get_usec_timestamp();
			if((rx_80211_header->frame_control_1 & 0xF) == MAC_FRAME_CTRL1_TYPE_DATA){
				((station_stats)->data.rx_num_packets)++;
				((station_stats)->data.rx_num_bytes) += (length - WLAN_PHY_FCS_NBYTES - sizeof(mac_header_80211));
			} else if((rx_80211_header->frame_control_1 & 0xF) == MAC_FRAME_CTRL1_TYPE_MGMT) {
				((station_stats)->mgmt.rx_num_packets)++;
				((station_stats)->mgmt.rx_num_bytes) += (length - WLAN_PHY_FCS_NBYTES - sizeof(mac_header_80211));
			}
		}
		if(unicast_to_me || to_multicast){
			// Process the packet
			switch(rx_80211_header->frame_control_1) {

				//---------------------------------------------------------------------
				case MAC_FRAME_CTRL1_SUBTYPE_QOSDATA:
					pre_llc_offset = sizeof(qos_control);
				case (MAC_FRAME_CTRL1_SUBTYPE_DATA):
					// Data packet
					//   - If the STA is associated with the AP and this is from the DS, then transmit over the wired network
					//
					if(is_associated){
						if((rx_80211_header->frame_control_2) & MAC_FRAME_CTRL2_FLAG_FROM_DS) {
							// MPDU is flagged as destined to the DS - send it for de-encapsulation and Ethernet Tx (if appropriate)
							wlan_mpdu_eth_send(mpdu,length, pre_llc_offset);
						}
					}
				break;


				//---------------------------------------------------------------------
				case (MAC_FRAME_CTRL1_SUBTYPE_ASSOC_RESP):
					// Association response
					//   - If we are in the correct association state and the response was success, then associate with the AP
					//


					mpdu_ptr_u8 += sizeof(mac_header_80211);

					if(wlan_addr_eq(rx_80211_header->address_1, wlan_mac_addr) && ((association_response_frame*)mpdu_ptr_u8)->status_code == STATUS_SUCCESS){
						// AP is authenticating us. Update BSS_info.
						bss_info_entry = wlan_mac_high_find_bss_info_BSSID(rx_80211_header->address_3);

						if(bss_info_entry != NULL){
							curr_bss_info = (bss_info*)(bss_info_entry->data);
							if(curr_bss_info->state == BSS_STATE_AUTHENTICATED){
								curr_bss_info->state = BSS_STATE_ASSOCIATED;
								wlan_mac_sta_bss_attempt_poll((((association_response_frame*)mpdu_ptr_u8)->association_id)&~0xC000);
							}
						}
					} else {
						xil_printf("Association failed, reason code %d\n", ((association_response_frame*)mpdu_ptr_u8)->status_code);
					}

				break;


				//---------------------------------------------------------------------
				case (MAC_FRAME_CTRL1_SUBTYPE_AUTH):
					// Authentication Reponse

					if( wlan_addr_eq(rx_80211_header->address_1, wlan_mac_addr)) {

						// Move the packet pointer to after the header
						mpdu_ptr_u8 += sizeof(mac_header_80211);

						// Check the authentication algorithm
						switch(((authentication_frame*)mpdu_ptr_u8)->auth_algorithm){

							case AUTH_ALGO_OPEN_SYSTEM:
								// Check that this was a successful authentication response
								if(((authentication_frame*)mpdu_ptr_u8)->auth_sequence == AUTH_SEQ_RESP){

									if(((authentication_frame*)mpdu_ptr_u8)->status_code == STATUS_SUCCESS){
										// AP is authenticating us. Update BSS_info.
										bss_info_entry = wlan_mac_high_find_bss_info_BSSID(rx_80211_header->address_3);

										if(bss_info_entry != NULL){
											curr_bss_info = (bss_info*)(bss_info_entry->data);
											if(curr_bss_info->state == BSS_STATE_UNAUTHENTICATED){
												curr_bss_info->state = BSS_STATE_AUTHENTICATED;
												wlan_mac_sta_bss_attempt_poll(0);
											}
										}
									}

									// Finish the function
									goto mpdu_rx_process_end;
								}
							break;

							default:
								xil_printf("Authentication failed.  AP uses authentication algorithm %d which is not support by the 802.11 reference design.\n", ((authentication_frame*)mpdu_ptr_u8)->auth_algorithm);
							break;
						}
					}
				break;


				//---------------------------------------------------------------------
				case (MAC_FRAME_CTRL1_SUBTYPE_DEAUTH):
					// De-authentication
					//   - If we are being de-authenticated, then log and update the association state
					//   - Start and active scan to find the AP if an SSID is defined
					//
					if(my_bss_info != NULL){
						if(wlan_addr_eq(rx_80211_header->address_1, wlan_mac_addr) && (wlan_mac_high_find_station_info_ADDR(&(my_bss_info->associated_stations), rx_80211_header->address_2) != NULL)){

							// Log the association state change
							add_station_info_to_log((station_info*)((my_bss_info->associated_stations.first)->data), STATION_INFO_ENTRY_ZERO_AID, WLAN_EXP_STREAM_ASSOC_CHANGE);

							// Remove the association
							wlan_mac_high_remove_association(&(my_bss_info->associated_stations), &statistics_table, rx_80211_header->address_2);

							// Purge all packets for the AP
							purge_queue(UNICAST_QID);

							// Update the hex display to show that we are no longer associated
							sta_write_hex_display(0);

							my_bss_info->state = BSS_STATE_UNAUTHENTICATED;

							curr_bss_info = my_bss_info;
							my_bss_info = NULL;

							wlan_mac_sta_join(curr_bss_info,0); //Attempt to rejoin the AP

						}
					}
				break;


				//---------------------------------------------------------------------
				case (MAC_FRAME_CTRL1_SUBTYPE_BEACON):
				case (MAC_FRAME_CTRL1_SUBTYPE_PROBE_RESP):
					// Beacon Packet / Probe Response Packet
					//   -
					//

					// Define the PHY timestamp offset
					#define PHY_T_OFFSET 25

					// Update the timestamp from the beacon / probe response if allowed
					if(my_bss_info != NULL && allow_beacon_ts_update == 1){

						// If this packet was from our AP
						if( wlan_addr_eq( ((station_info*)(((my_bss_info->associated_stations).first)->data))->addr, rx_80211_header->address_3)){

							// Move the packet pointer to after the header
							mpdu_ptr_u8 += sizeof(mac_header_80211);

							// Calculate the difference between the beacon timestamp and the packet timestamp
							//     NOTE:  We need to compensate for the time it takes to set the timestamp in the PHY
							timestamp_diff = (s64)(((beacon_probe_frame*)mpdu_ptr_u8)->timestamp) - (s64)(mpdu_info->timestamp) + PHY_T_OFFSET;

							// Set the timestamp
							wlan_mac_high_set_timestamp_delta(timestamp_diff);

							// Move the packet pointer back to the start for the rest of the function
							mpdu_ptr_u8 -= sizeof(mac_header_80211);
						}
					}

				break;


				//---------------------------------------------------------------------
				default:
					//This should be left as a verbose print. It occurs often when communicating with mobile devices since they tend to send
					//null data frames (type: DATA, subtype: 0x4) for power management reasons.
					warp_printf(PL_VERBOSE, "Received unknown frame control type/subtype %x\n",rx_80211_header->frame_control_1);
				break;
			}
		}

		// Finish the function
		goto mpdu_rx_process_end;
	} else {
		// Process any Bad FCS packets
		goto mpdu_rx_process_end;
	}


	// Finish any processing for the RX MPDU process
	mpdu_rx_process_end:

	// Currently, asynchronous transmission of log entries is not supported
	//
	if ((rx_event_log_entry != NULL) && ((rx_event_log_entry->rate) != WLAN_MAC_MCS_1M)) {
        wn_transmit_log_entry((void *)rx_event_log_entry);
	}

    return;
}



/**
 * @brief Callback to handle new Local Traffic Generator event
 *
 * This function is called when the LTG scheduler determines a traffic generator should create a new packet. The
 * behavior of this function depends entirely on the LTG payload parameters.
 *
 * The reference implementation defines 3 LTG payload types:
 *  - LTG_PYLD_TYPE_FIXED: generate 1 fixed-length packet to single destination; callback_arg is pointer to ltg_pyld_fixed struct
 *  - LTG_PYLD_TYPE_UNIFORM_RAND: generate 1 random-length packet to signle destimation; callback_arg is pointer to ltg_pyld_uniform_rand struct
 *  - LTG_PYLD_TYPE_ALL_ASSOC_FIXED: generate 1 fixed-length packet to each associated station; callback_arg is poitner to ltg_pyld_all_assoc_fixed struct
 *
 * @param u32 id
 *  - Unique ID of the previously created LTG
 * @param void* callback_arg
 *  - Callback argument provided at LTG creation time; interpretation depends on LTG type
 * @return None
 */
void ltg_event(u32 id, void* callback_arg){

	u32                 payload_length;
	u32					min_ltg_payload_length;
	u8*                 addr_da;
	station_info*       ap_station_info;
	tx_queue_element* curr_tx_queue_element        = NULL;
	tx_queue_buffer*  curr_tx_queue_buffer         = NULL;

	if(my_bss_info != NULL){
		switch(((ltg_pyld_hdr*)callback_arg)->type){
			case LTG_PYLD_TYPE_FIXED:
				addr_da = ((ltg_pyld_fixed*)callback_arg)->addr_da;
				payload_length = ((ltg_pyld_fixed*)callback_arg)->length;
			break;
			case LTG_PYLD_TYPE_UNIFORM_RAND:
				addr_da = ((ltg_pyld_uniform_rand*)callback_arg)->addr_da;
				payload_length = (rand()%(((ltg_pyld_uniform_rand*)(callback_arg))->max_length - ((ltg_pyld_uniform_rand*)(callback_arg))->min_length))+((ltg_pyld_uniform_rand*)(callback_arg))->min_length;
			break;
			default:
				xil_printf("ERROR ltg_event: Unknown LTG Payload Type! (%d)\n", ((ltg_pyld_hdr*)callback_arg)->type);
				return;
			break;
		}

		ap_station_info = (station_info*)((my_bss_info->associated_stations.first)->data);

		// Send a Data packet to AP
		if(queue_num_queued(UNICAST_QID) < max_queue_size){
			// Checkout 1 element from the queue;
			curr_tx_queue_element = queue_checkout();
			if(curr_tx_queue_element != NULL){
				// Create LTG packet
				curr_tx_queue_buffer = ((tx_queue_buffer*)(curr_tx_queue_element->data));

				// Setup the MAC header
				wlan_mac_high_setup_tx_header( &tx_header_common, ap_station_info->addr, addr_da );

				min_ltg_payload_length = wlan_create_ltg_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, MAC_FRAME_CTRL2_FLAG_TO_DS, id);
				payload_length = max(payload_length+sizeof(mac_header_80211)+WLAN_PHY_FCS_NBYTES, min_ltg_payload_length);

				// Finally prepare the 802.11 header
				wlan_mac_high_setup_tx_frame_info ( &tx_header_common, curr_tx_queue_element, payload_length, (TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO), UNICAST_QID);

				// Update the queue entry metadata to reflect the new new queue entry contents
				curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_STATION_INFO;
				curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)ap_station_info;
				curr_tx_queue_buffer->frame_info.AID         = ap_station_info->AID;

				// Submit the new packet to the appropriate queue
				enqueue_after_tail(UNICAST_QID, curr_tx_queue_element);


			}
		}

	}
}


/**
 * @brief Reset Station Statistics
 *
 * Reset all statistics being kept for all stations
 *
 * @param  None
 * @return None
 */
void reset_station_statistics(){
	wlan_mac_high_reset_statistics(&statistics_table);
}

/**
 * @brief Reset BSS Information
 *
 * Reset all BSS Info except for my_bss_info (if it exists)
 *
 * @param  None
 * @return None
 */
void reset_bss_info(){
	dl_list  * bss_info_list = wlan_mac_high_get_bss_info_list();
	dl_entry * next_dl_entry = bss_info_list->first;
	dl_entry * curr_dl_entry;
    bss_info * curr_bss_info;

	while(next_dl_entry != NULL){
		curr_dl_entry = next_dl_entry;
		next_dl_entry = dl_entry_next(curr_dl_entry);
		curr_bss_info = (bss_info *)(curr_dl_entry->data);

		if(curr_bss_info != my_bss_info){
			wlan_mac_high_clear_bss_info(curr_bss_info);
			dl_entry_remove(bss_info_list, curr_dl_entry);
			bss_info_checkin(curr_dl_entry);
		}
	}
}



/**
 * @brief Reset All Associations
 *
 * Wrapper to provide consistent name and potentially wrap additional functionality
 * in the future.
 *
 * @param  None
 * @return None
 */
void reset_all_associations(){
    xil_printf("Reset All Associations\n");

    // STA disassociate command is the same for an individual AP or ALL
	sta_disassociate();

}


void mpdu_dequeue(tx_queue_element* packet){
	mac_header_80211* 	header;
	tx_frame_info*		frame_info;
	ltg_packet_id*      pkt_id;
	u32 				packet_payload_size;

	header 	  			= (mac_header_80211*)((((tx_queue_buffer*)(packet->data))->frame));
	frame_info 			= (tx_frame_info*)&((((tx_queue_buffer*)(packet->data))->frame_info));
	packet_payload_size	= frame_info->length;

	switch(wlan_mac_high_pkt_type(header, packet_payload_size)){
		case PKT_TYPE_DATA_ENCAP_LTG:
			pkt_id		       = (ltg_packet_id*)((u8*)header + sizeof(mac_header_80211));
			pkt_id->unique_seq = wlan_mac_high_get_unique_seq();
			//do not break here
		case PKT_TYPE_DATA_ENCAP_ETH:
			// Overwrite addr1 of this packet with the currently associated AP. This will allow previously
			// enqueued packets to seemlessly hand off if this STA joins a new AP
			if(my_bss_info != NULL){
				memcpy(header->address_1, my_bss_info->bssid, 6);
			} else {
				xil_printf("Dequeue error: no associated AP\n");
			}
		break;
	}
}

/**
 * @brief Accessor methods for global variables
 *
 * These functions will return pointers to global variables
 *
 * @param  None
 * @return None
 */
dl_list * get_station_info_list(){
	if(my_bss_info != NULL){
		return &(my_bss_info->associated_stations);
	} else {
		return NULL;
	}
}
dl_list * get_statistics()       { return &statistics_table;   }
u8      * get_wlan_mac_addr()    { return (u8 *)&wlan_mac_addr;      }



/**
 * @brief Disassociate the STA from the associated AP
 *
 * This function will disassociate the STA from the AP if it is associated.  Otherwise,
 * it will do nothing.  It also logs any association state change
 *
 * @param  None
 * @return int
 *  -  0 if successful
 *  - -1 if unsuccessful
 *
 *  @note This function uses global variables:  association_state, association_table
 *      and statistics_table
 */
int  sta_disassociate( void ) {
	int                 status = 0;
	station_info*       associated_station = NULL;
	dl_entry*	        associated_station_entry;

	xil_printf("Disassociate from AP\n");

	// If the STA is currently associated, remove the association; otherwise do nothing
	if(my_bss_info != NULL){

		my_bss_info->state = BSS_STATE_UNAUTHENTICATED; //Drop all the way back in unauthenticated

		// Get the currently associated station
		//   NOTE:  This assumes that there is only one associated station
		associated_station_entry = my_bss_info->associated_stations.first;
		associated_station       = (station_info*)associated_station_entry->data;

#if _DEBUG_
		u32 i;
		xil_printf("Disassociating node: %02x", (associated_station->addr)[0]);
		for ( i = 1; i < ETH_ADDR_LEN; i++ ) { xil_printf(":%02x", (associated_station->addr)[i] ); } xil_printf("\n");
#endif

		// Log association change
		add_station_info_to_log(associated_station, STATION_INFO_ENTRY_ZERO_AID, WLAN_EXP_STREAM_ASSOC_CHANGE);

		//
		// TODO:  Send Disassociation Message
		// NOTE: Jump to old channel before doing so. The channel is present in the my_bss_info in this context. No need to change back after.
		//

		// Remove current association
		status = wlan_mac_high_remove_association(&(my_bss_info->associated_stations), &statistics_table, associated_station->addr);

		my_bss_info = NULL;
	}

	// Update the HEX display
	sta_write_hex_display(0);

	return status;
}


int  sta_set_association_state( bss_info* new_bss_info, u16 aid ) {
    int                 status = -1;
	station_info*       associated_station = NULL;

	xil_printf("Setting New Association State:\n");
	xil_printf("SSID:  %s\n", new_bss_info->ssid);
	xil_printf("AID:   %d\n", aid);
	xil_printf("BSSID: %02x-%02x-%02x-%02x-%02x-%02x\n", new_bss_info->bssid[0],new_bss_info->bssid[1],new_bss_info->bssid[2],new_bss_info->bssid[3],new_bss_info->bssid[4],new_bss_info->bssid[5]);
	xil_printf("State: %d\n", new_bss_info->state);

	// Disassociate from any currently associated APs
	status = sta_disassociate();

	// The disassociate step may have changed channels to send a message to the old AP.
	mac_param_chan = new_bss_info->chan;
	wlan_mac_high_set_channel(mac_param_chan);

	my_bss_info = new_bss_info;

	if ( new_bss_info->state == BSS_STATE_ASSOCIATED ) {
		// Add the new association
		associated_station = wlan_mac_high_add_association(&(my_bss_info->associated_stations), &statistics_table, my_bss_info->bssid, aid);

		if ( associated_station != NULL ) {

			// Log association change
			add_station_info_to_log(associated_station, STATION_INFO_ENTRY_NO_CHANGE, WLAN_EXP_STREAM_ASSOC_CHANGE);

#if _DEBUG_
			u32 i;
			xil_printf("Associating node: %02x", (associated_station->addr)[0]);
			for ( i = 1; i < ETH_ADDR_LEN; i++ ) { xil_printf(":%02x", (associated_station->addr)[i] ); } xil_printf("\n");
#endif

			// Update the HEX display
			sta_write_hex_display(associated_station->AID);

			pause_data_queue = 0;

			status = 0;

		} else {
		    status = -1;
		}
	}

	return status;
}



/**
 * @brief Write a Decimal Value to the Hex Display
 *
 * This function will write a decimal value to the board's two-digit hex displays.
 * For the STA, the display is right justified; WARPNet will indicate its connection
 * state using the right decimal point.
 *
 * @param u8 val
 *  - Value to be displayed (between 0 and 99)
 * @return None
 *
 */
void sta_write_hex_display(u8 val){
    u32 right_dp;

	// Need to retain the value of the right decimal point
	right_dp = userio_read_hexdisp_right( USERIO_BASEADDR ) & W3_USERIO_HEXDISP_DP;

	if ( val < 10 ) {
		// Turn off hex mapping; turn off left hex display
		userio_write_control( USERIO_BASEADDR, ( userio_read_control( USERIO_BASEADDR ) & ( ~( W3_USERIO_HEXDISP_L_MAPMODE ) ) ) );
		userio_write_hexdisp_left(USERIO_BASEADDR, 0x00);

		userio_write_control(USERIO_BASEADDR, userio_read_control(USERIO_BASEADDR) | (W3_USERIO_HEXDISP_R_MAPMODE));
		userio_write_hexdisp_right(USERIO_BASEADDR, (val | right_dp));
	} else {
		userio_write_control(USERIO_BASEADDR, userio_read_control(USERIO_BASEADDR) | (W3_USERIO_HEXDISP_L_MAPMODE | W3_USERIO_HEXDISP_R_MAPMODE));

	    userio_write_hexdisp_left(USERIO_BASEADDR, ((val/10)%10));
		userio_write_hexdisp_right(USERIO_BASEADDR, ((val%10) | right_dp));
	}
}



