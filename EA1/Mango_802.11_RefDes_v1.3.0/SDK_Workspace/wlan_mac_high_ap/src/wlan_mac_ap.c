/** @file wlan_mac_ap.c
 *  @brief Access Point
 *
 *  This contains code for the 802.11 Access Point.
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

//Xilinx SDK includes
#include "stdio.h"
#include "stdlib.h"
#include "xtmrctr.h"
#include "xio.h"
#include "string.h"
#include "xintc.h"
#include "xparameters.h"

//802.11 ref design includes
#include "w3_userio.h"
#include "wlan_mac_addr_filter.h"
#include "wlan_mac_ipc_util.h"
#include "wlan_mac_misc_util.h"
#include "wlan_mac_802_11_defs.h"
#include "wlan_mac_queue.h"
#include "wlan_mac_ltg.h"
#include "wlan_mac_high.h"
#include "wlan_mac_packet_types.h"
#include "wlan_mac_eth_util.h"
#include "wlan_mac_event_log.h"
#include "wlan_mac_entries.h"
#include "wlan_mac_ap.h"
#include "wlan_mac_schedule.h"
#include "wlan_mac_dl_list.h"
#include "ascii_characters.h"
#include "wlan_mac_bss_info.h"
#include "wlan_mac_mgmt_tags.h"

// Experiments framework includes
#include "wlan_exp.h"
#include "wlan_exp_common.h"
#include "wlan_exp_node.h"
#include "wlan_exp_node_ap.h"
#include "wlan_exp_transport.h"


/*************************** Constant Definitions ****************************/
#define  WLAN_EXP_ETH                           WN_ETH_B 
#define  WLAN_EXP_NODE_TYPE                     (WARPNET_TYPE_80211_BASE + WARPNET_TYPE_80211_HIGH_AP)
#define  WLAN_EXP_TYPE_MASK                     (WARPNET_TYPE_BASE_MASK + WARPNET_TYPE_80211_HIGH_MASK)

#define  WLAN_DEFAULT_CHANNEL                   1
#define  WLAN_DEFAULT_TX_PWR		            15

#define  WLAN_DEFAULT_BEACON_INTERVAL_TU        100

/*********************** Global Variable Definitions *************************/


/*************************** Variable Definitions ****************************/

// SSID variables
static char                       default_AP_SSID[] = "WARP-AP";

// Common TX header for 802.11 packets
static mac_header_80211_common    tx_header_common;

// Default Transmission Parameters
tx_params                         default_unicast_mgmt_tx_params;
tx_params                         default_unicast_data_tx_params;
tx_params                         default_multicast_mgmt_tx_params;
tx_params                         default_multicast_data_tx_params;

// "my_bss_info" is a pointer to the bss_info that describes this AP.
// Inside this structure is a dl_list of station_info. This is a list
// of all stations that are currently associated with this AP. In the
// 802.11-2012 Section 10.3 parlance, these stations are currently
// in State 4 (Authenticated, Associated). As part of the association
// process, we want to track stations as they transition through the
// 10.3 states. To do this, we'll create a totally separate dl_list of
// station_info that represent stations in State 2
// (Authenticated, Unassociated). Only members of this list will be allowed
// to elevate to State 4 in the my_bss_info.
bss_info*	                      my_bss_info;

dl_list		                      statistics_table;
dl_list		                      station_info_state_2;

// Tx queue variables;
static u32                        max_queue_size;

// AP channel
volatile u32                      mac_param_chan;

// MAC address
static u8 	                      wlan_mac_addr[6];

// Traffic Indication Map State
volatile ps_conf                  power_save_configuration;

// Beacon variables
volatile u32                      beacon_schedule_id = SCHEDULE_FAILURE;



/*************************** Functions Prototypes ****************************/

u8   sevenSegmentMap(u8 x);


/******************************** Functions **********************************/

int main(){
	wlan_mac_hw_info *hw_info;
	u8 disallow_filter[6] = {0x00,0x00,0x00,0x00,0x00,0x00};
	u8 disallow_mask[6]   = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};


	xil_printf("\f");
	xil_printf("----- Mango 802.11 Reference Design -----\n");
	xil_printf("----- v1.3 ------------------------------\n");
	xil_printf("----- wlan_mac_ap -----------------------\n");

	xil_printf("Compiled %s %s\n\n", __DATE__, __TIME__);

	//heap_init() must be executed before any use of malloc. This explicit init
	// handles the case of soft-reset of the MicroBlaze leaving stale values in the heap RAM
	wlan_mac_high_heap_init();

	//Initialize the MAC framework
	wlan_mac_high_init();

	//Define the default PHY and MAC params for all transmissions

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

	// Setup the stats lists
	dl_list_init(&statistics_table);

	// Set the maximum associations
	wlan_mac_high_set_max_associations(MAX_NUM_ASSOC);

	// Calculate the maximum length of any Tx queue
	//   (queue_total_size()- eth_get_num_rx_bd()) is the number of queue entries available after dedicating some to the ETH DMA
	//   MAX_PER_FLOW_QUEUE is the absolute max length of any queue; long queues (a.k.a. buffer bloat) are bad
	max_queue_size = min((queue_total_size()- eth_get_num_rx_bd()) / (1), MAX_TX_QUEUE_LEN);

	// Initialize callbacks
	wlan_mac_util_set_eth_rx_callback(          (void*)ethernet_receive);
	wlan_mac_high_set_mpdu_tx_done_callback(    (void*)mpdu_transmit_done);
	wlan_mac_high_set_mpdu_rx_callback(         (void*)mpdu_rx_process);
	wlan_mac_high_set_pb_u_callback(            (void*)up_button);

	wlan_mac_high_set_uart_rx_callback(         (void*)uart_rx);
	wlan_mac_high_set_poll_tx_queues_callback(  (void*)poll_tx_queues);
	wlan_mac_high_set_mpdu_dequeue_callback(    (void*)mpdu_dequeue);
    wlan_mac_ltg_sched_set_callback(            (void*)ltg_event);

    // Configure the wireless-wired encapsulation mode (AP and STA behaviors are different)
    wlan_mac_util_set_eth_encap_mode(ENCAP_MODE_AP);

    // Ask CPU Low for its status
    // The response to this request will be handled asynchronously
    wlan_mac_high_request_low_state();


    // Wait for CPU Low to initialize
	while( wlan_mac_high_is_cpu_low_initialized() == 0 ){
		xil_printf("waiting on CPU_LOW to boot\n");
	}

#ifdef USE_WARPNET_WLAN_EXP
    // NOTE:  To use the WLAN Experiments Framework, it must be initialized after
	//        CPU low has populated the hw_info structure in the MAC High framework.

	// Reset all callbacks
	wlan_exp_reset_all_callbacks();

	// Set WLAN Exp callbacks
	//   - Currently no additional init needed; Use wlan_exp_set_init_callback();
	wlan_exp_set_process_callback(                  (void *)wlan_exp_node_ap_processCmd);
	wlan_exp_set_reset_station_statistics_callback( (void *)reset_station_statistics);
	wlan_exp_set_purge_all_data_tx_queue_callback(  (void *)purge_all_data_tx_queue);
	wlan_exp_set_reset_all_associations_callback(   (void *)reset_all_associations);
	wlan_exp_set_reset_bss_info_callback(           (void *)reset_bss_info);
	wlan_exp_set_timebase_adjust_callback(          (void *)association_timestamp_adjust);
    //   - wlan_exp_set_tx_cmd_add_association_callback() should not be used by the AP

	// Configure the wlan_exp framework
	wlan_exp_configure(WLAN_EXP_NODE_TYPE, WLAN_EXP_TYPE_MASK, WLAN_EXP_ETH);

	// Get the hardware info that has been collected from CPU low
	hw_info = wlan_mac_high_get_hw_info();

	// Initialize WLAN Exp
	wlan_exp_node_init(hw_info->type, hw_info->serial_number, hw_info->fpga_dna,
			           hw_info->wn_eth_device, hw_info->hw_addr_wn, hw_info->hw_addr_wlan);
#endif


	// The node's MAC address is stored in the EEPROM, accessible only to CPU Low
	// CPU Low provides this to CPU High after it boots
	memcpy((void*) &(wlan_mac_addr[0]), (void*) wlan_mac_high_get_eeprom_mac_addr(), 6);

    // Set Header information
	tx_header_common.address_2 = &(wlan_mac_addr[0]);

    // Initialize hex display
	ap_write_hex_display(0);

	// Configure default radio and PHY params via messages to CPU Low
	mac_param_chan = WLAN_DEFAULT_CHANNEL;
	wlan_mac_high_set_channel( mac_param_chan );
	wlan_mac_high_set_rx_ant_mode(RX_ANTMODE_SISO_ANTA);
	wlan_mac_high_set_tx_ctrl_pow(WLAN_DEFAULT_TX_PWR);

	// Configure CPU Low's filter for passing Rx packets up to CPU High
	//  Default is "promiscuous" mode - pass all data and management packets with good or bad checksums
	//   This allows logging of all data/management receptions, even if they're not intended for this node
	wlan_mac_high_set_rx_filter_mode( (RX_FILTER_FCS_ALL | RX_FILTER_HDR_ALL) );

	// Set up BSS description
	my_bss_info = wlan_mac_high_create_bss_info(wlan_mac_addr, default_AP_SSID, mac_param_chan);
	my_bss_info->state           = BSS_STATE_OWNED;
	my_bss_info->beacon_interval = WLAN_DEFAULT_BEACON_INTERVAL_TU;
	my_bss_info->capabilities    = (CAPABILITIES_ESS | CAPABILITIES_SHORT_TIMESLOT);
	my_bss_info->phy_mode		 = BSS_INFO_PHY_MODE_11A;

	// Initialize interrupts
	wlan_mac_high_interrupt_init();

    // Setup default scheduled events:
	//  Periodic beacon transmissions

	power_save_configuration.enable = 1;
	power_save_configuration.dtim_period = 1;
	power_save_configuration.dtim_count = 0;
	power_save_configuration.dtim_mcast_allow_window = (WLAN_DEFAULT_BEACON_INTERVAL_TU * BSS_MICROSECONDS_IN_A_TU) / 4;

	beacon_schedule_id = wlan_mac_schedule_event_repeated(SCHEDULE_COARSE, (my_bss_info->beacon_interval * BSS_MICROSECONDS_IN_A_TU), SCHEDULE_REPEAT_FOREVER, (void*)beacon_transmit);

	//  Periodic check for timed-out associations
	wlan_mac_schedule_event_repeated(SCHEDULE_COARSE, ASSOCIATION_CHECK_INTERVAL_US, SCHEDULE_REPEAT_FOREVER, (void*)association_timestamp_check);

	//  Set Periodic blinking of hex display
	userio_set_pwm_period(USERIO_BASEADDR, 500);

	// Ramp must be disabled when changing ramp params
	userio_set_pwm_ramp_en(USERIO_BASEADDR, 0);
	userio_set_pwm_ramp_min(USERIO_BASEADDR, 2);
	userio_set_pwm_ramp_max(USERIO_BASEADDR, 400);

	wlan_mac_high_enable_hex_pwm();

	// Reset the event log
	event_log_reset();

	// Set address filter
	if((wlan_mac_high_get_user_io_state()&GPIO_MASK_DS_3)){
		xil_printf("Disallowing Associations\n");
		wlan_mac_addr_filter_reset();
		wlan_mac_addr_filter_add(disallow_mask, disallow_filter);
	}


	// Print AP information to the terminal
    xil_printf("WLAN MAC AP boot complete: \n");
    xil_printf("  SSID    : %s \n", my_bss_info->ssid);
    xil_printf("  Channel : %d \n", my_bss_info->chan);
	xil_printf("  MAC Addr: %02x-%02x-%02x-%02x-%02x-%02x\n\n",my_bss_info->bssid[0],my_bss_info->bssid[1],my_bss_info->bssid[2],my_bss_info->bssid[3],my_bss_info->bssid[4],my_bss_info->bssid[5]);

#ifdef WLAN_USE_UART_MENU
	xil_printf("\nPress the Esc key in your terminal to access the UART menu\n");
#endif

	// Finally enable all interrupts to start handling wireless and wired traffic
	wlan_mac_high_interrupt_restore_state(INTERRUPTS_ENABLED);

	while(1) {
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
 *   - Two queue groups are defined: Management (MGMT_QGRP) and Data (DATA_QGRP)
 *     - The Management group contains one queue for all management traffic
 *     - The Data group contains one queue for multicast data plus one queue per associated STA
 *   - The code alternates its polling between queue groups
 *   - In each group queues are polled via round robin
 *
 *  This scheme gives priority to management transmissions to help avoid timeouts during
 *  association handshakes and treats each associated STA with equal priority.
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
	interrupt_state_t curr_interrupt_state;
	u32 i,k;

	curr_interrupt_state = wlan_mac_high_interrupt_stop();

	#define NUM_QUEUE_GROUPS 2
	typedef enum {MGMT_QGRP, DATA_QGRP} queue_group_t;

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
				case MGMT_QGRP:
					next_queue_group = DATA_QGRP;
					if(dequeue_transmit_checkin(MANAGEMENT_QID)){
						goto poll_cleanup;
						return;
					}
				break;

				case DATA_QGRP:
					next_queue_group = MGMT_QGRP;
					curr_station_info_entry = next_station_info_entry;

					for(i = 0; i < (my_bss_info->associated_stations.length + 1); i++) {
						// Loop through all associated stations' queues and the broadcast queue
						if(curr_station_info_entry == NULL){
							// Check the broadcast queue
							next_station_info_entry = my_bss_info->associated_stations.first;

							if((get_usec_timestamp() - power_save_configuration.dtim_timestamp) <= power_save_configuration.dtim_mcast_allow_window || (power_save_configuration.enable == 0)){
								if(dequeue_transmit_checkin(MCAST_QID)){
									// Found a not-empty queue, transmitted a packet
									goto poll_cleanup;
									return;
								}
							}

							curr_station_info_entry = next_station_info_entry;

						} else {
							curr_station_info = (station_info*)(curr_station_info_entry->data);
							if( wlan_mac_high_is_valid_association(&my_bss_info->associated_stations, curr_station_info) ){
								if(curr_station_info_entry == my_bss_info->associated_stations.last){
									// We've reached the end of the table, so we wrap around to the beginning
									next_station_info_entry = NULL;
								} else {
									next_station_info_entry = dl_entry_next(curr_station_info_entry);
								}

								if(((curr_station_info->flags & STATION_INFO_FLAG_DOZE) == 0) || (power_save_configuration.enable == 0)){
									if(dequeue_transmit_checkin(AID_TO_QID(curr_station_info->AID))){
										// Found a not-empty queue, transmitted a packet
										goto poll_cleanup;
										return;
									}
								}

								curr_station_info_entry = next_station_info_entry;

							} else {
								// This curr_station_info is invalid. Perhaps it was removed from
								// the association table before poll_tx_queues was called. We will
								// start the round robin checking back at broadcast.
								next_station_info_entry = NULL;
								goto poll_cleanup;
								return;
							} // END if(is_valid_association)
						}
					} // END for loop over association table
				break;
			} // END switch(queue group)
		} // END loop over queue groups
	} // END CPU low is ready

	poll_cleanup:

	wlan_mac_high_interrupt_restore_state(curr_interrupt_state);

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
	curr_station_info_entry = my_bss_info->associated_stations.first;

	while(curr_station_info_entry != NULL){
		curr_station_info = (station_info*)(curr_station_info_entry->data);
		purge_queue(AID_TO_QID(curr_station_info->AID));       		// Each unicast queue
		curr_station_info_entry = dl_entry_next(curr_station_info_entry);
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
	station_info*          station 				   = NULL;
	dl_entry*	           entry				   = NULL;


	entry = wlan_mac_high_find_station_info_AID(&(my_bss_info->associated_stations), tx_mpdu->AID);
	if(entry != NULL) station = (station_info*)(entry->data);

	// Additional variables (Future Use)
	// void*                  mpdu                    = (u8*)tx_mpdu + PHY_TX_PKT_BUF_MPDU_OFFSET;
	// u8*                    mpdu_ptr_u8             = (u8*)mpdu;
	// mac_header_80211*      tx_80211_header         = (mac_header_80211*)((void *)mpdu_ptr_u8);

	// Log all of the TX Low transmissions

	//xil_printf("------------\n"); //DEBUG
	for(i = 0; i < num_tx_low_details; i++) {

		if( i==0 && (tx_low_details[i].tx_start_delta < T_SLOT) ){
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

		//xil_printf("[%d] :", i); //DEBUG

		//switch(tx_low_details[i].tx_details_type){
		//	case TX_DETAILS_RTS_ONLY:
		//		xil_printf(" RTS\n");
		//	break;
		//	case TX_DETAILS_RTS_MPDU:
		//		xil_printf(" RTS+MPDU\n");
		//	break;
		//	case TX_DETAILS_MPDU:
		//		xil_printf(" MPDU\n");
		//	break;
		//}

		//xil_printf("     TS:   %d\n", (u32)(ts_old) ); //DEBUG
		//xil_printf("     CW:   %d\n", tx_low_details[i].cw ); //DEBUG
		//xil_printf("     SRC:  %d\n", tx_low_details[i].src ); //DEBUG
		//xil_printf("     LRC:  %d\n", tx_low_details[i].lrc ); //DEBUG
		//xil_printf("     SSRC: %d\n", tx_low_details[i].ssrc ); //DEBUG
		//xil_printf("     SLRC: %d\n", tx_low_details[i].slrc ); //DEBUG


		// Accumulate the time-between-transmissions, used to calculate absolute time of each TX_LOW event above
		ts_old += tx_low_details[i].tx_start_delta;
	}

	// Log the TX MPDU
	wlan_exp_log_create_tx_entry(tx_mpdu, mac_param_chan);

	// Update the statistics for the node to which the packet was just transmitted
	if(tx_mpdu->AID != 0) {
		wlan_mac_high_update_tx_statistics(tx_mpdu,station);
	}


	// Send log entry to wlan_exp controller immediately (not currently supported)
	//
	// if (tx_high_event_log_entry != NULL) {
    //     wn_transmit_log_entry((void *)tx_high_event_log_entry);
	// }
}



/**
 * @brief Callback to handle push of up button
 *
 * Reference implementation does nothing.
 *
 * @param None
 * @return None
 */
void up_button(){
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
						return;
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
						return;
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

		do{
			continue_loop = 0;

			if(queue_num_queued(queue_sel) < max_queue_size){
				// Checkout 1 element from the queue;
				curr_tx_queue_element = queue_checkout();
				if(curr_tx_queue_element != NULL){
					// Create LTG packet
					curr_tx_queue_buffer = ((tx_queue_buffer*)(curr_tx_queue_element->data));

					// Setup the MAC header
					wlan_mac_high_setup_tx_header( &tx_header_common, addr_da, wlan_mac_addr );

					min_ltg_payload_length = wlan_create_ltg_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, MAC_FRAME_CTRL2_FLAG_FROM_DS, id);
					payload_length = max(payload_length+sizeof(mac_header_80211)+WLAN_PHY_FCS_NBYTES, min_ltg_payload_length);

					// Finally prepare the 802.11 header
					if (is_multicast) {
						wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
															curr_tx_queue_element,
															payload_length,
															(TX_MPDU_FLAGS_FILL_DURATION),
															queue_sel );
					} else {
						wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
															curr_tx_queue_element,
															payload_length,
															(TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO),
															queue_sel );
					}

					// Update the queue entry metadata to reflect the new new queue entry contents
					if (is_multicast || (station == NULL)) {
						curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
						curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)&default_multicast_data_tx_params;
						curr_tx_queue_buffer->frame_info.AID     	 = 0;
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
	station_info* station;
	dl_entry*     entry;

	// Determine how to send the packet
	if( wlan_addr_mcast(eth_dest) ) {

		// Send the multicast packet
		if(queue_num_queued(MCAST_QID) < max_queue_size){

			// Send the pre-encapsulated Ethernet frame over the wireless interface
			//     NOTE:  The queue element has already been provided, so we do not need to check if it is NULL
			tx_queue_buffer* curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

			// Setup the TX header
			wlan_mac_high_setup_tx_header( &tx_header_common, (u8*)(&(eth_dest[0])), (u8*)(&(eth_src[0])) );

			// Fill in the data
			wlan_create_data_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, MAC_FRAME_CTRL2_FLAG_FROM_DS);

			// Setup the TX frame info
			wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
												curr_tx_queue_element,
												tx_length,
												0,
												MCAST_QID);

			// Set the information in the TX queue buffer
			curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
			curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)&(default_multicast_data_tx_params);
			curr_tx_queue_buffer->frame_info.AID         = 0;

			// Put the packet in the queue
			enqueue_after_tail(MCAST_QID, curr_tx_queue_element);

		} else {
			// Packet was not successfully enqueued
			return 0;
		}

	} else {
		// Check associations
		//     Is this packet meant for a station we are associated with?
		entry = wlan_mac_high_find_station_info_ADDR(&my_bss_info->associated_stations, eth_dest);

		if( entry != NULL ) {
			station = (station_info*)(entry->data);

			// Send the unicast packet
			if(queue_num_queued(AID_TO_QID(station->AID)) < max_queue_size){

				// Send the pre-encapsulated Ethernet frame over the wireless interface
				//     NOTE:  The queue element has already been provided, so we do not need to check if it is NULL
				tx_queue_buffer* curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

				// Setup the TX header
				wlan_mac_high_setup_tx_header( &tx_header_common, (u8*)(&(eth_dest[0])), (u8*)(&(eth_src[0])) );

				// Fill in the data
				wlan_create_data_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, MAC_FRAME_CTRL2_FLAG_FROM_DS);

				// Setup the TX frame info
				wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
													curr_tx_queue_element,
													tx_length,
													(TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO),
													AID_TO_QID(station->AID));

				// Set the information in the TX queue buffer
				curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_STATION_INFO;
				curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)station;
				curr_tx_queue_buffer->frame_info.AID         = station->AID;

				// Put the packet in the queue
				enqueue_after_tail(AID_TO_QID(station->AID), curr_tx_queue_element);

			} else {
				// Packet was not successfully enqueued
				return 0;
			}
		} else {
			// Packet was not successfully enqueued
			return 0;
		}
	}

	// Packet successfully enqueued
	return 1;
}



/**
 * @brief Transmit a beacon
 *
 * This function will create and enqueue a beacon.
 *
 * @param  None
 * @return None
 */
void beacon_transmit() {
 	u16 tx_length;
 	tx_queue_element*	curr_tx_queue_element;
 	tx_queue_buffer* 	curr_tx_queue_buffer;

 	// Create a beacon
 	curr_tx_queue_element = queue_checkout();

 	if(curr_tx_queue_element != NULL){
 		curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

		// Setup the TX header
 		wlan_mac_high_setup_tx_header( &tx_header_common, (u8 *)bcast_addr, wlan_mac_addr );

		// Fill in the data
        tx_length = wlan_create_beacon_frame(
			(void*)(curr_tx_queue_buffer->frame),
			&tx_header_common,
			my_bss_info);

 		wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
 										curr_tx_queue_element,
 										tx_length,
 										(TX_MPDU_FLAGS_FILL_TIMESTAMP),
 										MANAGEMENT_QID );

		// Set the information in the TX queue buffer
 		curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
 		curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(&default_multicast_mgmt_tx_params);
		curr_tx_queue_buffer->frame_info.AID         = 0;

		// Put the packet in the queue
 		enqueue_after_tail(MANAGEMENT_QID, curr_tx_queue_element);

 	}
}



/**
 * @brief Check the time since the AP heard from each station
 *
 * This function will check the timestamp of the last reception from each station and send a
 * de-authentication packet to any stations that have timed out.
 *
 * @param  None
 * @return None
 */
void association_timestamp_check() {

	u32                 aid;
	u64 				time_since_last_activity;
	station_info*       curr_station_info;
	dl_entry*           curr_station_info_entry;
	dl_entry*           next_station_info_entry;


	next_station_info_entry = my_bss_info->associated_stations.first;

	while(next_station_info_entry != NULL) {
		curr_station_info_entry = next_station_info_entry;
		next_station_info_entry = dl_entry_next(curr_station_info_entry);

		curr_station_info        = (station_info*)(curr_station_info_entry->data);
		time_since_last_activity = (get_usec_timestamp() - curr_station_info->latest_activity_timestamp);

		// De-authenticate the station if we have timed out and we have not disabled this check for the station
		if((time_since_last_activity > ASSOCIATION_TIMEOUT_US) && ((curr_station_info->flags & STATION_INFO_FLAG_DISABLE_ASSOC_CHECK) == 0)){

			aid = deauthenticate_station( curr_station_info );

			if (aid != 0) {
				xil_printf("\n\nDisassociation due to inactivity:\n");
			}
		}
	}

	next_station_info_entry = station_info_state_2.first;

	while(next_station_info_entry != NULL) {
		curr_station_info_entry = next_station_info_entry;
		next_station_info_entry = dl_entry_next(curr_station_info_entry);

		curr_station_info        = (station_info*)(curr_station_info_entry->data);
		time_since_last_activity = (get_usec_timestamp() - curr_station_info->latest_activity_timestamp);

		// De-authenticate the station if we have timed out and we have not disabled this check for the station
		if((time_since_last_activity > ASSOCIATION_TIMEOUT_US) && ((curr_station_info->flags & STATION_INFO_FLAG_DISABLE_ASSOC_CHECK) == 0)){
			aid = deauthenticate_station( curr_station_info );
			if (aid != 0) {
				xil_printf("\n\nDeauthentication due to inactivity:\n");
			}
		}
	}
}

/**
 * @brief Update the last activity timestamps for all associated nodes
 *
 * In the current architecture, the last activity timestamps used the same usec counter than
 * can be modified by WLAN_EXP. This can lead to unexpected timeouts by 
 * association_timestamp_check(). This function should be called prior to large changes in
 * the underlying timebase to prevent this from occuring.
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

	u8                  send_response            = 0;
	u16                 tx_length;
	u16                 rx_seq;
	tx_queue_element*   curr_tx_queue_element;
	tx_queue_buffer*    curr_tx_queue_buffer;
	rx_common_entry*    rx_event_log_entry;

	dl_entry*	        associated_station_entry = NULL;
	station_info*       associated_station       = NULL;
	statistics_txrx*    station_stats            = NULL;

	u8                  unicast_to_me;
	u8                  to_multicast;
	u8                  eth_send;
	u8                  allow_auth               = 0;

	u8					pre_llc_offset			 = 0;

	u8 					rate					 = mpdu_info->phy_details.mcs;
	u16 				length					 = mpdu_info->phy_details.length;

	// Set the additional info field to NULL
	mpdu_info->additional_info = (u32)NULL;

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
	if( mpdu_info->state == RX_MPDU_STATE_FCS_GOOD){

		// Update the association information
		if(my_bss_info != NULL){
			associated_station_entry = wlan_mac_high_find_station_info_ADDR(&my_bss_info->associated_stations, (rx_80211_header->address_2));
		}

		if( associated_station_entry != NULL ){
			associated_station = (station_info*)(associated_station_entry->data);

			// Update PS state
			if((rx_80211_header->frame_control_2) & MAC_FRAME_CTRL2_FLAG_POWER_MGMT){
				associated_station->flags |= STATION_INFO_FLAG_DOZE;
			} else {
				associated_station->flags = (associated_station->flags) & ~STATION_INFO_FLAG_DOZE;
			}

			// Update station information
			mpdu_info->additional_info                    = (u32)associated_station;

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
					//   - Determine if this packet is from an associated station
					//   - Depending on the type and destination, transmit the packet wirelessly or over the wired network
					//


					if(associated_station != NULL){

						// MPDU is flagged as destined to the DS
						if((rx_80211_header->frame_control_2) & MAC_FRAME_CTRL2_FLAG_TO_DS) {
							eth_send = 1;

							// Check if this is a multicast packet
							if(wlan_addr_mcast(rx_80211_header->address_3)){
								//TODO: Needs fix for QoS case to handle u16 offset of QoS Control
								// Send the data packet over the wireless
								curr_tx_queue_element = queue_checkout();

								if(curr_tx_queue_element != NULL){
									curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

									// Setup the TX header
									wlan_mac_high_setup_tx_header( &tx_header_common, rx_80211_header->address_3, rx_80211_header->address_2);

									// Fill in the data
									mpdu_ptr_u8  = curr_tx_queue_buffer->frame;
									tx_length    = wlan_create_data_frame((void*)mpdu_ptr_u8, &tx_header_common, MAC_FRAME_CTRL2_FLAG_FROM_DS);
									mpdu_ptr_u8 += sizeof(mac_header_80211);
									memcpy(mpdu_ptr_u8, (void*)rx_80211_header + sizeof(mac_header_80211), length - sizeof(mac_header_80211));

									// Setup the TX frame info
									wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
																		curr_tx_queue_element,
																		length, 0,
																		MCAST_QID );

									// Set the information in the TX queue buffer
									curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
									curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(&default_multicast_data_tx_params);
									curr_tx_queue_buffer->frame_info.AID         = 0;

									// Put the packet in the queue
									enqueue_after_tail(MCAST_QID, curr_tx_queue_element);

								}
							} else {
								// Packet is not a multi-cast packet.  Check if it is destined for one of our stations
								associated_station_entry = wlan_mac_high_find_station_info_ADDR(&my_bss_info->associated_stations, rx_80211_header->address_3);

								if(associated_station_entry != NULL){
									//TODO: Needs fix for QoS case to handle u16 offset of QoS Control
									associated_station = (station_info*)(associated_station_entry->data);

									// Send the data packet over the wireless to our station
									curr_tx_queue_element = queue_checkout();

									if(curr_tx_queue_element != NULL){
										curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

										// Setup the TX header
										wlan_mac_high_setup_tx_header( &tx_header_common, rx_80211_header->address_3, rx_80211_header->address_2);

										// Fill in the data
										mpdu_ptr_u8  = curr_tx_queue_buffer->frame;
										tx_length    = wlan_create_data_frame((void*)mpdu_ptr_u8, &tx_header_common, MAC_FRAME_CTRL2_FLAG_FROM_DS);
										mpdu_ptr_u8 += sizeof(mac_header_80211);
										memcpy(mpdu_ptr_u8, (void*)rx_80211_header + sizeof(mac_header_80211), length - sizeof(mac_header_80211));

										// Setup the TX frame info
										wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
																			curr_tx_queue_element,
																			length,
																			(TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO),
																			AID_TO_QID(associated_station->AID) );


										// Set the information in the TX queue buffer
										curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_STATION_INFO;
										curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(associated_station);
										curr_tx_queue_buffer->frame_info.AID         = associated_station->AID;

										// Put the packet in the queue
										enqueue_after_tail(AID_TO_QID(associated_station->AID),  curr_tx_queue_element);


										// Given we sent the packet wirelessly to our stations, if we do not allow Ethernet transmissions
										//   of wireless transmissions, then do not send over Ethernet
										#ifndef ALLOW_ETH_TX_OF_WIRELESS_TX
										eth_send = 0;
										#endif
									}
								}
							}

							// Encapsulate the packet and send over the wired network
							if(eth_send){
								wlan_mpdu_eth_send(mpdu, length, pre_llc_offset);
							}
						}
					} else {
						// Packet was not from an associated station
						//   - Print a WARNING and send a de-authentication to trigger a re-association
						//
						//
						if(unicast_to_me){

							// Received a data frame from a STA that claims to be associated with this AP but is not in the AP association table
							//   Discard the MPDU and reply with a de-authentication frame to trigger re-association at the STA
							warp_printf(PL_WARNING, "Data from non-associated station: [%x %x %x %x %x %x], issuing de-authentication\n", rx_80211_header->address_2[0],rx_80211_header->address_2[1],rx_80211_header->address_2[2],rx_80211_header->address_2[3],rx_80211_header->address_2[4],rx_80211_header->address_2[5]);
							warp_printf(PL_WARNING, "Address 3: [%x %x %x %x %x %x]\n", rx_80211_header->address_3[0],rx_80211_header->address_3[1],rx_80211_header->address_3[2],rx_80211_header->address_3[3],rx_80211_header->address_3[4],rx_80211_header->address_3[5]);

							// Send de-authentication packet to the station
							curr_tx_queue_element = queue_checkout();

							if(curr_tx_queue_element != NULL){
								curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

								// Setup the TX header
								wlan_mac_high_setup_tx_header( &tx_header_common, rx_80211_header->address_2, wlan_mac_addr );

								// Fill in the data
								tx_length = wlan_create_deauth_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, DEAUTH_REASON_NONASSOCIATED_STA);

								// Setup the TX frame info
								wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
																	curr_tx_queue_element,
																	tx_length,
																	(TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO),
																	MANAGEMENT_QID );

								// Set the information in the TX queue buffer
								curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
								curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(&default_unicast_mgmt_tx_params);
								curr_tx_queue_buffer->frame_info.AID         = 0;

								// Put the packet in the queue
								enqueue_after_tail(MANAGEMENT_QID, curr_tx_queue_element);
							}
						}
					} // END if(associated_station != NULL)
				break;


				//---------------------------------------------------------------------
				case (MAC_FRAME_CTRL1_SUBTYPE_PROBE_REQ):
					// Probe Request Packet
					//   - Check that this packet is to the broadcast address
					//   - Look at the tagged parameters
					//   - Depending on the parameters, send a probe response
					//
					if(wlan_addr_eq(rx_80211_header->address_3, bcast_addr)) {
						mpdu_ptr_u8 += sizeof(mac_header_80211);

						// Loop through tagged parameters
						while(((u32)mpdu_ptr_u8 -  (u32)mpdu)<= (length - WLAN_PHY_FCS_NBYTES)){

							// What kind of tag is this?
							switch(mpdu_ptr_u8[0]){
								//-----------------------------------------------------
								case TAG_SSID_PARAMS:
									// SSID parameter set
									if((mpdu_ptr_u8[1]==0) || (memcmp(mpdu_ptr_u8+2, (u8*)my_bss_info->ssid, mpdu_ptr_u8[1])==0)) {
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
								wlan_mac_high_setup_tx_header( &tx_header_common, rx_80211_header->address_2, wlan_mac_addr );

								// Fill in the data
								tx_length = wlan_create_probe_resp_frame((void*)(curr_tx_queue_buffer->frame),
																		 &tx_header_common,
																		 my_bss_info);

								// Setup the TX frame info
								wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
																	curr_tx_queue_element,
																	tx_length,
																	(TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO | TX_MPDU_FLAGS_FILL_TIMESTAMP),
																	MANAGEMENT_QID );

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
				break;


				//---------------------------------------------------------------------
				case (MAC_FRAME_CTRL1_SUBTYPE_AUTH):
					// Authentication Packet
					//   - Check if authentication is allowed
					//   - Potentially send authentication response
					//
					if(wlan_addr_eq(rx_80211_header->address_3, wlan_mac_addr) && wlan_mac_addr_filter_is_allowed(rx_80211_header->address_2)) {
						mpdu_ptr_u8 += sizeof(mac_header_80211);
						switch(((authentication_frame*)mpdu_ptr_u8)->auth_algorithm ){
							case AUTH_ALGO_OPEN_SYSTEM:
								allow_auth = 1;
							break;
							default:
								allow_auth = 0;
							break;
						}
					}

					// Only send response if the packet was from a requester
					//
					if(((authentication_frame*)mpdu_ptr_u8)->auth_sequence == AUTH_SEQ_REQ){

						if(allow_auth){

							if(wlan_mac_high_find_station_info_ADDR (&(my_bss_info->associated_stations), rx_80211_header->address_2) == NULL){
								xil_printf("Authenticated, Unassociated Stations:\n");
								//This station wasn't already authenticated/associated (state 4), so we'll manually add it to the state 2 list.
								wlan_mac_high_add_association(&station_info_state_2, &statistics_table, rx_80211_header->address_2, ADD_ASSOCIATION_ANY_AID);
							}

							// Create a successful authentication response frame
							curr_tx_queue_element = queue_checkout();

							if(curr_tx_queue_element != NULL){
								curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

								// Setup the TX header
								wlan_mac_high_setup_tx_header( &tx_header_common, rx_80211_header->address_2, wlan_mac_addr );

								// Fill in the data
								tx_length = wlan_create_auth_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, AUTH_ALGO_OPEN_SYSTEM, AUTH_SEQ_RESP, STATUS_SUCCESS);

								// Setup the TX frame info
								wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
																	curr_tx_queue_element,
																	tx_length,
																	(TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO ),
																	MANAGEMENT_QID );

								// Set the information in the TX queue buffer
								curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
								curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(&default_unicast_mgmt_tx_params);
								curr_tx_queue_buffer->frame_info.AID         = 0;

								// Put the packet in the queue
								enqueue_after_tail(MANAGEMENT_QID, curr_tx_queue_element);

							}

							// Finish the function
							goto mpdu_rx_process_end;

						} else {
							// Create a unsuccessful authentication response frame
							curr_tx_queue_element = queue_checkout();

							if(curr_tx_queue_element != NULL){
								curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

								// Setup the TX header
								wlan_mac_high_setup_tx_header( &tx_header_common, rx_80211_header->address_2, wlan_mac_addr );

								// Fill in the data
								tx_length = wlan_create_auth_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, AUTH_ALGO_OPEN_SYSTEM, AUTH_SEQ_RESP, STATUS_AUTH_REJECT_UNSPECIFIED);

								// Setup the TX frame info
								wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
																	curr_tx_queue_element,
																	tx_length,
																	(TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO),
																	MANAGEMENT_QID );

								// Set the information in the TX queue buffer
								curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
								curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(&default_unicast_mgmt_tx_params);
								curr_tx_queue_buffer->frame_info.AID         = 0;

								// Put the packet in the queue
								enqueue_after_tail(MANAGEMENT_QID, curr_tx_queue_element);

							}
						}

						// Finish the function
						goto mpdu_rx_process_end;
					}
				break;


				//---------------------------------------------------------------------
				case (MAC_FRAME_CTRL1_SUBTYPE_ASSOC_REQ):
				case (MAC_FRAME_CTRL1_SUBTYPE_REASSOC_REQ):
					// Association Request / Re-association Request
					//   - Check if the packet is for me
					//

					if(wlan_addr_eq(rx_80211_header->address_3, wlan_mac_addr)) {



						// Check if we have authenticated this TA
						if (wlan_mac_high_find_station_info_ADDR(&station_info_state_2, rx_80211_header->address_2) != NULL){

							xil_printf("Authenticated, Unassociated Stations:\n");
							wlan_mac_high_remove_association(&station_info_state_2, &statistics_table, rx_80211_header->address_2);

							// NOTE:  This function handles both the case that the station is already in the association
							//   table and the case that the association needs to be added to the association table
							//

							xil_printf("Authenticated, Associated Stations:\n");
							associated_station = wlan_mac_high_add_association(&my_bss_info->associated_stations, &statistics_table, rx_80211_header->address_2, ADD_ASSOCIATION_ANY_AID);
							ap_write_hex_display(my_bss_info->associated_stations.length);
						}

						if(associated_station != NULL) {

							// Log the association state change
							add_station_info_to_log(associated_station, STATION_INFO_ENTRY_NO_CHANGE, WLAN_EXP_STREAM_ASSOC_CHANGE);

							// Create a successful association response frame
							curr_tx_queue_element = queue_checkout();

							if(curr_tx_queue_element != NULL){
								curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

								// Setup the TX header
								wlan_mac_high_setup_tx_header( &tx_header_common, rx_80211_header->address_2, wlan_mac_addr );

								// Fill in the data
								tx_length = wlan_create_association_response_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, STATUS_SUCCESS, associated_station->AID);

								// Setup the TX frame info
								wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
																	curr_tx_queue_element,
																	tx_length,
																	(TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO ),
																	AID_TO_QID(associated_station->AID) );

								// Set the information in the TX queue buffer
								curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_STATION_INFO;
								curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)associated_station;
								curr_tx_queue_buffer->frame_info.AID         = associated_station->AID;

								// Put the packet in the queue
								enqueue_after_tail(AID_TO_QID(associated_station->AID), curr_tx_queue_element);

							}

							// Finish the function
							goto mpdu_rx_process_end;

						} else {
							// Create an unsuccessful association response frame
							curr_tx_queue_element = queue_checkout();

							if(curr_tx_queue_element != NULL){
								curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

								// Setup the TX header
								wlan_mac_high_setup_tx_header( &tx_header_common, rx_80211_header->address_2, wlan_mac_addr );

								// Fill in the data
								tx_length = wlan_create_association_response_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, STATUS_REJECT_TOO_MANY_ASSOCIATIONS, 0);

								// Setup the TX frame info
								wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
																	curr_tx_queue_element,
																	tx_length,
																	(TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO ),
																	MANAGEMENT_QID );

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
				break;


				//---------------------------------------------------------------------
				case (MAC_FRAME_CTRL1_SUBTYPE_DISASSOC):
					// Disassociation
					//   - Log the assocation state change
					//   - Remove the assocation and update the display
					//
					if(associated_station != NULL){
						if ((associated_station->flags & STATION_INFO_DO_NOT_REMOVE) != STATION_INFO_DO_NOT_REMOVE) {
							// Log association state change
							add_station_info_to_log(associated_station, STATION_INFO_ENTRY_ZERO_AID, WLAN_EXP_STREAM_ASSOC_CHANGE);
						}
					}

					xil_printf("Authenticated, Associated Stations:\n");
					wlan_mac_high_remove_association(&my_bss_info->associated_stations, &statistics_table, rx_80211_header->address_2);

					ap_write_hex_display(my_bss_info->associated_stations.length);
				break;

				case (MAC_FRAME_CTRL1_SUBTYPE_NULLDATA):
				break;

				//---------------------------------------------------------------------
				default:
					//This should be left as a verbose print. It occurs often when communicating with mobile devices since they tend to send
					//null data frames (type: DATA, subtype: 0x4) for power management reasons.
					warp_printf(PL_VERBOSE, "Received unknown frame control type/subtype %x\n",rx_80211_header->frame_control_1);

				break;
			}
		}

		goto mpdu_rx_process_end;

	} else {
		// Process any Bad FCS packets
		goto mpdu_rx_process_end;
	}

	// Finish any processing for the RX MPDU process
	mpdu_rx_process_end:

	// Currently, asynchronous transmission of log entries is not supported
	//
	// if (rx_event_log_entry != NULL) {
    //     wn_transmit_log_entry((void *)rx_event_log_entry);
	// }

	return;
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

	// Deauthenticate all stations
	deauthenticate_stations();

}



/**
 * @brief Deauthenticate given station in the Association Table
 *
 * Deauthenticate the station in the associations table
 *
 * @param  station_info * station
 *   - Station to be deauthenticated
 * @return u32 aid
 *   - AID of the station that was deauthenticated; AID of 0 is reserved to indicate failure
 */
u32  deauthenticate_station( station_info* station ) {

	tx_queue_element*		curr_tx_queue_element;
	tx_queue_buffer* 		curr_tx_queue_buffer;
	u32            tx_length;
	u32            aid;

	if(station == NULL){
		return 0;
	}

	// Get the AID
	aid = station->AID;

	// Send De-authentication packet
	curr_tx_queue_element = queue_checkout();

	if(curr_tx_queue_element != NULL){
		curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

		// Setup the TX header
		wlan_mac_high_setup_tx_header( &tx_header_common, station->addr, wlan_mac_addr );

		// Fill in the data
		tx_length = wlan_create_deauth_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, DEAUTH_REASON_INACTIVITY);

		// Setup the TX frame info
		wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
											curr_tx_queue_element,
											tx_length,
											(TX_MPDU_FLAGS_FILL_DURATION | TX_MPDU_FLAGS_REQ_TO ),
											MANAGEMENT_QID );

		// Set the information in the TX queue buffer
		curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
		curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(&default_unicast_mgmt_tx_params);
		curr_tx_queue_buffer->frame_info.AID         = 0;

		// Put the packet in the queue
		enqueue_after_tail(MANAGEMENT_QID, curr_tx_queue_element);

 		// Purge any packets in the queue meant for this node
		purge_queue(AID_TO_QID(aid));
	}

	// Log the association state change
	add_station_info_to_log(station, STATION_INFO_ENTRY_ZERO_AID, WLAN_EXP_STREAM_ASSOC_CHANGE);

	// Remove this STA from association list
	xil_printf("Authenticated, Associated Stations:\n");
	wlan_mac_high_remove_association( &my_bss_info->associated_stations, &statistics_table, station->addr );

	ap_write_hex_display(my_bss_info->associated_stations.length);

	return aid;
}



/**
 * @brief Deauthenticate all stations in the Association Table
 *
 * Loop through all associations in the table and deauthenticate the stations
 *
 * @param  None
 * @return None
 */
void deauthenticate_stations(){
	station_info* curr_station_info;
	dl_entry* next_station_info_entry;
	dl_entry* curr_station_info_entry;

	next_station_info_entry = my_bss_info->associated_stations.first;

	// Deauthenticate all stations and remove from the association table
	//
	// NOTE:  Cannot use a for loop for this iteration b/c we could remove
	//   elements from the list.
	while(next_station_info_entry != NULL){
		curr_station_info_entry = next_station_info_entry;
		next_station_info_entry = dl_entry_next(curr_station_info_entry);
		curr_station_info = (station_info*)(curr_station_info_entry->data);
		deauthenticate_station(curr_station_info);
	}
}


void mpdu_dequeue(tx_queue_element* packet){
	mac_header_80211* 	header;
	tx_frame_info*		frame_info;
	ltg_packet_id*      pkt_id;
	u32 				packet_payload_size;
	u8                  tim_control;
	u16 				tim_byte_idx           = 0;
	u16 				tim_next_byte_idx      = 0;
	u8					tim_bit_idx            = 0;
	dl_entry*			curr_station_entry;
	station_info*		curr_station;
	u32                 i;
	u8					tim_len;
	mgmt_tag_template* 	mgmt_tag_ptr;

	header 	  			= (mac_header_80211*)((((tx_queue_buffer*)(packet->data))->frame));
	frame_info 			= (tx_frame_info*)&((((tx_queue_buffer*)(packet->data))->frame_info));
	packet_payload_size	= frame_info->length;


	switch(wlan_mac_high_pkt_type(header, packet_payload_size)){
		case PKT_TYPE_DATA_ENCAP_LTG:
			pkt_id		       = (ltg_packet_id*)((u8*)header + sizeof(mac_header_80211));
			pkt_id->unique_seq = wlan_mac_high_get_unique_seq();
		case PKT_TYPE_DATA_ENCAP_ETH:
			if(my_bss_info != NULL){
				curr_station_entry = wlan_mac_high_find_station_info_AID(&(my_bss_info->associated_stations), frame_info->AID);
				if(curr_station_entry != NULL){
					curr_station = (station_info*)(curr_station_entry->data);
					if(queue_num_queued(AID_TO_QID(curr_station->AID)) > 1){
						//If the is more data (in addition to this packet) queued for this station, we can let it know
						//in the frame_control_2 field.
						header->frame_control_2 |= MAC_FRAME_CTRL2_FLAG_MORE_DATA;
					} else {
						header->frame_control_2 = (header->frame_control_2) & ~MAC_FRAME_CTRL2_FLAG_MORE_DATA;
					}
				}
			}
		break;
		case PKT_TYPE_MGMT:
			if(header->frame_control_1 == MAC_FRAME_CTRL1_SUBTYPE_BEACON && my_bss_info != NULL){
				//If the packet we are about to send is a beacon, we need to tack on the TIM

				if(power_save_configuration.enable){
					mgmt_tag_ptr = (mgmt_tag_template*) ( ((u8*)header) + (packet_payload_size - WLAN_PHY_FCS_NBYTES) );

					tim_control = 0; //The top 7 bits are an offset for the partial map

					if(queue_num_queued(MCAST_QID)>0){
						tim_control |= 0x01; //Raise the multicast bit in the TIM control field
					}

					mgmt_tag_ptr->data[3] =  0;

					curr_station_entry = my_bss_info->associated_stations.first;
					while(curr_station_entry != NULL){
						curr_station = (station_info*)(curr_station_entry->data);

						if(queue_num_queued(AID_TO_QID(curr_station->AID))){
							tim_next_byte_idx = (curr_station->AID) / 8;

							if(tim_next_byte_idx > tim_byte_idx){
								//We've moved on to a new octet. We should zero everything after the previous octet
								//up to and including the new octet.
								for(i = tim_byte_idx+1; i <= tim_next_byte_idx; i++){
									mgmt_tag_ptr->data[3+i] = 0;
								}
							}

							tim_bit_idx  = (curr_station->AID) % 8;
							tim_byte_idx = tim_next_byte_idx;

							//Raise the bit for this station in the TIM partial bitmap
							mgmt_tag_ptr->data[3+tim_byte_idx] |= 1<<tim_bit_idx;
						}

						curr_station_entry = dl_entry_next(curr_station_entry);
					}

					tim_len = tim_byte_idx+1;

					mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_TIM;
					mgmt_tag_ptr->header.tag_length = 3+tim_len;

					mgmt_tag_ptr->data[0] = power_save_configuration.dtim_count; //DTIM count
					mgmt_tag_ptr->data[1] =  power_save_configuration.dtim_period; //DTIM period
					mgmt_tag_ptr->data[2] =  tim_control; //Bitmap control

					mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward

					packet_payload_size = ((u8*)mgmt_tag_ptr - (u8*)(header)) + WLAN_PHY_FCS_NBYTES;

					frame_info->length = packet_payload_size;

					//Update DTIM fields
					if(power_save_configuration.dtim_count > 0){
						power_save_configuration.dtim_count--;
					} else {
						power_save_configuration.dtim_timestamp = get_usec_timestamp();
						power_save_configuration.dtim_count = (power_save_configuration.dtim_period-1);
					}
				}

			}
		break;
	}
}



/**
 * @brief Enqueue a channel switch announcement
 *
 * This function will create a channel switch announcement and enqueue it to the management
 * queue.  It simply enqueues the packet and does not poll the TX queues.
 *
 * @param  u8 channel
 *   - Channel to which AP is switching
 * @return int status
 *   - Return 0 on success; non-zero otherwise
 */
int  send_channel_switch_announcement( u8 channel ) {
	int                 status = 0;
 	u16                 tx_length;
	tx_queue_element*   curr_tx_queue_element;
	tx_queue_buffer* 	curr_tx_queue_buffer;

	// Checkout 1 element from the queue
	curr_tx_queue_element = queue_checkout();

	// There was at least 1 free queue element
	if(curr_tx_queue_element != NULL){

		curr_tx_queue_buffer = (tx_queue_buffer*)(curr_tx_queue_element->data);

		// Create Channel Switch Announcement packet
 		wlan_mac_high_setup_tx_header( &tx_header_common, (u8 *)bcast_addr, wlan_mac_addr );

		tx_length = wlan_create_channel_switch_announcement_frame((void*)(curr_tx_queue_buffer->frame), &tx_header_common, channel);

 		wlan_mac_high_setup_tx_frame_info ( &tx_header_common,
 											curr_tx_queue_element,
 											tx_length,
 											0,
 											MANAGEMENT_QID );

		curr_tx_queue_buffer->metadata.metadata_type = QUEUE_METADATA_TYPE_TX_PARAMS;
		curr_tx_queue_buffer->metadata.metadata_ptr  = (u32)(&default_multicast_mgmt_tx_params);

		enqueue_after_tail(MANAGEMENT_QID, curr_tx_queue_element);
	} else {
		status = -1;
	}

	return status;
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
 * @brief Write a Decimal Value to the Hex Display
 *
 * This function will write a decimal value to the board's two-digit hex displays.
 * For the AP, the display is right justified and will blink; WARPNet will indicate
 * its connection state using the right decimal point.
 *
 * @param u8 val
 *   - Value to be displayed (between 0 and 99)
 * @return None
 *
 */
void ap_write_hex_display(u8 val){
	u32 hw_control;
	u32 temp_control;
    u32 right_dp;
    u8  left_val;
    u8  right_val;
    u32 pwm_val;

	// Need to retain the value of the right decimal point
	right_dp = userio_read_hexdisp_right( USERIO_BASEADDR ) & W3_USERIO_HEXDISP_DP;

	if ( val < 10 ) {
		left_val  = 0;
		right_val = sevenSegmentMap(val);
	} else {
		left_val  = sevenSegmentMap(((val/10)%10));
		right_val = sevenSegmentMap((val%10));
	}

    // Store the original value of what is under HW control
	hw_control   = userio_read_control(USERIO_BASEADDR);

	// Need to zero out all of the HW control of the hex displays; Change to raw hex mode
	temp_control = (hw_control & ( ~( W3_USERIO_HEXDISP_L_MAPMODE | W3_USERIO_HEXDISP_R_MAPMODE | W3_USERIO_CTRLSRC_HEXDISP_R | W3_USERIO_CTRLSRC_HEXDISP_L )));

	// Set the hex display mode to raw bits
    userio_write_control( USERIO_BASEADDR, temp_control );

    // Write the display
	userio_write_hexdisp_left(USERIO_BASEADDR, left_val);
	userio_write_hexdisp_right(USERIO_BASEADDR, (right_val | right_dp));

	pwm_val   = (right_val << 8) + left_val;

	// Set the HW / SW control of the user io (raw mode w/ the new display value)
    userio_write_control( USERIO_BASEADDR, ( temp_control | pwm_val ) );

    // Set the pins that are using PWM mode
	userio_set_hw_ctrl_mode_pwm(USERIO_BASEADDR, pwm_val);
}



