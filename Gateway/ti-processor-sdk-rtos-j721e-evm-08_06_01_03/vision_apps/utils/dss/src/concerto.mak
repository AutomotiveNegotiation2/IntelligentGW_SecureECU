ifeq ($(TARGET_OS),$(filter $(TARGET_OS),SYSBIOS FREERTOS SAFERTOS))
ifeq ($(TARGET_CPU),R5F)

include $(PRELUDE)
TARGET      := app_utils_dss
TARGETTYPE  := library

CSOURCES    := app_dss.c app_dss_soc.c app_dctrl.c app_dss_defaults.c app_dss_dual_display_defaults.c

ifeq ($(BUILD_ENABLE_ETHFW),yes)
DEFS+=ENABLE_ETHFW
endif

DEFS+=$(BUILD_PDK_BOARD)

include $(FINALE)

endif
endif
