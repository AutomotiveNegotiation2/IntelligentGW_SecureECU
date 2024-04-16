#
# This file is the makefile for building VHWA LDC test app for TI RTOS
#
ifeq ($(RULES_MAKE), )
include $(PDK_INSTALL_PATH)/ti/build/Rules.make
else
include $(RULES_MAKE)
endif

ifeq ($(BUILD_OS_TYPE), baremetal)
    APP_NAME = vhwa_ldc_$(BUILD_OS_TYPE)_testapp
else
    APP_NAME = vhwa_ldc_testapp_$(BUILD_OS_TYPE)
endif

include makefile.mk
