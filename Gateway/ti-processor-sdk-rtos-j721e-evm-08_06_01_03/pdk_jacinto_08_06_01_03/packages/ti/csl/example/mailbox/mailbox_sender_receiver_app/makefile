#
# This file is the makefile for building CSL mailbox app.
#
include $(PDK_INSTALL_PATH)/ti/build/Rules.make

APP_NAME = csl_mailbox_sender_receiver_app
BUILD_OS_TYPE = baremetal
SRCDIR = .
INCDIR =

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = pdk

# List all the components required by the application
COMP_LIST_COMMON += csl_utils_common csl_uart_console $(PDK_COMMON_BAREMETAL_COMP)

# Common source files and CFLAGS across all platforms and cores
PACKAGE_SRCS_COMMON = .
SRCS_COMMON =

SRCS_mcu1_0 = mailbox_receiver.c
SRCS_mcu1_1 = mailbox_sender.c
SRCS_mpu1_0 = mailbox_sender.c

EXTERNAL_LNKCMD_FILE_LOCAL = linker_$(CORE).lds

CFLAGS_LOCAL_COMMON = $(PDK_CFLAGS)

ifeq ($(ISA),$(filter $(ISA), a72))
  LNKFLAGS_LOCAL_$(CORE) += --entry Entry
endif
CFLAGS_LOCAL_COMMON += -DBARE_METAL

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

# Nothing beyond this point
