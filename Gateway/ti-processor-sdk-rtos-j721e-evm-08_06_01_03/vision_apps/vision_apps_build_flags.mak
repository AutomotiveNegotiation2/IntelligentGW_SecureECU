
ifndef $(VISION_APPS_BUILD_FLAGS_MAK)
VISION_APPS_BUILD_FLAGS_MAK = 1

# Used to version control the tivision_apps.so and ipk files
PSDK_VERSION?=8.6.0

# Edit below file in tiovx/ to change additional build options
include $(TIOVX_PATH)/build_flags.mak

# Build specific CPUs
ifeq ($(SOC),j721e)
BUILD_CPU_MPU1?=yes
BUILD_CPU_MCU1_0?=no
BUILD_CPU_MCU2_0?=yes
BUILD_CPU_MCU2_1?=yes
BUILD_CPU_MCU3_0?=no
BUILD_CPU_MCU3_1?=no
BUILD_CPU_C6x_1?=yes
BUILD_CPU_C6x_2?=yes
BUILD_CPU_C7x_1?=yes
else ifeq ($(SOC),j721s2)
BUILD_CPU_MPU1?=yes
BUILD_CPU_MCU1_0?=no
BUILD_CPU_MCU2_0?=yes
BUILD_CPU_MCU2_1?=yes
BUILD_CPU_MCU3_0?=no
BUILD_CPU_MCU3_1?=no
BUILD_CPU_C7x_1?=yes
BUILD_CPU_C7x_2?=yes
else ifeq ($(SOC),j784s4)
BUILD_CPU_MPU1?=yes
BUILD_CPU_MCU1_0?=no
BUILD_CPU_MCU2_0?=yes
BUILD_CPU_MCU2_1?=yes
BUILD_CPU_MCU3_0?=yes
BUILD_CPU_MCU3_1?=yes
BUILD_CPU_MCU4_0?=yes
BUILD_CPU_MCU4_1?=yes
BUILD_CPU_C7x_1?=yes
BUILD_CPU_C7x_2?=yes
BUILD_CPU_C7x_3?=yes
BUILD_CPU_C7x_4?=yes
else ifeq ($(SOC),am62a)
BUILD_CPU_MPU1?=yes
BUILD_CPU_MCU1_0?=yes
BUILD_CPU_C7x_1?=yes
endif

BUILD_PTK?=yes

BUILD_ENABLE_ETHFW?=yes

# ETHFW is not supported in J721S2
ifneq (,$(filter $(SOC),j721s2 am62a))
BUILD_ENABLE_ETHFW=no
endif

ifeq ($(RTOS),SAFERTOS)
ifeq ($(SOC),j784s4)
BUILD_ENABLE_ETHFW=no
endif
endif

# Proxy ARP handling support
# To enable this feature, ETHFW_PROXY_ARP_SUPPORT must be set to "yes" in
# ethfw_build_flags.mk. This feature is enabled by default.

# Inter-core virtual ethernet support
# Supported Values: yes | no
ifneq (,$(filter yes,$(BUILD_CPU_MCU2_0)))
ifeq ($(BUILD_QNX_A72),yes)
ETHFW_INTERCORE_ETH_SUPPORT?=no
else
ETHFW_INTERCORE_ETH_SUPPORT?=yes
endif
endif

BUILD_EDGEAI?=no

# If set to no, then MCU core firmware will be built with NO board dependencies
# (such as I2C, board specific PINMUX, DSS, HDMI, I2C, ETHFW, CSIRX, CSITX).  Most of
# the packaged vision_apps require these interfaces on the MCU for the EVM, but
# when porting to a board other than an EVM, or using applications which control
# these interfaces from the HLOS on A72 (such as EdgeAI kit), then this should be set
# to 'no'.
BUILD_MCU_BOARD_DEPENDENCIES?=yes

ifeq ($(BUILD_EDGEAI), yes)
BUILD_MCU_BOARD_DEPENDENCIES=no
FIRMWARE_SUBFOLDER=vision_apps_eaik
UENV_NAME=uEnv_$(SOC)_edgeai_apps.txt
endif

ifeq ($(BUILD_MCU_BOARD_DEPENDENCIES),no)
BUILD_ENABLE_ETHFW=no
endif

# Need to export this variable so that the following xdc .cfg file can pick this up from the env:
# ${PSDK_PATH}/vision_apps/platform/$(SOC)/rtos/mcu2_0/mcu2_0.cfg
export BUILD_ENABLE_ETHFW

# Set to 'yes' to link all .out files against libtivision_apps.so instead of static libs
# (Only supported on A72, ignored on x86_64)
LINK_SHARED_OBJ?=yes

ifeq ($(SOC),j784s4)
ifeq ($(BUILD_QNX_A72),yes)
LINK_SHARED_OBJ=no
endif
endif

# Since MCU R5F runs in locked step mode in vision apps, dont set these to 'yes'
BUILD_CPU_MCU1_1?=no

# Build TI-RTOS fileio binaries
BUILD_APP_RTOS_FILEIO?=no

# Build RTOS + Linux binaries
BUILD_APP_RTOS_LINUX?=$(BUILD_LINUX_A72)

# Build RTOS + QNX binaries
BUILD_APP_RTOS_QNX?=$(BUILD_QNX_A72)

# PDK board to build for, valid values: j721e_sim j721e_evm j721s2_evm j784s4_evm am62a_evm
BUILD_PDK_BOARD=$(SOC)_evm

# Flag to build for an HS device. Signs the built remote proc firmware binaries
HS?=0

# Flag to select silicon revision: 2_0 for SR 2.0, 1_1 for SR 1.1, 1_0 for SR 1.0
HS_SR?=1_1
ifeq ($(SOC), $(filter $(SOC), j721s2 j784s4))
# Note: There is only SR 1.0 for J721S2 and J784S4 HS
HS_SR=1_0
endif


# when mcu2-1 build is enabled, mcu2-0 must also be built
ifeq ($(BUILD_CPU_MCU2_1),yes)
BUILD_CPU_MCU2_0=yes
endif

# Build a specific CPU type's based on CPU flags status defined above
ifneq (,$(filter yes,$(BUILD_CPU_MCU1_0) $(BUILD_CPU_MCU1_1) $(BUILD_CPU_MCU2_0) $(BUILD_CPU_MCU2_1) $(BUILD_CPU_MCU3_0) $(BUILD_CPU_MCU3_1)))
BUILD_ISA_R5F=yes
else
BUILD_ISA_R5F=no
endif
ifneq (,$(filter yes,$(BUILD_CPU_C6x_1) $(BUILD_CPU_C6x_2)))
BUILD_ISA_C6x=yes
else
BUILD_ISA_C6x=no
endif
ifneq (,$(filter yes,$(BUILD_CPU_C7x_1) $(BUILD_CPU_C7x_2) $(BUILD_CPU_C7x_3) $(BUILD_CPU_C7x_4)))
BUILD_ISA_C7x=yes
else
BUILD_ISA_C7x=no
endif
ifneq (,$(filter yes,$(BUILD_CPU_MPU1)))
BUILD_ISA_A72=yes
else
BUILD_ISA_A72=no
endif

endif # ifndef $(VISION_APPS_BUILD_FLAGS_MAK)
