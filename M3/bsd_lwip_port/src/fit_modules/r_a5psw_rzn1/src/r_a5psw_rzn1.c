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
 * $Revision: 1344 $
 * $Date: 2019-03-07 15:21:15 +0000 (Thu, 07 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_a5psw_rzn1.c
 * Description  :  A5PSW driver functions
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
#include "r_phy_rzn1.h"
#include "r_a5psw_rzn1.h"
#include "r_gmac_rzn1.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/* Version Number of API. */
#define SWITCH_DRIVER_MAJOR_VERSION_NUMBER         (1)
#define SWITCH_DRIVER_MINOR_VERSION_NUMBER         (1)

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  External function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local (private) variables
 **********************************************************************************************************************/
static volatile A5PSW_Type *Switch_Control;

/***********************************************************************************************************************
 * Local (private) function declarations
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *
 *  Function:       switch_GetVersion
 *
 *  Return value:   Driver number
 *
 *  Parameters:     Pointer to buffer for version information
 *  Description:    Returns the ADC driver version number
 *
 **********************************************************************************************************************/
void switch_GetVersion (void *buf)
{
    ((uint8_t *) buf)[1] = (uint8_t)SWITCH_DRIVER_MAJOR_VERSION_NUMBER;
    ((uint8_t *) buf)[0] = (uint8_t)SWITCH_DRIVER_MINOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function switch_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       switch_init
 *
 *  Return value:   Error value
 *
 *  Parameters:     None
 *
 *  Description:    Initialises the switch
 *
 **********************************************************************************************************************/
void switch_init (void)
{
    volatile uint32_t *Authorization;

    Switch_Control = (volatile A5PSW_Type *) RZN1_SWITCH_BASE;

    R_SYSCTRL_EthReg(); /*Enable clock for protected Ethernet register*/
    R_SYSCTRL_Switch();

    eht_protection_control(1); /*Enable writing to protected Ethernet register */

    write_eth_reg(PHY_LINK, 0xF, 0xf); /*Change A5PSW link signal control to low active level*/
    write_eth_reg(SWCTRL_REG, 0x00, 0); /*Sets Switch speed register to 0 that we would be able to control speed only modifying COMMAND_CONFIG reg*/
    write_eth_reg(SWCTRL_REG, 0x30000, 0x30000); /*Enable switch for all ports*/
    write_eth_reg(SWDUPC_REG, 0xF, 0); /*Sets Switch to full duplex mode*/
    reset_rgmii_conv(); /*Restarts the converters */

    Switch_Control->LK_CTRL.LONG = 0; /*Disable Lookup*/
    Switch_Control->PORT_ENA.LONG = ENABLE_PORT(4); /*Port1 should always be enabled*/
    Switch_Control->BCAST_DEFAULT_MASK.BIT.BCASTDM = 0x1F;
    Switch_Control->UCAST_DEFAULT_MASK.BIT.UCASTDM = 0x1F;
    
    Authorization = (uint32_t *) ((uint32_t)( &Switch_Control->AUTH_PORT0.LONG));
    ( *Authorization) |= (1);

    for (uint8_t sw_port = 0; sw_port < 4; sw_port++)
    {
        Authorization = (uint32_t *) ((uint32_t)( &Switch_Control->AUTH_PORT0.LONG) + (0x4 * sw_port));
        ( *Authorization) &= ( ~1);
    }
    R_RIN_Reset();
    eht_protection_control(0);
}
/***********************************************************************************************************************
 End of function switch_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       switch_open
 *
 *  Return value:   Error value
 *
 *  Parameters:     port -  port number (PHY address)
 *
 *  Description:    Opens the switch port and gets it ready to pass through
 *                  the packages.
 **********************************************************************************************************************/
ER_RET switch_open (uint8_t port)
{
    ER_RET ret_val = ER_OK;
    uint32_t sw_port;
    volatile uint32_t *Authorization;
    volatile uint32_t *FRM_Length;
    volatile uint32_t *Command_Config;
    volatile uint32_t *Port_Enable;

    switch (port)
    {
        case (PORT1):
            sw_port = 4;
        break;
        case (PORT2):
            sw_port = 3;
        break;
        case (PORT3):
            sw_port = 2;
        break;
        case (PORT4):
            sw_port = 1;
        break;
        case (PORT5):
            sw_port = 0;
        break;
        default:
            ret_val = ER_PARAM;
        break;
    }

    if (ER_OK == ret_val)
    {
        Authorization = (uint32_t *) ((uint32_t)( &Switch_Control->AUTH_PORT0.LONG) + (0x4 * sw_port));
        FRM_Length = (uint32_t *) ((uint32_t)( &Switch_Control->FRM_LENGTH_P0.LONG) + (0x400 * sw_port));
        Command_Config = (uint32_t *) ((uint32_t)( &Switch_Control->COMMAND_CONFIG_P0.LONG) + (0x400 * sw_port));
        Port_Enable = (uint32_t *) ( &Switch_Control->PORT_ENA.LONG);

        ( *Authorization) |= 1;
        *FRM_Length = 9224;

        if ((PORT2 == port) || (PORT3 == port) || (PORT1 == port))
        {
            *Command_Config = EN_SPEED_1G;
        }
        else
        {
            *Command_Config = EN_SPEED_100M_10M;
        }
        ( *Port_Enable) |= ENABLE_PORT(sw_port);
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function switch_open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       switch_close
 *
 *  Return value:   Error value
 *
 *  Parameters:     port -  port number (PHY address)
 *
 *  Description:    Disables and closes the switch port
 *
 **********************************************************************************************************************/
ER_RET switch_close (uint8_t port)
{
    ER_RET ret_val = ER_OK;
    uint32_t sw_port;
    volatile uint32_t *Authorization;
    volatile uint32_t *FRM_Length;
    volatile uint32_t *Command_Config;
    volatile uint32_t* Port_Enable;

    switch (port)
    {
        case (PORT1):
            sw_port = 4;
        break;
        case (PORT2):
            sw_port = 3;
        break;
        case (PORT3):
            sw_port = 2;
        break;
        case (PORT4):
            sw_port = 1;
        break;
        case (PORT5):
            sw_port = 0;
        break;
        default:
            ret_val = ER_PARAM;
        break;
    }

    if (ER_OK == ret_val)
    {
        Authorization = (uint32_t *) ((uint32_t)( &Switch_Control->AUTH_PORT0.LONG) + (0x4 * sw_port));
        FRM_Length = (uint32_t *) ((uint32_t)( &Switch_Control->FRM_LENGTH_P0.LONG) + (0x400 * sw_port));
        Command_Config = (uint32_t *) ((uint32_t)( &Switch_Control->COMMAND_CONFIG_P0.LONG) + (0x400 * sw_port));
        Port_Enable = (uint32_t *) ( &Switch_Control->PORT_ENA.LONG);

        ( *Authorization) &= ( ~1);
        *FRM_Length = 0;
        *Port_Enable = (( *Port_Enable) & ( ~ENABLE_PORT(sw_port)));

        *Command_Config = DISABLE_SWITCH;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function switch_close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       switch_speedconfig
 *
 *  Return value:   Error value
 *
 *  Parameters:     port -  port number (PHY address)
 *                  speed - speed parameter
 *  Description:    Changes the operating speed of the switch
 *
 **********************************************************************************************************************/
ER_RET switch_speedconfig (uint8_t port, gmac_operation_mode_t speed)
{
    ER_RET ret_val = ER_OK;
    volatile uint32_t *Command_Config;
    uint32_t sw_port;

    switch (port)
    {
        case (PORT1):
            sw_port = 4;
        break;
        case (PORT2):
            sw_port = 3;
        break;
        case (PORT3):
            sw_port = 2;
        break;
        case (PORT4):
            sw_port = 1;
        break;
        case (PORT5):
            sw_port = 0;
        break;
        default:
            ret_val = ER_PARAM;
        break;
    }

    if (ER_OK == ret_val)
    {
        Command_Config = (uint32_t *) ((uint32_t)( &Switch_Control->COMMAND_CONFIG_P0.LONG) + (0x400 * sw_port));

        if ((PORT2 == port) || (PORT3 == port) || (PORT1 == port))
        {
            if ((FD_1G == speed) || (HD_1G == speed))
            {
                *Command_Config = EN_SPEED_1G;
            }
            else
            {
                *Command_Config = EN_SPEED_100M_10M;
            }
        }
        else
        {
            *Command_Config = EN_SPEED_100M_10M;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function switch_speedconfig
 **********************************************************************************************************************/
