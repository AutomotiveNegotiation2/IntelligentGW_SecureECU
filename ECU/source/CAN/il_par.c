#include "Includes.h"

void CAN_SetTxFlagForMsgUpdate(can_inst_t canChannel, uint32_t msgId);
void ilMsg_Register_Callback_Fn(can_inst_t instance, uint32_t id);

static void ilMsgECU2_Clock_Tx_Send(void);
static void ilMsgECU2_V2V_Warning_Send(void);

static void ilMsgECU1_System_Power_Mode_Tx_Send(void);
static void	ilMsgECU1_Blind_Zone_Alert_Status_Tx_Send(void);

void ilMsgNACU_Diag_Tx1_Send(void);
void ilMsgNACU_Diag_Tx2_Send(void);
void ilMsgNACU_Diag_Tx3_Send(void);
void ilMsgNACU_Diag_Tx4_Send(void);
void ilMsgNACU_Diag_Tx5_Send(void);

void ilMsg_Register_Callback_Fn(can_inst_t instance, uint32_t id)
{
	uint8_t i;
	can_config_t * config;

	config = (can_config_t *)CAN_GetConfigAddr(instance);

	for (i=0; i<config->msgTx->NoOfMsg; i++)
	{
		if (id == config->msgTx->id[i])
		{
			break;
		}
	}

	if (i >= config->msgTx->NoOfMsg)
	{
		SYSINFO_PRINTF("[%s] CAN ID[0x%X] is not matched.\n", __func__, id);
		assert(0);
	}
	
	if (config->msgTx->attr[i] == CAN_TX_ATTR_PERIODIC)
	{
		ClearSoftTimerCounter(config->msgTx->stimerId[i]);
		if (config->msgTx->stimer_state[i] == CAN_TX_PERI_FUNC_STOP)
		{
			SetSoftTimer(config->msgTx->stimerId[i], config->msgTx->attrtime[i], config->msgTx->tCallback[i]);
			config->msgTx->stimer_state[i] = CAN_TX_PERI_FUNC_START;
		}
	}
}

/*******************************************************************************
	CAN 1 Transmit message
 *******************************************************************************/
FuncCanTxCallback CanTxFuncList1[CAN1_NO_OF_TX_OBJECT] =
{
	ilMsgECU2_Clock_Tx_Send,
	ilMsgECU2_V2V_Warning_Send,
	ilMsgNACU_Diag_Tx3_Send,
	ilMsgNACU_Diag_Tx4_Send,
	ilMsgNACU_Diag_Tx5_Send
};

void ilMsgNACU_Diag_Tx1_Send(void)
{
	/*NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_0 = 0x01;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_1 = 0x02;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_2 = 0x03;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_3 = 0x04;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_4 = 0x05;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_5 = 0x06;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_6 = 0x07;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_7 = 0x08;*/

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[0]);
}

void ilMsgNACU_Diag_Tx2_Send(void)
{
	/*NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_0 = 0x01;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_1 = 0x02;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_2 = 0x03;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_3 = 0x04;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_4 = 0x05;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_5 = 0x06;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_6 = 0x07;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_7 = 0x08;*/

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[1]);
}

void ilMsgNACU_Diag_Tx3_Send(void)
{
	/*NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_0 = 0x01;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_1 = 0x02;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_2 = 0x03;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_3 = 0x04;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_4 = 0x05;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_5 = 0x06;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_6 = 0x07;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_7 = 0x08;*/

	CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[2]);
}

void ilMsgNACU_Diag_Tx4_Send(void)
{
	/*NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_0 = 0x01;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_1 = 0x02;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_2 = 0x03;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_3 = 0x04;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_4 = 0x05;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_5 = 0x06;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_6 = 0x07;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_7 = 0x08;*/

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[3]);
}

void ilMsgNACU_Diag_Tx5_Send(void)
{
	/*NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_0 = 0x01;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_1 = 0x02;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_2 = 0x03;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_3 = 0x04;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_4 = 0x05;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_5 = 0x06;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_6 = 0x07;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_7 = 0x08;*/

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[4]);
}

void ApplCanMsg_NACU_Diag_Tx1_Get(uint8_t * data)
{
	
}

void ApplCanMsg_NACU_Diag_Tx1_Set(uint8_t * data)
{
	
}

/*******************************************************************************
	CAN 1 Receive message
 *******************************************************************************/

FuncCanRxCallback CanRxFuncList1[CAN1_NO_OF_RX_OBJECT] =
{
	IlMsgECU2_ROUTED_System_Power_Mode_Rx0Indication,
	IlMsgECU2_ROUTED_Blind_Zone_Alert_Status_Rx1Indication,
	IlMsgECU2_ROUTED_Drive_Status_Rx2Indication,
	IlMsgECU2_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3Indication,
	IlMsgBCM_BCAN_1_Rx1Indication,
	IlMsgBCM_BCAN_1_Rx2Indication,
	IlMsgBCM_BCAN_1_Rx3Indication,
	IlMsgBCM_BCAN_1_Rx4Indication,
	IlMsgICM_1_Rx1Indication,
	IlMsgICM_1_Rx2Indication,
	IlMsgICM_1_Rx3Indication,
	IlMsgICM_1_Rx4Indication,
	IlMsgBCM_BCAN_2_Rx1Indication,
	IlMsgBCM_BCAN_2_Rx2Indication,
	IlMsgBCM_BCAN_2_Rx3Indication,
	IlMsgBCM_BCAN_2_Rx4Indication,
};

void IlMsgBCM_TCU_BCS_Rx1Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx1BCS_VehSpdSigIndication();
	ApplRx1BCS_VehSpdVDSigIndication();
}

void IlMsgBCM_TCU_BCS_Rx2Indication(uint8_t * data, uint8_t dlc)
{
	uint8_t buf[8];

	memcpy(buf, data, dlc);
	
	ApplRx2BCS_VehSpdSigIndication();
	ApplRx2BCS_VehSpdVDSigIndication();
}

void IlMsgBCM_TCU_BCS_Rx3Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx3BCS_VehSpdSigIndication();
	ApplRx3BCS_VehSpdVDSigIndication();
}

void IlMsgBCM_TCU_BCS_Rx4Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx4BCS_VehSpdSigIndication();
	ApplRx4BCS_VehSpdVDSigIndication();
}

void IlMsgBCM_BCAN_1_Rx1Indication(uint8_t * data, uint8_t dlc)
{
	uint8_t buf[8];

	memcpy(buf, data, dlc);
	
	ApplRx1BCAN_1_ReverseSwitchStSigIndication();
	ApplRx1BCAN_1_ParkingLampStSigIndication();
}

void IlMsgBCM_BCAN_1_Rx2Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx2BCAN_1_ReverseSwitchStSigIndication();
	ApplRx2BCAN_1_ParkingLampStSigIndication();
}

void IlMsgBCM_BCAN_1_Rx3Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx3BCAN_1_ReverseSwitchStSigIndication();
	ApplRx3BCAN_1_ParkingLampStSigIndication();
}

void IlMsgBCM_BCAN_1_Rx4Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx4BCAN_1_ReverseSwitchStSigIndication();
	ApplRx4BCAN_1_ParkingLampStSigIndication();
}

void IlMsgICM_1_Rx1Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx1ICM_HandBrakeStSigIndication();
	ApplRx1ICM_HandBrakeVDSigIndication();
	ApplRx1ICM_BackLightLevelSigIndication();
}

void IlMsgICM_1_Rx2Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx2ICM_HandBrakeStSigIndication();
	ApplRx2ICM_HandBrakeVDSigIndication();
	ApplRx2ICM_BackLightLevelSigIndication();
}

void IlMsgICM_1_Rx3Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx3ICM_HandBrakeStSigIndication();
	ApplRx3ICM_HandBrakeVDSigIndication();
	ApplRx3ICM_BackLightLevelSigIndication();
}

void IlMsgICM_1_Rx4Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx4ICM_HandBrakeStSigIndication();
	ApplRx4ICM_HandBrakeVDSigIndication();
	ApplRx4ICM_BackLightLevelSigIndication();
}

void IlMsgBCM_BCAN_2_Rx1Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx1ICM_ModuleSigIndication();
	ApplRx1HVAC_ModuleSigIndication();
	ApplRx1ACU_NACU_ModuleSigIndication();
	ApplRx1TPMS_ModuleSigIndication();
	ApplRx1SAM_ModuleSigIndication();
	ApplRx1BCM_ModuleSigIndication();
	ApplRx1EMS_ModuleSigIndication();
	ApplRx1TCU_ModuleSigIndication();
	ApplRx1SRS_ModuleSigIndication();
	ApplRx1BCS_ModuleSigIndication();
	ApplRx1EPS_ModuleSigIndication();
	ApplRx1ALS_ModuleSigIndication();
	ApplRx1SAS_ModuleSigIndication();
}

void IlMsgBCM_BCAN_2_Rx2Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx2ICM_ModuleSigIndication();
	ApplRx2HVAC_ModuleSigIndication();
	ApplRx2ACU_NACU_ModuleSigIndication();
	ApplRx2TPMS_ModuleSigIndication();
	ApplRx2SAM_ModuleSigIndication();
	ApplRx2BCM_ModuleSigIndication();
	ApplRx2EMS_ModuleSigIndication();
	ApplRx2TCU_ModuleSigIndication();
	ApplRx2SRS_ModuleSigIndication();
	ApplRx2BCS_ModuleSigIndication();
	ApplRx2EPS_ModuleSigIndication();
	ApplRx2ALS_ModuleSigIndication();
	ApplRx2SAS_ModuleSigIndication();
}

void IlMsgBCM_BCAN_2_Rx3Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx3ICM_ModuleSigIndication();
	ApplRx3HVAC_ModuleSigIndication();
	ApplRx3ACU_NACU_ModuleSigIndication();
	ApplRx3TPMS_ModuleSigIndication();
	ApplRx3SAM_ModuleSigIndication();
	ApplRx3BCM_ModuleSigIndication();
	ApplRx3EMS_ModuleSigIndication();
	ApplRx3TCU_ModuleSigIndication();
	ApplRx3SRS_ModuleSigIndication();
	ApplRx3BCS_ModuleSigIndication();
	ApplRx3EPS_ModuleSigIndication();
	ApplRx3ALS_ModuleSigIndication();
	ApplRx3SAS_ModuleSigIndication();
}

void IlMsgBCM_BCAN_2_Rx4Indication(uint8_t * data, uint8_t dlc)
{
	ApplRx4ICM_ModuleSigIndication();
	ApplRx4HVAC_ModuleSigIndication();
	ApplRx4ACU_NACU_ModuleSigIndication();
	ApplRx4TPMS_ModuleSigIndication();
	ApplRx4SAM_ModuleSigIndication();
	ApplRx4BCM_ModuleSigIndication();
	ApplRx4EMS_ModuleSigIndication();
	ApplRx4TCU_ModuleSigIndication();
	ApplRx4SRS_ModuleSigIndication();
	ApplRx4BCS_ModuleSigIndication();
	ApplRx4EPS_ModuleSigIndication();
	ApplRx4ALS_ModuleSigIndication();
	ApplRx4SAS_ModuleSigIndication();
}

bool IlGetRx1BCS_VehSpdVD(void)
{
	return NACU_BCM_TCU_BCS_Rx1.BCM_TCU_BCS.BCS_VehSpdVD;
}

uint16_t IlGetRx1BCS_VehSpd(void)
{
	uint16_t rc;

	rc = (uint16_t)NACU_BCM_TCU_BCS_Rx1.BCM_TCU_BCS.BCS_VehSpd_0;
	rc |= (uint16_t)NACU_BCM_TCU_BCS_Rx1.BCM_TCU_BCS.BCS_VehSpd_1 << 8;

	return rc;
}

bool IlGetRx2BCS_VehSpdVD(void)
{
	return NACU_BCM_TCU_BCS_Rx2.BCM_TCU_BCS.BCS_VehSpdVD;
}

uint16_t IlGetRx2BCS_VehSpd(void)
{
	uint16_t rc;

	rc = (uint16_t)NACU_BCM_TCU_BCS_Rx2.BCM_TCU_BCS.BCS_VehSpd_0;
	rc |= (uint16_t)NACU_BCM_TCU_BCS_Rx2.BCM_TCU_BCS.BCS_VehSpd_1 << 8;

	return rc;
}

bool IlGetRx3BCS_VehSpdVD(void)
{
	return NACU_BCM_TCU_BCS_Rx3.BCM_TCU_BCS.BCS_VehSpdVD;
}

uint16_t IlGetRx3BCS_VehSpd(void)
{
	uint16_t rc;

	rc = (uint16_t)NACU_BCM_TCU_BCS_Rx3.BCM_TCU_BCS.BCS_VehSpd_0;
	rc |= (uint16_t)NACU_BCM_TCU_BCS_Rx3.BCM_TCU_BCS.BCS_VehSpd_1 << 8;

	return rc;
}

bool IlGetRx4BCS_VehSpdVD(void)
{
	return NACU_BCM_TCU_BCS_Rx4.BCM_TCU_BCS.BCS_VehSpdVD;
}

uint16_t IlGetRx4BCS_VehSpd(void)
{
	uint16_t rc;

	rc = (uint16_t)NACU_BCM_TCU_BCS_Rx4.BCM_TCU_BCS.BCS_VehSpd_0;
	rc |= (uint16_t)NACU_BCM_TCU_BCS_Rx4.BCM_TCU_BCS.BCS_VehSpd_1 << 8;

	return rc;
}

/*******************************************************************************
	CAN 3 Transmit message
 *******************************************************************************/
void ilMsgNACU2_Diag_Tx1_Send(void)
{
	/*NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_0 = 0x01;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_1 = 0x02;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_2 = 0x03;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_3 = 0x04;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_4 = 0x05;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_5 = 0x06;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_6 = 0x07;
	NACU_Diag_Tx1.NACU_Diag_Tx.NACU_Diag_Response_7 = 0x08;*/

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[0]);
}

void ilMsgNACU2_Diag_Tx2_Send(void)
{
	/*NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_0 = 0x01;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_1 = 0x02;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_2 = 0x03;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_3 = 0x04;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_4 = 0x05;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_5 = 0x06;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_6 = 0x07;
	NACU_Diag_Tx2.NACU_Diag_Tx.NACU_Diag_Response_7 = 0x08;*/

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

void CAN_SetTxFlagForMsgUpdate(can_inst_t canChannel, uint32_t msgId)
{
	uint8_t i;
	can_config_t * config;

	config = (can_config_t *) CAN_GetConfigAddr(canChannel);

	for (i=0; i<config->msgTx->NoOfMsg; i++)
	{
		if (msgId == config->msgTx->id[i])
		{
			config->msgTx->msgUpdate[i] = MSG_UPDATE_REQUEST;
			break;
		}
	}
}

uint8_t IlGetECU2_Clock_YearSig(void)
{
	return ECU2_Clock_Tx0.Clock.Year;
}

void IlSetECU2_Clock_YearSig(uint8_t * msgdata)
{
	ECU2_Clock_Tx0.Clock.Year = msgdata[0];

	// CANFD Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[0]);
}

uint8_t IlGetECU2_Clock_MonthSig(void)
{
	return ECU2_Clock_Tx0.Clock.Month;
}

void IlSetECU2_Clock_MonthSig(uint8_t * msgdata)
{
	ECU2_Clock_Tx0.Clock.Month = msgdata[0];

	// CANFD Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[0]);
}

uint8_t IlGetECU2_Clock_DaySig(void)
{
	return ECU2_Clock_Tx0.Clock.Day;
}

void IlSetECU2_Clock_DaySig(uint8_t * msgdata)
{
	ECU2_Clock_Tx0.Clock.Day = msgdata[0];

	// CANFD Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[0]);
}

uint8_t IlGetECU2_Clock_HourSig(void)
{
	return ECU2_Clock_Tx0.Clock.Hour;
}

void IlSetECU2_Clock_HourSig(uint8_t * msgdata)
{
	ECU2_Clock_Tx0.Clock.Hour = msgdata[0];

	// CANFD Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[0]);
}

uint8_t IlGetECU2_Clock_MinuteSig(void)
{
	return ECU2_Clock_Tx0.Clock.Minute;
}

void IlSetECU2_Clock_MinuteSig(uint8_t * msgdata)
{
	ECU2_Clock_Tx0.Clock.Minute = msgdata[0];

	// CANFD Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[0]);
}

uint8_t IlGetECU2_Clock_SecondSig(void)
{
	return ECU2_Clock_Tx0.Clock.Second;
}

void IlSetECU2_Clock_SecondSig(uint8_t * msgdata)
{
	ECU2_Clock_Tx0.Clock.Second = msgdata[0];

	// CANFD Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[0]);
}

static void ilMsgECU2_Clock_Tx_Send(void)
{
	uint8_t data;
	
	// for initial value
	data = 0x23;
	IlSetECU2_Clock_YearSig(&data);
	data = 0x08;
	IlSetECU2_Clock_MonthSig(&data);
	data = 0x17;
	IlSetECU2_Clock_DaySig(&data);

	data = 0x09;
	IlSetECU2_Clock_HourSig(&data);
	data = 0x27;
	IlSetECU2_Clock_MinuteSig(&data);
	data = 0x38;
	IlSetECU2_Clock_SecondSig(&data);

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[0]);
}

uint8_t IlGetECU2_VehicleToVehicleWarningDirectionSig(void)
{
	return ECU2_V2V_Warning_Tx1.V2V_Warning.VehcileToVehicleWarningDirection;
}

void IlSetECU2_VehicleToVehicleWarningDirectionSig(uint8_t * msgdata)
{
	ECU2_V2V_Warning_Tx1.V2V_Warning.VehcileToVehicleWarningDirection = msgdata[0];

	// CANFD Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[1]);
}

uint8_t IlGetECU2_VehicleToVehicleWarningIndicationRequestSig(void)
{
	return ECU2_V2V_Warning_Tx1.V2V_Warning.VehcileToVehicleWarningIndicationRequest;
}

void IlSetECU2_VehicleToVehicleWarningIndicationRequestSig(uint8_t * msgdata)
{
	ECU2_V2V_Warning_Tx1.V2V_Warning.VehcileToVehicleWarningIndicationRequest = msgdata[0];

	// CANFD Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[1]);
}

static void ilMsgECU2_V2V_Warning_Send(void)
{
	uint8_t data;
	
	// for initial value
	data = 0x02;
	IlSetECU2_VehicleToVehicleWarningDirectionSig(&data);
	data = 0x08;
	IlSetECU2_VehicleToVehicleWarningIndicationRequestSig(&data);

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_1, Can1_txmsg.id[1]);
}

bool IlGetRxECU2_SystemPowerModeValiditySig(void)
{
	return ECU2_ROUTED_System_Power_Mode_Rx0.System_Power_Mode.SystemPowerModeValidity;
}

uint8_t IlGetRxECU2_SystemPowerModeSig(void)
{
	return ECU2_ROUTED_System_Power_Mode_Rx0.System_Power_Mode.SystemPowerMode;
}

void IlMsgECU2_ROUTED_System_Power_Mode_Rx0Indication(uint8_t * data, uint8_t dlc)
{
	uint8_t buf[8];

	memcpy(buf, data, dlc);
	
	ApplRxECU2_SystemPowerModeValiditySigIndication();
	ApplRxECU2_SystemPowerModeSigIndication();
}

bool IlGetRxECU2_LeftLaneChangeThreatSig(void)
{
	return ECU2_ROUTED_Blind_Zone_Alert_Status_Rx1.Blind_Zone_Alert_Status.LeftLaneChangeThreat;
}

bool IlGetRxECU2_SlideBlindZoneAlertTempUnavailableIndiOnSig(void)
{
	return ECU2_ROUTED_Blind_Zone_Alert_Status_Rx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertTempUnavailableIndiOn;
}

bool IlGetRxECU2_SlideBlindZoneAlertSystemServiceIndiOnSig(void)
{
	return ECU2_ROUTED_Blind_Zone_Alert_Status_Rx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemServiceIndiOn;
}

bool IlGetRxECU2_SlideBlindZoneAlertSystemOffIndiOnSig(void)
{
	return ECU2_ROUTED_Blind_Zone_Alert_Status_Rx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemOffIndiOn;
}

bool IlGetRxECU2_SlideBlindZoneAlertSystemCleanIndiOnSig(void)
{
	return ECU2_ROUTED_Blind_Zone_Alert_Status_Rx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemCleanIndiOn;
}

uint8_t IlGetRxECU2_LeftLaneChangeApproachSpeedSig(void)
{
	return ECU2_ROUTED_Blind_Zone_Alert_Status_Rx1.Blind_Zone_Alert_Status.LeftLaneChangeApproachSpeed;
}

void IlMsgECU2_ROUTED_Blind_Zone_Alert_Status_Rx1Indication(uint8_t * data, uint8_t dlc)
{
	uint8_t buf[8];

	memcpy(buf, data, dlc);
	
	ApplRxECU2_LeftLaneChangeThreatSigIndication();
	ApplRxECU2_SlideBlindZoneAlertTempUnavailableIndiOnSigIndication();
	ApplRxECU2_SlideBlindZoneAlertSystemServiceIndiOnSigIndication();
	ApplRxECU2_SlideBlindZoneAlertSystemOffIndiOnSigIndication();
	ApplRxECU2_SlideBlindZoneAlertSystemCleanIndiOnSigIndication();
	ApplRxECU2_LeftLaneChangeApproachSpeedSigIndication();
}

uint8_t IlGetRxECU2_DrowsinessLevelSig(void)
{
	return ECU2_ROUTED_Drive_Status_Rx2.Drive_Status.DrowsinessLevel;
}

uint8_t IlGetRxECU2_DistractionLevelSig(void)
{
	return ECU2_ROUTED_Drive_Status_Rx2.Drive_Status.DistractionLevel;
}

uint8_t IlGetRxECU2_HandsOnLevelSig(void)
{
	return ECU2_ROUTED_Drive_Status_Rx2.Drive_Status.HandsOnLevel;
}

void IlMsgECU2_ROUTED_Drive_Status_Rx2Indication(uint8_t * data, uint8_t dlc)
{
	uint8_t buf[8];

	memcpy(buf, data, dlc);

	ApplRxECU2_DrowsinessLevelSigIndication();
	ApplRxECU2_DistractionLevelSigIndication();
	ApplRxECU2_HandsOnLevelSigIndication();
}

bool IlGetRxECU2_PedestrianFriendlyAlertSoundGenerationEnableSig(void)
{
	return ECU2_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3.Pedestrain_Friendly_Alert_Status.PedestrianFriendlyAlertSoundGenerationEnable;
}

uint8_t IlGetRxECU2_PedestrianFriendlyAlertForwardSoundSig(void)
{
	return ECU2_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3.Pedestrain_Friendly_Alert_Status.PedestrianFriendlyAlertForwardSound;
}

uint8_t IlGetRxECU2_PedestrianFriendlyAlertReverseSoundSig(void)
{
	return ECU2_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3.Pedestrain_Friendly_Alert_Status.PedestrianFriendlyAlertReverseSound;
}

uint8_t IlGetRxECU2_PedestrianFriendlyAlertCrossoverSpeedSig(void)
{
	return ECU2_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3.Pedestrain_Friendly_Alert_Status.PedestrianFriendlyAlertCrossoverSpeed;
}

uint8_t IlGetRxECU2_PedestrianFriendlyAlertSystemStatusSig(void)
{
	return ECU2_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3.Pedestrain_Friendly_Alert_Status.PedestrianFriendlyAlertSystemStatus;
}

void IlMsgECU2_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3Indication(uint8_t * data, uint8_t dlc)
{
	uint8_t buf[8];

	memcpy(buf, data, dlc);
	
	ApplRxECU2_PedestrianFriendlyAlertSoundGenerationEnableSigIndication();
	ApplRxECU2_PedestrianFriendlyAlertForwardSoundSigIndication();
	ApplRxECU2_PedestrianFriendlyAlertReverseSoundSigIndication();
	ApplRxECU2_PedestrianFriendlyAlertCrossoverSpeedSigIndication();
	ApplRxECU2_PedestrianFriendlyAlertSystemStatusSigIndication();
}

bool IlGetECU1_SystemPowerModeValiditySig(void)
{
	return ECU1_System_Power_Mode_Tx0.System_Power_Mode.SystemPowerModeValidity;
}

void IlSetECU1_SystemPowerModeValiditySig(uint8_t * msgdata)
{
	if (msgdata[0] == 0x01)
		ECU1_System_Power_Mode_Tx0.System_Power_Mode.SystemPowerModeValidity = 1;
	else
		ECU1_System_Power_Mode_Tx0.System_Power_Mode.SystemPowerModeValidity = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[0]);
}

uint8_t IlGetECU1_SystemPowerModeSig(void)
{
	return ECU1_System_Power_Mode_Tx0.System_Power_Mode.SystemPowerMode;
}

void IlSetECU1_SystemPowerModeSig(uint8_t * msgdata)
{
	if (msgdata[0] > 0x03)
	{
		// msg is not valid
	}
	else
	{
		ECU1_System_Power_Mode_Tx0.System_Power_Mode.SystemPowerMode = msgdata[0];
	}

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[0]);
}

static void ilMsgECU1_System_Power_Mode_Tx_Send(void)
{
	uint8_t data;
	
	// for initial value
	data = 1;
	IlSetECU1_SystemPowerModeValiditySig(&data);

	data = 0x00;
	IlSetECU1_SystemPowerModeSig(&data);

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[0]);
}

bool IlGetECU1_LeftLaneChangeThreatSig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.LeftLaneChangeThreat;
}

void IlSetECU1_LeftLaneChangeThreatSig(uint8_t * msgdata)	
{
	if (msgdata[0] == 0x01)
		ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.LeftLaneChangeThreat = 1;
	else
		ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.LeftLaneChangeThreat = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

bool IlGetECU1_SlideBlindZoneAlertTempUnavailableIndiOnSig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertTempUnavailableIndiOn;
}

void IlSetECU1_SlideBlindZoneAlertTempUnavailableIndiOnSig(uint8_t * msgdata)
{
	if (msgdata[0] == 0x01)
		ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertTempUnavailableIndiOn = 1;
	else
		ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertTempUnavailableIndiOn = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

bool IlGetECU1_SlideBlindZoneAlertSystemServiceIndiOnSig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemServiceIndiOn;
}

void IlSetECU1_SlideBlindZoneAlertSystemServiceIndiOnSig(uint8_t * msgdata)
{
	if (msgdata[0] == 0x01)
		ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemServiceIndiOn = 1;
	else
		ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemServiceIndiOn = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

bool IlGetECU1_SlideBlindZoneAlertSystemOffIndiOnSig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemOffIndiOn;
}

void IlSetECU1_SlideBlindZoneAlertSystemOffIndiOnSig(uint8_t * msgdata)
{
	if (msgdata[0] == 0x01)
		ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemOffIndiOn = 1;
	else
		ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemOffIndiOn = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

bool IlGetECU1_SlideBlindZoneAlertSystemCleanIndiOnSig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemCleanIndiOn;
}

void IlSetECU1_SlideBlindZoneAlertSystemCleanIndiOnSig(uint8_t * msgdata)
{
	if (msgdata[0] == 0x01)
		ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemCleanIndiOn = 1;
	else
		ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemCleanIndiOn = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

uint8_t IlGetECU1_LeftLaneChangeApproachSpeedSig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.LeftLaneChangeApproachSpeed;
}

void IlSetECU1_LeftLaneChangeApproachSpeedSig(uint8_t * msgdata)
{
	ECU1_Blind_Zone_Alert_Status_Tx1.Blind_Zone_Alert_Status.LeftLaneChangeApproachSpeed = msgdata[0];

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

static void ilMsgECU1_Blind_Zone_Alert_Status_Tx_Send(void)
{
	uint8_t data;
	
	// for initial value
	data = 1;
	IlSetECU1_LeftLaneChangeThreatSig(&data);
	IlSetECU1_SlideBlindZoneAlertTempUnavailableIndiOnSig(&data);
	IlSetECU1_SlideBlindZoneAlertSystemOffIndiOnSig(&data);
	data = 0;
	IlSetECU1_SlideBlindZoneAlertSystemServiceIndiOnSig(&data);
	IlSetECU1_SlideBlindZoneAlertSystemCleanIndiOnSig(&data);
	data = 217;
	IlSetECU1_LeftLaneChangeApproachSpeedSig(&data);

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

#if 0
void ApplCanMsg_ECU1_Blind_Zone_Alert_Status_Tx_Get(uint8_t * data)
{
	
}

void ApplCanMsg_ECU1_Blind_Zone_Alert_Status_Tx_Set(uint8_t * data)
{
	
}
#endif

void ilMsgNACU2_Diag_Tx3_Send(void)
{
	/*NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_0 = 0x01;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_1 = 0x02;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_2 = 0x03;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_3 = 0x04;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_4 = 0x05;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_5 = 0x06;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_6 = 0x07;
	NACU_Diag_Tx3.NACU_Diag_Tx.NACU_Diag_Response_7 = 0x08;*/

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[2]);
}

void ilMsgNACU2_Diag_Tx4_Send(void)
{
	/*NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_0 = 0x01;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_1 = 0x02;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_2 = 0x03;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_3 = 0x04;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_4 = 0x05;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_5 = 0x06;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_6 = 0x07;
	NACU_Diag_Tx4.NACU_Diag_Tx.NACU_Diag_Response_7 = 0x08;*/

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[3]);
}

void ilMsgNACU2_Diag_Tx5_Send(void)
{
	/*NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_0 = 0x01;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_1 = 0x02;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_2 = 0x03;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_3 = 0x04;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_4 = 0x05;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_5 = 0x06;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_6 = 0x07;
	NACU_Diag_Tx5.NACU_Diag_Tx.NACU_Diag_Response_7 = 0x08;*/

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[4]);
}

FuncCanTxCallback CanTxFuncList2[CAN3_NO_OF_TX_OBJECT] =
{
	ilMsgECU1_System_Power_Mode_Tx_Send,
	ilMsgECU1_Blind_Zone_Alert_Status_Tx_Send,
	ilMsgNACU2_Diag_Tx3_Send,
	ilMsgNACU2_Diag_Tx4_Send,
	ilMsgNACU2_Diag_Tx5_Send
};

/*******************************************************************************
	CAN 3 Receive message
 *******************************************************************************/

FuncCanRxCallback CanRxFuncList2[CAN3_NO_OF_RX_OBJECT] =
{
	IlMsgECU1_ROUTED_Clock_Rx0Indication,
	IlMsgECU1_ROUTED_Drive_Status_Rx1Indication,
	IlMsgECU1_ROUTED_V2V_Warning_Rx2Indication,
	IlMsgECU1_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3Indication,
	IlMsgBCM2_BCAN_1_Rx1Indication,
	IlMsgBCM2_BCAN_1_Rx2Indication,
	IlMsgBCM2_BCAN_1_Rx3Indication,
	IlMsgBCM2_BCAN_1_Rx4Indication,
	IlMsgICM2_1_Rx1Indication,
	IlMsgICM2_1_Rx2Indication,
	IlMsgICM2_1_Rx3Indication,
	IlMsgICM2_1_Rx4Indication,
	IlMsgBCM2_BCAN_2_Rx1Indication,
	IlMsgBCM2_BCAN_2_Rx2Indication,
	IlMsgBCM2_BCAN_2_Rx3Indication,
	IlMsgBCM2_BCAN_2_Rx4Indication,
};

uint8_t IlGetRxECU1_VehicleToVehicleWarningDirectionSig(void)
{
	return ECU1_ROUTED_V2V_Warning_Rx2.V2V_Warning.VehcileToVehicleWarningDirection;
}

uint8_t IlGetRxECU1_VehicleToVehicleWarningIndicationRequestSig(void)
{
	return ECU1_ROUTED_V2V_Warning_Rx2.V2V_Warning.VehcileToVehicleWarningIndicationRequest;
}

void IlMsgECU1_ROUTED_V2V_Warning_Rx2Indication(uint8_t * data, uint8_t dlc)
{
	uint8_t buf[8];

	memcpy(buf, data, dlc);
	
	ApplRxECU1_VehicleToVehicleWarningDirectionSigIndication();
	ApplRxECU1_VehicleToVehicleWarningIndicationRequestSigIndication();
}

bool IlGetRxECU1_PedestrianFriendlyAlertSoundGenerationEnableSig(void)
{
	return ECU1_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3.Pedestrain_Friendly_Alert_Status.PedestrianFriendlyAlertSoundGenerationEnable;
}

uint8_t IlGetRxECU1_PedestrianFriendlyAlertForwardSoundSig(void)
{
	return ECU1_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3.Pedestrain_Friendly_Alert_Status.PedestrianFriendlyAlertForwardSound;
}

uint8_t IlGetRxECU1_PedestrianFriendlyAlertReverseSoundSig(void)
{
	return ECU1_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3.Pedestrain_Friendly_Alert_Status.PedestrianFriendlyAlertReverseSound;
}

uint8_t IlGetRxECU1_PedestrianFriendlyAlertCrossoverSpeedSig(void)
{
	return ECU1_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3.Pedestrain_Friendly_Alert_Status.PedestrianFriendlyAlertCrossoverSpeed;
}

uint8_t IlGetRxECU1_PedestrianFriendlyAlertSystemStatusSig(void)
{
	return ECU1_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3.Pedestrain_Friendly_Alert_Status.PedestrianFriendlyAlertSystemStatus;
}

void IlMsgECU1_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3Indication(uint8_t * data, uint8_t dlc)
{
	uint8_t buf[8];

	memcpy(buf, data, dlc);
	
	ApplRxECU1_PedestrianFriendlyAlertSoundGenerationEnableSigIndication();
	ApplRxECU1_PedestrianFriendlyAlertForwardSoundSigIndication();
	ApplRxECU1_PedestrianFriendlyAlertReverseSoundSigIndication();
	ApplRxECU1_PedestrianFriendlyAlertCrossoverSpeedSigIndication();
	ApplRxECU1_PedestrianFriendlyAlertSystemStatusSigIndication();
}

uint8_t IlGetRxECU1_DrowsinessLevelSig(void)
{
	return ECU1_ROUTED_Drive_Status_Rx1.Drive_Status.DrowsinessLevel;
}

uint8_t IlGetRxECU1_DistractionLevelSig(void)
{
	return ECU1_ROUTED_Drive_Status_Rx1.Drive_Status.DistractionLevel;
}

uint8_t IlGetRxECU1_HandsOnLevelSig(void)
{
	return ECU1_ROUTED_Drive_Status_Rx1.Drive_Status.HandsOnLevel;
}

void IlMsgECU1_ROUTED_Drive_Status_Rx1Indication(uint8_t * data, uint8_t dlc)
{
	uint8_t buf[8];

	memcpy(buf, data, dlc);

	ApplRxECU1_DrowsinessLevelSigIndication();
	ApplRxECU1_DistractionLevelSigIndication();
	ApplRxECU1_HandsOnLevelSigIndication();
}

uint8_t IlGetRxECU1_ClockYearSig(void)
{
	return ECU1_ROUTED_Clock_Rx0.Clock.Year;
}

uint8_t IlGetRxECU1_ClockMonthSig(void)
{
	return ECU1_ROUTED_Clock_Rx0.Clock.Month;
}

uint8_t IlGetRxECU1_ClockDaySig(void)
{
	return ECU1_ROUTED_Clock_Rx0.Clock.Day;
}

uint8_t IlGetRxECU1_ClockHourSig(void)
{
	return ECU1_ROUTED_Clock_Rx0.Clock.Hour;
}

uint8_t IlGetRxECU1_ClockMinuteSig(void)
{
	return ECU1_ROUTED_Clock_Rx0.Clock.Minute;
}

uint8_t IlGetRxECU1_ClockSecondSig(void)
{
	return ECU1_ROUTED_Clock_Rx0.Clock.Second;
}

void IlMsgECU1_ROUTED_Clock_Rx0Indication(uint8_t * data, uint8_t dlc)
{
	uint8_t buf[8];

	memcpy(buf, data, dlc);
	
	ApplRxECU1_ClockYearSigIndication();
	ApplRxECU1_ClockMonthSigIndication();
	ApplRxECU1_ClockDaySigIndication();
	ApplRxECU1_ClockHourSigIndication();
	ApplRxECU1_ClockMinuteSigIndication();
	ApplRxECU1_ClockSecondSigIndication();
}

void IlMsgBCM2_TCU_BCS_Rx1Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgBCM2_TCU_BCS_Rx2Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgBCM2_TCU_BCS_Rx3Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgBCM2_TCU_BCS_Rx4Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgBCM2_BCAN_1_Rx1Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgBCM2_BCAN_1_Rx2Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgBCM2_BCAN_1_Rx3Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgBCM2_BCAN_1_Rx4Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgICM2_1_Rx1Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgICM2_1_Rx2Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgICM2_1_Rx3Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgICM2_1_Rx4Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgBCM2_BCAN_2_Rx1Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgBCM2_BCAN_2_Rx2Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgBCM2_BCAN_2_Rx3Indication(uint8_t * data, uint8_t dlc)
{
}

void IlMsgBCM2_BCAN_2_Rx4Indication(uint8_t * data, uint8_t dlc)
{
}

