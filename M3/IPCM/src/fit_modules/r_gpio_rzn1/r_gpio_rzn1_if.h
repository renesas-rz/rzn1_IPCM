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
 * FILE         :  r_gpio_rzn1_if.h
 * Description  :  General Purpose I/O driver for RZN1 MCUs. This interface file has everything the user needs to use this
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef GPIO_RZN1_INTERFACE_HEADER_FILE
#define GPIO_RZN1_INTERFACE_HEADER_FILE

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"
/* Module configuration. */
#include "r_gpio_rzn1_config.h"

/* Include specifics for chosen MCU. Go to the header file for your MCU to see available ports and pins. */
#if defined(BSP_MCU_RZN1D)
#include "./src/targets/rzn1d/r_gpio_rzn1d.h"
#elif defined(BSP_MCU_RZN1L)
#include "./src/targets/rzn1l/r_gpio_rzn1l.h"
#elif defined(BSP_MCU_RZN1S)
#include "./src/targets/rzn1s/r_gpio_rzn1s.h"
#else
#error "This MCU is not supported by the current r_gpio_rzn1 module."
#endif

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* Version Number of API. */
#define GPIO_RZN1_VERSION_MAJOR           (1)
#define GPIO_RZN1_VERSION_MINOR           (7)

         /* First mask out the port number from the pin identifier,
         * then left shift a bit by this value.*/
#define GPIO_PIN_VALUE(pin)               (1u << ((pin) & 0x00FFu))
/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/* The gpio_port_t and gpio_port_pin_t enums are located in the 'targets' folder for each MCU. For example, to see
 * these enums for a RZN1 look at the following file: r_gpio_rzn1/src/targets/rzn1d/r_gpio_rzn1d.h
 */

/* State of the GPIO pin --> Whether or not it has been enabled as GPIO */
typedef enum
{
    GPIO_PIN_STATE_CLOSED = 0, /* Pin uninitialised */
    GPIO_PIN_STATE_OPEN, /* Pin initialised */
} gpio_pin_states_t;

/* Options that can be used with the R_GPIO_PortDirectionSet() and R_GPIO_PinDirectionSet() functions. */
typedef enum
{
    /* GPIO Input */
    GPIO_DIRECTION_INPUT = 0u,

    /* GPIO Output */
    GPIO_DIRECTION_OUTPUT = 1u
} gpio_dir_t;

typedef enum
{
    /* GPIO Pin Interrupt Disable */
    GPIO_INTTERRUPT_DISABLED = 0u,

    /* GPIO Pin Interrupt Enable */
    GPIO_INTTERRUPT_ENABLED = 1u
} gpio_int_en_t;

typedef enum
{
    /* GPIO Pin Interrupt Mask Disable */
    GPIO_INTTERRUPT_MASK_DISABLED = 0u,

    /* GPIO Pin Interrupt Mask Enable */
    GPIO_INTTERRUPT_MASK_ENABLED = 1u
} gpio_int_mask_t;

typedef enum
{
    /* GPIO Pin Interrupt level triggered */
    GPIO_INTTERRUPT_TRIGGER_LEVEL = 0u,

    /* GPIO Pin Interrupt edge triggered */
    GPIO_INTTERRUPT_TRIGGER_EDGE = 1u
} gpio_int_trigger_type_t;

typedef enum
{
    /* GPIO Pin Interrupt Polarity Low */
    GPIO_INTTERRUPT_POLARITY_LOW = 0u,

    /* GPIO Pin Interrupt polarity High */
    GPIO_INTTERRUPT_POLARITY_HIGH = 1u
} gpio_int_polarity_t;

typedef enum
{
    /* Output/Input Level low */
    GPIO_LEVEL_LOW = 0u,

    /* Output/Input Level high */
    GPIO_LEVEL_HIGH = 1u
} gpio_level_t;

/* GPIO Control requests */
typedef enum
{
    GPIO_CONTROL_GET_PIN_STATE, /* Get the pin state */
    GPIO_CONTROL_SET_INT, /* Enable or disable interrupts */

    /* A maximum of 8 A-Port pins can be enabled for interrupts at a time */
    GPIO_CONTROL_SET_INT_MASK, /* Setup interrupt mask */
    GPIO_CONTROL_SET_INT_TRIG_TYPE, /* Set the interrupt trigger type */
    GPIO_CONTROL_SET_INT_TRIG_POL /* Set the interrupt trigger polarity */
} gpio_cmd_t;

/* Call back function for interrupts */
typedef void (*gpio_callback) (gpio_port_pin_t pin);

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
void R_GPIO_GetVersion (void *buf);

ER_RET R_GPIO_Init (void);
ER_RET R_GPIO_Uninitialise (void);
ER_RET R_GPIO_PortOpen (gpio_port_t port, uint32_t mask);
ER_RET R_GPIO_PinOpen (gpio_port_pin_t pin);
ER_RET R_GPIO_PortClose (gpio_port_t port, uint32_t mask);
ER_RET R_GPIO_PinClose (gpio_port_pin_t pin);

ER_RET R_GPIO_PortWrite (gpio_port_t port, uint32_t value, uint32_t mask);
ER_RET R_GPIO_PortRead (gpio_port_t port, uint32_t *value);
ER_RET R_GPIO_PortDirectionGet (gpio_port_t port, uint32_t *direction);
ER_RET R_GPIO_PortDirectionSet (gpio_port_t port, gpio_dir_t dir, uint32_t mask);

ER_RET R_GPIO_PinWrite (gpio_port_pin_t pin, gpio_level_t level);
ER_RET R_GPIO_PinRead (gpio_port_pin_t pin, gpio_level_t *level);
ER_RET R_GPIO_PinDirectionGet (gpio_port_pin_t pin, gpio_dir_t *dir);
ER_RET R_GPIO_PinDirectionSet (gpio_port_pin_t pin, gpio_dir_t dir);

ER_RET R_GPIO_RegInterruptCallBack (gpio_callback gpio_call_back);
ER_RET R_GPIO_PinControl (gpio_port_pin_t pin, gpio_cmd_t cmd, void *gpio_ctrl);

#endif /* GPIO_RZN1_INTERFACE_HEADER_FILE */

