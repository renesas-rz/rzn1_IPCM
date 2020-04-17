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
 * $Revision: 1318 $
 * $Date: 2019-03-01 16:17:33 +0000 (Fri, 01 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hhub_rzn1_if.h
 * Description  :  USB Host HUB Interface File
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __R_USBH_HUB_RZN1_IF_H__
#define __R_USBH_HUB_RZN1_IF_H__

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_usb_basic_if.h"

/***********************************************************************************************************************
 Constant macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Enumerated Types
 **********************************************************************************************************************/
typedef enum
{
    EVENT_HHUB_NONE,
    EVENT_HHUB_CONFIGURED,
    EVENT_HHUB_DETACH,
    EVENT_HHUB_DEVICE_ATTACH,
    EVENT_HHUB_DEVICE_DETACH,
}
EVENT_HHUB_t;

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
typedef void (* USB_HHUB_CB_t)(uint16_t devadr, EVENT_HHUB_t event, const void * data, uint16_t length);

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/
void        R_USB_HHUB_Registration(USB_HCDREG_t *callback);
void        R_USB_HHUB_Task(void);
ER_RET      R_USB_HHUB_RegisterCallback(USB_HHUB_CB_t hub_callback);

#endif  /* __R_USBH_HUB_RZN1_IF_H__ */