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
 * FILE         :  r_usbf_controlrw.c
 * Description  :  USB Peripheral control transfer API code
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_usbf_basic_rzn1_if.h"
#include "r_usb_common.h"
#include "r_usb_cdefusbip.h"
#include "r_usbf_hal.h"
#include "r_usbf_driver.h"
#include "r_usb_rzn1_reg_defs.h"
#include "timer.h"

/***********************************************************************************************************************
 Renesas Abstracted Peripheral Control RW API functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function Name   : usb_pstd_ControlRead
 Description     : Called by R_usb_pstd_ControlRead, see it for description.
 Arguments       : uint32_t bsize    : Read size in bytes.
 : uint8_t *table    : Start address of read data buffer.
 Return value    : uint16_t          : USB_WRITESHRT/USB_WRITE_END/USB_WRITING/
 :                   : USB_FIFOERROR.
 **********************************************************************************************************************/
uint16_t usb_pstd_ControlRead(uint32_t bsize, uint8_t *table)
{
    uint16_t end_flag;

    usb_gcstd_DataCnt[USB_PIPE0] = bsize;
    usb_gcstd_DataPtr[USB_PIPE0] = table;

    /* Peripheral Control sequence */
    end_flag = usb_cstd_write_data( USB_PIPE0, USB_CUSE);
    if (USB_ERROR == end_flag)
    {
        usb_cstd_ForcedTermination( USB_PIPE0, (uint16_t)USB_DATA_ERR);
    }
    /* End or error or continue */
    return (end_flag);
}
/***********************************************************************************************************************
 End of function usb_pstd_ControlRead
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function Name   : usb_pstd_ControlWrite
 Description     : Called by R_usb_pstd_ControlWrite, see it for description.
 Arguments       : uint32_t bsize    : Write size in bytes.
 : uint8_t *table    : Start address of write data buffer.
 Return value    : none
 **********************************************************************************************************************/
void usb_pstd_ControlWrite(uint32_t bsize, uint8_t *table)
{

    usb_gcstd_DataCnt[USB_PIPE0] = bsize;
    usb_gcstd_DataPtr[USB_PIPE0] = table;

    /* Buffer clear */

    /* Interrupt enable */

    /* Enable ready interrupt */

}
/***********************************************************************************************************************
 End of function usb_pstd_ControlWrite
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function Name   : usb_pstd_ControlEnd
 Description     : End control transfer
 Arguments       : USB_UTR_t *ptr    : USB system internal structure.
 : uint16_t status   : Transfer end status
 Return value    : none
 **********************************************************************************************************************/
void usb_pstd_ControlEnd(uint16_t status)
{
    uint32_t i;

    if ((USB_DATA_ERR == status) || (USB_DATA_OVR == status))
    {
        /* Request error */
        usb_pstd_SetStallPipe0();
    } else if (USB_DATA_STOP == status)
    {
        /* Pipe stop */
        usb_cstd_SetONakPipe0();
    } else
    {
        /* End Control Transfer stage */
        /* wait with 10 msec timeout for transmission buffer empty */
        ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_BCLR =
                1; /* Buffer clear */
        for (i = 200; i > 0; i--)
        {
            if (((volatile EPC_EP0_STATUS_Type *) USBFUNC_USB_EPC_EP0_STATUS_ADDRESS)->EP0_STATUS.BIT.EP0_IN_EMPTY)
            {
                ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_DEND =
                        1; /* send NULL data */
                break;
            }
            systimer_delay(50); /* Delay 50 usecs */
        }
        if (0 == i)
        {
            /* timeout */
            usb_pstd_SetStallPipe0();
        }
    }

    usbf_eps[USB_EP0].state = USB_CS_IDST;
}
/***********************************************************************************************************************
 End of function usb_pstd_ControlEnd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
