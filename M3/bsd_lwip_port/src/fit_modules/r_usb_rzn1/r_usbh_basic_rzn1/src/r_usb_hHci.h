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
 * FILE         :  r_usb_hHci.h
 * Description  :  USB HCI Common
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __USB_HHCI_H__
#define __USB_HHCI_H__

#include "r_usb_basic_local.h"

/***********************************************************************************************************************
 Definitions for HCI Common
 **********************************************************************************************************************/
#define USB_HCI_TRREQ_NUM              USB_MAXPIPE    /* Max Transfer Request Number */
#define USB_HCI_DEVICE_NUM             USB_MAXDEVADDR     /* Max Device Number */

#define USB_HCI_CONFIGDESC_BUFFSIZE    USB_CONFIGSIZE     /* Configuration Descriptor Buffer Size */

#define USB_HCI_HUBPORT_NUM            USB_HUBDOWNPORT    /* Hub port Number */


#define USB_HCI_HCTYPE_OHCI            (1u)    /* HCI type is OHCI */
#define USB_HCI_HCTYPE_EHCI            (2u)    /* HCI type is EHCI */

#define USB_HCI_DIRECTION_OUT          (0u)    /* Direction is output */
#define USB_HCI_DIRECTION_IN           (1u)    /* Direction is input */

#define USB_HCI_DEVSPEED_FS            (0u)    /* Full speed */
#define USB_HCI_DEVSPEED_LS            (1u)    /* Low speed */
#define USB_HCI_DEVSPEED_HS            (2u)    /* High speed */

#define USB_HCI_SETUP_DATA_SIZE        (8u)    /* SetUp data size */

#define USB_HCI_NODEVICE               (0xFF)  /* No Device Define */

#define USB_HCI_GET_ENDIAN             0       /* Endian Setting */


/***********************************************************************************************************************
 TypeDefs for USB Common
 **********************************************************************************************************************/
typedef struct USB_HCI_DEVICE_DESCRIPTOR_tag
{
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint16_t    bcdUSB;
    uint8_t     bDeviceClass;
    uint8_t     bDeviceSubClass;
    uint8_t     bDeviceProtocol;
    uint8_t     bMaxPacketSize0;
    uint16_t    idVendor;
    uint16_t    idProduct;
    uint16_t    bcdDevice;
    uint8_t     iManufacturer;
    uint8_t     iProduct;
    uint8_t     iSerialNumber;
    uint8_t     bNumConfigurations;
} USB_HCI_DEVICE_DESCRIPTOR;

typedef struct USB_HCI_CONFIG_DESCRIPTOR_tag
{
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint16_t    wTotalLength;
    uint8_t     bNumInterfaces;
    uint8_t     bConfigurationValue;
    uint8_t     iConfiguration;
    uint8_t     bmAttributes;
    uint8_t     bMaxPower;
} USB_HCI_CONFIG_DESCRIPTOR;

typedef struct USB_HCI_INTERFACE_DESCRIPTOR_tag
{
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bInterfaceNumber;
    uint8_t     bAlternateSetting;
    uint8_t     bNumEndpoints;
    uint8_t     bInterfaceClass;
    uint8_t     bInterfaceSubClass;
    uint8_t     bInterfaceProtocol;
    uint8_t     iInterface;
} USB_HCI_INTERFACE_DESCRIPTOR;

typedef struct USB_HCI_ENDPOINT_DESCRIPTOR_tag
{
    uint8_t     bLength;
    uint8_t     bDescriptorType;
    uint8_t     bEndpointAddress;
    uint8_t     bmAttributes;
    uint16_t    wMaxPacketSize;
    uint8_t     bInterval;
} USB_HCI_ENDPOINT_DESCRIPTOR;


/***********************************************************************************************************************
 TypeDefs for HCI Common
 **********************************************************************************************************************/
typedef struct USB_HCI_DEVICE_tag
{
    struct
    {
        uint32_t            devnum     : 7;                     // Device Number
        uint32_t            disconnect_req : 1;                 // Disconnect Request Flag
        uint32_t            hubaddr    : 7;                     // Hub Address
        uint32_t            sprit_flag : 1;                     // Sprit Transaction Flag
        uint32_t            hubportnum : 7;                     // Hub Port Number
        uint32_t                       : 1;
        uint32_t            hctype     : 2;                     // HCI Type
        uint32_t            devspeed   : 2;                     // Device Speed
        uint32_t                       : 3;
        uint32_t            enable     : 1;                     // Enable Flag
    } bit;
    USB_HCI_DEVICE_DESCRIPTOR   devicedesc;                     // Device Descriptor
    uint32_t                rawconfigdesc[ USB_HCI_CONFIGDESC_BUFFSIZE / 4 ];   // Configuration Descriptor Raw Data
    struct {
        uint8_t             devnum[ USB_HCI_HUBPORT_NUM ];      // Device Number for HUB down-port device
        uint8_t             devspeed[ USB_HCI_HUBPORT_NUM ];    // Device Speed for HUB down-port device
    } hubdevinfo;
    void                    *hci_device;                        // HCI Characteristic Device Information pointer
} USB_HCI_DEVICE;

typedef struct USB_HCI_TR_REQ_tag
{
    struct
    {
        uint32_t            devadrs    : 7;     // Device Address
        uint32_t            cancel_req : 1;     // Cancel Transfer Request Flag
        uint32_t            epnum      : 7;     // Endpoint Number
        uint32_t            direction  : 1;     // Direction
        uint32_t            mps        : 13;    // Max Packet Size
        uint32_t            eptype     : 2;     // Endpoint Type
        uint32_t            enable     : 1;     // Enable Flag
    } bit;
    uint32_t                status;             // Status
    USB_HCI_DEVICE          *devinfo;           // Device Information Pointer
    uint32_t                pollrate;           // Polling rate(for interrupt/isochronous transfer)
    uint32_t                *setupbuf;          // SETUP Data Pointer(for control transfer only)
    uint32_t                databuf;            // Transfer Data Buffer
    uint32_t                trsize;             // Transfer Request Size
    uint32_t                actual_size;        // Actual Transfer Size
    void                    *utr_p;             // UTR data pointer
    void                    *hci_info;          // HCI Characteristic Information pointer
} USB_HCI_TR_REQ;

typedef struct USB_HCI_CB_INFO_tag
{
    void    ( *attach_cb )( uint16_t port_no );             // Attach Call Back Function Pointer
    void    ( *detach_cb )( uint16_t port_no );             // Detach Call Back Function Pointer
    void    ( *over_current_cb )( uint16_t port_no );       // Over Current Call Back Function Pointer
    void    ( *port_reset_cb )( uint16_t port_no );         // Port Reset Call Back Function Pointer
    void    ( *tr_end_cb )( void* utr_p, uint32_t actual_size, uint16_t status ); // Transfer End Call Back Function Pointer
} USB_HCI_CB_INFO;


/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
/* function */
extern void             r_usb_hstd_HciTask(void);
extern int32_t          r_usb_hstd_HciInit(USB_HCI_CB_INFO *cb_info);
extern void             r_usb_hstd_HciDeinit(void);
extern uint16_t         r_usb_hstd_HciMakeTransferRequest(void* utr_p,
                                       void* setup,
                                       uint32_t devaddr,
                                       uint32_t epnum,
                                       uint32_t eptype,
                                       uint32_t epdir,
                                       uint32_t tranlen,
                                       uint32_t tranadr,
                                       uint32_t mps);
extern void             r_usb_hstd_HciCancelTransferRequest(uint32_t devaddr,
                                                uint32_t epnum,
                                                uint32_t eptype,
                                                uint32_t epdir);
extern void             r_usb_hstd_HciDisconnect(uint32_t devadd);
extern uint16_t         r_usb_hstd_HciGetDeviceAddressOfRootpoot(uint16_t rootport);
extern uint16_t         r_usb_hstd_HciSetDeviceAddressOfRootpoot(uint16_t rootport, uint16_t devaddr);
extern uint32_t         r_usb_hstd_HciGetDeviceSpeed(uint16_t devaddr);
extern USB_HCI_DEVICE  *r_usb_hstd_HciGetDeviceInformation(uint16_t devaddr);
extern void             r_usb_hstd_HciPortReset(uint16_t rootport);
extern void             r_usb_hstd_HciPortSuspend(uint16_t rootport);
extern void             r_usb_hstd_HciPortResume(uint16_t rootport);
extern void             r_usb_hstd_HciSetHubInfo(uint32_t hubaddr, uint32_t hubportnum, uint32_t devaddr, uint32_t devspeed);
extern void             r_usb_hstd_HciSetDeviceAddressOfHubport(uint16_t hubaddr, uint16_t devaddr);
extern void             r_usb_hstd_HciElectricalTest(uint16_t rootport, uint8_t mode);
extern void             r_usb_hstd_HciWaitTime(uint32_t ms);

#endif  /* #ifndef __USB_HHCI_H__ */
