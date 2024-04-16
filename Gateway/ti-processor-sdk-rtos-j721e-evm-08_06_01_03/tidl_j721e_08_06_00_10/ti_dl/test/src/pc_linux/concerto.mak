ifeq ($(TARGET_PLATFORM), PC)
ifeq ($(TARGET_OS), LINUX)

include $(PRELUDE)

TARGET      := PC_dsp_test_dl_algo.out
TARGETTYPE  := exe
CSOURCES    := $(call all-c-files)

#STATIC BUILD C SOURCES
ifeq ($(BUILD_WITH_STATIC_ARRAYS), 1)
CSOURCES    += ../../../../ti_dl/test/tidl_tb_net.c
CSOURCES    += ../../../../ti_dl/test/tidl_tb_pIn_tensor.c
CSOURCES    += ../../../../ti_dl/test/tidl_tb_pOutx_tensor.c
CSOURCES    += ../../../../ti_dl/test/tidl_tb_gIOParams.c
CSOURCES    += ../../../../ti_dl/test/tidl_tb_tidl_net_config.c
DEFS += BUILD_WITH_STATIC_ARRAYS
endif

# host emulation needs HE includes
IDIRS += $(CGT7X_ROOT)/host_emulation/include/$(TARGET_C7X_VERSION)
ifeq ($(BUILD_LIDAR_PREPROC), 1)
IDIRS += $(PSDK_INSTALL_PATH)/tiadalg/include
endif

# library search dirs are always platform specific
LDIRS += $(CGT7X_ROOT)/host_emulation
LDIRS += $(PDK_PATH)/ti/csl/lib/$(TARGET_SOC)/c7x-hostemu/$(TARGET_BUILD)

ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), am62a AM62A))
else
	LDIRS += $(PDK_PATH)/ti/osal/lib/nonos/$(TARGET_SOC)/c7x-hostemu/$(TARGET_BUILD)
	LDIRS += $(PDK_PATH)/ti/drv/sciclient/lib/$(TARGET_SOC)_hostemu/c7x-hostemu/$(TARGET_BUILD)
endif
LDIRS += $(PDK_PATH)/ti/drv/udma/lib/$(TARGET_SOC)_hostemu/c7x-hostemu/$(TARGET_BUILD)
LDIRS += $(MMALIB_PATH)/lib/$(TARGET_C7X_VERSION)/$(TARGET_BUILD)
ifeq ($(BUILD_LIDAR_PREPROC), 1)
LDIRS += $(PSDK_INSTALL_PATH)/tiadalg/lib/x86_64/$(TARGET_BUILD)
endif
# path to tidl_algo and tidl_priv_algo 
ifeq ($(TIDL_BUILD_PATHS), LEGACY)
LDIRS += $($(_MODULE)_SDIR)/../../../lib/PC/dsp/algo/$(TARGET_BUILD)
else
LDIRS += $($(_MODULE)_SDIR)/../../../lib/$(TARGET_SOC)/PC/algo/$(TARGET_BUILD)
endif

# AVV build needs runtime support library, not libc
#ifeq ($(TARGET_C7X_VERSION), C7100)
#ADDITIONAL_STATIC_LIBS += rts7100_le.lib
#else
#ADDITIONAL_STATIC_LIBS += rts7120_le.lib
#endif

# External libraries: The order in which they are defined ins important


ADDITIONAL_STATIC_LIBS += dmautils.lib

ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), am62a AM62A))
DEFS += DMA_UTILS_STANDALONE
else
ADDITIONAL_STATIC_LIBS += udma.lib
ADDITIONAL_STATIC_LIBS += sciclient.lib
ADDITIONAL_STATIC_LIBS += ti.osal.lib
endif
ADDITIONAL_STATIC_LIBS += ti.csl.lib
# Custom Library
STATIC_LIBS += tidl_custom

# internal libraries
STATIC_LIBS += tidl_algo
STATIC_LIBS += tidl_obj_algo
STATIC_LIBS += tidl_priv_algo


# External libraries: The order in which they are defined ins important
# Also, must be defined after the internal libraries
STATIC_LIBS += mmalib_cn_x86_64
STATIC_LIBS += mmalib_x86_64
STATIC_LIBS += common_x86_64
STATIC_LIBS += $(TARGET_C7X_VERSION)-host-emulation
ifeq ($(BUILD_LIDAR_PREPROC), 1)
STATIC_LIBS += tiadalg_voxelization
DEFS += BUILD_LIDAR_PREPROC
endif
# CUDA
# TODO may have LDIRS, IDIRS, {STATIC, SHARED}_LIBS
ifeq ($(BUILD_WITH_CUDA), 1)
DEFS += BUILD_WITH_CUDA
endif

# OPENCV
ifeq ($(BUILD_WITH_OPENCV), 1)
DEFS += BUILD_WITH_OPENCV

# search path for opencv includes
IDIRS += $(TIDL_OPENCV_PATH)/modules/core/include
IDIRS += $(TIDL_OPENCV_PATH)/modules/highgui/include
IDIRS += $(TIDL_OPENCV_PATH)/modules/imgcodecs/include
IDIRS += $(TIDL_OPENCV_PATH)/modules/videoio/include
IDIRS += $(TIDL_OPENCV_PATH)/modules/imgproc/include
IDIRS += $(TIDL_OPENCV_PATH)/cmake

# search path for opencv library
LDIRS += $(TIDL_OPENCV_PATH)/cmake/lib
LDIRS += $(TIDL_OPENCV_PATH)/cmake/3rdparty/lib

# opencv libraries
STATIC_LIBS += opencv_imgproc
STATIC_LIBS += opencv_imgcodecs
STATIC_LIBS += opencv_core
STATIC_LIBS += libtiff
STATIC_LIBS += libwebp
STATIC_LIBS += libpng
STATIC_LIBS += libjpeg-turbo
STATIC_LIBS += IlmImf
STATIC_LIBS += zlib
STATIC_LIBS += libjasper

# opencv needs libdl.so
SHARED_LIBS += dl
endif

# AVX
# TODO may have LDIRS, IDIRS, {STATIC, SHARED}_LIBS
STATIC_LIBS += tidl_avx_kernels

# defines for host emulation
DEFS += HOST_EMULATION
DEFS += _HOST_BUILD

ifeq ($(TARGET_C7X_VERSION), C7100)
else
DEFS += _TEMP_REF_MODELS
endif

ifeq ($(DMA_UTILS_STANDALONE), 1)
DEFS += DMA_UTILS_STANDALONE
endif


# get the common make flags from test/src/<plat>/../concerto_common.mak
include $($(_MODULE)_SDIR)/../concerto_common.mak
# This compiler keeps screaming about warnings
CFLAGS += -std=c++11

# override CC so that build uses g++-5
override CC := g++-5

include $(FINALE)

endif
endif
