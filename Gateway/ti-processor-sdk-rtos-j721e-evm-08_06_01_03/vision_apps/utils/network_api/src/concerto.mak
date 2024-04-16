ifneq ($(TARGET_PLATFORM),PC)

include $(PRELUDE)
TARGET      := app_utils_network_api
TARGETTYPE  := library

ifeq ($(TARGET_OS),LINUX)
CSOURCES    := network_api.c

endif

IDIRS += $(VISION_APPS_PATH)
IDIRS += $(VISION_APPS_PATH)/utils/itt_server/include
IDIRS += $(VISION_APPS_PATH)/utils/network_api/include
IDIRS += $(IMAGING_PATH)/sensor_drv/include

include $(FINALE)

endif
