/** @file wlan_mac_high.h
 *  @brief Low-level WLAN MAC High Framework
 *
 *  This contains the low-level code for accessing the WLAN MAC Low Framework.
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

#ifndef WLAN_MAC_LOW_H_
#define WLAN_MAC_LOW_H_

#include "wlan_mac_ipc_util.h"

#define USERIO_BASEADDR     XPAR_W3_USERIO_BASEADDR

/*************** WLAN MAC HW ***************/
//Register renames
//RO:
#define WLAN_MAC_REG_STATUS					XPAR_WLAN_MAC_HW_MEMMAP_STATUS
#define WLAN_MAC_REG_TIMESTAMP_MSB			XPAR_WLAN_MAC_HW_MEMMAP_TIMESTAMP_MSB
#define WLAN_MAC_REG_TIMESTAMP_LSB			XPAR_WLAN_MAC_HW_MEMMAP_TIMESTAMP_LSB
#define WLAN_MAC_REG_LATEST_RX_BYTE			XPAR_WLAN_MAC_HW_MEMMAP_LATEST_RX_BYTE
#define WLAN_MAC_REG_PHY_RX_PARAMS			XPAR_WLAN_MAC_HW_MEMMAP_PHY_RX_PARAMS
#define WLAN_MAC_REG_BACKOFF_COUNTER		XPAR_WLAN_MAC_HW_MEMMAP_BACKOFF_COUNTER
#define WLAN_MAC_REG_RX_TIMESTAMP_LSB		XPAR_WLAN_MAC_HW_MEMMAP_RX_START_TIMESTAMP_LSB
#define WLAN_MAC_REG_RX_TIMESTAMP_MSB		XPAR_WLAN_MAC_HW_MEMMAP_RX_START_TIMESTAMP_MSB
#define WLAN_MAC_REG_TX_TIMESTAMP_LSB		XPAR_WLAN_MAC_HW_MEMMAP_TX_START_TIMESTAMP_LSB
#define WLAN_MAC_REG_TX_TIMESTAMP_MSB		XPAR_WLAN_MAC_HW_MEMMAP_TX_START_TIMESTAMP_MSB

//RW:
#define WLAN_MAC_REG_TX_START				XPAR_WLAN_MAC_HW_MEMMAP_TX_START
#define WLAN_MAC_REG_CALIB_TIMES			XPAR_WLAN_MAC_HW_MEMMAP_CALIB_TIMES
#define WLAN_MAC_REG_IFS_1					XPAR_WLAN_MAC_HW_MEMMAP_IFS_INTERVALS1
#define WLAN_MAC_REG_IFS_2					XPAR_WLAN_MAC_HW_MEMMAP_IFS_INTERVALS2
#define WLAN_MAC_REG_CONTROL				XPAR_WLAN_MAC_HW_MEMMAP_CONTROL
#define WLAN_MAC_REG_SW_BACKOFF_CTRL		XPAR_WLAN_MAC_HW_MEMMAP_BACKOFF_CTRL
#define WLAN_MAC_REG_SET_TIMESTAMP_LSB		XPAR_WLAN_MAC_HW_MEMMAP_TIMESTAMP_SET_LSB
#define WLAN_MAC_REG_SET_TIMESTAMP_MSB		XPAR_WLAN_MAC_HW_MEMMAP_TIMESTAMP_SET_MSB
#define WLAN_MAC_REG_SET_TIMESTAMP_OFFSET	XPAR_WLAN_MAC_HW_MEMMAP_TIMESTAMP_INSERT_OFFSET
#define WLAN_MAC_REG_TX_CTRL_A_PARAMS		XPAR_WLAN_MAC_HW_MEMMAP_TX_CTRL_A_PARAMS
#define WLAN_MAC_REG_TX_CTRL_A_GAINS		XPAR_WLAN_MAC_HW_MEMMAP_TX_CTRL_A_GAINS
#define WLAN_MAC_REG_TX_CTRL_B_PARAMS		XPAR_WLAN_MAC_HW_MEMMAP_TX_CTRL_B_PARAMS
#define WLAN_MAC_REG_TX_CTRL_B_GAINS		XPAR_WLAN_MAC_HW_MEMMAP_TX_CTRL_B_GAINS
#define WLAN_MAC_REG_POST_TX_TIMERS			XPAR_WLAN_MAC_HW_MEMMAP_POST_TX_TIMERS
#define WLAN_MAC_REG_POST_RX_TIMERS			XPAR_WLAN_MAC_HW_MEMMAP_POST_RX_TIMERS
#define WLAN_MAC_REG_NAV_CHECK_ADDR_1		XPAR_WLAN_MAC_HW_MEMMAP_NAV_MATCH_ADDR_1
#define WLAN_MAC_REG_NAV_CHECK_ADDR_2		XPAR_WLAN_MAC_HW_MEMMAP_NAV_MATCH_ADDR_2


#define WLAN_MAC_POST_TX_TIMERS_MASK_TIMER1_COUNTTO	0x00007FFF
#define WLAN_MAC_POST_TX_TIMERS_MASK_TIMER1_EN		0x00008000
#define WLAN_MAC_POST_TX_TIMERS_MASK_TIMER2_COUNTTO	0x7FFF0000
#define WLAN_MAC_POST_TX_TIMERS_MASK_TIMER2_EN		0x80000000

#define WLAN_MAC_POST_RX_TIMERS_MASK_TIMER1_COUNTTO	0x00007FFF
#define WLAN_MAC_POST_RX_TIMERS_MASK_TIMER1_EN		0x00008000
#define WLAN_MAC_POST_RX_TIMERS_MASK_TIMER2_COUNTTO	0x7FFF0000
#define WLAN_MAC_POST_RX_TIMERS_MASK_TIMER2_EN		0x80000000

#define wlan_mac_set_postTx_timer1(d)		(Xil_Out32(WLAN_MAC_REG_POST_TX_TIMERS, ( (Xil_In32(WLAN_MAC_REG_POST_TX_TIMERS) & ~WLAN_MAC_POST_TX_TIMERS_MASK_TIMER1_COUNTTO) | ((d)       & WLAN_MAC_POST_TX_TIMERS_MASK_TIMER1_COUNTTO))))
#define wlan_mac_set_postTx_timer2(d)		(Xil_Out32(WLAN_MAC_REG_POST_TX_TIMERS, ( (Xil_In32(WLAN_MAC_REG_POST_TX_TIMERS) & ~WLAN_MAC_POST_TX_TIMERS_MASK_TIMER2_COUNTTO) | (((d)<<16) & WLAN_MAC_POST_TX_TIMERS_MASK_TIMER2_COUNTTO))))
#define wlan_mac_set_postRx_timer1(d)		(Xil_Out32(WLAN_MAC_REG_POST_RX_TIMERS, ( (Xil_In32(WLAN_MAC_REG_POST_RX_TIMERS) & ~WLAN_MAC_POST_RX_TIMERS_MASK_TIMER1_COUNTTO) | ((d)       & WLAN_MAC_POST_RX_TIMERS_MASK_TIMER1_COUNTTO))))
#define wlan_mac_set_postRx_timer2(d)		(Xil_Out32(WLAN_MAC_REG_POST_RX_TIMERS, ( (Xil_In32(WLAN_MAC_REG_POST_RX_TIMERS) & ~WLAN_MAC_POST_RX_TIMERS_MASK_TIMER2_COUNTTO) | (((d)<<16) & WLAN_MAC_POST_RX_TIMERS_MASK_TIMER2_COUNTTO))))

#define wlan_mac_postTx_timer1_en(d)		(Xil_Out32(WLAN_MAC_REG_POST_TX_TIMERS, ( (Xil_In32(WLAN_MAC_REG_POST_TX_TIMERS) & ~WLAN_MAC_POST_TX_TIMERS_MASK_TIMER1_EN) | (d ? WLAN_MAC_POST_TX_TIMERS_MASK_TIMER1_EN : 0))))
#define wlan_mac_postTx_timer2_en(d)		(Xil_Out32(WLAN_MAC_REG_POST_TX_TIMERS, ( (Xil_In32(WLAN_MAC_REG_POST_TX_TIMERS) & ~WLAN_MAC_POST_TX_TIMERS_MASK_TIMER2_EN) | (d ? WLAN_MAC_POST_TX_TIMERS_MASK_TIMER2_EN : 0))))
#define wlan_mac_postRx_timer1_en(d)		(Xil_Out32(WLAN_MAC_REG_POST_RX_TIMERS, ( (Xil_In32(WLAN_MAC_REG_POST_RX_TIMERS) & ~WLAN_MAC_POST_RX_TIMERS_MASK_TIMER1_EN) | (d ? WLAN_MAC_POST_RX_TIMERS_MASK_TIMER1_EN : 0))))
#define wlan_mac_postRx_timer2_en(d)		(Xil_Out32(WLAN_MAC_REG_POST_RX_TIMERS, ( (Xil_In32(WLAN_MAC_REG_POST_RX_TIMERS) & ~WLAN_MAC_POST_RX_TIMERS_MASK_TIMER2_EN) | (d ? WLAN_MAC_POST_RX_TIMERS_MASK_TIMER2_EN : 0))))

//Bit masks for wlan_mac_hw STATUS register
#define WLAN_MAC_STATUS_MASK_TX_A_PENDING				0x00000001 //b[0]
#define WLAN_MAC_STATUS_MASK_TX_A_DONE					0x00000002 //b[1]
#define WLAN_MAC_STATUS_MASK_TX_A_RESULT				0x0000000C //b[3:2]
#define WLAN_MAC_STATUS_MASK_TX_A_STATE					0x00000070 //b[6:4]
#define WLAN_MAC_STATUS_MASK_TX_B_PENDING				0x00000080 //b[7]
#define WLAN_MAC_STATUS_MASK_TX_B_DONE					0x00000100 //b[8]
#define WLAN_MAC_STATUS_MASK_TX_B_RESULT				0x00000600 //b[10:9]
#define WLAN_MAC_STATUS_MASK_TX_B_STATE					0x00003800 //b[13:11]
#define WLAN_MAC_STATUS_MASK_TX_PHY_ACTIVE				0x00004000 //b[14]
#define WLAN_MAC_STATUS_MASK_RX_PHY_ACTIVE				0x00008000 //b[15]
#define WLAN_MAC_STATUS_MASK_NAV_BUSY					0x00010000 //b[16]
#define WLAN_MAC_STATUS_MASK_CCA_BUSY					0x00020000 //b[17]
#define WLAN_MAC_STATUS_MASK_RX_FCS_GOOD				0x00040000 //b[18]
#define WLAN_MAC_STATUS_MASK_RX_PHY_BLOCKED_FCS_GOOD	0x00080000 //b[19]
#define WLAN_MAC_STATUS_MASK_RX_PHY_BLOCKED				0x00100000 //b[20]
#define WLAN_MAC_STATUS_MASK_NAV_ADDR_MATCHED			0x00200000 //b[21]
#define WLAN_MAC_STATUS_MASK_POSTTX_TIMER2_RUNNING		0x00400000 //b[22]
#define WLAN_MAC_STATUS_MASK_POSTTX_TIMER1_RUNNING		0x00800000 //b[23]
#define WLAN_MAC_STATUS_MASK_POSTRX_TIMER2_RUNNING		0x01000000 //b[24]
#define WLAN_MAC_STATUS_MASK_POSTRX_TIMER1_RUNNING		0x02000000 //b[25]

#define WLAN_MAC_STATUS_TX_A_RESULT_NONE		(0 << 2) //FSM idle or still running
#define WLAN_MAC_STATUS_TX_A_RESULT_TIMEOUT		(1 << 2) //FSM completed with postTx timer expiration
#define WLAN_MAC_STATUS_TX_A_RESULT_RX_STARTED	(2 << 2) //FSM completed with PHY Rx starting

#define WLAN_MAC_STATUS_TX_A_STATE_IDLE 		(0 << 4)
#define WLAN_MAC_STATUS_TX_A_STATE_PRE_TX_WAIT	(1 << 4)
#define WLAN_MAC_STATUS_TX_A_STATE_START_BO		(2 << 4)
#define WLAN_MAC_STATUS_TX_A_STATE_DEFER 		(3 << 4)
#define WLAN_MAC_STATUS_TX_A_STATE_DO_TX 		(4 << 4)
#define WLAN_MAC_STATUS_TX_A_STATE_POST_TX 		(5 << 4)
#define WLAN_MAC_STATUS_TX_A_STATE_POST_TX_WAIT (6 << 4)
#define WLAN_MAC_STATUS_TX_A_STATE_DONE		 	(7 << 4)

#define WLAN_MAC_STATUS_TX_B_RESULT_NONE		(0 << 9) //FSM idle or still running
#define WLAN_MAC_STATUS_TX_B_RESULT_DID_TX		(1 << 9) //FSM completed with PHY Tx
#define WLAN_MAC_STATUS_TX_B_RESULT_NO_TX		(2 << 9) //FSM completed, skipped PHY Tx

#define WLAN_MAC_STATUS_TX_B_STATE_IDLE 		(0 << 11)
#define WLAN_MAC_STATUS_TX_B_STATE_PRE_TX_WAIT	(1 << 11)
#define WLAN_MAC_STATUS_TX_B_STATE_CHECK_NAV	(2 << 11)
#define WLAN_MAC_STATUS_TX_B_STATE_DO_TX 		(3 << 11)
#define WLAN_MAC_STATUS_TX_B_STATE_DONE		 	(4 << 11)

//Bit masks for PHY_RX_PARAMS register
#define WLAN_MAC_PHY_RX_PARAMS_MASK_LENGTH			0x0000FFFF //b[15:0]
#define WLAN_MAC_PHY_RX_PARAMS_MASK_MCS				0x003F0000 //b[22:16]
#define WLAN_MAC_PHY_RX_PARAMS_MASK_UNSUPPORTED		0x00800000 //b[23]
#define WLAN_MAC_PHY_RX_PARAMS_MASK_RX_ERROR		0x01000000 //b[24]
#define WLAN_MAC_PHY_RX_PARAMS_MASK_PHY_MODE		0x0E000000 //b[27:25]
#define WLAN_MAC_PHY_RX_PARAMS_MASK_PARAMS_VALID	0x10000000 //b[28]
#define WLAN_MAC_PHY_RX_PARAMS_MASK_PHY_SEL			0x20000000 //b[29]

#define WLAN_MAC_PHY_RX_PARAMS_PHY_SEL_DSSS			0x00000000
#define WLAN_MAC_PHY_RX_PARAMS_PHY_SEL_OFDM			0x20000000

#define WLAN_MAC_PHY_RX_PARAMS_PHY_MODE_11AG		0x1
#define WLAN_MAC_PHY_RX_PARAMS_PHY_MODE_11N			0x2
#define WLAN_MAC_PHY_RX_PARAMS_PHY_MODE_11AC		0x8

//Bit masks for CONTROL register
#define WLAN_MAC_CTRL_MASK_RESET					0x001
#define WLAN_MAC_CTRL_MASK_RX_PHY_BLOCK_EN			0x002
#define WLAN_MAC_CTRL_MASK_RX_PHY_BLOCK_RESET		0x004
#define WLAN_MAC_CTRL_MASK_DISABLE_NAV				0x008
#define WLAN_MAC_CTRL_MASK_BLOCK_RX_ON_TX			0x010
#define WLAN_MAC_CTRL_MASK_UPDATE_TIMESTAMP			0x020
#define WLAN_MAC_CTRL_MASK_BLOCK_RX_ON_VALID_RXEND	0x040 //blocks Rx on bad FCS pkts, only for logging/analysis
#define WLAN_MAC_CTRL_MASK_CCA_IGNORE_PHY_CS		0x080
#define WLAN_MAC_CTRL_MASK_CCA_IGNORE_TX_BUSY		0x100
#define WLAN_MAC_CTRL_MASK_CCA_IGNORE_NAV			0x200
#define WLAN_MAC_CTRL_MASK_RESET_NAV				0x400
#define WLAN_MAC_CTRL_MASK_RESET_BACKOFF			0x800

//Macros for reading/writing registers
#define wlan_mac_timestamp_lsb() Xil_In32(WLAN_MAC_REG_TIMESTAMP_LSB)
#define wlan_mac_timestamp_msb() Xil_In32(WLAN_MAC_REG_TIMESTAMP_MSB)

//WLAN_MAC_REG_SW_BACKOFF_CTRL:
// b[15:0]: Num Slots
// b[31]: Start
#define wlan_mac_set_backoff_num_slots(d) Xil_Out32(WLAN_MAC_REG_SW_BACKOFF_CTRL, ((Xil_In32(WLAN_MAC_REG_SW_BACKOFF_CTRL) & (~0x0000FFFF)) | ((d) & 0x0000FFFF)))
#define wlan_mac_backoff_start(x) Xil_Out32(WLAN_MAC_REG_SW_BACKOFF_CTRL, ((Xil_In32(WLAN_MAC_REG_SW_BACKOFF_CTRL) & (~0x80000000)) | (((x)<<31) & 0x80000000)))

//WLAN_MAC_IFS_1:
// b[9:0]: Slot
// b[29:20]: DIFS
#define wlan_mac_set_slot(d) Xil_Out32(WLAN_MAC_REG_IFS_1, ((Xil_In32(WLAN_MAC_REG_IFS_1) & (~0x000003FF)) | ((d) & 0x000003FF)))
#define wlan_mac_set_DIFS(d) Xil_Out32(WLAN_MAC_REG_IFS_1, ((Xil_In32(WLAN_MAC_REG_IFS_1) & (~0x3FF00000)) | (((d)<<20) & 0x3FF00000)))

//WLAN_MAC_IFS_2:
// b[15:0]: EIFS
// b[31:16]: ACK Timeout
#define wlan_mac_set_EIFS(d) Xil_Out32(WLAN_MAC_REG_IFS_2, ((Xil_In32(WLAN_MAC_REG_IFS_2) & (~0x0000FFFF)) | ((d) & 0x0000FFFF)))

//WLAN_MAC_CALIB_TIMES:
// b[9:0]: TxDIFS
// b[31:24]: NAV Adj (Fix8_0 - signed char!)
#define wlan_mac_set_TxDIFS(d) Xil_Out32(WLAN_MAC_REG_CALIB_TIMES, ((Xil_In32(WLAN_MAC_REG_CALIB_TIMES) & (~0x000003FF)) | ((d) & 0x000003FF)))
#define wlan_mac_set_NAV_adj(d) Xil_Out32(WLAN_MAC_REG_CALIB_TIMES, ((Xil_In32(WLAN_MAC_REG_CALIB_TIMES) & (~0xFF000000)) | (((d)<<20) & 0xFF000000)))

//TX_CTRL_A_PARAMS:
// b[3:0]: Pkt buf
// b[7:4]: Tx ant mask
// b[23:8]: Num backoff slots
// b[24]: Pre-Wait for PostRx Timer 1
// b[25]: Pre-Wait for PostTx Timer 1
// b[26]: Post-Wait for PostTx Timer 2
#define wlan_mac_tx_ctrl_A_params(pktBuf, antMask, preTx_backoff_slots, preWait_postRxTimer1, preWait_postTxTimer1, postWait_postTxTimer2) \
	Xil_Out32(WLAN_MAC_REG_TX_CTRL_A_PARAMS, \
		((pktBuf & 0xF) | \
		((antMask & 0xF) << 4) | \
		((preTx_backoff_slots & 0xFFFF) << 8) | \
		((preWait_postRxTimer1 & 0x1) << 24) | \
		((preWait_postTxTimer1 & 0x1) << 25) | \
		((postWait_postTxTimer2 & 0x1) << 26)))

////TX_CTRL_A_GAINS
// b[0:5]: RFA Tx gain
// b[6:11]: RFB Tx gain
// b[12:17]: RFC Tx gain
// b[18:23]: RFD Tx gain
#define wlan_mac_tx_ctrl_A_gains(rf_a, rf_b, rf_c, rf_d) \
	Xil_Out32(WLAN_MAC_REG_TX_CTRL_A_GAINS, \
			((rf_a & 0x3F) | \
			((rf_b & 0x3F) << 6) | \
			((rf_c & 0x3F) << 12) | \
			((rf_d & 0x3F) << 18)))

//TX_CTRL_B_PARAMS:
// b[3:0]: Pkt buf
// b[7:4]: Tx ant mask
// b[8]: Pre-Wait for PostRx Timer 1
// b[9]: Pre-Wait for PostRx Timer 2
// b[10]: Post-Wait for PostTx Timer 1
// b[11]: Require NAV=0 at Tx time (otherwise skip Tx)
#define wlan_mac_tx_ctrl_B_params(pktBuf, antMask, req_zeroNAV, preWait_postRxTimer1, preWait_postRxTimer2, postWait_postTxTimer1) \
	Xil_Out32(WLAN_MAC_REG_TX_CTRL_B_PARAMS, \
		((pktBuf & 0xF) | \
		((antMask & 0xF) << 4) | \
		((preWait_postRxTimer1 & 0x1) << 8) | \
		((preWait_postRxTimer2 & 0x1) << 9) | \
		((postWait_postTxTimer1 & 0x1) << 10) | \
		((req_zeroNAV & 0x1) << 11)))

//TX_CTRL_B_GAINS
// b[0:5]: RFA Tx gain
// b[6:11]: RFB Tx gain
// b[12:17]: RFC Tx gain
// b[18:23]: RFD Tx gain
#define wlan_mac_tx_ctrl_B_gains(rf_a, rf_b, rf_c, rf_d) \
	Xil_Out32(WLAN_MAC_REG_TX_CTRL_B_GAINS, \
			((rf_a & 0x3F) | \
			((rf_b & 0x3F) << 6) | \
			((rf_c & 0x3F) << 12) | \
			((rf_d & 0x3F) << 18)))


#define wlan_mac_set_backoff_reset(x) Xil_Out32( WLAN_MAC_REG_CONTROL, ( Xil_In32(WLAN_MAC_REG_CONTROL) & ~WLAN_MAC_CTRL_MASK_RESET_BACKOFF ) | ( (x) ? WLAN_MAC_CTRL_MASK_RESET_BACKOFF : 0 ) )

//TX_START
// b[0]: Tx CTRL A Start
// b[1]: Tx CTRL B Start
//Intrepret non-zero (x) as Tx start enable, zero (x) as Tx start disable
// MAC core requires rising edge on either Tx start bit; software must set then clear for each Tx
#define wlan_mac_tx_ctrl_A_start(x) Xil_Out32(WLAN_MAC_REG_TX_START, ((Xil_In32(WLAN_MAC_REG_TX_START) & ~0x1) | ((x) ? 0x1 : 0x0)))
#define wlan_mac_tx_ctrl_B_start(x) Xil_Out32(WLAN_MAC_REG_TX_START, ((Xil_In32(WLAN_MAC_REG_TX_START) & ~0x2) | ((x) ? 0x2 : 0x0)))

#define wlan_mac_set_timestamp_offset(d) Xil_Out32(WLAN_MAC_REG_SET_TIMESTAMP_OFFSET, d)
#define wlan_mac_get_timestamp_offset() Xil_In32(WLAN_MAC_REG_SET_TIMESTAMP_OFFSET)

#define wlan_mac_reset(x) Xil_Out32(WLAN_MAC_REG_CONTROL, (Xil_In32(WLAN_MAC_REG_CONTROL) & ~WLAN_MAC_CTRL_MASK_RESET) | (WLAN_MAC_CTRL_MASK_RESET & x))


#define wlan_mac_get_last_byte_index() (Xil_In32(WLAN_MAC_REG_LATEST_RX_BYTE) & 0xFFFF)
#define wlan_mac_get_last_byte() ((Xil_In32(WLAN_MAC_REG_LATEST_RX_BYTE) & 0xFF0000) >> 16)

#define wlan_mac_get_status() (Xil_In32(WLAN_MAC_REG_STATUS))
#define wlan_mac_get_backoff_count() (Xil_In32(WLAN_MAC_REG_BACKOFF_COUNTER) & 0xFFFF)

//RX_PHY_PARAMS Register:
// b[15:0] Length
// b[22:16] MCS
// b[23] Unsupported
// b[24] Rx Error
// b[27:25] Rx PHY Mode ([1,2,4] = [11a,11n,11ac])
// b[28] Rx params valid
// b[29] Rx PHY Sel (0=OFDM, 1=DSSS)
#define wlan_mac_get_rx_params() 			 (Xil_In32(WLAN_MAC_REG_PHY_RX_PARAMS))
#define wlan_mac_get_rx_phy_length()		 (Xil_In32(WLAN_MAC_REG_PHY_RX_PARAMS) & WLAN_MAC_PHY_RX_PARAMS_MASK_LENGTH)
#define wlan_mac_get_rx_phy_mcs() 			((Xil_In32(WLAN_MAC_REG_PHY_RX_PARAMS) & WLAN_MAC_PHY_RX_PARAMS_MASK_MCS) >> 16)
#define wlan_mac_get_rx_phy_sel() 			((Xil_In32(WLAN_MAC_REG_PHY_RX_PARAMS) & WLAN_MAC_PHY_RX_PARAMS_MASK_PHY_SEL))
#define wlan_mac_get_rx_phy_mode() 			((Xil_In32(WLAN_MAC_REG_PHY_RX_PARAMS) & WLAN_MAC_PHY_RX_PARAMS_MASK_PHY_MODE) >> 25)
#define wlan_mac_get_rx_phy_params_valid() 	((Xil_In32(WLAN_MAC_REG_PHY_RX_PARAMS) & WLAN_MAC_PHY_RX_PARAMS_MASK_PARAMS_VALID))

#define T_DIFS (T_SIFS + 2*T_SLOT)

#define T_EIFS 88
#define T_PHY_RX_START_DLY 25
#define T_TIMEOUT (T_SIFS+T_SLOT+T_PHY_RX_START_DLY)

#define POLL_MAC_STATUS_RECEIVED_PKT	0x00000001 //b[0]
#define POLL_MAC_STATUS_GOOD  		 	0x00000002 //b[1]
#define POLL_MAC_ADDR_MATCH				0x00000004 //b[2]
#define POLL_MAC_CANCEL_TX				0x00000008 //b[3]
#define POLL_MAC_STATUS_TYPE			0x0000FF00 //b[15:8]

#define POLL_MAC_TYPE_DATA				(1<<8)
#define POLL_MAC_TYPE_ACK				(1<<9)
#define POLL_MAC_TYPE_CTS				(1<<10)
#define POLL_MAC_TYPE_OTHER				(1<<11)

// WN Low Params
//     NOTE:  Need to make sure that these values do not conflict with any of the LOW PARAM
//     callback defines
#define LOW_PARAM_PHYSICAL_CS_THRESH	0x00000001
#define	LOW_PARAM_CW_EXP_MIN			0x00000002
#define LOW_PARAM_CW_EXP_MAX			0x00000003
#define LOW_PARAM_TIMESTAMP_OFFSET		0x00000004
#define LOW_PARAM_BB_GAIN				0x00000005
#define LOW_PARAM_LINEARITY_PA			0x00000006
#define LOW_PARAM_LINEARITY_VGA			0x00000007
#define LOW_PARAM_LINEARITY_UPCONV		0x00000008
#define LOW_PARAM_AD_SCALING			0x00000009
#define LOW_PARAM_PKT_DET_MIN_POWER		0x0000000A

#define PKT_DET_MIN_POWER_MIN -90
#define PKT_DET_MIN_POWER_MAX -30


int wlan_mac_low_init(u32 type);
u8 wlan_mac_low_get_cw_exp_min();
u8 wlan_mac_low_get_cw_exp_max();
void wlan_mac_low_finish_init();
void wlan_mac_low_dcf_init();
inline void wlan_mac_low_send_exception(u32 reason);
inline void wlan_mac_low_poll_ipc_rx();
void process_ipc_msg_from_high(wlan_ipc_msg* msg);
void wlan_mac_low_set_time(u64 new_time);
void wlan_mac_low_init_hw_info( u32 type );
wlan_mac_hw_info* wlan_mac_low_get_hw_info();
inline u32 wlan_mac_low_get_active_channel();
inline s8 wlan_mac_low_get_current_ctrl_tx_pow();
inline u32 wlan_mac_low_get_current_rx_filter();
int wlan_mac_low_rx_power_to_rssi(s8 rx_pow);
int wlan_mac_low_set_pkt_det_min_power(s8 rx_pow);
inline int wlan_mac_low_calculate_rx_power(u16 rssi, u8 lna_gain);
inline u32 wlan_mac_low_poll_frame_rx();
void wlan_mac_low_set_frame_rx_callback(function_ptr_t callback);
void wlan_mac_low_set_frame_tx_callback(function_ptr_t callback);
void wlan_mac_low_set_ipc_low_param_callback(function_ptr_t callback);
void wlan_mac_low_frame_ipc_send();
inline void wlan_mac_low_lock_empty_rx_pkt_buf();
inline u64 get_usec_timestamp();
inline u64 get_rx_start_timestamp();
inline u64 get_tx_start_timestamp();
void wlan_mac_dcf_hw_unblock_rx_phy();
inline u32 wlan_mac_dcf_hw_rx_finish();
inline u8 wlan_mac_low_dbm_to_gain_target(s8 power);
inline void wlan_mac_reset_backoff_counter();
inline void wlan_mac_reset_NAV_counter();
inline u32 wlan_mac_low_wlan_chan_to_rc_chan(u32 mac_channel);
void wlan_mac_set_nav_check_addr(u8* addr);
inline u8 wlan_mac_mcs_to_n_dbps(u8 mcs);
inline u8 wlan_mac_mcs_to_phy_rate(u8 mcs);
inline u8 wlan_mac_mcs_to_ctrl_resp_mcs(u8 mcs);

#endif /* WLAN_MAC_LOW_H_ */
