#!/bin/bash
#
# Copyright (c) 2018-2022, Texas Instruments Incorporated
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
# Usage : sysfw_migrate.sh <release tag> [OPTIONS]

################################################################################
export RM=rm
export MV=mv
export MKDIR=mkdir
export MAKE=gcc
export ECHO=echo
export CHMOD=chmod
export COPY=cp
export CAT=cat

################################################################################
# Parse CLI arguments
RELEASE_TAG=$1
SOC_LIST=$2
for i in "$@"; do
case $i in
    -sr|--skip-reset) # Skips the PDK reset and rebase step
        SKIP_RESET=YES
        shift
        ;;
    -sk|--skip-checkout) # Skips the SYSFW checkout step
        SKIP_CHECKOUT=YES
        shift
        ;;
    -sb|--skip-build) # Skips the sciclient_ccs_init build step
        SKIP_BUILD=YES
        shift
        ;;
    -sg|--skip-gen) # Skips the firmwareHeaderGen.sh step
        SKIP_GEN_BIN=YES
        shift
        ;;
    -sc|--skip-commit) # Skips the PDK commit step
        SKIP_COMMIT=YES
        shift
        ;;
    -*) # Invalid flag
        $ECHO "!!!WARNING!!! - IGNORING INVALID FLAG: $1"
        shift
        ;;
esac
done

# Check CLI positional args (must always include a SYSFW release tag)
if [ "$RELEASE_TAG" == "" ]; then
    $ECHO "Usage : sysfw_migrate.sh <release tag> <soc_list>(optional) [OPTIONS]"
    exit 1
fi

if [ "$SOC_LIST" == "" ]; then
    SOC_LIST="j721e j7200 j721s2 j784s4"
fi

################################################################################
# Specify paths relative to script
export SCRIPT_DIR=$(cd "$( dirname "${BASH_SOURCE[0]}")" && pwd )
export SCI_CLIENT_DIR=$(cd "$SCRIPT_DIR/.." && pwd )
export ROOTDIR=$(cd "$SCI_CLIENT_DIR/../../.." && pwd )

################################################################################
# Checkout SYSFW release and prepare it for use with PDK

if [ "$SKIP_RESET" != "YES" ]; then
    $ECHO "Reset PDK branch and rebase onto master"
    git reset --hard HEAD
    git fetch origin; git rebase origin/master
fi

if [ "$SKIP_CHECKOUT" != "YES" ]; then

    $ECHO "Cloning the system-firmware-releases"
    cd $SCI_CLIENT_DIR/soc/
    git clone ssh://git@bitbucket.itg.ti.com/sysfw/system-firmware-releases.git --branch $RELEASE_TAG
    if [ $? -ne 0 ]; then
        $ECHO
        $ECHO "!!!ABORT!!! - SYSFW TAG NOT FOUND: $RELEASE_TAG"
        exit 1
    fi

    $ECHO "Remove old SYSFW dir, and replace it with the newly cloned repo"
    $RM -fr sysfw/binaries/scripts
    $MV system-firmware-releases/binaries/scripts sysfw/binaries
    $RM -fr sysfw/binaries/system-firmware-public-documentation
    $MV system-firmware-releases/binaries/system-firmware-public-documentation sysfw/binaries
    $MV system-firmware-releases/binaries/ti-fs*j7*gp.bin sysfw/binaries
    $MV system-firmware-releases/binaries/ti-fs*j7*cert.bin sysfw/binaries
    $MV system-firmware-releases/binaries/ti-fs*j7*enc.bin sysfw/binaries
    $RM -fr sysfw/include/tisci
    $COPY -r system-firmware-releases/include/tisci sysfw/include
    for SOC in $SOC_LIST
    do
        $RM -fr sysfw/include/$SOC
        $MV system-firmware-releases/include/$SOC sysfw/include
    
    done

    $RM -fr system-firmware-release



    cd sysfw

    $ECHO "Removing files not required from SYSFW release.."
    $RM -fr .git
    $RM -fr src
    $RM -fr log
    $RM -fr binaries/system-firmware-design-documentation
    $RM -fr binaries/system-firmware-full-documentation
    $RM -fr docs/BUILD.md
    $RM -fr reports
fi

################################################################################
# Build sciclient_ccs_init for use with launch.js
if [ "$SKIP_BUILD" != "YES" ]; then
    cd $ROOTDIR/ti/build

    for SOC in $SOC_LIST
    do
        make -j -s allclean
        make -j -s sciclient_boardcfg BOARD="$SOC"_evm
        make -j -s sciclient_boardcfg BOARD="$SOC"_evm BUILD_HS=yes
        make -j -s sciclient_ccs_init_clean BOARD="$SOC"_evm
        make -j -s sciclient_ccs_init BOARD="$SOC"_evm
        make -j -s sciserver_testapp_freertos_clean BOARD="$SOC"_evm
        make -j -s sciserver_testapp_freertos BOARD="$SOC"_evm
        $COPY $ROOTDIR/ti/binary/sciclient_ccs_init/bin/"$SOC"/sciclient_ccs_init_mcu1_0_release.xer5f $SCI_CLIENT_DIR/tools/ccsLoadDmsc/"$SOC"/
        $COPY $ROOTDIR/ti/binary/sciserver_testapp_freertos/bin/"$SOC"/sciserver_testapp_freertos_mcu1_0_release.xer5f $SCI_CLIENT_DIR/tools/ccsLoadDmsc/"$SOC"/
        $COPY $ROOTDIR/ti/binary/sciserver_testapp_freertos/bin/"$SOC"/sciserver_testapp_freertos_mcu1_0_release.rprc $SCI_CLIENT_DIR/tools/ccsLoadDmsc/"$SOC"/
        if [ $SOC=="j721e" ] || [ $SOC=="j7200" ] || [ $SOC=="j721s2" ]; then
            make -j -s sciserver_testapp_safertos_clean BOARD="$SOC"_evm
            make -j -s sciserver_testapp_safertos BOARD="$SOC"_evm
            $COPY $ROOTDIR/ti/binary/sciserver_testapp_safertos/bin/"$SOC"/sciserver_testapp_safertos_mcu1_0_release.xer5f $SCI_CLIENT_DIR/tools/ccsLoadDmsc/"$SOC"/
            $COPY $ROOTDIR/ti/binary/sciserver_testapp_safertos/bin/"$SOC"/sciserver_testapp_safertos_mcu1_0_release.rprc $SCI_CLIENT_DIR/tools/ccsLoadDmsc/"$SOC"/
        fi
    done

    cd -
fi

################################################################################

if [ "$SKIP_GEN_BIN" != "YES" ];  then

    cd $ROOTDIR/ti/drv/sciclient/tools/

    for SOC in $SOC_LIST
    do
        case $SOC in
            "j721e")
                ./firmwareHeaderGen.sh j721e
                ./firmwareHeaderGen.sh j721e-hs
                ./firmwareHeaderGen.sh j721e_sr1_1-hs
                ./firmwareHeaderGen.sh j721e_sr2-hs
                ./firmwareHeaderGen.sh j721e_sr2-hs-fs
                shift
                ;;
            "j7200")
                ./firmwareHeaderGen.sh j7200
                ./firmwareHeaderGen.sh j7200-hs
                ./firmwareHeaderGen.sh j7200_sr2-hs
                ./firmwareHeaderGen.sh j7200_sr2-hs-fs
                shift
                ;;
            "j721s2")
                ./firmwareHeaderGen.sh j721s2
                ./firmwareHeaderGen.sh j721s2-hs
                ./firmwareHeaderGen.sh j721s2-hs-fs
                shift
                ;;
            "j784s4")
                ./firmwareHeaderGen.sh j784s4
                ./firmwareHeaderGen.sh j784s4-hs
                ./firmwareHeaderGen.sh j784s4-hs-fs
                shift
                ;;
        esac
    done

fi

################################################################################
# Commit changes to PDK
if [ "$SKIP_COMMIT" != "YES" ]; then
    $ECHO "Commit changes to PDK"
    cd $SCRIPT_DIR
    git add $SCI_CLIENT_DIR/soc/sysfw/binaries/system-firmware-public-documentation/
    git add $SCI_CLIENT_DIR/soc/sysfw/binaries/sysfw-trace*
    git add $SCI_CLIENT_DIR/soc/sysfw/include/tisci

    for SOC in $SOC_LIST
    do
        case $SOC in
            "j721e")
                git add $SCI_CLIENT_DIR/soc/sysfw/binaries/*j721e*
                git add $SCI_CLIENT_DIR/soc/sysfw/include/j721e
                git add $SCI_CLIENT_DIR/soc/V1
                git add $SCI_CLIENT_DIR/tools/ccsLoadDmsc/j721e
                shift
                ;;
            "j7200")
                git add $SCI_CLIENT_DIR/soc/sysfw/binaries/*j7200*
                git add $SCI_CLIENT_DIR/soc/sysfw/include/j7200
                git add $SCI_CLIENT_DIR/soc/V2
                git add $SCI_CLIENT_DIR/tools/ccsLoadDmsc/j7200
                shift
                ;;
            "j721s2")
                git add $SCI_CLIENT_DIR/soc/sysfw/binaries/*j721s2*
                git add $SCI_CLIENT_DIR/soc/sysfw/include/j721s2
                git add $SCI_CLIENT_DIR/soc/V4
                git add $SCI_CLIENT_DIR/tools/ccsLoadDmsc/j721s2
                shift
                ;;
            "j784s4")
                git add $SCI_CLIENT_DIR/soc/sysfw/binaries/*j784s4*
                git add $SCI_CLIENT_DIR/soc/sysfw/include/j784s4
                git add $SCI_CLIENT_DIR/soc/V6
                git add $SCI_CLIENT_DIR/tools/ccsLoadDmsc/j784s4
                shift
                ;;
        esac
    done

    git commit -m "Migrating to SYSFW version $RELEASE_TAG"
fi

################################################################################
$ECHO "Done."
