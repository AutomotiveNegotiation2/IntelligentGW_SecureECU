#!/bin/bash
#
# Copyright (c) 2022, Texas Instruments Incorporated
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# *  Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
# *  Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# *  Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
# THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Usage : This will be called by make_multicore_appimages.sh

#####################
## User-defined paths
#####################

SDK_INSTALL_PATH=${PWD}/../../../../../../../..
pushd ${PWD}
cd ${SDK_INSTALL_PATH}
SDK_INSTALL_PATH=${PWD}
popd
PDK_INSTALL_PATH="${SDK_INSTALL_PATH}/pdk/packages"
SBL_REPO_PATH="${PDK_INSTALL_PATH}/ti/boot/sbl"
MULTICORE_APPIMAGE_GEN_TOOL_PATH="${SBL_REPO_PATH}/tools/multicoreImageGen/bin"
SBL_OUT2RPRC_GEN_TOOL_PATH="${SBL_REPO_PATH}/tools/out2rprc/bin"

rm -rf ../multicore_images/*
mkdir -p ../multicore_images/j721s2_evm
MULTICOREAPP_BIN_PATH=${SBL_REPO_PATH}/example/boot_app/multicore_images/j721s2_evm

devId=55

###################################
## Image definitions for each stage
###################################

numStages=3

appImageName1=multicore_MCU2_0_MCU2_1_stage1.appimage
appImageName2=multicore_DSP_1_2_C7x_MCU3_0_MCU3_1_stage2.appimage
appImageName3=multicore_MPU1_0_stage3.appimage

ElfImages1=("ipc_rtos_echo_test_freertos_mcu2_0_release.xer5f" \
            "ipc_rtos_echo_test_freertos_mcu2_1_release.xer5f" \
           )
ElfImages2=("ipc_rtos_echo_test_freertos_mcu3_0_release.xer5f" \
            "ipc_rtos_echo_test_freertos_mcu3_1_release.xer5f" \
            "ipc_rtos_echo_test_freertos_c7x_1_release.xe71" \
            "ipc_rtos_echo_test_freertos_c7x_2_release.xe71" \
           )
ElfImages3=("udma_baremetal_memcpy_testapp_mpu1_0_release.xa72fg" \
           )

CoreRprcFiles1=("ipc_rtos_echo_test_freertos_mcu2_0_release.xer5f.rprc" \
                "ipc_rtos_echo_test_freertos_mcu2_1_release.xer5f.rprc" \
               )
CoreRprcFiles2=("ipc_rtos_echo_test_freertos_mcu3_0_release.xer5f.rprc" \
                "ipc_rtos_echo_test_freertos_mcu3_1_release.xer5f.rprc" \
                "ipc_rtos_echo_test_freertos_c7x_1_release.xe71.rprc" \
                "ipc_rtos_echo_test_freertos_c7x_2_release.xe71.rprc" \
               )
CoreRprcFiles3=("udma_baremetal_memcpy_testapp_mpu1_0_release.xa72fg.rprc" \
               )

CoreIds1=(10 11);
CoreIds2=(12 13 18 19);
CoreIds3=(0);

############################################################

## Create all output arguments for each of the stages

# Create output arguments for Stage 1 appimage
arrayLength=${#CoreIds1[@]}
echo "Stage 1 length is $arrayLength"

for (( i = 0; i < $arrayLength; i++ )); do
    output_args1+="${CoreIds1[i]} ${CoreRprcFiles1[i]} "
done

# Create output arguments for Stage 2 appimage
arrayLength=${#CoreIds2[@]}
echo "Stage 2 length is $arrayLength"
for (( i = 0; i < $arrayLength; i++ )); do
    output_args2+="${CoreIds2[i]} ${CoreRprcFiles2[i]} "
done

# Create output arguments for Stage 3 appimage
arrayLength=${#CoreIds3[@]}
echo "Stage 3 length is $arrayLength"
for (( i = 0; i < $arrayLength; i++ )); do
    output_args3+="${CoreIds3[i]} ${CoreRprcFiles3[i]} "
done

cd $MULTICOREAPP_BIN_PATH

## Create all rprc files for each of the stages
for i in ${ElfImages1[@]}; do
    MY_APP=ipc_rtos_echo_test_freertos
    $SBL_OUT2RPRC_GEN_TOOL_PATH/out2rprc.exe ${PDK_INSTALL_PATH}/ti/binary/${MY_APP}/bin/j721s2_evm/$i "$i.rprc"
done
for i in ${ElfImages2[@]}; do
    MY_APP=ipc_rtos_echo_test_freertos
    $SBL_OUT2RPRC_GEN_TOOL_PATH/out2rprc.exe ${PDK_INSTALL_PATH}/ti/binary/${MY_APP}/bin/j721s2_evm/$i "$i.rprc"
done
for i in ${ElfImages3[@]}; do
    MY_APP=udma_baremetal_memcpy_testapp
    $SBL_OUT2RPRC_GEN_TOOL_PATH/out2rprc.exe ${PDK_INSTALL_PATH}/ti/binary/${MY_APP}/bin/j721s2_evm/$i "$i.rprc"
done

# Generate the appimage (both unsigned and signed) for Stage 1
$MULTICORE_APPIMAGE_GEN_TOOL_PATH/MulticoreImageGen LE $devId $appImageName1 $output_args1
$PDK_INSTALL_PATH/ti/build/makerules/x509CertificateGen.sh -b $PDK_INSTALL_PATH/ti/boot/sbl/example/boot_app/multicore_images/j721s2_evm/$appImageName1 -o $MULTICOREAPP_BIN_PATH/$appImageName1.signed -c R5 -l 0x41C00100 -k $PDK_INSTALL_PATH/ti/build/makerules/k3_dev_mpk.pem

echo "output_args is $output_args1"
echo "Wrote output appImage to $appImageName1"
echo "Wrote signed output appImage to $appImageName1.signed"

# ## Generate the appimage (both unsigned and signed) for Stage 2
$MULTICORE_APPIMAGE_GEN_TOOL_PATH/MulticoreImageGen LE $devId $appImageName2 $output_args2
$PDK_INSTALL_PATH/ti/build/makerules/x509CertificateGen.sh -b $PDK_INSTALL_PATH/ti/boot/sbl/example/boot_app/multicore_images/j721s2_evm/$appImageName2 -o $MULTICOREAPP_BIN_PATH/$appImageName2.signed -c R5 -l 0x41C00100 -k $PDK_INSTALL_PATH/ti/build/makerules/k3_dev_mpk.pem

echo "output_args is $output_args2"
echo "Wrote output appImage to $appImageName2"
echo "Wrote signed output appImage to $appImageName2.signed"

## Generate the appimage (both unsigned and signed) for Stage 3
$MULTICORE_APPIMAGE_GEN_TOOL_PATH/MulticoreImageGen LE $devId $appImageName3 $output_args3
$PDK_INSTALL_PATH/ti/build/makerules/x509CertificateGen.sh -b $PDK_INSTALL_PATH/ti/boot/sbl/example/boot_app/multicore_images/j721s2_evm/$appImageName3 -o $MULTICOREAPP_BIN_PATH/$appImageName3.signed -c R5 -l 0x41C00100 -k $PDK_INSTALL_PATH/ti/build/makerules/k3_dev_mpk.pem

echo "output_args is $output_args3"
echo "Wrote output appImage to $appImageName3"
echo "Wrote signed output appImage to $appImageName3.signed"

