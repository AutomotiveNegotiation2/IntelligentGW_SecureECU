SOC_DEP_LIB_SOCS=k2h k2hk k2l k2e k2g c6678 c6657 omapl137 omapl138 am65xx j721e j721s2 am77x j7200 am64x tpr12 awr294x j784s4
GPIO_V2_SOCS=tpr12 awr294x

# Common source files across all platforms and cores
ifeq ($(SOC),$(filter $(SOC),$(SOC_DEP_LIB_SOCS) ))
   ifeq ($(SOC),$(filter $(SOC),$(GPIO_V2_SOCS) ))
      SRCDIR = . src src/v2
      INCDIR = . src src/v2
      SRCS_COMMON += GPIO_drv.c GPIO_v2.c
   else
      SRCDIR = . src src/v0
      INCDIR = . src src/v0
      SRCS_COMMON += GPIO_drv.c GPIO_v0.c
   endif
else
      SRCDIR = . src src/v1 src/v0
      INCDIR = . src src/v1 src/v0
      SRCS_COMMON += GPIO_drv.c GPIO_v0.c GPIO_v1.c
endif

PACKAGE_SRCS_COMMON = makefile GPIO.h gpio_component.mk src/GPIO_osal.h \
              docs/ReleaseNotes_GPIO_LLD.pdf \
              src/GPIO_drv.c src/GPIO_drv_log.h \
              soc/GPIO_v1.h \
              build src/src_files_common.mk src/Module.xs \
              config_mk.bld GPIOver.h GPIOver.h.xdt package.bld package.xdc package.xs Settings.xdc.xdt

ifeq ($(SOC),$(filter $(SOC),$(SOC_DEP_LIB_SOCS) ))
  ifeq ($(SOC),$(filter $(SOC),$(GPIO_V2_SOCS) ))
    PACKAGE_SRCS_COMMON += src/v2 src/v2/GPIO_v2.h src/v2/GPIO_v2.c test
    PACKAGE_SRCS_COMMON += soc/GPIO_soc.h soc/$(SOC)
  else
    PACKAGE_SRCS_COMMON += src/v0 src/v0/GPIO_v0.h src/v0/GPIO_v0.c test
  endif
else
PACKAGE_SRCS_COMMON += src/v0 src/v0/GPIO_v0.h src/v0/GPIO_v0.c \
	 	      src/v1 src/v1/GPIO_v1.h src/v1/GPIO_v1.c test
endif


