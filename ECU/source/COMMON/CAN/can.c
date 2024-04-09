#include "Includes.h"

/* Select OSC24Mhz as master flexcan clock source */
#define FLEXCAN_CLOCK_SOURCE_SELECT (1U)
/* Clock divider for master flexcan clock source */
#define FLEXCAN_CLOCK_SOURCE_DIVIDER (1U)
#define USE_IMPROVED_TIMING_CONFIG (1U)
#define BYTES_IN_MB	kFLEXCAN_8BperMB

clock_root_t can_clk[] = {(clock_root_t)0, kCLOCK_Root_Can1, kCLOCK_Root_Can2, kCLOCK_Root_Can3};

flexcan_mb_transfer_t txXfer, rxXfer;

CanRxFuncCallback CanRxCallback[ORGAN_MAX] = {NULL, };
CanTxFuncCallback CanTxCallback[ORGAN_MAX] = {NULL, };

static FLEXCAN_CALLBACK(flexcan_3_callback);
static FLEXCAN_CALLBACK(flexcan_1_callback);
static void FLEXCAN_CalculateClock(can_config_t * config, flexcan_config_t * flexcanConfig, uint32_t clock);
static void FLEXCAN_ConfigTxMsg(can_config_t * config);
static void FLEXCAN_ConfigRxMsg(can_config_t * config);
static int32_t CAN_Receive(uint32_t instance, uint32_t buffIdx, flexcan_mb_transfer_t *xfer);

can_config_t can_config[CAN_CH_MAX] = {
	{
		.base		= NULL,
	},
	{
#if (CAN1toCANFD_EN == ON)
		.base		= CAN1,
		.baudRate	= 1000000U,
		.baudRateFD	= 2000000U,
		.maxMbNum	= 64,
		.fdEnable	= 1,
		.framefd	=
		{
			.format	= kFLEXCAN_FrameFormatStandard,
			.type	= kFLEXCAN_FrameTypeData,
			.brs	= 1,
		},
		//.frame		= NULL,
		.callback	= flexcan_3_callback,
		.msgRx		= /*&Can1_rxmsg*/NULL,
		.msgTx		= /*&Can1_txmsg*/NULL,
#else
		.base		= NULL,
#endif
	},
	{
		.base		= NULL,
	},
	{
#if (CAN3toCAN_EN == ON)
		.base		= CAN3,
		.baudRate	= 500000U,
		.baudRateFD	= (uint32_t)NULL,
		.maxMbNum	= 64,
		.fdEnable	= 0,
		//.framefd	= NULL,
		.frame		=
		{
			.format	= kFLEXCAN_FrameFormatStandard,
			.type	= kFLEXCAN_FrameTypeData,
		},
		.callback	= flexcan_3_callback,
		.msgRx		= /*&Can3_rxmsg*/NULL,
		.msgTx		= /*&Can3_txmsg*/NULL,
#else
		.base		= NULL,
#endif
	}	
};

canTransFnCallback CanFnCtrl[CAN_CH_MAX] = {
	{
		.Standby	= NULL,
		.Normal		= NULL,
	},
	{
#if (CAN1toCANFD_EN == ON)
		.Standby	= CAN1_TRANS_TO_STANDBY_MODE,
		.Normal		= CAN1_TRANS_TO_NORMAL_MODE,
#else
		.Standby	= NULL,
		.Normal 	= NULL,
#endif
	},
	{
		.Standby	= NULL,
		.Normal		= NULL,
	},
	{
#if (CAN3toCAN_EN == ON)
		.Standby	= CAN3_TRANS_TO_STANDBY_MODE,
		.Normal		= CAN3_TRANS_TO_NORMAL_MODE,
#else
		.Standby	= NULL,
		.Normal 	= NULL,
#endif
	},
};

static FLEXCAN_CALLBACK(flexcan_3_callback)
{
	uint32_t instance;
	can_config_t * config;

	instance = FLEXCAN_GetInstance(base);
	config = (can_config_t *)CAN_GetConfigAddr(instance);
	
    switch (status)
    {
        case kStatus_FLEXCAN_RxIdle:
			CAN_Receive(instance, result, &rxXfer);
            break;

        case kStatus_FLEXCAN_TxIdle:
            break;

        case kStatus_FLEXCAN_WakeUp:
            //wakenUp = true;
            break;

        default:
            break;
    }
}

static FLEXCAN_CALLBACK(flexcan_1_callback)
{
	uint32_t instance;
	can_config_t * config;

	instance = FLEXCAN_GetInstance(base);
	config = (can_config_t *)CAN_GetConfigAddr(instance);
	
    switch (status)
    {
        case kStatus_FLEXCAN_RxIdle:
			CAN_Receive(instance, result, &rxXfer);
            break;

        case kStatus_FLEXCAN_TxIdle:
            break;

        case kStatus_FLEXCAN_WakeUp:
            //wakenUp = true;
            break;

        default:
            break;
    }
}

void CAN_Init(can_inst_t instance)
{
	can_config_t * config;
	flexcan_config_t flexcanConfig;
	uint32_t calculated_can_clk;

	config = (can_config_t *)CAN_GetConfigAddr(instance);

	/*Clock setting for FLEXCAN*/
	clock_root_config_t rootCfg = {0};
	rootCfg.mux 				= FLEXCAN_CLOCK_SOURCE_SELECT;
	rootCfg.div 				= FLEXCAN_CLOCK_SOURCE_DIVIDER;
	CLOCK_SetRootClock(can_clk[instance], &rootCfg);

	memset(&config->fCanHandle, 0, sizeof(flexcan_handle_t));

	FLEXCAN_GetDefaultConfig(&flexcanConfig);
	
	/* Setup CAN baud rate. */
	flexcanConfig.baudRate = config->baudRate;
	/* Setup MAX mailbox number */
	flexcanConfig.maxMbNum = config->maxMbNum;

	calculated_can_clk = (CLOCK_GetRootClockFreq(can_clk[FLEXCAN_GetInstance(config->base)]) / 100000U) * 100000U;
	FLEXCAN_CalculateClock(config, &flexcanConfig, calculated_can_clk);

	if (config->fdEnable)
		FLEXCAN_FDInit(config->base, &flexcanConfig, calculated_can_clk, BYTES_IN_MB, true);
	else
		FLEXCAN_Init(config->base, &flexcanConfig, calculated_can_clk);

	/* Create FlexCAN handle structure and set call back function. */
	FLEXCAN_TransferCreateHandle(config->base, &config->fCanHandle, config->callback, NULL);

	/* Setup Rx Message Buffer. */
	FLEXCAN_ConfigRxMsg(config);
	/* Setup Tx Message Buffer. */
	FLEXCAN_ConfigTxMsg(config);
}

static void FLEXCAN_ConfigRxMsg(can_config_t * config)
{
	uint8_t i;
	flexcan_rx_mb_config_t mbConfig;

	if (config == NULL)
	{
		COMMON_PRINTF("[%s] register memory is not assigned normally ...\r\n", __func__);
		assert(0);
	}

	mbConfig.format = config->frame.format;
	mbConfig.type = config->frame.type;

	for (i=0; i<((CAN_MSG_FUNC_ptr *)config->msgRx)->NoOfMsg; i++)
	{
		mbConfig.id = FLEXCAN_ID_STD(((CAN_MSG_FUNC_ptr *)config->msgRx)->id[i]);
		if (config->fdEnable)
			FLEXCAN_SetFDRxMbConfig(config->base, ((CAN_MSG_FUNC_ptr *)config->msgRx)->mbox[i], &mbConfig, true);
		else
			FLEXCAN_SetRxMbConfig(config->base, ((CAN_MSG_FUNC_ptr *)config->msgRx)->mbox[i], &mbConfig, true);
	}
}

static void FLEXCAN_ConfigTxMsg(can_config_t * config)
{
	uint8_t i;

	if (config == NULL)
	{
		COMMON_PRINTF("[%s] register memory is not assigned normally ...\r\n", __func__);
		assert(0);
	}

	for (i=0; i<((CAN_MSG_FUNC_ptr *)config->msgTx)->NoOfMsg; i++)
	{
		if (config->fdEnable)
			FLEXCAN_SetFDTxMbConfig(config->base, ((CAN_MSG_FUNC_ptr *)config->msgTx)->mbox[i], true);
		else
			FLEXCAN_SetTxMbConfig(config->base, ((CAN_MSG_FUNC_ptr *)config->msgTx)->mbox[i], true);
	}
}

static void FLEXCAN_CalculateClock(can_config_t * config, flexcan_config_t * flexcanConfig, uint32_t clock)
{
	#if (defined(USE_IMPROVED_TIMING_CONFIG) && USE_IMPROVED_TIMING_CONFIG)
    flexcan_timing_config_t timing_config;
    memset(&timing_config, 0, sizeof(flexcan_timing_config_t));

	if (config->fdEnable)
	{
		if (FLEXCAN_FDCalculateImprovedTimingValues(config->base, flexcanConfig->baudRate, flexcanConfig->baudRateFD, clock, &timing_config))
	    {
	        /* Update the improved timing configuration*/
	        memcpy(&(flexcanConfig->timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
	    }
	    else
	    {
	        COMMON_PRINTF("No found Improved Timing Configuration. Just used default configuration\r\n\r\n");
	    }
	}
	else
	{
		if (FLEXCAN_CalculateImprovedTimingValues(config->base, flexcanConfig->baudRate, clock, &timing_config))
	    {
	        /* Update the improved timing configuration*/
	        memcpy(&(flexcanConfig->timingConfig), &timing_config, sizeof(flexcan_timing_config_t));
	    }
	    else
	    {
	        COMMON_PRINTF("No found Improved Timing Configuration. Just used default configuration\r\n\r\n");
	    }
	}
#endif
}

int32_t CAN_Transmit(can_inst_t instance, uint32_t id)
{
	uint8_t no, i, dlc;
	can_config_t * config;

	config = (can_config_t *)CAN_GetConfigAddr(instance);
	
	for (no=0; no<((CAN_MSG_FUNC_ptr *)config->msgTx)->NoOfMsg; no++)
	{
		if (id == ((CAN_MSG_FUNC_ptr *)config->msgTx)->id[no])
		{
			break;
		}
	}

	if (no >= ((CAN_MSG_FUNC_ptr *)config->msgTx)->NoOfMsg)
	{
		COMMON_PRINTF("[%s] CAN ID[0x%X] is not matched.\n", __func__, id);
		assert(0);
	}

	txXfer.mbIdx = ((CAN_MSG_FUNC_ptr *)config->msgTx)->mbox[no];

	if (config->fdEnable)
	{
		uint8_t len;
		
		txXfer.framefd = &config->framefd;
		txXfer.framefd->id = FLEXCAN_ID_STD(id);
		txXfer.framefd->length = ((CAN_MSG_FUNC_ptr *)config->msgTx)->dlc[no];
		dlc = ((CAN_MSG_FUNC_ptr *)config->msgTx)->dlc[no];

		len = (uint8_t)(dlc/4);
		if (dlc%4)
			len += 1;

		for (i=0; i<len; i++)
		{
			txXfer.framefd->dataWord[i] = (uint32_t)(((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][i*4])<<24;
			txXfer.framefd->dataWord[i] += (uint32_t)(((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][i*4+1])<<16;
			txXfer.framefd->dataWord[i] += (uint32_t)(((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][i*4+2])<<8;
			txXfer.framefd->dataWord[i] += (uint32_t)(((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][i*4+3]);
		}

		(void)FLEXCAN_TransferFDSendNonBlocking(config->base, &config->fCanHandle, &txXfer);
	}
	else
	{
		txXfer.frame = &config->frame;
		txXfer.frame->id = FLEXCAN_ID_STD(id);
		txXfer.frame->length = ((CAN_MSG_FUNC_ptr *)config->msgTx)->dlc[no];
		dlc = ((CAN_MSG_FUNC_ptr *)config->msgTx)->dlc[no];

		txXfer.frame->dataByte0 = ((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][0];
		txXfer.frame->dataByte1 = ((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][1];
		txXfer.frame->dataByte2 = ((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][2];
		txXfer.frame->dataByte3 = ((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][3];

		if (dlc > 4)
		{
			txXfer.frame->dataByte4 = ((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][4];
			txXfer.frame->dataByte5 = ((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][5];
			txXfer.frame->dataByte6 = ((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][6];
			txXfer.frame->dataByte7 = ((CAN_MSG_FUNC_ptr *)config->msgTx)->data[no][7];
		}

		FLEXCAN_TransferSendNonBlocking(config->base, &config->fCanHandle, &txXfer);
	}

	for (i=0; i<ORGAN_MAX; i++)
	{
		if (CanTxCallback[i] != NULL)
			(*CanTxCallback[i])(config->msgTx, no);
	}

	return 0;
}

void CAN_ReceiveStart(can_inst_t instance)
{
	uint8_t i;
	can_config_t * config;
	
	config = (can_config_t *)CAN_GetConfigAddr(instance);

	memset(&rxXfer, 0, sizeof(flexcan_mb_transfer_t));

	if (config->fdEnable)
		rxXfer.framefd = &config->framefd;
	else
		rxXfer.frame = &config->frame;

	for (i=0; i<((CAN_MSG_FUNC_ptr *)config->msgRx)->NoOfMsg; i++)
	{
		rxXfer.mbIdx = ((CAN_MSG_FUNC_ptr *)config->msgRx)->mbox[i];
		if (config->fdEnable)
		{
			rxXfer.framefd->length = ((CAN_MSG_FUNC_ptr *)config->msgRx)->dlc[i];
			rxXfer.framefd->id = ((CAN_MSG_FUNC_ptr *)config->msgRx)->id[i];
			(void)FLEXCAN_TransferFDReceiveNonBlocking(config->base, &config->fCanHandle, &rxXfer);
		}
		else
		{
			rxXfer.frame->length = ((CAN_MSG_FUNC_ptr *)config->msgRx)->dlc[i];
			rxXfer.frame->id = ((CAN_MSG_FUNC_ptr *)config->msgRx)->id[i];
			(void)FLEXCAN_TransferReceiveNonBlocking(config->base, &config->fCanHandle, &rxXfer);
		}
	}
}

static int32_t CAN_Receive(uint32_t instance, uint32_t buffIdx, flexcan_mb_transfer_t *xfer)
{
	uint8_t no, i, data[64], dlc;
	uint32_t id;
	can_config_t * config;
	status_t result;
	
	config = (can_config_t *)CAN_GetConfigAddr(instance);

	for (no=0; no<((CAN_MSG_FUNC_ptr *)config->msgRx)->NoOfMsg; no++) 
	{
		if (((CAN_MSG_FUNC_ptr *)config->msgRx)->mbox[no] == buffIdx)
		{
			break;
		}
	}

	if (no >= ((CAN_MSG_FUNC_ptr *)config->msgRx)->NoOfMsg)
	{
		// error
		//COMMON_PRINTF("[%s] mailbox id is over maximum rx message.\r\n", __func__, rxmsg, frame);
		assert(0);
	}

	xfer->mbIdx = (uint8_t)buffIdx;
	if (config->fdEnable)
	{
		uint8_t len;
		
		xfer->framefd = &config->framefd;
		result = FLEXCAN_TransferFDReceiveNonBlocking(config->base, &config->fCanHandle, xfer);

		dlc = config->framefd.length;
		id = (config->framefd.id >> CAN_ID_STD_SHIFT) & 0x1FFFFFFFU;

		len = (uint8_t)(dlc/4);
		if (dlc%4)
			len += 1;

		for (i=0; i<len; i++)
		{
			data[i*4] = (uint8_t)(config->framefd.dataWord[i]>>24);
			data[i*4+1] = (uint8_t)(config->framefd.dataWord[i]>>16);
			data[i*4+2] = (uint8_t)(config->framefd.dataWord[i]>>8);
			data[i*4+3] = (uint8_t)(config->framefd.dataWord[i]);
		}
	}
	else
	{
		xfer->frame = &config->frame;
		result = FLEXCAN_TransferReceiveNonBlocking(config->base, &config->fCanHandle, xfer);
		
		dlc = config->frame.length;
		id = (config->frame.id >> CAN_ID_STD_SHIFT) & 0x7FFU;

		data[0] = (uint8_t)config->frame.dataByte0;
		data[1] = (uint8_t)config->frame.dataByte1;
		data[2] = (uint8_t)config->frame.dataByte2;
		data[3] = (uint8_t)config->frame.dataByte3;

		if (dlc > 4)
		{
			data[4] = (uint8_t)config->frame.dataByte4;
			data[5] = (uint8_t)config->frame.dataByte5;
			data[6] = (uint8_t)config->frame.dataByte6;
			data[7] = (uint8_t)config->frame.dataByte7;
		}
	}

	for (i=0; i<ORGAN_MAX; i++)
	{
		if (CanRxCallback[i] != NULL)
			(*CanRxCallback[i])(config->msgRx, no, id, dlc, data);
	}

	return 0;
}

uint32_t CAN_GetConfigAddr(can_inst_t instance)
{
	if ((instance != CAN_CH_3) && (instance != CAN_CH_1))
	{
		COMMON_PRINTF("[%s] CAN Instance Error ...\r\n", __func__);
		assert(0);
	}

	return (uint32_t)(&can_config[instance]);
}

void CanTransOperationMode(can_inst_t instance, can_trans_opmode_t opmode)
{
	canTransFnCallback * ctrl;

	ctrl = &CanFnCtrl[instance];
	
	switch (opmode)
	{
		case CAN_TRANS_OPMODE_STANDBY:
			ctrl->Standby();
			COMMON_PRINTF("[%s] CAN_%d_TRANS_OPMODE_STANDBY Operation ...\r\n", __func__, instance);
			break;

		case CAN_TRANS_OPMODE_NORMAL:
			ctrl->Normal();
			COMMON_PRINTF("[%s] CAN_%d_TRANS_OPMODE_NORMAL Operation ...\r\n", __func__, instance);
			break;

		default:
			break;
	}
}

void CanRxCallback_Register(organ_t organ, void * callback)
{
	CanRxCallback[organ] = callback;
}

void CanRxCallback_Clear(organ_t organ)
{
	CanRxCallback[organ] = NULL;
}

void CanTxCallback_Register(organ_t organ, void * callback)
{
	CanTxCallback[organ] = callback;
}

void CanTxCallback_Clear(organ_t organ)
{
	CanTxCallback[organ] = NULL;
}

