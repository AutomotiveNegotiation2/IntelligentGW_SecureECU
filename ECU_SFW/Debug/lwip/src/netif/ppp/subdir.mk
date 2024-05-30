################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/src/netif/ppp/auth.c \
../lwip/src/netif/ppp/ccp.c \
../lwip/src/netif/ppp/chap-md5.c \
../lwip/src/netif/ppp/chap-new.c \
../lwip/src/netif/ppp/chap_ms.c \
../lwip/src/netif/ppp/demand.c \
../lwip/src/netif/ppp/eap.c \
../lwip/src/netif/ppp/ecp.c \
../lwip/src/netif/ppp/eui64.c \
../lwip/src/netif/ppp/fsm.c \
../lwip/src/netif/ppp/ipcp.c \
../lwip/src/netif/ppp/ipv6cp.c \
../lwip/src/netif/ppp/lcp.c \
../lwip/src/netif/ppp/magic.c \
../lwip/src/netif/ppp/mppe.c \
../lwip/src/netif/ppp/multilink.c \
../lwip/src/netif/ppp/ppp.c \
../lwip/src/netif/ppp/pppapi.c \
../lwip/src/netif/ppp/pppcrypt.c \
../lwip/src/netif/ppp/pppoe.c \
../lwip/src/netif/ppp/pppol2tp.c \
../lwip/src/netif/ppp/pppos.c \
../lwip/src/netif/ppp/upap.c \
../lwip/src/netif/ppp/utils.c \
../lwip/src/netif/ppp/vj.c 

C_DEPS += \
./lwip/src/netif/ppp/auth.d \
./lwip/src/netif/ppp/ccp.d \
./lwip/src/netif/ppp/chap-md5.d \
./lwip/src/netif/ppp/chap-new.d \
./lwip/src/netif/ppp/chap_ms.d \
./lwip/src/netif/ppp/demand.d \
./lwip/src/netif/ppp/eap.d \
./lwip/src/netif/ppp/ecp.d \
./lwip/src/netif/ppp/eui64.d \
./lwip/src/netif/ppp/fsm.d \
./lwip/src/netif/ppp/ipcp.d \
./lwip/src/netif/ppp/ipv6cp.d \
./lwip/src/netif/ppp/lcp.d \
./lwip/src/netif/ppp/magic.d \
./lwip/src/netif/ppp/mppe.d \
./lwip/src/netif/ppp/multilink.d \
./lwip/src/netif/ppp/ppp.d \
./lwip/src/netif/ppp/pppapi.d \
./lwip/src/netif/ppp/pppcrypt.d \
./lwip/src/netif/ppp/pppoe.d \
./lwip/src/netif/ppp/pppol2tp.d \
./lwip/src/netif/ppp/pppos.d \
./lwip/src/netif/ppp/upap.d \
./lwip/src/netif/ppp/utils.d \
./lwip/src/netif/ppp/vj.d 

OBJS += \
./lwip/src/netif/ppp/auth.o \
./lwip/src/netif/ppp/ccp.o \
./lwip/src/netif/ppp/chap-md5.o \
./lwip/src/netif/ppp/chap-new.o \
./lwip/src/netif/ppp/chap_ms.o \
./lwip/src/netif/ppp/demand.o \
./lwip/src/netif/ppp/eap.o \
./lwip/src/netif/ppp/ecp.o \
./lwip/src/netif/ppp/eui64.o \
./lwip/src/netif/ppp/fsm.o \
./lwip/src/netif/ppp/ipcp.o \
./lwip/src/netif/ppp/ipv6cp.o \
./lwip/src/netif/ppp/lcp.o \
./lwip/src/netif/ppp/magic.o \
./lwip/src/netif/ppp/mppe.o \
./lwip/src/netif/ppp/multilink.o \
./lwip/src/netif/ppp/ppp.o \
./lwip/src/netif/ppp/pppapi.o \
./lwip/src/netif/ppp/pppcrypt.o \
./lwip/src/netif/ppp/pppoe.o \
./lwip/src/netif/ppp/pppol2tp.o \
./lwip/src/netif/ppp/pppos.o \
./lwip/src/netif/ppp/upap.o \
./lwip/src/netif/ppp/utils.o \
./lwip/src/netif/ppp/vj.o 


# Each subdirectory must supply rules for building sources it contributes
lwip/src/netif/ppp/%.o: ../lwip/src/netif/ppp/%.c lwip/src/netif/ppp/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT1176DVMAA -DCPU_MIMXRT1176DVMAA_cm7 -D_POSIX_SOURCE -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DLWIP_ENET_FLEXIBLE_CONFIGURATION -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -DPRINTF_ADVANCED_ENABLE=1 -DMCUBOOT_APPLICATION=1 -DUSE_RTOS=1 -DLWIP_DNS=1 -DLWIP_DHCP=1 -DMBEDTLS_CONFIG_FILE='"mbedtls_config_client.h"' -DENET_RXBUFF_NUM=14 -DSHELL_BUFFER_SIZE=128U -DMCUXPRESSO_SDK -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_ICMP6=1 -DMFLASH_FILE_BASEADDR=14221312 -DDEBUG_CONSOLE_RX_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -DCRYPTO_USE_DRIVER_CAAM -DCACHE_MODE_WRITE_THROUGH=1 -DSDK_OS_FREE_RTOS -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\source" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\Crypto\inc" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\Crypto\key" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\Crypto\sample_bin" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\Crypto\test_src\inc" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\flash" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\phy" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\drivers" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\mbedtls\include" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\mbedtls\library" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\mbedtls\port\ksdk" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\lwip\port" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\lwip\src" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\lwip\src\include" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\flash\mflash\mimxrt1170" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\silicon_id" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\freertos\corehttp\source\include" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\freertos\corehttp\source\interface" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\utilities" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\device" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\uart" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\serial_manager" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\lists" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\startup" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\gpio" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\flash\mflash" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\llhttp\include" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\freertos\freertos-kernel\include" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\freertos\freertos-kernel\portable\GCC\ARM_CM4F" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\CMSIS" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\board" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\source\config" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\bootutil_port" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\bootutil_port\mcuboot_config" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\bootutil_port\sysflash" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\bootutil_port\board_specific" -Og -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lwip-2f-src-2f-netif-2f-ppp

clean-lwip-2f-src-2f-netif-2f-ppp:
	-$(RM) ./lwip/src/netif/ppp/auth.d ./lwip/src/netif/ppp/auth.o ./lwip/src/netif/ppp/ccp.d ./lwip/src/netif/ppp/ccp.o ./lwip/src/netif/ppp/chap-md5.d ./lwip/src/netif/ppp/chap-md5.o ./lwip/src/netif/ppp/chap-new.d ./lwip/src/netif/ppp/chap-new.o ./lwip/src/netif/ppp/chap_ms.d ./lwip/src/netif/ppp/chap_ms.o ./lwip/src/netif/ppp/demand.d ./lwip/src/netif/ppp/demand.o ./lwip/src/netif/ppp/eap.d ./lwip/src/netif/ppp/eap.o ./lwip/src/netif/ppp/ecp.d ./lwip/src/netif/ppp/ecp.o ./lwip/src/netif/ppp/eui64.d ./lwip/src/netif/ppp/eui64.o ./lwip/src/netif/ppp/fsm.d ./lwip/src/netif/ppp/fsm.o ./lwip/src/netif/ppp/ipcp.d ./lwip/src/netif/ppp/ipcp.o ./lwip/src/netif/ppp/ipv6cp.d ./lwip/src/netif/ppp/ipv6cp.o ./lwip/src/netif/ppp/lcp.d ./lwip/src/netif/ppp/lcp.o ./lwip/src/netif/ppp/magic.d ./lwip/src/netif/ppp/magic.o ./lwip/src/netif/ppp/mppe.d ./lwip/src/netif/ppp/mppe.o ./lwip/src/netif/ppp/multilink.d ./lwip/src/netif/ppp/multilink.o ./lwip/src/netif/ppp/ppp.d ./lwip/src/netif/ppp/ppp.o ./lwip/src/netif/ppp/pppapi.d ./lwip/src/netif/ppp/pppapi.o ./lwip/src/netif/ppp/pppcrypt.d ./lwip/src/netif/ppp/pppcrypt.o ./lwip/src/netif/ppp/pppoe.d ./lwip/src/netif/ppp/pppoe.o ./lwip/src/netif/ppp/pppol2tp.d ./lwip/src/netif/ppp/pppol2tp.o ./lwip/src/netif/ppp/pppos.d ./lwip/src/netif/ppp/pppos.o ./lwip/src/netif/ppp/upap.d ./lwip/src/netif/ppp/upap.o ./lwip/src/netif/ppp/utils.d ./lwip/src/netif/ppp/utils.o ./lwip/src/netif/ppp/vj.d ./lwip/src/netif/ppp/vj.o

.PHONY: clean-lwip-2f-src-2f-netif-2f-ppp

