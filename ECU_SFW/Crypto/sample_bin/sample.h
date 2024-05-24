#ifndef SAMPLE_BIN_SAMPLE_H_
#define SAMPLE_BIN_SAMPLE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#define SRAM_OC2				(char*)0x202c0000
#define SAMPLE_MEMORY_ADDRESS	SRAM_OC2



void Sample_Cpy(char* sample, unsigned int length);

#ifdef __cplusplus
}
#endif

#endif /* SAMPLE_BIN_SAMPLE_H_ */
