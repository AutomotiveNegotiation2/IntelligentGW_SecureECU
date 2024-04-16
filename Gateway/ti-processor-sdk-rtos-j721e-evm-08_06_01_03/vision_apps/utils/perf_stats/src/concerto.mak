ifeq ($(TARGET_CPU),$(filter $(TARGET_CPU), x86_64))

include $(PRELUDE)

TARGET      := app_utils_perf_stats
TARGETTYPE  := library

CSOURCES += app_perf_stats_api_x86.c

include $(FINALE)

endif

ifeq ($(TARGET_PLATFORM),$(filter $(TARGET_PLATFORM), J7 J721S2 J784S4 AM62A))

include $(PRELUDE)
TARGET      := app_utils_perf_stats
TARGETTYPE  := library

ifeq ($(TARGET_OS),SYSBIOS)
CSOURCES    := app_perf_stats_tirtos.c
endif

ifeq ($(TARGET_OS),$(filter $(TARGET_OS), FREERTOS SAFERTOS))
CSOURCES    := app_perf_stats_freertos.c
endif

ifeq ($(TARGET_OS),$(filter $(TARGET_OS), LINUX QNX))
CSOURCES    := app_perf_stats_hlos.c
endif

CSOURCES += app_perf_stats_api.c

include $(FINALE)


endif

