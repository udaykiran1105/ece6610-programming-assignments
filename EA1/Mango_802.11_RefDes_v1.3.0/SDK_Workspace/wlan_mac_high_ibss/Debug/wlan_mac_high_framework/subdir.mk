################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_exp_common.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_exp_node.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_exp_transport.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_addr_filter.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_bss_info.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_dl_list.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_entries.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_eth_util.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_event_log.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_high.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_ltg.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_packet_types.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_queue.c \
G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_schedule.c 

OBJS += \
./wlan_mac_high_framework/wlan_exp_common.o \
./wlan_mac_high_framework/wlan_exp_node.o \
./wlan_mac_high_framework/wlan_exp_transport.o \
./wlan_mac_high_framework/wlan_mac_addr_filter.o \
./wlan_mac_high_framework/wlan_mac_bss_info.o \
./wlan_mac_high_framework/wlan_mac_dl_list.o \
./wlan_mac_high_framework/wlan_mac_entries.o \
./wlan_mac_high_framework/wlan_mac_eth_util.o \
./wlan_mac_high_framework/wlan_mac_event_log.o \
./wlan_mac_high_framework/wlan_mac_high.o \
./wlan_mac_high_framework/wlan_mac_ltg.o \
./wlan_mac_high_framework/wlan_mac_packet_types.o \
./wlan_mac_high_framework/wlan_mac_queue.o \
./wlan_mac_high_framework/wlan_mac_schedule.o 

C_DEPS += \
./wlan_mac_high_framework/wlan_exp_common.d \
./wlan_mac_high_framework/wlan_exp_node.d \
./wlan_mac_high_framework/wlan_exp_transport.d \
./wlan_mac_high_framework/wlan_mac_addr_filter.d \
./wlan_mac_high_framework/wlan_mac_bss_info.d \
./wlan_mac_high_framework/wlan_mac_dl_list.d \
./wlan_mac_high_framework/wlan_mac_entries.d \
./wlan_mac_high_framework/wlan_mac_eth_util.d \
./wlan_mac_high_framework/wlan_mac_event_log.d \
./wlan_mac_high_framework/wlan_mac_high.d \
./wlan_mac_high_framework/wlan_mac_ltg.d \
./wlan_mac_high_framework/wlan_mac_packet_types.d \
./wlan_mac_high_framework/wlan_mac_queue.d \
./wlan_mac_high_framework/wlan_mac_schedule.d 


# Each subdirectory must supply rules for building sources it contributes
wlan_mac_high_framework/wlan_exp_common.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_exp_common.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_exp_node.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_exp_node.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_exp_transport.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_exp_transport.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_mac_addr_filter.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_addr_filter.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_mac_bss_info.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_bss_info.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_mac_dl_list.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_dl_list.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_mac_entries.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_entries.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_mac_eth_util.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_eth_util.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_mac_event_log.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_event_log.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_mac_high.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_high.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_mac_ltg.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_ltg.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_mac_packet_types.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_packet_types.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_mac_queue.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_queue.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '

wlan_mac_high_framework/wlan_mac_schedule.o: G:/MS/Mango_802.11_RefDes_v1.3.0/EDK_Projects/Mango_802.11_RefDes_v1.3.0/SDK_Workspace/wlan_mac_shared/wlan_mac_high_framework/wlan_mac_schedule.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -Os -g3 -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_high_ibss\src\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_common\include" -I"G:\MS\Mango_802.11_RefDes_v1.3.0\EDK_Projects\Mango_802.11_RefDes_v1.3.0\SDK_Workspace\wlan_mac_shared\wlan_mac_high_framework\include" -c -fmessage-length=0 -Wl,--no-relax -I../../wlan_bsp_cpu_high/mb_high/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.40.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


