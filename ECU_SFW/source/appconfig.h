#ifndef _CONFIG_H_
#define	_CONFIG_H_

#include <stdint.h>
#include "fsl_debug_console.h"

/* Enable/Disable the debug message output via uart. */
#define	DEBUG_COMMON	ON
#define	DEBUG_AUTOCRYPT	OFF
#define	DEBUG_KORUNIV	OFF
#define	DEBUG_KETI		OFF
#define	DEBUG_DHAUTO	OFF

//#define	ORGAN_FUNC_LOAD	OFF

/* Enable/Disable CAN & CAN-FD
   Enable CAN.
   Enable CAN-FD.
   Enable CAN & CAN-FD for only test */
#define	CAN3toCAN_EN	ON
#define	CAN1toCANFD_EN	OFF

/* Enable/Disable DHAUTO function. */
#define	DHAUTO_FUNC_EN				ON
#define	LIGHTING_GRILL_INSTALLED	ON

/* Enable/Disable the output of execution time message. */
#define	EXECUTION_TIME_LOG				OFF
#if (EXECUTION_TIME_LOG == ON)
#define	EXECUTION_TIME_LOG_COMMON		ON
#define	EXECUTION_TIME_LOG_AUTOCRYPT	OFF
#define	EXECUTION_TIME_LOG_KORUNIV		OFF
#define	EXECUTION_TIME_LOG_KETI			OFF
#define	EXECUTION_TIME_LOG_DHAUTO		ON
#else
#define	EXECUTION_TIME_LOG_COMMON		OFF
#define	EXECUTION_TIME_LOG_AUTOCRYPT	OFF
#define	EXECUTION_TIME_LOG_KORUNIV		OFF
#define	EXECUTION_TIME_LOG_KETI			OFF
#define	EXECUTION_TIME_LOG_DHAUTO		OFF
#endif

#if ((CAN3toCAN_EN == OFF) && (CAN1toCANFD_EN == OFF))
#error CAN function more than one channel must be activated
#endif

#endif /* _CONFIG_H_ */
