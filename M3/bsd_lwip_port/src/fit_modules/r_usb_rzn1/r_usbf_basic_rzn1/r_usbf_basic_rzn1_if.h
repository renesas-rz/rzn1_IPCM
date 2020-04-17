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
 * $Revision: 1349 $
 * $Date: 2019-03-08 12:32:59 +0000 (Fri, 08 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usbf_basic_rzn1_if.h
 * Description  :  Interface file for USB basic API
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef _USB_BASIC_H
#define _USB_BASIC_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "r_usb_rzn1_if.h"
#include "platform.h"
/* Module configuration. */
#include "r_usb_basic_config.h"

/***********************************************************************************************************************
 Constant macro definitions
 **********************************************************************************************************************/
#define USB_QOVR            ((USB_ER_t)(-43L))    /* Submit overlap error */

/* Control Transfer stage */
#define USB_CS_IDST         (0x0000u)   /* Idle or setup stage */
#define USB_CS_RDDS         (0x0001u)   /* Ctrl read data stage */
#define USB_CS_RDSS         (0x0002u)   /* Ctrl read status stage */
#define USB_CS_WRDS         (0x0003u)   /* Ctrl write data stage */
#define USB_CS_WRSS         (0x0004u)   /* Ctrl write status stage */
#define USB_CS_WRND         (0x0005u)   /* Ctrl write nodata status stage */
#define USB_CS_SQER         (0x0006u)   /* Sequence error */
#define USB_CS_DISC         (0x000Fu)   /* Disconnected */

/* Data Transfer stage */
#define USB_DS_IDST         (0x0000u)   /* Idle  */
#define USB_DS_RX           (0x0010u)   /* Rx in progress */
#define USB_DS_TX           (0x0020u)   /* Tx in progress */
#define USB_DS_ER           (0x0030u)   /* Rx or Tx error */

/* Version Number of API. */
#define USB_DRIVER_MAJOR_VERSION_NUMBER    (1)
#define USB_DRIVER_MINOR_VERSION_NUMBER    (4)
/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/* USB Request Type */
typedef struct
{
    uint16_t ReqType; /* Request type */
    uint16_t ReqTypeType; /* Request type TYPE */
    uint16_t ReqTypeRecip; /* Request type RECIPIENT */
    uint16_t ReqRequest; /* Request */
    uint16_t ReqValue; /* Value */
    uint16_t ReqIndex; /* Index */
    uint16_t ReqLength; /* Length */
    uint16_t align; /* align structure on 32-bit boundary */
} USB_REQUEST_t;

/* Class request processing function type. */
typedef void (*USB_CB_TRN_t)(USB_REQUEST_t* preq, uint16_t ctsq);

/* Driver Registration */
typedef struct USB_PCDREG
{
    uint16_t **pipetbl; /* Pipe Define Table address */
    uint8_t *devicetbl; /* Device descriptor Table address */
    uint8_t *qualitbl; /* Qualifier descriptor Table address */
    uint8_t **configtbl; /* Configuration descriptor Table address */
    uint8_t **othertbl; /* Other configuration descriptor Table address */
    uint8_t **stringtbl; /* String descriptor Table address */
    USB_CB_t devdefault; /* Device default callback */
    USB_CB_t devconfig; /* Device configured callback */
    USB_CB_t devdetach; /* Device detach callback */
    USB_CB_t devsuspend; /* Device suspend callback */
    USB_CB_t devresume; /* Device resume callback */
    USB_CB_t interface; /* Interface changed callback */
    USB_CB_TRN_t ctrltrans; /* Control Transfer callback */
    uint16_t registered; /* set true when a PCD application has been registered */
} USB_PCDREG_t;

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
/* USB API (Peripheral) */
ER_RET R_USBf_Init(void);
uint8_t R_usb_pstd_get_minor_version_num(void);
uint8_t R_usb_pstd_get_major_version_num(void);

ER_RET R_USB_Open(void);
ER_RET R_USB_Close(void);
USB_ER_t R_usb_pstd_TransferStart(USB_UTR_t *ptr);
USB_ER_t R_usb_pstd_TransferEnd(uint16_t pipe);
void R_usb_pstd_ChangeDeviceState(uint16_t state, uint16_t keyword,
        USB_UTR_CB_t complete);
ER_RET R_usb_pstd_DriverRegistration(USB_PCDREG_t *registinfo);
void R_usb_pstd_driver_deregister(void);
void R_usb_pstd_SetPipeStall(uint16_t pipe);
uint16_t R_usb_pstd_ControlRead(uint32_t Bsize, uint8_t *Table);
void R_usb_pstd_ControlWrite(uint32_t Bsize, uint8_t *Table);
void R_usb_pstd_ControlEnd(uint16_t status);
void R_usb_pstd_poll(void);

#endif /* _USB_BASIC_H */
