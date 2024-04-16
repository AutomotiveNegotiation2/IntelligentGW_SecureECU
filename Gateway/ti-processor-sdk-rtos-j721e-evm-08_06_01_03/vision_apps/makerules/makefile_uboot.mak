#
# Utility makefile to build u-boot with MCU1_0 image
#
# Edit this file to suit your specific build needs
#

ifeq ($(PROFILE), $(filter $(PROFILE),debug all))
UBOOT_APP_PROFILE=debug
endif
ifeq ($(PROFILE), $(filter $(PROFILE),release all))
UBOOT_APP_PROFILE=release
endif

VISION_APPS_LINUX_DM=$(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(UBOOT_APP_PROFILE)/vx_app_rtos_linux_mcu1_0.out
VISION_APPS_LINUX_DM_STRIP=$(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(UBOOT_APP_PROFILE)/vx_app_rtos_linux_mcu1_0_strip.out

VISION_APPS_QNX_DM=$(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(UBOOT_APP_PROFILE)/vx_app_rtos_qnx_mcu1_0.out
VISION_APPS_QNX_DM_STRIP=$(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(UBOOT_APP_PROFILE)/vx_app_rtos_qnx_mcu1_0_strip.out

uboot_check:
ifeq ($(BUILD_TARGET_MODE),yes)
	@if [ ! -d $(PSDK_LINUX_PATH) ]; then echo 'ERROR: $(PSDK_LINUX_PATH) not found !!!'; exit 1; fi
	@if [ ! -d $(PSDK_LINUX_PATH)/board-support/u-boot-* ]; then echo 'ERROR: $(PSDK_LINUX_PATH)/board-support/u-boot-* not found !!!'; exit 1; fi
	@if [ ! -f $(PSDK_LINUX_PATH)/board-support/prebuilt-images/bl31.bin ]; then echo 'ERROR: $(PSDK_LINUX_PATH)/board-support/prebuilt-images/bl31.bin not found !!!'; exit 1; fi
	@if [ ! -f $(PSDK_LINUX_PATH)/board-support/prebuilt-images/bl32.bin ]; then echo 'ERROR: $(PSDK_LINUX_PATH)/board-support/prebuilt-images/bl32.bin not found !!!'; exit 1; fi
endif

uboot_check_firmware:
ifeq ($(BUILD_TARGET_MODE),yes)
ifeq ($(BUILD_LINUX_A72),yes)
	@if [ ! -f  $(VISION_APPS_LINUX_DM) ]; then echo 'ERROR: $(VISION_APPS_LINUX_DM) not found !!!'; exit 1; fi
endif
ifeq ($(BUILD_QNX_A72),yes)
	@if [ ! -f $(VISION_APPS_QNX_DM) ]; then echo 'ERROR: $(VISION_APPS_QNX_DM) !!!'; exit 1; fi
endif
endif

uboot_clean: uboot_check
ifeq ($(BUILD_TARGET_MODE),yes)
	$(MAKE) -C $(PSDK_LINUX_PATH)/board-support/u-boot-* clean
	rm -rf $(PSDK_LINUX_PATH)/board-support/u-boot-*/$(SOC)-arm64-linux/
	rm -rf $(PSDK_LINUX_PATH)/board-support/u-boot-*/$(SOC)-arm64-qnx/
endif

uboot: uboot_check uboot_check_firmware
ifeq ($(BUILD_TARGET_MODE),yes)
ifeq ($(BUILD_LINUX_A72),yes)
	cp $(VISION_APPS_LINUX_DM) $(VISION_APPS_LINUX_DM_STRIP)
	$(TIARMCGT_LLVM_ROOT)/bin/tiarmstrip -p $(VISION_APPS_LINUX_DM_STRIP)
ifeq  ($(SOC), am62a)
	$(MAKE) -C $(PSDK_LINUX_PATH)/board-support/u-boot-* ARCH=arm CROSS_COMPILE=$(GCC_LINUX_ARM_ROOT)/bin/aarch64-none-linux-gnu- O=$(SOC)-arm64-linux -j8 $(SOC)x_evm_a53_defconfig
else
	$(MAKE) -C $(PSDK_LINUX_PATH)/board-support/u-boot-* ARCH=arm CROSS_COMPILE=$(GCC_LINUX_ARM_ROOT)/bin/aarch64-none-linux-gnu- O=$(SOC)-arm64-linux -j8 $(SOC)_evm_a72_defconfig
endif
	$(MAKE) -C $(PSDK_LINUX_PATH)/board-support/u-boot-* ARCH=arm CROSS_COMPILE=$(GCC_LINUX_ARM_ROOT)/bin/aarch64-none-linux-gnu- ATF=$(PSDK_LINUX_PATH)/board-support/prebuilt-images/bl31.bin TEE=$(PSDK_LINUX_PATH)/board-support/prebuilt-images/bl32.bin DM=$(VISION_APPS_LINUX_DM_STRIP) O=$(SOC)-arm64-linux
endif
ifeq ($(BUILD_QNX_A72),yes)
	cp $(VISION_APPS_QNX_DM) $(VISION_APPS_QNX_DM_STRIP)
	$(TIARMCGT_LLVM_ROOT)/bin/tiarmstrip -p $(VISION_APPS_QNX_DM_STRIP)
ifeq  ($(SOC), am62a)
	$(MAKE) -C $(PSDK_LINUX_PATH)/board-support/u-boot-* ARCH=arm CROSS_COMPILE=$(GCC_LINUX_ARM_ROOT)/bin/aarch64-none-linux-gnu- O=$(SOC)-arm64-qnx -j8 $(SOC)x_evm_a53_defconfig
else
	$(MAKE) -C $(PSDK_LINUX_PATH)/board-support/u-boot-* ARCH=arm CROSS_COMPILE=$(GCC_LINUX_ARM_ROOT)/bin/aarch64-none-linux-gnu- O=$(SOC)-arm64-qnx -j8 $(SOC)_evm_a72_defconfig
endif
	$(MAKE) -C $(PSDK_LINUX_PATH)/board-support/u-boot-* ARCH=arm CROSS_COMPILE=$(GCC_LINUX_ARM_ROOT)/bin/aarch64-none-linux-gnu- ATF=$(PSDK_LINUX_PATH)/board-support/prebuilt-images/bl31.bin TEE=$(PSDK_LINUX_PATH)/board-support/prebuilt-images/bl32.bin DM=$(VISION_APPS_QNX_DM_STRIP) O=$(SOC)-arm64-qnx
endif
endif

uboot_linux_install_sd: uboot_check
ifeq ($(BUILD_TARGET_MODE),yes)
	cp $(PSDK_LINUX_PATH)/board-support/u-boot-*/$(SOC)-arm64-linux/tispl.bin $(LINUX_SD_FS_BOOT_PATH)/
	cp $(PSDK_LINUX_PATH)/board-support/u-boot-*/$(SOC)-arm64-linux/u-boot.img $(LINUX_SD_FS_BOOT_PATH)/
	sync
endif

uboot_qnx_install_sd: uboot_check
ifeq ($(BUILD_TARGET_MODE),yes)
	cp $(PSDK_LINUX_PATH)/board-support/u-boot-*/$(SOC)-arm64-qnx/tispl.bin $(QNX_SD_FS_BOOT_PATH)/
	cp $(PSDK_LINUX_PATH)/board-support/u-boot-*/$(SOC)-arm64-qnx/u-boot.img $(QNX_SD_FS_BOOT_PATH)/
	sync
endif

.PHONY: uboot_check uboot_check_firmware uboot_clean uboot uboot_linux_install_sd uboot_qnx_install_sd
