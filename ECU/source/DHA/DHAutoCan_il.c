#include "Includes.h"

#if ((CAN3toCAN_EN == ON) && (CAN1toCANFD_EN == ON))
#define	USED_CAN_CHANNEL_NO	2

can_inst_t ilCanChannel[USED_CAN_CHANNEL_NO] = {CAN_CH_3, CAN_CH_1};	// {CAN, CANFD}
#else
#define	USED_CAN_CHANNEL_NO	1

#if (CAN3toCAN_EN == ON)
can_inst_t ilCanChannel[USED_CAN_CHANNEL_NO] = {CAN_CH_3};	// {CAN}
#else
can_inst_t ilCanChannel[USED_CAN_CHANNEL_NO] = {CAN_CH_1};	// {CANFD}
#endif

#endif

ilMsgCtrl_t ilMsgCtrl;

#if (DEBUG_CAN == ON)
void ilMsgTxLog(can_inst_t inst, uint32_t id, uint8_t dlc, uint8_t * data);
#endif

void ilTxTask(void)
{
	uint8_t i, cnt;
	can_config_t * config;

	if (ilMsgCtrl.firstCanStart == ON)
	{
		for (i=0; i<USED_CAN_CHANNEL_NO; i++)
		{
			config = (can_config_t *) CAN_GetConfigAddr((can_inst_t)ilCanChannel[i]);

			if (config->base == NULL)
			{
				ENETINFO_PRINTF("[%s] CAN Instance Error ...\r\n", __func__);
				assert(0);
			}

			for (cnt=0; cnt<((CAN_MSG_FUNC_ptr *)config->msgTx)->NoOfMsg; cnt++)
			{
				(*(&((CAN_MSG_FUNC_ptr *)config->msgTx)->tCallback[cnt]))();
				CAN_Transmit(((CAN_MSG_FUNC_ptr *)config->msgTx)->inst, ((CAN_MSG_FUNC_ptr *)config->msgTx)->id[cnt]);
			}
		}

		ilMsgCtrl.firstCanStart = OFF;
	}
	else
	{
		for (i=0; i<USED_CAN_CHANNEL_NO; i++)
		{
			config = (can_config_t *) CAN_GetConfigAddr((can_inst_t)ilCanChannel[i]);

			for (cnt=0; cnt<((CAN_MSG_FUNC_ptr *)config->msgTx)->NoOfMsg; cnt++)
			{
				if (((CAN_MSG_FUNC_ptr *)config->msgTx)->msgUpdate[cnt] == MSG_UPDATE_REQUEST)
				{
					CAN_Transmit(((CAN_MSG_FUNC_ptr *)config->msgTx)->inst, ((CAN_MSG_FUNC_ptr *)config->msgTx)->id[cnt]);
					//IOCTRL_SetLedOpForTx((uint8_t)ilCanChannel[i], ptr->msgTx->attr[cnt]);
					((CAN_MSG_FUNC_ptr *)config->msgTx)->msgUpdate[cnt] = MSG_UPDATE_COMPLETE;
				}
			}
		}
	}
}

#if (DEBUG_CAN == ON)
void ilMsgTxLog(can_inst_t inst, uint32_t id, uint8_t dlc, uint8_t * data)
{
	uint8_t buf[10]={0,};
	
	if (inst == CAN_CH_3)
	{
		sprintf(buf, "CAN");
	}
	else if (inst == CAN_CH_1)
	{
		sprintf(buf, "CANFD");
	}
	else
	{
		sprintf(buf, "INVAL");
	}

	CANINFO_PRINTF("[TX] %05s ID=0x%x, DLC=%d DATA=", buf, id, dlc);
	for (uint8_t i=0; i<dlc; i++)
	{
		CANINFO_PRINTF("0x%x ", data[i]);
	}
	CANINFO_PRINTF("\r\n");
}
#endif

bool ilGetFirstCanOpStatus(void)
{
	return ilMsgCtrl.firstCanStart;
}

void ilInit(void)
{
	memset(&ilMsgCtrl, 0, sizeof(ilMsgCtrl_t));
}

void ilStart(void)
{
	ilMsgCtrl.firstCanStart = ON;
}

void Debug_ilRxTask(void)
{
	QueuePopCanDataforRx2();
}

#if 0
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
#endif

