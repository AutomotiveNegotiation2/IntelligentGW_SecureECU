SRCS_COMMON += vhwa_dmpac_soc.c vhwa_vpac_soc.c
SRCS_COMMON += csl_dmpac_hts.c csl_nsf4.c
SRCS_COMMON += csl_fcp.c csl_hts.c csl_visstop.c
SRCS_COMMON += csl_lse.c csl_ldc.c csl_msc.c vhwa_soc_fc.c

ifeq ($(SOC),$(filter $(SOC), j721s2 j784s4))
SRCS_COMMON += csl_cac.c
endif
