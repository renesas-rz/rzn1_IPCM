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
 * FILE         :  r_usb_hOhciMemory.c
 * Description  :  HCI Memory Control Code
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_usb_hHciLocal.h"

/***********************************************************************************************************************
 Prototype
 **********************************************************************************************************************/
/* Global function */
USB_OHCI_HCCA_BLOCK_P              usb_hstd_OhciGetHccaAddress(void);
void                                usb_hstd_OhciInitRequestMemory(void);
void                                usb_hstd_OhciInitDeviceData(void);
void                                usb_hstd_OhciClearList(void);
USB_OHCI_REQUEST_P                 usb_hstd_OhciAllocTransferRequest(void);
USB_OHCI_HCD_DEVICE_DATA_P         usb_hstd_OhciAllocDeviceData(void);
USB_OHCI_HCD_ENDPOINT_P            usb_hstd_OhciAllocEndpoint(void);
USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P usb_hstd_OhciAllocateEndpointDescriptor(void);
USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P usb_hstd_OhciAllocateTransferDescriptor(void);
USB_OHCI_ISO_INFO_P                usb_hstd_OhciAllocEndpointIso(void);
void                                usb_hstd_OhciFreeTransferRequest(USB_OHCI_REQUEST_P ohci_req);
void                                usb_hstd_OhciFreeTransferDescriptor(USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P td);
void                                usb_hstd_OhciFreeEndpoint(USB_OHCI_HCD_ENDPOINT_P endpoint);
void                                usb_hstd_OhciFreeEndpointDescriptor(USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ed);
USB_OHCI_HCD_ENDPOINT_P            usb_hstd_OhciScanEndpoint(uint8_t device_address, uint8_t endpoint_number, uint8_t direction);
void                                usb_hstd_OhciStoreEndpoint(uint8_t device_address, uint8_t endpoint_number, uint8_t direction, USB_OHCI_HCD_ENDPOINT_P endpoint);
uint32_t                            usb_hstd_OhciScanContainingRecord(USB_OHCI_LIST_ENTRY_P list, uint8_t type, uint8_t field);
uint32_t                            usb_hstd_OhciCheckRemainedTd(void);
uint32_t                            usb_hstd_OhciCheckRemainedEd(void);
uint32_t                            usb_hstd_OhciCheckRemainedEp(void);


/***********************************************************************************************************************
 Variable
 **********************************************************************************************************************/
/* static */

#ifdef __ICCARM__
#pragma location="OHCI_HCCA"
static USB_OHCI_HCCA_BLOCK                 ohci_hcca;
/* 256 byte-boundary Area */
#pragma location="OHCI_TD"
static USB_OHCI_HCD_TRANSFER_DESCRIPTOR    ohci_TdMemory[USB_OHCI_NUM_TD];    /* 32 bit-boundary Area */
#pragma location="OHCI_ED"
static USB_OHCI_HCD_ENDPOINT_DESCRIPTOR    ohci_EdMemory[USB_OHCI_NUM_ED];    /* 16 bit-boundary Area */
#endif  /* __ICCARM__ */

#ifdef __GNUC__
static USB_OHCI_HCCA_BLOCK                 ohci_hcca
        __attribute__ ((section ("OHCI_HCCA")));
/* 256 byte-boundary Area */
static USB_OHCI_HCD_TRANSFER_DESCRIPTOR    ohci_TdMemory[USB_OHCI_NUM_TD]    /* 32 bit-boundary Area */
        __attribute__ ((section ("OHCI_TD")));
static USB_OHCI_HCD_ENDPOINT_DESCRIPTOR    ohci_EdMemory[USB_OHCI_NUM_ED]    /* 16 bit-boundary Area */
        __attribute__ ((section ("OHCI_ED")));
#endif  /* __GNUC__ */


#ifdef __CC_ARM
#pragma arm section zidata = "OHCI_HCCA"
static USB_OHCI_HCCA_BLOCK                 ohci_hcca;
#pragma arm section zidata
/* 256 byte-boundary Area */
#pragma arm section zidata = "OHCI_TD"
static USB_OHCI_HCD_TRANSFER_DESCRIPTOR    ohci_TdMemory[USB_OHCI_NUM_TD];    /* 32 bit-boundary Area */
#pragma arm section zidata
#pragma arm section zidata = "OHCI_ED"
static USB_OHCI_HCD_ENDPOINT_DESCRIPTOR    ohci_EdMemory[USB_OHCI_NUM_ED];    /* 16 bit-boundary Area */
#pragma arm section zidata
#endif  /* __CC_ARM */

static uint8_t                          ohci_IsoBuffer[ USB_OHCI_ISO_MAXDEVICE ][ USB_OHCI_ISO_MAX_FRAME ][ USB_OHCI_ISO_MAX_PACKET_SIZE ];

static USB_OHCI_REQUEST                 ohci_RequestArray[ USB_OHCI_NUM_REQUEST ];
static USB_OHCI_HCD_DEVICE_DATA         ohci_DeviceDataMemory[ USB_OHCI_NUM_DEVICEDATA ];
static USB_OHCI_HCD_ENDPOINT            ohci_EndpointMemory[ USB_OHCI_NUM_ENDPOINT ];
static USB_OHCI_HCD_ENDPOINT_P          ohci_EnableEndpoint[ USB_OHCI_MAXDEVICE ][ USB_OHCI_MAXENDPOINT ][ 2 ];
static USB_OHCI_ISO_INFO                ohci_IsoEndpoint[ USB_OHCI_ISO_MAXDEVICE ];

static uint32_t                             ohci_RemainDD = USB_OHCI_NUM_DEVICEDATA;   /* Remaining DeviceData */
static uint32_t                             ohci_RemainEP = USB_OHCI_NUM_ENDPOINT;     /* Remaining Endpoint */
static uint32_t                             ohci_RemainED = USB_OHCI_NUM_ED;           /* Remaining EndpointDescriptor */
static uint32_t                             ohci_RemainTD = USB_OHCI_NUM_TD;           /* Remaining TransferDescriptor */


/***********************************************************************************************************************
 Function
 **********************************************************************************************************************/

/* Global Function */
/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciGetHccaAddress
 *
 *  Description:    OHCI Getting of HCCA Address
 *
 *  Parameters:     void
 *
 *  Return value:   USB_OHCI_HCCA_BLOCK_P ; HCCA Address pointer
 *
 **********************************************************************************************************************/
USB_OHCI_HCCA_BLOCK_P usb_hstd_OhciGetHccaAddress( void )
{
    return( &ohci_hcca );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciGetHccaAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciInitRequestMemory
 *
 *  Description:    OHCI Initialize Request-Memory
 *
 *  Parameters:     void
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciInitRequestMemory( void )
{
    usb_hstd_HciLockResouce();

    memset( &ohci_RequestArray[ 0 ], 0, sizeof( ohci_RequestArray ) );

    usb_hstd_HciUnlockResouce();
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciInitRequestMemory
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciInitDeviceData
 *
 *  Description:    OHCI Initialize Device Data Memory
 *
 *  Parameters:     void
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciInitDeviceData( void )
{
    usb_hstd_HciLockResouce();

    /*  Clear all DeviceData */
    memset( &ohci_DeviceDataMemory[ 0 ], 0, sizeof( ohci_DeviceDataMemory ) );

    usb_hstd_HciUnlockResouce();
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciInitDeviceData
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciClearList
 *
 *  Description:    OHCI Clear List
 *
 *  Parameters:     void
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciClearList( void )
{
    usb_hstd_HciLockResouce();

    /*  Clear all Endpoints */
    memset( &ohci_EndpointMemory[ 0 ], 0, sizeof( ohci_EndpointMemory ) );

    /*  Clear all EndpointDescriptors */
    memset( &ohci_EdMemory[ 0 ], 0, sizeof( ohci_EdMemory ) );

    /*  Clear all TransferDescriptors */
    memset( &ohci_TdMemory[ 0 ], 0, sizeof( ohci_TdMemory ) );

    /*  Clear ohci_EnableEndpoint[][] */
    memset( &ohci_EnableEndpoint[ 0 ], 0, sizeof( ohci_EnableEndpoint ) );

    ohci_RemainEP = USB_OHCI_NUM_ENDPOINT;
    ohci_RemainED = USB_OHCI_NUM_ED;
    ohci_RemainTD = USB_OHCI_NUM_TD;

    usb_hstd_HciUnlockResouce();
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciClearList
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciAllocTransferRequest
 *
 *  Description:    OHCI Create Transfer Request
 *
 *  Parameters:     void
 *
 *  Return value:   USB_OHCI_REQUEST_P ohci_req ; OHCI transfer request pointer
 *
 **********************************************************************************************************************/
USB_OHCI_REQUEST_P usb_hstd_OhciAllocTransferRequest( void )
{
    USB_OHCI_REQUEST_P  ohci_req;
    USB_OHCI_REQUEST_P  ret_req = NULL;
    uint32_t            n;

    usb_hstd_HciLockResouce();

    /* Allocate Request */
    ohci_req = &ohci_RequestArray[ 0 ];
    for(n = 0; n < USB_OHCI_NUM_REQUEST; n++, ohci_req++)
    {
        if(ohci_req->UsingFlag == FALSE)
        {
            memset( ohci_req, 0, sizeof( USB_OHCI_REQUEST ) );
            ohci_req->UsingFlag = TRUE;
            ret_req = ohci_req;
            break;
        }
    }

    usb_hstd_HciUnlockResouce();

    return( ret_req );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciAllocTransferRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciAllocDeviceData
 *
 *  Description:    OHCI Allocate Device Data Memory
 *
 *  Parameters:     void
 *
 *  Return value:   USB_OHCI_HCD_DEVICE_DATA_P ; Device Data Pointer
 *
 **********************************************************************************************************************/
USB_OHCI_HCD_DEVICE_DATA_P usb_hstd_OhciAllocDeviceData( void )
{
    USB_OHCI_HCD_DEVICE_DATA_P  device_data;
    USB_OHCI_HCD_DEVICE_DATA_P  ret_device_data = NULL;
    uint32_t                    n;
    uint32_t                    m;

    usb_hstd_HciLockResouce();

    /* Allocate device_data */
    device_data = &ohci_DeviceDataMemory[ 0 ];
    for(n = 0; n < USB_OHCI_NUM_DEVICEDATA; n++, device_data++)
    {
        if(device_data->UsingFlag == FALSE)
        {
            /* 0 clear */
            memset( device_data, 0, sizeof( USB_OHCI_HCD_DEVICE_DATA ) );
            ret_device_data = device_data;

            /* Initialize Device Data */
            device_data->UsingFlag = TRUE;
            device_data->AvailableBandwidth      = 0x2778;
            for(m = 0; m < USB_OHCI_MAXROOTPORTS; m++)
            {
                device_data->RootDevice[ m ] = USB_HCI_NODEVICE;
            }
            ohci_RemainDD--;
            break;
        }
    }

    usb_hstd_HciUnlockResouce();

    return( ret_device_data );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciAllocDeviceData
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciAllocEndpoint
 *
 *  Description:    OHCI Allocate Endpoint Memory
 *
 *  Parameters:     void
 *
 *  Return value:   USB_OHCI_HCD_ENDPOINT_P ; Endpoint Pointer
 *
 **********************************************************************************************************************/
USB_OHCI_HCD_ENDPOINT_P usb_hstd_OhciAllocEndpoint( void )
{
    USB_OHCI_HCD_ENDPOINT_P endpoint;
    USB_OHCI_HCD_ENDPOINT_P ret_endpoint = NULL;
    uint32_t                n;

    usb_hstd_HciLockResouce();

    /*  Allocate endpoint */
    endpoint = &ohci_EndpointMemory[ 0 ];
    for(n = 0; n < USB_OHCI_NUM_ENDPOINT; n++, endpoint++)
    {
        if(endpoint->UsingFlag == FALSE)
        {
            ret_endpoint = endpoint;

            /* Initialize Endpoint */
            memset( endpoint, 0, sizeof( USB_OHCI_HCD_ENDPOINT ) );
            endpoint->UsingFlag = TRUE;
            ohci_RemainEP--;
            break;
        }
    }

    usb_hstd_HciUnlockResouce();

    return( ret_endpoint );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciAllocEndpoint
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciAllocateEndpointDescriptor
 *
 *  Description:    OHCI Allocate EndpointDescriptor Memory
 *
 *  Parameters:     void
 *
 *  Return value:   USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ; Endpoint Descriptor Pointer
 *
 **********************************************************************************************************************/
USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P usb_hstd_OhciAllocateEndpointDescriptor( void )
{
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  ed;
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  ret_ed = NULL;
    uint32_t                            i;

    usb_hstd_HciLockResouce();

    /* Allocate EndpointDescriptor */
    ed = &ohci_EdMemory[ 0 ];
    for(i = 0; i < USB_OHCI_NUM_ED; i++, ed++)
    {
        if(ed->UsingFlag == FALSE)
        {
            ret_ed = ed;

            /* Initialize EndpointDescriptor */
            memset( ed, 0, sizeof( USB_OHCI_HCD_ENDPOINT_DESCRIPTOR ) );
            ed->UsingFlag = TRUE;
            ohci_RemainED--;
            break;
        }
    }

    usb_hstd_HciUnlockResouce();

    return( ret_ed );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciAllocateEndpointDescriptor
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciAllocateTransferDescriptor
 *
 *  Description:    OHCI Allocate TransferDescriptor Memory
 *
 *  Parameters:     void
 *
 *  Return value:   USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P ; Transfer Descriptor Pointer
 *
 **********************************************************************************************************************/
USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P usb_hstd_OhciAllocateTransferDescriptor( void )
{
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P  td;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P  ret_td = NULL;
    uint32_t                            i;

    usb_hstd_HciLockResouce();

    /* Allocate TransferDescriptor */
    td = &ohci_TdMemory[ 0 ];
    for(i = 0; i < USB_OHCI_NUM_TD; i++, td++)
    {
        if(td->UsingFlag == FALSE)
        {
            ret_td = td;

            /* Initialize TransferDescriptor */
            memset( td, 0, sizeof( USB_OHCI_HCD_TRANSFER_DESCRIPTOR ) );
            td->UsingFlag = TRUE;
            ohci_RemainTD--;
            break;
        }
    }

    usb_hstd_HciUnlockResouce();

    return( ret_td );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciAllocateTransferDescriptor
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciAllocEndpointIso
 *
 *  Description:    OHCI Allocate Iso Endpoint
 *
 *  Parameters:     void
 *
 *  Return value:   USB_OHCI_ISO_INFO_P ; Iso Endpoint pointer
 *
 **********************************************************************************************************************/
USB_OHCI_ISO_INFO_P usb_hstd_OhciAllocEndpointIso( void )
{
    USB_OHCI_ISO_INFO_P ret_iso_info = NULL;
    USB_OHCI_ISO_INFO_P iso_info;
    uint32_t            n;
    uint32_t            i;

    usb_hstd_HciLockResouce();

    iso_info = &ohci_IsoEndpoint[ 0 ];
    for(n = 0; n < USB_OHCI_ISO_MAXDEVICE; n++, iso_info++)
    {
        if(iso_info->UsingFlag == FALSE)
        {
            memset( iso_info, 0, sizeof( USB_OHCI_ISO_INFO ) );
            for(i = 0; i < USB_OHCI_ISO_MAX_FRAME; i++)
            {
                iso_info->TransferInfo[ i ].Buffer = &ohci_IsoBuffer[ n ][ i ][ 0 ];
            }
            iso_info->UsingFlag = TRUE;
            ret_iso_info = iso_info;
            break;
        }
    }

    usb_hstd_HciUnlockResouce();

    return( ret_iso_info );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciAllocEndpointIso
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciFreeTransferRequest
 *
 *  Description:    OHCI Free Transfer Request
 *
 *  Parameters:     USB_OHCI_REQUEST_P ohci_req ; OHCI transfer request pointer
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciFreeTransferRequest( USB_OHCI_REQUEST_P ohci_req )
{
    usb_hstd_HciLockResouce();

    memset( ohci_req, 0, sizeof( USB_OHCI_REQUEST ) );

    usb_hstd_HciUnlockResouce();
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciFreeTransferRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciFreeTransferDescriptor
 *
 *  Description:    OHCI Free TransferDescriptor Memory
 *
 *  Parameters:     USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P ; Transfer Descriptor Pointer
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciFreeTransferDescriptor( USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P td )
{
    if(td == NULL)
    {
        return;
    }

    usb_hstd_HciLockResouce();

    if(td->UsbdRequest->HcdList.Flink == &td->RequestList)
    {
        /* Removing TD is located in head of the HcdList */
        td->UsbdRequest->HcdList.Flink = td->UsbdRequest->HcdList.Flink->Flink;
    }
    else if(td->UsbdRequest->HcdList.Blink == &td->RequestList)
    {
        /* Removing TD is located in tail of the HcdList */
        td->UsbdRequest->HcdList.Blink = td->UsbdRequest->HcdList.Blink->Blink;
    }

    /* clear */
    memset( td, 0, sizeof( USB_OHCI_HCD_TRANSFER_DESCRIPTOR ) );

    ohci_RemainTD++;

    usb_hstd_HciUnlockResouce();
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciFreeTransferDescriptor
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciFreeEndpoint
 *
 *  Description:    OHCI Free Endpoint
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P ; endpoint pointer
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciFreeEndpoint( USB_OHCI_HCD_ENDPOINT_P endpoint )
{
    if((endpoint->HcdHeadP != NULL) && (endpoint->HcdHeadP == endpoint->HcdTailP))
    {
        /* Remove NullTD (if remained) */
        usb_hstd_OhciFreeTransferDescriptor( endpoint->HcdHeadP );
    }

    usb_hstd_HciLockResouce();

    if(endpoint->IsoInfo != NULL)
    {
        endpoint->IsoInfo->UsingFlag = FALSE;
    }

    memset( endpoint, 0, sizeof( USB_OHCI_HCD_ENDPOINT ) );

    ohci_RemainEP++;

    usb_hstd_HciUnlockResouce();
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciFreeEndpoint
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciFreeEndpointDescriptor
 *
 *  Description:    OHCI Free Endpoint Descriptor
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ed ; Endpoint Descriptor Pointer
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciFreeEndpointDescriptor( USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ed )
{
    usb_hstd_OhciFreeEndpoint( ed->Endpoint );

    usb_hstd_HciLockResouce();

    memset( ed, 0 , sizeof( USB_OHCI_HCD_ENDPOINT_DESCRIPTOR ) );

    ohci_RemainED++;

    usb_hstd_HciUnlockResouce();
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciFreeEndpointDescriptor
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciScanEndpoint
 *
 *  Description:    OHCI Scan Endpoint info.
 *
 *  Parameters:     uint8_t device_address  ; device address
 *                  uint8_t endpoint_number ; endpoint no
 *                  uint8_t direction       ; direction
 *
 *  Return value:   USB_OHCI_HCD_ENDPOINT_P ; endpoint pointer
 *
 **********************************************************************************************************************/
USB_OHCI_HCD_ENDPOINT_P usb_hstd_OhciScanEndpoint( uint8_t device_address, uint8_t endpoint_number, uint8_t direction )
{
    return( ohci_EnableEndpoint[ device_address ][ endpoint_number ][ direction ] );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciScanEndpoint
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciStoreEndpoint
 *
 *  Description:    OHCI Store Endpoint info.
 *
 *  Parameters:     uint8_t device_address  ; device address
 *                  uint8_t endpoint_number ; endpoint no
 *                  uint8_t direction       ; direction
 *                  USB_OHCI_HCD_ENDPOINT_P ; endpoint pointer
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciStoreEndpoint( uint8_t device_address, uint8_t endpoint_number, uint8_t direction, USB_OHCI_HCD_ENDPOINT_P endpoint )
{
    ohci_EnableEndpoint[ device_address ][ endpoint_number ][ direction ] = endpoint;
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciStoreEndpoint
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciScanContainingRecord
 *
 *  Description:    OHCI Scan Containing Record( ED/TD )
 *
 *  Parameters:     USB_OHCI_LIST_ENTRY_P list ; Scanning list pointer
 *                  uint8_t type               ; list type
 *                  uint8_t field              ; list field
 *
 *  Return value:   uint32_t                   ; scanned record address
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciScanContainingRecord( USB_OHCI_LIST_ENTRY_P list, uint8_t type, uint8_t field )
{
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  ed;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P  td;
    uint32_t                            i;

    if(list == NULL)
    {
        return( 0 );
    }

    if(type == USB_OHCI_CR_TRANSFER_DESCRIPTOR)
    {
        if(field == USB_OHCI_CR_REQUESTLIST)
        {
            td = &ohci_TdMemory[ 0 ];
            for(i = 0; i < USB_OHCI_NUM_TD; i++, td++)
            {
                if((td->UsingFlag == TRUE) && (&td->RequestList == list))
                {
                    return( ( uint32_t )td );
                }
            }
        }
    }
    else if(type == USB_OHCI_CR_ENDPOINT_DESCRIPTOR)
    {
        if(field == USB_OHCI_CR_LINK)
        {
            ed = &ohci_EdMemory[ 0 ];
            for(i = 0; i < USB_OHCI_NUM_ED; i++, ed++)
            {
                if((ed->UsingFlag == TRUE) && (&ed->Link == list))
                {
                    return( ( uint32_t )ed );
                }
            }
        }
        else if(field == USB_OHCI_CR_PAUSEDLINK)
        {
            ed = &ohci_EdMemory[ 0 ];
            for(i = 0; i < USB_OHCI_NUM_ED; i++, ed++)
            {
                if((ed->UsingFlag == TRUE) && (&ed->PausedLink == list))
                {
                    return( ( uint32_t )ed );
                }
            }
        }
    }
    return( 0 );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciScanContainingRecord
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciCheckRemainedTd
 *
 *  Description:    OHCI Check remaining TDs
 *
 *  Parameters:     void
 *
 *  Return value:   uint32_t ; check result( TRUE:remaining, FALSE:not remaining )
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciCheckRemainedTd( void )
{
    if(ohci_RemainTD > 4)
    {
        return( TRUE );
    }
    return( FALSE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciCheckRemainedTd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciCheckRemainedEd
 *
 *  Description:    OHCI Check remaining EDs
 *
 *  Parameters:     void
 *
 *  Return value:   uint32_t ; check result( TRUE:remaining, FALSE:not remaining )
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciCheckRemainedEd( void )
{
    if(ohci_RemainED > 1)
    {
        return( TRUE );
    }
    return( FALSE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciCheckRemainedEd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciCheckRemainedEp
 *
 *  Description:    OHCI Check remaining EPs
 *
 *  Parameters:     void
 *
 *  Return value:   uint32_t ; check result( TRUE:remaining, FALSE:not remaining )
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciCheckRemainedEp( void )
{
    if(ohci_RemainEP > 1)
    {
        return( TRUE );
    }
    return( FALSE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciCheckRemainedEp
 **********************************************************************************************************************/