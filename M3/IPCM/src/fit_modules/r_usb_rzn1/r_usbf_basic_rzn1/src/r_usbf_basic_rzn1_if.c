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
 * $Revision: 1815 $
 * $Date: 2020-01-27 14:51:49 +0000 (Mon, 27 Jan 2020) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usbf_basic_rzn1_if.c
 * Description  :  USB Driver API code
 *                 USB Function transfer level commands.
 * (C) Copyright Renesas Electronics Europe Ltd. 2020. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Doxygen Design Documentation block:
 **********************************************************************************************************************/
/*!
 * @page PageUSBfBasic USB function basic bare metal driver
 * @tableofcontents
 * @section usbf_basic USB USB function basic driver
 * @ref USBF_BASIC_MODULE
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
 * @ingroup USBF_BASIC_MODULE RZN1 USBf Basic Bare Metal Driver
 * @{
 * @file
 * @brief USBf Basic Bare Metal Driver
 * @details Supports configuring, reading and writing USB device port
 * @} */
/***********************************************************************************************************************
 * End of Doxygen Summary block
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "r_usb_basic_config.h"
#include "r_sysctrl_rzn1_if.h"
#include "r_usbf_basic_rzn1_if.h"
#include "mcu_interrupts_if.h"
#include "r_usb_common.h"
#include "r_usb_cdefusbip.h"
#include "r_usbf_core.h"
#include "r_usbf_hal.h"
#include "r_usbf_driver.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/
static USBF_DRIVER_STATE_E usbf_driver_state = USBF_DRIVER_STATE_UNINITIALISED;

/***********************************************************************************************************************
 Renesas Abstracted Peripheral Driver API functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_USBf_Init
 **********************************************************************************************************************/
/*!
 * @brief    Initialise USB function bare metal driver
 * @details  Initialise USB Port 1 function parameters
 * @details  Call system controller to initialise USB function controller
 * @param    void
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_USBf_Init(void)
{
    ER_RET ret_val = ER_OK;
#ifndef USB_FUNCTION_POLLING
    IRQn_Type irq_num;
    uint32_t int_priority = USB_INT_PRIORITY;
#endif
    uint8_t *reg_info;

    if (USBF_DRIVER_STATE_INITIALISED == usbf_driver_state)
    {
        ret_val = ER_INVAL;
    }
    else
    {
        /* Initialise USB function controller  */
        ret_val = R_SYSCTRL_EnableUSBf();

    #ifndef USB_FUNCTION_POLLING
        /* Register interrupt handler for USBF_EPC (AHB-EPC bridge) */
        irq_num = (IRQn_Type) RZN1_IRQ_USBF_EPC;
        if (R_BSP_InterruptRegisterCallback(irq_num,
                (bsp_int_cb_t) &handle_usbf_epc_isr) == MCU_INT_SUCCESS)
        {
            ret_val = R_BSP_InterruptControl(irq_num,
                    MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
            if (MCU_INT_SUCCESS != ret_val)
            {
                ret_val = ER_SYS;
            }
        } else
        {
            ret_val = ER_SYS;
        }

        if (ER_OK == ret_val)
        {
            /* Register interrupt handler for USBF */
            irq_num = (IRQn_Type) RZN1_IRQ_USBF;
            if (R_BSP_InterruptRegisterCallback(irq_num,
                    (bsp_int_cb_t) &handle_usbf_isr) == MCU_INT_SUCCESS)
            {
                ret_val = R_BSP_InterruptControl(irq_num,
                        MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
                if (MCU_INT_SUCCESS != ret_val)
                {
                    ret_val = ER_SYS;
                }
            } else
            {
                ret_val = ER_SYS;
            }
        }
    #endif

        /* Clear registration info of USB device Class application for USB peripheral driver */
        reg_info = (uint8_t *) &usb_gpstd_Driver;
        memset(reg_info, 0, sizeof(USB_PCDREG_t));

        if (ER_OK == ret_val)
        {
            usbf_driver_state = USBF_DRIVER_STATE_INITIALISED;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_USBf_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_USB_Open
 **********************************************************************************************************************/
/*!
 * @brief    Prepare USB function port for connection to USB Host
 * @details  Register USBf interrupt handler,  Startup USBf
 * @details  Enable USBf interrupts. Check USB connection status.
 * @param    void
 * @retval   Error status
 **********************************************************************************************************************/
ER_RET R_USB_Open(void)
{
    ER_RET ret_val = ER_OK;
    USB_ERR usb_status;

    /*Initialise the USB core */
    usb_status = R_USBCORE_Init();

    if (USB_ERR_OK != usb_status)
    {
        /* Check USB error & print if error */
        ret_val = ER_SYS;
    } else
#ifndef USB_FUNCTION_POLLING
    {
        IRQn_Type irq_num;

        /* Enable USBF_EPC Interrupt */
        irq_num = (IRQn_Type) RZN1_IRQ_USBF_EPC;
        ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_ENABLE,
                FIT_NO_PTR);

        if (ER_OK == ret_val)
        {
            /* Enable USBF Interrupt */
            irq_num = (IRQn_Type) RZN1_IRQ_USBF;
            ret_val = R_BSP_InterruptControl(irq_num,
                    MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);
        }
    }

    if (ER_OK == ret_val) {
#else
    {
        systimer_nonblocking_delay(USBF_NON_BLOCKING_DELAY_INSTANCE, USB_POLL_PERIOD_uS);
#endif
        /* Enable EP0 and Initial connect */
        usb_pstd_InitConnect();
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_USB_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_USB_Close
 **********************************************************************************************************************/
/*!
 * @brief    Close USB function connection
 * @details
 * @details
 * @param    void
 * @retval   Error status
 **********************************************************************************************************************/
ER_RET R_USB_Close(void)
{
    ER_RET ret_val = ER_OK;
#ifndef USB_FUNCTION_POLLING
    /*USB_ERR usb_status;*/
    IRQn_Type irq_num;

    /* Terminate all connections and disable EP0 */
    /*usb_pstd_Disconnect_and_disable();    */
    /* Disable USBF Interrupt */
    irq_num = (IRQn_Type) RZN1_IRQ_USBF;
    ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE,
            FIT_NO_PTR);
    if (ER_OK == ret_val)
    {
        /* Disable USBF_EPC Interrupt */
        irq_num = (IRQn_Type) RZN1_IRQ_USBF_EPC;
        ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE,
                FIT_NO_PTR);
    }
#else
    systimer_nonblocking_delay_cancel(USBF_NON_BLOCKING_DELAY_INSTANCE);
#endif
    /*Un-Initialise the USB core */
    /*usb_status = R_USBCORE_Init();*/

    /* De=register the USB peripheral class application */
    R_usb_pstd_driver_deregister();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_USB_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 * Function Name:   R_USBf_Uninit
 *
 * Description  :   Uninitialises the USBf driver
 *
 * Arguments    :   None
 *
 * Return Value :   Error status
 *
 **********************************************************************************************************************/
ER_RET R_USBf_Uninit(void)
{
    ER_RET ret_val = ER_OK;

    if (USBF_DRIVER_STATE_UNINITIALISED == usbf_driver_state)
    {
        ret_val = ER_INVAL;
    }
    else
    {
        R_SYSCTRL_DisableUSBf();
        usbf_driver_state = USBF_DRIVER_STATE_UNINITIALISED;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_USBf_Uninit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_usb_pstd_TransferStart
 *
 *  Description:    Initiate data transfer for a Pipe Request PCD to transfer data, and the PCD transfers the data
 *                  based on the transfer information stored in ptr
 *
 *  Parameters:     *ptr : keyword, msghead and msginfo are used for...
 *
 *  Return Value:   Error info.
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_pstd_TransferStart(USB_UTR_t *ptr)
{
    USB_ER_t err;
    uint16_t pipenum;

    pipenum = ptr->keyword;
    if (USB_NULL != usb_gcstd_Pipe[pipenum])
    {
        /* Get PIPE TYPE */
        if (usb_cstd_GetPipeType(pipenum) != USB_ISO)
        {
            /* R_usb_pstd_TransferStart overlaps */
            return USB_QOVR ;
        }
    }

    /* Check state ( Configured ) */
    if (usb_pstd_ChkConfigured() != USB_TRUE)
    {
        /* not configured */
        return USB_ERROR ;
    }

    if (USB_PIPE0 == pipenum)
    {
        return USB_ERROR ;
    }

    err = usb_pstd_SetSubmitutr(ptr);
    return err;

}
/***********************************************************************************************************************
 End of function R_usb_pstd_TransferStart
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_usb_pstd_TransferEnd
 *
 *  Description:    Force termination of data transfer of specified pipe. Request PCD to force termination
 *                  data transfer, and the PCD forced-terminates data transfer.
 *
 *  Parameters:     pipe : Pipe number.
 *
 *  Return Value:   Error info.
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_pstd_TransferEnd(uint16_t pipe)
{
    if (USB_NULL == usb_gcstd_Pipe[pipe])
    {
        return USB_ERROR ;
    } else
    {
        usb_cstd_ForcedTermination(pipe, (uint16_t)USB_DATA_STOP);
    }

    return USB_OK ;
}
/***********************************************************************************************************************
 End of function R_usb_pstd_TransferEnd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_usb_pstd_ChangeDeviceState
 **********************************************************************************************************************/
/*!
 * @brief    Change USB Device to the status specified by argument
 * @details  Register pipe information table, descriptor information table,
 * @param    state - New device state
 * @param    keyword - Pipe
 * @param    complete - Callback function
 * @retval   void
 **********************************************************************************************************************/
void R_usb_pstd_ChangeDeviceState(uint16_t state, uint16_t keyword,
        USB_UTR_CB_t complete)
{
    uint16_t pipenum;
    uint16_t connect_info;

    pipenum = keyword;
    switch (state)
    {
    case USB_DO_STALL:
        if (USB_PIPE0 == pipenum)
        {
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST; /* Reset EP0 control transfer state */
        } else
        {
            usb_pstd_SetIStall(pipenum);
            usb_pstd_SetOStall(pipenum);
        }
        usb_gpstd_StallPipe[pipenum] = USB_TRUE;
        usb_gpstd_StallCB = complete;
        break;

    case USB_DO_REMOTEWAKEUP:
        break;

    case USB_DO_DP_ENABLE:
        /* Check VBUS level */
        connect_info = usb_pstd_ChkVbsts();
        if (USB_ATTACH == connect_info)
        {
            usb_pstd_AttachProcess();
        }
        break;
    case USB_DO_DP_DISABLE:
        /* if connected, force a disconnect */
        if ((usb_pstd_ChkConfigured() == USB_TRUE))
        {
            usb_pstd_DetachProcess();
        }
        break;
    default:
        break;
    }
}
/***********************************************************************************************************************
 End of function R_usb_pstd_ChangeDeviceState
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_usb_pstd_DriverRegistration
 **********************************************************************************************************************/
/*!
 * @brief    Register a USB device Class application with the USB peripheral driver
 * @details  Register pipe information table, descriptor information table,
 * @details  callback function, etc. This info is specified by the data in
 * @details  the structure USB_PCDREG_t.
 * @param    *registinfo - registration information
 * @retval   Error status
 **********************************************************************************************************************/
ER_RET R_usb_pstd_DriverRegistration(USB_PCDREG_t *registinfo)
{
    ER_RET ret_val = ER_OK;
    USB_PCDREG_t *driver;

    driver = &usb_gpstd_Driver;

    if (driver->registered)
    {
        /* A USB device class app has already been registered for this driver */
        ret_val = ER_INVAL;
    } else
    {
        /* Pipe define table address */
        driver->pipetbl = registinfo->pipetbl;
        /* Device descriptor table address */
        driver->devicetbl = registinfo->devicetbl;
        /* Qualifier descriptor table address */
        driver->qualitbl = registinfo->qualitbl;
        /* Configuration descriptor table address */
        driver->configtbl = registinfo->configtbl;
        /* Other configuration descriptor table address */
        driver->othertbl = registinfo->othertbl;
        /* String descriptor table address */
        driver->stringtbl = registinfo->stringtbl;
        /* Device default */
        driver->devdefault = registinfo->devdefault;
        /* Device configured */
        driver->devconfig = registinfo->devconfig;
        /* Device detach */
        driver->devdetach = registinfo->devdetach;
        /* Device suspend */
        driver->devsuspend = registinfo->devsuspend;
        /* Device resume */
        driver->devresume = registinfo->devresume;
        /* Interfaced change */
        driver->interface = registinfo->interface;
        /* Control transfer */
        driver->ctrltrans = registinfo->ctrltrans;

        driver->registered = true;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function  R_usb_pstd_DriverRegistration
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_usb_pstd_driver_deregister
 **********************************************************************************************************************/
/*!
 * @brief    De-Register a USB device Class application with the USB peripheral driver
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void R_usb_pstd_driver_deregister(void)
{
    USB_PCDREG_t *driver;

    driver = &usb_gpstd_Driver;
    driver->registered = false;
}
/***********************************************************************************************************************
 End of function  R_usb_pstd_driver_deregister
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_usb_pstd_SetPipeStall
 **********************************************************************************************************************/
/*!
 * @brief    Pipe Stall Set
 * @details
 * @param    pipe - pipe number
 * @retval   void
 **********************************************************************************************************************/
void R_usb_pstd_SetPipeStall(uint16_t pipe)
{
    if (USB_PIPE0 == pipe)
    {
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST; /* Reset EP0 control transfer state */
    } else
    {
        usb_pstd_SetOStall(pipe);
        usb_pstd_SetIStall(pipe);
    }
}
/***********************************************************************************************************************
 End of function R_usb_pstd_SetPipeStall
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_usb_pstd_ControlRead
 **********************************************************************************************************************/
/*!
 * @brief    Start control read transfer (API).
 * @details  When a valid control read request is received from host,
 * @details  this function prepares data for transmission to the host and
 * @details  writes it to the write buffer
 * @param    bsize - Read size in bytes
 * @param    table - Start address of read data buffer
 * @retval   write status - USB_WRITESHRT, USB_WRITE_END, USB_WRITING
 **********************************************************************************************************************/
uint16_t R_usb_pstd_ControlRead(uint32_t bsize, uint8_t *table)
{
    return usb_pstd_ControlRead(bsize, table);
}
/***********************************************************************************************************************
 End of function R_usb_pstd_ControlRead
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_usb_pstd_ControlWrite
 *
 *  Description:    Start control write transfer (API). When a valid control write request from host is received,
 *                  the ControlWrite function enables data reception from the host.
 *
 *  Parameters:     bsize - Write size in bytes.
 *                  *table - Start address of write data buffer.
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void R_usb_pstd_ControlWrite(uint32_t bsize, uint8_t *table)
{
    usb_pstd_ControlWrite(bsize, table);
}
/***********************************************************************************************************************
 End of function R_usb_pstd_ControlWrite
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_usb_pstd_ControlEnd
 *
 *  Description:    End control transfer.
 *
 *  Parameters:     status - Control transfer status.
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void R_usb_pstd_ControlEnd(uint16_t status)
{
    usb_pstd_ControlEnd(status);
}
/***********************************************************************************************************************
 End of function R_usb_pstd_ControlEnd
 **********************************************************************************************************************/

#ifdef USB_FUNCTION_POLLING
/***********************************************************************************************************************
 *
 *  Function Name:  R_usb_interrupt_poll
 *
 *  Description:    Poll USB function interrupts
 *
 *  Parameters:     None
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
static void R_usb_interrupt_poll(void)
{
    IRQn_Type irq_num;

    if (systimer_nonblocking_delay_is_elapsed(USBF_NON_BLOCKING_DELAY_INSTANCE))
    {
        irq_num = RZN1_IRQ_USBF_EPC;
        handle_usbf_epc_isr(&irq_num);

        irq_num = RZN1_IRQ_USBF;
        handle_usbf_isr(&irq_num);

        systimer_nonblocking_delay(USBF_NON_BLOCKING_DELAY_INSTANCE, USB_POLL_PERIOD_uS);
    }
}
/***********************************************************************************************************************
 End of function R_usb_interrupt_poll
 **********************************************************************************************************************/
#endif

/***********************************************************************************************************************
 *
 *  Function Name:  R_usb_pstd_poll
 *
 *  Description:    Call PCD (Peripheral Control Driver) task (API for nonOS).
 *
 *  Parameters:     None
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void R_usb_pstd_poll(void)
{
#ifdef USB_FUNCTION_POLLING
    R_usb_interrupt_poll();
#endif
    usb_pstd_PcdTask();
}
/***********************************************************************************************************************
 End of function R_usb_pstd_poll
 **********************************************************************************************************************/

/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
