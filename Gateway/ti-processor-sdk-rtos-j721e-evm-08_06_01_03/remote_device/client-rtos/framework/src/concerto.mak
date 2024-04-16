include $(PRELUDE)
TARGET      := lib_remote_device_client
TARGETTYPE  := library

IDIRS       :=
IDIRS       += $(REMOTE_DEVICE_PATH)

CSOURCES    := app_queue.c app_remote_device.c

DEFS        :=
ifeq ($(SOC),j721e)
DEFS        += SOC_J721E
endif
ifeq ($(SOC),j7200)
DEFS        += SOC_J7200
endif
ifeq ($(SOC),j721s2)
DEFS        += SOC_J721S2
endif
ifeq ($(SOC),j784s4)
DEFS        += SOC_J784S4
endif

include $(FINALE)
