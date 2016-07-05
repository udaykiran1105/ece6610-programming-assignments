/** @file wlan_mac_ap.h
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


/***************************** Include Files *********************************/



/*************************** Constant Definitions ****************************/
#ifndef WLAN_MAC_AP_H_
#define WLAN_MAC_AP_H_

#include "wlan_mac_dl_list.h"

// Enable the WLAN UART Menu
#define WLAN_USE_UART_MENU

// Allow Ethernet transmission of packets received by an associated station
// destined for another associated station
//#define ALLOW_ETH_TX_OF_WIRELESS_TX

// UART Menu Modes
#define UART_MODE_MAIN                 0
#define UART_MODE_INTERACTIVE          1
#define UART_MODE_SSID_CHANGE          2

// Common Defines
#define MAX_TX_QUEUE_LEN	  150 ///max number of entries in any Tx queue
#define MAX_NUM_ASSOC		  10  ///max number of associations the AP will allow

#define MCAST_QID 0
#define MANAGEMENT_QID 1
#define AID_TO_QID(x) ((x)+1) ///map association ID to Tx queue ID; min AID is 1

// Period for checking association table for stale STA associations
#define ASSOCIATION_CHECK_INTERVAL_MS  (1000)
#define ASSOCIATION_CHECK_INTERVAL_US  (ASSOCIATION_CHECK_INTERVAL_MS*1000)

// Timeout for last reception for an association STA; timed-out STA's are subject to de-association
#define ASSOCIATION_TIMEOUT_S          (300)
#define ASSOCIATION_TIMEOUT_US         (ASSOCIATION_TIMEOUT_S*1000000)

// Interval to allow associations after entering ASSOCIATION_ALLOW_TEMPORARY mode
#define ASSOCIATION_ALLOW_INTERVAL_MS  (30000)
#define ASSOCIATION_ALLOW_INTERVAL_US  (ASSOCIATION_ALLOW_INTERVAL_MS*1000)

// Blinking period for hex displays, when used to show association mode
#define ANIMATION_RATE_US              (100000)

// LTG helper macros and defines
#define LTG_ID_TO_AID(ltg_id) (ltg_id)
#define AID_TO_LTG_ID(aid)	  (aid)

#define LTG_ID_GRP_SCHED_CONSTANT 1
#define LTG_ID_GRP_SCHED_RANDOM	  2

#define LTG_ID_GRP_PYLD_FIXED	  1
#define LTG_ID_GRP_PYLD_RANDOM	  2

// WLAN Exp defines
#define  WLAN_EXP_STREAM_ASSOC_CHANGE            WN_TRANSMIT


typedef struct{
	u8 enable;
	u8 dtim_period;
	u8 dtim_count;
	u64 dtim_timestamp;
	u64 dtim_mcast_allow_window;
} ps_conf;


/*************************** Function Prototypes *****************************/
int  main();

void ltg_event(u32 id, void* callback_arg);
int  ethernet_receive(tx_queue_element* curr_tx_queue_element, u8* eth_dest, u8* eth_src, u16 tx_length);
void mpdu_rx_process(void* pkt_buf_addr);
void mpdu_transmit_done(tx_frame_info* tx_mpdu, wlan_mac_low_tx_details* tx_low_details, u16 num_tx_low_details);

void poll_tx_queues();
void purge_all_data_tx_queue();

void beacon_transmit();
int  send_channel_switch_announcement( u8 channel );

void enable_associations();
void disable_associations();
void association_timestamp_check();
void association_timestamp_adjust(s64 timestamp_diff);

void reset_all_associations();
void reset_station_statistics();
void reset_bss_info();

u32  deauthenticate_station( station_info* station );
void deauthenticate_stations();
void mpdu_dequeue(tx_queue_element* packet);

dl_list * get_statistics();
void eth_packet_inspection(u32 type, u32 length, void* ptr);
void up_button();

void uart_rx(u8 rxByte);

void print_menu();
void print_ssid_menu();
void print_queue_status();
void print_station_status();
void start_periodic_print();
void print_all_observed_statistics();
void stop_periodic_print();
int  is_qwerty_row(u8 rxByte);
int  qwerty_row_to_number(u8 rxByte);

void ap_write_hex_display(u8 val);

#endif /* WLAN_MAC_AP_H_ */
