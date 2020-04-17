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
 * FILE         :  r_i2c_rzn1_if.h
 * Description  :  I2C driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_I2C_RZN1_IF_H__
#define R_I2C_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define I2C_CHAN_1         (0)
#define I2C_CHAN_2         (1)

#define I2C_CHAN_BASE_ADDR_INCREMENT    (RZN1_I2C2_BASE - RZN1_I2C1_BASE)

#define I2C_SPEED_STANDARD_MODE     (1)
#define I2C_SPEED_FAST_MODE         (2)

/* Version Number of API. */
#define I2C_DRIVER_MAJOR_VERSION_NUMBER     (1)
#define I2C_DRIVER_MINOR_VERSION_NUMBER     (7)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/* I2C Channel States */
typedef enum
{
    I2C_CHANNEL_STATE_CLOSED = 0, /* Channel uninitialised */
    I2C_CHANNEL_STATE_OPEN, /* CHANNEL initialised and idle */
    I2C_CHANNEL_STATE_BUSY /* Channel currently being used for Read or Write */
} I2C_IF_CHANNEL_STATE_E;

/* I2C Transfer States */
typedef enum
{
    I2C_TRANSFER_STATE_IDLE = 0, /* Not started */
    I2C_TRANSFER_STATE_IN_PROGRESS, I2C_TRANSFER_STATE_END, /* Transfer completed OK, transfer status not yet requested */
    I2C_TRANSFER_STATE_ERROR /* Transfer error, transfer status not yet requested */
} I2C_IF_TRANSFER_STATE_E;

/* I2C transfer mode */
typedef enum
{
    I2C_TRANSFER_MODE_BLOCKING = 1, /* Wait for rx or tx transfer to complete (I2C interrupt disabled) */
    I2C_TRANSFER_MODE_NON_BLOCKING, /* Invoke callback when rx or tx transfer has completed (I2C interrupt enabled )*/
} I2C_TRANSFER_MODE_E;

typedef struct
{
        I2C_TRANSFER_MODE_E transfer_mode; /* blocking or non-blocking i.e. interrupt disabled or enabled */
        uint32_t timeout_ms; /* max time to wait for data to be sent or received */
} i2c_transfer_config_t;

typedef struct
{
        /* I2C channel configuration */
        bool master; /* TRUE if master mode, FALSE if slave mode*/
        bool restart_enable; /* True if Restart conditions may be sent - Master mode only */
        uint8_t addr_mode; /* 0: 7-bit addressing. 1: 10-bit addressing */
        uint8_t addr_mode_response_slave; /* 0: responds to 7-bit addressing. 1: responds to 10-bit addressing - Slave mode only */
        uint8_t speed; /* 1: standard mode (100 kbits/sec). 2: fast mode (<= 400 kbits per sec) - Master mode only */
        uint32_t slave_addr; /* Slave address - Slave mode only */
} I2C_CHANNEL_CONFIG_T;

/* I2C Control Request */
typedef enum
{
    I2C_CONTROL_GET_DRIVER_VERSION, /* Get I2C Driver version */
    I2C_CONTROL_SET_CHAN_CONFIG, /* Set channel configuration */
    I2C_CONTROL_GET_CHAN_CONFIG, /* Get channel configuration */
    I2C_CONTROL_GET_CHAN_STATE, /* Get channel state (see I2C_IF_CHANNEL_STATE_E) */
    I2C_CONTROL_SET_COMPLETION_CALLBACK, /* Set I2C operation completion callback */
    I2C_CONTROL_RESET /* Reset the I2C channel */
} I2C_CONTROL_REQUEST_E;

/* Define for I2C Information structure type. */
typedef struct
{
        uint8_t *p_tx_data; /* Pointer to transmit data buffer */
        uint8_t *p_rx_data; /* Pointer to receive data buffer */
        uint32_t data_len; /* Number of byes to send or receive */
} i2c_info_t;

typedef void (*i2c_transfer_complete_callback_t) (uint8_t chan_num, uint32_t total_bytes);

/***********************************************************************************************************************
 Global functions
 **********************************************************************************************************************/
void R_I2C_GetVersion (void *buf);
ER_RET R_I2C_Init (void);
ER_RET R_I2C_Uninitialise (void);
ER_RET R_I2C_Open (uint8_t i2c_chan_num);
ER_RET R_I2C_Close (uint8_t i2c_chan_num);
ER_RET R_I2C_Control (uint8_t i2c_chan_num, I2C_CONTROL_REQUEST_E control_request, uint8_t *buf);
ER_RET R_I2C_Write (uint8_t i2c_chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len, I2C_TRANSFER_MODE_E mode);
ER_RET R_I2C_Read (uint8_t i2c_chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len, I2C_TRANSFER_MODE_E mode);

#endif /* R_I2C_RZN1_IF_H__ */
