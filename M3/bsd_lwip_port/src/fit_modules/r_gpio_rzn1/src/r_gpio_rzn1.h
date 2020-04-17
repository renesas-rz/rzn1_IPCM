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
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_gpio_rzn1.h
 * Description  :  IO multiplexer driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_GPIO_RZN1_H__
#define R_GPIO_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 External variables
 **********************************************************************************************************************/
extern gpio_port_pin_t gpio_interrupt_pins[GPIO_MAX_INTERRUPT];

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/
ER_RET gpio_init (void);
ER_RET gpio_uninit (void);
void gpio_portwrite (gpio_port_t port, uint32_t value, uint32_t mask);
uint32_t gpio_portread (gpio_port_t port);
uint32_t gpio_portdirectionget (gpio_port_t port);
void gpio_portdirectionset (gpio_port_t port, gpio_dir_t dir, uint32_t mask);
void gpio_pinwrite (gpio_port_pin_t pin, gpio_level_t level);
gpio_level_t gpio_pinread (gpio_port_pin_t pin);
gpio_dir_t gpio_pindirectionget (gpio_port_pin_t pin);
void gpio_pindirectionset (gpio_port_pin_t pin, gpio_dir_t dir);
void gpio_setcallback (gpio_callback gpio_interrupt_callback);
void gpio_interruptenable (gpio_port_pin_t pin, gpio_int_en_t value);
void gpio_interruptmask (gpio_port_pin_t pin, gpio_int_mask_t value);
void gpio_interrupttriggertype (gpio_port_pin_t pin, gpio_int_trigger_type_t value);
void gpio_interrupttriggerpolarity (gpio_port_pin_t pin, gpio_int_polarity_t value);

#endif /* R_GPIO_RZN1_H__ */
