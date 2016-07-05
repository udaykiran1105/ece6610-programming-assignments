/** @file wlan_mac_ibss_join_fsm.c
 *  @brief Join FSM
 *
 *  This contains code for the IBSS join process.
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


//Xilinx SDK includes
#include "xparameters.h"
#include "stdio.h"
#include "stdlib.h"
#include "xtmrctr.h"
#include "xio.h"
#include "string.h"
#include "xintc.h"

//WARP includes
#include "wlan_mac_802_11_defs.h"
#include "wlan_mac_high.h"
#include "wlan_mac_packet_types.h"
#include "wlan_mac_scan_fsm.h"
#include "wlan_mac_schedule.h"
#include "wlan_mac_dl_list.h"
#include "wlan_mac_bss_info.h"
#include "wlan_mac_ibss_join_fsm.h"
#include "wlan_mac_ibss.h"


#define BSS_JOIN_SCAN_ENABLED                              1
#define BSS_JOIN_SCAN_DISABLED                             0

typedef enum {JOIN_IDLE, JOIN_SEARCHING} join_state_t;

//External Global Variables:
extern mac_header_80211_common    tx_header_common;
extern u8                         pause_data_queue;
extern u32                        mac_param_chan; ///< This is the "home" channel
extern tx_params                  default_unicast_mgmt_tx_params;


// File Variables
static join_state_t               join_state = JOIN_IDLE;
static function_ptr_t             join_success_callback = (function_ptr_t)nullCallback;

//JOIN_SEARCHING Global Variables:
static char                       search_ssid[SSID_LEN_MAX + 1];
static u32                        search_sched_id      = SCHEDULE_FAILURE;
static u32                        search_kill_sched_id = SCHEDULE_FAILURE;
static u32                        search_timeout       = BSS_SEARCH_DEFAULT_TIMEOUT_SEC;



void wlan_mac_ibss_set_join_success_callback(function_ptr_t callback){
	join_success_callback = callback;
}


/**
 * @brief Attempt Scan and Join to AP
 *
 * This function will scan for a particular SSID and attempt to join it. The second
 * argument to the function is a timeout for the process. This function is non-blocking.
 *
 * @param char* ssid
 *  - SSID string of AP to find and join
 * @param u32 to_usec
 * 	- Timeout (seconds) for process.

 */
void wlan_mac_ibss_scan_and_join(char* ssid_str, u32 to_sec){

	if(strlen(ssid_str) != 0){
		switch(join_state){
			case JOIN_IDLE:
			    join_state = JOIN_SEARCHING;
				strcpy(search_ssid, ssid_str);
				search_timeout = to_sec;

				wlan_mac_scan_enable((u8*)bcast_addr, ssid_str);

				if(to_sec != 0){
					search_kill_sched_id = wlan_mac_schedule_event_repeated(SCHEDULE_COARSE, (to_sec*1000000), 1, (void*)wlan_mac_ibss_return_to_idle);
				}

				search_sched_id = wlan_mac_schedule_event_repeated(SCHEDULE_COARSE, BSS_SEARCH_POLL_INTERVAL_USEC, SCHEDULE_REPEAT_FOREVER, (void*)wlan_mac_ibss_bss_search_poll);
			break;

			case JOIN_SEARCHING:
			    wlan_mac_ibss_return_to_idle();
				wlan_mac_ibss_scan_and_join(ssid_str, to_sec);
			break;
		}
	} else {
		xil_printf("Error: SSID string must be non-null\n");
	}
}


void wlan_mac_ibss_join(bss_info* bss_description){
	interrupt_state_t prev_interrupt_state;
	prev_interrupt_state = wlan_mac_high_interrupt_stop();

	if(bss_description != NULL){
		switch(join_state){
			case JOIN_IDLE:
			    ibss_set_association_state(bss_description);
				join_success_callback(bss_description);
			break;
			case JOIN_SEARCHING:
			    wlan_mac_ibss_return_to_idle();
				wlan_mac_ibss_join(bss_description);
			break;
		}
	}

	wlan_mac_high_interrupt_restore_state(prev_interrupt_state);
}

//Low-Level functions

void wlan_mac_ibss_return_to_idle(){
	interrupt_state_t prev_interrupt_state;
    switch(join_state){
		case JOIN_IDLE:
		    // Nothing to do, we are already idle.
			if(search_sched_id != SCHEDULE_FAILURE){
				xil_printf("ERROR: Join currently idle, but search schedule ID found\n");
			}

			if(search_kill_sched_id != SCHEDULE_FAILURE){
				xil_printf("ERROR: Join currently idle, but kill schedule ID found\n");
			}
		break;

		case JOIN_SEARCHING:
		    wlan_mac_scan_disable();

			// We should kill the search_sched_id and search_kill_sched_id schedules (if they are running)
		    prev_interrupt_state = wlan_mac_high_interrupt_stop();

			join_state = JOIN_IDLE;

			if(search_sched_id != SCHEDULE_FAILURE){
				wlan_mac_remove_schedule(SCHEDULE_COARSE, search_sched_id);
				search_sched_id = SCHEDULE_FAILURE;
			}

			if(search_kill_sched_id != SCHEDULE_FAILURE){
				wlan_mac_remove_schedule(SCHEDULE_COARSE, search_kill_sched_id);
				search_kill_sched_id = SCHEDULE_FAILURE;
			}

			wlan_mac_high_interrupt_restore_state(prev_interrupt_state);
		break;
	}
}

void wlan_mac_ibss_bss_search_poll(u32 schedule_id){
	dl_entry* curr_dl_entry = NULL;
	bss_info* curr_bss_info;

    if (search_sched_id == SCHEDULE_FAILURE) {
    	xil_printf("WARNING:  BSS search poll called after schedule has been removed.\n");
    	return;
    }

    switch(join_state){
		case JOIN_IDLE:
			xil_printf("JOIN FSM Error: Searching/Idle mismatch\n");
		break;

		case JOIN_SEARCHING:
			curr_dl_entry = wlan_mac_high_find_bss_info_SSID(search_ssid);

			if(curr_dl_entry != NULL){
				curr_bss_info = (bss_info*)(curr_dl_entry->data);
				if(curr_bss_info->capabilities & CAPABILITIES_IBSS){
					wlan_mac_ibss_return_to_idle();
					wlan_mac_ibss_join(curr_bss_info);
				}
			}
		break;
	}
}

