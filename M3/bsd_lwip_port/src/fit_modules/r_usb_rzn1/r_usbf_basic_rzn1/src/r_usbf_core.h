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
 * FILE         :  r_usbf_core.h
 * Description  :  The USB core sits above the HAL in the USB stack.
 *                 Initialises the HAL.
 *                 Handles standard setup packets.
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef USB_CORE_H
#define USB_CORE_H

/***********************************************************************************************************************
 User Includes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/

/* Descriptor Types */
#define DESCRIPTOR_DEVICE                       (1)
#define DESCRIPTOR_CONFIGURATION                (2)
#define DESCRIPTOR_STRING                       (3)
#define DESCRIPTOR_DEVICE_QUALIFIER             (6)
#define DESCRIPTOR_OTHER_SPEED_CONFIGURATION    (7)

/*Setup Packet bmRequest d6..5 values */
#define REQUEST_STANDARD    (0)
#define REQUEST_CLASS       (1)
#define REQUEST_VENDOR      (2)

/*String Descriptor Types*/
#define STRING_iMANUFACTURER    (1)
#define STRING_iPRODUCT         (2)
/*0 means serial number is not supported*/
#define STRING_iSERIAL          (0)

/*Macros used to extract bits from bmRequest byte in the USB_SetupPacket*/
/*NOTE: Not using bitfields for bmRequest as bit order is nor ANSI defined
 and therefore can cause portability issues.*/
#define EXTRACT_bmRequest_RECIPIENT(bmRequest)   ((uint8_t)((bmRequest) & 0x1F))       /*Recipient*/
#define EXTRACT_bmRequest_TYPE(bmRequest)        ((uint8_t)(((bmRequest) >> 5) & 0x3)) /*Type*/
#define EXTRACT_bmRequest_DIRECTION(bmRequest)   ((uint8_t)(((bmRequest) >> 7) & 0x1)) /*Direction*/

/***********************************************************************************************************************
 Type Definitions
 **********************************************************************************************************************/

/*Setup packet */
typedef struct USB_SetupPacket
{
    /* Request feature */
    uint8_t bmRequest;
    /* Request number */
    uint8_t bRequest;
    /* Field that varies according to request */
    uint16_t wValue;
    /* Field that varies according to request;
     Typically used to pass an index or offset*/
    uint16_t wIndex;
    /* Number of bytes to transfer if there is a Data Stage */
    uint16_t wLength;
} USB_SetupPacket;

/***********************************************************************************************************************
 Function Prototypes
 **********************************************************************************************************************/
USB_ERR R_USBCORE_Init(void);

void usb_pstd_BusReset(void);
void usb_pstd_InitConnect(void);
void usb_pstd_AttachProcess(void);
void usb_pstd_DetachProcess(void);
void usb_pstd_SuspendProcess(void);
void usb_pstd_ResumeProcess(void);

/* r_usb_pStdRequest.c */
void usb_pstd_StandReq0(void);
void usb_pstd_StandReq1(void);
void usb_pstd_StandReq2(void);
void usb_pstd_StandReq3(void);
void usb_pstd_StandReq4(void);
void usb_pstd_StandReq5(void);
void usb_pstd_SetFeatureFunction(void);

#endif /*USB_CORE_H*/
