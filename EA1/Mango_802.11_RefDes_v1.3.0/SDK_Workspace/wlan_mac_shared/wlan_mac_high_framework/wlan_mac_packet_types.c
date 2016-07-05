/** @file wlan_mac_packet_types.c
 *  @brief Packet Constructors
 *
 *  This contains code for constructing a variety of different types of MPDUs.
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

//Xilinx SDK includes
#include "stdio.h"
#include "stdlib.h"
#include "xio.h"
#include "string.h"
#include "xil_types.h"
#include "xintc.h"

//WARP includes
#include "wlan_mac_high.h"
#include "wlan_mac_ipc_util.h"
#include "wlan_mac_802_11_defs.h"
#include "wlan_mac_mgmt_tags.h"
#include "wlan_mac_bss_info.h"
#include "wlan_mac_packet_types.h"


int wlan_create_beacon_probe_resp_frame(u8 frame_control_1, void* pkt_buf, mac_header_80211_common* common, bss_info* my_bss_info) {

	ht_capabilities* ht_capabilities_element;
	ht_information* ht_information_element;

	//void* pkt_buf,mac_header_80211_common* common, u16 beacon_interval, u16 capabilities, u8 ssid_len, u8* ssid, u8 chan

	u32 packetLen_bytes;
	mgmt_tag_template* mgmt_tag_ptr;

	u8  real_ssid_len = min(strlen(my_bss_info->ssid), SSID_LEN_MAX);

	mac_header_80211* mac_header;
	mac_header = (mac_header_80211*)(pkt_buf);

	mac_header->frame_control_1 = frame_control_1;
	mac_header->frame_control_2 = 0;

	//This field may be overwritten by CPU_LOW
	mac_header->duration_id = 0;

	mac_header->sequence_control = 0; //Will be filled in at dequeue

	memcpy(mac_header->address_1,common->address_1,6);
	memcpy(mac_header->address_2,common->address_2,6);
	memcpy(mac_header->address_3,common->address_3,6);

	beacon_probe_frame* beacon_probe_mgmt_header;
	beacon_probe_mgmt_header = (beacon_probe_frame*)(pkt_buf + sizeof(mac_header_80211));

	//This field may be overwritten by CPU_LOW
	beacon_probe_mgmt_header->timestamp = 0;

	beacon_probe_mgmt_header->beacon_interval = my_bss_info->beacon_interval;
	beacon_probe_mgmt_header->capabilities = my_bss_info->capabilities;

	mgmt_tag_ptr = (mgmt_tag_template *)( (void *)(pkt_buf) + sizeof(mac_header_80211) + sizeof(beacon_probe_frame) );


	mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_SSID;
	mgmt_tag_ptr->header.tag_length = real_ssid_len;
	memcpy((void *)(mgmt_tag_ptr->data),my_bss_info->ssid,real_ssid_len);
	mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward


	//Top bit is whether or not the rate is mandatory (basic). Bottom 7 bits is in units of "number of 500kbps"
	mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_SUPPORTED_RATES;
	mgmt_tag_ptr->header.tag_length = 8;
	mgmt_tag_ptr->data[0] = RATE_BASIC | (0x0C); 	//6Mbps  (BPSK,   1/2)
	mgmt_tag_ptr->data[1] = (0x12);				 	//9Mbps  (BPSK,   3/4)
	mgmt_tag_ptr->data[2] = RATE_BASIC | (0x18); 	//12Mbps (QPSK,   1/2)
	mgmt_tag_ptr->data[3] = (0x24); 				//18Mbps (QPSK,   3/4)
	mgmt_tag_ptr->data[4] = RATE_BASIC | (0x30); 	//24Mbps (16-QAM, 1/2)
	mgmt_tag_ptr->data[5] = (0x48); 				//36Mbps (16-QAM, 3/4)
	mgmt_tag_ptr->data[6] = (0x60); 				//48Mbps  (64-QAM, 2/3)
	mgmt_tag_ptr->data[7] = (0x6C); 				//54Mbps  (64-QAM, 3/4)
	mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward

	if( (my_bss_info->phy_mode) & BSS_INFO_PHY_MODE_11N ){
		//Insert HT Capabilities and HT Information tags
		mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_HT_CAPABILITIES;
		mgmt_tag_ptr->header.tag_length = 26;

		ht_capabilities_element = (ht_capabilities*)mgmt_tag_ptr->data;
		ht_capabilities_element->ht_capabilities_info = 0x010c;
		ht_capabilities_element->a_mpdu_parameters = 0x00;
		ht_capabilities_element->rx_supported_mcs[0] = 0x000000ff;
		ht_capabilities_element->rx_supported_mcs[1] = 0x00000000;
		ht_capabilities_element->rx_supported_mcs[2] = 0x00000000;
		ht_capabilities_element->rx_supported_mcs[3] = 0x00000000;
		ht_capabilities_element->ht_extended_capabilities = 0x0000;
		ht_capabilities_element->tx_beamforming = 0x0000;
		ht_capabilities_element->ant_sel = 0x00;

		mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward

		mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_HT_OPERATION;
		mgmt_tag_ptr->header.tag_length = 22;

		ht_information_element = (ht_information*)mgmt_tag_ptr->data;
		ht_information_element->channel = my_bss_info->chan;
		ht_information_element->ht_info_subset_1 = 0x00;
		ht_information_element->ht_info_subset_2 = 0x0000;
		ht_information_element->ht_info_subset_3 = 0x0000;
		ht_information_element->rx_supported_mcs[0] = 0x00000000;
		ht_information_element->rx_supported_mcs[1] = 0x00000000;
		ht_information_element->rx_supported_mcs[2] = 0x00000000;
		ht_information_element->rx_supported_mcs[3] = 0x00000000;

		mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward
	}

	mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_DSSS_PARAMETER_SET;
	mgmt_tag_ptr->header.tag_length = 1; //tag length... doesn't include the tag itself and the tag length
	mgmt_tag_ptr->data[0] = my_bss_info->chan;
	mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward

	mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_ERP;
	mgmt_tag_ptr->header.tag_length = 1;
	mgmt_tag_ptr->data[0] = 0; //Non ERP Present - not set, don't use protection, no barker preamble mode
	mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward

	packetLen_bytes = ((u8*)mgmt_tag_ptr - (u8*)(pkt_buf)) + WLAN_PHY_FCS_NBYTES;

	return packetLen_bytes;

}

int wlan_create_measurement_req_frame(void* pkt_buf, mac_header_80211_common* common, u8 measurement_type, u8 chan){
	u32 packetLen_bytes;
	u8* txBufferPtr_u8;

	measurement_common_frame* measurement_req;

	txBufferPtr_u8 = (u8*)pkt_buf;

	mac_header_80211* hdr_80211;
	hdr_80211 = (mac_header_80211*)(txBufferPtr_u8);

	hdr_80211->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_ACTION;
	hdr_80211->frame_control_2 = 0;

	//This field may be overwritten by CPU_LOW
	hdr_80211->duration_id = 0;

	hdr_80211->sequence_control = 0; //Will be filled in at dequeue

	memcpy(hdr_80211->address_1,common->address_1,6);
	memcpy(hdr_80211->address_2,common->address_2,6);
	memcpy(hdr_80211->address_3,common->address_3,6);

	txBufferPtr_u8 = (u8 *)((void *)(txBufferPtr_u8) + sizeof(mac_header_80211));
	measurement_req = (measurement_common_frame*)txBufferPtr_u8;

	measurement_req->category = 0; //Spectrum management action frame
	measurement_req->action = 0; //Request
	//measurement_req->dialog_token = (common->seq_num)&0xFF; //Just a field for matching reqs and resps. We'll just use seq
	measurement_req->element_id = 38; //Measurement Req
	measurement_req->length = sizeof(measurement_common_frame) - 5; //Length of field after this element;
	measurement_req->measurement_token = 0;
	measurement_req->request_mode = MEASUREMENT_REQ_MODE_ENABLE | MEASUREMENT_REQ_MODE_REPORTS;
	measurement_req->measurement_type = measurement_type;
	measurement_req->channel = chan;
	//measurement_req->start_time = 0; //Measure now
	bzero(measurement_req->start_time,8);
	bzero(measurement_req->duration,2);
	(measurement_req->duration)[0] = 0; //Do it as fast as you can? Unclear

	txBufferPtr_u8 = (u8 *)((u8 *)(txBufferPtr_u8) + sizeof(measurement_common_frame));
	packetLen_bytes = (txBufferPtr_u8 - (u8*)(pkt_buf)) + WLAN_PHY_FCS_NBYTES;

	return packetLen_bytes;
}



int wlan_create_channel_switch_announcement_frame(void* pkt_buf, mac_header_80211_common* common, u8 channel){
	u32 packetLen_bytes;
	u8* txBufferPtr_u8;

	channel_switch_announcement_frame* chan_req;

	txBufferPtr_u8 = (u8*)pkt_buf;

	mac_header_80211* hdr_80211;
	hdr_80211 = (mac_header_80211*)(txBufferPtr_u8);

	hdr_80211->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_ACTION;
	hdr_80211->frame_control_2 = 0;

	// This field may be overwritten by CPU_LOW
	hdr_80211->duration_id = 0;

	memcpy(hdr_80211->address_1,common->address_1,6);
	memcpy(hdr_80211->address_2,common->address_2,6);
	memcpy(hdr_80211->address_3,common->address_3,6);

	hdr_80211->sequence_control = 0; //Will be filled in at dequeue

	txBufferPtr_u8 = (u8 *)((void *)(txBufferPtr_u8) + sizeof(mac_header_80211));
	chan_req = (channel_switch_announcement_frame*)txBufferPtr_u8;

	chan_req->category          = 0;             // Spectrum management action frame
	chan_req->action            = 4;             // Channel switch announcement

	chan_req->element_id        = 37;            // Channel switch announcement
	chan_req->length            = 3;             // Length
	chan_req->chan_switch_mode  = 0;             // No restrictions on transmission until a channel switch
	chan_req->new_chan_num      = channel;       // New Channel
	chan_req->chan_switch_count = 0;             // Switch occurs any time after the frame is transmitted

	txBufferPtr_u8  = (u8 *)((u8 *)(txBufferPtr_u8) + sizeof(channel_switch_announcement_frame));
	packetLen_bytes = (txBufferPtr_u8 - (u8*)(pkt_buf)) + WLAN_PHY_FCS_NBYTES;

	return packetLen_bytes;
}



int wlan_create_probe_req_frame(void* pkt_buf, mac_header_80211_common* common, u8 ssid_len, u8* ssid, u8 chan){
	u32 packetLen_bytes;
	u8* txBufferPtr_u8;
	u8  real_ssid_len = min(ssid_len, SSID_LEN_MAX);

	txBufferPtr_u8 = (u8*)pkt_buf;

	mac_header_80211* probe_req_80211_header;
	probe_req_80211_header = (mac_header_80211*)(txBufferPtr_u8);

	probe_req_80211_header->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_PROBE_REQ;
	probe_req_80211_header->frame_control_2 = 0;

	//This field may be overwritten by CPU_LOW
	probe_req_80211_header->duration_id = 0;

	memcpy(probe_req_80211_header->address_1,common->address_1,6);
	memcpy(probe_req_80211_header->address_2,common->address_2,6);
	memcpy(probe_req_80211_header->address_3,common->address_3,6);

	probe_req_80211_header->sequence_control = 0; //Will be filled in at dequeue

	txBufferPtr_u8 = (u8 *)((void *)(txBufferPtr_u8) + sizeof(mac_header_80211));
	txBufferPtr_u8[0] = 0; //Tag 0: SSID parameter set
	txBufferPtr_u8[1] = real_ssid_len;
	memcpy((void *)(&(txBufferPtr_u8[2])),(void *)(&ssid[0]),real_ssid_len);

	txBufferPtr_u8+=(real_ssid_len+2); //Move up to next tag

	//http://my.safaribooksonline.com/book/networking/wireless/0596100523/4dot-802dot11-framing-in-detail/wireless802dot112-chp-4-sect-3
	//Top bit is whether or not the rate is mandatory (basic). Bottom 7 bits is in units of "number of 500kbps"
	txBufferPtr_u8[0] = 1; //Tag 1: Supported Rates
	txBufferPtr_u8[1] = 8; //tag length... doesn't include the tag itself and the tag length
	txBufferPtr_u8[2] = (0x0C); 				//6Mbps  (BPSK,   1/2)
	txBufferPtr_u8[3] = (0x12);				 	//9Mbps  (BPSK,   3/4)
	txBufferPtr_u8[4] = (0x18); 				//12Mbps (QPSK,   1/2)
	txBufferPtr_u8[5] = (0x24); 				//18Mbps (QPSK,   3/4)
	txBufferPtr_u8[6] = (0x30); 				//24Mbps (16-QAM, 1/2)
	txBufferPtr_u8[7] = (0x48); 				//36Mbps (16-QAM, 3/4)
	txBufferPtr_u8[8] = (0x60); 				//48Mbps  (64-QAM, 2/3)
	txBufferPtr_u8[9] = (0x6C); 				//54Mbps  (64-QAM, 3/4)
	txBufferPtr_u8+=(8+2); //Move up to next tag

	txBufferPtr_u8[0] = 3; //Tag 3: DS Parameter set
	txBufferPtr_u8[1] = 1; //tag length... doesn't include the tag itself and the tag length
	txBufferPtr_u8[2] = chan;
	txBufferPtr_u8+=(1+2);

	packetLen_bytes = (txBufferPtr_u8 - (u8*)(pkt_buf)) + WLAN_PHY_FCS_NBYTES;

	return packetLen_bytes;
}



int wlan_create_auth_frame(void* pkt_buf, mac_header_80211_common* common, u16 auth_algorithm,  u16 auth_seq, u16 status_code){
	u32 packetLen_bytes;
	u8* txBufferPtr_u8;

	txBufferPtr_u8 = (u8*)pkt_buf;

	mac_header_80211* auth_80211_header;
	auth_80211_header = (mac_header_80211*)(txBufferPtr_u8);

	auth_80211_header->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_AUTH;
	auth_80211_header->frame_control_2 = 0;

	//duration can be filled in by CPU_LOW
	auth_80211_header->duration_id = 0;
	memcpy(auth_80211_header->address_1,common->address_1,6);
	memcpy(auth_80211_header->address_2,common->address_2,6);
	memcpy(auth_80211_header->address_3,common->address_3,6);

	auth_80211_header->sequence_control = 0; //Will be filled in at dequeue

	authentication_frame* auth_mgmt_header;
	auth_mgmt_header = (authentication_frame*)(pkt_buf + sizeof(mac_header_80211));
	auth_mgmt_header->auth_algorithm = auth_algorithm;
	auth_mgmt_header->auth_sequence = auth_seq;
	auth_mgmt_header->status_code = status_code;

	txBufferPtr_u8 = (u8 *)((void *)(txBufferPtr_u8) + sizeof(mac_header_80211) + sizeof(authentication_frame));

	packetLen_bytes = (txBufferPtr_u8 - (u8*)(pkt_buf)) + WLAN_PHY_FCS_NBYTES;

	return packetLen_bytes;
}



int wlan_create_deauth_frame(void* pkt_buf, mac_header_80211_common* common, u16 reason_code){
	u32 packetLen_bytes;
	u8* txBufferPtr_u8;

	txBufferPtr_u8 = (u8*)pkt_buf;

	mac_header_80211* deauth_80211_header;
	deauth_80211_header = (mac_header_80211*)(txBufferPtr_u8);

	deauth_80211_header->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_DEAUTH;
	deauth_80211_header->frame_control_2 = 0;

	//duration can be filled in by CPU_LOW
	deauth_80211_header->duration_id = 0;
	memcpy(deauth_80211_header->address_1,common->address_1,6);
	memcpy(deauth_80211_header->address_2,common->address_2,6);
	memcpy(deauth_80211_header->address_3,common->address_3,6);

	deauth_80211_header->sequence_control = 0; //Will be filled in at dequeue

	deauthentication_frame* deauth_mgmt_header;
	deauth_mgmt_header = (deauthentication_frame*)(pkt_buf + sizeof(mac_header_80211));
	deauth_mgmt_header->reason_code = reason_code;

	txBufferPtr_u8 = (u8 *)((void *)(txBufferPtr_u8) + sizeof(mac_header_80211) + sizeof(authentication_frame));

	packetLen_bytes = (txBufferPtr_u8 - (u8*)(pkt_buf)) + WLAN_PHY_FCS_NBYTES;

	return packetLen_bytes;
}



int wlan_create_reassoc_assoc_req_frame(void* pkt_buf, u8 frame_control_1, mac_header_80211_common* common, bss_info* attempt_bss_info){
	u32 packetLen_bytes;

	ht_capabilities* ht_capabilities_element;
	ht_information* ht_information_element;

	u8  real_ssid_len = min(strlen(attempt_bss_info->ssid), SSID_LEN_MAX);
	mgmt_tag_template* mgmt_tag_ptr;


	mac_header_80211* assoc_80211_header;
	assoc_80211_header = (mac_header_80211*)(pkt_buf);

	assoc_80211_header->frame_control_1 = frame_control_1;
	assoc_80211_header->frame_control_2 = 0;
	//duration can be filled in by CPU_LOW
	assoc_80211_header->duration_id = 0;

	memcpy(assoc_80211_header->address_1,common->address_1,6);
	memcpy(assoc_80211_header->address_2,common->address_2,6);
	memcpy(assoc_80211_header->address_3,common->address_3,6);

	assoc_80211_header->sequence_control = 0; //Will be filled in at dequeue

	association_request_frame* association_req_mgmt_header;
	association_req_mgmt_header = (association_request_frame*)(pkt_buf + sizeof(mac_header_80211));
	association_req_mgmt_header->capabilities = (CAPABILITIES_ESS | CAPABILITIES_SHORT_TIMESLOT | CAPABILITIES_SHORT_PREAMBLE);

	//This value is defined in 802.11-2012 in 8.4.1.6 and tells the AP how many beacon intervals
	//this station intends to doze before waking. In our implementation we hardcode this to 1
	//to represent that we will be awake at every beacon target time.
	association_req_mgmt_header->listen_interval = 0x0001;

	mgmt_tag_ptr = (mgmt_tag_template *)( (void *)(pkt_buf) + sizeof(mac_header_80211) + sizeof(association_request_frame) );


	mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_SSID;
	mgmt_tag_ptr->header.tag_length = real_ssid_len;
	memcpy((void *)(mgmt_tag_ptr->data),attempt_bss_info->ssid,real_ssid_len);
	mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward

	//Top bit is whether or not the rate is mandatory (basic). Bottom 7 bits is in units of "number of 500kbps"
	//Note: these parameters are spoofed. The 802.11 Reference Design does not support the 802.11b rates (with the exception
	//of Rx of DSSS 1Mbps). However, most commercial APs will decline a STA from joining if they don't advertise support
	//for the nominal set of 802.11b basic rates.
	mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_SUPPORTED_RATES;
	mgmt_tag_ptr->header.tag_length = 8;
	mgmt_tag_ptr->data[0] = RATE_BASIC | (0x02); 	//1Mbps
	mgmt_tag_ptr->data[1] = RATE_BASIC | (0x04);	//2Mbps
	mgmt_tag_ptr->data[2] = RATE_BASIC | (0x0B);	//5.5Mbps
	mgmt_tag_ptr->data[3] = RATE_BASIC | (0x16);	//11Mbps
	mgmt_tag_ptr->data[4] = (0x24); 				//18Mbps
	mgmt_tag_ptr->data[5] = (0x30); 				//24Mbps
	mgmt_tag_ptr->data[6] = (0x48); 				//36Mbps
	mgmt_tag_ptr->data[7] = (0x6C); 				//54Mbps
	mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward

	mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_EXTENDED_SUPPORTED_RATES;
	mgmt_tag_ptr->header.tag_length = 4;
	mgmt_tag_ptr->data[0] = (0x0c); 				//6Mbps
	mgmt_tag_ptr->data[1] = (0x12);					//9Mbps
	mgmt_tag_ptr->data[2] = (0x18);					//12Mbps
	mgmt_tag_ptr->data[3] = (0x60);					//48Mbps
	mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward

	if( (attempt_bss_info->phy_mode) & BSS_INFO_PHY_MODE_11N ){
			//Insert HT Capabilities and HT Information tags
			mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_HT_CAPABILITIES;
			mgmt_tag_ptr->header.tag_length = 26;

			ht_capabilities_element = (ht_capabilities*)mgmt_tag_ptr->data;
			ht_capabilities_element->ht_capabilities_info = 0x010c;
			ht_capabilities_element->a_mpdu_parameters = 0x00;
			ht_capabilities_element->rx_supported_mcs[0] = 0x000000ff;
			ht_capabilities_element->rx_supported_mcs[1] = 0x00000000;
			ht_capabilities_element->rx_supported_mcs[2] = 0x00000000;
			ht_capabilities_element->rx_supported_mcs[3] = 0x00000000;
			ht_capabilities_element->ht_extended_capabilities = 0x0000;
			ht_capabilities_element->tx_beamforming = 0x0000;
			ht_capabilities_element->ant_sel = 0x00;

			mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward

			mgmt_tag_ptr->header.tag_element_id = MGMT_TAG_HT_OPERATION;
			mgmt_tag_ptr->header.tag_length = 22;

			ht_information_element = (ht_information*)mgmt_tag_ptr->data;
			ht_information_element->channel = attempt_bss_info->chan;
			ht_information_element->ht_info_subset_1 = 0x00;
			ht_information_element->ht_info_subset_2 = 0x0000;
			ht_information_element->ht_info_subset_3 = 0x0000;
			ht_information_element->rx_supported_mcs[0] = 0x00000000;
			ht_information_element->rx_supported_mcs[1] = 0x00000000;
			ht_information_element->rx_supported_mcs[2] = 0x00000000;
			ht_information_element->rx_supported_mcs[3] = 0x00000000;

			mgmt_tag_ptr = (void*)mgmt_tag_ptr + ( mgmt_tag_ptr->header.tag_length + sizeof(mgmt_tag_header) ); //Advance tag template forward
		}
	packetLen_bytes = ((u8*)mgmt_tag_ptr - (u8*)(pkt_buf)) + WLAN_PHY_FCS_NBYTES;

	return packetLen_bytes;
}



int wlan_create_association_response_frame(void* pkt_buf, mac_header_80211_common* common, u16 status, u16 AID) {
	u32 packetLen_bytes;
	u8* txBufferPtr_u8;

	txBufferPtr_u8 = (u8*)pkt_buf;

	mac_header_80211* assoc_80211_header;
	assoc_80211_header = (mac_header_80211*)(txBufferPtr_u8);

	assoc_80211_header->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_ASSOC_RESP;
	assoc_80211_header->frame_control_2 = 0;
	//duration can be filled in by CPU_LOW
	assoc_80211_header->duration_id = 0;

	memcpy(assoc_80211_header->address_1,common->address_1,6);
	memcpy(assoc_80211_header->address_2,common->address_2,6);
	memcpy(assoc_80211_header->address_3,common->address_3,6);

	assoc_80211_header->sequence_control = 0; //Will be filled in at dequeue

	association_response_frame* association_resp_mgmt_header;
	association_resp_mgmt_header = (association_response_frame*)(pkt_buf + sizeof(mac_header_80211));
	association_resp_mgmt_header->capabilities = (CAPABILITIES_ESS | CAPABILITIES_SHORT_TIMESLOT);

	association_resp_mgmt_header->status_code = status;
	association_resp_mgmt_header->association_id = 0xC000 | AID;

	txBufferPtr_u8 = (u8 *)((void *)(txBufferPtr_u8) + sizeof(mac_header_80211) + sizeof(association_response_frame));

	//http://my.safaribooksonline.com/book/networking/wireless/0596100523/4dot-802dot11-framing-in-detail/wireless802dot112-chp-4-sect-3
	//Top bit is whether or not the rate is mandatory (basic). Bottom 7 bits is in units of "number of 500kbps"
	txBufferPtr_u8[0] = 1; //Tag 1: Supported Rates
	txBufferPtr_u8[1] = 8; //tag length... doesn't include the tag itself and the tag length
	txBufferPtr_u8[2] = RATE_BASIC | (0x0C); 	//6Mbps  (BPSK,   1/2)
	txBufferPtr_u8[3] = (0x12);				 	//9Mbps  (BPSK,   3/4)
	txBufferPtr_u8[4] = RATE_BASIC | (0x18); 	//12Mbps (QPSK,   1/2)
	txBufferPtr_u8[5] = (0x24); 				//18Mbps (QPSK,   3/4)
	txBufferPtr_u8[6] = RATE_BASIC | (0x30); 	//24Mbps (16-QAM, 1/2)
	txBufferPtr_u8[7] = (0x48); 				//36Mbps (16-QAM, 3/4)
	txBufferPtr_u8[8] = (0x60); 				//48Mbps  (64-QAM, 2/3)
	txBufferPtr_u8[9] = (0x6C); 				//54Mbps  (64-QAM, 3/4)
	txBufferPtr_u8+=(8+2); //Move up to next tag

/*
	txBufferPtr_u8[0] = 1; //Tag 1: Supported Rates
	txBufferPtr_u8[1] = 8; //tag length... doesn't include the tag itself and the tag length
	txBufferPtr_u8[2] = RATE_BASIC | (0x02); 	//1Mbps
	txBufferPtr_u8[3] = RATE_BASIC | (0x04);	//2Mbps
	txBufferPtr_u8[4] = RATE_BASIC | (0x0b); 	//5.5Mbps
	txBufferPtr_u8[5] = RATE_BASIC | (0x16); 	//11Mbps
	txBufferPtr_u8[6] = (0x24); 				//18Mbps
	txBufferPtr_u8[7] = (0x30); 				//24Mbps
	txBufferPtr_u8[8] = (0x48); 				//36Mbps
	txBufferPtr_u8[9] = (0x6C); 				//54Mbps
	txBufferPtr_u8+=(8+2); //Move up to next tag

	txBufferPtr_u8[0] = 50; //Tag 50: Extended Supported Rates
	txBufferPtr_u8[1] = 3; //tag length... doesn't include the tag itself and the tag length
	txBufferPtr_u8[2] = (0x0c); 	//6Mbps
	txBufferPtr_u8[3] = (0x12);		//9Mbps
	txBufferPtr_u8[4] = (0x18); 	//12Mbps
	txBufferPtr_u8[5] = (0x60); 	//48Mbps
	txBufferPtr_u8+=(4+2); //Move up to next tag
*/

	packetLen_bytes = (txBufferPtr_u8 - (u8*)(pkt_buf)) + WLAN_PHY_FCS_NBYTES;

	return packetLen_bytes;
}



int wlan_create_data_frame(void* pkt_buf, mac_header_80211_common* common, u8 flags) {

	u8* txBufferPtr_u8;
	txBufferPtr_u8 = (u8*)pkt_buf;

	mac_header_80211* data_80211_header;
	data_80211_header = (mac_header_80211*)(txBufferPtr_u8);

	data_80211_header->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_DATA;
	data_80211_header->frame_control_2 = flags;

	data_80211_header->duration_id = 0;

	memcpy(data_80211_header->address_1,common->address_1,6);
	memcpy(data_80211_header->address_2,common->address_2,6);
	memcpy(data_80211_header->address_3,common->address_3,6);

	data_80211_header->sequence_control = 0; //Will be filled in at dequeue

	return (sizeof(mac_header_80211) + WLAN_PHY_FCS_NBYTES);
}

int wlan_create_rts_frame(void* pkt_buf_addr, u8* address_ra, u8* address_ta, u16 duration) {
	//TODO: This function is redundant to the same function in wlam_mac_dcf.c. These could be merged,
	//but there isn't currently a good place in wlan_mac_common to place this merged copy. If there
	//are additional cases of universal-scope functions, we could create a new top-level C file to
	//sit alongside wlan_mac_ipc_util.c.

	mac_header_80211_RTS* rts_header;
	rts_header = (mac_header_80211_RTS*)(pkt_buf_addr);

	rts_header->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_RTS;
	rts_header->frame_control_2 = 0;
	rts_header->duration_id = duration;
	memcpy(rts_header->address_ra, address_ra, 6);
	memcpy(rts_header->address_ta, address_ta, 6);

	//Include FCS in packet size (MAC accounts for FCS, even though the PHY calculates it)
	return (sizeof(mac_header_80211_RTS)+WLAN_PHY_FCS_NBYTES);
}

int wlan_create_cts_frame(void* pkt_buf_addr, u8* address_ra, u16 duration) {
	//TODO: This function is redundant to the same function in wlam_mac_dcf.c. These could be merged,
	//but there isn't currently a good place in wlan_mac_common to place this merged copy. If there
	//are additional cases of universal-scope functions, we could create a new top-level C file to
	//sit alongside wlan_mac_ipc_util.c.

	mac_header_80211_CTS* cts_header;
	cts_header = (mac_header_80211_CTS*)(pkt_buf_addr);

	cts_header->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_CTS;
	cts_header->frame_control_2 = 0;
	cts_header->duration_id = duration;
	memcpy(cts_header->address_ra, address_ra, 6);

	//Include FCS in packet size (MAC accounts for FCS, even though the PHY calculates it)
	return (sizeof(mac_header_80211_CTS)+WLAN_PHY_FCS_NBYTES);
}

int wlan_create_ack_frame(void* pkt_buf_addr, u8* address_ra) {
	//TODO: This function is redundant to the same function in wlam_mac_dcf.c. These could be merged,
	//but there isn't currently a good place in wlan_mac_common to place this merged copy. If there
	//are additional cases of universal-scope functions, we could create a new top-level C file to
	//sit alongside wlan_mac_ipc_util.c.
	mac_header_80211_ACK* ack_header;
	ack_header = (mac_header_80211_ACK*)(pkt_buf_addr);

	ack_header->frame_control_1 = MAC_FRAME_CTRL1_SUBTYPE_ACK;
	ack_header->frame_control_2 = 0;
	ack_header->duration_id = 0;
	memcpy(ack_header->address_ra, address_ra, 6);

	//Include FCS in packet size (MAC accounts for FCS, even though the PHY calculates it)
	return (sizeof(mac_header_80211_ACK)+WLAN_PHY_FCS_NBYTES);
}



