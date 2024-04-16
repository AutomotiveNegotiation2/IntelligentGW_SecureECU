TARGET      := tidl_onnxrt_EP
TARGETTYPE  := dsmo

CPPSOURCES    += ../onnxrt_ep.cpp
CPPSOURCES    += ../../../common/tidl_runtimes_infer_common.cpp
CPPSOURCES    += ../../../common/tidl_onnxrt_common.cpp

IDIRS += $($(_MODULE)_SDIR)/../../../rt/inc
IDIRS += $(IVISION_PATH)
IDIRS += $(TIDL_PROTOBUF_PATH)/src
IDIRS += $($(_MODULE)_SDIR)/../../../common
IDIRS += $($(_MODULE)_SDIR)/../src
IDIRS += $($(_MODULE)_SDIR)/../../onnx_proto/onnx_cc

IDIRS += $(ONNX_REPO_PATH)/onnxruntime
IDIRS += $(ONNX_REPO_PATH)/include/onnxruntime

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
