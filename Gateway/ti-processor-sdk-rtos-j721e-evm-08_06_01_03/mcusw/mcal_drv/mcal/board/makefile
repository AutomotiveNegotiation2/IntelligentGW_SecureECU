include $(MCUSW_INSTALL_PATH)/build/Rules.make

MODULE_NAME = brd

SRCDIR = flash/src
INCDIR = $(mcal_PATH)
# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk autosarBSW autosarConfig autosarCompiler
# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = fls brd bsw_stubs

MODULE_SRC_BASE_PATH := $(mcal_PATH)/board

# Common source files and CFLAGS across all platforms and cores

SRCS_COMMON += nor_spi_phy_tune.c nor_spi_patterns.c
#SRC_COMMON += phyTuning/nor_spi_phy_tune.c phyTuning/nor_spi_patterns.c
#Fls_Priv.c

ifeq ($(SOC),j721e)
   SRCS_COMMON += Fls_Brd_Nor_Ospi.c
endif
ifeq ($(SOC),j7200)
   SRCS_COMMON += Fls_Brd_Nor_Xspi.c
endif
ifeq ($(SOC),j721s2)
   SRCS_COMMON += Fls_Brd_Nor_Xspi.c
endif
ifeq ($(SOC),j784s4)
   SRCS_COMMON += Fls_Brd_Nor_Xspi.c
endif


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
