include $(PRELUDE)
TARGET      := lib_remoteswitchcfg_client
TARGETTYPE  := library

CSOURCES    := remote_device_client_ethswitch.c
CSOURCES    += cpsw_proxy.c

ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
  DEFS += MAKEFILE_BUILD
endif

include $(ETHFW_PATH)/apps/concerto_inc.mak

include $(FINALE)
