TIDL_TB_FILES :=
COMMON_FILE   :=

# This is relative to the plat directory
# This section lists ti_dl/test/src/*.c files
# needed by all platforms
TIDL_TB_FILES += tidl_tb.c
TIDL_TB_FILES += tidl_rt.c
TIDL_TB_FILES += tidl_tb_utils.c
TIDL_TB_FILES += tidl_config.c
TIDL_TB_FILES += tidl_image_postproc.c
TIDL_TB_FILES += tidl_image_preproc.c
TIDL_TB_FILES += tidl_image_read_write.c
TIDL_TB_FILES += tidl_lidar_preproc.c

# This is relative to the plat directory
# This section lists common/*.c files
# needed by all platforms
COMMON_FILES += ti_draw_utils.c
COMMON_FILES += ti_mem_manager.c
COMMON_FILES += configparser.c

CSOURCES += $(foreach file, $(TIDL_TB_FILES), ../$(file))
CSOURCES += $(foreach file, $(COMMON_FILES), ../../../../common/$(file))

# include search directories needed by all platforms
IDIRS += $(PDK_PATH)
IDIRS += $(PDK_PATH)/ti/drv/udma/dmautils
IDIRS += $(PDK_PATH)/ti/csl
IDIRS += $(IVISION_PATH)
IDIRS += $($(_MODULE)_SDIR)/../../../inc
IDIRS += $($(_MODULE)_SDIR)/../../src
IDIRS += $($(_MODULE)_SDIR)/../../../../common
IDIRS += $($(_MODULE)_SDIR)/../../../custom
IDIRS += $($(_MODULE)_SDIR)/../../../utils/perfsim
IDIRS += $($(_MODULE)_SDIR)/../../../../arm-tidl/rt/inc

# defs needed by all platforms
ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J721E j721e))
    CFLAGS += -DSOC_J721E
endif
ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J721S2 j721s2))
    CFLAGS += -DSOC_J721S2
endif
ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J784S4 j784s4))
    CFLAGS += -DSOC_J784S4
endif
DEFS+=BUILD_C7X_$(C7X_CORE_ID)
ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), am62a AM62A))
    CFLAGS += -DSOC_AM62A
    DEFS+=DMA_UTILS_STANDALONE
endif

#ifeq ($(TIDL_BUILD_FOR_QT), 1)
DEFS+=TIDL_BUILD_FOR_QT
#endif

ifeq ($(TIDL_WRITE_PRINTS_TO_BUF), 1)
DEFS+=TIDL_WRITE_PRINTS_TO_BUF
endif

ifeq ($(TIDL_PRESILICON_SDK_UC_ENABLE), 1)
DEFS+=TIDL_PRESILICON_SDK_UC_ENABLE
endif
ifeq ($(TIDL_ENABLE_PER_FRAME_PERFORMANCE), 1)
DEFS+=TIDL_ENABLE_PER_FRAME_PERFORMANCE
endif
