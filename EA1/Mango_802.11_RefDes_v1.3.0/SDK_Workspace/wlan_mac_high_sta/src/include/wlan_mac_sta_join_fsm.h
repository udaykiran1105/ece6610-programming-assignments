/** @file wlan_mac_sta_join_fsm.h
 *  @brief Join FSM
 *
 *  This contains code for the STA join process.
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


#ifndef WLAN_MAC_STA_JOIN_FSM_H_
#define WLAN_MAC_STA_JOIN_FSM_H_

#define BSS_SEARCH_DEFAULT_TIMEOUT_SEC           0
#define BSS_SEARCH_POLL_INTERVAL_USEC            100000
#define BSS_ATTEMPT_POLL_INTERVAL_USEC           50000

void wlan_mac_sta_set_join_success_callback(function_ptr_t callback);
void wlan_mac_sta_scan_and_join(char* ssid, u32 to_sec);
void wlan_mac_sta_join(bss_info* bss_description, u32 to_sec);
void wlan_mac_sta_bss_search_poll(u32 schedule_id);
void wlan_mac_sta_bss_attempt_poll(u32 arg);
void wlan_mac_sta_scan_auth_transmit();
void wlan_mac_sta_scan_assoc_req_transmit();
void wlan_mac_sta_return_to_idle();

#endif
