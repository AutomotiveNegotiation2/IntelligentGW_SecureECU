#
# This file is the makefile for building SBL image
# that is loaded by R5 ROM.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

HLOS_SUFFIX=
ifeq ($(HLOS_BOOT),yes)
HLOS_SUFFIX=_hlos
endif
HS_SUFFIX=
ifeq ($(BUILD_HS),yes)
HS_SUFFIX=_hs
endif
DMA_SUFFIX=
ifeq ($(BOOTMODE), ospi)
  ifeq ($(SBL_USE_DMA),no)
    DMA_SUFFIX=_nondma
  endif
endif
EMMC_SUFFIX=
ifeq ($(EMMC_BOOT0), yes)
  EMMC_SUFFIX=_boot0
else ifeq ($(EMMC_BOOT0), no)
  EMMC_SUFFIX=_uda
endif

# if you want to boot app more than 500KB you need to change the following macro
# for instance your app is x KB then you need to give the macro with the following value from cmd line
# (x * 1024) in hexadecimal
MAX_APP_SIZE_EMMC ?= 0x7D000

ifeq ($(BOOT_PERF), yes)
  APP_NAME = sbl_boot_perf_cust_img
  LOCAL_APP_NAME = sbl_boot_perf_$(BOOTMODE)_img_$(CORE)
else ifeq ($(BOOTMODE), xip)
  ifeq ($(OSPI_FREQ), 133)
    APP_NAME = sbl_xip_133_img$(HS_SUFFIX)
    LOCAL_APP_NAME = sbl_xip_133_img_$(CORE)
  else
    APP_NAME = sbl_xip_img$(HS_SUFFIX)
    LOCAL_APP_NAME = sbl_xip_img_$(CORE)
  endif
else ifeq ($(RAT), 1)
  APP_NAME = sbl_cust_rat_main_ocm_img
  LOCAL_APP_NAME = sbl_cust_rat_main_ocm_img_$(CORE)
else
  APP_NAME = sbl_$(BOOTMODE)$(EMMC_SUFFIX)_img$(HLOS_SUFFIX)$(HS_SUFFIX)
  LOCAL_APP_NAME=sbl_$(BOOTMODE)$(EMMC_SUFFIX)_img$(HLOS_SUFFIX)_$(CORE)
endif
BUILD_OS_TYPE = baremetal

SRCDIR += $(PDK_SBL_COMP_PATH)/board/k3

INCDIR      += $(PDK_SBL_COMP_PATH)
INCDIR      += $(PDK_SBL_COMP_PATH)/soc
INCDIR      += $(PDK_SBL_COMP_PATH)/soc/k3

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the components required by the application
COMP_LIST_COMMON = $(PDK_COMMON_BAREMETAL_COMP)
ifneq ($(strip $(HS_SUFFIX)),) #if $(HS_SUFFIX) is non-empty
  SCICLIENT := $(filter sciclient%,$(COMP_LIST_COMMON))
  COMP_LIST_COMMON := $(subst $(SCICLIENT),$(SCICLIENT)_hs,$(COMP_LIST_COMMON))
endif

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(SBL_CFLAGS)

# Check for custom flags
ifeq ($(BOOTMODE), cust)
  SBL_CFLAGS = $(CUST_SBL_FLAGS)
  COMP_LIST_COMMON += sbl_lib_$(BOOTMODE)$(HS_SUFFIX)
  ifeq ($(RAT), 1)
    SBL_CFLAGS += -DSBL_OCM_MAIN_DOMAIN_RAT
  endif
else ifeq ($(BOOTMODE), xip)
  SBL_CFLAGS = $(CUST_SBL_FLAGS)
  SBL_CFLAGS += -DBUILD_XIP
  ifeq ($(OSPI_FREQ), 133)
    SBL_CFLAGS += -DOSPI_FREQ_133
  else
    SBL_CFLAGS += -DOSPI_FREQ_166
  endif
  COMP_LIST_COMMON += sbl_lib_cust$(HS_SUFFIX)
else
  COMP_LIST_COMMON += sbl_lib_$(BOOTMODE)$(DMA_SUFFIX)$(HLOS_SUFFIX)$(HS_SUFFIX)
endif # ifeq ($(BOOTMODE), cust)

ifeq ($(SBL_USE_DMA),yes)
  SBL_CFLAGS += -DSBL_USE_DMA=1
else
  SBL_CFLAGS += -DSBL_USE_DMA=0
endif

ifeq ($(BOOT_PERF), yes)
  SBL_CFLAGS += -DBOOT_PERF 
endif

# HLOS Boot flags
ifeq ($(HLOS_BOOT),yes)
  SBL_CFLAGS += -DSBL_ENABLE_HLOS_BOOT -DSBL_HLOS_OWNS_FLASH
endif
ifeq ($(BUILD_HS),yes)
  SBL_CFLAGS += -DSBL_BUILD_HS -DBUILD_HS
endif
# BOOTMODE specific CFLAGS
ifeq ($(BOOTMODE), mmcsd)
  SBL_CFLAGS += -DBOOT_MMCSD
endif # ifeq ($(BOOTMODE), mmcsd)

ifeq ($(BOOTMODE), emmc)
  SBL_CFLAGS += -DBOOT_EMMC
  ifeq ($(EMMC_BOOT0), yes)
    SBL_CFLAGS += -DEMMC_BOOT0
  endif
endif # ifeq ($(BOOTMODE), emmc)

ifeq ($(BOOTMODE), ospi)
  SBL_CFLAGS += -DBOOT_OSPI
endif # ifeq ($(BOOTMODE), ospi)

ifeq ($(BOOTMODE), hyperflash)
  SBL_CFLAGS += -DBOOT_HYPERFLASH
endif # ifeq ($(BOOTMODE), hyperflash)

ifeq ($(BOOTMODE), uart)
  SBL_CFLAGS += -DBOOT_UART
endif # ifeq ($(BOOTMODE), uart)

ifeq ($(BOOTMODE), qspi)
  SBL_CFLAGS += -DBOOT_QSPI
endif # ifeq ($(BOOTMODE), qspi)

ifeq ($(filter $(SBL_CFLAGS), -DBOOT_MMCSD), -DBOOT_MMCSD)
  COMP_LIST_COMMON += mmcsd fatfs_indp
endif # ifeq ($(filter $(SBL_CFLAGS), -DBOOT_MMCSD), -DBOOT_MMCSD)

ifeq ($(filter $(SBL_CFLAGS), -DBOOT_EMMC), -DBOOT_EMMC)
  COMP_LIST_COMMON += mmcsd fatfs_indp
endif # ifeq ($(filter $(SBL_CFLAGS), -DBOOT_EMMC), -DBOOT_EMMC)

ifeq ($(filter $(SBL_CFLAGS), -DBOOT_HYPERFLASH), -DBOOT_HYPERFLASH)
  COMP_LIST_COMMON += spi
endif # ifeq ($(filter $(SBL_CFLAGS), -DBOOT_HYPERFLASH), -DBOOT_HYPERFLASH)

ifeq ($(filter $(SBL_CFLAGS), -DBOOT_OSPI), -DBOOT_OSPI)
ifeq ($(filter $(SBL_CFLAGS), -DSBL_USE_DMA=1), -DSBL_USE_DMA=1)
  COMP_LIST_COMMON += spi_dma
else
  COMP_LIST_COMMON += spi
endif # ifeq ($(filter $(SBL_CFLAGS), -DSBL_USE_DMA=1), -DSBL_USE_DMA=1)
endif # ifeq ($(filter $(SBL_CFLAGS), -DBOOT_OSPI), -DBOOT_OSPI)

ifeq ($(filter $(SBL_CFLAGS), -DBOOT_QSPI), -DBOOT_QSPI)
ifeq ($(filter $(SBL_CFLAGS), -DSBL_USE_DMA=1), -DSBL_USE_DMA=1)
  COMP_LIST_COMMON += spi_dma
else
  COMP_LIST_COMMON += spi
endif # ifeq ($(filter $(SBL_CFLAGS), -DSBL_USE_DMA=1), -DSBL_USE_DMA=1)
endif # ifeq ($(filter $(SBL_CFLAGS), -DBOOT_OSPI), -DBOOT_OSPI)

SBL_CFLAGS += -DMAX_APP_SIZE_EMMC=$(MAX_APP_SIZE_EMMC)

SRCS_COMMON += sbl_main.c

EXTERNAL_LNKCMD_FILE_LOCAL = $(PDK_SBL_COMP_PATH)/soc/k3/$(SOC)/linker.cmd

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/ti/build/makerules
  export MAKERULEDIR
endif

# Select the SBL_OBJ_COPY to use.
#
SBL_OBJ_COPY := $(TOOLCHAIN_PATH_GCC_ARCH64)/bin/$(GCC_ARCH64_BIN_PREFIX)-objcopy
#SoCs like TPR12 do not have GCC tool. So we package it as part of SBL
#TI ARM CGT objcopy does not copy .data sections correctly so cannot be used
ifeq ("$(wildcard ${TOOLCHAIN_PATH_GCC_ARCH64})","")
$(error gcc-arm compiler not found. please download it by running setup_psdk_rtos.sh)
endif
export SBL_OBJ_COPY

# EFUSE_DEFAULT - R5 ROM will run the SBL in lockstep mode in lockstep
# #                 enabled devices and in split mode, if the devices do
# #                 not support lockstep.
# # SPLIT_MODE -    R5 ROM will awlys run the SBL on MCU1_0 in split mode
# #                 irrespective of whether the EFuse says the device can
# #                 support lockstep mode.
R5_STARTUP_MODE := SPLIT_MODE
export R5_STARTUP_MODE

include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
