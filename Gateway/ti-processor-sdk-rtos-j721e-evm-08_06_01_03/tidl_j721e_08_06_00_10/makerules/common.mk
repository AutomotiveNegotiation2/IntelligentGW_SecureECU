ifeq ($(TARGET_PLATFORM) , PC)
INCLUDE_PATHS += -I $(DSP_TOOLS)/host_emulation/include/C$(SI_VER)/
else
CFLAGS += -mv$(SI_VER)
endif

ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J721E j721e))
    CFLAGS += -DSOC_J721E
else ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J721S2 j721s2))
    CFLAGS += -DSOC_J721S2
else ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), J784S4 j784s4))
    CFLAGS += -DSOC_J784S4    
else ifeq ($(TARGET_SOC),$(filter $(TARGET_SOC), AM62A am62a))
    CFLAGS += -DSOC_AM62A	
else
    #Temp change as we will be using j721e pdk
    CFLAGS += -DSOC_J721E
endif


ifeq ($(TIDL_BUILD_FOR_LOKI) ,1)
    CFLAGS+= -DLOKI_BUILD
endif

ifeq ($(TARGET_PLATFORM) , PC)
    ifeq ($(BUILD_WITH_CUDA) ,1)
        CFLAGS+= -DBUILD_WITH_CUDA
    endif    
else
    #CFLAGS+= -k
    CFLAGS+= -mw
endif

ifeq ($(TIDL_BUILD_FOR_QT), 1)
CFLAGS += -DTIDL_BUILD_FOR_QT
endif

ifeq ($(TARGET_PLATFORM) , PC)
CFLAGS += -D__C7X_HOSTEM__
CFLAGS += -DGLIBCXX_CHECK_MATH11_PROTO
CFLAGS += -D_FILE_OFFSET_BITS=64
else
CFLAGS += --cpp_default
endif
CFLAGS+= -D_TMS320C6600