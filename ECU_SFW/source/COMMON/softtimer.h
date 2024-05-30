#ifndef _SOFTTIMER_H_
#define	_SOFTTIMER_H_

typedef void (*TimerFuncCallback)(void);

#pragma pack(push, 4)

typedef enum 
{
	ORGAN_COMMON = 0,
	ORGAN_AUTOCRYPT,
	ORGAN_KETI,
	ORGAN_KORU,
#if (DHAUTO_FUNC_EN == ON)
	ORGAN_DHAUTO,
	ORGAN_DHAUTO_PLUS,
#endif
	ORGAN_MAX,
} organ_t;

#pragma pack(pop)

void SoftTimerInit(void);
void StartFuncExecTime(organ_t organ, char *s);
void StopFuncExecTime(void);
void PrintFuncExecTime(void);
uint32_t GetSoftTimerValue(void);
void ClearSoftTimerValue(void);
void TimerCallback_Register(organ_t organ, void * callback);
void TimerCallback_Clear(organ_t organ);

bool GetFuncTimer_100ms(void);
bool ClearFuncTimer_100ms(void);
bool GetFuncTimer_200ms(void);
bool ClearFuncTimer_200ms(void);
bool GetFuncTimer_500ms(void);
bool ClearFuncTimer_500ms(void);
bool GetFuncTimer_1000ms(void);
bool ClearFuncTimer_1000ms(void);

#endif /* _SOFTTIMER_H_ */