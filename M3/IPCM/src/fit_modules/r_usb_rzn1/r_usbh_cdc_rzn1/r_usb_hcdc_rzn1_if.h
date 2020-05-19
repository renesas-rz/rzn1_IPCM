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
 * $Revision: 1313 $
 * $Date: 2019-03-01 12:00:55 +0000 (Fri, 01 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hcdc_rzn1_if.h
 * Description  :  USB Host CDC Interface File
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __R_USBH_CDC_RZN1_IF_H__
#define __R_USBH_CDC_RZN1_IF_H__

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_usb_hcdc_if.h"
#include "r_usb_common.h"

/***********************************************************************************************************************
 Constant macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Enumerated Types
 **********************************************************************************************************************/
typedef enum
{
    EVENT_HCDC_NONE,
    EVENT_HCDC_CONFIGURED,
    EVENT_HCDC_DETACH,
    EVENT_HCDC_CLASS_REQUEST_START,
    EVENT_HCDC_CLASS_REQUEST_COMPLETE,
    EVENT_HCDC_RD_START,
    EVENT_HCDC_RD_COMPLETE,
    EVENT_HCDC_WR_START,
    EVENT_HCDC_WR_COMPLETE,
    EVENT_HCDC_COM_NOTIFY_RD_START,
    EVENT_HCDC_COM_NOTIFY_RD_COMPLETE,
}
EVENT_HCDC_t;

typedef enum
{
    USB_HCDC_CONTROL_SET_CALLBACK,
    USB_HCDC_CONTROL_SET_CHAN_CONFIG,
    USB_HCDC_CONTROL_GET_CHAN_CONFIG,
    USB_HCDC_CONTROL_SEND_BREAK,
}
USB_HCDC_CONTROL_REQUEST_t;

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
typedef void (* USB_HCDC_CB_t)(uint16_t devadr, EVENT_HCDC_t event, const uint8_t * data, uint16_t length);

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/
void R_USB_HCDC_Init( void );
void R_USB_HCDC_InterfaceTask(void);
ER_RET R_USB_HCDC_Write(uint16_t devadr, const uint8_t * const data, size_t length);
ER_RET R_USB_HCDC_RegisterCallback(USB_HCDC_CB_t cdc_callback);
ER_RET R_USB_HCDC_Control(uint8_t devadr, USB_HCDC_CONTROL_REQUEST_t control_request, void *buf);

#endif  /* __R_USBH_CDC_RZN1_IF_H__ */