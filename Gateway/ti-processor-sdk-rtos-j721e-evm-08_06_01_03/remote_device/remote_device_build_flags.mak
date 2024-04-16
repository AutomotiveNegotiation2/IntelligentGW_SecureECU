ifndef $(REMOTE_DEVICE_BUILD_FLAGS_MAK)
REMOTE_DEVICE_BUILD_FLAGS_MAK = 1

# BOARD and SOC selection
SOC?=j721e

ifeq ($(SOC),j721e)
BOARD=j721e_evm
TARGET_SOC=J721E
endif
ifeq ($(SOC),j7200)
BOARD=j7200_evm
TARGET_SOC=J7200
endif
ifeq ($(SOC),j721s2)
BOARD=j721s2_evm
TARGET_SOC=J721S2
endif
ifeq ($(SOC),j784s4)
BOARD=j784s4_evm
TARGET_SOC=J784S4
endif

# Build specific CPUs
BUILD_CPU_MCU1_0?=yes
BUILD_CPU_MCU2_0?=yes
BUILD_CPU_MCU3_0?=yes
BUILD_CPU_MCU1_1?=yes
BUILD_CPU_MCU2_1?=yes
BUILD_CPU_MCU3_1?=yes

# Build a specific CPU type's based on CPU flags status defined above
ifneq (,$(filter yes,$(BUILD_CPU_MCU1_0) $(BUILD_CPU_MCU1_1) $(BUILD_CPU_MCU2_0) $(BUILD_CPU_MCU2_1) $(BUILD_CPU_MCU3_0) $(BUILD_CPU_MCU3_1)))
BUILD_ISA_R5F=yes
else
BUILD_ISA_R5F=no
endif

# RTOS selection - FREERTOS or SAFERTOS
RTOS?=FREERTOS

endif # ifndef $(REMOTE_DEVICE_BUILD_FLAGS_MAK)
