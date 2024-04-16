ifeq ($(TARGET_PLATFORM), PC)

include $(PRELUDE)

CSOURCES    := tidl_rt_x86.c

LDIRS += $(DSP_TOOLS)/host_emulation
LDIRS += $(MMALIB_PATH)/lib/$(TARGET_C7X_VERSION)/$(TARGET_BUILD)
LDIRS += $(PDK_PATH)/ti/csl/lib/$(TARGET_SOC)/c7x-hostemu/$(TARGET_BUILD)
LDIRS += $(PDK_PATH)/ti/osal/lib/nonos/$(TARGET_SOC)/c7x-hostemu/$(TARGET_BUILD)
LDIRS += $(PDK_PATH)/ti/drv/sciclient/lib/$(TARGET_SOC)_hostemu/c7x-hostemu/$(TARGET_BUILD)
LDIRS += $(PDK_PATH)/ti/drv/udma/lib/$(TARGET_SOC)_hostemu/c7x-hostemu/$(TARGET_BUILD)
ifeq ($(TIDL_BUILD_PATHS), LEGACY)
LDIRS += $(TIDL_PATH)/lib/PC/dsp/algo/$(TARGET_BUILD)
else
LDIRS += $(TIDL_PATH)/lib/$(TARGET_SOC)/PC/algo/$(TARGET_BUILD)
endif
LDIRS += $(TIOVX_PATH)/lib/PC/$(TARGET_CPU)/$(TARGET_OS)/$(TARGET_BUILD)
LDIRS += $(VISION_APPS_PATH)/lib/PC/$(TARGET_OVX_PATH)/$(TARGET_CPU)/$(TARGET_OS)/$(TARGET_BUILD)

PDK_LIBS =
PDK_LIBS += dmautils.lib
PDK_LIBS += ti.csl.lib
ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), AM62A am62a))
DEFS += DMA_UTILS_STANDALONE
else
PDK_LIBS += udma.lib
PDK_LIBS += sciclient.lib
PDK_LIBS += ti.osal.lib
endif

MMA_LIBS =
MMA_LIBS += mmalib_cn_x86_64
MMA_LIBS += mmalib_x86_64
MMA_LIBS += common_x86_64

TIDL_LIBS =
TIDL_LIBS += tidl_algo
TIDL_LIBS += tidl_obj_algo
TIDL_LIBS += tidl_priv_algo
TIDL_LIBS += tidl_custom

TIDL_LIBS += tidl_avx_kernels

TIOVX_LIBS  =
TIOVX_LIBS += vx_framework
TIOVX_LIBS += vx_platform_pc
TIOVX_LIBS += vx_kernels_host_utils vx_kernels_target_utils
TIOVX_LIBS += vx_kernels_tidl
TIOVX_LIBS += vx_kernels_openvx_core vx_target_kernels_openvx_core
TIOVX_LIBS += vx_utils
TIOVX_LIBS += vx_target_kernels_tidl
TIOVX_LIBS += vx_target_kernels_ivision_common
TIOVX_LIBS += vx_target_kernels_dsp
TIOVX_LIBS += vx_target_kernels_source_sink
TIOVX_LIBS += vx_target_kernels_tutorial

VISION_APPS_UTILS_LIBS  =
VISION_APPS_UTILS_LIBS += app_utils_mem
VISION_APPS_UTILS_LIBS += app_utils_init

ADDITIONAL_STATIC_LIBS += $(PDK_LIBS)

STATIC_LIBS += $(TIDL_LIBS)
STATIC_LIBS += $(MMA_LIBS)
STATIC_LIBS += $(TIOVX_LIBS)
STATIC_LIBS += $(VISION_APPS_UTILS_LIBS)
STATIC_LIBS += vxlib_$(TARGET_CPU) c6xsim_$(TARGET_CPU)_C66
STATIC_LIBS += $(TARGET_C7X_VERSION)-host-emulation

SHARED_LIBS += rt

include $($(_MODULE)_SDIR)/../concerto_common.mak

include $(FINALE)

endif
