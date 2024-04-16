#
# Utility script to install all dependant components not included in the
# SDK
#
# - Make sure wget, apt-get, curl proxies are set
#   if required to access these tools from behind corporate firewall.
# - Make sure you have sudo access
# - Tested on Ubuntu 18.04
#
# IMPORANT NOTE:
#   TI provides this as is and may not work as expected on all systems,
#   Please review the contents of this script and modify as needed
#   for your environment
#
#
THIS_SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
source ${THIS_SCRIPT_DIR}/board_env.sh
if [ $? -ne 0 ]
then
    exit 1
fi

PSDKLA_ROOTFS=tisdk-${TISDK_IMAGE}-image-${TI_DEV_BOARD}.tar.xz
PSDKLA_BOOTFS=boot-${TI_DEV_BOARD}.tar.gz
ATF_TAG=2fcd408bb3a6756767a43c073c597cef06e7f2d5
OPTEE_TAG=8e74d47616a20eaa23ca692f4bbbf917a236ed94
TIOVX_KERNELS_TAG=EDGEAI_APP_STACK_08_06_00_02
TIOVX_MODULES_TAG=EDGEAI_APP_STACK_08_06_00_02
GST_PLUGINS_TAG=EDGEAI_APP_STACK_08_06_00_02

skip_sudo=0
skip_linux=0
firmware_only=0

POSITIONAL=()
while [[ $# -gt 0 ]]
do
key="$1"
case $key in
    --skip_sudo)
    skip_sudo=1
    shift # past argument
    ;;
    --qnx_sbl)
    skip_linux=1
    shift # past argument
    ;;
    --firmware_only)
    skip_linux=1
    firmware_only=1
    shift # past argument
    ;;
    -h|--help)
    echo Usage: $0 [options]
    echo
    echo Options,
    echo --skip_sudo     use this option to skip steps that need sudo command
    echo --qnx_sbl       use this option for setting up SDK for QNX SBL only, skipping SPL u-boot setup steps
    echo --firmware_only use this option for setting up SDK for Firmware Build only, skipping linux build dependencies
    exit 0
    ;;
esac
done
set -- "${POSITIONAL[@]}" # restore positional parameters

# Track which packages didn't install then print out at the end
declare -a err_packages

if [ $skip_sudo -eq 0 ]
then
    echo "[dof] Creating/Updating system link to libDOF.so ..."
    sudo ln -sf $PWD/j7_c_models/lib/PC/x86_64/LINUX/release/libDOF.so /usr/lib/x86_64-linux-gnu/libDOF.so
    sudo ln -sf $PWD/j7_c_models/lib/PC/x86_64/LINUX/release/libglbce.so /usr/lib/x86_64-linux-gnu/libApicalSIM.so.1

    sudo apt-get update
    declare -a arr=("gcc-5" "g++-5" "libtinfo5" "libpng-dev" "zlib1g-dev" "libtiff-dev" "libsdl2-dev" "libsdl2-image-dev" \
        "graphviz" "graphviz-dev" "build-essential" "libxmu-dev" "libxi-dev" "libgl-dev" "libosmesa-dev" "python3" "python3-pip" "curl"    \
        "libz1:i386" "libc6-dev-i386" "libc6:i386" "libstdc++6:i386" "g++-multilib" "git" "diffstat" "texinfo"\
        "gawk" "chrpath" "libfreetype6-dev" "mono-runtime" "flex" "libssl-dev" "u-boot-tools" "libdevil-dev"  \
        "bison" "python3-pyelftools" "python3-dev" "libx11-dev" "pxz" "libglew-dev" "xz-utils" "python3-bs4"  \
        "cmake" "ninja-build")

    if ! sudo apt-get install -y "${arr[@]}"; then
        for i in "${arr[@]}"
        do
            if ! sudo apt-get install -y "$i"; then
               err_packages+=("$i")
            fi
        done
    fi
else
    echo ""
    echo "Skipping apt-get install, ensure all required packages are installed on the machine by sudo user"
    echo ""
fi

if [ $skip_linux -eq 0 ]
then
    echo "[psdkla ${PSDKLA_ROOTFS}] Checking ..."
    if [ ! -d targetfs ]
    then
        if [ -f ${PSDKLA_ROOTFS} ]
        then
            echo "[psdkla ${PSDKLA_ROOTFS}] Installing files ..."
            mkdir targetfs
            tar xf ${PSDKLA_ROOTFS} -C targetfs/
        else
            echo
            echo "ERROR: Missing $PWD/${PSDKLA_ROOTFS}.  Download and try again"
            exit -1
        fi
    fi
    echo "[psdkla ${PSDKLA_ROOTFS}] Done "

    echo "[psdkla ${PSDKLA_BOOTFS}] Checking ... "
    if [ ! -d bootfs ]
    then
        if [ -f ${PSDKLA_BOOTFS} ]
        then
            echo "[psdkla ${PSDKLA_BOOTFS}] Installing files ..."
            mkdir bootfs
            tar xf ${PSDKLA_BOOTFS} -C bootfs/
        else
            echo
            echo "ERROR: Missing $PWD/${PSDKLA_BOOTFS}.  Download and try again"
            exit -1
        fi
    fi
    echo "[psdkla ${PSDKLA_BOOTFS}] Done "
fi

if [ $firmware_only -eq 0 ]
then
    echo "[gcc-arm-9.2-2019.12-x86_64-aarch64-none-elf] Checking ..."
    if [ ! -d gcc-arm-9.2-2019.12-x86_64-aarch64-none-elf ]
    then
        wget https://developer.arm.com/-/media/Files/downloads/gnu-a/9.2-2019.12/binrel/gcc-arm-9.2-2019.12-x86_64-aarch64-none-elf.tar.xz --no-check-certificate
        tar xvf gcc-arm-9.2-2019.12-x86_64-aarch64-none-elf.tar.xz > /dev/null
        rm gcc-arm-9.2-2019.12-x86_64-aarch64-none-elf.tar.xz
    fi
    echo "[gcc-arm-9.2-2019.12-x86_64-aarch64-none-elf] Done"

    echo "[gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu] Checking ..."
    if [ ! -d gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu ]
    then
        wget https://developer.arm.com/-/media/Files/downloads/gnu-a/9.2-2019.12/binrel/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu.tar.xz --no-check-certificate
        tar xf gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu.tar.xz > /dev/null
        rm gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu.tar.xz
    fi
    echo "[gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu] Done"

    echo "[gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf] Checking ..."
    if [ ! -d gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf ]
    then
        wget https://developer.arm.com/-/media/Files/downloads/gnu-a/9.2-2019.12/binrel/gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf.tar.xz --no-check-certificate
        tar xf gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf.tar.xz > /dev/null
        rm gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf.tar.xz
    fi
    echo "[gcc-arm-9.2-2019.12-x86_64-arm-none-linux-gnueabihf] Done"
fi

# core secdev check
echo "[core secdev] Checking ..."
if [ ! -d ./core-secdev-k3 ]
then
    git clone git://git.ti.com/security-development-tools/core-secdev-k3.git
fi
if [ ! -d ./core-secdev-k3 ]
then
    echo "ERROR: Could not clone git://git.ti.com/security-development-tools/core-secdev-k3.git"
fi
echo "[core secdev] Checking ... Done"

# ATF check
echo "[ATF] Checking ..."
if [ ! -d ./trusted-firmware-a ]
then
    git clone https://git.trustedfirmware.org/TF-A/trusted-firmware-a.git
fi
if [ ! -d ./trusted-firmware-a ]
then
    echo "ERROR: Could not clone https://git.trustedfirmware.org/TF-A/trusted-firmware-a.git"
else
    cd trusted-firmware-a
    git fetch origin
    git checkout $ATF_TAG
    git describe
    cd ..
fi
echo "[ATF] Checking ... Done"

# OPTEE check
echo "[OPTEE] Checking ..."
if [ ! -d ./optee_os ]
then
    git clone https://github.com/OP-TEE/optee_os.git
fi
if [ ! -d ./optee_os ]
then
    echo "ERROR: Could not clone https://github.com/OP-TEE/optee_os.git"
else
    cd optee_os
    git fetch origin
    git checkout $OPTEE_TAG
    git describe
    cd ..
fi
echo "[OPTEE] Checking ... Done"

if [ -n "${SOC}" ] && ([ ${SOC} = "j721e" ] || [ ${SOC} = "j721s2" ] || [ ${SOC} = "am62a" ] || [ ${SOC} = "j784s4" ])
then

    # EDGEAI-TIOVX-KERNELS check
    echo "[EDGEAI-TIOVX-KERNELS] Checking ..."
    if [ ! -d ./edgeai-tiovx-kernels ]
    then
        git clone git://git.ti.com/edgeai/edgeai-tiovx-kernels.git
    fi
    if [ ! -d ./edgeai-tiovx-kernels ]
    then
        echo "ERROR: Could not clone git://git.ti.com/edgeai/edgeai-tiovx-kernels.git"
    else
        cd edgeai-tiovx-kernels
        git fetch origin
        git checkout ${TIOVX_KERNELS_TAG}
        cd ..
    fi
    echo "[EDGEAI-TIOVX-KERNELS] Checking ... Done"

    # EDGEAI-TIOVX-MODULES check
    echo "[EDGEAI-TIOVX-MODULES] Checking ..."
    if [ ! -d ./edgeai-tiovx-modules ]
    then
        git clone git://git.ti.com/edgeai/edgeai-tiovx-modules.git
    fi
    if [ ! -d ./edgeai-tiovx-modules ]
    then
        echo "ERROR: Could not clone git://git.ti.com/edgeai/edgeai-tiovx-modules.git"
    else
        cd edgeai-tiovx-modules
        git fetch origin
        git checkout ${TIOVX_MODULES_TAG}
        cd ..
    fi
    echo "[EDGEAI-TIOVX-MODULES] Checking ... Done"

    # EDGEAI-GST-PLUGINS check
    echo "[EDGEAI-GST-PLUGINS] Checking ..."
    if [ ! -d ./edgeai-gst-plugins ]
    then
        git clone https://github.com/TexasInstruments/edgeai-gst-plugins.git
    fi
    if [ ! -d ./edgeai-gst-plugins ]
    then
        echo "ERROR: Could not clone https://github.com/TexasInstruments/edgeai-gst-plugins.git"
    else
        cd edgeai-gst-plugins
        git fetch origin
        git checkout ${GST_PLUGINS_TAG}
        cd ..
    fi
    echo "[EDGEAI-GST-PLUGINS] Checking ... Done"

fi

echo "[opkg-utils] Checking ..."
if [ ! -d opkg-utils-master ]
then
    wget https://git.yoctoproject.org/cgit/cgit.cgi/opkg-utils/snapshot/opkg-utils-master.tar.gz --no-check-certificate
    tar -xf opkg-utils-master.tar.gz
    rm opkg-utils-master.tar.gz
fi
echo "[opkg-utils] Done"

echo "[glm] Checking ..."
# GLM needed for srv PC emulation demo
if [ ! -d glm ]
then
    wget https://github.com/g-truc/glm/releases/download/0.9.8.0/glm-0.9.8.0.zip --no-check-certificate
    unzip glm-0.9.8.0.zip > /dev/null
    rm glm-0.9.8.0.zip
fi
echo "[glm] Done"

echo "[pip] Checking ..."
if [ ! -f ~/.local/bin/pip ]
then
    PYTHON3_VERSION=`python3 -c 'import sys; version=sys.version_info[:2]; print("{1}".format(*version))'`
    if [ ${PYTHON3_VERSION} = '3' ]
    then
        curl "https://bootstrap.pypa.io/pip/3.3/get-pip.py" -o "get-pip.py"
    elif [ ${PYTHON3_VERSION} = '4' ]
    then
        curl "https://bootstrap.pypa.io/pip/3.4/get-pip.py" -o "get-pip.py"
    elif [ ${PYTHON3_VERSION} = '5' ]
    then
        curl "https://bootstrap.pypa.io/pip/3.5/get-pip.py" -o "get-pip.py"
    elif [ ${PYTHON3_VERSION} = '6' ]
    then
        curl "https://bootstrap.pypa.io/pip/3.6/get-pip.py" -o "get-pip.py"
    else
        curl "https://bootstrap.pypa.io/pip/get-pip.py" -o "get-pip.py"
    fi
    python3 get-pip.py --user
    rm get-pip.py
fi

if [ $skip_sudo -eq 0 ]
then
    sudo -H python3 -m pip install --upgrade pip
fi
echo "[pip] Checking ... Done"

echo "[pip] Installing dependant python packages ..."
# There are needed to build ATF, OPTEE
if ! command -v pip3 &> /dev/null
then
    export PATH=${HOME}/.local/bin:$PATH
fi
pip3 install pycrypto pycryptodomex meson --user
echo "[pip] Installing dependant python packages ... Done"

# check if there is a err_packages
if [ -z "$err_packages" ]; then
    echo "Packages installed successfully"
else
    echo "ERROR: The following packages were not installed:"
    for i in "${err_packages[@]}"
    do
       echo "$i"
    done
fi
