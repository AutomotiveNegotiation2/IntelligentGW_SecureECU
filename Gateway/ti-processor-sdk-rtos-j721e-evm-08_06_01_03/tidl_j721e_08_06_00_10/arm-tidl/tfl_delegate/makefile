ALGBASE_PATH ?= $(abspath ../)
include $(ALGBASE_PATH)/config.mk

BUILD_IGNORE_LIB_ORDER := yes
GCC_LINUX_ROOT         := /usr


ifeq ($(TARGET_BUILD),debug)
  PROFILE := debug
else
  PROFILE := release
endif

DIRECTORIES := src

TARGET_COMBOS :=

SYSDEFS := CONCERTO_BUILD

ifeq ($(TARGET_PLATFORM),PC)
  TARGET_COMBOS += PC:LINUX:x86_64:1:$(PROFILE):GCC_LINUX
else
  ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J721S2 j721s2))
    TARGET_COMBOS += J721S2:LINUX:A72:1:$(PROFILE):GCC_LINUX_ARM
  else ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J784S4 j784s4))
    TARGET_COMBOS += J784S4:LINUX:A72:1:$(PROFILE):GCC_LINUX_ARM
  else ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), AM62A am62a))
    TARGET_COMBOS += AM62A:LINUX:A72:1:$(PROFILE):GCC_LINUX_ARM
  else
    TARGET_COMBOS += J7:LINUX:A72:1:$(PROFILE):GCC_LINUX_ARM
  endif
endif

BUILD_MULTI_PROJECT := 1

include $(CONCERTO_ROOT)/rules.mak

# Project specific rules

.PHONY: all
all:
