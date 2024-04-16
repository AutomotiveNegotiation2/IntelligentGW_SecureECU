ifeq ($(TARGET_PLATFORM), PC)

include $(PRELUDE)
TARGET      := PC_dsp_test_dl_algo_host_rt.out
TARGETTYPE  := exe
CSOURCES    := $(call all-c-files)

# host emulation needs HE includes
ifeq ($(TARGET_C7X_VERSION),C7100)
INCLUDE_PATHS += -I $(DSP_TOOLS)/host_emulation/include/C7100/
else ifeq ($(TARGET_C7X_VERSION),C7120)
INCLUDE_PATHS+= -I $(DSP_TOOLS)/host_emulation/include/C7120/
else
INCLUDE_PATHS+= -I $(DSP_TOOLS)/host_emulation/include/C7504/
endif


# library search dirs are always platform specific
LDIRS += $(DSP_TOOLS)/host_emulation
LDIRS += $(PDK_PATH)/ti/csl/lib/$(TARGET_SOC)/c7x-hostemu/$(TARGET_BUILD)
LDIRS += $(PDK_PATH)/ti/drv/udma/lib/$(TARGET_SOC)_hostemu/c7x-hostemu/$(TARGET_BUILD)

ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), AM62A am62a))
DEFS += DMA_UTILS_STANDALONE
else
LDIRS += $(PDK_PATH)/ti/osal/lib/nonos/$(TARGET_SOC)/c7x-hostemu/$(TARGET_BUILD)
LDIRS += $(PDK_PATH)/ti/drv/sciclient/lib/$(TARGET_SOC)_hostemu/c7x-hostemu/$(TARGET_BUILD)

ADDITIONAL_STATIC_LIBS += ti.osal.lib
ADDITIONAL_STATIC_LIBS += udma.lib
ADDITIONAL_STATIC_LIBS += sciclient.lib

endif

LDIRS += $(MMALIB_PATH)/lib/$(TARGET_C7X_VERSION)/$(TARGET_BUILD)

# path to tidl_algo and tidl_priv_algo 
ifeq ($(TIDL_BUILD_PATHS), LEGACY)
LDIRS += $(TIDL_PATH)/lib/PC/dsp/algo/$(TARGET_BUILD)
else
LDIRS += $(TIDL_PATH)/lib/$(TARGET_SOC)/PC/algo/$(TARGET_BUILD)
endif

# External libraries: The order in which they are defined is important
ADDITIONAL_STATIC_LIBS += dmautils.lib
ADDITIONAL_STATIC_LIBS += ti.csl.lib

# internal libraries 
STATIC_LIBS += tidl_algo
STATIC_LIBS += tidl_obj_algo
STATIC_LIBS += tidl_priv_algo

# Custom Library
ifeq ($(TIDL_TEST_CUSTOM_LAYER), 1)
DEFS += TIDL_TEST_CUSTOM_LAYER
STATIC_LIBS += tidl_custom
endif

# External libraries: The order in which they are defined ins important
# Also, must be defined after the internal libraries
#STATIC_LIBS += mmalib_cn_x86_64
#STATIC_LIBS += mmalib_x86_64
#STATIC_LIBS += common_x86_64
STATIC_LIBS += $(TARGET_C7X_VERSION)-host-emulation


# defines for host emulation
DEFS += HOST_EMULATION
DEFS += _HOST_BUILD

# get the common make flags from test/src/<plat>/../concerto_common.mak
include $($(_MODULE)_SDIR)/../concerto_common.mak

# override CC so that build uses g++-5
# override CC := g++-5

CFLAGS += -Wno-unused-variable \
	      -Wno-maybe-uninitialized \
 	      -Wno-parentheses \
          -Wno-unused-result \
          -Wno-implicit-function-declaration \
          -Wno-int-to-pointer-cast \
          -Wno-int-conversion

include $(FINALE)

endif
