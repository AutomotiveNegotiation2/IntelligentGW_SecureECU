#!/bin/bash
#
# Utility script to setup SDK for SafeRTOS Builds
#
# Prerequisites:-
# - Make sure you have installed the SafeRTOS Packages from WHIS
#
# Note:-
# - Make sure the paths provided DO NOT have any spaces in them

# Example usage
# ./safertos-setup.sh --j721e_r5f_path=path/to/whis/safertos/j721e/r5f/pacakge --j721e_c66_path=path/to/whis/safertos/j721e/c66/pacakge --j721e_c7x_path=path/to/whis/safertos/j721e/c7x/pacakge
# ./safertos-setup.sh --j721e_r5f_path=path/to/whis/safertos/j721e/r5f/pacakge 
# ./safertos-setup.sh --j721e_c66_path=path/to/whis/safertos/j721e/c66/pacakge 
# ./safertos-setup.sh --j721e_c7x_path=path/to/whis/safertos/j721e/c7x/pacakge


#Environmental variables
pdk_build_path=`pwd`

#Ethernet related libraries
enet_libs="lwipstack_safertos lwipcontrib_safertos lwipport_safertos enet_example_utils_safertos enet_example_utils_full_safertos lwipif_safertos lwipific_safertos"

#Get user input
while [ $# -gt 0 ]; do
  case "$1" in
    --j721e_r5f_path=*)
      j721e_r5f_path="${1#*=}"
      ;;
    --j721e_c66_path=*)
      j721e_c66_path="${1#*=}"
      ;;
    --j721e_c7x_path=*)
      j721e_c7x_path="${1#*=}"
      ;;   
    --j7200_r5f_path=*)
      j7200_r5f_path="${1#*=}"
      ;;
    --j721s2_r5f_path=*)
      j721s2_r5f_path="${1#*=}"
      ;;
    --j721s2_c7x_path=*)
      j721s2_c7x_path="${1#*=}"
      ;;
    --j784s4_c7x_path=*)
      j784s4_c7x_path="${1#*=}"
      ;;
    --j784s4_r5f_path=*)
      j784s4_r5f_path="${1#*=}"
      ;;  
    -h|--help)
      echo Usage: $0 [options]
      echo
      echo Options:
      echo "--j721e_r5f_path       Path to J721E(TDA4VM) R5F SafeRTOS Package from WHIS"
      echo "--j721e_c66_path       Path to J721E(TDA4VM) C66 SafeRTOS Package from WHIS"
      echo "--j721e_c7x_path       Path to J721E(TDA4VM) C7x SafeRTOS Package from WHIS"
      echo "--j7200_r5f_path       Path to J7200(DRA821) R5F SafeRTOS Package from WHIS"
      echo "--j721s2_r5f_path      Path to J721S2(TDA4VL) R5F SafeRTOS Package from WHIS"
      echo "--j721s2_c7x_path      Path to J721S2(TDA4VL) C7X SafeRTOS Package from WHIS"
      echo "--j784s4_r5f_path      Path to J784S4(TDA4VH) R5F SafeRTOS Package from WHIS"
      echo "--j784s4_c7x_path      Path to J784S4(TDA4VH) C7X SafeRTOS Package from WHIS"
      exit 0
      ;;
    *)
      printf "Error: Invalid argument $1!!\n"
  esac
  shift
done

printf "\n pdk_build_path = $pdk_build_path \n"

if [ ! "${j721e_r5f_path}" == "" ]; then
  printf "\n j721e_r5f_path = $j721e_r5f_path \n\n"
  if [ !  -d ${j721e_r5f_path} ] ; then
    printf "\n Error: Invalid j721e_r5f_path!!\n\n"
  else
    #Update R5F Install Path
    sed -i -e "s|SAFERTOS_j721e_r5f_INSTALL_PATH =.*|SAFERTOS_j721e_r5f_INSTALL_PATH = ${j721e_r5f_path}|g" safertos_version.mk
    #Build safertos lib for all R5F cores
    make safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j721e_evm
    make safertos -sj8 CORE=mcu1_1 BUILD_PROFILE=release BOARD=j721e_evm
    make safertos -sj8 CORE=mcu2_0 BUILD_PROFILE=release BOARD=j721e_evm
    make safertos -sj8 CORE=mcu2_1 BUILD_PROFILE=release BOARD=j721e_evm
    make safertos -sj8 CORE=mcu3_0 BUILD_PROFILE=release BOARD=j721e_evm
    make safertos -sj8 CORE=mcu3_1 BUILD_PROFILE=release BOARD=j721e_evm
    #OSAL is a core independent library, and hence building for 1 of the cores is sufficient.
    make osal_safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j721e_evm
    #Build sciserver_testapp_safertos and check-in
    make sciserver_testapp_safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j721e_evm
    cp ${pdk_build_path}/../binary/sciserver_testapp_safertos/bin/j721e/sciserver_testapp_safertos_mcu1_0_release.xer5f ${pdk_build_path}/../drv/sciclient/tools/ccsLoadDmsc/j721e/
    cp ${pdk_build_path}/../binary/sciserver_testapp_safertos/bin/j721e/sciserver_testapp_safertos_mcu1_0_release.rprc  ${pdk_build_path}/../drv/sciclient/tools/ccsLoadDmsc/j721e/
    #Ethernet related libraries
    make ${enet_libs} -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j721e_evm
    make ${enet_libs} -sj8 CORE=mcu2_0 BUILD_PROFILE=release BOARD=j721e_evm
    make ${enet_libs} -sj8 CORE=mcu2_1 BUILD_PROFILE=release BOARD=j721e_evm
    printf "\n Successfully completed setup SafeRTOS Builds for J721E R5F\n\n"
  fi
fi
if [ ! "${j721e_c66_path}" == "" ]; then
  printf "\n j721e_c66_path = $j721e_c66_path \n\n"
  if [ !  -d ${j721e_c66_path} ] ; then
    printf "\n Error: Invalid j721e_c66_path!!\n\n"
  else
    #Update C66 Install Path
    sed -i -e "s|SAFERTOS_j721e_c66_INSTALL_PATH =.*|SAFERTOS_j721e_c66_INSTALL_PATH = ${j721e_c66_path}|g" safertos_version.mk
    #Build safertos lib for all c66 cores
    make safertos -sj8 CORE=c66xdsp_1 BUILD_PROFILE=release;
    make safertos -sj8 CORE=c66xdsp_2 BUILD_PROFILE=release;
    #OSAL is a core independent library, and hence building for 1 of the cores is sufficient.
    make osal_safertos -sj8 CORE=c66xdsp_1 BUILD_PROFILE=release;
    printf "\n Successfully completed setup SafeRTOS Builds for J721E C66\n\n"
  fi
fi
if [ ! "${j721e_c7x_path}" == "" ]; then
  printf "\n j721e_c7x_path = $j721e_c7x_path \n\n"
  if [ !  -d ${j721e_c7x_path} ] ; then
    printf "\n Error: Invalid j721e_c7x_path!!\n\n"
  else
    #Update C7x install Path
    sed -i -e "s|SAFERTOS_j721e_c7x_INSTALL_PATH =.*|SAFERTOS_j721e_c7x_INSTALL_PATH = ${j721e_c7x_path}|g" safertos_version.mk
    #Build safertos lib for all c7x cores
    make safertos -sj8 CORE=c7x_1 BUILD_PROFILE=release;
    #Build osal_safertos for c7x
    make osal_safertos -sj8 CORE=c7x_1 BUILD_PROFILE=release;
    printf "\n Successfully completed setup SafeRTOS Builds for J721E C7x\n\n"
  fi
fi

if [ ! "${j7200_r5f_path}" == "" ]; then
  printf "\n j7200_r5f_path = $j7200_r5f_path \n\n"
  if [ !  -d ${j7200_r5f_path} ] ; then
    printf "\n Error: Invalid j7200_r5f_path!!\n\n"
  else
    #Update R5F Install Path
    sed -i -e "s|SAFERTOS_j7200_r5f_INSTALL_PATH =.*|SAFERTOS_j7200_r5f_INSTALL_PATH = ${j7200_r5f_path}|g" safertos_version.mk
    #Build safertos lib for all R5F cores
    make safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j7200_evm
    make safertos -sj8 CORE=mcu1_1 BUILD_PROFILE=release BOARD=j7200_evm
    make safertos -sj8 CORE=mcu2_0 BUILD_PROFILE=release BOARD=j7200_evm
    make safertos -sj8 CORE=mcu2_1 BUILD_PROFILE=release BOARD=j7200_evm
    #OSAL is a core independent library, and hence building for 1 of the cores is sufficient.
    make osal_safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j7200_evm
    #Build sciserver_testapp_safertos and check-in
    make sciserver_testapp_safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j7200_evm
    cp ${pdk_build_path}/../binary/sciserver_testapp_safertos/bin/j7200/sciserver_testapp_safertos_mcu1_0_release.xer5f ${pdk_build_path}/../drv/sciclient/tools/ccsLoadDmsc/j7200/
    cp ${pdk_build_path}/../binary/sciserver_testapp_safertos/bin/j7200/sciserver_testapp_safertos_mcu1_0_release.rprc  ${pdk_build_path}/../drv/sciclient/tools/ccsLoadDmsc/j7200/
    #Ethernet related libraries
    make ${enet_libs} -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j7200_evm
    make ${enet_libs} -sj8 CORE=mcu2_0 BUILD_PROFILE=release BOARD=j7200_evm
    make ${enet_libs} -sj8 CORE=mcu2_1 BUILD_PROFILE=release BOARD=j7200_evm
    printf "\n Successfully completed setup SafeRTOS Builds for J7200 R5F\n\n"
  fi
fi

if [ ! "${j721s2_r5f_path}" == "" ]; then
  printf "\n j721s2_r5f_path = $j721s2_r5f_path \n\n"
  if [ !  -d ${j721s2_r5f_path} ] ; then
    printf "\n Error: Invalid j721s2_r5f_path!!\n\n"
  else
    #Update R5F Install Path
    sed -i -e "s|SAFERTOS_j721s2_r5f_INSTALL_PATH =.*|SAFERTOS_j721s2_r5f_INSTALL_PATH = ${j721s2_r5f_path}|g" safertos_version.mk
    #Build safertos lib for all R5F cores
    make safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j721s2_evm
    make safertos -sj8 CORE=mcu1_1 BUILD_PROFILE=release BOARD=j721s2_evm
    make safertos -sj8 CORE=mcu2_0 BUILD_PROFILE=release BOARD=j721s2_evm
    make safertos -sj8 CORE=mcu2_1 BUILD_PROFILE=release BOARD=j721s2_evm
    make safertos -sj8 CORE=mcu3_0 BUILD_PROFILE=release BOARD=j721s2_evm
    make safertos -sj8 CORE=mcu3_1 BUILD_PROFILE=release BOARD=j721s2_evm
    #OSAL is a core independent library, and hence building for 1 of the cores is sufficient.
    make osal_safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j721s2_evm
    #Build sciserver_testapp_safertos and check-in
    make sciserver_testapp_safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j721s2_evm
    cp ${pdk_build_path}/../binary/sciserver_testapp_safertos/bin/j721s2/sciserver_testapp_safertos_mcu1_0_release.xer5f ${pdk_build_path}/../drv/sciclient/tools/ccsLoadDmsc/j721s2/
    cp ${pdk_build_path}/../binary/sciserver_testapp_safertos/bin/j721s2/sciserver_testapp_safertos_mcu1_0_release.rprc  ${pdk_build_path}/../drv/sciclient/tools/ccsLoadDmsc/j721s2/
    #Ethernet related libraries
    make ${enet_libs} -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j721s2_evm
    make ${enet_libs} -sj8 CORE=mcu2_0 BUILD_PROFILE=release BOARD=j721s2_evm
    make ${enet_libs} -sj8 CORE=mcu2_1 BUILD_PROFILE=release BOARD=j721s2_evm
    printf "\n Successfully completed setup SafeRTOS Builds for J721S2 R5F\n\n"
  fi
fi

if [ ! "${j721s2_c7x_path}" == "" ]; then
  printf "\n j721s2_c7x_path = $j721s2_c7x_path \n\n"
  if [ !  -d ${j721s2_c7x_path} ] ; then
    printf "\n Error: Invalid j721s2_c7x_path!!\n\n"
  else
    #Update C7X Install Path
    sed -i -e "s|SAFERTOS_j721s2_c7x_INSTALL_PATH =.*|SAFERTOS_j721s2_c7x_INSTALL_PATH = ${j721s2_c7x_path}|g" safertos_version.mk
    #Build safertos lib for all C7X cores
    make safertos -sj8 CORE=c7x_1 BUILD_PROFILE=release BOARD=j721s2_evm
    make safertos -sj8 CORE=c7x_2 BUILD_PROFILE=release BOARD=j721s2_evm
    #OSAL is a core independent library, and hence building for 1 of the cores is sufficient.
    make osal_safertos -sj8 CORE=c7x_1 BUILD_PROFILE=release BOARD=j721s2_evm
    printf "\n Successfully completed setup SafeRTOS Builds for J721S2 C7X\n\n"
  fi
fi

if [ ! "${j784s4_r5f_path}" == "" ]; then
  printf "\n j784s4_r5f_path = $j784s4_r5f_path \n\n"
  if [ !  -d ${j7284s4_r5f_path} ] ; then
    printf "\n Error: Invalid j784s4_r5f_path!!\n\n"
  else
    #Update R5F Install Path
    sed -i -e "s|SAFERTOS_j784s4_r5f_INSTALL_PATH =.*|SAFERTOS_j784s4_r5f_INSTALL_PATH = ${j784s4_r5f_path}|g" safertos_version.mk
    #Build safertos lib for all R5F cores
    make safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j784s4_evm
    make safertos -sj8 CORE=mcu1_1 BUILD_PROFILE=release BOARD=j784s4_evm
    make safertos -sj8 CORE=mcu2_0 BUILD_PROFILE=release BOARD=j784s4_evm
    make safertos -sj8 CORE=mcu2_1 BUILD_PROFILE=release BOARD=j784s4_evm
    make safertos -sj8 CORE=mcu3_0 BUILD_PROFILE=release BOARD=j784s4_evm
    make safertos -sj8 CORE=mcu3_1 BUILD_PROFILE=release BOARD=j784s4_evm
    make safertos -sj8 CORE=mcu4_0 BUILD_PROFILE=release BOARD=j784s4_evm
    make safertos -sj8 CORE=mcu4_1 BUILD_PROFILE=release BOARD=j784s4_evm
    #OSAL is a core independent library, and hence building for 1 of the cores is sufficient.
    make osal_safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j784s4_evm
    #Build sciserver_testapp_safertos and check-in
    make sciserver_testapp_safertos -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j784s4_evm
    cp ${pdk_build_path}/../binary/sciserver_testapp_safertos/bin/j784s4/sciserver_testapp_safertos_mcu1_0_release.xer5f ${pdk_build_path}/../drv/sciclient/tools/ccsLoadDmsc/j784s4/
    cp ${pdk_build_path}/../binary/sciserver_testapp_safertos/bin/j784s4/sciserver_testapp_safertos_mcu1_0_release.rprc  ${pdk_build_path}/../drv/sciclient/tools/ccsLoadDmsc/j784s4/
    #Ethernet related libraries
    make ${enet_libs} -sj8 CORE=mcu1_0 BUILD_PROFILE=release BOARD=j784s4_evm
    make ${enet_libs} -sj8 CORE=mcu2_0 BUILD_PROFILE=release BOARD=j784s4_evm
    make ${enet_libs} -sj8 CORE=mcu2_1 BUILD_PROFILE=release BOARD=j784s4_evm
    printf "\n Successfully completed setup SafeRTOS Builds for j784s4 R5F\n\n"
  fi
fi

if [ ! "${j784s4_c7x_path}" == "" ]; then
  printf "\n j784s4_c7x_path = $j784s4_c7x_path \n\n"
  if [ !  -d ${j784s4_c7x_path} ] ; then
    printf "\n Error: Invalid j784s4_c7x_path!!\n\n"
  else
    #Update C7X Install Path
    sed -i -e "s|SAFERTOS_j784s4_c7x_INSTALL_PATH =.*|SAFERTOS_j784s4_c7x_INSTALL_PATH = ${j784s4_c7x_path}|g" safertos_version.mk
    #Build safertos lib for all C7X cores
    make safertos -sj8 CORE=c7x_1 BUILD_PROFILE=release BOARD=j784s4_evm
    make safertos -sj8 CORE=c7x_2 BUILD_PROFILE=release BOARD=j784s4_evm
    make safertos -sj8 CORE=c7x_3 BUILD_PROFILE=release BOARD=j784s4_evm
    make safertos -sj8 CORE=c7x_4 BUILD_PROFILE=release BOARD=j784s4_evm
    #OSAL is a core independent library, and hence building for 1 of the cores is sufficient.
    make osal_safertos -sj8 CORE=c7x_1 BUILD_PROFILE=release BOARD=j784s4_evm

    printf "\n Successfully completed setup SafeRTOS Builds for j784s4 C7X\n\n"
  fi
fi

exit
