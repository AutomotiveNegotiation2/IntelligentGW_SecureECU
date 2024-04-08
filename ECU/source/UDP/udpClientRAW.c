/*
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************

  File:		  udpClientRAW.c
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


#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"

#include "stdio.h"
#include "string.h"

#include "udpClientRAW.h"


void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port);
static void udpClient_send(void);
static err_t send_msg_to_dest(void);

struct udp_pcb *upcb;
char buffer[100];
static int counter = 0;
ip4_addr_t destIPAddr; 

void HAL_TIM_PeriodUdpElapsedCallback(void)
{
	send_msg_to_dest();
}

void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	struct pbuf *pbuf;

	/* Copy the data from the pbuf */
	strncpy (buffer, (char *)p->payload, p->len);
	/* allocate pbuf from pool*/
	pbuf = pbuf_alloc(PBUF_TRANSPORT,strlen((char*)buffer), PBUF_POOL);
	if (pbuf != NULL)
	{
		/* copy data to pbuf */
		pbuf_take(pbuf, (char*)buffer, strlen((char*)buffer));
		/* send udp data */
		udp_send(upcb, pbuf);
		/* free pbuf */
		pbuf_free(pbuf);
	}
}

err_t send_msg_to_dest(void)
{
	struct pbuf *p;

	sprintf((char*)buffer, "sending udp client message %d\r\n", (int)counter);
	/* allocate pbuf from pool*/
	p = pbuf_alloc(PBUF_TRANSPORT,strlen((char*)buffer), PBUF_POOL);
	if (p != NULL)
	{
		/* copy data to pbuf */
		pbuf_take(p, (char*)buffer, strlen((char*)buffer));
		/* send udp data */
		udp_send(upcb, p);
		/* free pbuf */
		pbuf_free(p);

		return ERR_OK;
	}

	return ERR_MEM;
}

err_t create_udp_socket(void)
{
	err_t err = ERR_OK;

	upcb = udp_new();
	if (upcb == NULL)
	{
		return ERR_MEM;
	}
	// Load the static IP of the destination address

	IP4_ADDR(&destIPAddr,192,168,0,255);

	upcb->local_port = 4004;
	// Set our local port to 4004
	// Should bind to the local ip and port
	err = udp_bind(upcb,IP4_ADDR_ANY,4004);
	if (err != ERR_OK)
	{
		return err;
	}
	// Connect to the other port
	err = udp_connect(upcb,&destIPAddr,1234);
	if (err != ERR_OK)
	{
		return err;
	}
	// Set the receive function
	udp_recv(upcb,udp_receive_callback,NULL);
	return err;
}

#if 0
void udpClient_connect(void)
{
	err_t err;

	/* 1. Create a new UDP control block  */
	upcb = udp_new();
#if 0
	/* Bind the block to module's IP and port */
	ip_addr_t myIPaddr;
	//IP_ADDR4(&myIPaddr, 192, 168, 0, 111);
	IP_ADDR4(&myIPaddr, 192, 168, 0, 102);
	udp_bind(upcb, &myIPaddr, 8);
#endif

	/* configure destination IP address and port */
	ip_addr_t DestIPaddr;
	//IP_ADDR4(&DestIPaddr, 192, 168, 0, 102);
	IP_ADDR4(&DestIPaddr, 192, 168, 0, 100);
	err= udp_connect(upcb, &DestIPaddr, 7);

	if (err == ERR_OK)
	{
#if 0
		/* 2. Send message to server */
		udpClient_send ();
#endif
		/* 3. Set a receive callback for the upcb */
		udp_recv(upcb, udp_receive_callback, NULL);
	}
}

static void udpClient_send(void)
{
  struct pbuf *txBuf;
  char data[100];

  int len = sprintf(data, "sending UDP client message %d", counter);

  /* allocate pbuf from pool*/
  txBuf = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);

  if (txBuf != NULL)
  {
    /* copy data to pbuf */
    pbuf_take(txBuf, data, len);

    /* send udp data */
    udp_send(upcb, txBuf);

    /* free pbuf */
    pbuf_free(txBuf);
  }
}


void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p, const ip_addr_t *addr, u16_t port)
{
	/* Copy the data from the pbuf */
	strncpy (buffer, (char *)p->payload, p->len);

	/*increment message count */
	counter++;

	/* Free receive pbuf */
	pbuf_free(p);
}
#endif

