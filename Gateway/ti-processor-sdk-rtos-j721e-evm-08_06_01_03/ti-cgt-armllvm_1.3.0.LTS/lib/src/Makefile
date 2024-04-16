##############################################################################
#
#
# Makefile for ARMLLVM run-time support library version 1.0.0
#
#
##############################################################################
#
# This Makefile is automatically-generated: you usually should not edit it. 
#
##############################################################################


##############################################################################
#
# This Makefile is specific to compiler RTS library version 1.0.0.  
# The format is subject to change without notice.  This Makefile is intended
# for use with mklib, which understands which 'make' variables to set to build
# each distinct version of the RTS library.
#
# This Makefile uses GNU make language extensions.
#
##############################################################################

##############################################################################
#
# GROUPS
#
# The source files are set up in a modular fashion using "groups."  Groups
# represent major feature clusters, and usually specify source files which
# implement that feature.  When building a library which needs a particular
# feature, the group which represents that feature is "activated" by setting a
# 'make' variable.  This variable can be set directly by the user, or may be
# inferred from the setting of other variables.  Groups (and the files they
# contain) not needed for a certain library are not activated.  Some groups
# are always activated.  Groups which are not always activated are enclosed in
# an "ifeq" testing the corresponding 'make' variable (the name of the
# variable is the name of the group).
#
# Groups can specify any kind of source file (e.g. C, C++, assembly), but do
# not list header files, or source files included from other source files.
# This Makefile is focused on how to build the object files, not listing all
# of the necessary files.  Some groups do not list any source files; these
# groups may still carry information such as extra options to use when that
# group is active, or may activate other groups.  Some groups exist only to be
# tested as part of the activation condition of other groups.
#
# Groups can specify extra compiler options to use when that group is active.
# These can be options intended for all targets (UNIVERSAL_FLAGS), such as the
# CPU version, or can be intended only for a certain type of files (CPP_FLAGS)
# (e.g. the option "--exceptions")
#
##############################################################################

##############################################################################
#
# OPTIONS
#
# You can append or override some options through 'make' variables specified
# on the command line.  Not all options can be changed this way, and some
# options are dangerous to use in a Makefile (e.g. "--skip_assembler").
# Options added by groups below should not be altered; if the option is
# undesired, you're probably building the wrong library.  For example, if you
# don't want "--exceptions", you shouldn't be using EXCEPTIONS=1.
#
# You can append options to the standard list by using EXTRA_FLAGS.  This is
# useful for enabling debugging support or activating silicon errata
# workarounds:
#
# gmake LIB=some.lib EXTRA_FLAGS="-g"
#
##############################################################################

##############################################################################
# Available libraries
#
# You can build each 1.0.0 library using the appropriate command:
#
# gmake library LIB=libc_armv6m-ti-none-eabi.lib FREEBSD_MATH_64_BIT=1 FREEBSD_MATH_COMMON=1 FREEBSD_MATH_32_BIT=1 FREEBSD_C99_COMPLEX=1 FREEBSD_MACHINE=1 FREEBSD_SUPPLEMENTAL_C=1 CORTEX_M=1 FREEBSD_SYS_HEADERS=1 THUMB1_MODE=1 FREEBSD_FENV=1 ARMLLVM_C=1 GENERIC_C_SIZE_OPTIMIZED=1 FREEBSD_C99_COMPLEX_COMMON=1 FREEBSD_C99_COMPLEX_32_BIT=1 ARMLLVM_RT=1 V6M0=1 THUMB_MODE=1 XLOCALE=1 LITTLE_ENDIAN=1 FREEBSD_MATH_TI_SUPPLEMENT=1 CLASSIC_ERRNO=1 GENERIC_MATH_LIBRARY_INTEGER=1 FULL_WCHAR=1 FREEBSD_C99_COMPLEX_64_BIT=1 TARGET=1 FREEBSD_MATH=1 CLASSIC_MATH_LIBRARY_INTEGER=1 XLOCALE_HEADERS=1 OPENBSD_C99_COMPLEX=1 GENERIC_C=1 CLASSIC_CPP_MATH_OVERLOADS=1
# gmake library LIB=libc_armv7em-ti-none-eabi.lib FREEBSD_C99_COMPLEX_COMMON=1 FREEBSD_FENV=1 ARMLLVM_C=1 GENERIC_C_SIZE_OPTIMIZED=1 FREEBSD_C99_COMPLEX_32_BIT=1 ARMLLVM_RT=1 THUMB2_MODE=1 FREEBSD_C99_COMPLEX=1 FREEBSD_SUPPLEMENTAL_C=1 FREEBSD_MACHINE=1 FREEBSD_MATH_COMMON=1 FREEBSD_MATH_64_BIT=1 FREEBSD_MATH_32_BIT=1 FREEBSD_SYS_HEADERS=1 NOVFP=1 CORTEX_M=1 OPENBSD_C99_COMPLEX=1 XLOCALE_HEADERS=1 TARGET=1 FREEBSD_MATH=1 CLASSIC_MATH_LIBRARY_INTEGER=1 GENERIC_C=1 CLASSIC_CPP_MATH_OVERLOADS=1 V7M4=1 LITTLE_ENDIAN=1 FREEBSD_MATH_TI_SUPPLEMENT=1 XLOCALE=1 THUMB_MODE=1 GENERIC_MATH_LIBRARY_INTEGER=1 FULL_WCHAR=1 FREEBSD_C99_COMPLEX_64_BIT=1 CLASSIC_ERRNO=1
# gmake library LIB=libc_armv7em-ti-none-eabihf.lib XLOCALE=1 THUMB_MODE=1 LITTLE_ENDIAN=1 FREEBSD_MATH_TI_SUPPLEMENT=1 V7M4=1 CLASSIC_ERRNO=1 FREEBSD_C99_COMPLEX_64_BIT=1 GENERIC_MATH_LIBRARY_INTEGER=1 FULL_WCHAR=1 FREEBSD_MATH=1 CLASSIC_MATH_LIBRARY_INTEGER=1 TARGET=1 XLOCALE_HEADERS=1 OPENBSD_C99_COMPLEX=1 CLASSIC_CPP_MATH_OVERLOADS=1 FPV4SPD16=1 GENERIC_C=1 FREEBSD_MATH_64_BIT=1 FREEBSD_MATH_COMMON=1 FREEBSD_MATH_32_BIT=1 FREEBSD_MACHINE=1 FREEBSD_SUPPLEMENTAL_C=1 FREEBSD_C99_COMPLEX=1 CORTEX_M=1 FREEBSD_SYS_HEADERS=1 ARMLLVM_C=1 GENERIC_C_SIZE_OPTIMIZED=1 FREEBSD_FENV=1 FREEBSD_C99_COMPLEX_COMMON=1 ARMLLVM_RT=1 THUMB2_MODE=1 FREEBSD_C99_COMPLEX_32_BIT=1
# gmake library LIB=libc_armv7m-ti-none-eabi.lib FREEBSD_MATH_32_BIT=1 FREEBSD_MATH_64_BIT=1 FREEBSD_MATH_COMMON=1 FREEBSD_C99_COMPLEX=1 FREEBSD_MACHINE=1 FREEBSD_SUPPLEMENTAL_C=1 CORTEX_M=1 FREEBSD_SYS_HEADERS=1 FREEBSD_FENV=1 ARMLLVM_C=1 GENERIC_C_SIZE_OPTIMIZED=1 FREEBSD_C99_COMPLEX_COMMON=1 FREEBSD_C99_COMPLEX_32_BIT=1 ARMLLVM_RT=1 THUMB2_MODE=1 V7M3=1 XLOCALE=1 THUMB_MODE=1 LITTLE_ENDIAN=1 FREEBSD_MATH_TI_SUPPLEMENT=1 CLASSIC_ERRNO=1 GENERIC_MATH_LIBRARY_INTEGER=1 FULL_WCHAR=1 FREEBSD_C99_COMPLEX_64_BIT=1 TARGET=1 FREEBSD_MATH=1 CLASSIC_MATH_LIBRARY_INTEGER=1 XLOCALE_HEADERS=1 OPENBSD_C99_COMPLEX=1 GENERIC_C=1 CLASSIC_CPP_MATH_OVERLOADS=1
# gmake library LIB=libc_armv7r-ti-none-eabi.lib FREEBSD_MATH_TI_SUPPLEMENT=1 LITTLE_ENDIAN=1 XLOCALE=1 FULL_WCHAR=1 GENERIC_MATH_LIBRARY_INTEGER=1 FREEBSD_C99_COMPLEX_64_BIT=1 CLASSIC_ERRNO=1 OPENBSD_C99_COMPLEX=1 XLOCALE_HEADERS=1 TARGET=1 CLASSIC_MATH_LIBRARY_INTEGER=1 FREEBSD_MATH=1 GENERIC_C=1 CLASSIC_CPP_MATH_OVERLOADS=1 FREEBSD_C99_COMPLEX=1 FREEBSD_SUPPLEMENTAL_C=1 FREEBSD_MACHINE=1 FREEBSD_MATH_COMMON=1 FREEBSD_MATH_64_BIT=1 FREEBSD_MATH_32_BIT=1 NOVFP=1 FREEBSD_SYS_HEADERS=1 V7R4=1 FREEBSD_C99_COMPLEX_COMMON=1 FREEBSD_FENV=1 GENERIC_C_SIZE_OPTIMIZED=1 ARMLLVM_C=1 FREEBSD_C99_COMPLEX_32_BIT=1 NON_CORTEX_M=1 ARMLLVM_RT=1
# gmake library LIB=libc_armv7r-ti-none-eabihf.lib NON_CORTEX_M=1 ARMLLVM_RT=1 FREEBSD_C99_COMPLEX_32_BIT=1 ARMLLVM_C=1 GENERIC_C_SIZE_OPTIMIZED=1 FREEBSD_FENV=1 VFPV3D16=1 FREEBSD_C99_COMPLEX_COMMON=1 V7R4=1 FREEBSD_SYS_HEADERS=1 FREEBSD_MATH_COMMON=1 FREEBSD_MATH_64_BIT=1 FREEBSD_MATH_32_BIT=1 FREEBSD_MACHINE=1 FREEBSD_SUPPLEMENTAL_C=1 FREEBSD_C99_COMPLEX=1 CLASSIC_CPP_MATH_OVERLOADS=1 GENERIC_C=1 FREEBSD_MATH=1 CLASSIC_MATH_LIBRARY_INTEGER=1 TARGET=1 OPENBSD_C99_COMPLEX=1 XLOCALE_HEADERS=1 CLASSIC_ERRNO=1 FREEBSD_C99_COMPLEX_64_BIT=1 GENERIC_MATH_LIBRARY_INTEGER=1 FULL_WCHAR=1 XLOCALE=1 LITTLE_ENDIAN=1 FREEBSD_MATH_TI_SUPPLEMENT=1
# gmake library LIB=libc_armv7reb-ti-none-eabi.lib NON_CORTEX_M=1 ARMLLVM_RT=1 FREEBSD_C99_COMPLEX_32_BIT=1 ARMLLVM_C=1 GENERIC_C_SIZE_OPTIMIZED=1 FREEBSD_FENV=1 FREEBSD_C99_COMPLEX_COMMON=1 V7R4=1 FREEBSD_SYS_HEADERS=1 NOVFP=1 BIG_ENDIAN=1 FREEBSD_MATH_32_BIT=1 FREEBSD_MATH_64_BIT=1 FREEBSD_MATH_COMMON=1 FREEBSD_MACHINE=1 FREEBSD_SUPPLEMENTAL_C=1 FREEBSD_C99_COMPLEX=1 CLASSIC_CPP_MATH_OVERLOADS=1 GENERIC_C=1 FREEBSD_MATH=1 CLASSIC_MATH_LIBRARY_INTEGER=1 TARGET=1 XLOCALE_HEADERS=1 OPENBSD_C99_COMPLEX=1 CLASSIC_ERRNO=1 FREEBSD_C99_COMPLEX_64_BIT=1 GENERIC_MATH_LIBRARY_INTEGER=1 FULL_WCHAR=1 XLOCALE=1 FREEBSD_MATH_TI_SUPPLEMENT=1
# gmake library LIB=libc_armv7reb-ti-none-eabihf.lib GENERIC_C=1 CLASSIC_CPP_MATH_OVERLOADS=1 TARGET=1 FREEBSD_MATH=1 CLASSIC_MATH_LIBRARY_INTEGER=1 OPENBSD_C99_COMPLEX=1 XLOCALE_HEADERS=1 CLASSIC_ERRNO=1 GENERIC_MATH_LIBRARY_INTEGER=1 FULL_WCHAR=1 FREEBSD_C99_COMPLEX_64_BIT=1 XLOCALE=1 FREEBSD_MATH_TI_SUPPLEMENT=1 FREEBSD_C99_COMPLEX_32_BIT=1 ARMLLVM_RT=1 NON_CORTEX_M=1 FREEBSD_FENV=1 VFPV3D16=1 ARMLLVM_C=1 GENERIC_C_SIZE_OPTIMIZED=1 FREEBSD_C99_COMPLEX_COMMON=1 V7R4=1 FREEBSD_SYS_HEADERS=1 BIG_ENDIAN=1 FREEBSD_MATH_32_BIT=1 FREEBSD_MATH_COMMON=1 FREEBSD_MATH_64_BIT=1 FREEBSD_C99_COMPLEX=1 FREEBSD_SUPPLEMENTAL_C=1 FREEBSD_MACHINE=1
# gmake library LIB=libc_armv8m.main-ti-none-eabi.lib ARMLLVM_RT=1 THUMB2_MODE=1 V8M33=1 FREEBSD_C99_COMPLEX_32_BIT=1 FREEBSD_C99_COMPLEX_COMMON=1 ARMLLVM_C=1 GENERIC_C_SIZE_OPTIMIZED=1 FREEBSD_FENV=1 FREEBSD_SYS_HEADERS=1 NOVFP=1 CORTEX_M=1 FREEBSD_MACHINE=1 FREEBSD_SUPPLEMENTAL_C=1 FREEBSD_C99_COMPLEX=1 FREEBSD_MATH_COMMON=1 FREEBSD_MATH_64_BIT=1 FREEBSD_MATH_32_BIT=1 CLASSIC_CPP_MATH_OVERLOADS=1 GENERIC_C=1 XLOCALE_HEADERS=1 OPENBSD_C99_COMPLEX=1 FREEBSD_MATH=1 CLASSIC_MATH_LIBRARY_INTEGER=1 TARGET=1 FREEBSD_C99_COMPLEX_64_BIT=1 GENERIC_MATH_LIBRARY_INTEGER=1 FULL_WCHAR=1 CLASSIC_ERRNO=1 LITTLE_ENDIAN=1 FREEBSD_MATH_TI_SUPPLEMENT=1 THUMB_MODE=1 XLOCALE=1
# gmake library LIB=libc_armv8m.main-ti-none-eabihf.lib FREEBSD_SUPPLEMENTAL_C=1 FREEBSD_MACHINE=1 FREEBSD_C99_COMPLEX=1 FREEBSD_MATH_COMMON=1 FREEBSD_MATH_32_BIT=1 FREEBSD_MATH_64_BIT=1 FREEBSD_SYS_HEADERS=1 CORTEX_M=1 FREEBSD_C99_COMPLEX_COMMON=1 GENERIC_C_SIZE_OPTIMIZED=1 ARMLLVM_C=1 FREEBSD_FENV=1 THUMB2_MODE=1 ARMLLVM_RT=1 V8M33=1 FREEBSD_C99_COMPLEX_32_BIT=1 FREEBSD_MATH_TI_SUPPLEMENT=1 FPV5SPD16=1 LITTLE_ENDIAN=1 THUMB_MODE=1 XLOCALE=1 FREEBSD_C99_COMPLEX_64_BIT=1 FULL_WCHAR=1 GENERIC_MATH_LIBRARY_INTEGER=1 CLASSIC_ERRNO=1 XLOCALE_HEADERS=1 OPENBSD_C99_COMPLEX=1 CLASSIC_MATH_LIBRARY_INTEGER=1 FREEBSD_MATH=1 TARGET=1 CLASSIC_CPP_MATH_OVERLOADS=1 GENERIC_C=1
# gmake library LIB=libsysbm_armv6m-ti-none-eabi.lib THUMB_MODE=1 ARMLLVM_SYS=1 LITTLE_ENDIAN=1 GENERIC_SYS=1 CORTEX_M=1 THUMB1_MODE=1 V6M0=1
# gmake library LIB=libsysbm_armv7em-ti-none-eabi.lib V7M4=1 LITTLE_ENDIAN=1 ARMLLVM_SYS=1 THUMB_MODE=1 NOVFP=1 CORTEX_M=1 GENERIC_SYS=1 THUMB2_MODE=1
# gmake library LIB=libsysbm_armv7em-ti-none-eabihf.lib THUMB_MODE=1 ARMLLVM_SYS=1 LITTLE_ENDIAN=1 V7M4=1 THUMB2_MODE=1 CORTEX_M=1 GENERIC_SYS=1 FPV4SPD16=1
# gmake library LIB=libsysbm_armv7m-ti-none-eabi.lib CORTEX_M=1 GENERIC_SYS=1 THUMB2_MODE=1 V7M3=1 ARMLLVM_SYS=1 THUMB_MODE=1 LITTLE_ENDIAN=1
# gmake library LIB=libsysbm_armv7r-ti-none-eabi.lib ARM_MODE=1 GENERIC_SYS=1 NON_CORTEX_M=1 V7R4=1 NOVFP=1 ARMLLVM_SYS=1 LITTLE_ENDIAN=1
# gmake library LIB=libsysbm_armv7r-ti-none-eabihf.lib ARM_MODE=1 NON_CORTEX_M=1 V7R4=1 GENERIC_SYS=1 LITTLE_ENDIAN=1 VFPV3D16=1 ARMLLVM_SYS=1
# gmake library LIB=libsysbm_armv7reb-ti-none-eabi.lib BIG_ENDIAN=1 ARMLLVM_SYS=1 NOVFP=1 NON_CORTEX_M=1 V7R4=1 GENERIC_SYS=1 ARM_MODE=1
# gmake library LIB=libsysbm_armv7reb-ti-none-eabihf.lib V7R4=1 NON_CORTEX_M=1 GENERIC_SYS=1 ARM_MODE=1 VFPV3D16=1 BIG_ENDIAN=1 ARMLLVM_SYS=1
# gmake library LIB=libsysbm_armv8m.main-ti-none-eabi.lib NOVFP=1 V8M33=1 CORTEX_M=1 GENERIC_SYS=1 THUMB2_MODE=1 LITTLE_ENDIAN=1 ARMLLVM_SYS=1 THUMB_MODE=1
# gmake library LIB=libsysbm_armv8m.main-ti-none-eabihf.lib ARMLLVM_SYS=1 THUMB_MODE=1 FPV5SPD16=1 LITTLE_ENDIAN=1 CORTEX_M=1 GENERIC_SYS=1 THUMB2_MODE=1 V8M33=1
##############################################################################

ifdef CMD_FILE
 -include $(CMD_FILE)
endif
#-----------------------------------------------------------------------------
# Basic definitions
#-----------------------------------------------------------------------------
ifeq (y,$(shell [ -e $(CGT_BIN)//tmp/scratch/build_jenkins/workspace/BuildAndValidate_Worker/llvm_cgt/arm-llvm/Release/llvm/bin/clang ] && echo y))
  CC = $(CGT_BIN)//tmp/scratch/build_jenkins/workspace/BuildAndValidate_Worker/llvm_cgt/arm-llvm/Release/llvm/bin/clang
else
  CC = /tmp/scratch/build_jenkins/workspace/BuildAndValidate_Worker/llvm_cgt/arm-llvm/Release/llvm/bin/clang
endif
ifeq (y,$(shell [ -e $(CGT_BIN)//tmp/scratch/build_jenkins/workspace/BuildAndValidate_Worker/llvm_cgt/arm-llvm/Release/llvm/bin/llvm-ar ] && echo y))
  AR = $(CGT_BIN)//tmp/scratch/build_jenkins/workspace/BuildAndValidate_Worker/llvm_cgt/arm-llvm/Release/llvm/bin/llvm-ar
else
  AR = /tmp/scratch/build_jenkins/workspace/BuildAndValidate_Worker/llvm_cgt/arm-llvm/Release/llvm/bin/llvm-ar
endif
CD = cd

#-----------------------------------------------------------------------------
# Group TARGET
#-----------------------------------------------------------------------------
ifeq ($(TARGET),1)
ARMLLVM_C=1
ARMLLVM_RT=1
REMOVE_GROUP=1
endif


#-----------------------------------------------------------------------------
# Group ARMLLVM_C
#-----------------------------------------------------------------------------
ifeq ($(ARMLLVM_C),1)
FREEBSD_MATH=1
GENERIC_C=1
FULL_WCHAR=1
FREEBSD_MACHINE=1
FREEBSD_SUPPLEMENTAL_C=1

ARMLLVM_C_C_SOURCE = \
	aeabi_portable.c \
	aeabi_atexit.c

C_SOURCE += $(ARMLLVM_C_C_SOURCE)


ARMLLVM_C_ASM_SOURCE = \
	aeabi_ctype.S

ASM_SOURCE += $(ARMLLVM_C_ASM_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group FREEBSD_MATH
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_MATH),1)
FREEBSD_MATH_COMMON=1
FREEBSD_MATH_32_BIT=1
FREEBSD_MATH_64_BIT=1
FREEBSD_C99_COMPLEX=1
endif


#-----------------------------------------------------------------------------
# Group V7M4
#-----------------------------------------------------------------------------
ifeq ($(V7M4),1)
CORTEX_M=1
THUMB2_MODE=1
UNIVERSAL_FLAGS += -mcpu=cortex-m4
endif


#-----------------------------------------------------------------------------
# Group FULL_WCHAR
#-----------------------------------------------------------------------------
ifeq ($(FULL_WCHAR),1)
XLOCALE=1
FREEBSD_SYS_HEADERS=1
FULL_WCHAR_FLAGS += -DSTRIP_FBSDID -D_XOPEN_SOURCE=700 

FULL_WCHAR_C_SOURCE = \
	wcstof.c \
	wcstod.c \
	wcstold.c \
	wcstol.c \
	wcstoul.c \
	wcstoll.c \
	wcstoull.c \
	wcstoimax.c \
	wcstoumax.c \
	wcsftime.c \
	fwprintf.c \
	fwscanf.c \
	swprintf.c \
	swscanf.c \
	vwprintf.c \
	vwscanf.c \
	wprintf.c \
	wscanf.c \
	wcscat.c \
	wcschr.c \
	wcscmp.c \
	wcscpy.c \
	wcscspn.c \
	wcsdup.c \
	wcslen.c \
	wcsncat.c \
	wcsncmp.c \
	wcsncpy.c \
	wcspbrk.c \
	wcsrchr.c \
	wcsspn.c \
	wcsstr.c \
	wcstok.c \
	wmemchr.c \
	wmemcpy.c \
	wmemcmp.c \
	wmemmove.c \
	wmemset.c \
	none_mb.c \
	fgetwc.c \
	fgetws.c \
	fputws.c \
	vfwprintf.c \
	vfwscanf.c \
	vswprintf.c \
	vswscanf.c \
	wcscoll.c \
	wcsxfrm.c
endif


#-----------------------------------------------------------------------------
# Group V8M33
#-----------------------------------------------------------------------------
ifeq ($(V8M33),1)
CORTEX_M=1
THUMB2_MODE=1
UNIVERSAL_FLAGS += -mcpu=cortex-m33
endif


#-----------------------------------------------------------------------------
# Group V7M3
#-----------------------------------------------------------------------------
ifeq ($(V7M3),1)
CORTEX_M=1
THUMB2_MODE=1
UNIVERSAL_FLAGS += -mcpu=cortex-m3
endif


#-----------------------------------------------------------------------------
# Group V6M0
#-----------------------------------------------------------------------------
ifeq ($(V6M0),1)
THUMB1_MODE=1
CORTEX_M=1
UNIVERSAL_FLAGS += -mcpu=cortex-m0 -D __small_divide__
endif


#-----------------------------------------------------------------------------
# Group GENERIC_C
#-----------------------------------------------------------------------------
ifeq ($(GENERIC_C),1)
GENERIC_C_SIZE_OPTIMIZED=1

GENERIC_C_C_SOURCE = \
	exit.c \
	_data_synch.c \
	_lock.c \
	_ltoa.c \
	_mutex.c \
	_pthread.c \
	args_main.c \
	asctime.c \
	assert.c \
	atof.c \
	atoi.c \
	atol.c \
	atoll.c \
	bcmp.c \
	bcopy.c \
	bsearch.c \
	bzero.c \
	clearerr.c \
	common_exit.c \
	ctime_.c \
	ctime64.c \
	defs.c \
	difftime.c \
	difftime64.c \
	ecvt.c \
	fcvt.c \
	ffs.c \
	gmtime.c \
	gmtime64.c \
	index.c \
	isalnum.c \
	isalpha.c \
	isascii.c \
	iscntrl.c \
	isdigit.c \
	isgraph.c \
	islower.c \
	isprint.c \
	ispunct.c \
	isspace.c \
	isupper.c \
	isxdigit.c \
	localtim.c \
	localtim64.c \
	ltoa.c \
	memccpy.c \
	memchr.c \
	memcmp.c \
	memmov.c \
	memory.c \
	mktime.c \
	mktime64.c \
	perror.c \
	qsort.c \
	quick_exit.c \
	rand.c \
	rewind.c \
	rindex.c \
	setlocale.c \
	strcasecmp.c \
	strcat.c \
	strchr.c \
	strcmp.c \
	strcoll.c \
	strcpy.c \
	strcspn.c \
	strdup.c \
	strerror.c \
	strftime.c \
	strlen.c \
	strncasecmp.c \
	strncat.c \
	strncmp.c \
	strncpy.c \
	strpbrk.c \
	strrchr.c \
	strspn.c \
	strstr.c \
	strtod.c \
	strtof.c \
	strtok.c \
	strtol.c \
	strtold.c \
	strtoll.c \
	strtoul.c \
	strtoull.c \
	strtoimax.c \
	strtoumax.c \
	strxfrm.c \
	tmpfile.c \
	tmpnam.c \
	tmzone.c \
	toascii.c \
	tolower.c \
	toupper.c \
	wctype.c \
	signal.c
ifneq ($(FULL_WCHAR),1)
GENERIC_C_C_SOURCE += multibyte.c
endif

C_SOURCE += $(GENERIC_C_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group XLOCALE
#-----------------------------------------------------------------------------
ifeq ($(XLOCALE),1)
XLOCALE_HEADERS=1
XLOCALE_FLAGS += -DSTRIP_FBSDID -D_XOPEN_SOURCE=700 

XLOCALE_C_SOURCE = \
	xlocale.c \
	locale_inttypes.c \
	locale_stdio.c \
	locale_stdlib.c \
	locale_string.c \
	locale_strings.c \
	locale_time.c \
	locale_wchar.c
endif


#-----------------------------------------------------------------------------
# Group ARMLLVM_SYS
#-----------------------------------------------------------------------------
ifeq ($(ARMLLVM_SYS),1)
GENERIC_SYS=1
REMOVE_GROUP=1
endif


#-----------------------------------------------------------------------------
# Group THUMB2_MODE
#-----------------------------------------------------------------------------
ifeq ($(THUMB2_MODE),1)
THUMB_MODE=1

THUMB2_MODE_ASM_SOURCE = \
	memcpy_t2.S \
	setjmp_t2.S \
	memset_t2.S

ASM_SOURCE += $(THUMB2_MODE_ASM_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group FREEBSD_MATH_COMMON
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_MATH_COMMON),1)
OPENBSD_C99_COMPLEX=1
FREEBSD_FENV=1
FREEBSD_MATH_TI_SUPPLEMENT=1
GENERIC_MATH_LIBRARY_INTEGER=1
CLASSIC_MATH_LIBRARY_INTEGER=1
CLASSIC_CPP_MATH_OVERLOADS=1
CLASSIC_ERRNO=1

FREEBSD_MATH_COMMON_C_SOURCE = \
	e_rem_pio2.c \
	e_rem_pio2f.c \
	k_rem_pio2.c

C_SOURCE += $(FREEBSD_MATH_COMMON_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group FREEBSD_C99_COMPLEX
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_C99_COMPLEX),1)
FREEBSD_C99_COMPLEX_32_BIT=1
FREEBSD_C99_COMPLEX_64_BIT=1
FREEBSD_C99_COMPLEX_COMMON=1
FREEBSD_C99_COMPLEX_C_FLAGS += -std=c11
endif


#-----------------------------------------------------------------------------
# Group V7R4
#-----------------------------------------------------------------------------
ifeq ($(V7R4),1)
NON_CORTEX_M=1
UNIVERSAL_FLAGS += -mcpu=cortex-r4
endif


#-----------------------------------------------------------------------------
# Group THUMB1_MODE
#-----------------------------------------------------------------------------
ifeq ($(THUMB1_MODE),1)
THUMB_MODE=1

THUMB1_MODE_ASM_SOURCE = \
	memcpy16.S \
	setjmp16.S \
	hwdiv16.S \
	memset16.S

ASM_SOURCE += $(THUMB1_MODE_ASM_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group CLASSIC_MATH_LIBRARY_INTEGER
#-----------------------------------------------------------------------------
ifeq ($(CLASSIC_MATH_LIBRARY_INTEGER),1)

CLASSIC_MATH_LIBRARY_INTEGER_C_SOURCE = \
	abs.c \
	labs.c \
	llabs.c \
	imaxabs.c \
	imaxdiv.c

C_SOURCE += $(CLASSIC_MATH_LIBRARY_INTEGER_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group OPENBSD_C99_COMPLEX
#-----------------------------------------------------------------------------
ifeq ($(OPENBSD_C99_COMPLEX),1)
OPENBSD_C99_COMPLEX_C_FLAGS += -std=c11

OPENBSD_C99_COMPLEX_C_SOURCE = \
	s_clog.c \
	s_clogf.c \
	s_clogl.c \
	s_cpow.c \
	s_cpowf.c \
	s_cpowl.c
endif


#-----------------------------------------------------------------------------
# Group XLOCALE_HEADERS
#-----------------------------------------------------------------------------
ifeq ($(XLOCALE_HEADERS),1)
endif


#-----------------------------------------------------------------------------
# Group ARM_MODE
#-----------------------------------------------------------------------------
ifeq ($(ARM_MODE),1)

ARM_MODE_ASM_SOURCE = \
	memcpy32.S \
	setjmp32.S \
	memset32.S

ASM_SOURCE += $(ARM_MODE_ASM_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group GENERIC_SYS
#-----------------------------------------------------------------------------
ifeq ($(GENERIC_SYS),1)

GENERIC_SYS_C_SOURCE = \
	write.c \
	unlink.c \
	hostclock.c \
	hostclose.c \
	hostgetenv.c \
	hostlseek.c \
	hostopen.c \
	hostread.c \
	hostrename.c \
	hosttime.c \
	hostunlink.c \
	hostwrite.c \
	host_device.c \
	trgmsg.c \
	time.c \
	time64.c \
	rename.c \
	remove.c \
	remove_device.c \
	read.c \
	open.c \
	lseek.c \
	close.c \
	clock.c \
	add_device.c

C_SOURCE += $(GENERIC_SYS_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group FPV4SPD16
#-----------------------------------------------------------------------------
ifeq ($(FPV4SPD16),1)
UNIVERSAL_FLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
endif


#-----------------------------------------------------------------------------
# Group CLASSIC_CPP_MATH_OVERLOADS
#-----------------------------------------------------------------------------
ifeq ($(CLASSIC_CPP_MATH_OVERLOADS),1)
endif


#-----------------------------------------------------------------------------
# Group THUMB_MODE
#-----------------------------------------------------------------------------
ifeq ($(THUMB_MODE),1)
UNIVERSAL_FLAGS += -mthumb
endif


#-----------------------------------------------------------------------------
# Group LITTLE_ENDIAN
#-----------------------------------------------------------------------------
ifeq ($(LITTLE_ENDIAN),1)
UNIVERSAL_FLAGS += -mlittle-endian
endif


#-----------------------------------------------------------------------------
# Group FPV5SPD16
#-----------------------------------------------------------------------------
ifeq ($(FPV5SPD16),1)
UNIVERSAL_FLAGS += -mfpu=fpv5-sp-d16 -mfloat-abi=hard
endif


#-----------------------------------------------------------------------------
# Group FREEBSD_MATH_TI_SUPPLEMENT
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_MATH_TI_SUPPLEMENT),1)
FREEBSD_MATH_TI_SUPPLEMENT_C_FLAGS += -std=c11

FREEBSD_MATH_TI_SUPPLEMENT_C_SOURCE = \
	ti_fenv.c \
	ti_fmax.c \
	ti_nan.c
endif


#-----------------------------------------------------------------------------
# Group CLASSIC_ERRNO
#-----------------------------------------------------------------------------
ifeq ($(CLASSIC_ERRNO),1)

CLASSIC_ERRNO_C_SOURCE = \
	errno.c

C_SOURCE += $(CLASSIC_ERRNO_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group GENERIC_MATH_LIBRARY_INTEGER
#-----------------------------------------------------------------------------
ifeq ($(GENERIC_MATH_LIBRARY_INTEGER),1)

GENERIC_MATH_LIBRARY_INTEGER_C_SOURCE = \
	div.c \
	ldiv.c \
	lldiv.c

C_SOURCE += $(GENERIC_MATH_LIBRARY_INTEGER_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group REMOVE_GROUP
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Group FREEBSD_C99_COMPLEX_64_BIT
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_C99_COMPLEX_64_BIT),1)
FREEBSD_C99_COMPLEX_64_BIT_C_FLAGS += -std=c11

FREEBSD_C99_COMPLEX_64_BIT_C_SOURCE = \
	catrig.c \
	k_exp.c \
	s_ccosh.c \
	s_cexp.c \
	s_csinh.c \
	s_csqrt.c \
	s_ctanh.c \
	s_log1p.c \
	e_hypot.c \
	s_copysign.c
endif


#-----------------------------------------------------------------------------
# Group GENERIC_OPTIONS
#-----------------------------------------------------------------------------
CPP_FLAGS += --rtti -fg
UNIVERSAL_FLAGS += -c -Oz -ffunction-sections -fdata-sections -fomit-frame-pointer -fvisibility=hidden -Wno-shift-op-parentheses -Wno-dangling-else -Wno-main -Wpragmas -D__TI_RTS_BUILD
ASM_FLAGS += 

#-----------------------------------------------------------------------------
# Group FREEBSD_FENV
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_FENV),1)

FREEBSD_FENV_C_SOURCE = \
	fenv.c

C_SOURCE += $(FREEBSD_FENV_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group VFPV3D16
#-----------------------------------------------------------------------------
ifeq ($(VFPV3D16),1)
UNIVERSAL_FLAGS += -mfpu=vfpv3-d16 -mfloat-abi=hard
endif


#-----------------------------------------------------------------------------
# Group GENERIC_C_SIZE_OPTIMIZED
#-----------------------------------------------------------------------------
ifeq ($(GENERIC_C_SIZE_OPTIMIZED),1)
GENERIC_C_SIZE_OPTIMIZED_FLAGS += 

GENERIC_C_SIZE_OPTIMIZED_C_SOURCE = \
	printf.c \
	fprintf.c \
	_printfi.c \
	_printfi_template.c \
	_printfi_vector.c \
	snprintf.c \
	sprintf.c \
	vfprintf.c \
	vprintf.c \
	vsnprintf.c \
	vsprintf.c \
	_scanfi.c \
	_scanfi_min.c \
	_scanfi_nf.c \
	fscanf.c \
	sscanf.c \
	fclose.c \
	feof.c \
	ferror.c \
	fflush.c \
	fgetc.c \
	fgetpos.c \
	fgets.c \
	fopen.c \
	fputc.c \
	fputs.c \
	fread.c \
	fseek.c \
	fsetpos.c \
	ftell.c \
	fwrite.c \
	_bufread.c \
	_io_perm.c \
	getenv.c \
	getdevice.c \
	setbuf.c \
	setvbuf.c \
	ungetc.c
endif


#-----------------------------------------------------------------------------
# Group FREEBSD_C99_COMPLEX_COMMON
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_C99_COMPLEX_COMMON),1)
endif


#-----------------------------------------------------------------------------
# Group FREEBSD_C99_COMPLEX_32_BIT
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_C99_COMPLEX_32_BIT),1)
FREEBSD_C99_COMPLEX_32_BIT_C_FLAGS += -std=c11

FREEBSD_C99_COMPLEX_32_BIT_C_SOURCE = \
	catrigf.c \
	k_expf.c \
	s_carg.c \
	s_cargf.c \
	s_cargl.c \
	s_ccoshf.c \
	s_cexpf.c \
	s_cimag.c \
	s_cimagf.c \
	s_cimagl.c \
	s_conj.c \
	s_conjf.c \
	s_conjl.c \
	s_cproj.c \
	s_cprojf.c \
	s_cprojl.c \
	s_creal.c \
	s_crealf.c \
	s_creall.c \
	s_csinhf.c \
	s_csqrtf.c \
	s_ctanhf.c \
	w_cabs.c \
	w_cabsf.c \
	w_cabsl.c \
	s_log1pf.c \
	e_hypotf.c \
	s_copysignf.c
endif


#-----------------------------------------------------------------------------
# Group NON_CORTEX_M
#-----------------------------------------------------------------------------
ifeq ($(NON_CORTEX_M),1)

NON_CORTEX_M_ASM_SOURCE = \
	boot_non_cortex_m.S

ASM_SOURCE += $(NON_CORTEX_M_ASM_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group ARMLLVM_RT
#-----------------------------------------------------------------------------
ifeq ($(ARMLLVM_RT),1)

ARMLLVM_RT_C_SOURCE = \
	mpu_init.c \
	autoinit.c \
	pre_init.c \
	startup.c \
	cpy_tbl.c \
	copy_zero_init.c \
	copy_decompress_none.c \
	copy_decompress_rle.c \
	copy_decompress_lzss.c

C_SOURCE += $(ARMLLVM_RT_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group BIG_ENDIAN
#-----------------------------------------------------------------------------
ifeq ($(BIG_ENDIAN),1)
UNIVERSAL_FLAGS += -mbig-endian
endif


#-----------------------------------------------------------------------------
# Group FREEBSD_MATH_64_BIT
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_MATH_64_BIT),1)
FREEBSD_MATH_64_BIT_C_FLAGS += -std=c11

FREEBSD_MATH_64_BIT_C_SOURCE = \
	b_exp.c \
	b_log.c \
	b_tgamma.c \
	e_acos.c \
	e_acosh.c \
	e_asin.c \
	e_atan2.c \
	e_atanh.c \
	e_cosh.c \
	e_exp.c \
	e_fmod.c \
	e_lgamma.c \
	e_lgamma_r.c \
	e_log.c \
	e_log10.c \
	e_log2.c \
	e_pow.c \
	e_remainder.c \
	e_sinh.c \
	e_sqrt.c \
	k_cos.c \
	k_sin.c \
	k_tan.c \
	s_asinh.c \
	s_atan.c \
	s_cbrt.c \
	s_ceil.c \
	s_cos.c \
	s_erf.c \
	s_exp2.c \
	s_expm1.c \
	s_fabs.c \
	s_floor.c \
	s_fma.c \
	s_frexp.c \
	s_ilogb.c \
	s_logb.c \
	s_modf.c \
	s_nextafter.c \
	s_remquo.c \
	s_rint.c \
	s_round.c \
	s_scalbn.c \
	s_sin.c \
	s_tan.c \
	s_tanh.c \
	s_trunc.c
endif


#-----------------------------------------------------------------------------
# Group FREEBSD_MATH_32_BIT
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_MATH_32_BIT),1)
FREEBSD_MATH_32_BIT_C_FLAGS += -std=c11

FREEBSD_MATH_32_BIT_C_SOURCE = \
	e_acosf.c \
	e_acoshf.c \
	e_asinf.c \
	e_atan2f.c \
	e_atanhf.c \
	e_coshf.c \
	e_expf.c \
	e_fmodf.c \
	e_lgammaf.c \
	e_lgammaf_r.c \
	e_log10f.c \
	e_log2f.c \
	e_logf.c \
	e_powf.c \
	e_remainderf.c \
	e_sinhf.c \
	e_sqrtf.c \
	k_cosf.c \
	k_sinf.c \
	k_tanf.c \
	s_asinhf.c \
	s_atanf.c \
	s_cbrtf.c \
	s_ceilf.c \
	s_cosf.c \
	s_erff.c \
	s_exp2f.c \
	s_expm1f.c \
	s_fabsf.c \
	s_fdim.c \
	s_floorf.c \
	s_fmaf.c \
	s_frexpf.c \
	s_ilogbf.c \
	s_logbf.c \
	s_llrint.c \
	s_llrintf.c \
	s_llrintl.c \
	s_llround.c \
	s_llroundf.c \
	s_llroundl.c \
	s_lrint.c \
	s_lrintf.c \
	s_lrintl.c \
	s_lround.c \
	s_lroundf.c \
	s_lroundl.c \
	s_modff.c \
	s_nearbyint.c \
	s_nextafterf.c \
	s_nexttowardf.c \
	s_remquof.c \
	s_rintf.c \
	s_roundf.c \
	s_scalbln.c \
	s_scalbnf.c \
	s_sinf.c \
	s_tanf.c \
	s_tanhf.c \
	s_tgammaf.c \
	s_truncf.c
endif


#-----------------------------------------------------------------------------
# Group FREEBSD_MACHINE
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_MACHINE),1)
endif


#-----------------------------------------------------------------------------
# Group FREEBSD_SUPPLEMENTAL_C
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_SUPPLEMENTAL_C),1)

FREEBSD_SUPPLEMENTAL_C_C_SOURCE = \
	asprintf.c \
	vasprintf.c \
	stpcpy.c \
	stpncpy.c

C_SOURCE += $(FREEBSD_SUPPLEMENTAL_C_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group CORTEX_M
#-----------------------------------------------------------------------------
ifeq ($(CORTEX_M),1)

CORTEX_M_C_SOURCE = \
	boot_cortex_m.c \
	mathacl_init.c

C_SOURCE += $(CORTEX_M_C_SOURCE)

endif


#-----------------------------------------------------------------------------
# Group FREEBSD_SYS_HEADERS
#-----------------------------------------------------------------------------
ifeq ($(FREEBSD_SYS_HEADERS),1)
endif


#-----------------------------------------------------------------------------
# Group NOVFP
#-----------------------------------------------------------------------------
ifeq ($(NOVFP),1)
UNIVERSAL_FLAGS += -mfpu=none -mfloat-abi=soft
endif



FREEBSD_MATH_32_BIT_C_OBJS_1 = $(patsubst %.c,$(OBJ)/%.c.obj,$(FREEBSD_MATH_32_BIT_C_SOURCE))
$(FREEBSD_MATH_32_BIT_C_OBJS_1): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(FREEBSD_MATH_32_BIT_FLAGS) $(C_FLAGS) $(FREEBSD_MATH_32_BIT_C_FLAGS) -I$(INC) -o $@ -MMD -MP -MF $(OBJ)/$*.Td
	@$(MV_CMD) $(OBJ)/$*.Td $(OBJ)/$*.P

FREEBSD_MATH_64_BIT_C_OBJS_2 = $(patsubst %.c,$(OBJ)/%.c.obj,$(FREEBSD_MATH_64_BIT_C_SOURCE))
$(FREEBSD_MATH_64_BIT_C_OBJS_2): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(FREEBSD_MATH_64_BIT_FLAGS) $(C_FLAGS) $(FREEBSD_MATH_64_BIT_C_FLAGS) -I$(INC) -o $@ -MMD -MP -MF $(OBJ)/$*.Td
	@$(MV_CMD) $(OBJ)/$*.Td $(OBJ)/$*.P

FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_3 = $(patsubst %.c,$(OBJ)/%.c.obj,$(FREEBSD_C99_COMPLEX_32_BIT_C_SOURCE))
$(FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_3): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(FREEBSD_C99_COMPLEX_32_BIT_FLAGS) $(C_FLAGS) $(FREEBSD_C99_COMPLEX_32_BIT_C_FLAGS) -I$(INC) -o $@ -MMD -MP -MF $(OBJ)/$*.Td
	@$(MV_CMD) $(OBJ)/$*.Td $(OBJ)/$*.P

GENERIC_C_SIZE_OPTIMIZED_C_OBJS_4 = $(patsubst %.c,$(OBJ)/%.c.obj,$(GENERIC_C_SIZE_OPTIMIZED_C_SOURCE))
$(GENERIC_C_SIZE_OPTIMIZED_C_OBJS_4): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(GENERIC_C_SIZE_OPTIMIZED_FLAGS) $(C_FLAGS) $(GENERIC_C_SIZE_OPTIMIZED_C_FLAGS) -I$(INC) -o $@ -MMD -MP -MF $(OBJ)/$*.Td
	@$(MV_CMD) $(OBJ)/$*.Td $(OBJ)/$*.P

FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_5 = $(patsubst %.c,$(OBJ)/%.c.obj,$(FREEBSD_C99_COMPLEX_64_BIT_C_SOURCE))
$(FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_5): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(FREEBSD_C99_COMPLEX_64_BIT_FLAGS) $(C_FLAGS) $(FREEBSD_C99_COMPLEX_64_BIT_C_FLAGS) -I$(INC) -o $@ -MMD -MP -MF $(OBJ)/$*.Td
	@$(MV_CMD) $(OBJ)/$*.Td $(OBJ)/$*.P

FULL_WCHAR_C_OBJS_6 = $(patsubst %.c,$(OBJ)/%.c.obj,$(FULL_WCHAR_C_SOURCE))
$(FULL_WCHAR_C_OBJS_6): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(FULL_WCHAR_FLAGS) $(C_FLAGS) $(FULL_WCHAR_C_FLAGS) -I$(INC) -o $@ -MMD -MP -MF $(OBJ)/$*.Td
	@$(MV_CMD) $(OBJ)/$*.Td $(OBJ)/$*.P

FREEBSD_MATH_TI_SUPPLEMENT_C_OBJS_7 = $(patsubst %.c,$(OBJ)/%.c.obj,$(FREEBSD_MATH_TI_SUPPLEMENT_C_SOURCE))
$(FREEBSD_MATH_TI_SUPPLEMENT_C_OBJS_7): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(FREEBSD_MATH_TI_SUPPLEMENT_FLAGS) $(C_FLAGS) $(FREEBSD_MATH_TI_SUPPLEMENT_C_FLAGS) -I$(INC) -o $@ -MMD -MP -MF $(OBJ)/$*.Td
	@$(MV_CMD) $(OBJ)/$*.Td $(OBJ)/$*.P

XLOCALE_C_OBJS_8 = $(patsubst %.c,$(OBJ)/%.c.obj,$(XLOCALE_C_SOURCE))
$(XLOCALE_C_OBJS_8): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(XLOCALE_FLAGS) $(C_FLAGS) $(XLOCALE_C_FLAGS) -I$(INC) -o $@ -MMD -MP -MF $(OBJ)/$*.Td
	@$(MV_CMD) $(OBJ)/$*.Td $(OBJ)/$*.P

OPENBSD_C99_COMPLEX_C_OBJS_9 = $(patsubst %.c,$(OBJ)/%.c.obj,$(OPENBSD_C99_COMPLEX_C_SOURCE))
$(OPENBSD_C99_COMPLEX_C_OBJS_9): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(OPENBSD_C99_COMPLEX_FLAGS) $(C_FLAGS) $(OPENBSD_C99_COMPLEX_C_FLAGS) -I$(INC) -o $@ -MMD -MP -MF $(OBJ)/$*.Td
	@$(MV_CMD) $(OBJ)/$*.Td $(OBJ)/$*.P

ASM_OBJS_10 = $(patsubst %.S,$(OBJ)/%.S.obj,$(ASM_SOURCE))
$(ASM_OBJS_10): $(OBJ)/%.S.obj: %.S
	$(CC) $< $(EXTRA_FLAGS) $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(UNIVERSAL_FLAGS) $(ASM_FLAGS) -I$(INC) -o $@ -MMD -MP -MF $(OBJ)/$*.Td
	@$(MV_CMD) $(OBJ)/$*.Td $(OBJ)/$*.P

C_OBJS_11 = $(patsubst %.c,$(OBJ)/%.c.obj,$(C_SOURCE))
$(C_OBJS_11): $(OBJ)/%.c.obj: %.c
	$(CC) $< $(EXTRA_FLAGS) $(STANDARD_FLAGS) $(EXTRA_FLAGS) $(UNIVERSAL_FLAGS) $(UNIVERSAL_FLAGS) $(C_FLAGS) -I$(INC) -o $@ -MMD -MP -MF $(OBJ)/$*.Td
	@$(MV_CMD) $(OBJ)/$*.Td $(OBJ)/$*.P

ALL_OBJS = $(FREEBSD_MATH_32_BIT_C_OBJS_1) $(FREEBSD_MATH_64_BIT_C_OBJS_2) $(FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_3) $(GENERIC_C_SIZE_OPTIMIZED_C_OBJS_4) $(FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_5) $(FULL_WCHAR_C_OBJS_6) $(FREEBSD_MATH_TI_SUPPLEMENT_C_OBJS_7) $(XLOCALE_C_OBJS_8) $(OPENBSD_C99_COMPLEX_C_OBJS_9) $(ASM_OBJS_10) $(C_OBJS_11)
RELATIVE_FREEBSD_MATH_32_BIT_C_OBJS_1 := $(foreach obj,$(FREEBSD_MATH_32_BIT_C_OBJS_1),$(subst $(OBJ)/,,$(obj)))
RELATIVE_FREEBSD_MATH_64_BIT_C_OBJS_2 := $(foreach obj,$(FREEBSD_MATH_64_BIT_C_OBJS_2),$(subst $(OBJ)/,,$(obj)))
RELATIVE_FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_3 := $(foreach obj,$(FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_3),$(subst $(OBJ)/,,$(obj)))
RELATIVE_GENERIC_C_SIZE_OPTIMIZED_C_OBJS_4 := $(foreach obj,$(GENERIC_C_SIZE_OPTIMIZED_C_OBJS_4),$(subst $(OBJ)/,,$(obj)))
RELATIVE_FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_5 := $(foreach obj,$(FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_5),$(subst $(OBJ)/,,$(obj)))
RELATIVE_FULL_WCHAR_C_OBJS_6 := $(foreach obj,$(FULL_WCHAR_C_OBJS_6),$(subst $(OBJ)/,,$(obj)))
RELATIVE_FREEBSD_MATH_TI_SUPPLEMENT_C_OBJS_7 := $(foreach obj,$(FREEBSD_MATH_TI_SUPPLEMENT_C_OBJS_7),$(subst $(OBJ)/,,$(obj)))
RELATIVE_XLOCALE_C_OBJS_8 := $(foreach obj,$(XLOCALE_C_OBJS_8),$(subst $(OBJ)/,,$(obj)))
RELATIVE_OPENBSD_C99_COMPLEX_C_OBJS_9 := $(foreach obj,$(OPENBSD_C99_COMPLEX_C_OBJS_9),$(subst $(OBJ)/,,$(obj)))
RELATIVE_ASM_OBJS_10 := $(foreach obj,$(ASM_OBJS_10),$(subst $(OBJ)/,,$(obj)))
RELATIVE_C_OBJS_11 := $(foreach obj,$(C_OBJS_11),$(subst $(OBJ)/,,$(obj)))

-include $(ALL_OBJS:.obj=.P)

library: $(ALL_OBJS)
	@echo "Creating library $(LIB)"
	$(CD) $(OBJ); $(AR) r $(LIB) $(RELATIVE_FREEBSD_MATH_32_BIT_C_OBJS_1)
	$(CD) $(OBJ); $(AR) r $(LIB) $(RELATIVE_FREEBSD_MATH_64_BIT_C_OBJS_2)
	$(CD) $(OBJ); $(AR) r $(LIB) $(RELATIVE_FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_3)
	$(CD) $(OBJ); $(AR) r $(LIB) $(RELATIVE_GENERIC_C_SIZE_OPTIMIZED_C_OBJS_4)
	$(CD) $(OBJ); $(AR) r $(LIB) $(RELATIVE_FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_5)
	$(CD) $(OBJ); $(AR) r $(LIB) $(RELATIVE_FULL_WCHAR_C_OBJS_6)
	$(CD) $(OBJ); $(AR) r $(LIB) $(RELATIVE_FREEBSD_MATH_TI_SUPPLEMENT_C_OBJS_7)
	$(CD) $(OBJ); $(AR) r $(LIB) $(RELATIVE_XLOCALE_C_OBJS_8)
	$(CD) $(OBJ); $(AR) r $(LIB) $(RELATIVE_OPENBSD_C99_COMPLEX_C_OBJS_9)
	$(CD) $(OBJ); $(AR) r $(LIB) $(RELATIVE_ASM_OBJS_10)
	$(CD) $(OBJ); $(AR) r $(LIB) $(RELATIVE_C_OBJS_11)

info:
	@echo FREEBSD_MATH_32_BIT_C_OBJS_1 $(FREEBSD_MATH_32_BIT_C_OBJS_1)
	@echo FREEBSD_MATH_64_BIT_C_OBJS_2 $(FREEBSD_MATH_64_BIT_C_OBJS_2)
	@echo FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_3 $(FREEBSD_C99_COMPLEX_32_BIT_C_OBJS_3)
	@echo GENERIC_C_SIZE_OPTIMIZED_C_OBJS_4 $(GENERIC_C_SIZE_OPTIMIZED_C_OBJS_4)
	@echo FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_5 $(FREEBSD_C99_COMPLEX_64_BIT_C_OBJS_5)
	@echo FULL_WCHAR_C_OBJS_6 $(FULL_WCHAR_C_OBJS_6)
	@echo FREEBSD_MATH_TI_SUPPLEMENT_C_OBJS_7 $(FREEBSD_MATH_TI_SUPPLEMENT_C_OBJS_7)
	@echo XLOCALE_C_OBJS_8 $(XLOCALE_C_OBJS_8)
	@echo OPENBSD_C99_COMPLEX_C_OBJS_9 $(OPENBSD_C99_COMPLEX_C_OBJS_9)
	@echo ASM_OBJS_10 $(ASM_OBJS_10)
	@echo C_OBJS_11 $(C_OBJS_11)
	@echo ASM_FLAGS $(ASM_FLAGS)
	@echo C_FLAGS $(C_FLAGS)
	@echo EXTRA_FLAGS $(EXTRA_FLAGS)
	@echo FREEBSD_C99_COMPLEX_32_BIT_C_FLAGS $(FREEBSD_C99_COMPLEX_32_BIT_C_FLAGS)
	@echo FREEBSD_C99_COMPLEX_32_BIT_FLAGS $(FREEBSD_C99_COMPLEX_32_BIT_FLAGS)
	@echo FREEBSD_C99_COMPLEX_64_BIT_C_FLAGS $(FREEBSD_C99_COMPLEX_64_BIT_C_FLAGS)
	@echo FREEBSD_C99_COMPLEX_64_BIT_FLAGS $(FREEBSD_C99_COMPLEX_64_BIT_FLAGS)
	@echo FREEBSD_MATH_32_BIT_C_FLAGS $(FREEBSD_MATH_32_BIT_C_FLAGS)
	@echo FREEBSD_MATH_32_BIT_FLAGS $(FREEBSD_MATH_32_BIT_FLAGS)
	@echo FREEBSD_MATH_64_BIT_C_FLAGS $(FREEBSD_MATH_64_BIT_C_FLAGS)
	@echo FREEBSD_MATH_64_BIT_FLAGS $(FREEBSD_MATH_64_BIT_FLAGS)
	@echo FREEBSD_MATH_TI_SUPPLEMENT_C_FLAGS $(FREEBSD_MATH_TI_SUPPLEMENT_C_FLAGS)
	@echo FREEBSD_MATH_TI_SUPPLEMENT_FLAGS $(FREEBSD_MATH_TI_SUPPLEMENT_FLAGS)
	@echo FULL_WCHAR_C_FLAGS $(FULL_WCHAR_C_FLAGS)
	@echo FULL_WCHAR_FLAGS $(FULL_WCHAR_FLAGS)
	@echo GENERIC_C_SIZE_OPTIMIZED_C_FLAGS $(GENERIC_C_SIZE_OPTIMIZED_C_FLAGS)
	@echo GENERIC_C_SIZE_OPTIMIZED_FLAGS $(GENERIC_C_SIZE_OPTIMIZED_FLAGS)
	@echo OPENBSD_C99_COMPLEX_C_FLAGS $(OPENBSD_C99_COMPLEX_C_FLAGS)
	@echo OPENBSD_C99_COMPLEX_FLAGS $(OPENBSD_C99_COMPLEX_FLAGS)
	@echo STANDARD_FLAGS $(STANDARD_FLAGS)
	@echo UNIVERSAL_FLAGS $(UNIVERSAL_FLAGS)
	@echo XLOCALE_C_FLAGS $(XLOCALE_C_FLAGS)
	@echo XLOCALE_FLAGS $(XLOCALE_FLAGS)
