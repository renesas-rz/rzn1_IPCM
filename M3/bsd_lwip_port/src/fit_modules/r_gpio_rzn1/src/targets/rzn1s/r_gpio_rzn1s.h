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
 * FILE         :  r_gpio_rzn1s.h
 * Description  :  Specifics for the r_gpio_rzn1d driver for the RZN1S.
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef R_GPIO_RZN1S_H__
#define R_GPIO_RZN1S_H__

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"
#if defined(BSP_MCU_RZN1S)  //Prevents the compiler from finding multiple definitions of constant in this file.

/* Configuration for this package. */
#include "r_gpio_rzn1_config.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* General information about number of ports and pins on this device. */
#define GPIO_MAX_INTERRUPT                  (8u)

#if (BSP_PACKAGE_PINS == 324)
#define GPIO_INFO_NUM_PORTS             (5u)
#define GPIO_INFO_NUM_PINS              (160u)
#elif (BSP_PACKAGE_PINS == 196)
#define GPIO_INFO_NUM_PORTS             (5u)
#define GPIO_INFO_NUM_PINS              (95u)
#else
#error "r_gpio_rzn1[x].h does not have information about this r_gpio_rzn1[x] package. Please update r_gpio_rzn1[x].h"
#endif

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/* Register type enumerator */
typedef enum
{
    /* Output Data Register */
    GPIO_REGISTER_ODR,
    /* Data Direction Register */
    GPIO_REGISTER_DDR,
    /* Interrupt Enable Register */
    GPIO_REGISTER_INTEN,
    /* Interrupt Mask Register */
    GPIO_REGISTER_INTMASK,
    /* Interrupt Type Level Register */
    GPIO_REGISTER_INTTYPE_LEVEL,
    /* Interrupt Polarity Register */
    GPIO_REGISTER_INT_POLARITY,
    /* Interrupt Status Register */
    GPIO_REGISTER_INTSTATUS,
    /* Raw Interrupt Status Register */
    GPIO_REGISTER_RAW_INTSTATUS,
    /* Clear Interrupt Register */
    GPIO_REGISTER_EOI,
    /* Input Data Register */
    GPIO_REGISTER_IDR,
    /* Level Sensitive Synchronisation Enable Register */
    GPIO_REGISTER_LS_SYNC,
}gpio_register_type_t;

#if (BSP_PACKAGE_PINS == 324)

#define GPIO_MAX_PORT (GPIO_PORT_3A)
#define GPIO_MAX_PIN (GPIO_PORT_3A_PIN_31)

/* This enumerator has each available GPIO port on this MCU. This list will change depending on the MCU chosen. */
typedef enum
{
    GPIO_PORT_1A = 0x1A00u,
    GPIO_PORT_1B = 0x1B00u,
    GPIO_PORT_2A = 0x2A00u,
    GPIO_PORT_2B = 0x2B00u,
    GPIO_PORT_3A = 0x3A00u,
}gpio_port_t;

#define PORT_1A_SIZE (32)
#define PORT_1B_SIZE (32)
#define PORT_2A_SIZE (32)
#define PORT_2B_SIZE (32)
#define PORT_3A_SIZE (32)
#define PORT_3B_SIZE (0)

#define PORT_1A_MASK (0xFFFFFFFF)
#define PORT_1B_MASK (0xFFFFFFFF)
#define PORT_2A_MASK (0xFFFFFFFF)
#define PORT_2B_MASK (0xFFFFFFFF)
#define PORT_3A_MASK (0xFFFFFFFF)
#define PORT_3B_MASK (0x000003FF)

typedef enum
{
    GPIO_NO_PIN = 0x0000,
    GPIO_PORT_1A_PIN_00 = 0x1A00,
    GPIO_PORT_1A_PIN_01 = 0x1A01,
    GPIO_PORT_1A_PIN_02 = 0x1A02,
    GPIO_PORT_1A_PIN_03 = 0x1A03,
    GPIO_PORT_1A_PIN_04 = 0x1A04,
    GPIO_PORT_1A_PIN_05 = 0x1A05,
    GPIO_PORT_1A_PIN_06 = 0x1A06,
    GPIO_PORT_1A_PIN_07 = 0x1A07,
    GPIO_PORT_1A_PIN_08 = 0x1A08,
    GPIO_PORT_1A_PIN_09 = 0x1A09,
    GPIO_PORT_1A_PIN_10 = 0x1A0A,
    GPIO_PORT_1A_PIN_11 = 0x1A0B,
    GPIO_PORT_1A_PIN_12 = 0x1A0C,
    GPIO_PORT_1A_PIN_13 = 0x1A0D,
    GPIO_PORT_1A_PIN_14 = 0x1A0E,
    GPIO_PORT_1A_PIN_15 = 0x1A0F,
    GPIO_PORT_1A_PIN_16 = 0x1A10,
    GPIO_PORT_1A_PIN_17 = 0x1A11,
    GPIO_PORT_1A_PIN_18 = 0x1A12,
    GPIO_PORT_1A_PIN_19 = 0x1A13,
    GPIO_PORT_1A_PIN_20 = 0x1A14,
    GPIO_PORT_1A_PIN_21 = 0x1A15,
    GPIO_PORT_1A_PIN_22 = 0x1A16,
    GPIO_PORT_1A_PIN_23 = 0x1A17,
    GPIO_PORT_1A_PIN_24 = 0x1A18,
    GPIO_PORT_1A_PIN_25 = 0x1A19,
    GPIO_PORT_1A_PIN_26 = 0x1A1A,
    GPIO_PORT_1A_PIN_27 = 0x1A1B,
    GPIO_PORT_1A_PIN_28 = 0x1A1C,
    GPIO_PORT_1A_PIN_29 = 0x1A1D,
    GPIO_PORT_1A_PIN_30 = 0x1A1E,
    GPIO_PORT_1A_PIN_31 = 0x1A1F,
    GPIO_PORT_1B_PIN_00 = 0x1B00,
    GPIO_PORT_1B_PIN_01 = 0x1B01,
    GPIO_PORT_1B_PIN_02 = 0x1B02,
    GPIO_PORT_1B_PIN_03 = 0x1B03,
    GPIO_PORT_1B_PIN_04 = 0x1B04,
    GPIO_PORT_1B_PIN_05 = 0x1B05,
    GPIO_PORT_1B_PIN_06 = 0x1B06,
    GPIO_PORT_1B_PIN_07 = 0x1B07,
    GPIO_PORT_1B_PIN_08 = 0x1B08,
    GPIO_PORT_1B_PIN_09 = 0x1B09,
    GPIO_PORT_1B_PIN_10 = 0x1B0A,
    GPIO_PORT_1B_PIN_11 = 0x1B0B,
    GPIO_PORT_1B_PIN_12 = 0x1B0C,
    GPIO_PORT_1B_PIN_13 = 0x1B0D,
    GPIO_PORT_1B_PIN_14 = 0x1B0E,
    GPIO_PORT_1B_PIN_15 = 0x1B0F,
    GPIO_PORT_1B_PIN_16 = 0x1B10,
    GPIO_PORT_1B_PIN_17 = 0x1B11,
    GPIO_PORT_1B_PIN_18 = 0x1B12,
    GPIO_PORT_1B_PIN_19 = 0x1B13,
    GPIO_PORT_1B_PIN_20 = 0x1B14,
    GPIO_PORT_1B_PIN_21 = 0x1B15,
    GPIO_PORT_1B_PIN_22 = 0x1B16,
    GPIO_PORT_1B_PIN_23 = 0x1B17,
    GPIO_PORT_1B_PIN_24 = 0x1B18,
    GPIO_PORT_1B_PIN_25 = 0x1B19,
    GPIO_PORT_1B_PIN_26 = 0x1B1A,
    GPIO_PORT_1B_PIN_27 = 0x1B1B,
    GPIO_PORT_1B_PIN_28 = 0x1B1C,
    GPIO_PORT_1B_PIN_29 = 0x1B1D,
    GPIO_PORT_1B_PIN_30 = 0x1B1E,
    GPIO_PORT_1B_PIN_31 = 0x1B1F,
    GPIO_PORT_2A_PIN_00 = 0x2A00,
    GPIO_PORT_2A_PIN_01 = 0x2A01,
    GPIO_PORT_2A_PIN_02 = 0x2A02,
    GPIO_PORT_2A_PIN_03 = 0x2A03,
    GPIO_PORT_2A_PIN_04 = 0x2A04,
    GPIO_PORT_2A_PIN_05 = 0x2A05,
    GPIO_PORT_2A_PIN_06 = 0x2A06,
    GPIO_PORT_2A_PIN_07 = 0x2A07,
    GPIO_PORT_2A_PIN_08 = 0x2A08,
    GPIO_PORT_2A_PIN_09 = 0x2A09,
    GPIO_PORT_2A_PIN_10 = 0x2A0A,
    GPIO_PORT_2A_PIN_11 = 0x2A0B,
    GPIO_PORT_2A_PIN_12 = 0x2A0C,
    GPIO_PORT_2A_PIN_13 = 0x2A0D,
    GPIO_PORT_2A_PIN_14 = 0x2A0E,
    GPIO_PORT_2A_PIN_15 = 0x2A0F,
    GPIO_PORT_2A_PIN_16 = 0x2A10,
    GPIO_PORT_2A_PIN_17 = 0x2A11,
    GPIO_PORT_2A_PIN_18 = 0x2A12,
    GPIO_PORT_2A_PIN_19 = 0x2A13,
    GPIO_PORT_2A_PIN_20 = 0x2A14,
    GPIO_PORT_2A_PIN_21 = 0x2A15,
    GPIO_PORT_2A_PIN_22 = 0x2A16,
    GPIO_PORT_2A_PIN_23 = 0x2A17,
    GPIO_PORT_2A_PIN_24 = 0x2A18,
    GPIO_PORT_2A_PIN_25 = 0x2A19,
    GPIO_PORT_2A_PIN_26 = 0x2A1A,
    GPIO_PORT_2A_PIN_27 = 0x2A1B,
    GPIO_PORT_2A_PIN_28 = 0x2A1C,
    GPIO_PORT_2A_PIN_29 = 0x2A1D,
    GPIO_PORT_2A_PIN_30 = 0x2A1E,
    GPIO_PORT_2A_PIN_31 = 0x2A1F,
    GPIO_PORT_2B_PIN_00 = 0x2B00,
    GPIO_PORT_2B_PIN_01 = 0x2B01,
    GPIO_PORT_2B_PIN_02 = 0x2B02,
    GPIO_PORT_2B_PIN_03 = 0x2B03,
    GPIO_PORT_2B_PIN_04 = 0x2B04,
    GPIO_PORT_2B_PIN_05 = 0x2B05,
    GPIO_PORT_2B_PIN_06 = 0x2B06,
    GPIO_PORT_2B_PIN_07 = 0x2B07,
    GPIO_PORT_2B_PIN_08 = 0x2B08,
    GPIO_PORT_2B_PIN_09 = 0x2B09,
    GPIO_PORT_2B_PIN_10 = 0x2B0A,
    GPIO_PORT_2B_PIN_11 = 0x2B0B,
    GPIO_PORT_2B_PIN_12 = 0x2B0C,
    GPIO_PORT_2B_PIN_13 = 0x2B0D,
    GPIO_PORT_2B_PIN_14 = 0x2B0E,
    GPIO_PORT_2B_PIN_15 = 0x2B0F,
    GPIO_PORT_2B_PIN_16 = 0x2B10,
    GPIO_PORT_2B_PIN_17 = 0x2B11,
    GPIO_PORT_2B_PIN_18 = 0x2B12,
    GPIO_PORT_2B_PIN_19 = 0x2B13,
    GPIO_PORT_2B_PIN_20 = 0x2B14,
    GPIO_PORT_2B_PIN_21 = 0x2B15,
    GPIO_PORT_2B_PIN_22 = 0x2B16,
    GPIO_PORT_2B_PIN_23 = 0x2B17,
    GPIO_PORT_2B_PIN_24 = 0x2B18,
    GPIO_PORT_2B_PIN_25 = 0x2B19,
    GPIO_PORT_2B_PIN_26 = 0x2B1A,
    GPIO_PORT_2B_PIN_27 = 0x2B1B,
    GPIO_PORT_2B_PIN_28 = 0x2B1C,
    GPIO_PORT_2B_PIN_29 = 0x2B1D,
    GPIO_PORT_2B_PIN_30 = 0x2B1E,
    GPIO_PORT_2B_PIN_31 = 0x2B1F,
    GPIO_PORT_3A_PIN_00 = 0x3A00,
    GPIO_PORT_3A_PIN_01 = 0x3A01,
    GPIO_PORT_3A_PIN_02 = 0x3A02,
    GPIO_PORT_3A_PIN_03 = 0x3A03,
    GPIO_PORT_3A_PIN_04 = 0x3A04,
    GPIO_PORT_3A_PIN_05 = 0x3A05,
    GPIO_PORT_3A_PIN_06 = 0x3A06,
    GPIO_PORT_3A_PIN_07 = 0x3A07,
    GPIO_PORT_3A_PIN_08 = 0x3A08,
    GPIO_PORT_3A_PIN_09 = 0x3A09,
    GPIO_PORT_3A_PIN_10 = 0x3A0A,
    GPIO_PORT_3A_PIN_11 = 0x3A0B,
    GPIO_PORT_3A_PIN_12 = 0x3A0C,
    GPIO_PORT_3A_PIN_13 = 0x3A0D,
    GPIO_PORT_3A_PIN_14 = 0x3A0E,
    GPIO_PORT_3A_PIN_15 = 0x3A0F,
    GPIO_PORT_3A_PIN_16 = 0x3A10,
    GPIO_PORT_3A_PIN_17 = 0x3A11,
    GPIO_PORT_3A_PIN_18 = 0x3A12,
    GPIO_PORT_3A_PIN_19 = 0x3A13,
    GPIO_PORT_3A_PIN_20 = 0x3A14,
    GPIO_PORT_3A_PIN_21 = 0x3A15,
    GPIO_PORT_3A_PIN_22 = 0x3A16,
    GPIO_PORT_3A_PIN_23 = 0x3A17,
    GPIO_PORT_3A_PIN_24 = 0x3A18,
    GPIO_PORT_3A_PIN_25 = 0x3A19,
    GPIO_PORT_3A_PIN_26 = 0x3A1A,
    GPIO_PORT_3A_PIN_27 = 0x3A1B,
    GPIO_PORT_3A_PIN_28 = 0x3A1C,
    GPIO_PORT_3A_PIN_29 = 0x3A1D,
    GPIO_PORT_3A_PIN_30 = 0x3A1E,
    GPIO_PORT_3A_PIN_31 = 0x3A1F
}gpio_port_pin_t;

#elif (BSP_PACKAGE_PINS == 196)

#define GPIO_MAX_PORT (GPIO_PORT_2B)
#define GPIO_MAX_PIN (GPIO_PORT_2B_PIN_25)

/* This enumerator has each available GPIO port on this MCU. This list will change depending on the MCU chosen. */
typedef enum
{
    GPIO_PORT_1A = 0x1A00u,
    GPIO_PORT_1B = 0x1B00u,
    GPIO_PORT_2A = 0x2A00u,
    GPIO_PORT_2B = 0x2B00u,
}gpio_port_t;

#define PORT_1A_SIZE (22)
#define PORT_1B_SIZE (18)
#define PORT_2A_SIZE (29)
#define PORT_2B_SIZE (26)
#define PORT_3A_SIZE (0)
#define PORT_3B_SIZE (0)

typedef enum
{
    GPIO_NO_PIN = 0x0000,
    GPIO_PORT_1A_PIN_00 = 0x1A00,
    GPIO_PORT_1A_PIN_01 = 0x1A01,
    GPIO_PORT_1A_PIN_02 = 0x1A02,
    GPIO_PORT_1A_PIN_03 = 0x1A03,
    GPIO_PORT_1A_PIN_04 = 0x1A04,
    GPIO_PORT_1A_PIN_15 = 0x1A0F,
    GPIO_PORT_1A_PIN_16 = 0x1A10,
    GPIO_PORT_1A_PIN_17 = 0x1A11,
    GPIO_PORT_1A_PIN_18 = 0x1A12,
    GPIO_PORT_1A_PIN_19 = 0x1A13,
    GPIO_PORT_1A_PIN_20 = 0x1A14,
    GPIO_PORT_1A_PIN_21 = 0x1A15,
    GPIO_PORT_1A_PIN_22 = 0x1A16,
    GPIO_PORT_1A_PIN_23 = 0x1A17,
    GPIO_PORT_1A_PIN_24 = 0x1A18,
    GPIO_PORT_1A_PIN_25 = 0x1A19,
    GPIO_PORT_1A_PIN_26 = 0x1A1A,
    GPIO_PORT_1A_PIN_27 = 0x1A1B,
    GPIO_PORT_1A_PIN_28 = 0x1A1C,
    GPIO_PORT_1A_PIN_29 = 0x1A1D,
    GPIO_PORT_1A_PIN_30 = 0x1A1E,
    GPIO_PORT_1A_PIN_31 = 0x1A1F,
    GPIO_PORT_1B_PIN_00 = 0x1B00,
    GPIO_PORT_1B_PIN_01 = 0x1B01,
    GPIO_PORT_1B_PIN_02 = 0x1B02,
    GPIO_PORT_1B_PIN_03 = 0x1B03,
    GPIO_PORT_1B_PIN_04 = 0x1B04,
    GPIO_PORT_1B_PIN_05 = 0x1B05,
    GPIO_PORT_1B_PIN_06 = 0x1B06,
    GPIO_PORT_1B_PIN_21 = 0x1B15,
    GPIO_PORT_1B_PIN_22 = 0x1B16,
    GPIO_PORT_1B_PIN_23 = 0x1B17,
    GPIO_PORT_1B_PIN_24 = 0x1B18,
    GPIO_PORT_1B_PIN_25 = 0x1B19,
    GPIO_PORT_1B_PIN_26 = 0x1B1A,
    GPIO_PORT_1B_PIN_27 = 0x1B1B,
    GPIO_PORT_1B_PIN_28 = 0x1B1C,
    GPIO_PORT_1B_PIN_29 = 0x1B1D,
    GPIO_PORT_1B_PIN_30 = 0x1B1E,
    GPIO_PORT_1B_PIN_31 = 0x1B1F,
    GPIO_PORT_2A_PIN_00 = 0x2A00,
    GPIO_PORT_2A_PIN_01 = 0x2A01,
    GPIO_PORT_2A_PIN_02 = 0x2A02,
    GPIO_PORT_2A_PIN_03 = 0x2A03,
    GPIO_PORT_2A_PIN_04 = 0x2A04,
    GPIO_PORT_2A_PIN_05 = 0x2A05,
    GPIO_PORT_2A_PIN_06 = 0x2A06,
    GPIO_PORT_2A_PIN_07 = 0x2A07,
    GPIO_PORT_2A_PIN_08 = 0x2A08,
    GPIO_PORT_2A_PIN_09 = 0x2A09,
    GPIO_PORT_2A_PIN_10 = 0x2A0A,
    GPIO_PORT_2A_PIN_11 = 0x2A0B,
    GPIO_PORT_2A_PIN_12 = 0x2A0C,
    GPIO_PORT_2A_PIN_13 = 0x2A0D,
    GPIO_PORT_2A_PIN_14 = 0x2A0E,
    GPIO_PORT_2A_PIN_15 = 0x2A0F,
    GPIO_PORT_2A_PIN_16 = 0x2A10,
    GPIO_PORT_2A_PIN_17 = 0x2A11,
    GPIO_PORT_2A_PIN_18 = 0x2A12,
    GPIO_PORT_2A_PIN_19 = 0x2A13,
    GPIO_PORT_2A_PIN_20 = 0x2A14,
    GPIO_PORT_2A_PIN_21 = 0x2A15,
    GPIO_PORT_2A_PIN_22 = 0x2A16,
    GPIO_PORT_2A_PIN_23 = 0x2A17,
    GPIO_PORT_2A_PIN_24 = 0x2A18,
    GPIO_PORT_2A_PIN_25 = 0x2A19,
    GPIO_PORT_2A_PIN_26 = 0x2A1A,
    GPIO_PORT_2A_PIN_27 = 0x2A1B,
    GPIO_PORT_2A_PIN_28 = 0x2A1C,
    GPIO_PORT_2B_PIN_00 = 0x2B00,
    GPIO_PORT_2B_PIN_01 = 0x2B01,
    GPIO_PORT_2B_PIN_02 = 0x2B02,
    GPIO_PORT_2B_PIN_03 = 0x2B03,
    GPIO_PORT_2B_PIN_04 = 0x2B04,
    GPIO_PORT_2B_PIN_05 = 0x2B05,
    GPIO_PORT_2B_PIN_06 = 0x2B06,
    GPIO_PORT_2B_PIN_07 = 0x2B07,
    GPIO_PORT_2B_PIN_08 = 0x2B08,
    GPIO_PORT_2B_PIN_09 = 0x2B09,
    GPIO_PORT_2B_PIN_10 = 0x2B0A,
    GPIO_PORT_2B_PIN_11 = 0x2B0B,
    GPIO_PORT_2B_PIN_12 = 0x2B0C,
    GPIO_PORT_2B_PIN_13 = 0x2B0D,
    GPIO_PORT_2B_PIN_14 = 0x2B0E,
    GPIO_PORT_2B_PIN_15 = 0x2B0F,
    GPIO_PORT_2B_PIN_16 = 0x2B10,
    GPIO_PORT_2B_PIN_17 = 0x2B11,
    GPIO_PORT_2B_PIN_18 = 0x2B12,
    GPIO_PORT_2B_PIN_19 = 0x2B13,
    GPIO_PORT_2B_PIN_20 = 0x2B14,
    GPIO_PORT_2B_PIN_21 = 0x2B15,
    GPIO_PORT_2B_PIN_22 = 0x2B16,
    GPIO_PORT_2B_PIN_23 = 0x2B17,
    GPIO_PORT_2B_PIN_24 = 0x2B18,
    GPIO_PORT_2B_PIN_25 = 0x2B19
}gpio_port_pin_t;

#endif /* (BSP_PACKAGE_PINS == 324) */

typedef struct
{
    uint8_t port_size;
    uint32_t port_mask;
}gpio_port_info_t;

#define NO_OF_GPIO_SUB_PORTS (2)

#define RZN1_GPIO_PORT(port) \
        ((((port) >> 12) - 1) * NO_OF_GPIO_SUB_PORTS + ((((port) >> 8)&0x0F) - 0x0A))
#define RZN1_GPIO_PIN(port_pin) \
    (((((port_pin) >> 12) - 1) * (NO_OF_GPIO_SUB_PORTS * 32)) + (((((port_pin) >> 8)&0x0F) - 0x0A) * 32) + ((port_pin) & 0xFF))

static const uint8_t rzn1_gpio_linear_pin_map[] =
{
    0, 3, 4, 9, 10, 12, 15, 16, 21, 22, 24, 27, 28, 33, 34, 36, 39, 40, 45, 46, 48, 51, 52, 57, 58, 62, 63, 64, 65, 66, 67, 68,
    1, 2, 5, 6, 7, 8, 11, 13, 14, 17, 18, 19, 20, 23, 25, 26, 29, 30, 31, 32, 35, 37, 38, 41, 42, 43, 44, 47, 49, 50, 53, 54,
    69, 70, 71, 72, 73, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
    55, 56, 59, 60, 61, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 150, 151, 152, 153, 154, 155,
    122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 156, 157, 158, 159,
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169
};

/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/
static const gpio_port_info_t GPIO_PORT_INFO[6] =
{
    {   .port_size = PORT_1A_SIZE, .port_mask = PORT_1A_MASK},
    {   .port_size = PORT_1B_SIZE, .port_mask = PORT_1B_MASK},
    {   .port_size = PORT_2A_SIZE, .port_mask = PORT_2A_MASK},
    {   .port_size = PORT_2B_SIZE, .port_mask = PORT_2B_MASK},
    {   .port_size = PORT_3A_SIZE, .port_mask = PORT_3A_MASK},
    {   .port_size = PORT_3B_SIZE, .port_mask = PORT_3B_MASK}};
/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif /* BSP_MCU_RZN1S */
#endif /* GPIO_RZN1S */
