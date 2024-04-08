#ifndef _CAN_PAR_H_
#define	_CAN_PAR_H_

#pragma pack(push, 4)

#define	CAN3_NO_OF_RX_OBJECT		16
#define	CAN3_NO_OF_TX_OBJECT		5
#define	CAN3_NO_OF_MSG_OBJECT		(CAN3_NO_OF_RX_OBJECT+CAN3_NO_OF_TX_OBJECT)

#define	CAN1_NO_OF_RX_OBJECT		16
#define	CAN1_NO_OF_TX_OBJECT		5
#define	CAN1_NO_OF_MSG_OBJECT		(CAN1_NO_OF_RX_OBJECT+CAN1_NO_OF_TX_OBJECT)

enum {
	CAN_TX_ATTR_EVENT		= 0,
	CAN_TX_ATTR_PERIODIC,
	CAN_TX_ATTR_MAX			
};

enum {
	CAN_TX_PERI_FUNC_STOP = 0,
	CAN_TX_PERI_FUNC_START,
};

typedef enum {
	CAN_NOT_USED = 0u,
	CAN_1,
	CAN_2,
	CAN_3,
	CAN_NO_MAX,
} can_instance_t;

typedef enum {
	MSG_UPDATE_COMPLETE = 0u,
	MSG_UPDATE_REQUEST,
} msg_update_inst_t;

typedef void (*FuncCanTxCallback)(void);
//typedef void (*FuncCanTxCallback)(uint8_t instance, uint32_t id);
typedef void (*FuncCanRxCallback)(uint8_t * data, uint8_t dlc);

typedef struct {
	can_instance_t inst;
	uint8_t NoOfMsg;
	uint8_t * mbox;
	uint32_t * id;
	uint8_t * dlc;
	uint8_t ** data;
	uint8_t * attr;
	uint16_t * attrtime;
	//uint8_t ptr;
	uint16_t * stimerId;
	uint8_t * stimer_state;
	FuncCanTxCallback * tCallback;
	FuncCanRxCallback * rCallback;
	msg_update_inst_t * msgUpdate;
} CAN_MSG_FUNC_ptr;

typedef struct _c_NACU_Diag_Tx_msgTypeTag
{
	uint8_t NACU_Diag_Response_0 : 8;
	uint8_t NACU_Diag_Response_1 : 8;
	uint8_t NACU_Diag_Response_2 : 8;
	uint8_t NACU_Diag_Response_3 : 8;
	uint8_t NACU_Diag_Response_4 : 8;
	uint8_t NACU_Diag_Response_5 : 8;
	uint8_t NACU_Diag_Response_6 : 8;
	uint8_t NACU_Diag_Response_7 : 8;
} _c_NACU_Diag_Tx_msgType;

typedef union _c_NACU_Diag_Tx_bufTag
{
	uint8_t _c[8];
	_c_NACU_Diag_Tx_msgType NACU_Diag_Tx;
} _c_NACU_Diag_Tx_buf;

typedef struct _c_ECU1_Blind_Zone_Alert_Status_msgTypeTag
{
	uint8_t unused0 : 3;
	uint8_t SlideBlindZoneAlertSystemCleanIndiOn : 1;
	uint8_t SlideBlindZoneAlertSystemOffIndiOn : 1;
	uint8_t SlideBlindZoneAlertSystemServiceIndiOn : 1;
	uint8_t SlideBlindZoneAlertTempUnavailableIndiOn : 1;
	uint8_t LeftLaneChangeThreat : 1;
	uint8_t LeftLaneChangeApproachSpeed : 8;
} _c_Blind_Zone_Alert_Status_msgType;

typedef union _c_ECU1_Blind_Zone_Alert_Status_bufTag
{
	uint8_t _c[2];
	_c_Blind_Zone_Alert_Status_msgType Blind_Zone_Alert_Status;
} _c_Blind_Zone_Alert_Status_buf;

typedef struct _c_System_Power_Mode_msgTypeTag
{
	uint8_t unused0 : 5;
	uint8_t SystemPowerMode : 2;
	uint8_t SystemPowerModeValidity : 1;
} _c_System_Power_Mode_msgType;

typedef union _c_System_Power_Mode_bufTag
{
	uint8_t _c[1];
	_c_System_Power_Mode_msgType System_Power_Mode;
} _c_System_Power_Mode_buf;

typedef struct _c_BCM_TCU_BCS_msgTypeTag
{
	uint8_t unused0 : 8;
	uint8_t unused1 : 8;
	uint8_t unused2 : 3;
	uint8_t BCS_VehSpd_1 : 5;
	uint8_t BCS_VehSpd_0 : 8;
	uint8_t unused3 : 7;
	uint8_t BCS_VehSpdVD : 1;
} _c_BCM_TCU_BCS_msgType;

typedef union _c_BCM_TCU_BCS_bufTag
{
	uint8_t _c[5];
	_c_BCM_TCU_BCS_msgType BCM_TCU_BCS;
} _c_BCM_TCU_BCS_buf;

typedef struct _c_V2V_Warning_msgTypeTag
{
	uint8_t VehcileToVehicleWarningIndicationRequest : 5;
	uint8_t VehcileToVehicleWarningDirection : 3;
} _c_V2V_Warning_msgType;

typedef union _c_V2V_Warning_bufTag
{
	uint8_t _c[1];
	_c_V2V_Warning_msgType V2V_Warning;
} _c_V2V_Warning_buf;

typedef struct _c_Pedestrain_Friendly_Alert_Status_msgTypeTag
{
	uint8_t unused0	: 3;
	uint8_t PedestrianFriendlyAlertReverseSound	: 2;
	uint8_t PedestrianFriendlyAlertForwardSound	: 2;
	uint8_t	PedestrianFriendlyAlertSoundGenerationEnable	: 1;
	uint8_t PedestrianFriendlyAlertCrossoverSpeed : 8;
	uint8_t unused1	: 6;
	uint8_t PedestrianFriendlyAlertSystemStatus : 2;
} _c_Pedestrain_Friendly_Alert_Status_msgType;

typedef union _c_Pedestrain_Friendly_Alert_Status_bufTag
{
	uint8_t _c[3];
	_c_Pedestrain_Friendly_Alert_Status_msgType Pedestrain_Friendly_Alert_Status;
} _c_Pedestrain_Friendly_Alert_Status_buf;

typedef struct _c_Drive_Status_msgTypeTag
{
	uint8_t DrowsinessLevel	: 8;
	uint8_t DistractionLevel	: 8;
	uint8_t HandsOnLevel	: 8;
} _c_Drive_Status_msgType;

typedef union _c_Drive_Status_bufTag
{
	uint8_t _c[3];
	_c_Drive_Status_msgType Drive_Status;
} _c_Drive_Status_buf;

typedef struct _c_Clock_msgTypeTag
{
	uint8_t Year	: 8;
	uint8_t Month	: 8;
	uint8_t Day		: 8;
	uint8_t Hour	: 8;
	uint8_t Minute	: 8;
	uint8_t Second	: 8;
} _c_Clock_msgType;

typedef union _c_Clock_bufTag
{
	uint8_t _c[3];
	_c_Clock_msgType Clock;
} _c_Clock_buf;

typedef struct _c_BCM_BCAN_1_msgTypeTag
{
	uint8_t unused0 : 8;
	uint8_t unused1 : 8;
	uint8_t unused2 : 8;
	uint8_t BCM_ParkingLampSt : 1;
	uint8_t unused3 : 1;
	uint8_t BCM_ReverseSwitchSt : 1;
	uint8_t unused4 : 5;
} _c_BCM_BCAN_1_msgType;

typedef union _c_BCM_BCAN_1_bufTag
{
	uint8_t _c[4];
	_c_BCM_BCAN_1_msgType BCM_BCAN_1;
} _c_BCM_BCAN_1_buf;

typedef struct _c_ICM_1_msgTypeTag
{
	uint8_t ICM_HandBrakeSt : 1;
	uint8_t unused0 : 3;
	uint8_t ICM_HandBrakeVD : 1;
	uint8_t unused1 : 3;
	uint8_t unused2 : 8;
	uint8_t unused3 : 8;
	uint8_t unused4 : 8;
	uint8_t unused5 : 8;
	uint8_t unused6 : 8;
	uint8_t unused7 : 2;
	uint8_t ICM_BackLightLevel : 4;
	uint8_t unused8 : 2;
} _c_ICM_1_msgType;

typedef union _c_ICM_1_bufTag
{
	uint8_t _c[7];
	_c_ICM_1_msgType ICM_1;
} _c_ICM_1_buf;

typedef struct _c_BCM_BCAN_2_msgTypeTag
{
	uint8_t ICM_Module : 1;
	uint8_t HVAC_Module : 1;
	uint8_t RPA_Module : 1;
	uint8_t ACU_NACU_Module : 1;
	uint8_t TPMS_Module : 1;
	uint8_t SAM_Module : 1;
	uint8_t BCM_Module : 1;
	uint8_t EMS_Module : 1;
	uint8_t TCU_Module : 1;
	uint8_t SRS_Module : 1;
	uint8_t BCS_Module : 1;
	uint8_t EPS_Module : 1;
	uint8_t ALS_Module : 1;
	uint8_t SAS_Module : 1;
	uint8_t unused0 : 2;
} _c_BCM_BCAN_2_msgType;

typedef union _c_BCM_BCAN_2_bufTag
{
	uint8_t _c[2];
	_c_BCM_BCAN_2_msgType BCM_BCAN_2;
} _c_BCM_BCAN_2_buf;

#pragma pack(pop)

extern _c_BCM_TCU_BCS_buf NACU_BCM_TCU_BCS_Rx1;
extern _c_BCM_TCU_BCS_buf NACU_BCM_TCU_BCS_Rx2;
extern _c_BCM_TCU_BCS_buf NACU_BCM_TCU_BCS_Rx3;
extern _c_BCM_TCU_BCS_buf NACU_BCM_TCU_BCS_Rx4;
extern _c_BCM_BCAN_1_buf NACU_BCM_BCAN_1_Rx1;
extern _c_BCM_BCAN_1_buf NACU_BCM_BCAN_1_Rx2;
extern _c_BCM_BCAN_1_buf NACU_BCM_BCAN_1_Rx3;
extern _c_BCM_BCAN_1_buf NACU_BCM_BCAN_1_Rx4;
extern _c_ICM_1_buf NACU_ICM_1_Rx1;
extern _c_ICM_1_buf NACU_ICM_1_Rx2;
extern _c_ICM_1_buf NACU_ICM_1_Rx3;
extern _c_ICM_1_buf NACU_ICM_1_Rx4;
extern _c_BCM_BCAN_2_buf NACU_BCM_BCAN_2_Rx1;
extern _c_BCM_BCAN_2_buf NACU_BCM_BCAN_2_Rx2;
extern _c_BCM_BCAN_2_buf NACU_BCM_BCAN_2_Rx3;
extern _c_BCM_BCAN_2_buf NACU_BCM_BCAN_2_Rx4;

extern uint8_t CanTxMbox1[CAN1_NO_OF_TX_OBJECT];
extern uint32_t CanTxId1[CAN1_NO_OF_TX_OBJECT];
extern uint8_t CanTxDLC1[CAN1_NO_OF_TX_OBJECT];
extern uint8_t * CanTxDataPtr1[CAN1_NO_OF_TX_OBJECT];
extern FuncCanTxCallback CanTxFuncList1[CAN1_NO_OF_TX_OBJECT];

extern uint8_t CanRxMbox1[CAN1_NO_OF_RX_OBJECT];
extern uint32_t CanRxId1[CAN1_NO_OF_RX_OBJECT];
extern uint8_t CanRxDLC1[CAN1_NO_OF_RX_OBJECT];
extern uint8_t * CanRxDataPtr1[CAN1_NO_OF_RX_OBJECT];

extern CAN_MSG_FUNC_ptr Can1_txmsg;
extern CAN_MSG_FUNC_ptr Can1_rxmsg;
extern FuncCanRxCallback CanRxFuncList1[CAN1_NO_OF_RX_OBJECT];

extern _c_BCM_TCU_BCS_buf NACU2_BCM_TCU_BCS_Rx1;
extern _c_BCM_TCU_BCS_buf NACU2_BCM_TCU_BCS_Rx2;
extern _c_BCM_TCU_BCS_buf NACU2_BCM_TCU_BCS_Rx3;
extern _c_BCM_TCU_BCS_buf NACU2_BCM_TCU_BCS_Rx4;
extern _c_BCM_BCAN_1_buf NACU2_BCM_BCAN_1_Rx1;
extern _c_BCM_BCAN_1_buf NACU2_BCM_BCAN_1_Rx2;
extern _c_BCM_BCAN_1_buf NACU2_BCM_BCAN_1_Rx3;
extern _c_BCM_BCAN_1_buf NACU2_BCM_BCAN_1_Rx4;
extern _c_ICM_1_buf NACU2_ICM_1_Rx1;
extern _c_ICM_1_buf NACU2_ICM_1_Rx2;
extern _c_ICM_1_buf NACU2_ICM_1_Rx3;
extern _c_ICM_1_buf NACU2_ICM_1_Rx4;
extern _c_BCM_BCAN_2_buf NACU2_BCM_BCAN_2_Rx1;
extern _c_BCM_BCAN_2_buf NACU2_BCM_BCAN_2_Rx2;
extern _c_BCM_BCAN_2_buf NACU2_BCM_BCAN_2_Rx3;
extern _c_BCM_BCAN_2_buf NACU2_BCM_BCAN_2_Rx4;

extern _c_Clock_buf ECU2_Clock_Tx0;
extern _c_V2V_Warning_buf ECU2_V2V_Warning_Tx1;
extern _c_System_Power_Mode_buf ECU2_ROUTED_System_Power_Mode_Rx0;
extern _c_Blind_Zone_Alert_Status_buf ECU2_ROUTED_Blind_Zone_Alert_Status_Rx1;
extern _c_Drive_Status_buf ECU2_ROUTED_Drive_Status_Rx2;
extern _c_Pedestrain_Friendly_Alert_Status_buf ECU2_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3;

extern _c_System_Power_Mode_buf ECU1_System_Power_Mode_Tx0;
extern _c_Blind_Zone_Alert_Status_buf ECU1_Blind_Zone_Alert_Status_Tx1;
extern _c_V2V_Warning_buf ECU1_ROUTED_V2V_Warning_Rx2;
extern _c_Pedestrain_Friendly_Alert_Status_buf ECU1_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3;
extern _c_Drive_Status_buf ECU1_ROUTED_Drive_Status_Rx1;
extern _c_Clock_buf ECU1_ROUTED_Clock_Rx0;

extern uint8_t CanTxMbox2[CAN3_NO_OF_TX_OBJECT];
extern uint32_t CanTxId2[CAN3_NO_OF_TX_OBJECT];
extern uint8_t CanTxDLC2[CAN3_NO_OF_TX_OBJECT];
extern uint8_t * CanTxDataPtr2[CAN3_NO_OF_TX_OBJECT];
extern FuncCanTxCallback CanTxFuncList2[CAN3_NO_OF_TX_OBJECT];

#if 1
extern uint8_t CanRxMbox2[CAN3_NO_OF_RX_OBJECT];
extern uint32_t CanRxId2[CAN3_NO_OF_RX_OBJECT];
extern uint8_t CanRxDLC2[CAN3_NO_OF_RX_OBJECT];
extern uint8_t * CanRxDataPtr2[CAN3_NO_OF_RX_OBJECT];
#endif

extern CAN_MSG_FUNC_ptr Can3_txmsg;
extern CAN_MSG_FUNC_ptr Can3_rxmsg;
extern FuncCanRxCallback CanRxFuncList2[CAN3_NO_OF_RX_OBJECT];

#endif /* _CAN_PAR_H_ */
