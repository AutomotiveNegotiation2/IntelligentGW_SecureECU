/*
  ***************************************************************************************************************
  ***************************************************************************************************************
  ***************************************************************************************************************

  File:		  	   tcpClientRAW.c
  Modified By:     ControllersTech.com
  Updated:    	   29-Jul-2021

  ***************************************************************************************************************
  Copyright (C) 2017 ControllersTech.com

  This is a free software under the GNU license, you can redistribute it and/or modify it under the terms
  of the GNU General Public License version 3 as published by the Free Software Foundation.
  This software library is shared with public for educational purposes, without WARRANTY and Author is not liable for any damages caused directly
  or indirectly by this software, read more about this on the GNU General Public License.

  ***************************************************************************************************************
*/


/**
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of and a contribution to the lwIP TCP/IP stack.
 *
 * Credits go to Adam Dunkels (and the current maintainers) of this software.
 *
 * Christiaan Simons rewrote this file to get a more stable  application.
 *
 **/

 /* This file was modified by ST */

#include "tcpClientRAW.h"

#include "lwip/tcp.h"

#include "stdio.h"
#include "string.h"

enum tcpecho_raw_states
{
  ES_NONE = 0,
  ES_ACCEPTED,
  ES_RECEIVED,
  ES_CLOSING
};

/* structure for maintaining connection infos to be passed as argument
   to LwIP callbacks*/
struct tcp_client_struct
{
  u8_t state;             /* current connection state */
  u8_t retries;
  struct tcp_pcb *pcb;    /* pointer on the current tcp_pcb */
  struct pbuf *p;         /* pointer on the received/to be transmitted pbuf */
};

/* This callback will be called, when the client is connected to the server */
static err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err);

/* This callback will be called, when the client receive data from the server */
static err_t tcp_client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);

/* This callback will be called, when the server Polls for the Client */
static err_t tcp_client_poll(void *arg, struct tcp_pcb *tpcb);

/* This callback will be called, when the server acknowledges the data sent by the client */
static err_t tcp_client_sent(void *arg, struct tcp_pcb *tpcb, u16_t len);

/* A Function to send the data to the server */
static void tcp_client_send(struct tcp_pcb *tpcb, struct tcp_client_struct *es);

/* Function to close the connection */
static void tcp_client_connection_close(struct tcp_pcb *tpcb, struct tcp_client_struct *es);

/* This is the part where we are going to handle the incoming data from the server */
static void tcp_client_handle (struct tcp_pcb *tpcb, struct tcp_client_struct *es);

static void tcp_client_free(struct tcp_client_struct *es);

static void recv_cb(struct pbuf *p);

uint8_t data[100];

/* create a struct to store data */
struct tcp_client_struct *esTx = 0;

struct tcp_pcb *pcbTx = 0;

void HAL_TIM_PeriodTcpElapsedCallback(void)
{
	char buf[100];

	/* Prepare the first message to send to the server */
	int len = sprintf(buf, "Sending TCPclient Message\r\n");

	/* allocate pbuf */
	esTx->p = pbuf_alloc(PBUF_TRANSPORT, len , PBUF_POOL);

	/* copy data to pbuf */
	pbuf_take(esTx->p, (char*)buf, len);

	tcp_client_send(pcbTx, esTx);
}

/* IMPLEMENTATION FOR TCP CLIENT

1. Create TCP block.
2. connect to the server
3. start communicating
*/

void tcp_client_init(void)
{
	/* 1. create new tcp pcb */
	pcbTx = tcp_new();

	/* 2. Connect to the server */
	ip_addr_t destIPADDR;
	IP_ADDR4(&destIPADDR, 192, 168, 0, 100);
	tcp_connect(pcbTx, &destIPADDR, 31, tcp_client_connected);
}

static void tcp_client_error(void *arg, err_t err)
{
  struct tcp_client_struct *es;

  LWIP_UNUSED_ARG(err);

  es = (struct tcp_client_struct *)arg;

  tcp_client_free(es);
}

static err_t tcp_client_connected(void *arg, struct tcp_pcb *newpcb, err_t err)
{
  err_t ret_err;
  struct tcp_client_struct *es;

  LWIP_UNUSED_ARG(arg);
  if ((err != ERR_OK) || (newpcb == NULL)) {
    return ERR_VAL;
  }

  /* Unless this pcb should have NORMAL priority, set its priority now.
     When running out of pcbs, low priority pcbs can be aborted to create
     new pcbs of higher priority. */
  tcp_setprio(newpcb, TCP_PRIO_MIN);

  es = (struct tcp_client_struct *)mem_malloc(sizeof(struct tcp_client_struct));
  if (es != NULL) {
    es->state = ES_ACCEPTED;
    es->pcb = newpcb;
    es->retries = 0;
    es->p = NULL;
    /* pass newly allocated es to our callbacks */
    tcp_arg(newpcb, es);
    tcp_recv(newpcb, tcp_client_recv);
    tcp_err(newpcb, tcp_client_error);
    tcp_poll(newpcb, tcp_client_poll, 0);
    tcp_sent(newpcb, tcp_client_sent);
    ret_err = ERR_OK;
  } else {
    ret_err = ERR_MEM;
  }
  return ret_err;
}

static err_t tcp_client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
  struct tcp_client_struct *es;
  err_t ret_err;

  LWIP_ASSERT("arg != NULL",arg != NULL);
  es = (struct tcp_client_struct *)arg;
  if (p == NULL) {
    /* remote host closed connection */
    es->state = ES_CLOSING;
    if(es->p == NULL) {
      /* we're done sending, close it */
      tcp_client_connection_close(tpcb, es);
    } else {
      /* we're not done yet */
      tcp_client_send(tpcb, es);
    }
    ret_err = ERR_OK;
  } else if(err != ERR_OK) {
    /* cleanup, for unknown reason */
    LWIP_ASSERT("no pbuf expected here", p == NULL);
    ret_err = err;
  }
  else if(es->state == ES_ACCEPTED) {
    /* first data chunk in p->payload */
    es->state = ES_RECEIVED;
    /* store reference to incoming pbuf (chain) */
    es->p = p;
	recv_cb(es->p);
    tcp_client_send(tpcb, es);
    ret_err = ERR_OK;
  } else if (es->state == ES_RECEIVED) {
    /* read some more data */
    if(es->p == NULL) {
      es->p = p;
	  recv_cb(es->p);
      tcp_client_send(tpcb, es);
    } else {
      struct pbuf *ptr;

      /* chain pbufs to the end of what we recv'ed previously  */
      ptr = es->p;
      pbuf_cat(ptr,p);
    }
    ret_err = ERR_OK;
  } else {
    /* unknown es->state, trash data  */
    tcp_recved(tpcb, p->tot_len);
    pbuf_free(p);
    ret_err = ERR_OK;
  }
  return ret_err;
}

static err_t tcp_client_poll(void *arg, struct tcp_pcb *tpcb)
{
  err_t ret_err;
  struct tcp_client_struct *es;

  es = (struct tcp_client_struct *)arg;
  if (es != NULL) {
    if (es->p != NULL) {
      /* there is a remaining pbuf (chain)  */
      tcp_client_send(tpcb, es);
    } else {
      /* no remaining pbuf (chain)  */
      if(es->state == ES_CLOSING) {
        tcp_client_connection_close(tpcb, es);
      }
    }
    ret_err = ERR_OK;
  } else {
    /* nothing to be done */
    tcp_abort(tpcb);
    ret_err = ERR_ABRT;
  }
  return ret_err;
}

static err_t tcp_client_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
  struct tcp_client_struct *es;

  LWIP_UNUSED_ARG(len);

  es = (struct tcp_client_struct *)arg;
  es->retries = 0;

  if(es->p != NULL) {
    /* still got pbufs to send */
    tcp_sent(tpcb, tcp_client_sent);
    tcp_client_send(tpcb, es);
  } else {
    /* no more pbufs to send */
    if(es->state == ES_CLOSING) {
      tcp_client_connection_close(tpcb, es);
    }
  }
  return ERR_OK;
}

static void tcp_client_send(struct tcp_pcb *tpcb, struct tcp_client_struct *es)
{
  struct pbuf *ptr;
  err_t wr_err = ERR_OK;

  while ((wr_err == ERR_OK) &&
         (es->p != NULL) &&
         (es->p->len <= tcp_sndbuf(tpcb))) {
    ptr = es->p;

    /* enqueue data for transmission */
    wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);
    if (wr_err == ERR_OK) {
      u16_t plen;

      plen = ptr->len;
      /* continue with next pbuf in chain (if any) */
      es->p = ptr->next;
      if(es->p != NULL) {
        /* new reference! */
        pbuf_ref(es->p);
      }
      /* chop first pbuf from chain */
      pbuf_free(ptr);
      /* we can read more data now */
      tcp_recved(tpcb, plen);
    } else if(wr_err == ERR_MEM) {
      /* we are low on memory, try later / harder, defer to poll */
      es->p = ptr;
    } else {
      /* other problem ?? */
    }
  }
}

static void tcp_client_free(struct tcp_client_struct *es)
{
  if (es != NULL) {
    if (es->p) {
      /* free the buffer chain if present */
      pbuf_free(es->p);
    }

    mem_free(es);
  }
}

static void tcp_client_connection_close(struct tcp_pcb *tpcb, struct tcp_client_struct *es)
{
  tcp_arg(tpcb, NULL);
  tcp_sent(tpcb, NULL);
  tcp_recv(tpcb, NULL);
  tcp_err(tpcb, NULL);
  tcp_poll(tpcb, NULL, 0);

  tcp_client_free(es);

  tcp_close(tpcb);
}

/* Handle the incoming TCP Data */
static void tcp_client_handle(struct tcp_pcb *tpcb, struct tcp_client_struct *es)
{
	/* get the Remote IP */
	ip4_addr_t inIP = tpcb->remote_ip;
	uint16_t inPort = tpcb->remote_port;

	/* Extract the IP */
	char *remIP = ipaddr_ntoa(&inIP);

//	esTx->state = es->state;
//	esTx->pcb = es->pcb;
//	esTx->p = es->p;

	esTx = es;
	pcbTx = tpcb;
}

static void recv_cb(struct pbuf *p)
{
	char buf[100];

	memcpy(buf, (char *)(p->payload), p->len);

	PRINTF("Recv Msg : %s, Len : %d\r\n", buf, p->len);
}
