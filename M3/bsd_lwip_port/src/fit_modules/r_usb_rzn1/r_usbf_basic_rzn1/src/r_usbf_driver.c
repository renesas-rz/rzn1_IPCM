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
 * $Revision: 1298 $
 * $Date: 2019-02-25 10:17:29 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :   RZ/N1 bare metal Drivers
 * FILE         :   r_usbf_driver.c
 * Description  :   USB function IP interface code
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Doxygen Design Documentation block:
 **********************************************************************************************************************/
/*!
 * @page PageUSBfCore USB function IP interface functions
 * @tableofcontents
 * @section usbf_basic USB function HAL layer - IP interface functions
 * @ref USBF_DRIVER
 *
 */
/***********************************************************************************************************************
 * End of Doxygen Design block
 **********************************************************************************************************************/
/*
 ********************************************************************************
 * Doxygen Summary block
 **********************************************************************************************************************/
/*!
 * @ingroup USBF_DRIVER RZN1 USB function HAL layer IP interface functions
 * @{
 * @file
 * @brief USBf Basic Driver IP interface functions
 * @details IP interface functions
 * @} */
/***********************************************************************************************************************
 * End of Doxygen Summary block
 **********************************************************************************************************************/


/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include "log_serial_io.h"
#include "r_usbf_basic_rzn1_if.h"
#include "r_usb_common.h"
#include "r_usb_cdefusbip.h"
#include "r_usbf_core.h"
#include "r_usbf_hal.h"
#include "r_usbf_driver.h"
#include "r_usb_rzn1_reg_defs.h"

#define USB_CURPIPE             (0x000Fu)   /* b2-0: PIPE select */

/***********************************************************************************************************************
 Static variables and functions
 **********************************************************************************************************************/
static void usb_pstd_process_ep0_interrupt(uint32_t ep0_status);
static void usb_pstd_process_epm_interrupt(uint16_t ep_num, uint32_t ep_status);
static void ep0_clear_inak(void);
static void ep0_clear_onak(void);
static void usb_pstd_SaveRequest(void);
static void usb_cstd_pipe_init(uint16_t pipe, uint16_t *tbl, uint16_t ofs);

/***********************************************************************************************************************
 Global variables and functions
 **********************************************************************************************************************/
extern uint8_t dbg_count;

uint16_t usb_gpstd_StallPipe[USB_MAX_PIPE_NO + 1u]; /* Stall Pipe info */
USB_UTR_CB_t usb_gpstd_StallCB; /* Stall Callback function */
uint16_t usb_gpstd_ConfigNum = 0; /* Current configuration number */
uint16_t usb_gpstd_AltNum[USB_ALT_NO]; /* Alternate number */
uint16_t usb_gpstd_RemoteWakeup = USB_FALSE; /* Remote wakeup enable flag */

uint16_t usb_gpstd_TestModeSelect; /* Test mode selectors */
uint16_t usb_gpstd_TestModeFlag = USB_FALSE; /* Test mode flag */

uint16_t usb_gpstd_EpTblIndex[2][USBF_MAX_EPS]; /* Index of endpoint information table */
uint16_t usb_gpstd_ReqType; /* Request type */
uint16_t usb_gpstd_ReqTypeType; /* Request type TYPE */
uint16_t usb_gpstd_ReqTypeRecip; /* Request type RECIPIENT */
uint16_t usb_gpstd_ReqRequest; /* Request */
uint16_t usb_gpstd_ReqValue; /* Value */
uint16_t usb_gpstd_ReqIndex; /* Index */
uint16_t usb_gpstd_ReqLength; /* Length */

bool check_vbus_level;
#if USB_CPU_LPW_PP  == USB_LPWR_USE_PP
uint16_t usb_gcstd_SuspendMode = USB_NORMAL_MODE;
#endif /* USB_CPU_LPW_PP  == USB_LPWR_USE_PP */

/* Driver registration */
USB_PCDREG_t usb_gpstd_Driver;
USB_REQUEST_t usb_gpstd_ReqReg; /* Device Request - Request structure */

extern void sample_app_printf(const char *message);

/***********************************************************************************************************************
 Renesas Abstracted Peripheral Driver functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_PcdTask
 **********************************************************************************************************************/
/*!
 * @brief    The Peripheral Control Driver(PCD) task
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_PcdTask(void)
{
    uint16_t connect_info;

    /* Check for VBUS level change */
    if (true == check_vbus_level)
    {
        connect_info = usb_pstd_ChkVbsts();
        switch (connect_info)
        {
        case USB_ATTACH:
            /* Attach host controller */
            usb_pstd_AttachProcess();
            break;
        case USB_DETACH:
            /* Detach host controller */
            usb_pstd_DetachProcess();
            break;
        default:
            /* no connection change */
            break;
        }
        check_vbus_level = false; /* reset VBUS check flag */
        /* Re-enable VBUS interrupt */
        enable_usbf_ahb_epc_isr();
    }

    if (usb_gpstd_UsbEPCInt.Wp != usb_gpstd_UsbEPCInt.Rp)
    {
        /* Pop Interrupt info */
        usb_pstd_Interrupt(&(usb_gpstd_UsbEPCInt.Buf[usb_gpstd_UsbEPCInt.Rp]));
        /* Update read pointer */
        usb_gpstd_UsbEPCInt.Rp =
                ((usb_gpstd_UsbEPCInt.Rp + 1) % USB_INT_BUFSIZE);
    }

#if USB_DMA_PP == USB_DMA_USE_PP
    if( usb_gpstd_UsbInt.WpD != usb_gpstd_UsbInt.RpD )
    {
        /* Pop */
        usb_cstd_DfifoInt();
        /* Read countup */
        usb_gpstd_UsbInt.RpD++;
    }
#endif /* USB_DMA_PP */
}
/***********************************************************************************************************************
 End of function usb_pstd_PcdTask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetSubmitutr
 **********************************************************************************************************************/
/*!
 * @brief    USB Peripheral Submit utr
 * @details
 * @param    USB_UTR_t *utrmsg
 * @retval   USB_ER_t
 **********************************************************************************************************************/
USB_ER_t usb_pstd_SetSubmitutr(USB_UTR_t *utrmsg)
{
    uint16_t pipenum;

    pipenum = utrmsg->keyword;
    usb_gcstd_Pipe[pipenum] = utrmsg;

    /* Check state ( Configured ) */
    if (usb_pstd_ChkConfigured() == USB_TRUE)
    {
        /* Data transfer */
        if (usb_cstd_GetPipeDir(pipenum) == USB_DIR_P_OUT)
        { /* Out transfer */
            usb_cstd_ReceiveStart(pipenum);
        } else
        {
            /* In transfer */
            usb_cstd_SendStart(pipenum);
        }
    } else
    {
        /* Transfer stop */
        usb_cstd_ForcedTermination(pipenum, (uint16_t)USB_DATA_ERR);
    }
    return USB_OK ;
}
/***********************************************************************************************************************
 End of function usb_pstd_SetSubmitutr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_Interrupt
 **********************************************************************************************************************/
/*!
 * @brief    Process the USB Peripheral interrupt events
 * @details  Handles all interrupts for USBf EPC module
 * @param    epc_ints_status - EPC interrrupts which have occurred
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_Interrupt(EPC_INT_STATUS *epc_ints_status)
{
    uint32_t ints_to_process;
    uint16_t ep_num;

    /* Mask generic ints to process & set EP ints if set in epn_status */
    ints_to_process = epc_ints_status->usb_status;
    for (ep_num = USB_EP0; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (epc_ints_status->epn_status[ep_num])
        {
            ints_to_process |= (EPC_USB_INT_STA_EP0_INT_BIT << ep_num);
        }
    }

    if (ints_to_process & EPC_USB_INT_STA_RSUM_INT_BIT)
    {
        usb_pstd_ResumeProcess();
    }
    if (ints_to_process & EPC_USB_INT_STA_SPND_INT_BIT)
    {
        /* Suspend */
        usb_pstd_SuspendProcess();
    }
    if (ints_to_process & EPC_USB_INT_STA_USB_RST_INT_BIT)
    {
        /* Bus Reset */
        usb_pstd_BusReset();

        /*if (bus_reset need to flush the ep request queue (this should be handled by usb_pstd_BusReset()   */
    }
    if (ints_to_process & EPC_USB_INT_STA_SPEED_MODE_RST_INT_BIT)
    {
        /* Speed Mode changed from FS to HS */

        /* No need to re-evaluate max pkt sizes and base RAM addresses for EPms as initially set for HS */
        g_bHighSpeed = true;
    }

    if (ints_to_process & EPC_USB_INT_STA_USB_RST_INT_BIT)
    {
        usb_reset_ep(USB_EP0);
    }

    /* Check EP0 int status */
    if (ints_to_process & (EPC_USB_INT_STA_EP0_INT_BIT))
    {
        usb_pstd_process_ep0_interrupt(epc_ints_status->epn_status[USB_EP0]);
    }

    /* Read int status register for all EPs */
    for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].enabled)
        {
            if (ints_to_process & EPC_USB_INT_STA_USB_RST_INT_BIT)
            {
                usb_reset_ep(ep_num);
            }
            if (ints_to_process & (EPC_USB_INT_STA_EP0_INT_BIT << ep_num))
            {
                usb_pstd_process_epm_interrupt(ep_num,
                        epc_ints_status->epn_status[ep_num]);
            }
        }
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_Interrupt
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_process_ep0_interrupt
 **********************************************************************************************************************/
/*!
 * @brief    Process the interrupt events for EP0
 * @details
 * @param    ep_status - status of EP0 interrupts
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_process_ep0_interrupt(uint32_t ep_status)
{
    if (ep_status & EPC_EP0_STATUS_SETUP_INT_BIT)
    {
        /* Control Transfer - Valid Setup data has been received */
        if (USB_CS_IDST == usbf_eps[USB_EP0].state)
        {
            /* Save request */
            usb_pstd_SaveRequest();

            if ((usb_gpstd_ReqLength > 0)
                    && (USB_EP_IN == usbf_eps[USB_EP0].dir))
            {
                /* Control Read */
                (void) epn_flush_buffer(USB_EP0,
                        EPC_EP0_STATUS_EP0_IN_EMPTY_BIT);
                ep0_clear_inak(); /* Clear NAK response control bit for IN token to endpoint0 */
                usbf_eps[USB_EP0].state = USB_CS_RDDS;
            } else if ((usb_gpstd_ReqLength > 0)
                    && (USB_EP_OUT == usbf_eps[USB_EP0].dir))
            {
                /* Control Write Data Stage (don't expect to see this stage!) */
                ep0_clear_onak(); /* Clear NAK response control bit for OUT/PING token to endpoint0 */
                usbf_eps[USB_EP0].state = USB_CS_WRDS;
            } else
            {
                /* No Data Stage */
                usbf_eps[USB_EP0].state = USB_CS_WRND;
            }

            if ( USB_STANDARD == usb_gpstd_ReqTypeType)
            {
                switch (usbf_eps[USB_EP0].state)
                {
                /* Idle or setup stage */
                case USB_CS_IDST:
                    usb_pstd_StandReq0();
                    break;
                    /* Control read data stage */
                case USB_CS_RDDS:
                    usb_pstd_StandReq1();
                    break;
                    /* Control write data stage */
                case USB_CS_WRDS:
                    usb_pstd_StandReq2();
                    break;
                    /* no data - wait for status stage to process?*/
                case USB_CS_WRND:
                    usb_pstd_StandReq0();
                    break;
                    /* Illegal */
                default:
                    usb_pstd_ControlEnd((uint16_t)USB_DATA_ERR);
                    break;
                }
            } else
            {
                if ((USB_CS_RDDS == usbf_eps[USB_EP0].state)
                        || (USB_CS_WRDS == usbf_eps[USB_EP0].state))
                {
                    /* Vendor Specific */
                    usb_gpstd_ReqReg.ReqType = usb_gpstd_ReqType;
                    usb_gpstd_ReqReg.ReqTypeType = usb_gpstd_ReqTypeType;
                    usb_gpstd_ReqReg.ReqTypeRecip = usb_gpstd_ReqTypeRecip;
                    usb_gpstd_ReqReg.ReqRequest = usb_gpstd_ReqRequest;
                    usb_gpstd_ReqReg.ReqValue = usb_gpstd_ReqValue;
                    usb_gpstd_ReqReg.ReqIndex = usb_gpstd_ReqIndex;
                    usb_gpstd_ReqReg.ReqLength = usb_gpstd_ReqLength;
                    /* Callback */
                    (*usb_gpstd_Driver.ctrltrans)(
                            (USB_REQUEST_t *) &usb_gpstd_ReqReg,
                            usbf_eps[USB_EP0].state);
                }
            }
        } else
        {
            usb_pstd_ControlEnd((uint16_t)USB_DATA_ERR);
        }
    }

    if (ep_status & EPC_EP0_STATUS_EP0_OUT_INT_BIT)
    {
        /* Out Int - valid data has been stored to EP0 read register (reception buffer) */
        if (USB_CS_WRDS == usbf_eps[USB_EP0].state)
        {
            /* Read and store the data & check to see if all received */

            /* Peripheral Control sequence */

            switch (usb_cstd_read_data( USB_PIPE0, USB_CUSE))
            {
            case USB_READEND:
                /* Continue */
            case USB_READSHRT:
                /* End of data read */
                break;
                /* Reading in progress */
            case USB_READING:
                /* PID = BUF */
                break;
            case USB_READOVER:
                /*Clear EP0 buffer (write & read regs on CPU side & USB side) */
                ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_BCLR =
                        1;
                usb_pstd_ControlEnd((uint16_t)USB_DATA_OVR);
                break;
            case USB_ERROR :
                /* access error - Control transfer stop */
                usb_pstd_ControlEnd((uint16_t)USB_DATA_ERR);
                break;
            default:
                usb_pstd_ControlEnd((uint16_t)USB_DATA_ERR);
                break;
            }
        }
    }

    if (ep_status & EPC_EP0_STATUS_EP0_OUT_OR_INT_BIT)
    {
        /* OUT_OR_INT - overrun occurred while EP0 receiving data */
        if (USB_CS_WRDS == usbf_eps[USB_EP0].state)
        {
            /* receive data overrun Pipe 0 */

            /*Clear EP0 buffer (write & read regs on CPU side & USB side) */
            ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_BCLR =
                    1;

            /* Control transfer stop(end) */
            usb_pstd_ControlEnd((uint16_t)USB_DATA_OVR);
        }
    }

    if (ep_status & EPC_EP0_STATUS_STG_START_INT_BIT)
    {
        /* Control Transfer - Status stage starts */
        if ((usb_gpstd_ReqLength > 0) && (USB_EP_IN == usbf_eps[USB_EP0].dir))
        {
            /* Control Read */
            ep0_clear_onak(); /* Clear NAK response control bit for OUT/PING token to endpoint0 */
        } else if ((usb_gpstd_ReqLength > 0)
                && (USB_EP_OUT == usbf_eps[USB_EP0].dir))
        {
            /* Control Write */
            (void) epn_flush_buffer(USB_EP0, EPC_EP0_STATUS_EP0_OUT_EMPTY_BIT);
            ep0_clear_inak(); /* Clear NAK response control bit for IN token to endpoint0 */
        } else
        {
            /* No Data Stage */
            (void) epn_flush_buffer(USB_EP0, EPC_EP0_STATUS_EP0_IN_EMPTY_BIT);
            ep0_clear_inak(); /* Clear NAK response control bit for IN token to endpoint0 */
        }

        if (USB_CS_IDST == usbf_eps[USB_EP0].state)
        {
            /* Setup transfer request not yet saved */
            usb_pstd_SaveRequest();
        }
        if ((USB_CS_IDST == usbf_eps[USB_EP0].state)
                || (USB_CS_WRDS == usbf_eps[USB_EP0].state))
        {
            usbf_eps[USB_EP0].state = USB_CS_WRSS; /* Control Write status Stage */
        } else if (USB_CS_RDDS == usbf_eps[USB_EP0].state)
        {
            usbf_eps[USB_EP0].state = USB_CS_RDSS; /* Control Read Status Stage */
        } else if (USB_CS_WRND != usbf_eps[USB_EP0].state)
        {
            usbf_eps[USB_EP0].state = USB_CS_SQER;
        }
        if ( USB_STANDARD == usb_gpstd_ReqTypeType)
        {
            switch (usbf_eps[USB_EP0].state)
            {
            /* Status stage of a control write where there is no data stage */
            case USB_CS_WRND:
                usb_pstd_StandReq3();
                break;
                /* Control read status stage */
            case USB_CS_RDSS:
                usb_pstd_StandReq4();
                break;
                /* Control write status stage */
            case USB_CS_WRSS:
                usb_pstd_StandReq5();
                break;
                /* Control sequence error */
            case USB_CS_SQER:
                usb_pstd_ControlEnd((uint16_t)USB_DATA_ERR);
                break;
                /* Illegal */
            default:
                usb_pstd_ControlEnd((uint16_t)USB_DATA_ERR);
                break;
            }
        } else
        {
            /* Vendor Specific - not yet processed*/
            usb_gpstd_ReqReg.ReqType = usb_gpstd_ReqType;
            usb_gpstd_ReqReg.ReqTypeType = usb_gpstd_ReqTypeType;
            usb_gpstd_ReqReg.ReqTypeRecip = usb_gpstd_ReqTypeRecip;
            usb_gpstd_ReqReg.ReqRequest = usb_gpstd_ReqRequest;
            usb_gpstd_ReqReg.ReqValue = usb_gpstd_ReqValue;
            usb_gpstd_ReqReg.ReqIndex = usb_gpstd_ReqIndex;
            usb_gpstd_ReqReg.ReqLength = usb_gpstd_ReqLength;
            /* Callback */
            (*usb_gpstd_Driver.ctrltrans)((USB_REQUEST_t *) &usb_gpstd_ReqReg,
                    usbf_eps[USB_EP0].state);

            /* Control transfer stop(end) */
            usb_pstd_ControlEnd((uint16_t)USB_CTRL_END);
        }
    }
    /* safer to set EP0 status at end of usb_pstd_ControlEnd() */
    if (ep_status & EPC_EP0_STATUS_STG_END_INT_BIT)
    {
        usbf_eps[USB_EP0].state = USB_CS_IDST; /* Reset control transfer state */
    }

    if (ep_status & EPC_EP0_STATUS_EP0_STALL_INT_BIT)
    {
        /* Stalled */
        usb_cstd_ForcedTermination(USB_PIPE0, (uint16_t)USB_DATA_STALL);
        usb_gpstd_StallPipe[USB_PIPE0] = USB_TRUE;
        usbf_eps[USB_EP0].state = USB_CS_IDST; /* Reset control transfer state */
    }

}
/***********************************************************************************************************************
 End of function usb_pstd_process_ep0_interrupt
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_process_epm_interrupt
 **********************************************************************************************************************/
/*!
 * @brief    Process the interrupt events for an EP
 * @details
 * @param    ep_num - EP for which interrupts have occurred
 * @param    ep_status - status of interrupts for the EP
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_process_epm_interrupt(uint16_t ep_num, uint32_t ep_status)
{
    /*volatile    EPC_EPm_CONTROL_Type *epm_control_reg_addr;*/
    uint16_t pipe;

    pipe = usbf_eps[ep_num].pipe;

    if ((ep_status & EPC_EPm_STATUS_OUT_INT_BIT)
            || (ep_status & EPC_EPm_STATUS_OUT_END_INT_BIT)) /* may need to separate for DMA */
    {
        /* Out Int - valid data has been stored to EPm read register (reception buffer) */

        if (USB_NULL != usb_gcstd_Pipe[pipe]) /* is pipe in use ? */
        {
            /* Read and store the data & check to see if all received */

            switch (usb_cstd_read_data(pipe, USB_CUSE))
            {
            case USB_READEND:
                /* End of data read */
                usb_cstd_DataEnd(pipe, (uint16_t)USB_DATA_OK);
                break;
            case USB_READSHRT:
                /* End of data read */
                usb_cstd_DataEnd(pipe, (uint16_t)USB_DATA_SHT);
                break;
                /* Reading in progress */
            case USB_READING:
                break;

            case USB_READOVER:
                usb_cstd_ForcedTermination(pipe, (uint16_t)USB_DATA_OVR);
                break;
            case USB_ERROR :
                usb_cstd_ForcedTermination(pipe, (uint16_t)USB_DATA_ERR);
                break;
            default:
                usb_cstd_ForcedTermination(pipe, (uint16_t)USB_DATA_ERR);
                break;
            }
        }
    }

    if (ep_status & EPC_EPm_STATUS_IN_INT_BIT)
    {
        /* In Int */

        /* Tx finished. */
        if (USB_DS_TX == usbf_eps[ep_num].state)
        {
            usb_cstd_DataEnd(pipe, (uint16_t)USB_DATA_OK);
        }

        /*sample_app_printf("N");      */
    }

}
/***********************************************************************************************************************
 End of function usb_pstd_process_epm_interrupt
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   ep0_clear_inak
 **********************************************************************************************************************/
/*!
 * @brief    Clear NAK response control bit for IN token to EP0
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void ep0_clear_inak(void)
{
    uint32_t control_reg;

    control_reg =
            ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.LONG;
    control_reg |= EPC_EP0_CONTROL_EP0_INAK_EN_BIT;
    control_reg &= (~EPC_EP0_CONTROL_EP0_INAK_BIT);
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.LONG =
            control_reg;
}
/***********************************************************************************************************************
 End of function ep0_clear_inak
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   ep0_clear_onak
 **********************************************************************************************************************/
/*!
 * @brief    NAK response control bit for OUT/PING token to endpoint0
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void ep0_clear_onak(void)
{
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_ONAK =
            0;
}
/***********************************************************************************************************************
 End of function ep0_clear_onak
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_ClearAlt
 **********************************************************************************************************************/
/*!
 * @brief    Zero-clear the alternate table (buffer).
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_ClearAlt(void)
{
    uint16_t i;

    for (i = 0; i < USB_ALT_NO; ++i)
    {
        /* Alternate table clear */
        usb_gpstd_AltNum[i] = 0;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_ClearAlt
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_ClearMem
 **********************************************************************************************************************/
/*!
 * @brief    Initialize global variables defined for peripheral mode
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_ClearMem(void)
{
    /* Configuration number */
    usb_gpstd_ConfigNum = 0;
    /* Remote wakeup enable flag */
    usb_gpstd_RemoteWakeup = USB_FALSE;
    /* Alternate setting clear */
    usb_pstd_ClearAlt();
}
/***********************************************************************************************************************
 End of function usb_pstd_ClearMem
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetConfigNum
 **********************************************************************************************************************/
/*!
 * @brief    Set specified configuration number
 * @details
 * @param    uint16_t value  - Configuration number
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_SetConfigNum(uint16_t value)
{
    /* Set configuration number */
    usb_gpstd_ConfigNum = value;

    if (0 == value)
    {
        /* Disable all EPs except EP0 */
        ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.BIT.CONF =
                0;
    } else
    {
        /* Enable all EPs */
        ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.BIT.CONF =
                1;
    }
    /* Alternate setting clear */
    usb_pstd_ClearAlt();
}
/***********************************************************************************************************************
 End of function usb_pstd_SetConfigNum
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_ClearEpTblIndex
 **********************************************************************************************************************/
/*!
 * @brief    Clear Endpoint Index Table (buffer)
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_ClearEpTblIndex(void)
{
    uint16_t i;

    for (i = USB_EP0; i <= USB_MAX_EP_NO; ++i)
    {
        /* Endpoint index table clear */
        usb_gpstd_EpTblIndex[0][i] = USB_ERROR;
        usb_gpstd_EpTblIndex[1][i] = USB_ERROR;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_ClearEpTblIndex
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_GetConfigNum
 **********************************************************************************************************************/
/*!
 * @brief    Get number of possible configurations
 * @details
 * @param    void
 * @retval   uint16_t - Number of possible configurations
 **********************************************************************************************************************/
uint16_t usb_pstd_GetConfigNum(void)
{
    /* Configuration Number */
    return (uint16_t)(usb_gpstd_Driver.devicetbl[USB_DEV_NUM_CONFIG]);
}
/***********************************************************************************************************************
 End of function usb_pstd_GetConfigNum
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_get_confignum_to_tblindex
 **********************************************************************************************************************/
/*!
 * @brief    Get Configuration descriptor table index
 * @details
 * @param    void
 * @param    uint16_t con_num : Configuration Number
 * @retval   uint16_t - Configuration descriptor table index
 **********************************************************************************************************************/
uint16_t usb_pstd_get_confignum_to_tblindex(uint16_t con_num)
{
    uint16_t conf;
    uint16_t i;
    uint16_t tbl_index = 0;

    conf = con_num;
    if (conf < (uint16_t) 1)
    {
        /* Address state */
        conf = (uint16_t) 1;
    }

    /* Configuration Descriptor search loop */
    for (i = 0; i < con_num; i++)
    {
        /* Check Configuration Number.   5:bConfigurationValue */
        if ((*(uint8_t*) (usb_gpstd_Driver.configtbl[i]
                + USB_DEV_B_CONFIGURATION_VALUE)) == con_num)
        {
            /* Set Configuration tabile index */
            tbl_index = i;
            break;
        }
    }

    return tbl_index;
}
/***********************************************************************************************************************
 End of function usb_pstd_get_confignum_to_tblindex
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_GetInterfaceNum
 **********************************************************************************************************************/
/*!
 * @brief    Get interface number
 * @details
 * @param    uint16_t con_num - Configuration Number
 * @retval   uint16_t - Number of this interface
 **********************************************************************************************************************/
uint16_t usb_pstd_GetInterfaceNum(uint16_t con_num)
{
    uint16_t conf;
    uint16_t num_if = 0;
    uint16_t tbl_index;

    conf = con_num;
    if (conf < (uint16_t) 1)
    {
        /* Address state */
        conf = (uint16_t) 1;
    }

    /* Get Configuration descriptor table index */
    tbl_index = usb_pstd_get_confignum_to_tblindex(conf);

    /* Get NumInterfaces.        4:bNumInterfaces */
    num_if = *(uint8_t*) (usb_gpstd_Driver.configtbl[tbl_index]
            + USB_DEV_B_NUM_INTERFACES);

    return num_if;
}
/***********************************************************************************************************************
 End of function usb_pstd_GetInterfaceNum
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_GetAlternateNum
 **********************************************************************************************************************/
/*!
 * @brief    Get Alternate Setting Number
 * @details
 * @param    uint16_t con_num - Configuration Number
 * @param    uint16_t int_num - Interface Number
 * @retval   uint16_t  - Alternate setting
 **********************************************************************************************************************/
uint16_t usb_pstd_GetAlternateNum(uint16_t con_num, uint16_t int_num)
{
    uint16_t i;
    uint16_t conf;
    uint16_t alt_num = 0;
    uint8_t *ptr;
    uint16_t length;
    uint16_t tbl_index;

    conf = con_num;
    if (conf < (uint16_t) 1)
    {
        /* Address state */
        conf = (uint16_t) 1;
    }

    /* Get Configuration descriptor table index */
    tbl_index = usb_pstd_get_confignum_to_tblindex(conf);

    ptr = usb_gpstd_Driver.configtbl[tbl_index];
    i = ptr[0];
    /* Interface descriptor[0] */
    ptr = (uint8_t*) ((uint32_t) ptr + ptr[0]);
    length = (uint16_t)(
            *(uint8_t*) ((uint32_t) usb_gpstd_Driver.configtbl[tbl_index]
                    + (uint16_t) 2u));
    length |=
            (uint16_t)(
                    (uint16_t)(
                            *(uint8_t*) ((uint32_t) usb_gpstd_Driver.configtbl[tbl_index]
                                    + (uint16_t) 3u)) << 8u);

    /* Search descriptor table size */
    for (; i < length;)
    {
        /* Descriptor type ? */
        switch (ptr[1])
        {
        /* Interface */
        case USB_DT_INTERFACE:
            if (int_num == ptr[2])
            {
                /* Alternate number count */
                alt_num = (uint16_t) ptr[3];
            }
            i += ptr[0];
            /* Interface descriptor[0] */
            ptr = (uint8_t*) ((uint32_t) ptr + ptr[0]);
            break;
            /* Device */
        case USB_DT_DEVICE:
            /* Continue */
            /* Configuration */
        case USB_DT_CONFIGURATION:
            /* Continue */
            /* String */
        case USB_DT_STRING:
            /* Continue */
            /* Endpoint */
        case USB_DT_ENDPOINT:
            /* Continue */
            /* Class, Vendor, else */
        default:
            i += ptr[0];
            /* Interface descriptor[0] */
            ptr = (uint8_t*) ((uint32_t) ptr + ptr[0]);
            break;
        }
    }
    return alt_num;
}
/***********************************************************************************************************************
 End of function usb_pstd_GetAlternateNum
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetEpTblIndex
 **********************************************************************************************************************/
/*!
 * @brief    Set endpoint index in table (buffer) for configuration descriptor
 * @details  i.e. set which endpoints to use based on specified Configuration
 * @param    uint16_t con_num - Configuration Number
 * @param    uint16_t int_num - Interface Number
 * @param    uint16_t  - Alternate setting
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_SetEpTblIndex(uint16_t con_num, uint16_t int_num,
        uint16_t alt_num)
{
    uint8_t *ptr;
    uint16_t i;
    uint16_t j;
    uint16_t length;
    uint16_t conf;
    uint16_t start;
    uint16_t numbers;
    uint16_t ep;
    uint16_t tbl_index;
    uint16_t dir;

    conf = con_num;
    if (conf < (uint16_t) 1)
    {
        /* Address state */
        conf = (uint16_t) 1;
    }

    /* Get Configuration descriptor table index */
    tbl_index = usb_pstd_get_confignum_to_tblindex(conf);

    /* Configuration descriptor */
    ptr = usb_gpstd_Driver.configtbl[tbl_index];
    i = *ptr;
    length = (uint16_t)(*(uint8_t*) ((uint32_t) ptr + (uint32_t) 3u));
    length = (uint16_t)(length << 8);
    length += (uint16_t)(*(uint8_t*) ((uint32_t) ptr + (uint32_t) 2u));
    ptr = (uint8_t*) ((uint32_t) ptr + (*ptr));
    start = 0;
    numbers = 0;
    j = 0;

    for (; i < length;)
    {
        /* Descriptor type ? */
        switch (*(uint8_t*) ((uint32_t) ptr + (uint32_t) 1u))
        {
        /* Interface */
        case USB_DT_INTERFACE:
            if (((*(uint8_t*) ((uint32_t) ptr + (uint32_t) 2u)) == int_num)
                    && ((*(uint8_t*) ((uint32_t) ptr + (uint32_t) 3u)) == alt_num))
            {
                numbers = *(uint8_t*) ((uint32_t) ptr + (uint32_t) 4u);
            } else
            {
                start += (*(uint8_t*) ((uint32_t) ptr + (uint32_t) 4u));
            }
            i += (*ptr);
            ptr = (uint8_t*) ((uint32_t) ptr + (*ptr));
            break;
            /* Endpoint */
        case USB_DT_ENDPOINT:
            if (j < numbers)
            {
                ep = (uint16_t) * (uint8_t*) ((uint32_t) ptr + (uint32_t) 2u);
                if ( USB_EP_IN == (ep & USB_EP_DIRMASK))
                {
                    dir = 1; /* IN */
                } else
                {
                    dir = 0; /* OUT */
                }
                ep &= (uint16_t) 0x0f;
                usb_gpstd_EpTblIndex[dir][ep] = (uint8_t)(start + j);
                ++j;
            }
            i += (*ptr);
            ptr = (uint8_t*) ((uint32_t) ptr + (*ptr));
            break;
            /* Device */
        case USB_DT_DEVICE:
            /* Continue */
            /* Configuration */
        case USB_DT_CONFIGURATION:
            /* Continue */
            /* String */
        case USB_DT_STRING:
            /* Continue */
            /* Class, Vendor, else */
        default:
            i += (*ptr);
            ptr = (uint8_t*) ((uint32_t) ptr + (*ptr));
            break;
        }
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_SetEpTblIndex
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_ChkRemote
 **********************************************************************************************************************/
/*!
 * @brief    Check if the RemoteWakeUp bit is set for the current configuration
 * @details
 * @param    void
 * @retval   uint16_t - remote wakeup status (YES/NO)
 **********************************************************************************************************************/
uint16_t usb_pstd_ChkRemote(void)
{
    uint8_t atr;
    uint16_t tbl_index;

    if (0 == usb_gpstd_ConfigNum)
    {
        return USB_FALSE;
    }

    /* Get Configuration descriptor table index */
    tbl_index = usb_pstd_get_confignum_to_tblindex(usb_gpstd_ConfigNum);

    /* Get Configuration Descriptor - bmAttributes */
    atr = *(uint8_t*) ((uint32_t) usb_gpstd_Driver.configtbl[tbl_index]
            + (uint32_t) 7u);
    /* Remote Wakeup check(= D5) */
    if ((atr & USB_CF_RWUPON) == USB_CF_RWUPON)
    {
        return USB_TRUE;
    }
    return USB_FALSE;
}
/***********************************************************************************************************************
 End of function usb_pstd_ChkRemote
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_GetCurrentPower
 **********************************************************************************************************************/
/*!
 * @brief    Find out how the peripheral is powered for the current configuration
 * @details
 * @param    void
 * @retval   currentpower - self-powered or bus-powered (GS_SELFPOWERD/GS_BUSPOWERD)
 **********************************************************************************************************************/
uint8_t usb_pstd_GetCurrentPower(void)
{

    uint8_t tmp;
    uint8_t currentpower;
    uint8_t conf;
    uint16_t tbl_index;

    conf = (uint8_t) usb_gpstd_ConfigNum;
    if (conf < (uint8_t) 1)
    {
        /* Address state */
        conf = (uint8_t) 1;
    }

    /* Get Configuration descriptor table index */
    tbl_index = usb_pstd_get_confignum_to_tblindex(conf);

    /* Standard configuration descriptor */
    tmp = *(uint8_t*) ((uint32_t) usb_gpstd_Driver.configtbl[tbl_index]
            + (uint32_t) 7u);
    if ((tmp & USB_CF_SELFP) == USB_CF_SELFP)
    {
        /* Self Powered */
        currentpower = USB_GS_SELFPOWERD;
    } else
    {
        /* Bus Powered */
        currentpower = USB_GS_BUSPOWERD;
    }

    /* Check currently powered */
    return currentpower;
}
/***********************************************************************************************************************
 End of function usb_pstd_GetCurrentPower
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetPipeRegister
 **********************************************************************************************************************/
/*!
 * @brief    Configure specified pipe.
 * @details
 * @param    uint16_t pipe  - Pipe number
 * @param    uint16_t *tbl  - ep table
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_SetPipeRegister(uint16_t pipe_number, uint16_t *tbl)
{
    uint16_t i;
    uint16_t pipe;
    uint16_t ep;
    uint16_t dir;

    switch (pipe_number)
    {
    /* Initialise all pipes */
    case USB_USEPIPE:
        for (i = 0; USB_PDTBLEND != tbl[i]; i += USB_EPL)
        {
            /* Pipe number */
            pipe = (uint16_t)(tbl[i + 0] & USB_CURPIPE);
            usb_cstd_pipe_init(pipe, tbl, i);
        }
        break;
        /* Initialise peripheral pipes */
    case USB_PERIPIPE:
        for (ep = USB_EP1; ep <= USB_MAX_EP_NO; ++ep)
        {
            for (dir = 0; dir < 2; dir++)
            {
                if (USB_ERROR != usb_gpstd_EpTblIndex[dir][ep])
                {
                    i = (uint16_t)(USB_EPL * usb_gpstd_EpTblIndex[dir][ep]);

                    /* Pipe number */
                    pipe = (uint16_t)(tbl[i + 0] & USB_CURPIPE);

                    usb_cstd_pipe_init(pipe, tbl, i);
                }
            }
        }
        break;
        /* Clear Peripheral pipe register */
    case USB_CLRPIPE:
        /* Clear current pipe */
        for (ep = USB_EP1; ep <= USB_MAX_EP_NO; ++ep)
        {
            for (dir = 0; dir < 2; dir++)
            {
                if (USB_ERROR != usb_gpstd_EpTblIndex[dir][ep])
                {
                    i = (uint16_t)(USB_EPL * usb_gpstd_EpTblIndex[dir][ep]);
                    /* Pipe number */
                    pipe = (uint16_t)(tbl[i + 0] & USB_CURPIPE);
                    usb_cstd_ClrPipeCnfg(pipe);
                }
            }
        }
        break;
        /* Initialise specified pipe */
    default:
        for (i = 0; USB_PDTBLEND != tbl[i]; i += USB_EPL)
        {
            /* Pipe number */
            pipe = (uint16_t)(tbl[i + 0] & USB_CURPIPE);
            if (pipe == pipe_number)
            {
                usb_cstd_pipe_init(pipe, tbl, i);
            }
        }
        break;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_SetPipeRegister
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_StopClock
 **********************************************************************************************************************/
/*!
 * @brief    If low-power mode configured stop clock
 * @details  If low-power mode is configured then stop clock supply to EPC,
 * @details  SIE and USBPHY and enter SUSPEND mode
 * @param    uint16_t pipe_no  : pipe number
 * @retval   void
 **********************************************************************************************************************/
void usb_cstd_StopClock(void)
{
#if USB_CPU_LPW_PP  == USB_LPWR_USE_PP
    usb_gcstd_SuspendMode = 1/*USB_SUSPEND_MODE*/;
    /* UTMI Suspend Mode */
    /* Set SUSPEND bit to stop clock supply for EPC, SIE, USBPHY */
    ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.BIT.SUSPEND =
            1;
#endif /*  USB_CPU_LPW_PP  == USB_LPWR_USE_PP */
}
/***********************************************************************************************************************
 End of function usb_cstd_StopClock
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_ClrPipeCnfg
 **********************************************************************************************************************/
/*!
 * @brief    Clear Pipe configuration
 * @details
 * @param    uint16_t pipe - pipe number
 * @retval   void
 **********************************************************************************************************************/
void usb_cstd_ClrPipeCnfg(uint16_t pipe)
{
    uint16_t ep_num;

    /* find ep associated with this pipe */
    for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }
    if (ep_num <= USB_MAX_EP_NO)
    {
        usb_gcstd_Pipe[pipe] = (USB_UTR_t*) USB_NULL;

        /* PID=NAK & clear STALL */
        usb_cstd_ClrStall_EPm(ep_num);

#if USB_DMA_PP == USB_DMA_USE_PP
        usb_cpu_d0fifo_stop_dma();

        usb_creg_clr_dreqe( USB_D0DMA );
        usb_cstd_chg_curpipe( (uint16_t)USB_PIPE0, (uint16_t)USB_D0DMA, USB_FALSE);

#endif    /* USB_DMA_PP */

        /* clear transaction counter */
    }
}
/***********************************************************************************************************************
 End of function usb_cstd_ClrPipeCnfg
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_ForcedTermination
 **********************************************************************************************************************/
/*!
 * @brief    Terminate data transmission and reception
 * @details
 * @param    uint16_t pipe_no  : pipe number
 * @param    uint16_t status   : Transfer status type
 * @retval   void
 **********************************************************************************************************************/
void usb_cstd_ForcedTermination(uint16_t pipe, uint16_t status)
{
    uint16_t ep_num;
#if USB_DMA_PP == USB_DMA_USE_PP
    uint16_t useport;
#endif

    if (USB_PIPE0 != pipe)
    {
        /* find ep associated with this pipe */
        for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
        {
            if (usbf_eps[ep_num].pipe == pipe)
            {
                break;
            }
        }
        if (ep_num <= USB_MAX_EP_NO)
        {
            /* PID = NAK */
            /* Set NAK  */
            usb_cstd_SetONak(pipe);
            usbf_eps[ep_num].state = USB_DS_IDST;

            /* Disable Interrupts for EP associated with this pipe */
            disable_usbf_epc_epm_isr(ep_num);

            /* Clear transaction counter */
#if USB_DMA_PP == USB_DMA_USE_PP
            /* Check access */

            /* Pipe number to port select */
            useport = usb_cstd_Pipe2Fport( pipe );
            /* D0FIFO use */
            if (USB_D0DMA == useport || USB_D0DMA_C == useport)
            {
                /* Stop DMA,FIFO access */
                usb_cpu_d0fifo_stop_dma();

                usb_cstd_D0fifoStopUsb();
                usb_cstd_D0FifoselSet();
            }
#endif    /* USB_DMA_PP */
        }

        /* Call Back */
        if (USB_NULL != usb_gcstd_Pipe[pipe])
        {
            /* Transfer information set */
            usb_gcstd_Pipe[pipe]->tranlen = usb_gcstd_DataCnt[pipe];
            usb_gcstd_Pipe[pipe]->status = status;

            if ( USB_NULL != (usb_gcstd_Pipe[pipe]->complete))
            {
                (usb_gcstd_Pipe[pipe]->complete)(usb_gcstd_Pipe[pipe]);
            }
            usb_gcstd_Pipe[pipe] = (USB_UTR_t*) USB_NULL;
        }
    }
}
/***********************************************************************************************************************
 End of function usb_cstd_ForcedTermination
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_PortSpeed
 **********************************************************************************************************************/
/*!
 * @brief    Get USB-speed of function port
 * @details
 * @param    void
 * @retval   uint16_t : HSCONNECT - Hi-Speed, FSCONNECT - Full-Speed, NOCONNECT - not connect
 **********************************************************************************************************************/
uint16_t usb_cstd_PortSpeed(void)
{
    uint16_t ConnInf;

    if (1
            == ((volatile EPC_USB_STATUS_Type *) USBFUNC_USB_EPC_STATUS_ADDRESS)->USB_STATUS.BIT.SPEED_MODE)
    {
        ConnInf = USB_HSCONNECT;
    } else
    {
        ConnInf = USB_FSCONNECT;
    }

    return (ConnInf);
}
/***********************************************************************************************************************
 End of function usb_cstd_PortSpeed
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SaveRequest
 **********************************************************************************************************************/
/*!
 * @brief    Save setup data when SETUP request received
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_SaveRequest(void)
{
    uint32_t setup0;
    uint32_t setup1;

    /* Read the setup 8 bytes from the data registers.*/
    setup0 =
            (uint32_t)(
                    (volatile EPC_SETUP_DATA0_Type *) USBFUNC_USB_EPC_SETUP_DATA0_ADDRESS)->SETUP_DATA0.LONG;
    setup1 =
            (uint32_t)(
                    (volatile EPC_SETUP_DATA1_Type *) USBFUNC_USB_EPC_SETUP_DATA1_ADDRESS)->SETUP_DATA1.LONG;

    usb_gpstd_ReqType = (uint16_t)(setup0 & USB_BMREQUESTTYPE);
    /* Check direction */
    if ((usb_gpstd_ReqType & USB_EP_DIRMASK) == USB_EP_IN)
    {
        usbf_eps[USB_EP0].dir = USB_EP_IN;
    } else
    {
        usbf_eps[USB_EP0].dir = USB_EP_OUT;
    }
    usb_gpstd_ReqTypeType = (uint16_t)(setup0 & USB_BMREQUESTTYPETYPE);
    usb_gpstd_ReqTypeRecip = (uint16_t)(setup0 & USB_BMREQUESTTYPERECIP);
    usb_gpstd_ReqRequest = (uint16_t)(setup0 & USB_BREQUEST);

    usb_gpstd_ReqValue = (uint16_t)(setup0 >> 16); /*Setup packet */
    usb_gpstd_ReqIndex = (uint16_t)(setup1 & 0xFFFF);
    usb_gpstd_ReqLength = (uint16_t)(setup1 >> 16);
}
/***********************************************************************************************************************
 End of function usb_pstd_SaveRequest(void)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_ChkConfigured
 **********************************************************************************************************************/
/*!
 * @brief    Check if USB Device is in a CONFIGURED state
 * @details
 * @param    void
 * @retval   Configuration state TRUE or FALSE
 **********************************************************************************************************************/
uint16_t usb_pstd_ChkConfigured(void)
{
    uint16_t ret_val;

    /* Device Status - Read USB Status Register */
    if (1
            == ((volatile EPC_USB_STATUS_Type *) USBFUNC_USB_EPC_STATUS_ADDRESS)->USB_STATUS.BIT.CONF)
    {
        ret_val = USB_TRUE;
    } else
    {
        ret_val = USB_FALSE;
    }

    return ret_val;
} /* eof usb_pstd_ChkConfigured() */
/***********************************************************************************************************************
 End of function usb_pstd_ChkConfigured
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetIStall
 **********************************************************************************************************************/
/*!
 * @brief    Set the specified pipe's PID to STALL for IN Tokens
 * @details
 * @param    uint16_t pipe  - Pipe Number
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_SetIStall(uint16_t pipe)
{
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;
    uint16_t ep_num;

    /* find ep associated with this pipe */
    for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }
    if (ep_num <= USB_MAX_EP_NO)
    {
        epm_control_reg_addr =
                (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                        + (0x20 * (ep_num - 1)));
        epm_control_reg_addr->EPm_CONTROL.BIT.EPm_ISTL = 1;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_SetIStall
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetOStall
 **********************************************************************************************************************/
/*!
 * @brief    Set the specified pipe's PID to STALL for OUT Tokens
 * @details
 * @param    uint16_t pipe  - Pipe Number
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_SetOStall(uint16_t pipe)
{
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;
    uint16_t ep_num;

    /* find ep associated with this pipe */
    for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }
    if (ep_num <= USB_MAX_EP_NO)
    {
        epm_control_reg_addr =
                (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                        + (0x20 * (ep_num - 1)));
        epm_control_reg_addr->EPm_CONTROL.BIT.EPm_OSTL_EN = 1;
        epm_control_reg_addr->EPm_CONTROL.BIT.EPm_OSTL = 1;
        epm_control_reg_addr->EPm_CONTROL.BIT.EPm_OSTL_EN = 0;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_SetOStall
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetStallPipe0
 **********************************************************************************************************************/
/*!
 * @brief    Set pipe0 PID to STALL
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_SetStallPipe0(void)
{
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_STL =
            1;
}
/***********************************************************************************************************************
 End of function usb_pstd_SetStallPipe0
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_ClrStall_EP0
 **********************************************************************************************************************/
/*!
 * @brief
 * @details  NAK the EP0, and clear the STALL-bit
 * @details  set to the PID of Pipe0
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_cstd_ClrStall_EP0(void)
{
    /* Set NAK */
    usb_cstd_SetONakPipe0();
    usb_cstd_SetINakPipe0();
    /* Clear STALL */
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_STL =
            0;
}
/***********************************************************************************************************************
 End of function usb_cstd_ClrStall_EP0
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_ClrStall_EPm
 **********************************************************************************************************************/
/*!
 * @brief
 * @details  NAK the EP, and clear the STALL-bit
 * @param    uint16_t ep - endpoint
 * @retval   void
 **********************************************************************************************************************/
void usb_cstd_ClrStall_EPm(uint16_t ep)
{
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;
    uint32_t epm_control_reg;
    uint16_t pipe;

    pipe = usbf_eps[ep].pipe;
    /* Set NAK */
    usb_cstd_SetONak(pipe);

    /* Clear STALL */
    epm_control_reg_addr =
            (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                    + (0x20 * (ep - 1)));
    epm_control_reg = epm_control_reg_addr->EPm_CONTROL.LONG;
    epm_control_reg &= (~EPC_EPm_CONTROL_EPm_ISTL_BIT);
    epm_control_reg |= EPC_EPm_CONTROL_EPm_OSTL_EN_BIT;
    epm_control_reg |= EPC_EPm_CONTROL_EPm_OSTL_BIT;
    epm_control_reg &= (~EPC_EPm_CONTROL_EPm_OSTL_EN_BIT);

    epm_control_reg_addr->EPm_CONTROL.LONG = epm_control_reg;
}
/***********************************************************************************************************************
 End of function usb_cstd_ClrStall_EPm
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_SetONak
 **********************************************************************************************************************/
/*!
 * @brief    NAK the specified pipe (non-Control pipe)
 * @details
 * @param    uint16_t pipe - Pipe Number
 * @retval   void
 **********************************************************************************************************************/
void usb_cstd_SetONak(uint16_t pipe)
{
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;
    uint16_t ep_num;

    /* find ep associated with this pipe */
    for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }
    if (ep_num <= USB_MAX_EP_NO)
    {
        epm_control_reg_addr =
                (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                        + (0x20 * (ep_num - 1)));
        epm_control_reg_addr->EPm_CONTROL.BIT.EPm_ONAK = 1;
    }
}
/***********************************************************************************************************************
 End of function usb_cstd_SetONak
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_SetONakPipe0
 **********************************************************************************************************************/
/*!
 * @brief    NAK Pipe0
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_cstd_SetONakPipe0(void)
{
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_ONAK = 1;
}
/***********************************************************************************************************************
 End of function usb_cstd_SetONakPipe0
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_SetINakPipe0
 **********************************************************************************************************************/
/*!
 * @brief    NAK Pipe0
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_cstd_SetINakPipe0(void)
{
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_INAK_EN = 1;
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_INAK = 1;
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_INAK_EN = 0;
}
/***********************************************************************************************************************
 End of function usb_cstd_SetINakPipe0
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_reset_ep
 **********************************************************************************************************************/
/*!
 * @brief    Reset the EP
 * @details
 * @param    ep_num
 * @retval   void
 **********************************************************************************************************************/
void usb_reset_ep(uint16_t ep_num)
{
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;

    if (USB_EP0 == ep_num)
    {
        /*Clear EP0 buffer (write & read regs on CPU side & USB side) */
        ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_BCLR =
                1;
    } else
    {
        epm_control_reg_addr =
                (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                        + (0x20 * (ep_num - 1)));
        epm_control_reg_addr->EPm_CONTROL.BIT.EPm_BCLR = 1;
    }
}
/***********************************************************************************************************************
 End of function usb_reset_ep
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_Epadr2Pipe
 **********************************************************************************************************************/
/*!
 * @brief    Get the associated pipe no. of the specified endpoint
 * @details
 * @param    uint16_t dir_ep - Direction + endpoint number
 * @retval   uint16_t - OK : Pipe number, otherwise ERROR
 **********************************************************************************************************************/
uint16_t usb_cstd_Epadr2Pipe(uint16_t dir_ep)
{
    uint16_t i;
    uint16_t direp;
    uint16_t tmp;
    uint16_t *table;
    uint16_t conf;

    conf = usb_gpstd_ConfigNum;
    if (conf < (uint16_t) 1)
    {
        /* Address state */
        conf = (uint16_t) 1;
    }

    /* Peripheral */
    /* Get PIPE Number from Endpoint address */
    table = (uint16_t*) ((uint16_t**) (usb_gpstd_Driver.pipetbl[conf - 1]));
    direp = (uint16_t)(((dir_ep & 0x80) >> 3) | (dir_ep & 0x0F));
    /* EP table loop */
    for (i = 0; USB_PDTBLEND != table[i]; i += USB_EPL)
    {
        tmp = (uint16_t)(table[i + 1] & (USB_DIRFIELD | USB_EPNUMFIELD));
        /* EP table endpoint dir check */
        if (direp == tmp)
        {
            return table[i];
        }
    }

    return USB_ERROR ;
}
/***********************************************************************************************************************
 End of function usb_cstd_Epadr2Pipe
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_EpNum2PipeDir
 **********************************************************************************************************************/
/*!
 * @brief    Get the direction of the pipe associated with the given endpoint
 * @details
 * @param    uint16_t ep_num - endpoint number
 * @retval   uint16_t - OK : Pipe direction, or USB_DIR_P_IN as default if pipe not found
 **********************************************************************************************************************/
uint16_t usb_cstd_EpNum2PipeDir(uint16_t ep_num)
{
    uint16_t * table;
    uint16_t conf;
    uint16_t i;

    conf = usb_gpstd_ConfigNum;
    if( conf < (uint16_t)1 )
    {
        /* Address state */
        conf = (uint16_t)1;
    }

    /* Get PIPE Number from Endpoint number and then get pipes direction */
    table = (uint16_t*)((uint16_t**)(usb_gpstd_Driver.pipetbl[conf - 1]));
    /* EP table loop */
    for (i = 0; USB_PDTBLEND != table[i]; i += USB_EPL)
    {
        if ( ((uint16_t)(table[i + 1] & USB_EPNUMFIELD)) == ep_num )
        {
            return (table[i + 1] & USB_DIRFIELD);
        }
    }

    /* USB_DIR_P_IN is the default for the system so also use for pipe not found case */
    return USB_DIR_P_IN;
}
/***********************************************************************************************************************
End of function usb_cstd_EpNum2PipeDir
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_GetPipeType
 **********************************************************************************************************************/
/*!
 * @brief    Find and return PIPE TYPE.
 * @details
 * @param    uint16_t pipe  - Pipe number.
 * @retval   uint16_t Pipe type
 **********************************************************************************************************************/
uint16_t usb_cstd_GetPipeType(uint16_t pipe)
{
    uint16_t buffer = 0; /* initialise to invalid type */
    uint16_t ep_num;
    uint16_t ep_mode;
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;

    /* find ep associated with this pipe */
    for (ep_num = USB_EP0; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }

    if ((ep_num > USB_EP0) && (ep_num <= USB_MAX_EP_NO))
    {
        epm_control_reg_addr =
                (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                        + (0x20 * (ep_num - 1)));

        ep_mode = (uint16_t) epm_control_reg_addr->EPm_CONTROL.BIT.EPm_MODE;
        if (0 == ep_mode)
        {
            buffer = USB_BULK;
        } else if (1 == ep_mode)
        {
            buffer = USB_INT;
        } else if (2 == ep_mode)
        {
            buffer = USB_ISO;
        }
    }
    return buffer;
}
/***********************************************************************************************************************
 End of function usb_cstd_GetPipeType
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_GetPipeDir
 **********************************************************************************************************************/
/*!
 * @brief    Get pipe direction for non- Control pipe
 * @details
 * @param    uint16_t pipe  - Pipe number.
 * @retval   uint16_t pipe direction
 **********************************************************************************************************************/
uint16_t usb_cstd_GetPipeDir(uint16_t pipe)
{
    uint16_t ep_num;
    uint16_t ep_dir = 0;

    /* find ep associated with this pipe */
    for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }

    if (ep_num <= USB_MAX_EP_NO)
    {
        if (USB_EP_OUT == usbf_eps[ep_num].dir)
        {
            ep_dir = USB_DIR_P_OUT;

        } else
        {
            ep_dir = USB_DIR_P_IN;
        }
    }
    return ep_dir;
}
/***********************************************************************************************************************
 End of function usb_cstd_GetPipeDir
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_Pipe2Fport
 **********************************************************************************************************************/
/*!
 * @brief    Get port selection for non-Control pipe
 * @details
 * @param    uint16_t pipe  - Pipe number.
 * @retval   uint16_t port selection
 **********************************************************************************************************************/
uint16_t usb_cstd_Pipe2Fport(uint16_t pipe)
{
    uint16_t i;
    uint16_t *table;
    uint16_t conf;

    conf = usb_gpstd_ConfigNum;
    if (conf < (uint16_t) 1)
    {
        /* Address state */
        conf = (uint16_t) 1;
    }
    /* Peripheral */
    /* Get port from PIPE number */
    table = (uint16_t*) ((uint16_t**) (usb_gpstd_Driver.pipetbl[conf - 1]));
    /* EP table loop */
    for (i = 0; USB_PDTBLEND != table[i]; i += USB_EPL)
    {
        if (table[i] == pipe)
        {
            return table[i + 5];
        }
    }
    return USB_ERROR ;
}
/***********************************************************************************************************************
 End of function usb_cstd_Pipe2Fport
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_pipe_init
 **********************************************************************************************************************/
/*!
 * @brief    Initialization of registers associated with specified pipe
 * @details
 * @param    uint16_t pipe  - Pipe number
 * @param    uint16_t *tbl  - ep table
 * @param    uint16_t ofs   - ep table offset
 * @retval   void
 **********************************************************************************************************************/
static void usb_cstd_pipe_init(uint16_t pipe, uint16_t *tbl, uint16_t ofs)
{
    uint16_t ep_num;

    if (0 == pipe)
    {
        sample_app_printf("\nusb_cstd_pipe_init() PIPE=0\n");
    }
    /* find ep associated with this pipe */
    for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }
    if (ep_num <= USB_MAX_EP_NO)
    {
        usb_gcstd_Pipe[pipe] = (USB_UTR_t*) USB_NULL;

        /* Disable interrupts for the ep */
        disable_usbf_epc_epm_isr(ep_num);

        /* PID=NAK & clear STALL */
        usb_cstd_ClrStall_EPm(ep_num);

#if USB_DMA_PP == USB_DMA_USE_PP
        if((( USB_D0DMA == tbl[ofs + 5])||(USB_D0DMA_C == tbl[ofs + 5]))||(USB_D1DMA_C == tbl[ofs + 5]))
        {
            tbl[ofs + 1] |= USB_BFREON;
        }
#endif
    }
}
/***********************************************************************************************************************
 End of function usb_cstd_pipe_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
