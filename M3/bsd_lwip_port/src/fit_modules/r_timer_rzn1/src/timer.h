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
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  timer.h
 * Description  :  Timer definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef TIMER_H__
#define TIMER_H__

#define SYS_TIMER_DIVIDE        (3)                     /* System timer freqency divided by 2^n */
#define MIN_DMA_TIMER           (6)
#define MAX_INTERVAL_TICKS      (65535UL)              /* TimerLoadCount for Timer0 is 2-bytes i.e. max value is 65535 ticks. */
/* For 25MHz Time base, tick=40 nsecs. So max interval time = (65,000*40)nsecs = 2600,000 nsecs or 2.6 msecs  */
/* For 1MHz Time base, tick=1,000 nsecs. So max interval time = (65,000*1,000)nsecs = 65,000,000 nsecs or 65 msecs */
#define MIN_INTERVAL_TICKS      (1UL)                  /* Min interval time (ms) */

/***********************************************************************************************************************
 T Y P E  D E F
 **********************************************************************************************************************/
typedef void (*timer_interval_callback) (unsigned long interval_count);

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
void clock_init (void);
void sys_timer_start (void);
void sys_timer_stop (void);
ER_RET timer1_subtimer_init (uint8_t chan, uint8_t time_base);
ER_RET timer1_subtimer_dma_configure (uint8_t chan, uint8_t dma_chan);
void timer1_subtimer_dma_disable (uint8_t chan);
ER_RET timer1_subtimer_set_callback (uint8_t chan, timer_interval_callback callback_function);
ER_RET timer1_subtimer_start (uint8_t chan, uint32_t i_time);
ER_RET timer1_subtimer_stop (uint8_t chan);
ER_RET timer1_subtimer_delay (uint32_t chan, uint32_t delay_interval_count);
void systimer_delay (uint32_t usecs_delay);
#endif /* TIMER_H__ */
