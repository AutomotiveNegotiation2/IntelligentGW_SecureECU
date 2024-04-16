TARGET      := tidl_tfl_delegate
TARGETTYPE  := dsmo

CPPSOURCES    += ../tfl_delegate.cpp
CPPSOURCES    += ../../../common/tidl_runtimes_infer_common.cpp
CPPSOURCES    += ../../../common/tidl_tflrt_common.cpp

IDIRS += $($(_MODULE)_SDIR)/../../../rt/inc
IDIRS += $($(_MODULE)_SDIR)/../../../common

IDIRS += $(TF_REPO_PATH)  
IDIRS += $(IVISION_PATH)

LDIRS += $($(_MODULE)_SDIR)/../../../rt/out/$(TARGET_PLATFORM)/$(TARGET_CPU)/LINUX/$(TARGET_BUILD)

SHARED_LIBS += dl

CPPFLAGS  += --std=c++11 \
             -Wno-maybe-uninitialized \
             -Wno-unused-variable \
             -Wno-sign-compare \
             -Wno-unused-but-set-variable \
             -Wno-unused-result \
             -Wno-format-overflow \
             -Wno-format-truncation
