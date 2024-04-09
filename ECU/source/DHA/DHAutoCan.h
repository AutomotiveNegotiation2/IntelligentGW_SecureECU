#ifndef _DHAUTO_CAN_H_
#define	_DHAUTO_CAN_H_

#include "DHAutoCan_par.h"
#include "DHAutoCan_il.h"
#include "DHAutoCan_il_par.h"

enum {
	KEY_OFF = 0,
	ACCESSORY,
	RUN,
	CRANK_REQUEST,
};

enum {
	INVALID = 0,
	VALID,
};

#pragma pack(push, 4)

typedef struct {
	uint32_t	SchudleTask;
	uint32_t	busoff;
	uint8_t		TaskEn;
} can_timer_t;

typedef struct {
	uint8_t	inst;
	uint32_t id;
	uint8_t dlc;
	uint8_t data[16];
} queue_can_rx_buf_t;

#pragma pack(pop)

void CanTimer_Incr(void);

void ApplCan_InitBuf(void);
void CAN_ACC_ON_Init(can_inst_t instance);
uint8_t CanGetTaskEnState(void);
void QueuePushCanDataforRx2(uint8_t inst, uint32_t id, uint8_t dlc, uint8_t * data);
void QueuePopCanDataforRx2(void);

void ApplTxECU1_Blind_Zone_Alert_Status_TxComfirmation(void);
void ApplTxECU1_SystemPowerMode_TxComfirmation(void);

void ApplTxECU2_V2V_Warning_TxComfirmation(void);
void ApplTxECU2_Clock_TxComfirmation(void);
void CanMain(void);

#endif /* _DHAUTO_CAN_H_ */
