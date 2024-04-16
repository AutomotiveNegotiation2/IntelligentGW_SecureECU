/* ======================================================================
 *   Copyright (c) 2023 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/**
 *  \file     PwmApp_Startup.h
 *
 *  \brief    PWM example header file
 *
 */

#ifndef ICUAPP_STARTUP_H_
#define ICUAPP_STARTUP_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include "Icu.h"
#include "Icu_Irq.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define ICU_CHANNEL        (ICU_CHANNEL2)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

void PwmApp_PowerAndClkSrc(void);

#ifdef __cplusplus
}
#endif

#endif  /* #ifndef PWMAPP_STARTUP_H_ */
