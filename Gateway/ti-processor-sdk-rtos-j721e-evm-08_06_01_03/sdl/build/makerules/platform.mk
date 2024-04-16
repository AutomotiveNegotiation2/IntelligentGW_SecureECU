#*******************************************************************************
#                                                                              *
# Copyright (c) 2021 Texas Instruments Incorporated - http://www.ti.com/       *
#                        ALL RIGHTS RESERVED                                   *
#                                                                              *
#*******************************************************************************

# Filename: platform.mk
#
# Platforms make file - Platform/SoC/targets are defined/derived in this file
#
# This file needs to change when:
#     1. a new platform/SoC is added, which also might have its own cores/ISAs
#

#
# Derive SOCFAMILY from SOC
#

# J721E
ifeq ($(SOC),$(filter $(SOC), j721e))
SOCFAMILY = j721e
BOARD = j721e_evm
endif

# Derive Target/ISA from CORE

# r5f
ifeq ($(CORE),$(filter $(CORE), r5f))
 ISA = r5f
 ISA_EXT = r5f
 ARCH = armv7m
endif

#
# Derive XDC/ISA specific settings
#
ifeq ($(FORMAT),ELF)
  FORMAT_EXT = e
endif
# If ENDIAN is set to "big", set ENDIAN_EXT to "e", that would be used in
#    in the filename extension of object/library/executable files
ifeq ($(ENDIAN),big)
  ENDIAN_EXT = e
endif

# J721E
ifeq ($(BOARD),$(filter $(BOARD), j721e_sim j721e_hostemu j721e_ccqt j721e_loki j721e_qt j721e_vhwazebu j721e_evm))
 SOC = j721e
 SBL_RUN_ADDRESS=0x41C00100
 SBL_DEV_ID=55
endif

# J721E support for mcu1_0
ifeq ($(SOC),$(filter $(SOC), j721e))
  SBL_CORE_ID_r5f = 8
  SBL_CORE_ID_r5f_smp = 27
endif

# Define the file extensions
OBJEXT = o$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
LIBEXT = a$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
EXEEXT = x$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)
ASMEXT = s$(FORMAT_EXT)$(ISA)$(ENDIAN_EXT)

export SOC
export SOCFAMILY

# Nothing beyond this point
