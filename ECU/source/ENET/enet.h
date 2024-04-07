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

void BOARD_InitModuleClock(void);
void IOMUXC_SelectENETClock(void);
void Enet_100M_Mdio_Init(void);
void Enet_100M_NetifConfig(void);
err_enum_t Enet_100M_WaitLinkUp(long timeout_ms);

#endif /* _ENET_H_ */
