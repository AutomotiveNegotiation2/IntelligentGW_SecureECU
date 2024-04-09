#include "Includes.h"

SoftTimerInfo SoftTimerTable[STIMER_END_OF_ID-1];

uint16_t SetSoftTimer(uint16_t nID, uint16_t nElapse, FuncSTimerCallBack lpfnTimer)
{
	int idx;
	idx = nID -1;
	if(idx >= STIMER_END_OF_ID-1)
		return STIMER_START_OF_ID;

	if(SoftTimerTable[idx].bActivate == TRUE)
		return STIMER_START_OF_ID;

	if(lpfnTimer == NULL)
		return STIMER_START_OF_ID;

	memset(&SoftTimerTable[idx], 0, sizeof(SoftTimerTable[idx]));   

	SoftTimerTable[idx].nElapse = nElapse;
	SoftTimerTable[idx].nEventID = nID;
	SoftTimerTable[idx].bActivate = TRUE;
	SoftTimerTable[idx].pCallBack = lpfnTimer;

	return nID;
}

void KillSoftTimer(uint16_t nID)
{
	int idx;
	idx = nID-1;
	memset(&SoftTimerTable[idx], 0, sizeof(SoftTimerTable[idx]));
}

void SoftTimerSrv(void)
{
	int i;
	FuncSTimerCallBack pFnTimerCallBack;

	if(GetSoftTimerValue() > DHAUTO_SOFTTIME_1S)       
	{// 1sec
		ClearSoftTimerValue();   
	}
 
	for(i=0;i<STIMER_END_OF_ID-1;i++)
	{
		if(SoftTimerTable[i].bActivate == TRUE && SoftTimerTable[i].nCounter >= SoftTimerTable[i].nElapse)
		{
			SoftTimerTable[i].nCounter = 0;
			pFnTimerCallBack = (FuncSTimerCallBack)SoftTimerTable[i].pCallBack;
			if(pFnTimerCallBack != NULL) 
			{
				pFnTimerCallBack();
			}
			else
			{
				//while(1);
			}
		}
	}   
}

uint16_t ClearSoftTimerCounter(uint16_t nID)
{
	uint16_t idx;

	idx = nID - 1;
	if(idx >= STIMER_END_OF_ID-1)
		return STIMER_START_OF_ID;

	SoftTimerTable[idx].nCounter = 0;

	return nID;
}

