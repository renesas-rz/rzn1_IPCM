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
 * $Revision: 1794 $
 * $Date: 2019-12-19 15:18:01 +0000 (Thu, 19 Dec 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_pcdc_if.h
 * Description  :  Interface file for USB PCDC API
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef _USB_PCDC_IF_H
#define _USB_PCDC_IF_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "platform.h"
#include "r_usb_pcdc_config.h"
#include "r_usbf_basic_rzn1_if.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/* Class Notification Serial State */
typedef struct st_unist
{
    union
    {
        unsigned long WORD;
        struct
        {
            /* DCD signal */
            uint16_t bRxCarrier :1;
            /* DSR signal */
            uint16_t bTxCarrier :1;
            /* State of break detection mechanism of the device */
            uint16_t bBreak :1;
            /* State of ring signal detection of the device */
            uint16_t bRingSignal :1;
            /* Framing error */
            uint16_t bFraming :1;
            /* Parity error */
            uint16_t bParity :1;
            /* Over Run error */
            uint16_t bOverRun :1;
            /* reserve */
            uint16_t rsv :9;
        } BIT;

    } u_USB_SCI_SerialState;

} USB_SCI_SerialState_t;

typedef struct
{
    /* Data terminal rate, in bits per second */
    uint32_t dwDTERate;
    /* Stop bits */
    uint8_t bCharFormat;
    /* Parity */
    uint8_t bParityType;
    /* Data bits */
    uint8_t bDataBits;
    /* reserve */
    uint8_t rsv;
} USB_PCDC_LineCoding_t; /* note: make sure is 32-bit aligned */

typedef struct
{
    /* DTR */
    uint16_t bDTR :1;
    /* RTS */
    uint16_t bRTS :1;
    /* reserve */
    uint16_t rsv :14;
} USB_PCDC_ControlLineState_t;

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
extern void R_usb_pcdc_SendData(uint8_t *Table, uint32_t size,
        USB_UTR_CB_t complete);
extern void R_usb_pcdc_ReceiveData(uint8_t *Table, uint32_t size,
        USB_UTR_CB_t complete);
extern void R_usb_pcdc_SerialStateNotification(
        USB_SCI_SerialState_t serial_state, USB_UTR_CB_t complete);
extern void R_usb_pcdc_ctrltrans(USB_REQUEST_t *preq, uint16_t ctsq);

#endif /* _USB_PCDC_IF_H */
