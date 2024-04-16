ifeq ($(TARGET_CPU),A72)
ifeq ($(TARGET_OS), $(filter $(TARGET_OS), LINUX QNX))

include $(PRELUDE)

TARGETTYPE  := exe
TARGET      := vx_app_arm_remote_log
CSOURCES    := $(call all-c-files)

include $(VISION_APPS_PATH)/apps/concerto_a72_inc.mak

include $(FINALE)

endif
endif

