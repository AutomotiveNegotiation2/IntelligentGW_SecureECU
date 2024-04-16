#
# Copyright (c) {2015 - 2020} Texas Instruments Incorporated
#
# All rights reserved not granted herein.
#
# Limited License.
#
# Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
# license under copyrights and patents it now or hereafter owns or controls to make,
# have made, use, import, offer to sell and sell ("Utilize") this software subject to the
# terms herein.  With respect to the foregoing patent license, such license is granted
# solely to the extent that any such patent is necessary to Utilize the software alone.
# The patent license shall not apply to any combinations which include this software,
# other than combinations with devices manufactured by or for TI ("TI Devices").
# No hardware patent is licensed hereunder.
#
# Redistributions must preserve existing copyright notices and reproduce this license
# (including the above copyright notice and the disclaimer and (if applicable) source
# code license limitations below) in the documentation and/or other materials provided
# with the distribution
#
# Redistribution and use in binary form, without modification, are permitted provided
# that the following conditions are met:
#
# *       No reverse engineering, decompilation, or disassembly of this software is
# permitted with respect to any software provided in binary form.
#
# *       any redistribution and use are licensed by TI for use only with TI Devices.
#
# *       Nothing shall obligate TI to provide you with source code for the software
# licensed and provided to you in object code.
#
# If software source code is provided to you, modification and redistribution of the
# source code are permitted provided that the following conditions are met:
#
# *       any redistribution and use of the source code, including any resulting derivative
# works, are licensed by TI for use only with TI Devices.
#
# *       any redistribution and use of any object code compiled from the source code
# and any resulting derivative works, are licensed by TI for use only with TI Devices.
#
# Neither the name of Texas Instruments Incorporated nor the names of its suppliers
#
# may be used to endorse or promote products derived from this software without
# specific prior written permission.
#
# DISCLAIMER.
#
# THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.
#
#
#Other Variables

# Supported values: PC, TI_DEVICE (SIMULATORS or EMULATOR )
TARGET_PLATFORM ?= TI_DEVICE
# Supported values: debug and release)
TARGET_BUILD    ?= release
# Supported values: j721e j721s2 j784s4 am62a
TARGET_SOC ?= j721e
# Supported C64T, C64P, C64, C66, C674, C67, C67P, m4
TARGET_CPU      ?= C71
# Supported values: 1 and 0)
BUILD_WITH_CUDA ?= 0


PSDK_INSTALL_PATH   ?= /ti/j7presi/workarea/
CONCERTO_ROOT       ?=$(PSDK_INSTALL_PATH)/vision_apps/concerto
IVISION_PATH        ?=$(PSDK_INSTALL_PATH)/ivision

ifeq ($(TARGET_PLATFORM), PC)
DSP_TOOLS           ?=$(PSDK_INSTALL_PATH)/ti-cgt-c7000_3.1.0.LTS
MMALIB_PATH         ?=$(PSDK_INSTALL_PATH)/mmalib_02_06_02_00
PDK_INSTALL_PATH    ?=$(PSDK_INSTALL_PATH)/pdk/packages
endif


TIOVX_PATH          ?=$(PSDK_INSTALL_PATH)/tiovx
VISION_APPS_PATH    ?=$(PSDK_INSTALL_PATH)/vision_apps
GCC_LINUX_ARM_ROOT  ?=$(PSDK_INSTALL_PATH)/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu
LINUX_FS_PATH       ?=$(PSDK_INSTALL_PATH)/targetfs

TF_REPO_PATH        ?=$(PSDK_INSTALL_PATH)/tensorflow
ONNX_REPO_PATH      ?=$(PSDK_INSTALL_PATH)/onnxruntime
TIDL_PROTOBUF_PATH  ?=$(PSDK_INSTALL_PATH)/protobuf-3.11.3
CUDA_PATH           ?= /usr/local/cuda



#C7x Version (C7120/C7100)
#Compiles code for a particular C7x mode
ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J721E j721e))
TARGET_C7X_VERSION ?= C7100
else ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J721S2 j721s2 J784S4 j784s4))
TARGET_C7X_VERSION ?= C7120
else ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), AM62A am62a))
TARGET_C7X_VERSION ?= C7504
endif