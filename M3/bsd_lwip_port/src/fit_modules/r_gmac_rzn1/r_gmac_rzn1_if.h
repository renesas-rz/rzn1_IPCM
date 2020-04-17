/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * $Revision: 1346 $
 * $Date: 2019-03-07 16:48:23 +0000 (Thu, 07 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_gmac_rzn1_if.h
 * Description  :  GMAC driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_GMAC_RZN1_IF_H__
#define R_GMAC_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define GMAC_CHAN_1              (0)
#define GMAC_CHAN_2              (1)
#define MAX_GMAC                 (2)
#define ARP                     (0x0806)        /* Address resolution protocol */
#define IPv4                    (0x0800)        /* Internet Protocol version 4 */
#define ETHERNET1               (0x0001)        /* Hardware type Ethernet (1) */
#define SET_IP_ADDRESS(a, b, c, d)   (((unsigned int) (a) << 24) | ((b) << 16) | ((c) << 8) | (d))
#define ETH_FRAME_LENGTH        (14)                /*Ethernet frame length*/
#define MY_IPv4_ADDRESS            (SET_IP_ADDRESS(192, 168, 1, 10))

/**< MAC address wrapper */
#define SET_MAC_ADDRESS_MSW(a, b)         ((uint16_t) ((a) << 8) | (b))
#define SET_MAC_ADDRESS_LSW(c, d, e, f)   ((uint32_t) (((c) << 24) | ((d) << 16) | ((e) << 8) | (f)))
#define MY_MAC_ADDR_MSW         (SET_MAC_ADDRESS_MSW(ASB_mac_id[0], ASB_mac_id[1]))                         /*Modifiable device MAC address*/
#define MY_MAC_ADDR_LSW         (SET_MAC_ADDRESS_LSW(ASB_mac_id[2], ASB_mac_id[3], ASB_mac_id[4], ASB_mac_id[5]))

/* Define PHY addresses*/
#define PORT1        (0x08)             /*PHY address of port 1*/
#define PORT2        (0x01)             /*PHY address of port 2*/
#define PORT3        (0x0A)             /*PHY address of port 3*/
#define PORT4        (0x04)             /*PHY address of port 4*/
#define PORT5        (0x05)             /*PHY address of port 5*/

#define LINK_BIT_1_2_3_PORTS                (0x00000400)
#define LINK_BIT_4_5_PORTS                  (0x00000004)
#define AUTONEG_COMPLETE                    (0x00000020)

/* Version Number of API. */
#define GMAC_RZN1_VERSION_MAJOR           (1)
#define GMAC_RZN1_VERSION_MINOR           (3)

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
/* GMAC channel state */
typedef enum
{
    GMAC_STATE_CLOSED = 0, /* Channel uninitialised */
    GMAC_STATE_OPEN, /* Channel initialised and idle */
} GMAC_STATE;

typedef enum
{
    SET_SPEED,    /* Change speed in PHY, GMAC an RGMII/MII interface */
    SET_FILTER,   /* Change filtering setting for GMAC*/
    ETH_MUX_CTRL, /* Change control settings for Ethernet switch mux */
    REG_CALLBACK  /* Register callback for receive notification */ // $REA Added
} gmac_control_state_t;

typedef enum
{
    DISABLE = 0, ENABLE = 1,
} gmac_control;

/*Descirbes whether the filter MAC addres should be used for source address filtering or destination */
typedef enum
{
    Destination_Address = 0, Source_Address = 1,
} gmac_comparison_field;

/*Operation modes: FD - full duplex, HD - half duplex */
typedef enum
{
    FD_1G, HD_1G, FD_100M, HD_100M, FD_10M, HD_10M,
} gmac_operation_mode_t;

/*Pointer to data of the last received packet*/
typedef struct
{
    char *payload;
    uint64_t *dst_mac;
    uint64_t *src_mac;
    uint16_t *type;
} gmac_receive_buf;

/*Stores the speed of the operation on the link and received data of the last reecived packet*/
typedef struct
{
    uint8_t chan_num;
    uint8_t port;
    gmac_operation_mode_t mode;
    gmac_receive_buf receive_buf;
    uint16_t *payload_length;
} gmac_transfer_data;

/*Filtering configurations*/
typedef struct
{
    gmac_control receive_all;
    gmac_control sa_filter;
    gmac_control sa_inverse_filter;
    gmac_control da_inverse_filter;
    gmac_control disable_broadcast;
    gmac_control promiscuous_mode;
    gmac_comparison_field mac_comparison_field[17]; /*Tells whether the filter MAC addres should be used for source address filtering or destination */
    uint16_t msw_mac_addr[17]; /*Most significant word of MAC address which is desired to be used for filtering (18 address can be used for filtering, 1 of them is hard coded with device MAC address*/
    uint32_t lsw_mac_addr[17]; /*Most significant word of MAC address which is desired to be used for filtering*/
    uint8_t number_of_filtered_addr; /*Number of added addresses*/
} gmac_filter_config;

/*Ethernet frame data*/
typedef struct
{
    uint32_t dst_mac_lsw;
    uint16_t dst_mac_msw;
    uint16_t type;
    char *payload;
    uint16_t size;
} gmac_eth_frame;

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
void R_GMAC_GetVersion(void *buf);
ER_RET R_GMAC_Init(void);
ER_RET R_GMAC_Uninit(void);
ER_RET R_GMAC_Open(const gmac_transfer_data *data);
ER_RET R_GMAC_Close(const gmac_transfer_data *data);
uint8_t R_GMAC_LinkStatus(uint8_t port);
ER_RET R_GMAC_Read (uint8_t chan_num, uint8_t ** p_buf, uint16_t * p_len);
ER_RET R_GMAC_Write(const gmac_transfer_data *data, const gmac_eth_frame *eth_frame);
ER_RET R_GMAC_Control(const gmac_transfer_data *data,
        gmac_control_state_t control_request, uint32_t control_options);

#endif /* R_GMAC_RZN1_IF_H__ */
