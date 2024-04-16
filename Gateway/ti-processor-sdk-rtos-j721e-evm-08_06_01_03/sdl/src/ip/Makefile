MODULE_NAME = sdl_ip

SRCDIR = .
INCDIR = .

INCDIR += $(sdl_PATH) $(sdl_PATH)/src/sdl
INCDIR += ../.. $(sdl_PATH)/include $(sdl_PATH)/include/soc/$(SOC)

INCLUDE_INTERNAL_INTERFACES = sdl_ip

ifeq ($(SOC),$(filter $(SOC), j721e))
PACKAGE_SRCS_COMMON += sdlr_pbist.h pbist/V0
SRCDIR += pbist/V0
INCDIR += pbist/V0

PACKAGE_SRCS_COMMON += sdlr_lbist.h lbist/V0
SRCDIR += lbist/V0
INCDIR += lbist/V0

PACKAGE_SRCS_COMMON += tog
SRCDIR += tog/V0
INCDIR += tog/V0

PACKAGE_SRCS_COMMON +=pok
SRCDIR += pok
INCDIR += pok

PACKAGE_SRCS_COMMON += rti/V0
SRCDIR += rti/V0
INCDIR += rti/V0

PACKAGE_SRCS_COMMON += esm
SRCDIR += esm/V0
INCDIR += esm/V0 esm/V0_0

PACKAGE_SRCS_COMMON += vtm/V0
SRCDIR += vtm/V0
INCDIR += vtm/V0 $(sdl_PATH)/include/soc/j721e

PACKAGE_SRCS_COMMON += mcrc
SRCDIR += mcrc
INCDIR += mcrc

PACKAGE_SRCS_COMMON += rat/V0
SRCDIR += rat/V0
INCDIR += rat/V0

endif

# List all the external components/interfaces, whose interface header files
#  need to be included for this component
INCLUDE_EXTERNAL_INTERFACES = 

SRCS_COMMON += sdl_ip_pbist.c sdl_ip_lbist.c sdl_ip_tog.c sdl_ip_pok.c sdl_ip_esm.c sdl_ip_mcrc.c
PACKAGE_SRCS_COMMON += sdl_ip_pbist.h sdl_ip_lbist.h sdl_ip_tog.c sdl_ip_pok.h sdl_pok_def.h sdl_ip_esm.h sdl_ip_mcrc.h

ifeq ($(SOC),$(filter $(SOC), j721e))
PACKAGE_SRCS_COMMON += sdlr_ecc.h ecc/V1
SRCDIR += ecc/V1
INCDIR += ecc/V1
endif

SRCS_COMMON += sdl_ip_ecc.c
PACKAGE_SRCS_COMMON += sdl_ip_ecc.h

SRCS_COMMON += sdl_ip_rti.c
PACKAGE_SRCS_COMMON +=  sdl_ip_rti.h

SRCS_COMMON += sdl_ip_rat.c
PACKAGE_SRCS_COMMON +=  sdl_ip_rat.h

SRCS_COMMON += sdl_ip_vtm.c sdl_vtm_pvt_sensor.c
PACKAGE_SRCS_COMMON += sdl_ip_vtm.h

MODULE_SRC_BASE_PATH = $(sdl_PATH)/src/ip

# Include common make files
ifeq ($(MAKERULEDIR), )
#Makerule path not defined, define this and assume relative path from ROOTDIR
  MAKERULEDIR := $(ROOTDIR)/build/makerules
  export MAKERULEDIR
endif
include $(MAKERULEDIR)/common.mk
