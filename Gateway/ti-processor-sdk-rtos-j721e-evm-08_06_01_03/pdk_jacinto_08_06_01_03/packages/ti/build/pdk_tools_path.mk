################################################################################
# Configure toolchain paths
################################################################################
  # This section applies to all broader set of boards with SOCs beyond TDA class
  # in Processor SDK RTOS release
  PDK_VERSION_STR=_jacinto_08_06_01_03
ifeq ($(PDK_VERSION),)
  PDK_VERSION_STR=_jacinto_08_06_01_03
endif

  #Tool versions for non-TDA builds
  GCC_CROSS_TOOL_PREFIX=arm-none-eabi-
  GCC_CROSS_TOOL_TAG=9-2019-q4-major
  GCC_ARCH64_VERSION=9.2-2019.12
  GCC_ARCH64_BIN_PREFIX_STR=aarch64-none-elf
  CGT_VERSION=8.3.7
  BIOS_VERSION=6_83_02_07
  XDC_VERSION=3_61_04_40_core
  MMWAVE_DFP_VERSION=02_04_00_01

  CGT_C7X_VERSION=3.1.0.LTS
  CGT_ARM_VERSION=20.2.0.LTS
  CGT_ARMLLVM_VERSION=1.3.0.LTS
  GCC_VERSION_HARDLIB=9.2.1

  CGT_ARP32_VERSION=1.0.8
  CG_XML_VERSION=2.61.00

ifeq ($(BOARD),$(filter $(BOARD), tpr12_evm tpr12_qt awr294x_evm))
  CGT_ARM_VERSION=20.2.2.LTS
endif

  EDMA_VERSION=2_12_05_30E
  SECDEV_VERSION=01_06_00_05
  CGT_PRU_VERSION=2.3.3

  #Hardcode IPC version if it is not set already
  IPC_VERSION=3_50_04_08
  NDK_VERSION=3_61_01_01
  NS_VERSION=2_60_01_06

ifeq ($(BOARD),$(filter $(BOARD), am65xx_evm am65xx_idk j721e_evm j7200_evm j721s2_evm am64x_evm am64x_svb tpr12_qt tpr12_evm awr294x_evm j784s4_evm))
  NDK_VERSION=3_80_00_19
  NS_VERSION=2_80_00_17
endif

  UIA_VERSION=2_30_01_02
  XDAIS_VERSION=7_24_00_04
  AER_VERSION=17_0_0_0

  # C674x DSP libraries sould be used for OMAPL13x platform
ifeq ($(SOC),$(filter $(SOC), omapl137 omapl138))
  DSPLIB_VERSION ?= c674x_3_4_0_4
  IMGLIB_VERSION ?= c674x_3_1_1_0
  MATHLIB_VERSION ?= c674x_3_1_2_4
else
  DSPLIB_VERSION ?= c66x_3_4_0_4
  IMGLIB_VERSION ?= c66x_3_1_1_0
  MATHLIB_VERSION ?= c66x_3_1_2_4
endif

  export GCC_FLOAT_PATH ?= HARD

################################################################################
# Dependent toolchain paths variables
################################################################################
# Version of GCC
GCC_VERSION=$(GCC_CROSS_TOOL_PREFIX)$(GCC_CROSS_TOOL_TAG)
GCC_VERSION_ARM_A15=$(GCC_CROSS_TOOL_PREFIX)$(GCC_CROSS_TOOL_TAG)
  export GCC_VERSION_ARM_A8=$(GCC_CROSS_TOOL_PREFIX)$(GCC_CROSS_TOOL_TAG)
  export GCC_VERSION_ARM_A9=$(GCC_CROSS_TOOL_PREFIX)$(GCC_CROSS_TOOL_TAG)
  export CROSS_TOOL_PRFX           ?= $(GCC_CROSS_TOOL_PREFIX)
  export C6X_GEN_INSTALL_PATH      ?= $(TOOLS_INSTALL_PATH)/ti-cgt-c6000_$(CGT_VERSION)
  export C7X_GEN_INSTALL_PATH      ?= $(TOOLS_INSTALL_PATH)/ti-cgt-c7000_$(CGT_C7X_VERSION)
  export CL_PRU_INSTALL_PATH       ?= $(TOOLS_INSTALL_PATH)/ti-cgt-pru_$(CGT_PRU_VERSION)

ifeq ($(OS),Windows_NT)
  #Paths for windows machine
  export TOOLCHAIN_PATH_GCC_ARCH64 ?= $(TOOLS_INSTALL_PATH)/gcc-arm-$(GCC_ARCH64_VERSION)-mingw-w64-i686-aarch64-none-elf
else
  #Paths for linux machine
  export TOOLCHAIN_PATH_GCC_ARCH64 ?= $(TOOLS_INSTALL_PATH)/gcc-arm-$(GCC_ARCH64_VERSION)-x86_64-aarch64-none-elf
endif

  export GCC_ARCH64_BIN_PREFIX     ?= $(GCC_ARCH64_BIN_PREFIX_STR)

  export TOOLCHAIN_PATH_QNX_A72    ?= $(QNX_HOST)/usr/bin
  export TOOLCHAIN_PATH_A53        ?= $(TOOLCHAIN_PATH_GCC_ARCH64)
  export TOOLCHAIN_PATH_A72        ?= $(TOOLCHAIN_PATH_GCC_ARCH64)
  export TOOLCHAIN_PATH_EVE        ?= $(TOOLS_INSTALL_PATH)/arp32_$(CGT_ARP32_VERSION)
  export TOOLCHAIN_PATH_M4         ?= $(TOOLS_INSTALL_PATH)/ti-cgt-arm_$(CGT_ARM_VERSION)
  export TOOLCHAIN_PATH_R5         ?= $(TOOLS_INSTALL_PATH)/ti-cgt-armllvm_$(CGT_ARMLLVM_VERSION)
  export BIOS_INSTALL_PATH         ?= $(SDK_INSTALL_PATH)/bios_$(BIOS_VERSION)
  export DSPLIB_INSTALL_PATH       ?= $(SDK_INSTALL_PATH)/dsplib_$(DSPLIB_VERSION)
  export EDMA3LLD_BIOS6_INSTALLDIR ?= $(SDK_INSTALL_PATH)/edma3_lld_$(EDMA_VERSION)
  export IMGLIB_INSTALL_PATH       ?= $(SDK_INSTALL_PATH)/imglib_$(IMGLIB_VERSION)
  export IPC_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/ipc_$(IPC_VERSION)
  export MATHLIB_INSTALL_PATH      ?= $(SDK_INSTALL_PATH)/mathlib_$(MATHLIB_VERSION)
  export NDK_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/ndk_$(NDK_VERSION)
  export NS_INSTALL_PATH           ?= $(SDK_INSTALL_PATH)/ns_$(NS_VERSION)
  export PDK_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/pdk$(PDK_VERSION_STR)/packages
  export UIA_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/uia_$(UIA_VERSION)
  export RADARLINK_INSTALL_PATH    ?= $(SDK_INSTALL_PATH)/$(mmwavelink_version)
  export CG_XML_BIN_INSTALL_PATH   ?= $(SDK_INSTALL_PATH)/cg_xml_$(CG_XML_VERSION)/bin
  export TI_SECURE_DEV_PKG         ?= $(SDK_INSTALL_PATH)/proc-sdk-secdev_$(SECDEV_VERSION)
  export XDAIS_INSTALL_PATH        ?= $(SDK_INSTALL_PATH)/xdais_$(XDAIS_VERSION)
  export AER_INSTALL_PATH          ?= $(SDK_INSTALL_PATH)/aer_c64Px_obj_$(AER_VERSION)
  export GCC_ARM_NONE_TOOLCHAIN    ?= $(SDK_INSTALL_PATH)/gcc-$(GCC_CROSS_TOOL_PREFIX)$(GCC_CROSS_TOOL_TAG)
  export TI_CGT6x_INSTALL_DIR      ?= $(SDK_INSTALL_PATH)/c6000_7.4.16
  export M4_TOOLCHAIN_INSTALL_DIR  ?= $(TOOLCHAIN_PATH_M4)
  export FREERTOS_KERNEL_INSTALL_PATH   ?= $(PDK_INSTALL_PATH)/ti/kernel/freertos/FreeRTOS-LTS
  export FREERTOS_LABS_INSTALL_PATH     ?= $(PDK_INSTALL_PATH)/ti/kernel/freertos/FreeRTOS-Labs
  export MMWAVE_DFP_INSTALL_PATH        ?= $(SDK_INSTALL_PATH)/mmwave_dfp_$(MMWAVE_DFP_VERSION)

# Utilities directory. This is required only if the build machine is Windows.
# This should be CCS install directory as in c:/ti/ccsv<ver>/ccs/utils/cygwin
ifeq ($(OS),Windows_NT)
  export utils_PATH ?= c:/ti/ccs1120/ccs/utils/cygwin
endif
