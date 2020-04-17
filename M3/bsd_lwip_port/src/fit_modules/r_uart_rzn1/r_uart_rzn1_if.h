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
 * FILE         :  r_uart_rzn1_if.h
 * Description  :  UART driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
/*
 ********************************************************************************
 * Doxygen Summary block
 **********************************************************************************************************************/
/*!
 * @defgroup UART_MODULE RZN1 UART Bare Metal Driver
 * @{
 * @file
 * @brief UART Bare Metal Driver
 * @details Supports configuring, reading and writing UART port
 * @} */
/***********************************************************************************************************************
 * End of Doxygen Summary block
 **********************************************************************************************************************/

#ifndef R_UART_RZN1_IF_H__
#define R_UART_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define UART_CHAN_1         (0)
#define UART_CHAN_2         (1)
#define UART_CHAN_3         (2)
#define UART_CHAN_4         (3)
#define UART_CHAN_5         (4)
#define UART_CHAN_6         (5)
#define UART_CHAN_7         (6)
#define UART_CHAN_8         (7)

/* Version Number of API. */
#define UART_DRIVER_MAJOR_VERSION_NUMBER    (1)
#define UART_DRIVER_MINOR_VERSION_NUMBER    (7)
/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/*! UART Channel States */
typedef enum
{
    UART_CHANNEL_STATE_CLOSED = 0, /*!< Channel uninitialised */
    UART_CHANNEL_STATE_OPEN, /*!< CHANNEL initialised and idle */
    UART_CHANNEL_STATE_BUSY /*!< Channel currently being used for Read or Write */
} UART_IF_CHANNEL_STATE_E;

/*! UART transfer mode */
typedef enum
{
    UART_TRANSFER_MODE_BLOCKING = 1, /*!< Wait for rx or tx transfer to complete */
    UART_TRANSFER_MODE_NON_BLOCKING, /*!< Invoke callback when rx or tx transfer has completed */
    UART_TRANSFER_MODE_DMA, /*!< Same as non-blocking but data is written to or read from DMA channel
     - number of characters restricted to 8191 bytes max */
} UART_TRANSFER_MODE_E;

/*! UART Parity settings */
typedef enum
{
    UART_PARITY_NONE = 0, /*!< No parity */
    UART_PARITY_ODD, /*!< Odd parity */
    UART_PARITY_EVEN /*!< Even parity */
} UART_PARITY_E;

/*! UART Flow control settings */
typedef enum
{
    UART_FLOW_CONTROL_NONE = 0, /*!< No flow control */
    UART_FLOW_CONTROL_HW = 1 /*!< Hardware flow control */
} UART_FLOW_CONTROL_E;

/*! UART number of stop bits */
typedef enum
{
    NO_OF_STOP_BITS_1 = 0, /*!< 1 stop bits */
    NO_OF_STOP_BITS_2 = 1, /*!< 2 stop bits
     - If 5 bits per char, this is 1.5 stop bits */
} UART_STOP_BITS_E;

/*! UART number of data bits per character */
typedef enum
{
    DATA_BITS_PER_CHAR_5 = 0, /*!< 5 data bits per character */
    DATA_BITS_PER_CHAR_6 = 1, /*!< 6 data bits per character */
    DATA_BITS_PER_CHAR_7 = 2, /*!< 7 data bits per character */
    DATA_BITS_PER_CHAR_8 = 3, /*!< 8 data bits per character */
} UART_DATA_BITS_E;

/*! UART transfer complete callback */
/*! DMA transfer mode returns 0 for total_bytes_received */
typedef void (*uart_transfer_complete_callback_t) (uint8_t chan_num, uint32_t total_bytes_received);

/*! UART channel configuration */
typedef struct
{
        UART_PARITY_E parity; /*!< Parity configuration */
        UART_FLOW_CONTROL_E flow_control; /*!< Flow control */
        UART_STOP_BITS_E stopbits; /*!< Number of stop bits */
        UART_DATA_BITS_E databits; /*!< Number of data bits per character */
        uint32_t baudrate; /*!< Transfer baudrate */
} UART_CHANNEL_CONFIG_T;

/*! UART Control Request */
typedef enum
{
    UART_CONTROL_GET_DRIVER_VERSION = 1, /*!< Get UART driver version */
    UART_CONTROL_SET_CHAN_CONFIG, /*!< Set channel configuration parity, flow_control, stopbits, databits, baudrate */
    UART_CONTROL_GET_CHAN_CONFIG, /*!< Get channel configuration */
    UART_CONTROL_GET_CHAN_STATE, /*!< Get channel state (see UART_IF_CHANNEL_STATE_E) */
    UART_CONTROL_RESERVE_DMA_CHAN_RX, /*!< Reserve a DMA channel for the UART channel's Rx transfers */
    UART_CONTROL_RESERVE_DMA_CHAN_TX, /*!< Reserve a DMA channel for the UART channel's Tx transfers */
    UART_CONTROL_RELEASE_DMA_CHAN_RX, /*!< Release any DMA channel reserved for the UART channel's Rx transfers */
    UART_CONTROL_RELEASE_DMA_CHAN_TX, /*!< Release any DMA channel reserved for the UART channel's Rx transfers */
    UART_CONTROL_TRANSFER_CANCEL, /*!< Cancel current transfer */
    UART_CONTROL_RESET, /*!< Reset the UART channel */
} UART_CONTROL_REQUEST_E;

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/
/*!< Default channel configuration */
extern const UART_CHANNEL_CONFIG_T default_uart_chan_config;

/***********************************************************************************************************************
 Global functions
 **********************************************************************************************************************/
void R_UART_GetVersion (void *buf);
ER_RET R_UART_Init (void);
ER_RET R_UART_Open (uint8_t chan_num);
ER_RET R_UART_Control (uint8_t chan_num, UART_CONTROL_REQUEST_E control_request, uint8_t *buf);
ER_RET R_UART_Write (uint8_t chan_num, const uint8_t *buf, size_t *num_chars_ptr, UART_TRANSFER_MODE_E mode,
        uart_transfer_complete_callback_t tx_complete_callback);
ER_RET R_UART_Read (uint8_t chan_num, uint8_t *buf, size_t *num_chars_ptr, UART_TRANSFER_MODE_E mode,
        uart_transfer_complete_callback_t rx_complete_callback);
ER_RET R_UART_Close (uint8_t chan_num);

#endif /* R_UART_RZN1_IF_H__ */
