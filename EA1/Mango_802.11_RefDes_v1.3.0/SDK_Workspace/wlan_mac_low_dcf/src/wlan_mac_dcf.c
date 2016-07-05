/** @file wlan_mac_dcf.c
 *  @brief Distributed Coordination Function
 *
 *  This contains code to implement the 802.11 DCF.
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
#define DBG_PRINT 0

// Xilinx SDK includes
#include "xparameters.h"
#include <stdio.h>
#include <stdlib.h>
#include "xtmrctr.h"
#include "xio.h"
#include <string.h>

// WARP includes
#include "wlan_mac_low.h"
#include "w3_userio.h"
#include "radio_controller.h"

#include "wlan_mac_ipc_util.h"
#include "wlan_mac_802_11_defs.h"
#include "wlan_mac_misc_util.h"
#include "wlan_phy_util.h"
#include "wlan_mac_dcf.h"

#include "wlan_exp.h"
#include "math.h"


#define WARPNET_TYPE_80211_LOW         WARPNET_TYPE_80211_LOW_DCF
#define NUM_LEDS                       4

volatile static u32                    gl_stationShortRetryCount;
volatile static u32                    gl_stationLongRetryCount;
volatile static u32                    gl_cw_exp;

volatile static u32					   gl_dot11RTSThreshold;

volatile static u8                     gl_autocancel_en;
volatile static u8                     gl_autocancel_match_type;
volatile static u8                     gl_autocancel_match_addr3[6];
volatile static u64                    gl_autocancel_last_rx_ts;

volatile static u8                     gl_eeprom_addr[6];

volatile static u8					   gl_mpdu_pkt_buf;

volatile static u32					   gl_dot11ShortRetryLimit;
volatile static u32 				   gl_dot11LongRetryLimit;

volatile u8                            gl_red_led_index;
volatile u8                            gl_green_led_index;


int main(){
	wlan_mac_hw_info* hw_info;
	xil_printf("\f");
	xil_printf("----- Mango 802.11 Reference Design -----\n");
	xil_printf("----- v1.3 ------------------------------\n");
	xil_printf("----- wlan_mac_dcf ----------------------\n");
	xil_printf("Compiled %s %s\n\n", __DATE__, __TIME__);

	xil_printf("Note: this UART is currently printing from CPU_LOW. To view prints from\n");
	xil_printf("and interact with CPU_HIGH, raise the right-most User I/O DIP switch bit.\n");
	xil_printf("This switch can be toggled any time while the design is running.\n\n");

	gl_autocancel_en = 0;
	gl_mpdu_pkt_buf = PKT_BUF_INVALID;

	gl_autocancel_match_addr3[0] = 0x00;
	gl_autocancel_match_addr3[1] = 0x00;
	gl_autocancel_match_addr3[2] = 0x00;
	gl_autocancel_match_addr3[3] = 0x00;
	gl_autocancel_match_addr3[4] = 0x00;
	gl_autocancel_match_addr3[5] = 0x00;
	gl_autocancel_match_type     = 0x00;
	gl_autocancel_last_rx_ts = 0;

	gl_dot11ShortRetryLimit = 7;
	gl_dot11LongRetryLimit = 4;

	gl_dot11RTSThreshold = 2000;

	gl_stationShortRetryCount = 0;
	gl_stationLongRetryCount = 0;


	wlan_tx_config_ant_mode(TX_ANTMODE_SISO_ANTA);

	gl_red_led_index = 0;
	gl_green_led_index = 0;
	userio_write_leds_green(USERIO_BASEADDR, (1<<gl_green_led_index));
	userio_write_leds_red(USERIO_BASEADDR, (1<<gl_red_led_index));

	wlan_mac_low_init(WARPNET_TYPE_80211_LOW);

	gl_cw_exp = wlan_mac_low_get_cw_exp_min();

	hw_info = wlan_mac_low_get_hw_info();
	memcpy((void*)gl_eeprom_addr, hw_info->hw_addr_wlan, 6);

	wlan_mac_low_set_frame_rx_callback((void*)frame_receive);
	wlan_mac_low_set_frame_tx_callback((void*)frame_transmit);
	wlan_mac_low_set_ipc_low_param_callback((void*)wlan_dcf_process_low_param);

	if(lock_pkt_buf_tx(TX_PKT_BUF_ACK_CTS) != PKT_BUF_MUTEX_SUCCESS){
		warp_printf(PL_ERROR, "Error: unable to lock ACK packet buf %d\n", TX_PKT_BUF_ACK_CTS);
		wlan_mac_low_send_exception(EXC_MUTEX_TX_FAILURE);
		return -1;
	}

	if(lock_pkt_buf_tx(TX_PKT_BUF_RTS) != PKT_BUF_MUTEX_SUCCESS){
		warp_printf(PL_ERROR, "Error: unable to lock ACK packet buf %d\n", TX_PKT_BUF_RTS);
		wlan_mac_low_send_exception(EXC_MUTEX_TX_FAILURE);
		return -1;
	}

	wlan_mac_low_finish_init();

    xil_printf("Initialization Finished\n");

	while(1){
		//Poll PHY RX start
		wlan_mac_low_poll_frame_rx();

		//Poll IPC rx
		wlan_mac_low_poll_ipc_rx();
	}
	return 0;
}

/**
 * @brief Handles reception of a wireless packet
 *
 * This function is called after a good SIGNAL field is detected by either PHY (OFDM or DSSS)
 * It is the responsibility of this function to wait until a sufficient number of bytes have been received
 * before it can start to process those bytes. When this function is called the eventual checksum status is
 * unknown. The packet contents can be provisionally processed (e.g. prepare an ACK for fast transmission),
 * but post-reception actions must be conditioned on the eventual FCS status (good or bad).
 *
 * Note: The timing of this function is critical for correct operation of the 802.11 DCF. It is not
 * safe to add large delays to this function (e.g. xil_printf or usleep)
 *
 * Two primary job responsibilities of this function:
 *  (1): Prepare outgoing ACK packets and instruct the MAC_DCF_HW core whether or not to send ACKs
 *  (2): Pass up MPDUs (FCS valid or invalid) to CPU_HIGH
 *
 * @param u8 rx_pkt_buf
 *  -Index of the Rx packet buffer containing the newly recevied packet
 * @param phy_rx_details* phy_details
 *  -Pointer to phy_rx_details struct containing PHY mode, MCS, and Length
 * @return
 *  -Bit mask of flags indicating various results of the reception
 */
u32 frame_receive(u8 rx_pkt_buf, phy_rx_details* phy_details) {

	//RX_LEN_THRESH is used to manage a potential pipeline bubble
	//that can be used during a reception for processing.
	//
	// - if the ongoing reception is >RX_LEN_THRESH, we will start
	//   processing the frame and filling in metadata into the packet
	//   buffer prior to calling wlan_mac_dcf_hw_rx_finish().
	// - if the ongoing reception is <RX_LEN_THRESH, we'll immediately
	//   start polling the PHY with wlan_mac_dcf_hw_rx_finish() and,
	//   if need be, configure a MAC Tx core to send a response.
	//
	//This structure handles any risk of response packets (e.g. an ACK)
	//not being configured in time for the hard SIFS boundary.

	#define RX_LEN_THRESH 200

	u32 return_value;
	u32 tx_length;
	u8 tx_phy_rate;
	u8 tx_mcs;
	u16 tx_N_DBPS;
	u16 cts_duration;
	u8 unicast_to_me, to_multicast;
	u16 rssi;
	u8 lna_gain;
	u8 active_rx_ant;
	u32 rx_filter;
	u8 report_to_mac_high;
	u8 ctrl_tx_gain;
	unsigned char mpdu_tx_ant_mask = 0;
	u8 num_resp_failures = 0;


	rx_finish_state_t rx_finish_state = RX_FINISH_SEND_NONE;
	tx_pending_state_t tx_pending_state = TX_PENDING_NONE;

	rx_frame_info* mpdu_info;
	mac_header_80211* rx_header;

	u32 mac_hw_status;

	//Translate Rx pkt buf index into actual memory address
	void* pkt_buf_addr = (void *)RX_PKT_BUF_TO_ADDR(rx_pkt_buf);

	return_value = 0;

	//Get pointer to MPDU info struct (stored at 0 offset in the pkt buffer)
	mpdu_info = (rx_frame_info*)pkt_buf_addr;

	mpdu_info->flags = 0;

	//Apply the mac_header_80211 template to the first bytes of the received MPDU
	rx_header = (mac_header_80211*)((void*)(pkt_buf_addr + PHY_RX_PKT_BUF_MPDU_OFFSET));

	//Sanity check length value - anything shorter than an ACK must be bogus
	if( (phy_details->length) < ( sizeof(mac_header_80211_ACK) + WLAN_PHY_FCS_NBYTES ) ){
		//warp_printf(PL_ERROR, "Error: received packet of length %d, which is not valid\n", length);
		wlan_mac_dcf_hw_rx_finish();
		wlan_mac_dcf_hw_unblock_rx_phy();
		return return_value;
	}

	//Translate the rate index into the rate code used by the Tx PHY
	// This translation is required in case this reception needs to send an ACK, as the ACK
	// rate is a function of the rate of the received packet
	//The mapping of Rx rate to ACK rate is given in 9.7.6.5.2 of 802.11-2012
	tx_mcs = wlan_mac_mcs_to_ctrl_resp_mcs( phy_details->mcs );
	tx_phy_rate = wlan_mac_mcs_to_phy_rate( tx_mcs );
	tx_N_DBPS = wlan_mac_mcs_to_n_dbps( tx_mcs );

	//Determine which antenna the ACK will be sent from
	// The current implementation transmits ACKs from the same antenna over which the previous packet was received
	unsigned char tx_ant_mask = 0;
	active_rx_ant = (wlan_phy_rx_get_active_rx_ant());
	switch(active_rx_ant){
		case RX_ACTIVE_ANTA:
			tx_ant_mask |= 0x1;
		break;
		case RX_ACTIVE_ANTB:
			tx_ant_mask |= 0x2;
		break;
		case RX_ACTIVE_ANTC:
			tx_ant_mask |= 0x4;
		break;
		case RX_ACTIVE_ANTD:
			tx_ant_mask |= 0x8;
		break;
		default:
			tx_ant_mask = 0x1;
		break;
	}

	//Wait until the PHY has written enough bytes so that the first address field can be processed

	while(wlan_mac_get_last_byte_index() < MAC_HW_LASTBYTE_ADDR1){
		if(DBG_PRINT) xil_printf("Waiting for Rx Bytes (%d < %d)\n", wlan_mac_get_last_byte_index(), MAC_HW_LASTBYTE_ADDR1);
	};

	//Check the destination address
	unicast_to_me = wlan_addr_eq(rx_header->address_1, gl_eeprom_addr);
	to_multicast = wlan_addr_mcast(rx_header->address_1);

	//Prep outgoing ACK just in case it needs to be sent
	// ACKs are only sent for non-control frames addressed to this node
	if( unicast_to_me && !WLAN_IS_CTRL_FRAME(rx_header) ) {
		//Auto TX Delay is in units of 100ns. This delay runs from RXEND of the preceding reception.
		//wlan_mac_tx_ctrl_B_params(pktBuf, antMask, req_zeroNAV, preWait_postRxTimer1, preWait_postRxTimer2, postWait_postTxTimer1)
		wlan_mac_tx_ctrl_B_params(TX_PKT_BUF_ACK_CTS, tx_ant_mask, 0, 1, 0, 0);
		
		//ACKs are transmitted with a nominal Tx power used for all control packets
		ctrl_tx_gain = wlan_mac_low_dbm_to_gain_target(wlan_mac_low_get_current_ctrl_tx_pow());
		wlan_mac_tx_ctrl_B_gains(ctrl_tx_gain, ctrl_tx_gain, ctrl_tx_gain, ctrl_tx_gain);

		//Construct the ACK frame in the dedicated Tx pkt buf
		tx_length = wlan_create_ack_frame((void*)(TX_PKT_BUF_TO_ADDR(TX_PKT_BUF_ACK_CTS) + PHY_TX_PKT_BUF_MPDU_OFFSET), rx_header->address_2);

		//Write the SIGNAL field for the ACK
		wlan_phy_set_tx_signal(TX_PKT_BUF_ACK_CTS, tx_phy_rate, tx_length);

		rx_finish_state = RX_FINISH_SEND_B;

		mpdu_info->resp_low_tx_details.tx_details_type = TX_DETAILS_ACK;
		mpdu_info->resp_low_tx_details.ctrl_phy_params.rate = tx_mcs;

		//We let "duration" be equal to the duration field of an ACK. This value is provided explicitly to CPU_HIGH
		//in the low_tx_details struct such that CPU_HIGH has can reconstruct the RTS in its log. This isn't critical
		//to the operation of the DCF, but is critical for the logging framework.
		mpdu_info->resp_low_tx_details.duration = 0;

		//This element remains unused during MPDU-only transmissions
		mpdu_info->resp_low_tx_details.ctrl_phy_params.power = wlan_mac_low_get_current_ctrl_tx_pow();
		mpdu_info->resp_low_tx_details.ctrl_phy_params.antenna_mode = active_rx_ant;


	} else if( unicast_to_me && (rx_header->frame_control_1 == MAC_FRAME_CTRL1_SUBTYPE_CTS) ){
		if( gl_mpdu_pkt_buf != PKT_BUF_INVALID ){
			//We have an outgoing data frame we should send
			//Configure the Tx antenna selection
			//The frame_transmit() context already configured the SIGNAL field,
			//so we do not have to worry about it in this context
			tx_frame_info* tx_mpdu_info = (tx_frame_info*) (TX_PKT_BUF_TO_ADDR(gl_mpdu_pkt_buf));
			int curr_tx_pow;
			switch(tx_mpdu_info->params.phy.antenna_mode) {
				case TX_ANTMODE_SISO_ANTA:
					mpdu_tx_ant_mask |= 0x1;
				break;
				case TX_ANTMODE_SISO_ANTB:
					mpdu_tx_ant_mask |= 0x2;
				break;
				case TX_ANTMODE_SISO_ANTC:
					mpdu_tx_ant_mask |= 0x4;
				break;
				case TX_ANTMODE_SISO_ANTD:
					mpdu_tx_ant_mask |= 0x8;
				break;
				default:
					mpdu_tx_ant_mask = 0x1;
				break;
			}

			//Configure the Tx power - update all antennas, even though only one will be used
			curr_tx_pow = wlan_mac_low_dbm_to_gain_target(tx_mpdu_info->params.phy.power);
			wlan_mac_tx_ctrl_A_gains(curr_tx_pow, curr_tx_pow, curr_tx_pow, curr_tx_pow);
			wlan_mac_tx_ctrl_A_params(gl_mpdu_pkt_buf, mpdu_tx_ant_mask, 0, 1, 0, 1); //Use postRx timer 1 and postTx_timer2

			rx_finish_state = RX_FINISH_SEND_A;

			return_value |= POLL_MAC_TYPE_CTS;

		} else {
			xil_printf("Error: unexpected CTS to me\n");
		}
	} else if(unicast_to_me && (rx_header->frame_control_1 == MAC_FRAME_CTRL1_SUBTYPE_RTS)){
		//We need to send a CTS
		//Auto TX Delay is in units of 100ns. This delay runs from RXEND of the preceding reception.
		//wlan_mac_tx_ctrl_B_params(pktBuf, antMask, req_zeroNAV, preWait_postRxTimer1, preWait_postRxTimer2, postWait_postTxTimer1)
		wlan_mac_tx_ctrl_B_params(TX_PKT_BUF_ACK_CTS, tx_ant_mask, 1, 1, 0, 0);

		//ACKs are transmitted with a nominal Tx power used for all control packets
		ctrl_tx_gain = wlan_mac_low_dbm_to_gain_target(wlan_mac_low_get_current_ctrl_tx_pow());
		wlan_mac_tx_ctrl_B_gains(ctrl_tx_gain, ctrl_tx_gain, ctrl_tx_gain, ctrl_tx_gain);

		cts_duration = sat_sub(rx_header->duration_id, (T_SIFS) + wlan_ofdm_txtime(sizeof(mac_header_80211_CTS) + WLAN_PHY_FCS_NBYTES, tx_N_DBPS));

		//Construct the ACK frame in the dedicated Tx pkt buf
		tx_length = wlan_create_cts_frame((void*)(TX_PKT_BUF_TO_ADDR(TX_PKT_BUF_ACK_CTS) + PHY_TX_PKT_BUF_MPDU_OFFSET),
										  rx_header->address_2,
										  cts_duration);

		//Write the SIGNAL field for the CTS
		wlan_phy_set_tx_signal(TX_PKT_BUF_ACK_CTS, tx_phy_rate, tx_length);

		rx_finish_state = RX_FINISH_SEND_B;

		mpdu_info->resp_low_tx_details.tx_details_type = TX_DETAILS_CTS;
		mpdu_info->resp_low_tx_details.ctrl_phy_params.rate = tx_mcs;

		//We let "duration" be equal to the duration field of an CTS. This value is provided explicitly to CPU_HIGH
		//in the low_tx_details struct such that CPU_HIGH has can reconstruct the RTS in its log. This isn't critical
		//to the operation of the DCF, but is critical for the logging framework.
		mpdu_info->resp_low_tx_details.duration = cts_duration;

		//This element remains unused during MPDU-only transmissions
		mpdu_info->resp_low_tx_details.ctrl_phy_params.power = wlan_mac_low_get_current_ctrl_tx_pow();
		mpdu_info->resp_low_tx_details.ctrl_phy_params.antenna_mode = active_rx_ant;
	}

	if( (phy_details->length) <= RX_LEN_THRESH ){
		mpdu_info->state = wlan_mac_dcf_hw_rx_finish();

		if(mpdu_info->state == RX_MPDU_STATE_FCS_GOOD){
			switch( rx_finish_state ){
				case RX_FINISH_SEND_A:
					wlan_mac_tx_ctrl_A_start(1);
					wlan_mac_tx_ctrl_A_start(0);
					tx_pending_state = TX_PENDING_A;
				break;

				case RX_FINISH_SEND_B:
					wlan_mac_tx_ctrl_B_start(1);
					wlan_mac_tx_ctrl_B_start(0);
					tx_pending_state = TX_PENDING_B;
				break;

				default:
				case RX_FINISH_SEND_NONE:
				break;
			}
		}
		rx_finish_state = RX_FINISH_SEND_NONE;
	}


	//Check if this reception is an ACK
	if((rx_header->frame_control_1) == MAC_FRAME_CTRL1_SUBTYPE_ACK){
		return_value |= POLL_MAC_TYPE_ACK;
	}

	//Update metadata about this reception
	mpdu_info->phy_details = *phy_details;

	if((rx_header->frame_control_2) & MAC_FRAME_CTRL2_FLAG_RETRY) {
		//This reception was a re-transmission by the other node
		mpdu_info->flags |= RX_MPDU_FLAGS_RETRY;
	}

	mpdu_info->channel = wlan_mac_low_get_active_channel();
	mpdu_info->timestamp = get_rx_start_timestamp();

	//Record the antenna selection, AGC gain selections and Rx power to the Rx pkt metadata
	mpdu_info->ant_mode = active_rx_ant;

	mpdu_info->rf_gain = wlan_phy_rx_get_agc_RFG(active_rx_ant);
	mpdu_info->bb_gain = wlan_phy_rx_get_agc_BBG(active_rx_ant);

	lna_gain = wlan_phy_rx_get_agc_RFG(active_rx_ant);
	rssi = wlan_phy_rx_get_pkt_rssi(active_rx_ant);
	mpdu_info->rx_power = wlan_mac_low_calculate_rx_power(rssi, lna_gain);

	//Block until the reception is complete, storing the checksum status in the frame_info struct
	if( (phy_details->length) > RX_LEN_THRESH ){
		mpdu_info->state = wlan_mac_dcf_hw_rx_finish();
	}

	//Check if this reception should trigger the cancellation of a pending or future transmission
	// This is used by the IBSS application to cancel a pending beacon transmission when
	// a beacon is received from a peer node
	if( (mpdu_info->state == RX_MPDU_STATE_FCS_GOOD) && //Rx pkt checksum good
			(rx_header->frame_control_1 == gl_autocancel_match_type) && //Pkt type matches auto-cancel condition
			(wlan_addr_eq(rx_header->address_3, gl_autocancel_match_addr3) && //Pkt addr3 matches auto-cancel condition when pkt has addr3
			(phy_details->length) >= sizeof(mac_header_80211) ) ) {

		if(gl_autocancel_en) {
			//Clobber all state in the DCF core - this cancels deferrals and pending transmissions
			wlan_mac_reset(1);
			wlan_mac_reset(0);
			return_value |= POLL_MAC_CANCEL_TX;
		}

		//Whether or not a transmission was just canceled, remember the timestamp of this auto-cancel-worthy packet reception
		// This handles a race condition, where a beacon is received after CPU High has pushed down a new beacon with the
		// TX_MPDU_FLAGS_AUTOCANCEL flag set, but a beacon is received before frame_transmit() is called. The timestamp
		// recorded here is compared to the current time immediately before a new beacon might be transmitted, allowing
		// just-in-time cancellation of the transmission
		gl_autocancel_last_rx_ts = get_rx_start_timestamp();
	}

	if(mpdu_info->state == RX_MPDU_STATE_FCS_GOOD) {
		//Received packet had good checksum

		//Increment green LEDs
		gl_green_led_index = (gl_green_led_index + 1) % NUM_LEDS;
		userio_write_leds_green(USERIO_BASEADDR, (1<<gl_green_led_index));

		return_value |= POLL_MAC_STATUS_GOOD;

		//Check if this packet should be passed up to CPU High for further processing
		rx_filter = wlan_mac_low_get_current_rx_filter();

		switch(rx_filter & RX_FILTER_HDR_MASK){
			default:
			case RX_FILTER_HDR_ADDR_MATCH_MPDU:
				//Non-control packet either addressed to me or addressed to multicast address
				report_to_mac_high = (unicast_to_me || to_multicast) && !WLAN_IS_CTRL_FRAME(rx_header);
			break;
			case RX_FILTER_HDR_ALL_MPDU:
				//Any non-control packet
				report_to_mac_high = !WLAN_IS_CTRL_FRAME(rx_header);
			break;
			case RX_FILTER_HDR_ALL:
				//All packets (data, management and control; no type or address filtering)
				report_to_mac_high = 1;
			break;
		}

		//Sanity check packet length - if the header says non-control but the length is shorter than a full MAC header
		// it must be invalid; this should never happen, but better to catch rare events here than corrupt state in CPU High
		if(!WLAN_IS_CTRL_FRAME(rx_header) && (phy_details->length < sizeof(mac_header_80211))) {
			report_to_mac_high = 0;
		}

		if(unicast_to_me) {
			return_value |= POLL_MAC_ADDR_MATCH;
		}

		if( (phy_details->length) > RX_LEN_THRESH ){
			switch( rx_finish_state ){
				case RX_FINISH_SEND_A:
					wlan_mac_tx_ctrl_A_start(1);
					wlan_mac_tx_ctrl_A_start(0);
					tx_pending_state = TX_PENDING_A;
				break;

				case RX_FINISH_SEND_B:
					wlan_mac_tx_ctrl_B_start(1);
					wlan_mac_tx_ctrl_B_start(0);
					tx_pending_state = TX_PENDING_B;
				break;

				default:
				case RX_FINISH_SEND_NONE:
				break;
			}
		}


	} else {
		//Received checksum was bad
		//Increment red LEDs
		gl_red_led_index = (gl_red_led_index + 1) % NUM_LEDS;
		userio_write_leds_red(USERIO_BASEADDR, (1<<gl_red_led_index));

		//Check if this packet should be passed up to CPU High for further processing
		rx_filter = wlan_mac_low_get_current_rx_filter();
		switch(rx_filter & RX_FILTER_FCS_MASK) {
			default:
			case RX_FILTER_FCS_GOOD:
				report_to_mac_high = 0;
			break;
			case RX_FILTER_FCS_ALL:
				report_to_mac_high = 1;
			break;
		}

	} //END else (FCS was bad)




	//Wait for MAC CFG A or B to finish starting a response transmission
	switch(tx_pending_state){
		default:
		case TX_PENDING_A:
			//We don't need to do anything here for pending transmissions from CFG A.
			//The only time this case occurs is when we are sending an MPDU in response to
			//a CTS. We don't need to update any fields here since reporting of the MPDU Tx
			//is the responsibility of the frame_transmit context.
		break;
		case TX_PENDING_B:
			do{
				mac_hw_status = wlan_mac_get_status();

				if( (mac_hw_status & WLAN_MAC_STATUS_MASK_TX_B_STATE) == WLAN_MAC_STATUS_TX_B_STATE_DONE){
					if( (wlan_mac_get_status() & WLAN_MAC_STATUS_MASK_TX_B_RESULT) != WLAN_MAC_STATUS_TX_B_RESULT_NO_TX ){
						mpdu_info->flags = mpdu_info->flags & ~RX_MPDU_FLAGS_FORMED_RESPONSE;
						break;
					}
				} else if( (mac_hw_status & WLAN_MAC_STATUS_MASK_TX_B_STATE) == WLAN_MAC_STATUS_TX_B_STATE_DO_TX ) {
					mpdu_info->flags |= RX_MPDU_FLAGS_FORMED_RESPONSE;
					break;
				} else if( ((mac_hw_status & WLAN_MAC_STATUS_MASK_TX_B_STATE) == WLAN_MAC_STATUS_TX_B_STATE_PRE_TX_WAIT) &&
						   ((mac_hw_status & WLAN_MAC_STATUS_MASK_POSTRX_TIMER1_RUNNING) == 0 )){
					//This is potentially a bad state. It likely means we were late in processing this reception
					//There is a slight race condition in detecting this state. There is a small 1 or 2 cycle window where this
					//check can inaccurately deem a failed response transmission. As such, we'll require the condition to be met
					//multiple times.
					num_resp_failures++;
					if(num_resp_failures > 2){
						mpdu_info->flags = mpdu_info->flags & ~RX_MPDU_FLAGS_FORMED_RESPONSE;
						//TODO: We should force TX_B back to an idle state here since it is still primed
						break;
					}
				}
			} while(mac_hw_status & WLAN_MAC_STATUS_MASK_TX_B_PENDING);
		break;
	}

	if( mpdu_info->flags & RX_MPDU_FLAGS_FORMED_RESPONSE ){
		mpdu_info->resp_low_tx_details.timestamp_offset = (u32)(get_tx_start_timestamp() - mpdu_info->timestamp);
	}

	if(report_to_mac_high) {
		//This packet should be passed up to CPU_high for further processing

		//Unlock the pkt buf mutex before passing the packet up
		// If this fails, something has gone horribly wrong
		if(unlock_pkt_buf_rx(rx_pkt_buf) != PKT_BUF_MUTEX_SUCCESS){
			xil_printf("Error: unable to unlock RX pkt_buf %d\n", rx_pkt_buf);
			wlan_mac_low_send_exception(EXC_MUTEX_RX_FAILURE);
		} else {
			wlan_mac_low_frame_ipc_send();
			//Find a free packet buffer and begin receiving packets there (blocks until free buf is found)
			wlan_mac_low_lock_empty_rx_pkt_buf();
		}
	}

	//Unblock the PHY post-Rx (no harm calling this if the PHY isn't actually blocked)
	wlan_mac_dcf_hw_unblock_rx_phy();

//	//If auto-tx ACK is currently transmitting, wait for it to finish before returning
//    do{
//    	mac_hw_status = wlan_mac_get_status();
//    } while(mac_hw_status & WLAN_MAC_STATUS_MASK_TX_B_PENDING);


	return return_value;
}



/**
 * @brief Handles transmission of a wireless packet
 *
 * This function is called to transmit a new packet via the DCF+PHY. This code interacts with the wlan_mac_dcf_hw core
 * to manage MAC and PHY state. This function should be called once per packet and will return after the full transmission
 * state machine has executed for that packet. This state machine includes channel access (including carrier sensing, deferrals and
 * backoffs), ACK reception, timeouts and re-transmissions.
 *
 * This function is called once per IPC_MBOX_TX_MPDU_READY message from CPU High. The IPC_MBOX_TX_MPDU_DONE message will be sent
 * back to CPU High when this function returns.
 *
 * @param u8 rx_pkt_buf
 *  -Index of the Tx packet buffer containing the packet to transmit
 * @param u8 rate
 *  -Index of PHY rate at which packet will be transmitted
 * @param u16 length
 *  -Number of bytes in packet, including MAC header and FCS
 * @param wlan_mac_low_tx_details* low_tx_details
 *  -Pointer to array of metadata entries to be created for each PHY transmission of this packet (eventually leading to TX_LOW log entries)
 * @return
 *  -Transmission result
 */
int frame_transmit(u8 mpdu_pkt_buf, u8 mpdu_rate, u16 mpdu_length, wlan_mac_low_tx_details* low_tx_details) {
	//The pkt_buf, rate, and length arguments provided to this function specifically relate to
	//the MPDU that the WLAN MAC LOW framework wants us to send. We may opt to first send an RTS
	//to reserve the medium prior to doing this. The tx_rate, tx_length, and tx_pkt_buf relate
	//to whatever the next waveform will be. That waveform could be an RTS, or it could be the
	//MPDU itself.

	u8 mac_cfg_rate;
	u16 mac_cfg_length;
	u8 mac_cfg_pkt_buf;
	u16 rts_header_duration;
	u8 req_timeout;
	u8 req_backoff;
	u16 n_slots = 0;
	u32 rx_status;
	u16 cts_header_duration;
	u16 MPDU_N_DBPS;
	tx_frame_info* mpdu_info = (tx_frame_info*) (TX_PKT_BUF_TO_ADDR(mpdu_pkt_buf));
	u64 last_tx_timestamp;
	int curr_tx_pow;
	mac_header_80211* header = (mac_header_80211*)(TX_PKT_BUF_TO_ADDR(mpdu_pkt_buf) + PHY_TX_PKT_BUF_MPDU_OFFSET);
	u64 autocancel_curr_timestamp;
	u64 autocancel_timestamp_diff;
	u32 mac_hw_status;


	tx_wait_state_t tx_wait_state;
	tx_mode_t tx_mode;

	//This state variable will inform the rest of the frame_transmit function
	//on whether the code is actively waiting for an ACK, for an RTS, or not
	//waiting for anything.
	tx_wait_state = TX_WAIT_NONE;

	//Reset SRC/LRC and num_tx_attempts (which is the union of SRC and LRC)
	mpdu_info->short_retry_count = 0;
	mpdu_info->long_retry_count = 0;
	mpdu_info->num_tx_attempts = 0;

	//Remember the starting time, used to calculate the actual timestamps of each Tx below
	last_tx_timestamp = (u64)(mpdu_info->delay_accept) + (u64)(mpdu_info->timestamp_create);

	//Compare the length of this frame to the RTS Threshold
	if(mpdu_length <= gl_dot11RTSThreshold) {
		tx_mode = TX_MODE_SHORT;
	} else {
		tx_mode = TX_MODE_LONG;
	}


	while(1) { //This is the retry loop
		(mpdu_info->num_tx_attempts)++;

		//Check if the higher-layer MAC requires this transmission have a pre-Tx backoff or post-Tx timeout
		req_timeout = ((mpdu_info->flags) & TX_MPDU_FLAGS_REQ_TO) != 0;
		req_backoff = ((mpdu_info->flags) & TX_MPDU_FLAGS_REQ_BO) != 0;

		//Check whether this transmission can be canceled - used by IBSS nodes competing with peers to send beacons
		gl_autocancel_en = ((mpdu_info->flags) & TX_MPDU_FLAGS_AUTOCANCEL) != 0;
		if(gl_autocancel_en) {
			//Define the conditions to apply to receptions that would trigger cancellation of this transmission
			gl_autocancel_match_type = header->frame_control_1;
			memcpy((void*)gl_autocancel_match_addr3, header->address_3, 6);
			autocancel_curr_timestamp = get_usec_timestamp();
			if(autocancel_curr_timestamp >= gl_autocancel_last_rx_ts){
				autocancel_timestamp_diff = autocancel_curr_timestamp - gl_autocancel_last_rx_ts;
			} else {
				autocancel_timestamp_diff = gl_autocancel_last_rx_ts - autocancel_curr_timestamp;
			}
			if(autocancel_timestamp_diff < 50000){
				//TODO: this is currently hardcoded to 50ms. In the future, it should be a parameter that passes down from CPU_HIGH
				//Conceptually, this value should be just less than a beacon interval. Any beacon transmission will be canceled if it
				//happens in this interval after the previous beacon reception.
				gl_autocancel_en = 0;
				return -1;
			}
		}

		//Write the SIGNAL field (interpreted by the PHY during Tx waveform generation)
		//This is the SIGNAL field for the MPDU we will eventually transmit. It's possible
		//the next waveform we send will be an RTS with its own independent SIGNAL
		wlan_phy_set_tx_signal(mpdu_pkt_buf, mpdu_rate, mpdu_length);

		if( (tx_mode == TX_MODE_LONG) && (req_timeout == 1) ) {
			//This is a long MPDU that requires an RTS/CTS handshake prior to the MPDU transmission.
			tx_wait_state = TX_WAIT_CTS;
			gl_mpdu_pkt_buf = mpdu_pkt_buf; //This is a global pkt_buf index that can be seen by the frame_receive() context.
									//frame_receive() needs this to figure out what to send in the event that it receives
									//a valid CTS.
			mac_cfg_pkt_buf = TX_PKT_BUF_RTS;

			// The rate given to us in the argument of frame_transmit applies to the MPDU. Several
			// elements depend on this rate:
			//
			// 1) The rate of the RTS we will send
			// 2) The rate of the CTS we expect to receive
			// 3) The duration of the RTS/CTS/DATA frames a long with the IFS periods between them
			//
			// The below switch() sets these elements accordingly.
			switch( mpdu_rate ) {
				default:
				case WLAN_PHY_RATE_BPSK12:
					mac_cfg_rate = WLAN_PHY_RATE_BPSK12;
					cts_header_duration = TX_TIME_CTS_R6;
					MPDU_N_DBPS = N_DBPS_R6;
					low_tx_details[(mpdu_info->num_tx_attempts)-1].ctrl_phy_params.rate = WLAN_MAC_MCS_6M;
				break;
				case WLAN_PHY_RATE_BPSK34:
					mac_cfg_rate = WLAN_PHY_RATE_BPSK12;
					cts_header_duration = TX_TIME_CTS_R6;
					MPDU_N_DBPS = N_DBPS_R9;
					low_tx_details[(mpdu_info->num_tx_attempts)-1].ctrl_phy_params.rate = WLAN_MAC_MCS_6M;
				break;
				case WLAN_PHY_RATE_QPSK12:
					mac_cfg_rate = WLAN_PHY_RATE_QPSK12;
					cts_header_duration = TX_TIME_CTS_R12;
					MPDU_N_DBPS = N_DBPS_R12;
					low_tx_details[(mpdu_info->num_tx_attempts)-1].ctrl_phy_params.rate = WLAN_MAC_MCS_12M;
				break;
				case WLAN_PHY_RATE_QPSK34:
					mac_cfg_rate = WLAN_PHY_RATE_QPSK12;
					cts_header_duration = TX_TIME_CTS_R12;
					MPDU_N_DBPS = N_DBPS_R18;
					low_tx_details[(mpdu_info->num_tx_attempts)-1].ctrl_phy_params.rate = WLAN_MAC_MCS_12M;
				break;
				case WLAN_PHY_RATE_16QAM12:
					mac_cfg_rate = WLAN_PHY_RATE_16QAM12;
					cts_header_duration = TX_TIME_CTS_R24;
					MPDU_N_DBPS = N_DBPS_R24;
					low_tx_details[(mpdu_info->num_tx_attempts)-1].ctrl_phy_params.rate = WLAN_MAC_MCS_24M;
				break;
				case WLAN_PHY_RATE_16QAM34:
					mac_cfg_rate = WLAN_PHY_RATE_16QAM12;
					cts_header_duration = TX_TIME_CTS_R24;
					MPDU_N_DBPS = N_DBPS_R36;
					low_tx_details[(mpdu_info->num_tx_attempts)-1].ctrl_phy_params.rate = WLAN_MAC_MCS_24M;
				break;
				case WLAN_PHY_RATE_64QAM23:
					mac_cfg_rate = WLAN_PHY_RATE_16QAM12;
					cts_header_duration = TX_TIME_CTS_R24;
					MPDU_N_DBPS = N_DBPS_R48;
					low_tx_details[(mpdu_info->num_tx_attempts)-1].ctrl_phy_params.rate = WLAN_MAC_MCS_24M;
				break;
				case WLAN_PHY_RATE_64QAM34:
					mac_cfg_rate = WLAN_PHY_RATE_16QAM12;
					cts_header_duration = TX_TIME_CTS_R24;
					MPDU_N_DBPS = N_DBPS_R54;
					low_tx_details[(mpdu_info->num_tx_attempts)-1].ctrl_phy_params.rate = WLAN_MAC_MCS_24M;
				break;
			}

			rts_header_duration = (T_SIFS) +
								  cts_header_duration +
	   	   	   	   	   	   	   	  (T_SIFS) +
	   	   	   	   	   	   	   	  wlan_ofdm_txtime(mpdu_length, MPDU_N_DBPS) +
	   	   	   	   	   	   	   	  header->duration_id;


			//We let "duration" be equal to the duration field of an RTS. This value is provided explicitly to CPU_HIGH
			//in the low_tx_details struct such that CPU_HIGH has can reconstruct the RTS in its log. This isn't critical
			//to the operation of the DCF, but is critical for the logging framework.
			low_tx_details[(mpdu_info->num_tx_attempts)-1].duration = rts_header_duration;


			//Construct the RTS frame in the dedicated Tx pkt buf for control frames
			mac_cfg_length = wlan_create_rts_frame((void*)(TX_PKT_BUF_TO_ADDR(TX_PKT_BUF_RTS) + PHY_TX_PKT_BUF_MPDU_OFFSET),
											   header->address_1,
											   header->address_2,
											   rts_header_duration);



			wlan_phy_set_tx_signal(mac_cfg_pkt_buf, mac_cfg_rate, mac_cfg_length); // Write SIGNAL for RTS




		} else if( (tx_mode == TX_MODE_SHORT) && (req_timeout == 1) ) {
			//Unicast, no RTS
			tx_wait_state = TX_WAIT_ACK;
			mac_cfg_rate = mpdu_rate;
			mac_cfg_length = mpdu_length;
			mac_cfg_pkt_buf = mpdu_pkt_buf;
		} else {
			//Multicast, short or long
			tx_wait_state = TX_WAIT_NONE;
			mac_cfg_rate = mpdu_rate;
			mac_cfg_length = mpdu_length;
			mac_cfg_pkt_buf = mpdu_pkt_buf;
		}


		//Configure the Tx antenna selection
		unsigned char mpdu_tx_ant_mask = 0;
		switch(mpdu_info->params.phy.antenna_mode) {
			case TX_ANTMODE_SISO_ANTA:
				mpdu_tx_ant_mask |= 0x1;
			break;
			case TX_ANTMODE_SISO_ANTB:
				mpdu_tx_ant_mask |= 0x2;
			break;
			case TX_ANTMODE_SISO_ANTC:
				mpdu_tx_ant_mask |= 0x4;
			break;
			case TX_ANTMODE_SISO_ANTD:
				mpdu_tx_ant_mask |= 0x8;
			break;
			default:
				mpdu_tx_ant_mask = 0x1;
			break;
		}

		//Configure the Tx power - update all antennas, even though only one will be used
		curr_tx_pow = wlan_mac_low_dbm_to_gain_target(mpdu_info->params.phy.power);
		wlan_mac_tx_ctrl_A_gains(curr_tx_pow, curr_tx_pow, curr_tx_pow, curr_tx_pow);

		if( (mpdu_info->num_tx_attempts) == 1 ) {
			//This is the first transmission, so we speculatively draw a backoff in case
			//the backoff counter is currently 0 but the medium is busy. Prior to all other
			//(re)transmissions, an explicit backoff will have been started at the end of
			//the previous iteration of this loop.
			if (req_backoff == 0) {
				//Normal packets don't require pre-Tx backoff; the pre-Tx backoff will only occur
				// if the medium is busy at Tx time
				n_slots = rand_num_slots(RAND_SLOT_REASON_STANDARD_ACCESS);

			} else {
				//IBSS beacon transmissions always require a pre-Tx backoff to dither Tx attempts
				// by multiple IBSS peers
				n_slots = rand_num_slots(RAND_SLOT_REASON_IBSS_BEACON);

				//Force-reset the DCF core, to clear any previously-running backoffs
				wlan_mac_set_backoff_reset(1);
				wlan_mac_set_backoff_reset(0);

				//Start the backoff
				wlan_mac_dcf_hw_start_backoff(n_slots);
			}

			//Configure the DCF core Tx state machine for this transmission
			//wlan_mac_tx_ctrl_A_params(pktBuf, antMask, preTx_backoff_slots, preWait_postRxTimer1, preWait_postTxTimer1, postWait_postTxTimer2)
			wlan_mac_tx_ctrl_A_params(mac_cfg_pkt_buf, mpdu_tx_ant_mask, n_slots, 0, 0, req_timeout);
		} else {
			//This is a retry. We will inherit whatever backoff that is currently running.
			//Configure the DCF core Tx state machine for this transmission
			// preTx_backoff_slots is 0 here, since the core will have started a post-timeout backoff automatically
			//wlan_mac_MPDU_tx_params(tx_pkt_buf, 0, req_timeout, mpdu_tx_ant_mask);
			wlan_mac_tx_ctrl_A_params(mac_cfg_pkt_buf, mpdu_tx_ant_mask, 0, 0, 0, req_timeout);
		}
		
		//Wait for the Tx PHY to be idle
		//Actually waiting here is rare, but handles corner cases like a background ACK transmission at a low rate
		// overlapping the attempt to start a new packet transmission
		do{
			mac_hw_status = wlan_mac_get_status();
		} while(mac_hw_status & WLAN_MAC_STATUS_MASK_TX_PHY_ACTIVE);

		//Submit the MPDU for transmission - this starts the MAC hardware's MPDU Tx state machine
		wlan_mac_tx_ctrl_A_start(1);
		wlan_mac_tx_ctrl_A_start(0);

		//While waiting, fill in the metadata about this transmission attempt, to be used by CPU High in creating TX_LOW log entries
		//The phy_params (as opposed to phy_params2) element is used for the MPDU itself. If we are waiting for a CTS and we do not
		//receive one, CPU_HIGH will know to ignore this element of low_tx_details (since the MPDU will not be transmitted).
		low_tx_details[(mpdu_info->num_tx_attempts)-1].mpdu_phy_params.rate = mpdu_info->params.phy.rate;
		low_tx_details[(mpdu_info->num_tx_attempts)-1].mpdu_phy_params.power = mpdu_info->params.phy.power;
		low_tx_details[(mpdu_info->num_tx_attempts)-1].mpdu_phy_params.antenna_mode = mpdu_info->params.phy.antenna_mode;
		low_tx_details[(mpdu_info->num_tx_attempts)-1].chan_num = wlan_mac_low_get_active_channel();

		//If RTS/CTS isn't used, these fields should just be ignored
		low_tx_details[(mpdu_info->num_tx_attempts)-1].ctrl_phy_params.power = mpdu_info->params.phy.power;
		low_tx_details[(mpdu_info->num_tx_attempts)-1].ctrl_phy_params.antenna_mode = mpdu_info->params.phy.antenna_mode;


		low_tx_details[(mpdu_info->num_tx_attempts)-1].cw = (1 << gl_cw_exp)-1; //(2^(gl_cw_exp) - 1)
		low_tx_details[(mpdu_info->num_tx_attempts)-1].ssrc = gl_stationShortRetryCount;
		low_tx_details[(mpdu_info->num_tx_attempts)-1].slrc = gl_stationLongRetryCount;
		low_tx_details[(mpdu_info->num_tx_attempts)-1].src = mpdu_info->short_retry_count;
		low_tx_details[(mpdu_info->num_tx_attempts)-1].lrc = mpdu_info->long_retry_count;

		//NOTE: the pre-Tx backoff may not occur for the initial transmission attempt. If the medium has been idle for >DIFS when
		// the first Tx occurs the DCF state machine will not start a backoff. The upper-level MAC should compare the num_slots value
		// to the time delta between the accept and start times of the first transmission to determine whether the pre-Tx backoff
		// actually occurred.
		low_tx_details[(mpdu_info->num_tx_attempts)-1].num_slots = n_slots;

		//Wait for the MPDU Tx to finish
		do { //while(tx_status & WLAN_MAC_STATUS_MASK_TX_A_PENDING)

			//Poll the DCF core status register
			mac_hw_status = wlan_mac_get_status();

			if( mac_hw_status & WLAN_MAC_STATUS_MASK_TX_A_DONE ) {
				//Transmission is complete


				if(tx_wait_state == TX_WAIT_CTS) {
					low_tx_details[(mpdu_info->num_tx_attempts)-1].tx_details_type = TX_DETAILS_RTS_ONLY; //This will potentially be overwritten with TX_DETAILS_RTS_MPDU
																									   //should we make it that far.
					low_tx_details[(mpdu_info->num_tx_attempts)-1].tx_start_delta = (u32)(get_tx_start_timestamp() - last_tx_timestamp);
					last_tx_timestamp = get_tx_start_timestamp();
				} else if( (tx_mode == TX_MODE_LONG) && (tx_wait_state == TX_WAIT_ACK) ) {
					//Note: this clause will overwrite the previous TX_DETAILS_RTS_ONLY state in the event
					//a CTS is received.
					low_tx_details[(mpdu_info->num_tx_attempts)-1].tx_details_type = TX_DETAILS_RTS_MPDU;
					//Second note: we won't update the tx_start_delta field in this case. We already wrote it
					//in the RTS_ONLY state. We'll let CPU_HIGH figure out the tx_start timestamp of this MPDU
					//based on the start time of the RTS and everything else it knows about the MPDU.

					low_tx_details[(mpdu_info->num_tx_attempts)-1].timestamp_offset = (u32)(get_tx_start_timestamp() - last_tx_timestamp);

				} else {
					//This is a non-RTS/CTS-protected MPDU transmission
					low_tx_details[(mpdu_info->num_tx_attempts)-1].tx_details_type = TX_DETAILS_MPDU;
					low_tx_details[(mpdu_info->num_tx_attempts)-1].tx_start_delta = (u32)(get_tx_start_timestamp() - last_tx_timestamp);
					last_tx_timestamp = get_tx_start_timestamp();
				}

				//Switch on the result of the transmission attempt
				switch( mac_hw_status & WLAN_MAC_STATUS_MASK_TX_A_RESULT ) {

					case WLAN_MAC_STATUS_TX_A_RESULT_NONE:
						//Transmission was immediately successful - this implies no post-Tx timeout was required,
						// so the core didn't wait for any post-Tx receptions (i.e. multicast/broadcast transmission)

						switch(tx_mode) {
							case TX_MODE_SHORT:
								reset_ssrc();
								reset_cw();
							break;
							case TX_MODE_LONG:
								reset_slrc();
								reset_cw();
							break;
						}

						//Start a post-Tx backoff using the updated contention window
						n_slots = rand_num_slots(RAND_SLOT_REASON_STANDARD_ACCESS);
						wlan_mac_dcf_hw_start_backoff(n_slots);

						//Disable any auto-cancellation of transmissions (to be re-enabled by future transmissions if needed)
						gl_autocancel_en = 0;

						return 0;
					break;

					case WLAN_MAC_STATUS_TX_A_RESULT_RX_STARTED:
						//Transmission ended, followed by a new reception (hopefully a CTS or ACK)

						//Handle the new reception

						rx_status = wlan_mac_low_poll_frame_rx();

						gl_mpdu_pkt_buf = PKT_BUF_INVALID;

						//Check if the reception is an ACK addressed to this node, received with a valid checksum
						if((tx_wait_state == TX_WAIT_CTS) &&
								  (rx_status & POLL_MAC_STATUS_RECEIVED_PKT) &&
								  (rx_status & POLL_MAC_TYPE_CTS) &&
								  (rx_status & POLL_MAC_STATUS_GOOD) &&
								  (rx_status & POLL_MAC_ADDR_MATCH)) {

							tx_wait_state = TX_WAIT_ACK;

							//We received the CTS, so we can reset our SSRC
							//Note: as per 9.3.3 of 802.11-2012, we do not reset our CW
							reset_ssrc();

							//At this point, the MAC tx state machine has started anew to send a the MPDU itself.
							//This was triggered by the frame_receive() context.
							mac_hw_status |= WLAN_MAC_STATUS_MASK_TX_A_PENDING; //We know that the frame_receive context
																				//has started the transmission of the MPDU.
																				//This ensures we are not kicked out of the
																				//do-while loop.
							//Note: the above assignment is better than re-reading wlan_mac_get_status() in the case of a short
							//MPDU, where we may skip the PENDING state directly to DONE without this code context seeing it.
							continue;

						} else if( (tx_wait_state == TX_WAIT_ACK) &&
								(rx_status & POLL_MAC_STATUS_RECEIVED_PKT) &&
								(rx_status & POLL_MAC_TYPE_ACK) &&
								(rx_status & POLL_MAC_STATUS_GOOD) &&
								(rx_status & POLL_MAC_ADDR_MATCH)) {
								//Update contention window
								switch(tx_mode) {
									case TX_MODE_SHORT:
										reset_ssrc();
										reset_cw();
									break;
									case TX_MODE_LONG:
										reset_slrc();
										reset_cw();
									break;
								}
								//Start a post-Tx backoff using the updated contention window
								n_slots = rand_num_slots(RAND_SLOT_REASON_STANDARD_ACCESS);
								wlan_mac_dcf_hw_start_backoff(n_slots);

								//Disable any auto-cancellation of transmissions (to be re-enabled by future transmissions if needed)
								gl_autocancel_en = 0;

								return TX_MPDU_RESULT_SUCCESS;

						} else {
							//Received a packet immediately after transmitting, but it wasn't the ACK we wanted
							// It could have been our ACK with a bad checksum or a different packet altogether
							switch(tx_wait_state) {
								case TX_WAIT_ACK:
									//We were waiting for an ACK
									//Depending on the size of the MPDU, we will increment
									//either the SRC or the LRC

									header->frame_control_2 = (header->frame_control_2) | MAC_FRAME_CTRL2_FLAG_RETRY;

									switch(tx_mode) {
										case TX_MODE_SHORT:
											increment_src_ssrc(&(mpdu_info->short_retry_count));
										break;
										case TX_MODE_LONG:
											increment_lrc_slrc(&(mpdu_info->long_retry_count));
										break;
									}
								break;
								case TX_WAIT_CTS:
									//We were waiting for a CTS but did not get it.
									//Increment the SRC
									increment_src_ssrc(&(mpdu_info->short_retry_count));
								break;
								case TX_WAIT_NONE:
									xil_printf("Error: unexpected state");
								break;
							}

							//Start the post-Tx backoff
							n_slots = rand_num_slots(RAND_SLOT_REASON_STANDARD_ACCESS);
							wlan_mac_dcf_hw_start_backoff(n_slots);

							//Now we evaluate the SRC and LRC to see if either has reached its maximum
							// Use >= here to handle unlikely case of retryLimit values changing mid-Tx
							if( (mpdu_info->short_retry_count >=  gl_dot11ShortRetryLimit) || (mpdu_info->long_retry_count >=  gl_dot11LongRetryLimit) ){
								//We are done transmitting. We now break out of the retry while loop
								gl_autocancel_en = 0;
								return TX_MPDU_RESULT_FAILURE;
							}

							//Jump to next loop iteration
							continue;
						}
					break;
					case WLAN_MAC_STATUS_TX_A_RESULT_TIMEOUT:

						gl_mpdu_pkt_buf = PKT_BUF_INVALID;
						//Tx required timeout, timeout expired with no receptions

						switch(tx_wait_state){
							case TX_WAIT_ACK:
								//We were waiting for an ACK
								//Depending on the size of the MPDU, we will increment
								//either the SRC or the LRC

								header->frame_control_2 = (header->frame_control_2) | MAC_FRAME_CTRL2_FLAG_RETRY;

								switch(tx_mode){
									case TX_MODE_SHORT:
										increment_src_ssrc(&(mpdu_info->short_retry_count));
									break;
									case TX_MODE_LONG:
										increment_lrc_slrc(&(mpdu_info->long_retry_count));
									break;
								}
							break;
							case TX_WAIT_CTS:
								//We were waiting for a CTS but did not get it.
								//Increment the SRC
								increment_src_ssrc(&(mpdu_info->short_retry_count));
							break;
							case TX_WAIT_NONE:
								xil_printf("Error: unexpected state");
							break;
						}

						//Start the post-Tx backoff
						n_slots = rand_num_slots(RAND_SLOT_REASON_STANDARD_ACCESS);
						wlan_mac_dcf_hw_start_backoff(n_slots);

						//Now we evaluate the SRC and LRC to see if either has reached its maximum
						if( (mpdu_info->short_retry_count ==  gl_dot11ShortRetryLimit) || (mpdu_info->long_retry_count ==  gl_dot11LongRetryLimit) ){
							//We are done transmitting. We now break out of the retry while loop
							gl_autocancel_en = 0;
							return TX_MPDU_RESULT_FAILURE;
						}
						//Jump to next loop iteration
						continue;
					break;
				}
			} else { //else for if(mac_hw_status & WLAN_MAC_STATUS_MASK_TX_A_DONE)
				//Poll the MAC Rx state to check if a packet was received while our Tx was deferring

				if( mac_hw_status & (WLAN_MAC_STATUS_MASK_RX_PHY_ACTIVE | WLAN_MAC_STATUS_MASK_RX_PHY_BLOCKED_FCS_GOOD | WLAN_MAC_STATUS_MASK_RX_PHY_BLOCKED) ) {
					rx_status = wlan_mac_low_poll_frame_rx();

					//Check if the new reception met the conditions to cancel the already-submitted transmission
					if((gl_autocancel_en == 1) && ((rx_status & POLL_MAC_CANCEL_TX) != 0)) {
						//The Rx handler killed this transmission already by resetting the MAC core
						// Reset the global gl_autocancel_en variable and return failure
						gl_autocancel_en = 0;
						return TX_MPDU_RESULT_FAILURE;
					}
				}
			}//END if(Tx A state machine done)
		} while( mac_hw_status & WLAN_MAC_STATUS_MASK_TX_A_PENDING );
	} //end retransmission loop

	return 0;
}

inline void increment_src_ssrc(u8* src_ptr){

	//Increment the Short Retry Count
	(*src_ptr)++;

	//Increment the Station Short Retry Count
	//9.3.3 in 802.11-2012
	gl_stationShortRetryCount = sat_add32(gl_stationShortRetryCount, 1);

	if(gl_stationShortRetryCount == gl_dot11ShortRetryLimit){
		reset_cw();
	} else {
		gl_cw_exp = min(gl_cw_exp+1, wlan_mac_low_get_cw_exp_max());
	}

	return;
}

inline void increment_lrc_slrc(u8* lrc_ptr){
	//Increment the Long Retry Count
	(*lrc_ptr)++;

	//Increment the Station Long Retry Count
	//9.3.3 in 802.11-2012
	gl_stationLongRetryCount = sat_add32(gl_stationLongRetryCount, 1);

	if(gl_stationLongRetryCount == gl_dot11LongRetryLimit){
		reset_cw();
	} else {
		gl_cw_exp = min(gl_cw_exp+1, wlan_mac_low_get_cw_exp_max());
	}

	return;
}

inline void reset_ssrc(){
	//Note: Resetting the SSRC does not necessarily
	//indicate that the contention window should be reset.
	//e.g., the reception of a valid CTS.
	gl_stationShortRetryCount = 0;
}

inline void reset_slrc(){
	gl_stationLongRetryCount = 0;
}

inline void reset_cw(){
	gl_cw_exp = wlan_mac_low_get_cw_exp_min();
	return;
}

#if 0
/**
 * @brief Updates the MAC's contention window
 *
 * This function is called by the Tx state machine to update the contention window, typically after each transmission attempt.
 * The contention window and one of the station retry counters (sort or long) are updated per call.
 *
 * Two station retry counters are maintained- long and short.
 *
 * The short station retry counter increments on every transmission failure. The counter is reset on any successful transmission.
 *
 * The contention window is reset to CW_min when either:
 *  a) A packet is transmitted successfully
 *  b) A station retry counter reaches its limit
 *
 * Notice that in the case of multiple consecutive failed transmissions the CW will reset after the first packet reaches its retry limit
 *  but not when subsequent packets reach their retry limits. This is the behavior intended by the standard, to avoid excessive medium usage
 *  by a node who is consistently unable to transmit successfully. For more details see:
 *   -IEEE 802.11-2012 9.3.3
 *   -IEEE doc 802.11-03/752r0
 *
 * @param u8 pkt_buf
 *  -Index of the Tx packet buffer containing the packet who's transmission attempt caused this CW update
 * @param u8 reason
 *  -Reason code for this CW update (Tx success, Tx failure, etc)
 */

inline void update_cw(u8 reason, u8 pkt_buf) {
	volatile u32* station_rc_ptr;
	u8 retry_limit;
	tx_frame_info* tx_mpdu = (tx_frame_info*)TX_PKT_BUF_TO_ADDR(pkt_buf);

	mac_header_80211* tx_80211_header;

	tx_80211_header = (mac_header_80211*)((void*)(TX_PKT_BUF_TO_ADDR(pkt_buf)+PHY_TX_PKT_BUF_MPDU_OFFSET));

	//Decide which station retry counter to operate on
	if(tx_mpdu->length > gl_dot11RTSThreshold){
		station_rc_ptr = (u32*)&gl_stationLongRetryCount;
	} else {
		station_rc_ptr = (u32*)&gl_stationShortRetryCount;
	}

	//Pull the retry limit for the current packet from its metadata
	retry_limit = tx_mpdu->params.mac.num_tx_max;

	switch(reason) {
		case DCF_CW_UPDATE_MPDU_TX_ERR:

			//Transmission error - update the station retry counter
			(*station_rc_ptr)++;

			//Reest the CW if the station retry counter is eactly the retry limit
			if(*station_rc_ptr == retry_limit) {
				gl_cw_exp = wlan_mac_low_get_cw_exp_min();
			} else {
				gl_cw_exp = min(gl_cw_exp+1, wlan_mac_low_get_cw_exp_max());
			}

			//Raise retry flag in the MAC header
			tx_80211_header->frame_control_2 = (tx_80211_header->frame_control_2) | MAC_FRAME_CTRL2_FLAG_RETRY;
		break;

		case DCF_CW_UPDATE_BCAST_TX:
		case DCF_CW_UPDATE_MPDU_RX_ACK:
			//Transmission success

			//Reset station retry counter and contention window
			(*station_rc_ptr) = 0;
			gl_cw_exp = wlan_mac_low_get_cw_exp_min();
		break;
	}

	return;
}
#endif

/**
 * @brief Generate a random number in the range set by the current contention window
 *
 * When reason is RAND_SLOT_REASON_IBSS_BEACON the random draw is taken from the range
 * [0, 2*CWmin], used for pre-beacon backoffs in IBSS (per 802.11-2012 10.1.3.3)
 *
 * @param u8 reason
 *  -Code for the random draw; must be RAND_SLOT_REASON_STANDARD_ACCESS or RAND_SLOT_REASON_IBSS_BEACON
 * @return
 *  -Random integer
 */
inline unsigned int rand_num_slots(u8 reason){
//Generates a uniform random value between [0, (2^(gl_cw_exp) - 1)], where gl_cw_exp is a positive integer
//This function assumed RAND_MAX = 2^31.
// |	gl_cw_exp	|	CW			|
// |	4		|	[0, 15]		|
// |	5       |	[0, 31]		|
// |	6		|	[0, 63]		|
// |	7		|	[0, 123]	|
// |	8		|	[0, 255]	|
// |	9		|	[0, 511]	|
// |	10		|	[0, 1023]	|
	volatile u32 n_slots;

	switch(reason) {
		case RAND_SLOT_REASON_STANDARD_ACCESS:
			n_slots = ((unsigned int)rand() >> (32-(gl_cw_exp+1)));
		break;

		case RAND_SLOT_REASON_IBSS_BEACON:
			//Section 10.1.3.3 of 802.11-2012: Backoffs prior to IBSS beacons are drawn from [0, 2*CWmin]
			n_slots = ((unsigned int)rand() >> (32-(wlan_mac_low_get_cw_exp_min()+1+1)));
		break;
	}

	return n_slots;
}

/**
 * @brief Start a backoff
 *
 * This function might do nothing if a backoff is already running. The backoff-start attempt will be safely ignored
 * in this case.
 *
 * @param u16 num_slots
 *  -Duration of backoff interval, in units of slots
 */
void wlan_mac_dcf_hw_start_backoff(u16 num_slots) {
	//WLAN_MAC_REG_SW_BACKOFF_CTRL:
	// b[15:0]: Num slots
	// b[31]: Start backoff

	//Write num_slots and toggle start
	Xil_Out32(WLAN_MAC_REG_SW_BACKOFF_CTRL, (num_slots & 0xFFFF) | 0x80000000);
	Xil_Out32(WLAN_MAC_REG_SW_BACKOFF_CTRL, (num_slots & 0xFFFF));

	return;
}

/**
 * @brief Construct an ACK frame
 *
 * @param void* pkt_buf_addr
 *  -Address of Tx packet buffer where to construct new ACK packet
 * @param u8* address_ra
 *  -Pointer to 6-byte MAC address of receiving node
 */
int wlan_create_ack_frame(void* pkt_buf_addr, u8* address_ra) {

	mac_header_80211_ACK* ack_header;
	ack_header = (mac_header_80211_ACK*)(pkt_buf_addr);

	ack_header->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_ACK;
	ack_header->frame_control_2 = 0;
	ack_header->duration_id = 0;
	memcpy(ack_header->address_ra, address_ra, 6);

	//Include FCS in packet size (MAC accounts for FCS, even though the PHY calculates it)
	return (sizeof(mac_header_80211_ACK)+WLAN_PHY_FCS_NBYTES);
}

int wlan_create_cts_frame(void* pkt_buf_addr, u8* address_ra, u16 duration) {

	mac_header_80211_CTS* cts_header;
	cts_header = (mac_header_80211_CTS*)(pkt_buf_addr);

	cts_header->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_CTS;
	cts_header->frame_control_2 = 0;
	cts_header->duration_id = duration;
	memcpy(cts_header->address_ra, address_ra, 6);

	//Include FCS in packet size (MAC accounts for FCS, even though the PHY calculates it)
	return (sizeof(mac_header_80211_CTS)+WLAN_PHY_FCS_NBYTES);
}

int wlan_create_rts_frame(void* pkt_buf_addr, u8* address_ra, u8* address_ta, u16 duration) {

	mac_header_80211_RTS* rts_header;
	rts_header = (mac_header_80211_RTS*)(pkt_buf_addr);

	rts_header->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_RTS;
	rts_header->frame_control_2 = 0;
	rts_header->duration_id = duration;
	memcpy(rts_header->address_ra, address_ra, 6);
	memcpy(rts_header->address_ta, address_ta, 6);

	//Include FCS in packet size (MAC accounts for FCS, even though the PHY calculates it)
	return (sizeof(mac_header_80211_RTS)+WLAN_PHY_FCS_NBYTES);
}

int wlan_dcf_process_low_param(u8 mode, u32* payload){
	switch(mode){
		default:
		case IPC_REG_READ_MODE:
			//Not currently implemented in wlan_mac_low.c
		break;
		case IPC_REG_WRITE_MODE:
			switch(payload[0]){
				default:
					xil_printf("Unknown param 0x%08x\n", payload[0]);
				break;
				case LOW_PARAM_DCF_RTS_THRESH:
					gl_dot11RTSThreshold = payload[1];
				break;
				case LOW_PARAM_DCF_DOT11SHORTRETRY:
					gl_dot11ShortRetryLimit = payload[1];
				break;
				case LOW_PARAM_DCF_DOT11LONGRETRY:
					gl_dot11LongRetryLimit = payload[1];
				break;
			}

		break;
	}
	return 0;
}

