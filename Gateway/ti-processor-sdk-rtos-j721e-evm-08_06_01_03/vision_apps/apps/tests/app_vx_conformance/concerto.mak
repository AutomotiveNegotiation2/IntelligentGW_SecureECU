ifeq ($(TARGET_CPU),A72)
ifeq ($(TARGET_OS), $(filter $(TARGET_OS), LINUX QNX))

include $(PRELUDE)

TARGET      := vx_app_conformance
TARGETTYPE  := exe
CSOURCES    := $(call all-c-files)

include $(VISION_APPS_PATH)/apps/concerto_a72_inc.mak

STATIC_LIBS += $(IMAGING_LIBS)
STATIC_LIBS += $(TEST_LIBS)

include $(FINALE)

endif
endif

