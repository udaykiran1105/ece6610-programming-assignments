/** @file wlan_mac_nomac.c
 *  @brief Simple MAC that does nothing but transmit and receive
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

#ifndef WLAN_MAC_NOMAC_H_
#define WLAN_MAC_NOMAC_H_

int main();
int frame_transmit(u8 pkt_buf, u8 rate, u16 length, wlan_mac_low_tx_details* low_tx_details);
u32 frame_receive(u8 rx_pkt_buf, phy_rx_details* phy_details);

#endif /* WLAN_MAC_NOMAC_H_ */
