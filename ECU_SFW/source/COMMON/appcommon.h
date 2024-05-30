#ifndef _COMMON_H_
#define	_COMMON_H_

#include "can.h"
#include "enet.h"

#include "ethernetif.h"
#include "udpClientRAW.h"

#include "EnetApp.h"

#if (DEBUG_COMMON == ON)
#define	COMMON_PRINTF		PRINTF
#else
#define	COMMON_PRINTF
#endif

#define	MEASURED_10MS_DELAY			SDK_DelayAtLeastUs(7000U, 996000000U)
#define	MEASURED_20MS_DELAY			SDK_DelayAtLeastUs(13000U, 996000000U)
#define	MEASURED_OVER_10MS_DELAY	SDK_DelayAtLeastUs(10000U, 996000000U)
#define	MEASURED_OVER_20MS_DELAY	SDK_DelayAtLeastUs(20000U, 996000000U)

void Init_CommonFunc(void);
void CommonFunc(void);

#endif /* _COMMON_H_ */