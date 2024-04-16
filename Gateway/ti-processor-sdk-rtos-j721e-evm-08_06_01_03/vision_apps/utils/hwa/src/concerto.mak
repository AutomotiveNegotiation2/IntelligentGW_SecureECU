ifeq ($(TARGET_CPU),$(filter $(TARGET_CPU), x86_64))

include $(PRELUDE)

TARGET      := app_utils_hwa
TARGETTYPE  := library

CSOURCES += app_hwa_api_x86.c

include $(FINALE)

endif

ifneq ($(TARGET_PLATFORM),PC)

ifeq ($(TARGET_OS),$(filter $(TARGET_OS), LINUX QNX))

include $(PRELUDE)

TARGET      := app_utils_hwa
TARGETTYPE  := library

CSOURCES    := app_hwa_api.c

include $(FINALE)

endif

ifeq ($(TARGET_CPU),R5F)

include $(PRELUDE)

TARGET      := app_utils_hwa
TARGETTYPE  := library

CSOURCES    := app_hwa.c

include $(FINALE)

endif

endif
