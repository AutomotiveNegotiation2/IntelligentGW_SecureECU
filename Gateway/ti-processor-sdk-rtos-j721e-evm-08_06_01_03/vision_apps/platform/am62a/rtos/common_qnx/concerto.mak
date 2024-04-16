ifeq ($(TARGET_PLATFORM),J7)
ifeq ($(TARGET_OS), $(filter $(TARGET_OS), SYSBIOS FREERTOS))


include $(PRELUDE)
TARGET      := app_rtos_qnx
TARGETTYPE  := library

CSOURCES    := app_common.c

IDIRS+=$(VISION_APPS_PATH)/platform/$(SOC)/rtos/common

include $(FINALE)

endif
endif
