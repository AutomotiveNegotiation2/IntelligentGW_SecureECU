ifeq ($(TARGET_CPU),C7504)

IDIRS+=$(VISION_APPS_PATH)/platform/$(SOC)/rtos/common
IDIRS+=$(VISION_APPS_PATH)/kernels/img_proc/include
IDIRS+=$(VISION_APPS_PATH)/kernels/fileio/include
IDIRS+=$(VISION_APPS_PATH)/kernels/srv/include
IDIRS+=$(VISION_APPS_PATH)/kernels/park_assist/include
IDIRS+=$(VISION_APPS_PATH)/kernels/stereo/include
IDIRS+=$(IMAGING_PATH)/kernels/include

ifeq ($(RTOS),SYSBIOS)
	LDIRS += $(PDK_PATH)/packages/ti/osal/lib/tirtos/$(SOC)/c7x/$(TARGET_BUILD)/
endif
ifeq ($(RTOS),FREERTOS)
	LDIRS += $(PDK_PATH)/packages/ti/osal/lib/freertos/$(SOC)/c75x/$(TARGET_BUILD)/
endif
LDIRS += $(PDK_PATH)/packages/ti/csl/lib/$(SOC)/c75x/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/uart/lib/$(SOC)/c75x/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/ipc/lib/$(SOC)/c7x_1/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/mailbox/lib/$(SOC)/c7x_1/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/udma/lib/$(SOC)/c7x_1/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/sciclient/lib/$(SOC)/c7x_1/$(TARGET_BUILD)/
LDIRS += $(VXLIB_PATH)/lib/$(TARGET_PLATFORM)/C7504/NO_OS/$(TARGET_BUILD)
LDIRS += $(TIOVX_PATH)/lib/$(TARGET_PLATFORM)/$(TARGET_CPU)/$(TARGET_OS)/$(TARGET_BUILD)
LDIRS += $(VISION_APPS_PATH)/lib/$(TARGET_PLATFORM)/$(TARGET_CPU)/$(TARGET_OS)/$(TARGET_BUILD)
LDIRS += $(MMALIB_PATH)/lib/$(C7X_VERSION)/$(TARGET_BUILD)
LDIRS += $(TIDL_PATH)/lib/$(SOC)/dsp/algo/$(TARGET_BUILD)

STATIC_LIBS += app_utils_mem
STATIC_LIBS += app_utils_console_io
STATIC_LIBS += app_utils_ipc
STATIC_LIBS += vx_app_c7x_target_kernel
STATIC_LIBS += app_utils_remote_service
STATIC_LIBS += app_utils_udma
STATIC_LIBS += app_utils_sciclient
STATIC_LIBS += app_utils_misc
STATIC_LIBS += app_utils_perf_stats
#STATIC_LIBS += vx_target_kernels_img_proc_c71

TIOVX_LIBS =
TIOVX_LIBS += vx_target_kernels_tidl
TIOVX_LIBS += vx_target_kernels_tvm
TIOVX_LIBS += vx_target_kernels_tvm_dynload
TIOVX_LIBS += vx_target_kernels_ivision_common
TIOVX_LIBS += vx_framework vx_platform_psdk_j7_rtos vx_kernels_target_utils
TIOVX_LIBS += vx_target_kernels_tutorial
TIOVX_LIBS += vx_target_kernels_openvx_core
TIOVX_LIBS += vx_target_kernels_dsp

TIDL_LIBS =
TIDL_LIBS += common_C7504
TIDL_LIBS += mmalib_C7504
TIDL_LIBS += mmalib_cn_C7504
TIDL_LIBS += tidl_algo
TIDL_LIBS += tidl_priv_algo
TIDL_LIBS += tidl_obj_algo
TIDL_LIBS += tidl_custom

SYS_STATIC_LIBS += $(TIOVX_LIBS) $(TIDL_LIBS)

ADDITIONAL_STATIC_LIBS += ti.osal.ae71
ADDITIONAL_STATIC_LIBS += ipc.ae71
ADDITIONAL_STATIC_LIBS += mailbox.ae71
ADDITIONAL_STATIC_LIBS += dmautils.ae71
ADDITIONAL_STATIC_LIBS += sciclient.ae71
ADDITIONAL_STATIC_LIBS += ti.drv.uart.ae71

ADDITIONAL_STATIC_LIBS += vxlib_C7504.lib

ifeq ($(RTOS),FREERTOS)
	ADDITIONAL_STATIC_LIBS += ti.kernel.freertos.ae71
endif
ADDITIONAL_STATIC_LIBS += ti.csl.ae71

ADDITIONAL_STATIC_LIBS += libc.a

endif
