
include $(MCUSW_INSTALL_PATH)/build/Rules.make

MODULE_NAME = app_utils

ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(PDK_INSTALL_PATH)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/platform.mk

#Accommodating Changes for introducing multiple Tool Chains
SRCDIR = src
INCDIR = . $(mcal_PATH)

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk autosarCompiler
INCLUDE_INTERNAL_INTERFACES = app_utils
UtilsPriv_INCLUDE =

SRCS_COMMON += app_utils.c app_r5f_Pmu.c rti.c

CFLAGS_LOCAL_COMMON = $(MCUSW_CFLAGS)
LNKFLAGS_LOCAL_COMMON = $(MCUSW_LNKFLAGS)

ifeq ($(MCUSW_UART_ENABLE),TRUE)
    CFLAGS_LOCAL_COMMON += -DUART_ENABLED
endif
# Core/SoC/platform specific source files and CFLAGS
# Example:
#   SRCS_<core/SoC/platform-name> =
#   CFLAGS_LOCAL_<core/SoC/platform-name> =

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(PDK_INSTALL_PATH)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point
