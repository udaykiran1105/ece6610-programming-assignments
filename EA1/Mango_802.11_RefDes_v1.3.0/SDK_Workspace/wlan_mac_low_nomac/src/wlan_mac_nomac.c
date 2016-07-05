/** @file wlan_mac_nomac.c
 *  @brief Simple MAC that does nothing but transmit and receive
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
#include "wlan_mac_nomac.h"

#include "wlan_exp.h"
#include "math.h"


/*************************** Constant Definitions ****************************/

#define WARPNET_TYPE_80211_LOW         WARPNET_TYPE_80211_LOW_NOMAC
#define NUM_LEDS                       4

/*********************** Global Variable Definitions *************************/


/*************************** Variable Definitions ****************************/
static u8                              eeprom_addr[6];

volatile u8                            red_led_index;
volatile u8                            green_led_index;

/******************************** Functions **********************************/

int main(){

	wlan_mac_hw_info* hw_info;
	xil_printf("\f");
	xil_printf("----- Mango 802.11 Reference Design -----\n");
	xil_printf("----- v1.3 ------------------------------\n");
	xil_printf("----- wlan_mac_nomac --------------------\n");
	xil_printf("Compiled %s %s\n\n", __DATE__, __TIME__);

	xil_printf("Note: this UART is currently printing from CPU_LOW. To view prints from\n");
	xil_printf("and interact with CPU_HIGH, raise the right-most User I/O DIP switch bit.\n");
	xil_printf("This switch can be toggled live while the design is running.\n\n");

	wlan_tx_config_ant_mode(TX_ANTMODE_SISO_ANTA);

	red_led_index = 0;
	green_led_index = 0;
	userio_write_leds_green(USERIO_BASEADDR, (1<<green_led_index));
	userio_write_leds_red(USERIO_BASEADDR, (1<<red_led_index));

	wlan_mac_low_init(WARPNET_TYPE_80211_LOW);

	hw_info = wlan_mac_low_get_hw_info();
	memcpy(eeprom_addr,hw_info->hw_addr_wlan,6);


	wlan_mac_low_set_frame_rx_callback((void*)frame_receive);
	wlan_mac_low_set_frame_tx_callback((void*)frame_transmit);

	wlan_mac_low_finish_init();

	REG_SET_BITS(WLAN_MAC_REG_CONTROL, (WLAN_MAC_CTRL_MASK_CCA_IGNORE_PHY_CS | WLAN_MAC_CTRL_MASK_CCA_IGNORE_NAV));

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
 * unknown. In NOMAC, this function doesn't need to do any kind of filtering or operations like transmitting
 * an acknowledgment.
 *
 * @param u8 rx_pkt_buf
 *  -Index of the Rx packet buffer containing the newly recevied packet
 * @param u8 rate
 *  -Index of PHY rate at which pcaket was received
 * @param u16 length
 *  -Number of bytes received by the PHY, including MAC header and FCS
 * @return
 *  - always returns 0 in NOMAC implementation
 */
u32 frame_receive(u8 rx_pkt_buf, phy_rx_details* phy_details){
	//This function is called after a good SIGNAL field is detected by either PHY (OFDM or DSSS)
	//It is the responsibility of this function to wait until a sufficient number of bytes have been received
	// before it can start to process those bytes. When this function is called the eventual checksum status is
	// unknown. The packet contents can be provisionally processed (e.g. prepare an ACK for fast transmission),
	// but post-reception actions must be conditioned on the eventual FCS status (good or bad).
	//
	// Note: The timing of this function is critical for correct operation of the 802.11 DCF. It is not
	// safe to add large delays to this function (e.g. xil_printf or usleep)
	//
	//Two primary job responsibilities of this function:
	// (1): Prepare outgoing ACK packets and instruct the MAC_DCF_HW core whether or not to send ACKs
	// (2): Pass up MPDUs (FCS valid or invalid) to CPU_HIGH

	rx_frame_info* mpdu_info;
	void* pkt_buf_addr = (void *)RX_PKT_BUF_TO_ADDR(rx_pkt_buf);

	mpdu_info = (rx_frame_info*)pkt_buf_addr;

	mpdu_info->flags = 0;
	mpdu_info->phy_details = *phy_details;
	mpdu_info->channel = wlan_mac_low_get_active_channel();
	mpdu_info->timestamp = get_rx_start_timestamp();
	mpdu_info->state = wlan_mac_dcf_hw_rx_finish(); //Blocks until reception is complete


	mpdu_info->ant_mode = wlan_phy_rx_get_active_rx_ant();

	mpdu_info->rf_gain = wlan_phy_rx_get_agc_RFG(mpdu_info->ant_mode);
	mpdu_info->bb_gain = wlan_phy_rx_get_agc_BBG(mpdu_info->ant_mode);
	mpdu_info->rx_power = wlan_mac_low_calculate_rx_power(wlan_phy_rx_get_pkt_rssi(mpdu_info->ant_mode), wlan_phy_rx_get_agc_RFG(mpdu_info->ant_mode));

	if(mpdu_info->state == RX_MPDU_STATE_FCS_GOOD){
		green_led_index = (green_led_index + 1) % NUM_LEDS;
		userio_write_leds_green(USERIO_BASEADDR, (1<<green_led_index));
	} else {
		red_led_index = (red_led_index + 1) % NUM_LEDS;
		userio_write_leds_red(USERIO_BASEADDR, (1<<red_led_index));
	}

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

	//Unblock the PHY post-Rx (no harm calling this if the PHY isn't actually blocked)
	wlan_mac_dcf_hw_unblock_rx_phy();

	return 0;
}

/**
 * @brief Handles transmission of a wireless packet
 *
 * This function is called to transmit a new packet via the PHY. While the code does utilize the wlan_mac_dcf_hw core,
 * it bypasses any of the DCF-specific state in order to directly transmit the frame. This function should be called once per packet and will return 
 * immediately following that transmission. It will not perform any DCF-like retransmissions.
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
int frame_transmit(u8 pkt_buf, u8 rate, u16 length, wlan_mac_low_tx_details* low_tx_details) {
	//This function manages the MAC_DCF_HW core.

	//return 0; //disable all Tx

	tx_frame_info* mpdu_info = (tx_frame_info*) (TX_PKT_BUF_TO_ADDR(pkt_buf));
	u64 last_tx_timestamp;
	int curr_tx_pow;
	last_tx_timestamp = (u64)(mpdu_info->delay_accept) + (u64)(mpdu_info->timestamp_create);

	u32 mac_hw_status;

	//Write the SIGNAL field (interpreted by the PHY during Tx waveform generation)
	wlan_phy_set_tx_signal(pkt_buf, rate, length);

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

	mpdu_info->num_tx_attempts = 1;

	curr_tx_pow = wlan_mac_low_dbm_to_gain_target(mpdu_info->params.phy.power);

	//wlan_mac_tx_ctrl_A_params(pktBuf, antMask, preTx_backoff_slots, preWait_postRxTimer1, preWait_postTxTimer1, postWait_postTxTimer2)
	wlan_mac_tx_ctrl_A_params(pkt_buf, mpdu_tx_ant_mask, 0, 0, 0, 0);

	//Set Tx Gains
	wlan_mac_tx_ctrl_A_gains(curr_tx_pow, curr_tx_pow, curr_tx_pow, curr_tx_pow);

	//Before we mess with any PHY state, we need to make sure it isn't actively
	//transmitting. For example, it may be sending an ACK when we get to this part of the code
	while(wlan_mac_get_status() & WLAN_MAC_STATUS_MASK_TX_PHY_ACTIVE){}

	//Submit the MPDU for transmission - this starts the MAC hardware's MPDU Tx state machine
	wlan_mac_tx_ctrl_A_start(1);
	wlan_mac_tx_ctrl_A_start(0);

	//Wait for the MPDU Tx to finish
	do{
		if(low_tx_details != NULL){
			low_tx_details[0].mpdu_phy_params.rate = mpdu_info->params.phy.rate;
			low_tx_details[0].mpdu_phy_params.power = mpdu_info->params.phy.power;
			low_tx_details[0].mpdu_phy_params.antenna_mode = mpdu_info->params.phy.antenna_mode;
			low_tx_details[0].chan_num = wlan_mac_low_get_active_channel();
			low_tx_details[0].num_slots = 0;
			low_tx_details[0].cw = 0;
		}
		mac_hw_status = wlan_mac_get_status();

		if( mac_hw_status & WLAN_MAC_STATUS_MASK_TX_A_DONE) {
			if( low_tx_details != NULL ){
				low_tx_details[0].tx_start_delta = (u32)(get_tx_start_timestamp() - last_tx_timestamp);
				last_tx_timestamp = get_tx_start_timestamp();
			}

			switch( mac_hw_status & WLAN_MAC_STATUS_MASK_TX_A_RESULT ){
				case WLAN_MAC_STATUS_TX_A_RESULT_NONE:
					return 0;
				break;
			}
		}
	} while( mac_hw_status & WLAN_MAC_STATUS_MASK_TX_A_PENDING );

	return -1;
}
