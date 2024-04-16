#
# Utility makefile to build ethfw libraries
#
# Edit this file to suit your specific build needs
#

SOC_ETHFW := $(call uppercase,$(SOC))

ethfw: remote_device
ifeq ($(BUILD_TARGET_MODE),yes)
	$(MAKE) -C ${REMOTE_DEVICE_PATH} RTOS=$(RTOS) cp_to_lib SOC=$(SOC) PROFILE=$(PROFILE) -s
ifeq ($(RTOS),FREERTOS)
	$(MAKE) -C $(ETHFW_PATH) BUILD_APP_SAFERTOS=no BUILD_APP_FREERTOS=yes ethfw ethfw_board ethfw_callbacks ethfw_lwip eth_intervlan lib_remoteswitchcfg_server BUILD_CPU_MCU2_1=no BUILD_SOC_LIST=$(SOC_ETHFW) PROFILE=$(PROFILE) -s
endif
ifeq ($(RTOS),SAFERTOS)
	$(MAKE) -C $(ETHFW_PATH) BUILD_APP_SAFERTOS=yes BUILD_APP_FREERTOS=no ethfw ethfw_board ethfw_callbacks ethfw_lwip eth_intervlan lib_remoteswitchcfg_server BUILD_CPU_MCU2_1=no BUILD_SOC_LIST=$(SOC_ETHFW) PROFILE=$(PROFILE) -s
endif
endif

ethfw_clean:
ifeq ($(BUILD_TARGET_MODE),yes)
	$(MAKE) -C ${REMOTE_DEVICE_PATH} RTOS=$(RTOS) clean -s
ifeq ($(RTOS),FREERTOS)
	$(MAKE) -C $(ETHFW_PATH) BUILD_APP_SAFERTOS=no BUILD_APP_FREERTOS=yes clean -s
endif
ifeq ($(RTOS),SAFERTOS)
	$(MAKE) -C $(ETHFW_PATH) BUILD_APP_SAFERTOS=yes BUILD_APP_FREERTOS=no clean -s
endif
endif

ethfw_scrub:
ifeq ($(BUILD_TARGET_MODE),yes)
	rm -rf $(REMOTE_DEVICE_PATH)/out
	rm -rf $(ETHFW_PATH)/out $(ETHFW_PATH)/lib
endif

.PHONY: ethfw ethfw_clean ethfw_scrub
