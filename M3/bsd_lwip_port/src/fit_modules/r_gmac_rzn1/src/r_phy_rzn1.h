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
 * $Revision: 1195 $
 * $Date: 2019-01-29 12:51:05 +0000 (Tue, 29 Jan 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_phy_rzn1.h
 * Description  :  PHY driver definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_PHY_RZN1_H__
#define R_PHY_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_gpio_rzn1_if.h"

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define FULL_DUPLEX_1G          (0x0200)
#define HALF_DUPLEX_1G          (0x0100)
#define FULL_DUPLEX_100M        (0x0101)
#define HALF_DUPLEX_100M        (0x0081)
#define FULL_DUPLEX_10M         (0x0061)
#define HALF_DUPLEX_10M         (0x0021)

/* Define PHY addresses*/
#define PORT1                   (0x08)
#define PORT2                   (0x01)
#define PORT3                   (0x0A)
#define PORT4                   (0x04)
#define PORT5                   (0x05)

/* RIN RGMII/RMII Converter regs */
#define CONCTRL(x)              (0x100 + ((x)) * 4) /* RGMII/RMII Converter */
#define PHY_LINK                (0x14)
#define PTP_MODE_REG            (0x0C)
#define SW_MODE_REG             (0x08)
#define SWCTRL_REG              (0x304)
#define SWDUPC_REG              (0x308)
#define CONVCTRL_10_MBPS        (0 << 0)
#define CONVCTRL_100_MBPS       (1 << 0)
#define CONVCTRL_1000_MBPS      (1 << 1)
#define CONVCTRL_MII            (0 << 2)
#define CONVCTRL_RMII           (1 << 2)
#define CONVCTRL_RGMII          (1 << 3)
#define CONVCTRL_REF_CLK_OUT    (1 << 4)
#define CONVCTRL_HALF_DUPLEX    (0 << 8)
#define CONVCTRL_FULL_DUPLEX    (1 << 8)
#define CONRST                  (0x114)        /* RGMII/RMII Converter RST */
#define PHYIF_RST(x)            (1 << (x))

/*Converter Operation Mode*/
#define RGMII_1G_MODE           (10)
#define RGMII_100M_MODE         (9)
#define RGMII_10M_MODE          (8)
#define MII_MODE                (0)

/*A5PSW Link Signal Control Active Level*/
#define SWLNK_LOW_ACTIVE        (0xf)
#define SWLNK_HIGH_ACTIVE       (0)

/*Clock source of PTP timer for GMAC1 and GMAC2*/
#define MGHz_25                 (0x4)
#define MGHz_50                 (0x3)
#define MGHz_125                (0x2)
#define RGMII_REFCLK            (0x1)
#define STOP                    (0)

#define CONV_MODE_MASK          (0x1F)
#define PTP_MODE_MASK           (0xF)
#define SWLINK_MODE_MASK        (0xF)
#define NO_MASK                 (0)

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/

uint16_t phy_read (uint8_t phyadr, uint8_t regadr);
void phy_write (uint8_t phyadr, uint8_t regadr, uint16_t data);
void phy_set_mode (uint8_t phyadr, uint16_t mode);
void phy_interrupt_enable (uint8_t port, gpio_port_pin_t pin, void *callback);
void phy_interrupt_disable (uint8_t port, gpio_port_pin_t pin);
void write_eth_reg (uint16_t offset, uint32_t val, uint32_t mask);
void eht_protection_control (bool control);
void reset_rgmii_conv (void);
void phy_reg_write (uint8_t phy_addr, uint8_t reg, uint16_t data, uint8_t page_num);
uint16_t phy_reg_read (uint8_t phy_addr, uint8_t reg, uint8_t page_num);

#endif /* R_PHY_RZN1_H__ */
