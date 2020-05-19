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
 * FILE         :  r_usb_hEhciMemory.c
 * Description  :  EHCI Memory Control Code
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
void                usb_hstd_EhciInitQhMemory(void);
void                usb_hstd_EhciInitItdMemory(void);
void                usb_hstd_EhciInitSitdMemory(void);
void                usb_hstd_EhciInitQtdMemory(void);
void                usb_hstd_EhciInitPeriodicFrameList(void);
uint32_t            usb_gstd_EhciGetPeriodicFrameListAddr(void);
USB_EHCI_QH        *usb_hstd_EhciAllocQh(void);
USB_EHCI_ITD       *usb_hstd_EhciAllocItd(void);
USB_EHCI_SITD      *usb_hstd_EhciAllocSitd(void);
USB_EHCI_QTD       *usb_hstd_EhciAllocQtd(void);
void                usb_hstd_EhciFreeQtd(USB_EHCI_QTD *free_qtd);
USB_EHCI_QH        *usb_hstd_EhciSearchQh(uint32_t devadd, uint32_t epnum, uint32_t direction, uint32_t eptype);
USB_EHCI_ITD       *usb_hstd_EhciSearchItd(uint32_t devadd, uint32_t epnum, uint32_t direction);
USB_EHCI_SITD      *usb_hstd_EhciSearchSitd(uint32_t devadd, uint32_t epnum, uint32_t direction);
void                usb_hstd_EhciClearDeviceQh(uint32_t devadd);
void                usb_hstd_EhciClearQh(USB_EHCI_QH *qh);
void                usb_hstd_EhciClearDeviceItd(uint32_t devadd);
void                usb_hstd_EhciClearDeviceSitd(uint32_t devadd);


/***********************************************************************************************************************
 Variable
 **********************************************************************************************************************/
#ifdef __ICCARM__
#pragma location="EHCI_PFL"
static uint32_t         ehci_PeriodicFrameList[ USB_EHCI_PFL_SIZE ];    /* 4KByte alignment */
#pragma location="EHCI_QH"
static USB_EHCI_QH      ehci_Qh[ USB_EHCI_NUM_QH ];                     /* 32Byte alignment */
#pragma location="EHCI_QTD"
static USB_EHCI_QTD     ehci_Qtd[ USB_EHCI_NUM_QTD ];                   /* 32Byte alignment */
#pragma location="EHCI_ITD"
static USB_EHCI_ITD     ehci_Itd[ USB_EHCI_NUM_ITD ];                   /* 32Byte alignment */
#pragma location="EHCI_SITD"
static USB_EHCI_SITD    ehci_Sitd[ USB_EHCI_NUM_SITD ];                 /* 32Byte alignment */
#endif  /* __ICCARM__ */

#ifdef __GNUC__
static uint32_t         ehci_PeriodicFrameList[ USB_EHCI_PFL_SIZE ]     /* 4KByte alignment */
        __attribute__ ((section ("EHCI_PFL")));
static USB_EHCI_QH      ehci_Qh[ USB_EHCI_NUM_QH ]                      /* 32Byte alignment */
        __attribute__ ((section ("EHCI_QH")));
static USB_EHCI_QTD     ehci_Qtd[ USB_EHCI_NUM_QTD ]                    /* 32Byte alignment */
        __attribute__ ((section ("EHCI_QTD")));
static USB_EHCI_ITD     ehci_Itd[ USB_EHCI_NUM_ITD ]                    /* 32Byte alignment */
        __attribute__ ((section ("EHCI_ITD")));
static USB_EHCI_SITD    ehci_Sitd[ USB_EHCI_NUM_SITD ]                  /* 32Byte alignment */
        __attribute__ ((section ("EHCI_SITD")));
#endif  /* __GNUC__ */

#ifdef __CC_ARM
#pragma arm section zidata = "EHCI_PFL"
static uint32_t         ehci_PeriodicFrameList[ USB_EHCI_PFL_SIZE ];    /* 4KByte alignment */
#pragma arm section zidata
#pragma arm section zidata = "EHCI_QH"
static USB_EHCI_QH      ehci_Qh[ USB_EHCI_NUM_QH ];                     /* 32Byte alignment */
#pragma arm section zidata
#pragma arm section zidata = "EHCI_QTD"
static USB_EHCI_QTD     ehci_Qtd[ USB_EHCI_NUM_QTD ];                   /* 32Byte alignment */
#pragma arm section zidata
#pragma arm section zidata = "EHCI_ITD"
static USB_EHCI_ITD     ehci_Itd[ USB_EHCI_NUM_ITD ];                   /* 32Byte alignment */
#pragma arm section zidata
#pragma arm section zidata = "EHCI_SITD"
static USB_EHCI_SITD    ehci_Sitd[ USB_EHCI_NUM_SITD ];                 /* 32Byte alignment */
#pragma arm section zidata
#endif  /* __CC_ARM */


static USB_EHCI_QTD     *ehci_QtdTop;

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciInitQhMemory
 *
 *  Description:    Initialize QH
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciInitQhMemory( void )
{
    usb_hstd_HciLockResouce();

    memset( &ehci_Qh[ 0 ], 0, sizeof( ehci_Qh ) );

    usb_hstd_HciUnlockResouce();
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciInitQhMemory
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciInitItdMemory
 *
 *  Description:    Initialize iTD
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciInitItdMemory( void )
{
    usb_hstd_HciLockResouce();

    memset( &ehci_Itd[ 0 ], 0, sizeof( ehci_Itd ) );

    usb_hstd_HciUnlockResouce();
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciInitItdMemory
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciInitSitdMemory
 *
 *  Description:    Initialize siTD
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciInitSitdMemory( void )
{
    usb_hstd_HciLockResouce();

    memset( &ehci_Sitd[ 0 ], 0, sizeof( ehci_Sitd ) );

    usb_hstd_HciUnlockResouce();
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciInitSitdMemory
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciInitQtdMemory
 *
 *  Description:    Initialize qTD
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciInitQtdMemory( void )
{
    USB_EHCI_QTD    *qtd;
    uint32_t    n;

    usb_hstd_HciLockResouce();

    ehci_QtdTop = NULL;
    memset( &ehci_Qtd[ 0 ], 0, sizeof( ehci_Qtd ) );

    usb_hstd_HciUnlockResouce();

    qtd = &ehci_Qtd[ 0 ];
    for(n = 0; n < USB_EHCI_NUM_QTD; n++, qtd++)
    {
        usb_hstd_EhciFreeQtd( qtd );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciInitQtdMemory
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciInitPeriodicFrameList
 *
 *  Description:    Initialize Periodic Frame List
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciInitPeriodicFrameList( void )
{
    uint32_t        *list;
    uint32_t        n;

    list = &ehci_PeriodicFrameList[ 0 ];
    for(n = 0; n < USB_EHCI_PFL_SIZE; n++)
    {
        *list++ = 0x00000001;
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciInitPeriodicFrameList
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_gstd_EhciGetPeriodicFrameListAddr
 *
 *  Description:    Get Periodic Frame List Address
 *
 *  Parameters:     void
 *
 *  Return Value:   uint32_t ; Periodic Frame List Address
 *
 **********************************************************************************************************************/
uint32_t usb_gstd_EhciGetPeriodicFrameListAddr( void )
{
    return( ( uint32_t )&ehci_PeriodicFrameList[ 0 ] );
}
/***********************************************************************************************************************
 End of function usb_gstd_EhciGetPeriodicFrameListAddr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciAllocQh
 *
 *  Description:    Allocate QH
 *
 *  Parameters:     void
 *
 *  Return Value:   USB_EHCI_QH* ; QH Address
 *
 **********************************************************************************************************************/
USB_EHCI_QH* usb_hstd_EhciAllocQh( void )
{
    USB_EHCI_QH     *ret_qh = NULL;
    USB_EHCI_QH     *qh;
    uint32_t        n;

    usb_hstd_HciLockResouce();

    qh = &ehci_Qh[ 0 ];
    for(n = 0; n < USB_EHCI_NUM_QH; n++, qh++)
    {
        if(qh->Info.enable == FALSE)
        {
            qh->Info.enable = TRUE;
            qh->Next_qTD.Address = 0x00000001;
            qh->Alternate_Next_qTD.Address = 0x00000001;
            qh->qtd_head = NULL;
            qh->qtd_end = NULL;

            ret_qh = qh;
            break;
        }
    }

    usb_hstd_HciUnlockResouce();

    if(ret_qh == NULL)
    {
        USB_HCI_PRINTF0_R( "----------------------------------------------\n" );
        USB_HCI_PRINTF0_R( "Memory Allocation Error: usb_hstd_EhciAllocQh\n" );
        USB_HCI_PRINTF0_R( "----------------------------------------------\n" );
    }
    return( ret_qh );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciAllocQh
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciAllocItd
 *
 *  Description:    Allocate iTD
 *
 *  Parameters:     void
 *
 *  Return Value:   USB_EHCI_ITD* ; ITD Address
 *
 **********************************************************************************************************************/
USB_EHCI_ITD* usb_hstd_EhciAllocItd( void )
{
    USB_EHCI_ITD    *ret_itd = NULL;
    USB_EHCI_ITD    *itd;
    uint32_t        n;

    usb_hstd_HciLockResouce();

    itd = &ehci_Itd[ 0 ];
    for(n = 0; n < USB_EHCI_NUM_ITD; n++, itd++)
    {
        if(itd->Info.enable == FALSE)
        {
            itd->Info.enable = TRUE;

            ret_itd = itd;
            break;
        }
    }

    usb_hstd_HciUnlockResouce();

    if(ret_itd == NULL)
    {
        USB_HCI_PRINTF0_R( "-----------------------------------------------\n" );
        USB_HCI_PRINTF0_R( "Memory Allocation Error: usb_hstd_EhciAllocItd\n" );
        USB_HCI_PRINTF0_R( "-----------------------------------------------\n" );
    }

    return( ret_itd );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciAllocItd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciAllocSitd
 *
 *  Description:    Allocate siTD
 *
 *  Parameters:     void
 *
 *  Return Value:   USB_EHCI_SITD* ; SITD Address
 *
 **********************************************************************************************************************/
USB_EHCI_SITD* usb_hstd_EhciAllocSitd( void )
{
    USB_EHCI_SITD   *ret_sitd = NULL;
    USB_EHCI_SITD   *sitd;
    uint32_t        n;

    usb_hstd_HciLockResouce();

    sitd = &ehci_Sitd[ 0 ];
    for(n = 0; n < USB_EHCI_NUM_SITD; n++, sitd++)
    {
        if(sitd->Info.enable == FALSE)
        {
            sitd->Info.enable = TRUE;

            ret_sitd = sitd;
            break;
        }
    }
    usb_hstd_HciUnlockResouce();

    if(ret_sitd == NULL)
    {
        USB_HCI_PRINTF0_R( "------------------------------------------------\n" );
        USB_HCI_PRINTF0_R( "Memory Allocation Error: usb_hstd_EhciAllocSitd\n" );
        USB_HCI_PRINTF0_R( "------------------------------------------------\n" );
    }

    return( ret_sitd );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciAllocSitd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciAllocQtd
 *
 *  Description:    Allocate qTD
 *
 *  Parameters:     void
 *
 *  Return Value:   USB_EHCI_QTD* ; QTD Address
 *
 **********************************************************************************************************************/
USB_EHCI_QTD* usb_hstd_EhciAllocQtd( void )
{
    USB_EHCI_QTD    *ret_qtd = NULL;

    usb_hstd_HciLockResouce();

    if(ehci_QtdTop != NULL)
    {
        ret_qtd = ehci_QtdTop;

        ehci_QtdTop = ( USB_EHCI_QTD * )ehci_QtdTop->Next_qTD.Address;
    }

    usb_hstd_HciUnlockResouce();

    if(ret_qtd == NULL)
    {
        USB_HCI_PRINTF0_R( "----------------------------------------------\n" );
        USB_HCI_PRINTF0_R( "Memory Allocation Error: usb_hstd_EhciAllocQtd\n" );
        USB_HCI_PRINTF0_R( "----------------------------------------------\n" );
    }

    return( ret_qtd );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciAllocQtd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciFreeQtd
 *
 *  Description:    Free qTD
 *
 *  Parameters:     USB_EHCI_QTD *free_qtd ; QTD Address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciFreeQtd( USB_EHCI_QTD *free_qtd )
{
    usb_hstd_HciLockResouce();

    free_qtd->Next_qTD.Address = ( uint32_t )ehci_QtdTop;

    ehci_QtdTop = free_qtd;

    usb_hstd_HciUnlockResouce();
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciFreeQtd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciSearchQh
 *
 *  Description:    Search QH
 *
 *  Parameters:     uint32_t devadd       ; Device Address
 *                  uint32_t epnum        ; Endpoint Number
 *                  uint32_t direction    ; Direction
 *                  uint32_t eptype       ; Endpoint Type
 *
 *  Return Value:   USB_EHCI_QH*          ; QH Address
 *
 **********************************************************************************************************************/
USB_EHCI_QH* usb_hstd_EhciSearchQh( uint32_t devadd, uint32_t epnum, uint32_t direction, uint32_t eptype )
{
    USB_EHCI_QH     *ret_qh = NULL;
    USB_EHCI_QH     *qh;
    uint32_t        n;

    qh = &ehci_Qh[ 1 ];
    for(n = 1; n < USB_EHCI_NUM_QH; n++, qh++)
    {
        if(qh->Info.enable == TRUE)
        {
            if((qh->Endpoint1.BIT.Device_Address == devadd) && (qh->Endpoint1.BIT.Endpt == epnum))
            {
                if((eptype == USB_EP_CNTRL) || (qh->Info.direction == direction))
                {
                    ret_qh = qh;
                }
            }
        }
    }
    return( ret_qh );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciSearchQh
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciSearchItd
 *
 *  Description:    Search ITD
 *
 *  Parameters:     uint32_t devadd       ; Device Address
 *                  uint32_t epnum        ; Endpoint Number
 *                  uint32_t direction    ; Direction
 *
 *  Return Value:   USB_EHCI_ITD*         ; ITD Address
 *
 **********************************************************************************************************************/
USB_EHCI_ITD* usb_hstd_EhciSearchItd( uint32_t devadd, uint32_t epnum, uint32_t direction )
{
    USB_EHCI_ITD    *ret_itd = NULL;
    USB_EHCI_ITD    *itd;
    uint32_t        n;

    itd = &ehci_Itd[ 0 ];
    for(n = 0; n < USB_EHCI_NUM_ITD; n++, itd++)
    {
        if(itd->Info.enable == TRUE)
        {
            if ( ( itd->Buffer[ 0 ].BIT0.Device_Address == devadd )
                && ( itd->Buffer[ 0 ].BIT0.Endpt == epnum )
                && (itd->Buffer[1].BIT1.Direction == direction))
            {
                ret_itd = itd;
            }
        }
    }
    return( ret_itd );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciSearchItd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciSearchSitd
 *
 *  Description:    Search SITD
 *
 *  Parameters:     uint32_t devadd       ; Device Address
 *                  uint32_t epnum        ; Endpoint Number
 *                  uint32_t direction    ; Direction
 *
 *  Return Value:   USB_EHCI_SITD*        ; SITD Address
 *
 **********************************************************************************************************************/
USB_EHCI_SITD* usb_hstd_EhciSearchSitd( uint32_t devadd, uint32_t epnum, uint32_t direction )
{
    USB_EHCI_SITD   *ret_sitd = NULL;
    USB_EHCI_SITD   *sitd;
    uint32_t        n;

    sitd = &ehci_Sitd[ 0 ];
    for(n = 0; n < USB_EHCI_NUM_SITD; n++, sitd++)
    {
        if(sitd->Info.enable == TRUE)
        {
            if ( ( sitd->Endpoint1.BIT.Device_Address == devadd )
                && ( sitd->Endpoint1.BIT.Endpt == epnum )
                && (sitd->Endpoint1.BIT.Direction == direction))
            {
                ret_sitd = sitd;
            }
        }
    }
    return( ret_sitd );
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciSearchSitd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciClearDeviceQh
 *
 *  Description:    Clear QH for disconnected device
 *
 *  Parameters:     uint32_t devadd ; Device Address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciClearDeviceQh( uint32_t devadd )
{
    USB_EHCI_QH     *qh;
    uint32_t        n;

    qh = &ehci_Qh[ 1 ];
    for(n = 1; n < USB_EHCI_NUM_QH; n++, qh++)
    {
        if(qh->Info.enable == TRUE)
        {
            if ( qh->Endpoint1.BIT.Device_Address == devadd ) {
                usb_hstd_EhciClearQh( qh );
            }
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciClearDeviceQh
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciClearQh
 *
 *  Description:    Clear QH
 *
 *  Parameters:     USB_EHCI_QH *qh ; QH Address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciClearQh( USB_EHCI_QH *qh )
{
    if(qh != NULL)
    {
        if(qh->Info.enable == TRUE)
        {
            /* Unlink qh */
            if(qh->Info.pollrate != 0)
            {
                /* interrupt */
                usb_hstd_EhciUnlinkQhForPeriodic( qh );
            }
            else
            {
                /* control/bulk */
                usb_hstd_EhciUnlinkQhForAsync( qh );
            }
            /* clear qh( enable = FALSE ) */
            memset( qh, 0, sizeof( USB_EHCI_QH ) );
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciClearQh
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciClearDeviceItd
 *
 *  Description:    Clear ITD for disconnected device
 *
 *  Parameters:     uint32_t devadd ; Device Address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciClearDeviceItd( uint32_t devadd )
{
    USB_EHCI_ITD    *itd;
    uint32_t        n;

    itd = &ehci_Itd[ 0 ];
    for(n = 0; n < USB_EHCI_NUM_ITD; n++, itd++)
    {
        if(itd->Info.enable == TRUE)
        {
            if(itd->Buffer[0].BIT0.Device_Address == devadd)
            {
                /* Unlink itd */
                usb_hstd_EhciUnlinkItd( itd );
                /* clear itd( enable = FALSE ) */
                memset( itd, 0, sizeof( USB_EHCI_ITD ) );
            }
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciClearDeviceItd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_EhciClearDeviceSitd
 *
 *  Description:    Clear SITD for disconnected device
 *
 *  Parameters:     uint32_t devadd ; Device Address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_EhciClearDeviceSitd( uint32_t devadd )
{
    USB_EHCI_SITD   *sitd;
    uint32_t        n;

    sitd = &ehci_Sitd[ 0 ];
    for(n = 0; n < USB_EHCI_NUM_SITD; n++, sitd++)
    {
        if(sitd->Info.enable == TRUE)
        {
            if(sitd->Endpoint1.BIT.Device_Address == devadd)
            {
                /* Unlink sitd */
                usb_hstd_EhciUnlinkSitd( sitd );
                /* clear sitd( enable = FALSE ) */
                memset( sitd, 0, sizeof( USB_EHCI_SITD ) );
            }
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EhciClearDeviceSitd
 **********************************************************************************************************************/