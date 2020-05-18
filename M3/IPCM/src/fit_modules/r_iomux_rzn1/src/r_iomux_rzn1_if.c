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
 * FILE         :  r_iomux_rzn1_if.c
 * Description  :   I/O multiplexing driver for RZN1 MCUs
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 11.09.2017 0.00    Pre-Release
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_iomux_rzn1_if.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Variables
 **********************************************************************************************************************/
extern uint32_t rzn1_pinmux_get (uint8_t pin);
extern void rzn1_pinmux_set (uint32_t setting);

/***********************************************************************************************************************
 *
 *  Function:       R_IOMUX_PinCtrl
 *
 *  Return value:   Error status
 *
 *  Parameters:     pin - Which pin to configure
 *                    cmd - The command to execute (Set/Get pin properties)
 *                    properties - The properties of the pin
 *                                (function, drive strength, pull level)
 *
 *  Description:    Configures the multiplexing of the pin
 *
 **********************************************************************************************************************/
ER_RET R_IOMUX_PinCtrl (uint8_t pin, iomux_cmd_t cmd, iomux_pin_properties_t *properties)
{
    ER_RET ret_val = ER_OK;
    uint32_t setting;

    /* parameter check */
    /* CHECK PIN!? */
    if ((NULL == properties))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        switch (cmd)
        {
            case IOMUX_CONTROL_GET_PIN_PROPERTIES:
                setting = rzn1_pinmux_get(pin);
                properties->function = (setting >> RZN1_MUX_FUNC_BIT) & 0x7f;
                properties->drive_strength = (setting >> RZN1_MUX_DRIVE_BIT) & 3;
                properties->pull_level = (setting >> RZN1_MUX_PULL_BIT) & 3;
            break;
            case IOMUX_CONTROL_SET_PIN_PROPERTIES:
                setting = pin;
                setting |= ((properties->function) << RZN1_MUX_FUNC_BIT);
                setting |= ((0x01) << RZN1_MUX_HAS_FUNC_BIT);
                setting |= ((0x01) << RZN1_MUX_HAS_DRIVE_BIT);
                setting |= ((properties->drive_strength) << RZN1_MUX_DRIVE_BIT);
                setting |= ((0x01) << RZN1_MUX_HAS_PULL_BIT);
                setting |= ((properties->pull_level) << RZN1_MUX_PULL_BIT);
                rzn1_pinmux_set(setting);
            break;
            default:
                ret_val = ER_PARAM;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_IOMUX_PinCtrl
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *
 *  Function:       R_IOMUX_PortCtrl
 *
 *  Return value:   Error status
 *
 *  Parameters:     port - apply command to all pins on the given port
 *                  port_mask  - indicates pins in use on this port
 *                  cmd - The command to execute (Set/Get pin properties)
 *                  properties - The properties of the pin
 *                                (function, drive strength, pull level)
 *
 *  Description:    Configures the multiplexing of the pin
 *
 **********************************************************************************************************************/
ER_RET R_IOMUX_PortCtrl (gpio_port_t port, uint32_t port_mask, iomux_cmd_t cmd, iomux_pin_properties_t *properties)
{
    ER_RET                  ret_val = ER_OK;
    uint8_t                 i;
    uint32_t                port_pin;
    uint32_t                 pin;
    iomux_pin_properties_t *properties_ptr;

    /* parameter check */
    if ((NULL == properties))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        for (i = 0, properties_ptr = properties; i < 32 ; i++)
        {
            if ( port_mask & (0x00000001 << i) )
            {
                port_pin = (uint32_t)port + i;
                pin = rzn1_gpio_linear_pin_map[RZN1_GPIO_PIN(port_pin)];

                ret_val = R_IOMUX_PinCtrl (pin, cmd, properties_ptr);
            }
            else
            {
                if (cmd == IOMUX_CONTROL_GET_PIN_PROPERTIES)
                {
                    /* pin not in use */
                    properties_ptr->function = 0;
                    properties_ptr->drive_strength = 0;
                    properties_ptr->pull_level = 0;
                }
            }
            if (cmd == IOMUX_CONTROL_GET_PIN_PROPERTIES)
            {
                properties_ptr++;
            }
        }
    }
    return ret_val;
}