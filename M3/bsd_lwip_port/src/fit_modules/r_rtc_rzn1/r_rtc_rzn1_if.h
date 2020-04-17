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
 * PROJECT NAME     :  RZ/N1 bare metal Drivers
 * FILE             :  r_rtc_rzn1_if.h
 * Description      :  RTC driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef    R_RTC_RZN1_IF_H__
#define    R_RTC_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_rtc_rzn1.h"
#include <time.h>

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/* Version Number of API. */
#define RTC_DRIVER_MAJOR_VERSION_NUMBER         (1)
#define RTC_DRIVER_MINOR_VERSION_NUMBER         (1)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/* RTC States */
typedef enum
{
    RTC_STATE_NOT_INIT = 0,                     /* RTC un-initialised */
    RTC_STATE_INIT,                             /* RTC initialised */
    RTC_STATE_OPEN,                             /* RTC open */
    RTC_STATE_CLOSED,                           /* RTC closed */
} RTC_IF_STATE_E;

/* RTC Control Request */
typedef enum
{
    RTC_CONTROL_GET_DRIVER_VERSION,             /* Get RTC Driver version */
    RTC_CONTROL_SET_CLOCK_CONFIG,               /* Set Clock configuration */
    RTC_CONTROL_GET_STATE,                      /* Get state (see RTC_IF_STATE_E) */
    RTC_CONTROL_SET_ALARM_CALLBACK,             /* Set RTC Alarm Callback */
    RTC_CONTROL_SET_PERIODIC_CALLBACK,          /* Set RTC One Second Callback */
    RTC_CONTROL_SET_ONE_SEC_CALLBACK,           /* Set RTC One Second Callback */
    RTC_CONTROL_RESET                           /* Reset the RTC */
} RTC_CONTROL_REQUEST_E;

/***********************************************************************************************************************
 Global functions
 **********************************************************************************************************************/
void R_RTC_GetVersion(void *buf);
ER_RET R_RTC_Init(void);
ER_RET R_RTC_Uninitialise(void);
ER_RET R_RTC_Open(void);
ER_RET R_RTC_Close(void);
ER_RET R_RTC_Control(RTC_CONTROL_REQUEST_E control_request, uint8_t *buf);
ER_RET R_RTC_Write(tm_t * p_current);
ER_RET R_RTC_Read(tm_t * p_current);

#endif /* R_RTC_RZN1_IF_H__ */
