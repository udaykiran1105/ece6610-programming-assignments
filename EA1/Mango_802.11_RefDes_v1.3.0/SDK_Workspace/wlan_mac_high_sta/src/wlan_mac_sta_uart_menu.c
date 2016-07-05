/** @file wlan_mac_sta_uart_menu.c
 *  @brief Station UART Menu
 *
 *  This contains code for the 802.11 Station's UART menu.
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
#include "xparameters.h"
#include "stdio.h"
#include "stdlib.h"
#include "xtmrctr.h"
#include "xio.h"
#include "string.h"
#include "xintc.h"

//WARP includes
#include "wlan_mac_ipc_util.h"
#include "wlan_mac_misc_util.h"
#include "wlan_mac_802_11_defs.h"
#include "wlan_mac_queue.h"
#include "wlan_mac_ltg.h"
#include "wlan_mac_high.h"
#include "wlan_mac_packet_types.h"
#include "wlan_mac_eth_util.h"
#include "wlan_mac_sta.h"
#include "ascii_characters.h"
#include "wlan_mac_schedule.h"
#include "wlan_mac_event_log.h"
#include "wlan_mac_bss_info.h"


#ifndef WLAN_USE_UART_MENU

void uart_rx(u8 rxByte){ };

#else

#define MAX_NUM_CHARS                       31


extern u32                                  mac_param_chan;
extern tx_params                            default_unicast_data_tx_params;

extern bss_info*                            my_bss_info;
extern dl_list                              statistics_table;


static volatile u8                          uart_mode            = UART_MODE_MAIN;
static volatile u32                         schedule_ID;
static volatile u8                          print_scheduled      = 0;



void uart_rx(u8 rxByte){

	station_info* access_point = NULL;

	if(my_bss_info != NULL){
		access_point = ((station_info*)(my_bss_info->associated_stations.first->data));
	}

	if(rxByte == ASCII_ESC){
		uart_mode = UART_MODE_MAIN;

		if(print_scheduled){
			wlan_mac_remove_schedule(SCHEDULE_COARSE, schedule_ID);
		}
		print_menu();

		ltg_sched_remove(LTG_REMOVE_ALL);

		return;
	}

	switch(uart_mode){
		case UART_MODE_MAIN:
			switch(rxByte){
				case ASCII_1:
					uart_mode = UART_MODE_INTERACTIVE;
					print_station_status(1);
				break;

				case ASCII_2:
					print_all_observed_statistics();
				break;

				case ASCII_e:
			        event_log_config_logging(EVENT_LOG_LOGGING_DISABLE);
					print_event_log_size();
#ifdef _DEBUG_
			        print_event_log( 0xFFFF );
					print_event_log_size();
#endif
			        event_log_config_logging(EVENT_LOG_LOGGING_ENABLE);
				break;

				case ASCII_a:
					print_bss_info();
				break;

				case ASCII_x:
					reset_bss_info();
				break;

				case ASCII_r:
					if((default_unicast_data_tx_params.phy.rate) > WLAN_MAC_MCS_6M){
						(default_unicast_data_tx_params.phy.rate)--;
					} else {
						(default_unicast_data_tx_params.phy.rate) = WLAN_MAC_MCS_6M;
					}

					if(access_point != NULL) access_point->tx.phy.rate = (default_unicast_data_tx_params.phy.rate);


					xil_printf("(-) Default Unicast Rate: %d Mbps\n", wlan_lib_mac_rate_to_mbps((default_unicast_data_tx_params.phy.rate)));
				break;
				case ASCII_R:
					if((default_unicast_data_tx_params.phy.rate) < WLAN_MAC_MCS_54M){
						(default_unicast_data_tx_params.phy.rate)++;
					} else {
						(default_unicast_data_tx_params.phy.rate) = WLAN_MAC_MCS_54M;
					}

					if(access_point != NULL) access_point->tx.phy.rate = (default_unicast_data_tx_params.phy.rate);

					xil_printf("(+) Default Unicast Rate: %d Mbps\n", wlan_lib_mac_rate_to_mbps((default_unicast_data_tx_params.phy.rate)));
				break;
			}
		break;
		case UART_MODE_INTERACTIVE:
			switch(rxByte){
				case ASCII_r:
					//Reset statistics
					reset_station_statistics();
				break;
			}
		break;

	}


}


void print_menu(){
	xil_printf("\f");
	xil_printf("********************** Station Menu **********************\n");
	xil_printf("[1] - Interactive Station Status\n");
	xil_printf("[2] - Print all Observed Statistics\n");
	xil_printf("\n");
	xil_printf("[a] - 	display BSS information\n");
	xil_printf("[r/R] - change unicast rate\n");
}

void print_station_status(u8 manual_call){

	u64 timestamp;
	dl_entry* access_point_entry = NULL;

	if(my_bss_info != NULL){
		access_point_entry = my_bss_info->associated_stations.first;
	}

	station_info* access_point = NULL;

	if(my_bss_info != NULL){
		access_point = ((station_info*)(access_point_entry->data));
	}
	statistics_txrx* curr_statistics;


	if(uart_mode == UART_MODE_INTERACTIVE){
		timestamp = get_usec_timestamp();
		xil_printf("\f");
		xil_printf("---------------------------------------------------\n");

			if(my_bss_info != NULL){
				xil_printf(" AID: %02x -- MAC Addr: %02x:%02x:%02x:%02x:%02x:%02x\n", access_point->AID,
							access_point->addr[0],access_point->addr[1],access_point->addr[2],access_point->addr[3],access_point->addr[4],access_point->addr[5]);

				curr_statistics = access_point->stats;

				xil_printf("     - Last heard from         %d ms ago\n",((u32)(timestamp - (access_point->latest_activity_timestamp)))/1000);
				xil_printf("     - Last Rx Power:          %d dBm\n",access_point->rx.last_power);
				xil_printf("     - # of queued MPDUs:      %d\n", queue_num_queued(UNICAST_QID));
				xil_printf("     - # Tx High Data MPDUs:   %d (%d successful)\n", curr_statistics->data.tx_num_packets_total, curr_statistics->data.tx_num_packets_success);
				xil_printf("     - # Tx High Data bytes:   %d (%d successful)\n", (u32)(curr_statistics->data.tx_num_bytes_total), (u32)(curr_statistics->data.tx_num_bytes_success));
				xil_printf("     - # Tx Low Data MPDUs:    %d\n", curr_statistics->data.tx_num_packets_low);
				xil_printf("     - # Tx High Mgmt MPDUs:   %d (%d successful)\n", curr_statistics->mgmt.tx_num_packets_total, curr_statistics->mgmt.tx_num_packets_success);
				xil_printf("     - # Tx High Mgmt bytes:   %d (%d successful)\n", (u32)(curr_statistics->mgmt.tx_num_bytes_total), (u32)(curr_statistics->mgmt.tx_num_bytes_success));
				xil_printf("     - # Tx Low Mgmt MPDUs:    %d\n", curr_statistics->mgmt.tx_num_packets_low);
				xil_printf("     - # Rx Data MPDUs:        %d\n", curr_statistics->data.rx_num_packets);
				xil_printf("     - # Rx Data Bytes:        %d\n", curr_statistics->data.rx_num_bytes);
				xil_printf("     - # Rx Mgmt MPDUs:        %d\n", curr_statistics->mgmt.rx_num_packets);
				xil_printf("     - # Rx Mgmt Bytes:        %d\n", curr_statistics->mgmt.rx_num_bytes);
			}
		xil_printf("---------------------------------------------------\n");
		xil_printf("\n");
		xil_printf("[r] - reset statistics\n\n");

		//Update display
		schedule_ID = wlan_mac_schedule_event(SCHEDULE_COARSE, 1000000, (void*)print_station_status);

	}
}

void print_all_observed_statistics(){
	dl_entry*	curr_statistics_entry;
	statistics_txrx* curr_statistics;

	curr_statistics_entry = statistics_table.first;

	xil_printf("\nAll Statistics:\n");
	while(curr_statistics_entry != NULL){
		curr_statistics = (statistics_txrx*)(curr_statistics_entry->data);
		xil_printf("---------------------------------------------------\n");
		xil_printf("%02x:%02x:%02x:%02x:%02x:%02x\n", curr_statistics->addr[0],curr_statistics->addr[1],curr_statistics->addr[2],curr_statistics->addr[3],curr_statistics->addr[4],curr_statistics->addr[5]);
		xil_printf("     - Last timestamp:         %d usec\n", (u32)curr_statistics->latest_txrx_timestamp);
		xil_printf("     - Associated?             %d\n", curr_statistics->is_associated);
		xil_printf("     - # Tx High Data MPDUs:   %d (%d successful)\n", curr_statistics->data.tx_num_packets_total, curr_statistics->data.tx_num_packets_success);
		xil_printf("     - # Tx High Data bytes:   %d (%d successful)\n", (u32)(curr_statistics->data.tx_num_bytes_total), (u32)(curr_statistics->data.tx_num_bytes_success));
		xil_printf("     - # Tx Low Data MPDUs:    %d\n", curr_statistics->data.tx_num_packets_low);
		xil_printf("     - # Tx High Mgmt MPDUs:   %d (%d successful)\n", curr_statistics->mgmt.tx_num_packets_total, curr_statistics->mgmt.tx_num_packets_success);
		xil_printf("     - # Tx High Mgmt bytes:   %d (%d successful)\n", (u32)(curr_statistics->mgmt.tx_num_bytes_total), (u32)(curr_statistics->mgmt.tx_num_bytes_success));
		xil_printf("     - # Tx Low Mgmt MPDUs:    %d\n", curr_statistics->mgmt.tx_num_packets_low);
		xil_printf("     - # Rx Data MPDUs:        %d\n", curr_statistics->data.rx_num_packets);
		xil_printf("     - # Rx Data Bytes:        %d\n", curr_statistics->data.rx_num_bytes);
		xil_printf("     - # Rx Mgmt MPDUs:        %d\n", curr_statistics->mgmt.rx_num_packets);
		xil_printf("     - # Rx Mgmt Bytes:        %d\n", curr_statistics->mgmt.rx_num_bytes);
		curr_statistics_entry = dl_entry_next(curr_statistics_entry);
	}
}




#endif


