include remote_device_tools_path.mak

# Edit below file to change default build options
include remote_device_build_flags.mak


DIRECTORIES :=
DIRECTORIES += server-rtos client-rtos

TARGET_COMBOS :=

ifeq ($(PROFILE), $(filter $(PROFILE), debug all))
	ifeq ($(BUILD_ISA_R5F),yes)
	TARGET_COMBOS += $(TARGET_SOC):$(RTOS):R5F:3:debug:TIARMCGT_LLVM
	endif
endif

ifeq ($(PROFILE), $(filter $(PROFILE), release all))
	ifeq ($(BUILD_ISA_R5F),yes)
	TARGET_COMBOS += $(TARGET_SOC):$(RTOS):R5F:3:release:TIARMCGT_LLVM
	endif
endif

CONCERTO_ROOT ?= concerto
BUILD_MULTI_PROJECT := 1
BUILD_TARGET := target.mak
BUILD_PLATFORM :=

include $(CONCERTO_ROOT)/rules.mak

doxy_docs:
	-$(Q)$(MKDIR) docs/user_guide/ $(QUIET) || true
	$(DOXYGEN) internal_docs/doxy_cfg_user_guide/user_guide_linux.cfg 2> internal_docs/doxy_cfg_user_guide/doxy_warnings.txt

