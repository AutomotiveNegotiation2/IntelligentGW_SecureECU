################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_anatop_ai.c \
../drivers/fsl_caam.c \
../drivers/fsl_cache.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dcdc.c \
../drivers/fsl_enet.c \
../drivers/fsl_flexspi.c \
../drivers/fsl_gpc.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_mu.c \
../drivers/fsl_pmu.c \
../drivers/fsl_soc_src.c 

C_DEPS += \
./drivers/fsl_anatop_ai.d \
./drivers/fsl_caam.d \
./drivers/fsl_cache.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dcdc.d \
./drivers/fsl_enet.d \
./drivers/fsl_flexspi.d \
./drivers/fsl_gpc.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_mu.d \
./drivers/fsl_pmu.d \
./drivers/fsl_soc_src.d 

OBJS += \
./drivers/fsl_anatop_ai.o \
./drivers/fsl_caam.o \
./drivers/fsl_cache.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dcdc.o \
./drivers/fsl_enet.o \
./drivers/fsl_flexspi.o \
./drivers/fsl_gpc.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_mu.o \
./drivers/fsl_pmu.o \
./drivers/fsl_soc_src.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MIMXRT1176DVMAA -DCPU_MIMXRT1176DVMAA_cm7 -D_POSIX_SOURCE -DSDK_DEBUGCONSOLE=1 -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DFSL_FEATURE_PHYKSZ8081_USE_RMII50M_MODE -DLWIP_ENET_FLEXIBLE_CONFIGURATION -DFSL_SDK_ENABLE_DRIVER_CACHE_CONTROL=1 -DPRINTF_ADVANCED_ENABLE=1 -DMCUBOOT_APPLICATION=1 -DUSE_RTOS=0 -DLWIP_DHCP=0 -DMBEDTLS_CONFIG_FILE='"mbedtls_config_client.h"' -DENET_RXBUFF_NUM=14 -DSHELL_BUFFER_SIZE=128U -DMCUXPRESSO_SDK -DLWIP_DISABLE_PBUF_POOL_SIZE_SANITY_CHECKS=1 -DCHECKSUM_GEN_ICMP6=1 -DCHECKSUM_CHECK_ICMP6=1 -DMFLASH_FILE_BASEADDR=14221312 -DDEBUG_CONSOLE_RX_ENABLE=0 -DSERIAL_PORT_TYPE_UART=1 -DCRYPTO_USE_DRIVER_CAAM -DCACHE_MODE_WRITE_THROUGH=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\source" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\Crypto\inc" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\Crypto\key" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\Crypto\sample_bin" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\Crypto\test_src\inc" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\flash" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\phy" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\drivers" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\mbedtls\include" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\mbedtls\library" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\mbedtls\port\ksdk" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\lwip\port" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\lwip\src" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\lwip\src\include" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\flash\mflash\mimxrt1170" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\silicon_id" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\utilities" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\device" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\uart" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\serial_manager" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\lists" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\startup" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\component\gpio" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\flash\mflash" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\CMSIS" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\board" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\source\config" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\bootutil_port" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\bootutil_port\mcuboot_config" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\bootutil_port\sysflash" -I"C:\Users\USER\Documents\MCUXpressoIDE_11.9.1_2170\workspace_fw\MCUXpresso_IDE_FW\bootutil_port\board_specific" -Og -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_anatop_ai.d ./drivers/fsl_anatop_ai.o ./drivers/fsl_caam.d ./drivers/fsl_caam.o ./drivers/fsl_cache.d ./drivers/fsl_cache.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dcdc.d ./drivers/fsl_dcdc.o ./drivers/fsl_enet.d ./drivers/fsl_enet.o ./drivers/fsl_flexspi.d ./drivers/fsl_flexspi.o ./drivers/fsl_gpc.d ./drivers/fsl_gpc.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_lpuart.d ./drivers/fsl_lpuart.o ./drivers/fsl_mu.d ./drivers/fsl_mu.o ./drivers/fsl_pmu.d ./drivers/fsl_pmu.o ./drivers/fsl_soc_src.d ./drivers/fsl_soc_src.o

.PHONY: clean-drivers

