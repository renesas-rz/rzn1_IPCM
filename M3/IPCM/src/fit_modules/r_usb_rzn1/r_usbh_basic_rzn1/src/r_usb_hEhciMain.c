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
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * $Revision: 1814 $
 * $Date: 2020-01-23 15:43:44 +0000 (Thu, 23 Jan 2020) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hEhciMain.c
 * Description  :  USB EHCI main
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2020. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_usb_hHciLocal.h"

/***********************************************************************************************************************
                                Define
 **********************************************************************************************************************/
// for debug
//#define DEBUG_PRINT_PORT_INFORMATION
//#define DEBUG_PRINT_ASYNC_SCHEDULING
//#define DEBUG_PRINT_PERIODIC_SCHEDULING


/***********************************************************************************************************************
                                Prototype
 **********************************************************************************************************************/
/* Global function */
uint32_t            usb_hstd_EhciInit(void);
void                usb_hstd_EhciDeinit(void);
uint32_t            usb_hstd_EhciPortReset(uint32_t portnum);
void                usb_hstd_EhciDisconnect(uint32_t devadd);
uint32_t            usb_hstd_EhciGetFrameListSize(void);
void                usb_hstd_EhciWaitMicroFrame(uint32_t uframe_no);
void                usb_hstd_EhciAddAsync(USB_EHCI_QH *qh);
void                usb_hstd_EhciAddPeriodic(USB_EHCI_FLEP *new_element, uint32_t type, uint32_t pollrate, uint32_t pollrate_offset);
void                usb_hstd_EhciLinkQtd(USB_EHCI_QTD *qtd1st, USB_EHCI_QTD *qtd2nd);
void                usb_hstd_EhciClearQtd(USB_EHCI_QTD *qtd_head);
void                usb_hstd_EhciInactiveQtd(USB_EHCI_QTD *qtd_head);
void                usb_hstd_EhciUnlinkQhForAsync(USB_EHCI_QH *qh);
void                usb_hstd_EhciUnlinkQhForPeriodic(USB_EHCI_QH *qh);
void                usb_hstd_EhciUnlinkItd(USB_EHCI_ITD *itd);
void                usb_hstd_EhciUnlinkSitd(USB_EHCI_SITD *sitd);
uint32_t            usb_hstd_EhciUpdatePeriodicSchedulingScore(uint32_t max_period, uint32_t pollrate);
void                usb_hstd_EhciIntTransferEnd(void);
void                usb_hstd_EhciIntPortChange(void);
uint32_t            usb_hstd_EhciGetPortCurrentConnectStatus(uint16_t rootport);
void                usb_hstd_EhciClearEnumalationWaitFlag(void);
void                usb_hstd_EhciInterruptHandler(void);
uint16_t            usb_hstd_EhciGetDeviceAddressOfRootpoot(uint16_t rootport);
uint16_t            usb_hstd_EhciSetDeviceAddressOfRootpoot(uint16_t rootport, uint16_t deviceaddr);
uint16_t            usb_hstd_EhciGetTransferEndStatus(USB_HCI_TR_REQ *tr_req);
uint16_t            usb_hstd_EhciGetPidStatus(USB_HCI_TR_REQ *tr_req);
void                usb_hstd_EhciPortSuspend(uint16_t port);
void                usb_hstd_EhciPortResume(uint16_t port);
void                usb_hstd_EhciCancelTransferRequest(USB_HCI_TR_REQ *tr_req);

/* Static function */
static uint32_t usb_hstd_EhciHwReset( void );
static void usb_hstd_EhciSetPortRoute( void );
static uint32_t usb_hstd_EhciPortEnable( uint32_t portnum, uint32_t *hs_enable_flag );
static void usb_hstd_EhciDeletePeriodicSchedulingScore( uint32_t speed, uint32_t pollrate, uint32_t pollrate_offset );
static uint32_t usb_hstd_EhciUnlinkPeriodic( USB_EHCI_FLEP *dataptr, uint32_t elementnum );
static void usb_hstd_EhciClearDeviceTrreq( uint32_t devadd );

/* for debug */
#ifdef DEBUG_PRINT_PORT_INFORMATION
static void usb_hstd_EhciPrintPortInformation( void );
#endif
#ifdef DEBUG_PRINT_ASYNC_SCHEDULING
static void usb_hstd_EhciPrintAsyncScheduling( USB_EHCI_QH *h_qh );
#endif
#ifdef DEBUG_PRINT_PERIODIC_SCHEDULING
static void usb_hstd_EhciPrintPeriodicSchedulingList( void );
static void usb_hstd_EhciPrintPeriodicSchedulingScore( void );
#endif

/***********************************************************************************************************************
                                Variable
 **********************************************************************************************************************/
/* static */
static uint8_t                  ehci_RootDeviceAddress[ USB_EHCI_MAXROOTPORTS ];
static uint8_t                  ehci_PeriodicSchedulingScore[ USB_EHCI_PFL_SIZE * 8 ];

/***********************************************************************************************************************
                                Function
 **********************************************************************************************************************/

/* Global Function */
/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciInit
 *
 *  Description:    Initialize EHCI
 *
 *  Parameters:     void
 *
 *  Return Value:   uint32_t ; status
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_EhciInit( void )
{
    USB_EHCI_QH     *qh;
    uint32_t        timeout;
    uint32_t            i;

    /* EHCI version check */
    if(USB_EHCI_VERSON != USB_HOST->CAPL_VERSION.BIT.InterfaceVersionNumber)
    {
        USB_HCI_PRINTF1_R( "HCIVERSION Error : %04x\n", USB_HOST->CAPL_VERSION.BIT.InterfaceVersionNumber );
        return( USB_ERROR );
    }

    /* Stop & Reset eHC */
    usb_hstd_EhciHwReset();

    for(i = 0; i < USB_EHCI_MAXROOTPORTS; i++)
    {
        ehci_RootDeviceAddress[ i ] = USB_HCI_NODEVICE;
    }

    /* =================== */
    /*  Set Int Threshold  */
    /* =================== */
    /*  */
    USB_HOST->USBCMD.BIT.InterruptThresholdControl = 1;  /* Interrupt Threshold == 1 micro-frame */

    /* ============================== */
    /*  Set Periodic Frame List Size  */
    /* ============================== */
    if(USB_HOST->HCCPARAMS.BIT.PFLF)
    {
        if(USB_EHCI_PFL_SIZE == 512)
        {
            USB_HOST->USBCMD.BIT.FrameListSize = 1;  /* 512 */
        }
        else if(USB_EHCI_PFL_SIZE == 256)
        {
            USB_HOST->USBCMD.BIT.FrameListSize = 2;  /* 256 */
        }
    }
    else
    {
        if(USB_EHCI_PFL_SIZE != 1024)
        {
            return (USB_ERROR);     /* error */
        }
    }

    /* ========= */
    /*  Run eHC  */
    /* ========= */
    USB_HOST->USBCMD.BIT.RS = 1;   /* Run/Stop = 1 */

    /* ============================= */
    /*  Initialize QH/qTD/iTD Array  */
    /* ============================= */
    usb_hstd_EhciInitQhMemory();
    usb_hstd_EhciInitQtdMemory();
    usb_hstd_EhciInitItdMemory();
    usb_hstd_EhciInitSitdMemory();

    /* ========================== */
    /*  Initialize Periodic List  */
    /* ========================== */
    usb_hstd_EhciInitPeriodicFrameList();
    memset( &ehci_PeriodicSchedulingScore[ 0 ], 0, sizeof( ehci_PeriodicSchedulingScore ) );

    /* Link PeriodicFrameList to PeriodicSchedule */
    USB_HOST->PERIODICLIST.LONG = USB_HCI_NONCACHE_ADDR( usb_gstd_EhciGetPeriodicFrameListAddr() );

    /* Enable Periodic Schedule */
    USB_HOST->USBCMD.BIT.PeriodicScheduleEnable = 1;

    timeout = 0;
    while(USB_HOST->USBSTS.BIT.PeriodicScheduleStatus == 0)
    {
        if(timeout > USB_EHCI_TIMEOUT)
        {
            USB_HCI_PRINTF0_R( "Error : usb_hstd_EhciInit TIMEOUT\n" );
            return( USB_ERROR );
        }
        r_usb_hstd_HciWaitTime( 1 );
        timeout++;
    }

    /* ======================= */
    /*  Initialize Async List  */
    /* ======================= */
    qh = usb_hstd_EhciAllocQh();
    if(qh == NULL)
    {
        return( USB_ERROR );
    }

    qh->Queue_Head_Horizontal_Link.Address = USB_HCI_NONCACHE_ADDR( ( uint32_t )qh );
    qh->Queue_Head_Horizontal_Link.BIT.Typ = USB_EHCI_TYP_QH;
    qh->Endpoint1.BIT.H = 1;

    /* Link QH to AsyncSchuedule */
    USB_HOST->ASYNCLISTADDR.LONG = USB_HCI_NONCACHE_ADDR( ( uint32_t )qh );

    /* Enable Asynchronous Schedule */
    USB_HOST->USBCMD.BIT.ASPME = 1;

#ifdef DEBUG_PRINT_ASYNC_SCHEDULING
    usb_hstd_EhciPrintAsyncScheduling( qh );
#endif

    /* ================ */
    /*  Set Int Enable  */
    /* ================ */
    USB_HOST->USBINTR.BIT.InterruptonAsyncAdvanceEnable = 1;
    USB_HOST->USBINTR.BIT.HostSystemErrorEnable = 1;
//    USB_HOST->USBINTR.BIT.FrameListRolloverEnable = 1;
    USB_HOST->USBINTR.BIT.PortChangeInterruptEnable = 1;
    USB_HOST->USBINTR.BIT.USBErrorInterruptEnable = 1;
    USB_HOST->USBINTR.BIT.USBInterruptEnable = 1;

    USB_HOST->CONFIGFLAG.BIT.CF = 1;    /* CF */

    /* ================== */
    /*  Set Port Routing  */
    /* ================== */
    usb_hstd_EhciSetPortRoute();

    return( USB_OK );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciInit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciDeinit
 *
 *  Description:    Deinitialize EHCI
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciDeinit( void )
{
    /* Stop & Reset eHC */
    usb_hstd_EhciHwReset();
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciDeinit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciPortReset
 *
 *  Description:    EHCI Port Reset
 *
 *  Parameters:     uint32_t portnum ; port no
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_EhciPortReset( uint32_t portnum )
{
    uint32_t        timeout;

    if( portnum == 0 )
    {
        USB_HOST->PORTSC1.BIT.PortReset = 1;  /* Set Port Reset */
        r_usb_hstd_HciWaitTime( 10 );
        USB_HOST->PORTSC1.BIT.PortReset = 0;  /* Clear Port Reset */

        /* Wait Port Reset bit was cleared */
        timeout = 0;
        while(USB_HOST->PORTSC1.BIT.PortReset == 1)
        {
            if(timeout > USB_EHCI_TIMEOUT)
            {
                USB_HCI_PRINTF0_R( "Error : usb_hstd_EhciPortEnable TIMEOUT\n" );
                return( FALSE );
            }
             r_usb_hstd_HciWaitTime( 1 );
             timeout++;
        }

         r_usb_hstd_HciWaitTime( 10 );

         return( TRUE );
    }
    else
    {
         USB_HCI_PRINTF0_R( "Error : Port Setting Error\n" );
         return( FALSE );
    }

}
/***********************************************************************************************************************
 End of function usb_hstd_EhciPortReset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciDisconnect
 *
 *  Description:    EHCI Device Disconnect
 *
 *  Parameters:     uint32_t devadd ; device address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciDisconnect( uint32_t devadd )
{
    usb_hstd_EhciClearDeviceTrreq( devadd );
    usb_hstd_EhciClearDeviceQh( devadd );
    usb_hstd_EhciClearDeviceItd( devadd );
    usb_hstd_EhciClearDeviceSitd( devadd );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciDisconnect
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciGetFrameListSize
 *
 *  Description:    Getting of Frame list size
 *
 *  Parameters:     void
 *
 *  Return Value:   uint32_t ; frame list size(1024/512/256)
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_EhciGetFrameListSize( void )
{
    uint32_t    frame_list_size = 0;
    uint32_t    data;

    data = USB_HOST->USBCMD.BIT.FrameListSize;
    switch(data)
    {
        case 0:
            frame_list_size = 1024;
            break;
        case 1:
            frame_list_size = 512;
            break;
        case 2:
            frame_list_size = 256;
            break;
        default:
            break;
    }

    return( frame_list_size );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciGetFrameListSize
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciWaitMicroFrame
 *
 *  Description:    This function is waited for until becoming a specified micro frame number.
 *
 *  Parameters:     uint32_t uframe_no ; micro frame number
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciWaitMicroFrame( uint32_t uframe_no )
{
    while ( ( USB_HOST->FRINDEX.LONG & 0x00000003 ) == uframe_no );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciWaitMicroFrame
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciAddAsync
 *
 *  Description:    Add QH to AsyncSchedule
 *
 *  Parameters:     USB_EHCI_QH *qh ; QH pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciAddAsync( USB_EHCI_QH *qh )
{
    uint32_t            async_list_addr;
    USB_EHCI_QH         *qh_base;
    USB_EHCI_FLEP       tmp;

    async_list_addr = USB_HOST->ASYNCLISTADDR.LONG;
    if(async_list_addr == 0x00000000)
    {
        USB_HCI_PRINTF0_R( "usb_hstd_EhciAddAsync Error : ASYNCLISTADDR is not registered. \n" );
        return;
    }
    else
    {
        qh_base = ( USB_EHCI_QH * )USB_HCI_NONCACHE_ADDR( async_list_addr );
        if(qh != qh_base)
        {
            /* QH addition */
            tmp.Address = qh_base->Queue_Head_Horizontal_Link.Address;
            tmp.BIT.Typ = USB_EHCI_TYP_QH;
            qh->Queue_Head_Horizontal_Link.Address = tmp.Address;

            tmp.Address = USB_HCI_NONCACHE_ADDR( ( uint32_t )qh );
            tmp.BIT.Typ = USB_EHCI_TYP_QH;
            qh_base->Queue_Head_Horizontal_Link.Address = tmp.Address;
        }
        else
        {
            USB_HCI_PRINTF0_R( "usb_hstd_EhciAddAsync Error : The QH has already been registered. \n" );
            return;
        }
    }

#ifdef DEBUG_PRINT_ASYNC_SCHEDULING
    usb_hstd_EhciPrintAsyncScheduling( NULL );
#endif
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciAddAsync
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciAddPeriodic
 *
 *  Description:    Add QH/ITD/SITD to PeriodicSchedule
 *
 *  Parameters:     USB_EHCI_FLEP *new_element   ; QH/ITD/SITD pointer
 *                  uint32_t type            ; element type( QH/ITD/SITD )
 *                  uint32_t pollrate        ; poll-rate
 *                  uint32_t pollrate_offset ; poll-rate offset
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciAddPeriodic( USB_EHCI_FLEP *new_element, uint32_t type, uint32_t pollrate, uint32_t pollrate_offset )
{
    uint32_t                frame_list_size;
    uint32_t                n;
    uint32_t                periodic_list_addr;
    uint32_t                pollrate_ms;
    uint32_t                offset_ms;
    uint32_t                current_element_pollrate;
    uint32_t                tmp_addr;
    USB_EHCI_FLEP           *listbase;
    volatile USB_EHCI_FLEP  *current_element;
    volatile USB_EHCI_FLEP  tmp_element;

    if(pollrate == 0)
    {
        USB_HCI_PRINTF0_R( "usb_hstd_EhciAddPeriodic Error: pollrate = 0\n" );
        return;
    }
    if(type == USB_EHCI_TYP_FSTN)
    {
        USB_HCI_PRINTF0_R( "usb_hstd_EhciAddPeriodic Error: USB_EHCI_TYP_FSTN is not support\n" );
        return;
    }
    if(new_element == NULL)
    {
        USB_HCI_PRINTF0_R( "usb_hstd_EhciAddPeriodic Error: Element Pointer is NULL\n" );
        return;
    }

    /* Get frame list size */
    frame_list_size = usb_hstd_EhciGetFrameListSize();

    periodic_list_addr = USB_HOST->PERIODICLIST.LONG & 0xFFFFF000;
    if(periodic_list_addr == 0x00000000)
    {
        USB_HCI_PRINTF0_R( "usb_hstd_EhciAddPeriodic Error : PERIODICLISTBASE is not registered. \n" );
        return;
    }
    else
    {
        periodic_list_addr = USB_HCI_CACHE_ADDR( periodic_list_addr );
    }

    offset_ms = pollrate_offset / 8;
    pollrate_ms = pollrate / 8;
    if(pollrate_ms == 0)
    {
        pollrate_ms = 1;
    }

    /*-----------*/
    /* Interrupt */
    /*-----------*/
    /* The content of the periodic frame list is changed.  */
    /* Attention: In this schedule, the Paul rate should be an involution value of two. */
    listbase = ( USB_EHCI_FLEP * )periodic_list_addr;
    for (n = offset_ms; n < frame_list_size; n += pollrate_ms)
    {
        current_element = &listbase[ n ];

        while(1)
        {
            if(current_element == NULL)
            {
                USB_HCI_PRINTF0_R( "usb_hstd_EhciAddPeriodic Error: Current Element Pointer is NULL\n" );
                return;
            }

            /* If T bit is 1, the new element is added. */
            if(current_element->BIT.T == 1)
            {
                new_element->Address = 0x00000001;
                tmp_element.Address = USB_HCI_NONCACHE_ADDR( ( uint32_t )new_element );
                tmp_element.BIT.Typ = type;
                *current_element = tmp_element;
                break;
            }

            tmp_addr = USB_HCI_NONCACHE_ADDR( current_element->Address & 0xFFFFFFE0 );

            /* If a current element is the same as the new element, loop termination.  */
            if(tmp_addr == (uint32_t)new_element)
            {
                break;
            }

            /* The poll-rate of a current element is acquired. */
            switch(current_element->BIT.Typ)
            {
                case USB_EHCI_TYP_ITD:
                    current_element_pollrate = ( ( USB_EHCI_ITD * )tmp_addr )->Info.pollrate;
                    break;
                case USB_EHCI_TYP_QH:
                    current_element_pollrate = ( ( USB_EHCI_QH * )tmp_addr )->Info.pollrate;
                    break;
                case USB_EHCI_TYP_SITD:
                    current_element_pollrate = ( ( USB_EHCI_SITD * )tmp_addr )->Info.pollrate;
                    break;
                default:
                    current_element_pollrate = 0xFFFFFFFF;
                    break;
            }

            /* If poll-rates are compared, and the value of the new element is large, the new element is added. */
            if(pollrate > current_element_pollrate)
            {
                tmp_element.Address = USB_HCI_NONCACHE_ADDR( tmp_addr );
//              tmp_element.Address = USB_HCI_CACHE_ADDR( tmp_addr );
                tmp_element.BIT.Typ = current_element->BIT.Typ;
                *new_element = tmp_element;

                tmp_element.Address = USB_HCI_NONCACHE_ADDR( ( uint32_t )new_element );
//              tmp_element.Address = USB_HCI_CACHE_ADDR( ( uint32_t )new_element );
                tmp_element.BIT.Typ = type;
                *current_element = tmp_element;
                break;
            }

            /* It shifts to the next element.  */
//          current_element = ( USB_EHCI_FLEP * )USB_HCI_CACHE_ADDR( current_element->Address & 0xFFFFFFE0 );
            current_element = ( USB_EHCI_FLEP * )USB_HCI_NONCACHE_ADDR( current_element->Address & 0xFFFFFFE0 );
        }
    }

#ifdef DEBUG_PRINT_PERIODIC_SCHEDULING
    usb_hstd_EhciPrintPeriodicSchedulingList();
#endif
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciAddPeriodic
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciLinkQtd
 *
 *  Description:    Link qTDs
 *
 *  Parameters:     USB_EHCI_QTD *qtd1st ; QTD pointer
 *                  USB_EHCI_QTD *qtd2nd ; QTD pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciLinkQtd( USB_EHCI_QTD *qtd1st, USB_EHCI_QTD *qtd2nd )
{
    qtd1st->Next_qTD.Address = USB_HCI_NONCACHE_ADDR( ( uint32_t )qtd2nd );
//  qtd1st->Next_qTD.Address = USB_HCI_CACHE_ADDR( ( uint32_t )qtd2nd );
    qtd1st->Alternate_Next_qTD.Address = qtd1st->Next_qTD.Address;
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciLinkQtd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciClearQtd
 *
 *  Description:    Clear qTDs
 *
 *  Parameters:     USB_EHCI_QTD *qtd_head ; QTD head pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciClearQtd( USB_EHCI_QTD *qtd_head )
{
    USB_EHCI_QTD    *clear_qtd;
    USB_EHCI_QTD    *next_qtd;

    clear_qtd = qtd_head;
    while(1)
    {
        if(clear_qtd == NULL)
        {
            USB_HCI_PRINTF0_R( "usb_hstd_EhciClearQtd Error : QTD pointer is NULL. \n" );
            return;
        }
        if(clear_qtd->Next_qTD.BIT.T == 1)
        {
            memset( clear_qtd, 0, sizeof( USB_EHCI_QTD ) );
            usb_hstd_EhciFreeQtd( clear_qtd );
            break;
        }
        else
        {
//          next_qtd = ( USB_EHCI_QTD * )USB_HCI_CACHE_ADDR( clear_qtd->Next_qTD.Address & 0xFFFFFFE0 );
            next_qtd = ( USB_EHCI_QTD * )USB_HCI_NONCACHE_ADDR( clear_qtd->Next_qTD.Address & 0xFFFFFFE0 );
            memset( clear_qtd, 0, sizeof( USB_EHCI_QTD ) );
            usb_hstd_EhciFreeQtd( clear_qtd );
            clear_qtd = next_qtd;
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciClearQtd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciInactiveQtd
 *
 *  Description:    Inactive qTDs
 *
 *  Parameters:     USB_EHCI_QTD *qtd_head ; QTD head pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciInactiveQtd( USB_EHCI_QTD *qtd_head )
{
    USB_EHCI_QTD    *clear_qtd;

    clear_qtd = qtd_head;

    while(1)
    {
        if(clear_qtd == NULL)
        {
            USB_HCI_PRINTF0_R( "usb_hstd_EhciInactiveQtd Error : QTD pointer is NULL. \n" );
            return;
        }
        /* clear active bit */
        clear_qtd->Transfer_Info.BIT.Status_Active = 0;

        if(clear_qtd->Next_qTD.BIT.T == 1)
        {
            break;
        }

//      clear_qtd = ( USB_EHCI_QTD * )USB_HCI_CACHE_ADDR( clear_qtd->Next_qTD.Address & 0xFFFFFFE0 );
        clear_qtd = ( USB_EHCI_QTD * )USB_HCI_NONCACHE_ADDR( clear_qtd->Next_qTD.Address & 0xFFFFFFE0 );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciInactiveQtd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciUnlinkQhForAsync
 *
 *  Description:    Unlink Async-QH( CNT/BULK ) from AsyncList
 *
 *  Parameters:     USB_EHCI_QH *qh ; QH pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciUnlinkQhForAsync( USB_EHCI_QH *qh )
{
    USB_EHCI_QH     *asynclist;
    USB_EHCI_QH     *current_element;
    uint32_t        current_contents;
    uint32_t        timeout;

    if(qh == NULL)
    {
        return;
    }
    if((USB_HOST->ASYNCLISTADDR.LONG & 0xFFFFFFE0) == 0x00000000)
    {
        USB_HCI_PRINTF0_R( "usb_hstd_EhciUnlinkQhForAsync Error : ASYNCLISTADDR is not registered. \n" );
        return;
    }
//  asynclist = ( USB_EHCI_QH * )USB_HCI_CACHE_ADDR( USB_HOST->ASYNCLISTADDR.LONG & 0xFFFFFFE0 );
    asynclist = ( USB_EHCI_QH * )USB_HCI_NONCACHE_ADDR( USB_HOST->ASYNCLISTADDR.LONG & 0xFFFFFFE0 );

    /*-----------------*/
    /* check asynclist */
    /*-----------------*/
    /* When the next link of QH is oneself */
//  if(((uint32_t)qh == USB_HCI_CACHE_ADDR(qh->Queue_Head_Horizontal_Link.Address & 0xFFFFFFE0)))
    if(((uint32_t)qh == USB_HCI_NONCACHE_ADDR(qh->Queue_Head_Horizontal_Link.Address & 0xFFFFFFE0)))
    {
        /* The termination of the asynchronization schedule is executed */
        if(qh != asynclist)
        {
            USB_HCI_PRINTF0_R( "usb_hstd_EhciUnlinkQhForAsync Error : Illegal case 1\n" );
            return;
        }
        /* disable Asynchronous Schedule */
        USB_HOST->USBCMD.BIT.AsynchronousScheduleParkModeEnable = 0;

        /* wait async schedule disabled */
        timeout = 0;
        while(USB_HOST->USBSTS.BIT.PeriodicScheduleStatus == 1)
        {
            if(timeout > USB_EHCI_TIMEOUT)
            {
                break;
            }
            r_usb_hstd_HciWaitTime( 1 );
            timeout++;
        }

        /* clear AsyncSchuedule */
        USB_HOST->ASYNCLISTADDR.LONG = 0;
        return;
    }

    /* When you delete qh specified with asynclist by chance */
    if(qh == asynclist)
    {
        /* The setting of asynclist is changed to the next QH */
//      asynclist = ( USB_EHCI_QH * )USB_HCI_CACHE_ADDR( asynclist->Queue_Head_Horizontal_Link.Address & 0xFFFFFFE0 );
        asynclist = ( USB_EHCI_QH * )USB_HCI_NONCACHE_ADDR( asynclist->Queue_Head_Horizontal_Link.Address & 0xFFFFFFE0 );
    }

    /*---------*/
    /* scan QH */
    /*---------*/
    current_element = asynclist;
//  current_contents = USB_HCI_CACHE_ADDR( current_element->Queue_Head_Horizontal_Link.Address & 0xFFFFFFE0 );
    current_contents = USB_HCI_NONCACHE_ADDR( current_element->Queue_Head_Horizontal_Link.Address & 0xFFFFFFE0 );
    while(current_contents != (uint32_t)asynclist)
    {
        if(current_element->Queue_Head_Horizontal_Link.BIT.T == 1)
        {
            /* The terminal is shown though it is a list of the round loop (This case is usually impossible) */
            USB_HCI_PRINTF0_R( "usb_hstd_EhciUnlinkQhForAsync Error : Illegal case 2\n" );
            return;
        }
        else if(current_contents == (uint32_t)qh)
        {
            current_element->Queue_Head_Horizontal_Link.Address = qh->Queue_Head_Horizontal_Link.Address;
            break;
        }
        else
        {
//          current_element = ( USB_EHCI_QH * )USB_HCI_CACHE_ADDR( current_element->Queue_Head_Horizontal_Link.Address & 0xFFFFFFE0 );
            current_element = ( USB_EHCI_QH * )USB_HCI_NONCACHE_ADDR( current_element->Queue_Head_Horizontal_Link.Address & 0xFFFFFFE0 );
            if(current_element == NULL)
            {
                USB_HCI_PRINTF0_R( "usb_hstd_EhciUnlinkQhForAsync Error: Current Element Pointer is NULL\n" );
                return;
            }
//          current_contents = USB_HCI_CACHE_ADDR( current_element->Queue_Head_Horizontal_Link.Address & 0xFFFFFFE0 );
            current_contents = USB_HCI_NONCACHE_ADDR( current_element->Queue_Head_Horizontal_Link.Address & 0xFFFFFFE0 );
        }
    }

    /*-----------*/
    /* unlink QH */
    /*-----------*/
    /* doorbell */
    USB_HOST->USBCMD.BIT.InterruptonAsyncAdvanceDoorbell = 1;
    /* It is necessary to wait here for 1ms */
    r_usb_hstd_HciWaitTime( 1 );
    timeout = 0;
    while(USB_HOST->USBSTS.BIT.InterruptonAsyncAdvance == 1)
    {
        if (timeout > USB_EHCI_TIMEOUT)
        {
            break;
        }
        r_usb_hstd_HciWaitTime( 1 );
        timeout++;
    }
    USB_HOST->USBSTS.BIT.InterruptonAsyncAdvance = 1;

#ifdef DEBUG_PRINT_ASYNC_SCHEDULING
    usb_hstd_EhciPrintAsyncScheduling( NULL );
#endif
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciUnlinkQhForAsync
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciUnlinkQhForPeriodic
 *
 *  Description:    Unlink Periodic-QH( INT ) from Periodic Frame List
 *
 *  Parameters:     USB_EHCI_QH *qh ; QH pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciUnlinkQhForPeriodic( USB_EHCI_QH *qh )
{
    uint32_t    n;
    uint32_t    frame_list_size;
    uint32_t    max_period;

    if(qh == NULL)
    {
        return;
    }

    /* Get frame list size */
    frame_list_size = usb_hstd_EhciGetFrameListSize();

    /* unlink qh */
    for(n = 0; n < frame_list_size; n++)
    {
        usb_hstd_EhciUnlinkPeriodic( &qh->Queue_Head_Horizontal_Link, n );
    }

#ifdef DEBUG_PRINT_PERIODIC_SCHEDULING
    usb_hstd_EhciPrintPeriodicSchedulingList();
#endif

    if(qh->Info.pollrate != 0)
    {
        if(qh->Endpoint1.BIT.EPS == USB_HCI_DEVSPEED_HS)
        {
            max_period = 1;
        }
        else
        {
            /* The maximum term of 5 frames is set for the split transaction of the interrupt forwarding */
            max_period = 5;
        }
        usb_hstd_EhciDeletePeriodicSchedulingScore( max_period, qh->Info.pollrate, qh->Info.pollrate_offset );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciUnlinkQhForPeriodic
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciUnlinkItd
 *
 *  Description:    Unlink Periodic-ITD( HS-ISO ) from Periodic Frame List
 *
 *  Parameters:     USB_EHCI_ITD *itd ; ITD pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciUnlinkItd( USB_EHCI_ITD *itd )
{
    uint32_t    n;
    uint32_t    frame_list_size;
    uint32_t    max_period;

    if(itd == NULL)
    {
        return;
    }

    /* Get frame list size */
    frame_list_size = usb_hstd_EhciGetFrameListSize();

    /* unlink itd */
    for(n = 0; n < frame_list_size; n++)
    {
        usb_hstd_EhciUnlinkPeriodic( &itd->Next_Link, n );
    }

#ifdef DEBUG_PRINT_PERIODIC_SCHEDULING
    usb_hstd_EhciPrintPeriodicSchedulingList();
#endif

    if(itd->Info.pollrate != 0)
    {
        max_period = 1;
        usb_hstd_EhciDeletePeriodicSchedulingScore( max_period, itd->Info.pollrate, itd->Info.pollrate_offset );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciUnlinkItd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciUnlinkSitd
 *
 *  Description:    Unlink Periodic-SITD( FS-ISO ) from Periodic Frame List
 *
 *  Parameters:     USB_EHCI_SITD *sitd ; SITD pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciUnlinkSitd( USB_EHCI_SITD *sitd )
{
    uint32_t    n;
    uint32_t    frame_list_size;
    uint32_t    max_period;

    if(sitd == NULL)
    {
        return;
    }

    /* Get frame list size */
    frame_list_size = usb_hstd_EhciGetFrameListSize();

    /* unlink sitd */
    for(n = 0; n < frame_list_size; n++)
    {
        usb_hstd_EhciUnlinkPeriodic( &sitd->Next_Link, n );
    }

#ifdef DEBUG_PRINT_PERIODIC_SCHEDULING
    usb_hstd_EhciPrintPeriodicSchedulingList();
#endif

    if(sitd->Info.pollrate != 0)
    {
        /* The number of micro frames necessary for transfer is calculated */
        max_period = ( sitd->mps + USB_EHCI_SITD_DATA_SIZE - 1 ) / USB_EHCI_SITD_DATA_SIZE;
        if(sitd->Info.direction == USB_HCI_DIRECTION_IN)
        {
            /* The IN transfer adds 2 micro frame */
            max_period += 2;
        }
        usb_hstd_EhciDeletePeriodicSchedulingScore( max_period, sitd->Info.pollrate, sitd->Info.pollrate_offset );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciUnlinkSitd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciUpdatePeriodicSchedulingScore
 *
 *  Description:    Update Periodic Scheduling Score
 *
 *  Parameters:     uint32_t max_period ; max period
 *                  uint32_t pollrate   ; poll-rate
 *
 *  Return Value:   uint32_t            ; poll-rate offset
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_EhciUpdatePeriodicSchedulingScore( uint32_t max_period, uint32_t pollrate )
{
    uint32_t        uframe_list_size;
    uint32_t        n;
    uint32_t        i;
    uint32_t        j;
    uint32_t        score;
    uint32_t        score_min;
    uint32_t        score_min_n = 0;
    uint32_t        pollrate_offset;

    /* Get micro frame list size */
    uframe_list_size = usb_hstd_EhciGetFrameListSize();
    uframe_list_size *= 8;

    /* Search for minimum score */
    score_min = 0xFFFFFFFF;
    for(n = 0; n < pollrate; )
    {
        /* Acquisition of score */
        score = 0;
        for(j = 0; j < max_period; j++)
        {
            for(i = n + j; i < uframe_list_size; i += pollrate)
            {
                score += ehci_PeriodicSchedulingScore[ i ];
            }
        }

        if(score_min > score)
        {
            /* Because a minimum score at present was found, the value is kept */
            score_min = score;
            score_min_n = n;
        }

        if(score_min == 0)
        {
            /* Because minimum score 0 was found, it ends here */
            break;
        }

        if(max_period == 1)
        {
            n++;
        }
        else
        {
            /* The split transaction that steps over the frame is not scheduled */
            if ((n % 8) == (8 - max_period))
            {
                n += max_period;
            }
            else
            {
                n++;
            }
        }
    }
    pollrate_offset = score_min_n % pollrate;

    /* Update Score */
    for(n = pollrate_offset; n < uframe_list_size; n += pollrate)
    {
        for(j = 0; j < max_period; j++)
        {
            ehci_PeriodicSchedulingScore[ n + j ]++;
        }
    }

#ifdef DEBUG_PRINT_PERIODIC_SCHEDULING
    usb_hstd_EhciPrintPeriodicSchedulingScore();
#endif

    return( pollrate_offset );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciUpdatePeriodicSchedulingScore
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciIntTransferEnd
 *
 *  Description:    EHCI Transfer End Interrupt Handler
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciIntTransferEnd( void )
{
    USB_HCI_TR_REQ  *tr_req;
    USB_EHCI_QH     *qh;
    USB_EHCI_ITD    *itd;
    USB_EHCI_SITD   *sitd;
    uint32_t        i;
    uint8_t         error_status;

    tr_req = &usb_ghstd_HciTransferRequest[ 0 ];
    for(i = 0; i < USB_HCI_TRREQ_NUM; i++, tr_req++)
    {
        if(tr_req->bit.enable == TRUE)
        {
            if(tr_req->devinfo == NULL)
            {
                continue;
            }
            if(tr_req->devinfo->bit.hctype == USB_HCI_HCTYPE_EHCI)
            {
                if(NULL != tr_req->hci_info)
                {
                    if(tr_req->bit.eptype == USB_EP_ISO)
                    {
                        /* for isochronous */
                        if(tr_req->devinfo->bit.devspeed == USB_HCI_DEVSPEED_HS)
                        {
                            itd = ( USB_EHCI_ITD * )tr_req->hci_info;
                            if(itd->Info.tr_req_flag == TRUE)
                            {
                                /* check status */
                                if(itd->Transaction[itd->next_trend_uframe].BIT.Status_Data_Buffer_Error == 1)
                                {
                                    USB_HCI_PRINTF1_R( "Error ITD(%d): Data Buffer Error\n", tr_req->bit.devadrs );
                                }
                                if(itd->Transaction[itd->next_trend_uframe].BIT.Status_Babble_Detected == 1)
                                {
                                    USB_HCI_PRINTF1_R( "Error ITD(%d): Babble Detected\n", tr_req->bit.devadrs );
                                }
                                if(itd->Transaction[itd->next_trend_uframe].BIT.Status_Transaction_Error == 1)
                                {
                                    USB_HCI_PRINTF1_R( "Error ITD(%d): Transaction Error\n", tr_req->bit.devadrs );
                                }
                                /* High-speed isochronous */
                                if(itd->Transaction[itd->next_trend_uframe].BIT.Status_Active == 0)
                                {
                                    usb_hstd_EhciTransferEndItd( tr_req );
                                }
                            }
                        }
                        else
                        {
                            sitd = ( USB_EHCI_SITD * )tr_req->hci_info;
                            if(sitd->Info.tr_req_flag == TRUE)
                            {
                                /* check status */
                                if(sitd->State.BIT.Status_ERR == 1)
                                {
                                    USB_HCI_PRINTF1_R( "Error SITD(%d): ERR Response\n", tr_req->bit.devadrs );
                                }
                                if(sitd->State.BIT.Status_Data_Buffer_Error == 1)
                                {
                                    USB_HCI_PRINTF1_R( "Error SITD(%d): Data Buffer Error\n", tr_req->bit.devadrs );
                                }
                                if(sitd->State.BIT.Status_Babble_Detected == 1)
                                {
                                    USB_HCI_PRINTF1_R( "Error SITD(%d): Babble Detected\n", tr_req->bit.devadrs );
                                }
                                if(sitd->State.BIT.Status_Transaction_Error == 1)
                                {
                                    USB_HCI_PRINTF1_R( "Error SITD(%d): Transaction Error\n", tr_req->bit.devadrs );
                                }
                                if(sitd->State.BIT.Status_Missed_Micro_Frame == 1)
                                {
//                                  USB_HCI_PRINTF1_R( "Error SITD(%d): Missed Micro Frame\n", tr_req->bit.devadrs );
                                }
                                /* Full-speed isochronous( Split transaction ) */
                                if((sitd->State.BIT.IOC == 1) && (sitd->State.BIT.Status_Active == 0))
                                {
                                    usb_hstd_EhciTransferEndSitd( tr_req );
                                }
                            }
                        }
                    }
                    else
                    {
                        /* Error Status Clear */
                        error_status = 0x00;
                        /* for interrupt/control/bulk */
                        qh = ( USB_EHCI_QH * )tr_req->hci_info;
                        if(qh->Info.tr_req_flag == TRUE)
                        {
                            /* check status */
                            if(qh->Transfer_Info.BIT.CERR != 3)
                            {
                                if(qh->Transfer_Info.BIT.CERR == 0)
                                {
                                    error_status |= 0x01;
                                }
                                USB_HCI_PRINTF2_R( "Error QH(%d): CERR=%d\n", tr_req->bit.devadrs, qh->Transfer_Info.BIT.CERR );
                            }
                            if(qh->Transfer_Info.BIT.Status_Halted == 1)
                            {
                                error_status |= 0x02;
                                USB_HCI_PRINTF1_R( "Error QH(%d): Halted\n", tr_req->bit.devadrs );
                            }
                            if(qh->Transfer_Info.BIT.Status_Data_Buffer_Error == 1)
                            {
                                error_status |= 0x04;
                                USB_HCI_PRINTF1_R( "Error QH(%d): Data Buffer Error\n", tr_req->bit.devadrs );
                            }
                            if(qh->Transfer_Info.BIT.Status_Babble_Detected == 1)
                            {
                                error_status |= 0x08;
                                USB_HCI_PRINTF1_R( "Error QH(%d): Babble Detected\n", tr_req->bit.devadrs );
                            }
                            if(qh->Transfer_Info.BIT.Status_Transaction_Error == 1)
                            {
                                error_status |= 0x10;
                                USB_HCI_PRINTF1_R( "Error QH(%d): Transaction Error\n", tr_req->bit.devadrs );
                                tr_req->bit.enable = FALSE;
                            }
                            if(qh->Transfer_Info.BIT.Status_Missed_Micro_Frame == 1)
                            {
//                              USB_HCI_PRINTF1_R( "Error QH(%d): Missed Micro Frame\n", tr_req->bit.devadrs );
                            }

                            if(qh->Transfer_Info.BIT.Status_Halted == 1)
                            {
                                /* Transfer completion when abnormality operating */
                                usb_hstd_EhciTransferEndQh( tr_req );
                            }
                            else if((qh->qtd_end->Transfer_Info.BIT.IOC == 1) &&
                                       (qh->qtd_end->Transfer_Info.BIT.Status_Active == 0))
                            {
                                /* Transfer completion when normality operating */
                                usb_hstd_EhciTransferEndQh( tr_req );
                            }
                            else if(error_status != 0x00)
                            {
                                /* Error Check */
                                if(qh->Current_qTD.Pointer->Transfer_Info.BIT.Status_Active == 0)
                                {
                                    USB_HCI_PRINTF2_R( "Error QH(%d): Error Stop! Error Status=0x%x\n", tr_req->bit.devadrs, error_status);
                                    usb_hstd_EhciTransferEndQh(tr_req);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciIntTransferEnd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciIntPortChange
 *
 *  Description:    EHCI Port Change Interrupt Handler
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciIntPortChange( void )
{
    USB_HCI_DEVICE      *devinfo;
    uint32_t            n;
    uint32_t            connect_flag;
    uint32_t            hs_enable_flag;
    uint32_t            count;

    n = 0;

#ifdef DEBUG_PRINT_PORT_INFORMATION
        usb_hstd_EhciPrintPortInformation();
#endif

    if(USB_HOST->PORTSC1.BIT.PortOwner == 1)
    {
        return;
    }

    if(USB_HOST->PORTSC1.BIT.OvercurrentChange == 1)
    {
        if(USB_HOST->PORTSC1.BIT.OvercurrentActive == 1)
        {
            /* over current callback */
            usb_ghstd_HciCallback.over_current_cb( n );
        }
    }

    if(USB_HOST->PORTSC1.BIT.PortEnableDisableChange == 1)
    {
        if(USB_HOST->PORTSC1.BIT.PortEnabledDisabled == 1)
        {
            /* port enable */
        }
        else
        {
            /* port disable */
        }
    }

    if(USB_HOST->PORTSC1.BIT.ConnectStatusChange == 1)
    {
        /* Here is waited for until Current_Connect_Status is fixed */
        count = 0;
        while(count < 11)
        {
            connect_flag = USB_HOST->PORTSC1.BIT.CurrentConnectStatus;
            r_usb_hstd_HciWaitTime( 10 );
            if(connect_flag == USB_HOST->PORTSC1.BIT.CurrentConnectStatus)
            {
                count++;
            }
            else
            {
                count = 0;
            }
        }

        if((USB_HOST->PORTSC1.BIT.CurrentConnectStatus == 0) && (USB_HOST->PORTSC1.BIT.PortOwner == 0))
        {
            if(ehci_RootDeviceAddress[n] != USB_HCI_NODEVICE)
            {
                r_usb_hstd_HciDisconnect( ehci_RootDeviceAddress[ n ] );
                ehci_RootDeviceAddress[ n ] = USB_HCI_NODEVICE;
                /* detach callback */
                usb_ghstd_HciCallback.detach_cb( n );
            }
        }
        else
        {
            if(ehci_RootDeviceAddress[n] != USB_HCI_NODEVICE)
            {
                r_usb_hstd_HciDisconnect( ehci_RootDeviceAddress[ n ] );
                ehci_RootDeviceAddress[ n ] = USB_HCI_NODEVICE;
            }

            if(usb_hstd_EhciPortEnable(n, &hs_enable_flag) == TRUE)
            {
                if(hs_enable_flag == TRUE)
                {
                    /* For an enable port */
                    devinfo = usb_hstd_HciAllocDevinfo();
                    if(devinfo != NULL)
                    {
                        devinfo->bit.devnum = 0;
                        ehci_RootDeviceAddress[ n ] = devinfo->bit.devnum;
                        devinfo->bit.devspeed = USB_HCI_DEVSPEED_HS;
                        devinfo->bit.hctype = USB_HCI_HCTYPE_EHCI;
                        /* attach callback */
                        usb_ghstd_HciCallback.attach_cb( n );
                        }
                    }
                else
                {
                    /* The port owner is changed to OHCI in case of the port disable */
                    USB_HOST->PORTSC1.BIT.PortOwner = 1;  /* Port Owner : OHCI */
                    r_usb_hstd_HciWaitTime( 50 );
                }
            }
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciIntPortChange
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciInterruptHandler
 *
 *  Description:    EHCI Interrupt Handler
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciInterruptHandler( void )
{

    if(USB_HOST->USBSTS.LONG != 0 && USB_HOST->USBINTR.LONG != 0)
    {
        if( USB_HOST->USBSTS.BIT.HostSystemError == 1 && USB_HOST->USBINTR.BIT.HostSystemErrorEnable == 1)
        {
            usb_hstd_HciSendMessageFromInt( USB_HCI_TASK, USB_HCI_MESS_EHCI_HOST_SYSTEM_ERROR, 0 );
            USB_HOST->USBSTS.BIT.HostSystemError = 1;
        }
        if( USB_HOST->USBSTS.BIT.PortChangeDetect == 1 && USB_HOST->USBINTR.BIT.PortChangeInterruptEnable == 1)
        {
            usb_hstd_HciSendMessageFromInt( USB_HCI_TASK, USB_HCI_MESS_EHCI_PORT_CHANGE_DETECT, 0 );
            USB_HOST->USBSTS.BIT.PortChangeDetect = 1;
        }
        if( USB_HOST->USBSTS.BIT.USBERRINT == 1 && USB_HOST->USBINTR.BIT.USBErrorInterruptEnable == 1)
        {
            usb_hstd_HciSendMessageFromInt( USB_HCI_TASK, USB_HCI_MESS_EHCI_USBERRINT, 0 );
            USB_HOST->USBSTS.BIT.USBERRINT = 1;
        }
        if( USB_HOST->USBSTS.BIT.InterruptonAsyncAdvance == 1 && USB_HOST->USBINTR.BIT.InterruptonAsyncAdvanceEnable == 1)
        {
            usb_hstd_HciSendMessageFromInt( USB_HCI_TASK, USB_HCI_MESS_EHCI_INTERRUPT_ON_ASYNC_ADVANCE, 0 );
            USB_HOST->USBSTS.BIT.InterruptonAsyncAdvance = 1;
        }
        if( USB_HOST->USBSTS.BIT.FrameListRollover == 1 && USB_HOST->USBINTR.BIT.FrameListRolloverEnable == 1)
        {
            usb_hstd_HciSendMessageFromInt( USB_HCI_TASK, USB_HCI_MESS_EHCI_FRAME_LIST_ROLLOVER, 0 );
            USB_HOST->USBSTS.BIT.FrameListRollover = 1;
        }
        if( USB_HOST->USBSTS.BIT.USBINT == 1 && USB_HOST->USBINTR.BIT.USBInterruptEnable == 1)
        {
            usb_hstd_HciSendMessageFromInt( USB_HCI_TASK, USB_HCI_MESS_EHCI_USBINT, 0 );
            USB_HOST->USBSTS.BIT.USBINT = 1;
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciInterruptHandler
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciGetDeviceAddressOfRootpoot
 *
 *  Description:    EHCI Getting of device address of rootport
 *
 *  Parameters:     uint16_t rootport ; rootport no
 *
 *  Return Value:   uint16_t          ; device address
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_EhciGetDeviceAddressOfRootpoot( uint16_t rootport )
{
    if(USB_EHCI_MAXROOTPORTS > rootport)
    {
        return( ehci_RootDeviceAddress[ rootport ] );
    }
    return( USB_HCI_NODEVICE );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciGetDeviceAddressOfRootpoot
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciSetDeviceAddressOfRootpoot
 *
 *  Description:    The device address of EHCI route port is set.
 *
 *  Parameters:     uint16_t rootport ; rootport no
 *                  uint16_t devaddr  ; device address
 *
 *  Return Value:   uint16_t          ; device address
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_EhciSetDeviceAddressOfRootpoot( uint16_t rootport, uint16_t deviceaddr )
{
    USB_HCI_DEVICE      *devinfo;

    if(USB_EHCI_MAXROOTPORTS <= rootport)
    {
        return( USB_HCI_NODEVICE );
    }

    if(ehci_RootDeviceAddress[rootport] != 0)
    {
        return( USB_HCI_NODEVICE );
    }

    /* The device address of device information is updated */
    devinfo = r_usb_hstd_HciGetDeviceInformation( ehci_RootDeviceAddress[ rootport ] );
    if(devinfo == NULL)
    {
        return( USB_HCI_NODEVICE );
    }
    devinfo->bit.devnum = deviceaddr;

    ehci_RootDeviceAddress[ rootport ] = deviceaddr;

    return( deviceaddr );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciSetDeviceAddressOfRootpoot
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciGetTransferEndStatus
 *
 *  Description:    Getting of EHCI Transfer End Status
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req ; transfer request pointer
 *
 *  Return Value:   uint16_t               ; USB Standard F/W Transfer End Status
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_EhciGetTransferEndStatus( USB_HCI_TR_REQ *tr_req )
{
    USB_EHCI_TRANSFER_INFO  status;
    uint16_t                ret = USB_DATA_ERR;

    if(tr_req != NULL)
    {
        status.DWORD = tr_req->status;

        if(tr_req->bit.enable == FALSE)
        {
            ret = USB_DATA_STOP;
        }
        else if(tr_req->bit.eptype == USB_EP_ISO)
        {
            if(status.BIT.Status_Halted == 1)
            {
            }
            else if(status.BIT.Status_Data_Buffer_Error == 1)
            {
            }
            else if(status.BIT.Status_Babble_Detected == 1)
            {
            }
            else if(status.BIT.Status_Transaction_Error == 1)
            {
            }
//            else if(status.BIT.Status_Missed_Micro_Frame == 1)
//            {
//            }
            else
            {
                /* For isochronous */
                if(tr_req->bit.direction == USB_HCI_DIRECTION_OUT)
                {
                    ret = USB_DATA_WRITING;
                }
                else
                {
                    ret = USB_DATA_READING;
                }
            }
        }
        else
        {
            if(status.BIT.Status_Halted == 1)
            {
                ret = USB_DATA_STOP;
                if(status.BIT.CERR == 0)
                {
                }
                else if(status.BIT.Status_Data_Buffer_Error == 1)
                {
                }
                else if(status.BIT.Status_Babble_Detected == 1)
                {
                }
                else if(status.BIT.Status_Transaction_Error == 1)
                {
                }
                else if(status.BIT.Status_Missed_Micro_Frame == 1)
                {
                }
                else
                {
                    if(status.BIT.CERR == 3)
                    {
                        /* For STALL */
                        ret = USB_DATA_STALL;
                    }
                }
            }
            else
            {
                if(tr_req->bit.eptype == USB_EP_CNTRL)
                {
                    /* For control */
                    ret = USB_CTRL_END;
                }
                else
                {
                    if(tr_req->bit.direction == USB_HCI_DIRECTION_OUT)
                    {
                        /* When the data sending ends normally */
                        ret = USB_DATA_NONE;
                    }
                    else
                    {
                        if(tr_req->actual_size > tr_req->trsize)
                        {
                            /* When receive data is size over */
                            ret = USB_DATA_OVR;
                        }
                        else if(tr_req->actual_size < tr_req->trsize)
                        {
                            /* When receive data is short size */
                            ret = USB_DATA_SHT;
                        }
                        else
                        {
                            /* When the data reception ends normally */
                            ret = USB_DATA_OK;
                        }
                    }
                }
            }
        }
    }
    return( ret );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciGetTransferEndStatus
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciPortSuspend
 *
 *  Description:    EHCI Port Suspend
 *
 *  Parameters:     uint16_t port ; port no
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciPortSuspend( uint16_t port )
{
    if(USB_EHCI_MAXROOTPORTS <= port)
    {
        USB_HCI_PRINTF1_R( "usb_hstd_EhciPortSuspend Error: Illegal port no(%d)\n", port );
        return;
    }

    USB_HOST->PORTSC1.BIT.WKOC_E      = 1;    /* Over-Current Detect Enable */
    USB_HOST->PORTSC1.BIT.WKDSCNNT_E  = 1;    /* DisConnect Enable */
    USB_HOST->PORTSC1.BIT.WKCNNT_E    = 1;    /* Device Connect Enable */
    USB_HOST->PORTSC1.BIT.Suspend     = 1;    /* Set Suspend */
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciPortSuspend
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciPortResume
 *
 *  Description:    EHCI Port Resume
 *
 *  Parameters:     uint16_t port ; port no
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciPortResume( uint16_t port )
{
    if(USB_EHCI_MAXROOTPORTS <= port)
    {
        USB_HCI_PRINTF1_R( "usb_hstd_EhciPortResume Error: Illegal port no(%d)\n", port );
        return;
    }

    if((USB_HOST->PORTSC1.BIT.Suspend == 1) && (USB_HOST->PORTSC1.BIT.PortEnabledDisabled == 1))
    {
        /* Set Force Port Resume */
        USB_HOST->PORTSC1.BIT.ForcePortResume    = 1;
        r_usb_hstd_HciWaitTime(20);
        do
        {
            /* Set Force Port Resume */
            USB_HOST->PORTSC1.BIT.ForcePortResume    = 0;
            r_usb_hstd_HciWaitTime(1);
        } while ( ( USB_HOST->PORTSC1.BIT.Suspend != 0 ) && ( USB_HOST->PORTSC1.BIT.PortEnabledDisabled != 0 ) );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciPortResume
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciCancelTransferRequest
 *
 *  Description:    EHCI Chancel Transfer Request
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req ; Transfer Request Address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciCancelTransferRequest( USB_HCI_TR_REQ *tr_req )
{
    USB_EHCI_QH         *qh;
    USB_EHCI_ITD        *itd;
    USB_EHCI_SITD       *sitd;
    uint32_t            n;

    if(tr_req == NULL)
    {
        return;
    }

    if(tr_req->hci_info != NULL)
    {
        if(tr_req->bit.eptype == USB_EP_ISO)
        {
            if(tr_req->devinfo->bit.devspeed == USB_HCI_DEVSPEED_HS)
            {
                itd = ( USB_EHCI_ITD * )tr_req->hci_info;
                /* inactivate itd */
                for(n = 0; n < 8; n++)
                {
                    itd->Transaction[ n ].BIT.Status_Active = 0;
                }
            }
            else
            {
                sitd = ( USB_EHCI_SITD * )tr_req->hci_info;
                /* inactivate sitd */
                sitd->State.BIT.Status_Active = 0;
            }
        }
        else
        {
            qh = ( USB_EHCI_QH * )tr_req->hci_info;
            /* inactivate qh */
            if(qh->qtd_head != NULL)
            {
                /* inactive qtd */
                usb_hstd_EhciInactiveQtd( qh->qtd_head );
            }
            qh->Transfer_Info.BIT.Status_Active = 0;

            /* delete qtd */
            if(qh->qtd_head != NULL)
            {
                usb_hstd_EhciClearQtd( qh->qtd_head );
                qh->qtd_head = NULL;
            }
        }
    }

    /* delete tr-req */
    tr_req->bit.enable = FALSE;
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciCancelTransferRequest
 **********************************************************************************************************************/

/* Static Function */
/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciHwReset
 *
 *  Description:    Reset EHCI H/W
 *
 *  Parameters:     void
 *
 *  Return Value:   uint32_t ; status
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_EhciHwReset( void )
{
    uint32_t        timeout;

    /* ========== */
    /*  Stop eHC  */
    /* ========== */
    USB_HOST->USBCMD.BIT.RS = 0;               /* Clear Run/Stop bit. Stop HC */

    timeout = 0;
    while(USB_HOST->USBSTS.BIT.HCHalted == 0)  /* Wait Halted == 1 */
    {
        if(timeout > USB_EHCI_TIMEOUT)
        {
            USB_HCI_PRINTF0_R( "Error : usb_hstd_EhciInit TIMEOUT\n" );
            return( USB_ERROR );
        }
        r_usb_hstd_HciWaitTime( 1 );
        timeout++;
    }

    /* =========== */
    /*  Reset eHC  */
    /* =========== */
    USB_HOST->USBCMD.BIT.HCRESET = 1;          /* Reset */

    timeout = 0;
    while(USB_HOST->USBCMD.BIT.HCRESET == 1)
    {
        if(timeout > USB_EHCI_TIMEOUT)
        {
            USB_HCI_PRINTF0_R( "Error : usb_hstd_EhciInit TIMEOUT\n" );
            return( USB_ERROR );
        }
        r_usb_hstd_HciWaitTime( 1 );
        timeout++;
    }

    return( USB_OK );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciHwReset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciSetPortRoute
 *
 *  Description:    Set Port Routing
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciSetPortRoute( void )
{
    uint32_t    n_ports;
    uint32_t    n;

    /* =============== */
    /*  Set Ownership  */
    /* =============== */
    n_ports = USB_HOST->HCSPARAMS.BIT.N_PORTS;

    for(n = 0; n < n_ports; n++)
    {
        USB_HOST->PORTSC1.BIT.PortOwner = 0;    /* Port Owner : EHCI */
        USB_HOST->PORTSC1.BIT.PP        = 0;    /* Port Power : OFF */

        if(USB_HOST->PORTSC1.BIT.OvercurrentChange == 1)
        {
            USB_HOST->PORTSC1.BIT.OvercurrentChange = 1;   /* Clear Over-current */
        }

        r_usb_hstd_HciWaitTime(100);     /* Wait port power stabilization time */
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciSetPortRoute
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciPortEnable
 *
 *  Description:    EHCI Port Enable
 *
 *  Parameters:     uint32_t portnum ; port no
 *
 *  Return Value:   uint32_t *hs_enable_flag ; HS Device Enable Flag pointer
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_EhciPortEnable( uint32_t portnum, uint32_t *hs_enable_flag )
{
    *hs_enable_flag = FALSE;

    /* Device existence confirmation */
    if(USB_HOST->PORTSC1.BIT.CurrentConnectStatus == 0)
    {
        return( FALSE );
    }

    /* For Low-Speed Device */
    if(USB_HOST->PORTSC1.BIT.LineStatus == USB_EHCI_LINE_STATE_K)
    {
        return( TRUE );
    }

    /* Port Reset */
    if(FALSE == usb_hstd_EhciPortReset(portnum))
    {
        return( FALSE );
    }

    /* Device existence confirmation */
    if(USB_HOST->PORTSC1.BIT.CurrentConnectStatus == 0)
    {
        return( FALSE );
    }

    /* HS Device Enable confirmation */
    if(USB_HOST->PORTSC1.BIT.PortEnabledDisabled == 1)
    {
        *hs_enable_flag = TRUE;
    }

    return( TRUE );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciPortEnable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciDeletePeriodicSchedulingScore
 *
 *  Description:    Delete Periodic Scheduling Score
 *
 *  Parameters:     uint32_t max_period ; max period
 *                  uint32_t pollrate   ; poll-rate
 *                  uint32_t            ; poll-rate offset
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciDeletePeriodicSchedulingScore( uint32_t max_period, uint32_t pollrate, uint32_t pollrate_offset )
{
    uint32_t    uframe_list_size;
    uint32_t    n;
    uint32_t    j;

    /* Get micro frame list size */
    uframe_list_size = usb_hstd_EhciGetFrameListSize();
    uframe_list_size *= 8;

    /* Update of score */
    for(n = pollrate_offset; n < uframe_list_size; n += pollrate)
    {
        for(j = 0; j < max_period; j++)
        {
            if(ehci_PeriodicSchedulingScore[n + j] != 0)
            {
                ehci_PeriodicSchedulingScore[ n + j ]--;
            }
            else
            {
                USB_HCI_PRINTF0_R( "Error: Can't delete Periodic Scheduling Score\n" );
            }
        }
    }

#ifdef DEBUG_PRINT_PERIODIC_SCHEDULING
    usb_hstd_EhciPrintPeriodicSchedulingScore();
#endif
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciDeletePeriodicSchedulingScore
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciUnlinkPeriodic
 *
 *  Description:    Unlink data structure from periodic frame list
 *
 *  Parameters:     USB_EHCI_FLEP *data ; data structure pointer
 *                  uint32_t elementnum ; periodic frame list no
 *
 *  Return Value:   uint32_t status     ; unlink flag
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_EhciUnlinkPeriodic( USB_EHCI_FLEP *data, uint32_t elementnum )
{
    uint32_t        periodic_list_addr;
    uint32_t        tmp_addr;
    USB_EHCI_FLEP   *current_element;

    periodic_list_addr = USB_HOST->PERIODICLIST.LONG & 0xFFFFF000;
    if(periodic_list_addr == 0x00000000)
    {
        USB_HCI_PRINTF0_R( "usb_hstd_EhciUnlinkPeriodic Error : PERIODICLISTBASE is not registered. \n" );
        return( 0 );
    }
    else
    {
//      periodic_list_addr = USB_HCI_CACHE_ADDR( periodic_list_addr );
        periodic_list_addr = USB_HCI_NONCACHE_ADDR( periodic_list_addr );
    }

    /* The address of the periodic frame list specified with element num is calculated.  */
    tmp_addr = elementnum * sizeof( uint32_t );
    tmp_addr &= 0x00000FFC;
    tmp_addr |= periodic_list_addr;
    current_element = ( USB_EHCI_FLEP * )tmp_addr;

    while(1)
    {
        if(current_element == NULL)
        {
            USB_HCI_PRINTF0_R( "usb_hstd_EhciUnlinkPeriodic Error: Current Element Pointer is NULL\n" );
            return( 0 );
        }

        if(current_element->BIT.T == 1)
        {
            break;
        }
//      if(USB_HCI_CACHE_ADDR(current_element->Address & 0xFFFFFFE0) == (uint32_t)data)
        if(USB_HCI_NONCACHE_ADDR(current_element->Address & 0xFFFFFFE0) == (uint32_t)data)
        {
            /* The value of the next link pointer of qh/itd/sitd is set */
            *current_element = *data;
            return( 1 );
        }
        else
        {
            /* The nest qh/itd/sitd is retrieved referring to the next link pointer.  */
//          current_element = ( USB_EHCI_FLEP * )USB_HCI_CACHE_ADDR( current_element->Address & 0xFFFFFFE0 );
            current_element = ( USB_EHCI_FLEP * )USB_HCI_NONCACHE_ADDR( current_element->Address & 0xFFFFFFE0 );
        }
    }
    return( 0 );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciUnlinkPeriodic
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciClearDeviceTrreq
 *
 *  Description:    EHCI Clear transfer request for disconnected device
 *
 *  Parameters:     uint32_t devadd ; Device Address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciClearDeviceTrreq( uint32_t devadd )
{
    uint8_t     n;

    for(n = 0; n < USB_HCI_TRREQ_NUM; n++)
    {
        if((usb_ghstd_HciTransferRequest[n].bit.enable == 1) && (usb_ghstd_HciTransferRequest[n].bit.devadrs == devadd))
        {
            usb_hstd_EhciCancelTransferRequest( &usb_ghstd_HciTransferRequest[ n ] );
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciClearDeviceTrreq
 **********************************************************************************************************************/

#ifdef DEBUG_PRINT_PORT_INFORMATION
/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciPrintPortInformation
 *
 *  Description:    EHCI Port Information Print
 *
 *  Parameters:     None
 *
 *  Return Value:   void
 *
 *  Note:           This function is used for debugging.
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciPrintPortInformation(void)
{
    USB_HCI_PRINTF0( "-------------------------------\n" );
    USB_HCI_PRINTF1( "  EHCI Port No.%d Information\n", 0 );
    USB_HCI_PRINTF0( "-------------------------------\n" );
//  USB_HCI_PRINTF1( "WKOC_E                     : %d\n", USB_HOST->PORTSC1.BIT.WKOC_E );
//  USB_HCI_PRINTF1( "WKDSCNNT_E                 : %d\n", USB_HOST->PORTSC1.BIT.WKDSCNNT_E );
//  USB_HCI_PRINTF1( "WKCNNT_E                   : %d\n", USB_HOST->PORTSC1.BIT.WKCNNT_E );
//  USB_HCI_PRINTF1( "Port_Test_Control          : %d\n", USB_HOST->PORTSC1.BIT.PortTestControl );
//  USB_HCI_PRINTF1( "Port_IndicatorControl      : %d\n", USB_HOST->PORTSC1.BIT.PortIndicatorControl );
    USB_HCI_PRINTF1( "Port_Owner                 : %d\n", USB_HOST->PORTSC1.BIT.PortOwner );
    USB_HCI_PRINTF1( "PP                         : %d\n", USB_HOST->PORTSC1.BIT.PP );
    USB_HCI_PRINTF1( "Line_Status                : %d\n", USB_HOST->PORTSC1.BIT.LineStatus );
    USB_HCI_PRINTF1( "Port_Reset                 : %d\n", USB_HOST->PORTSC1.BIT.PortReset );
    USB_HCI_PRINTF1( "Suspend                    : %d\n", USB_HOST->PORTSC1.BIT.Suspend );
    USB_HCI_PRINTF1( "Force_Port_Resume          : %d\n", USB_HOST->PORTSC1.BIT.ForcePortResume );
    USB_HCI_PRINTF1( "Over_Current_Change        : %d\n", USB_HOST->PORTSC1.BIT.OvercurrentChange );
    USB_HCI_PRINTF1( "Over_Current_Active        : %d\n", USB_HOST->PORTSC1.BIT.OvercurrentActive );
    USB_HCI_PRINTF1( "Port_Enable_Disable_Change : %d\n", USB_HOST->PORTSC1.BIT.PortEnableDisableChange );
    USB_HCI_PRINTF1( "Port_Enabled               : %d\n", USB_HOST->PORTSC1.BIT.PortEnabledDisabled );
    USB_HCI_PRINTF1( "Connect_Status_Change      : %d\n", USB_HOST->PORTSC1.BIT.ConnectStatusChange );
    USB_HCI_PRINTF1( "Current_Connect_Status     : %d\n", USB_HOST->PORTSC1.BIT.CurrentConnectStatus );
    USB_HCI_PRINTF0( "\n" );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciPrintPortInformation
 **********************************************************************************************************************/
#endif

#ifdef DEBUG_PRINT_ASYNC_SCHEDULING
/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciPrintAsyncScheduling
 *
 *  Description:    Asynch scheduling print
 *
 *  Parameters:     USB_EHCI_QH *qh ; QH pointer
 *
 *  Return Value:   void
 *
 *  Note:           This function is used for debugging.
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciPrintAsyncScheduling( USB_EHCI_QH *h_qh )
{
    static USB_EHCI_QH      *keep_h_qh = NULL;
    USB_EHCI_QH             *qh;
    uint32_t                cnt = 0;

    if(h_qh != NULL)
    {
        keep_h_qh = h_qh;
    }

    USB_HCI_PRINTF0( "\n--------------------------------------- Async Scheduling Start \n" );
    qh = keep_h_qh;
    if(qh == NULL)
    {
        return;
    }
    else
    {
        while(1)
        {
            USB_HCI_PRINTF1( "0x%X", ( uint32_t )qh );
            if(qh->Endpoint1.BIT.H == 1)
            {
                USB_HCI_PRINTF0( " H=1" );
                cnt++;
                if(cnt == 2)
                {
                    USB_HCI_PRINTF0( "\n" );
                    break;
                }
            }
            USB_HCI_PRINTF0( "\n" );
            qh = ( USB_EHCI_QH * )USB_HCI_CACHE_ADDR( qh->Queue_Head_Horizontal_Link.Address & 0xFFFFFFE0 );
        }
    }

    USB_HCI_PRINTF0( "----------------------------------------- Async Scheduling End \n\n" );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciPrintAsyncScheduling
 **********************************************************************************************************************/
#endif

#ifdef DEBUG_PRINT_PERIODIC_SCHEDULING
/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciPrintPeriodicSchedulingList
 *
 *  Description:    Print EHCI Periodic Scheduling List
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 *  Note:           This function is used for debugging.
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciPrintPeriodicSchedulingList( void )
{
    uint32_t                frame_list_size;
    uint32_t                n;
    uint32_t                periodic_list_addr;
    uint32_t                tmp_addr;
    USB_EHCI_FLEP           *listbase;
    volatile USB_EHCI_FLEP  *current_element;

    /* Get frame list size */
    frame_list_size = usb_hstd_EhciGetFrameListSize();


    periodic_list_addr = USB_HOST->PERIODICLIST.LONG & 0xFFFFF000;
    if(periodic_list_addr == 0x00000000)
    {
        USB_HCI_PRINTF0_R( "usb_hstd_EhciPrintPeriodicSchedulingList Error : PERIODICLISTBASE is not registered. \n" );
        return;
    }
    else if(periodic_list_addr != 0x00000000)
    {
//      periodic_list_addr = USB_HCI_CACHE_ADDR( periodic_list_addr );
        periodic_list_addr = USB_HCI_NONCACHE_ADDR( periodic_list_addr );
    }

    listbase = ( USB_EHCI_FLEP * )periodic_list_addr;
    for(n = 0; n < frame_list_size; n++)
    {
        current_element = &listbase[ n ];
        USB_HCI_PRINTF1( "FLEP(%4d):", n );
        while (1)
        {
            if(current_element == NULL)
            {
                USB_HCI_PRINTF0_R( "usb_hstd_EhciPrintPeriodicSchedulingList Error: Current Element Pointer is NULL\n" );
                return;
            }

            if(current_element->BIT.T == 1)
            {
                break;
            }

//          tmp_addr = USB_HCI_CACHE_ADDR( current_element->Address & 0xFFFFFFE0 );
            tmp_addr = USB_HCI_NONCACHE_ADDR( current_element->Address & 0xFFFFFFE0 );

            switch(current_element->BIT.Typ)
            {
                case USB_EHCI_TYP_ITD:
                    USB_HCI_PRINTF2( " (%d,%d)", ( ( USB_EHCI_ITD * )tmp_addr )->Buffer[0].BIT0.Device_Address, ( ( USB_EHCI_ITD * )tmp_addr )->Info.pollrate );
                    break;
                case USB_EHCI_TYP_QH:
                    USB_HCI_PRINTF2( " (%d,%d)", ( ( USB_EHCI_QH * )tmp_addr )->Endpoint1.BIT.Device_Address, ( ( USB_EHCI_QH * )tmp_addr )->Info.pollrate );
                    break;
                case USB_EHCI_TYP_SITD:
                    USB_HCI_PRINTF2( " (%d,%d)", ( ( USB_EHCI_SITD * )tmp_addr )->Endpoint1.BIT.Device_Address, ( ( USB_EHCI_SITD * )tmp_addr )->Info.pollrate );
                    break;
                default:
                    break;
            }

            current_element = ( USB_EHCI_FLEP * )USB_HCI_CACHE_ADDR( current_element->Address & 0xFFFFFFE0 );
        }
        USB_HCI_PRINTF0( "\n" );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciPrintPeriodicSchedulingList
 **********************************************************************************************************************/
#endif

#ifdef DEBUG_PRINT_PERIODIC_SCHEDULING
/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciPrintPeriodicSchedulingScore
 *
 *  Description:    EHCI Periodic Scheduling Score Print
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 *  Note:           This function is used for debugging.
 *
 **********************************************************************************************************************/
static void usb_hstd_EhciPrintPeriodicSchedulingScore( void )
{
    uint32_t            uframe_list_size;
    uint32_t            n;

    /* Get micro frame list size */
    uframe_list_size = usb_hstd_EhciGetFrameListSize();
    uframe_list_size *= 8;

    for(n = 0; n < uframe_list_size; n++)
    {
        if(( n % 8 ) == 0)
        {
            USB_HCI_PRINTF1( "Score(%4d):", n / 8 );
        }
        USB_HCI_PRINTF1( " %d", ehci_PeriodicSchedulingScore[ n ] );
        if((n % 8) == 7)
        {
            USB_HCI_PRINTF0( "\n" );
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciPrintPeriodicSchedulingScore
 **********************************************************************************************************************/
#endif