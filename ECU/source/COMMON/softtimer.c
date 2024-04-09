#include "Includes.h"

#define	SYSTEM_TIMER_BASEADDR		PIT1
#define	SYSTEM_TIMER_CHANNEL		kPIT_Chnl_0
#define	SYSTEM_TIMER_IRQ_HANDLER	PIT1_IRQHandler
#define	SYSTEM_TIMER_IRQn			PIT1_IRQn
#define	SYSTEM_TIMER_SOURCE_CLOCK	CLOCK_GetRootClockFreq(kCLOCK_Root_Bus)
#define	SYSTEM_TIMER_TIMEOUT		1000U

#define	FUNC_TIMER_CHANNEL			kPIT_Chnl_1
//#define	FUNC_TIMER_TIMEOUT			10000U	// 10ms
#define	FUNC_TIMER_TIMEOUT			20000U	// 20ms

#define	MAX_EXECUTION_TIME_10MS		10
#define	MAX_EXECUTION_TIME_20MS		20

#define	TIMEOUT_OFF		0
#define TIMEOUT_ON		1

typedef struct {
	char funcName[64];
	organ_t organ;
	uint32_t execFuncTime;
	uint32_t execMaxTime;
	uint32_t execSrvTime;
	bool timeout;
} funcExec_time_t;

TimerFuncCallback timerCallback[ORGAN_MAX] = {NULL, };

static uint32_t nTimer_1ms;
static uint32_t nFuncTimer_1ms;

static funcExec_time_t fEtime_Organ[ORGAN_MAX];
static funcExec_time_t * fEtime;

static void SysTimer_Config(void);
static void FuncTimer_Config(void);

void SYSTEM_TIMER_IRQ_HANDLER(void)
{
	if (PIT_GetStatusFlags(SYSTEM_TIMER_BASEADDR, SYSTEM_TIMER_CHANNEL) != 0)
	{
		PIT_ClearStatusFlags(SYSTEM_TIMER_BASEADDR, SYSTEM_TIMER_CHANNEL, kPIT_TimerFlag);

		nTimer_1ms++;
		nFuncTimer_1ms++;

		for (uint8_t i=0; i<ORGAN_MAX; i++)
		{
			if (timerCallback[i] != NULL)
				(*timerCallback[i])();
		}
	}

	if (PIT_GetStatusFlags(SYSTEM_TIMER_BASEADDR, FUNC_TIMER_CHANNEL) != 0)
	{
		PIT_ClearStatusFlags(SYSTEM_TIMER_BASEADDR, FUNC_TIMER_CHANNEL, kPIT_TimerFlag);

		fEtime->timeout = TIMEOUT_ON;
	}

	SDK_ISR_EXIT_BARRIER;
}

void SoftTimerInit(void)
{
	nTimer_1ms = 0;
	nFuncTimer_1ms = 0;
	SysTimer_Config();

	memset(fEtime_Organ, 0, sizeof(funcExec_time_t)*ORGAN_MAX);
	memset(fEtime, 0, sizeof(funcExec_time_t));
}

void TimerCallback_Register(organ_t organ, void * callback)
{
	timerCallback[organ] = callback;
}

void TimerCallback_Clear(organ_t organ)
{
	timerCallback[organ] = NULL;
}


uint32_t GetSoftTimerValue(void)
{
	//return (nTimer_1ms+1);
	return nTimer_1ms;
}

void ClearSoftTimerValue(void)
{
	nTimer_1ms = 0;
}

static void SysTimer_Config(void)
{
	pit_config_t pitConfig;

	PIT_GetDefaultConfig(&pitConfig);
	PIT_Init(SYSTEM_TIMER_BASEADDR, &pitConfig);

	/* System Timer Setup */
	PIT_SetTimerPeriod(SYSTEM_TIMER_BASEADDR, SYSTEM_TIMER_CHANNEL, USEC_TO_COUNT(SYSTEM_TIMER_TIMEOUT, SYSTEM_TIMER_SOURCE_CLOCK));
	PIT_EnableInterrupts(SYSTEM_TIMER_BASEADDR, SYSTEM_TIMER_CHANNEL, kPIT_TimerInterruptEnable);

	/* Func Timer Setup */
	PIT_EnableInterrupts(SYSTEM_TIMER_BASEADDR, FUNC_TIMER_CHANNEL, kPIT_TimerInterruptEnable);

	EnableIRQ(SYSTEM_TIMER_IRQn);

	PIT_StartTimer(SYSTEM_TIMER_BASEADDR, SYSTEM_TIMER_CHANNEL);
}

void StartFuncExecTime(organ_t organ, char *s)
{
	if (organ >= ORGAN_MAX)
	{
		COMMON_PRINTF("[%s] Organization name isn't valid.\r\n", __func__);
		assert(0);
	}

	fEtime = &fEtime_Organ[organ];
	
	memset(fEtime->funcName, 0, sizeof(fEtime->funcName));
	fEtime->organ = organ;
	memcpy(fEtime->funcName, s, strlen(s));

	PIT_SetTimerPeriod(SYSTEM_TIMER_BASEADDR, FUNC_TIMER_CHANNEL, USEC_TO_COUNT(FUNC_TIMER_TIMEOUT, SYSTEM_TIMER_SOURCE_CLOCK));
	PIT_StartTimer(SYSTEM_TIMER_BASEADDR, FUNC_TIMER_CHANNEL);
}

void StopFuncExecTime(void)
{
	uint32_t msec;

	msec = COUNT_TO_MSEC(PIT_GetCurrentTimerCount(SYSTEM_TIMER_BASEADDR, FUNC_TIMER_CHANNEL), SYSTEM_TIMER_SOURCE_CLOCK);	
	PIT_StopTimer(SYSTEM_TIMER_BASEADDR, FUNC_TIMER_CHANNEL);
#if (DHAUTO_FUNC_EN == ON)
	funcExec_time_t * fEtimeTmp;

	if (fEtime->organ == ORGAN_DHAUTO_PLUS)
	{
		fEtimeTmp = &fEtime_Organ[ORGAN_DHAUTO];

		fEtimeTmp->execFuncTime += (FUNC_TIMER_TIMEOUT/1000U) - msec;
		fEtime->execFuncTime += (FUNC_TIMER_TIMEOUT/1000U) - msec;
	}
	else if (fEtime->organ == ORGAN_DHAUTO)
	{
		fEtime->execFuncTime += (FUNC_TIMER_TIMEOUT/1000U) - msec;
	}
	else
#endif
	{
		fEtime->execFuncTime = (FUNC_TIMER_TIMEOUT/1000U) - msec;
	}

	if ((fEtime->timeout == TIMEOUT_ON) || (fEtime->execMaxTime > MAX_EXECUTION_TIME_20MS))
	{
		COMMON_PRINTF("Stop ECU execution because of the func %s [%dms>20ms].\r\n", fEtime->funcName, fEtime->execMaxTime);
		assert(0);
	}
	else
	{
		if (fEtime->execFuncTime > fEtime->execMaxTime)
		{
			fEtime->execMaxTime = fEtime->execFuncTime;
		}
#if (DHAUTO_FUNC_EN == ON)
		if (fEtime->organ == ORGAN_DHAUTO)
		{
			fEtimeTmp = &fEtime_Organ[ORGAN_DHAUTO_PLUS];
			
			fEtime->execFuncTime = 0;
			fEtimeTmp->execFuncTime = 0;
		}
#endif
	}
}

void ClearPrintFuncExecTimeValue(void)
{
	nFuncTimer_1ms = 0;
}

uint32_t GetPrintFuncExecTimeValue(void)
{
	return nFuncTimer_1ms;
}

void PrintFuncExecTime(void)
{
	funcExec_time_t * fEtimeTmp;

	COMMON_PRINTF("\33[31m");	// red
#if 0
	COMMON_PRINTF("++++++++++++++++++++++++++++++++++++++++++++++\r\n");
	for (i=ORGAN_COMMON; i<=ORGAN_DHAUTO; i++)
	//for (i=ORGAN_COMMON; i<ORGAN_MAX; i++)
	{
		fEtimeTmp = &fEtime_Organ[i];

		COMMON_PRINTF("[%s] Max execution time is %02d ms.\r\n", fEtimeTmp->funcName, fEtimeTmp->execMaxTime);

		// clear execution time every 1s after printing the time.
		memset(fEtimeTmp, 0, sizeof(funcExec_time_t));
	}
	COMMON_PRINTF("----------------------------------------------\r\n");
#else

	COMMON_PRINTF("+++++ Max Execution Time +++++\r\n");
#if (EXECUTION_TIME_LOG_COMMON == ON)
	fEtimeTmp = &fEtime_Organ[ORGAN_COMMON];
	COMMON_PRINTF("[%s] : %02d ms.\r\n", fEtimeTmp->funcName, fEtimeTmp->execMaxTime);
#endif

#if (EXECUTION_TIME_LOG_AUTOCRYPT == ON)
	fEtimeTmp = &fEtime_Organ[ORGAN_AUTOCRYPT];
	COMMON_PRINTF("[%s] : %02d ms.\r\n", fEtimeTmp->funcName, fEtimeTmp->execMaxTime);
#endif

#if (EXECUTION_TIME_LOG_KORUNIV == ON)
	fEtimeTmp = &fEtime_Organ[ORGAN_KORU];
	COMMON_PRINTF("[%s] : %02d ms.\r\n", fEtimeTmp->funcName, fEtimeTmp->execMaxTime);
#endif

#if (EXECUTION_TIME_LOG_KETI == ON)
	fEtimeTmp = &fEtime_Organ[ORGAN_KETI];
	COMMON_PRINTF("[%s] : %02d ms.\r\n", fEtimeTmp->funcName, fEtimeTmp->execMaxTime);
#endif

#if ((DHAUTO_FUNC_EN == ON) && (EXECUTION_TIME_LOG_DHAUTO == ON))
	fEtimeTmp = &fEtime_Organ[ORGAN_DHAUTO];
	COMMON_PRINTF("[%s] : %02d ms.\r\n", fEtimeTmp->funcName, fEtimeTmp->execMaxTime);
#endif

	memset(fEtime_Organ, 0, sizeof(funcExec_time_t)*ORGAN_MAX);
#if 0
	for (uint8_t i=ORGAN_COMMON; i<=ORGAN_DHAUTO; i++)
	{
		fEtimeTmp = &fEtime_Organ[i];

		COMMON_PRINTF("[%s] : %02d ms.\r\n", fEtimeTmp->funcName, fEtimeTmp->execMaxTime);

		// clear execution time every 1s after printing the time.
		memset(fEtimeTmp, 0, sizeof(funcExec_time_t));
	}
#endif
	//COMMON_PRINTF("------------------------------\r\n");
#endif
	COMMON_PRINTF("\33[0m");	// normal
}

