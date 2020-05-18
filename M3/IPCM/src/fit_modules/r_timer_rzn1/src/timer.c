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
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  timer.c
 * Description  :  Timer functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/

#include <time.h>
#include "r_sysctrl_rzn1_if.h"
#include "mcu_interrupts_if.h"
#include "timer.h"
#include "r_timer_rzn1_if.h"
#include "platform.h"
#include "iodefine.h"
#include "r_timer_rzn1_config.h"

#if r_dma_rzn1_timer_included
#include "r_dma_rzn1_if.h"
#endif
/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define timer_dma_index(_chan) \
    ((_chan) - MIN_DMA_TIMER)
/***********************************************************************************************************************
 Structures
 **********************************************************************************************************************/
#if r_dma_rzn1_timer_included

typedef struct
{
    uint8_t DMAC_number;
    uint8_t HS_Interface;
    uint8_t channel;
    bool dma_chan_reserved;
} timer_dma_info;

const uint8_t TIMER_DMA_REQ[(MAX_TIMER_CHANNEL - MIN_DMA_TIMER) + 1] = // @suppress("Source line ordering")
        { DMA_Timer1_SubTimer6_REQ, DMA_Timer1_SubTimer7_REQ };
#endif
/***********************************************************************************************************************
 Variables
 **********************************************************************************************************************/
static volatile uint32_t timer1_interval_count[MAX_TIMER_CHANNEL + 1];
static volatile uint32_t interrupt_interval_usecs[MAX_TIMER_CHANNEL + 1];
static volatile uint8_t timer1_time_base[MAX_TIMER_CHANNEL + 1];
static timer_interval_callback timer1_interval_callback[MAX_TIMER_CHANNEL + 1];
#if r_dma_rzn1_timer_included
static timer_dma_info timer_dma[(MAX_TIMER_CHANNEL - MIN_DMA_TIMER) + 1];
#endif
/***********************************************************************************************************************
 Externals
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
static void handle_timer0_interrupt (IRQn_Type *irq_num_ptr);
#if r_dma_rzn1_timer_included
static void timer_unpack_dma_info (timer_dma_info *dma_info, uint8_t dma_req_info);
#endif
/***********************************************************************************************************************
 * Function Name: clock_init
 * Description  : Initialize Clock.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void clock_init (void)
{
    /* Indicate to the interconnect that the slave is ready for Timer1 access */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG2_25MHZ.BIT.SLVRDY_R = 1;
    timer1_subtimer_init( SYS_TIMER_CHANNEL, TIMER_TIME_BASE_25MHz);
}
/***********************************************************************************************************************
 End of function clock_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: sys_timer_start
 * Description  : Start Baremetal Drivers System Timer -
 *                Timer block1 subtimer1 with interrupt tick time of 10usecs for RZ/N1 bare metal drivers.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void sys_timer_start (void)
{
    /* Start Timer Block1 sub-timer0  */
    (void) timer1_subtimer_start( SYS_TIMER_CHANNEL, 250); /* 250 ticks * 40 nsecs per tick gives an interval time of 10 usecs */
}
/***********************************************************************************************************************
 End of function sys_timer_start
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: sys_timer_stop
 * Description  : Stop Baremetal Drivers System Timer - Timer block1 subtimer1
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void sys_timer_stop (void)
{
    /* Stop Timer Block1 sub-timer0  */
    (void) timer1_subtimer_stop(SYS_TIMER_CHANNEL);
}
/***********************************************************************************************************************
 End of function sys_timer_stop
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: timer1_subtimer_init
 * Description  : Initialize interval timer, set initial interval timer counter
 *                and enable timer interrupts for subtimer 'chan' of timer block1
 * Arguments    : chan - channel number (i.e. sub-timer)
 *                time_base - either 1MHz or 25MHz
 * Return Value : ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET timer1_subtimer_init (uint8_t chan, uint8_t time_base)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num;
    uint32_t int_priority;

    R_SYSCTRL_EnableTimer();

    /* Check parameters */

    /* Set Control Mode */
    {
        volatile uint32_t *pr_reg;
        pr_reg = (uint32_t*) &(((volatile TIMER_Type *) RZN1_TIMER0_BASE)->rTimerControl_0.LONG);
        *(pr_reg + ((chan * 0x20) / (sizeof pr_reg))) = 0x0000000a | time_base; /* DMA channel disable,timer interrupt mask NOT masked (i.e. not disabled), Disable Timer, Auto re-load timer, Time base 25MHz or 1MHz */
        timer1_time_base[chan] = time_base; /* Save time base */
    }

    /* Set interrupt priority for Timer unit 0, Sub-timer chan & enable Timer0 interrupt */
    irq_num = RZN1_IRQ_TIMER0_0 + chan;

    if (R_BSP_InterruptRegisterCallback(irq_num, (bsp_int_cb_t) &handle_timer0_interrupt) == MCU_INT_SUCCESS)
    {
        int_priority = TIMER_DEFAULT_INT_PRIORITY;
        if (R_BSP_InterruptControl(irq_num, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority) != MCU_INT_SUCCESS)
        {
            ret_val = ER_SYS;
        }
        else
        {
            if (R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_ENABLE,
            FIT_NO_PTR) != MCU_INT_SUCCESS)
            {
                ret_val = ER_SYS;
            }
        }
    }
    else
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function timer1_subtimer_init
 **********************************************************************************************************************/

#if r_dma_rzn1_timer_included
/***********************************************************************************************************************
 * Function Name: timer_unpack_dma_info
 * Description  : Unpacks DMA information about the channel
 * Arguments    : dma_info - location to strore unpacked data
 *                dma_req_info - Packaged timer-DMA data
 * Return Value : None.
 **********************************************************************************************************************/
static void timer_unpack_dma_info (timer_dma_info *dma_info, uint8_t dma_req_info)
{
    dma_info->DMAC_number = (dma_req_info >> DMA_MUX_DMA_BIT) & DMA_MUX_DMA_MASK;
    dma_info->HS_Interface = (dma_req_info >> DMA_MUX_SRC_REQ_BIT) & DMA_MUX_SRC_REQ_MASK;
}
/***********************************************************************************************************************
 End of function timer_unpack_dma_info
 **********************************************************************************************************************/
#endif

/***********************************************************************************************************************
 * Function Name: timer1_subtimer_dma_configure
 * Description  : Unpacks DMA information about the channel
 * Arguments    : chan - channel number (i.e. sub-timer)
 *                dma_chan - DMA channel number
 * Return Value : ER_RET - Error status
 **********************************************************************************************************************/
ER_RET timer1_subtimer_dma_configure (uint8_t chan, uint8_t dma_chan)
{
    ER_RET ret_val = ER_OK;

    timer_unpack_dma_info( &timer_dma[timer_dma_index(chan)], TIMER_DMA_REQ[timer_dma_index(chan)]);

    /* OPEN REQUESTED DMA CHANNEL */
    if (ER_OK == (ret_val = R_DMA_Open(timer_dma[timer_dma_index(chan)].DMAC_number, dma_chan)))
    {
        timer_dma[timer_dma_index(chan)].channel = dma_chan;
        timer_dma[timer_dma_index(chan)].dma_chan_reserved = true;

        /* CONFIGURE HANDSHAKING - USE UNWRAPPING FUNCTION FROM SPI/UART */
        /* Set up DMA channel control */
        DMA_CHAN_CTRL dma_chan_ctrl = DMA_DEFAULT_CHAN_CTRL;
        dma_chan_ctrl.SRC_HS.TYPE = HARDWARE;
        dma_chan_ctrl.SRC_HS.HS_INTERFACE = timer_dma[timer_dma_index(chan)].HS_Interface;
        dma_chan_ctrl.DST_HS.TYPE = HARDWARE;
        dma_chan_ctrl.DST_HS.HS_INTERFACE = timer_dma[timer_dma_index(chan)].HS_Interface;
        ret_val = R_DMA_Control(timer_dma[timer_dma_index(chan)].DMAC_number, timer_dma[timer_dma_index(chan)].channel,
                DMA_CONTROL_SET_CHAN_CONFIG, &dma_chan_ctrl);

        /* SET DMA ENABLE IN CONTROL REGISTER */
        if (ER_OK == ret_val)
        {
            volatile uint32_t *pr_reg;
            pr_reg = (uint32_t*) &(((volatile TIMER_Type *) RZN1_TIMER0_BASE)->rTimerControl_0.LONG);
            ( *(pr_reg + ((chan * 0x20) / (sizeof pr_reg)))) |= 0x00000010;
        }

        /* LET USER DEAL WITH SETTING UP TRANSFER - MEM TO MEM,  SOURCE, DEST, BURST AND BLOCK SIZES */
        /* LOOK AT HOW THE DMA CHANNEL BEHAVES (MAYBE - MUST KEEP DMA CHANNEL OPEN) */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function timer1_subtimer_dma_configure
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: timer1_subtimer_dma_disable
 * Description  : disables DMA requests
 * Arguments    : chan - channel number (i.e. sub-timer)
 * Return Value : None.
 **********************************************************************************************************************/
void timer1_subtimer_dma_disable (uint8_t chan)
{
    volatile uint32_t *pr_reg;

    /* DMA DISABLE IN CONTROL REGISTER */
    pr_reg = (uint32_t*) &(((volatile TIMER_Type *) RZN1_TIMER0_BASE)->rTimerControl_0.LONG);
    ( *(pr_reg + ((chan * 0x20) / (sizeof pr_reg)))) &= ( ~(0x00000010));

    if (true == timer_dma[timer_dma_index(chan)].dma_chan_reserved)
    {
        /* CLOSE THE DMA CHANNEL ASSOCIATED WITH THIS TIMER CHANNEL */
        R_DMA_Close(timer_dma[timer_dma_index(chan)].DMAC_number, timer_dma[timer_dma_index(chan)].channel);
        timer_dma[timer_dma_index(chan)].dma_chan_reserved = false;
    }
}
/***********************************************************************************************************************
 End of function timer1_subtimer_dma_disable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: timer1_subtimer_register_callback
 * Description  : Register the timer callback function
 * Arguments    : chan - channel number (i.e. sub-timer)
 *                callback_function - callback function for interrupt handling
 * Return Value : ER_RET - Error status
 **********************************************************************************************************************/
ER_RET timer1_subtimer_set_callback (uint8_t chan, timer_interval_callback callback_function)
{
    ER_RET ret_val = ER_OK;

#if TIMER_CFG_PARAM_CHECKING_ENABLE
    /* Check parameter */
    if ((chan > MAX_TIMER_CHANNEL) || (FIT_NO_PTR == callback_function))
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        timer1_interval_callback[chan] = callback_function;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function timer1_subtimer_set_callback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name: timer1_subtimer_start
 * Description  : Set the interval time and start the interval timer counter
 * Arguments    : chan - channel number (i.e. sub-timer)
 *                i_time - interval time (ticks)
 * Return Value : ER_RET - Error status
 **********************************************************************************************************************/
ER_RET timer1_subtimer_start (uint8_t chan, uint32_t i_time)
{
    ER_RET ret_val = ER_OK;

    /* Set count value */
    {
        volatile uint32_t *cdr_reg;

        /* set base pointer */
        cdr_reg = (uint32_t*) &(((volatile TIMER_Type *) RZN1_TIMER0_BASE)->rTimerLoadCount_0.LONG);
        *(cdr_reg + ((chan * 0x20) / (sizeof cdr_reg))) = i_time - 1; /* [31:0] countdown start value */
    }

    /* Start the Timer  */
    {
        volatile uint32_t *pr_reg;

        timer1_interval_count[chan] = 0; /* initialise the intervals counter */
        if (TIMER_TIME_BASE_25MHz == timer1_time_base[chan])
        {
            interrupt_interval_usecs[chan] = (i_time * 40) / 1000; /* save current interrupt interval time in usecs */
        }
        else
        {
            interrupt_interval_usecs[chan] = i_time; /* save current interrupt interval time in usecs */
        }

        pr_reg = (uint32_t*) &(((volatile TIMER_Type *) RZN1_TIMER0_BASE)->rTimerControl_0.LONG);
        ( *(pr_reg + ((chan * 0x20) / (sizeof pr_reg)))) |= 0x00000004; /* Enable Timer */

    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function timer1_subtimer_start
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       timer1_subtimer_stop
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan - Timer channel number (i.e. sub-timer)
 *
 *  Description:    Stop the Timer for this Timer channel
 *
 **********************************************************************************************************************/
ER_RET timer1_subtimer_stop (uint8_t chan)
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
        /* Stop the Timer  */
        {
            volatile uint32_t *pr_reg;
            volatile uint32_t *ci_reg;

            volatile uint32_t read_val;
            pr_reg = (uint32_t*) &(((volatile TIMER_Type *) RZN1_TIMER0_BASE)->rTimerControl_0.LONG);
            ( *(pr_reg + ((chan * 0x20) / (sizeof pr_reg)))) &= 0xFFFFFFFB; /* Disable Timer */
            ci_reg = (uint32_t*) &(((volatile TIMER_Type *) RZN1_TIMER0_BASE)->rTimerClearInt_0.LONG);
            read_val = *(ci_reg + ((chan * 0x20) / (sizeof ci_reg))); /* bTimerClearInt */

            /* Clear callback function */
            timer1_interval_callback[chan] = 0;
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function timer1_subtimer_stop
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       systimer_delay
 *
 *  Return value:   None
 *
 *  Parameters:     usecs_delay - length of time to delay in usecs
 *
 *  Description:    Delay for given usecs time
 *
 *
 **********************************************************************************************************************/
void systimer_delay (uint32_t usecs_delay)
{
    uint32_t delay_in_int_intervals;
    uint32_t remainder;

    /* convert usecs to timer interrupt interval which is 10 usecs */
    delay_in_int_intervals = usecs_delay / interrupt_interval_usecs[SYS_TIMER_CHANNEL];
    remainder = usecs_delay % interrupt_interval_usecs[SYS_TIMER_CHANNEL];
    if (remainder)
    {
        delay_in_int_intervals++;
    }
    (void) timer1_subtimer_delay(SYS_TIMER_CHANNEL, delay_in_int_intervals);

    return;
}
/***********************************************************************************************************************
 End of function systimer_delay
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       timer1_subtimer_delay
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan - Timer channel number (i.e. sub-timer)
 *                  delay_interval_count - count of timer intervals to delay
 *
 *  Description:    Delay for delay_interval_count * timer interval of chan
 *
 *
 **********************************************************************************************************************/
ER_RET timer1_subtimer_delay (uint32_t chan, uint32_t delay_interval_count)
{
    ER_RET ret_val = ER_OK;
    uint32_t initial_interval_count;
    uint32_t final_interval_count;

    volatile uint32_t *pr_reg;

    /* Check Timer is running */
    pr_reg = (uint32_t*) &(((volatile TIMER_Type *) RZN1_TIMER0_BASE)->rTimerControl_0.LONG);
    if ((( *(pr_reg + ((chan * 0x20) / (sizeof pr_reg)))) & 0x00000004) == 0)
    {
        /* This sub-timer is not running */
        ret_val = ER_INVAL;
    }
    else
    {
        initial_interval_count = timer1_interval_count[chan];
        final_interval_count = initial_interval_count + delay_interval_count;
        if (final_interval_count > initial_interval_count)
        {
            while (timer1_interval_count[chan] < final_interval_count);
        }
        else
        {
            /* counter will wrap */
            while (timer1_interval_count[chan] > final_interval_count)
            {
                /* wait for interval counter to wrap */
                if (timer1_interval_count[chan] < initial_interval_count) /* Extra check in case timer1_interval_count[chan] misses reaching final_interval_count, e.g. if final_interval_count=0 */
                {
                    break;
                }
            }
            while (timer1_interval_count[chan] < final_interval_count);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function timer1_subtimer_delay
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       handle_timer0_interrupt
 *
 *  Return value:   none
 *
 *  Parameters:     irq_num_ptr - pointer to interrupt vector number
 *
 *  Description:    handle timer Interrupt for 'chan_num'
 *
 **********************************************************************************************************************/
static void handle_timer0_interrupt (IRQn_Type *irq_num_ptr)
{
    int32_t timer_chan_num;
    volatile uint32_t *ci_reg;
    volatile uint32_t read_val;

    IRQn_Type irq_num = *irq_num_ptr;

    if ((irq_num >= RZN1_IRQ_TIMER0_0) && (irq_num <= RZN1_IRQ_TIMER0_7))
    {
        timer_chan_num = irq_num - RZN1_IRQ_TIMER0_0;

        ci_reg = (uint32_t*) &(((volatile TIMER_Type *) RZN1_TIMER0_BASE)->rTimerClearInt_0.LONG);
        read_val = *(ci_reg + ((timer_chan_num * 0x20) / (sizeof ci_reg))); /* bTimerClearInt */

        timer1_interval_count[timer_chan_num]++;

        if (FIT_NO_PTR != timer1_interval_callback[timer_chan_num])
        {
            /* Callback */
            (timer1_interval_callback[timer_chan_num])(timer1_interval_count[timer_chan_num]);
        }
    }
}
/***********************************************************************************************************************
 End of function handle_timer0_interrupt
 **********************************************************************************************************************/
