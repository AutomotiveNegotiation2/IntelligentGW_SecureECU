#
# Utility makefile to build edgeai components
#
# 1. edgeai-tiovx-kernels
# 2. edgeai-tiovx-modules
# 3. edgeai-gst-plugins
#

EDGEAI_KERNELS_PATH   ?= $(PSDK_PATH)/edgeai-tiovx-kernels/
EDGEAI_MODULES_PATH   ?= $(PSDK_PATH)/edgeai-tiovx-modules/
EDGEAI_PLUGINS_PATH   ?= $(PSDK_PATH)/edgeai-gst-plugins/
CROSS_COMPILER_PATH    = $(PSDK_PATH)/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu
CROSS_COMPILER_PREFIX  = aarch64-none-linux-gnu-
TARGET_FS              = $(PSDK_PATH)/targetfs
EDGEAI_INSTALL_PATH   ?= $(TARGET_FS)

export CROSS_COMPILER_PATH
export CROSS_COMPILER_PREFIX
export TARGET_FS

edgeai_check_paths:
	@if [ ! -d $(EDGEAI_KERNELS_PATH) ]; then echo 'ERROR: $(EDGEAI_KERNELS_PATH) not found !!!'; exit 1; fi
	@if [ ! -d $(EDGEAI_MODULES_PATH) ]; then echo 'ERROR: $(EDGEAI_MODULES_PATH) not found !!!'; exit 1; fi
	@if [ ! -d $(EDGEAI_PLUGINS_PATH) ]; then echo 'ERROR: $(EDGEAI_PLUGINS_PATH) not found !!!'; exit 1; fi

edgeai:
	@echo "Building EdgeAI Components"
	$(MAKE) edgeai_check_paths
	$(MAKE) linux_fs_install
	$(MAKE) edgeai_kernels
	$(MAKE) edgeai_modules
	$(MAKE) edgeai_plugins

edgeai_kernels:
	@echo "Building EdgeAI Kernels"
	cd $(EDGEAI_KERNELS_PATH); \
	mkdir build; \
	cd build; \
	cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/cross_compile_aarch64.cmake ..; \
	$(MAKE) install DESTDIR=$(TARGET_FS)

edgeai_modules:
	@echo "Building EdgeAI Modules"
	cd $(EDGEAI_MODULES_PATH); \
	mkdir build; \
	cd build; \
	cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/cross_compile_aarch64.cmake ..; \
	$(MAKE) install DESTDIR=$(TARGET_FS)

edgeai_plugins:
	@echo "Building EdgeAI Plugins"
	cd $(EDGEAI_PLUGINS_PATH); \
	PKG_CONFIG_PATH='' crossbuild/environment $(PSDK_PATH) > aarch64-none-linux-gnu.ini; \
	PKG_CONFIG_PATH='' meson build -Ddl-plugins=disabled --cross-file aarch64-none-linux-gnu.ini --cross-file crossbuild/crosscompile.ini; \
	DESTDIR=$(TARGET_FS) ninja -C build install

edgeai_install:
	@echo "Install EdgeAI Kernels, Modules and Plugins to EDGEAI_INSTALL_PATH"
	cd $(EDGEAI_KERNELS_PATH); \
	if [ -d "build" ]; then $(MAKE) install DESTDIR=$(EDGEAI_INSTALL_PATH) -C build; else echo edgeai-tiovx-kernels has not been built yet, skipping install; fi;
	cd $(EDGEAI_MODULES_PATH); \
	if [ -d "build" ]; then $(MAKE) install DESTDIR=$(EDGEAI_INSTALL_PATH) -C build; else echo edgeai-tiovx-modules has not been built yet, skipping install; fi;
	cd $(EDGEAI_PLUGINS_PATH); \
	if [ -d "build" ]; then DESTDIR=$(EDGEAI_INSTALL_PATH) ninja -C build install; else echo edgeai-gst-plugins has not been built yet, skipping install; fi; \
	sync

edgeai_scrub:
	@echo "EdgeAI Scrub"
	cd $(EDGEAI_KERNELS_PATH); \
	rm -rf build bin lib
	cd $(EDGEAI_MODULES_PATH); \
	rm -rf build bin lib
	cd $(EDGEAI_PLUGINS_PATH); \
	rm -rf build
