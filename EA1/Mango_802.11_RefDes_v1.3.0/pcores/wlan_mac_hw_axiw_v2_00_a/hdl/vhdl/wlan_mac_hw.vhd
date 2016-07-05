--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2013 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
-- You must compile the wrapper file addsb_11_0_38dd91dde0ab1a97.vhd when simulating
-- the core, addsb_11_0_38dd91dde0ab1a97. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY addsb_11_0_38dd91dde0ab1a97 IS
  PORT (
    a : IN STD_LOGIC_VECTOR(21 DOWNTO 0);
    b : IN STD_LOGIC_VECTOR(21 DOWNTO 0);
    s : OUT STD_LOGIC_VECTOR(21 DOWNTO 0)
  );
END addsb_11_0_38dd91dde0ab1a97;

ARCHITECTURE addsb_11_0_38dd91dde0ab1a97_a OF addsb_11_0_38dd91dde0ab1a97 IS
-- synthesis translate_off
COMPONENT wrapped_addsb_11_0_38dd91dde0ab1a97
  PORT (
    a : IN STD_LOGIC_VECTOR(21 DOWNTO 0);
    b : IN STD_LOGIC_VECTOR(21 DOWNTO 0);
    s : OUT STD_LOGIC_VECTOR(21 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_addsb_11_0_38dd91dde0ab1a97 USE ENTITY XilinxCoreLib.c_addsub_v11_0(behavioral)
    GENERIC MAP (
      c_a_type => 0,
      c_a_width => 22,
      c_add_mode => 0,
      c_ainit_val => "0",
      c_b_constant => 0,
      c_b_type => 0,
      c_b_value => "0000000000000000000000",
      c_b_width => 22,
      c_borrow_low => 1,
      c_bypass_low => 0,
      c_ce_overrides_bypass => 1,
      c_ce_overrides_sclr => 0,
      c_has_bypass => 0,
      c_has_c_in => 0,
      c_has_c_out => 0,
      c_has_ce => 0,
      c_has_sclr => 0,
      c_has_sinit => 0,
      c_has_sset => 0,
      c_implementation => 0,
      c_latency => 0,
      c_out_width => 22,
      c_sclr_overrides_sset => 1,
      c_sinit_val => "0",
      c_verbosity => 0,
      c_xdevicefamily => "virtex6"
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_addsb_11_0_38dd91dde0ab1a97
  PORT MAP (
    a => a,
    b => b,
    s => s
  );
-- synthesis translate_on

END addsb_11_0_38dd91dde0ab1a97_a;
--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2014 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
-- You must compile the wrapper file addsb_11_0_3c1d0ac9b6b8f403.vhd when simulating
-- the core, addsb_11_0_3c1d0ac9b6b8f403. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY addsb_11_0_3c1d0ac9b6b8f403 IS
  PORT (
    a : IN STD_LOGIC_VECTOR(65 DOWNTO 0);
    b : IN STD_LOGIC_VECTOR(65 DOWNTO 0);
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    s : OUT STD_LOGIC_VECTOR(65 DOWNTO 0)
  );
END addsb_11_0_3c1d0ac9b6b8f403;

ARCHITECTURE addsb_11_0_3c1d0ac9b6b8f403_a OF addsb_11_0_3c1d0ac9b6b8f403 IS
-- synthesis translate_off
COMPONENT wrapped_addsb_11_0_3c1d0ac9b6b8f403
  PORT (
    a : IN STD_LOGIC_VECTOR(65 DOWNTO 0);
    b : IN STD_LOGIC_VECTOR(65 DOWNTO 0);
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    s : OUT STD_LOGIC_VECTOR(65 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_addsb_11_0_3c1d0ac9b6b8f403 USE ENTITY XilinxCoreLib.c_addsub_v11_0(behavioral)
    GENERIC MAP (
      c_a_type => 0,
      c_a_width => 66,
      c_add_mode => 0,
      c_ainit_val => "0",
      c_b_constant => 0,
      c_b_type => 0,
      c_b_value => "000000000000000000000000000000000000000000000000000000000000000000",
      c_b_width => 66,
      c_borrow_low => 1,
      c_bypass_low => 0,
      c_ce_overrides_bypass => 1,
      c_ce_overrides_sclr => 0,
      c_has_bypass => 0,
      c_has_c_in => 0,
      c_has_c_out => 0,
      c_has_ce => 1,
      c_has_sclr => 0,
      c_has_sinit => 0,
      c_has_sset => 0,
      c_implementation => 0,
      c_latency => 1,
      c_out_width => 66,
      c_sclr_overrides_sset => 1,
      c_sinit_val => "0",
      c_verbosity => 0,
      c_xdevicefamily => "virtex6"
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_addsb_11_0_3c1d0ac9b6b8f403
  PORT MAP (
    a => a,
    b => b,
    clk => clk,
    ce => ce,
    s => s
  );
-- synthesis translate_on

END addsb_11_0_3c1d0ac9b6b8f403_a;
--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2013 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
-- You must compile the wrapper file cntr_11_0_23bc6491dc8a06da.vhd when simulating
-- the core, cntr_11_0_23bc6491dc8a06da. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY cntr_11_0_23bc6491dc8a06da IS
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    q : OUT STD_LOGIC_VECTOR(13 DOWNTO 0)
  );
END cntr_11_0_23bc6491dc8a06da;

ARCHITECTURE cntr_11_0_23bc6491dc8a06da_a OF cntr_11_0_23bc6491dc8a06da IS
-- synthesis translate_off
COMPONENT wrapped_cntr_11_0_23bc6491dc8a06da
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    q : OUT STD_LOGIC_VECTOR(13 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_cntr_11_0_23bc6491dc8a06da USE ENTITY XilinxCoreLib.c_counter_binary_v11_0(behavioral)
    GENERIC MAP (
      c_ainit_val => "0",
      c_ce_overrides_sync => 0,
      c_count_by => "1",
      c_count_mode => 0,
      c_count_to => "1",
      c_fb_latency => 0,
      c_has_ce => 1,
      c_has_load => 0,
      c_has_sclr => 0,
      c_has_sinit => 1,
      c_has_sset => 0,
      c_has_thresh0 => 0,
      c_implementation => 0,
      c_latency => 1,
      c_load_low => 0,
      c_restrict_count => 0,
      c_sclr_overrides_sset => 1,
      c_sinit_val => "1",
      c_thresh0_value => "1",
      c_verbosity => 0,
      c_width => 14,
      c_xdevicefamily => "virtex6"
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_cntr_11_0_23bc6491dc8a06da
  PORT MAP (
    clk => clk,
    ce => ce,
    sinit => sinit,
    q => q
  );
-- synthesis translate_on

END cntr_11_0_23bc6491dc8a06da_a;
--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2013 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
-- You must compile the wrapper file cntr_11_0_33b670dfb2dd60f1.vhd when simulating
-- the core, cntr_11_0_33b670dfb2dd60f1. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY cntr_11_0_33b670dfb2dd60f1 IS
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    load : IN STD_LOGIC;
    l : IN STD_LOGIC_VECTOR(19 DOWNTO 0);
    q : OUT STD_LOGIC_VECTOR(19 DOWNTO 0)
  );
END cntr_11_0_33b670dfb2dd60f1;

ARCHITECTURE cntr_11_0_33b670dfb2dd60f1_a OF cntr_11_0_33b670dfb2dd60f1 IS
-- synthesis translate_off
COMPONENT wrapped_cntr_11_0_33b670dfb2dd60f1
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    load : IN STD_LOGIC;
    l : IN STD_LOGIC_VECTOR(19 DOWNTO 0);
    q : OUT STD_LOGIC_VECTOR(19 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_cntr_11_0_33b670dfb2dd60f1 USE ENTITY XilinxCoreLib.c_counter_binary_v11_0(behavioral)
    GENERIC MAP (
      c_ainit_val => "0",
      c_ce_overrides_sync => 0,
      c_count_by => "1",
      c_count_mode => 1,
      c_count_to => "1",
      c_fb_latency => 0,
      c_has_ce => 1,
      c_has_load => 1,
      c_has_sclr => 0,
      c_has_sinit => 1,
      c_has_sset => 0,
      c_has_thresh0 => 0,
      c_implementation => 0,
      c_latency => 1,
      c_load_low => 0,
      c_restrict_count => 0,
      c_sclr_overrides_sset => 1,
      c_sinit_val => "0",
      c_thresh0_value => "1",
      c_verbosity => 0,
      c_width => 20,
      c_xdevicefamily => "virtex6"
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_cntr_11_0_33b670dfb2dd60f1
  PORT MAP (
    clk => clk,
    ce => ce,
    sinit => sinit,
    load => load,
    l => l,
    q => q
  );
-- synthesis translate_on

END cntr_11_0_33b670dfb2dd60f1_a;
--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2013 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
-- You must compile the wrapper file cntr_11_0_5b0a1653ddb23333.vhd when simulating
-- the core, cntr_11_0_5b0a1653ddb23333. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY cntr_11_0_5b0a1653ddb23333 IS
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    q : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
  );
END cntr_11_0_5b0a1653ddb23333;

ARCHITECTURE cntr_11_0_5b0a1653ddb23333_a OF cntr_11_0_5b0a1653ddb23333 IS
-- synthesis translate_off
COMPONENT wrapped_cntr_11_0_5b0a1653ddb23333
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    q : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_cntr_11_0_5b0a1653ddb23333 USE ENTITY XilinxCoreLib.c_counter_binary_v11_0(behavioral)
    GENERIC MAP (
      c_ainit_val => "0",
      c_ce_overrides_sync => 0,
      c_count_by => "1",
      c_count_mode => 0,
      c_count_to => "1",
      c_fb_latency => 0,
      c_has_ce => 1,
      c_has_load => 0,
      c_has_sclr => 0,
      c_has_sinit => 1,
      c_has_sset => 0,
      c_has_thresh0 => 0,
      c_implementation => 0,
      c_latency => 1,
      c_load_low => 0,
      c_restrict_count => 0,
      c_sclr_overrides_sset => 1,
      c_sinit_val => "0",
      c_thresh0_value => "1",
      c_verbosity => 0,
      c_width => 16,
      c_xdevicefamily => "virtex6"
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_cntr_11_0_5b0a1653ddb23333
  PORT MAP (
    clk => clk,
    ce => ce,
    sinit => sinit,
    q => q
  );
-- synthesis translate_on

END cntr_11_0_5b0a1653ddb23333_a;
--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2013 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
-- You must compile the wrapper file cntr_11_0_5e62871cb125c52e.vhd when simulating
-- the core, cntr_11_0_5e62871cb125c52e. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY cntr_11_0_5e62871cb125c52e IS
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    load : IN STD_LOGIC;
    l : IN STD_LOGIC_VECTOR(63 DOWNTO 0);
    q : OUT STD_LOGIC_VECTOR(63 DOWNTO 0)
  );
END cntr_11_0_5e62871cb125c52e;

ARCHITECTURE cntr_11_0_5e62871cb125c52e_a OF cntr_11_0_5e62871cb125c52e IS
-- synthesis translate_off
COMPONENT wrapped_cntr_11_0_5e62871cb125c52e
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    load : IN STD_LOGIC;
    l : IN STD_LOGIC_VECTOR(63 DOWNTO 0);
    q : OUT STD_LOGIC_VECTOR(63 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_cntr_11_0_5e62871cb125c52e USE ENTITY XilinxCoreLib.c_counter_binary_v11_0(behavioral)
    GENERIC MAP (
      c_ainit_val => "0",
      c_ce_overrides_sync => 0,
      c_count_by => "1",
      c_count_mode => 0,
      c_count_to => "1",
      c_fb_latency => 0,
      c_has_ce => 1,
      c_has_load => 1,
      c_has_sclr => 0,
      c_has_sinit => 1,
      c_has_sset => 0,
      c_has_thresh0 => 0,
      c_implementation => 0,
      c_latency => 1,
      c_load_low => 0,
      c_restrict_count => 0,
      c_sclr_overrides_sset => 1,
      c_sinit_val => "0",
      c_thresh0_value => "1",
      c_verbosity => 0,
      c_width => 64,
      c_xdevicefamily => "virtex6"
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_cntr_11_0_5e62871cb125c52e
  PORT MAP (
    clk => clk,
    ce => ce,
    sinit => sinit,
    load => load,
    l => l,
    q => q
  );
-- synthesis translate_on

END cntr_11_0_5e62871cb125c52e_a;
--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2013 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
-- You must compile the wrapper file cntr_11_0_86806e294f737f4c.vhd when simulating
-- the core, cntr_11_0_86806e294f737f4c. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY cntr_11_0_86806e294f737f4c IS
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    q : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
  );
END cntr_11_0_86806e294f737f4c;

ARCHITECTURE cntr_11_0_86806e294f737f4c_a OF cntr_11_0_86806e294f737f4c IS
-- synthesis translate_off
COMPONENT wrapped_cntr_11_0_86806e294f737f4c
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    q : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_cntr_11_0_86806e294f737f4c USE ENTITY XilinxCoreLib.c_counter_binary_v11_0(behavioral)
    GENERIC MAP (
      c_ainit_val => "0",
      c_ce_overrides_sync => 0,
      c_count_by => "1",
      c_count_mode => 0,
      c_count_to => "1",
      c_fb_latency => 0,
      c_has_ce => 1,
      c_has_load => 0,
      c_has_sclr => 0,
      c_has_sinit => 1,
      c_has_sset => 0,
      c_has_thresh0 => 0,
      c_implementation => 0,
      c_latency => 1,
      c_load_low => 0,
      c_restrict_count => 0,
      c_sclr_overrides_sset => 1,
      c_sinit_val => "0",
      c_thresh0_value => "1",
      c_verbosity => 0,
      c_width => 8,
      c_xdevicefamily => "virtex6"
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_cntr_11_0_86806e294f737f4c
  PORT MAP (
    clk => clk,
    ce => ce,
    sinit => sinit,
    q => q
  );
-- synthesis translate_on

END cntr_11_0_86806e294f737f4c_a;
--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2014 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
-- You must compile the wrapper file cntr_11_0_bc4e334678893d0e.vhd when simulating
-- the core, cntr_11_0_bc4e334678893d0e. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY cntr_11_0_bc4e334678893d0e IS
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    load : IN STD_LOGIC;
    l : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
    q : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
  );
END cntr_11_0_bc4e334678893d0e;

ARCHITECTURE cntr_11_0_bc4e334678893d0e_a OF cntr_11_0_bc4e334678893d0e IS
-- synthesis translate_off
COMPONENT wrapped_cntr_11_0_bc4e334678893d0e
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    load : IN STD_LOGIC;
    l : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
    q : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_cntr_11_0_bc4e334678893d0e USE ENTITY XilinxCoreLib.c_counter_binary_v11_0(behavioral)
    GENERIC MAP (
      c_ainit_val => "0",
      c_ce_overrides_sync => 0,
      c_count_by => "1",
      c_count_mode => 1,
      c_count_to => "1",
      c_fb_latency => 0,
      c_has_ce => 1,
      c_has_load => 1,
      c_has_sclr => 0,
      c_has_sinit => 1,
      c_has_sset => 0,
      c_has_thresh0 => 0,
      c_implementation => 0,
      c_latency => 1,
      c_load_low => 0,
      c_restrict_count => 0,
      c_sclr_overrides_sset => 1,
      c_sinit_val => "0",
      c_thresh0_value => "1",
      c_verbosity => 0,
      c_width => 16,
      c_xdevicefamily => "virtex6"
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_cntr_11_0_bc4e334678893d0e
  PORT MAP (
    clk => clk,
    ce => ce,
    sinit => sinit,
    load => load,
    l => l,
    q => q
  );
-- synthesis translate_on

END cntr_11_0_bc4e334678893d0e_a;
--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2015 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
-- You must compile the wrapper file cntr_11_0_e1525560b82138e7.vhd when simulating
-- the core, cntr_11_0_e1525560b82138e7. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY cntr_11_0_e1525560b82138e7 IS
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    q : OUT STD_LOGIC_VECTOR(18 DOWNTO 0)
  );
END cntr_11_0_e1525560b82138e7;

ARCHITECTURE cntr_11_0_e1525560b82138e7_a OF cntr_11_0_e1525560b82138e7 IS
-- synthesis translate_off
COMPONENT wrapped_cntr_11_0_e1525560b82138e7
  PORT (
    clk : IN STD_LOGIC;
    ce : IN STD_LOGIC;
    sinit : IN STD_LOGIC;
    q : OUT STD_LOGIC_VECTOR(18 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_cntr_11_0_e1525560b82138e7 USE ENTITY XilinxCoreLib.c_counter_binary_v11_0(behavioral)
    GENERIC MAP (
      c_ainit_val => "0",
      c_ce_overrides_sync => 0,
      c_count_by => "1",
      c_count_mode => 0,
      c_count_to => "1",
      c_fb_latency => 0,
      c_has_ce => 1,
      c_has_load => 0,
      c_has_sclr => 0,
      c_has_sinit => 1,
      c_has_sset => 0,
      c_has_thresh0 => 0,
      c_implementation => 0,
      c_latency => 1,
      c_load_low => 0,
      c_restrict_count => 0,
      c_sclr_overrides_sset => 1,
      c_sinit_val => "0",
      c_thresh0_value => "1",
      c_verbosity => 0,
      c_width => 19,
      c_xdevicefamily => "virtex6"
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_cntr_11_0_e1525560b82138e7
  PORT MAP (
    clk => clk,
    ce => ce,
    sinit => sinit,
    q => q
  );
-- synthesis translate_on

END cntr_11_0_e1525560b82138e7_a;
--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2013 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
-- You must compile the wrapper file mult_11_2_7def12de86dcdc6a.vhd when simulating
-- the core, mult_11_2_7def12de86dcdc6a. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY mult_11_2_7def12de86dcdc6a IS
  PORT (
    clk : IN STD_LOGIC;
    a : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    b : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
    ce : IN STD_LOGIC;
    sclr : IN STD_LOGIC;
    p : OUT STD_LOGIC_VECTOR(19 DOWNTO 0)
  );
END mult_11_2_7def12de86dcdc6a;

ARCHITECTURE mult_11_2_7def12de86dcdc6a_a OF mult_11_2_7def12de86dcdc6a IS
-- synthesis translate_off
COMPONENT wrapped_mult_11_2_7def12de86dcdc6a
  PORT (
    clk : IN STD_LOGIC;
    a : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    b : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
    ce : IN STD_LOGIC;
    sclr : IN STD_LOGIC;
    p : OUT STD_LOGIC_VECTOR(19 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_mult_11_2_7def12de86dcdc6a USE ENTITY XilinxCoreLib.mult_gen_v11_2(behavioral)
    GENERIC MAP (
      c_a_type => 1,
      c_a_width => 4,
      c_b_type => 1,
      c_b_value => "10000001",
      c_b_width => 16,
      c_ccm_imp => 0,
      c_ce_overrides_sclr => 1,
      c_has_ce => 1,
      c_has_sclr => 1,
      c_has_zero_detect => 0,
      c_latency => 1,
      c_model_type => 0,
      c_mult_type => 1,
      c_optimize_goal => 1,
      c_out_high => 19,
      c_out_low => 0,
      c_round_output => 0,
      c_round_pt => 0,
      c_verbosity => 0,
      c_xdevicefamily => "virtex6"
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_mult_11_2_7def12de86dcdc6a
  PORT MAP (
    clk => clk,
    a => a,
    b => b,
    ce => ce,
    sclr => sclr,
    p => p
  );
-- synthesis translate_on

END mult_11_2_7def12de86dcdc6a_a;

-------------------------------------------------------------------
-- System Generator version 14.3 VHDL source file.
--
-- Copyright(C) 2012 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2012 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
package conv_pkg is
    constant simulating : boolean := false
      -- synopsys translate_off
        or true
      -- synopsys translate_on
    ;
    constant xlUnsigned : integer := 1;
    constant xlSigned : integer := 2;
    constant xlFloat : integer := 3;
    constant xlWrap : integer := 1;
    constant xlSaturate : integer := 2;
    constant xlTruncate : integer := 1;
    constant xlRound : integer := 2;
    constant xlRoundBanker : integer := 3;
    constant xlAddMode : integer := 1;
    constant xlSubMode : integer := 2;
    attribute black_box : boolean;
    attribute syn_black_box : boolean;
    attribute fpga_dont_touch: string;
    attribute box_type :  string;
    attribute keep : string;
    attribute syn_keep : boolean;
    function std_logic_vector_to_unsigned(inp : std_logic_vector) return unsigned;
    function unsigned_to_std_logic_vector(inp : unsigned) return std_logic_vector;
    function std_logic_vector_to_signed(inp : std_logic_vector) return signed;
    function signed_to_std_logic_vector(inp : signed) return std_logic_vector;
    function unsigned_to_signed(inp : unsigned) return signed;
    function signed_to_unsigned(inp : signed) return unsigned;
    function pos(inp : std_logic_vector; arith : INTEGER) return boolean;
    function all_same(inp: std_logic_vector) return boolean;
    function all_zeros(inp: std_logic_vector) return boolean;
    function is_point_five(inp: std_logic_vector) return boolean;
    function all_ones(inp: std_logic_vector) return boolean;
    function convert_type (inp : std_logic_vector; old_width, old_bin_pt,
                           old_arith, new_width, new_bin_pt, new_arith,
                           quantization, overflow : INTEGER)
        return std_logic_vector;
    function cast (inp : std_logic_vector; old_bin_pt,
                   new_width, new_bin_pt, new_arith : INTEGER)
        return std_logic_vector;
    function shift_division_result(quotient, fraction: std_logic_vector;
                                   fraction_width, shift_value, shift_dir: INTEGER)
        return std_logic_vector;
    function shift_op (inp: std_logic_vector;
                       result_width, shift_value, shift_dir: INTEGER)
        return std_logic_vector;
    function vec_slice (inp : std_logic_vector; upper, lower : INTEGER)
        return std_logic_vector;
    function s2u_slice (inp : signed; upper, lower : INTEGER)
        return unsigned;
    function u2u_slice (inp : unsigned; upper, lower : INTEGER)
        return unsigned;
    function s2s_cast (inp : signed; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return signed;
    function u2s_cast (inp : unsigned; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return signed;
    function s2u_cast (inp : signed; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return unsigned;
    function u2u_cast (inp : unsigned; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return unsigned;
    function u2v_cast (inp : unsigned; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return std_logic_vector;
    function s2v_cast (inp : signed; old_bin_pt,
                   new_width, new_bin_pt : INTEGER)
        return std_logic_vector;
    function trunc (inp : std_logic_vector; old_width, old_bin_pt, old_arith,
                    new_width, new_bin_pt, new_arith : INTEGER)
        return std_logic_vector;
    function round_towards_inf (inp : std_logic_vector; old_width, old_bin_pt,
                                old_arith, new_width, new_bin_pt,
                                new_arith : INTEGER) return std_logic_vector;
    function round_towards_even (inp : std_logic_vector; old_width, old_bin_pt,
                                old_arith, new_width, new_bin_pt,
                                new_arith : INTEGER) return std_logic_vector;
    function max_signed(width : INTEGER) return std_logic_vector;
    function min_signed(width : INTEGER) return std_logic_vector;
    function saturation_arith(inp:  std_logic_vector;  old_width, old_bin_pt,
                              old_arith, new_width, new_bin_pt, new_arith
                              : INTEGER) return std_logic_vector;
    function wrap_arith(inp:  std_logic_vector;  old_width, old_bin_pt,
                        old_arith, new_width, new_bin_pt, new_arith : INTEGER)
                        return std_logic_vector;
    function fractional_bits(a_bin_pt, b_bin_pt: INTEGER) return INTEGER;
    function integer_bits(a_width, a_bin_pt, b_width, b_bin_pt: INTEGER)
        return INTEGER;
    function sign_ext(inp : std_logic_vector; new_width : INTEGER)
        return std_logic_vector;
    function zero_ext(inp : std_logic_vector; new_width : INTEGER)
        return std_logic_vector;
    function zero_ext(inp : std_logic; new_width : INTEGER)
        return std_logic_vector;
    function extend_MSB(inp : std_logic_vector; new_width, arith : INTEGER)
        return std_logic_vector;
    function align_input(inp : std_logic_vector; old_width, delta, new_arith,
                          new_width: INTEGER)
        return std_logic_vector;
    function pad_LSB(inp : std_logic_vector; new_width: integer)
        return std_logic_vector;
    function pad_LSB(inp : std_logic_vector; new_width, arith : integer)
        return std_logic_vector;
    function max(L, R: INTEGER) return INTEGER;
    function min(L, R: INTEGER) return INTEGER;
    function "="(left,right: STRING) return boolean;
    function boolean_to_signed (inp : boolean; width: integer)
        return signed;
    function boolean_to_unsigned (inp : boolean; width: integer)
        return unsigned;
    function boolean_to_vector (inp : boolean)
        return std_logic_vector;
    function std_logic_to_vector (inp : std_logic)
        return std_logic_vector;
    function integer_to_std_logic_vector (inp : integer;  width, arith : integer)
        return std_logic_vector;
    function std_logic_vector_to_integer (inp : std_logic_vector;  arith : integer)
        return integer;
    function std_logic_to_integer(constant inp : std_logic := '0')
        return integer;
    function bin_string_element_to_std_logic_vector (inp : string;  width, index : integer)
        return std_logic_vector;
    function bin_string_to_std_logic_vector (inp : string)
        return std_logic_vector;
    function hex_string_to_std_logic_vector (inp : string; width : integer)
        return std_logic_vector;
    function makeZeroBinStr (width : integer) return STRING;
    function and_reduce(inp: std_logic_vector) return std_logic;
    -- synopsys translate_off
    function is_binary_string_invalid (inp : string)
        return boolean;
    function is_binary_string_undefined (inp : string)
        return boolean;
    function is_XorU(inp : std_logic_vector)
        return boolean;
    function to_real(inp : std_logic_vector; bin_pt : integer; arith : integer)
        return real;
    function std_logic_to_real(inp : std_logic; bin_pt : integer; arith : integer)
        return real;
    function real_to_std_logic_vector (inp : real;  width, bin_pt, arith : integer)
        return std_logic_vector;
    function real_string_to_std_logic_vector (inp : string;  width, bin_pt, arith : integer)
        return std_logic_vector;
    constant display_precision : integer := 20;
    function real_to_string (inp : real) return string;
    function valid_bin_string(inp : string) return boolean;
    function std_logic_vector_to_bin_string(inp : std_logic_vector) return string;
    function std_logic_to_bin_string(inp : std_logic) return string;
    function std_logic_vector_to_bin_string_w_point(inp : std_logic_vector; bin_pt : integer)
        return string;
    function real_to_bin_string(inp : real;  width, bin_pt, arith : integer)
        return string;
    type stdlogic_to_char_t is array(std_logic) of character;
    constant to_char : stdlogic_to_char_t := (
        'U' => 'U',
        'X' => 'X',
        '0' => '0',
        '1' => '1',
        'Z' => 'Z',
        'W' => 'W',
        'L' => 'L',
        'H' => 'H',
        '-' => '-');
    -- synopsys translate_on
end conv_pkg;
package body conv_pkg is
    function std_logic_vector_to_unsigned(inp : std_logic_vector)
        return unsigned
    is
    begin
        return unsigned (inp);
    end;
    function unsigned_to_std_logic_vector(inp : unsigned)
        return std_logic_vector
    is
    begin
        return std_logic_vector(inp);
    end;
    function std_logic_vector_to_signed(inp : std_logic_vector)
        return signed
    is
    begin
        return  signed (inp);
    end;
    function signed_to_std_logic_vector(inp : signed)
        return std_logic_vector
    is
    begin
        return std_logic_vector(inp);
    end;
    function unsigned_to_signed (inp : unsigned)
        return signed
    is
    begin
        return signed(std_logic_vector(inp));
    end;
    function signed_to_unsigned (inp : signed)
        return unsigned
    is
    begin
        return unsigned(std_logic_vector(inp));
    end;
    function pos(inp : std_logic_vector; arith : INTEGER)
        return boolean
    is
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
    begin
        vec := inp;
        if arith = xlUnsigned then
            return true;
        else
            if vec(width-1) = '0' then
                return true;
            else
                return false;
            end if;
        end if;
        return true;
    end;
    function max_signed(width : INTEGER)
        return std_logic_vector
    is
        variable ones : std_logic_vector(width-2 downto 0);
        variable result : std_logic_vector(width-1 downto 0);
    begin
        ones := (others => '1');
        result(width-1) := '0';
        result(width-2 downto 0) := ones;
        return result;
    end;
    function min_signed(width : INTEGER)
        return std_logic_vector
    is
        variable zeros : std_logic_vector(width-2 downto 0);
        variable result : std_logic_vector(width-1 downto 0);
    begin
        zeros := (others => '0');
        result(width-1) := '1';
        result(width-2 downto 0) := zeros;
        return result;
    end;
    function and_reduce(inp: std_logic_vector) return std_logic
    is
        variable result: std_logic;
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
    begin
        vec := inp;
        result := vec(0);
        if width > 1 then
            for i in 1 to width-1 loop
                result := result and vec(i);
            end loop;
        end if;
        return result;
    end;
    function all_same(inp: std_logic_vector) return boolean
    is
        variable result: boolean;
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
    begin
        vec := inp;
        result := true;
        if width > 0 then
            for i in 1 to width-1 loop
                if vec(i) /= vec(0) then
                    result := false;
                end if;
            end loop;
        end if;
        return result;
    end;
    function all_zeros(inp: std_logic_vector)
        return boolean
    is
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
        variable zero : std_logic_vector(width-1 downto 0);
        variable result : boolean;
    begin
        zero := (others => '0');
        vec := inp;
        -- synopsys translate_off
        if (is_XorU(vec)) then
            return false;
        end if;
         -- synopsys translate_on
        if (std_logic_vector_to_unsigned(vec) = std_logic_vector_to_unsigned(zero)) then
            result := true;
        else
            result := false;
        end if;
        return result;
    end;
    function is_point_five(inp: std_logic_vector)
        return boolean
    is
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
        variable result : boolean;
    begin
        vec := inp;
        -- synopsys translate_off
        if (is_XorU(vec)) then
            return false;
        end if;
         -- synopsys translate_on
        if (width > 1) then
           if ((vec(width-1) = '1') and (all_zeros(vec(width-2 downto 0)) = true)) then
               result := true;
           else
               result := false;
           end if;
        else
           if (vec(width-1) = '1') then
               result := true;
           else
               result := false;
           end if;
        end if;
        return result;
    end;
    function all_ones(inp: std_logic_vector)
        return boolean
    is
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
        variable one : std_logic_vector(width-1 downto 0);
        variable result : boolean;
    begin
        one := (others => '1');
        vec := inp;
        -- synopsys translate_off
        if (is_XorU(vec)) then
            return false;
        end if;
         -- synopsys translate_on
        if (std_logic_vector_to_unsigned(vec) = std_logic_vector_to_unsigned(one)) then
            result := true;
        else
            result := false;
        end if;
        return result;
    end;
    function full_precision_num_width(quantization, overflow, old_width,
                                      old_bin_pt, old_arith,
                                      new_width, new_bin_pt, new_arith : INTEGER)
        return integer
    is
        variable result : integer;
    begin
        result := old_width + 2;
        return result;
    end;
    function quantized_num_width(quantization, overflow, old_width, old_bin_pt,
                                 old_arith, new_width, new_bin_pt, new_arith
                                 : INTEGER)
        return integer
    is
        variable right_of_dp, left_of_dp, result : integer;
    begin
        right_of_dp := max(new_bin_pt, old_bin_pt);
        left_of_dp := max((new_width - new_bin_pt), (old_width - old_bin_pt));
        result := (old_width + 2) + (new_bin_pt - old_bin_pt);
        return result;
    end;
    function convert_type (inp : std_logic_vector; old_width, old_bin_pt,
                           old_arith, new_width, new_bin_pt, new_arith,
                           quantization, overflow : INTEGER)
        return std_logic_vector
    is
        constant fp_width : integer :=
            full_precision_num_width(quantization, overflow, old_width,
                                     old_bin_pt, old_arith, new_width,
                                     new_bin_pt, new_arith);
        constant fp_bin_pt : integer := old_bin_pt;
        constant fp_arith : integer := old_arith;
        variable full_precision_result : std_logic_vector(fp_width-1 downto 0);
        constant q_width : integer :=
            quantized_num_width(quantization, overflow, old_width, old_bin_pt,
                                old_arith, new_width, new_bin_pt, new_arith);
        constant q_bin_pt : integer := new_bin_pt;
        constant q_arith : integer := old_arith;
        variable quantized_result : std_logic_vector(q_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        result := (others => '0');
        full_precision_result := cast(inp, old_bin_pt, fp_width, fp_bin_pt,
                                      fp_arith);
        if (quantization = xlRound) then
            quantized_result := round_towards_inf(full_precision_result,
                                                  fp_width, fp_bin_pt,
                                                  fp_arith, q_width, q_bin_pt,
                                                  q_arith);
        elsif (quantization = xlRoundBanker) then
            quantized_result := round_towards_even(full_precision_result,
                                                  fp_width, fp_bin_pt,
                                                  fp_arith, q_width, q_bin_pt,
                                                  q_arith);
        else
            quantized_result := trunc(full_precision_result, fp_width, fp_bin_pt,
                                      fp_arith, q_width, q_bin_pt, q_arith);
        end if;
        if (overflow = xlSaturate) then
            result := saturation_arith(quantized_result, q_width, q_bin_pt,
                                       q_arith, new_width, new_bin_pt, new_arith);
        else
             result := wrap_arith(quantized_result, q_width, q_bin_pt, q_arith,
                                  new_width, new_bin_pt, new_arith);
        end if;
        return result;
    end;
    function cast (inp : std_logic_vector; old_bin_pt, new_width,
                   new_bin_pt, new_arith : INTEGER)
        return std_logic_vector
    is
        constant old_width : integer := inp'length;
        constant left_of_dp : integer := (new_width - new_bin_pt)
                                         - (old_width - old_bin_pt);
        constant right_of_dp : integer := (new_bin_pt - old_bin_pt);
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
        variable j   : integer;
    begin
        vec := inp;
        for i in new_width-1 downto 0 loop
            j := i - right_of_dp;
            if ( j > old_width-1) then
                if (new_arith = xlUnsigned) then
                    result(i) := '0';
                else
                    result(i) := vec(old_width-1);
                end if;
            elsif ( j >= 0) then
                result(i) := vec(j);
            else
                result(i) := '0';
            end if;
        end loop;
        return result;
    end;
    function shift_division_result(quotient, fraction: std_logic_vector;
                                   fraction_width, shift_value, shift_dir: INTEGER)
        return std_logic_vector
    is
        constant q_width : integer := quotient'length;
        constant f_width : integer := fraction'length;
        constant vec_MSB : integer := q_width+f_width-1;
        constant result_MSB : integer := q_width+fraction_width-1;
        constant result_LSB : integer := vec_MSB-result_MSB;
        variable vec : std_logic_vector(vec_MSB downto 0);
        variable result : std_logic_vector(result_MSB downto 0);
    begin
        vec := ( quotient & fraction );
        if shift_dir = 1 then
            for i in vec_MSB downto 0 loop
                if (i < shift_value) then
                     vec(i) := '0';
                else
                    vec(i) := vec(i-shift_value);
                end if;
            end loop;
        else
            for i in 0 to vec_MSB loop
                if (i > vec_MSB-shift_value) then
                    vec(i) := vec(vec_MSB);
                else
                    vec(i) := vec(i+shift_value);
                end if;
            end loop;
        end if;
        result := vec(vec_MSB downto result_LSB);
        return result;
    end;
    function shift_op (inp: std_logic_vector;
                       result_width, shift_value, shift_dir: INTEGER)
        return std_logic_vector
    is
        constant inp_width : integer := inp'length;
        constant vec_MSB : integer := inp_width-1;
        constant result_MSB : integer := result_width-1;
        constant result_LSB : integer := vec_MSB-result_MSB;
        variable vec : std_logic_vector(vec_MSB downto 0);
        variable result : std_logic_vector(result_MSB downto 0);
    begin
        vec := inp;
        if shift_dir = 1 then
            for i in vec_MSB downto 0 loop
                if (i < shift_value) then
                     vec(i) := '0';
                else
                    vec(i) := vec(i-shift_value);
                end if;
            end loop;
        else
            for i in 0 to vec_MSB loop
                if (i > vec_MSB-shift_value) then
                    vec(i) := vec(vec_MSB);
                else
                    vec(i) := vec(i+shift_value);
                end if;
            end loop;
        end if;
        result := vec(vec_MSB downto result_LSB);
        return result;
    end;
    function vec_slice (inp : std_logic_vector; upper, lower : INTEGER)
      return std_logic_vector
    is
    begin
        return inp(upper downto lower);
    end;
    function s2u_slice (inp : signed; upper, lower : INTEGER)
      return unsigned
    is
    begin
        return unsigned(vec_slice(std_logic_vector(inp), upper, lower));
    end;
    function u2u_slice (inp : unsigned; upper, lower : INTEGER)
      return unsigned
    is
    begin
        return unsigned(vec_slice(std_logic_vector(inp), upper, lower));
    end;
    function s2s_cast (inp : signed; old_bin_pt, new_width, new_bin_pt : INTEGER)
        return signed
    is
    begin
        return signed(cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlSigned));
    end;
    function s2u_cast (inp : signed; old_bin_pt, new_width,
                   new_bin_pt : INTEGER)
        return unsigned
    is
    begin
        return unsigned(cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlSigned));
    end;
    function u2s_cast (inp : unsigned; old_bin_pt, new_width,
                   new_bin_pt : INTEGER)
        return signed
    is
    begin
        return signed(cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlUnsigned));
    end;
    function u2u_cast (inp : unsigned; old_bin_pt, new_width,
                   new_bin_pt : INTEGER)
        return unsigned
    is
    begin
        return unsigned(cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlUnsigned));
    end;
    function u2v_cast (inp : unsigned; old_bin_pt, new_width,
                   new_bin_pt : INTEGER)
        return std_logic_vector
    is
    begin
        return cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlUnsigned);
    end;
    function s2v_cast (inp : signed; old_bin_pt, new_width,
                   new_bin_pt : INTEGER)
        return std_logic_vector
    is
    begin
        return cast(std_logic_vector(inp), old_bin_pt, new_width, new_bin_pt, xlSigned);
    end;
    function boolean_to_signed (inp : boolean; width : integer)
        return signed
    is
        variable result : signed(width - 1 downto 0);
    begin
        result := (others => '0');
        if inp then
          result(0) := '1';
        else
          result(0) := '0';
        end if;
        return result;
    end;
    function boolean_to_unsigned (inp : boolean; width : integer)
        return unsigned
    is
        variable result : unsigned(width - 1 downto 0);
    begin
        result := (others => '0');
        if inp then
          result(0) := '1';
        else
          result(0) := '0';
        end if;
        return result;
    end;
    function boolean_to_vector (inp : boolean)
        return std_logic_vector
    is
        variable result : std_logic_vector(1 - 1 downto 0);
    begin
        result := (others => '0');
        if inp then
          result(0) := '1';
        else
          result(0) := '0';
        end if;
        return result;
    end;
    function std_logic_to_vector (inp : std_logic)
        return std_logic_vector
    is
        variable result : std_logic_vector(1 - 1 downto 0);
    begin
        result(0) := inp;
        return result;
    end;
    function trunc (inp : std_logic_vector; old_width, old_bin_pt, old_arith,
                                new_width, new_bin_pt, new_arith : INTEGER)
        return std_logic_vector
    is
        constant right_of_dp : integer := (old_bin_pt - new_bin_pt);
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if right_of_dp >= 0 then
            if new_arith = xlUnsigned then
                result := zero_ext(vec(old_width-1 downto right_of_dp), new_width);
            else
                result := sign_ext(vec(old_width-1 downto right_of_dp), new_width);
            end if;
        else
            if new_arith = xlUnsigned then
                result := zero_ext(pad_LSB(vec, old_width +
                                           abs(right_of_dp)), new_width);
            else
                result := sign_ext(pad_LSB(vec, old_width +
                                           abs(right_of_dp)), new_width);
            end if;
        end if;
        return result;
    end;
    function round_towards_inf (inp : std_logic_vector; old_width, old_bin_pt,
                                old_arith, new_width, new_bin_pt, new_arith
                                : INTEGER)
        return std_logic_vector
    is
        constant right_of_dp : integer := (old_bin_pt - new_bin_pt);
        constant expected_new_width : integer :=  old_width - right_of_dp  + 1;
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable one_or_zero : std_logic_vector(new_width-1 downto 0);
        variable truncated_val : std_logic_vector(new_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if right_of_dp >= 0 then
            if new_arith = xlUnsigned then
                truncated_val := zero_ext(vec(old_width-1 downto right_of_dp),
                                          new_width);
            else
                truncated_val := sign_ext(vec(old_width-1 downto right_of_dp),
                                          new_width);
            end if;
        else
            if new_arith = xlUnsigned then
                truncated_val := zero_ext(pad_LSB(vec, old_width +
                                                  abs(right_of_dp)), new_width);
            else
                truncated_val := sign_ext(pad_LSB(vec, old_width +
                                                  abs(right_of_dp)), new_width);
            end if;
        end if;
        one_or_zero := (others => '0');
        if (new_arith = xlSigned) then
            if (vec(old_width-1) = '0') then
                one_or_zero(0) := '1';
            end if;
            if (right_of_dp >= 2) and (right_of_dp <= old_width) then
                if (all_zeros(vec(right_of_dp-2 downto 0)) = false) then
                    one_or_zero(0) := '1';
                end if;
            end if;
            if (right_of_dp >= 1) and (right_of_dp <= old_width) then
                if vec(right_of_dp-1) = '0' then
                    one_or_zero(0) := '0';
                end if;
            else
                one_or_zero(0) := '0';
            end if;
        else
            if (right_of_dp >= 1) and (right_of_dp <= old_width) then
                one_or_zero(0) :=  vec(right_of_dp-1);
            end if;
        end if;
        if new_arith = xlSigned then
            result := signed_to_std_logic_vector(std_logic_vector_to_signed(truncated_val) +
                                                 std_logic_vector_to_signed(one_or_zero));
        else
            result := unsigned_to_std_logic_vector(std_logic_vector_to_unsigned(truncated_val) +
                                                  std_logic_vector_to_unsigned(one_or_zero));
        end if;
        return result;
    end;
    function round_towards_even (inp : std_logic_vector; old_width, old_bin_pt,
                                old_arith, new_width, new_bin_pt, new_arith
                                : INTEGER)
        return std_logic_vector
    is
        constant right_of_dp : integer := (old_bin_pt - new_bin_pt);
        constant expected_new_width : integer :=  old_width - right_of_dp  + 1;
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable one_or_zero : std_logic_vector(new_width-1 downto 0);
        variable truncated_val : std_logic_vector(new_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if right_of_dp >= 0 then
            if new_arith = xlUnsigned then
                truncated_val := zero_ext(vec(old_width-1 downto right_of_dp),
                                          new_width);
            else
                truncated_val := sign_ext(vec(old_width-1 downto right_of_dp),
                                          new_width);
            end if;
        else
            if new_arith = xlUnsigned then
                truncated_val := zero_ext(pad_LSB(vec, old_width +
                                                  abs(right_of_dp)), new_width);
            else
                truncated_val := sign_ext(pad_LSB(vec, old_width +
                                                  abs(right_of_dp)), new_width);
            end if;
        end if;
        one_or_zero := (others => '0');
        if (right_of_dp >= 1) and (right_of_dp <= old_width) then
            if (is_point_five(vec(right_of_dp-1 downto 0)) = false) then
                one_or_zero(0) :=  vec(right_of_dp-1);
            else
                one_or_zero(0) :=  vec(right_of_dp);
            end if;
        end if;
        if new_arith = xlSigned then
            result := signed_to_std_logic_vector(std_logic_vector_to_signed(truncated_val) +
                                                 std_logic_vector_to_signed(one_or_zero));
        else
            result := unsigned_to_std_logic_vector(std_logic_vector_to_unsigned(truncated_val) +
                                                  std_logic_vector_to_unsigned(one_or_zero));
        end if;
        return result;
    end;
    function saturation_arith(inp:  std_logic_vector;  old_width, old_bin_pt,
                              old_arith, new_width, new_bin_pt, new_arith
                              : INTEGER)
        return std_logic_vector
    is
        constant left_of_dp : integer := (old_width - old_bin_pt) -
                                         (new_width - new_bin_pt);
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
        variable overflow : boolean;
    begin
        vec := inp;
        overflow := true;
        result := (others => '0');
        if (new_width >= old_width) then
            overflow := false;
        end if;
        if ((old_arith = xlSigned and new_arith = xlSigned) and (old_width > new_width)) then
            if all_same(vec(old_width-1 downto new_width-1)) then
                overflow := false;
            end if;
        end if;
        if (old_arith = xlSigned and new_arith = xlUnsigned) then
            if (old_width > new_width) then
                if all_zeros(vec(old_width-1 downto new_width)) then
                    overflow := false;
                end if;
            else
                if (old_width = new_width) then
                    if (vec(new_width-1) = '0') then
                        overflow := false;
                    end if;
                end if;
            end if;
        end if;
        if (old_arith = xlUnsigned and new_arith = xlUnsigned) then
            if (old_width > new_width) then
                if all_zeros(vec(old_width-1 downto new_width)) then
                    overflow := false;
                end if;
            else
                if (old_width = new_width) then
                    overflow := false;
                end if;
            end if;
        end if;
        if ((old_arith = xlUnsigned and new_arith = xlSigned) and (old_width > new_width)) then
            if all_same(vec(old_width-1 downto new_width-1)) then
                overflow := false;
            end if;
        end if;
        if overflow then
            if new_arith = xlSigned then
                if vec(old_width-1) = '0' then
                    result := max_signed(new_width);
                else
                    result := min_signed(new_width);
                end if;
            else
                if ((old_arith = xlSigned) and vec(old_width-1) = '1') then
                    result := (others => '0');
                else
                    result := (others => '1');
                end if;
            end if;
        else
            if (old_arith = xlSigned) and (new_arith = xlUnsigned) then
                if (vec(old_width-1) = '1') then
                    vec := (others => '0');
                end if;
            end if;
            if new_width <= old_width then
                result := vec(new_width-1 downto 0);
            else
                if new_arith = xlUnsigned then
                    result := zero_ext(vec, new_width);
                else
                    result := sign_ext(vec, new_width);
                end if;
            end if;
        end if;
        return result;
    end;
   function wrap_arith(inp:  std_logic_vector;  old_width, old_bin_pt,
                       old_arith, new_width, new_bin_pt, new_arith : INTEGER)
        return std_logic_vector
    is
        variable result : std_logic_vector(new_width-1 downto 0);
        variable result_arith : integer;
    begin
        if (old_arith = xlSigned) and (new_arith = xlUnsigned) then
            result_arith := xlSigned;
        end if;
        result := cast(inp, old_bin_pt, new_width, new_bin_pt, result_arith);
        return result;
    end;
    function fractional_bits(a_bin_pt, b_bin_pt: INTEGER) return INTEGER is
    begin
        return max(a_bin_pt, b_bin_pt);
    end;
    function integer_bits(a_width, a_bin_pt, b_width, b_bin_pt: INTEGER)
        return INTEGER is
    begin
        return  max(a_width - a_bin_pt, b_width - b_bin_pt);
    end;
    function pad_LSB(inp : std_logic_vector; new_width: integer)
        return STD_LOGIC_VECTOR
    is
        constant orig_width : integer := inp'length;
        variable vec : std_logic_vector(orig_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
        variable pos : integer;
        constant pad_pos : integer := new_width - orig_width - 1;
    begin
        vec := inp;
        pos := new_width-1;
        if (new_width >= orig_width) then
            for i in orig_width-1 downto 0 loop
                result(pos) := vec(i);
                pos := pos - 1;
            end loop;
            if pad_pos >= 0 then
                for i in pad_pos downto 0 loop
                    result(i) := '0';
                end loop;
            end if;
        end if;
        return result;
    end;
    function sign_ext(inp : std_logic_vector; new_width : INTEGER)
        return std_logic_vector
    is
        constant old_width : integer := inp'length;
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if new_width >= old_width then
            result(old_width-1 downto 0) := vec;
            if new_width-1 >= old_width then
                for i in new_width-1 downto old_width loop
                    result(i) := vec(old_width-1);
                end loop;
            end if;
        else
            result(new_width-1 downto 0) := vec(new_width-1 downto 0);
        end if;
        return result;
    end;
    function zero_ext(inp : std_logic_vector; new_width : INTEGER)
        return std_logic_vector
    is
        constant old_width : integer := inp'length;
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if new_width >= old_width then
            result(old_width-1 downto 0) := vec;
            if new_width-1 >= old_width then
                for i in new_width-1 downto old_width loop
                    result(i) := '0';
                end loop;
            end if;
        else
            result(new_width-1 downto 0) := vec(new_width-1 downto 0);
        end if;
        return result;
    end;
    function zero_ext(inp : std_logic; new_width : INTEGER)
        return std_logic_vector
    is
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        result(0) := inp;
        for i in new_width-1 downto 1 loop
            result(i) := '0';
        end loop;
        return result;
    end;
    function extend_MSB(inp : std_logic_vector; new_width, arith : INTEGER)
        return std_logic_vector
    is
        constant orig_width : integer := inp'length;
        variable vec : std_logic_vector(orig_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if arith = xlUnsigned then
            result := zero_ext(vec, new_width);
        else
            result := sign_ext(vec, new_width);
        end if;
        return result;
    end;
    function pad_LSB(inp : std_logic_vector; new_width, arith: integer)
        return STD_LOGIC_VECTOR
    is
        constant orig_width : integer := inp'length;
        variable vec : std_logic_vector(orig_width-1 downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
        variable pos : integer;
    begin
        vec := inp;
        pos := new_width-1;
        if (arith = xlUnsigned) then
            result(pos) := '0';
            pos := pos - 1;
        else
            result(pos) := vec(orig_width-1);
            pos := pos - 1;
        end if;
        if (new_width >= orig_width) then
            for i in orig_width-1 downto 0 loop
                result(pos) := vec(i);
                pos := pos - 1;
            end loop;
            if pos >= 0 then
                for i in pos downto 0 loop
                    result(i) := '0';
                end loop;
            end if;
        end if;
        return result;
    end;
    function align_input(inp : std_logic_vector; old_width, delta, new_arith,
                         new_width: INTEGER)
        return std_logic_vector
    is
        variable vec : std_logic_vector(old_width-1 downto 0);
        variable padded_inp : std_logic_vector((old_width + delta)-1  downto 0);
        variable result : std_logic_vector(new_width-1 downto 0);
    begin
        vec := inp;
        if delta > 0 then
            padded_inp := pad_LSB(vec, old_width+delta);
            result := extend_MSB(padded_inp, new_width, new_arith);
        else
            result := extend_MSB(vec, new_width, new_arith);
        end if;
        return result;
    end;
    function max(L, R: INTEGER) return INTEGER is
    begin
        if L > R then
            return L;
        else
            return R;
        end if;
    end;
    function min(L, R: INTEGER) return INTEGER is
    begin
        if L < R then
            return L;
        else
            return R;
        end if;
    end;
    function "="(left,right: STRING) return boolean is
    begin
        if (left'length /= right'length) then
            return false;
        else
            test : for i in 1 to left'length loop
                if left(i) /= right(i) then
                    return false;
                end if;
            end loop test;
            return true;
        end if;
    end;
    -- synopsys translate_off
    function is_binary_string_invalid (inp : string)
        return boolean
    is
        variable vec : string(1 to inp'length);
        variable result : boolean;
    begin
        vec := inp;
        result := false;
        for i in 1 to vec'length loop
            if ( vec(i) = 'X' ) then
                result := true;
            end if;
        end loop;
        return result;
    end;
    function is_binary_string_undefined (inp : string)
        return boolean
    is
        variable vec : string(1 to inp'length);
        variable result : boolean;
    begin
        vec := inp;
        result := false;
        for i in 1 to vec'length loop
            if ( vec(i) = 'U' ) then
                result := true;
            end if;
        end loop;
        return result;
    end;
    function is_XorU(inp : std_logic_vector)
        return boolean
    is
        constant width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
        variable result : boolean;
    begin
        vec := inp;
        result := false;
        for i in 0 to width-1 loop
            if (vec(i) = 'U') or (vec(i) = 'X') then
                result := true;
            end if;
        end loop;
        return result;
    end;
    function to_real(inp : std_logic_vector; bin_pt : integer; arith : integer)
        return real
    is
        variable  vec : std_logic_vector(inp'length-1 downto 0);
        variable result, shift_val, undefined_real : real;
        variable neg_num : boolean;
    begin
        vec := inp;
        result := 0.0;
        neg_num := false;
        if vec(inp'length-1) = '1' then
            neg_num := true;
        end if;
        for i in 0 to inp'length-1 loop
            if  vec(i) = 'U' or vec(i) = 'X' then
                return undefined_real;
            end if;
            if arith = xlSigned then
                if neg_num then
                    if vec(i) = '0' then
                        result := result + 2.0**i;
                    end if;
                else
                    if vec(i) = '1' then
                        result := result + 2.0**i;
                    end if;
                end if;
            else
                if vec(i) = '1' then
                    result := result + 2.0**i;
                end if;
            end if;
        end loop;
        if arith = xlSigned then
            if neg_num then
                result := result + 1.0;
                result := result * (-1.0);
            end if;
        end if;
        shift_val := 2.0**(-1*bin_pt);
        result := result * shift_val;
        return result;
    end;
    function std_logic_to_real(inp : std_logic; bin_pt : integer; arith : integer)
        return real
    is
        variable result : real := 0.0;
    begin
        if inp = '1' then
            result := 1.0;
        end if;
        if arith = xlSigned then
            assert false
                report "It doesn't make sense to convert a 1 bit number to a signed real.";
        end if;
        return result;
    end;
    -- synopsys translate_on
    function integer_to_std_logic_vector (inp : integer;  width, arith : integer)
        return std_logic_vector
    is
        variable result : std_logic_vector(width-1 downto 0);
        variable unsigned_val : unsigned(width-1 downto 0);
        variable signed_val : signed(width-1 downto 0);
    begin
        if (arith = xlSigned) then
            signed_val := to_signed(inp, width);
            result := signed_to_std_logic_vector(signed_val);
        else
            unsigned_val := to_unsigned(inp, width);
            result := unsigned_to_std_logic_vector(unsigned_val);
        end if;
        return result;
    end;
    function std_logic_vector_to_integer (inp : std_logic_vector;  arith : integer)
        return integer
    is
        constant width : integer := inp'length;
        variable unsigned_val : unsigned(width-1 downto 0);
        variable signed_val : signed(width-1 downto 0);
        variable result : integer;
    begin
        if (arith = xlSigned) then
            signed_val := std_logic_vector_to_signed(inp);
            result := to_integer(signed_val);
        else
            unsigned_val := std_logic_vector_to_unsigned(inp);
            result := to_integer(unsigned_val);
        end if;
        return result;
    end;
    function std_logic_to_integer(constant inp : std_logic := '0')
        return integer
    is
    begin
        if inp = '1' then
            return 1;
        else
            return 0;
        end if;
    end;
    function makeZeroBinStr (width : integer) return STRING is
        variable result : string(1 to width+3);
    begin
        result(1) := '0';
        result(2) := 'b';
        for i in 3 to width+2 loop
            result(i) := '0';
        end loop;
        result(width+3) := '.';
        return result;
    end;
    -- synopsys translate_off
    function real_string_to_std_logic_vector (inp : string;  width, bin_pt, arith : integer)
        return std_logic_vector
    is
        variable result : std_logic_vector(width-1 downto 0);
    begin
        result := (others => '0');
        return result;
    end;
    function real_to_std_logic_vector (inp : real;  width, bin_pt, arith : integer)
        return std_logic_vector
    is
        variable real_val : real;
        variable int_val : integer;
        variable result : std_logic_vector(width-1 downto 0) := (others => '0');
        variable unsigned_val : unsigned(width-1 downto 0) := (others => '0');
        variable signed_val : signed(width-1 downto 0) := (others => '0');
    begin
        real_val := inp;
        int_val := integer(real_val * 2.0**(bin_pt));
        if (arith = xlSigned) then
            signed_val := to_signed(int_val, width);
            result := signed_to_std_logic_vector(signed_val);
        else
            unsigned_val := to_unsigned(int_val, width);
            result := unsigned_to_std_logic_vector(unsigned_val);
        end if;
        return result;
    end;
    -- synopsys translate_on
    function valid_bin_string (inp : string)
        return boolean
    is
        variable vec : string(1 to inp'length);
    begin
        vec := inp;
        if (vec(1) = '0' and vec(2) = 'b') then
            return true;
        else
            return false;
        end if;
    end;
    function hex_string_to_std_logic_vector(inp: string; width : integer)
        return std_logic_vector is
        constant strlen       : integer := inp'LENGTH;
        variable result       : std_logic_vector(width-1 downto 0);
        variable bitval       : std_logic_vector((strlen*4)-1 downto 0);
        variable posn         : integer;
        variable ch           : character;
        variable vec          : string(1 to strlen);
    begin
        vec := inp;
        result := (others => '0');
        posn := (strlen*4)-1;
        for i in 1 to strlen loop
            ch := vec(i);
            case ch is
                when '0' => bitval(posn downto posn-3) := "0000";
                when '1' => bitval(posn downto posn-3) := "0001";
                when '2' => bitval(posn downto posn-3) := "0010";
                when '3' => bitval(posn downto posn-3) := "0011";
                when '4' => bitval(posn downto posn-3) := "0100";
                when '5' => bitval(posn downto posn-3) := "0101";
                when '6' => bitval(posn downto posn-3) := "0110";
                when '7' => bitval(posn downto posn-3) := "0111";
                when '8' => bitval(posn downto posn-3) := "1000";
                when '9' => bitval(posn downto posn-3) := "1001";
                when 'A' | 'a' => bitval(posn downto posn-3) := "1010";
                when 'B' | 'b' => bitval(posn downto posn-3) := "1011";
                when 'C' | 'c' => bitval(posn downto posn-3) := "1100";
                when 'D' | 'd' => bitval(posn downto posn-3) := "1101";
                when 'E' | 'e' => bitval(posn downto posn-3) := "1110";
                when 'F' | 'f' => bitval(posn downto posn-3) := "1111";
                when others => bitval(posn downto posn-3) := "XXXX";
                               -- synopsys translate_off
                               ASSERT false
                                   REPORT "Invalid hex value" SEVERITY ERROR;
                               -- synopsys translate_on
            end case;
            posn := posn - 4;
        end loop;
        if (width <= strlen*4) then
            result :=  bitval(width-1 downto 0);
        else
            result((strlen*4)-1 downto 0) := bitval;
        end if;
        return result;
    end;
    function bin_string_to_std_logic_vector (inp : string)
        return std_logic_vector
    is
        variable pos : integer;
        variable vec : string(1 to inp'length);
        variable result : std_logic_vector(inp'length-1 downto 0);
    begin
        vec := inp;
        pos := inp'length-1;
        result := (others => '0');
        for i in 1 to vec'length loop
            -- synopsys translate_off
            if (pos < 0) and (vec(i) = '0' or vec(i) = '1' or vec(i) = 'X' or vec(i) = 'U')  then
                assert false
                    report "Input string is larger than output std_logic_vector. Truncating output.";
                return result;
            end if;
            -- synopsys translate_on
            if vec(i) = '0' then
                result(pos) := '0';
                pos := pos - 1;
            end if;
            if vec(i) = '1' then
                result(pos) := '1';
                pos := pos - 1;
            end if;
            -- synopsys translate_off
            if (vec(i) = 'X' or vec(i) = 'U') then
                result(pos) := 'U';
                pos := pos - 1;
            end if;
            -- synopsys translate_on
        end loop;
        return result;
    end;
    function bin_string_element_to_std_logic_vector (inp : string;  width, index : integer)
        return std_logic_vector
    is
        constant str_width : integer := width + 4;
        constant inp_len : integer := inp'length;
        constant num_elements : integer := (inp_len + 1)/str_width;
        constant reverse_index : integer := (num_elements-1) - index;
        variable left_pos : integer;
        variable right_pos : integer;
        variable vec : string(1 to inp'length);
        variable result : std_logic_vector(width-1 downto 0);
    begin
        vec := inp;
        result := (others => '0');
        if (reverse_index = 0) and (reverse_index < num_elements) and (inp_len-3 >= width) then
            left_pos := 1;
            right_pos := width + 3;
            result := bin_string_to_std_logic_vector(vec(left_pos to right_pos));
        end if;
        if (reverse_index > 0) and (reverse_index < num_elements) and (inp_len-3 >= width) then
            left_pos := (reverse_index * str_width) + 1;
            right_pos := left_pos + width + 2;
            result := bin_string_to_std_logic_vector(vec(left_pos to right_pos));
        end if;
        return result;
    end;
   -- synopsys translate_off
    function std_logic_vector_to_bin_string(inp : std_logic_vector)
        return string
    is
        variable vec : std_logic_vector(1 to inp'length);
        variable result : string(vec'range);
    begin
        vec := inp;
        for i in vec'range loop
            result(i) := to_char(vec(i));
        end loop;
        return result;
    end;
    function std_logic_to_bin_string(inp : std_logic)
        return string
    is
        variable result : string(1 to 3);
    begin
        result(1) := '0';
        result(2) := 'b';
        result(3) := to_char(inp);
        return result;
    end;
    function std_logic_vector_to_bin_string_w_point(inp : std_logic_vector; bin_pt : integer)
        return string
    is
        variable width : integer := inp'length;
        variable vec : std_logic_vector(width-1 downto 0);
        variable str_pos : integer;
        variable result : string(1 to width+3);
    begin
        vec := inp;
        str_pos := 1;
        result(str_pos) := '0';
        str_pos := 2;
        result(str_pos) := 'b';
        str_pos := 3;
        for i in width-1 downto 0  loop
            if (((width+3) - bin_pt) = str_pos) then
                result(str_pos) := '.';
                str_pos := str_pos + 1;
            end if;
            result(str_pos) := to_char(vec(i));
            str_pos := str_pos + 1;
        end loop;
        if (bin_pt = 0) then
            result(str_pos) := '.';
        end if;
        return result;
    end;
    function real_to_bin_string(inp : real;  width, bin_pt, arith : integer)
        return string
    is
        variable result : string(1 to width);
        variable vec : std_logic_vector(width-1 downto 0);
    begin
        vec := real_to_std_logic_vector(inp, width, bin_pt, arith);
        result := std_logic_vector_to_bin_string(vec);
        return result;
    end;
    function real_to_string (inp : real) return string
    is
        variable result : string(1 to display_precision) := (others => ' ');
    begin
        result(real'image(inp)'range) := real'image(inp);
        return result;
    end;
    -- synopsys translate_on
end conv_pkg;

-------------------------------------------------------------------
-- System Generator version 14.3 VHDL source file.
--
-- Copyright(C) 2012 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2012 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
-- synopsys translate_off
library unisim;
use unisim.vcomponents.all;
-- synopsys translate_on
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity srl17e is
    generic (width : integer:=16;
             latency : integer :=8);
    port (clk   : in std_logic;
          ce    : in std_logic;
          d     : in std_logic_vector(width-1 downto 0);
          q     : out std_logic_vector(width-1 downto 0));
end srl17e;
architecture structural of srl17e is
    component SRL16E
        port (D   : in STD_ULOGIC;
              CE  : in STD_ULOGIC;
              CLK : in STD_ULOGIC;
              A0  : in STD_ULOGIC;
              A1  : in STD_ULOGIC;
              A2  : in STD_ULOGIC;
              A3  : in STD_ULOGIC;
              Q   : out STD_ULOGIC);
    end component;
    attribute syn_black_box of SRL16E : component is true;
    attribute fpga_dont_touch of SRL16E : component is "true";
    component FDE
        port(
            Q  :        out   STD_ULOGIC;
            D  :        in    STD_ULOGIC;
            C  :        in    STD_ULOGIC;
            CE :        in    STD_ULOGIC);
    end component;
    attribute syn_black_box of FDE : component is true;
    attribute fpga_dont_touch of FDE : component is "true";
    constant a : std_logic_vector(4 downto 0) :=
        integer_to_std_logic_vector(latency-2,5,xlSigned);
    signal d_delayed : std_logic_vector(width-1 downto 0);
    signal srl16_out : std_logic_vector(width-1 downto 0);
begin
    d_delayed <= d after 200 ps;
    reg_array : for i in 0 to width-1 generate
        srl16_used: if latency > 1 generate
            u1 : srl16e port map(clk => clk,
                                 d => d_delayed(i),
                                 q => srl16_out(i),
                                 ce => ce,
                                 a0 => a(0),
                                 a1 => a(1),
                                 a2 => a(2),
                                 a3 => a(3));
        end generate;
        srl16_not_used: if latency <= 1 generate
            srl16_out(i) <= d_delayed(i);
        end generate;
        fde_used: if latency /= 0  generate
            u2 : fde port map(c => clk,
                              d => srl16_out(i),
                              q => q(i),
                              ce => ce);
        end generate;
        fde_not_used: if latency = 0  generate
            q(i) <= srl16_out(i);
        end generate;
    end generate;
 end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity synth_reg is
    generic (width           : integer := 8;
             latency         : integer := 1);
    port (i       : in std_logic_vector(width-1 downto 0);
          ce      : in std_logic;
          clr     : in std_logic;
          clk     : in std_logic;
          o       : out std_logic_vector(width-1 downto 0));
end synth_reg;
architecture structural of synth_reg is
    component srl17e
        generic (width : integer:=16;
                 latency : integer :=8);
        port (clk : in std_logic;
              ce  : in std_logic;
              d   : in std_logic_vector(width-1 downto 0);
              q   : out std_logic_vector(width-1 downto 0));
    end component;
    function calc_num_srl17es (latency : integer)
        return integer
    is
        variable remaining_latency : integer;
        variable result : integer;
    begin
        result := latency / 17;
        remaining_latency := latency - (result * 17);
        if (remaining_latency /= 0) then
            result := result + 1;
        end if;
        return result;
    end;
    constant complete_num_srl17es : integer := latency / 17;
    constant num_srl17es : integer := calc_num_srl17es(latency);
    constant remaining_latency : integer := latency - (complete_num_srl17es * 17);
    type register_array is array (num_srl17es downto 0) of
        std_logic_vector(width-1 downto 0);
    signal z : register_array;
begin
    z(0) <= i;
    complete_ones : if complete_num_srl17es > 0 generate
        srl17e_array: for i in 0 to complete_num_srl17es-1 generate
            delay_comp : srl17e
                generic map (width => width,
                             latency => 17)
                port map (clk => clk,
                          ce  => ce,
                          d       => z(i),
                          q       => z(i+1));
        end generate;
    end generate;
    partial_one : if remaining_latency > 0 generate
        last_srl17e : srl17e
            generic map (width => width,
                         latency => remaining_latency)
            port map (clk => clk,
                      ce  => ce,
                      d   => z(num_srl17es-1),
                      q   => z(num_srl17es));
    end generate;
    o <= z(num_srl17es);
end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity synth_reg_reg is
    generic (width           : integer := 8;
             latency         : integer := 1);
    port (i       : in std_logic_vector(width-1 downto 0);
          ce      : in std_logic;
          clr     : in std_logic;
          clk     : in std_logic;
          o       : out std_logic_vector(width-1 downto 0));
end synth_reg_reg;
architecture behav of synth_reg_reg is
  type reg_array_type is array (latency-1 downto 0) of std_logic_vector(width -1 downto 0);
  signal reg_bank : reg_array_type := (others => (others => '0'));
  signal reg_bank_in : reg_array_type := (others => (others => '0'));
  attribute syn_allow_retiming : boolean;
  attribute syn_srlstyle : string;
  attribute syn_allow_retiming of reg_bank : signal is true;
  attribute syn_allow_retiming of reg_bank_in : signal is true;
  attribute syn_srlstyle of reg_bank : signal is "registers";
  attribute syn_srlstyle of reg_bank_in : signal is "registers";
begin
  latency_eq_0: if latency = 0 generate
    o <= i;
  end generate latency_eq_0;
  latency_gt_0: if latency >= 1 generate
    o <= reg_bank(latency-1);
    reg_bank_in(0) <= i;
    loop_gen: for idx in latency-2 downto 0 generate
      reg_bank_in(idx+1) <= reg_bank(idx);
    end generate loop_gen;
    sync_loop: for sync_idx in latency-1 downto 0 generate
      sync_proc: process (clk)
      begin
        if clk'event and clk = '1' then
          if clr = '1' then
            reg_bank_in <= (others => (others => '0'));
          elsif ce = '1'  then
            reg_bank(sync_idx) <= reg_bank_in(sync_idx);
          end if;
        end if;
      end process sync_proc;
    end generate sync_loop;
  end generate latency_gt_0;
end behav;

-------------------------------------------------------------------
-- System Generator version 14.3 VHDL source file.
--
-- Copyright(C) 2012 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2012 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
-- synopsys translate_off
library unisim;
use unisim.vcomponents.all;
-- synopsys translate_on
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity single_reg_w_init is
  generic (
    width: integer := 8;
    init_index: integer := 0;
    init_value: bit_vector := b"0000"
  );
  port (
    i: in std_logic_vector(width - 1 downto 0);
    ce: in std_logic;
    clr: in std_logic;
    clk: in std_logic;
    o: out std_logic_vector(width - 1 downto 0)
  );
end single_reg_w_init;
architecture structural of single_reg_w_init is
  function build_init_const(width: integer;
                            init_index: integer;
                            init_value: bit_vector)
    return std_logic_vector
  is
    variable result: std_logic_vector(width - 1 downto 0);
  begin
    if init_index = 0 then
      result := (others => '0');
    elsif init_index = 1 then
      result := (others => '0');
      result(0) := '1';
    else
      result := to_stdlogicvector(init_value);
    end if;
    return result;
  end;
  component fdre
    port (
      q: out std_ulogic;
      d: in  std_ulogic;
      c: in  std_ulogic;
      ce: in  std_ulogic;
      r: in  std_ulogic
    );
  end component;
  attribute syn_black_box of fdre: component is true;
  attribute fpga_dont_touch of fdre: component is "true";
  component fdse
    port (
      q: out std_ulogic;
      d: in  std_ulogic;
      c: in  std_ulogic;
      ce: in  std_ulogic;
      s: in  std_ulogic
    );
  end component;
  attribute syn_black_box of fdse: component is true;
  attribute fpga_dont_touch of fdse: component is "true";
  constant init_const: std_logic_vector(width - 1 downto 0)
    := build_init_const(width, init_index, init_value);
begin
  fd_prim_array: for index in 0 to width - 1 generate
    bit_is_0: if (init_const(index) = '0') generate
      fdre_comp: fdre
        port map (
          c => clk,
          d => i(index),
          q => o(index),
          ce => ce,
          r => clr
        );
    end generate;
    bit_is_1: if (init_const(index) = '1') generate
      fdse_comp: fdse
        port map (
          c => clk,
          d => i(index),
          q => o(index),
          ce => ce,
          s => clr
        );
    end generate;
  end generate;
end architecture structural;
-- synopsys translate_off
library unisim;
use unisim.vcomponents.all;
-- synopsys translate_on
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity synth_reg_w_init is
  generic (
    width: integer := 8;
    init_index: integer := 0;
    init_value: bit_vector := b"0000";
    latency: integer := 1
  );
  port (
    i: in std_logic_vector(width - 1 downto 0);
    ce: in std_logic;
    clr: in std_logic;
    clk: in std_logic;
    o: out std_logic_vector(width - 1 downto 0)
  );
end synth_reg_w_init;
architecture structural of synth_reg_w_init is
  component single_reg_w_init
    generic (
      width: integer := 8;
      init_index: integer := 0;
      init_value: bit_vector := b"0000"
    );
    port (
      i: in std_logic_vector(width - 1 downto 0);
      ce: in std_logic;
      clr: in std_logic;
      clk: in std_logic;
      o: out std_logic_vector(width - 1 downto 0)
    );
  end component;
  signal dly_i: std_logic_vector((latency + 1) * width - 1 downto 0);
  signal dly_clr: std_logic;
begin
  latency_eq_0: if (latency = 0) generate
    o <= i;
  end generate;
  latency_gt_0: if (latency >= 1) generate
    dly_i((latency + 1) * width - 1 downto latency * width) <= i
      after 200 ps;
    dly_clr <= clr after 200 ps;
    fd_array: for index in latency downto 1 generate
       reg_comp: single_reg_w_init
          generic map (
            width => width,
            init_index => init_index,
            init_value => init_value
          )
          port map (
            clk => clk,
            i => dly_i((index + 1) * width - 1 downto index * width),
            o => dly_i(index * width - 1 downto (index - 1) * width),
            ce => ce,
            clr => dly_clr
          );
    end generate;
    o <= dly_i(width - 1 downto 0);
  end generate;
end structural;

-------------------------------------------------------------------
-- System Generator version 14.3 VHDL source file.
--
-- Copyright(C) 2012 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2012 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity xldelay is
   generic(width        : integer := -1;
           latency      : integer := -1;
           reg_retiming : integer :=  0;
           reset        : integer :=  0);
   port(d       : in std_logic_vector (width-1 downto 0);
        ce      : in std_logic;
        clk     : in std_logic;
        en      : in std_logic;
        rst     : in std_logic;
        q       : out std_logic_vector (width-1 downto 0));
end xldelay;
architecture behavior of xldelay is
   component synth_reg
      generic (width       : integer;
               latency     : integer);
      port (i       : in std_logic_vector(width-1 downto 0);
            ce      : in std_logic;
            clr     : in std_logic;
            clk     : in std_logic;
            o       : out std_logic_vector(width-1 downto 0));
   end component;
   component synth_reg_reg
      generic (width       : integer;
               latency     : integer);
      port (i       : in std_logic_vector(width-1 downto 0);
            ce      : in std_logic;
            clr     : in std_logic;
            clk     : in std_logic;
            o       : out std_logic_vector(width-1 downto 0));
   end component;
   signal internal_ce  : std_logic;
begin
   internal_ce  <= ce and en;
   srl_delay: if ((reg_retiming = 0) and (reset = 0)) or (latency < 1) generate
     synth_reg_srl_inst : synth_reg
       generic map (
         width   => width,
         latency => latency)
       port map (
         i   => d,
         ce  => internal_ce,
         clr => '0',
         clk => clk,
         o   => q);
   end generate srl_delay;
   reg_delay: if ((reg_retiming = 1) or (reset = 1)) and (latency >= 1) generate
     synth_reg_reg_inst : synth_reg_reg
       generic map (
         width   => width,
         latency => latency)
       port map (
         i   => d,
         ce  => internal_ce,
         clr => rst,
         clk => clk,
         o   => q);
   end generate reg_delay;
end architecture behavior;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity inverter_e5b38cca3b is
  port (
    ip : in std_logic_vector((1 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end inverter_e5b38cca3b;


architecture behavior of inverter_e5b38cca3b is
  signal ip_1_26: boolean;
  type array_type_op_mem_22_20 is array (0 to (1 - 1)) of boolean;
  signal op_mem_22_20: array_type_op_mem_22_20 := (
    0 => false);
  signal op_mem_22_20_front_din: boolean;
  signal op_mem_22_20_back: boolean;
  signal op_mem_22_20_push_front_pop_back_en: std_logic;
  signal internal_ip_12_1_bitnot: boolean;
begin
  ip_1_26 <= ((ip) = "1");
  op_mem_22_20_back <= op_mem_22_20(0);
  proc_op_mem_22_20: process (clk)
  is
    variable i: integer;
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (op_mem_22_20_push_front_pop_back_en = '1')) then
        op_mem_22_20(0) <= op_mem_22_20_front_din;
      end if;
    end if;
  end process proc_op_mem_22_20;
  internal_ip_12_1_bitnot <= ((not boolean_to_vector(ip_1_26)) = "1");
  op_mem_22_20_push_front_pop_back_en <= '0';
  op <= boolean_to_vector(internal_ip_12_1_bitnot);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity logical_80f90b97d0 is
  port (
    d0 : in std_logic_vector((1 - 1) downto 0);
    d1 : in std_logic_vector((1 - 1) downto 0);
    y : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end logical_80f90b97d0;


architecture behavior of logical_80f90b97d0 is
  signal d0_1_24: std_logic;
  signal d1_1_27: std_logic;
  signal fully_2_1_bit: std_logic;
begin
  d0_1_24 <= d0(0);
  d1_1_27 <= d1(0);
  fully_2_1_bit <= d0_1_24 and d1_1_27;
  y <= std_logic_to_vector(fully_2_1_bit);
end behavior;


-------------------------------------------------------------------
-- System Generator version 14.3 VHDL source file.
--
-- Copyright(C) 2012 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2012 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
-- synopsys translate_off
library XilinxCoreLib;
-- synopsys translate_on
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity xlcounter_free_wlan_mac_hw is
  generic (
    core_name0: string := "";
    op_width: integer := 5;
    op_arith: integer := xlSigned
  );
  port (
    ce: in std_logic;
    clr: in std_logic;
    clk: in std_logic;
    op: out std_logic_vector(op_width - 1 downto 0);
    up: in std_logic_vector(0 downto 0) := (others => '0');
    load: in std_logic_vector(0 downto 0) := (others => '0');
    din: in std_logic_vector(op_width - 1 downto 0) := (others => '0');
    en: in std_logic_vector(0 downto 0);
    rst: in std_logic_vector(0 downto 0)
  );
end xlcounter_free_wlan_mac_hw ;
architecture behavior of xlcounter_free_wlan_mac_hw is
  component cntr_11_0_86806e294f737f4c
    port (
      clk: in std_logic;
      ce: in std_logic;
      SINIT: in std_logic;
      q: out std_logic_vector(op_width - 1 downto 0)
    );
  end component;

  attribute syn_black_box of cntr_11_0_86806e294f737f4c:
    component is true;
  attribute fpga_dont_touch of cntr_11_0_86806e294f737f4c:
    component is "true";
  attribute box_type of cntr_11_0_86806e294f737f4c:
    component  is "black_box";
  component cntr_11_0_5e62871cb125c52e
    port (
      clk: in std_logic;
      ce: in std_logic;
      SINIT: in std_logic;
      load: in std_logic;
      l: in std_logic_vector(op_width - 1 downto 0);
      q: out std_logic_vector(op_width - 1 downto 0)
    );
  end component;

  attribute syn_black_box of cntr_11_0_5e62871cb125c52e:
    component is true;
  attribute fpga_dont_touch of cntr_11_0_5e62871cb125c52e:
    component is "true";
  attribute box_type of cntr_11_0_5e62871cb125c52e:
    component  is "black_box";
  component cntr_11_0_23bc6491dc8a06da
    port (
      clk: in std_logic;
      ce: in std_logic;
      SINIT: in std_logic;
      q: out std_logic_vector(op_width - 1 downto 0)
    );
  end component;

  attribute syn_black_box of cntr_11_0_23bc6491dc8a06da:
    component is true;
  attribute fpga_dont_touch of cntr_11_0_23bc6491dc8a06da:
    component is "true";
  attribute box_type of cntr_11_0_23bc6491dc8a06da:
    component  is "black_box";
  component cntr_11_0_bc4e334678893d0e
    port (
      clk: in std_logic;
      ce: in std_logic;
      SINIT: in std_logic;
      load: in std_logic;
      l: in std_logic_vector(op_width - 1 downto 0);
      q: out std_logic_vector(op_width - 1 downto 0)
    );
  end component;

  attribute syn_black_box of cntr_11_0_bc4e334678893d0e:
    component is true;
  attribute fpga_dont_touch of cntr_11_0_bc4e334678893d0e:
    component is "true";
  attribute box_type of cntr_11_0_bc4e334678893d0e:
    component  is "black_box";
  component cntr_11_0_5b0a1653ddb23333
    port (
      clk: in std_logic;
      ce: in std_logic;
      SINIT: in std_logic;
      q: out std_logic_vector(op_width - 1 downto 0)
    );
  end component;

  attribute syn_black_box of cntr_11_0_5b0a1653ddb23333:
    component is true;
  attribute fpga_dont_touch of cntr_11_0_5b0a1653ddb23333:
    component is "true";
  attribute box_type of cntr_11_0_5b0a1653ddb23333:
    component  is "black_box";
  component cntr_11_0_33b670dfb2dd60f1
    port (
      clk: in std_logic;
      ce: in std_logic;
      SINIT: in std_logic;
      load: in std_logic;
      l: in std_logic_vector(op_width - 1 downto 0);
      q: out std_logic_vector(op_width - 1 downto 0)
    );
  end component;

  attribute syn_black_box of cntr_11_0_33b670dfb2dd60f1:
    component is true;
  attribute fpga_dont_touch of cntr_11_0_33b670dfb2dd60f1:
    component is "true";
  attribute box_type of cntr_11_0_33b670dfb2dd60f1:
    component  is "black_box";
  component cntr_11_0_e1525560b82138e7
    port (
      clk: in std_logic;
      ce: in std_logic;
      SINIT: in std_logic;
      q: out std_logic_vector(op_width - 1 downto 0)
    );
  end component;

  attribute syn_black_box of cntr_11_0_e1525560b82138e7:
    component is true;
  attribute fpga_dont_touch of cntr_11_0_e1525560b82138e7:
    component is "true";
  attribute box_type of cntr_11_0_e1525560b82138e7:
    component  is "black_box";
-- synopsys translate_off
  constant zeroVec: std_logic_vector(op_width - 1 downto 0) := (others => '0');
  constant oneVec: std_logic_vector(op_width - 1 downto 0) := (others => '1');
  constant zeroStr: string(1 to op_width) :=
    std_logic_vector_to_bin_string(zeroVec);
  constant oneStr: string(1 to op_width) :=
    std_logic_vector_to_bin_string(oneVec);
-- synopsys translate_on
  signal core_sinit: std_logic;
  signal core_ce: std_logic;
  signal op_net: std_logic_vector(op_width - 1 downto 0);
begin
  core_ce <= ce and en(0);
  core_sinit <= (clr or rst(0)) and ce;
  op <= op_net;
  comp0: if ((core_name0 = "cntr_11_0_86806e294f737f4c")) generate
    core_instance0: cntr_11_0_86806e294f737f4c
      port map (
        clk => clk,
        ce => core_ce,
        SINIT => core_sinit,
        q => op_net
      );
  end generate;
  comp1: if ((core_name0 = "cntr_11_0_5e62871cb125c52e")) generate
    core_instance1: cntr_11_0_5e62871cb125c52e
      port map (
        clk => clk,
        ce => core_ce,
        SINIT => core_sinit,
        load => load(0),
        l => din,
        q => op_net
      );
  end generate;
  comp2: if ((core_name0 = "cntr_11_0_23bc6491dc8a06da")) generate
    core_instance2: cntr_11_0_23bc6491dc8a06da
      port map (
        clk => clk,
        ce => core_ce,
        SINIT => core_sinit,
        q => op_net
      );
  end generate;
  comp3: if ((core_name0 = "cntr_11_0_bc4e334678893d0e")) generate
    core_instance3: cntr_11_0_bc4e334678893d0e
      port map (
        clk => clk,
        ce => core_ce,
        SINIT => core_sinit,
        load => load(0),
        l => din,
        q => op_net
      );
  end generate;
  comp4: if ((core_name0 = "cntr_11_0_5b0a1653ddb23333")) generate
    core_instance4: cntr_11_0_5b0a1653ddb23333
      port map (
        clk => clk,
        ce => core_ce,
        SINIT => core_sinit,
        q => op_net
      );
  end generate;
  comp5: if ((core_name0 = "cntr_11_0_33b670dfb2dd60f1")) generate
    core_instance5: cntr_11_0_33b670dfb2dd60f1
      port map (
        clk => clk,
        ce => core_ce,
        SINIT => core_sinit,
        load => load(0),
        l => din,
        q => op_net
      );
  end generate;
  comp6: if ((core_name0 = "cntr_11_0_e1525560b82138e7")) generate
    core_instance6: cntr_11_0_e1525560b82138e7
      port map (
        clk => clk,
        ce => core_ce,
        SINIT => core_sinit,
        q => op_net
      );
  end generate;
end behavior;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity constant_5f4d695836 is
  port (
    op : out std_logic_vector((8 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end constant_5f4d695836;


architecture behavior of constant_5f4d695836 is
begin
  op <= "10011111";
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity logical_aacf6e1b0e is
  port (
    d0 : in std_logic_vector((1 - 1) downto 0);
    d1 : in std_logic_vector((1 - 1) downto 0);
    y : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end logical_aacf6e1b0e;


architecture behavior of logical_aacf6e1b0e is
  signal d0_1_24: std_logic;
  signal d1_1_27: std_logic;
  signal fully_2_1_bit: std_logic;
begin
  d0_1_24 <= d0(0);
  d1_1_27 <= d1(0);
  fully_2_1_bit <= d0_1_24 or d1_1_27;
  y <= std_logic_to_vector(fully_2_1_bit);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_54048c8b02 is
  port (
    a : in std_logic_vector((8 - 1) downto 0);
    b : in std_logic_vector((8 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_54048c8b02;


architecture behavior of relational_54048c8b02 is
  signal a_1_31: unsigned((8 - 1) downto 0);
  signal b_1_34: unsigned((8 - 1) downto 0);
  signal result_12_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  result_12_3_rel <= a_1_31 = b_1_34;
  op <= boolean_to_vector(result_12_3_rel);
end behavior;


-------------------------------------------------------------------
-- System Generator version 14.3 VHDL source file.
--
-- Copyright(C) 2012 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2012 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use work.conv_pkg.all;
entity xlslice is
    generic (
        new_msb      : integer := 9;
        new_lsb      : integer := 1;
        x_width      : integer := 16;
        y_width      : integer := 8);
    port (
        x : in std_logic_vector (x_width-1 downto 0);
        y : out std_logic_vector (y_width-1 downto 0));
end xlslice;
architecture behavior of xlslice is
begin
    y <= x(new_msb downto new_lsb);
end  behavior;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity concat_62c4475a80 is
  port (
    in0 : in std_logic_vector((32 - 1) downto 0);
    in1 : in std_logic_vector((32 - 1) downto 0);
    y : out std_logic_vector((64 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end concat_62c4475a80;


architecture behavior of concat_62c4475a80 is
  signal in0_1_23: unsigned((32 - 1) downto 0);
  signal in1_1_27: unsigned((32 - 1) downto 0);
  signal y_2_1_concat: unsigned((64 - 1) downto 0);
begin
  in0_1_23 <= std_logic_vector_to_unsigned(in0);
  in1_1_27 <= std_logic_vector_to_unsigned(in1);
  y_2_1_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(in0_1_23) & unsigned_to_std_logic_vector(in1_1_27));
  y <= unsigned_to_std_logic_vector(y_2_1_concat);
end behavior;


-------------------------------------------------------------------
-- System Generator version 14.3 VHDL source file.
--
-- Copyright(C) 2012 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2012 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity xlregister is
   generic (d_width          : integer := 5;
            init_value       : bit_vector := b"00");
   port (d   : in std_logic_vector (d_width-1 downto 0);
         rst : in std_logic_vector(0 downto 0) := "0";
         en  : in std_logic_vector(0 downto 0) := "1";
         ce  : in std_logic;
         clk : in std_logic;
         q   : out std_logic_vector (d_width-1 downto 0));
end xlregister;
architecture behavior of xlregister is
   component synth_reg_w_init
      generic (width      : integer;
               init_index : integer;
               init_value : bit_vector;
               latency    : integer);
      port (i   : in std_logic_vector(width-1 downto 0);
            ce  : in std_logic;
            clr : in std_logic;
            clk : in std_logic;
            o   : out std_logic_vector(width-1 downto 0));
   end component;
   -- synopsys translate_off
   signal real_d, real_q           : real;
   -- synopsys translate_on
   signal internal_clr             : std_logic;
   signal internal_ce              : std_logic;
begin
   internal_clr <= rst(0) and ce;
   internal_ce  <= en(0) and ce;
   synth_reg_inst : synth_reg_w_init
      generic map (width      => d_width,
                   init_index => 2,
                   init_value => init_value,
                   latency    => 1)
      port map (i   => d,
                ce  => internal_ce,
                clr => internal_clr,
                clk => clk,
                o   => q);
end architecture behavior;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity constant_6293007044 is
  port (
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end constant_6293007044;


architecture behavior of constant_6293007044 is
begin
  op <= "1";
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity constant_963ed6358a is
  port (
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end constant_963ed6358a;


architecture behavior of constant_963ed6358a is
begin
  op <= "0";
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity logical_6cb8f0ce02 is
  port (
    d0 : in std_logic_vector((1 - 1) downto 0);
    d1 : in std_logic_vector((1 - 1) downto 0);
    d2 : in std_logic_vector((1 - 1) downto 0);
    y : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end logical_6cb8f0ce02;


architecture behavior of logical_6cb8f0ce02 is
  signal d0_1_24: std_logic;
  signal d1_1_27: std_logic;
  signal d2_1_30: std_logic;
  signal fully_2_1_bit: std_logic;
begin
  d0_1_24 <= d0(0);
  d1_1_27 <= d1(0);
  d2_1_30 <= d2(0);
  fully_2_1_bit <= d0_1_24 or d1_1_27 or d2_1_30;
  y <= std_logic_to_vector(fully_2_1_bit);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_e528f2ec9d is
  port (
    a : in std_logic_vector((16 - 1) downto 0);
    b : in std_logic_vector((1 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_e528f2ec9d;


architecture behavior of relational_e528f2ec9d is
  signal a_1_31: unsigned((16 - 1) downto 0);
  signal b_1_34: unsigned((1 - 1) downto 0);
  signal cast_18_16: unsigned((16 - 1) downto 0);
  signal result_18_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  cast_18_16 <= u2u_cast(b_1_34, 0, 16, 0);
  result_18_3_rel <= a_1_31 > cast_18_16;
  op <= boolean_to_vector(result_18_3_rel);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_fe0d6a6e93 is
  port (
    a : in std_logic_vector((14 - 1) downto 0);
    b : in std_logic_vector((14 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_fe0d6a6e93;


architecture behavior of relational_fe0d6a6e93 is
  signal a_1_31: unsigned((14 - 1) downto 0);
  signal b_1_34: unsigned((14 - 1) downto 0);
  signal result_22_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  result_22_3_rel <= a_1_31 >= b_1_34;
  op <= boolean_to_vector(result_22_3_rel);
end behavior;


-------------------------------------------------------------------
-- System Generator version 14.3 VHDL source file.
--
-- Copyright(C) 2012 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2012 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity convert_func_call is
    generic (
        din_width    : integer := 16;
        din_bin_pt   : integer := 4;
        din_arith    : integer := xlUnsigned;
        dout_width   : integer := 8;
        dout_bin_pt  : integer := 2;
        dout_arith   : integer := xlUnsigned;
        quantization : integer := xlTruncate;
        overflow     : integer := xlWrap);
    port (
        din : in std_logic_vector (din_width-1 downto 0);
        result : out std_logic_vector (dout_width-1 downto 0));
end convert_func_call;
architecture behavior of convert_func_call is
begin
    result <= convert_type(din, din_width, din_bin_pt, din_arith,
                           dout_width, dout_bin_pt, dout_arith,
                           quantization, overflow);
end behavior;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;
entity xlconvert is
    generic (
        din_width    : integer := 16;
        din_bin_pt   : integer := 4;
        din_arith    : integer := xlUnsigned;
        dout_width   : integer := 8;
        dout_bin_pt  : integer := 2;
        dout_arith   : integer := xlUnsigned;
        en_width     : integer := 1;
        en_bin_pt    : integer := 0;
        en_arith     : integer := xlUnsigned;
        bool_conversion : integer :=0;
        latency      : integer := 0;
        quantization : integer := xlTruncate;
        overflow     : integer := xlWrap);
    port (
        din : in std_logic_vector (din_width-1 downto 0);
        en  : in std_logic_vector (en_width-1 downto 0);
        ce  : in std_logic;
        clr : in std_logic;
        clk : in std_logic;
        dout : out std_logic_vector (dout_width-1 downto 0));
end xlconvert;
architecture behavior of xlconvert is
    component synth_reg
        generic (width       : integer;
                 latency     : integer);
        port (i       : in std_logic_vector(width-1 downto 0);
              ce      : in std_logic;
              clr     : in std_logic;
              clk     : in std_logic;
              o       : out std_logic_vector(width-1 downto 0));
    end component;
    component convert_func_call
        generic (
            din_width    : integer := 16;
            din_bin_pt   : integer := 4;
            din_arith    : integer := xlUnsigned;
            dout_width   : integer := 8;
            dout_bin_pt  : integer := 2;
            dout_arith   : integer := xlUnsigned;
            quantization : integer := xlTruncate;
            overflow     : integer := xlWrap);
        port (
            din : in std_logic_vector (din_width-1 downto 0);
            result : out std_logic_vector (dout_width-1 downto 0));
    end component;
    -- synopsys translate_off
    -- synopsys translate_on
    signal result : std_logic_vector(dout_width-1 downto 0);
    signal internal_ce : std_logic;
begin
    -- synopsys translate_off
    -- synopsys translate_on
    internal_ce <= ce and en(0);

    bool_conversion_generate : if (bool_conversion = 1)
    generate
      result <= din;
    end generate;
    std_conversion_generate : if (bool_conversion = 0)
    generate
      convert : convert_func_call
        generic map (
          din_width   => din_width,
          din_bin_pt  => din_bin_pt,
          din_arith   => din_arith,
          dout_width  => dout_width,
          dout_bin_pt => dout_bin_pt,
          dout_arith  => dout_arith,
          quantization => quantization,
          overflow     => overflow)
        port map (
          din => din,
          result => result);
    end generate;
    latency_test : if (latency > 0) generate
        reg : synth_reg
            generic map (
              width => dout_width,
              latency => latency
            )
            port map (
              i => result,
              ce => internal_ce,
              clr => clr,
              clk => clk,
              o => dout
            );
    end generate;
    latency0 : if (latency = 0)
    generate
        dout <= result;
    end generate latency0;
end  behavior;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity mux_a54904b290 is
  port (
    sel : in std_logic_vector((1 - 1) downto 0);
    d0 : in std_logic_vector((16 - 1) downto 0);
    d1 : in std_logic_vector((16 - 1) downto 0);
    y : out std_logic_vector((16 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end mux_a54904b290;


architecture behavior of mux_a54904b290 is
  signal sel_1_20: std_logic;
  signal d0_1_24: std_logic_vector((16 - 1) downto 0);
  signal d1_1_27: std_logic_vector((16 - 1) downto 0);
  signal sel_internal_2_1_convert: std_logic_vector((1 - 1) downto 0);
  signal unregy_join_6_1: std_logic_vector((16 - 1) downto 0);
begin
  sel_1_20 <= sel(0);
  d0_1_24 <= d0;
  d1_1_27 <= d1;
  sel_internal_2_1_convert <= cast(std_logic_to_vector(sel_1_20), 0, 1, 0, xlUnsigned);
  proc_switch_6_1: process (d0_1_24, d1_1_27, sel_internal_2_1_convert)
  is
  begin
    case sel_internal_2_1_convert is 
      when "0" =>
        unregy_join_6_1 <= d0_1_24;
      when others =>
        unregy_join_6_1 <= d1_1_27;
    end case;
  end process proc_switch_6_1;
  y <= unregy_join_6_1;
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_53a2345101 is
  port (
    a : in std_logic_vector((16 - 1) downto 0);
    b : in std_logic_vector((1 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_53a2345101;


architecture behavior of relational_53a2345101 is
  signal a_1_31: unsigned((16 - 1) downto 0);
  signal b_1_34: unsigned((1 - 1) downto 0);
  signal cast_12_17: unsigned((16 - 1) downto 0);
  signal result_12_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  cast_12_17 <= u2u_cast(b_1_34, 0, 16, 0);
  result_12_3_rel <= a_1_31 = cast_12_17;
  op <= boolean_to_vector(result_12_3_rel);
end behavior;


-------------------------------------------------------------------
-- System Generator version 14.3 VHDL source file.
--
-- Copyright(C) 2012 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2012 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity axi_sgiface is
    generic (
        -- AXI specific.
        -- TODO: need to figure out a way to pass these generics from outside
        C_S_AXI_SUPPORT_BURST   : integer := 0;
        -- TODO: fix the internal ID width to 8
        C_S_AXI_ID_WIDTH        : integer := 8;
        C_S_AXI_DATA_WIDTH      : integer := 32;
        C_S_AXI_ADDR_WIDTH      : integer := 32;
        C_S_AXI_TOTAL_ADDR_LEN  : integer := 12;
        C_S_AXI_LINEAR_ADDR_LEN : integer := 8;
        C_S_AXI_BANK_ADDR_LEN   : integer := 2;
        C_S_AXI_AWLEN_WIDTH     : integer := 8;
        C_S_AXI_ARLEN_WIDTH     : integer := 8
    );
    port (
        -- General.
        AXI_AClk      : in  std_logic;
        AXI_AResetN    : in  std_logic;
        -- not used
        AXI_Ce        : in  std_logic;
  
        -- AXI Port.
        S_AXI_AWADDR  : in  std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
        S_AXI_AWID    : in  std_logic_vector(C_S_AXI_ID_WIDTH-1 downto 0);
        S_AXI_AWLEN   : in  std_logic_vector(C_S_AXI_AWLEN_WIDTH-1 downto 0);
        S_AXI_AWSIZE  : in  std_logic_vector(2 downto 0);
        S_AXI_AWBURST : in  std_logic_vector(1 downto 0);
        S_AXI_AWLOCK  : in  std_logic_vector(1 downto 0);
        S_AXI_AWCACHE : in  std_logic_vector(3 downto 0);
        S_AXI_AWPROT  : in  std_logic_vector(2 downto 0);
        S_AXI_AWVALID : in  std_logic;
        S_AXI_AWREADY : out std_logic;
        
        S_AXI_WLAST   : in  std_logic;
        S_AXI_WDATA   : in  std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        S_AXI_WSTRB   : in  std_logic_vector((C_S_AXI_DATA_WIDTH/8)-1 downto 0);
        S_AXI_WVALID  : in  std_logic;
        S_AXI_WREADY  : out std_logic;
        
        S_AXI_BRESP   : out std_logic_vector(1 downto 0);
        S_AXI_BID     : out std_logic_vector(C_S_AXI_ID_WIDTH-1 downto 0);
        S_AXI_BVALID  : out std_logic;
        S_AXI_BREADY  : in  std_logic;
        
        S_AXI_ARADDR  : in  std_logic_vector(C_S_AXI_ADDR_WIDTH-1 downto 0);
        S_AXI_ARID    : in  std_logic_vector(C_S_AXI_ID_WIDTH-1 downto 0);
        S_AXI_ARLEN   : in  std_logic_vector(C_S_AXI_ARLEN_WIDTH-1 downto 0);
        S_AXI_ARSIZE  : in  std_logic_vector(2 downto 0);
        S_AXI_ARBURST : in  std_logic_vector(1 downto 0);
        S_AXI_ARLOCK  : in  std_logic_vector(1 downto 0);
        S_AXI_ARCACHE : in  std_logic_vector(3 downto 0);
        S_AXI_ARPROT  : in  std_logic_vector(2 downto 0);
        S_AXI_ARVALID : in  std_logic;
        S_AXI_ARREADY : out std_logic;
        
        -- 'From Register'
        -- 'NAV_VALUE'
        sm_NAV_VALUE_dout : in std_logic_vector(32-1 downto 0);
        -- 'BACKOFF_COUNTER'
        sm_BACKOFF_COUNTER_dout : in std_logic_vector(32-1 downto 0);
        -- 'PHY_RX_PARAMS'
        sm_PHY_RX_PARAMS_dout : in std_logic_vector(32-1 downto 0);
        -- 'LATEST_RX_BYTE'
        sm_LATEST_RX_BYTE_dout : in std_logic_vector(32-1 downto 0);
        -- 'TX_START_TIMESTAMP_MSB'
        sm_TX_START_TIMESTAMP_MSB_dout : in std_logic_vector(32-1 downto 0);
        -- 'TX_START_TIMESTAMP_LSB'
        sm_TX_START_TIMESTAMP_LSB_dout : in std_logic_vector(32-1 downto 0);
        -- 'RX_START_TIMESTAMP_MSB'
        sm_RX_START_TIMESTAMP_MSB_dout : in std_logic_vector(32-1 downto 0);
        -- 'RX_START_TIMESTAMP_LSB'
        sm_RX_START_TIMESTAMP_LSB_dout : in std_logic_vector(32-1 downto 0);
        -- 'TIMESTAMP_MSB'
        sm_TIMESTAMP_MSB_dout : in std_logic_vector(32-1 downto 0);
        -- 'TIMESTAMP_LSB'
        sm_TIMESTAMP_LSB_dout : in std_logic_vector(32-1 downto 0);
        -- 'Status'
        sm_Status_dout : in std_logic_vector(32-1 downto 0);
        -- 'To Register'
        -- 'TX_CTRL_B_PARAMS'
        sm_TX_CTRL_B_PARAMS_dout : in std_logic_vector(32-1 downto 0);
        sm_TX_CTRL_B_PARAMS_din  : out std_logic_vector(32-1 downto 0);
        sm_TX_CTRL_B_PARAMS_en   : out std_logic;
        -- 'TX_CTRL_A_GAINS'
        sm_TX_CTRL_A_GAINS_dout : in std_logic_vector(32-1 downto 0);
        sm_TX_CTRL_A_GAINS_din  : out std_logic_vector(32-1 downto 0);
        sm_TX_CTRL_A_GAINS_en   : out std_logic;
        -- 'TX_CTRL_A_PARAMS'
        sm_TX_CTRL_A_PARAMS_dout : in std_logic_vector(32-1 downto 0);
        sm_TX_CTRL_A_PARAMS_din  : out std_logic_vector(32-1 downto 0);
        sm_TX_CTRL_A_PARAMS_en   : out std_logic;
        -- 'POST_RX_TIMERS'
        sm_POST_RX_TIMERS_dout : in std_logic_vector(32-1 downto 0);
        sm_POST_RX_TIMERS_din  : out std_logic_vector(32-1 downto 0);
        sm_POST_RX_TIMERS_en   : out std_logic;
        -- 'TX_CTRL_B_GAINS'
        sm_TX_CTRL_B_GAINS_dout : in std_logic_vector(32-1 downto 0);
        sm_TX_CTRL_B_GAINS_din  : out std_logic_vector(32-1 downto 0);
        sm_TX_CTRL_B_GAINS_en   : out std_logic;
        -- 'POST_TX_TIMERS'
        sm_POST_TX_TIMERS_dout : in std_logic_vector(32-1 downto 0);
        sm_POST_TX_TIMERS_din  : out std_logic_vector(32-1 downto 0);
        sm_POST_TX_TIMERS_en   : out std_logic;
        -- 'TIMESTAMP_INSERT_OFFSET'
        sm_TIMESTAMP_INSERT_OFFSET_dout : in std_logic_vector(32-1 downto 0);
        sm_TIMESTAMP_INSERT_OFFSET_din  : out std_logic_vector(32-1 downto 0);
        sm_TIMESTAMP_INSERT_OFFSET_en   : out std_logic;
        -- 'TIMESTAMP_SET_LSB'
        sm_TIMESTAMP_SET_LSB_dout : in std_logic_vector(32-1 downto 0);
        sm_TIMESTAMP_SET_LSB_din  : out std_logic_vector(32-1 downto 0);
        sm_TIMESTAMP_SET_LSB_en   : out std_logic;
        -- 'TIMESTAMP_SET_MSB'
        sm_TIMESTAMP_SET_MSB_dout : in std_logic_vector(32-1 downto 0);
        sm_TIMESTAMP_SET_MSB_din  : out std_logic_vector(32-1 downto 0);
        sm_TIMESTAMP_SET_MSB_en   : out std_logic;
        -- 'CALIB_TIMES'
        sm_CALIB_TIMES_dout : in std_logic_vector(32-1 downto 0);
        sm_CALIB_TIMES_din  : out std_logic_vector(32-1 downto 0);
        sm_CALIB_TIMES_en   : out std_logic;
        -- 'IFS_INTERVALS2'
        sm_IFS_INTERVALS2_dout : in std_logic_vector(32-1 downto 0);
        sm_IFS_INTERVALS2_din  : out std_logic_vector(32-1 downto 0);
        sm_IFS_INTERVALS2_en   : out std_logic;
        -- 'IFS_INTERVALS1'
        sm_IFS_INTERVALS1_dout : in std_logic_vector(32-1 downto 0);
        sm_IFS_INTERVALS1_din  : out std_logic_vector(32-1 downto 0);
        sm_IFS_INTERVALS1_en   : out std_logic;
        -- 'TX_START'
        sm_TX_START_dout : in std_logic_vector(32-1 downto 0);
        sm_TX_START_din  : out std_logic_vector(32-1 downto 0);
        sm_TX_START_en   : out std_logic;
        -- 'Control'
        sm_Control_dout : in std_logic_vector(32-1 downto 0);
        sm_Control_din  : out std_logic_vector(32-1 downto 0);
        sm_Control_en   : out std_logic;
        -- 'NAV_MATCH_ADDR_1'
        sm_NAV_MATCH_ADDR_1_dout : in std_logic_vector(32-1 downto 0);
        sm_NAV_MATCH_ADDR_1_din  : out std_logic_vector(32-1 downto 0);
        sm_NAV_MATCH_ADDR_1_en   : out std_logic;
        -- 'NAV_MATCH_ADDR_2'
        sm_NAV_MATCH_ADDR_2_dout : in std_logic_vector(32-1 downto 0);
        sm_NAV_MATCH_ADDR_2_din  : out std_logic_vector(32-1 downto 0);
        sm_NAV_MATCH_ADDR_2_en   : out std_logic;
        -- 'BACKOFF_CTRL'
        sm_BACKOFF_CTRL_dout : in std_logic_vector(32-1 downto 0);
        sm_BACKOFF_CTRL_din  : out std_logic_vector(32-1 downto 0);
        sm_BACKOFF_CTRL_en   : out std_logic;
        -- 'From FIFO'
        -- 'To FIFO'
        -- 'Shared Memory'

        S_AXI_RLAST   : out std_logic;
        S_AXI_RID     : out std_logic_vector(C_S_AXI_ID_WIDTH-1 downto 0);
        S_AXI_RDATA   : out std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
        S_AXI_RRESP   : out std_logic_vector(1 downto 0);
        S_AXI_RVALID  : out std_logic;
        S_AXI_RREADY  : in  std_logic
    );
end entity axi_sgiface;

architecture IMP of axi_sgiface is

-- Internal signals for write channel.
signal S_AXI_BVALID_i       : std_logic;
signal S_AXI_BID_i          : std_logic_vector(C_S_AXI_ID_WIDTH-1 downto 0);
signal S_AXI_WREADY_i       : std_logic;
  
-- Internal signals for read channels.
signal S_AXI_ARLEN_i        : std_logic_vector(C_S_AXI_ARLEN_WIDTH-1 downto 0);
signal S_AXI_RLAST_i        : std_logic;
signal S_AXI_RREADY_i       : std_logic;
signal S_AXI_RVALID_i       : std_logic;
signal S_AXI_RDATA_i        : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal S_AXI_RID_i          : std_logic_vector(C_S_AXI_ID_WIDTH-1 downto 0);

-- for read channel
signal read_bank_addr_i     : std_logic_vector(C_S_AXI_BANK_ADDR_LEN-1 downto 0);
signal read_linear_addr_i   : std_logic_vector(C_S_AXI_LINEAR_ADDR_LEN-1 downto 0);
-- for write channel
signal write_bank_addr_i    : std_logic_vector(C_S_AXI_BANK_ADDR_LEN-1 downto 0);
signal write_linear_addr_i  : std_logic_vector(C_S_AXI_LINEAR_ADDR_LEN-1 downto 0);

signal reg_bank_out_i       : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal fifo_bank_out_i      : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal shmem_bank_out_i     : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
    
-- 'From Register'
-- 'NAV_VALUE'
signal sm_NAV_VALUE_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'BACKOFF_COUNTER'
signal sm_BACKOFF_COUNTER_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'PHY_RX_PARAMS'
signal sm_PHY_RX_PARAMS_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'LATEST_RX_BYTE'
signal sm_LATEST_RX_BYTE_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'TX_START_TIMESTAMP_MSB'
signal sm_TX_START_TIMESTAMP_MSB_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'TX_START_TIMESTAMP_LSB'
signal sm_TX_START_TIMESTAMP_LSB_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'RX_START_TIMESTAMP_MSB'
signal sm_RX_START_TIMESTAMP_MSB_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'RX_START_TIMESTAMP_LSB'
signal sm_RX_START_TIMESTAMP_LSB_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'TIMESTAMP_MSB'
signal sm_TIMESTAMP_MSB_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'TIMESTAMP_LSB'
signal sm_TIMESTAMP_LSB_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'Status'
signal sm_Status_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'To Register'
-- 'TX_CTRL_B_PARAMS'
signal sm_TX_CTRL_B_PARAMS_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_TX_CTRL_B_PARAMS_en_i    : std_logic;
signal sm_TX_CTRL_B_PARAMS_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'TX_CTRL_A_GAINS'
signal sm_TX_CTRL_A_GAINS_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_TX_CTRL_A_GAINS_en_i    : std_logic;
signal sm_TX_CTRL_A_GAINS_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'TX_CTRL_A_PARAMS'
signal sm_TX_CTRL_A_PARAMS_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_TX_CTRL_A_PARAMS_en_i    : std_logic;
signal sm_TX_CTRL_A_PARAMS_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'POST_RX_TIMERS'
signal sm_POST_RX_TIMERS_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_POST_RX_TIMERS_en_i    : std_logic;
signal sm_POST_RX_TIMERS_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'TX_CTRL_B_GAINS'
signal sm_TX_CTRL_B_GAINS_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_TX_CTRL_B_GAINS_en_i    : std_logic;
signal sm_TX_CTRL_B_GAINS_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'POST_TX_TIMERS'
signal sm_POST_TX_TIMERS_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_POST_TX_TIMERS_en_i    : std_logic;
signal sm_POST_TX_TIMERS_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'TIMESTAMP_INSERT_OFFSET'
signal sm_TIMESTAMP_INSERT_OFFSET_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_TIMESTAMP_INSERT_OFFSET_en_i    : std_logic;
signal sm_TIMESTAMP_INSERT_OFFSET_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'TIMESTAMP_SET_LSB'
signal sm_TIMESTAMP_SET_LSB_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_TIMESTAMP_SET_LSB_en_i    : std_logic;
signal sm_TIMESTAMP_SET_LSB_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'TIMESTAMP_SET_MSB'
signal sm_TIMESTAMP_SET_MSB_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_TIMESTAMP_SET_MSB_en_i    : std_logic;
signal sm_TIMESTAMP_SET_MSB_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'CALIB_TIMES'
signal sm_CALIB_TIMES_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_CALIB_TIMES_en_i    : std_logic;
signal sm_CALIB_TIMES_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'IFS_INTERVALS2'
signal sm_IFS_INTERVALS2_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_IFS_INTERVALS2_en_i    : std_logic;
signal sm_IFS_INTERVALS2_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'IFS_INTERVALS1'
signal sm_IFS_INTERVALS1_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_IFS_INTERVALS1_en_i    : std_logic;
signal sm_IFS_INTERVALS1_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'TX_START'
signal sm_TX_START_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_TX_START_en_i    : std_logic;
signal sm_TX_START_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'Control'
signal sm_Control_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_Control_en_i    : std_logic;
signal sm_Control_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'NAV_MATCH_ADDR_1'
signal sm_NAV_MATCH_ADDR_1_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_NAV_MATCH_ADDR_1_en_i    : std_logic;
signal sm_NAV_MATCH_ADDR_1_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'NAV_MATCH_ADDR_2'
signal sm_NAV_MATCH_ADDR_2_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_NAV_MATCH_ADDR_2_en_i    : std_logic;
signal sm_NAV_MATCH_ADDR_2_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'BACKOFF_CTRL'
signal sm_BACKOFF_CTRL_din_i   : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
signal sm_BACKOFF_CTRL_en_i    : std_logic;
signal sm_BACKOFF_CTRL_dout_i  : std_logic_vector(C_S_AXI_DATA_WIDTH-1 downto 0);
-- 'From FIFO'
-- 'To FIFO'
-- 'Shared Memory'

type t_read_state is (IDLE, READ_PREP, READ_DATA);
signal read_state : t_read_state;

type t_write_state is (IDLE, WRITE_DATA, WRITE_RESPONSE);
signal write_state : t_write_state;

type t_memmap_state is (READ, WRITE);
signal memmap_state : t_memmap_state;

constant C_READ_PREP_DELAY : std_logic_vector(1 downto 0) := "11";

signal read_prep_counter : std_logic_vector(1 downto 0);
signal read_addr_counter : std_logic_vector(C_S_AXI_ARLEN_WIDTH-1 downto 0);
signal read_data_counter : std_logic_vector(C_S_AXI_ARLEN_WIDTH-1 downto 0);

-- enable of shared BRAMs
signal s_shram_en : std_logic;

signal write_addr_valid : std_logic;
signal write_ready : std_logic;

-- 're' of From/To FIFOs
signal s_fifo_re : std_logic;
-- 'we' of To FIFOs
signal s_fifo_we : std_logic;

begin

-- enable for 'Shared Memory' blocks

-- conversion to match with the data bus width
-- 'From Register'
-- 'NAV_VALUE'
gen_sm_NAV_VALUE_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_NAV_VALUE_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_NAV_VALUE_dout_i;
sm_NAV_VALUE_dout_i(32-1 downto 0) <= sm_NAV_VALUE_dout;
-- 'BACKOFF_COUNTER'
gen_sm_BACKOFF_COUNTER_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_BACKOFF_COUNTER_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_BACKOFF_COUNTER_dout_i;
sm_BACKOFF_COUNTER_dout_i(32-1 downto 0) <= sm_BACKOFF_COUNTER_dout;
-- 'PHY_RX_PARAMS'
gen_sm_PHY_RX_PARAMS_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_PHY_RX_PARAMS_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_PHY_RX_PARAMS_dout_i;
sm_PHY_RX_PARAMS_dout_i(32-1 downto 0) <= sm_PHY_RX_PARAMS_dout;
-- 'LATEST_RX_BYTE'
gen_sm_LATEST_RX_BYTE_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_LATEST_RX_BYTE_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_LATEST_RX_BYTE_dout_i;
sm_LATEST_RX_BYTE_dout_i(32-1 downto 0) <= sm_LATEST_RX_BYTE_dout;
-- 'TX_START_TIMESTAMP_MSB'
gen_sm_TX_START_TIMESTAMP_MSB_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TX_START_TIMESTAMP_MSB_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TX_START_TIMESTAMP_MSB_dout_i;
sm_TX_START_TIMESTAMP_MSB_dout_i(32-1 downto 0) <= sm_TX_START_TIMESTAMP_MSB_dout;
-- 'TX_START_TIMESTAMP_LSB'
gen_sm_TX_START_TIMESTAMP_LSB_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TX_START_TIMESTAMP_LSB_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TX_START_TIMESTAMP_LSB_dout_i;
sm_TX_START_TIMESTAMP_LSB_dout_i(32-1 downto 0) <= sm_TX_START_TIMESTAMP_LSB_dout;
-- 'RX_START_TIMESTAMP_MSB'
gen_sm_RX_START_TIMESTAMP_MSB_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_RX_START_TIMESTAMP_MSB_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_RX_START_TIMESTAMP_MSB_dout_i;
sm_RX_START_TIMESTAMP_MSB_dout_i(32-1 downto 0) <= sm_RX_START_TIMESTAMP_MSB_dout;
-- 'RX_START_TIMESTAMP_LSB'
gen_sm_RX_START_TIMESTAMP_LSB_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_RX_START_TIMESTAMP_LSB_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_RX_START_TIMESTAMP_LSB_dout_i;
sm_RX_START_TIMESTAMP_LSB_dout_i(32-1 downto 0) <= sm_RX_START_TIMESTAMP_LSB_dout;
-- 'TIMESTAMP_MSB'
gen_sm_TIMESTAMP_MSB_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TIMESTAMP_MSB_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TIMESTAMP_MSB_dout_i;
sm_TIMESTAMP_MSB_dout_i(32-1 downto 0) <= sm_TIMESTAMP_MSB_dout;
-- 'TIMESTAMP_LSB'
gen_sm_TIMESTAMP_LSB_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TIMESTAMP_LSB_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TIMESTAMP_LSB_dout_i;
sm_TIMESTAMP_LSB_dout_i(32-1 downto 0) <= sm_TIMESTAMP_LSB_dout;
-- 'Status'
gen_sm_Status_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_Status_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_Status_dout_i;
sm_Status_dout_i(32-1 downto 0) <= sm_Status_dout;
-- 'To Register'
-- 'TX_CTRL_B_PARAMS'
sm_TX_CTRL_B_PARAMS_din     <= sm_TX_CTRL_B_PARAMS_din_i(32-1 downto 0);
sm_TX_CTRL_B_PARAMS_en      <= sm_TX_CTRL_B_PARAMS_en_i;
gen_sm_TX_CTRL_B_PARAMS_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TX_CTRL_B_PARAMS_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TX_CTRL_B_PARAMS_dout_i;
sm_TX_CTRL_B_PARAMS_dout_i(32-1 downto 0) <= sm_TX_CTRL_B_PARAMS_dout;
-- 'TX_CTRL_A_GAINS'
sm_TX_CTRL_A_GAINS_din     <= sm_TX_CTRL_A_GAINS_din_i(32-1 downto 0);
sm_TX_CTRL_A_GAINS_en      <= sm_TX_CTRL_A_GAINS_en_i;
gen_sm_TX_CTRL_A_GAINS_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TX_CTRL_A_GAINS_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TX_CTRL_A_GAINS_dout_i;
sm_TX_CTRL_A_GAINS_dout_i(32-1 downto 0) <= sm_TX_CTRL_A_GAINS_dout;
-- 'TX_CTRL_A_PARAMS'
sm_TX_CTRL_A_PARAMS_din     <= sm_TX_CTRL_A_PARAMS_din_i(32-1 downto 0);
sm_TX_CTRL_A_PARAMS_en      <= sm_TX_CTRL_A_PARAMS_en_i;
gen_sm_TX_CTRL_A_PARAMS_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TX_CTRL_A_PARAMS_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TX_CTRL_A_PARAMS_dout_i;
sm_TX_CTRL_A_PARAMS_dout_i(32-1 downto 0) <= sm_TX_CTRL_A_PARAMS_dout;
-- 'POST_RX_TIMERS'
sm_POST_RX_TIMERS_din     <= sm_POST_RX_TIMERS_din_i(32-1 downto 0);
sm_POST_RX_TIMERS_en      <= sm_POST_RX_TIMERS_en_i;
gen_sm_POST_RX_TIMERS_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_POST_RX_TIMERS_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_POST_RX_TIMERS_dout_i;
sm_POST_RX_TIMERS_dout_i(32-1 downto 0) <= sm_POST_RX_TIMERS_dout;
-- 'TX_CTRL_B_GAINS'
sm_TX_CTRL_B_GAINS_din     <= sm_TX_CTRL_B_GAINS_din_i(32-1 downto 0);
sm_TX_CTRL_B_GAINS_en      <= sm_TX_CTRL_B_GAINS_en_i;
gen_sm_TX_CTRL_B_GAINS_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TX_CTRL_B_GAINS_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TX_CTRL_B_GAINS_dout_i;
sm_TX_CTRL_B_GAINS_dout_i(32-1 downto 0) <= sm_TX_CTRL_B_GAINS_dout;
-- 'POST_TX_TIMERS'
sm_POST_TX_TIMERS_din     <= sm_POST_TX_TIMERS_din_i(32-1 downto 0);
sm_POST_TX_TIMERS_en      <= sm_POST_TX_TIMERS_en_i;
gen_sm_POST_TX_TIMERS_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_POST_TX_TIMERS_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_POST_TX_TIMERS_dout_i;
sm_POST_TX_TIMERS_dout_i(32-1 downto 0) <= sm_POST_TX_TIMERS_dout;
-- 'TIMESTAMP_INSERT_OFFSET'
sm_TIMESTAMP_INSERT_OFFSET_din     <= sm_TIMESTAMP_INSERT_OFFSET_din_i(32-1 downto 0);
sm_TIMESTAMP_INSERT_OFFSET_en      <= sm_TIMESTAMP_INSERT_OFFSET_en_i;
gen_sm_TIMESTAMP_INSERT_OFFSET_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TIMESTAMP_INSERT_OFFSET_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TIMESTAMP_INSERT_OFFSET_dout_i;
sm_TIMESTAMP_INSERT_OFFSET_dout_i(32-1 downto 0) <= sm_TIMESTAMP_INSERT_OFFSET_dout;
-- 'TIMESTAMP_SET_LSB'
sm_TIMESTAMP_SET_LSB_din     <= sm_TIMESTAMP_SET_LSB_din_i(32-1 downto 0);
sm_TIMESTAMP_SET_LSB_en      <= sm_TIMESTAMP_SET_LSB_en_i;
gen_sm_TIMESTAMP_SET_LSB_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TIMESTAMP_SET_LSB_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TIMESTAMP_SET_LSB_dout_i;
sm_TIMESTAMP_SET_LSB_dout_i(32-1 downto 0) <= sm_TIMESTAMP_SET_LSB_dout;
-- 'TIMESTAMP_SET_MSB'
sm_TIMESTAMP_SET_MSB_din     <= sm_TIMESTAMP_SET_MSB_din_i(32-1 downto 0);
sm_TIMESTAMP_SET_MSB_en      <= sm_TIMESTAMP_SET_MSB_en_i;
gen_sm_TIMESTAMP_SET_MSB_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TIMESTAMP_SET_MSB_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TIMESTAMP_SET_MSB_dout_i;
sm_TIMESTAMP_SET_MSB_dout_i(32-1 downto 0) <= sm_TIMESTAMP_SET_MSB_dout;
-- 'CALIB_TIMES'
sm_CALIB_TIMES_din     <= sm_CALIB_TIMES_din_i(32-1 downto 0);
sm_CALIB_TIMES_en      <= sm_CALIB_TIMES_en_i;
gen_sm_CALIB_TIMES_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_CALIB_TIMES_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_CALIB_TIMES_dout_i;
sm_CALIB_TIMES_dout_i(32-1 downto 0) <= sm_CALIB_TIMES_dout;
-- 'IFS_INTERVALS2'
sm_IFS_INTERVALS2_din     <= sm_IFS_INTERVALS2_din_i(32-1 downto 0);
sm_IFS_INTERVALS2_en      <= sm_IFS_INTERVALS2_en_i;
gen_sm_IFS_INTERVALS2_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_IFS_INTERVALS2_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_IFS_INTERVALS2_dout_i;
sm_IFS_INTERVALS2_dout_i(32-1 downto 0) <= sm_IFS_INTERVALS2_dout;
-- 'IFS_INTERVALS1'
sm_IFS_INTERVALS1_din     <= sm_IFS_INTERVALS1_din_i(32-1 downto 0);
sm_IFS_INTERVALS1_en      <= sm_IFS_INTERVALS1_en_i;
gen_sm_IFS_INTERVALS1_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_IFS_INTERVALS1_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_IFS_INTERVALS1_dout_i;
sm_IFS_INTERVALS1_dout_i(32-1 downto 0) <= sm_IFS_INTERVALS1_dout;
-- 'TX_START'
sm_TX_START_din     <= sm_TX_START_din_i(32-1 downto 0);
sm_TX_START_en      <= sm_TX_START_en_i;
gen_sm_TX_START_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_TX_START_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_TX_START_dout_i;
sm_TX_START_dout_i(32-1 downto 0) <= sm_TX_START_dout;
-- 'Control'
sm_Control_din     <= sm_Control_din_i(32-1 downto 0);
sm_Control_en      <= sm_Control_en_i;
gen_sm_Control_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_Control_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_Control_dout_i;
sm_Control_dout_i(32-1 downto 0) <= sm_Control_dout;
-- 'NAV_MATCH_ADDR_1'
sm_NAV_MATCH_ADDR_1_din     <= sm_NAV_MATCH_ADDR_1_din_i(32-1 downto 0);
sm_NAV_MATCH_ADDR_1_en      <= sm_NAV_MATCH_ADDR_1_en_i;
gen_sm_NAV_MATCH_ADDR_1_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_NAV_MATCH_ADDR_1_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_NAV_MATCH_ADDR_1_dout_i;
sm_NAV_MATCH_ADDR_1_dout_i(32-1 downto 0) <= sm_NAV_MATCH_ADDR_1_dout;
-- 'NAV_MATCH_ADDR_2'
sm_NAV_MATCH_ADDR_2_din     <= sm_NAV_MATCH_ADDR_2_din_i(32-1 downto 0);
sm_NAV_MATCH_ADDR_2_en      <= sm_NAV_MATCH_ADDR_2_en_i;
gen_sm_NAV_MATCH_ADDR_2_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_NAV_MATCH_ADDR_2_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_NAV_MATCH_ADDR_2_dout_i;
sm_NAV_MATCH_ADDR_2_dout_i(32-1 downto 0) <= sm_NAV_MATCH_ADDR_2_dout;
-- 'BACKOFF_CTRL'
sm_BACKOFF_CTRL_din     <= sm_BACKOFF_CTRL_din_i(32-1 downto 0);
sm_BACKOFF_CTRL_en      <= sm_BACKOFF_CTRL_en_i;
gen_sm_BACKOFF_CTRL_dout_i: if (32 < C_S_AXI_DATA_WIDTH) generate
    sm_BACKOFF_CTRL_dout_i(C_S_AXI_DATA_WIDTH-1 downto 32) <= (others => '0');
end generate gen_sm_BACKOFF_CTRL_dout_i;
sm_BACKOFF_CTRL_dout_i(32-1 downto 0) <= sm_BACKOFF_CTRL_dout;
-- 'From FIFO'
-- 'To FIFO'
-- 'Shared Memory'

ReadWriteSelect: process(memmap_state) is begin
    if (memmap_state = READ) then
    else
    end if;
end process ReadWriteSelect;

-----------------------------------------------------------------------------
-- address for 'Shared Memory'
-----------------------------------------------------------------------------
SharedMemory_Addr_ResetN : process(AXI_AClk) is begin
    if (AXI_AClk'event and AXI_AClk = '1') then
        if (AXI_AResetN = '0') then
            memmap_state <= READ;
        else
            if (S_AXI_AWVALID = '1') then
                -- write operation
                memmap_state <= WRITE;
            elsif (S_AXI_ARVALID = '1') then
                -- read operation
                memmap_state <= READ;
            end if;
        end if;
    end if;
end process SharedMemory_Addr_ResetN;

-----------------------------------------------------------------------------
-- WRITE Command Control
-----------------------------------------------------------------------------
S_AXI_BID     <= S_AXI_BID_i;
S_AXI_BVALID  <= S_AXI_BVALID_i;
S_AXI_WREADY  <= S_AXI_WREADY_i;
-- No error checking
S_AXI_BRESP  <= (others=>'0');

PROC_AWREADY_ACK: process(read_state, write_state, S_AXI_ARVALID, S_AXI_AWVALID) is begin
    if (write_state = IDLE and S_AXI_AWVALID = '1' and read_state = IDLE) then
        S_AXI_AWREADY <= S_AXI_AWVALID;
    else
        S_AXI_AWREADY <= '0';
    end if;
end process PROC_AWREADY_ACK;

Cmd_Decode_Write: process(AXI_AClk) is begin
    if (AXI_AClk'event and AXI_AClk = '1') then
        if (AXI_AResetN = '0') then
            write_addr_valid    <= '0';
            write_ready         <= '0';
            s_fifo_we           <= '0';
            S_AXI_BVALID_i      <= '0';
            S_AXI_BID_i         <= (others => '0');
            write_bank_addr_i   <= (others => '0');
            write_linear_addr_i <= (others => '0');
        else
            if (write_state = IDLE) then
                if (S_AXI_AWVALID = '1' and read_state = IDLE) then
                    -- reflect awid
                    S_AXI_BID_i <= S_AXI_AWID;

                    -- latch bank and linear addresses
                    write_bank_addr_i   <= S_AXI_AWADDR(C_S_AXI_TOTAL_ADDR_LEN-1 downto C_S_AXI_LINEAR_ADDR_LEN+2);
                    write_linear_addr_i <= S_AXI_AWADDR(C_S_AXI_LINEAR_ADDR_LEN+1 downto 2);
                    write_addr_valid <= '1';
                    s_fifo_we <= '1';

                    -- write state transition
                    write_state <= WRITE_DATA;
                end if;
            elsif (write_state = WRITE_DATA) then
                write_ready <= '1';
                s_fifo_we <= '0';
                write_addr_valid <= S_AXI_WVALID;
                
                if (S_AXI_WVALID = '1' and write_ready = '1') then
                    write_linear_addr_i <= Std_Logic_Vector(unsigned(write_linear_addr_i) + 1);
                end if;

                if (S_AXI_WLAST = '1' and write_ready = '1') then
                    -- start responding through B channel upon the last write data sample
                    S_AXI_BVALID_i <= '1';
                    -- write data is over
                    write_addr_valid <= '0';
                    write_ready <= '0';
                    -- write state transition
                    write_state <= WRITE_RESPONSE;
                end if;
            elsif (write_state = WRITE_RESPONSE) then

                if (S_AXI_BREADY = '1') then
                    -- write respond is over
                    S_AXI_BVALID_i <= '0';
                    S_AXI_BID_i <= (others => '0');

                    -- write state transition
                    write_state <= IDLE;
                end if;
            end if;
        end if;
    end if;
end process Cmd_Decode_Write;

Write_Linear_Addr_Decode : process(AXI_AClk) is 

begin
    if (AXI_AClk'event and AXI_AClk = '1') then
        if (AXI_AResetN = '0') then
            -- 'To Register'
            -- TX_CTRL_B_PARAMS din/en
            sm_TX_CTRL_B_PARAMS_din_i <= (others => '0');
            sm_TX_CTRL_B_PARAMS_en_i <= '0';
            -- TX_CTRL_A_GAINS din/en
            sm_TX_CTRL_A_GAINS_din_i <= (others => '0');
            sm_TX_CTRL_A_GAINS_en_i <= '0';
            -- TX_CTRL_A_PARAMS din/en
            sm_TX_CTRL_A_PARAMS_din_i <= (others => '0');
            sm_TX_CTRL_A_PARAMS_en_i <= '0';
            -- POST_RX_TIMERS din/en
            sm_POST_RX_TIMERS_din_i <= (others => '0');
            sm_POST_RX_TIMERS_en_i <= '0';
            -- TX_CTRL_B_GAINS din/en
            sm_TX_CTRL_B_GAINS_din_i <= (others => '0');
            sm_TX_CTRL_B_GAINS_en_i <= '0';
            -- POST_TX_TIMERS din/en
            sm_POST_TX_TIMERS_din_i <= (others => '0');
            sm_POST_TX_TIMERS_en_i <= '0';
            -- TIMESTAMP_INSERT_OFFSET din/en
            sm_TIMESTAMP_INSERT_OFFSET_din_i <= (others => '0');
            sm_TIMESTAMP_INSERT_OFFSET_en_i <= '0';
            -- TIMESTAMP_SET_LSB din/en
            sm_TIMESTAMP_SET_LSB_din_i <= (others => '0');
            sm_TIMESTAMP_SET_LSB_en_i <= '0';
            -- TIMESTAMP_SET_MSB din/en
            sm_TIMESTAMP_SET_MSB_din_i <= (others => '0');
            sm_TIMESTAMP_SET_MSB_en_i <= '0';
            -- CALIB_TIMES din/en
            sm_CALIB_TIMES_din_i <= (others => '0');
            sm_CALIB_TIMES_en_i <= '0';
            -- IFS_INTERVALS2 din/en
            sm_IFS_INTERVALS2_din_i <= (others => '0');
            sm_IFS_INTERVALS2_en_i <= '0';
            -- IFS_INTERVALS1 din/en
            sm_IFS_INTERVALS1_din_i <= (others => '0');
            sm_IFS_INTERVALS1_en_i <= '0';
            -- TX_START din/en
            sm_TX_START_din_i <= (others => '0');
            sm_TX_START_en_i <= '0';
            -- Control din/en
            sm_Control_din_i <= (others => '0');
            sm_Control_en_i <= '0';
            -- NAV_MATCH_ADDR_1 din/en
            sm_NAV_MATCH_ADDR_1_din_i <= (others => '0');
            sm_NAV_MATCH_ADDR_1_en_i <= '0';
            -- NAV_MATCH_ADDR_2 din/en
            sm_NAV_MATCH_ADDR_2_din_i <= (others => '0');
            sm_NAV_MATCH_ADDR_2_en_i <= '0';
            -- BACKOFF_CTRL din/en
            sm_BACKOFF_CTRL_din_i <= (others => '0');
            sm_BACKOFF_CTRL_en_i <= '0';
            -- 'To FIFO'
            -- 'Shared Memory'
        else
            -- default assignments

            -- 'To Register'
            if (unsigned(write_bank_addr_i) = 2) then
                if (unsigned(write_linear_addr_i) = 0) then
                    -- TX_CTRL_B_PARAMS din/en
                    sm_TX_CTRL_B_PARAMS_din_i <= S_AXI_WDATA;
                    sm_TX_CTRL_B_PARAMS_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 1) then
                    -- TX_CTRL_A_GAINS din/en
                    sm_TX_CTRL_A_GAINS_din_i <= S_AXI_WDATA;
                    sm_TX_CTRL_A_GAINS_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 2) then
                    -- TX_CTRL_A_PARAMS din/en
                    sm_TX_CTRL_A_PARAMS_din_i <= S_AXI_WDATA;
                    sm_TX_CTRL_A_PARAMS_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 3) then
                    -- POST_RX_TIMERS din/en
                    sm_POST_RX_TIMERS_din_i <= S_AXI_WDATA;
                    sm_POST_RX_TIMERS_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 4) then
                    -- TX_CTRL_B_GAINS din/en
                    sm_TX_CTRL_B_GAINS_din_i <= S_AXI_WDATA;
                    sm_TX_CTRL_B_GAINS_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 5) then
                    -- POST_TX_TIMERS din/en
                    sm_POST_TX_TIMERS_din_i <= S_AXI_WDATA;
                    sm_POST_TX_TIMERS_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 6) then
                    -- TIMESTAMP_INSERT_OFFSET din/en
                    sm_TIMESTAMP_INSERT_OFFSET_din_i <= S_AXI_WDATA;
                    sm_TIMESTAMP_INSERT_OFFSET_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 7) then
                    -- TIMESTAMP_SET_LSB din/en
                    sm_TIMESTAMP_SET_LSB_din_i <= S_AXI_WDATA;
                    sm_TIMESTAMP_SET_LSB_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 8) then
                    -- TIMESTAMP_SET_MSB din/en
                    sm_TIMESTAMP_SET_MSB_din_i <= S_AXI_WDATA;
                    sm_TIMESTAMP_SET_MSB_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 9) then
                    -- CALIB_TIMES din/en
                    sm_CALIB_TIMES_din_i <= S_AXI_WDATA;
                    sm_CALIB_TIMES_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 10) then
                    -- IFS_INTERVALS2 din/en
                    sm_IFS_INTERVALS2_din_i <= S_AXI_WDATA;
                    sm_IFS_INTERVALS2_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 11) then
                    -- IFS_INTERVALS1 din/en
                    sm_IFS_INTERVALS1_din_i <= S_AXI_WDATA;
                    sm_IFS_INTERVALS1_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 12) then
                    -- TX_START din/en
                    sm_TX_START_din_i <= S_AXI_WDATA;
                    sm_TX_START_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 13) then
                    -- Control din/en
                    sm_Control_din_i <= S_AXI_WDATA;
                    sm_Control_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 14) then
                    -- NAV_MATCH_ADDR_1 din/en
                    sm_NAV_MATCH_ADDR_1_din_i <= S_AXI_WDATA;
                    sm_NAV_MATCH_ADDR_1_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 15) then
                    -- NAV_MATCH_ADDR_2 din/en
                    sm_NAV_MATCH_ADDR_2_din_i <= S_AXI_WDATA;
                    sm_NAV_MATCH_ADDR_2_en_i  <= write_addr_valid;
                elsif (unsigned(write_linear_addr_i) = 16) then
                    -- BACKOFF_CTRL din/en
                    sm_BACKOFF_CTRL_din_i <= S_AXI_WDATA;
                    sm_BACKOFF_CTRL_en_i  <= write_addr_valid;
                end if;
            end if;        
        
        
        end if;
    end if;
end process Write_Linear_Addr_Decode;
 
-----------------------------------------------------------------------------
-- READ Control
-----------------------------------------------------------------------------

S_AXI_RDATA  <= S_AXI_RDATA_i;
S_AXI_RVALID  <= S_AXI_RVALID_i;
S_AXI_RLAST   <= S_AXI_RLAST_i;
S_AXI_RID     <= S_AXI_RID_i;
-- TODO: no error checking
S_AXI_RRESP <= (others=>'0');

PROC_ARREADY_ACK: process(read_state, S_AXI_ARVALID, write_state, S_AXI_AWVALID) is begin
    -- Note: WRITE has higher priority than READ
    if (read_state = IDLE and S_AXI_ARVALID = '1' and write_state = IDLE and S_AXI_AWVALID /= '1') then
        S_AXI_ARREADY <= S_AXI_ARVALID;
    else
        S_AXI_ARREADY <= '0';
    end if;
end process PROC_ARREADY_ACK;

S_AXI_WREADY_i <= write_ready;

Process_Sideband: process(write_state, read_state) is begin
    if (read_state = READ_PREP) then
        s_shram_en <= '1';
    elsif (read_state = READ_DATA) then
        s_shram_en <= S_AXI_RREADY;
    elsif (write_state = WRITE_DATA) then
        s_shram_en <= S_AXI_WVALID;
    else
        s_shram_en <= '0';
    end if;
end process Process_Sideband;

Cmd_Decode_Read: process(AXI_AClk) is begin
    if (AXI_AClk'event and AXI_AClk = '1') then
        if (AXI_AResetN = '0') then
            S_AXI_RVALID_i <= '0';
            read_bank_addr_i    <= (others => '0');
            read_linear_addr_i  <= (others => '0');
            S_AXI_ARLEN_i       <= (others => '0');
            S_AXI_RLAST_i       <= '0';
            S_AXI_RID_i         <= (others => '0');
            read_state          <= IDLE;
            read_prep_counter   <= (others => '0');
            read_addr_counter   <= (others => '0');
            read_data_counter   <= (others => '0');
        else
            -- default assignments
            s_fifo_re <= '0';

            if (read_state = IDLE) then
                -- Note WRITE has higher priority than READ
                if (S_AXI_ARVALID = '1' and write_state = IDLE and S_AXI_AWVALID /= '1') then
                    -- extract bank and linear addresses
                    read_bank_addr_i    <= S_AXI_ARADDR(C_S_AXI_TOTAL_ADDR_LEN-1 downto C_S_AXI_LINEAR_ADDR_LEN+2);
                    read_linear_addr_i  <= S_AXI_ARADDR(C_S_AXI_LINEAR_ADDR_LEN+1 downto 2);
                    s_fifo_re <= '1';

                    -- reflect arid
                    S_AXI_RID_i <= S_AXI_ARID;

                    -- load read liner address and data counter
                    read_addr_counter <= S_AXI_ARLEN;
                    read_data_counter <= S_AXI_ARLEN;

                    -- load read preparation counter
                    read_prep_counter <= C_READ_PREP_DELAY;
                    -- read state transition
                    read_state <= READ_PREP;
                end if;
            elsif (read_state = READ_PREP) then
                if (unsigned(read_prep_counter) = 0) then
                    if (unsigned(read_data_counter) = 0) then
                        -- tag the last data generated by the slave
                        S_AXI_RLAST_i <= '1';
                    end if;
                    -- valid data appears
                    S_AXI_RVALID_i <= '1';
                    -- read state transition
                    read_state <= READ_DATA;
                else
                    -- decrease read preparation counter
                    read_prep_counter <= Std_Logic_Vector(unsigned(read_prep_counter) - 1);
                end if;

                if (unsigned(read_prep_counter) /= 3 and unsigned(read_addr_counter) /= 0) then
                    -- decrease address counter
                    read_addr_counter <= Std_Logic_Vector(unsigned(read_addr_counter) - 1);
                    -- increase linear address (no band crossing)
                    read_linear_addr_i <= Std_Logic_Vector(unsigned(read_linear_addr_i) + 1);
                end if;
            elsif (read_state = READ_DATA) then
                if (S_AXI_RREADY = '1') then
                    if (unsigned(read_data_counter) = 1) then
                        -- tag the last data generated by the slave
                        S_AXI_RLAST_i <= '1';
                    end if;

                    if (unsigned(read_data_counter) = 0) then
                        -- arid
                        S_AXI_RID_i <= (others => '0');
                        -- rlast
                        S_AXI_RLAST_i <= '0';
                        -- no more valid data
                        S_AXI_RVALID_i <= '0';
                        -- read state transition
                        read_state <= IDLE;
                    else
                        -- decrease read preparation counter
                        read_data_counter <= Std_Logic_Vector(unsigned(read_data_counter) - 1);

                        if (unsigned(read_addr_counter) /= 0) then
                            -- decrease address counter
                            read_addr_counter <= Std_Logic_Vector(unsigned(read_addr_counter) - 1);
                            -- increase linear address (no band crossing)
                            read_linear_addr_i <= Std_Logic_Vector(unsigned(read_linear_addr_i) + 1);
                        end if;
                    end if;
                end if;
            end if;

        end if;
    end if;
end process Cmd_Decode_Read;

Read_Linear_Addr_Decode : process(AXI_AClk) is begin
    if (AXI_AClk'event and AXI_AClk = '1') then
        if (AXI_AResetN = '0') then
            reg_bank_out_i   <= (others => '0');
            fifo_bank_out_i  <= (others => '0');
            shmem_bank_out_i <= (others => '0');
            S_AXI_RDATA_i    <= (others => '0');
        else
            if (unsigned(read_bank_addr_i) = 2) then
                -- 'From Register'
                if (unsigned(read_linear_addr_i) = 17) then
                    -- 'NAV_VALUE' dout
                    reg_bank_out_i <= sm_NAV_VALUE_dout_i;
                elsif (unsigned(read_linear_addr_i) = 18) then
                    -- 'BACKOFF_COUNTER' dout
                    reg_bank_out_i <= sm_BACKOFF_COUNTER_dout_i;
                elsif (unsigned(read_linear_addr_i) = 19) then
                    -- 'PHY_RX_PARAMS' dout
                    reg_bank_out_i <= sm_PHY_RX_PARAMS_dout_i;
                elsif (unsigned(read_linear_addr_i) = 20) then
                    -- 'LATEST_RX_BYTE' dout
                    reg_bank_out_i <= sm_LATEST_RX_BYTE_dout_i;
                elsif (unsigned(read_linear_addr_i) = 21) then
                    -- 'TX_START_TIMESTAMP_MSB' dout
                    reg_bank_out_i <= sm_TX_START_TIMESTAMP_MSB_dout_i;
                elsif (unsigned(read_linear_addr_i) = 22) then
                    -- 'TX_START_TIMESTAMP_LSB' dout
                    reg_bank_out_i <= sm_TX_START_TIMESTAMP_LSB_dout_i;
                elsif (unsigned(read_linear_addr_i) = 23) then
                    -- 'RX_START_TIMESTAMP_MSB' dout
                    reg_bank_out_i <= sm_RX_START_TIMESTAMP_MSB_dout_i;
                elsif (unsigned(read_linear_addr_i) = 24) then
                    -- 'RX_START_TIMESTAMP_LSB' dout
                    reg_bank_out_i <= sm_RX_START_TIMESTAMP_LSB_dout_i;
                elsif (unsigned(read_linear_addr_i) = 25) then
                    -- 'TIMESTAMP_MSB' dout
                    reg_bank_out_i <= sm_TIMESTAMP_MSB_dout_i;
                elsif (unsigned(read_linear_addr_i) = 26) then
                    -- 'TIMESTAMP_LSB' dout
                    reg_bank_out_i <= sm_TIMESTAMP_LSB_dout_i;
                elsif (unsigned(read_linear_addr_i) = 27) then
                    -- 'Status' dout
                    reg_bank_out_i <= sm_Status_dout_i;
                end if;
                -- 'To Register' (with register readback)
                if (unsigned(read_linear_addr_i) = 0) then
                    -- 'TX_CTRL_B_PARAMS' dout
                    reg_bank_out_i <= sm_TX_CTRL_B_PARAMS_dout_i;
                elsif (unsigned(read_linear_addr_i) = 1) then
                    -- 'TX_CTRL_A_GAINS' dout
                    reg_bank_out_i <= sm_TX_CTRL_A_GAINS_dout_i;
                elsif (unsigned(read_linear_addr_i) = 2) then
                    -- 'TX_CTRL_A_PARAMS' dout
                    reg_bank_out_i <= sm_TX_CTRL_A_PARAMS_dout_i;
                elsif (unsigned(read_linear_addr_i) = 3) then
                    -- 'POST_RX_TIMERS' dout
                    reg_bank_out_i <= sm_POST_RX_TIMERS_dout_i;
                elsif (unsigned(read_linear_addr_i) = 4) then
                    -- 'TX_CTRL_B_GAINS' dout
                    reg_bank_out_i <= sm_TX_CTRL_B_GAINS_dout_i;
                elsif (unsigned(read_linear_addr_i) = 5) then
                    -- 'POST_TX_TIMERS' dout
                    reg_bank_out_i <= sm_POST_TX_TIMERS_dout_i;
                elsif (unsigned(read_linear_addr_i) = 6) then
                    -- 'TIMESTAMP_INSERT_OFFSET' dout
                    reg_bank_out_i <= sm_TIMESTAMP_INSERT_OFFSET_dout_i;
                elsif (unsigned(read_linear_addr_i) = 7) then
                    -- 'TIMESTAMP_SET_LSB' dout
                    reg_bank_out_i <= sm_TIMESTAMP_SET_LSB_dout_i;
                elsif (unsigned(read_linear_addr_i) = 8) then
                    -- 'TIMESTAMP_SET_MSB' dout
                    reg_bank_out_i <= sm_TIMESTAMP_SET_MSB_dout_i;
                elsif (unsigned(read_linear_addr_i) = 9) then
                    -- 'CALIB_TIMES' dout
                    reg_bank_out_i <= sm_CALIB_TIMES_dout_i;
                elsif (unsigned(read_linear_addr_i) = 10) then
                    -- 'IFS_INTERVALS2' dout
                    reg_bank_out_i <= sm_IFS_INTERVALS2_dout_i;
                elsif (unsigned(read_linear_addr_i) = 11) then
                    -- 'IFS_INTERVALS1' dout
                    reg_bank_out_i <= sm_IFS_INTERVALS1_dout_i;
                elsif (unsigned(read_linear_addr_i) = 12) then
                    -- 'TX_START' dout
                    reg_bank_out_i <= sm_TX_START_dout_i;
                elsif (unsigned(read_linear_addr_i) = 13) then
                    -- 'Control' dout
                    reg_bank_out_i <= sm_Control_dout_i;
                elsif (unsigned(read_linear_addr_i) = 14) then
                    -- 'NAV_MATCH_ADDR_1' dout
                    reg_bank_out_i <= sm_NAV_MATCH_ADDR_1_dout_i;
                elsif (unsigned(read_linear_addr_i) = 15) then
                    -- 'NAV_MATCH_ADDR_2' dout
                    reg_bank_out_i <= sm_NAV_MATCH_ADDR_2_dout_i;
                elsif (unsigned(read_linear_addr_i) = 16) then
                    -- 'BACKOFF_CTRL' dout
                    reg_bank_out_i <= sm_BACKOFF_CTRL_dout_i;
                end if;

                S_AXI_RDATA_i <= reg_bank_out_i;
            elsif (unsigned(read_bank_addr_i) = 1) then
                -- 'From FIFO'
                -- 'To FIFO'

                S_AXI_RDATA_i <= fifo_bank_out_i;
            elsif (unsigned(read_bank_addr_i) = 0 and s_shram_en = '1') then
                -- 'Shared Memory'

                S_AXI_RDATA_i <= shmem_bank_out_i;
            end if;
        end if;
    end if;
end process Read_Linear_Addr_Decode;

end architecture IMP;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_3c8242143a is
  port (
    a : in std_logic_vector((4 - 1) downto 0);
    b : in std_logic_vector((1 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_3c8242143a;


architecture behavior of relational_3c8242143a is
  signal a_1_31: unsigned((4 - 1) downto 0);
  signal b_1_34: unsigned((1 - 1) downto 0);
  signal cast_14_17: unsigned((4 - 1) downto 0);
  signal result_14_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  cast_14_17 <= u2u_cast(b_1_34, 0, 4, 0);
  result_14_3_rel <= a_1_31 /= cast_14_17;
  op <= boolean_to_vector(result_14_3_rel);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity mux_3efa5ceb62 is
  port (
    sel : in std_logic_vector((1 - 1) downto 0);
    d0 : in std_logic_vector((14 - 1) downto 0);
    d1 : in std_logic_vector((20 - 1) downto 0);
    y : out std_logic_vector((20 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end mux_3efa5ceb62;


architecture behavior of mux_3efa5ceb62 is
  signal sel_1_20: std_logic;
  signal d0_1_24: std_logic_vector((14 - 1) downto 0);
  signal d1_1_27: std_logic_vector((20 - 1) downto 0);
  signal sel_internal_2_1_convert: std_logic_vector((1 - 1) downto 0);
  signal unregy_join_6_1: std_logic_vector((20 - 1) downto 0);
begin
  sel_1_20 <= sel(0);
  d0_1_24 <= d0;
  d1_1_27 <= d1;
  sel_internal_2_1_convert <= cast(std_logic_to_vector(sel_1_20), 0, 1, 0, xlUnsigned);
  proc_switch_6_1: process (d0_1_24, d1_1_27, sel_internal_2_1_convert)
  is
  begin
    case sel_internal_2_1_convert is 
      when "0" =>
        unregy_join_6_1 <= cast(d0_1_24, 0, 20, 0, xlUnsigned);
      when others =>
        unregy_join_6_1 <= d1_1_27;
    end case;
  end process proc_switch_6_1;
  y <= unregy_join_6_1;
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_6fce5fc0e4 is
  port (
    a : in std_logic_vector((16 - 1) downto 0);
    b : in std_logic_vector((20 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_6fce5fc0e4;


architecture behavior of relational_6fce5fc0e4 is
  signal a_1_31: unsigned((16 - 1) downto 0);
  signal b_1_34: unsigned((20 - 1) downto 0);
  signal cast_22_12: unsigned((20 - 1) downto 0);
  signal result_22_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  cast_22_12 <= u2u_cast(a_1_31, 0, 20, 0);
  result_22_3_rel <= cast_22_12 >= b_1_34;
  op <= boolean_to_vector(result_22_3_rel);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity concat_8e53793314 is
  port (
    in0 : in std_logic_vector((8 - 1) downto 0);
    in1 : in std_logic_vector((8 - 1) downto 0);
    y : out std_logic_vector((16 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end concat_8e53793314;


architecture behavior of concat_8e53793314 is
  signal in0_1_23: unsigned((8 - 1) downto 0);
  signal in1_1_27: unsigned((8 - 1) downto 0);
  signal y_2_1_concat: unsigned((16 - 1) downto 0);
begin
  in0_1_23 <= std_logic_vector_to_unsigned(in0);
  in1_1_27 <= std_logic_vector_to_unsigned(in1);
  y_2_1_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(in0_1_23) & unsigned_to_std_logic_vector(in1_1_27));
  y <= unsigned_to_std_logic_vector(y_2_1_concat);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity constant_e8ddc079e9 is
  port (
    op : out std_logic_vector((2 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end constant_e8ddc079e9;


architecture behavior of constant_e8ddc079e9 is
begin
  op <= "10";
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity constant_3a9a3daeb9 is
  port (
    op : out std_logic_vector((2 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end constant_3a9a3daeb9;


architecture behavior of constant_3a9a3daeb9 is
begin
  op <= "11";
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity constant_cda50df78a is
  port (
    op : out std_logic_vector((2 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end constant_cda50df78a;


architecture behavior of constant_cda50df78a is
begin
  op <= "00";
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity mux_03e37234da is
  port (
    sel : in std_logic_vector((1 - 1) downto 0);
    d0 : in std_logic_vector((16 - 1) downto 0);
    d1 : in std_logic_vector((2 - 1) downto 0);
    y : out std_logic_vector((16 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end mux_03e37234da;


architecture behavior of mux_03e37234da is
  signal sel_1_20: std_logic_vector((1 - 1) downto 0);
  signal d0_1_24: std_logic_vector((16 - 1) downto 0);
  signal d1_1_27: std_logic_vector((2 - 1) downto 0);
  signal unregy_join_6_1: std_logic_vector((16 - 1) downto 0);
begin
  sel_1_20 <= sel;
  d0_1_24 <= d0;
  d1_1_27 <= d1;
  proc_switch_6_1: process (d0_1_24, d1_1_27, sel_1_20)
  is
  begin
    case sel_1_20 is 
      when "0" =>
        unregy_join_6_1 <= d0_1_24;
      when others =>
        unregy_join_6_1 <= cast(d1_1_27, 0, 16, 0, xlUnsigned);
    end case;
  end process proc_switch_6_1;
  y <= unregy_join_6_1;
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_95b230a7ba is
  port (
    a : in std_logic_vector((16 - 1) downto 0);
    b : in std_logic_vector((2 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_95b230a7ba;


architecture behavior of relational_95b230a7ba is
  signal a_1_31: unsigned((16 - 1) downto 0);
  signal b_1_34: unsigned((2 - 1) downto 0);
  signal cast_12_17: unsigned((16 - 1) downto 0);
  signal result_12_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  cast_12_17 <= u2u_cast(b_1_34, 0, 16, 0);
  result_12_3_rel <= a_1_31 = cast_12_17;
  op <= boolean_to_vector(result_12_3_rel);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity concat_4a9a9a25a3 is
  port (
    in0 : in std_logic_vector((1 - 1) downto 0);
    in1 : in std_logic_vector((2 - 1) downto 0);
    y : out std_logic_vector((3 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end concat_4a9a9a25a3;


architecture behavior of concat_4a9a9a25a3 is
  signal in0_1_23: unsigned((1 - 1) downto 0);
  signal in1_1_27: unsigned((2 - 1) downto 0);
  signal y_2_1_concat: unsigned((3 - 1) downto 0);
begin
  in0_1_23 <= std_logic_vector_to_unsigned(in0);
  in1_1_27 <= std_logic_vector_to_unsigned(in1);
  y_2_1_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(in0_1_23) & unsigned_to_std_logic_vector(in1_1_27));
  y <= unsigned_to_std_logic_vector(y_2_1_concat);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity constant_0f59f02ba5 is
  port (
    op : out std_logic_vector((3 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end constant_0f59f02ba5;


architecture behavior of constant_0f59f02ba5 is
begin
  op <= "011";
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity constant_145086465d is
  port (
    op : out std_logic_vector((4 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end constant_145086465d;


architecture behavior of constant_145086465d is
begin
  op <= "1000";
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity mux_29b032b226 is
  port (
    sel : in std_logic_vector((3 - 1) downto 0);
    d0 : in std_logic_vector((8 - 1) downto 0);
    d1 : in std_logic_vector((8 - 1) downto 0);
    d2 : in std_logic_vector((8 - 1) downto 0);
    d3 : in std_logic_vector((8 - 1) downto 0);
    d4 : in std_logic_vector((8 - 1) downto 0);
    d5 : in std_logic_vector((8 - 1) downto 0);
    d6 : in std_logic_vector((1 - 1) downto 0);
    d7 : in std_logic_vector((1 - 1) downto 0);
    y : out std_logic_vector((8 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end mux_29b032b226;


architecture behavior of mux_29b032b226 is
  signal sel_1_20: std_logic_vector((3 - 1) downto 0);
  signal d0_1_24: std_logic_vector((8 - 1) downto 0);
  signal d1_1_27: std_logic_vector((8 - 1) downto 0);
  signal d2_1_30: std_logic_vector((8 - 1) downto 0);
  signal d3_1_33: std_logic_vector((8 - 1) downto 0);
  signal d4_1_36: std_logic_vector((8 - 1) downto 0);
  signal d5_1_39: std_logic_vector((8 - 1) downto 0);
  signal d6_1_42: std_logic_vector((1 - 1) downto 0);
  signal d7_1_45: std_logic_vector((1 - 1) downto 0);
  signal unregy_join_6_1: std_logic_vector((8 - 1) downto 0);
begin
  sel_1_20 <= sel;
  d0_1_24 <= d0;
  d1_1_27 <= d1;
  d2_1_30 <= d2;
  d3_1_33 <= d3;
  d4_1_36 <= d4;
  d5_1_39 <= d5;
  d6_1_42 <= d6;
  d7_1_45 <= d7;
  proc_switch_6_1: process (d0_1_24, d1_1_27, d2_1_30, d3_1_33, d4_1_36, d5_1_39, d6_1_42, d7_1_45, sel_1_20)
  is
  begin
    case sel_1_20 is 
      when "000" =>
        unregy_join_6_1 <= d0_1_24;
      when "001" =>
        unregy_join_6_1 <= d1_1_27;
      when "010" =>
        unregy_join_6_1 <= d2_1_30;
      when "011" =>
        unregy_join_6_1 <= d3_1_33;
      when "100" =>
        unregy_join_6_1 <= d4_1_36;
      when "101" =>
        unregy_join_6_1 <= d5_1_39;
      when "110" =>
        unregy_join_6_1 <= cast(d6_1_42, 0, 8, 0, xlUnsigned);
      when others =>
        unregy_join_6_1 <= cast(d7_1_45, 0, 8, 0, xlUnsigned);
    end case;
  end process proc_switch_6_1;
  y <= unregy_join_6_1;
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_3eccb4b5fa is
  port (
    a : in std_logic_vector((16 - 1) downto 0);
    b : in std_logic_vector((3 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_3eccb4b5fa;


architecture behavior of relational_3eccb4b5fa is
  signal a_1_31: unsigned((16 - 1) downto 0);
  signal b_1_34: unsigned((3 - 1) downto 0);
  signal cast_12_17: unsigned((16 - 1) downto 0);
  signal result_12_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  cast_12_17 <= u2u_cast(b_1_34, 0, 16, 0);
  result_12_3_rel <= a_1_31 = cast_12_17;
  op <= boolean_to_vector(result_12_3_rel);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_573d663832 is
  port (
    a : in std_logic_vector((16 - 1) downto 0);
    b : in std_logic_vector((4 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_573d663832;


architecture behavior of relational_573d663832 is
  signal a_1_31: unsigned((16 - 1) downto 0);
  signal b_1_34: unsigned((4 - 1) downto 0);
  signal cast_12_17: unsigned((16 - 1) downto 0);
  signal result_12_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  cast_12_17 <= u2u_cast(b_1_34, 0, 16, 0);
  result_12_3_rel <= a_1_31 = cast_12_17;
  op <= boolean_to_vector(result_12_3_rel);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity concat_22af082bf9 is
  port (
    in0 : in std_logic_vector((21 - 1) downto 0);
    in1 : in std_logic_vector((4 - 1) downto 0);
    y : out std_logic_vector((25 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end concat_22af082bf9;


architecture behavior of concat_22af082bf9 is
  signal in0_1_23: unsigned((21 - 1) downto 0);
  signal in1_1_27: unsigned((4 - 1) downto 0);
  signal y_2_1_concat: unsigned((25 - 1) downto 0);
begin
  in0_1_23 <= std_logic_vector_to_unsigned(in0);
  in1_1_27 <= std_logic_vector_to_unsigned(in1);
  y_2_1_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(in0_1_23) & unsigned_to_std_logic_vector(in1_1_27));
  y <= unsigned_to_std_logic_vector(y_2_1_concat);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity constant_4c449dd556 is
  port (
    op : out std_logic_vector((4 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end constant_4c449dd556;


architecture behavior of constant_4c449dd556 is
begin
  op <= "0000";
end behavior;


-------------------------------------------------------------------
-- System Generator version 14.3 VHDL source file.
--
-- Copyright(C) 2012 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2012 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
-- synopsys translate_off
library XilinxCoreLib;
-- synopsys translate_on
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use work.conv_pkg.all;
entity xladdsub_wlan_mac_hw is
  generic (
    core_name0: string := "";
    a_width: integer := 16;
    a_bin_pt: integer := 4;
    a_arith: integer := xlUnsigned;
    c_in_width: integer := 16;
    c_in_bin_pt: integer := 4;
    c_in_arith: integer := xlUnsigned;
    c_out_width: integer := 16;
    c_out_bin_pt: integer := 4;
    c_out_arith: integer := xlUnsigned;
    b_width: integer := 8;
    b_bin_pt: integer := 2;
    b_arith: integer := xlUnsigned;
    s_width: integer := 17;
    s_bin_pt: integer := 4;
    s_arith: integer := xlUnsigned;
    rst_width: integer := 1;
    rst_bin_pt: integer := 0;
    rst_arith: integer := xlUnsigned;
    en_width: integer := 1;
    en_bin_pt: integer := 0;
    en_arith: integer := xlUnsigned;
    full_s_width: integer := 17;
    full_s_arith: integer := xlUnsigned;
    mode: integer := xlAddMode;
    extra_registers: integer := 0;
    latency: integer := 0;
    quantization: integer := xlTruncate;
    overflow: integer := xlWrap;
    c_latency: integer := 0;
    c_output_width: integer := 17;
    c_has_c_in : integer := 0;
    c_has_c_out : integer := 0
  );
  port (
    a: in std_logic_vector(a_width - 1 downto 0);
    b: in std_logic_vector(b_width - 1 downto 0);
    c_in : in std_logic_vector (0 downto 0) := "0";
    ce: in std_logic;
    clr: in std_logic := '0';
    clk: in std_logic;
    rst: in std_logic_vector(rst_width - 1 downto 0) := "0";
    en: in std_logic_vector(en_width - 1 downto 0) := "1";
    c_out : out std_logic_vector (0 downto 0);
    s: out std_logic_vector(s_width - 1 downto 0)
  );
end xladdsub_wlan_mac_hw;
architecture behavior of xladdsub_wlan_mac_hw is
  component synth_reg
    generic (
      width: integer := 16;
      latency: integer := 5
    );
    port (
      i: in std_logic_vector(width - 1 downto 0);
      ce: in std_logic;
      clr: in std_logic;
      clk: in std_logic;
      o: out std_logic_vector(width - 1 downto 0)
    );
  end component;
  function format_input(inp: std_logic_vector; old_width, delta, new_arith,
                        new_width: integer)
    return std_logic_vector
  is
    variable vec: std_logic_vector(old_width-1 downto 0);
    variable padded_inp: std_logic_vector((old_width + delta)-1  downto 0);
    variable result: std_logic_vector(new_width-1 downto 0);
  begin
    vec := inp;
    if (delta > 0) then
      padded_inp := pad_LSB(vec, old_width+delta);
      result := extend_MSB(padded_inp, new_width, new_arith);
    else
      result := extend_MSB(vec, new_width, new_arith);
    end if;
    return result;
  end;
  constant full_s_bin_pt: integer := fractional_bits(a_bin_pt, b_bin_pt);
  constant full_a_width: integer := full_s_width;
  constant full_b_width: integer := full_s_width;
  signal full_a: std_logic_vector(full_a_width - 1 downto 0);
  signal full_b: std_logic_vector(full_b_width - 1 downto 0);
  signal core_s: std_logic_vector(full_s_width - 1 downto 0);
  signal conv_s: std_logic_vector(s_width - 1 downto 0);
  signal temp_cout : std_logic;
  signal internal_clr: std_logic;
  signal internal_ce: std_logic;
  signal extra_reg_ce: std_logic;
  signal override: std_logic;
  signal logic1: std_logic_vector(0 downto 0);
  component addsb_11_0_38dd91dde0ab1a97
    port (
          a: in std_logic_vector(22 - 1 downto 0);
    s: out std_logic_vector(c_output_width - 1 downto 0);
    b: in std_logic_vector(22 - 1 downto 0)
    );
  end component;
  component addsb_11_0_3c1d0ac9b6b8f403
    port (
          a: in std_logic_vector(66 - 1 downto 0);
    clk: in std_logic:= '0';
    ce: in std_logic:= '0';
    s: out std_logic_vector(c_output_width - 1 downto 0);
    b: in std_logic_vector(66 - 1 downto 0)
    );
  end component;
begin
  internal_clr <= (clr or (rst(0))) and ce;
  internal_ce <= ce and en(0);
  logic1(0) <= '1';
  addsub_process: process (a, b, core_s)
  begin
    full_a <= format_input (a, a_width, b_bin_pt - a_bin_pt, a_arith,
                            full_a_width);
    full_b <= format_input (b, b_width, a_bin_pt - b_bin_pt, b_arith,
                            full_b_width);
    conv_s <= convert_type (core_s, full_s_width, full_s_bin_pt, full_s_arith,
                            s_width, s_bin_pt, s_arith, quantization, overflow);
  end process addsub_process;

  comp0: if ((core_name0 = "addsb_11_0_38dd91dde0ab1a97")) generate
    core_instance0: addsb_11_0_38dd91dde0ab1a97
      port map (
         a => full_a,
         s => core_s,
         b => full_b
      );
  end generate;
  comp1: if ((core_name0 = "addsb_11_0_3c1d0ac9b6b8f403")) generate
    core_instance1: addsb_11_0_3c1d0ac9b6b8f403
      port map (
         a => full_a,
         clk => clk,
         ce => internal_ce,
         s => core_s,
         b => full_b
      );
  end generate;
  latency_test: if (extra_registers > 0) generate
      override_test: if (c_latency > 1) generate
       override_pipe: synth_reg
          generic map (
            width => 1,
            latency => c_latency
          )
          port map (
            i => logic1,
            ce => internal_ce,
            clr => internal_clr,
            clk => clk,
            o(0) => override);
       extra_reg_ce <= ce and en(0) and override;
      end generate override_test;
      no_override: if ((c_latency = 0) or (c_latency = 1)) generate
       extra_reg_ce <= ce and en(0);
      end generate no_override;
      extra_reg: synth_reg
        generic map (
          width => s_width,
          latency => extra_registers
        )
        port map (
          i => conv_s,
          ce => extra_reg_ce,
          clr => internal_clr,
          clk => clk,
          o => s
        );
      cout_test: if (c_has_c_out = 1) generate
      c_out_extra_reg: synth_reg
        generic map (
          width => 1,
          latency => extra_registers
        )
        port map (
          i(0) => temp_cout,
          ce => extra_reg_ce,
          clr => internal_clr,
          clk => clk,
          o => c_out
        );
      end generate cout_test;
  end generate;
  latency_s: if ((latency = 0) or (extra_registers = 0)) generate
    s <= conv_s;
  end generate latency_s;
  latency0: if (((latency = 0) or (extra_registers = 0)) and
                 (c_has_c_out = 1)) generate
    c_out(0) <= temp_cout;
  end generate latency0;
  tie_dangling_cout: if (c_has_c_out = 0) generate
    c_out <= "0";
  end generate tie_dangling_cout;
end architecture behavior;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity constant_5c1626e05e is
  port (
    op : out std_logic_vector((4 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end constant_5c1626e05e;


architecture behavior of constant_5c1626e05e is
begin
  op <= "1010";
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity logical_3640e86e6c is
  port (
    d0 : in std_logic_vector((1 - 1) downto 0);
    d1 : in std_logic_vector((1 - 1) downto 0);
    d2 : in std_logic_vector((1 - 1) downto 0);
    d3 : in std_logic_vector((1 - 1) downto 0);
    y : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end logical_3640e86e6c;


architecture behavior of logical_3640e86e6c is
  signal d0_1_24: std_logic;
  signal d1_1_27: std_logic;
  signal d2_1_30: std_logic;
  signal d3_1_33: std_logic;
  signal fully_2_1_bit: std_logic;
begin
  d0_1_24 <= d0(0);
  d1_1_27 <= d1(0);
  d2_1_30 <= d2(0);
  d3_1_33 <= d3(0);
  fully_2_1_bit <= d0_1_24 and d1_1_27 and d2_1_30 and d3_1_33;
  y <= std_logic_to_vector(fully_2_1_bit);
end behavior;


-------------------------------------------------------------------
-- System Generator version 14.3 VHDL source file.
--
-- Copyright(C) 2012 by Xilinx, Inc.  All rights reserved.  This
-- text/file contains proprietary, confidential information of Xilinx,
-- Inc., is distributed under license from Xilinx, Inc., and may be used,
-- copied and/or disclosed only pursuant to the terms of a valid license
-- agreement with Xilinx, Inc.  Xilinx hereby grants you a license to use
-- this text/file solely for design, simulation, implementation and
-- creation of design files limited to Xilinx devices or technologies.
-- Use with non-Xilinx devices or technologies is expressly prohibited
-- and immediately terminates your license unless covered by a separate
-- agreement.
--
-- Xilinx is providing this design, code, or information "as is" solely
-- for use in developing programs and solutions for Xilinx devices.  By
-- providing this design, code, or information as one possible
-- implementation of this feature, application or standard, Xilinx is
-- making no representation that this implementation is free from any
-- claims of infringement.  You are responsible for obtaining any rights
-- you may require for your implementation.  Xilinx expressly disclaims
-- any warranty whatsoever with respect to the adequacy of the
-- implementation, including but not limited to warranties of
-- merchantability or fitness for a particular purpose.
--
-- Xilinx products are not intended for use in life support appliances,
-- devices, or systems.  Use in such applications is expressly prohibited.
--
-- Any modifications that are made to the source code are done at the user's
-- sole risk and will be unsupported.
--
-- This copyright and support notice must be retained as part of this
-- text at all times.  (c) Copyright 1995-2012 Xilinx, Inc.  All rights
-- reserved.
-------------------------------------------------------------------
-- synopsys translate_off
library XilinxCoreLib;
-- synopsys translate_on
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use work.conv_pkg.all;
entity xlmult_wlan_mac_hw is
  generic (
    core_name0: string := "";
    a_width: integer := 4;
    a_bin_pt: integer := 2;
    a_arith: integer := xlSigned;
    b_width: integer := 4;
    b_bin_pt: integer := 1;
    b_arith: integer := xlSigned;
    p_width: integer := 8;
    p_bin_pt: integer := 2;
    p_arith: integer := xlSigned;
    rst_width: integer := 1;
    rst_bin_pt: integer := 0;
    rst_arith: integer := xlUnsigned;
    en_width: integer := 1;
    en_bin_pt: integer := 0;
    en_arith: integer := xlUnsigned;
    quantization: integer := xlTruncate;
    overflow: integer := xlWrap;
    extra_registers: integer := 0;
    c_a_width: integer := 7;
    c_b_width: integer := 7;
    c_type: integer := 0;
    c_a_type: integer := 0;
    c_b_type: integer := 0;
    c_pipelined: integer := 1;
    c_baat: integer := 4;
    multsign: integer := xlSigned;
    c_output_width: integer := 16
  );
  port (
    a: in std_logic_vector(a_width - 1 downto 0);
    b: in std_logic_vector(b_width - 1 downto 0);
    ce: in std_logic;
    clr: in std_logic;
    clk: in std_logic;
    core_ce: in std_logic := '0';
    core_clr: in std_logic := '0';
    core_clk: in std_logic := '0';
    rst: in std_logic_vector(rst_width - 1 downto 0);
    en: in std_logic_vector(en_width - 1 downto 0);
    p: out std_logic_vector(p_width - 1 downto 0)
  );
end xlmult_wlan_mac_hw;
architecture behavior of xlmult_wlan_mac_hw is
  component synth_reg
    generic (
      width: integer := 16;
      latency: integer := 5
    );
    port (
      i: in std_logic_vector(width - 1 downto 0);
      ce: in std_logic;
      clr: in std_logic;
      clk: in std_logic;
      o: out std_logic_vector(width - 1 downto 0)
    );
  end component;
  component mult_11_2_7def12de86dcdc6a
    port (
      b: in std_logic_vector(c_b_width - 1 downto 0);
      p: out std_logic_vector(c_output_width - 1 downto 0);
      clk: in std_logic;
      ce: in std_logic;
      sclr: in std_logic;
      a: in std_logic_vector(c_a_width - 1 downto 0)
    );
  end component;

  attribute syn_black_box of mult_11_2_7def12de86dcdc6a:
    component is true;
  attribute fpga_dont_touch of mult_11_2_7def12de86dcdc6a:
    component is "true";
  attribute box_type of mult_11_2_7def12de86dcdc6a:
    component  is "black_box";
  signal tmp_a: std_logic_vector(c_a_width - 1 downto 0);
  signal conv_a: std_logic_vector(c_a_width - 1 downto 0);
  signal tmp_b: std_logic_vector(c_b_width - 1 downto 0);
  signal conv_b: std_logic_vector(c_b_width - 1 downto 0);
  signal tmp_p: std_logic_vector(c_output_width - 1 downto 0);
  signal conv_p: std_logic_vector(p_width - 1 downto 0);
  -- synopsys translate_off
  signal real_a, real_b, real_p: real;
  -- synopsys translate_on
  signal rfd: std_logic;
  signal rdy: std_logic;
  signal nd: std_logic;
  signal internal_ce: std_logic;
  signal internal_clr: std_logic;
  signal internal_core_ce: std_logic;
begin
-- synopsys translate_off
-- synopsys translate_on
  internal_ce <= ce and en(0);
  internal_core_ce <= core_ce and en(0);
  internal_clr <= (clr or rst(0)) and ce;
  nd <= internal_ce;
  input_process:  process (a,b)
  begin
    tmp_a <= zero_ext(a, c_a_width);
    tmp_b <= zero_ext(b, c_b_width);
  end process;
  output_process: process (tmp_p)
  begin
    conv_p <= convert_type(tmp_p, c_output_width, a_bin_pt+b_bin_pt, multsign,
                           p_width, p_bin_pt, p_arith, quantization, overflow);
  end process;
  comp0: if ((core_name0 = "mult_11_2_7def12de86dcdc6a")) generate
    core_instance0: mult_11_2_7def12de86dcdc6a
      port map (
        a => tmp_a,
        clk => clk,
        ce => internal_ce,
        sclr => internal_clr,
        p => tmp_p,
        b => tmp_b
      );
  end generate;
  latency_gt_0: if (extra_registers > 0) generate
    reg: synth_reg
      generic map (
        width => p_width,
        latency => extra_registers
      )
      port map (
        i => conv_p,
        ce => internal_ce,
        clr => internal_clr,
        clk => clk,
        o => p
      );
  end generate;
  latency_eq_0: if (extra_registers = 0) generate
    p <= conv_p;
  end generate;
end architecture behavior;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_ee03197e2c is
  port (
    a : in std_logic_vector((4 - 1) downto 0);
    b : in std_logic_vector((1 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_ee03197e2c;


architecture behavior of relational_ee03197e2c is
  signal a_1_31: unsigned((4 - 1) downto 0);
  signal b_1_34: unsigned((1 - 1) downto 0);
  signal cast_12_17: unsigned((4 - 1) downto 0);
  signal result_12_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  cast_12_17 <= u2u_cast(b_1_34, 0, 4, 0);
  result_12_3_rel <= a_1_31 = cast_12_17;
  op <= boolean_to_vector(result_12_3_rel);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_bebc7e34dc is
  port (
    a : in std_logic_vector((20 - 1) downto 0);
    b : in std_logic_vector((25 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_bebc7e34dc;


architecture behavior of relational_bebc7e34dc is
  signal a_1_31: unsigned((20 - 1) downto 0);
  signal b_1_34: unsigned((25 - 1) downto 0);
  signal cast_16_12: unsigned((25 - 1) downto 0);
  signal result_16_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  cast_16_12 <= u2u_cast(a_1_31, 0, 25, 0);
  result_16_3_rel <= cast_16_12 < b_1_34;
  op <= boolean_to_vector(result_16_3_rel);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_77a58970b2 is
  port (
    a : in std_logic_vector((20 - 1) downto 0);
    b : in std_logic_vector((1 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_77a58970b2;


architecture behavior of relational_77a58970b2 is
  signal a_1_31: unsigned((20 - 1) downto 0);
  signal b_1_34: unsigned((1 - 1) downto 0);
  signal cast_18_16: unsigned((20 - 1) downto 0);
  signal result_18_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  cast_18_16 <= u2u_cast(b_1_34, 0, 20, 0);
  result_18_3_rel <= a_1_31 > cast_18_16;
  op <= boolean_to_vector(result_18_3_rel);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity logical_954ee29728 is
  port (
    d0 : in std_logic_vector((1 - 1) downto 0);
    d1 : in std_logic_vector((1 - 1) downto 0);
    d2 : in std_logic_vector((1 - 1) downto 0);
    y : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end logical_954ee29728;


architecture behavior of logical_954ee29728 is
  signal d0_1_24: std_logic;
  signal d1_1_27: std_logic;
  signal d2_1_30: std_logic;
  signal fully_2_1_bit: std_logic;
begin
  d0_1_24 <= d0(0);
  d1_1_27 <= d1(0);
  d2_1_30 <= d2(0);
  fully_2_1_bit <= d0_1_24 and d1_1_27 and d2_1_30;
  y <= std_logic_to_vector(fully_2_1_bit);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity mux_f9c0f11a18 is
  port (
    sel : in std_logic_vector((1 - 1) downto 0);
    d0 : in std_logic_vector((4 - 1) downto 0);
    d1 : in std_logic_vector((4 - 1) downto 0);
    y : out std_logic_vector((4 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end mux_f9c0f11a18;


architecture behavior of mux_f9c0f11a18 is
  signal sel_1_20: std_logic;
  signal d0_1_24: std_logic_vector((4 - 1) downto 0);
  signal d1_1_27: std_logic_vector((4 - 1) downto 0);
  signal sel_internal_2_1_convert: std_logic_vector((1 - 1) downto 0);
  signal unregy_join_6_1: std_logic_vector((4 - 1) downto 0);
begin
  sel_1_20 <= sel(0);
  d0_1_24 <= d0;
  d1_1_27 <= d1;
  sel_internal_2_1_convert <= cast(std_logic_to_vector(sel_1_20), 0, 1, 0, xlUnsigned);
  proc_switch_6_1: process (d0_1_24, d1_1_27, sel_internal_2_1_convert)
  is
  begin
    case sel_internal_2_1_convert is 
      when "0" =>
        unregy_join_6_1 <= d0_1_24;
      when others =>
        unregy_join_6_1 <= d1_1_27;
    end case;
  end process proc_switch_6_1;
  y <= unregy_join_6_1;
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity mux_ac2c510b5b is
  port (
    sel : in std_logic_vector((1 - 1) downto 0);
    d0 : in std_logic_vector((6 - 1) downto 0);
    d1 : in std_logic_vector((6 - 1) downto 0);
    y : out std_logic_vector((6 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end mux_ac2c510b5b;


architecture behavior of mux_ac2c510b5b is
  signal sel_1_20: std_logic;
  signal d0_1_24: std_logic_vector((6 - 1) downto 0);
  signal d1_1_27: std_logic_vector((6 - 1) downto 0);
  signal sel_internal_2_1_convert: std_logic_vector((1 - 1) downto 0);
  signal unregy_join_6_1: std_logic_vector((6 - 1) downto 0);
begin
  sel_1_20 <= sel(0);
  d0_1_24 <= d0;
  d1_1_27 <= d1;
  sel_internal_2_1_convert <= cast(std_logic_to_vector(sel_1_20), 0, 1, 0, xlUnsigned);
  proc_switch_6_1: process (d0_1_24, d1_1_27, sel_internal_2_1_convert)
  is
  begin
    case sel_internal_2_1_convert is 
      when "0" =>
        unregy_join_6_1 <= d0_1_24;
      when others =>
        unregy_join_6_1 <= d1_1_27;
    end case;
  end process proc_switch_6_1;
  y <= unregy_join_6_1;
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity relational_f3394f23a6 is
  port (
    a : in std_logic_vector((19 - 1) downto 0);
    b : in std_logic_vector((19 - 1) downto 0);
    op : out std_logic_vector((1 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end relational_f3394f23a6;


architecture behavior of relational_f3394f23a6 is
  signal a_1_31: unsigned((19 - 1) downto 0);
  signal b_1_34: unsigned((19 - 1) downto 0);
  signal result_22_3_rel: boolean;
begin
  a_1_31 <= std_logic_vector_to_unsigned(a);
  b_1_34 <= std_logic_vector_to_unsigned(b);
  result_22_3_rel <= a_1_31 >= b_1_34;
  op <= boolean_to_vector(result_22_3_rel);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity concat_463b9166a5 is
  port (
    in0 : in std_logic_vector((1 - 1) downto 0);
    in1 : in std_logic_vector((1 - 1) downto 0);
    in2 : in std_logic_vector((1 - 1) downto 0);
    in3 : in std_logic_vector((1 - 1) downto 0);
    in4 : in std_logic_vector((1 - 1) downto 0);
    in5 : in std_logic_vector((1 - 1) downto 0);
    in6 : in std_logic_vector((1 - 1) downto 0);
    in7 : in std_logic_vector((1 - 1) downto 0);
    in8 : in std_logic_vector((1 - 1) downto 0);
    in9 : in std_logic_vector((1 - 1) downto 0);
    in10 : in std_logic_vector((1 - 1) downto 0);
    in11 : in std_logic_vector((1 - 1) downto 0);
    in12 : in std_logic_vector((3 - 1) downto 0);
    in13 : in std_logic_vector((2 - 1) downto 0);
    in14 : in std_logic_vector((1 - 1) downto 0);
    in15 : in std_logic_vector((1 - 1) downto 0);
    in16 : in std_logic_vector((3 - 1) downto 0);
    in17 : in std_logic_vector((2 - 1) downto 0);
    in18 : in std_logic_vector((1 - 1) downto 0);
    in19 : in std_logic_vector((1 - 1) downto 0);
    y : out std_logic_vector((26 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end concat_463b9166a5;


architecture behavior of concat_463b9166a5 is
  signal in0_1_23: boolean;
  signal in1_1_27: boolean;
  signal in2_1_31: boolean;
  signal in3_1_35: boolean;
  signal in4_1_39: boolean;
  signal in5_1_43: boolean;
  signal in6_1_47: boolean;
  signal in7_1_51: boolean;
  signal in8_1_55: boolean;
  signal in9_1_59: boolean;
  signal in10_1_63: boolean;
  signal in11_1_68: boolean;
  signal in12_1_73: unsigned((3 - 1) downto 0);
  signal in13_1_78: unsigned((2 - 1) downto 0);
  signal in14_1_83: boolean;
  signal in15_1_88: boolean;
  signal in16_1_93: unsigned((3 - 1) downto 0);
  signal in17_1_98: unsigned((2 - 1) downto 0);
  signal in18_1_103: boolean;
  signal in19_1_108: boolean;
  signal y_2_1_concat: unsigned((26 - 1) downto 0);
begin
  in0_1_23 <= ((in0) = "1");
  in1_1_27 <= ((in1) = "1");
  in2_1_31 <= ((in2) = "1");
  in3_1_35 <= ((in3) = "1");
  in4_1_39 <= ((in4) = "1");
  in5_1_43 <= ((in5) = "1");
  in6_1_47 <= ((in6) = "1");
  in7_1_51 <= ((in7) = "1");
  in8_1_55 <= ((in8) = "1");
  in9_1_59 <= ((in9) = "1");
  in10_1_63 <= ((in10) = "1");
  in11_1_68 <= ((in11) = "1");
  in12_1_73 <= std_logic_vector_to_unsigned(in12);
  in13_1_78 <= std_logic_vector_to_unsigned(in13);
  in14_1_83 <= ((in14) = "1");
  in15_1_88 <= ((in15) = "1");
  in16_1_93 <= std_logic_vector_to_unsigned(in16);
  in17_1_98 <= std_logic_vector_to_unsigned(in17);
  in18_1_103 <= ((in18) = "1");
  in19_1_108 <= ((in19) = "1");
  y_2_1_concat <= std_logic_vector_to_unsigned(boolean_to_vector(in0_1_23) & boolean_to_vector(in1_1_27) & boolean_to_vector(in2_1_31) & boolean_to_vector(in3_1_35) & boolean_to_vector(in4_1_39) & boolean_to_vector(in5_1_43) & boolean_to_vector(in6_1_47) & boolean_to_vector(in7_1_51) & boolean_to_vector(in8_1_55) & boolean_to_vector(in9_1_59) & boolean_to_vector(in10_1_63) & boolean_to_vector(in11_1_68) & unsigned_to_std_logic_vector(in12_1_73) & unsigned_to_std_logic_vector(in13_1_78) & boolean_to_vector(in14_1_83) & boolean_to_vector(in15_1_88) & unsigned_to_std_logic_vector(in16_1_93) & unsigned_to_std_logic_vector(in17_1_98) & boolean_to_vector(in18_1_103) & boolean_to_vector(in19_1_108));
  y <= unsigned_to_std_logic_vector(y_2_1_concat);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity concat_16fe2e7edf is
  port (
    in0 : in std_logic_vector((15 - 1) downto 0);
    in1 : in std_logic_vector((4 - 1) downto 0);
    y : out std_logic_vector((19 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end concat_16fe2e7edf;


architecture behavior of concat_16fe2e7edf is
  signal in0_1_23: unsigned((15 - 1) downto 0);
  signal in1_1_27: unsigned((4 - 1) downto 0);
  signal y_2_1_concat: unsigned((19 - 1) downto 0);
begin
  in0_1_23 <= std_logic_vector_to_unsigned(in0);
  in1_1_27 <= std_logic_vector_to_unsigned(in1);
  y_2_1_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(in0_1_23) & unsigned_to_std_logic_vector(in1_1_27));
  y <= unsigned_to_std_logic_vector(y_2_1_concat);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity concat_4a94c27437 is
  port (
    in0 : in std_logic_vector((10 - 1) downto 0);
    in1 : in std_logic_vector((4 - 1) downto 0);
    y : out std_logic_vector((14 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end concat_4a94c27437;


architecture behavior of concat_4a94c27437 is
  signal in0_1_23: unsigned((10 - 1) downto 0);
  signal in1_1_27: unsigned((4 - 1) downto 0);
  signal y_2_1_concat: unsigned((14 - 1) downto 0);
begin
  in0_1_23 <= std_logic_vector_to_unsigned(in0);
  in1_1_27 <= std_logic_vector_to_unsigned(in1);
  y_2_1_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(in0_1_23) & unsigned_to_std_logic_vector(in1_1_27));
  y <= unsigned_to_std_logic_vector(y_2_1_concat);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity concat_0a671b9443 is
  port (
    in0 : in std_logic_vector((16 - 1) downto 0);
    in1 : in std_logic_vector((4 - 1) downto 0);
    y : out std_logic_vector((20 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end concat_0a671b9443;


architecture behavior of concat_0a671b9443 is
  signal in0_1_23: unsigned((16 - 1) downto 0);
  signal in1_1_27: unsigned((4 - 1) downto 0);
  signal y_2_1_concat: unsigned((20 - 1) downto 0);
begin
  in0_1_23 <= std_logic_vector_to_unsigned(in0);
  in1_1_27 <= std_logic_vector_to_unsigned(in1);
  y_2_1_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(in0_1_23) & unsigned_to_std_logic_vector(in1_1_27));
  y <= unsigned_to_std_logic_vector(y_2_1_concat);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity reinterpret_4389dc89bf is
  port (
    input_port : in std_logic_vector((8 - 1) downto 0);
    output_port : out std_logic_vector((8 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end reinterpret_4389dc89bf;


architecture behavior of reinterpret_4389dc89bf is
  signal input_port_1_40: unsigned((8 - 1) downto 0);
  signal output_port_5_5_force: signed((8 - 1) downto 0);
begin
  input_port_1_40 <= std_logic_vector_to_unsigned(input_port);
  output_port_5_5_force <= unsigned_to_signed(input_port_1_40);
  output_port <= signed_to_std_logic_vector(output_port_5_5_force);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity concat_04a248b81b is
  port (
    in0 : in std_logic_vector((8 - 1) downto 0);
    in1 : in std_logic_vector((16 - 1) downto 0);
    y : out std_logic_vector((24 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end concat_04a248b81b;


architecture behavior of concat_04a248b81b is
  signal in0_1_23: unsigned((8 - 1) downto 0);
  signal in1_1_27: unsigned((16 - 1) downto 0);
  signal y_2_1_concat: unsigned((24 - 1) downto 0);
begin
  in0_1_23 <= std_logic_vector_to_unsigned(in0);
  in1_1_27 <= std_logic_vector_to_unsigned(in1);
  y_2_1_concat <= std_logic_vector_to_unsigned(unsigned_to_std_logic_vector(in0_1_23) & unsigned_to_std_logic_vector(in1_1_27));
  y <= unsigned_to_std_logic_vector(y_2_1_concat);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity concat_16621e8277 is
  port (
    in0 : in std_logic_vector((1 - 1) downto 0);
    in1 : in std_logic_vector((1 - 1) downto 0);
    in2 : in std_logic_vector((3 - 1) downto 0);
    in3 : in std_logic_vector((1 - 1) downto 0);
    in4 : in std_logic_vector((1 - 1) downto 0);
    in5 : in std_logic_vector((7 - 1) downto 0);
    in6 : in std_logic_vector((16 - 1) downto 0);
    y : out std_logic_vector((30 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end concat_16621e8277;


architecture behavior of concat_16621e8277 is
  signal in0_1_23: boolean;
  signal in1_1_27: boolean;
  signal in2_1_31: unsigned((3 - 1) downto 0);
  signal in3_1_35: boolean;
  signal in4_1_39: boolean;
  signal in5_1_43: unsigned((7 - 1) downto 0);
  signal in6_1_47: unsigned((16 - 1) downto 0);
  signal y_2_1_concat: unsigned((30 - 1) downto 0);
begin
  in0_1_23 <= ((in0) = "1");
  in1_1_27 <= ((in1) = "1");
  in2_1_31 <= std_logic_vector_to_unsigned(in2);
  in3_1_35 <= ((in3) = "1");
  in4_1_39 <= ((in4) = "1");
  in5_1_43 <= std_logic_vector_to_unsigned(in5);
  in6_1_47 <= std_logic_vector_to_unsigned(in6);
  y_2_1_concat <= std_logic_vector_to_unsigned(boolean_to_vector(in0_1_23) & boolean_to_vector(in1_1_27) & unsigned_to_std_logic_vector(in2_1_31) & boolean_to_vector(in3_1_35) & boolean_to_vector(in4_1_39) & unsigned_to_std_logic_vector(in5_1_43) & unsigned_to_std_logic_vector(in6_1_47));
  y <= unsigned_to_std_logic_vector(y_2_1_concat);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity mcode_block_9fcb5ce515 is
  port (
    pre_wait_postrxtimer1 : in std_logic_vector((1 - 1) downto 0);
    pre_wait_posttxtimer1 : in std_logic_vector((1 - 1) downto 0);
    post_wait_posttxtimer2 : in std_logic_vector((1 - 1) downto 0);
    reset : in std_logic_vector((1 - 1) downto 0);
    new_tx : in std_logic_vector((1 - 1) downto 0);
    postrxtimer1_done : in std_logic_vector((1 - 1) downto 0);
    posttxtimer1_done : in std_logic_vector((1 - 1) downto 0);
    posttxtimer2_done : in std_logic_vector((1 - 1) downto 0);
    backoff_done : in std_logic_vector((1 - 1) downto 0);
    idle_for_difs : in std_logic_vector((1 - 1) downto 0);
    phy_tx_done : in std_logic_vector((1 - 1) downto 0);
    phy_rx_start : in std_logic_vector((1 - 1) downto 0);
    backoff_start : out std_logic_vector((1 - 1) downto 0);
    phy_tx_start : out std_logic_vector((1 - 1) downto 0);
    tx_done : out std_logic_vector((1 - 1) downto 0);
    tx_result_out : out std_logic_vector((2 - 1) downto 0);
    fsm_state_out : out std_logic_vector((3 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end mcode_block_9fcb5ce515;


architecture behavior of mcode_block_9fcb5ce515 is
  signal pre_wait_postrxtimer1_3_9: boolean;
  signal pre_wait_posttxtimer1_4_9: boolean;
  signal post_wait_posttxtimer2_5_9: boolean;
  signal reset_6_9: boolean;
  signal new_tx_7_9: boolean;
  signal postrxtimer1_done_8_9: boolean;
  signal posttxtimer1_done_9_9: boolean;
  signal posttxtimer2_done_10_9: boolean;
  signal backoff_done_11_9: boolean;
  signal idle_for_difs_12_9: boolean;
  signal phy_tx_done_13_9: boolean;
  signal phy_rx_start_14_9: boolean;
  signal fsm_state_16_23_next: unsigned((3 - 1) downto 0);
  signal fsm_state_16_23: unsigned((3 - 1) downto 0) := "000";
  signal fsm_state_16_23_rst: std_logic;
  signal tx_result_17_23_next: unsigned((2 - 1) downto 0);
  signal tx_result_17_23: unsigned((2 - 1) downto 0) := "00";
  signal tx_result_17_23_rst: std_logic;
  signal bool_71_20: boolean;
  signal not_74_24: boolean;
  signal fsm_state_join_71_17: unsigned((3 - 1) downto 0);
  signal fsm_state_join_70_13: unsigned((3 - 1) downto 0);
  signal bool_99_18: boolean;
  signal bool_99_66: boolean;
  signal bool_99_18_x_000000: boolean;
  signal fsm_state_join_99_13: unsigned((3 - 1) downto 0);
  signal fsm_state_join_122_13: unsigned((3 - 1) downto 0);
  signal fsm_state_join_136_13: unsigned((3 - 1) downto 0);
  signal fsm_state_join_150_13: unsigned((3 - 1) downto 0);
  signal tx_result_join_164_13: unsigned((2 - 1) downto 0);
  signal fsm_state_join_164_13: unsigned((3 - 1) downto 0);
  signal phy_tx_start_join_61_5: unsigned((1 - 1) downto 0);
  signal tx_result_join_61_5: unsigned((2 - 1) downto 0);
  signal tx_done_join_61_5: unsigned((1 - 1) downto 0);
  signal backoff_start_join_61_5: unsigned((1 - 1) downto 0);
  signal fsm_state_join_61_5: unsigned((3 - 1) downto 0);
  signal phy_tx_start_join_53_1: unsigned((1 - 1) downto 0);
  signal tx_result_join_53_1: unsigned((2 - 1) downto 0);
  signal tx_result_join_53_1_rst: std_logic;
  signal tx_done_join_53_1: unsigned((1 - 1) downto 0);
  signal backoff_start_join_53_1: unsigned((1 - 1) downto 0);
  signal fsm_state_join_53_1: unsigned((3 - 1) downto 0);
  signal fsm_state_join_53_1_rst: std_logic;
begin
  pre_wait_postrxtimer1_3_9 <= ((pre_wait_postrxtimer1) = "1");
  pre_wait_posttxtimer1_4_9 <= ((pre_wait_posttxtimer1) = "1");
  post_wait_posttxtimer2_5_9 <= ((post_wait_posttxtimer2) = "1");
  reset_6_9 <= ((reset) = "1");
  new_tx_7_9 <= ((new_tx) = "1");
  postrxtimer1_done_8_9 <= ((postrxtimer1_done) = "1");
  posttxtimer1_done_9_9 <= ((posttxtimer1_done) = "1");
  posttxtimer2_done_10_9 <= ((posttxtimer2_done) = "1");
  backoff_done_11_9 <= ((backoff_done) = "1");
  idle_for_difs_12_9 <= ((idle_for_difs) = "1");
  phy_tx_done_13_9 <= ((phy_tx_done) = "1");
  phy_rx_start_14_9 <= ((phy_rx_start) = "1");
  proc_fsm_state_16_23: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (fsm_state_16_23_rst = '1')) then
        fsm_state_16_23 <= "000";
      elsif (ce = '1') then 
        fsm_state_16_23 <= fsm_state_16_23_next;
      end if;
    end if;
  end process proc_fsm_state_16_23;
  proc_tx_result_17_23: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (tx_result_17_23_rst = '1')) then
        tx_result_17_23 <= "00";
      elsif (ce = '1') then 
        tx_result_17_23 <= tx_result_17_23_next;
      end if;
    end if;
  end process proc_tx_result_17_23;
  bool_71_20 <= pre_wait_postrxtimer1_3_9 or pre_wait_posttxtimer1_4_9;
  not_74_24 <=  not backoff_done_11_9;
  proc_if_71_17: process (bool_71_20, idle_for_difs_12_9, not_74_24)
  is
  begin
    if bool_71_20 then
      fsm_state_join_71_17 <= std_logic_vector_to_unsigned("001");
    elsif not_74_24 then
      fsm_state_join_71_17 <= std_logic_vector_to_unsigned("011");
    elsif idle_for_difs_12_9 then
      fsm_state_join_71_17 <= std_logic_vector_to_unsigned("100");
    else 
      fsm_state_join_71_17 <= std_logic_vector_to_unsigned("010");
    end if;
  end process proc_if_71_17;
  proc_if_70_13: process (fsm_state_join_71_17, new_tx_7_9)
  is
  begin
    if new_tx_7_9 then
      fsm_state_join_70_13 <= fsm_state_join_71_17;
    else 
      fsm_state_join_70_13 <= std_logic_vector_to_unsigned("000");
    end if;
  end process proc_if_70_13;
  bool_99_18 <= pre_wait_postrxtimer1_3_9 and postrxtimer1_done_8_9;
  bool_99_66 <= pre_wait_posttxtimer1_4_9 and posttxtimer1_done_9_9;
  bool_99_18_x_000000 <= bool_99_18 or bool_99_66;
  proc_if_99_13: process (bool_99_18_x_000000)
  is
  begin
    if bool_99_18_x_000000 then
      fsm_state_join_99_13 <= std_logic_vector_to_unsigned("100");
    else 
      fsm_state_join_99_13 <= std_logic_vector_to_unsigned("001");
    end if;
  end process proc_if_99_13;
  proc_if_122_13: process (backoff_done_11_9)
  is
  begin
    if backoff_done_11_9 then
      fsm_state_join_122_13 <= std_logic_vector_to_unsigned("100");
    else 
      fsm_state_join_122_13 <= std_logic_vector_to_unsigned("011");
    end if;
  end process proc_if_122_13;
  proc_if_136_13: process (phy_tx_done_13_9)
  is
  begin
    if phy_tx_done_13_9 then
      fsm_state_join_136_13 <= std_logic_vector_to_unsigned("101");
    else 
      fsm_state_join_136_13 <= std_logic_vector_to_unsigned("100");
    end if;
  end process proc_if_136_13;
  proc_if_150_13: process (post_wait_posttxtimer2_5_9)
  is
  begin
    if post_wait_posttxtimer2_5_9 then
      fsm_state_join_150_13 <= std_logic_vector_to_unsigned("110");
    else 
      fsm_state_join_150_13 <= std_logic_vector_to_unsigned("111");
    end if;
  end process proc_if_150_13;
  proc_if_164_13: process (phy_rx_start_14_9, posttxtimer2_done_10_9)
  is
  begin
    if phy_rx_start_14_9 then
      tx_result_join_164_13 <= std_logic_vector_to_unsigned("10");
      fsm_state_join_164_13 <= std_logic_vector_to_unsigned("111");
    elsif posttxtimer2_done_10_9 then
      tx_result_join_164_13 <= std_logic_vector_to_unsigned("01");
      fsm_state_join_164_13 <= std_logic_vector_to_unsigned("111");
    else 
      tx_result_join_164_13 <= std_logic_vector_to_unsigned("00");
      fsm_state_join_164_13 <= std_logic_vector_to_unsigned("110");
    end if;
  end process proc_if_164_13;
  proc_switch_61_5: process (fsm_state_16_23, fsm_state_join_122_13, fsm_state_join_136_13, fsm_state_join_150_13, fsm_state_join_164_13, fsm_state_join_70_13, fsm_state_join_99_13, tx_result_17_23, tx_result_join_164_13)
  is
  begin
    case fsm_state_16_23 is 
      when "000" =>
        phy_tx_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        tx_result_join_61_5 <= std_logic_vector_to_unsigned("00");
        tx_done_join_61_5 <= std_logic_vector_to_unsigned("0");
        backoff_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_61_5 <= fsm_state_join_70_13;
      when "001" =>
        phy_tx_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        tx_result_join_61_5 <= std_logic_vector_to_unsigned("00");
        tx_done_join_61_5 <= std_logic_vector_to_unsigned("0");
        backoff_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_61_5 <= fsm_state_join_99_13;
      when "010" =>
        phy_tx_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        tx_result_join_61_5 <= std_logic_vector_to_unsigned("00");
        tx_done_join_61_5 <= std_logic_vector_to_unsigned("0");
        backoff_start_join_61_5 <= std_logic_vector_to_unsigned("1");
        fsm_state_join_61_5 <= std_logic_vector_to_unsigned("011");
      when "011" =>
        phy_tx_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        tx_result_join_61_5 <= std_logic_vector_to_unsigned("00");
        tx_done_join_61_5 <= std_logic_vector_to_unsigned("0");
        backoff_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_61_5 <= fsm_state_join_122_13;
      when "100" =>
        phy_tx_start_join_61_5 <= std_logic_vector_to_unsigned("1");
        tx_result_join_61_5 <= std_logic_vector_to_unsigned("00");
        tx_done_join_61_5 <= std_logic_vector_to_unsigned("0");
        backoff_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_61_5 <= fsm_state_join_136_13;
      when "101" =>
        phy_tx_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        tx_result_join_61_5 <= std_logic_vector_to_unsigned("00");
        tx_done_join_61_5 <= std_logic_vector_to_unsigned("0");
        backoff_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_61_5 <= fsm_state_join_150_13;
      when "110" =>
        phy_tx_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        tx_result_join_61_5 <= tx_result_join_164_13;
        tx_done_join_61_5 <= std_logic_vector_to_unsigned("0");
        backoff_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_61_5 <= fsm_state_join_164_13;
      when "111" =>
        phy_tx_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        tx_result_join_61_5 <= tx_result_17_23;
        tx_done_join_61_5 <= std_logic_vector_to_unsigned("1");
        backoff_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_61_5 <= std_logic_vector_to_unsigned("000");
      when others =>
        phy_tx_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        tx_result_join_61_5 <= std_logic_vector_to_unsigned("00");
        tx_done_join_61_5 <= std_logic_vector_to_unsigned("0");
        backoff_start_join_61_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_61_5 <= std_logic_vector_to_unsigned("000");
    end case;
  end process proc_switch_61_5;
  proc_if_53_1: process (backoff_start_join_61_5, fsm_state_join_61_5, phy_tx_start_join_61_5, reset_6_9, tx_done_join_61_5, tx_result_join_61_5)
  is
  begin
    if reset_6_9 then
      tx_result_join_53_1_rst <= '1';
    else 
      tx_result_join_53_1_rst <= '0';
    end if;
    tx_result_join_53_1 <= tx_result_join_61_5;
    if reset_6_9 then
      fsm_state_join_53_1_rst <= '1';
    else 
      fsm_state_join_53_1_rst <= '0';
    end if;
    fsm_state_join_53_1 <= fsm_state_join_61_5;
    if reset_6_9 then
      phy_tx_start_join_53_1 <= std_logic_vector_to_unsigned("0");
      tx_done_join_53_1 <= std_logic_vector_to_unsigned("0");
      backoff_start_join_53_1 <= std_logic_vector_to_unsigned("0");
    else 
      phy_tx_start_join_53_1 <= phy_tx_start_join_61_5;
      tx_done_join_53_1 <= tx_done_join_61_5;
      backoff_start_join_53_1 <= backoff_start_join_61_5;
    end if;
  end process proc_if_53_1;
  fsm_state_16_23_next <= fsm_state_join_61_5;
  fsm_state_16_23_rst <= fsm_state_join_53_1_rst;
  tx_result_17_23_next <= tx_result_join_61_5;
  tx_result_17_23_rst <= tx_result_join_53_1_rst;
  backoff_start <= unsigned_to_std_logic_vector(backoff_start_join_53_1);
  phy_tx_start <= unsigned_to_std_logic_vector(phy_tx_start_join_53_1);
  tx_done <= unsigned_to_std_logic_vector(tx_done_join_53_1);
  tx_result_out <= unsigned_to_std_logic_vector(tx_result_17_23);
  fsm_state_out <= unsigned_to_std_logic_vector(fsm_state_16_23);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use work.conv_pkg.all;

entity mcode_block_249e341dc6 is
  port (
    pre_wait_postrxtimer1 : in std_logic_vector((1 - 1) downto 0);
    pre_wait_postrxtimer2 : in std_logic_vector((1 - 1) downto 0);
    pre_wait_posttxtimer1 : in std_logic_vector((1 - 1) downto 0);
    req_zero_nav : in std_logic_vector((1 - 1) downto 0);
    reset : in std_logic_vector((1 - 1) downto 0);
    new_tx : in std_logic_vector((1 - 1) downto 0);
    nav_zero : in std_logic_vector((1 - 1) downto 0);
    postrxtimer1_done : in std_logic_vector((1 - 1) downto 0);
    postrxtimer2_done : in std_logic_vector((1 - 1) downto 0);
    posttxtimer1_done : in std_logic_vector((1 - 1) downto 0);
    phy_tx_done : in std_logic_vector((1 - 1) downto 0);
    phy_tx_start : out std_logic_vector((1 - 1) downto 0);
    tx_done : out std_logic_vector((1 - 1) downto 0);
    tx_result_out : out std_logic_vector((2 - 1) downto 0);
    fsm_state_out : out std_logic_vector((3 - 1) downto 0);
    clk : in std_logic;
    ce : in std_logic;
    clr : in std_logic);
end mcode_block_249e341dc6;


architecture behavior of mcode_block_249e341dc6 is
  signal pre_wait_postrxtimer1_3_9: boolean;
  signal pre_wait_postrxtimer2_4_9: boolean;
  signal pre_wait_posttxtimer1_5_9: boolean;
  signal req_zero_nav_6_9: boolean;
  signal reset_7_9: boolean;
  signal new_tx_8_9: boolean;
  signal nav_zero_9_9: boolean;
  signal postrxtimer1_done_10_9: boolean;
  signal postrxtimer2_done_11_9: boolean;
  signal posttxtimer1_done_12_9: boolean;
  signal phy_tx_done_13_9: boolean;
  signal fsm_state_15_23_next: unsigned((3 - 1) downto 0);
  signal fsm_state_15_23: unsigned((3 - 1) downto 0) := "000";
  signal fsm_state_15_23_rst: std_logic;
  signal tx_result_16_23_next: unsigned((2 - 1) downto 0);
  signal tx_result_16_23: unsigned((2 - 1) downto 0) := "00";
  signal tx_result_16_23_rst: std_logic;
  signal bool_74_20: boolean;
  signal fsm_state_join_74_17: unsigned((2 - 1) downto 0);
  signal fsm_state_join_73_13: unsigned((2 - 1) downto 0);
  signal bool_94_18: boolean;
  signal bool_95_18: boolean;
  signal bool_96_18: boolean;
  signal bool_94_18_x_000000: boolean;
  signal fsm_state_join_94_13: unsigned((2 - 1) downto 0);
  signal bool_106_18: boolean;
  signal not_106_47: boolean;
  signal bool_106_18_x_000000: boolean;
  signal tx_result_join_106_13: unsigned((2 - 1) downto 0);
  signal fsm_state_join_106_13: unsigned((3 - 1) downto 0);
  signal fsm_state_join_121_13: unsigned((3 - 1) downto 0);
  signal tx_result_join_65_5: unsigned((2 - 1) downto 0);
  signal tx_done_join_65_5: unsigned((1 - 1) downto 0);
  signal fsm_state_join_65_5: unsigned((3 - 1) downto 0);
  signal phy_tx_start_join_65_5: unsigned((1 - 1) downto 0);
  signal tx_result_join_58_1: unsigned((2 - 1) downto 0);
  signal tx_result_join_58_1_rst: std_logic;
  signal tx_done_join_58_1: unsigned((1 - 1) downto 0);
  signal fsm_state_join_58_1: unsigned((3 - 1) downto 0);
  signal fsm_state_join_58_1_rst: std_logic;
  signal phy_tx_start_join_58_1: unsigned((1 - 1) downto 0);
begin
  pre_wait_postrxtimer1_3_9 <= ((pre_wait_postrxtimer1) = "1");
  pre_wait_postrxtimer2_4_9 <= ((pre_wait_postrxtimer2) = "1");
  pre_wait_posttxtimer1_5_9 <= ((pre_wait_posttxtimer1) = "1");
  req_zero_nav_6_9 <= ((req_zero_nav) = "1");
  reset_7_9 <= ((reset) = "1");
  new_tx_8_9 <= ((new_tx) = "1");
  nav_zero_9_9 <= ((nav_zero) = "1");
  postrxtimer1_done_10_9 <= ((postrxtimer1_done) = "1");
  postrxtimer2_done_11_9 <= ((postrxtimer2_done) = "1");
  posttxtimer1_done_12_9 <= ((posttxtimer1_done) = "1");
  phy_tx_done_13_9 <= ((phy_tx_done) = "1");
  proc_fsm_state_15_23: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (fsm_state_15_23_rst = '1')) then
        fsm_state_15_23 <= "000";
      elsif (ce = '1') then 
        fsm_state_15_23 <= fsm_state_15_23_next;
      end if;
    end if;
  end process proc_fsm_state_15_23;
  proc_tx_result_16_23: process (clk)
  is
  begin
    if (clk'event and (clk = '1')) then
      if ((ce = '1') and (tx_result_16_23_rst = '1')) then
        tx_result_16_23 <= "00";
      elsif (ce = '1') then 
        tx_result_16_23 <= tx_result_16_23_next;
      end if;
    end if;
  end process proc_tx_result_16_23;
  bool_74_20 <= pre_wait_postrxtimer1_3_9 or pre_wait_postrxtimer2_4_9 or pre_wait_posttxtimer1_5_9;
  proc_if_74_17: process (bool_74_20)
  is
  begin
    if bool_74_20 then
      fsm_state_join_74_17 <= std_logic_vector_to_unsigned("01");
    else 
      fsm_state_join_74_17 <= std_logic_vector_to_unsigned("10");
    end if;
  end process proc_if_74_17;
  proc_if_73_13: process (fsm_state_join_74_17, new_tx_8_9)
  is
  begin
    if new_tx_8_9 then
      fsm_state_join_73_13 <= fsm_state_join_74_17;
    else 
      fsm_state_join_73_13 <= std_logic_vector_to_unsigned("00");
    end if;
  end process proc_if_73_13;
  bool_94_18 <= pre_wait_postrxtimer1_3_9 and postrxtimer1_done_10_9;
  bool_95_18 <= pre_wait_postrxtimer2_4_9 and postrxtimer2_done_11_9;
  bool_96_18 <= pre_wait_posttxtimer1_5_9 and posttxtimer1_done_12_9;
  bool_94_18_x_000000 <= bool_94_18 or bool_95_18 or bool_96_18;
  proc_if_94_13: process (bool_94_18_x_000000)
  is
  begin
    if bool_94_18_x_000000 then
      fsm_state_join_94_13 <= std_logic_vector_to_unsigned("10");
    else 
      fsm_state_join_94_13 <= std_logic_vector_to_unsigned("01");
    end if;
  end process proc_if_94_13;
  bool_106_18 <= req_zero_nav_6_9 and nav_zero_9_9;
  not_106_47 <=  not req_zero_nav_6_9;
  bool_106_18_x_000000 <= bool_106_18 or not_106_47;
  proc_if_106_13: process (bool_106_18_x_000000)
  is
  begin
    if bool_106_18_x_000000 then
      tx_result_join_106_13 <= std_logic_vector_to_unsigned("01");
      fsm_state_join_106_13 <= std_logic_vector_to_unsigned("011");
    else 
      tx_result_join_106_13 <= std_logic_vector_to_unsigned("10");
      fsm_state_join_106_13 <= std_logic_vector_to_unsigned("100");
    end if;
  end process proc_if_106_13;
  proc_if_121_13: process (phy_tx_done_13_9)
  is
  begin
    if phy_tx_done_13_9 then
      fsm_state_join_121_13 <= std_logic_vector_to_unsigned("100");
    else 
      fsm_state_join_121_13 <= std_logic_vector_to_unsigned("011");
    end if;
  end process proc_if_121_13;
  proc_switch_65_5: process (fsm_state_15_23, fsm_state_join_106_13, fsm_state_join_121_13, fsm_state_join_73_13, fsm_state_join_94_13, tx_result_16_23, tx_result_join_106_13)
  is
  begin
    case fsm_state_15_23 is 
      when "000" =>
        tx_result_join_65_5 <= std_logic_vector_to_unsigned("00");
        tx_done_join_65_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_65_5 <= u2u_cast(fsm_state_join_73_13, 0, 3, 0);
        phy_tx_start_join_65_5 <= std_logic_vector_to_unsigned("0");
      when "001" =>
        tx_result_join_65_5 <= std_logic_vector_to_unsigned("00");
        tx_done_join_65_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_65_5 <= u2u_cast(fsm_state_join_94_13, 0, 3, 0);
        phy_tx_start_join_65_5 <= std_logic_vector_to_unsigned("0");
      when "010" =>
        tx_result_join_65_5 <= tx_result_join_106_13;
        tx_done_join_65_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_65_5 <= fsm_state_join_106_13;
        phy_tx_start_join_65_5 <= std_logic_vector_to_unsigned("0");
      when "011" =>
        tx_result_join_65_5 <= tx_result_16_23;
        tx_done_join_65_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_65_5 <= fsm_state_join_121_13;
        phy_tx_start_join_65_5 <= std_logic_vector_to_unsigned("1");
      when "100" =>
        tx_result_join_65_5 <= tx_result_16_23;
        tx_done_join_65_5 <= std_logic_vector_to_unsigned("1");
        fsm_state_join_65_5 <= std_logic_vector_to_unsigned("000");
        phy_tx_start_join_65_5 <= std_logic_vector_to_unsigned("0");
      when others =>
        tx_result_join_65_5 <= std_logic_vector_to_unsigned("00");
        tx_done_join_65_5 <= std_logic_vector_to_unsigned("0");
        fsm_state_join_65_5 <= std_logic_vector_to_unsigned("000");
        phy_tx_start_join_65_5 <= std_logic_vector_to_unsigned("0");
    end case;
  end process proc_switch_65_5;
  proc_if_58_1: process (fsm_state_join_65_5, phy_tx_start_join_65_5, reset_7_9, tx_done_join_65_5, tx_result_join_65_5)
  is
  begin
    if reset_7_9 then
      tx_result_join_58_1_rst <= '1';
    else 
      tx_result_join_58_1_rst <= '0';
    end if;
    tx_result_join_58_1 <= tx_result_join_65_5;
    if reset_7_9 then
      fsm_state_join_58_1_rst <= '1';
    else 
      fsm_state_join_58_1_rst <= '0';
    end if;
    fsm_state_join_58_1 <= fsm_state_join_65_5;
    if reset_7_9 then
      tx_done_join_58_1 <= std_logic_vector_to_unsigned("0");
      phy_tx_start_join_58_1 <= std_logic_vector_to_unsigned("0");
    else 
      tx_done_join_58_1 <= tx_done_join_65_5;
      phy_tx_start_join_58_1 <= phy_tx_start_join_65_5;
    end if;
  end process proc_if_58_1;
  fsm_state_15_23_next <= fsm_state_join_65_5;
  fsm_state_15_23_rst <= fsm_state_join_58_1_rst;
  tx_result_16_23_next <= tx_result_join_65_5;
  tx_result_16_23_rst <= tx_result_join_58_1_rst;
  phy_tx_start <= unsigned_to_std_logic_vector(phy_tx_start_join_58_1);
  tx_done <= unsigned_to_std_logic_vector(tx_done_join_58_1);
  tx_result_out <= unsigned_to_std_logic_vector(tx_result_16_23);
  fsm_state_out <= unsigned_to_std_logic_vector(fsm_state_15_23);
end behavior;

library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/64-bit usec  Counter/Posedge2"

entity posedge2_entity_ec1bb5d558 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    d: in std_logic; 
    q: out std_logic
  );
end posedge2_entity_ec1bb5d558;

architecture structural of posedge2_entity_ec1bb5d558 is
  signal b_5_y_net: std_logic;
  signal ce_1_sg_x0: std_logic;
  signal clk_1_sg_x0: std_logic;
  signal delay_q_net: std_logic;
  signal inverter_op_net: std_logic;
  signal logical1_y_net_x0: std_logic;

begin
  ce_1_sg_x0 <= ce_1;
  clk_1_sg_x0 <= clk_1;
  b_5_y_net <= d;
  q <= logical1_y_net_x0;

  delay: entity work.xldelay
    generic map (
      latency => 1,
      reg_retiming => 0,
      reset => 0,
      width => 1
    )
    port map (
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      d(0) => b_5_y_net,
      en => '1',
      rst => '1',
      q(0) => delay_q_net
    );

  inverter: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x0,
      clk => clk_1_sg_x0,
      clr => '0',
      ip(0) => delay_q_net,
      op(0) => inverter_op_net
    );

  logical1: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => inverter_op_net,
      d1(0) => b_5_y_net,
      y(0) => logical1_y_net_x0
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/64-bit usec  Counter/usec Pulse"

entity usec_pulse_entity_9d1645808e is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    rst: in std_logic; 
    usec: out std_logic
  );
end usec_pulse_entity_9d1645808e;

architecture structural of usec_pulse_entity_9d1645808e is
  signal ce_1_sg_x1: std_logic;
  signal clk_1_sg_x1: std_logic;
  signal clk_usec_op_net: std_logic_vector(7 downto 0);
  signal constant1_op_net: std_logic_vector(7 downto 0);
  signal logical1_y_net_x1: std_logic;
  signal logical_y_net: std_logic;
  signal relational_op_net_x0: std_logic;

begin
  ce_1_sg_x1 <= ce_1;
  clk_1_sg_x1 <= clk_1;
  logical1_y_net_x1 <= rst;
  usec <= relational_op_net_x0;

  clk_usec: entity work.xlcounter_free_wlan_mac_hw
    generic map (
      core_name0 => "cntr_11_0_86806e294f737f4c",
      op_arith => xlUnsigned,
      op_width => 8
    )
    port map (
      ce => ce_1_sg_x1,
      clk => clk_1_sg_x1,
      clr => '0',
      en => "1",
      rst(0) => logical_y_net,
      op => clk_usec_op_net
    );

  constant1: entity work.constant_5f4d695836
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op => constant1_op_net
    );

  logical: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational_op_net_x0,
      d1(0) => logical1_y_net_x1,
      y(0) => logical_y_net
    );

  relational: entity work.relational_54048c8b02
    port map (
      a => clk_usec_op_net,
      b => constant1_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational_op_net_x0
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/64-bit usec  Counter"

entity \x64_bit_usec__counter_entity_ceed0591a1\ is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    reg_set_timestamp_lsb: in std_logic_vector(31 downto 0); 
    reg_set_timestamp_msb: in std_logic_vector(31 downto 0); 
    reg_update_timestamp: in std_logic; 
    microsecond_timestamp: out std_logic_vector(63 downto 0); 
    register3_x0: out std_logic_vector(31 downto 0); 
    register_x1: out std_logic_vector(31 downto 0)
  );
end \x64_bit_usec__counter_entity_ceed0591a1\;

architecture structural of \x64_bit_usec__counter_entity_ceed0591a1\ is
  signal b_5_y_net_x0: std_logic;
  signal ce_1_sg_x2: std_logic;
  signal clk_1_sg_x2: std_logic;
  signal concat_y_net: std_logic_vector(63 downto 0);
  signal logical1_y_net_x1: std_logic;
  signal logical_y_net: std_logic;
  signal microsecond_counter_op_net_x0: std_logic_vector(63 downto 0);
  signal register1_q_net: std_logic_vector(31 downto 0);
  signal register27_q_net_x0: std_logic_vector(31 downto 0);
  signal register28_q_net_x0: std_logic_vector(31 downto 0);
  signal register2_q_net: std_logic_vector(31 downto 0);
  signal register3_q_net_x0: std_logic_vector(31 downto 0);
  signal register_q_net_x0: std_logic_vector(31 downto 0);
  signal relational_op_net_x0: std_logic;
  signal x32lsb_y_net: std_logic_vector(31 downto 0);
  signal x32msb_y_net: std_logic_vector(31 downto 0);

begin
  ce_1_sg_x2 <= ce_1;
  clk_1_sg_x2 <= clk_1;
  register28_q_net_x0 <= reg_set_timestamp_lsb;
  register27_q_net_x0 <= reg_set_timestamp_msb;
  b_5_y_net_x0 <= reg_update_timestamp;
  microsecond_timestamp <= microsecond_counter_op_net_x0;
  register3_x0 <= register3_q_net_x0;
  register_x1 <= register_q_net_x0;

  concat: entity work.concat_62c4475a80
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      in0 => register27_q_net_x0,
      in1 => register28_q_net_x0,
      y => concat_y_net
    );

  logical: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x1,
      d1(0) => relational_op_net_x0,
      y(0) => logical_y_net
    );

  microsecond_counter: entity work.xlcounter_free_wlan_mac_hw
    generic map (
      core_name0 => "cntr_11_0_5e62871cb125c52e",
      op_arith => xlUnsigned,
      op_width => 64
    )
    port map (
      ce => ce_1_sg_x2,
      clk => clk_1_sg_x2,
      clr => '0',
      din => concat_y_net,
      en(0) => logical_y_net,
      load(0) => logical1_y_net_x1,
      rst => "0",
      op => microsecond_counter_op_net_x0
    );

  posedge2_ec1bb5d558: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x2,
      clk_1 => clk_1_sg_x2,
      d => b_5_y_net_x0,
      q => logical1_y_net_x1
    );

  register1: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x2,
      clk => clk_1_sg_x2,
      d => x32msb_y_net,
      en => "1",
      rst => "0",
      q => register1_q_net
    );

  register2: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x2,
      clk => clk_1_sg_x2,
      d => x32lsb_y_net,
      en => "1",
      rst => "0",
      q => register2_q_net
    );

  register3: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x2,
      clk => clk_1_sg_x2,
      d => register2_q_net,
      en => "1",
      rst => "0",
      q => register3_q_net_x0
    );

  register_x0: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x2,
      clk => clk_1_sg_x2,
      d => register1_q_net,
      en => "1",
      rst => "0",
      q => register_q_net_x0
    );

  usec_pulse_9d1645808e: entity work.usec_pulse_entity_9d1645808e
    port map (
      ce_1 => ce_1_sg_x2,
      clk_1 => clk_1_sg_x2,
      rst => logical1_y_net_x1,
      usec => relational_op_net_x0
    );

  x32lsb: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 31,
      x_width => 64,
      y_width => 32
    )
    port map (
      x => microsecond_counter_op_net_x0,
      y => x32lsb_y_net
    );

  x32msb: entity work.xlslice
    generic map (
      new_lsb => 32,
      new_msb => 63,
      x_width => 64,
      y_width => 32
    )
    port map (
      x => microsecond_counter_op_net_x0,
      y => x32msb_y_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Backoff/Ctrl/S-R Latch1"

entity s_r_latch1_entity_65359461e7 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    r: in std_logic; 
    s: in std_logic; 
    q: out std_logic
  );
end s_r_latch1_entity_65359461e7;

architecture structural of s_r_latch1_entity_65359461e7 is
  signal ce_1_sg_x6: std_logic;
  signal clk_1_sg_x6: std_logic;
  signal constant1_op_net: std_logic;
  signal logical1_y_net_x0: std_logic;
  signal logical4_y_net_x0: std_logic;
  signal register2_q_net_x0: std_logic;

begin
  ce_1_sg_x6 <= ce_1;
  clk_1_sg_x6 <= clk_1;
  logical1_y_net_x0 <= r;
  logical4_y_net_x0 <= s;
  q <= register2_q_net_x0;

  constant1: entity work.constant_6293007044
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant1_op_net
    );

  register2: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x6,
      clk => clk_1_sg_x6,
      d(0) => constant1_op_net,
      en(0) => logical4_y_net_x0,
      rst(0) => logical1_y_net_x0,
      q(0) => register2_q_net_x0
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Backoff/Ctrl"

entity ctrl_entity_f8d76dc5b7 is
  port (
    bo_start: in std_logic; 
    bo_zero: in std_logic; 
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    global_reset: in std_logic; 
    idle_for_difs: in std_logic; 
    num_slots: in std_logic_vector(15 downto 0); 
    bo_done: out std_logic; 
    bo_run: out std_logic; 
    num_slots_load: out std_logic
  );
end ctrl_entity_f8d76dc5b7;

architecture structural of ctrl_entity_f8d76dc5b7 is
  signal b_0_y_net: std_logic;
  signal ce_1_sg_x8: std_logic;
  signal clk_1_sg_x8: std_logic;
  signal constant_op_net: std_logic;
  signal delay_q_net_x1: std_logic;
  signal inverter_op_net: std_logic;
  signal logical1_y_net_x0: std_logic;
  signal logical1_y_net_x1: std_logic;
  signal logical1_y_net_x2: std_logic;
  signal logical1_y_net_x3: std_logic;
  signal logical2_y_net_x0: std_logic;
  signal logical3_y_net: std_logic;
  signal logical4_y_net_x0: std_logic;
  signal logical5_y_net_x0: std_logic;
  signal logical6_y_net_x1: std_logic;
  signal logical7_y_net_x0: std_logic;
  signal mux_y_net_x0: std_logic_vector(15 downto 0);
  signal register2_q_net_x1: std_logic;
  signal register2_q_net_x2: std_logic;
  signal relational1_op_net: std_logic;
  signal relational1_op_net_x2: std_logic;
  signal relational1_op_net_x3: std_logic;

begin
  logical6_y_net_x1 <= bo_start;
  relational1_op_net_x2 <= bo_zero;
  ce_1_sg_x8 <= ce_1;
  clk_1_sg_x8 <= clk_1;
  b_0_y_net <= global_reset;
  relational1_op_net_x3 <= idle_for_difs;
  mux_y_net_x0 <= num_slots;
  bo_done <= logical5_y_net_x0;
  bo_run <= register2_q_net_x2;
  num_slots_load <= delay_q_net_x1;

  constant_x0: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant_op_net
    );

  delay: entity work.xldelay
    generic map (
      latency => 1,
      reg_retiming => 0,
      reset => 0,
      width => 1
    )
    port map (
      ce => ce_1_sg_x8,
      clk => clk_1_sg_x8,
      d(0) => logical1_y_net_x2,
      en => '1',
      rst => '1',
      q(0) => delay_q_net_x1
    );

  inverter: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x8,
      clk => clk_1_sg_x8,
      clr => '0',
      ip(0) => delay_q_net_x1,
      op(0) => inverter_op_net
    );

  logical1: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x3,
      d1(0) => b_0_y_net,
      y(0) => logical1_y_net_x0
    );

  logical2: entity work.logical_6cb8f0ce02
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x3,
      d1(0) => logical3_y_net,
      d2(0) => b_0_y_net,
      y(0) => logical2_y_net_x0
    );

  logical3: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational1_op_net_x2,
      d1(0) => relational1_op_net_x3,
      y(0) => logical3_y_net
    );

  logical4: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational1_op_net,
      d1(0) => logical1_y_net_x2,
      y(0) => logical4_y_net_x0
    );

  logical5: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => inverter_op_net,
      d1(0) => register2_q_net_x1,
      y(0) => logical5_y_net_x0
    );

  logical7: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x1,
      d1(0) => relational1_op_net_x2,
      y(0) => logical7_y_net_x0
    );

  posedge1_77da20e6ab: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x8,
      clk_1 => clk_1_sg_x8,
      d => logical6_y_net_x1,
      q => logical1_y_net_x1
    );

  posedge2_93b52c7f4d: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x8,
      clk_1 => clk_1_sg_x8,
      d => logical7_y_net_x0,
      q => logical1_y_net_x2
    );

  posedge3_e14dc2f447: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x8,
      clk_1 => clk_1_sg_x8,
      d => relational1_op_net_x2,
      q => logical1_y_net_x3
    );

  relational1: entity work.relational_e528f2ec9d
    port map (
      a => mux_y_net_x0,
      b(0) => constant_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational1_op_net
    );

  s_r_latch1_65359461e7: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x8,
      clk_1 => clk_1_sg_x8,
      r => logical1_y_net_x0,
      s => logical4_y_net_x0,
      q => register2_q_net_x2
    );

  s_r_latch2_a65ae9b36c: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x8,
      clk_1 => clk_1_sg_x8,
      r => delay_q_net_x1,
      s => logical2_y_net_x0,
      q => register2_q_net_x1
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Backoff/Slot Time"

entity slot_time_entity_5b3e9d1cd5 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    en: in std_logic; 
    reg_interval_slot: in std_logic_vector(13 downto 0); 
    slot_done: out std_logic
  );
end slot_time_entity_5b3e9d1cd5;

architecture structural of slot_time_entity_5b3e9d1cd5 is
  signal ce_1_sg_x10: std_logic;
  signal clk_1_sg_x10: std_logic;
  signal concat1_y_net_x0: std_logic_vector(13 downto 0);
  signal inverter_op_net: std_logic;
  signal logical1_y_net: std_logic;
  signal logical1_y_net_x1: std_logic;
  signal logical4_y_net_x0: std_logic;
  signal relational2_op_net_x0: std_logic;
  signal slot_time_op_net: std_logic_vector(13 downto 0);

begin
  ce_1_sg_x10 <= ce_1;
  clk_1_sg_x10 <= clk_1;
  logical4_y_net_x0 <= en;
  concat1_y_net_x0 <= reg_interval_slot;
  slot_done <= logical1_y_net_x1;

  inverter: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x10,
      clk => clk_1_sg_x10,
      clr => '0',
      ip(0) => logical4_y_net_x0,
      op(0) => inverter_op_net
    );

  logical1: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational2_op_net_x0,
      d1(0) => inverter_op_net,
      y(0) => logical1_y_net
    );

  posedge2_231b7bcf9b: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x10,
      clk_1 => clk_1_sg_x10,
      d => relational2_op_net_x0,
      q => logical1_y_net_x1
    );

  relational2: entity work.relational_fe0d6a6e93
    port map (
      a => slot_time_op_net,
      b => concat1_y_net_x0,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational2_op_net_x0
    );

  slot_time: entity work.xlcounter_free_wlan_mac_hw
    generic map (
      core_name0 => "cntr_11_0_23bc6491dc8a06da",
      op_arith => xlUnsigned,
      op_width => 14
    )
    port map (
      ce => ce_1_sg_x10,
      clk => clk_1_sg_x10,
      clr => '0',
      en(0) => logical4_y_net_x0,
      rst(0) => logical1_y_net,
      op => slot_time_op_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Backoff"

entity backoff_entity_23f797b138 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    concat1: in std_logic_vector(13 downto 0); 
    global_reset: in std_logic; 
    idle_for_txdifs: in std_logic; 
    reg_backoff_sw_numslots: in std_logic_vector(15 downto 0); 
    reg_backoff_sw_start: in std_logic; 
    reg_force_reset_backoff: in std_logic; 
    tx_a_backoff_start: in std_logic; 
    tx_a_num_bo_slots: in std_logic_vector(15 downto 0); 
    backoff_done: out std_logic; 
    register1_x0: out std_logic; 
    status_current_backoff_count: out std_logic_vector(15 downto 0)
  );
end backoff_entity_23f797b138;

architecture structural of backoff_entity_23f797b138 is
  signal b_0_y_net_x0: std_logic;
  signal b_11_y_net: std_logic;
  signal ce_1_sg_x11: std_logic;
  signal clk_1_sg_x11: std_logic;
  signal concat1_y_net_x1: std_logic_vector(13 downto 0);
  signal constant_op_net: std_logic;
  signal convert_dout_net: std_logic_vector(15 downto 0);
  signal convert_dout_net_x1: std_logic;
  signal delay_q_net_x1: std_logic;
  signal inverter_op_net: std_logic;
  signal logical1_y_net: std_logic;
  signal logical1_y_net_x1: std_logic;
  signal logical2_y_net: std_logic;
  signal logical3_y_net: std_logic;
  signal logical4_y_net_x0: std_logic;
  signal logical5_y_net_x1: std_logic;
  signal logical6_y_net_x1: std_logic;
  signal mux_y_net_x0: std_logic_vector(15 downto 0);
  signal num_slots_op_net_x0: std_logic_vector(15 downto 0);
  signal register1_q_net_x0: std_logic;
  signal register20_q_net_x0: std_logic_vector(15 downto 0);
  signal register21_q_net_x0: std_logic;
  signal register2_q_net: std_logic_vector(15 downto 0);
  signal register2_q_net_x2: std_logic;
  signal register3_q_net_x0: std_logic_vector(15 downto 0);
  signal register_q_net: std_logic;
  signal relational1_op_net_x2: std_logic;
  signal relational1_op_net_x4: std_logic;

begin
  ce_1_sg_x11 <= ce_1;
  clk_1_sg_x11 <= clk_1;
  concat1_y_net_x1 <= concat1;
  b_0_y_net_x0 <= global_reset;
  relational1_op_net_x4 <= idle_for_txdifs;
  register20_q_net_x0 <= reg_backoff_sw_numslots;
  register21_q_net_x0 <= reg_backoff_sw_start;
  b_11_y_net <= reg_force_reset_backoff;
  convert_dout_net_x1 <= tx_a_backoff_start;
  register3_q_net_x0 <= tx_a_num_bo_slots;
  backoff_done <= logical5_y_net_x1;
  register1_x0 <= register1_q_net_x0;
  status_current_backoff_count <= num_slots_op_net_x0;

  constant_x0: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant_op_net
    );

  convert: entity work.xlconvert
    generic map (
      bool_conversion => 0,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 16,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 16,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x11,
      clk => clk_1_sg_x11,
      clr => '0',
      din => register2_q_net,
      en => "1",
      dout => convert_dout_net
    );

  ctrl_f8d76dc5b7: entity work.ctrl_entity_f8d76dc5b7
    port map (
      bo_start => logical6_y_net_x1,
      bo_zero => relational1_op_net_x2,
      ce_1 => ce_1_sg_x11,
      clk_1 => clk_1_sg_x11,
      global_reset => b_0_y_net_x0,
      idle_for_difs => relational1_op_net_x4,
      num_slots => mux_y_net_x0,
      bo_done => logical5_y_net_x1,
      bo_run => register2_q_net_x2,
      num_slots_load => delay_q_net_x1
    );

  inverter: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x11,
      clk => clk_1_sg_x11,
      clr => '0',
      ip(0) => relational1_op_net_x2,
      op(0) => inverter_op_net
    );

  logical1: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x1,
      d1(0) => inverter_op_net,
      y(0) => logical1_y_net
    );

  logical2: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => b_0_y_net_x0,
      d1(0) => b_11_y_net,
      y(0) => logical2_y_net
    );

  logical3: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => delay_q_net_x1,
      d1(0) => logical1_y_net,
      y(0) => logical3_y_net
    );

  logical4: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => register2_q_net_x2,
      d1(0) => relational1_op_net_x4,
      y(0) => logical4_y_net_x0
    );

  logical6: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => convert_dout_net_x1,
      d1(0) => register21_q_net_x0,
      y(0) => logical6_y_net_x1
    );

  mux: entity work.mux_a54904b290
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0 => register3_q_net_x0,
      d1 => register20_q_net_x0,
      sel(0) => register21_q_net_x0,
      y => mux_y_net_x0
    );

  num_slots: entity work.xlcounter_free_wlan_mac_hw
    generic map (
      core_name0 => "cntr_11_0_bc4e334678893d0e",
      op_arith => xlUnsigned,
      op_width => 16
    )
    port map (
      ce => ce_1_sg_x11,
      clk => clk_1_sg_x11,
      clr => '0',
      din => convert_dout_net,
      en(0) => logical3_y_net,
      load(0) => delay_q_net_x1,
      rst(0) => logical2_y_net,
      op => num_slots_op_net_x0
    );

  register1: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x11,
      clk => clk_1_sg_x11,
      d(0) => register_q_net,
      en => "1",
      rst => "0",
      q(0) => register1_q_net_x0
    );

  register2: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x11,
      clk => clk_1_sg_x11,
      d => mux_y_net_x0,
      en(0) => logical6_y_net_x1,
      rst => "0",
      q => register2_q_net
    );

  register_x0: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x11,
      clk => clk_1_sg_x11,
      d(0) => inverter_op_net,
      en => "1",
      rst => "0",
      q(0) => register_q_net
    );

  relational1: entity work.relational_53a2345101
    port map (
      a => num_slots_op_net_x0,
      b(0) => constant_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational1_op_net_x2
    );

  slot_time_5b3e9d1cd5: entity work.slot_time_entity_5b3e9d1cd5
    port map (
      ce_1 => ce_1_sg_x11,
      clk_1 => clk_1_sg_x11,
      en => logical4_y_net_x0,
      reg_interval_slot => concat1_y_net_x1,
      slot_done => logical1_y_net_x1
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/CCA"

entity cca_entity_95f741f726 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    mac_nav_busy: in std_logic; 
    phy_cca_ind_busy: in std_logic; 
    reg_cca_ignore_nav: in std_logic; 
    reg_cca_ignore_phy_cs: in std_logic; 
    reg_cca_ignore_txbusy: in std_logic; 
    status_tx_phy_active: in std_logic; 
    cs_busy: out std_logic; 
    cs_idle: out std_logic
  );
end cca_entity_95f741f726;

architecture structural of cca_entity_95f741f726 is
  signal b_7_y_net: std_logic;
  signal b_8_y_net: std_logic;
  signal b_9_y_net: std_logic;
  signal ce_1_sg_x12: std_logic;
  signal clk_1_sg_x12: std_logic;
  signal inverter1_op_net_x0: std_logic;
  signal inverter2_op_net: std_logic;
  signal inverter3_op_net: std_logic;
  signal inverter4_op_net: std_logic;
  signal logical1_y_net: std_logic;
  signal logical2_y_net: std_logic;
  signal logical3_y_net_x1: std_logic;
  signal logical3_y_net_x2: std_logic;
  signal logical4_y_net: std_logic;
  signal phy_cca_ind_busy_net_x0: std_logic;
  signal register2_q_net_x0: std_logic;

begin
  ce_1_sg_x12 <= ce_1;
  clk_1_sg_x12 <= clk_1;
  logical3_y_net_x1 <= mac_nav_busy;
  phy_cca_ind_busy_net_x0 <= phy_cca_ind_busy;
  b_9_y_net <= reg_cca_ignore_nav;
  b_7_y_net <= reg_cca_ignore_phy_cs;
  b_8_y_net <= reg_cca_ignore_txbusy;
  register2_q_net_x0 <= status_tx_phy_active;
  cs_busy <= logical3_y_net_x2;
  cs_idle <= inverter1_op_net_x0;

  inverter1: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x12,
      clk => clk_1_sg_x12,
      clr => '0',
      ip(0) => logical3_y_net_x2,
      op(0) => inverter1_op_net_x0
    );

  inverter2: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x12,
      clk => clk_1_sg_x12,
      clr => '0',
      ip(0) => b_8_y_net,
      op(0) => inverter2_op_net
    );

  inverter3: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x12,
      clk => clk_1_sg_x12,
      clr => '0',
      ip(0) => b_7_y_net,
      op(0) => inverter3_op_net
    );

  inverter4: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x12,
      clk => clk_1_sg_x12,
      clr => '0',
      ip(0) => b_9_y_net,
      op(0) => inverter4_op_net
    );

  logical1: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical3_y_net_x1,
      d1(0) => inverter4_op_net,
      y(0) => logical1_y_net
    );

  logical2: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => phy_cca_ind_busy_net_x0,
      d1(0) => inverter3_op_net,
      y(0) => logical2_y_net
    );

  logical3: entity work.logical_6cb8f0ce02
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical4_y_net,
      d1(0) => logical2_y_net,
      d2(0) => logical1_y_net,
      y(0) => logical3_y_net_x2
    );

  logical4: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => register2_q_net_x0,
      d1(0) => inverter2_op_net,
      y(0) => logical4_y_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/EDK Processor"

entity edk_processor_entity_82b88caaa5 is
  port (
    axi_aresetn: in std_logic; 
    from_register: in std_logic_vector(31 downto 0); 
    from_register1: in std_logic_vector(31 downto 0); 
    from_register10: in std_logic_vector(31 downto 0); 
    from_register2: in std_logic_vector(31 downto 0); 
    from_register3: in std_logic_vector(31 downto 0); 
    from_register4: in std_logic_vector(31 downto 0); 
    from_register5: in std_logic_vector(31 downto 0); 
    from_register6: in std_logic_vector(31 downto 0); 
    from_register7: in std_logic_vector(31 downto 0); 
    from_register8: in std_logic_vector(31 downto 0); 
    from_register9: in std_logic_vector(31 downto 0); 
    plb_ce_1: in std_logic; 
    plb_clk_1: in std_logic; 
    s_axi_araddr: in std_logic_vector(31 downto 0); 
    s_axi_arburst: in std_logic_vector(1 downto 0); 
    s_axi_arcache: in std_logic_vector(3 downto 0); 
    s_axi_arid: in std_logic_vector(7 downto 0); 
    s_axi_arlen: in std_logic_vector(7 downto 0); 
    s_axi_arlock: in std_logic_vector(1 downto 0); 
    s_axi_arprot: in std_logic_vector(2 downto 0); 
    s_axi_arsize: in std_logic_vector(2 downto 0); 
    s_axi_arvalid: in std_logic; 
    s_axi_awaddr: in std_logic_vector(31 downto 0); 
    s_axi_awburst: in std_logic_vector(1 downto 0); 
    s_axi_awcache: in std_logic_vector(3 downto 0); 
    s_axi_awid: in std_logic_vector(7 downto 0); 
    s_axi_awlen: in std_logic_vector(7 downto 0); 
    s_axi_awlock: in std_logic_vector(1 downto 0); 
    s_axi_awprot: in std_logic_vector(2 downto 0); 
    s_axi_awsize: in std_logic_vector(2 downto 0); 
    s_axi_awvalid: in std_logic; 
    s_axi_bready: in std_logic; 
    s_axi_rready: in std_logic; 
    s_axi_wdata: in std_logic_vector(31 downto 0); 
    s_axi_wlast: in std_logic; 
    s_axi_wstrb: in std_logic_vector(3 downto 0); 
    s_axi_wvalid: in std_logic; 
    to_register: in std_logic_vector(31 downto 0); 
    to_register1: in std_logic_vector(31 downto 0); 
    to_register10: in std_logic_vector(31 downto 0); 
    to_register11: in std_logic_vector(31 downto 0); 
    to_register12: in std_logic_vector(31 downto 0); 
    to_register13: in std_logic_vector(31 downto 0); 
    to_register14: in std_logic_vector(31 downto 0); 
    to_register15: in std_logic_vector(31 downto 0); 
    to_register16: in std_logic_vector(31 downto 0); 
    to_register2: in std_logic_vector(31 downto 0); 
    to_register3: in std_logic_vector(31 downto 0); 
    to_register4: in std_logic_vector(31 downto 0); 
    to_register5: in std_logic_vector(31 downto 0); 
    to_register6: in std_logic_vector(31 downto 0); 
    to_register7: in std_logic_vector(31 downto 0); 
    to_register8: in std_logic_vector(31 downto 0); 
    to_register9: in std_logic_vector(31 downto 0); 
    memmap_x0: out std_logic; 
    memmap_x1: out std_logic; 
    memmap_x10: out std_logic; 
    memmap_x11: out std_logic_vector(31 downto 0); 
    memmap_x12: out std_logic; 
    memmap_x13: out std_logic_vector(31 downto 0); 
    memmap_x14: out std_logic; 
    memmap_x15: out std_logic_vector(31 downto 0); 
    memmap_x16: out std_logic; 
    memmap_x17: out std_logic_vector(31 downto 0); 
    memmap_x18: out std_logic; 
    memmap_x19: out std_logic_vector(31 downto 0); 
    memmap_x2: out std_logic_vector(7 downto 0); 
    memmap_x20: out std_logic; 
    memmap_x21: out std_logic_vector(31 downto 0); 
    memmap_x22: out std_logic; 
    memmap_x23: out std_logic_vector(31 downto 0); 
    memmap_x24: out std_logic; 
    memmap_x25: out std_logic_vector(31 downto 0); 
    memmap_x26: out std_logic; 
    memmap_x27: out std_logic_vector(31 downto 0); 
    memmap_x28: out std_logic; 
    memmap_x29: out std_logic_vector(31 downto 0); 
    memmap_x3: out std_logic_vector(1 downto 0); 
    memmap_x30: out std_logic; 
    memmap_x31: out std_logic_vector(31 downto 0); 
    memmap_x32: out std_logic; 
    memmap_x33: out std_logic_vector(31 downto 0); 
    memmap_x34: out std_logic; 
    memmap_x35: out std_logic_vector(31 downto 0); 
    memmap_x36: out std_logic; 
    memmap_x37: out std_logic_vector(31 downto 0); 
    memmap_x38: out std_logic; 
    memmap_x39: out std_logic_vector(31 downto 0); 
    memmap_x4: out std_logic; 
    memmap_x40: out std_logic; 
    memmap_x41: out std_logic_vector(31 downto 0); 
    memmap_x42: out std_logic; 
    memmap_x43: out std_logic_vector(31 downto 0); 
    memmap_x44: out std_logic; 
    memmap_x5: out std_logic_vector(31 downto 0); 
    memmap_x6: out std_logic_vector(7 downto 0); 
    memmap_x7: out std_logic; 
    memmap_x8: out std_logic_vector(1 downto 0); 
    memmap_x9: out std_logic
  );
end edk_processor_entity_82b88caaa5;

architecture structural of edk_processor_entity_82b88caaa5 is
  signal axi_aresetn_net_x0: std_logic;
  signal from_register10_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register1_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register2_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register3_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register4_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register5_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register6_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register7_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register8_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register9_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register_data_out_net_x0: std_logic_vector(31 downto 0);
  signal memmap_s_axi_arready_net_x0: std_logic;
  signal memmap_s_axi_awready_net_x0: std_logic;
  signal memmap_s_axi_bid_net_x0: std_logic_vector(7 downto 0);
  signal memmap_s_axi_bresp_net_x0: std_logic_vector(1 downto 0);
  signal memmap_s_axi_bvalid_net_x0: std_logic;
  signal memmap_s_axi_rdata_net_x0: std_logic_vector(31 downto 0);
  signal memmap_s_axi_rid_net_x0: std_logic_vector(7 downto 0);
  signal memmap_s_axi_rlast_net_x0: std_logic;
  signal memmap_s_axi_rresp_net_x0: std_logic_vector(1 downto 0);
  signal memmap_s_axi_rvalid_net_x0: std_logic;
  signal memmap_s_axi_wready_net_x0: std_logic;
  signal memmap_sm_backoff_ctrl_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_backoff_ctrl_en_net_x0: std_logic;
  signal memmap_sm_calib_times_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_calib_times_en_net_x0: std_logic;
  signal memmap_sm_control_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_control_en_net_x0: std_logic;
  signal memmap_sm_ifs_intervals1_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_ifs_intervals1_en_net_x0: std_logic;
  signal memmap_sm_ifs_intervals2_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_ifs_intervals2_en_net_x0: std_logic;
  signal memmap_sm_nav_match_addr_1_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_nav_match_addr_1_en_net_x0: std_logic;
  signal memmap_sm_nav_match_addr_2_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_nav_match_addr_2_en_net_x0: std_logic;
  signal memmap_sm_post_rx_timers_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_post_rx_timers_en_net_x0: std_logic;
  signal memmap_sm_post_tx_timers_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_post_tx_timers_en_net_x0: std_logic;
  signal memmap_sm_timestamp_insert_offset_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_timestamp_insert_offset_en_net_x0: std_logic;
  signal memmap_sm_timestamp_set_lsb_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_timestamp_set_lsb_en_net_x0: std_logic;
  signal memmap_sm_timestamp_set_msb_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_timestamp_set_msb_en_net_x0: std_logic;
  signal memmap_sm_tx_ctrl_a_gains_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_tx_ctrl_a_gains_en_net_x0: std_logic;
  signal memmap_sm_tx_ctrl_a_params_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_tx_ctrl_a_params_en_net_x0: std_logic;
  signal memmap_sm_tx_ctrl_b_gains_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_tx_ctrl_b_gains_en_net_x0: std_logic;
  signal memmap_sm_tx_ctrl_b_params_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_tx_ctrl_b_params_en_net_x0: std_logic;
  signal memmap_sm_tx_start_din_net_x0: std_logic_vector(31 downto 0);
  signal memmap_sm_tx_start_en_net_x0: std_logic;
  signal plb_ce_1_sg_x0: std_logic;
  signal plb_clk_1_sg_x0: std_logic;
  signal s_axi_araddr_net_x0: std_logic_vector(31 downto 0);
  signal s_axi_arburst_net_x0: std_logic_vector(1 downto 0);
  signal s_axi_arcache_net_x0: std_logic_vector(3 downto 0);
  signal s_axi_arid_net_x0: std_logic_vector(7 downto 0);
  signal s_axi_arlen_net_x0: std_logic_vector(7 downto 0);
  signal s_axi_arlock_net_x0: std_logic_vector(1 downto 0);
  signal s_axi_arprot_net_x0: std_logic_vector(2 downto 0);
  signal s_axi_arsize_net_x0: std_logic_vector(2 downto 0);
  signal s_axi_arvalid_net_x0: std_logic;
  signal s_axi_awaddr_net_x0: std_logic_vector(31 downto 0);
  signal s_axi_awburst_net_x0: std_logic_vector(1 downto 0);
  signal s_axi_awcache_net_x0: std_logic_vector(3 downto 0);
  signal s_axi_awid_net_x0: std_logic_vector(7 downto 0);
  signal s_axi_awlen_net_x0: std_logic_vector(7 downto 0);
  signal s_axi_awlock_net_x0: std_logic_vector(1 downto 0);
  signal s_axi_awprot_net_x0: std_logic_vector(2 downto 0);
  signal s_axi_awsize_net_x0: std_logic_vector(2 downto 0);
  signal s_axi_awvalid_net_x0: std_logic;
  signal s_axi_bready_net_x0: std_logic;
  signal s_axi_rready_net_x0: std_logic;
  signal s_axi_wdata_net_x0: std_logic_vector(31 downto 0);
  signal s_axi_wlast_net_x0: std_logic;
  signal s_axi_wstrb_net_x0: std_logic_vector(3 downto 0);
  signal s_axi_wvalid_net_x0: std_logic;
  signal to_register10_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register11_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register12_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register13_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register14_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register15_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register16_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register1_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register2_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register3_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register4_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register5_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register6_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register7_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register8_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register9_dout_net_x0: std_logic_vector(31 downto 0);
  signal to_register_dout_net_x0: std_logic_vector(31 downto 0);

begin
  axi_aresetn_net_x0 <= axi_aresetn;
  from_register_data_out_net_x0 <= from_register;
  from_register1_data_out_net_x0 <= from_register1;
  from_register10_data_out_net_x0 <= from_register10;
  from_register2_data_out_net_x0 <= from_register2;
  from_register3_data_out_net_x0 <= from_register3;
  from_register4_data_out_net_x0 <= from_register4;
  from_register5_data_out_net_x0 <= from_register5;
  from_register6_data_out_net_x0 <= from_register6;
  from_register7_data_out_net_x0 <= from_register7;
  from_register8_data_out_net_x0 <= from_register8;
  from_register9_data_out_net_x0 <= from_register9;
  plb_ce_1_sg_x0 <= plb_ce_1;
  plb_clk_1_sg_x0 <= plb_clk_1;
  s_axi_araddr_net_x0 <= s_axi_araddr;
  s_axi_arburst_net_x0 <= s_axi_arburst;
  s_axi_arcache_net_x0 <= s_axi_arcache;
  s_axi_arid_net_x0 <= s_axi_arid;
  s_axi_arlen_net_x0 <= s_axi_arlen;
  s_axi_arlock_net_x0 <= s_axi_arlock;
  s_axi_arprot_net_x0 <= s_axi_arprot;
  s_axi_arsize_net_x0 <= s_axi_arsize;
  s_axi_arvalid_net_x0 <= s_axi_arvalid;
  s_axi_awaddr_net_x0 <= s_axi_awaddr;
  s_axi_awburst_net_x0 <= s_axi_awburst;
  s_axi_awcache_net_x0 <= s_axi_awcache;
  s_axi_awid_net_x0 <= s_axi_awid;
  s_axi_awlen_net_x0 <= s_axi_awlen;
  s_axi_awlock_net_x0 <= s_axi_awlock;
  s_axi_awprot_net_x0 <= s_axi_awprot;
  s_axi_awsize_net_x0 <= s_axi_awsize;
  s_axi_awvalid_net_x0 <= s_axi_awvalid;
  s_axi_bready_net_x0 <= s_axi_bready;
  s_axi_rready_net_x0 <= s_axi_rready;
  s_axi_wdata_net_x0 <= s_axi_wdata;
  s_axi_wlast_net_x0 <= s_axi_wlast;
  s_axi_wstrb_net_x0 <= s_axi_wstrb;
  s_axi_wvalid_net_x0 <= s_axi_wvalid;
  to_register_dout_net_x0 <= to_register;
  to_register1_dout_net_x0 <= to_register1;
  to_register10_dout_net_x0 <= to_register10;
  to_register11_dout_net_x0 <= to_register11;
  to_register12_dout_net_x0 <= to_register12;
  to_register13_dout_net_x0 <= to_register13;
  to_register14_dout_net_x0 <= to_register14;
  to_register15_dout_net_x0 <= to_register15;
  to_register16_dout_net_x0 <= to_register16;
  to_register2_dout_net_x0 <= to_register2;
  to_register3_dout_net_x0 <= to_register3;
  to_register4_dout_net_x0 <= to_register4;
  to_register5_dout_net_x0 <= to_register5;
  to_register6_dout_net_x0 <= to_register6;
  to_register7_dout_net_x0 <= to_register7;
  to_register8_dout_net_x0 <= to_register8;
  to_register9_dout_net_x0 <= to_register9;
  memmap_x0 <= memmap_s_axi_arready_net_x0;
  memmap_x1 <= memmap_s_axi_awready_net_x0;
  memmap_x10 <= memmap_s_axi_wready_net_x0;
  memmap_x11 <= memmap_sm_tx_ctrl_b_params_din_net_x0;
  memmap_x12 <= memmap_sm_tx_ctrl_b_params_en_net_x0;
  memmap_x13 <= memmap_sm_tx_ctrl_a_gains_din_net_x0;
  memmap_x14 <= memmap_sm_tx_ctrl_a_gains_en_net_x0;
  memmap_x15 <= memmap_sm_tx_ctrl_a_params_din_net_x0;
  memmap_x16 <= memmap_sm_tx_ctrl_a_params_en_net_x0;
  memmap_x17 <= memmap_sm_post_rx_timers_din_net_x0;
  memmap_x18 <= memmap_sm_post_rx_timers_en_net_x0;
  memmap_x19 <= memmap_sm_tx_ctrl_b_gains_din_net_x0;
  memmap_x2 <= memmap_s_axi_bid_net_x0;
  memmap_x20 <= memmap_sm_tx_ctrl_b_gains_en_net_x0;
  memmap_x21 <= memmap_sm_post_tx_timers_din_net_x0;
  memmap_x22 <= memmap_sm_post_tx_timers_en_net_x0;
  memmap_x23 <= memmap_sm_timestamp_insert_offset_din_net_x0;
  memmap_x24 <= memmap_sm_timestamp_insert_offset_en_net_x0;
  memmap_x25 <= memmap_sm_timestamp_set_lsb_din_net_x0;
  memmap_x26 <= memmap_sm_timestamp_set_lsb_en_net_x0;
  memmap_x27 <= memmap_sm_timestamp_set_msb_din_net_x0;
  memmap_x28 <= memmap_sm_timestamp_set_msb_en_net_x0;
  memmap_x29 <= memmap_sm_calib_times_din_net_x0;
  memmap_x3 <= memmap_s_axi_bresp_net_x0;
  memmap_x30 <= memmap_sm_calib_times_en_net_x0;
  memmap_x31 <= memmap_sm_ifs_intervals2_din_net_x0;
  memmap_x32 <= memmap_sm_ifs_intervals2_en_net_x0;
  memmap_x33 <= memmap_sm_ifs_intervals1_din_net_x0;
  memmap_x34 <= memmap_sm_ifs_intervals1_en_net_x0;
  memmap_x35 <= memmap_sm_tx_start_din_net_x0;
  memmap_x36 <= memmap_sm_tx_start_en_net_x0;
  memmap_x37 <= memmap_sm_control_din_net_x0;
  memmap_x38 <= memmap_sm_control_en_net_x0;
  memmap_x39 <= memmap_sm_nav_match_addr_1_din_net_x0;
  memmap_x4 <= memmap_s_axi_bvalid_net_x0;
  memmap_x40 <= memmap_sm_nav_match_addr_1_en_net_x0;
  memmap_x41 <= memmap_sm_nav_match_addr_2_din_net_x0;
  memmap_x42 <= memmap_sm_nav_match_addr_2_en_net_x0;
  memmap_x43 <= memmap_sm_backoff_ctrl_din_net_x0;
  memmap_x44 <= memmap_sm_backoff_ctrl_en_net_x0;
  memmap_x5 <= memmap_s_axi_rdata_net_x0;
  memmap_x6 <= memmap_s_axi_rid_net_x0;
  memmap_x7 <= memmap_s_axi_rlast_net_x0;
  memmap_x8 <= memmap_s_axi_rresp_net_x0;
  memmap_x9 <= memmap_s_axi_rvalid_net_x0;

  memmap: entity work.axi_sgiface
    port map (
      axi_aclk => plb_clk_1_sg_x0,
      axi_aresetn => axi_aresetn_net_x0,
      axi_ce => plb_ce_1_sg_x0,
      s_axi_araddr => s_axi_araddr_net_x0,
      s_axi_arburst => s_axi_arburst_net_x0,
      s_axi_arcache => s_axi_arcache_net_x0,
      s_axi_arid => s_axi_arid_net_x0,
      s_axi_arlen => s_axi_arlen_net_x0,
      s_axi_arlock => s_axi_arlock_net_x0,
      s_axi_arprot => s_axi_arprot_net_x0,
      s_axi_arsize => s_axi_arsize_net_x0,
      s_axi_arvalid => s_axi_arvalid_net_x0,
      s_axi_awaddr => s_axi_awaddr_net_x0,
      s_axi_awburst => s_axi_awburst_net_x0,
      s_axi_awcache => s_axi_awcache_net_x0,
      s_axi_awid => s_axi_awid_net_x0,
      s_axi_awlen => s_axi_awlen_net_x0,
      s_axi_awlock => s_axi_awlock_net_x0,
      s_axi_awprot => s_axi_awprot_net_x0,
      s_axi_awsize => s_axi_awsize_net_x0,
      s_axi_awvalid => s_axi_awvalid_net_x0,
      s_axi_bready => s_axi_bready_net_x0,
      s_axi_rready => s_axi_rready_net_x0,
      s_axi_wdata => s_axi_wdata_net_x0,
      s_axi_wlast => s_axi_wlast_net_x0,
      s_axi_wstrb => s_axi_wstrb_net_x0,
      s_axi_wvalid => s_axi_wvalid_net_x0,
      sm_backoff_counter_dout => from_register1_data_out_net_x0,
      sm_backoff_ctrl_dout => to_register16_dout_net_x0,
      sm_calib_times_dout => to_register9_dout_net_x0,
      sm_control_dout => to_register13_dout_net_x0,
      sm_ifs_intervals1_dout => to_register11_dout_net_x0,
      sm_ifs_intervals2_dout => to_register10_dout_net_x0,
      sm_latest_rx_byte_dout => from_register3_data_out_net_x0,
      sm_nav_match_addr_1_dout => to_register14_dout_net_x0,
      sm_nav_match_addr_2_dout => to_register15_dout_net_x0,
      sm_nav_value_dout => from_register_data_out_net_x0,
      sm_phy_rx_params_dout => from_register2_data_out_net_x0,
      sm_post_rx_timers_dout => to_register3_dout_net_x0,
      sm_post_tx_timers_dout => to_register5_dout_net_x0,
      sm_rx_start_timestamp_lsb_dout => from_register7_data_out_net_x0,
      sm_rx_start_timestamp_msb_dout => from_register6_data_out_net_x0,
      sm_status_dout => from_register10_data_out_net_x0,
      sm_timestamp_insert_offset_dout => to_register6_dout_net_x0,
      sm_timestamp_lsb_dout => from_register9_data_out_net_x0,
      sm_timestamp_msb_dout => from_register8_data_out_net_x0,
      sm_timestamp_set_lsb_dout => to_register7_dout_net_x0,
      sm_timestamp_set_msb_dout => to_register8_dout_net_x0,
      sm_tx_ctrl_a_gains_dout => to_register1_dout_net_x0,
      sm_tx_ctrl_a_params_dout => to_register2_dout_net_x0,
      sm_tx_ctrl_b_gains_dout => to_register4_dout_net_x0,
      sm_tx_ctrl_b_params_dout => to_register_dout_net_x0,
      sm_tx_start_dout => to_register12_dout_net_x0,
      sm_tx_start_timestamp_lsb_dout => from_register5_data_out_net_x0,
      sm_tx_start_timestamp_msb_dout => from_register4_data_out_net_x0,
      s_axi_arready => memmap_s_axi_arready_net_x0,
      s_axi_awready => memmap_s_axi_awready_net_x0,
      s_axi_bid => memmap_s_axi_bid_net_x0,
      s_axi_bresp => memmap_s_axi_bresp_net_x0,
      s_axi_bvalid => memmap_s_axi_bvalid_net_x0,
      s_axi_rdata => memmap_s_axi_rdata_net_x0,
      s_axi_rid => memmap_s_axi_rid_net_x0,
      s_axi_rlast => memmap_s_axi_rlast_net_x0,
      s_axi_rresp => memmap_s_axi_rresp_net_x0,
      s_axi_rvalid => memmap_s_axi_rvalid_net_x0,
      s_axi_wready => memmap_s_axi_wready_net_x0,
      sm_backoff_ctrl_din => memmap_sm_backoff_ctrl_din_net_x0,
      sm_backoff_ctrl_en => memmap_sm_backoff_ctrl_en_net_x0,
      sm_calib_times_din => memmap_sm_calib_times_din_net_x0,
      sm_calib_times_en => memmap_sm_calib_times_en_net_x0,
      sm_control_din => memmap_sm_control_din_net_x0,
      sm_control_en => memmap_sm_control_en_net_x0,
      sm_ifs_intervals1_din => memmap_sm_ifs_intervals1_din_net_x0,
      sm_ifs_intervals1_en => memmap_sm_ifs_intervals1_en_net_x0,
      sm_ifs_intervals2_din => memmap_sm_ifs_intervals2_din_net_x0,
      sm_ifs_intervals2_en => memmap_sm_ifs_intervals2_en_net_x0,
      sm_nav_match_addr_1_din => memmap_sm_nav_match_addr_1_din_net_x0,
      sm_nav_match_addr_1_en => memmap_sm_nav_match_addr_1_en_net_x0,
      sm_nav_match_addr_2_din => memmap_sm_nav_match_addr_2_din_net_x0,
      sm_nav_match_addr_2_en => memmap_sm_nav_match_addr_2_en_net_x0,
      sm_post_rx_timers_din => memmap_sm_post_rx_timers_din_net_x0,
      sm_post_rx_timers_en => memmap_sm_post_rx_timers_en_net_x0,
      sm_post_tx_timers_din => memmap_sm_post_tx_timers_din_net_x0,
      sm_post_tx_timers_en => memmap_sm_post_tx_timers_en_net_x0,
      sm_timestamp_insert_offset_din => memmap_sm_timestamp_insert_offset_din_net_x0,
      sm_timestamp_insert_offset_en => memmap_sm_timestamp_insert_offset_en_net_x0,
      sm_timestamp_set_lsb_din => memmap_sm_timestamp_set_lsb_din_net_x0,
      sm_timestamp_set_lsb_en => memmap_sm_timestamp_set_lsb_en_net_x0,
      sm_timestamp_set_msb_din => memmap_sm_timestamp_set_msb_din_net_x0,
      sm_timestamp_set_msb_en => memmap_sm_timestamp_set_msb_en_net_x0,
      sm_tx_ctrl_a_gains_din => memmap_sm_tx_ctrl_a_gains_din_net_x0,
      sm_tx_ctrl_a_gains_en => memmap_sm_tx_ctrl_a_gains_en_net_x0,
      sm_tx_ctrl_a_params_din => memmap_sm_tx_ctrl_a_params_din_net_x0,
      sm_tx_ctrl_a_params_en => memmap_sm_tx_ctrl_a_params_en_net_x0,
      sm_tx_ctrl_b_gains_din => memmap_sm_tx_ctrl_b_gains_din_net_x0,
      sm_tx_ctrl_b_gains_en => memmap_sm_tx_ctrl_b_gains_en_net_x0,
      sm_tx_ctrl_b_params_din => memmap_sm_tx_ctrl_b_params_din_net_x0,
      sm_tx_ctrl_b_params_en => memmap_sm_tx_ctrl_b_params_en_net_x0,
      sm_tx_start_din => memmap_sm_tx_start_din_net_x0,
      sm_tx_start_en => memmap_sm_tx_start_en_net_x0
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Idle for DIFS-EIFS/Bad Rx"

entity bad_rx_entity_0d840d48a2 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    phy_rx_end_ind: in std_logic; 
    phy_rx_end_rxerror: in std_logic_vector(3 downto 0); 
    phy_rx_fcs_good_ind: in std_logic; 
    rx: out std_logic
  );
end bad_rx_entity_0d840d48a2;

architecture structural of bad_rx_entity_0d840d48a2 is
  signal ce_1_sg_x14: std_logic;
  signal clk_1_sg_x14: std_logic;
  signal constant1_op_net: std_logic;
  signal inverter1_op_net: std_logic;
  signal logical1_y_net_x1: std_logic;
  signal logical3_y_net_x0: std_logic;
  signal logical4_y_net: std_logic;
  signal phy_rx_end_ind_net_x0: std_logic;
  signal phy_rx_end_rxerror_net_x0: std_logic_vector(3 downto 0);
  signal phy_rx_fcs_good_ind_net_x0: std_logic;
  signal relational1_op_net: std_logic;

begin
  ce_1_sg_x14 <= ce_1;
  clk_1_sg_x14 <= clk_1;
  phy_rx_end_ind_net_x0 <= phy_rx_end_ind;
  phy_rx_end_rxerror_net_x0 <= phy_rx_end_rxerror;
  phy_rx_fcs_good_ind_net_x0 <= phy_rx_fcs_good_ind;
  rx <= logical1_y_net_x1;

  constant1: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant1_op_net
    );

  inverter1: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x14,
      clk => clk_1_sg_x14,
      clr => '0',
      ip(0) => phy_rx_fcs_good_ind_net_x0,
      op(0) => inverter1_op_net
    );

  logical3: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => phy_rx_end_ind_net_x0,
      d1(0) => logical4_y_net,
      y(0) => logical3_y_net_x0
    );

  logical4: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => inverter1_op_net,
      d1(0) => relational1_op_net,
      y(0) => logical4_y_net
    );

  posedge1_98101a7f68: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x14,
      clk_1 => clk_1_sg_x14,
      d => logical3_y_net_x0,
      q => logical1_y_net_x1
    );

  relational1: entity work.relational_3c8242143a
    port map (
      a => phy_rx_end_rxerror_net_x0,
      b(0) => constant1_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational1_op_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Idle for DIFS-EIFS"

entity idle_for_difs_eifs_entity_d31a723322 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    global_reset: in std_logic; 
    medium_busy: in std_logic; 
    medium_idle: in std_logic; 
    phy_rx_end_ind: in std_logic; 
    phy_rx_end_rxerror: in std_logic_vector(3 downto 0); 
    phy_rx_fcs_good_ind: in std_logic; 
    reg_calibtime_txdifs: in std_logic_vector(13 downto 0); 
    reg_interval_difs: in std_logic_vector(13 downto 0); 
    reg_interval_eifs: in std_logic_vector(19 downto 0); 
    idle_for_difs: out std_logic; 
    idle_for_txdifs: out std_logic; 
    register1_x0: out std_logic; 
    register3_x0: out std_logic
  );
end idle_for_difs_eifs_entity_d31a723322;

architecture structural of idle_for_difs_eifs_entity_d31a723322 is
  signal b_0_y_net_x1: std_logic;
  signal ce_1_sg_x16: std_logic;
  signal clk_1_sg_x16: std_logic;
  signal concat1_y_net_x2: std_logic_vector(13 downto 0);
  signal concat1_y_net_x3: std_logic_vector(19 downto 0);
  signal concat1_y_net_x4: std_logic_vector(13 downto 0);
  signal difs_op_net: std_logic_vector(15 downto 0);
  signal inverter1_op_net_x1: std_logic;
  signal inverter_op_net: std_logic;
  signal logical1_y_net: std_logic;
  signal logical1_y_net_x2: std_logic;
  signal logical2_y_net: std_logic;
  signal logical3_y_net_x3: std_logic;
  signal logical5_y_net_x0: std_logic;
  signal mux1_y_net: std_logic_vector(19 downto 0);
  signal mux_y_net: std_logic_vector(19 downto 0);
  signal phy_rx_end_ind_net_x1: std_logic;
  signal phy_rx_end_rxerror_net_x1: std_logic_vector(3 downto 0);
  signal phy_rx_fcs_good_ind_net_x1: std_logic;
  signal register1_q_net_x0: std_logic;
  signal register2_q_net: std_logic;
  signal register2_q_net_x0: std_logic;
  signal register3_q_net_x0: std_logic;
  signal register_q_net: std_logic;
  signal relational1_op_net_x5: std_logic;
  signal relational3_op_net_x0: std_logic;

begin
  ce_1_sg_x16 <= ce_1;
  clk_1_sg_x16 <= clk_1;
  b_0_y_net_x1 <= global_reset;
  logical3_y_net_x3 <= medium_busy;
  inverter1_op_net_x1 <= medium_idle;
  phy_rx_end_ind_net_x1 <= phy_rx_end_ind;
  phy_rx_end_rxerror_net_x1 <= phy_rx_end_rxerror;
  phy_rx_fcs_good_ind_net_x1 <= phy_rx_fcs_good_ind;
  concat1_y_net_x4 <= reg_calibtime_txdifs;
  concat1_y_net_x2 <= reg_interval_difs;
  concat1_y_net_x3 <= reg_interval_eifs;
  idle_for_difs <= relational3_op_net_x0;
  idle_for_txdifs <= relational1_op_net_x5;
  register1_x0 <= register1_q_net_x0;
  register3_x0 <= register3_q_net_x0;

  bad_rx_0d840d48a2: entity work.bad_rx_entity_0d840d48a2
    port map (
      ce_1 => ce_1_sg_x16,
      clk_1 => clk_1_sg_x16,
      phy_rx_end_ind => phy_rx_end_ind_net_x1,
      phy_rx_end_rxerror => phy_rx_end_rxerror_net_x1,
      phy_rx_fcs_good_ind => phy_rx_fcs_good_ind_net_x1,
      rx => logical1_y_net_x2
    );

  difs: entity work.xlcounter_free_wlan_mac_hw
    generic map (
      core_name0 => "cntr_11_0_5b0a1653ddb23333",
      op_arith => xlUnsigned,
      op_width => 16
    )
    port map (
      ce => ce_1_sg_x16,
      clk => clk_1_sg_x16,
      clr => '0',
      en(0) => logical1_y_net,
      rst(0) => logical2_y_net,
      op => difs_op_net
    );

  inverter: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x16,
      clk => clk_1_sg_x16,
      clr => '0',
      ip(0) => relational3_op_net_x0,
      op(0) => inverter_op_net
    );

  logical1: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => inverter1_op_net_x1,
      d1(0) => inverter_op_net,
      y(0) => logical1_y_net
    );

  logical2: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => b_0_y_net_x1,
      d1(0) => logical3_y_net_x3,
      y(0) => logical2_y_net
    );

  logical5: entity work.logical_6cb8f0ce02
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational3_op_net_x0,
      d1(0) => logical3_y_net_x3,
      d2(0) => b_0_y_net_x1,
      y(0) => logical5_y_net_x0
    );

  mux: entity work.mux_3efa5ceb62
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0 => concat1_y_net_x2,
      d1 => concat1_y_net_x3,
      sel(0) => register2_q_net_x0,
      y => mux_y_net
    );

  mux1: entity work.mux_3efa5ceb62
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0 => concat1_y_net_x4,
      d1 => concat1_y_net_x3,
      sel(0) => register2_q_net_x0,
      y => mux1_y_net
    );

  register1: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x16,
      clk => clk_1_sg_x16,
      d(0) => register_q_net,
      en => "1",
      rst => "0",
      q(0) => register1_q_net_x0
    );

  register2: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x16,
      clk => clk_1_sg_x16,
      d(0) => register2_q_net_x0,
      en => "1",
      rst => "0",
      q(0) => register2_q_net
    );

  register3: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x16,
      clk => clk_1_sg_x16,
      d(0) => register2_q_net,
      en => "1",
      rst => "0",
      q(0) => register3_q_net_x0
    );

  register_x0: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x16,
      clk => clk_1_sg_x16,
      d(0) => relational1_op_net_x5,
      en => "1",
      rst => "0",
      q(0) => register_q_net
    );

  relational1: entity work.relational_6fce5fc0e4
    port map (
      a => difs_op_net,
      b => mux1_y_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational1_op_net_x5
    );

  relational3: entity work.relational_6fce5fc0e4
    port map (
      a => difs_op_net,
      b => mux_y_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational3_op_net_x0
    );

  s_r_latch1_5ecb38e786: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x16,
      clk_1 => clk_1_sg_x16,
      r => logical5_y_net_x0,
      s => logical1_y_net_x2,
      q => register2_q_net_x0
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/NAV/New Duration/Capture Rx Pkt Duration Field"

entity capture_rx_pkt_duration_field_entity_aac1b7925e is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    phy_rx_byte: in std_logic_vector(7 downto 0); 
    phy_rx_byte_valid: in std_logic; 
    phy_rx_bytenum: in std_logic_vector(15 downto 0); 
    phy_rx_start_ind: in std_logic; 
    duration: out std_logic_vector(15 downto 0)
  );
end capture_rx_pkt_duration_field_entity_aac1b7925e;

architecture structural of capture_rx_pkt_duration_field_entity_aac1b7925e is
  signal ce_1_sg_x17: std_logic;
  signal clk_1_sg_x17: std_logic;
  signal concat_y_net: std_logic_vector(15 downto 0);
  signal constant1_op_net: std_logic_vector(1 downto 0);
  signal constant2_op_net: std_logic_vector(1 downto 0);
  signal constant_op_net: std_logic_vector(1 downto 0);
  signal logical1_y_net: std_logic;
  signal logical_y_net: std_logic;
  signal msb_y_net: std_logic;
  signal mux_y_net_x0: std_logic_vector(15 downto 0);
  signal phy_rx_data_byte_net_x0: std_logic_vector(7 downto 0);
  signal phy_rx_data_bytenum_net_x0: std_logic_vector(15 downto 0);
  signal phy_rx_data_ind_net_x0: std_logic;
  signal phy_rx_start_ind_net_x0: std_logic;
  signal register1_q_net: std_logic_vector(7 downto 0);
  signal register_q_net: std_logic_vector(7 downto 0);
  signal relational1_op_net: std_logic;
  signal relational2_op_net: std_logic;

begin
  ce_1_sg_x17 <= ce_1;
  clk_1_sg_x17 <= clk_1;
  phy_rx_data_byte_net_x0 <= phy_rx_byte;
  phy_rx_data_ind_net_x0 <= phy_rx_byte_valid;
  phy_rx_data_bytenum_net_x0 <= phy_rx_bytenum;
  phy_rx_start_ind_net_x0 <= phy_rx_start_ind;
  duration <= mux_y_net_x0;

  concat: entity work.concat_8e53793314
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      in0 => register1_q_net,
      in1 => register_q_net,
      y => concat_y_net
    );

  constant1: entity work.constant_3a9a3daeb9
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op => constant1_op_net
    );

  constant2: entity work.constant_cda50df78a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op => constant2_op_net
    );

  constant_x0: entity work.constant_e8ddc079e9
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op => constant_op_net
    );

  logical: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => phy_rx_data_ind_net_x0,
      d1(0) => relational1_op_net,
      y(0) => logical_y_net
    );

  logical1: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => phy_rx_data_ind_net_x0,
      d1(0) => relational2_op_net,
      y(0) => logical1_y_net
    );

  msb: entity work.xlslice
    generic map (
      new_lsb => 15,
      new_msb => 15,
      x_width => 16,
      y_width => 1
    )
    port map (
      x => concat_y_net,
      y(0) => msb_y_net
    );

  mux: entity work.mux_03e37234da
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0 => concat_y_net,
      d1 => constant2_op_net,
      sel(0) => msb_y_net,
      y => mux_y_net_x0
    );

  register1: entity work.xlregister
    generic map (
      d_width => 8,
      init_value => b"00000000"
    )
    port map (
      ce => ce_1_sg_x17,
      clk => clk_1_sg_x17,
      d => phy_rx_data_byte_net_x0,
      en(0) => logical1_y_net,
      rst(0) => phy_rx_start_ind_net_x0,
      q => register1_q_net
    );

  register_x0: entity work.xlregister
    generic map (
      d_width => 8,
      init_value => b"00000000"
    )
    port map (
      ce => ce_1_sg_x17,
      clk => clk_1_sg_x17,
      d => phy_rx_data_byte_net_x0,
      en(0) => logical_y_net,
      rst(0) => phy_rx_start_ind_net_x0,
      q => register_q_net
    );

  relational1: entity work.relational_95b230a7ba
    port map (
      a => phy_rx_data_bytenum_net_x0,
      b => constant_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational1_op_net
    );

  relational2: entity work.relational_95b230a7ba
    port map (
      a => phy_rx_data_bytenum_net_x0,
      b => constant1_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational2_op_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/NAV/New Duration/Check Dest Addr"

entity check_dest_addr_entity_093125f060 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    phy_rx_byte: in std_logic_vector(7 downto 0); 
    phy_rx_byte_valid: in std_logic; 
    phy_rx_bytenum: in std_logic_vector(15 downto 0); 
    reg_nav_check_addr_1: in std_logic_vector(31 downto 0); 
    reg_nav_check_addr_2: in std_logic_vector(31 downto 0); 
    addr_match: out std_logic
  );
end check_dest_addr_entity_093125f060;

architecture structural of check_dest_addr_entity_093125f060 is
  signal b_0_y_net: std_logic_vector(7 downto 0);
  signal b_0_y_net_x0: std_logic_vector(7 downto 0);
  signal b_1_0_y_net: std_logic_vector(1 downto 0);
  signal b_1_y_net: std_logic_vector(7 downto 0);
  signal b_1_y_net_x0: std_logic_vector(7 downto 0);
  signal b_2_y_net: std_logic_vector(7 downto 0);
  signal b_3_y_net: std_logic_vector(7 downto 0);
  signal b_3_y_net_x0: std_logic;
  signal ce_1_sg_x18: std_logic;
  signal clk_1_sg_x18: std_logic;
  signal concat_y_net: std_logic_vector(2 downto 0);
  signal constant1_op_net: std_logic_vector(2 downto 0);
  signal constant2_op_net: std_logic_vector(3 downto 0);
  signal constant_op_net: std_logic;
  signal delay_q_net: std_logic;
  signal logical1_y_net: std_logic;
  signal logical6_y_net: std_logic;
  signal mux_y_net: std_logic_vector(7 downto 0);
  signal phy_rx_data_byte_net_x1: std_logic_vector(7 downto 0);
  signal phy_rx_data_bytenum_net_x1: std_logic_vector(15 downto 0);
  signal phy_rx_data_ind_net_x1: std_logic;
  signal register1_q_net: std_logic_vector(15 downto 0);
  signal register2_q_net: std_logic;
  signal register3_q_net: std_logic_vector(7 downto 0);
  signal register4_q_net_x0: std_logic;
  signal register69_q_net_x0: std_logic_vector(31 downto 0);
  signal register6_q_net: std_logic;
  signal register71_q_net_x0: std_logic_vector(31 downto 0);
  signal relational1_op_net: std_logic;
  signal relational2_op_net: std_logic;
  signal relational9_op_net: std_logic;

begin
  ce_1_sg_x18 <= ce_1;
  clk_1_sg_x18 <= clk_1;
  phy_rx_data_byte_net_x1 <= phy_rx_byte;
  phy_rx_data_ind_net_x1 <= phy_rx_byte_valid;
  phy_rx_data_bytenum_net_x1 <= phy_rx_bytenum;
  register71_q_net_x0 <= reg_nav_check_addr_1;
  register69_q_net_x0 <= reg_nav_check_addr_2;
  addr_match <= register4_q_net_x0;

  b_0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 7,
      x_width => 32,
      y_width => 8
    )
    port map (
      x => register71_q_net_x0,
      y => b_0_y_net
    );

  b_0_x0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 7,
      x_width => 32,
      y_width => 8
    )
    port map (
      x => register69_q_net_x0,
      y => b_0_y_net_x0
    );

  b_1: entity work.xlslice
    generic map (
      new_lsb => 8,
      new_msb => 15,
      x_width => 32,
      y_width => 8
    )
    port map (
      x => register71_q_net_x0,
      y => b_1_y_net
    );

  b_1_0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 1,
      x_width => 16,
      y_width => 2
    )
    port map (
      x => register1_q_net,
      y => b_1_0_y_net
    );

  b_1_x0: entity work.xlslice
    generic map (
      new_lsb => 8,
      new_msb => 15,
      x_width => 32,
      y_width => 8
    )
    port map (
      x => register69_q_net_x0,
      y => b_1_y_net_x0
    );

  b_2: entity work.xlslice
    generic map (
      new_lsb => 16,
      new_msb => 23,
      x_width => 32,
      y_width => 8
    )
    port map (
      x => register71_q_net_x0,
      y => b_2_y_net
    );

  b_3: entity work.xlslice
    generic map (
      new_lsb => 24,
      new_msb => 31,
      x_width => 32,
      y_width => 8
    )
    port map (
      x => register71_q_net_x0,
      y => b_3_y_net
    );

  b_3_x0: entity work.xlslice
    generic map (
      new_lsb => 3,
      new_msb => 3,
      x_width => 16,
      y_width => 1
    )
    port map (
      x => register1_q_net,
      y(0) => b_3_y_net_x0
    );

  concat: entity work.concat_4a9a9a25a3
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      in0(0) => b_3_y_net_x0,
      in1 => b_1_0_y_net,
      y => concat_y_net
    );

  constant1: entity work.constant_0f59f02ba5
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op => constant1_op_net
    );

  constant2: entity work.constant_145086465d
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op => constant2_op_net
    );

  constant_x0: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant_op_net
    );

  delay: entity work.xldelay
    generic map (
      latency => 1,
      reg_retiming => 0,
      reset => 0,
      width => 1
    )
    port map (
      ce => ce_1_sg_x18,
      clk => clk_1_sg_x18,
      d(0) => relational2_op_net,
      en => '1',
      rst => '1',
      q(0) => delay_q_net
    );

  logical1: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational1_op_net,
      d1(0) => register2_q_net,
      y(0) => logical1_y_net
    );

  logical6: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational9_op_net,
      d1(0) => register6_q_net,
      y(0) => logical6_y_net
    );

  mux: entity work.mux_29b032b226
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0 => b_0_y_net,
      d1 => b_1_y_net,
      d2 => b_2_y_net,
      d3 => b_3_y_net,
      d4 => b_0_y_net_x0,
      d5 => b_1_y_net_x0,
      d6(0) => constant_op_net,
      d7(0) => constant_op_net,
      sel => concat_y_net,
      y => mux_y_net
    );

  register1: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x18,
      clk => clk_1_sg_x18,
      d => phy_rx_data_bytenum_net_x1,
      en => "1",
      rst => "0",
      q => register1_q_net
    );

  register2: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x18,
      clk => clk_1_sg_x18,
      d(0) => phy_rx_data_ind_net_x1,
      en => "1",
      rst => "0",
      q(0) => register2_q_net
    );

  register3: entity work.xlregister
    generic map (
      d_width => 8,
      init_value => b"00000000"
    )
    port map (
      ce => ce_1_sg_x18,
      clk => clk_1_sg_x18,
      d => phy_rx_data_byte_net_x1,
      en => "1",
      rst => "0",
      q => register3_q_net
    );

  register4: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x18,
      clk => clk_1_sg_x18,
      d(0) => register6_q_net,
      en(0) => delay_q_net,
      rst(0) => logical1_y_net,
      q(0) => register4_q_net_x0
    );

  register6: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"1"
    )
    port map (
      ce => ce_1_sg_x18,
      clk => clk_1_sg_x18,
      d(0) => logical6_y_net,
      en(0) => register2_q_net,
      rst(0) => logical1_y_net,
      q(0) => register6_q_net
    );

  relational1: entity work.relational_3eccb4b5fa
    port map (
      a => register1_q_net,
      b => constant1_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational1_op_net
    );

  relational2: entity work.relational_573d663832
    port map (
      a => register1_q_net,
      b => constant2_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational2_op_net
    );

  relational9: entity work.relational_54048c8b02
    port map (
      a => register3_q_net,
      b => mux_y_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational9_op_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/NAV/New Duration/x16"

entity x16_entity_4ed5525b69 is
  port (
    a: in std_logic_vector(20 downto 0); 
    ax16: out std_logic_vector(24 downto 0)
  );
end x16_entity_4ed5525b69;

architecture structural of x16_entity_4ed5525b69 is
  signal addsub_s_net_x0: std_logic_vector(20 downto 0);
  signal concat1_y_net_x0: std_logic_vector(24 downto 0);
  signal constant9_op_net: std_logic_vector(3 downto 0);

begin
  addsub_s_net_x0 <= a;
  ax16 <= concat1_y_net_x0;

  concat1: entity work.concat_22af082bf9
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      in0 => addsub_s_net_x0,
      in1 => constant9_op_net,
      y => concat1_y_net_x0
    );

  constant9: entity work.constant_4c449dd556
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op => constant9_op_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/NAV/New Duration"

entity new_duration_entity_efbebbd314 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    phy_rx_data_byte: in std_logic_vector(7 downto 0); 
    phy_rx_data_bytenum: in std_logic_vector(15 downto 0); 
    phy_rx_data_ind: in std_logic; 
    phy_rx_end_ind: in std_logic; 
    phy_rx_end_rxerror: in std_logic_vector(3 downto 0); 
    phy_rx_start_ind: in std_logic; 
    reg_nav_time_adj: in std_logic_vector(7 downto 0); 
    register69: in std_logic_vector(31 downto 0); 
    register71: in std_logic_vector(31 downto 0); 
    status_rx_fcs_good: in std_logic; 
    check_dest_addr: out std_logic; 
    duration: out std_logic_vector(24 downto 0); 
    valid: out std_logic
  );
end new_duration_entity_efbebbd314;

architecture structural of new_duration_entity_efbebbd314 is
  signal addsub_s_net_x0: std_logic_vector(20 downto 0);
  signal ce_1_sg_x20: std_logic;
  signal clk_1_sg_x20: std_logic;
  signal concat1_y_net_x1: std_logic_vector(24 downto 0);
  signal constant1_op_net: std_logic_vector(3 downto 0);
  signal constant3_op_net: std_logic;
  signal delay1_q_net_x0: std_logic;
  signal delay_q_net: std_logic;
  signal inverter_op_net: std_logic;
  signal logical1_y_net_x1: std_logic;
  signal logical2_y_net: std_logic;
  signal mult_p_net: std_logic_vector(19 downto 0);
  signal mux_y_net_x0: std_logic_vector(15 downto 0);
  signal phy_rx_data_byte_net_x2: std_logic_vector(7 downto 0);
  signal phy_rx_data_bytenum_net_x2: std_logic_vector(15 downto 0);
  signal phy_rx_data_ind_net_x2: std_logic;
  signal phy_rx_end_ind_net_x2: std_logic;
  signal phy_rx_end_rxerror_net_x2: std_logic_vector(3 downto 0);
  signal phy_rx_start_ind_net_x1: std_logic;
  signal register2_q_net: std_logic_vector(15 downto 0);
  signal register3_q_net_x0: std_logic;
  signal register4_q_net_x1: std_logic;
  signal register69_q_net_x1: std_logic_vector(31 downto 0);
  signal register71_q_net_x1: std_logic_vector(31 downto 0);
  signal reinterpret_output_port_net_x0: std_logic_vector(7 downto 0);
  signal relational3_op_net: std_logic;

begin
  ce_1_sg_x20 <= ce_1;
  clk_1_sg_x20 <= clk_1;
  phy_rx_data_byte_net_x2 <= phy_rx_data_byte;
  phy_rx_data_bytenum_net_x2 <= phy_rx_data_bytenum;
  phy_rx_data_ind_net_x2 <= phy_rx_data_ind;
  phy_rx_end_ind_net_x2 <= phy_rx_end_ind;
  phy_rx_end_rxerror_net_x2 <= phy_rx_end_rxerror;
  phy_rx_start_ind_net_x1 <= phy_rx_start_ind;
  reinterpret_output_port_net_x0 <= reg_nav_time_adj;
  register69_q_net_x1 <= register69;
  register71_q_net_x1 <= register71;
  register3_q_net_x0 <= status_rx_fcs_good;
  check_dest_addr <= register4_q_net_x1;
  duration <= concat1_y_net_x1;
  valid <= logical1_y_net_x1;

  addsub: entity work.xladdsub_wlan_mac_hw
    generic map (
      a_arith => xlUnsigned,
      a_bin_pt => 0,
      a_width => 20,
      b_arith => xlSigned,
      b_bin_pt => 0,
      b_width => 8,
      c_has_c_out => 0,
      c_latency => 0,
      c_output_width => 22,
      core_name0 => "addsb_11_0_38dd91dde0ab1a97",
      extra_registers => 0,
      full_s_arith => 2,
      full_s_width => 22,
      latency => 0,
      overflow => 1,
      quantization => 1,
      s_arith => xlUnsigned,
      s_bin_pt => 0,
      s_width => 21
    )
    port map (
      a => mult_p_net,
      b => reinterpret_output_port_net_x0,
      ce => ce_1_sg_x20,
      clk => clk_1_sg_x20,
      clr => '0',
      en => "1",
      s => addsub_s_net_x0
    );

  capture_rx_pkt_duration_field_aac1b7925e: entity work.capture_rx_pkt_duration_field_entity_aac1b7925e
    port map (
      ce_1 => ce_1_sg_x20,
      clk_1 => clk_1_sg_x20,
      phy_rx_byte => phy_rx_data_byte_net_x2,
      phy_rx_byte_valid => phy_rx_data_ind_net_x2,
      phy_rx_bytenum => phy_rx_data_bytenum_net_x2,
      phy_rx_start_ind => phy_rx_start_ind_net_x1,
      duration => mux_y_net_x0
    );

  check_dest_addr_093125f060: entity work.check_dest_addr_entity_093125f060
    port map (
      ce_1 => ce_1_sg_x20,
      clk_1 => clk_1_sg_x20,
      phy_rx_byte => phy_rx_data_byte_net_x2,
      phy_rx_byte_valid => phy_rx_data_ind_net_x2,
      phy_rx_bytenum => phy_rx_data_bytenum_net_x2,
      reg_nav_check_addr_1 => register71_q_net_x1,
      reg_nav_check_addr_2 => register69_q_net_x1,
      addr_match => register4_q_net_x1
    );

  constant1: entity work.constant_5c1626e05e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op => constant1_op_net
    );

  constant3: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant3_op_net
    );

  delay: entity work.xldelay
    generic map (
      latency => 1,
      reg_retiming => 0,
      reset => 0,
      width => 1
    )
    port map (
      ce => ce_1_sg_x20,
      clk => clk_1_sg_x20,
      d(0) => logical2_y_net,
      en => '1',
      rst => '1',
      q(0) => delay_q_net
    );

  delay1: entity work.xldelay
    generic map (
      latency => 1,
      reg_retiming => 0,
      reset => 0,
      width => 1
    )
    port map (
      ce => ce_1_sg_x20,
      clk => clk_1_sg_x20,
      d(0) => delay_q_net,
      en => '1',
      rst => '1',
      q(0) => delay1_q_net_x0
    );

  inverter: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x20,
      clk => clk_1_sg_x20,
      clr => '0',
      ip(0) => register4_q_net_x1,
      op(0) => inverter_op_net
    );

  logical2: entity work.logical_3640e86e6c
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => register3_q_net_x0,
      d1(0) => phy_rx_end_ind_net_x2,
      d2(0) => relational3_op_net,
      d3(0) => inverter_op_net,
      y(0) => logical2_y_net
    );

  mult: entity work.xlmult_wlan_mac_hw
    generic map (
      a_arith => xlUnsigned,
      a_bin_pt => 0,
      a_width => 4,
      b_arith => xlUnsigned,
      b_bin_pt => 0,
      b_width => 16,
      c_a_type => 1,
      c_a_width => 4,
      c_b_type => 1,
      c_b_width => 16,
      c_baat => 4,
      c_output_width => 20,
      c_type => 1,
      core_name0 => "mult_11_2_7def12de86dcdc6a",
      extra_registers => 0,
      multsign => 1,
      overflow => 1,
      p_arith => xlUnsigned,
      p_bin_pt => 0,
      p_width => 20,
      quantization => 1
    )
    port map (
      a => constant1_op_net,
      b => register2_q_net,
      ce => ce_1_sg_x20,
      clk => clk_1_sg_x20,
      clr => '0',
      core_ce => ce_1_sg_x20,
      core_clk => clk_1_sg_x20,
      core_clr => '1',
      en => "1",
      rst => "0",
      p => mult_p_net
    );

  posedge1_886cae88a4: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x20,
      clk_1 => clk_1_sg_x20,
      d => delay1_q_net_x0,
      q => logical1_y_net_x1
    );

  register2: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x20,
      clk => clk_1_sg_x20,
      d => mux_y_net_x0,
      en(0) => logical2_y_net,
      rst(0) => phy_rx_start_ind_net_x1,
      q => register2_q_net
    );

  relational3: entity work.relational_ee03197e2c
    port map (
      a => phy_rx_end_rxerror_net_x2,
      b(0) => constant3_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational3_op_net
    );

  x16_4ed5525b69: entity work.x16_entity_4ed5525b69
    port map (
      a => addsub_s_net_x0,
      ax16 => concat1_y_net_x1
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/NAV"

entity nav_entity_556d0ea53d is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    global_reset: in std_logic; 
    phy_rx_data_byte: in std_logic_vector(7 downto 0); 
    phy_rx_data_bytenum: in std_logic_vector(15 downto 0); 
    phy_rx_data_ind: in std_logic; 
    phy_rx_end_ind: in std_logic; 
    phy_rx_end_rxerror: in std_logic_vector(3 downto 0); 
    phy_rx_start_ind: in std_logic; 
    reg_disable_nav: in std_logic; 
    reg_force_reset_nav: in std_logic; 
    register3: in std_logic; 
    register69: in std_logic_vector(31 downto 0); 
    register71: in std_logic_vector(31 downto 0); 
    reinterpret: in std_logic_vector(7 downto 0); 
    nav_busy: out std_logic; 
    nav_value_100nsec: out std_logic_vector(15 downto 0); 
    nav_zero: out std_logic; 
    new_duration: out std_logic; 
    register1_x0: out std_logic
  );
end nav_entity_556d0ea53d;

architecture structural of nav_entity_556d0ea53d is
  signal b_0_y_net_x2: std_logic;
  signal b_10_y_net: std_logic;
  signal b_3_y_net: std_logic;
  signal bitsm_4_y_net_x0: std_logic_vector(15 downto 0);
  signal ce_1_sg_x21: std_logic;
  signal clk_1_sg_x21: std_logic;
  signal concat1_y_net_x1: std_logic_vector(24 downto 0);
  signal constant_op_net: std_logic;
  signal convert_dout_net: std_logic_vector(19 downto 0);
  signal inverter1_op_net_x0: std_logic;
  signal inverter_op_net: std_logic;
  signal logical1_y_net: std_logic;
  signal logical1_y_net_x1: std_logic;
  signal logical2_y_net: std_logic;
  signal logical3_y_net_x2: std_logic;
  signal logical4_y_net: std_logic;
  signal nav_counter_op_net: std_logic_vector(19 downto 0);
  signal phy_rx_data_byte_net_x3: std_logic_vector(7 downto 0);
  signal phy_rx_data_bytenum_net_x3: std_logic_vector(15 downto 0);
  signal phy_rx_data_ind_net_x3: std_logic;
  signal phy_rx_end_ind_net_x3: std_logic;
  signal phy_rx_end_rxerror_net_x3: std_logic_vector(3 downto 0);
  signal phy_rx_start_ind_net_x2: std_logic;
  signal register1_q_net_x0: std_logic;
  signal register3_q_net_x1: std_logic;
  signal register4_q_net_x2: std_logic;
  signal register69_q_net_x2: std_logic_vector(31 downto 0);
  signal register71_q_net_x2: std_logic_vector(31 downto 0);
  signal register_q_net: std_logic;
  signal reinterpret_output_port_net_x1: std_logic_vector(7 downto 0);
  signal relational1_op_net: std_logic;
  signal relational2_op_net: std_logic;

begin
  ce_1_sg_x21 <= ce_1;
  clk_1_sg_x21 <= clk_1;
  b_0_y_net_x2 <= global_reset;
  phy_rx_data_byte_net_x3 <= phy_rx_data_byte;
  phy_rx_data_bytenum_net_x3 <= phy_rx_data_bytenum;
  phy_rx_data_ind_net_x3 <= phy_rx_data_ind;
  phy_rx_end_ind_net_x3 <= phy_rx_end_ind;
  phy_rx_end_rxerror_net_x3 <= phy_rx_end_rxerror;
  phy_rx_start_ind_net_x2 <= phy_rx_start_ind;
  b_3_y_net <= reg_disable_nav;
  b_10_y_net <= reg_force_reset_nav;
  register3_q_net_x1 <= register3;
  register69_q_net_x2 <= register69;
  register71_q_net_x2 <= register71;
  reinterpret_output_port_net_x1 <= reinterpret;
  nav_busy <= logical3_y_net_x2;
  nav_value_100nsec <= bitsm_4_y_net_x0;
  nav_zero <= inverter1_op_net_x0;
  new_duration <= register4_q_net_x2;
  register1_x0 <= register1_q_net_x0;

  bitsm_4: entity work.xlslice
    generic map (
      new_lsb => 4,
      new_msb => 19,
      x_width => 20,
      y_width => 16
    )
    port map (
      x => nav_counter_op_net,
      y => bitsm_4_y_net_x0
    );

  constant_x0: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant_op_net
    );

  convert: entity work.xlconvert
    generic map (
      bool_conversion => 0,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 25,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 20,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x21,
      clk => clk_1_sg_x21,
      clr => '0',
      din => concat1_y_net_x1,
      en => "1",
      dout => convert_dout_net
    );

  inverter: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x21,
      clk => clk_1_sg_x21,
      clr => '0',
      ip(0) => b_3_y_net,
      op(0) => inverter_op_net
    );

  inverter1: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x21,
      clk => clk_1_sg_x21,
      clr => '0',
      ip(0) => logical3_y_net_x2,
      op(0) => inverter1_op_net_x0
    );

  logical1: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational1_op_net,
      d1(0) => logical1_y_net_x1,
      y(0) => logical1_y_net
    );

  logical2: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net,
      d1(0) => relational2_op_net,
      y(0) => logical2_y_net
    );

  logical3: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => inverter_op_net,
      d1(0) => relational2_op_net,
      y(0) => logical3_y_net_x2
    );

  logical4: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => b_0_y_net_x2,
      d1(0) => b_10_y_net,
      y(0) => logical4_y_net
    );

  nav_counter: entity work.xlcounter_free_wlan_mac_hw
    generic map (
      core_name0 => "cntr_11_0_33b670dfb2dd60f1",
      op_arith => xlUnsigned,
      op_width => 20
    )
    port map (
      ce => ce_1_sg_x21,
      clk => clk_1_sg_x21,
      clr => '0',
      din => convert_dout_net,
      en(0) => logical2_y_net,
      load(0) => logical1_y_net,
      rst(0) => logical4_y_net,
      op => nav_counter_op_net
    );

  new_duration_efbebbd314: entity work.new_duration_entity_efbebbd314
    port map (
      ce_1 => ce_1_sg_x21,
      clk_1 => clk_1_sg_x21,
      phy_rx_data_byte => phy_rx_data_byte_net_x3,
      phy_rx_data_bytenum => phy_rx_data_bytenum_net_x3,
      phy_rx_data_ind => phy_rx_data_ind_net_x3,
      phy_rx_end_ind => phy_rx_end_ind_net_x3,
      phy_rx_end_rxerror => phy_rx_end_rxerror_net_x3,
      phy_rx_start_ind => phy_rx_start_ind_net_x2,
      reg_nav_time_adj => reinterpret_output_port_net_x1,
      register69 => register69_q_net_x2,
      register71 => register71_q_net_x2,
      status_rx_fcs_good => register3_q_net_x1,
      check_dest_addr => register4_q_net_x2,
      duration => concat1_y_net_x1,
      valid => logical1_y_net_x1
    );

  register1: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x21,
      clk => clk_1_sg_x21,
      d(0) => register_q_net,
      en => "1",
      rst => "0",
      q(0) => register1_q_net_x0
    );

  register_x0: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x21,
      clk => clk_1_sg_x21,
      d(0) => logical3_y_net_x2,
      en => "1",
      rst => "0",
      q(0) => register_q_net
    );

  relational1: entity work.relational_bebc7e34dc
    port map (
      a => nav_counter_op_net,
      b => concat1_y_net_x1,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational1_op_net
    );

  relational2: entity work.relational_77a58970b2
    port map (
      a => nav_counter_op_net,
      b(0) => constant_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational2_op_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/PHY I/O/PHY Rx Ports"

entity phy_rx_ports_entity_b0683ed47c is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    global_reset: in std_logic; 
    phy_rx_end_ind: in std_logic; 
    phy_rx_end_rxerror: in std_logic_vector(3 downto 0); 
    phy_rx_fcs_good_ind: in std_logic; 
    reg_block_rx_clear: in std_logic; 
    reg_block_rx_on_fcs_good: in std_logic; 
    reg_block_rx_on_tx: in std_logic; 
    reg_block_rx_on_valid_rxend: in std_logic; 
    status_tx_phy_active: in std_logic; 
    register2_x0: out std_logic; 
    status_blocked_on_good_fcs: out std_logic; 
    status_blocked_on_rxend: out std_logic
  );
end phy_rx_ports_entity_b0683ed47c;

architecture structural of phy_rx_ports_entity_b0683ed47c is
  signal b_0_y_net_x3: std_logic;
  signal b_1_y_net_x0: std_logic;
  signal b_4_y_net: std_logic;
  signal b_6_y_net: std_logic;
  signal ce_1_sg_x24: std_logic;
  signal clk_1_sg_x24: std_logic;
  signal constant_op_net: std_logic;
  signal logical1_y_net_x0: std_logic;
  signal logical2_y_net_x0: std_logic;
  signal logical5_y_net: std_logic;
  signal logical6_y_net: std_logic;
  signal logical7_y_net_x0: std_logic;
  signal logical8_y_net_x1: std_logic;
  signal phy_rx_end_ind_net_x4: std_logic;
  signal phy_rx_end_rxerror_net_x4: std_logic_vector(3 downto 0);
  signal phy_rx_fcs_good_ind_net_x2: std_logic;
  signal register2_q_net_x3: std_logic;
  signal register2_q_net_x4: std_logic;
  signal register2_q_net_x5: std_logic;
  signal register2_q_net_x6: std_logic;
  signal relational2_op_net: std_logic;

begin
  ce_1_sg_x24 <= ce_1;
  clk_1_sg_x24 <= clk_1;
  b_0_y_net_x3 <= global_reset;
  phy_rx_end_ind_net_x4 <= phy_rx_end_ind;
  phy_rx_end_rxerror_net_x4 <= phy_rx_end_rxerror;
  phy_rx_fcs_good_ind_net_x2 <= phy_rx_fcs_good_ind;
  logical1_y_net_x0 <= reg_block_rx_clear;
  b_1_y_net_x0 <= reg_block_rx_on_fcs_good;
  b_4_y_net <= reg_block_rx_on_tx;
  b_6_y_net <= reg_block_rx_on_valid_rxend;
  register2_q_net_x3 <= status_tx_phy_active;
  register2_x0 <= register2_q_net_x4;
  status_blocked_on_good_fcs <= register2_q_net_x5;
  status_blocked_on_rxend <= register2_q_net_x6;

  constant_x0: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant_op_net
    );

  logical2: entity work.logical_3640e86e6c
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => phy_rx_end_ind_net_x4,
      d1(0) => phy_rx_fcs_good_ind_net_x2,
      d2(0) => b_1_y_net_x0,
      d3(0) => relational2_op_net,
      y(0) => logical2_y_net_x0
    );

  logical5: entity work.logical_6cb8f0ce02
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical6_y_net,
      d1(0) => register2_q_net_x5,
      d2(0) => register2_q_net_x6,
      y(0) => logical5_y_net
    );

  logical6: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => register2_q_net_x3,
      d1(0) => b_4_y_net,
      y(0) => logical6_y_net
    );

  logical7: entity work.logical_954ee29728
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => phy_rx_end_ind_net_x4,
      d1(0) => b_6_y_net,
      d2(0) => relational2_op_net,
      y(0) => logical7_y_net_x0
    );

  logical8: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x0,
      d1(0) => b_0_y_net_x3,
      y(0) => logical8_y_net_x1
    );

  register2: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x24,
      clk => clk_1_sg_x24,
      d(0) => logical5_y_net,
      en => "1",
      rst => "0",
      q(0) => register2_q_net_x4
    );

  relational2: entity work.relational_ee03197e2c
    port map (
      a => phy_rx_end_rxerror_net_x4,
      b(0) => constant_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational2_op_net
    );

  s_r_latch1_ed73bce593: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x24,
      clk_1 => clk_1_sg_x24,
      r => logical8_y_net_x1,
      s => logical2_y_net_x0,
      q => register2_q_net_x5
    );

  s_r_latch4_40015cb0be: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x24,
      clk_1 => clk_1_sg_x24,
      r => logical8_y_net_x1,
      s => logical7_y_net_x0,
      q => register2_q_net_x6
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/PHY I/O/PHY Tx Ports"

entity phy_tx_ports_entity_f5754ed81f is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    tx_a_param_txantmask: in std_logic_vector(3 downto 0); 
    tx_a_param_txgain_a: in std_logic_vector(5 downto 0); 
    tx_a_param_txgain_b: in std_logic_vector(5 downto 0); 
    tx_a_param_txgain_c: in std_logic_vector(5 downto 0); 
    tx_a_param_txgain_d: in std_logic_vector(5 downto 0); 
    tx_a_phy_start: in std_logic; 
    tx_a_pktbuf: in std_logic_vector(3 downto 0); 
    tx_b_param_txantmask: in std_logic_vector(3 downto 0); 
    tx_b_param_txgain_a: in std_logic_vector(5 downto 0); 
    tx_b_param_txgain_b: in std_logic_vector(5 downto 0); 
    tx_b_param_txgain_c: in std_logic_vector(5 downto 0); 
    tx_b_param_txgain_d: in std_logic_vector(5 downto 0); 
    tx_b_phy_start: in std_logic; 
    tx_b_pktbuf: in std_logic_vector(3 downto 0); 
    register1_x0: out std_logic_vector(3 downto 0); 
    register2_x0: out std_logic_vector(5 downto 0); 
    register4_x0: out std_logic_vector(3 downto 0); 
    register5_x0: out std_logic_vector(5 downto 0); 
    register6_x0: out std_logic_vector(5 downto 0); 
    register7_x0: out std_logic_vector(5 downto 0); 
    register_x1: out std_logic
  );
end phy_tx_ports_entity_f5754ed81f;

architecture structural of phy_tx_ports_entity_f5754ed81f is
  signal ce_1_sg_x25: std_logic;
  signal clk_1_sg_x25: std_logic;
  signal convert1_dout_net_x1: std_logic;
  signal convert1_dout_net_x2: std_logic;
  signal logical3_y_net: std_logic;
  signal mux1_y_net: std_logic_vector(5 downto 0);
  signal mux2_y_net: std_logic_vector(3 downto 0);
  signal mux3_y_net: std_logic_vector(5 downto 0);
  signal mux4_y_net: std_logic_vector(5 downto 0);
  signal mux5_y_net: std_logic_vector(5 downto 0);
  signal mux_y_net: std_logic_vector(3 downto 0);
  signal register10_q_net_x1: std_logic_vector(5 downto 0);
  signal register10_q_net_x2: std_logic_vector(5 downto 0);
  signal register1_q_net_x0: std_logic_vector(3 downto 0);
  signal register2_q_net_x2: std_logic_vector(3 downto 0);
  signal register2_q_net_x3: std_logic_vector(3 downto 0);
  signal register2_q_net_x4: std_logic_vector(5 downto 0);
  signal register4_q_net_x0: std_logic_vector(3 downto 0);
  signal register5_q_net_x0: std_logic_vector(5 downto 0);
  signal register6_q_net_x2: std_logic_vector(5 downto 0);
  signal register6_q_net_x3: std_logic_vector(5 downto 0);
  signal register6_q_net_x4: std_logic_vector(5 downto 0);
  signal register7_q_net_x2: std_logic_vector(3 downto 0);
  signal register7_q_net_x3: std_logic_vector(3 downto 0);
  signal register7_q_net_x4: std_logic_vector(5 downto 0);
  signal register8_q_net_x1: std_logic_vector(5 downto 0);
  signal register8_q_net_x2: std_logic_vector(5 downto 0);
  signal register9_q_net_x1: std_logic_vector(5 downto 0);
  signal register9_q_net_x2: std_logic_vector(5 downto 0);
  signal register_q_net_x0: std_logic;

begin
  ce_1_sg_x25 <= ce_1;
  clk_1_sg_x25 <= clk_1;
  register7_q_net_x2 <= tx_a_param_txantmask;
  register6_q_net_x2 <= tx_a_param_txgain_a;
  register8_q_net_x1 <= tx_a_param_txgain_b;
  register9_q_net_x1 <= tx_a_param_txgain_c;
  register10_q_net_x1 <= tx_a_param_txgain_d;
  convert1_dout_net_x1 <= tx_a_phy_start;
  register2_q_net_x2 <= tx_a_pktbuf;
  register7_q_net_x3 <= tx_b_param_txantmask;
  register6_q_net_x3 <= tx_b_param_txgain_a;
  register8_q_net_x2 <= tx_b_param_txgain_b;
  register9_q_net_x2 <= tx_b_param_txgain_c;
  register10_q_net_x2 <= tx_b_param_txgain_d;
  convert1_dout_net_x2 <= tx_b_phy_start;
  register2_q_net_x3 <= tx_b_pktbuf;
  register1_x0 <= register1_q_net_x0;
  register2_x0 <= register2_q_net_x4;
  register4_x0 <= register4_q_net_x0;
  register5_x0 <= register5_q_net_x0;
  register6_x0 <= register6_q_net_x4;
  register7_x0 <= register7_q_net_x4;
  register_x1 <= register_q_net_x0;

  logical3: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => convert1_dout_net_x1,
      d1(0) => convert1_dout_net_x2,
      y(0) => logical3_y_net
    );

  mux: entity work.mux_f9c0f11a18
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0 => register2_q_net_x2,
      d1 => register2_q_net_x3,
      sel(0) => convert1_dout_net_x2,
      y => mux_y_net
    );

  mux1: entity work.mux_ac2c510b5b
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0 => register6_q_net_x2,
      d1 => register6_q_net_x3,
      sel(0) => convert1_dout_net_x2,
      y => mux1_y_net
    );

  mux2: entity work.mux_f9c0f11a18
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0 => register7_q_net_x2,
      d1 => register7_q_net_x3,
      sel(0) => convert1_dout_net_x2,
      y => mux2_y_net
    );

  mux3: entity work.mux_ac2c510b5b
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0 => register8_q_net_x1,
      d1 => register8_q_net_x2,
      sel(0) => convert1_dout_net_x2,
      y => mux3_y_net
    );

  mux4: entity work.mux_ac2c510b5b
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0 => register9_q_net_x1,
      d1 => register9_q_net_x2,
      sel(0) => convert1_dout_net_x2,
      y => mux4_y_net
    );

  mux5: entity work.mux_ac2c510b5b
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0 => register10_q_net_x1,
      d1 => register10_q_net_x2,
      sel(0) => convert1_dout_net_x2,
      y => mux5_y_net
    );

  register1: entity work.xlregister
    generic map (
      d_width => 4,
      init_value => b"0000"
    )
    port map (
      ce => ce_1_sg_x25,
      clk => clk_1_sg_x25,
      d => mux_y_net,
      en => "1",
      rst => "0",
      q => register1_q_net_x0
    );

  register2: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x25,
      clk => clk_1_sg_x25,
      d => mux1_y_net,
      en => "1",
      rst => "0",
      q => register2_q_net_x4
    );

  register4: entity work.xlregister
    generic map (
      d_width => 4,
      init_value => b"0000"
    )
    port map (
      ce => ce_1_sg_x25,
      clk => clk_1_sg_x25,
      d => mux2_y_net,
      en => "1",
      rst => "0",
      q => register4_q_net_x0
    );

  register5: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x25,
      clk => clk_1_sg_x25,
      d => mux3_y_net,
      en => "1",
      rst => "0",
      q => register5_q_net_x0
    );

  register6: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x25,
      clk => clk_1_sg_x25,
      d => mux4_y_net,
      en => "1",
      rst => "0",
      q => register6_q_net_x4
    );

  register7: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x25,
      clk => clk_1_sg_x25,
      d => mux5_y_net,
      en => "1",
      rst => "0",
      q => register7_q_net_x4
    );

  register_x0: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x25,
      clk => clk_1_sg_x25,
      d(0) => logical3_y_net,
      en => "1",
      rst => "0",
      q(0) => register_q_net_x0
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/PHY I/O"

entity o_entity_720fb5e965 is
  port (
    b_1: in std_logic; 
    b_4: in std_logic; 
    b_6: in std_logic; 
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    convert1: in std_logic; 
    convert1_x0: in std_logic; 
    global_reset: in std_logic; 
    logical1_x0: in std_logic; 
    phy_rx_data_done_ind: in std_logic; 
    phy_rx_end_ind: in std_logic; 
    phy_rx_end_rxerror: in std_logic_vector(3 downto 0); 
    phy_rx_fcs_good_ind: in std_logic; 
    phy_rx_start_ind: in std_logic; 
    phy_tx_end_confirm: in std_logic; 
    phy_tx_start_confirm: in std_logic; 
    register10: in std_logic_vector(5 downto 0); 
    register10_x0: in std_logic_vector(5 downto 0); 
    register2: in std_logic_vector(3 downto 0); 
    register2_x0: in std_logic_vector(3 downto 0); 
    register6: in std_logic_vector(5 downto 0); 
    register6_x0: in std_logic_vector(5 downto 0); 
    register7: in std_logic_vector(3 downto 0); 
    register7_x0: in std_logic_vector(3 downto 0); 
    register8: in std_logic_vector(5 downto 0); 
    register8_x0: in std_logic_vector(5 downto 0); 
    register9: in std_logic_vector(5 downto 0); 
    register9_x0: in std_logic_vector(5 downto 0); 
    phy_rx_ports: out std_logic; 
    phy_rx_ports_x0: out std_logic; 
    phy_rx_ports_x1: out std_logic; 
    phy_tx_ports: out std_logic; 
    phy_tx_ports_x0: out std_logic_vector(3 downto 0); 
    phy_tx_ports_x1: out std_logic_vector(5 downto 0); 
    phy_tx_ports_x2: out std_logic_vector(3 downto 0); 
    phy_tx_ports_x3: out std_logic_vector(5 downto 0); 
    phy_tx_ports_x4: out std_logic_vector(5 downto 0); 
    phy_tx_ports_x5: out std_logic_vector(5 downto 0); 
    status_rx_fcs_good: out std_logic; 
    status_rx_phy_active: out std_logic; 
    status_tx_phy_active: out std_logic
  );
end o_entity_720fb5e965;

architecture structural of o_entity_720fb5e965 is
  signal b_0_y_net_x4: std_logic;
  signal b_1_y_net_x1: std_logic;
  signal b_4_y_net_x0: std_logic;
  signal b_6_y_net_x0: std_logic;
  signal ce_1_sg_x28: std_logic;
  signal clk_1_sg_x28: std_logic;
  signal convert1_dout_net_x3: std_logic;
  signal convert1_dout_net_x4: std_logic;
  signal delay_q_net_x0: std_logic;
  signal logical1_y_net_x0: std_logic;
  signal logical1_y_net_x2: std_logic;
  signal logical4_y_net_x0: std_logic;
  signal phy_rx_data_done_ind_net_x0: std_logic;
  signal phy_rx_end_ind_net_x5: std_logic;
  signal phy_rx_end_rxerror_net_x5: std_logic_vector(3 downto 0);
  signal phy_rx_fcs_good_ind_net_x3: std_logic;
  signal phy_rx_start_ind_net_x4: std_logic;
  signal phy_tx_done_net_x0: std_logic;
  signal phy_tx_started_net_x1: std_logic;
  signal register10_q_net_x3: std_logic_vector(5 downto 0);
  signal register10_q_net_x4: std_logic_vector(5 downto 0);
  signal register1_q_net_x1: std_logic_vector(3 downto 0);
  signal register2_q_net_x0: std_logic;
  signal register2_q_net_x10: std_logic_vector(3 downto 0);
  signal register2_q_net_x11: std_logic;
  signal register2_q_net_x12: std_logic;
  signal register2_q_net_x13: std_logic;
  signal register2_q_net_x14: std_logic_vector(5 downto 0);
  signal register2_q_net_x15: std_logic;
  signal register2_q_net_x9: std_logic_vector(3 downto 0);
  signal register3_q_net_x2: std_logic;
  signal register4_q_net_x1: std_logic_vector(3 downto 0);
  signal register5_q_net_x1: std_logic_vector(5 downto 0);
  signal register6_q_net_x5: std_logic_vector(5 downto 0);
  signal register6_q_net_x6: std_logic_vector(5 downto 0);
  signal register6_q_net_x7: std_logic_vector(5 downto 0);
  signal register7_q_net_x5: std_logic_vector(3 downto 0);
  signal register7_q_net_x6: std_logic_vector(3 downto 0);
  signal register7_q_net_x7: std_logic_vector(5 downto 0);
  signal register8_q_net_x3: std_logic_vector(5 downto 0);
  signal register8_q_net_x4: std_logic_vector(5 downto 0);
  signal register9_q_net_x3: std_logic_vector(5 downto 0);
  signal register9_q_net_x4: std_logic_vector(5 downto 0);
  signal register_q_net_x1: std_logic;

begin
  b_1_y_net_x1 <= b_1;
  b_4_y_net_x0 <= b_4;
  b_6_y_net_x0 <= b_6;
  ce_1_sg_x28 <= ce_1;
  clk_1_sg_x28 <= clk_1;
  convert1_dout_net_x3 <= convert1;
  convert1_dout_net_x4 <= convert1_x0;
  b_0_y_net_x4 <= global_reset;
  logical1_y_net_x2 <= logical1_x0;
  phy_rx_data_done_ind_net_x0 <= phy_rx_data_done_ind;
  phy_rx_end_ind_net_x5 <= phy_rx_end_ind;
  phy_rx_end_rxerror_net_x5 <= phy_rx_end_rxerror;
  phy_rx_fcs_good_ind_net_x3 <= phy_rx_fcs_good_ind;
  phy_rx_start_ind_net_x4 <= phy_rx_start_ind;
  phy_tx_done_net_x0 <= phy_tx_end_confirm;
  phy_tx_started_net_x1 <= phy_tx_start_confirm;
  register10_q_net_x3 <= register10;
  register10_q_net_x4 <= register10_x0;
  register2_q_net_x9 <= register2;
  register2_q_net_x10 <= register2_x0;
  register6_q_net_x5 <= register6;
  register6_q_net_x6 <= register6_x0;
  register7_q_net_x5 <= register7;
  register7_q_net_x6 <= register7_x0;
  register8_q_net_x3 <= register8;
  register8_q_net_x4 <= register8_x0;
  register9_q_net_x3 <= register9;
  register9_q_net_x4 <= register9_x0;
  phy_rx_ports <= register2_q_net_x11;
  phy_rx_ports_x0 <= register2_q_net_x12;
  phy_rx_ports_x1 <= register2_q_net_x13;
  phy_tx_ports <= register_q_net_x1;
  phy_tx_ports_x0 <= register1_q_net_x1;
  phy_tx_ports_x1 <= register2_q_net_x14;
  phy_tx_ports_x2 <= register4_q_net_x1;
  phy_tx_ports_x3 <= register5_q_net_x1;
  phy_tx_ports_x4 <= register6_q_net_x7;
  phy_tx_ports_x5 <= register7_q_net_x7;
  status_rx_fcs_good <= register3_q_net_x2;
  status_rx_phy_active <= delay_q_net_x0;
  status_tx_phy_active <= register2_q_net_x15;

  delay: entity work.xldelay
    generic map (
      latency => 3,
      reg_retiming => 0,
      reset => 0,
      width => 1
    )
    port map (
      ce => ce_1_sg_x28,
      clk => clk_1_sg_x28,
      d(0) => register2_q_net_x0,
      en => '1',
      rst => '1',
      q(0) => delay_q_net_x0
    );

  logical1: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => phy_tx_done_net_x0,
      d1(0) => b_0_y_net_x4,
      y(0) => logical1_y_net_x0
    );

  logical4: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => phy_rx_end_ind_net_x5,
      d1(0) => b_0_y_net_x4,
      y(0) => logical4_y_net_x0
    );

  phy_rx_ports_b0683ed47c: entity work.phy_rx_ports_entity_b0683ed47c
    port map (
      ce_1 => ce_1_sg_x28,
      clk_1 => clk_1_sg_x28,
      global_reset => b_0_y_net_x4,
      phy_rx_end_ind => phy_rx_end_ind_net_x5,
      phy_rx_end_rxerror => phy_rx_end_rxerror_net_x5,
      phy_rx_fcs_good_ind => phy_rx_fcs_good_ind_net_x3,
      reg_block_rx_clear => logical1_y_net_x2,
      reg_block_rx_on_fcs_good => b_1_y_net_x1,
      reg_block_rx_on_tx => b_4_y_net_x0,
      reg_block_rx_on_valid_rxend => b_6_y_net_x0,
      status_tx_phy_active => register2_q_net_x15,
      register2_x0 => register2_q_net_x11,
      status_blocked_on_good_fcs => register2_q_net_x12,
      status_blocked_on_rxend => register2_q_net_x13
    );

  phy_tx_ports_f5754ed81f: entity work.phy_tx_ports_entity_f5754ed81f
    port map (
      ce_1 => ce_1_sg_x28,
      clk_1 => clk_1_sg_x28,
      tx_a_param_txantmask => register7_q_net_x5,
      tx_a_param_txgain_a => register6_q_net_x5,
      tx_a_param_txgain_b => register8_q_net_x3,
      tx_a_param_txgain_c => register9_q_net_x3,
      tx_a_param_txgain_d => register10_q_net_x3,
      tx_a_phy_start => convert1_dout_net_x3,
      tx_a_pktbuf => register2_q_net_x9,
      tx_b_param_txantmask => register7_q_net_x6,
      tx_b_param_txgain_a => register6_q_net_x6,
      tx_b_param_txgain_b => register8_q_net_x4,
      tx_b_param_txgain_c => register9_q_net_x4,
      tx_b_param_txgain_d => register10_q_net_x4,
      tx_b_phy_start => convert1_dout_net_x4,
      tx_b_pktbuf => register2_q_net_x10,
      register1_x0 => register1_q_net_x1,
      register2_x0 => register2_q_net_x14,
      register4_x0 => register4_q_net_x1,
      register5_x0 => register5_q_net_x1,
      register6_x0 => register6_q_net_x7,
      register7_x0 => register7_q_net_x7,
      register_x1 => register_q_net_x1
    );

  register3: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x28,
      clk => clk_1_sg_x28,
      d(0) => phy_rx_fcs_good_ind_net_x3,
      en(0) => phy_rx_data_done_ind_net_x0,
      rst(0) => phy_rx_start_ind_net_x4,
      q(0) => register3_q_net_x2
    );

  s_r_latch2_d48768d4c6: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x28,
      clk_1 => clk_1_sg_x28,
      r => logical1_y_net_x0,
      s => phy_tx_started_net_x1,
      q => register2_q_net_x15
    );

  s_r_latch3_db846e804a: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x28,
      clk_1 => clk_1_sg_x28,
      r => logical4_y_net_x0,
      s => phy_rx_start_ind_net_x4,
      q => register2_q_net_x0
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Post Tx/Rx Timers"

entity rx_timers_entity_5b2badea90 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    global_reset: in std_logic; 
    phy_rx_end_ind: in std_logic; 
    phy_rx_end_rxerror: in std_logic_vector(3 downto 0); 
    phy_tx_end_confirm: in std_logic; 
    reg_postrx_timer1_countto: in std_logic_vector(18 downto 0); 
    reg_postrx_timer1_en: in std_logic; 
    reg_postrx_timer2_countto: in std_logic_vector(18 downto 0); 
    reg_postrx_timer2_en: in std_logic; 
    reg_posttx_timer1_countto: in std_logic_vector(18 downto 0); 
    reg_posttx_timer1_en: in std_logic; 
    reg_posttx_timer2_countto: in std_logic_vector(18 downto 0); 
    reg_posttx_timer2_en: in std_logic; 
    postrx_timer_1_x0: out std_logic; 
    postrx_timer_2_x0: out std_logic; 
    posttx_timer_1_x0: out std_logic; 
    posttx_timer_2_x0: out std_logic; 
    status_postrx_timer1_running: out std_logic; 
    status_postrx_timer2_running: out std_logic; 
    status_posttx_timer1_running: out std_logic; 
    status_posttx_timer2_running: out std_logic
  );
end rx_timers_entity_5b2badea90;

architecture structural of rx_timers_entity_5b2badea90 is
  signal b_0_y_net_x5: std_logic;
  signal ce_1_sg_x35: std_logic;
  signal clk_1_sg_x35: std_logic;
  signal concat1_y_net_x3: std_logic_vector(18 downto 0);
  signal concat1_y_net_x4: std_logic_vector(18 downto 0);
  signal concat1_y_net_x5: std_logic_vector(18 downto 0);
  signal concat1_y_net_x6: std_logic_vector(18 downto 0);
  signal constant2_op_net: std_logic;
  signal inverter1_op_net: std_logic;
  signal inverter2_op_net: std_logic;
  signal inverter3_op_net: std_logic;
  signal inverter4_op_net: std_logic;
  signal inverter5_op_net: std_logic;
  signal inverter6_op_net: std_logic;
  signal inverter7_op_net: std_logic;
  signal inverter8_op_net: std_logic;
  signal logical10_y_net_x0: std_logic;
  signal logical1_y_net_x0: std_logic;
  signal logical1_y_net_x1: std_logic;
  signal logical1_y_net_x2: std_logic;
  signal logical2_y_net_x0: std_logic;
  signal logical3_y_net_x0: std_logic;
  signal logical4_y_net_x0: std_logic;
  signal logical5_y_net_x0: std_logic;
  signal logical6_y_net_x0: std_logic;
  signal logical7_y_net_x0: std_logic;
  signal logical8_y_net_x0: std_logic;
  signal phy_rx_end_ind_net_x6: std_logic;
  signal phy_rx_end_rxerror_net_x6: std_logic_vector(3 downto 0);
  signal phy_tx_done_net_x2: std_logic;
  signal postrx_timer_1_op_net: std_logic_vector(18 downto 0);
  signal postrx_timer_2_op_net: std_logic_vector(18 downto 0);
  signal posttx_timer_1_op_net: std_logic_vector(18 downto 0);
  signal posttx_timer_2_op_net: std_logic_vector(18 downto 0);
  signal register11_q_net_x0: std_logic;
  signal register14_q_net_x0: std_logic;
  signal register1_q_net_x0: std_logic;
  signal register2_q_net_x4: std_logic;
  signal register2_q_net_x5: std_logic;
  signal register2_q_net_x6: std_logic;
  signal register2_q_net_x7: std_logic;
  signal register2_q_net_x8: std_logic;
  signal register66_q_net_x0: std_logic;
  signal register67_q_net_x0: std_logic;
  signal register8_q_net_x0: std_logic;
  signal register9_q_net_x0: std_logic;
  signal relational1_op_net: std_logic;
  signal relational2_op_net: std_logic;
  signal relational4_op_net: std_logic;
  signal relational7_op_net: std_logic;
  signal relational8_op_net: std_logic;

begin
  ce_1_sg_x35 <= ce_1;
  clk_1_sg_x35 <= clk_1;
  b_0_y_net_x5 <= global_reset;
  phy_rx_end_ind_net_x6 <= phy_rx_end_ind;
  phy_rx_end_rxerror_net_x6 <= phy_rx_end_rxerror;
  phy_tx_done_net_x2 <= phy_tx_end_confirm;
  concat1_y_net_x6 <= reg_postrx_timer1_countto;
  register66_q_net_x0 <= reg_postrx_timer1_en;
  concat1_y_net_x4 <= reg_postrx_timer2_countto;
  register67_q_net_x0 <= reg_postrx_timer2_en;
  concat1_y_net_x5 <= reg_posttx_timer1_countto;
  register11_q_net_x0 <= reg_posttx_timer1_en;
  concat1_y_net_x3 <= reg_posttx_timer2_countto;
  register14_q_net_x0 <= reg_posttx_timer2_en;
  postrx_timer_1_x0 <= register8_q_net_x0;
  postrx_timer_2_x0 <= register9_q_net_x0;
  posttx_timer_1_x0 <= register1_q_net_x0;
  posttx_timer_2_x0 <= register2_q_net_x4;
  status_postrx_timer1_running <= register2_q_net_x7;
  status_postrx_timer2_running <= register2_q_net_x8;
  status_posttx_timer1_running <= register2_q_net_x5;
  status_posttx_timer2_running <= register2_q_net_x6;

  constant2: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant2_op_net
    );

  inverter1: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      ip(0) => register2_q_net_x7,
      op(0) => inverter1_op_net
    );

  inverter2: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      ip(0) => register2_q_net_x8,
      op(0) => inverter2_op_net
    );

  inverter3: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      ip(0) => register2_q_net_x5,
      op(0) => inverter3_op_net
    );

  inverter4: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      ip(0) => register2_q_net_x6,
      op(0) => inverter4_op_net
    );

  inverter5: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      ip(0) => register66_q_net_x0,
      op(0) => inverter5_op_net
    );

  inverter6: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      ip(0) => register67_q_net_x0,
      op(0) => inverter6_op_net
    );

  inverter7: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      ip(0) => register11_q_net_x0,
      op(0) => inverter7_op_net
    );

  inverter8: entity work.inverter_e5b38cca3b
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      ip(0) => register14_q_net_x0,
      op(0) => inverter8_op_net
    );

  logical1: entity work.logical_6cb8f0ce02
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational1_op_net,
      d1(0) => b_0_y_net_x5,
      d2(0) => inverter7_op_net,
      y(0) => logical1_y_net_x0
    );

  logical10: entity work.logical_6cb8f0ce02
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational7_op_net,
      d1(0) => b_0_y_net_x5,
      d2(0) => inverter5_op_net,
      y(0) => logical10_y_net_x0
    );

  logical2: entity work.logical_6cb8f0ce02
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational2_op_net,
      d1(0) => b_0_y_net_x5,
      d2(0) => inverter8_op_net,
      y(0) => logical2_y_net_x0
    );

  logical3: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x1,
      d1(0) => register11_q_net_x0,
      y(0) => logical3_y_net_x0
    );

  logical4: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x1,
      d1(0) => register14_q_net_x0,
      y(0) => logical4_y_net_x0
    );

  logical5: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x2,
      d1(0) => register67_q_net_x0,
      y(0) => logical5_y_net_x0
    );

  logical6: entity work.logical_6cb8f0ce02
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => relational8_op_net,
      d1(0) => b_0_y_net_x5,
      d2(0) => inverter6_op_net,
      y(0) => logical6_y_net_x0
    );

  logical7: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => phy_rx_end_ind_net_x6,
      d1(0) => relational4_op_net,
      y(0) => logical7_y_net_x0
    );

  logical8: entity work.logical_80f90b97d0
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x2,
      d1(0) => register66_q_net_x0,
      y(0) => logical8_y_net_x0
    );

  posedge1_f3bc99a300: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x35,
      clk_1 => clk_1_sg_x35,
      d => phy_tx_done_net_x2,
      q => logical1_y_net_x1
    );

  posedge3_fb1f7a7bd8: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x35,
      clk_1 => clk_1_sg_x35,
      d => logical7_y_net_x0,
      q => logical1_y_net_x2
    );

  postrx_timer_1: entity work.xlcounter_free_wlan_mac_hw
    generic map (
      core_name0 => "cntr_11_0_e1525560b82138e7",
      op_arith => xlUnsigned,
      op_width => 19
    )
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      en(0) => register2_q_net_x7,
      rst(0) => inverter1_op_net,
      op => postrx_timer_1_op_net
    );

  postrx_timer_2: entity work.xlcounter_free_wlan_mac_hw
    generic map (
      core_name0 => "cntr_11_0_e1525560b82138e7",
      op_arith => xlUnsigned,
      op_width => 19
    )
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      en(0) => register2_q_net_x8,
      rst(0) => inverter2_op_net,
      op => postrx_timer_2_op_net
    );

  posttx_timer_1: entity work.xlcounter_free_wlan_mac_hw
    generic map (
      core_name0 => "cntr_11_0_e1525560b82138e7",
      op_arith => xlUnsigned,
      op_width => 19
    )
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      en(0) => register2_q_net_x5,
      rst(0) => inverter3_op_net,
      op => posttx_timer_1_op_net
    );

  posttx_timer_2: entity work.xlcounter_free_wlan_mac_hw
    generic map (
      core_name0 => "cntr_11_0_e1525560b82138e7",
      op_arith => xlUnsigned,
      op_width => 19
    )
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      clr => '0',
      en(0) => register2_q_net_x6,
      rst(0) => inverter4_op_net,
      op => posttx_timer_2_op_net
    );

  register1: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      d(0) => relational1_op_net,
      en => "1",
      rst => "0",
      q(0) => register1_q_net_x0
    );

  register2: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      d(0) => relational2_op_net,
      en => "1",
      rst => "0",
      q(0) => register2_q_net_x4
    );

  register8: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      d(0) => relational7_op_net,
      en => "1",
      rst => "0",
      q(0) => register8_q_net_x0
    );

  register9: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x35,
      clk => clk_1_sg_x35,
      d(0) => relational8_op_net,
      en => "1",
      rst => "0",
      q(0) => register9_q_net_x0
    );

  relational1: entity work.relational_f3394f23a6
    port map (
      a => posttx_timer_1_op_net,
      b => concat1_y_net_x5,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational1_op_net
    );

  relational2: entity work.relational_f3394f23a6
    port map (
      a => posttx_timer_2_op_net,
      b => concat1_y_net_x3,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational2_op_net
    );

  relational4: entity work.relational_ee03197e2c
    port map (
      a => phy_rx_end_rxerror_net_x6,
      b(0) => constant2_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational4_op_net
    );

  relational7: entity work.relational_f3394f23a6
    port map (
      a => postrx_timer_1_op_net,
      b => concat1_y_net_x6,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational7_op_net
    );

  relational8: entity work.relational_f3394f23a6
    port map (
      a => postrx_timer_2_op_net,
      b => concat1_y_net_x4,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational8_op_net
    );

  s_r_latch1_692013368a: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x35,
      clk_1 => clk_1_sg_x35,
      r => logical1_y_net_x0,
      s => logical3_y_net_x0,
      q => register2_q_net_x5
    );

  s_r_latch2_0759ae5c44: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x35,
      clk_1 => clk_1_sg_x35,
      r => logical2_y_net_x0,
      s => logical4_y_net_x0,
      q => register2_q_net_x6
    );

  s_r_latch3_51c63448e7: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x35,
      clk_1 => clk_1_sg_x35,
      r => logical10_y_net_x0,
      s => logical8_y_net_x0,
      q => register2_q_net_x7
    );

  s_r_latch4_a26bcc7759: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x35,
      clk_1 => clk_1_sg_x35,
      r => logical6_y_net_x0,
      s => logical5_y_net_x0,
      q => register2_q_net_x8
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Registers/Ctrl Bits"

entity ctrl_bits_entity_dfa8c81886 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    x32b: in std_logic_vector(31 downto 0); 
    global_reset: out std_logic; 
    reg_block_rx_clear: out std_logic; 
    reg_block_rx_on_fcs_good: out std_logic; 
    reg_block_rx_on_tx: out std_logic; 
    reg_block_rx_on_valid_rxend: out std_logic; 
    reg_cca_ignore_nav: out std_logic; 
    reg_cca_ignore_phy_cs: out std_logic; 
    reg_cca_ignore_txbusy: out std_logic; 
    reg_disable_nav: out std_logic; 
    reg_force_reset_backoff: out std_logic; 
    reg_force_reset_nav: out std_logic; 
    reg_update_timestamp: out std_logic
  );
end ctrl_bits_entity_dfa8c81886;

architecture structural of ctrl_bits_entity_dfa8c81886 is
  signal b_0_y_net_x6: std_logic;
  signal b_10_y_net_x0: std_logic;
  signal b_11_y_net_x0: std_logic;
  signal b_1_y_net_x2: std_logic;
  signal b_2_y_net: std_logic;
  signal b_3_y_net_x0: std_logic;
  signal b_4_y_net_x1: std_logic;
  signal b_5_y_net_x1: std_logic;
  signal b_6_y_net_x1: std_logic;
  signal b_7_y_net_x0: std_logic;
  signal b_8_y_net_x0: std_logic;
  signal b_9_y_net_x0: std_logic;
  signal ce_1_sg_x37: std_logic;
  signal clk_1_sg_x37: std_logic;
  signal logical1_y_net_x4: std_logic;
  signal register36_q_net_x0: std_logic_vector(31 downto 0);

begin
  ce_1_sg_x37 <= ce_1;
  clk_1_sg_x37 <= clk_1;
  register36_q_net_x0 <= x32b;
  global_reset <= b_0_y_net_x6;
  reg_block_rx_clear <= logical1_y_net_x4;
  reg_block_rx_on_fcs_good <= b_1_y_net_x2;
  reg_block_rx_on_tx <= b_4_y_net_x1;
  reg_block_rx_on_valid_rxend <= b_6_y_net_x1;
  reg_cca_ignore_nav <= b_9_y_net_x0;
  reg_cca_ignore_phy_cs <= b_7_y_net_x0;
  reg_cca_ignore_txbusy <= b_8_y_net_x0;
  reg_disable_nav <= b_3_y_net_x0;
  reg_force_reset_backoff <= b_11_y_net_x0;
  reg_force_reset_nav <= b_10_y_net_x0;
  reg_update_timestamp <= b_5_y_net_x1;

  b_0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 0,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_0_y_net_x6
    );

  b_1: entity work.xlslice
    generic map (
      new_lsb => 1,
      new_msb => 1,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_1_y_net_x2
    );

  b_10: entity work.xlslice
    generic map (
      new_lsb => 10,
      new_msb => 10,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_10_y_net_x0
    );

  b_11: entity work.xlslice
    generic map (
      new_lsb => 11,
      new_msb => 11,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_11_y_net_x0
    );

  b_2: entity work.xlslice
    generic map (
      new_lsb => 2,
      new_msb => 2,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_2_y_net
    );

  b_3: entity work.xlslice
    generic map (
      new_lsb => 3,
      new_msb => 3,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_3_y_net_x0
    );

  b_4: entity work.xlslice
    generic map (
      new_lsb => 4,
      new_msb => 4,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_4_y_net_x1
    );

  b_5: entity work.xlslice
    generic map (
      new_lsb => 5,
      new_msb => 5,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_5_y_net_x1
    );

  b_6: entity work.xlslice
    generic map (
      new_lsb => 6,
      new_msb => 6,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_6_y_net_x1
    );

  b_7: entity work.xlslice
    generic map (
      new_lsb => 7,
      new_msb => 7,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_7_y_net_x0
    );

  b_8: entity work.xlslice
    generic map (
      new_lsb => 8,
      new_msb => 8,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_8_y_net_x0
    );

  b_9: entity work.xlslice
    generic map (
      new_lsb => 9,
      new_msb => 9,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => register36_q_net_x0,
      y(0) => b_9_y_net_x0
    );

  posedge1_d5e865820a: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x37,
      clk_1 => clk_1_sg_x37,
      d => b_2_y_net,
      q => logical1_y_net_x4
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Registers/Status Register"

entity status_register_entity_1c7c355a6a is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    mac_nav_busy: in std_logic; 
    phy_cca_ind_busy: in std_logic; 
    status_blocked_on_good_fcs: in std_logic; 
    status_blocked_on_rxend: in std_logic; 
    status_nav_addr_match: in std_logic; 
    status_postrx_timer1_running: in std_logic; 
    status_postrx_timer2_running: in std_logic; 
    status_posttx_timer1_running: in std_logic; 
    status_posttx_timer2_running: in std_logic; 
    status_rx_fcs_good: in std_logic; 
    status_rx_phy_active: in std_logic; 
    status_tx_a_done: in std_logic; 
    status_tx_a_pending: in std_logic; 
    status_tx_a_result: in std_logic_vector(1 downto 0); 
    status_tx_a_state: in std_logic_vector(2 downto 0); 
    status_tx_b_done: in std_logic; 
    status_tx_b_pending: in std_logic; 
    status_tx_b_result: in std_logic_vector(1 downto 0); 
    status_tx_b_state: in std_logic_vector(2 downto 0); 
    status_tx_phy_active: in std_logic; 
    constant1_x0: out std_logic; 
    convert1_x0: out std_logic_vector(31 downto 0)
  );
end status_register_entity_1c7c355a6a;

architecture structural of status_register_entity_1c7c355a6a is
  signal ce_1_sg_x39: std_logic;
  signal clk_1_sg_x39: std_logic;
  signal concat_y_net: std_logic_vector(25 downto 0);
  signal constant1_op_net_x0: std_logic;
  signal convert1_dout_net_x0: std_logic_vector(31 downto 0);
  signal delay_q_net_x1: std_logic;
  signal logical3_y_net_x3: std_logic;
  signal mcode_tx_control_a_fsm_state_out_net: std_logic_vector(2 downto 0);
  signal mcode_tx_control_b_fsm_state_out_net: std_logic_vector(2 downto 0);
  signal phy_cca_ind_busy_net_x1: std_logic;
  signal register10_q_net: std_logic;
  signal register1_q_net: std_logic_vector(2 downto 0);
  signal register1_q_net_x2: std_logic_vector(1 downto 0);
  signal register1_q_net_x3: std_logic_vector(1 downto 0);
  signal register2_q_net: std_logic_vector(1 downto 0);
  signal register2_q_net_x19: std_logic;
  signal register2_q_net_x20: std_logic;
  signal register2_q_net_x21: std_logic;
  signal register2_q_net_x22: std_logic;
  signal register2_q_net_x23: std_logic;
  signal register2_q_net_x24: std_logic;
  signal register2_q_net_x25: std_logic;
  signal register2_q_net_x26: std_logic;
  signal register2_q_net_x27: std_logic;
  signal register2_q_net_x28: std_logic;
  signal register2_q_net_x29: std_logic;
  signal register37_q_net: std_logic;
  signal register38_q_net: std_logic;
  signal register39_q_net: std_logic;
  signal register3_q_net_x3: std_logic;
  signal register41_q_net: std_logic;
  signal register42_q_net: std_logic;
  signal register43_q_net: std_logic_vector(2 downto 0);
  signal register44_q_net: std_logic_vector(1 downto 0);
  signal register45_q_net: std_logic;
  signal register46_q_net: std_logic;
  signal register47_q_net: std_logic;
  signal register48_q_net: std_logic;
  signal register4_q_net: std_logic;
  signal register4_q_net_x3: std_logic;
  signal register5_q_net: std_logic;
  signal register6_q_net: std_logic;
  signal register7_q_net: std_logic;
  signal register8_q_net: std_logic;
  signal register9_q_net: std_logic;
  signal register_q_net: std_logic_vector(25 downto 0);

begin
  ce_1_sg_x39 <= ce_1;
  clk_1_sg_x39 <= clk_1;
  logical3_y_net_x3 <= mac_nav_busy;
  phy_cca_ind_busy_net_x1 <= phy_cca_ind_busy;
  register2_q_net_x19 <= status_blocked_on_good_fcs;
  register2_q_net_x20 <= status_blocked_on_rxend;
  register4_q_net_x3 <= status_nav_addr_match;
  register2_q_net_x24 <= status_postrx_timer1_running;
  register2_q_net_x25 <= status_postrx_timer2_running;
  register2_q_net_x22 <= status_posttx_timer1_running;
  register2_q_net_x23 <= status_posttx_timer2_running;
  register3_q_net_x3 <= status_rx_fcs_good;
  delay_q_net_x1 <= status_rx_phy_active;
  register2_q_net_x27 <= status_tx_a_done;
  register2_q_net_x26 <= status_tx_a_pending;
  register1_q_net_x2 <= status_tx_a_result;
  mcode_tx_control_a_fsm_state_out_net <= status_tx_a_state;
  register2_q_net_x29 <= status_tx_b_done;
  register2_q_net_x28 <= status_tx_b_pending;
  register1_q_net_x3 <= status_tx_b_result;
  mcode_tx_control_b_fsm_state_out_net <= status_tx_b_state;
  register2_q_net_x21 <= status_tx_phy_active;
  constant1_x0 <= constant1_op_net_x0;
  convert1_x0 <= convert1_dout_net_x0;

  concat: entity work.concat_463b9166a5
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      in0(0) => register10_q_net,
      in1(0) => register9_q_net,
      in10(0) => register45_q_net,
      in11(0) => register46_q_net,
      in12 => register1_q_net,
      in13 => register2_q_net,
      in14(0) => register4_q_net,
      in15(0) => register5_q_net,
      in16 => register43_q_net,
      in17 => register44_q_net,
      in18(0) => register47_q_net,
      in19(0) => register48_q_net,
      in2(0) => register8_q_net,
      in3(0) => register7_q_net,
      in4(0) => register6_q_net,
      in5(0) => register37_q_net,
      in6(0) => register38_q_net,
      in7(0) => register39_q_net,
      in8(0) => register41_q_net,
      in9(0) => register42_q_net,
      y => concat_y_net
    );

  constant1: entity work.constant_6293007044
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant1_op_net_x0
    );

  convert1: entity work.xlconvert
    generic map (
      bool_conversion => 0,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 26,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 32,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      clr => '0',
      din => register_q_net,
      en => "1",
      dout => convert1_dout_net_x0
    );

  register1: entity work.xlregister
    generic map (
      d_width => 3,
      init_value => b"000"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d => mcode_tx_control_b_fsm_state_out_net,
      en => "1",
      rst => "0",
      q => register1_q_net
    );

  register10: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register2_q_net_x24,
      en => "1",
      rst => "0",
      q(0) => register10_q_net
    );

  register2: entity work.xlregister
    generic map (
      d_width => 2,
      init_value => b"00"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d => register1_q_net_x3,
      en => "1",
      rst => "0",
      q => register2_q_net
    );

  register37: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register2_q_net_x20,
      en => "1",
      rst => "0",
      q(0) => register37_q_net
    );

  register38: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register2_q_net_x19,
      en => "1",
      rst => "0",
      q(0) => register38_q_net
    );

  register39: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register3_q_net_x3,
      en => "1",
      rst => "0",
      q(0) => register39_q_net
    );

  register4: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register2_q_net_x29,
      en => "1",
      rst => "0",
      q(0) => register4_q_net
    );

  register41: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => phy_cca_ind_busy_net_x1,
      en => "1",
      rst => "0",
      q(0) => register41_q_net
    );

  register42: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => logical3_y_net_x3,
      en => "1",
      rst => "0",
      q(0) => register42_q_net
    );

  register43: entity work.xlregister
    generic map (
      d_width => 3,
      init_value => b"000"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d => mcode_tx_control_a_fsm_state_out_net,
      en => "1",
      rst => "0",
      q => register43_q_net
    );

  register44: entity work.xlregister
    generic map (
      d_width => 2,
      init_value => b"00"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d => register1_q_net_x2,
      en => "1",
      rst => "0",
      q => register44_q_net
    );

  register45: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => delay_q_net_x1,
      en => "1",
      rst => "0",
      q(0) => register45_q_net
    );

  register46: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register2_q_net_x21,
      en => "1",
      rst => "0",
      q(0) => register46_q_net
    );

  register47: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register2_q_net_x27,
      en => "1",
      rst => "0",
      q(0) => register47_q_net
    );

  register48: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register2_q_net_x26,
      en => "1",
      rst => "0",
      q(0) => register48_q_net
    );

  register5: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register2_q_net_x28,
      en => "1",
      rst => "0",
      q(0) => register5_q_net
    );

  register6: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register4_q_net_x3,
      en => "1",
      rst => "0",
      q(0) => register6_q_net
    );

  register7: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register2_q_net_x23,
      en => "1",
      rst => "0",
      q(0) => register7_q_net
    );

  register8: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register2_q_net_x22,
      en => "1",
      rst => "0",
      q(0) => register8_q_net
    );

  register9: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d(0) => register2_q_net_x25,
      en => "1",
      rst => "0",
      q(0) => register9_q_net
    );

  register_x0: entity work.xlregister
    generic map (
      d_width => 26,
      init_value => b"00000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x39,
      clk => clk_1_sg_x39,
      d => concat_y_net,
      en => "1",
      rst => "0",
      q => register_q_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Registers/Timestamp Regs & IO"

entity \timestamp_regs___io_entity_feb7327f6b\ is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    from_register10: in std_logic_vector(31 downto 0); 
    from_register11: in std_logic_vector(31 downto 0); 
    from_register13: in std_logic_vector(31 downto 0); 
    microsecond_timestamp: in std_logic_vector(63 downto 0); 
    phy_rx_start_ind: in std_logic; 
    phy_tx_start_confirm: in std_logic; 
    constant5_x0: out std_logic; 
    constant6_x0: out std_logic; 
    convert5_x0: out std_logic; 
    reg_set_timestamp_lsb: out std_logic_vector(31 downto 0); 
    reg_set_timestamp_msb: out std_logic_vector(31 downto 0); 
    register15_x0: out std_logic; 
    register26_x0: out std_logic_vector(31 downto 0); 
    register55_x0: out std_logic_vector(31 downto 0); 
    x32lsb1_x0: out std_logic_vector(31 downto 0); 
    x32lsb2_x0: out std_logic_vector(31 downto 0); 
    x32lsb_x1: out std_logic_vector(31 downto 0); 
    x32msb1_x0: out std_logic_vector(31 downto 0); 
    x32msb2_x0: out std_logic_vector(31 downto 0); 
    x32msb_x1: out std_logic_vector(31 downto 0)
  );
end \timestamp_regs___io_entity_feb7327f6b\;

architecture structural of \timestamp_regs___io_entity_feb7327f6b\ is
  signal addsub_s_net: std_logic_vector(63 downto 0);
  signal ce_1_sg_x42: std_logic;
  signal clk_1_sg_x42: std_logic;
  signal constant5_op_net_x0: std_logic;
  signal constant6_op_net_x0: std_logic;
  signal convert5_dout_net_x0: std_logic;
  signal convert7_dout_net_x0: std_logic;
  signal delay_q_net: std_logic;
  signal from_register10_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register11_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register13_data_out_net_x0: std_logic_vector(31 downto 0);
  signal logical1_y_net_x0: std_logic;
  signal logical1_y_net_x1: std_logic;
  signal microsecond_counter_op_net_x1: std_logic_vector(63 downto 0);
  signal phy_rx_start_ind_net_x6: std_logic;
  signal phy_tx_started_net_x2: std_logic;
  signal register11_q_net: std_logic_vector(63 downto 0);
  signal register14_q_net: std_logic_vector(63 downto 0);
  signal register15_q_net_x0: std_logic;
  signal register1_q_net: std_logic_vector(63 downto 0);
  signal register26_q_net_x0: std_logic_vector(31 downto 0);
  signal register27_q_net_x1: std_logic_vector(31 downto 0);
  signal register28_q_net_x1: std_logic_vector(31 downto 0);
  signal register50_q_net: std_logic_vector(63 downto 0);
  signal register51_q_net: std_logic_vector(63 downto 0);
  signal register52_q_net: std_logic_vector(63 downto 0);
  signal register54_q_net: std_logic_vector(63 downto 0);
  signal register55_q_net_x0: std_logic_vector(31 downto 0);
  signal register62_q_net: std_logic_vector(31 downto 0);
  signal register63_q_net: std_logic_vector(31 downto 0);
  signal x32lsb1_y_net_x0: std_logic_vector(31 downto 0);
  signal x32lsb2_y_net_x0: std_logic_vector(31 downto 0);
  signal x32lsb_y_net_x0: std_logic_vector(31 downto 0);
  signal x32lsb_y_net_x1: std_logic_vector(31 downto 0);
  signal x32msb1_y_net_x0: std_logic_vector(31 downto 0);
  signal x32msb2_y_net_x0: std_logic_vector(31 downto 0);
  signal x32msb_y_net_x0: std_logic_vector(31 downto 0);
  signal x32msb_y_net_x1: std_logic_vector(31 downto 0);

begin
  ce_1_sg_x42 <= ce_1;
  clk_1_sg_x42 <= clk_1;
  from_register10_data_out_net_x0 <= from_register10;
  from_register11_data_out_net_x0 <= from_register11;
  from_register13_data_out_net_x0 <= from_register13;
  microsecond_counter_op_net_x1 <= microsecond_timestamp;
  phy_rx_start_ind_net_x6 <= phy_rx_start_ind;
  phy_tx_started_net_x2 <= phy_tx_start_confirm;
  constant5_x0 <= constant5_op_net_x0;
  constant6_x0 <= constant6_op_net_x0;
  convert5_x0 <= convert5_dout_net_x0;
  reg_set_timestamp_lsb <= register28_q_net_x1;
  reg_set_timestamp_msb <= register27_q_net_x1;
  register15_x0 <= register15_q_net_x0;
  register26_x0 <= register26_q_net_x0;
  register55_x0 <= register55_q_net_x0;
  x32lsb1_x0 <= x32lsb1_y_net_x0;
  x32lsb2_x0 <= x32lsb2_y_net_x0;
  x32lsb_x1 <= x32lsb_y_net_x1;
  x32msb1_x0 <= x32msb1_y_net_x0;
  x32msb2_x0 <= x32msb2_y_net_x0;
  x32msb_x1 <= x32msb_y_net_x1;

  addsub: entity work.xladdsub_wlan_mac_hw
    generic map (
      a_arith => xlUnsigned,
      a_bin_pt => 0,
      a_width => 64,
      b_arith => xlSigned,
      b_bin_pt => 0,
      b_width => 32,
      c_has_c_out => 0,
      c_latency => 1,
      c_output_width => 66,
      core_name0 => "addsb_11_0_3c1d0ac9b6b8f403",
      extra_registers => 0,
      full_s_arith => 2,
      full_s_width => 66,
      latency => 1,
      overflow => 1,
      quantization => 1,
      s_arith => xlUnsigned,
      s_bin_pt => 0,
      s_width => 64
    )
    port map (
      a => register52_q_net,
      b => register63_q_net,
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      clr => '0',
      en => "1",
      s => addsub_s_net
    );

  constant5: entity work.constant_6293007044
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant5_op_net_x0
    );

  constant6: entity work.constant_6293007044
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant6_op_net_x0
    );

  convert5: entity work.xlconvert
    generic map (
      bool_conversion => 1,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 1,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 1,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      clr => '0',
      din(0) => logical1_y_net_x1,
      en => "1",
      dout(0) => convert5_dout_net_x0
    );

  convert7: entity work.xlconvert
    generic map (
      bool_conversion => 1,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 1,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 1,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      clr => '0',
      din(0) => phy_tx_started_net_x2,
      en => "1",
      dout(0) => convert7_dout_net_x0
    );

  delay: entity work.xldelay
    generic map (
      latency => 1,
      reg_retiming => 0,
      reset => 0,
      width => 1
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d(0) => register15_q_net_x0,
      en => '1',
      rst => '1',
      q(0) => delay_q_net
    );

  posedge1_b691247cd5: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x42,
      clk_1 => clk_1_sg_x42,
      d => convert7_dout_net_x0,
      q => logical1_y_net_x0
    );

  posedge2_d087737157: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x42,
      clk_1 => clk_1_sg_x42,
      d => phy_rx_start_ind_net_x6,
      q => logical1_y_net_x1
    );

  register1: entity work.xlregister
    generic map (
      d_width => 64,
      init_value => b"0000000000000000000000000000000000000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => register50_q_net,
      en => "1",
      rst => "0",
      q => register1_q_net
    );

  register11: entity work.xlregister
    generic map (
      d_width => 64,
      init_value => b"0000000000000000000000000000000000000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => register51_q_net,
      en => "1",
      rst => "0",
      q => register11_q_net
    );

  register14: entity work.xlregister
    generic map (
      d_width => 64,
      init_value => b"0000000000000000000000000000000000000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => register52_q_net,
      en => "1",
      rst => "0",
      q => register14_q_net
    );

  register15: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d(0) => logical1_y_net_x0,
      en => "1",
      rst => "0",
      q(0) => register15_q_net_x0
    );

  register26: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => x32msb_y_net_x0,
      en => "1",
      rst => "0",
      q => register26_q_net_x0
    );

  register27: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => from_register10_data_out_net_x0,
      en => "1",
      rst => "0",
      q => register27_q_net_x1
    );

  register28: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => from_register11_data_out_net_x0,
      en => "1",
      rst => "0",
      q => register28_q_net_x1
    );

  register50: entity work.xlregister
    generic map (
      d_width => 64,
      init_value => b"0000000000000000000000000000000000000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => microsecond_counter_op_net_x1,
      en => "1",
      rst => "0",
      q => register50_q_net
    );

  register51: entity work.xlregister
    generic map (
      d_width => 64,
      init_value => b"0000000000000000000000000000000000000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => microsecond_counter_op_net_x1,
      en => "1",
      rst => "0",
      q => register51_q_net
    );

  register52: entity work.xlregister
    generic map (
      d_width => 64,
      init_value => b"0000000000000000000000000000000000000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => microsecond_counter_op_net_x1,
      en => "1",
      rst => "0",
      q => register52_q_net
    );

  register54: entity work.xlregister
    generic map (
      d_width => 64,
      init_value => b"0000000000000000000000000000000000000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => addsub_s_net,
      en(0) => delay_q_net,
      rst => "0",
      q => register54_q_net
    );

  register55: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => x32lsb_y_net_x0,
      en => "1",
      rst => "0",
      q => register55_q_net_x0
    );

  register62: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => from_register13_data_out_net_x0,
      en => "1",
      rst => "0",
      q => register62_q_net
    );

  register63: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x42,
      clk => clk_1_sg_x42,
      d => register62_q_net,
      en => "1",
      rst => "0",
      q => register63_q_net
    );

  x32lsb: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 31,
      x_width => 64,
      y_width => 32
    )
    port map (
      x => register1_q_net,
      y => x32lsb_y_net_x1
    );

  x32lsb1: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 31,
      x_width => 64,
      y_width => 32
    )
    port map (
      x => register11_q_net,
      y => x32lsb1_y_net_x0
    );

  x32lsb2: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 31,
      x_width => 64,
      y_width => 32
    )
    port map (
      x => register14_q_net,
      y => x32lsb2_y_net_x0
    );

  x32lsb_x0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 31,
      x_width => 64,
      y_width => 32
    )
    port map (
      x => register54_q_net,
      y => x32lsb_y_net_x0
    );

  x32msb: entity work.xlslice
    generic map (
      new_lsb => 32,
      new_msb => 63,
      x_width => 64,
      y_width => 32
    )
    port map (
      x => register1_q_net,
      y => x32msb_y_net_x1
    );

  x32msb1: entity work.xlslice
    generic map (
      new_lsb => 32,
      new_msb => 63,
      x_width => 64,
      y_width => 32
    )
    port map (
      x => register11_q_net,
      y => x32msb1_y_net_x0
    );

  x32msb2: entity work.xlslice
    generic map (
      new_lsb => 32,
      new_msb => 63,
      x_width => 64,
      y_width => 32
    )
    port map (
      x => register14_q_net,
      y => x32msb2_y_net_x0
    );

  x32msb_x0: entity work.xlslice
    generic map (
      new_lsb => 32,
      new_msb => 63,
      x_width => 64,
      y_width => 32
    )
    port map (
      x => register54_q_net,
      y => x32msb_y_net_x0
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Registers/Tx Controller Regs/x2"

entity x2_entity_cfc11f484f is
  port (
    a: in std_logic_vector(14 downto 0); 
    ax16: out std_logic_vector(18 downto 0)
  );
end x2_entity_cfc11f484f;

architecture structural of x2_entity_cfc11f484f is
  signal concat1_y_net_x4: std_logic_vector(18 downto 0);
  signal constant9_op_net: std_logic_vector(3 downto 0);
  signal register9_q_net_x0: std_logic_vector(14 downto 0);

begin
  register9_q_net_x0 <= a;
  ax16 <= concat1_y_net_x4;

  concat1: entity work.concat_16fe2e7edf
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      in0 => register9_q_net_x0,
      in1 => constant9_op_net,
      y => concat1_y_net_x4
    );

  constant9: entity work.constant_4c449dd556
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op => constant9_op_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Registers/Tx Controller Regs"

entity tx_controller_regs_entity_8d6ee7f5ae is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    from_register1: in std_logic_vector(31 downto 0); 
    from_register12: in std_logic_vector(31 downto 0); 
    from_register14: in std_logic_vector(31 downto 0); 
    from_register3: in std_logic_vector(31 downto 0); 
    from_register7: in std_logic_vector(31 downto 0); 
    from_register9: in std_logic_vector(31 downto 0); 
    reg_postrx_timer1_countto: out std_logic_vector(18 downto 0); 
    reg_postrx_timer1_en: out std_logic; 
    reg_postrx_timer2_countto: out std_logic_vector(18 downto 0); 
    reg_postrx_timer2_en: out std_logic; 
    reg_posttx_timer1_countto: out std_logic_vector(18 downto 0); 
    reg_posttx_timer1_en: out std_logic; 
    reg_posttx_timer2_countto: out std_logic_vector(18 downto 0); 
    reg_posttx_timer2_en: out std_logic; 
    reg_tx_a_param_bo_slots: out std_logic_vector(15 downto 0); 
    reg_tx_a_param_pktbuf: out std_logic_vector(3 downto 0); 
    reg_tx_a_param_postwait_posttxtimer2: out std_logic; 
    reg_tx_a_param_prewait_postrxtimer1: out std_logic; 
    reg_tx_a_param_prewait_posttxtimer1: out std_logic; 
    reg_tx_a_param_txantmask: out std_logic_vector(3 downto 0); 
    reg_tx_a_param_txgain_rfa: out std_logic_vector(5 downto 0); 
    reg_tx_a_param_txgain_rfb: out std_logic_vector(5 downto 0); 
    reg_tx_a_param_txgain_rfc: out std_logic_vector(5 downto 0); 
    reg_tx_a_param_txgain_rfd: out std_logic_vector(5 downto 0); 
    reg_tx_b_param_pktbuf: out std_logic_vector(3 downto 0); 
    reg_tx_b_param_postwait_posttxtimer1: out std_logic; 
    reg_tx_b_param_prewait_postrxtimer1: out std_logic; 
    reg_tx_b_param_prewait_postrxtimer2: out std_logic; 
    reg_tx_b_param_req_zero_nav: out std_logic; 
    reg_tx_b_param_txantmask: out std_logic_vector(3 downto 0); 
    reg_tx_b_param_txgain_rfa: out std_logic_vector(5 downto 0); 
    reg_tx_b_param_txgain_rfb: out std_logic_vector(5 downto 0); 
    reg_tx_b_param_txgain_rfc: out std_logic_vector(5 downto 0); 
    reg_tx_b_param_txgain_rfd: out std_logic_vector(5 downto 0)
  );
end tx_controller_regs_entity_8d6ee7f5ae;

architecture structural of tx_controller_regs_entity_8d6ee7f5ae is
  signal b_10_y_net: std_logic;
  signal b_11_6_1_y_net: std_logic_vector(5 downto 0);
  signal b_11_6_y_net: std_logic_vector(5 downto 0);
  signal b_11_y_net: std_logic;
  signal b_14_0_1_y_net: std_logic_vector(14 downto 0);
  signal b_14_0_y_net: std_logic_vector(14 downto 0);
  signal b_15_1_y_net: std_logic;
  signal b_15_y_net: std_logic;
  signal b_17_12_1_y_net: std_logic_vector(5 downto 0);
  signal b_17_12_y_net: std_logic_vector(5 downto 0);
  signal b_23_18_1_y_net: std_logic_vector(5 downto 0);
  signal b_23_18_y_net: std_logic_vector(5 downto 0);
  signal b_23_8_y_net: std_logic_vector(15 downto 0);
  signal b_24_y_net: std_logic;
  signal b_25_y_net: std_logic;
  signal b_26_y_net: std_logic;
  signal b_30_16_1_y_net: std_logic_vector(14 downto 0);
  signal b_30_16_y_net: std_logic_vector(14 downto 0);
  signal b_31_1_y_net: std_logic;
  signal b_31_2_y_net: std_logic;
  signal b_3_0_y_net: std_logic_vector(3 downto 0);
  signal b_3_0_y_net_x0: std_logic_vector(3 downto 0);
  signal b_5_0_1_y_net: std_logic_vector(5 downto 0);
  signal b_5_0_y_net: std_logic_vector(5 downto 0);
  signal b_7_4_y_net: std_logic_vector(3 downto 0);
  signal b_7_4_y_net_x0: std_logic_vector(3 downto 0);
  signal b_8_y_net: std_logic;
  signal b_9_y_net: std_logic;
  signal ce_1_sg_x43: std_logic;
  signal clk_1_sg_x43: std_logic;
  signal concat1_y_net_x10: std_logic_vector(18 downto 0);
  signal concat1_y_net_x11: std_logic_vector(18 downto 0);
  signal concat1_y_net_x8: std_logic_vector(18 downto 0);
  signal concat1_y_net_x9: std_logic_vector(18 downto 0);
  signal from_register12_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register14_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register1_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register3_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register7_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register9_data_out_net_x0: std_logic_vector(31 downto 0);
  signal register11_q_net_x1: std_logic;
  signal register14_q_net_x1: std_logic;
  signal register15_q_net_x0: std_logic_vector(14 downto 0);
  signal register16_q_net_x0: std_logic_vector(3 downto 0);
  signal register17_q_net_x0: std_logic_vector(15 downto 0);
  signal register19_q_net_x0: std_logic_vector(5 downto 0);
  signal register1_q_net_x0: std_logic;
  signal register22_q_net_x0: std_logic_vector(3 downto 0);
  signal register23_q_net_x0: std_logic_vector(14 downto 0);
  signal register25_q_net_x0: std_logic_vector(3 downto 0);
  signal register2_q_net_x0: std_logic;
  signal register3_q_net_x0: std_logic;
  signal register4_q_net_x0: std_logic_vector(3 downto 0);
  signal register53_q_net_x0: std_logic_vector(5 downto 0);
  signal register56_q_net_x0: std_logic_vector(5 downto 0);
  signal register57_q_net_x0: std_logic_vector(5 downto 0);
  signal register58_q_net_x0: std_logic_vector(5 downto 0);
  signal register59_q_net_x0: std_logic_vector(5 downto 0);
  signal register5_q_net_x0: std_logic;
  signal register60_q_net_x0: std_logic_vector(5 downto 0);
  signal register61_q_net_x0: std_logic_vector(5 downto 0);
  signal register64_q_net_x0: std_logic_vector(14 downto 0);
  signal register66_q_net_x1: std_logic;
  signal register67_q_net_x1: std_logic;
  signal register6_q_net_x0: std_logic;
  signal register7_q_net_x0: std_logic;
  signal register8_q_net_x0: std_logic;
  signal register9_q_net_x0: std_logic_vector(14 downto 0);

begin
  ce_1_sg_x43 <= ce_1;
  clk_1_sg_x43 <= clk_1;
  from_register1_data_out_net_x0 <= from_register1;
  from_register12_data_out_net_x0 <= from_register12;
  from_register14_data_out_net_x0 <= from_register14;
  from_register3_data_out_net_x0 <= from_register3;
  from_register7_data_out_net_x0 <= from_register7;
  from_register9_data_out_net_x0 <= from_register9;
  reg_postrx_timer1_countto <= concat1_y_net_x11;
  reg_postrx_timer1_en <= register66_q_net_x1;
  reg_postrx_timer2_countto <= concat1_y_net_x9;
  reg_postrx_timer2_en <= register67_q_net_x1;
  reg_posttx_timer1_countto <= concat1_y_net_x10;
  reg_posttx_timer1_en <= register11_q_net_x1;
  reg_posttx_timer2_countto <= concat1_y_net_x8;
  reg_posttx_timer2_en <= register14_q_net_x1;
  reg_tx_a_param_bo_slots <= register17_q_net_x0;
  reg_tx_a_param_pktbuf <= register16_q_net_x0;
  reg_tx_a_param_postwait_posttxtimer2 <= register3_q_net_x0;
  reg_tx_a_param_prewait_postrxtimer1 <= register1_q_net_x0;
  reg_tx_a_param_prewait_posttxtimer1 <= register2_q_net_x0;
  reg_tx_a_param_txantmask <= register25_q_net_x0;
  reg_tx_a_param_txgain_rfa <= register19_q_net_x0;
  reg_tx_a_param_txgain_rfb <= register53_q_net_x0;
  reg_tx_a_param_txgain_rfc <= register56_q_net_x0;
  reg_tx_a_param_txgain_rfd <= register57_q_net_x0;
  reg_tx_b_param_pktbuf <= register22_q_net_x0;
  reg_tx_b_param_postwait_posttxtimer1 <= register7_q_net_x0;
  reg_tx_b_param_prewait_postrxtimer1 <= register5_q_net_x0;
  reg_tx_b_param_prewait_postrxtimer2 <= register6_q_net_x0;
  reg_tx_b_param_req_zero_nav <= register8_q_net_x0;
  reg_tx_b_param_txantmask <= register4_q_net_x0;
  reg_tx_b_param_txgain_rfa <= register58_q_net_x0;
  reg_tx_b_param_txgain_rfb <= register59_q_net_x0;
  reg_tx_b_param_txgain_rfc <= register60_q_net_x0;
  reg_tx_b_param_txgain_rfd <= register61_q_net_x0;

  b_10: entity work.xlslice
    generic map (
      new_lsb => 10,
      new_msb => 10,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register9_data_out_net_x0,
      y(0) => b_10_y_net
    );

  b_11: entity work.xlslice
    generic map (
      new_lsb => 11,
      new_msb => 11,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register9_data_out_net_x0,
      y(0) => b_11_y_net
    );

  b_11_6: entity work.xlslice
    generic map (
      new_lsb => 6,
      new_msb => 11,
      x_width => 32,
      y_width => 6
    )
    port map (
      x => from_register7_data_out_net_x0,
      y => b_11_6_y_net
    );

  b_11_6_1: entity work.xlslice
    generic map (
      new_lsb => 6,
      new_msb => 11,
      x_width => 32,
      y_width => 6
    )
    port map (
      x => from_register12_data_out_net_x0,
      y => b_11_6_1_y_net
    );

  b_14_0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 14,
      x_width => 32,
      y_width => 15
    )
    port map (
      x => from_register14_data_out_net_x0,
      y => b_14_0_y_net
    );

  b_14_0_1: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 14,
      x_width => 32,
      y_width => 15
    )
    port map (
      x => from_register1_data_out_net_x0,
      y => b_14_0_1_y_net
    );

  b_15: entity work.xlslice
    generic map (
      new_lsb => 15,
      new_msb => 15,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register14_data_out_net_x0,
      y(0) => b_15_y_net
    );

  b_15_1: entity work.xlslice
    generic map (
      new_lsb => 15,
      new_msb => 15,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register1_data_out_net_x0,
      y(0) => b_15_1_y_net
    );

  b_17_12: entity work.xlslice
    generic map (
      new_lsb => 12,
      new_msb => 17,
      x_width => 32,
      y_width => 6
    )
    port map (
      x => from_register7_data_out_net_x0,
      y => b_17_12_y_net
    );

  b_17_12_1: entity work.xlslice
    generic map (
      new_lsb => 12,
      new_msb => 17,
      x_width => 32,
      y_width => 6
    )
    port map (
      x => from_register12_data_out_net_x0,
      y => b_17_12_1_y_net
    );

  b_23_18: entity work.xlslice
    generic map (
      new_lsb => 18,
      new_msb => 23,
      x_width => 32,
      y_width => 6
    )
    port map (
      x => from_register7_data_out_net_x0,
      y => b_23_18_y_net
    );

  b_23_18_1: entity work.xlslice
    generic map (
      new_lsb => 18,
      new_msb => 23,
      x_width => 32,
      y_width => 6
    )
    port map (
      x => from_register12_data_out_net_x0,
      y => b_23_18_1_y_net
    );

  b_23_8: entity work.xlslice
    generic map (
      new_lsb => 8,
      new_msb => 23,
      x_width => 32,
      y_width => 16
    )
    port map (
      x => from_register3_data_out_net_x0,
      y => b_23_8_y_net
    );

  b_24: entity work.xlslice
    generic map (
      new_lsb => 24,
      new_msb => 24,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register3_data_out_net_x0,
      y(0) => b_24_y_net
    );

  b_25: entity work.xlslice
    generic map (
      new_lsb => 25,
      new_msb => 25,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register3_data_out_net_x0,
      y(0) => b_25_y_net
    );

  b_26: entity work.xlslice
    generic map (
      new_lsb => 26,
      new_msb => 26,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register3_data_out_net_x0,
      y(0) => b_26_y_net
    );

  b_30_16: entity work.xlslice
    generic map (
      new_lsb => 16,
      new_msb => 30,
      x_width => 32,
      y_width => 15
    )
    port map (
      x => from_register14_data_out_net_x0,
      y => b_30_16_y_net
    );

  b_30_16_1: entity work.xlslice
    generic map (
      new_lsb => 16,
      new_msb => 30,
      x_width => 32,
      y_width => 15
    )
    port map (
      x => from_register1_data_out_net_x0,
      y => b_30_16_1_y_net
    );

  b_31_1: entity work.xlslice
    generic map (
      new_lsb => 31,
      new_msb => 31,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register14_data_out_net_x0,
      y(0) => b_31_1_y_net
    );

  b_31_2: entity work.xlslice
    generic map (
      new_lsb => 31,
      new_msb => 31,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register1_data_out_net_x0,
      y(0) => b_31_2_y_net
    );

  b_3_0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 3,
      x_width => 32,
      y_width => 4
    )
    port map (
      x => from_register9_data_out_net_x0,
      y => b_3_0_y_net
    );

  b_3_0_x0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 3,
      x_width => 32,
      y_width => 4
    )
    port map (
      x => from_register3_data_out_net_x0,
      y => b_3_0_y_net_x0
    );

  b_5_0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 5,
      x_width => 32,
      y_width => 6
    )
    port map (
      x => from_register7_data_out_net_x0,
      y => b_5_0_y_net
    );

  b_5_0_1: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 5,
      x_width => 32,
      y_width => 6
    )
    port map (
      x => from_register12_data_out_net_x0,
      y => b_5_0_1_y_net
    );

  b_7_4: entity work.xlslice
    generic map (
      new_lsb => 4,
      new_msb => 7,
      x_width => 32,
      y_width => 4
    )
    port map (
      x => from_register3_data_out_net_x0,
      y => b_7_4_y_net
    );

  b_7_4_x0: entity work.xlslice
    generic map (
      new_lsb => 4,
      new_msb => 7,
      x_width => 32,
      y_width => 4
    )
    port map (
      x => from_register9_data_out_net_x0,
      y => b_7_4_y_net_x0
    );

  b_8: entity work.xlslice
    generic map (
      new_lsb => 8,
      new_msb => 8,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register9_data_out_net_x0,
      y(0) => b_8_y_net
    );

  b_9: entity work.xlslice
    generic map (
      new_lsb => 9,
      new_msb => 9,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register9_data_out_net_x0,
      y(0) => b_9_y_net
    );

  register1: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d(0) => b_24_y_net,
      en => "1",
      rst => "0",
      q(0) => register1_q_net_x0
    );

  register11: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d(0) => b_15_1_y_net,
      en => "1",
      rst => "0",
      q(0) => register11_q_net_x1
    );

  register14: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d(0) => b_31_2_y_net,
      en => "1",
      rst => "0",
      q(0) => register14_q_net_x1
    );

  register15: entity work.xlregister
    generic map (
      d_width => 15,
      init_value => b"000000000000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_14_0_1_y_net,
      en => "1",
      rst => "0",
      q => register15_q_net_x0
    );

  register16: entity work.xlregister
    generic map (
      d_width => 4,
      init_value => b"0000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_3_0_y_net_x0,
      en => "1",
      rst => "0",
      q => register16_q_net_x0
    );

  register17: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_23_8_y_net,
      en => "1",
      rst => "0",
      q => register17_q_net_x0
    );

  register19: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_5_0_y_net,
      en => "1",
      rst => "0",
      q => register19_q_net_x0
    );

  register2: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d(0) => b_25_y_net,
      en => "1",
      rst => "0",
      q(0) => register2_q_net_x0
    );

  register22: entity work.xlregister
    generic map (
      d_width => 4,
      init_value => b"0000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_3_0_y_net,
      en => "1",
      rst => "0",
      q => register22_q_net_x0
    );

  register23: entity work.xlregister
    generic map (
      d_width => 15,
      init_value => b"000000000000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_14_0_y_net,
      en => "1",
      rst => "0",
      q => register23_q_net_x0
    );

  register25: entity work.xlregister
    generic map (
      d_width => 4,
      init_value => b"0000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_7_4_y_net,
      en => "1",
      rst => "0",
      q => register25_q_net_x0
    );

  register3: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d(0) => b_26_y_net,
      en => "1",
      rst => "0",
      q(0) => register3_q_net_x0
    );

  register4: entity work.xlregister
    generic map (
      d_width => 4,
      init_value => b"0000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_7_4_y_net_x0,
      en => "1",
      rst => "0",
      q => register4_q_net_x0
    );

  register5: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d(0) => b_8_y_net,
      en => "1",
      rst => "0",
      q(0) => register5_q_net_x0
    );

  register53: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_11_6_y_net,
      en => "1",
      rst => "0",
      q => register53_q_net_x0
    );

  register56: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_17_12_y_net,
      en => "1",
      rst => "0",
      q => register56_q_net_x0
    );

  register57: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_23_18_y_net,
      en => "1",
      rst => "0",
      q => register57_q_net_x0
    );

  register58: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_5_0_1_y_net,
      en => "1",
      rst => "0",
      q => register58_q_net_x0
    );

  register59: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_11_6_1_y_net,
      en => "1",
      rst => "0",
      q => register59_q_net_x0
    );

  register6: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d(0) => b_9_y_net,
      en => "1",
      rst => "0",
      q(0) => register6_q_net_x0
    );

  register60: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_17_12_1_y_net,
      en => "1",
      rst => "0",
      q => register60_q_net_x0
    );

  register61: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_23_18_1_y_net,
      en => "1",
      rst => "0",
      q => register61_q_net_x0
    );

  register64: entity work.xlregister
    generic map (
      d_width => 15,
      init_value => b"000000000000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_30_16_y_net,
      en => "1",
      rst => "0",
      q => register64_q_net_x0
    );

  register66: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d(0) => b_15_y_net,
      en => "1",
      rst => "0",
      q(0) => register66_q_net_x1
    );

  register67: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d(0) => b_31_1_y_net,
      en => "1",
      rst => "0",
      q(0) => register67_q_net_x1
    );

  register7: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d(0) => b_10_y_net,
      en => "1",
      rst => "0",
      q(0) => register7_q_net_x0
    );

  register8: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d(0) => b_11_y_net,
      en => "1",
      rst => "0",
      q(0) => register8_q_net_x0
    );

  register9: entity work.xlregister
    generic map (
      d_width => 15,
      init_value => b"000000000000000"
    )
    port map (
      ce => ce_1_sg_x43,
      clk => clk_1_sg_x43,
      d => b_30_16_1_y_net,
      en => "1",
      rst => "0",
      q => register9_q_net_x0
    );

  x2_cfc11f484f: entity work.x2_entity_cfc11f484f
    port map (
      a => register9_q_net_x0,
      ax16 => concat1_y_net_x8
    );

  x4_5d63d458b2: entity work.x2_entity_cfc11f484f
    port map (
      a => register64_q_net_x0,
      ax16 => concat1_y_net_x9
    );

  x6_5af8904bd3: entity work.x2_entity_cfc11f484f
    port map (
      a => register15_q_net_x0,
      ax16 => concat1_y_net_x10
    );

  x7_feff68a011: entity work.x2_entity_cfc11f484f
    port map (
      a => register23_q_net_x0,
      ax16 => concat1_y_net_x11
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Registers/x1"

entity x1_entity_fdf9c2a3eb is
  port (
    a: in std_logic_vector(9 downto 0); 
    ax16: out std_logic_vector(13 downto 0)
  );
end x1_entity_fdf9c2a3eb;

architecture structural of x1_entity_fdf9c2a3eb is
  signal concat1_y_net_x3: std_logic_vector(13 downto 0);
  signal constant9_op_net: std_logic_vector(3 downto 0);
  signal register33_q_net_x0: std_logic_vector(9 downto 0);

begin
  register33_q_net_x0 <= a;
  ax16 <= concat1_y_net_x3;

  concat1: entity work.concat_4a94c27437
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      in0 => register33_q_net_x0,
      in1 => constant9_op_net,
      y => concat1_y_net_x3
    );

  constant9: entity work.constant_4c449dd556
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op => constant9_op_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Registers/x5"

entity x5_entity_99d1738aaf is
  port (
    a: in std_logic_vector(15 downto 0); 
    ax16: out std_logic_vector(19 downto 0)
  );
end x5_entity_99d1738aaf;

architecture structural of x5_entity_99d1738aaf is
  signal concat1_y_net_x4: std_logic_vector(19 downto 0);
  signal constant9_op_net: std_logic_vector(3 downto 0);
  signal register32_q_net_x0: std_logic_vector(15 downto 0);

begin
  register32_q_net_x0 <= a;
  ax16 <= concat1_y_net_x4;

  concat1: entity work.concat_0a671b9443
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      in0 => register32_q_net_x0,
      in1 => constant9_op_net,
      y => concat1_y_net_x4
    );

  constant9: entity work.constant_4c449dd556
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op => constant9_op_net
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Registers"

entity registers_entity_c6b0991c81 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    from_register1: in std_logic_vector(31 downto 0); 
    from_register10: in std_logic_vector(31 downto 0); 
    from_register11: in std_logic_vector(31 downto 0); 
    from_register12: in std_logic_vector(31 downto 0); 
    from_register13: in std_logic_vector(31 downto 0); 
    from_register14: in std_logic_vector(31 downto 0); 
    from_register15: in std_logic_vector(31 downto 0); 
    from_register16: in std_logic_vector(31 downto 0); 
    from_register1_x0: in std_logic_vector(31 downto 0); 
    from_register2: in std_logic_vector(31 downto 0); 
    from_register3: in std_logic_vector(31 downto 0); 
    from_register4: in std_logic_vector(31 downto 0); 
    from_register5: in std_logic_vector(31 downto 0); 
    from_register6: in std_logic_vector(31 downto 0); 
    from_register7: in std_logic_vector(31 downto 0); 
    from_register8: in std_logic_vector(31 downto 0); 
    from_register9: in std_logic_vector(31 downto 0); 
    mcode_tx_control_a: in std_logic_vector(2 downto 0); 
    mcode_tx_control_b: in std_logic_vector(2 downto 0); 
    nav: in std_logic; 
    nav_value_100nsec: in std_logic_vector(15 downto 0); 
    nav_x0: in std_logic; 
    o: in std_logic; 
    o_x0: in std_logic; 
    o_x1: in std_logic; 
    o_x2: in std_logic; 
    o_x3: in std_logic; 
    phy_cca_ind_busy: in std_logic; 
    phy_rx_byte: in std_logic_vector(7 downto 0); 
    phy_rx_byte_valid: in std_logic; 
    phy_rx_bytenum: in std_logic_vector(15 downto 0); 
    phy_rx_end_rxerror: in std_logic_vector(3 downto 0); 
    phy_rx_params_length: in std_logic_vector(15 downto 0); 
    phy_rx_params_mcs: in std_logic_vector(6 downto 0); 
    phy_rx_params_phy_mode: in std_logic_vector(2 downto 0); 
    phy_rx_params_unsupported: in std_logic; 
    phy_rx_params_valid: in std_logic; 
    phy_rx_start_ind: in std_logic; 
    phy_rx_start_phy_sel: in std_logic; 
    phy_tx_started: in std_logic; 
    register1_x0: in std_logic_vector(1 downto 0); 
    register1_x1: in std_logic_vector(1 downto 0); 
    register2_x0: in std_logic; 
    register2_x1: in std_logic; 
    register2_x2: in std_logic; 
    register2_x3: in std_logic; 
    rx_timers: in std_logic; 
    rx_timers_x0: in std_logic; 
    rx_timers_x1: in std_logic; 
    rx_timers_x2: in std_logic; 
    status_current_backoff_count: in std_logic_vector(15 downto 0); 
    x64_bit_usec_counter: in std_logic_vector(63 downto 0); 
    constant1_x0: out std_logic; 
    constant2_x0: out std_logic; 
    constant3_x0: out std_logic; 
    convert1_x0: out std_logic_vector(31 downto 0); 
    convert4_x0: out std_logic_vector(31 downto 0); 
    convert6_x0: out std_logic_vector(31 downto 0); 
    convert_x0: out std_logic_vector(31 downto 0); 
    ctrl_bits: out std_logic; 
    ctrl_bits_x0: out std_logic; 
    ctrl_bits_x1: out std_logic; 
    ctrl_bits_x10: out std_logic; 
    ctrl_bits_x2: out std_logic; 
    ctrl_bits_x3: out std_logic; 
    ctrl_bits_x4: out std_logic; 
    ctrl_bits_x5: out std_logic; 
    ctrl_bits_x6: out std_logic; 
    ctrl_bits_x7: out std_logic; 
    ctrl_bits_x8: out std_logic; 
    ctrl_bits_x9: out std_logic; 
    reg_backoff_sw_numslots: out std_logic_vector(15 downto 0); 
    reg_backoff_sw_start: out std_logic; 
    reg_calibtime_txdifs: out std_logic_vector(13 downto 0); 
    reg_interval_difs: out std_logic_vector(13 downto 0); 
    reg_interval_eifs: out std_logic_vector(19 downto 0); 
    reg_interval_slot: out std_logic_vector(13 downto 0); 
    reg_nav_check_addr_1: out std_logic_vector(31 downto 0); 
    reg_nav_check_addr_2: out std_logic_vector(31 downto 0); 
    reg_nav_time_adj: out std_logic_vector(7 downto 0); 
    reg_tx_start_a: out std_logic; 
    reg_tx_start_b: out std_logic; 
    register11_x0: out std_logic; 
    status_register: out std_logic; 
    status_register_x0: out std_logic_vector(31 downto 0); 
    timestamp_regs_io: out std_logic_vector(31 downto 0); 
    timestamp_regs_io_x0: out std_logic_vector(31 downto 0); 
    timestamp_regs_io_x1: out std_logic_vector(31 downto 0); 
    timestamp_regs_io_x10: out std_logic_vector(31 downto 0); 
    timestamp_regs_io_x11: out std_logic_vector(31 downto 0); 
    timestamp_regs_io_x12: out std_logic_vector(31 downto 0); 
    timestamp_regs_io_x2: out std_logic_vector(31 downto 0); 
    timestamp_regs_io_x3: out std_logic_vector(31 downto 0); 
    timestamp_regs_io_x4: out std_logic_vector(31 downto 0); 
    timestamp_regs_io_x5: out std_logic; 
    timestamp_regs_io_x6: out std_logic; 
    timestamp_regs_io_x7: out std_logic; 
    timestamp_regs_io_x8: out std_logic; 
    timestamp_regs_io_x9: out std_logic_vector(31 downto 0); 
    tx_controller_regs: out std_logic; 
    tx_controller_regs_x0: out std_logic; 
    tx_controller_regs_x1: out std_logic; 
    tx_controller_regs_x10: out std_logic; 
    tx_controller_regs_x11: out std_logic_vector(5 downto 0); 
    tx_controller_regs_x12: out std_logic_vector(5 downto 0); 
    tx_controller_regs_x13: out std_logic_vector(5 downto 0); 
    tx_controller_regs_x14: out std_logic_vector(5 downto 0); 
    tx_controller_regs_x15: out std_logic_vector(5 downto 0); 
    tx_controller_regs_x16: out std_logic; 
    tx_controller_regs_x17: out std_logic_vector(5 downto 0); 
    tx_controller_regs_x18: out std_logic_vector(5 downto 0); 
    tx_controller_regs_x19: out std_logic; 
    tx_controller_regs_x2: out std_logic_vector(3 downto 0); 
    tx_controller_regs_x20: out std_logic; 
    tx_controller_regs_x21: out std_logic; 
    tx_controller_regs_x22: out std_logic; 
    tx_controller_regs_x23: out std_logic_vector(18 downto 0); 
    tx_controller_regs_x24: out std_logic_vector(18 downto 0); 
    tx_controller_regs_x25: out std_logic_vector(18 downto 0); 
    tx_controller_regs_x26: out std_logic_vector(18 downto 0); 
    tx_controller_regs_x3: out std_logic_vector(15 downto 0); 
    tx_controller_regs_x4: out std_logic_vector(5 downto 0); 
    tx_controller_regs_x5: out std_logic; 
    tx_controller_regs_x6: out std_logic_vector(3 downto 0); 
    tx_controller_regs_x7: out std_logic_vector(3 downto 0); 
    tx_controller_regs_x8: out std_logic; 
    tx_controller_regs_x9: out std_logic_vector(3 downto 0)
  );
end registers_entity_c6b0991c81;

architecture structural of registers_entity_c6b0991c81 is
  signal b_0_y_net: std_logic;
  signal b_0_y_net_x7: std_logic;
  signal b_10_y_net_x1: std_logic;
  signal b_11_y_net_x1: std_logic;
  signal b_15_0_2_y_net: std_logic_vector(15 downto 0);
  signal b_15_0_y_net: std_logic_vector(15 downto 0);
  signal b_1_y_net: std_logic;
  signal b_1_y_net_x3: std_logic;
  signal b_29_20_y_net: std_logic_vector(9 downto 0);
  signal b_31_24_y_net: std_logic_vector(7 downto 0);
  signal b_31_y_net: std_logic;
  signal b_3_y_net_x1: std_logic;
  signal b_4_y_net_x2: std_logic;
  signal b_5_y_net_x2: std_logic;
  signal b_6_y_net_x2: std_logic;
  signal b_7_y_net_x1: std_logic;
  signal b_8_y_net_x1: std_logic;
  signal b_9_0_1_y_net: std_logic_vector(9 downto 0);
  signal b_9_0_y_net: std_logic_vector(9 downto 0);
  signal b_9_y_net_x1: std_logic;
  signal bitsm_4_y_net_x1: std_logic_vector(15 downto 0);
  signal ce_1_sg_x44: std_logic;
  signal clk_1_sg_x44: std_logic;
  signal concat1_y_net: std_logic_vector(23 downto 0);
  signal concat1_y_net_x12: std_logic_vector(18 downto 0);
  signal concat1_y_net_x13: std_logic_vector(18 downto 0);
  signal concat1_y_net_x14: std_logic_vector(18 downto 0);
  signal concat1_y_net_x15: std_logic_vector(18 downto 0);
  signal concat1_y_net_x16: std_logic_vector(13 downto 0);
  signal concat1_y_net_x17: std_logic_vector(13 downto 0);
  signal concat1_y_net_x18: std_logic_vector(19 downto 0);
  signal concat1_y_net_x19: std_logic_vector(13 downto 0);
  signal concat3_y_net: std_logic_vector(29 downto 0);
  signal constant1_op_net_x1: std_logic;
  signal constant1_op_net_x2: std_logic;
  signal constant2_op_net_x0: std_logic;
  signal constant3_op_net_x0: std_logic;
  signal constant4_op_net: std_logic;
  signal constant5_op_net_x1: std_logic;
  signal constant6_op_net_x1: std_logic;
  signal convert1_dout_net_x1: std_logic_vector(31 downto 0);
  signal convert1_dout_net_x2: std_logic_vector(31 downto 0);
  signal convert4_dout_net_x0: std_logic_vector(31 downto 0);
  signal convert5_dout_net_x1: std_logic;
  signal convert6_dout_net_x0: std_logic_vector(31 downto 0);
  signal convert_dout_net_x0: std_logic_vector(31 downto 0);
  signal delay_q_net_x2: std_logic;
  signal from_register10_data_out_net_x1: std_logic_vector(31 downto 0);
  signal from_register11_data_out_net_x1: std_logic_vector(31 downto 0);
  signal from_register12_data_out_net_x1: std_logic_vector(31 downto 0);
  signal from_register13_data_out_net_x1: std_logic_vector(31 downto 0);
  signal from_register14_data_out_net_x1: std_logic_vector(31 downto 0);
  signal from_register15_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register16_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register1_data_out_net_x1: std_logic_vector(31 downto 0);
  signal from_register1_data_out_net_x2: std_logic_vector(31 downto 0);
  signal from_register2_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register3_data_out_net_x1: std_logic_vector(31 downto 0);
  signal from_register4_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register5_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register6_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register7_data_out_net_x1: std_logic_vector(31 downto 0);
  signal from_register8_data_out_net_x0: std_logic_vector(31 downto 0);
  signal from_register9_data_out_net_x1: std_logic_vector(31 downto 0);
  signal logical1_y_net_x0: std_logic;
  signal logical1_y_net_x5: std_logic;
  signal logical3_y_net_x4: std_logic;
  signal logical_y_net_x0: std_logic;
  signal mcode_tx_control_a_fsm_state_out_net_x0: std_logic_vector(2 downto 0);
  signal mcode_tx_control_b_fsm_state_out_net_x0: std_logic_vector(2 downto 0);
  signal microsecond_counter_op_net_x2: std_logic_vector(63 downto 0);
  signal num_slots_op_net_x1: std_logic_vector(15 downto 0);
  signal phy_cca_ind_busy_net_x2: std_logic;
  signal phy_rx_data_byte_net_x4: std_logic_vector(7 downto 0);
  signal phy_rx_data_bytenum_net_x4: std_logic_vector(15 downto 0);
  signal phy_rx_data_ind_net_x4: std_logic;
  signal phy_rx_end_rxerror_net_x7: std_logic_vector(3 downto 0);
  signal phy_rx_params_ind_net_x0: std_logic;
  signal phy_rx_params_length_net_x0: std_logic_vector(15 downto 0);
  signal phy_rx_params_mcs_net_x0: std_logic_vector(6 downto 0);
  signal phy_rx_params_phy_mode_net_x0: std_logic_vector(2 downto 0);
  signal phy_rx_params_unsupported_net_x0: std_logic;
  signal phy_rx_start_ind_net_x7: std_logic;
  signal phy_rx_start_phy_sel_net_x0: std_logic;
  signal phy_tx_started_net_x3: std_logic;
  signal register10_q_net: std_logic_vector(23 downto 0);
  signal register11_q_net_x0: std_logic;
  signal register11_q_net_x2: std_logic;
  signal register12_q_net: std_logic_vector(15 downto 0);
  signal register13_q_net: std_logic_vector(15 downto 0);
  signal register14_q_net_x2: std_logic;
  signal register15_q_net_x1: std_logic;
  signal register16_q_net_x1: std_logic_vector(3 downto 0);
  signal register17_q_net_x1: std_logic_vector(15 downto 0);
  signal register19_q_net_x1: std_logic_vector(5 downto 0);
  signal register1_q_net: std_logic_vector(29 downto 0);
  signal register1_q_net_x4: std_logic_vector(1 downto 0);
  signal register1_q_net_x5: std_logic_vector(1 downto 0);
  signal register1_q_net_x6: std_logic;
  signal register20_q_net_x1: std_logic_vector(15 downto 0);
  signal register21_q_net_x1: std_logic;
  signal register22_q_net_x1: std_logic_vector(3 downto 0);
  signal register25_q_net_x1: std_logic_vector(3 downto 0);
  signal register26_q_net_x1: std_logic_vector(31 downto 0);
  signal register27_q_net_x2: std_logic_vector(31 downto 0);
  signal register28_q_net_x2: std_logic_vector(31 downto 0);
  signal register29_q_net_x0: std_logic_vector(9 downto 0);
  signal register2_q_net: std_logic_vector(15 downto 0);
  signal register2_q_net_x30: std_logic;
  signal register2_q_net_x31: std_logic;
  signal register2_q_net_x32: std_logic;
  signal register2_q_net_x33: std_logic;
  signal register2_q_net_x34: std_logic;
  signal register2_q_net_x35: std_logic;
  signal register2_q_net_x36: std_logic;
  signal register2_q_net_x37: std_logic;
  signal register2_q_net_x38: std_logic;
  signal register2_q_net_x39: std_logic;
  signal register2_q_net_x40: std_logic;
  signal register2_q_net_x41: std_logic;
  signal register30_q_net: std_logic_vector(7 downto 0);
  signal register32_q_net_x0: std_logic_vector(15 downto 0);
  signal register33_q_net_x0: std_logic_vector(9 downto 0);
  signal register34_q_net_x0: std_logic_vector(9 downto 0);
  signal register35_q_net_x0: std_logic;
  signal register36_q_net_x0: std_logic_vector(31 downto 0);
  signal register3_q_net: std_logic_vector(15 downto 0);
  signal register3_q_net_x4: std_logic;
  signal register3_q_net_x5: std_logic;
  signal register49_q_net: std_logic_vector(15 downto 0);
  signal register4_q_net: std_logic_vector(7 downto 0);
  signal register4_q_net_x4: std_logic;
  signal register4_q_net_x5: std_logic_vector(3 downto 0);
  signal register53_q_net_x1: std_logic_vector(5 downto 0);
  signal register55_q_net_x1: std_logic_vector(31 downto 0);
  signal register56_q_net_x1: std_logic_vector(5 downto 0);
  signal register57_q_net_x1: std_logic_vector(5 downto 0);
  signal register58_q_net_x1: std_logic_vector(5 downto 0);
  signal register59_q_net_x1: std_logic_vector(5 downto 0);
  signal register5_q_net: std_logic;
  signal register5_q_net_x1: std_logic;
  signal register60_q_net_x1: std_logic_vector(5 downto 0);
  signal register61_q_net_x1: std_logic_vector(5 downto 0);
  signal register66_q_net_x2: std_logic;
  signal register67_q_net_x2: std_logic;
  signal register68_q_net: std_logic_vector(31 downto 0);
  signal register69_q_net_x3: std_logic_vector(31 downto 0);
  signal register6_q_net_x1: std_logic;
  signal register6_q_net_x2: std_logic;
  signal register70_q_net: std_logic_vector(31 downto 0);
  signal register71_q_net_x3: std_logic_vector(31 downto 0);
  signal register7_q_net_x1: std_logic;
  signal register8_q_net_x1: std_logic;
  signal reinterpret_output_port_net_x2: std_logic_vector(7 downto 0);
  signal relational3_op_net: std_logic;
  signal x32lsb1_y_net_x1: std_logic_vector(31 downto 0);
  signal x32lsb2_y_net_x1: std_logic_vector(31 downto 0);
  signal x32lsb_y_net_x2: std_logic_vector(31 downto 0);
  signal x32msb1_y_net_x1: std_logic_vector(31 downto 0);
  signal x32msb2_y_net_x1: std_logic_vector(31 downto 0);
  signal x32msb_y_net_x2: std_logic_vector(31 downto 0);

begin
  ce_1_sg_x44 <= ce_1;
  clk_1_sg_x44 <= clk_1;
  from_register1_data_out_net_x1 <= from_register1;
  from_register10_data_out_net_x1 <= from_register10;
  from_register11_data_out_net_x1 <= from_register11;
  from_register12_data_out_net_x1 <= from_register12;
  from_register13_data_out_net_x1 <= from_register13;
  from_register14_data_out_net_x1 <= from_register14;
  from_register15_data_out_net_x0 <= from_register15;
  from_register16_data_out_net_x0 <= from_register16;
  from_register1_data_out_net_x2 <= from_register1_x0;
  from_register2_data_out_net_x0 <= from_register2;
  from_register3_data_out_net_x1 <= from_register3;
  from_register4_data_out_net_x0 <= from_register4;
  from_register5_data_out_net_x0 <= from_register5;
  from_register6_data_out_net_x0 <= from_register6;
  from_register7_data_out_net_x1 <= from_register7;
  from_register8_data_out_net_x0 <= from_register8;
  from_register9_data_out_net_x1 <= from_register9;
  mcode_tx_control_a_fsm_state_out_net_x0 <= mcode_tx_control_a;
  mcode_tx_control_b_fsm_state_out_net_x0 <= mcode_tx_control_b;
  logical3_y_net_x4 <= nav;
  bitsm_4_y_net_x1 <= nav_value_100nsec;
  register4_q_net_x4 <= nav_x0;
  delay_q_net_x2 <= o;
  register2_q_net_x30 <= o_x0;
  register2_q_net_x31 <= o_x1;
  register3_q_net_x4 <= o_x2;
  register2_q_net_x32 <= o_x3;
  phy_cca_ind_busy_net_x2 <= phy_cca_ind_busy;
  phy_rx_data_byte_net_x4 <= phy_rx_byte;
  phy_rx_data_ind_net_x4 <= phy_rx_byte_valid;
  phy_rx_data_bytenum_net_x4 <= phy_rx_bytenum;
  phy_rx_end_rxerror_net_x7 <= phy_rx_end_rxerror;
  phy_rx_params_length_net_x0 <= phy_rx_params_length;
  phy_rx_params_mcs_net_x0 <= phy_rx_params_mcs;
  phy_rx_params_phy_mode_net_x0 <= phy_rx_params_phy_mode;
  phy_rx_params_unsupported_net_x0 <= phy_rx_params_unsupported;
  phy_rx_params_ind_net_x0 <= phy_rx_params_valid;
  phy_rx_start_ind_net_x7 <= phy_rx_start_ind;
  phy_rx_start_phy_sel_net_x0 <= phy_rx_start_phy_sel;
  phy_tx_started_net_x3 <= phy_tx_started;
  register1_q_net_x4 <= register1_x0;
  register1_q_net_x5 <= register1_x1;
  register2_q_net_x37 <= register2_x0;
  register2_q_net_x38 <= register2_x1;
  register2_q_net_x39 <= register2_x2;
  register2_q_net_x40 <= register2_x3;
  register2_q_net_x33 <= rx_timers;
  register2_q_net_x34 <= rx_timers_x0;
  register2_q_net_x35 <= rx_timers_x1;
  register2_q_net_x36 <= rx_timers_x2;
  num_slots_op_net_x1 <= status_current_backoff_count;
  microsecond_counter_op_net_x2 <= x64_bit_usec_counter;
  constant1_x0 <= constant1_op_net_x1;
  constant2_x0 <= constant2_op_net_x0;
  constant3_x0 <= constant3_op_net_x0;
  convert1_x0 <= convert1_dout_net_x1;
  convert4_x0 <= convert4_dout_net_x0;
  convert6_x0 <= convert6_dout_net_x0;
  convert_x0 <= convert_dout_net_x0;
  ctrl_bits <= logical1_y_net_x5;
  ctrl_bits_x0 <= b_0_y_net_x7;
  ctrl_bits_x1 <= b_10_y_net_x1;
  ctrl_bits_x10 <= b_9_y_net_x1;
  ctrl_bits_x2 <= b_11_y_net_x1;
  ctrl_bits_x3 <= b_1_y_net_x3;
  ctrl_bits_x4 <= b_3_y_net_x1;
  ctrl_bits_x5 <= b_4_y_net_x2;
  ctrl_bits_x6 <= b_5_y_net_x2;
  ctrl_bits_x7 <= b_6_y_net_x2;
  ctrl_bits_x8 <= b_7_y_net_x1;
  ctrl_bits_x9 <= b_8_y_net_x1;
  reg_backoff_sw_numslots <= register20_q_net_x1;
  reg_backoff_sw_start <= register21_q_net_x1;
  reg_calibtime_txdifs <= concat1_y_net_x19;
  reg_interval_difs <= concat1_y_net_x16;
  reg_interval_eifs <= concat1_y_net_x18;
  reg_interval_slot <= concat1_y_net_x17;
  reg_nav_check_addr_1 <= register71_q_net_x3;
  reg_nav_check_addr_2 <= register69_q_net_x3;
  reg_nav_time_adj <= reinterpret_output_port_net_x2;
  reg_tx_start_a <= register35_q_net_x0;
  reg_tx_start_b <= register6_q_net_x1;
  register11_x0 <= register11_q_net_x0;
  status_register <= constant1_op_net_x2;
  status_register_x0 <= convert1_dout_net_x2;
  timestamp_regs_io <= x32lsb_y_net_x2;
  timestamp_regs_io_x0 <= x32lsb1_y_net_x1;
  timestamp_regs_io_x1 <= x32lsb2_y_net_x1;
  timestamp_regs_io_x10 <= register27_q_net_x2;
  timestamp_regs_io_x11 <= register28_q_net_x2;
  timestamp_regs_io_x12 <= register55_q_net_x1;
  timestamp_regs_io_x2 <= x32msb_y_net_x2;
  timestamp_regs_io_x3 <= x32msb1_y_net_x1;
  timestamp_regs_io_x4 <= x32msb2_y_net_x1;
  timestamp_regs_io_x5 <= constant5_op_net_x1;
  timestamp_regs_io_x6 <= constant6_op_net_x1;
  timestamp_regs_io_x7 <= convert5_dout_net_x1;
  timestamp_regs_io_x8 <= register15_q_net_x1;
  timestamp_regs_io_x9 <= register26_q_net_x1;
  tx_controller_regs <= register1_q_net_x6;
  tx_controller_regs_x0 <= register11_q_net_x2;
  tx_controller_regs_x1 <= register14_q_net_x2;
  tx_controller_regs_x10 <= register5_q_net_x1;
  tx_controller_regs_x11 <= register53_q_net_x1;
  tx_controller_regs_x12 <= register56_q_net_x1;
  tx_controller_regs_x13 <= register57_q_net_x1;
  tx_controller_regs_x14 <= register58_q_net_x1;
  tx_controller_regs_x15 <= register59_q_net_x1;
  tx_controller_regs_x16 <= register6_q_net_x2;
  tx_controller_regs_x17 <= register60_q_net_x1;
  tx_controller_regs_x18 <= register61_q_net_x1;
  tx_controller_regs_x19 <= register66_q_net_x2;
  tx_controller_regs_x2 <= register16_q_net_x1;
  tx_controller_regs_x20 <= register67_q_net_x2;
  tx_controller_regs_x21 <= register7_q_net_x1;
  tx_controller_regs_x22 <= register8_q_net_x1;
  tx_controller_regs_x23 <= concat1_y_net_x12;
  tx_controller_regs_x24 <= concat1_y_net_x13;
  tx_controller_regs_x25 <= concat1_y_net_x14;
  tx_controller_regs_x26 <= concat1_y_net_x15;
  tx_controller_regs_x3 <= register17_q_net_x1;
  tx_controller_regs_x4 <= register19_q_net_x1;
  tx_controller_regs_x5 <= register2_q_net_x41;
  tx_controller_regs_x6 <= register22_q_net_x1;
  tx_controller_regs_x7 <= register25_q_net_x1;
  tx_controller_regs_x8 <= register3_q_net_x5;
  tx_controller_regs_x9 <= register4_q_net_x5;

  b_0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 0,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register4_data_out_net_x0,
      y(0) => b_0_y_net
    );

  b_1: entity work.xlslice
    generic map (
      new_lsb => 1,
      new_msb => 1,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register4_data_out_net_x0,
      y(0) => b_1_y_net
    );

  b_15_0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 15,
      x_width => 32,
      y_width => 16
    )
    port map (
      x => from_register6_data_out_net_x0,
      y => b_15_0_y_net
    );

  b_15_0_2: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 15,
      x_width => 32,
      y_width => 16
    )
    port map (
      x => from_register1_data_out_net_x1,
      y => b_15_0_2_y_net
    );

  b_29_20: entity work.xlslice
    generic map (
      new_lsb => 20,
      new_msb => 29,
      x_width => 32,
      y_width => 10
    )
    port map (
      x => from_register5_data_out_net_x0,
      y => b_29_20_y_net
    );

  b_31: entity work.xlslice
    generic map (
      new_lsb => 31,
      new_msb => 31,
      x_width => 32,
      y_width => 1
    )
    port map (
      x => from_register1_data_out_net_x1,
      y(0) => b_31_y_net
    );

  b_31_24: entity work.xlslice
    generic map (
      new_lsb => 24,
      new_msb => 31,
      x_width => 32,
      y_width => 8
    )
    port map (
      x => from_register8_data_out_net_x0,
      y => b_31_24_y_net
    );

  b_9_0: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 9,
      x_width => 32,
      y_width => 10
    )
    port map (
      x => from_register5_data_out_net_x0,
      y => b_9_0_y_net
    );

  b_9_0_1: entity work.xlslice
    generic map (
      new_lsb => 0,
      new_msb => 9,
      x_width => 32,
      y_width => 10
    )
    port map (
      x => from_register8_data_out_net_x0,
      y => b_9_0_1_y_net
    );

  concat1: entity work.concat_04a248b81b
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      in0 => register4_q_net,
      in1 => register2_q_net,
      y => concat1_y_net
    );

  concat3: entity work.concat_16621e8277
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      in0(0) => phy_rx_start_phy_sel_net_x0,
      in1(0) => phy_rx_params_ind_net_x0,
      in2 => phy_rx_params_phy_mode_net_x0,
      in3(0) => relational3_op_net,
      in4(0) => phy_rx_params_unsupported_net_x0,
      in5 => phy_rx_params_mcs_net_x0,
      in6 => phy_rx_params_length_net_x0,
      y => concat3_y_net
    );

  constant1: entity work.constant_6293007044
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant1_op_net_x1
    );

  constant2: entity work.constant_6293007044
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant2_op_net_x0
    );

  constant3: entity work.constant_6293007044
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant3_op_net_x0
    );

  constant4: entity work.constant_963ed6358a
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => constant4_op_net
    );

  convert: entity work.xlconvert
    generic map (
      bool_conversion => 0,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 24,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 32,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      clr => '0',
      din => register10_q_net,
      en => "1",
      dout => convert_dout_net_x0
    );

  convert1: entity work.xlconvert
    generic map (
      bool_conversion => 0,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 16,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 32,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      clr => '0',
      din => register49_q_net,
      en => "1",
      dout => convert1_dout_net_x1
    );

  convert4: entity work.xlconvert
    generic map (
      bool_conversion => 0,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 30,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 32,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      clr => '0',
      din => register1_q_net,
      en => "1",
      dout => convert4_dout_net_x0
    );

  convert6: entity work.xlconvert
    generic map (
      bool_conversion => 0,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 16,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 32,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      clr => '0',
      din => register12_q_net,
      en => "1",
      dout => convert6_dout_net_x0
    );

  ctrl_bits_dfa8c81886: entity work.ctrl_bits_entity_dfa8c81886
    port map (
      ce_1 => ce_1_sg_x44,
      clk_1 => clk_1_sg_x44,
      x32b => register36_q_net_x0,
      global_reset => b_0_y_net_x7,
      reg_block_rx_clear => logical1_y_net_x5,
      reg_block_rx_on_fcs_good => b_1_y_net_x3,
      reg_block_rx_on_tx => b_4_y_net_x2,
      reg_block_rx_on_valid_rxend => b_6_y_net_x2,
      reg_cca_ignore_nav => b_9_y_net_x1,
      reg_cca_ignore_phy_cs => b_7_y_net_x1,
      reg_cca_ignore_txbusy => b_8_y_net_x1,
      reg_disable_nav => b_3_y_net_x1,
      reg_force_reset_backoff => b_11_y_net_x1,
      reg_force_reset_nav => b_10_y_net_x1,
      reg_update_timestamp => b_5_y_net_x2
    );

  logical: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => phy_rx_start_ind_net_x7,
      d1(0) => phy_rx_params_ind_net_x0,
      y(0) => logical_y_net_x0
    );

  posedge3_d0ff3f2c19: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x44,
      clk_1 => clk_1_sg_x44,
      d => logical_y_net_x0,
      q => logical1_y_net_x0
    );

  register1: entity work.xlregister
    generic map (
      d_width => 30,
      init_value => b"000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => concat3_y_net,
      en => "1",
      rst => "0",
      q => register1_q_net
    );

  register10: entity work.xlregister
    generic map (
      d_width => 24,
      init_value => b"000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => concat1_y_net,
      en(0) => register5_q_net,
      rst(0) => phy_rx_start_ind_net_x7,
      q => register10_q_net
    );

  register11: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d(0) => logical1_y_net_x0,
      en => "1",
      rst => "0",
      q(0) => register11_q_net_x0
    );

  register12: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => register13_q_net,
      en => "1",
      rst => "0",
      q => register12_q_net
    );

  register13: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => bitsm_4_y_net_x1,
      en => "1",
      rst => "0",
      q => register13_q_net
    );

  register2: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => phy_rx_data_bytenum_net_x4,
      en => "1",
      rst => "0",
      q => register2_q_net
    );

  register20: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => b_15_0_2_y_net,
      en => "1",
      rst => "0",
      q => register20_q_net_x1
    );

  register21: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d(0) => b_31_y_net,
      en => "1",
      rst => "0",
      q(0) => register21_q_net_x1
    );

  register29: entity work.xlregister
    generic map (
      d_width => 10,
      init_value => b"0000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => b_9_0_1_y_net,
      en => "1",
      rst => "0",
      q => register29_q_net_x0
    );

  register3: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => num_slots_op_net_x1,
      en => "1",
      rst => "0",
      q => register3_q_net
    );

  register30: entity work.xlregister
    generic map (
      d_width => 8,
      init_value => b"00000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => b_31_24_y_net,
      en => "1",
      rst => "0",
      q => register30_q_net
    );

  register32: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => b_15_0_y_net,
      en => "1",
      rst => "0",
      q => register32_q_net_x0
    );

  register33: entity work.xlregister
    generic map (
      d_width => 10,
      init_value => b"0000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => b_29_20_y_net,
      en => "1",
      rst => "0",
      q => register33_q_net_x0
    );

  register34: entity work.xlregister
    generic map (
      d_width => 10,
      init_value => b"0000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => b_9_0_y_net,
      en => "1",
      rst => "0",
      q => register34_q_net_x0
    );

  register35: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d(0) => b_0_y_net,
      en => "1",
      rst => "0",
      q(0) => register35_q_net_x0
    );

  register36: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => from_register2_data_out_net_x0,
      en => "1",
      rst => "0",
      q => register36_q_net_x0
    );

  register4: entity work.xlregister
    generic map (
      d_width => 8,
      init_value => b"00000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => phy_rx_data_byte_net_x4,
      en => "1",
      rst => "0",
      q => register4_q_net
    );

  register49: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => register3_q_net,
      en => "1",
      rst => "0",
      q => register49_q_net
    );

  register5: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d(0) => phy_rx_data_ind_net_x4,
      en => "1",
      rst => "0",
      q(0) => register5_q_net
    );

  register6: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d(0) => b_1_y_net,
      en => "1",
      rst => "0",
      q(0) => register6_q_net_x1
    );

  register68: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => from_register15_data_out_net_x0,
      en => "1",
      rst => "0",
      q => register68_q_net
    );

  register69: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => register68_q_net,
      en => "1",
      rst => "0",
      q => register69_q_net_x3
    );

  register70: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => from_register16_data_out_net_x0,
      en => "1",
      rst => "0",
      q => register70_q_net
    );

  register71: entity work.xlregister
    generic map (
      d_width => 32,
      init_value => b"00000000000000000000000000000000"
    )
    port map (
      ce => ce_1_sg_x44,
      clk => clk_1_sg_x44,
      d => register70_q_net,
      en => "1",
      rst => "0",
      q => register71_q_net_x3
    );

  reinterpret: entity work.reinterpret_4389dc89bf
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      input_port => register30_q_net,
      output_port => reinterpret_output_port_net_x2
    );

  relational3: entity work.relational_3c8242143a
    port map (
      a => phy_rx_end_rxerror_net_x7,
      b(0) => constant4_op_net,
      ce => '0',
      clk => '0',
      clr => '0',
      op(0) => relational3_op_net
    );

  status_register_1c7c355a6a: entity work.status_register_entity_1c7c355a6a
    port map (
      ce_1 => ce_1_sg_x44,
      clk_1 => clk_1_sg_x44,
      mac_nav_busy => logical3_y_net_x4,
      phy_cca_ind_busy => phy_cca_ind_busy_net_x2,
      status_blocked_on_good_fcs => register2_q_net_x30,
      status_blocked_on_rxend => register2_q_net_x31,
      status_nav_addr_match => register4_q_net_x4,
      status_postrx_timer1_running => register2_q_net_x35,
      status_postrx_timer2_running => register2_q_net_x36,
      status_posttx_timer1_running => register2_q_net_x33,
      status_posttx_timer2_running => register2_q_net_x34,
      status_rx_fcs_good => register3_q_net_x4,
      status_rx_phy_active => delay_q_net_x2,
      status_tx_a_done => register2_q_net_x38,
      status_tx_a_pending => register2_q_net_x37,
      status_tx_a_result => register1_q_net_x4,
      status_tx_a_state => mcode_tx_control_a_fsm_state_out_net_x0,
      status_tx_b_done => register2_q_net_x40,
      status_tx_b_pending => register2_q_net_x39,
      status_tx_b_result => register1_q_net_x5,
      status_tx_b_state => mcode_tx_control_b_fsm_state_out_net_x0,
      status_tx_phy_active => register2_q_net_x32,
      constant1_x0 => constant1_op_net_x2,
      convert1_x0 => convert1_dout_net_x2
    );

  timestamp_regs_io_feb7327f6b: entity work.\timestamp_regs___io_entity_feb7327f6b\
    port map (
      ce_1 => ce_1_sg_x44,
      clk_1 => clk_1_sg_x44,
      from_register10 => from_register10_data_out_net_x1,
      from_register11 => from_register11_data_out_net_x1,
      from_register13 => from_register13_data_out_net_x1,
      microsecond_timestamp => microsecond_counter_op_net_x2,
      phy_rx_start_ind => phy_rx_start_ind_net_x7,
      phy_tx_start_confirm => phy_tx_started_net_x3,
      constant5_x0 => constant5_op_net_x1,
      constant6_x0 => constant6_op_net_x1,
      convert5_x0 => convert5_dout_net_x1,
      reg_set_timestamp_lsb => register28_q_net_x2,
      reg_set_timestamp_msb => register27_q_net_x2,
      register15_x0 => register15_q_net_x1,
      register26_x0 => register26_q_net_x1,
      register55_x0 => register55_q_net_x1,
      x32lsb1_x0 => x32lsb1_y_net_x1,
      x32lsb2_x0 => x32lsb2_y_net_x1,
      x32lsb_x1 => x32lsb_y_net_x2,
      x32msb1_x0 => x32msb1_y_net_x1,
      x32msb2_x0 => x32msb2_y_net_x1,
      x32msb_x1 => x32msb_y_net_x2
    );

  tx_controller_regs_8d6ee7f5ae: entity work.tx_controller_regs_entity_8d6ee7f5ae
    port map (
      ce_1 => ce_1_sg_x44,
      clk_1 => clk_1_sg_x44,
      from_register1 => from_register1_data_out_net_x2,
      from_register12 => from_register12_data_out_net_x1,
      from_register14 => from_register14_data_out_net_x1,
      from_register3 => from_register3_data_out_net_x1,
      from_register7 => from_register7_data_out_net_x1,
      from_register9 => from_register9_data_out_net_x1,
      reg_postrx_timer1_countto => concat1_y_net_x15,
      reg_postrx_timer1_en => register66_q_net_x2,
      reg_postrx_timer2_countto => concat1_y_net_x13,
      reg_postrx_timer2_en => register67_q_net_x2,
      reg_posttx_timer1_countto => concat1_y_net_x14,
      reg_posttx_timer1_en => register11_q_net_x2,
      reg_posttx_timer2_countto => concat1_y_net_x12,
      reg_posttx_timer2_en => register14_q_net_x2,
      reg_tx_a_param_bo_slots => register17_q_net_x1,
      reg_tx_a_param_pktbuf => register16_q_net_x1,
      reg_tx_a_param_postwait_posttxtimer2 => register3_q_net_x5,
      reg_tx_a_param_prewait_postrxtimer1 => register1_q_net_x6,
      reg_tx_a_param_prewait_posttxtimer1 => register2_q_net_x41,
      reg_tx_a_param_txantmask => register25_q_net_x1,
      reg_tx_a_param_txgain_rfa => register19_q_net_x1,
      reg_tx_a_param_txgain_rfb => register53_q_net_x1,
      reg_tx_a_param_txgain_rfc => register56_q_net_x1,
      reg_tx_a_param_txgain_rfd => register57_q_net_x1,
      reg_tx_b_param_pktbuf => register22_q_net_x1,
      reg_tx_b_param_postwait_posttxtimer1 => register7_q_net_x1,
      reg_tx_b_param_prewait_postrxtimer1 => register5_q_net_x1,
      reg_tx_b_param_prewait_postrxtimer2 => register6_q_net_x2,
      reg_tx_b_param_req_zero_nav => register8_q_net_x1,
      reg_tx_b_param_txantmask => register4_q_net_x5,
      reg_tx_b_param_txgain_rfa => register58_q_net_x1,
      reg_tx_b_param_txgain_rfb => register59_q_net_x1,
      reg_tx_b_param_txgain_rfc => register60_q_net_x1,
      reg_tx_b_param_txgain_rfd => register61_q_net_x1
    );

  x1_fdf9c2a3eb: entity work.x1_entity_fdf9c2a3eb
    port map (
      a => register33_q_net_x0,
      ax16 => concat1_y_net_x16
    );

  x3_9291d02f53: entity work.x1_entity_fdf9c2a3eb
    port map (
      a => register34_q_net_x0,
      ax16 => concat1_y_net_x17
    );

  x5_99d1738aaf: entity work.x5_entity_99d1738aaf
    port map (
      a => register32_q_net_x0,
      ax16 => concat1_y_net_x18
    );

  x8_1e14ef55be: entity work.x1_entity_fdf9c2a3eb
    port map (
      a => register29_q_net_x0,
      ax16 => concat1_y_net_x19
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Tx Control A"

entity tx_control_a_entity_717cde016b is
  port (
    backoff_done: in std_logic; 
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    global_reset: in std_logic; 
    idle_for_difs: in std_logic; 
    phy_rx_start_ind: in std_logic; 
    phy_tx_end_confirm: in std_logic; 
    postrx_timer1_done: in std_logic; 
    posttx_timer1_done: in std_logic; 
    posttx_timer2_done: in std_logic; 
    reg_tx_a_param_bo_slots: in std_logic_vector(15 downto 0); 
    reg_tx_a_param_pktbuf: in std_logic_vector(3 downto 0); 
    reg_tx_a_param_postwait_posttxtimer2: in std_logic; 
    reg_tx_a_param_prewait_postrxtimer1: in std_logic; 
    reg_tx_a_param_prewait_posttxtimer1: in std_logic; 
    reg_tx_a_param_txantmask: in std_logic_vector(3 downto 0); 
    reg_tx_a_param_txgain_rfa: in std_logic_vector(5 downto 0); 
    reg_tx_a_param_txgain_rfb: in std_logic_vector(5 downto 0); 
    reg_tx_a_param_txgain_rfc: in std_logic_vector(5 downto 0); 
    reg_tx_a_param_txgain_rfd: in std_logic_vector(5 downto 0); 
    reg_tx_start_a: in std_logic; 
    register4_x0: out std_logic; 
    status_tx_a_done: out std_logic; 
    status_tx_a_pending: out std_logic; 
    status_tx_a_result: out std_logic_vector(1 downto 0); 
    status_tx_a_state: out std_logic_vector(2 downto 0); 
    tx_a_backoff_start: out std_logic; 
    tx_a_num_bo_slots: out std_logic_vector(15 downto 0); 
    tx_a_param_txantmask: out std_logic_vector(3 downto 0); 
    tx_a_param_txgain_a: out std_logic_vector(5 downto 0); 
    tx_a_param_txgain_b: out std_logic_vector(5 downto 0); 
    tx_a_param_txgain_c: out std_logic_vector(5 downto 0); 
    tx_a_param_txgain_d: out std_logic_vector(5 downto 0); 
    tx_a_phy_start: out std_logic; 
    tx_a_pktbuf: out std_logic_vector(3 downto 0)
  );
end tx_control_a_entity_717cde016b;

architecture structural of tx_control_a_entity_717cde016b is
  signal b_0_y_net_x8: std_logic;
  signal ce_1_sg_x49: std_logic;
  signal clk_1_sg_x49: std_logic;
  signal convert1_dout_net_x4: std_logic;
  signal convert3_dout_net_x0: std_logic;
  signal convert_dout_net_x2: std_logic;
  signal delay_q_net: std_logic;
  signal logical1_y_net_x0: std_logic;
  signal logical1_y_net_x1: std_logic;
  signal logical1_y_net_x2: std_logic;
  signal logical2_y_net_x0: std_logic;
  signal logical5_y_net_x2: std_logic;
  signal mcode_tx_control_a_backoff_start_net: std_logic;
  signal mcode_tx_control_a_fsm_state_out_net_x1: std_logic_vector(2 downto 0);
  signal mcode_tx_control_a_phy_tx_start_net: std_logic;
  signal mcode_tx_control_a_tx_done_net: std_logic;
  signal mcode_tx_control_a_tx_result_out_net: std_logic_vector(1 downto 0);
  signal phy_rx_start_ind_net_x8: std_logic;
  signal phy_tx_done_net_x3: std_logic;
  signal register10_q_net_x4: std_logic_vector(5 downto 0);
  signal register11_q_net: std_logic;
  signal register12_q_net: std_logic;
  signal register16_q_net_x2: std_logic_vector(3 downto 0);
  signal register17_q_net_x2: std_logic_vector(15 downto 0);
  signal register19_q_net_x2: std_logic_vector(5 downto 0);
  signal register1_q_net_x1: std_logic;
  signal register1_q_net_x7: std_logic;
  signal register1_q_net_x8: std_logic_vector(1 downto 0);
  signal register25_q_net_x2: std_logic_vector(3 downto 0);
  signal register2_q_net_x42: std_logic;
  signal register2_q_net_x43: std_logic_vector(3 downto 0);
  signal register2_q_net_x44: std_logic;
  signal register2_q_net_x45: std_logic;
  signal register2_q_net_x5: std_logic;
  signal register35_q_net_x2: std_logic;
  signal register3_q_net_x1: std_logic_vector(15 downto 0);
  signal register3_q_net_x6: std_logic;
  signal register4_q_net_x0: std_logic;
  signal register53_q_net_x2: std_logic_vector(5 downto 0);
  signal register56_q_net_x2: std_logic_vector(5 downto 0);
  signal register57_q_net_x2: std_logic_vector(5 downto 0);
  signal register5_q_net: std_logic;
  signal register6_q_net_x6: std_logic_vector(5 downto 0);
  signal register7_q_net_x6: std_logic_vector(3 downto 0);
  signal register8_q_net_x4: std_logic;
  signal register8_q_net_x5: std_logic_vector(5 downto 0);
  signal register9_q_net_x4: std_logic_vector(5 downto 0);
  signal register_q_net: std_logic;
  signal relational3_op_net_x1: std_logic;

begin
  logical5_y_net_x2 <= backoff_done;
  ce_1_sg_x49 <= ce_1;
  clk_1_sg_x49 <= clk_1;
  b_0_y_net_x8 <= global_reset;
  relational3_op_net_x1 <= idle_for_difs;
  phy_rx_start_ind_net_x8 <= phy_rx_start_ind;
  phy_tx_done_net_x3 <= phy_tx_end_confirm;
  register8_q_net_x4 <= postrx_timer1_done;
  register1_q_net_x1 <= posttx_timer1_done;
  register2_q_net_x5 <= posttx_timer2_done;
  register17_q_net_x2 <= reg_tx_a_param_bo_slots;
  register16_q_net_x2 <= reg_tx_a_param_pktbuf;
  register3_q_net_x6 <= reg_tx_a_param_postwait_posttxtimer2;
  register1_q_net_x7 <= reg_tx_a_param_prewait_postrxtimer1;
  register2_q_net_x42 <= reg_tx_a_param_prewait_posttxtimer1;
  register25_q_net_x2 <= reg_tx_a_param_txantmask;
  register19_q_net_x2 <= reg_tx_a_param_txgain_rfa;
  register53_q_net_x2 <= reg_tx_a_param_txgain_rfb;
  register56_q_net_x2 <= reg_tx_a_param_txgain_rfc;
  register57_q_net_x2 <= reg_tx_a_param_txgain_rfd;
  register35_q_net_x2 <= reg_tx_start_a;
  register4_x0 <= register4_q_net_x0;
  status_tx_a_done <= register2_q_net_x45;
  status_tx_a_pending <= register2_q_net_x44;
  status_tx_a_result <= register1_q_net_x8;
  status_tx_a_state <= mcode_tx_control_a_fsm_state_out_net_x1;
  tx_a_backoff_start <= convert_dout_net_x2;
  tx_a_num_bo_slots <= register3_q_net_x1;
  tx_a_param_txantmask <= register7_q_net_x6;
  tx_a_param_txgain_a <= register6_q_net_x6;
  tx_a_param_txgain_b <= register8_q_net_x5;
  tx_a_param_txgain_c <= register9_q_net_x4;
  tx_a_param_txgain_d <= register10_q_net_x4;
  tx_a_phy_start <= convert1_dout_net_x4;
  tx_a_pktbuf <= register2_q_net_x43;

  convert: entity work.xlconvert
    generic map (
      bool_conversion => 1,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 1,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 1,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      clr => '0',
      din(0) => mcode_tx_control_a_backoff_start_net,
      en => "1",
      dout(0) => convert_dout_net_x2
    );

  convert1: entity work.xlconvert
    generic map (
      bool_conversion => 1,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 1,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 1,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      clr => '0',
      din(0) => mcode_tx_control_a_phy_tx_start_net,
      en => "1",
      dout(0) => convert1_dout_net_x4
    );

  convert3: entity work.xlconvert
    generic map (
      bool_conversion => 1,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 1,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 1,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      clr => '0',
      din(0) => mcode_tx_control_a_tx_done_net,
      en => "1",
      dout(0) => convert3_dout_net_x0
    );

  delay: entity work.xldelay
    generic map (
      latency => 1,
      reg_retiming => 0,
      reset => 0,
      width => 1
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d(0) => logical1_y_net_x0,
      en => '1',
      rst => '1',
      q(0) => delay_q_net
    );

  logical1: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => b_0_y_net_x8,
      d1(0) => convert3_dout_net_x0,
      y(0) => logical1_y_net_x1
    );

  logical2: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x0,
      d1(0) => b_0_y_net_x8,
      y(0) => logical2_y_net_x0
    );

  mcode_tx_control_a: entity work.mcode_block_9fcb5ce515
    port map (
      backoff_done(0) => logical5_y_net_x2,
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      clr => '0',
      idle_for_difs(0) => relational3_op_net_x1,
      new_tx(0) => delay_q_net,
      phy_rx_start(0) => phy_rx_start_ind_net_x8,
      phy_tx_done(0) => phy_tx_done_net_x3,
      post_wait_posttxtimer2(0) => register5_q_net,
      postrxtimer1_done(0) => register8_q_net_x4,
      posttxtimer1_done(0) => register1_q_net_x1,
      posttxtimer2_done(0) => register2_q_net_x5,
      pre_wait_postrxtimer1(0) => register12_q_net,
      pre_wait_posttxtimer1(0) => register11_q_net,
      reset(0) => b_0_y_net_x8,
      backoff_start(0) => mcode_tx_control_a_backoff_start_net,
      fsm_state_out => mcode_tx_control_a_fsm_state_out_net_x1,
      phy_tx_start(0) => mcode_tx_control_a_phy_tx_start_net,
      tx_done(0) => mcode_tx_control_a_tx_done_net,
      tx_result_out => mcode_tx_control_a_tx_result_out_net
    );

  posedge1_fc1434a21a: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x49,
      clk_1 => clk_1_sg_x49,
      d => register35_q_net_x2,
      q => logical1_y_net_x2
    );

  posedge2_dfb3aee4c2: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x49,
      clk_1 => clk_1_sg_x49,
      d => register2_q_net_x44,
      q => logical1_y_net_x0
    );

  register1: entity work.xlregister
    generic map (
      d_width => 2,
      init_value => b"00"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d => mcode_tx_control_a_tx_result_out_net,
      en(0) => convert3_dout_net_x0,
      rst => "0",
      q => register1_q_net_x8
    );

  register10: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d => register57_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register10_q_net_x4
    );

  register11: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d(0) => register2_q_net_x42,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q(0) => register11_q_net
    );

  register12: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d(0) => register1_q_net_x7,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q(0) => register12_q_net
    );

  register2: entity work.xlregister
    generic map (
      d_width => 4,
      init_value => b"0000"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d => register16_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register2_q_net_x43
    );

  register3: entity work.xlregister
    generic map (
      d_width => 16,
      init_value => b"0000000000000000"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d => register17_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register3_q_net_x1
    );

  register4: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d(0) => register_q_net,
      en => "1",
      rst => "0",
      q(0) => register4_q_net_x0
    );

  register5: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d(0) => register3_q_net_x6,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q(0) => register5_q_net
    );

  register6: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d => register19_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register6_q_net_x6
    );

  register7: entity work.xlregister
    generic map (
      d_width => 4,
      init_value => b"0000"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d => register25_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register7_q_net_x6
    );

  register8: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d => register53_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register8_q_net_x5
    );

  register9: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d => register56_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register9_q_net_x4
    );

  register_x0: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x49,
      clk => clk_1_sg_x49,
      d(0) => register2_q_net_x44,
      en => "1",
      rst => "0",
      q(0) => register_q_net
    );

  s_r_latch1_8fa5bed45d: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x49,
      clk_1 => clk_1_sg_x49,
      r => logical1_y_net_x1,
      s => logical1_y_net_x2,
      q => register2_q_net_x44
    );

  s_r_latch2_44111b72d2: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x49,
      clk_1 => clk_1_sg_x49,
      r => logical2_y_net_x0,
      s => convert3_dout_net_x0,
      q => register2_q_net_x45
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw/Tx Control B"

entity tx_control_b_entity_bee87440a6 is
  port (
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    global_reset: in std_logic; 
    nav_zero: in std_logic; 
    phy_tx_end_confirm: in std_logic; 
    postrx_timer1_done: in std_logic; 
    postrx_timer2_done: in std_logic; 
    posttx_timer1_done: in std_logic; 
    reg_tx_b_param_pktbuf: in std_logic_vector(3 downto 0); 
    reg_tx_b_param_postwait_posttxtimer1: in std_logic; 
    reg_tx_b_param_prewait_postrxtimer1: in std_logic; 
    reg_tx_b_param_prewait_postrxtimer2: in std_logic; 
    reg_tx_b_param_req_zero_nav: in std_logic; 
    reg_tx_b_param_txantmask: in std_logic_vector(3 downto 0); 
    reg_tx_b_param_txgain_rfa: in std_logic_vector(5 downto 0); 
    reg_tx_b_param_txgain_rfb: in std_logic_vector(5 downto 0); 
    reg_tx_b_param_txgain_rfc: in std_logic_vector(5 downto 0); 
    reg_tx_b_param_txgain_rfd: in std_logic_vector(5 downto 0); 
    reg_tx_start_b: in std_logic; 
    register4_x0: out std_logic; 
    status_tx_b_done: out std_logic; 
    status_tx_b_pending: out std_logic; 
    status_tx_b_result: out std_logic_vector(1 downto 0); 
    status_tx_b_state: out std_logic_vector(2 downto 0); 
    tx_b_param_txantmask: out std_logic_vector(3 downto 0); 
    tx_b_param_txgain_a: out std_logic_vector(5 downto 0); 
    tx_b_param_txgain_b: out std_logic_vector(5 downto 0); 
    tx_b_param_txgain_c: out std_logic_vector(5 downto 0); 
    tx_b_param_txgain_d: out std_logic_vector(5 downto 0); 
    tx_b_phy_start: out std_logic; 
    tx_b_pktbuf: out std_logic_vector(3 downto 0)
  );
end tx_control_b_entity_bee87440a6;

architecture structural of tx_control_b_entity_bee87440a6 is
  signal b_0_y_net_x9: std_logic;
  signal ce_1_sg_x54: std_logic;
  signal clk_1_sg_x54: std_logic;
  signal convert1_dout_net_x5: std_logic;
  signal convert3_dout_net_x0: std_logic;
  signal delay_q_net: std_logic;
  signal inverter1_op_net_x1: std_logic;
  signal logical1_y_net_x0: std_logic;
  signal logical1_y_net_x1: std_logic;
  signal logical1_y_net_x2: std_logic;
  signal logical2_y_net_x0: std_logic;
  signal mcode_tx_control_b_fsm_state_out_net_x1: std_logic_vector(2 downto 0);
  signal mcode_tx_control_b_phy_tx_start_net: std_logic;
  signal mcode_tx_control_b_tx_done_net: std_logic;
  signal mcode_tx_control_b_tx_result_out_net: std_logic_vector(1 downto 0);
  signal phy_tx_done_net_x4: std_logic;
  signal register10_q_net_x5: std_logic_vector(5 downto 0);
  signal register11_q_net: std_logic;
  signal register12_q_net: std_logic;
  signal register13_q_net: std_logic;
  signal register1_q_net_x2: std_logic;
  signal register1_q_net_x6: std_logic_vector(1 downto 0);
  signal register22_q_net_x2: std_logic_vector(3 downto 0);
  signal register2_q_net_x43: std_logic_vector(3 downto 0);
  signal register2_q_net_x44: std_logic;
  signal register2_q_net_x45: std_logic;
  signal register4_q_net_x0: std_logic;
  signal register4_q_net_x6: std_logic_vector(3 downto 0);
  signal register58_q_net_x2: std_logic_vector(5 downto 0);
  signal register59_q_net_x2: std_logic_vector(5 downto 0);
  signal register5_q_net: std_logic;
  signal register5_q_net_x2: std_logic;
  signal register60_q_net_x2: std_logic_vector(5 downto 0);
  signal register61_q_net_x2: std_logic_vector(5 downto 0);
  signal register6_q_net_x4: std_logic;
  signal register6_q_net_x7: std_logic;
  signal register6_q_net_x8: std_logic_vector(5 downto 0);
  signal register7_q_net_x2: std_logic;
  signal register7_q_net_x7: std_logic_vector(3 downto 0);
  signal register8_q_net_x6: std_logic;
  signal register8_q_net_x7: std_logic;
  signal register8_q_net_x8: std_logic_vector(5 downto 0);
  signal register9_q_net_x1: std_logic;
  signal register9_q_net_x5: std_logic_vector(5 downto 0);
  signal register_q_net: std_logic;

begin
  ce_1_sg_x54 <= ce_1;
  clk_1_sg_x54 <= clk_1;
  b_0_y_net_x9 <= global_reset;
  inverter1_op_net_x1 <= nav_zero;
  phy_tx_done_net_x4 <= phy_tx_end_confirm;
  register8_q_net_x6 <= postrx_timer1_done;
  register9_q_net_x1 <= postrx_timer2_done;
  register1_q_net_x2 <= posttx_timer1_done;
  register22_q_net_x2 <= reg_tx_b_param_pktbuf;
  register7_q_net_x2 <= reg_tx_b_param_postwait_posttxtimer1;
  register5_q_net_x2 <= reg_tx_b_param_prewait_postrxtimer1;
  register6_q_net_x7 <= reg_tx_b_param_prewait_postrxtimer2;
  register8_q_net_x7 <= reg_tx_b_param_req_zero_nav;
  register4_q_net_x6 <= reg_tx_b_param_txantmask;
  register58_q_net_x2 <= reg_tx_b_param_txgain_rfa;
  register59_q_net_x2 <= reg_tx_b_param_txgain_rfb;
  register60_q_net_x2 <= reg_tx_b_param_txgain_rfc;
  register61_q_net_x2 <= reg_tx_b_param_txgain_rfd;
  register6_q_net_x4 <= reg_tx_start_b;
  register4_x0 <= register4_q_net_x0;
  status_tx_b_done <= register2_q_net_x45;
  status_tx_b_pending <= register2_q_net_x44;
  status_tx_b_result <= register1_q_net_x6;
  status_tx_b_state <= mcode_tx_control_b_fsm_state_out_net_x1;
  tx_b_param_txantmask <= register7_q_net_x7;
  tx_b_param_txgain_a <= register6_q_net_x8;
  tx_b_param_txgain_b <= register8_q_net_x8;
  tx_b_param_txgain_c <= register9_q_net_x5;
  tx_b_param_txgain_d <= register10_q_net_x5;
  tx_b_phy_start <= convert1_dout_net_x5;
  tx_b_pktbuf <= register2_q_net_x43;

  convert1: entity work.xlconvert
    generic map (
      bool_conversion => 1,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 1,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 1,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      clr => '0',
      din(0) => mcode_tx_control_b_phy_tx_start_net,
      en => "1",
      dout(0) => convert1_dout_net_x5
    );

  convert3: entity work.xlconvert
    generic map (
      bool_conversion => 1,
      din_arith => 1,
      din_bin_pt => 0,
      din_width => 1,
      dout_arith => 1,
      dout_bin_pt => 0,
      dout_width => 1,
      latency => 0,
      overflow => xlWrap,
      quantization => xlTruncate
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      clr => '0',
      din(0) => mcode_tx_control_b_tx_done_net,
      en => "1",
      dout(0) => convert3_dout_net_x0
    );

  delay: entity work.xldelay
    generic map (
      latency => 1,
      reg_retiming => 0,
      reset => 0,
      width => 1
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d(0) => logical1_y_net_x0,
      en => '1',
      rst => '1',
      q(0) => delay_q_net
    );

  logical1: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => b_0_y_net_x9,
      d1(0) => convert3_dout_net_x0,
      y(0) => logical1_y_net_x1
    );

  logical2: entity work.logical_aacf6e1b0e
    port map (
      ce => '0',
      clk => '0',
      clr => '0',
      d0(0) => logical1_y_net_x0,
      d1(0) => b_0_y_net_x9,
      y(0) => logical2_y_net_x0
    );

  mcode_tx_control_b: entity work.mcode_block_249e341dc6
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      clr => '0',
      nav_zero(0) => inverter1_op_net_x1,
      new_tx(0) => delay_q_net,
      phy_tx_done(0) => phy_tx_done_net_x4,
      postrxtimer1_done(0) => register8_q_net_x6,
      postrxtimer2_done(0) => register9_q_net_x1,
      posttxtimer1_done(0) => register1_q_net_x2,
      pre_wait_postrxtimer1(0) => register12_q_net,
      pre_wait_postrxtimer2(0) => register11_q_net,
      pre_wait_posttxtimer1(0) => register5_q_net,
      req_zero_nav(0) => register13_q_net,
      reset(0) => b_0_y_net_x9,
      fsm_state_out => mcode_tx_control_b_fsm_state_out_net_x1,
      phy_tx_start(0) => mcode_tx_control_b_phy_tx_start_net,
      tx_done(0) => mcode_tx_control_b_tx_done_net,
      tx_result_out => mcode_tx_control_b_tx_result_out_net
    );

  posedge1_fe6de1c653: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x54,
      clk_1 => clk_1_sg_x54,
      d => register6_q_net_x4,
      q => logical1_y_net_x2
    );

  posedge2_048b71aa37: entity work.posedge2_entity_ec1bb5d558
    port map (
      ce_1 => ce_1_sg_x54,
      clk_1 => clk_1_sg_x54,
      d => register2_q_net_x44,
      q => logical1_y_net_x0
    );

  register1: entity work.xlregister
    generic map (
      d_width => 2,
      init_value => b"00"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d => mcode_tx_control_b_tx_result_out_net,
      en(0) => convert3_dout_net_x0,
      rst => "0",
      q => register1_q_net_x6
    );

  register10: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d => register61_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register10_q_net_x5
    );

  register11: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d(0) => register6_q_net_x7,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q(0) => register11_q_net
    );

  register12: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d(0) => register5_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q(0) => register12_q_net
    );

  register13: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d(0) => register8_q_net_x7,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q(0) => register13_q_net
    );

  register2: entity work.xlregister
    generic map (
      d_width => 4,
      init_value => b"0000"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d => register22_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register2_q_net_x43
    );

  register4: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d(0) => register_q_net,
      en => "1",
      rst => "0",
      q(0) => register4_q_net_x0
    );

  register5: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d(0) => register7_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q(0) => register5_q_net
    );

  register6: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d => register58_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register6_q_net_x8
    );

  register7: entity work.xlregister
    generic map (
      d_width => 4,
      init_value => b"0000"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d => register4_q_net_x6,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register7_q_net_x7
    );

  register8: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d => register59_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register8_q_net_x8
    );

  register9: entity work.xlregister
    generic map (
      d_width => 6,
      init_value => b"000000"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d => register60_q_net_x2,
      en(0) => logical1_y_net_x0,
      rst => "0",
      q => register9_q_net_x5
    );

  register_x0: entity work.xlregister
    generic map (
      d_width => 1,
      init_value => b"0"
    )
    port map (
      ce => ce_1_sg_x54,
      clk => clk_1_sg_x54,
      d(0) => register2_q_net_x44,
      en => "1",
      rst => "0",
      q(0) => register_q_net
    );

  s_r_latch1_f90d405c26: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x54,
      clk_1 => clk_1_sg_x54,
      r => logical1_y_net_x1,
      s => logical1_y_net_x2,
      q => register2_q_net_x44
    );

  s_r_latch2_ea270a001b: entity work.s_r_latch1_entity_65359461e7
    port map (
      ce_1 => ce_1_sg_x54,
      clk_1 => clk_1_sg_x54,
      r => logical2_y_net_x0,
      s => convert3_dout_net_x0,
      q => register2_q_net_x45
    );

end structural;
library IEEE;
use IEEE.std_logic_1164.all;
use work.conv_pkg.all;

-- Generated from Simulink block "wlan_mac_hw"

entity wlan_mac_hw is
  port (
    axi_aresetn: in std_logic; 
    ce_1: in std_logic; 
    clk_1: in std_logic; 
    data_out: in std_logic_vector(31 downto 0); 
    data_out_x0: in std_logic_vector(31 downto 0); 
    data_out_x1: in std_logic_vector(31 downto 0); 
    data_out_x10: in std_logic_vector(31 downto 0); 
    data_out_x11: in std_logic_vector(31 downto 0); 
    data_out_x12: in std_logic_vector(31 downto 0); 
    data_out_x13: in std_logic_vector(31 downto 0); 
    data_out_x14: in std_logic_vector(31 downto 0); 
    data_out_x15: in std_logic_vector(31 downto 0); 
    data_out_x16: in std_logic_vector(31 downto 0); 
    data_out_x17: in std_logic_vector(31 downto 0); 
    data_out_x18: in std_logic_vector(31 downto 0); 
    data_out_x19: in std_logic_vector(31 downto 0); 
    data_out_x2: in std_logic_vector(31 downto 0); 
    data_out_x20: in std_logic_vector(31 downto 0); 
    data_out_x21: in std_logic_vector(31 downto 0); 
    data_out_x22: in std_logic_vector(31 downto 0); 
    data_out_x23: in std_logic_vector(31 downto 0); 
    data_out_x24: in std_logic_vector(31 downto 0); 
    data_out_x25: in std_logic_vector(31 downto 0); 
    data_out_x26: in std_logic_vector(31 downto 0); 
    data_out_x3: in std_logic_vector(31 downto 0); 
    data_out_x4: in std_logic_vector(31 downto 0); 
    data_out_x5: in std_logic_vector(31 downto 0); 
    data_out_x6: in std_logic_vector(31 downto 0); 
    data_out_x7: in std_logic_vector(31 downto 0); 
    data_out_x8: in std_logic_vector(31 downto 0); 
    data_out_x9: in std_logic_vector(31 downto 0); 
    dout: in std_logic_vector(31 downto 0); 
    dout_x0: in std_logic_vector(31 downto 0); 
    dout_x1: in std_logic_vector(31 downto 0); 
    dout_x10: in std_logic_vector(31 downto 0); 
    dout_x11: in std_logic_vector(31 downto 0); 
    dout_x12: in std_logic_vector(31 downto 0); 
    dout_x13: in std_logic_vector(31 downto 0); 
    dout_x14: in std_logic_vector(31 downto 0); 
    dout_x15: in std_logic_vector(31 downto 0); 
    dout_x2: in std_logic_vector(31 downto 0); 
    dout_x3: in std_logic_vector(31 downto 0); 
    dout_x4: in std_logic_vector(31 downto 0); 
    dout_x5: in std_logic_vector(31 downto 0); 
    dout_x6: in std_logic_vector(31 downto 0); 
    dout_x7: in std_logic_vector(31 downto 0); 
    dout_x8: in std_logic_vector(31 downto 0); 
    dout_x9: in std_logic_vector(31 downto 0); 
    phy_cca_ind_busy: in std_logic; 
    phy_rx_data_byte: in std_logic_vector(7 downto 0); 
    phy_rx_data_bytenum: in std_logic_vector(15 downto 0); 
    phy_rx_data_done_ind: in std_logic; 
    phy_rx_data_ind: in std_logic; 
    phy_rx_end_ind: in std_logic; 
    phy_rx_end_rxerror: in std_logic_vector(3 downto 0); 
    phy_rx_fcs_good_ind: in std_logic; 
    phy_rx_params_ind: in std_logic; 
    phy_rx_params_length: in std_logic_vector(15 downto 0); 
    phy_rx_params_mcs: in std_logic_vector(6 downto 0); 
    phy_rx_params_phy_mode: in std_logic_vector(2 downto 0); 
    phy_rx_params_unsupported: in std_logic; 
    phy_rx_start_ind: in std_logic; 
    phy_rx_start_phy_sel: in std_logic; 
    phy_tx_done: in std_logic; 
    phy_tx_started: in std_logic; 
    plb_ce_1: in std_logic; 
    plb_clk_1: in std_logic; 
    s_axi_araddr: in std_logic_vector(31 downto 0); 
    s_axi_arburst: in std_logic_vector(1 downto 0); 
    s_axi_arcache: in std_logic_vector(3 downto 0); 
    s_axi_arid: in std_logic_vector(7 downto 0); 
    s_axi_arlen: in std_logic_vector(7 downto 0); 
    s_axi_arlock: in std_logic_vector(1 downto 0); 
    s_axi_arprot: in std_logic_vector(2 downto 0); 
    s_axi_arsize: in std_logic_vector(2 downto 0); 
    s_axi_arvalid: in std_logic; 
    s_axi_awaddr: in std_logic_vector(31 downto 0); 
    s_axi_awburst: in std_logic_vector(1 downto 0); 
    s_axi_awcache: in std_logic_vector(3 downto 0); 
    s_axi_awid: in std_logic_vector(7 downto 0); 
    s_axi_awlen: in std_logic_vector(7 downto 0); 
    s_axi_awlock: in std_logic_vector(1 downto 0); 
    s_axi_awprot: in std_logic_vector(2 downto 0); 
    s_axi_awsize: in std_logic_vector(2 downto 0); 
    s_axi_awvalid: in std_logic; 
    s_axi_bready: in std_logic; 
    s_axi_rready: in std_logic; 
    s_axi_wdata: in std_logic_vector(31 downto 0); 
    s_axi_wlast: in std_logic; 
    s_axi_wstrb: in std_logic_vector(3 downto 0); 
    s_axi_wvalid: in std_logic; 
    data_in: out std_logic_vector(31 downto 0); 
    data_in_x0: out std_logic_vector(31 downto 0); 
    data_in_x1: out std_logic_vector(31 downto 0); 
    data_in_x10: out std_logic_vector(31 downto 0); 
    data_in_x11: out std_logic_vector(31 downto 0); 
    data_in_x12: out std_logic_vector(31 downto 0); 
    data_in_x13: out std_logic_vector(31 downto 0); 
    data_in_x14: out std_logic_vector(31 downto 0); 
    data_in_x15: out std_logic_vector(31 downto 0); 
    data_in_x16: out std_logic_vector(31 downto 0); 
    data_in_x17: out std_logic_vector(31 downto 0); 
    data_in_x18: out std_logic_vector(31 downto 0); 
    data_in_x19: out std_logic_vector(31 downto 0); 
    data_in_x2: out std_logic_vector(31 downto 0); 
    data_in_x20: out std_logic_vector(31 downto 0); 
    data_in_x21: out std_logic_vector(31 downto 0); 
    data_in_x22: out std_logic_vector(31 downto 0); 
    data_in_x23: out std_logic_vector(31 downto 0); 
    data_in_x24: out std_logic_vector(31 downto 0); 
    data_in_x25: out std_logic_vector(31 downto 0); 
    data_in_x26: out std_logic_vector(31 downto 0); 
    data_in_x3: out std_logic_vector(31 downto 0); 
    data_in_x4: out std_logic_vector(31 downto 0); 
    data_in_x5: out std_logic_vector(31 downto 0); 
    data_in_x6: out std_logic_vector(31 downto 0); 
    data_in_x7: out std_logic_vector(31 downto 0); 
    data_in_x8: out std_logic_vector(31 downto 0); 
    data_in_x9: out std_logic_vector(31 downto 0); 
    dbg_backoff_active: out std_logic; 
    dbg_eifs_sel: out std_logic; 
    dbg_idle_for_difs: out std_logic; 
    dbg_nav_active: out std_logic; 
    dbg_tx_a_pending: out std_logic; 
    dbg_tx_b_pending: out std_logic; 
    en: out std_logic; 
    en_x0: out std_logic; 
    en_x1: out std_logic; 
    en_x10: out std_logic; 
    en_x11: out std_logic; 
    en_x12: out std_logic; 
    en_x13: out std_logic; 
    en_x14: out std_logic; 
    en_x15: out std_logic; 
    en_x16: out std_logic; 
    en_x17: out std_logic; 
    en_x18: out std_logic; 
    en_x19: out std_logic; 
    en_x2: out std_logic; 
    en_x20: out std_logic; 
    en_x21: out std_logic; 
    en_x22: out std_logic; 
    en_x23: out std_logic; 
    en_x24: out std_logic; 
    en_x25: out std_logic; 
    en_x26: out std_logic; 
    en_x3: out std_logic; 
    en_x4: out std_logic; 
    en_x5: out std_logic; 
    en_x6: out std_logic; 
    en_x7: out std_logic; 
    en_x8: out std_logic; 
    en_x9: out std_logic; 
    phy_rx_block_pktdet: out std_logic; 
    phy_tx_ant_mask: out std_logic_vector(3 downto 0); 
    phy_tx_gain_a: out std_logic_vector(5 downto 0); 
    phy_tx_gain_b: out std_logic_vector(5 downto 0); 
    phy_tx_gain_c: out std_logic_vector(5 downto 0); 
    phy_tx_gain_d: out std_logic_vector(5 downto 0); 
    phy_tx_pkt_buf: out std_logic_vector(3 downto 0); 
    phy_tx_start: out std_logic; 
    s_axi_arready: out std_logic; 
    s_axi_awready: out std_logic; 
    s_axi_bid: out std_logic_vector(7 downto 0); 
    s_axi_bresp: out std_logic_vector(1 downto 0); 
    s_axi_bvalid: out std_logic; 
    s_axi_rdata: out std_logic_vector(31 downto 0); 
    s_axi_rid: out std_logic_vector(7 downto 0); 
    s_axi_rlast: out std_logic; 
    s_axi_rresp: out std_logic_vector(1 downto 0); 
    s_axi_rvalid: out std_logic; 
    s_axi_wready: out std_logic; 
    timestamp_lsb: out std_logic_vector(31 downto 0); 
    timestamp_msb: out std_logic_vector(31 downto 0); 
    tx_start_timestamp_lsb: out std_logic_vector(31 downto 0); 
    tx_start_timestamp_msb: out std_logic_vector(31 downto 0)
  );
end wlan_mac_hw;

architecture structural of wlan_mac_hw is
  attribute core_generation_info: string;
  attribute core_generation_info of structural : architecture is "wlan_mac_hw,sysgen_core,{clock_period=10.00000000,clocking=Clock_Enables,sample_periods=1.00000000000 1.00000000000,testbench=0,total_blocks=1262,xilinx_adder_subtracter_block=2,xilinx_arithmetic_relational_operator_block=22,xilinx_bit_slice_extractor_block=70,xilinx_bus_concatenator_block=16,xilinx_bus_multiplexer_block=11,xilinx_chipscope_block=1,xilinx_constant_block_block=47,xilinx_counter_block=11,xilinx_delay_block=25,xilinx_disregard_subsystem_for_generation_block=3,xilinx_edk_core_block=1,xilinx_edk_processor_block=1,xilinx_gateway_in_block=44,xilinx_gateway_out_block=68,xilinx_inverter_block=37,xilinx_logical_block_block=71,xilinx_mcode_block_block=2,xilinx_multiplier_block=1,xilinx_register_block=178,xilinx_shared_memory_based_from_register_block=28,xilinx_shared_memory_based_to_register_block=28,xilinx_system_generator_block=1,xilinx_type_converter_block=14,xilinx_type_reinterpreter_block=1,}";

  signal axi_aresetn_net: std_logic;
  signal b_0_y_net_x9: std_logic;
  signal b_10_y_net_x1: std_logic;
  signal b_11_y_net_x1: std_logic;
  signal b_1_y_net_x3: std_logic;
  signal b_3_y_net_x1: std_logic;
  signal b_4_y_net_x2: std_logic;
  signal b_5_y_net_x2: std_logic;
  signal b_6_y_net_x2: std_logic;
  signal b_7_y_net_x1: std_logic;
  signal b_8_y_net_x1: std_logic;
  signal b_9_y_net_x1: std_logic;
  signal bitsm_4_y_net_x1: std_logic_vector(15 downto 0);
  signal ce_1_sg_x55: std_logic;
  signal clk_1_sg_x55: std_logic;
  signal concat1_y_net_x12: std_logic_vector(18 downto 0);
  signal concat1_y_net_x13: std_logic_vector(18 downto 0);
  signal concat1_y_net_x14: std_logic_vector(18 downto 0);
  signal concat1_y_net_x15: std_logic_vector(18 downto 0);
  signal concat1_y_net_x16: std_logic_vector(13 downto 0);
  signal concat1_y_net_x17: std_logic_vector(13 downto 0);
  signal concat1_y_net_x18: std_logic_vector(19 downto 0);
  signal concat1_y_net_x19: std_logic_vector(13 downto 0);
  signal convert1_dout_net_x4: std_logic;
  signal convert1_dout_net_x5: std_logic;
  signal convert5_dout_net_x2: std_logic;
  signal convert_dout_net_x2: std_logic;
  signal data_in_net: std_logic_vector(31 downto 0);
  signal data_in_x0_net: std_logic_vector(31 downto 0);
  signal data_in_x10_net: std_logic_vector(31 downto 0);
  signal data_in_x11_net: std_logic_vector(31 downto 0);
  signal data_in_x12_net: std_logic_vector(31 downto 0);
  signal data_in_x13_net: std_logic_vector(31 downto 0);
  signal data_in_x14_net: std_logic_vector(31 downto 0);
  signal data_in_x15_net: std_logic_vector(31 downto 0);
  signal data_in_x16_net: std_logic_vector(31 downto 0);
  signal data_in_x17_net: std_logic_vector(31 downto 0);
  signal data_in_x18_net: std_logic_vector(31 downto 0);
  signal data_in_x19_net: std_logic_vector(31 downto 0);
  signal data_in_x1_net: std_logic_vector(31 downto 0);
  signal data_in_x20_net: std_logic_vector(31 downto 0);
  signal data_in_x21_net: std_logic_vector(31 downto 0);
  signal data_in_x22_net: std_logic_vector(31 downto 0);
  signal data_in_x23_net: std_logic_vector(31 downto 0);
  signal data_in_x24_net: std_logic_vector(31 downto 0);
  signal data_in_x25_net: std_logic_vector(31 downto 0);
  signal data_in_x26_net: std_logic_vector(31 downto 0);
  signal data_in_x2_net: std_logic_vector(31 downto 0);
  signal data_in_x3_net: std_logic_vector(31 downto 0);
  signal data_in_x4_net: std_logic_vector(31 downto 0);
  signal data_in_x5_net: std_logic_vector(31 downto 0);
  signal data_in_x6_net: std_logic_vector(31 downto 0);
  signal data_in_x7_net: std_logic_vector(31 downto 0);
  signal data_in_x8_net: std_logic_vector(31 downto 0);
  signal data_in_x9_net: std_logic_vector(31 downto 0);
  signal data_out_net: std_logic_vector(31 downto 0);
  signal data_out_x0_net: std_logic_vector(31 downto 0);
  signal data_out_x10_net: std_logic_vector(31 downto 0);
  signal data_out_x11_net: std_logic_vector(31 downto 0);
  signal data_out_x12_net: std_logic_vector(31 downto 0);
  signal data_out_x13_net: std_logic_vector(31 downto 0);
  signal data_out_x14_net: std_logic_vector(31 downto 0);
  signal data_out_x15_net: std_logic_vector(31 downto 0);
  signal data_out_x16_net: std_logic_vector(31 downto 0);
  signal data_out_x17_net: std_logic_vector(31 downto 0);
  signal data_out_x18_net: std_logic_vector(31 downto 0);
  signal data_out_x19_net: std_logic_vector(31 downto 0);
  signal data_out_x1_net: std_logic_vector(31 downto 0);
  signal data_out_x20_net: std_logic_vector(31 downto 0);
  signal data_out_x21_net: std_logic_vector(31 downto 0);
  signal data_out_x22_net: std_logic_vector(31 downto 0);
  signal data_out_x23_net: std_logic_vector(31 downto 0);
  signal data_out_x24_net: std_logic_vector(31 downto 0);
  signal data_out_x25_net: std_logic_vector(31 downto 0);
  signal data_out_x26_net: std_logic_vector(31 downto 0);
  signal data_out_x2_net: std_logic_vector(31 downto 0);
  signal data_out_x3_net: std_logic_vector(31 downto 0);
  signal data_out_x4_net: std_logic_vector(31 downto 0);
  signal data_out_x5_net: std_logic_vector(31 downto 0);
  signal data_out_x6_net: std_logic_vector(31 downto 0);
  signal data_out_x7_net: std_logic_vector(31 downto 0);
  signal data_out_x8_net: std_logic_vector(31 downto 0);
  signal data_out_x9_net: std_logic_vector(31 downto 0);
  signal dbg_backoff_active_net: std_logic;
  signal dbg_eifs_sel_net: std_logic;
  signal dbg_idle_for_difs_net: std_logic;
  signal dbg_nav_active_net: std_logic;
  signal dbg_tx_a_pending_net: std_logic;
  signal dbg_tx_b_pending_net: std_logic;
  signal delay_q_net_x2: std_logic;
  signal dout_net: std_logic_vector(31 downto 0);
  signal dout_x0_net: std_logic_vector(31 downto 0);
  signal dout_x10_net: std_logic_vector(31 downto 0);
  signal dout_x11_net: std_logic_vector(31 downto 0);
  signal dout_x12_net: std_logic_vector(31 downto 0);
  signal dout_x13_net: std_logic_vector(31 downto 0);
  signal dout_x14_net: std_logic_vector(31 downto 0);
  signal dout_x15_net: std_logic_vector(31 downto 0);
  signal dout_x1_net: std_logic_vector(31 downto 0);
  signal dout_x2_net: std_logic_vector(31 downto 0);
  signal dout_x3_net: std_logic_vector(31 downto 0);
  signal dout_x4_net: std_logic_vector(31 downto 0);
  signal dout_x5_net: std_logic_vector(31 downto 0);
  signal dout_x6_net: std_logic_vector(31 downto 0);
  signal dout_x7_net: std_logic_vector(31 downto 0);
  signal dout_x8_net: std_logic_vector(31 downto 0);
  signal dout_x9_net: std_logic_vector(31 downto 0);
  signal en_net: std_logic;
  signal en_x0_net: std_logic;
  signal en_x10_net: std_logic;
  signal en_x11_net: std_logic;
  signal en_x12_net: std_logic;
  signal en_x13_net: std_logic;
  signal en_x14_net: std_logic;
  signal en_x15_net: std_logic;
  signal en_x16_net: std_logic;
  signal en_x17_net: std_logic;
  signal en_x18_net: std_logic;
  signal en_x19_net: std_logic;
  signal en_x1_net: std_logic;
  signal en_x20_net: std_logic;
  signal en_x21_net: std_logic;
  signal en_x22_net: std_logic;
  signal en_x2_net: std_logic;
  signal en_x3_net: std_logic;
  signal en_x4_net: std_logic;
  signal en_x5_net: std_logic;
  signal en_x6_net: std_logic;
  signal en_x7_net: std_logic;
  signal en_x8_net: std_logic;
  signal en_x9_net: std_logic;
  signal inverter1_op_net_x1: std_logic;
  signal inverter1_op_net_x2: std_logic;
  signal logical1_y_net_x5: std_logic;
  signal logical3_y_net_x3: std_logic;
  signal logical3_y_net_x4: std_logic;
  signal logical5_y_net_x2: std_logic;
  signal mcode_tx_control_a_fsm_state_out_net_x1: std_logic_vector(2 downto 0);
  signal mcode_tx_control_b_fsm_state_out_net_x1: std_logic_vector(2 downto 0);
  signal microsecond_counter_op_net_x2: std_logic_vector(63 downto 0);
  signal num_slots_op_net_x1: std_logic_vector(15 downto 0);
  signal phy_cca_ind_busy_net: std_logic;
  signal phy_rx_block_pktdet_net: std_logic;
  signal phy_rx_data_byte_net: std_logic_vector(7 downto 0);
  signal phy_rx_data_bytenum_net: std_logic_vector(15 downto 0);
  signal phy_rx_data_done_ind_net: std_logic;
  signal phy_rx_data_ind_net: std_logic;
  signal phy_rx_end_ind_net: std_logic;
  signal phy_rx_end_rxerror_net: std_logic_vector(3 downto 0);
  signal phy_rx_fcs_good_ind_net: std_logic;
  signal phy_rx_params_ind_net: std_logic;
  signal phy_rx_params_length_net: std_logic_vector(15 downto 0);
  signal phy_rx_params_mcs_net: std_logic_vector(6 downto 0);
  signal phy_rx_params_phy_mode_net: std_logic_vector(2 downto 0);
  signal phy_rx_params_unsupported_net: std_logic;
  signal phy_rx_start_ind_net: std_logic;
  signal phy_rx_start_phy_sel_net: std_logic;
  signal phy_tx_ant_mask_net: std_logic_vector(3 downto 0);
  signal phy_tx_done_net: std_logic;
  signal phy_tx_gain_a_net: std_logic_vector(5 downto 0);
  signal phy_tx_gain_b_net: std_logic_vector(5 downto 0);
  signal phy_tx_gain_c_net: std_logic_vector(5 downto 0);
  signal phy_tx_gain_d_net: std_logic_vector(5 downto 0);
  signal phy_tx_pkt_buf_net: std_logic_vector(3 downto 0);
  signal phy_tx_start_net: std_logic;
  signal phy_tx_started_net: std_logic;
  signal plb_ce_1_sg_x1: std_logic;
  signal plb_clk_1_sg_x1: std_logic;
  signal register10_q_net_x4: std_logic_vector(5 downto 0);
  signal register10_q_net_x5: std_logic_vector(5 downto 0);
  signal register11_q_net_x2: std_logic;
  signal register14_q_net_x2: std_logic;
  signal register15_q_net_x2: std_logic;
  signal register16_q_net_x2: std_logic_vector(3 downto 0);
  signal register17_q_net_x2: std_logic_vector(15 downto 0);
  signal register19_q_net_x2: std_logic_vector(5 downto 0);
  signal register1_q_net_x4: std_logic;
  signal register1_q_net_x6: std_logic_vector(1 downto 0);
  signal register1_q_net_x7: std_logic;
  signal register1_q_net_x8: std_logic_vector(1 downto 0);
  signal register20_q_net_x1: std_logic_vector(15 downto 0);
  signal register21_q_net_x1: std_logic;
  signal register22_q_net_x2: std_logic_vector(3 downto 0);
  signal register25_q_net_x2: std_logic_vector(3 downto 0);
  signal register27_q_net_x2: std_logic_vector(31 downto 0);
  signal register28_q_net_x2: std_logic_vector(31 downto 0);
  signal register2_q_net_x30: std_logic;
  signal register2_q_net_x31: std_logic;
  signal register2_q_net_x32: std_logic;
  signal register2_q_net_x33: std_logic;
  signal register2_q_net_x34: std_logic;
  signal register2_q_net_x35: std_logic;
  signal register2_q_net_x36: std_logic;
  signal register2_q_net_x42: std_logic;
  signal register2_q_net_x43: std_logic_vector(3 downto 0);
  signal register2_q_net_x44: std_logic;
  signal register2_q_net_x45: std_logic;
  signal register2_q_net_x46: std_logic_vector(3 downto 0);
  signal register2_q_net_x47: std_logic;
  signal register2_q_net_x48: std_logic;
  signal register2_q_net_x5: std_logic;
  signal register35_q_net_x2: std_logic;
  signal register3_q_net_x4: std_logic;
  signal register3_q_net_x6: std_logic;
  signal register3_q_net_x7: std_logic_vector(15 downto 0);
  signal register4_q_net_x4: std_logic;
  signal register4_q_net_x6: std_logic_vector(3 downto 0);
  signal register53_q_net_x2: std_logic_vector(5 downto 0);
  signal register56_q_net_x2: std_logic_vector(5 downto 0);
  signal register57_q_net_x2: std_logic_vector(5 downto 0);
  signal register58_q_net_x2: std_logic_vector(5 downto 0);
  signal register59_q_net_x2: std_logic_vector(5 downto 0);
  signal register5_q_net_x2: std_logic;
  signal register60_q_net_x2: std_logic_vector(5 downto 0);
  signal register61_q_net_x2: std_logic_vector(5 downto 0);
  signal register66_q_net_x2: std_logic;
  signal register67_q_net_x2: std_logic;
  signal register69_q_net_x3: std_logic_vector(31 downto 0);
  signal register6_q_net_x4: std_logic;
  signal register6_q_net_x6: std_logic_vector(5 downto 0);
  signal register6_q_net_x8: std_logic;
  signal register6_q_net_x9: std_logic_vector(5 downto 0);
  signal register71_q_net_x3: std_logic_vector(31 downto 0);
  signal register7_q_net_x2: std_logic;
  signal register7_q_net_x6: std_logic_vector(3 downto 0);
  signal register7_q_net_x8: std_logic_vector(3 downto 0);
  signal register8_q_net_x5: std_logic_vector(5 downto 0);
  signal register8_q_net_x6: std_logic;
  signal register8_q_net_x7: std_logic;
  signal register8_q_net_x8: std_logic_vector(5 downto 0);
  signal register9_q_net_x1: std_logic;
  signal register9_q_net_x4: std_logic_vector(5 downto 0);
  signal register9_q_net_x5: std_logic_vector(5 downto 0);
  signal reinterpret_output_port_net_x2: std_logic_vector(7 downto 0);
  signal relational1_op_net_x5: std_logic;
  signal relational3_op_net_x1: std_logic;
  signal s_axi_araddr_net: std_logic_vector(31 downto 0);
  signal s_axi_arburst_net: std_logic_vector(1 downto 0);
  signal s_axi_arcache_net: std_logic_vector(3 downto 0);
  signal s_axi_arid_net: std_logic_vector(7 downto 0);
  signal s_axi_arlen_net: std_logic_vector(7 downto 0);
  signal s_axi_arlock_net: std_logic_vector(1 downto 0);
  signal s_axi_arprot_net: std_logic_vector(2 downto 0);
  signal s_axi_arready_net: std_logic;
  signal s_axi_arsize_net: std_logic_vector(2 downto 0);
  signal s_axi_arvalid_net: std_logic;
  signal s_axi_awaddr_net: std_logic_vector(31 downto 0);
  signal s_axi_awburst_net: std_logic_vector(1 downto 0);
  signal s_axi_awcache_net: std_logic_vector(3 downto 0);
  signal s_axi_awid_net: std_logic_vector(7 downto 0);
  signal s_axi_awlen_net: std_logic_vector(7 downto 0);
  signal s_axi_awlock_net: std_logic_vector(1 downto 0);
  signal s_axi_awprot_net: std_logic_vector(2 downto 0);
  signal s_axi_awready_net: std_logic;
  signal s_axi_awsize_net: std_logic_vector(2 downto 0);
  signal s_axi_awvalid_net: std_logic;
  signal s_axi_bid_net: std_logic_vector(7 downto 0);
  signal s_axi_bready_net: std_logic;
  signal s_axi_bresp_net: std_logic_vector(1 downto 0);
  signal s_axi_bvalid_net: std_logic;
  signal s_axi_rdata_net: std_logic_vector(31 downto 0);
  signal s_axi_rid_net: std_logic_vector(7 downto 0);
  signal s_axi_rlast_net: std_logic;
  signal s_axi_rready_net: std_logic;
  signal s_axi_rresp_net: std_logic_vector(1 downto 0);
  signal s_axi_rvalid_net: std_logic;
  signal s_axi_wdata_net: std_logic_vector(31 downto 0);
  signal s_axi_wlast_net: std_logic;
  signal s_axi_wready_net: std_logic;
  signal s_axi_wstrb_net: std_logic_vector(3 downto 0);
  signal s_axi_wvalid_net: std_logic;
  signal timestamp_lsb_net: std_logic_vector(31 downto 0);
  signal timestamp_msb_net: std_logic_vector(31 downto 0);
  signal tx_start_timestamp_lsb_net: std_logic_vector(31 downto 0);
  signal tx_start_timestamp_msb_net: std_logic_vector(31 downto 0);

begin
  axi_aresetn_net <= axi_aresetn;
  ce_1_sg_x55 <= ce_1;
  clk_1_sg_x55 <= clk_1;
  data_out_net <= data_out;
  data_out_x0_net <= data_out_x0;
  data_out_x1_net <= data_out_x1;
  data_out_x10_net <= data_out_x10;
  data_out_x11_net <= data_out_x11;
  data_out_x12_net <= data_out_x12;
  data_out_x13_net <= data_out_x13;
  data_out_x14_net <= data_out_x14;
  data_out_x15_net <= data_out_x15;
  data_out_x16_net <= data_out_x16;
  data_out_x17_net <= data_out_x17;
  data_out_x18_net <= data_out_x18;
  data_out_x19_net <= data_out_x19;
  data_out_x2_net <= data_out_x2;
  data_out_x20_net <= data_out_x20;
  data_out_x21_net <= data_out_x21;
  data_out_x22_net <= data_out_x22;
  data_out_x23_net <= data_out_x23;
  data_out_x24_net <= data_out_x24;
  data_out_x25_net <= data_out_x25;
  data_out_x26_net <= data_out_x26;
  data_out_x3_net <= data_out_x3;
  data_out_x4_net <= data_out_x4;
  data_out_x5_net <= data_out_x5;
  data_out_x6_net <= data_out_x6;
  data_out_x7_net <= data_out_x7;
  data_out_x8_net <= data_out_x8;
  data_out_x9_net <= data_out_x9;
  dout_net <= dout;
  dout_x0_net <= dout_x0;
  dout_x1_net <= dout_x1;
  dout_x10_net <= dout_x10;
  dout_x11_net <= dout_x11;
  dout_x12_net <= dout_x12;
  dout_x13_net <= dout_x13;
  dout_x14_net <= dout_x14;
  dout_x15_net <= dout_x15;
  dout_x2_net <= dout_x2;
  dout_x3_net <= dout_x3;
  dout_x4_net <= dout_x4;
  dout_x5_net <= dout_x5;
  dout_x6_net <= dout_x6;
  dout_x7_net <= dout_x7;
  dout_x8_net <= dout_x8;
  dout_x9_net <= dout_x9;
  phy_cca_ind_busy_net <= phy_cca_ind_busy;
  phy_rx_data_byte_net <= phy_rx_data_byte;
  phy_rx_data_bytenum_net <= phy_rx_data_bytenum;
  phy_rx_data_done_ind_net <= phy_rx_data_done_ind;
  phy_rx_data_ind_net <= phy_rx_data_ind;
  phy_rx_end_ind_net <= phy_rx_end_ind;
  phy_rx_end_rxerror_net <= phy_rx_end_rxerror;
  phy_rx_fcs_good_ind_net <= phy_rx_fcs_good_ind;
  phy_rx_params_ind_net <= phy_rx_params_ind;
  phy_rx_params_length_net <= phy_rx_params_length;
  phy_rx_params_mcs_net <= phy_rx_params_mcs;
  phy_rx_params_phy_mode_net <= phy_rx_params_phy_mode;
  phy_rx_params_unsupported_net <= phy_rx_params_unsupported;
  phy_rx_start_ind_net <= phy_rx_start_ind;
  phy_rx_start_phy_sel_net <= phy_rx_start_phy_sel;
  phy_tx_done_net <= phy_tx_done;
  phy_tx_started_net <= phy_tx_started;
  plb_ce_1_sg_x1 <= plb_ce_1;
  plb_clk_1_sg_x1 <= plb_clk_1;
  s_axi_araddr_net <= s_axi_araddr;
  s_axi_arburst_net <= s_axi_arburst;
  s_axi_arcache_net <= s_axi_arcache;
  s_axi_arid_net <= s_axi_arid;
  s_axi_arlen_net <= s_axi_arlen;
  s_axi_arlock_net <= s_axi_arlock;
  s_axi_arprot_net <= s_axi_arprot;
  s_axi_arsize_net <= s_axi_arsize;
  s_axi_arvalid_net <= s_axi_arvalid;
  s_axi_awaddr_net <= s_axi_awaddr;
  s_axi_awburst_net <= s_axi_awburst;
  s_axi_awcache_net <= s_axi_awcache;
  s_axi_awid_net <= s_axi_awid;
  s_axi_awlen_net <= s_axi_awlen;
  s_axi_awlock_net <= s_axi_awlock;
  s_axi_awprot_net <= s_axi_awprot;
  s_axi_awsize_net <= s_axi_awsize;
  s_axi_awvalid_net <= s_axi_awvalid;
  s_axi_bready_net <= s_axi_bready;
  s_axi_rready_net <= s_axi_rready;
  s_axi_wdata_net <= s_axi_wdata;
  s_axi_wlast_net <= s_axi_wlast;
  s_axi_wstrb_net <= s_axi_wstrb;
  s_axi_wvalid_net <= s_axi_wvalid;
  data_in <= data_in_net;
  data_in_x0 <= data_in_x0_net;
  data_in_x1 <= data_in_x1_net;
  data_in_x10 <= data_in_x10_net;
  data_in_x11 <= data_in_x11_net;
  data_in_x12 <= data_in_x12_net;
  data_in_x13 <= data_in_x13_net;
  data_in_x14 <= data_in_x14_net;
  data_in_x15 <= data_in_x15_net;
  data_in_x16 <= data_in_x16_net;
  data_in_x17 <= data_in_x17_net;
  data_in_x18 <= data_in_x18_net;
  data_in_x19 <= data_in_x19_net;
  data_in_x2 <= data_in_x2_net;
  data_in_x20 <= data_in_x20_net;
  data_in_x21 <= data_in_x21_net;
  data_in_x22 <= data_in_x22_net;
  data_in_x23 <= data_in_x23_net;
  data_in_x24 <= data_in_x24_net;
  data_in_x25 <= data_in_x25_net;
  data_in_x26 <= data_in_x26_net;
  data_in_x3 <= data_in_x3_net;
  data_in_x4 <= data_in_x4_net;
  data_in_x5 <= data_in_x5_net;
  data_in_x6 <= data_in_x6_net;
  data_in_x7 <= data_in_x7_net;
  data_in_x8 <= data_in_x8_net;
  data_in_x9 <= data_in_x9_net;
  dbg_backoff_active <= dbg_backoff_active_net;
  dbg_eifs_sel <= dbg_eifs_sel_net;
  dbg_idle_for_difs <= dbg_idle_for_difs_net;
  dbg_nav_active <= dbg_nav_active_net;
  dbg_tx_a_pending <= dbg_tx_a_pending_net;
  dbg_tx_b_pending <= dbg_tx_b_pending_net;
  en <= en_net;
  en_x0 <= en_x0_net;
  en_x1 <= en_x1_net;
  en_x10 <= en_x10_net;
  en_x11 <= en_x11_net;
  en_x12 <= en_x12_net;
  en_x13 <= en_x13_net;
  en_x14 <= en_x14_net;
  en_x15 <= en_x15_net;
  en_x16 <= en_x16_net;
  en_x17 <= en_x17_net;
  en_x18 <= en_x18_net;
  en_x19 <= en_x19_net;
  en_x2 <= en_x2_net;
  en_x20 <= en_x20_net;
  en_x21 <= en_x21_net;
  en_x22 <= en_x22_net;
  en_x23 <= convert5_dout_net_x2;
  en_x24 <= convert5_dout_net_x2;
  en_x25 <= register15_q_net_x2;
  en_x26 <= register15_q_net_x2;
  en_x3 <= en_x3_net;
  en_x4 <= en_x4_net;
  en_x5 <= en_x5_net;
  en_x6 <= en_x6_net;
  en_x7 <= en_x7_net;
  en_x8 <= en_x8_net;
  en_x9 <= en_x9_net;
  phy_rx_block_pktdet <= phy_rx_block_pktdet_net;
  phy_tx_ant_mask <= phy_tx_ant_mask_net;
  phy_tx_gain_a <= phy_tx_gain_a_net;
  phy_tx_gain_b <= phy_tx_gain_b_net;
  phy_tx_gain_c <= phy_tx_gain_c_net;
  phy_tx_gain_d <= phy_tx_gain_d_net;
  phy_tx_pkt_buf <= phy_tx_pkt_buf_net;
  phy_tx_start <= phy_tx_start_net;
  s_axi_arready <= s_axi_arready_net;
  s_axi_awready <= s_axi_awready_net;
  s_axi_bid <= s_axi_bid_net;
  s_axi_bresp <= s_axi_bresp_net;
  s_axi_bvalid <= s_axi_bvalid_net;
  s_axi_rdata <= s_axi_rdata_net;
  s_axi_rid <= s_axi_rid_net;
  s_axi_rlast <= s_axi_rlast_net;
  s_axi_rresp <= s_axi_rresp_net;
  s_axi_rvalid <= s_axi_rvalid_net;
  s_axi_wready <= s_axi_wready_net;
  timestamp_lsb <= timestamp_lsb_net;
  timestamp_msb <= timestamp_msb_net;
  tx_start_timestamp_lsb <= tx_start_timestamp_lsb_net;
  tx_start_timestamp_msb <= tx_start_timestamp_msb_net;

  backoff_23f797b138: entity work.backoff_entity_23f797b138
    port map (
      ce_1 => ce_1_sg_x55,
      clk_1 => clk_1_sg_x55,
      concat1 => concat1_y_net_x17,
      global_reset => b_0_y_net_x9,
      idle_for_txdifs => relational1_op_net_x5,
      reg_backoff_sw_numslots => register20_q_net_x1,
      reg_backoff_sw_start => register21_q_net_x1,
      reg_force_reset_backoff => b_11_y_net_x1,
      tx_a_backoff_start => convert_dout_net_x2,
      tx_a_num_bo_slots => register3_q_net_x7,
      backoff_done => logical5_y_net_x2,
      register1_x0 => dbg_backoff_active_net,
      status_current_backoff_count => num_slots_op_net_x1
    );

  cca_95f741f726: entity work.cca_entity_95f741f726
    port map (
      ce_1 => ce_1_sg_x55,
      clk_1 => clk_1_sg_x55,
      mac_nav_busy => logical3_y_net_x4,
      phy_cca_ind_busy => phy_cca_ind_busy_net,
      reg_cca_ignore_nav => b_9_y_net_x1,
      reg_cca_ignore_phy_cs => b_7_y_net_x1,
      reg_cca_ignore_txbusy => b_8_y_net_x1,
      status_tx_phy_active => register2_q_net_x32,
      cs_busy => logical3_y_net_x3,
      cs_idle => inverter1_op_net_x1
    );

  edk_processor_82b88caaa5: entity work.edk_processor_entity_82b88caaa5
    port map (
      axi_aresetn => axi_aresetn_net,
      from_register => data_out_net,
      from_register1 => data_out_x0_net,
      from_register10 => data_out_x1_net,
      from_register2 => data_out_x2_net,
      from_register3 => data_out_x3_net,
      from_register4 => data_out_x4_net,
      from_register5 => data_out_x5_net,
      from_register6 => data_out_x6_net,
      from_register7 => data_out_x7_net,
      from_register8 => data_out_x8_net,
      from_register9 => data_out_x9_net,
      plb_ce_1 => plb_ce_1_sg_x1,
      plb_clk_1 => plb_clk_1_sg_x1,
      s_axi_araddr => s_axi_araddr_net,
      s_axi_arburst => s_axi_arburst_net,
      s_axi_arcache => s_axi_arcache_net,
      s_axi_arid => s_axi_arid_net,
      s_axi_arlen => s_axi_arlen_net,
      s_axi_arlock => s_axi_arlock_net,
      s_axi_arprot => s_axi_arprot_net,
      s_axi_arsize => s_axi_arsize_net,
      s_axi_arvalid => s_axi_arvalid_net,
      s_axi_awaddr => s_axi_awaddr_net,
      s_axi_awburst => s_axi_awburst_net,
      s_axi_awcache => s_axi_awcache_net,
      s_axi_awid => s_axi_awid_net,
      s_axi_awlen => s_axi_awlen_net,
      s_axi_awlock => s_axi_awlock_net,
      s_axi_awprot => s_axi_awprot_net,
      s_axi_awsize => s_axi_awsize_net,
      s_axi_awvalid => s_axi_awvalid_net,
      s_axi_bready => s_axi_bready_net,
      s_axi_rready => s_axi_rready_net,
      s_axi_wdata => s_axi_wdata_net,
      s_axi_wlast => s_axi_wlast_net,
      s_axi_wstrb => s_axi_wstrb_net,
      s_axi_wvalid => s_axi_wvalid_net,
      to_register => dout_net,
      to_register1 => dout_x0_net,
      to_register10 => dout_x1_net,
      to_register11 => dout_x2_net,
      to_register12 => dout_x3_net,
      to_register13 => dout_x4_net,
      to_register14 => dout_x5_net,
      to_register15 => dout_x6_net,
      to_register16 => dout_x7_net,
      to_register2 => dout_x8_net,
      to_register3 => dout_x9_net,
      to_register4 => dout_x10_net,
      to_register5 => dout_x11_net,
      to_register6 => dout_x12_net,
      to_register7 => dout_x13_net,
      to_register8 => dout_x14_net,
      to_register9 => dout_x15_net,
      memmap_x0 => s_axi_arready_net,
      memmap_x1 => s_axi_awready_net,
      memmap_x10 => s_axi_wready_net,
      memmap_x11 => data_in_net,
      memmap_x12 => en_net,
      memmap_x13 => data_in_x0_net,
      memmap_x14 => en_x0_net,
      memmap_x15 => data_in_x8_net,
      memmap_x16 => en_x8_net,
      memmap_x17 => data_in_x9_net,
      memmap_x18 => en_x9_net,
      memmap_x19 => data_in_x10_net,
      memmap_x2 => s_axi_bid_net,
      memmap_x20 => en_x10_net,
      memmap_x21 => data_in_x11_net,
      memmap_x22 => en_x11_net,
      memmap_x23 => data_in_x12_net,
      memmap_x24 => en_x12_net,
      memmap_x25 => data_in_x13_net,
      memmap_x26 => en_x13_net,
      memmap_x27 => data_in_x14_net,
      memmap_x28 => en_x14_net,
      memmap_x29 => data_in_x15_net,
      memmap_x3 => s_axi_bresp_net,
      memmap_x30 => en_x15_net,
      memmap_x31 => data_in_x1_net,
      memmap_x32 => en_x1_net,
      memmap_x33 => data_in_x2_net,
      memmap_x34 => en_x2_net,
      memmap_x35 => data_in_x3_net,
      memmap_x36 => en_x3_net,
      memmap_x37 => data_in_x4_net,
      memmap_x38 => en_x4_net,
      memmap_x39 => data_in_x5_net,
      memmap_x4 => s_axi_bvalid_net,
      memmap_x40 => en_x5_net,
      memmap_x41 => data_in_x6_net,
      memmap_x42 => en_x6_net,
      memmap_x43 => data_in_x7_net,
      memmap_x44 => en_x7_net,
      memmap_x5 => s_axi_rdata_net,
      memmap_x6 => s_axi_rid_net,
      memmap_x7 => s_axi_rlast_net,
      memmap_x8 => s_axi_rresp_net,
      memmap_x9 => s_axi_rvalid_net
    );

  idle_for_difs_eifs_d31a723322: entity work.idle_for_difs_eifs_entity_d31a723322
    port map (
      ce_1 => ce_1_sg_x55,
      clk_1 => clk_1_sg_x55,
      global_reset => b_0_y_net_x9,
      medium_busy => logical3_y_net_x3,
      medium_idle => inverter1_op_net_x1,
      phy_rx_end_ind => phy_rx_end_ind_net,
      phy_rx_end_rxerror => phy_rx_end_rxerror_net,
      phy_rx_fcs_good_ind => phy_rx_fcs_good_ind_net,
      reg_calibtime_txdifs => concat1_y_net_x19,
      reg_interval_difs => concat1_y_net_x16,
      reg_interval_eifs => concat1_y_net_x18,
      idle_for_difs => relational3_op_net_x1,
      idle_for_txdifs => relational1_op_net_x5,
      register1_x0 => dbg_idle_for_difs_net,
      register3_x0 => dbg_eifs_sel_net
    );

  nav_556d0ea53d: entity work.nav_entity_556d0ea53d
    port map (
      ce_1 => ce_1_sg_x55,
      clk_1 => clk_1_sg_x55,
      global_reset => b_0_y_net_x9,
      phy_rx_data_byte => phy_rx_data_byte_net,
      phy_rx_data_bytenum => phy_rx_data_bytenum_net,
      phy_rx_data_ind => phy_rx_data_ind_net,
      phy_rx_end_ind => phy_rx_end_ind_net,
      phy_rx_end_rxerror => phy_rx_end_rxerror_net,
      phy_rx_start_ind => phy_rx_start_ind_net,
      reg_disable_nav => b_3_y_net_x1,
      reg_force_reset_nav => b_10_y_net_x1,
      register3 => register3_q_net_x4,
      register69 => register69_q_net_x3,
      register71 => register71_q_net_x3,
      reinterpret => reinterpret_output_port_net_x2,
      nav_busy => logical3_y_net_x4,
      nav_value_100nsec => bitsm_4_y_net_x1,
      nav_zero => inverter1_op_net_x2,
      new_duration => register4_q_net_x4,
      register1_x0 => dbg_nav_active_net
    );

  o_720fb5e965: entity work.o_entity_720fb5e965
    port map (
      b_1 => b_1_y_net_x3,
      b_4 => b_4_y_net_x2,
      b_6 => b_6_y_net_x2,
      ce_1 => ce_1_sg_x55,
      clk_1 => clk_1_sg_x55,
      convert1 => convert1_dout_net_x4,
      convert1_x0 => convert1_dout_net_x5,
      global_reset => b_0_y_net_x9,
      logical1_x0 => logical1_y_net_x5,
      phy_rx_data_done_ind => phy_rx_data_done_ind_net,
      phy_rx_end_ind => phy_rx_end_ind_net,
      phy_rx_end_rxerror => phy_rx_end_rxerror_net,
      phy_rx_fcs_good_ind => phy_rx_fcs_good_ind_net,
      phy_rx_start_ind => phy_rx_start_ind_net,
      phy_tx_end_confirm => phy_tx_done_net,
      phy_tx_start_confirm => phy_tx_started_net,
      register10 => register10_q_net_x4,
      register10_x0 => register10_q_net_x5,
      register2 => register2_q_net_x43,
      register2_x0 => register2_q_net_x46,
      register6 => register6_q_net_x6,
      register6_x0 => register6_q_net_x9,
      register7 => register7_q_net_x6,
      register7_x0 => register7_q_net_x8,
      register8 => register8_q_net_x5,
      register8_x0 => register8_q_net_x8,
      register9 => register9_q_net_x4,
      register9_x0 => register9_q_net_x5,
      phy_rx_ports => phy_rx_block_pktdet_net,
      phy_rx_ports_x0 => register2_q_net_x30,
      phy_rx_ports_x1 => register2_q_net_x31,
      phy_tx_ports => phy_tx_start_net,
      phy_tx_ports_x0 => phy_tx_pkt_buf_net,
      phy_tx_ports_x1 => phy_tx_gain_a_net,
      phy_tx_ports_x2 => phy_tx_ant_mask_net,
      phy_tx_ports_x3 => phy_tx_gain_b_net,
      phy_tx_ports_x4 => phy_tx_gain_c_net,
      phy_tx_ports_x5 => phy_tx_gain_d_net,
      status_rx_fcs_good => register3_q_net_x4,
      status_rx_phy_active => delay_q_net_x2,
      status_tx_phy_active => register2_q_net_x32
    );

  registers_c6b0991c81: entity work.registers_entity_c6b0991c81
    port map (
      ce_1 => ce_1_sg_x55,
      clk_1 => clk_1_sg_x55,
      from_register1 => data_out_x10_net,
      from_register10 => data_out_x18_net,
      from_register11 => data_out_x19_net,
      from_register12 => data_out_x22_net,
      from_register13 => data_out_x20_net,
      from_register14 => data_out_x23_net,
      from_register15 => data_out_x11_net,
      from_register16 => data_out_x12_net,
      from_register1_x0 => data_out_x21_net,
      from_register2 => data_out_x13_net,
      from_register3 => data_out_x24_net,
      from_register4 => data_out_x14_net,
      from_register5 => data_out_x15_net,
      from_register6 => data_out_x16_net,
      from_register7 => data_out_x25_net,
      from_register8 => data_out_x17_net,
      from_register9 => data_out_x26_net,
      mcode_tx_control_a => mcode_tx_control_a_fsm_state_out_net_x1,
      mcode_tx_control_b => mcode_tx_control_b_fsm_state_out_net_x1,
      nav => logical3_y_net_x4,
      nav_value_100nsec => bitsm_4_y_net_x1,
      nav_x0 => register4_q_net_x4,
      o => delay_q_net_x2,
      o_x0 => register2_q_net_x30,
      o_x1 => register2_q_net_x31,
      o_x2 => register3_q_net_x4,
      o_x3 => register2_q_net_x32,
      phy_cca_ind_busy => phy_cca_ind_busy_net,
      phy_rx_byte => phy_rx_data_byte_net,
      phy_rx_byte_valid => phy_rx_data_ind_net,
      phy_rx_bytenum => phy_rx_data_bytenum_net,
      phy_rx_end_rxerror => phy_rx_end_rxerror_net,
      phy_rx_params_length => phy_rx_params_length_net,
      phy_rx_params_mcs => phy_rx_params_mcs_net,
      phy_rx_params_phy_mode => phy_rx_params_phy_mode_net,
      phy_rx_params_unsupported => phy_rx_params_unsupported_net,
      phy_rx_params_valid => phy_rx_params_ind_net,
      phy_rx_start_ind => phy_rx_start_ind_net,
      phy_rx_start_phy_sel => phy_rx_start_phy_sel_net,
      phy_tx_started => phy_tx_started_net,
      register1_x0 => register1_q_net_x8,
      register1_x1 => register1_q_net_x6,
      register2_x0 => register2_q_net_x44,
      register2_x1 => register2_q_net_x45,
      register2_x2 => register2_q_net_x47,
      register2_x3 => register2_q_net_x48,
      rx_timers => register2_q_net_x33,
      rx_timers_x0 => register2_q_net_x34,
      rx_timers_x1 => register2_q_net_x35,
      rx_timers_x2 => register2_q_net_x36,
      status_current_backoff_count => num_slots_op_net_x1,
      x64_bit_usec_counter => microsecond_counter_op_net_x2,
      constant1_x0 => en_x18_net,
      constant2_x0 => en_x16_net,
      constant3_x0 => en_x19_net,
      convert1_x0 => data_in_x18_net,
      convert4_x0 => data_in_x17_net,
      convert6_x0 => data_in_x19_net,
      convert_x0 => data_in_x16_net,
      ctrl_bits => logical1_y_net_x5,
      ctrl_bits_x0 => b_0_y_net_x9,
      ctrl_bits_x1 => b_10_y_net_x1,
      ctrl_bits_x10 => b_9_y_net_x1,
      ctrl_bits_x2 => b_11_y_net_x1,
      ctrl_bits_x3 => b_1_y_net_x3,
      ctrl_bits_x4 => b_3_y_net_x1,
      ctrl_bits_x5 => b_4_y_net_x2,
      ctrl_bits_x6 => b_5_y_net_x2,
      ctrl_bits_x7 => b_6_y_net_x2,
      ctrl_bits_x8 => b_7_y_net_x1,
      ctrl_bits_x9 => b_8_y_net_x1,
      reg_backoff_sw_numslots => register20_q_net_x1,
      reg_backoff_sw_start => register21_q_net_x1,
      reg_calibtime_txdifs => concat1_y_net_x19,
      reg_interval_difs => concat1_y_net_x16,
      reg_interval_eifs => concat1_y_net_x18,
      reg_interval_slot => concat1_y_net_x17,
      reg_nav_check_addr_1 => register71_q_net_x3,
      reg_nav_check_addr_2 => register69_q_net_x3,
      reg_nav_time_adj => reinterpret_output_port_net_x2,
      reg_tx_start_a => register35_q_net_x2,
      reg_tx_start_b => register6_q_net_x4,
      register11_x0 => en_x17_net,
      status_register => en_x20_net,
      status_register_x0 => data_in_x20_net,
      timestamp_regs_io => data_in_x21_net,
      timestamp_regs_io_x0 => data_in_x23_net,
      timestamp_regs_io_x1 => data_in_x25_net,
      timestamp_regs_io_x10 => register27_q_net_x2,
      timestamp_regs_io_x11 => register28_q_net_x2,
      timestamp_regs_io_x12 => tx_start_timestamp_lsb_net,
      timestamp_regs_io_x2 => data_in_x22_net,
      timestamp_regs_io_x3 => data_in_x24_net,
      timestamp_regs_io_x4 => data_in_x26_net,
      timestamp_regs_io_x5 => en_x21_net,
      timestamp_regs_io_x6 => en_x22_net,
      timestamp_regs_io_x7 => convert5_dout_net_x2,
      timestamp_regs_io_x8 => register15_q_net_x2,
      timestamp_regs_io_x9 => tx_start_timestamp_msb_net,
      tx_controller_regs => register1_q_net_x7,
      tx_controller_regs_x0 => register11_q_net_x2,
      tx_controller_regs_x1 => register14_q_net_x2,
      tx_controller_regs_x10 => register5_q_net_x2,
      tx_controller_regs_x11 => register53_q_net_x2,
      tx_controller_regs_x12 => register56_q_net_x2,
      tx_controller_regs_x13 => register57_q_net_x2,
      tx_controller_regs_x14 => register58_q_net_x2,
      tx_controller_regs_x15 => register59_q_net_x2,
      tx_controller_regs_x16 => register6_q_net_x8,
      tx_controller_regs_x17 => register60_q_net_x2,
      tx_controller_regs_x18 => register61_q_net_x2,
      tx_controller_regs_x19 => register66_q_net_x2,
      tx_controller_regs_x2 => register16_q_net_x2,
      tx_controller_regs_x20 => register67_q_net_x2,
      tx_controller_regs_x21 => register7_q_net_x2,
      tx_controller_regs_x22 => register8_q_net_x7,
      tx_controller_regs_x23 => concat1_y_net_x12,
      tx_controller_regs_x24 => concat1_y_net_x13,
      tx_controller_regs_x25 => concat1_y_net_x14,
      tx_controller_regs_x26 => concat1_y_net_x15,
      tx_controller_regs_x3 => register17_q_net_x2,
      tx_controller_regs_x4 => register19_q_net_x2,
      tx_controller_regs_x5 => register2_q_net_x42,
      tx_controller_regs_x6 => register22_q_net_x2,
      tx_controller_regs_x7 => register25_q_net_x2,
      tx_controller_regs_x8 => register3_q_net_x6,
      tx_controller_regs_x9 => register4_q_net_x6
    );

  rx_timers_5b2badea90: entity work.rx_timers_entity_5b2badea90
    port map (
      ce_1 => ce_1_sg_x55,
      clk_1 => clk_1_sg_x55,
      global_reset => b_0_y_net_x9,
      phy_rx_end_ind => phy_rx_end_ind_net,
      phy_rx_end_rxerror => phy_rx_end_rxerror_net,
      phy_tx_end_confirm => phy_tx_done_net,
      reg_postrx_timer1_countto => concat1_y_net_x15,
      reg_postrx_timer1_en => register66_q_net_x2,
      reg_postrx_timer2_countto => concat1_y_net_x13,
      reg_postrx_timer2_en => register67_q_net_x2,
      reg_posttx_timer1_countto => concat1_y_net_x14,
      reg_posttx_timer1_en => register11_q_net_x2,
      reg_posttx_timer2_countto => concat1_y_net_x12,
      reg_posttx_timer2_en => register14_q_net_x2,
      postrx_timer_1_x0 => register8_q_net_x6,
      postrx_timer_2_x0 => register9_q_net_x1,
      posttx_timer_1_x0 => register1_q_net_x4,
      posttx_timer_2_x0 => register2_q_net_x5,
      status_postrx_timer1_running => register2_q_net_x35,
      status_postrx_timer2_running => register2_q_net_x36,
      status_posttx_timer1_running => register2_q_net_x33,
      status_posttx_timer2_running => register2_q_net_x34
    );

  tx_control_a_717cde016b: entity work.tx_control_a_entity_717cde016b
    port map (
      backoff_done => logical5_y_net_x2,
      ce_1 => ce_1_sg_x55,
      clk_1 => clk_1_sg_x55,
      global_reset => b_0_y_net_x9,
      idle_for_difs => relational3_op_net_x1,
      phy_rx_start_ind => phy_rx_start_ind_net,
      phy_tx_end_confirm => phy_tx_done_net,
      postrx_timer1_done => register8_q_net_x6,
      posttx_timer1_done => register1_q_net_x4,
      posttx_timer2_done => register2_q_net_x5,
      reg_tx_a_param_bo_slots => register17_q_net_x2,
      reg_tx_a_param_pktbuf => register16_q_net_x2,
      reg_tx_a_param_postwait_posttxtimer2 => register3_q_net_x6,
      reg_tx_a_param_prewait_postrxtimer1 => register1_q_net_x7,
      reg_tx_a_param_prewait_posttxtimer1 => register2_q_net_x42,
      reg_tx_a_param_txantmask => register25_q_net_x2,
      reg_tx_a_param_txgain_rfa => register19_q_net_x2,
      reg_tx_a_param_txgain_rfb => register53_q_net_x2,
      reg_tx_a_param_txgain_rfc => register56_q_net_x2,
      reg_tx_a_param_txgain_rfd => register57_q_net_x2,
      reg_tx_start_a => register35_q_net_x2,
      register4_x0 => dbg_tx_a_pending_net,
      status_tx_a_done => register2_q_net_x45,
      status_tx_a_pending => register2_q_net_x44,
      status_tx_a_result => register1_q_net_x8,
      status_tx_a_state => mcode_tx_control_a_fsm_state_out_net_x1,
      tx_a_backoff_start => convert_dout_net_x2,
      tx_a_num_bo_slots => register3_q_net_x7,
      tx_a_param_txantmask => register7_q_net_x6,
      tx_a_param_txgain_a => register6_q_net_x6,
      tx_a_param_txgain_b => register8_q_net_x5,
      tx_a_param_txgain_c => register9_q_net_x4,
      tx_a_param_txgain_d => register10_q_net_x4,
      tx_a_phy_start => convert1_dout_net_x4,
      tx_a_pktbuf => register2_q_net_x43
    );

  tx_control_b_bee87440a6: entity work.tx_control_b_entity_bee87440a6
    port map (
      ce_1 => ce_1_sg_x55,
      clk_1 => clk_1_sg_x55,
      global_reset => b_0_y_net_x9,
      nav_zero => inverter1_op_net_x2,
      phy_tx_end_confirm => phy_tx_done_net,
      postrx_timer1_done => register8_q_net_x6,
      postrx_timer2_done => register9_q_net_x1,
      posttx_timer1_done => register1_q_net_x4,
      reg_tx_b_param_pktbuf => register22_q_net_x2,
      reg_tx_b_param_postwait_posttxtimer1 => register7_q_net_x2,
      reg_tx_b_param_prewait_postrxtimer1 => register5_q_net_x2,
      reg_tx_b_param_prewait_postrxtimer2 => register6_q_net_x8,
      reg_tx_b_param_req_zero_nav => register8_q_net_x7,
      reg_tx_b_param_txantmask => register4_q_net_x6,
      reg_tx_b_param_txgain_rfa => register58_q_net_x2,
      reg_tx_b_param_txgain_rfb => register59_q_net_x2,
      reg_tx_b_param_txgain_rfc => register60_q_net_x2,
      reg_tx_b_param_txgain_rfd => register61_q_net_x2,
      reg_tx_start_b => register6_q_net_x4,
      register4_x0 => dbg_tx_b_pending_net,
      status_tx_b_done => register2_q_net_x48,
      status_tx_b_pending => register2_q_net_x47,
      status_tx_b_result => register1_q_net_x6,
      status_tx_b_state => mcode_tx_control_b_fsm_state_out_net_x1,
      tx_b_param_txantmask => register7_q_net_x8,
      tx_b_param_txgain_a => register6_q_net_x9,
      tx_b_param_txgain_b => register8_q_net_x8,
      tx_b_param_txgain_c => register9_q_net_x5,
      tx_b_param_txgain_d => register10_q_net_x5,
      tx_b_phy_start => convert1_dout_net_x5,
      tx_b_pktbuf => register2_q_net_x46
    );

  x64_bit_usec_counter_ceed0591a1: entity work.\x64_bit_usec__counter_entity_ceed0591a1\
    port map (
      ce_1 => ce_1_sg_x55,
      clk_1 => clk_1_sg_x55,
      reg_set_timestamp_lsb => register28_q_net_x2,
      reg_set_timestamp_msb => register27_q_net_x2,
      reg_update_timestamp => b_5_y_net_x2,
      microsecond_timestamp => microsecond_counter_op_net_x2,
      register3_x0 => timestamp_lsb_net,
      register_x1 => timestamp_msb_net
    );

end structural;
