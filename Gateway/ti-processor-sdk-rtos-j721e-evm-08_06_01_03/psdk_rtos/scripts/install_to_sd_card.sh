THIS_SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
source ${THIS_SCRIPT_DIR}/board_env.sh

bootfs_file=$PWD/boot-${TI_DEV_BOARD}.tar.gz
rootfs_file=$PWD/tisdk-${TISDK_IMAGE}-image-${TI_DEV_BOARD}.tar.xz

bootfs_folder=/media/$USER/BOOT
rootfs_folder=/media/$USER/rootfs

untar_bootfs()
{
    if [ -d $bootfs_folder ]
    then
        echo "Installing $bootfs_file to $bootfs_folder ..."
        if [ -f $bootfs_file ]
        then
            cd $bootfs_folder
            tar -xf $bootfs_file
            cd -
            sync
            echo "Installing $bootfs_file to $bootfs_folder ... Done"
        else
            echo "ERROR: $bootfs_file not found !!!"
        fi
    else
        echo "ERROR: $bootfs_folder not found !!!"
    fi
}

untar_rootfs()
{
    if [ -d $rootfs_folder ]
    then
        echo "Installing $rootfs_file to $rootfs_folder ..."
        if [ -f $rootfs_file ]
        then
            cd $rootfs_folder
            sudo chmod 777 .
            # -I pxz multithreads the decompression to increase performance
            sudo tar --same-owner -I pxz -xf ${rootfs_file} .
            cd -
            if [ "${TI_DEV_BOARD}" = "j7-evm" ] || [ "${TI_DEV_BOARD}" = "am62axx-evm" ] || [ "${TI_DEV_BOARD}" = "j721s2-evm" ] || [ "${TI_DEV_BOARD}" = "j784s4-evm" ]
            then
                sudo chmod 777 -R $rootfs_folder/opt/
                sudo chmod 777 $rootfs_folder/lib/firmware/
                sudo chmod 777 -R $rootfs_folder/usr/include/processor_sdk/
            if [ "${TI_DEV_BOARD}" = "j7-evm" ] || [ "${TI_DEV_BOARD}" = "j721s2-evm" ] || [ "${TI_DEV_BOARD}" = "j784s4-evm" ]
                then
                    sudo chmod 777 -R $rootfs_folder/lib/firmware/vision_apps_evm/
                fi
                sudo chmod 777 -R $rootfs_folder/lib/firmware/vision_apps_eaik/
                sudo chmod 777 -R $rootfs_folder/usr/lib/
                sudo chmod 777 -R $rootfs_folder/usr/include/edgeai-tiovx-modules/
                sudo chmod 777 $rootfs_folder/usr/bin/edgeai-tiovx-modules-test
                sudo chmod 777 -R $rootfs_folder/usr/include/edgeai-tiovx-kernels/
                sudo chmod 777 $rootfs_folder/usr/bin/edgeai-tiovx-kernels-test
                sudo chmod 666 $rootfs_folder/etc/security/limits.conf
                sudo rm $rootfs_folder/home/root/.profile
                sudo rm $rootfs_folder/lib/systemd/system-preset/*-edgeai-init.preset
            else
                sudo chmod 777 $rootfs_folder/opt/
                sudo chmod 777 $rootfs_folder/lib/firmware
                sudo chmod 777 $rootfs_folder/etc/security/
                sudo chmod 666 $rootfs_folder/etc/security/limits.conf
                sudo chmod 777 $rootfs_folder/boot
                sudo chmod 777 $rootfs_folder/usr/lib
                sudo chmod 777 $rootfs_folder/usr/lib/gstreamer-1.0/
                sudo chmod 777 $rootfs_folder/usr/lib/pkgconfig/
                sudo chmod 777 $rootfs_folder/usr/bin
                sudo chmod 777 $rootfs_folder/usr/include
            fi
            sync
            echo "Installing $rootfs_file to /media/$USER/$rootfs_folder ... Done"
        else
            echo "ERROR: $rootfs_file not found !!!"
        fi
    else
        echo "ERROR: $rootfs_folder not found !!!"
    fi

}

if [[ `id -u` -ne 0 ]]
then
  untar_bootfs
  untar_rootfs
else
  echo "Please run without sudo"
  exit
fi
