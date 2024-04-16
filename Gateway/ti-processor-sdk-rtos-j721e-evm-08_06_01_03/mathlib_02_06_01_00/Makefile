#******************************************************************************
#*      Copyright (C) 2013 Texas Instruments Incorporated.                    *
#*                      All Rights Reserved                                   *
#******************************************************************************

CONCERTO_ROOT ?= concerto
ifeq ($(wildcard $(CONCERTO_ROOT)),)
$(error You must define CONCERTO_ROOT!)
endif
# Define the MATHLIB specific build locations
DIRECTORIES:= ti
BUILD_TARGET := $(abspath .)/target.mak
include $(CONCERTO_ROOT)/rules.mak
