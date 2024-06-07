#include "Includes.h"

static void AppSrv(void);
static void RUN_APP_DN_ACC_OFF(void);
static void RUN_APP_UP_ACC_ON(void);

void AppMain(void)
{
	SoftTimerSrv();
	AppSrv();
}

static void AppSrv(void)
{
	switch(GlobalPocSeq.GSeq)
	{
		case GB_SEQ_UP_ACC_OFF:
			if(GlobalPocSeq.LSeq.B.SEQ_APP == LO_SEQ_START)
			{
				GlobalPocSeq.LSeq.B.SEQ_APP = LO_SEQ_FINISH;
			}
			break;

		case GB_SEQ_ACC_OFF:
			break;

		case GB_SEQ_DN_ACC_OFF:
			RUN_APP_DN_ACC_OFF();
			break;

		case GB_SEQ_UP_ACC_ON:
			RUN_APP_UP_ACC_ON();
			break;

		case GB_SEQ_ACC_ON:
			break;

		default:
			break;
	}
}

static void RUN_APP_DN_ACC_OFF(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_APP)
	{
		case LO_SEQ_START:
			GlobalPocSeq.LSeq.B.SEQ_APP = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			GlobalPocSeq.LSeq.B.SEQ_APP = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			GlobalPocSeq.LSeq.B.SEQ_APP = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_APP = LO_SEQ_START;
			// error
			APPINFO_PRINTF("[%s] APP Sequence Error\n", __func__);
			break;
	}
}

static void RUN_APP_UP_ACC_ON(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_APP)
	{
		case LO_SEQ_START:
			KillSoftTimer(STIMER_IOCTRL_LIGHTING_GRILL_LED_OP);
			
			GlobalPocSeq.LSeq.B.SEQ_APP = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			BOARD_InitFuncLightingGrillPins();
			lightingGrill_Init();
			
			GlobalPocSeq.LSeq.B.SEQ_APP = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			lightingGrill_OpStart(OP_LED_WELCOME, 5);
			
			GlobalPocSeq.LSeq.B.SEQ_APP = LO_SEQ_03;
			break;

		case LO_SEQ_03:
			GlobalPocSeq.LSeq.B.SEQ_APP = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_APP = LO_SEQ_START;
			// error
			APPINFO_PRINTF("[%s] APP Sequence Error\n", __func__);
			break;
	}
}

