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
 * FILE         :  r_usb_hDriver.c
 * Description  :  USB Host Control Driver
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_usb_basic_local.h"
#include "r_usb_hHci.h"
#include "platform.h"

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
USB_PIPE_t      usb_ghstd_pipe[USB_MAXPIPE+1u];                /* pipe information */

/***********************************************************************************************************************
 Static variables and functions
 **********************************************************************************************************************/
static uint16_t  usb_gcstd_DEVADD[USB_MAXDEVADDR];              /* DEVADD table */

/***********************************************************************************************************************
 *
 *  Description:    Get End point number from pipe number
 *
 *  Function:       uint16_t usb_cstd_GetEpnum(uint16_t pipe_id)
 *
 *  Parameters:     uint16_t pipe_id  : Pipe Number
 *
 *  Return value:   uint16_t endpoint number
 *
 **********************************************************************************************************************/
uint16_t usb_cstd_GetEpnum(uint16_t pipe_id)
{
    return usb_ghstd_pipe[pipe_id].epnum;
}
/***********************************************************************************************************************
 End of function usb_cstd_GetEpnum
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_cstd_GetMaxPacketSize
 *
 *  Description:    Fetch MaxPacketSize of the specified pipe.
 *
 *  Parameters:     uint16_t pipe_id  : Pipe number.
 *
 *  Return value:   uint16_t MaxPacketSize
 *
 **********************************************************************************************************************/
uint16_t usb_cstd_GetMaxPacketSize(uint16_t pipe_id)
{
    return usb_ghstd_pipe[pipe_id].mps;
}
/***********************************************************************************************************************
 End of function usb_cstd_GetMaxPacketSize
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_cstd_GetDevAddr
 *
 *  Description:    Get device address from pipe number
 *
 *  Parameters:     uint16_t pipe_id  : Pipe number.
 *
 *  Return value:   uint16_t DEVSEL-bit status
 *
 **********************************************************************************************************************/
uint16_t usb_cstd_GetDevAddr(uint16_t pipe_id)
{
    return usb_ghstd_pipe[pipe_id].devaddr;
}
/***********************************************************************************************************************
 End of function usb_cstd_GetDevAddr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_GetPipeDir
 *
 *  Description:    Get PIPE DIR
 *
 *  Parameters:     uint16_t pipe_id  : Pipe number.
 *
 *  Return value:   uint16_t pipe_id direction.
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_GetPipeDir(uint16_t pipe_id)
{
    return usb_ghstd_pipe[pipe_id].direction;
}
/***********************************************************************************************************************
 End of function usb_hstd_GetPipeDir
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_GetPipeType
 *
 *  Description:    Fetch and return PIPE TYPE.
 *
 *  Parameters:     uint16_t pipe_id  : Pipe number.
 *
 *  Return value:   uint16_t pipe_id type
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_GetPipeType(uint16_t pipe_id)
{
    return usb_ghstd_pipe[pipe_id].type;
}
/***********************************************************************************************************************
 End of function usb_hstd_GetPipeType
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_cstd_DummyFunction
 *
 *  Description:    dummy function
 *
 *  Parameters:     uint16_t data1    : Not used.
 *                  uint16_t data2    : Not used.
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void usb_cstd_DummyFunction(USB_UTR_t *utr)
{
}
/***********************************************************************************************************************
 End of function usb_cstd_DummyFunction
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_SetRootport
 *
 *  Description:    Set Port Number of the connected USB Device.
 *
 *  Parameters:     uint16_t devaddr          : device address
 *                  uint16_t port             : root port
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void usb_hstd_SetRootport(uint16_t devaddr, uint16_t rootport)
{
    usb_gcstd_DEVADD[devaddr] = rootport;
}
/***********************************************************************************************************************
 End of function usb_hstd_SetRootport
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_GetRootport
 *
 *  Description:    Get USB port no. set in the USB register based on the specified USB Device address.
 *
 *  Parameters:     uint16_t devaddr          : device address
 *
 *  Return value:   uint16_t                  : root port number
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_GetRootport(uint16_t devaddr)
{
    return usb_gcstd_DEVADD[devaddr];
}
/***********************************************************************************************************************
 End of function usb_hstd_GetRootport
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_MgrSndMbx
 *
 *  Description:    Send the message to MGR(Manager) task
 *
 *  Parameters:     uint16_t msginfo  : Message info.
 *                  uint16_t dat      : Port no.
 *                  uint16_t res      : Result
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void usb_hstd_MgrSndMbx(uint16_t msginfo, uint16_t dat, uint16_t res)
{
    USB_UTR_t       *p_blf;
    USB_ER_t        err, err2;

    /* Get mem pool blk */
    err = USB_PGET_BLK(USB_MGR_MPL, &p_blf);
    if (err == USB_OK)
    {
        p_blf->msginfo = msginfo;
        p_blf->keyword = dat;
        p_blf->result  = res;

        /* Send message */
        err = USB_SND_MSG(USB_MGR_MBX, (USB_MSG_t *)p_blf);
        if (err != USB_OK)
        {
            USB_PRINTF1("### hMgrSndMbx snd_msg error (%ld)\n", err);
            err2 = USB_REL_BLK(USB_MGR_MPL, p_blf);
            if (err2 != USB_OK)
            {
                USB_PRINTF1("### hMgrSndMbx rel_blk error (%ld)\n", err2);
            }
        }
    }
    else
    {
        USB_PRINTF1("### hMgrSndMbx pget_blk error (%ld)\n", err);
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_MgrSndMbx
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       void usb_hstd_TransferEnd
 *
 *  Description:    End of data transfer (IN/OUT)
 *
 *  Parameters:     uint16_t pipe_id         ; pipe Number
 *
 *  Return value:   USB_ER_t  error code  : USB_OK/USB_ERROR.
 *
 **********************************************************************************************************************/
USB_ER_t usb_hstd_TransferEnd(uint16_t pipe_id)
{
    uint16_t        devaddr;

    if ( pipe_id > USB_MAXPIPE ) {
        USB_PRINTF1("### R_usb_hstd_TransferEnd PipeErr %d\n", pipe_id);
        return USB_ERROR;
    }

    devaddr = usb_cstd_GetDevAddr(pipe_id);
    if( (devaddr == USB_DEVICE_0) && (pipe_id != USB_PIPE0) ) {
        USB_PRINTF1("### R_usb_hstd_TransferEnd AddrErr %d\n", pipe_id);
        return USB_ERROR;
    }

    if( pipe_id == USB_PIPE0 )
    {
    }
    else
    {
        r_usb_hstd_HciCancelTransferRequest(
            usb_cstd_GetDevAddr(pipe_id),
            usb_cstd_GetEpnum(pipe_id),
            usb_hstd_GetPipeType(pipe_id),
            usb_hstd_GetPipeDir(pipe_id)
        );
    }

    return USB_OK;
}
/***********************************************************************************************************************
 End of function usb_hstd_ForcedTermination
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_TransferStart
 *
 *  Description:    Request HCD to transfer data. HCD will transfer the data
 *                  based on the transfer information stored in utrmsg.
 *
 *  Parameters:     USB_UTR_t *utr  : USB system internal structure.
 *
 *  Return value:   USB_ER_t  error code  : USB_OK/USB_ERROR.
 *
 **********************************************************************************************************************/
USB_ER_t usb_hstd_TransferStart(USB_UTR_t *utr)
{
    USB_ER_t        err;
    uint16_t        pipe_id, devaddr;

    pipe_id = utr->keyword;

    if( pipe_id == USB_PIPE0 ) {
        devaddr = (uint16_t)(utr->setup->devaddr);
    } else {
        devaddr = usb_cstd_GetDevAddr(pipe_id);
    }
    if( (devaddr == USB_DEVICE_0) && (pipe_id != USB_PIPE0) ) {
        USB_PRINTF1("### R_usb_hstd_TransferStart not configured %x\n", devaddr);
        return USB_ERROR;
    }

    if( pipe_id == USB_PIPE0 )
    {
        err = r_usb_hstd_HciMakeTransferRequest(
                utr,                                     /* utr */
                utr->setup,                              /* setup */
                utr->setup->devaddr,                     /* devaddr */
                0,                                       /* epnum */
                USB_EP_CNTRL,                            /* eptype */
                (utr->setup->type & USB_DEV_TO_HOST),    /* epdir */
                utr->tranlen,                            /* tranlen */
                (uint32_t)utr->tranadr,                  /* tranadr */
                0                                        /* mps */
        );
    }
    else
    {
        err = r_usb_hstd_HciMakeTransferRequest(
                utr,                                     /* utr */
                (void*)USB_NULL,                         /* setup */
                usb_cstd_GetDevAddr(pipe_id),            /* devaddr */
                usb_cstd_GetEpnum(pipe_id),              /* epnum */
                usb_hstd_GetPipeType(pipe_id),           /* eptype */
                usb_hstd_GetPipeDir(pipe_id),            /* epdir */
                utr->tranlen,                            /* tranlen */
                (uint32_t)utr->tranadr,                  /* tranadr */
                usb_cstd_GetMaxPacketSize(pipe_id)       /* mps */
        );
    }

    return err;
}
/***********************************************************************************************************************
 End of function usb_hstd_TransferStart
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       void usb_hstd_AttachCb
 *
 *  Description:    Attach / Detach Callback Function
 *
 *  Parameters:     uint16_t rootport         : rootport number
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_AorDetachCb(uint16_t rootport)
{
    uint16_t ConnectInf;

    /* Decide USB Line state (ATTACH) */
    if ( r_usb_hstd_HciGetDeviceAddressOfRootpoot( rootport ) != USB_HCI_NODEVICE )
    {
        ConnectInf = USB_ATTACH;
    }
    /* Decide USB Line state (DETACH) */
    else
    {
        ConnectInf = USB_DETACH;
        usb_hstd_SetRootport(USB_DEVICEADDR, 0x0000);
        USB_PRINTF0("*** Device address 1 clear.\n");
    }

    usb_hstd_MgrSndMbx((uint16_t)USB_MSG_MGR_AORDETACH, rootport, ConnectInf);
}
/***********************************************************************************************************************
 End of function usb_hstd_AorDetachCb
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       void usb_hstd_PortResetCb
 *
 *  Description:    Port Reset Callback Function
 *
 *  Parameters:     uint16_t rootport     : rootport number
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_PortResetCb(uint16_t rootport)
{
    uint16_t    deviceaddr, ConnInf;
    uint32_t    speed;

    /* support speed check */
    deviceaddr = r_usb_hstd_HciGetDeviceAddressOfRootpoot( rootport );
    if ( USB_HCI_NODEVICE == deviceaddr ) {
        ConnInf = USB_NOCONNECT;
        return;
    }

    speed = r_usb_hstd_HciGetDeviceSpeed( deviceaddr );

    switch( speed ) {
        case USB_HCI_DEVSPEED_HS:   ConnInf = USB_HSCONNECT;    break;
        case USB_HCI_DEVSPEED_FS:   ConnInf = USB_FSCONNECT;    break;
        case USB_HCI_DEVSPEED_LS:   ConnInf = USB_LSCONNECT;    break;
        default:                    ConnInf = USB_NOCONNECT;    break;
    }

    usb_hstd_MgrSndMbx((uint16_t)USB_MSG_MGR_STATUSRESULT, rootport, ConnInf);
}
/***********************************************************************************************************************
 End of function usb_hstd_PortResetCb
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       void usb_hstd_OverCurrentCb
 *
 *  Description:    Over Current Callback Function
 *
 *  Parameters:     uint16_t rootport     : rootport number
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_OverCurrentCb(uint16_t rootport)
{
    usb_hstd_MgrSndMbx((uint16_t)USB_MSG_MGR_OVERCURRENT, rootport, 0u);
}
/***********************************************************************************************************************
 End of function usb_hstd_OverCurrentCb
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       void usb_hstd_TransferEndCb
 *
 *  Description:    Transfer End Callback Function
 *
 *  Parameters:     void     *utr_p : UTR Pointer
 *                  uint16_t status : Transfer Status
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_TransferEndCb(void* utr_p, uint32_t actual_size, uint16_t status)
{
    USB_UTR_t   *utr;

    utr = (USB_UTR_t *)utr_p;

    if( status == USB_DATA_SHT )
    {
        utr->tranlen -= actual_size;
    }

    /* Status setting */
    utr->result = status;

    /* Callback */
    utr->complete(utr);
}
/***********************************************************************************************************************
 End of function usb_hstd_TransferEndCb
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_IntEnable
 *
 *  Description:    USB host interrupt enable
 *
 *  Parameters:     None
 *
 *  Return value:   None
 *
 **********************************************************************************************************************/
void usb_hstd_IntEnable(void)
{
    (void)R_BSP_InterruptControl(RZN1_IRQ_USBH_BIND, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);
}
/***********************************************************************************************************************
 End of function usb_hstd_IntEnable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_IntDisable
 *
 *  Description:    USB host interrupt disable
 *
 *  Parameters:     None
 *
 *  Return value:   None
 *
 **********************************************************************************************************************/
void usb_hstd_IntDisable(void)
{
    (void)R_BSP_InterruptControl(RZN1_IRQ_USBH_BIND, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
}
/***********************************************************************************************************************
 End of function usb_hstd_IntDisable
 **********************************************************************************************************************/