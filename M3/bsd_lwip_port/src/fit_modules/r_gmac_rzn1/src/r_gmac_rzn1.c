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
 * FILE         :  r_gmac_rzn1.c
 * Description  :  GMAC driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "r_sysctrl_rzn1_if.h"
#include "iodefine.h"
#include "r_gmac_rzn1_if.h"
#include "r_gmac_rzn1.h"
#include "r_a5psw_rzn1.h"
#include "r_phy_rzn1.h"
#include "r_timer_rzn1_if.h"
#include "r_gpio_rzn1_if.h"
#include "r_gmac_rzn1_config.h"
#include "asb_low_level_init.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define TIMEOUT     (0xFFFFFF)
   
#define HWISR_ENABLED 1 // $REA
/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
struct MACDMA_desc
{
    uint32_t des0;
    uint32_t des1;
    uint32_t des2;
    uint32_t des3;
};

/***********************************************************************************************************************
 *  External function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local (private) variables
 **********************************************************************************************************************/
static volatile GMAC1_Type *BaseAddress1 = (volatile GMAC1_Type *) RZN1_GMAC0_BASE;
static volatile GMAC2_Type *BaseAddress2 = (volatile GMAC2_Type *) RZN1_GMAC1_BASE;

#ifdef CORE_CA7
UNCACHED_BUFFER struct MACDMA_desc tx_desc1[1];
UNCACHED_BUFFER struct MACDMA_desc rx_desc1[64];
UNCACHED_BUFFER struct MACDMA_desc* tx_desc_top1;
UNCACHED_BUFFER struct MACDMA_desc* rx_desc_top1;
UNCACHED_BUFFER static uint8_t rx_buf1[64][2048];
UNCACHED_BUFFER uint32_t eth_frame[4];
#else
volatile struct MACDMA_desc tx_desc1[1];
volatile struct MACDMA_desc rx_desc1[64];
volatile struct MACDMA_desc* tx_desc_top1;
volatile struct MACDMA_desc* rx_desc_top1;
uint8_t rx_buf1[64][2048]; //AE static
uint32_t eth_frame[4];
#endif
static uint16_t *protocol[2];
static uint64_t *dst_mac[2];
static uint64_t *src_mac[2];
static uint16_t *length[2];
static char *receive_buf[2];
static char *transmit_buf[2];
static link_status port_link_state[5];

#if 0
static gpio_port_pin_t phy_gpio_int[5] =
{ GPIO_PORT_3A_PIN_24, GPIO_PORT_3A_PIN_04, GPIO_PORT_2A_PIN_28, GPIO_PORT_3A_PIN_25, GPIO_PORT_3A_PIN_27 };
#endif

static gpio_port_pin_t phy_gpio_int[5] =
{ GPIO_NO_PIN, GPIO_NO_PIN, GPIO_NO_PIN, GPIO_PORT_2A_PIN_05, GPIO_PORT_2A_PIN_06 }; // $REA

static gmac_callback receive_callback;

/***********************************************************************************************************************
 * Local (private) function declarations*/

//static void gmac_isr_handler (IRQn_Type *irq_num_ptr);
static void set_receive_desc ();
static void set_tx_desc (uint32_t eth_frame, uint32_t payload, uint16_t len);
static uint32_t change_long_endian (uint32_t arg);
static void phy_irq_handler (gpio_port_pin_t pin);
static ER_RET reset_config (uint8_t phy_addr, uint8_t conv_num);
static uint8_t mii_status_check (uint8_t phy_addr);

/***********************************************************************************************************************
 *
 *  Function:       gmac_init
 *
 *  Return value:   Error value
 *
 *  Parameters:     None
 *
 *  Description:    Initialises the clock for both GMAC channels and sets up
 *                  RGMII/GMII converters.
 **********************************************************************************************************************/
ER_RET gmac_init ()
{
    uint32_t i;
    ER_RET ret_val = ER_OK;
    R_SYSCTRL_EthReg();
    (void) R_SYSCTRL_EnableGMAC();

    eht_protection_control(1);

    /* Setting up RGMII/GMII configurations by hand*/
    write_eth_reg(SW_MODE_REG, 19, NO_MASK); /*Switch mux mode*/
    for (i = 0; i < 3; i++)
    {
        write_eth_reg(CONCTRL(i), RGMII_1G_MODE, CONV_MODE_MASK); /*Speed of the converter*/
    }
    write_eth_reg(PHY_LINK, SWLNK_LOW_ACTIVE, SWLINK_MODE_MASK);
    for (i = 3; i < 5; i++)
    {
        write_eth_reg(CONCTRL(i), RGMII_100M_MODE, CONV_MODE_MASK); /*Speed of the converter*/
    }
    write_eth_reg(PTP_MODE_REG, MGHz_25, PTP_MODE_MASK); /*Select clock source of PTP timer for GMAC1 and GMAC2*/

    reset_rgmii_conv();

    eht_protection_control(0);

    switch_init();

    /*Configure LED[0] for all PHYs to display only link status for A5PSW */
    phy_reg_write(0x8, 16, 0x1010, 3); /* For PORT1 LED set up is not important cause this port does not use A5PSW*/
    phy_reg_write(0x1, 16, 0x1010, 3);
    phy_reg_write(0xA, 16, 0x1010, 3);
    phy_write(0x5, 0x1E, 0x4000);
    phy_write(0x4, 0x1E, 0x4000);

    for (i = 0; i < 5; i++)
    {
        port_link_state[i] = LINK_DOWN;
    }
    
    receive_callback = NULL;

    return ret_val;
}
/***********************************************************************************************************************
 End of function gmac_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       gmac_uninit
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Disables the clock for both GMAC channels
 *
 **********************************************************************************************************************/
void gmac_uninit ()
{
    uint32_t i = 0;

    BaseAddress1->Bus_Mode.BIT.SWR = 1u; /* Reset PHY*/
    BaseAddress2->Bus_Mode.BIT.SWR = 1u;
    while ((i++) < TIMEOUT) /* Wait reset*/
    {
        if ((0 == BaseAddress1->Bus_Mode.BIT.SWR)
            && (0 == BaseAddress2->Bus_Mode.BIT.SWR)
              )
        {
            break;
        }
    }

    /* Flush transmit FIFO */
    BaseAddress1->Operation_Mode.BIT.FTF = 1u; /*Flush down transmit FIFO*/
    BaseAddress2->Operation_Mode.BIT.FTF = 1u;
    R_SYSCTRL_DisableGMAC(); /*Disable GMAC clock*/

}
/***********************************************************************************************************************
 End of function gmac_uninit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       gmac_open
 *
 *  Return value:   Error value
 *
 *  Parameters:     chan_num - GMAC channel
 *                  port - PHY address
 *                  data - a pointer to a structure with transfer data
 *
 *  Description:    Opens GMAC channels, sets up the interrupts and gets it
 *                  ready for listening.
 **********************************************************************************************************************/
void gmac_isr_handler (IRQn_Type *irq_num_ptr);
ER_RET gmac_open (const gmac_transfer_data *data)
{
    ER_RET ret_val = ER_OK;
#if HWISR_ENABLED == 0
    uint32_t irq_num = (GMAC_CHAN_1 == data->chan_num) ? RZN1_IRQ_SBD0 : RZN1_IRQ_SBD1;
    IRQn_Type MAX_IRQ = irq_num + 3;
    uint32_t int_priority = GMAC_DEFAULT_INT_PRIORITY;
#endif
    uint8_t conv_num;
    uint32_t i = 0;
    volatile uint32_t *switch_status = (volatile uint32_t *) (RZN1_SWITCH_CTRL_REG_BASE + SW_MODE_REG);

    /*Declare register pointers */
    volatile uint32_t *Operation_mode;
    volatile uint32_t *Receive_Descriptor_List_Address;
    volatile uint32_t *Transmit_Descriptor_List_Address;
    volatile uint32_t *MAC_Frame_Filter;
    volatile uint32_t *Interrupt_Enable;
    volatile uint32_t *MAC_Configuration;
    volatile uint32_t *Bus_Mode;
    volatile uint32_t *MAC_Address0_High;
    volatile uint32_t *MAC_Address0_Low;
    volatile uint32_t *Receive_Interrupt_Mask;
    volatile uint32_t *Transmit_Interrupt_Mask;

    /*Set up the descriptor*/
    rx_desc_top1 = rx_desc1;
    tx_desc_top1 = tx_desc1;
    set_receive_desc();

    /*Find the RGMII/MII converter used for PHY*/
    switch (data->port)
    {
        case (PORT1):
            conv_num = 0;
        break;
        case (PORT2):
            conv_num = 1;
        break;
        case (PORT3):
            conv_num = 2;
        break;
        case (PORT4):
            conv_num = 3;
        break;
        case (PORT5):
            conv_num = 4;
        break;
        default:
            return ER_PARAM;
    }

    if (conv_num < 3)
    {
        if (((phy_reg_read(data->port, 17, 0) & 0x0400) >> 10)) /*Check if the link is up on the port*/
        {
            port_link_state[conv_num] = LINK_UP;
        }
        else
        {
            ret_val = ER_SYS;
        }
        phy_write(data->port, 4, 0x1E1); /*Enable advertisement for all speeds */
        phy_write(data->port, 9, 0x0300);
    }
    else
    {
        if (((phy_read(data->port, 1) & 0x04) >> 2)) /*Check if the link is up on the port*/
        {
            port_link_state[conv_num] = LINK_UP;
        }
        else
        {
            ret_val = ER_SYS;
        }
        phy_write(data->port, 4, 0x1E1); /*Enable advertisement for all speeds */
    }

    if (ER_OK == ret_val)
    {
        if ((((( *switch_status) & 0x1F) < 8) || ((( *switch_status) & 0x1F) > 11)))
        {
            ret_val = switch_open(data->port);
        }

        if (ER_OK == ret_val)
        {
            /*Obtain the addresses from registers according to a channel*/
            if (GMAC_CHAN_1 == data->chan_num)
            {
                Operation_mode = (uint32_t *) &BaseAddress1->Operation_Mode.LONG;
                Receive_Descriptor_List_Address = (uint32_t *) &BaseAddress1->Receive_Descriptor_List_Address.LONG;
                Transmit_Descriptor_List_Address = (uint32_t *) &BaseAddress1->Transmit_Descriptor_List_Address.LONG;
                MAC_Frame_Filter = (uint32_t *) &BaseAddress1->MAC_Frame_Filter.LONG;
                Interrupt_Enable = (uint32_t *) &BaseAddress1->Interrupt_Enable.LONG;
                MAC_Configuration = (uint32_t *) &BaseAddress1->MAC_Configuration.LONG;
                MAC_Address0_High = (uint32_t *) &BaseAddress1->MAC_Address0_High.LONG;
                MAC_Address0_Low = (uint32_t *) &BaseAddress1->MAC_Address0_Low.LONG;
                Bus_Mode = (uint32_t *) &BaseAddress1->Bus_Mode.LONG;
                Receive_Interrupt_Mask = (uint32_t *) &BaseAddress1->MMC_Receive_Interrupt_Mask.LONG;
                Transmit_Interrupt_Mask = (uint32_t *) &BaseAddress1->MMC_Transmit_Interrupt_Mask.LONG;
            }
            else
            {
                Operation_mode = (uint32_t *) &BaseAddress2->Operation_Mode.LONG;
                Receive_Descriptor_List_Address = (uint32_t *) &BaseAddress2->Receive_Descriptor_List_Address.LONG;
                Transmit_Descriptor_List_Address = (uint32_t *) &BaseAddress2->Transmit_Descriptor_List_Address.LONG;
                MAC_Frame_Filter = (uint32_t *) &BaseAddress2->MAC_Frame_Filter.LONG;
                Interrupt_Enable = (uint32_t *) &BaseAddress2->Interrupt_Enable.LONG;
                MAC_Configuration = (uint32_t *) &BaseAddress2->MAC_Configuration.LONG;
                MAC_Address0_High = (uint32_t *) &BaseAddress2->MAC_Address0_High.LONG;
                MAC_Address0_Low = (uint32_t *) &BaseAddress2->MAC_Address0_Low.LONG;
                Bus_Mode = (uint32_t *) &BaseAddress2->Bus_Mode.LONG;
                Receive_Interrupt_Mask = (uint32_t *) &BaseAddress2->MMC_Receive_Interrupt_Mask.LONG;
                Transmit_Interrupt_Mask = (uint32_t *) &BaseAddress2->MMC_Transmit_Interrupt_Mask.LONG;
            }
            
            /*Set up transmit data pointers and null them*/
            receive_buf[data->chan_num] = data->receive_buf.payload;
            protocol[data->chan_num] = data->receive_buf.type;
            src_mac[data->chan_num] = data->receive_buf.src_mac;
            dst_mac[data->chan_num] = data->receive_buf.dst_mac;
            length[data->chan_num] = data->payload_length;

            *transmit_buf[data->chan_num] = 0;
            *length[data->chan_num] = 0;
            *receive_buf[data->chan_num] = 0;
            *protocol[data->chan_num] = 0;
            *src_mac[data->chan_num] = 0;
            *dst_mac[data->chan_num] = 0;

            ( *Bus_Mode) |= 0x00000001; /* Reset PHY*/
            while ((i++) < TIMEOUT) /* Wait reset*/
            {
                if ((( *Bus_Mode) & 0x00000001) == 0)
                {
                    break;
                }
            }
            /*Set up MAC address for filtering for both GMAC channels*/
            *MAC_Address0_High = (uint16_t)(((MY_MAC_ADDR_LSW & 0xFF) << 8) | ((MY_MAC_ADDR_LSW & 0xFF00) >> 8));
            *MAC_Address0_Low = change_long_endian(
                    (uint32_t)((MY_MAC_ADDR_MSW & 0xFFFF) << 16) | ((MY_MAC_ADDR_LSW >> 16) & 0xFFFF));

            *Receive_Descriptor_List_Address = (uint32_t) rx_desc_top1; /* Rx buffer address*/
            *Transmit_Descriptor_List_Address = (uint32_t) tx_desc_top1; /*Tx buffer address*/
            *MAC_Frame_Filter = (1 << 31) | /* Receive all frames*/
            (1 << 0); /* Promiscuous mode*/

            ret_val = reset_config(data->port, conv_num);

            if (ER_OK == ret_val)
            {
                *Interrupt_Enable = 
            ( ~((1 << 10)| /* Disable Early Transmit Interrupt*/
                (1 << 15) | /* Disable Abnormal Interrupt*/ // $REA Only for debugging
                (1 << 9) | /* Disable Receive Watchdog Timeout*/
                (1 << 8) | /* Disable Receive Stopped*/
                (1 << 3) | /* Disable Transmit Jabber Timeout*/
                (1 << 2) | /* Disable Transmit Buffer Unavailable*/
                (1 << 1))) /* Disable Transmit Stopped Unavailable*/
                & 0x1FFFF;
                *Operation_mode = (1 << 25) | /* Receive Store and Forward*/
                (0 << 3) | /* Start Receive*/
                (1 << 1); /* Receive Threshold Control 00:64 01:32 10:96 11:128 */
                ( *MAC_Configuration) |= (1u << 2); /* Receiver Enable*/
                
                *Receive_Interrupt_Mask = 0xffffffff; // $REA Only for debugging
                *Transmit_Interrupt_Mask = 0xffffffff;  // $REA Only for debugging

                /*Interrupt Control */
                /*Register PHY interrupts*/
                phy_interrupt_enable(data->port, phy_gpio_int[conv_num], (void *) phy_irq_handler);
#if HWISR_ENABLED == 0
                /*Register and enable interrupt */
                for (; irq_num < MAX_IRQ; irq_num++)
                {
                    /* Register interrupts */
                    if (R_BSP_InterruptRegisterCallback((IRQn_Type) irq_num, (bsp_int_cb_t) &gmac_isr_handler)
                            == MCU_INT_SUCCESS)
                    {
                        ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
                        if (MCU_INT_SUCCESS != ret_val)
                        {
                            ret_val = ER_SYS;
                        }
                        else
                        {
                            ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);
                        }
                    }
                    else
                    {
                        ret_val = ER_SYS;
                    }
                }
#endif
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function gmac_open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       gmac_close
 *
 *  Return value:   Error value
 *
 *  Parameters:     chan_num - GMAC channel
 *                  port - PHY address
 *
 *  Description:    Closes the channel, disables interrupts and resets the
 *                  configurations.
 **********************************************************************************************************************/
ER_RET gmac_close (uint8_t chan_num, uint8_t port)
{
    ER_RET ret_val = ER_OK;
    uint32_t irq_num = (GMAC_CHAN_1 == chan_num) ? RZN1_IRQ_SBD0 : RZN1_IRQ_SBD1;
    IRQn_Type MAX_IRQ = irq_num + 3;
    uint8_t conv_num;
    volatile uint32_t *switch_status = (volatile uint32_t *) (RZN1_SWITCH_CTRL_REG_BASE + SW_MODE_REG);

    /*Declare register pointers */
    volatile uint32_t *Operation_mode;
    volatile uint32_t *Interrupt_Mask;
    volatile uint32_t *Interrupt_Enable;
    volatile uint32_t *MAC_Configuration;
    volatile uint32_t *Bus_Mode;

    /*Find the RGMII/MII converter used for PHY*/
    switch (port)
    {
        case (PORT1):
            conv_num = 0;
        break;
        case (PORT2):
            conv_num = 1;
        break;
        case (PORT3):
            conv_num = 2;
        break;
        case (PORT4):
            conv_num = 3;
        break;
        case (PORT5):
            conv_num = 4;
        break;
        default:
            return ER_PARAM;
    }

    port_link_state[conv_num] = LINK_DOWN;
    /*Disable PHY interrupts*/
    phy_interrupt_disable(port, phy_gpio_int[conv_num]);

    /*Obtain the addresses from registers according to a channel*/
    if (GMAC_CHAN_1 == chan_num)
    {
        Operation_mode = (uint32_t *) &BaseAddress1->Operation_Mode.LONG;
        Interrupt_Mask = (uint32_t *) &BaseAddress1->Interrupt_Mask.LONG;
        Interrupt_Enable = (uint32_t *) &BaseAddress1->Interrupt_Enable.LONG;
        MAC_Configuration = (uint32_t *) &BaseAddress1->MAC_Configuration.LONG;
        Bus_Mode = (uint32_t *) &BaseAddress1->Bus_Mode.LONG;
    }
    else
    {
        Operation_mode = (uint32_t *) &BaseAddress2->Operation_Mode.LONG;
        Interrupt_Mask = (uint32_t *) &BaseAddress2->Interrupt_Mask.LONG;
        Interrupt_Enable = (uint32_t *) &BaseAddress2->Interrupt_Enable.LONG;
        MAC_Configuration = (uint32_t *) &BaseAddress2->MAC_Configuration.LONG;
        Bus_Mode = (uint32_t *) &BaseAddress2->Bus_Mode.LONG;
    }
    
    /*Disable GMAC interrupts*/
    for (; ((irq_num < MAX_IRQ) && (ER_OK == ret_val)); irq_num++)
    {
        ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE,
        FIT_NO_PTR);
    }

    /*Set everything to initial conditions*/
    if (ER_OK == ret_val)
    {
        if ((((( *switch_status) & 0x1F) < 8) || ((( *switch_status) & 0x1F) > 11)))
        {
            ret_val = switch_close(port);
        }

        if (ER_OK == ret_val)
        {
            /*Set initial conditions */
            *transmit_buf[chan_num] = 0;
            *length[chan_num] = 0;
            *receive_buf[chan_num] = 0;
            *protocol[chan_num] = 0;
            *src_mac[chan_num] = 0;
            *dst_mac[chan_num] = 0;

            ( *Bus_Mode) |= 0x00000001; /* Reset PHY*/
            while (1) /* Wait reset*/
            {
                if ((( *Bus_Mode) & 0x00000001) == 0)
                {
                    break;
                }
            }

            *Operation_mode = (1u << 20); /* Flush transmit FIFO */
            while (1) /* Wait reset*/
            {
                if ((( *Operation_mode) & (1u << 20)) == 0)
                {
                    break;
                }
            }

            /* Mask interrupts */
            *Interrupt_Mask = 0x0608;
            *Operation_mode = 0;
            *MAC_Configuration = 0; /* Set phy speed and duplex*/
            *Interrupt_Enable = 0; /* Interrupt enable*/
        }
    }
    else
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function gmac_close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       gmac_write
 *
 *  Return value:   Error value
 *
 *  Parameters:     chan_num - GMAC channel
 *                  eth_frame_info - structure with stored information
 *                                   necessary for Ethernet frame and payload
 *  Description:    Sends out the data.
 *
 **********************************************************************************************************************/
ER_RET gmac_write (uint8_t chan_num, uint8_t port, const gmac_eth_frame *eth_frame_info)
{
    ER_RET ret_val = ER_OK;
    uint8_t conv_num;

    /*Declare register pointers */
    volatile uint32_t *Operation_mode;
    volatile uint32_t *Transmit_Poll_Demand;
    volatile uint32_t *Status;
    volatile uint32_t *MAC_Configuration;
    volatile uint32_t *Debug;

    switch (port)
    {
        case (PORT1):
            conv_num = 0;
        break;
        case (PORT2):
            conv_num = 1;
        break;
        case (PORT3):
            conv_num = 2;
        break;
        case (PORT4):
            conv_num = 3;
        break;
        case (PORT5):
            conv_num = 4;
        break;
        default:
            return ER_PARAM;
    }

    if ((chan_num > GMAC_CHAN_2) || (LINK_DOWN == port_link_state[conv_num]))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /*Obtain the addresses from registers according to a channel*/
        if (GMAC_CHAN_1 == chan_num)
        {
            Operation_mode = (uint32_t *) &BaseAddress1->Operation_Mode.LONG;
            Transmit_Poll_Demand = (uint32_t *) &BaseAddress1->Transmit_Poll_Demand.LONG;
            Status = (uint32_t *) &BaseAddress1->Status.LONG;
            MAC_Configuration = (uint32_t *) &BaseAddress1->MAC_Configuration.LONG;
            Debug = (uint32_t *) &BaseAddress1->Debug.LONG;
        }
        else
        {
            Operation_mode = (uint32_t *) &BaseAddress2->Operation_Mode.LONG;
            Transmit_Poll_Demand = (uint32_t *) &BaseAddress2->Transmit_Poll_Demand.LONG;
            Status = (uint32_t *) &BaseAddress2->Status.LONG;
            MAC_Configuration = (uint32_t *) &BaseAddress2->MAC_Configuration.LONG;
            Debug = (uint32_t *) &BaseAddress2->Debug.LONG;
        }
        /*Set up Ethernet header*/
        *(eth_frame) = change_long_endian(eth_frame_info->dst_mac_msw);
        *(eth_frame + 1) = change_long_endian(eth_frame_info->dst_mac_lsw);
        *(eth_frame + 2) = change_long_endian((uint32_t)(MY_MAC_ADDR_MSW << 16) | (MY_MAC_ADDR_LSW >> 16));
        *(eth_frame + 3) = change_long_endian((uint32_t)((MY_MAC_ADDR_LSW & 0xFFFF) << 16) | (eth_frame_info->type));

        /* Check Tx complete */
        while (1)
            if ((( *Debug) & (1u << 16)) == 0)
            {
                break;
            }
        ( *Operation_mode) &= ( ~(1u << 13)); /*Disable transmit*/
        ( *MAC_Configuration) &= ( ~(1u << 3)); /*Disable transmit*/
        ( *Operation_mode) |= (1u << 20); /* Flush transmit FIFO */
        while (1) /* Wait till flush is complete*/
        {
            if ((( *Operation_mode) & (1u << 20)) == 0)
            {
                break;
            }
        }

        /*Store all the information to the Tx descriptor*/
        set_tx_desc((uint32_t) eth_frame, (uint32_t) eth_frame_info->payload, eth_frame_info->size);

        /*Check if OWN bit in Tx descriptor is down and causing TU flag in status register to go high*/
        if ((( *Status) & (1u << 2)) == 1)
        {
            ( *Status) |= (1u << 15); /*Clear the flag and restart sending operation*/
            tx_desc1[0].des0 |= 0x80000000;
            *Transmit_Poll_Demand = 0;

        }
        else
        {
            /* Send Ethernet packets */
            ( *Operation_mode) |= ((1u << 21) | (1u << 13)); /*Enable transmit operation*/
            ( *MAC_Configuration) |= (1u << 3);
        }

        while (1)
        {
            if ((tx_desc1[0].des0 & 0x80000000) == 0x00000000) /*Wait till DMA handles the descriptor*/
            {
                break;
            }
        }

    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function gmac_write
 **********************************************************************************************************************/

// $REA function modified (returns pointer to buffer and data size)
/***********************************************************************************************************************
 *
 *  Function:       gmac_read
 *
 *  Return value:   None
 *
 *  Parameters:     chan_num - GMAC channel
 *
 *  Description:    Reads out data from the receive buffer and takes care with
 *                  Ethernet header.
 **********************************************************************************************************************/
void gmac_read (uint8_t chan_num, uint8_t ** p_buf, uint16_t * p_len)
{
    uint32_t rx_desc_cnt1;

    /* Find used descriptor */
    for (rx_desc_cnt1 = 0; rx_desc_cnt1 < 64; rx_desc_cnt1++)
    {
        if ((rx_desc1[rx_desc_cnt1].des0 & 0x80008000) == 0x00000000)
        {
            break;
        }
    }

    if (rx_desc_cnt1 < 64)
    {

        *p_len = ((rx_desc1[rx_desc_cnt1].des0 & 0x3FFF0000) >> 16); /* Read fram length */

        *p_buf = (uint8_t *) rx_buf1[rx_desc_cnt1];
        
        rx_desc1[rx_desc_cnt1].des0 = 0x80000000;
    }
    else
    {
        BaseAddress2->Status.BIT.NIS = 1; /* Mask interrupt flag for receive interrupt if there are no more open descriptors*/
        BaseAddress1->Status.BIT.AIS = 1;
    }

}
/***********************************************************************************************************************
 End of function gmac_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       gmac_filtering_config
 *
 *  Return value:   Error value
 *
 *  Parameters:     chan_num - GMAC channel
 *                  filtering_options - pointer to a structure with all the
 *                                      information for the configuration
 *  Description:    Reads out data from the receive buffer and takes care with
 *                  Ethernet header.
 **********************************************************************************************************************/
ER_RET gmac_filtering_config (uint8_t chan_num, gmac_filter_config *filtering_options)
{
    ER_RET ret_val = ER_OK;
    volatile uint32_t *MAC_Frame_Filter;
    volatile uint32_t *MAC_Address_High;
    volatile uint32_t *MAC_Address_Low;
    uint32_t i;

    if (chan_num)
    {
        MAC_Frame_Filter = (uint32_t *) &BaseAddress2->MAC_Frame_Filter.LONG;
        MAC_Address_High = (uint32_t *) &BaseAddress2->MAC_Address1_High.LONG;
        MAC_Address_Low = (uint32_t *) &BaseAddress2->MAC_Address1_Low.LONG;
    }
    else
    {
        MAC_Frame_Filter = (uint32_t *) &BaseAddress1->MAC_Frame_Filter.LONG;
        MAC_Address_High = (uint32_t *) &BaseAddress1->MAC_Address1_High.LONG;
        MAC_Address_Low = (uint32_t *) &BaseAddress1->MAC_Address1_Low.LONG;
    }

    /*Store data from the options structure to SFR */
    *MAC_Frame_Filter = ((filtering_options->receive_all << 31) | (filtering_options->sa_filter << 9)
            | (filtering_options->sa_inverse_filter << 8) | (filtering_options->disable_broadcast << 5)
            | (filtering_options->da_inverse_filter << 3) | filtering_options->promiscuous_mode);

    if (filtering_options->number_of_filtered_addr > 0)
    {
        for (i = 0; i < filtering_options->number_of_filtered_addr; i++)
        {
            if ((0 != filtering_options->lsw_mac_addr[i]) && (0 != filtering_options->msw_mac_addr[i])) /*Check if the MAC address is entered accordingly to the number_of_filtered_addr*/
            {
                /*Set up MAC address for filtering*/
                *MAC_Address_High = (1u << 31) | (filtering_options->mac_comparison_field[i] << 30)
                        | (uint16_t)(
                                ((filtering_options->lsw_mac_addr[i] & 0xFF) << 8)
                                        | ((filtering_options->lsw_mac_addr[i] & 0xFF00) >> 8));
                *MAC_Address_Low = change_long_endian(
                        (uint32_t)((filtering_options->msw_mac_addr[i] & 0xFFFF) << 16)
                                | ((filtering_options->lsw_mac_addr[i] >> 16) & 0xFFFF));

                /*Increment address for the next MAC addres register*/
                if (15 == i)
                {
                    MAC_Address_High = (uint32_t *) ((uint32_t) MAC_Address_High + 0x000007C0);
                    MAC_Address_Low = (uint32_t *) ((uint32_t) MAC_Address_Low + 0x000007C0);
                }
                else
                {
                    MAC_Address_High = (uint32_t *) ((uint32_t) MAC_Address_High + 0x8);
                    MAC_Address_Low = (uint32_t *) ((uint32_t) MAC_Address_Low + 0x8);
                }
            }
            else
            {
                ret_val = ER_PARAM;
                break;
            }
        }
    }

    /*Clear the rest of the addresses*/
    for (i = filtering_options->number_of_filtered_addr; i < 17; i++)
    {
        *MAC_Address_High = 0x0000FFFF;
        *MAC_Address_Low = 0xFFFFFFFF;
        if (15 == i)
        {
            MAC_Address_High = (uint32_t *) ((uint32_t) MAC_Address_High + 0x000007C0);
            MAC_Address_Low = (uint32_t *) ((uint32_t) MAC_Address_Low + 0x000007C0);
        }
        else
        {
            MAC_Address_High = (uint32_t *) ((uint32_t) MAC_Address_High + 0x8);
            MAC_Address_Low = (uint32_t *) ((uint32_t) MAC_Address_Low + 0x8);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function gmac_filtering_config
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       gmac_set_speed
 *
 *  Return value:   Error value
 *
 *  Parameters:     chan_num - GMAC channel
 *                  mode - speed of operation
 *                  port - PHY address
 *  Description:    Controls the speed for PHY, RGMII/GMII converter and GMAC.
 *
 **********************************************************************************************************************/
ER_RET gmac_set_speed (uint8_t chan_num, uint8_t port, gmac_operation_mode_t mode)
{
    ER_RET ret_val = ER_OK;
    const uint8_t channel = chan_num;
    uint8_t conv_mode = 0;
    uint8_t conv = 0;
    volatile uint32_t *ctrl;
    volatile uint32_t *switch_status = (volatile uint32_t *) (RZN1_SWITCH_CTRL_REG_BASE + SW_MODE_REG);
    uint8_t speed_mask = 0x3;

    switch (port)
    {
        case (PORT1):
            conv = 0;
        break;
        case (PORT2):
            conv = 1;
        break;
        case (PORT3):
            conv = 2;
        break;
        case (PORT4):
            conv = 3;
        break;
        case (PORT5):
            conv = 4;
        break;
        default:
            return ER_PARAM;
    }

    eht_protection_control(1);

    /*PORT4 and PORT5 cannot operate on 1000Mbps mode. PORT1 can only send and receive data through PORT1*/
    if (((GMAC_CHAN_1 == channel) && (PORT1 != port)) || ((GMAC_CHAN_2 == channel) && (PORT1 == port))
            || (((PORT4 == port) || (PORT5 == port)) && ((HD_1G == mode) || (FD_1G == mode)))
            || (LINK_DOWN == port_link_state[conv]))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        conv_mode = ( *((uint32_t *) (RZN1_SWITCH_CTRL_REG_BASE + CONCTRL(conv)))) & 0x0000000F; /*Obtain converter speed*/

        /*Obtain MAC configuration register address accordingly to a channel*/
        if (channel)
        {
            ctrl = (volatile uint32_t*) &BaseAddress2->MAC_Configuration;
        }
        else
        {
            ctrl = (volatile uint32_t*) &BaseAddress1->MAC_Configuration;
        }
        ( *ctrl) &= 0xFFFF37FF; /*Clear the bits that we want to change*/

        if ((((( *switch_status) & 0x1F) < 8) || ((( *switch_status) & 0x1F) > 11)) && (GMAC_CHAN_2 == channel))
        {
            ( *ctrl) |= ((01 << 14) & 0xC000);
            speed_mask = 0;
        }

        /*Set the speed*/
        switch (mode)
        {
            case (FD_1G):
                ( *ctrl) |= (((01 << 14) | /*Configure MAC address register, bits PS(b15), FES(b14) and DM(b11)*/
                (1 << 11)) & 0x0000C800);
                write_eth_reg(CONCTRL(conv), 0x10A, 0x11F); /*Change the converter speed*/
                phy_set_mode(port, FULL_DUPLEX_1G); /*Change PHY speed*/
            break;
            case (HD_1G):
                ( *ctrl) |= (((01 << 14) | (0 << 11)) & 0x0000C800);
                write_eth_reg(CONCTRL(conv), 0x00A, 0x11F);
                phy_set_mode(port, HALF_DUPLEX_1G);
            break;
            case (FD_100M):
                ( *ctrl) |= ((((11 & speed_mask) << 14) | (1 << 11)) & 0x0000C800);
                phy_set_mode(port, FULL_DUPLEX_100M);
                if (conv_mode) /*If converter is set on MII configuration it means that the PHY device cannot work on RGMII/GMII modes*/
                {
                    write_eth_reg((0x100 + (((conv)) * 4)), 0x109, 0x11F);
                }
            break;
            case (HD_100M):
                ( *ctrl) |= ((((11 & speed_mask) << 14) | (0 << 11)) & 0x0000C800);
                phy_set_mode(port, HALF_DUPLEX_100M);
                if (conv_mode)
                {
                    write_eth_reg((0x100 + (((conv)) * 4)), 0x009, 0x11F);
                }
            break;
            case (FD_10M):
                ( *ctrl) |= ((((10 & speed_mask) << 14) | (1 << 11)) & 0x0000C800);
                phy_set_mode(port, FULL_DUPLEX_10M);
                if (conv_mode)
                {
                    write_eth_reg((0x100 + (((conv)) * 4)), 0x108, 0x11F);
                }
            break;
            case (HD_10M):
                ( *ctrl) |= ((((10 & speed_mask) << 14) | (0 << 11)) & 0x0000C800);
                phy_set_mode(port, HALF_DUPLEX_10M);
                if (conv_mode)
                {
                    write_eth_reg((0x100 + (((conv)) * 4)), 0x008, 0x11F);
                }
            break;
            default:
            break;
        }
    }
    eht_protection_control(0);
    return ret_val;
}
/***********************************************************************************************************************
 End of function gmac_set_speed
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       set_receive_desc
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Sets up receive descriptor to a ring buffer.
 *
 **********************************************************************************************************************/
static void set_receive_desc ()
{
    uint16_t rx_desc_cnt1;

    for (rx_desc_cnt1 = 0; rx_desc_cnt1 < 64; rx_desc_cnt1++) /* Set Rx Descriptor x 16 ring*/
    {
        volatile struct MACDMA_desc* next_desc_top;

        if (63 == rx_desc_cnt1)
        {
            rx_desc1[rx_desc_cnt1].des1 = 0x00008800; /*Set buffer size and RER (receive end of ring) bits*/
            next_desc_top = rx_desc1;
        }
        else
        {
            rx_desc1[rx_desc_cnt1].des1 = 0x00004800; /*Set buffer size and RCH (second address chained) bits*/
            next_desc_top = &rx_desc1[rx_desc_cnt1 + 1];
        }
        rx_desc1[rx_desc_cnt1].des2 = (uint32_t) rx_buf1[rx_desc_cnt1]; /*Attach the address of receive buffer*/
        rx_desc1[rx_desc_cnt1].des3 = (uint32_t) next_desc_top; /*set the address of the next descriptor*/
        rx_desc1[rx_desc_cnt1].des0 = 0x80000000; /*Set OWN bit in desc0*/
    }
}
/***********************************************************************************************************************
 End of function set_receive_desc
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       set_tx_desc
 *
 *  Return value:   None
 *
 *  Parameters:     eth_frame - address of the variable storing Ethernet headder
 *                  payload - address of the variable storing the data to send
 *                  len - size of the data desired to send
 *  Description:    Sets up transmit descriptor.
 *
 **********************************************************************************************************************/
static void set_tx_desc (uint32_t eth_frame, uint32_t payload, uint16_t len)
{

    /* Set up destination MAC address */
    tx_desc1[0].des0 = 0xB0200000; /*Set OWN bit, FS(first segment), LS(last segment) and TER(transmit end of ring)*/
    tx_desc1[0].des1 = (uint32_t)(len << 16) | ETH_FRAME_LENGTH; /*Set length of the first buffer to send (Ethernet header) and second (payload)*/
    tx_desc1[0].des2 = (uint32_t)(eth_frame + 2); /*attach the address of Ethernet header variable (has to be moved by 2 because it is aligned in 32bit memory*/
    tx_desc1[0].des3 = (uint32_t) payload; /*Attach payload address*/
}
/***********************************************************************************************************************
 End of function set_tx_desc
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       change_long_endian
 *
 *  Return value:   None
 *
 *  Parameters:     arg - variable
 *
 *  Description:    Changes endian of 32bit variable
 *
 **********************************************************************************************************************/
static uint32_t change_long_endian (uint32_t arg)
{
    uint32_t temp;
    temp = arg ^ (((arg) >> 16) | (arg << 16)); /* XOR MSW with LSW and LSW with MSW and store it in MSW and LSW respectively */
    temp &= 0xff00ffff; /* Mask bits 16:23 */
    arg = ((arg) >> 8) | (arg << 24); /*Move bits 0:3 of the initial variable to the most significant 4 bits (27:31)*/
    arg = arg ^ ((temp) >> 8); /* XOR shifted variable to the modified temporary variable to obtain reversed variable */
    return arg;
}
/***********************************************************************************************************************
 End of function change_long_endian
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       reset_config
 *
 *  Return value:   None
 *
 *  Parameters:     phy_addr - PHY address
 *                  conv_num - converter used for that PHY
 *
 *  Description:    Reads out the new status of the operation and changes
 *                  settings for GMAC and RGMII/GMII converter accordingly.
 **********************************************************************************************************************/
static ER_RET reset_config (uint8_t phy_addr, uint8_t conv_num)
{
    ER_RET ret_val = ER_OK;
    uint8_t status;
    volatile uint32_t *ctrl;
    uint16_t conv_ctrl = CONCTRL(conv_num);
    volatile uint32_t *switch_status = (volatile uint32_t *) (RZN1_SWITCH_CTRL_REG_BASE + SW_MODE_REG);
    uint8_t speed_mask = 0x3;

    if (PORT1 == phy_addr)
    {
        ctrl = (volatile uint32_t *) &BaseAddress1->MAC_Configuration.LONG;
        status = (uint8_t)((phy_reg_read(phy_addr, 17, 0) >> 13) & 0x7); /*Obtain the current status of phy link connection*/

    }
    else
    {
        if ((PORT4 != phy_addr) && (PORT5 != phy_addr))
        {
            status = (uint8_t)((phy_reg_read(phy_addr, 17, 0) >> 13) & 0x7);
        } /*Obtain the current status of phy link connection*/
        else
        {
            status = mii_status_check(phy_addr);
        }
        ctrl = (volatile uint32_t *) &BaseAddress2->MAC_Configuration.LONG;
    }
    ( *ctrl) &= 0xFFFF37FF;

    if ((((( *switch_status) & 0x1F) < 8) || ((( *switch_status) & 0x1F) > 11)) && (PORT1 != phy_addr))
    {
        ( *ctrl) |= ((01 << 14) & 0xC000);
        speed_mask = 0;
    }
    
    eht_protection_control(1);
    /*Change the configuration according to the current status*/
    switch (status)
    {
        case (5):
            if ((PORT4 != phy_addr) && (PORT5 != phy_addr))
            {
                ( *ctrl) |= (((01 << 14) | (1 << 11)) & 0x0000C800);
                write_eth_reg(conv_ctrl, 0x10A, 0x11F);
                ret_val = switch_speedconfig(phy_addr, FD_1G);
            }
        break;
        case (4):
            if ((PORT4 != phy_addr) && (PORT5 != phy_addr))
            {
                ( *ctrl) |= (((01 << 14) | (0 << 11)) & 0x0000C800);
                write_eth_reg(conv_ctrl, 0x00A, 0x11F);
                ret_val = switch_speedconfig(phy_addr, HD_1G);
            }
        break;
        case (3):
            ( *ctrl) |= ((((11 & speed_mask) << 14) | (1 << 11)) & 0x0000C800);
            ret_val = switch_speedconfig(phy_addr, FD_100M);
            if ((PORT4 != phy_addr) && (PORT5 != phy_addr))
            {
                write_eth_reg(conv_ctrl, 0x109, 0x11F);
            }
            else
            {
                write_eth_reg(conv_ctrl, 0x000, 0x11F);
            }
        break;
        case (2):
            ( *ctrl) |= ((((11 & speed_mask) << 14) | (0 << 11)) & 0x0000C800);
            ret_val = switch_speedconfig(phy_addr, HD_100M);
            if ((PORT4 != phy_addr) && (PORT5 != phy_addr))
            {
                write_eth_reg(conv_ctrl, 0x009, 0x11F);
            }
            else
            {
                write_eth_reg(conv_ctrl, 0x000, 0x11F);
            }
        break;
        case (1):
            ( *ctrl) |= ((((10 & speed_mask) << 14) | (1 << 11)) & 0x0000C800);
            ret_val = switch_speedconfig(phy_addr, FD_10M);
            if ((PORT4 != phy_addr) && (PORT5 != phy_addr))
            {
                write_eth_reg(conv_ctrl, 0x108, 0x11F);
            }
            else
            {
                write_eth_reg(conv_ctrl, 0x000, 0x11F);
            }
        break;
        case (0):
            ( *ctrl) |= ((((10 & speed_mask) << 14) | (0 << 11)) & 0x0000C800);
            ret_val = switch_speedconfig(phy_addr, HD_10M);
            if ((PORT4 != phy_addr) && (PORT5 != phy_addr))
            {
                write_eth_reg(conv_ctrl, 0x009, 0x11F);
            }
            else
            {
                write_eth_reg(conv_ctrl, 0x000, 0x11F);
            }
        break;
        default:
        break;
    }
    eht_protection_control(0);

    return ret_val;
}
/***********************************************************************************************************************
 End of function reset_config
 **********************************************************************************************************************/

static uint8_t mii_status_check (uint8_t phy_addr)
{
    uint8_t status = 0;

    switch (((phy_read(phy_addr, 0x1F) >> 2) & 0x7))
    {
        case (1):
            status = 0;
        break;
        case (2):
            status = 2;
        break;
        case (5):
            status = 1;
        break;
        case (6):
            status = 3;
        break;
        default:
        break;
    }
    return status;
}
/***********************************************************************************************************************
 End of function mii_status_check
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       phy_irq_handler
 *
 *  Return value:   None
 *
 *  Parameters:     pin - GPIO pin number on which interrupt has occurred
 *
 *  Description:    Handles the interrupts on PHY device.
 *
 **********************************************************************************************************************/
static void phy_irq_handler (gpio_port_pin_t pin)
{
    uint16_t status = 0;
    uint8_t port;
    uint8_t conv_num;

    /*Find the port on which interrupt occurred according to the GPIO pin*/
    switch (pin)
    {
        case (GPIO_PORT_2A_PIN_05):
            port = PORT4;
            conv_num = 3;
        break;
        case (GPIO_PORT_2A_PIN_06):
            port = PORT5;
            conv_num = 4;
        break;

        default:
            return;
    }

    if (conv_num > 2)
    {
        status = phy_read(port, 0x1B) & 0xFF;
    }
    else
    {
        status = phy_reg_read(port, 19, 0);
    }

    if (0 != status)
    {
        if (conv_num < 3)
        {
            if (((phy_reg_read(port, 17, 0) & 0x0400) >> 10)) /*Check if the link is up on the port*/
            {
                port_link_state[conv_num] = LINK_UP;
                (void) reset_config(port, conv_num);
            }
            else
            {
                port_link_state[conv_num] = LINK_DOWN;
            }
        }
        else
        {
            if (((phy_read(port, 1) & 0x04) >> 2)) /*Check if the link is up on the port*/
            {
                port_link_state[conv_num] = LINK_UP;
                (void) reset_config(port, conv_num);
            }
            else
            {
                port_link_state[conv_num] = LINK_DOWN;
            }
        }
    }
}
/***********************************************************************************************************************
 End of function phy_irq_handler
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       gmac_isr_handler
 *
 *  Return value:   None
 *
 *  Parameters:     irq_num_ptr - IRQ number of the interrupt
 *
 *  Description:    Handles the interrupts on GMAC device.
 *
 **********************************************************************************************************************/
#if HWISR_ENABLED == 0
static void gmac_isr_handler (IRQn_Type *irq_num_ptr) // $REA no longer used, HWISR is used instead
{
    IRQn_Type irq_num = *irq_num_ptr;

    if ((int) (irq_num - RZN1_IRQ_SBD1) >= 0)
    {
        if (BaseAddress2->Status.BIT.NIS)
        {
            if (BaseAddress2->Status.BIT.RI)
            {
                BaseAddress2->Status.BIT.NIS = 1; /*Clear receive interrupt and read the package*/
                
                if (receive_callback != NULL)
                {
                  receive_callback(GMAC_CHAN_2);
                }
            }
        }
        else
        {
            if (BaseAddress2->Status.BIT.RU) /* Poll the receive descriptor is Receive descriptor flag is high */
            {
                BaseAddress2->Receive_Poll_Demand.LONG = 0;
            }
            BaseAddress2->Status.BIT.AIS = 1;
        }
    }
    else
    {
        if (BaseAddress1->Status.BIT.NIS)
        {
            if (BaseAddress1->Status.BIT.RI)
            {
                BaseAddress1->Status.BIT.NIS = 1; /*Clear receive interrupt and read the package*/
                
                if (receive_callback != NULL)
                {
                  receive_callback(GMAC_CHAN_1);
                }
            }
        }
        else
        {
            if (BaseAddress1->Status.BIT.RU) /* Poll the receive descriptor is Receive descriptor flag is high */
            {
                BaseAddress1->Receive_Poll_Demand.LONG = 0;
            }
            BaseAddress1->Status.BIT.AIS = 1;
        }
    }
}

#else
void gmac_hwisr_handler (void) 
{
    
    if (BaseAddress2->Status.BIT.NIS)
    {
        if (BaseAddress2->Status.BIT.RI)
        {
            BaseAddress2->Status.BIT.NIS = 1; /*Clear receive interrupt and read the package*/
            
            if (receive_callback != NULL)
            {
              receive_callback(GMAC_CHAN_2);
            }
        }
    }
    else
    {
        if (BaseAddress2->Status.BIT.RU) /* Poll the receive descriptor is Receive descriptor flag is high */
        {
            BaseAddress2->Receive_Poll_Demand.LONG = 0;
        }
        BaseAddress2->Status.BIT.AIS = 1;
    }
    

    if (BaseAddress1->Status.BIT.NIS)
    {
        if (BaseAddress1->Status.BIT.RI)
        {
            BaseAddress1->Status.BIT.NIS = 1; /*Clear receive interrupt and read the package*/
            
            if (receive_callback != NULL)
            {
              receive_callback(GMAC_CHAN_1);
            }
        }
    }
    else
    {
        if (BaseAddress1->Status.BIT.RU) /* Poll the receive descriptor is Receive descriptor flag is high */
        {
            BaseAddress1->Receive_Poll_Demand.LONG = 0;
        }
        BaseAddress1->Status.BIT.AIS = 1;
    }
   
}
#endif

/***********************************************************************************************************************
 *
 *  Function:       gmac_register_callback
 *
 *  Return value:   none
 *
 *  Parameters:     cb - packet ready callback
 *                  
 *  Description:    Registes callbacks to be called when a packet is received
 *
 *  $REA function added
 **********************************************************************************************************************/
void gmac_register_callback(gmac_callback cb)
{
  receive_callback = cb;
}
/***********************************************************************************************************************
 End of function gmac_isr_handler
 **********************************************************************************************************************/
