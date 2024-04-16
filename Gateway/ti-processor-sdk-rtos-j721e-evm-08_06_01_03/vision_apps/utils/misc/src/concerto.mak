ifneq ($(TARGET_PLATFORM),PC)
ifeq ($(TARGET_OS),$(filter $(TARGET_OS),SYSBIOS FREERTOS SAFERTOS))

include $(PRELUDE)

TARGET      := app_utils_misc
TARGETTYPE  := library

ifeq ($(TARGET_CPU),$(filter $(TARGET_CPU),C71 C7120))
ASSEMBLY += app_c7x_init_asm.asm
CSOURCES += app_c7x_init.c
endif

ifeq ($(TARGET_OS),SYSBIOS)
CSOURCES += app_cpu_hz_tirtos.c
endif

ifeq ($(TARGET_OS),FREERTOS)
IDIRS    += $(PDK_PATH)/packages/ti/kernel/freertos/FreeRTOS-LTS/FreeRTOS-Kernel/include/
endif

ifeq ($(TARGET_OS),$(filter $(TARGET_OS),FREERTOS SAFERTOS))
CSOURCES += app_cpu_hz_freertos.c
endif

ifeq ($(TARGET_OS),SAFERTOS)
ifeq ($(TARGET_CPU),R5F)
IDIRS+=${SAFERTOS_KERNEL_INSTALL_PATH_r5f}/source_code_and_projects/SafeRTOS/config
endif
ifeq ($(TARGET_CPU),C66)
IDIRS+=${SAFERTOS_KERNEL_INSTALL_PATH_c66}/source_code_and_projects/SafeRTOS/config
endif
ifeq ($(TARGET_CPU),$(filter $(TARGET_CPU),C71 C7120 C7504))
IDIRS+=${SAFERTOS_KERNEL_INSTALL_PATH_c7x}/source_code_and_projects/SafeRTOS/config
endif
endif

ifeq ($(TARGET_CPU),$(filter $(TARGET_CPU),C71 C7120))
IDIRS    += $(PDK_PATH)/packages/ti/kernel/freertos/portable/TI_CGT/c7x
IDIRS    += $(PDK_PATH)/packages/ti/kernel/freertos/config/$(SOC)/c7x
IDIRS    += $(PDK_PATH)/packages/ti/csl/arch/c7x
endif

ifeq ($(TARGET_CPU),$(filter $(TARGET_CPU),C7504))
IDIRS    += $(PDK_PATH)/packages/ti/kernel/freertos/portable/TI_CGT/c75x
IDIRS    += $(PDK_PATH)/packages/ti/kernel/freertos/config/$(SOC)/c75x
IDIRS    += $(PDK_PATH)/packages/ti/csl/arch/c7x
endif

ifeq ($(TARGET_CPU),C66)
IDIRS    += $(PDK_PATH)/packages/ti/kernel/freertos/portable/TI_CGT/c66
IDIRS    += $(PDK_PATH)/packages/ti/kernel/freertos/config/$(SOC)/c66
endif

ifeq ($(TARGET_CPU),R5F)

IDIRS    += $(PDK_PATH)/packages/ti/kernel/freertos/portable/TI_CGT/r5f
IDIRS    += $(PDK_PATH)/packages/ti/kernel/freertos/config/$(SOC)/r5f

CSOURCES += app_r5f_init.c

CSOURCES += app_pinmux_$(SOC).c

DEFS+=$(BUILD_PDK_BOARD)

endif

CSOURCES += app_utils_task_init.c

include $(FINALE)

endif
endif
