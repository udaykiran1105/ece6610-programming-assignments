/** @file wlan_mac_eth_util.h
 *  @brief Ethernet Framework
 *
 *  Contains code for using Ethernet, including encapsulation and de-encapsulation.
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

#ifndef WLAN_MAC_ETH_UTIL_H_
#define WLAN_MAC_ETH_UTIL_H_

#include "xintc.h"

//The struct definitions below are used to interpret packet payloads
// The code never creates instances of these structs

typedef struct{
	u8  address_destination[6];
	u8  address_source[6];
	u16 type;
} ethernet_header;

typedef struct{
	u8  ver_ihl;
	u8  tos;
	u16 length;
	u16 id;
	u16 flags_fragOffset;
	u8  ttl;
	u8  prot;
	u16 checksum;
	u8  ip_src[4];
	u8  ip_dest[4];
} ipv4_header;

typedef struct{
	u16 htype;
	u16 ptype;
	u8  hlen;
	u8  plen;
	u16 oper;
	u8  eth_src[6];
	u8  ip_src[4];
	u8  eth_dst[6];
	u8  ip_dst[4];
} arp_packet;

typedef struct{
	u16 src_port;
	u16 dest_port;
	u16 length;
	u16 checksum;
} udp_header;

typedef struct{
	u8  op;
	u8  htype;
	u8  hlen;
	u8  hops;
	u32 xid;
	u16 secs;
	u16 flags;
	u8  ciaddr[4];
	u8  yiaddr[4];
	u8  siaddr[4];
	u8  giaddr[4];
	u8  chaddr[6];
	u8  chaddr_padding[10];
	u8  padding[192];
	u32 magic_cookie;
} dhcp_packet;

typedef struct{
	u8  dsap;
	u8  ssap;
	u8  control_field;
	u8  org_code[3];
	u16 type;
} llc_header;

//Magic numbers used for Ethernet/IP/UDP/DHCP/ARP packet interpretation
#define DHCP_BOOTP_FLAGS_BROADCAST                         0x8000
#define DHCP_MAGIC_COOKIE                                  0x63825363
#define DHCP_OPTION_TAG_TYPE                               53
#define DHCP_OPTION_TYPE_DISCOVER                          1
#define DHCP_OPTION_TYPE_OFFER                             2
#define DHCP_OPTION_TYPE_REQUEST                           3
#define DHCP_OPTION_TYPE_ACK                               5
#define DHCP_OPTION_TAG_IDENTIFIER                         61
#define DHCP_OPTION_END                                    255
#define DHCP_HOST_NAME                                     12

#define IPV4_PROT_UDP                                      0x11

#define UDP_SRC_PORT_BOOTPC                                68
#define UDP_SRC_PORT_BOOTPS                                67

#define ETH_TYPE_ARP                                       0x0608
#define ETH_TYPE_IP                                        0x0008

#define LLC_SNAP                                           0xAA
#define LLC_CNTRL_UNNUMBERED                               0x03
#define LLC_TYPE_ARP                                       0x0608
#define LLC_TYPE_IP                                        0x0008
#define LLC_TYPE_WLAN_LTG                                  0x9090              // Non-standard type for LTG packets

#define ETH_A_DMA_DEV_ID	                               XPAR_MB_HIGH_ETH_DMA_DEVICE_ID

// Ethernet MAC-PHY link speed - must match PHY's actual link speed, as auto-negotiated at run time
#define ETH_A_LINK_SPEED	                               1000
#define ETH_A_MDIO_PHYADDR                                 0x6

// Memory space allocated per Ethernet packet
#define ETH_A_PKT_BUF_SIZE                                 0x800               // 2KB

int  wlan_eth_init();
int  wlan_eth_dma_init();

void wlan_mac_util_set_eth_rx_callback(void(*callback)());
void wlan_mac_util_set_eth_encap_mode(u8 mode);

void wlan_eth_dma_update();
int  wlan_eth_dma_send(u8* pkt_ptr, u32 length);

inline int eth_get_num_rx_bd();

int  wlan_mpdu_eth_send(void* mpdu, u16 length, u8 pre_llc_offset);

int  wlan_eth_encap(u8* mpdu_start_ptr, u8* eth_dest, u8* eth_src, u8* eth_start_ptr, u32 eth_rx_len);

inline void wlan_poll_eth_rx();

int  wlan_eth_setup_interrupt(XIntc* intc);
void eth_rx_interrupt_handler(void *callbarck_arg);

#endif /* WLAN_MAC_ETH_UTIL_H_ */
