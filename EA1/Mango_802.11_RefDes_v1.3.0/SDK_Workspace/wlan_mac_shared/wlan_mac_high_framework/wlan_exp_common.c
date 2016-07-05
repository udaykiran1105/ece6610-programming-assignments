/** @file wlan_exp_common.c
 *  @brief Experiment Framework (Common)
 *
 *  This contains the code for WARPnet Experimental Framework.
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

// Xilinx / Standard library includes

#include <xparameters.h>
#include <xil_io.h>
#include <xio.h>

#include "ctype.h"
#include "string.h"
#include "stdarg.h"

// WLAN includes
#include "wlan_mac_high.h"

// WLAN Exp includes
#include "wlan_exp_common.h"



/*************************** Constant Definitions ****************************/

/*********************** Global Variable Definitions *************************/

/*************************** Variable Definitions ****************************/

/*************************** Functions Prototypes ****************************/

/**************************** Common Functions *******************************/


/*****************************************************************************/
/**
* Debug Printing Functions
*
******************************************************************************/
u8       wlan_exp_print_level     = WLAN_EXP_PRINT_ERROR;
char   * print_type_node          = "NODE";
char   * print_type_transport     = "TRANSPORT";
char   * print_type_event_log     = "EVENT LOG";
char   * print_type_stats         = "STATS";
char   * print_type_ltg           = "LTG";
char   * print_type_queue         = "QUEUE";


void wlan_exp_print_header(u8 level, char * type, char* filename, u32 line) {
    char * basename = NULL;

	if (type != NULL) {
		xil_printf("%s", type);

		if ((level <= WLAN_EXP_PRINT_WARNING) || (wlan_exp_print_level == WLAN_EXP_PRINT_DEBUG)) {
            basename =  strrchr(filename, '/') ? strrchr(filename, '/') + 1 : filename;
		}

		if (wlan_exp_print_level == WLAN_EXP_PRINT_DEBUG) {
			xil_printf(" (%s:%d): ", basename, line);
		} else {
			xil_printf(": ");
		}

		switch(level) {
			case WLAN_EXP_PRINT_ERROR:
				xil_printf("ERROR (%s:%d): ", basename, line);
			break;

			case WLAN_EXP_PRINT_WARNING:
				xil_printf("WARNING (%s:%d): ", basename, line);
			break;
		}
	}
}


void wlan_exp_print_mac_address(u8 level, u8 * mac_address) {
    u32 i;

    if (level <= wlan_exp_print_level) {
		xil_printf("%02x", mac_address[0]);

		for ( i = 1; i < ETH_ADDR_LEN; i++ ) {
			xil_printf(":%02x", mac_address[i]);
		}
    }
}


void wlan_exp_set_print_level(u8 level) {

	switch(level) {
        case WLAN_EXP_PRINT_NONE:
        case WLAN_EXP_PRINT_ERROR:
        case WLAN_EXP_PRINT_WARNING:
        case WLAN_EXP_PRINT_INFO:
        case WLAN_EXP_PRINT_DEBUG:
        	wlan_exp_print_level = level;
        break;

        default:
        	xil_printf("Unsupported print level.  Setting to WLAN_EXP_PRINT_ERROR.\n");
        	wlan_exp_print_level = WLAN_EXP_PRINT_ERROR;
        break;
	}
}



#ifdef USE_WARPNET_WLAN_EXP



/*****************************************************************************/
/**
* Get MAC Address
*
* This function will populate the MAC address buffer, dest, with the MAC
* address coming over the network (byte swapped).  This uses the same formating
* as the HW address parameter from transport.c
*
* @param    src  - Source buffer of MAC address (u32, byte swapped)
*           dest - Destination buffer of MAC address
*
* @return	None.
*
* @note     None.
*
******************************************************************************/
void wlan_exp_get_mac_addr(u32 * src, u8 * dest) {

    dest[0] = (src[0] >> 16) & 0xFF;
    dest[1] = (src[0] >> 24) & 0xFF;
    dest[2] = (src[1] >>  0) & 0xFF;
    dest[3] = (src[1] >>  8) & 0xFF;
    dest[4] = (src[1] >> 16) & 0xFF;
    dest[5] = (src[1] >> 24) & 0xFF;

}


void wlan_exp_put_mac_addr(u8 * src, u32 * dest) {

	dest[0] = (src[1] << 24) + (src[0] << 16);
	dest[1] = (src[5] << 24) + (src[4] << 16) + (src[3] <<  8) + (src[2] <<  0);

}



/*****************************************************************************/
/**
* Configure WLAN Exp
*
* This function will configure the wlan_mac_hw_info structure with the WARPNet Type
* and the Ethernet device to use with WARPNet
*
* @param    type          - WARPNet type
*           type_mask     - Bit mask for WARPNet type
*           eth_dev_num   - WARPNet Ethernet device
*
* @return	None.
*
******************************************************************************/
void wlan_exp_configure(u32 type, u32 type_mask, u32 eth_dev_num){
	wlan_mac_hw_info* hw_info_ptr = wlan_mac_high_get_hw_info();

	hw_info_ptr->type          = (type & type_mask) + (hw_info_ptr->type & ~type_mask);
	hw_info_ptr->wn_eth_device = eth_dev_num;

}



/*****************************************************************************/
/**
* Get Station Status
*
* This function will populate the buffer with:
*   buffer[0]      = Number of stations
*   buffer[1 .. N] = memcpy of the station information structure
* where N is less than max_words
*
* @param    stations      - Station info pointer
*           num_stations  - Number of stations to copy
*           buffer        - u32 pointer to the buffer to transfer the data
*           max_words     - The maximum number of words in the buffer
*
* @return	Number of words copied in to the buffer
*
* @note     None.
*
******************************************************************************/
int get_station_status( station_info * stations, u32 num_stations, u32 * buffer, u32 max_words ) {

	unsigned int size;
	unsigned int index;

	index     = 0;

	// Set number of Association entries
	buffer[ index++ ] = num_stations;

	// Get total size (in bytes) of data to be transmitted
	size   = num_stations * sizeof( station_info );

	// Get total size of data (in words) to be transmitted
	index += size / sizeof( u32 );

    if ( (size > 0 ) && (index < max_words) ) {

        memcpy( &buffer[1], stations, size );
    }

	return index;
}



// End USE_WARPNET_WLAN_EXP
#endif
