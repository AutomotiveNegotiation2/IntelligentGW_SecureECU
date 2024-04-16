#
# module name       :TIDL
#
# module descripton :TI Deep learning Library module is TIs CNN/DNN
#                    acceleration on EVE and DSP
#
# Copyright (C) 2016-2017 Texas Instruments Incorporated - http://www.ti.com/
#
# ALL RIGHTS RESERVED
#
# 
#
ALGBASE_PATH ?= $(abspath ../../)
include $(ALGBASE_PATH)/makerules/config.mk

##############################################################
DSP_COMMON_DIR= ../../common

##############################################################


##############################################################

SUBDIRS = ./inc
SUBDIRS+= ./src

CFILES= $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.c))
HFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.h))
CPPFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)/*.cpp))

CMD_FILE= tidl_alg.cmd

LIB_DIR=algo

ifeq ($(TIDL_BUILD_PATHS), LEGACY)
ifeq ($(TARGET_PLATFORM) , PC)
LIBDIR  = ../lib/PC/$(CORE)/$(LIB_DIR)/$(TARGET_BUILD)
else
LIBDIR  = ../lib/$(CORE)/$(LIB_DIR)/$(TARGET_BUILD)
endif
else
ifeq ($(TARGET_PLATFORM) , PC)
LIBDIR  = ../lib/$(TARGET_SOC)/PC/$(LIB_DIR)/$(TARGET_BUILD)
else
LIBDIR  = ../lib/$(TARGET_SOC)/$(CORE)/$(LIB_DIR)/$(TARGET_BUILD)
endif
endif

ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
OUTFILE=$(LIBDIR)/tidl_algo.lib
else
OUTFILE=$(LIBDIR)/libtidl_algo.a
endif
else
OUTFILE=$(LIBDIR)/tidl_algo.lib
endif

##############################################################


##############################################################
include $(ALGBASE_PATH)/makerules/rules.mk
include $(ALGBASE_PATH)/makerules/common.mk
#used inside makerules, but okay to define it afterwards
INCLUDE_PATHS+= -I .
#INCLUDE_PATHS+= -I $(MMALIB_PATH)/vxlib/ti/vxlib/src
INCLUDE_PATHS+= -I $(MMALIB_PATH)/ti/mmalib/src/cnn_c7xmma
#INCLUDE_PATHS+= -I $(MMALIB_PATH)/vxlib/ti/vxlib/src/cnn_c7xmma/MMALIB_CNN_convolve_row_ixX_ixX_oxX
#INCLUDE_PATHS+= -I $(MMALIB_PATH)/vxlib/ti/vxlib/src/cnn_c7xmma/MMALIB_CNN_convolve_col_smallNo_ixX_ixX_oxX
#INCLUDE_PATHS+= -I $(MMALIB_PATH)/vxlib/ti/vxlib/src/common
#INCLUDE_PATHS+= -I $(MMALIB_PATH)/vxlib/ti/vxlib/src/common/c71
#INCLUDE_PATHS+= -I $(MMALIB_PATH)/vxlib
#INCLUDE_PATHS+= -I $(DMAUTILS_PATH)/inc
#INCLUDE_PATHS+= -I $(DMAUTILS_PATH)/inc/edma_utils
INCLUDE_PATHS+= -I ./inc
INCLUDE_PATHS+= -I ./inc/dummy
INCLUDE_PATHS+= -I ../inc
INCLUDE_PATHS+= -I $(IVISION_PATH)
INCLUDE_PATHS+= -I $(IVISION_PATH)/ti/xdais
INCLUDE_PATHS+= -I $(MATHLIB_INSTALL_DIR)/packages
INCLUDE_PATHS+= -I $(MATHLIB_INSTALL_DIR)/packages/ti/mathlib
INCLUDE_PATHS+= -I $(DSP_COMMON_DIR)
INCLUDE_PATHS+= -I /usr/local/include
INCLUDE_PATHS+= -I $(PDK_INSTALL_PATH)
INCLUDE_PATHS+= -I $(PDK_INSTALL_PATH)/ti/drv/udma/dmautils/inc
INCLUDE_PATHS+= -I $(PDK_INSTALL_PATH)/ti/drv/udma/dmautils/udma_standalone
INCLUDE_PATHS+= -I ../utils/perfsim
INCLUDE_PATHS+= -I src/tidsp/inc
INCLUDE_PATHS+= -I src/tidsp/inc_priv
#CFLAGS+= -I $(VLIB_INSTALL_DIR)
#############################################################
# Hack for one or two level back path inclusion in VLIB repo
#############################################################
#CFLAGS+= -I $(VLIB_INSTALL_DIR)/ti/vlib/src/common/c66
#CFLAGS+= -I $(VLIB_INSTALL_DIR)/ti/vlib/src/common


#ifeq ($(TARGET_PLATFORM) , TI_DEVICE)
#CFLAGS += -mv7100
#endif
#mv7100 should be in rules.mk
INCLUDE_PATHS+= -I $(DSP_COMMON_DIR)
INCLUDE_PATHS+= -I $(DSP_COMMON_DIR)/c6xsim

CFLAGS += $(INCLUDE_PATHS)


##############################################################


##############################################################
LDFLAGS= -l "./tidl_alg.cmd"
ifeq ($(CORE) , eve)
$(OUTFILE) : libfile
else ifeq ($(CORE) , dsp)
$(OUTFILE) : libfile
endif

##############################################################

