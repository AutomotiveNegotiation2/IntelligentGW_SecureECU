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

extern void ApplRxECU1_VehicleToVehicleWarningDirectionSigIndication(void);
extern void ApplRxECU1_VehicleToVehicleWarningIndicationRequestSigIndication(void);
extern void ApplRxECU1_PedestrianFriendlyAlertSoundGenerationEnableSigIndication(void);
extern void ApplRxECU1_PedestrianFriendlyAlertForwardSoundSigIndication(void);
extern void ApplRxECU1_PedestrianFriendlyAlertReverseSoundSigIndication(void);
extern void	ApplRxECU1_PedestrianFriendlyAlertCrossoverSpeedSigIndication(void);
extern void ApplRxECU1_PedestrianFriendlyAlertSystemStatusSigIndication(void);
extern void ApplRxECU1_DrowsinessLevelSigIndication(void);
extern void ApplRxECU1_DistractionLevelSigIndication(void);
extern void ApplRxECU1_HandsOnLevelSigIndication(void);
extern void ApplRxECU1_ClockYearSigIndication(void);
extern void ApplRxECU1_ClockMonthSigIndication(void);
extern void ApplRxECU1_ClockDaySigIndication(void);
extern void ApplRxECU1_ClockHourSigIndication(void);
extern void ApplRxECU1_ClockMinuteSigIndication(void);
extern void ApplRxECU1_ClockSecondSigIndication(void);

extern void ApplRxECU2_SystemPowerModeValiditySigIndication(void);
extern void ApplRxECU2_SystemPowerModeSigIndication(void);
extern void ApplRxECU2_LeftLaneChangeThreatSigIndication(void);
extern void ApplRxECU2_SlideBlindZoneAlertTempUnavailableIndiOnSigIndication(void);
extern void ApplRxECU2_SlideBlindZoneAlertSystemServiceIndiOnSigIndication(void);
extern void ApplRxECU2_SlideBlindZoneAlertSystemOffIndiOnSigIndication(void);
extern void ApplRxECU2_SlideBlindZoneAlertSystemCleanIndiOnSigIndication(void);
extern void ApplRxECU2_LeftLaneChangeApproachSpeedSigIndication(void);
extern void ApplRxECU2_DrowsinessLevelSigIndication(void);
extern void ApplRxECU2_DistractionLevelSigIndication(void);
extern void ApplRxECU2_HandsOnLevelSigIndication(void);
extern void ApplRxECU2_PedestrianFriendlyAlertSoundGenerationEnableSigIndication(void);
extern void ApplRxECU2_PedestrianFriendlyAlertForwardSoundSigIndication(void);
extern void ApplRxECU2_PedestrianFriendlyAlertReverseSoundSigIndication(void);
extern void	ApplRxECU2_PedestrianFriendlyAlertCrossoverSpeedSigIndication(void);
extern void ApplRxECU2_PedestrianFriendlyAlertSystemStatusSigIndication(void);

void ApplRx1BCS_VehSpdSigIndication(void);

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

bool IlGetECU1_LeftLaneChangeThreatSig(void);
void IlSetECU1_LeftLaneChangeThreatSig(uint8_t * msgdata);
bool IlGetECU1_SlideBlindZoneAlertTempUnavailableIndiOnSig(void);
void IlSetECU1_SlideBlindZoneAlertTempUnavailableIndiOnSig(uint8_t * msgdata);
bool IlGetECU1_SlideBlindZoneAlertSystemServiceIndiOnSig(void);
void IlSetECU1_SlideBlindZoneAlertSystemServiceIndiOnSig(uint8_t * msgdata);
bool IlGetECU1_SlideBlindZoneAlertSystemOffIndiOnSig(void);
void IlSetECU1_SlideBlindZoneAlertSystemOffIndiOnSig(uint8_t * msgdata);
bool IlGetECU1_SlideBlindZoneAlertSystemCleanIndiOnSig(void);
void IlSetECU1_SlideBlindZoneAlertSystemCleanIndiOnSig(uint8_t * msgdata);
uint8_t IlGetECU1_LeftLaneChangeApproachSpeedSig(void);
void IlSetECU1_LeftLaneChangeApproachSpeedSig(uint8_t * msgdata);
uint8_t IlGetRxECU1_VehicleToVehicleWarningDirectionSig(void);
uint8_t IlGetRxECU1_VehicleToVehicleWarningIndicationRequestSig(void);
bool IlGetRxECU1_PedestrianFriendlyAlertSoundGenerationEnableSig(void);
uint8_t IlGetRxECU1_PedestrianFriendlyAlertForwardSoundSig(void);
uint8_t IlGetRxECU1_PedestrianFriendlyAlertReverseSoundSig(void);
uint8_t IlGetRxECU1_PedestrianFriendlyAlertCrossoverSpeedSig(void);
uint8_t IlGetRxECU1_PedestrianFriendlyAlertSystemStatusSig(void);
uint8_t IlGetRxECU1_DrowsinessLevelSig(void);
uint8_t IlGetRxECU1_DistractionLevelSig(void);
uint8_t IlGetRxECU1_HandsOnLevelSig(void);
uint8_t IlGetRxECU1_ClockYearSig(void);
uint8_t IlGetRxECU1_ClockMonthSig(void);
uint8_t IlGetRxECU1_ClockDaySig(void);
uint8_t IlGetRxECU1_ClockHourSig(void);
uint8_t IlGetRxECU1_ClockMinuteSig(void);
uint8_t IlGetRxECU1_ClockSecondSig(void);
bool IlGetECU1_SystemPowerModeValiditySig(void);
void IlSetECU1_SystemPowerModeValiditySig(uint8_t * msgdata);
uint8_t IlGetECU1_SystemPowerModeSig(void);
void IlSetECU1_SystemPowerModeSig(uint8_t * msgdata);

uint8_t IlGetECU2_VehicleToVehicleWarningDirectionSig(void);
void IlSetECU2_VehicleToVehicleWarningDirectionSig(uint8_t * msgdata);
uint8_t IlGetECU2_VehicleToVehicleWarningIndicationRequestSig(void);
void IlSetECU2_VehicleToVehicleWarningIndicationRequestSig(uint8_t * msgdata);

bool IlGetRxECU2_SystemPowerModeValiditySig(void);
uint8_t IlGetRxECU2_SystemPowerModeSig(void);
void IlMsgECU2_ROUTED_System_Power_Mode_Rx0Indication(uint8_t * data, uint8_t dlc);

bool IlGetRxECU2_LeftLaneChangeThreatSig(void);
bool IlGetRxECU2_SlideBlindZoneAlertTempUnavailableIndiOnSig(void);
bool IlGetRxECU2_SlideBlindZoneAlertSystemServiceIndiOnSig(void);
bool IlGetRxECU2_SlideBlindZoneAlertSystemOffIndiOnSig(void);
bool IlGetRxECU2_SlideBlindZoneAlertSystemCleanIndiOnSig(void);
uint8_t IlGetRxECU2_LeftLaneChangeApproachSpeedSig(void);
void IlMsgECU2_ROUTED_Blind_Zone_Alert_Status_Rx1Indication(uint8_t * data, uint8_t dlc);

uint8_t IlGetRxECU2_DrowsinessLevelSig(void);
uint8_t IlGetRxECU2_DistractionLevelSig(void);
uint8_t IlGetRxECU2_HandsOnLevelSig(void);
void IlMsgECU2_ROUTED_Drive_Status_Rx2Indication(uint8_t * data, uint8_t dlc);

bool IlGetRxECU2_PedestrianFriendlyAlertSoundGenerationEnableSig(void);
uint8_t IlGetRxECU2_PedestrianFriendlyAlertForwardSoundSig(void);
uint8_t IlGetRxECU2_PedestrianFriendlyAlertReverseSoundSig(void);
uint8_t IlGetRxECU2_PedestrianFriendlyAlertCrossoverSpeedSig(void);
uint8_t IlGetRxECU2_PedestrianFriendlyAlertSystemStatusSig(void);
void IlMsgECU2_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3Indication(uint8_t * data, uint8_t dlc);

uint16_t IlGetECU2_Clock_YearSig(void);
uint8_t IlGetECU2_Clock_MonthSig(void);
uint8_t IlGetECU2_Clock_DaySig(void);
uint8_t IlGetECU2_Clock_HourSig(void);
uint8_t IlGetECU2_Clock_MinuteSig(void);
uint8_t IlGetECU2_Clock_SecondSig(void);

void IlSetECU2_Clock_YearSig(uint16_t * msgdata);
void IlSetECU2_Clock_MonthSig(uint8_t * msgdata);
void IlSetECU2_Clock_DaySig(uint8_t * msgdata);
void IlSetECU2_Clock_HourSig(uint8_t * msgdata);
void IlSetECU2_Clock_MinuteSig(uint8_t * msgdata);
void IlSetECU2_Clock_SecondSig(uint8_t * msgdata);

void IlMsgECU1_ROUTED_V2V_Warning_Rx2Indication(uint8_t * data, uint8_t dlc);
void IlMsgECU1_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3Indication(uint8_t * data, uint8_t dlc);
void IlMsgECU1_ROUTED_Drive_Status_Rx1Indication(uint8_t * data, uint8_t dlc);
void IlMsgECU1_ROUTED_Clock_Rx0Indication(uint8_t * data, uint8_t dlc);

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
