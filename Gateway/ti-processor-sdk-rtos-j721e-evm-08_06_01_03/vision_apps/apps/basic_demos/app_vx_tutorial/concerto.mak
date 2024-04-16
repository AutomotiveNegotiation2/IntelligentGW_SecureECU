ifeq ($(TARGET_CPU),A72)
ifeq ($(TARGET_OS), $(filter $(TARGET_OS), LINUX QNX))

include $(PRELUDE)

TARGETTYPE  := exe
TARGET      := vx_app_tutorial
CSOURCES    := $(call all-c-files)

include $(VISION_APPS_PATH)/apps/concerto_a72_inc.mak

STATIC_LIBS += $(TEST_LIBS)

include $(FINALE)

endif
endif
