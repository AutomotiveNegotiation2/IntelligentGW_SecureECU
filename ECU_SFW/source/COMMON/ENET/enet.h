#ifndef _ENET_H_
#define	_ENET_H_

#ifndef configMAC_ADDR
#include "fsl_silicon_id.h"
#endif

#include "fsl_phyksz8081.h"
#if BOARD_NETWORK_USE_1G_ENET_PORT
#include "fsl_phyrtl8211f.h"
#endif

#include "ping.h"
#include "ethernetif.h"
#include "lwip/init.h"
#include "lwip/opt.h"
#include "lwip/timeouts.h"
#include "netif/ethernet.h"

extern struct netif netif;
extern ip4_addr_t netif_ipaddr, netif_netmask, netif_gw;

#if BOARD_NETWORK_USE_1G_ENET_PORT
extern struct netif netif_1G;
extern ip4_addr_t netif_ipaddr_1G, netif_netmask_1G, netif_gw_1G;
#endif

void BOARD_InitModuleClock(void);
void IOMUXC_SelectENETClock(void);
void Enet_Mdio_Init(void);
void Enet_NetifConfig(void);
void Enet_WaitLinkUp(void);
void Enet_IPADDR_Config(void);
void Enet_Init(void);
bool Enet_GetLinkUp_100M(void);

#if BOARD_NETWORK_USE_1G_ENET_PORT
void Enet_Mdio_Init_1G(void);
bool Enet_GetLinkUp_1G(void);
err_enum_t Enet_WaitLinkUp_1G(long timeout_ms);
#endif

#endif /* _ENET_H_ */