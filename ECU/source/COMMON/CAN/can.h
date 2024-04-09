#ifndef _CAN_H_
#define	_CAN_H_

#include "fsl_flexcan.h"

typedef enum {
	CAN_CH_NULL = 0,
	CAN_CH_1,
	CAN_CH_2,
	CAN_CH_3,
	CAN_CH_MAX,
} can_inst_t;

typedef enum {
	CAN_TRANS_OPMODE_STANDBY = 0,
	CAN_TRANS_OPMODE_GO_TO_SLEEP,
	CAN_TRANS_OPMODE_LISTEN_ONLY,
	CAN_TRANS_OPMODE_NORMAL
} can_trans_opmode_t;

typedef enum {
	MSG_UPDATE_COMPLETE = 0u,
	MSG_UPDATE_REQUEST,
} msg_update_inst_t;

typedef void (*FuncCanTxCallback)(void);
typedef void (*FuncCanRxCallback)(uint8_t * data, uint8_t dlc);

typedef void (*CanRxFuncCallback)(void * callback, uint8_t no, uint32_t id, uint8_t dlc, uint8_t * data);
typedef void (*CanTxFuncCallback)(void * callback, uint8_t no);

typedef void (*FuncCanTransCallback)(void);

#pragma pack(push, 4)

typedef struct {
	can_inst_t inst;
	uint8_t NoOfMsg;
	uint8_t * mbox;
	uint32_t * id;
	uint8_t * dlc;
	uint8_t ** data;
	uint8_t * attr;
	uint16_t * attrtime;
	uint16_t * stimerId;
	uint8_t * stimer_state;
	FuncCanTxCallback * tCallback;
	FuncCanRxCallback * rCallback;
	msg_update_inst_t * msgUpdate;
} CAN_MSG_FUNC_ptr;

typedef struct {
	CAN_Type *					base;
	uint32_t					baudRate;
	uint32_t					baudRateFD;
	uint8_t						maxMbNum;
	bool						fdEnable;
	flexcan_handle_t 			fCanHandle;
	flexcan_frame_t 			frame;
	flexcan_fd_frame_t			framefd;
	flexcan_transfer_callback_t callback;
	/*CAN_MSG_FUNC_ptr*/void *			msgRx;
	/*CAN_MSG_FUNC_ptr*/void *			msgTx;
} can_config_t;

typedef struct {
	FuncCanTransCallback 	Standby;
	//FuncCanTransCallback 	GoToSleep;
	//FuncCanTransCallback 	ListenOnly;
	FuncCanTransCallback 	Normal;
} canTransFnCallback;

#pragma pack(pop)

static inline void CAN1_TRANS_TO_STANDBY_MODE(void)
{
	GPIO_WritePinOutput(BOARD_INITPINS_CAN_FD_STBY_GPIO, BOARD_INITPINS_CAN_FD_STBY_GPIO_PIN, 1);
}

static inline void CAN1_TRANS_TO_NORMAL_MODE(void)
{
	GPIO_WritePinOutput(BOARD_INITPINS_CAN_FD_STBY_GPIO, BOARD_INITPINS_CAN_FD_STBY_GPIO_PIN, 0);
}

static inline void CAN3_TRANS_TO_STANDBY_MODE(void)
{
	GPIO_WritePinOutput(BOARD_INITPINS_CAN_FD_STBY_GPIO, BOARD_INITPINS_CAN_FD_STBY_GPIO_PIN, 1);
}

static inline void CAN3_TRANS_TO_NORMAL_MODE(void)
{
	GPIO_WritePinOutput(BOARD_INITPINS_CAN_FD_STBY_GPIO, BOARD_INITPINS_CAN_FD_STBY_GPIO_PIN, 0);
}

uint32_t CAN_GetConfigAddr(can_inst_t instance);
void CAN_Init(can_inst_t instance);
int32_t CAN_Transmit(can_inst_t instance, uint32_t id);
void CAN_ReceiveStart(can_inst_t instance);
void CanTransOperationMode(can_inst_t instance, can_trans_opmode_t opmode);
void CanRxCallback_Register(organ_t organ, void * callback);
void CanTxCallback_Register(organ_t organ, void * callback);

#endif /* _CAN_H_ */

