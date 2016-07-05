/** @file wlan_mac_high.h
 *  @brief Top-level WLAN MAC High Framework
 *
 *  This contains the top-level code for accessing the WLAN MAC High Framework.
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

#ifndef WLAN_MAC_HIGH_H_
#define WLAN_MAC_HIGH_H_

#define INIT_DATA_BASEADDR                  XPAR_MB_HIGH_INIT_BRAM_CTRL_S_AXI_BASEADDR   ///< Base address of memory used for storing boot data
#define INIT_DATA_DOTDATA_IDENTIFIER	    0x1234ABCD                                   ///< "Magic number" used as an identifier in boot data memory
#define INIT_DATA_DOTDATA_START             (INIT_DATA_BASEADDR+0x200)                   ///< Offset into memory for boot data
#define INIT_DATA_DOTDATA_SIZE              (4*(XPAR_MB_HIGH_INIT_BRAM_CTRL_S_AXI_HIGHADDR - INIT_DATA_DOTDATA_START))  ///< Amount of space available in boot data memory

#define ENCAP_MODE_AP                       0                                       ///< Used as a flag for AP encapsulation and de-encapsulation
#define ENCAP_MODE_STA                      1                                       ///< Used as a flag for STA encapsulation and de-encapsulation
#define ENCAP_MODE_IBSS                     2                                       ///< Used as a flag for IBSS encapsulation and de-encapsulation

#define TX_BUFFER_NUM                       2                                       ///< Number of PHY transmit buffers to use. This should remain 2 (ping/pong buffering).

#define INTC_DEVICE_ID                      XPAR_INTC_0_DEVICE_ID					///< XParameters rename of interrupt controller device ID
#define ETH_A_MAC_DEVICE_ID                 XPAR_ETH_A_MAC_DEVICE_ID                ///< XParameters rename for ETH A
#define TIMESTAMP_GPIO_DEVICE_ID            XPAR_MB_HIGH_TIMESTAMP_GPIO_DEVICE_ID   ///< XParameters rename for GPIO used as usec timestamp
#define UARTLITE_DEVICE_ID                  XPAR_UARTLITE_0_DEVICE_ID               ///< XParameters rename for UART

#define TIMESTAMP_GPIO_LSB_CHAN             1                                       ///< GPIO channel used for lower 32 bits of 64-bit timestamp
#define TIMESTAMP_GPIO_MSB_CHAN             2                                       ///< GPIO channel used for upper 32 bits of 64-bit timestamp



// Aux. BRAM and DRAM Memory Map

#define AUX_BRAM_BASE					(XPAR_MB_HIGH_AUX_BRAM_CTRL_S_AXI_BASEADDR)
#define AUX_BRAM_SIZE					(XPAR_MB_HIGH_AUX_BRAM_CTRL_S_AXI_HIGHADDR - XPAR_MB_HIGH_AUX_BRAM_CTRL_S_AXI_BASEADDR + 1)
#define AUX_BRAM_HIGH					(XPAR_MB_HIGH_AUX_BRAM_CTRL_S_AXI_HIGHADDR)
#define	DRAM_BASE						(XPAR_DDR3_SODIMM_S_AXI_BASEADDR)
#define DRAM_SIZE						(XPAR_DDR3_SODIMM_S_AXI_HIGHADDR - XPAR_DDR3_SODIMM_S_AXI_BASEADDR + 1)
#define	DRAM_HIGH						(XPAR_DDR3_SODIMM_S_AXI_HIGHADDR)
/*
//     Aux. BRAM     |          DRAM
//--------------------------------------------
//
// Tx Queue DL_ENTRY -> Tx Queue Buffer
//
//-------------------|
//                   |
// BSS Info DL_ENTRY |------------------------
//                   ->
//-------------------|  BSS Info Buffer
// Eth Tx BD         |
//-------------------|
//                   |------------------------
// Eth Rx BD         |
//                   | User Scratch Space
//-------------------|
//                   |------------------------
//                   |
//                   |
//                   | Event Log
//                   |
//                   |
//                   |------------------------
*/

#define high_addr_calc(base, size)      ((base)+((size)-1))


/* The Tx Queue consists of two pieces:
 *  (1) dl_entry structs that live in the aux. BRAM and
 *  (2) data buffers for the packets themselves than live in DRAM
 *
 *	The below definitions carve out the sizes of memory for these two pieces.
 *	The default value of 40 kB do the dl_entry memory space was chosen. Because
 *	each dl_entry has a size of 12 bytes, this space allows for a potential
 *	of 3413 dl_entry structs describing Tx queue elements.
 *
 *	As far as the actual payload space in DRAM, 14000 kB was chosen because this
 *	is enough to store each of the 3413 Tx queue elements. Each queue element points
 *	to a unique 4KB-sized buffer.
 */
#define TX_QUEUE_DL_ENTRY_MEM_BASE		(AUX_BRAM_BASE)
#define TX_QUEUE_DL_ENTRY_MEM_SIZE		(40*1024)
#define TX_QUEUE_DL_ENTRY_MEM_HIGH		high_addr_calc(TX_QUEUE_DL_ENTRY_MEM_BASE, TX_QUEUE_DL_ENTRY_MEM_SIZE)
#define TX_QUEUE_BUFFER_BASE            (DRAM_BASE)
#define TX_QUEUE_BUFFER_SIZE            (14000*1024)
#define TX_QUEUE_BUFFER_HIGH            high_addr_calc(TX_QUEUE_BUFFER_BASE, TX_QUEUE_BUFFER_SIZE)

/* Like the Tx Queue, BSS Info consists of two pieces:
 *  (1) dl_entry structs that live in the aux. BRAM and
 *  (2) bss_info buffers with the actual content that live in DRAM
 *
 *	The below definitions carve out the sizes of memory for these two pieces.
 *	The default value of 9 kB for the dl_entry memory space was chosen. Because
 *	each dl_entry has a size of 12 bytes, this space allows for a potential
 *	of 768 dl_entry structs describing bss_info elements.
 *
 *	Each bss_info struct is a total of 80 bytes in size. So, 768 bss_info
 *	structs require 60 kB of memory. This is why BSS_INFO_BUFFER_SIZE
 *	is set to 60 kB.
 */
#define BSS_INFO_DL_ENTRY_MEM_BASE		(TX_QUEUE_DL_ENTRY_MEM_BASE + TX_QUEUE_DL_ENTRY_MEM_SIZE)
#define	BSS_INFO_DL_ENTRY_MEM_SIZE		(9*1024)
#define	BSS_INFO_DL_ENTRY_MEM_HIGH		high_addr_calc(BSS_INFO_DL_ENTRY_MEM_BASE, BSS_INFO_DL_ENTRY_MEM_SIZE)
#define BSS_INFO_BUFFER_BASE			(TX_QUEUE_BUFFER_BASE + TX_QUEUE_BUFFER_SIZE)
#define BSS_INFO_BUFFER_SIZE			(60*1024)
#define BSS_INFO_BUFFER_HIGH			high_addr_calc(BSS_INFO_BUFFER_BASE, BSS_INFO_BUFFER_SIZE)

/* The current architecture blocks on Ethernet transmissions. As such, only a
 * single Eth DMA buffer descriptor (BD) is needed. Each BD is 64 bytes in
 * size (see XAXIDMA_BD_MINIMUM_ALIGNMENT), so we set ETH_TX_BD_SIZE to 64.
 */
#define ETH_TX_BD_BASE					(BSS_INFO_DL_ENTRY_MEM_BASE + BSS_INFO_DL_ENTRY_MEM_SIZE)
#define ETH_TX_BD_SIZE					(64)
#define ETH_TX_BD_HIGH					high_addr_calc(ETH_TX_BD_BASE, ETH_TX_BD_SIZE)

/* Since it is the last section we are defining in the aux. BRAM, we allow
 * the ETH_RX to fill up the rest of the BRAM. This remaining space allows for
 * a total of 239 Eth Rx DMA BDs.
 */
#define ETH_RX_BD_BASE					(ETH_TX_BD_BASE + ETH_TX_BD_SIZE)
#define ETH_RX_BD_SIZE					(AUX_BRAM_SIZE - (TX_QUEUE_DL_ENTRY_MEM_SIZE + BSS_INFO_DL_ENTRY_MEM_SIZE + ETH_TX_BD_SIZE))
#define ETH_RX_BD_HIGH					high_addr_calc(ETH_RX_BD_BASE, ETH_RX_BD_SIZE)

/* We have set aside ~14MB of space for users to use the DRAM in their applications.
 * We do not use the below definitions in any part of the reference design.
 */
#define USER_SCRATCH_BASE				(BSS_INFO_BUFFER_BASE + BSS_INFO_BUFFER_SIZE)
#define USER_SCRATCH_SIZE				(14336*1024)
#define USER_SCRATCH_HIGH				high_addr_calc(USER_SCRATCH_BASE, USER_SCRATCH_SIZE)


/* Finally, the remaining space in DRAM is used for the WLAN_EXP event log. The above sections in DRAM
 * are much smaller than the space set aside for the event log. In the current implementation, the
 * event log is ~996 MB.
 */
#define EVENT_LOG_BASE					(USER_SCRATCH_BASE + USER_SCRATCH_SIZE)
#define EVENT_LOG_SIZE					(DRAM_SIZE - (TX_QUEUE_BUFFER_SIZE + BSS_INFO_BUFFER_SIZE + USER_SCRATCH_SIZE))
#define EVENT_LOG_HIGH					high_addr_calc(EVENT_LOG_BASE, EVENT_LOG_SIZE)

// End Aux. BRAM and DRAM Memory Map


#define USERIO_BASEADDR                     XPAR_W3_USERIO_BASEADDR            ///< XParameters rename of base address of User I/O

#define GPIO_DEVICE_ID                      XPAR_MB_HIGH_SW_GPIO_DEVICE_ID     ///< XParameters rename of device ID of GPIO
#define INTC_GPIO_INTERRUPT_ID              XPAR_INTC_0_GPIO_0_VEC_ID          ///< XParameters rename of GPIO interrupt ID
#define UARTLITE_INT_IRQ_ID                 XPAR_INTC_0_UARTLITE_0_VEC_ID      ///< XParameters rename of UART interrupt ID
#define TMRCTR_INTERRUPT_ID                 XPAR_INTC_0_TMRCTR_0_VEC_ID        ///< XParameters rename of timer interrupt ID

#define GPIO_OUTPUT_CHANNEL                 1                                  ///< Channel used as output for GPIO
#define GPIO_INPUT_CHANNEL                  2                                  ///< Channel used as input for GPIO
#define GPIO_INPUT_INTERRUPT                XGPIO_IR_CH2_MASK                  ///< Mask for enabling interrupts on GPIO input

#define GPIO_MASK_DRAM_INIT_DONE            0x00000100                         ///< Mask for GPIO -- DRAM initialization bit
#define GPIO_MASK_PB_U                      0x00000040                         ///< Mask for GPIO -- "Up" Pushbutton
#define GPIO_MASK_PB_M                      0x00000020                         ///< Mask for GPIO -- "Middle" Pushbutton
#define GPIO_MASK_PB_D                      0x00000010                         ///< Mask for GPIO -- "Down" Pushbutton
#define GPIO_MASK_DS_3                      0x00000008                         ///< Mask for GPIO -- MSB of Dip Switch

#define UART_BUFFER_SIZE                     1                                 ///< UART is configured to read 1 byte at a time

#define NUM_VALID_RATES                     12                                 ///< Number of supported rates

#define PKT_TYPE_DATA_OTHER                  1                                 ///< Other Data
#define PKT_TYPE_DATA_ENCAP_ETH	             2                                 ///< Encapsulated Ethernet Type
#define PKT_TYPE_DATA_ENCAP_LTG	             3                                 ///< Encapsulated LTG Type
#define PKT_TYPE_DATA_PROTECTED	             4                                 ///< Protected Data
#define PKT_TYPE_MGMT                       11                                 ///< Management Type
#define PKT_TYPE_CONTROL_ACK                21                                 ///< ACK Control Type
#define PKT_TYPE_CONTROL_RTS                22                                 ///< RTS Control Type
#define PKT_TYPE_CONTROL_CTS                23                                 ///< CTS Control Type

#define ADD_ASSOCIATION_ANY_AID              0                                 ///< Special argument to function that adds associations

#define WLAN_MAC_HIGH_MAX_PROMISC_STATS     50                                 ///< Maximum number of promiscuous statistics
#define WLAN_MAC_HIGH_MAX_ASSOCIATONS       20                                 ///< Maximum number of associations

#define SSID_LEN_MAX                        32                                 ///< Maximum SSID length


/* Include other framework headers
 * Includes have to be after any #define
 * that are needed in the typedefs within the
 * includes. */
#include "wlan_mac_queue.h"
#include "wlan_mac_packet_types.h"
#include "wlan_mac_ipc_util.h"
#include "wlan_mac_misc_util.h"
#include "wlan_mac_dl_list.h"


typedef enum {INTERRUPTS_DISABLED, INTERRUPTS_ENABLED} interrupt_state_t;

/**
 * @brief Frame Statistics Structure
 *
 * This struct contains statistics about the communications link. It is intended to
 * be instantiated multiple times in the broader statistics_txrx struct so that
 * different packet types can be individually tracked.
 */
typedef struct{
	u64		rx_num_bytes;				///< # of successfully received bytes (de-duplicated)
	u64		tx_num_bytes_success;		///< # of successfully transmitted bytes (high-level MPDUs)
	u64		tx_num_bytes_total;			///< Total # of transmitted bytes (high-level MPDUs)
	u32		rx_num_packets;				///< # of successfully received packets (de-duplicated)
	u32		tx_num_packets_success;		///< # of successfully transmitted packets (high-level MPDUs)
	u32		tx_num_packets_total;		///< Total # of transmitted packets (high-level MPDUs)
	u32		tx_num_packets_low;			///< # of low-level transmitted frames (including retransmissions)
} frame_statistics_txrx;


/**
 * @brief Statistics Structure
 *
 * This struct contains statistics about the communications link.
 * Additionally, statistics can be decoupled from station_info
 * structs entirely to enable promiscuous statistics about
 * unassociated devices seen in the network.
 */
#define MY_STATISTICS_TXRX_COMMON_FIELDS                                                                 \
		u8                      addr[6];                        /* HW Address */ 						 \
		u8                      is_associated;                  /* Is this device associated with me? */ \
		u8                      padding;                                                                 \
		frame_statistics_txrx	data;                           /* Statistics about data types */        \
		frame_statistics_txrx	mgmt;                           /* Statistics about data types */

typedef struct{
	MY_STATISTICS_TXRX_COMMON_FIELDS
	u64     latest_txrx_timestamp;                              ///< Timestamp of the last frame reception
} statistics_txrx;
CASSERT(sizeof(statistics_txrx) == 96, statistics_txrx_alignment_check);


/**
 * @brief Base Statistics Structure
 *
 * This struct is a modification of the statistics_txrx struct that eliminates
 * pointers to other data.
 */
typedef struct{
	MY_STATISTICS_TXRX_COMMON_FIELDS
} statistics_txrx_base;


/**
 * @brief Reception Information Structure
 *
 * This structure contains information about the previous reception. It is used in high
 * level MACs to de-duplicate incoming receptions.
 */
typedef struct{
	u16     last_seq;       ///< Sequence number of the last MPDU reception
	char    last_power;     ///< Power of last frame reception (in dBm)
	u8      last_rate;      ///< Rate of last MPDU reception
} rx_info;


/**
 * @brief Rate Selection Information
 *
 * This structure contains information about the rate selection scheme.
 */
typedef struct{
	u16 rate_selection_scheme;
} rate_selection_info;

#define RATE_SELECTION_SCHEME_STATIC	         0


/**
 * @brief Station Information Structure
 *
 * This struct contains information about associated stations (or, in the
 * case of a station, information about the associated access point).
 */
#define STATION_INFO_HOSTNAME_MAXLEN             19

#define MY_STATION_INFO_COMMON_FIELDS 								   									\
		u8          addr[6]; 									/* HW Address */ 						\
		u16         AID; 										/* Association ID */	 				\
		char		hostname[STATION_INFO_HOSTNAME_MAXLEN+1]; 	/* Hostname from DHCP requests */		\
		u32			flags;										/* 1-bit flags */						\
		u64         latest_activity_timestamp;                  /* Timestamp of most recent activity */ \
		rx_info     rx; 										/* Reception Information Structure */	\
		tx_params   tx;											/* Transmission Parameters Structure */

typedef struct{
	MY_STATION_INFO_COMMON_FIELDS
	statistics_txrx* stats;									///< Statistics Information Structure
															///< @note This is a pointer to the statistics structure
                            								///< because statistics can survive outside of the context
                            								///< of associated station_info structs.
	rate_selection_info rate_info;

} station_info;


/**
 * @brief Base Station Information Structure
 *
 * This struct is a modification of the station_info struct that eliminates
 * pointers to other data.
 */
typedef struct{
	MY_STATION_INFO_COMMON_FIELDS
} station_info_base;


#define STATION_INFO_FLAG_DISABLE_ASSOC_CHECK    0x0001         ///< Mask for flag in station_info -- disable association check
#define STATION_INFO_FLAG_DOZE                   0x0002         ///< Mask to sleeping stations (if STA supports PS)
#define STATION_INFO_DO_NOT_REMOVE               0x80000000     ///< Mask to not remove station info from association table




//////////// Global Constants ////////////

extern const  u8 bcast_addr[6];



//////////// Initialization Functions ////////////
void               wlan_mac_high_init();
void               wlan_mac_high_heap_init();

int                         wlan_mac_high_interrupt_init();
inline int                  wlan_mac_high_interrupt_restore_state(interrupt_state_t new_interrupt_state);
inline interrupt_state_t     wlan_mac_high_interrupt_stop();

void               wlan_mac_high_uart_rx_handler(void *CallBackRef, unsigned int EventData);
void               wlan_mac_high_gpio_handler(void *InstancePtr);

dl_entry*          wlan_mac_high_find_station_info_AID(dl_list* list, u32 aid);
dl_entry*          wlan_mac_high_find_station_info_ADDR(dl_list* list, u8* addr);
dl_entry*          wlan_mac_high_find_statistics_ADDR(dl_list* list, u8* addr);

u32                wlan_mac_high_get_user_io_state();

void               wlan_mac_high_set_pb_u_callback(function_ptr_t callback);
void               wlan_mac_high_set_pb_m_callback(function_ptr_t callback);
void               wlan_mac_high_set_pb_d_callback(function_ptr_t callback);
void               wlan_mac_high_set_uart_rx_callback(function_ptr_t callback);
void               wlan_mac_high_set_mpdu_tx_done_callback(function_ptr_t callback);
void               wlan_mac_high_set_mpdu_rx_callback(function_ptr_t callback);
void               wlan_mac_high_set_poll_tx_queues_callback(function_ptr_t callback);
void               wlan_mac_high_set_mpdu_dequeue_callback(function_ptr_t callback);

u64                get_usec_timestamp();
void               usleep(u64 delay);

void*              wlan_mac_high_malloc(u32 size);
void*              wlan_mac_high_calloc(u32 size);
void*              wlan_mac_high_realloc(void* addr, u32 size);
void               wlan_mac_high_free(void* addr);
void               wlan_mac_high_display_mallinfo();

void               wlan_mac_high_enable_hex_pwm();
void               wlan_mac_high_disable_hex_pwm();
void               wlan_mac_high_write_hex_display(u8 val);
void               wlan_mac_high_set_node_error_status(u8 status);
void               wlan_mac_high_blink_hex_display(u32 num_blinks, u32 blink_time);

int                wlan_mac_high_memory_test();
int                wlan_mac_high_right_shift_test();

int                wlan_mac_high_cdma_start_transfer(void* dest, void* src, u32 size);
void               wlan_mac_high_cdma_finish_transfer();

void               wlan_mac_high_mpdu_transmit(tx_queue_element* packet, int tx_pkt_buf);

wlan_mac_hw_info*  wlan_mac_high_get_hw_info();
u8*                wlan_mac_high_get_eeprom_mac_addr();
inline u64         wlan_mac_high_get_unique_seq();

u8                 wlan_mac_high_valid_tagged_rate(u8 rate);
void               wlan_mac_high_tagged_rate_to_readable_rate(u8 rate, char* str);

void               wlan_mac_high_setup_tx_header( mac_header_80211_common * header, u8 * addr_1, u8 * addr_3 );
void               wlan_mac_high_setup_tx_frame_info( mac_header_80211_common * header, tx_queue_element * curr_tx_queue_element, u32 tx_length, u8 flags, u8 QID );

void               wlan_mac_high_ipc_rx();
void               wlan_mac_high_process_ipc_msg(wlan_ipc_msg* msg);
void               wlan_mac_high_set_srand( unsigned int seed );
void               wlan_mac_high_set_channel( unsigned int mac_channel );
void               wlan_mac_high_set_rx_ant_mode( u8 ant_mode );
void               wlan_mac_high_set_tx_ctrl_pow( s8 pow );
void               wlan_mac_high_set_rx_filter_mode( u32 filter_mode );
int                wlan_mac_high_write_low_mem( u32 num_words, u32* payload );
int                wlan_mac_high_read_low_mem( u32 num_words, u32 baseaddr, u32* payload );
int                wlan_mac_high_read_low_param( u32 param_id, u32* size, u32* payload );
void               wlan_mac_high_set_dsss( unsigned int dsss_value );
void               wlan_mac_high_set_timestamp( u64 timestamp );
void               wlan_mac_high_set_timestamp_delta( s64 timestamp );
void               wlan_mac_high_request_low_state();
int                wlan_mac_high_is_cpu_low_initialized();
int                wlan_mac_high_is_ready_for_tx();
int                wlan_mac_high_lock_new_tx_packet_buffer();
int                wlan_mac_high_release_tx_packet_buffer(int pkt_buf);
u8                 wlan_mac_high_pkt_type(void* mpdu, u16 length);

inline void        wlan_mac_high_set_debug_gpio(u8 val);
inline void        wlan_mac_high_clear_debug_gpio(u8 val);

int                str2num(char* str);
u8                 sevenSegmentMap(u8 hex_value);

station_info*      wlan_mac_high_add_association(dl_list* assoc_tbl, dl_list* stat_tbl, u8* addr, u16 requested_AID);
int                wlan_mac_high_remove_association(dl_list* assoc_tbl, dl_list* stat_tbl, u8* addr);
u8                 wlan_mac_high_is_valid_association(dl_list* assoc_tbl, station_info* station);
u32                wlan_mac_high_set_max_associations(u32 num_associations);
u32                wlan_mac_high_get_max_associations();

statistics_txrx*   wlan_mac_high_add_statistics(dl_list* stat_tbl, station_info* station, u8* addr);
void               wlan_mac_high_reset_statistics(dl_list* stat_tbl);
void               wlan_mac_high_update_tx_statistics(tx_frame_info* tx_mpdu, station_info* station);

void               wlan_mac_high_print_hw_info( wlan_mac_hw_info * info );
void               wlan_mac_high_print_associations(dl_list* assoc_tbl);


// Common functions that must be implemented by users of the framework
dl_list *          get_statistics();
dl_list *          get_station_info_list();
u8      *          get_wlan_mac_addr();

#endif /* WLAN_MAC_HIGH_H_ */
