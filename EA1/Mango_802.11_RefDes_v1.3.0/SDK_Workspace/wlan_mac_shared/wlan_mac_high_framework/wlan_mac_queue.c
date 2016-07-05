/** @file wlan_mac_queue.c
 *  @brief Transmit Queue Framework
 *
 *  This contains code for accessing the transmit queue.
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

#include "xil_types.h"
#include "stdlib.h"
#include "stdio.h"
#include "xparameters.h"
#include "xintc.h"
#include "string.h"

#include "wlan_mac_ipc_util.h"
#include "wlan_mac_high.h"
#include "wlan_mac_queue.h"
#include "wlan_mac_dl_list.h"
#include "wlan_mac_eth_util.h"

#include "wlan_exp_common.h"


//This list holds all of the empty, free elements
static dl_list               queue_free;

//This queue_tx vector will get filled in with elements from the queue_free list
//Note: this implementation sparsely packs the queue_tx array to allow fast
//indexing at the cost of some wasted memory. The queue_tx array will be
//reallocated whenever the upper-level MAC asks to enqueue at an index
//that is larger than the current size of the array. It is assumed that this
//index will not continue to grow over the course of execution, otherwise
//this array will continue to grow and eventually be unable to be reallocated.
//Practically speaking, this means an AP needs to re-use the AIDs it issues
//stations if it wants to use the AIDs as an index into the tx queue.
static dl_list*              queue_tx;
static u16                   num_queue_tx;

extern function_ptr_t        tx_poll_callback;             ///< User callback when higher-level framework is ready to send a packet to low

volatile static u32          num_tx_queue;


void queue_init(u8 dram_present){
	u32 i;
	//The number of Tx Queue elements we can initialize is limited by the smaller of two values:
	//	(1) The number of dl_entry structs we can squeeze into TX_QUEUE_DL_ENTRY_MEM_SIZE
	//  (2) The number of QUEUE_BUFFER_SIZE MPDU buffers we can squeeze into TX_QUEUE_BUFFER_SIZE
	num_tx_queue =  min(TX_QUEUE_DL_ENTRY_MEM_SIZE/sizeof(dl_entry), TX_QUEUE_BUFFER_SIZE/QUEUE_BUFFER_SIZE );

	if(dram_present != 1){
		xil_printf("A working DRAM SODIMM has not been detected on this board.\n");
		xil_printf("DRAM is required for the wireless transmission queue.  Halting.\n");

		wlan_mac_high_set_node_error_status(2);
		wlan_mac_high_blink_hex_display(0, 250000);
	}


	dl_list_init(&queue_free);
	bzero((void*)TX_QUEUE_BUFFER_BASE, TX_QUEUE_BUFFER_SIZE);

	//At boot, every dl_entry buffer descriptor is free
	//To set up the doubly linked list, we exploit the fact that we know the starting state is sequential.
	//This matrix addressing is not safe once the queue is used. The insert/remove helper functions should be used
	dl_entry* dl_entry_base;
	dl_entry_base = (dl_entry*)(TX_QUEUE_DL_ENTRY_MEM_BASE);

	for(i=0;i<num_tx_queue;i++){
		dl_entry_base[i].data = (void*)(TX_QUEUE_BUFFER_BASE + (i*QUEUE_BUFFER_SIZE));
		dl_entry_insertEnd(&queue_free,&(dl_entry_base[i]));
	}

	xil_printf("Tx Queue of %d placed in DRAM: using %d kB\n", num_tx_queue, (num_tx_queue*QUEUE_BUFFER_SIZE)/1024);

	num_queue_tx = 0;
	queue_tx     = NULL;
	return;
}

/**
 * @return Total number of queue entries; sum of all free and occupied entries
 */
int queue_total_size(){
	return num_tx_queue;
}

/**
 * @brief Flushes the contents of the selected queue
 *
 * Purges all entries from the selected queue and returns them to the free pool. Packets contained
 * in the purged entries will be dropped. This function should only be called when enqueued packets
 * should no longer be transmitted wirelessly, such as when a node leaves a BSS.
 *
 * @param u16 queue_sel
 *  -ID of the queue to purge
 */
void purge_queue(u16 queue_sel){
	u32             num_queued;
	u32			    i;
	tx_queue_element* curr_tx_queue_element;
	interrupt_state_t prev_interrupt_state;

	// The queue purge is not interrupt safe
	prev_interrupt_state = wlan_mac_high_interrupt_stop();

	num_queued = queue_num_queued(queue_sel);

	if( num_queued > 0 ){
		wlan_exp_printf(WLAN_EXP_PRINT_INFO, print_type_queue, "Purging %d packets from queue %d\n", num_queued, queue_sel);

		for(i = 0; i < num_queued; i++){
			curr_tx_queue_element = dequeue_from_head(queue_sel);
			queue_checkin(curr_tx_queue_element);
		}
	}

	// Re-enable interrupts now that we are done
	wlan_mac_high_interrupt_restore_state(prev_interrupt_state);
}

/**
 * @brief Adds a queue entry to a specified queue
 *
 * Adds the queue entry pointed to by tqe to the queue with ID queue_sel. The calling context must ensure
 * tqe points to a queue entry containing a packet ready for wireless transmission. If a queue with ID quele_sel
 * does not already exist this function will create it, then add tqe to the new queue.
 *
 * @param u16 queue_sel
 *  -ID of the queue to which tqe is added. A new queue with ID queue_sel will be created if it does not already exist.
 * @param tx_queue_element* tqe
 *  -Queue entry containing packet for transmission
 */
void enqueue_after_tail(u16 queue_sel, tx_queue_element* tqe){
	u32 i;

	//Create queues up to and including queue_sel if they don't already exist
	// Queue IDs are low-valued integers, allowing for fast lookup by indexing the queue_tx array
	if((queue_sel+1) > num_queue_tx){
    	queue_tx = wlan_mac_high_realloc(queue_tx, (queue_sel+1)*sizeof(dl_list));

    	if(queue_tx == NULL){
    		wlan_exp_printf(WLAN_EXP_PRINT_ERROR, print_type_queue, "Could not reallocate %d bytes for queue %d\n", (queue_sel+1)*sizeof(dl_list), queue_sel);
    	}

    	for(i = num_queue_tx; i <= queue_sel; i++){
    		dl_list_init(&(queue_tx[i]));
    	}

    	num_queue_tx = queue_sel+1;
    }

	//Insert the queue entry into the dl_list representing the selected queue
	dl_entry_insertEnd(&(queue_tx[queue_sel]), (dl_entry*)tqe);

	tx_poll_callback();

	return;
}

/**
 * @brief Removes the head entry from the specified queue
 *
 * If queue_sel is not empty this function returns a tx_queue_element pointer for the head
 * entry in the queue. If the specified queue is empty this function returns NULL.
 *
 * @param u16 queue_sel
 *  -ID of the queue from which to dequeue an entry
 * @return
 *  -Pointer to queue entry if available, NULL if queue is empty
 */
tx_queue_element* dequeue_from_head(u16 queue_sel){
	tx_queue_element* tqe;
	dl_entry* curr_dl_entry;

	if((queue_sel+1) > num_queue_tx){
		//The specified queue does not exist; this can happen if a node has associated (has a valid AID=queue_sel)
		// but no packet has ever been enqueued to it, as queues are created upon first insertion - see enqueue_after_tail()
		return NULL;
	} else {
		if(queue_tx[queue_sel].length == 0){
			//Requested queue exists but is empty
			return NULL;
		} else {
			curr_dl_entry = (queue_tx[queue_sel].first);
			dl_entry_remove(&queue_tx[queue_sel],curr_dl_entry);
			tqe = (tx_queue_element*)curr_dl_entry;
			return tqe;
		}
	}
}

/**
 * @return Number of queue entries in the free pool
 */
u32 queue_num_free(){
	return queue_free.length;
}

/**
 * @param u16 queue_sel ID of queue
 * @return Number of entries in the specified queue
 */
u32 queue_num_queued(u16 queue_sel){
	if((queue_sel+1) > num_queue_tx){
		return 0;
	} else {
		return queue_tx[queue_sel].length;
	}
}

/**
 * @brief Checks out one queue entry from the free pool
 *
 * The queue framework maintains a pool of free queue entries. This function removes one entry
 * from the free pool and returns it for use by the MAC application. If the free pool is empty
 * NULL is returned.
 *
 * @return New queue entry, NULL if none is available
 */
tx_queue_element* queue_checkout(){
	tx_queue_element* tqe;

	if(queue_free.length > 0){
		tqe = ((tx_queue_element*)(queue_free.first));
		dl_entry_remove(&queue_free,queue_free.first);
		((tx_queue_buffer*)(tqe->data))->metadata.metadata_type = QUEUE_METADATA_TYPE_IGNORE;
		return tqe;
	} else {
		return NULL;
	}
}

/**
 * @brief Checks out one queue entry from the free pool
 *
 * The queue framework maintains a pool of free queue entries. This function returns one entry
 * to the free pool. tqe must be a valid pointer to a queue entry which the MAC application no
 * longer needs. The application must not use the entry pointed to by tqe after calling this function.
 *
 * @param tx_queue_element* tqe Pointer to queue entry to be returned to free pool
 *
 * @return New queue entry, NULL if none is available
 */
void queue_checkin(tx_queue_element* tqe){
	dl_entry_insertEnd(&queue_free,(dl_entry*)tqe);
	return;
}


/**
 * @brief Checks out multiple queue entries from the free pool
 *
 * The queue framework maintains a pool of free queue entries. This function attempts to check out
 * num_tqe queue entries from the free pool. The number of queue entries successfully checked out
 * is returned. This may be less than requested if the free pool had fewer than num_tqe entries
 * available.
 *
 * @param dl_list* new_list Pointer to doubly linked list to which new queue entries are appended.
 * @param u16 num_tqe Number of queue entries requested
 *
 * @return Number of queue entries successfully checked out and appended to new_list
 */
int queue_checkout_list(dl_list* new_list, u16 num_tqe){
	//Checks out up to num_packet_bd number of packet_bds from the free list. If num_packet_bd are not free,
	//then this function will return the number that are free and only check out that many.

	u32 i,num_checkout;
	dl_entry* curr_dl_entry;

	if(num_tqe <= queue_free.length){
		num_checkout = num_tqe;
	} else {
		num_checkout = queue_free.length;
	}

	//Traverse the queue_free and update the pointers
	for (i=0;i<num_checkout;i++){
		curr_dl_entry = (queue_free.first);

		//Remove from free list
		dl_entry_remove(&queue_free,curr_dl_entry);
		//Add to new checkout list
		dl_entry_insertEnd(new_list,curr_dl_entry);
	}
	return num_checkout;
}



/**
 * @brief Dequeues one packet and submits it the lower MAC for wireless transmission
 *
 * This function is the link between the Tx queue framework and the lower-level MAC. The calling
 * function has determined the next wireless transmission should come from the queue with ID queue_sel.
 * This function attempts to checkout 1 packet from that queue. If a packet is available it is
 * passed to wlan_mac_high_mpdu_transmit(), which handles the actual copy-to-pkt-buf and Tx process.
 *
 * When a packet is successfully de-queued and submitted for transmission the corresponding queue entry
 * (tx_queue_element) is returned to the free pool.
 *
 * This function returns 0 if no packets are available in the requested queue or if the MAC state machine
 * is not ready to submit a new packet to the lower MAC for transmission.
 *
 * @param u16 queue_sel Queue ID from which to dequeue packet
 *
 * @return Number of successfully transmitted packets (0 or 1)
 */
inline int dequeue_transmit_checkin(u16 queue_sel){
	int return_value = 0;
	int tx_pkt_buf = -1;
	tx_queue_element* curr_tx_queue_element;

	tx_pkt_buf = wlan_mac_high_lock_new_tx_packet_buffer();

	if(tx_pkt_buf != -1){
		curr_tx_queue_element = dequeue_from_head(queue_sel);

		if(curr_tx_queue_element != NULL){
			return_value = 1;
			wlan_mac_high_mpdu_transmit(curr_tx_queue_element, tx_pkt_buf);
			queue_checkin(curr_tx_queue_element);
			wlan_eth_dma_update();
		} else {
			wlan_mac_high_release_tx_packet_buffer(tx_pkt_buf);
		}
	}
	return return_value;
}
