#include "Includes.h"

void Init_DHAutoFunc(void)
{
	GlobalSequence_Init();
	
	ApplCan_InitBuf();
#if (CAN3toCAN_EN == ON)
	CAN_ACC_ON_Init(CAN_CH_3);	// CAN
#endif

#if (CAN1toCANFD_EN == ON)
	CAN_ACC_ON_Init(CAN_CH_1);	// CANFD
#endif
}

void DHAutoFunc(void)
{
	GlobalSequence();
	
	CanMain();
	EnetMain();
	AppMain();
	IoctrlMain();
}

