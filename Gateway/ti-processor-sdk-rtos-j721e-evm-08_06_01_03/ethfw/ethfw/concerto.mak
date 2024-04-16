include $(PRELUDE)

ifeq ($(BUILD_CPU_MCU2_0),yes)
ifneq (,$(filter $(TARGET_CPU),R5F R5Ft))

TARGET     := ethfw
TARGETTYPE := library
TARGET_OS_LC := $(call lowercase,$(TARGET_OS))

CSOURCES := src/ethfw.c

IDIRS := ${ETHFW_PATH}
ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
  IDIRS += $(PDK_PATH)/packages/ti/transport/lwip/lwip-stack/src/include
  IDIRS += $(PDK_PATH)/packages/ti/transport/lwip/lwip-port/${TARGET_OS_LC}/include
endif
IDIRS += $(REMOTE_DEVICE_PATH)
IDIRS += $(NDK_PATH)/packages
IDIRS += $(PDK_PATH)/packages

ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
  DEFS += MAKEFILE_BUILD
endif

ifeq ($(ETHFW_PROXY_ARP_SUPPORT),yes)
  DEFS += ETHFW_PROXY_ARP_HANDLING
endif

RPMSG_KDRV_TP_ETHSWITCH_VERSION_LAST_COMMIT := ${shell cd ${ETHFW_PATH};git rev-parse --short=8 HEAD 2>/dev/null}
DEFS += RPMSG_KDRV_TP_ETHSWITCH_VERSION_LAST_COMMIT="\"${RPMSG_KDRV_TP_ETHSWITCH_VERSION_LAST_COMMIT}\""

endif
endif

include $(FINALE)
