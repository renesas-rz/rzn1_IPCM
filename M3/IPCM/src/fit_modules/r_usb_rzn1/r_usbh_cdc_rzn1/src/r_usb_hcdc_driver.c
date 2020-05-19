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
 * FILE         :  r_usb_hcdc_driver.c
 * Description  :  USB Host CDC Drivers
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2020. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include "r_usb_basic_local.h"
#include "r_usb_hcdc_if.h"
#include "r_usb_hcdc_local.h"

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/
/* variables */
USB_HCDC_ClassRequest_UTR_t     usb_ghcdc_cls_req;  /* Class Request Parameter */
uint8_t     *usb_ghcdc_device_table;                /* Device Descriptor Table */
uint16_t    usb_ghcdc_devaddr;                      /* Device Address */
/* functions */
void        usb_hcdc_task(void);
USB_ER_t    usb_hcdc_send_message(uint16_t msginfo, uint16_t pipe_id, void* tranadr, uint32_t tranlen,  USB_UTR_CB_t complete);

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
/* variables */
static USB_UTR_t   usb_ghcdc_ControlSetupUtr;       /* Control data transfer message */
UNCACHED_BUFFER static uint8_t usb_ghcdc_ClassRequestData[USB_HCDC_TR_DATA_SIZE];   /* CDC Class Request transfer Data */
static USB_UTR_t   usb_ghcdc_Mess[USB_MAXPIPE];     /* PCDC massage */
static int16_t     usb_ghcdc_EnumSeq;               /* Enumeration Sequence */
static USB_SETUP_t usb_ghcdc_setup;                 /* Control Transfer Request field */
static USB_HCDC_Strings_t usb_ghcdc_strings;
/* functions */
static void        usb_hcdc_enumeration(USB_UTR_t *mess);
static USB_ER_t    usb_hcdc_data_trans(uint16_t pipe, uint32_t size, uint8_t *table, USB_UTR_CB_t complete);
static USB_ER_t    usb_hcdc_class_request_process(void);

/***********************************************************************************************************************
 Renesas USB Host CDC Driver functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hcdc_task
 *
 *  Description:    HCDC task
 *
 *  Parameters:     None
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void usb_hcdc_task(void)
{
    USB_UTR_t   *mess;
    USB_ER_t    err;

    err = R_USB_RCV_MSG(USB_HCDC_MBX,(USB_MSG_t**)&mess);
    if( err != USB_OK )
    {
        return;
    }

    switch( mess->msginfo )
    {
    case USB_MSG_CLS_CHECKREQUEST:
        /* Initialize sequence number for enumeration */
        usb_ghcdc_EnumSeq = USB_SEQ_0;
        /* Start Class Enumeration */
        usb_hcdc_enumeration(mess);
        break;

    case USB_HCDC_TCMD_RECEIVE:
    case USB_HCDC_TCMD_SEND:
    case USB_HCDC_TCMD_CLASS_NOTIFY:
        /* Data send request for Host */
        err = usb_hcdc_data_trans(mess->keyword, mess->tranlen,
            (uint8_t*)mess->tranadr, mess->complete);
        break;

    case USB_HCDC_TCMD_CLASS_REQ:
        err = usb_hcdc_class_request_process();
        if( err == USB_ERROR )
        {
            R_USB_WAI_MSG( USB_HCDC_MBX, mess, 500 );
            USB_PRINTF0("### CDC Class Request QOVR retry\n");
            return;
        }
        break;
    default:
        break;
    }

    err = R_USB_REL_BLK(USB_HCDC_MPL, mess);
    if( err != USB_OK )
    {
        USB_PRINTF0("### USB HCDC Task rel_blk error\n");
    }
}
/***********************************************************************************************************************
 End of function usb_hcdc_task
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hcdc_send_message
 *
 *  Description:    Send message to HCDC task.
 *
 *  Parameters:     uint16_t msginfo          :
 *                  uint16_t pipe_id          :
 *                  uint8_t  *tranadr         : Send data address
 *                  uint32_t tranlen          : Send data Size
 *                  USB_UTR_CB_t complete     : Callback function
 *
 *  Return Value:   USB_ER_t                  : Error info
 *
 **********************************************************************************************************************/
USB_ER_t usb_hcdc_send_message(uint16_t msginfo, uint16_t pipe_id, void* tranadr, uint32_t tranlen, USB_UTR_CB_t complete)
{
    USB_UTR_t   *p_blf;
    USB_ER_t    err;

    /* Get mem block from pool. */
    err = R_USB_PGET_BLK(USB_HCDC_MPL, &p_blf);
    if( err == USB_OK )
    {
        p_blf->msginfo  = msginfo;               /* Set message information: USB TX */
        p_blf->keyword  = pipe_id;
        p_blf->tranadr  = tranadr;               /* Transfer data start address */
        p_blf->tranlen  = tranlen;               /* Transfer data length */
        p_blf->complete = complete;              /* Callback function */

        /* Send message */
        err = R_USB_SND_MSG(USB_HCDC_MBX, (USB_MSG_t*)p_blf);
        if( err != USB_OK )
        {
            /* Send message failure */
            USB_PRINTF1("### hcdc snd_msg error (%ld)\n", err);
            err = R_USB_REL_BLK(USB_HCDC_MPL, p_blf);
            if( err != USB_OK )
            {
                /* Release memory block failure */
                USB_PRINTF1("### hcdc rel_blk error (%ld)\n", err);
            }
        }
    }
    else
    {
        /* Get memory block failure */
        USB_PRINTF1("### hcdc pget_blk error (%ld)\n", err);
    }

    return err;
}
/***********************************************************************************************************************
 End of function usb_hcdc_send_message
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hcdc_get_strings
 *
 *  Description:    Get the CDC device strings
 *                  Note: This function can only be assumed to return the correct data immediately after device enumeration
 *
 *  Parameters:     None
 *
 *  Return Value:   const USB_HCDC_Strings_t *  : The Device strings which shall be valid or NULL
 *
 **********************************************************************************************************************/
const USB_HCDC_Strings_t * usb_hcdc_get_strings(void)
{
    return &usb_ghcdc_strings;
}
/***********************************************************************************************************************
 End of function usb_hcdc_get_strings
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hcdc_enumeration
 *
 *  Description:    USB CDC Class Enumeration
 *
 *  Parameters:     USB_UTR_t *mess           : CDC Class Info pointer
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
static void usb_hcdc_enumeration(USB_UTR_t *mess)
{
    switch(usb_ghcdc_EnumSeq)
    {
    case    USB_SEQ_0:
        /* String descriptor (LANGID codes requested) */
        usb_hstd_GetStringDesc(usb_ghcdc_devaddr, (uint16_t)0, &usb_hcdc_enumeration);
        usb_ghcdc_EnumSeq++;
        break;

    case    USB_SEQ_1:
        /* Get Product ID String */
        if( mess->result == USB_CTRL_END )
        {
            /* Set LanguageID */
            usb_hstd_SetLangId();
            /* Get Product ID String */
            usb_hstd_GetStringDesc(usb_ghcdc_devaddr, (uint16_t)usb_ghcdc_device_table[USB_DEV_I_PRODUCT], &usb_hcdc_enumeration);
            usb_ghcdc_EnumSeq++;
        }
        else    /* USB_ERROR */
        {
            USB_PRINTF0("### Enumeration is stopped(String STALL)\n");
            R_usb_hstd_ReturnEnuMGR(USB_OK);   /* Return to MGR */
        }
        break;

    case    USB_SEQ_2:
        /* Finished getting Product ID transaction, process result */
        if( mess->result == USB_CTRL_END )
        {
            /* Copy Product Id string data */
            R_USB_ConvertUnicodeStrDscrToAsciiStr((uint8_t *)mess->tranadr, (uint8_t *)usb_ghcdc_strings.product_id);
            /* Get Manufacturer ID String */
            usb_hstd_GetStringDesc(usb_ghcdc_devaddr, (uint16_t)usb_ghcdc_device_table[USB_DEV_I_MANUFACTURER], &usb_hcdc_enumeration);
            usb_ghcdc_EnumSeq++;

        }
        else    /* USB_ERROR */
        {
            USB_PRINTF0("*** Product ID error\n");
            R_usb_hstd_ReturnEnuMGR(USB_OK);   /* Return to MGR */
        }
        break;

    case    USB_SEQ_3:
        /* Finished getting Manufacturer ID transaction, process result */
        if( mess->result == USB_CTRL_END )
        {
            /* Copy Manufacturer Id string data */
            R_USB_ConvertUnicodeStrDscrToAsciiStr((uint8_t *)mess->tranadr, (uint8_t *)usb_ghcdc_strings.manufacturer_id);
            /* Get Serial Number String */
            usb_hstd_GetStringDesc(usb_ghcdc_devaddr, (uint16_t)usb_ghcdc_device_table[USB_DEV_I_SERIAL_NUMBER], &usb_hcdc_enumeration);
            usb_ghcdc_EnumSeq++;
        }
        else    /* USB_ERROR */
        {
            USB_PRINTF0("*** Manufacturer ID error\n");
            R_usb_hstd_ReturnEnuMGR(USB_OK);   /* Return to MGR */
        }
        break;

    case    USB_SEQ_4:
        /* Finished getting Serial Number string transaction, process result */
        if( mess->result == USB_CTRL_END )
        {
            /* Copy Serial Number  Id string data */
            R_USB_ConvertUnicodeStrDscrToAsciiStr((uint8_t *)mess->tranadr, (uint8_t *)usb_ghcdc_strings.serial_num);
        }
        else    /* USB_ERROR */
        {
            USB_PRINTF0("*** Serial Number ID error\n");
        }

        R_usb_hstd_ReturnEnuMGR(USB_OK);    /* Return to MGR */
        break;
    }
}
/***********************************************************************************************************************
 End of function usb_hcdc_enumeration
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hcdc_data_trans
 *
 *  Description:    Transfer data from USB
 *
 *  Parameters:     uint16_t pipe             : Pipe No
 *                  uint32_t size             : Data Size
 *                  uint8_t *table            : Data address
 *                  USB_UTR_CB_t complete     : Callback function
 *
 *  Return Value:   USB_ER_t                  : Error Info
 *
 **********************************************************************************************************************/
static USB_ER_t usb_hcdc_data_trans(uint16_t pipe, uint32_t size, uint8_t *table, USB_UTR_CB_t complete)
{
    /* Transfer Pipe No set */
    usb_ghcdc_Mess[pipe].keyword        = pipe;
    /* Data message address set */
    usb_ghcdc_Mess[pipe].tranadr        = table;
    /* Transfer data length */
    usb_ghcdc_Mess[pipe].tranlen        = size;
    /* Callback set */
    usb_ghcdc_Mess[pipe].complete       = complete;

    /* Transfer start */
    return( R_usb_hstd_TransferStart(&usb_ghcdc_Mess[pipe]) );
}
/***********************************************************************************************************************
 End of function usb_hcdc_data_trans
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  usb_hcdc_class_request_process
 *
 *  Description:    Communications Devices Class Class Request
 *
 *  Parameters:     None
 *
 *  Return Value:   USB_ER_t                  : Error Info
 *
 **********************************************************************************************************************/
static USB_ER_t usb_hcdc_class_request_process(void)
{
    USB_ER_t    err;
    USB_HCDC_ControlLineState_t *p_control_line_state;
    USB_HCDC_LineCoding_t       *p_set_line_coding_parm;

    usb_ghcdc_ControlSetupUtr.keyword  = (uint16_t)USB_PIPE0;
    usb_ghcdc_ControlSetupUtr.tranadr  = (void*)USB_NULL;
    usb_ghcdc_ControlSetupUtr.complete = usb_ghcdc_cls_req.complete;

    switch(usb_ghcdc_cls_req.bRequestCode)
    {
    case USB_HCDC_SET_LINE_CODING:
        /* Data message address set */
        usb_ghcdc_ControlSetupUtr.tranadr = (void*)usb_ghcdc_ClassRequestData;
        p_set_line_coding_parm = usb_ghcdc_cls_req.parm.LineCoding;
        memcpy(&usb_ghcdc_ClassRequestData, p_set_line_coding_parm, USB_HCDC_LINE_CODING_STR_LEN);
        /* DTE Rate set */
        usb_ghcdc_ClassRequestData[0] = (uint8_t)(p_set_line_coding_parm->dwDTERate & 0xff);
        usb_ghcdc_ClassRequestData[1] = (uint8_t)((p_set_line_coding_parm->dwDTERate >> 8) & 0xff);
        usb_ghcdc_ClassRequestData[2] = (uint8_t)((p_set_line_coding_parm->dwDTERate >> 16) & 0xff);
        usb_ghcdc_ClassRequestData[3] = (uint8_t)((p_set_line_coding_parm->dwDTERate >> 24) & 0xff);
        /* Setup message address set */
        usb_ghcdc_setup.type   = 0x2021;
        usb_ghcdc_setup.value  = 0x0000;
        usb_ghcdc_setup.index  = 0x0000;
        usb_ghcdc_setup.length = USB_HCDC_LINE_CODING_STR_LEN;
        break;

    case USB_HCDC_SET_CONTROL_LINE_STATE:
        /* Setup message address set */
        usb_ghcdc_setup.type   = 0x2221;
        usb_ghcdc_setup.value  = 0x0000;    /* Clear as value setting below only sets the valid bits for this command and leaves residual bits in place */
        usb_ghcdc_setup.index  = 0x0000;
        usb_ghcdc_setup.length = 0x0000;

        p_control_line_state = (USB_HCDC_ControlLineState_t *)&usb_ghcdc_setup.value;
        p_control_line_state->bDTR = usb_ghcdc_cls_req.parm.ControlLineState.bDTR;
        p_control_line_state->bRTS = usb_ghcdc_cls_req.parm.ControlLineState.bRTS;
        break;

    case USB_HCDC_GET_LINE_CODING:
        /* Data message address set */
        usb_ghcdc_ControlSetupUtr.tranadr = usb_ghcdc_cls_req.parm.LineCoding;
        /* Setup message address set */
        usb_ghcdc_setup.type   = 0x21A1;
        usb_ghcdc_setup.value  = 0x0000;
        usb_ghcdc_setup.index  = 0x0000;
        usb_ghcdc_setup.length = USB_HCDC_LINE_CODING_STR_LEN;
        break;

     case USB_HCDC_SEND_BREAK:
        /* Setup message address set */
        usb_ghcdc_setup.type   = 0x2321;
        usb_ghcdc_setup.value  = usb_ghcdc_cls_req.parm.breakPeriodMs;
        usb_ghcdc_setup.index  = 0x0000;
        usb_ghcdc_setup.length = 0x0000;
        break;

    default:
        break;
    }
    usb_ghcdc_cls_req.bRequestCode = USB_HCDC_NULL;

    usb_ghcdc_ControlSetupUtr.tranlen = usb_ghcdc_setup.length;

    usb_ghcdc_setup.devaddr = usb_ghcdc_cls_req.devadr;
    usb_ghcdc_ControlSetupUtr.setup = &usb_ghcdc_setup;

    err = R_usb_hstd_TransferStart(&usb_ghcdc_ControlSetupUtr);

    return  err;
}
/***********************************************************************************************************************
 End of function usb_hcdc_class_request_process
 **********************************************************************************************************************/