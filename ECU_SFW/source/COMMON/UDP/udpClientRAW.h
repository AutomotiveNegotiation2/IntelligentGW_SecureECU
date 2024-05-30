/*
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************

  File:		  udpClientRAW.h
  Author:     ControllersTech.com
  Updated:    Jul 23, 2021

  ***************************************************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ***************************************************************************************************************
*/


#ifndef INC_UDPCLIENTRAW_H_
#define INC_UDPCLIENTRAW_H_

#include "board.h"
#include "enet.h"

enum {
	ETH_100M = 0,
	ETH_1G,
	ETH_MAX,
};

void HAL_TIM_PeriodUdpElapsedCallback(void);
err_t create_udp_socket(void);

#if BOARD_NETWORK_USE_1G_ENET_PORT
err_t create_udp_socket_1G(void);
void HAL_TIM_PeriodUdpElapsedCallback_1G(void);
#endif

#endif /* INC_UDPCLIENTRAW_H_ */
