include $(PRELUDE)

TARGET      := ethfw_lwip
TARGETTYPE  := library
TARGET_OS_LC := $(call lowercase,$(TARGET_OS))

ifneq (,$(filter $(TARGET_PLATFORM),J721E J7200 J784S4 AM65XX))
ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
  CSOURCES := src/ethfw_lwip_utils.c

  IDIRS := ${ETHFW_PATH}
  IDIRS += $(PDK_PATH)/packages/ti/transport/lwip/lwip-stack/src/include
  IDIRS += $(PDK_PATH)/packages/ti/transport/lwip/lwip-port/$(TARGET_OS_LC)/include
  IDIRS += $(PDK_PATH)/packages

  DEFS += MAKEFILE_BUILD
endif
endif

include $(FINALE)
