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
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hcdc_api.c
 * Description  :  USB host CDC Driver API
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_usb_hcdc_if.h"
#include "r_usb_hcdc_local.h"

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Renesas USB Host Com Class Driver functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hcdc_task
 *
 *  Description:    Call Host CDC task
 *
 *  Parameters:     none
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void R_usb_hcdc_task(void)
{
    /* Host CDC Task call */
    usb_hcdc_task();
}
/***********************************************************************************************************************
 End of function R_usb_hcdc_task
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hcdc_driver_start
 *
 *  Description:    USB host Initialize process
 *
 *  Parameters:     none
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void R_usb_hcdc_driver_start( void )
{
    /* Set host CDC Task priority */
    R_usb_cstd_SetTaskPri(USB_HCDC_TSK, USB_PRI_4);
}
/***********************************************************************************************************************
 End of function R_usb_hcdc_driver_start
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hcdc_class_check
 *
 *  Description:    class check.
 *
 *  Parameters:     uint16_t **table  : Pointer to data table.
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void R_usb_hcdc_class_check(uint16_t **table)
{
    usb_ghcdc_device_table      = (uint8_t*)(table[0]); /* Set device descriptor address */
    usb_ghcdc_devaddr           = *table[7];            /* Set device address */

    /* Set Pipe Information */
    R_usb_hstd_SetPipe(table);
    /* Class Enumeration Request */
    usb_hcdc_send_message(USB_MSG_CLS_CHECKREQUEST, USB_PIPE0, USB_NULL, 0, USB_NULL);
}
/***********************************************************************************************************************
 End of function R_usb_hcdc_class_check
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hcdc_send_data
 *
 *  Description:    Transfer (send) the USB data of specified size from the specified (table) address.
 *
 *  Parameters:     uint16_t pipe_id          : PipeID
 *                  uint8_t *table            : Send data address
 *                  uint32_t size             : Send data Size
 *                  USB_UTR_CB_t complete     : Callback function
 *
 *  Return value:   USB_ER_t                  : Error info
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hcdc_send_data(uint16_t pipe_id, uint8_t *table, uint32_t size, USB_UTR_CB_t complete )
{
    USB_ER_t    err;

    err = usb_hcdc_send_message(USB_HCDC_TCMD_SEND, pipe_id, table, size, complete);

    return err;
}
/***********************************************************************************************************************
 End of function R_usb_hcdc_send_data
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hcdc_receive_data
 *
 *  Description:    Data receive request for host
 *
 *  Parameters:     uint16_t pipe_id          : PipeID
 *                  uint8_t *table            : Receive data address
 *                  uint32_t size             : Receive data Size
 *                  USB_UTR_CB_t complete     : Callback function
 *
 *  Return value:   USB_ER_t                  : Error info
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hcdc_receive_data( uint16_t pipe_id, uint8_t *table, uint32_t size, USB_UTR_CB_t complete )
{
    USB_ER_t    err;

    err = usb_hcdc_send_message(USB_HCDC_TCMD_RECEIVE, pipe_id, table, size, complete);

    return err;
}
/***********************************************************************************************************************
 End of function R_usb_hcdc_receive_data
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hcdc_get_strings
 *
 *  Description:    Get the CDC device strings
 *                  Note: This function can only be assumed to return the correct data immediatly after device enumeration
 *
 *  Parameters:     None
 *
 *  Return value:   const USB_HCDC_Strings_t *  : The Device strings which shall be valid or NULL
 *
 **********************************************************************************************************************/
const USB_HCDC_Strings_t * R_usb_hcdc_get_strings(void)
{
    return usb_hcdc_get_strings();
}
/***********************************************************************************************************************
 End of function R_usb_hcdc_get_strings
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hcdc_serial_state_trans
 *
 *  Description:    Handle CDC class and serial state info from peripheral.
 *
 *  Parameters:     uint16_t      pipe_id  : PipeID
 *                  uint8_t       *table   : Receive data address
 *                  USB_UTR_CB_t  complete : Callback function
 *
 *  Return value:   USB_ER_t               : Error info
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hcdc_serial_state_trans( uint16_t pipe_id, uint8_t *table, USB_UTR_CB_t complete )
{
    USB_ER_t    err;

    err = usb_hcdc_send_message(USB_HCDC_TCMD_CLASS_NOTIFY, pipe_id, table, USB_HCDC_SERIAL_STATE_MSG_LEN, complete);

    return err;
}
/***********************************************************************************************************************
 End of function R_usb_hcdc_serial_state_trans
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hcdc_set_line_coding
 *
 *  Description:    SetLineCoding (CDC Request)
 *
 *  Parameters:     uint32_t      speed       : Baud rate
 *                  uint8_t       databits    : 7bits or 8bits
 *                  uint8_t       stopbit     : Stop bit
 *                  uint8_t       parity      : Parity
 *                  USB_UTR_CB_t  complete    : Callback function
 *
 *  Return value:   USB_ER_t                  : Error info
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hcdc_set_line_coding( uint16_t devadr, USB_HCDC_LineCoding_t *p_linecoding, USB_UTR_CB_t complete )
{
    USB_ER_t    err;

    usb_ghcdc_cls_req.bRequestCode = USB_HCDC_SET_LINE_CODING;            /* Class request setup packet bRequest Set */
    usb_ghcdc_cls_req.parm.LineCoding = p_linecoding;                     /* Line coding parameter set */
    usb_ghcdc_cls_req.complete = complete;                                /* Set Callback function */
    usb_ghcdc_cls_req.devadr = devadr;                                    /* Device Address */

    err = usb_hcdc_send_message(USB_HCDC_TCMD_CLASS_REQ, USB_PIPE0, USB_NULL, 0, USB_NULL);

    return err;
}
/***********************************************************************************************************************
 End of function R_usb_hcdc_set_line_coding
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hcdc_get_line_coding
 *
 *  Description:    GetLineCoding (CDC Request)
 *
 *  Parameters:     USB_HCDC_LineCoding_t *p_linecoding  : Line Coding table address
 *                  USB_UTR_CB_t complete     : Callback function
 *
 *  Return value:   USB_ER_t                  : Error info
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hcdc_get_line_coding( uint16_t devadr, USB_HCDC_LineCoding_t *p_linecoding, USB_UTR_CB_t complete )
{
    USB_ER_t    err;

    usb_ghcdc_cls_req.bRequestCode = USB_HCDC_GET_LINE_CODING;            /* Class request setup packet bRequest Set */
    usb_ghcdc_cls_req.parm.LineCoding = p_linecoding;                     /* Line Coding table address */
    usb_ghcdc_cls_req.complete = complete;                                /* Set Callback function */
    usb_ghcdc_cls_req.devadr = devadr;                                    /* Device Address */

    err = usb_hcdc_send_message(USB_HCDC_TCMD_CLASS_REQ, USB_PIPE0, USB_NULL, 0, USB_NULL);

    return err;
}
/***********************************************************************************************************************
 End of function R_usb_hcdc_get_line_coding
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hcdc_set_control_line_state
 *
 *  Description:    Set Control Line State (CDC Request)
 *
 *  Parameters:     uint16_t dtr              : DTR
 *                  uint16_t rts              : RTS
 *                  USB_UTR_CB_t complete     : Callback function
 *
 *  Return value:   USB_ER_t                  : Error info
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hcdc_set_control_line_state( uint16_t devadr, uint16_t dtr, uint16_t rts, USB_UTR_CB_t complete )
{
    USB_ER_t    err;

    usb_ghcdc_cls_req.bRequestCode = USB_HCDC_SET_CONTROL_LINE_STATE;     /* Class request setup packet bRequest Set */
    usb_ghcdc_cls_req.parm.ControlLineState.bDTR = dtr;                   /* RS232 signal DTR */
    usb_ghcdc_cls_req.parm.ControlLineState.bRTS = rts;                   /* RS232 signal RTS */
    usb_ghcdc_cls_req.complete = complete;                                /* Set Callback function */
    usb_ghcdc_cls_req.devadr = devadr;                                    /* Device Address */

    err = usb_hcdc_send_message(USB_HCDC_TCMD_CLASS_REQ, USB_PIPE0, USB_NULL, 0, USB_NULL);

    return err;
}
/***********************************************************************************************************************
 End of function R_usb_hcdc_set_control_line_state
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hcdc_send_break
 *
 *  Description:    Send break signal
 *
 *  Parameters:     uint16_t break_period_ms    : length of break in milli-seconds
 *                  USB_UTR_CB_t complete       : Callback function
 *
 *  Return value:   USB_ER_t                    : Error info
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hcdc_send_break( uint16_t devadr, uint16_t break_period_ms, USB_UTR_CB_t complete )
{
    USB_ER_t    err;

    usb_ghcdc_cls_req.bRequestCode = USB_HCDC_SEND_BREAK;               /* Class request setup packet bRequest Set */
    usb_ghcdc_cls_req.parm.breakPeriodMs = break_period_ms;             /* Period, in milli-seconds of break */
    usb_ghcdc_cls_req.complete = complete;                              /* Set Callback function */
    usb_ghcdc_cls_req.devadr = devadr;                                  /* Device Address */

    err = usb_hcdc_send_message(USB_HCDC_TCMD_CLASS_REQ, USB_PIPE0, USB_NULL, 0, USB_NULL);
    return err;
}
/***********************************************************************************************************************
 End of function R_usb_hcdc_send_break
 **********************************************************************************************************************/