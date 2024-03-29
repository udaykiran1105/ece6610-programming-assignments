/*****************************************************************
* File: w3_clock_controller.c
* Copyright (c) 2015 Mango Communications, all rights reseved
* Released under the WARP License
* See http://warpproject.org/license for details
*****************************************************************/

/** \file w3_clock_controller.c

\mainpage
This is the driver for the w3_clock_controller_axi core, which implements an SPI master for controlling
the AD9512 clock buffers on the WARP v3 board. This core also manages the interfaces on CM-MMCX
and CM-PLL clock modules. Refer to the WARP v3 user guide for more details on the clock options and connections.

@version 4.00.a
@author Patrick Murphy
@copyright (c) 2015 Mango Communications, Inc. All rights reserved.<br>
Released under the WARP open source license (see http://warpproject.org/license)

*/

#include "w3_clock_controller.h"

/**
\defgroup user_functions Functions
\brief Functions to call from user code
\addtogroup user_functions

Example:
\code{.c}
//Assumes user code sets CLK_BASEADDR to base address of w3_clock_controller_axi core, as set in xparameters.h

//Initialize the AD9512 clock buffers
clk_init(CLK_BASEADDR, 3);

//Enable clock outputs to FMC slot
clk_config_outputs(CLK_BASEADDR, CLK_OUTPUT_ON, (CLK_SAMP_OUTSEL_FMC | CLK_RFREF_OUTSEL_FMC));

//Disable clock outputs to clock module header
clk_config_outputs(CLK_BASEADDR, CLK_OUTPUT_OFF, (CLK_SAMP_OUTSEL_CLKMODHDR | CLK_RFREF_OUTSEL_CLKMODHDR));

//Set clock to AD chips to 40MHz (80MHz source divided by 2)
clk_config_dividers(CLK_BASEADDR, 2, (CLK_SAMP_OUTSEL_AD_RFA | CLK_SAMP_OUTSEL_AD_RFB));

\endcode

@{
*/

/**
\brief Initializes the clock controller. This function must be called once at boot before any AD or 
RF operations will work. The w3_clock_controller_axi HDL applies preliminary configuration values
to the sampling and RF reference clock buffers, and (if preset) the PLL+buffer on the CM-PLL 
clock module.

The HDL applies the minimum set of configuration values to allow the MicroBlaze
subsystem to boot. This function does not override any configuration values applied by
the HDL.

Refer to the pcore user guide for details on the pre-boot configuration process:
  http://warpproject.org/trac/wiki/cores/w3_clock_controller

Default config is:
- On board 80MHz TCXO used as source for sampling and RF ref clock buffers
- 80MHz clock driven to FPGA, RF A and RF B ADC/DACs
- 40MHz clock driven to RF A and B transceivers
- FMC and clock module header clocks disabled
\param baseaddr Base memory address of w3_clock_controller_axi pcore
\param clkDiv Clock divider for SPI serial clock (set to 3 for 160MHz bus)
*/
int clk_init(u32 baseaddr, u8 clkDiv) {
	u32 x;
	
	//Set the SPI clock divider
	Xil_Out32(baseaddr + CLKCTRL_REG_CONFIG, (clkDiv & CLKCTRL_REG_CONFIG_MASK_CLKDIV));

	//Confirm the SPI interfaces are working
	// Reads reg 0x00 from both AD9512; both must return 0x10
	x = 0xFFFF & clk_spi_read(baseaddr, (CLK_SAMP_CS|CLK_RFREF_CS), 0x0);
	if(x != 0x1010) {
		xil_printf("First CLK SPI readback was wrong: addr[0]=0x%04x (should be 0x1010)\n", x);
		return -1;
	}

	/* Samping Clock Buffer Config
	Samp clock AD9512 outputs on WARP v3 board:
	 OUT0: AD2 (LVPECL)
	 OUT1: Clock module header (LVPECL)
	 OUT2: AD1 (LVPECL)
	 OUT3: FPGA col2 SRCC (LVDS)
	 OUT4: FMC  (LVDS)

	HDL configures:
	 -Selects CLK1 (on-board) or CLK2 (off-board) as sampling clock source
	 -Sets divider and output type on OUT3 to achieve 80MHz LVDS to FPGA

	clk_init() configures:
	 -Sets divider on OUT0/OUT2 for 40MHz LVPECL to RFA/B converters
	 -Disables OUT1/OUT4 outputs to clock module header and FMC

	clk_init() must *not* change sampling clock source or divider on OUT3

*/
	//Enable OUT0, OUT2, OUT3; disable OUT1, OUT4; all outputs are on after powerup/reset
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x3E, 0x02); //OUT1 = off (PD2 mode, because OUT1 has load resistors)
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x41, 0x01); //OUT4 = off

	//Power down divider logic on disabled outputs and 80MHz outputs
	// Don't touch OUT3 divider config - HDL sets this
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x4D, 0x80); //OUT1 divider off
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x53, 0x80); //OUT4 divider off

	//Divide by 2 on OUT0/OUT2 to RFA/B convterters
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x4B, 0x00); //OUT0 divider on
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x4A, 0x00); //OUT0 divide by 2
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x4F, 0x00); //OUT2 divider on
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x4E, 0x00); //OUT2 divide by 2

	//Trigger register update
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x5A, 0x01); //Self-clearing register update flag

	/* RF Reference Clock Buffer Config
	RF ref clock AD9512 outputs on WARP v3 board:
		OUT0: Clock module header (LVPECL)
		OUT1: NC
		OUT2: NC
		OUT3: Both MAX2829 ref (RFA=CMOSp, RFB=CMOSn; must be 20 or 40 MHz)
		OUT4: FMC (LVDS)

	HDL configures either:
	   -Nothing - in most configurations the HDL does not write RF ref clk buffer registers
     or
	   -Selects on-board clock source (CLK1) and sets OUT0 divider to 8, providing a 10MHz
	     reference clock to the AD9511 PLL on the CM-PLL

	clk_init() configures:
	  -If OUT0 is not configured for divide-by-8 (i.e. HDL did not write any regs):
	    -Selects CLK1 (on-board) clock source
		-Disables OUT0 (output to clock module)
	  -Always configures:
	    -Disables OUT1/2 (unconnected on board)
	    -Enables OUT3 as 40MHz CMOS +/-
		-Disables OUT4 (FMC)
	*/

	//Read reg 0x4A - OUT3 divider config
	// 0x33 => HDL wrote config
	// Anything else => HDL did not write registers
	x = clk_spi_read(baseaddr, (CLK_RFREF_CS), 0x4A);
	if((x & 0xFF00) != 0x3300) {
		//HDL didn't write config - apply defaults here

		//Select CLK1 input, power down CLK2
		clk_spi_write(baseaddr, CLK_RFREF_CS, 0x45, 0x05); //CLK1 on, CLK2 off, CLK1 drives distribution

		//Disable OUT0 (output to clock module)
		clk_spi_write(baseaddr, CLK_RFREF_CS, 0x3D, 0x02); //OUT0 = off, has load resistors
		clk_spi_write(baseaddr, CLK_RFREF_CS, 0x4B, 0x80); //OUT0 divider off
	}
	
	//Disable unused outputs
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x3E, 0x03); //OUT1 = off, has no load resistors
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x3F, 0x03); //OUT2 = off, has no load resistors
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x41, 0x01); //OUT4 = off

	//Power down divider logic on disabled ports
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x4D, 0x80); //OUT1 divider off
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x4F, 0x80); //OUT2 divider off
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x53, 0x80); //OUT4 divider off

	//Enable inverted CMOS output on OUT3
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x40, 0x18); //OUT3 = CMOS, +/- both on

	//Set divider to 2 on OUT3
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x50, 0x00); //OUT3 40MHz (1 cycle down)
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x51, 0x00); //Enable OUT3 divider

	//Alternate config: 20MHz RF reference, OUT3 divider = 4
	//clk_spi_write(baseaddr, CLK_RFREF_CS, 0x50, 0x11); //OUT3 20MHz (2 cycle down)
	//clk_spi_write(baseaddr, CLK_RFREF_CS, 0x51, 0x00); //Enable OUT3 divider

	//Trigger register update
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x5A, 0x01); //Self-clearing register update flag
	
	return 0;
}

/**
\brief Configures which outputs are en/disabled in both AD9512 clock buffers
\param baseaddr Base memory address of w3_clock_controller_axi pcore
\param clkOutMode New mode for selected clock outputs; must be CLK_OUTPUT_ON or CLK_OUTPUT_OFF
\param clkOutSel Masks to select which clock outputs to affect; must be OR'd combination of:
 Mask | Selected Output
 ---- | ----
 CLK_SAMP_OUTSEL_FMC | Sampling clock buffer to FMC slot
 CLK_SAMP_OUTSEL_CLKMODHDR | Sampling clock buffer to clock module header
 CLK_SAMP_OUTSEL_FPGA | Sampling clock buffer to FPGA
 CLK_SAMP_OUTSEL_AD_RFA | Sampling clock buffer to RF A AD9963 (ADC/DAC ref clock)
 CLK_SAMP_OUTSEL_AD_RFB | Sampling clock buffer to RF B AD9963 (ADC/DAC ref clock)
 CLK_RFREF_OUTSEL_FMC | RF ref clock buffer to FMC
 CLK_RFREF_OUTSEL_CLKMODHDR | RF ref clock buffer to clock module header
 CLK_RFREF_OUTSEL_RFAB | RF ref clock buffer to RF A and B transceivers
\return Returns 0 on success, -1 for invalid parameters
*/
int clk_config_outputs(u32 baseaddr, u8 clkOutMode, u32 clkOutSel) {
	if((clkOutMode != CLK_OUTPUT_ON) && (clkOutMode != CLK_OUTPUT_OFF))
		return -1;
/*
	Samp clock AD9512 outputs on WARP v3 board:
		OUT0: AD2 (LVPECL)
		OUT1: Clock module header (LVPECL)
		OUT2: AD1 (LVPECL)
		OUT3: FPGA col2 SRCC (LVDS)
		OUT4: FMC  (LVDS)

	RF ref clock AD9512 outputs on WARP v3 board:
		OUT0: Clock module header (LVPECL)
		OUT1: NC
		OUT2: NC
		OUT3: Both MAX2829 ref (RFA=CMOSp, RFB=CMOSn; must be 20 or 40 MHz)
		OUT4: FMC (LVDS)
*/
	
	u8 lvpecl_cfg, lvds_cfg, cmos_cfg;

	//Set the register values to write, based on output type and user ON/OFF param
	if(clkOutMode == CLK_OUTPUT_ON) lvpecl_cfg = 0x8; //LVPECL output on, 805mV drive
	else lvpecl_cfg = 0x2; //output off (for outputs w/ load resistors)

	if(clkOutMode == CLK_OUTPUT_ON) lvds_cfg = 0x2; //output on, LVDS logic, 3.5mA drive
	else lvds_cfg = 0x1; //output off

	if(clkOutMode == CLK_OUTPUT_ON) cmos_cfg = 0x18; //+/- outputs on, CMOS logic
	else cmos_cfg = 0x1; //output off
	
	/***** Sampling Clock Buffer Config ******/
	//reg 0x3D, 0x3E, 0x3F: CLKOUT[0,1,2] config
	// [1:0] LVPECL power down
	//   (0x0=on, 0x2=PD2 (power down outputs w/ load resistors), 0x3=PD3 (power down outputs w/out load resistors)
	// [3:2] LVPECL output drive (set to 0x2 for default 805mv)
	if(clkOutSel & CLK_SAMP_OUTSEL_AD_RFB)		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x3D, lvpecl_cfg); //CLKOUT0
	if(clkOutSel & CLK_SAMP_OUTSEL_CLKMODHDR)	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x3E, lvpecl_cfg); //CLKOUT1
	if(clkOutSel & CLK_SAMP_OUTSEL_AD_RFA)		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x3F, lvpecl_cfg); //CLKOUT2

	//reg 0x40, 0x41: CLKOUT[3,4] config
	// [0] 0=output on, 1=output off
	// [2:1] LVDS output current (set to 0x1 for 3.5mA default)
	// [3] Logic (0=LVDS, 1=CMOS)
	// [4] CMOS- (0=Disable CMOS inverted output; 1=enable)
	if(clkOutSel & CLK_SAMP_OUTSEL_FPGA)		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x40, lvds_cfg); //CLKOUT3 (LVDS)
	if(clkOutSel & CLK_SAMP_OUTSEL_FMC)			clk_spi_write(baseaddr, CLK_SAMP_CS, 0x41, lvds_cfg); //CLKOUT4 (LVDS)

	//Trigger register update
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x5A, 0x01); //Self-clearing register update flag

	/***** RF Ref Clock Buffer Config ******/
	//reg 0x3D: CLKOUT0 config
	// [1:0] LVPECL power down
	//   (0x0=on, 0x2=PD2 (power down outputs w/ load resistors), 0x3=PD3 (power down outputs w/out load resistors)
	// [3:2] LVPECL output drive (set to 0x2 for default 805mv)
	//CLKOUT1, CLKOUT2 are unused and are disabled in clk_init
	if(clkOutSel & CLK_RFREF_OUTSEL_CLKMODHDR)	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x3D, lvpecl_cfg); //CLKOUT0

	//reg 0x40, 0x41: CLKOUT[3,4] config
	// [0] 0=output on, 1=output off
	// [2:1] LVDS output current (set to 0x1 for 3.5mA default)
	// [3] Logic (0=LVDS, 1=CMOS)
	// [4] CMOS- (0=Disable CMOS inverted output; 1=enable)
	if(clkOutSel & CLK_RFREF_OUTSEL_RFAB)		clk_spi_write(baseaddr, CLK_RFREF_CS, 0x40, cmos_cfg); //CLKOUT3 (CMOS +/-)
	if(clkOutSel & CLK_RFREF_OUTSEL_FMC)		clk_spi_write(baseaddr, CLK_RFREF_CS, 0x41, lvds_cfg); //CLKOUT4 (LVDS)

	//Trigger register update
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x5A, 0x01); //Self-clearing register update flag

	return 0;
}

/**
\brief Configures whether the RF Reference Buffer uses the on-board or off-board clock source
\param baseaddr Base memory address of w3_clock_controller_axi pcore
\param clkInSel Clock source mask, must be either CLK_INSEL_ONBOARD (for on-board oscillator) or CLK_INSEL_CLKMOD (for off-board clock via clock module header)
 Mask | Selected Input
 ---- | ----
 CLK_INSEL_ONBOARD | Selects on-board TCXO as RF Reference clock source (AD9512 CLK1/CLK1B port)
 CLK_INSEL_CLKMOD | Selects off-board clock from clock module header as RF Reference clock source (AD9512 CLK2/CLK2B port)
\return Returns 0 on success, -1 for invalid parameters
*/
int clk_config_input_rf_ref(u32 baseaddr, u8 clkInSel) {
	if((clkInSel != CLK_INSEL_ONBOARD) && (clkInSel != CLK_INSEL_CLKMOD))
		return -1;
/*
	Samp clock AD9512 inputs on WARP v3 board:
		CLK1: On-board TCXO
		CLK2: Clock module header
*/
	
	/***** Sampling Clock Buffer Config ******/
	//reg 0x45
	// [0] Input sel (0=CLK2, 1=CLK1)
	// [1] 1=Power down CLK1 input circuit
	// [2] 1=Power down CLK2 input circuit
	// [3:4] Reserved
	// [5] Power down both input circuits
	// [6:7] Reserved
	if(clkInSel == CLK_INSEL_ONBOARD)	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x45, 0x05); //Select CLK1, power down CLK2
	if(clkInSel == CLK_INSEL_CLKMOD) 	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x45, 0x02); //Select CLK2, power down CLK1

	//Trigger register update
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x5A, 0x01); //Self-clearing register update flag

	return 0;
}

/**
\brief Reads the status pins of the currently installed clock module
\param baseaddr Base memory address of w3_clock_controller_axi pcore
\return Returns the clock module status; the meaning of the status bits depends on the currently installed module.

For the CM-MMCX, 2 LSB are value of 2-position SIP switch.
For the CM-PLL, 3 LSB are the value of the 3 LSB of the DIP switch. Bit 0x8 is the PLL status.
*/
inline u32 clk_config_read_clkmod_status(u32 baseaddr) {
	//Status reg in HDL:
	// [31:28] = {cm_pll_status, cm_switch[2:0]}
	return (u32)((Xil_In32(baseaddr + CLKCTRL_REG_CONFIG)) >> 28);
}

/**
\brief Configures output dividers in both AD9512 clock buffers
\param baseaddr Base memory address of w3_clock_controller_axi pcore
\param clkDiv Divider value to set; must be 1 or even integer in [2,32]
\param clkOutSel Masks to select which clock outputs to affect; must be OR'd combination of:
 Mask | Selected Output
 ---- | ----
 CLK_SAMP_OUTSEL_FMC | Sampling clock buffer to FMC slot
 CLK_SAMP_OUTSEL_CLKMODHDR | Sampling clock buffer to clock module header
 CLK_SAMP_OUTSEL_FPGA | Sampling clock buffer to FPGA
 CLK_SAMP_OUTSEL_AD_RFA | Sampling clock buffer to RF A AD9963 (ADC/DAC ref clock)
 CLK_SAMP_OUTSEL_AD_RFB | Sampling clock buffer to RF B AD9963 (ADC/DAC ref clock)
 CLK_RFREF_OUTSEL_FMC | RF ref clock buffer to FMC
 CLK_RFREF_OUTSEL_CLKMODHDR | RF ref clock buffer to clock module header
 CLK_RFREF_OUTSEL_RFAB | RF ref clock buffer to RF A and B transceivers
\return Returns 0 on success, -1 for invalid parameters
*/
int clk_config_dividers(u32 baseaddr, u8 clkDiv, u32 clkOutSel) {
/*
	AD9512 reg 0x[4A,4C,4E,50,52]: Divider config high/low for CLKOUT[0,1,2,3,4]
	 [3:0] Divider high cycles
	 [7:4] Divider low cycles
	 Clock freq divided by ((high+1)+(low+1))
	 50% duty cycle requkired; only possible with 1 or even division ratios (high==low)

	AD9512 reg 0x[4B,4D,4F,51,53]: Divider power down & sync for CLKOUT[0,1,2,3,4]
	 [7] 1=disable and bypass divider logic, 0=use divider
	 [6:0] Divider sync setup (not currently used)
	*/
	
	u8 div_pd, div_cfg;

	//Check for invalid clkDiv value (any odd value besides 1, greater than 32, or 0)
	if( ((clkDiv != 1) && (clkDiv & 0x1)) || clkDiv > 32 || clkDiv == 0)
		return -1;
	
	if(clkDiv == 1) {
		div_pd = 0x80; //divide-by-1 requires bypassing divider entirely
		div_cfg = 0x00;
	} else {
		div_pd = 0x00; //enable divider

		//Calculate number of high/low cycles
		div_cfg = (clkDiv>>1)-1;
		
		//Set high=low
		div_cfg = (div_cfg<<4) | div_cfg;
	}
	
	
	//Sampling clock buffer
	if(clkOutSel & CLK_SAMP_OUTSEL_AD_RFB) { //CLKOUT0
		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x4A, div_cfg);
		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x4B, div_pd);
	}
	if(clkOutSel & CLK_SAMP_OUTSEL_CLKMODHDR) { //CLKOUT1
		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x4C, div_cfg);
		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x4D, div_pd);
	}
	if(clkOutSel & CLK_SAMP_OUTSEL_AD_RFA) { //CLKOUT2
		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x4E, div_cfg);
		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x4F, div_pd);
	}
	if(clkOutSel & CLK_SAMP_OUTSEL_FPGA) { //CLKOUT3
		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x50, div_cfg);
		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x51, div_pd);
	}
	if(clkOutSel & CLK_SAMP_OUTSEL_FMC) { //CLKOUT4
		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x52, div_cfg);
		clk_spi_write(baseaddr, CLK_SAMP_CS, 0x53, div_pd);
	}
	
	//Trigger register update
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x5A, 0x01); //Self-clearing register update flag

    // Sync outputs (High -> Low transition on bit 2 - Soft SYNC)
    clk_spi_write(baseaddr, CLK_SAMP_CS, 0x58, 0x04);
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x5A, 0x01); //Self-clearing register update flag
    clk_spi_write(baseaddr, CLK_SAMP_CS, 0x58, 0x00);
	clk_spi_write(baseaddr, CLK_SAMP_CS, 0x5A, 0x01); //Self-clearing register update flag
    
	//RF reference clock buffer
	if(clkOutSel & CLK_RFREF_OUTSEL_CLKMODHDR) { //CLKOUT0
		clk_spi_write(baseaddr, CLK_RFREF_CS, 0x4A, div_cfg);
		clk_spi_write(baseaddr, CLK_RFREF_CS, 0x4B, div_pd);
	}
	//CLKOUT1, CLKOUT2 are unused; dividers are disabled in clk_init
	if(clkOutSel & CLK_RFREF_OUTSEL_RFAB) { //CLKOUT3
		clk_spi_write(baseaddr, CLK_RFREF_CS, 0x50, div_cfg);
		clk_spi_write(baseaddr, CLK_RFREF_CS, 0x51, div_pd);
	}
	if(clkOutSel & CLK_RFREF_OUTSEL_FMC) { //CLKOUT4
		clk_spi_write(baseaddr, CLK_RFREF_CS, 0x52, div_cfg);
		clk_spi_write(baseaddr, CLK_RFREF_CS, 0x53, div_pd);
	}
	
	//Trigger register update
	clk_spi_write(baseaddr, CLK_RFREF_CS, 0x5A, 0x01); //Self-clearing register update flag

	return 0;
}

/**
\brief Reads the specified register from both AD9963s
\param baseaddr Base memory address of w3_clock_controller_axi pcore
\param csMask OR'd combination of CLK_SAMP_CS and CLK_RFREF_CS
\param regAddr Address of register to read, in [0x00, 0x5A]
\return Returns concatenation of current values of the specified register for both AD9512s (if selected); samp clock buffer is LSB
*/
u32 clk_spi_read(u32 baseaddr,  u32 csMask, u8 regAddr) {
	u32 txWord, rxWord;

	//SPI Tx register is 4 bytes:
	// [3]: chip selects (bitwise OR'd ADCTRL_REG_SPITX_ADx_CS)
	// [2]: {rnw n1 n0 5'b0}, rnw=1 for SPI write, n1=n0=0 for 1 byte write
	// [1]: reg addr[7:0]
	// [0]: ignored for read (read value captured in Rx register)
	txWord = (csMask & (CLK_SAMP_CS | CLK_RFREF_CS | CMPLL_CS)) | //chip selects
			 (CLKCTRL_REG_SPITX_RNW) | //spi_tx_byte[2] = {rnw n1 n0 5'b0}
			 ((regAddr & 0x7F)<<8) | //spi_tx_byte[1] = addr[7:0]
			 (0x00); //spi_tx_byte[0] = ignored for read (AD drives data pin during this byte)

	Xil_Out32(baseaddr + CLKCTRL_REG_SPITX, txWord);

	rxWord = Xil_In32(baseaddr + CLKCTRL_REG_SPIRX);

	return(rxWord);
}

/**
\brief Writes the specified register value to the selected AD9512 clock buffers
\param baseaddr Base memory address of w3_clock_controller_axi pcore
\param csMask OR'd combination of CLK_SAMP_CS and CLK_RFREF_CS
\param regAddr Address of register to write, in [0x00, 0x5A]
\param txByte 8-bit value to write
*/
void clk_spi_write(u32 baseaddr, u32 csMask, u8 regAddr, u8 txByte) {
	u32 txWord;

	//SPI read process:
	// -Write full SPI word with RNW=1 and address of desired register
	// -Capture register value in last byte of SPI write process (handled automatically in logic)
	
	//SPI Tx register is 4 bytes:
	// [3]: chip selects (bitwise OR'd ADCTRL_REG_SPITX_ADx_CS)
	// [2]: {rnw n1 n0 5'b0}, rnw=0 for SPI write, n1=n0=0 for 1 byte write
	// [1]: reg addr[7:0]
	// [0]: reg data[7:0]
	txWord = (csMask & (CLK_SAMP_CS | CLK_RFREF_CS | CMPLL_CS)) | //chip selects
			 (0x00) | //spi_tx_byte[2] = {rnw n1 n0 5'b0}
			 ((regAddr & 0xFF)<<8) | //spi_tx_byte[1] = addr[7:0]
			 (txByte & 0xFF); //spi_tx_byte[0] = data byte to write

	Xil_Out32(baseaddr + CLKCTRL_REG_SPITX, txWord);
	
	return;
}

/** @}*/ //END group user_functions
