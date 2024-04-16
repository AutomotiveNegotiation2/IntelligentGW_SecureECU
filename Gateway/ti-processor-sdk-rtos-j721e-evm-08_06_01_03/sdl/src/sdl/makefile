MODULE_NAME = sdl_api

SRCDIR = . pbist/ lbist/ tog/ pok/ ecc/ r5/ esm/ vtm/ dcc/ mcrc/ rat/ misc/
INCDIR = .

INCDIR += ../.. $(sdl_PATH)/include $(sdl_PATH)/include/soc/$(SOC)
INCDIR += $(sdl_PATH)/src/sdl/r5/$(SOC)

INCLUDE_INTERNAL_INTERFACES = sdl_api

ifeq ($(SOC),$(filter $(SOC), j721e))
PACKAGE_SRCS_COMMON += pbist/soc/j721e
SRCDIR += pbist/soc/j721e
INCDIR += pbist/soc/j721e

PACKAGE_SRCS_COMMON += lbist/soc/j721e
SRCDIR += lbist/soc/j721e
INCDIR += lbist/soc/j721e

PACKAGE_SRCS_COMMON += tog/soc/j721e
SRCDIR += tog/soc/j721e
INCDIR += tog/soc/j721e

SRCDIR += rti
INCDIR += rti

PACKAGE_SRCS_COMMON +=pok
SRCDIR += pok
INCDIR += pok

PACKAGE_SRCS_COMMON +=dcc
SRCDIR += dcc
INCDIR += dcc

PACKAGE_SRCS_COMMON += mcrc
SRCDIR += mcrc
INCDIR += mcrc

PACKAGE_SRCS_COMMON += esm
SRCDIR += esm
INCDIR += esm

PACKAGE_SRCS_COMMON +=rat
SRCDIR += rat
INCDIR += rat

PACKAGE_SRCS_COMMON += vtm/soc/j721e
SRCDIR += vtm/soc/j721e
INCDIR += vtm/soc/j721e
endif

ifeq ($(SOC),$(filter $(SOC), j721e))
PACKAGE_SRCS_COMMON += ecc/soc/j721e
INCDIR += ecc/soc/j721e

PACKAGE_SRCS_COMMON += misc/soc/j721e
SRCDIR += misc/soc/j721e
INCDIR += misc/soc/j721e
endif

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = sdl_osal

SRCS_COMMON += sdl_pbist.c sdl_soc_pbist.c sdl_lbist.c sdl_soc_lbist.c sdl_tog.c sdl_vtm.c
PACKAGE_SRCS_COMMON += sdl_pbist.h sdl_pbist.c sdl_pbist_priv.h sdl_lbist.h sdl_lbist.c sdl_lbist_priv.h sdl_tog.h sdl_vtm.h

SRCS_COMMON +=  sdl_rti.c
PACKAGE_SRCS_COMMON += sdl_rti.h

SRCS_COMMON +=  sdl_dcc.c
PACKAGE_SRCS_COMMON += sdl_dcc.h

SRCS_COMMON +=  sdl_rat.c
PACKAGE_SRCS_COMMON += sdl_rat.h

SRCS_COMMON +=  sdl_mcrc.c
PACKAGE_SRCS_COMMON += sdl_mcrc.h

SRCS_COMMON += sdl_pok.c
PACKAGE_SRCS_COMMON += sdl_pok.c

SRCS_COMMON += sdl_ecc.c
SRCS_ASM_COMMON += sdl_ecc_utils.asm
PACKAGE_SRCS_COMMON += sdl_ecc_core.h sdl_priv.h sdl_ecc_utils.h sdl_soc_ecc.h

SRCS_COMMON += sdl_ecc_r5.c sdl_exception.c sdl_mpu.c sdl_mpuCfg.c sdl_ccm.c
SRCS_ASM_COMMON += sdl_r5_utils.asm
PACKAGE_SRCS_COMMON += sdl_r5_core.h

SRCS_COMMON += sdl_esm.c sdl_esm_priv.c sdl_esm_core.c
PACKAGE_SRCS_COMMON += sdl_esm.h

SRCS_COMMON += sdl_msmc.c
PACKAGE_SRCS_COMMON += sdl_msmc.h

MODULE_SRC_BASE_PATH = $(sdl_PATH)/src/sdl

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk
