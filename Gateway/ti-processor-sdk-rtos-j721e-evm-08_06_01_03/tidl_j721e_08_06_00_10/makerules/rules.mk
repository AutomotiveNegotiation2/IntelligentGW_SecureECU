#
# Copyright (c) {2015 - 2020} Texas Instruments Incorporated
#
# All rights reserved not granted herein.
#
# Limited License.
#
# Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
# license under copyrights and patents it now or hereafter owns or controls to make,
# have made, use, import, offer to sell and sell ("Utilize") this software subject to the
# terms herein.  With respect to the foregoing patent license, such license is granted
# solely to the extent that any such patent is necessary to Utilize the software alone.
# The patent license shall not apply to any combinations which include this software,
# other than combinations with devices manufactured by or for TI ("TI Devices").
# No hardware patent is licensed hereunder.
#
# Redistributions must preserve existing copyright notices and reproduce this license
# (including the above copyright notice and the disclaimer and (if applicable) source
# code license limitations below) in the documentation and/or other materials provided
# with the distribution
#
# Redistribution and use in binary form, without modification, are permitted provided
# that the following conditions are met:
#
# *       No reverse engineering, decompilation, or disassembly of this software is
# permitted with respect to any software provided in binary form.
#
# *       any redistribution and use are licensed by TI for use only with TI Devices.
#
# *       Nothing shall obligate TI to provide you with source code for the software
# licensed and provided to you in object code.
#
# If software source code is provided to you, modification and redistribution of the
# source code are permitted provided that the following conditions are met:
#
# *       any redistribution and use of the source code, including any resulting derivative
# works, are licensed by TI for use only with TI Devices.
#
# *       any redistribution and use of any object code compiled from the source code
# and any resulting derivative works, are licensed by TI for use only with TI Devices.
#
# Neither the name of Texas Instruments Incorporated nor the names of its suppliers
#
# may be used to endorse or promote products derived from this software without
# specific prior written permission.
#
# DISCLAIMER.
#
# THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.
#
#


##############################################################

include $(ALGBASE_PATH)/makerules/config.mk

BUILD_FOLDER      := $(ALGBASE_PATH)\out

ifdef SystemRoot
#Windows OS
    ifndef UTILS_PATH
      $(error You must define UTILS_PATH!)
    endif
    RM_CMD = $(UTILS_PATH)\rm -rf
    MKDIR_CMD = $(UTILS_PATH)\mkdir -p $(1)
    CHANGE_PATHSEP=$(subst /,\,$(1))
    CAT_CMD = $(UTILS_PATH)\cat
    MAKE = gmake
else
    ifeq ($(shell uname), Linux)
#Linux
      RM_CMD = rm -rf
      MKDIR_CMD = mkdir -p $(1)
      CHANGE_PATHSEP=$(subst \,/,$(1))
      CAT_CMD = cat
      MAKE = make
    endif
endif

ifeq ($(SHOW_COMMANDS),1)
Q:=
else
Q:=@
endif

ALGBASE_PATH:= $(call  CHANGE_PATHSEP,$(ALGBASE_PATH))
EMPTY:=
SPACE:=$(EMPTY) $(EMPTY)
COMMA:=$(EMPTY),$(EMPTY)

_MAKEPATH := $(abspath .)
_MAKEPATH:= $(call  CHANGE_PATHSEP,$(_MAKEPATH))


ifdef SystemRoot
_MODPATH  := $(subst $(ALGBASE_PATH)\,,$(_MAKEPATH))
else
_MODPATH  := $(subst $(ALGBASE_PATH)/,,$(_MAKEPATH))
endif
_MODPATH:= $(call CHANGE_PATHSEP,$(_MODPATH))



BUILD_MODE ?=OBJ

#if platform is J721E
ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J721E j721e))
    DEFINE_FLAGS := J721E_PLATFORM
endif

ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J721S2 j721s2))
    DEFINE_FLAGS := J721S2_PLATFORM
endif

ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J784S4 j784s4))
    DEFINE_FLAGS := J784S4_PLATFORM
endif

ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), AM62A am62a))
    DEFINE_FLAGS := AM62A_PLATFORM
endif

#if platform is vme
ifeq ($(TARGET_SOC),vme)
    DEFINE_FLAGS := VME_PLATFORM
endif

ifeq ($(TARGET_BUILD), )
ifeq ($(TARGET_PLATFORM) , PC)
	TARGET_BUILD := debug
else
	TARGET_BUILD := release
endif
endif

LIB_DIR=algo

ifeq ($(TARGET_PLATFORM) , PC)
CURR_BUILD_FOLDER:= $(BUILD_FOLDER)/$(TARGET_PLATFORM)/$(CORE)/$(LIB_DIR)/$(TARGET_BUILD)
else
CURR_BUILD_FOLDER:= $(BUILD_FOLDER)/$(TARGET_SOC)/$(CORE)/$(LIB_DIR)/$(TARGET_BUILD)
endif

CURR_BUILD_FOLDER:= $(call  CHANGE_PATHSEP,$(CURR_BUILD_FOLDER))

##############################################################

##############################################################
ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
  #Window Host Emulation
  CC = CL
  CP = CL
  AS = $(TARGET_CPU)ASM
  AR = LIB
  LD = LINK


  #Scalable API Support for PC-Windows
  COMPILER_FLAGS += /D__C7X_UNSTABLE_API

  #Top Level C7100/C7120 Define:
  ifeq ($(TARGET_C7X_VERSION), C7100)
  COMPILER_FLAGS += /D__C7100__
  endif
  
  ifeq ($(TARGET_C7X_VERSION), C7120)
  COMPILER_FLAGS += /D__C7120__
  endif
  
  ifeq ($(TARGET_C7X_VERSION), C7504)
  COMPILER_FLAGS += /D__C7504__ 
    endif

  ifeq ($(TARGET_BUILD), release)
    COMPILER_FLAGS += /EHsc /TP /W0 /FS /wd4505 /D_CRT_SECURE_NO_WARNINGS /DHOST_EMULATION /D_HOST_BUILD /c /nologo /Ox /D_NDEBUG /MT /Zi /D_HOST_BUILD  /D_HAS_ITERATOR_DEBUGGING=0 /D_ITERATOR_DEBUG_LEVEL=0 /DMSVC_BUILD /std:c++14
    LDDEBUG := /DEBUG 

  else
    COMPILER_FLAGS += /EHsc /TP /W0 /FS /wd4505 /D_CRT_SECURE_NO_WARNINGS /DHOST_EMULATION /D_HOST_BUILD /c /nologo /Od /MT /Zi /D_HAS_ITERATOR_DEBUGGING=0 /D_ITERATOR_DEBUG_LEVEL=0 /D_HOST_BUILD /DMSVC_BUILD /std:c++14
    LDDEBUG := /DEBUG 
  endif
  
  ifeq ($(BUILD_WITH_CUDA) ,1)
  ARFLAGS := /nologo /MACHINE:x64 /ignore:4099
  else
  ARFLAGS := /nologo /MACHINE:x64 /ignore:4099
  endif
  
  ifeq ($(TARGET_CPU),C64T)
  #COMPILER_FLAGS += /D__C7100__
  endif
else 
  #Linux Host Emulation
  CC=g++-5 -c
  AR=gcc-ar-5
  ARFLAGS := rvs

  #Scalable API Support for PC-Linux
  COMPILER_FLAGS += -D__C7X_UNSTABLE_API
  
  #Top Level C7100/C7120/C7504 Define:
  ifeq ($(TARGET_C7X_VERSION), C7100)
  COMPILER_FLAGS += -D__C7100__
  endif
  
  ifeq ($(TARGET_C7X_VERSION), C7120) 
  COMPILER_FLAGS += -D__C7120__
  endif
  
  ifeq ($(TARGET_C7X_VERSION), C7504)
  COMPILER_FLAGS += -D__C7504__
  endif

  ifeq ($(TARGET_BUILD), debug)
    COMPILER_FLAGS += -std=c++14  -DHOST_EMULATION -w -D_HOST_BUILD -DGCC_BUILD  
    GCC_DEBUG_CFLAGS :=-ggdb -ggdb3 -gdwarf-2
  else
    ifeq ($(DEVELOPER_BUILD), 0)
      COMPILER_FLAGS += -std=c++14 -O3 -DHOST_EMULATION -D_HOST_BUILD -DGCC_BUILD 
    else
      COMPILER_FLAGS += -std=c++14 -O3 -DHOST_EMULATION -D_HOST_BUILD -DGCC_BUILD -g
    endif
  endif
  LD=g++-5
  LDFLAGS +=
endif
  ifeq ($(CORE),eve)
  COMPILER_FLAGS += -DCORE_EVE -DVCOP_HOST_EMULATION
  endif
  ifeq ($(CORE),dsp)
  COMPILER_FLAGS += -DCORE_DSP -D_TMS320C6600

   ifeq ($(TARGET_CPU),C64T)
     COMPILER_FLAGS += -DTMS320C64X
     else ifeq ($(TARGET_CPU),C64P)
     COMPILER_FLAGS += -DTMS320C64PX
     else ifeq ($(TARGET_CPU),C64)
     COMPILER_FLAGS += -DTMS320C64X
     else ifeq ($(TARGET_CPU),C66)
     COMPILER_FLAGS += -DTMS320C66X
     else ifeq ($(TARGET_CPU),C674)
     COMPILER_FLAGS += -DTMS320C67X
     else ifeq ($(TARGET_CPU),C67)
     COMPILER_FLAGS += -DTMS320C67X
     else ifeq ($(TARGET_CPU),C67P)
     COMPILER_FLAGS += -DTMS320C67X
   endif
   COMPILER_FLAGS += -DLITTLE_ENDIAN_HOST
  endif 

else
#TI_DEVICE
  ifeq ($(CORE),eve)
    CC = $(ARP32_TOOLS)\bin\cl-arp32
    LD = $(ARP32_TOOLS)\bin\lnk-arp32
    AR = $(ARP32_TOOLS)\bin\ar-arp32
    ifeq ($(TARGET_BUILD), release)
      COMPILER_FLAGS += -kh -kv -lu -o3 --silicon_version=v210 -D$(DEFINE_FLAGS) --gen_func_subsections --display_error_number --diag_suppress=496 --diag_suppress=1311 --no_warnings
    else
      COMPILER_FLAGS += -kh -kv -lu -g --silicon_version=v210  -D$(DEFINE_FLAGS) --gen_func_subsections --display_error_number --diag_suppress=496 --diag_suppress=1311 --no_warnings
    endif
    ARFLAGS = r
    LDFLAGS += -cr -x --display_error_number --diag_suppress=num=10063  --diag_suppress=num=10068
    CFLAGS += -I $(ARP32_TOOLS)/include
    CFLAGS += -DCORE_EVE
    ifneq ($(VCOP_H_DIR),)
      CFLAGS += --temp_directory=$(VCOP_H_DIR)
    endif
  endif
  ifeq ($(CORE),dsp)
    CC = $(DSP_TOOLS)\bin\cl7x
    LD = $(DSP_TOOLS)\bin\lnk7x
    AR = $(DSP_TOOLS)\bin\ar7x
    ifeq ($(TARGET_BUILD), release)
      CFLAGS = -O3  -DUSE_LEVEL_1_MACROS -D$(DEFINE_FLAGS)
    else
      CFLAGS = -g -DUSE_LEVEL_1_MACROS -D$(DEFINE_FLAGS)
    endif

    CFLAGS += -DCORE_DSP
    
    #Scalable API:
    CFLAGS += -D__C7X_UNSTABLE_API
    
    ifeq ($(TARGET_CPU),C64T)
      CFLAGS += --silicon_version=tesla -D=xdc_target_name=C64T
      else ifeq ($(TARGET_CPU),C64P)
      CFLAGS += --silicon_version=6400+ -D=xdc_target_name=C64P
      else ifeq ($(TARGET_CPU),C64)
      CFLAGS += --silicon_version=6400 -D=xdc_target_name=C64
      else ifeq ($(TARGET_CPU),C66)
      CFLAGS += --silicon_version=6600 -D=xdc_target_name=C66
      else ifeq ($(TARGET_CPU),C674)
      CFLAGS += --silicon_version=6740 -D=xdc_target_name=C674
      else ifeq ($(TARGET_CPU),C67)
      CFLAGS += --silicon_version=6700 -D=xdc_target_name=C67
      else ifeq ($(TARGET_CPU),C67P)
      CFLAGS += --silicon_version=6700+ -D=xdc_target_name=C67P
      else ifeq ($(TARGET_CPU),C71)
        ifeq ($(TARGET_C7X_VERSION),C7100)
        CFLAGS += --silicon_version=7100 --silicon_errata_i2117 -D=xdc_target_name=C71 --emit_warnings_as_errors  --abi=eabi --rtti -mo
        else ifeq ($(TARGET_C7X_VERSION),C7120)
        CFLAGS += --silicon_version=7120 -D=xdc_target_name=C71 --emit_warnings_as_errors  --abi=eabi --rtti -mo
        else
        CFLAGS += --silicon_version=7504 -D=xdc_target_name=C71  --emit_warnings_as_errors --abi=eabi --rtti -mo
        endif
   endif
    ARFLAGS = r
    LDFLAGS += --cinit_compression=off
    CFLAGS += -I $(DSP_TOOLS)/include/libcxx -I $(DSP_TOOLS)/include
  endif
  ifeq ($(CORE),arm)
	CFLAGS_GLOBAL_m4vpss = -g -ms -D___DSPBIOS___ -D___DUCATI_FW___ --obj_extension=obj
	ENDIAN = little
	FORMAT = ELF
    
	CC = $(TIARM_TOOLS)\bin\armcl
	LD = $(TIARM_TOOLS)\bin\armlnk
	AR = $(TIARM_TOOLS)\bin\armar
	CFLAGS_INTERNAL = -c -qq -pdsw225 --endian=$(ENDIAN) -mv7M4 --float_support=vfplib --abi=$(CSWITCH_FORMAT) -eo.$(OBJEXT) -ea.$(ASMEXT) --symdebug:dwarf --embed_inline_assembly
    
    ifeq ($(FORMAT),COFF)
		CSWITCH_FORMAT = ti_arm9_abi
		RTSLIB_FORMAT = tiarm9
    endif
    ifeq ($(FORMAT),ELF)
		CSWITCH_FORMAT = eabi
		RTSLIB_FORMAT = eabi
    endif

    ifeq ($(TARGET_BUILD), release)
		LNKFLAGS_INTERNAL_PROFILE = --opt='--endian=$(ENDIAN) -mv7M4 --float_support=vfplib --abi=$(CSWITCH_FORMAT) -qq -pdsw225 $(CFLAGS_GLOBAL_m4vpss) -oe --symdebug:dwarf -ms -op2 -O3 -os --optimize_with_debug --inline_recursion_limit=20 --diag_suppress=23000' --strict_compatibility=on
		CFLAGS_XDCINTERNAL = -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_release -Dxdc_bld__vers_1_0_4_6_1 -ms -oe -O3 -op0 -os --optimize_with_debug --inline_recursion_limit=20
    else
		LNKFLAGS_INTERNAL_PROFILE =
		CFLAGS_XDCINTERNAL = -Dxdc_target_name__=M4 -Dxdc_target_types__=ti/targets/arm/elf/std.h -Dxdc_bld__profile_debug -Dxdc_bld__vers_1_0_4_6_1 -D_DEBUG_=1
 
    endif
	
	ARFLAGS = rq
	CFLAGS = $(CFLAGS_INTERNAL) $(CFLAGS_GLOBAL_m4vpss) $(CFLAGS_XDCINTERNAL)
	CFLAGS += -I $(TIARM_TOOLS)\include
  endif

  
  CFLAGS += --diag_suppress=496 --diag_suppress=1311 --diag_suppress=1111
endif

ifeq ($(CORE),eve)
CFLAGS += -I $(ARP32_TOOLS)/include/vcop
endif
##############################################################


##############################################################
ifeq ($(LIBDIR),)
LIBDIR =  .\lib\$(TARGET_BUILD)
endif
ifeq ($(OUTDIR),)
OUTDIR =  .\elf_out
endif



ifeq ($(ENABLE_FASTFILEIO),1)
CFLAGS += -DUSE_HOST_FILE_IO
endif

##############################################################

# In case there are no sources, it is better to not generate any lib
ifeq (,$(wildcard $(CFILES)))
OUTFILE=
endif
##############################################################
CFILES := $(call  CHANGE_PATHSEP,$(CFILES))
HFILES := $(call  CHANGE_PATHSEP,$(HFILES))
CFILESCU:= $(filter %.cu,$(CFILES))

CFILESK:= $(filter %.k,$(CFILES))
CFILESC:= $(filter %.c,$(CFILES))
CFILESCPP:= $(filter %.cpp,$(CFILES))
CFILESCC:= $(filter %.cc,$(CFILES))
CFILESASM:= $(filter %.asm,$(CFILES))
CFILES:= $(CFILESK) $(CFILESC) $(CFILESASM) $(CFILESCPP) $(CFILESCC) $(CFILESCU)
#OFILES:= $(addsuffix .obj, $(basename $(notdir $(CFILES))))

OFILES:= $(CFILESC:%.c=%.obj)
OFILES+= $(CFILESCPP:%.cpp=%.obj)
OFILES+= $(CFILESCC:%.cc=%.obj)
OFILES+= $(CFILESCU:%.cu=%.obj) #
ifneq ($(TARGET_PLATFORM) , PC)
OFILES+= $(CFILESASM:%.asm=%.obj)
endif
DEPILES:= $(CFILESC:%.c=%.dep)
DEPILES+= $(CFILESCPP:%.cpp=%.dep)
DEPILES+= $(CFILESCC:%.cc=%.dep)
DEPILES+= $(CFILESCC:%.cu=%.dep)
KOFILES:= $(CFILESK:%.k=%.obj)

BUILDDIR := $(CURR_BUILD_FOLDER)/$(_MODPATH)/
BUILDDIR := $(call  CHANGE_PATHSEP,$(BUILDDIR))

OFILES:= $(addprefix  $(BUILDDIR), $(OFILES))
KOFILES:= $(addprefix $(BUILDDIR), $(KOFILES))
DEPILES:= $(addprefix $(BUILDDIR), $(DEPILES))

OFILES := $(call  CHANGE_PATHSEP,$(OFILES))
FIRST_OFILES := $(word 1,$(OFILES))
RESTOF_OFILES := $(filter-out $(FIRST_OFILES), $(OFILES))

BUILDDIR := $(call  CHANGE_PATHSEP,$(BUILDDIR))
OUTFILE := $(call  CHANGE_PATHSEP,$(OUTFILE))
OBJDIRS := $(foreach file, $(OFILES), $(dir $(file)))
OBJDIRS += $(foreach file, $(KOFILES), $(dir $(file)))
OBJDIRS += $(foreach file, $(OUTFILE), $(dir $(file)))
OBJDIRS += $(BUILDDIR)
OBJDIRS := $(sort $(OBJDIRS))
OBJDIRS := $(addsuffix .gitignore, $(OBJDIRS))

##############################################################
CC := $(call  CHANGE_PATHSEP,$(CC))
LD := $(call  CHANGE_PATHSEP,$(LD))
AR := $(call  CHANGE_PATHSEP,$(AR))

CFLAGS := $(call  CHANGE_PATHSEP,$(CFLAGS))
OUTFILE := $(call  CHANGE_PATHSEP,$(OUTFILE))
LIBDIR := $(call  CHANGE_PATHSEP,$(LIBDIR))
OUTDIR := $(call  CHANGE_PATHSEP,$(OUTDIR))

OBJDIRS := $(call  CHANGE_PATHSEP,$(OBJDIRS))

CFLAGS := $(COMPILER_FLAGS) $(CFLAGS)

#$(info OBJDIRS $(OBJDIRS))
SMS ?= 50 52 60 70 # CUDA 9.0 version onward, sm_30 sm_35 sm_37 are not supported or not needed, hence removed
ifeq ($(GENCODE_FLAGS),)
# Generate SASS code for each SM architecture listed in $(SMS)
$(foreach sm,$(SMS),$(eval GENCODE_FLAGS += -gencode arch=compute_$(sm),code=sm_$(sm)))

# Generate PTX code from the highest SM architecture in $(SMS) to guarantee forward-compatibility
HIGHEST_SM := $(lastword $(sort $(SMS)))
ifneq ($(HIGHEST_SM),)
GENCODE_FLAGS += -gencode arch=compute_$(HIGHEST_SM),code=compute_$(HIGHEST_SM)
endif
endif
##############################################################
# 'all' rules
ifdef SystemRoot
all :  dir $(OUTFILE)
else
all :  | dir $(OUTFILE)
endif

# Define a ".gitignore" file which will help in making sure the module's output
# folder always exists.
%gitignore:
#	@echo creating $@
	$(Q) $(MKDIR_CMD) $(dir $@)
	$(Q)echo .> $@
dir: $(OBJDIRS)

$(OUTFILE): $(KOFILES) $(OFILES)

ifdef SystemRoot
$(BUILDDIR)\%.obj: .\%.k
else
$(BUILDDIR)%.obj: %.k
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
  #Window Host Emulation
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)$(CC) $(CFLAGS) $(GCC_DEBUG_CFLAGS)  -fPIC $< -o $@
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --compile_only -fr=$(dir $@) -fs=$(dir $@) "$<"
endif

ifdef SystemRoot
$(BUILDDIR)\%.obj: .\%.c
else
$(BUILDDIR)%.obj: %.c
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
  #Window Host Emulation
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)$(CC) $(CFLAGS) $(GCC_DEBUG_CFLAGS) -fPIC  $< -o $@
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -fs=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif
ifdef SystemRoot
$(BUILDDIR)\%.obj: ./%.cu
else
$(BUILDDIR)%.obj: %.cu
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
ifeq ($(BUILD_WITH_CUDA), 1)
	$(Q)$(CUDA_PATH)/bin/nvcc -I $(CUDNN_PATH)/include $(INCLUDE_PATHS) -D BUILD_WITH_CUDA -o $@ -c $<
else
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
endif
else
ifeq ($(BUILD_WITH_CUDA), 1)
	$(Q)$(CUDA_PATH)/bin/nvcc -ccbin  $(CC) $(CFLAGS) $(GENCODE_FLAGS) -Xcompiler -fPIC -o $@ -c $<
else
	$(Q)$(CC) $(CFLAGS) $(GCC_DEBUG_CFLAGS) -fPIC  $< -o $@
endif
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -fs=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif


ifdef SystemRoot
$(BUILDDIR)\%.obj: ./%.cpp
else
$(BUILDDIR)%.obj: %.cpp
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
  #Window Host Emulation
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)$(CC) $(CFLAGS)  $(GCC_DEBUG_CFLAGS) -fPIC  $< -o $@
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -fs=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif

ifdef SystemRoot
$(BUILDDIR)\%.obj: ./%.cc
else
$(BUILDDIR)%.obj: %.cc
endif
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo compiling $<
ifdef SystemRoot
  #Window Host Emulation
	$(Q)$(CC) $(CFLAGS) $< /Fo$@ /Fd$(BUILDDIR)$*.pdb
else
	$(Q)$(CC) $(CFLAGS)  $(GCC_DEBUG_CFLAGS) -fPIC  $< -o $@
endif
else
	$(Q)echo compiling $<
	$(Q)$(CC) $(CFLAGS) --preproc_with_compile -fr=$(dir $@) -fs=$(dir $@) -ppd="$(BUILDDIR)$*.dep" $<
endif


ifneq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
$(BUILDDIR)\%.obj : ./%.asm
else
$(BUILDDIR)%.obj : %.asm
endif
	$(Q)$(CC) $(CFLAGS) -c $^ --output_file=$@
endif
##############################################################

print :
	echo $(LDFLAGS)
	echo $(OFILES)
	echo $(OUTFILE)
	echo $(CFILES)
	echo $(HFILES)
	echo @$(AR) $(ARFLAGS) $(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
##############################################################
# clean rules
.IGNORE: clean
clean:
ifdef SystemRoot
	@echo echo OFF > temp_pps.bat
	@FOR %%i IN ($(OFILES) $(KOFILES)) DO echo del %%i >> temp_pps.bat
ifneq ($(TARGET_PLATFORM) , PC)
	@FOR %%i IN ( $(DEPILES)) DO echo del %%i >> temp_pps.bat
endif
	@echo echo ON >> temp_pps.bat
	@temp_pps.bat
	@-del temp_pps.bat
else
	$(Q)$(RM_CMD) $(OFILES) $(KOFILES)
endif	
ifneq ($(BUILD_MODE),OBJ)
	$(Q)$(RM_CMD) $(LIBDIR)
endif
	$(Q)$(RM_CMD) $(OUTFILE)*
	$(Q)$(RM_CMD) $(OUTDIR)
##############################################################


##############################################################
.PHONY: libfile
libfile: $(LIBDIR) $(KOFILES) $(OFILES) $(ARFILES)
ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
  #Window Host Emulation
	$(Q)echo Linking $(OUTFILE)
	$(Q)echo $(ARFLAGS) /OUT:$(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(KOFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
else
	$(Q)$(AR) $(ARFLAGS) $(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
endif
else
	$(Q)$(RM_CMD) $(OUTFILE)
ifdef SystemRoot
	$(Q)echo $(ARFLAGS) $(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(KOFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)$(RM_CMD) ar_cmd.txt
else	
	@$(AR) $(ARFLAGS) $(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
endif	
endif 
$(LIBDIR):
	$(Q) $(MKDIR_CMD) $(LIBDIR) || cd $(LIBDIR)

##############################################################
.PHONY: pllibfile
pllibfile: $(LIBDIR) $(OFILES) $(LDFILES)
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)echo Linking $(OUTFILE)
ifdef SystemRoot
  #Window Host Emulation
	$(Q)echo $(ARFLAGS) /OUT:$(OUTFILE) > ar_cmd.txt
	$(Q)FOR %%i IN ($(OFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
else
	$(Q)$(AR) $(ARFLAGS) $(OUTFILE) $(KOFILES) $(OFILES) $(ARFILES)
endif
else
ifdef SystemRoot
	$(Q)echo $(ARFLAGS) temp_pl.lib > ar_cmd.txt
	$(Q)FOR %%i IN ($(RESTOF_OFILES) $(KOFILES) $(ARFILES)) DO echo %%i >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del ar_cmd.txt
	$(Q)if exist $(OUTFILE) del $(OUTFILE)
	$(Q)$(LD) -r $(LDFLAGS) --output_file="plink.out"  $(FIRST_OFILES) $(LDFILES) -m "plink.map" -l temp_pl.lib
	$(Q)echo $(ARFLAGS) $(OUTFILE) > ar_cmd.txt
	$(Q)echo plink.out >> ar_cmd.txt
	$(Q)$(AR) @ar_cmd.txt
	$(Q)-del temp_pl.lib
	$(Q)-del ar_cmd.txt
	$(Q)-del plink.map
	$(Q)-del plink.out
else	
	$(Q)$(LD) -r --output_file="plink.out"  $(FIRST_OFILES) $(RESTOF_OFILES) $(KOFILES) -m "plink.map"
	$(Q)$(AR) $(ARFLAGS) $(OUTFILE) plink.out
endif	
endif

##############################################################
PC_LDFLAGS1 = $(filter-out %rtsarp32_v200.lib,$(LDFLAGS))
PC_LDFLAGS = $(filter-out %rtsarp32_v200.lib",$(PC_LDFLAGS1))
ALL_LIBS1 = $(filter %.lib,$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.lib",$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.lib"",$(PC_LDFLAGS))
ALL_LIBS1 += $(filter %.a86",$(PC_LDFLAGS))

ALL_LIBS  = $(subst .lib,.lib,$(ALL_LIBS1))
ifeq ($(BUILD_WITH_CUDA), 1)
ALL_LIBS+= "$(CUDA_PATH)\lib\x64\cudart.lib"
ALL_LIBS+= "$(CUDA_PATH)\lib\x64\cublas.lib"
ALL_LIBS+= "$(CUDNN_PATH)\lib\x64\cudnn.lib"
endif
##############################################################
.PHONY: outfile
outfile: $(OUTDIR) $(KOFILES) $(OFILES) $(LDFILES)
ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
	$(Q)if exist $(OUTFILE).exe del $(OUTFILE).exe
ifeq ($(BUILD_WITH_CUDA), 1)
	$(Q)$(CUDA_PATH)/bin/nvcc  -o $(OUTFILE) $(KOFILES) $(OFILES) $(LDFILES) $(ALL_LIBS) "User32.lib" 
else
	$(Q)$(LD) /stack:16000000 $(ALL_LIBS) $(LDDEBUG) $(ARFLAGS) /OUT:$(OUTFILE).exe $(KOFILES) $(OFILES) $(LDFILES)
endif
else
	$(Q)$(RM_CMD) $(OUTFILE)
ifeq ($(BUILD_WITH_CUDA), 1)
	$(Q)$(CUDA_PATH)/bin/nvcc -ccbin $(LD) -o $(OUTFILE) $(KOFILES) $(OFILES) $(LDFILES) $(LDFLAGS)  -m64
else
	$(Q)$(LD) -o $(OUTFILE) $(KOFILES) $(OFILES) $(LDFILES) $(LDFLAGS) 
endif
endif
else
	$(Q)$(RM_CMD) $(OUTFILE)
	$(Q)$(LD) $(LDFLAGS) --output_file=$(OUTFILE) $(KOFILES) $(OFILES) $(LDFILES) -m "$(OUTFILE)".map
endif
$(OUTDIR):
	$(Q)$(MKDIR_CMD) $(OUTDIR) || cd $(OUTDIR)

##############################################################
.PHONY: sharedlibfile
ifdef SystemRoot
DLLLIB=$(basename $(OUTFILE)).lib
endif
sharedlibfile: $(OUTDIR) $(KOFILES) $(OFILES) $(LDFILES)
ifeq ($(TARGET_PLATFORM) , PC)
ifdef SystemRoot
	$(Q)if exist $(OUTFILE) del $(OUTFILE)
	$(Q)if exist $(DLLLIB) del $(DLLLIB)
	$(Q)$(LD) /DLL $(ALL_LIBS) $(LDDEBUG) /OUT:$(OUTFILE) $(KOFILES) $(OFILES) $(LDFILES)
else
	$(Q)$(RM_CMD) $(OUTFILE)
	$(Q)$(LD) -shared -o $(OUTFILE) $(KOFILES) $(OFILES) $(LDFILES) $(LDFLAGS) 
endif
else
	$(Q)$(RM_CMD) $(OUTFILE)
	$(Q)$(LD) --dynamic=lib $(LDFLAGS) --output_file=$(OUTFILE) $(KOFILES) $(OFILES) $(LDFILES) -m "$(OUTFILE)".map
endif

##############################################################
.PHONY: mergefile
mergefile: 
ifeq ($(TARGET_PLATFORM) , PC)
	$(Q)$(AR) $(ARFLAGS) /OUT:lib\$(TARGET_BUILD)\libevekernels.eve.lib lib\$(TARGET_BUILD)\libevekernels.eve.lib lib\$(TARGET_BUILD)\libeveprivkernels.eve.lib
	$(Q)$(AR) $(ARFLAGS) /OUT:lib\$(TARGET_BUILD)\libevenatckernels.eve.lib lib\$(TARGET_BUILD)\libevenatckernels.eve.lib lib\$(TARGET_BUILD)\libeveprivnatckernels.eve.lib
else
	$(Q)$(AR) x lib/$(TARGET_BUILD)/libevekernels.eve.lib
	$(Q)$(AR) x lib/$(TARGET_BUILD)/libeveprivkernels.eve.lib
	$(Q)$(AR) a lib/$(TARGET_BUILD)/libevekernels.eve.lib *.obj
	$(Q)$(RM_CMD) *.obj
	$(Q)$(AR) x lib/$(TARGET_BUILD)/libevenatckernels.eve.lib
	$(Q)$(AR) x lib/$(TARGET_BUILD)/libeveprivnatckernels.eve.lib
	$(Q)$(AR) a lib/$(TARGET_BUILD)/libevenatckernels.eve.lib *.obj
	$(Q)$(RM_CMD) *.obj
endif
##############################################################


define INCLUDE_DEPEND
-include $(1).dep
endef

$(foreach obj,$(OFILES),$(eval $(call INCLUDE_DEPEND,$(basename $(obj)))))




