#include "Includes.h"

bool bUdpTest = FALSE;

void Enet_UdpCallback(void)
{
	HAL_TIM_PeriodUdpElapsedCallback();
	COMMON_PRINTF("UDP[100M] Callback is called.\r\n");
}

#if BOARD_NETWORK_USE_1G_ENET_PORT
void Enet_UdpCallback_1G(void)
{
	HAL_TIM_PeriodUdpElapsedCallback_1G();
	COMMON_PRINTF("UDP[1G] Callback is called.\r\n");
}
#endif
