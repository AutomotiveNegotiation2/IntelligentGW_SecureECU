#ifndef _CONFIG_H_
#define	_CONFIG_H_

#include <stdint.h>
#include "fsl_debug_console.h"

#define	DEBUG_COMMON	ON
#define	DEBUG_AUTOCRYPT	OFF
#define	DEBUG_KORUNIV	OFF
#define	DEBUG_KETI		OFF
#define	DEBUG_DHAUTO	ON

typedef enum {
	DEBUG_LEVEL0=0,
	DEBUG_LEVEL1,
	DEBUG_LEVEL2,
	DEBUG_LEVEL3,
} DEBUG_LEVEL_t;

#define	CAN3toCAN_EN	ON
#define	CAN1toCANFD_EN	OFF

#define	DHAUTO_FUNC_EN				ON
#define	LIGHTING_GRILL_INSTALLED	OFF

#define	EXECUTION_TIME_LOG				ON
#if (EXECUTION_TIME_LOG == ON)
#define	EXECUTION_TIME_LOG_COMMON		ON
#define	EXECUTION_TIME_LOG_AUTOCRYPT	OFF
#define	EXECUTION_TIME_LOG_KORUNIV		OFF
#define	EXECUTION_TIME_LOG_KETI			OFF
#define	EXECUTION_TIME_LOG_DHAUTO		ON
#endif

#define configMAC_ADDR {0x02, 0x12, 0x13, 0x10, 0x15, 0x11}

#if ((CAN3toCAN_EN == OFF) && (CAN1toCANFD_EN == OFF))
#error CAN function more than one channel must be activated
#endif

#if (DEBUG_COMMON == ON)
#define	COMMON_PRINTF		PRINTF
#else
#define	COMMON_PRINTF
#endif

#if (DEBUG_AUTOCRYPT == ON)
#define	AUTOCRYPT_PRINTF	PRINTF
#else
#define	AUTOCRYPT_PRINTF
#endif

#if (DEBUG_KORUNIV == ON)
#define	KORUNIV_PRINTF		PRINTF
#else
#define	KORUNIV_PRINTF
#endif

#if (DEBUG_KETI == ON)
#define	KETI_PRINTF			PRINTF
#else
#define	KETI_PRINTF
#endif

#endif /* _CONFIG_H_ */
