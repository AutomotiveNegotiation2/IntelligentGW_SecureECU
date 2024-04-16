include $(MCUSW_INSTALL_PATH)/build/Rules.make

MODULE_NAME = eth

SRCDIR =  $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/Eth/src  \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/Eth/src/cpsw  \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/Eth/src/udma

INCDIR =  $(MCUSW_INSTALL_PATH)/mcal_drv \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/Eth/src \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/Eth/src/cpsw/include \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/Eth/include/ \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/EthTrcv/include/ \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/Eth/src/udma \
          $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/Eth/src/csl

INCDIR += $(mcu_plus_sdk_INSTALL_PATH)/source/drivers/sciclient/include \
          $(mcu_plus_sdk_INSTALL_PATH)/source/drivers \
          $(mcu_plus_sdk_INSTALL_PATH)/source/drivers/sciclient \
          $(mcu_plus_sdk_INSTALL_PATH)/source/drivers/sciclient/include \
          $(mcu_plus_sdk_INSTALL_PATH)/source/drivers/drivers/hw_include \
          $(mcu_plus_sdk_INSTALL_PATH)/source

INCDIR += $(MCUSW_INSTALL_PATH)/mcal_drv/mcal
INCDIR += $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/examples_config/EthTrcv_Demo_Cfg/output/generated/soc/$(SOC)/$(CORE)/include

BUILD_VARIANT ?= PreCompile
ifeq ($(BUILD_VARIANT), PreCompile)
  INCDIR += $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/examples_config/Eth_Demo_Cfg/output/generated/soc/$(SOC)/$(CORE)/include
else
ifeq ($(BUILD_VARIANT), LinkTime)
  INCDIR += $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/examples_config/Eth_Demo_Lcfg/output/generated/soc/$(SOC)/$(CORE)/include
else
  INCDIR += $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/examples_config/Eth_Demo_PBcfg/output/generated/soc/$(SOC)/$(CORE)/include
endif
endif

#$(mcal_PATH)/Bsw_Stubs/AsrGnrl/inc

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk autosarBSW autosarConfig autosarCompiler

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = eth ethtrcv bsw_stubs cdd_ipc gpt

MODULE_SRC_BASE_PATH := $(mcal_PATH)/Eth

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += Cpsw_Dma.c      \
               Cpsw_Port.c     \
               Cpsw_Mac.c      \
               Cpsw_Stats.c    \
               Cpsw_Mdio.c     \
               Cpsw_Ale.c      \
               Cpsw_Cpts.c     \
               Eth.c           \
               Eth_Irq.c       \
               Eth_Priv.c      \
               Udma_Ring_LL.c \
               Udma_LL.c \
               Udma.c \
               Udma_SciClient.c \
               Eth_Packet.c \
               Eth_IrqPacing.c

ifeq ($(SOC),$(filter $(SOC), j721e j7200 j784s4))
SRCS_COMMON += Eth_Rpc.c Eth_VirtMac.c
endif

SRCDIR +=  $(MCUSW_INSTALL_PATH)/mcal_drv/mcal/Eth/src/csl
SRCS_COMMON += csl_cpsw.c \
               csl_cpsw_ale_9g_tblcfg.c \
               csl_cpgmac_sl.c \
               csl_mdio.c \
               csl_cpts.c \

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
