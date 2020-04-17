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
 * $Revision: 1166 $
 * $Date: 2019-01-17 14:01:52 +0000 (Thu, 17 Jan 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_common.h
 * Description  :  Common USB definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_USB_COMMON_H__
#define R_USB_COMMON_H__

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
typedef int16_t USB_ERR;

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/

/*A Setup Packet is always 8 bytes*/
#define USB_SETUP_PACKET_SIZE (8)

#ifndef NULL
#define NULL (0)
#endif

#ifndef true
#define true      (1)
#define false     (0)
#endif

/***********************************************************************************************************************
 USB Error Values
 **********************************************************************************************************************/
#define USB_ERR_OK                  ((USB_ERR)0)
#define USB_ERR_FAIL                ((USB_ERR)-1)
#define USB_ERR_PARAM               ((USB_ERR)-2)
#define USB_ERR_STATE               ((USB_ERR)-3)
#define USB_ERR_BULK_OUT            ((USB_ERR)-4)
#define USB_ERR_BULK_OUT_NO_BUFFER  ((USB_ERR)-5)
#define USB_ERR_CONTROL_OUT         ((USB_ERR)-6)
#define USB_ERR_NOT_CONNECTED       ((USB_ERR)-7)
#define USB_ERR_UNKNOWN_REQUEST     ((USB_ERR)-8)
#define USB_ERR_INVALID_REQUEST     ((USB_ERR)-9)
#define USB_ERR_CANCEL              ((USB_ERR)-10)
#define USB_ERR_BUSY                ((USB_ERR)-11)

/*BIT masks*/
#define BIT0        ((UINT32)0x00000001)    /**< bit00 */
#define BIT1        ((UINT32)0x00000002)    /**< bit01 */
#define BIT2        ((UINT32)0x00000004)    /**< bit02 */
#define BIT3        ((UINT32)0x00000008)    /**< bit03 */
#define BIT4        ((UINT32)0x00000010)    /**< bit04 */
#define BIT5        ((UINT32)0x00000020)    /**< bit05 */
#define BIT6        ((UINT32)0x00000040)    /**< bit06 */
#define BIT7        ((UINT32)0x00000080)    /**< bit07 */
#define BIT8        ((UINT32)0x00000100)    /**< bit08 */
#define BIT9        ((UINT32)0x00000200)    /**< bit09 */
#define BIT10       ((UINT32)0x00000400)    /**< bit10 */
#define BIT11       ((UINT32)0x00000800)    /**< bit11 */
#define BIT12       ((UINT32)0x00001000)    /**< bit12 */
#define BIT13       ((UINT32)0x00002000)    /**< bit13 */
#define BIT14       ((UINT32)0x00004000)    /**< bit14 */
#define BIT15       ((UINT32)0x00008000)    /**< bit15 */
#define BIT16       ((UINT32)0x00010000)    /**< bit16 */
#define BIT17       ((UINT32)0x00020000)    /**< bit17 */
#define BIT18       ((UINT32)0x00040000)    /**< bit18 */
#define BIT19       ((UINT32)0x00080000)    /**< bit19 */
#define BIT20       ((UINT32)0x00100000)    /**< bit20 */
#define BIT21       ((UINT32)0x00200000)    /**< bit21 */
#define BIT22       ((UINT32)0x00400000)    /**< bit22 */
#define BIT23       ((UINT32)0x00800000)    /**< bit23 */
#define BIT24       ((UINT32)0x01000000)    /**< bit24 */
#define BIT25       ((UINT32)0x02000000)    /**< bit25 */
#define BIT26       ((UINT32)0x04000000)    /**< bit26 */
#define BIT27       ((UINT32)0x08000000)    /**< bit27 */
#define BIT28       ((UINT32)0x10000000)    /**< bit28 */
#define BIT29       ((UINT32)0x20000000)    /**< bit29 */
#define BIT30       ((UINT32)0x40000000)    /**< bit30 */
#define BIT31       ((UINT32)0x80000000)    /**< bit31 */

#define CDC_DATA_LEN    (512)     /* MAX USB packet data size */
#define ALIGN_SIZE      (0x20)    /* 32Byte */

#endif /* R_USB_COMMON_H__ */
