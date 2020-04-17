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
 * FILE         :  r_usb_basic_local.h
 * Description  :  USB local definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef _USB_BASIC_LOCAL_H
#define _USB_BASIC_LOCAL_H

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/* !!!!! WARNING--You can not edit this file. !!!!!*/
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

#include "r_usb_basic_if.h"

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/* PIPE Information Structure */
typedef struct usb_pipe_t
{
    uint8_t         ifnum;          /* Interface Number */
    uint8_t         epnum;          /* Endpoint Number */
    uint8_t         direction;      /* Endpoint Direction */
    uint8_t         type;           /* Endpoint Type */
    uint16_t        mps;            /* Endpoint Max Packet Size */
    uint16_t        devaddr;        /* Device Address */
} USB_PIPE_t;

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* USB Device address define */
#define USB_DEVICEADDR          (1u)    /* PORT0 USB Address (1 to 10) */

/* HUB Address */
#define USB_HUBDPADDR           (USB_DEVICEADDR + 1u)

/* Descriptor size */
#define USB_DEVICESIZE          (20u)   /* Device Descriptor size */
#define USB_CONFIGSIZE          (256u)  /* Configuration Descriptor size */

/* HUB down port */
#define USB_HUBDOWNPORT         (4u)    /* HUB downport (MAX15) */

/* H/W function type */
#define USB_BIT0                (uint16_t)0x0001
#define USB_BIT1                (uint16_t)0x0002
#define USB_BIT2                (uint16_t)0x0004
#define USB_BIT3                (uint16_t)0x0008
#define USB_BIT4                (uint16_t)0x0010
#define USB_BIT5                (uint16_t)0x0020
#define USB_BIT6                (uint16_t)0x0040
#define USB_BIT7                (uint16_t)0x0080
#define USB_BIT8                (uint16_t)0x0100
#define USB_BIT9                (uint16_t)0x0200
#define USB_BIT10               (uint16_t)0x0400
#define USB_BIT11               (uint16_t)0x0800
#define USB_BIT12               (uint16_t)0x1000
#define USB_BIT13               (uint16_t)0x2000
#define USB_BIT14               (uint16_t)0x4000
#define USB_BIT15               (uint16_t)0x8000
#define USB_BITSET(x)           (uint16_t)((uint16_t)1 << (x))

#define USB_SND_MSG(ID, MESS)       usb_cstd_SndMsg( (uint8_t)ID, (USB_MSG_t*)MESS )
#define USB_WAI_MSG(ID, MESS, TM)   usb_cstd_WaiMsg( (uint8_t)ID, (USB_MSG_t*)MESS, (uint16_t)TM )
#define USB_RCV_MSG(ID, MESS)       usb_cstd_RecMsg( (uint8_t)ID, (USB_MSG_t**)MESS )
#define USB_PGET_BLK(ID, BLK)       usb_cstd_PgetBlk( (uint8_t)ID, (USB_UTR_t**)BLK )
#define USB_REL_BLK(ID, BLK)        usb_cstd_RelBlk( (uint8_t)ID,  (USB_UTR_t*)BLK )

/* USB Manager mode */
#define USB_PORTOFF                         0u      /* Disconnect(VBUSoff) */
#define USB_DETACHED                        10u     /* Disconnect(VBUSon) */
#define USB_ATTACHED                        20u     /* Disconnect(HUBdiconfigured) */
#define USB_POWERED                         30u     /* Start reset handshake */
#define USB_DEFAULT                         40u     /* Set device address */
#define USB_ADDRESS                         50u     /* Enumeration start */
#define USB_ENUMERATION                     60u     /* Wait device enumeration */
#define USB_CONFIGURED                      70u     /* Detach detected */
#define USB_SUSPENDED                       80u     /* Device suspended */
#define USB_DETACH_PROCESS                  101u    /* Wait device detach */
#define USB_SUSPENDED_PROCESS               102u    /* Wait device suspend */
#define USB_RESUME_PROCESS                  103u    /* Wait device resume */

/* USB Manager task message command */
#define USB_MSG_MGR_AORDETACH               0x0121u
#define USB_MSG_MGR_OVERCURRENT             0x0122u
#define USB_MSG_MGR_STATUSRESULT            0x0123u
#define USB_MSG_MGR_SUBMITRESULT            0x0124u

/***********************************************************************************************************************
 Public Variables
 **********************************************************************************************************************/
/* r_usb_hManager.c */
extern USB_HCDREG_t usb_ghstd_DeviceDrv[USB_MAXDEVADDR + 1u]; /* Device driver (registration) */
extern uint16_t     usb_ghstd_MgrMode[1u];        /* Manager mode */
extern uint16_t     usb_ghstd_DeviceAddr;         /* Device address */
extern uint16_t     usb_ghstd_DeviceSpeed;        /* Reset handshake result */
extern uint16_t     usb_ghstd_DeviceNum;          /* Device driver number */

extern uint16_t     usb_ghstd_DeviceDescriptor[USB_DEVICESIZE / 2u]; /* Received Device Descriptor */
extern uint16_t     usb_ghstd_ConfigurationDescriptor[USB_CONFIGSIZE / 2u]; /* Received Configuration Descriptor */
extern uint16_t     usb_ghstd_CheckEnuResult;     /* Enumeration result check */

/***********************************************************************************************************************
 Public Functions
 **********************************************************************************************************************/
/* r_usb_cScheduler.c */
USB_ER_t    usb_cstd_RecMsg( uint8_t id, USB_MSG_t** mess );
USB_ER_t    usb_cstd_SndMsg( uint8_t id, USB_MSG_t* mess );
USB_ER_t    usb_cstd_iSndMsg( uint8_t id, USB_MSG_t* mess );
USB_ER_t    usb_cstd_WaiMsg( uint8_t id, USB_MSG_t* mess, uint16_t times );
void        usb_cstd_WaitScheduler(void);
USB_ER_t    usb_cstd_PgetBlk( uint8_t id, USB_UTR_t** blk );
USB_ER_t    usb_cstd_RelBlk( uint8_t id,  USB_UTR_t* blk );
void        usb_cstd_ScheInit(void);

/* r_usb_hDriver.c */
uint16_t    usb_cstd_GetEpnum(uint16_t pipe_id);
uint16_t    usb_cstd_GetMaxPacketSize(uint16_t pipe_id);
uint16_t    usb_cstd_GetDevAddr(uint16_t pipe_id);
uint16_t    usb_hstd_GetPipeDir(uint16_t pipe_id);
uint16_t    usb_hstd_GetPipeType(uint16_t pipe_id);
void        usb_hstd_SetRootport(uint16_t devaddr, uint16_t rootport);
uint16_t    usb_hstd_GetRootport(uint16_t devaddr);
void        usb_cstd_DummyFunction(USB_UTR_t *utr);
void        usb_hstd_MgrSndMbx(uint16_t msginfo, uint16_t dat, uint16_t res);
USB_ER_t    usb_hstd_TransferStart(USB_UTR_t *utr);
USB_ER_t    usb_hstd_TransferEnd(uint16_t pipe_id);
void        usb_hstd_AorDetachCb(uint16_t rootport);
void        usb_hstd_PortResetCb(uint16_t rootport);
void        usb_hstd_OverCurrentCb(uint16_t rootport );

/* r_usb_hManager.c */
void        usb_hstd_EnumGetDescriptor(uint16_t addr, uint16_t cnt_value);
void        usb_hstd_ElectricalTestMode(uint16_t product_id, uint16_t port);
void        usb_hstd_MgrTask(void);
void        usb_hstd_SetLangId(void);
uint16_t    usb_hstd_GetStringDesc(uint16_t addr, uint16_t string, USB_UTR_CB_t complete);
USB_ER_t    usb_hstd_ClearStall(uint16_t pipe, USB_UTR_CB_t complete);

uint16_t    usb_hstd_SetFeature(uint16_t addr, uint16_t epnum, USB_UTR_CB_t complete);
uint16_t    usb_hstd_ClearFeature(uint16_t addr, uint16_t epnum, USB_UTR_CB_t complete);

#endif /* _USB_BASIC_LOCAL_H */
