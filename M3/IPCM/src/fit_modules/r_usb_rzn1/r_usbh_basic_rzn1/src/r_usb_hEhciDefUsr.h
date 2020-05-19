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
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * $Revision: 1814 $
 * $Date: 2020-01-23 15:43:44 +0000 (Thu, 23 Jan 2020) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hEhciDefUsr.h
 * Description  :  USB EHCI user defines
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2020. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __USB_HEHCIDEFUSR_H__
#define __USB_HEHCIDEFUSR_H__

/***********************************************************************************************************************
 User Definitions
 **********************************************************************************************************************/
#define USB_EHCI_PFL_SIZE       256             /* Periodic Frame List Size */
//#define USB_EHCI_PFL_SIZE     512
//#define USB_EHCI_PFL_SIZE     1024

#define USB_EHCI_NUM_QH         ( USB_HCI_TRREQ_NUM + USB_HCI_DEVICE_NUM )  /* The maximum number of QH memory resources */
#define USB_EHCI_NUM_QTD        2048            /* The maximum number of QTD memory resources */
#define USB_EHCI_NUM_ITD        4               /* The maximum number of ITD memory resources */
#define USB_EHCI_NUM_SITD       4               /* The maximum number of SITD memory resources */

#define USB_EHCI_ITD_DATA_SIZE  1024            /* Maximum size that can be transfered with one micro frame of ITD */

#define USB_EHCI_TIMEOUT        3000            /* Time-out setting (msec) */

#endif
