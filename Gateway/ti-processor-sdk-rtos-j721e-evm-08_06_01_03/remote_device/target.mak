# Copyright (C) 2011 Texas Insruments, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


ifeq ($(BUILD_DEBUG),1)
$(info TI_TOOLS_ROOT=$(TI_TOOLS_ROOT))
$(info TIARMCGT_ROOT=$(TIARMCGT_ROOT))
$(info TIARMCGT_LLVM_ROOT=$(TIARMCGT_LLVM_ROOT))
endif

# DEP_PROJECTS does not need to be set as the dependencies are contained in the build.

SYSLDIRS :=
SYSDEFS  :=

ifeq ($(TARGET_PLATFORM),$(filter $(TARGET_PLATFORM), J721E J7200 J721S2 J784S4))
	SYSDEFS +=
	ifeq ($(TARGET_FAMILY),ARM)
		ifeq ($(TARGET_CPU),A72)
			SYSIDIRS += $(GCC_LINUX_ARM_ROOT)/aarch64-linux-gnu/libc/usr/include/
			SYSLDIRS += $(GCC_LINUX_ARM_ROOT)/aarch64-linux-gnu/libc/usr/lib/
		else
			SYSIDIRS += $(TIARMCGT_LLVM_ROOT)/include
			SYSLDIRS += $(TIARMCGT_LLVM_ROOT)/lib
		endif
	else ifeq ($(TARGET_FAMILY),DSP)
		ifeq ($(TARGET_CPU),C66)
		SYSIDIRS += $(CGT6X_ROOT)/include
		SYSLDIRS += $(CGT6X_ROOT)/lib
		else
		SYSIDIRS += $(CGT7X_ROOT)/include
		SYSLDIRS += $(CGT7X_ROOT)/lib
		endif
	else ifeq ($(TARGET_FAMILY),EVE)
		SYSIDIRS += $(ARP32CGT_ROOT)/include
		SYSLDIRS += $(ARP32CGT_ROOT)/lib
	endif
	SYSIDIRS += $(PDK_PATH)/packages
endif

ifeq ($(TARGET_PLATFORM),PC)
	SYSDEFS +=
	SYSIDIRS += $(GCC_WINDOWS_ROOT)/include
	SYSLDIRS += $(GCC_WINDOWS_ROOT)/lib
endif

