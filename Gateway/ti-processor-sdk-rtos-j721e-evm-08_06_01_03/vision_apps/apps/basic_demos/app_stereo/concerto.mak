ifeq ($(TARGET_CPU),$(filter $(TARGET_CPU), x86_64 A72))

include $(PRELUDE)

TARGET      := vx_app_stereo_depth
CSOURCES    := main.c

ifeq ($(TARGET_CPU),x86_64)

TARGETTYPE  := exe
CSOURCES    += main_x86.c

include $(VISION_APPS_PATH)/apps/concerto_x86_64_inc.mak

SYSLDIRS += /usr/lib64

endif

ifeq ($(TARGET_CPU),A72)

TARGETTYPE  := exe
CSOURCES    += main_linux_arm.c

include $(VISION_APPS_PATH)/apps/concerto_a72_inc.mak

endif

IDIRS += $(VISION_APPS_KERNELS_IDIRS)
IDIRS += $(VISION_APPS_STEREO_KERNELS_IDIRS)
IDIRS += $(PTK_IDIRS)

STATIC_LIBS += $(VISION_APPS_KERNELS_LIBS)
STATIC_LIBS += $(PTK_LIBS)
STATIC_LIBS += $(VISION_APPS_STEREO_LIBS)

include $(FINALE)

endif
