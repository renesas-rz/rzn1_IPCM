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
 * FILE         :  r_timer_rzn1_if.c
 * Description  :  TIMER driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include "platform.h"
#include "r_timer_rzn1_if.h"

/***********************************************************************************************************************
 * Function Name: R_TIMER_GetVersion
 * Description  : Returns the current version of this module.
 * Arguments    : buf - Pointer to buffer for version information
 * Return Value : Version of this module.
 **********************************************************************************************************************/
void R_TIMER_GetVersion (void *buf)
{
    /* These version macros are defined in r_timer_rzn1_if.h. */
    ((uint8_t *) buf)[1] = (uint8_t)TIMER_RZN1_VERSION_MAJOR;
    ((uint8_t *) buf)[0] = (uint8_t)TIMER_RZN1_VERSION_MINOR;
}
/***********************************************************************************************************************
 End of function R_TIMER_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_Timer_Init
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan - channel number (i.e. sub-timer)
 *                  time_base - time base for the Timer channel
 *                  callback_function - interrupt callback function
 *
 *  Description:    Initialize interval timer, set initial interval timer counter
 *                and enable timer interrupts for subtimer 'chan' of timer block1
 *
 *
 **********************************************************************************************************************/

ER_RET R_TIMER_Init (uint8_t chan, uint8_t time_base, timer_interval_callback callback_function)
{
    ER_RET ret_val = ER_OK;

#if TIMER_CFG_PARAM_CHECKING_ENABLE
    if ((chan > MAX_TIMER_CHANNEL) || (time_base > TIMER_TIME_BASE_1MHz))
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        /* Initialise timer */
        ret_val = timer1_subtimer_init(chan, time_base);

        if(ER_OK == ret_val)
        {
            /* Register callback for timer interrupt handler */
            ret_val = timer1_subtimer_set_callback(chan, callback_function);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_TIMER_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_TIMER_DMAConfigure
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan - channel number (i.e. sub-timer)
 *                  dma_chan - DMA channel number
 *
 *  Description:    Unpacks DMA information about the channel
 *
 *
 **********************************************************************************************************************/

ER_RET R_TIMER_DMAConfigure (uint8_t chan, uint8_t dma_chan)
{
    ER_RET ret_val = ER_OK;
#if r_dma_rzn1_timer_included

#if TIMER_CFG_PARAM_CHECKING_ENABLE
    /* PARAM CHECK FOR DMA SUPPORT */
    if (chan < MIN_DMA_TIMER)
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        ret_val = timer1_subtimer_dma_configure(chan, dma_chan);
    }
#else
    ret_val = ER_INVAL;
#endif

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_TIMER_DMAConfigure
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_TIMER_DMADisable
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan - Timer channel number (i.e. sub-timer)
 *
 *  Description:    Disables DMA requests
 *
 **********************************************************************************************************************/

ER_RET R_TIMER_DMADisable (uint8_t chan)
{
    ER_RET ret_val = ER_OK;
#if r_dma_rzn1_timer_included

    timer1_subtimer_dma_disable(chan);
#else
    ret_val = ER_INVAL;
#endif

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_TIMER_DMADisable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_TIMER_Start
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan - Timer channel number (i.e. sub-timer)
 *                  i_time - interval time (ticks)
 *  Description:    Start the Timer for this Timer channel
 *
 **********************************************************************************************************************/

ER_RET R_TIMER_Start (uint8_t chan, uint32_t i_time)
{
    ER_RET ret_val = ER_OK;

#if TIMER_CFG_PARAM_CHECKING_ENABLE
    /* Check parameter */
    if (chan > MAX_TIMER_CHANNEL)
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        if ((i_time < MIN_INTERVAL_TICKS) || (MAX_INTERVAL_TICKS < i_time))
        {
            ret_val = ER_PARAM;
        }
        else
        {
            /* Start the Timer */
            timer1_subtimer_start(chan, i_time);
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_TIMER_Start
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_TIMER_Stop
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan - Timer channel number (i.e. sub-timer)
 *
 *  Description:    Stop the Timer for this Timer channel
 *
 **********************************************************************************************************************/

ER_RET R_TIMER_Stop (uint8_t chan)
{
    ER_RET ret_val = ER_OK;

#if TIMER_CFG_PARAM_CHECKING_ENABLE
    /* Check parameter */
    if (chan > MAX_TIMER_CHANNEL)
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        /* Stop the Timer */
        timer1_subtimer_stop(chan);

    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_TIMER_Stop
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       Delay_usec
 *
 *  Return value:   None
 *
 *  Parameters:     usecs_delay - time delay in usecs
 *
 *
 *  Description:    Timer delay using SYS_TIMER_CHANNEL
 *
 *
 **********************************************************************************************************************/

void Delay_usec (uint32_t usecs_delay)    // @suppress("Non-API function naming")
{
    systimer_delay(usecs_delay);
}
/***********************************************************************************************************************
 End of function Delay_usec
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_TIMER_Delay
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan - Timer channel number (i.e. sub-timer)
 *                  delay_interval_count - count of timer intervals to delay
 *
 *  Description:    Timer delay on a specific channel
 *                  If time base is 1MHz then 1 interval count will represent 1us
 *                  If time base is 25MHz then 1 interval count will represent 40ns
 **********************************************************************************************************************/
ER_RET R_TIMER_Delay (uint32_t chan, uint32_t delay_interval_count)
{
    ER_RET ret_val = ER_OK;

#if TIMER_CFG_PARAM_CHECKING_ENABLE
    /* Check parameter */
    if (chan > MAX_TIMER_CHANNEL)
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        ret_val = timer1_subtimer_delay(chan, delay_interval_count);
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_TIMER_Delay
 **********************************************************************************************************************/
