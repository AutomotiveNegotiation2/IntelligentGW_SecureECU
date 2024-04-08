#include "Includes.h"

void RUN_IOCTRL_DN_ACC_OFF(void);
void RUN_IOCTRL_UP_ACC_ON(void);

void IoctrlSrv(void)
{
	switch(GlobalPocSeq.GSeq)
	{
		case GB_SEQ_UP_ACC_OFF:
			if(GlobalPocSeq.LSeq.B.SEQ_IOCTRL == LO_SEQ_START)
			{
				GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_FINISH;
			}
			break;

		case GB_SEQ_ACC_OFF:
			break;

		case GB_SEQ_DN_ACC_OFF:
			RUN_IOCTRL_DN_ACC_OFF();
			break;

		case GB_SEQ_UP_ACC_ON:
			RUN_IOCTRL_UP_ACC_ON();
			break;

		case GB_SEQ_ACC_ON:
			break;

		default:
			break;
	}
}

void RUN_IOCTRL_DN_ACC_OFF(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_IOCTRL)
	{
		case LO_SEQ_START:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_START;
			// error
			SYSINFO_PRINTF("[%s] IOCTRL Sequence Error\n", __func__);
			break;
	}
}

void RUN_IOCTRL_UP_ACC_ON(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_IOCTRL)
	{
		case LO_SEQ_START:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_START;
			// error
			SYSINFO_PRINTF("[%s] IOCTRL Sequence Error\n", __func__);
			break;
	}
}

