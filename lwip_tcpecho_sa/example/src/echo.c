/*
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
 * Christiaan Simons rewrote this file to get a more stable echo example.
 */

/**
 * @file
 * TCP echo server example using raw API.
 *
 * Echos all bytes sent by connecting client,
 * and passively closes when client is done.
 *
 */


#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/udp.h"

#if LWIP_TCP

static struct udp_pcb *echo_pcb;

enum echo_states
{
  ES_NONE = 0,
  ES_ACCEPTED,
  ES_RECEIVED,
  ES_CLOSING
};

ip_addr_t m_ipaddr_dst;
u16_t m_port_dst;

struct echo_state
{
  u8_t state;
  u8_t retries;
  struct udp_pcb *pcb;
  /* pbuf (chain) to recycle */
  struct pbuf *p;
};

err_t echo_recv(void *arg, struct udp_pcb *tpcb, struct pbuf *p, err_t err);

void echo_close(struct udp_pcb *tpcb, struct echo_state *es);

err_t
echo_init(ip_addr_t ipaddr, int port, ip_addr_t ipaddr_dst, u16_t port_dst)
{
  echo_pcb = udp_new();
  if (echo_pcb != NULL)
  {
	  m_ipaddr_dst = ipaddr_dst;
	  m_port_dst = port_dst;
      return  udp_bind(echo_pcb, &ipaddr, port);
  }
  return ERR_MEM;

}

err_t
echo_recv(void *arg, struct udp_pcb *tpcb, struct pbuf *p, err_t err)
{
	if(p == NULL)
	   return ERR_MEM;

	udp_sendto(tpcb, p, &m_ipaddr_dst, m_port_dst);
	pbuf_free(p);

	return ERR_OK;
}
 

void
echo_close(struct udp_pcb *tpcb, struct echo_state *es)
{

  udp_recv(tpcb, NULL, 0);
  
  if (es != NULL)
  {
    mem_free(es);
  }  

}

#endif /* LWIP_TCP */
