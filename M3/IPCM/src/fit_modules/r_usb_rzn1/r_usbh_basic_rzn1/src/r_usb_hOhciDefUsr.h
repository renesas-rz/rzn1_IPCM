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
 * FILE         :  r_usb_hOhciDefUsr.h
 * Description  :  USB OHCI user defines
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __USB_HOHCIDEFUSR_H__
#define __USB_HOHCIDEFUSR_H__

/***********************************************************************************************************************
 User Definitions
 **********************************************************************************************************************/
#define USB_OHCI_NUM_ENDPOINT           ( USB_HCI_TRREQ_NUM + USB_HCI_DEVICE_NUM )  /* The maximum number of Endpoint memory */
#define USB_OHCI_NUM_ED                 ( ( USB_OHCI_ED_INTERRUPT_32ms * USB_OHCI_NUM_DEVICEDATA ) + USB_OHCI_NUM_ENDPOINT )    /* The maximum number of Endpoint Descriptor memory */
#define USB_OHCI_NUM_TD                 ( 0x100000 / USB_OHCI_MAXTDSIZE )           /* The maximum number of Transfer Descriptor memory */

#define USB_OHCI_ISO_MAXDEVICE          4                               /* The maximum number of OHCI Isochronous Device */
#define USB_OHCI_ISO_MAX_PACKET_SIZE    1023                            /* The maximum number of OHCI Isochronous Packet Size */

#define USB_OHCI_TIMEOUT                3000                            /* Time-out setting (msec) */

#endif
