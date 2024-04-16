
include $(MCUSW_INSTALL_PATH)/build/Rules.make

MODULE_NAME = bsw_stubs

ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(PDK_INSTALL_PATH)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/platform.mk

#Accomodating Changes for introducing multiple Tool Chains
SRCDIR = Det/src Dem/src Rte/src CanIf/src Os/src EcuM/src Fee/src MemIf/src
INCDIR = $(mcal_PATH)

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk autosarBSW autosarCompiler
INCLUDE_INTERNAL_INTERFACES = bsw_stubs app_utils
UtilsPriv_INCLUDE =

SRCS_COMMON += Det.c Dem.c Os.c
SRCS_COMMON += SchM_Spi.c SchM_Can.c SchM_Dio.c SchM_Fls.c SchM_Mcu.c
SRCS_COMMON += SchM_Eth.c SchM_EthTrcv.c SchM_Gpt.c SchM_Pwm.c SchM_Adc.c SchM_Icu.c
SRCS_COMMON += SchM_Cdd_Ipc.c
SRCS_COMMON += EcuM_Cbk.c
SRCS_COMMON += CanIf_Cbk.c Fee_Cbk.c

PACKAGE_SRCS_COMMON = .
CFLAGS_LOCAL_COMMON = $(MCUSW_CFLAGS)

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
