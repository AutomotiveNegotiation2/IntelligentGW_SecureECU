################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwip/doc/NO_SYS_SampleCode.c \
../lwip/doc/ZeroCopyRx.c 

C_DEPS += \
./lwip/doc/NO_SYS_SampleCode.d \
./lwip/doc/ZeroCopyRx.d 

OBJS += \
./lwip/doc/NO_SYS_SampleCode.o \
./lwip/doc/ZeroCopyRx.o 


# Each subdirectory must supply rules for building sources it contributes
lwip/doc/%.o: ../lwip/doc/%.c lwip/doc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT1176DVMAA -DCPU_MIMXRT1176DVMAA_cm7 -D_POSIX_SOURCE -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DLWIP_ENET_FLEXIBLE_CONFIGURATION -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -DPRINTF_ADVANCED_ENABLE=1 -DMCUBOOT_APPLICATION=1 -DUSE_RTOS=1 -DLWIP_DNS=1 -DLWIP_DHCP=1 -DMBEDTLS_CONFIG_FILE='"mbedtls_config_client.h"' -DENET_RXBUFF_NUM=14 -DSHELL_BUFFER_SIZE=128U -DMCUXPRESSO_SDK -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_ICMP6=1 -DMFLASH_FILE_BASEADDR=14221312 -DDEBUG_CONSOLE_RX_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -DCRYPTO_USE_DRIVER_CAAM -DCACHE_MODE_WRITE_THROUGH=1 -DSDK_OS_FREE_RTOS -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\source" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\flash" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\component\phy" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\drivers" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\mbedtls\include" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\mbedtls\library" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\mbedtls\port\ksdk" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\lwip\port" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\lwip\src" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\lwip\src\include" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\flash\mflash\mimxrt1170" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\component\silicon_id" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\freertos\corehttp\source\include" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\freertos\corehttp\source\interface" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\utilities" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\device" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\component\uart" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\component\serial_manager" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\component\lists" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\startup" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\component\gpio" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\flash\mflash" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\llhttp\include" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\freertos\freertos-kernel\include" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\freertos\freertos-kernel\portable\GCC\ARM_CM4F" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\CMSIS" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\board" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\source\config" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\bootutil_port" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\bootutil_port\mcuboot_config" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\bootutil_port\sysflash" -I"C:\BSKO\PRJ\IITP\SW\MCUXpresso_IDE_Workspace\evkmimxrt1170_ota_mcuboot_client_enet\bootutil_port\board_specific" -Og -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lwip-2f-doc

clean-lwip-2f-doc:
	-$(RM) ./lwip/doc/NO_SYS_SampleCode.d ./lwip/doc/NO_SYS_SampleCode.o ./lwip/doc/ZeroCopyRx.d ./lwip/doc/ZeroCopyRx.o

.PHONY: clean-lwip-2f-doc

