PSDK_PATH     ?= $(abspath ..)
PTK_ROOT_DIR  ?= $(PSDK_PATH)/ti-perception-toolkit
TIOVX_PATH    ?= $(PSDK_PATH)/tiovx
LINUX_FS_PATH ?= $(PSDK_PATH)/targetfs/

# paths for components shared between tiovx and perception are specified in below
# file in tiovx, ex, bios, tidl, pdk, cgtools, ...
include $(TIOVX_PATH)/psdkra_tools_path.mak
include $(TIOVX_PATH)/build_flags.mak

DIRECTORIES :=
DIRECTORIES += src

TARGET_COMBOS :=

ifeq ($(BUILD_EMULATION_MODE),yes)
    ifeq ($(PROFILE), $(filter $(PROFILE), debug all))
        TARGET_COMBOS += PC:LINUX:x86_64:1:debug:GCC_LINUX
    endif

    ifeq ($(PROFILE), $(filter $(PROFILE), release all))
        TARGET_COMBOS += PC:LINUX:x86_64:1:release:GCC_LINUX
    endif
endif

ifeq ($(BUILD_TARGET_MODE),yes)
    ifeq ($(PROFILE), $(filter $(PROFILE), debug all))
        ifeq ($(TARGET_SOC),J7)
            TARGET_COMBOS += $(TARGET_SOC):$(RTOS):C66:1:debug:CGT6X
        endif
        TARGET_COMBOS += $(TARGET_SOC):$(RTOS):$(C7X_TARGET):1:debug:CGT7X
        ifeq ($(BUILD_LINUX_A72),yes)
            TARGET_COMBOS += $(TARGET_SOC):LINUX:A72:1:debug:GCC_LINUX_ARM
        endif
        ifeq ($(BUILD_QNX_A72),yes)
            TARGET_COMBOS += $(TARGET_SOC):QNX:A72:1:debug:GCC_QNX_ARM
        endif
    endif

    ifeq ($(PROFILE), $(filter $(PROFILE), release all))
        ifeq ($(TARGET_SOC),J7)
            TARGET_COMBOS += $(TARGET_SOC):$(RTOS):C66:1:release:CGT6X
        endif
        TARGET_COMBOS += $(TARGET_SOC):$(RTOS):$(C7X_TARGET):1:release:CGT7X
        ifeq ($(BUILD_LINUX_A72),yes)
            TARGET_COMBOS += $(TARGET_SOC):LINUX:A72:1:release:GCC_LINUX_ARM
        endif
        ifeq ($(BUILD_QNX_A72),yes)
            TARGET_COMBOS += $(TARGET_SOC):QNX:A72:1:release:GCC_QNX_ARM
        endif
    endif
endif

CONCERTO_ROOT ?= concerto
BUILD_MULTI_PROJECT := 1
BUILD_TARGET := target.mak
BUILD_PLATFORM :=

.PHONY: all
all:

doxy_docs:
	$(DOXYGEN) internal_docs/api_guide/ptk_api_guide.cfg 2> internal_docs/api_guide/doxy_warnings.txt

include $(CONCERTO_ROOT)/rules.mak

