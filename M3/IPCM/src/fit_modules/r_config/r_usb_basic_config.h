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
 * FILE         :  r_usb_basic_config.h
 * Description  :  USB Basic Config
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __R_USB_CONFIG_H__
#define __R_USB_CONFIG_H__

/***********************************************************************************************************************
 MCU separate setting
 **********************************************************************************************************************/
#define USB_INT_PRIORITY        (9u)

/* Select using DMA module */
#define USB_DMA_USE_PP          (1)   /* Used DMA module */
#define USB_DMA_NOT_USE_PP      (0)   /* No used DMA module */

#define USB_DMA_PP              (USB_DMA_NOT_USE_PP)

/* Select CPU Low Power Mode */
#define USB_LPWR_USE_PP         (1)   /* Used CPU Low power mode */
#define USB_LPWR_NOT_USE_PP     (0)   /* No used CPU Low power mode */

#define USB_CPU_LPW_PP          (USB_LPWR_USE_PP)

/* Select Debug Mode */
#define USB_DEBUG_ON_PP         (1)   /* No output the debugging message */
#define USB_DEBUG_OFF_PP        (0)   /* Output the debugging message */

#define USB_DEBUG_OUTPUT_PP     (USB_DEBUG_OFF_PP)

/* Max of string descriptor */
#define USB_STRINGNUM           (7u)

/* Function Controller max endpoints */
#define USBF_MAX_EPS            (16)

#endif  /* __R_USB_CONFIG_H__ */
/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
