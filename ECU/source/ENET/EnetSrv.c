#include "ethernetif.h"
#include "pin_mux.h"

#include "Includes.h"

#include "udpClientRAW.h"
#include "tcpClientRAW.h"

//#define	APP_PING
//#define	APP_UDP
#define	APP_TCP

#define	ENET_100M_RESET_ENABLE	GPIO_WritePinOutput(BOARD_INITENETPINS_ENET_RST_GPIO, BOARD_INITENETPINS_ENET_RST_GPIO_PIN, 0);
#define	ENET_100M_RESET_DISABLE	GPIO_WritePinOutput(BOARD_INITENETPINS_ENET_RST_GPIO, BOARD_INITENETPINS_ENET_RST_GPIO_PIN, 1);

#define	ENET_100M_RESET_TIMEOUT	10U

#if BOARD_NETWORK_USE_1G_ENET_PORT
#define	ENET_1G_RESET_ENABLE	GPIO_WritePinOutput(BOARD_INITENET1GPINS_ENET_1G_RST_GPIO, BOARD_INITENET1GPINS_ENET_1G_RST_GPIO_PIN, 0);
#define	ENET_1G_RESET_DISABLE	GPIO_WritePinOutput(BOARD_INITENET1GPINS_ENET_1G_RST_GPIO, BOARD_INITENET1GPINS_ENET_1G_RST_GPIO_PIN, 1);

#define	ENET_1G_RESET_TIMEOUT	10U
#endif

/* IP address configuration. */
#ifndef configIP_ADDR0
#define configIP_ADDR0 192
#endif
#ifndef configIP_ADDR1
#define configIP_ADDR1 168
#endif
#ifndef configIP_ADDR2
#define configIP_ADDR2 0
#endif
#ifndef configIP_ADDR3
#define configIP_ADDR3 102
#endif

#if BOARD_NETWORK_USE_1G_ENET_PORT
/* IP address configuration. */
#ifndef configIP1G_ADDR0
#define configIP1G_ADDR0 192
#endif
#ifndef configIP1G_ADDR1
#define configIP1G_ADDR1 168
#endif
#ifndef configIP1G_ADDR2
#define configIP1G_ADDR2 0
#endif
#ifndef configIP1G_ADDR3
#define configIP1G_ADDR3 12
#endif
#endif

/* Netmask configuration. */
#ifndef configNET_MASK0
#define configNET_MASK0 255
#endif
#ifndef configNET_MASK1
#define configNET_MASK1 255
#endif
#ifndef configNET_MASK2
#define configNET_MASK2 255
#endif
#ifndef configNET_MASK3
#define configNET_MASK3 0
#endif

/* Gateway address configuration. */
#ifndef configGW_ADDR0
#define configGW_ADDR0 192
#endif
#ifndef configGW_ADDR1
#define configGW_ADDR1 168
#endif
#ifndef configGW_ADDR2
#define configGW_ADDR2 0
#endif
#ifndef configGW_ADDR3
#define configGW_ADDR3 254
#endif

static bool	bEnetTMRING, bEnetLinkUp;
long EnetLinkUpCnt;
#if BOARD_NETWORK_USE_1G_ENET_PORT
static bool	bEnet1GLinkUp;
long Enet1GLinkUpCnt;
#endif

void RUN_ENET_100M_DN_ACC_OFF(void);
void RUN_ENET_100M_UP_ACC_ON(void);
void RUN_ENET_100M_ACC_ON(void);
void SetEnetSEQ(void);
void Enet_IPADDR_Config(void);
void Enet_WaitLinkUp(void);

#if BOARD_NETWORK_USE_1G_ENET_PORT
void Enet1G_IPADDR_Config(void);
void Enet1G_WaitLinkUp(void);
#endif

#if defined (APP_UDP)
void Enet_UdpCallback(void)
{
	HAL_TIM_PeriodUdpElapsedCallback();
	ENETINFO_PRINTF("UDP Callback is called.\r\n", __func__);
}
#endif

#if defined (APP_TCP)
bool TcpSendEnable = FALSE;
void Enet_TcpCallback(void)
{
	HAL_TIM_PeriodTcpElapsedCallback();
	ENETINFO_PRINTF("[ENET100M] TCP Callback is called.\r\n");
	KillSoftTimer(STIMER_ENET_100M_TCP_TEST);
	SetSoftTimer(STIMER_ENET_100M_TCP_TEST, 1000, Enet_TcpCallback);
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
void Enet1G_TcpCallback(void)
{
	HAL_TIM_PeriodTcp1GElapsedCallback();
	ENETINFO_PRINTF("[ENET1G] TCP Callback is called.\r\n");
	KillSoftTimer(STIMER_ENET_1G_TCP_TEST);
	SetSoftTimer(STIMER_ENET_1G_TCP_TEST, 1000, Enet1G_TcpCallback);
}
#endif

#endif

void EnetSrv(void)
{
	switch(GlobalPocSeq.GSeq)
	{
		case GB_SEQ_UP_ACC_OFF:
			if(GlobalPocSeq.LSeq.B.SEQ_ENET_100M == LO_SEQ_START)
			{
				GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_FINISH;
			}
			break;

		case GB_SEQ_ACC_OFF:
			break;

		case GB_SEQ_DN_ACC_OFF:
			RUN_ENET_100M_DN_ACC_OFF();
			break;

		case GB_SEQ_UP_ACC_ON:
			RUN_ENET_100M_UP_ACC_ON();
			break;

		case GB_SEQ_ACC_ON:
			RUN_ENET_100M_ACC_ON();
			break;

		default:
			break;
	}
}

void RUN_ENET_100M_UP_ACC_ON(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_ENET_100M)
	{
		case LO_SEQ_START:
			KillSoftTimer(STIMER_ENET_100M);
			KillSoftTimer(STIMER_ENET_100M_LINKUP);
			KillSoftTimer(STIMER_ENET_100M_TCP_TEST);
#if BOARD_NETWORK_USE_1G_ENET_PORT
			KillSoftTimer(STIMER_ENET_1G_LINKUP);
			KillSoftTimer(STIMER_ENET_1G_TCP_TEST);
#endif

			bEnetTMRING = OFF;
			BOARD_InitModuleClock();
			IOMUXC_SelectENETClock();

			BOARD_InitEnetPins();
#if BOARD_NETWORK_USE_1G_ENET_PORT
			BOARD_Init1GModuleClock();
			IOMUXC_SelectENET1GClock();

			BOARD_InitEnet1GPins();
#endif

			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			ENET_100M_RESET_ENABLE;
#if BOARD_NETWORK_USE_1G_ENET_PORT
			ENET_1G_RESET_ENABLE;
#endif
			bEnetTMRING = ON;
			SetSoftTimer(STIMER_ENET_100M, ENET_100M_RESET_TIMEOUT, SetEnetSEQ); 
			break;

		case LO_SEQ_02:
			if(bEnetTMRING == ON) break;
			
			ENET_100M_RESET_DISABLE;
#if BOARD_NETWORK_USE_1G_ENET_PORT
			ENET_1G_RESET_DISABLE;
#endif

			bEnetTMRING = ON;
#if BOARD_NETWORK_USE_1G_ENET_PORT
			SetSoftTimer(STIMER_ENET_100M, 30U, SetEnetSEQ); 
#else
			SetSoftTimer(STIMER_ENET_100M, 6, SetEnetSEQ); 
#endif
			break;

		case LO_SEQ_03:
			if(bEnetTMRING == ON) break;

			Enet_Mdio_Init();
#if BOARD_NETWORK_USE_1G_ENET_PORT
			EnableIRQ(ENET_1G_MAC0_Tx_Rx_1_IRQn);
		    EnableIRQ(ENET_1G_MAC0_Tx_Rx_2_IRQn);

			Enet1G_Mdio_Init();
#endif
			time_init();

			Enet_IPADDR_Config();
#if BOARD_NETWORK_USE_1G_ENET_PORT
			//Enet1G_IPADDR_Config();
#endif
			lwip_init();

			Enet_NetifConfig();
#if BOARD_NETWORK_USE_1G_ENET_PORT
			//Enet1G_NetifConfig();
#endif
			bEnetLinkUp = FALSE;
			EnetLinkUpCnt = 0;
			SetSoftTimer(STIMER_ENET_100M_LINKUP, 10, Enet_WaitLinkUp);
#if BOARD_NETWORK_USE_1G_ENET_PORT
			//bEnet1GLinkUp = FALSE;
			//Enet1GLinkUpCnt = 0;
			//SetSoftTimer(STIMER_ENET_1G_LINKUP, 10, Enet1G_WaitLinkUp);
#endif
			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_START;
			// error
			ENETINFO_PRINTF("[%s] ENET_100M Sequence Error\r\n", __func__);
			break;
	}
}

void RUN_ENET_100M_DN_ACC_OFF(void)
{
	switch(GlobalPocSeq.LSeq.B.SEQ_ENET_100M)
	{
		case LO_SEQ_START:
			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_START;
			// error
			ENETINFO_PRINTF("[%s] ENET_100M Sequence Error\n", __func__);
			break;
	}
}

void RUN_ENET_100M_ACC_ON(void)
{
	if (bEnetLinkUp == TRUE)
	{
		/* Poll the driver, get any outstanding frames */
		ethernetif_input(&netif);
	}
#if BOARD_NETWORK_USE_1G_ENET_PORT
	if (bEnet1GLinkUp == TRUE)
	{
		ethernetif_input(&netif1G);
	}
#endif

#if BOARD_NETWORK_USE_1G_ENET_PORT
	if ((bEnet1GLinkUp == TRUE) || (bEnetLinkUp == TRUE))
#else
	if (bEnetLinkUp == TRUE)
#endif
	{
		sys_check_timeouts(); /* Handle all system timeouts for all core protocols */
	}
}

void SetEnetSEQ(void)
{
	KillSoftTimer(STIMER_ENET_100M);
	GlobalPocSeq.LSeq.B.SEQ_ENET_100M++;
	bEnetTMRING = OFF;	
}

void Enet_IPADDR_Config(void)
{
	IP4_ADDR(&netif_ipaddr, configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3);
    IP4_ADDR(&netif_netmask, configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3);
    IP4_ADDR(&netif_gw, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2, configGW_ADDR3);
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
void Enet1G_IPADDR_Config(void)
{
	IP4_ADDR(&netif1G_ipaddr, configIP1G_ADDR0, configIP1G_ADDR1, configIP1G_ADDR2, configIP1G_ADDR3);
    IP4_ADDR(&netif1G_netmask, configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3);
    IP4_ADDR(&netif1G_gw, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2, configGW_ADDR3);
}
#endif

void Enet_WaitLinkUp(void)
{
	err_enum_t result = ERR_OK;

	result = Enet_100M_WaitLinkUp(1);
	if (result != ERR_OK)
	{
		if (++EnetLinkUpCnt > 500)
		{
			ENETINFO_PRINTF("PHY[100M] Auto-negotiation failed. Please check the cable connection and link partner setting.\r\n");
			EnetLinkUpCnt = 0;
		}
	}
	else
	{
		bEnetLinkUp = TRUE;
#if defined (APP_PING)
		ping_init(&netif_gw);
#elif defined (APP_UDP)
		create_udp_socket();
		SetSoftTimer(STIMER_ENET_100M_UDP_TEST, 1000, Enet_UdpCallback);
#elif defined (APP_TCP)
		tcp_client_init();
		SetSoftTimer(STIMER_ENET_100M_TCP_TEST, 10000, Enet_TcpCallback);
#else

#endif

#if BOARD_NETWORK_USE_1G_ENET_PORT
		Enet1G_IPADDR_Config();
		Enet1G_NetifConfig();
		bEnet1GLinkUp = FALSE;
		Enet1GLinkUpCnt = 0;
		SetSoftTimer(STIMER_ENET_1G_LINKUP, 10, Enet1G_WaitLinkUp);
#endif

#if 0
		PRINTF("\r\n************************************************\r\n");
	    PRINTF(" PING example\r\n");
	    PRINTF("************************************************\r\n");
	    PRINTF(" IPv4 Address     : %u.%u.%u.%u\r\n", ((u8_t *)&netif_ipaddr)[0], ((u8_t *)&netif_ipaddr)[1],
	           ((u8_t *)&netif_ipaddr)[2], ((u8_t *)&netif_ipaddr)[3]);
	    PRINTF(" IPv4 Subnet mask : %u.%u.%u.%u\r\n", ((u8_t *)&netif_netmask)[0], ((u8_t *)&netif_netmask)[1],
	           ((u8_t *)&netif_netmask)[2], ((u8_t *)&netif_netmask)[3]);
	    PRINTF(" IPv4 Gateway     : %u.%u.%u.%u\r\n", ((u8_t *)&netif_gw)[0], ((u8_t *)&netif_gw)[1],
	           ((u8_t *)&netif_gw)[2], ((u8_t *)&netif_gw)[3]);
	    PRINTF("************************************************\r\n");
#endif
		KillSoftTimer(STIMER_ENET_100M_LINKUP);
	}
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
void Enet1G_WaitLinkUp(void)
{
	err_enum_t result = ERR_OK;

	result = Enet_1G_WaitLinkUp(1);
	if (result != ERR_OK)
	{
		if (++Enet1GLinkUpCnt > 500)
		{
			ENETINFO_PRINTF("PHY[1G] Auto-negotiation failed. Please check the cable connection and link partner setting.\r\n");
			Enet1GLinkUpCnt = 0;
		}
	}
	else
	{
		bEnet1GLinkUp = TRUE;
		tcp_enet1G_client_init();
		//SetSoftTimer(STIMER_ENET_1G_TCP_TEST, 10000, Enet1G_TcpCallback);
		KillSoftTimer(STIMER_ENET_1G_LINKUP);
	}
}
#endif
