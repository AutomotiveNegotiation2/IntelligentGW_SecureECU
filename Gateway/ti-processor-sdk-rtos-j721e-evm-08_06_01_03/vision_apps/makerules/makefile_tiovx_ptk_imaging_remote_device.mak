#
# Utility makefile to build TIOVX, PTK and imaging libaries and related components
#
# Edit this file to suit your specific build needs
#

vxlib:
ifeq ($(BUILD_EMULATION_MODE),yesDISABLE)
ifeq ($(PROFILE), $(filter $(PROFILE),release all))
	TARGET_PLATFORM=PC TARGET_CPU=x86_64 TARGET_SCPU=C66 TARGET_BUILD=release $(MAKE) -C $(VXLIB_PATH) vxlib
	TARGET_PLATFORM=PC TARGET_CPU=x86_64 TARGET_SCPU=C66 TARGET_BUILD=release $(MAKE) -C $(VXLIB_PATH) cp_to_lib
endif
ifeq ($(PROFILE), $(filter $(PROFILE),debug all))
	TARGET_PLATFORM=PC TARGET_CPU=x86_64 TARGET_SCPU=C66 TARGET_BUILD=debug $(MAKE) -C $(VXLIB_PATH) vxlib
	TARGET_PLATFORM=PC TARGET_CPU=x86_64 TARGET_SCPU=C66 TARGET_BUILD=debug $(MAKE) -C $(VXLIB_PATH) cp_to_lib
endif
endif
ifeq ($(BUILD_TARGET_MODE),yes)
ifeq ($(SOC),j721e)
ifeq ($(PROFILE), $(filter $(PROFILE),release all))
	TARGET_PLATFORM=$(TARGET_SOC) TARGET_CPU=C66 TARGET_BUILD=release $(MAKE) -C $(VXLIB_PATH) vxlib
	TARGET_PLATFORM=$(TARGET_SOC) TARGET_CPU=C66 TARGET_BUILD=release $(MAKE) -C $(VXLIB_PATH) cp_to_lib
endif
ifeq ($(PROFILE), $(filter $(PROFILE),debug all))
	TARGET_PLATFORM=$(TARGET_SOC) TARGET_CPU=C66 TARGET_BUILD=debug $(MAKE) -C $(VXLIB_PATH) vxlib
	TARGET_PLATFORM=$(TARGET_SOC) TARGET_CPU=C66 TARGET_BUILD=debug $(MAKE) -C $(VXLIB_PATH) cp_to_lib
endif
endif
ifeq ($(SOC), $(filter $(SOC),j721s2 j784s4 am62a))
ifeq ($(PROFILE), $(filter $(PROFILE),release all))
	TARGET_PLATFORM=$(TARGET_SOC) TARGET_CPU=$(C7X_TARGET) TARGET_BUILD=release $(MAKE) -C $(VXLIB_PATH) vxlib
	TARGET_PLATFORM=$(TARGET_SOC) TARGET_CPU=$(C7X_TARGET) TARGET_BUILD=release $(MAKE) -C $(VXLIB_PATH) cp_to_lib
endif
ifeq ($(PROFILE), $(filter $(PROFILE),debug all))
	TARGET_PLATFORM=$(TARGET_SOC) TARGET_CPU=$(C7X_TARGET) TARGET_BUILD=debug $(MAKE) -C $(VXLIB_PATH) vxlib
	TARGET_PLATFORM=$(TARGET_SOC) TARGET_CPU=$(C7X_TARGET) TARGET_BUILD=debug $(MAKE) -C $(VXLIB_PATH) cp_to_lib
endif
endif
endif

vxlib_scrub:
	$(MAKE) -C $(VXLIB_PATH) scrub

vxlib_clean:
	$(MAKE) -C $(VXLIB_PATH) clean

tiovx:
	$(MAKE) -C $(TIOVX_PATH)

tiovx_clean:
	$(MAKE) -C $(TIOVX_PATH) clean

tiovx_scrub:
	$(MAKE) -C $(TIOVX_PATH) scrub

tiovx_docs:
	$(MAKE) -C $(TIOVX_PATH) doxy_docs

ptk:
ifeq ($(BUILD_PTK),yes)
ifeq ($(BUILD_EMULATION_MODE),yes)
	-$(MAKE) -C $(PTK_PATH) TARGET_SOC=$(TARGET_SOC) RTOS=$(RTOS) C7X_TARGET=$(C7X_TARGET) BUILD_TARGET_MODE=no
	-$(MAKE) -C $(PTK_PATH) TARGET_SOC=$(TARGET_SOC) RTOS=$(RTOS) C7X_TARGET=$(C7X_TARGET) cp_to_lib BUILD_TARGET_MODE=no
endif
ifeq ($(BUILD_TARGET_MODE),yes)
	-$(MAKE) -C $(PTK_PATH) TARGET_SOC=$(TARGET_SOC) RTOS=$(RTOS) C7X_TARGET=$(C7X_TARGET) BUILD_TARGET_MODE=yes
	-$(MAKE) -C $(PTK_PATH) TARGET_SOC=$(TARGET_SOC) RTOS=$(RTOS) C7X_TARGET=$(C7X_TARGET) cp_to_lib BUILD_TARGET_MODE=yes
endif
endif

ptk_clean:
ifeq ($(BUILD_PTK),yes)
	-$(MAKE) -C $(PTK_PATH) TARGET_SOC=$(TARGET_SOC) RTOS=$(RTOS) C7X_TARGET=$(C7X_TARGET) clean
endif

ptk_docs:
ifeq ($(BUILD_PTK),yes)
	$(MAKE) -C $(PTK_PATH) doxy_docs
endif

ptk_scrub:
ifeq ($(BUILD_PTK),yes)
ifeq ($(BUILD_EMULATION_MODE),yes)
	$(MAKE) -C $(PTK_PATH) TARGET_SOC=$(TARGET_SOC) RTOS=$(RTOS) C7X_TARGET=$(C7X_TARGET) BUILD_TARGET_MODE=no scrub
endif
ifeq ($(BUILD_TARGET_MODE),yes)
	$(MAKE) -C $(PTK_PATH) TARGET_SOC=$(TARGET_SOC) RTOS=$(RTOS) C7X_TARGET=$(C7X_TARGET) BUILD_TARGET_MODE=yes scrub
endif
endif

imaging:
	$(MAKE) -C $(IMAGING_PATH)

imaging_clean:
	$(MAKE) -C $(IMAGING_PATH) clean

imaging_scrub:
	$(MAKE) -C $(IMAGING_PATH) scrub

remote_device:
ifeq ($(BUILD_TARGET_MODE),yes)
ifeq ($(TARGET_SOC),J7)
	$(MAKE) -C $(REMOTE_DEVICE_PATH) TARGET_SOC=J721E RTOS=$(RTOS) lib_remote_device
	$(MAKE) -C $(REMOTE_DEVICE_PATH) TARGET_SOC=J721E RTOS=$(RTOS) cp_to_lib
else
	$(MAKE) -C $(REMOTE_DEVICE_PATH) TARGET_SOC=$(TARGET_SOC) RTOS=$(RTOS) lib_remote_device
	$(MAKE) -C $(REMOTE_DEVICE_PATH) TARGET_SOC=$(TARGET_SOC) RTOS=$(RTOS) cp_to_lib
endif
endif

remote_device_clean:
	$(MAKE) -C $(REMOTE_DEVICE_PATH) TARGET_SOC=$(TARGET_SOC) RTOS=$(RTOS) clean

remote_device_scrub:
	$(MAKE) -C $(REMOTE_DEVICE_PATH) TARGET_SOC=$(TARGET_SOC) RTOS=$(RTOS) scrub

.PHONY: tiovx tiovx_clean ptk ptk_clean imaging imaging_clean remote_device remote_device_clean
