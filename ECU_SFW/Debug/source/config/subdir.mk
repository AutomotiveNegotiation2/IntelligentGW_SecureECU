################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/config/core_http_config.c 

C_DEPS += \
./source/config/core_http_config.d 

OBJS += \
./source/config/core_http_config.o 


# Each subdirectory must supply rules for building sources it contributes
source/config/%.o: ../source/config/%.c source/config/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT1176DVMAA -DCPU_MIMXRT1176DVMAA_cm7 -D_POSIX_SOURCE -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DLWIP_ENET_FLEXIBLE_CONFIGURATION -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -DPRINTF_ADVANCED_ENABLE=1 -DMCUBOOT_APPLICATION=1 -DUSE_RTOS=1 -DLWIP_DNS=1 -DLWIP_DHCP=1 -DMBEDTLS_CONFIG_FILE='"mbedtls_config_client.h"' -DENET_RXBUFF_NUM=14 -DSHELL_BUFFER_SIZE=128U -DMCUXPRESSO_SDK -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_ICMP6=1 -DMFLASH_FILE_BASEADDR=14221312 -DDEBUG_CONSOLE_RX_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -DCRYPTO_USE_DRIVER_CAAM -DCACHE_MODE_WRITE_THROUGH=1 -DSDK_OS_FREE_RTOS -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\source" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\Crypto\inc" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\Crypto\key" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\Crypto\sample_bin" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\Crypto\test_src\inc" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\flash" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\phy" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\drivers" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\mbedtls\include" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\mbedtls\library" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\mbedtls\port\ksdk" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\lwip\port" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\lwip\src" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\lwip\src\include" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\flash\mflash\mimxrt1170" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\silicon_id" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\freertos\corehttp\source\include" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\freertos\corehttp\source\interface" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\utilities" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\device" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\uart" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\serial_manager" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\lists" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\startup" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\component\gpio" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\flash\mflash" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\llhttp\include" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\freertos\freertos-kernel\include" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\freertos\freertos-kernel\portable\GCC\ARM_CM4F" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\CMSIS" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\board" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\source\config" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\bootutil_port" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\bootutil_port\mcuboot_config" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\bootutil_port\sysflash" -I"D:\Work\Gateway\FW\NXP\ECU_NETIF\ECU_SFW\trunk\bootutil_port\board_specific" -Og -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source-2f-config

clean-source-2f-config:
	-$(RM) ./source/config/core_http_config.d ./source/config/core_http_config.o

.PHONY: clean-source-2f-config

