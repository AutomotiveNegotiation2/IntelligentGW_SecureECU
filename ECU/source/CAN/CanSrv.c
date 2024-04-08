#include "pin_mux.h"
#include "Includes.h"

#define	CAN_TASK_10MS_TIME			10
#define	QUEUE_CAN_RX_BUFFER_SIZE	128

#if (DEBUG_CAN == ON)
#define	CANAPP_DEBUG 	OFF
#endif

#if (CANAPP_DEBUG == ON)
#define	CANAPPINFO_PRINTF	PRINTF
#else 
#define	CANAPPINFO_PRINTF
#endif


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
				CANINFO_PRINTF("[%s] Wait until PWR_STS_PERI_PWR_5V_3P3V is enabled ...\r\n", __func__);
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
			CANINFO_PRINTF("[%s] CAN Sequence Error\n", __func__);
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
			CANINFO_PRINTF("[%s] CAN Sequence Error\n", __func__);
			break;
	}
}

static void CAN_ACC_ON_Init(can_inst_t instance)
{
	can_config_t * config;

	if ((instance != CAN_CH_3) && (instance != CAN_CH_1))
	{
		CANINFO_PRINTF("[%s] CAN Instance Error ...\r\n", __func__);
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
			CANINFO_PRINTF("[%s] CAN_%d_TRANS_OPMODE_STANDBY Operation ...\r\n", __func__, instance);
			break;

		case CAN_TRANS_OPMODE_NORMAL:
			ctrl->Normal();
			CANINFO_PRINTF("[%s] CAN_%d_TRANS_OPMODE_NORMAL Operation ...\r\n", __func__, instance);
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
	CANINFO_PRINTF("\r\n[PUSH] CAN_CH=%d ID=0x%x, DLC=%d DATA=", msgbuf.inst, msgbuf.id, msgbuf.dlc);
	for (uint8_t i=0; i<msgbuf.dlc; i++)
	{
		CANINFO_PRINTF("0x%x ", msgbuf.data[i]);
	}
	CANINFO_PRINTF("\r\n");
#endif

	Queue_PushBuffer(&CanRx2MsgQueue, (void *)&msgbuf);
}

//void QueuePopCanDataforRx2(QUEUE * queue, queue_can_rx_buf_t * msgbuf)
void QueuePopCanDataforRx2(void)
{
	queue_can_rx_buf_t msgbuf;
	char buf[10]={0, };
	
	if (Queue_PopBuffer(&CanRx2MsgQueue, (void *)&msgbuf) == QUEUE_BUFFER_STS_DONE)
	{
		if (msgbuf.inst == CAN_CH_3)
		{
			sprintf(buf, "CAN");
		}
		else if (msgbuf.inst == CAN_CH_1)
		{
			sprintf(buf, "CANFD");
		}

		CANINFO_PRINTF("[RX] %05s ID=0x%X, DLC=%d DATA=", buf, msgbuf.id, msgbuf.dlc);
		for (uint8_t i=0; i<msgbuf.dlc; i++)
		{
			CANINFO_PRINTF("0x%x ", msgbuf.data[i]);
		}
		CANINFO_PRINTF("\r\n");
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

void ApplRxECU1_VehicleToVehicleWarningDirectionSigIndication(void)
{
	uint8_t temp;

	temp = IlGetRxECU1_VehicleToVehicleWarningDirectionSig();

	CANAPPINFO_PRINTF("[ROUTED V2V Warning] VehicleToVehicleWarningDirectionSig = 0x%x\r\n", temp);
}

void ApplRxECU1_VehicleToVehicleWarningIndicationRequestSigIndication(void)
{
	uint8_t temp;
	
	temp = IlGetRxECU1_VehicleToVehicleWarningIndicationRequestSig();	

	CANAPPINFO_PRINTF("[ROUTED V2V Warning] VehicleToVehicleWarningIndicationRequestSig = 0x%x\r\n", temp);
}

void ApplRxECU1_PedestrianFriendlyAlertSoundGenerationEnableSigIndication(void)
{
	uint8_t temp;
	
	temp = IlGetRxECU1_PedestrianFriendlyAlertSoundGenerationEnableSig();
	
	CANAPPINFO_PRINTF("[ROUTED Pedestrain Friendly Alert Status] PedestrianFriendlyAlertSoundGenerationEnableSig = 0x%x\r\n", temp);
}

void ApplRxECU1_PedestrianFriendlyAlertForwardSoundSigIndication(void)
{
	uint8_t temp;
	
	temp = IlGetRxECU1_PedestrianFriendlyAlertForwardSoundSig();
	
	CANAPPINFO_PRINTF("[ROUTED Pedestrain Friendly Alert Status] PedestrianFriendlyAlertForwardSoundSig = 0x%x\r\n", temp);
}

void ApplRxECU1_PedestrianFriendlyAlertReverseSoundSigIndication(void)
{
	uint8_t temp;
	
	temp = IlGetRxECU1_PedestrianFriendlyAlertReverseSoundSig();
	
	CANAPPINFO_PRINTF("[ROUTED Pedestrain Friendly Alert Status] PedestrianFriendlyAlertReverseSoundSig = 0x%x\r\n", temp);
}

void ApplRxECU1_PedestrianFriendlyAlertCrossoverSpeedSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU1_PedestrianFriendlyAlertCrossoverSpeedSig();
		
	CANAPPINFO_PRINTF("[ROUTED Pedestrain Friendly Alert Status] PedestrianFriendlyAlertCrossoverSpeedSig = 0x%x\r\n", temp);
}

void ApplRxECU1_PedestrianFriendlyAlertSystemStatusSigIndication()
{
	uint8_t temp;
		
	temp = IlGetRxECU1_PedestrianFriendlyAlertSystemStatusSig();
		
	CANAPPINFO_PRINTF("[ROUTED Pedestrain Friendly Alert Status] PedestrianFriendlyAlertSystemStatusSig = 0x%x\r\n", temp);
}

void ApplRxECU1_DrowsinessLevelSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU1_DrowsinessLevelSig();
		
	CANAPPINFO_PRINTF("[ROUTED Drive Status] DrowsinessLevelSig = 0x%x\r\n", temp);
}

void ApplRxECU1_DistractionLevelSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU1_DistractionLevelSig();
		
	CANAPPINFO_PRINTF("[ROUTED Drive Status] DistractionLevelSig = 0x%x\r\n", temp);
}

void ApplRxECU1_HandsOnLevelSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU1_HandsOnLevelSig();
		
	CANAPPINFO_PRINTF("[ROUTED Drive Status] HandsOnLevelSig = 0x%x\r\n", temp);
}

void ApplRxECU1_ClockYearSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU1_ClockYearSig();
		
	CANAPPINFO_PRINTF("[ROUTED Clock] ClockYearSig = 0x%x\r\n", temp);
}

void ApplRxECU1_ClockMonthSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU1_ClockMonthSig();
		
	CANAPPINFO_PRINTF("[ROUTED Clock] ClockMonthSig = 0x%x\r\n", temp);
}

void ApplRxECU1_ClockDaySigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU1_ClockDaySig();
		
	CANAPPINFO_PRINTF("[ROUTED Clock] ClockDaySig = 0x%x\r\n", temp);
}

void ApplRxECU1_ClockHourSigIndication()
{
	uint8_t temp;
		
	temp = IlGetRxECU1_ClockHourSig();
		
	CANAPPINFO_PRINTF("[ROUTED Clock] ClockHourSig = 0x%x\r\n", temp);
}

void ApplRxECU1_ClockMinuteSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU1_ClockMinuteSig();
		
	CANAPPINFO_PRINTF("[ROUTED Clock] ClockMInuteSig = 0x%x\r\n", temp);
}

void ApplRxECU1_ClockSecondSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU1_ClockSecondSig();
		
	CANAPPINFO_PRINTF("[ROUTED Clock] ClockSecondSig = 0x%x\r\n", temp);
}

void ApplRxECU2_SystemPowerModeValiditySigIndication(void)
{
	uint8_t temp;
		
	temp = (uint8_t)IlGetRxECU2_SystemPowerModeValiditySig();
		
	CANAPPINFO_PRINTF("[ROUTED System Power Mode] SystemPowerModeValiditySig = 0x%x\r\n", temp);
}

void ApplRxECU2_SystemPowerModeSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU2_SystemPowerModeSig();
		
	CANAPPINFO_PRINTF("[ROUTED System Power Mode] SystemPowerModeSig = 0x%x\r\n", temp);
}

void ApplRxECU2_LeftLaneChangeThreatSigIndication(void)
{
	uint8_t temp;
		
	temp = (uint8_t) IlGetRxECU2_LeftLaneChangeThreatSig();
		
	CANAPPINFO_PRINTF("[ROUTED Blind_Zone_Alert_Status] LeftLaneChangeThreatSig = 0x%x\r\n", temp);
}

void ApplRxECU2_SlideBlindZoneAlertTempUnavailableIndiOnSigIndication(void)
{
	uint8_t temp;
		
	temp = (uint8_t) IlGetRxECU2_SlideBlindZoneAlertTempUnavailableIndiOnSig();
		
	CANAPPINFO_PRINTF("[ROUTED Blind_Zone_Alert_Status] SlideBlindZoneAlertTempUnavailableIndiOnSig = 0x%x\r\n", temp);
}

void ApplRxECU2_SlideBlindZoneAlertSystemServiceIndiOnSigIndication(void)
{
	uint8_t temp;
		
	temp = (uint8_t) IlGetRxECU2_SlideBlindZoneAlertSystemServiceIndiOnSig();
		
	CANAPPINFO_PRINTF("[ROUTED Blind_Zone_Alert_Status] SlideBlindZoneAlertSystemServiceIndiOnSig = 0x%x\r\n", temp);
}

void ApplRxECU2_SlideBlindZoneAlertSystemOffIndiOnSigIndication(void)
{
	uint8_t temp;
		
	temp = (uint8_t) IlGetRxECU2_SlideBlindZoneAlertSystemOffIndiOnSig();
		
	CANAPPINFO_PRINTF("[ROUTED Blind_Zone_Alert_Status] SlideBlindZoneAlertSystemOffIndiOnSig = 0x%x\r\n", temp);
}

void ApplRxECU2_SlideBlindZoneAlertSystemCleanIndiOnSigIndication(void)
{
	uint8_t temp;
		
	temp = (uint8_t) IlGetRxECU2_SlideBlindZoneAlertSystemCleanIndiOnSig();
		
	CANAPPINFO_PRINTF("[ROUTED Blind_Zone_Alert_Status] SlideBlindZoneAlertSystemCleanIndiOnSig = 0x%x\r\n", temp);
}

void ApplRxECU2_LeftLaneChangeApproachSpeedSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU2_LeftLaneChangeApproachSpeedSig();
		
	CANAPPINFO_PRINTF("[ROUTED Blind_Zone_Alert_Status] LeftLaneChangeApproachSpeedSig = 0x%x\r\n", temp);
}

void ApplRxECU2_DrowsinessLevelSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU2_DrowsinessLevelSig();
		
	CANAPPINFO_PRINTF("[ROUTED Drive Status] DrowsinessLevelSig = 0x%x\r\n", temp);
}

void ApplRxECU2_DistractionLevelSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU2_DistractionLevelSig();
		
	CANAPPINFO_PRINTF("[ROUTED Drive Status] DistractionLevelSig = 0x%x\r\n", temp);
}

void ApplRxECU2_HandsOnLevelSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU2_HandsOnLevelSig();
		
	CANAPPINFO_PRINTF("[ROUTED Drive Status] HandsOnLevelSig = 0x%x\r\n", temp);
}

void ApplRxECU2_PedestrianFriendlyAlertSoundGenerationEnableSigIndication(void)
{
	uint8_t temp;
	
	temp = IlGetRxECU2_PedestrianFriendlyAlertSoundGenerationEnableSig();
	
	CANAPPINFO_PRINTF("[ROUTED Pedestrain Friendly Alert Status] PedestrianFriendlyAlertSoundGenerationEnableSig = 0x%x\r\n", temp);
}

void ApplRxECU2_PedestrianFriendlyAlertForwardSoundSigIndication(void)
{
	uint8_t temp;
	
	temp = IlGetRxECU2_PedestrianFriendlyAlertForwardSoundSig();
	
	CANAPPINFO_PRINTF("[ROUTED Pedestrain Friendly Alert Status] PedestrianFriendlyAlertForwardSoundSig = 0x%x\r\n", temp);
}

void ApplRxECU2_PedestrianFriendlyAlertReverseSoundSigIndication(void)
{
	uint8_t temp;
	
	temp = IlGetRxECU2_PedestrianFriendlyAlertReverseSoundSig();
	
	CANAPPINFO_PRINTF("[ROUTED Pedestrain Friendly Alert Status] PedestrianFriendlyAlertReverseSoundSig = 0x%x\r\n", temp);
}

void ApplRxECU2_PedestrianFriendlyAlertCrossoverSpeedSigIndication(void)
{
	uint8_t temp;
		
	temp = IlGetRxECU2_PedestrianFriendlyAlertCrossoverSpeedSig();
		
	CANAPPINFO_PRINTF("[ROUTED Pedestrain Friendly Alert Status] PedestrianFriendlyAlertCrossoverSpeedSig = 0x%x\r\n", temp);
}

void ApplRxECU2_PedestrianFriendlyAlertSystemStatusSigIndication()
{
	uint8_t temp;
		
	temp = IlGetRxECU2_PedestrianFriendlyAlertSystemStatusSig();
		
	CANAPPINFO_PRINTF("[ROUTED Pedestrain Friendly Alert Status] PedestrianFriendlyAlertSystemStatusSig = 0x%x\r\n", temp);
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

	if (IlGetECU1_SlideBlindZoneAlertSystemCleanIndiOnSig() == ON)
	{
		sig = OFF;
	}
	else
	{
		sig = ON;
	}
	
	IlSetECU1_SlideBlindZoneAlertSystemCleanIndiOnSig(&sig);
}

void ApplTxECU1_SystemPowerMode_TxComfirmation(void)
{
	uint8_t sig;

	if (IlGetECU1_SystemPowerModeValiditySig() == INVALID)
	{
		sig = VALID;
		IlSetECU1_SystemPowerModeValiditySig(&sig);
	}

	sig = IlGetECU1_SystemPowerModeSig();

	if (sig < CRANK_REQUEST)
	{
		sig++;
	}
	else
	{
		sig = KEY_OFF;
	}
	
	IlSetECU1_SystemPowerModeSig(&sig);
}

void ApplTxECU2_V2V_Warning_TxComfirmation(void)
{
	uint8_t sig;

	sig = IlGetECU2_VehicleToVehicleWarningDirectionSig();
	if (++sig < 0x08)
	{
		IlSetECU2_VehicleToVehicleWarningDirectionSig(&sig);
	}
	else
	{
		sig = 0;
		IlSetECU2_VehicleToVehicleWarningDirectionSig(&sig);
	}

	sig = IlGetECU2_VehicleToVehicleWarningIndicationRequestSig();
	if (++sig < 0x11)
	{
		IlSetECU2_VehicleToVehicleWarningIndicationRequestSig(&sig);
	}
	else
	{
		sig = 0;
		IlSetECU2_VehicleToVehicleWarningIndicationRequestSig(&sig);
	}
}

