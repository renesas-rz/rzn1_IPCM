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
 * FILE         :  r_usb_basic_if.h
 * Description  :  Interface file for USB basic API for RZ/T1
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef _USB_BASIC_IF_H
#define _USB_BASIC_IF_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_usbh_basic_config.h"
#include "r_usb_rzn1_if.h"
#include "r_usb_cdefusbip.h"
#include "platform.h"

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/* USB message Type*/
typedef void           USB_MSG_t;
/* USB ClassCheck Callback Type */
typedef void           (*USB_CB_CHECK_t)(uint16_t**);

/* Registration Structure */
typedef struct USB_HCDREG
{
    uint16_t        rootport;       /* Root port */
    uint16_t        devaddr;        /* Device address */
    uint16_t        devstate;       /* Device state */
    uint16_t        ifclass;        /* Interface Class */
    uint16_t        *tpl;           /* Target peripheral list (Vendor ID, Product ID) */
    USB_CB_CHECK_t  classcheck;     /* Driver check */
    USB_CB_t        devconfig;      /* Device configured */
    USB_CB_t        devdetach;      /* Device detach */
    USB_CB_t        devsuspend;     /* Device suspend */
    USB_CB_t        devresume;      /* Device resume */
} USB_HCDREG_t;

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* Version Number of API. */
#define USBH_DRIVER_MAJOR_VERSION_NUMBER    (1)
#define USBH_DRIVER_MINOR_VERSION_NUMBER    (0)

/* Scheduler use define */
#define USB_TBLCLR          0u                  /* Table clear */
#define USB_CNTCLR          0u                  /* Counter clear */
#define USB_FLGCLR          0u                  /* Flag clear */
#define USB_FLGSET          1u                  /* Flag set */
#define USB_IDCLR           0xFFu               /* Priority clear */

/* Task ID define */
#define USB_TID_0           0u                  /* Task ID 0 */
#define USB_TID_1           1u                  /* Task ID 1 */
#define USB_TID_2           2u                  /* Task ID 2 */
#define USB_TID_3           3u                  /* Task ID 3 */
#define USB_TID_4           4u                  /* Task ID 4 */
#define USB_TID_5           5u                  /* Task ID 5 */
#define USB_TID_6           6u                  /* Task ID 6 */
#define USB_TID_7           7u                  /* Task ID 7 */
#define USB_TID_8           8u                  /* Task ID 8 */
#define USB_TID_9           9u                  /* Task ID 9 */
#define USB_TID_10          10u                 /* Task ID 9 */

/* Task priority define */
#define USB_PRI_0           0u                  /* Priority 0 */
#define USB_PRI_1           1u                  /* Priority 1 */
#define USB_PRI_2           2u                  /* Priority 2 */
#define USB_PRI_3           3u                  /* Priority 3 */
#define USB_PRI_4           4u                  /* Priority 4 */
#define USB_PRI_5           5u                  /* Priority 5 */
#define USB_PRI_6           6u                  /* Priority 6 */
#define USB_PRI_7           7u                  /* Priority 7 */

/* nonOS Use */
#define USB_SEQ_0           (uint16_t)0x0000    /* Sequence 0 */
#define USB_SEQ_1           (uint16_t)0x0001    /* Sequence 1 */
#define USB_SEQ_2           (uint16_t)0x0002    /* Sequence 2 */
#define USB_SEQ_3           (uint16_t)0x0003    /* Sequence 3 */
#define USB_SEQ_4           (uint16_t)0x0004    /* Sequence 4 */
#define USB_SEQ_5           (uint16_t)0x0005    /* Sequence 5 */
#define USB_SEQ_6           (uint16_t)0x0006    /* Sequence 6 */
#define USB_SEQ_7           (uint16_t)0x0007    /* Sequence 7 */
#define USB_SEQ_8           (uint16_t)0x0008    /* Sequence 8 */
#define USB_SEQ_9           (uint16_t)0x0009    /* Sequence 9 */
#define USB_SEQ_10          (uint16_t)0x000a    /* Sequence 10 */

#define R_USB_SND_MSG(ID, MESS)     R_usb_cstd_SndMsg( (uint8_t)ID, (USB_MSG_t*)MESS )
#define R_USB_WAI_MSG(ID, MESS, TM) R_usb_cstd_WaiMsg( (uint8_t)ID, (USB_MSG_t*)MESS, (uint16_t)TM )
#define R_USB_RCV_MSG(ID, MESS)     R_usb_cstd_RecMsg( (uint8_t)ID, (USB_MSG_t**)MESS )
#define R_USB_PGET_BLK(ID, BLK)     R_usb_cstd_PgetBlk( (uint8_t)ID, (USB_UTR_t**)BLK )
#define R_USB_REL_BLK(ID, BLK)      R_usb_cstd_RelBlk( (uint8_t)ID,  (USB_UTR_t*)BLK )

/***********************************************************************************************************************
 USB specification define
 **********************************************************************************************************************/

/* Standard Configuration Descriptor Offset Define */
#define USB_CON_W_TOTAL_LENGTH_L            2u      /* Total length of data returned for this configuration */
#define USB_CON_W_TOTAL_LENGTH_H            3u      /* Total length of data returned for this configuration */
#define USB_CON_B_NUM_INTERFACES            4u      /* Number of interfaces supported by this configuration */
#define USB_CON_B_CONFIGURATION_VALUE       5u      /* Configuration value */
#define USB_CON_I_CONFIGURATION             6u      /* Index of string descriptor describing this configuration */
#define USB_CON_BM_ATTRIBUTES               7u      /* Configuration characteristics */
#define USB_CON_B_MAX_POWER                 8u      /* Max power consumption of the USB device from the bus */

/* Standard Interface Descriptor Offset Define */
#define USB_IF_B_INTERFACENUMBER            2u      /* bInterfaceNumber */
#define USB_IF_B_ALTERNATESETTING           3u      /* bAlternateSetting */
#define USB_IF_B_NUMENDPOINTS               4u      /* bNumEndpoints */
#define USB_IF_B_INTERFACECLASS             5u      /* bInterfaceClass */
#define USB_IF_B_INTERFACESUBCLASS          6u      /* bInterfaceSubClass */
#define USB_IF_B_INTERFACEPROTOCOL          7u      /* bInterfacePtorocol */
#define USB_IF_I_INTERFACE                  8u      /* iInterface */

/* Standard Endpoint descriptor Offset Define */
#define USB_EP_B_EPADDRESS                  2u      /* bEndpointAddress */
#define USB_EP_B_ATTRIBUTES                 3u      /* bmAttributes */
#define USB_EP_W_MPS_L                      4u      /* wMaxPacketSize */
#define USB_EP_W_MPS_H                      5u      /* wMaxPacketSize */
#define USB_EP_B_INTERVAL                   6u      /* bInterval */

/* OTG descriptor bit define */
#define USB_OTG_HNP                         0x02u   /* HNP support */
#define USB_OTG_SRP                         0x01u   /* SRP support */

/* USB Standard request */

/* HUB CLASS REQUEST */
#define USB_HUB_CLEAR_TT_BUFFER             0x0800u
#define USB_HUB_RESET_TT                    0x0900u
#define USB_HUB_GET_TT_STATE                0x0A00u
#define USB_HUB_STOP_TT                     0x0B00u

/* HUB CLASS FEATURE SELECTER */
#define USB_HUB_C_HUB_LOCAL_POWER           0x0000u
#define USB_HUB_C_HUB_OVER_CURRENT          0x0001u
#define USB_HUB_PORT_CONNECTION             0x0000u
#define USB_HUB_PORT_ENABLE                 0x0001u
#define USB_HUB_PORT_SUSPEND                0x0002u
#define USB_HUB_PORT_OVER_CURRENT           0x0003u
#define USB_HUB_PORT_RESET                  0x0004u
#define USB_HUB_PORT_POWER                  0x0008u
#define USB_HUB_PORT_LOW_SPEED              0x0009u
#define USB_HUB_PORT_HIGH_SPEED             0x000Au
#define USB_HUB_C_PORT_CONNECTION           0x0010u
#define USB_HUB_C_PORT_ENABLE               0x0011u
#define USB_HUB_C_PORT_SUSPEND              0x0012u
#define USB_HUB_C_PORT_OVER_CURRENT         0x0013u
#define USB_HUB_C_PORT_RESET                0x0014u
#define USB_HUB_PORT_TEST                   0x0015u
#define USB_HUB_PORT_INDICATOR              0x0016u

/***********************************************************************************************************************
 USB-H/W register define
 **********************************************************************************************************************/
/* Root port */
#define USB_PORT0                           0u
#define USB_NOPORT                          0xFFFFu /* Not connect */

/* Device Addr */
#define USB_DEVICE_0                        0x0000u /* Device address 0 */
#define USB_NODEVICE                        0xF000u /* No device */

/* Device class Define  */
#define USB_NOVENDOR                        0xFFFFu /* Vendor ID nocheck */
#define USB_NOPRODUCT                       0xFFFFu /* Product ID nocheck */

/* CLS task message command */
#define USB_MSG_CLS_CHECKREQUEST            0x0201u /* nonOS */
#define USB_MSG_CLS_INIT                    0x0202u /* nonOS */
#define USB_MSG_CLS_TASK                    0x0203u /* nonOS */
#define USB_MSG_CLS_WAIT                    0x0204u /* nonOS */
#define USB_MSG_CLS_PROCESSRESULT           0x0205u /* nonOS */

#define USB_DO_GLOBAL_SUSPEND               0x0301u /* USB_MSG_HCD_SUSPEND */
#define USB_DO_GLOBAL_RESUME                0x0302u /* USB_MSG_HCD_RESUME */
#define USB_DO_CLR_STALL                    0x0303u /* USB_MSG_HCD_CLR_STALL */

/***********************************************************************************************************************
 Host Compliance Define
 **********************************************************************************************************************/
#ifdef USB_HOST_COMPLIANCE_MODE
#define USB_COMP_ATTACH                     (0x00u)
#define USB_COMP_DETACH                     (0x01u)
#define USB_COMP_TPL                        (0x02u)
#define USB_COMP_NOTTPL                     (0x03u)
#define USB_COMP_HUB                        (0x04u)
#define USB_COMP_STOP                       (0x05u)
#define USB_COMP_NOTRESP                    (0x06u)
#define USB_COMP_VID                        (0x07u)
#define USB_COMP_PID                        (0x08u)
#define USB_COMP_ERR                        (0x09u)
#endif /* USB_HOST_COMPLIANCE_MODE */

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
/* USB API (Host) */
ER_RET R_USBh_Init(void);
uint8_t R_usb_hstd_get_minor_version_num(void);
uint8_t R_usb_hstd_get_major_version_num(void);
ER_RET R_USBh_Open(void);
ER_RET R_USBh_Close(void);
void R_USBh_PollTask(void);

USB_ER_t    R_usb_hstd_TransferStart(USB_UTR_t *utr);
USB_ER_t    R_usb_hstd_TransferEnd(uint16_t pipe_id);
USB_ER_t    R_usb_hstd_DriverRegistration(USB_HCDREG_t *callback);
void        R_usb_hstd_ReturnEnuMGR(uint16_t cls_result);
USB_ER_t    R_usb_hstd_ChangeDeviceState(USB_UTR_CB_t complete, uint16_t msginfo, uint16_t member);
USB_ER_t    R_usb_hstd_SetPipe(uint16_t **table);
uint16_t    R_usb_hstd_GetPipeID(uint16_t devaddr, uint8_t type, uint8_t direction, uint8_t ifnum);
USB_ER_t    R_usb_hstd_ClearPipe(uint16_t devaddr);
USB_ER_t    R_usb_hstd_MgrOpen(void);
void        R_usb_hstd_MgrTask(void);
void        R_usb_cstd_DelayXms(uint32_t time);

/* NonOS Scheduler */
USB_ER_t    R_usb_cstd_RecMsg( uint8_t id, USB_MSG_t** mess );
USB_ER_t    R_usb_cstd_SndMsg( uint8_t id, USB_MSG_t* mess );
USB_ER_t    R_usb_cstd_WaiMsg( uint8_t id, USB_MSG_t* mess, uint16_t tm );
USB_ER_t    R_usb_cstd_PgetBlk( uint8_t id, USB_UTR_t** blk );
USB_ER_t    R_usb_cstd_RelBlk( uint8_t id,  USB_UTR_t* blk );
void        R_usb_cstd_Scheduler(void);
void        R_usb_cstd_SetTaskPri(uint8_t tasknum, uint8_t pri);
uint8_t     R_usb_cstd_CheckSchedule(void);

#endif /* _USB_BASIC_IF_H */