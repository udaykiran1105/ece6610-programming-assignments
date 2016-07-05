/** @file wlan_mac_ibss.c
 *  @brief Station
 *
 *  This contains code for the 802.11 IBSS node (ad hoc).
 *
 *  @copyright Copyright 2014-2015, Mango Communications. All rights reserved.
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
#include "wlan_mac_ibss_join_fsm.h"
#include "ascii_characters.h"
#include "wlan_mac_schedule.h"
#include "wlan_mac_dl_list.h"
#include "wlan_mac_bss_info.h"
#include "wlan_mac_ibss.h"

// WLAN Exp includes
#include "wlan_exp.h"
#include "wlan_exp_common.h"
#include "wlan_exp_node.h"
#include "wlan_exp_node_ibss.h"
#include "wlan_exp_transport.h"

/*************************** Constant Definitions ****************************/

#define  WLAN_EXP_ETH                            WN_ETH_B
#define  WLAN_EXP_NODE_TYPE                      (WARPNET_TYPE_80211_BASE + WARPNET_TYPE_80211_HIGH_IBSS)
#define  WLAN_EXP_TYPE_MASK                      (WARPNET_TYPE_BASE_MASK + WARPNET_TYPE_80211_HIGH_MASK)

#define  WLAN_DEFAULT_CHANNEL                    1
#define  WLAN_DEFAULT_TX_PWR                     15

#define  SCAN_TIMEOUT_SEC                        5
#define  SCAN_TIMEOUT_USEC                       (SCAN_TIMEOUT_SEC*1000000)


/*********************** Global Variable Definitions *************************/


/*************************** Variable Definitions ****************************/

// If you want this station to try to associate to a known IBSS at boot, type
//   the string here. Otherwise, let it be an empty string.
static char                       default_ssid[SSID_LEN_MAX + 1] = "WARP-IBSS";
// static char                       default_ssid[SSID_LEN_MAX + 1] = "";


// Common TX header for 802.11 packets
mac_header_80211_common           tx_header_common;

// Default transmission parameters
tx_params                         default_unicast_mgmt_tx_params;
tx_params                         default_unicast_data_tx_params;
tx_params                         default_multicast_mgmt_tx_params;
tx_params                         default_multicast_data_tx_params;

// Top level IBSS state
bss_info*                         my_bss_info;

// List to hold Tx/Rx statistics
dl_list		                      statistics_table;

// Tx queue variables;
static u32                        max_queue_size;
volatile u8                       pause_data_queue;

// Default channel
volatile u32                      mac_param_chan;

// MAC address
static u8 	                      wlan_mac_addr[6];

// Beacon variables
volatile u32                      beacon_schedule_id = SCHEDULE_FAILURE;
volatile u8                       enable_beacon_tx;
volatile u8	                      allow_beacon_ts_update;            // Allow timebase to be updated from beacons



/*************************** Functions Prototypes ****************************/


/******************************** Functions **********************************/

int main() {
	u64                scan_start_timestamp;
	u8                 locally_administered_addr[6];
	bss_info         * temp_bss_info;
	wlan_mac_hw_info * hw_info;

	// Default Channels
	u8                 channel_selections[14] = {1,2,3,4,5,6,7,8,9,10,11,36,44,48};


	// Print initial message to UART
	xil_printf("\f");
	xil_printf("----- Mango 802.11 Reference Design -----\n");
	xil_printf("----- v1.3 ------------------------------\n");
	xil_printf("----- wlan_mac_ibss ---------------------\n");
	xil_printf("Compiled %s %s\n\n", __DATE__, __TIME__);

	// This function should be executed first. It will zero out memory, and if that
	//     memory is used before calling this function, unexpected results may happen.
	wlan_mac_high_heap_init();

	// Initialize the maximum TX queue size
	max_queue_size = MAX_TX_QUEUE_LEN;

	// Set default behavior
	pause_data_queue       = 0;
	enable_beacon_tx       = 1;
	allow_beacon_ts_update = 1;

	// Set my_bss_info to NULL (ie IBSS is not currently on a BSS)
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
	wlan_mac_util_set_eth_encap_mode(ENCAP_MODE_IBSS);

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
	wlan_exp_set_init_callback(                     (void *)wlan_exp_node_ibss_init);
	wlan_exp_set_process_callback(                  (void *)wlan_exp_node_ibss_processCmd);
	wlan_exp_set_reset_station_statistics_callback( (void *)reset_station_statistics);
	wlan_exp_set_purge_all_data_tx_queue_callback(  (void *)purge_all_data_tx_queue);
	wlan_exp_set_reset_all_associations_callback(   (void *)leave_ibss);
	wlan_exp_set_reset_bss_info_callback(           (void *)reset_bss_info);
	wlan_exp_set_timebase_adjust_callback(          (void *)association_timestamp_adjust);
	wlan_exp_set_tx_cmd_add_association_callback(   (void *)wlan_exp_ibss_tx_cmd_add_association);

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

	// Set the hex display initial value
	ibss_write_hex_display(0);

	// Reset the event log
	event_log_reset();

	// Print Station information to the terminal
    xil_printf("WLAN MAC IBSS boot complete: \n");
	xil_printf("  MAC Addr     : %02x-%02x-%02x-%02x-%02x-%02x\n\n",wlan_mac_addr[0],wlan_mac_addr[1],wlan_mac_addr[2],wlan_mac_addr[3],wlan_mac_addr[4],wlan_mac_addr[5]);

#ifdef WLAN_USE_UART_MENU
	xil_printf("\nPress the Esc key in your terminal to access the UART menu\n");
#endif

	// Start the interrupts
	wlan_mac_high_interrupt_restore_state(INTERRUPTS_ENABLED);

	// Set the default active scan channels
	wlan_mac_set_scan_channels(channel_selections, sizeof(channel_selections)/sizeof(channel_selections[0]));


	// If there is a default SSID and the DIP switch allows it, initiate a probe request
	if( (strlen(default_ssid) > 0) && ((wlan_mac_high_get_user_io_state()&GPIO_MASK_DS_3) == 0)) {
		wlan_mac_ibss_scan_and_join(default_ssid, SCAN_TIMEOUT_SEC);
		scan_start_timestamp = get_usec_timestamp();
		while((get_usec_timestamp() < (scan_start_timestamp + SCAN_TIMEOUT_USEC))){
			if(my_bss_info != NULL){
				break;
			}
		}

		if(my_bss_info == NULL){
			xil_printf("Unable to find '%s' IBSS. Creating new network.\n",default_ssid);

			memcpy(locally_administered_addr,wlan_mac_addr,6);
			locally_administered_addr[0] |= MAC_ADDR_MSB_MASK_LOCAL; //Raise the bit identifying this address as locally administered
			temp_bss_info = wlan_mac_high_create_bss_info(locally_administered_addr, default_ssid, WLAN_DEFAULT_CHANNEL);
			temp_bss_info->beacon_interval = BEACON_INTERVAL_TU;
			temp_bss_info->state = BSS_STATE_OWNED;
			temp_bss_info->capabilities = (CAPABILITIES_SHORT_TIMESLOT | CAPABILITIES_IBSS);
			wlan_mac_ibss_join( temp_bss_info );
		}
	}

	wlan_mac_schedule_event_repeated(SCHEDULE_COARSE, ASSOCIATION_CHECK_INTERVAL_US, SCHEDULE_REPEAT_FOREVER, (void*)association_timestamp_check);


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



void ibss_set_association_state( bss_info* new_bss_info ){

	leave_ibss();

	mac_param_chan = new_bss_info->chan;
	wlan_mac_high_set_channel(mac_param_chan);

	my_bss_info = new_bss_info;

	xil_printf("IBSS Details: \n");
	xil_printf("  BSSID           : %02x-%02x-%02x-%02x-%02x-%02x\n",my_bss_info->bssid[0],my_bss_info->bssid[1],my_bss_info->bssid[2],my_bss_info->bssid[3],my_bss_info->bssid[4],my_bss_info->bssid[5]);
	xil_printf("   SSID           : %s\n", my_bss_info->ssid);
	xil_printf("   Channel        : %d\n", my_bss_info->chan);
	xil_printf("   Beacon Interval: %d TU (%d us)\n",my_bss_info->beacon_interval, my_bss_info->beacon_interval*1024);


	//802.11-2012 10.1.3.3 Beacon generation in an IBSS
	//Note: Unlike the AP implementation, we need to use the SCHEDULE_FINE scheduler sub-beacon-interval fidelity
	if(enable_beacon_tx) beacon_schedule_id = wlan_mac_schedule_event_repeated(SCHEDULE_FINE, (my_bss_info->beacon_interval)*1024, 1, (void*)beacon_transmit);
}


/**
 * @brief Transmit a beacon
 *
 * This function will create and enqueue a beacon.
 *
 * @param  None
 * @return None
 */
void beacon_transmit(u32 schedule_id) {

 	u16 tx_length;
 	tx_queue_element*	curr_tx_queue_element;
 	tx_queue_buffer* 	curr_tx_queue_buffer;

	if(my_bss_info != NULL && enable_beacon_tx == 1){

		//When an IBSS node receives a beacon, it schedules the call of this beacon_transmit function
		//for some point in the future that is generally less than the beacon interval to account for
		//the delay in reception and processing. As such, this function will update the period of this
		//schedule with the actual beacon interval.

		beacon_schedule_id = wlan_mac_schedule_event_repeated(SCHEDULE_FINE, (my_bss_info->beacon_interval)*1024, 1, (void*)beacon_transmit);

		// Create a beacon
		curr_tx_queue_element = queue_checkout();

		if((curr_tx_queue_element != NULL) && (my_bss_info != NULL)){
			curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

			// Setup the TX header
			wlan_mac_high_setup_tx_header( &tx_header_common, (u8 *)bcast_addr, my_bss_info->bssid );

			// Fill in the data
			tx_length = wlan_create_beacon_frame(
				(void*)(curr_tx_queue_buffer->frame),
				&tx_header_common,
				my_bss_info);

			// Setup the TX frame info
			wlan_mac_high_setup_tx_frame_info ( &tx_header_common, curr_tx_queue_element, tx_length, (TX_MPDU_FLAGS_FILL_TIMESTAMP | TX_MPDU_FLAGS_REQ_BO | TX_MPDU_FLAGS_AUTOCANCEL), BEACON_QID );

			// Set the information in the TX queue buffer
			curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
			curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(&default_multicast_mgmt_tx_params);
			curr_tx_queue_buffer->frame_info.AID         = 0;

			// Put the packet in the queue
			enqueue_after_tail(BEACON_QID, curr_tx_queue_element);

		}
	}
}


/**
 * @brief Poll Tx queues to select next available packet to transmit
 *
 * @param None
 * @return None
 */
void poll_tx_queues(){
	u32 i,k;

	#define NUM_QUEUE_GROUPS 3
	typedef enum {BEACON_QGRP, MGMT_QGRP, DATA_QGRP} queue_group_t;

	// Remember the next group to poll between calls to this function
	//   This implements the ping-pong poll between the MGMT_QGRP and DATA_QGRP groups
	static queue_group_t next_queue_group = MGMT_QGRP;
	queue_group_t curr_queue_group;

	// Remember the last queue polled between calls to this function
	//   This implements the round-robin poll of queues in the DATA_QGRP group
	static dl_entry* next_station_info_entry = NULL;
	dl_entry* curr_station_info_entry;

	station_info* curr_station_info;

	if( wlan_mac_high_is_ready_for_tx() ){
		for(k = 0; k < NUM_QUEUE_GROUPS; k++){
			curr_queue_group = next_queue_group;

			switch(curr_queue_group){
				case BEACON_QGRP:
					next_queue_group = MGMT_QGRP;
					if(dequeue_transmit_checkin(BEACON_QID)){
						return;
					}
				break;

				case MGMT_QGRP:
					next_queue_group = DATA_QGRP;
					if(dequeue_transmit_checkin(MANAGEMENT_QID)){
						return;
					}
				break;

				case DATA_QGRP:
					next_queue_group = BEACON_QGRP;
					curr_station_info_entry = next_station_info_entry;

					if(my_bss_info != NULL){
						for(i = 0; i < (my_bss_info->associated_stations.length + 1); i++) {
							// Loop through all associated stations' queues and the broadcast queue
							if(curr_station_info_entry == NULL){
								// Check the broadcast queue
								next_station_info_entry = my_bss_info->associated_stations.first;
								if(dequeue_transmit_checkin(MCAST_QID)){
									// Found a not-empty queue, transmitted a packet
									return;
								} else {
									curr_station_info_entry = next_station_info_entry;
								}
							} else {
								curr_station_info = (station_info*)(curr_station_info_entry->data);
								if( wlan_mac_high_is_valid_association(&my_bss_info->associated_stations, curr_station_info) ){
									if(curr_station_info_entry == my_bss_info->associated_stations.last){
										// We've reached the end of the table, so we wrap around to the beginning
										next_station_info_entry = NULL;
									} else {
										next_station_info_entry = dl_entry_next(curr_station_info_entry);
									}

									if(dequeue_transmit_checkin(AID_TO_QID(curr_station_info->AID))){
										// Found a not-empty queue, transmitted a packet
										return;
									} else {
										curr_station_info_entry = next_station_info_entry;
									}
								} else {
									// This curr_station_info is invalid. Perhaps it was removed from
									// the association table before poll_tx_queues was called. We will
									// start the round robin checking back at broadcast.
									next_station_info_entry = NULL;
									return;
								} // END if(is_valid_association)
							}
						} // END for loop over association table
					} else {
						if(dequeue_transmit_checkin(MCAST_QID)){
							// Found a not-empty queue, transmitted a packet
							return;
						}
					}
				break;
			} // END switch(queue group)
		} // END loop over queue groups
	} // END CPU low is ready
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
	dl_entry*	  curr_station_info_entry;
	station_info* curr_station_info;

	// Purge all data transmit queues
	purge_queue(MCAST_QID);                                    		// Broadcast Queue

	if(my_bss_info != NULL){
		curr_station_info_entry = my_bss_info->associated_stations.first;
		while(curr_station_info_entry != NULL){
			curr_station_info = (station_info*)(curr_station_info_entry->data);
			purge_queue(AID_TO_QID(curr_station_info->AID));       		// Each unicast queue
			curr_station_info_entry = dl_entry_next(curr_station_info_entry);
		}
	}
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
	dl_entry*              entry                   = NULL;
	station_info*          station 				   = NULL;

	if(my_bss_info != NULL){
		if(tx_mpdu->AID != 0){
			entry = wlan_mac_high_find_station_info_AID(&(my_bss_info->associated_stations), tx_mpdu->AID);
			if(entry != NULL){
				station = (station_info*)(entry->data);
			}
		}
	}

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
	station_info*       associated_station;
	u32                 queue_sel;

	if(my_bss_info != NULL){

		// Send the pre-encapsulated Ethernet frame over the wireless interface
		//     NOTE:  The queue element has already been provided, so we do not need to check if it is NULL
		curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

		// Setup the TX header
		wlan_mac_high_setup_tx_header( &tx_header_common, eth_dest,my_bss_info->bssid);

		// Fill in the data
		wlan_create_data_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, 0);

		if( wlan_addr_mcast(eth_dest) ){
			// Setup the TX frame info
				queue_sel = MCAST_QID;
				wlan_mac_high_setup_tx_frame_info ( &tx_header_common, curr_tx_queue_element, tx_length, ( 0 ), queue_sel );

				// Set the information in the TX queue buffer
				curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
				curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(&default_multicast_data_tx_params);
				curr_tx_queue_buffer->frame_info.AID         = 0;
		} else {
			associated_station = wlan_mac_high_add_association(&my_bss_info->associated_stations, &statistics_table, eth_dest, ADD_ASSOCIATION_ANY_AID);
			ibss_write_hex_display(my_bss_info->associated_stations.length);
			//Note: the above function will not create a new station_info if it already exists for this address in the associated_stations list

			if(associated_station == NULL){
				//If we don't have a station_info for this frame, we'll stick it in the multicast queue as a catch all
				queue_sel = MCAST_QID;
				// Setup the TX frame info
				wlan_mac_high_setup_tx_frame_info ( &tx_header_common, curr_tx_queue_element, tx_length, (TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO), queue_sel );
				curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
				curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(&default_unicast_data_tx_params);
				curr_tx_queue_buffer->frame_info.AID         = 0;
			} else {
				queue_sel = AID_TO_QID(associated_station->AID);
				// Setup the TX frame info
				wlan_mac_high_setup_tx_frame_info ( &tx_header_common, curr_tx_queue_element, tx_length, (TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO), queue_sel );
				associated_station->latest_activity_timestamp = get_usec_timestamp();
				curr_tx_queue_buffer->metadata.metadata_type  = QUEUE_METADATA_TYPE_STATION_INFO;
				curr_tx_queue_buffer->metadata.metadata_ptr   = (u32)associated_station;
				curr_tx_queue_buffer->frame_info.AID          = associated_station->AID;
			}

		}

		if(queue_num_queued(queue_sel) < max_queue_size){
			// Put the packet in the queue
			enqueue_after_tail(queue_sel, curr_tx_queue_element);

		} else {
			// Packet was not successfully enqueued
			return 0;
		}

		// Packet was successfully enqueued
		return 1;
	} else {
		return 0;
	}
}



/**
 * @brief Process received MPDUs
 *
 * This callback function will process all the received MPDUs.
 *
 * This function must implement the state machine that will allow associaton with other IBSS nodes in the same BSS.
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

	station_info*       associated_station       = NULL;
	statistics_txrx*    station_stats            = NULL;

	tx_queue_element*   curr_tx_queue_element;
	tx_queue_buffer*    curr_tx_queue_buffer;

	u8                  unicast_to_me;
	u8                  to_multicast;
	s64                 timestamp_diff;
	u8					send_response			 = 0;
	u32					tx_length;
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
			if(wlan_addr_eq(rx_80211_header->address_3, my_bss_info->bssid)){
				associated_station = wlan_mac_high_add_association(&my_bss_info->associated_stations, &statistics_table, rx_80211_header->address_2, ADD_ASSOCIATION_ANY_AID);
				ibss_write_hex_display(my_bss_info->associated_stations.length);
			}
		} else {
			associated_station = NULL;
		}

		if(associated_station != NULL) {

			// Update station information
			associated_station->latest_activity_timestamp = get_usec_timestamp();
			associated_station->rx.last_power             = mpdu_info->rx_power;
			associated_station->rx.last_rate              = rate;

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
					if(my_bss_info != NULL){
						if(wlan_addr_eq(rx_80211_header->address_3, my_bss_info->bssid)) {
							// MPDU is flagged as destined to the DS - send it for de-encapsulation and Ethernet Tx (if appropriate)
							wlan_mpdu_eth_send(mpdu, length, pre_llc_offset);
						}
					}
				break;

				//---------------------------------------------------------------------
				case (MAC_FRAME_CTRL1_SUBTYPE_PROBE_REQ):
					if(my_bss_info != NULL){
						if(wlan_addr_eq(rx_80211_header->address_3, bcast_addr)) {
							mpdu_ptr_u8 += sizeof(mac_header_80211);

							// Loop through tagged parameters
							while(((u32)mpdu_ptr_u8 -  (u32)mpdu)<= (length - WLAN_PHY_FCS_NBYTES)){

								// What kind of tag is this?
								switch(mpdu_ptr_u8[0]){
									//-----------------------------------------------------
									case TAG_SSID_PARAMS:
										// SSID parameter set
										if((mpdu_ptr_u8[1]==0) || (memcmp(mpdu_ptr_u8+2, (u8*)default_ssid, mpdu_ptr_u8[1])==0)) {
											// Broadcast SSID or my SSID - send unicast probe response
											send_response = 1;
										}
									break;

									//-----------------------------------------------------
									case TAG_SUPPORTED_RATES:
										// Supported rates
									break;

									//-----------------------------------------------------
									case TAG_EXT_SUPPORTED_RATES:
										// Extended supported rates
									break;

									//-----------------------------------------------------
									case TAG_DS_PARAMS:
										// DS Parameter set (e.g. channel)
									break;
								}

								// Move up to the next tag
								mpdu_ptr_u8 += mpdu_ptr_u8[1]+2;
							}

							if(send_response) {
								// Create a probe response frame
								curr_tx_queue_element = queue_checkout();

								if(curr_tx_queue_element != NULL){
									curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

									// Setup the TX header
									wlan_mac_high_setup_tx_header( &tx_header_common, rx_80211_header->address_2, my_bss_info->bssid );

									// Fill in the data
									tx_length = wlan_create_probe_resp_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, my_bss_info);

									// Setup the TX frame info
									wlan_mac_high_setup_tx_frame_info ( &tx_header_common, curr_tx_queue_element, tx_length, (TX_MPDU_FLAGS_FILL_TIMESTAMP | TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO), MANAGEMENT_QID );

									// Set the information in the TX queue buffer
									curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
									curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(&default_unicast_mgmt_tx_params);
									curr_tx_queue_buffer->frame_info.AID         = 0;

									// Put the packet in the queue
									enqueue_after_tail(MANAGEMENT_QID, curr_tx_queue_element);

								}

								// Finish the function
								goto mpdu_rx_process_end;
							}
						}
					}
				break;

				//---------------------------------------------------------------------
				case (MAC_FRAME_CTRL1_SUBTYPE_BEACON):
					// Beacon Packet
					//   -
					//

					// Define the PHY timestamp offset
					#define PHY_T_OFFSET 25

					// Update the timestamp from the beacon
					if(my_bss_info != NULL){
						// If this packet was from our IBSS
						if( wlan_addr_eq( my_bss_info->bssid, rx_80211_header->address_3)){



							// Move the packet pointer to after the header
							mpdu_ptr_u8 += sizeof(mac_header_80211);

							// Calculate the difference between the beacon timestamp and the packet timestamp
							//     NOTE:  We need to compensate for the time it takes to set the timestamp in the PHY
							timestamp_diff = (s64)(((beacon_probe_frame*)mpdu_ptr_u8)->timestamp) - (s64)(mpdu_info->timestamp) + PHY_T_OFFSET;

							// Set the timestamp
							if( allow_beacon_ts_update == 1 ){
								if(timestamp_diff > 0){

									if(abs_64(timestamp_diff) >= (10*1024*my_bss_info->beacon_interval)){
										association_timestamp_adjust(timestamp_diff);
									}

									wlan_mac_high_set_timestamp_delta(timestamp_diff);
								}

								// We need to adjust the phase of our TBTT. To do this, we will kill the old schedule event, and restart now (which is near the TBTT)
								if(beacon_schedule_id != SCHEDULE_FAILURE){
									wlan_mac_remove_schedule(SCHEDULE_FINE, beacon_schedule_id);
									timestamp_diff = get_usec_timestamp() - ((beacon_probe_frame*)mpdu_ptr_u8)->timestamp;
									beacon_schedule_id = wlan_mac_schedule_event_repeated(SCHEDULE_FINE, (my_bss_info->beacon_interval)*1024 - timestamp_diff, 1, (void*)beacon_transmit);
								}
							}
							if(queue_num_queued(BEACON_QID)){

								//We should destroy the beacon that is currently enqueued if
								//it exists. Note: these statements aren't typically executed.
								//It's very likely the to-be-transmitted BEACON is already down
								//in CPU_LOW's domain and needs to be cancelled there.
								curr_tx_queue_element = dequeue_from_head(BEACON_QID);
								if(curr_tx_queue_element != NULL){
									queue_checkin(curr_tx_queue_element);
									wlan_eth_dma_update();
								}
							}

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
 * @brief Check the time since the station has interacted with another station
 *
 *
 * @param  None
 * @return None
 */
void association_timestamp_check() {

	u64 				time_since_last_activity;
	station_info*       curr_station_info;
	dl_entry*           curr_station_info_entry;
	dl_entry*           next_station_info_entry;

	if(my_bss_info != NULL){
		next_station_info_entry = my_bss_info->associated_stations.first;

		while(next_station_info_entry != NULL) {
			curr_station_info_entry = next_station_info_entry;
			next_station_info_entry = dl_entry_next(curr_station_info_entry);

			curr_station_info        = (station_info*)(curr_station_info_entry->data);
			time_since_last_activity = (get_usec_timestamp() - curr_station_info->latest_activity_timestamp);

			// De-authenticate the station if we have timed out and we have not disabled this check for the station
			if((time_since_last_activity > ASSOCIATION_TIMEOUT_US) && ((curr_station_info->flags & STATION_INFO_FLAG_DISABLE_ASSOC_CHECK) == 0)){
                purge_queue(AID_TO_QID(curr_station_info->AID));
				wlan_mac_high_remove_association( &my_bss_info->associated_stations, &statistics_table, curr_station_info->addr );
				ibss_write_hex_display(my_bss_info->associated_stations.length);
			}
		}
	}
}

/**
 * @brief Update the last activity timestamps for all associated nodes
 *
 * In the current architecture, the last activity timestamps used the same usec counter than
 * can be modified by beacon receptions (in the case of IBSS) or by WLAN_EXP. This can lead
 * to unexpected timeouts by association_timestamp_check(). This function should be called
 * prior to large changes in the underlying timebase to prevent this from occuring.
 *
 * @param  s64 timestamp_diff
 *  - number of usec that timestamps should be adjusted forward or backward
 * @return None
 */
void association_timestamp_adjust(s64 timestamp_diff){
    station_info*       curr_station_info;
    dl_entry*           curr_station_info_entry;
    dl_entry*           next_station_info_entry;
    
    if(my_bss_info != NULL){
        next_station_info_entry = my_bss_info->associated_stations.first;
        
        while(next_station_info_entry != NULL) {
            curr_station_info_entry = next_station_info_entry;
            next_station_info_entry = dl_entry_next(curr_station_info_entry);
            
            curr_station_info        = (station_info*)(curr_station_info_entry->data);
            (curr_station_info->latest_activity_timestamp) += timestamp_diff;
        }
    }
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

	u32               payload_length;
	u32               min_ltg_payload_length;
	dl_entry*	      station_info_entry           = NULL;
	station_info*     station                      = NULL;
	u8*               addr_da;
	u8                is_multicast;
	u8                queue_sel;
	tx_queue_element* curr_tx_queue_element        = NULL;
	tx_queue_buffer*  curr_tx_queue_buffer         = NULL;
	u8                continue_loop;

	if(my_bss_info != NULL){
		switch(((ltg_pyld_hdr*)callback_arg)->type){
			case LTG_PYLD_TYPE_FIXED:
				payload_length = ((ltg_pyld_fixed*)callback_arg)->length;
				addr_da = ((ltg_pyld_fixed*)callback_arg)->addr_da;
				is_multicast = wlan_addr_mcast(addr_da);
				if(is_multicast){
					queue_sel = MCAST_QID;
				} else {
					station_info_entry = wlan_mac_high_find_station_info_ADDR(&my_bss_info->associated_stations, addr_da);
					if(station_info_entry != NULL){
						station = (station_info*)(station_info_entry->data);
						queue_sel = AID_TO_QID(station->AID);
					} else {
						//Unlike the AP, this isn't necessarily a criteria for giving up on this LTG event.
						//In the IBSS, it's possible that there simply wasn't room in the heap for a station_info,
						//but we should still send it a packet. We'll use the multi-cast queue as a catch-all queue for these frames.
						queue_sel = MCAST_QID;
					}
				}
			break;

			case LTG_PYLD_TYPE_UNIFORM_RAND:
				payload_length = (rand()%(((ltg_pyld_uniform_rand*)(callback_arg))->max_length - ((ltg_pyld_uniform_rand*)(callback_arg))->min_length))+((ltg_pyld_uniform_rand*)(callback_arg))->min_length;
				addr_da = ((ltg_pyld_fixed*)callback_arg)->addr_da;

				is_multicast = wlan_addr_mcast(addr_da);
				if(is_multicast){
					queue_sel = MCAST_QID;
				} else {
					station_info_entry = wlan_mac_high_find_station_info_ADDR(&my_bss_info->associated_stations, addr_da);
					if(station_info_entry != NULL){
						station = (station_info*)(station_info_entry->data);
						queue_sel = AID_TO_QID(station->AID);
					} else {
						//Unlike the AP, this isn't necessarily a criteria for giving up on this LTG event.
						//In the IBSS, it's possible that there simply wasn't room in the heap for a station_info,
						//but we should still send it a packet. We'll use the multi-cast queue as a catch-all queue for these frames.
						queue_sel = MCAST_QID;
					}
				}
			break;

			case LTG_PYLD_TYPE_ALL_ASSOC_FIXED:
				if(my_bss_info->associated_stations.length > 0){
					station_info_entry = my_bss_info->associated_stations.first;
					station = (station_info*)station_info_entry->data;
					addr_da = station->addr;
					queue_sel = AID_TO_QID(station->AID);
					is_multicast = 0;
					payload_length = ((ltg_pyld_all_assoc_fixed*)callback_arg)->length;
				} else {
					return;
				}
			break;

			default:
				xil_printf("ERROR ltg_event: Unknown LTG Payload Type! (%d)\n", ((ltg_pyld_hdr*)callback_arg)->type);
				return;
			break;
		}

		if(is_multicast == 0){
			wlan_mac_high_add_association(&my_bss_info->associated_stations, &statistics_table, addr_da, ADD_ASSOCIATION_ANY_AID);
			//Note: the above function will not create a new station_info if it already exists for this address in the associated_stations list
			ibss_write_hex_display(my_bss_info->associated_stations.length);
		}


		do{
			continue_loop = 0;

			if(queue_num_queued(queue_sel) < max_queue_size){
				// Checkout 1 element from the queue;
				curr_tx_queue_element = queue_checkout();
				if(curr_tx_queue_element != NULL){
					// Create LTG packet
					curr_tx_queue_buffer = ((tx_queue_buffer*)(curr_tx_queue_element->data));

					// Setup the MAC header
					wlan_mac_high_setup_tx_header( &tx_header_common, addr_da, my_bss_info->bssid );

					min_ltg_payload_length = wlan_create_ltg_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, MAC_FRAME_CTRL2_FLAG_FROM_DS, id);
					payload_length = max(payload_length+sizeof(mac_header_80211)+WLAN_PHY_FCS_NBYTES, min_ltg_payload_length);

					// Finally prepare the 802.11 header
					if (is_multicast) {
						wlan_mac_high_setup_tx_frame_info ( &tx_header_common, curr_tx_queue_element, payload_length, (TX_MPDU_FLAGS_FILL_DURATION), queue_sel);
					} else {
						wlan_mac_high_setup_tx_frame_info ( &tx_header_common, curr_tx_queue_element, payload_length, (TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO), queue_sel);
					}

					// Update the queue entry metadata to reflect the new new queue entry contents
					if (is_multicast) {
						curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
						curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)&default_multicast_data_tx_params;
						curr_tx_queue_buffer->frame_info.AID     = 0;
					} else if(station == NULL){
						curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
						curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)&default_unicast_data_tx_params;
						curr_tx_queue_buffer->frame_info.AID     = 0;
					} else {

					    curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_STATION_INFO;
					    curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)station;
						curr_tx_queue_buffer->frame_info.AID         = station->AID;
					}

					// Submit the new packet to the appropriate queue
					enqueue_after_tail(queue_sel, curr_tx_queue_element);


				} else {
					// There aren't any free queue elements right now.
					// As such, there probably isn't any point to continuing this callback.
					// We'll return and try again once it is called the next time.
					return;
				}
			}

			if(((ltg_pyld_hdr*)callback_arg)->type == LTG_PYLD_TYPE_ALL_ASSOC_FIXED){
				station_info_entry = dl_entry_next(station_info_entry);
				if(station_info_entry != NULL){
					station = (station_info*)station_info_entry->data;
					addr_da = station->addr;
					queue_sel = AID_TO_QID(station->AID);
					is_multicast = 0;
					continue_loop = 1;
				} else {
					continue_loop = 0;
				}
			} else {
				continue_loop = 0;
			}
		} while(continue_loop == 1);
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
 * @brief Leave the IBSS
 *
 * Removes the node from the BSS and resets all peer station_info
 *
 * @param  None
 * @return None
 */
void leave_ibss(){

	xil_printf("Resetting IBSS state (current BSS and all peer station_info structs)\n");

	if(my_bss_info != NULL){

		station_info* curr_station_info;
		dl_entry* next_station_info_entry;
		dl_entry* curr_station_info_entry;

		next_station_info_entry = my_bss_info->associated_stations.first;

		while(next_station_info_entry != NULL){
			curr_station_info_entry = next_station_info_entry;
			next_station_info_entry = dl_entry_next(curr_station_info_entry);
			curr_station_info = (station_info*)(curr_station_info_entry->data);
            purge_queue(AID_TO_QID(curr_station_info->AID));
			wlan_mac_high_remove_association( &my_bss_info->associated_stations, &statistics_table, curr_station_info->addr );
			ibss_write_hex_display(my_bss_info->associated_stations.length);
		}

		my_bss_info = NULL;

		if(beacon_schedule_id != SCHEDULE_FAILURE){
			wlan_mac_remove_schedule(SCHEDULE_FINE, beacon_schedule_id);
		}
	}
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
		break;
	}

}

/**
 * @brief Write a Decimal Value to the Hex Display
 *
 * This function will write a decimal value to the board's two-digit hex displays.
 * For the IBSS, the display is right justified; WARPNet will indicate its connection
 * state using the right decimal point.
 *
 * @param u8 val
 *  - Value to be displayed (between 0 and 99)
 * @return None
 *
 */
void ibss_write_hex_display(u8 val){
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



