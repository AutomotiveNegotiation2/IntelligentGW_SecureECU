#include "fsl_flexcan.h"
#include "clock_config.h"

#include "Includes.h"

/* Select OSC24Mhz as master flexcan clock source */
#define FLEXCAN_CLOCK_SOURCE_SELECT (1U)
/* Clock divider for master flexcan clock source */
#define FLEXCAN_CLOCK_SOURCE_DIVIDER (1U)
#define USE_IMPROVED_TIMING_CONFIG (1U)
#define BYTES_IN_MB	kFLEXCAN_8BperMB

clock_root_t can_clk[] = {(clock_root_t)0, kCLOCK_Root_Can1, kCLOCK_Root_Can2, kCLOCK_Root_Can3};

flexcan_mb_transfer_t txXfer, rxXfer;

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
		.frame		= NULL,
		.callback	= flexcan_1_callback,
		.msgRx		= &Can1_rxmsg,
		.msgTx		= &Can1_txmsg,
	},
	{
		.base		= NULL,
	},
	{
		.base		= CAN3,
		.baudRate	= 500000U,
		.baudRateFD	= NULL,
		.maxMbNum	= 64,
		.fdEnable	= 0,
		.framefd	= NULL,
		.frame		=
		{
			.format	= kFLEXCAN_FrameFormatStandard,
			.type	= kFLEXCAN_FrameTypeData,
		},
		.callback	= flexcan_3_callback,
		.msgRx		= &Can3_rxmsg,
		.msgTx		= &Can3_txmsg,
	}	
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
		SYSINFO_PRINTF("[%s] register memory is not assigned normally ...\r\n", __func__);
		assert(0);
	}

	mbConfig.format = config->frame.format;
	mbConfig.type = config->frame.type;

	for (i=0; i<config->msgRx->NoOfMsg; i++)
	{
		mbConfig.id = FLEXCAN_ID_STD(config->msgRx->id[i]);
		if (config->fdEnable)
			FLEXCAN_SetFDRxMbConfig(config->base, config->msgRx->mbox[i], &mbConfig, true);
		else
			FLEXCAN_SetRxMbConfig(config->base, config->msgRx->mbox[i], &mbConfig, true);
	}
}

static void FLEXCAN_ConfigTxMsg(can_config_t * config)
{
	uint8_t i;

	if (config == NULL)
	{
		SYSINFO_PRINTF("[%s] register memory is not assigned normally ...\r\n", __func__);
		assert(0);
	}

	for (i=0; i<config->msgTx->NoOfMsg; i++)
	{
		if (config->fdEnable)
			FLEXCAN_SetFDTxMbConfig(config->base, config->msgTx->mbox[i], true);
		else
			FLEXCAN_SetTxMbConfig(config->base, config->msgTx->mbox[i], true);
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
	        SYSINFO_PRINTF("No found Improved Timing Configuration. Just used default configuration\r\n\r\n");
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
	        SYSINFO_PRINTF("No found Improved Timing Configuration. Just used default configuration\r\n\r\n");
	    }
	}
#endif
}

int32_t CAN_Transmit(can_inst_t instance, uint32_t id)
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

	txXfer.mbIdx = config->msgTx->mbox[i];

	if (config->fdEnable)
	{
		txXfer.framefd = &config->framefd;
		txXfer.framefd->id = FLEXCAN_ID_STD(id);
		txXfer.framefd->length = config->msgTx->dlc[i];

		(void)FLEXCAN_TransferFDSendNonBlocking(config->base, &config->fCanHandle, &txXfer);
	}
	else
	{
		txXfer.frame = &config->frame;
		txXfer.frame->id = FLEXCAN_ID_STD(id);
		txXfer.frame->length = config->msgTx->dlc[i];

		FLEXCAN_TransferSendNonBlocking(config->base, &config->fCanHandle, &txXfer);
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

	for (i=0; i<config->msgRx->NoOfMsg; i++)
	{
		rxXfer.mbIdx = config->msgRx->mbox[i];
		if (config->fdEnable)
		{
			rxXfer.framefd->length = config->msgRx->dlc[i];
			rxXfer.framefd->id = config->msgRx->id[i];
			(void)FLEXCAN_TransferFDReceiveNonBlocking(config->base, &config->fCanHandle, &rxXfer);
		}
		else
		{
			rxXfer.frame->length = config->msgRx->dlc[i];
			rxXfer.frame->id = config->msgRx->id[i];
			(void)FLEXCAN_TransferReceiveNonBlocking(config->base, &config->fCanHandle, &rxXfer);
		}
	}
}

static int32_t CAN_Receive(uint32_t instance, uint32_t buffIdx, flexcan_mb_transfer_t *xfer)
{
	uint8_t i, data[64];
	can_config_t * config;
	status_t result;
	
	config = (can_config_t *)CAN_GetConfigAddr(instance);

	for (i=0; i<config->msgRx->NoOfMsg; i++) 
	{
		if (config->msgRx->mbox[i] == buffIdx)
		{
			break;
		}
	}

	if (i >= config->msgRx->NoOfMsg)
	{
		// error
		//SYSINFO_PRINTF("[%s] mailbox id is over maximum rx message.\r\n", __func__, rxmsg, frame);
		assert(0);
	}

	xfer->mbIdx = (uint8_t)buffIdx;
	if (config->fdEnable)
	{
		uint8_t len;
		
		result = FLEXCAN_TransferFDReceiveNonBlocking(config->base, &config->fCanHandle, xfer);

		config->msgRx->dlc[i] = xfer->framefd->length;

		if (xfer->framefd->length%4)
			len = (xfer->framefd->length/4)+1;
		else
			len = xfer->framefd->length;

		for (uint8_t j=0; j<len; j++)
		{
			data[j*4] = (uint8_t)(config->framefd.dataWord[j]>>24);
			data[j*4+1] = (uint8_t)(config->framefd.dataWord[j]>>16);
			data[j*4+2] = (uint8_t)(config->framefd.dataWord[j]>>8);
			data[j*4+3] = (uint8_t)(config->framefd.dataWord[j]);
		}

		memcpy(*(config->msgRx->data+i), data, xfer->framefd->length);
	}
	else
	{
		result = FLEXCAN_TransferReceiveNonBlocking(config->base, &config->fCanHandle, xfer);
		
		config->msgRx->dlc[i] = xfer->frame->length;

		data[0] = (uint8_t)xfer->frame->dataByte0;
		data[1] = (uint8_t)xfer->frame->dataByte1;
		data[2] = (uint8_t)xfer->frame->dataByte2;
		data[3] = (uint8_t)xfer->frame->dataByte3;

		if (xfer->frame->length > 4)
		{
			data[4] = (uint8_t)xfer->frame->dataByte4;
			data[5] = (uint8_t)xfer->frame->dataByte5;
			data[6] = (uint8_t)xfer->frame->dataByte6;
			data[7] = (uint8_t)xfer->frame->dataByte7;
		}

		memcpy(config->msgRx->data[i], data, xfer->frame->length);
	}

#if 0
	SYSINFO_PRINTF("[%s] length=0x%X, data=0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X\r\n", __func__, 
		frame->length, frame->dataByte0, frame->dataByte1, frame->dataByte2, frame->dataByte3, 
		frame->dataByte4, frame->dataByte5, frame->dataByte6, frame->dataByte7);
#endif

	(config->msgRx->rCallback[i])(config->msgRx->data[i], config->msgRx->dlc[i]);

	return 0;
}

uint32_t CAN_GetConfigAddr(can_inst_t instance)
{
	if ((instance != CAN_CH_3) && (instance != CAN_CH_1))
	{
		SYSINFO_PRINTF("[%s] CAN Instance Error ...\r\n", __func__);
		assert(0);
	}

	return (uint32_t)(&can_config[instance]);
}

void CAN3_TX_Test(void)
{
	uint8_t i;
	
	for (i=0; i<CAN3_NO_OF_TX_OBJECT; i++)
	{
		CAN_Transmit(CAN_CH_3, CanTxId2[i]);
	}
}

void CAN1_TX_Test(void)
{
	uint8_t i;
	
	for (i=0; i<CAN1_NO_OF_TX_OBJECT; i++)
	{
		CAN_Transmit(CAN_CH_1, CanTxId1[i]);
	}
}

