ifeq ($(TARGET_CPU),A72)

IDIRS+=$(VISION_APPS_PATH)/platform/$(SOC)/rtos/common
IDIRS+=$(VISION_APPS_PATH)/kernels/img_proc/include
IDIRS+=$(VISION_APPS_PATH)/kernels/fileio/include
IDIRS+=$(VISION_APPS_PATH)/kernels/srv/include
IDIRS+=$(VISION_APPS_PATH)/kernels/park_assist/include
IDIRS+=$(PTK_PATH)/include
IDIRS+=$(VISION_APPS_PATH)/kernels/stereo/include
IDIRS+=$(IMAGING_PATH)/kernels/include

LDIRS += $(PDK_PATH)/packages/ti/osal/lib/tirtos/$(SOC)/a72/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/csl/lib/$(SOC)/a72/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/board/lib/$(BUILD_PDK_BOARD)/a72/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/uart/lib/$(SOC)/a72/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/mmcsd/lib/$(SOC)/a72/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/emac/lib/$(SOC)/a72/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/fs/fatfs/lib/a72/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/transport/ndk/nimu/lib/$(SOC)/a72/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/i2c/lib/$(SOC)/a72/$(TARGET_BUILD)/
LDIRS += $(TIOVX_PATH)/lib/$(TARGET_PLATFORM)/$(TARGET_CPU)/$(TARGET_OS)/$(TARGET_BUILD)
LDIRS += $(IMAGING_PATH)/lib/$(TARGET_PLATFORM)/$(TARGET_CPU)/$(TARGET_OS)/$(TARGET_BUILD)

STATIC_LIBS += app_utils_mem
STATIC_LIBS += app_utils_console_io
STATIC_LIBS += app_utils_ipc
STATIC_LIBS += app_utils_remote_service
STATIC_LIBS += app_utils_udma
STATIC_LIBS += app_utils_sciclient
STATIC_LIBS += app_utils_misc
STATIC_LIBS += app_utils_perf_stats
STATIC_LIBS += app_utils_iss
STATIC_LIBS += app_utils_hwa

STATIC_LIBS += vx_app_c7x_kernel
STATIC_LIBS += app_utils_draw2d
STATIC_LIBS += vx_app_tidl
STATIC_LIBS += vx_kernels_img_proc
STATIC_LIBS += vx_kernels_fileio
STATIC_LIBS += vx_app_single_cam
IMAGING_LIBS += vx_kernels_imaging
IMAGING_LIBS += vx_target_kernels_imaging_aewb

# Test framework libs
STATIC_LIBS += vx_app_test_framework
STATIC_LIBS += vx_kernels_stereo
#STATIC_LIBS += vx_kernels_srv
STATIC_LIBS += vx_kernels_srv_tests
STATIC_LIBS += vx_applib_srv_calibration vx_applib_srv_bowl_lut_gen vx_applib_tests
STATIC_LIBS += vx_app_dense_optical_flow
STATIC_LIBS += vx_app_stereo_depth
STATIC_LIBS += vx_target_kernels_stereo

IMAGING_LIBS  = ti_imaging_awbalg
IMAGING_LIBS += ti_imaging_dcc
IMAGING_LIBS += vx_kernels_imaging
IMAGING_LIBS += vx_target_kernels_imaging_aewb
IMAGING_LIBS += ti_imaging_aealg

TIOVX_LIBS =
TIOVX_LIBS += vx_conformance_engine vx_conformance_tests vx_conformance_tests_testmodule
TIOVX_LIBS += vx_tiovx_tests vx_tutorial vx_utils
TIOVX_LIBS += vx_framework vx_vxu vx_platform_psdk_j7_rtos vx_kernels_target_utils
TIOVX_LIBS += vx_kernels_test_kernels_tests vx_kernels_test_kernels
TIOVX_LIBS += vx_target_kernels_source_sink
TIOVX_LIBS += vx_kernels_host_utils vx_kernels_openvx_core
TIOVX_LIBS += vx_kernels_hwa_tests vx_kernels_hwa
TIOVX_LIBS += vx_kernels_tidl
TIOVX_LIBS += vx_tiovx_tidl_tests

SYS_STATIC_LIBS += $(TIOVX_LIBS)
SYS_STATIC_LIBS += $(IMAGING_LIBS)
SYS_STATIC_LIBS += stdc++ gcc m c nosys

ADDITIONAL_STATIC_LIBS += ti.osal.aa72fg
ADDITIONAL_STATIC_LIBS += ti.csl.aa72fg
ADDITIONAL_STATIC_LIBS += ti.csl.init.aa72fg
ADDITIONAL_STATIC_LIBS += ti.board.aa72fg
ADDITIONAL_STATIC_LIBS += ti.drv.uart.aa72fg
ADDITIONAL_STATIC_LIBS += udma.aa72fg
ADDITIONAL_STATIC_LIBS += udma_apputils.aa72fg
ADDITIONAL_STATIC_LIBS += sciclient.aa72fg
ADDITIONAL_STATIC_LIBS += ipc.aa72fg
ADDITIONAL_STATIC_LIBS += ti.drv.mmcsd.aa72fg
ADDITIONAL_STATIC_LIBS += ti.fs.fatfs.aa72fg
ADDITIONAL_STATIC_LIBS += ti.fs.fatfs.aa72fg
ADDITIONAL_STATIC_LIBS += ti.drv.i2c.aa72fg

endif
