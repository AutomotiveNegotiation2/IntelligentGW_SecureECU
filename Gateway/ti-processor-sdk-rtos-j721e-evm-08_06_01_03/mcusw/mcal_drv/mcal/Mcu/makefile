include $(MCUSW_INSTALL_PATH)/build/Rules.make

MODULE_NAME = mcu
ifeq ($(SOC),$(filter $(SOC), j7200 j721e j721s2 j784s4))
SRCDIR = src $(mcal_PATH)/Mcu/mcu_hw/V1
INCDIR =  src $(mcal_PATH)
else
#other Soc requirements
endif

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = autosarBSW autosarConfig autosarCompiler

# List all the internal submodules whose interface header files
# need to be included for this module
INCLUDE_INTERNAL_INTERFACES = mcu bsw_stubs

MODULE_SRC_BASE_PATH := $(mcal_PATH)/Mcu

# Common source files and CFLAGS across all platforms and cores
ifeq ($(SOC),$(filter $(SOC), j7200 j721e j721s2 j784s4))
SRCS_COMMON += Mcu.c Mcu_Priv.c
else

#other Soc requirements
endif
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
