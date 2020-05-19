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
 * FILE         :  r_usb_pcdc_local.h
 * Description  :  USB PCDC Local Header
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __R_USB_PCDC_LOCAL_H__
#define __R_USB_PCDC_LOCAL_H__

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* CDC Class Requests IDs*/
#define USB_PCDC_SET_LINE_CODING            (0x2000)
#define USB_PCDC_GET_LINE_CODING            (0x2100)
#define USB_PCDC_SET_CONTROL_LINE_STATE     (0x2200)

/* GET_LINE_CODING request wLength */
#define USB_PCDC_GET_LINE_CODING_LENGTH     (0x07)

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/
void usb_pcdc_DataTrans(uint16_t Pipe, uint32_t Size, uint8_t *Table,
        USB_UTR_CB_t complete);
void usb_pcdc_ControlTrans_idst(USB_REQUEST_t *req);
void usb_pcdc_ControlTrans_rdds(USB_REQUEST_t *req);
void usb_pcdc_ControlTrans_wrds(USB_REQUEST_t *req);
void usb_pcdc_ControlTrans_wrnd(USB_REQUEST_t *req);
void usb_pcdc_ControlTrans_rdss(USB_REQUEST_t *req);
void usb_pcdc_ControlTrans_wrss(USB_REQUEST_t *req);

#endif  /* __R_USB_PCDC_LOCAL_H__ */
/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
