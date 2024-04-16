include $(PRELUDE)

TARGET      := eth_intervlan
TARGETTYPE  := library

ifneq (,$(filter $(TARGET_PLATFORM),J721E J7200 J784S4 AM65XX))

CSOURCES := src/eth_hwintervlan.c
CSOURCES += src/eth_swintervlan.c

IDIRS := ${ETHFW_PATH}
IDIRS += $(PDK_PATH)/packages

endif

include $(FINALE)
