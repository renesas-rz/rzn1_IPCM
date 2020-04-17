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
 * $Revision: 1201 $
 * $Date: 2019-02-04 14:08:15 +0000 (Mon, 04 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_wdt_rzn1_if.c
 * Description  :  WDT driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_wdt_rzn1_if.h"
#include "r_wdt_rzn1.h"

/***********************************************************************************************************************
 Data structures
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static bool wdt_counting = false;
static WDT_PRESCALER wdt_prescaler;
static uint16_t reload_val = 0xFFF;
static WDT_OUTPUT wdt_output;
static WDT_STATE wdt_state = WDT_STATE_CLOSED;

/***********************************************************************************************************************
 *
 *  Function:       R_WDT_GetVersion
 *
 *  Return value:   None.
 *
 *  Parameters:     buf - Pointer to buffer for version information.
 *
 *  Description:    Returns the WDT driver version number
 *
 **********************************************************************************************************************/
void R_WDT_GetVersion (void *buf)
{
    ((uint8_t *) buf)[1] = wdt_get_major_version_num();
    ((uint8_t *) buf)[0] = wdt_get_minor_version_num();
}
/***********************************************************************************************************************
 End of function R_WDT_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_WDT_Open
 *
 *  Return value:   Error value
 *
 *  Parameters:     void
 *
 *  Description:    Initialises the WDT.
 *
 **********************************************************************************************************************/
ER_RET R_WDT_Open (void)
{
    ER_RET ret_val = ER_OK;

    if (WDT_STATE_BUSY != wdt_state)
    {
        ret_val = wdt_init();

        if (ER_OK == ret_val)
        {
            wdt_state = WDT_STATE_OPEN;
        }
    }
    else
    {
        ret_val = ER_BUSY;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_WDT_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_WDT_Close
 *
 *  Return value:   Error status
 *
 *  Parameters:     None.
 *
 *  Description:    Uninitialises the WDT
 *
 **********************************************************************************************************************/
ER_RET R_WDT_Close (void)
{
    ER_RET ret_val = ER_OK;

    /* Cannot close the WDT once countdown has begun */
    if (false == wdt_counting)
    {
        ret_val = wdt_uninit();
        if (ER_OK == ret_val)
        {
            wdt_state = WDT_STATE_CLOSED;
        }
    }
    else
    {
        ret_val = ER_INVAL;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_WDT_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_WDT_Control
 *
 *  Return value:   Error status
 *
 *  Parameters:
 *                  control_request - Which control action to implement.
 *                  control - The control parameter that is used along with the
 *                           control action to configure the channel a certain way.
 *
 *  Description:    Controls a WDT instance.
 *
 **********************************************************************************************************************/
ER_RET R_WDT_Control (WDT_CONTROL_REQUEST control_request, void *control)
{
    ER_RET ret_val = ER_OK;

    if (NULL == control)
    {
        ret_val = ER_PARAM;
    }
    else if (WDT_STATE_OPEN == wdt_state)
    {
        switch (control_request)
        {
            case WDT_SET_PRESCALER:
                if (true == wdt_counting)
                {
                    ret_val = ER_INVAL; /* Cannot reconfigure the WDT after countdown has commenced */
                }
                else
                {
                    wdt_prescaler = *(WDT_PRESCALER *) control;
                }
            break;
            case WDT_GET_PRESCALER:
                *(WDT_PRESCALER *) control = wdt_prescaler;
            break;
            case WDT_SET_RELOAD_VALUE:
                if (true == wdt_counting) /* Cannot reconfigure the WDT after countdown has commenced */
                {
                    ret_val = ER_INVAL;
                }
                else
                {
                    reload_val = *(uint16_t *) control;
                }
            break;
            case WDT_GET_RELOAD_VALUE:
                *(uint16_t *) control = reload_val;
            break;
            case WDT_SET_OUTPUT:
                wdt_setoutput( *(WDT_OUTPUT *) control);
                wdt_output = *(WDT_OUTPUT *) control;
            break;
            case WDT_GET_OUTPUT:
                *(WDT_OUTPUT *) control = wdt_output;
            break;
            case WDT_SET_CALLBACK:
                ret_val = wdt_setcallback((wdt_callback) control);
            break;
            default:
                ret_val = ER_PARAM;
            break;

        }
    }
    else
    {
        if (WDT_STATE_BUSY == wdt_state)
        {
            ret_val = ER_BUSY;
        }
        else
        {
            ret_val = ER_INVAL;
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_WDT_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_WDT_Start
 *
 *  Return value:   Error status
 *
 *  Parameters:     None.
 *
 *  Description:   Start the WDT countdown
 *
 **********************************************************************************************************************/
ER_RET R_WDT_Start (void)
{
    ER_RET ret_val = ER_OK;

    if (WDT_STATE_OPEN == wdt_state)
    {
        ret_val = wdt_enable(wdt_prescaler, reload_val);

        if (ER_OK == ret_val)
        {
            wdt_state = WDT_STATE_BUSY;
            wdt_counting = true;
        }
    }
    else
    {
        ret_val = ER_INVAL;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_WDT_Start
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_WDT_Kick
 *
 *  Return value:   Error status
 *
 *  Parameters:     None.
 *
 *  Description:    Refreshes the countdown value
 *
 **********************************************************************************************************************/
ER_RET R_WDT_Kick (void)
{
    ER_RET ret_val = ER_OK;

    if (WDT_STATE_CLOSED != wdt_state)
    {
        /* Check countdown has begun*/
        if (false == wdt_counting)
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = wdt_retrigger();
        }
    }
    else
    {
        ret_val = ER_INVAL;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_WDT_Kick
 **********************************************************************************************************************/
