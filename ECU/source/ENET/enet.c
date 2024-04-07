#include "pin_mux.h"
#include "board.h"

#ifndef configMAC_ADDR
#include "fsl_silicon_id.h"
#endif
#include "fsl_phy.h"

#include "fsl_phyksz8081.h"
#include "fsl_enet.h"

#include "Includes.h"

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
#define ENET_100M_CLOCK_FREQ CLOCK_GetRootClockFreq(kCLOCK_Root_Bus)

phy_ksz8081_resource_t g_phy_resource;

static phy_handle_t phyHandle;
struct netif netif;
ip4_addr_t netif_ipaddr, netif_netmask, netif_gw;

void BOARD_InitModuleClock(void)
{
    const clock_sys_pll1_config_t sysPll1Config = {
        .pllDiv2En = true,
    };
    CLOCK_InitSysPll1(&sysPll1Config);

    clock_root_config_t rootCfg = {.mux = 4, .div = 10}; /* Generate 50M root clock. */
    CLOCK_SetRootClock(kCLOCK_Root_Enet1, &rootCfg);
}

void IOMUXC_SelectENETClock(void)
{
    IOMUXC_GPR->GPR4 |= IOMUXC_GPR_GPR4_ENET_REF_CLK_DIR_MASK; /* 50M ENET_REF_CLOCK output to PHY and ENET module. */
}

void BOARD_ENETFlexibleConfigure(enet_config_t *config)
{
#if 1 /* BOARD_NETWORK_USE_100M_ENET_PORT */
	config->miiMode = kENET_RmiiMode;
#else
	config->miiMode = kENET_RgmiiMode;
#endif

}

static void MDIO_Init(void)
{
    (void)CLOCK_EnableClock(s_enetClock[ENET_GetInstance(ENET_100M)]);
    ENET_SetSMI(ENET_100M, ENET_100M_CLOCK_FREQ, false);
}

static status_t MDIO_Write(uint8_t phyAddr, uint8_t regAddr, uint16_t data)
{
    return ENET_MDIOWrite(ENET_100M, phyAddr, regAddr, data);
}

static status_t MDIO_Read(uint8_t phyAddr, uint8_t regAddr, uint16_t *pData)
{
    return ENET_MDIORead(ENET_100M, phyAddr, regAddr, pData);
}

void SysTick_Handler(void)
{
    time_isr();
}

void Enet_100M_Mdio_Init(void)
{
	MDIO_Init();
    g_phy_resource.read  = MDIO_Read;
    g_phy_resource.write = MDIO_Write;
}

void Enet_100M_NetifConfig(void)
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
    enet_config.srcClockHz = ENET_100M_CLOCK_FREQ;
	
	netif_add(&netif, &netif_ipaddr, &netif_netmask, &netif_gw, &enet_config, ENET_100M_NETIF_INIT_FN, ethernet_input);
	netif_set_default(&netif);
	netif_set_up(&netif);
}

err_enum_t Enet_100M_WaitLinkUp(long timeout_ms)
{
	return ethernetif_wait_linkup(&netif, timeout_ms);;
}
