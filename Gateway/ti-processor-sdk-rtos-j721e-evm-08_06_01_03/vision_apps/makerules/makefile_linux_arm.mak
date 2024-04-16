#
# Utility makefile to build linux components and load updated file system
#
# Edit this file to suit your specific build needs
#

ifeq ($(PROFILE), $(filter $(PROFILE),debug all))
LINUX_APP_PROFILE=debug
endif
ifeq ($(PROFILE), $(filter $(PROFILE),release all))
LINUX_APP_PROFILE=release
endif

ifeq ($(SOC),j721e)
LINUX_FIRMWARE_PREFIX=j7
else
LINUX_FIRMWARE_PREFIX=$(SOC)
endif

FIRMWARE_SUBFOLDER?=vision_apps_evm
UENV_NAME?=uEnv_$(SOC)_vision_apps.txt
LINUX_FS_STAGE_PATH?=/tmp/tivision_apps_targetfs_stage

linux_fs_stage:
ifeq ($(YOCTO_STAGE),)
	@rm -rf $(LINUX_FS_STAGE_PATH)
	install -m 775 -d $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)
endif
	install -m 775 -d $(LINUX_FS_STAGE_PATH)/usr/lib

ifeq ($(BUILD_CPU_MPU1),yes)
	# copy application binaries and scripts
	install -m 775 -d $(LINUX_FS_STAGE_PATH)/opt/vision_apps
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/A72/LINUX/$(LINUX_APP_PROFILE)/*.out $(LINUX_FS_STAGE_PATH)/opt/vision_apps || true
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/A72/LINUX/$(LINUX_APP_PROFILE)/vx_app_arm_remote_log.out $(LINUX_FS_STAGE_PATH)/opt || true
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/A72/LINUX/$(LINUX_APP_PROFILE)/libtivision_apps.so.$(PSDK_VERSION) $(LINUX_FS_STAGE_PATH)/usr/lib
	cp -P $(VISION_APPS_PATH)/out/$(TARGET_SOC)/A72/LINUX/$(LINUX_APP_PROFILE)/libtivision_apps.so $(LINUX_FS_STAGE_PATH)/usr/lib
	cp $(VISION_APPS_PATH)/apps/basic_demos/app_linux_fs_files/vision_apps_init.sh $(LINUX_FS_STAGE_PATH)/opt/vision_apps/.
	cp -r $(VISION_APPS_PATH)/apps/basic_demos/app_linux_fs_files/vision_apps_all/* $(LINUX_FS_STAGE_PATH)/opt/vision_apps/.
ifeq ($(YOCTO_STAGE),)
	cp -r $(VISION_APPS_PATH)/apps/basic_demos/app_linux_fs_files/vision_apps_evm/* $(LINUX_FS_STAGE_PATH)/opt/vision_apps/.
	chmod +x $(LINUX_FS_STAGE_PATH)/opt/vision_apps/*.sh
endif

	# copy imaging sensor dcc binaries
	install -m 775 -d $(LINUX_FS_STAGE_PATH)/opt/imaging/imx390
	install -m 775 -d $(LINUX_FS_STAGE_PATH)/opt/imaging/ar0820
	install -m 775 -d $(LINUX_FS_STAGE_PATH)/opt/imaging/ar0233
	install -m 775 -d $(LINUX_FS_STAGE_PATH)/opt/imaging/imx219
ifeq ($(SOC),am62a)
	install -m 775 -d $(LINUX_FS_STAGE_PATH)/opt/imaging/ov2312
endif

	cp $(IMAGING_PATH)/sensor_drv/src/imx390/dcc_bins/*.bin $(LINUX_FS_STAGE_PATH)/opt/imaging/imx390
	cp $(IMAGING_PATH)/sensor_drv/src/ar0820/dcc_bins/*.bin $(LINUX_FS_STAGE_PATH)/opt/imaging/ar0820
	cp $(IMAGING_PATH)/sensor_drv/src/ar0233/dcc_bins/*.bin $(LINUX_FS_STAGE_PATH)/opt/imaging/ar0233
	cp $(IMAGING_PATH)/sensor_drv/src/imx219/dcc_bins/*.bin $(LINUX_FS_STAGE_PATH)/opt/imaging/imx219
ifeq ($(SOC),am62a)
	cp $(IMAGING_PATH)/sensor_drv/src/ov2312/dcc_bins/*.bin $(LINUX_FS_STAGE_PATH)/opt/imaging/ov2312
endif

	# Copy header files (variables used in this section are defined in makefile_ipk.mak)
	@# copy all the .h files under folders in IPK_INCLUDE_FOLDERS
	@# https://stackoverflow.com/questions/10176849/how-can-i-copy-only-header-files-in-an-entire-nested-directory-to-another-direct
	for folder in $(IPK_INCLUDE_FOLDERS); do \
		install -m 775 -d $(LINUX_FS_STAGE_PATH)/$(IPK_TARGET_INC_PATH)/$$folder; \
		(cd $(PSDK_PATH)/$$folder && find . -name '*.h' -print | tar --create --files-from -) | (cd $(LINUX_FS_STAGE_PATH)/$(IPK_TARGET_INC_PATH)/$$folder && tar xfp -); \
	done

ifeq ($(YOCTO_STAGE),)
	ln -sr $(LINUX_FS_STAGE_PATH)/$(IPK_TARGET_INC_PATH)/$(tidl_dir) $(LINUX_FS_STAGE_PATH)/$(IPK_TARGET_INC_PATH)/tidl_j7
	$(MAKE) EDGEAI_INSTALL_PATH=$(LINUX_FS_STAGE_PATH) edgeai_install
endif

endif

ifeq ($(YOCTO_STAGE),)
ifeq ($(BUILD_CPU_MCU1_0),yes)
	# copy remote firmware files for mcu1_0
	$(eval IMAGE_NAME := vx_app_rtos_linux_mcu1_0.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(TIARMCGT_LLVM_ROOT)/bin/tiarmstrip -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
ifneq ($(SOC), am62a)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-mcu-r5f0_0-fw
endif
else
	# Copy MCU1_0 firmware which is used in the default uboot
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/pdk-ipc/ipc_echo_testb_mcu1_0_release_strip.xer5f $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-mcu-r5f0_0-fw
endif
ifeq ($(BUILD_CPU_MCU1_1),yes)
	# copy remote firmware files for mcu1_1
	$(eval IMAGE_NAME := vx_app_rtos_linux_mcu1_1.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(TIARMCGT_LLVM_ROOT)/bin/tiarmstrip -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-mcu-r5f0_1-fw
endif
ifeq ($(BUILD_CPU_MCU2_0),yes)
	# copy remote firmware files for mcu2_0
	$(eval IMAGE_NAME := vx_app_rtos_linux_mcu2_0.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(TIARMCGT_LLVM_ROOT)/bin/tiarmstrip -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f0_0-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f0_0-fw-sec
endif
endif
ifeq ($(BUILD_CPU_MCU2_1),yes)
	# copy remote firmware files for mcu2_1
	$(eval IMAGE_NAME := vx_app_rtos_linux_mcu2_1.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(TIARMCGT_LLVM_ROOT)/bin/tiarmstrip -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f0_1-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f0_1-fw-sec
endif
endif
ifeq ($(BUILD_CPU_MCU3_0),yes)
	# copy remote firmware files for mcu3_0
	$(eval IMAGE_NAME := vx_app_rtos_linux_mcu3_0.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(TIARMCGT_LLVM_ROOT)/bin/tiarmstrip -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f1_0-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f1_0-fw-sec
endif
endif
ifeq ($(BUILD_CPU_MCU3_1),yes)
	# copy remote firmware files for mcu3_1
	$(eval IMAGE_NAME := vx_app_rtos_linux_mcu3_1.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(TIARMCGT_LLVM_ROOT)/bin/tiarmstrip -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f1_1-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f1_1-fw-sec
endif
endif
ifeq ($(BUILD_CPU_MCU4_0),yes)
	# copy remote firmware files for mcu4_0
	$(eval IMAGE_NAME := vx_app_rtos_linux_mcu4_0.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(TIARMCGT_LLVM_ROOT)/bin/tiarmstrip -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f2_0-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f2_0-fw-sec
endif
endif
ifeq ($(BUILD_CPU_MCU4_1),yes)
	# copy remote firmware files for mcu4_1
	$(eval IMAGE_NAME := vx_app_rtos_linux_mcu4_1.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/R5F/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(TIARMCGT_LLVM_ROOT)/bin/tiarmstrip -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f2_1-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-main-r5f2_1-fw-sec
endif
endif
ifeq ($(BUILD_CPU_C6x_1),yes)
	# copy remote firmware files for c6x_1
	$(eval IMAGE_NAME := vx_app_rtos_linux_c6x_1.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/C66/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(CGT6X_ROOT)/bin/strip6x -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c66_0-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c66_0-fw-sec
endif
endif
ifeq ($(BUILD_CPU_C6x_2),yes)
	# copy remote firmware files for c6x_2
	$(eval IMAGE_NAME := vx_app_rtos_linux_c6x_2.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/C66/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(CGT6X_ROOT)/bin/strip6x -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c66_1-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c66_1-fw-sec
endif
endif
ifeq ($(BUILD_CPU_C7x_1),yes)
	# copy remote firmware files for c7x_1
	$(eval IMAGE_NAME := vx_app_rtos_linux_c7x_1.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/$(C7X_TARGET)/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(CGT7X_ROOT)/bin/strip7x -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c71_0-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c71_0-fw-sec
endif

	#Build TIDL test case and copy binaries
	#$(MAKE) -C $(TIDL_PATH)/../ run
	mkdir -p $(LINUX_FS_STAGE_PATH)/opt/tidl_test
	#J721E, J721S2, J784S4, AM62A use the new arm-tidl paths
	cp -P $(TIDL_PATH)/../arm-tidl/tfl_delegate/out/$(TARGET_SOC)/A72/LINUX/$(LINUX_APP_PROFILE)/*.so*  $(LINUX_FS_STAGE_PATH)/usr/lib
	cp -P $(TIDL_PATH)/../arm-tidl/onnxrt_ep/out/$(TARGET_SOC)/A72/LINUX/$(LINUX_APP_PROFILE)/*.so*  $(LINUX_FS_STAGE_PATH)/usr/lib
	cp -P $(TIDL_PATH)/../arm-tidl/rt/out/$(TARGET_SOC)/A72/LINUX/$(LINUX_APP_PROFILE)/*.so*  $(LINUX_FS_STAGE_PATH)/usr/lib
	cp $(TIDL_PATH)/../arm-tidl/rt/out/$(TARGET_SOC)/A72/LINUX/$(LINUX_APP_PROFILE)/*.out     $(LINUX_FS_STAGE_PATH)/opt/tidl_test/
	cp -r $(TIDL_PATH)/test/testvecs/ $(LINUX_FS_STAGE_PATH)/opt/tidl_test/
endif
ifeq ($(BUILD_CPU_C7x_2),yes)
	# copy remote firmware files for c7x_2
	$(eval IMAGE_NAME := vx_app_rtos_linux_c7x_2.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/$(C7X_TARGET)/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(CGT7X_ROOT)/bin/strip7x -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c71_1-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c71_1-fw-sec
endif
endif
ifeq ($(BUILD_CPU_C7x_3),yes)
	# copy remote firmware files for c7x_3
	$(eval IMAGE_NAME := vx_app_rtos_linux_c7x_3.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/$(C7X_TARGET)/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(CGT7X_ROOT)/bin/strip7x -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c71_2-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c71_2-fw-sec
endif
endif
ifeq ($(BUILD_CPU_C7x_4),yes)
	# copy remote firmware files for c7x_4
	$(eval IMAGE_NAME := vx_app_rtos_linux_c7x_4.out)
	cp $(VISION_APPS_PATH)/out/$(TARGET_SOC)/$(C7X_TARGET)/$(RTOS)/$(LINUX_APP_PROFILE)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/.
	$(CGT7X_ROOT)/bin/strip7x -p $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME)
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c71_3-fw
ifeq ($(HS),1)
	$(TI_SECURE_DEV_PKG)/scripts/secure-binary-image.sh $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME) $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed
	ln -sr $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/$(IMAGE_NAME).signed $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-c71_3-fw-sec
endif
endif
	sync
endif

# MODIFY_FS macro for making PSDK RTOS modifications to the PSDK Linux to file system
# $1 : rootfs path
# $2 : bootfs path
define MODIFY_FS =
	# copy uEnv.txt for PSDK RTOS
	cp $(VISION_APPS_PATH)/apps/basic_demos/app_linux_fs_files/uEnv_$(SOC)_vision_apps.txt $(2)/
	cp $(VISION_APPS_PATH)/apps/basic_demos/app_linux_fs_files/uEnv_$(SOC)_edgeai_apps.txt $(2)/
	cp $(2)/$(UENV_NAME) $(2)/uEnv.txt
	# update any additional files specific to PSDK RTOS in the filesystem
	-cp $(VISION_APPS_PATH)/apps/basic_demos/app_linux_fs_files/limits.conf $(1)/etc/security/limits.conf 2> /dev/null
	sync
endef

ifeq ($(SOC), am62a)
	FIRMWARE_PREFIX_TO_DELETE=c7*-fw
else
	FIRMWARE_PREFIX_TO_DELETE=*-fw
endif
# CLEAN_COPY_FROM_STAGE macro for updating a file system from the stage fs
# $1 : destination rootfs path
define CLEAN_COPY_FROM_STAGE =
	# remove old remote files from filesystem
	-rm -f $(1)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-$(FIRMWARE_PREFIX_TO_DELETE)
	-rm -f $(1)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-*-fw-sec
	-rm -rf $(1)/lib/firmware/$(FIRMWARE_SUBFOLDER)
	-rm -rf $(1)/opt/tidl_test/*
	-rm -rf $(1)/opt/notebooks/*
	-rm -rf $(1)/$(IPK_TARGET_INC_PATH)/*

	# create new directories
	-mkdir -p $(1)/$(IPK_TARGET_INC_PATH)

	# copy full vision apps linux fs stage directory into linux fs
	cp -r $(LINUX_FS_STAGE_PATH)/* $(1)/.
	sync
endef

# CLEAN_COPY_FROM_STAGE_FAST macro for updating a file system from the stage fs
# - Assumes that FULL copy has been done before
# - Only updates vision_apps exe and firmware
# $1 : destination rootfs path
define CLEAN_COPY_FROM_STAGE_FAST =
	# remove old remote files from filesystem
	-rm -f $(1)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-*-fw
	-rm -f $(1)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-*-fw-sec
	-rm -rf $(1)/lib/firmware/$(FIRMWARE_SUBFOLDER)

	# copy partial vision apps linux fs stage directory into linux fs
	cp -r $(LINUX_FS_STAGE_PATH)/lib/firmware/$(LINUX_FIRMWARE_PREFIX)-*-fw $(1)/lib/firmware/.
	cp -r $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER) $(1)/lib/firmware/.
	cp -r $(LINUX_FS_STAGE_PATH)/opt/vision_apps/* $(1)/opt/vision_apps/.
	cp -r $(LINUX_FS_STAGE_PATH)/usr/lib/* $(1)/usr/lib/.
	sync
endef

###### USED FOR YOCTO BUILD #########

YOCTO_VARS = PROFILE=release \
	BUILD_EMULATION_MODE=no \
	TARGET_CPU=A72 \
	TARGET_OS=LINUX \
	TIDL_PATH=$(PSDK_PATH)/tidl_j7/ti_dl

yocto_build:
	$(COPYDIR) $(PSDK_PATH)/psdk_include/* $(PSDK_PATH)/.
	$(YOCTO_VARS) $(MAKE) imaging
	$(YOCTO_VARS) BUILD_CSITX=no $(MAKE) tiovx
	$(YOCTO_VARS) $(MAKE) ptk
	$(YOCTO_VARS) $(MAKE) tivision_apps
	$(YOCTO_VARS) $(MAKE) vx_app_conformance vx_app_arm_remote_log vx_app_arm_ipc \
		vx_app_arm_mem vx_app_arm_fd_exchange_consumer vx_app_arm_fd_exchange_producer \
		vx_app_c7x_kernel vx_app_heap_stats vx_app_load_test vx_app_viss

yocto_clean: imaging_scrub tiovx_scrub ptk_scrub scrub
	$(CLEANDIR) $(PSDK_PATH)/tidl_j7
	$(CLEANDIR) $(VXLIB_PATH)
	$(CLEANDIR) $(IVISION_PATH)
	$(CLEANDIR) $(TIADALG_PATH)

yocto_install:
	$(YOCTO_VARS) YOCTO_STAGE=1 $(MAKE) linux_fs_stage

#### USED FOR FIRMWARE ONLY BUILD ####

FIRMWARE_VARS = PROFILE=release \
	BUILD_EMULATION_MODE=no \
	BUILD_CPU_MPU1=no \
	BUILD_LINUX_A72=no \
	BUILD_QNX_A72=no \
	BUILD_APP_RTOS_LINUX=yes \
	BUILD_EDGEAI=yes

firmware:
	$(FIRMWARE_VARS) $(MAKE) sdk
	$(FIRMWARE_VARS) $(MAKE) update_fw

firmware_scrub:
	$(FIRMWARE_VARS) $(MAKE) sdk_scrub

update_fw: linux_fs_stage
	mkdir -p $(PSDK_PATH)/psdk_fw/$(SOC)/$(FIRMWARE_SUBFOLDER)/
	cp $(LINUX_FS_STAGE_PATH)/lib/firmware/$(FIRMWARE_SUBFOLDER)/* $(PSDK_PATH)/psdk_fw/$(SOC)/$(FIRMWARE_SUBFOLDER)/.

######################################

linux_host_libs_includes:
	BUILD_EMULATION_MODE=no TARGET_CPU=A72 TARGET_OS=LINUX $(MAKE) imaging
	BUILD_EMULATION_MODE=no TARGET_CPU=A72 TARGET_OS=LINUX $(MAKE) tiovx
	BUILD_EMULATION_MODE=no TARGET_CPU=A72 TARGET_OS=LINUX $(MAKE) ptk
	BUILD_EMULATION_MODE=no TARGET_CPU=A72 TARGET_OS=LINUX \
		BUILD_CPU_MPU1=yes BUILD_CPU_MCU1_0=no BUILD_CPU_MCU2_0=no BUILD_CPU_MCU2_1=no \
		BUILD_CPU_MCU3_0=no BUILD_CPU_MCU3_1=no BUILD_CPU_C6x_1=no BUILD_CPU_C6x_2=no \
		BUILD_CPU_C7x_1=no $(MAKE) tivision_apps
	BUILD_EMULATION_MODE=no TARGET_CPU=A72 TARGET_OS=LINUX \
		BUILD_CPU_MPU1=yes BUILD_CPU_MCU1_0=no BUILD_CPU_MCU2_0=no BUILD_CPU_MCU2_1=no \
		BUILD_CPU_MCU3_0=no BUILD_CPU_MCU3_1=no BUILD_CPU_C6x_1=no BUILD_CPU_C6x_2=no \
		BUILD_CPU_C7x_1=no $(MAKE) linux_fs_install
	rm -Rf $(LINUX_FS_STAGE_PATH)/lib $(LINUX_FS_STAGE_PATH)/opt

linux_fs_install: linux_fs_stage
	$(call CLEAN_COPY_FROM_STAGE,$(LINUX_FS_PATH))

linux_fs_install_sd: linux_fs_install
	$(call CLEAN_COPY_FROM_STAGE,$(LINUX_SD_FS_ROOT_PATH))

	$(call MODIFY_FS,$(LINUX_SD_FS_ROOT_PATH),$(LINUX_SD_FS_BOOT_PATH))

ifeq ($(BUILD_CPU_MCU1_0),yes)
	$(MAKE) uboot_linux_install_sd
endif

linux_fs_install_nfs: linux_fs_install
	$(call MODIFY_FS,$(LINUX_FS_PATH),$(LINUX_FS_BOOT_PATH))

linux_fs_install_sd_ip: ip_addr_check linux_fs_install
	mkdir -p /tmp/j7-evm
	sshfs -o nonempty root@$(J7_IP_ADDRESS):/ /tmp/j7-evm
	#(call CLEAN_COPY_FROM_STAGE,/tmp/j7-evm)
	$(call CLEAN_COPY_FROM_STAGE_FAST,/tmp/j7-evm)
	$(MAKE) EDGEAI_INSTALL_PATH=/tmp/j7-evm edgeai_install
	chmod 777 -R /tmp/j7-evm/lib/firmware/$(FIRMWARE_SUBFOLDER)
	fusermount -u /tmp/j7-evm/

linux_fs_install_sd_test_data:
	$(call INSTALL_TEST_DATA,$(LINUX_SD_FS_ROOT_PATH),opt/vision_apps)

linux_fs_install_nfs_test_data:
	$(call INSTALL_TEST_DATA,$(LINUX_FS_PATH),opt/vision_apps)

linux_fs_install_tar: linux_fs_install_nfs linux_fs_install_nfs_test_data
	# Creating bootfs tar - zipping with gzip (-z option in tar)
	cd $(LINUX_FS_BOOT_PATH) && tar czf $(VISION_APPS_PATH)/bootfs.tar.gz .
	# Creating rootfs tar - using lzma compression, but parallelized to increase performance (-I pxz)
	# (-J would do lzma compression, but without parallelization)
	cd $(LINUX_FS_PATH) && sudo tar -I pxz -cpf $(VISION_APPS_PATH)/rootfs.tar.xz .

linux_fs_install_from_custom_stage:
	# Internal Testing
	# Set LINUX_FS_PATH=destination dir
	# Set LINUX_FS_STAGE_PATH=source dir
	$(call CLEAN_COPY_FROM_STAGE,$(LINUX_FS_PATH))

