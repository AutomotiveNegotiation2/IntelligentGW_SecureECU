include $(PRELUDE)

TARGET      := ethfw_callbacks
TARGETTYPE  := library
TARGET_OS_LC := $(call lowercase,$(TARGET_OS))

ifneq (,$(filter $(TARGET_PLATFORM),J721E J7200 J784S4 AM65XX))
ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
  CSOURCES := src/ethfw_callbacks_lwipif.c
endif

IDIRS := ${ETHFW_PATH}
ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
  IDIRS += $(PDK_PATH)/packages/ti/transport/lwip/lwip-stack/src/include
  IDIRS += $(PDK_PATH)/packages/ti/transport/lwip/lwip-port/$(TARGET_OS_LC)/include
endif
IDIRS += $(PDK_PATH)/packages

ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
  DEFS += MAKEFILE_BUILD
endif

ifeq ($(ETHFW_PROXY_ARP_SUPPORT),yes)
  DEFS += ETHFW_PROXY_ARP_HANDLING
endif

endif

include $(FINALE)
