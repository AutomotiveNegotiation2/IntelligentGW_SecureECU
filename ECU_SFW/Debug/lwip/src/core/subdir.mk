################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/core/altcp.c \
../lwip/src/core/altcp_alloc.c \
../lwip/src/core/altcp_tcp.c \
../lwip/src/core/def.c \
../lwip/src/core/dns.c \
../lwip/src/core/inet_chksum.c \
../lwip/src/core/init.c \
../lwip/src/core/ip.c \
../lwip/src/core/mem.c \
../lwip/src/core/memp.c \
../lwip/src/core/netif.c \
../lwip/src/core/pbuf.c \
../lwip/src/core/raw.c \
../lwip/src/core/stats.c \
../lwip/src/core/sys.c \
../lwip/src/core/tcp.c \
../lwip/src/core/tcp_in.c \
../lwip/src/core/tcp_out.c \
../lwip/src/core/timeouts.c \
../lwip/src/core/udp.c 

C_DEPS += \
./lwip/src/core/altcp.d \
./lwip/src/core/altcp_alloc.d \
./lwip/src/core/altcp_tcp.d \
./lwip/src/core/def.d \
./lwip/src/core/dns.d \
./lwip/src/core/inet_chksum.d \
./lwip/src/core/init.d \
./lwip/src/core/ip.d \
./lwip/src/core/mem.d \
./lwip/src/core/memp.d \
./lwip/src/core/netif.d \
./lwip/src/core/pbuf.d \
./lwip/src/core/raw.d \
./lwip/src/core/stats.d \
./lwip/src/core/sys.d \
./lwip/src/core/tcp.d \
./lwip/src/core/tcp_in.d \
./lwip/src/core/tcp_out.d \
./lwip/src/core/timeouts.d \
./lwip/src/core/udp.d 

OBJS += \
./lwip/src/core/altcp.o \
./lwip/src/core/altcp_alloc.o \
./lwip/src/core/altcp_tcp.o \
./lwip/src/core/def.o \
./lwip/src/core/dns.o \
./lwip/src/core/inet_chksum.o \
./lwip/src/core/init.o \
./lwip/src/core/ip.o \
./lwip/src/core/mem.o \
./lwip/src/core/memp.o \
./lwip/src/core/netif.o \
./lwip/src/core/pbuf.o \
./lwip/src/core/raw.o \
./lwip/src/core/stats.o \
./lwip/src/core/sys.o \
./lwip/src/core/tcp.o \
./lwip/src/core/tcp_in.o \
./lwip/src/core/tcp_out.o \
./lwip/src/core/timeouts.o \
./lwip/src/core/udp.o 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/core/%.o: ../lwip/src/core/%.c lwip/src/core/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT1176DVMAA -DCPU_MIMXRT1176DVMAA_cm7 -D_POSIX_SOURCE -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DLWIP_ENET_FLEXIBLE_CONFIGURATION -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -DPRINTF_ADVANCED_ENABLE=1 -DMCUBOOT_APPLICATION=1 -DUSE_RTOS=0 -DLWIP_DHCP=0 -DMBEDTLS_CONFIG_FILE='"mbedtls_config_client.h"' -DENET_RXBUFF_NUM=14 -DSHELL_BUFFER_SIZE=128U -DMCUXPRESSO_SDK -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_ICMP6=1 -DMFLASH_FILE_BASEADDR=14221312 -DDEBUG_CONSOLE_RX_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -DCRYPTO_USE_DRIVER_CAAM -DCACHE_MODE_WRITE_THROUGH=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\source" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\Crypto\inc" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\Crypto\key" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\Crypto\sample_bin" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\Crypto\test_src\inc" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\flash" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\phy" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\drivers" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\mbedtls\include" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\mbedtls\library" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\mbedtls\port\ksdk" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\lwip\port" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\lwip\src" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\lwip\src\include" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\flash\mflash\mimxrt1170" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\silicon_id" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\utilities" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\device" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\uart" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\serial_manager" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\lists" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\startup" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\gpio" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\flash\mflash" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\freertos\freertos-kernel\include" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\freertos\freertos-kernel\portable\GCC\ARM_CM4F" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\CMSIS" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\board" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\source\config" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\bootutil_port" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\bootutil_port\mcuboot_config" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\bootutil_port\sysflash" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\bootutil_port\board_specific" -Og -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lwip-2f-src-2f-core

clean-lwip-2f-src-2f-core:
	-$(RM) ./lwip/src/core/altcp.d ./lwip/src/core/altcp.o ./lwip/src/core/altcp_alloc.d ./lwip/src/core/altcp_alloc.o ./lwip/src/core/altcp_tcp.d ./lwip/src/core/altcp_tcp.o ./lwip/src/core/def.d ./lwip/src/core/def.o ./lwip/src/core/dns.d ./lwip/src/core/dns.o ./lwip/src/core/inet_chksum.d ./lwip/src/core/inet_chksum.o ./lwip/src/core/init.d ./lwip/src/core/init.o ./lwip/src/core/ip.d ./lwip/src/core/ip.o ./lwip/src/core/mem.d ./lwip/src/core/mem.o ./lwip/src/core/memp.d ./lwip/src/core/memp.o ./lwip/src/core/netif.d ./lwip/src/core/netif.o ./lwip/src/core/pbuf.d ./lwip/src/core/pbuf.o ./lwip/src/core/raw.d ./lwip/src/core/raw.o ./lwip/src/core/stats.d ./lwip/src/core/stats.o ./lwip/src/core/sys.d ./lwip/src/core/sys.o ./lwip/src/core/tcp.d ./lwip/src/core/tcp.o ./lwip/src/core/tcp_in.d ./lwip/src/core/tcp_in.o ./lwip/src/core/tcp_out.d ./lwip/src/core/tcp_out.o ./lwip/src/core/timeouts.d ./lwip/src/core/timeouts.o ./lwip/src/core/udp.d ./lwip/src/core/udp.o

.PHONY: clean-lwip-2f-src-2f-core

