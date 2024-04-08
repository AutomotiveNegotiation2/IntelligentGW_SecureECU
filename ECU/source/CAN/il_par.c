#include "Includes.h"

void CAN_SetTxFlagForMsgUpdate(can_inst_t canChannel, uint32_t msgId);
void ilMsg_Register_Callback_Fn(can_inst_t instance, uint32_t id);

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
	ilMsgNACU_Diag_Tx1_Send,
	ilMsgNACU_Diag_Tx2_Send,
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
	IlMsgBCM_TCU_BCS_Rx1Indication,
	IlMsgBCM_TCU_BCS_Rx2Indication,
	IlMsgBCM_TCU_BCS_Rx3Indication,
	IlMsgBCM_TCU_BCS_Rx4Indication,
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

bool IlGetECU1_SystemPowerModeValidity_Sig(void)
{
	return ECU1_System_Power_Mode_Tx.System_Power_Mode.SystemPowerModeValidity;
}

void IlSetECU1_SystemPowerModeValidity_Sig(uint8_t * msgdata)
{
	if (msgdata[0] == 0x01)
		ECU1_System_Power_Mode_Tx.System_Power_Mode.SystemPowerModeValidity = 1;
	else
		ECU1_System_Power_Mode_Tx.System_Power_Mode.SystemPowerModeValidity = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[0]);
}

uint8_t IlGetECU1_SystemPowerMode_Sig(void)
{
	return ECU1_System_Power_Mode_Tx.System_Power_Mode.SystemPowerMode;
}

void IlSetECU1_SystemPowerMode_Sig(uint8_t * msgdata)
{
	if (msgdata[0] > 0x03)
	{
		// msg is not valid
	}
	else
	{
		ECU1_System_Power_Mode_Tx.System_Power_Mode.SystemPowerMode = msgdata[0];
	}

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[0]);
}

void ilMsgECU1_System_Power_Mode_Tx_Send(void)
{
	uint8_t data;
	
	// for initial value
	data = 1;
	IlSetECU1_SystemPowerModeValidity_Sig(&data);

	data = 0x00;
	IlSetECU1_SystemPowerMode_Sig(&data);

	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[0]);
}

bool IlGetECU1_LeftLaneChangeThreat_Sig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.LeftLaneChangeThreat;
}

void IlSetECU1_LeftLaneChangeThreat_Sig(uint8_t * msgdata)	
{
	if (msgdata[0] == 0x01)
		ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.LeftLaneChangeThreat = 1;
	else
		ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.LeftLaneChangeThreat = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

bool IlGetECU1_SlideBlindZoneAlertTempUnavailableIndiOn_Sig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertTempUnavailableIndiOn;
}

void IlSetECU1_SlideBlindZoneAlertTempUnavailableIndiOn_Sig(uint8_t * msgdata)
{
	if (msgdata[0] == 0x01)
		ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertTempUnavailableIndiOn = 1;
	else
		ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertTempUnavailableIndiOn = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

bool IlGetECU1_SlideBlindZoneAlertSystemServiceIndiOn_Sig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemServiceIndiOn;
}

void IlSetECU1_SlideBlindZoneAlertSystemServiceIndiOn_Sig(uint8_t * msgdata)
{
	if (msgdata[0] == 0x01)
		ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemServiceIndiOn = 1;
	else
		ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemServiceIndiOn = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

bool IlGetECU1_SlideBlindZoneAlertSystemOffIndiOn_Sig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemOffIndiOn;
}

void IlSetECU1_SlideBlindZoneAlertSystemOffIndiOn_Sig(uint8_t * msgdata)
{
	if (msgdata[0] == 0x01)
		ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemOffIndiOn = 1;
	else
		ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemOffIndiOn = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

bool IlGetECU1_SlideBlindZoneAlertSystemCleanIndiOn_Sig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemCleanIndiOn;
}

void IlSetECU1_SlideBlindZoneAlertSystemCleanIndiOn_Sig(uint8_t * msgdata)
{
	if (msgdata[0] == 0x01)
		ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemCleanIndiOn = 1;
	else
		ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.SlideBlindZoneAlertSystemCleanIndiOn = 0;

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

uint8_t IlGetECU1_LeftLaneChangeApproachSpeed_Sig(void)
{
	return ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.LeftLaneChangeApproachSpeed;
}

void IlSetECU1_LeftLaneChangeApproachSpeed_Sig(uint8_t * msgdata)
{
	ECU1_Blind_Zone_Alert_Status_Tx.Blind_Zone_Alert_Status.LeftLaneChangeApproachSpeed = msgdata[0];

	// CAN Transmit ON
	if (ilGetFirstCanOpStatus() != ON)
		CAN_SetTxFlagForMsgUpdate(CAN_CH_3, Can3_txmsg.id[1]);
}

void ilMsgECU1_Blind_Zone_Alert_Status_Tx_Send(void)
{
	uint8_t data;
	
	// for initial value
	data = 1;
	IlSetECU1_LeftLaneChangeThreat_Sig(&data);
	IlSetECU1_SlideBlindZoneAlertTempUnavailableIndiOn_Sig(&data);
	IlSetECU1_SlideBlindZoneAlertSystemOffIndiOn_Sig(&data);
	data = 0;
	IlSetECU1_SlideBlindZoneAlertSystemServiceIndiOn_Sig(&data);
	IlSetECU1_SlideBlindZoneAlertSystemCleanIndiOn_Sig(&data);
	data = 217;
	IlSetECU1_LeftLaneChangeApproachSpeed_Sig(&data);

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
	//ilMsgNACU2_Diag_Tx1_Send,
	ilMsgECU1_System_Power_Mode_Tx_Send,
	//ilMsgNACU2_Diag_Tx2_Send,
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
	IlMsgBCM2_TCU_BCS_Rx1Indication,
	IlMsgECU2_V2V_Warning_Rx1Indication,	//IlMsgBCM2_TCU_BCS_Rx2Indication,
	IlMsgBCM2_TCU_BCS_Rx3Indication,
	IlMsgBCM2_TCU_BCS_Rx4Indication,
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

void IlMsgECU2_V2V_Warning_Rx1Indication(uint8_t * data, uint8_t dlc)
{
	uint8_t buf[8];

	memcpy(buf, data, dlc);
	
	ApplRx2ECU2_VehicleToVehicleWarningDirectionSigIndication();
	ApplRx2ECU2_VehicleToVehicleWarningIndicationRequestSigIndication();
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

