ifeq ($(TARGET_CPU),A72)
ifeq ($(TARGET_OS), $(filter $(TARGET_OS), LINUX QNX))

include $(PRELUDE)

TARGET      := tivision_apps
TARGETTYPE  := dsmo
VERSION     := $(PSDK_VERSION)

include $(VISION_APPS_PATH)/apps/concerto_a72_inc.mak

STATIC_LIBS     += $(IMAGING_LIBS)
STATIC_LIBS     += $(PTK_LIBS)
STATIC_LIBS     += $(VISION_APPS_KERNELS_LIBS)
STATIC_LIBS     += $(VISION_APPS_MODULES_LIBS)
STATIC_LIBS     += $(TEST_LIBS)

ifneq ($(SOC), am62a)
STATIC_LIBS     += $(VISION_APPS_STEREO_LIBS)
STATIC_LIBS     += $(VISION_APPS_SRV_LIBS)

SHARED_LIBS += GLESv2 EGL

ifeq ($(TARGET_OS),LINUX)
SHARED_LIBS += rt gbm
endif
endif

ifeq ($(TARGET_OS),QNX)
SYS_SHARED_LIBS += screen
endif

include $(FINALE)

endif
endif
