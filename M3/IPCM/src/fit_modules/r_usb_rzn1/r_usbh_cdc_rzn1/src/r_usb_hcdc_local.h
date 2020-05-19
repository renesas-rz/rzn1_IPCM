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
 * FILE         :  r_usb_hcdc_local.h
 * Description  :  USB Host CDC header file
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __R_USB_HCDC_LOCAL_H__
#define __R_USB_HCDC_LOCAL_H__

/***********************************************************************************************************************
 Enumerated Types
 **********************************************************************************************************************/
/* Host CDC Task Command */
typedef enum
{
    USB_HCDC_TCMD_OPEN,
    USB_HCDC_TCMD_SEND,
    USB_HCDC_TCMD_RECEIVE,
    USB_HCDC_TCMD_CLASS_REQ,
    USB_HCDC_TCMD_CLASS_NOTIFY,
    USB_HCDC_TCMD_SEND_CB,
    USB_HCDC_TCMD_RECEIVE_CB,
    USB_HCDC_TCMD_CLASS_REQ_CB,
    USB_HCDC_TCMD_CLASS_NOTIFY_CB,
} USB_HCDC_TCMD_t;

/* Abstract Control Model Requests */
typedef enum
{
    /* Request Code define */
    USB_HCDC_NULL,
    USB_HCDC_SEND_ENCAPSULATED_COMMAND,
    USB_HCDC_GET_ENACAPSULATED_RESPONSE,
    USB_HCDC_SET_COMM_FEATURE,
    USB_HCDC_GET_COMM_FEATURE,
    USB_HCDC_CLR_COMM_FEATURE,
    USB_HCDC_SET_LINE_CODING,
    USB_HCDC_GET_LINE_CODING,
    USB_HCDC_SET_CONTROL_LINE_STATE,
    USB_HCDC_SEND_BREAK,
} USB_HCDC_ABS_Req_t;

/***********************************************************************************************************************
 Constant macro definitions
 **********************************************************************************************************************/
/* Line Coding Structure Length */
#define     USB_HCDC_LINE_CODING_STR_LEN    7
/* CDC Transfer data size */
#define     USB_HCDC_TR_DATA_SIZE           64

/***********************************************************************************************************************
 Struct definition
 **********************************************************************************************************************/
/* Class Request Parameter */
typedef union
{
    USB_HCDC_LineCoding_t           *LineCoding;
    USB_HCDC_ControlLineState_t     ControlLineState;
    uint16_t                        breakPeriodMs;
} USB_HCDC_ClassRequestParm_t;

/* Class Request Structure */
typedef struct
{
    uint16_t                        devadr;
    USB_HCDC_ABS_Req_t              bRequestCode;
    uint16_t                        selector;       /* Feature Selector */
    USB_HCDC_ClassRequestParm_t     parm;           /* Parameter */
    USB_UTR_CB_t                    complete;       /* Callback Function */
} USB_HCDC_ClassRequest_UTR_t;

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/
extern  USB_HCDC_ClassRequest_UTR_t usb_ghcdc_cls_req;
extern  uint8_t                    *usb_ghcdc_device_table;
extern  uint16_t                    usb_ghcdc_devaddr;

extern void        usb_hcdc_task(void);
extern USB_ER_t    usb_hcdc_send_message(uint16_t msginfo, uint16_t pipe_id,
                        void* tranadr, uint32_t tranlen, USB_UTR_CB_t complete);
extern const USB_HCDC_Strings_t * usb_hcdc_get_strings(void);

#endif  /* #ifndef __R_USB_HCDC_LOCAL_H__ */