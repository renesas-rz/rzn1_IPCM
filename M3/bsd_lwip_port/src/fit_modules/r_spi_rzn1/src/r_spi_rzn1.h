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
 * $Revision: 1217 $
 * $Date: 2019-02-05 17:13:23 +0000 (Tue, 05 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_spi_rzn1.h
 * Description  :  SPI driver definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_SPI_RZN1_H__
#define R_SPI_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_spi_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function prototypes
 **********************************************************************************************************************/
ER_RET spi_init (void);
void spi_uninit (void);

ER_RET spi_channelopen (uint8_t chan_num);
void spi_channelclose (uint8_t chan_num);

ER_RET spi_setchanconfig (uint8_t chan_num, spi_channel_config_t chan_config);
void spi_getchanconfig (uint8_t chan_num, spi_channel_config_t *chan_config);
ER_RET spi_registercallback (uint8_t chan_num, spi_transfer_complete_callback_t callback_function);

ER_RET spi_allocate_dma_rx_chan (uint8_t chan_num, uint8_t dma_chan);
ER_RET spi_allocate_dma_tx_chan (uint8_t chan_num, uint8_t dma_chan);
void spi_release_dma_rx_chan (uint8_t chan_num);
void spi_release_dma_tx_chan (uint8_t chan_num);

ER_RET spi_write (uint8_t chan_num, spi_transfer_data_t transfer_data);
ER_RET spi_read (uint8_t chan_num, spi_transfer_data_t transfer_data);
ER_RET spi_readwrite (uint8_t chan_num, spi_transfer_data_t transfer_data);
bool spi_istransferring (uint8_t chan_num);
void spi_transfer_cancel (uint8_t chan_num);
void spi_transfer_completed (uint8_t chan_num);
#endif /* R_SPI_RZN1_H__ */
