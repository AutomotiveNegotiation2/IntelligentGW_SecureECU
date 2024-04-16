ifeq ($(TARGET_CPU),$(filter $(TARGET_CPU), x86_64 A72))

include $(PRELUDE)

TARGET      := vx_app_tidl

CSOURCES    := imagenet_class_labels.c main.c

ifeq ($(TARGET_CPU),x86_64)

TARGETTYPE  := exe

CSOURCES    += main_x86.c

include $(VISION_APPS_PATH)/apps/concerto_x86_64_inc.mak

endif

ifeq ($(TARGET_CPU),A72)
ifeq ($(TARGET_OS),$(filter $(TARGET_OS), LINUX QNX))

TARGETTYPE  := exe

CSOURCES    += main_linux_arm.c

include $(VISION_APPS_PATH)/apps/concerto_a72_inc.mak

endif
endif

ifeq ($(TARGET_OS),SYSBIOS)
ifeq ($(TARGET_CPU),$(filter $(TARGET_CPU), A72))
TARGETTYPE  := library
endif
endif

include $(FINALE)

endif
