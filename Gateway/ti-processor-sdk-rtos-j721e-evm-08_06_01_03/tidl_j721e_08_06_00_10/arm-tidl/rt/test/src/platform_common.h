#ifndef __PLATFORM_COMMON_H__
#define __PLATFORM_COMMON_H__

#include  "itidl_ti.h"

int32_t debug_printf(const char *format, ...);
uint64_t tidltb_virtToPhyAddrConversion(const void *virtAddr,
                                      uint32_t chNum,
                                      void *appData);

extern TIDL_CreateParams  createParams;
extern sTIDL_IOBufDesc_t  gIOParams;

#include <platform_defines.h>

#define L1_TOTAL_MEMORY_SIZE  (16 * 1024)

#define L1_MEM_SIZE  (16*1024 +  EXTRA_MEM_FOR_ALIGN)

#ifdef SOC_J721E
  #define L2_MEM_SIZE  (448*1024+  EXTRA_MEM_FOR_ALIGN)
  #define L3_MEM_SIZE  (7968 * 1024)
  #define L3_TOTAL_MEMORY_SIZE  (8 * 1024 * 1024)
  #define L2_TOTAL_MEMORY_SIZE  (512 * 1024)
#elif defined(SOC_J721S2)
  #define L2_MEM_SIZE  (448*1024+  EXTRA_MEM_FOR_ALIGN)
  #define L3_MEM_SIZE  (3768 * 1024)
  #define L3_TOTAL_MEMORY_SIZE  (4 * 1024 * 1024)
  #define L2_TOTAL_MEMORY_SIZE  (512 * 1024)
#elif defined(SOC_J784S4)
  #define L2_MEM_SIZE  (448*1024+  EXTRA_MEM_FOR_ALIGN)
  #define L3_MEM_SIZE  (2994 * 1024)
  #define L3_TOTAL_MEMORY_SIZE  (3 * 1024 * 1024)
  #define L2_TOTAL_MEMORY_SIZE  (512 * 1024)
#elif defined (SOC_AM62A)
  /* Actual L2 Aux size is 256kb  but some part of it currently used as L1D */
  #define L2_MEM_SIZE  (224*1024)
  #define L3_MEM_SIZE  (1024 * 1024)
  #define L3_TOTAL_MEMORY_SIZE  (1 * 1024 * 1024)
  #define L2_TOTAL_MEMORY_SIZE  (256 * 1024)
#else
  #define L2_MEM_SIZE  (448*1024+  EXTRA_MEM_FOR_ALIGN)
  #define L3_MEM_SIZE  (7968 * 1024)
  #define L3_TOTAL_MEMORY_SIZE  (8 * 1024 * 1024)
  #define L2_TOTAL_MEMORY_SIZE  (512 * 1024)
#endif

extern uint8_t *L1Scratch;
extern uint8_t *L2Scratch;
extern uint8_t *L3Scratch;
extern uint8_t *L4Scratch;

#endif /*__PLATFORM_COMMON_H__*/
