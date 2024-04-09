#include "Includes.h"

#define MK_STDID(id)		((uint32_t)((uint32_t)(id) << 18))
#define MK_TX_DLC(dlc)		(dlc)

_c_Clock_buf ECU2_Clock_Tx0;
_c_V2V_Warning_buf ECU2_V2V_Warning_Tx1;
_c_System_Power_Mode_buf ECU2_ROUTED_System_Power_Mode_Rx0;
_c_Blind_Zone_Alert_Status_buf ECU2_ROUTED_Blind_Zone_Alert_Status_Rx1;
_c_Drive_Status_buf ECU2_ROUTED_Drive_Status_Rx2;
_c_Pedestrain_Friendly_Alert_Status_buf ECU2_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3;

_c_NACU_Diag_Tx_buf NACU_Diag_Tx1;
_c_NACU_Diag_Tx_buf NACU_Diag_Tx2;
_c_System_Power_Mode_buf ECU1_System_Power_Mode_Tx0;
_c_Blind_Zone_Alert_Status_buf ECU1_Blind_Zone_Alert_Status_Tx1;
_c_NACU_Diag_Tx_buf NACU_Diag_Tx3;
_c_NACU_Diag_Tx_buf NACU_Diag_Tx4;
_c_NACU_Diag_Tx_buf NACU_Diag_Tx5;

_c_BCM_TCU_BCS_buf NACU_BCM_TCU_BCS_Rx1;
_c_BCM_TCU_BCS_buf NACU_BCM_TCU_BCS_Rx2;
_c_BCM_TCU_BCS_buf NACU_BCM_TCU_BCS_Rx3;
_c_BCM_TCU_BCS_buf NACU_BCM_TCU_BCS_Rx4;
_c_BCM_BCAN_1_buf NACU_BCM_BCAN_1_Rx1;
_c_BCM_BCAN_1_buf NACU_BCM_BCAN_1_Rx2;
_c_BCM_BCAN_1_buf NACU_BCM_BCAN_1_Rx3;
_c_BCM_BCAN_1_buf NACU_BCM_BCAN_1_Rx4;
_c_ICM_1_buf NACU_ICM_1_Rx1;
_c_ICM_1_buf NACU_ICM_1_Rx2;
_c_ICM_1_buf NACU_ICM_1_Rx3;
_c_ICM_1_buf NACU_ICM_1_Rx4;
_c_BCM_BCAN_2_buf NACU_BCM_BCAN_2_Rx1;
_c_BCM_BCAN_2_buf NACU_BCM_BCAN_2_Rx2;
_c_BCM_BCAN_2_buf NACU_BCM_BCAN_2_Rx3;
_c_BCM_BCAN_2_buf NACU_BCM_BCAN_2_Rx4;

_c_V2V_Warning_buf ECU1_ROUTED_V2V_Warning_Rx2;
_c_Pedestrain_Friendly_Alert_Status_buf ECU1_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3;
_c_Drive_Status_buf ECU1_ROUTED_Drive_Status_Rx1;
_c_Clock_buf ECU1_ROUTED_Clock_Rx0;

_c_BCM_TCU_BCS_buf NACU2_BCM_TCU_BCS_Rx1;
_c_BCM_TCU_BCS_buf NACU2_BCM_TCU_BCS_Rx2;
_c_BCM_TCU_BCS_buf NACU2_BCM_TCU_BCS_Rx3;
_c_BCM_TCU_BCS_buf NACU2_BCM_TCU_BCS_Rx4;
_c_BCM_BCAN_1_buf NACU2_BCM_BCAN_1_Rx1;
_c_BCM_BCAN_1_buf NACU2_BCM_BCAN_1_Rx2;
_c_BCM_BCAN_1_buf NACU2_BCM_BCAN_1_Rx3;
_c_BCM_BCAN_1_buf NACU2_BCM_BCAN_1_Rx4;
_c_ICM_1_buf NACU2_ICM_1_Rx1;
_c_ICM_1_buf NACU2_ICM_1_Rx2;
_c_ICM_1_buf NACU2_ICM_1_Rx3;
_c_ICM_1_buf NACU2_ICM_1_Rx4;
_c_BCM_BCAN_2_buf NACU2_BCM_BCAN_2_Rx1;
_c_BCM_BCAN_2_buf NACU2_BCM_BCAN_2_Rx2;
_c_BCM_BCAN_2_buf NACU2_BCM_BCAN_2_Rx3;
_c_BCM_BCAN_2_buf NACU2_BCM_BCAN_2_Rx4;


/*******************************************************************************
	CAN 1 (CANFD) Transmit message
 *******************************************************************************/
uint8_t CanTxMbox1[CAN1_NO_OF_TX_OBJECT] =
{
	1,
	2,
	3,
	4,
	5
};

uint32_t CanTxId1[CAN1_NO_OF_TX_OBJECT] =
{
	0x109u,
	0x119u,
	0x513u,
	0x514u,
	0x515u
};

uint8_t CanTxDLC1[CAN1_NO_OF_TX_OBJECT] =
{
	7,
	1,
	8,
	8,
	8
};

uint8_t * CanTxDataPtr1[CAN1_NO_OF_TX_OBJECT] =
{
	(uint8_t *) ECU2_Clock_Tx0._c,
	(uint8_t *) ECU2_V2V_Warning_Tx1._c,
	(uint8_t *) NACU_Diag_Tx3._c,
	(uint8_t *) NACU_Diag_Tx4._c,
	(uint8_t *) NACU_Diag_Tx5._c
};

uint8_t CanTxAttr1[CAN1_NO_OF_TX_OBJECT] =
{
	CAN_TX_ATTR_PERIODIC,
	CAN_TX_ATTR_EVENT,
	CAN_TX_ATTR_EVENT,
	CAN_TX_ATTR_PERIODIC,
	CAN_TX_ATTR_EVENT
};

uint16_t CanTxAttrTime1[CAN1_NO_OF_TX_OBJECT] =
{
	1000,
	0,
	0,
	100,
	0
};

uint16_t Can1TxAtttSTimerId[CAN1_NO_OF_TX_OBJECT] =
{
	STIMER_CAN1_TX_MSG_TIMER_START,
	STIMER_CAN1_TX_MSG_TIMER_START+1,
	STIMER_CAN1_TX_MSG_TIMER_START+2,
	STIMER_CAN1_TX_MSG_TIMER_START+3,
	STIMER_CAN1_TX_MSG_TIMER_START+4,
};

uint8_t Can1SoftTimerState[CAN1_NO_OF_TX_OBJECT] =
{
	CAN_TX_PERI_FUNC_STOP,
	CAN_TX_PERI_FUNC_STOP,
	CAN_TX_PERI_FUNC_STOP,
	CAN_TX_PERI_FUNC_STOP,
	CAN_TX_PERI_FUNC_STOP,
};

uint8_t Can1MsgUpdateState[CAN1_NO_OF_TX_OBJECT] =
{
	MSG_UPDATE_COMPLETE,
	MSG_UPDATE_COMPLETE,
	MSG_UPDATE_COMPLETE,
	MSG_UPDATE_COMPLETE,
	MSG_UPDATE_COMPLETE,
};

CAN_MSG_FUNC_ptr Can1_txmsg =
{
	CAN_CH_1,
	CAN1_NO_OF_TX_OBJECT,
	CanTxMbox1,
	CanTxId1,
	CanTxDLC1,
	CanTxDataPtr1,
	CanTxAttr1,
	CanTxAttrTime1,
	//0,
	Can1TxAtttSTimerId,
	Can1SoftTimerState,
	CanTxFuncList1,
	NULL,
	Can1MsgUpdateState,
};

/*******************************************************************************
	CAN 1 (CANFD) Receive message
 *******************************************************************************/
uint8_t CanRxMbox1[CAN1_NO_OF_RX_OBJECT] =
{
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31
};

uint32_t CanRxId1[CAN1_NO_OF_RX_OBJECT] =
{
	0x10Au,
	0x11Au,
	0x12Au,
	0x13Au,
	0x534u,
	0x535u,
	0x536u,
	0x537u,
	0x538u,
	0x539u,
	0x53Au,
	0x53Bu,
	0x53Cu,
	0x53Du,
	0x53Eu,
	0x53Fu
};

uint8_t CanRxDLC1[CAN1_NO_OF_RX_OBJECT] =
{
	1,
	2,
	3,
	3,
	4,
	4,
	4,
	4,
	7,
	7,
	7,
	7,
	2,
	2,
	2,
	2,
};

uint8_t * CanRxDataPtr1[CAN1_NO_OF_RX_OBJECT] =
{
	(uint8_t *) ECU2_ROUTED_System_Power_Mode_Rx0._c,
	(uint8_t *) ECU2_ROUTED_Blind_Zone_Alert_Status_Rx1._c,
	(uint8_t *) ECU2_ROUTED_Drive_Status_Rx2._c,
	(uint8_t *) ECU2_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3._c,
	(uint8_t *) NACU_BCM_BCAN_1_Rx1._c,
	(uint8_t *) NACU_BCM_BCAN_1_Rx2._c,
	(uint8_t *) NACU_BCM_BCAN_1_Rx3._c,
	(uint8_t *) NACU_BCM_BCAN_1_Rx4._c,
	(uint8_t *) NACU_ICM_1_Rx1._c,
	(uint8_t *) NACU_ICM_1_Rx2._c,
	(uint8_t *) NACU_ICM_1_Rx3._c,
	(uint8_t *) NACU_ICM_1_Rx4._c,
	(uint8_t *) NACU_BCM_BCAN_2_Rx1._c,
	(uint8_t *) NACU_BCM_BCAN_2_Rx2._c,
	(uint8_t *) NACU_BCM_BCAN_2_Rx3._c,
	(uint8_t *) NACU_BCM_BCAN_2_Rx4._c,
};

CAN_MSG_FUNC_ptr Can1_rxmsg =
{
	CAN_CH_1,
	CAN1_NO_OF_RX_OBJECT,
	CanRxMbox1,
	CanRxId1,
	CanRxDLC1,
	CanRxDataPtr1,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	CanRxFuncList1,
	NULL,
};

/*******************************************************************************
	CAN 3 (CAN) Transmit message
 *******************************************************************************/
uint8_t CanTxMbox2[CAN3_NO_OF_TX_OBJECT] =
{
	32,
	33,
	34,
	35,
	36
};

uint32_t CanTxId2[CAN3_NO_OF_TX_OBJECT] =
{
	0x101u,
	0x111u,
	0x121u,
	0x131u,
	0x141u
};

uint8_t CanTxDLC2[CAN3_NO_OF_TX_OBJECT] =
{
	1,
	2,
	8,
	8,
	8
};

uint8_t * CanTxDataPtr2[CAN3_NO_OF_TX_OBJECT] =
{
	(uint8_t *) ECU1_System_Power_Mode_Tx0._c,
	(uint8_t *) ECU1_Blind_Zone_Alert_Status_Tx1._c,
	(uint8_t *) NACU_Diag_Tx3._c,
	(uint8_t *) NACU_Diag_Tx4._c,
	(uint8_t *) NACU_Diag_Tx5._c
};

uint8_t CanTxAttr2[CAN3_NO_OF_TX_OBJECT] =
{
	CAN_TX_ATTR_PERIODIC,
	//CAN_TX_ATTR_PERIODIC,
	CAN_TX_ATTR_EVENT,
	CAN_TX_ATTR_EVENT,
	CAN_TX_ATTR_PERIODIC,
	CAN_TX_ATTR_EVENT
};

uint16_t CanTxAttrTime2[CAN3_NO_OF_TX_OBJECT] =
{
	100,
	0,
	0,
	100,
	0
};

uint16_t Can3TxAtttSTimerId[CAN3_NO_OF_TX_OBJECT] = 
{
	STIMER_CAN3_TX_MSG_TIMER_START,
	STIMER_CAN3_TX_MSG_TIMER_START+1,
	STIMER_CAN3_TX_MSG_TIMER_START+2,
	STIMER_CAN3_TX_MSG_TIMER_START+3,
	STIMER_CAN3_TX_MSG_TIMER_START+4,
};

uint8_t Can3SoftTimerState[CAN3_NO_OF_TX_OBJECT] =
{
	CAN_TX_PERI_FUNC_STOP,
	CAN_TX_PERI_FUNC_STOP,
	CAN_TX_PERI_FUNC_STOP,
	CAN_TX_PERI_FUNC_STOP,
	CAN_TX_PERI_FUNC_STOP,
};

uint8_t Can3MsgUpdateState[CAN1_NO_OF_TX_OBJECT] =
{
	MSG_UPDATE_COMPLETE,
	MSG_UPDATE_COMPLETE,
	MSG_UPDATE_COMPLETE,
	MSG_UPDATE_COMPLETE,
	MSG_UPDATE_COMPLETE,
};

CAN_MSG_FUNC_ptr Can3_txmsg =
{
	CAN_CH_3,
	CAN3_NO_OF_TX_OBJECT,
	CanTxMbox2,
	CanTxId2,
	CanTxDLC2,
	CanTxDataPtr2,
	CanTxAttr2,
	CanTxAttrTime2,
	//0,
	Can3TxAtttSTimerId,
	Can3SoftTimerState,
	CanTxFuncList2,
	NULL,
	Can3MsgUpdateState,
};

/*******************************************************************************
	CAN 3 (CAN) Receive message
 *******************************************************************************/
uint8_t CanRxMbox2[CAN3_NO_OF_RX_OBJECT] =
{
	 37,
	 38,
	 39,
	 49,
	 50,
	 51,
	 52,
	 53,
	 54,
	 55,
	 56,
	 57,
	 58,
	 59,
	 50,
	 61
};

uint32_t CanRxId2[CAN3_NO_OF_RX_OBJECT] =
{
	 0x102u,
	 0x112u,
	 0x122u,
	 0x132u,
	 0x634u,
	 0x635u,
	 0x636u,
	 0x637u,
	 0x638u,
	 0x639u,
	 0x63Au,
	 0x63Bu,
	 0x63Cu,
	 0x63Du,
	 0x63Eu,
	 0x63Fu
};

uint8_t CanRxDLC2[CAN3_NO_OF_RX_OBJECT] =
{
	 7,
	 3,
	 1,
	 3,
	 4,
	 4,
	 4,
	 4,
	 7,
	 7,
	 7,
	 7,
	 2,
	 2,
	 2,
	 2,
};

uint8_t * CanRxDataPtr2[CAN3_NO_OF_RX_OBJECT] =
{
	 (uint8_t *) ECU1_ROUTED_Clock_Rx0._c,
	 (uint8_t *) ECU1_ROUTED_Drive_Status_Rx1._c,
	 (uint8_t *) ECU1_ROUTED_V2V_Warning_Rx2._c,
	 (uint8_t *) ECU1_ROUTED_Pedestrain_Friendly_Alert_Status_Rx3._c,
	 (uint8_t *) NACU2_BCM_BCAN_1_Rx1._c,
	 (uint8_t *) NACU2_BCM_BCAN_1_Rx2._c,
	 (uint8_t *) NACU2_BCM_BCAN_1_Rx3._c,
	 (uint8_t *) NACU2_BCM_BCAN_1_Rx4._c,
	 (uint8_t *) NACU2_ICM_1_Rx1._c,
	 (uint8_t *) NACU2_ICM_1_Rx2._c,
	 (uint8_t *) NACU2_ICM_1_Rx3._c,
	 (uint8_t *) NACU2_ICM_1_Rx4._c,
	 (uint8_t *) NACU2_BCM_BCAN_2_Rx1._c,
	 (uint8_t *) NACU2_BCM_BCAN_2_Rx2._c,
	 (uint8_t *) NACU2_BCM_BCAN_2_Rx3._c,
	 (uint8_t *) NACU2_BCM_BCAN_2_Rx4._c,
};

CAN_MSG_FUNC_ptr Can3_rxmsg =
{
	 CAN_CH_3,
	 CAN3_NO_OF_RX_OBJECT,
	 CanRxMbox2,
	 CanRxId2,
	 CanRxDLC2,
	 CanRxDataPtr2,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 NULL,
	 CanRxFuncList2,
	 NULL,
};
