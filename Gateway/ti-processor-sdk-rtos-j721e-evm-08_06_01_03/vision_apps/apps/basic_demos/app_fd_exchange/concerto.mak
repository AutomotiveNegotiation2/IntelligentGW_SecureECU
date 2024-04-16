ifeq ($(TARGET_CPU),$(filter $(TARGET_CPU), x86_64 A72))
ifeq ($(TARGET_OS),$(filter $(TARGET_OS), LINUX QNX))

_MODULE=producer
# Producer executable
include $(PRELUDE)

TARGET      := vx_app_arm_fd_exchange_producer
TARGETTYPE  := exe
CSOURCES    := main_producer.c apputils_net.c app_common.c

ifeq ($(TARGET_OS),$(filter $(TARGET_OS), QNX))
SYS_SHARED_LIBS += socket
endif

ifeq ($(TARGET_CPU),A72)
include $(VISION_APPS_PATH)/apps/concerto_a72_inc.mak
endif

ifeq ($(TARGET_CPU), x86_64)
include $(VISION_APPS_PATH)/apps/concerto_x86_64_inc.mak
endif

include $(FINALE)

_MODULE=consumer
# Consumer executable
include $(PRELUDE)

TARGET      := vx_app_arm_fd_exchange_consumer
TARGETTYPE  := exe
CSOURCES    := main_consumer.c apputils_net.c app_common.c

ifeq ($(TARGET_OS),$(filter $(TARGET_OS), QNX))
SYS_SHARED_LIBS += socket
endif

ifeq ($(TARGET_CPU),A72)
include $(VISION_APPS_PATH)/apps/concerto_a72_inc.mak
endif

ifeq ($(TARGET_CPU), x86_64)
include $(VISION_APPS_PATH)/apps/concerto_x86_64_inc.mak
endif

include $(FINALE)

endif
endif
