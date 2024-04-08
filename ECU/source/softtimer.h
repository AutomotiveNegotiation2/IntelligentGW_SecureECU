#ifndef _SOFTTIMER_H_
#define _SOFTTIMER_H_

#include "can_par.h"

#pragma pack(push, 4)

enum 
{
	STIMER_START_OF_ID,	
	STIMER_MAIN,	
	STIMER_POWER,
	STIMER_CAN,
	STIMER_ENET_100M,
	STIMER_COMM,
	STIMER_IOCTRL,
	STIMER_IDLE,
	STIMER_END_OF_SEQ_ID, /* End of Sequence control Timer */

	STIMER_POWER_PWC_WKUP,
	STIMER_POWER_CAM,
	STIMER_POWER_SC_MODE,
	STIMER_POWER_CPU_POWER_OFF_WAIT,
	STIMER_POWER_CPU_OFF,

	STIMER_CAN3_TX_MSG_TIMER_START,
	STIMER_CAN3_TX_MSG_TIMER_END = STIMER_CAN3_TX_MSG_TIMER_START + CAN3_NO_OF_TX_OBJECT - 1,
	STIMER_CAN3_TX_TEST,

	STIMER_CAN1_TX_MSG_TIMER_START,
	STIMER_CAN1_TX_MSG_TIMER_END = STIMER_CAN1_TX_MSG_TIMER_START + CAN1_NO_OF_TX_OBJECT - 1,
	STIMER_CAN1_TX_TEST,

	STIMER_ENET_100M_LINKUP,
	STIMER_ENET_100M_UDP_TEST,
	STIMER_ENET_100M_TCP_TEST,

	STIMER_COMM_INNER_SRV,
	STIMER_COMM_INNER_INT100_CHANNEL,
	STIMER_COMM_INNER_BK_CHANNEL,
	STIMER_COMM_INNER_HS_CHANNEL,
	STIMER_COMM_INNER_WAIT_ACK,
	
	STIMER_SYSTEM_STABLE,

#if defined (DEBUG_EN_RTC)
	STIMER_IOCTRL_RTC,
#endif /* #if (DEBUG_RTC == ON) */
#ifdef DEBUG_IGN_DET_EN
	STIMER_IOCTRL_CRASH,
#endif /* #ifdef DEBUG_IGN_DET_EN */
	STIMER_DEBUG,
	STIMER_END_OF_ID       	
};

typedef void (*FuncSTimerCallBack)(void);

typedef struct TagSoftTimer
{
	uint16_t	nEventID;
	uint16_t	nElapse;
	uint16_t	nCounter;
	bool     	bActivate;
	FuncSTimerCallBack pCallBack;
} SoftTimerInfo;

#pragma pack(pop)

void callback_systemTimer(void * param);
void SoftTimerInit(void);
uint16_t SetSoftTimer(uint16_t nID, uint16_t nElapse, FuncSTimerCallBack lpfnTimer);
void KillSoftTimer(uint16_t nID);
void SoftTimerSrv(void);
uint16_t ClearSoftTimerCounter(uint16_t nID);

#endif /* _SOFTTIMER_H_ */
