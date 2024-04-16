ifeq ($(TARGET_CPU),R5Ft)
    TARGET_CPU_FOLDER := r5f
    REMOTE_DEVICE_TARGET_CPU := R5F
else
    TARGET_CPU_FOLDER := $(call lowercase,$(TARGET_CPU))
    REMOTE_DEVICE_TARGET_CPU := $(TARGET_CPU)
endif

TARGET_SOC_FOLDER := $(call lowercase,$(TARGET_PLATFORM))
TARGET_BOARD_FOLDER := $(call lowercase,${$(TARGET_PLATFORM)_BOARD})
CPU_ID_FOLDER       := $(strip $(if $(filter $(call lowercase,${CPU_ID}),mpu1),mpu1_0,$(call lowercase,${CPU_ID})))
TARGET_OS_LC        := $(call lowercase,$(TARGET_OS))

DEFS+=CPU_$(CPU_ID)

ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
    IDIRS += $(PDK_PATH)/packages/ti/transport/lwip/lwip-stack/src/include
    IDIRS += $(PDK_PATH)/packages/ti/transport/lwip/lwip-port/${TARGET_OS_LC}/include
endif
ifeq ($(TARGET_OS),SAFERTOS)
    ifeq ($(TARGET_PLATFORM),J721E)
        SAFERTOS_KERNEL_INSTALL_PATH_r5f = ${SAFERTOS_KERNEL_INSTALL_PATH_r5f_J721E}
    else ifeq ($(TARGET_PLATFORM),J7200)
        SAFERTOS_KERNEL_INSTALL_PATH_r5f = ${SAFERTOS_KERNEL_INSTALL_PATH_r5f_J7200}
    else ifeq ($(TARGET_PLATFORM),J784S4)
        SAFERTOS_KERNEL_INSTALL_PATH_r5f = ${SAFERTOS_KERNEL_INSTALL_PATH_r5f_J784S4}
    endif

    IDIRS += ${SAFERTOS_KERNEL_INSTALL_PATH_r5f}/source_code_and_projects/SafeRTOS/api/$(SAFERTOS_ISA_EXT_r5f)
    IDIRS += ${SAFERTOS_KERNEL_INSTALL_PATH_r5f}/source_code_and_projects/SafeRTOS/api/PrivWrapperStd
    IDIRS += ${SAFERTOS_KERNEL_INSTALL_PATH_r5f}/source_code_and_projects/SafeRTOS/config
    IDIRS += ${SAFERTOS_KERNEL_INSTALL_PATH_r5f}/source_code_and_projects/SafeRTOS/kernel/include_api
    IDIRS += ${SAFERTOS_KERNEL_INSTALL_PATH_r5f}/source_code_and_projects/SafeRTOS/kernel/include_prv
    IDIRS += ${SAFERTOS_KERNEL_INSTALL_PATH_r5f}/source_code_and_projects/SafeRTOS/portable/$(SAFERTOS_ISA_EXT_r5f)
    IDIRS += ${SAFERTOS_KERNEL_INSTALL_PATH_r5f}/source_code_and_projects/SafeRTOS/portable/$(SAFERTOS_ISA_EXT_r5f)/$(SAFERTOS_COMPILER_EXT_r5f)
endif
ifeq ($(TARGET_OS),FREERTOS)
    IDIRS += $(PDK_PATH)/packages/ti/kernel/freertos/portable/TI_CGT/${TARGET_CPU_FOLDER}
    IDIRS += $(PDK_PATH)/packages/ti/kernel/freertos/config/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}
    IDIRS += $(PDK_PATH)/packages/ti/kernel/freertos/FreeRTOS-LTS/FreeRTOS-Kernel/include
endif
IDIRS += $(PDK_PATH)/packages
IDIRS += $(REMOTE_DEVICE_PATH)
IDIRS += $(ETHFW_PATH)

ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
    LDIRS += $(PDK_PATH)/packages/ti/osal/lib/${TARGET_OS_LC}/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
    LDIRS += $(PDK_PATH)/packages/ti/transport/lwip/lwip-stack/lib/${TARGET_OS_LC}/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
    LDIRS += $(PDK_PATH)/packages/ti/transport/lwip/lwip-contrib/lib/${TARGET_OS_LC}/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
    LDIRS += $(PDK_PATH)/packages/ti/transport/lwip/lwip-port/lib/${TARGET_OS_LC}/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
endif

ifeq ($(TARGET_OS),FREERTOS)
    LDIRS += $(PDK_PATH)/packages/ti/kernel/lib/${TARGET_SOC_FOLDER}/${CPU_ID_FOLDER}/$(TARGET_BUILD)
else ifeq ($(TARGET_OS),SAFERTOS)
    LDIRS += $(PDK_PATH)/packages/ti/kernel/safertos/lib/${TARGET_SOC_FOLDER}/${CPU_ID_FOLDER}/$(TARGET_BUILD)
endif

LDIRS += $(PDK_PATH)/packages/ti/csl/lib/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/board/lib/${TARGET_BOARD_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/i2c/lib/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/uart/lib/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/gpio/lib/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/enet/lib/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/enet/lib/${TARGET_SOC_FOLDER}/${CPU_ID_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/enet/lib/${TARGET_BOARD_FOLDER}/${CPU_ID_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/enet/lib/${TARGET_OS_LC}/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/enet/lib/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/udma/lib/${TARGET_SOC_FOLDER}/${CPU_ID_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/sciclient/lib/${TARGET_SOC_FOLDER}/${CPU_ID_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/pm/lib/${TARGET_SOC_FOLDER}/${TARGET_CPU_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(PDK_PATH)/packages/ti/drv/ipc/lib/${TARGET_SOC_FOLDER}/${CPU_ID_FOLDER}/$(TARGET_BUILD)/
LDIRS += $(REMOTE_DEVICE_PATH)/out/${TARGET_PLATFORM}/${REMOTE_DEVICE_TARGET_CPU}/${TARGET_OS}/$(TARGET_BUILD)/

STATIC_LIBS += app_utils_console_io
STATIC_LIBS += app_utils_mem
STATIC_LIBS += app_ethfw_stats
STATIC_LIBS += app_remote_service
STATIC_LIBS += app_perf_stats

ifneq (,$(filter ${TARGET_CPU},R5F R5Ft))
    # Same extension is kept for R5F or R5Ft (Thumb mode)
    # in PDK build system for backwards compatibility reasons
    TARGET_CPU_SUFFIX=r5f
    ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
        ADDITIONAL_STATIC_LIBS += enet_cfgserver_${TARGET_OS_LC}.ae$(TARGET_CPU_SUFFIX)
    endif
    ADDITIONAL_STATIC_LIBS += enet_timesync_ptp.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += enet_timesync_hal.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += $(ENET_APPUTILS_LIB).ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += enetsoc.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += enet.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += enetphy.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += ti.board.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += udma.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += ipc.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += sciclient.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += ti.drv.i2c.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += ti.drv.uart.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += ti.drv.gpio.ae$(TARGET_CPU_SUFFIX)
    ADDITIONAL_STATIC_LIBS += pm_lib.ae$(TARGET_CPU_SUFFIX)
    ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
        ADDITIONAL_STATIC_LIBS += lwipstack_${TARGET_OS_LC}.ae$(TARGET_CPU_SUFFIX)
        ADDITIONAL_STATIC_LIBS += lwipcontrib_${TARGET_OS_LC}.ae$(TARGET_CPU_SUFFIX)
        ADDITIONAL_STATIC_LIBS += lwipport_${TARGET_OS_LC}.ae$(TARGET_CPU_SUFFIX)
        ADDITIONAL_STATIC_LIBS += lwipif_${TARGET_OS_LC}.ae$(TARGET_CPU_SUFFIX)
        ADDITIONAL_STATIC_LIBS += lwipific_${TARGET_OS_LC}.ae$(TARGET_CPU_SUFFIX)
        ADDITIONAL_STATIC_LIBS += enet_intercore.ae$(TARGET_CPU_SUFFIX)
    endif

    # osal_freertos and freertos libs have a cyclic dependency. osal_freertos lib needs to added twice to meet the cyclic dependency.
    ADDITIONAL_STATIC_LIBS += ti.osal.ae$(TARGET_CPU_SUFFIX)
    ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
        ADDITIONAL_STATIC_LIBS += ti.kernel.${TARGET_OS_LC}.ae$(TARGET_CPU_SUFFIX)
        ADDITIONAL_STATIC_LIBS += ti.osal.ae$(TARGET_CPU_SUFFIX)
    endif

    ADDITIONAL_STATIC_LIBS += ti.csl.ae$(TARGET_CPU_SUFFIX)
    ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
        ADDITIONAL_STATIC_LIBS += ti.csl.init.ae$(TARGET_CPU_SUFFIX)
    endif
else
    CORTEX_A_LIB_SUFFIX := $(if $(filter $(TARGET_BUILD),debug),g,)
    ifneq (,$(filter ${TARGET_CPU},A72 A53))
        ADDITIONAL_STATIC_LIBS += ti.board.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += nimuenet.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += enet_timesync_hal.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += enet_timesync_ptp.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += $(ENET_APPUTILS_LIB).a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += enet.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += udma.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += ipc.ae$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += sciclient.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += ti.drv.i2c.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += ti.drv.uart.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += ti.drv.gpio.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += ti.csl.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += ti.osal.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
        ADDITIONAL_STATIC_LIBS += pm_lib.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
    endif
    ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
        ADDITIONAL_STATIC_LIBS += enet_cfgserver_${TARGET_OS_LC}.a$(call lowercase,$(TARGET_CPU))f$(CORTEX_A_LIB_SUFFIX)
    endif
endif


PDK_SOC_LIST += $(TARGET_PLATFORM)
PDK_LIB_RULES += i2c
PDK_LIB_RULES += pm_lib
ifneq ($(filter $(TARGET_OS),FREERTOS SAFERTOS),)
    PDK_LIB_RULES += osal_${TARGET_OS_LC}
    PDK_LIB_RULES += ${TARGET_OS_LC}
    PDK_LIB_RULES += lwipstack_${TARGET_OS_LC}
    PDK_LIB_RULES += lwipcontrib_${TARGET_OS_LC}
    PDK_LIB_RULES += lwipport_${TARGET_OS_LC}
    PDK_LIB_RULES += lwipif_${TARGET_OS_LC}
    PDK_LIB_RULES += lwipific_${TARGET_OS_LC}
    PDK_LIB_RULES += enet_cfgserver_${TARGET_OS_LC}
    PDK_LIB_RULES += enet_intercore
endif
PDK_LIB_RULES += udma
PDK_LIB_RULES += csl
PDK_LIB_RULES += sciclient
PDK_LIB_RULES += enet
PDK_LIB_RULES += enetsoc
PDK_LIB_RULES += enetphy
PDK_LIB_RULES += $(ENET_APPUTILS_LIB)
PDK_LIB_RULES += uart
PDK_LIB_RULES += gpio
PDK_LIB_RULES += board
PDK_LIB_RULES += ipc
PDK_LIB_RULES += enet_timesync_hal
PDK_LIB_RULES += enet_timesync_ptp
