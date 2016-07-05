################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/wlan_exp_node_ap.c \
../src/wlan_mac_ap.c \
../src/wlan_mac_ap_uart_menu.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/wlan_exp_node_ap.o \
./src/wlan_mac_ap.o \
./src/wlan_mac_ap_uart_menu.o 

C_DEPS += \
./src/wlan_exp_node_ap.d \
./src/wlan_mac_ap.d \
./src/wlan_mac_ap_uart_menu.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ap\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


