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
 * $Revision: 1301 $
 * $Date: 2019-02-25 14:29:43 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_gpio_rzn1_if.c
 * Description  :  General Purpose Input/Output interface functions for RZN1 MCUs.
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>

#include "r_gpio_rzn1_if.h"
#include "r_gpio_rzn1.h"

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
static gpio_pin_states_t gpio_pin_state[sizeof(rzn1_gpio_linear_pin_map) / sizeof(uint8_t)];

/***********************************************************************************************************************
 * External variables declarations
 **********************************************************************************************************************/
extern gpio_port_pin_t gpio_interrupt_pins[GPIO_MAX_INTERRUPT] =
{ GPIO_NO_PIN };

/***********************************************************************************************************************
 * External function declarations
 **********************************************************************************************************************/
extern uint32_t rzn1_pinmux_get (uint8_t pin); // @suppress("Internal function declaration")
extern void rzn1_pinmux_gpio_register_interrupt (uint8_t port, uint8_t pin, uint8_t int_line); // @suppress("Internal function declaration")
extern void rzn1_pinmux_gpio_disable_interrupt (uint8_t int_line);

/***********************************************************************************************************************
 * Local (private) function declarations
 **********************************************************************************************************************/
ER_RET r_gpio_checkportpinmux (gpio_port_t port, uint32_t mask);
ER_RET r_gpio_checkporstate (gpio_port_t port, gpio_pin_states_t desired_state, uint32_t mask);
ER_RET r_gpio_iterruptenable (gpio_port_pin_t pin, gpio_int_en_t value); /* A maximum of 8 A-Port pins can be enabled for interrupts at a time */
ER_RET r_gpio_interruptmask (gpio_port_pin_t pin, gpio_int_mask_t value);
ER_RET r_gpio_interrupttriggertype (gpio_port_pin_t pin, gpio_int_trigger_type_t value);
ER_RET r_gpio_interrupttriggerpolarity (gpio_port_pin_t pin, gpio_int_polarity_t value);

/***********************************************************************************************************************
 * Function Name: R_GPIO_GetVersion
 * Description  : Returns the current version of this module.
 * Arguments    : buf - Pointer to buffer for version information
 * Return Value : Version of this module.
 **********************************************************************************************************************/
void R_GPIO_GetVersion (void *buf)
{
    /* These version macros are defined in r_gpio_rzn1_if.h. */
    ((uint8_t *) buf)[1] = (uint8_t)GPIO_RZN1_VERSION_MAJOR;
    ((uint8_t *) buf)[0] = (uint8_t)GPIO_RZN1_VERSION_MINOR;
}
/***********************************************************************************************************************
 End of function R_GPIO_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_Init
 * Description  : Initialises the GPIO Driver
 * Arguments    : None
 * Return Value : Error state
 **********************************************************************************************************************/
ER_RET R_GPIO_Init (void)
{
    ER_RET ret_val = ER_OK;
    uint8_t i;

    ret_val = gpio_init();

    if (ER_OK == ret_val)
    {
        /* Reset interrupt pins in case of warm reset */
        for (i = 0; i < GPIO_MAX_INTERRUPT; i++)
        {
            gpio_interrupt_pins[i] = GPIO_NO_PIN;
        }

        /* Reset pin states in case of warm reset */
        for (i = 0; i < (sizeof(rzn1_gpio_linear_pin_map) / sizeof(uint8_t)); i++)
        {
            gpio_pin_state[i] = GPIO_PIN_STATE_CLOSED;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_Uninitialise
 * Description  : Uninitialises the GPIO Driver
 * Arguments    : None
 * Return Value : Error state
 **********************************************************************************************************************/
ER_RET R_GPIO_Uninitialise (void)
{
    ER_RET ret_val = ER_OK;
    uint8_t i;

    ret_val = gpio_uninit();

    if (ER_OK == ret_val)
    {
        /* Reset interrupt pins in case of warm reset */
        for (i = 0; i < GPIO_MAX_INTERRUPT; i++)
        {
            gpio_interrupt_pins[i] = GPIO_NO_PIN;
        }

        /* Reset pin states in case of warm reset */
        for (i = 0; i < (sizeof(rzn1_gpio_linear_pin_map) / sizeof(uint8_t)); i++)
        {
            gpio_pin_state[i] = GPIO_PIN_STATE_CLOSED;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_Uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PortOpen
 * Description  : Enables pins of a port as GPIO pins
 * Arguments    : port -
 *                    Which port to write to.
 *                mask -
 *                    Mask to allow certain pins of the port to be set to GPIO. A pin will only change when the
 *                    corresponding mask bit is 1.
 * Return Value : Error state
 **********************************************************************************************************************/
ER_RET R_GPIO_PortOpen (gpio_port_t port, uint32_t mask)
{
    ER_RET ret_val = ER_OK;
    uint32_t i;

    /* parameter check */
    /* bit shift drive strength 10 times because located at bit 10 in register - discard less significant bits. Same explanation for pull level */
    if ((GPIO_MAX_PORT < port) || (GPIO_PORT_1A > port)
            || ((GPIO_PORT_INFO[RZN1_GPIO_PORT(port)].port_mask & mask) != mask))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check pins are closed, return error otherwise */
        if (ER_OK == (ret_val = r_gpio_checkporstate(port, GPIO_PIN_STATE_CLOSED, mask)))
        {
            /* Check all pins are multiplexed for GPIO */
            if (ER_OK == (ret_val = r_gpio_checkportpinmux(port, mask)))
            {
                gpio_portdirectionset(port, GPIO_DIRECTION_INPUT, mask); /* Set the pins to Input as an initial value*/

                /* Loop through pins, set states to open */
                for (i = RZN1_GPIO_PIN(port); (i < (RZN1_GPIO_PIN(port) + 32)) || (GPIO_MAX_PIN < i); i++)
                {
                    /* Wherever mask is high, set state to open */
                    if (mask & (0x01 << (i - RZN1_GPIO_PIN(port))))
                    {
                        gpio_pin_state[i] = GPIO_PIN_STATE_OPEN;
                    }
                }
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PortOpen
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PinOpen
 * Description  : Enables a pin as a GPIO pin
 * Arguments    : pin -
 *                    Which pin to set.
 * Return Value : Error state
 **********************************************************************************************************************/
ER_RET R_GPIO_PinOpen (gpio_port_pin_t pin)
{
    ER_RET ret_val = ER_OK;

    /* parameter check */
    if ((GPIO_MAX_PIN < pin) || (RZN1_GPIO_PORT(pin) > RZN1_GPIO_PORT(GPIO_MAX_PORT)) || (RZN1_GPIO_PORT(pin) < 0)
            || (0 == ((GPIO_PORT_INFO[RZN1_GPIO_PORT(pin)].port_mask) & (0x01 << (pin & 0xFF)))))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check state is closed */
        if (GPIO_PIN_STATE_CLOSED == gpio_pin_state[RZN1_GPIO_PIN(pin)])
        {
            /* Check Pin is multiplexed for GPIO */
            if (((rzn1_pinmux_get(rzn1_gpio_linear_pin_map[RZN1_GPIO_PIN(pin)]) >> RZN1_MUX_FUNC_BIT) & 0x7F)
                    == RZN1_FUNC_GPIO)
            {
                gpio_pindirectionset(pin, GPIO_DIRECTION_INPUT); /* Set input as an initial direction of the pin */

                /* Set state to open */
                gpio_pin_state[RZN1_GPIO_PIN(pin)] = GPIO_PIN_STATE_OPEN;
            }
            else
            {
                /* Pin in use for another function */
                ret_val = ER_BUSY;
            }
        }
        else
        {
            /* Pin is already open */
            ret_val = ER_INVAL;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PinOpen
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PortClose
 * Description  : Disables GPIO pins of a port
 * Arguments    : port -
 *                    Which port to close.
 *                mask -
 *                    Mask to allow certain pins of the port to be selected. A pin will only close when the
 *                    corresponding mask bit is 1.
 * Return Value : Error state
 **********************************************************************************************************************/
ER_RET R_GPIO_PortClose (gpio_port_t port, uint32_t mask)
{
    ER_RET ret_val = ER_OK;
    bool interrupt_registered = false;
    uint32_t i;
    uint8_t j;

    /* parameter check */
    if ((GPIO_MAX_PORT < port) || (GPIO_PORT_1A > port))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        gpio_portdirectionset(port, GPIO_DIRECTION_INPUT, mask); /* Set the pins to Input before closing the port*/

        /* Loop through pins, set states to closed */
        for (i = RZN1_GPIO_PIN(port); (i < (RZN1_GPIO_PIN(port) + 32)) || (GPIO_MAX_PIN < i); i++)
        {
            /* Disable interrupts on pin if enabled */
            for (j = 0; j < GPIO_MAX_INTERRUPT; j++) /* Check if an interrupt has been set */
            {
                if (i == gpio_interrupt_pins[j])
                {
                    gpio_interrupt_pins[j] = GPIO_NO_PIN; /* Free the IRQ for another pin to use */
                    interrupt_registered = true;
                    break;
                }
            }
            if (true == interrupt_registered)
            {
                /* Disable the interrupt */
                gpio_interruptenable((gpio_port_pin_t)(port + (i - RZN1_GPIO_PIN(port))), GPIO_INTTERRUPT_DISABLED);
            }

            /* Wherever mask is high, set state to closed */
            if (mask & (0x01 << (i - RZN1_GPIO_PIN(port))))
            {
                gpio_pin_state[i] = GPIO_PIN_STATE_CLOSED;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PortClose
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PinClose
 * Description  : Diables a GPIO pin
 * Arguments    : pin -
 *                    Which pin to disable.
 * Return Value : Error state
 **********************************************************************************************************************/
ER_RET R_GPIO_PinClose (gpio_port_pin_t pin)
{
    ER_RET ret_val = ER_OK;
    bool interrupt_registered = false;
    uint8_t i;

    /* parameter check */
    if ((GPIO_MAX_PIN < pin) || (RZN1_GPIO_PORT(pin) > RZN1_GPIO_PORT(GPIO_MAX_PORT)) || (RZN1_GPIO_PORT(pin) < 0)
            || (0 == ((GPIO_PORT_INFO[RZN1_GPIO_PORT(pin)].port_mask) & (0x01 << (pin & 0xFF)))))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        gpio_pindirectionset(pin, GPIO_DIRECTION_INPUT); /* Set input before closing the pin */

        /* Disable interrupts on pin if enabled */
        for (i = 0; i < GPIO_MAX_INTERRUPT; i++) /* Check if an interrupt has been set */
        {
            if (pin == gpio_interrupt_pins[i])
            {
                gpio_interrupt_pins[i] = GPIO_NO_PIN; /* Free the IRQ for another pin to use */
                interrupt_registered = true;
                break;
            }
        }
        if (true == interrupt_registered)
        {
            /* Disable the interrupt */
            gpio_interruptenable(pin, GPIO_INTTERRUPT_DISABLED);
        }

        /* Set state to closed */
        gpio_pin_state[RZN1_GPIO_PIN(pin)] = GPIO_PIN_STATE_CLOSED;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PinClose
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PortWrite
 * Description  : Writes the levels of all pins on a port.
 * Arguments    : port -
 *                    Which port to write to.
 *                value -
 *                    The value to write to the port. Each bit corresponds to a pin on the port (e.g. bit 0 of value
 *                    will be written to pin 0 on supplied port)
 *                mask -
 *                    Mask to allow certain pins of the port to be changed. A pin will only change value when the
 *                    corresponding mask bit is 1.
 * Return Value : Error state
 **********************************************************************************************************************/
ER_RET R_GPIO_PortWrite (gpio_port_t port, uint32_t value, uint32_t mask)
{
    ER_RET ret_val = ER_OK;
    uint32_t gpio_direction_state;
    uint32_t direction_check;

    if ((GPIO_MAX_PORT < port) || (GPIO_PORT_1A > port))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check pin states */
        if (ER_OK == (ret_val = r_gpio_checkporstate(port, GPIO_PIN_STATE_OPEN, mask)))
        {
            /* Check direction state */
            gpio_direction_state = gpio_portdirectionget(port); /* 0 = input */
            direction_check = gpio_direction_state | mask; /* if mask is high where pin is input, direction_check becomes high */

            /* if missmatch, then attempting to write to input pin - return error */
            if (direction_check == gpio_direction_state)
            {
                gpio_portwrite(port, value, mask);
            }
            else
            {
                ret_val = ER_INVAL;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PortWrite
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PortRead
 * Description  : Reads the levels of all pins on a port.
 * Arguments    : port -
 *                    Which port to read.
 *               value -
 *                    Value of the port
 * Return Value : Error state
 **********************************************************************************************************************/
ER_RET R_GPIO_PortRead (gpio_port_t port, uint32_t *value)
{
    ER_RET ret_val = ER_OK;

    if ((GPIO_MAX_PORT < port) || (GPIO_PORT_1A > port) || (NULL == value))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Read the selected port. No state enforcement */
        *value = gpio_portread(port);
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PortRead
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PortDirectionGet
 * Description  : Reads the DDR register of the selected port
 * Arguments    : port -
 *                    Which port to read.
 *                direction -
 *                    used to store the returned data for port direction
 * Return Value : unsigned 32 bit int
 **********************************************************************************************************************/
ER_RET R_GPIO_PortDirectionGet (gpio_port_t port, uint32_t *direction)
{
    ER_RET ret_val = ER_OK;

    if ((GPIO_MAX_PORT < port) || (GPIO_PORT_1A > port) || (NULL == direction))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Read the selected port DDR. No state enforcement */
        *direction = gpio_portdirectionget(port);
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PortDirectionGet
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PortDirectionSet
 * Description  : Sets multiple pins on a port to inputs or outputs at once. Each bit in the mask parameter corresponds
 *                to a pin on the port. For example, bit 7 of mask corresponds to pin 7, bit 6 corresponds to pin 6,
 *                and so forth. If a bit is set to 1 then the corresponding pin will be changed to an input or output
 *                as specified by the dir parameter. If a bit is set to 0 then the direction of the pin will not
 *                be changed.
 * Arguments    : port -
 *                    Which port to read.
 *                dir
 *                    Which direction to use.
 *                mask
 *                    Mask of which pins to set to change. 1 = set direction, 0 = do not change.
 * Return Value : none
 **********************************************************************************************************************/
ER_RET R_GPIO_PortDirectionSet (gpio_port_t port, gpio_dir_t dir, uint32_t mask)
{
    ER_RET ret_val = ER_OK;

    if ((GPIO_MAX_PORT < port) || (GPIO_PORT_1A > port) || (GPIO_DIRECTION_OUTPUT < dir))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check pins are open */
        if (ER_OK == (ret_val = r_gpio_checkporstate(port, GPIO_PIN_STATE_OPEN, mask)))
        {
            gpio_portdirectionset(port, dir, mask);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PortDirectionSet
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PinWrite
 * Description  : Sets the level of a pin.
 * Arguments    : pin -
 *                    Which pin to use.
 *                level
 *                    What level to set the pin to: GPIO_LEVEL_LOW or GPIO_LEVEL_HIGH
 * Return Value : Error state
 **********************************************************************************************************************/
ER_RET R_GPIO_PinWrite (gpio_port_pin_t pin, gpio_level_t level)
{
    ER_RET ret_val = ER_OK;

    if ((GPIO_MAX_PIN < pin) || (RZN1_GPIO_PORT(pin) > RZN1_GPIO_PORT(GPIO_MAX_PORT)) || (RZN1_GPIO_PORT(pin) < 0)
            || (0 == ((GPIO_PORT_INFO[RZN1_GPIO_PORT(pin)].port_mask) & (0x01 << (pin & 0xFF))))
            || (GPIO_LEVEL_HIGH < level))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check state is Open AND Output */
        if ((GPIO_PIN_STATE_OPEN == gpio_pin_state[RZN1_GPIO_PIN(pin)])
                && (gpio_pindirectionget(pin) == GPIO_DIRECTION_OUTPUT))
        {
            gpio_pinwrite(pin, level);
        }
        else
        {
            ret_val = ER_INVAL;
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PinWrite
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PinRead
 * Description  : Reads the level of a pin.
 * Arguments    : pin -
 *                    Which pin to read.
 * Return Value : Level of the pin.
 **********************************************************************************************************************/
ER_RET R_GPIO_PinRead (gpio_port_pin_t pin, gpio_level_t *level)
{
    ER_RET ret_val = ER_OK;

    if ((GPIO_MAX_PIN < pin) || (RZN1_GPIO_PORT(pin) > RZN1_GPIO_PORT(GPIO_MAX_PORT)) || (RZN1_GPIO_PORT(pin) < 0)
            || (0 == ((GPIO_PORT_INFO[RZN1_GPIO_PORT(pin)].port_mask) & (0x01 << (pin & 0xFF)))) || (NULL == level))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check state is Open AND Input */
        if ((GPIO_PIN_STATE_OPEN == gpio_pin_state[RZN1_GPIO_PIN(pin)])
                && (gpio_pindirectionget(pin) == GPIO_DIRECTION_INPUT))
        {
            *level = gpio_pinread(pin);
        }
        else
        {
            ret_val = ER_INVAL;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PinRead
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PinDirectionGet
 * Description  : Gets the direction of a pin.
 * Arguments    : pin -
 *                    Which pin to use
 *                dir -
 *                    Used to store data about the pin direction (GPIO_DIRECTION_OUTPUT, or GPIO_DIRECTION_INPUT)
 * Return Value : Direction the pin is set to. Options are GPIO_DIRECTION_INPUT or GPIO_DIRECTION_OUTPUT.
 **********************************************************************************************************************/
ER_RET R_GPIO_PinDirectionGet (gpio_port_pin_t pin, gpio_dir_t *dir)
{
    ER_RET ret_val = ER_OK;

    if ((GPIO_MAX_PIN < pin) || (RZN1_GPIO_PORT(pin) > RZN1_GPIO_PORT(GPIO_MAX_PORT)) || (RZN1_GPIO_PORT(pin) < 0)
            || (0 == ((GPIO_PORT_INFO[RZN1_GPIO_PORT(pin)].port_mask) & (0x01 << (pin & 0xFF)))) || (NULL == dir))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check state is Open */
        if (GPIO_PIN_STATE_OPEN == gpio_pin_state[RZN1_GPIO_PIN(pin)])
        {
            *dir = gpio_pindirectionget(pin);
        }
        else
        {
            ret_val = ER_INVAL;
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PinDirectionGet
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PinDirectionSet
 * Description  : Sets the direction of a pin.
 * Arguments    : pin -
 *                    Which pin to use
 *                dir -
 *                    Direction to set the pin to. Options are GPIO_DIRECTION_INPUT or GPIO_DIRECTION_OUTPUT.
 * Return Value : none
 **********************************************************************************************************************/
ER_RET R_GPIO_PinDirectionSet (gpio_port_pin_t pin, gpio_dir_t dir)
{
    ER_RET ret_val = ER_OK;

    if ((GPIO_MAX_PIN < pin) || (RZN1_GPIO_PORT(pin) > RZN1_GPIO_PORT(GPIO_MAX_PORT)) || (RZN1_GPIO_PORT(pin) < 0)
            || (0 == ((GPIO_PORT_INFO[RZN1_GPIO_PORT(pin)].port_mask) & (0x01 << (pin & 0xFF))))
            || (GPIO_DIRECTION_OUTPUT < dir))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check state is Open */
        if (GPIO_PIN_STATE_OPEN == gpio_pin_state[RZN1_GPIO_PIN(pin)])
        {
            gpio_pindirectionset(pin, dir);
        }
        else
        {
            ret_val = ER_INVAL;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PinDirectionSet
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_PinControl
 * Description  : Controls physical properties of a GPIO pin
 * Arguments    : pin -
 *                    Which pin to write to.
 *                cmd - which control command to execute
 *                gpio_ctrl -
 *                    Control parameter (data associated with the command).
 * Return Value : Error state
 **********************************************************************************************************************/
ER_RET R_GPIO_PinControl (gpio_port_pin_t pin, gpio_cmd_t cmd, void *gpio_ctrl)
{
    ER_RET ret_val = ER_OK;

    /* parameter check */
    if ((GPIO_MAX_PIN < pin) || (RZN1_GPIO_PORT(pin) > RZN1_GPIO_PORT(GPIO_MAX_PORT)) || (RZN1_GPIO_PORT(pin) < 0)
            || (0 == ((GPIO_PORT_INFO[RZN1_GPIO_PORT(pin)].port_mask) & (0x01 << (pin & 0xFF)))))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        switch (cmd)
        {
            case GPIO_CONTROL_GET_PIN_STATE:
                *(gpio_pin_states_t *) gpio_ctrl = gpio_pin_state[RZN1_GPIO_PIN(pin)];
            break;
            case GPIO_CONTROL_SET_INT:
                ret_val = r_gpio_iterruptenable(pin, *(gpio_int_en_t *) gpio_ctrl);
            break;
            case GPIO_CONTROL_SET_INT_MASK:
                ret_val = r_gpio_interruptmask(pin, *(gpio_int_mask_t *) gpio_ctrl);
            break;
            case GPIO_CONTROL_SET_INT_TRIG_TYPE:
                ret_val = r_gpio_interrupttriggertype(pin, *(gpio_int_trigger_type_t *) gpio_ctrl);
            break;
            case GPIO_CONTROL_SET_INT_TRIG_POL:
                ret_val = r_gpio_interrupttriggerpolarity(pin, *(gpio_int_polarity_t *) gpio_ctrl);
            break;
            default:
                ret_val = ER_PARAM;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_PinControl
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_RegInterruptCallBack
 * Description  : Registers an interrupt call back
 * Arguments    : gpio_call_back -
 *                       The call back function registered by the user.
 * Return Value : Error status
 **********************************************************************************************************************/
ER_RET R_GPIO_RegInterruptCallBack (gpio_callback gpio_call_back)
{
    ER_RET ret_val = ER_OK;

    if (gpio_call_back != NULL)
    {
        gpio_setcallback(gpio_call_back);
    }
    else
    {
        ret_val = ER_PARAM;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GPIO_RegInterruptCallBack
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_InterruptEnable
 * Description  : Enables or disables interrupts for a GPIO input pin
 * Arguments    : pin -
 *                    Which pin to use
 *                value -
 *                    Selects between normal GPIO signal (GPIO_INTTERRUPT_DISABLED),
 *                    and interrupt (GPIO_INTTERRUPT_DISABLED).
 * Return Value : GPIO_SUCCESS -
 *                    Command executed successfully.
 *                GPIO_ERR_INVALID_MODE -
 *                    Pin does not support requested mode.
 **********************************************************************************************************************/
ER_RET r_gpio_iterruptenable (gpio_port_pin_t pin, gpio_int_en_t value)
{
    ER_RET ret_val = ER_OK;
    bool interrupt_registered = false;
    uint8_t i;

    if ((GPIO_MAX_PIN < pin) || (RZN1_GPIO_PORT(pin) > RZN1_GPIO_PORT(GPIO_MAX_PORT)) || (RZN1_GPIO_PORT(pin) < 0)
            || (0 == ((GPIO_PORT_INFO[RZN1_GPIO_PORT(pin)].port_mask) & (0x01 << (pin & 0xFF))))
            || (GPIO_INTTERRUPT_ENABLED < value))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Only pins on A-Ports can be configured for interrupts */
        if (0x0A00 == (pin & 0x0F00))
        {
            if (GPIO_PIN_STATE_OPEN == gpio_pin_state[RZN1_GPIO_PIN(pin)])
            {
                if (GPIO_INTTERRUPT_ENABLED == value)
                {
                    for (i = 0; i < GPIO_MAX_INTERRUPT; i++) /* Check if there is a free IRQ */
                    {
                        if (GPIO_NO_PIN == gpio_interrupt_pins[i])
                        {
                            gpio_interrupt_pins[i] = pin;
                            rzn1_pinmux_gpio_register_interrupt(((pin >> 12) - 1), (pin & 0xFF), i);
                            interrupt_registered = true;
                            break;
                        }
                    }
                    if (true == interrupt_registered)
                    {
                        gpio_interruptenable(pin, value);
                    }
                    else
                    {
                        ret_val = ER_INVAL; /* No free IRQ lines */
                    }
                }
                else
                {
                    for (i = 0; i < GPIO_MAX_INTERRUPT; i++) /* Check if an interrupt has been set */
                    {
                        if (pin == gpio_interrupt_pins[i])
                        {
                            gpio_interrupt_pins[i] = GPIO_NO_PIN; /* Free the IRQ for another pin to use */
                            rzn1_pinmux_gpio_disable_interrupt(i);
                            interrupt_registered = true;
                            break;
                        }
                    }
                    if (true == interrupt_registered)
                    {
                        gpio_interruptenable(pin, value);
                    }
                    else
                    {
                        ret_val = ER_INVAL; /* Pin was not originally configured to have interrupts enabled */
                    }
                }
            }
            else
            {
                ret_val = ER_INVAL; /* Pin is not open */
            }
        }
        else
        {
            ret_val = ER_INVAL; /* B-Port pin selected */
        }
    } /* Pin in correct range */

    return ret_val;
}
/***********************************************************************************************************************
 End of function r_gpio_iterruptenable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_InterruptMask
 * Description  : Enables or disables interrupt mask for a GPIO pin.
 * Arguments    : pin -
 *                    Which pin to use
 *                value -
 *                    Selects between interrupt mask disabled (GPIO_INTTERRUPT_MASK_DISABLED),
 *                    and interrupt mask enabled (GPIO_INTTERRUPT_MASK_DISABLED).
 * Return Value : GPIO_SUCCESS -
 *                    Command executed successfully.
 *                GPIO_ERR_INVALID_MODE -
 *                    Pin does not support requested mode.
 **********************************************************************************************************************/
ER_RET r_gpio_interruptmask (gpio_port_pin_t pin, gpio_int_mask_t value)
{
    ER_RET ret_val = ER_OK;

    if ((GPIO_MAX_PIN < pin) || (RZN1_GPIO_PORT(pin) > RZN1_GPIO_PORT(GPIO_MAX_PORT)) || (RZN1_GPIO_PORT(pin) < 0)
            || (0 == ((GPIO_PORT_INFO[RZN1_GPIO_PORT(pin)].port_mask) & (0x01 << (pin & 0xFF))))
            || (GPIO_INTTERRUPT_MASK_ENABLED < value))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check state is Open */
        if (GPIO_PIN_STATE_OPEN == gpio_pin_state[RZN1_GPIO_PIN(pin)])
        {
            gpio_interruptmask(pin, value);
        }
        else
        {
            ret_val = ER_INVAL;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function r_gpio_interruptmask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_InterruptTriggerType
 * Description  : Enables or disables interrupt mask for a GPIO pin.
 * Arguments    : pin -
 *                    Which pin to use
 *                value -
 *                    Selects between level triggered interrupt (GPIO_INTTERRUPT_TRIGGER_LEVEL),
 *                    and edge level triggered interrupt (GPIO_INTTERRUPT_TRIGGER_EDGE).
 * Return Value : GPIO_SUCCESS -
 *                    Command executed successfully.
 *                GPIO_ERR_INVALID_MODE -
 *                    Pin does not support requested mode.
 **********************************************************************************************************************/
ER_RET r_gpio_interrupttriggertype (gpio_port_pin_t pin, gpio_int_trigger_type_t value)
{
    ER_RET ret_val = ER_OK;

    if ((GPIO_MAX_PIN < pin) || (RZN1_GPIO_PORT(pin) > RZN1_GPIO_PORT(GPIO_MAX_PORT)) || (RZN1_GPIO_PORT(pin) < 0)
            || (0 == ((GPIO_PORT_INFO[RZN1_GPIO_PORT(pin)].port_mask) & (0x01 << (pin & 0xFF))))
            || (GPIO_INTTERRUPT_TRIGGER_EDGE < value))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check state is Open */
        if (GPIO_PIN_STATE_OPEN == gpio_pin_state[RZN1_GPIO_PIN(pin)])
        {
            gpio_interrupttriggertype(pin, value);
        }
        else
        {
            ret_val = ER_INVAL;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function r_gpio_interrupttriggertype
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: R_GPIO_InterruptTriggerPolarity
 * Description  : Sets the interrupt polarity for a GPIO pin.
 * Arguments    : pin -
 *                    Which pin to use
 *                value -
 *                    Selects between Active Low (GPIO_INTTERRUPT_POLARITY_LOW),
 *                    and Active High triggered interrupt (GPIO_INTTERRUPT_POLARITY_HIGH).
 * Return Value : GPIO_SUCCESS -
 *                    Command executed successfully.
 *                GPIO_ERR_INVALID_MODE -
 *                    Pin does not support requested mode.
 **********************************************************************************************************************/
ER_RET r_gpio_interrupttriggerpolarity (gpio_port_pin_t pin, gpio_int_polarity_t value)
{
    ER_RET ret_val = ER_OK;

    if ((GPIO_MAX_PIN < pin) || (RZN1_GPIO_PORT(pin) > RZN1_GPIO_PORT(GPIO_MAX_PORT)) || (RZN1_GPIO_PORT(pin) < 0)
            || (0 == ((GPIO_PORT_INFO[RZN1_GPIO_PORT(pin)].port_mask) & (0x01 << (pin & 0xFF))))
            || (GPIO_INTTERRUPT_POLARITY_HIGH < value))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check state is Open */
        if (GPIO_PIN_STATE_OPEN == gpio_pin_state[RZN1_GPIO_PIN(pin)])
        {
            gpio_interrupttriggerpolarity(pin, value);
        }
        else
        {
            ret_val = ER_INVAL;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function r_gpio_interrupttriggerpolarity
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: GPIO_CheckPortState
 * Description  : Compares the states of unmasked pins of a port against the desired state
 * Arguments    : port -
 *                    Which port to use.
 *                desired_state -
 *                    The reference state.
 *                mask -
 *                    The mask used to specify which pins of the port to compare.
 * Return Value : Error state
 **********************************************************************************************************************/
static ER_RET r_gpio_checkporstate (gpio_port_t port, gpio_pin_states_t desired_state, uint32_t mask)
{
    ER_RET ret_val = ER_OK;
    uint16_t i;

    /* Loop through states of pins on the port */
    for (i = RZN1_GPIO_PIN(port); (i < (RZN1_GPIO_PIN(port) + 32)) || (GPIO_MAX_PIN < i); i++)
    {
        /* Compare pin state against desired state where mask is high */
        if ((gpio_pin_state[i] != desired_state) && (mask & (0x01 << (i - RZN1_GPIO_PIN(port)))))
        {
            /* If state missmatch, return error */
            ret_val = ER_INVAL;
            break;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function r_gpio_checkporstate
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: GPIO_CheckPortPinMux
 * Description  : Checks the selected pins of a port have been multiplexed for GPIO, returns error otherwise
 * Arguments    : port -
 *                    Which port to use.
 *                mask -
 *                    The mask used to specify which pins of the port to check.
 * Return Value : Error state
 **********************************************************************************************************************/
static ER_RET r_gpio_checkportpinmux (gpio_port_t port, uint32_t mask)
{
    ER_RET ret_val = ER_OK;
    uint16_t i;

    /* Loop through pins on the port */
    for (i = RZN1_GPIO_PIN(port); (i < (RZN1_GPIO_PIN(port) + 32)) || (GPIO_MAX_PIN < i); i++)
    {
        if (mask & (0x01 << (i - RZN1_GPIO_PIN(port))))
        {
            /* Check pin multiplexed for GPIO where mask is high */
            if (((rzn1_pinmux_get(rzn1_gpio_linear_pin_map[i]) >> RZN1_MUX_FUNC_BIT) & 0x7F) != RZN1_FUNC_GPIO)
            {
                /* If mux missmatch, return error */
                ret_val = ER_BUSY;
                break;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function r_gpio_checkportpinmux
 **********************************************************************************************************************/
