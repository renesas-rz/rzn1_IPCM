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
 * FILE         :  r_usb_rzn1_if.c
 * Description  :  USB driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
/*
 ***********************************************************************************
 * Doxygen Summary block
 **********************************************************************************************************************/
/*!
 * @ingroup USB_MODULE RZN1 USB Bare Metal Driver
 * @{
 * @file
 * @brief USB Bare Metal Driver
 * @details Supports configuring, reading and writing USB port
 * @} */
/***********************************************************************************************************************
 * End of Doxygen Summary block
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_usb_rzn1_config.h"
#include "r_usb_rzn1_if.h"
#include "r_usbf_basic_rzn1_if.h"
#include "r_usb_basic_if.h"

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
#define ASCII_EXT_RANGE_MAX                     255

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_GetVersion
 *
 *  Return value:   None.
 *
 *  Parameters:     None.
 *
 *  Description:    Returns the USB Function driver version number
 *
 **********************************************************************************************************************/
void R_USB_GetVersion(void *buf)
{
    ((uint8_t *) buf)[1] = R_usb_pstd_get_major_version_num();
    ((uint8_t *) buf)[0] = R_usb_pstd_get_minor_version_num();
}
/***********************************************************************************************************************
 End of function R_USB_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USBh_GetVersion
 *
 *  Return value:   None.
 *
 *  Parameters:     None.
 *
 *  Description:    Returns the USB Host driver version number
 *
 **********************************************************************************************************************/
void R_USBh_GetVersion(void *buf)
{
    ((uint8_t *) buf)[1] = R_usb_hstd_get_major_version_num();
    ((uint8_t *) buf)[0] = R_usb_hstd_get_minor_version_num();
}
/***********************************************************************************************************************
 End of function R_USBh_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_Init
 *
 *  Description:    Initialise generic (Host & Function) USB parameters.
 *                  If Host Classes configured, call USB Basic Host driver init function
 *                  If Function Classes configured, call USB Basic function driver init function
 *
 *  Parameters:     void
 *
 *  Return value:   ER_RET - Error Status
 *
 **********************************************************************************************************************/
ER_RET R_USB_Init(void)
{
    ER_RET ret_val = ER_OK;

#if defined(USB_CFG_PCDC_USE) || defined(USB_CFG_PHID_USE) || defined(USB_CFG_PMSC_USE) || defined(USB_CFG_PVND_USE)
    ret_val = R_USBf_Init();
#endif

#if defined(USB_CFG_HCDC_USE) || defined(USB_CFG_HHID_USE) || defined(USB_CFG_HMSC_USE) || defined(USB_CFG_HVND_USE)
    ret_val = R_USBh_Init();
#endif

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_USB_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_ConvertUnicodeStrDscrToAsciiStr
 *
 *  Description:    Convert a complete USB String descriptor to standard 'C' type string
 *
 *  Parameters:     p_str_dscr  - complete USB String Descriptor
 *                  p_ascii_str - buffer to store the decoded (ASCII string) USB Unicode string
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void R_USB_ConvertUnicodeStrDscrToAsciiStr(const uint8_t * const p_str_dscr, uint8_t * p_ascii_str)
{
    /* Divide given value by two as count is in bytes but string char is in 16bit unicode format */
    uint8_t char_count             = (p_str_dscr[USB_STR_B_LENGTH] - USB_STR_B_STRING_START)/2 ;
    uint8_t desc_type              = p_str_dscr[USB_STR_B_DESCRIPTOR_TYPE];
    const uint16_t * p_unicode_str = (uint16_t *)&p_str_dscr[USB_STR_B_STRING_START];
    uint8_t index;

    if (USB_GET_DT_TYPE(USB_STRING_DESCRIPTOR) != desc_type)
    {
        /* Set NULL string */
        p_ascii_str[0] = '\0';
        return;
    }

    for (index = 0; index < char_count; index++)
    {
        /* Convert string from USB 16 bit wide char to standard C 8 bit wide */
        if (ASCII_EXT_RANGE_MAX >= p_unicode_str[index])
        {
            /* Valid ASCII character */
            p_ascii_str[index] = (uint8_t)p_unicode_str[index];
        }
        else
        {
            /* Unicode character not supported by ASCII */
            p_ascii_str[index] = '?';
        }
    }

    /* Ensure NULL termination of string */
    p_ascii_str[char_count] = '\0';

    return;
}
/***********************************************************************************************************************
 End of function R_USB_ConvertUnicodeStrDscrToAsciiStr
 **********************************************************************************************************************/