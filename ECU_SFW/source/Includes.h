#ifndef _INCLUDES_H_
#define	_INCLUDES_H_

#include <stdio.h>

#include "pin_mux.h"
#include "fsl_pit.h"
#include "fsl_lpuart.h"
#include "clock_config.h"

#include "board.h"

#include "main.h"
#include "typedef.h"
#include "appconfig.h"
#include "softtimer.h"

#include "fsl_phy.h"
#include "fsl_enet.h"

#include "appcommon.h"
#if (DHAUTO_FUNC_EN == ON)
#include "DHAuto.h"
#endif

#endif /* _INCLUDES_H_ */
