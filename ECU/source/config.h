#ifndef _CONFIG_H_
#define	_CONFIG_H_

#include <stdint.h>
#include "fsl_debug_console.h"

#define	DEBUG_SYS		ON
#define	DEBUG_CAN		OFF
#define	DEBUG_ENET		OFF
#define	DEBUG_APP		ON
#define	DEBUG_IOCTRL	OFF

typedef enum {
	DEBUG_LEVEL0=0,
	DEBUG_LEVEL1,
	DEBUG_LEVEL2,
	DEBUG_LEVEL3,
} DEBUG_LEVEL_t;

#define	CAN3toCAN_EN	ON
#define	CAN1toCANFD_EN	OFF
#define	LIGHTING_GRILL_INSTALLED	ON

#if ((CAN3toCAN_EN == OFF) && (CAN1toCANFD_EN == OFF))
#error CAN function more than one channel must be activated
#endif

#if (DEBUG_SYS == ON)
#define	SYSINFO_PRINTF		PRINTF
#else
#define	SYSINFO_PRINTF
#endif

#if (DEBUG_CAN == ON)
#define	CANINFO_PRINTF		PRINTF
#else
#define	CANINFO_PRINTF
#endif

#if (DEBUG_ENET == ON)
#define	ENETINFO_PRINTF		PRINTF
#else
#define	ENETINFO_PRINTF
#endif

#if (DEBUG_APP == ON)
#define	APPINFO_PRINTF		PRINTF
#else
#define	APPINFO_PRINTF
#endif

#if (DEBUG_IOCTRL == ON)
#define	IOCTRLINFO_PRINTF		PRINTF
#else
#define	IOCTRLINFO_PRINTF
#endif

#endif /* _CONFIG_H_ */
