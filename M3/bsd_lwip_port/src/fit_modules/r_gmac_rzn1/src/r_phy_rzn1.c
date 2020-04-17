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
 * FILE         :  r_phy_rzn1.c
 * Description  :  I2C driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_iomux_rzn1_if.h"
#include "iodefine.h"
#include "r_phy_rzn1.h"
#include "r_timer_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
// $REA defines added because of the change in the phy read and write mechanisms
#define MDIO_BUSY_TIMEOUT_MS     10             /**< 10 ms busy wait timeout */
#define MDIO_BUSY_BIT_MASK       1              /**< busy bit mask */
#define MDIO_STATUS_READERR_MASK 2              /**< read error mask */
#define MDIO_CMD_ADDR_MASK       0x1f           /**< address mask */
#define MDIO_CMD_ADDR_PHY_SHIFT  5              /**< PHY address shift */
#define MDIO_CMD_TRANINIT_READ   1              /**< transaction init read */
#define MDIO_CMD_TRANINIT_SHIFT  15             /**< transaction init shift */
#define MDIO_REG_MASK            0xffff         /**< 16-bit register mask */

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local (private) variables
 **********************************************************************************************************************/
// static volatile GMAC1_Type *BaseAddress = (volatile GMAC1_Type *) RZN1_GMAC1_BASE; // $REA No longer used
static volatile ETHACS_Type *EtherConfig = (volatile ETHACS_Type *) RZN1_SWITCH_CTRL_REG_BASE;

/***********************************************************************************************************************
 *  External function declarations
 **********************************************************************************************************************/
extern ER_RET r_gpio_iterruptenable (gpio_port_pin_t pin, gpio_int_en_t value); /* A maximum of 8 A-Port pins can be enabled for interrupts at a time */
extern ER_RET r_gpio_interruptmask (gpio_port_pin_t pin, gpio_int_mask_t value);
extern ER_RET r_gpio_interrupttriggertype (gpio_port_pin_t pin, gpio_int_trigger_type_t value);
extern ER_RET r_gpio_interrupttriggerpolarity (gpio_port_pin_t pin, gpio_int_polarity_t value);

/***********************************************************************************************************************
 * Local (private) function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       phy_read
 *
 *  Return value:   Read value
 *
 *  Parameters:     phyadr - PHY address
 *                  regadr - PHY register address
 *  Description:    Reads from specified PHY register
 *
 **********************************************************************************************************************/

uint16_t phy_read (uint8_t phyadr, uint8_t regadr)
{
  // $REA Original phy read mechanism doesn't work with N1L
/*
    uint32_t val_tmp;

    val_tmp = (phyadr << 11) | // Phy address
            (regadr << 6) | // Phy reg address
            (0x4 << 2) | // Speed
            (0 << 1) | // Read
            (1 << 0); // Busy

    BaseAddress->GMII_Address.LONG = val_tmp; // Read phy register

    while (1)
    { // Wait read complete
        if ( !(BaseAddress->GMII_Address.BIT.GB))
        {
            return BaseAddress->GMII_Data.LONG & 0xffff; // Return phy value (reg 5)
        }
    }
*/
  
    volatile uint32_t *p_reg_cmd;                 /* command register */
    volatile uint32_t *p_reg_data;                /* data register */
    volatile uint32_t *p_reg_status;              /* status register */

    /* assign register pointer */
    p_reg_cmd    = (volatile uint32_t *) &A5PSW->MDIO_COMMAND.LONG;
    p_reg_data   = (volatile uint32_t *) &A5PSW->MDIO_DATA.LONG;
    p_reg_status = (volatile uint32_t *) &A5PSW->MDIO_CFG_STATUS.LONG;

    /* initialize and execute read command */
    *p_reg_cmd = (regadr & MDIO_CMD_ADDR_MASK) |
               ((phyadr & MDIO_CMD_ADDR_MASK) << MDIO_CMD_ADDR_PHY_SHIFT);
    *p_reg_cmd |= MDIO_CMD_TRANINIT_READ << MDIO_CMD_TRANINIT_SHIFT;

    /* wait until MDIO is ready */
    while (1) 
    {
        if (!(*p_reg_status & MDIO_BUSY_BIT_MASK)) 
        {
            return *p_reg_data & MDIO_REG_MASK;
        }
    }     

}
/***********************************************************************************************************************
 End of function phy_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       phy_write
 *
 *  Return value:   None
 *
 *  Parameters:     phyadr - PHY address
 *                  regadr - PHY register address
 *                  data -  data to be written to the register
 *  Description:    Writes to specified PHY register
 *
 **********************************************************************************************************************/
void phy_write (uint8_t phyadr, uint8_t regadr, uint16_t data)
{
  // $REA Original phy write mechanism doesn't work with N1L
/*
    uint32_t val_tmp;

    val_tmp = (phyadr << 11) | // Phy address
            (regadr << 6) | // Phy reg address
            (0x4 << 2) | // Speed
            (1 << 1) | // Write
            (1 << 0); // Busy

    BaseAddress->GMII_Data.LONG = data;        // Set write value
    BaseAddress->GMII_Address.LONG = val_tmp; // Write phy register

    while (1)
    { // wait write complete
        if ( !(BaseAddress->GMII_Address.BIT.GB))
        {
            break;
        }
    }
*/ 
    volatile uint32_t *p_reg_cmd;                 /* command register */
    volatile uint32_t *p_reg_data;                /* data register */
    volatile uint32_t *p_reg_status;              /* status register */
    
    /* assign register pointer */
    p_reg_cmd    = (volatile uint32_t *) &A5PSW->MDIO_COMMAND.LONG;
    p_reg_data   = (volatile uint32_t *) &A5PSW->MDIO_DATA.LONG;
    p_reg_status = (volatile uint32_t *) &A5PSW->MDIO_CFG_STATUS.LONG;

    /* initialize and execute write command */
    *p_reg_cmd = (regadr & MDIO_CMD_ADDR_MASK) |
               ((phyadr & MDIO_CMD_ADDR_MASK) << MDIO_CMD_ADDR_PHY_SHIFT);
    *p_reg_data = data & MDIO_REG_MASK;

    /* wait until MDIO is ready */
    while (1) 
    {
        if (!(*p_reg_status & MDIO_BUSY_BIT_MASK)) 
        {
            break;
        }
    }     

}
/***********************************************************************************************************************
 End of function phy_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       phy_interrupt_enable
 *
 *  Return value:   None
 *
 *  Parameters:     port - PHY address
 *                  pin - pin number which is connected to PHY interrupt
 *                  callback -  callback function address
 *  Description:    Enables PHY interrupts
 *
 **********************************************************************************************************************/
void phy_interrupt_enable (uint8_t port, gpio_port_pin_t pin, void *callback)
{
    /*Enable phy interrupts */
    if ((PORT4 == port) || (PORT5 == port))
    {
        R_GPIO_PinOpen(pin);
        R_GPIO_RegInterruptCallBack((gpio_callback) callback);
        r_gpio_interrupttriggertype(pin, GPIO_INTTERRUPT_TRIGGER_LEVEL);
        r_gpio_interrupttriggerpolarity(pin, GPIO_INTTERRUPT_POLARITY_LOW);
        r_gpio_interruptmask(pin, GPIO_INTTERRUPT_MASK_DISABLED);
        r_gpio_iterruptenable(pin, GPIO_INTTERRUPT_ENABLED);

        phy_write(port, 0x1F, 0x0300);
        phy_write(port, 0x1B, 0x2D00);

    }
    else
    {
        R_GPIO_PinOpen(pin);
        R_GPIO_RegInterruptCallBack((gpio_callback) callback);
        r_gpio_interrupttriggertype(pin, GPIO_INTTERRUPT_TRIGGER_EDGE);
        r_gpio_interrupttriggerpolarity(pin, GPIO_INTTERRUPT_POLARITY_HIGH);
        r_gpio_interruptmask(pin, GPIO_INTTERRUPT_MASK_DISABLED);
        r_gpio_iterruptenable(pin, GPIO_INTTERRUPT_ENABLED);

        phy_reg_write(port, 18, 0x4185, 3);
        phy_reg_write(port, 18, 0x6400, 0);
    }
}
/***********************************************************************************************************************
 End of function phy_interrupt_enable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       phy_interrupt_disable
 *
 *  Return value:   None
 *
 *  Parameters:     port - PHY address
 *                  pin - pin number which is connected to PHY interrupt
 *
 *  Description:    Disables PHY interrupts
 *
 **********************************************************************************************************************/
void phy_interrupt_disable (uint8_t port, gpio_port_pin_t pin)
{
    /*Enable phy interrupts */
    r_gpio_interruptmask(pin, GPIO_INTTERRUPT_MASK_ENABLED);
    r_gpio_iterruptenable(pin, GPIO_INTTERRUPT_DISABLED);
    R_GPIO_PinClose(pin);
    if ((PORT4 == port) || (PORT5 == port))
    {
        phy_write(port, 27, 0x0000);
        phy_read(port, 0x1B); /* Clear the interrupts */
    }
    else
    {
        phy_reg_write(port, 18, 0x4105, 3);
        phy_reg_write(port, 18, 0x0000, 0);
    }
}
/***********************************************************************************************************************
 End of function phy_interrupt_disable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       phy_set_mode
 *
 *  Return value:   None
 *
 *  Parameters:     phyadr - PHY address
 *                  mode - speed mode
 *
 *  Description:    Configures PHY speed
 *
 **********************************************************************************************************************/
void phy_set_mode (uint8_t phyadr, uint16_t mode)
{

    switch (mode)
    {
        case (FULL_DUPLEX_1G):
            if ((PORT4 != phyadr) && (PORT5 != phyadr))
            {
                phy_reg_write(phyadr, 9, FULL_DUPLEX_1G, 0); /* 1000BASE-T FDX*/
                phy_reg_write(phyadr, 4, 0x0001, 0); /* Disable 10/100*/
            }
        break;
        case (HALF_DUPLEX_1G):
            if ((PORT4 != phyadr) && (PORT5 != phyadr))
            {
                phy_reg_write(phyadr, 9, HALF_DUPLEX_1G, 0); /* 1000BASE-T HDX*/
                phy_reg_write(phyadr, 4, 0x0001, 0); /* Disable 10/100*/
            }
        break;
        case (FULL_DUPLEX_100M):
            if ((PORT4 != phyadr) && (PORT5 != phyadr))
            {
                phy_reg_write(phyadr, 9, 0x0000, 0); /* Disable 1000*/
                phy_reg_write(phyadr, 4, FULL_DUPLEX_100M, 0); /* 100BASE-T HDX*/
            }
            else
            {
                phy_write(phyadr, 4, FULL_DUPLEX_100M); /* 100BASE-T HDX*/
            }
        break;
        case (HALF_DUPLEX_100M):
            if ((PORT4 != phyadr) && (PORT5 != phyadr))
            {
                phy_reg_write(phyadr, 9, 0x0000, 0); /* Disable 1000*/
                phy_reg_write(phyadr, 4, HALF_DUPLEX_100M, 0); /* 100BASE-T HDX*/
            }
            else
            {
                phy_write(phyadr, 4, HALF_DUPLEX_100M); /* 100BASE-T HDX*/
            }
        break;
        case (FULL_DUPLEX_10M):
            if ((PORT4 != phyadr) && (PORT5 != phyadr))
            {
                phy_reg_write(phyadr, 9, 0x0000, 0); /* Disable 1000*/
                phy_reg_write(phyadr, 4, FULL_DUPLEX_10M, 0); /* 10BASE-T HDX*/
            }
            else
            {
                phy_write(phyadr, 4, FULL_DUPLEX_10M); /* 10BASE-T HDX*/
            }
        break;
        case (HALF_DUPLEX_10M):
            if ((PORT4 != phyadr) && (PORT5 != phyadr))
            {
                phy_reg_write(phyadr, 9, 0x0000, 0); /* Disable 1000*/
                phy_reg_write(phyadr, 4, HALF_DUPLEX_10M, 0); /* 10BASE-T HDX*/
            }
            else
            {
                phy_write(phyadr, 4, HALF_DUPLEX_10M); /* 10BASE-T HDX*/
            }
        break;
        default:
        break;
    }

    /*Restart auto-negotiation and wait till PHY resets*/
    if ((PORT4 != phyadr) && (PORT5 != phyadr))
    {
        phy_reg_write(phyadr, 0, 0x1200, 0);
        while (( !(phy_reg_read(phyadr, 1, 0) & 0x00000020)) && ( !(phy_reg_read(phyadr, 17, 0) & 0x00000400)));
        Delay_usec(200000);

        phy_reg_write(phyadr, 4, 0x1E1, 0);
        phy_reg_write(phyadr, 9, 0x0300, 0);

    }
    else
    {
        phy_write(phyadr, 0, 0x1200);
        while ( !(phy_read(phyadr, 1) & 0x0000024));
        Delay_usec(200000);
        
        phy_write(phyadr, 4, 0x1E1);
    }
}
/***********************************************************************************************************************
 End of function phy_set_mode
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       reset_rgmii_conv
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Resets RGMII converters (EtherConfig register has to be
 *                  unlocked to use this function (eht_protection_control)
 **********************************************************************************************************************/
void reset_rgmii_conv (void)
{
    EtherConfig->CONVRST.BIT.PHYIF_RSTn = 0;
    Delay_usec(200);

    EtherConfig->CONVRST.BIT.PHYIF_RSTn = 0x1F;
}
/***********************************************************************************************************************
 End of function reset_rgmii_conv
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       write_eth_reg
 *
 *  Return value:   None
 *
 *  Parameters:     offset - register offset
 *                  val - value to be written to the register
 *                  mask -  mask for the register bits
 *  Description:    Writes into EtherConfig register (EtherConfig register has
 *                  to be unlocked to use this function (eht_protection_control)
 **********************************************************************************************************************/
void write_eth_reg (uint16_t offset, uint32_t val, uint32_t mask)
{
    volatile uint32_t *reg;
    uint32_t temp;
    reg = (uint32_t *) (RZN1_SWITCH_CTRL_REG_BASE + offset);

    if (0 == mask)
    {
        *reg = val;
    }
    else
    {
        temp = (( *reg) & ( ~mask)) | val;
        *reg = temp;
    }
}
/***********************************************************************************************************************
 End of function write_eth_reg
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       eht_protection_control
 *
 *  Return value:   None
 *
 *  Parameters:     control - 1 - unlocks, 0 - locks
 *
 *  Description:    Unlocks or locks EtherConfig register
 *
 **********************************************************************************************************************/
void eht_protection_control (bool control)
{
    if (1 == control)
    {
        /*Unlock protected register by writing a set of values defined in section 10.4.1 of Ethernet manual*/
        EtherConfig->PRCMD.LONG = 0x00A5;
        EtherConfig->PRCMD.BIT.PRCMD = 1;
        EtherConfig->PRCMD.LONG = 0xFFFE;
        EtherConfig->PRCMD.BIT.PRCMD = 1;
    }
    else
    {
        EtherConfig->PRCMD.BIT.PRCMD = 0; /*Lock it again */
    }
}
/***********************************************************************************************************************
 End of function eht_protection_control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       phy_reg_write
 *
 *  Return value:   None
 *
 *  Parameters:     phy_addr - PHY address
 *                  reg - register number
 *                  data -  data to be written to the register
 *                  page_num - page number
 *
 *  Description:    Writes into the PHY register when different page number is
 *                  required
 **********************************************************************************************************************/
void phy_reg_write (uint8_t phy_addr, uint8_t reg, uint16_t data, uint8_t page_num)
{
    phy_write(phy_addr, 22, page_num);
    phy_write(phy_addr, reg, data);
}
/***********************************************************************************************************************
 End of function phy_reg_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       phy_reg_read
 *
 *  Return value:   Read data
 *
 *  Parameters:     phy_addr - PHY address
 *                  reg - register number
 *                  page_num - page number
 *
 *  Description:    Read from the PHY register when different page number is
 *                  required
 **********************************************************************************************************************/
uint16_t phy_reg_read (uint8_t phy_addr, uint8_t reg, uint8_t page_num)
{
    phy_write(phy_addr, 22, page_num);

    return phy_read(phy_addr, reg);
}
/***********************************************************************************************************************
 End of function phy_reg_read
 **********************************************************************************************************************/
