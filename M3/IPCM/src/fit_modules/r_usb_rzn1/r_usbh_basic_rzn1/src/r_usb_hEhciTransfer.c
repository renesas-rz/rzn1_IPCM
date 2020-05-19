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
 * $Revision: 1806 $
 * $Date: 2020-01-10 17:46:36 +0000 (Fri, 10 Jan 2020) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hEhciTransfer.c
 * Description  :  EHCI Transfer Code
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
void                usb_hstd_EhciMakeTransferRequest(USB_HCI_TR_REQ *tr_req);
void                usb_hstd_EhciSetAsyncQh(USB_HCI_TR_REQ *tr_req, USB_EHCI_QH *qh);
void                usb_hstd_EhciTransferEndQh(USB_HCI_TR_REQ *tr_req);
void                usb_hstd_EhciTransferEndItd(USB_HCI_TR_REQ *tr_req);
void                usb_hstd_EhciTransferEndSitd(USB_HCI_TR_REQ *tr_req);

/* Static function */
static void usb_hstd_EhciMakeCntrolBulkInterruptRequest( USB_HCI_TR_REQ *tr_req );
static void usb_hstd_EhciMakeIsochronousRequest( USB_HCI_TR_REQ *tr_req );
static void usb_hstd_EhciSetQtd( USB_EHCI_QTD *qtd, uint32_t totalsize, uint32_t pid, uint32_t toggle, uint32_t ioc, uint32_t bufferadrs );
static void usb_hstd_EhciSetPeriodicQh( USB_HCI_TR_REQ *tr_req, USB_EHCI_QH *qh, uint32_t pollrate_offset );
static void usb_hstd_EhciStartPeriodicQh( USB_EHCI_QH *qh );
static void usb_hstd_EhciInitItd( USB_HCI_TR_REQ *tr_req, USB_EHCI_ITD *itd, uint32_t ioc, uint32_t multi, uint32_t pollrate_offset );
static void usb_hstd_EhciStartItd( USB_HCI_TR_REQ   *tr_req );
static void usb_hstd_EhciInitSitd( USB_HCI_TR_REQ *tr_req, USB_EHCI_SITD *sitd, uint32_t pollrate_offset );
static void usb_hstd_EhciSetSitd( USB_EHCI_SITD *sitd, uint32_t totalsize, uint32_t direction, uint32_t ioc, uint32_t bufferadrs );
static void usb_hstd_EhciStartSitd( USB_EHCI_SITD *sitd );

/***********************************************************************************************************************
 Variable
 **********************************************************************************************************************/
#if USB_HOST_COMPLIANCE_MODE
extern uint8_t usb_ghstd_TestPacketParameterFlag;
#endif /* USB_HOST_COMPLIANCE_MODE */

/* static */
/* Start Micro-Frame Mask Table */
static const uint8_t ehci_s_mask[8] =
{
    0x01,
    0x02,
    0x04,
    0x08,
    0x10,
    0x20,
    0x40,
    0x80
};

/* Start Micro-Frame Mask Table */
static const uint8_t ehci_s_mask_pollrate4[4] =
{
    0x11,
    0x22,
    0x44,
    0x88
};

/* Start Micro-Frame Mask Table */
static const uint8_t ehci_s_mask_pollrate2[2] =
{
    0x55,
    0xAA
};

/* Complete Micro-Frame Mask Table */
static const uint8_t ehci_c_mask[8] =
{
    0x1C,
    0x38,
    0x70,
    0xE0,
    0x00,
    0x00,
    0x00,
    0x00
};

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/

/* Global Function */
/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciMakeTransferRequest
 *
 *  Description:    Make Transfer Request
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req    ; Transfer Request Information
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciMakeTransferRequest( USB_HCI_TR_REQ *tr_req )
{
    uint32_t    frame_list_size;

    /* poll-rate setting */
    switch(tr_req->bit.eptype)
    {
        case USB_EP_CNTRL:
        case USB_EP_BULK:
            tr_req->pollrate = 0;
            break;

        case USB_EP_INT:
        case USB_EP_ISO:
            tr_req->pollrate = usb_hstd_HciGetPollrate( tr_req );
            if(tr_req->pollrate == 0)
            {
                USB_HCI_PRINTF0_R( "usb_hstd_EhciMakeTransferRequest Error: pollrate = 0\n" );
                return;
            }

            /* When the cycle of the poll-rate is larger than that of the frame list size */
            frame_list_size = usb_hstd_EhciGetFrameListSize();
            if((tr_req->pollrate / 8) > frame_list_size)
            {
                tr_req->pollrate = frame_list_size * 8;
            }
            break;

        default:
            USB_HCI_PRINTF0_R( "usb_hstd_EhciMakeTransferRequest Error: Unknown Endpoint-Type\n" );
            return;
    }

    if(tr_req->bit.eptype == USB_EP_ISO)
    {
        usb_hstd_EhciMakeIsochronousRequest( tr_req );
    }
    else
    {
        usb_hstd_EhciMakeCntrolBulkInterruptRequest( tr_req );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciMakeTransferRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciSetAsyncQh
 *
 *  Description:    Set Async QH
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req ; Transfer Request Information
 *                  USB_EHCI_QH *qh        ; pointer to QH
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciSetAsyncQh( USB_HCI_TR_REQ *tr_req, USB_EHCI_QH *qh )
{
    union Endpoint1_tag     Endpoint1;
    union Endpoint2_tag     Endpoint2;

    Endpoint1.DWORD = 0;
    Endpoint2.DWORD = 0;

    Endpoint1.BIT.Maximum_Packet_Length = tr_req->bit.mps;  /* MaxPacketSize */
    if(tr_req->bit.eptype == USB_EP_CNTRL)
    {
        Endpoint1.BIT.DTC = 1;      /* Data Toggle Control */
    }
    Endpoint1.BIT.EPS               = tr_req->devinfo->bit.devspeed;    /* Device Speed */
    Endpoint1.BIT.Endpt             = tr_req->bit.epnum;                /* Endpoint No */
    Endpoint1.BIT.Device_Address    = tr_req->bit.devadrs;              /* Device Address */

    /* For split transaction */
    if(tr_req->devinfo->bit.devspeed != USB_HCI_DEVSPEED_HS)
    {
        if(tr_req->bit.eptype == USB_EP_CNTRL)
        {
            Endpoint1.BIT.C = 1;    /* Control Endpoint Flag */
        }
        Endpoint2.BIT.Hub_Addr      = tr_req->devinfo->bit.hubaddr;     /* Hub Address */
        Endpoint2.BIT.Port_Number   = tr_req->devinfo->bit.hubportnum;  /* Port Number */
    }
    Endpoint2.BIT.Mult = 1;         /* Multi = 1 */

    /* For reclamation flag */
    if(qh->Endpoint1.BIT.H == 1)
    {
        Endpoint1.BIT.H = 1;
    }

    qh->Endpoint2.DWORD = Endpoint2.DWORD;
    qh->Endpoint1.DWORD = Endpoint1.DWORD;

    if(qh->qtd_head == NULL)
    {
        /* Case that is called from usb_hstd_EhciInit function */
        qh->Next_qTD.Address = 1;
        qh->Alternate_Next_qTD.Address = 1;
    }
    else
    {
        /* When Next_qTD of QH is not set */
        qh->Next_qTD.Address = USB_HCI_NONCACHE_ADDR( ( uint32_t )qh->qtd_head );
//      qh->Next_qTD.Address = USB_HCI_CACHE_ADDR( ( uint32_t )qh->qtd_head );
        qh->Alternate_Next_qTD.Address = 1;
    }

    if(qh->Transfer_Info.BIT.Status_Halted == 1)
    {
        /* The Halted bit is released */
        qh->Transfer_Info.BIT.Status_Halted = 0;
    }

    qh->Info.direction = tr_req->bit.direction;

    /* Set Transfer Request Flag */
    qh->Info.tr_req_flag = TRUE;
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciSetAsyncQh
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciTransferEndQh
 *
 *  Description:    Transfer End QH
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req    ; Transfer Request Information
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciTransferEndQh( USB_HCI_TR_REQ *tr_req )
{
    USB_EHCI_QH     *qh;
    USB_EHCI_QTD    *data_qtd;
    uint32_t        remain_size;
    uint16_t        status;

    qh = ( USB_EHCI_QH * )tr_req->hci_info;

    /* ==================== */
    /*  Calc Transfer Size  */
    /* ==================== */
    if(tr_req->bit.eptype == USB_EP_CNTRL)
    {
        /* SETUP is skipped, and the DATA is set */
//      data_qtd = ( USB_EHCI_QTD * )USB_HCI_CACHE_ADDR( qh->qtd_head->Next_qTD.Address & 0xFFFFFFE0 );
        data_qtd = ( USB_EHCI_QTD * )USB_HCI_NONCACHE_ADDR( qh->qtd_head->Next_qTD.Address & 0xFFFFFFE0 );
    }
    else
    {
        data_qtd = qh->qtd_head;
    }

    /* The remaining transfer size is calculated */
    tr_req->actual_size = tr_req->trsize;
    while(1)
    {
        remain_size = data_qtd->Transfer_Info.BIT.Total_Bytes_to_Transfer;
        if(tr_req->actual_size < remain_size)
        {
            tr_req->actual_size = 0;
            USB_HCI_PRINTF0_R( "usb_hstd_EhciTransferEndQh Error: Transfer sizes that are bigger than Request Sizes\n" );
            break;
        }
        else
        {
            tr_req->actual_size -= remain_size;
        }

        if(data_qtd == qh->qtd_end)
        {
            break;
        }

        if(data_qtd->Next_qTD.BIT.T == 0)
        {
//          data_qtd = ( USB_EHCI_QTD * )USB_HCI_CACHE_ADDR( data_qtd->Next_qTD.Address & 0xFFFFFFE0 );
            data_qtd = ( USB_EHCI_QTD * )USB_HCI_NONCACHE_ADDR( data_qtd->Next_qTD.Address & 0xFFFFFFE0 );
        }
        else
        {
            break;
        }
    }

    /* ======================= */
    /*  Check Transfer Result  */
    /* ======================= */
    tr_req->status = qh->Transfer_Info.DWORD;

    /* =========== */
    /*  Clear qTD  */
    /* =========== */
    usb_hstd_EhciClearQtd( qh->qtd_head );
    qh->qtd_head = NULL;

    /* Clear Transfer Request Flag */
    qh->Info.tr_req_flag = FALSE;

    /* Set Transfer Status */
    status = usb_hstd_EhciGetTransferEndStatus( tr_req );

    if(tr_req->bit.eptype == USB_EP_CNTRL)
    {
        if(usb_hstd_EhciGetTransferEndStatus(tr_req) == USB_DATA_STALL)
        {
            usb_hstd_EhciClearQh( qh );
        }
    }

    /* ============== */
    /*  Clear tr_req  */
    /* ============== */
    tr_req->bit.enable = FALSE;

    /* =============== */
    /*  Callback Func  */
    /* =============== */
    usb_ghstd_HciCallback.tr_end_cb( tr_req->utr_p, tr_req->actual_size, status );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciTransferEndQh
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciTransferEndItd
 *
 *  Description:    Transfer End ITD
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req    ; Transfer Request Information
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciTransferEndItd( USB_HCI_TR_REQ *tr_req )
{
    USB_EHCI_TRANSFER_INFO  *status_p;
    USB_EHCI_ITD            *itd;
    uint16_t                status;
    uint16_t                i;
    uint8_t                 *pdatabuf;

    itd = ( USB_EHCI_ITD * )tr_req->hci_info;

    /* ==================== */
    /*  Calc Transfer Size  */
    /* ==================== */
    if(tr_req->bit.direction == USB_HCI_DIRECTION_IN)
    {
        /* Set Destination Address */
        pdatabuf = (uint8_t *)(tr_req->databuf);
        for(i = 0; i < 8; i++)
        {
            /* Check data is set */
            if( itd->Transaction[i].BIT.Length > 0 )
            {
                /* copy IN data */
                memcpy( pdatabuf, &itd->tmp_buffer[i][0], itd->Transaction[i].BIT.Length );
                /* Update Destination Address */
                pdatabuf += itd->Transaction[i].BIT.Length;
                /* Set the Reception Size */
                tr_req->actual_size += itd->Transaction[i].BIT.Length;
            }
        }
    }
    else
    {
        /* Set the Transfer Request Size */
        tr_req->actual_size = tr_req->trsize;
    }

    /* ======================= */
    /*  Check Transfer Result  */
    /* ======================= */
    tr_req->status = 0;
    status_p = ( USB_EHCI_TRANSFER_INFO * )&tr_req->status;
    status_p->BIT.Status_Active = itd->Transaction[ itd->next_trend_uframe ].BIT.Status_Active;
    status_p->BIT.Status_Data_Buffer_Error = itd->Transaction[ itd->next_trend_uframe ].BIT.Status_Data_Buffer_Error;
    status_p->BIT.Status_Babble_Detected = itd->Transaction[ itd->next_trend_uframe ].BIT.Status_Babble_Detected;
    status_p->BIT.Status_Transaction_Error = itd->Transaction[ itd->next_trend_uframe ].BIT.Status_Transaction_Error;

    /* Clear Transfer Request Flag */
    itd->Info.tr_req_flag = FALSE;

    /* Set Transfer Status */
    status = usb_hstd_EhciGetTransferEndStatus( tr_req );

    /* ============== */
    /*  Clear tr_req  */
    /* ============== */
    tr_req->bit.enable = FALSE;

    /* =========== */
    /*  Call Func  */
    /* =========== */
    usb_ghstd_HciCallback.tr_end_cb( tr_req->utr_p, tr_req->actual_size, status );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciTransferEndItd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciTransferEndSitd
 *
 *  Description:    Transfer End SITD
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req    ; Transfer Request Information
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciTransferEndSitd( USB_HCI_TR_REQ *tr_req )
{
    USB_EHCI_SITD   *sitd;
    uint32_t        remain_size;
    uint16_t        status;

    sitd = ( USB_EHCI_SITD * )tr_req->hci_info;

    /* ==================== */
    /*  Calc Transfer Size  */
    /* ==================== */
    /* The remaining transfer size is calculated */
    tr_req->actual_size = tr_req->trsize;
    remain_size = sitd->State.BIT.Total_Bytes_to_Transfer;
    if(tr_req->actual_size < remain_size)
    {
        tr_req->actual_size = 0;
        USB_HCI_PRINTF0_R( "usb_hstd_EhciTransferEndSitd Error: Transfer sizes that are bigger than Request Sizes\n" );
    }
    else
    {
        tr_req->actual_size -= remain_size;
    }

    /* ======================= */
    /*  Check Transfer Result  */
    /* ======================= */
    tr_req->status = sitd->State.DWORD;

    /* Clear Transfer Request Flag */
    sitd->Info.tr_req_flag = FALSE;

    /* Set Transfer Status */
    status = usb_hstd_EhciGetTransferEndStatus( tr_req );

    /* ============== */
    /*  Clear tr_req  */
    /* ============== */
    tr_req->bit.enable = FALSE;

    /* =========== */
    /*  Call Func  */
    /* =========== */
    usb_ghstd_HciCallback.tr_end_cb( tr_req->utr_p, tr_req->actual_size, status );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciTransferEndSitd
 **********************************************************************************************************************/

/* Static Function */
/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciMakeCntrolBulkInterruptRequest
 *
 *  Description:    Make Transfer Request
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req    ; Transfer Request Information
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciMakeCntrolBulkInterruptRequest( USB_HCI_TR_REQ *tr_req )
{
    uint32_t        new_qh_flag = FALSE;
    USB_EHCI_QH     *qh;
    USB_EHCI_QTD    *tmp_qtd;
    USB_EHCI_QTD    *pre_qtd;
    USB_EHCI_QTD    *qtd_head = NULL;
    USB_EHCI_QTD    *qtd_end  = NULL;
    uint32_t        data_pid;
    uint32_t        setup_pid;
    uint32_t        data_ioc;
    uint32_t        data_toggle;
    uint32_t        remain_size;
    uint32_t        bufaddress;
    uint32_t        ioc_flag = 0;
    uint32_t        tr_size;
    uint32_t        pollrate_offset;
    uint32_t        max_period;

    if(tr_req->bit.direction == USB_HCI_DIRECTION_OUT)
    {
        data_pid    = USB_EHCI_PID_OUT;    /* Data PID : OUT */
        setup_pid   = USB_EHCI_PID_IN;     /* Setup PID: IN */
    }
    else
    {
        data_pid    = USB_EHCI_PID_IN;     /* Data PID : IN */
        setup_pid   = USB_EHCI_PID_OUT;    /* Setup PID: OUT */
    }

    /*-----------*/
    /*  Setup TD */
    /*-----------*/
    if(tr_req->bit.eptype == USB_EP_CNTRL)
    {
        tmp_qtd = usb_hstd_EhciAllocQtd();
        if(tmp_qtd == NULL)
        {
            /* clear tr_req */
            tr_req->bit.enable = FALSE;
            return;
        }

        usb_hstd_EhciSetQtd(
                    tmp_qtd,                            /* qTD */
                    USB_HCI_SETUP_DATA_SIZE,           /* Total Size */
                    USB_EHCI_PID_SETUP,                /* PID */
                    0,                                  /* Toggle */
                    0,                                  /* Interrupt On Complete */
                    (uint32_t)&tr_req->setupbuf[0]      /* Buffer Address */
        );

        pre_qtd = tmp_qtd;
        qtd_head = tmp_qtd;
    }
    else
    {
        pre_qtd = NULL;
    }

    /*---------*/
    /* Data TD */
    /*---------*/
    if(tr_req->bit.eptype == USB_EP_CNTRL)     /* Control */
    {
        data_ioc = 0;
        data_toggle = 1;
    }
    else                                        /* Bulk or Interrupt */
    {
        data_ioc = 1;
        data_toggle = 0;
    }
    remain_size = tr_req->trsize;
    bufaddress = tr_req->databuf;
    while(remain_size != 0)
    {
        tmp_qtd = usb_hstd_EhciAllocQtd();
        if(tmp_qtd == NULL)
        {
            /* clear qtd */
            usb_hstd_EhciClearQtd( qtd_head );
            /* clear tr_req */
            tr_req->bit.enable = FALSE;
            return;
        }

        /* The maximum forwarding size of one QTD is decided */
        tr_size = USB_EHCI_MAXQTDSIZE - ( bufaddress & 0x00000FFF );
        tr_size -= tr_size % tr_req->bit.mps;
        /* Is it the last forwarding? */
        if(remain_size <= tr_size)
        {
            tr_size = remain_size;
            ioc_flag = data_ioc;
        }

        usb_hstd_EhciSetQtd(
                    tmp_qtd,                /* qTD */
                    tr_size,                /* Total Size */
                    data_pid,               /* PID */
                    data_toggle,            /* Toggle */
                    ioc_flag,               /* Interrupt On Complete */
                    bufaddress              /* Buffer Address */
        );

        remain_size -= tr_size;
        bufaddress += tr_size;

        if(pre_qtd != NULL)
        {
            usb_hstd_EhciLinkQtd( pre_qtd, tmp_qtd );
        }
        else
        {
            qtd_head = tmp_qtd;
        }
        pre_qtd = tmp_qtd;
        qtd_end = tmp_qtd;
    }

    /*-----------*/
    /* Status TD */
    /*-----------*/
    if(tr_req->bit.eptype == USB_EP_CNTRL)
    {
        tmp_qtd = usb_hstd_EhciAllocQtd();
        if(tmp_qtd == NULL)
        {
            /* clear qtd */
            usb_hstd_EhciClearQtd( qtd_head );
            /* clear tr_req */
            tr_req->bit.enable = FALSE;
            return;
        }

        usb_hstd_EhciSetQtd(
                    tmp_qtd,                /* qTD */
                    0,                      /* Total Size */
                    setup_pid,              /* PID */
                    1,                      /* Toggle */
                    1,                      /* Interrupt On Complete */
                    0                       /* Buffer Address */
        );
        usb_hstd_EhciLinkQtd( pre_qtd, tmp_qtd );
        qtd_end = tmp_qtd;
    }

    /*  QH search */
    qh = usb_hstd_EhciSearchQh( tr_req->bit.devadrs, tr_req->bit.epnum, tr_req->bit.direction, tr_req->bit.eptype );
    if(qh == NULL)
    {
        qh = usb_hstd_EhciAllocQh();
        if(qh == NULL)
        {
            /* clear qtd */
            usb_hstd_EhciClearQtd( qtd_head );
            /* clear tr_req */
            tr_req->bit.enable = FALSE;
            return;
        }
        else
        {
            new_qh_flag = TRUE;
        }
    }

    /* QH registration */
    tr_req->hci_info = qh;

    qh->qtd_head = qtd_head;
    qh->qtd_end = qtd_end;

#if USB_HOST_COMPLIANCE_MODE
    /* Sanity check to confirm pointers still aren't NULL as they are about to be dereferenced */
    if( (qtd_head == NULL) || (qtd_end == NULL) )
    {
        return;
    }

    if( usb_ghstd_TestPacketParameterFlag )
    {
        qh->qtd_head->Transfer_Info.BIT.Status_Active = 0;
        qh->qtd_head->Next_qTD.Pointer->Transfer_Info.BIT.Status_Active = 0;
        qh->qtd_end->Transfer_Info.BIT.Status_Active = 0;
    }
#endif /* USB_HOST_COMPLIANCE_MODE */

    if(tr_req->bit.eptype == USB_EP_INT)   /* Interrupt */
    {
        if(new_qh_flag == TRUE)
        {
            if(tr_req->devinfo->bit.devspeed == USB_HCI_DEVSPEED_HS)
            {
                max_period = 1;
            }
            else
            {
                /* The maximum term of 5 frames is set for the split transaction of the interrupt forwarding */
                max_period = 5;
            }
            /* Scheduling score update of Periodic Transfer */
            pollrate_offset = usb_hstd_EhciUpdatePeriodicSchedulingScore( max_period, tr_req->pollrate );
        }
        else
        {
            /* An existing setting is used */
            pollrate_offset = qh->Info.pollrate_offset;
        }

        usb_hstd_EhciSetPeriodicQh( tr_req, qh, pollrate_offset );

        if(new_qh_flag == TRUE)
        {
            /*  Link to Periodic Schedule */
            usb_hstd_EhciAddPeriodic( &qh->Queue_Head_Horizontal_Link, USB_EHCI_TYP_QH, qh->Info.pollrate, qh->Info.pollrate_offset );
        }

        /* Transfer Start */
        usb_hstd_EhciStartPeriodicQh( qh );
    }
    else                                    /* Control or Bulk */
    {
        usb_hstd_EhciSetAsyncQh( tr_req, qh );
        if(new_qh_flag == TRUE)
        {
            /*  Link to Async Schedule */
            usb_hstd_EhciAddAsync( qh );
        }
    }

#if USB_HOST_COMPLIANCE_MODE
    if( usb_ghstd_TestPacketParameterFlag )
    {
        qh->qtd_head->Transfer_Info.BIT.Status_Active = 1;                      /* Setup stage */
        r_usb_hstd_HciWaitTime(15000);
        qh->qtd_head->Next_qTD.Pointer->Transfer_Info.BIT.Status_Active = 1;    /* Data stage(IN) */
        qh->qtd_end->Transfer_Info.BIT.Status_Active = 1;                       /* Status stage */
        r_usb_hstd_HciWaitTime(15000);
    }
#endif /* USB_HOST_COMPLIANCE_MODE */

}
/***********************************************************************************************************************
 End of function usb_hstd_EhciMakeCntrolBulkInterruptRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciMakeIsochronousRequest
 *
 *  Description:    Make Isochronous Transfer Request
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req    ; Transfer Request Information
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciMakeIsochronousRequest( USB_HCI_TR_REQ *tr_req )
{
    USB_EHCI_ITD    *itd;
    USB_EHCI_SITD   *sitd;
    uint32_t        new_flag = FALSE;
    uint32_t        pollrate_offset;
    uint32_t        max_period;

    /* 0 length packet is unsupported */
    if(tr_req->trsize == 0)
    {
        return;
    }

    if(tr_req->devinfo->bit.devspeed == USB_HCI_DEVSPEED_HS)
    {
        /* Unsupported size */
        if(tr_req->trsize > (USB_EHCI_ITD_DATA_SIZE * (8 / tr_req->pollrate)) )
        {
            return;
        }

        itd = usb_hstd_EhciSearchItd( tr_req->bit.devadrs, tr_req->bit.epnum, tr_req->bit.direction );
        if(NULL == itd)
        {
            new_flag = TRUE;
            itd = usb_hstd_EhciAllocItd();
            if(itd == NULL)
            {
                tr_req->bit.enable = FALSE;
                return;
            }
        }

        tr_req->hci_info = itd;

        if(new_flag == TRUE)
        {
            max_period = 1;

            /* Update Periodic Scheduling Score */
            pollrate_offset = usb_hstd_EhciUpdatePeriodicSchedulingScore( max_period, tr_req->pollrate );

            /* Initialize ITD */
            usb_hstd_EhciInitItd(
                    tr_req,                 /* Transfer Request Information */
                    itd,                    /* pointer to ITD */
                    0,                      /* Interrupt On Complete */
                    1,                      /* Multi */
                    pollrate_offset         /* polling rate offset */
            );

            /* Link to Periodic Schedule */
            while ( ( USB_HOST->FRINDEX.LONG & 0x00000007 ) != 0x00000007 );  /* uFrame Sync */
            usb_hstd_EhciAddPeriodic( &itd->Next_Link, USB_EHCI_TYP_ITD, itd->Info.pollrate, itd->Info.pollrate_offset );
        }
        /* Transfer Start */
        usb_hstd_EhciStartItd( tr_req );
    }
    else
    {
        /* Full-speed isochronous( Split transaction ) */
        sitd = usb_hstd_EhciSearchSitd( tr_req->bit.devadrs, tr_req->bit.epnum, tr_req->bit.direction );
        if(NULL == sitd)
        {
            new_flag = TRUE;
            sitd = usb_hstd_EhciAllocSitd();
            if(sitd == NULL)
            {
                tr_req->bit.enable = FALSE;
                return;
            }
        }

        tr_req->hci_info = sitd;

        if(new_flag == TRUE)
        {
            /* The number of micro frames necessary for transfer is calculated */
            max_period = ( tr_req->bit.mps + USB_EHCI_SITD_DATA_SIZE - 1 ) / USB_EHCI_SITD_DATA_SIZE;
            if(tr_req->bit.direction == USB_HCI_DIRECTION_IN)
            {
                /* The IN transfer adds 2 micro frame.  */
                max_period += 2;
            }

            /* Update Periodic Scheduling Score */
            pollrate_offset = usb_hstd_EhciUpdatePeriodicSchedulingScore( max_period, tr_req->pollrate );
            /* Initialize SITD */
            usb_hstd_EhciInitSitd( tr_req, sitd, pollrate_offset );
            /* Link to Periodic Schedule */
            usb_hstd_EhciAddPeriodic( &sitd->Next_Link, USB_EHCI_TYP_SITD, sitd->Info.pollrate, sitd->Info.pollrate_offset );
        }

        usb_hstd_EhciSetSitd(
                    sitd,                   /* siTD */
                    tr_req->trsize,         /* Total Size */
                    tr_req->bit.direction,  /* direction */
                    1,                      /* Interrupt On Complete */
                    tr_req->databuf         /* Buffer */
        );

        /* Transfer Setting */
        usb_hstd_EhciStartSitd( sitd );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciMakeIsochronousRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciSetQtd
 *
 *  Description:    Set Async qTD
 *
 *  Parameters:     USB_EHCI_QTD *qtd     ; pointer to qTD
 *                  uint32_t totalsize    ; total transfer size
 *                  uint32_t pid          ; PID
 *                  uint32_t toggle       ; toggle
 *                  uint32_t ioc          ; Interrupt On Complete
 *                  uint32_t bufferadrs   ; buffer address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciSetQtd(
    USB_EHCI_QTD   *qtd,       /* pointer to qTD */
    uint32_t        totalsize,  /* total transfer size */
    uint32_t        pid,        /* pid */
    uint32_t        toggle,     /* toggle */
    uint32_t        ioc,        /* Interrupt On Complete */
    uint32_t        bufferadrs  /* buffer address */
)
{
    memset( qtd, 0, sizeof( USB_EHCI_QTD ) );

    qtd->Next_qTD.BIT.T = 1;
    qtd->Alternate_Next_qTD.BIT.T = 1;

    qtd->Transfer_Info.BIT.Total_Bytes_to_Transfer = totalsize;
    qtd->Transfer_Info.BIT.PID_Code                = pid;
    qtd->Transfer_Info.BIT.Data_Toggle             = toggle;
    qtd->Transfer_Info.BIT.IOC                     = ioc;
    qtd->Transfer_Info.BIT.CERR                    = 3;         /* Initial value of error count(3) */
    qtd->Transfer_Info.BIT.Status_Active           = 1;

    if(bufferadrs != 0)
    {
        qtd->Buffer[ 0 ].Address = USB_HCI_NONCACHE_ADDR( bufferadrs );
//      qtd->Buffer[ 0 ].Address = USB_HCI_CACHE_ADDR( bufferadrs );
        qtd->Buffer[ 1 ].Address = ( qtd->Buffer[ 0 ].Address + 0x1000 ) & 0xFFFFF000;
        qtd->Buffer[ 2 ].Address = ( qtd->Buffer[ 1 ].Address + 0x1000 );
        qtd->Buffer[ 3 ].Address = ( qtd->Buffer[ 2 ].Address + 0x1000 );
        qtd->Buffer[ 4 ].Address = ( qtd->Buffer[ 3 ].Address + 0x1000 );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciSetQtd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciSetPeriodicQh
 *
 *  Description:    Set Periodic QH
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req   ; Transfer Request information
 *                  USB_EHCI_QH *qh          ; pointer to QH
 *                  uint32_t pollrate_offset ; polling rate offset
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciSetPeriodicQh( USB_HCI_TR_REQ *tr_req, USB_EHCI_QH *qh, uint32_t pollrate_offset )
{
    uint32_t            offset_us;

    offset_us = pollrate_offset % 8;

    qh->Endpoint1.BIT.Maximum_Packet_Length = tr_req->bit.mps;                  /* MaxPacketSize */
    qh->Endpoint1.BIT.EPS                   = tr_req->devinfo->bit.devspeed;    /* Device Speed */
    qh->Endpoint1.BIT.Endpt                 = tr_req->bit.epnum;                /* Endpoint Number */
    qh->Endpoint1.BIT.Device_Address        = tr_req->bit.devadrs;              /* Device Address */

    /* For high band width */
    qh->Endpoint2.BIT.Mult = ((tr_req->bit.mps >> 10) & 0x3) + 1;   /* Multi */
    if(tr_req->pollrate >= 8)
    {
        qh->Endpoint2.BIT.Mframe_Smask = ehci_s_mask[offset_us];    /* Start mask */
    }
    else if(tr_req->pollrate == 4)
    {
        qh->Endpoint2.BIT.Mframe_Smask = ehci_s_mask_pollrate4[pollrate_offset % 4];    /* Start mask */
    }
    else if(tr_req->pollrate == 2)
    {
        qh->Endpoint2.BIT.Mframe_Smask = ehci_s_mask_pollrate2[pollrate_offset % 2];    /* Start mask */
    }
    else
    {
        qh->Endpoint2.BIT.Mframe_Smask =0xFF;   /* Start mask */
    }

    /* For split transaction */
    if(tr_req->devinfo->bit.devspeed != USB_HCI_DEVSPEED_HS)
    {
        qh->Endpoint2.BIT.Hub_Addr      = tr_req->devinfo->bit.hubaddr;     /* Hub Address */
        qh->Endpoint2.BIT.Port_Number   = tr_req->devinfo->bit.hubportnum;  /* Port Number */
        qh->Endpoint2.BIT.Mframe_Cmask  = ehci_c_mask[offset_us];           /* Complete Mask */
    }

    qh->Info.direction       = tr_req->bit.direction;
    qh->Info.pollrate        = tr_req->pollrate;
    qh->Info.pollrate_offset = pollrate_offset;
    qh->Transfer_Info.BIT.CERR = 3;             /* Initial value of error count(3) */

    qh->Alternate_Next_qTD.Address = 0x00000001;
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciSetPeriodicQh
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciStartPeriodicQh( USB_EHCI_QH *qh )
 *
 *  Description:    Start Periodic QH
 *
 *  Parameters:     USB_EHCI_QH *qh     ; pointer to QH
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciStartPeriodicQh( USB_EHCI_QH *qh )
{
    /* Set Transfer Request Flag */
    qh->Info.tr_req_flag = TRUE;

    qh->Next_qTD.Address = USB_HCI_NONCACHE_ADDR( ( uint32_t )qh->qtd_head );
//  qh->Next_qTD.Address = USB_HCI_CACHE_ADDR( ( uint32_t )qh->qtd_head );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciStartPeriodicQh
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciInitItd
 *
 *  Description:    Initialize ITD
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req            ; Transfer Request Information
 *                  USB_EHCI_ITD   *itd               ; pointer to ITD
 *                  uint32_t       ioc                ; Interrupt On Complete
 *                  uint32_t       multi              ; Multi
 *                  uint32_t       pollrate_offset    ; polling rate offset
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciInitItd( USB_HCI_TR_REQ *tr_req, USB_EHCI_ITD *itd, uint32_t ioc, uint32_t multi, uint32_t pollrate_offset )
{
    uint8_t     n;
    uint8_t     pg;
    uint32_t    tmp_bufferadrs;
    uint32_t    address;

    pg = 0;
    tmp_bufferadrs = ( uint32_t )&itd->tmp_buffer[ 0 ][ 0 ];
    itd->Buffer[ pg ].Address = USB_HCI_NONCACHE_ADDR( tmp_bufferadrs & 0xFFFFF000 );
//  itd->Buffer[ pg ].Address = USB_HCI_CACHE_ADDR( tmp_bufferadrs & 0xFFFFF000 );
    for(n = 0; n < 8; n++)
    {
        itd->Transaction[n].BIT.Offset  = tmp_bufferadrs & 0x00000FFF;  /* Offset */
        itd->Transaction[n].BIT.PG      = pg;                           /* PG */
        itd->Transaction[n].BIT.IOC     = ioc;                          /* Interrupt On Completion */

        address = tmp_bufferadrs & 0xFFFFF000;
        tmp_bufferadrs += USB_EHCI_ITD_DATA_SIZE;
        /* Buffer array has a length of 7 and not eight which is the loop limit and the first index is already used. So Buffer[] indexing may need boundary protection */
        if((address != (tmp_bufferadrs & 0xFFFFF000)) && (7 > (pg+1)))
        {
            pg++;
            itd->Buffer[ pg ].Address = USB_HCI_NONCACHE_ADDR( tmp_bufferadrs & 0xFFFFF000 );
//          itd->Buffer[ pg ].Address = USB_HCI_CACHE_ADDR( tmp_bufferadrs & 0xFFFFF000 );
        }
    }

    itd->Buffer[0].BIT0.Endpt                   = tr_req->bit.epnum;        /* Endpoint No */
    itd->Buffer[0].BIT0.Device_Address          = tr_req->bit.devadrs;      /* Device Address */
    itd->Buffer[1].BIT1.Direction               = tr_req->bit.direction;    /* Direction */
    itd->Buffer[1].BIT1.Maximum_Packet_Length   = tr_req->bit.mps;          /* Max Packet Size */
    itd->Buffer[2].BIT2.Multi                   = multi;                    /* Multi */

    itd->Info.direction       = tr_req->bit.direction;
    itd->Info.pollrate        = tr_req->pollrate;
    itd->Info.pollrate_offset = pollrate_offset;
    itd->next_setup_uframe    = pollrate_offset;
    itd->next_active_uframe   = pollrate_offset;
    itd->next_trend_uframe    = pollrate_offset;
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciInitItd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciStartItd
 *
 *  Description:    Start ITD
 *
 *  Parameters:     USB_HCI_TR_REQ    *tr_req     ; Transfer Request information
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciStartItd( USB_HCI_TR_REQ *tr_req )
{
    USB_EHCI_ITD    *itd;
    uint32_t        i;
    uint32_t        trsize;
    uint32_t         remain;
    uint8_t         *pdatabuf;

    itd = ( USB_EHCI_ITD * )tr_req->hci_info;

    /* Transfer Setting */
    remain = tr_req->trsize;
    for(i = 0; i < (8 / itd->Info.pollrate); i++)
    {
        /* Set TransferSize */
        if( remain > tr_req->bit.mps )
        {
            /* MaxPacketSize */
            trsize = tr_req->bit.mps;
        }
        else
        {
            /* FinalSize */
            trsize = remain;
        }
        /* Update remain size */
        remain -= trsize;
        /* Set Source Address */
        pdatabuf = (uint8_t *)((tr_req->databuf) + (tr_req->bit.mps * i));
        /* Copy OUT data */
        if(itd->Info.direction == USB_HCI_DIRECTION_OUT)
        {
            memcpy( &itd->tmp_buffer[itd->next_setup_uframe][0], pdatabuf, trsize );
        }
        /* Set Transaction */
        itd->Transaction[itd->next_setup_uframe].BIT.Length                   = trsize;
        itd->Transaction[itd->next_setup_uframe].BIT.Status_Data_Buffer_Error = 0;
        itd->Transaction[itd->next_setup_uframe].BIT.Status_Babble_Detected   = 0;
        itd->Transaction[itd->next_setup_uframe].BIT.Status_Transaction_Error = 0;
        itd->Transaction[itd->next_setup_uframe].BIT.Status_Active            = 0;
        /* Data End */
        if( remain == 0 )
        {
            /* Set Interrupt On Completion */
            itd->Transaction[itd->next_setup_uframe].BIT.IOC = 1;
            break;
        }
        /* Update Transaction index */
        itd->next_setup_uframe += itd->Info.pollrate;
    }
    /* Reset Counter */
    itd->next_setup_uframe    = itd->Info.pollrate_offset;
    /* Set Transfer Request Flag */
    itd->Info.tr_req_flag = TRUE;

    /* Setting Active Flag */
    for(i = 0; i < (8 / itd->Info.pollrate); i++)
    {
        /* Check data is set */
        if( itd->Transaction[itd->next_active_uframe].BIT.Length > 0 )
        {
            /* Set Active flag */
            itd->Transaction[itd->next_active_uframe].BIT.Status_Active = 1;
            /* Update Transaction End flame */
            itd->next_trend_uframe   = itd->next_active_uframe;
        }
        /* Update Transaction index */
        itd->next_active_uframe += itd->Info.pollrate;
    }
    /* Reset Counter */
    itd->next_active_uframe   = itd->Info.pollrate_offset;
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciStartItd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciInitSitd
 *
 *  Description:    Initialize SITD
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req     ; Transfer Request Information
 *                  USB_EHCI_SITD *sitd        ; pointer to siTD
 *                  uint32_t pollrate_offset   ; polling rate offset
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciInitSitd( USB_HCI_TR_REQ *tr_req, USB_EHCI_SITD *sitd, uint32_t pollrate_offset )
{
    uint32_t    bit_vector;
    uint32_t    tmp_size;
    uint32_t    tr_count;

    sitd->Endpoint1.BIT.Direction       = tr_req->bit.direction;            /* Direction */
    sitd->Endpoint1.BIT.Port_Number     = tr_req->devinfo->bit.hubportnum;  /* Port Number */
    sitd->Endpoint1.BIT.Hub_Addr        = tr_req->devinfo->bit.hubaddr;     /* Hub Address */
    sitd->Endpoint1.BIT.Endpt           = tr_req->bit.epnum;                /* Endpoint Number */
    sitd->Endpoint1.BIT.Device_Address  = tr_req->bit.devadrs;              /* Device Address */

    /* set bit vector */
    tmp_size = tr_req->bit.mps;
    bit_vector = 1;
    tr_count = 1;
    while(tmp_size)
    {
        if(tmp_size < USB_EHCI_SITD_DATA_SIZE)
        {
            tmp_size = 0;
        }
        else
        {
            tmp_size -= USB_EHCI_SITD_DATA_SIZE;
            bit_vector |= ( 1 << tr_count );
            tr_count++;
        }
    }

    if(tr_req->bit.direction == USB_HCI_DIRECTION_OUT)
    {
        bit_vector = bit_vector << pollrate_offset;
        sitd->Endpoint2.BIT.Mframe_Cmask = 0;           /* C-mask : 0000 0000 */
        sitd->Endpoint2.BIT.Mframe_Smask = bit_vector;  /* S-mask */
    }
    else
    {
        bit_vector = bit_vector << ( 2 + pollrate_offset );
        sitd->Endpoint2.BIT.Mframe_Cmask = bit_vector;                      /* C-mask */
        sitd->Endpoint2.BIT.Mframe_Smask = ehci_s_mask[pollrate_offset];    /* S-mask */
    }

    sitd->Back.BIT.T            = 1;    /* Back Pointer */

    sitd->Info.pollrate        = tr_req->pollrate;
    sitd->Info.pollrate_offset = pollrate_offset;
    sitd->Info.direction       = tr_req->bit.direction;
    sitd->mps                  = tr_req->bit.mps;
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciInitSitd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciSetSitd
 *
 *  Description:    Set siTD
 *
 *  Parameters:     USB_EHCI_SITD *sitd   ; pointer to siTD
 *                  uint32_t totalsize    ; total transfer size
 *                  uint32_t direction    ; direction
 *                  uint32_t ioc          ; Interrupt On Complete
 *                  uint32_t bufferadrs   ; buffer address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciSetSitd(
    USB_EHCI_SITD  *sitd,      /* pointer to siTD */
    uint32_t        totalsize,  /* total transfer size */
    uint32_t        direction,  /* direction */
    uint32_t        ioc,        /* Interrupt On Complete */
    uint32_t        bufferadrs  /* buffer address */
)
{
    uint32_t    tmp_size;
    uint32_t    tr_count;

    if(totalsize > 1023)
    {
        USB_HCI_PRINTF0_R( "usb_hstd_EhciSetSitd Error: Transfer Request Size over than 1023, force set 1023\n" );
        totalsize = 1023;
    }

    /* set bit vector */
    tmp_size = totalsize;
    tr_count = 1;
    while(tmp_size)
    {
        if(tmp_size < USB_EHCI_SITD_DATA_SIZE)
        {
            tmp_size = 0;
        }
        else
        {
            tmp_size -= USB_EHCI_SITD_DATA_SIZE;
            tr_count++;
        }
    }

    sitd->State.DWORD                       = 0;            /* State Clear */
    sitd->State.BIT.IOC                     = ioc;          /* Interrupt On Completion */
    sitd->State.BIT.Page_Select             = 0;            /* Page Select */
    sitd->State.BIT.Total_Bytes_to_Transfer = totalsize;    /* Total Size */

    sitd->Buffer[ 0 ].Address = USB_HCI_NONCACHE_ADDR( bufferadrs );
    sitd->Buffer[ 1 ].Address = USB_HCI_NONCACHE_ADDR( ( bufferadrs & 0xFFFFF000 ) + 0x1000 );
//  sitd->Buffer[ 0 ].Address = USB_HCI_CACHE_ADDR( bufferadrs );
//  sitd->Buffer[ 1 ].Address = USB_HCI_CACHE_ADDR( ( bufferadrs & 0xFFFFF000 ) + 0x1000 );

    if(direction == USB_HCI_DIRECTION_OUT)
    {
        if(totalsize <= USB_EHCI_SITD_DATA_SIZE)
        {
            sitd->Buffer[1].BIT1.TP = USB_EHCI_TP_ALL;     /* TP = 0(ALL) */
        }
        else
        {
            sitd->Buffer[1].BIT1.TP = USB_EHCI_TP_BEGIN;   /* TP = 1(BEGIN) */
        }
        sitd->Buffer[1].BIT1.T_Count = tr_count;            /* T-Count */
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciSetSitd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciStartSitd
 *
 *  Description:    Start SITD
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req     ; Transfer Request information
 *                  USB_EHCI_SITD *sitd        ; pointer to siTD
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciStartSitd( USB_EHCI_SITD *sitd )
{
    sitd->Info.tr_req_flag          = TRUE;     /* Set Transfer Request Flag */
    sitd->State.BIT.Status_Active   = 1;        /* Set Active Flag */
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciStartSitd
 **********************************************************************************************************************/