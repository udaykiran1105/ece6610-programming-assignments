/** @file wlan_mac_dcf.h
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

#ifndef WLAN_MAC_DCF_H_
#define WLAN_MAC_DCF_H_

#define PKT_BUF_INVALID 0xFF

#define TX_PKT_BUF_RTS	   6
#define TX_PKT_BUF_ACK_CTS 7

//Custom DCF Low Params
#define LOW_PARAM_DCF_RTS_THRESH			0x10000001
#define LOW_PARAM_DCF_DOT11SHORTRETRY		0x10000002
#define LOW_PARAM_DCF_DOT11LONGRETRY		0x10000003

//CW Update Reasons
#define DCF_CW_UPDATE_MPDU_TX_ERR 0
#define DCF_CW_UPDATE_MPDU_RX_ACK 1
#define DCF_CW_UPDATE_BCAST_TX 2

#define MAC_HW_LASTBYTE_ADDR1 (13)

#define RAND_SLOT_REASON_STANDARD_ACCESS 0
#define RAND_SLOT_REASON_IBSS_BEACON     1

//These are hardcoded OFDM TX times for CTS frames of various rates
//Since CTS is a fixed size, we can precompute these to save time
#define TX_TIME_CTS_R6 50
#define TX_TIME_CTS_R12 38
#define TX_TIME_CTS_R24 34


typedef enum {RX_FINISH_SEND_NONE, RX_FINISH_SEND_A, RX_FINISH_SEND_B} rx_finish_state_t;
typedef enum {TX_PENDING_NONE, TX_PENDING_A, TX_PENDING_B} tx_pending_state_t;

typedef enum {TX_WAIT_NONE, TX_WAIT_ACK, TX_WAIT_CTS} tx_wait_state_t;
typedef enum {TX_MODE_SHORT, TX_MODE_LONG} tx_mode_t;

int main();
int frame_transmit(u8 mpdu_pkt_buf, u8 mpdu_rate, u16 mpdu_length, wlan_mac_low_tx_details* low_tx_details);
u32 frame_receive(u8 rx_pkt_buf, phy_rx_details* phy_details);
inline void increment_src_ssrc(u8* src_ptr);
inline void increment_lrc_slrc(u8* lrc_ptr);
inline void reset_cw();
inline void reset_ssrc();
inline void reset_slrc();
//inline void update_cw(u8 reason, u8 pkt_buf);
inline unsigned int rand_num_slots(u8 reason);
void wlan_mac_dcf_hw_start_backoff(u16 num_slots);
int wlan_dcf_process_low_param(u8 mode, u32* payload);
int wlan_create_ack_frame(void* pkt_buf_addr, u8* address_ra);
int wlan_create_cts_frame(void* pkt_buf_addr, u8* address_ra, u16 duration);
int wlan_create_rts_frame(void* pkt_buf_addr, u8* address_ra, u8* address_ta, u16 duration);



#endif /* WLAN_MAC_DCF_H_ */
