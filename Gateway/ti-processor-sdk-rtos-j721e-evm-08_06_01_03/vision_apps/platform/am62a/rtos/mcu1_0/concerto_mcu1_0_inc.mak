DEFS+=CPU_mcu1_0
DEFS+=BUILD_MCU1_0
DEFS+=BUILD_MCU
DEFS+=VIM_DIRECT_REGISTRATION

# This enables ARM Thumb mode which reduces firmware size and enables faster boot
COPT +=--code_state=16

ifeq ($(RTOS),SYSBIOS)
	XDC_BLD_FILE = $($(_MODULE)_SDIR)/../bios_cfg/config_r5f.bld
	XDC_IDIRS    = $($(_MODULE)_SDIR)/../bios_cfg/
	XDC_CFG_FILE = $($(_MODULE)_SDIR)/mcu1_0.cfg
	XDC_PLATFORM = "ti.platforms.cortexR:J7ES_MCU"
	LINKER_CMD_FILES +=  $($(_MODULE)_SDIR)/linker.cmd
endif
ifeq ($(RTOS),FREERTOS)
	CSOURCES += $(SOC)_mpu_cfg.c
	LINKER_CMD_FILES +=  $($(_MODULE)_SDIR)/$(SOC)_linker_freertos.cmd
endif

LINKER_CMD_FILES +=  $($(_MODULE)_SDIR)/linker_mem_map.cmd

IDIRS+=$(VISION_APPS_PATH)/platform/$(SOC)/rtos

ifeq ($(RTOS),FREERTOS)
	LDIRS += $(PDK_PATH)/packages/ti/kernel/lib/$(SOC)/mcu1_0/$(TARGET_BUILD)/
endif

LDIRS += $(PDK_PATH)/packages/ti/drv/ipc/lib/$(SOC)/mcu1_0/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/mailbox/lib/$(SOC)/mcu1_0/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/udma/lib/$(SOC)/mcu1_0/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/sciclient/lib/$(SOC)/mcu1_0/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/vhwa/lib/$(SOC)/mcu1_0/$(TARGET_BUILD)/

include $($(_MODULE)_SDIR)/../concerto_r5f_inc.mak

# CPU instance specific libraries
STATIC_LIBS += app_rtos_common_mcu1_0

ifeq ($(RTOS),FREERTOS)
	STATIC_LIBS += app_rtos
endif

STATIC_LIBS += app_utils_hwa
STATIC_LIBS += app_utils_sciserver

ADDITIONAL_STATIC_LIBS += vhwa.aer5f
ADDITIONAL_STATIC_LIBS += sciclient_direct.aer5f
ADDITIONAL_STATIC_LIBS += sciserver_tirtos.aer5f
ADDITIONAL_STATIC_LIBS += mailbox.aer5f
ADDITIONAL_STATIC_LIBS += rm_pm_hal.aer5f
ADDITIONAL_STATIC_LIBS += self_reset.aer5f

DEFS        += $(RTOS)
