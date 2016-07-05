/** @file wlan_mac_bss_info.h
 *  @brief BSS Info Subsystem
 *
 *  This contains code tracking BSS information. It also contains code for managing
 *  the active scan state machine.
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

#ifndef WLAN_MAC_BSS_INFO_H_
#define WLAN_MAC_BSS_INFO_H_

#include "wlan_mac_high.h"

#define BSS_INFO_TIMEOUT_USEC	                 600000000

#define NUM_BASIC_RATES_MAX	                     10


// Define common BSS info fields
//   Note: These fields have been 32 bit aligned using padding bytes

// TODO: Update Python with new phy_mode
#define MY_BSS_INFO_COMMON_FIELDS                                                                       \
        u8         bssid[6];                          /* BSS ID - 40 bit HW address */                  \
        u8         chan;                              /* Channel */                                     \
        u8         flags;                             /* BSS Flags - Each flag is 1 bit */              \
        u64        latest_activity_timestamp;         /* Timestamp - Last interaction with BSS */       \
        char       ssid[SSID_LEN_MAX + 1];            /* SSID of the BSS - 33 bytes */                  \
        u8         state;                             /* State of the BSS */                            \
        u16        capabilities;                      /* Supported capabilities */                      \
        u16        beacon_interval;                   /* Beacon interval - In time units of 1024 us */  \
        u8         padding0;                          /* Padding byte - for 32-bit alignment */      \
        u8         num_basic_rates;                   /* Number of basic rates supported */             \
        u8         basic_rates[NUM_BASIC_RATES_MAX];  /* Supported basic rates - 10 bytes */            \
        u8		   phy_mode;						  /* PHY Mode (Legacy, HT, VHT)	*/					\
        u8         padding1;                          /* Padding byte - for 32-bit alignment */

#define BSS_INFO_PHY_MODE_11A		0x01
#define BSS_INFO_PHY_MODE_11N	 	0x02
#define BSS_INFO_PHY_MODE_11AC	 	0x04

/**
 * @brief Basic Service Set (BSS) Information Structure
 *
 * This struct contains information about the basic service set for the node.
 */
typedef struct{
	MY_BSS_INFO_COMMON_FIELDS

	dl_list associated_stations;
} bss_info;


/**
 * @brief Base BSS Information Structure
 *
 * This struct is a modification of the bss_info struct that eliminates
 * pointers to other data.
 */
typedef struct{
	MY_BSS_INFO_COMMON_FIELDS
} bss_info_base;


// BSS State defines
#define BSS_STATE_UNAUTHENTICATED	                       1
#define BSS_STATE_AUTHENTICATED		                       2
#define BSS_STATE_ASSOCIATED		                       4
#define BSS_STATE_OWNED				                       5

// BSS Beacon Interval defines
#define BSS_MICROSECONDS_IN_A_TU                           1024



/*************************** Function Prototypes *****************************/

void             bss_info_init(u8 dram_present);
void             bss_info_init_finish();

dl_entry       * bss_info_checkout();
void             bss_info_checkin(dl_entry* bsi);

inline void      bss_info_rx_process(void* pkt_buf_addr);

void             print_bss_info();
void             bss_info_timestamp_check();

dl_entry       * wlan_mac_high_find_bss_info_SSID(char* ssid);
dl_entry       * wlan_mac_high_find_bss_info_BSSID(u8* bssid);

bss_info       * wlan_mac_high_create_bss_info(u8* bssid, char* ssid, u8 chan);
void             wlan_mac_high_clear_bss_info(bss_info * info);

inline dl_list * wlan_mac_high_get_bss_info_list();

#endif
