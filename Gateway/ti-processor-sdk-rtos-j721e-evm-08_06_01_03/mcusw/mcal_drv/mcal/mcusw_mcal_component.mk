# This file is component include make file of MCAL components.
# List of variables set in this file and their purpose:
# <mod>_RELPATH        - This is the relative path of the module, typically from
#                        top-level directory of the package
# <mod>_PATH           - This is the absolute path of the module. It derives from
#                        absolute path of the top-level directory (set in env.mk)
#                        and relative path set above
# <mod>_INCLUDE        - This is the path that has interface header files of the
#                        module. This can be multiple directories (space separated)
# <mod>_PKG_LIST       - Names of the modules (and sub-modules) that are a part
#                        part of this module, including itself.
# <mod>_BOARD_DEPENDENCY - "yes": means the code for this module depends on
#                             platform and the compiled obj/lib has to be kept
#                             under <platform> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no platform dependent code and hence
#                             the obj/libs are not kept under <platform> dir.
# <mod>_CORE_DEPENDENCY     - "yes": means the code for this module depends on
#                             core and the compiled obj/lib has to be kept
#                             under <core> directory
#                             "no" or "" or if this variable is not defined: means
#                             this module has no core dependent code and hence
#                             the obj/libs are not kept under <core> dir.
# <mod>_APP_STAGE_FILES     - List of source files that belongs to the module
#                             <mod>, but that needs to be compiled at application
#                             build stage (in the context of the app). This is
#                             primarily for link time configurations or if the
#                             source file is dependent on options/defines that are
#                             application dependent. This can be left blank or
#                             not defined at all, in which case, it means there
#                             no source files in the module <mod> that are required
#                             to be compiled in the application build stage.
#
ifeq ($(mcusw_mcal_component_make_include), )

mcusw_mcal_default_SOCLIST          = j721e j7200 j721s2 j784s4
mcusw_mcal_default_BOARDLIST        = j721e_sim j721e_evm j7200_evm j721s2_evm j784s4_evm
mcusw_mcal_default_j7200_CORELIST   = mcu1_0 mcu2_1
mcusw_mcal_default_j721e_CORELIST   = mcu1_0 mcu1_1 mcu2_0 mcu2_1 mcu3_0 mcu3_1
mcusw_mcal_default_j721s2_CORELIST   = mcu1_0 mcu2_1
mcusw_mcal_default_j784s4_CORELIST   = mcu1_0 mcu2_1

############################
# mcal package
# List of components included under mcal lib
# The components included here are built and will be part of mcal lib
############################
mcusw_mcal_LIB_LIST =

############################
# mcal examples
# List of mcal examples mcal (+= is used at each example definition)
# All the examples mentioned in list are built when test target is called
# List below all examples for allowed values
############################
mcusw_mcal_EXAMPLE_LIST =

############################
# mcal DUP examples
# List of mcal DUP examples mcal (+= is used at each example definition)
# All the examples mentioned in list are built individually (not with build all)
# List below all examples for allowed values
############################
mcusw_mcal_dup_EXAMPLE_LIST =

#
# MCAL Modules
#

# FLS
fls_COMP_LIST = fls
fls_RELPATH = mcal/Fls
fls_PATH = $(mcal_PATH)/Fls
fls_MAKEFILE = -fmakefile
export fls_MAKEFILE
fls_BOARD_DEPENDENCY = no
fls_CORE_DEPENDENCY = no
export fls_COMP_LIST
export fls_BOARD_DEPENDENCY
export fls_CORE_DEPENDENCY
fls_PKG_LIST = fls
export fls_PKG_LIST
fls_INCLUDE = $(fls_PATH)/include
fls_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export fls_SOCLIST
fls_$(SOC)_CORELIST = mcu1_0 mcu2_1
export fls_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += fls

# BOARD
brd_COMP_LIST = brd
brd_RELPATH = mcal/board
brd_PATH = $(mcal_PATH)/board
brd_MAKEFILE = -fmakefile
export brd_MAKEFILE
brd_BOARD_DEPENDENCY = no
brd_CORE_DEPENDENCY = no
export brd_COMP_LIST
export brd_BOARD_DEPENDENCY
export brd_CORE_DEPENDENCY
brd_PKG_LIST = brd
export brd_PKG_LIST
brd_INCLUDE = $(brd_PATH)/flash/inc
brd_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export brd_SOCLIST
brd_$(SOC)_CORELIST = mcu1_0 mcu2_1
export brd_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += brd

# SPI
spi_COMP_LIST = spi
spi_RELPATH = mcal/Spi
spi_PATH = $(mcal_PATH)/Spi
spi_MAKEFILE = -fmakefile
export spi_MAKEFILE
spi_BOARD_DEPENDENCY = no
spi_CORE_DEPENDENCY = yes
export spi_COMP_LIST
export spi_BOARD_DEPENDENCY
export spi_CORE_DEPENDENCY
spi_PKG_LIST = spi
export spi_PKG_LIST
spi_INCLUDE = $(spi_PATH)/include
spi_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export spi_SOCLIST
spi_$(SOC)_CORELIST = $(mcusw_mcal_default_$(SOC)_CORELIST)
export spi_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += spi

# DIO
dio_COMP_LIST = dio
dio_RELPATH = mcal/Dio
dio_PATH = $(mcal_PATH)/Dio
dio_MAKEFILE = -fmakefile
export dio_MAKEFILE
dio_BOARD_DEPENDENCY = no
dio_CORE_DEPENDENCY = yes
export dio_COMP_LIST
export dio_BOARD_DEPENDENCY
export dio_CORE_DEPENDENCY
dio_PKG_LIST = dio
export dio_PKG_LIST
dio_INCLUDE = $(dio_PATH)/include
dio_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export dio_SOCLIST
dio_$(SOC)_CORELIST = $(mcusw_mcal_default_$(SOC)_CORELIST)
export dio_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += dio

# GPT
gpt_COMP_LIST = gpt
gpt_RELPATH = mcal/Gpt
gpt_PATH = $(mcal_PATH)/Gpt
gpt_MAKEFILE = -fmakefile
export gpt_MAKEFILE
gpt_BOARD_DEPENDENCY = no
gpt_CORE_DEPENDENCY = yes
export gpt_COMP_LIST
export gpt_BOARD_DEPENDENCY
export gpt_CORE_DEPENDENCY
gpt_PKG_LIST = gpt
export gpt_PKG_LIST
gpt_INCLUDE = $(gpt_PATH)/include
gpt_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export gpt_SOCLIST
gpt_$(SOC)_CORELIST = $(mcusw_mcal_default_$(SOC)_CORELIST)
export gpt_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += gpt

# Eth
eth_COMP_LIST = eth
eth_RELPATH = mcal/Eth
eth_PATH = $(mcal_PATH)/Eth
eth_MAKEFILE = -fmakefile
export eth_MAKEFILE
eth_BOARD_DEPENDENCY = no
eth_CORE_DEPENDENCY = yes
export eth_COMP_LIST
export eth_BOARD_DEPENDENCY
export eth_CORE_DEPENDENCY
eth_PKG_LIST = eth
export eth_PKG_LIST
eth_INCLUDE = $(eth_PATH)/include
eth_INCLUDE += $(eth_PATH)/src
eth_INCLUDE += $(eth_PATH)/src/cpsw/include
eth_INCLUDE += $(eth_PATH)/config
eth_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export eth_SOCLIST
eth_$(SOC)_CORELIST = mcu1_0 mcu2_1
export eth_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += eth

# EthTrcv
ethtrcv_COMP_LIST = ethtrcv
ethtrcv_RELPATH = mcal/EthTrcv
ethtrcv_PATH = $(mcal_PATH)/EthTrcv
ethtrcv_MAKEFILE = -fmakefile
export ethtrcv_MAKEFILE
ethtrcv_BOARD_DEPENDENCY = no
ethtrcv_CORE_DEPENDENCY = yes
export ethtrcv_COMP_LIST
export ethtrcv_BOARD_DEPENDENCY
export ethtrcv_CORE_DEPENDENCY
ethtrcv_PKG_LIST = ethtrcv
export ethtrcv_PKG_LIST
ethtrcv_INCLUDE = $(ethtrcv_PATH)/include
ethtrcv_INCLUDE += $(ethtrcv_PATH)/config
ethtrcv_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export ethtrcv_SOCLIST
ethtrcv_$(SOC)_CORELIST = mcu1_0
export ethtrcv_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += ethtrcv

# CAN
can_COMP_LIST = can
can_RELPATH = mcal/Can
can_PATH = $(mcal_PATH)/Can
can_MAKEFILE = -fmakefile
export can_MAKEFILE
can_BOARD_DEPENDENCY = no
can_CORE_DEPENDENCY = yes
export can_COMP_LIST
export can_BOARD_DEPENDENCY
export can_CORE_DEPENDENCY
can_PKG_LIST = can
export can_PKG_LIST
can_INCLUDE = $(can_PATH)/include
can_SOCLIST = j721e j7200 j721s2
export can_SOCLIST
can_$(SOC)_CORELIST = $(mcusw_mcal_default_$(SOC)_CORELIST)
export can_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += can

# WDG
wdg_COMP_LIST = wdg
wdg_RELPATH = mcal/Wdg
wdg_PATH = $(mcal_PATH)/Wdg
wdg_MAKEFILE = -fmakefile
export wdg_MAKEFILE
wdg_BOARD_DEPENDENCY = no
wdg_CORE_DEPENDENCY = yes
export wdg_COMP_LIST
export wdg_BOARD_DEPENDENCY
export wdg_CORE_DEPENDENCY
wdg_PKG_LIST = wdg
export wdg_PKG_LIST
wdg_INCLUDE = $(wdg_PATH)/include
wdg_SOCLIST = j721e j7200 j721s2
export wdg_SOCLIST
wdg_$(SOC)_CORELIST = $(mcusw_mcal_default_$(SOC)_CORELIST)
export wdg_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += wdg

# PWM
pwm_COMP_LIST = pwm
pwm_RELPATH = mcal/Pwm
pwm_PATH = $(mcal_PATH)/Pwm
pwm_MAKEFILE = -fmakefile
export pwm_MAKEFILE
pwm_BOARD_DEPENDENCY = no
pwm_CORE_DEPENDENCY = yes
export pwm_COMP_LIST
export pwm_BOARD_DEPENDENCY
export pwm_CORE_DEPENDENCY
pwm_PKG_LIST = pwm
export pwm_PKG_LIST
pwm_INCLUDE = $(pwm_PATH)/include
pwm_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export pwm_SOCLIST
pwm_$(SOC)_CORELIST = $(mcusw_mcal_default_$(SOC)_CORELIST)
export pwm_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += pwm

# ADC
adc_COMP_LIST = adc
adc_RELPATH = mcal/Adc
adc_PATH = $(mcal_PATH)/Adc
adc_MAKEFILE = -fmakefile
export adc_MAKEFILE
adc_BOARD_DEPENDENCY = no
adc_CORE_DEPENDENCY = yes
export adc_COMP_LIST
export adc_BOARD_DEPENDENCY
export adc_CORE_DEPENDENCY
adc_PKG_LIST = adc
export adc_PKG_LIST
adc_INCLUDE = $(adc_PATH)/include
adc_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export adc_SOCLIST
adc_$(SOC)_CORELIST = $(mcusw_mcal_default_$(SOC)_CORELIST)
export adc_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += adc

# CDD Ipc
cdd_ipc_COMP_LIST = cdd_ipc
cdd_ipc_RELPATH = mcal/CddIpc
cdd_ipc_PATH = $(mcal_PATH)/CddIpc
cdd_ipc_MAKEFILE = -fmakefile
export cdd_ipc_MAKEFILE
cdd_ipc_BOARD_DEPENDENCY = no
cdd_ipc_CORE_DEPENDENCY = yes
export cdd_ipc_COMP_LIST
export cdd_ipc_BOARD_DEPENDENCY
export cdd_ipc_CORE_DEPENDENCY
cdd_ipc_PKG_LIST = cdd_ipc
export cdd_ipc_PKG_LIST
cdd_ipc_INCLUDE = $(cdd_ipc_PATH)/include
cdd_ipc_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export cdd_ipc_SOCLIST
cdd_ipc_$(SOC)_CORELIST = mcu2_1
export cdd_ipc_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += cdd_ipc

# IPC library
ipc_baremetal_COMP_LIST = ipc_baremetal
ipc_baremetal_RELPATH = mcal/CddIpc/ipc_baremetal_hw
ipc_baremetal_PATH = $(mcal_PATH)/CddIpc/ipc_baremetal_hw
ipc_baremetal_MAKEFILE = -fmakefile
export ipc_baremetal_MAKEFILE
ipc_baremetal_BOARD_DEPENDENCY = no
ipc_baremetal_CORE_DEPENDENCY = yes
export ipc_baremetal_COMP_LIST
export ipc_baremetal_BOARD_DEPENDENCY
export ipc_baremetal_CORE_DEPENDENCY
ipc_baremetal_PKG_LIST = ipc_baremetal
export ipc_baremetal_PKG_LIST
ipc_baremetal_INCLUDE = $(ipc_baremetal_PATH)
ipc_baremetal_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export ipc_baremetal_SOCLIST
ipc_baremetal_$(SOC)_CORELIST = mcu2_1
export ipc_baremetal_$(SOC)_CORELIST
ipc_LIB_LIST += ipc_baremetal

# ICU
icu_COMP_LIST = icu
icu_RELPATH = mcal/Icu
icu_PATH = $(mcal_PATH)/Icu
icu_MAKEFILE = -fmakefile
export icu_MAKEFILE
icu_BOARD_DEPENDENCY = no
icu_CORE_DEPENDENCY = yes
export icu_COMP_LIST
export icu_BOARD_DEPENDENCY
export icu_CORE_DEPENDENCY
icu_PKG_LIST = icu
export icu_PKG_LIST
icu_INCLUDE = $(icu_PATH)/include
icu_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export icu_SOCLIST
icu_$(SOC)_CORELIST = $(mcusw_mcal_default_$(SOC)_CORELIST)
export icu_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += icu


# MCU
mcu_COMP_LIST = mcu
mcu_RELPATH = mcal/Mcu
mcu_PATH = $(mcal_PATH)/Mcu
mcu_MAKEFILE = -fmakefile
export mcu_MAKEFILE
mcu_BOARD_DEPENDENCY = no
mcu_CORE_DEPENDENCY = yes
export mcu_COMP_LIST
export mcu_BOARD_DEPENDENCY
export mcu_CORE_DEPENDENCY
mcu_PKG_LIST = mcu
export mcu_PKG_LIST
mcu_INCLUDE = $(mcu_PATH)/include
mcu_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export mcu_SOCLIST
mcu_$(SOC)_CORELIST = mcu1_0 mcu2_1
export mcu_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += mcu


# BSW_STUBS
bsw_stubs_COMP_LIST = bsw_stubs
bsw_stubs_RELPATH = mcal/Bsw_Stubs
bsw_stubs_PATH = $(mcal_PATH)/Bsw_Stubs
bsw_stubs_MAKEFILE = -fmakefile
export bsw_stubs_MAKEFILE
bsw_stubs_BOARD_DEPENDENCY = no
bsw_stubs_CORE_DEPENDENCY = no
export bsw_stubs_COMP_LIST
export bsw_stubs_BOARD_DEPENDENCY
export bsw_stubs_CORE_DEPENDENCY
bsw_stubs_PKG_LIST = bsw_stubs
export bsw_stubs_PKG_LIST
bsw_stubs_INCLUDE = $(bsw_stubs_PATH)/Det/inc
bsw_stubs_INCLUDE += $(bsw_stubs_PATH)/MemMap/inc
bsw_stubs_INCLUDE += $(bsw_stubs_PATH)/Os/inc
bsw_stubs_INCLUDE += $(bsw_stubs_PATH)/Dem/inc
bsw_stubs_INCLUDE += $(bsw_stubs_PATH)/Rte/inc
bsw_stubs_INCLUDE += $(bsw_stubs_PATH)/EcuM/inc
bsw_stubs_INCLUDE += $(bsw_stubs_PATH)/EthIf/inc
bsw_stubs_INCLUDE += $(bsw_stubs_PATH)/Fee/inc
bsw_stubs_INCLUDE += $(bsw_stubs_PATH)/MemIf/inc
bsw_stubs_INCLUDE += $(bsw_stubs_PATH)/AsrGnrl/inc
bsw_stubs_INCLUDE += $(bsw_stubs_PATH)/CanIf/inc
bsw_stubs_INCLUDE += $(bsw_stubs_PATH)/WdgIf/inc
bsw_stubs_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export bsw_stubs_SOCLIST
bsw_stubs_$(SOC)_CORELIST = $(mcusw_mcal_default_$(SOC)_CORELIST)
export bsw_stubs_$(SOC)_CORELIST
mcusw_mcal_LIB_LIST += bsw_stubs

# example utilities
app_utils_stubs_COMP_LIST = app_utils
app_utils_RELPATH = mcal/examples/utils
app_utils_PATH = $(mcal_PATH)/examples/utils
app_utils_MAKEFILE = -fmakefile
export app_utils_MAKEFILE
app_utils_BOARD_DEPENDENCY = yes
app_utils_CORE_DEPENDENCY = yes
export app_utils_COMP_LIST
export app_utils_BOARD_DEPENDENCY
export app_utils_CORE_DEPENDENCY
export app_utils_PATH
app_utils_PKG_LIST = app_utils
export app_utils_PKG_LIST
app_utils_INCLUDE = $(app_utils_PATH)
app_utils_SOCLIST = $(mcusw_mcal_default_SOCLIST)
export app_utils_SOCLIST
app_utils_$(SOC)_CORELIST = $(mcusw_mcal_default_$(SOC)_CORELIST)
export app_utils_$(SOC)_CORELIST
mcusw_APP_LIB_LIST += app_utils

export mcusw_mcal_LIB_LIST
export mcusw_APP_LIB_LIST

#
# MCAL Examples
#

# DIO app
dio_app_COMP_LIST = dio_app
dio_app_RELPATH = mcal/examples/Dio/dio_app
dio_app_PATH = $(mcal_PATH)/examples/Dio/dio_app
dio_app_BOARD_DEPENDENCY = yes
dio_app_CORE_DEPENDENCY = no
export dio_app_COMP_LIST
export dio_app_BOARD_DEPENDENCY
export dio_app_CORE_DEPENDENCY
dio_app_PKG_LIST = dio_app
dio_app_INCLUDE = $(dio_app_PATH)
dio_app_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export dio_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
dio_app_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export dio_app_$(SOC)_CORELIST
dio_app_SBL_APPIMAGEGEN = yes
export dio_app_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += dio_app

# ICU app
icu_app_COMP_LIST = icu_app
icu_app_RELPATH = mcal/examples/Icu/icu_app
icu_app_PATH = $(mcal_PATH)/examples/Icu/icu_app
icu_app_BOARD_DEPENDENCY = yes
icu_app_CORE_DEPENDENCY = yes
export icu_app_COMP_LIST
export icu_app_BOARD_DEPENDENCY
export icu_app_CORE_DEPENDENCY
icu_app_PKG_LIST = icu_app
icu_app_INCLUDE = $(icu_app_PATH)
icu_app_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export icu_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
icu_app_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export icu_app_$(SOC)_CORELIST
icu_app_SBL_APPIMAGEGEN = yes
export icu_app_SBL_APPIMAGEGEN
icu_app_MAKEFILE = autosarConfigSrc_PATH:=${icu_app_PATH}
export icu_app_MAKEFILE
mcusw_mcal_dup_EXAMPLE_LIST += icu_app

# FLS app
fls_app_COMP_LIST = fls_app
fls_app_RELPATH = mcal/examples/Fls/fls_app
fls_app_PATH = $(mcal_PATH)/examples/Fls/fls_app
fls_app_BOARD_DEPENDENCY = yes
fls_app_CORE_DEPENDENCY = no
export fls_app_COMP_LIST
export fls_app_BOARD_DEPENDENCY
export fls_app_CORE_DEPENDENCY
fls_app_PKG_LIST = fls_app
fls_app_INCLUDE = $(fls_app_PATH)
fls_app_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
fls_app_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export fls_app_$(SOC)_CORELIST
fls_app_SBL_APPIMAGEGEN = yes
export fls_app_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += fls_app

# FLS DAC app
fls_app_dac_COMP_LIST = fls_app_dac
fls_app_RELPATH = mcal/examples/Fls/fls_app_dac
fls_app_dac_PATH = $(mcal_PATH)/examples/Fls/fls_app_dac
fls_app_dac_BOARD_DEPENDENCY = yes
fls_app_dac_CORE_DEPENDENCY = no
export fls_app_dac_COMP_LIST
export fls_app_dac_BOARD_DEPENDENCY
export fls_app_dac_CORE_DEPENDENCY
fls_app_dac_PKG_LIST = fls_app_dac
fls_app_dac_INCLUDE = $(fls_app_dac_PATH)
fls_app_dac_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export fls_app_dac_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
fls_app_dac_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export fls_app_dac_$(SOC)_CORELIST
fls_app_dac_SBL_APPIMAGEGEN = yes
export fls_app_dac_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += fls_app_dac

# FLS INDAC app
fls_app_indac_COMP_LIST = fls_app_indac
fls_app_RELPATH = mcal/examples/Fls/fls_app_indac
fls_app_indac_PATH = $(mcal_PATH)/examples/Fls/fls_app_indac
fls_app_indac_BOARD_DEPENDENCY = yes
fls_app_indac_CORE_DEPENDENCY = no
export fls_app_indac_COMP_LIST
export fls_app_indac_BOARD_DEPENDENCY
export fls_app_indac_CORE_DEPENDENCY
fls_app_indac_PKG_LIST = fls_app_indac
fls_app_indac_INCLUDE = $(fls_app_indac_PATH)
fls_app_indac_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export fls_app_indac_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
fls_app_indac_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export fls_app_indac_$(SOC)_CORELIST
fls_app_indac_SBL_APPIMAGEGEN = yes
export fls_app_indac_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += fls_app_indac

# FLS XIP app
fls_app_xip_COMP_LIST = fls_app_xip
fls_app_RELPATH = mcal/examples/Fls/fls_app_xip
fls_app_xip_PATH = $(mcal_PATH)/examples/Fls/fls_app_xip
fls_app_xip_BOARD_DEPENDENCY = yes
fls_app_xip_CORE_DEPENDENCY = no
export fls_app_xip_COMP_LIST
export fls_app_xip_BOARD_DEPENDENCY
export fls_app_xip_CORE_DEPENDENCY
fls_app_xip_PKG_LIST = fls_app_xip
fls_app_xip_INCLUDE = $(fls_app_xip_PATH)
fls_app_xip_BOARDLIST = j721e_evm j7200_evm
export fls_app_xip_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm))
fls_app_xip_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export fls_app_xip_$(SOC)_CORELIST
fls_app_xip_SBL_APPIMAGEGEN = yes
export fls_app_xip_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += fls_app_xip

# FLS xip
fls_xip_COMP_LIST = fls_xip
fls_xip_RELPATH = mcal/examples/Fls/fls_xip
fls_xip_PATH = $(mcal_PATH)/examples/Fls/fls_xip
fls_xip_BOARD_DEPENDENCY = yes
fls_xip_CORE_DEPENDENCY = no
export fls_xip_COMP_LIST
export fls_xip_BOARD_DEPENDENCY
export fls_xip_CORE_DEPENDENCY
fls_xip_PKG_LIST = fls_xip
fls_xip_INCLUDE = $(fls_xip_PATH)
fls_xip_BOARDLIST = j721e_evm j7200_evm
export fls_xip_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm))
fls_xip_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export fls_xip_$(SOC)_CORELIST
fls_xip_SBL_APPIMAGEGEN = yes
fls_xip_SBL_APP_BINIMAGEGEN = yes
export fls_xip_SBL_APPIMAGEGEN
export fls_xip_SBL_APP_BINIMAGEGEN
fls_xip_SBL_APP_BIN_SECTIONS = --only-section .rstvectors --only-section .text --only-section .sbl_mcu_1_0_resetvector
mcusw_mcal_EXAMPLE_LIST += fls_xip

# MCSPI app
mcspi_app_COMP_LIST = mcspi_app
mcspi_app_RELPATH = mcal/examples/Spi/mcspi_app
mcspi_app_PATH = $(mcal_PATH)/examples/Spi/mcspi_app
mcspi_app_BOARD_DEPENDENCY = yes
mcspi_app_CORE_DEPENDENCY = no
export mcspi_app_COMP_LIST
export mcspi_app_BOARD_DEPENDENCY
export mcspi_app_CORE_DEPENDENCY
mcspi_app_PKG_LIST = mcspi_app
mcspi_app_INCLUDE = $(mcspi_app_PATH)
mcspi_app_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export mcspi_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
mcspi_app_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export mcspi_app_$(SOC)_CORELIST
mcspi_app_SBL_APPIMAGEGEN = yes
export mcspi_app_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += mcspi_app

# Gpt app
gpt_app_COMP_LIST = gpt_app
gpt_app_RELPATH = mcal/examples/Gpt
gpt_app_PATH = $(mcal_PATH)/examples/Gpt
gpt_app_BOARD_DEPENDENCY = yes
gpt_app_CORE_DEPENDENCY = no
export gpt_app_COMP_LIST
export gpt_app_BOARD_DEPENDENCY
export gpt_app_CORE_DEPENDENCY
gpt_app_PKG_LIST = gpt_app
gpt_app_INCLUDE = $(gpt_app_PATH)
gpt_app_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export gpt_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
gpt_app_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export gpt_app_$(SOC)_CORELIST
gpt_app_SBL_APPIMAGEGEN = yes
export gpt_app_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += gpt_app

# Mcu app
mcu_app_COMP_LIST = mcu_app
mcu_app_RELPATH = mcal/examples/Mcu
mcu_app_PATH = $(mcal_PATH)/examples/Mcu
mcu_app_BOARD_DEPENDENCY = yes
mcu_app_CORE_DEPENDENCY = no
export mcu_app_COMP_LIST
export mcu_app_BOARD_DEPENDENCY
export mcu_app_CORE_DEPENDENCY
mcu_app_PKG_LIST = mcu_app
mcu_app_INCLUDE = $(mcu_app_PATH)
mcu_app_BOARDLIST = j721e_sim j721e_evm j7200_evm j721s2_evm j784s4_evm
export mcu_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
mcu_app_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export mcu_app_$(SOC)_CORELIST
mcu_app_SBL_APPIMAGEGEN = yes
export mcu_app_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += mcu_app

# ETH test app
eth_app_COMP_LIST = eth_app
eth_app_RELPATH = mcal/examples/Eth/eth_app/target
eth_app_PATH = $(mcal_PATH)/examples/Eth/eth_app/target
eth_app_BOARD_DEPENDENCY = yes
eth_app_CORE_DEPENDENCY = no
export eth_app_COMP_LIST
export eth_app_BOARD_DEPENDENCY
export eth_app_CORE_DEPENDENCY
eth_app_PKG_LIST = eth_app
eth_app_INCLUDE = $(eth_app_PATH)
eth_app_BOARDLIST = j721e_evm j7200_evm j721s2_evm j784s4_evm
export eth_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
eth_app_$(SOC)_CORELIST = mcu1_0
endif
export eth_app_$(SOC)_CORELIST
eth_app_SBL_APPIMAGEGEN = yes
export eth_app_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += eth_app

# ETH virtual mac test app
eth_virtmac_app_COMP_LIST = eth_virtmac_app
eth_virtmac_app_RELPATH = mcal/examples/Eth/eth_app/target
eth_virtmac_app_PATH = $(mcal_PATH)/examples/Eth/eth_app/target
eth_virtmac_app_BOARD_DEPENDENCY = yes
eth_virtmac_app_CORE_DEPENDENCY = no
export eth_virtmac_app_COMP_LIST
export eth_virtmac_app_BOARD_DEPENDENCY
export eth_virtmac_app_CORE_DEPENDENCY
eth_virtmac_app_PKG_LIST = eth_virtmac_app
eth_virtmac_app_INCLUDE = $(eth_virtmac_app_PATH)
eth_virtmac_app_BOARDLIST = j721e_sim j721e_evm j7200_evm j784s4_evm
export eth_virtmac_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j784s4_evm))
eth_virtmac_app_$(SOC)_CORELIST = mcu2_1
endif
export eth_virtmac_app_$(SOC)_CORELIST
eth_virtmac_app_SBL_APPIMAGEGEN = yes
export eth_virtmac_app_SBL_APPIMAGEGEN
eth_virtmac_app_MAKEFILE = -fmakeethvirtmac autosarConfigSrc_PATH:=${eth_virtmac_app_PATH}
export eth_virtmac_app_MAKEFILE
mcusw_mcal_EXAMPLE_LIST += eth_virtmac_app

# CAN app
can_app_COMP_LIST = can_app
can_app_RELPATH = mcal/examples/Can
can_app_PATH = $(mcal_PATH)/examples/Can
can_app_BOARD_DEPENDENCY = yes
can_app_CORE_DEPENDENCY = no
export can_app_COMP_LIST
export can_app_BOARD_DEPENDENCY
export can_app_CORE_DEPENDENCY
can_app_PKG_LIST = can_app
can_app_INCLUDE = $(can_app_PATH)
can_app_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export can_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
can_app_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export can_app_$(SOC)_CORELIST
can_app_SBL_APPIMAGEGEN = yes
export can_app_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += can_app

# WDG app
wdg_app_COMP_LIST = wdg_app
wdg_app_RELPATH = mcal/examples/Wdg
wdg_app_PATH = $(mcal_PATH)/examples/Wdg
wdg_app_BOARD_DEPENDENCY = yes
wdg_app_CORE_DEPENDENCY = no
export wdg_app_COMP_LIST
export wdg_app_BOARD_DEPENDENCY
export wdg_app_CORE_DEPENDENCY
wdg_app_PKG_LIST = wdg_app
wdg_app_INCLUDE = $(wdg_app_PATH)
wdg_app_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export wdg_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
wdg_app_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export wdg_app_$(SOC)_CORELIST
wdg_app_SBL_APPIMAGEGEN = yes
export wdg_app_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += wdg_app

# PWM app
pwm_app_COMP_LIST = pwm_app
pwm_app_RELPATH = mcal/examples/Pwm/PwmApp_Gpt
pwm_app_PATH = $(mcal_PATH)/examples/Pwm/PwmApp_Gpt
pwm_app_BOARD_DEPENDENCY = yes
pwm_app_CORE_DEPENDENCY = no
export pwm_app_COMP_LIST
export pwm_app_BOARD_DEPENDENCY
export pwm_app_CORE_DEPENDENCY
pwm_app_PKG_LIST = pwm_app
pwm_app_INCLUDE = $(pwm_app_PATH)
pwm_app_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export pwm_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
pwm_app_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export pwm_app_$(SOC)_CORELIST
pwm_app_SBL_APPIMAGEGEN = yes
export pwm_app_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += pwm_app

# PWM EPWM app
pwm_app_epwm_COMP_LIST = pwm_app_epwm
pwm_app_epwm_RELPATH = mcal/examples/Pwm/PwmApp_Epwm
pwm_app_epwm_PATH = $(mcal_PATH)/examples/Pwm/PwmApp_Epwm
pwm_app_epwm_BOARD_DEPENDENCY = yes
pwm_app_epwm_CORE_DEPENDENCY = no
export pwm_app_epwm_COMP_LIST
export pwm_app_epwm_BOARD_DEPENDENCY
export pwm_app_epwm_CORE_DEPENDENCY
pwm_app_epwm_PKG_LIST = pwm_app_epwm
pwm_app_epwm_INCLUDE = $(pwm_app_epwm_PATH)
pwm_app_epwm_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export pwm_app_epwm_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
pwm_app_epwm_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export pwm_app_epwm_$(SOC)_CORELIST
pwm_app_epwm_SBL_APPIMAGEGEN = yes
export pwm_app_epwm_SBL_APPIMAGEGEN
pwm_app_epwm_MAKEFILE = autosarConfigSrc_PATH:=${pwm_app_epwm_PATH}
export pwm_app_epwm_MAKEFILE
mcusw_mcal_dup_EXAMPLE_LIST += pwm_app_epwm

# ADC app
adc_app_COMP_LIST = adc_app
adc_app_RELPATH = mcal/examples/Adc
adc_app_PATH = $(mcal_PATH)/examples/Adc
adc_app_BOARD_DEPENDENCY = yes
adc_app_CORE_DEPENDENCY = no
export adc_app_COMP_LIST
export adc_app_BOARD_DEPENDENCY
export adc_app_CORE_DEPENDENCY
adc_app_PKG_LIST = adc_app
adc_app_INCLUDE = $(adc_app_PATH)
adc_app_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export adc_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
adc_app_$(SOC)_CORELIST = mcu1_0 mcu2_1
endif
export adc_app_$(SOC)_CORELIST
adc_app_SBL_APPIMAGEGEN = yes
export adc_app_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += adc_app

# CDD IPC app
cdd_ipc_app_COMP_LIST = cdd_ipc_app
cdd_ipc_app_RELPATH = mcal/examples/CddIpc
cdd_ipc_app_PATH = $(mcal_PATH)/examples/CddIpc
cdd_ipc_app_BOARD_DEPENDENCY = yes
cdd_ipc_app_CORE_DEPENDENCY = no
export cdd_ipc_app_COMP_LIST
export cdd_ipc_app_BOARD_DEPENDENCY
export cdd_ipc_app_CORE_DEPENDENCY
cdd_ipc_app_PKG_LIST = cdd_ipc_app
cdd_ipc_app_INCLUDE = $(cdd_ipc_app_PATH)
cdd_ipc_app_BOARDLIST = $(mcusw_mcal_default_BOARDLIST)
export cdd_ipc_app_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm j784s4_evm))
cdd_ipc_app_$(SOC)_CORELIST = mcu2_1
endif
export cdd_ipc_app_$(SOC)_CORELIST
cdd_ipc_app_SBL_APPIMAGEGEN = yes
export cdd-ipc_app_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += cdd_ipc_app

# CddIpcApp_1remote_2chnls app
cdd_ipc_app_1remote_2chnls_COMP_LIST = cdd_ipc_app_1remote_2chnls
cdd_ipc_app_1remote_2chnls_RELPATH = mcal/examples/CddIpc/CddIpcApp_1remote_2chnls
cdd_ipc_app_1remote_2chnls_PATH = $(mcal_PATH)/examples/CddIpc/CddIpcApp_1remote_2chnls
cdd_ipc_app_1remote_2chnls_BOARD_DEPENDENCY = yes
cdd_ipc_app_1remote_2chnls_CORE_DEPENDENCY = no
export cdd_ipc_app_1remote_2chnls_COMP_LIST
export cdd_ipc_app_1remote_2chnls_BOARD_DEPENDENCY
export cdd_ipc_app_1remote_2chnls_CORE_DEPENDENCY
cdd_ipc_app_1remote_2chnls_PKG_LIST = cdd_ipc_app_1remote_2chnls
cdd_ipc_app_1remote_2chnls_INCLUDE = $(cdd_ipc_app_1remote_2chnls_PATH)
cdd_ipc_app_1remote_2chnls_BOARDLIST = j721e_sim j721e_evm j7200_evm j721s2_evm
export cdd_ipc_app_1remote_2chnls_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm j721s2_evm))
cdd_ipc_app_1remote_2chnls_$(SOC)_CORELIST = mcu2_1
endif
export cdd_ipc_app_1remote_2chnls_$(SOC)_CORELIST
cdd_ipc_app_1remote_2chnls_SBL_APPIMAGEGEN = yes
export cdd_ipc_app_1remote_2chnls_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += cdd_ipc_app_1remote_2chnls


# CDD IPC app with Linux Remote Core
cdd_ipc_app_rc_linux_COMP_LIST = cdd_ipc_app_rc_linux
cdd_ipc_app_rc_linux_RELPATH = mcal/examples/CddIpcRProcLinux
cdd_ipc_app_rc_linux_PATH = $(mcal_PATH)/examples/CddIpcRProcLinux
cdd_ipc_app_rc_linux_BOARD_DEPENDENCY = yes
cdd_ipc_app_rc_linux_CORE_DEPENDENCY = no
export cdd_ipc_app_rc_linux_COMP_LIST
export cdd_ipc_app_rc_linux_BOARD_DEPENDENCY
export cdd_ipc_app_rc_linux_CORE_DEPENDENCY
cdd_ipc_app_rc_linux_PKG_LIST = cdd_ipc_app_rc_linux
cdd_ipc_app_rc_linux_INCLUDE = $(cdd_ipc_app_rc_linux_PATH)
cdd_ipc_app_rc_linux_BOARDLIST = j721e_evm j7200_evm
export cdd_ipc_app_rc_linux_BOARDLIST
ifeq ($(BOARD),$(filter $(BOARD), j721e_evm j7200_evm))
cdd_ipc_app_rc_linux_$(SOC)_CORELIST = mcu2_1
endif
export cdd_ipc_app_rc_linux_$(SOC)_CORELIST
cdd_ipc_app_rc_linux_SBL_APPIMAGEGEN = yes
export cdd-ipc_app_rc_linux_SBL_APPIMAGEGEN
mcusw_mcal_EXAMPLE_LIST += cdd_ipc_app_rc_linux


# Final list of application supported
export mcusw_mcal_EXAMPLE_LIST
export mcusw_mcal_dup_EXAMPLE_LIST

mcusw_mcal_component_make_include := 1
endif
