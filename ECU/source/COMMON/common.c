#include "Includes.h"

#define	TIME_1S		1000U		
#define	TIME_500MS	500U		
#define	TIME_100MS	100U

static void Init_CanDriver(void);
static void Init_EthDriver(void);

void Init_CommonFunc(void)
{
	/* System Information */
	SystemInfo();

	/* Count the global base timer value based on timer interrupt every 1ms */
	SoftTimerInit();

	Init_CanDriver();
	Init_EthDriver();
}

void CommonFunc(void)
{
	Enet_WaitLinkUp();

	if (GetPrintFuncExecTimeValue() > TIME_1S)	// Print max execution time every 1s is printed.	
	{	
#if (EXECUTION_TIME_LOG == ON)
		PrintFuncExecTime();
#endif

		if (bEnetLinkUp == TRUE)
		{
			Enet_UdpCallback();
		}

		ClearPrintFuncExecTimeValue();
	}
	else if (GetPrintFuncExecTimeValue() > TIME_500MS)
	{
	}
	else if (GetPrintFuncExecTimeValue() > TIME_100MS)
	{
	}
	else
	{
	}
}

static void Init_CanDriver(void)
{
#if (CAN3toCAN_EN == ON)
	BOARD_InitCanPins();
	CanTransOperationMode(CAN_CH_3, CAN_TRANS_OPMODE_STANDBY);
	CAN_Init(CAN_CH_3);	// CAN
	CAN_ReceiveStart(CAN_CH_3);	// CAN
	CanTransOperationMode(CAN_CH_3, CAN_TRANS_OPMODE_NORMAL);
#endif

#if (CAN1toCANFD_EN == ON)
	BOARD_InitCanFdPins();
	CanTransOperationMode(CAN_CH_1, CAN_TRANS_OPMODE_STANDBY);
	CAN_Init(CAN_CH_1);	// CANFD
	CAN_ReceiveStart(CAN_CH_1);	// CANFD
	CanTransOperationMode(CAN_CH_1, CAN_TRANS_OPMODE_NORMAL);
#endif
}

static void Init_EthDriver(void)
{
	BOARD_InitModuleClock();
	IOMUXC_SelectENETClock();

	BOARD_InitEnetPins();

	ENET_100M_RESET_ENABLE;
	SDK_DelayAtLeastUs(10000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);	// 10ms
	ENET_100M_RESET_DISABLE;
	SDK_DelayAtLeastUs(10000U, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);	// 10ms

	Enet_Mdio_Init();

	time_init();

	Enet_IPADDR_Config();

	lwip_init();

	Enet_NetifConfig();
	
	bEnetLinkUp = FALSE;
	EnetLinkUpCnt = 0;

	create_udp_socket();
	bUdpTest = FALSE;
}

