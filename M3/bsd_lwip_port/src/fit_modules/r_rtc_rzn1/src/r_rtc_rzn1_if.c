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
 * $Revision: 1195 $
 * $Date: 2019-01-29 12:51:05 +0000 (Tue, 29 Jan 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_rtc_rzn1_if.c
 * Description  :  RTC driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "r_rtc_rzn1_config.h"
#include "r_rtc_rzn1_if.h"
#include "r_rtc_rzn1.h"

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static RTC_IF_STATE_E rtc_state = RTC_STATE_NOT_INIT; /* RTC state */
/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           R_RTC_GetVersion
 *
 *  Return value:       None.
 *
 *  Parameters:         Pointer to version buffer.
 *
 *  Description:        Returns the RTC driver version number
 *
 **********************************************************************************************************************/
void R_RTC_GetVersion (void *buf)
{
    ((uint8_t *) buf)[1] = rtc_get_major_version_num();
    ((uint8_t *) buf)[0] = rtc_get_minor_version_num();
}
/***********************************************************************************************************************
 End of function R_RTC_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           R_RTC_Init
 *
 *  Return value:       Error status
 *
 *  Parameters:         None
 *  Description:        Initialise RTC IP
 *
 **********************************************************************************************************************/
ER_RET R_RTC_Init (void)
{
    ER_RET ret_val = ER_OK;

    if (RTC_STATE_NOT_INIT != rtc_state)
    {
        return ER_INVAL;
    }

    /* Initialise the RTC driver */
    ret_val = rtc_init();
    if (ER_OK == ret_val)
    {
        rtc_state = RTC_STATE_INIT;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_RTC_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           R_RTC_Uninitialise
 *
 *  Return value:       Error status
 *
 *  Parameters:         None
 *  Description:        Un-Initialise RTC IP
 *
 **********************************************************************************************************************/
ER_RET R_RTC_Uninitialise (void)
{
    ER_RET ret_val = ER_OK;

    if ((RTC_STATE_INIT != rtc_state) && (RTC_STATE_CLOSED != rtc_state))
    {
        return ER_INVAL;
    }

    rtc_state = RTC_STATE_NOT_INIT;

    /* Initialise the RTC driver */
    ret_val = rtc_uninitialise();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_RTC_Uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           R_RTC_Open
 *
 *  Return value:       Error status
 *
 *  Parameters:         None
 *
 *  Description:        Opens the RTC
 *
 **********************************************************************************************************************/
ER_RET R_RTC_Open (void)
{
    ER_RET ret_val = ER_OK;

    if ((RTC_STATE_INIT != rtc_state) && (RTC_STATE_CLOSED != rtc_state))
    {
        return ER_INVAL;
    }

    ret_val = rtc_open();
    if (ER_OK == ret_val)
    {
        rtc_state = RTC_STATE_OPEN;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_RTC_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           R_RTC_Close
 *
 *  Return value:       Error status
 *
 *  Parameters:         None
 *
 *  Description:        Closes the RTC
 *
 **********************************************************************************************************************/
ER_RET R_RTC_Close (void)
{
    ER_RET ret_val = ER_OK;

    if (RTC_STATE_OPEN != rtc_state)
    {
        return ER_INVAL;
    }

    rtc_state = RTC_STATE_INIT;

    /* Close the RTC driver */
    ret_val = rtc_close();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_RTC_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           R_RTC_Control
 *
 *  Return value:       Error status
 *
 *  Parameters:         control_request - request to configure or get existing configuration.
 *                      buf - configuration data (to set or get).
 *
 *                      NOTE: API function checks that buf is non-zero.
 *                      The upper layer should check that the buffer lies within a valid address range.
 *
 *  Description:        Set Alarm/Periodic/Interval Callbacks, reset,
 *                      get RTC info, depending on control_request
 *
 **********************************************************************************************************************/
ER_RET R_RTC_Control (RTC_CONTROL_REQUEST_E control_request, uint8_t *buf)
{
    ER_RET ret_val = ER_OK;

    /* For all control requests except RTC_CONTROL_RESET, need a valid buf pointer */
    if (RTC_CONTROL_RESET != control_request)
    {
        if (FIT_NO_PTR == buf)
        {
            ret_val = ER_PARAM;
        }
    }

    if (ER_OK == ret_val)
    {
        /* RTC driver state & parameters are valid */
        switch (control_request)
        {
            case RTC_CONTROL_SET_CLOCK_CONFIG:
                ret_val = rtc_set_clock_calib((RTC_CLOCK_CALIB_T *) buf);
            break;

            case RTC_CONTROL_GET_STATE:
                buf[0] = (uint8_t) rtc_state;
            break;

            case RTC_CONTROL_RESET:
                /* Reset the RTC */
                ret_val = rtc_reset();
            break;

            case RTC_CONTROL_SET_ALARM_CALLBACK:
            case RTC_CONTROL_SET_PERIODIC_CALLBACK:
            case RTC_CONTROL_SET_ONE_SEC_CALLBACK:
                /* Setup a callback event*/
                if (RTC_STATE_OPEN == rtc_state)
                {
                    ret_val = rtc_register_event_callback((RTC_CALLBACK_REQUEST_T *) buf);
                }
                else
                {
                    ret_val = ER_INVAL;
                }
            break;

            default:
                ret_val = ER_PARAM;
            break;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_RTC_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           R_RTC_Read
 *
 *  Return value:       Error Code
 *
 *  Parameters:         p_current - Returns RTC time in standard 'C' time format
 *
 *  Description:        Reads time from the RTC
 *
 **********************************************************************************************************************/
ER_RET R_RTC_Read (tm_t * p_current)
{
    ER_RET ret_val = ER_OK;

    if (RTC_STATE_OPEN != rtc_state)
    {
        return ER_INVAL;
    }

    ret_val = rtc_read(p_current);

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_RTC_Read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           R_RTC_Write
 *
 *  Return value:       Error Code
 *
 *  Parameters:         p_current - Gives RTC time in standard 'C' time format
 *
 *  Description:        Writes time to the RTC
 *
 **********************************************************************************************************************/
ER_RET R_RTC_Write (tm_t * p_current)
{
    ER_RET ret_val = ER_OK;

    if (RTC_STATE_OPEN != rtc_state)
    {
        return ER_INVAL;
    }

    ret_val = rtc_write(p_current);

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_RTC_Write
 **********************************************************************************************************************/
