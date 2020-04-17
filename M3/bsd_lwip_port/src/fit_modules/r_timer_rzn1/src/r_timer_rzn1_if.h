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
 * $Revision: 1252 $
 * $Date: 2019-02-12 11:14:16 +0000 (Tue, 12 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_timer_rzn1_if.h
 * Description  :  Timer driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_TIMER_RZN1_IF_H__
#define R_TIMER_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "timer.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define MAX_TIMER_CHANNEL       (7)                     /* Max timer channel number */
#define SYS_TIMER_CHANNEL       (0)                     /* System timer channel (Sub-timer 0 of Timer Block 0)*/

/* Sub-timer definitions for Timer Blocks */
#define SUB_TIMER_CHANNEL0      (0)
#define SUB_TIMER_CHANNEL1      (1)
#define SUB_TIMER_CHANNEL2      (2)
#define SUB_TIMER_CHANNEL3      (3)
#define SUB_TIMER_CHANNEL4      (4)
#define SUB_TIMER_CHANNEL5      (5)
#define SUB_TIMER_CHANNEL6      (6)
#define SUB_TIMER_CHANNEL7      (7)

#define TIMER_TIME_BASE_1MHz    (1)
#define TIMER_TIME_BASE_25MHz   (0)
#define r_dma_rzn1_timer_included (1)

/* Defines for delay count in usecs */
#define ONE_USEC                (1)
#define TEN_USECS               (10)
#define ONE_HUNDRED_USECS       (100)
#define ONE_MSEC                (1000)

/* Version Number of API. */
#define TIMER_RZN1_VERSION_MAJOR           (1)
#define TIMER_RZN1_VERSION_MINOR           (2)
/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
//typedef void (*timer_interval_callback) (unsigned long interval_count);         // @suppress("Non-block comment")
/***********************************************************************************************************************
 Global functions
 **********************************************************************************************************************/
void R_TIMER_GetVersion (void *buf);
ER_RET R_TIMER_Init (uint8_t chan, uint8_t time_base, timer_interval_callback callback_function);
ER_RET R_TIMER_DMAConfigure (uint8_t chan, uint8_t dma_chan);
ER_RET R_TIMER_DMADisable (uint8_t chan);
ER_RET R_TIMER_Start (uint8_t chan, uint32_t i_time);
ER_RET R_TIMER_Stop (uint8_t chan);
void Delay_usec (uint32_t usecs_delay);
ER_RET R_TIMER_Delay (uint32_t chan, uint32_t delay_interval_count);

#endif /* R_TIMER_RZN1_IF_H__ */
