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
 * FILE         :  r_usb_hHciLocal.h
 * Description  :  USB HCI local
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __USB_HHCILOCAL_H__
#define __USB_HHCILOCAL_H__

#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "iodefine.h"
#include "r_usb_hHci.h"
#include "r_usb_hEhciDefUsr.h"
#include "r_usb_hEhciTypedef.h"
#include "r_usb_hEhciExtern.h"
#include "r_usb_hOhciDefUsr.h"
#include "r_usb_hOhciTypedef.h"
#include "r_usb_hOhciExtern.h"

//#define USB_DEBUG_HCI

#ifndef NULL
#define NULL                    0
#endif
#ifndef FALSE
#define FALSE                   0
#endif
#ifndef TRUE
#define TRUE                    1
#endif

#define USB_HCI_NONCACHE_ADDR(x)        (x)
#define USB_HCI_CACHE_ADDR(x)           (x)

#define USB_PID                 (0x0003u)   /* b1-0: Response PID */
#define USB_PID_STALL           (0x0002u)   /* STALL */
#define USB_PID_BUF             (0x0001u)   /* BUF */
#define USB_PID_NAK             (0x0000u)   /* NAK */

/***********************************************************************************************************************
 Definitions for HCI Common
 **********************************************************************************************************************/
/* Type of HCI task */
enum Usb_Hci_Task_Enum_Type {
    USB_HCI_TASK,
    USB_HCI_TASK_MAX
};

/* Type of HCI task message */
enum Usb_Hci_Mess_Enum_Type {
    USB_HCI_MESS_EHCI_USBINT,                       /* EHCI Interrupt on complete message */
    USB_HCI_MESS_EHCI_USBERRINT,                    /* EHCI Error Interrupt message */
    USB_HCI_MESS_EHCI_PORT_CHANGE_DETECT,           /* EHCI Port Change Detect message */
    USB_HCI_MESS_EHCI_FRAME_LIST_ROLLOVER,          /* EHCI Frame List Rollover message */
    USB_HCI_MESS_EHCI_HOST_SYSTEM_ERROR,            /* EHCI Host System Error message */
    USB_HCI_MESS_EHCI_INTERRUPT_ON_ASYNC_ADVANCE,   /* EHCI Interrupt on Asnc Advance message */
    USB_HCI_MESS_OHCI_INT,                          /* OHCI Interrupt message */
    USB_HCI_MESS_OHCI_CONTROL_ROOTHUB,              /* OHCI Control Roothub message */
    USB_HCI_MESS_PORT_RESET_REQUEST,                /* Port Reset Request message */
    USB_HCI_MESS_MAKE_TRANSFER_REQUEST,             /* Transfer Request message */
    USB_HCI_MESS_DISCONNECT_REQUEST,                /* Disconnect Request message */
    USB_HCI_MESS_CANCEL_TRANSFER_REQUEST_S,         /* Cancel Transfer Request for System task */
    USB_HCI_MESS_CANCEL_TRANSFER_REQUEST_T,         /* Cancel Transfer Request for Transfer task */
    USB_HCI_MESS_MAX
};

#ifdef USB_DEBUG_HCI
#define USB_HCI_PRINTF0(FORM)           printf("\033[36m"FORM"\033[0m")
#define USB_HCI_PRINTF1(FORM,x)         printf("\033[36m"FORM"\033[0m",x)
#define USB_HCI_PRINTF2(FORM,x,y)       printf("\033[36m"FORM"\033[0m",x,y)
#define USB_HCI_PRINTF3(FORM,x,y,z)     printf("\033[36m"FORM"\033[0m",x,y,z)
#define USB_HCI_PRINTF0_R(FORM)         printf("\033[31m"FORM"\033[0m")
#define USB_HCI_PRINTF1_R(FORM,x)       printf("\033[31m"FORM"\033[0m",x)
#define USB_HCI_PRINTF2_R(FORM,x,y)     printf("\033[31m"FORM"\033[0m",x,y)
#define USB_HCI_PRINTF3_R(FORM,x,y,z)   printf("\033[31m"FORM"\033[0m",x,y,z)
#define USB_HCI_PRINTF0_G(FORM)         printf("\033[32m"FORM"\033[0m")
#define USB_HCI_PRINTF1_G(FORM,x)       printf("\033[32m"FORM"\033[0m",x)
#define USB_HCI_PRINTF2_G(FORM,x,y)     printf("\033[32m"FORM"\033[0m",x,y)
#define USB_HCI_PRINTF3_G(FORM,x,y,z)   printf("\033[32m"FORM"\033[0m",x,y,z)
#define USB_HCI_PRINTF0_Y(FORM)         printf("\033[33m"FORM"\033[0m")
#define USB_HCI_PRINTF1_Y(FORM,x)       printf("\033[33m"FORM"\033[0m",x)
#define USB_HCI_PRINTF2_Y(FORM,x,y)     printf("\033[33m"FORM"\033[0m",x,y)
#define USB_HCI_PRINTF3_Y(FORM,x,y,z)   printf("\033[33m"FORM"\033[0m",x,y,z)
#else
#define USB_HCI_PRINTF0(FORM)
#define USB_HCI_PRINTF1(FORM,x)
#define USB_HCI_PRINTF2(FORM,x,y)
#define USB_HCI_PRINTF3(FORM,x,y,z)
#define USB_HCI_PRINTF0_R(FORM)
#define USB_HCI_PRINTF1_R(FORM,x)
#define USB_HCI_PRINTF2_R(FORM,x,y)
#define USB_HCI_PRINTF3_R(FORM,x,y,z)
#define USB_HCI_PRINTF0_G(FORM)
#define USB_HCI_PRINTF1_G(FORM,x)
#define USB_HCI_PRINTF2_G(FORM,x,y)
#define USB_HCI_PRINTF3_G(FORM,x,y,z)
#define USB_HCI_PRINTF0_Y(FORM)
#define USB_HCI_PRINTF1_Y(FORM,x)
#define USB_HCI_PRINTF2_Y(FORM,x,y)
#define USB_HCI_PRINTF3_Y(FORM,x,y,z)
#endif

/***********************************************************************************************************************
 TypeDefs for USB Common
 **********************************************************************************************************************/
typedef struct USB_HCI_DESCRIPTOR_HEADER_tag {
    uint8_t     bLength;
    uint8_t     bDescriptorType;
} USB_HCI_DESCRIPTOR_HEADER;


/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
// function
extern void                 usb_hstd_HciSendMessageFromInt(int32_t task_no, int8_t message, uint32_t data);
extern USB_HCI_DEVICE      *usb_hstd_HciAllocDevinfo(void);
extern void                 usb_hstd_HciFreeDevinfo(uint32_t devadd);
extern uint32_t             usb_hstd_HciGetPollrate(USB_HCI_TR_REQ *tr_req);
extern void                 usb_hstd_HciLockResouce(void);
extern void                 usb_hstd_HciUnlockResouce(void);

extern void                 r_usb_hstd_HciWaitTime( uint32_t waittime );

// data
extern USB_HCI_TR_REQ   usb_ghstd_HciTransferRequest[ USB_HCI_TRREQ_NUM ];
extern USB_HCI_CB_INFO  usb_ghstd_HciCallback;

#endif  /* #ifndef __USB_HHCILOCAL_H__ */
