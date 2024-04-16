STATIC_LIBS += fft_c7xmma/FFTLIB_FFT_dftSmall_ixX_cxX_oxX_lib_$(TARGET_CPU) \
fft_c7xmma/FFTLIB_FFT_dftLarge_ixX_cxX_oxX_lib_$(TARGET_CPU) \
linalg_c7xmma/FFTLIB_LINALG_matrixMatrixMultiply_ixX_ixX_oxX_lib_$(TARGET_CPU) \
fft_c7xmma/FFTLIB_FFT_highRadixDecompositions_ixX_cxX_oxX_lib_$(TARGET_CPU)
LDIRS += $(TARGET_OUT)/linalg_c7xmma \
$(TARGET_OUT)/fft_c7xmma
