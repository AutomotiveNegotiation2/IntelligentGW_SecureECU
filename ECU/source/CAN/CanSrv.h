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
	uint32_t	timer;
	uint32_t	busoff;
	uint8_t		TaskEn;
} can_timer_t;

#pragma pack(pop)

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

#endif /* _CANSRV_H_ */
