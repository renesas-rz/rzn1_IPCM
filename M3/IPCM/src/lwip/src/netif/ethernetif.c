/**
* @file
* Ethernet Interface Skeleton
*
*/

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
* This file is part of the lwIP TCP/IP stack.
*
* Author: Adam Dunkels <adam@sics.se>
*
*/

/*
* This file is a skeleton for developing Ethernet network interface
* drivers for lwIP. Add code to the low_level functions and do a
* search-and-replace for the word "ethernetif" to replace it with
* something that better describes your network interface.
*/

#include "lwip/opt.h"

#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "lwip/etharp.h"
#include "netif/ppp/pppoe.h"

#include "lwip/sys.h"
#include "kernel.h"
#include "kernel_id.h"
#include "platform.h"
#include "r_gmac_rzn1_if.h"
#include "r_iomux_rzn1_if.h"
#include "asb_low_level_init.h"

#include <string.h>
/* Define those to better describe your network interface. */
#define IFNAME0 'r'
#define IFNAME1 'z'

#define PHY_RESET_PIN GPIO_PORT_2B_PIN_20 // GPIO94

#define ETH_MTU_LEN                 1536
#define ETH_PORT_INTER_CONNECTION   19  //  SWITCH PORTIN = MAC2... (secion 8.2.1 RZN1 introducion manual)

#define TASK_ETH_RX_PRIORITY 5
#define TASK_ETH_RX_STACK    0x400

#define N1L_PORT PORT4
//#define N1L_PORT PORT5

// TODO: Mark what was modified

/**
* Helper struct to hold private data used to operate your ethernet interface.
* Keeping the ethernet address of the MAC in this struct is not necessary
* as it is already kept in the struct netif.
* But this is only an example, anyway...
*/
struct ethernetif {
  struct eth_addr *ethaddr;
  /* Add whatever per-interface state that is needed here. */
};

static void eth_rx_callback(u8_t ch);
static struct pbuf * gmac_buf_get (void);

static sys_mutex_t lock_eth_tx = 0;
char transmit_buf[ETH_MTU_LEN];
static gmac_eth_frame frame;

static uint16_t array_size[2];
static uint64_t DST_MAC[2];
static uint64_t SRC_MAC[2];
static uint16_t protocol[2];

static gmac_transfer_data sending_chan =
{.chan_num = GMAC_CHAN_2, .port = N1L_PORT, .receive_buf.payload = NULL, .receive_buf.dst_mac = &DST_MAC[0], .receive_buf.src_mac = &SRC_MAC[0], .receive_buf.type = &protocol[0], .payload_length = &array_size[0]};

static gmac_transfer_data ctrl_chan = // $REA why do we need to open this port?
{.chan_num = GMAC_CHAN_1, .port = PORT1, .receive_buf.payload = NULL, .receive_buf.dst_mac = &DST_MAC[0], .receive_buf.src_mac = &SRC_MAC[0], .receive_buf.type = &protocol[0], .payload_length = &array_size[0]};

/* Forward declarations. */
static void  ethernetif_input(struct netif *netif);

/**
* In this function, the hardware should be initialized.
* Called from ethernetif_init().
*
* @param netif the already initialized lwip network interface structure
*        for this ethernetif
*/
static void
low_level_init(struct netif *netif)
{
  ER_RET ret_val;
  
  /* set MAC hardware address length */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;

  /* set MAC hardware address */
  netif->hwaddr[0] = ASB_mac_id[0];
  netif->hwaddr[1] = ASB_mac_id[1];
  netif->hwaddr[2] = ASB_mac_id[2];
  netif->hwaddr[3] = ASB_mac_id[3];
  netif->hwaddr[4] = ASB_mac_id[4];
  netif->hwaddr[5] = ASB_mac_id[5];

  /* maximum transfer unit */
  netif->mtu = ETH_MTU_LEN;
  
  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
  
#if LWIP_IPV6 && LWIP_IPV6_MLD
  /*
  * For hardware/netifs that implement MAC filtering.
  * All-nodes link-local is handled by default, so we must let the hardware know
  * to allow multicast packets in.
  * Should set mld_mac_filter previously. */
  if (netif->mld_mac_filter != NULL) {
    ip6_addr_t ip6_allnodes_ll;
    ip6_addr_set_allnodes_linklocal(&ip6_allnodes_ll);
    netif->mld_mac_filter(netif, &ip6_allnodes_ll, NETIF_ADD_MAC_FILTER);
  }
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */
  
  /* Do whatever else is needed to initialize interface. */

  // tslp_tsk(100); // potential delay around PHY reset

  // $REA Enable PHY
  R_GPIO_PinOpen(PHY_RESET_PIN);
  R_GPIO_PinDirectionSet(PHY_RESET_PIN, GPIO_DIRECTION_OUTPUT); 
  
//  R_GPIO_PinWrite(PHY_RESET_PIN, GPIO_LEVEL_HIGH);
//  for (int i = 0; i < 0xfff; i++);
//  R_GPIO_PinWrite(PHY_RESET_PIN, GPIO_LEVEL_LOW);
//  for (int i = 0; i < 0xfff; i++);
  R_GPIO_PinWrite(PHY_RESET_PIN, GPIO_LEVEL_HIGH);
  //  tslp_tsk(100);  // potential delay around PHY reset

  ret_val = R_GMAC_Init();
  
  if (ret_val != ER_OK)
  {
    return;
  }
  // tslp_tsk(100);    // potential delay around PHY reset

  while(!R_GMAC_LinkStatus(N1L_PORT));      /*Wait till the link is up*/
  
  R_GMAC_Control(&sending_chan, REG_CALLBACK, (uint32_t)eth_rx_callback);
  
  ret_val = R_GMAC_Control(&sending_chan, ETH_MUX_CTRL, ETH_PORT_INTER_CONNECTION); // $REA
  
  if (ret_val != ER_OK)
  {
    return;
  }
  
  R_GMAC_Open(&ctrl_chan); // $REA Why is this necessary?
  
  ret_val = R_GMAC_Open(&sending_chan);
  
  if (ret_val != ER_OK)
  {
    return;
  }
  
  sys_thread_new("ETH Rx", (lwip_thread_fn) ethernetif_input, netif, TASK_ETH_RX_STACK, TASK_ETH_RX_PRIORITY);
    
  sys_mutex_new(&lock_eth_tx);
}

/**
* This function should do the actual transmission of the packet. The packet is
* contained in the pbuf that is passed to the function. This pbuf
* might be chained.
*
* @param netif the lwip network interface structure for this ethernetif
* @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
* @return ERR_OK if the packet could be sent
*         an err_t value if the packet couldn't be sent
*
* @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
*       strange results. You might consider waiting for space in the DMA queue
*       to become available since the stack doesn't retry to send a packet
*       dropped because of memory failure (except for the TCP timers).
*/

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
  struct pbuf *q;
  ER_RET ret_val;
  
  sys_mutex_lock(&lock_eth_tx);
  
#if ETH_PAD_SIZE
  pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif
  
  frame.size  = 0;
  
  for (q = p; q != NULL; q = q->next) 
  {
    u8_t * ptr_q = (u8_t*)q->payload;
    if (q == p)
    {
      
      frame.dst_mac_lsw = (uint32_t) SET_MAC_ADDRESS_LSW(ptr_q[2], 
                                                         ptr_q[3], 
                                                         ptr_q[4], 
                                                         ptr_q[5]);
      
      frame.dst_mac_msw = SET_MAC_ADDRESS_MSW(ptr_q[0], ptr_q[1]);
      
      frame.type = (ptr_q[12] << 8) | ptr_q[13];
      
      memcpy(transmit_buf, ptr_q + ETH_FRAME_LENGTH, q->len - ETH_FRAME_LENGTH);
      frame.size = q->len - ETH_FRAME_LENGTH;
    }
    else
    {
      if ((frame.size + q->len) < sizeof(transmit_buf))
      {
        memcpy(transmit_buf + frame.size, ptr_q, q->len);
        frame.size += q->len;
      }
      else
      {
        return ERR_IF;
      }
    }
  }
  
  frame.payload = transmit_buf;
  
  ret_val = R_GMAC_Write(&sending_chan, &frame);      /*Send the buffer out*/
  
  if (ret_val != ER_OK)
  {
    return ERR_IF;
  }
  
  MIB2_STATS_NETIF_ADD(netif, ifoutoctets, p->tot_len);
  if (((u8_t*)p->payload)[0] & 1) 
  {
    /* broadcast or multicast packet*/
    MIB2_STATS_NETIF_INC(netif, ifoutnucastpkts);
  } 
  else 
  {
    /* unicast packet */
    MIB2_STATS_NETIF_INC(netif, ifoutucastpkts);
  }
  /* increase ifoutdiscards or ifouterrors on error */
  
#if ETH_PAD_SIZE
  pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif
  
  LINK_STATS_INC(link.xmit);
  
  sys_mutex_unlock(&lock_eth_tx);
  
  return ERR_OK;
}

/**
* Should allocate a pbuf and transfer the bytes of the incoming
* packet from the interface into the pbuf.
*
* @param netif the lwip network interface structure for this ethernetif
* @return a pbuf filled with the received packet (including MAC header)
*         NULL on memory error
*/
static struct pbuf *
low_level_input(struct netif *netif)
{
  struct pbuf * p;
  
  p = gmac_buf_get();
  
  if (p == NULL)
    return p;
  
  MIB2_STATS_NETIF_ADD(netif, ifinoctets, p->tot_len);
  if (((u8_t*)p->payload)[0] & 1) 
  {
    /* broadcast or multicast packet*/
    MIB2_STATS_NETIF_INC(netif, ifinnucastpkts);
  } 
  else 
  {
    /* unicast packet*/
    MIB2_STATS_NETIF_INC(netif, ifinucastpkts);
  }
#if ETH_PAD_SIZE
  pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif
  
  LINK_STATS_INC(link.recv);
  
  return p;
}

/**
* This function should be called when a packet is ready to be read
* from the interface. It uses the function low_level_input() that
* should handle the actual reception of bytes from the network
* interface. Then the type of the received packet is determined and
* the appropriate input function is called.
*
* @param netif the lwip network interface structure for this ethernetif
*/
static void
ethernetif_input(struct netif *netif)
{
  struct pbuf *p;
  ER ercd;
  FLGPTN flags = 0;
  
  while (1)
  {
    
    ercd = wai_flg(ID_FLG_ETH_RX_MAC, EV_ETH_RX_PACKET_READY, TWF_ORW, &flags);
    if ((E_OK != ercd) || (0 == flags)) 
    {
      continue;
    }
        
    /* move received packet into a new pbuf */
    do
    {
      p = low_level_input(netif);
      /* if no packet could be read, silently ignore this */
      if (p != NULL) 
      {
        /* pass all packets to ethernet_input, which decides what packets it supports */
        if (netif->input(p, netif) != ERR_OK) 
        {
          LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
          pbuf_free(p);
          p = NULL;
        }
      }
    }while (p != NULL);
    
  }
}

/**
* Should be called at the beginning of the program to set up the
* network interface. It calls the function low_level_init() to do the
* actual setup of the hardware.
*
* This function should be passed as a parameter to netif_add().
*
* @param netif the lwip network interface structure for this ethernetif
* @return ERR_OK if the loopif is initialized
*         ERR_MEM if private data couldn't be allocated
*         any other err_t on error
*/
err_t
ethernetif_init(struct netif *netif)
{
  struct ethernetif *ethernetif;
  
  LWIP_ASSERT("netif != NULL", (netif != NULL));
  
  ethernetif = mem_malloc(sizeof(struct ethernetif));
  if (ethernetif == NULL) {
    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory\n"));
    return ERR_MEM;
  }
  
#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */
  
  /*
  * Initialize the snmp variables and counters inside the struct netif.
  * The last argument should be replaced with your link speed, in units
  * of bits per second.
  */
  MIB2_INIT_NETIF(netif, snmp_ifType_ethernet_csmacd, 100000000);
  
  netif->state = ethernetif;
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  /* We directly use etharp_output() here to save a function call.
  * You can instead declare your own function an call etharp_output()
  * from it if you have to do some checks before sending (e.g. if link
  * is available...) */
  netif->output = etharp_output;
#if LWIP_IPV6
  netif->output_ip6 = ethip6_output;
#endif /* LWIP_IPV6 */
  netif->linkoutput = low_level_output;
  
  ethernetif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);
  
  /* initialize the hardware */
  low_level_init(netif);
  
  return ERR_OK;
}

/**
* This callback function is called from the GMAC driver when packet is 
* ready to be read
*
* $REA This callback mechanism is not part of the original driver
* $REA Calling hwrtos function from this callback will fail if the calling GMAC
*      ISR is not triggered by the hwrtos (i.e. using the static interrupt table)
*      E.g. iset_flg will return error -25 (CPU in locked state)
*
* @param ch GMAC channel number (0 or 1)
*/
static void eth_rx_callback(u8_t ch)
{
  if (ch == sending_chan.chan_num)
  {
    iset_flg(ID_FLG_ETH_RX_MAC, EV_ETH_RX_PACKET_READY); 
  }
}

/**
* Reads available ethernet packet and returns the packet data in a lwip buffer 
*
* $REA This callback mechanism is not part of the original driver
*
* @return Pointer to lwip buffer
*         NULL if no ethernet packet exists          
*/
static struct pbuf * gmac_buf_get (void)
{
  u32_t index = 0;
  struct pbuf *p, *q;
  uint16_t len = 0;
  uint8_t * p_buf = NULL;
  
  p = NULL;
  
  R_GMAC_Read(sending_chan.chan_num, &p_buf, &len);
  
  if (p_buf == NULL || len == 0)
    return NULL;
  
  p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
  
  if (p != NULL) 
  {
    for (q = p; q != NULL; q = q->next) 
    { 
      memcpy((u8_t*)q->payload, (u8_t*)&p_buf[index], q->len);
      index = index + q->len;
    }
  }
  
  return p;
}
