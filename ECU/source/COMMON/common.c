#include "Includes.h"

#define	TIME_1S		1000U		
#define	TIME_500MS	500U		
#define	TIME_100MS	100U

static void Init_CanDriver(void);
static void Init_EthDriver(void);
static void Poll_EthDriver(void);

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
	if (GetFuncTimer_1000ms() == ON)	// Print max execution time every 1s is printed.	
	{	
		/* Test function for 100M ehternet */
		if (Enet_GetLinkUp_100M() == TRUE)
		{
			Enet_UdpCallback();
		}
		
#if BOARD_NETWORK_USE_1G_ENET_PORT
		/* Test function for 1G ehternet */
		if (Enet_GetLinkUp_1G() == TRUE)
		{
			Enet_UdpCallback_1G();
		}
#endif

		ClearFuncTimer_1000ms();

#if (EXECUTION_TIME_LOG == ON)
		PrintFuncExecTime();
#endif

	}

	if (GetFuncTimer_500ms() == ON)
	{

		ClearFuncTimer_500ms();
	}

	if (GetFuncTimer_200ms() == ON)
	{

		ClearFuncTimer_200ms();
	}
	
	if (GetFuncTimer_100ms() == ON)
	{
		Enet_WaitLinkUp();

		ClearFuncTimer_100ms();
	}

	Poll_EthDriver();
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

	/* 100Mbps Ethernet */
	BOARD_InitEnetPins();

	ENET_RESET_ENABLE_100M;
	SDK_DelayAtLeastUs(ENET_RESET_ENABLE_TIME, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);	// 10ms
	ENET_RESET_DISABLE_100M;
	SDK_DelayAtLeastUs(ENET_RESET_STABLE_TIME, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);	// 10ms

	Enet_Mdio_Init();

#if BOARD_NETWORK_USE_1G_ENET_PORT
	BOARD_InitEnet1GPins();
	
	ENET_RESET_ENABLE_1G;
	SDK_DelayAtLeastUs(ENET_RESET_ENABLE_TIME_1G, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY); // 10ms
	ENET_RESET_DISABLE_1G;
	SDK_DelayAtLeastUs(ENET_RESET_STABLE_TIME_1G, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY); // 30ms
	
	EnableIRQ(ENET_1G_MAC0_Tx_Rx_1_IRQn);
	EnableIRQ(ENET_1G_MAC0_Tx_Rx_2_IRQn);
	
	Enet_Mdio_Init_1G();
#endif

	time_init();

	Enet_IPADDR_Config();

	lwip_init();

	Enet_NetifConfig();

	create_udp_socket();
#if BOARD_NETWORK_USE_1G_ENET_PORT
	create_udp_socket_1G();
#endif
	//create_udp_socket();

	Enet_Init();
	bUdpTest = FALSE;
}

static void Poll_EthDriver(void)
{
	if (Enet_GetLinkUp_100M() == TRUE)
	{
		/* Poll the driver, get any outstanding frames */
		ethernetif_input(&netif);
	}
#if BOARD_NETWORK_USE_1G_ENET_PORT
	if (Enet_GetLinkUp_1G() == TRUE)
	{
		/* Poll the driver, get any outstanding frames */
		ethernetif_input(&netif_1G);
	}
	
	if ((Enet_GetLinkUp_1G() == TRUE) || (Enet_GetLinkUp_100M() == TRUE))
#else
	if (Enet_GetLinkUp_100M() == TRUE)
#endif
	{
		sys_check_timeouts(); /* Handle all system timeouts for all core protocols */
	}
}
