
include vision_apps_tools_path.mak

# Edit below file to change default build options
include vision_apps_build_flags.mak

# Project specific build defs (don't change across different combos):
BUILD_DEFS :=
ifeq ($(BUILD_IVISION_KERNELS),yes)
BUILD_DEFS += BUILD_IVISION_KERNELS
endif
ifneq ($(CUSTOM_KERNEL_PATH),)
BUILD_DEFS += CUSTOM_KERNEL_PATH
endif
ifneq ($(APP_CONFIG_BASE_PATH),)
BUILD_DEFS += APP_CONFIG_BASE_PATH
endif
ifeq ($(BUILD_TUTORIAL),yes)
BUILD_DEFS += BUILD_TUTORIAL
endif
ifeq ($(BUILD_CONFORMANCE_TEST),yes)
BUILD_DEFS += BUILD_CONFORMANCE_TEST
endif

BUILD_DEFS += $(SOC_DEF)
BUILD_DEFS += $(VPAC_VERSION)

DIRECTORIES :=
ifeq ($(SOC),am62a)
DIRECTORIES += utils/app_init
DIRECTORIES += utils/console_io
DIRECTORIES += utils/hwa
DIRECTORIES += utils/ipc
DIRECTORIES += utils/iss
DIRECTORIES += utils/mem
DIRECTORIES += utils/misc
DIRECTORIES += utils/perf_stats
DIRECTORIES += utils/remote_service
DIRECTORIES += utils/sciclient
DIRECTORIES += utils/sciserver
DIRECTORIES += utils/udma

DIRECTORIES += platform/$(SOC)

DIRECTORIES += modules
DIRECTORIES += apps/basic_demos/app_c7x_kernel
DIRECTORIES += apps/basic_demos/app_fd_exchange
DIRECTORIES += apps/tests/app_vx_conformance
DIRECTORIES += apps/utilities

DIRECTORIES += kernels/fileio
DIRECTORIES += kernels/img_proc

else
DIRECTORIES += utils
DIRECTORIES += kernels
DIRECTORIES += modules
DIRECTORIES += applibs
DIRECTORIES += platform/$(SOC)

ifeq ($(BUILD_EDGEAI),no)
	DIRECTORIES += apps
else
	DIRECTORIES += apps/basic_demos/app_c7x_kernel
	DIRECTORIES += apps/utilities
	DIRECTORIES += apps/tests
endif
endif

TARGET_COMBOS :=

ifeq ($(BUILD_TARGET_MODE),yes)
  ifeq ($(PROFILE), $(filter $(PROFILE), debug all))
	ifeq ($(BUILD_ISA_R5F),yes)
	TARGET_COMBOS += $(TARGET_SOC):$(RTOS):R5F:3:debug:TIARMCGT_LLVM
	endif
	ifeq ($(BUILD_ISA_C6x),yes)
	TARGET_COMBOS += $(TARGET_SOC):$(RTOS):C66:2:debug:CGT6X
	endif
	ifeq ($(BUILD_ISA_C7x),yes)
	TARGET_COMBOS += $(TARGET_SOC):$(RTOS):$(C7X_TARGET):1:debug:CGT7X
	endif
	ifeq ($(BUILD_ISA_A72),yes)
		ifeq ($(BUILD_LINUX_A72),yes)
		TARGET_COMBOS += $(TARGET_SOC):LINUX:A72:1:debug:GCC_LINUX_ARM
		endif
		ifeq ($(BUILD_QNX_A72),yes)
		TARGET_COMBOS += $(TARGET_SOC):QNX:A72:1:debug:GCC_QNX_ARM
		endif
	endif
  endif

  ifeq ($(PROFILE), $(filter $(PROFILE), release all))
	ifeq ($(BUILD_ISA_R5F),yes)
	TARGET_COMBOS += $(TARGET_SOC):$(RTOS):R5F:3:release:TIARMCGT_LLVM
	endif
	ifeq ($(BUILD_ISA_C6x),yes)
	TARGET_COMBOS += $(TARGET_SOC):$(RTOS):C66:2:release:CGT6X
	endif
	ifeq ($(BUILD_ISA_C7x),yes)
	TARGET_COMBOS += $(TARGET_SOC):$(RTOS):$(C7X_TARGET):1:release:CGT7X
	endif
	ifeq ($(BUILD_ISA_A72),yes)
		ifeq ($(BUILD_LINUX_A72),yes)
		TARGET_COMBOS += $(TARGET_SOC):LINUX:A72:1:release:GCC_LINUX_ARM
		endif
		ifeq ($(BUILD_QNX_A72),yes)
		TARGET_COMBOS += $(TARGET_SOC):QNX:A72:1:release:GCC_QNX_ARM
		endif
	endif
  endif

endif

ifeq ($(BUILD_EMULATION_MODE),yes)
  ifeq ($(OS),Windows_NT)
    ifeq ($(PROFILE), $(filter $(PROFILE), debug all))
        ifeq ($(BUILD_EMULATION_ARCH), $(filter $(BUILD_EMULATION_ARCH), x86_64 all))
            TARGET_COMBOS += PC:WINDOWS:x86_64:1:debug:GCC_WINDOWS
        endif
        ifeq ($(BUILD_EMULATION_ARCH), $(filter $(BUILD_EMULATION_ARCH), X86 all))
            TARGET_COMBOS += PC:WINDOWS:X86:1:debug:GCC_WINDOWS
        endif
    endif

    ifeq ($(PROFILE), $(filter $(PROFILE), release all))
        ifeq ($(BUILD_EMULATION_ARCH), $(filter $(BUILD_EMULATION_ARCH), x86_64 all))
            TARGET_COMBOS += PC:WINDOWS:x86_64:1:release:GCC_WINDOWS
        endif
        ifeq ($(BUILD_EMULATION_ARCH), $(filter $(BUILD_EMULATION_ARCH), X86 all))
            TARGET_COMBOS += PC:WINDOWS:X86:1:release:GCC_WINDOWS
        endif
    endif
  else
    ifeq ($(PROFILE), $(filter $(PROFILE), debug all))
        ifeq ($(BUILD_EMULATION_ARCH), $(filter $(BUILD_EMULATION_ARCH), x86_64 all))
            TARGET_COMBOS += PC:LINUX:x86_64:1:debug:GCC_LINUX
        endif
        ifeq ($(BUILD_EMULATION_ARCH), $(filter $(BUILD_EMULATION_ARCH), X86 all))
            TARGET_COMBOS += PC:LINUX:X86:1:debug:GCC_LINUX
        endif
    endif

    ifeq ($(PROFILE), $(filter $(PROFILE), release all))
        ifeq ($(BUILD_EMULATION_ARCH), $(filter $(BUILD_EMULATION_ARCH), x86_64 all))
            TARGET_COMBOS += PC:LINUX:x86_64:1:release:GCC_LINUX
        endif
        ifeq ($(BUILD_EMULATION_ARCH), $(filter $(BUILD_EMULATION_ARCH), X86 all))
            TARGET_COMBOS += PC:LINUX:X86:1:release:GCC_LINUX
        endif
    endif
  endif
endif

CONCERTO_ROOT ?= concerto
BUILD_MULTI_PROJECT := 1
BUILD_TARGET := target.mak
BUILD_PLATFORM :=

include $(CONCERTO_ROOT)/rules.mak

# Project specific rules

.PHONY: all vision_apps sdk
all:

doxy_docs:
	-$(Q)$(MKDIR) docs/user_guide/ $(QUIET) || true
	-$(Q)$(COPY) tools/3d_calibration_tool/PSDK_RTOS_UserGuide_3D_SurroundView_Manual_CalibTool.pdf docs/user_guide/
	-$(Q)$(COPY) tools/3d_calibration_tool/poster_calib_chart.pdf docs/user_guide/
	$(DOXYGEN) internal_docs/doxy_cfg_user_guide/user_guide_linux_$(SOC).cfg 2> internal_docs/doxy_cfg_user_guide/doxy_warnings.txt
	-$(Q)$(COPY) internal_docs/doxy_cfg_user_guide/theme/*.png docs/user_guide/
	$(COPY) vision_apps_release_notes_$(SOC).html vision_apps_release_notes.html

doxy_design_docs:
	$(DOXYGEN) internal_docs/doxy_cfg_design/design_guide.cfg 2> internal_docs/doxy_cfg_design/doxy_warnings.txt

doxy_datasheet_docs:
	-$(Q)$(MKDIR) docs/datasheet/ $(QUIET) || true
	$(DOXYGEN) internal_docs/doxy_cfg_datasheet/datasheet_$(SOC).cfg 2> internal_docs/doxy_cfg_datasheet/doxy_warnings.txt

# Additional make targets to build various related components
include makerules/makefile_pdk.mak
include makerules/makefile_tidl_mmalib.mak
include makerules/makefile_tiovx_ptk_imaging_remote_device.mak
include makerules/makefile_test_data.mak
include makerules/makefile_linux_arm.mak
include makerules/makefile_help.mak
include makerules/makefile_config.mak
include makerules/makefile_tiadalg.mak
include makerules/makefile_check_paths.mak
include makerules/makefile_qnx.mak
include makerules/makefile_sbl.mak
include makerules/makefile_ethfw.mak
include makerules/makefile_ipk.mak
include makerules/makefile_uboot.mak
include makerules/makefile_sbl_combined_appimage.mak
include makerules/makefile_edgeai.mak

vision_apps: sdk_check_paths
	$(MAKE) all
vision_apps_clean: sdk_check_paths pdk_emu_clean clean
vision_apps_scrub: sdk_check_paths
	rm -rf out/

vision_apps_docs: sdk_check_paths doxy_docs

# Set Variables for SOC specific rule dependencies used in make rules below
ifeq ($(SOC), $(filter $(SOC), j721e j784s4))
SOC_VARIABLE_RULES=ethfw remote_device tiadalg qnx
SOC_VARIABLE_CLEAN=ethfw_clean remote_device_clean tiadalg_clean qnx_clean
SOC_VARIABLE_SCRUB=ethfw_scrub remote_device_scrub tiadalg_scrub qnx_scrub
SOC_VARIABLE_DOCS=tiadalg_docs
else ifeq ($(SOC),j721s2)
SOC_VARIABLE_RULES=tiadalg qnx
SOC_VARIABLE_CLEAN=tiadalg_clean qnx_clean
SOC_VARIABLE_SCRUB=tiadalg_scrub qnx_scrub
SOC_VARIABLE_DOCS=tiadalg_docs
else ifeq ($(SOC),am62a)
SOC_VARIABLE_RULES=
SOC_VARIABLE_CLEAN=
SOC_VARIABLE_SCRUB=
SOC_VARIABLE_DOCS=
endif

ifeq ($(BUILD_PTK),yes)
SOC_VARIABLE_RULES += ptk
SOC_VARIABLE_CLEAN += ptk_clean
SOC_VARIABLE_SCRUB += ptk_scrub
SOC_VARIABLE_DOCS  += ptk_docs
endif

sdk: sdk_check_paths pdk imaging vxlib tiovx $(SOC_VARIABLE_RULES)
	$(MAKE) vision_apps
ifeq ($(BUILD_CPU_MCU1_0),yes)
	$(MAKE) uboot
endif

sdk_clean: sdk_check_paths pdk_clean imaging_clean vxlib_clean tiovx_clean vision_apps_clean sbl_bootimage_clean $(SOC_VARIABLE_CLEAN)
ifeq ($(BUILD_CPU_MCU1_0),yes)
	$(MAKE) uboot_clean
endif

sdk_scrub: sdk_check_paths pdk_scrub imaging_scrub vxlib_scrub tiovx_scrub vision_apps_scrub sbl_bootimage_scrub $(SOC_VARIABLE_SCRUB)
ifeq ($(BUILD_CPU_MCU1_0),yes)
	$(MAKE) uboot_clean
endif

sdk_docs: sdk_check_paths tiovx_docs vision_apps_docs $(SOC_VARIABLE_DOCS)
	$(MAKE) -C $(PSDK_PATH)/psdk_rtos sphinx_docs

#KW build: Split the build into two - components which need not be part of
# SDK KW report as the report for these components are separately delivered
# Build it first and the use "kw_build" target for KW inject
kw_pre_build: pdk

kw_build: sdk
