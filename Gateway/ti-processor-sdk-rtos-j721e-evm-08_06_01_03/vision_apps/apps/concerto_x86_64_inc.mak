
ifeq ($(TARGET_CPU),x86_64)

TEST_IDIRS =
TEST_IDIRS += $(TIOVX_PATH)/conformance_tests

IMAGING_IDIRS  =
IMAGING_IDIRS += $(IMAGING_PATH)/kernels/include
IMAGING_IDIRS += $(IMAGING_PATH)/sensor_drv/include

VISION_APPS_KERNELS_IDIRS =
VISION_APPS_KERNELS_IDIRS += $(VISION_APPS_PATH)/kernels
VISION_APPS_KERNELS_IDIRS += $(VISION_APPS_PATH)/kernels/img_proc/include
VISION_APPS_KERNELS_IDIRS += $(VISION_APPS_PATH)/kernels/fileio/include

VISION_APPS_MODULES_IDIRS =
VISION_APPS_MODULES_IDIRS += $(VISION_APPS_PATH)/modules/include

VISION_APPS_SRV_IDIRS =
VISION_APPS_SRV_IDIRS += $(VISION_APPS_PATH)/kernels/srv/include
VISION_APPS_SRV_IDIRS += $(VISION_APPS_PATH)/kernels/srv/c66
VISION_APPS_SRV_IDIRS += $(VISION_APPS_PATH)/kernels/srv/gpu/3dsrv
VISION_APPS_SRV_IDIRS += $(VISION_APPS_PATH)/kernels/sample/include
VISION_APPS_SRV_IDIRS += $(VISION_APPS_PATH)/kernels/sample/host

VISION_APPS_APPLIBS_IDIRS =
VISION_APPS_APPLIBS_IDIRS += $(VISION_APPS_PATH)/applibs

PTK_IDIRS =
PTK_IDIRS += $(PTK_PATH)/include

VISION_APPS_STEREO_KERNELS_IDIRS =
VISION_APPS_STEREO_KERNELS_IDIRS += $(VISION_APPS_PATH)/kernels/stereo/include

LDIRS       += $(VISION_APPS_PATH)/out/PC/$(TARGET_CPU)/$(TARGET_OS)/$(TARGET_BUILD)
LDIRS       += $(TIOVX_PATH)/lib/PC/$(TARGET_CPU)/$(TARGET_OS)/$(TARGET_BUILD)
LDIRS       += $(IMAGING_PATH)/lib/PC/$(TARGET_CPU)/$(TARGET_OS)/$(TARGET_BUILD)
LDIRS       += $(TIADALG_PATH)/lib/$(TARGET_CPU)/$(TARGET_BUILD)
LDIRS       += $(CGT7X_ROOT)/host_emulation
LDIRS       += $(MMALIB_PATH)/lib/$(C7X_VERSION)/$(TARGET_BUILD)
LDIRS       += $(PTK_PATH)/lib/$(TARGET_PLATFORM)/$(TARGET_CPU)/$(TARGET_OS)/$(TARGET_BUILD)

CFLAGS += -Wno-unused-but-set-variable
CFLAGS += -Wno-unused-variable
CFLAGS += -Wno-unused-result
CFLAGS += -Wno-maybe-uninitialized

TIOVX_LIBS  =
TIOVX_LIBS += vx_vxu vx_framework
TIOVX_LIBS += vx_kernels_host_utils vx_kernels_target_utils
TIOVX_LIBS += vx_platform_pc
TIOVX_LIBS += vx_kernels_openvx_core vx_target_kernels_openvx_core
TIOVX_LIBS += vx_target_kernels_dsp
TIOVX_LIBS += vx_target_kernels_tutorial
TIOVX_LIBS += vx_app_c7x_target_kernel
TIOVX_LIBS += vx_utils
TIOVX_LIBS += vx_hwa_target_kernels

IMAGING_LIBS = vx_kernels_imaging
IMAGING_LIBS += app_utils_iss
IMAGING_LIBS += ti_imaging_aealg
IMAGING_LIBS += ti_imaging_awbalg
IMAGING_LIBS += ti_imaging_dcc
IMAGING_LIBS += vx_target_kernels_imaging_aewb

TIADALG_LIBS  =
TIADALG_LIBS += tiadalg_fisheye_transformation
TIADALG_LIBS += tiadalg_image_preprocessing
TIADALG_LIBS += tiadalg_dof_plane_seperation
TIADALG_LIBS += tiadalg_visual_localization
TIADALG_LIBS += tiadalg_select_top_feature
TIADALG_LIBS += tiadalg_solve_pnp
TIADALG_LIBS += tiadalg_sparse_upsampling
TIADALG_LIBS += tiadalg_image_color_blending
TIADALG_LIBS += tiadalg_image_recursive_nms
TIADALG_LIBS += tiadalg_structure_from_motion
ifeq ($(SOC),j721e)
TIADALG_LIBS += c6xsim
endif

VISION_APPS_UTILS_LIBS  =
VISION_APPS_UTILS_LIBS += app_utils_draw2d
VISION_APPS_UTILS_LIBS += app_utils_mem
VISION_APPS_UTILS_LIBS += app_utils_perf_stats
VISION_APPS_UTILS_LIBS += app_utils_console_io
VISION_APPS_UTILS_LIBS += app_utils_grpx
VISION_APPS_UTILS_LIBS += app_utils_hwa
VISION_APPS_UTILS_LIBS += app_utils_init

VISION_APPS_SRV_LIBS  =
VISION_APPS_SRV_LIBS  += vx_kernels_sample vx_target_kernels_sample_a72
VISION_APPS_SRV_LIBS  += vx_kernels_srv vx_target_kernels_srv_gpu
VISION_APPS_SRV_LIBS  += vx_target_kernels_srv_c66
VISION_APPS_SRV_LIBS  += vx_applib_srv_bowl_lut_gen
VISION_APPS_SRV_LIBS  += vx_applib_srv_calibration
VISION_APPS_SRV_LIBS  += vx_srv_render_utils
VISION_APPS_SRV_LIBS  += vx_srv_render_utils_tools
VISION_APPS_SRV_LIBS  += app_utils_opengl

VISION_APPS_KERNELS_LIBS  =
VISION_APPS_KERNELS_LIBS += vx_kernels_img_proc
VISION_APPS_KERNELS_LIBS += vx_target_kernels_img_proc_c66
VISION_APPS_KERNELS_LIBS += vx_target_kernels_img_proc_c71
VISION_APPS_KERNELS_LIBS += vx_target_kernels_img_proc_a72
VISION_APPS_KERNELS_LIBS += vx_target_kernels_img_proc_r5f
VISION_APPS_KERNELS_LIBS += vx_kernels_fileio
VISION_APPS_KERNELS_LIBS += vx_target_kernels_fileio

VISION_APPS_MODULES_LIBS  =
VISION_APPS_MODULES_LIBS += vx_app_modules

PTK_LIBS =
PTK_LIBS += ptk_base
PTK_LIBS += ptk_algos

VISION_APPS_STEREO_LIBS =
VISION_APPS_STEREO_LIBS += vx_kernels_common
VISION_APPS_STEREO_LIBS += vx_kernels_stereo
VISION_APPS_STEREO_LIBS += vx_target_kernels_stereo

TEST_LIBS =
TEST_LIBS += vx_tiovx_tests vx_conformance_tests vx_conformance_engine vx_conformance_tests_testmodule
TEST_LIBS += vx_kernels_hwa_tests vx_tiovx_tidl_tests
TEST_LIBS += vx_kernels_test_kernels_tests vx_kernels_test_kernels
TEST_LIBS += vx_target_kernels_source_sink
TEST_LIBS += vx_kernels_srv_tests
TEST_LIBS += vx_applib_tests

PDK_LIBS =
PDK_LIBS += dmautils.lib
PDK_LIBS += udma.lib
PDK_LIBS += sciclient.lib
PDK_LIBS += ti.csl.lib
PDK_LIBS += ti.osal.lib

MMA_LIBS =
MMA_LIBS += mmalib_cn_x86_64
MMA_LIBS += mmalib_x86_64
MMA_LIBS += common_x86_64

ifneq ($(SOC),am62a)
ADDITIONAL_STATIC_LIBS += $(PDK_LIBS)
STATIC_LIBS += $(VISION_APPS_UTILS_LIBS)
endif

STATIC_LIBS += $(MMA_LIBS)
STATIC_LIBS += $(TIOVX_LIBS)
STATIC_LIBS += vxlib_$(TARGET_CPU) c6xsim_$(TARGET_CPU)_C66
STATIC_LIBS += C7100-host-emulation

include $(TIOVX_PATH)/conformance_tests/kernels/concerto_inc.mak
ifneq ($(TIOVX_CUSTOM_KERNEL_PATH),)
include $(TIOVX_CUSTOM_KERNEL_PATH)/custom_tools_path.mak
include $(TIOVX_CUSTOM_KERNEL_PATH)/concerto_inc.mak
endif

SYS_SHARED_LIBS += stdc++ m rt

endif
