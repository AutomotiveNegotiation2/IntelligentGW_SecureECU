
PSDK_PATH = $(abspath ..)
$(info PSDK_PATH=$(PSDK_PATH))

TIOVX_PATH ?= $(PSDK_PATH)/tiovx

# paths for cgtools are specified in below
# file in tiovx, ...
include $(TIOVX_PATH)/psdkra_tools_path.mak
