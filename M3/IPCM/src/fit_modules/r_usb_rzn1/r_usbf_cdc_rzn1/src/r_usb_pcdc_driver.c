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
 * FILE         :  r_usb_pcdc_driver.c
 * Description  :  USB PCDC Driver code
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_usbf_basic_rzn1_if.h"
#include "r_usb_pcdc_if.h"
#include "r_usb_pcdc_local.h"
#include "r_usb_common.h"
#include "r_usb_cdefusbip.h"

/***********************************************************************************************************************
 Constant macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
/* PCDC <--> USB massage */
USB_UTR_t usb_gpcdc_Mess[10];
/* Line Coding data */
USB_PCDC_LineCoding_t usb_gcdc_LineCoding = {.bDataBits=8, .dwDTERate=115200};
/* Control Line Status data */
USB_PCDC_ControlLineState_t usb_gcdc_ControlLineState;

USB_ER_t usb_pcdc_UserDataTrans(uint16_t pipe, uint32_t size, uint8_t *table,
        USB_UTR_CB_t complete);
void usb_pcdc_ControlTrans_idst(USB_REQUEST_t *req);
void usb_pcdc_ControlTrans_rdds(USB_REQUEST_t *req);
void usb_pcdc_ControlTrans_wrds(USB_REQUEST_t *req);
void usb_pcdc_ControlTrans_wrnd(USB_REQUEST_t *req);
void usb_pcdc_ControlTrans_rdss(USB_REQUEST_t *req);
void usb_pcdc_ControlTrans_wrss(USB_REQUEST_t *req);
void usb_pcdc_SetControlLineState(void);
void usb_pcdc_SetLineCoding(void);
void usb_pcdc_GetLineCoding(void);

/***********************************************************************************************************************
 Renesas Abstracted Peripheral Communications Devices Class Driver API functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_pcdc_DataTrans
 *
 *  Description:    Transfer data from USB
 *
 *  Parameters:     size - Data Size
 *                  *table - Data address
 *                  complete - Callback function
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void usb_pcdc_DataTrans(uint16_t pipe, uint32_t size, uint8_t *table, USB_UTR_CB_t complete)
{
    /* PIPE Transfer set */
    usb_gpcdc_Mess[pipe].keyword = pipe; /* Pipe No */
    usb_gpcdc_Mess[pipe].tranadr = table; /* Data address */
    usb_gpcdc_Mess[pipe].tranlen = size; /* Data Size */
    usb_gpcdc_Mess[pipe].complete = complete; /* Callback function */

    R_usb_pstd_TransferStart(&usb_gpcdc_Mess[pipe]); /* USB Transfer Start */
}
/***********************************************************************************************************************
 End of function usb_pcdc_DataTrans
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_pcdc_ControlTrans_idst
 *
 *  Description:    Class request processing(idle or setup stage)
 *
 *  Parameters:     *req - Pointer to Class request information
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void usb_pcdc_ControlTrans_idst(USB_REQUEST_t *req)
{
    ;
}
/***********************************************************************************************************************
 End of function usb_pcdc_ControlTrans_idst
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_pcdc_ControlTrans_rdds
 *
 *  Description:    Class request processing (control read)
 *
 *  Parameters:     *req - Pointer to Class request information
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void usb_pcdc_ControlTrans_rdds(USB_REQUEST_t *req)
{
    /* Is a request receive target Interface? */
    if ((0 == req->ReqIndex) && (USB_INTERFACE == req->ReqTypeRecip))
    {
        /* Is a Request Type GetLineCoding? */
        if (USB_PCDC_GET_LINE_CODING == req->ReqRequest)
        {
            /* send get_line_coding */
            R_usb_pstd_ControlRead(USB_PCDC_GET_LINE_CODING_LENGTH,
                    (uint8_t *) &usb_gcdc_LineCoding);
        } else
        {
            /* Set Stall */
            R_usb_pstd_SetPipeStall(USB_PIPE0); /* Req Error */
        }
    } else
    {
        /* Set Stall */
        R_usb_pstd_SetPipeStall(USB_PIPE0); /* Req Error */
    }
}
/***********************************************************************************************************************
 End of function usb_pcdc_ControlTrans_rdds
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_pcdc_ControlTrans_wrnd
 *
 *  Description:    Class request processing(control no data write)
 *
 *  Parameters:     *req - Pointer to Class request information
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void usb_pcdc_ControlTrans_wrnd(USB_REQUEST_t *req)
{
    /* Is a request receive target Interface? */
    if ((0 == req->ReqIndex) && (USB_INTERFACE == req->ReqTypeRecip))
    {
        /* Is a Request Type SetControlLineState? */
        if (USB_PCDC_SET_CONTROL_LINE_STATE == req->ReqRequest)
        {
            /* DTR & RTS set value store */
            *(uint16_t *) &usb_gcdc_ControlLineState = req->ReqValue;
            /* send Set_Control_Line_State */
            usb_pcdc_SetControlLineState();
        } else
        {
            /* Set Stall */
            R_usb_pstd_SetPipeStall(USB_PIPE0); /* Req Error */
        }
    } else
    {
        /* Set Stall */
        R_usb_pstd_SetPipeStall(USB_PIPE0); /* Req Error */
    }
    if (0 != req->ReqRequest)
    {
        R_usb_pstd_ControlEnd((uint16_t)USB_CTRL_END);
    }
}
/***********************************************************************************************************************
 End of function usb_pcdc_ControlTrans_wrnd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_pcdc_ControlTrans_wrds
 *
 *  Description:    Class request processing (control write data stage)
 *
 *  Parameters:     *req - Pointer to Class request information
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void usb_pcdc_ControlTrans_wrds(USB_REQUEST_t *req)
{
    /* Is a request receive target Interface? */
    if ((0 == req->ReqIndex) && (USB_INTERFACE == req->ReqTypeRecip))
    {
        /* Is a Request Type SetLineCoding? */
        if (USB_PCDC_SET_LINE_CODING == req->ReqRequest)
        {
            /* send Set_Line_Coding */
            R_usb_pstd_ControlWrite(7, (uint8_t *) &usb_gcdc_LineCoding);
        } else
        {
            /* Set Stall */
            R_usb_pstd_SetPipeStall(USB_PIPE0); /* Req Error */
        }
    } else
    {
        /* Set Stall */
        R_usb_pstd_SetPipeStall(USB_PIPE0); /* Req Error */
    }
}
/***********************************************************************************************************************
 End of function usb_pcdc_ControlTrans_wrds
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_pcdc_ControlTrans_rdss
 *
 *  Description:    Class request processing (control read status stage)
 *
 *  Parameters:     *req - Pointer to Class request information
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void usb_pcdc_ControlTrans_rdss(USB_REQUEST_t *req)
{
    /* Is a Request Type GetLineCoding? */
    if (USB_PCDC_GET_LINE_CODING == req->ReqRequest)
    {
        /* Get Line Coding Request */
        usb_pcdc_GetLineCoding();
    } else
    {
        /* Set Stall */
        R_usb_pstd_SetPipeStall(USB_PIPE0); /* Req Error */
    }
    R_usb_pstd_ControlEnd((uint16_t)USB_CTRL_END);
}
/***********************************************************************************************************************
 End of function usb_pcdc_ControlTrans_rdss
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_pcdc_ControlTrans_wrss
 *
 *  Description:    Process class request (control write status stage)
 *
 *  Parameters:     *req - Pointer to Class request information
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void usb_pcdc_ControlTrans_wrss(USB_REQUEST_t *req)
{
    /* Is a request receive target Interface? */
    if ((0 == req->ReqIndex) && (USB_INTERFACE == req->ReqTypeRecip))
    {
        /* Is a Request Type SetLineCoding? */
        if (USB_PCDC_SET_LINE_CODING == req->ReqRequest)
        {
            /* send Set_Line_Coding */
            usb_pcdc_SetLineCoding();
        } else
        {
            /* Set Stall */
            R_usb_pstd_SetPipeStall(USB_PIPE0); /* Req Error */
        }
    } else
    {
        /* Set Stall */
        R_usb_pstd_SetPipeStall(USB_PIPE0); /* Req Error */
    }
    R_usb_pstd_ControlEnd((uint16_t)USB_CTRL_END);
}
/***********************************************************************************************************************
 End of function usb_pcdc_ControlTrans_wrss
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_pcdc_SetControlLineState
 *
 *  Description:    Peripheral Set Control Line State request
 *
 *  Parameters:     None
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void usb_pcdc_SetControlLineState(void)
{
    /* RS-232 signal RTS & DTR Set */
    /* If RTS/DTR control function is prepared, calls this function here */
    ;
}
/***********************************************************************************************************************
 End of function usb_pcdc_SetControlLineState
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_pcdc_SetLineCoding
 *
 *  Description:    Peripheral Set Line Coding request
 *
 *  Parameters:     None
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void usb_pcdc_SetLineCoding(void)
{
    ;
}
/***********************************************************************************************************************
 End of function usb_pcdc_SetLineCoding
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_pcdc_GetLineCoding
 *
 *  Description:    Peripheral Get Line Coding request
 *
 *  Parameters:     None
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void usb_pcdc_GetLineCoding(void)
{
    ;
}
/***********************************************************************************************************************
 End of function usb_pcdc_GetLineCoding
 **********************************************************************************************************************/

/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
