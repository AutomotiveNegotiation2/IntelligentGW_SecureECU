ifeq ($(BUILD_CPU_MCU2_0),yes)
ifeq ($(TARGET_CPU),R5F)

CPU_ID=mcu2_0

TARGET      := app_demo_device_client_example
TARGETTYPE  := exe

IDIRS       :=
IDIRS       += $(REMOTE_DEVICE_PATH)

CSOURCES    := main_rtos.c

ifeq ($(RTOS),FREERTOS)
	CSOURCES += ipc_trace.c
	ifeq ($(SOC),j721e)
		CSOURCES += j721e_mcu2_0_mpu_cfg.c
		LINKER_CMD_FILES +=  $($(_MODULE)_SDIR)/j721e_mcu2_0_freertos.lds
	endif
	ifeq ($(SOC),j7200)
		CSOURCES += j7200_mcu2_0_mpu_cfg.c
		LINKER_CMD_FILES +=  $($(_MODULE)_SDIR)/j7200_mcu2_0_freertos.lds
	endif
	ifeq ($(SOC),j721s2)
		CSOURCES += j721s2_mcu2_0_mpu_cfg.c
		LINKER_CMD_FILES +=  $($(_MODULE)_SDIR)/j721s2_mcu2_0_freertos.lds
	endif
	ifeq ($(SOC),j784s4)
		CSOURCES += j784s4_mcu2_0_mpu_cfg.c
		LINKER_CMD_FILES +=  $($(_MODULE)_SDIR)/j784s4_mcu2_0_freertos.lds
	endif
endif

LDIRS += $(PDK_PATH)/packages/ti/csl/lib/$(SOC)/r5f/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/ipc/lib/$(SOC)/$(CPU_ID)/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/sciclient/lib/$(SOC)/$(CPU_ID)/$(TARGET_BUILD)/
ifeq ($(RTOS),FREERTOS)
	LDIRS += $(PDK_PATH)/packages/ti/kernel/lib/$(SOC)/$(CPU_ID)/$(TARGET_BUILD)/
	LDIRS += $(PDK_PATH)/packages/ti/osal/lib/freertos/$(SOC)/r5f/$(TARGET_BUILD)/
endif

STATIC_LIBS += lib_remote_device_client

ADDITIONAL_STATIC_LIBS += ipc.aer5f
# osal_freertos and freertos libs have a cyclic dependency. osal_freertos lib needs to added twice to meet the cyclic dependency.
ADDITIONAL_STATIC_LIBS += ti.osal.aer5f
ADDITIONAL_STATIC_LIBS += sciclient.aer5f
ifeq ($(RTOS),FREERTOS)
	ADDITIONAL_STATIC_LIBS += ti.kernel.freertos.aer5f
	ADDITIONAL_STATIC_LIBS += ti.osal.aer5f
endif
ADDITIONAL_STATIC_LIBS += ti.csl.aer5f
ifeq ($(RTOS),FREERTOS)
	ADDITIONAL_STATIC_LIBS += ti.csl.init.aer5f
endif

DEFS        :=
ifeq ($(SOC),j721e)
DEFS        += SOC_J721E
endif
ifeq ($(SOC),j7200)
DEFS        += SOC_J7200
endif
ifeq ($(SOC),j721s2)
DEFS        += SOC_J721S2
endif
ifeq ($(SOC),j784s4)
DEFS        += SOC_J784S4
endif
DEFS        += BUILD_MCU2_0
DEFS        += A72_LINUX_OS
DEFS        += $(RTOS)

endif
endif

