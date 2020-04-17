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
 * FILE         :  r_usb_cdefusbip.h
 * Description  :  USB Definitions for IP
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __R_USB_CDEFUSBIP_H__
#define __R_USB_CDEFUSBIP_H__

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 USB specification define
 **********************************************************************************************************************/

/* Standard Device Descriptor Define */
#define USB_DEV_B_LENGTH                    (0u)      /* Size of descriptor */
#define USB_DEV_B_DESCRIPTOR_TYPE           (1u)      /* Descriptor type */
#define USB_DEV_BCD_USB_L                   (2u)      /* USB Specification Release Number */
#define USB_DEV_BCD_USB_H                   (3u)      /* USB Specification Release Number */
#define USB_DEV_B_DEVICE_CLASS              (4u)      /* Class code */
#define USB_DEV_B_DEVICE_SUBCLASS           (5u)      /* Subclass code */
#define USB_DEV_B_DEVICE_PROTOCOL           (6u)      /* Protocol code */
#define USB_DEV_B_MAX_PACKET_SIZE_0         (7u)      /* Max packet size for EP0(only 8,16,32,64 are valid) */
#define USB_DEV_ID_VENDOR_L                 (8u)      /* Vendor ID */
#define USB_DEV_ID_VENDOR_H                 (9u)      /* Vendor ID */
#define USB_DEV_ID_PRODUCT_L                (10u)     /* Product ID */
#define USB_DEV_ID_PRODUCT_H                (11u)     /* Product ID */
#define USB_DEV_BCD_DEVICE_L                (12u)     /* Device relese number */
#define USB_DEV_BCD_DEVICE_H                (13u)     /* Device relese number */
#define USB_DEV_I_MANUFACTURER              (14u)     /* Index of string descriptor describing manufacturer */
#define USB_DEV_I_PRODUCT                   (15u)     /* Index of string descriptor describing product */
#define USB_DEV_I_SERIAL_NUMBER             (16u)     /* Device serial number */
#define USB_DEV_B_NUM_CONFIGURATION         (17u)     /* Number of possible configuration */

/* Standard String Descriptor contents */
#define USB_STR_B_LENGTH                    (0u)      /* Size of descriptor */
#define USB_STR_B_DESCRIPTOR_TYPE           (1u)      /* Descriptor type  = 3*/
#define USB_STR_B_STRING_START              (2u)      /* Start of strings if refrencing as byte fields*/
#define USB_STR_W_STRING_START              (1u)      /* Start of string if referencing as 16 word field  as per string format */
#define USB_STR_MAX_LENGTH                  (255u)    /* Max size of string */

/* Standard Configuration Descriptor Define */
//#define   USB_DEV_B_LENGTH                    0u      /* Size of descriptor */
//#define   USB_DEV_B_DESCRIPTOR_TYPE           1u      /* Descriptor type */
#define USB_DEV_W_TOTAL_LENGTH_L            (2)       /* Total length of data returned for this configuration */
#define USB_DEV_W_TOTAL_LENGTH_H            (3)       /* Total length of data returned for this configuration */
#define USB_DEV_B_NUM_INTERFACES            (4)       /* Number of interfaces supported by this configuration */
#define USB_DEV_B_CONFIGURATION_VALUE       (5)       /* Configuration value */
#define USB_DEV_I_CONFIGURATION             (6)       /* Index of string descriptor describing this configuration */
#define USB_DEV_BM_ATTRIBUTES               (7)       /* Configuration characteristics */
#define USB_DEV_B_MAX_POWER                 (8)       /* Max power consumption of the USB device from the bus */

/* Descriptor type  Define */
#define USB_DT_DEVICE                       (0x01u)   /* Configuration Descriptor */
#define USB_DT_CONFIGURATION                (0x02u)   /* Configuration Descriptor */
#define USB_DT_STRING                       (0x03u)   /* Configuration Descriptor */
#define USB_DT_INTERFACE                    (0x04u)   /* Interface Descriptor */
#define USB_DT_ENDPOINT                     (0x05u)   /* Endpoint Descriptor */
#define USB_DT_DEVICE_QUALIFIER             (0x06u)   /* Device Qualifier Descriptor */
#define USB_DT_OTHER_SPEED_CONF             (0x07u)   /* Other Speed Configuration Descriptor */
#define USB_DT_INTERFACE_POWER              (0x08u)   /* Interface Power Descriptor */
#define USB_DT_OTGDESCRIPTOR                (0x09u)   /* OTG Descriptor */
#define USB_DT_HUBDESCRIPTOR                (0x29u)   /* HUB descriptor */

/* Device class Define  */
#define USB_DEVCLS_INTF                     (0x00u)   /* Class information at interface */
#define USB_DEVCLS_COMM                     (0x02u)   /* Communication Device */
#define USB_DEVCLS_HUB                      (0x90u)   /* HUB Device */
#define USB_DEVCLS_DIAG                     (0xDCu)   /* Diagnostic Device */
#define USB_DEVCLS_WIRE                     (0xE0u)   /* Wireless Controller */
#define USB_DEVCLS_APL                      (0xFEu)   /* Application-Specific */
#define USB_DEVCLS_VEN                      (0xFFu)   /* Vendor-Specific */

/* Interface class Define */
#define USB_IFCLS_NOT                       (0x00u)   /* Un corresponding Class */
#define USB_IFCLS_AUD                       (0x01u)   /* Audio Class */
#define USB_IFCLS_CDC                       (0x02u)   /* CDC Class */
#define USB_IFCLS_CDCC                      (0x02u)   /* CDC-Control Class */
#define USB_IFCLS_HID                       (0x03u)   /* HID Class */
#define USB_IFCLS_PHY                       (0x05u)   /* Physical Class */
#define USB_IFCLS_IMG                       (0x06u)   /* Image Class */
#define USB_IFCLS_PRN                       (0x07u)   /* Printer Class */
#define USB_IFCLS_MAS                       (0x08u)   /* Mass Storage Class */
#define USB_IFCLS_HUB                       (0x09u)   /* HUB Class */
#define USB_IFCLS_CDCD                      (0x0Au)   /* CDC-Data Class */
#define USB_IFCLS_CHIP                      (0x0Bu)   /* Chip/Smart Card Class */
#define USB_IFCLS_CNT                       (0x0Cu)   /* Content-Security Class */
#define USB_IFCLS_VID                       (0x0Du)   /* Video Class */
#define USB_IFCLS_DIAG                      (0xDCu)   /* Diagnostic Device */
#define USB_IFCLS_WIRE                      (0xE0u)   /* Wireless Controller */
#define USB_IFCLS_APL                       (0xFEu)   /* Application-Specific */
#define USB_IFCLS_VEN                       (0xFFu)   /* Vendor-Specific Class */

/* Endpoint Descriptor  Define */
#define USB_EP_DIRMASK                      (0x80u)   /* Endpoint direction mask [2] */
#define USB_EP_IN                           (0x80u)   /* In Endpoint */
#define USB_EP_OUT                          (0x00u)   /* Out Endpoint */
#define USB_EP_NUMMASK                      (0x0Fu)   /* Endpoint number mask [2] */
#define USB_EP_USGMASK                      (0x30u)   /* Usage type mask [2] */
#define USB_EP_SYNCMASK                     (0x0Cu)   /* Synchronization type mask [2] */
#define USB_EP_TRNSMASK                     (0x03u)   /* Transfer type mask [2] */
#define USB_EP_CNTRL                        (0x00u)   /* Control Transfer */
#define USB_EP_ISO                          (0x01u)   /* Isochronous Transfer */
#define USB_EP_BULK                         (0x02u)   /* Bulk Transfer */
#define USB_EP_INT                          (0x03u)   /* Interrupt Transfer */

/* Configuration descriptor bit define */
#define USB_CF_RESERVED                     (0x80u)   /* Reserved(set to 1) */
#define USB_CF_SELFP                        (0x40u)   /* Self Powered */
#define USB_CF_BUSP                         (0x00u)   /* Bus Powered */
#define USB_CF_RWUPON                       (0x20u)   /* Remote Wakeup ON */
#define USB_CF_RWUPOFF                      (0x00u)   /* Remote Wakeup OFF */

/* USB Standard request */

/* USB Request Type Register */
#define USB_BREQUEST            (0xFF00u)   /* b15-8: USB_BREQUEST */
#define USB_BMREQUESTTYPE       (0x00FFu)   /* b7-0: USB_BMREQUESTTYPE */
#define USB_BMREQUESTTYPEDIR    (0x0080u)   /* b7  : Data transfer direction */
#define USB_BMREQUESTTYPETYPE   (0x0060u)   /* b6-5: Type */
#define USB_BMREQUESTTYPERECIP  (0x001Fu)   /* b4-0: Recipient */

/* USB Request Value Register */
#define USB_WVALUE              (0xFFFFu)   /* b15-0: wValue */
#define USB_DT_TYPE             (0xFF00u)
#define USB_GET_DT_TYPE(v)      (((v) & USB_DT_TYPE) >> 8)
#define USB_DT_INDEX            (0x00FFu)
#define USB_CONF_NUM            (0x00FFu)
#define USB_ALT_SET             (0x00FFu)

/* USB_BREQUEST         0xFF00u(b15-8) */
#define USB_GET_STATUS                      (0x0000u)
#define USB_CLEAR_FEATURE                   (0x0100u)
#define USB_REQRESERVED                     (0x0200u)
#define USB_SET_FEATURE                     (0x0300u)
#define USB_REQRESERVED1                    (0x0400u)
#define USB_SET_ADDRESS                     (0x0500u)
#define USB_GET_DESCRIPTOR                  (0x0600u)
#define USB_SET_DESCRIPTOR                  (0x0700u)
#define USB_GET_CONFIGURATION               (0x0800u)
#define USB_SET_CONFIGURATION               (0x0900u)
#define USB_GET_INTERFACE                   (0x0A00u)
#define USB_SET_INTERFACE                   (0x0B00u)
#define USB_SYNCH_FRAME                     (0x0C00u)

/* USB_BMREQUESTTYPEDIR 0x0080u(b7) */
#define USB_HOST_TO_DEV                     (0x0000u)
#define USB_DEV_TO_HOST                     (0x0080u)

/* USB_BMREQUESTTYPETYPE    0x0060u(b6-5) */
#define USB_STANDARD                        (0x0000u)
#define USB_CLASS                           (0x0020u)
#define USB_VENDOR                          (0x0040u)

/* USB_BMREQUESTTYPERECIP   0x001Fu(b4-0) */
#define USB_DEVICE                          (0x0000u)
#define USB_INTERFACE                       (0x0001u)
#define USB_ENDPOINT                        (0x0002u)
#define USB_OTHER                           (0x0003u)

/* GET_STATUS request information */
/* Standard Device status */
#define USB_GS_BUSPOWERD                    (0x0000u)
#define USB_GS_SELFPOWERD                   (0x0001u)
#define USB_GS_REMOTEWAKEUP                 (0x0002u)

/* Endpoint status */
#define USB_GS_NOTHALT                      (0x0000u)
#define USB_GS_HALT                         (0x0001u)

/* CLEAR_FEATURE/GET_FEATURE/SET_FEATURE request information */
/* Standard Feature Selector */
#define USB_ENDPOINT_HALT                   (0x0000u)
#define USB_DEV_REMOTE_WAKEUP               (0x0001u)
#define USB_TEST_MODE                       (0x0002u)

/* GET_DESCRIPTOR/SET_DESCRIPTOR request information */
/* Standard Descriptor type */
#define USB_HUB_DESCRIPTOR                  (0x0000u)
#define USB_DEV_DESCRIPTOR                  (0x0100u)
#define USB_CONF_DESCRIPTOR                 (0x0200u)
#define USB_STRING_DESCRIPTOR               (0x0300u)
#define USB_INTERFACE_DESCRIPTOR            (0x0400u)
#define USB_ENDPOINT_DESCRIPTOR             (0x0500u)
#define USB_DEV_QUALIFIER_DESCRIPTOR        (0x0600u)
#define USB_OTHER_SPEED_CONF_DESCRIPTOR     (0x0700u)
#define USB_INTERFACE_POWER_DESCRIPTOR      (0x0800u)

/***********************************************************************************************************************
 USB-H/W register define
 **********************************************************************************************************************/
/* Device connect information */
#define USB_ATTACH                          (0x0040u)
#define USB_ATTACHL                         (0x0041u)
#define USB_ATTACHF                         (0x0042u)
#define USB_DETACH                          (0x0043u)
#define USB_CONNECT_UNCHANGED               (0x0044u)

/* Reset Handshake result */
#define USB_NOCONNECT                       (0x0000u) /* Speed undecidedness */
#define USB_HSCONNECT                       (0x00C0u) /* Hi-Speed connect */
#define USB_FSCONNECT                       (0x0080u) /* Full-Speed connect */
#define USB_LSCONNECT                       (0x0040u) /* Low-Speed connect */

/* Pipe define */
#define USB_USEPIPE                         (0x00FEu)
#define USB_PERIPIPE                        (0x00FDu)
#define USB_CLRPIPE                         (0x00FCu) /* Clear Pipe registration */
#define USB_PIPE0                           (0x0000u) /* PIPE 0 */
#define USB_PIPE1                           (0x0001u) /* PIPE 1 */
#define USB_PIPE2                           (0x0002u) /* PIPE 2 */
#define USB_PIPE3                           (0x0003u) /* PIPE 3 */
#define USB_PIPE4                           (0x0004u) /* PIPE 4 */
#define USB_PIPE5                           (0x0005u) /* PIPE 5 */
#define USB_PIPE6                           (0x0006u) /* PIPE 6 */
#define USB_PIPE7                           (0x0007u) /* PIPE 7 */
#define USB_PIPE8                           (0x0008u) /* PIPE 8 */
#define USB_PIPE9                           (0x0009u) /* PIPE 9 */
#define USB_MAX_PIPE_NO                     (9u)      /* PIPE0 ... PIPE9 */

/* Pipe configuration table define */
#define USB_EPL                             (6u)      /* Pipe configuration table length */
#define USB_TYPFIELD                        (0xC000u) /* Transfer type */
#define   USB_PERIODIC                      (0x8000u) /* Periodic pipe */
#define   USB_ISO                           (0xC000u) /* Isochronous */
#define   USB_INT                           (0x8000u) /* Interrupt */
#define   USB_BULK                          (0x4000u) /* Bulk */
#define   USB_NOUSE                         (0x0000u) /* Not configuration */
#define USB_BFREFIELD                       (0x0400u) /* Buffer ready interrupt mode select */
#define   USB_BFREON                        (0x0400u)
#define   USB_BFREOFF                       (0x0000u)
#define USB_DBLBFIELD                       (0x0200u) /* Double buffer mode select */
#define   USB_DBLBON                        (0x0200u)
#define   USB_DBLBOFF                       (0x0000u)
#define USB_CNTMDFIELD                      (0x0100u) /* Continuous transfer mode select */
#define   USB_CNTMDON                       (0x0100u)
#define   USB_CNTMDOFF                      (0x0000u)
#define USB_SHTNAKFIELD                     (0x0080u) /* Transfer end NAK */
#define   USB_SHTNAKON                      (0x0080u)
#define   USB_SHTNAKOFF                     (0x0000u)
#define USB_DIRFIELD                        (0x0010u) /* Transfer direction select */
#define   USB_DIR_H_OUT                     (0x0010u) /* HOST OUT */
#define   USB_DIR_P_IN                      (0x0010u) /* PERI IN */
#define   USB_DIR_H_IN                      (0x0000u) /* HOST IN */
#define   USB_DIR_P_OUT                     (0x0000u) /* PERI OUT */
#define   USB_BUF2FIFO                      (0x0010u) /* Buffer --> FIFO , same as USB_DIR_P_IN */
#define   USB_FIFO2BUF                      (0x0000u) /* FIFO --> buffer , same as USB_DIR_P_OUT */
#define USB_EPNUMFIELD                      (0x000Fu) /* Endpoint number select */
#define USB_MAX_EP_NO                       (USBF_MAX_EPS - 1)
#define   USB_EP0                           (0x0000u)
#define   USB_EP1                           (0x0001u)
#define   USB_EP2                           (0x0002u)
#define   USB_EP3                           (0x0003u)
#define   USB_EP4                           (0x0004u)
#define   USB_EP5                           (0x0005u)
#define   USB_EP6                           (0x0006u)
#define   USB_EP7                           (0x0007u)
#define   USB_EP8                           (0x0008u)
#define   USB_EP9                           (0x0009u)
#define   USB_EP10                          (0x000Au)
#define   USB_EP11                          (0x000Bu)
#define   USB_EP12                          (0x000Cu)
#define   USB_EP13                          (0x000Du)
#define   USB_EP14                          (0x000Eu)
#define   USB_EP15                          (0x000Fu)

#define USB_BUF_SIZE(x)                     ((uint16_t)(((x) / 64u) - 1u) << 10u)
#define USB_BUF_NUMB(x)                     (x)

#define USB_IFISFIELD                       (0x1000u) /* Isochronous in-buf flash mode */
#define   USB_IFISON                        (0x1000u)
#define   USB_IFISOFF                       (0x0000u)
#define USB_IITVFIELD                       (0x0007u) /* Isochronous interval */
#define USB_IITV_TIME(x)                    (x)

/* FIFO port & access define */
#define USB_CUSE                            (0u)  /* USB Read/Write register CPU trans */
#define USB_D0USE                           (1u)  /* D0FIFO CPU trans - unused */
#define USB_D0DMA                           (2u)  /* USB Read/Write register DMA trans */
#define USB_D1USE                           (3u)  /* D1FIFO CPU trans - unused */
#define USB_D1DMA                           (4u)  /* D1FIFO DMA trans - unused */
#define USB_CUSE2                           (5u)  /* CFIFO CPU trans (not trans count) - unused */
#define USB_D0DMA_C                         (6u)  /* D0FIFOB DMA trans - unused */
#define USB_D1DMA_C                         (7u)  /* D1FIFOB DMA trans - unused */

#define USB_FIFO_ACCESS_UNIT_4              (4u)  /* D0FIFO ACCESS BYTE */
#define USB_FIFO_ACCESS_UNIT_32             (32u) /* D0/D1FIFO ACCESS BYTE */

/***********************************************************************************************************************
 Another define
 **********************************************************************************************************************/
/* FIFO read / write result */
#define USB_FIFOERROR                       (0xFFFFu)     /* FIFO not ready */
#define USB_WRITEEND                        (0x0000u)     /* End of write (but packet may not be outputting) */
#define USB_WRITESHRT                       (0x0001u)     /* End of write (send short packet) */
#define USB_WRITING                         (0x0002u)     /* Write continues */
#define USB_READEND                         (0x0000u)     /* End of read */
#define USB_READSHRT                        (0x0001u)     /* Insufficient (receive short packet) */
#define USB_READING                         (0x0002u)     /* Read continues */
#define USB_READOVER                        (0x0003u)     /* Buffer size over */

/* Pipe define table end code */
#define USB_PDTBLEND                        (0xFFFFu) /* End of table */

/* Transfer status Type */
#define USB_CTRL_END                        (0u)
#define USB_DATA_NONE                       (1u)
#define USB_DATA_WAIT                       (2u)
#define USB_DATA_OK                         (3u)
#define USB_DATA_SHT                        (4u)
#define USB_DATA_OVR                        (5u)
#define USB_DATA_STALL                      (6u)
#define USB_DATA_ERR                        (7u)
#define USB_DATA_STOP                       (8u)
#define USB_DATA_TMO                        (9u)
#define USB_CTRL_READING                    (17u)
#define USB_CTRL_WRITING                    (18u)
#define USB_DATA_READING                    (19u)
#define USB_DATA_WRITING                    (20u)

/* Callback argument */
#define USB_NO_ARG                          (0u)

/* USB interrupt type (common)*/
#define USB_INT_UNKNOWN                     (0x0000u)
#define USB_INT_BRDY                        (0x0001u) /* buf ready */
#define USB_INT_BEMP                        (0x0002u) /* Empty/SizeErr  */
#define USB_INT_NRDY                        (0x0003u)

/* USB interrupt type (PERI)*/
#define USB_INT_VBINT                       (0x0011u)
#define USB_INT_RESM                        (0x0012u)
#define USB_INT_SOFR                        (0x0013u)
#define USB_INT_DVST                        (0x0014u)
#define USB_INT_CTRT                        (0x0015u)
#define USB_INT_ATTACH                      (0x0016u)
#define USB_INT_DETACH                      (0x0017u)

#define USB_INT_SUSPEND                     (0x0021u)
#define USB_INT_BUSRESET                    (0x0022u)
#define USB_INT_SPEEDCHG                    (0x0023u)
#define USB_INT_SOFERR                      (0x0024u)

/***********************************************************************************************************************
 USB-H/W register define
 **********************************************************************************************************************/
/* Max device */
#define USB_MAXPIPE_BULK                    (5)
#define     USB_MAXPIPE_ISO                 (2)
#define     USB_MAXPIPE_NUM                 (9)

/* DCP Max packetsize */
#define USB_MAXPFIELD                       (0x007Fu) /* Maxpacket size of DCP */

/***********************************************************************************************************************
 USB driver specification define
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Another define
 **********************************************************************************************************************/
/* Descriptor index */
#define USB_DEV_MAX_PKT_SIZE                (7u)  /* Index of bMAXPacketSize */
#define USB_DEV_NUM_CONFIG                  (17u) /* Index of bNumConfigurations */
#define USB_ALT_NO                          (255u)
#define USB_SOFT_CHANGE                     (0u)

/***********************************************************************************************************************
 Task request message type
 **********************************************************************************************************************/

#define USB_DO_REMOTEWAKEUP            (0x0155u)
#define USB_DO_DETACH                  (0x0161u)
#define USB_DO_ATTACH                  (0x0162u)
#define USB_DO_CLRSEQBIT               (0x0163u)
#define USB_DO_STALL                   (0x0164u)

#define USB_DO_DP_ENABLE               (0x0157u)
#define USB_DO_DP_DISABLE              (0x0158u)
#define USB_DO_DM_ENABLE               (0x0159u)
#define USB_DO_DM_DISABLE              (0x015Au)

#define USB_DO_D0FIFO_INT              (0x0144u)
#define USB_DO_D1FIFO_INT              (0x0145u)
#define USB_DO_RESM_INT                (0x0146u)

#endif  /* __R_USB_CDEFUSBIP_H__ */
/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
