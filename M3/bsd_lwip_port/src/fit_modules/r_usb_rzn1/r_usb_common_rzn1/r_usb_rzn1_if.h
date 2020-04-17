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
 * $Revision: 1297 $
 * $Date: 2019-02-22 17:18:43 +0000 (Fri, 22 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_rzn1_if.h
 * Description  :  USB driver API generic definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
/*
 ********************************************************************************
 * Doxygen Summary block
 **********************************************************************************************************************/
/*!
 * @defgroup USB_MODULE RZN1 USB Bare Metal Driver
 * @{
 * @file
 * @brief USB Bare Metal Driver
 * @details Supports configuring, reading and writing USB port
 * @} */
/***********************************************************************************************************************
 * End of Doxygen Summary block
 **********************************************************************************************************************/
#ifndef R_USB_RZN1_IF_H__
#define R_USB_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define USB_OK              ((USB_ER_t)(0))
#define USB_ERROR           ((USB_ER_t)(-1L))
#define USB_TRUE            (1)
#define USB_FALSE           (0)
#define USB_NULL            (0)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/*! USB Channel States */
typedef enum
{
    USB_CHANNEL_STATE_CLOSED = 0, /*!< Channel uninitialised */
    USB_CHANNEL_STATE_OPEN, /*!< CHANNEL initialised and idle */
    USB_CHANNEL_STATE_BUSY /*!< Channel connected and in use */
} USB_IF_CHANNEL_STATE_E;

typedef struct USB_UTR USB_UTR_t;

/* USB error Type */
typedef uint16_t USB_ER_t;

/* USB Standard Callback Type */
typedef void (*USB_UTR_CB_t)(USB_UTR_t *);

/* USB Class Callback Type */
typedef void (*USB_CB_t)(uint16_t);

/* Setup Structure */
typedef struct USB_SETUP
{
    uint16_t        type;           /* bRequest[b15-b8], bmRequestType[b7-b0] */
    uint16_t        value;          /* wValue */
    uint16_t        index;          /* wIndex */
    uint16_t        length;         /* wLength */
    uint16_t        devaddr;        /* Device Address */
} USB_SETUP_t;

/* Transfer Request Structure */
struct USB_UTR
{
    uint32_t        tranlen;        /* Transfer data length */
    void            *tranadr;       /* Transfer data Start address */
    USB_UTR_CB_t    complete;       /* Call Back Function Info */
    uint16_t        keyword;        /* Rootport / Pipe number / Device Address */

    union
    {
        /* USB Function */
        struct
        {
            uint16_t status; /* Status */
            uint16_t pipectr; /* Pipe control register */
        };

        /* USB Host */
        struct
        {
            USB_SETUP_t     *setup;         /* Setup packet(for control only) */
            uint16_t        msginfo;        /* Message Info for F/W */
            uint16_t        result;         /* Transfer Result */
        };
    };
};

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Global functions
 **********************************************************************************************************************/
ER_RET R_USB_Init(void);
void R_USB_GetVersion(void *buf);
void R_USBh_GetVersion(void *buf);
void R_USB_ConvertUnicodeStrDscrToAsciiStr(const uint8_t * const p_str_dscr, uint8_t * p_ascii_str);

#endif /* R_USB_RZN1_IF_H__ */
