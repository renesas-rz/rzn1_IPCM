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
 * FILE         :  r_usb_hOhciTransfer.c
 * Description  :  USB OHCI Transfer Code
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
void                            usb_hstd_OhciMakeTransferRequest(USB_HCI_TR_REQ *tr_req);
void                            usb_hstd_OhciCancelTransferRequest(USB_HCI_TR_REQ *tr_req);
void                            usb_hstd_OhciProcessDoneQueue(uint32_t phys_hc_td);
void                            usb_hstd_OhciCompleteTransferRequest(USB_OHCI_REQUEST_P ohci_req);

/* Static function */
static void usb_hstd_OhciSetupRequest( USB_HCI_TR_REQ *tr_req, USB_OHCI_REQUEST_P ohci_req );
static uint32_t usb_hstd_OhciDoTransferRequest( USB_OHCI_HCD_DEVICE_DATA_P device_data, uint8_t device_address, uint8_t endpoint_number, uint8_t endpoint_type, uint16_t mps, uint8_t speed, USB_OHCI_REQUEST_P ohci_req, uint32_t pollrate );
static uint32_t usb_hstd_OhciCheckEp( USB_OHCI_HCD_ENDPOINT_P endpoint, uint8_t endpoint_type, uint16_t mps, uint8_t speed );
static uint32_t usb_hstd_OhciQueueGeneralRequest( USB_OHCI_HCD_ENDPOINT_P endpoint, USB_OHCI_REQUEST_P ohci_req );
static uint32_t usb_hstd_OhciQueueIsoRequest( USB_OHCI_HCD_ENDPOINT_P endpoint, USB_OHCI_REQUEST_P ohci_req );
static uint32_t usb_hstd_OhciQueueIsoRequestIn( USB_OHCI_HCD_ENDPOINT_P endpoint, USB_OHCI_REQUEST_P ohci_req );
static uint32_t usb_hstd_OhciQueueIsoRequestOut( USB_OHCI_HCD_ENDPOINT_P endpoint, USB_OHCI_REQUEST_P ohci_req );
static uint32_t usb_hstd_OhciInsertEDForEndpoint( USB_OHCI_HCD_ENDPOINT_P endpoint );
static void usb_hstd_OhciCompleteTransferRequestIso( USB_OHCI_HCD_ENDPOINT_P endpoint );
static uint32_t usb_hstd_OhciOpenPeriodicPipe( USB_OHCI_HCD_ENDPOINT_P endpoint );
static USB_OHCI_HCD_ENDPOINT_P usb_hstd_OhciInitializeEndpoint( USB_OHCI_HCD_DEVICE_DATA_P device_data, uint8_t endpoint_type, uint16_t max_packet_size, uint8_t device_address, uint8_t endpoint_number, uint8_t speed, uint8_t direction, uint32_t pollrate );
static uint32_t usb_hstd_OhciSetupEndpoint( USB_OHCI_HCD_DEVICE_DATA_P device_data, USB_OHCI_HCD_ENDPOINT_P endpoint, uint8_t endpoint_type, uint16_t mps, uint8_t devaddr, uint8_t epnum, uint8_t speed, uint8_t direction, uint32_t pollrate );
static USB_OHCI_LIST_ENTRY_P usb_hstd_OhciVirtualAddressOf( uint32_t data );
static uint8_t usb_hstd_OhciMinDelay( uint8_t delay1, uint8_t delay2 );
static uint32_t usb_hstd_OhciCheckTransferRequestEnd( USB_OHCI_REQUEST_P ohci_req, uint32_t mps, uint16_t size );
static uint32_t usb_hstd_OhciCancelRequest( USB_OHCI_REQUEST_P ohci_req );

/***********************************************************************************************************************
 Variable
 **********************************************************************************************************************/
/* static */
static const uint32_t   ohci_CcTable[16] =
{
    USB_OHCI_RS_NORMAL_COMPLETION,     /* NoError */
    USB_OHCI_CC_CRC,                   /* CRC */
    USB_OHCI_CC_BITSTUFFING,           /* BitStuffing */
    USB_OHCI_CC_DATATOGGLEMISMATCH,    /* DataToggleMismatch */
    USB_OHCI_CC_STALL,                 /* Stall */
    USB_OHCI_CC_DEVICENOTRESPOND,      /* DeviceNotResponding */
    USB_OHCI_CC_PIDCHECKFAILURE,       /* PIDCheckFailure */
    USB_OHCI_CC_UNEXPECTEDPID,         /* UnexpectedPID */
    USB_OHCI_CC_DATAOVERRUN,           /* DataOverrun */
    USB_OHCI_CC_DATAUNDERRUN,          /* DataUnderrun */
    USB_OHCI_RS_NOT_DONE,
    USB_OHCI_RS_NOT_DONE,
    USB_OHCI_CC_BUFFEROVERRUN,         /* BufferOverrun */
    USB_OHCI_CC_BUFFERUNDERRUN,        /* BufferUnderrun */
    USB_OHCI_RS_NOT_DONE,              /* NotAccessed */
    USB_OHCI_RS_NOT_DONE               /* NotAccessed */
};

static const uint8_t ohci_OffsetPswTable[2][8] =
{
    { 0, 1, 2, 3, 4, 5, 6, 7 }, /* little endian */
    { 1, 0, 3, 2, 5, 4, 7, 6 }  /* big endian */
};

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/

/* Global Function */
/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciMakeTransferRequest
 *
 *  Description:    OHCI Make Transfer Request
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req    ; Transfer Request Information
 *
 *  Return value:   void

 **********************************************************************************************************************/
void usb_hstd_OhciMakeTransferRequest( USB_HCI_TR_REQ *tr_req )
{
    USB_OHCI_REQUEST_P  ohci_req;
    uint32_t            result;

    /* pollrate setting */
    if(tr_req->bit.eptype == USB_EP_INT)
    {
        tr_req->pollrate = usb_hstd_HciGetPollrate( tr_req );
    }

    /* Make USBD_Request */
    ohci_req = usb_hstd_OhciAllocTransferRequest();
    if(ohci_req == NULL)
    {
        return;
    }

    tr_req->hci_info = ohci_req;

    /* Convert Driver_Request to USBD_Request */
    usb_hstd_OhciSetupRequest( tr_req, ohci_req );

    /* Send Request to HCD */
    result = usb_hstd_OhciDoTransferRequest(
        ( USB_OHCI_HCD_DEVICE_DATA_P )( tr_req->devinfo->hci_device ),
        tr_req->bit.devadrs,
        tr_req->bit.epnum,
        tr_req->bit.eptype,
        tr_req->bit.mps,
        tr_req->devinfo->bit.devspeed,
        ohci_req,
        tr_req->pollrate
    );
    if(result == FALSE)
    {
        usb_hstd_OhciFreeTransferRequest( ohci_req );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciMakeTransferRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciCancelTransferRequest
 *
 *  Description:    OHCI Chancel Transfer Request
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req ; Transfer Request Address
 *
 *  Return value:   void

 **********************************************************************************************************************/
void usb_hstd_OhciCancelTransferRequest( USB_HCI_TR_REQ *tr_req )
{
    if(tr_req == NULL)
    {
        return;
    }

    if(tr_req->bit.enable == TRUE)
    {
        if(tr_req->hci_info != NULL)
        {
            tr_req->bit.cancel_req = TRUE;

            /* Cancel Transfer Reques */
            usb_hstd_OhciCancelRequest( ( USB_OHCI_REQUEST_P )tr_req->hci_info );
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciCancelTransferRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciProcessDoneQueue
 *
 *  Description:    OHCI Process DoneQueue.
 *
 *  Parameters:     uint32_t phys_hc_td ; Physical Address Hcca Done Head
 *
 *  Return value:   void

 **********************************************************************************************************************/
void usb_hstd_OhciProcessDoneQueue( uint32_t phys_hc_td )
{
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P      td;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P      tn;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P      td_list = NULL;
    USB_OHCI_REQUEST_P                      ohci_req;
    USB_OHCI_HCD_ENDPOINT_P                 endpoint;
    USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR_P   hc_iso_td;
    USB_OHCI_ISO_TRANSFER_INFO_P            iso_tr_info;

    /* Reverse the queue passed from controller while virtualizing addresses */
    /* NOTE: The following code assumes that a uint32_t and a pointer are the same size */

    if(phys_hc_td & 1)
    {
        phys_hc_td &= ~( uint32_t )1;
    }

    if(phys_hc_td == 0)
    {
        return;
    }

#if USB_OHCI_SHAREDMEMORYTYPE == USB_OHCI_SHAREDMEMORYTYPE_EXCLUSIVE
    phys_hc_td += USB_OHCI_SHAREDMEMORY_OFFSET;
    do
    {
        td = ( USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P )usb_hstd_OhciScanContainingRecord(
            usb_hstd_OhciVirtualAddressOf( phys_hc_td ), USB_OHCI_CR_TRANSFER_DESCRIPTOR, USB_OHCI_CR_REQUESTLIST );

        phys_hc_td = td->HcTD.NextTD;
        phys_hc_td += USB_OHCI_SHAREDMEMORY_OFFSET;

        if(td_list == NULL)
        {
            td->HcTD.NextTD = NULL;
        }
        else
        {
            td->HcTD.NextTD = ( uint32_t )( td_list->PhysicalAddress + USB_OHCI_SHAREDMEMORY_OFFSET );
        }
        td_list = td;
    } while( phys_hc_td != USB_OHCI_SHAREDMEMORY_OFFSET );

#elif USB_OHCI_SHAREDMEMORYTYPE == USB_OHCI_SHAREDMEMORYTYPE_PCI
    phys_hc_td = USB_HCI_NONCACHE_ADDR( phys_hc_td );
    do
    {
        td = ( USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P )usb_hstd_OhciScanContainingRecord(
            usb_hstd_OhciVirtualAddressOf( phys_hc_td ), USB_OHCI_CR_TRANSFER_DESCRIPTOR, USB_OHCI_CR_REQUESTLIST );

        if(td->HcTD.NextTD != 0)
        {
            phys_hc_td = USB_HCI_NONCACHE_ADDR( td->HcTD.NextTD );
        }
        else
        {
            phys_hc_td = 0;
        }

        if(td_list == NULL)
        {
            td->HcTD.NextTD = 0;
        }
        else
        {
            td->HcTD.NextTD = USB_HCI_NONCACHE_ADDR( td_list->PhysicalAddress );
        }
        td_list = td;
    } while( phys_hc_td != 0 );

#else
    do
    {
        td = ( USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P )usb_hstd_OhciScanContainingRecord(
            usb_hstd_OhciVirtualAddressOf( phys_hc_td ), USB_OHCI_CR_TRANSFER_DESCRIPTOR, USB_OHCI_CR_REQUESTLIST );

        phys_hc_td = td->HcTD.NextTD;
        if(td_list == NULL)
        {
            td->HcTD.NextTD = NULL;
        }
        else
        {
            td->HcTD.NextTD = ( uint32_t )td_list->PhysicalAddress;
        }
        td_list = td;
    } while( phys_hc_td != 0 );

#endif

    /* Process list that is now reordered to completion order */
    while(td_list != NULL)
    {
        td = td_list;
        if(td->HcTD.NextTD != 0)
        {
            td_list = ( USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P )( ( td->HcTD.NextTD ) - 0x20 );
        }
        else
        {
            td_list = NULL;
        }

        if(td->TDStatus == USB_OHCI_TD_CANCELED)
        {
            usb_hstd_OhciFreeTransferDescriptor( td );
            continue;
        }

        ohci_req = td->UsbdRequest;
        endpoint = td->Endpoint;

        if(endpoint->Type != USB_EP_ISO)
        {
            if(td->HcTD.CBP != 0)
            {
                td->TransferCount -=
                    ( ( ( td->HcTD.BE ^ td->HcTD.CBP ) & 0xFFFFF000 ) ? 0x00001000 : 0 ) +
                    ( td->HcTD.BE & 0x00000FFF ) - ( td->HcTD.CBP & 0x00000FFF ) + 1;
            }
            if(td->HcTD.Control.DP != USB_OHCI_PID_SETUP)
            {
                ohci_req->BufferLength += td->TransferCount;
            }
            if(td->HcTD.Control.CC == USB_OHCI_CC_NOERROR)
            {
                /* td completed without error, remove it from USB_OHCI_REQUEST list, */
                /* if USB_OHCI_REQUEST list is now empty, then complete the request. */

                endpoint->HcdHeadP = td->NextHcdTD;
                usb_hstd_OhciRemoveListEntry( &td->RequestList );
                usb_hstd_OhciFreeTransferDescriptor( td );
                if(usb_hstd_OhciIsListEmpty(&ohci_req->HcdList) == TRUE)
                {
                    if(ohci_req->Status != USB_OHCI_RS_CANCELING)
                    {
                        ohci_req->Status = USB_OHCI_RS_NORMAL_COMPLETION;
                    }
                    else
                    {
                        ohci_req->Status = USB_OHCI_RS_CANCELED;
                    }
                    usb_hstd_OhciCompleteTransferRequest( ohci_req );
                }
            }
            else
            {
                /* TD completed with an error, remove it and other TDs for same request, */
                /* set appropriate status in USB_OHCI_REQUEST and then complete it. There */
                /* are two special cases: 1) error is DataUnderun on Bulk or Interrupt and */
                /* ShortXferOk is true; for this do not report error to USBD and restart */
                /* endpoint. 2) error is DataUnderrun on Control and ShortXferOk is true; */
                /* for this the final status TD for the ohci_req should not be canceled, the */
                /* ohci_req should not be completed, and the endpoint should be restarted. */
                /* NOTE: The endpoint has been halted by the controller */

                for(tn = endpoint->HcdHeadP; tn != endpoint->HcdTailP; tn = tn->NextHcdTD)
                {
                    if ( ( ohci_req != tn->UsbdRequest )
                        || ( ( td->HcTD.Control.CC == USB_OHCI_CC_DATAUNDERRUN )
                            && ( ohci_req->ShortXferOk != 0 )
                            && ( ohci_req->Status != USB_OHCI_RS_CANCELING )
                            && ( td->HcTD.Control.DP != tn->HcTD.Control.DP ) )
                      )
                    {
                        break;
                    }
                }

                endpoint->HcdHeadP = tn;

                endpoint->HcdED->HcED.HeadP = tn->PhysicalAddress |
                    ( endpoint->HcdED->HcED.HeadP & ( USB_OHCI_HCED_HEADP_HALT | USB_OHCI_HCED_HEADP_CARRY ) );

                /*  Delete TD about failed request  */
                while ( ( tn = ( USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P )usb_hstd_OhciScanContainingRecord(
                            usb_hstd_OhciRemoveListHead( &ohci_req->HcdList ),
                            USB_OHCI_CR_TRANSFER_DESCRIPTOR,
                                USB_OHCI_CR_REQUESTLIST)) != NULL)
                {
                    if((tn != td) && (tn != endpoint->HcdHeadP))
                    {
                        usb_hstd_OhciFreeTransferDescriptor( tn );
                    }
                }
                if(endpoint->HcdHeadP->UsbdRequest == ohci_req)
                {
                    usb_hstd_OhciInsertTailList( &ohci_req->HcdList, &endpoint->HcdHeadP->RequestList );
                    endpoint->HcdED->HcED.HeadP &= ~USB_OHCI_HCED_HEADP_HALT;
                }
                else
                {
                    if((ohci_req->ShortXferOk != 0) && (td->HcTD.Control.CC == USB_OHCI_CC_DATAUNDERRUN))
                    {
                        if(ohci_req->Status != USB_OHCI_RS_CANCELING)
                        {
                            ohci_req->Status = USB_OHCI_RS_NORMAL_COMPLETION;
                        }
                        else
                        {
                            ohci_req->Status = USB_OHCI_RS_CANCELED;
                        }
                        endpoint->HcdED->HcED.HeadP &= ~USB_OHCI_HCED_HEADP_HALT;
                    }
                    else if(ohci_req->Status != USB_OHCI_RS_CANCELING)
                    {
                        ohci_req->Status = ohci_CcTable[ td->HcTD.Control.CC ];
                    }
                    else
                    {
                        ohci_req->Status = USB_OHCI_RS_CANCELED;
                    }
                    usb_hstd_OhciCompleteTransferRequest( ohci_req );
                }
                usb_hstd_OhciFreeTransferDescriptor( td );

                switch(endpoint->Type)
                {
                    case USB_EP_CNTRL:
                        USB_HOST->HcCommandStatus.LONG = USB_OHCI_CONTROLLISTFILLED;
                        break;

                    case USB_EP_BULK:
                        USB_HOST->HcCommandStatus.LONG = USB_OHCI_BULKLISTFILLED;
                        break;

                    default:
                        break;
                }
            }
        }
        else
        {
            /* Code for Isochronous */
            hc_iso_td = ( USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR_P )&td->HcTD;

            iso_tr_info = &endpoint->IsoInfo->TransferInfo[ endpoint->IsoInfo->End_p ];
            endpoint->IsoInfo->End_p++;
            endpoint->IsoInfo->End_p &= USB_OHCI_ISO_MAX_FRAME - 1;

            iso_tr_info->Control_Cc = hc_iso_td->Control.CC;
            if(endpoint->Control.D == (USB_HCI_DIRECTION_IN + 1))
            {
                if(USB_HCI_GET_ENDIAN == 1)
                {
                    iso_tr_info->Size = hc_iso_td->USB_OHCI_OFFSET_PSW[ 1 ].PSW.SIZE;
                    iso_tr_info->Psw_Cc = hc_iso_td->USB_OHCI_OFFSET_PSW[ 1 ].PSW.CC;
                }
                else
                {
                    iso_tr_info->Size = hc_iso_td->USB_OHCI_OFFSET_PSW[ 0 ].PSW.SIZE;
                    iso_tr_info->Psw_Cc = hc_iso_td->USB_OHCI_OFFSET_PSW[ 0 ].PSW.CC;
                }
            }
            else
            {
                if(USB_HCI_GET_ENDIAN == 1)
                {
                    iso_tr_info->Size -= hc_iso_td->USB_OHCI_OFFSET_PSW[ 1 ].PSW.SIZE;
                    iso_tr_info->Psw_Cc = hc_iso_td->USB_OHCI_OFFSET_PSW[ 1 ].PSW.CC;
                }
                else
                {
                    iso_tr_info->Size -= hc_iso_td->USB_OHCI_OFFSET_PSW[ 0 ].PSW.SIZE;
                    iso_tr_info->Psw_Cc = hc_iso_td->USB_OHCI_OFFSET_PSW[ 0 ].PSW.CC;
                }
            }

            endpoint->IsoInfo->StartCnt--;
            endpoint->IsoInfo->EndCnt++;

            endpoint->HcdHeadP = td->NextHcdTD;
            usb_hstd_OhciRemoveListEntry( &td->RequestList );
            usb_hstd_OhciFreeTransferDescriptor( td );

            if(endpoint->IsoInfo->UsbdRequest != NULL)
            {
                usb_hstd_OhciCompleteTransferRequestIso( endpoint );
            }
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciProcessDoneQueue
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciCompleteTransferRequest
 *
 *  Description:    OHCI Complete Transfer Request
 *
 *  Parameters:     USB_OHCI_REQUEST_P ohci_req ; OHCI transfer request pointer
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciCompleteTransferRequest( USB_OHCI_REQUEST_P ohci_req )
{
    USB_HCI_TR_REQ  *tr_req;
    uint16_t        status;

    if(ohci_req->UsingFlag == FALSE)
    {
        return;
    }

    tr_req = ( USB_HCI_TR_REQ * )( ohci_req->DriverRequest );
    if(tr_req->bit.enable == FALSE)
    {
        return;
    }

    tr_req->status = ohci_req->Status;
    tr_req->actual_size += ohci_req->BufferLength;

    if(tr_req->status != USB_OHCI_RS_NORMAL_COMPLETION)
    {
        USB_HCI_PRINTF0_R( "Condition Code : " );
        if(tr_req->status == USB_OHCI_RS_CANCELED)
        {
            USB_HCI_PRINTF0_R( "Request is Canceled\n" );
        }
        else if(tr_req->status == USB_OHCI_CC_CRC)
        {
            USB_HCI_PRINTF0_R( "CRC Error\n" );
        }
        else if(tr_req->status == USB_OHCI_CC_BITSTUFFING)
        {
            USB_HCI_PRINTF0_R( "BitStuffing Error\n" );
        }
        else if(tr_req->status == USB_OHCI_CC_DATATOGGLEMISMATCH)
        {
            USB_HCI_PRINTF0_R( "DataToggleMismatch Error\n" );
        }
        else if(tr_req->status == USB_OHCI_CC_STALL)
        {
            USB_HCI_PRINTF0_R( "Endpoint is Stalled\n" );
        }
        else if(tr_req->status == USB_OHCI_CC_DEVICENOTRESPOND)
        {
            USB_HCI_PRINTF0_R( "DeviceNotRespond\n" );
        }
        else if(tr_req->status == USB_OHCI_CC_PIDCHECKFAILURE)
        {
            USB_HCI_PRINTF0_R( "PIDCheckFailured\n" );
        }
        else if(tr_req->status == USB_OHCI_CC_UNEXPECTEDPID)
        {
            USB_HCI_PRINTF0_R( "UnexpectedPID\n" );
        }
        else if(tr_req->status == USB_OHCI_CC_DATAOVERRUN)
        {
            USB_HCI_PRINTF0_R( "DataOverrun\n" );
        }
        else if(tr_req->status == USB_OHCI_CC_DATAUNDERRUN)
        {
            USB_HCI_PRINTF0_R( "DataUnderrun\n" );
        }
        else if(tr_req->status == USB_OHCI_CC_BUFFEROVERRUN)
        {
            USB_HCI_PRINTF0_R( "BufferOverrun\n" );
        }
        else if(tr_req->status == USB_OHCI_CC_BUFFERUNDERRUN)
        {
            USB_HCI_PRINTF0_R( "BufferUnderrun\n" );
        }

        if(tr_req->bit.eptype != USB_EP_ISO)
        {
            usb_hstd_OhciPauseEndpoint( tr_req->bit.devadrs, tr_req->bit.epnum, ohci_req->XferInfo );
        }
    }

    /* Clear completed USBD_Request */
    usb_hstd_OhciFreeTransferRequest( ohci_req );
    /* Set Transfer Status */
    status = usb_hstd_OhciGetTransferEndStatus( tr_req );

    tr_req->bit.enable = FALSE;

    usb_ghstd_HciCallback.tr_end_cb( tr_req->utr_p, tr_req->actual_size, status );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciCompleteTransferRequest
 **********************************************************************************************************************/


/* Static Function */
/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciSetupRequest
 *
 *  Description:    OHCI Setup Request
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req      ; HCI transfer request pointer
 *                  USB_OHCI_REQUEST_P ohci_req ; OHCI transfer request pointer
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_OhciSetupRequest( USB_HCI_TR_REQ *tr_req, USB_OHCI_REQUEST_P ohci_req )
{
    ohci_req->Buffer         = ( uint8_t * )tr_req->databuf;
    ohci_req->BufferLength   = tr_req->trsize;
    ohci_req->XferInfo       = tr_req->bit.direction;
    ohci_req->MaxIntDelay    = 0x00;
    ohci_req->ShortXferOk    = 0x01;

    if(tr_req->bit.epnum == 0x00)
    {
        ohci_req->Setup      = ( uint8_t * )tr_req->setupbuf;
    }

    ohci_req->DriverRequest  = ( uint32_t * )tr_req;
    ohci_req->Status         = USB_OHCI_RS_NOT_REQUESTED;
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciSetupRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciDoTransferRequest
 *
 *  Description:    OHCI Do Transfer Request
 *
 *  Parameters:     USB_OHCI_HCD_DEVICE_DATA_P device_data ; Device Data pointer
 *                  uint8_t device_address                 ; device address
 *                  uint8_t endpoint_number                ; endpoint no
 *                  uint8_t endpoint_type                  ; endpoint type
 *                  uint16_t mps                           ; Max Packet Size
 *                  uint8_t speed                          ; device speed
 *                  USB_OHCI_REQUEST_P ohci_req            ; Driver Request Information pointer
 *                  uint32_t pollrate                      ; polling rate
 *
 *  Return value:   uint32_t                               ; result( TRUE:Normal End, FALSE:Request Fail )
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciDoTransferRequest(
    USB_OHCI_HCD_DEVICE_DATA_P device_data,
    uint8_t device_address,
    uint8_t endpoint_number,
    uint8_t endpoint_type,
    uint16_t mps,
    uint8_t speed,
    USB_OHCI_REQUEST_P ohci_req,
    uint32_t pollrate
)
{
    USB_OHCI_HCD_ENDPOINT_P     endpoint;
    uint32_t                    ret = FALSE;

    endpoint = usb_hstd_OhciScanEndpoint( device_address, endpoint_number, ohci_req->XferInfo );
    if(endpoint != NULL)
    {
        if(usb_hstd_OhciCheckEp(endpoint, endpoint_type, mps, speed) == FALSE)
        {
            usb_hstd_OhciRemoveEndpoint( device_address, endpoint_number, ohci_req->XferInfo, FALSE );
            endpoint = NULL;
        }
    }

    if(usb_hstd_OhciCheckRemainedTd() == TRUE)
    {
        if(endpoint == NULL)
        {
            if((usb_hstd_OhciCheckRemainedEp() == TRUE) && (usb_hstd_OhciCheckRemainedEd() == TRUE))
            {
                endpoint = usb_hstd_OhciInitializeEndpoint(
                                    device_data,        /* Device Data pointer */
                                    endpoint_type,      /* endpoint type */
                                    mps,                /* Max Packet Size */
                                    device_address,     /* device address */
                                    endpoint_number,    /* endpoint no */
                                    speed,              /* device speed */
                                    ohci_req->XferInfo, /* direction */
                                    pollrate            /* polling rate */
                );
            }
        }

        if(endpoint != NULL)
        {
            if(endpoint_type == USB_EP_ISO)
            {
                ret = usb_hstd_OhciQueueIsoRequest( endpoint, ohci_req );
            }
            else
            {
                ret = usb_hstd_OhciQueueGeneralRequest( endpoint, ohci_req );
            }
        }
    }

    return( ret );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciDoTransferRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciCheckEp
 *
 *  Description:    OHCI Check difference between received information
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P ; endpoint pointer
 *                  uint8_t endpoint_type   ; endpoint type
 *                  uint16_t mps            ; max packet size
 *                  uint8_t speed           ; device speed
 *
 *  Return value:   uint32_t                ; check result( TRUE:same, FALSE:difference )
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciCheckEp( USB_OHCI_HCD_ENDPOINT_P endpoint, uint8_t endpoint_type, uint16_t mps, uint8_t speed )
{
    uint8_t     ret = FALSE;

    if(endpoint != NULL)
    {
        if((mps == endpoint->MaxPacket) && (speed == endpoint->Control.S) && (endpoint_type == endpoint->Type))
        {
            if(endpoint_type == USB_EP_INT)
            {
                switch(endpoint->Rate)
                {
                    case 1:
                    case 2:
                    case 4:
                    case 8:
                    case 16:
                    case 32:
                        ret = TRUE;
                        break;
                    default:
                        break;
                }
            }
            else
            {
                ret = TRUE;
            }
        }
    }
    return( ret );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciCheckEp
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciQueueGeneralRequest
 *
 *  Description:    Generate TD
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P endpoint ; Endpoint Pointer
 *                  USB_OHCI_REQUEST_P ohci_req      ; Driver ohci_req Information pointer
 *
 *  Return value:   uint32_t                         ; result( TRUE:Normal End, FALSE:Fail )
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciQueueGeneralRequest( USB_OHCI_HCD_ENDPOINT_P endpoint, USB_OHCI_REQUEST_P ohci_req )
{
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  ed;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P  td;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P  list_td = NULL;
    uint32_t                            remaining_length;
    uint32_t                            count;
    uint8_t                             *current_buffer_pointer;

    ed = endpoint->HcdED;

    if((ed == NULL) || (ed->ListIndex == USB_OHCI_ED_EOF))
    {
        /* endpoint has been removed from schedule */
        return( FALSE );
    }

    td = endpoint->HcdTailP;    /* HcdHeadP => HcdTailP */
    ohci_req->Status = USB_OHCI_RS_NOT_DONE;
    remaining_length = ohci_req->BufferLength;
    ohci_req->BufferLength  = 0;    /* report back bytes transferred so far */
    current_buffer_pointer = ohci_req->Buffer;
    usb_hstd_OhciInitializeListHead( &ohci_req->HcdList );

    if(endpoint->Type == USB_EP_CNTRL)
    {
        /* Setup a TD for setup packet */
        usb_hstd_OhciInsertTailList( &ohci_req->HcdList, &td->RequestList );
        td->UsbdRequest = ohci_req;
        td->Endpoint = endpoint;
        td->CancelPending = FALSE;
        td->HcTD.CBP = usb_hstd_OhciPhysicalAddressOf( ohci_req->Setup );
        td->HcTD.BE = usb_hstd_OhciPhysicalAddressOf( ohci_req->Setup + 7 );
        td->TransferCount = 0;
        td->HcTD.Control.DP = USB_OHCI_PID_SETUP;
        td->HcTD.Control.Toggle = 2;
        td->HcTD.Control.R = TRUE;
        td->HcTD.Control.IntD           = 7;    /* specify no interrupt */
        td->HcTD.Control.CC = USB_OHCI_CC_NOTACCESSED;
        td->NextHcdTD = usb_hstd_OhciAllocateTransferDescriptor();
        td->NextHcdTD->PhysicalAddress = td->HcTD.NextTD = usb_hstd_OhciPhysicalAddressOf( &td->NextHcdTD->HcTD );

        list_td = td;
        td = td->NextHcdTD;
    }

    /* Setup TD(s) for data packets */
    while((remaining_length != 0) || (list_td == NULL))
    {
        usb_hstd_OhciInsertTailList( &ohci_req->HcdList, &td->RequestList );
        td->UsbdRequest = ohci_req;
        td->Endpoint = endpoint;
        td->CancelPending = FALSE;

        if(remaining_length != 0)
        {
            td->HcTD.CBP = usb_hstd_OhciPhysicalAddressOf( current_buffer_pointer );
            count = USB_OHCI_MAXTDSIZE - (td->HcTD.CBP & 0x00000FFF);
            if(count < remaining_length)
            {
            }
            else
            {
                count = remaining_length;
            }
            current_buffer_pointer += count - 1;
            td->HcTD.BE = usb_hstd_OhciPhysicalAddressOf( current_buffer_pointer++ );
        }
        else
        {
            td->HcTD.CBP = td->HcTD.BE = count = 0;
        }

        td->TransferCount = count;
        td->HcTD.Control.DP = ohci_req->XferInfo + 1;

        if(endpoint->Type == USB_EP_CNTRL)
        {
            td->HcTD.Control.Toggle = 3;
        }
        else
        {
            td->HcTD.Control.Toggle = 0;
        }
        if(((remaining_length -= count) == 0) && (ohci_req->ShortXferOk != 0))
        {
            td->HcTD.Control.R = TRUE;
        }
        else
        {
            td->HcTD.Control.R = FALSE;
        }
        td->HcTD.Control.IntD           = 7;    /* specify no interrupt */
        td->HcTD.Control.CC = USB_OHCI_CC_NOTACCESSED;
        td->NextHcdTD = usb_hstd_OhciAllocateTransferDescriptor();
        td->NextHcdTD->PhysicalAddress = td->HcTD.NextTD = usb_hstd_OhciPhysicalAddressOf( &td->NextHcdTD->HcTD );

        list_td = td;
        td = td->NextHcdTD;
    }

    if(endpoint->Type == USB_EP_CNTRL)
    {
        /* Setup TD for status phase */
        usb_hstd_OhciInsertTailList( &ohci_req->HcdList, &td->RequestList );
        td->Endpoint = endpoint;
        td->UsbdRequest = ohci_req;
        td->CancelPending = FALSE;
        td->HcTD.CBP = 0;
        td->HcTD.BE = 0;
        td->TransferCount = 0;
        if(ohci_req->XferInfo == USB_HCI_DIRECTION_IN)
        {
            td->HcTD.Control.DP = USB_OHCI_PID_OUT;
        }
        else
        {
            td->HcTD.Control.DP = USB_OHCI_PID_IN;
        }
        td->HcTD.Control.Toggle = 3;
        td->HcTD.Control.R = FALSE;
        td->HcTD.Control.IntD           = 7;    /* specify no interrupt */
        td->HcTD.Control.CC = USB_OHCI_CC_NOTACCESSED;
        td->NextHcdTD = usb_hstd_OhciAllocateTransferDescriptor();
        td->NextHcdTD->PhysicalAddress = td->HcTD.NextTD = usb_hstd_OhciPhysicalAddressOf( &td->NextHcdTD->HcTD );

        list_td = td;
        td = td->NextHcdTD;
    }

    /* Setup interrupt delay */
    list_td->HcTD.Control.IntD = usb_hstd_OhciMinDelay( 6, ohci_req->MaxIntDelay );

    /* Set new TailP in ED */
    td->UsbdRequest = NULL;
    endpoint->HcdTailP = td;
    ed->HcED.TailP = td->PhysicalAddress;   /* Add null TD to the tail */

    switch(endpoint->Type)
    {
        case USB_EP_CNTRL:
            USB_HOST->HcCommandStatus.LONG = USB_OHCI_CONTROLLISTFILLED;
            break;
        case USB_EP_BULK:
            USB_HOST->HcCommandStatus.LONG = USB_OHCI_BULKLISTFILLED;
            break;
        case USB_EP_INT:
            break;
        default:
            return( FALSE );
    }

    return( TRUE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciQueueGeneralRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciQueueIsoRequest
 *
 *  Description:    OHCI Isochronous TD
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P endpoint ; Endpoint Pointer
 *                  USB_OHCI_REQUEST_P ohci_req      ; Driver ohci_req Information pointer
 *
 *  Return value:   uint32_t                         ; result( TRUE:Normal End, FALSE:Fail )

 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciQueueIsoRequest( USB_OHCI_HCD_ENDPOINT_P endpoint, USB_OHCI_REQUEST_P ohci_req )
{
    if(ohci_req->XferInfo == USB_HCI_DIRECTION_IN)
    {
        return( usb_hstd_OhciQueueIsoRequestIn( endpoint, ohci_req ) );
    }
    else
    {
        return( usb_hstd_OhciQueueIsoRequestOut( endpoint, ohci_req ) );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciQueueIsoRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciQueueIsoRequestIn
 *
 *  Description:    OHCI Isochronous TD for IN Transfer
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P endpoint ; Endpoint Pointer
 *                  USB_OHCI_REQUEST_P ohci_req      ; Driver ohci_req Information pointer
 *
 *  Return value:   uint32_t                         ; result( TRUE:Normal End, FALSE:Fail )
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciQueueIsoRequestIn( USB_OHCI_HCD_ENDPOINT_P endpoint, USB_OHCI_REQUEST_P ohci_req )
{
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P      ed;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P      td;
    uint32_t                                remaining_length;
    uint8_t                                 *current_buffer_pointer;
    uint32_t                                buffer_pointer_tmp;
    USB_OHCI_ISO_TRANSFER_INFO_P            iso_tr_info;
    USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR_P   hc_iso_td;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P      last_valid_iso_td;
    USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR_P   last_iso_hctd;

    ed = endpoint->HcdED;

    if(ed == NULL)
    {
        return( FALSE );
    }
    if(ed->ListIndex == USB_OHCI_ED_EOF)
    {
        /* endpoint has been removed from schedule */
        return( FALSE );
    }

    if(endpoint->IsoInfo->UsbdRequest == NULL)
    {
        /* The relations between Endpoint and UsbdRequest are linked here */
        endpoint->IsoInfo->UsbdRequest = ohci_req;
    }
    else
    {
        /* Error when new transfer request comes */
        return( FALSE );
    }

    if(endpoint->IsoInfo->EndCnt != 0)
    {
        usb_hstd_OhciCompleteTransferRequestIso( endpoint );
        return( TRUE );
    }

    td = endpoint->HcdTailP;        /* HcdHeadP => HcdTailP */
    if(td == NULL)
    {
        return( FALSE );
    }
    ohci_req->Status = USB_OHCI_RS_NOT_DONE;
    ohci_req->BufferLength  = 0;        /* report back bytes transferred so far */
    remaining_length = ( USB_OHCI_ISO_MAX_FRAME - ( endpoint->IsoInfo->StartCnt + endpoint->IsoInfo->EndCnt ) ) * endpoint->MaxPacket;
    usb_hstd_OhciInitializeListHead( &ohci_req->HcdList );

    /* Setup TD(s) for data packets */
    while(remaining_length != 0)
    {
        usb_hstd_OhciInsertTailList( &ohci_req->HcdList, &td->RequestList );
        td->UsbdRequest = NULL;
        td->Endpoint = endpoint;
        td->CancelPending = FALSE;

        hc_iso_td = ( USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR_P )&td->HcTD;

        iso_tr_info = &endpoint->IsoInfo->TransferInfo[ endpoint->IsoInfo->Start_p ];
        iso_tr_info->Size = 0;
        iso_tr_info->Control_Cc = 0;
        iso_tr_info->Psw_Cc = 0;

        current_buffer_pointer = &iso_tr_info->Buffer[ 0 ];
        endpoint->IsoInfo->StartCnt++;
        endpoint->IsoInfo->Start_p++;
        endpoint->IsoInfo->Start_p &= USB_OHCI_ISO_MAX_FRAME - 1;

        hc_iso_td->BP0 = usb_hstd_OhciPhysicalAddressOf( current_buffer_pointer );
        if(remaining_length > endpoint->MaxPacket)
        {
            hc_iso_td->BE = usb_hstd_OhciPhysicalAddressOf( current_buffer_pointer + endpoint->MaxPacket -1 );
        }
        else
        {
            hc_iso_td->BE = usb_hstd_OhciPhysicalAddressOf( current_buffer_pointer + remaining_length -1 );
        }

        buffer_pointer_tmp = ( uint32_t )current_buffer_pointer & 0x00000FFF;
        hc_iso_td->USB_OHCI_OFFSET_PSW[ ohci_OffsetPswTable[ USB_HCI_GET_ENDIAN ][ 0 ] ].OFFSET.OFFSET = buffer_pointer_tmp & 0x00001FFF;
        hc_iso_td->USB_OHCI_OFFSET_PSW[ ohci_OffsetPswTable[ USB_HCI_GET_ENDIAN ][ 0 ] ].OFFSET.CC = 7;
        if(remaining_length > endpoint->MaxPacket)
        {
            td->TransferCount += endpoint->MaxPacket;
            remaining_length -= endpoint->MaxPacket;
        }
        else
        {
            td->TransferCount += remaining_length;
            remaining_length = 0;
        }

        hc_iso_td->Control.IntD = 7;    /* specify no interrupt */
        hc_iso_td->Control.CC = USB_OHCI_CC_NOTACCESSED;
        hc_iso_td->Control.FC = 0;
        hc_iso_td->Control.IntD = usb_hstd_OhciMinDelay(6, ohci_req->MaxIntDelay);     /* Setup interrupt delay */

        last_valid_iso_td = endpoint->HcdHeadP;
        if(last_valid_iso_td->NextHcdTD == 0)       /* Valid IsoTD is Empty */
        {
            hc_iso_td->Control.SF = USB_HOST->HcFmNumber.LONG + 2;
        }
        else
        {
            while(last_valid_iso_td->NextHcdTD->NextHcdTD != 0)
            {
                last_valid_iso_td = last_valid_iso_td->NextHcdTD;
            }
            last_iso_hctd = ( USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR_P )&last_valid_iso_td->HcTD;
            hc_iso_td->Control.SF = last_iso_hctd->Control.SF + last_iso_hctd->Control.FC + 1;
        }

        td->NextHcdTD = usb_hstd_OhciAllocateTransferDescriptor();
        td->NextHcdTD->PhysicalAddress = td->HcTD.NextTD = usb_hstd_OhciPhysicalAddressOf( &td->NextHcdTD->HcTD );
        td = td->NextHcdTD;
    }

    /* Set new TailP in ED */
    td->UsbdRequest = NULL;
    endpoint->HcdTailP = td;
    ed->HcED.TailP = td->PhysicalAddress;   /* Add null TD to the tail */

    return( TRUE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciQueueIsoRequestIn
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciQueueIsoRequestOut
 *
 *  Description:    OHCI Isochronous TD for OUT Transfer
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P endpoint ; Endpoint Pointer
 *                  USB_OHCI_REQUEST_P ohci_req      ; Driver ohci_req Information pointer
 *
 *  Return value:   uint32_t                         ; result( TRUE:Normal End, FALSE:Fail )
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciQueueIsoRequestOut( USB_OHCI_HCD_ENDPOINT_P endpoint, USB_OHCI_REQUEST_P ohci_req )
{
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P      ed;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P      td;
    uint32_t                                remaining_count;
    uint8_t                                 *current_buffer_pointer;
    uint32_t                                buffer_pointer_tmp;
    uint32_t                                total_size;
    USB_OHCI_ISO_TRANSFER_INFO_P            iso_tr_info;
    USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR_P   hc_iso_td;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P      last_valid_iso_td;
    USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR_P   last_iso_hctd;

    ed = endpoint->HcdED;

    if(ed == NULL)
    {
        return( FALSE );
    }
    if(ed->ListIndex == USB_OHCI_ED_EOF)
    {
        /* endpoint has been removed from schedule */
        return( FALSE );
    }

    if(endpoint->IsoInfo->UsbdRequest == NULL)
    {
        /* The relations between Endpoint and UsbdRequest are linked here */
        endpoint->IsoInfo->UsbdRequest = ohci_req;
    }
    else
    {
        /* Error when new transfer request comes */
        return( FALSE );
    }

    /* Buffering */
    total_size = 0;
    while((endpoint->IsoInfo->CopyCnt < USB_OHCI_ISO_MAX_FRAME) && (ohci_req->BufferLength != 0))
    {
        iso_tr_info = &endpoint->IsoInfo->TransferInfo[ endpoint->IsoInfo->Copy_p ];

        if(ohci_req->BufferLength > endpoint->MaxPacket)
        {
            iso_tr_info->Size = endpoint->MaxPacket;
        }
        else
        {
            iso_tr_info->Size = ohci_req->BufferLength;
        }
        iso_tr_info->Control_Cc = 0;
        iso_tr_info->Psw_Cc = 0;
        memcpy( &iso_tr_info->Buffer[ 0 ], ohci_req->Buffer, iso_tr_info->Size );

        ohci_req->Buffer += iso_tr_info->Size;
        ohci_req->BufferLength -= iso_tr_info->Size;
        total_size += iso_tr_info->Size;

        endpoint->IsoInfo->CopyCnt++;
        endpoint->IsoInfo->Copy_p++;
        endpoint->IsoInfo->Copy_p &= USB_OHCI_ISO_MAX_FRAME - 1;
    }

    /* The transfer request size buffering is completed */
    /* However, the transfer completion is notified when not having arrived at USB_OHCI_ISO_MAX_FRAME yet */
    /* As a result, the following forwarding is requested */
    if((endpoint->IsoInfo->CopyCnt < USB_OHCI_ISO_MAX_FRAME) && (ohci_req->BufferLength == 0) && (endpoint->IsoInfo->StartCnt == 0))
    {
        ohci_req->BufferLength = total_size;
        /* The relation between Endpoint and UsbdRequest is released here */
        endpoint->IsoInfo->UsbdRequest = NULL;
        if(ohci_req->Status != USB_OHCI_RS_CANCELING)
        {
            ohci_req->Status = USB_OHCI_RS_NORMAL_COMPLETION;
        }
        else
        {
            ohci_req->Status = USB_OHCI_RS_CANCELED;
        }
        usb_hstd_OhciCompleteTransferRequest( ohci_req );
        return( TRUE );
    }

    if(endpoint->IsoInfo->EndCnt)
    {
        usb_hstd_OhciCompleteTransferRequestIso( endpoint );
        return( TRUE );
    }

    td = endpoint->HcdTailP;    /* HcdHeadP => HcdTailP */
    ohci_req->Status = USB_OHCI_RS_NOT_DONE;
    remaining_count = USB_OHCI_ISO_MAX_FRAME - endpoint->IsoInfo->StartCnt;
    usb_hstd_OhciInitializeListHead( &ohci_req->HcdList );

    /* Setup TD(s) for data packets */
    while(remaining_count != 0)
    {
        usb_hstd_OhciInsertTailList( &ohci_req->HcdList, &td->RequestList );
        td->UsbdRequest = NULL;
        td->Endpoint = endpoint;
        td->CancelPending = FALSE;

        hc_iso_td = ( USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR_P )&td->HcTD;

        iso_tr_info = &endpoint->IsoInfo->TransferInfo[ endpoint->IsoInfo->Start_p ];
        current_buffer_pointer = &iso_tr_info->Buffer[ 0 ];
        endpoint->IsoInfo->StartCnt++;
        endpoint->IsoInfo->Start_p++;
        endpoint->IsoInfo->Start_p &= USB_OHCI_ISO_MAX_FRAME - 1;

        hc_iso_td->BP0 = usb_hstd_OhciPhysicalAddressOf( current_buffer_pointer );
        hc_iso_td->BE = usb_hstd_OhciPhysicalAddressOf( current_buffer_pointer + iso_tr_info->Size -1 );

        buffer_pointer_tmp = ( uint32_t )current_buffer_pointer & 0x00000FFF;
        hc_iso_td->USB_OHCI_OFFSET_PSW[ ohci_OffsetPswTable[ USB_HCI_GET_ENDIAN ][ 0 ] ].OFFSET.OFFSET = buffer_pointer_tmp & 0x00001FFF;
        hc_iso_td->USB_OHCI_OFFSET_PSW[ ohci_OffsetPswTable[ USB_HCI_GET_ENDIAN ][ 0 ] ].OFFSET.CC = 7;
        td->TransferCount += iso_tr_info->Size;

        endpoint->IsoInfo->CopyCnt--;
        remaining_count--;

        hc_iso_td->Control.IntD = 7;    /* specify no interrupt */
        hc_iso_td->Control.CC = USB_OHCI_CC_NOTACCESSED;
        hc_iso_td->Control.FC = 0;
        hc_iso_td->Control.IntD = usb_hstd_OhciMinDelay(6, ohci_req->MaxIntDelay);     /* Setup interrupt delay */

        last_valid_iso_td = endpoint->HcdHeadP;
        if(last_valid_iso_td->NextHcdTD == 0)   /* Valid IsoTD is Empty */
        {
            hc_iso_td->Control.SF = USB_HOST->HcFmNumber.LONG + 2;
        }
        else
        {
            while(last_valid_iso_td->NextHcdTD->NextHcdTD != 0)
            {
                last_valid_iso_td = last_valid_iso_td->NextHcdTD;
            }
            last_iso_hctd = ( USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR_P )&last_valid_iso_td->HcTD;
            hc_iso_td->Control.SF = last_iso_hctd->Control.SF + last_iso_hctd->Control.FC + 1;
        }

        td->NextHcdTD = usb_hstd_OhciAllocateTransferDescriptor();
        td->NextHcdTD->PhysicalAddress = td->HcTD.NextTD = usb_hstd_OhciPhysicalAddressOf( &td->NextHcdTD->HcTD );
        td = td->NextHcdTD;
    }

    /* Set new TailP in ED */
    td->UsbdRequest = NULL;
    endpoint->HcdTailP = td;
    ed->HcED.TailP = td->PhysicalAddress;   /* Add null TD to the tail */

    return( TRUE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciQueueIsoRequestOut
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciInsertEDForEndpoint
 *
 *  Description:    OHCI Inserting ED to Endpoint structure.
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P endpoint ; Endpoint Pointer
 *
 *  Return value:   uint32_t                         ; result( TRUE:Normal End, FALSE:Fail )
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciInsertEDForEndpoint( USB_OHCI_HCD_ENDPOINT_P endpoint )
{
    USB_OHCI_HCD_DEVICE_DATA_P          device_data;
    USB_OHCI_HCD_ED_LIST_P              list;
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  ed;
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  tail_ed;

    device_data = endpoint->DeviceData;
    list = &device_data->EdList[ endpoint->ListIndex ];

    /* Initialize an endpoint descriptor for this endpoint */
    ed = usb_hstd_OhciAllocateEndpointDescriptor();
    if(ed == NULL)
    {
        return( FALSE );
    }

    ed->Endpoint = endpoint;
    ed->ListIndex = endpoint->ListIndex;
    ed->PhysicalAddress = usb_hstd_OhciPhysicalAddressOf( &ed->HcED );
    ed->HcED.Control = endpoint->Control;

    endpoint->HcdHeadP = usb_hstd_OhciAllocateTransferDescriptor();    /* Make Dummy TD */
    if(endpoint->HcdHeadP == NULL)
    {
        usb_hstd_OhciFreeEndpointDescriptor( ed );
        return( FALSE );
    }
    endpoint->HcdTailP = endpoint->HcdHeadP;

    ed->HcED.HeadP = usb_hstd_OhciPhysicalAddressOf( &endpoint->HcdHeadP->HcTD );

    endpoint->HcdHeadP->PhysicalAddress = ed->HcED.TailP = ed->HcED.HeadP;
    endpoint->HcdED = ed;
    endpoint->HcdHeadP->UsbdRequest = NULL;

    /* Link endpoint descriptor into HCD tracking queue */
    if((endpoint->Type != USB_EP_ISO) || (usb_hstd_OhciIsListEmpty(&list->Head) == TRUE))
    {
        /* Control/Bulk/Interrupt(any case) , Iso(List is empty) */

        /* Link ED into head of ED list */
        usb_hstd_OhciInsertHeadList( &list->Head, &ed->Link );
        ed->HcED.NextED = *list->PhysicalHead;
        *list->PhysicalHead = ed->PhysicalAddress;

    }
    else
    {
        /* Iso type ( List is not empty) */

        /* Link ED into tail of ED list */
        tail_ed = ( USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P )usb_hstd_OhciScanContainingRecord( list->Head.Blink,
            USB_OHCI_CR_ENDPOINT_DESCRIPTOR, USB_OHCI_CR_LINK );

        usb_hstd_OhciInsertTailList( &list->Head, &ed->Link );
        ed->HcED.NextED = 0;
        tail_ed->HcED.NextED = ed->PhysicalAddress;
    }

    return( TRUE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciInsertEDForEndpoint
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciCompleteTransferRequestIso
 *
 *  Description:    OHCI Complete Transfer Request for Isochronous
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P endpoint ; Endpoint Pointer
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_OhciCompleteTransferRequestIso( USB_OHCI_HCD_ENDPOINT_P endpoint )
{
    USB_OHCI_ISO_TRANSFER_INFO_P    iso_tr_info;
    USB_OHCI_REQUEST_P              ohci_req;

    ohci_req = endpoint->IsoInfo->UsbdRequest;

    iso_tr_info = &endpoint->IsoInfo->TransferInfo[ endpoint->IsoInfo->Complete_p ];
    endpoint->IsoInfo->Complete_p++;
    endpoint->IsoInfo->Complete_p &= USB_OHCI_ISO_MAX_FRAME - 1;
    if(ohci_req->XferInfo == USB_HCI_DIRECTION_IN)
    {
        memcpy( ohci_req->Buffer, iso_tr_info->Buffer, iso_tr_info->Size );
    }

    ohci_req->BufferLength += iso_tr_info->Size;
    endpoint->IsoInfo->EndCnt--;

    /* Check Transfer Request End */
    if ( usb_hstd_OhciCheckTransferRequestEnd(ohci_req, endpoint->MaxPacket, iso_tr_info->Size) == TRUE)
    {
        /* The relation between Endpoint and UsbdRequest is released here */
        endpoint->IsoInfo->UsbdRequest = NULL;
        if(ohci_req->Status != USB_OHCI_RS_CANCELING)
        {
            if(iso_tr_info->Control_Cc == USB_OHCI_CC_NOERROR)
            {
                ohci_req->Status = USB_OHCI_RS_NORMAL_COMPLETION;
            }
            else
            {
                ohci_req->Status = ohci_CcTable[ iso_tr_info->Control_Cc ];
            }
        }
        else
        {
            ohci_req->Status = USB_OHCI_RS_CANCELED;
        }
        usb_hstd_OhciCompleteTransferRequest( ohci_req );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciCompleteTransferRequestIso
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciOpenPeriodicPipe
 *
 *  Description:    OHCI Open periodic pipe
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P endpoint ; Endpoint Pointer
 *
 *  Return value:   uint32_t                         ; result( TRUE:Normal End, FALSE:Fail )
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciOpenPeriodicPipe( USB_OHCI_HCD_ENDPOINT_P endpoint )
{
    uint32_t                    which_list;
    uint32_t                    junk;
    USB_OHCI_HCD_DEVICE_DATA_P  device_data;

    device_data = endpoint->DeviceData;

    /* Determine the scheduling period  */
    which_list = USB_OHCI_ED_INTERRUPT_32ms;
    while(which_list >= endpoint->Rate && (which_list >>= 1))
    {
        continue;
    }

    /* Commit this endpoints bandwidth to the proper scheduling slot */
    if(which_list == USB_OHCI_ED_ISOCHRONOUS)
    {
        device_data->EdList[ USB_OHCI_ED_ISOCHRONOUS ].Bandwidth += endpoint->Bandwidth;
        device_data->MaxBandwidthInUse += endpoint->Bandwidth;
    }
    else
    {
        /* Determine which scheduling list has the least bandwidth */
        usb_hstd_OhciCheckBandwidth( device_data, which_list, &which_list );
        device_data->EdList[ which_list ].Bandwidth += endpoint->Bandwidth;

        /* Recalculate the max bandwidth which is in use */
        /* This allows 1ms (isoc) pipe opens to occur with few calculation */
        device_data->MaxBandwidthInUse = usb_hstd_OhciCheckBandwidth( device_data, USB_OHCI_ED_INTERRUPT_32ms, &junk );
    }

    /* Verify the new max has not over committed the USB */
    if(device_data->MaxBandwidthInUse > device_data->AvailableBandwidth)
    {
        /* Too much, back this bandwidth out and fail the request */
        device_data->EdList[ which_list ].Bandwidth -= endpoint->Bandwidth;
        device_data->MaxBandwidthInUse = usb_hstd_OhciCheckBandwidth( device_data, USB_OHCI_ED_INTERRUPT_32ms, &junk );
        return( FALSE );
    }

    /* Assign endpoint to list and open pipe */
    endpoint->ListIndex = which_list;

    return( TRUE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciOpenPeriodicPipe
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciInitializeEndpoint
 *
 *  Description:    OHCI Initialize Endpoint
 *
 *  Parameters:     USB_OHCI_HCD_DEVICE_DATA_P device_data ; Device Data pointer
 *                  uint8_t endpoint_type                  ; endpoint type
 *                  uint16_t max_packet_size               ; Max Packet Size
 *                  uint8_t device_address                 ; device address
 *                  uint8_t endpoint_number                ; endpoint no
 *                  uint8_t speed                          ; device speed
 *                  uint8_t direction                      ; direction
 *                  uint32_t pollrate                      ; polling rate
 *
 *  Return value:   USB_OHCI_HCD_ENDPOINT_P endpoint       ; endpoint pointer
 *
 **********************************************************************************************************************/
static USB_OHCI_HCD_ENDPOINT_P usb_hstd_OhciInitializeEndpoint(
    USB_OHCI_HCD_DEVICE_DATA_P device_data,
    uint8_t endpoint_type,
    uint16_t max_packet_size,
    uint8_t device_address,
    uint8_t endpoint_number,
    uint8_t speed,
    uint8_t direction,
    uint32_t pollrate
)
{
    USB_OHCI_HCD_ENDPOINT_P endpoint;
    uint32_t                ret;

    /* Create EndPoint */
    endpoint = usb_hstd_OhciAllocEndpoint();
    if(endpoint == NULL)
    {
        return( NULL );
    }

    ret = usb_hstd_OhciSetupEndpoint(
        device_data,
        endpoint,
        endpoint_type,
        max_packet_size,
        device_address,
        endpoint_number,
        speed,
        direction,
        pollrate
    );

    if(ret == FALSE)
    {
        usb_hstd_OhciFreeEndpoint( endpoint );
        return( NULL );
    }

    if((endpoint->Type == USB_EP_INT) || (endpoint->Type == USB_EP_ISO))
    {
        if(usb_hstd_OhciOpenPeriodicPipe(endpoint) == FALSE)
        {
            return( NULL );
        }
    }

    /* Add to Host Controller schedule processing */
    ret = usb_hstd_OhciInsertEDForEndpoint( endpoint );
    if(ret == TRUE)
    {
        usb_hstd_OhciStoreEndpoint( device_address, endpoint_number, direction, endpoint );
    }
    else
    {
        return( NULL );
    }

    return( endpoint );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciInitializeEndpoint
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciSetupEndpoint
 *
 *  Description:    OHCI Setup Endpoint Memory
 *
 *  Parameters:     USB_OHCI_HCD_DEVICE_DATA_P device_data ; Device Data pointer
 *                  USB_OHCI_HCD_ENDPOINT_P endpoint       ; endpoint pointer
 *                  uint8_t endpoint_type                  ; endpoint type
 *                  uint16_t mps                           ; Max Packet Size
 *                  uint8_t devaddr                        ; device address
 *                  uint8_t epnum                          ; endpoint no
 *                  uint8_t speed                          ; device speed
 *                  uint8_t direction                      ; direction
 *                  uint32_t pollrate                      ; polling rate
 *
 *  Return value:   uint32_t                               ; status
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciSetupEndpoint(
    USB_OHCI_HCD_DEVICE_DATA_P device_data,
    USB_OHCI_HCD_ENDPOINT_P endpoint,
    uint8_t endpoint_type,
    uint16_t mps,
    uint8_t devaddr,
    uint8_t epnum,
    uint8_t speed,
    uint8_t direction,
    uint32_t pollrate
)
{
    uint8_t     EndpointDescriptor_Type;

    endpoint->DeviceData = device_data;

    switch(endpoint_type)
    {
        case USB_EP_CNTRL:
            EndpointDescriptor_Type = USB_OHCI_ED_CONTROL;
            endpoint->Type = endpoint_type;
            break;

        case USB_EP_BULK:
            EndpointDescriptor_Type = USB_OHCI_ED_BULK;
            endpoint->Type = endpoint_type;
            break;

        case USB_EP_ISO:
            EndpointDescriptor_Type = USB_OHCI_ED_ISOCHRONOUS;
            endpoint->Type = endpoint_type;
            endpoint->IsoInfo = usb_hstd_OhciAllocEndpointIso();
            if(endpoint->IsoInfo == NULL)
            {
                return( FALSE );
            }
            break;

        case USB_EP_INT:
            endpoint->Type = USB_EP_INT;
            if (pollrate < (2 * 8))
            {
                EndpointDescriptor_Type = USB_OHCI_ED_INTERRUPT_1ms;
                endpoint->Rate = 1;
            }
            else if(pollrate < (4 * 8))
            {
                EndpointDescriptor_Type = USB_OHCI_ED_INTERRUPT_2ms;
                endpoint->Rate = 2;
            }
            else if(pollrate < (8 * 8))
            {
                EndpointDescriptor_Type = USB_OHCI_ED_INTERRUPT_4ms;
                endpoint->Rate = 4;
            }
            else if(pollrate < (16 * 8))
            {
                EndpointDescriptor_Type = USB_OHCI_ED_INTERRUPT_8ms;
                endpoint->Rate = 8;
            }
            else if(pollrate < (32 * 8))
            {
                EndpointDescriptor_Type = USB_OHCI_ED_INTERRUPT_16ms;
                endpoint->Rate = 16;
            }
            else
            {
                EndpointDescriptor_Type = USB_OHCI_ED_INTERRUPT_32ms;
                endpoint->Rate = 32;
            }
            break;

        default:
            return( FALSE );
    }

    endpoint->ListIndex = EndpointDescriptor_Type;
    endpoint->MaxPacket = mps;
    endpoint->Control.MPS = mps;
    endpoint->Control.FA = devaddr;
    endpoint->Control.EN = epnum;
    endpoint->Control.S = speed;

    if(endpoint_type == USB_EP_ISO)
    {
        endpoint->Control.D = direction + 1;
        endpoint->Control.F = 1;
    }
    else
    {
        endpoint->Bandwidth = mps;
    }

    return( TRUE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciSetupEndpoint
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciVirtualAddressOf
 *
 *  Description:    OHCI Return VirtualAddress
 *
 *  Parameters:     uint32_t data         ; address
 *
 *  Return value:   USB_OHCI_LIST_ENTRY_P ; Virtual Address
 *
 **********************************************************************************************************************/
static USB_OHCI_LIST_ENTRY_P usb_hstd_OhciVirtualAddressOf( uint32_t data )
{
    return( ( USB_OHCI_LIST_ENTRY_P )( data - 20 ) );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciVirtualAddressOf
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciMinDelay
 *
 *  Description:    OHCI Judge minimum value
 *
 *  Parameters:     uint8_t delay1 ; value1
 *                  uint8_t delay2 ; value2
 *
 *  Return value:   uint8_t        ; Minimum value
 *
 **********************************************************************************************************************/
static uint8_t usb_hstd_OhciMinDelay( uint8_t delay1, uint8_t delay2 )
{
    if(delay1 <= delay2)
    {
        return( delay1 );
    }
    return( delay2 );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciMinDelay
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciCheckTransferRequestEnd
 *
 *  Description:    OHCI Check Transfer Request End
 *
 *  Parameters:     USB_OHCI_REQUEST_P ohci_req ; OHCI transfer request pointer
 *                  uint32_t mps                ; max packet size
 *                  uint16_t size               ; transfer size
 *
 *  Return value:   uint32_t                    ; check flag( TRUE:End, FALSE:Not End )
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciCheckTransferRequestEnd( USB_OHCI_REQUEST_P ohci_req, uint32_t mps, uint16_t size )
{
    USB_HCI_TR_REQ  *tr_req;

    if(ohci_req->UsingFlag == FALSE)
    {
        return( FALSE );
    }

    tr_req = ( USB_HCI_TR_REQ * )( ohci_req->DriverRequest );

    /* check short packet */
    if(mps > size)
    {
        return( TRUE );
    }

    /* check transfer request size */
    if(tr_req->trsize <= (tr_req->actual_size + size))
    {
        return( TRUE );
    }

    return( FALSE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciCheckTransferRequestEnd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_OhciCancelRequest
 *
 *  Description:    OHCI Cancel Transfer Request
 *
 *  Parameters:     USB_OHCI_REQUEST_P ohci_req      ; Driver ohci_req Information pointer
 *
 *  Return value:   uint32_t                         ; result( TRUE:Normal End, FALSE:Fail )

 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciCancelRequest( USB_OHCI_REQUEST_P ohci_req )
{
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P  td;
    USB_OHCI_HCD_ENDPOINT_P             endpoint;

    /* If request status is 'not done' set status to 'canceling' */
    if(ohci_req->Status != USB_OHCI_RS_NOT_DONE)
    {
        return (FALSE);     /* cannot cancel a completed request */
    }
    ohci_req->Status = USB_OHCI_RS_CANCELING;

    td = ( USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P )usb_hstd_OhciScanContainingRecord(
            ohci_req->HcdList.Flink, USB_OHCI_CR_TRANSFER_DESCRIPTOR, USB_OHCI_CR_REQUESTLIST );

    if(td == NULL)
    {
        return (TRUE);
    }

    while(TRUE)
    {
        td->CancelPending = TRUE;
        if(&td->RequestList == ohci_req->HcdList.Blink)
        {
            break;
        }

        td = ( USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P )usb_hstd_OhciScanContainingRecord(
                td->RequestList.Flink, USB_OHCI_CR_TRANSFER_DESCRIPTOR, USB_OHCI_CR_REQUESTLIST );

        if(td == NULL)
        {
            return (TRUE);
        }

    }
    endpoint = td->Endpoint;
    usb_hstd_OhciPauseEd(endpoint);    /* stop endpoint, schedule cleanup (see Section 5.2.7.1.3) */
    return( TRUE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciCancelRequest
 **********************************************************************************************************************/