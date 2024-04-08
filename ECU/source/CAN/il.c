#include "Includes.h"

#define	USED_CAN_CHANNEL_NO	2

ilMsgCtrl_t ilMsgCtrl;
can_inst_t ilCanChannel[USED_CAN_CHANNEL_NO] = {CAN_CH_3, CAN_CH_1};	// {CAN, CANFD}

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
				SYSINFO_PRINTF("[%s] CAN Instance Error ...\r\n", __func__);
				assert(0);
			}

			for (cnt=0; cnt<config->msgTx->NoOfMsg; cnt++)
			{
				(*(&config->msgTx->tCallback[cnt]))();
				CAN_Transmit(config->msgTx->inst, config->msgTx->id[cnt]);
			}
		}

		ilMsgCtrl.firstCanStart = OFF;
	}
	else
	{
		for (i=0; i<USED_CAN_CHANNEL_NO; i++)
		{
			config = (can_config_t *) CAN_GetConfigAddr((can_inst_t)ilCanChannel[i]);
			for (cnt=0; cnt<config->msgTx->NoOfMsg; cnt++)
			{
				if (config->msgTx->msgUpdate[cnt] == MSG_UPDATE_REQUEST)
				{
					CAN_Transmit(config->msgTx->inst, config->msgTx->id[cnt]);
					config->msgTx->msgUpdate[cnt] = MSG_UPDATE_COMPLETE;
				}
			}
		}
	}	
}

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
