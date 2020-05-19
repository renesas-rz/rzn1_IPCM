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
 * $Revision: 1802 $
 * $Date: 2020-01-08 17:27:34 +0000 (Wed, 08 Jan 2020) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_pcdc_api.c
 * Description  :  USB PCDC API Functions
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
 Section    <Section Definition> , "Project Sections"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Constant macro definitions
 **********************************************************************************************************************/
/* setup packet table size (uint16_t * 5) */
#define     USB_CDC_SETUP_TBL_BSIZE             (12)  /* align on uint32_t boundary */

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
/* Abstract Control Model Notification - SerialState */
uint8_t usb_gpcdc_SerialState_Table[USB_CDC_SETUP_TBL_BSIZE] =
{ 0xA1, /* bmRequestType */
0x20, /* bNotification:SERIAL_STATE */
0x00, 0x00, /* wValue:Zero */
0x00, 0x00, /* wIndex:Interface */
0x02, 0x00, /* wLength:2 */
0x00, 0x00 }; /* Data:UART State bitmap */

/***********************************************************************************************************************
 Renesas Abstracted Peripheral Communications Devices Class Driver API functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_usb_pcdc_SendData
 *
 *  Description:    Handles request to send data to Host
 *
 *  Parameters:     uint8_t       *Table      ; Pointer to Data stored buffer
 *                  uint32_t      size        ; Data size
 *                  USB_CB_t      complete    ; Pointer to Callback function
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void R_usb_pcdc_SendData(uint8_t *Table, uint32_t size, USB_UTR_CB_t complete)
{
    usb_pcdc_DataTrans(USB_PCDC_USE_PIPE_IN, size, Table, complete);
}
/***********************************************************************************************************************
 End of function R_usb_pcdc_SendData
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_usb_pcdc_ReceiveData
 *
 *  Description:    Data Receive request for Host
 *
 *  Parameters:     uint8_t       *Table      ; Pointer to Data stored buffer
 *                  uint32_t      size        ; Data size
 *                  USB_CB_t      complete    ; Pointer to Callback function
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void R_usb_pcdc_ReceiveData(uint8_t *Table, uint32_t size, USB_UTR_CB_t complete)
{
    usb_pcdc_DataTrans(USB_PCDC_USE_PIPE_OUT, size, Table, complete);
}
/***********************************************************************************************************************
 End of function R_usb_pcdc_ReceiveData
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_usb_pcdc_SerialStateNotification
 *
 *  Description:    Class Notification Serial State for USB Host
 *
 *  Parameters:     uint16_t  serial_state   ; State of Serial port
 *                  USB_CB_t  complete       ; Pointer to Callback function
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void R_usb_pcdc_SerialStateNotification(USB_SCI_SerialState_t serial_state,
        USB_UTR_CB_t complete)
{
    /* UART State bitmap set */
    usb_gpcdc_SerialState_Table[8] = (uint8_t)(
            serial_state.u_USB_SCI_SerialState.WORD & 0xff);
    usb_gpcdc_SerialState_Table[9] = (uint8_t)(
            serial_state.u_USB_SCI_SerialState.WORD >> 8);
    usb_pcdc_DataTrans(USB_PCDC_USE_PIPE_STATUS, 10,
            usb_gpcdc_SerialState_Table, complete);
}
/***********************************************************************************************************************
 End of function R_usb_pcdc_SerialStateNotification
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_usb_pcdc_ctrltrans
 *
 *  Description:    Class request processing for CDC
 *
 *  Parameters:     USB_REQUEST_t *preq  ; Class request information
                    uint16_t ctsq        ; Control Stage
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void R_usb_pcdc_ctrltrans(USB_REQUEST_t *preq, uint16_t ctsq)
{
    if (USB_CLASS == preq->ReqTypeType)
    {
        switch (ctsq)
        {
        /* Idle or setup stage */
        case USB_CS_IDST:
            usb_pcdc_ControlTrans_idst(preq);
            break;
            /* Control read data stage */
        case USB_CS_RDDS:
            usb_pcdc_ControlTrans_rdds(preq);
            break;
            /* Control write data stage */
        case USB_CS_WRDS:
            usb_pcdc_ControlTrans_wrds(preq);
            break;
            /* Control write nodata status stage */
        case USB_CS_WRND:
            usb_pcdc_ControlTrans_wrnd(preq);
            break;
            /* Control read status stage */
        case USB_CS_RDSS:
            usb_pcdc_ControlTrans_rdss(preq);
            break;
            /* Control write status stage */
        case USB_CS_WRSS:
            usb_pcdc_ControlTrans_wrss(preq);
            break;

            /* Control sequence error */
        case USB_CS_SQER:
            R_usb_pstd_ControlEnd((uint16_t)USB_DATA_ERR);
            break;
            /* Illegal */
        default:
            R_usb_pstd_ControlEnd((uint16_t)USB_DATA_ERR);
            break;
        }
    } else
    {
        R_usb_pstd_SetPipeStall(USB_PIPE0);
    }
}
/***********************************************************************************************************************
 End of function R_usb_pcdc_ctrltrans
 **********************************************************************************************************************/

/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
