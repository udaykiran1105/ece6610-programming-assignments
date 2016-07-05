/** @file wlan_mac_addr_mac_filter.c
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

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "xil_types.h"
#include "wlan_mac_addr_filter.h"
#include "wlan_mac_dl_list.h"
#include "wlan_mac_high.h"
#include "wlan_mac_bss_info.h"


/*************************** Constant Definitions ****************************/


/*********************** Global Variable Definitions *************************/

extern bss_info*		       my_bss_info;


/*************************** Variable Definitions ****************************/


// **********************************************************************
// White-list for address ranges
//
// For the mask, bits that are 0 are treated as "any" and bits that are 1 are treated as "must equal"
// For the compare, locations of one bits in the mask must match whitelist_range_compare for incoming addresses
//

dl_list   addr_filter;

static u8 warp_range_mask[WHITELIST_ADDR_LEN]    = { 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00 };
static u8 warp_range_compare[WHITELIST_ADDR_LEN] = { 0x40, 0xD8, 0x55, 0x04, 0x20, 0x00 };


/*************************** Functions Prototypes ****************************/

u8    addr_is_allowed(u8* addr, u8* mask, u8* compare);


/******************************** Functions **********************************/

/**
 * @brief Initialize the Address Filter
 *
 * This function will initialize the address filter
 *
 * @param    None.
 * @return   None.
 */
void  wlan_mac_addr_filter_init() {
	// Setup the address filter
	dl_list_init(&addr_filter);
}


/**
 * @brief Reset the Address Filter
 *
 * This function will reset the address filter back to the default state of
 * "allow all" (ie mask = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }, range =
 * { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }) and free all memory associated
 * with the white-list ranges.
 *
 * @param    None.
 * @return   None.
 */
void  wlan_mac_addr_filter_reset() {
    whitelist_range* curr_range;
	dl_entry* 	     next_range_dl_entry;
	dl_entry* 	     curr_range_dl_entry;

	next_range_dl_entry = addr_filter.first;

	// Remove all ranges from the address filter
	//
	// NOTE:  Cannot use a for loop for this iteration b/c we are removing
	//   elements from the list.
	while(next_range_dl_entry != NULL){
		curr_range_dl_entry = next_range_dl_entry;
		next_range_dl_entry = dl_entry_next(curr_range_dl_entry);

		curr_range = (whitelist_range*)(curr_range_dl_entry->data);

		dl_entry_remove(&addr_filter, curr_range_dl_entry);

		// Free allocated memory
		wlan_mac_high_free(curr_range_dl_entry);
		wlan_mac_high_free(curr_range);
	}
}


/**
 * @brief Add a white-list range to the Address Filter
 *
 * This function will allocate memory for a white-list range and add that to
 * the current list being used to filter addresses.
 *
 * @param    u8 * mask    - Mask for the white-list range
 * @param    u8 * compare - Compare address for the white-list range
 * @return   int  - Was this filter added successfully
 *      - nonzero if error
 */
int   wlan_mac_addr_filter_add(u8* mask, u8* compare) {
    whitelist_range* range;
	dl_entry* 	     entry;

	// Allocate memory for the entry and the white-list range
	entry = wlan_mac_high_malloc(sizeof(dl_entry));

	if(entry == NULL){
		return -1;
	}

	range = wlan_mac_high_malloc(sizeof(whitelist_range));

	if(range == NULL){
		free(entry);
		return -1;
	}

	entry->data = (void*)range;

	// Copy the mask and compare address to the new range
	memcpy( &(range->mask[0]), mask, WHITELIST_ADDR_LEN);
	memcpy( &(range->compare[0]), compare, WHITELIST_ADDR_LEN);

	// Add this range at the end of the address filter
	dl_entry_insertEnd(&addr_filter, entry);

	return 0;
}


/**
 * @brief Is the given address allowed?
 *
 * This function will apply the filter to the given address and return whether
 * the address passed the filter.
 *
 * @param    u8 * addr  - Address to check against the filter
 * @return   u8
 *      - zero if address is not allowed
 *      - one  if address is allowed
 */
u8    wlan_mac_addr_filter_is_allowed(u8* addr){
	u32              list_len = addr_filter.length;
    whitelist_range* curr_range;
	dl_entry* 	     curr_range_dl_entry;


	// Check if the list is empty
	//     NOTE: By default, we disallow all addresses
	//
	if (list_len == 0) { return 1; }


	// Check if you are currently in the association table
	//    If you are 're-joining' you should be allowed
	//
	if(my_bss_info != NULL){
		if ( wlan_mac_high_find_station_info_ADDR(&(my_bss_info->associated_stations), addr) != NULL) { return 1; }
	}


	// Check if the incoming address is within the allowable range of addresses
	//
	curr_range_dl_entry = addr_filter.first;

	while(curr_range_dl_entry != NULL){

		curr_range = (whitelist_range*)(curr_range_dl_entry->data);

		if ( addr_is_allowed(addr, (curr_range->mask), (curr_range->compare)) == 1 ) return 1;

		curr_range_dl_entry = dl_entry_next(curr_range_dl_entry);
	}

	// If the code made it this far, we aren't allowing this address to join the network.
	return 0;
}


/**
 * @brief Is the given address a WARP node?
 *
 * This function will check if the given address is in the WARP address range.
 *
 * @param    u8 * addr  - Address to check against the filter
 * @return   u8
 *      - zero if address is not a WARP address
 *      - one  if address is a WARP address
 */
u8    wlan_mac_addr_is_warp(u8* addr){
	return addr_is_allowed(addr, warp_range_mask, warp_range_compare);
}



/**
 * @brief
 *
 * This function will check the address against the given address range.
 *
 * @param    u8 * addr    - Address to check against the address range
 * @param    u8 * mask    - Mask of the address range
 * @param    u8 * compare - Compare address of the address range
 * @return   u8
 *      - zero if address is not in the range
 *      - one  if address is in the range
 */
u8    addr_is_allowed(u8* addr, u8* mask, u8* compare){
	u32       i;
	u32       sum;

	sum = 0;

	for(i = 0; i < WHITELIST_ADDR_LEN; i++){
		sum += (mask[i] & compare[i]) == (mask[i] & addr[i]);
	}

	if(sum == WHITELIST_ADDR_LEN) {
		return 1;
	} else {
        return 0;
	}
}





