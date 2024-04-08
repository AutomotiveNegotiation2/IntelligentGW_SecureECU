#ifndef _IL_PAR_H_
#define	_IL_PAR_H_

uint16_t IlGetRx1BCS_VehSpd(void);
bool IlGetRx1BCS_VehSpdVD(void);
uint16_t IlGetRx2BCS_VehSpd(void);
bool IlGetRx2BCS_VehSpdVD(void);
uint16_t IlGetRx3BCS_VehSpd(void);
bool IlGetRx3BCS_VehSpdVD(void);
uint16_t IlGetRx4BCS_VehSpd(void);
bool IlGetRx4BCS_VehSpdVD(void);

void IlMsgBCM_TCU_BCS_Rx1Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM_TCU_BCS_Rx2Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM_TCU_BCS_Rx3Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM_TCU_BCS_Rx4Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM_BCAN_1_Rx1Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM_BCAN_1_Rx2Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM_BCAN_1_Rx3Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM_BCAN_1_Rx4Indication(uint8_t * data, uint8_t dlc);
void IlMsgICM_1_Rx1Indication(uint8_t * data, uint8_t dlc);
void IlMsgICM_1_Rx2Indication(uint8_t * data, uint8_t dlc);
void IlMsgICM_1_Rx3Indication(uint8_t * data, uint8_t dlc);
void IlMsgICM_1_Rx4Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM_BCAN_2_Rx1Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM_BCAN_2_Rx2Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM_BCAN_2_Rx3Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM_BCAN_2_Rx4Indication(uint8_t * data, uint8_t dlc);

extern void ApplCanTx1ECU1_LeftLaneChangeThreat_Sig_Comfirmation(void);
extern void ApplCanTx1ECU1_SlideBlindZoneAlertTempUnavailableIndiOn_Sig_Comfirmation(void);
extern void ApplCanTx1ECU1_SlideBlindZoneAlertSystemServiceIndiOn_Sig_Comfirmation(void);
extern void ApplCanTx1ECU1_SlideBlindZoneAlertSystemOffIndiOn_Sig_Comfirmation(void);
extern void ApplCanTx1ECU1_SlideBlindZoneAlertSystemCleanIndiOn_Sig_Comfirmation(void);
extern void ApplCanTx1ECU1_LeftLaneChangeApproachSpeed_Sig_Comfirmation(void);
extern void ApplRx2ECU2_VehicleToVehicleWarningDirectionSigIndication(void);
extern void ApplRx2ECU2_VehicleToVehicleWarningIndicationRequestSigIndication(void);

extern void ApplRx1BCS_VehSpdSigIndication(void);
extern void ApplRx1BCS_VehSpdVDSigIndication(void);
extern void ApplRx2BCS_VehSpdSigIndication(void);
extern void ApplRx2BCS_VehSpdVDSigIndication(void);
extern void ApplRx3BCS_VehSpdSigIndication(void);
extern void ApplRx3BCS_VehSpdVDSigIndication(void);
extern void ApplRx4BCS_VehSpdSigIndication(void);
extern void ApplRx4BCS_VehSpdVDSigIndication(void);

extern void ApplRx1BCAN_1_ReverseSwitchStSigIndication(void);
extern void ApplRx1BCAN_1_ParkingLampStSigIndication(void);
extern void ApplRx2BCAN_1_ReverseSwitchStSigIndication(void);
extern void ApplRx2BCAN_1_ParkingLampStSigIndication(void);
extern void ApplRx3BCAN_1_ReverseSwitchStSigIndication(void);
extern void ApplRx3BCAN_1_ParkingLampStSigIndication(void);
extern void ApplRx4BCAN_1_ReverseSwitchStSigIndication(void);
extern void ApplRx4BCAN_1_ParkingLampStSigIndication(void);

extern void ApplRx1ICM_HandBrakeStSigIndication(void);
extern void ApplRx1ICM_HandBrakeVDSigIndication(void);
extern void ApplRx1ICM_BackLightLevelSigIndication(void);
extern void ApplRx2ICM_HandBrakeStSigIndication(void);
extern void ApplRx2ICM_HandBrakeVDSigIndication(void);
extern void ApplRx2ICM_BackLightLevelSigIndication(void);
extern void ApplRx3ICM_HandBrakeStSigIndication(void);
extern void ApplRx3ICM_HandBrakeVDSigIndication(void);
extern void ApplRx3ICM_BackLightLevelSigIndication(void);
extern void ApplRx4ICM_HandBrakeStSigIndication(void);
extern void ApplRx4ICM_HandBrakeVDSigIndication(void);
extern void ApplRx4ICM_BackLightLevelSigIndication(void);

extern void ApplRx1ICM_ModuleSigIndication(void);
extern void ApplRx1HVAC_ModuleSigIndication(void);
extern void ApplRx1ACU_NACU_ModuleSigIndication(void);
extern void ApplRx1TPMS_ModuleSigIndication(void);
extern void ApplRx1SAM_ModuleSigIndication(void);
extern void ApplRx1BCM_ModuleSigIndication(void);
extern void ApplRx1EMS_ModuleSigIndication(void);
extern void ApplRx1TCU_ModuleSigIndication(void);
extern void ApplRx1SRS_ModuleSigIndication(void);
extern void ApplRx1BCS_ModuleSigIndication(void);
extern void ApplRx1EPS_ModuleSigIndication(void);
extern void ApplRx1ALS_ModuleSigIndication(void);
extern void ApplRx1SAS_ModuleSigIndication(void);

bool IlGetECU1_LeftLaneChangeThreat_Sig(void);
void IlSetECU1_LeftLaneChangeThreat_Sig(uint8_t * msgdata);
bool IlGetECU1_SlideBlindZoneAlertTempUnavailableIndiOn_Sig(void);
void IlSetECU1_SlideBlindZoneAlertTempUnavailableIndiOn_Sig(uint8_t * msgdata);
bool IlGetECU1_SlideBlindZoneAlertSystemServiceIndiOn_Sig(void);
void IlSetECU1_SlideBlindZoneAlertSystemServiceIndiOn_Sig(uint8_t * msgdata);
bool IlGetECU1_SlideBlindZoneAlertSystemOffIndiOn_Sig(void);
void IlSetECU1_SlideBlindZoneAlertSystemOffIndiOn_Sig(uint8_t * msgdata);
bool IlGetECU1_SlideBlindZoneAlertSystemCleanIndiOn_Sig(void);
void IlSetECU1_SlideBlindZoneAlertSystemCleanIndiOn_Sig(uint8_t * msgdata);
uint8_t IlGetECU1_LeftLaneChangeApproachSpeed_Sig(void);
uint8_t IlGetECU1_LeftLaneChangeApproachSpeed_Sig(void);


void IlMsgECU2_V2V_Warning_Rx1Indication(uint8_t * data, uint8_t dlc);

void IlMsgBCM2_TCU_BCS_Rx1Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM2_TCU_BCS_Rx2Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM2_TCU_BCS_Rx3Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM2_TCU_BCS_Rx4Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM2_BCAN_1_Rx1Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM2_BCAN_1_Rx2Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM2_BCAN_1_Rx3Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM2_BCAN_1_Rx4Indication(uint8_t * data, uint8_t dlc);
void IlMsgICM2_1_Rx1Indication(uint8_t * data, uint8_t dlc);
void IlMsgICM2_1_Rx2Indication(uint8_t * data, uint8_t dlc);
void IlMsgICM2_1_Rx3Indication(uint8_t * data, uint8_t dlc);
void IlMsgICM2_1_Rx4Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM2_BCAN_2_Rx1Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM2_BCAN_2_Rx2Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM2_BCAN_2_Rx3Indication(uint8_t * data, uint8_t dlc);
void IlMsgBCM2_BCAN_2_Rx4Indication(uint8_t * data, uint8_t dlc);

extern void ApplRx2ICM_ModuleSigIndication(void);
extern void ApplRx2HVAC_ModuleSigIndication(void);
extern void ApplRx2ACU_NACU_ModuleSigIndication(void);
extern void ApplRx2TPMS_ModuleSigIndication(void);
extern void ApplRx2SAM_ModuleSigIndication(void);
extern void ApplRx2BCM_ModuleSigIndication(void);
extern void ApplRx2EMS_ModuleSigIndication(void);
extern void ApplRx2TCU_ModuleSigIndication(void);
extern void ApplRx2SRS_ModuleSigIndication(void);
extern void ApplRx2BCS_ModuleSigIndication(void);
extern void ApplRx2EPS_ModuleSigIndication(void);
extern void ApplRx2ALS_ModuleSigIndication(void);
extern void ApplRx2SAS_ModuleSigIndication(void);

extern void ApplRx3ICM_ModuleSigIndication(void);
extern void ApplRx3HVAC_ModuleSigIndication(void);
extern void ApplRx3ACU_NACU_ModuleSigIndication(void);
extern void ApplRx3TPMS_ModuleSigIndication(void);
extern void ApplRx3SAM_ModuleSigIndication(void);
extern void ApplRx3BCM_ModuleSigIndication(void);
extern void ApplRx3EMS_ModuleSigIndication(void);
extern void ApplRx3TCU_ModuleSigIndication(void);
extern void ApplRx3SRS_ModuleSigIndication(void);
extern void ApplRx3BCS_ModuleSigIndication(void);
extern void ApplRx3EPS_ModuleSigIndication(void);
extern void ApplRx3ALS_ModuleSigIndication(void);
extern void ApplRx3SAS_ModuleSigIndication(void);

extern void ApplRx4ICM_ModuleSigIndication(void);
extern void ApplRx4HVAC_ModuleSigIndication(void);
extern void ApplRx4ACU_NACU_ModuleSigIndication(void);
extern void ApplRx4TPMS_ModuleSigIndication(void);
extern void ApplRx4SAM_ModuleSigIndication(void);
extern void ApplRx4BCM_ModuleSigIndication(void);
extern void ApplRx4EMS_ModuleSigIndication(void);
extern void ApplRx4TCU_ModuleSigIndication(void);
extern void ApplRx4SRS_ModuleSigIndication(void);
extern void ApplRx4BCS_ModuleSigIndication(void);
extern void ApplRx4EPS_ModuleSigIndication(void);
extern void ApplRx4ALS_ModuleSigIndication(void);
extern void ApplRx4SAS_ModuleSigIndication(void);

#endif /* _IL_PAR_H_ */
