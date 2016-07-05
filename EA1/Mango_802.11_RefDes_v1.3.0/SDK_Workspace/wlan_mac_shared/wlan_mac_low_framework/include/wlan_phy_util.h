/** @file wlan_phy_util.h
 *  @brief Physical Layer Utility
 *
 *  This contains code for configuring low-level parameters in the PHY and hardware.
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

#ifndef WLAN_PHY_UTIL_H_
#define WLAN_PHY_UTIL_H_

//Define standard macros for pcore base addresses and device IDs
// XPAR_ names will change with instance names in hardware
#define USERIO_BASEADDR		XPAR_W3_USERIO_BASEADDR
#define CLK_BASEADDR 		XPAR_W3_CLOCK_CONTROLLER_0_BASEADDR
#define EEPROM_BASEADDR 	XPAR_W3_IIC_EEPROM_ONBOARD_BASEADDR
#define FMC_EEPROM_BASEADDR XPAR_W3_IIC_EEPROM_FMC_BASEADDR
#define DRAM_BASEADDR 		XPAR_DDR3_2GB_SODIMM_MPMC_BASEADDR
#define RC_BASEADDR 		XPAR_RADIO_CONTROLLER_0_BASEADDR
#define AD_BASEADDR 		XPAR_W3_AD_CONTROLLER_0_BASEADDR

//Timer params
#define TIMER_FREQ			XPAR_TMRCTR_0_CLOCK_FREQ_HZ
#define TMRCTR_DEVICE_ID	XPAR_TMRCTR_0_DEVICE_ID
#define TIMER_COUNTER_0	 0

//Util macros for creating SIGNAL fields for transmission
#define WLAN_TX_SIGNAL_CALC(rate, length) (((rate) & 0xF) | (((length)&0xFFF)<<5) | (WLAN_TX_SIGNAL_PARITY_CALC(rate,length)))
#define WLAN_TX_SIGNAL_PARITY_CALC(rate, length) ((0x1 & (ones_in_chars[rate] + ones_in_chars[length&0xFF] + ones_in_chars[(length)>>8]))<<17)

//Times (in microseconds) for various PHY-level events, used by the MAC in its duration calculations
#define TXTIME_T_PREAMBLE 16	//320 samples @ 20MHz
#define TXTIME_T_SIGNAL 4		//80 samples @ 20MHz
#define TXTIME_T_SYM 4			//80 samples @ 20MHz

#define PHY_RX_SIG_EXT_USEC 6
//The extra 3 usec properly delays the assertion of TX END
//to match the assertion of RX END at the receiving node.
//#define PHY_TX_SIG_EXT_USEC (6+3) //TODO
#define PHY_TX_SIG_EXT_SAMP_PERIODS (182) //TODO


#define TX_RC_PHYSTART_DLY 0

//We empirically measured a 2.2usec latency from RC PHY start to observable waveform
#define TX_PHY_DLY_100NSEC ( ((TX_RC_PHYSTART_DLY)/4) + 22)

#define PHY_RX_RSSI_SUM_LEN 4
#define PHY_RX_RSSI_SUM_LEN_BITS 2 //LOG2(PHY_RX_RSSI_SUM_LEN)

//Modulation/coding rate values
#define WLAN_PHY_RATE_DSSS_1M	0x1 //RX Only
#define WLAN_PHY_RATE_BPSK12	0xB
#define WLAN_PHY_RATE_BPSK34	0xF
#define WLAN_PHY_RATE_QPSK12	0xA
#define WLAN_PHY_RATE_QPSK34	0xE
#define WLAN_PHY_RATE_16QAM12	0x9
#define WLAN_PHY_RATE_16QAM34	0xD
#define WLAN_PHY_RATE_64QAM23	0x8
#define WLAN_PHY_RATE_64QAM34	0xC

//Data bytes per OFDM symbol
//Table 17-3 of 2007 IEEE 802.11
#define N_DBPS_R6	24
#define N_DBPS_R9	36
#define N_DBPS_R12	48
#define N_DBPS_R18	72
#define N_DBPS_R24	96
#define N_DBPS_R36	144
#define N_DBPS_R48	192
#define N_DBPS_R54	216

//Fast Divide
#define U16REC1(A, M, S) (u16)((((u32)(A) * (u32)(M)) >> 16u) >> (S))
#define U16REC2(A, M, S) (u16)((((((u32)(A) * (u32)(M)) >> 16u) + (A)) >> 1u) >> (S))

#define U16DIVBY24(A)    U16REC1(A, 0xAAABu, 4u)
#define U16DIVBY36(A)    U16REC1(A, 0xE38Fu, 5u)
#define U16DIVBY48(A)    U16REC1(A, 0xAAABu, 5u)
#define U16DIVBY72(A)    U16REC1(A, 0xE38Fu, 6u)
#define U16DIVBY96(A)    U16REC1(A, 0xAAABu, 6u)
#define U16DIVBY144(A)    U16REC1(A, 0xE38Fu, 7u)
#define U16DIVBY192(A)    U16REC1(A, 0xAAABu, 7u)
#define U16DIVBY216(A)    U16REC2(A, 0x2F69u, 7u)



/* PHY Register Bit Masks */

//RX CONTROL
#define WLAN_RX_REG_CTRL_RESET			0x1

//RX CONFIG
#define WLAN_RX_REG_CFG_DSSS_RX_EN			0x000001 //Enable DSSS Rx
#define WLAN_RX_REG_CFG_USE_TX_SIG_BLOCK	0x000002 //Force I/Q/RSSI signals to zero during Tx
#define WLAN_RX_REG_CFG_PKT_BUF_WEN_SWAP	0x000004 //Swap byte order at pkt buf interface
#define WLAN_RX_REG_CFG_CHAN_EST_WEN_SWAP	0x000008 //Swap the order of H est writes per u64 ([0,1] vs [1,0])
#define WLAN_RX_REG_CFG_DSSS_RX_AGC_HOLD	0x000010 //Allow active DSSS Rx to keep AGC locked
#define WLAN_RX_REG_CFG_CFO_EST_BYPASS		0x000020 //Bypass time-domain CFO correction
#define WLAN_RX_REG_CFG_RECORD_CHAN_EST		0x000040 //Enable recording channel estimates to the Rx pkt buffer
#define WLAN_RX_REG_CFG_SWITCHING_DIV_EN	0x000080 //Enable switching diversity per-Rx
#define WLAN_RX_REG_CFG_DSSS_RX_REQ_AGC		0x000100 //DSSS Rx requires AGC be locked first
#define WLAN_RX_REG_CFG_PKT_DET_EN_ANT_A	0x000200 //Enable pkt detection on RF A
#define WLAN_RX_REG_CFG_PKT_DET_EN_ANT_B	0x000400 //Enable pkt detection on RF B
#define WLAN_RX_REG_CFG_PKT_DET_EN_ANT_C	0x000800 //Enable pkt detection on RF C
#define WLAN_RX_REG_CFG_PKT_DET_EN_ANT_D	0x001000 //Enable pkt detection on RF D
#define WLAN_RX_REG_CFG_PKT_DET_EN_EXT		0x002000 //Enable pkt detection via pkt_det_in port
#define WLAN_RX_REG_CFG_PHY_CCA_MODE_SEL	0x004000 //Selects any(0) or all(1) antenna requirement for PHY CCA BUSY
#define WLAN_RX_REG_CFG_ANT_SEL_MASK		0x018000 //Selects antenna for PHY input when sel div is disabled ([0,1,2,3] = RF[A,B,C,D])
#define WLAN_RX_REG_CFG_MAX_PKT_LEN_MASK	0x1E0000 //Sets max SIGNAL.LENGTH value in kB
#define WLAN_RX_REG_CFG_REQ_BOTH_PKT_DET	0x200000 //Requires both auto_corr and RSSI pkt det assertion to start Rx
#define WLAN_RX_REG_CFG_BUSY_HOLD_PKT_DET	0x400000 //Valid SIGNAL holds pkt det for rate*lengh duration, even if unsupported
#define WLAN_RX_REG_CFG_DSSS_ASSERTS_CCA	0x800000 //DSSS active holds CCA busy

#define wlan_phy_select_rx_antenna(d) Xil_Out32(WLAN_RX_REG_CFG, ((Xil_In32(WLAN_RX_REG_CFG) & ~WLAN_RX_REG_CFG_ANT_SEL_MASK) | ((d&0x3) << 15)))

//RX STATUS
#define WLAN_RX_REG_STATUS_OFDM_FCS_GOOD	0x1
#define WLAN_RX_REG_STATUS_DSSS_FCS_GOOD	0x2
#define WLAN_RX_REG_STATUS_ACTIVE_ANT_MASK	0xC //2-bits: [0,1,2,3]=RF[A,B,C,D]
#define WLAN_RX_REG_STATUS_PKT_DET_STATUS_MASK	0x1F0

//TX CONFIG
#define WLAN_TX_REG_CFG_SET_RC_RXEN					0x001
#define WLAN_TX_REG_CFG_RESET_SCRAMBLING_PER_PKT	0x002
#define WLAN_TX_REG_CFG_ANT_A_TXEN					0x004
#define WLAN_TX_REG_CFG_ANT_B_TXEN					0x008
#define WLAN_TX_REG_CFG_ANT_C_TXEN					0x010
#define WLAN_TX_REG_CFG_ANT_D_TXEN					0x020
#define WLAN_TX_REG_CFG_USE_MAC_ANT_MASKS			0x040
#define WLAN_TX_REG_CFG_DELAY_DBG_TX_RUNNING		0x080
#define WLAN_TX_REG_CFG_MAX_PKT_LEN_MASK			0xF00

#define WLAN_TX_REG_CFG_RESET						0x80000000

//TX STATUS
#define WLAN_TX_REG_STATUS_TX_RUNNING	0x1

//TX START
#define WLAN_TX_REG_START_DIRECT		0x1
#define WLAN_TX_REG_START_VIA_RC		0x2

//Register renames
#define WLAN_RX_REG_CTRL			XPAR_WLAN_PHY_RX_MEMMAP_CONTROL
#define WLAN_RX_REG_CFG				XPAR_WLAN_PHY_RX_MEMMAP_CONFIG
#define WLAN_RX_STATUS				XPAR_WLAN_PHY_RX_MEMMAP_STATUS
#define WLAN_RX_PKT_BUF_SEL			XPAR_WLAN_PHY_RX_MEMMAP_PKT_BUF_SEL
#define WLAN_RX_FEC_CFG				XPAR_WLAN_PHY_RX_MEMMAP_FEC_CONFIG
#define WLAN_RX_LTS_CFG				XPAR_WLAN_PHY_RX_MEMMAP_LTS_CORR_CONFIG
#define WLAN_RX_LTS_THRESH			XPAR_WLAN_PHY_RX_MEMMAP_LTS_CORR_THRESH
#define WLAN_RX_FFT_CFG				XPAR_WLAN_PHY_RX_MEMMAP_FFT_CONFIG
#define WLAN_RX_DEBUG_GPIO			XPAR_WLAN_PHY_RX_MEMMAP_DEBUG_GPIO
#define WLAN_RX_RSSI_THRESH			XPAR_WLAN_PHY_RX_MEMMAP_RSSI_THRESH
#define WLAN_RX_PKTDET_RSSI_CFG		XPAR_WLAN_PHY_RX_MEMMAP_PKTDET_RSSI_CONFIG
#define WLAN_RX_PHY_CCA_CFG			XPAR_WLAN_PHY_RX_MEMMAP_PHY_CCA_CONFIG
#define WLAN_RX_PKT_RSSI_AB			XPAR_WLAN_PHY_RX_MEMMAP_RX_PKT_RSSI_AB
#define WLAN_RX_PKT_RSSI_CD			XPAR_WLAN_PHY_RX_MEMMAP_RX_PKT_RSSI_CD
#define WLAN_RX_PKT_AGC_GAINS		XPAR_WLAN_PHY_RX_MEMMAP_RX_PKT_AGC_GAINS
#define WLAN_RX_DSSS_CFG			XPAR_WLAN_PHY_RX_MEMMAP_DSSS_RX_CONFIG
#define WLAN_RX_PKT_DET_OFDM_CFG	XPAR_WLAN_PHY_RX_MEMMAP_PKTDET_AUTOCORR_CONFIG
#define WLAN_RX_PKT_DET_DSSS_CFG 	XPAR_WLAN_PHY_RX_MEMMAP_PKTDET_DSSS_CONFIG
#define WLAN_RX_PKT_BUF_MAXADDR		XPAR_WLAN_PHY_RX_MEMMAP_PKTBUF_MAX_WRITE_ADDR

#define WLAN_TX_REG_STATUS			XPAR_WLAN_PHY_TX_MEMMAP_STATUS
#define WLAN_TX_REG_CFG				XPAR_WLAN_PHY_TX_MEMMAP_CONFIG
#define WLAN_TX_REG_PKT_BUF_SEL		XPAR_WLAN_PHY_TX_MEMMAP_PKT_BUF_SEL
#define WLAN_TX_REG_SCALING			XPAR_WLAN_PHY_TX_MEMMAP_OUTPUT_SCALING
#define WLAN_TX_REG_START			XPAR_WLAN_PHY_TX_MEMMAP_TX_START
#define WLAN_TX_REG_FFT_CFG			XPAR_WLAN_PHY_TX_MEMMAP_FFT_CONFIG
#define WLAN_TX_REG_TIMING			XPAR_WLAN_PHY_TX_MEMMAP_TIMING

#define WLAN_AGC_REG_RESET			XPAR_WLAN_AGC_MEMMAP_RESET
#define WLAN_AGC_REG_TIMING_AGC		XPAR_WLAN_AGC_MEMMAP_TIMING_AGC
#define WLAN_AGC_REG_TIMING_DCO		XPAR_WLAN_AGC_MEMMAP_TIMING_DCO
#define WLAN_AGC_REG_TARGET			XPAR_WLAN_AGC_MEMMAP_TARGET
#define WLAN_AGC_REG_CONFIG			XPAR_WLAN_AGC_MEMMAP_CONFIG
#define WLAN_AGC_REG_RSSI_PWR_CALIB	XPAR_WLAN_AGC_MEMMAP_RSSI_PWR_CALIB
#define WLAN_AGC_REG_IIR_COEF_B0	XPAR_WLAN_AGC_MEMMAP_IIR_COEF_B0
#define WLAN_AGC_REG_IIR_COEF_A1	XPAR_WLAN_AGC_MEMMAP_IIR_COEF_A1
#define WLAN_AGC_TIMING_RESET		XPAR_WLAN_AGC_MEMMAP_TIMING_RESET

#define REG_CLEAR_BITS(addr, mask)	Xil_Out32(addr, (Xil_In32(addr) & ~mask))
#define REG_SET_BITS(addr, mask)	Xil_Out32(addr, (Xil_In32(addr) | mask))

//PHY Macros

#define wlan_phy_enable_req_both_pkt_det() Xil_Out32(WLAN_RX_REG_CFG, (Xil_In32(WLAN_RX_REG_CFG) |  WLAN_RX_REG_CFG_REQ_BOTH_PKT_DET))
#define wlan_phy_disable_req_both_pkt_det() Xil_Out32(WLAN_RX_REG_CFG, (Xil_In32(WLAN_RX_REG_CFG) & ~WLAN_RX_REG_CFG_REQ_BOTH_PKT_DET))

#define wlan_phy_rx_set_max_pkt_len_kB(d) Xil_Out32(WLAN_RX_REG_CFG, (Xil_In32(WLAN_RX_REG_CFG) & ~WLAN_RX_REG_CFG_MAX_PKT_LEN_MASK) | (((d) << 17) & WLAN_RX_REG_CFG_MAX_PKT_LEN_MASK))
#define wlan_phy_tx_set_max_pkt_len_kB(d) Xil_Out32(WLAN_TX_REG_CFG, (Xil_In32(WLAN_TX_REG_CFG) & ~WLAN_TX_REG_CFG_MAX_PKT_LEN_MASK) | (((d) << 8) & WLAN_TX_REG_CFG_MAX_PKT_LEN_MASK))

#define wlan_phy_rx_set_max_pktbuf_addr(a) Xil_Out32(WLAN_RX_PKT_BUF_MAXADDR, (a))

//The PHY header offsets deal in units of u64 words, so the << 13 is like a << 16 and >> 3 to convert u8 words to u64 words
#define wlan_phy_rx_pkt_buf_phy_hdr_offset(d) Xil_Out32(WLAN_RX_PKT_BUF_SEL, ((Xil_In32(WLAN_RX_PKT_BUF_SEL) & (~0x00FF0000)) | (((d)<<13) & 0x00FF0000)))
#define wlan_phy_tx_pkt_buf_phy_hdr_offset(d) Xil_Out32(WLAN_TX_REG_PKT_BUF_SEL, ((Xil_In32(WLAN_TX_REG_PKT_BUF_SEL) & (~0x00FF0000)) | (((d)<<13) & 0x00FF0000)))

//Chan est offset is specified in units of u64 words; this macros converts a byte offset to u64 offset (hence the implicit >>3)
#define wlan_phy_rx_pkt_buf_h_est_offset(d) Xil_Out32(WLAN_RX_PKT_BUF_SEL, ((Xil_In32(WLAN_RX_PKT_BUF_SEL) & (~0xFF000000)) | (((d)<<(24-3)) & 0xFF000000)))

#define wlan_phy_tx_set_scaling(pre, pay) Xil_Out32(WLAN_TX_REG_SCALING, ( ( (pre) & 0xFFFF) | (( (pay)&0xFFFF)<<16)))


#define wlan_phy_rx_pkt_buf_dsss(d) Xil_Out32(WLAN_RX_PKT_BUF_SEL, ((Xil_In32(WLAN_RX_PKT_BUF_SEL) & (~0x00000F00)) | (((d)<<8) & 0x00000F00)))
#define wlan_phy_rx_pkt_buf_ofdm(d) Xil_Out32(WLAN_RX_PKT_BUF_SEL, ((Xil_In32(WLAN_RX_PKT_BUF_SEL) & (~0x0000000F)) | ((d) & 0x0000000F)))

#define wlan_phy_tx_pkt_buf(d) Xil_Out32(WLAN_TX_REG_PKT_BUF_SEL, ((Xil_In32(WLAN_TX_REG_PKT_BUF_SEL) & (~0x0000000F)) | ((d) & 0x0000000F)))

#define wlan_phy_tx_timestamp_ins_start(d) Xil_Out32(WLAN_TX_REG_PKT_BUF_SEL, ((Xil_In32(WLAN_TX_REG_PKT_BUF_SEL) & (~0x000003F0)) | ((d<<4) & 0x000003F0)))
#define wlan_phy_tx_timestamp_ins_end(d)   Xil_Out32(WLAN_TX_REG_PKT_BUF_SEL, ((Xil_In32(WLAN_TX_REG_PKT_BUF_SEL) & (~0x0000FC00)) | ((d<<10) & 0x0000FC00)))


//Currently
#define RX_ACTIVE_ANTA			0x0
#define RX_ACTIVE_ANTB			0x1
#define RX_ACTIVE_ANTC			0x2
#define RX_ACTIVE_ANTD			0x3

#define wlan_phy_rx_get_active_rx_ant()  ((Xil_In32(WLAN_RX_STATUS) & WLAN_RX_REG_STATUS_ACTIVE_ANT_MASK) >> 2)

#define wlan_phy_rx_get_pkt_det_status()  ((Xil_In32(WLAN_RX_STATUS) & WLAN_RX_REG_STATUS_PKT_DET_STATUS_MASK) >> 4)

//WLAN_RX_FFT_CFG register fields:
// [ 7: 0] Number of subcarriers (MUST BE 64 - OTHER VALUES UNTESTED)
// [15: 8] Cyclic prefix length (MUST BE 16 - OTHER VALUES UNTESTED)
// [23:16] FFT window offset - number of samples of CP to use on average (must be in [0,CP_LENGTH))
// [31:24] FFT scaling - UFix6_0 value; see Xilinx FFT datasheet for scaling details
#define wlan_phy_rx_set_fft_window_offset(d) Xil_Out32(WLAN_RX_FFT_CFG, ((Xil_In32(WLAN_RX_FFT_CFG) & 0xFF00FFFF) | ((d & 0xFF) << 16)))
#define wlan_phy_rx_set_fft_scaling(d) Xil_Out32(WLAN_RX_FFT_CFG, ((Xil_In32(WLAN_RX_FFT_CFG) & 0x00FFFFFF) | ((d & 0xFF) << 24)))

//RSSI reg: b[15:0]=RFA, b[31:16]=RFB
//RSSI reg: b[15:0]=RFC, b[31:16]=RFd

//Note: The final << 1 accounts for the fact that this register actually
//returns the summed RSSI divided by 2
#define wlan_phy_rx_get_pkt_rssi(ant) (( (ant==0) ? (Xil_In32(WLAN_RX_PKT_RSSI_AB) & 0xFFFF) : \
		(ant==1) ? ((Xil_In32(WLAN_RX_PKT_RSSI_AB)>>16) & 0xFFFF) : \
		(ant==2) ? (Xil_In32(WLAN_RX_PKT_RSSI_CD) & 0xFFFF) : \
		(Xil_In32(WLAN_RX_PKT_RSSI_CD)>>16) & 0xFFFF) << 1)

//AGC gains reg:
// [4:0]: RF A BBG
// [6:5]: RF A RFG
// [7]:   0
// [12:8]: RF B BBG
// [14:13]: RF B RFG
// [15]: 0
// [20:16]: RF C BBG
// [22:21]: RF C RFG
// [23]: 0
// [28:24]: RF D BBG
// [30:29]: RF D RFG

#define wlan_phy_rx_get_agc_RFG(ant) (( (ant==0) ? (Xil_In32(WLAN_RX_PKT_AGC_GAINS)>>5) : \
										(ant==1) ? (Xil_In32(WLAN_RX_PKT_AGC_GAINS)>>13) : \
										(ant==2) ? (Xil_In32(WLAN_RX_PKT_AGC_GAINS)>>21) : \
												   (Xil_In32(WLAN_RX_PKT_AGC_GAINS)>>29)) & 0x3)

#define wlan_phy_rx_get_agc_BBG(ant) (( (ant==0) ? (Xil_In32(WLAN_RX_PKT_AGC_GAINS)>>0) : \
										(ant==1) ? (Xil_In32(WLAN_RX_PKT_AGC_GAINS)>>8) : \
										(ant==2) ? (Xil_In32(WLAN_RX_PKT_AGC_GAINS)>>16) : \
												   (Xil_In32(WLAN_RX_PKT_AGC_GAINS)>>24)) & 0x1F)

#define	wlan_phy_DSSS_rx_enable() Xil_Out32(WLAN_RX_REG_CFG, Xil_In32(WLAN_RX_REG_CFG) | WLAN_RX_REG_CFG_DSSS_RX_EN)
#define	wlan_phy_DSSS_rx_disable() Xil_Out32(WLAN_RX_REG_CFG, Xil_In32(WLAN_RX_REG_CFG) & ~WLAN_RX_REG_CFG_DSSS_RX_EN)


#define wlan_phy_rx_pktDet_RSSI_cfg(sum_len, sum_thresh, min_dur) \
	Xil_Out32(WLAN_RX_PKTDET_RSSI_CFG, ( (sum_len & 0x1F) | ((sum_thresh & 0x7FFF) << 5) | ((min_dur & 0x1F)<<20)))

//WLAN_RX_DSSS_CFG:
// b[11: 0]: Correlation threshold as UFix12_4
// b[16:12]: DSSS de-spread delay
// b[31:24]: Rx timeout - max bits to SFD
#define	wlan_phy_DSSS_rx_config(code_corr, despread_dly, sfd_timeout) Xil_Out32(WLAN_RX_DSSS_CFG,  \
	((code_corr & 0xFFFF) | ((despread_dly & 0x1F)<<12) | ((sfd_timeout & 0xFF)<<24)))

//WLAN_RX_PKT_DET_DSSS_CFG:
// b[ 7: 0]: Correlation threshold as UFix8_6
// b[17: 8]: Energy threshold as UFix10_0
// b[24:18]: Det timeout - minimum number of ones before timeout bit count
// b[31:25]: Det timeout - timeout bit count
#define wlan_phy_rx_pktDet_autoCorr_dsss_cfg(corr_thresh, energy_thresh, timeout_ones, timeout_count) \
	Xil_Out32(WLAN_RX_PKT_DET_DSSS_CFG, ( (corr_thresh & 0xFF) | ((energy_thresh & 0x3FF) << 8) | ((timeout_ones & 0x7F)<<18) | ( (timeout_count & 0x7F)<<25)))

//WLAN_RX_PKT_DET_OFDM_CFG:
// b[ 7: 0]: Correlation threshold as UFix8_8
// b[21: 8]: Energy threshold as UFix14_8
// b[25:22]: Minimum duration (also used by DSSS det)
// b[31:26]: Post det reset block (also used by DSSS det)
#define wlan_phy_rx_pktDet_autoCorr_ofdm_cfg(corr_thresh, energy_thresh, min_dur, post_wait) \
	Xil_Out32(WLAN_RX_PKT_DET_OFDM_CFG, ( (corr_thresh & 0xFF) | ((energy_thresh & 0x3FFF) << 8) | ((min_dur & 0xF)<<22) | ( (post_wait & 0x3F)<<26)))


#define wlan_phy_rx_lts_corr_thresholds(corr_thresh_low_snr, corr_thresh_high_snr) \
	Xil_Out32(WLAN_RX_LTS_THRESH, (corr_thresh_low_snr & 0xFFFF) | ((corr_thresh_high_snr & 0xFFFF) << 16))

#define wlan_phy_rx_lts_corr_config(snr_thresh, corr_timeout) \
	Xil_Out32(WLAN_RX_LTS_CFG, (corr_timeout & 0xFF) | ((snr_thresh & 0xFFFF) << 8))

#define wlan_phy_tx_set_extension(d) Xil_Out32(WLAN_TX_REG_TIMING, ( (Xil_In32(WLAN_TX_REG_TIMING) & 0xFFFFFF00) | ((d) & 0xFF)))
#define wlan_phy_tx_set_txen_extension(d) Xil_Out32(WLAN_TX_REG_TIMING, ( (Xil_In32(WLAN_TX_REG_TIMING) & 0xFFFF00FF) | (((d) & 0xFF) << 8)))
#define wlan_phy_tx_set_rx_invalid_extension(d) Xil_Out32(WLAN_TX_REG_TIMING, ( (Xil_In32(WLAN_TX_REG_TIMING) & 0xFF00FFFF) | (((d) & 0xFF) << 16)))

#define wlan_phy_rx_set_cca_thresh(d) Xil_Out32(WLAN_RX_PHY_CCA_CFG, ((Xil_In32(WLAN_RX_PHY_CCA_CFG) & 0xFFFF0000) | ((d) & 0xFFFF)))
#define wlan_phy_rx_set_extension(d) Xil_Out32(WLAN_RX_PHY_CCA_CFG, ((Xil_In32(WLAN_RX_PHY_CCA_CFG) & 0xFF00FFFF) | (((d)<<16) & 0xFF0000)))


//AGC Macros
#define wlan_agc_set_AGC_timing(capt_rssi_1, capt_rssi_2, capt_v_db, agc_done) \
	Xil_Out32(WLAN_AGC_REG_TIMING_AGC, ( (capt_rssi_1 & 0xFF) | ( (capt_rssi_2 & 0xFF)<<8) | \
										 ( (capt_v_db & 0xFF)<<16) | ( (agc_done & 0xFF) << 24)))

#define wlan_agc_set_DCO_timing(start_dco, en_iir_filt) \
	Xil_Out32(WLAN_AGC_REG_TIMING_DCO, (start_dco & 0xFF) | ( (en_iir_filt & 0xFF)<<8))

#define wlan_agc_set_target(target_pwr) Xil_Out32(WLAN_AGC_REG_TARGET, (target_pwr & 0x3F))

#define wlan_agc_set_config(thresh32, thresh21, avg_len, v_db_adj, init_g_bb) \
	Xil_Out32(WLAN_AGC_REG_CONFIG, \
			((thresh32 & 0xFF) << 0) | \
			((thresh21 & 0xFF) << 8) | \
			((avg_len & 0x03) << 16) | \
			((v_db_adj & 0x3F) << 18) | \
			((init_g_bb & 0x1F) << 24))

#define wlan_agc_set_RSSI_pwr_calib(g3, g2, g1) Xil_Out32(WLAN_AGC_REG_RSSI_PWR_CALIB, ( (g3 & 0xFF) | ((g2 & 0xFF)<<8) | ((g1 & 0xFF)<<16)))

#define wlan_agc_set_reset_timing(rxhp,g_rf, g_bb) \
	Xil_Out32(WLAN_AGC_TIMING_RESET, ((rxhp & 0xFF) | ( (g_rf & 0xFF)<<8) | ( (g_bb & 0xFF) << 16)))


//Uncomment this macro to enable software support for RF C and D interfaces on the FMC-RF-2X245 module
// IMPORTANT: Do not use a 4-radio hardware project on a kit with a different FMC module
//#define WLAN_4RF_EN

#ifdef WLAN_4RF_EN
#define RC_ALL_RF (RC_RFA | RC_RFB | RC_RFC | RC_RFD)
#define AD_ALL_RF (RFA_AD_CS | RFB_AD_CS | RFC_AD_CS | RFD_AD_CS)
#else
#define RC_ALL_RF (RC_RFA | RC_RFB)
#define AD_ALL_RF (RFA_AD_CS | RFB_AD_CS)
#endif



/* Function Prototypes for wlan_phy_util.c */
u32 wlan_phy_cca_indication();
void wlan_phy_init();
void wlan_radio_init();
int w3_node_init();
void usleep(u32 duration);
inline void wlan_tx_start();
inline void wlan_tx_buffer_sel(u8 n);
inline int wlan_tx_isrunning();
inline u16 wlan_ofdm_txtime(u16 length,u16 n_DBPS);
inline u16 wlan_ofdm_txtime_fast(u16 length,u16 n_DBPS);
void wlan_phy_set_tx_signal(u8 pkt_buf, u8 rate, u16 length);
void process_config_phy_rx(ipc_config_phy_rx* config_phy_rx);
void process_config_phy_tx(ipc_config_phy_tx* config_phy_tx);
void wlan_agc_config(u32 ant_mode);
void wlan_tx_config_ant_mode(u32 ant_mode);
void wlan_rx_config_ant_mode(u32 ant_mode);

extern const u8 ones_in_chars[256];

#endif /* WLAN_PHY_UTIL_H_ */
