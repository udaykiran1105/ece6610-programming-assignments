/** @file wlan_exp_node_ap.c
 *  @brief Access Point WARPNet Experiment
 *
 *  This contains code for the 802.11 Access Point's WARPNet experiment interface.
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
#include "wlan_exp.h"
#include "wlan_mac_high.h"
#include "wlan_mac_entries.h"
#include "wlan_exp_node.h"
#include "wlan_exp_node_ap.h"


#ifdef USE_WARPNET_WLAN_EXP

// Xilinx includes
#include <xparameters.h>
#include <xil_io.h>
#include <xio.h>
#include "xintc.h"


// Library includes
#include "string.h"
#include "stdlib.h"

//WARP includes
#include "wlan_mac_ipc_util.h"
#include "wlan_mac_misc_util.h"
#include "wlan_mac_802_11_defs.h"
#include "wlan_mac_queue.h"
#include "wlan_mac_ltg.h"
#include "wlan_mac_packet_types.h"
#include "wlan_mac_eth_util.h"
#include "wlan_mac_dl_list.h"
#include "wlan_mac_schedule.h"
#include "wlan_mac_addr_filter.h"
#include "wlan_mac_event_log.h"
#include "wlan_mac_ap.h"
#include "wlan_mac_bss_info.h"



/*************************** Constant Definitions ****************************/


/*********************** Global Variable Definitions *************************/


extern dl_list      statistics_table;
extern tx_params    default_unicast_data_tx_params;
extern u32          mac_param_chan;
extern bss_info*	my_bss_info;
extern ps_conf      power_save_configuration;
extern u32          beacon_schedule_id;

/*************************** Variable Definitions ****************************/


/*************************** Functions Prototypes ****************************/


/******************************** Functions **********************************/


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
int wlan_exp_node_ap_processCmd( unsigned int cmdID, const wn_cmdHdr* cmdHdr, void* cmdArgs, wn_respHdr* respHdr, void* respArgs, void* pktSrc, unsigned int eth_dev_num){
	//IMPORTANT ENDIAN NOTES:
	// -cmdHdr is safe to access directly (pre-swapped if needed)
	// -cmdArgs is *not* pre-swapped, since the framework doesn't know what it is
	// -respHdr will be swapped by the framework; user code should fill it normally
	// -respArgs will *not* be swapped by the framework, since only user code knows what it is
	//    Any data added to respArgs by the code below must be endian-safe (swapped on AXI hardware)

	u32         * cmdArgs32  = cmdArgs;
	u32         * respArgs32 = respArgs;

	unsigned int  respIndex  = 0;                  // This function is called w/ same state as node_processCmd
	unsigned int  respSent   = NO_RESP_SENT;       // Initialize return value to NO_RESP_SENT
    // unsigned int  max_words  = 300;                // Max number of u32 words that can be sent in the packet (~1200 bytes)
                                                   //   If we need more, then we will need to rework this to send multiple response packets
    int           status;

    u32           temp, temp2, i;
    u32           msg_cmd;
    u32           id;
    u32           flags;
    u32           beacon_time;

	u8            mac_addr[6];
    u8            mask[6];

	dl_entry	* curr_entry;
	station_info* curr_station_info;
	interrupt_state_t prev_interrupt_state;

    // Note:    
    //   Response header cmd, length, and numArgs fields have already been initialized.
    
    
#ifdef _DEBUG_
	xil_printf("In wlan_exp_node_ap_processCmd():  ID = %d \n", cmdID);
#endif

	switch(cmdID){


//-----------------------------------------------------------------------------
// WLAN Exp Node Commands that must be implemented in child classes
//-----------------------------------------------------------------------------


		//---------------------------------------------------------------------
		case CMDID_NODE_DISASSOCIATE:
            // Disassociate device from node
            //
			// Message format:
			//     cmdArgs32[0:1]      MAC Address (All 0xFF means all station info)
            //
			// Response format:
			//     respArgs32[0]       Status
            //
			wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Disassociate\n");

			// Get MAC Address
        	wlan_exp_get_mac_addr(&((u32 *)cmdArgs32)[0], &mac_addr[0]);
        	id = wlan_exp_get_id_in_associated_stations(&mac_addr[0]);

			status  = CMD_PARAM_SUCCESS;

            if ( id == 0 ) {
				// If we cannot find the MAC address, return status error
            	wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Could not find specified node: ");
				wlan_exp_print_mac_address(WLAN_EXP_PRINT_INFO, &mac_addr[0]); wlan_exp_printf(WLAN_EXP_PRINT_INFO, NULL, "\n");

				status = CMD_PARAM_ERROR;

            } else {
				// If parameter is not the magic number to disassociate all stations
				if ( id != CMD_PARAM_NODE_CONFIG_ALL ) {
					// Find the station_info entry
					curr_entry = wlan_mac_high_find_station_info_ADDR( get_station_info_list(), &mac_addr[0]);

					if (curr_entry != NULL) {
						curr_station_info = (station_info*)(curr_entry->data);

						// Disable interrupts so no packets interrupt the disassociate
						prev_interrupt_state = wlan_mac_high_interrupt_stop();

						// Deauthenticate station
						deauthenticate_station(curr_station_info);

						// Re-enable interrupts
						wlan_mac_high_interrupt_restore_state(prev_interrupt_state);

						// Set return parameters and print info to console
						wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Disassociated node: ");
						wlan_exp_print_mac_address(WLAN_EXP_PRINT_INFO, &mac_addr[0]); wlan_exp_printf(WLAN_EXP_PRINT_INFO, NULL, "\n");

					} else {
						// If we cannot find the MAC address, return status error
						wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Could not find specified node: ");
						wlan_exp_print_mac_address(WLAN_EXP_PRINT_INFO, &mac_addr[0]); wlan_exp_printf(WLAN_EXP_PRINT_INFO, NULL, "\n");

						status = CMD_PARAM_ERROR;
					}
				} else {
					// Disable interrupts so no packets interrupt the disassociate
					prev_interrupt_state = wlan_mac_high_interrupt_stop();

					// Deauthenticate all stations
					deauthenticate_stations();

					// Re-enable interrupts
					wlan_mac_high_interrupt_restore_state(prev_interrupt_state);

					// Set return parameters and print info to console
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Disassociated node: ");
					wlan_exp_print_mac_address(WLAN_EXP_PRINT_INFO, &mac_addr[0]); wlan_exp_printf(WLAN_EXP_PRINT_INFO, NULL, "\n");
				}
            }

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;

        
		//---------------------------------------------------------------------
		case CMDID_NODE_CHANNEL:
			//   - cmdArgs32[0]      - Command
			//   - cmdArgs32[1]      - Channel

			msg_cmd = Xil_Ntohl(cmdArgs32[0]);
			temp    = Xil_Ntohl(cmdArgs32[1]);
			status  = CMD_PARAM_SUCCESS;

			if ( msg_cmd == CMD_PARAM_WRITE_VAL ) {
				// Set the Channel
				if ( wlan_lib_channel_verify(temp) == 0 ){
					// Send Channel Switch Announcement
					//   NOTE:  We are not sending this at this time b/c it does not look like commercial
					//       devices honor this message; The WARP nodes do not currently honor this message
					//       and there are some timing issues that need to be sorted out.
					// send_channel_switch_announcement( temp );

					mac_param_chan = temp;
					if(my_bss_info != NULL){
						//The AP uses the value in my_bss_info->chan when constructing beacons and probe response,
						//not mac_param_chan. In this Reference Design, mac_param_chan and my_bss_info are kept
						//in lockstep. Keeping them as separate variables, however, allows for flexibility in an
						//application where the AP wants to temporarily move to a different channel but not shift
						//the whole BSS to that new channel. In this case, mac_param_chan would change independently
						//of the channel within the bss_info.
						my_bss_info->chan = mac_param_chan;
					}
					wlan_mac_high_set_channel( mac_param_chan );

					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Set Channel = %d\n", mac_param_chan);
				} else {
					status  = CMD_PARAM_ERROR;
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node,
							        "Channel %d is not supported by the node. Staying on Channel %d\n", temp, mac_param_chan);
				}
			}

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );
            respArgs32[respIndex++] = Xil_Htonl( mac_param_chan );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


//-----------------------------------------------------------------------------
// AP Specific Commands
//-----------------------------------------------------------------------------


		//---------------------------------------------------------------------
		case CMDID_NODE_AP_CONFIG:
            // Set AP configuration flags
            //
			// Message format:
			//     cmdArgs32[0]   Flags
			//                     [ 0] - NODE_AP_CONFIG_FLAG_POWER_SAVING
			//     cmdArgs32[1]   Mask for flags
        	//
			// Response format:
			//     respArgs32[0]  Status (CMD_PARAM_SUCCESS/CMD_PARAM_ERROR)
			//

			// Set the return value
			status = CMD_PARAM_SUCCESS;

			// Get flags
			temp  = Xil_Ntohl(cmdArgs32[0]);
			temp2 = Xil_Ntohl(cmdArgs32[1]);

			wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "AP: Configure flags = 0x%08x  mask = 0x%08x\n", temp, temp2);

			// Configure based on the flag bit / mask
			if ( ( temp2 & CMD_PARAM_NODE_AP_CONFIG_FLAG_POWER_SAVING ) == CMD_PARAM_NODE_AP_CONFIG_FLAG_POWER_SAVING ) {
				if ( ( temp & CMD_PARAM_NODE_AP_CONFIG_FLAG_POWER_SAVING ) == CMD_PARAM_NODE_AP_CONFIG_FLAG_POWER_SAVING ) {
					power_save_configuration.enable = 1;
				} else {
					power_save_configuration.enable = 0;
				}
			}

			// Send response of status
			respArgs32[respIndex++] = Xil_Htonl( status );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
        break;


		//---------------------------------------------------------------------
		case CMDID_NODE_AP_DTIM_PERIOD:
            // Command to get / set the number of beacon intervals between DTIM beacons
            //
			// Message format:
			//     cmdArgs32[0]   Command:
			//                      - Write       (CMD_PARAM_WRITE_VAL)
			//                      - Read        (CMD_PARAM_READ_VAL)
			//     cmdArgs32[1]   Number of beacon intervals between DTIM beacons (0 - 255)
        	//
			// Response format:
			//     respArgs32[0]  Status (CMD_PARAM_SUCCESS/CMD_PARAM_ERROR)
			//     respArgs32[1]  Number of beacon intervals between DTIM beacons (0 - 255)
            //
        	msg_cmd = Xil_Ntohl(cmdArgs32[0]);
			temp    = Xil_Ntohl(cmdArgs32[1]);
			status  = CMD_PARAM_SUCCESS;

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
					power_save_configuration.dtim_period = (temp & 0xFF);
			    break;

				case CMD_PARAM_READ_VAL:
					temp = power_save_configuration.dtim_period;
			    break;

				default:
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
					status = CMD_PARAM_ERROR;
				break;
			}

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );
            respArgs32[respIndex++] = Xil_Htonl( temp );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
        break;


		//---------------------------------------------------------------------
        case CMDID_NODE_AP_SET_AUTHENTICATION_ADDR_FILTER:
            // Allow / Disallow wireless authentications
            //
			// Message format:
			//     cmdArgs32[0]   Command:
			//                      - Write       (CMD_PARAM_WRITE_VAL)
			//     cmdArgs32[1]   Number of address filters
        	//     cmdArgs32[2:N] [ Compare address (u64)), (Mask (u64) ]
        	//
			// Response format:
			//     respArgs32[0]  Status
            //
        	msg_cmd = Xil_Ntohl(cmdArgs32[0]);
			temp    = Xil_Ntohl(cmdArgs32[1]);
			status  = CMD_PARAM_SUCCESS;

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
                    // Need to disable interrupts during this operation so the filter does not have any holes
					prev_interrupt_state = wlan_mac_high_interrupt_stop();

					// Reset the current address filter
					wlan_mac_addr_filter_reset();

					// Add all the address ranges to the filter
                    for( i = 0; i < temp; i++ ) {
                        // Extract the address and the mask
                    	wlan_exp_get_mac_addr(&((u32 *)cmdArgs32)[2 + (4*i)], &mac_addr[0]);
                    	wlan_exp_get_mac_addr(&((u32 *)cmdArgs32)[4 + (4*i)], &mask[0]);

                    	wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Adding Address filter: (");
        				wlan_exp_print_mac_address(WLAN_EXP_PRINT_INFO, mac_addr); wlan_exp_printf(WLAN_EXP_PRINT_INFO, NULL, ", ");
        				wlan_exp_print_mac_address(WLAN_EXP_PRINT_INFO, mask); wlan_exp_printf(WLAN_EXP_PRINT_INFO, NULL, "\n");

                    	if ( wlan_mac_addr_filter_add(mask, mac_addr) == -1 ) {
                    		status = CMD_PARAM_ERROR;
                    	}
                    }

					wlan_mac_high_interrupt_restore_state(prev_interrupt_state);
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
		case CMDID_NODE_AP_SET_SSID:
            // Set AP SSID
            //
			// NOTE:  This method does not force any maximum length on the SSID.  However,
			//   the rest of the framework enforces the convention that the maximum length
			//   of the SSID is SSID_LEN_MAX.
			//
			// Message format:
			//     cmdArgs32[0]        Command:
			//                           - Write       (CMD_PARAM_WRITE_VAL)
			//                           - Read        (CMD_PARAM_READ_VAL)
			//     cmdArgs32[1]        SSID Length (write-only)
			//     cmdArgs32[2:N]      SSID        (write-only)
            //
			// Response format:
			//     respArgs32[0]       Status
        	//     respArgs32[1]       SSID Length
			//     respArgs32[2:N]     SSID (packed array of ascii character values)
			//                             NOTE: The characters are copied with a straight strcpy
			//                               and must be correctly processed on the host side
            //
        	msg_cmd = Xil_Ntohl(cmdArgs32[0]);
			temp    = Xil_Ntohl(cmdArgs32[1]);
			status  = CMD_PARAM_SUCCESS;

			char * ssid;

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
					ssid = (char *)&cmdArgs32[2];

					// Deauthenticate all stations since we are changing the SSID
					deauthenticate_stations();
					strcpy(my_bss_info->ssid, ssid);
			    break;

				case CMD_PARAM_READ_VAL:
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "AP: SSID = %s\n", my_bss_info->ssid);
				break;

				default:
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
					status = CMD_PARAM_ERROR;
				break;
			}

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );

            // Return the size and current SSID
			if (my_bss_info->ssid != NULL) {
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
		case CMDID_NODE_AP_BEACON_INTERVAL:
            // Command to get / set the time interval between beacons
            //
			// Message format:
			//     cmdArgs32[0]   Command:
			//                      - Write       (CMD_PARAM_WRITE_VAL)
			//                      - Read        (CMD_PARAM_READ_VAL)
			//     cmdArgs32[1]   Number of Time Units (TU) between beacons [1, 65535]
        	//
			// Response format:
			//     respArgs32[0]  Status (CMD_PARAM_SUCCESS/CMD_PARAM_ERROR)
			//     respArgs32[1]  Number of Time Units (TU) between beacons [1, 65535]
            //
        	msg_cmd = Xil_Ntohl(cmdArgs32[0]);
			temp    = Xil_Ntohl(cmdArgs32[1]);
			status  = CMD_PARAM_SUCCESS;

			switch (msg_cmd) {
				case CMD_PARAM_WRITE_VAL:
					beacon_time                  = (temp & 0xFFFF) * BSS_MICROSECONDS_IN_A_TU;
					my_bss_info->beacon_interval = (temp & 0xFFFF);

					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Beacon interval: %d microseconds\n", beacon_time);

					// Start / Restart the beacon event with the new beacon interval
					if (beacon_schedule_id != SCHEDULE_FAILURE) {
						wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Restarting beacon\n");
						wlan_mac_remove_schedule(SCHEDULE_COARSE, beacon_schedule_id);
						beacon_schedule_id = wlan_mac_schedule_event_repeated(SCHEDULE_COARSE, beacon_time, SCHEDULE_REPEAT_FOREVER, (void*)beacon_transmit);
					} else {
						wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Starting beacon\n");
						beacon_schedule_id = wlan_mac_schedule_event_repeated(SCHEDULE_COARSE, beacon_time, SCHEDULE_REPEAT_FOREVER, (void*)beacon_transmit);
					}
			    break;

				case CMD_PARAM_READ_VAL:
					temp = my_bss_info->beacon_interval;
			    break;

				default:
					wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown command for 0x%6x: %d\n", cmdID, msg_cmd);
					status = CMD_PARAM_ERROR;
				break;
			}

			// Send response
            respArgs32[respIndex++] = Xil_Htonl( status );
            respArgs32[respIndex++] = Xil_Htonl( temp );

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
        break;


//-----------------------------------------------------------------------------
// Association Commands
//-----------------------------------------------------------------------------


		//---------------------------------------------------------------------
		case CMDID_NODE_ASSOCIATE:
			// Associate with the device
			//
			// Message format:
			//     cmdArgs32[0]        Association flags
			//                             CMD_PARAM_AP_ASSOCIATE_FLAG_ALLOW_TIMEOUT
			//                             CMD_PARAM_AP_ASSOCIATE_FLAG_STATION_INFO_DO_NOT_REMOVE
			//     cmdArgs32[1]        Association flags mask
			//     cmdArgs32[2:3]      Association MAC Address
			//
			// Response format:
			//     respArgs32[0]       Status
			//
			wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "AP: Associate\n");

			status            = CMD_PARAM_SUCCESS;
            curr_station_info = NULL;

            // Set default value for the flags
            flags             = STATION_INFO_FLAG_DISABLE_ASSOC_CHECK;

			if( my_bss_info->associated_stations.length < wlan_mac_high_get_max_associations() ) {

				// Get MAC Address
				wlan_exp_get_mac_addr(&((u32 *)cmdArgs32)[2], &mac_addr[0]);

				// Get flags
				temp  = Xil_Ntohl(cmdArgs32[0]);
				temp2 = Xil_Ntohl(cmdArgs32[1]);

				wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Associate flags = 0x%08x  mask = 0x%08x\n", temp, temp2);

				// Configure based on the flag bit / mask
				if ( ( temp2 & CMD_PARAM_AP_ASSOCIATE_FLAG_ALLOW_TIMEOUT ) == CMD_PARAM_AP_ASSOCIATE_FLAG_ALLOW_TIMEOUT ) {
					if ( ( temp & CMD_PARAM_AP_ASSOCIATE_FLAG_ALLOW_TIMEOUT ) == CMD_PARAM_AP_ASSOCIATE_FLAG_ALLOW_TIMEOUT ) {
						flags |= STATION_INFO_FLAG_DISABLE_ASSOC_CHECK;
					} else {
						flags &= ~STATION_INFO_FLAG_DISABLE_ASSOC_CHECK;
					}
				}

				if ( ( temp2 & CMD_PARAM_AP_ASSOCIATE_FLAG_STATION_INFO_DO_NOT_REMOVE ) == CMD_PARAM_AP_ASSOCIATE_FLAG_STATION_INFO_DO_NOT_REMOVE ) {
					if ( ( temp & CMD_PARAM_AP_ASSOCIATE_FLAG_STATION_INFO_DO_NOT_REMOVE ) == CMD_PARAM_AP_ASSOCIATE_FLAG_STATION_INFO_DO_NOT_REMOVE ) {
						flags |= STATION_INFO_DO_NOT_REMOVE;
					} else {
						flags &= ~STATION_INFO_DO_NOT_REMOVE;
					}
				}

				// Disable interrupts so no packets interrupt the disassociate
				prev_interrupt_state = wlan_mac_high_interrupt_stop();

				// Add association
				curr_station_info = wlan_mac_high_add_association(&my_bss_info->associated_stations, &statistics_table, &mac_addr[0], ADD_ASSOCIATION_ANY_AID);

				// Set the flags
				curr_station_info->flags = flags;

				// Re-enable interrupts
				wlan_mac_high_interrupt_restore_state(prev_interrupt_state);

				// Set return parameters and print info to console
				if (curr_station_info != NULL) {
					// Log association state change
					add_station_info_to_log(curr_station_info, STATION_INFO_ENTRY_NO_CHANGE, WLAN_EXP_STREAM_ASSOC_CHANGE);

					memcpy(&(curr_station_info->tx), &default_unicast_data_tx_params, sizeof(tx_params));

					// Update the hex display
					ap_write_hex_display(my_bss_info->associated_stations.length);

					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Associated with node: ");
				} else {
					wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Could not associate with node: ");
					status = CMD_PARAM_ERROR;
				}
			} else {
				wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_node, "Could not associate with node: ");
				status = CMD_PARAM_ERROR;
			}

			wlan_exp_print_mac_address(WLAN_EXP_PRINT_INFO, &mac_addr[0]); wlan_exp_printf(WLAN_EXP_PRINT_INFO, NULL, "\n");

			// Send response
			respArgs32[respIndex++] = Xil_Htonl( status );
			if (curr_station_info != NULL ) {
			    respArgs32[respIndex++] = Xil_Htonl( curr_station_info->AID );
			} else {
			    respArgs32[respIndex++] = Xil_Htonl( 0 );
			}

			respHdr->length += (respIndex * sizeof(respArgs32));
			respHdr->numArgs = respIndex;
		break;


        //---------------------------------------------------------------------
		default:
			wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_node, "Unknown node command: 0x%x\n", cmdID);
		break;
	}

	return respSent;
}


#endif
