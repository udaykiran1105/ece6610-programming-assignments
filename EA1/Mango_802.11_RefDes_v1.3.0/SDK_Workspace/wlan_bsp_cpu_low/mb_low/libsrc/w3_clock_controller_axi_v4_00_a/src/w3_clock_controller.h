#ifndef WARP_CLOCK_CONTROLLER_H
#define WARP_CLOCK_CONTROLLER_H

#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"

#define WARP_CLOCK_CONTROLLER_USER_SLV_SPACE_OFFSET (0x00000000)

#define WARP_CLOCK_CONTROLLER_SLV_REG0_OFFSET (WARP_CLOCK_CONTROLLER_USER_SLV_SPACE_OFFSET + 0x00000000)
#define WARP_CLOCK_CONTROLLER_SLV_REG1_OFFSET (WARP_CLOCK_CONTROLLER_USER_SLV_SPACE_OFFSET + 0x00000004)
#define WARP_CLOCK_CONTROLLER_SLV_REG2_OFFSET (WARP_CLOCK_CONTROLLER_USER_SLV_SPACE_OFFSET + 0x00000008)
#define WARP_CLOCK_CONTROLLER_SLV_REG3_OFFSET (WARP_CLOCK_CONTROLLER_USER_SLV_SPACE_OFFSET + 0x0000000C)
#define WARP_CLOCK_CONTROLLER_SLV_REG4_OFFSET (WARP_CLOCK_CONTROLLER_USER_SLV_SPACE_OFFSET + 0x00000010)
#define WARP_CLOCK_CONTROLLER_SLV_REG5_OFFSET (WARP_CLOCK_CONTROLLER_USER_SLV_SPACE_OFFSET + 0x00000014)
#define WARP_CLOCK_CONTROLLER_SLV_REG6_OFFSET (WARP_CLOCK_CONTROLLER_USER_SLV_SPACE_OFFSET + 0x00000018)
#define WARP_CLOCK_CONTROLLER_SLV_REG7_OFFSET (WARP_CLOCK_CONTROLLER_USER_SLV_SPACE_OFFSET + 0x0000001C)

/* Address map:
	HDL is coded [MSB:LSB] = [31:0]
	regX[31]  maps to 0x80000000 in C driver
	regX[0] maps to 0x00000001 in C driver

0: Config:
	[ 2: 0] Clock divider bit sel (00=0.5*busclk, 01=0.25*busclk, ...) 0x00000003
	[    3] Reserved
	[    4] samp buf reset (active low)		0x00000010
	[    5] rf ref buf reset (active low)	0x00000020
	[15: 6] Reserved 						0x0000FFC0
	[31:16] Clock module status				0xFFFF0000

1: SPI Tx
	[ 7: 0] Tx data byte
	[14: 8] 7-bit register address (0x00 to 0xFF all valid)
	[20:15] 6'b0 (always zero)
	[22:21] Num bytes to Tx/Rx; must be 2'b0 for 1-byte Tx/Rx
	[   23] RW# 1=Read, 0=Write
	[   24] samp clock buffer chip select mask
	[   25] rf ref clk buffer chip select mask
	[   26] clock module clk buffer chip select mask
	[31:27] Reserved

2: SPI Rx: {samp_rxByte, rfref_rxByte, 16'b0}
	[ 7: 0] SPI Rx byte for samp buf 	 0x0000FF
	[15: 8] SPI Rx byte for rf ref buf 	 0x00FF00
	[23:16] SPI Rx byte for clock module 0xFF0000
	[31:24] Reserved 					 0xFF000000
	
3: RW: User reset outputs
	[0] usr_reset0
	[1] usr_reset1
	[2] usr_reset2
	[3] usr_reset3
	[31:4] reserved

4: RO: User status inputs
	[31: 0] usr_status input

5-15: Reserved
*/

#define CLKCTRL_REG_CONFIG                  WARP_CLOCK_CONTROLLER_SLV_REG0_OFFSET
#define CLKCTRL_REG_SPITX                   WARP_CLOCK_CONTROLLER_SLV_REG1_OFFSET
#define CLKCTRL_REG_SPIRX                   WARP_CLOCK_CONTROLLER_SLV_REG2_OFFSET
#define CLKCTRL_REG_USR_RESETS				WARP_CLOCK_CONTROLLER_SLV_REG3_OFFSET
#define CLKCTRL_REG_STATUS                  WARP_CLOCK_CONTROLLER_SLV_REG4_OFFSET

#define CLKCTRL_REG_CONFIG_MASK_CLKDIV      0x03
#define CLKCTRL_REG_CONFIG_MASK_SAMP_FUNC   0x10
#define CLKCTRL_REG_CONFIG_MASK_RFREF_FUNC  0x20

#define CLKCTRL_REG_SPITX_SAMP_CS           0x01000000
#define CLKCTRL_REG_SPITX_RFREF_CS          0x02000000
#define CLKCTRL_REG_SPITX_CMPLL_CS          0x04000000
#define CLKCTRL_REG_SPITX_RNW               0x00800000

#define CLK_SAMP_CS                         CLKCTRL_REG_SPITX_SAMP_CS
#define CLK_RFREF_CS                        CLKCTRL_REG_SPITX_RFREF_CS
#define CMPLL_CS							CLKCTRL_REG_SPITX_CMPLL_CS

#define CLK_SAMP_OUTSEL_FMC			        0x01
#define CLK_SAMP_OUTSEL_CLKMODHDR	        0x02
#define CLK_SAMP_OUTSEL_FPGA		        0x04
#define CLK_SAMP_OUTSEL_AD_RFA		        0x08
#define CLK_SAMP_OUTSEL_AD_RFB		        0x10

#define CLK_RFREF_OUTSEL_FMC                0x20
#define CLK_RFREF_OUTSEL_CLKMODHDR          0x40
#define CLK_RFREF_OUTSEL_RFAB               0x80

#define CLK_OUTPUT_ON                       1
#define CLK_OUTPUT_OFF                      2

#define CLK_INSEL_ONBOARD                   1
#define CLK_INSEL_CLKMOD                    2

//CM switch interpretation
// Clock modules pull switch signals to GND when switch is asserted
// FPGA pulls up sw[2:0] to [111]
// CM-PLL pulls sw[2] to GND, sw[1:0] set by LSB of DIP switch ("up" = 0)
//  CM-PLL:  sw[2:0] = [2,1,0] => CFG_[A,B,C]
// CM-MMCX floats sw[2] (IOB pulls up), sw[1:0] set by SIP switch ("down" = 0)
//  CM-MMCX: sw[2:0] = [6,5,4] => CFG_[A,B,C]

#define CM_STATUS_SW						0x7

#define CM_STATUS_DET_NOCM					0x7

#define CM_STATUS_DET_CMMMCX_CFG_A			0x6
#define CM_STATUS_DET_CMMMCX_CFG_B			0x5
#define CM_STATUS_DET_CMMMCX_CFG_C			0x4

#define CM_STATUS_DET_CMPLL_BYPASS			0x3
#define CM_STATUS_DET_CMPLL_CFG_A			0x2
#define CM_STATUS_DET_CMPLL_CFG_B			0x1
#define CM_STATUS_DET_CMPLL_CFG_C			0x0

#define CM_STATUS_CMPLL_LOCKED				0x8

u32  clk_spi_read(u32 baseaddr,  u32 csMask, u8 regAddr);
void clk_spi_write(u32 baseaddr, u32 csMask, u8 regAddr, u8 txByte);

int  clk_init(u32 baseaddr, u8 clkDiv);

int  clk_config_outputs(u32 baseaddr, u8 clkOutMode, u32 clkOutSel);
int  clk_config_dividers(u32 baseaddr, u8 clkDiv, u32 clkOutSel);
int  clk_config_input_rf_ref(u32 baseaddr, u8 clkInSel);
inline u32  clk_config_read_clkmod_status(u32 baseaddr);

#endif /** WARP_CLOCK_CONTROLLER_H */
