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
 * FILE         :  r_usbh_basic_config.h
 * Description  :  USBh basic configuration definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __R_USBH_CONFIG_H__
#define __R_USBH_CONFIG_H__

/***********************************************************************************************************************
 Macro definitions (USER DEFINE)
 **********************************************************************************************************************/
#define USB_HOST_INT_PRIORITY                   (9u)

/* HCI Task */
#define USB_HCI_TSK        USB_TID_0             /* Task ID */
#define USB_HCI_MBX        USB_HCI_TSK           /* Mailbox ID */
#define USB_HCI_MPL        USB_HCI_TSK           /* Memorypool ID */
/* Host Manager Task */
#define USB_MGR_TSK        USB_TID_1             /* Task ID */
#define USB_MGR_MBX        USB_MGR_TSK           /* Mailbox ID */
#define USB_MGR_MPL        USB_MGR_TSK           /* Memorypool ID */
/* Hub Task */
#define USB_HUB_TSK        USB_TID_2             /* Task ID */
#define USB_HUB_MBX        USB_HUB_TSK           /* Mailbox ID */
#define USB_HUB_MPL        USB_HUB_TSK           /* Memorypool ID */
/* Select Device MAX */
#define USB_MAXDEVADDR      (12u)
/* Maximum Task ID +1 */
#define USB_IDMAX           11u
/* Maximum Priority number +1 */
#define USB_PRIMAX          8u
/* Maximum block */
#define USB_BLKMAX          20u
/* Maximum priority table */
#define USB_TABLEMAX        USB_BLKMAX
/* Select PIPE NUM */
#define USB_MAXPIPE         32u

/* defined: Host COMPLIANCE mode, undefined: Host NORMAL mode */
//#define USB_HOST_COMPLIANCE_MODE

#ifdef USB_HOST_COMPLIANCE_MODE
    #define USB_COMPLIANCE_DISP(data1, data2)
#endif /* USB_HOST_COMPLIANCE_MODE */

#define USB_OVERCURRENT(rootport)

/* Output debugging message in a console of IDE. */
//#define USB_DEBUG_OUTPUT

#ifdef USB_DEBUG_OUTPUT
    #include    <stdlib.h>
    #include    <stdio.h>
    #define USB_PRINTF0(FORM)                           printf(FORM)
    #define USB_PRINTF1(FORM,x1)                        printf(FORM,x1)
    #define USB_PRINTF2(FORM,x1,x2)                     printf(FORM,x1,x2)
    #define USB_PRINTF3(FORM,x1,x2,x3)                  printf(FORM,x1,x2,x3)
    #define USB_PRINTF4(FORM,x1,x2,x3,x4)               printf(FORM,x1,x2,x3,x4)
    #define USB_PRINTF5(FORM,x1,x2,x3,x4,x5)            printf(FORM,x1,x2,x3,x4,x5)
    #define USB_PRINTF6(FORM,x1,x2,x3,x4,x5,x6)         printf(FORM,x1,x2,x3,x4,x5,x6)
    #define USB_PRINTF7(FORM,x1,x2,x3,x4,x5,x6,x7)      printf(FORM,x1,x2,x3,x4,x5,x6,x7)
    #define USB_PRINTF8(FORM,x1,x2,x3,x4,x5,x6,x7,x8)   printf(FORM,x1,x2,x3,x4,x5,x6,x7,x8)
#else
    #define USB_PRINTF0(FORM)
    #define USB_PRINTF1(FORM,x1)
    #define USB_PRINTF2(FORM,x1,x2)
    #define USB_PRINTF3(FORM,x1,x2,x3)
    #define USB_PRINTF4(FORM,x1,x2,x3,x4)
    #define USB_PRINTF5(FORM,x1,x2,x3,x4,x5)
    #define USB_PRINTF6(FORM,x1,x2,x3,x4,x5,x6)
    #define USB_PRINTF7(FORM,x1,x2,x3,x4,x5,x6,x7)
    #define USB_PRINTF8(FORM,x1,x2,x3,x4,x5,x6,x7,x8)
#endif

#endif  /* __R_USBH_CONFIG_H__ */