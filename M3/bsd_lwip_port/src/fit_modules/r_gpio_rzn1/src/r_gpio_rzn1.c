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
 * $Revision: 1343 $
 * $Date: 2019-03-07 14:32:01 +0000 (Thu, 07 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_gpio_rzn1.c
 * Description  :  General Purpose Input/Output driver for RZN1 MCUs.
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
#include "r_sysctrl_rzn1_if.h"
#include "iodefine.h"

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
static uint32_t volatile * gpio_port_addr_get (gpio_register_type_t register_type, uint16_t index);
static BGPIO_Type *pBGPIO1;
#if 0
static void handle_gpio_isr (IRQn_Type *irq_num_ptr);
#endif
gpio_callback gpio_call_back;

/***********************************************************************************************************************
 * Function Name: gpio_init
 * Description  : Sets the BGPIO base addresses and registers interrupts
 * Arguments    : None
 * Return Value : Error state.
 **********************************************************************************************************************/
ER_RET gpio_init (void)
{
    ER_RET ret_val = ER_OK;
#if 0
    IRQn_Type irq_num = (uint8_t) RZN1_IRQ_GPIO_0;
    uint32_t int_priority = GPIO_DEFAULT_INT_PRIORITY;
#endif
    uint32_t address = RZN1_GPIO0_BASE;

    for (pBGPIO1 = (BGPIO_Type *) RZN1_GPIO0_BASE; pBGPIO1 <= (BGPIO_Type *) RZN1_GPIO2_BASE; pBGPIO1 =
            (BGPIO_Type *) (address += 0x1000))
    {
        pBGPIO1->rGPIO_swportb_ddr.LONG = 0;
        pBGPIO1->rGPIO_swporta_ddr.LONG = 0;

    }
    pBGPIO1 = (BGPIO_Type *) RZN1_GPIO0_BASE;

    /* Setup power management control for BGPIO */
    R_SYSCTRL_EnableBGPIO();

#if 0
    for (irq_num = RZN1_IRQ_GPIO_0; (irq_num <= RZN1_IRQ_GPIO_7) && (ER_OK == ret_val); irq_num++)
    {
        /* Register interrupts */
        if (R_BSP_InterruptRegisterCallback((IRQn_Type) irq_num, (bsp_int_cb_t) &handle_gpio_isr) == MCU_INT_SUCCESS)
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
    return ret_val;
}
/***********************************************************************************************************************
 End of function gpio_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_uninit
 * Description  : Disables the power magament for GPIO and disables interrupts
 * Arguments    : None
 * Return Value : Error state.
 **********************************************************************************************************************/

ER_RET gpio_uninit (void)
{
    ER_RET ret_val = ER_OK;
#if 0
    IRQn_Type irq_num = (uint8_t) RZN1_IRQ_GPIO_0;
#endif
    uint32_t address = RZN1_GPIO0_BASE;

    for (pBGPIO1 = (BGPIO_Type *) RZN1_GPIO0_BASE; pBGPIO1 <= (BGPIO_Type *) RZN1_GPIO2_BASE; pBGPIO1 =
            (BGPIO_Type *) (address += 0x1000))
    {
        pBGPIO1->rGPIO_swportb_ddr.LONG = 0;
        pBGPIO1->rGPIO_swporta_ddr.LONG = 0;

    }

    pBGPIO1 = (BGPIO_Type *) RZN1_GPIO0_BASE;

    /* Setup power management control for BGPIO */
    R_SYSCTRL_DisableBGPIO();

#if 0
    for (irq_num = RZN1_IRQ_GPIO_0; (irq_num <= RZN1_IRQ_GPIO_7) && (ER_OK == ret_val); irq_num++)
    {
        /* Register interrupts */
        if (R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE,
        FIT_NO_PTR) != MCU_INT_SUCCESS)
        {
            ret_val = ER_SYS;
            break;
        }
    }
#endif
    return ret_val;
}
/***********************************************************************************************************************
 End of function gpio_uninit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_portwrite
 * Description  : Writes the levels of all pins on a port.
 * Arguments    : port -
 *                    Which port to write to.
 *                value -
 *                    The value to write to the port. Each bit corresponds to a pin on the port (e.g. bit 0 of value
 *                    will be written to pin 0 on supplied port)
 *                mask -
 *                    Mask to allow certain pins of the port to be changed. A pin will only change value when the
 *                    corresponding mask bit is 1.
 * Return Value : none
 **********************************************************************************************************************/
void gpio_portwrite (gpio_port_t port, uint32_t value, uint32_t mask)
{
    uint32_t volatile * podr;
    uint32_t write_value;

    /* Get register address. */
    podr = gpio_port_addr_get(GPIO_REGISTER_ODR, (uint16_t) port);
    write_value = *podr;

    /* Write logic high to wherever mask and value are logic high. */
    write_value = (uint32_t)(write_value | (mask & value));

    /* Write logic low to wherever mask is logic high and value is logic low. */
    write_value = (uint32_t)(write_value & ( ~(( ~value) & mask))); /* !!Check that the value  has been written by reading back and comparing!! - also check the direction is output */

    *podr = write_value;
}
/***********************************************************************************************************************
 End of function gpio_portwrite
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_portread
 * Description  : Reads the levels of all pins on a port.
 * Arguments    : port -
 *                    Which port to read.
 * Return Value : Value of the port
 **********************************************************************************************************************/
uint32_t gpio_portread (gpio_port_t port)
{
    return *gpio_port_addr_get(GPIO_REGISTER_IDR, (uint16_t) port);
}
/***********************************************************************************************************************
 End of function gpio_portread
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_portdirectionget
 * Description  : Reads the DDR register of the selected port
 * Arguments    : port -
 *                    Which port to read.
 * Return Value : unsigned 32 bit int
 **********************************************************************************************************************/
uint32_t gpio_portdirectionget (gpio_port_t port)
{
    uint32_t volatile * pdr;

    /* Get register address. */
    pdr = gpio_port_addr_get(GPIO_REGISTER_DDR, (uint16_t) port);
    return *pdr;
}
/***********************************************************************************************************************
 End of function gpio_portdirectionget
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_portdirectionset
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
void gpio_portdirectionset (gpio_port_t port, gpio_dir_t dir, uint32_t mask)
{
    uint32_t volatile * pdr;

    /* Get register address. */
    pdr = gpio_port_addr_get(GPIO_REGISTER_DDR, (uint16_t) port);

    /* Write to the selected register. & or | based on direction. */
    if (GPIO_DIRECTION_INPUT == dir)
    {
        *pdr = (uint32_t)(( *pdr) & ( ~mask));
    }
    else
    {
        *pdr = (uint32_t)(( *pdr) | mask);
    }
}
/***********************************************************************************************************************
 End of function gpio_portdirectionset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: GPIO_PinWrite
 * Description  : Sets the level of a pin.
 * Arguments    : pin -
 *                    Which pin to use.
 *                level
 *                    What level to set the pin to: GPIO_LEVEL_LOW or GPIO_LEVEL_HIGH
 * Return Value : none
 **********************************************************************************************************************/
void gpio_pinwrite (gpio_port_pin_t pin, gpio_level_t level)
{
    uint32_t volatile * podr;

    /* Get register address. */
    podr = gpio_port_addr_get(GPIO_REGISTER_ODR, (uint16_t) pin);

    /* Write to the selected bit. & or | based on direction. */
    if (GPIO_LEVEL_LOW == level)
    {
        /* Set the pin value low:
         * As we are setting the bit low, invert the bits then bitwise AND with this value.
         */
        *podr = (uint32_t)(( *podr) & ( ~GPIO_PIN_VALUE(pin)));
    }
    else
    {
        /* Set the pin value low:
         * As we are setting the bit high, bitwise OR with this value.
         */
        *podr = (uint32_t)(( *podr) | GPIO_PIN_VALUE(pin));
    }
}
/***********************************************************************************************************************
 End of function gpio_pinwrite
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_pinread
 * Description  : Reads the level of a pin.
 * Arguments    : pin -
 *                    Which pin to read.
 * Return Value : Level of the pin.
 **********************************************************************************************************************/
gpio_level_t gpio_pinread (gpio_port_pin_t pin)
{
    uint32_t volatile * pdr;

    /* Get Input Data Register address. */
    pdr = gpio_port_addr_get(GPIO_REGISTER_IDR, (uint16_t) pin);

    /* Mask to get the individual bit without the port identifier. */
    if ((( *pdr) & GPIO_PIN_VALUE(pin)) != 0u)
    {
        return GPIO_LEVEL_HIGH;
    }
    else
    {
        return GPIO_LEVEL_LOW;
    }
}
/***********************************************************************************************************************
 End of function gpio_pinread
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_pindirectionget
 * Description  : Gets the direction of a pin.
 * Arguments    : pin -
 *                    Which pin to use
 * Return Value : Direction the pin is set to. Options are GPIO_DIRECTION_INPUT or GPIO_DIRECTION_OUTPUT.
 **********************************************************************************************************************/
gpio_dir_t gpio_pindirectionget (gpio_port_pin_t pin)
{
    uint32_t volatile * pdr;

    /* Get register address. The high byte of the pin */
    pdr = gpio_port_addr_get(GPIO_REGISTER_DDR, (uint16_t) pin);

    /* Read the direction of the selected bit.
     The low byte of the pin indicates the bit number */
    if ((( *pdr) & GPIO_PIN_VALUE(pin)) != 0u)
    {
        return GPIO_DIRECTION_OUTPUT;
    }
    else
    {
        return GPIO_DIRECTION_INPUT;
    }
}
/***********************************************************************************************************************
 End of function gpio_pindirectionget
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_pindirectionset
 * Description  : Sets the direction of a pin.
 * Arguments    : pin -
 *                    Which pin to use
 *                dir -
 *                    Direction to set the pin to. Options are GPIO_DIRECTION_INPUT or GPIO_DIRECTION_OUTPUT.
 * Return Value : None.
 **********************************************************************************************************************/
void gpio_pindirectionset (gpio_port_pin_t pin, gpio_dir_t dir)
{
    uint32_t volatile * pdr;

    /* Get register address. */
    pdr = gpio_port_addr_get(GPIO_REGISTER_DDR, (uint16_t) pin);

    /* Write to the selected bit. & or | based on direction. */
    if (GPIO_DIRECTION_INPUT == dir)
    {
        /* Set the pin direction low (input):
         * As we are setting the bit low, invert the bits then bitwise AND with this value.
         */
        *pdr = (uint32_t)(( *pdr) & ( ~GPIO_PIN_VALUE(pin)));
    }
    else
    {
        /* Set the pin direction high (output):
         * As we are setting the bit high, bitwise OR with this value.
         */
        *pdr = (uint32_t)(( *pdr) | GPIO_PIN_VALUE(pin));
    }
}
/***********************************************************************************************************************
 End of function gpio_pindirectionset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_setcallback
 * Description  : Sets callback for GPIO interupts.
 * Arguments    : gpio_interrupt_callback -
 *                    pointer to callback function
 *
 * Return Value : None.
 **********************************************************************************************************************/
void gpio_setcallback (gpio_callback gpio_interrupt_callback)
{
    gpio_call_back = gpio_interrupt_callback;
}
/***********************************************************************************************************************
 End of function gpio_setcallback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_interruptenable
 * Description  : Enables or disables interrupts for a GPIO input pin
 * Arguments    : pin -
 *                    Which pin to use
 *                value -
 *                    Selects between normal GPIO signal (GPIO_INTTERRUPT_DISABLED),
 *                    and interrupt (GPIO_INTTERRUPT_DISABLED).
 * Return Value : None.
 **********************************************************************************************************************/
void gpio_interruptenable (gpio_port_pin_t pin, gpio_int_en_t value)
{
    uint32_t volatile * pdr;

    /* Clear any pending interrupt */
    pdr = gpio_port_addr_get(GPIO_REGISTER_EOI, (uint16_t) pin);
    *pdr = (uint32_t)(( *pdr) | GPIO_PIN_VALUE(pin));

    /* Get register address. */
    pdr = gpio_port_addr_get(GPIO_REGISTER_INTEN, (uint16_t) pin);

    /* Write to the selected bit. & or | based on direction. */
    if (GPIO_INTTERRUPT_DISABLED == value)
    {
        /* Disable interrupts for this pin:
         * As we are setting the bit low, invert the bits then bitwise AND with this value.
         */
        *pdr = (uint32_t)(( *pdr) & ( ~GPIO_PIN_VALUE(pin)));
    }
    else
    {
        /* Enable interrupts for this pin:
         * As we are setting the bit high, bitwise OR with this value.
         */
        *pdr = (uint32_t)(( *pdr) | GPIO_PIN_VALUE(pin));
    }
}
/***********************************************************************************************************************
 End of function gpio_interruptenable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_interruptmask
 * Description  : Enables or disables interrupt mask for a GPIO pin.
 * Arguments    : pin -
 *                    Which pin to use
 *                value -
 *                    Selects between interrupt mask disabled (GPIO_INTTERRUPT_MASK_DISABLED),
 *                    and interrupt mask enabled (GPIO_INTTERRUPT_MASK_DISABLED).
 * Return Value : None.
 **********************************************************************************************************************/
void gpio_interruptmask (gpio_port_pin_t pin, gpio_int_mask_t value)
{
    uint32_t volatile * pdr;

    /* Get register address. */
    pdr = gpio_port_addr_get(GPIO_REGISTER_INTMASK, (uint16_t) pin);

    /* Write to the selected bit. & or | based on direction. */
    if (GPIO_INTTERRUPT_MASK_DISABLED == value)
    {
        /* Clear masking of interrupts for this pin:
         * As we are setting the bit low, invert the bits then bitwise AND with this value.
         */
        *pdr = (uint32_t)(( *pdr) & ( ~GPIO_PIN_VALUE(pin)));
    }
    else
    {
        /* Set masking of interrupts for this pin:
         * As we are setting the bit high, bitwise OR with this value.
         */
        *pdr = (uint32_t)(( *pdr) | GPIO_PIN_VALUE(pin));
    }
}
/***********************************************************************************************************************
 End of function gpio_interruptmask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_interrupttriggertype
 * Description  : Enables or disables interrupt mask for a GPIO pin.
 * Arguments    : pin -
 *                    Which pin to use
 *                value -
 *                    Selects between level triggered interrupt (GPIO_INTTERRUPT_TRIGGER_LEVEL),
 *                    and edge level triggered interrupt (GPIO_INTTERRUPT_TRIGGER_EDGE).
 * Return Value : None.
 **********************************************************************************************************************/
void gpio_interrupttriggertype (gpio_port_pin_t pin, gpio_int_trigger_type_t value)
{
    uint32_t volatile * pdr;

    /* Get register address. */
    pdr = gpio_port_addr_get(GPIO_REGISTER_INTTYPE_LEVEL, (uint16_t) pin);

    /* Write to the selected bit. & or | based on direction. */
    if (GPIO_INTTERRUPT_TRIGGER_LEVEL == value)
    {
        /* Clear masking of interrupts for this pin:
         * As we are setting the bit low, invert the bits then bitwise AND with this value.
         */
        *pdr = (uint32_t)(( *pdr) & ( ~GPIO_PIN_VALUE(pin)));
    }
    else
    {
        /* Set masking of interrupts for this pin:
         * As we are setting the bit high, bitwise OR with this value.
         */
        *pdr = (uint32_t)(( *pdr) | GPIO_PIN_VALUE(pin));
    }
}
/***********************************************************************************************************************
 End of function gpio_interrupttriggertype
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_interrupttriggerpolarity
 * Description  : Sets the interrupt polarity for a GPIO pin.
 * Arguments    : pin -
 *                    Which pin to use
 *                value -
 *                    Selects between Active Low (GPIO_INTTERRUPT_POLARITY_LOW),
 *                    and Active High triggered interrupt (GPIO_INTTERRUPT_POLARITY_HIGH).
 * Return Value : None.
 **********************************************************************************************************************/
void gpio_interrupttriggerpolarity (gpio_port_pin_t pin, gpio_int_polarity_t value)
{
    uint32_t volatile * pdr;

    /* Get register address. */
    pdr = gpio_port_addr_get(GPIO_REGISTER_INT_POLARITY, (uint16_t) pin);

    /* Write to the selected bit. & or | based on direction. */
    if (GPIO_INTTERRUPT_POLARITY_LOW == value)
    {
        /* Clear masking of interrupts for this pin:
         * As we are setting the bit low, invert the bits then bitwise AND with this value.
         */
        *pdr = (uint32_t)(( *pdr) & ( ~GPIO_PIN_VALUE(pin)));
    }
    else
    {
        /* Set masking of interrupts for this pin:
         * As we are setting the bit high, bitwise OR with this value.
         */
        *pdr = (uint32_t)(( *pdr) | GPIO_PIN_VALUE(pin));
    }
}
/***********************************************************************************************************************
 End of function gpio_interrupttriggerpolarity
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: gpio_port_addr_get
 * Description  : Get the address for a port register based on a base port register address.
 * Arguments    : base_addr -
 *                    First port register of this type (e.g. &PORT0.PODR.BYTE)
 *                index -
 *                    Index off the base. (e.g. for PORT4 it would be 0x0400)
 * Return Value : Address of the register that was requested
 **********************************************************************************************************************/
static uint32_t volatile * gpio_port_addr_get (gpio_register_type_t register_type, uint16_t index)
{
    volatile void * register_address;

    /* set register_address to the address of the first register of the first port initially */
    /* Set the register address according to the register_type. These will be for port 1 initially, then adjusted
     * for ports 2 and 3 */
    switch (register_type)
    {
        /* Output Data Register */
        case GPIO_REGISTER_ODR:
            /* A and B ports use separate registers */
            if (0x0B00u == (index & 0x0F00u))
            {
                register_address = &pBGPIO1->rGPIO_swportb_dr;
            }
            else
            {
                register_address = &pBGPIO1->rGPIO_swporta_dr;
            }
        break;

            /* Data Direction Register */
        case GPIO_REGISTER_DDR:
            /* A and B ports use separate registers */
            if (0x0B00u == (index & 0x0F00u))
            {
                register_address = &pBGPIO1->rGPIO_swportb_ddr;
            }
            else
            {
                register_address = &pBGPIO1->rGPIO_swporta_ddr;
            }
        break;

            /* Interrupt Enable Register */
        case GPIO_REGISTER_INTEN:
            register_address = &pBGPIO1->rGPIO_inten;
        break;

            /* Interrupt Mask Register */
        case GPIO_REGISTER_INTMASK:
            register_address = &pBGPIO1->rGPIO_intmask;
        break;

            /* Interrupt Type Level Register */
        case GPIO_REGISTER_INTTYPE_LEVEL:
            register_address = &pBGPIO1->rGPIO_inttype_level;
        break;

            /* Interrupt Polarity Register */
        case GPIO_REGISTER_INT_POLARITY:
            register_address = &pBGPIO1->rGPIO_int_polarity;
        break;

            /* Interrupt Status Register */
        case GPIO_REGISTER_INTSTATUS:
            register_address = &pBGPIO1->rGPIO_intstatus;
        break;

            /* Raw Interrupt Status Register */
        case GPIO_REGISTER_RAW_INTSTATUS:
            register_address = &pBGPIO1->rGPIO_raw_intstatus;
        break;

            /* Clear Interrupt Register */
        case GPIO_REGISTER_EOI:
            register_address = &pBGPIO1->rGPIO_porta_eoi;
        break;

            /* Input Data Register */
        case GPIO_REGISTER_IDR:
            /* A and B ports use separate registers */
            if (0x0B00u == (index & 0x0F00u))
            {
                register_address = &pBGPIO1->rGPIO_ext_portb;
            }
            else
            {
                register_address = &pBGPIO1->rGPIO_ext_porta;
            }
        break;

            /* Level Sensitive Synchronisation Enable Register */
        case GPIO_REGISTER_LS_SYNC:
            register_address = &pBGPIO1->rGPIO_ls_sync;
        break;

        default:
            register_address = NULL;
        break;
    }

    /* Adjust register address according to the port number.
     * The port number is the top nibble of the 16 bit index, as they are identified as H'1Axx, H'1Bxx etc.
     * We need to mask the irrelevant bits, add it to the base address and subtract H'1000, to get the address
     * of the first register of the port.
     */
    register_address = (volatile void *) ((uint32_t) register_address + ((index & 0xF000u) - 0x1000u));
    return register_address;
}
/***********************************************************************************************************************
 End of function gpio_port_addr_get
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       handle_gpio_isr
 *
 *  Return value:   None.
 *
 *  Parameters:     irq_num_ptr - contains the number of the IRQ generated.
 *
 *  Description:    Interrupt handler for GPIO.
 *
 **********************************************************************************************************************/
#if 0
static void handle_gpio_isr (IRQn_Type *irq_num_ptr)
{
    volatile BGPIO_Type *baseaddress;
    IRQn_Type irq_num = *irq_num_ptr;
    gpio_port_pin_t pin;
    uint8_t interrupt_array_element;

    /* Determine the interrupt causing pin */
    interrupt_array_element = irq_num - RZN1_IRQ_GPIO_0;

    pin = gpio_interrupt_pins[interrupt_array_element];
    baseaddress = (BGPIO_Type *) ((uint32_t) pBGPIO1 + (((uint32_t) pin & 0xF000u) - 0x1000u));

    /* Clear the interrupt */
    baseaddress->rGPIO_porta_eoi.LONG |= (0x01 << (pin & 0x00FF));

    /* Callback function */
    if (NULL != gpio_call_back)
    {
        (gpio_call_back)(pin);
    }
}
#endif
/***********************************************************************************************************************
 End of function handle_gpio_isr
 **********************************************************************************************************************/
