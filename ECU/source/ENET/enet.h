#ifndef _ENET_H_
#define _ENET_H_

#include "ping.h"
#include "ethernetif.h"
#include "lwip/init.h"
#include "lwip/opt.h"
#include "lwip/timeouts.h"
#include "netif/ethernet.h"

extern struct netif netif;
extern ip4_addr_t netif_ipaddr, netif_netmask, netif_gw;

#if BOARD_NETWORK_USE_1G_ENET_PORT
extern struct netif netif1G;
extern ip4_addr_t netif1G_ipaddr, netif1G_netmask, netif1G_gw;
#endif

void BOARD_InitModuleClock(void);
void IOMUXC_SelectENETClock(void);
void Enet_Mdio_Init(void);
void Enet_NetifConfig(void);
err_enum_t Enet_100M_WaitLinkUp(long timeout_ms);

#if BOARD_NETWORK_USE_1G_ENET_PORT
void BOARD_Init1GModuleClock(void);
void IOMUXC_SelectENET1GClock(void);
void Enet1G_Mdio_Init(void);
void Enet1G_NetifConfig(void);
err_enum_t Enet_1G_WaitLinkUp(long timeout_ms);
#endif

#endif /* _ENET_H_ */
