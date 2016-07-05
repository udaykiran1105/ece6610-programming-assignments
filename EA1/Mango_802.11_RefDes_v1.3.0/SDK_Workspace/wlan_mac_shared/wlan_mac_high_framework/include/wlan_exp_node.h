/** @file wlan_exp_node.h
 *  @brief Experiment Framework
 *
 *  This contains the code for WARPnet Experimental Framework.
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
#include "wlan_exp_common.h"


// WLAN MAC includes for common functions
#include "wlan_mac_high.h"


/*************************** Constant Definitions ****************************/
#ifndef WLAN_EXP_NODE_H_
#define WLAN_EXP_NODE_H_



// ****************************************************************************
// Define Node Commands
//
// NOTE:  All Command IDs (CMDID_*) must be a 24 bit unique number
//

//-----------------------------------------------
// WARPNet Node Commands
//
#define CMDID_NODE_INFO                                    0x000001
#define CMDID_NODE_IDENTIFY                                0x000002

#define CMD_PARAM_NODE_IDENTIFY_ALL                        0xFFFFFFFF

#define CMDID_NODE_CONFIG_SETUP                            0x000003
#define CMDID_NODE_CONFIG_RESET                            0x000004

#define CMD_PARAM_NODE_CONFIG_RESET_ALL                    0xFFFFFFFF

#define CMDID_NODE_TEMPERATURE                             0x000005


//-----------------------------------------------
// WLAN Exp Node Commands
//
#define CMDID_NODE_RESET_STATE                             0x001000
#define CMDID_NODE_CONFIGURE                               0x001001
#define CMDID_NODE_TIME                                    0x001010
#define CMDID_NODE_CHANNEL                                 0x001011
#define CMDID_NODE_TX_POWER                                0x001012
#define CMDID_NODE_TX_RATE                                 0x001013
#define CMDID_NODE_TX_ANT_MODE                             0x001014
#define CMDID_NODE_RX_ANT_MODE                             0x001015
#define CMDID_NODE_LOW_TO_HIGH_FILTER                      0x001016
#define CMDID_NODE_RANDOM_SEED                             0x001017
#define CMDID_NODE_WLAN_MAC_ADDR                           0x001018
#define CMDID_NODE_LOW_PARAM				               0x001020

#define CMD_PARAM_WRITE_VAL                                0x00000000
#define CMD_PARAM_READ_VAL                                 0x00000001
#define CMD_PARAM_WRITE_DEFAULT_VAL                        0x00000002
#define CMD_PARAM_READ_DEFAULT_VAL                         0x00000004
#define CMD_PARAM_RSVD                                     0xFFFFFFFF

#define CMD_PARAM_SUCCESS                                  0x00000000
#define CMD_PARAM_ERROR                                    0xFF000000

#define CMD_PARAM_UNICAST_VAL                              0x00000000
#define CMD_PARAM_MULTICAST_DATA_VAL                       0x00000001
#define CMD_PARAM_MULTICAST_MGMT_VAL                       0x00000002

#define CMD_PARAM_NODE_CONFIG_ALL                          0xFFFFFFFF

#define CMD_PARAM_NODE_RESET_FLAG_LOG                      0x00000001
#define CMD_PARAM_NODE_RESET_FLAG_TXRX_STATS               0x00000002
#define CMD_PARAM_NODE_RESET_FLAG_LTG                      0x00000004
#define CMD_PARAM_NODE_RESET_FLAG_TX_DATA_QUEUE            0x00000008
#define CMD_PARAM_NODE_RESET_FLAG_ASSOCIATIONS             0x00000010
#define CMD_PARAM_NODE_RESET_FLAG_BSS_INFO                 0x00000020

#define CMD_PARAM_NODE_CONFIG_FLAG_DSSS_ENABLE             0x00000001
#define CMD_PARAM_NODE_CONFIG_SET_WLAN_EXP_PRINT_LEVEL     0x80000000

#define CMD_PARAM_NODE_TIME_ADD_TO_LOG_VAL                 0x00000002
#define CMD_PARAM_NODE_TIME_RSVD_VAL                       0xFFFFFFFF
#define CMD_PARAM_NODE_TIME_RSVD_VAL_64                    0xFFFFFFFFFFFFFFFF

#define CMD_PARAM_NODE_TX_POWER_LOW                        0x00000010
#define CMD_PARAM_NODE_TX_POWER_ALL                        0x00000020

#define CMD_PARAM_RSVD_CHANNEL                             0x00000000
#define CMD_PARAM_RSVD_MAC_ADDR                            0xFFFFFFFF

#define CMD_PARAM_RANDOM_SEED_VALID                        0x00000001
#define CMD_PARAM_RANDOM_SEED_RSVD                         0xFFFFFFFF


//-----------------------------------------------
// LTG Commands
//
#define CMDID_LTG_CONFIG                                   0x002000
#define CMDID_LTG_START                                    0x002001
#define CMDID_LTG_STOP                                     0x002002
#define CMDID_LTG_REMOVE                                   0x002003
#define CMDID_LTG_STATUS                                   0x002004

#define CMD_PARAM_LTG_ERROR                                0x000001

#define CMD_PARAM_LTG_CONFIG_FLAG_AUTOSTART                0x00000001

#define CMD_PARAM_LTG_ALL_LTGS                             LTG_ID_INVALID

#define CMD_PARAM_LTG_RUNNING                              0x00000001
#define CMD_PARAM_LTG_STOPPED                              0x00000000


//-----------------------------------------------
// Log Commands
//
#define CMDID_LOG_CONFIG                                   0x003000
#define CMDID_LOG_GET_STATUS                               0x003001
#define CMDID_LOG_GET_CAPACITY                             0x003002
#define CMDID_LOG_GET_ENTRIES                              0x003003
#define CMDID_LOG_ADD_EXP_INFO_ENTRY                       0x003004
#define CMDID_LOG_ADD_STATS_TXRX                           0x003005
#define CMDID_LOG_ENABLE_ENTRY                             0x003006
#define CMDID_LOG_STREAM_ENTRIES                           0x003007

#define CMD_PARAM_LOG_GET_ALL_ENTRIES                      0xFFFFFFFF

#define CMD_PARAM_LOG_CONFIG_FLAG_LOGGING                  0x00000001
#define CMD_PARAM_LOG_CONFIG_FLAG_WRAP                     0x00000002
#define CMD_PARAM_LOG_CONFIG_FLAG_PAYLOADS                 0x00000004
#define CMD_PARAM_LOG_CONFIG_FLAG_WN_CMDS                  0x00000008
#define CMD_PARAM_LOG_CONFIG_FLAG_TXRX_MPDU                0x00000010
#define CMD_PARAM_LOG_CONFIG_FLAG_TXRX_CTRL                0x00000020


//-----------------------------------------------
// Statistics Commands
//
#define CMDID_STATS_CONFIG_TXRX                            0x004000
#define CMDID_STATS_GET_TXRX                               0x004001

#define CMD_PARAM_STATS_CONFIG_FLAG_PROMISC                0x00000001
#define CMD_PARAM_STATS_RETURN_ZEROED_IF_NONE              0x80000000


//-----------------------------------------------
// Queue Commands
//
#define CMDID_QUEUE_TX_DATA_PURGE_ALL                      0x005000


//-----------------------------------------------
// Association Commands
//
#define CMDID_NODE_GET_SSID                                0x006000
#define CMDID_NODE_GET_STATION_INFO                        0x006001
#define CMDID_NODE_GET_BSS_INFO                            0x006002

#define CMDID_NODE_DISASSOCIATE                            0x006010
#define CMDID_NODE_ASSOCIATE                               0x006011


//-----------------------------------------------
// Common Commands for STA / IBSS
//
#define CMDID_NODE_SCAN_PARAM                              0x007000
#define CMDID_NODE_SCAN                                    0x007001
#define CMDID_NODE_JOIN                                    0x007002
#define CMDID_NODE_SCAN_AND_JOIN                           0x007003

#define CMD_PARAM_NODE_SCAN_ENABLE                         0x00000001
#define CMD_PARAM_NODE_SCAN_DISABLE                        0x00000000

#define CMD_PARAM_NODE_JOIN_SUCCEEDED                      0x00000000
#define CMD_PARAM_NODE_JOIN_FAILED                         0xFFFFFFFF


//-----------------------------------------------
// Development Commands
//
#define CMDID_DEV_MEM_HIGH                                 0xFFF000
#define CMDID_DEV_MEM_LOW                                  0xFFF001



// ****************************************************************************
// WLAN Exp Defines
//
#define WLAN_EXP_AID_NONE                                  0x00000000
#define WLAN_EXP_AID_ALL                                   0xFFFFFFFF
#define WLAN_EXP_AID_ME                                    0xFFFFFFFE
#define WLAN_EXP_AID_DEFAULT                               0x00000001


// ****************************************************************************
// Define Node Hardware Parameters
//   - NOTE:  To add another parameter, add the define before "NODE_MAX_PARAMETER"
//     and then change the value of "NODE_MAX_PARAMETER" to be the largest value
//     in the list so it is easy to iterate over all parameters
//
#define NODE_TYPE                                          0
#define NODE_ID                                            1
#define NODE_HW_GEN                                        2
#define NODE_DESIGN_VER                                    3
#define NODE_FPGA_DNA                                      4
#define NODE_SERIAL_NUM                                    5
#define NODE_WLAN_EXP_DESIGN_VER                           6
#define NODE_WLAN_MAC_ADDR                                 7
#define NODE_WLAN_SCHEDULER_RESOLUTION                     8
#define NODE_MAX_PARAMETER                                 9



/*********************** Global Structure Definitions ************************/

// **********************************************************************
// WARPNet Node Info Structure
//
typedef struct {

    u32   type;                             // Type of WARPNet node
    u32   node;                             // Only first 16 bits are valid
    u32   hw_generation;                    // Only first  8 bits are valid
	u32   warpnet_design_ver;               // Only first 24 bits are valid

	u32   fpga_dna[FPGA_DNA_LEN];
	u32   serial_number;

	u32   wlan_exp_design_ver;              // WLAN Exp - Version (only first 24 bits are valid)
    u32   wlan_hw_addr[2];                  // WLAN Exp - Wireless MAC address
	u32   wlan_scheduler_resolution;        // WLAN Exp - Minimum Scheduler resolution

    u32   eth_device;
    u8    hw_addr[ETH_ADDR_LEN];
    u8    ip_addr[IP_VERSION];
    u32   unicast_port;
    u32   broadcast_port;

} wn_node_info;



/*************************** Function Prototypes *****************************/

// WLAN Exp node commands
//
int  wlan_exp_node_init(u32 type, u32 serial_number, u32 *fpga_dna, u32 eth_dev_num, u8 *hw_addr, u8 *wlan_hw_addr);

void wlan_exp_reset_all_callbacks();
void wlan_exp_set_process_callback(void(*callback)());
void wlan_exp_set_init_callback(void(*callback)());
void wlan_exp_set_reset_station_statistics_callback(void(*callback)());
void wlan_exp_set_purge_all_data_tx_queue_callback(void(*callback)());
void wlan_exp_set_reset_all_associations_callback(void(*callback)());
void wlan_exp_set_reset_bss_info_callback(void(*callback)());
void wlan_exp_set_timebase_adjust_callback(void(*callback)());
void wlan_exp_set_tx_cmd_add_association_callback(void(*callback)());

int  node_get_parameters(u32 * buffer, unsigned int max_words, unsigned char network);
int  node_get_parameter_values(u32 * buffer, unsigned int max_words);

void node_info_set_wlan_hw_addr  ( u8 * hw_addr  );
void node_info_set_max_assn      ( u32 max_assn  );
void node_info_set_event_log_size( u32 log_size  );
void node_info_set_max_stats     ( u32 max_stats );

u32  wn_get_node_id       ( void );
u32  wn_get_serial_number ( void );
u32  wn_get_curr_temp     ( void );
u32  wn_get_min_temp      ( void );
u32  wn_get_max_temp      ( void );

#endif /* WLAN_EXP_NODE_H_ */
