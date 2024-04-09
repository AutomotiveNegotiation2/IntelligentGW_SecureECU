#include "Includes.h"

phy_ksz8081_resource_t g_phy_resource;

#define ENET_100M ENET
/* Address of PHY interface. */
#define ENET_100M_PHY_ADDRESS BOARD_ENET0_PHY_ADDRESS
/* PHY operations. */
#define ENET_100M_PHY_OPS &phyksz8081_ops
/* ENET instance select. */
#define ENET_100M_NETIF_INIT_FN ethernetif0_init

/* PHY resource. */
#define ENET_100M_PHY_RESOURCE &g_phy_resource

/* ENET clock frequency. */
#define ENET_CLOCK_FREQ CLOCK_GetRootClockFreq(kCLOCK_Root_Bus)

#define configMAC_ADDR {0x02, 0x12, 0x13, 0x10, 0x15, 0x11}

static phy_handle_t phyHandle;
struct netif netif;
ip4_addr_t netif_ipaddr, netif_netmask, netif_gw;

#if BOARD_NETWORK_USE_1G_ENET_PORT
phy_rtl8211f_resource_t g_phy_resource_1G;

#define ENET_1Gb ENET_1G
/* Address of PHY interface. */
#define ENET_PHY_ADDRESS_1G BOARD_ENET1_PHY_ADDRESS
/* PHY operations. */
#define ENET_PHY_OPS_1G &phyrtl8211f_ops
/* ENET instance select. */
#define ENET_NETIF_INIT_FN_1G ethernetif1_init

/* PHY resource. */
#define ENET_PHY_RESOURCE_1G &g_phy_resource_1G

//#define	configMAC_ADDR_1G {0x02, 0x12, 0x13, 0x10, 0x15, 0x12}

static phy_handle_t phyHandle_1G;
struct netif netif_1G;
ip4_addr_t netif_ipaddr_1G, netif_netmask_1G, netif_gw_1G;

#endif

void BOARD_InitModuleClock(void)
{
    const clock_sys_pll1_config_t sysPll1Config = {
        .pllDiv2En = true,
    };
    CLOCK_InitSysPll1(&sysPll1Config);

    clock_root_config_t rootCfg = {.mux = 4, .div = 10}; /* Generate 50M root clock. */
    CLOCK_SetRootClock(kCLOCK_Root_Enet1, &rootCfg);

#if BOARD_NETWORK_USE_1G_ENET_PORT
	clock_root_config_t rootCfg_1G = {.mux = 4, .div = 4}; /* Generate 125M root clock. */
    CLOCK_SetRootClock(kCLOCK_Root_Enet2, &rootCfg_1G);
#endif
}

void IOMUXC_SelectENETClock(void)
{
    IOMUXC_GPR->GPR4 |= IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_MASK; /* 50M ENET_REF_CLOCK output to PHY and ENET module. */

#if BOARD_NETWORK_USE_1G_ENET_PORT
	IOMUXC_GPR->GPR5 |= IOMUXC_GPR_GPR5_ENET1G_RGMII_EN_MASK; /* bit1:iomuxc_gpr_enet_clk_dir
                                                                 bit0:GPR_ENET_TX_CLK_SEL(internal or OSC) */
#endif
}

void BOARD_ENETFlexibleConfigure(enet_config_t *config)
{
	if (config->userData == (void *)&netif)
		config->miiMode = kENET_RmiiMode;
#if BOARD_NETWORK_USE_1G_ENET_PORT	
	else if (config->userData == (void *)&netif_1G)
		config->miiMode = kENET_RgmiiMode;
#endif
	else
		ENETINFO_PRINTF("[%s] netif address isn't valid. \r\n", __func__);
}

static void MDIO_Init(void)
{
    (void)CLOCK_EnableClock(s_enetClock[ENET_GetInstance(ENET_100M)]);
    ENET_SetSMI(ENET_100M, ENET_CLOCK_FREQ, false);
}

static status_t MDIO_Write(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    return ENET_MDIOWrite(ENET_100M, phyAddr, regAddr, data);
}

static status_t MDIO_Read(uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    return ENET_MDIORead(ENET_100M, phyAddr, regAddr, pData);
}

void Enet_Mdio_Init(void)
{
	MDIO_Init();
    g_phy_resource.read  = MDIO_Read;
    g_phy_resource.write = MDIO_Write;
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
static void MDIO_Init_1G(void)
{
    (void)CLOCK_EnableClock(s_enetClock[ENET_GetInstance(ENET_1Gb)]);
    ENET_SetSMI(ENET_1Gb, ENET_CLOCK_FREQ, false);
}

static status_t MDIO_Write_1G(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    return ENET_MDIOWrite(ENET_1Gb, phyAddr, regAddr, data);
}

static status_t MDIO_Read_1G(uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    return ENET_MDIORead(ENET_1Gb, phyAddr, regAddr, pData);
}

void Enet_Mdio_Init_1G(void)
{
	MDIO_Init_1G();
    g_phy_resource_1G.read  = MDIO_Read_1G;
    g_phy_resource_1G.write = MDIO_Write_1G;
}
#endif

void SysTick_Handler(void)
{
    time_isr();
}

void Enet_IPADDR_Config(void)
{
	IP4_ADDR(&netif_ipaddr, configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP_ADDR3);
    IP4_ADDR(&netif_netmask, configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3);
    IP4_ADDR(&netif_gw, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2, configGW_ADDR3);
	
#if BOARD_NETWORK_USE_1G_ENET_PORT
	IP4_ADDR(&netif_ipaddr_1G, configIP_ADDR0, configIP_ADDR1, configIP_ADDR2, configIP1G_ADDR3_1G);
	IP4_ADDR(&netif_netmask_1G, configNET_MASK0, configNET_MASK1, configNET_MASK2, configNET_MASK3);
	IP4_ADDR(&netif_gw_1G, configGW_ADDR0, configGW_ADDR1, configGW_ADDR2, configGW_ADDR3);
#endif
}

void Enet_NetifConfig(void)
{
	ethernetif_config_t enet_config = {.phyHandle   = &phyHandle,
                                       .phyAddr     = ENET_100M_PHY_ADDRESS,
                                       .phyOps      = ENET_100M_PHY_OPS,
                                       .phyResource = ENET_100M_PHY_RESOURCE,
#ifdef configMAC_ADDR
                                       .macAddress = configMAC_ADDR
#endif
    };
	
#if BOARD_NETWORK_USE_1G_ENET_PORT
	ethernetif_config_t enet_config_1G = {.phyHandle   = &phyHandle_1G,
                                       .phyAddr     = ENET_PHY_ADDRESS_1G,
                                       .phyOps      = ENET_PHY_OPS_1G,
                                       .phyResource = ENET_PHY_RESOURCE_1G,
#ifdef configMAC_ADDR
                                       .macAddress = configMAC_ADDR
#endif
    };
#endif

	    /* Set MAC address. */
#ifndef configMAC_ADDR
    (void)SILICONID_ConvertToMacAddr(&enet_config.macAddress);
#if BOARD_NETWORK_USE_1G_ENET_PORT
	(void)SILICONID_ConvertToMacAddr(&enet_config_1G.macAddress);
#endif
#endif

    /* Get clock after hardware init. */
    enet_config.srcClockHz = ENET_CLOCK_FREQ;
	
	netif_add(&netif, &netif_ipaddr, &netif_netmask, &netif_gw, &enet_config, ENET_100M_NETIF_INIT_FN, ethernet_input);
	netif_set_default(&netif);
	netif_set_up(&netif);

#if BOARD_NETWORK_USE_1G_ENET_PORT
	/* Get clock after hardware init. */
    enet_config_1G.srcClockHz = ENET_CLOCK_FREQ;

	netif_add(&netif_1G, &netif_ipaddr, &netif_netmask, &netif_gw, &enet_config, ENET_NETIF_INIT_FN_1G, ethernet_input);
	netif_set_default(&netif_1G);
	netif_set_up(&netif_1G);
#endif
}

err_enum_t Enet_100M_WaitLinkUp(long timeout_ms)
{
	return ethernetif_wait_linkup(&netif, timeout_ms);;
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
err_enum_t Enet_1G_WaitLinkUp(long timeout_ms)
{
	return ethernetif_wait_linkup(&netif_1G, timeout_ms);;
}
#endif

void Enet_WaitLinkUp(void)
{
	err_enum_t result = ERR_OK;

	result = Enet_100M_WaitLinkUp(1);
	if (result != ERR_OK)
	{
		//if (++EnetLinkUpCnt > 500)
		if (++EnetLinkUpCnt > 250)
		{
			bUdpTest = FALSE;
			ENETINFO_PRINTF("PHY[100M] Auto-negotiation failed. Please check the cable connection and link partner setting.\r\n");
			EnetLinkUpCnt = 0;
		}
	}
	else
	{
		bEnetLinkUp = TRUE;

		if (bUdpTest == FALSE)
		{
			bUdpTest = TRUE;
		}
	}
}

