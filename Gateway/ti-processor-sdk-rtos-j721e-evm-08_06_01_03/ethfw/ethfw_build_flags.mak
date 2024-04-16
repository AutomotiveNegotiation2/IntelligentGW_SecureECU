
ifndef $(ETHFW_BUILD_FLAGS_MAK)
ETHFW_BUILD_FLAGS_MAK = 1

#Build log flags
NO_BANNER?=1

BUILD_TARGET_MODE?=yes
BUILD_EMULATION_MODE?=no
# valid values: X86 x86_64 all
BUILD_EMULATION_ARCH?=x86_64

# Build specific CPUs
BUILD_CPU_MPU1?=no
BUILD_CPU_MCU1_0?=no
BUILD_CPU_MCU2_0?=yes
BUILD_CPU_MCU3_0?=no
BUILD_CPU_C6x_1?=no
BUILD_CPU_C6x_2?=no
BUILD_CPU_C7x_1?=no
BUILD_CPU_MCU1_1?=no
BUILD_CPU_MCU2_1?=yes
BUILD_CPU_MCU3_1?=no
BUILD_SOC_LIST ?= J721E J7200 J784S4
export BUILD_SOC_LIST
# Build FREERTOS only binaries
BUILD_APP_FREERTOS?=yes
BUILD_APP_SAFERTOS?=no
#Build Profile
PROFILE?=release

# A72 OS specific Build flag
BUILD_QNX_A72?=no

# Treat compiler warning as error
# Supported Values: 1 | 0
TREAT_WARNINGS_AS_ERROR ?= 1

# R5F Thumb mode
BUILD_R5F_THUMB?=yes

# Build a specific CPU type's based on CPU flags status defined above
ifneq (,$(filter yes,$(BUILD_CPU_MCU1_0) $(BUILD_CPU_MCU1_1) $(BUILD_CPU_MCU2_0) $(BUILD_CPU_MCU2_1) $(BUILD_CPU_MCU3_0) $(BUILD_CPU_MCU3_1)))
  ifeq ($(BUILD_R5F_THUMB),yes)
    BUILD_ISA_R5F=no
    BUILD_ISA_R5Ft=yes
  else
    BUILD_ISA_R5F=yes
    BUILD_ISA_R5Ft=no
  endif
else
  BUILD_ISA_R5F=no
  BUILD_ISA_R5Ft=no
endif

ifneq (,$(filter yes,$(BUILD_CPU_C6x_1) $(BUILD_CPU_C6x_2)))
  BUILD_ISA_C6x=yes
else
  BUILD_ISA_C6x=no
endif

ifneq (,$(filter yes,$(BUILD_CPU_C7x_1)))
  BUILD_ISA_C7x=yes
else
  BUILD_ISA_C7x=no
endif

ifneq (,$(filter yes,$(BUILD_CPU_MPU1)))
  BUILD_ISA_A72=yes
else
  BUILD_ISA_A72=no
endif

ifneq (,$(filter yes,$(BUILD_CPU_MPU1)))
  BUILD_ISA_A53=yes
else
  BUILD_ISA_A53=no
endif

# Proxy ARP handling support
# Supported Values: yes | no
ifneq (,$(filter yes,$(BUILD_CPU_MCU2_0)))
  ETHFW_PROXY_ARP_SUPPORT=yes
endif

# Inter-core virtual ethernet support
# Supported Values: yes | no
ifneq (,$(filter yes,$(BUILD_CPU_MCU2_0) $(BUILD_CPU_MCU2_1)))
  ifeq ($(BUILD_QNX_A72),yes)
    ETHFW_INTERCORE_ETH_SUPPORT?=no
  else
    ETHFW_INTERCORE_ETH_SUPPORT?=yes
  endif
endif

endif # ifndef $(ETHFW_BUILD_FLAGS_MAK)
