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
 * $Revision: 1299 $
 * $Date: 2019-02-25 12:05:48 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :   RZ/N1 bare metal Drivers
 * FILE         :  pinmux.c
 * Description  :   I/O multiplexing driver for RZN1 MCUs
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
/*
 * (C) Copyright 2015 Renesas Electronics Europe Ltd
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */
/* #include <asm/io.h> */
/* #include <common.h> */
#include "platform.h"

#define GPIO_LVL1_CONFIG_B(x)       (0x40067000 + ((x) << 2))
#define GPIO_LVL2_CONFIG(x)         (0x51000000 + ((x) << 2))
#define GPIO_LVL1_STATUS_PROTECT    (0x40067000 + 0x400)
#define GPIO_LVL2_STATUS_PROTECT    (0x51000000 + 0x400)
#define GPIO_LVL2_GPIO_INT(x)       (0x51000480 + ((x) << 2))
#define WRITE_ACCESS_MASK           (0xfffffff8)
#define DISABLE_WRITE_ACCESS        (1)
#define PADS_FUNCTION_USE_L2_SEL    (15)
#define RZN1_L1_PADFUNC_MASK        (0xf)
#define RZN1_L2_PADFUNC_MASK        (0x3f)

/* PinMux */
#define RZN1_DRIVE_SET              (1u << 31)
#define RZN1_PULL_SET               (1 << 30)
// #define RZN1_DRIVE_4MA           (RZN1_DRIVE_SET | (0 << 10))
// #define RZN1_DRIVE_6MA           (RZN1_DRIVE_SET | (1 << 10))
// #define RZN1_DRIVE_8MA           (RZN1_DRIVE_SET | (2 << 10))
// #define RZN1_DRIVE_12MA          (RZN1_DRIVE_SET | (3 << 10))
#define RZN1_DRIVE_MASK             (3 << 10)
// #define RZN1_PULL_NONE           (RZN1_PULL_SET | (0 << 8))
// #define RZN1_PULL_UP             (RZN1_PULL_SET | (1 << 8))
// #define RZN1_PULL_DOWN           (RZN1_PULL_SET | (3 << 8))
#define RZN1_PULL_MASK              (3 << 8)

/* Basic read/write */
#define readl(pAddress)          (* (volatile unsigned int *) (pAddress))
#define writel(data, pAddress)    (* (volatile unsigned int *) (pAddress) = (data))

void rzn1_pinmux_set (uint32_t setting);
uint32_t rzn1_pinmux_get (uint8_t pin);
void rzn1_pinmux_gpio_register_interrupt (uint8_t port, uint8_t pin, uint8_t int_line);

static void pinmux_unprotect (uint32_t reg)
{
    /* Enable write access to port multiplex registers */
    /* write the address of the register to the register */
    writel(reg & WRITE_ACCESS_MASK, reg);
}
/***********************************************************************************************************************
 End of function pinmux_unprotect
 **********************************************************************************************************************/

static void pinmux_protect (uint32_t reg)
{
    /* Disable write access to port multiplex registers */
    /* write the address of the register to the register */
    uint32_t val = reg;
    val &= WRITE_ACCESS_MASK;
    val |= DISABLE_WRITE_ACCESS;
    writel(val, reg);
}
/***********************************************************************************************************************
 End of function pinmux_protect
 **********************************************************************************************************************/

static void set_lvl1_pinmux (uint8_t pin, uint32_t func, uint32_t attrib)
{
    uint32_t reg = readl(GPIO_LVL1_CONFIG_B(pin));

    /* Set pad function */
    reg &= ( ~RZN1_L1_PADFUNC_MASK);
    reg |= (func & RZN1_L1_PADFUNC_MASK);

    if (attrib & RZN1_DRIVE_SET)
    {
        reg &= ( ~RZN1_DRIVE_MASK);
        reg |= (attrib & RZN1_DRIVE_MASK);
    }

    if (attrib & RZN1_PULL_SET)
    {
        reg &= ( ~RZN1_PULL_MASK);
        reg |= (attrib & RZN1_PULL_MASK);
    }

    pinmux_unprotect(GPIO_LVL1_STATUS_PROTECT);
    writel(reg, GPIO_LVL1_CONFIG_B(pin));
    pinmux_protect(GPIO_LVL1_STATUS_PROTECT);
}
/***********************************************************************************************************************
 End of function set_lvl1_pinmux
 **********************************************************************************************************************/

static void rzn1_pinmux_mdio_select (uint8_t mdio, uint32_t func)
{
    pinmux_unprotect(GPIO_LVL2_STATUS_PROTECT);
    writel(func, GPIO_LVL2_STATUS_PROTECT + 4 + (mdio * 4));
    pinmux_protect(GPIO_LVL2_STATUS_PROTECT);
}
/***********************************************************************************************************************
 End of function rzn1_pinmux_mdio_select
 **********************************************************************************************************************/

void rzn1_pinmux_select (uint8_t pin, uint32_t func, uint32_t attrib)
{
    /* Special 'virtual' pins for the MDIO muxing */
    if ((pin >= RZN1_MDIO_BUS0) && (pin <= RZN1_MDIO_BUS1))
    {
        if ((func >= RZN1_FUNC_MDIO_MUX_HIGHZ) && (func <= RZN1_FUNC_MDIO_MUX_SWITCH))
        {
            pin -= RZN1_MDIO_BUS0;
            func -= RZN1_FUNC_MDIO_MUX_HIGHZ;
            rzn1_pinmux_mdio_select(pin, func);
        }
        return;
    }

    if (func >= RZN1_FUNC_LEVEL2_OFFSET)
    {
        func -= RZN1_FUNC_LEVEL2_OFFSET;

        /* Level 2 to High-Z just in case */
        pinmux_unprotect(GPIO_LVL2_STATUS_PROTECT);
        writel(0, GPIO_LVL2_CONFIG(pin));
        pinmux_protect(GPIO_LVL2_STATUS_PROTECT);

        /* Level 1 */
        set_lvl1_pinmux(pin, PADS_FUNCTION_USE_L2_SEL, attrib);

        /* Level 2 */
        pinmux_unprotect(GPIO_LVL2_STATUS_PROTECT);
        writel(func, GPIO_LVL2_CONFIG(pin));
        pinmux_protect(GPIO_LVL2_STATUS_PROTECT);
    }
    else
    {
        /* Level 1 */
        set_lvl1_pinmux(pin, func, attrib);
    }
}
/***********************************************************************************************************************
 End of function rzn1_pinmux_select
 **********************************************************************************************************************/

void rzn1_pinmux_set (uint32_t setting)
{
    uint8_t pin = setting & 0xff;
    uint32_t func = (setting >> RZN1_MUX_FUNC_BIT) & 0x7f;
    uint32_t attrib = 0;
    uint32_t tmp;

    if (setting & (1 << RZN1_MUX_HAS_DRIVE_BIT))
    {
        tmp = (setting >> RZN1_MUX_DRIVE_BIT) & 3;
        attrib |= (RZN1_DRIVE_SET | (tmp << 10));
    }

    if (setting & (1 << RZN1_MUX_HAS_PULL_BIT))
    {
        tmp = (setting >> RZN1_MUX_PULL_BIT) & 3;
        attrib |= (RZN1_PULL_SET | (tmp << 8));
    }

    rzn1_pinmux_select(pin, func, attrib);
}
/***********************************************************************************************************************
 End of function rzn1_pinmux_set
 **********************************************************************************************************************/

uint32_t rzn1_pinmux_get (uint8_t pin)
{
    /* Read level 1 */
    uint32_t reg = readl(GPIO_LVL1_CONFIG_B(pin));
    uint32_t drive = (reg & RZN1_DRIVE_MASK) >> 10;
    uint32_t pull = (reg & RZN1_PULL_MASK) >> 8;

    /* Extract Function */
    reg &= RZN1_L1_PADFUNC_MASK;
    if (PADS_FUNCTION_USE_L2_SEL == reg)
    {
        /* Level 2 */
        reg = readl(GPIO_LVL2_CONFIG(pin));
        reg += RZN1_FUNC_LEVEL2_OFFSET;
    }
    /* Repackage and return the data */
    return (pin | (reg << RZN1_MUX_FUNC_BIT) | (1 << RZN1_MUX_HAS_FUNC_BIT) | (drive << RZN1_MUX_DRIVE_BIT)
            | (1 << RZN1_MUX_HAS_DRIVE_BIT) | (pull << RZN1_MUX_PULL_BIT) | (1 << RZN1_MUX_HAS_PULL_BIT));
}
/***********************************************************************************************************************
 End of function rzn1_pinmux_get
 **********************************************************************************************************************/

void rzn1_pinmux_gpio_register_interrupt (uint8_t port, uint8_t pin, uint8_t int_line)
{
    writel((port << 5) | pin, GPIO_LVL2_GPIO_INT(int_line));
}
/***********************************************************************************************************************
 End of function rzn1_pinmux_gpio_register_interrupt
 **********************************************************************************************************************/

void rzn1_pinmux_gpio_disable_interrupt (uint8_t int_line)
{
    writel(0, GPIO_LVL2_GPIO_INT(int_line));
}
/***********************************************************************************************************************
 End of function rzn1_pinmux_gpio_disable_interrupt
 **********************************************************************************************************************/
