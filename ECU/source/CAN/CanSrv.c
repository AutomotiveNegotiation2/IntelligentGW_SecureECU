#include "pin_mux.h"
#include "Includes.h"

static void CanTransOperationMode(can_inst_t instance, can_trans_opmode_t opmode);
static void CAN_ACC_ON_Init(void);
static inline uint8_t CanPowerIsEnabled(void);
static void RUN_CAN_ACC_ON(void);
static void RUN_CAN_ACC_OFF(void);

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
			RUN_CAN_ACC_OFF();
			break;

		case GB_SEQ_UP_ACC_ON:
			RUN_CAN_ACC_ON();
			break;

		case GB_SEQ_ACC_ON:
			break;

		default:
			break;
	}
}

static void RUN_CAN_ACC_ON(void)
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
			
			CAN_ACC_ON_Init();
			
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
			CAN3_TX_Test();
			CAN1_TX_Test();

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

static void RUN_CAN_ACC_OFF(void)
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

static void CAN_ACC_ON_Init(void)
{

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

