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
# Usage : make_multicore_appimages.sh BOARD (BOARD can be j721e_evm, j7200_evm, j721s2_evm j784s4_evm)

MY_BOARD=$1
if [ "${MY_BOARD}" = "j721e_evm" ]
then
  MY_SOC=j721e
elif [ "${MY_BOARD}" = "j7200_evm" ]
then
  MY_SOC=j7200
elif [ "${MY_BOARD}" = "j721s2_evm" ]
then
  MY_SOC=j721s2
elif [ "${MY_BOARD}" = "j784s4_evm" ]
then
  MY_SOC=j784s4
fi

# for each of the cores, ensure that the image was properly created
ALL_CORE_IMAGES_CREATED=1

if [ "${MY_SOC}" == "j7200" ] || [ "${MY_SOC}" == "j721e" ] || [ "${MY_SOC}" == "j721s2" ] || [ "${MY_SOC}" == "j784s4" ]  
then
  MY_PROFILE=release
  MY_BUILDDIR=../../../../../build
  MY_APP=""
  SDK_INSTALL_PATH=${PWD}/../../../../../../../..
  PDK_INSTALL_PATH=${SDK_INSTALL_PATH}/pdk/packages

  declare -a cores_j721e=("mpu1_0" "mcu2_0" "mcu2_1" "mcu3_0" "mcu3_1" "c66xdsp_1" "c66xdsp_2" "c7x_1")
  declare -a cores_exten_names_j721e=("xa72fg" "xer5f" "xer5f" "xer5f" "xer5f" "xe66" "xe66" "xe71")
  declare -a cores_j7200=("mpu1_0" "mcu2_0" "mcu2_1")
  declare -a cores_exten_names_j7200=("xa72fg" "xer5f" "xer5f")
  declare -a cores_j721s2=("mpu1_0" "mcu2_0" "mcu2_1" "mcu3_0" "mcu3_1"  "c7x_1" "c7x_2")
  declare -a cores_exten_names_j721s2=("xa72fg" "xer5f" "xer5f" "xer5f" "xer5f" "xe71" "xe71")
  declare -a cores_j784s4=("mpu1_0" "mcu2_0" "mcu2_1" "mcu3_0" "mcu3_1" "mcu4_0" "mcu4_1" "c7x_1" "c7x_2" "c7x_3" "c7x_4")
  declare -a cores_exten_names_j784s4=("xa72fg" "xer5f" "xer5f" "xer5f" "xer5f" "xer5f" "xer5f" "xe71" "xe71" "xe71" "xe71")
  MY_BLD="-s -j BOARD=${MY_BOARD} SOC=${MY_SOC} BUILD_PROFILE=${MY_PROFILE}" 
fi

pushd $PWD
cd ${MY_BUILDDIR}

# iterate over all cores of J721e
if [ "${MY_BOARD}" = "j721e_evm" ]
then
    for i in "${!cores_j721e[@]}"
    do
        if [ "${cores_j721e[i]}" = "mcu2_0" ] || [ "${cores_j721e[i]}" = "mcu2_1" ] || [ "${cores_j721e[i]}" = "mcu3_0" ] || [ "${cores_j721e[i]}" = "mcu3_1" ] || [ "${cores_j721e[i]}" = "c66xdsp_1" ] || [ "${cores_j721e[i]}" = "c66xdsp_2" ] || [ "${cores_j721e[i]}" = "c7x_1" ]
        then
            MY_APP=ipc_rtos_echo_test_freertos
            echo make ${MY_BLD} ${MY_APP} CORE="${cores_j721e[i]}"
            make ${MY_BLD} ${MY_APP} CORE="${cores_j721e[i]}"
        elif [ "${cores_j721e[i]}" = "mpu1_0" ]
        then 
             MY_APP=udma_baremetal_memcpy_testapp
             echo make ${MY_BLD} ${MY_APP} CORE="${cores_j721e[i]}"
             make ${MY_BLD} ${MY_APP} CORE="${cores_j721e[i]}"
        fi
        FILE=${PDK_INSTALL_PATH}/ti/binary/${MY_APP}/bin/${MY_BOARD}/${MY_APP}_${cores_j721e[i]}_${MY_PROFILE}.${cores_exten_names_j721e[i]}
        if [ ! -f "$FILE" ]
        then
            echo "Error - $FILE does not exist"
            ALL_CORE_IMAGES_CREATED=0
            break
        fi
    done
fi

# iterate over all cores of J7200
if [ ${MY_BOARD} = "j7200_evm" ]
then
    for i in "${!cores_j7200[@]}"
    do
        if [ "${cores_j7200[i]}" = "mcu2_0" ] || [ "${cores_j7200[i]}" = "mcu2_1" ]
        then
            MY_APP=ipc_rtos_echo_test_freertos
            echo make ${MY_BLD} ${MY_APP} CORE="${cores_j7200[i]}"
            make ${MY_BLD} ${MY_APP} CORE="${cores_j7200[i]}"
        elif [ "${cores_j7200[i]}" = "mpu1_0" ]
        then 
            MY_APP=udma_baremetal_memcpy_testapp
            echo make ${MY_BLD} ${MY_APP} CORE="${cores_j7200[i]}"
            make ${MY_BLD} ${MY_APP} CORE="${cores_j7200[i]}"
        fi
        FILE=${PDK_INSTALL_PATH}/ti/binary/${MY_APP}/bin/${MY_BOARD}/${MY_APP}_${cores_j7200[i]}_${MY_PROFILE}.${cores_exten_names_j7200[i]}
        if [ ! -f "$FILE" ]
        then
            echo "Error - $FILE does not exist"
            ALL_CORE_IMAGES_CREATED=0
            break
        fi
    done
fi

# iterate over all cores of J721S2
if [ "${MY_BOARD}" = "j721s2_evm" ]
then
    for i in "${!cores_j721s2[@]}"
    do
        if [ "${cores_j721s2[i]}" = "mcu2_0" ] || [ "${cores_j721s2[i]}" = "mcu2_1" ] || [ "${cores_j721s2[i]}" = "mcu3_0" ] || [ "${cores_j721s2[i]}" = "mcu3_1" ] || [ "${cores_j721s2[i]}" = "c7x_1" ] || [ "${cores_j721s2[i]}" = "c7x_2" ]
        then
            MY_APP=ipc_rtos_echo_test_freertos
            echo make ${MY_BLD} ${MY_APP} CORE="${cores_j721s2[i]}"
            make ${MY_BLD} ${MY_APP} CORE="${cores_j721s2[i]}"
        elif [ "${cores_j721s2[i]}" = mpu1_0 ]
        then 
            MY_APP=udma_baremetal_memcpy_testapp
            echo make ${MY_BLD} ${MY_APP} CORE="${cores_j721s2[i]}"
            make ${MY_BLD} ${MY_APP} CORE="${cores_j721s2[i]}"
        fi
        FILE=${PDK_INSTALL_PATH}/ti/binary/${MY_APP}/bin/${MY_BOARD}/${MY_APP}_${cores_j721s2[i]}_${MY_PROFILE}.${cores_exten_names_j721s2[i]}
        if [ ! -f "$FILE" ]; then
            echo "Error - $FILE does not exist"
            ALL_CORE_IMAGES_CREATED=0
            break
        fi
    done
fi

# iterate over all cores of J784S4
if [ "${MY_BOARD}" = "j784s4_evm" ]
then
    for i in "${!cores_j784s4[@]}"
    do
        if [ "${cores_j784s4[i]}" = "mcu2_0" ] || [ "${cores_j784s4[i]}" = "mcu2_1" ] || [ "${cores_j784s4[i]}" = "mcu3_0" ] || [ "${cores_j784s4[i]}" = "mcu3_1" ] || [ "${cores_j784s4[i]}" = "mcu4_0" ] || [ "${cores_j784s4[i]}" = "mcu4_1" ] || [ "${cores_j784s4[i]}" = "c7x_1" ] || [ "${cores_j784s4[i]}" = "c7x_2" ] || [ "${cores_j784s4[i]}" = "c7x_3" ] || [ "${cores_j784s4[i]}" = "c7x_4" ]
        then
            MY_APP=ipc_rtos_echo_test_freertos
            echo make ${MY_BLD} ${MY_APP} CORE="${cores_j784s4[i]}"
            make ${MY_BLD} ${MY_APP} CORE="${cores_j784s4[i]}"
        elif [ "${cores_j784s4[i]}" = mpu1_0 ]
        then 
            MY_APP=udma_baremetal_memcpy_testapp
            echo make ${MY_BLD} ${MY_APP} CORE="${cores_j784s4[i]}"
            make ${MY_BLD} ${MY_APP} CORE="${cores_j784s4[i]}"
        fi
        FILE=${PDK_INSTALL_PATH}/ti/binary/${MY_APP}/bin/${MY_BOARD}/${MY_APP}_${cores_j784s4[i]}_${MY_PROFILE}.${cores_exten_names_j784s4[i]}
        if [ ! -f "$FILE" ];
        then
            echo "Error - $FILE does not exist"
            ALL_CORE_IMAGES_CREATED=0
            break
        fi
    done
fi

popd

if [ $ALL_CORE_IMAGES_CREATED == 1 ]
then
    # Since all core images were created, we can create the
    # RPRC multicore appimage now
    echo All the Core images have been created
    bash constructappimage_multistage_${MY_SOC}.sh
fi
