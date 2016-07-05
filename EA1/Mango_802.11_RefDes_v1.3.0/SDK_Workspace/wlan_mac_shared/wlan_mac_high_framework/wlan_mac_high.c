/** @file wlan_mac_high.c
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

/***************************** Include Files *********************************/

//Xilinx Includes
#include "stdlib.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xil_exception.h"
#include "xintc.h"
#include "xuartlite.h"
#include "xaxicdma.h"
#include "malloc.h"

//WARP Includes
#include "w3_userio.h"
#include "wlan_mac_dl_list.h"
#include "wlan_mac_ipc_util.h"
#include "wlan_mac_802_11_defs.h"
#include "wlan_mac_high.h"
#include "wlan_mac_packet_types.h"
#include "wlan_mac_queue.h"
#include "wlan_mac_eth_util.h"
#include "wlan_mac_ltg.h"
#include "wlan_mac_event_log.h"
#include "wlan_mac_schedule.h"
#include "wlan_mac_addr_filter.h"
#include "wlan_mac_bss_info.h"
#include "wlan_exp_common.h"
#include "wlan_exp_node.h"

/*********************** Global Variable Definitions *************************/

//These variables are defined by the linker at compile time
extern int __data_start; ///< Start address of the data secion
extern int __data_end;	 ///< End address of the data section
extern int __bss_start;	 ///< Start address of the bss section
extern int __bss_end;	 ///< End address of the bss section
extern int _heap_start;	 ///< Start address of the heap
extern int _HEAP_SIZE;	 ///< Size of the heap
extern int _stack_end;	 ///< Start of the stack (stack counts backwards)
extern int __stack;	 	 ///< End of the stack


// Variables implemented in child classes (ie AP, STA, etc)
extern tx_params default_unicast_mgmt_tx_params;
extern tx_params default_unicast_data_tx_params;
extern tx_params default_multicast_mgmt_tx_params;
extern tx_params default_multicast_data_tx_params;



/*************************** Variable Definitions ****************************/

// Constants
const  u8                    bcast_addr[6]        = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

// Associations
volatile static u32          max_num_associations = WLAN_MAC_HIGH_MAX_ASSOCIATONS;

// HW structures
static XGpio                 Gpio_timestamp;               ///< GPIO instance used for 64-bit usec timestamp
static XGpio                 Gpio;                         ///< General-purpose GPIO instance
XIntc       	             InterruptController;          ///< Interrupt Controller instance
XUartLite                    UartLite;                     ///< UART Device instance
XAxiCdma                     cdma_inst;                    ///< Central DMA instance

// UART interface
u8                           uart_rx_buffer[UART_BUFFER_SIZE];       ///< Buffer for received byte from UART

// Callback function pointers
volatile function_ptr_t      pb_u_callback;                ///< User callback for "up" pushbutton
volatile function_ptr_t      pb_m_callback;                ///< User callback for "middle" pushbutton
volatile function_ptr_t      pb_d_callback;                ///< User callback for "down" pushbutton
volatile function_ptr_t      uart_callback;                ///< User callback for UART reception
volatile function_ptr_t      mpdu_tx_done_callback;        ///< User callback for lower-level message that MPDU transmission is complete
volatile function_ptr_t      mpdu_rx_callback;             ///< User callback for lower-level message that MPDU reception is ready for processing
volatile function_ptr_t      tx_poll_callback;             ///< User callback when higher-level framework is ready to send a packet to low
volatile function_ptr_t      mpdu_tx_dequeue_callback;     ///< User callback for higher-level framework dequeuing a packet

// Node information
wlan_mac_hw_info             hw_info;                      ///< Information about hardware
volatile u8                  dram_present;                 ///< Indication variable for whether DRAM SODIMM is present on this hardware

// Status information
volatile static u32          cpu_low_status;               ///< Tracking variable for lower-level CPU status

// CPU Low Register Read Buffer
volatile static u32*	     cpu_low_reg_read_buffer;
volatile static u8		     cpu_low_reg_read_buffer_status;

#define CPU_LOW_REG_READ_BUFFER_STATUS_READY               1
#define CPU_LOW_REG_READ_BUFFER_STATUS_NOT_READY           0

// CPU Low Parameter Read Buffer
volatile static u32*	     cpu_low_param_read_buffer;
volatile static u32          cpu_low_param_read_buffer_size;
volatile static u8		     cpu_low_param_read_buffer_status;

#define CPU_LOW_PARAM_READ_BUFFER_STATUS_READY             1
#define CPU_LOW_PARAM_READ_BUFFER_STATUS_NOT_READY         0

// Interrupt State
volatile static interrupt_state_t interrupt_state;

// Debug GPIO State
volatile static u8           debug_gpio_state;             ///< Current state of debug GPIO pins

// IPC variables
wlan_ipc_msg                 ipc_msg_from_low;							            ///< IPC message from lower-level
u32                          ipc_msg_from_low_payload[IPC_BUFFER_MAX_NUM_WORDS];	///< Buffer space for IPC message from lower-level

// Memory Allocation Debugging
volatile static u32          num_malloc;                   ///< Tracking variable for number of times malloc has been called
volatile static u32          num_free;                     ///< Tracking variable for number of times free has been called
volatile static u32          num_realloc;                  ///< Tracking variable for number of times realloc has been called

// Statistics Flags
volatile u8                  promiscuous_stats_enabled;    ///< Are promiscuous statistics collected (1 = Yes / 0 = No)

// Receive Antenna mode tracker
volatile u8                  rx_ant_mode_tracker = 0;      ///< Tracking variable for RX Antenna mode for CPU Low

// Unique transmit sequence number
volatile static u64	         unique_seq;

// Tx Packet Buffer Busy State
volatile static u8           tx_pkt_buf_busy_state;


/*************************** Functions Prototypes ****************************/

#ifdef _DEBUG_
void wlan_mac_high_copy_comparison();
#endif


// Functions implemented in AP, STA, etc
dl_list * get_station_info_list();



/******************************** Functions **********************************/

/**
 * @brief Initialize Heap and Data Sections
 *
 * Dynamic memory allocation through malloc uses metadata in the data section
 * of the elf binary. This metadata is not reset upon software reset (i.e., when a
 * user presses the reset button on the hardware). This will cause failures on
 * subsequent boots because this metadata has not be reset back to its original
 * state at the first boot.
 *
 * This function backs up the original data section to a dedicated BRAM, so it can
 * be copied back on subsequent soft resets.
 *
 * @param None
 * @return None
 *
 * @note This function should be the first thing called after boot. If it is
 * called after other parts have the code have started dynamic memory access,
 * there will be unpredictable results on software reset.
 */
void wlan_mac_high_heap_init(){
	u32 data_size;
	volatile u32* identifier;

	data_size = 4*(&__data_end - &__data_start);
	identifier = (u32*)INIT_DATA_BASEADDR;

	//Zero out the heap
	bzero((void*)&_heap_start, (int)&_HEAP_SIZE);

	//Zero out the bss
	bzero((void*)&__bss_start, 4*(&__bss_end - &__bss_start));

#ifdef INIT_DATA_BASEADDR
	if(*identifier == INIT_DATA_DOTDATA_IDENTIFIER){
		//This program has run before. We should copy the .data out of the INIT_DATA memory.
		if(data_size <= INIT_DATA_DOTDATA_SIZE){
			memcpy((void*)&__data_start, (void*)INIT_DATA_DOTDATA_START, data_size);
		}

	} else {
		//This is the first time this program has been run.
		if(data_size <= INIT_DATA_DOTDATA_SIZE){
			*identifier = INIT_DATA_DOTDATA_IDENTIFIER;
			memcpy((void*)INIT_DATA_DOTDATA_START, (void*)&__data_start, data_size);
		}

	}
#endif
}



/**
 * @brief Initialize MAC High Framework
 *
 * This function initializes the MAC High Framework by setting
 * up the hardware and other subsystems in the framework.
 *
 * @param None
 * @return None
 */
void wlan_mac_high_init(){
	int            Status;
    u32            i;
	u64            timestamp;
	u32            log_size;
	XAxiCdma_Config *cdma_cfg_ptr;


	// Check that right shift works correctly
	//   Issue with -Os in Xilinx SDK 14.7
	if (wlan_mac_high_right_shift_test() != 0) {
		wlan_mac_high_set_node_error_status(0);
		wlan_mac_high_blink_hex_display(0, 250000);
	}

	// Sanity check memory map of aux. BRAM and DRAM
	//Aux. BRAM Check
	Status = (AUX_BRAM_BASE <= TX_QUEUE_DL_ENTRY_MEM_BASE) && (TX_QUEUE_DL_ENTRY_MEM_HIGH < BSS_INFO_DL_ENTRY_MEM_BASE) && (BSS_INFO_DL_ENTRY_MEM_HIGH < ETH_TX_BD_BASE) && (ETH_TX_BD_HIGH < ETH_RX_BD_BASE) && (ETH_RX_BD_HIGH <= AUX_BRAM_HIGH);
	if(Status != 1){
		xil_printf("Error: Overlap detected in Aux. BRAM. Check address assignments\n");
	}

	//DRAM Check
	Status = (DRAM_BASE <= TX_QUEUE_BUFFER_BASE) && (TX_QUEUE_BUFFER_HIGH < BSS_INFO_BUFFER_BASE) && (BSS_INFO_BUFFER_HIGH < USER_SCRATCH_BASE) && (USER_SCRATCH_HIGH < EVENT_LOG_BASE) && (EVENT_LOG_HIGH <= DRAM_HIGH);
	if(Status != 1){
		xil_printf("Error: Overlap detected in DRAM. Check address assignments\n");
	}


	// ***************************************************
	// Initialize the utility library
	// ***************************************************
	wlan_lib_init();

	mtshr(&__stack);
	mtslr(&_stack_end);

	// ***************************************************
    // Initialize callbacks and global state variables
	// ***************************************************
	pb_u_callback            = (function_ptr_t)nullCallback;
	pb_m_callback            = (function_ptr_t)nullCallback;
	pb_d_callback            = (function_ptr_t)nullCallback;
	uart_callback            = (function_ptr_t)nullCallback;
	mpdu_rx_callback         = (function_ptr_t)nullCallback;
	mpdu_tx_done_callback    = (function_ptr_t)nullCallback;
	tx_poll_callback	     = (function_ptr_t)nullCallback;
	mpdu_tx_dequeue_callback = (function_ptr_t)nullCallback;

	wlan_lib_mailbox_set_rx_callback((function_ptr_t)wlan_mac_high_ipc_rx);

	interrupt_state = INTERRUPTS_DISABLED;

	num_malloc  = 0;
	num_realloc = 0;
	num_free    = 0;

	cpu_low_reg_read_buffer        = NULL;
	cpu_low_param_read_buffer      = NULL;
	cpu_low_param_read_buffer_size = 0;

	// Enable promiscuous statistics by default
	promiscuous_stats_enabled = 1;

	unique_seq = 0;

	tx_pkt_buf_busy_state = 0;

	// ***************************************************
	// Initialize Transmit Packet Buffers
	// ***************************************************
	for(i=0;i < NUM_TX_PKT_BUFS; i++){
		unlock_pkt_buf_tx(i);
	}


	// ***************************************************
	// Initialize CDMA, GPIO, and UART drivers
	// ***************************************************

	// Initialize the central DMA (CDMA) driver
	cdma_cfg_ptr = XAxiCdma_LookupConfig(XPAR_AXI_CDMA_0_DEVICE_ID);
	Status = XAxiCdma_CfgInitialize(&cdma_inst, cdma_cfg_ptr, cdma_cfg_ptr->BaseAddress);
	if (Status != XST_SUCCESS) {
		warp_printf(PL_ERROR,"Error initializing CDMA: %d\n", Status);
	}
	XAxiCdma_IntrDisable(&cdma_inst, XAXICDMA_XR_IRQ_ALL_MASK);

	// Initialize the GPIO driver
	Status = XGpio_Initialize(&Gpio, GPIO_DEVICE_ID);

	// Initialize GPIO timestamp
	XGpio_Initialize(&Gpio_timestamp, TIMESTAMP_GPIO_DEVICE_ID);
	XGpio_SetDataDirection(&Gpio_timestamp, TIMESTAMP_GPIO_LSB_CHAN, 0xFFFFFFFF);
	XGpio_SetDataDirection(&Gpio_timestamp, TIMESTAMP_GPIO_MSB_CHAN, 0xFFFFFFFF);

	if (Status != XST_SUCCESS) {
		warp_printf(PL_ERROR, "Error initializing GPIO\n");
		return;
	}
	// Set direction of GPIO channels
	XGpio_SetDataDirection(&Gpio, GPIO_INPUT_CHANNEL, 0xFFFFFFFF);
	XGpio_SetDataDirection(&Gpio, GPIO_OUTPUT_CHANNEL, 0);

	// Clear any existing state in debug GPIO
	wlan_mac_high_clear_debug_gpio(0xFF);

	// Initialize the UART driver
	Status = XUartLite_Initialize(&UartLite, UARTLITE_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		warp_printf(PL_ERROR, "Error initializing XUartLite\n");
		return;
	}

	// Test to see if DRAM SODIMM is connected to board
	dram_present = 0;
	timestamp = get_usec_timestamp();

	while((get_usec_timestamp() - timestamp) < 100000){
		if((XGpio_DiscreteRead(&Gpio, GPIO_INPUT_CHANNEL)&GPIO_MASK_DRAM_INIT_DONE)){
			xil_printf("------------------------\nDRAM SODIMM Detected\n");
			if(wlan_mac_high_memory_test()==0){
				dram_present = 1;
			} else {
				dram_present = 0;
			}
			break;
		}
	}


	// ***************************************************
	// Initialize various subsystems in the MAC High Framework
	// ***************************************************
	queue_init(dram_present);

	if( dram_present ) {
		// The event_list lives in DRAM immediately following the queue payloads.
		if(MAX_EVENT_LOG == -1){
			log_size = EVENT_LOG_SIZE;
		} else {
			log_size = min(EVENT_LOG_SIZE, MAX_EVENT_LOG );
		}

		event_log_init( (void*)EVENT_LOG_BASE, log_size );

	} else {
		// No DRAM, so the log has nowhere to be stored.
		log_size = 0;
	}

	bss_info_init(dram_present);
	wlan_eth_init();
	wlan_mac_schedule_init();
	wlan_mac_ltg_sched_init();
	wlan_mac_addr_filter_init();

	//Create IPC message to receive into
	ipc_msg_from_low.payload_ptr = &(ipc_msg_from_low_payload[0]);
}



/**
 * @brief Initialize MAC High Framework's Interrupts
 *
 * This function initializes sets up the interrupt subsystem
 * of the MAC High Framework.
 *
 * @param None
 * @return int
 *      - nonzero if error
 */
int wlan_mac_high_interrupt_init(){
	int Result;

	// ***************************************************
	// Initialize XIntc
	// ***************************************************
	Result = XIntc_Initialize(&InterruptController, INTC_DEVICE_ID);
	if (Result != XST_SUCCESS) {
		return Result;
	}

	// ***************************************************
	// Connect interrupt devices "owned" by wlan_mac_high
	// ***************************************************
	Result = XIntc_Connect(&InterruptController, INTC_GPIO_INTERRUPT_ID, (XInterruptHandler)wlan_mac_high_gpio_handler, &Gpio);
	if (Result != XST_SUCCESS) {
		warp_printf(PL_ERROR,"Failed to connect GPIO to XIntc\n");
		return Result;
	}
	XIntc_Enable(&InterruptController, INTC_GPIO_INTERRUPT_ID);
	XGpio_InterruptEnable(&Gpio, GPIO_INPUT_INTERRUPT);
	XGpio_InterruptGlobalEnable(&Gpio);

	Result = XIntc_Connect(&InterruptController, UARTLITE_INT_IRQ_ID, (XInterruptHandler)XUartLite_InterruptHandler, &UartLite);
	if (Result != XST_SUCCESS) {
		warp_printf(PL_ERROR,"Failed to connect XUartLite to XIntc\n");
		return Result;
	}
	XIntc_Enable(&InterruptController, UARTLITE_INT_IRQ_ID);
	XUartLite_SetRecvHandler(&UartLite, wlan_mac_high_uart_rx_handler, &UartLite);
	XUartLite_EnableInterrupt(&UartLite);

	// ***************************************************
	// Connect interrupt devices in other subsystems
	// ***************************************************
	Result = wlan_mac_schedule_setup_interrupt(&InterruptController);
	if (Result != XST_SUCCESS) {
		warp_printf(PL_ERROR,"Failed to set up scheduler interrupt\n");
		return -1;
	}

	Result = wlan_lib_mailbox_setup_interrupt(&InterruptController);
	if (Result != XST_SUCCESS) {
		warp_printf(PL_ERROR,"Failed to set up wlan_lib mailbox interrupt\n");
		return -1;
	}

	Result = wlan_eth_setup_interrupt(&InterruptController);
	if (Result != XST_SUCCESS) {
		warp_printf(PL_ERROR,"Failed to set up Ethernet interrupt\n");
		return Result;
	}

	// ***************************************************
	// Enable MicroBlaze exceptions
	// ***************************************************
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XIntc_InterruptHandler, &InterruptController);
	Xil_ExceptionEnable();


	// Finish setting up any subsystems that were waiting on interrupts to be configured
	bss_info_init_finish();


	return 0;
}



/**
 * @brief Restore the state of the interrupt controller
 *
 * This function starts the interrupt controller, allowing the executing code
 * to be interrupted.
 *
 * @param interrupt_state_t new_interrupt_state
 * 		- State to return interrupts. Typically, this argument is the output of a previous
 * 		call to wlan_mac_high_interrupt_stop()
 * @return int
 *      - nonzero if error
 */
inline int wlan_mac_high_interrupt_restore_state(interrupt_state_t new_interrupt_state){
	interrupt_state = new_interrupt_state;
	if(interrupt_state == INTERRUPTS_ENABLED){
		if(InterruptController.IsReady && InterruptController.IsStarted == 0){
			return XIntc_Start(&InterruptController, XIN_REAL_MODE);
		} else {
			return -1;
		}
	} else {
		return 0;
	}
}



/**
 * @brief Stop the interrupt controller
 *
 * This function stops the interrupt controller, effectively pausing interrupts. This can
 * be used alongside wlan_mac_high_interrupt_start() to wrap code that is not interrupt-safe.
 *
 * @param None
 * @return interrupt_state_t
 * 		- INTERRUPTS_ENABLED if interrupts were enabled at the time this function was called
 * 		- INTERRUPTS_DISABLED if interrupts were disabled at the time this function was called
 *
 * @note Interrupts that occur while the interrupt controller is off will be executed once it is
 * turned back on. They will not be "lost" as the interrupt inputs to the controller will remain
 * high.
 */
inline interrupt_state_t wlan_mac_high_interrupt_stop(){
	interrupt_state_t curr_state = interrupt_state;
	if(InterruptController.IsReady && InterruptController.IsStarted) XIntc_Stop(&InterruptController);
	interrupt_state = INTERRUPTS_DISABLED;
	return curr_state;
}



/**
 * @brief UART Receive Interrupt Handler
 *
 * This function is the interrupt handler for UART receptions. It, in turn,
 * will execute a callback that the user has previously registered.
 *
 * @param void* CallBackRef
 *  - Argument supplied by the XUartLite driver. Unused in this application.
 * @param unsigned int EventData
 *  - Argument supplied by the XUartLite driver. Unused in this application.
 * @return None
 *
 * @see wlan_mac_high_set_uart_rx_callback()
 */
void wlan_mac_high_uart_rx_handler(void* CallBackRef, unsigned int EventData){
#ifdef _ISR_PERF_MON_EN_
	wlan_mac_high_set_debug_gpio(ISR_PERF_MON_GPIO_MASK);
#endif
	XUartLite_Recv(&UartLite, uart_rx_buffer, UART_BUFFER_SIZE);
	uart_callback(uart_rx_buffer[0]);
#ifdef _ISR_PERF_MON_EN_
	wlan_mac_high_clear_debug_gpio(ISR_PERF_MON_GPIO_MASK);
#endif
}



/**
 * @brief Find Station Information within a doubly-linked list from an AID
 *
 * Given a doubly-linked list of station_info structures, this function will return
 * the pointer to a particular entry whose association ID field matches the argument
 * to this function.
 *
 * @param dl_list* list
 *  - Doubly-linked list of station_info structures
 * @param u32 aid
 *  - Association ID to search for
 * @return curr_station_info_entry*
 *  - Returns the pointer to the entry in the doubly-linked list that has the
 *    provided AID.
 *  - Returns NULL if no station_info pointer is found that matches the search
 *    criteria
 *
 */
dl_entry* wlan_mac_high_find_station_info_AID(dl_list* list, u32 aid){
	dl_entry*	curr_station_info_entry;
	station_info* curr_station_info;

	curr_station_info_entry = list->first;

	while(curr_station_info_entry != NULL){
		curr_station_info = (station_info*)(curr_station_info_entry->data);

		if(curr_station_info->AID == aid){
			return curr_station_info_entry;
		} else {
			curr_station_info_entry = dl_entry_next(curr_station_info_entry);
		}
	}

	return NULL;
}



/**
 * @brief Find Station Information within a doubly-linked list from an hardware address
 *
 * Given a doubly-linked list of station_info structures, this function will return
 * the pointer to a particular entry whose hardware address matches the argument
 * to this function.
 *
 * @param dl_list* list
 *  - Doubly-linked list of station_info structures
 * @param u8* addr
 *  - 6-byte hardware address to search for
 * @return dl_entry*
 *  - Returns the pointer to the entry in the doubly-linked list that has the
 *    provided hardware address.
 *  - Returns NULL if no station_info pointer is found that matches the search
 *    criteria
 *
 */
dl_entry* wlan_mac_high_find_station_info_ADDR(dl_list* list, u8* addr){
	dl_entry* curr_station_info_entry;
	station_info* curr_station_info;

	curr_station_info_entry = list->first;

	while(curr_station_info_entry != NULL){
		curr_station_info = (station_info*)(curr_station_info_entry->data);

		if(wlan_addr_eq(curr_station_info->addr, addr)){
			return curr_station_info_entry;
		} else {
			curr_station_info_entry = dl_entry_next(curr_station_info_entry);
		}
	}

	return NULL;
}



/**
 * @brief Find Statistics within a doubly-linked list from an hardware address
 *
 * Given a doubly-linked list of statistics structures, this function will return
 * the pointer to a particular entry whose hardware address matches the argument
 * to this function.
 *
 * @param dl_list* list
 *  - Doubly-linked list of statistics structures
 * @param u8* addr
 *  - 6-byte hardware address to search for
 * @return dl_entry*
 *  - Returns the pointer to the entry in the doubly-linked list that has the
 *    provided hardware address.
 *  - Returns NULL if no statistics pointer is found that matches the search
 *    criteria
 *
 */
dl_entry* wlan_mac_high_find_statistics_ADDR(dl_list* list, u8* addr){
	dl_entry*		 curr_statistics_entry;
	statistics_txrx* curr_statistics;

	curr_statistics_entry = list->first;

	while(curr_statistics_entry != NULL){

		curr_statistics = (statistics_txrx*)(curr_statistics_entry->data);

		if(wlan_addr_eq(curr_statistics->addr, addr)){
			//Move this statistics entry to the front of the list to increase
			//the performance of finding it again.
			//Note: this performance increase makes the basic assumption that
			//finding a MAC address in this list will be tied to wanting to find
			//it again in the future. Busy traffic will naturally float to the front
			//of the list and make them easier to find again.

			dl_entry_remove(list, curr_statistics_entry);
			dl_entry_insertBeginning(list, curr_statistics_entry);

			return curr_statistics_entry;
		} else {
			curr_statistics_entry = dl_entry_next(curr_statistics_entry);
		}
	}
	return NULL;
}



/**
 * @brief GPIO Interrupt Handler
 *
 * Handles GPIO interrupts that occur from the GPIO core's input
 * channel. Depending on the signal, this function will execute
 * one of several different user-provided callbacks.
 *
 * @param void* InstancePtr
 *  - Pointer to the GPIO instance
 * @return None
 *
 * @see wlan_mac_high_set_pb_u_callback()
 * @see wlan_mac_high_set_pb_m_callback()
 * @see wlan_mac_high_set_pb_d_callback()
 *
 */
void wlan_mac_high_gpio_handler(void *InstancePtr){
	XGpio *GpioPtr;
	u32 gpio_read;

#ifdef _ISR_PERF_MON_EN_
	wlan_mac_high_set_debug_gpio(ISR_PERF_MON_GPIO_MASK);
#endif

	GpioPtr = (XGpio *)InstancePtr;

	XGpio_InterruptDisable(GpioPtr, GPIO_INPUT_INTERRUPT);
	gpio_read = XGpio_DiscreteRead(GpioPtr, GPIO_INPUT_CHANNEL);

	if(gpio_read & GPIO_MASK_PB_U) pb_u_callback();
	if(gpio_read & GPIO_MASK_PB_M) pb_m_callback();
	if(gpio_read & GPIO_MASK_PB_D) pb_d_callback();

	(void)XGpio_InterruptClear(GpioPtr, GPIO_INPUT_INTERRUPT);
	XGpio_InterruptEnable(GpioPtr, GPIO_INPUT_INTERRUPT);

#ifdef _ISR_PERF_MON_EN_
	wlan_mac_high_clear_debug_gpio(ISR_PERF_MON_GPIO_MASK);
#endif
	return;
}

u32 wlan_mac_high_get_user_io_state(){
	return XGpio_DiscreteRead(&Gpio, GPIO_INPUT_CHANNEL);
}



/**
 * @brief Set "Up" Pushbutton Callback
 *
 * Tells the framework which function should be called when
 * the "up" button in the User I/O section of the hardware
 * is pressed.
 *
 * @param function_ptr_t callback
 *  - Pointer to callback function
 * @return None
 *
 */
void wlan_mac_high_set_pb_u_callback(function_ptr_t callback){
	pb_u_callback = callback;
}



/**
 * @brief Set "Middle" Pushbutton Callback
 *
 * Tells the framework which function should be called when
 * the "middle" button in the User I/O section of the hardware
 * is pressed.
 *
 * @param function_ptr_t callback
 *  - Pointer to callback function
 * @return None
 *
 */
void wlan_mac_high_set_pb_m_callback(function_ptr_t callback){
	pb_m_callback = callback;
}



/**
 * @brief Set "Down" Pushbutton Callback
 *
 * Tells the framework which function should be called when
 * the "down" button in the User I/O section of the hardware
 * is pressed.
 *
 * @param function_ptr_t callback
 *  - Pointer to callback function
 * @return None
 *
 */
void wlan_mac_high_set_pb_d_callback(function_ptr_t callback){
	pb_d_callback = callback;
}



/**
 * @brief Set UART Reception Callback
 *
 * Tells the framework which function should be called when
 * a byte is received from UART.
 *
 * @param function_ptr_t callback
 *  - Pointer to callback function
 * @return None
 *
 */
void wlan_mac_high_set_uart_rx_callback(function_ptr_t callback){
	// xil_printf("assigning uart_callback = 0x%08x\n", (u32)uart_callback);
	uart_callback = callback;
}



/**
 * @brief Set MPDU Transmission Complete Callback
 *
 * Tells the framework which function should be called when
 * the lower-level CPU confirms that an MPDU has been transmitted.
 *
 * @param function_ptr_t callback
 *  - Pointer to callback function
 * @return None
 *
 * @note This callback is not executed for individual retransmissions.
 * It is instead only executed after a chain of retransmissions is complete
 * either through the reception of an ACK or the number of retransmissions
 * reaching the maximum number of retries specified by the MPDU's
 * tx_frame_info metadata.
 *
 */
void wlan_mac_high_set_mpdu_tx_done_callback(function_ptr_t callback){
	mpdu_tx_done_callback = callback;
}



/**
 * @brief Set MPDU Reception Callback
 *
 * Tells the framework which function should be called when
 * the lower-level CPU receives a valid MPDU frame.
 *
 * @param function_ptr_t callback
 *  - Pointer to callback function
 * @return None
 *
 */
void wlan_mac_high_set_mpdu_rx_callback(function_ptr_t callback){
	mpdu_rx_callback = callback;
}



/**
 * @brief Set Poll Tx Queue Callback
 *
 * Tells the framework which function should be called whenever
 * the framework knows that CPU_LOW is ready to send a new packet.
 *
 * @param function_ptr_t callback
 *  - Pointer to callback function
 * @return None
 *
 */
void wlan_mac_high_set_poll_tx_queues_callback(function_ptr_t callback){
	tx_poll_callback = callback;
}


/**
 * @brief Set MPDU Dequeue Callback
 *
 * Tells the framework which function should be called when
 * a packet is dequeued and about to be passed to the
 * lower-level CPU.
 *
 * @param function_ptr_t callback
 *  - Pointer to callback function
 * @return None
 *
 */
void wlan_mac_high_set_mpdu_dequeue_callback(function_ptr_t callback){
	mpdu_tx_dequeue_callback = callback;
}



/**
 * @brief Get Microsecond Counter Timestamp
 *
 * The Reference Design includes a 64-bit counter that increments with
 * every microsecond. This function returns this value and is used
 * throughout the framework as a timestamp.
 *
 * @param None
 * @return u64
 *  - Current number of microseconds that have elapsed since the hardware
 *  has booted.
 *
 */
u64 get_usec_timestamp(){
	u32 timestamp_high_u32;
	u32 timestamp_low_u32;
	u64 timestamp_u64;

	timestamp_high_u32 = XGpio_DiscreteRead(&Gpio_timestamp,TIMESTAMP_GPIO_MSB_CHAN);
	timestamp_low_u32  = XGpio_DiscreteRead(&Gpio_timestamp,TIMESTAMP_GPIO_LSB_CHAN);

	//Catch very rare race when 32-LSB of 64-bit value wraps between the two 32-bit reads
	if( (timestamp_high_u32 & 0x1) != (XGpio_DiscreteRead(&Gpio_timestamp,TIMESTAMP_GPIO_MSB_CHAN) & 0x1) ) {
		//32-LSB wrapped - start over
		timestamp_high_u32 = XGpio_DiscreteRead(&Gpio_timestamp,TIMESTAMP_GPIO_MSB_CHAN);
		timestamp_low_u32  = XGpio_DiscreteRead(&Gpio_timestamp,TIMESTAMP_GPIO_LSB_CHAN);
	}

	timestamp_u64      = (((u64)timestamp_high_u32)<<32) + ((u64)timestamp_low_u32);

	return timestamp_u64;
}



/**
 * @brief Display Memory Allocation Information
 *
 * This function is a wrapper around a call to mallinfo(). It prints
 * the information returned by mallinfo() to aid in the debugging of
 * memory leaks and other dynamic memory allocation issues.
 *
 * @param None
 * @return None
 *
 */
void wlan_mac_high_display_mallinfo(){
	struct mallinfo mi;
	mi = mallinfo();

	xil_printf("\n");
	xil_printf("--- Malloc Info ---\n");
	xil_printf("Summary:\n");
	xil_printf("   num_malloc:              %d\n", num_malloc);
	xil_printf("   num_realloc:             %d\n", num_realloc);
	xil_printf("   num_free:                %d\n", num_free);
	xil_printf("   num_malloc-num_free:     %d\n", (int)num_malloc - (int)num_free);
	xil_printf("   System:                  %d bytes\n", mi.arena);
	xil_printf("   Total Allocated Space:   %d bytes\n", mi.uordblks);
	xil_printf("   Total Free Space:        %d bytes\n", mi.fordblks);
#ifdef _DEBUG_
	xil_printf("Details:\n");
	xil_printf("   arena:                   %d\n", mi.arena);
	xil_printf("   ordblks:                 %d\n", mi.ordblks);
	xil_printf("   smblks:                  %d\n", mi.smblks);
	xil_printf("   hblks:                   %d\n", mi.hblks);
	xil_printf("   hblkhd:                  %d\n", mi.hblkhd);
	xil_printf("   usmblks:                 %d\n", mi.usmblks);
	xil_printf("   fsmblks:                 %d\n", mi.fsmblks);
	xil_printf("   uordblks:                %d\n", mi.uordblks);
	xil_printf("   fordblks:                %d\n", mi.fordblks);
	xil_printf("   keepcost:                %d\n", mi.keepcost);
#endif
}



/**
 * @brief Dynamically Allocate Memory
 *
 * This function wraps malloc() and uses its same API.
 *
 * @param u32 size
 *  - Number of bytes that should be allocated
 * @return void*
 *  - Memory address of allocation if the allocation was successful
 *  - NULL if the allocation was unsuccessful
 *
 * @note The purpose of this function is to funnel all memory allocations through one place in
 * code to enable easier debugging of memory leaks when they occur. This function also updates
 * a variable maintained by the framework to track the number of memory allocations and prints
 * this value, along with the other data from wlan_mac_high_display_mallinfo() in the event that
 * malloc() fails to allocate the requested size.
 *
 */
void* wlan_mac_high_malloc(u32 size){
	void* return_value;
	return_value = malloc(size);

	if(return_value == NULL){
		xil_printf("malloc error. Try increasing heap size in linker script.\n");
		wlan_mac_high_display_mallinfo();
	} else {
#ifdef _DEBUG_
		xil_printf("MALLOC - 0x%08x    %d\n", return_value, size);
#endif
		num_malloc++;
	}
	return return_value;
}



/**
 * @brief Dynamically Allocate and Initialize Memory
 *
 * This function wraps wlan_mac_high_malloc() and uses its same API. If successfully allocated,
 * this function will explicitly zero-initialize the allocated memory.
 *
 * @param u32 size
 *  - Number of bytes that should be allocated
 * @return void*
 *  - Memory address of allocation if the allocation was successful
 *  - NULL if the allocation was unsuccessful
 *
 * @see wlan_mac_high_malloc()
 *
 */
void* wlan_mac_high_calloc(u32 size){
	//This is just a simple wrapper around calloc to aid in debugging memory leak issues
	void* return_value;
	return_value = wlan_mac_high_malloc(size);

	if(return_value == NULL){
	} else {
		memset(return_value, 0 , size);
	}
	return return_value;
}



/**
 * @brief Dynamically Reallocate Memory
 *
 * This function wraps realloc() and uses its same API.
 *
 * @param void* addr
 *  - Address of dynamically allocated array that should be reallocated
 * @param u32 size
 *  - Number of bytes that should be allocated
 * @return void*
 *  - Memory address of allocation if the allocation was successful
 *  - NULL if the allocation was unsuccessful
 *
 * @note The purpose of this function is to funnel all memory allocations through one place in
 * code to enable easier debugging of memory leaks when they occur. This function also updates
 * a variable maintained by the framework to track the number of memory allocations and prints
 * this value, along with the other data from wlan_mac_high_display_mallinfo() in the event that
 * realloc() fails to allocate the requested size.
 *
 */
void* wlan_mac_high_realloc(void* addr, u32 size){
	void* return_value;
	return_value = realloc(addr, size);

	if(return_value == NULL){
		xil_printf("realloc error. Try increasing heap size in linker script.\n");
		wlan_mac_high_display_mallinfo();
	} else {
#ifdef _DEBUG_
		xil_printf("REALLOC - 0x%08x    %d\n", return_value, size);
#endif
		num_realloc++;
	}

	return return_value;
}



/**
 * @brief Free Dynamically Allocated Memory
 *
 * This function wraps free() and uses its same API.
 *
 * @param void* addr
 *  - Address of dynamically allocated array that should be freed
 * @return None
 *
 * @note The purpose of this function is to funnel all memory freeing through one place in
 * code to enable easier debugging of memory leaks when they occur. This function also updates
 * a variable maintained by the framework to track the number of memory frees.
 *
 */
void wlan_mac_high_free(void* addr){
#ifdef _DEBUG_
	xil_printf("FREE - 0x%08x\n", addr);
#endif
	free(addr);
	num_free++;
}



/**
 * @brief Enable the PWM functionality of the hex display
 *
 * This function will tell the User I/O to enable the PWM to blink the hex display.
 *
 * @param None
 * @return None
 *
 */
void wlan_mac_high_enable_hex_pwm(){
	userio_set_pwm_ramp_en(USERIO_BASEADDR, 1);
}



/**
 * @brief Disable the PWM functionality of the hex display
 *
 * This function will tell the User I/O to disable the PWM to blink the hex display.
 *
 * @param None
 * @return None
 *
 */
void wlan_mac_high_disable_hex_pwm(){
	userio_set_pwm_ramp_en(USERIO_BASEADDR, 0);
}



/**
 * @brief Write a Decimal Value to the Hex Display
 *
 * This function will write a decimal value to the board's two-digit hex displays.
 *
 * @param u8 val
 *  - Value to be displayed (between 0 and 99)
 * @return None
 *
 */
void wlan_mac_high_write_hex_display(u8 val){
    u32 right_dp;
    u8  left_val;
    u8  right_val;

	// Need to retain the value of the right decimal point
	right_dp = userio_read_hexdisp_right( USERIO_BASEADDR ) & W3_USERIO_HEXDISP_DP;

	userio_write_control( USERIO_BASEADDR, ( userio_read_control( USERIO_BASEADDR ) & ( ~( W3_USERIO_HEXDISP_L_MAPMODE | W3_USERIO_HEXDISP_R_MAPMODE ) ) ) );

	if ( val < 10 ) {
		left_val  = sevenSegmentMap(0);
		right_val = sevenSegmentMap(val);
	} else {
		left_val  = sevenSegmentMap(((val/10)%10));
		right_val = sevenSegmentMap((val%10));
	}

	userio_write_hexdisp_left(USERIO_BASEADDR, left_val);
	userio_write_hexdisp_right(USERIO_BASEADDR, (right_val | right_dp));
}



/**
 * @brief Set Error Status for Node
 *
 * Function will set the hex display to be "Ex", where x is the value of the
 * status error
 *
 * @param  int status
 *     - Number from 0 - 0xF to indicate status error
 * @return None
 */
void wlan_mac_high_set_node_error_status(u8 status) {
    u32 right_dp;

	// Need to retain the value of the right decimal point
	right_dp = userio_read_hexdisp_right( USERIO_BASEADDR ) & W3_USERIO_HEXDISP_DP;

	userio_write_control( USERIO_BASEADDR, ( userio_read_control( USERIO_BASEADDR ) & ( ~( W3_USERIO_HEXDISP_L_MAPMODE | W3_USERIO_HEXDISP_R_MAPMODE ) ) ) );

	userio_write_hexdisp_left(USERIO_BASEADDR,  sevenSegmentMap(0xE));
	userio_write_hexdisp_right(USERIO_BASEADDR, (sevenSegmentMap(status % 16) | right_dp));
}


/**
 * @brief Blink LEDs
 *
 * For WARP v3 Hardware, this function will blink the hex display.
 *
 * @param    num_blinks  - Number of blinks (0 means blink forever)
 *           blink_time  - Time in us between blinks
 *
 * @return	None.
 *
 * @note	None.
 *
 */
void wlan_mac_high_blink_hex_display(u32 num_blinks, u32 blink_time) {
	u32          i, j;
	u32          hw_control;
	u32          temp_control;
    u8           right_val;
    u8           left_val;

    u32          blink_time_extended;
    volatile u32 tmp_value;

    // Get left / right values
	left_val  = userio_read_hexdisp_left( USERIO_BASEADDR );
	right_val = userio_read_hexdisp_right( USERIO_BASEADDR );

	// Store the original value of what is under HW control
	hw_control   = userio_read_control(USERIO_BASEADDR);

	// Need to zero out all of the HW control of the hex displays; Change to raw hex mode
	temp_control = (hw_control & ( ~( W3_USERIO_HEXDISP_L_MAPMODE | W3_USERIO_HEXDISP_R_MAPMODE | W3_USERIO_CTRLSRC_HEXDISP_R | W3_USERIO_CTRLSRC_HEXDISP_L )));

	// Set the hex display mode to raw bits
    userio_write_control( USERIO_BASEADDR, temp_control );

    // Do we have interrupts enabled so we can use the usleep function?
	if(InterruptController.IsReady && InterruptController.IsStarted == 0){
		if ( num_blinks > 0 ) {
	        // Perform standard blink
			for( i = 0; i < num_blinks; i++ ) {
				userio_write_hexdisp_left(USERIO_BASEADDR,  (((i % 2) == 0) ? left_val  : 0x00));
				userio_write_hexdisp_right(USERIO_BASEADDR, (((i % 2) == 0) ? right_val : 0x00));
				usleep( blink_time );
			}
		} else {
			// Perform an infinite blink
			i = 0;
			while(1){
				userio_write_hexdisp_left(USERIO_BASEADDR,  (((i % 2) == 0) ? left_val  : 0x00));
				userio_write_hexdisp_right(USERIO_BASEADDR, (((i % 2) == 0) ? right_val : 0x00));
				usleep( blink_time );
				i++;
			}
		}
	} else {
		blink_time_extended = blink_time * 4;

		if ( num_blinks > 0 ) {
	        // Perform standard blink
			for( i = 0; i < num_blinks; i++ ) {
				userio_write_hexdisp_left(USERIO_BASEADDR,  (((i % 2) == 0) ? left_val  : 0x00));
				userio_write_hexdisp_right(USERIO_BASEADDR, (((i % 2) == 0) ? right_val : 0x00));
				for( j=0; j < blink_time_extended; j++){
					tmp_value = Xil_In32(0xC0000000);
					if (tmp_value == 0xDEADBEEF) {
						break;
					}
				}
			}
		} else {
			// Perform an infinite blink
			i = 0;
			while(1){
				userio_write_hexdisp_left(USERIO_BASEADDR,  (((i % 2) == 0) ? left_val  : 0x00));
				userio_write_hexdisp_right(USERIO_BASEADDR, (((i % 2) == 0) ? right_val : 0x00));
				for( j=0; j < blink_time_extended; j++){
					tmp_value = Xil_In32(0xC0000000);
					if (tmp_value == 0xDEADBEEF) {
						break;
					}
				}
				i++;
			}
		}
	}

	// Set control back to original value
    userio_write_control( USERIO_BASEADDR, hw_control );
}



/**
 * @brief Mapping of hexadecimal values to the 7-segment display
 *
 * @param  u8 hex_value
 *   - Hexadecimal value to be converted (between 0 and 15)
 * @return u8
 *   - LED map value of the 7-segment display
 */
u8   sevenSegmentMap(u8 hex_value) {
    switch(hex_value) {
        case(0x0) : return 0x3F;
        case(0x1) : return 0x06;
        case(0x2) : return 0x5B;
        case(0x3) : return 0x4F;
        case(0x4) : return 0x66;
        case(0x5) : return 0x6D;
        case(0x6) : return 0x7D;
        case(0x7) : return 0x07;
        case(0x8) : return 0x7F;
        case(0x9) : return 0x6F;

        case(0xA) : return 0x77;
        case(0xB) : return 0x7C;
        case(0xC) : return 0x39;
        case(0xD) : return 0x5E;
        case(0xE) : return 0x79;
        case(0xF) : return 0x71;
        default   : return 0x00;
    }
}



/**
 * @brief Test DDR3 SODIMM Memory Module
 *
 * This function tests the integrity of the DDR3 SODIMM module attached to the hardware
 * by performing various write and read tests. Note, this function will destory contents
 * in DRAM, so it should only be called immediately after booting.
 *
 * @param None
 * @return int
 * 	- 0 for memory test pass
 *	- -1 for memory test fail
 */
int wlan_mac_high_memory_test(){

#define READBACK_DELAY_USEC	10000

	volatile u8 i,j;

	volatile u8  test_u8;
	volatile u16 test_u16;
	volatile u32 test_u32;
	volatile u64 test_u64;

	volatile u8  readback_u8;
	volatile u16 readback_u16;
	volatile u32 readback_u32;
	volatile u64 readback_u64;

	volatile void* memory_ptr;

	for(i=0;i<6;i++){
		memory_ptr = (void*)((u8*)DRAM_BASE + (i*100000*1024));
		for(j=0;j<3;j++){
			//Test 1 byte offsets to make sure byte enables are all working
			test_u8 = rand()&0xFF;
			test_u16 = rand()&0xFFFF;
			test_u32 = rand()&0xFFFFFFFF;
			test_u64 = (((u64)rand()&0xFFFFFFFF)<<32) + ((u64)rand()&0xFFFFFFFF);

			*((u8*)memory_ptr) = test_u8;
			usleep(READBACK_DELAY_USEC);
			readback_u8 = *((u8*)memory_ptr);

			if(readback_u8!= test_u8){
				xil_printf("0x%08x: %2x = %2x\n", memory_ptr, readback_u8, test_u8);
				xil_printf("DRAM Failure: Addr: 0x%08x -- Unable to verify write of u8\n",memory_ptr);
				return -1;
			}
			*((u16*)memory_ptr) = test_u16;
			usleep(READBACK_DELAY_USEC);
			readback_u16 = *((u16*)memory_ptr);

			if(readback_u16 != test_u16){
				xil_printf("0x%08x: %4x = %4x\n", memory_ptr, readback_u16, test_u16);
				xil_printf("DRAM Failure: Addr: 0x%08x -- Unable to verify write of u16\n",memory_ptr);
				return -1;
			}
			*((u32*)memory_ptr) = test_u32;
			usleep(READBACK_DELAY_USEC);
			readback_u32 = *((u32*)memory_ptr);

			if(readback_u32 != test_u32){
				xil_printf("0x%08x: %8x = %8x\n", memory_ptr, readback_u32, test_u32);
				xil_printf("DRAM Failure: Addr: 0x%08x -- Unable to verify write of u32\n",memory_ptr);
				return -1;
			}
			*((u64*)memory_ptr) = test_u64;
			usleep(READBACK_DELAY_USEC);
			readback_u64 = *((u64*)memory_ptr);

			if(readback_u64!= test_u64){
				xil_printf("DRAM Failure: Addr: 0x%08x -- Unable to verify write of u64\n",memory_ptr);
				return -1;
			}
			memory_ptr++;
		}
	}
	return 0;
}



/**
 * @brief Test Right Shift Operator
 *
 * This function tests the compiler right shift operator.  This is due to a bug in
 * the Xilinx 14.7 toolchain when the '-Os' flag is used during compilation.  Please
 * see:  http://warpproject.org/forums/viewtopic.php?id=2472 for more information.
 *
 * @param None
 * @return int
 * 	-  0 for right shift test pass
 *	- -1 for right shift test fail
 */
u32 right_shift_test = 0xFEDCBA98;

int wlan_mac_high_right_shift_test(){
    u8 val_3, val_2, val_1, val_0;

    u32 test_val   = right_shift_test;
    u8 *test_array = (u8 *)&right_shift_test;

    val_3 = (u8)((test_val & 0xFF000000) >> 24);
    val_2 = (u8)((test_val & 0x00FF0000) >> 16);
    val_1 = (u8)((test_val & 0x0000FF00) >>  8);
    val_0 = (u8)((test_val & 0x000000FF) >>  0);

    if ((val_3 != test_array[3]) || (val_2 != test_array[2]) || (val_1 != test_array[1]) || (val_0 != test_array[0])) {
	    xil_printf("Right shift operator is not operating correctly in this toolchain.\n");
	    xil_printf("Please use Xilinx 14.4 or an optimization level other than '-Os'\n");
        xil_printf("See http://warpproject.org/forums/viewtopic.php?id=2472 for more info.\n");
        return -1;
    }

	return 0;
}



/**
 * @brief Start Central DMA Transfer
 *
 * This function wraps the XAxiCdma call for a CDMA memory transfer and mimics the well-known
 * API of memcpy(). This function does not block once the transfer is started.
 *
 * @param void* dest
 *  - Pointer to destination address where bytes should be copied
 * @param void* src
 *  - Pointer to source address from where bytes should be copied
 * @param u32 size
 *  - Number of bytes that should be copied
 * @return int
 *	- XST_SUCCESS for success of submission
 *	- XST_FAILURE for submission failure
 *	- XST_INVALID_PARAM if:
 *	 Length out of valid range [1:8M]
 *	 Or, address not aligned when DRE is not built in
 *
 *	 @note This function will block until any existing CDMA transfer is complete. It is therefore
 *	 safe to call this function successively as each call will wait on the preceeding call.
 *
 */
int wlan_mac_high_cdma_start_transfer(void* dest, void* src, u32 size){
	//This is a wrapper function around the central DMA simple transfer call. It's arguments
	//are intended to be similar to memcpy. Note: This function does not block on the transfer.
	int return_value = XST_SUCCESS;
	u8 out_of_range  = 0;


	if((u32)src > XPAR_MB_HIGH_DLMB_BRAM_CNTLR_0_BASEADDR && (u32)src < XPAR_MB_HIGH_DLMB_BRAM_CNTLR_0_HIGHADDR){
		out_of_range = 1;
	} else if((u32)src > XPAR_MB_HIGH_DLMB_BRAM_CNTLR_1_BASEADDR && (u32)src < XPAR_MB_HIGH_DLMB_BRAM_CNTLR_1_HIGHADDR){
		out_of_range = 1;
	} else if((u32)dest > XPAR_MB_HIGH_DLMB_BRAM_CNTLR_0_BASEADDR && (u32)dest < XPAR_MB_HIGH_DLMB_BRAM_CNTLR_0_HIGHADDR){
		out_of_range = 1;
	} else if((u32)dest > XPAR_MB_HIGH_DLMB_BRAM_CNTLR_1_BASEADDR && (u32)dest < XPAR_MB_HIGH_DLMB_BRAM_CNTLR_1_HIGHADDR){
		out_of_range = 1;
	}


	if(out_of_range == 0){
		wlan_mac_high_cdma_finish_transfer();
		return_value = XAxiCdma_SimpleTransfer(&cdma_inst, (u32)src, (u32)dest, size, NULL, NULL);

		if(return_value != 0){
			xil_printf("CDMA Error: code %d, (0x%08x,0x%08x,%d)\n", return_value, dest,src,size);
		}
	} else {
		xil_printf("CDMA Error: source and destination addresses must not located in the DLMB. Using memcpy instead. memcpy(0x%08x,0x%08x,%d)\n",dest,src,size);
		memcpy(dest,src,size);
	}

	return return_value;
}



/**
 * @brief Finish Central DMA Transfer
 *
 * This function will block until an ongoing CDMA transfer is complete.
 * If there is no CDMA transfer underway when this function is called, it
 * returns immediately.
 *
 * @param None
 * @return None
 *
 */
void wlan_mac_high_cdma_finish_transfer(){
	while(XAxiCdma_IsBusy(&cdma_inst)) {}
	return;
}



/**
 * @brief Transmit MPDU
 *
 * This function passes off an MPDU to the lower-level processor for transmission.
 *
 * @param tx_queue_entry* packet
 *  - Pointer to the packet that should be transmitted
 * @return None
 *
 */
void wlan_mac_high_mpdu_transmit(tx_queue_element* packet, int tx_pkt_buf) {
	wlan_ipc_msg ipc_msg_to_low;
	tx_frame_info* tx_mpdu;
	station_info* station;
	mac_header_80211* header;
	void* dest_addr;
	void* src_addr;
	u32 xfer_len;

	tx_mpdu = (tx_frame_info*) TX_PKT_BUF_TO_ADDR(tx_pkt_buf);

	header 	  = (mac_header_80211*)((((tx_queue_buffer*)(packet->data))->frame));

	// Insert sequence number here
	header->sequence_control = ((header->sequence_control) & 0xF) | ( (unique_seq&0xFFF)<<4 );

	// Call user code to notify it of dequeue

	if(mpdu_tx_dequeue_callback != NULL) mpdu_tx_dequeue_callback(packet);


	dest_addr = (void*)TX_PKT_BUF_TO_ADDR(tx_pkt_buf);
	src_addr  = (void*) (&(((tx_queue_buffer*)(packet->data))->frame_info));
	xfer_len  = ((tx_queue_buffer*)(packet->data))->frame_info.length + sizeof(tx_frame_info) + PHY_TX_PKT_BUF_PHY_HDR_SIZE - WLAN_PHY_FCS_NBYTES;

	// Transfer the frame info
	wlan_mac_high_cdma_start_transfer( dest_addr, src_addr, xfer_len);

	// Wait for transfer to finish
	wlan_mac_high_cdma_finish_transfer();

	// Place the unique sequence number in the packet and increment
	//   NOTE:  Adding to tx_mpdu must be done here due to the CDMA transfer
	tx_mpdu->unique_seq = unique_seq;
	unique_seq++;

	switch(((tx_queue_buffer*)(packet->data))->metadata.metadata_type){
	    case QUEUE_METADATA_TYPE_IGNORE:
		break;

		case QUEUE_METADATA_TYPE_STATION_INFO:
			station = (station_info*)(((tx_queue_buffer*)(packet->data))->metadata.metadata_ptr);

			//
			// NOTE: this would be a good place to add code to handle the automatic adjustment of transmission properties like rate
			//

			memcpy(&(tx_mpdu->params), &(station->tx), sizeof(tx_params));
		break;

		case QUEUE_METADATA_TYPE_TX_PARAMS:
			memcpy(&(tx_mpdu->params), (void*)(((tx_queue_buffer*)(packet->data))->metadata.metadata_ptr), sizeof(tx_params));
		break;
	}

	tx_mpdu->short_retry_count = 0;
	tx_mpdu->long_retry_count = 0;

	ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_TX_MPDU_READY);
	ipc_msg_to_low.arg0              = tx_pkt_buf;
	ipc_msg_to_low.num_payload_words = 0;

	if(unlock_pkt_buf_tx(tx_pkt_buf) != PKT_BUF_MUTEX_SUCCESS){
		warp_printf(PL_ERROR,"Error: unable to unlock tx pkt_buf %d\n",tx_pkt_buf);
	} else {
		tx_pkt_buf_busy_state |= (1 << tx_pkt_buf);
		ipc_mailbox_write_msg(&ipc_msg_to_low);
	}

}

inline u64 wlan_mac_high_get_unique_seq(){
	return unique_seq;
}

/**
 * @brief Retrieve Hardware Information
 *
 * This function returns the node hardware information structure maintained by CPU High.
 *
 * @param None
 * @return wlan_mac_hw_info*
 *  - Pointer to the hardware info struct maintained by the MAC High Framework
 *
 */
wlan_mac_hw_info* wlan_mac_high_get_hw_info(){
	return &hw_info;
}



/**
 * @brief Retrieve Hardware MAC Address from EEPROM
 *
 * This function returns the 6-byte unique hardware MAC address of the board.
 *
 * @param None
 * @return u8*
 *  - Pointer to 6-byte MAC address
 *
 */
u8* wlan_mac_high_get_eeprom_mac_addr(){
	return (u8 *) &(hw_info.hw_addr_wlan);
}



/**
 * @brief Check Validity of Tagged Rate
 *
 * This function checks the validity of a given rate from a tagged field in a management frame.
 *
 * @param u8 rate
 *     - Tagged rate
 * @return u8
 *     - 1 if valid
 *     - 0 if invalid
 *
 *  @note This function checks against the 12 possible valid rates sent in 802.11b/a/g.
 *  The faster 802.11n rates will return as invalid when this function is used.
 *
 */
u8 wlan_mac_high_valid_tagged_rate(u8 rate){
	u32 i;
	u8 valid_rates[NUM_VALID_RATES] = {0x02, 0x04, 0x0b, 0x16, 0x0c, 0x12, 0x18, 0x24, 0x30, 0x48, 0x60, 0x6c};

	for(i = 0; i < NUM_VALID_RATES; i++ ){
		if((rate & ~RATE_BASIC) == valid_rates[i]) return 1;
	}

	return 0;
}



/**
 * @brief Convert Tagged Rate to Human-Readable String (in Mbps)
 *
 * This function takes a tagged rate as an input and fills in a provided
 * string with the rate in Mbps.
 *
 * @param u8 rate
 *  - Tagged rate
 * @param char* str
 *  - Empty string that will be filled in by this function
 * @return u8
 *  - 1 if valid
 *  - 0 if invalid
 *
 *  @note The str argument must have room for 4 bytes at most ("5.5" followed by NULL)
 *
 */
void wlan_mac_high_tagged_rate_to_readable_rate(u8 rate, char* str){

	switch(rate & ~RATE_BASIC){
		case 0x02:  strcpy(str,"1");    break;
		case 0x04:  strcpy(str,"2");    break;
		case 0x0b:  strcpy(str,"5.5");  break;
		case 0x16:  strcpy(str,"11");   break;
		case 0x0c:  strcpy(str,"6");    break;
		case 0x12:  strcpy(str,"9");    break;
		case 0x18:  strcpy(str,"12");   break;
		case 0x24:  strcpy(str,"18");   break;
		case 0x30:  strcpy(str,"24");   break;
		case 0x48:  strcpy(str,"36");   break;
		case 0x60:  strcpy(str,"48");   break;
		case 0x6c:  strcpy(str,"54");   break;

		default:    // Unknown rate
			*str = NULL;
		break;
	}
}



/**
 * @brief Set up the 802.11 Header
 *
 * @param  mac_header_80211_common * header
 *     - Pointer to the 802.11 header
 * @param  u8 * addr_1
 *     - Address 1 of the packet header
 * @param  u8 * addr_3
 *     - Address 3 of the packet header
 * @return None
 */
void wlan_mac_high_setup_tx_header( mac_header_80211_common * header, u8 * addr_1, u8 * addr_3 ) {
	// Set up Addresses in common header
	header->address_1 = addr_1;
    header->address_3 = addr_3;
}



/**
 * @brief Set up the 802.11 Header
 *
 * @param  mac_header_80211_common * header
 *     - Pointer to the 802.11 header
 * @param  tx_queue_element * curr_tx_queue_element
 *     - Pointer to the TX queue element
 * @param  u32 tx_length
 *     - Length of the frame info
 * @param  tx_frame_info_flags_bf flags
 *     - Flags for the frame info
 * @param  u8 QID
 *     - Queue ID
 * @return None
 */
void wlan_mac_high_setup_tx_frame_info( mac_header_80211_common * header, tx_queue_element * curr_tx_queue_element, u32 tx_length, u8 flags, u8 QID ) {

	tx_queue_buffer* curr_tx_queue_buffer = ((tx_queue_buffer*)(curr_tx_queue_element->data));

	bzero(&(curr_tx_queue_buffer->frame_info), sizeof(tx_frame_info));

	// Set up frame info data
	curr_tx_queue_buffer->frame_info.timestamp_create			 = get_usec_timestamp();
	curr_tx_queue_buffer->frame_info.length          			 = tx_length;
	curr_tx_queue_buffer->frame_info.flags                       = flags;
	curr_tx_queue_buffer->frame_info.QID                         = QID;

}



/**
 * @brief WLAN MAC IPC receive
 *
 * IPC receive function that will poll the mailbox for as many messages as are
 * available and then call the CPU high IPC processing function on each message
 *
 * @param  None
 * @return None
 */
void wlan_mac_high_ipc_rx(){

#ifdef _DEBUG_
	u32 numMsg = 0;
	xil_printf("Mailbox Rx:  ");
#endif

	while( ipc_mailbox_read_msg( &ipc_msg_from_low ) == IPC_MBOX_SUCCESS ) {
		wlan_mac_high_process_ipc_msg(&ipc_msg_from_low);

#ifdef _DEBUG_
		numMsg++;
#endif
	}

#ifdef _DEBUG_
	xil_printf("Processed %d msg in one ISR\n", numMsg);
#endif
}



/**
 * @brief WLAN MAC IPC processing function for CPU High
 *
 * Process IPC message from CPU low
 *
 * @param  wlan_ipc_msg* msg
 *     - Pointer to the IPC message
 * @return None
 */
void wlan_mac_high_process_ipc_msg( wlan_ipc_msg* msg ) {

	u8                  rx_pkt_buf;
    u32                 temp_1, temp_2;
	rx_frame_info*      rx_mpdu;
	tx_frame_info*      tx_mpdu;

    // Determine what type of message this is
	switch(IPC_MBOX_MSG_ID_TO_MSG(msg->msg_id)) {

		//---------------------------------------------------------------------
		case IPC_MBOX_RX_MPDU_READY:
			// CPU Low has received an MPDU addressed to this node or to the broadcast address
			//
			rx_pkt_buf = msg->arg0;

			// First attempt to lock the indicated Rx pkt buf (CPU Low must unlock it before sending this msg)
			if(lock_pkt_buf_rx(rx_pkt_buf) != PKT_BUF_MUTEX_SUCCESS){
				warp_printf(PL_ERROR,"Error: unable to lock pkt_buf %d\n",rx_pkt_buf);
			} else {
				rx_mpdu = (rx_frame_info*)RX_PKT_BUF_TO_ADDR(rx_pkt_buf);

				//Before calling the user's callback, we'll pass this reception off to the BSS info subsystem so it can scrape for
				bss_info_rx_process((void*)(RX_PKT_BUF_TO_ADDR(rx_pkt_buf)));

				// Call the RX callback function to process the received packet
				mpdu_rx_callback((void*)(RX_PKT_BUF_TO_ADDR(rx_pkt_buf)));

				// Free up the rx_pkt_buf
				rx_mpdu->state = RX_MPDU_STATE_EMPTY;

				if(unlock_pkt_buf_rx(rx_pkt_buf) != PKT_BUF_MUTEX_SUCCESS){
					warp_printf(PL_ERROR, "Error: unable to unlock rx pkt_buf %d\n",rx_pkt_buf);
				}
			}
		break;

		//---------------------------------------------------------------------
		case IPC_MBOX_TX_MPDU_DONE:
			// CPU Low has finished the Tx process for the previously submitted-accepted frame
			//     CPU High should do any necessary post-processing, then recycle the packet buffer
            //

			// Lock this packet buffer
			if(lock_pkt_buf_tx(msg->arg0) != PKT_BUF_MUTEX_SUCCESS){
				xil_printf("Error: DONE Lock Tx Pkt Buf State Mismatch\n");
				return;
			}

			tx_mpdu = (tx_frame_info*)TX_PKT_BUF_TO_ADDR(msg->arg0);
			temp_1  = (4*(msg->num_payload_words)) / sizeof(wlan_mac_low_tx_details);
			mpdu_tx_done_callback(tx_mpdu, (wlan_mac_low_tx_details*)(msg->payload_ptr), temp_1);

			wlan_mac_high_release_tx_packet_buffer(msg->arg0);

			tx_poll_callback();
		break;


		//---------------------------------------------------------------------
		case IPC_MBOX_HW_INFO:
			// CPU low is passing up node hardware information that is only accessible by CPU low
			//
			temp_1 = hw_info.type;
			temp_2 = hw_info.wn_eth_device;

			// CPU Low updated the node's HW information
            //     NOTE:  this information is typically stored in the WARP v3 EEPROM, accessible only to CPU Low
			memcpy((void*) &hw_info, (void*) &(ipc_msg_from_low_payload[0]), sizeof( wlan_mac_hw_info ) );

			// Add type info from CPU low
			hw_info.type          = (hw_info.type & WARPNET_TYPE_80211_CPU_LOW_MASK) + (temp_1 & ~WARPNET_TYPE_80211_CPU_LOW_MASK);

			// Override value from CPU for Ethernet device
			hw_info.wn_eth_device = temp_2;
		break;


		//---------------------------------------------------------------------
		case IPC_MBOX_CPU_STATUS:
			// CPU low's status
			//
			cpu_low_status = ipc_msg_from_low_payload[0];

			if(cpu_low_status & CPU_STATUS_EXCEPTION){
				warp_printf(PL_ERROR, "An unrecoverable exception has occurred in CPU_LOW, halting...\n");
				warp_printf(PL_ERROR, "Reason code: %d\n", ipc_msg_from_low_payload[1]);
				while(1){}
			}
		break;


		//---------------------------------------------------------------------
		case IPC_MBOX_MEM_READ_WRITE:
			// Memory Read / Write message
			//   - Allows CPU High to read / write arbitrary memory locations in CPU low
			//
			if(cpu_low_reg_read_buffer != NULL){
				memcpy( (u8*)cpu_low_reg_read_buffer, (u8*)ipc_msg_from_low_payload, (msg->num_payload_words) * sizeof(u32));
				cpu_low_reg_read_buffer_status = CPU_LOW_REG_READ_BUFFER_STATUS_READY;

			} else {
				warp_printf(PL_ERROR, "Error: received low-level register buffer from CPU_LOW and was not expecting it\n");
			}
		break;


		//---------------------------------------------------------------------
		case IPC_MBOX_LOW_PARAM:
			// Param Read / Write message
			//   - Allows CPU High to read / write parameters in CPU low
			//
			if(cpu_low_param_read_buffer != NULL){
				memcpy( (u8*)cpu_low_param_read_buffer, (u8*)ipc_msg_from_low_payload, (msg->num_payload_words) * sizeof(u32));
				cpu_low_param_read_buffer_size   = msg->num_payload_words;
				cpu_low_param_read_buffer_status = CPU_LOW_PARAM_READ_BUFFER_STATUS_READY;

			} else {
				warp_printf(PL_ERROR, "Error: received low-level parameter buffer from CPU_LOW and was not expecting it\n");
			}
		break;


		//---------------------------------------------------------------------
		default:
			warp_printf(PL_ERROR, "Unknown IPC message type %d\n",IPC_MBOX_MSG_ID_TO_MSG(msg->msg_id));
		break;
	}
}



/**
 * @brief Set Random Seed
 *
 * Send an IPC message to CPU Low to set the Random Seed
 *
 * @param  unsigned int seed
 *     - Random number generator seed
 * @return None
 */
void wlan_mac_high_set_srand( unsigned int seed ) {

	wlan_ipc_msg       ipc_msg_to_low;
	u32                ipc_msg_to_low_payload = seed;
	// Send message to CPU Low
	ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_LOW_RANDOM_SEED);
	ipc_msg_to_low.num_payload_words = 1;
	ipc_msg_to_low.payload_ptr       = &(ipc_msg_to_low_payload);

	ipc_mailbox_write_msg(&ipc_msg_to_low);
}



/**
 * @brief Set MAC Channel
 *
 * Send an IPC message to CPU Low to set the MAC Channel
 *
 * @param  unsigned int mac_channel
 *     - 802.11 Channel to set
 * @return None
 */
void wlan_mac_high_set_channel( unsigned int mac_channel ) {

	wlan_ipc_msg       ipc_msg_to_low;
	u32                ipc_msg_to_low_payload = mac_channel;


	if(wlan_lib_channel_verify(mac_channel) == 0){

		// Send message to CPU Low
		ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_CONFIG_CHANNEL);
		ipc_msg_to_low.num_payload_words = 1;
		ipc_msg_to_low.payload_ptr       = &(ipc_msg_to_low_payload);

		ipc_mailbox_write_msg(&ipc_msg_to_low);
	} else {
		xil_printf("Channel %d not allowed\n", mac_channel);
	}
}



/**
 * @brief Set Rx Antenna Mode
 *
 * Send an IPC message to CPU Low to set the Rx antenna mode.
 *
 * @param  u8 ant_mode
 *     - Antenna mode selection
 * @return None
 */
void wlan_mac_high_set_rx_ant_mode( u8 ant_mode ) {

	wlan_ipc_msg       ipc_msg_to_low;
	u32                ipc_msg_to_low_payload = (u32)ant_mode;

	//Sanity check input
	switch(ant_mode){
		case RX_ANTMODE_SISO_ANTA:
		case RX_ANTMODE_SISO_ANTB:
		case RX_ANTMODE_SISO_ANTC:
		case RX_ANTMODE_SISO_ANTD:
		case RX_ANTMODE_SISO_SELDIV_2ANT:
			rx_ant_mode_tracker = ant_mode;
		break;
		default:
			xil_printf("Error: unsupported antenna mode %x\n", ant_mode);
			return;
		break;
	}

	// Send message to CPU Low
	ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_CONFIG_RX_ANT_MODE);
	ipc_msg_to_low.num_payload_words = 1;
	ipc_msg_to_low.payload_ptr       = &(ipc_msg_to_low_payload);

	ipc_mailbox_write_msg(&ipc_msg_to_low);
}



/**
 * @brief Set Tx Control Packet Power
 *
 * Send an IPC message to CPU Low to set the Tx control packet power
 *
 * @param  s8 pow
 *     - Tx control packet power
 * @return None
 */
void wlan_mac_high_set_tx_ctrl_pow( s8 pow ) {

	wlan_ipc_msg       ipc_msg_to_low;
	u32                ipc_msg_to_low_payload = (u32)pow;

	// Send message to CPU Low
	ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_CONFIG_TX_CTRL_POW);
	ipc_msg_to_low.num_payload_words = 1;
	ipc_msg_to_low.payload_ptr       = &(ipc_msg_to_low_payload);

	ipc_mailbox_write_msg(&ipc_msg_to_low);
}



/**
 * @brief Set Rx Filter
 *
 * Send an IPC message to CPU Low to set the filter for receptions. This will
 * allow or disallow different packets from being passed up to CPU_High
 *
 * @param    filter_mode
 * 				- RX_FILTER_FCS_GOOD
 * 				- RX_FILTER_FCS_ALL
 * 				- RX_FILTER_ADDR_STANDARD	(unicast to me or multicast)
 * 				- RX_FILTER_ADDR_ALL_MPDU	(all MPDU frames to any address)
 * 				- RX_FILTER_ADDR_ALL			(all observed frames, including control)
 *
 * @note	FCS and ADDR filter selections must be bit-wise ORed together. For example,
 * wlan_mac_high_set_rx_filter_mode(RX_FILTER_FCS_ALL | RX_FILTER_ADDR_ALL)
 *
 * @return	None
 */
void wlan_mac_high_set_rx_filter_mode( u32 filter_mode ) {

	wlan_ipc_msg       ipc_msg_to_low;
	u32                ipc_msg_to_low_payload = (u32)filter_mode;

	// Send message to CPU Low
	ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_CONFIG_RX_FILTER);
	ipc_msg_to_low.num_payload_words = 1;
	ipc_msg_to_low.payload_ptr       = &(ipc_msg_to_low_payload);

	ipc_mailbox_write_msg(&ipc_msg_to_low);
}



/**
 * @brief Write a memory location in CPU low
 *
 * Send an IPC message to CPU Low to write the given data
 *
 * @param  u32 num_words
 *     - Number of words in the message payload
 * @param  u32 * payload
 *     - Pointer to the message payload
 * @return None
 */
int wlan_mac_high_write_low_mem( u32 num_words, u32* payload ){
	wlan_ipc_msg	   ipc_msg_to_low;

	if( num_words > IPC_BUFFER_MAX_NUM_WORDS ){
		return -1;
	}

	// Send message to CPU Low
	ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_MEM_READ_WRITE);
	ipc_msg_to_low.num_payload_words = num_words;
	ipc_msg_to_low.arg0				 = IPC_REG_WRITE_MODE;
	ipc_msg_to_low.payload_ptr       = payload;

	ipc_mailbox_write_msg(&ipc_msg_to_low);

	return 0;
}



/**
 * @brief Read a memory location in CPU low
 *
 * Send an IPC message to CPU Low to read the given data
 *
 * @param  u32 num_words
 *     - Number of words to read from CPU low
 * @param  u32 baseaddr
 *     - Base address of the data to read from CPU low
 * @param  u32 * payload
 *     - Pointer to the buffer to be populated with data
 * @return None
 */
int wlan_mac_high_read_low_mem( u32 num_words, u32 baseaddr, u32* payload ){

	wlan_ipc_msg	   ipc_msg_to_low;
	ipc_reg_read_write ipc_msg_to_low_payload;

	if(InterruptController.IsStarted == XIL_COMPONENT_IS_STARTED){
		// Send message to CPU Low
		ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_MEM_READ_WRITE);
		ipc_msg_to_low.num_payload_words = sizeof(ipc_reg_read_write) / sizeof(u32);
		ipc_msg_to_low.arg0				 = IPC_REG_READ_MODE;
		ipc_msg_to_low.payload_ptr       = (u32*)(&(ipc_msg_to_low_payload));

		ipc_msg_to_low_payload.baseaddr  = baseaddr;
		ipc_msg_to_low_payload.num_words = num_words;

		// Set the read buffer to the payload pointer
		cpu_low_reg_read_buffer          = payload;
		cpu_low_reg_read_buffer_status   = CPU_LOW_REG_READ_BUFFER_STATUS_NOT_READY;

		ipc_mailbox_write_msg(&ipc_msg_to_low);

		// Wait for CPU low to finish the read
		while(cpu_low_reg_read_buffer_status != CPU_LOW_REG_READ_BUFFER_STATUS_READY){}

		// Reset the read buffer
		cpu_low_reg_read_buffer          = NULL;

		return 0;
	} else {
		xil_printf("Error: Reading CPU_LOW memory requires interrupts being enabled");
		return -1;
	}
}



/**
 * @brief Read a parameter in CPU low
 *
 * Send an IPC message to CPU Low to read the given paramter
 *
 * @param  u32 num_words
 *     - Number of words to read from CPU low
 * @param  u32 baseaddr
 *     - Base address of the data to read from CPU low
 * @param  u32 * payload
 *     - Pointer to the buffer to be populated with data
 * @return None
 */
int wlan_mac_high_read_low_param( u32 param_id, u32* size, u32* payload ){

	wlan_ipc_msg	   ipc_msg_to_low;

	if(InterruptController.IsStarted == XIL_COMPONENT_IS_STARTED){
		// Send message to CPU Low
		ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_LOW_PARAM);
		ipc_msg_to_low.num_payload_words = 1;
		ipc_msg_to_low.arg0				 = IPC_REG_READ_MODE;
		ipc_msg_to_low.payload_ptr       = (u32*)(&(param_id));

		// Set the read buffer to the payload pointer
		cpu_low_param_read_buffer        = payload;
		cpu_low_param_read_buffer_status = CPU_LOW_PARAM_READ_BUFFER_STATUS_NOT_READY;

		ipc_mailbox_write_msg(&ipc_msg_to_low);

		// Wait for CPU low to finish the read
		while(cpu_low_param_read_buffer_status != CPU_LOW_PARAM_READ_BUFFER_STATUS_READY){}

		// Set the size
		*(size) = cpu_low_param_read_buffer_size;

		// Reset the read buffer
		cpu_low_param_read_buffer        = NULL;
		cpu_low_param_read_buffer_size   = 0;

		return 0;
	} else {
		xil_printf("Error: Reading CPU_LOW parameters requires interrupts being enabled");
		return -1;
	}
}



/**
 * @brief Enable/Disable DSSS
 *
 * Send an IPC message to CPU Low to set the DSSS value
 *
 * @param  unsigned int dsss_value
 *     - DSSS Enable/Disable value
 * @return None
 */
void wlan_mac_high_set_dsss( unsigned int dsss_value ) {

	wlan_ipc_msg       ipc_msg_to_low;
	u32                ipc_msg_to_low_payload[1];
	ipc_config_phy_rx* config_phy_rx;

	// Send message to CPU Low
	ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_CONFIG_PHY_RX);
	ipc_msg_to_low.num_payload_words = sizeof(ipc_config_phy_rx)/sizeof(u32);
	ipc_msg_to_low.payload_ptr       = &(ipc_msg_to_low_payload[0]);

	// Initialize the payload
	init_ipc_config(config_phy_rx, ipc_msg_to_low_payload, ipc_config_phy_rx);

	config_phy_rx->enable_dsss = dsss_value;

	ipc_mailbox_write_msg(&ipc_msg_to_low);
}



/**
 * @brief Set the timestamp for CPU low
 *
 * Send an IPC message to CPU Low to set the timestamp
 *
 * @param  u64 timestamp
 *     - Value for CPU low to set the timestamp
 * @return None
 */
void wlan_mac_high_set_timestamp( u64 timestamp ){

	wlan_ipc_msg       ipc_msg_to_low;

	// Send message to CPU Low
	ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_SET_TIME);
	ipc_msg_to_low.num_payload_words = sizeof(u64)/sizeof(u32);
	ipc_msg_to_low.arg0				 = 0; // This means the u64 should replace the old timestamp
	ipc_msg_to_low.payload_ptr       = (u32*)(&(timestamp));

	ipc_mailbox_write_msg(&ipc_msg_to_low);
}



/**
 * @brief Modify the timestamp
 *
 * Send an IPC message to CPU Low to modify the timestamp
 *
 * @param  s64 timestamp
 *     - Value to add to the current timestamp
 * @return None
 */
void wlan_mac_high_set_timestamp_delta( s64 timestamp ){

	wlan_ipc_msg       ipc_msg_to_low;

	// Send message to CPU Low
	ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_SET_TIME);
	ipc_msg_to_low.num_payload_words = sizeof(u64)/sizeof(u32);
	ipc_msg_to_low.arg0				 = 1; // This means the s64 should augment the old timestamp
	ipc_msg_to_low.payload_ptr       = (u32*)(&(timestamp));

	ipc_mailbox_write_msg(&ipc_msg_to_low);
}



/**
 * @brief Get CPU low's state
 *
 * Send an IPC message to CPU Low to get its state
 *
 * @param  None
 * @return None
 */
void wlan_mac_high_request_low_state(){
	wlan_ipc_msg       ipc_msg_to_low;

	// Send message to CPU Low
	ipc_msg_to_low.msg_id            = IPC_MBOX_MSG_ID(IPC_MBOX_CPU_STATUS);
	ipc_msg_to_low.num_payload_words = 0;
	ipc_msg_to_low.arg0				 = 1; // This means a request for a status update

	ipc_mailbox_write_msg(&ipc_msg_to_low);
}



/**
 * @brief Check that CPU low is initialized
 *
 * @param  None
 * @return int
 *     - 0 if CPU low is not initialized
 *     - 1 if CPU low is initialized
 */
int wlan_mac_high_is_cpu_low_initialized(){
	wlan_mac_high_ipc_rx();
	return ( (cpu_low_status & CPU_STATUS_INITIALIZED) != 0 );
}



/**
 * @brief Check that CPU low is ready to transmit
 *
 * @param  None
 * @return int
 *     - 0 if CPU low is not ready to transmit
 *     - 1 if CPU low is ready to transmit
 */
int wlan_mac_high_is_ready_for_tx(){
	return (tx_pkt_buf_busy_state != 3);
}


/**
 * @brief Return the index of the next free transmit packet buffer
 * and lock it.
 *
 * @param  None
 * @return int
 *     - packet buffer index of free, now-locked packet buffer
 *     - -1 if there are no free Tx packet buffers
 */
int wlan_mac_high_lock_new_tx_packet_buffer(){
	int pkt_buf_sel = -1;

	switch(tx_pkt_buf_busy_state){
		case 1: //Ping: busy, Pong: free
			pkt_buf_sel = 1;
			tx_pkt_buf_busy_state |= 2;
		break;
		case 0: //Ping: free, Pong: free
		case 2: //Ping: free, Pong: busy
			pkt_buf_sel = 0;
			tx_pkt_buf_busy_state |= 1;
		break;
		case 3: //Ping: free, Pong: busy
			pkt_buf_sel = -1;
		break;
	}

	if(pkt_buf_sel != -1){
		if(lock_pkt_buf_tx(pkt_buf_sel) != PKT_BUF_MUTEX_SUCCESS){
			xil_printf("Error: Unlock Tx Pkt Buf State Mismatch\n");
			return -1;
		}
	}

	return pkt_buf_sel;
}

/**
 * @brief Release the current Tx packet buffer
 *
 * @param  None
 * @return int
 * 	   - 0 if success
 *     - -1 if error
 */
int wlan_mac_high_release_tx_packet_buffer(int pkt_buf){

	switch(pkt_buf){
		case 0:
			tx_pkt_buf_busy_state &= (~1);
		break;
		case 1:
			tx_pkt_buf_busy_state &= (~2);
		break;
		default:
			xil_printf("Error: invalid pkt buf selection");
			return -1;
		break;
	}

	if(unlock_pkt_buf_tx(pkt_buf) != PKT_BUF_MUTEX_SUCCESS){
		xil_printf("Error: Unlock Tx Pkt Buf State Mismatch\n");
		return -1;
	} else {
		return 0;
	}
}



/**
 * @brief Determine the MPDU packet type
 *
 * @param  None
 * @return u8
 *     - Packet type: {PKT_TYPE_MGMT, PKT_TYPE_CONTROL, PKT_TYPE_DATA_ENCAP_ETH, PKT_TYPE_DATA_ENCAP_LTG, PKT_TYPE_DATA_OTHER}
 *     - NULL
 */
u8 wlan_mac_high_pkt_type(void* mpdu, u16 length){

	mac_header_80211* hdr_80211;
	llc_header* llc_hdr;

	hdr_80211 = (mac_header_80211*)((void*)mpdu);

	if((hdr_80211->frame_control_1 & 0xF) == MAC_FRAME_CTRL1_TYPE_MGMT){
		return PKT_TYPE_MGMT;

	} else if((hdr_80211->frame_control_1) == MAC_FRAME_CTRL1_SUBTYPE_ACK) {
		return PKT_TYPE_CONTROL_ACK;

	} else if((hdr_80211->frame_control_1) == MAC_FRAME_CTRL1_SUBTYPE_CTS) {
		return PKT_TYPE_CONTROL_CTS;

	} else if((hdr_80211->frame_control_1) == MAC_FRAME_CTRL1_SUBTYPE_RTS) {
		return PKT_TYPE_CONTROL_RTS;

	} else if((hdr_80211->frame_control_1 & 0xF) == MAC_FRAME_CTRL1_TYPE_DATA) {

		//Check if this is an encrypted packet. If it is, we can't trust any of the MPDU
		//payload bytes for further classification
		if(hdr_80211->frame_control_2 & MAC_FRAME_CTRL2_FLAG_PROTECTED){
			return PKT_TYPE_DATA_PROTECTED;
		}

		llc_hdr = (llc_header*)((u8*)mpdu + sizeof(mac_header_80211));

		if(length < (sizeof(mac_header_80211) + sizeof(llc_header) + WLAN_PHY_FCS_NBYTES)){
			// This was a DATA packet, but it wasn't long enough to have an LLC header.
			return PKT_TYPE_DATA_OTHER;

		} else {
			switch(llc_hdr->type){
				case LLC_TYPE_ARP:
				case LLC_TYPE_IP:
					return PKT_TYPE_DATA_ENCAP_ETH;
				break;

				case LLC_TYPE_WLAN_LTG:
					return PKT_TYPE_DATA_ENCAP_LTG;
				break;

				default:
					return PKT_TYPE_DATA_OTHER;
				break;
			}
		}
	}

	// Unknown packet type, return NULL
	return NULL;
}



/**
 * @brief Set the debug GPIO (inline function)
 *
 * @param  u8 val
 *     - Value to set the debug GPIO
 * @return None
 */
inline void wlan_mac_high_set_debug_gpio(u8 val){
	debug_gpio_state |= (val & 0xF);
	XGpio_DiscreteWrite(&Gpio, GPIO_OUTPUT_CHANNEL, debug_gpio_state);
}



/**
 * @brief Clear the debug GPIO (inline function)
 *
 * @param  u8 val
 *     - Value to clear the debug GPIO
 * @return None
 */
inline void wlan_mac_high_clear_debug_gpio(u8 val){
	debug_gpio_state &= ~(val & 0xF);
	XGpio_DiscreteWrite(&Gpio, GPIO_OUTPUT_CHANNEL, debug_gpio_state);
}



/**
 * @brief Convert a string to a number
 *
 * @param  char * str
 *     - String to convert
 * @return int
 *     - Integer value of the string
 *
 * @note   For now this only works with non-negative values
 */
int str2num(char* str){
	u32 i;
	u8  decade_index;
	int multiplier;
	int return_value  = 0;
	u8  string_length = strlen(str);

	for(decade_index = 0; decade_index < string_length; decade_index++){
		multiplier = 1;
		for(i = 0; i < (string_length - 1 - decade_index) ; i++){
			multiplier = multiplier*10;
		}
		return_value += multiplier*(u8)(str[decade_index] - 48);
	}

	return return_value;
}



/**
 * @brief Sleep delay (in microseconds)
 *
 * Function will delay execution for the specified amount of time.
 *
 * @param  u64 delay
 *     - Time to sleep in microseconds
 * @return None
 */
void usleep(u64 delay){
	u64 timestamp = get_usec_timestamp();
	while(get_usec_timestamp() < (timestamp+delay)){}
	return;
}



/**
 * @brief Add association
 *
 * Function will add an association to the association table for the given address using the
 * requested AID
 *
 * @param  dl_list* assoc_tbl
 *     - Association table pointer
 * @param  dl_list* stat_tbl
 *     - Statistics table pointer
 * @param  u8* addr
 *     - Address of association to add to the association table
 * @param  u16 requested_AID
 *     - Requested AID for the new association.  A value of 'ADD_ASSOCIATION_ANY_AID' will use the next available AID.
 * @return station_info *
 *     - Pointer to the station info in the association table
 *     - NULL
 *
 * @note   This function will not perform any filtering on the addr field
 */
station_info* wlan_mac_high_add_association(dl_list* assoc_tbl, dl_list* stat_tbl, u8* addr, u16 requested_AID){
	dl_entry*	  entry;
	station_info* station;

	statistics_txrx*   station_stats;
	dl_entry*	  curr_station_info_entry;
	station_info* curr_station_info;
	u16 curr_AID;

	curr_AID = 0;

	if(requested_AID != ADD_ASSOCIATION_ANY_AID){
		// This call is requesting a particular AID.
		entry = wlan_mac_high_find_station_info_AID(assoc_tbl, requested_AID);

		if(entry != NULL){
			station = (station_info*)(entry->data);
			// We found a station_info with this requested AID. Let's check
			// if the address matches the argument to this function call
			if(wlan_addr_eq(station->addr, addr)){
				// We already have this exact station_info, so we'll just return a pointer to it.
				return station;
			} else {
				// The requested AID is already in use and it is used by a different
				// address. We cannot add this association.
				return NULL;
			}
		}
	}

	entry = wlan_mac_high_find_station_info_ADDR(assoc_tbl, addr);

	if(entry != NULL){
		station = (station_info*)(entry->data);
		// This addr is already tied to an association table entry. We'll just pass this call
		// the pointer to that entry back to the calling function without creating a new entry

		return station;
	} else {
		// First check that we have room in the association table to add the entry
		if(assoc_tbl->length >= max_num_associations) {
			return NULL;
		}

		// This addr is new, so we'll have to add an entry into the association table
		entry = wlan_mac_high_malloc(sizeof(dl_entry));
		if(entry == NULL){
			return NULL;
		}

		station = wlan_mac_high_malloc(sizeof(station_info));
		if(station == NULL){
			free(entry);
			return NULL;
		}

        // Get the statistics for this address
		station_stats = wlan_mac_high_add_statistics(stat_tbl, station, addr);
		if(station_stats == NULL){
			wlan_mac_high_free(entry);
			wlan_mac_high_free(station);
			return NULL;
		}

		bzero(&(station->rate_info),sizeof(rate_selection_info));
		station->rate_info.rate_selection_scheme = RATE_SELECTION_SCHEME_STATIC;

		// Populate the entry
		entry->data = (void*)station;

		// Populate the station with information
		station->stats = station_stats;
		station->stats->is_associated = 1;

		memcpy(station->addr, addr, 6);

		station->tx.phy.rate = 0;
		station->AID         = 0;
		station->hostname[0] = 0;
		station->flags       = 0;

		// Set the last received sequence number to something invalid so we don't accidentally
		// de-duplicate the next reception if that sequency number is 0.
		station->rx.last_seq = 0xFFFF; //Sequence numbers are only 12 bits long. This is intentionally invalid.

		// Do not allow WARP nodes to time out
		if(wlan_mac_addr_is_warp(addr)){
			station->flags |= STATION_INFO_FLAG_DISABLE_ASSOC_CHECK;
		}

		// Set the association TX parameters
		memcpy(&(station->tx), &default_unicast_data_tx_params, sizeof(tx_params));

		// Set up the AID for the association
		if(requested_AID == ADD_ASSOCIATION_ANY_AID){
			// Find the minimum AID that can be issued to this station.
			curr_station_info_entry = assoc_tbl->first;

			while(curr_station_info_entry != NULL){

				curr_station_info = (station_info*)(curr_station_info_entry->data);

				if( (curr_station_info->AID - curr_AID) > 1 ){
					// There is a hole in the association table and we can re-issue a previously issued AID.
					station->AID = curr_station_info->AID - 1;

					// Add this station into the association table just before the curr_station_info
					dl_entry_insertBefore(assoc_tbl, curr_station_info_entry, entry);

					break;
				} else {
					curr_AID = curr_station_info->AID;
				}

				curr_station_info_entry = dl_entry_next(curr_station_info_entry);
			}

			if(station->AID == 0){
				// There was no hole in the association table, so we just issue a new AID larger than the last AID in the table.

				if(assoc_tbl->length == 0){
					// This is the first entry in the association table;
					station->AID = 1;
				} else {
					curr_station_info_entry = assoc_tbl->last;
					curr_station_info = (station_info*)(curr_station_info_entry->data);
					station->AID = (curr_station_info->AID)+1;
				}

				// Add this station into the association table at the end
				dl_entry_insertEnd(assoc_tbl, entry);
			}
		} else {
			// Find the right place in the dl_list to insert this station_info with the requested AID
			curr_station_info_entry = assoc_tbl->first;

			while(curr_station_info_entry != NULL){

				curr_station_info = (station_info*)(curr_station_info_entry->data);

				if(curr_station_info->AID > requested_AID){
					station->AID = requested_AID;
					// Add this station into the association table just before the curr_station_info
					dl_entry_insertBefore(assoc_tbl, curr_station_info_entry, entry);
				}

				curr_station_info_entry = dl_entry_next(curr_station_info_entry);
			}

			if(station->AID == 0){
				// There was no hole in the association table, so we insert it at the end
				station->AID = requested_AID;

				// Add this station into the association table at the end
				dl_entry_insertEnd(assoc_tbl, entry);
			}
		}

		// Print our associations on the UART
		wlan_mac_high_print_associations(assoc_tbl);
		return station;
	}
}



/**
 * @brief Remove association
 *
 * Function will remove the association from the association table for the given address
 *
 * @param  dl_list* assoc_tbl
 *     - Association table pointer
 * @param  dl_list* stat_tbl
 *     - Statistics table pointer
 * @param  u8* addr
 *     - Address of association to remove from the association table
 * @return int
 *     -  0  - Successfully removed the association
 *     - -1  - Failed to remove association
 */
int wlan_mac_high_remove_association(dl_list* assoc_tbl, dl_list* stat_tbl, u8* addr){
	u32 i;
	dl_entry* entry;
	station_info* station;

	dl_entry* stats_entry;

	entry = wlan_mac_high_find_station_info_ADDR(assoc_tbl, addr);

	if(entry == NULL){
		// This addr doesn't refer to any station currently in the association table,
		// so there is nothing to remove. We'll return an error to let the calling
		// function know that something is wrong.
		return -1;
	} else {
		station = (station_info*)(entry->data);

		if ((station->flags & STATION_INFO_DO_NOT_REMOVE) != STATION_INFO_DO_NOT_REMOVE) {
			// Remove station from the association table;
			dl_entry_remove(assoc_tbl, entry);

			if (promiscuous_stats_enabled) {
				station->stats->is_associated = 0;
			} else {
				//Remove station's statistics from statistics table
				stats_entry = wlan_mac_high_find_statistics_ADDR(stat_tbl, addr);
				dl_entry_remove(stat_tbl, stats_entry);
				wlan_mac_high_free(stats_entry);
				wlan_mac_high_free(station->stats);
			}

			wlan_mac_high_free(entry);
			wlan_mac_high_free(station);
			wlan_mac_high_print_associations(assoc_tbl);
		} else {
			xil_printf("Station not removed due to flags: %02x", addr[0]);
			for ( i = 1; i < ETH_ADDR_LEN; i++ ) { xil_printf(":%02x", addr[i] ); } xil_printf("\n");
		}
		return 0;
	}
}



/**
 * @brief Is the provided station a valid association
 *
 * Function will check that the provided station is part of the association table
 *
 * @param  dl_list* assoc_tbl
 *     - Association table pointer
 * @param  station_info * station
 *     - Station info pointer to check
 * @return u8
 *     - 0  - Station is not in the association table
 *     - 1  - Station is in the association table
 */
u8 wlan_mac_high_is_valid_association(dl_list* assoc_tbl, station_info* station){
	dl_entry*	  curr_station_info_entry;
	station_info* curr_station_info;

	curr_station_info_entry = assoc_tbl->first;

	while(curr_station_info_entry != NULL){

		curr_station_info = (station_info*)(curr_station_info_entry->data);

		if(station == curr_station_info){
			return 1;
		}

		curr_station_info_entry = dl_entry_next(curr_station_info_entry);
		curr_station_info = (station_info*)(curr_station_info_entry->data);
	}

	return 0;
}



/**
 * @brief Set the maximum number of associations
 *
 * Function will set the maximum number of associations allowed on the node.
 *
 * @param  u32 num_associations
 *     - Number of associations (must be less than WLAN_MAC_HIGH_MAX_ASSOCIATONS)
 * @return u32
 *     - Maximum number of associations
 */
u32 wlan_mac_high_set_max_associations(u32 num_associations) {

	if (num_associations < WLAN_MAC_HIGH_MAX_ASSOCIATONS) {
		max_num_associations = num_associations;
	} else {
		max_num_associations = WLAN_MAC_HIGH_MAX_ASSOCIATONS;
	}

    return max_num_associations;
}



/**
 * @brief Get the maximum number of associations
 *
 * Function will get the maximum number of associations allowed on the node.
 *
 * @return u32
 *     - Maximum number of associations
 */
u32 wlan_mac_high_get_max_associations() {
    return max_num_associations;
}



/**
 * @brief Print associations
 *
 * Function will print the associations in the association table to the UART
 *
 * @param  dl_list* assoc_tbl
 *     - Association table pointer
 * @return None
 */
void wlan_mac_high_print_associations(dl_list* assoc_tbl){
	u64 timestamp = get_usec_timestamp();
	dl_entry*	  curr_station_info_entry;
	station_info* curr_station_info;

	xil_printf("\n(MAC time = %d usec)\n",timestamp);
	xil_printf("|-ID-|----- MAC ADDR ----|\n");

	curr_station_info_entry = assoc_tbl->first;

	while(curr_station_info_entry != NULL){

		curr_station_info       = (station_info*)(curr_station_info_entry->data);

		xil_printf("| %02x | %02x:%02x:%02x:%02x:%02x:%02x |\n", curr_station_info->AID,
				curr_station_info->addr[0],curr_station_info->addr[1],curr_station_info->addr[2],curr_station_info->addr[3],curr_station_info->addr[4],curr_station_info->addr[5]);

		curr_station_info_entry = dl_entry_next(curr_station_info_entry);
		curr_station_info       = (station_info*)(curr_station_info_entry->data);
	}
	xil_printf("|------------------------|\n");
}



/**
 * @brief Add statistics
 *
 * Function will add a statistics structure to the statistics table for the given address
 *
 * @param  dl_list* stat_tbl
 *     - Statistics table pointer
 * @param  station_info * station
 *     - Station info pointer
 * @param  u8* addr
 *     - Address of station for which we will add statistics
 * @return statistics_txrx *
 *     - Pointer to the statistics structure in the statistics table
 *     - NULL
 */
statistics_txrx* wlan_mac_high_add_statistics(dl_list* stat_tbl, station_info* station, u8* addr){
	dl_entry*	station_stats_entry;
	dl_entry*	curr_statistics_entry;
	dl_entry*   oldest_statistics_entry = NULL;

	statistics_txrx* station_stats      = NULL;
	statistics_txrx* curr_statistics    = NULL;
	statistics_txrx* oldest_statistics  = NULL;

	if(station == NULL){
		if (!promiscuous_stats_enabled) {
			// This statistics struct isn't being added to an associated station. Furthermore,
			// Promiscuous statistics are now allowed, so we will return NULL to the calling function.
			return NULL;
		}
	}

	station_stats_entry = wlan_mac_high_find_statistics_ADDR(stat_tbl, addr);

	if(station_stats_entry == NULL){
		// Note: This memory allocation has no corresponding free. It is by definition a memory leak.
		// The reason for this is that it allows the node to monitor statistics on surrounding devices.
		// In a busy environment, this promiscuous statistics gathering can be disabled by commenting
		// out the ALLOW_PROMISC_STATISTICS or disabled via the WLAN Exp framework.

		if(stat_tbl->length >= WLAN_MAC_HIGH_MAX_PROMISC_STATS){
			// There are too many statistics being tracked. We'll get rid of the oldest that isn't currently associated.
			curr_statistics_entry = stat_tbl->first;

			while(curr_statistics_entry != NULL){
				curr_statistics = (statistics_txrx*)(curr_statistics_entry->data);

				if( (oldest_statistics_entry == NULL) ){
					if(curr_statistics->is_associated == 0){
						oldest_statistics_entry = curr_statistics_entry;
						oldest_statistics = (statistics_txrx*)(oldest_statistics_entry->data);
					}
				} else if(( (curr_statistics->latest_txrx_timestamp) < (oldest_statistics->latest_txrx_timestamp)) ){
					if(curr_statistics->is_associated == 0){
						oldest_statistics_entry = curr_statistics_entry;
						oldest_statistics = (statistics_txrx*)(oldest_statistics_entry->data);
					}
				}
				curr_statistics_entry = dl_entry_next(curr_statistics_entry);
			}

			if(oldest_statistics_entry == NULL){
				xil_printf("ERROR: Could not find deletable oldest statistics.\n");
				xil_printf("    Ensure that WLAN_MAC_HIGH_MAX_PROMISC_STATS > max_associations\n");
				xil_printf("    if allowing promiscuous statistics\n");
			} else {
				dl_entry_remove(stat_tbl, oldest_statistics_entry);
				wlan_mac_high_free(oldest_statistics_entry);
				wlan_mac_high_free(oldest_statistics);
			}
		}

		station_stats_entry = wlan_mac_high_malloc(sizeof(dl_entry));

		if(station_stats_entry == NULL){
			return NULL;
		}

		station_stats = wlan_mac_high_calloc(sizeof(statistics_txrx));

		if(station_stats == NULL){
			wlan_mac_high_free(station_stats_entry);
			return NULL;
		}

		station_stats_entry->data = (void*)station_stats;

		memcpy(station_stats->addr, addr, 6);

		dl_entry_insertEnd(stat_tbl, station_stats_entry);

	} else {
		station_stats = (statistics_txrx*)(station_stats_entry->data);
	}
	if(station != NULL){
		station->stats = station_stats;
	}

	return station_stats;
}



/**
 * @brief Reset statistics
 *
 * Function will remove all the statistics in the statistics table except those for associated nodes
 *
 * @param  dl_list* stat_tbl
 *     - Statistics table pointer
 * @return None
 */
void wlan_mac_high_reset_statistics(dl_list* stat_tbl){
	statistics_txrx* curr_statistics       = NULL;
	dl_entry*        next_statistics_entry = NULL;
	dl_entry*        curr_statistics_entry = NULL;

	next_statistics_entry = stat_tbl->first;

	// Remove all statistics entries from the statistics table
	//
	// NOTE:  Cannot use a for loop for this iteration b/c we are removing
	//   elements from the list.
	while(next_statistics_entry != NULL){

		curr_statistics_entry = next_statistics_entry;
		next_statistics_entry = dl_entry_next(curr_statistics_entry);

		curr_statistics = (statistics_txrx*)(curr_statistics_entry->data);

		bzero((void*)(&(curr_statistics->data)), sizeof(frame_statistics_txrx));
		bzero((void*)(&(curr_statistics->mgmt)), sizeof(frame_statistics_txrx));

		// Do not remove the entry if it is associated
		if(curr_statistics->is_associated == 0){
			dl_entry_remove(stat_tbl, curr_statistics_entry);
			wlan_mac_high_free(curr_statistics);
			wlan_mac_high_free(curr_statistics_entry);
		}
	}
}



/**
 * @brief Update transmit statistics
 *
 * Function will update the transmit statistics for the given MPDU
 *
 * @param  tx_frame_info * tx_mpdu
 *     - Pointer to the TX MPDU that we will use to update the statistics
 * @return None
 */
void wlan_mac_high_update_tx_statistics(tx_frame_info* tx_mpdu, station_info* station) {
	void*                  mpdu                    = (u8*)tx_mpdu + PHY_TX_PKT_BUF_MPDU_OFFSET;
	frame_statistics_txrx* frame_stats             = NULL;

	u8 			           pkt_type;

	if(station != NULL){
	    // Get the packet type
		pkt_type = wlan_mac_high_pkt_type(mpdu, tx_mpdu->length);

		switch(pkt_type){
			case PKT_TYPE_DATA_ENCAP_ETH:
			case PKT_TYPE_DATA_ENCAP_LTG:
				frame_stats = &(station->stats->data);
			break;

			case PKT_TYPE_MGMT:
				frame_stats = &(station->stats->mgmt);
			break;
		}

		// Update Transmission Stats
		if(frame_stats != NULL){

			(frame_stats->tx_num_packets_total)++;

			(frame_stats->tx_num_bytes_total) += (tx_mpdu->length);
			(frame_stats->tx_num_packets_low) += (tx_mpdu->short_retry_count); //TODO: Needs to be fixed for short/long

			if((tx_mpdu->tx_result) == TX_MPDU_RESULT_SUCCESS){
				(frame_stats->tx_num_packets_success)++;
				(frame_stats->tx_num_bytes_success) += tx_mpdu->length;
			}
		}
	}
}



#ifdef _DEBUG_

/**
 * @brief CDMA vs CPU copy performance comparison
 *
 * @param  None
 * @return None
 */
void wlan_mac_high_copy_comparison(){

	#define MAXLEN 10000

	u32 d_cdma;
	u32 d_memcpy;
	u8  isMatched_memcpy;
	u8  isMatched_cdma;

	u32 i;
	u32 j;
	u8* srcAddr = (u8*)RX_PKT_BUF_TO_ADDR(0);
	u8* destAddr = (u8*)DDR3_BASEADDR;
	//u8* destAddr = (u8*)TX_PKT_BUF_TO_ADDR(1);
	u64 t_start;
	u64 t_end;

	xil_printf("--- MEMCPY vs. CDMA Speed Comparison ---\n");
	xil_printf("LEN, T_MEMCPY, T_CDMA, MEMCPY Match?, CDMA Match?\n");
	for(i=0; i<MAXLEN; i++){
		memset(destAddr,0,MAXLEN);
		t_start = get_usec_timestamp();
		memcpy(destAddr,srcAddr,i+1);
		t_end = get_usec_timestamp();
		d_memcpy = (u32)(t_end - t_start);

		isMatched_memcpy = 1;
		for(j=0; j<i; j++){
			if(srcAddr[j] != destAddr[j]){
				isMatched_memcpy = 0;
			}
		}

		memset(destAddr,0,MAXLEN);

		t_start = get_usec_timestamp();
		wlan_mac_high_cdma_start_transfer((void*)destAddr,(void*)srcAddr,i+1);
		//wlan_mac_high_cdma_finish_transfer();
		t_end = get_usec_timestamp();
		wlan_mac_high_clear_debug_gpio(0x04);
		d_cdma = (u32)(t_end - t_start);

		isMatched_cdma = 1;
		for(j=0; j<i; j++){
			if(srcAddr[j] != destAddr[j]){
				isMatched_cdma = 0;
			}
		}
		xil_printf("%d, %d, %d, %d, %d\n", i+1, d_memcpy, d_cdma, isMatched_memcpy, isMatched_cdma);
	}
}



/**
 * @brief Print Hardware Information
 *
 * This function stops the interrupt controller, effectively pausing interrupts. This can
 * be used alongside wlan_mac_high_interrupt_start() to wrap code that is not interrupt-safe.
 *
 * @param wlan_mac_hw_info* info
 *  - pointer to the hardware info struct that should be printed
 * @return None
 *
 */
void wlan_mac_high_print_hw_info( wlan_mac_hw_info * info ) {
	int i;

	xil_printf("WLAN MAC HW INFO:  \n");
	xil_printf("  Type             :  0x%8x\n", info->type);
	xil_printf("  Serial Number    :  %d\n",    info->serial_number);
	xil_printf("  FPGA DNA         :  0x%8x  0x%8x\n", info->fpga_dna[1], info->fpga_dna[0]);
	xil_printf("  WLAN EXP ETH Dev :  %d\n",    info->wn_exp_eth_device);

	xil_printf("  WLAN EXP HW Addr :  %02x",    info->hw_addr_wn[0]);
	for( i = 1; i < WLAN_MAC_ETH_ADDR_LEN; i++ ) {
		xil_printf(":%02x", info->hw_addr_wn[i]);
	}
	xil_printf("\n");

	xil_printf("  WLAN HW Addr     :  %02x",    info->hw_addr_wlan[0]);
	for( i = 1; i < WLAN_MAC_ETH_ADDR_LEN; i++ ) {
		xil_printf(":%02x", info->hw_addr_wlan[i]);
	}
	xil_printf("\n");

	xil_printf("END \n");
}



/**
 * @brief Pretty print a buffer of u8
 *
 * @param  u8 * buf
 *     - Buffer to be printed
 * @param  u32 size
 *     - Number of bytes to be printed
 * @return None
 */
void print_buf(u8 *buf, u32 size) {
	u32 i;
	for (i=0; i<size; i++) {
        xil_printf("%2x ", buf[i]);
        if ( (((i + 1) % 16) == 0) && ((i + 1) != size) ) {
            xil_printf("\n");
        }
	}
	xil_printf("\n\n");
}

#endif




