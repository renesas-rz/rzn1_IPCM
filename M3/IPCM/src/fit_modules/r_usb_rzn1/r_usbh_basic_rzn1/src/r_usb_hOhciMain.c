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
 * FILE         :  r_usb_hOhciMain.c
 * Description  :  USB OHCI Main Code
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2020. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_usb_hHciLocal.h"

/***********************************************************************************************************************
 Prototype
 **********************************************************************************************************************/
/* Global function */
uint32_t                usb_hstd_OhciInit(void);
void                    usb_hstd_OhciDeinit(void);
void                    usb_hstd_OhciInterruptHandler(void);
void                    usb_hstd_OhciControlRoothub(void);
void                    usb_hstd_OhciDisconnect(uint32_t devadd);
uint16_t                usb_hstd_OhciGetDeviceAddressOfRootpoot(uint16_t rootport);
uint16_t                usb_hstd_OhciSetDeviceAddressOfRootpoot(uint16_t rootport, uint16_t deviceaddr);
void                    usb_hstd_OhciPortReset(uint32_t portnum);
uint16_t                usb_hstd_OhciGetPidStatus(USB_HCI_TR_REQ *tr_req);
void                    usb_hstd_OhciPortSuspend(uint16_t port);
void                    usb_hstd_OhciPortResume(uint16_t port);
uint16_t                usb_hstd_OhciGetTransferEndStatus(USB_HCI_TR_REQ *tr_req);
uint32_t                usb_hstd_OhciRemoveEndpoint(uint8_t device_address, uint8_t endpoint_number, uint8_t direction, boolean_t free_ed);
uint32_t                usb_hstd_OhciPauseEndpoint(uint8_t device_address, uint8_t endpoint_number, uint8_t direction);
USB_OHCI_LIST_ENTRY_P  usb_hstd_OhciRemoveListHead(USB_OHCI_LIST_ENTRY_P list);
void                    usb_hstd_OhciRemoveListEntry(USB_OHCI_LIST_ENTRY_P list);
void                    usb_hstd_OhciInitializeListHead(USB_OHCI_LIST_ENTRY_P list);
uint32_t                usb_hstd_OhciIsListEmpty(USB_OHCI_LIST_ENTRY_P list);
void                    usb_hstd_OhciInsertHeadList(USB_OHCI_LIST_ENTRY_P list_head, USB_OHCI_LIST_ENTRY_P link);
void                    usb_hstd_OhciInsertTailList(USB_OHCI_LIST_ENTRY_P list_head, USB_OHCI_LIST_ENTRY_P link);
uint32_t                usb_hstd_OhciPhysicalAddressOf(void *data);
void                    usb_hstd_OhciPauseEd(USB_OHCI_HCD_ENDPOINT_P endpoint);
void                    usb_hstd_OhciUnscheduleIsochronousOrInterruptEndpoint(USB_OHCI_HCD_ENDPOINT_P endpoint, boolean_t free_ed, boolean_t endpoint_processing_required);
uint32_t                usb_hstd_OhciSetFrameInterval(USB_OHCI_HCD_DEVICE_DATA_P device_data, boolean_t up_not_down);
uint32_t                usb_hstd_OhciGet32BitFrameNumber(USB_OHCI_HCD_DEVICE_DATA_P device_data);
uint32_t                usb_hstd_OhciCheckBandwidth(USB_OHCI_HCD_DEVICE_DATA_P device_data, uint32_t list, uint32_t *best_list);

/* Static function */
static void usb_hstd_OhciHwSetup( void );
static uint32_t usb_hstd_OhciHwReset( void );
static void usb_hstd_OhciInitailizeInterruptLists( USB_OHCI_HCD_DEVICE_DATA_P device_data );
static void usb_hstd_OhciClearHcca( USB_OHCI_HCD_DEVICE_DATA_P device_data );
static void usb_hstd_OhciClearDeviceTrreq( uint32_t devadd );
static void usb_hstd_OhciRootPortConnection( USB_OHCI_HCD_DEVICE_DATA_P devicedata, uint8_t devspeed, uint8_t portnum );
static void usb_hstd_OhciRootPortDisconnection( USB_OHCI_HCD_DEVICE_DATA_P devicedata, uint8_t portnum );
static void usb_hstd_OhciRemoveDevice( uint8_t device_address, boolean_t free_ed );
static uint8_t usb_hstd_OhciGetRootDeviceSpeed( USB_OHCI_HCD_DEVICE_DATA_P device_data, uint8_t portnum );
static void usb_hstd_OhciProcessPausedED( USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ed );
static void usb_hstd_OhciRemoveED( USB_OHCI_HCD_ENDPOINT_P endpoint, boolean_t free_ed );


/***********************************************************************************************************************
 Variable
 **********************************************************************************************************************/
/* static */
static USB_OHCI_HCD_DEVICE_DATA_P   ohci_DeviceData;


/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/

/* Global Function */
/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciInit
 *
 *  Description:    Initialize OHCI
 *
 *  Parameters:     void
 *
 *  Return Value:   uint32_t ; status
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciInit( void )
{
    usb_hstd_OhciInitDeviceData();

    usb_hstd_OhciClearList();

    usb_hstd_OhciInitRequestMemory();

    usb_hstd_OhciHwSetup();

    return( USB_OK );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciInit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciDeinit
 *
 *  Description:    Deinitialize OHCI
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciDeinit( void )
{
    /* H/W reset */
    usb_hstd_OhciHwReset();
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciDeinit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciInterruptHandler
 *
 *  Description:    OHCI Detect interrupt
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciInterruptHandler( void )
{
    uint32_t    context_info = 0;
    uint32_t    HcIntEnable;

    HcIntEnable = USB_HOST->HcIntEnable.LONG;

    /* Is this our interrupt? */
    if(ohci_DeviceData->HCCA->HccaDoneHead != 0)
    {
        context_info = USB_OHCI_IS_WRITEBACKDONEHEAD;  /* note interrupt processing required */

        if(ohci_DeviceData->HCCA->HccaDoneHead & 1)
        {
            context_info |= (USB_HOST->HcIntStatus.LONG & HcIntEnable);
        }
    }
    else
    {
        context_info = (USB_HOST->HcIntStatus.LONG & HcIntEnable);
        if(context_info == 0)
        {
            return;     /* not my interrupt */
        }
    }

    /* It is our interrupt, prevent HC from doing it to us again until we are finished */
    USB_HOST->HcIntDisable.LONG = USB_OHCI_IS_MASTERINTENABLE;

    usb_hstd_HciSendMessageFromInt( USB_HCI_TASK, USB_HCI_MESS_OHCI_INT, context_info );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciInterruptHandler
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciMainRoutine
 *
 *  Description:    OHCI Main Routine
 *
 *  Parameters:     uint32_t context_info ; Interrupt Context Information
 *
 *  Return Value:   void
 *
 *  Note:           This function is based on HcdInterruptService() of OHCI specification
 *
 **********************************************************************************************************************/
void usb_hstd_OhciMainRoutine( uint32_t context_info )
{
    uint32_t    temp;
    uint32_t    temp2;
    uint32_t    frame;

    if(context_info & USB_OHCI_IS_UNRECOVERABLERROR)
    {
        /* The controller is hung, maybe resetting it can get it going again */
        /* But that code is left as an exercise to the reader */
    }

    if(context_info & (USB_OHCI_IS_SCHEDULINGOVERRUN | USB_OHCI_IS_WRITEBACKDONEHEAD | USB_OHCI_IS_STARTOFFRAME | USB_OHCI_IS_FRAMENUMBEROVERRUN))
    {
        context_info |= USB_OHCI_IS_MASTERINTENABLE;       /* flag for end of frame type interrupts */
    }

#if 0
    /* Check for Schedule Overrun */
    if(context_info & USB_OHCI_IS_SCHEDULINGOVERRUN)
    {
        frame = usb_hstd_OhciGet32BitFrameNumber(ohci_DeviceData);
        temp2 = USB_HOST->HcCommandStatus & EFC_Mask;
        temp = temp2 - (ohci_DeviceData->SOCount & EFC_Mask);
        temp = (((temp >> EFC_Position) - 1) % EFC_Size) + 1;

        /* number of bad frames since last error */
        if(!(ohci_DeviceData->SOCount & SOC_Mask) || ((ohci_DeviceData->SOCount & SOC_Mask) + ohci_DeviceData->SOStallFrame + temp) != frame)   /* start a new count? */
        {
            ohci_DeviceData->SOLimitFrame = ohci_DeviceData->SOStallFrame = frame - temp;
            ohci_DeviceData->SOCount = temp | temp2;
        }
        else    /* got a running count */
        {
            ohci_DeviceData->SOCount = (ohci_DeviceData->SOCount + temp) & SOC_Mask | temp2;
            while(frame - ohci_DeviceData->SOLimitFrame >= 100)
            {
                ohci_DeviceData->SOLimitHit++;
                ohci_DeviceData->SOLimitFrame += 100;
            }
            if(frame - ohci_DeviceData->SOStallFrame >= 32740)
            {
                USB_HOST->HcControl  &= ~USB_OHCI_ISOCHRONOUSENABLE;    /* stop isochronous transfers */
                ohci_DeviceData->SOStallHit = TRUE;
                ohci_DeviceData->SOCount        = temp2;                            /* clear error counter */
            }
        }
        USB_HOST->HcInterruptStatus = USB_OHCI_IS_SCHEDULINGOVERRUN;    /* acknowledge interrupt */
        context_info &= ~USB_OHCI_IS_SCHEDULINGOVERRUN;
    }
    else    /* no schedule overrun, check for good frame */
    {
        if(context_info & USB_OHCI_IS_MASTERINTENABLE)
        {
            ohci_DeviceData->SOCount &= EFC_MASK;       /* clear counter */
    }
    }
#endif

    /* Check for frame Number Overflow */
    /* Note: the formula below prevents a debugger break from making the 32-bit frame number run backward */
    if(context_info & USB_OHCI_IS_FRAMENUMBEROVERRUN)
    {
        ohci_DeviceData->FrameHighPart += 0x10000 - ( ( ohci_DeviceData->HCCA->HccaFrameNumber ^ ohci_DeviceData->FrameHighPart ) & 0x8000 );
        USB_HOST->HcIntStatus.LONG  = USB_OHCI_IS_FRAMENUMBEROVERRUN;  /* acknowledge interrupt */
        context_info &= ~USB_OHCI_IS_FRAMENUMBEROVERRUN;
    }

    /* Processor interrupts could be enabled here and the interrupt dismissed at the interrupt */
    /* controller, but for simplicity this code won't */
    if(context_info & USB_OHCI_IS_RESUMEDETECTED)
    {
        /* Resume has been requested by a device on USB. HCD must wait 20ms then put controller */
        /* in the UsbOperational state. This code is left as an exercise to the reader */
        context_info &= ~USB_OHCI_IS_RESUMEDETECTED;
        USB_HOST->HcIntStatus.LONG = USB_OHCI_IS_RESUMEDETECTED;
    }

    /* Process the Done Queue */
    if(context_info & USB_OHCI_IS_WRITEBACKDONEHEAD)
    {
        usb_hstd_OhciProcessDoneQueue( ohci_DeviceData->HCCA->HccaDoneHead );

        /* Done Queue processing complete, notify controller */
        ohci_DeviceData->HCCA->HccaDoneHead = 0;
        USB_HOST->HcIntStatus.LONG = USB_OHCI_IS_WRITEBACKDONEHEAD;
        context_info &= ~USB_OHCI_IS_WRITEBACKDONEHEAD;
    }

    /* Process Root Hub changes */
    if(context_info & USB_OHCI_IS_ROOTHUBSTATUSCHANGE)
    {
        /* EmulateRootHubInterruptXfer will complete a USB_OHCI_HCD_TRANSFER_DESCRIPTOR which */
        /* we then pass to usb_hstd_OhciProcessDoneQueue to emulate an HC completion */

        /* leave RootHubStatusChange set in context_info so that it will be masked off */
        /* (it won't be unmasked again until another TD is queued for the emulated endpoint) */
        usb_hstd_OhciControlRoothub();
        USB_HOST->HcIntStatus.LONG = 0x00000040;    /* Clear RHSC bit */
        context_info &= ~USB_OHCI_IS_ROOTHUBSTATUSCHANGE;
    }

    if(context_info & USB_OHCI_IS_OWNERSHIPCHANGE)
    {
        /* Only SMM drivers need implement this */
        /* See Sections 5.1.1.3.3 and 5.1.1.3.6 for descriptions of what the code here must do */
    }

    /* Any interrupts left should just be masked out */
    /* (This is normal processing for StartOfFrame and RootHubStatusChange) */
    if(context_info & ~USB_OHCI_IS_MASTERINTENABLE)    /* any unprocessed interrupts? */
    {
        USB_HOST->HcIntDisable.LONG = context_info;     /* yes, mask them */
    }

    /* We've completed the actual service of the HC interrupts, now we must deal with the effects */
#if 0
    /* Check for Scheduling Overrun limit */
    if(ohci_DeviceData->SOLimitHit)
    {
        do
        {
            USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ED;
            if ( usb_hstd_OhciIsListEmpty(&ohci_DeviceData->EdList[USB_OHCI_ED_ISOCHRONOUS].Head) == TRUE )
            {
                break;  /* Isochronous List is empty */
            }

            ED = (USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P)usb_hstd_OhciScanContainingRecord(
                    ohci_DeviceData->EdList[USB_OHCI_ED_ISOCHRONOUS].Head.Blink,
                    USB_OHCI_CR_ENDPOINT_DESCRIPTOR,USB_OHCI_CR_LINK);

            if(ED->Endpoint->Type != USB_EP_ISO)
            {
                break;  /* Only 1ms Interrupts left on list */
            }
            ohci_DeviceData->AvailableBandwidth = ohci_DeviceData->MaxBandwidthInUse - 64;

            /* It is recommended that the above bandwidth be saved in non-volatile memory for future use */
            usb_hstd_OhciRemoveED(ED->Endpoint);
        } while (--ohci_DeviceData->SOLimitHit);
        ohci_DeviceData->SOLimitHit = 0;
    }
#endif

    /* look for things on the PausedEDRestart list */
    frame = usb_hstd_OhciGet32BitFrameNumber( ohci_DeviceData );
    while(usb_hstd_OhciIsListEmpty(&ohci_DeviceData->PausedEDRestart) == FALSE)
    {
        USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ED;

        ED = ( USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P )usb_hstd_OhciScanContainingRecord(
                ohci_DeviceData->PausedEDRestart.Flink, USB_OHCI_CR_ENDPOINT_DESCRIPTOR, USB_OHCI_CR_PAUSEDLINK );

        if(ED == NULL)
        {
            usb_hstd_OhciRemoveListEntry( &ohci_DeviceData->PausedEDRestart );
            break;
        }

        if((int32_t)(ED->ReclamationFrame - frame) > 0)
        {
            break;
        }

        usb_hstd_OhciRemoveListEntry( &ED->PausedLink );
        ED->PausedFlag = FALSE;
        usb_hstd_OhciProcessPausedED( ED );
    }

    /* look for things on the StalledEDReclamation list */
    if((context_info & USB_OHCI_IS_MASTERINTENABLE) && (usb_hstd_OhciIsListEmpty(&ohci_DeviceData->StalledEDReclamation) == FALSE))
    {
        temp = USB_HOST->HcContCurrentED.LONG;
        temp2 = USB_HOST->HcBulkCurrentED.LONG;
        while(usb_hstd_OhciIsListEmpty(&ohci_DeviceData->StalledEDReclamation) == FALSE)
        {
            USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ED;

            ED = ( USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P )usb_hstd_OhciScanContainingRecord(
                    ohci_DeviceData->StalledEDReclamation.Flink, USB_OHCI_CR_ENDPOINT_DESCRIPTOR, USB_OHCI_CR_LINK );

            if(ED == NULL)
            {
                usb_hstd_OhciRemoveListEntry( &ohci_DeviceData->StalledEDReclamation );
                break;
            }

            usb_hstd_OhciRemoveListEntry( &ED->Link );
            if(ED->PhysicalAddress == temp)
            {
                USB_HOST->HcContCurrentED.LONG = temp = ED->HcED.NextED;
            }
            else if(ED->PhysicalAddress == temp2)
            {
                USB_HOST->HcBulkCurrentED.LONG = temp2 = ED->HcED.NextED;
            }

            if(ED->Endpoint != NULL)
            {
                usb_hstd_OhciProcessPausedED(ED);      /* cancel any outstanding TDs */
                usb_hstd_OhciFreeEndpointDescriptor( ED );
            }
            else
            {
                usb_hstd_OhciFreeEndpointDescriptor( ED );
            }
        }
        USB_HOST->HcControl.LONG |= USB_OHCI_CONTROLLISTENABLE | USB_OHCI_BULKLISTENABLE;   /* restart queues */
    }

    /* look for things on the RunningEDReclamation list */
    frame = usb_hstd_OhciGet32BitFrameNumber( ohci_DeviceData );
    while(usb_hstd_OhciIsListEmpty(&ohci_DeviceData->RunningEDReclamation) == FALSE)
    {
        USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ED;

        ED = ( USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P )usb_hstd_OhciScanContainingRecord(
                ohci_DeviceData->RunningEDReclamation.Flink, USB_OHCI_CR_ENDPOINT_DESCRIPTOR, USB_OHCI_CR_LINK );

        if(ED == NULL)
        {
            usb_hstd_OhciRemoveListEntry( &ohci_DeviceData->RunningEDReclamation );
            break;
        }

        if((int32_t)(ED->ReclamationFrame - frame) > 0)
        {
            break;
        }

        usb_hstd_OhciRemoveListEntry( &ED->Link );
        if(ED->Endpoint != NULL)
        {
            usb_hstd_OhciProcessPausedED(ED);      /* cancel any outstanding TDs */
            usb_hstd_OhciFreeEndpointDescriptor( ED );
        }
        else
        {
            usb_hstd_OhciFreeEndpointDescriptor( ED );
        }
    }

    /* If processor interrupts were enabled earlier then they must be disabled here before we re-enable the interrupts at the controller */
    USB_HOST->HcIntEnable.LONG = USB_OHCI_IS_MASTERINTENABLE;

    return;
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciMainRoutine
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciControlRoothub
 *
 *  Description:    OHCI Control RootHub
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciControlRoothub( void )
{
    uint32_t    portnum;
    uint32_t    numports;
    uint32_t    *port_status_reg;

//  r_usb_hstd_HciWaitTime( 5 );

    numports = USB_HOST->HcRhDescriptorA.LONG & 0x000000FF;

    for(portnum = 0; portnum < numports; portnum++)
    {

        port_status_reg = (uint32_t *)&( USB_HOST->HcRhPortStatus1.HcRhPortStatus1_A.LONG );

        port_status_reg += portnum;

        /*  Detect DisConnection */
        if((*port_status_reg & 0x00020002) == 0x00020000)
        {
//          r_usb_hstd_HciWaitTime( 20 );

            if(USB_HOST->HcIntStatus.LONG & USB_OHCI_IS_WRITEBACKDONEHEAD)
            {
                USB_HOST->HcIntStatus.LONG = USB_OHCI_IS_WRITEBACKDONEHEAD;
//              return;
            }

            usb_hstd_OhciRootPortDisconnection( ohci_DeviceData, portnum );
            r_usb_hstd_HciWaitTime( 1 );

            *port_status_reg = 0x00030000;      /* Clear PESC & CSC bit */
        }
        else if((*port_status_reg & 0x00010001) == 0x00010001)
        {
            /*  Detect Connection */
            *port_status_reg = 0x00010000;      /* Clear CSC bit */
            usb_hstd_OhciPortReset( portnum );
            if((*port_status_reg & 0x00000001) == 0x00000000)
            {
                return;
            }
            /* Report USBD-Layer */
            usb_hstd_OhciRootPortConnection( ohci_DeviceData, usb_hstd_OhciGetRootDeviceSpeed( ohci_DeviceData, portnum ), portnum );
        }
        else
        {
        }
        if((*port_status_reg & 0x00080000) == 0x00080000)
        {
            /*  Detect OverCurrent */
            *port_status_reg = 0x00080000;      /* Clear OCIC bit */
            r_usb_hstd_HciWaitTime(10);          /* Wait 10ms */
            /* over current callback */
            usb_ghstd_HciCallback.over_current_cb( portnum );
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciControlRoothub
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciDisconnect
 *
 *  Description:    OHCI Device Disconnect
 *
 *  Parameters:     uint32_t devadd ; device address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciDisconnect( uint32_t devadd )
{
    uint8_t free_ed = FALSE;

    if(devadd == USB_HCI_NODEVICE)
    {
        return;
    }

    usb_hstd_OhciClearDeviceTrreq( devadd );

    usb_hstd_OhciRemoveDevice( devadd, free_ed );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciDisconnect
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciGetDeviceAddressOfRootpoot
 *
 *  Description:    OHCI Getting of device address of rootport
 *
 *  Parameters:     uint16_t rootport ; rootport no
 *
 *  Return Value:   uint16_t          ; device address
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_OhciGetDeviceAddressOfRootpoot( uint16_t rootport )
{
    if(USB_OHCI_MAXROOTPORTS > rootport)
    {
        return( ohci_DeviceData->RootDevice[ rootport ] );
    }
    return( USB_HCI_NODEVICE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciGetDeviceAddressOfRootpoot
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciSetDeviceAddressOfRootpoot
 *
 *  Description:    The device address of OHCI route port is set.
 *
 *  Parameters:     uint16_t rootport ; rootport no
 *                  uint16_t devaddr  ; device address
 *
 *  Return Value:   uint16_t          ; device address
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_OhciSetDeviceAddressOfRootpoot( uint16_t rootport, uint16_t deviceaddr )
{
    USB_HCI_DEVICE      *devinfo_p;

    if(USB_OHCI_MAXROOTPORTS <= rootport)
    {
        return( USB_HCI_NODEVICE );
    }
    if(ohci_DeviceData->RootDevice[rootport] != 0)
    {
        //USB_HCI_PRINTF1_R( "Error: The device address has already been allocated to the route port %d.\n", rootport );
        return( USB_HCI_NODEVICE );
    }

    /* The device address of device information is updated */
    devinfo_p = r_usb_hstd_HciGetDeviceInformation( ohci_DeviceData->RootDevice[ rootport ] );
    if(devinfo_p == NULL)
    {
        return( USB_HCI_NODEVICE );
    }
    devinfo_p->bit.devnum = deviceaddr;

    ohci_DeviceData->RootDevice[ rootport ] = deviceaddr;

    return( deviceaddr );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciSetDeviceAddressOfRootpoot
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciPortReset
 *
 *  Description:    OHCI Port Reset
 *
 *  Parameters:     uint32_t portnum ; port no
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciPortReset( uint32_t portnum )
{
    uint32_t *port_status_reg;

    port_status_reg = (uint32_t *)&( USB_HOST->HcRhPortStatus1.HcRhPortStatus1_A.LONG );
    port_status_reg += portnum;

    /* Port* Reset */
    *port_status_reg = 0x00000010;
    while((*port_status_reg & 0x00100000) == 0x00000000)    /* Wait Port*-Enable */
    {
        if((*port_status_reg & 0x00000001) == 0x00000000)   /* if device is dis-connect */
        {
            break;
        }
        r_usb_hstd_HciWaitTime( 1 );
    }

    *port_status_reg = 0x00100000;  /* Clear PRSC bit */

    r_usb_hstd_HciWaitTime(10);      /* Wait 10ms */
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciPortReset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciGetPidStatus
 *
 *  Description:    Getting of OHCI PID Status
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req ; transfer request pointer
 *
 *  Return Value:   uint16_t               ; PID Status
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_OhciGetPidStatus( USB_HCI_TR_REQ *tr_req )
{
    USB_OHCI_REQUEST_P  ohci_req;
    uint32_t            status;

    if(tr_req != NULL)
    {
        if(tr_req->bit.enable == TRUE)
        {
            ohci_req = ( USB_OHCI_REQUEST_P )tr_req->hci_info;
            status = ohci_req->Status;
            if(status == USB_OHCI_CC_STALL)
            {
                return (USB_PID_STALL);
            }
            if(status == USB_OHCI_CC_NOERROR)
            {
                return (USB_PID_BUF);
            }
        }
    }
    return (USB_PID_NAK);
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciGetPidStatus
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciPortSuspend
 *
 *  Description:    OHCI Port Suspend
 *
 *  Parameters:     uint16_t port ; port no
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciPortSuspend( uint16_t port )
{
    uint32_t *port_status_reg;

    port_status_reg = (uint32_t *)&( USB_HOST->HcRhPortStatus1.HcRhPortStatus1_A.LONG );
    port_status_reg += port;

    *port_status_reg = 0x00000004;  /* Port* Suspend */
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciPortSuspend
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciPortResume
 *
 *  Description:    OHCI Port Resume
 *
 *  Parameters:     uint16_t port ; port no
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciPortResume( uint16_t port )
{
    uint32_t *port_status_reg;

    port_status_reg = (uint32_t *)&( USB_HOST->HcRhPortStatus1.HcRhPortStatus1_A.LONG );
    port_status_reg += port;

    /* Port* Resume */
    *port_status_reg = 0x00000008;
    while((*port_status_reg & 0x00040000) == 0x00000000)    /* Wait Port*-Resume wait */
    {
        if((*port_status_reg & 0x00000001) == 0x00000000)   /* if device is dis-connect */
        {
            break;
        }
        r_usb_hstd_HciWaitTime( 1 );
    }

    *port_status_reg = 0x00040000;      /* Clear PSSC bit */
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciPortResume
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciGetTransferEndStatus
 *
 *  Description:    Getting of OHCI Transfer End Status
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req ; HCI transfer request pointer
 *
 *  Return Value:   uint16_t               ; USB Standard F/W Transfer End Status
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_OhciGetTransferEndStatus( USB_HCI_TR_REQ *tr_req )
{
    uint32_t    status;
    uint16_t    ret = USB_DATA_ERR;

    status = tr_req->status;

    if(status == USB_OHCI_CC_NOERROR)
    {
        if(tr_req->bit.eptype == USB_EP_CNTRL)
        {
            /* For control */
            ret = USB_CTRL_END;
        }
        else if(tr_req->bit.eptype == USB_EP_ISO)
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
        else
        {
            /* For bulk/interrupt */
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
    else
    {
        if(tr_req->bit.eptype == USB_EP_ISO)
        {
            if(status == USB_OHCI_CC_DATAOVERRUN)
            {
                /* For isochronous */
                if(tr_req->bit.direction == USB_HCI_DIRECTION_OUT)
                {
                    ret = USB_DATA_WRITING;
                }
                else
                {
                    /* When receive data is size over */
                    ret = USB_DATA_OVR;
                }
            }
        }
        else
        {
            if(status == USB_OHCI_CC_DATAUNDERRUN)
            {
                ret = USB_DATA_OK;
            }
            else if(status == USB_OHCI_CC_STALL)
            {
                /* For STALL */
                ret = USB_DATA_STALL;
            }
            else if(status == USB_OHCI_CC_DEVICENOTRESPOND)
            {
                /* Transfer stop by Detach */
                ret = USB_DATA_STOP;
            }
            else if(status == USB_OHCI_RS_CANCELED)
            {
                /* Transfer stop by Cancel */
                ret = USB_DATA_STOP;
            }
        }
    }

    return( ret );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciGetTransferEndStatus
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciRemoveEndpoint
 *
 *  Description:    OHCI Remove Endpoint/ED
 *
 *  Parameters:     uint8_t device_address  ; device address
 *                  uint8_t endpoint_number ; endpoint no
 *                  uint8_t direction       ; direction
 *                  boolean_t free_ed       ; free flag
 *
 *  Return Value:   uint32_t                : result( TRUE:Normal End, FALSE:Fail )
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciRemoveEndpoint( uint8_t device_address, uint8_t endpoint_number, uint8_t direction, boolean_t free_ed )
{
    USB_OHCI_HCD_ENDPOINT_P endpoint;
    uint32_t                ret = FALSE;

    endpoint = usb_hstd_OhciScanEndpoint( device_address, endpoint_number, direction );
    if(endpoint != NULL)
    {
        usb_hstd_OhciRemoveED( endpoint, free_ed );
        if(free_ed == TRUE)
        {
            usb_hstd_OhciFreeEndpoint( endpoint );
        }
        usb_hstd_OhciStoreEndpoint( device_address, endpoint_number, direction, NULL );

        ret = TRUE;
    }

    return( ret );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciRemoveEndpoint
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciPauseEndpoint
 *
 *  Description:    OHCI Pause ED
 *
 *  Parameters:     uint8_t device_address  ; device address
 *                  uint8_t endpoint_number ; endpoint no
 *                  uint8_t direction       ; direction
 *
 *  Return Value:   uint32_t                : result( TRUE:Normal End, FALSE:Fail )
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciPauseEndpoint( uint8_t device_address, uint8_t endpoint_number, uint8_t direction )
{
    USB_OHCI_HCD_ENDPOINT_P endpoint;
    uint32_t                ret = FALSE;

    endpoint = usb_hstd_OhciScanEndpoint( device_address, endpoint_number, direction );
    if(endpoint != NULL)
    {
        usb_hstd_OhciPauseEd( endpoint );
        ret = TRUE;
    }

    return( ret );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciPauseEndpoint
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciRemoveListHead
 *
 *  Description:    OHCI Remove ListHead
 *
 *  Parameters:     USB_OHCI_LIST_ENTRY_P list ; remove list head pointer
 *
 *  Return Value:   USB_OHCI_LIST_ENTRY_P      ; next link list pointer
 *
 **********************************************************************************************************************/
USB_OHCI_LIST_ENTRY_P usb_hstd_OhciRemoveListHead( USB_OHCI_LIST_ENTRY_P list )
{
    USB_OHCI_LIST_ENTRY     *ret_list;

    ret_list = list->Flink;

    if(list->Flink == list->Blink)
    {
        list->Flink = list->Blink = NULL;
    }
    else
    {
        list->Flink = list->Flink->Flink;
    }

    return( ret_list );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciRemoveListHead
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciRemoveListEntry
 *
 *  Description:    OHCI Remove ListEntry
 *
 *  Parameters:     USB_OHCI_LIST_ENTRY_P list ; remove list pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciRemoveListEntry( USB_OHCI_LIST_ENTRY_P list )
{
    USB_OHCI_LIST_ENTRY     *list_head;

    if((list->Blink == NULL) || (list->Flink == NULL))
    {
        return;
    }

    if(list->Blink == list->Flink)
    {
        list_head = list->Blink;
        list_head->Blink = list_head->Flink = NULL;
    }
    else
    {
        list->Blink->Flink = list->Flink;
        list->Flink->Blink = list->Blink;
    }
    list->Flink = list->Blink = NULL;
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciRemoveListEntry
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciInitializeListHead
 *
 *  Description:    OHCI Initialize ListHead
 *
 *  Parameters:     USB_OHCI_LIST_ENTRY_P list ; list pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciInitializeListHead( USB_OHCI_LIST_ENTRY_P list )
{
    list->Flink = NULL;
    list->Blink = NULL;
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciInitializeListHead
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciIsListEmpty
 *
 *  Description:    Judge List is empty or not
 *
 *  Parameters:     USB_OHCI_LIST_ENTRY_P list ; List pointer
 *
 *  Return Value:   uint32_t                   ; result( TRUE:Empty, FALSE:Not Empty )
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciIsListEmpty( USB_OHCI_LIST_ENTRY_P list )
{
    if(list->Flink == NULL)
    {
        return( TRUE );
    }
    return( FALSE );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciIsListEmpty
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciInsertHeadList
 *
 *  Description:    OHCI Insert list to the head of list
 *
 *  Parameters:     USB_OHCI_LIST_ENTRY_P list_head ; List Head pointer
 *                  USB_OHCI_LIST_ENTRY_P link      ; insert list pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciInsertHeadList( USB_OHCI_LIST_ENTRY_P list_head, USB_OHCI_LIST_ENTRY_P link )
{
    if(list_head->Flink == NULL)
    {
        /* list_head is Empty */
        list_head->Flink = list_head->Blink = link;
        link->Flink = link->Blink = list_head;
    }
    else
    {
        list_head->Flink->Blink = link;
        link->Flink = list_head->Flink;
        list_head->Flink = link;
        link->Blink = list_head;
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciInsertHeadList
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciInsertTailList
 *
 *  Description:    OHCI Insert list to tail of list
 *
 *  Parameters:     USB_OHCI_LIST_ENTRY_P list_head ; List Head pointer
 *                  USB_OHCI_LIST_ENTRY_P link      ; insert list pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciInsertTailList( USB_OHCI_LIST_ENTRY_P list_head, USB_OHCI_LIST_ENTRY_P link )
{
    if (list_head->Blink == NULL)
    {
        /* list_head is Empty */
        list_head->Blink = list_head->Flink = link;
        link->Flink = link->Blink = list_head;
    }
    else
    {
        list_head->Blink->Flink = link;
        link->Blink = list_head->Blink;
        list_head->Blink = link;
        link->Flink = list_head;
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciInsertTailList
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciPhysicalAddressOf
 *
 *  Description:    Return PhysicalAddress
 *
 *  Parameters:     void *Data ; Data Address
 *
 *  Return Value:   uint32_t   ; Physical Address
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciPhysicalAddressOf( void *data )
{
#if USB_OHCI_SHAREDMEMORYTYPE == USB_OHCI_SHAREDMEMORYTYPE_EXCLUSIVE
    return( ( uint32_t )data - USB_OHCI_SHAREDMEMORY_OFFSET );
#elif USB_OHCI_SHAREDMEMORYTYPE == USB_OHCI_SHAREDMEMORYTYPE_PCI
    return( ( uint32_t )USB_HCI_NONCACHE_ADDR( ( uint32_t )data ) );
#else
    return( ( uint32_t )data );
#endif
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciPhysicalAddressOf
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciPauseEd
 *
 *  Description:    OHCI Pause Endpoint
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P endpoint ; Endpoint Pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciPauseEd( USB_OHCI_HCD_ENDPOINT_P endpoint )
{
    USB_OHCI_HCD_DEVICE_DATA_P          device_data;
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  ed;

    device_data = endpoint->DeviceData;
    ed = endpoint->HcdED;
    ed->HcED.Control.K = TRUE;

    if(ed->PausedFlag)
    {
        /* already awaiting pause processing */
        return;
    }
    if((ed->HcED.HeadP & USB_OHCI_HCED_HEADP_HALT) == 0)
    {
        /* Endpoint is active in Host Controller, wait for SOF before processing the endpoint */
        ed->PausedFlag = TRUE;
        USB_HOST->HcIntStatus.LONG = USB_OHCI_HC_INT_SOF;  /* clear SOF interrupt pending */
        ed->ReclamationFrame = usb_hstd_OhciGet32BitFrameNumber( device_data ) + 1;
        usb_hstd_OhciInsertTailList( &device_data->PausedEDRestart, &ed->PausedLink );

        USB_HOST->HcIntEnable.LONG = USB_OHCI_HC_INT_SOF; /* interrupt on next SOF */
        return;
    }

    /* Endpoint already paused, do processing now */
    usb_hstd_OhciProcessPausedED( ed );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciPauseEd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciUnscheduleIsochronousOrInterruptEndpoint
 *
 *  Description:    OHCI Unschedule Iso,Int Endpoint
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P endpoint       ; Endpoint Pointer
 *                  boolean_t free_ed                      ; endpoint free flag
 *                  boolean_t endpoint_processing_required ; endpoint processing required flag
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OhciUnscheduleIsochronousOrInterruptEndpoint( USB_OHCI_HCD_ENDPOINT_P endpoint, boolean_t free_ed, boolean_t endpoint_processing_required )
{
//  USB_OHCI_HCD_DEVICE_DATA_P  device_data;

//  device_data = endpoint->DeviceData;

    usb_hstd_OhciRemoveED(endpoint, free_ed);      /* see sample code in Section 5.2.7.1.2 */
    if(endpoint_processing_required == TRUE)
    {
        USB_HOST->HcIntEnable.LONG = USB_OHCI_HC_INT_SOF;     /* interrupt on next SOF */
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciUnscheduleIsochronousOrInterruptEndpoint
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciSetFrameInterval
 *
 *  Description:    OHCI Set FrameInterval
 *
 *  Parameters:     USB_OHCI_HCD_DEVICE_DATA_P device_data ; Device Data Pointer
 *                  boolean_t up_not_down                  ; up or down flag( TRUE:up, FALSE:down )
 *
 *  Return Value:   uint32_t                               ; frame number
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciSetFrameInterval( USB_OHCI_HCD_DEVICE_DATA_P device_data, boolean_t up_not_down )
{
    uint32_t    frame_number;
    uint32_t    interval;

//    interval |= (device_data->HC->HcFmInterval & 0x00003FFF);
//    interval = (device_data->HC->HcFmInterval & 0x00003FFF);
    interval = (USB_HOST->HcFmInterval.LONG & 0x00003FFF);
    if(up_not_down == TRUE)
    {
        ++interval;
    }
    else
    {
        --interval;
    }
    interval |= ( ( ( interval - USB_OHCI_MAXIMUM_OVERHEAD ) * 6 ) / 7 ) << 16;
//  interval |= 0x80000000 & ( 0x80000000 ^ ( device_data->HC->HcFrameRemaining ) );
    interval |= 0x80000000 & ( 0x80000000 ^ ( USB_HOST->HcFmRemaining.LONG ) );
    frame_number = usb_hstd_OhciGet32BitFrameNumber( device_data );
//  device_data->HC->HcFmInterval = interval;
    USB_HOST->HcFmInterval.LONG = interval;
//    if(0x80000000 & (device_data->HC->HcFrameRemaining ^ interval))
    if(0x80000000 & (USB_HOST->HcFmRemaining.LONG ^ interval))
    {
        frame_number += 1;
    }
    else
    {
        frame_number = usb_hstd_OhciGet32BitFrameNumber( device_data );
    }
    return (frame_number);      /* return frame number new interval takes effect */
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciSetFrameInterval
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciGet32BitFrameNumber
 *
 *  Description:    OHCI Get 32bit FrameNumber
 *
 *  Parameters:     USB_OHCI_HCD_DEVICE_DATA_P device_data ; Device Data Pointer
 *
 *  Return Value:   uint32_t                               ; 32bit frame number
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciGet32BitFrameNumber( USB_OHCI_HCD_DEVICE_DATA_P device_data )
{
    uint32_t    fm;
    uint32_t    hp;

    /* This code accounts for the fact that HccaFrameNumber is updated by the HC before the HCD gets an interrupt that will adjust FrameHighPart */
    hp = device_data->FrameHighPart;
    fm = device_data->HCCA->HccaFrameNumber;
    return( ( ( fm & 0x7FFF ) | hp ) + ( ( fm ^ hp ) & 0x8000 ) );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciGet32BitFrameNumber
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciCheckBandwidth
 *
 *  Description:    OHCI Check bandwidth
 *
 *  Parameters:     USB_OHCI_HCD_DEVICE_DATA_P device_data ; Device Data Pointer
 *                  uint32_t list                          ; list
 *                  uint32_t *best_list                    ; pointer of return best list
 *
 *  Return Value:   uint32_t                               ; Worst Bandwidth
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_OhciCheckBandwidth( USB_OHCI_HCD_DEVICE_DATA_P device_data, uint32_t list, uint32_t *best_list )
{
/*++
    This routine scans all the scheduling lists of frequency determined by
    the base List passed in and returns the worst bandwidth found (i.e., max
    in use by any given scheduling list) and the list which had the least
    bandwidth in use.
    List - must be a base scheduling list. I.e., it must be one of
    USB_OHCI_ED_INTERRUPT_1ms, USB_OHCI_ED_INTERRUPT_2ms,USB_OHCI_ED_INTERRUPT_4ms, ..., USB_OHCI_ED_INTERRUPT_32ms.
    All lists of the appropriate frequency are checked
--*/

    uint32_t    last_list;
    uint32_t    index;
    uint32_t    best_bandwidth;
    uint32_t    worst_bandwidth;
    uint32_t    bandwidth;

    worst_bandwidth = 0;
    best_bandwidth = ~0;

    for(last_list = list + list; list <= last_list; list++)
    {
        /* Sum bandwidth in use in this scheduling time */
        bandwidth = 0;
        for(index = list; index != USB_OHCI_ED_EOF; index = device_data->EdList[ index ].Next)
        {
            bandwidth += device_data->EdList[ index ].Bandwidth;
        }

        /* Remember best and worst */
        if(bandwidth < best_bandwidth)
        {
            best_bandwidth = bandwidth;
            *best_list = list;
        }
        if(bandwidth > worst_bandwidth)
        {
            worst_bandwidth = bandwidth;
        }
    }

    return( worst_bandwidth );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciCheckBandwidth
 **********************************************************************************************************************/


/* Static Function */
/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciHwSetup
 *
 *  Description:    OHCI H/W Setup
 *
 *  Parameters:     void
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_OhciHwSetup( void )
{
    uint32_t        n;
    uint32_t        portnum;
    uint32_t        numports;
    uint32_t        *port_status_reg;

    /* Setup ohci_DeviceData */
    ohci_DeviceData = usb_hstd_OhciAllocDeviceData();
    if(ohci_DeviceData == NULL)
    {
        return;
    }

    /* Register setting */
//    ohci_DeviceData->HC = (USB_OHCI_HC_OPERATIONAL_REGISTER_P)USB_OHCI_BASE;

    /* H/W reset */
    if(USB_OK != usb_hstd_OhciHwReset())
    {
        return;
    }

    USB_HOST->HcHCCA.LONG = usb_hstd_OhciPhysicalAddressOf( usb_hstd_OhciGetHccaAddress() );
    ohci_DeviceData->HCCA = usb_hstd_OhciGetHccaAddress();

    usb_hstd_OhciClearHcca( ohci_DeviceData );

    usb_hstd_OhciInitailizeInterruptLists( ohci_DeviceData );

    numports = USB_HOST->HcRhDescriptorA.LONG & 0x000000FF;

    /* Set USB-Operational state */
    USB_HOST->HcControl.LONG = ( USB_HOST->HcControl.LONG & ~0x000000C0 ) | 0x00000080;

    /*  Clear HcInterruptStatus */
    USB_HOST->HcIntStatus.LONG = 0xFFFFFFFF;

    USB_HOST->HcFmInterval.LONG = 0x27782EDF;
    USB_HOST->HcPeriodicStart.LONG = 0x2A2F;

    /*  Set PowerControl-related Reg */
    USB_HOST->HcRhDescriptorA.LONG    = 0x02001902;   /* Enable Power-SW, Disable OverCurrent */
    for(n = 0; n < numports; n++)
    {
        USB_HOST->HcRhDescriptorB.LONG |= ( 0x00020000 << n );
    }

    /* Enable OverCurrent */
    USB_HOST->HcRhDescriptorA.LONG &= ~0x00001000;

    for(portnum = 0; portnum < numports; portnum++)
    {
        port_status_reg = (uint32_t *)&( USB_HOST->HcRhPortStatus1.HcRhPortStatus1_A.LONG );
        port_status_reg += portnum;
        *port_status_reg = 0xFFFF0000;
    }

    ohci_DeviceData->EdList[ USB_OHCI_ED_CONTROL ].PhysicalHead = (uint32_t *)&USB_HOST->HcContHeadED.LONG;
    ohci_DeviceData->EdList[ USB_OHCI_ED_BULK ].PhysicalHead = (uint32_t *)&USB_HOST->HcBulkHeadED.LONG;

    /*  Enable MasterInt,RHSC,FNO,WBDH */
    USB_HOST->HcIntEnable.LONG = 0x80000062;

    /* Control,Bulk,Iso,Periodic List Enable */
    USB_HOST->HcControl.LONG |= 0x0000003C;

    return;
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciHwSetup
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciHwReset
 *
 *  Description:    Reset OHCI H/W
 *
 *  Parameters:     void
 *
 *  Return Value:   uint32_t ; status
 *
 **********************************************************************************************************************/
static uint32_t usb_hstd_OhciHwReset( void )
{
    uint32_t        timeout;

    USB_HOST->HcCommandStatus.LONG = 0x00000001;  /* Reset HC */
    timeout = 0;
    while(USB_HOST->HcCommandStatus.LONG & 0x00000001)
    {
        if(timeout > USB_OHCI_TIMEOUT)
        {
            USB_HCI_PRINTF0_R( "Error : usb_hstd_OhciHwSetup TIMEOUT\n" );
            return( USB_ERROR );
        }
        r_usb_hstd_HciWaitTime( 1 );
        timeout++;
    }

    return( USB_OK );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciHwReset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciInitailizeInterruptLists
 *
 *  Description:    OHCI Initialize InterruptED List
 *
 *  Parameters:     USB_OHCI_HCD_DEVICE_DATA_P device_data ; Device Data Pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_OhciInitailizeInterruptLists( USB_OHCI_HCD_DEVICE_DATA_P device_data )
{
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  ed;
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  StaticED[ USB_OHCI_ED_INTERRUPT_32ms ] = {0};
    uint32_t                            i;
    uint32_t                            j;
    uint32_t                            k;

    static uint8_t Balance[16] =
    {
        0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE, 0x1, 0x9, 0x5, 0xD, 0x3, 0xB, 0x7, 0xF
    };

    /* Allocate satirically disabled EDs, and set head pointers for scheduling lists */
    for(i = 0; i < USB_OHCI_ED_INTERRUPT_32ms; i++)
    {
        ed = usb_hstd_OhciAllocateEndpointDescriptor();
        /* Check for valid pointer */
        if (FIT_NO_PTR == ed)
        {
            continue;
        }

        ed->PhysicalAddress = usb_hstd_OhciPhysicalAddressOf( &ed->HcED );
        device_data->EdList[ i ].PhysicalHead = &ed->HcED.NextED;
        ed->HcED.Control.K = 1;     /* mark ED as disabled */

        ed->HcED.Control.S = 0;

        usb_hstd_OhciInitializeListHead( &device_data->EdList[ i ].Head );
        StaticED[ i ] = ed;
        if(i > 0)
        {
            device_data->EdList[ i ].Next = ( i - 1 ) / 2;
            ed->HcED.NextED = StaticED[ ( i - 1 ) / 2 ]->PhysicalAddress;
        }
        else
        {
            device_data->EdList[ i ].Next = USB_OHCI_ED_EOF;
            ed->HcED.NextED = 0;
        }
    }

    /* Set head pointers for 32ms scheduling lists which start from HCCA */
    for(i = 0, j = USB_OHCI_ED_INTERRUPT_32ms ; i < 32; i++, j++)
    {
        device_data->EdList[ j ].PhysicalHead = &device_data->HCCA->HccaInterruptList[ i ];
        usb_hstd_OhciInitializeListHead( &device_data->EdList[ j ].Head );
        k = Balance[ i & 0xF ] + USB_OHCI_ED_INTERRUPT_16ms;
        device_data->EdList[ j ].Next = k;
        device_data->HCCA->HccaInterruptList[ i ] = StaticED[ k ]->PhysicalAddress;
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciInitailizeInterruptLists
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciClearHcca
 *
 *  Description:    OHCI Clear HCCA
 *
 *  Parameters:     USB_OHCI_HCD_DEVICE_DATA_P device_data ; Device Data Pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_OhciClearHcca( USB_OHCI_HCD_DEVICE_DATA_P device_data )
{
    device_data->HCCA->HccaFrameNumber = 0x0;
    device_data->HCCA->HccaPad1 = 0x0;
    device_data->HCCA->HccaDoneHead = 0x0;
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciClearHcca
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciClearDeviceTrreq
 *
 *  Description:    OHCI Clear transfer request for disconnected device
 *
 *  Parameters:     uint32_t devadd ; Device Address
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_OhciClearDeviceTrreq( uint32_t devadd )
{
    uint32_t    i;
    uint32_t    n;
    uint8_t     free_ed = FALSE;

    for(i = 0; i < USB_HCI_TRREQ_NUM; i++)
    {
        if((usb_ghstd_HciTransferRequest[i].bit.enable == TRUE) && (usb_ghstd_HciTransferRequest[i].bit.devadrs == devadd))
        {
            /* Cancel Request */
            usb_hstd_OhciCancelTransferRequest(&usb_ghstd_HciTransferRequest[ i ]);

            /* Remove ED */
            usb_hstd_OhciRemoveDevice( devadd, free_ed );

            /* Check downstream port */
            for(n = 0; n < USB_HCI_HUBPORT_NUM; n++)
            {
                if(usb_ghstd_HciTransferRequest[i].devinfo->hubdevinfo.devnum[n] != 0)
                {
                    usb_hstd_OhciClearDeviceTrreq( usb_ghstd_HciTransferRequest[ i ].devinfo->hubdevinfo.devnum[ n ] );
                }
            }
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciClearDeviceTrreq
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciRootPortConnection
 *
 *  Description:    OHCI Root Port Device Connection
 *
 *  Parameters:     USB_OHCI_HCD_DEVICE_DATA_P devicedata ; Device Data Pointer
 *                  uint8_t devspeed                      ; Device Speed
 *                  uint8_t portnum                       ; Port No
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_OhciRootPortConnection( USB_OHCI_HCD_DEVICE_DATA_P devicedata, uint8_t devspeed, uint8_t portnum )
{
    USB_HCI_DEVICE      *devinfo;
    uint8_t             free_ed = FALSE;

    usb_hstd_OhciRemoveDevice( 0, free_ed );

    devinfo = usb_hstd_HciAllocDevinfo();
    if(devinfo != NULL)
    {
        devinfo->bit.devspeed             = devspeed;
        devinfo->bit.devnum               = 0;
        devinfo->bit.hctype               = USB_HCI_HCTYPE_OHCI;
        devinfo->hci_device               = devicedata;
        devicedata->RootDevice[ portnum ] = devinfo->bit.devnum;

        /* attach callback */
        usb_ghstd_HciCallback.attach_cb(portnum);
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciRootPortConnection
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciRootPortDisconnection
 *
 *  Description:    OHCI Root Port Device Disconnection
 *
 *  Parameters:     USB_OHCI_HCD_DEVICE_DATA_P devicedata ; Device Data Pointer
 *                  uint8_t portnum                       ; Port No
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_OhciRootPortDisconnection( USB_OHCI_HCD_DEVICE_DATA_P devicedata, uint8_t portnum )
{
    r_usb_hstd_HciDisconnect( devicedata->RootDevice[ portnum ] );

    devicedata->RootDevice[ portnum ] = USB_HCI_NODEVICE;

    /* detach callback */
    usb_ghstd_HciCallback.detach_cb(portnum);
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciRootPortDisconnection
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciRemoveDevice
 *
 *  Description:    OHCI Remove Device
 *
 *  Parameters:     uint8_t device_address  ; device address
 *                  boolean_t free_ed       ; free flag
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_OhciRemoveDevice( uint8_t device_address, boolean_t free_ed )
{
    uint32_t    n;

    for(n = 0; n < USB_OHCI_MAXENDPOINT; n++)
    {
        usb_hstd_OhciRemoveEndpoint( device_address, n, USB_HCI_DIRECTION_OUT, free_ed );
        usb_hstd_OhciRemoveEndpoint( device_address, n, USB_HCI_DIRECTION_IN, free_ed );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciRemoveDevice
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciGetRootDeviceSpeed
 *
 *  Description:    OHCI Return speed information
 *
 *  Parameters:     USB_OHCI_HCD_DEVICE_DATA_P device_data ; Device Data pointer
 *                  uint8_t portnum                        ; Port No
 *
 *  Return Value:   uint8_t                                ; Speed
 *
 **********************************************************************************************************************/
static uint8_t usb_hstd_OhciGetRootDeviceSpeed( USB_OHCI_HCD_DEVICE_DATA_P device_data, uint8_t portnum )
{
    uint32_t    *port_status_reg;

    port_status_reg = (uint32_t *)&( USB_HOST->HcRhPortStatus1.HcRhPortStatus1_A.LONG );
    port_status_reg += portnum;

    if((*port_status_reg & 0x00000200) == 0)
    {
        return( USB_HCI_DEVSPEED_FS );
    }

    return( USB_HCI_DEVSPEED_LS );
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciGetRootDeviceSpeed
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciProcessPausedED
 *
 *  Description:    OHCI Pause Endpoint
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ed ; Endpoint Descriptor Pointer
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_OhciProcessPausedED( USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ed )
{
    USB_OHCI_HCD_ENDPOINT_P             endpoint;
//  USB_OHCI_REQUEST_P                  ohci_req;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P  td;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P  last = NULL;
    USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P  *previous;
    boolean_t                           b4head = TRUE;

    endpoint = ed->Endpoint;

    if(endpoint == NULL)
    {
        return;
    }

    td = endpoint->HcdHeadP;            /* set head TD */
    previous = &endpoint->HcdHeadP;

    while(td != endpoint->HcdTailP)
    {

        if((ed->HcED.HeadP & ~0xF) == td->PhysicalAddress)
        {
            b4head = FALSE;
        }

        if((ed->ListIndex == USB_OHCI_ED_EOF) || (td->CancelPending))  /* cancel TD */
        {
//          ohci_req = td->UsbdRequest;
            usb_hstd_OhciRemoveListEntry( &td->RequestList );
//            if(usb_hstd_OhciIsListEmpty(&ohci_req->HcdList) == TRUE)
//            if(usb_hstd_OhciIsListEmpty(&ohci_req->HcdList) == FALSE)
//          {
//              ohci_req->Status = USB_OHCI_RS_CANCELED;
//              usb_hstd_OhciCompleteTransferRequest( ohci_req );
//          }
            *previous = td->NextHcdTD;      /* point around TD */
            if(last != NULL)
            {
                last->HcTD.NextTD = td->HcTD.NextTD;
            }
            if(b4head == TRUE)              /* TD on delayed Done List */
            {
                td->TDStatus = USB_OHCI_TD_CANCELED;
            }
            else
            {
                usb_hstd_OhciFreeTransferDescriptor( td );
            }
        }
        else                                                            /* don't cancel TD */
        {
            previous = &td->NextHcdTD;
            if(b4head == FALSE)
            {
                last = td;
            }
        }
        td = *previous;

    }
    ed->HcED.HeadP = endpoint->HcdHeadP->PhysicalAddress | ( ed->HcED.HeadP & USB_OHCI_HCED_HEADP_CARRY );
    ed->HcED.Control.K = FALSE;
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciProcessPausedED
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hstd_OhciRemoveED
 *
 *  Description:    OHCI Remove Endpoint
 *
 *  Parameters:     USB_OHCI_HCD_ENDPOINT_P endpoint ; Endpoint Pointer
 *                  boolean_t free_ed                ; endpoint free flag
 *
 *  Return Value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_OhciRemoveED( USB_OHCI_HCD_ENDPOINT_P endpoint, boolean_t free_ed )
{
    USB_OHCI_HCD_DEVICE_DATA_P          device_data;
    USB_OHCI_HCD_ED_LIST_P              list;
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  ed;
    USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  previous_ed;
    uint32_t                            list_disable;

    device_data = endpoint->DeviceData;
    list = &device_data->EdList[ endpoint->ListIndex ];
    ed = endpoint->HcdED;

    /* Prevent Host Controller from processing this ED */
    ed->HcED.Control.K = TRUE;

    /* Unlink the ED from the physical ED list */
    if(ed->Link.Blink == &list->Head)   /* Removing ED is located in head of ED List */
    {
        /* Remove ED from head */
        *list->PhysicalHead = ed->HcED.NextED;
        previous_ed = NULL;
    }
    else
    {
        /* Remove ED from list */
        previous_ed = ( USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P )usb_hstd_OhciScanContainingRecord(
                        ed->Link.Blink, USB_OHCI_CR_ENDPOINT_DESCRIPTOR, USB_OHCI_CR_LINK );
        if(previous_ed != NULL)
        {
            previous_ed->HcED.NextED = ed->HcED.NextED;
        }
    }

    /* Unlink ED from HCD list */
    usb_hstd_OhciRemoveListEntry( &ed->Link );

    /* If freeing the endpoint, remove the descriptor */
    if(free_ed == TRUE)     /* TD queue must already be empty */
    {
        endpoint->HcdED = NULL;
        ed->Endpoint = NULL;
    }

    /* Check to see if interrupt processing is required to free the ED */
    switch(endpoint->Type)
    {
        case USB_EP_CNTRL:
            list_disable = ~USB_OHCI_CONTROLLISTENABLE;
            break;
        case USB_EP_BULK:
            list_disable = ~USB_OHCI_BULKLISTENABLE;
            break;
        default:
            device_data->EdList[ endpoint->ListIndex ].Bandwidth -= endpoint->Bandwidth;
            device_data->MaxBandwidthInUse = usb_hstd_OhciCheckBandwidth( device_data, USB_OHCI_ED_INTERRUPT_32ms, &list_disable );
            list_disable = 0;
    }

    ed->ListIndex = USB_OHCI_ED_EOF;   /* ED is not on a list now */

    /* Set ED for reclamation */
    USB_HOST->HcIntStatus.LONG = USB_OHCI_HC_INT_SOF;  /* clear SOF interrupt pending */

    if(list_disable != 0)
    {
        USB_HOST->HcControl.LONG &= list_disable;
        ed->ReclamationFrame = usb_hstd_OhciGet32BitFrameNumber( device_data ) + 1;
        usb_hstd_OhciInsertTailList( &device_data->StalledEDReclamation, &ed->Link );
        USB_HOST->HcIntEnable.LONG = USB_OHCI_HC_INT_SOF;  /* interrupt on next SOF */
    }
    else
    {
        ed->ReclamationFrame = usb_hstd_OhciGet32BitFrameNumber( device_data ) + 1;
        usb_hstd_OhciInsertTailList( &device_data->RunningEDReclamation, &ed->Link );
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_OhciRemoveED
 **********************************************************************************************************************/