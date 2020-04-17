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
 * $Revision: 1305 $
 * $Date: 2019-02-26 08:39:27 +0000 (Tue, 26 Feb 2019) $
 *
 * PROJECT NAME :   RZ/N1 bare metal Drivers
 * FILE         :   r_can_rzn1_if.c
 * Description  :   CAN driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "r_can_rzn1_config.h"
#include "r_can_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define CAN_CHAN_NUM_TO_BIT_MASK(chan_num)      ((uint32_t)(1 << (chan_num)))
#define CAN_IS_CHAN_OPEN(chan_num)              (m_channels_open & CAN_CHAN_NUM_TO_BIT_MASK(chan_num))
#define CAN_CHAN_CLOSED                         (0)

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static CAN_IF_STATE_E m_can_state = CAN_STATE_NOT_INIT; /* CAN state */
static uint32_t m_channels_open;

/***********************************************************************************************************************
 * Local function definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 External variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_CAN_GetVersion
 *
 *  Return value:   Driver number
 *
 *  Parameters:     Pointer to buffer for version information
 *  Description:    Returns the CAN driver version number
 *
 **********************************************************************************************************************/
void R_CAN_GetVersion (void *buf)
{
    ((uint8_t *) buf)[1] = (uint8_t)CAN_DRIVER_MAJOR_VERSION_NUMBER;
    ((uint8_t *) buf)[0] = (uint8_t)CAN_DRIVER_MINOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function R_CAN_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_CAN_Init
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *  Description:    Initialise CAN driver and channels interface state
 *
 **********************************************************************************************************************/
ER_RET R_CAN_Init (void)
{
    ER_RET ret_val = ER_OK;

    if (CAN_STATE_NOT_INIT != m_can_state)
    {
        return ER_INVAL;
    }

    /* Initialise the CAN driver */
    ret_val = can_init();

    if (ER_OK == ret_val)
    {
        m_can_state = CAN_STATE_INIT;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_CAN_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_CAN_Uninitialise
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *  Description:    Un-Initialise CAN IP
 *
 **********************************************************************************************************************/
ER_RET R_CAN_Uninitialise (void)
{
    ER_RET ret_val = ER_OK;

    if ((CAN_STATE_INIT != m_can_state) || (CAN_CHAN_CLOSED != m_channels_open))
    {
        return ER_INVAL;
    }

    m_can_state = CAN_STATE_NOT_INIT;

    /* Initialise the CAN driver */
    ret_val = can_uninitialise();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_CAN_Uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_CAN_Open
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - CAN channel number to open
 *
 *  Description:    Opens an CAN channel
 *
 **********************************************************************************************************************/
ER_RET R_CAN_Open (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

    if (CAN_STATE_INIT != m_can_state)
    {
        return ER_INVAL;
    }

    if ((chan_num >= CAN_CHAN_MAX) || CAN_IS_CHAN_OPEN(chan_num))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Attempt to open and configure the channel */
        ret_val = can_channel_open(chan_num);
        if (ER_OK == ret_val)
        {
            m_channels_open |= CAN_CHAN_NUM_TO_BIT_MASK(chan_num);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_CAN_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_CAN_Close
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - CAN channel number to close
 *
 *  Description:    Closes an CAN channel
 *
 **********************************************************************************************************************/
ER_RET R_CAN_Close (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

    if (CAN_STATE_INIT != m_can_state)
    {
        return ER_INVAL;
    }

    if ((chan_num >= CAN_CHAN_MAX) || (CAN_CHAN_CLOSED == CAN_IS_CHAN_OPEN(chan_num)))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Close the CAN channel */
        ret_val = can_channel_close(chan_num);
        m_channels_open &= ( ~CAN_CHAN_NUM_TO_BIT_MASK(chan_num));
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_CAN_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_CAN_Write
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - CAN channel number
 *                  ptr_msg: pointer to message buffer
 *
 *  Description:    Write data to a CAN channel
 *
 **********************************************************************************************************************/
ER_RET R_CAN_Write (uint8_t chan_num, CAN_MSG_T * ptr_msg)
{
    ER_RET ret_val = ER_OK;

#if CAN_CFG_PARAM_CHECKING_ENABLE
    /* Parameter check */
    if (chan_num >= CAN_CHAN_MAX)
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        if (CAN_CHAN_CLOSED == CAN_IS_CHAN_OPEN(chan_num))
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = can_write(chan_num, ptr_msg);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_CAN_Write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_CAN_Control
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - CAN channel number to control
 *                  control_request - request to configure channel or get channel info.
 *                  can_ctrl - configuration data (to set or get).
 *
 *                  NOTE: API function checks that can_ctrl is non-zero.
 *                  The upper layer should check that the buffer lies within a valid address range.
 *
 *  Description:    Configure channel parameters, set transfer parameters or
 *                  get channel or transfer info, depending on control_request
 *
 **********************************************************************************************************************/
ER_RET R_CAN_Control (uint8_t chan_num, CAN_CONTROL_REQUEST_E control_request, void * ptr_can_ctrl)
{
    ER_RET ret_val = ER_OK;

#if CAN_CFG_PARAM_CHECKING_ENABLE
    if ((chan_num >= CAN_CHAN_MAX))
    {
        return ER_PARAM;
    }
#endif

    if (CAN_CONTROL_GET_CHAN_STATE != control_request)
    {
        /* All configuration should be performed while driver in the init state but the channel is closed */
        if (CAN_STATE_INIT != m_can_state)
        {
            return ER_INVAL;
        }
    }

    if ((CAN_CONTROL_GET_CHAN_STATE != control_request) && (CAN_CONTROL_SET_CHAN_RESET != control_request)
            && (CAN_CONTROL_CLEAR_CHAN_RESET != control_request))
    {
        if (CAN_CHAN_CLOSED == CAN_IS_CHAN_OPEN(chan_num))
        {
            return ER_INVAL;
        }
    }

    switch (control_request)
    {
        case CAN_CONTROL_SET_CHAN_CALLBACK:
            ret_val = can_register_channel_callback(chan_num, (can_event_callback_t) ptr_can_ctrl);
        break;

        case CAN_CONTROL_GET_CHAN_STATE:
            if (CAN_CHAN_CLOSED == CAN_IS_CHAN_OPEN(chan_num))
            {
                *(CAN_IF_STATE_E *) ptr_can_ctrl = CAN_STATE_CHANNEL_CLOSED;
            }
            else
            {
                *(CAN_IF_STATE_E *) ptr_can_ctrl = CAN_STATE_CHANNEL_OPEN;
            }
        break;

        case CAN_CONTROL_GET_CHAN_CONFIG:
            ret_val = can_get_channel_config(chan_num, (CAN_CONFIG_T *) ptr_can_ctrl);
        break;

        case CAN_CONTROL_SET_CHAN_RESET:
            can_reset_enter(chan_num);
        break;

        case CAN_CONTROL_CLEAR_CHAN_RESET:
            can_reset_exit(chan_num);
        break;

        case CAN_CONTROL_SET_CHAN_BITRATE:
            ret_val = can_set_bit_rate(chan_num, (CAN_BITRATE_T) ((uint32_t) ptr_can_ctrl));
        break;

        case CAN_CONTROL_SET_CHAN_FILTER:
            ret_val = can_set_filter(chan_num, ((CAN_FILTER_T *) ptr_can_ctrl));
        break;

        case CAN_CONTROL_START_CHAN_SYNC_PULSE:
            ret_val = can_sync_pulse_start(chan_num, (CAN_SYNC_PULSE_T *) ptr_can_ctrl);
        break;

        case CAN_CONTROL_STOP_CHAN_SYNC_PULSE:
            ret_val = can_sync_pulse_stop(chan_num);
        break;

        case CAN_CONTROL_GET_CHAN_STATS:
            ret_val = can_get_stats(chan_num, (CAN_STATS_T *) ptr_can_ctrl);
        break;

        case CAN_CONTROL_SET_TEST_MODE:
            ret_val = can_set_test_mode(chan_num, (CAN_TEST_MODE_T) ((uint32_t) ptr_can_ctrl));
        break;

        default:
            ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_CAN_Control
 **********************************************************************************************************************/
