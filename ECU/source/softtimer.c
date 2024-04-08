#include "fsl_pit.h"

#include "Includes.h"

#define	SYSTEM_TIMER_BASEADDR		PIT1
#define	SYSTEM_TIMER_CHANNEL		kPIT_Chnl_0
#define	SYSTEM_TIMER_IRQ_HANDLER	PIT1_IRQHandler
#define	SYSTEM_TIMER_IRQn			PIT1_IRQn
#define	SYSTEM_TIMER_SOURCE_CLOCK	CLOCK_GetRootClockFreq(kCLOCK_Root_Bus)
#define	SYSTEM_TIMER_TIMEOUT		1000U

uint32_t nTimer_1ms;

SoftTimerInfo SoftTimerTable[STIMER_END_OF_ID-1];

void SYSTEM_TIMER_IRQ_HANDLER(void)
{
	uint8_t i;

	if (PIT_GetStatusFlags(SYSTEM_TIMER_BASEADDR, SYSTEM_TIMER_CHANNEL) != 0)
	{
		PIT_ClearStatusFlags(SYSTEM_TIMER_BASEADDR, SYSTEM_TIMER_CHANNEL, kPIT_TimerFlag);
	
		nTimer_1ms++;

		CanTimer.SchudleTask++;

		for(i=0;i<STIMER_END_OF_ID-1;i++) 	SoftTimerTable[i].nCounter++;
	}

	SDK_ISR_EXIT_BARRIER;
}

void SysTimer_Config(void)
{
	pit_config_t pitConfig;

	PIT_GetDefaultConfig(&pitConfig);
	PIT_Init(SYSTEM_TIMER_BASEADDR, &pitConfig);
	PIT_SetTimerPeriod(SYSTEM_TIMER_BASEADDR, SYSTEM_TIMER_CHANNEL, USEC_TO_COUNT(SYSTEM_TIMER_TIMEOUT, SYSTEM_TIMER_SOURCE_CLOCK));
	PIT_EnableInterrupts(SYSTEM_TIMER_BASEADDR, SYSTEM_TIMER_CHANNEL, kPIT_TimerInterruptEnable);
	EnableIRQ(SYSTEM_TIMER_IRQn);

	PIT_StartTimer(SYSTEM_TIMER_BASEADDR, SYSTEM_TIMER_CHANNEL);
}

uint32_t GetSoftTimerValue(void)
{
	return (nTimer_1ms+1);
}

void SoftTimerInit(void)
{
	memset(SoftTimerTable, 0, sizeof(SoftTimerTable));
	//WT_Start();
	nTimer_1ms = 0;
	SysTimer_Config();
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

void SoftTimerDeinit(void)
{
	
}

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

	if(nTimer_1ms > 1000)       
	{// 1sec
		nTimer_1ms = 0;   
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

