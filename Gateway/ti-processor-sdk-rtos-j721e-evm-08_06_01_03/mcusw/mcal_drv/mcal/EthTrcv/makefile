include $(MCUSW_INSTALL_PATH)/build/Rules.make

MODULE_NAME = ethtrcv

SRCDIR = src
INCDIR = $(MCUSW_INSTALL_PATH)/mcal_drv \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/EthTrcv/include/ \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/Eth/src/udma \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/csl \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/Eth_Wrapper/Implementation

INCDIR += $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/examples_config/EthTrcv_Demo_Cfg/output/generated/soc/$(SOC)/$(CORE)/include

BUILD_VARIANT ?= PreCompile
ifeq ($(BUILD_VARIANT), PreCompile)
  INCDIR += $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/examples_config/Eth_Demo_Cfg/output/generated/soc/$(SOC)/$(CORE)//include
else
ifeq ($(BUILD_VARIANT), LinkTime)
  INCDIR += $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/examples_config/Eth_Demo_Lcfg/output/generated/soc/$(SOC)/$(CORE)/include
else
  INCDIR += $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/examples_config/Eth_Demo_PBcfg/output/generated/soc/$(SOC)/$(CORE)/include
endif
endif

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk autosarBSW autosarConfig autosarCompiler

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = eth ethtrcv bsw_stubs

MODULE_SRC_BASE_PATH := $(mcal_PATH)/Eth

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += EthTrcv.c EthTrcv_Priv.c

PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(MCUSW_CFLAGS)

# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(PDK_INSTALL_PATH)/ti/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
