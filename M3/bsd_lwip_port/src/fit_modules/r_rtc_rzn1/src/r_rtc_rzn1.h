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
 * FILE         :  r_rtc_rzn1.h
 * Description  :  RTC driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_RTC_RZN1_H__
#define R_RTC_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <time.h>
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define RTC_YEAR_MIN                            (2000)        /* RTC has a range of 0 - 99 so lets enforce input values of between 2000 and 2099 */
#define RTC_YEAR_MAX                            (2099)
#define TM_STRUCT_EPOCH                         (1900)

#ifndef RTC_WAIT_TIMEOUT_COUNT_uS
#define RTC_WAIT_TIMEOUT_COUNT_uS               (1000)
#endif
#ifndef RTC_WAIT_TIMEOUT_POLL_RATE_uS
#define RTC_WAIT_TIMEOUT_POLL_RATE_uS           (50)
#endif

#define RTC_SCMP_FREQ_MIN                       (32000)
#define RTC_SUBU_FREQ_MIN                       (-31)
#define RTC_SUBU_FREQ_MAX                       (31)

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
typedef enum
{
    RTC_HOURS_AMPM = 0, /* hours reported in am/pm mode */
    RTC_HOURS_24HR = 1, /* hours reported in 24 hour mode */
} RTC_HOURS_MODE_E;

typedef enum
{
    RTC_ALARM_EVENT = 0, RTC_PERIODIC_EVENT, RTC_ONE_SEC_EVENT,
} RTC_EVENT_E;

typedef enum
{
    RTC_PERIODIC_NONE = 0,
    RTC_PERIODIC_QTR_SEC = 1,
    RTC_PERIODIC_HALF_SEC = 2,
    RTC_PERIODIC_ONE_SEC = 3,
    RTC_PERIODIC_ONE_MIN = 4,
    RTC_PERIODIC_ONE_HOUR = 5,
    RTC_PERIODIC_ONE_DAY = 6,
    RTC_PERIODIC_ONE_MTH = 7,
} RTC_PERIODIC_EVENT_E;

typedef enum
{
    RTC_CLK_CALIB_NONE = 0, RTC_CLK_CALIB_FINE, RTC_CLK_CALIB_COARSE,
} RTC_CLOCK_CALIB_MODE_E;

typedef struct
{
        uint8_t minutes;
        uint8_t hours;

        union
        {
                uint8_t activeDays;

                struct
                {
                        bool sunday :1;
                        bool monday :1;
                        bool tuesday :1;
                        bool wednesday :1;
                        bool thursday :1;
                        bool friday :1;
                        bool saturday :1;
                };
        };
} RTC_ALARM_SETUP_T;

typedef struct
{
        int32_t clkFrequency;
        RTC_CLOCK_CALIB_MODE_E mode;
} RTC_CLOCK_CALIB_T;

typedef void (*rtc_event_callback_t) (RTC_EVENT_E event);

typedef struct
{
        RTC_EVENT_E eventType;
        rtc_event_callback_t callback;

        union
        {
                RTC_ALARM_SETUP_T alarmSetup;
                RTC_PERIODIC_EVENT_E periodicSetup;
        };
} RTC_CALLBACK_REQUEST_T;

typedef struct tm tm_t; /* typedef to avoid having to include struct keyword when a tm structure or point is defined */

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
uint8_t rtc_get_major_version_num (void);
uint8_t rtc_get_minor_version_num (void);
ER_RET rtc_init (void);
ER_RET rtc_uninitialise (void);
ER_RET rtc_open (void);
ER_RET rtc_close (void);
ER_RET rtc_read (tm_t * p_current);
ER_RET rtc_write (tm_t * p_current);
ER_RET rtc_register_event_callback (RTC_CALLBACK_REQUEST_T * pCallbackEvent);
ER_RET rtc_reset (void);
ER_RET rtc_set_clock_calib (RTC_CLOCK_CALIB_T * pCalibData);

#endif /* R_RTC_RZN1_H__ */
