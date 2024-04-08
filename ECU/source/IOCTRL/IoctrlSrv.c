#include "Includes.h"

#define	ReadBtnKey()		GPIO_PinRead(BOARD_INITPINS_USER_BUTTON_GPIO, BOARD_INITPINS_USER_BUTTON_GPIO_PIN)
#define	KEY_PRESSED		0
#define	KEY_RELEASED	1

typedef struct {
	uint8_t keyChattTimer;
	bool keyPressedOnFlag;
	bool keyReleasedOnFlag;
	bool keyChatStartFlag;
} key_detect_ctrl_t;

key_detect_ctrl_t keyCtrl;

void RUN_IOCTRL_DN_ACC_OFF(void);
void RUN_IOCTRL_UP_ACC_ON(void);
void Ioctrl_KeyOp(void);

void IoctrlSrv(void)
{
	switch(GlobalPocSeq.GSeq)
	{
		case GB_SEQ_UP_ACC_OFF:
			if(GlobalPocSeq.LSeq.B.SEQ_IOCTRL == LO_SEQ_START)
			{
				GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_FINISH;
			}
			break;

		case GB_SEQ_ACC_OFF:
			break;

		case GB_SEQ_DN_ACC_OFF:
			RUN_IOCTRL_DN_ACC_OFF();
			break;

		case GB_SEQ_UP_ACC_ON:
			RUN_IOCTRL_UP_ACC_ON();
			break;

		case GB_SEQ_ACC_ON:
			break;

		default:
			break;
	}
}

void RUN_IOCTRL_DN_ACC_OFF(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_IOCTRL)
	{
		case LO_SEQ_START:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_START;
			// error
			IOCTRLINFO_PRINTF("[%s] IOCTRL Sequence Error\n", __func__);
			break;
	}
}

void RUN_IOCTRL_UP_ACC_ON(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_IOCTRL)
	{
		case LO_SEQ_START:
			KillSoftTimer(STIMER_IOCTRL_USER_KEY_OP);
			
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			InitRTC();
			
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			memset(&keyCtrl, 0, sizeof(key_detect_ctrl_t));
			SetSoftTimer(STIMER_IOCTRL_USER_KEY_OP, 10, Ioctrl_KeyOp);	// dse_yjpark
			
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_START;
			// error
			IOCTRLINFO_PRINTF("[%s] IOCTRL Sequence Error\n", __func__);
			break;
	}
}

void Ioctrl_KeyChattOp(void)
{
	if (keyCtrl.keyPressedOnFlag != ON)
	{
		if (ReadBtnKey() == KEY_PRESSED)
		{
			if (++keyCtrl.keyChattTimer > 10)	// 50ms
			{
				keyCtrl.keyChattTimer = 0;
				keyCtrl.keyPressedOnFlag = ON;
			}
			else
			{
			}
		}
		else
		{
			keyCtrl.keyChattTimer = 0;
		}
	}
	else /*if (keyCtrl.keyPressedOnFlag == ON)*/
	{
		if (ReadBtnKey() == KEY_RELEASED)
		{
			if (++keyCtrl.keyChattTimer > 10)	// 50ms
			{
				keyCtrl.keyChattTimer = 0;
				keyCtrl.keyReleasedOnFlag = ON;
				KillSoftTimer(STIMER_IOCTRL_USER_KEY_CHATT_OP);
			}
			else
			{
			}
		}
		else
		{
			keyCtrl.keyChattTimer = 0;
		}
	}
}

void Ioctrl_KeyOp(void)
{
	if (keyCtrl.keyChatStartFlag != ON)
	{
		if (ReadBtnKey() == KEY_PRESSED)
		{
			keyCtrl.keyChatStartFlag = ON;
			KillSoftTimer(STIMER_IOCTRL_USER_KEY_CHATT_OP);
			SetSoftTimer(STIMER_IOCTRL_USER_KEY_CHATT_OP, 5, Ioctrl_KeyChattOp);
		}
	}
	else if (keyCtrl.keyReleasedOnFlag == ON)
	{
		memset(&keyCtrl, 0, sizeof(key_detect_ctrl_t));
		//ApplTxECU1_Blind_Zone_Alert_Status_TxComfirmation();	// CAN
		//ApplTxECU2_V2V_Warning_TxComfirmation();	// CANFD
#if (CAN3toCAN_EN == ON)
		ApplTxECU1_SystemPowerMode_TxComfirmation();	// CAN
#elif (CAN1toCANFD_EN == ON)
		ApplTxECU2_V2V_Warning_TxComfirmation();	// CANFD
#endif
	}
	else
	{
	}
}



