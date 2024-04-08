#ifndef _CANSRV_H_
#define	_CANSRV_H_

#include "fsl_gpio.h"
#include "pin_mux.h"

#pragma pack(push, 4)

typedef void (*FuncCanTransCallback)(void);

typedef struct {
	FuncCanTransCallback 	Standby;
	//FuncCanTransCallback 	GoToSleep;
	//FuncCanTransCallback 	ListenOnly;
	FuncCanTransCallback 	Normal;
} canTransFnCallback;

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

extern can_timer_t CanTimer;

static inline void CAN1_TRANS_TO_STANDBY_MODE(void)
{
	GPIO_WritePinOutput(BOARD_INITCANPINS_CAN_FD_STBY_GPIO, BOARD_INITCANPINS_CAN_FD_STBY_GPIO_PIN, 1);
}

static inline void CAN1_TRANS_TO_NORMAL_MODE(void)
{
	GPIO_WritePinOutput(BOARD_INITCANPINS_CAN_FD_STBY_GPIO, BOARD_INITCANPINS_CAN_FD_STBY_GPIO_PIN, 0);
}

static inline void CAN3_TRANS_TO_STANDBY_MODE(void)
{
	GPIO_WritePinOutput(BOARD_INITCANPINS_CAN_FD_STBY_GPIO, BOARD_INITCANPINS_CAN_FD_STBY_GPIO_PIN, 1);
}

static inline void CAN3_TRANS_TO_NORMAL_MODE(void)
{
	GPIO_WritePinOutput(BOARD_INITCANPINS_CAN_FD_STBY_GPIO, BOARD_INITCANPINS_CAN_FD_STBY_GPIO_PIN, 0);
}

void CanSrv(void);
void ApplCan_InitBuf(void);
uint8_t CanGetTaskEnState(void);
void QueuePushCanDataforRx2(uint8_t inst, uint32_t id, uint8_t dlc, uint8_t * data);
void QueuePopCanDataforRx2(void);

void ApplTxECU1_Blind_Zone_Alert_Status_TxComfirmation(void);

#endif /* _CANSRV_H_ */
