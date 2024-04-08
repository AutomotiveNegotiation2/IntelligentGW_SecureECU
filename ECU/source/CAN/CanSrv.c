#include "pin_mux.h"
#include "Includes.h"

#define	CAN_TASK_10MS_TIME			10
#define	QUEUE_CAN_RX_BUFFER_SIZE	128

can_timer_t CanTimer;

static QUEUE CanRx2MsgQueue;
static queue_can_rx_buf_t CanRx2MsgBuffer[QUEUE_CAN_RX_BUFFER_SIZE];


static void CanTaskStart(void);
static void ApplCan_ScheduleTask(void);
static void CanTransOperationMode(can_inst_t instance, can_trans_opmode_t opmode);
static void CAN_ACC_ON_Init(can_inst_t instance);
static inline uint8_t CanPowerIsEnabled(void);
static void RUN_CAN_UP_ACC_ON(void);
static void RUN_CAN_DN_ACC_OFF(void);

canTransFnCallback CanFnCtrl[CAN_CH_MAX] = {
	{
		.Standby	= NULL,
		.Normal		= NULL,
	},
	{
		.Standby	= CAN1_TRANS_TO_STANDBY_MODE,
		.Normal		= CAN1_TRANS_TO_NORMAL_MODE,
	},
	{
		.Standby	= NULL,
		.Normal		= NULL,
	},
	{
		.Standby	= CAN3_TRANS_TO_STANDBY_MODE,
		.Normal		= CAN3_TRANS_TO_NORMAL_MODE,
	},
};

void CanSrv(void)
{
	if (CanTimer.TaskEn == ON)
	{
		if (CanTimer.SchudleTask >= CAN_TASK_10MS_TIME)
		{
			ApplCan_ScheduleTask();
			CanTimer.SchudleTask -= CAN_TASK_10MS_TIME;
		}
	}
	
	switch(GlobalPocSeq.GSeq)
	{
		case GB_SEQ_UP_ACC_OFF:
			if(GlobalPocSeq.LSeq.B.SEQ_CAN == LO_SEQ_START)
			{
				GlobalPocSeq.LSeq.B.SEQ_CAN = LO_SEQ_FINISH;
			}
			break;

		case GB_SEQ_ACC_OFF:
			break;

		case GB_SEQ_DN_ACC_OFF:
			RUN_CAN_DN_ACC_OFF();
			break;

		case GB_SEQ_UP_ACC_ON:
			RUN_CAN_UP_ACC_ON();
			break;

		case GB_SEQ_ACC_ON:
			break;

		default:
			break;
	}
}

static void RUN_CAN_UP_ACC_ON(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_CAN)
	{
		case LO_SEQ_START:
			/* STANDBY MODE */
			KillSoftTimer(STIMER_CAN3_TX_TEST);
			KillSoftTimer(STIMER_CAN1_TX_TEST);

			BOARD_InitCanPins();
			CanTransOperationMode(CAN_CH_3, CAN_TRANS_OPMODE_STANDBY);
			CanTransOperationMode(CAN_CH_1, CAN_TRANS_OPMODE_STANDBY);

			CAN_ACC_ON_Init(CAN_CH_3);	// CAN
			CAN_ACC_ON_Init(CAN_CH_1);	// CANFD
			
			GlobalPocSeq.LSeq.B.SEQ_CAN = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			if (CanPowerIsEnabled() != TRUE)
			{
				SYSINFO_PRINTF("[%s] Wait until PWR_STS_PERI_PWR_5V_3P3V is enabled ...\r\n", __func__);
				return;
			}
			
			CAN_Init(CAN_CH_3);	// CAN
			CAN_Init(CAN_CH_1);	// CANFD
			
			GlobalPocSeq.LSeq.B.SEQ_CAN = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			CAN_ReceiveStart(CAN_CH_3);	// CAN
			CAN_ReceiveStart(CAN_CH_1);	// CANFD
			CanTransOperationMode(CAN_CH_3, CAN_TRANS_OPMODE_NORMAL);
			CanTransOperationMode(CAN_CH_1, CAN_TRANS_OPMODE_NORMAL);
			
			GlobalPocSeq.LSeq.B.SEQ_CAN = LO_SEQ_03;
			break;

		case LO_SEQ_03:
			ilInit();
			ilStart();
			CanTaskStart();
			//CAN3_TX_Test();
			//CAN1_TX_Test();

			GlobalPocSeq.LSeq.B.SEQ_CAN = LO_SEQ_04;
			break;

		case LO_SEQ_04:
			GlobalPocSeq.LSeq.B.SEQ_CAN = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_CAN = LO_SEQ_START;
			// error
			SYSINFO_PRINTF("[%s] CAN Sequence Error\n", __func__);
			break;
	}
}

static void RUN_CAN_DN_ACC_OFF(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_CAN)
	{
		case LO_SEQ_START:
			GlobalPocSeq.LSeq.B.SEQ_CAN = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			GlobalPocSeq.LSeq.B.SEQ_CAN = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			GlobalPocSeq.LSeq.B.SEQ_CAN = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_CAN = LO_SEQ_START;
			// error
			SYSINFO_PRINTF("[%s] CAN Sequence Error\n", __func__);
			break;
	}
}

static void CAN_ACC_ON_Init(can_inst_t instance)
{
	can_config_t * config;

	if ((instance != CAN_CH_3) && (instance != CAN_CH_1))
	{
		SYSINFO_PRINTF("[%s] CAN Instance Error ...\r\n", __func__);
		assert(0);
	}

	config = (can_config_t *)CAN_GetConfigAddr(instance);

	memset(config->msgTx->stimer_state, CAN_TX_PERI_FUNC_STOP, config->msgTx->NoOfMsg);
	memset(config->msgTx->msgUpdate, MSG_UPDATE_COMPLETE, config->msgTx->NoOfMsg);
}

static void CanTaskStart(void)
{
	CanTimer.SchudleTask = 0;
	CanTimer.TaskEn = ON;
}

uint8_t CanGetTaskEnState(void)
{
	return CanTimer.TaskEn;
}

static inline uint8_t CanPowerIsEnabled(void)
{
	return TRUE;
}

static void CanTransOperationMode(can_inst_t instance, can_trans_opmode_t opmode)
{
	canTransFnCallback * ctrl;

	ctrl = &CanFnCtrl[instance];
	
	switch (opmode)
	{
		case CAN_TRANS_OPMODE_STANDBY:
			ctrl->Standby();
			SYSINFO_PRINTF("[%s] CAN_%d_TRANS_OPMODE_STANDBY Operation ...\r\n", __func__, instance);
			break;

		case CAN_TRANS_OPMODE_NORMAL:
			ctrl->Normal();
			SYSINFO_PRINTF("[%s] CAN_%d_TRANS_OPMODE_NORMAL Operation ...\r\n", __func__, instance);
			break;

		default:
			break;
	}
}

void ApplCan_InitBuf(void)
{
	memset(&CanTimer, 0, sizeof(can_timer_t));
	Queue_InitBuffer(&CanRx2MsgQueue, (void *)CanRx2MsgBuffer, sizeof(queue_can_rx_buf_t), QUEUE_CAN_RX_BUFFER_SIZE);
}

void QueuePushCanDataforRx2(uint8_t inst, uint32_t id, uint8_t dlc, uint8_t * data)
{
	queue_can_rx_buf_t msgbuf;

	memset(&msgbuf, 0, sizeof(queue_can_rx_buf_t));
	
	msgbuf.inst = inst;
	msgbuf.id = id;
	msgbuf.dlc = dlc;
	memcpy(msgbuf.data, data, dlc);

#if 0
	SYSINFO_PRINTF("\r\n[PUSH] CAN_CH=%d ID=0x%x, DLC=%d DATA=", msgbuf.inst, msgbuf.id, msgbuf.dlc);
	for (uint8_t i=0; i<msgbuf.dlc; i++)
	{
		SYSINFO_PRINTF("0x%x ", msgbuf.data[i]);
	}
	SYSINFO_PRINTF("\r\n");
#endif

	Queue_PushBuffer(&CanRx2MsgQueue, (void *)&msgbuf);
}

//void QueuePopCanDataforRx2(QUEUE * queue, queue_can_rx_buf_t * msgbuf)
void QueuePopCanDataforRx2(void)
{
	queue_can_rx_buf_t msgbuf;
	
	if (Queue_PopBuffer(&CanRx2MsgQueue, (void *)&msgbuf) == QUEUE_BUFFER_STS_DONE)
	{
		SYSINFO_PRINTF("\r\n[POP] CAN_CH=%d ID=0x%x, DLC=%d DATA=", msgbuf.inst, msgbuf.id, msgbuf.dlc);
		for (uint8_t i=0; i<msgbuf.dlc; i++)
		{
			SYSINFO_PRINTF("0x%x ", msgbuf.data[i]);
		}
		SYSINFO_PRINTF("\r\n");
	}
}

static void ApplCan_ScheduleTask(void)
{
	ilTxTask();

	Debug_ilRxTask();
}

void ApplCanTx1ECU1_LeftLaneChangeThreat_Sig_Comfirmation(void)
{
	
}

void ApplCanTx1ECU1_SlideBlindZoneAlertTempUnavailableIndiOn_Sig_Comfirmation(void)
{
	
}

void ApplCanTx1ECU1_SlideBlindZoneAlertSystemServiceIndiOn_Sig_Comfirmation(void)
{
	
}

void ApplCanTx1ECU1_SlideBlindZoneAlertSystemOffIndiOn_Sig_Comfirmation(void)
{
	
}

void ApplCanTx1ECU1_SlideBlindZoneAlertSystemCleanIndiOn_Sig_Comfirmation(void)
{
	
}

void ApplCanTx1ECU1_LeftLaneChangeApproachSpeed_Sig_Comfirmation(void)
{

}

void ApplRx2ECU2_VehicleToVehicleWarningDirectionSigIndication(void)
{

}

void ApplRx2ECU2_VehicleToVehicleWarningIndicationRequestSigIndication(void)
{
	
}

void ApplRx1BCS_VehSpdSigIndication(void)
{
}

void ApplRx1BCS_VehSpdVDSigIndication(void)
{
}

void ApplRx2BCS_VehSpdSigIndication(void)
{

}

void ApplRx2BCS_VehSpdVDSigIndication(void)
{
	uint8_t temp;

	temp = IlGetRx2BCS_VehSpdVD();
}

void ApplRx3BCS_VehSpdSigIndication(void)
{
}

void ApplRx3BCS_VehSpdVDSigIndication(void)
{
}

void ApplRx4BCS_VehSpdSigIndication(void)
{
}

void ApplRx4BCS_VehSpdVDSigIndication(void)
{
}

void ApplRx1BCAN_1_ReverseSwitchStSigIndication(void)
{
}

void ApplRx1BCAN_1_ParkingLampStSigIndication(void)
{
}

void ApplRx2BCAN_1_ReverseSwitchStSigIndication(void)
{
}

void ApplRx2BCAN_1_ParkingLampStSigIndication(void)
{
}

void ApplRx3BCAN_1_ReverseSwitchStSigIndication(void)
{
}

void ApplRx3BCAN_1_ParkingLampStSigIndication(void)
{
}

void ApplRx4BCAN_1_ReverseSwitchStSigIndication(void)
{
}

void ApplRx4BCAN_1_ParkingLampStSigIndication(void)
{
}

void ApplRx1ICM_HandBrakeStSigIndication(void)
{
}

void ApplRx1ICM_HandBrakeVDSigIndication(void)
{
}

void ApplRx1ICM_BackLightLevelSigIndication(void)
{
}

void ApplRx2ICM_HandBrakeStSigIndication(void)
{
}

void ApplRx2ICM_HandBrakeVDSigIndication(void)
{
}

void ApplRx2ICM_BackLightLevelSigIndication(void)
{
}

void ApplRx3ICM_HandBrakeStSigIndication(void)
{
}

void ApplRx3ICM_HandBrakeVDSigIndication(void)
{
}

void ApplRx3ICM_BackLightLevelSigIndication(void)
{
}

void ApplRx4ICM_HandBrakeStSigIndication(void)
{
}

void ApplRx4ICM_HandBrakeVDSigIndication(void)
{
}

void ApplRx4ICM_BackLightLevelSigIndication(void)
{
}

void ApplRx1ICM_ModuleSigIndication(void)
{
}

void ApplRx1HVAC_ModuleSigIndication(void)
{
}

void ApplRx1ACU_NACU_ModuleSigIndication(void)
{
}

void ApplRx1TPMS_ModuleSigIndication(void)
{
}

void ApplRx1SAM_ModuleSigIndication(void)
{
}

void ApplRx1BCM_ModuleSigIndication(void)
{
}

void ApplRx1EMS_ModuleSigIndication(void)
{
}

void ApplRx1TCU_ModuleSigIndication(void)
{
}

void ApplRx1SRS_ModuleSigIndication(void)
{
}

void ApplRx1BCS_ModuleSigIndication(void)
{
}

void ApplRx1EPS_ModuleSigIndication(void)
{
}

void ApplRx1ALS_ModuleSigIndication(void)
{
}

void ApplRx1SAS_ModuleSigIndication(void)
{
}

void ApplRx2ICM_ModuleSigIndication(void)
{
}

void ApplRx2HVAC_ModuleSigIndication(void)
{
}

void ApplRx2ACU_NACU_ModuleSigIndication(void)
{
}

void ApplRx2TPMS_ModuleSigIndication(void)
{
}

void ApplRx2SAM_ModuleSigIndication(void)
{
}

void ApplRx2BCM_ModuleSigIndication(void)
{
}

void ApplRx2EMS_ModuleSigIndication(void)
{
}

void ApplRx2TCU_ModuleSigIndication(void)
{
}

void ApplRx2SRS_ModuleSigIndication(void)
{
}

void ApplRx2BCS_ModuleSigIndication(void)
{
}

void ApplRx2EPS_ModuleSigIndication(void)
{
}

void ApplRx2ALS_ModuleSigIndication(void)
{
}

void ApplRx2SAS_ModuleSigIndication(void)
{
}

void ApplRx3ICM_ModuleSigIndication(void)
{
}

void ApplRx3HVAC_ModuleSigIndication(void)
{
}

void ApplRx3ACU_NACU_ModuleSigIndication(void)
{
}

void ApplRx3TPMS_ModuleSigIndication(void)
{
}

void ApplRx3SAM_ModuleSigIndication(void)
{
}

void ApplRx3BCM_ModuleSigIndication(void)
{
}

void ApplRx3EMS_ModuleSigIndication(void)
{
}

void ApplRx3TCU_ModuleSigIndication(void)
{
}

void ApplRx3SRS_ModuleSigIndication(void)
{
}

void ApplRx3BCS_ModuleSigIndication(void)
{
}

void ApplRx3EPS_ModuleSigIndication(void)
{
}

void ApplRx3ALS_ModuleSigIndication(void)
{
}

void ApplRx3SAS_ModuleSigIndication(void)
{
}

void ApplRx4ICM_ModuleSigIndication(void)
{
}

void ApplRx4HVAC_ModuleSigIndication(void)
{
}

void ApplRx4ACU_NACU_ModuleSigIndication(void)
{
}

void ApplRx4TPMS_ModuleSigIndication(void)
{
}

void ApplRx4SAM_ModuleSigIndication(void)
{
}

void ApplRx4BCM_ModuleSigIndication(void)
{
}

void ApplRx4EMS_ModuleSigIndication(void)
{
}

void ApplRx4TCU_ModuleSigIndication(void)
{
}

void ApplRx4SRS_ModuleSigIndication(void)
{
}

void ApplRx4BCS_ModuleSigIndication(void)
{
}

void ApplRx4EPS_ModuleSigIndication(void)
{
}

void ApplRx4ALS_ModuleSigIndication(void)
{
}

void ApplRx4SAS_ModuleSigIndication(void)
{
}

void ApplTxECU1_Blind_Zone_Alert_Status_TxComfirmation(void)
{
	uint8_t sig;

	if (IlGetECU1_SlideBlindZoneAlertSystemCleanIndiOn_Sig() == ON)
	{
		sig = OFF;
	}
	else
	{
		sig = ON;
	}
	
	IlSetECU1_SlideBlindZoneAlertSystemCleanIndiOn_Sig(&sig);
}

