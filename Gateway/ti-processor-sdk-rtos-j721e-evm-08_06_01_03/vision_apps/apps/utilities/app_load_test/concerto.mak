ifeq ($(TARGET_CPU),A72)
ifeq ($(TARGET_OS), $(filter $(TARGET_OS), QNX LINUX))

include $(PRELUDE)

TARGETTYPE  := exe
TARGET      := vx_app_load_test
CSOURCES    := $(call all-c-files)

include $(VISION_APPS_PATH)/apps/concerto_a72_inc.mak

include $(FINALE)

endif
endif

