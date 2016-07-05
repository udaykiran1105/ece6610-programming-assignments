/** @file wlan_mac_entries.c
 *  @brief Event log
 *
 *  This contains the code for accessing event log.
 *
 *  @copyright Copyright 2014-2015, Mango Communications. All rights reserved.
 *          Distributed under the Mango Communications Reference Design License
 *				See LICENSE.txt included in the design archive or
 *				at http://mangocomm.com/802.11/license
 *
 *	@note
 *  This is the only code that the user should modify in order to add entries
 *  to the event log.  To add a new entry, please follow the template provided
 *  and create:
 *    1) A new entry type in wlan_mac_entries.h
 *    2) Wrapper function:  get_next_empty_*_entry()
 *    3) Update the print function so that it is easy to print the log to the
 *    terminal
 *
 *  @author Chris Hunter (chunter [at] mangocomm.com)
 *  @author Patrick Murphy (murphpo [at] mangocomm.com)
 *  @author Erik Welsh (welsh [at] mangocomm.com)
 */


/***************************** Include Files *********************************/

// SDK includes
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "xil_types.h"

// WLAN includes
#include "wlan_exp_common.h"
#include "wlan_mac_event_log.h"
#include "wlan_mac_entries.h"

// Includes for wlan_exp_log_get_txrx_entry_sizes()
#include "xintc.h"
#include "wlan_mac_eth_util.h"
#include "wlan_mac_high.h"
#include "wlan_mac_ltg.h"



/*************************** Constant Definitions ****************************/



/*********************** Global Variable Definitions *************************/

static u8	log_entry_en_mask;


//-----------------------------------------------
// mac_payload_log_len
//
// Global variable that defines the number of payload bytes that are recorded
// for each transmission / reception.  This value must be between:
//     MIN_MAC_PAYLOAD_LOG_LEN
//     MAX_MAC_PAYLOAD_LOG_LEN
// and be 4-byte aligned.  Use the wlan_exp_log_set_mac_payload_len() method
// to change the value of this variable.  By default, this is set to the minimum
// payload length to save space in the log and can be altered by C code or
// through WARPNet.
//

u32 mac_payload_log_len = MIN_MAC_PAYLOAD_LOG_LEN;
// u32 mac_payload_log_len = MAX_MAC_PAYLOAD_LOG_LEN;


/*************************** Variable Definitions ****************************/



/*************************** Functions Prototypes ****************************/

void wlan_exp_log_get_txrx_entry_sizes( u32 type, u16 packet_payload_size, u32 * min_log_len, u32 * entry_size, u32 * payload_size );



/******************************** Functions **********************************/

/*****************************************************************************/
/**
* Set entry enable mask.
*
* @param    u8 mask
* 				- Bitwise OR of:
* 					- ENTRY_EN_MASK_TXRX_CTRL
* 					- ENTRY_EN_MASK_TXRX_MPDU
*
*
* @return	None.
*
* @note		None.
*
******************************************************************************/

u8 wlan_exp_log_get_entry_en_mask(){
	return log_entry_en_mask;
}

void wlan_exp_log_set_entry_en_mask(u8 mask){
	log_entry_en_mask = mask;
}

/*****************************************************************************/
/**
* Set max_mac_payload_log_len
*
* @param    u32 payload_len
* 				- Number of bytes to set aside for payload.
* 				@note This needs to be 4-byte aligned.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void wlan_exp_log_set_mac_payload_len(u32 payload_len){
	u32 value;
	u32 offset;

	// Make sure that value is 4-byte aligned.
	offset = payload_len % 4;
	if (offset != 0) {
		value = payload_len;
	} else {
		value = payload_len + (4 - offset);
	}

	// If the value is less than the minimum, then set it to the minimum
	if (value < MIN_MAC_PAYLOAD_LOG_LEN) {
		value = MIN_MAC_PAYLOAD_LOG_LEN;
	}

	// If the value is greater than the maximum, then set it to the maximum
	if (value > MAX_MAC_PAYLOAD_LOG_LEN) {
		value = MAX_MAC_PAYLOAD_LOG_LEN;
	}

	// Set the global variable
	mac_payload_log_len = value;
}



/*****************************************************************************/
/**
* Get the next empty log entry
*
* @param    u16 entry_type_id
*               - ID of the entry being requested
*           u16 entry_size
* 				- Number of total bytes in the entry.
* 				@note This needs to be 4-byte aligned.
*
* @return	void *
*               - Pointer to memory that was allocated for the entry in the log
*               @note This can be NULL if an entry was not allocated
*
* @note		None.
*
******************************************************************************/
void * wlan_exp_log_create_entry(u16 entry_type_id, u16 entry_size){

	void *    ret_val   = NULL;

	//
	// NOTE:  This is where filtering on entry_type_id would be in future implementations
	//

	ret_val = event_log_get_next_empty_entry( entry_type_id, entry_size );

	return ret_val;
}



/*****************************************************************************/
/**
* Create a TX Low Log entry
*
* @param    tx_frame_info * tx_mpdu
*               - TX MPDU of the associated TX low entry
*           wlan_mac_low_tx_details * tx_low_details
* 				- Specific information of the TX low transmission
* 			u64 timestamp_offset
* 			    - Offset of the TX low entry's timestamp
* 			u32 tx_low_count
* 			    - Indicates which TX low this is for the TX MPDU (starts at zero)
*
* @return	tx_low_entry *
*               - Pointer to tx_low_entry log entry
*               @note This can be NULL if an entry was not allocated
*
* @note		None.
*
******************************************************************************/
tx_low_entry * wlan_exp_log_create_tx_low_entry(tx_frame_info* tx_mpdu, wlan_mac_low_tx_details* tx_low_details, u64 timestamp_offset, u32 tx_low_count){

	tx_low_entry*     tx_low_event_log_entry  = NULL;
	void*             mpdu;
	u8*               mpdu_ptr_u8;
	mac_header_80211* tx_80211_header;
	u32               packet_payload_size;
	u8                pkt_type;
	u16               entry_type;
	u32               entry_size;
	u32               entry_payload_size;
	u32               min_entry_payload_size;

	mpdu                    = (u8*)tx_mpdu + PHY_TX_PKT_BUF_MPDU_OFFSET;
	mpdu_ptr_u8             = (u8*)mpdu;
	tx_80211_header         = (mac_header_80211*)((void *)mpdu_ptr_u8);

	if( ((tx_low_details->tx_details_type == TX_DETAILS_RTS_ONLY) || (tx_low_details->tx_details_type == TX_DETAILS_RTS_MPDU)) && (log_entry_en_mask & ENTRY_EN_MASK_TXRX_CTRL) ){


		//CREATE RTS LOG ENTRY
		entry_type = ENTRY_TYPE_TX_LOW;

		packet_payload_size = sizeof(mac_header_80211_RTS)+WLAN_PHY_FCS_NBYTES;

		// Get all the necessary sizes to log the packet
		wlan_exp_log_get_txrx_entry_sizes( entry_type, packet_payload_size, &entry_size, &entry_payload_size, &min_entry_payload_size );

		// Request space for a TX_LOW log entry
		tx_low_event_log_entry = (tx_low_entry *)wlan_exp_log_create_entry( entry_type, entry_size );

		if(tx_low_event_log_entry != NULL){
			// Store the payload size in the log entry
			tx_low_event_log_entry->mac_payload_log_len = entry_payload_size;

			// Create the payload for the log entry
			// The actual RTS bytes that were transmitted aren't visible to this function. We only have the underlying MPDU that
			// the RTS was trying to reserve the medium for. Instead, we can reconstruct what the RTS payload actually was in
			// this log entry.
			wlan_create_rts_frame((void*)(&((tx_low_entry*)tx_low_event_log_entry)->mac_payload),
								  tx_80211_header->address_1,
								  tx_80211_header->address_2,
								  tx_low_details->duration);

			// Zero pad log entry if payload_size was less than the allocated space in the log (ie min_log_len)
			if(entry_payload_size < min_entry_payload_size){
				bzero((u8*)(((u32)((tx_low_entry*)tx_low_event_log_entry)->mac_payload) + entry_payload_size), (min_entry_payload_size - entry_payload_size));
			}

			tx_low_event_log_entry->flags = 0;

			// Compute the timestamp of the actual Tx event
			//   CPU low accumulates time deltas relative to original enqueue time (easier to store u32 deltas vs u64 times)
			tx_low_event_log_entry->timestamp_send            = (u64)(tx_mpdu->timestamp_create + (u64)(tx_mpdu->delay_accept) + (u64)(tx_low_details->tx_start_delta) + timestamp_offset);

			pkt_type = wlan_mac_high_pkt_type(&((tx_low_entry*)tx_low_event_log_entry)->mac_payload, packet_payload_size);

			tx_low_event_log_entry->unique_seq				  = tx_mpdu->unique_seq; //Note: RTS frames don't have sequence numbers. However, for easier processing
																					 //we'll include the MPDU's unique sequence number in this RTS TX LOW entry
			tx_low_event_log_entry->transmission_count        = tx_low_count + 1;
			tx_low_event_log_entry->chan_num                  = tx_low_details->chan_num;
			tx_low_event_log_entry->num_slots				  = tx_low_details->num_slots;
			tx_low_event_log_entry->cw						  = tx_low_details->cw;
			memcpy((&((tx_low_entry*)tx_low_event_log_entry)->phy_params), &(tx_low_details->ctrl_phy_params), sizeof(phy_tx_params));

			tx_low_event_log_entry->length                    = packet_payload_size;
			tx_low_event_log_entry->pkt_type				  = pkt_type;

		}

	}

	if( ((tx_low_details->tx_details_type == TX_DETAILS_MPDU) || (tx_low_details->tx_details_type == TX_DETAILS_RTS_MPDU)) && (log_entry_en_mask & ENTRY_EN_MASK_TXRX_MPDU)){
		//CREATE MPDU LOG ENTRY

		packet_payload_size     = tx_mpdu->length;

		// Determine the type of the packet
		pkt_type = wlan_mac_high_pkt_type(mpdu, packet_payload_size);

		// Determine the entry type
		if (pkt_type == PKT_TYPE_DATA_ENCAP_LTG) {
			entry_type = ENTRY_TYPE_TX_LOW_LTG;
		} else {
			entry_type = ENTRY_TYPE_TX_LOW;
		}

		// Get all the necessary sizes to log the packet
		wlan_exp_log_get_txrx_entry_sizes( entry_type, packet_payload_size, &entry_size, &entry_payload_size, &min_entry_payload_size );

		// Request space for a TX_LOW log entry
		tx_low_event_log_entry = (tx_low_entry *)wlan_exp_log_create_entry( entry_type, entry_size );

		if(tx_low_event_log_entry != NULL){

			// Store the payload size in the log entry
			tx_low_event_log_entry->mac_payload_log_len = entry_payload_size;

			// Transfer the payload to the log entry
			wlan_mac_high_cdma_start_transfer((&((tx_low_entry*)tx_low_event_log_entry)->mac_payload), tx_80211_header, entry_payload_size);

			// Zero pad log entry if payload_size was less than the allocated space in the log (ie min_log_len)
			if(entry_payload_size < min_entry_payload_size){
				bzero((u8*)(((u32)((tx_low_entry*)tx_low_event_log_entry)->mac_payload) + entry_payload_size), (min_entry_payload_size - entry_payload_size));
			}

			// Set the flags in the log entry
			if(((tx_low_count + 1) == (tx_mpdu->num_tx_attempts)) && (tx_mpdu->tx_result == TX_MPDU_RESULT_SUCCESS)){
				tx_low_event_log_entry->flags = TX_LOW_FLAGS_WAS_ACKED;
			} else {
				tx_low_event_log_entry->flags = 0;
			}

			if((tx_low_details->tx_details_type == TX_DETAILS_MPDU)){
			// Compute the timestamp of the actual Tx event
			//   CPU low accumulates time deltas relative to original enqueue time (easier to store u32 deltas vs u64 times)
				tx_low_event_log_entry->timestamp_send            = (u64)(tx_mpdu->timestamp_create + (u64)(tx_mpdu->delay_accept) + (u64)(tx_low_details->tx_start_delta) + timestamp_offset);
			}
			else{
				tx_low_event_log_entry->timestamp_send            = (u64)(tx_mpdu->timestamp_create + (u64)(tx_mpdu->delay_accept) + (u64)(tx_low_details->tx_start_delta) + timestamp_offset + (u64)(tx_low_details->timestamp_offset));
			}

			tx_low_event_log_entry->unique_seq				  = tx_mpdu->unique_seq;
			tx_low_event_log_entry->transmission_count        = tx_low_count + 1;
			tx_low_event_log_entry->chan_num                  = tx_low_details->chan_num;
			tx_low_event_log_entry->num_slots				  = tx_low_details->num_slots;
			tx_low_event_log_entry->cw						  = tx_low_details->cw;
			memcpy((&((tx_low_entry*)tx_low_event_log_entry)->phy_params), &(tx_low_details->mpdu_phy_params), sizeof(phy_tx_params));
			tx_low_event_log_entry->length                    = tx_mpdu->length;
			tx_low_event_log_entry->pkt_type				  = pkt_type;
			wlan_mac_high_cdma_finish_transfer();

			//CPU Low updates the retry flag in the header for any re-transmissions
			// Re-create the original header for the first TX_LOW by de-asserting the flag
			if(tx_low_count == 0) {
				//This is the first transmission
				((mac_header_80211*)(tx_low_event_log_entry->mac_payload))->frame_control_2 &= ~MAC_FRAME_CTRL2_FLAG_RETRY;
			} else {
				//This is all subsequent transmissions
				((mac_header_80211*)(tx_low_event_log_entry->mac_payload))->frame_control_2 |= MAC_FRAME_CTRL2_FLAG_RETRY;
			}

	#ifdef _DEBUG_
			xil_printf("TX LOW  : %8d    %8d    \n", transfer_len, MIN_MAC_PAYLOAD_LOG_LEN);
			print_buf((u8 *)((u32)tx_low_event_log_entry - 8), sizeof(tx_low_entry) + 12);
	#endif
		}


	}



	return tx_low_event_log_entry;
}



/*****************************************************************************/
/**
* Create a TX Log entry
*
* @param    tx_frame_info * tx_mpdu
*               - TX MPDU of the associated TX entry
* 			u8 channel_number
* 			    - Indicates the channel on which the transmission occurred
*
* @return	tx_high_entry *
*               - Pointer to the tx_high_entry log entry
*               @note This can be NULL if an entry was not allocated
*
* @note		None.
*
******************************************************************************/
tx_high_entry * wlan_exp_log_create_tx_entry(tx_frame_info* tx_mpdu, u8 channel_num){

	tx_high_entry*    tx_high_event_log_entry = NULL;
	void*             mpdu                    = (u8*)tx_mpdu + PHY_TX_PKT_BUF_MPDU_OFFSET;
	u8*               mpdu_ptr_u8             = (u8*)mpdu;
	mac_header_80211* tx_80211_header         = (mac_header_80211*)((void *)mpdu_ptr_u8);
	u32               packet_payload_size     = tx_mpdu->length;
	u8                pkt_type;
	u16               entry_type;
	u32               entry_size;
	u32               entry_payload_size;
	u32               min_entry_payload_size;
	u32               transfer_len;

	if( (log_entry_en_mask & ENTRY_EN_MASK_TXRX_MPDU) == 0 ){
		//MPDU logging is disabled
		return NULL;
	}

	// Determine the type of the packet
	pkt_type = wlan_mac_high_pkt_type(mpdu, packet_payload_size);

	// Determine the entry type
	if (pkt_type == PKT_TYPE_DATA_ENCAP_LTG) {
		entry_type = ENTRY_TYPE_TX_HIGH_LTG;
	} else {
		entry_type = ENTRY_TYPE_TX_HIGH;
	}

	// Get all the necessary sizes to log the packet
	wlan_exp_log_get_txrx_entry_sizes( entry_type, packet_payload_size, &entry_size, &entry_payload_size, &min_entry_payload_size );

	// Request space for a TX entry
	tx_high_event_log_entry = (tx_high_entry *)wlan_exp_log_create_entry( entry_type, entry_size );

	if(tx_high_event_log_entry != NULL){

		// Fill in the TX log entry
		//   This is done one field at a time, as the TX log entry format is not a byte-for-byte copy of the tx_frame_info
		tx_high_event_log_entry->mac_payload_log_len = entry_payload_size;

		// Compute the length of the DMA transfer to log the packet:
		//
		// We have two arrays in memory that we have to be aware of:
		//     1) The packet payload that has "packet_payload_size" bytes;
		//     2) The TX log entry that has "entry_payload_size" bytes;
		//
		// Because the packet payload does not have to be 32-bit aligned and we could be logging an arbitrary number of
		// bytes of the packet, we have to be careful about not walking off the end of either array. Therefore, we need
		// to transfer the shorter of the two arrays and then zero pad the log entry if we transfered less than
		// "entry_payload_size" bytes.
		//
		transfer_len = min(entry_payload_size, packet_payload_size);

		wlan_mac_high_cdma_start_transfer((&((tx_high_entry*)tx_high_event_log_entry)->mac_payload), tx_80211_header, transfer_len);

		// Zero pad log entry if transfer_len was less than the allocated space in the log (ie entry_payload_size)
		if(transfer_len < entry_payload_size){
			bzero((u8*)(((u32)((tx_high_entry*)tx_high_event_log_entry)->mac_payload) + transfer_len), (entry_payload_size - transfer_len) );
		}

        // Populate the log entry
		bzero(tx_high_event_log_entry->padding , sizeof(tx_high_event_log_entry->padding));
		tx_high_event_log_entry->unique_seq				  = tx_mpdu->unique_seq;
		tx_high_event_log_entry->queue_id				  = tx_mpdu->QID;
		tx_high_event_log_entry->result                   = tx_mpdu->tx_result;
		tx_high_event_log_entry->power              	  = tx_mpdu->params.phy.power;
		tx_high_event_log_entry->length                   = tx_mpdu->length;
		tx_high_event_log_entry->rate                     = tx_mpdu->params.phy.rate;
		tx_high_event_log_entry->chan_num				  = channel_num;
		tx_high_event_log_entry->pkt_type				  = pkt_type;
		tx_high_event_log_entry->num_tx                   = tx_mpdu->short_retry_count; //TODO: Add long/short distinction to event log
		tx_high_event_log_entry->timestamp_create         = tx_mpdu->timestamp_create;
		tx_high_event_log_entry->delay_accept             = tx_mpdu->delay_accept;
		tx_high_event_log_entry->delay_done               = tx_mpdu->delay_done;
		tx_high_event_log_entry->ant_mode				  = tx_mpdu->params.phy.antenna_mode;


#ifdef _DEBUG_
		xil_printf("TX HIGH : %8d    %8d    %8d    %8d    %8d\n", transfer_len, MIN_MAC_PAYLOAD_LOG_LEN, total_payload_len, extra_payload, payload_log_len);
        print_buf((u8 *)((u32)tx_high_event_log_entry - 8), sizeof(tx_high_entry) + extra_payload + 12);
#endif
	}

	return tx_high_event_log_entry;
}



/*****************************************************************************/
/**
* Create a RX Log entry
*
* @param    rx_frame_info * rx_mpdu
*               - RX MPDU of the associated RX entry
* 			u8 channel_number
* 			    - Indicates the channel on which the reception occurred
* 			u8 rate
* 			    - Indicates the rate at which the reception occurred
*
* @return	rx_common_entry *
*               - Pointer to the rx_common_entry log entry
*               @note This can be NULL if an entry was not allocated
*
* @note		None.
*
******************************************************************************/
rx_common_entry * wlan_exp_log_create_rx_entry(rx_frame_info* rx_mpdu, u8 channel_num, u8 rate){

	rx_common_entry*  rx_event_log_entry      = NULL;
	tx_low_entry*     tx_low_event_log_entry  = NULL; //This is for any inferred CTRL transmissions
	void*             mpdu                    = (u8*)rx_mpdu + PHY_RX_PKT_BUF_MPDU_OFFSET;
	u8*               mpdu_ptr_u8             = (u8*)mpdu;
	mac_header_80211* rx_80211_header         = (mac_header_80211*)((void *)mpdu_ptr_u8);
	u32               packet_payload_size     = rx_mpdu->phy_details.length;
	u8                pkt_type;
    u32               entry_type;
	u32               entry_size;
	u32               entry_payload_size;
	u32               min_entry_payload_size;
	u32               transfer_len;

	typedef enum {PAYLOAD_FIRST, CHAN_EST_FIRST} copy_order_t;
	copy_order_t      copy_order;

	if( (((rx_80211_header->frame_control_1 & 0xF) == MAC_FRAME_CTRL1_TYPE_DATA) && (log_entry_en_mask & ENTRY_EN_MASK_TXRX_MPDU)) ||
		(((rx_80211_header->frame_control_1 & 0xF) == MAC_FRAME_CTRL1_TYPE_CTRL) && (log_entry_en_mask & ENTRY_EN_MASK_TXRX_CTRL)) ||
		( (rx_80211_header->frame_control_1 & 0xF) == MAC_FRAME_CTRL1_TYPE_MGMT) ){

		// Determine the type of the packet
		pkt_type = wlan_mac_high_pkt_type(mpdu, packet_payload_size);

		// Determine the entry type
		if(rate != WLAN_MAC_MCS_1M){
			if (pkt_type == PKT_TYPE_DATA_ENCAP_LTG) {
				entry_type = ENTRY_TYPE_RX_OFDM_LTG;
			} else {
				entry_type = ENTRY_TYPE_RX_OFDM;
			}
		} else {
			entry_type = ENTRY_TYPE_RX_DSSS;
		}

		// Get all the necessary sizes to log the packet
		wlan_exp_log_get_txrx_entry_sizes( entry_type, packet_payload_size, &entry_size, &entry_payload_size, &min_entry_payload_size );


		// Create the log entry
		rx_event_log_entry = (rx_common_entry*)wlan_exp_log_create_entry( entry_type, entry_size );

		// Populate the log entry
		if(rx_event_log_entry != NULL){

			// For maximum pipelining, we'll break up the two major log copy operations (packet payload + [optional] channel estimates)
			// We will start the CDMA operation for whichever of those copies is shorter, then fill in the rest of the log entry
			// while that copy is under way, and then start the CDMA operation for the larger (which will first block on the shorter if
			// it is still going).

			if(rate == WLAN_MAC_MCS_1M){
				// This is a DSSS packet that has no channel estimates
				copy_order = PAYLOAD_FIRST;
			} else {
				// This is an OFDM packet that contains channel estimates
	#ifdef WLAN_MAC_ENTRIES_LOG_CHAN_EST
				if( sizeof(rx_mpdu->channel_est) < packet_payload_size ){
					copy_order = CHAN_EST_FIRST;
				} else {
					copy_order = PAYLOAD_FIRST;
				}
	#else
				copy_order = PAYLOAD_FIRST;
	#endif
			}

			// Compute the length of the DMA transfer to log the packet:
			//
			// We have two arrays in memory that we have to be aware of:
			//     1) The packet payload that has "packet_payload_size" bytes;
			//     2) The TX log entry that has "entry_payload_size" bytes;
			//
			// Because the packet payload does not have to be 32-bit aligned and we could be logging an arbitrary number of
			// bytes of the packet, we have to be careful about not walking off the end of either array. Therefore, we need
			// to transfer the shorter of the two arrays and then zero pad the log entry if we transfered less than
			// "entry_payload_size" bytes.
			//
			transfer_len = min(entry_payload_size, packet_payload_size);

			// Start copy based on the copy order
			switch(copy_order){
				case PAYLOAD_FIRST:
					if( rate != WLAN_MAC_MCS_1M ){
						((rx_ofdm_entry*)rx_event_log_entry)->mac_payload_log_len = entry_payload_size;
						wlan_mac_high_cdma_start_transfer((((rx_ofdm_entry*)rx_event_log_entry)->mac_payload), rx_80211_header, transfer_len);

						// Zero pad log entry if transfer_len was less than the allocated space in the log (ie entry_payload_size)
						if(transfer_len < entry_payload_size){
							bzero((u8*)(((u32)((rx_ofdm_entry*)rx_event_log_entry)->mac_payload) + transfer_len), (entry_payload_size - transfer_len));
						}
					} else {
						((rx_dsss_entry*)rx_event_log_entry)->mac_payload_log_len = entry_payload_size;
						wlan_mac_high_cdma_start_transfer((((rx_dsss_entry*)rx_event_log_entry)->mac_payload), rx_80211_header, transfer_len);

						// Zero pad log entry if transfer_len was less than the allocated space in the log (ie entry_payload_size)
						if(transfer_len < entry_payload_size){
							bzero((u8*)(((u32)((rx_dsss_entry*)rx_event_log_entry)->mac_payload) + transfer_len), (entry_payload_size - transfer_len));
						}
					}
				break;

				case CHAN_EST_FIRST:
	#ifdef WLAN_MAC_ENTRIES_LOG_CHAN_EST
					if(rate != WLAN_MAC_MCS_1M) wlan_mac_high_cdma_start_transfer(((rx_ofdm_entry*)rx_event_log_entry)->channel_est, rx_mpdu->channel_est, sizeof(rx_mpdu->channel_est));
	#endif
				break;
			}

			// Fill in Log Entry
			rx_event_log_entry->fcs_status = (rx_mpdu->state == RX_MPDU_STATE_FCS_GOOD) ? RX_ENTRY_FCS_GOOD : RX_ENTRY_FCS_BAD;
			rx_event_log_entry->timestamp  = rx_mpdu->timestamp;
			rx_event_log_entry->power      = rx_mpdu->rx_power;
			rx_event_log_entry->rf_gain    = rx_mpdu->rf_gain;
			rx_event_log_entry->bb_gain    = rx_mpdu->bb_gain;
			rx_event_log_entry->length     = rx_mpdu->phy_details.length;
			rx_event_log_entry->rate       = rx_mpdu->phy_details.mcs;
			rx_event_log_entry->pkt_type   = pkt_type;
			rx_event_log_entry->chan_num   = channel_num;
			rx_event_log_entry->ant_mode   = rx_mpdu->ant_mode;
			rx_event_log_entry->flags      = 0;


			// Start second copy based on the copy order
			switch(copy_order){
				case PAYLOAD_FIRST:
	#ifdef WLAN_MAC_ENTRIES_LOG_CHAN_EST
					if(rate != WLAN_MAC_MCS_1M) wlan_mac_high_cdma_start_transfer(((rx_ofdm_entry*)rx_event_log_entry)->channel_est, rx_mpdu->channel_est, sizeof(rx_mpdu->channel_est));
	#endif
				break;

				case CHAN_EST_FIRST:
					if( rate != WLAN_MAC_MCS_1M ){
						((rx_ofdm_entry*)rx_event_log_entry)->mac_payload_log_len = entry_payload_size;
						wlan_mac_high_cdma_start_transfer((((rx_ofdm_entry*)rx_event_log_entry)->mac_payload), rx_80211_header, transfer_len);

						// Zero pad log entry if transfer_len was less than the allocated space in the log (ie entry_payload_size)
						if(transfer_len < entry_payload_size){
							bzero((u8*)(((u32)((rx_ofdm_entry*)rx_event_log_entry)->mac_payload) + transfer_len), (entry_payload_size - transfer_len));
						}
					} else {
						((rx_dsss_entry*)rx_event_log_entry)->mac_payload_log_len = entry_payload_size;
						wlan_mac_high_cdma_start_transfer((((rx_dsss_entry*)rx_event_log_entry)->mac_payload), rx_80211_header, transfer_len);

						// Zero pad log entry if transfer_len was less than the allocated space in the log (ie entry_payload_size)
						if(transfer_len < entry_payload_size){
							bzero((u8*)(((u32)((rx_dsss_entry*)rx_event_log_entry)->mac_payload) + transfer_len), (entry_payload_size - transfer_len));
						}
					}
				break;
			}

	#ifdef _DEBUG_
			xil_printf("RX      : %8d    %8d    %8d    %8d    %8d\n", transfer_len, MIN_MAC_PAYLOAD_LOG_LEN, length, extra_payload, payload_log_len);
			print_buf((u8 *)((u32)rx_event_log_entry - 8), sizeof(rx_ofdm_entry) + extra_payload + 12);
	#endif
		}
	}

	if((rx_mpdu->flags & RX_MPDU_FLAGS_FORMED_RESPONSE) && (log_entry_en_mask & ENTRY_EN_MASK_TXRX_CTRL)){

		if(rx_80211_header->frame_control_1 == MAC_FRAME_CTRL1_SUBTYPE_RTS){
			//CREATE CTS LOG ENTRY
			entry_type = ENTRY_TYPE_TX_LOW;

			packet_payload_size = sizeof(mac_header_80211_CTS)+WLAN_PHY_FCS_NBYTES;

			// Get all the necessary sizes to log the packet
			wlan_exp_log_get_txrx_entry_sizes( entry_type, packet_payload_size, &entry_size, &entry_payload_size, &min_entry_payload_size );

			// Request space for a TX_LOW log entry
			tx_low_event_log_entry = (tx_low_entry *)wlan_exp_log_create_entry( entry_type, entry_size );

			if(tx_low_event_log_entry != NULL){
				// Store the payload size in the log entry
				tx_low_event_log_entry->mac_payload_log_len = entry_payload_size;

				// Create the payload for the log entry
				// The actual RTS bytes that were transmitted aren't visible to this function. We only have the underlying MPDU that
				// the RTS was trying to reserve the medium for. Instead, we can reconstruct what the RTS payload actually was in
				// this log entry.
				wlan_create_cts_frame((void*)(&((tx_low_entry*)tx_low_event_log_entry)->mac_payload),
									  rx_80211_header->address_2,
									  rx_mpdu->resp_low_tx_details.duration);

				//Because a CTS is smaller than a typical 24-byte 802.11 header, we need to be sure to zero pad out the rest of the payload
				//There is no good way to get a valid FCS for CTRL transmissions since the packet buffer is long gone.
				//Instead, we'll explicitly zero out those bytes as well.
				if((packet_payload_size-WLAN_PHY_FCS_NBYTES) < entry_payload_size){
					bzero((u8*)(((u32)((tx_low_entry*)tx_low_event_log_entry)->mac_payload) + (packet_payload_size-WLAN_PHY_FCS_NBYTES)),
						  (entry_payload_size -(packet_payload_size-WLAN_PHY_FCS_NBYTES)));
				}

				tx_low_event_log_entry->flags = 0;

				// Compute the timestamp of the actual Tx event
				//   CPU low accumulates time deltas relative to original enqueue time (easier to store u32 deltas vs u64 times)
				tx_low_event_log_entry->timestamp_send			  = (rx_mpdu->timestamp) + (rx_mpdu->resp_low_tx_details.timestamp_offset);

				pkt_type = wlan_mac_high_pkt_type(&((tx_low_entry*)tx_low_event_log_entry)->mac_payload, packet_payload_size);

				memcpy((&((tx_low_entry*)tx_low_event_log_entry)->phy_params), &(rx_mpdu->resp_low_tx_details.ctrl_phy_params), sizeof(phy_tx_params));

				tx_low_event_log_entry->transmission_count        = 1;
				tx_low_event_log_entry->unique_seq				  = 0;
				tx_low_event_log_entry->chan_num                  = rx_mpdu->resp_low_tx_details.chan_num;
				tx_low_event_log_entry->num_slots				  = rx_mpdu->resp_low_tx_details.num_slots;
				tx_low_event_log_entry->cw						  = rx_mpdu->resp_low_tx_details.cw;
				tx_low_event_log_entry->length                    = packet_payload_size;
				tx_low_event_log_entry->pkt_type				  = pkt_type;
			}



			} else if((rx_80211_header->frame_control_1 == MAC_FRAME_CTRL1_SUBTYPE_DATA) || (rx_80211_header->frame_control_1 == MAC_FRAME_CTRL1_SUBTYPE_QOSDATA)){
				//CREATE ACK LOG ENTRY
				entry_type = ENTRY_TYPE_TX_LOW;

				packet_payload_size = sizeof(mac_header_80211_ACK)+WLAN_PHY_FCS_NBYTES;

				// Get all the necessary sizes to log the packet
				wlan_exp_log_get_txrx_entry_sizes( entry_type, packet_payload_size, &entry_size, &entry_payload_size, &min_entry_payload_size );

				// Request space for a TX_LOW log entry
				tx_low_event_log_entry = (tx_low_entry *)wlan_exp_log_create_entry( entry_type, entry_size );

				if(tx_low_event_log_entry != NULL){
					// Store the payload size in the log entry
					tx_low_event_log_entry->mac_payload_log_len = entry_payload_size;

					// Create the payload for the log entry
					// The actual RTS bytes that were transmitted aren't visible to this function. We only have the underlying MPDU that
					// the RTS was trying to reserve the medium for. Instead, we can reconstruct what the RTS payload actually was in
					// this log entry.
					wlan_create_ack_frame((void*)(&((tx_low_entry*)tx_low_event_log_entry)->mac_payload),
										  rx_80211_header->address_2);

					//Because an ACK is smaller than a typical 24-byte 802.11 header, we need to be sure to zero pad out the rest of the payload
					//TODO: There is no good way to get a valid FCS for CTRL transmissions since the packet buffer is long gone.
					//Instead, we'll explicitly zero out those bytes as well.
					if((packet_payload_size-WLAN_PHY_FCS_NBYTES) < entry_payload_size){
						bzero((u8*)(((u32)((tx_low_entry*)tx_low_event_log_entry)->mac_payload) + (packet_payload_size-WLAN_PHY_FCS_NBYTES)),
							  (entry_payload_size -(packet_payload_size-WLAN_PHY_FCS_NBYTES)));
					}

					tx_low_event_log_entry->flags = 0;

					// Compute the timestamp of the actual Tx event
					//   CPU low accumulates time deltas relative to original enqueue time (easier to store u32 deltas vs u64 times)
					tx_low_event_log_entry->timestamp_send			  = (rx_mpdu->timestamp) + (rx_mpdu->resp_low_tx_details.timestamp_offset);

					pkt_type = wlan_mac_high_pkt_type(&((tx_low_entry*)tx_low_event_log_entry)->mac_payload, packet_payload_size);

					memcpy((&((tx_low_entry*)tx_low_event_log_entry)->phy_params), &(rx_mpdu->resp_low_tx_details.ctrl_phy_params), sizeof(phy_tx_params));

					tx_low_event_log_entry->transmission_count        = 1;
					tx_low_event_log_entry->unique_seq				  = 0;
					tx_low_event_log_entry->chan_num                  = rx_mpdu->resp_low_tx_details.chan_num;
					tx_low_event_log_entry->num_slots				  = rx_mpdu->resp_low_tx_details.num_slots;
					tx_low_event_log_entry->cw						  = rx_mpdu->resp_low_tx_details.cw;
					tx_low_event_log_entry->length                    = packet_payload_size;
					tx_low_event_log_entry->pkt_type				  = pkt_type;
				}
			}
	}

	return rx_event_log_entry;
}



/*****************************************************************************/
/**
* Determine RX/TX entry size
*
* @param    rx_frame_info * rx_mpdu
*               - RX MPDU of the associated RX entry
* 			u8 channel_number
* 			    - Indicates the channel on which the reception occurred
* 			u8 rate
* 			    - Indicates the rate at which the reception occurred
*
* @return	rx_common_entry *
*               - Pointer to the rx_common_entry log entry
*               @note This can be NULL if an entry was not allocated
*
* @note		None.
*
******************************************************************************/
void wlan_exp_log_get_txrx_entry_sizes( u32 entry_type, u16 packet_payload_size,
		                                u32 * entry_size, u32 * entry_payload_size, u32 * min_entry_payload_size ) {
	u32  base_entry_size;
    u32  pkt_bytes_to_log;
    u32  log_bytes_to_log;
    u32  extra_entry_payload;

    u32  tmp_entry_size;
	u32  tmp_entry_payload_size;
	u32  tmp_min_entry_payload_size;

	// Set the base entry size based on the entry type
	switch( entry_type ) {
	    case ENTRY_TYPE_RX_OFDM:
	    case ENTRY_TYPE_RX_OFDM_LTG:   base_entry_size = sizeof(rx_ofdm_entry);  break;

	    case ENTRY_TYPE_RX_DSSS:       base_entry_size = sizeof(rx_dsss_entry);  break;

	    case ENTRY_TYPE_TX_HIGH:
	    case ENTRY_TYPE_TX_HIGH_LTG:   base_entry_size = sizeof(tx_high_entry);  break;

	    case ENTRY_TYPE_TX_LOW:
	    case ENTRY_TYPE_TX_LOW_LTG:    base_entry_size = sizeof(tx_low_entry);   break;

	    default:                       base_entry_size = 0;                      break;
	}

	// Determine the minimum entry payload size based on entry type
	switch( entry_type ) {
	    // Non-LTG TX/RX Entry types
		case ENTRY_TYPE_RX_DSSS:
		case ENTRY_TYPE_RX_OFDM:
		case ENTRY_TYPE_TX_HIGH:
	    case ENTRY_TYPE_TX_LOW:
			tmp_min_entry_payload_size = MIN_MAC_PAYLOAD_LOG_LEN;
		break;

	    // LTG TX/RX Entry types
		case ENTRY_TYPE_RX_OFDM_LTG:
	    case ENTRY_TYPE_TX_HIGH_LTG:
	    case ENTRY_TYPE_TX_LOW_LTG:
			tmp_min_entry_payload_size = MIN_MAC_PAYLOAD_LTG_LOG_LEN;
	    break;

		default:
			tmp_min_entry_payload_size = MIN_MAC_PAYLOAD_LOG_LEN;
		break;
	}

	// Determine the entry size and payload size based on the entry type
	switch( entry_type ) {

		// Determine length required for RX / TX high log entry:
		//
		//   - mac_payload_log_len is a global variable that determines the maximum number of payload bytes to log.  This
		//         can be changed during runtime by WLAN Exp or other C code.
		//   - MIN_MAC_PAYLOAD_LOG_LEN and MIN_MAC_PAYLOAD_LTG_LOG_LEN define the minimum payload that should be logged
	    //         for regular and LTG packets, respectively.  This value is guaranteed to be 32-bit aligned (ie a multiple
		//         of 4 bytes).
	    //
	    // Procedure:
	    //   1) Determine the number of bytes we would log from the packet, enforcing the minimum number of bytes from 1).
	    //   2) Determine the number of bytes the infrastructure is asking us to log, enforcing the minimum number of bytes from 1).
	    //   3) Determine the number of bytes we will actually log by taking the minimum bytes from 2) and 3) so we don't
	    //          add extra bytes to the log for no reason.
	    //   4) Determine the number of bytes needed to be allocated for the log entry beyond the MIN_MAC_PAYLOAD_LOG_LEN which
	    //          is part of the log entry definition.
		//
		case ENTRY_TYPE_RX_DSSS:
	    case ENTRY_TYPE_RX_OFDM:
	    case ENTRY_TYPE_RX_OFDM_LTG:
	    case ENTRY_TYPE_TX_HIGH:
	    case ENTRY_TYPE_TX_HIGH_LTG:
	    	// Determine if we need to log the minimum entry payload size or the 32-bit aligned packet payload, whichever is larger
	    	pkt_bytes_to_log       = max(tmp_min_entry_payload_size, ((1 + ((packet_payload_size - 1) / 4))*4));

	    	// Determine if we need to log the mimimum entry payload size or the mac_payload_log_len, whichever is larger
	    	log_bytes_to_log       = max(tmp_min_entry_payload_size, mac_payload_log_len);

	    	// Log the minimum of either the pkt_bytes_to_log or the log_bytes_to_log
	    	tmp_entry_payload_size = min( pkt_bytes_to_log, log_bytes_to_log  );

	    	// Determine the extra payload bytes needed for the entry beyond the MIN_MAC_PAYLOAD_LOG_LEN already allocated
	    	extra_entry_payload    = (tmp_entry_payload_size > MIN_MAC_PAYLOAD_LOG_LEN) ? (tmp_entry_payload_size - MIN_MAC_PAYLOAD_LOG_LEN) : 0;

	    	// Then entry size is the base_entry_size plus the extra payload
	    	tmp_entry_size         = base_entry_size + extra_entry_payload;
	    break;


		// Determine length required for TX low log entry:
		//     - Log the MAC header.
        //
	    case ENTRY_TYPE_TX_LOW:
			tmp_entry_size             = base_entry_size;
			tmp_entry_payload_size     = sizeof(mac_header_80211);
		break;


		// Determine length required for TX low LTG log entry:
	    //     - Log the MAC header, LLC header, and LTG payload ID
        //
	    case ENTRY_TYPE_TX_LOW_LTG:
			tmp_entry_size             = base_entry_size + sizeof(ltg_packet_id);
			tmp_entry_payload_size     = sizeof(mac_header_80211) + sizeof(ltg_packet_id);
	    break;


	    default:
	    	wlan_exp_printf(WLAN_EXP_PRINT_WARNING, print_type_event_log, "Unknown entry type:  %d", entry_type);
	    	tmp_entry_size             = 0;
	    	tmp_entry_payload_size     = 0;
	    break;
	}

	// Assign output arguments
	*entry_size             = tmp_entry_size;
	*entry_payload_size     = tmp_entry_payload_size;
	*min_entry_payload_size = tmp_min_entry_payload_size;
}






#ifdef _DEBUG_


/*****************************************************************************/
/**
* Prints an entry
*
* @param    entry_number     - Index of entry in the log
*           entry_type       - Type of entry
*           timestamp        - Lower 32 bits of the timestamp
*           entry            - Pointer to the entry
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void print_entry( u32 entry_number, u32 entry_type, void * entry ){
	u32 i, j;

	node_info_entry    * node_info_entry_log_item;
	exp_info_entry     * exp_info_entry_log_item;
	wn_cmd_entry       * wn_cmd_entry_log_item;
	time_info_entry    * time_info_entry_log_item;
	txrx_stats_entry   * txrx_stats_entry_log_item;
	rx_common_entry    * rx_common_log_item;
	tx_high_entry      * tx_high_entry_log_item;
	tx_low_entry       * tx_low_entry_log_item;

	switch( entry_type ){
        case ENTRY_TYPE_NODE_INFO:
        	node_info_entry_log_item = (node_info_entry*) entry;
			xil_printf("%d: - Log Info entry\n", entry_number );
			xil_printf("   Timestamp   :   0x%08x  0x%08x\n", (u32)(node_info_entry_log_item->timestamp >>32), (u32)(node_info_entry_log_item->timestamp) );
			xil_printf("   Type        :   %d\n",       node_info_entry_log_item->type);
			xil_printf("   ID          :   0x%4x\n",    node_info_entry_log_item->id);
			xil_printf("   HW Gen      :   %d\n",       node_info_entry_log_item->hw_gen);
			xil_printf("   WN Ver      :   0x%08x\n",   node_info_entry_log_item->wn_ver);
			xil_printf("   FPGA DNA    :   0x%08x  0x%08x\n", (u32)(node_info_entry_log_item->fpga_dna >>32), (u32)(node_info_entry_log_item->fpga_dna) );
			xil_printf("   Serial Num  :   %d\n",       node_info_entry_log_item->serial_number);
			xil_printf("   WLAN Exp Ver:   0x%08x\n",   node_info_entry_log_item->wlan_exp_ver);
			xil_printf("   MAC Addr    :   0x%08x  0x%08x\n", (u32)(node_info_entry_log_item->wlan_mac_addr[1]), (u32)(node_info_entry_log_item->wlan_mac_addr[0]) );
			xil_printf("   Sched Res   :   %d\n",       node_info_entry_log_item->wlan_scheduler_resolution);
		break;

        case ENTRY_TYPE_EXP_INFO:
        	exp_info_entry_log_item = (exp_info_entry*) entry;
			xil_printf("%d: - Experiment Info entry\n", entry_number );
			xil_printf("   Timestamp:  %d\n", (u32)(exp_info_entry_log_item->timestamp));
			xil_printf("   Info Type:  %d\n",       exp_info_entry_log_item->info_type);
			xil_printf("   Message  :  \n");
			for( i = 0; i < exp_info_entry_log_item->info_length; i++) {
				xil_printf("        ");
				for( j = 0; j < 16; j++){
					xil_printf("0x%02x ", (exp_info_entry_log_item->info_payload)[16*i + j]);
				}
				xil_printf("\n");
			}
		break;

        case ENTRY_TYPE_WN_CMD:
        	wn_cmd_entry_log_item = (wn_cmd_entry*) entry;
			xil_printf("%d: - WARPNet Command entry\n", entry_number );
			xil_printf("   Timestamp:  %d\n", (u32)(wn_cmd_entry_log_item->timestamp));
			xil_printf("   Command  :  0x%08x\n",    wn_cmd_entry_log_item->command);
			xil_printf("   Args[%02d] :  \n",       wn_cmd_entry_log_item->num_args);
			for( i = 0; i < wn_cmd_entry_log_item->num_args; i++) {
				if (i == 10) break;
				xil_printf("        0x%08x \n", (wn_cmd_entry_log_item->args)[i]);
			}
        break;

        case ENTRY_TYPE_TIME_INFO:
        	time_info_entry_log_item = (time_info_entry*) entry;
			xil_printf("%d: - Time Info entry\n", entry_number );
			xil_printf("   Timestamp:  %d\n", (u32)(time_info_entry_log_item->timestamp));
			xil_printf("   Time id  :  %d\n",       time_info_entry_log_item->time_id);
			xil_printf("   Reason   :  %d\n",       time_info_entry_log_item->reason);
			xil_printf("   Abs time :  $d\n", (u32)(time_info_entry_log_item->abs_time));
			xil_printf("   New time :  %d\n", (u32)(time_info_entry_log_item->new_time));
        break;

		case ENTRY_TYPE_TXRX_STATS:
			txrx_stats_entry_log_item = (txrx_stats_entry*) entry;
			xil_printf("%d: - Statistics Event\n", entry_number );
			xil_printf("   Last timestamp :        %d\n",        (u32)(txrx_stats_entry_log_item->stats.last_txrx_timestamp));
			xil_printf("   Address        :        %02x",             (txrx_stats_entry_log_item->stats.addr)[0]);
			for( i = 1; i < 6; i++) { xil_printf(":%02x",         (txrx_stats_entry_log_item->stats.addr)[i]); }
			xil_printf("\n");
			xil_printf("   Is associated  :        %d\n",              txrx_stats_entry_log_item->stats.is_associated);
			xil_printf("   # Tx High Data MPDUs:   %d (%d successful)\n", txrx_stats_entry_log_item->stats.data.tx_num_packets_total, txrx_stats_entry_log_item->stats.data.tx_num_packets_success);
			xil_printf("   # Tx High Data bytes:   %d (%d successful)\n", (u32)(txrx_stats_entry_log_item->stats.data.tx_num_bytes_total), (u32)(txrx_stats_entry_log_item->stats.data.tx_num_bytes_success));
			xil_printf("   # Tx Low Data MPDUs:    %d\n", txrx_stats_entry_log_item->stats.data.tx_num_packets_low);
			xil_printf("   # Tx High Mgmt MPDUs:   %d (%d successful)\n", txrx_stats_entry_log_item->stats.mgmt.tx_num_packets_total, txrx_stats_entry_log_item->stats.mgmt.tx_num_packets_success);
			xil_printf("   # Tx High Mgmt bytes:   %d (%d successful)\n", (u32)(txrx_stats_entry_log_item->stats.mgmt.tx_num_bytes_total), (u32)(txrx_stats_entry_log_item->stats.mgmt.tx_num_bytes_success));
			xil_printf("   # Tx Low Mgmt MPDUs:    %d\n", txrx_stats_entry_log_item->stats.mgmt.tx_num_packets_low);
			xil_printf("   # Rx Data MPDUs:        %d\n", txrx_stats_entry_log_item->stats.data.rx_num_packets);
			xil_printf("   # Rx Data Bytes:        %d\n", txrx_stats_entry_log_item->stats.data.rx_num_bytes);
			xil_printf("   # Rx Mgmt MPDUs:        %d\n", txrx_stats_entry_log_item->stats.mgmt.rx_num_packets);
			xil_printf("   # Rx Mgmt Bytes:        %d\n", txrx_stats_entry_log_item->stats.mgmt.rx_num_bytes);
		break;

		case ENTRY_TYPE_RX_OFDM:
			rx_common_log_item = (rx_common_entry*) entry;
			xil_printf("%d: - Rx OFDM Event\n", entry_number );
#ifdef WLAN_MAC_ENTRIES_LOG_CHAN_EST
			xil_printf("   Channel Estimates:\n");

			for( i = 0; i < 16; i++) {
				xil_printf("        ");
				for( j = 0; j < 4; j++){
					xil_printf("0x%8x ", (((rx_ofdm_entry*)rx_common_log_item)->channel_est)[4*i + j]);
				}
				xil_printf("\n");
			}
#endif
			xil_printf("   Time:     %d\n",		(u32)(rx_common_log_item->timestamp));
			xil_printf("   FCS:      %d\n",     rx_common_log_item->fcs_status);
			xil_printf("   Pow:      %d\n",     rx_common_log_item->power);
			xil_printf("   Rate:     %d\n",     rx_common_log_item->rate);
			xil_printf("   Length:   %d\n",     rx_common_log_item->length);
			xil_printf("   Pkt Type: 0x%x\n",   rx_common_log_item->pkt_type);
			xil_printf("   Channel:  %d\n",     rx_common_log_item->chan_num);
		break;

		case ENTRY_TYPE_RX_DSSS:
			rx_common_log_item = (rx_common_entry*) entry;
			xil_printf("%d: - Rx DSSS Event\n", entry_number );
			xil_printf("   Time:     %d\n",		(u32)(rx_common_log_item->timestamp));
			xil_printf("   FCS:      %d\n",     rx_common_log_item->fcs_status);
			xil_printf("   Pow:      %d\n",     rx_common_log_item->power);
			xil_printf("   Rate:     %d\n",     rx_common_log_item->rate);
			xil_printf("   Length:   %d\n",     rx_common_log_item->length);
			xil_printf("   Pkt Type: 0x%x\n",   rx_common_log_item->pkt_type);
			xil_printf("   Channel:  %d\n",     rx_common_log_item->chan_num);
		break;

		case ENTRY_TYPE_TX_HIGH:
			tx_high_entry_log_item = (tx_high_entry*) entry;
			xil_printf("%d: - Tx High Event\n", entry_number);
			xil_printf("   Creation Time:    %d\n",		(u32)(tx_high_entry_log_item->timestamp_create));
			xil_printf("   Accept Delay:     %d\n",		(u32)(tx_high_entry_log_item->delay_accept));
			xil_printf("   Done Delay:       %d\n",		(u32)(tx_high_entry_log_item->delay_done));
			xil_printf("   Tx Unique Seq:    %d\n",		(u32)(tx_high_entry_log_item->unique_seq));
			xil_printf("   Tx Power:         %d\n",     tx_high_entry_log_item->power);
			xil_printf("   Rate:             %d\n",     tx_high_entry_log_item->rate);
			xil_printf("   Length:           %d\n",     tx_high_entry_log_item->length);
			xil_printf("   Channel:          %d\n",     tx_high_entry_log_item->chan_num);
			xil_printf("   Result:           %d\n",     tx_high_entry_log_item->result);
			xil_printf("   Pkt Type:         0x%x\n",   tx_high_entry_log_item->pkt_type);
			xil_printf("   Num Tx:           %d\n",     tx_high_entry_log_item->num_tx);
		break;

		case ENTRY_TYPE_TX_LOW:
			tx_low_entry_log_item = (tx_low_entry*) entry;
			xil_printf("%d: - Tx Low Event\n", entry_number);
			xil_printf("   Tx Start Time:    %d\n",		(u32)(tx_low_entry_log_item->timestamp_send));
			xil_printf("   Tx Unique Seq:    %d\n",		(u32)(tx_low_entry_log_item->unique_seq));
			xil_printf("   Tx Count:         %d\n",		tx_low_entry_log_item->transmission_count);
			xil_printf("   Power:            %d\n",     tx_low_entry_log_item->phy_params.power);
			xil_printf("   Rate:             %d\n",     tx_low_entry_log_item->phy_params.rate);
			xil_printf("   Length:           %d\n",     tx_low_entry_log_item->length);
			xil_printf("   Channel:          %d\n",     tx_low_entry_log_item->chan_num);
			xil_printf("   Pkt Type:         0x%x\n",   tx_low_entry_log_item->pkt_type);
			xil_printf("   Antenna Mode:     %d\n",     tx_low_entry_log_item->phy_params.antenna_mode);
			xil_printf("   # of BO Slots     %d\n",     tx_low_entry_log_item->num_slots);
		break;

		default:
			xil_printf("%d: - Unknown Event\n", entry_number);
		break;
	}

}

#endif

