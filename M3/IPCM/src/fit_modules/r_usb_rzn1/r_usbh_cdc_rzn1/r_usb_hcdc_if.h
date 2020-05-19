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
 * $Revision: 1297 $
 * $Date: 2019-02-22 17:18:43 +0000 (Fri, 22 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hcdc_if.h
 * Description  :  Interface file for USB CDC class API
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef _USB_HCDC_IF_H
#define _USB_HCDC_IF_H

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_usb_basic_if.h"
#include "r_usb_hcdc_config.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/* Serial State message Length */
#define USB_HCDC_SERIAL_STATE_MSG_LEN   10

/***********************************************************************************************************************
 Enumerated Types
 **********************************************************************************************************************/
typedef enum
{
    USB_HCDC_DATA_BIT_7         = 7u,   /* Line Coding 7Data bits */
    USB_HCDC_DATA_BIT_8         = 8u    /* Line Coding 8Data bits */
} USB_HCDC_DATA_BIT_t;

typedef enum
{
    USB_HCDC_STOP_BIT_1         = 0u,   /* Line Coding 1Stop bits */
    USB_HCDC_STOP_BIT_15        = 1u,   /* Line Coding 1.5Stop bits */
    USB_HCDC_STOP_BIT_2         = 2u    /* Line Coding 2Stop bits */
} USB_HCDC_STOP_BIT_t;

typedef enum
{
    USB_HCDC_PARITY_BIT_NONE    = 0u,   /* Line Coding None Parity */
    USB_HCDC_PARITY_BIT_ODD     = 1u,   /* Line Coding Odd Parity */
    USB_HCDC_PARITY_BIT_EVEN    = 2u    /* Line Coding Even Parity */
} USB_HCDC_PARITY_BIT_t;

typedef enum
{
    USB_HCDC_SPEED_1200         = 1200u,    /* Line Coding 1200bps */
    USB_HCDC_SPEED_2400         = 2400u,    /* Line Coding 2400bps */
    USB_HCDC_SPEED_4800         = 4800u,    /* Line Coding 4800bps */
    USB_HCDC_SPEED_9600         = 9600u,    /* Line Coding 9600bps */
    USB_HCDC_SPEED_14400        = 14400u,   /* Line Coding 14400bps */
    USB_HCDC_SPEED_19200        = 19200u,   /* Line Coding 19200bps */
    USB_HCDC_SPEED_38400        = 38400u,   /* Line Coding 38400bps */
    USB_HCDC_SPEED_57600        = 57600u,   /* Line Coding 57600bps */
    USB_HCDC_SPEED_115200       = 115200u   /* Line Coding 115200bps */
} USB_HCDC_LINE_SPEED_t;

/***********************************************************************************************************************
 Struct definition
 **********************************************************************************************************************/
typedef struct
{
    uint32_t    dwDTERate;      /* Data terminal rate, in bits per second */
    uint8_t     bCharFormat;    /* Stop bits */
    uint8_t     bParityType;    /* Parity */
    uint8_t     bDataBits;      /* Data bits */
    uint8_t     rsv;            /* Reserve */
} USB_HCDC_LineCoding_t;

typedef struct
{
    uint16_t    bDTR:1;         /* DTR */
    uint16_t    bRTS:1;         /* RTS */
    uint16_t    rsv:14;         /* Reserve */
} USB_HCDC_ControlLineState_t;

typedef struct
{
    uint16_t    bRxCarrier:1;   /* DCD signal */
    uint16_t    bTxCarrier:1;   /* DSR signal */
    uint16_t    bBreak:1;       /* State of break detection mechanism of the device */
    uint16_t    bRingSignal:1;  /* State of ring signal detection of the device */
    uint16_t    bFraming:1;     /* Framing error */
    uint16_t    bParity:1;      /* Parity error */
    uint16_t    bOverRun:1;     /* Over Run error */
    uint16_t    rsv:9;          /* Reserve */
} USB_HCDC_SerialState_t;

typedef struct
{
    char        product_id[USB_STR_MAX_LENGTH+1];                   /* Product ID string: buffer to store 'C' type string after converting from UTF */
    char        manufacturer_id[USB_STR_MAX_LENGTH+1];              /* Manufacturer ID string: buffer to store 'C' type string after converting from UTF */
    char        serial_num[USB_STR_MAX_LENGTH+1];                   /* Serial Number string: buffer to store 'C' type string after converting from UTF */
}
USB_HCDC_Strings_t;

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
void        R_usb_hcdc_task(void);
void        R_usb_hcdc_class_check(uint16_t **table);
void        R_usb_hcdc_driver_start(void);
USB_ER_t    R_usb_hcdc_receive_data( uint16_t pipe_id, uint8_t *table, uint32_t size, USB_UTR_CB_t complete );
USB_ER_t    R_usb_hcdc_send_data(uint16_t pipe_id, uint8_t *table, uint32_t size, USB_UTR_CB_t complete );
const USB_HCDC_Strings_t * R_usb_hcdc_get_strings(void);
USB_ER_t    R_usb_hcdc_serial_state_trans( uint16_t pipe_id, uint8_t *table, USB_UTR_CB_t complete );
/* Class Request functions */
USB_ER_t    R_usb_hcdc_set_line_coding( uint16_t devadr, USB_HCDC_LineCoding_t *p_linecoding, USB_UTR_CB_t complete );
USB_ER_t    R_usb_hcdc_get_line_coding( uint16_t devadr, USB_HCDC_LineCoding_t *p_linecoding, USB_UTR_CB_t complete );
USB_ER_t    R_usb_hcdc_set_control_line_state( uint16_t devadr, uint16_t dtr, uint16_t rts, USB_UTR_CB_t complete );
USB_ER_t    R_usb_hcdc_send_break( uint16_t devadr, uint16_t break_period_ms, USB_UTR_CB_t complete );

#endif /* _USB_HCDC_IF_H */
