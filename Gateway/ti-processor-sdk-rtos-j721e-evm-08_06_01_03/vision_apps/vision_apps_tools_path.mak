
PSDK_PATH = $(abspath ..)
TIOVX_PATH = $(PSDK_PATH)/tiovx
MCUSW_PATH=$(PSDK_PATH)/mcusw

# paths for components shared between tiovx and vision_apps are specified in below
# file in tiovx, ex, bios, tidl, pdk, cgtools, ...
include $(TIOVX_PATH)/psdkra_tools_path.mak
include $(TIOVX_PATH)/build_flags.mak

# This is required to be set when pulling in the safertos_version
BOARD=$(SOC)_evm

ifeq ($(SOC), $(filter $(SOC), j721e j721s2 j784s4))
ifneq ($(wildcard $(PDK_PATH)),)
  include $(PDK_PATH)/packages/ti/build/safertos_version.mk

  ifeq ($(SAFERTOS_$(SOC)_r5f_INSTALL_PATH),)
    export SAFERTOS_KERNEL_INSTALL_PATH_r5f = $(PSDK_PATH)/safertos_$(SOC)_r5f_$(SAFERTOS_VERSION_r5f)
  else
    export SAFERTOS_KERNEL_INSTALL_PATH_r5f = $(SAFERTOS_$(SOC)_r5f_INSTALL_PATH)
  endif
  ifeq ($(SAFERTOS_$(SOC)_c7x_INSTALL_PATH),)
    export SAFERTOS_KERNEL_INSTALL_PATH_c7x = $(PSDK_PATH)/safertos_$(SOC)_c7x_$(SAFERTOS_VERSION_c7x)
  else
    export SAFERTOS_KERNEL_INSTALL_PATH_c7x = $(SAFERTOS_$(SOC)_c7x_INSTALL_PATH)
  endif
  ifeq ($(SOC),j721e)
    ifeq ($(SAFERTOS_$(SOC)_c66_INSTALL_PATH),)
      export SAFERTOS_KERNEL_INSTALL_PATH_c66 = $(PSDK_PATH)/safertos_$(SOC)_c66_$(SAFERTOS_VERSION_c66)
    else
      export SAFERTOS_KERNEL_INSTALL_PATH_c66 = $(SAFERTOS_$(SOC)_c66_INSTALL_PATH)
    endif
  endif
endif
endif

LINUX_FS_PATH ?= $(PSDK_PATH)/targetfs/
LINUX_FS_BOOT_PATH ?= $(PSDK_PATH)/bootfs/
LINUX_SD_FS_ROOT_PATH ?= /media/$(USER)/rootfs
LINUX_SD_FS_BOOT_PATH ?= /media/$(USER)/BOOT

TIOVX_CUSTOM_KERNEL_PATH ?= $(CUSTOM_KERNEL_PATH)
PTK_PATH           ?= $(PSDK_PATH)/ti-perception-toolkit
REMOTE_DEVICE_PATH ?= $(PSDK_PATH)/remote_device
TIADALG_PATH       ?= $(PSDK_PATH)/tiadalg
GLM_PATH           ?= $(PSDK_PATH)/glm
ETHFW_PATH         ?= $(PSDK_PATH)/ethfw
TI_SECURE_DEV_PKG  ?= $(PSDK_PATH)/core-secdev-k3

BUILD_OS ?= Linux

# QNX Paths
export PSDK_QNX_PATH ?= $(PSDK_PATH)/psdkqa
ifeq ($(SOC),j721e)
  export PSDK_LINUX_PATH ?= $(HOME)/ti-processor-sdk-linux-j7-evm-08_06_01_02
else ifeq ($(SOC),j721s2)
  export PSDK_LINUX_PATH ?= $(HOME)/ti-processor-sdk-linux-j721s2-evm-08_06_01_02
else ifeq ($(SOC),j784s4)
  export PSDK_LINUX_PATH ?= $(HOME)/ti-processor-sdk-linux-j784s4-evm-08_06_01_02
else ifeq ($(SOC),am62a)
  export PSDK_LINUX_PATH ?= $(HOME)/ti-processor-sdk-linux-am62axx-evm-08.05.00.24
endif

export QNX_SDP_VERSION ?= 710
ifeq ($(QNX_SDP_VERSION),700)
  export QNX_BASE ?= $(HOME)/qnx700
  export QNX_CROSS_COMPILER_TOOL ?= aarch64-unknown-nto-qnx7.0.0-
else
  export QNX_BASE ?= $(HOME)/qnx710
  export QNX_CROSS_COMPILER_TOOL ?= aarch64-unknown-nto-qnx7.1.0-
  # Adding this path for QNX SDP 7.1 which has a need to set the path
  # variable for the g++ tool to properly invloke the ld tool
  PATH := $(QNX_BASE)/host/linux/x86_64/usr/bin:$(PATH)
endif
export QNX_HOST ?= $(QNX_BASE)/host/linux/x86_64
export QNX_TARGET ?= $(QNX_BASE)/target/qnx7
export GCC_QNX_ROOT ?= $(QNX_HOST)/usr/bin
export GCC_QNX_ARM_ROOT ?= $(QNX_HOST)/usr/bin
export GCC_QNX_ARM ?= $(QNX_HOST)/usr/bin
QNX_BOOT_PATH ?= $(PSDK_QNX_PATH)/bootfs/
QNX_FS_PATH ?= $(PSDK_QNX_PATH)/qnxfs/
QNX_SD_FS_ROOT_PATH ?= /media/$(USER)/rootfs
QNX_SD_FS_QNX_PATH ?= /media/$(USER)/qnxfs
QNX_SD_FS_BOOT_PATH ?= /media/$(USER)/boot

ifeq ($(BUILD_OS),Linux)
GCC_LINUX_ROOT ?= /usr/
endif
