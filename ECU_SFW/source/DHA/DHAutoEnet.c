#include "Includes.h"

static void EnetSrv(void);
static void RUN_ENET_UP_ACC_ON(void);
static void RUN_ENET_ACC_ON(void);
static void RUN_ENET_DN_ACC_OFF(void);

void EnetMain(void)
{
	SoftTimerSrv();
	EnetSrv();
}

static void EnetSrv(void)
{
	switch(GlobalPocSeq.GSeq)
	{
		case GB_SEQ_UP_ACC_OFF:
			if(GlobalPocSeq.LSeq.B.SEQ_ENET == LO_SEQ_START)
			{
				GlobalPocSeq.LSeq.B.SEQ_ENET = LO_SEQ_FINISH;
			}
			break;

		case GB_SEQ_ACC_OFF:
			if(GlobalPocSeq.LSeq.B.SEQ_ENET == LO_SEQ_START)
			{
				GlobalPocSeq.LSeq.B.SEQ_ENET = LO_SEQ_FINISH;
			}
			break;

		case GB_SEQ_DN_ACC_OFF:
			RUN_ENET_DN_ACC_OFF();
			break;

		case GB_SEQ_UP_ACC_ON:
			RUN_ENET_UP_ACC_ON();
			break;

		case GB_SEQ_ACC_ON:
			RUN_ENET_ACC_ON();
			break;

		default:
			break;
	}
}

static void RUN_ENET_UP_ACC_ON(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_ENET)
	{
		case LO_SEQ_START:
			GlobalPocSeq.LSeq.B.SEQ_ENET = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			GlobalPocSeq.LSeq.B.SEQ_ENET = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			GlobalPocSeq.LSeq.B.SEQ_ENET = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_ENET = LO_SEQ_START;
			// error
			ENETINFO_PRINTF("[%s] ENET Sequence Error\n", __func__);
			break;
	}
}

static void RUN_ENET_ACC_ON(void)
{
	if (Enet_GetLinkUp_1G() == TRUE)
	{
	}
	else
	{
	}
}

static void RUN_ENET_DN_ACC_OFF(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_ENET)
	{
		case LO_SEQ_START:
			GlobalPocSeq.LSeq.B.SEQ_ENET = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			GlobalPocSeq.LSeq.B.SEQ_ENET = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			GlobalPocSeq.LSeq.B.SEQ_ENET = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_ENET = LO_SEQ_START;
			// error
			ENETINFO_PRINTF("[%s] ENET Sequence Error\n", __func__);
			break;
	}
}

