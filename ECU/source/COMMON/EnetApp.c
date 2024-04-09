#include "Includes.h"

bool bUdpTest = FALSE;

void Enet_UdpCallback(void)
{
	HAL_TIM_PeriodUdpElapsedCallback();
	ENETINFO_PRINTF("UDP Callback is called.\r\n", __func__);
}

