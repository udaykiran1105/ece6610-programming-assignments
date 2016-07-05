/** @file wlan_mac_mgmt_tags.h
 *  @brief Tagged Parameters in Management Packets
 *
 *  This contains definitions for creating and parsing tagged parameter
 *  fields in management frames.
 *
 *  @copyright Copyright 2015, Mango Communications. All rights reserved.
 *          Distributed under the Mango Communications Reference Design License
 *				See LICENSE.txt included in the design archive or
 *				at http://mangocomm.com/802.11/license
 *
 *  @author Chris Hunter (chunter [at] mangocomm.com)
 *  @author Patrick Murphy (murphpo [at] mangocomm.com)
 *  @author Erik Welsh (welsh [at] mangocomm.com)
 */

#ifndef WLAN_MAC_MGMT_TAGS_H_
#define WLAN_MAC_MGMT_TAGS_H_

typedef struct{
	u8 tag_element_id;
	u8 tag_length;
} mgmt_tag_header;

// Note: mgmt_tag_template should never be instantiated. Instead,
// it should be used as pointer on top of existing memory
typedef struct{
	mgmt_tag_header header;
	u8				data[256];
} mgmt_tag_template;

typedef struct __attribute__ ((__packed__)){
	u16		ht_capabilities_info;
	u8		a_mpdu_parameters;
	u32     rx_supported_mcs[4];
	u16		ht_extended_capabilities;
	u32		tx_beamforming;
	u8		ant_sel;
} ht_capabilities;

typedef struct __attribute__ ((__packed__)){
	u8		channel;
	u8		ht_info_subset_1;
	u16		ht_info_subset_2;
	u16		ht_info_subset_3;
	u32		rx_supported_mcs[4];
} ht_information;

// Tag Element IDs from Table 8-54 in 802.11-2012
#define MGMT_TAG_SSID									0
#define MGMT_TAG_SUPPORTED_RATES						1
#define MGMT_TAG_FH_PARAMETER_SET						2
#define MGMT_TAG_DSSS_PARAMETER_SET						3
#define MGMT_TAG_CF_PARAMETER_SET						4
#define MGMT_TAG_TIM									5
#define MGMT_TAG_IBSS_PARAMETER_SET						6
#define MGMT_TAG_COUNTRY								7
#define MGMT_TAG_HOPPING_PATTERN_PARAMETERS				8
#define MGMT_TAG_HOPPING_PATTERN_TABLE					9
#define MGMT_TAG_REQUEST								10
#define MGMT_TAG_BSS_LOAD								11
#define MGMT_TAG_EDCA_PARAMETER_SET						12
#define MGMT_TAG_TSPEC									13
#define MGMT_TAG_TCLAS									14
#define MGMT_TAG_SCHEDULE								15
#define MGMT_TAG_CHALLENGE_TEXT							16
//			RESERVED									17-31
#define MGMT_TAG_POWER_CONSTRAINT						32
#define MGMT_TAG_POWER_CAPABILITY						33
#define MGMT_TAG_TPC_REQUEST							34
#define MGMT_TAG_TPC_REPORT								35
#define MGMT_TAG_SUPPORTED_CHANNELS						36
#define MGMT_TAG_CHANNEL_SWITCH_ANNOUNCEMENT			37
#define MGMT_TAG_MEASUREMENT_REQUEST					38
#define MGMT_TAG_MEASUREMENT_REPORT						39
#define MGMT_TAG_QUIET									40
#define MGMT_TAG_IBSS_DFS								41
#define MGMT_TAG_ERP									42
#define MGMT_TAG_TS_DELAY								43
#define MGMT_TAG_TCLAS_PROCESSING						44
#define MGMT_TAG_HT_CAPABILITIES						45
#define MGMT_TAG_QOS_CAPABILITY							46
//			RESERVED									47
#define MGMT_TAG_RSN									48
//			RESERVED									49
#define MGMT_TAG_EXTENDED_SUPPORTED_RATES				50
#define MGMT_TAG_AP_CHANNEL_REPORT						51
#define MGMT_TAG_NEIGHBOR_REPORT						52
#define MGMT_TAG_RCPI									53
#define MGMT_TAG_MOBILITY_DOMAIN_MDE					54
#define MGMT_TAG_FAST_BSS_TRANSITION_FTE				55
#define MGMT_TAG_TIMEOUT_INTERVAL						56
#define MGMT_TAG_RIC_DATA_RDE							57
#define MGMT_TAG_DSE_REGISTERED_LOCATION				58
#define MGMT_TAG_SUPPORTED_OPERATING_CLASSES			59
#define MGMT_TAG_EXTENDED_CHANNEL_SWITCH_ANNOUNCEMENT	60
#define MGMT_TAG_HT_OPERATION							61
#define MGMT_TAG_SECONDARY_CHANNEL_OFFSET				62
#define MGMT_TAG_BSS_AVERAGE_ACCESS_DELAY				63
#define MGMT_TAG_ANTENNA								64
#define MGMT_TAG_RSNI									65
#define MGMT_TAG_MEASUREMENT_PILOT_TRANSMISSION			66
#define MGMT_TAG_BSS_AVAILABILITY_ADMISSION_CAPACITY	67
#define MGMT_TAG_BSS_AC_ACCESS_DELAY					68
#define MGMT_TAG_TIME_ADVERTISEMENT						69
#define MGMT_TAG_RM_ENABLED_CAPABILITIES				70
#define MGMT_TAG_MULTIPLE_BSSID							71
#define MGMT_TAG_20_40_BSS_COEXISTENCE					72
#define MGMT_TAG_20_40_BSS_INTOLERANT_CHANNEL_REPORT	73
#define MGMT_TAG_OVERLAPPING_BSS_SCAN_PARAMETERS		74
#define MGMT_TAG_RIC_DESCRIPTOR							75
#define MGMT_TAG_MANAGEMENT_MIC							76
//			RESERVED									77
#define MGMT_TAG_EVENT_REQUEST							78
#define MGMT_TAG_EVENT_REPORT							79
#define MGMT_TAG_DIAGNOSTIC_REQUEST						80
#define MGMT_TAG_DIAGNOSTIC_REPORT						81
#define MGMT_TAG_LOCATION_PARAMETERS					82
#define MGMT_TAG_NONTRANSMITTED_BSSID_CAPABILITY		83
#define MGMT_TAG_SSID_LIST								84
#define MGMT_TAG_MULTIPLE_BSSID_INDEX					85
#define MGMT_TAG_FMS_DESCRIPTOR							86
#define MGMT_TAG_FMS_REQUEST							87
#define MGMT_TAG_FMS_RESPONSE							88
#define MGMT_TAG_QOS_TRAFFIC_CAPABILITY					89
#define MGMT_TAG_BSS_MAX_IDLE_PERIOD					90
#define MGMT_TAG_TFS_REQUEST							91
#define MGMT_TAG_RFS_RESPONSE							92
#define MGMT_TAG_WNM_SLEEP_MODE							93
#define MGMT_TAG_TIM_BROADCAST_REQUEST					94
#define MGMT_TAG_TIM_BROADCAST_RESPONSE					95
#define MGMT_TAG_COLLOCATED_INTERFERENCE_REPORT			96
#define MGMT_TAG_CHANNEL_USAGE							97
#define MGMT_TAG_TIME_ZONE								98
#define MGMT_TAG_DMS_REQUEST							99
#define MGMT_TAG_DMS_RESPONSE							100
#define MGMT_TAG_LINK_IDENTIFIER						101
#define MGMT_TAG_WAKEUP_SCHEDULE						102
//			RESERVED									103
#define MGMT_TAG_CHANNEL_SWITCH_TIMING					104
#define MGMT_TAG_PTI_CONTROL							105
#define MGMT_TAG_TPU_BUFFER_STATUS						106
#define MGMT_TAG_INTERWORKING							107
#define MGMT_TAG_ADVERTISEMENT_PROTOCOL					108
#define MGMT_TAG_EXPECTED_BANDWIDTH_REQUEST				109
#define MGMT_TAG_QOS_MAP_SET							110
#define MGMT_TAG_ROAMING_CONSORTIUM						111
#define MGMT_TAG_EMERGENCY_ALERT_IDENTIFIER				112
#define MGMT_TAG_MESH_CONFIGURATION						113
#define MGMT_TAG_MESH_ID								114
#define MGMT_TAG_MESH_LINK_METRIC_REPORT				115
#define MGMT_TAG_CONGESTION_NOTIFICATION				116
#define MGMT_TAG_MESH_PEERING_MANAGEMENT				117
#define MGMT_TAG_MESH_CHANNEL_SWITCH_PARAMETERS			118
#define MGMT_TAG_MESH_AWAKE_WINDOWS						119
#define MGMT_TAG_BEACON_TIMING							120
#define MGMT_TAG_MCCAOP_SETUP_REQUEST					121
#define MGMT_TAG_MCCAOP_SETUP_REPLY						122
#define MGMT_TAG_MCCAOP_ADVERTISEMENT					123
#define MGMT_TAG_MCCAOP_TEARDOWN						124
#define MGMT_TAG_GANN									125
#define MGMT_TAG_RANN									126
#define MGMT_TAG_EXTENDED_CAPABILITIES					127
//			RESERVED									128-129
#define MGMT_TAG_PREQ									130
#define MGMT_TAG_PREP									131
#define MGMT_TAG_PERR									132
//			RESERVED									133-136
#define MGMT_TAG_PXU									137
#define MGMT_TAG_PXUC									138
#define MGMT_TAG_AUTHENTICATED_MESH_PEERING_EXCHANGE	139
#define MGMT_TAG_MIC									140
#define MGMT_TAG_DESTINATION_URI						141
#define MGMT_TAG_U_APSD_COEXISTENCE						142
//			RESERVED									143-173
#define MGMT_TAG_MCCAOP_ADVERTISEMENT_OVERVIEW			174
//			RESERVED									175-220
#define MGMT_TAG_VENDOR_SPECIFIC						221
//			RESERVED									222-255

#endif
