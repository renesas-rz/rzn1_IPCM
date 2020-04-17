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
 * $Revision: 1277 $
 * $Date: 2019-02-19 10:31:41 +0000 (Tue, 19 Feb 2019) $
 *
 * PROJECT NAME :   RZ/N1 bare metal Drivers
 * FILE         :   r_iomux_rzn1_if.h
 * Description  :   I/O multiplexing driver for RZN1 MCUs - API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 31.08.2017 0.00    Pre-Release
 **********************************************************************************************************************/
#ifndef IOMUX_RZN1_INTERFACE_HEADER_FILE
#define IOMUX_RZN1_INTERFACE_HEADER_FILE

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "platform.h"
#include "r_gpio_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
typedef struct
{
        uint8_t function;
        uint8_t drive_strength;
        uint8_t pull_level;
} iomux_pin_properties_t;

typedef enum
{
    IOMUX_CONTROL_GET_PIN_PROPERTIES,
    IOMUX_CONTROL_SET_PIN_PROPERTIES
} iomux_cmd_t;
/***********************************************************************************************************************
 Function prototypes
 **********************************************************************************************************************/
ER_RET R_IOMUX_PinCtrl (uint8_t pin, iomux_cmd_t cmd, iomux_pin_properties_t *properties);
ER_RET R_IOMUX_PortCtrl (gpio_port_t port, uint32_t port_mask, iomux_cmd_t cmd, iomux_pin_properties_t *properties);

#endif /* IOMUX_RZN1_INTERFACE_HEADER_FILE */
