/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer *
* Copyright (C) 2017-2018 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/**
 *******************************************************************************
 * @file  kernel_id.h
 * @brief HW-RTOS kernel configuration file
 *******************************************************************************
 */

#ifndef	KERNEL_ID_H__
#define	KERNEL_ID_H__

/*============================================================================*/
/* I N C L U D E                                                              */
/*============================================================================*/
#include "kernel.h"

/*============================================================================*/
/* D E F I N E                                                                */
/*============================================================================*/
// --- Task ID ---
// To make CPU load per task simple the IDs of the HW-RTOS task in static_task_table should be
// in the ascending order starting from ONE (1)
// ID_TASK_MAX_STATIC should be ALWAYS updated after adding a new task to static_task_table
#define ID_TASK_INIT        1
#define ID_TASK_PL320_RX    2
#define ID_TASK_PL320_TX    3
#define ID_MONITOR_TASK     4
#define ID_TASK_IDLE        5


// --- Eventflag ID ---
#define ID_FLG_PL320_IRQ    1


#endif // KERNEL_ID_H__
