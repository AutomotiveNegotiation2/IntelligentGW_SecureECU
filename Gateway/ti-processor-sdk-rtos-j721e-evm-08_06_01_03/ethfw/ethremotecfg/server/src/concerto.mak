include $(PRELUDE)
TARGET      := lib_remoteswitchcfg_server
TARGETTYPE  := library
TARGET_OS_LC := $(call lowercase,$(TARGET_OS))

CSOURCES    := remote_device_server_ethswitch.c
CSOURCES    += cpsw_proxy_server.c

#include $(ETHFW_PATH)/apps/concerto_inc.mak
ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
  IDIRS       += $(PDK_PATH)/packages/ti/transport/lwip/lwip-stack/src/include
  IDIRS       += $(PDK_PATH)/packages/ti/transport/lwip/lwip-port/${TARGET_OS_LC}/include
endif
IDIRS       += $(PDK_PATH)/packages
IDIRS       += $(REMOTE_DEVICE_PATH)
IDIRS       += $(ETHFW_PATH)

ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
  DEFS += MAKEFILE_BUILD
endif

ifeq ($(ETHFW_PROXY_ARP_SUPPORT),yes)
  DEFS += ETHFW_PROXY_ARP_HANDLING
endif

include $(FINALE)
