#
# Utility makefile to check important paths needed for build
#

sdk_check_paths:
ifeq ($(BUILD_CPU_MPU1),yes)
	@if [ ! -d $(GCC_LINUX_ARM_ROOT) ]; then echo 'ERROR: $(GCC_LINUX_ARM_ROOT) not found !!!'; echo 'Ensure all dependencies have been downloaded as per http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/vision_apps/docs/user_guide/ENVIRONMENT_SETUP.html#ADDITIONAL_DOWNLOADS'; exit 1; fi
ifeq ($(BUILD_LINUX_A72),yes)
	@if [ ! -d $(LINUX_FS_PATH)/usr/include ]; then echo 'ERROR: $(LINUX_FS_PATH)/usr/include not found !!!'; echo 'Ensure all dependencies have been downloaded as per http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/vision_apps/docs/user_guide/ENVIRONMENT_SETUP.html#ENVIRONMENT_SETUP_STEP2'; exit 1; fi
endif
endif
	@if [ ! -d $(TI_SECURE_DEV_PKG) ]; then echo 'ERROR: $(TI_SECURE_DEV_PKG) not found !!!'; exit 1; fi
	@if [ ! -d $(CGT7X_ROOT) ]; then echo 'ERROR: $(CGT7X_ROOT) not found !!!'; exit 1; fi
	@if [ ! -d $(TIARMCGT_LLVM_ROOT) ]; then echo 'ERROR: $(TIARMCGT_LLVM_ROOT) not found !!!'; exit 1; fi
	@if [ ! -d $(VXLIB_PATH) ]; then echo 'ERROR: $(VXLIB_PATH) not found !!!'; exit 1; fi
ifneq ($(SOC), am62a)
ifeq ($(BUILD_EMULATION_MODE),yes)
	@if [ ! -d $(J7_C_MODELS_PATH) ]; then echo 'ERROR: $(J7_C_MODELS_PATH) not found !!!'; echo 'Ensure all dependencies have been downloaded as per http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/vision_apps/docs/user_guide/ENVIRONMENT_SETUP.html#autotoc_md4'; exit 1; fi
endif
endif
	@if [ ! -d $(IVISION_PATH) ]; then echo 'ERROR: $(IVISION_PATH) not found !!!'; exit 1; fi
	@if [ ! -d $(IMAGING_PATH) ]; then echo 'ERROR: $(IMAGING_PATH) not found !!!'; exit 1; fi
	@if [ ! -d $(MMALIB_PATH) ]; then echo 'ERROR: $(MMALIB_PATH) not found !!!'; exit 1; fi
	@if [ ! -d $(PDK_PATH) ]; then echo 'ERROR: $(PDK_PATH) not found !!!'; exit 1; fi
	@if [ ! -d $(VISION_APPS_PATH) ]; then echo 'ERROR: $(VISION_APPS_PATH) not found !!!'; exit 1; fi
	@if [ ! -d $(TIOVX_PATH) ]; then echo 'ERROR: $(TIOVX_PATH) not found !!!'; exit 1; fi
ifneq ($(SOC), am62a)
	@if [ ! -d $(TIADALG_PATH) ]; then echo 'ERROR: $(TIADALG_PATH) not found !!!'; exit 1; fi
	@if [ ! -d $(PTK_PATH) ]; then echo 'ERROR: $(PTK_PATH) not found !!!'; exit 1; fi
ifneq ($(SOC), j721s2)
	@if [ ! -d $(REMOTE_DEVICE_PATH) ]; then echo 'ERROR: $(REMOTE_DEVICE_PATH) not found !!!'; exit 1; fi
endif
endif
ifeq ($(SOC),j721e)
	@if [ ! -d $(CGT6X_ROOT) ]; then echo 'ERROR: $(CGT6X_ROOT) not found !!!'; exit 1; fi
endif
ifeq ($(BUILD_QNX_A72),yes)
	@if [ ! -d $(QNX_BASE) ]; then echo 'ERROR: $(QNX_BASE) not found !!!'; echo 'Ensure all dependencies have been downloaded as per http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/vision_apps/docs/user_guide/ENVIRONMENT_SETUP.html#ENVIRONMENT_SETUP_QNX'; exit 1; fi
endif

	@echo "# SDK paths OK !!!"
