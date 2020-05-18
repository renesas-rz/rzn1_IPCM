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
 * FILE         :  r_uart_rzn1.h
 * Description  :  UART driver definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_UART_RZN1_H__
#define R_UART_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_uart_rzn1_if.h"

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 UART registers
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
uint8_t uart_get_major_version_num (void);
uint8_t uart_get_minor_version_num (void);
ER_RET uart_driver_init (void);
ER_RET uart_channel_open (uint8_t chan_num);
ER_RET uart_channel_close (uint8_t chan_num);
ER_RET uart_set_chan_config (uint8_t chan_num, UART_CHANNEL_CONFIG_T channel_config);
ER_RET uart_get_chan_config (uint8_t chan_num, UART_CHANNEL_CONFIG_T *channel_config);
ER_RET uart_allocate_dma_rx_chan (uint8_t chan_num, uint8_t dma_chan);
ER_RET uart_allocate_dma_tx_chan (uint8_t chan_num, uint8_t dma_chan);
void uart_release_dma_rx_chan (uint8_t chan_num);
void uart_release_dma_tx_chan (uint8_t chan_num);
ER_RET uart_transfer_cancel (uint8_t chan_num);
ER_RET uart_reset (uint8_t chan_num);
ER_RET uart_sync_read (uint8_t chan_num, uint8_t* buf, size_t num_chars, size_t *num_chars_ptr);
ER_RET uart_sync_write (uint8_t chan_num, const uint8_t* buf, size_t num_chars, size_t *num_chars_ptr);
ER_RET uart_async_read (uint8_t chan_num, uint8_t *buf, size_t num_chars,
        uart_transfer_complete_callback_t rx_complete_callback);
ER_RET uart_async_write (uint8_t chan_num, const uint8_t *buf, size_t num_chars,
        uart_transfer_complete_callback_t tx_complete_callback);
ER_RET uart_dma_read (uint8_t chan_num, uint8_t *buf, size_t num_chars,
        uart_transfer_complete_callback_t rx_complete_callback);
ER_RET uart_dma_write (uint8_t chan_num, const uint8_t* buf, size_t num_chars,
        uart_transfer_complete_callback_t tx_complete_callback);
void rx_transfer_completed (uint8_t chan_num);
void tx_transfer_completed (uint8_t chan_num);

#endif /* R_UART_RZN1_H__ */
