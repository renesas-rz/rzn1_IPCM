/**********************************************************************************************************************
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
* $Revision: 1.00
* $Date: 2020-05-01 12:00:00 +0000 (Fri, 1 May 2020) $
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/
/********************************************************************************
Includes
********************************************************************************/
/********************************************************************************
Defines
********************************************************************************/
#define MBOX_DEVICE_MASTER_NAME "/dev/mbox"     /**< Name of master device */

/* ioctl defines */
#define MBOX_IOCTL_NUM 0x1337                   /**< magic number */
#define MBOX_IOCTL_CREATE _IOW(MBOX_IOCTL_NUM, 0, unsigned int) /**< create a new mailbox sub-device */
#define MBOX_IOCTL_TIMEOUT_SET _IOW(MBOX_IOCTL_NUM, 1, unsigned int) /**< timeout of the mailbox sub-device in ms */
#define MBOX_IOCTL_VERSION_GET _IOR(MBOX_IOCTL_NUM, 2, unsigned int *) /**< get the version of the mailbox driver as 32 bit value (higher 16 bit: major, lower 16 bit: minor) */
#define IPCM_DATA_REG_NUM 7

/********************************************************************************
Types, structs
********************************************************************************/
/********************************************************************************
Global variables
********************************************************************************/
/********************************************************************************
Externals
********************************************************************************/