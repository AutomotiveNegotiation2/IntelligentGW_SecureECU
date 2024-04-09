#include "Includes.h"

GLOBAL_PROC_SEQUENCE GlobalPocSeq;
eGLOBAL_SEQ BackupGSeq = GB_SEQ_BATT_OFF;
uint8_t gFlagSystemActive;
uint32_t gLO_ALL_FINISH;

void GlobalSequence_Init(void)
{
	gLO_ALL_FINISH = 0x0000FFFF;

	GlobalSeqSwitch(GB_SEQ_UP_ACC_OFF);
	gFlagSystemActive = FALSE;
}

void GlobalSequence(void)
{
	switch(GlobalPocSeq.GSeq)
	{
		case GB_SEQ_UP_ACC_OFF:
			if (GlobalPocSeq.LSeq.U == gLO_ALL_FINISH)
			{
				GlobalSeqSwitch(GB_SEQ_ACC_OFF);
			}
			break;

		case GB_SEQ_ACC_OFF:
			GlobalSeqSwitch(GB_SEQ_UP_ACC_ON);
			break;

		case GB_SEQ_DN_ACC_OFF:
			break;

		case GB_SEQ_UP_ACC_ON:
			if(GlobalPocSeq.LSeq.U == gLO_ALL_FINISH)
			{
				GlobalSeqSwitch(GB_SEQ_ACC_ON);
			}
			break;

		case GB_SEQ_ACC_ON:
			break;

		default:
			break;
	}
}

void ClearLocalSEQ(void)
{
	uint32_t i=0;

	for(i=STIMER_START_OF_ID+1;i<STIMER_END_OF_SEQ_ID;i++) 
	{
		KillSoftTimer(i);
	}
	GlobalPocSeq.LSeq.U = LO_SEQ_START;
	memset(&GlobalPocSeq.LSeq, 0, sizeof(GlobalPocSeq.LSeq));
}

void GlobalSeqSwitch(eGLOBAL_SEQ GSEQ)
{
	if(GSEQ > GB_SEQ_START && GSEQ < GB_SEQ_END)
	{
		BackupGSeq = GlobalPocSeq.GSeq = GSEQ;
		ClearLocalSEQ();
	}
}
