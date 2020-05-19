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
 * FILE         :  r_usbf_core.c
 * Description  :  The USB core sits above the HAL in the USB stack.
 * (C) Copyright Renesas Electronics Europe Ltd. 2020. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Doxygen Design Documentation block:
 **********************************************************************************************************************/
/*!
 * @page PageUSBfCore USB function signal control code
 * @tableofcontents
 * @section usbf_basic USB function core layer - signal control functions
 * @ref USBF_CORE
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
 * @ingroup USBF_CORE RZN1 USB function core layer, signal control functions
 * @{
 * @file
 * @brief USBf Basic Driver Core Layer
 * @details Signal control functions
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
#include "platform.h"
#include "log_serial_io.h"
#include "r_usbf_basic_rzn1_if.h"
#include "r_usb_common.h"
#include "r_usb_cdefusbip.h"
#include "r_usbf_core.h"
#include "r_usbf_hal.h"
#include "r_usbf_driver.h"
#include "r_usb_rzn1_reg_defs.h"
#include "r_timer_rzn1_if.h"

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Static variables and functions
 **********************************************************************************************************************/
uint8_t dbg_count = 0;

static void usb_pstd_SetConfiguration0(void);
static void usb_pstd_SetInterface0(void);
static void usb_pstd_GetStatus1(void);
static void usb_pstd_GetDescriptor1(void);
static void usb_pstd_GetConfiguration1();
static void usb_pstd_GetInterface1();
static void usb_pstd_SetDescriptor2();
static void usb_pstd_ClearFeature3(void);
static void usb_pstd_SetFeature3(void);
static void usb_pstd_SetAddress3(void);
static void usb_pstd_SetConfiguration3(void);
static void usb_pstd_SetInterface3(void);
static void usb_pstd_SynchFrame1();

/***********************************************************************************************************************
 * Function Name :   R_USBCORE_Init
 **********************************************************************************************************************/
/*!
 * @brief    Initilaises USB Core layer
 * @details
 * @param    void
 * @retval   USB error status
 **********************************************************************************************************************/
USB_ERR R_USBCORE_Init(void)
{
    USB_ERR ret_val = ER_OK;

    /*Initialise USB HAL*/
    ret_val = R_USBHAL_Init();

    return (ret_val);
}
/***********************************************************************************************************************
 End of function R_USBCORE_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Renesas Abstracted Peripheral signal control functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_BusReset
 **********************************************************************************************************************/
/*!
 * @brief    Initilaises USB Core layer
 * @details  A USB bus reset was issued by the host. Execute relevant processing
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_BusReset(void)
{
    uint16_t connect_info;

    /* Memory clear */
    usb_pstd_ClearMem();
    Delay_usec(10000); /* Delay 10 msecs to allow bus speed to be detected correctly before the config descriptor is sent */
    connect_info = usb_cstd_PortSpeed();
    /* Callback */
    (*usb_gpstd_Driver.devdefault)(connect_info);
    /* DCP maxpacket size register (0x5E) */
    /*** RZ/T1  usb_creg_write_dcpmxps(usb_gpstd_Driver.devicetbl[USB_DEV_MAX_PKT_SIZE]);  ***/
}
/***********************************************************************************************************************
 End of function usb_pstd_BusReset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_InitConnect
 **********************************************************************************************************************/
/*!
 * @brief    Initilaises USB Core layer
 * @details  Set up interrupts and initialise
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_InitConnect(void)
{
    uint16_t connect_info;
    uint16_t i;

    for (i = USB_PIPE0; i <= USB_MAX_PIPE_NO; i++)
    {
        usb_gpstd_StallPipe[i] = USB_FALSE;
        usb_gcstd_Pipe[i] = (USB_UTR_t*) USB_NULL;
    }

    connect_info = usb_pstd_ChkVbsts();
    switch (connect_info)
    {
    /* Attach host controller */
    case USB_ATTACH:
        usb_pstd_AttachProcess();
        break;
        /* Detach host controller */
    case USB_DETACH:
        usb_pstd_DetachProcess();
        break;
    default:
        break;
    }
    check_vbus_level = false; /* reset VBUS check flag */

    /* Enable interrupts for initial connection */
    enable_usbf_ahb_epc_isr(); /* AHB-EPC bridge interrupts */
    enable_usbf_epc_isr(); /* USB interrupts */
    enable_usbf_epc_ep0_isr(); /* EP0 interrupts */
}
/***********************************************************************************************************************
 End of function usb_pstd_InitConnect
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_AttachProcess
 **********************************************************************************************************************/
/*!
 * @brief
 * @details  USB attach following cable connect
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_AttachProcess(void)
{
    uint32_t control_reg;

    /*sample_app_printf("\nAP");    */
    /* Delay about 10-20ms (to stabilise VBUS.) */
    Delay_usec(15000); /* Delay 15 msecs */

    /*b_pstd_BusReset();    */

    /* Reset HAL */
    R_USBHAL_Reset();

    /* Connect and D+ PullUp to signal full speed mode */
    control_reg =
            ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.LONG;
    control_reg &= (~EPC_USB_CONTROL_CONNECTB_BIT); /* Clear CONNECTB to Enable the USB signal sent to the UTMI-PHY block(and then to the SIE block) */
    control_reg |= EPC_USB_CONTROL_PUE2_BIT; /* Pull-up enable - Pull up the D+ signal */
    control_reg |= EPC_USB_CONTROL_DEFAULT_BIT; /* Set DEFAULT bit to enable endpoint 0 */
    ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.LONG =
            control_reg;
}
/***********************************************************************************************************************
 End of function usb_pstd_AttachProcess
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_DetachProcess
 **********************************************************************************************************************/
/*!
 * @brief
 * @details  USB detach following cable dis-connect
 * @details  call the callback function to complete the detach
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_DetachProcess(void)
{
    uint16_t i;
    uint16_t conf;
    uint16_t *tbl;
    uint32_t control_reg;

    control_reg =
            ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.LONG;
    control_reg |= EPC_USB_CONTROL_CONNECTB_BIT; /* set CONNECTB to disable the USB signal sent to the UTMI-PHY block(and then to the SIE block) */
    control_reg &= (~EPC_USB_CONTROL_PUE2_BIT); /* Pull-up disable */
    control_reg &= (~EPC_USB_CONTROL_DEFAULT_BIT); /* Clear DEFAULT bit to disable endpoint 0 */
    control_reg &= (~EPC_USB_CONTROL_CONF_BIT); /* Disable all endpoints except ep0 */
    ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.LONG =
            control_reg;
    /*sample_app_printf("\nDP");*/
    Delay_usec((uint32_t) 2);

    conf = usb_gpstd_ConfigNum;
    if (conf < (uint16_t) 1)
    {
        /* Address state */
        conf = (uint16_t) 1;
    }
    /* Configuration index */
    usb_gpstd_ConfigNum = 0;
    /* Remote wakeup enable flag */
    usb_gpstd_RemoteWakeup = USB_FALSE;

    tbl = usb_gpstd_Driver.pipetbl[conf - 1];

    /* go through Pipe table for this configuration */
    for (i = 0; USB_PDTBLEND != tbl[i]; i += USB_EPL)
    {
        usb_cstd_ForcedTermination(tbl[i], (uint16_t)USB_DATA_STOP);

        /* Clear configuration for this Pipe */
        usb_cstd_ClrPipeCnfg(tbl[i]);
    }

    /*Reset HAL */
    R_USBHAL_Reset();

    /* Callback */
    (*usb_gpstd_Driver.devdetach)(USB_NO_ARG);
}
/***********************************************************************************************************************
 End of function usb_pstd_DetachProcess
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SuspendProcess
 **********************************************************************************************************************/
/*!
 * @brief
 * @details  Perform a USB peripheral suspend
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_SuspendProcess(void)
{
    /* Suspend Callback */
    (*usb_gpstd_Driver.devsuspend)(usb_gpstd_RemoteWakeup);
}
/***********************************************************************************************************************
 End of function usb_pstd_SuspendProcess
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_ResumeProcess
 **********************************************************************************************************************/
/*!
 * @brief    Set USB registers to implement resume processing
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_ResumeProcess(void)
{
    /* Resume callback */
    (*usb_gpstd_Driver.devresume)(USB_NO_ARG);
}
/***********************************************************************************************************************
 End of function usb_pstd_ResumeProcess
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Renesas Abstracted Peripheral standard request functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_StandReq0
 **********************************************************************************************************************/
/*!
 * @brief    The idle and setup stages of a standard request from host (USB_CS_IDST)
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_StandReq0(void)
{
    switch (usb_gpstd_ReqRequest)
    {
    case USB_CLEAR_FEATURE:
        /* Clear Feature0 */
        break;
    case USB_SET_FEATURE:
        /* Set Feature0 */
        break;
    case USB_SET_ADDRESS:
        /* Set Address0 */
        break;
    case USB_SET_CONFIGURATION:
        /* Set Configuration0 */
        usb_pstd_SetConfiguration0();
        break;
    case USB_SET_INTERFACE:
        /* Set Interface0 */
        usb_pstd_SetInterface0();
        break;
    default:
        break;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_StandReq0
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_StandReq1
 **********************************************************************************************************************/
/*!
 * @brief    The control read data stage of a standard request from host (USB_CS_RDDS)
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_StandReq1(void)
{
    switch (usb_gpstd_ReqRequest)
    {
    case USB_GET_STATUS:
        /* Get Status1 */
        usb_pstd_GetStatus1();
        break;
    case USB_GET_DESCRIPTOR:
        /* Get Descriptor1 */
        usb_pstd_GetDescriptor1();
        break;
    case USB_GET_CONFIGURATION:
        /* Get Configuration1 */
        usb_pstd_GetConfiguration1();
        break;
    case USB_GET_INTERFACE:
        /* Get Interface1 */
        usb_pstd_GetInterface1();
        break;
    case USB_SYNCH_FRAME:
        /* Synch Frame */
        usb_pstd_SynchFrame1();
        break;
    default:
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST;
        break;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_StandReq1
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_StandReq2
 **********************************************************************************************************************/
/*!
 * @brief    The control write data stage of a standard request from host (USB_CS_WRDS)
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_StandReq2(void)
{
    if (USB_SET_DESCRIPTOR == usb_gpstd_ReqRequest)
    {
        /* Set Descriptor2 */
        usb_pstd_SetDescriptor2();
    } else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_StandReq2
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_StandReq3
 **********************************************************************************************************************/
/*!
 * @brief    Standard request process.
 * @details  This is for the status stage of a control write where there is no data stage (USB_CS_WRND)
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_StandReq3(void)
{
    switch (usb_gpstd_ReqRequest)
    {
    case USB_CLEAR_FEATURE:
        /* ClearFeature3 */
        usb_pstd_ClearFeature3();
        break;
    case USB_SET_FEATURE:
        /* SetFeature3 */
        usb_pstd_SetFeature3();
        break;
    case USB_SET_ADDRESS:
        /* SetAddress3 */
        usb_pstd_SetAddress3();
        break;
    case USB_SET_CONFIGURATION:
        /* SetConfiguration3 */
        usb_pstd_SetConfiguration3();
        break;
    case USB_SET_INTERFACE:
        /* SetInterface3 */
        usb_pstd_SetInterface3();
        break;
    default:
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0();
        break;
    }
    /* Control transfer stop(end) */
    usb_pstd_ControlEnd((uint16_t)USB_CTRL_END);
}
/***********************************************************************************************************************
 End of function usb_pstd_StandReq3
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_StandReq4
 **********************************************************************************************************************/
/*!
 * @brief    Standard request process.
 * @details  The control read status stage of a standard request from host (USB_CS_RDSS)
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_StandReq4(void)
{
    switch (usb_gpstd_ReqRequest)
    {
    case USB_GET_STATUS:
    case USB_GET_DESCRIPTOR:
    case USB_GET_CONFIGURATION:
    case USB_GET_INTERFACE:
    case USB_SYNCH_FRAME:
        /*usb_cstd_SetBuf( (uint16_t)USB_PIPE0);*/
        break;
    default:
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0();
        break;
    }

    /* Control transfer stop(end) */
    usb_pstd_ControlEnd((uint16_t)USB_CTRL_END);
}
/***********************************************************************************************************************
 End of function usb_pstd_StandReq4
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_StandReq5
 **********************************************************************************************************************/
/*!
 * @brief    Standard request process.
 * @details  The control write status stage of a standard request from host (USB_CS_WRSS)
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_StandReq5(void)
{
    if (USB_SET_DESCRIPTOR == usb_gpstd_ReqRequest)
    {
        /* Set pipe PID_BUF */
        /*usb_cstd_SetBuf( (uint16_t)USB_PIPE0);*/
        ;
    } else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0();
    }

    /* Control transfer stop(end) */
    usb_pstd_ControlEnd((uint16_t)USB_CTRL_END);
}
/***********************************************************************************************************************
 End of function usb_pstd_StandReq5
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetConfiguration0
 **********************************************************************************************************************/
/*!
 * @brief    notify the reception of SetConfiguration command
 * @details  (idle/setup stage)
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_SetConfiguration0(void)
{
    uint16_t config_num;

    config_num = usb_gpstd_ConfigNum;

    /* Configuration number set */
    usb_pstd_SetConfigNum(usb_gpstd_ReqValue);

    if (usb_gpstd_ReqValue && (usb_gpstd_ReqValue != config_num))
    {
        /* Registration open function call */
        (*usb_gpstd_Driver.devconfig)(usb_gpstd_ConfigNum);
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_SetConfiguration0
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetInterface0
 **********************************************************************************************************************/
/*!
 * @brief    notify reception of SetInterface command
 * @details  (idle/setup stage)
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void usb_pstd_SetInterface0(void)
{
    /* Interfaced change function call */
    (*usb_gpstd_Driver.interface)(usb_gpstd_AltNum[usb_gpstd_ReqIndex]);
}
/***********************************************************************************************************************
 End of function usb_pstd_SetInterface0
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_GetStatus1
 **********************************************************************************************************************/
/*!
 * @brief    Analyze a Get Status command and process it
 * @details  (for control read data stage)
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_GetStatus1(void)
{
    static uint8_t tbl[4]; /* 32-bit alignment */
    uint16_t ep;
    uint16_t pipe;

    if ((0 == usb_gpstd_ReqValue) && (2 == usb_gpstd_ReqLength))
    {
        tbl[0] = 0;
        tbl[1] = 0;
        /* Check request type */
        switch (usb_gpstd_ReqTypeRecip)
        {
        case USB_DEVICE:
            if (0 == usb_gpstd_ReqIndex)
            {
                /* Self powered / Bus powered */
                tbl[0] = usb_pstd_GetCurrentPower();
                /* Support remote wakeup ? */
                if (USB_TRUE == usb_gpstd_RemoteWakeup)
                {
                    tbl[0] |= USB_GS_REMOTEWAKEUP;
                }
                /* Control read */
                usb_pstd_ControlRead((uint32_t) 2, tbl);
            } else
            {
                /* Request error */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
            break;
        case USB_INTERFACE:
            if (usb_pstd_ChkConfigured() == USB_TRUE)
            {
                if (usb_gpstd_ReqIndex
                        < usb_pstd_GetInterfaceNum(usb_gpstd_ConfigNum))
                {
                    /* Control read start */
                    usb_pstd_ControlRead((uint32_t) 2, tbl);
                } else
                {
                    /* Request error (not exist interface) */
                    usb_pstd_SetStallPipe0();
                    usbf_eps[USB_EP0].state = USB_CS_IDST;
                }
            } else
            {
                /* Request error */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
            break;
        case USB_ENDPOINT:
            /* Endpoint number */
            ep = (uint16_t)(usb_gpstd_ReqIndex & USB_EPNUMFIELD);
            /* Endpoint 0 */
            if ( USB_EP0 == 0)
            {
                if (USB_TRUE == usb_gpstd_StallPipe[USB_PIPE0])
                {
                    /* Halt set */
                    tbl[0] = USB_GS_HALT;
                }
                /* Control read start */
                usb_pstd_ControlRead((uint32_t) 2, tbl);
            }
            /* EP1 to max */
            else if (ep <= USB_MAX_EP_NO)
            {
                if (usb_pstd_ChkConfigured() == USB_TRUE)
                {
                    pipe = usb_cstd_Epadr2Pipe(usb_gpstd_ReqIndex);
                    if ( USB_ERROR == pipe)
                    {
                        /* Set pipe USB_PID_STALL */
                        usb_pstd_SetStallPipe0();
                        usbf_eps[USB_EP0].state = USB_CS_IDST;
                    } else
                    {
                        if (USB_TRUE == usb_gpstd_StallPipe[pipe])
                        {
                            /* Halt set */
                            tbl[0] = USB_GS_HALT;
                        }

                        /* Control read start */
                        usb_pstd_ControlRead((uint32_t) 2, tbl);
                    }
                } else
                {
                    /* Set pipe USB_PID_STALL */
                    usb_pstd_SetStallPipe0();
                    usbf_eps[USB_EP0].state = USB_CS_IDST;
                }
            } else
            {
                /* Set pipe USB_PID_STALL */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
            break;
        default:
            /* Set pipe USB_PID_STALL */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
            break;
        }
    } else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_GetStatus1
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_GetDescriptor1
 **********************************************************************************************************************/
/*!
 * @brief    Analyze a Get Descriptor command and process it
 * @details  (for control read data stage)
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_GetDescriptor1(void)
{
    uint16_t len;
    uint16_t idx;
    uint8_t *table;

    if (USB_DEVICE == usb_gpstd_ReqTypeRecip)
    {
        idx = (uint16_t)(usb_gpstd_ReqValue & USB_DT_INDEX);
        switch ((uint16_t)USB_GET_DT_TYPE(usb_gpstd_ReqValue))
        {
        /*---- Device descriptor ----*/
        case USB_DT_DEVICE:
            if (((uint16_t) 0 == usb_gpstd_ReqIndex) && ((uint16_t) 0 == idx))
            {
                table = usb_gpstd_Driver.devicetbl;

                if (usb_gpstd_ReqLength < table[0])
                {
                    /* Control read start */
                    usb_pstd_ControlRead((uint32_t) usb_gpstd_ReqLength, table);
                } else
                {
                    /* Control read start */
                    usb_pstd_ControlRead((uint32_t) table[0], table);
                }
            } else
            {
                /* Request error */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
            break;
            /*---- Configuration descriptor ----*/
        case USB_DT_CONFIGURATION:
            if ((0 == usb_gpstd_ReqIndex) && ((uint16_t) 0 == idx))
            {
                table = usb_gpstd_Driver.configtbl[idx];
                len = (uint16_t)(*(uint8_t*) ((uint32_t) table + (uint32_t) 3));
                len = (uint16_t)(len << 8);
                len += (uint16_t)(
                        *(uint8_t*) ((uint32_t) table + (uint32_t) 2));
                /* Descriptor > wLength */
                if (usb_gpstd_ReqLength < len)
                {
                    /* Control read start */
                    usb_pstd_ControlRead((uint32_t) usb_gpstd_ReqLength, table);
                } else
                {
                    /* Control read start */
                    usb_pstd_ControlRead((uint32_t) len, table);
                }
            } else
            {
                /* Request error */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
            break;
            /*---- String descriptor ----*/
        case USB_DT_STRING:
            if (idx < USB_STRINGNUM)
            {
                table = usb_gpstd_Driver.stringtbl[idx];
                len = (uint16_t)(*(uint8_t*) ((uint32_t) table + (uint32_t) 0));
                if (usb_gpstd_ReqLength < len)
                {
                    /* Control read start */
                    usb_pstd_ControlRead((uint32_t) usb_gpstd_ReqLength, table);
                } else
                {
                    /* Control read start */
                    usb_pstd_ControlRead((uint32_t) len, table);
                }
            } else
            {
                /* Request error */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
            break;
            /*---- Interface descriptor ----*/
        case USB_DT_INTERFACE:
            /* Set pipe USB_PID_STALL */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
            break;
            /*---- Endpoint descriptor ----*/
        case USB_DT_ENDPOINT:
            /* Set pipe USB_PID_STALL */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
            break;
        case USB_DT_DEVICE_QUALIFIER:
            if ((0 == usb_gpstd_ReqIndex) && (0 == idx))
            {
                table = usb_gpstd_Driver.qualitbl;
                if (usb_gpstd_ReqLength < table[0])
                {
                    /* Control read start */
                    usb_pstd_ControlRead((uint32_t) usb_gpstd_ReqLength, table);
                } else
                {
                    /* Control read start */
                    usb_pstd_ControlRead((uint32_t) table[0], table);
                }
            } else
            {
                /* Request error */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
            break;
        case USB_DT_OTHER_SPEED_CONF:
            if ((0 == usb_gpstd_ReqIndex) && (0 == idx))
            {
                table = usb_gpstd_Driver.othertbl[idx];
                len = (uint16_t)(*(uint8_t*) ((uint32_t) table + (uint32_t) 3));
                len = (uint16_t)(len << 8);
                len += (uint16_t)(
                        *(uint8_t*) ((uint32_t) table + (uint32_t) 2));
                /* Descriptor > wLength */
                if (usb_gpstd_ReqLength < len)
                {
                    /* Control read start */
                    usb_pstd_ControlRead((uint32_t) usb_gpstd_ReqLength, table);
                } else
                {
                    /* Control read start */
                    usb_pstd_ControlRead((uint32_t) len, table);
                }
            } else
            {
                /* Request error */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
            break;
        case USB_DT_INTERFACE_POWER:
            /* Not support */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
            break;
        default:
            /* Set pipe USB_PID_STALL */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
            break;
        }
    } else if (USB_INTERFACE == usb_gpstd_ReqTypeRecip)
    {
        usb_gpstd_ReqReg.ReqType = usb_gpstd_ReqType;
        usb_gpstd_ReqReg.ReqTypeType = usb_gpstd_ReqTypeType;
        usb_gpstd_ReqReg.ReqTypeRecip = usb_gpstd_ReqTypeRecip;
        usb_gpstd_ReqReg.ReqRequest = usb_gpstd_ReqRequest;
        usb_gpstd_ReqReg.ReqValue = usb_gpstd_ReqValue;
        usb_gpstd_ReqReg.ReqIndex = usb_gpstd_ReqIndex;
        usb_gpstd_ReqReg.ReqLength = usb_gpstd_ReqLength;
        (*usb_gpstd_Driver.ctrltrans)((USB_REQUEST_t *) &usb_gpstd_ReqReg,
                (uint16_t)USB_NO_ARG);
    } else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_GetDescriptor1
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_GetConfiguration1
 **********************************************************************************************************************/
/*!
 * @brief    Analyze a Get Configuration command and process it
 * @details  (for control read data stage)
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_GetConfiguration1(void)
{
    static uint8_t tbl[4]; /* only 1 byte required but align buffer on uint32_t boundary */

    /* check request */
    if ((((USB_DEVICE == usb_gpstd_ReqTypeRecip) && (0 == usb_gpstd_ReqValue))
            && (0 == usb_gpstd_ReqIndex)) && (1 == usb_gpstd_ReqLength))
    {
        tbl[0] = (uint8_t) usb_gpstd_ConfigNum;
        /* Control read start */
        usb_pstd_ControlRead((uint32_t) 1, tbl);
    } else
    {
        /* Set pipe USB_PID_STALL */
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_GetConfiguration1
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_GetInterface1
 **********************************************************************************************************************/
/*!
 * @brief    Analyze a Get Interface command and process it
 * @details  (for control read data stage)
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_GetInterface1(void)
{
    static uint8_t tbl[2];

    /* check request */
    if (((USB_INTERFACE == usb_gpstd_ReqTypeRecip) && (0 == usb_gpstd_ReqValue))
            && (1 == usb_gpstd_ReqLength))
    {
        if (usb_gpstd_ReqIndex < USB_ALT_NO)
        {
            tbl[0] = (uint8_t) usb_gpstd_AltNum[usb_gpstd_ReqIndex];
            /* Start control read */
            usb_pstd_ControlRead((uint32_t) 1, tbl);
        } else
        {
            /* Request error */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
        }
    } else
    {
        /* Request error */
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_GetInterface1
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetDescriptor2
 **********************************************************************************************************************/
/*!
 * @brief    Return STALL in response to a Set Descriptor command
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_SetDescriptor2(void)
{
    /* Not specification */
    usb_pstd_SetStallPipe0();
    usbf_eps[USB_EP0].state = USB_CS_IDST;
}
/***********************************************************************************************************************
 End of function usb_pstd_SetDescriptor2
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_ClearFeature3
 **********************************************************************************************************************/
/*!
 * @brief    Analyze a Clear Feature command and process it
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_ClearFeature3(void)
{
    uint16_t pipe;
    uint16_t ep;

    if (0 == usb_gpstd_ReqLength)
    {
        /* check request type */
        switch (usb_gpstd_ReqTypeRecip)
        {
        case USB_DEVICE:
            if ((USB_DEV_REMOTE_WAKEUP == usb_gpstd_ReqValue)
                    && (0 == usb_gpstd_ReqIndex))
            {
                if (usb_pstd_ChkRemote() == USB_TRUE)
                {
                    usb_gpstd_RemoteWakeup = USB_FALSE;
                    /* Set pipe PID_BUF */
                    /*usb_cstd_SetBuf( (uint16_t)USB_PIPE0);*/
                } else
                {
                    /* Not support remote wakeup */
                    /* Request error */
                    usb_pstd_SetStallPipe0();
                    usbf_eps[USB_EP0].state = USB_CS_IDST;
                }
            } else
            {
                /* Not specification */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
            break;
        case USB_INTERFACE:
            /* Request error */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
            break;
        case USB_ENDPOINT:
            /* Endpoint number */
            ep = (uint16_t)(usb_gpstd_ReqIndex & USB_EPNUMFIELD);
            if (USB_ENDPOINT_HALT == usb_gpstd_ReqValue)
            {
                /* EP0 */
                if ( USB_EP0 == ep)
                {
                    /* Stall clear */
                    usb_cstd_ClrStall_EP0();
                    /* Set pipe PID_BUF */
                }
                /* EP1 to max */
                else if (ep <= USB_MAX_EP_NO)
                {
                    pipe = usb_cstd_Epadr2Pipe(usb_gpstd_ReqIndex);
                    if ((USB_ERROR == pipe) || (9 < pipe))
                    {
                        /* Request error */
                        usb_pstd_SetStallPipe0();
                        usbf_eps[USB_EP0].state = USB_CS_IDST;
                    } else
                    {
                        usbf_eps[ep].pipe = pipe;
                        if (USB_TRUE == usb_gpstd_StallPipe[pipe])
                        {
                            usb_gpstd_StallPipe[pipe] = USB_FALSE;
                            (*usb_gpstd_StallCB)(USB_NULL);
                        }
                    }
                } else
                {
                    /* Request error */
                    usb_pstd_SetStallPipe0();
                    usbf_eps[USB_EP0].state = USB_CS_IDST;
                }
            } else
            {
                /* Request error */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
            break;
        default:
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
            break;
        }
    } else
    {
        /* Not specification */
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_ClearFeature3
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetFeature3
 **********************************************************************************************************************/
/*!
 * @brief    Analyze a Set Feature command and process it
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_SetFeature3(void)
{
    uint16_t pipe;
    uint16_t ep;

    if (0 == usb_gpstd_ReqLength)
    {
        /* check request type */
        switch (usb_gpstd_ReqTypeRecip)
        {
        case USB_DEVICE:
            switch (usb_gpstd_ReqValue)
            {
            case USB_DEV_REMOTE_WAKEUP:
                if (0 == usb_gpstd_ReqIndex)
                {
                    if (usb_pstd_ChkRemote() == USB_TRUE)
                    {
                        usb_gpstd_RemoteWakeup = USB_TRUE;
                    } else
                    {
                        /* Not support remote wakeup */
                        /* Request error */
                        usb_pstd_SetStallPipe0();
                        usbf_eps[USB_EP0].state = USB_CS_IDST;
                    }
                } else
                {
                    /* Not specification */
                    usb_pstd_SetStallPipe0();
                    usbf_eps[USB_EP0].state = USB_CS_IDST;
                }
                break;
            default:
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
                break;
            }
            break;
        case USB_INTERFACE:
            /* Set pipe USB_PID_STALL */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
            break;
        case USB_ENDPOINT:
            /* Endpoint number */
            ep = (uint16_t)(usb_gpstd_ReqIndex & USB_EPNUMFIELD);
            if (USB_ENDPOINT_HALT == usb_gpstd_ReqValue)
            {
                /* EP1 to max */
                if (ep > 0)
                {
                    if (ep <= USB_MAX_EP_NO)
                    {
                        pipe = usb_cstd_Epadr2Pipe(usb_gpstd_ReqIndex);
                        if ( USB_ERROR == pipe)
                        {
                            /* Request error */
                            usb_pstd_SetStallPipe0();
                            usbf_eps[USB_EP0].state = USB_CS_IDST; /* Reset EP0 control transfer state */
                        } else
                        {
                            usbf_eps[ep].pipe = pipe; /* should already be set at initialisation */
                            /* Set pipe USB_PID_STALL */
                            usb_pstd_SetOStall(pipe);
                        }
                    } else
                    {
                        /* Request error */
                        usb_pstd_SetStallPipe0();
                        usbf_eps[USB_EP0].state = USB_CS_IDST;
                    }
                }
            } else
            {
                /* Not specification */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
            break;

        default:
            /* Request error */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
            break;
        }
    } else
    {
        /* Request error */
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_SetFeature3
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetAddress3
 **********************************************************************************************************************/
/*!
 * @brief    Analyze a Set Address command and process it
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_SetAddress3(void)
{
    if (USB_DEVICE == usb_gpstd_ReqTypeRecip)
    {
        if ((0 == usb_gpstd_ReqIndex) && (0 == usb_gpstd_ReqLength))
        {
            if (usb_gpstd_ReqValue <= 127)
            {
                /* Set Address */
                ((volatile EPC_USB_ADDRESS_Type *) USBFUNC_USB_EPC_ADDRESS_ADDRESS)->USB_ADDRESS.BIT.USB_ADDR =
                        usb_gpstd_ReqValue;
            } else
            {
                /* Not specification */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
        } else
        {
            /* Not specification */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
        }
    } else
    {
        /* Request error */
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_SetAddress3
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetConfiguration3
 **********************************************************************************************************************/
/*!
 * @brief    Analyze a Set Configuration command and process it
 * @details  (for status stage of a control write where there is no data stage)
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_SetConfiguration3(void)
{
    uint16_t i;
    uint16_t j;
    uint16_t ifc;
    uint16_t cfgnum;
    uint16_t cfgok;
    uint16_t *table;
    uint8_t *table2;

    if (USB_DEVICE == usb_gpstd_ReqTypeRecip)
    {
        cfgnum = usb_pstd_GetConfigNum(); /* get max number of configurations */
        cfgok = USB_ERROR;

        for (j = 0; j < cfgnum; j++)
        {
            table2 = usb_gpstd_Driver.configtbl[j];

            if ((((usb_gpstd_ReqValue == table2[5]) || (0 == usb_gpstd_ReqValue))
                    && (0 == usb_gpstd_ReqIndex)) && (0 == usb_gpstd_ReqLength))
            {
                cfgok = USB_OK;

                if ((usb_gpstd_ReqValue > 0)
                        && (usb_gpstd_ReqValue != usb_gpstd_ConfigNum))
                {
                    usb_pstd_ClearEpTblIndex();
                    ifc = usb_pstd_GetInterfaceNum(usb_gpstd_ReqValue);
                    for (i = 0; i < ifc; ++i)
                    {
                        /* Pipe Information Table ("endpoint table") initialize */
                        usb_pstd_SetEpTblIndex(usb_gpstd_ReqValue, i,
                                (uint16_t) 0);
                    }
                    table = usb_gpstd_Driver.pipetbl[usb_gpstd_ReqValue - 1];
                    /* Clear pipe configuration register */
                    usb_pstd_SetPipeRegister((uint16_t)USB_CLRPIPE, table);
                    /* Set pipe configuration register */
                    usb_pstd_SetPipeRegister((uint16_t)USB_PERIPIPE, table);
                }
                break;
            }
        }
        if (USB_ERROR == cfgok)
        {
            /* Request error */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
        }
    } else
    {
        /* Request error */
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST;
    }
}

/***********************************************************************************************************************
 End of function usb_pstd_SetConfiguration3
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_SetInterface3
 **********************************************************************************************************************/
/*!
 * @brief    Analyze a Set Interface command and process it
 * @details  (for status stage of a control write where there is no data stage)
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
static void usb_pstd_SetInterface3(void)
{
    uint16_t *table;
    uint16_t conf;

    conf = usb_gpstd_ConfigNum;
    if (conf < (uint16_t) 1)
    {
        /* Address state */
        conf = (uint16_t) 1;
    }

    /* Configured ? */
    if ((usb_pstd_ChkConfigured() == USB_TRUE)
            && (USB_INTERFACE == usb_gpstd_ReqTypeRecip))
    {
        if ((usb_gpstd_ReqIndex <= usb_pstd_GetInterfaceNum(usb_gpstd_ConfigNum))
                && (0 == usb_gpstd_ReqLength))
        {
            if (usb_gpstd_ReqValue
                    <= usb_pstd_GetAlternateNum(usb_gpstd_ConfigNum,
                            usb_gpstd_ReqIndex))
            {
                usb_gpstd_AltNum[usb_gpstd_ReqIndex] = (uint16_t)(
                        usb_gpstd_ReqValue & USB_ALT_SET);
                /*usb_cstd_SetBuf( (uint16_t)USB_PIPE0);*/
                usb_pstd_ClearEpTblIndex();
                /* Search endpoint setting */
                usb_pstd_SetEpTblIndex(usb_gpstd_ConfigNum, usb_gpstd_ReqIndex,
                        usb_gpstd_AltNum[usb_gpstd_ReqIndex]);
                table = usb_gpstd_Driver.pipetbl[conf - 1];
                /* Set pipe configuration register */
                usb_pstd_SetPipeRegister((uint16_t)USB_PERIPIPE, table);
            } else
            {
                /* Request error */
                usb_pstd_SetStallPipe0();
                usbf_eps[USB_EP0].state = USB_CS_IDST;
            }
        } else
        {
            /* Request error */
            usb_pstd_SetStallPipe0();
            usbf_eps[USB_EP0].state = USB_CS_IDST;
        }
    } else
    {
        /* Request error */
        usb_pstd_SetStallPipe0();
        usbf_eps[USB_EP0].state = USB_CS_IDST;
    }
}
/***********************************************************************************************************************
 End of function usb_pstd_SetInterface3
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_pstd_SynchFrame1
 *
 *  Description:    Return STALL response to SynchFrame command.
 *
 *  Parameters:     None
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
static void usb_pstd_SynchFrame1(void)
{
    /* Set pipe USB_PID_STALL */
    usb_pstd_SetStallPipe0();
    usbf_eps[USB_EP0].state = USB_CS_IDST;
}
/***********************************************************************************************************************
 End of function usb_pstd_SynchFrame1
 **********************************************************************************************************************/

/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
