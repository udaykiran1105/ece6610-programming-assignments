/** @file wlan_mac_misc_util.h
 *  @brief Common Miscellaneous Definitions
 *
 *  This contains miscellaneous definitions of required by both the upper and
 *  lower-level CPUs.
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

#ifndef WLAN_MAC_MISC_UTIL_H_
#define WLAN_MAC_MISC_UTIL_H_

typedef int (*function_ptr_t)();

#define max(A,B) (((A)>(B))?(A):(B))
#define min(A,B) (((A)<(B))?(A):(B))
#define abs_64(A) (((A) < 0)?(-1*A):(A))

#define sat_add16(a, b) ( ((a) > (0xFFFF - (b))) ? 0xFFFF : ((a) + (b)) )
#define sat_add32(a, b) ( ((a) > (0xFFFFFFFF - (b))) ? 0xFFFFFFFF : ((a) + (b)) )

#define sat_sub(a, b) ( ((a) > (b)) ? ((a) - (b)) : 0 )

#define WLAN_PHY_FCS_NBYTES	4
#define T_SIFS 10

//#define _ISR_PERF_MON_EN_	///< ISR Performance Monitor Toggle
#define ISR_PERF_MON_GPIO_MASK	0x01

#define PRINT_LEVEL PL_ERROR

#define PL_NONE		0
#define PL_ERROR 	1
#define PL_WARNING  2
#define PL_VERBOSE  3

#define warp_printf(severity,format,args...) \
	do { \
	 if(PRINT_LEVEL>=severity){xil_printf(format, ##args);} \
	} while(0)

#define wlan_addr_eq(addr1, addr2) (memcmp((void*)(addr1), (void*)(addr2), 6)==0)
#define wlan_addr_mcast(addr) ( (((u8*)(addr))[0] & 1) == 1 )


//Reference: http://standards.ieee.org/develop/regauth/tut/macgrp.pdf
#define MAC_ADDR_MSB_MASK_MCAST	0x01
#define MAC_ADDR_MSB_MASK_LOCAL	0x02

typedef struct{
	u8      rate;			///< PHY rate index
	u8      antenna_mode;	///< Tx antenna selection
	s8      power;			///< Tx power (in dBm)
	u8		flags;			///< Flags affecting waveform construction
} phy_tx_params;

typedef struct{
	u8		flags;					///< Flags affecting waveform construction
	u8 		reserved[3];
} mac_tx_params;


///Compile-time assertions
#define CASSERT(predicate, file) _impl_CASSERT_LINE(predicate,__LINE__,file)

#define _impl_PASTE(a,b) a##b
#define _impl_CASSERT_LINE(predicate, line, file) \
    typedef char _impl_PASTE(assertion_failed_##file##_,line)[2*!!(predicate)-1];


/**
 * @brief Transmit Parameters Structure
 *
 * This struct contains transmission parameters.
 */
typedef struct{
	phy_tx_params phy; ///< PHY Tx params
	mac_tx_params mac; ///< Lower-level MAC Tx params
} tx_params;

typedef enum {TX_DETAILS_MPDU, TX_DETAILS_RTS_ONLY, TX_DETAILS_RTS_MPDU, TX_DETAILS_CTS, TX_DETAILS_ACK} tx_details_type_t;

///Note: This struct must be padded to be an integer
///number of u32 words.
typedef struct {
	u32   				  tx_start_delta;
	phy_tx_params 		  mpdu_phy_params;
	s16  				  num_slots;
	u16	  				  cw;
	u8 	  				  chan_num;
	tx_details_type_t 	  tx_details_type;
	u16 	  			  duration;
	u16 	  			  timestamp_offset;
	u16					  ssrc;
	u16					  slrc;
	u8					  src;
	u8					  lrc;
	phy_tx_params 		  ctrl_phy_params;
} wlan_mac_low_tx_details;

typedef struct {
	u8  phy_mode;
	u8	mcs;
	u16 length;
	u16 N_DBPS;		///< Number of data bits per OFDM symbol
} phy_rx_details;

#define PHY_RX_DETAILS_MODE_DSSS      (0)
#define PHY_RX_DETAILS_MODE_11AG   (WLAN_MAC_PHY_RX_PARAMS_PHY_MODE_11AG)
#define PHY_RX_DETAILS_MODE_11N    (WLAN_MAC_PHY_RX_PARAMS_PHY_MODE_11N)

typedef struct{
	u64 timestamp_create; 						///< MAC timestamp of packet creation
	u32 delay_accept;							///< Time in microseconds between timestamp_create and packet acceptance by CPU Low
	u32 delay_done;								///< Time in microseconds between acceptance and transmit completion
	u64	unique_seq;								///< Unique sequence number for this packet (12 LSB used as 802.11 MAC sequence number)
	u8 padding0;
	u8 tx_result;								///< Result of transmission attempt - TX_MPDU_RESULT_SUCCESS or TX_MPDU_RESULT_FAILURE
	u8 QID;										///< Queue ID from which this packet was taken
	u8 short_retry_count;
	u8 long_retry_count;
	u8 num_tx_attempts;
	u8 flags;									///< Bit flags en/disabling certain operations by the lower-level MAC
	u8 padding1;
	u16 length;									///< Number of bytes in MAC packet, including MAC header and FCS
	u16 AID;									///< Association ID of the node to which this packet is addressed
	u8 padding2[4];
	tx_params params;							///< Additional lower-level MAC and PHY parameters
} tx_frame_info;

#define TX_POWER_MAX_DBM (21)
#define TX_POWER_MIN_DBM (-9)

#define TX_MPDU_RESULT_SUCCESS	0
#define TX_MPDU_RESULT_FAILURE	1

#define TX_MPDU_FLAGS_REQ_TO				0x01
#define TX_MPDU_FLAGS_FILL_TIMESTAMP		0x02
#define TX_MPDU_FLAGS_FILL_DURATION			0x04
#define TX_MPDU_FLAGS_REQ_BO				0x08
#define TX_MPDU_FLAGS_AUTOCANCEL			0x10


//The rx_frame_info struct is padded to give space for the PHY to fill in channel estimates. The offset where
//the PHY fills in this information must be written to the wlan_phy_rx_pkt_buf_h_est_offset macro
typedef struct{
	u8 state;										///< Packet buffer state - RX_MPDU_STATE_EMPTY, RX_MPDU_STATE_RX_PENDING, RX_MPDU_STATE_FCS_GOOD or RX_MPDU_STATE_FCS_BAD
	u8 flags;										///< Bit flags
	u8 ant_mode;									///< Rx antenna selection
	s8 rx_power;									///< Rx power, in dBm
	phy_rx_details phy_details;						///< Details from PHY used in this reception
	u8 rf_gain;										///< Gain setting of radio Rx LNA, in [0,1,2]
	u8 bb_gain;										///< Gain setting of radio Rx VGA, in [0,1,...31]
	u8 channel;										///< Channel index
	u8 reserved1;
	u32 additional_info;							///< Field to hold MAC-specific info, such as a pointer to a station_info
	wlan_mac_low_tx_details	resp_low_tx_details;
	u64 timestamp;									///< MAC timestamp at time of reception
	u32 channel_est[64];							///< Rx PHY channel estimates
} rx_frame_info;

#define RX_MPDU_FLAGS_FORMED_RESPONSE		0x1
#define RX_MPDU_FLAGS_RETRY					0x2

#define RX_MPDU_STATE_EMPTY 	 	0
#define RX_MPDU_STATE_RX_PENDING	1
#define RX_MPDU_STATE_FCS_GOOD 	 	2
#define RX_MPDU_STATE_FCS_BAD 	 	3

#define CPU_STATUS_INITIALIZED			0x00000001
#define CPU_STATUS_EXCEPTION			0x80000000

#define NUM_TX_PKT_BUFS	8
#define NUM_RX_PKT_BUFS 8

#define PKT_BUF_SIZE 4096

//Tx and Rx packet buffers
#define TX_PKT_BUF_TO_ADDR(n)	(XPAR_PKT_BUFF_TX_BRAM_CTRL_S_AXI_BASEADDR + ((n)&0x7)*PKT_BUF_SIZE)
#define RX_PKT_BUF_TO_ADDR(n)	(XPAR_PKT_BUFF_RX_BRAM_CTRL_S_AXI_BASEADDR + ((n)&0x7)*PKT_BUF_SIZE)

#define PHY_RX_PKT_BUF_PHY_HDR_OFFSET (sizeof(rx_frame_info))
#define PHY_TX_PKT_BUF_PHY_HDR_OFFSET (sizeof(tx_frame_info))

#define PHY_RX_PKT_BUF_PHY_HDR_SIZE 0x10 //Was 0x8 through release v1.2 / xps v48
#define PHY_TX_PKT_BUF_PHY_HDR_SIZE 0x8

#define PHY_RX_PKT_BUF_MPDU_OFFSET (PHY_RX_PKT_BUF_PHY_HDR_SIZE+PHY_RX_PKT_BUF_PHY_HDR_OFFSET)
#define PHY_TX_PKT_BUF_MPDU_OFFSET (PHY_TX_PKT_BUF_PHY_HDR_SIZE+PHY_TX_PKT_BUF_PHY_HDR_OFFSET)

//Antenna modes (enumerated - these values are *not* written to PHY registers)
#define RX_ANTMODE_SISO_ANTA		0x0
#define RX_ANTMODE_SISO_ANTB		0x1
#define RX_ANTMODE_SISO_ANTC		0x2
#define RX_ANTMODE_SISO_ANTD		0x3
#define RX_ANTMODE_SISO_SELDIV_2ANT	0x4
#define RX_ANTMODE_SISO_SELDIV_4ANT	0x5

#define TX_ANTMODE_SISO_ANTA	0x10
#define TX_ANTMODE_SISO_ANTB	0x20
#define TX_ANTMODE_SISO_ANTC	0x30
#define TX_ANTMODE_SISO_ANTD	0x40

#define RX_FILTER_FCS_GOOD				0x1000  //Pass only packets with good checksum result
#define RX_FILTER_FCS_ALL				0x2000  //Pass packets with any checksum result
#define RX_FILTER_FCS_MASK				0xF000
#define RX_FILTER_FCS_NOCHANGE			RX_FILTER_FCS_MASK

#define RX_FILTER_HDR_ADDR_MATCH_MPDU 	0x0001	//Pass any unicast-to-me or multicast data or management packet
#define RX_FILTER_HDR_ALL_MPDU 			0x0002  //Pass any data or management packet (no address filter)
#define RX_FILTER_HDR_ALL				0x0003  //Pass any packet (no type or address filters)
#define RX_FILTER_HDR_MASK				0x0FFF
#define RX_FILTER_HDR_NOCHANGE			RX_FILTER_HDR_MASK

#endif /* WLAN_MAC_MISC_UTIL_H_ */
