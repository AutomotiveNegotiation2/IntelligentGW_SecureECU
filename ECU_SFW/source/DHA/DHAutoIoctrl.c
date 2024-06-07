#include "Includes.h"

#define	KEY_PRESSED		1
#define	KEY_RELEASED	0

bool	ReadCBdBtnKey(void)		{return GPIO_PinRead(BOARD_INITPINS_USER_BUTTON_GPIO, BOARD_INITPINS_USER_BUTTON_GPIO_PIN) == 0 ? KEY_PRESSED : KEY_RELEASED;}
bool	ReadFBdSw01BtnKey(void)	{return GPIO_PinRead(BOARD_INITFUNCIOPINS_FlexSPI_B_D3_GPIO, BOARD_INITFUNCIOPINS_FlexSPI_B_D3_GPIO_PIN) == 0 ? KEY_PRESSED : KEY_RELEASED;}
bool	ReadFBdSw02BtnKey(void)	{return GPIO_PinRead(BOARD_INITFUNCIOPINS_FlexSPI_B_D2_GPIO, BOARD_INITFUNCIOPINS_FlexSPI_B_D2_GPIO_PIN) == 0 ? KEY_PRESSED : KEY_RELEASED;}
bool	ReadFBdSw03BtnKey(void)	{return GPIO_PinRead(BOARD_INITFUNCIOPINS_FlexSPI_B_D1_GPIO, BOARD_INITFUNCIOPINS_FlexSPI_B_D1_GPIO_PIN) == 0 ? KEY_PRESSED : KEY_RELEASED;}
bool	ReadFBdSw04BtnKey(void)	{return GPIO_PinRead(BOARD_INITFUNCIOPINS_FlexSPI_B_D0_GPIO, BOARD_INITFUNCIOPINS_FlexSPI_B_D0_GPIO_PIN) == 0 ? KEY_PRESSED : KEY_RELEASED;}

#define	LED_D1_RED_ON		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_RED_D1_GPIO, BOARD_INITFUNCIOPINS_LED_RED_D1_GPIO_PIN, ON)
#define	LED_D1_RED_OFF		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_RED_D1_GPIO, BOARD_INITFUNCIOPINS_LED_RED_D1_GPIO_PIN, OFF)
#define	LED_D1_GREEN_ON		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_GREEN_D1_GPIO, BOARD_INITFUNCIOPINS_LED_GREEN_D1_GPIO_PIN, ON)
#define	LED_D1_GREEN_OFF	GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_GREEN_D1_GPIO, BOARD_INITFUNCIOPINS_LED_GREEN_D1_GPIO_PIN, OFF)
#define	LED_D2_RED_ON		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_RED_D2_GPIO, BOARD_INITFUNCIOPINS_LED_RED_D2_GPIO_PIN, ON)
#define	LED_D2_RED_OFF		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_RED_D2_GPIO, BOARD_INITFUNCIOPINS_LED_RED_D2_GPIO_PIN, OFF)
#define	LED_D2_GREEN_ON		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_GREEN_D2_GPIO, BOARD_INITFUNCIOPINS_LED_GREEN_D2_GPIO_PIN, ON)
#define	LED_D2_GREEN_OFF	GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_GREEN_D2_GPIO, BOARD_INITFUNCIOPINS_LED_GREEN_D2_GPIO_PIN, OFF)
#define	LED_D3_RED_ON		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_RED_D3_GPIO, BOARD_INITFUNCIOPINS_LED_RED_D3_GPIO_PIN, ON)
#define	LED_D3_RED_OFF		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_RED_D3_GPIO, BOARD_INITFUNCIOPINS_LED_RED_D3_GPIO_PIN, OFF)
#define	LED_D3_GREEN_ON		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_GREEN_D3_GPIO, BOARD_INITFUNCIOPINS_LED_GREEN_D3_GPIO_PIN, ON)
#define	LED_D3_GREEN_OFF	GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_GREEN_D3_GPIO, BOARD_INITFUNCIOPINS_LED_GREEN_D3_GPIO_PIN, OFF)
#define	LED_D4_RED_ON		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_RED_D4_GPIO, BOARD_INITFUNCIOPINS_LED_RED_D4_GPIO_PIN, ON)
#define	LED_D4_RED_OFF		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_RED_D4_GPIO, BOARD_INITFUNCIOPINS_LED_RED_D4_GPIO_PIN, OFF)
#define	LED_D4_GREEN_ON		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_GREEN_D4_GPIO, BOARD_INITFUNCIOPINS_LED_GREEN_D4_GPIO_PIN, ON)
#define	LED_D4_GREEN_OFF	GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_GREEN_D4_GPIO, BOARD_INITFUNCIOPINS_LED_GREEN_D4_GPIO_PIN, OFF)
#define	LED_D5_RED_ON		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_RED_D5_GPIO, BOARD_INITFUNCIOPINS_LED_RED_D5_GPIO_PIN, ON)
#define	LED_D5_RED_OFF		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_RED_D5_GPIO, BOARD_INITFUNCIOPINS_LED_RED_D5_GPIO_PIN, OFF)
#define	LED_D5_GREEN_ON		GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_GREEN_D5_GPIO, BOARD_INITFUNCIOPINS_LED_GREEN_D5_GPIO_PIN, ON)
#define	LED_D5_GREEN_OFF	GPIO_PinWrite(BOARD_INITFUNCIOPINS_LED_GREEN_D5_GPIO, BOARD_INITFUNCIOPINS_LED_GREEN_D5_GPIO_PIN, OFF)

uint32_t led[LED_COLOR_MAX][LED_NUM_MAX] = 
{
	// LED GREEN
	{
		BOARD_INITFUNCIOPINS_LED_GREEN_D1_GPIO_PIN,
		BOARD_INITFUNCIOPINS_LED_GREEN_D2_GPIO_PIN,
		BOARD_INITFUNCIOPINS_LED_GREEN_D3_GPIO_PIN,
		BOARD_INITFUNCIOPINS_LED_GREEN_D4_GPIO_PIN,
		BOARD_INITFUNCIOPINS_LED_GREEN_D5_GPIO_PIN,
	},
	// LED RED
	{
		BOARD_INITFUNCIOPINS_LED_RED_D1_GPIO_PIN,
		BOARD_INITFUNCIOPINS_LED_RED_D2_GPIO_PIN,
		BOARD_INITFUNCIOPINS_LED_RED_D3_GPIO_PIN,
		BOARD_INITFUNCIOPINS_LED_RED_D4_GPIO_PIN,
		BOARD_INITFUNCIOPINS_LED_RED_D5_GPIO_PIN
	},
};

typedef struct {
	uint8_t keyChattTimer;
	bool keyPressedOnFlag;
	bool keyReleasedOnFlag;
	bool keyChatStartFlag;
} key_detect_ctrl_t;

typedef struct {
	key_detect_ctrl_t * keyCtrl;
	ReadKeyInCallback * keyInReadFunc;
	KeyFuncCallback * keyCbFunc;
} keyIn_read_t;

ReadKeyInCallback keyInFunc[KEY_IN_MAX] = 
{
	ReadCBdBtnKey,
	ReadFBdSw01BtnKey,
	ReadFBdSw02BtnKey,
	ReadFBdSw03BtnKey,
	ReadFBdSw04BtnKey
};

KeyFuncCallback keyFunc[KEY_IN_MAX] = 
{
	NULL,
#if (LIGHTING_GRILL_KEY_DEMO == ON)
	DHADemoApp_LG_TURN_RIGHT,
	DHADemoApp_LG_TURN_LEFT,
	DHADemoApp_LG_EMERGENCY,
	DHADemoApp_LG_WELCOME,
#else
#if (CAN3toCAN_EN == ON)
	ApplTxECU1_SystemPowerMode_TxComfirmation,
	ApplTxECU1_Blind_Zone_Alert_Status_TxComfirmation,
#else
	NULL,
	NULL,
#endif
#if (CAN1toCANFD_EN == ON)
	ApplTxECU2_Clock_TxComfirmation,
	ApplTxECU2_V2V_Warning_TxComfirmation,
#else
	NULL,
	NULL
#endif
#endif
};

key_detect_ctrl_t keyInCtrl[KEY_IN_MAX];
keyIn_read_t keyInConfig;
	
static void RUN_IOCTRL_DN_ACC_OFF(void);
static void RUN_IOCTRL_UP_ACC_ON(void);
void Ioctrl_KeyOp(void);
void Ioctrl_KeyChattOp(void);
#if (CAN1toCANFD_EN == ON)
void Ioctrl_CanFdLedOp(void);
#endif
#if (CAN3toCAN_EN == ON)
void Ioctrl_CanLedOp(void);
#endif
void Led_Write(led_color_inst_t color, led_inst_t led, uint8_t output);
static void IoctrlSrv(void);

void IoctrlMain(void)
{
	SoftTimerSrv();
	IoctrlSrv();
}

static void IoctrlSrv(void)
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

static void RUN_IOCTRL_DN_ACC_OFF(void)
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

static void RUN_IOCTRL_UP_ACC_ON(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_IOCTRL)
	{
		case LO_SEQ_START:
			KillSoftTimer(STIMER_IOCTRL_USER_KEY_OP);
			KillSoftTimer(STIMER_IOCTRL_USER_KEY_CHATT_OP);
#if (CAN1toCANFD_EN == 1)
			KillSoftTimer(STIMER_IOCTRL_CANFD_LED_OP);
#endif
#if (CAN3toCAN_EN == 1)
			KillSoftTimer(STIMER_IOCTRL_CAN_LED_OP);
#endif

			BOARD_InitFuncIoPins();
			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			InitRTC();

			GlobalPocSeq.LSeq.B.SEQ_IOCTRL = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			memset(keyInCtrl, 0, sizeof(key_detect_ctrl_t)*KEY_IN_MAX);
			SetSoftTimer(STIMER_IOCTRL_USER_KEY_OP, 10, Ioctrl_KeyOp);	
			SetSoftTimer(STIMER_IOCTRL_USER_KEY_CHATT_OP, 5, Ioctrl_KeyChattOp);
#if (CAN1toCANFD_EN == 1)
			SetSoftTimer(STIMER_IOCTRL_CANFD_LED_OP, 200, Ioctrl_CanFdLedOp);
#endif

#if (CAN3toCAN_EN == 1)
			SetSoftTimer(STIMER_IOCTRL_CAN_LED_OP, 200, Ioctrl_CanLedOp);
#endif
			
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

uint32_t IOCTRL_GetConfigKeyIn(keyIn_inst_t keych)
{
	if (keych >= KEY_IN_MAX)
	{
		IOCTRLINFO_PRINTF("[%s] KeyIn Channel is not valid ...\r\n", __func__);
		assert(0);
	}

	keyInConfig.keyCtrl = &keyInCtrl[keych];
	keyInConfig.keyInReadFunc = &keyInFunc[keych];
	keyInConfig.keyCbFunc = &keyFunc[keych];

	return (uint32_t)(&keyInConfig);
}

void Ioctrl_KeyChattOp(void)
{
	keyIn_inst_t keyin;
	keyIn_read_t * keyhandle;
	
	for (keyin=KEY_IN_CHECK_START; keyin<KEY_IN_MAX; keyin++)
	{
		keyhandle = (keyIn_read_t *)IOCTRL_GetConfigKeyIn(keyin);
		if (keyhandle->keyCtrl->keyChatStartFlag == ON)
		{
			if (keyhandle->keyCtrl->keyPressedOnFlag != ON)
			{
				if ((*(keyhandle->keyInReadFunc))() == KEY_PRESSED)
				{
					if (++keyhandle->keyCtrl->keyChattTimer > 10)
					{
						keyhandle->keyCtrl->keyChattTimer = 0;
						keyhandle->keyCtrl->keyPressedOnFlag = ON;
					}
					else
					{
					}
				}
				else
				{
					keyhandle->keyCtrl->keyChattTimer = 0;
				}
			}
			else
			{
				if ((*(keyhandle->keyInReadFunc))() == KEY_RELEASED)
				{
					if (++keyhandle->keyCtrl->keyChattTimer > 10)
					{
						keyhandle->keyCtrl->keyChattTimer = 0;
						keyhandle->keyCtrl->keyReleasedOnFlag = ON;
						//KillSoftTimer(STIMER_IOCTRL_USER_KEY_CHATT_OP);
					}
					else
					{
					}
				}
				else
				{
					keyhandle->keyCtrl->keyChattTimer = 0;
				}
			}
		}
		else
		{
		}
	}
}

void Ioctrl_KeyOp(void)
{
	keyIn_inst_t keyin;
	keyIn_read_t * keyhandle;
	
	for (keyin=KEY_IN_CHECK_START; keyin<KEY_IN_MAX; keyin++)
	{
		keyhandle = (keyIn_read_t *)IOCTRL_GetConfigKeyIn(keyin);
		if (keyhandle->keyCtrl->keyChatStartFlag != ON)
		{
			if ((*(keyhandle->keyInReadFunc))() == KEY_PRESSED)
			{
				IOCTRLINFO_PRINTF("[SW%d] key is pressed ...\r\n", keyin);
				keyhandle->keyCtrl->keyChatStartFlag = ON;
				//KillSoftTimer(STIMER_IOCTRL_USER_KEY_CHATT_OP);
				//SetSoftTimer(STIMER_IOCTRL_USER_KEY_CHATT_OP, 5, Ioctrl_KeyChattOp);
			}
		}
		else if (keyhandle->keyCtrl->keyReleasedOnFlag == ON)
		{
			IOCTRLINFO_PRINTF("[SW%d] key is released ...\r\n", keyin);
			if (*keyhandle->keyCbFunc != NULL)
			{
				(*(keyhandle->keyCbFunc))();
			}
			else
			{
#if ((CAN3toCAN_EN == OFF) && (CAN1toCANFD_EN == OFF))
				IOCTRLINFO_PRINTF("[%s] key callback function is NULL ...\r\n", __func__);
				IOCTRLINFO_PRINTF("You should set the CAN/CANFD configuration ...\r\n");
#elif (CAN3toCAN_EN == OFF)
				IOCTRLINFO_PRINTF("[%s] CAN configuration is OFF ...\r\n", __func__);
				IOCTRLINFO_PRINTF("You should use SW03, SW04 for CANFD in Function IO Board ...\r\n");
#elif (CAN1toCANFD_EN == OFF)
				IOCTRLINFO_PRINTF("[%s] CANFD configuration is OFF ...\r\n", __func__);
				IOCTRLINFO_PRINTF("You should use SW01, SW02 for CAN in Function IO Board ...\r\n");
#else
				IOCTRLINFO_PRINTF("[%s] User Button callback function is not set ...\r\n", __func__);
				IOCTRLINFO_PRINTF("You should use SW01, SW02, SW03, SW04 for CAN/CANFD in Function IO Board ...\r\n");
#endif
			}
	
			memset(keyhandle->keyCtrl, 0, sizeof(key_detect_ctrl_t));
		}
		else
		{
		}
	}
}

#if (CAN1toCANFD_EN == 1)
bool ledCanFdPEToggle=1, ledCanFdEVToggle=1, ledCanFdRxToggle=1;
uint8_t ledCanFdPECnt=0, ledCanFdEVCnt=0, ledCanFdRxCnt=0;
void Ioctrl_CanFdLedOp(void)
{
	if (ledCanFdPECnt > 0 )
	{
		if (ledCanFdPEToggle == 1)
			Led_Write(LED_RED, LED_D1, ON);
		else
			Led_Write(LED_RED, LED_D1, OFF);

		ledCanFdPEToggle ^= 1;
		ledCanFdPECnt--;
	}
	else
	{
		ledCanFdPEToggle = 1;
		Led_Write(LED_RED, LED_D1, OFF);		
	}

	if (ledCanFdEVCnt > 0 )
	{
		if (ledCanFdEVToggle == 1)
			Led_Write(LED_RED, LED_D2, ON);
		else
			Led_Write(LED_RED, LED_D2, OFF);

		ledCanFdEVToggle ^= 1;
		ledCanFdEVCnt--;
	}
	else
	{
		ledCanFdEVToggle = 1;
		Led_Write(LED_RED, LED_D2, OFF);		
	}

	if (ledCanFdRxCnt > 0 )
	{
		if (ledCanFdRxToggle == 1)
			Led_Write(LED_RED, LED_D3, ON);
		else
			Led_Write(LED_RED, LED_D3, OFF);

		ledCanFdRxToggle ^= 1;
		ledCanFdRxCnt--;
	}
	else
	{
		ledCanFdRxToggle = 1;
		Led_Write(LED_RED, LED_D3, OFF);		
	}
}
#endif

#if (CAN3toCAN_EN == 1)
bool ledCanPEToggle=1, ledCanEVToggle=1, ledCanRxToggle=1;
uint8_t ledCanPECnt=0, ledCanEVCnt=0, ledCanRxCnt=0;
void Ioctrl_CanLedOp(void)
{
	if (ledCanPECnt > 0 )
	{
		if (ledCanPEToggle == 1)
			Led_Write(LED_GREEN, LED_D1, ON);
		else
			Led_Write(LED_GREEN, LED_D1, OFF);

		ledCanPEToggle ^= 1;
		ledCanPECnt--;
	}
	else
	{
		ledCanPEToggle = 1;
		Led_Write(LED_GREEN, LED_D1, OFF);		
	}

	if (ledCanEVCnt > 0 )
	{
		if (ledCanEVToggle == 1)
			Led_Write(LED_GREEN, LED_D2, ON);
		else
			Led_Write(LED_GREEN, LED_D2, OFF);

		ledCanEVToggle ^= 1;
		ledCanEVCnt--;
	}
	else
	{
		ledCanEVToggle = 1;
		Led_Write(LED_GREEN, LED_D2, OFF);		
	}

	if (ledCanRxCnt > 0 )
	{
		if (ledCanRxToggle == 1)
			Led_Write(LED_GREEN, LED_D3, ON);
		else
			Led_Write(LED_GREEN, LED_D3, OFF);

		ledCanRxToggle ^= 1;
		ledCanRxCnt--;
	}
	else
	{
		ledCanRxToggle = 1;
		Led_Write(LED_GREEN, LED_D3, OFF);		
	}
}
#endif

void IOCTRL_SetLedOpForTx(uint8_t inst, uint8_t attr)
{
	if (attr == CAN_TX_ATTR_PERIODIC)
	{
#if (CAN1toCANFD_EN == 1)
		if (inst == CAN_CH_1)	// CANFD
			ledCanFdPECnt = 5;
#endif
#if (CAN3toCAN_EN == 1)
		if (inst == CAN_CH_3)	// CAN
			ledCanPECnt = 5;
#endif
	}
	else	// EVENT
	{
#if (CAN1toCANFD_EN == 1)
		if (inst == CAN_CH_1)	// CANFD
			ledCanFdEVCnt = 5;
#endif
#if (CAN3toCAN_EN == 1)
		if (inst == CAN_CH_3)	// CAN
			ledCanEVCnt = 5;
#endif
	}
}

void IOCTRL_SetLedOpForRx(uint8_t inst)
{
#if (CAN1toCANFD_EN == 1)
	if (inst == CAN_CH_1)	// CANFD
		ledCanFdRxCnt = 5;
#endif
#if (CAN3toCAN_EN == 1)
	if (inst == CAN_CH_3)	// CAN
		ledCanRxCnt = 5;
#endif
}


void Led_Write(led_color_inst_t color, led_inst_t ledNum, uint8_t output)
{
	GPIO_PinWrite(GPIO13, led[color][ledNum], output);
}

