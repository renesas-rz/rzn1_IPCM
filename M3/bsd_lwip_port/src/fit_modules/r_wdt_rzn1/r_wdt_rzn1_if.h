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
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_wdt_rzn1_if.h
 * Description  :  WDT (Watchdog Timer)control interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef R_WDT_RZN1_IF_H__
#define R_WDT_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/* Version Number of API. */
#define WDT_DRIVER_MAJOR_VERSION_NUMBER    (1)
#define WDT_DRIVER_MINOR_VERSION_NUMBER    (5)

/***********************************************************************************************************************
 Data Structures
 **********************************************************************************************************************/
typedef enum
{
    WDT_STATE_CLOSED = 0, /* WDT uninitialised */
    WDT_STATE_OPEN, /* WDT initialised and idle */
    WDT_STATE_BUSY /* WDT is curently counting */
} WDT_STATE;

typedef enum
{
    WDT_CLOCK_DIVIDE_2 = 0,
    WDT_CLOCK_DIVIDE_2EXP14 = 1
} WDT_PRESCALER;

typedef enum
{
    WDT_SYSTEM_RESET = 0,
    WDT_INTERRUPT
} WDT_OUTPUT;

typedef enum
{
    WDT_SET_PRESCALER,
    WDT_GET_PRESCALER,
    WDT_SET_RELOAD_VALUE,
    WDT_GET_RELOAD_VALUE,
    WDT_SET_OUTPUT,
    WDT_GET_OUTPUT,
    WDT_SET_CALLBACK
} WDT_CONTROL_REQUEST;

/* Call back function for interrupts */
typedef void (*wdt_callback) (void);

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/
void R_WDT_GetVersion (void *buf);
ER_RET R_WDT_Open (void);
ER_RET R_WDT_Control (WDT_CONTROL_REQUEST control_request, void *control);
ER_RET R_WDT_Start (void);
ER_RET R_WDT_Kick (void);
ER_RET R_WDT_Close (void);

#endif /* R_WDT_RZN1_IF_H__ */
