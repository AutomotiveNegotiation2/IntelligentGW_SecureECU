#
# This file is the makefile for building timesync PTP library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = enet_timesync_ptp

SRCDIR = . ./src
INCDIR = . ./include ../../

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk
INCLUDE_INTERNAL_INTERFACES = enet_timesync_hal

# List all the components required by the application
COMP_LIST_COMMON += timeSync

# Common source files and CFLAGS across all platforms and cores
SRCS_COMMON += timeSync_ptp.c
SRCS_COMMON += timeSync_ptp_init_priv.c
SRCS_COMMON += timeSync_ptp_osal_priv.c
SRCS_COMMON += timeSync_tools.c

PACKAGE_SRCS_COMMON = include $(SRCDIR) ../ptp ../../protocol ../../timeSync.h

CFLAGS_LOCAL_COMMON += $(PDK_CFLAGS) $(TIMESYNC_CFLAGS)

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
include $(MAKERULEDIR)/common.mk

# OBJs and libraries are built by using rule defined in rules_<target>.mk
#     and need not be explicitly specified here

# Nothing beyond this point:
