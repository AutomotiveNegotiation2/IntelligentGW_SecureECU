#
# This file is the makefile for building timesync driver library.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

MODULE_NAME = enet_timesync_hal

SRCDIR = ./src
INCDIR = . ./include ../../

# List all the external components/interfaces, whose interface header files
# need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# Common source files and CFLAGS across all platforms and cores
ifeq ($(SOC),$(filter $(SOC), j721e j7200 j721s2 j784s4))
SRCS_COMMON += timeSync_cpsw.c
endif

ifeq ($(SOC),$(filter $(SOC), am65xx))
SRCS_COMMON += timeSync_icssg.c
endif

TIMESYNC_CFLAGS +=
PACKAGE_SRCS_COMMON = $(SRCDIR) ../hal
CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS) $(TIMESYNC_CFLAGS)

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
