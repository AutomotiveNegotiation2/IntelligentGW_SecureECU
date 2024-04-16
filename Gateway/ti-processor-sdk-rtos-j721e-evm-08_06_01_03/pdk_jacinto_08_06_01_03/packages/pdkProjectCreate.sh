# ******************************************************************************
# * FILE PURPOSE: PDK Unit Test and Example Project Creator
# ******************************************************************************
# * FILE NAME: pdkProjectCreate.sh
# *
# * DESCRIPTION: 
# *  The script file is used to create the test and example projects of all
# *  components under PDK. These projects are available in the specified 
# *  workspace.
# *
# * USAGE:
# *  pdkProjectCreate.sh [soc] [board] [endian] [module] [project type] [processor] [SECUREMODE=<yes/no>]
# * 
# *  Description:      (first option is default)
# *  soc           -   AM335x / AM437x / AM571x / AM572x / AM574x / K2E / K2G / K2K / K2H / K2L /
# *                    C6678 / C6657 / DRA72x / DRA75x / DRA78x / OMAPL137 / OMAPL138 / C6748 / am65xx
# *  board         -   all (use "all" for K2X and C66X SOCs)
# *                    -or-
# *                    Refer to pdk_<soc>_<version>\packages\ti\board\lib
# *                    for valid board inputs for the soc
# *  endian        -   little / big
# *  module        -   all
# *                    -or-
# *                    aif2 / bcp / cppi / csl / dfe / emac / fatfs / fm / fftc /
# *                    gpio / hyplnk / i2c / icss_emac / iqn2 / mcasp / mcbsp / mmap / mmcsd /
# *                    nimu / nimu_icss / nwal / osal / pa / pcie / pktlib / pruss / qm / rm /
# *                    sa / serdes-diag / spi / srio / tcp3d / tfw / transportqmss /
# *                    transportsrio / tsip / uart / usb / wdtimer / vps / dcan / dss / lcdc
# *  project type  -   all / example / test  
# *  processor     -   arm / dsp / m4 / mcu / mpu
# *  SECUREMODE    -   yes/no (optional argument). If unspecificed non-secure mode is assumed.
# * 
# *  Example:
# *   a) pdkProjectCreate.sh
# *               - Creates all module projects for the AM335x soc for arm little endian
# *   b) pdkProjectCreate.sh AM437x
# *               - Creates all module projects for the AM437x soc for arm little endian
# *   c) pdkProjectCreate.sh AM437x idkAM437x
# *               - Creates all module projects for idkAM437x device for arm little endian
# *   d) pdkProjectCreate.sh AM571x evmAM571x little
# *               - Creates all module projects for evmAM571x device for arm little endian
# *   e) pdkProjectCreate.sh AM571x evmAM571x little i2c all dsp
# *               - Creates all i2c module projects for evmAM571x device for dsp little endian
# *   f) pdkProjectCreate.sh K2H all little i2c example arm
# *               - Creates i2c module example projects for K2H device for arm little endian
# *   g) pdkProjectCreate.sh C6678 all little hyplnk test dsp
# *               - Creates hyplnk module test projects for C6678 device for dsp little endian
# *   h) pdkProjectCreate.sh K2G evmK2G little mcasp all dsp SECUREMODE=yes
# *               - Creates mcasp module test projects for dsp little endian to be run on evmK2G
# *                 which is in secure mode
# * 
# * Copyright (C) 2012-2019, Texas Instruments, Inc.
# *****************************************************************************

# Lists of valid input parameters - MUST be updated as new input parameters are added
# *****************************************************************************
soc_list=("AM335x" "AM437x" "AM571x" "AM572x" "AM574x" "K2E" "K2K" "K2H" "K2L" "K2G" "C6678" "C6657" "DRA72x" "DRA75x" "DRA78x" "OMAPL137" "OMAPL138" "C6748" "am65xx")
endian_list=("little" "big")
module_list=("all" "aif2" "bcp" "cppi" "csl" "dfe" "emac" "fatfs" "fm" "fftc" "gpio" "gpmc" "hyplnk" "i2c" "icss_emac" "iqn2" "mcasp" "mcbsp" "mmap" "mmcsd" "nimu" "nimu_icss" "nwal" "osal" "pa" "pcie" "pktlib" "pruss" "qm" "rm" "sa" "serdes_diag" "spi" "srio" "tcp3d" "tfw" "transportqmss" "transportsrio" "tsip" "uart" "usb" "wdtimer" "vps" "dcan" "dss" "lcdc" "timeSync")
projectType_list=("all" "example" "test")
proc_list=("arm" "dsp" "m4" "mpu" "mcu")

# Parameter Validation: Check if the argument was passed to the batch file.
# *****************************************************************************
# Argument [soc] is used to set SOC variable.
if [ -n "$1" ]; then
    export SOC="$1"
else
    export SOC="AM335x"
fi

# Argument [board] is used to set BOARD variable.
# This is the board type of the soc for which project are to be created.
if [ -n "$2" ]; then
    export BOARD="$2"
else
    export BOARD="all"
fi

# Argument [endian] is used to set ENDIAN variable.
# This is Endianess of the projects being created.
# Valid Values are 'little' and 'big'. Defaults to 'little'.
if [ -n "$3" ]; then
    export ENDIAN="$3"
else
    export ENDIAN="little"
fi

# Argument [module] is used to set MODULE variable.
# This is specific module for which projects are created.
# Valid Values are LLD name. Defaults to all LLD's.
if [ -n "$4" ]; then
    export MODULE="$4"
else
    export MODULE="all"
fi

# Argument [proj type] is used to set PROJECT_TYPE variable.
# This is the type of projects that are created
# Valid Values are all, example, or test . Defaults to all.
if [ -n "$5" ]; then
    export PROJECT_TYPE="$5"
else
    export PROJECT_TYPE="all"
fi

# Argument [processor] is used to set PROCESSOR variable.
# This is specific processor type for which projects are created.
# Valid Values are arm, dsp, or m4 . Defaults to arm.
if [ -n "$6" ]; then
    export PROCESSOR="$6"
else
    export PROCESSOR="arm"
fi

# Argument [SECUREMODE] is used to set SECUREMODE variable.
# Default to non secure mode if this argument is not specified
if [ -n "$7" ]; then
  if [ "$7" == "SECUREMODE=yes" ]; then
    echo "The board is in secure mode"
    export SECUREMODE="yes"
  else
    echo "The board is non in secure mode"
    export SECUREMODE="no"
  fi 
else
    export SECUREMODE="no"
fi

# If the below entries need to be added for ARM sysbios config files 
export RTSCCFG_ENTRY_SECUREMODE_ARM="
/* Start of lines added for secure device */
var gicHwi = xdc.useModule('ti.sysbios.family.arm.gic.Hwi'); 
gicHwi.enableSecureMode = false; 
gicHwi.BPR = 3; 
gicHwi.NUM_PRIORITY_BITS = 4;
/* End of Lines added for secure device */
"
# If the below entries need to be added for DSP sysbios config files 
export RTSCCFG_ENTRY_SECUREMODE_DSP="
/* Start of lines added for secure device */
var BIOS = xdc.useModule('ti.sysbios.BIOS');
BIOS.useSK = true;
BIOS.setupSecureContext = true;
BIOS.libType = BIOS.LibType_Custom;
/* End of Lines added for secure device */
"
export PDK_SHORT_NAME=$PWD

# This define is used to patch the GP EVM CFG file if the SECUREMODE is enabled.
# Some EVMs like K2G would need the patch, where as AM437x does not in SECURE MODE
# This define will help with the selective patching
export SEC_CFG_FILE_UPDATE_NEEDED="no"
# TI SDK root directory
if [ -z $SDK_INSTALL_PATH ]; then
    export SDK_INSTALL_PATH=__SDK__INSTALL_DIR__
fi

# *****************************************************************************

echo "========================================================================="
echo "Configuration:"
echo "  SOC             :   $SOC"
echo "  BOARD           :   $BOARD"
echo "  ENDIAN          :   $ENDIAN"
echo "  MODULE          :   $MODULE"
echo "  PROJECT_TYPE    :   $PROJECT_TYPE"
echo "  PROCESSOR       :   $PROCESSOR"
echo "  PDK_SHORT_NAME  :   $PDK_SHORT_NAME"
echo "========================================================================="
echo "Checking Configuration..."

error_exit () {
    echo "Exiting..."
    echo "========================================================================="
    exit 1
}

contains () {
    local name=$1[@]
    local list=("${!name}")
    local in_list=0

    for item in "${list[@]}"
    do
        if [ "$2" = "$item" ]; then
            in_list=1
            break
        fi
    done

    if [ $in_list -eq 0 ]; then
        echo "ERROR: $3 ($2) is invalid"
        error_exit
    fi
}

contains soc_list          "$SOC"           "SOC"
contains endian_list       "$ENDIAN"        "Endian"
contains module_list       "$MODULE"        "Module"
contains projectType_list  "$PROJECT_TYPE"  "Project Type"  
contains proc_list         "$PROCESSOR"     "Processor"

if [ $BOARD != "all" ]; then
    if [ $BOARD = "iceAMIC110" ]; then
        if [ $SOC != "AM335x" ]; then
            echo "ERROR: Board ($BOARD) is invalid for the specified SOC ($SOC)"
            error_exit
        fi
    elif [ "${BOARD/$SOC}" = "$BOARD" ]; then
        echo "ERROR: Board ($BOARD) is invalid for the specified SOC ($SOC)"
        error_exit
    fi
fi

if [ $SOC = "AM335x" ]; then
    if [ $PROCESSOR = "dsp" ]; then
        echo "ERROR: The AM335x soc does not contain a DSP processor"
        error_exit
    elif [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The AM335x soc does not contain a M4 processor"
        error_exit
    fi

    if [ $ENDIAN = "big" ]; then
        echo "ERROR: The AM335x soc's arm does not support big endian"
        error_exit
    fi
elif [ $SOC = "AM437x" ]; then
    if [ $PROCESSOR = "dsp" ]; then
        echo "ERROR: The AM437x soc does not contain a DSP processor"
        error_exit
    elif [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The AM437x soc does not contain a M4 processor"
        error_exit
    fi

    if [ $ENDIAN = "big" ]; then
        echo "ERROR: The AM437x soc's arm does not support big endian"
        error_exit
    fi
elif [ $SOC = "AM571x" ]; then
    if [ $ENDIAN = "big" ]; then
        echo "ERROR: The AM571x soc's processor's do not support big endian"
        error_exit
    fi
elif [ $SOC = "AM572x" ]; then
    if [ $ENDIAN = "big" ]; then
        echo "ERROR: The AM572x soc's processor's do not support big endian"
        error_exit
    fi
elif [ $SOC = "AM574x" ]; then
    if [ $ENDIAN = "big" ]; then
        echo "ERROR: The AM574x soc's processor's do not support big endian"
        error_exit
    fi
elif [ $SOC = "K2K" ]; then
    if [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The K2K soc does not contain a M4 processor"
        error_exit
    fi
    if [ $PROCESSOR = "arm" ]; then
        if [ $ENDIAN = "big" ]; then
            echo "ERROR: The K2K soc's processor's do not support big endian"
            error_exit
        fi
    fi
elif [ $SOC = "K2H" ]; then
    if [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The K2H soc does not contain a M4 processor"
        error_exit
    fi
    if [ $PROCESSOR = "arm" ]; then
        if [ $ENDIAN = "big" ]; then
            echo "ERROR: The K2H soc's processor's do not support big endian"
            error_exit
        fi
    fi
elif [ $SOC = "K2E" ]; then
    if [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The K2E soc does not contain a M4 processor"
        error_exit
    fi
    if [ $PROCESSOR = "arm" ]; then
        if [ $ENDIAN = "big" ]; then
            echo "ERROR: The K2E soc's processor's do not support big endian"
            error_exit
        fi
    fi
elif [ $SOC = "K2L" ]; then
    if [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The K2L soc does not contain a M4 processor"
        error_exit
    fi
    if [ $PROCESSOR = "arm" ]; then
        if [ $ENDIAN = "big" ]; then
            echo "ERROR: The K2L soc's processor's do not support big endian"
            error_exit
        fi
    fi
elif [ $SOC = "K2G" ]; then
    if [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The K2G soc does not contain a M4 processor"
        error_exit
    fi
    if [ $PROCESSOR = "arm" ]; then
        if [ $ENDIAN = "big" ]; then
            echo "ERROR: The K2G soc's processor's do not support big endian"
            error_exit
        fi
    fi
elif [ $SOC = "OMAPL137" ]; then
    if [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The OMAPL137 soc does not contain a M4 processor"
        error_exit
    fi
    if [ $PROCESSOR = "arm" ]; then
        if [ $ENDIAN = "big" ]; then
            echo "ERROR: The OMAPL137 soc's processor's do not support big endian"
            error_exit
        fi
    fi
elif [ $SOC = "OMAPL138" ]; then
    if [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The OMAPL138 soc does not contain a M4 processor"
        error_exit
    fi
    if [ $PROCESSOR = "arm" ]; then
        if [ $ENDIAN = "big" ]; then
            echo "ERROR: The OMAPL138 soc's processor's do not support big endian"
            error_exit
        fi
    fi
elif [ $SOC = "C6748" ]; then
    if [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The C6748 soc does not contain a M4 processor"
        error_exit
    fi
    if [ $PROCESSOR = "arm" ]; then
       echo "ERROR: The C6748 soc does not contain an arm processor"
       error_exit
    fi
    if [ $PROCESSOR = "dsp" ]; then
        if [ $ENDIAN = "big" ]; then
            echo "ERROR: The C6748 soc's processor's do not support big endian"
            error_exit
        fi
    fi
elif [ $SOC = "C6678" ]; then
    if [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The C6678 soc does not contain a M4 processor"
        error_exit
    fi
    if [ $PROCESSOR = "arm" ]; then
        echo "ERROR: The C6678 soc does not contain an arm processor"
        error_exit
    fi
elif [ $SOC = "C6657" ]; then
    if [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The C6657 soc does not contain a M4 processor"
        error_exit
    fi
    if [ $PROCESSOR = "arm" ]; then
        echo "ERROR: The C6657 soc does not contain an arm processor"
        error_exit
    fi
elif [ $SOC = "DRA72x" ]; then
    if [ $ENDIAN = "big" ]; then
        echo "ERROR: The DRA72x soc's processor's do not support big endian"
        error_exit
    fi
elif [ $SOC = "DRA75x" ]; then
    if [ $ENDIAN = "big" ]; then
        echo "ERROR: The DRA75x soc's processor's do not support big endian"
        error_exit
    fi
elif [ $SOC = "DRA78x" ]; then
    if [ $ENDIAN = "big" ]; then
        echo "ERROR: The DRA78x soc's processor's do not support big endian"
        error_exit
    fi
elif [ $SOC = "am65xx" ]; then
    if [ $PROCESSOR = "m4" ]; then
        echo "ERROR: The am65xx soc does not contain a M4 processor"
        error_exit
    fi
    if [ $PROCESSOR = "dsp" ]; then
        echo "ERROR: The am65xx soc does not contain a DSP processor"
        error_exit
    fi
    if [ $ENDIAN = "big" ]; then
        echo "ERROR: The am65xx soc's processor's do not support big endian"
        error_exit
    fi
else
    echo "ERROR: Invalid soc"
    error_exit
fi

# *****************************************************************************
# * Version Information of the various tools etc required to build the test
# * projects. Customers are free to modify these to meet their requi#ents.
# *****************************************************************************

# export to 'no' when using QT, EVM, VDB, or other hardware. export to 'yes'
# only when using the simulator.
export IS_SIMULATOR_SUPPORT_NEEDED=no

# Tools root directory
if [ -z $CCS_INSTALL_PATH ]; then
    export CCS_INSTALL_PATH=~/ti/ccs930/ccs
fi

# Workspace where the PDK projects will be created.
export MY_WORKSPACE=$PDK_SHORT_NAME/MyExampleProjects

# macros.ini location
export MACROS_FILE=$PDK_SHORT_NAME/macros.ini

# This is the format of the executable being created
# Valid Values are 'ELF' and 'COFF'
export OUTPUT_FORMAT=ELF

# Version of CG-Tools
export CGT_VERSION=8.3.2

# Version of CG-ARM-Tools for M4
export CGT_M4_VERSION=18.12.5.LTS

# Version of XDC
export XDC_VERSION=3.55.02.22

# Version of BIOS
export BIOS_VERSION=6.76.03.01

# Version of CG-Tools for ARM
export CGT_VERSION_ARM=GNU_7.2.1:Linaro

# Version of CG-Tools for A53
export CGT_VERSION_ARM_A53="GNU_7.2.1:Linaro aarch64"

# Version of the IPC
export IPC_VERSION=3_50_04_08

# EDMA3 Version 
export EDMA_VERSION=2.12.05.30E

# Version of the PDK
export PDK_VERSION=08_06_01_03

# Version of the NDK 
export NDK_VERSION=3.61.01.01

# Version of UIA
export UIA_VERSION=2.30.01.02

# Version of CG-Tools for ARM
export CGT_VERSION_ARM9=18.1.5.LTS

# PDK Part Number & Platform name
if [ "$SOC" = "K2K" ]; then
    export PDK_PARTNO=TCI6638
    export PDK_ECLIPSE_ID=com.ti.pdk.k2hk
    export RTSC_PLATFORM_NAME=ti.platforms.evmTCI6638K2K
    if [ "$PROCESSOR" == "arm" ]; then
        export RTSC_TARGET=gnu.targets.arm.A15F
        export CCS_DEVICE="Cortex A.TCI6638K2K"
    fi
elif [ "$SOC" = "K2H" ]; then
    export PDK_PARTNO=TCI6636
    export PDK_ECLIPSE_ID=com.ti.pdk.k2hk
    export RTSC_PLATFORM_NAME=ti.platforms.evmTCI6636K2H
    if [ "$PROCESSOR" == "arm" ]; then
        export RTSC_TARGET=gnu.targets.arm.A15F
        export CCS_DEVICE="Cortex A.66AK2H12"
    fi
elif [ "$SOC" = "K2L" ]; then
    export PDK_PARTNO=TCI6630
    export PDK_ECLIPSE_ID=com.ti.pdk.k2l
    export RTSC_PLATFORM_NAME=ti.platforms.evmTCI6630K2L
    if [ "$PROCESSOR" == "arm" ]; then
        export RTSC_TARGET=gnu.targets.arm.A15F
        export CCS_DEVICE="Cortex A.TCI6630K2L"
    fi
elif [ "$SOC" = "K2E" ]; then
    export PDK_PARTNO=66AK2E05
    export PDK_ECLIPSE_ID=com.ti.pdk.k2e
    export RTSC_PLATFORM_NAME=ti.platforms.evmC66AK2E
    if [ "$PROCESSOR" == "arm" ]; then
        export RTSC_TARGET=gnu.targets.arm.A15F
        export CCS_DEVICE="Cortex A.66AK2E05"
    fi
elif [ "$SOC" = "OMAPL137" ]; then
    export PDK_PARTNO=OMAPL137
    export PDK_ECLIPSE_ID=com.ti.pdk.omapl137
    export RTSC_PLATFORM_NAME=ti.platforms.evmOMAPL137
    if [ "$PROCESSOR" == "arm" ]; then
        export RTSC_TARGET=ti.targets.arm.elf.Arm9
        export CCS_DEVICE="ARM9.OMAPL137"
    fi
elif [ "$SOC" = "OMAPL138" ]; then
    export PDK_PARTNO=OMAPL138
    export PDK_ECLIPSE_ID=com.ti.pdk.omapl138
    export RTSC_PLATFORM_NAME=ti.platforms.evmOMAPL138
    if [ "$PROCESSOR" == "arm" ]; then
        export RTSC_TARGET=ti.targets.arm.elf.Arm9
        export CCS_DEVICE="ARM9.OMAPL138"
    fi
elif [ "$SOC" = "C6748" ]; then
# C6748 is the alias for OMAPL138 where the OMAPL138 settings will
# be used to create projects for C6748 SOC.
    export SOC=OMAPL138
    export BOARD=lcdkOMAPL138
    export PDK_PARTNO=OMAPL138
    export PDK_ECLIPSE_ID=com.ti.pdk.omapl138
    export RTSC_PLATFORM_NAME=ti.platforms.evmOMAPL138
    if [ "$PROCESSOR" == "arm" ]; then
        export RTSC_TARGET=ti.targets.arm.elf.Arm9
        export CCS_DEVICE="ARM9.OMAPL138"
    fi
elif [ "$SOC" = "K2G" ]; then
    export PDK_PARTNO=66AK2G02
     if [ "$SECUREMODE" == "yes" ]; then
      # Set the board to evmK2G as BOARD is being used to find example project files by name
        export PDK_ECLIPSE_ID=com.ti.pdk.k2g-hs
        export SEC_CFG_FILE_UPDATE_NEEDED="yes"
     else
        export PDK_ECLIPSE_ID=com.ti.pdk.k2g
     fi 
    export RTSC_PLATFORM_NAME=ti.platforms.evmTCI66AK2G02
    if [ "$PROCESSOR" == "arm" ]; then
        export RTSC_TARGET=gnu.targets.arm.A15F
        export CCS_DEVICE="Cortex A.66AK2G02"
    fi
elif [ "$SOC" = "AM571x" ]; then
    export PDK_PARTNO=AM571X
    export PDK_ECLIPSE_ID=com.ti.pdk.am57xx
    export RTSC_PLATFORM_NAME=ti.platforms.idkAM571X
    if [ "$PROCESSOR" = "arm" ]; then
        export RTSC_TARGET=gnu.targets.arm.A15F
        export CCS_DEVICE="Cortex A.AM5728_RevA"
    elif [ "$PROCESSOR" == "m4" ]; then
        export RTSC_TARGET=ti.targets.arm.elf.M4
        export CCS_DEVICE="Cortex M.AM5728_RevA"
    fi
elif [ "$SOC" == "AM572x" ]; then
    export PDK_PARTNO=AM572X
    export PDK_ECLIPSE_ID=com.ti.pdk.am57xx
    if [ "$BOARD" == "idkAM572x" ]; then
        export RTSC_PLATFORM_NAME=ti.platforms.idkAM572X
    else
        export RTSC_PLATFORM_NAME=ti.platforms.evmAM572X
    fi
    if [ "$PROCESSOR" == "arm" ]; then
        export RTSC_TARGET=gnu.targets.arm.A15F
        export CCS_DEVICE="Cortex A.AM5728_RevA"
    elif [ "$PROCESSOR" == "m4" ]; then
        export RTSC_TARGET=ti.targets.arm.elf.M4
        export CCS_DEVICE="Cortex M.AM5728_RevA"
    fi
elif [ "$SOC" = "AM574x" ]; then
    export PDK_PARTNO=AM574X
    export PDK_ECLIPSE_ID=com.ti.pdk.am57xx
    export RTSC_PLATFORM_NAME=ti.platforms.idkAM572X
    if [ "$PROCESSOR" = "arm" ]; then
        export RTSC_TARGET=gnu.targets.arm.A15F
        export CCS_DEVICE="Cortex A.AM5728_RevA"
    elif [ "$PROCESSOR" == "m4" ]; then
        export RTSC_TARGET=ti.targets.arm.elf.M4
        export CCS_DEVICE="Cortex M.AM5728_RevA"
    fi
elif [ "$SOC" == "DRA72x" ]; then
    export PDK_PARTNO=DRA72x
    export PDK_ECLIPSE_ID=com.ti.pdk.dra7xx
    export RTSC_PLATFORM_NAME=ti.platforms.evmDRA7XX
    if [ "$PROCESSOR" == "arm" ]; then
        export RTSC_TARGET=gnu.targets.arm.A15F
        export CCS_DEVICE="Cortex A.DRA72x"
    elif [ "$PROCESSOR" == "m4" ]; then
        export RTSC_TARGET=ti.targets.arm.elf.M4
        export CCS_DEVICE="Cortex M.DRA72x"
    fi
elif [ "$SOC" == "DRA75x" ]; then
    export PDK_PARTNO=DRA75x
    export PDK_ECLIPSE_ID=com.ti.pdk.dra7xx
    export RTSC_PLATFORM_NAME=ti.platforms.evmDRA7XX
    if [ "$PROCESSOR" == "arm" ]; then
        export RTSC_TARGET=gnu.targets.arm.A15F
        export CCS_DEVICE="Cortex A.DRA75x_DRA74x"
    elif [ "$PROCESSOR" == "m4" ]; then
        export RTSC_TARGET=ti.targets.arm.elf.M4
        export CCS_DEVICE="Cortex M.DRA75x_DRA74x"
    fi
elif [ "$SOC" == "DRA78x" ]; then
    export PDK_PARTNO=DRA78x
    export PDK_ECLIPSE_ID=com.ti.pdk.dra7xx
    export RTSC_PLATFORM_NAME=ti.platforms.evmTDA3XX
    if [ "$PROCESSOR" == "m4" ]; then
        export RTSC_TARGET=ti.targets.arm.elf.M4
        export CCS_DEVICE="Cortex M.TDA3x"
    fi
elif [ "$SOC" == AM335x ]; then
    export PDK_PARTNO=AM335
    export PDK_ECLIPSE_ID=com.ti.pdk.am335x
    export RTSC_PLATFORM_NAME=ti.platforms.evmAM3359
    export RTSC_TARGET=gnu.targets.arm.A8F
    export CCS_DEVICE="Cortex A.AM3359.ICE_AM3359"
elif [ "$SOC" = "AM437x" ]; then
    export PDK_PARTNO=AM437
     if [ "$SECUREMODE" == "yes" ]; then
      # Set the board to am437x-hs as BOARD is being used to find example project files by name
        export PDK_ECLIPSE_ID=com.ti.pdk.am437x-hs
      # No cfg file updates are required for AM437x-hs
        export SEC_CFG_FILE_UPDATE_NEEDED="no"
     else
        export PDK_ECLIPSE_ID=com.ti.pdk.am437x
     fi 
    export RTSC_PLATFORM_NAME=ti.platforms.evmAM437X
    export RTSC_TARGET=gnu.targets.arm.A9F
    export CCS_DEVICE="Cortex A.AM4379.IDK_AM437X"
elif [ "$SOC" = "C6678" ]; then
    export PDK_PARTNO=C6678L
    export PDK_ECLIPSE_ID=com.ti.pdk.c667x
    export RTSC_PLATFORM_NAME=ti.platforms.evm6678
elif [ "$SOC" = "C6657" ]; then
    export PDK_PARTNO=C6657
    export PDK_ECLIPSE_ID=com.ti.pdk.c665x
    export RTSC_PLATFORM_NAME=ti.platforms.evm6657
elif [ "$SOC" = "am65xx" ]; then
    export PDK_PARTNO=AM65XX
    export PDK_ECLIPSE_ID=com.ti.pdk.am65xx
    if [ "$PROCESSOR" = "mpu" ]; then
        export RTSC_PLATFORM_NAME=ti.platforms.cortexA:AM65X
        export RTSC_TARGET=gnu.targets.arm.A53F
        export CCS_DEVICE="Cortex A.AM6548"
    elif [ "$PROCESSOR" == "mcu" ]; then
        export RTSC_PLATFORM_NAME=ti.platforms.cortexR:AM65X
        export RTSC_TARGET=ti.targets.arm.elf.R5F
        export CCS_DEVICE="Cortex R.AM6548"
    fi
else
    # Need to exit the batch script cleanly 
    export PDK_PARTNO=TCI6634
    export PDK_ECLIPSE_ID=ti.pdk
    export RTSC_PLATFORM_NAME=ti.platforms.simKepler
fi

# RTSC Target
# - Please ensure that you select this taking into account the
#   OUTPUT_FORMAT and the RTSC_PLATFORM_NAME 
if [ "$PROCESSOR" = "dsp" ]; then
    if [ "$ENDIAN" = "big" ]; then
        export RTSC_TARGET=ti.targets.elf.C66_big_endian
        export CCS_DEVICE="com.ti.ccstudio.deviceModel.C6000.GenericC64xPlusDevice"
		export DSP_TYPE=c66
    else
        if [ "$SOC" = "OMAPL137" ]; then
            export RTSC_TARGET=ti.targets.elf.C674
            export CCS_DEVICE="com.ti.ccstudio.deviceModel.C6000.GenericC674xDevice"
            export DSP_TYPE=c674x
		elif [ "$SOC" = "OMAPL138" ]; then
            export RTSC_TARGET=ti.targets.elf.C674
            export CCS_DEVICE="com.ti.ccstudio.deviceModel.C6000.GenericC674xDevice"
            export DSP_TYPE=c674x
		else
            export RTSC_TARGET=ti.targets.elf.C66
            export CCS_DEVICE="com.ti.ccstudio.deviceModel.C6000.GenericC64xPlusDevice"
            export DSP_TYPE=c66
        fi
    fi
fi

echo "  PDK_PARTNO         : $PDK_PARTNO"
echo "  PDK_ECLIPSE_ID     : $PDK_ECLIPSE_ID"
echo "  RTSC_PLATFORM_NAME : $RTSC_PLATFORM_NAME"
echo "  RTSC_TARGET        : $RTSC_TARGET"
echo "  CCS_DEVICE         : $CCS_DEVICE"
# *****************************************************************************
# *****************************************************************************
#                 Please do NOT change anything below this
# *****************************************************************************
# *****************************************************************************

# export auto create command by default for use with CCSv8
export AUTO_CREATE_COMMAND=eclipse/ccstudio

# export project for Silicon or QT by default
export SIMULATOR_SUPPORT_DEFINE=

echo "*****************************************************************************"
echo "Detecting all projects in PDK and importing them in the workspace $MY_WORKSPACE"


export RTSC_PRODUCTS="com.ti.rtsc.SYSBIOS:$BIOS_VERSION;$PDK_ECLIPSE_ID:$PDK_VERSION"

if [ -d ${SDK_INSTALL_PATH}/edma3_lld_${EDMA_VERSION//./_} ]; then
	export RTSC_EDMA=";com.ti.sdo.edma3:$EDMA_VERSION"
fi

if [[ "$SOC" != "AM335x" && "$SOC" != "AM437x" ]]; then
if [ -d ${SDK_INSTALL_PATH}/ipc_${IPC_VERSION//./_} ]; then
	export RTSC_IPC=";com.ti.rtsc.IPC:$IPC_VERSION"
fi
fi

if [ -d ${SDK_INSTALL_PATH}/ndk_${NDK_VERSION//./_} ]; then
	export RTSC_NDK=";com.ti.rtsc.NDK:${NDK_VERSION}-eng"
fi
if [ -d ${SDK_INSTALL_PATH}/uia_${UIA_VERSION//./_} ]; then
	export RTSC_UIA=";com.ti.uia:$UIA_VERSION"
fi

export RTSC_PRODUCTS="${RTSC_PRODUCTS}${RTSC_EDMA}${RTSC_IPC}${RTSC_NDK}${RTSC_UIA}"

# Set MODULE to null string so it picks up all projects of PROCESSOR
if [ "$MODULE" = "all" ]; then
    MODULE=""
fi

# Set BOARD to equal the SOC if BOARD is set to "all".  All projects for the
# SOC will be picked up
# Additionally for AM335x, check for AMIC110 board
export AMIC110BOARD=
if [ "$BOARD" = "all" ]; then
    BOARD="$SOC"
    if [ "$SOC" = "AM335x" ]; then
        AMIC110BOARD="-o -iname *$MODULE*AMIC110*arm*roject.txt"
    fi
fi

# Set PROJECT_TYPE to null string so it picks up all project types 
if [ "$PROJECT_TYPE" = "all" ]; then
    PROJECT_TYPE=""
fi

if [ "$SOC" = "OMAPL137" ]; then
	export LINKER_OPT=""
	export COMPILER_OPT=""
	export COMPILER=$CGT_VERSION_ARM9
elif [ "$SOC" = "OMAPL138" ]; then
	export LINKER_OPT=""
	export COMPILER_OPT=""
	export COMPILER=$CGT_VERSION_ARM9
elif [ "$SOC" = "am65xx" ]; then
	export LINKER_OPT=""
	export COMPILER_OPT=""
	export COMPILER="$CGT_VERSION_ARM_A53"
else
	export LINKER_OPT=\"-L\${BIOS_CG_ROOT}/packages/gnu/targets/arm/libs/install-native/arm-none-eabi/lib/hard\ --specs=nano.specs\"
	export COMPILER_OPT=\"-I\${CG_TOOL_ROOT}/arm-none-eabi/include/newlib-nano\"
	export COMPILER=$CGT_VERSION_ARM
fi

ccs_create_dsp()
{
    echo Detected Project $1
    textfile=${1#*/}

    ccs_proj_name=${textfile%.*}
    # If the board is in secure mode , a few lines need to be added to sysbios config file for the application
    if [ "$SEC_CFG_FILE_UPDATE_NEEDED" == "yes" ]; then
       # For SECUREMODE=yes, the cc projects are appended with _HS so that they can coexist with non-HS projects
       ccs_proj_name=$ccs_proj_name"_HS"
       # Check if the secure device configuration exists on the application sysbios config file.
       # if not add it to the config file.
       cfgfile=$(grep "\.cfg" $textfile| sed -e  's/.*\/ti/\/ti/'|sed -e  's/"//g'| sed -e "s|\.*\/ti|${PDK_INSTALL_PATH}\/ti|g")
       securecfg_occurance=$(grep -c "Start of lines added for secure device" $cfgfile)
       if [ $securecfg_occurance -eq 0 ]; then
          echo "Adding secure device configuration file for sysbios configuration file $cfgfile .."
          echo "${RTSCCFG_ENTRY_SECUREMODE_DSP}" >> $cfgfile
       fi
    fi

$CCS_INSTALL_PATH/$AUTO_CREATE_COMMAND -nosplash -data $MY_WORKSPACE -application com.ti.ccstudio.apps.projectCreate -ccs.name ${ccs_proj_name} -ccs.outputFormat $OUTPUT_FORMAT -ccs.setCompilerOptions "-DUSE_BIOS" -ccs.device "$CCS_DEVICE" -ccs.endianness $ENDIAN -ccs.kind executable -ccs.cgtVersion $CGT_VERSION -rtsc.xdcVersion $XDC_VERSION -rtsc.enableDspBios -rtsc.biosVersion $BIOS_VERSION -rtsc.buildProfile "debug" -rtsc.products "$RTSC_PRODUCTS" -rtsc.platform "$RTSC_PLATFORM_NAME" -rtsc.target $RTSC_TARGET -ccs.rts libc.a -ccs.args $textfile -ccs.overwrite full -ccs.setPostBuildStep "\${TI_PDK_INSTALL_DIR}/packages/pdkAppImageCreate.sh \${TI_PDK_INSTALL_DIR}/packages \${CG_TOOL_ROOT} \${PROJECT_LOC}/\${ConfigName} \${ProjName} $SOC $PROCESSOR" \;

    echo "Copying macros.ini"
    cp $PDK_SHORT_NAME/macros.ini $MY_WORKSPACE/${ccs_proj_name}
}

ccs_create_arm()
{
    echo Detected Project $1
    textfile=${1#*/}
    ccs_proj_name=${textfile%.*}
    # If the board is in secure mode , a few lines need to be added to sysbios config file for the application
    if [ "$SEC_CFG_FILE_UPDATE_NEEDED" == "yes" ]; then
       # For SECUREMODE=yes, the cc projects are appended with _HS so that they can coexist with non-HS projects
       ccs_proj_name=$ccs_proj_name"_HS"
       # Check if the secure device configuration exists on the application sysbios config file.
       # if not add it to the config file.
       cfgfile=$(grep "\.cfg" $textfile| sed -e  's/.*\/ti/\/ti/'|sed -e  's/"//g'| sed -e "s|\.*\/ti|${PDK_INSTALL_PATH}\/ti|g")
       securecfg_occurance=$(grep -c "Start of lines added for secure device" $cfgfile)
       if [ $securecfg_occurance -eq 0 ]; then
          echo "Adding secure device configuration file for sysbios configuration file $cfgfile .."
          echo "${RTSCCFG_ENTRY_SECUREMODE_ARM}" >> $cfgfile
       fi
    fi
 
    #Run CCS create command specific to baremetal and OS projects
    if [[ "$textfile" =~ "nonOS" ]]; then
       $CCS_INSTALL_PATH/$AUTO_CREATE_COMMAND -nosplash -data $MY_WORKSPACE -application com.ti.ccstudio.apps.projectCreate -ccs.cmd "" -ccs.name ${ccs_proj_name} -ccs.outputFormat $OUTPUT_FORMAT -ccs.device "$CCS_DEVICE" -ccs.endianness $ENDIAN -ccs.kind executable -ccs.cgtVersion "$COMPILER"  -ccs.args $textfile -ccs.overwrite full  -ccs.setPostBuildStep $(CG_TOOL_ROOT)/bin/arm-none-eabi-objcopy -O binary ${ccs_proj_name}.out ${ccs_proj_name}.bin

        #REM Deletes the startup file generated defaultly by CCS tool
        rm $MY_WORKSPACE/${ccs_proj_name}/*.S
    else
        $CCS_INSTALL_PATH/$AUTO_CREATE_COMMAND -nosplash -data $MY_WORKSPACE -application com.ti.ccstudio.apps.projectCreate -ccs.cmd "" -ccs.name ${ccs_proj_name} -ccs.outputFormat $OUTPUT_FORMAT -ccs.setLinkerOptions "$LINKER_OPT" -ccs.setCompilerOptions "$COMPILER_OPT" -ccs.setCompilerOptions "-DUSE_BIOS" -ccs.device "$CCS_DEVICE" -ccs.endianness $ENDIAN -ccs.kind executable -ccs.cgtVersion "$COMPILER" -rtsc.xdcVersion $XDC_VERSION -rtsc.enableDspBios -rtsc.biosVersion $BIOS_VERSION -rtsc.buildProfile "debug" -rtsc.products "$RTSC_PRODUCTS" -rtsc.platform "$RTSC_PLATFORM_NAME" -rtsc.target $RTSC_TARGET -ccs.rts libc.a libgcc.a libuart.a libm.a libnosys.a -ccs.args $textfile -ccs.overwrite full -ccs.setPostBuildStep "\${TI_PDK_INSTALL_DIR}/packages/pdkAppImageCreate.sh \${TI_PDK_INSTALL_DIR}/packages \${CG_TOOL_ROOT} \${PROJECT_LOC}/\${ConfigName} \${ProjName} $SOC $PROCESSOR" \;
    fi

    echo "Copying macros.ini"
    cp $PDK_SHORT_NAME/macros.ini $MY_WORKSPACE/${ccs_proj_name}
}

ccs_create_m4()
{
    echo Detected Project $1
    textfile=${1#*/}

    $CCS_INSTALL_PATH/$AUTO_CREATE_COMMAND -nosplash -data $MY_WORKSPACE -application com.ti.ccstudio.apps.projectCreate -ccs.cmd "" -ccs.name ${textfile%.*} -ccs.outputFormat $OUTPUT_FORMAT -ccs.setCompilerOptions "-DUSE_BIOS" -ccs.device "$CCS_DEVICE" -ccs.endianness $ENDIAN -ccs.kind executable -ccs.cgtVersion $CGT_M4_VERSION -rtsc.xdcVersion $XDC_VERSION -rtsc.enableDspBios -rtsc.biosVersion $BIOS_VERSION -rtsc.buildProfile "debug" -rtsc.products "$RTSC_PRODUCTS" -rtsc.platform "$RTSC_PLATFORM_NAME" -rtsc.target $RTSC_TARGET -ccs.rts libc.a libgcc.a libuart.a libm.a libnosys.a -ccs.args $textfile -ccs.overwrite full -ccs.setPostBuildStep "\${TI_PDK_INSTALL_DIR}/packages/pdkAppImageCreate.sh \${TI_PDK_INSTALL_DIR}/packages \${CG_TOOL_ROOT} \${PROJECT_LOC}/\${ConfigName} \${ProjName} $SOC $PROCESSOR" \;

    echo "Copying macros.ini"
    cp $PDK_SHORT_NAME/macros.ini $MY_WORKSPACE/${textfile%.*}
}
ccs_create_r5()
{
    echo Detected Project $1
    textfile=${1#*/}

    $CCS_INSTALL_PATH/$AUTO_CREATE_COMMAND -nosplash -data $MY_WORKSPACE -application com.ti.ccstudio.apps.projectCreate -ccs.cmd "" -ccs.name ${textfile%.*} -ccs.outputFormat $OUTPUT_FORMAT -ccs.setCompilerOptions "-DUSE_BIOS" -ccs.device "$CCS_DEVICE" -ccs.endianness $ENDIAN -ccs.kind executable -ccs.cgtVersion $CGT_M4_VERSION -rtsc.xdcVersion $XDC_VERSION -rtsc.enableDspBios -rtsc.biosVersion $BIOS_VERSION -rtsc.buildProfile "debug" -rtsc.products "$RTSC_PRODUCTS" -rtsc.platform "$RTSC_PLATFORM_NAME" -rtsc.target $RTSC_TARGET -ccs.rts libc.a libgcc.a libuart.a libm.a libnosys.a -ccs.args $textfile -ccs.overwrite full -ccs.setPostBuildStep "\${TI_PDK_INSTALL_DIR}/packages/pdkAppImageCreate.sh \${TI_PDK_INSTALL_DIR}/packages \${CG_TOOL_ROOT} \${PROJECT_LOC}/\${ConfigName} \${ProjName} $SOC $PROCESSOR" \;

    echo "Copying macros.ini"
    cp $PDK_SHORT_NAME/macros.ini $MY_WORKSPACE/${textfile%.*}
}

export -f ccs_create_dsp
export -f ccs_create_arm
export -f ccs_create_m4

if [ "$PROCESSOR" = "dsp" ]; then
	find -iname "*$MODULE*$BOARD*$DSP_TYPE*$PROJECT_TYPE*roject.txt" -execdir bash -c 'ccs_create_dsp {}' \;
    if [ $(find -iname "*$MODULE*$BOARD*$DSP_TYPE*$PROJECT_TYPE*roject.txt" | wc -l) -eq 0 ]; then
       echo "No projects detected"
    fi
elif [ "$PROCESSOR" = "arm" ] || [ "$PROCESSOR" = "mpu" ]; then
    find \( -iname "*$MODULE*$BOARD*$PROCESSOR*$PROJECT_TYPE*roject.txt" $AMIC110BOARD \) -execdir bash -c 'ccs_create_arm {}' \;
    if [ $(find \( -iname "*$MODULE*$BOARD*$PROCESSOR*$PROJECT_TYPE*roject.txt" $AMIC110BOARD \) | wc -l) -eq 0 ]; then
       echo "No projects detected"
    fi
elif [ "$PROCESSOR" = "m4" ]|| [ "$PROCESSOR" = "mcu" ]; then
    find -iname "*$MODULE*$BOARD*$PROCESSOR*$PROJECT_TYPE*roject.txt" -execdir bash -c 'ccs_create_m4 {}' \;
    if [ $(find -iname "*$MODULE*$BOARD*$PROCESSOR*$PROJECT_TYPE*roject.txt" | wc -l) -eq 0 ]; then
       echo "No projects detected"
    fi
else
    echo "$PROCESSOR is an invalid processor"
fi

echo "Project generation complete"
echo "*****************************************************************************"
