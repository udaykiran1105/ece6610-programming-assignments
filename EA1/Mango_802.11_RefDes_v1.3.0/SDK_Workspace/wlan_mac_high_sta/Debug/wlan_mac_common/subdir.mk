################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_common/wlan_mac_ipc_util.c 

OBJS += \
./wlan_mac_common/wlan_mac_ipc_util.o 

C_DEPS += \
./wlan_mac_common/wlan_mac_ipc_util.d 


# Each subdirectory must supply rules for building sources it contributes
wlan_mac_common/wlan_mac_ipc_util.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_common/wlan_mac_ipc_util.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_sta\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


