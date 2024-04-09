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
phy_rtl8211f_resource_t g_1G_phy_resource;

#define ENET_1Gb ENET_1G
/* Address of PHY interface. */
#define ENET_1G_PHY_ADDRESS BOARD_ENET1_PHY_ADDRESS
/* PHY operations. */
#define ENET_1G_PHY_OPS &phyrtl8211f_ops
/* ENET instance select. */
#define ENET_1G_NETIF_INIT_FN ethernetif1_init

/* PHY resource. */
#define ENET_1G_PHY_RESOURCE &g_1G_phy_resource

#define	configMAC1G_ADDR {0x02, 0x12, 0x13, 0x10, 0x15, 0x12}

static phy_handle_t phy1GHandle;
struct netif netif1G;
ip4_addr_t netif1G_ipaddr, netif1G_netmask, netif1G_gw;

#endif

void BOARD_InitModuleClock(void)
{
    const clock_sys_pll1_config_t sysPll1Config = {
        .pllDiv2En = true,
    };
    CLOCK_InitSysPll1(&sysPll1Config);

    clock_root_config_t rootCfg = {.mux = 4, .div = 10}; /* Generate 50M root clock. */
    CLOCK_SetRootClock(kCLOCK_Root_Enet1, &rootCfg);
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
void BOARD_Init1GModuleClock(void)
{
    const clock_sys_pll1_config_t sysPll1Config = {
        .pllDiv2En = true,
    };
    CLOCK_InitSysPll1(&sysPll1Config);

    clock_root_config_t rootCfg = {.mux = 4, .div = 4}; /* Generate 125M root clock. */
    CLOCK_SetRootClock(kCLOCK_Root_Enet2, &rootCfg);
}
#endif

void IOMUXC_SelectENETClock(void)
{
    IOMUXC_GPR->GPR4 |= IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_MASK; /* 50M ENET_REF_CLOCK output to PHY and ENET module. */
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
void IOMUXC_SelectENET1GClock(void)
{
    IOMUXC_GPR->GPR5 |= IOMUXC_GPR_GPR5_ENET1G_RGMII_EN_MASK; /* bit1:iomuxc_gpr_enet_clk_dir
                                                                 bit0:GPR_ENET_TX_CLK_SEL(internal or OSC) */
}
#endif

void BOARD_ENETFlexibleConfigure(enet_config_t *config)
{
	if (config->userData == (void *)&netif)
		config->miiMode = kENET_RmiiMode;
#if BOARD_NETWORK_USE_1G_ENET_PORT	
	else if (config->userData == (void *)&netif1G)
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

#if BOARD_NETWORK_USE_1G_ENET_PORT
static void MDIO_1G_Init(void)
{
    (void)CLOCK_EnableClock(s_enetClock[ENET_GetInstance(ENET_1Gb)]);
    ENET_SetSMI(ENET_1Gb, ENET_CLOCK_FREQ, false);
}
#endif

static status_t MDIO_Write(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    return ENET_MDIOWrite(ENET_100M, phyAddr, regAddr, data);
}

static status_t MDIO_Read(uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    return ENET_MDIORead(ENET_100M, phyAddr, regAddr, pData);
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
static status_t MDIO_1G_Write(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    return ENET_MDIOWrite(ENET_1Gb, phyAddr, regAddr, data);
}

static status_t MDIO_1G_Read(uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    return ENET_MDIORead(ENET_1Gb, phyAddr, regAddr, pData);
}
#endif

void SysTick_Handler(void)
{
    time_isr();
}

void Enet_Mdio_Init(void)
{
	MDIO_Init();
    g_phy_resource.read  = MDIO_Read;
    g_phy_resource.write = MDIO_Write;
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
void Enet1G_Mdio_Init(void)
{
	MDIO_1G_Init();
    g_1G_phy_resource.read  = MDIO_1G_Read;
    g_1G_phy_resource.write = MDIO_1G_Write;
}
#endif

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

	    /* Set MAC address. */
#ifndef configMAC_ADDR
    (void)SILICONID_ConvertToMacAddr(&enet_config.macAddress);
#endif

    /* Get clock after hardware init. */
    enet_config.srcClockHz = ENET_CLOCK_FREQ;
	
	netif_add(&netif, &netif_ipaddr, &netif_netmask, &netif_gw, &enet_config, ENET_100M_NETIF_INIT_FN, ethernet_input);
	netif_set_default(&netif);
	netif_set_up(&netif);
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
void Enet1G_NetifConfig(void)
{
	ethernetif_config_t enet_config = {.phyHandle   = &phy1GHandle,
                                       .phyAddr     = ENET_1G_PHY_ADDRESS,
                                       .phyOps      = ENET_1G_PHY_OPS,
                                       .phyResource = ENET_1G_PHY_RESOURCE,
#ifdef configMAC1G_ADDR
                                       .macAddress = configMAC1G_ADDR
#endif
    };

	    /* Set MAC address. */
#ifndef configMAC1G_ADDR
    (void)SILICONID_ConvertToMacAddr(&enet_config.macAddress);
#endif

    /* Get clock after hardware init. */
    enet_config.srcClockHz = ENET_CLOCK_FREQ;
	
	//netif_add(&netif1G, &netif1G_ipaddr, &netif1G_netmask, &netif1G_gw, &enet_config, ENET_1G_NETIF_INIT_FN, ethernet_input);
	netif_add(&netif1G, &netif_ipaddr, &netif_netmask, &netif_gw, &enet_config, ENET_1G_NETIF_INIT_FN, ethernet_input);
	netif_set_default(&netif1G);
	netif_set_up(&netif1G);
}
#endif

err_enum_t Enet_100M_WaitLinkUp(long timeout_ms)
{
	return ethernetif_wait_linkup(&netif, timeout_ms);;
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
err_enum_t Enet_1G_WaitLinkUp(long timeout_ms)
{
	return ethernetif_wait_linkup(&netif1G, timeout_ms);;
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

