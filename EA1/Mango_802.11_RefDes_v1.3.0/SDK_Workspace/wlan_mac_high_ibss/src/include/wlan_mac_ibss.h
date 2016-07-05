/** @file wlan_mac_ibss.h
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
#include "wlan_mac_high.h"
#include "wlan_mac_dl_list.h"
#include "wlan_mac_bss_info.h"



/*************************** Constant Definitions ****************************/
#ifndef WLAN_MAC_STA_H_
#define WLAN_MAC_STA_H_

// Enable the WLAN UART Menu
#define WLAN_USE_UART_MENU

// Tx queue IDs
#define MCAST_QID 		0
#define BEACON_QID		1
#define MANAGEMENT_QID 	2
#define AID_TO_QID(x)   ((x)+2) ///map association ID to Tx queue ID; min AID is 1

// Common Defines
#define NUM_BASIC_RATES_MAX            10

#define MAX_TX_QUEUE_LEN	  150 ///max number of entries in any Tx queue
#define MAX_NUM_ASSOC		  15  ///max number of associations the IBSS will allow

// UART Menu Modes
#define UART_MODE_MAIN                 0
#define UART_MODE_INTERACTIVE          1

// Timing Parameters

// Time between beacon transmissions
#define BEACON_INTERVAL_TU             (100)

#define ASSOCIATION_CHECK_INTERVAL_MS  (1000)
#define ASSOCIATION_CHECK_INTERVAL_US  (ASSOCIATION_CHECK_INTERVAL_MS*1000)

#define ASSOCIATION_TIMEOUT_S          (300)
#define ASSOCIATION_TIMEOUT_US         (ASSOCIATION_TIMEOUT_S*1000000)

//Number of probe requests to send per channel when active scanning
#define NUM_PROBE_REQ                  5

//Time the active scan procedure will dwell on each channel before
//moving to the next channel (microseconds)
#define ACTIVE_SCAN_DWELL			   100000

//The amount of time between full active scans when looking for a particular SSID
//Note: This value must be larger than the maximum amount of time it takes for
//a single active scan. For an active scan over 11 channels, this value must be larger
//than 11*ACTIVE_SCAN_DWELL.
#define ACTIVE_SCAN_UPDATE_RATE		  5000000

// WLAN Exp defines
#define  WLAN_EXP_STREAM_ASSOC_CHANGE            WN_NO_TRANSMIT

/*************************** Function Prototypes *****************************/
int main();

void ibss_set_association_state( bss_info* new_bss_info );
void association_timestamp_check();

void ltg_event(u32 id, void* callback_arg);
void association_timestamp_adjust(s64 timestamp_diff);

int ethernet_receive(tx_queue_element* curr_tx_queue_element, u8* eth_dest, u8* eth_src, u16 tx_length);

void mpdu_rx_process(void* pkt_buf_addr);
void mpdu_transmit_done(tx_frame_info* tx_mpdu, wlan_mac_low_tx_details* tx_low_details, u16 num_tx_low_details);
void mpdu_dequeue(tx_queue_element* packet);

void beacon_transmit(u32 schedule_id);

void poll_tx_queues();
void purge_all_data_tx_queue();

void reset_bss_info();
void leave_ibss();
void reset_station_statistics();

dl_list * get_statistics();

void uart_rx(u8 rxByte);

void print_menu();
void print_queue_status();
void print_station_status(u8 manual_call);
void print_all_observed_statistics();

void ibss_write_hex_display(u8 val);


#endif /* WLAN_MAC_STA_H_ */
