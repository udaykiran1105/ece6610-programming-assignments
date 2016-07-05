/** @file wlan_mac_addr_mac_filter.h
 *  @brief Address Filter
 *
 *  This contains code for the filtering MAC addresses
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


/*************************** Constant Definitions ****************************/
#ifndef WLAN_MAC_ADDR_FILTER_H_
#define WLAN_MAC_ADDR_FILTER_H_


#define WHITELIST_ADDR_LEN                       6


/*********************** Global Structure Definitions ************************/

// **********************************************************************
// Whitelist Range Structure
//
typedef struct {

	u8   mask[WHITELIST_ADDR_LEN];
	u8   compare[WHITELIST_ADDR_LEN];

} whitelist_range;



/*************************** Function Prototypes *****************************/

void  wlan_mac_addr_filter_init();
void  wlan_mac_addr_filter_reset();

int   wlan_mac_addr_filter_add(u8* mask, u8* compare);

u8    wlan_mac_addr_filter_is_allowed(u8* addr);
u8    wlan_mac_addr_is_warp(u8* addr);


#endif /* WLAN_MAC_ADDR_FILTER_H_ */




