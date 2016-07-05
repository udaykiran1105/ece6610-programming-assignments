/** @file wlan_mac_scan_fsm.h
 *  @brief Active Scan FSM
 *
 *  This contains code for the active scan finite state machine. This particular file
 *  is for the STA variant.
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


#ifndef WLAN_MAC_SCAN_FSM_H_
#define WLAN_MAC_SCAN_FSM_H_

int wlan_mac_set_scan_channels(u8* channel_vec, u32 len);
void wlan_mac_set_scan_timings(u32 dwell_usec, u32 idle_usec);
void wlan_mac_scan_enable(u8* bssid, char* ssid_str);
void wlan_mac_scan_disable();
void wlan_mac_scan_state_transition();
void wlan_mac_scan_probe_req_transmit();

#endif
