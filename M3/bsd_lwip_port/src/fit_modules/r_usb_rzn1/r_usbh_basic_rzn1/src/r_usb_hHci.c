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
 * FILE         :  r_usb_hHci.c
 * Description  : USB HCI Common Code
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_usb_hHciLocal.h"

/***********************************************************************************************************************
 Define
 **********************************************************************************************************************/
#define USB_HCI_MESS_MAX    32  /* Maximum number of HCI message buffers */


/***********************************************************************************************************************
 Typedef
 **********************************************************************************************************************/
typedef void ( *USB_HCI_TASK_FUNC )( void );

typedef struct {
    int16_t         sem_id;
    int16_t         tsk_id;
    uint32_t        mess_write;
    uint32_t        mess_read;
    uint32_t        mess_cnt;
    uint32_t        data_buff[ USB_HCI_MESS_MAX ];
    int8_t          mess_buff[ USB_HCI_MESS_MAX ];
} USB_HCI_TASK_INFO;

typedef struct {
    USB_HCI_TASK_INFO  task[ USB_HCI_TASK_MAX ];
} USB_HCI_MANAGE_INFO;


/***********************************************************************************************************************
 Prototype
 **********************************************************************************************************************/
/* Global function */
void                usb_hstd_HciInterruptHandler(IRQn_Type *irq_num_ptr);
void                usb_hstd_HciSendMessageFromInt(int32_t task_no, int8_t message, uint32_t data);
USB_HCI_DEVICE     *usb_hstd_HciAllocDevinfo(void);
void                usb_hstd_HciFreeDevinfo(uint32_t devadd);
uint32_t            usb_hstd_HciGetPollrate(USB_HCI_TR_REQ *tr_req);
void                usb_hstd_HciLockResouce(void);
void                usb_hstd_HciUnlockResouce(void);
USB_HCI_TR_REQ     *usb_hstd_HciAllocTransferRequest(void);


/* Static function */
static void         usb_hstd_HciSetDisconnectFlag(uint32_t devadd);
static USB_HCI_ENDPOINT_DESCRIPTOR* usb_hstd_HciSearchEndpointDescriptor( USB_HCI_TR_REQ *tr_req );

/* API function */
void                r_usb_hstd_HciTask(void);
int32_t             r_usb_hstd_HciInit(USB_HCI_CB_INFO *cb_info);
void                r_usb_hstd_HciDeinit(void);
uint16_t            r_usb_hstd_HciMakeTransferRequest(void* utr_p,
                                       void* setup,
                                       uint32_t devaddr,
                                       uint32_t epnum,
                                       uint32_t eptype,
                                       uint32_t epdir,
                                       uint32_t tranlen,
                                       uint32_t tranadr,
                                       uint32_t mps);
void                r_usb_hstd_HciCancelTransferRequest(uint32_t devaddr,
                                         uint32_t epnum,
                                         uint32_t eptype,
                                         uint32_t epdir);
void                r_usb_hstd_HciDisconnect(uint32_t devadd);
uint16_t            r_usb_hstd_HciGetDeviceAddressOfRootpoot(uint16_t rootport);
uint16_t            r_usb_hstd_HciSetDeviceAddressOfRootpoot(uint16_t rootport, uint16_t devaddr);
uint32_t            r_usb_hstd_HciGetDeviceSpeed(uint16_t devaddr);
USB_HCI_DEVICE     *r_usb_hstd_HciGetDeviceInformation(uint16_t devaddr);
uint32_t            r_usb_hstd_HciGetPortCurrentConnectStatus(uint16_t rootport);
void                r_usb_hstd_HciPortReset(uint16_t rootport);
void                r_usb_hstd_HciPortSuspend(uint16_t rootport);
void                r_usb_hstd_HciPortResume(uint16_t rootport);
uint16_t            r_usb_hstd_HciGetPidStatus(uint16_t devaddr, uint16_t epnum);
void                r_usb_hstd_HciSetHubInfo(uint32_t hubaddr, uint32_t hubportnum, uint32_t devaddr, uint32_t devspeed);
void                r_usb_hstd_HciSetDeviceAddressOfHubport(uint16_t hubaddr, uint16_t devaddr);
void                r_usb_hstd_HciWaitTime( uint32_t ms );

/***********************************************************************************************************************
 Variable
 **********************************************************************************************************************/
/* global */
USB_HCI_CB_INFO            usb_ghstd_HciCallback;
USB_HCI_TR_REQ             usb_ghstd_HciTransferRequest[USB_HCI_TRREQ_NUM];

/* static */
/* 8Byte Buffer for setup packet */
static uint32_t            hci_SetupBuffer[USB_HCI_TRREQ_NUM][USB_HCI_SETUP_DATA_SIZE / sizeof(uint32_t)];
static USB_HCI_DEVICE      hci_DeviceInfo[ USB_HCI_DEVICE_NUM ];
static USB_HCI_MANAGE_INFO hci_ManageInfo;
static uint16_t            hci_TmpAddr;

/***********************************************************************************************************************
 External
 **********************************************************************************************************************/
extern void         usb_hstd_IntEnable(void);
extern void         usb_hstd_IntDisable(void);
#ifdef USB_HOST_COMPLIANCE_MODE
extern void         usb_hstd_ElectricalTestMode( uint16_t product_id, uint16_t port );
#endif /* USB_HOST_COMPLIANCE_MODE */

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/

/* Global function */
/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciTask
 *
 *  Description:    HCI Task
 *
 *  Parameters:     void
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void r_usb_hstd_HciTask(void)
{
    USB_ER_t           Err;
    USB_HCI_TASK_INFO  *task_info;
    uint32_t           message;
    uint32_t           data;
    uint8_t            dummy;

    /* receive message */
    Err = USB_RCV_MSG(USB_HCI_MBX, &dummy);
    if(Err != USB_OK)
    {
        return;
    }

    task_info = &hci_ManageInfo.task[USB_HCI_TASK];

    /* Taking out of message */
    if(task_info->mess_cnt)
    {
        usb_hstd_IntDisable();

        message = task_info->mess_buff[task_info->mess_read];
        data    = task_info->data_buff[task_info->mess_read];
        task_info->mess_read++;
        if(USB_HCI_MESS_MAX <= task_info->mess_read)
        {
            task_info->mess_read = 0ul;
        }
        task_info->mess_cnt--;

        usb_hstd_IntEnable();

        /* Processing of message */
        switch(message)
        {
            case USB_HCI_MESS_EHCI_PORT_CHANGE_DETECT:
                USB_HCI_PRINTF0( "USB_HCI_MESS_EHCI_PORT_CHANGE_DETECT \n" );
                usb_hstd_EhciIntPortChange();
                break;

            case USB_HCI_MESS_EHCI_HOST_SYSTEM_ERROR:
                USB_HCI_PRINTF0_R( "USB_HCI_MESS_EHCI_HOST_SYSTEM_ERROR \n" );
                break;

            case USB_HCI_MESS_EHCI_USBINT:
                USB_HCI_PRINTF0( "USB_HCI_MESS_EHCI_USBINT \n" );
                usb_hstd_EhciIntTransferEnd();
                break;

            case USB_HCI_MESS_EHCI_USBERRINT:
                USB_HCI_PRINTF0_R( "USB_HCI_MESS_EHCI_USBERRINT \n" );
                usb_hstd_EhciIntTransferEnd();
                break;

            case USB_HCI_MESS_EHCI_FRAME_LIST_ROLLOVER:
                USB_HCI_PRINTF0( "USB_HCI_MESS_EHCI_FRAME_LIST_ROLLOVER \n" );
                break;

            case USB_HCI_MESS_EHCI_INTERRUPT_ON_ASYNC_ADVANCE:
                USB_HCI_PRINTF0( "USB_HCI_MESS_EHCI_INTERRUPT_ON_ASYNC_ADVANCE \n" );
                break;

            case USB_HCI_MESS_OHCI_INT:
                USB_HCI_PRINTF1( "USB_HCI_MESS_OHCI_INT : %08x \n", data );
                usb_hstd_OhciMainRoutine(data);
                break;

            default:
                USB_HCI_PRINTF0_R( "Error: HCI transfer task unknown message \n" );
                break;
        }
    }
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciTask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_HciInterruptHandler
 *
 *  Description:    Interrupt Routine for HCI
 *
 *  Parameters:     void
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_HciInterruptHandler(IRQn_Type *irq_num_ptr)
{
    if (RZN1_IRQ_USBH_BIND != *irq_num_ptr)
    {
        while(1);
    }

    /* Check ohci */
    usb_hstd_OhciInterruptHandler();

    /* Check ehci */
    usb_hstd_EhciInterruptHandler();
}
/***********************************************************************************************************************
 End of function usb_hstd_HciInterruptHandler
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_HciSendMessageFromInt
 *
 *  Description:    Message sending from interrupt
 *
 *  Parameters:     int32_t task_no ; task no
 *              : int8_t message  ; message type
 *              : void *data      ; data pointer
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_HciSendMessageFromInt( int32_t task_no, int8_t message, uint32_t data )
{
    USB_HCI_TASK_INFO  *task_info;

    task_info = &hci_ManageInfo.task[ task_no ];

    /* Registration of message */
    task_info->mess_buff[ task_info->mess_write ] = message;
    task_info->data_buff[ task_info->mess_write ] = data;
    task_info->mess_write++;
    if(USB_HCI_MESS_MAX <= task_info->mess_write)
    {
        task_info->mess_write = 0ul;
    }
    task_info->mess_cnt++;

    if(task_info->mess_cnt > USB_HCI_MESS_MAX)
    {
        /* Message buffer overflow  */
        USB_HCI_PRINTF1_R( "Error: HCI send message buffer overflow( task_no:%d ) \n", task_no );
    }

    /* Notification of message sending */
    USB_SND_MSG(USB_HCI_MBX, (USB_MSG_t *)NULL);
}
/***********************************************************************************************************************
 End of function usb_hstd_HciSendMessageFromInt
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_HciAllocDevinfo
 *
 *  Description:    Allocate Device-Information-Memory
 *
 *  Parameters:     void
 *
 *  Return value:   USB_HCI_DEVICE * ; Device-Information-Memory pointer
 *
 **********************************************************************************************************************/
USB_HCI_DEVICE *usb_hstd_HciAllocDevinfo(void)
{
    USB_HCI_DEVICE     *ret = NULL;
    USB_HCI_DEVICE     *devinfo;
    uint32_t            i;

    usb_hstd_HciLockResouce();

    devinfo = &hci_DeviceInfo[0];
    for(i = 0; i < USB_HCI_DEVICE_NUM; i++, devinfo++)
    {
        if(devinfo->bit.enable == FALSE)
        {
            memset(devinfo, 0, sizeof(USB_HCI_DEVICE));
            devinfo->bit.enable = TRUE;
            ret                 = devinfo;
            break;
        }
    }

    usb_hstd_HciUnlockResouce();

    if(ret == NULL)
    {
        USB_HCI_PRINTF0_R( "--------------------------------------------------\n" );
        USB_HCI_PRINTF0_R( "Memory Allocation Error: usb_hstd_HciAllocDevinfo\n" );
        USB_HCI_PRINTF0_R( "--------------------------------------------------\n" );
    }

    return(ret);
}
/***********************************************************************************************************************
 End of function usb_hstd_HciAllocDevinfo
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_HciFreeDevinfo
 *
 *  Description:    Free Device-Information-Memory
 *
 *  Parameters:     uint32_t devadd ; device address
 *
 *  Return value:   void
 *
 *   When the device is HUB, the disconnection process of the down port is executed.
 **********************************************************************************************************************/
void usb_hstd_HciFreeDevinfo(uint32_t devadd)
{
    USB_HCI_DEVICE     *devinfo;
    uint32_t            n;
    uint32_t            i;

    devinfo = &hci_DeviceInfo[0];
    for(i = 0; i < USB_HCI_DEVICE_NUM; i++, devinfo++)
    {
        if(devinfo->bit.enable == TRUE)
        {
            if(devinfo->bit.devnum == devadd)
            {
                /* When the device is HUB, the disconnection process of the down port is executed.  */
                for(n = 0; n < USB_HCI_HUBPORT_NUM; n++)
                {
                    if(devinfo->hubdevinfo.devnum[n] != 0)
                    {
                        r_usb_hstd_HciDisconnect(devinfo->hubdevinfo.devnum[n]);
                    }
                }
                usb_hstd_HciLockResouce();
                /* clear device info */
                devinfo->bit.enable = FALSE;
                usb_hstd_HciUnlockResouce();
            }
            else
            {
                /* The HUB registered information is deleted for the device connected with HUB. */
                for(n = 0; n < USB_HCI_HUBPORT_NUM; n++)
                {
                    if(devinfo->hubdevinfo.devnum[n] == devadd)
                    {
                        devinfo->hubdevinfo.devnum[n]   = 0;
                        devinfo->hubdevinfo.devspeed[n] = 0;
                    }
                }
            }
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_HciFreeDevinfo
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_HciGetPollrate
 *
 *  Description:    Getting of Pollrate
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req ; transfer request pointer
 *
 *  Return value:   uint32_t               ; pollrate( uFrame unit )
 *
 **********************************************************************************************************************/
uint32_t usb_hstd_HciGetPollrate(USB_HCI_TR_REQ *tr_req)
{
    USB_HCI_ENDPOINT_DESCRIPTOR    *ep_desc;
    uint32_t                        ep_interbal;
    uint32_t                        pollrate = 0;

    ep_desc = usb_hstd_HciSearchEndpointDescriptor(tr_req);
    if(ep_desc != NULL)
    {
        ep_interbal = ep_desc->bInterval;
        switch(tr_req->bit.eptype)
        {
            case USB_EP_INT:
                if(tr_req->devinfo->bit.devspeed == USB_HCI_DEVSPEED_HS)
                {
                    pollrate = 1;
                    for(ep_interbal--; ep_interbal != 0; ep_interbal--)
                    {
                        pollrate *= 2;
                    }
                }
                else
                {
                    pollrate = ep_interbal * 8;
                }
                break;

            case USB_EP_ISO:
                if(tr_req->devinfo->bit.devspeed == USB_HCI_DEVSPEED_HS)
                {
                    pollrate = 1;
                    for(ep_interbal--; ep_interbal != 0; ep_interbal--)
                    {
                        pollrate *= 2;
                    }
                }
                else
                {
                    if(tr_req->devinfo->devicedesc.bcdUSB == 0x0200)
                    {
                        pollrate = 1;
                        for(ep_interbal--; ep_interbal != 0; ep_interbal--)
                        {
                            pollrate *= 2;
                        }
                        pollrate *= 8;
                    }
                    else
                    {
                        pollrate = 8;
                    }
                }
                break;

            default:
                break;
        }
    }

    return(pollrate);
}
/***********************************************************************************************************************
 End of function usb_hstd_HciGetPollrate
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_HciLockResouce
 *
 *  Description:    HCI Lock resource
 *
 *  Parameters:     void
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_HciLockResouce(void)
{
}
/***********************************************************************************************************************
 End of function usb_hstd_HciLockResouce
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_HciUnlockResouce
 *
 *  Description:    HCI Lock resource
 *
 *  Parameters:     void
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_HciUnlockResouce(void)
{
}
/***********************************************************************************************************************
 End of function usb_hstd_HciUnlockResouce
 **********************************************************************************************************************/

/* Static function */

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_HciSetDisconnectFlag
 *
 *  Description:    Device Disconnect Flag Set
 *
 *  Parameters:     uint32_t devadd ; device address
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
static void usb_hstd_HciSetDisconnectFlag(uint32_t devadd)
{
    USB_HCI_DEVICE     *devinfo;
    uint32_t            n;

    devinfo = r_usb_hstd_HciGetDeviceInformation(devadd);

    /* Disconnect Request Flag Set */
    devinfo->bit.disconnect_req = TRUE;

    /* Hub Port Device Disconnect */
    for(n = 0; n < USB_HCI_HUBPORT_NUM; n++)
    {
        if(devinfo->hubdevinfo.devnum[n] != 0)
        {
            usb_hstd_HciSetDisconnectFlag(devinfo->hubdevinfo.devnum[n]);
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_HciSetDisconnectFlag
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_HciSearchEndpointDescriptor
 *
 *  Description:    Searching of endpoint descriptor address
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req ; transfer request pointer
 *
 *  Return value:   USB_HCI_ENDPOINT_DESCRIPTOR * ; endpoint descriptor pointer
 *
 **********************************************************************************************************************/
static USB_HCI_ENDPOINT_DESCRIPTOR* usb_hstd_HciSearchEndpointDescriptor(USB_HCI_TR_REQ *tr_req)
{
    USB_HCI_ENDPOINT_DESCRIPTOR    *epdesc;
    USB_HCI_DESCRIPTOR_HEADER      *desc_head;
    USB_HCI_DEVICE                 *devinfo;
    uint32_t                        n;
    uint8_t                         ep_direction;

    n = 0;
    devinfo = tr_req->devinfo;

    if(tr_req->bit.direction == USB_HCI_DIRECTION_IN)
    {
        ep_direction = USB_EP_IN;
    }
    else
    {
        ep_direction = USB_EP_OUT;
    }

    while(n < USB_HCI_CONFIGDESC_BUFFSIZE)
    {
        desc_head = (USB_HCI_DESCRIPTOR_HEADER *)((uint8_t *)&devinfo->rawconfigdesc[0] + n);
        if(desc_head->bDescriptorType == USB_DT_ENDPOINT)
        {
            epdesc = (USB_HCI_ENDPOINT_DESCRIPTOR *)desc_head;
            if(((epdesc->bmAttributes & USB_EP_TRNSMASK) == tr_req->bit.eptype)
                && ((epdesc->bEndpointAddress & USB_EP_DIRMASK) == ep_direction)
                && ((epdesc->bEndpointAddress & USB_EP_NUMMASK) == tr_req->bit.epnum))
            {
                return(epdesc);
            }
        }
        n += desc_head->bLength;
    }
    return(NULL);
}
/***********************************************************************************************************************
 End of function usb_hstd_HciSearchEndpointDescriptor
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_HciAllocTransferRequest
 *
 *  Description:    Allocate Transfer-Request-Memory
 *
 *  Parameters:     void
 *
 *  Return value:   USB_HCI_TR_REQ * ; Transfer-Request-Memory pointer
 *
 **********************************************************************************************************************/
USB_HCI_TR_REQ* usb_hstd_HciAllocTransferRequest( void )
{
    USB_HCI_TR_REQ     *ret = NULL;
    USB_HCI_TR_REQ     *tr_req;
    uint32_t            i;

    usb_hstd_HciLockResouce();

    tr_req = &usb_ghstd_HciTransferRequest[0];
    for(i = 0; i < USB_HCI_TRREQ_NUM; i++, tr_req++)
    {
        if(tr_req->bit.enable == FALSE)
        {
            memset(tr_req, 0, sizeof(USB_HCI_TR_REQ));

            tr_req->bit.enable  = TRUE;
            tr_req->setupbuf    = &hci_SetupBuffer[i][0];
            ret                 = tr_req;
            break;
        }
    }

    usb_hstd_HciUnlockResouce();

    if(NULL == ret)
    {
        USB_HCI_PRINTF0_R( "-----------------------------------------------------------\n" );
        USB_HCI_PRINTF0_R( "Memory Allocation Error: usb_hstd_HciAllocTransferRequest\n" );
        USB_HCI_PRINTF0_R( "-----------------------------------------------------------\n" );
    }

    return(ret);
}
/***********************************************************************************************************************
 End of function usb_hstd_HciAllocTransferRequest
 **********************************************************************************************************************/

/* API function */
/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciInit
 *
 *  Description:    Initialize HCI
 *
 *  Parameters:     USB_HCI_CB_INFO *cb_info ; callback function information
 *
 *  Return value:   uint32_t                  ; status
 *
 **********************************************************************************************************************/
int32_t r_usb_hstd_HciInit(USB_HCI_CB_INFO *cb_info)
{
    if(NULL == cb_info)
    {
        return(USB_ERROR);
    }
    if((NULL == cb_info->attach_cb)
        || (NULL == cb_info->detach_cb)
        || (NULL == cb_info->over_current_cb)
        || (NULL == cb_info->tr_end_cb))
    {
        return(USB_ERROR);
    }

    /* set callback function information */
    usb_ghstd_HciCallback = *cb_info;

    /* HCI management memory initialization */
    memset(&hci_ManageInfo, 0, sizeof(hci_ManageInfo));

    usb_hstd_HciLockResouce();

    /* Initialize Transfer-Request Array */
    memset(&usb_ghstd_HciTransferRequest[0], 0, sizeof(usb_ghstd_HciTransferRequest));
    /* Initialize Device-Info Array */
    memset(&hci_DeviceInfo[0], 0, sizeof(hci_DeviceInfo));

    usb_hstd_HciUnlockResouce();

    /* Init EHCI */
    if(USB_OK != usb_hstd_EhciInit())
    {
        return(USB_ERROR);
    }

    /* Init OHCI */
    if(USB_OK != usb_hstd_OhciInit())
    {
        return(USB_ERROR);
    }

    /* interrupt enable */
//    usb_cstd_UsbintInit();

    return(USB_OK);
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciInit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciDeinit
 *
 *  Description:    Deinitialize HCI
 *
 *  Parameters:     void
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void r_usb_hstd_HciDeinit(void)
{
    USB_HCI_DEVICE     *devinfo;
    uint32_t            i;

    /* All transfers are stopped, and all devices are disconnect. */
    devinfo = &hci_DeviceInfo[0];
    for(i = 0; i < USB_HCI_DEVICE_NUM; i++, devinfo++)
    {
        if(devinfo->bit.enable == FALSE)
        {
            r_usb_hstd_HciDisconnect(devinfo->bit.devnum);
        }
    }

    usb_hstd_EhciDeinit();     /* EHCI H/W reset */
    usb_hstd_OhciDeinit();     /* OHCI H/W reset */

    memset(&hci_ManageInfo, 0, sizeof(hci_ManageInfo));
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciDeinit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciMakeTransferRequest
 *
 *  Description:    Making of Transfer Request
 *
 *  Parameters:     USB_HCI_TR_REQ *tr_req ; transfer request information
 *
 *  Return value:   uint16_t
 *
 **********************************************************************************************************************/
uint16_t r_usb_hstd_HciMakeTransferRequest(void* utr_p,
                                       void* setup,
                                       uint32_t devaddr,
                                       uint32_t epnum,
                                       uint32_t eptype,
                                       uint32_t epdir,
                                       uint32_t tranlen,
                                       uint32_t tranadr,
                                       uint32_t mps)
{
    USB_HCI_TR_REQ  *tr_req;
    uint32_t    i;
    uint8_t     *dst_p;
    uint8_t     *src_p;

    tr_req = usb_hstd_HciAllocTransferRequest();
    if(tr_req == NULL)
    {
        return USB_ERROR;
    }

    /* Device Address */
    tr_req->bit.devadrs   = devaddr;

    /* Get Device Information */
    if( devaddr == 0 )
    {
        devaddr = hci_TmpAddr;
    }
    tr_req->devinfo  = r_usb_hstd_HciGetDeviceInformation( devaddr );
    /* Check Devinfo Address */
    if ( tr_req->devinfo == NULL )
    {
        tr_req->bit.enable = FALSE;
        USB_HCI_PRINTF0_R( "-------------\n" );
        USB_HCI_PRINTF0_R( " Devinfo NULL\n" );
        USB_HCI_PRINTF0_R( "-------------\n" );
        return USB_ERROR;
    }
    /* Check Connection */
    if ( tr_req->devinfo->bit.disconnect_req == TRUE ) {
        tr_req->bit.enable = FALSE;
        USB_HCI_PRINTF0_R( "-------------\n" );
        USB_HCI_PRINTF0_R( " Disconnected\n" );
        USB_HCI_PRINTF0_R( "-------------\n" );
        return USB_ERROR;
    }


    /* Endpoint Type */
    tr_req->bit.eptype    = eptype;
    /* Direction */
    if (epdir == USB_EP_OUT) {
        tr_req->bit.direction = USB_HCI_DIRECTION_OUT;
    } else {
        tr_req->bit.direction = USB_HCI_DIRECTION_IN;
    }
    /* Endpoint Number */
    tr_req->bit.epnum     = epnum;
    /* Transfer Size */
    tr_req->trsize        = tranlen;
    /* Transfer Data Buffer */
    tr_req->databuf       = tranadr;
    /* Set UTR Pointer */
    tr_req->utr_p         = utr_p;

    /* Control Transfer */
    if( eptype == USB_EP_CNTRL )
    {
        /* Setup Buffer */
        /* Because the data format is different, location is converted. */
        dst_p = (uint8_t *)tr_req->setupbuf;
        src_p = (uint8_t *)setup;
        for ( i = 0; i < USB_HCI_SETUP_DATA_SIZE; i++ ) {
            *dst_p++ = *src_p++;
        }

        /* MaxPacket Size */
        if ( tr_req->devinfo->devicedesc.bMaxPacketSize0 == 0 ) {
            if ( tr_req->devinfo->bit.devspeed == USB_HCI_DEVSPEED_LS ) {
                tr_req->bit.mps = 0x08;
            } else {
                tr_req->bit.mps = 0x40;
            }
        } else {
            tr_req->bit.mps = tr_req->devinfo->devicedesc.bMaxPacketSize0;
        }
    }
    /* For Bulk, Interrupt and  Isochronous Transfer */
    else if ( (eptype == USB_EP_ISO) || (eptype == USB_EP_BULK) || (eptype == USB_EP_INT) )
    {
        tr_req->bit.mps = mps;
    }

    switch(tr_req->devinfo->bit.hctype)
    {
        case USB_HCI_HCTYPE_EHCI:
            usb_hstd_EhciMakeTransferRequest(tr_req);
            break;

        case USB_HCI_HCTYPE_OHCI:
            usb_hstd_OhciMakeTransferRequest(tr_req);
            break;

        default:
            break;
    }
    return USB_OK;
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciMakeTransferRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciCancelTransferRequest
 *
 *  Description:    Message sending of transfer request
 *
 *  Parameters:     uint32_t devadrs   ; device address
 *              : uint32_t epnum     ; endpoint no
 *              : uint32_t direction ; direction
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void r_usb_hstd_HciCancelTransferRequest(uint32_t devaddr,
                                         uint32_t epnum,
                                         uint32_t eptype,
                                         uint32_t epdir)
{
    USB_HCI_TR_REQ     *tr_req;
    uint32_t            i;

    tr_req = &usb_ghstd_HciTransferRequest[0];
    for(i = 0; i < USB_HCI_TRREQ_NUM; i++, tr_req++)
    {
        if(tr_req->bit.enable == TRUE)
        {
            if(epdir == USB_EP_OUT){
                epdir = USB_HCI_DIRECTION_OUT;
            } else {
                epdir = USB_HCI_DIRECTION_IN;
            }

            if( (tr_req->bit.devadrs == devaddr) && (tr_req->bit.epnum == epnum) &&
                (tr_req->bit.direction == epdir) &&  (tr_req->bit.eptype == eptype) )
            {
                if(tr_req->hci_info != NULL)
                {
                    tr_req->devinfo  = r_usb_hstd_HciGetDeviceInformation( devaddr );
                    if(tr_req->devinfo->bit.hctype == USB_HCI_HCTYPE_EHCI)
                    {
                        usb_hstd_EhciCancelTransferRequest(tr_req);
                    }
                    else if(tr_req->devinfo->bit.hctype == USB_HCI_HCTYPE_OHCI)
                    {
                        usb_hstd_OhciCancelTransferRequest(tr_req);
                    }
                }
                return;
            }
        }
    }
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciCancelTransferRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciDisconnect
 *
 *  Description:    Device Disconnect
 *
 *  Parameters:     uint32_t devadd ; device address
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void r_usb_hstd_HciDisconnect(uint32_t devadd)
{
    USB_HCI_DEVICE     *devinfo;

    devinfo = r_usb_hstd_HciGetDeviceInformation(devadd);
    if(devinfo != NULL)
    {
        /* Disconnect Request Flag Set */
        usb_hstd_HciSetDisconnectFlag(devadd);

        switch(devinfo->bit.hctype)
        {
            case USB_HCI_HCTYPE_EHCI:
                usb_hstd_EhciDisconnect(devadd);
                usb_hstd_HciFreeDevinfo(devadd);
                break;

            case USB_HCI_HCTYPE_OHCI:
                usb_hstd_OhciDisconnect(devadd);
                usb_hstd_HciFreeDevinfo(devadd);
                break;

            default:
                break;
        }
    }
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciDisconnect
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciGetDeviceAddressOfRootpoot
 *
 *  Description:    Getting of device address of rootpoot
 *
 *  Parameters:     uint16_t rootport ; rootport no
 *
 *  Return value:   uint16_t          ; device address
 *
 **********************************************************************************************************************/
uint16_t r_usb_hstd_HciGetDeviceAddressOfRootpoot(uint16_t rootport)
{
    uint16_t    devaddr;

    devaddr = usb_hstd_EhciGetDeviceAddressOfRootpoot(rootport);
    if(USB_HCI_NODEVICE == devaddr)
    {
        devaddr = usb_hstd_OhciGetDeviceAddressOfRootpoot(rootport);
    }
    return(devaddr);
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciGetDeviceAddressOfRootpoot
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciSetDeviceAddressOfRootpoot
 *
 *  Description:    The device address of the route port is set.
 *
 *  Parameters:     uint16_t rootport ; rootport no
 *                  uint16_t devaddr  ; device address
 *
 *  Return value:   uint16_t          ; device address
 *
 **********************************************************************************************************************/
uint16_t r_usb_hstd_HciSetDeviceAddressOfRootpoot(uint16_t rootport, uint16_t devaddr)
{
    uint16_t    ret_devaddr;

    hci_TmpAddr = devaddr;

    ret_devaddr = usb_hstd_EhciSetDeviceAddressOfRootpoot(rootport, devaddr);
    if(USB_HCI_NODEVICE == ret_devaddr)
    {
        ret_devaddr = usb_hstd_OhciSetDeviceAddressOfRootpoot(rootport, devaddr);
    }
    return(ret_devaddr);
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciSetDeviceAddressOfRootpoot
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciGetDeviceSpeed
 *
 *  Description:    Getting of device speed
 *
 *  Parameters:     uint16_t devaddr  ; device address
 *
 *  Return value:   uint16_t          ; device speed
 *
 **********************************************************************************************************************/
uint32_t r_usb_hstd_HciGetDeviceSpeed(uint16_t devaddr)
{
    USB_HCI_DEVICE     *devinfo;
    uint32_t            i;

    devinfo = &hci_DeviceInfo[0];
    for(i = 0; i < USB_HCI_DEVICE_NUM; i++, devinfo++)
    {
        if(devinfo->bit.enable == TRUE)
        {
            if(devinfo->bit.devnum == devaddr)
            {
                return(devinfo->bit.devspeed);
            }
        }
    }
    /* Error */
    return(0xFF);
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciGetDeviceSpeed
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciGetDeviceInformation
 *
 *  Description:    Getting of device information
 *
 *  Parameters:     uint16_t devaddr  ; device address
 *
 *  Return value:   USB_HCI_DEVICE *  ; device information
 *
 **********************************************************************************************************************/
USB_HCI_DEVICE *r_usb_hstd_HciGetDeviceInformation(uint16_t devaddr)
{
    USB_HCI_DEVICE     *devinfo;
    uint32_t            i;

    devinfo = &hci_DeviceInfo[0];
    for(i = 0; i < USB_HCI_DEVICE_NUM; i++, devinfo++)
    {
        if(devinfo->bit.enable == TRUE)
        {
            if(devinfo->bit.devnum == devaddr)
            {
                return(devinfo);
            }
        }
    }
    /* Error */
    return(NULL);
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciGetDeviceInformation
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciGetPortCurrentConnectStatus
 *
 *  Description:    Get Port Connection Status
 *
 *  Parameters:     uint16_t rootport ; rootport no
 *
 *  Return value:   uint32_t          ; Current Connect Status( 1:Connected, 0:Not Connect );
 *
 **********************************************************************************************************************/
uint32_t r_usb_hstd_HciGetPortCurrentConnectStatus(uint16_t rootport)
{
    return(usb_hstd_EhciGetPortCurrentConnectStatus(rootport));
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciGetPortCurrentConnectStatus
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciPortReset
 *
 *  Description:    Port Reset
 *
 *  Parameters:     uint16_t rootport ; rootport no
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void r_usb_hstd_HciPortReset(uint16_t rootport)
{
    uint16_t    devaddr;

    devaddr = usb_hstd_EhciGetDeviceAddressOfRootpoot( rootport );
    if(USB_HCI_NODEVICE != devaddr)
    {
        usb_hstd_EhciPortReset(rootport);
        usb_ghstd_HciCallback.port_reset_cb(rootport);
            }
    else
    {
        devaddr = usb_hstd_OhciGetDeviceAddressOfRootpoot(rootport);
        if(USB_HCI_NODEVICE != devaddr)
        {
            usb_hstd_OhciPortReset(rootport);
            usb_ghstd_HciCallback.port_reset_cb(rootport);
        }
    }
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciPortReset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciPortSuspend
 *
 *  Description:    Port Suspend
 *
 *  Parameters:     uint16_t rootport ; rootport no
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void r_usb_hstd_HciPortSuspend(uint16_t rootport)
{
    uint16_t    devaddr;

    devaddr = usb_hstd_EhciGetDeviceAddressOfRootpoot(rootport);
    if(USB_HCI_NODEVICE != devaddr)
    {
        usb_hstd_EhciPortSuspend(rootport);
    }
    else
    {
        devaddr = usb_hstd_OhciGetDeviceAddressOfRootpoot(rootport);
        if(USB_HCI_NODEVICE != devaddr)
        {
            usb_hstd_OhciPortSuspend(rootport);
        }
    }
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciPortSuspend
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciPortResume
 *
 *  Description:    Port Resume
 *
 *  Parameters:     uint16_t rootport ; rootport no
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void r_usb_hstd_HciPortResume(uint16_t rootport)
{
    uint16_t    devaddr;

    devaddr = usb_hstd_EhciGetDeviceAddressOfRootpoot( rootport );
    if(USB_HCI_NODEVICE != devaddr)
    {
        usb_hstd_EhciPortResume(rootport);
    }
    else
    {
        devaddr = usb_hstd_OhciGetDeviceAddressOfRootpoot( rootport );
        if(USB_HCI_NODEVICE != devaddr)
        {
            usb_hstd_OhciPortResume(rootport);
        }
    }
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciPortResume
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciGetPidStatus
 *
 *  Description:    Getting of PID status
 *
 *  Parameters:     uint16_t devaddr ; device address
 *
 *  Return value:   uint16_t pid status
 *
 **********************************************************************************************************************/
uint16_t r_usb_hstd_HciGetPidStatus(uint16_t devaddr, uint16_t epnum)
{
    USB_HCI_TR_REQ     *tr_req;
    uint32_t            i;

    tr_req = &usb_ghstd_HciTransferRequest[0];
    for(i = 0; i < USB_HCI_TRREQ_NUM; i++, tr_req++)
    {
        if(tr_req->bit.enable == TRUE)
        {
            if((tr_req->bit.devadrs == devaddr) && (tr_req->bit.epnum == epnum))
            {
                if(tr_req->devinfo->bit.hctype == USB_HCI_HCTYPE_EHCI)
                {
                    return(usb_hstd_EhciGetPidStatus(tr_req));
                }
                else if(tr_req->devinfo->bit.hctype == USB_HCI_HCTYPE_OHCI)
                {
                    return(usb_hstd_OhciGetPidStatus(tr_req));
                }
                break;
            }
        }
    }

    return(USB_PID_NAK);
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciGetPidStatus
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:      r_usb_hstd_HciSetHubInfo
 *
 *  Description:    HUB information setting when new device is attached.
 *
 *  Parameters:     uint32_t hubaddr    ; HUB device address
 *                  uint32_t hubportnum ; HUB port no
 *                  uint32_t devaddr    ; new device address
 *                  uint32_t devspeed   ; new device speed
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void r_usb_hstd_HciSetHubInfo(uint32_t hubaddr, uint32_t hubportnum, uint32_t devaddr, uint32_t devspeed)
{
    USB_HCI_DEVICE     *new_devinfo;
    USB_HCI_DEVICE     *hub_devinfo;

    new_devinfo = usb_hstd_HciAllocDevinfo();
    if(new_devinfo != NULL)
    {
        /* Getting of device information on connected HUB */
        hub_devinfo = r_usb_hstd_HciGetDeviceInformation(hubaddr);
        if(hub_devinfo != NULL)
        {
            new_devinfo->bit.devnum     = devaddr;
            new_devinfo->bit.devspeed   = devspeed;
            new_devinfo->bit.hctype     = hub_devinfo->bit.hctype;

            /* The split transaction is checked. */
            if(hub_devinfo->bit.sprit_flag == TRUE)
            {
                new_devinfo->bit.sprit_flag = TRUE;
                new_devinfo->bit.hubaddr    = hub_devinfo->bit.hubaddr;
                new_devinfo->bit.hubportnum = hub_devinfo->bit.hubportnum;
            }
            else
            {
                if((devspeed != USB_HCI_DEVSPEED_HS) && (hub_devinfo->bit.devspeed == USB_HCI_DEVSPEED_HS))
                {
                    /* The split transaction is set. */
                    new_devinfo->bit.sprit_flag = TRUE;
                }else
                {
                    new_devinfo->bit.sprit_flag = FALSE;
                }
                new_devinfo->bit.hubaddr    = hubaddr;
                new_devinfo->bit.hubportnum = hubportnum;
            }

            /* Device information on HCI is succeeded. */
            new_devinfo->hci_device = hub_devinfo->hci_device;
        }
    }
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciSetHubInfo
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       r_usb_hstd_HciSetDeviceAddressOfHubport
 *
 *  Description:    The device address of the HUB port is set.
 *
 *  Parameters:     uint16_t hubaddr ; HUB device address
 *                  uint16_t devaddr ; HUB down port device address
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void r_usb_hstd_HciSetDeviceAddressOfHubport(uint16_t hubaddr, uint16_t devaddr)
{
    USB_HCI_DEVICE  *hub_devinfo;
    USB_HCI_DEVICE  *devinfo;
    uint32_t        cnt;

    /* Getting of HUB device information */
    hub_devinfo = r_usb_hstd_HciGetDeviceInformation(hubaddr);

    /* Getting of HUB down-port device information */
    devinfo = r_usb_hstd_HciGetDeviceInformation(devaddr);

    if((hub_devinfo != NULL) && (devinfo != NULL))
    {
        for(cnt = 0; cnt < USB_HCI_HUBPORT_NUM; cnt++)
        {
            if(hub_devinfo->hubdevinfo.devnum[cnt] == 0)
            {
                hub_devinfo->hubdevinfo.devnum[cnt]     = (uint8_t)devaddr;
                hub_devinfo->hubdevinfo.devspeed[cnt]   = (uint8_t)devinfo->bit.devspeed;
                hci_TmpAddr = devaddr;
                break;
            }
        }
    }
    else
    {
        /* Error */
        USB_HCI_PRINTF2_R( "Error: unknown hubaddr( %d ) or devaddr( %d )\n", hubaddr, devaddr );
        }
    }

/*********************/
/* utility function  */
/*********************/
#ifdef USB_HOST_COMPLIANCE_MODE
void r_usb_hstd_HciElectricalTest( uint16_t rootport, uint8_t mode)
{
    switch(mode)
    {
    case 0:    /* Test SE0_NAK */
        USB_HOST->PORTSC1.BIT.PortTestControl = 3;
        while(1);   /* This loops infinitely until it's reset. */
        break;
    case 1:    /* Test J */
        USB_HOST->PORTSC1.BIT.PortTestControl = 1;
        while(1);   /* This loops infinitely until it's reset. */
        break;
    case 2:    /* Test K */
        USB_HOST->PORTSC1.BIT.PortTestControl = 2;
        while(1);   /* This loops infinitely until it's reset. */
        break;
    case 3:    /* Signal Quality */
        USB_HOST->PORTSC1.BIT.PortTestControl = 4;
        while(1);   /* This loops infinitely until it's reset. */
        break;
    case 4:    /* Suspend/Resume */
        r_usb_hstd_HciWaitTime(15000);            /* wait 15sec */
        USB_HOST->PORTSC1.BIT.Suspend = 1;           /* Suspend */
        r_usb_hstd_HciWaitTime(15000);            /* wait 15sec */
        USB_HOST->PORTSC1.BIT.ForcePortResume = 1;   /* Resume start */
        r_usb_hstd_HciWaitTime(20);               /* wait 20ms */
        USB_HOST->PORTSC1.BIT.ForcePortResume = 0;   /* Resume end */
        break;
    case 5:   /* Packet Parameters */
        usb_hstd_ElectricalTestMode(0x0108, rootport);
        break;
    case 6:   /* Chirp Timing */
        USB_HOST->PORTSC1.BIT.Suspend = 1;
        if(USB_HOST->PORTSC1.BIT.CurrentConnectStatus == 1)
        {
            USB_HOST->USBINTR.LONG = 0x00000000;  /* Disable interrupt */
            r_usb_hstd_HciPortReset(rootport);
            r_usb_hstd_HciWaitTime(15000);            /* wait 15sec */
        }

        if(USB_HOST->PORTSC1.BIT.CurrentConnectStatus == 1)
        {
            r_usb_hstd_HciPortReset(rootport);
        }
        USB_HOST->USBINTR.LONG = 0x00000007;  /* PortChange, USBError, USBInt */
        break;
    default:
        break;
    }
}
#endif /* USB_HOST_COMPLIANCE_MODE */

/* waittimer_function for usbhstd */
void r_usb_hstd_HciWaitTime( uint32_t ms )
{
    uint32_t prv = USB_HOST->HcFmNumber.LONG;

    USB_HCI_PRINTF1("Wait %d[ms]\n",ms);
    while( ms )
    {
        if( (USB_HOST->HcFmNumber.LONG - prv) != 0 )
        {
            ms--;
            prv = USB_HOST->HcFmNumber.LONG;
        }
    }
}
/***********************************************************************************************************************
 End of function r_usb_hstd_HciSetDeviceAddressOfHubport
 **********************************************************************************************************************/