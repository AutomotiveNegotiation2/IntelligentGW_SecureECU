################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include xip/subdir.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/config/subdir.mk
-include source/subdir.mk
-include mbedtls/port/ksdk/subdir.mk
-include mbedtls/library/subdir.mk
-include lwip/src/netif/ppp/subdir.mk
-include lwip/src/netif/subdir.mk
-include lwip/src/core/ipv6/subdir.mk
-include lwip/src/core/ipv4/subdir.mk
-include lwip/src/core/subdir.mk
-include lwip/src/api/subdir.mk
-include lwip/port/subdir.mk
-include llhttp/src/subdir.mk
-include freertos/freertos-kernel/portable/MemMang/subdir.mk
-include freertos/freertos-kernel/portable/GCC/ARM_CM4F/subdir.mk
-include freertos/freertos-kernel/subdir.mk
-include freertos/corehttp/source/subdir.mk
-include flash/mflash/mimxrt1170/subdir.mk
-include flash/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/silicon_id/subdir.mk
-include component/serial_manager/subdir.mk
-include component/phy/subdir.mk
-include component/lists/subdir.mk
-include component/gpio/subdir.mk
-include bootutil_port/board_specific/subdir.mk
-include board/subdir.mk
-include Crypto/test_src/src/subdir.mk
-include Crypto/src/subdir.mk
-include Crypto/sample_bin/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := trunk
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: trunk.axf

# Tool invocations
trunk.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -no-warn-rwx-segments -Xlinker -Map="trunk.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -T trunk_Debug.ld -o "trunk.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) trunk.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "trunk.axf" ; arm-none-eabi-objcopy -v -O binary "trunk.axf" "trunk.bin" ; # checksum -p MIMXRT1176xxxxx -d "trunk.bin"
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
