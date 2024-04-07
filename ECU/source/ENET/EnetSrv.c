#include "ethernetif.h"
#include "pin_mux.h"

#include "Includes.h"

#define	ENET_100M_RESET_ENABLE	GPIO_WritePinOutput(BOARD_INITENETPINS_ENET_RST_GPIO, BOARD_INITENETPINS_ENET_RST_GPIO_PIN, 0);
#define	ENET_100M_RESET_DISABLE	GPIO_WritePinOutput(BOARD_INITENETPINS_ENET_RST_GPIO, BOARD_INITENETPINS_ENET_RST_GPIO_PIN, 1);

#define	ENET_100M_RESET_TIMEOUT	10000U

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
#define configGW_ADDR3 100
#endif

static bool	bEnetTMRING, bEnetLinkUp;
long EnetLinkUpCnt;

void RUN_ENET_100M_DN_ACC_OFF(void);
void RUN_ENET_100M_UP_ACC_ON(void);
void RUN_ENET_100M_ACC_ON(void);
void SetEnetSEQ(void);
void Enet_IPADDR_Config(void);
void Enet_WaitLinkUp(void);

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
			bEnetTMRING = OFF;
			BOARD_InitModuleClock();
			IOMUXC_SelectENETClock();

			BOARD_InitEnetPins();

			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_01;
			break;

		case LO_SEQ_01:
			ENET_100M_RESET_ENABLE;

			bEnetTMRING = ON;
			SetSoftTimer(STIMER_ENET_100M, ENET_100M_RESET_TIMEOUT, SetEnetSEQ); 
			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_02;
			break;

		case LO_SEQ_02:
			if(bEnetTMRING == ON) break;
			
			ENET_100M_RESET_DISABLE;

			bEnetTMRING = ON;
			SetSoftTimer(STIMER_ENET_100M, 6, SetEnetSEQ); 
			
			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_03;
			break;

		case LO_SEQ_03:
			if(bEnetTMRING == ON) break;

			Enet_100M_Mdio_Init();
			time_init();

			Enet_IPADDR_Config();

			lwip_init();

			Enet_100M_NetifConfig();

			bEnetLinkUp = FALSE;
			EnetLinkUpCnt = 0;
			SetSoftTimer(STIMER_ENET_100M_LINKUP, 10, Enet_WaitLinkUp);

			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_FINISH;
			break;

		case LO_SEQ_FINISH:
			break;
			
		default:
			GlobalPocSeq.LSeq.B.SEQ_ENET_100M = LO_SEQ_START;
			// error
			SYSINFO_PRINTF("[%s] ENET_100M Sequence Error\n", __func__);
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
			SYSINFO_PRINTF("[%s] ENET_100M Sequence Error\n", __func__);
			break;
	}
}

void RUN_ENET_100M_ACC_ON(void)
{
	if (bEnetLinkUp == TRUE)
	{
		/* Poll the driver, get any outstanding frames */
		ethernetif_input(&netif);

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

void Enet_WaitLinkUp(void)
{
	err_enum_t result = ERR_OK;

	result = Enet_100M_WaitLinkUp(1);
	if (result != ERR_OK)
	{
		if (++EnetLinkUpCnt > 500)
		{
			PRINTF("PHY Auto-negotiation failed. Please check the cable connection and link partner setting.\r\n");
			EnetLinkUpCnt = 0;
		}
	}
	else
	{
		bEnetLinkUp = TRUE;
		ping_init(&netif_gw);

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