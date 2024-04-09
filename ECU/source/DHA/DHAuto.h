#ifndef _DHAUTO_H_
#define	_DHAUTO_H_

#include "DHAutoSequence.h"
#include "DHAutoApp_lightingGrill.h"
#include "DHAutoApp.h"
#include "DHAutoRtc.h"
#include "DHAutoQueue.h"
#include "DHAutoCan.h"
#include "DHAutoIoctrl.h"
#include "DHAutoTimer.h"

#define	DEBUG_SYS		ON
#define	DEBUG_CAN		OFF
#define	DEBUG_ENET		OFF
#define	DEBUG_APP		OFF
#define	DEBUG_IOCTRL	OFF

#define	DHAUTO_SOFTTIME_10MS		10
#define	DHAUTO_SOFTTIME_50MS		50
#define	DHAUTO_SOFTTIME_100MS		100
#define	DHAUTO_SOFTTIME_1S			1000

#if ((DEBUG_DHAUTO == ON) && (DEBUG_SYS == ON))
#define	SYSINFO_PRINTF		PRINTF
#else
#define	SYSINFO_PRINTF
#endif

#if ((DEBUG_DHAUTO == ON) && (DEBUG_CAN == ON))
#define	CANINFO_PRINTF		PRINTF
#else
#define	CANINFO_PRINTF
#endif

#if ((DEBUG_DHAUTO == ON) && (DEBUG_ENET == ON))
#define	ENETINFO_PRINTF		PRINTF
#else
#define	ENETINFO_PRINTF
#endif

#if ((DEBUG_DHAUTO == ON) && (DEBUG_APP == ON))
#define	APPINFO_PRINTF		PRINTF
#else
#define	APPINFO_PRINTF
#endif

#if ((DEBUG_DHAUTO == ON) && (DEBUG_IOCTRL == ON))
#define	IOCTRLINFO_PRINTF		PRINTF
#else
#define	IOCTRLINFO_PRINTF
#endif

void Init_DHAutoFunc();
void DHAutoFunc();

#endif /* _DHAUTO_H_ */
