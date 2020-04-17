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
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_can_rzn1.h
 * Description  :  CAN driver definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_CAN_RZN1_H__
#define R_CAN_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define CAN_CHAN_1                              (0)
#define CAN_CHAN_2                              (1)
#define CAN_CHAN_MAX                            (2)         /* Number of CAN modules */
#define CAN_DATA_LEN_MAX                        (8)

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/* CAN Events */
typedef enum
{
    CAN_EVENT_RX = 0,       /* Message Received */
    CAN_EVENT_TX,           /* Message Transmitted */
    CAN_EVENT_ERR_BUSOFF,   /* Bus is Off */
    CAN_EVENT_ERR_PASSIVE,  /* No acknowledge */
    CAN_EVENT_ERR_ACTIVE,   /* Bus OK */
    CAN_EVENT_ERR_OVERRUN   /* Receive message lost */
} CAN_EVENT_T;

/* CAN Bit-rate */
typedef enum
{
    CAN_BR_20_KBITS = 0,
    CAN_BR_50_KBITS = 1,
    CAN_BR_100_KBITS = 2,
    CAN_BR_125_KBITS = 3,
    CAN_BR_250_KBITS = 4,
    CAN_BR_500_KBITS = 5,
    CAN_BR_800_KBITS = 6,
    CAN_BR_1000_KBITS = 7,
    CAN_BR_INVALID = 8
} CAN_BITRATE_T;

/*
 * Test Mode: NOTE: CAN_TMODE_NONE must be set exclusively by itself.
 * All other values can be used in combination with each other
 */
typedef enum
{
    CAN_TMODE_NONE = 0,             /* No tests mode active */
    CAN_TMODE_TX_NACK_OK = 1,       /* TX requires no ACK to be seen as successful */
    CAN_TMODE_TX_SINGLE_SHOT = 2,   /* Do not attempt to repeat unsuccessful messages */
    CAN_TMODE_MONITOR_ONLY = 4,     /* Listen to messages on the bus without issuing an ACK */
    CAN_TMODE_SELF_RX = 8,          /* Receive own Tx messages */
} CAN_TEST_MODE_T;

typedef enum
{
    CAN_FRTR_LOW = 0,               /* Filter for non-RTR messages */
    CAN_FRTR_HIGH = 1,              /* Filter for RTR messages */
    CAN_FRTR_DONT_CARE = 2,         /* Don't care if RTR is set or not */
} CAN_FILTER_RTR_T;

typedef struct
{
    uint32_t id;                    /* Message identifier */
    bool rtr_flag;                  /* Remote Transmission requested */
    bool extended_flag;             /* Extended Identifier */
    uint16_t data_len;              /* Length of data */
    uint8_t data[CAN_DATA_LEN_MAX]; /* Message data */
} CAN_MSG_T;

typedef struct
{
    CAN_MSG_T sync_msg;             /* Definition of periodic synchronisation message (OpenCAN) */
    uint16_t sync_period_in_bits;   /* The period, in bit time, that synchronisation messages are sent */
} CAN_SYNC_PULSE_T;

typedef struct
{
    uint32_t accept;                /* 1st Acceptance Filter */
    uint32_t mask;                  /* 1st Acceptance Filter Mask (applied to the filter to mask out bits that are tested during the filtering */
    bool is_extended;               /* Defines if filter relates to extended or standard ID type messages */
    CAN_FILTER_RTR_T is_rtr;        /* Defines if also filtered on RTR flag */
} CAN_FILTER_T;

/* Various runtime metrics of a CAN Bus module */
typedef struct
{
    uint32_t tx_msgs_total;
    uint32_t tx_msgs_std;
    uint32_t tx_msgs_ext;
    uint32_t rx_msgs_total;
    uint32_t rx_msgs_std;
    uint32_t rx_msgs_ext;
    uint32_t bus_off_errors;
    uint32_t bus_passive_errors;
    uint32_t bus_active_errors;
    uint32_t data_overrun_errors;
} CAN_STATS_T;

typedef struct
{
    CAN_BITRATE_T bitrate;          /* Bit-rate of CAN module */
    CAN_FILTER_T filter;            /* Filter, if any, of CAN module */
    CAN_SYNC_PULSE_T sync_msg;      /* synchronisation pulse, if any, of CAN module */
    uint32_t test_mode;             /* Value can be combinations of enumerations in CAN_TEST_MODE_T */
} CAN_CONFIG_T;

/* CAN Event Callback Prototype */
typedef void (*can_event_callback_t)(uint8_t chan_num, CAN_EVENT_T event, CAN_MSG_T *ptr_msg);

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
ER_RET can_init(void);
ER_RET can_uninitialise(void);
ER_RET can_channel_open(uint8_t chan_num);
ER_RET can_channel_close(uint8_t chan_num);
ER_RET can_write(uint8_t chan_num, CAN_MSG_T * ptr_msg);
ER_RET can_get_channel_config(uint8_t chan_num, CAN_CONFIG_T * ptr_config);
ER_RET can_register_channel_callback(uint8_t chan_num, can_event_callback_t event_callback);
ER_RET can_set_bit_rate(uint8_t chan_num, CAN_BITRATE_T bitrate);
ER_RET can_set_filter(uint8_t chan_num, CAN_FILTER_T * ptr_filter);
ER_RET can_sync_pulse_start(uint8_t chan_num, CAN_SYNC_PULSE_T * ptr_sync_config);
ER_RET can_sync_pulse_stop(uint8_t chan_num);
ER_RET can_set_test_mode(uint8_t chan_num, CAN_TEST_MODE_T test_mode);
ER_RET can_get_stats(uint8_t chan_num, CAN_STATS_T * ptr_stats);
ER_RET can_reset_enter(uint8_t chan_num);
ER_RET can_reset_exit(uint8_t chan_num);

#endif /* R_CAN_RZN1_H__ */
