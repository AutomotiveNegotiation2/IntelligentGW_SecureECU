#include "Includes.h"

void Init_DHAutoFunc(void)
{
	GlobalSequence_Init();

#if ((CAN3toCAN_EN == ON) || (CAN1toCANFD_EN == ON))
	ApplCan_InitBuf();
#if (CAN3toCAN_EN == ON)
	CAN_ACC_ON_Init(CAN_CH_3);	// CAN
#endif

#if (CAN1toCANFD_EN == ON)
	CAN_ACC_ON_Init(CAN_CH_1);	// CANFD
#endif
#endif
}

void DHAutoFunc(void)
{
	GlobalSequence();

#if ((CAN3toCAN_EN == ON) || (CAN1toCANFD_EN == ON))
	CanMain();
#endif
	EnetMain();
	AppMain();
	IoctrlMain();
}

