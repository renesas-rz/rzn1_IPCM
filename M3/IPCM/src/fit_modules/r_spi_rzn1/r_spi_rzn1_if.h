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
 * FILE         :  r_spi_rzn1_if.h
 * Description  :  SPI driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_SPI_RZN1_IF_H__
#define R_SPI_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define SPI_CHAN_1         (0)            /* SPI Channel 1 - Master */
#define SPI_CHAN_2         (1)            /* SPI Channel 2 - Master */
#define SPI_CHAN_3         (2)            /* SPI Channel 3 - Master */
#define SPI_CHAN_4         (3)            /* SPI Channel 4 - Master */
#define SPI_CHAN_5         (4)            /* SPI Channel 5 - Slave */
#define SPI_CHAN_6         (5)            /* SPI Channel 6 - Slave */

#define MASTER            (1)
#define SLAVE             (0)

/* Version Number of API. */
#define SPI_DRIVER_MAJOR_VERSION_NUMBER    (1)
#define SPI_DRIVER_MINOR_VERSION_NUMBER    (4)
/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/* SPI Channel States */
typedef enum
{
    SPI_CHANNEL_STATE_CLOSED = 0, /* Channel uninitialised */
    SPI_CHANNEL_STATE_OPEN, /* Channel initialised and idle */
    SPI_CHANNEL_STATE_BUSY /* Channel currently being used for Read or Write */
} spi_channel_state_t;

/* SPI Transfer mode */
typedef enum
{
    SPI_TRANSFER_MODE_BLOCKING = 0, /* Wait for rx or tx transfer to complete */
    SPI_TRANSFER_MODE_NON_BLOCKING, /* Invoke callback when rx or tx transfer has completed */
    SPI_TRANSFER_MODE_DMA, /* Same as non-blocking but data is written to or read from DMA channel */
} spi_transfer_mode_t;

/* SPI Transfer type */
typedef enum
{
    SPI_TRANSFER_TYPE_TX_RX = 0, /* Transmit and receive */
    SPI_TRANSFER_TYPE_TX = 1, /* Transmit only */
    SPI_TRANSFER_TYPE_RX = 2, /* Receive only */
} spi_transfer_type_t;

/* SPI Frame Format */
typedef enum
{
    spi_motorola = 0, /* Motorola SPI frame format */
    spi_texas_instruments = 1, /* Texas Instruments Synchronous Serial Protocol */
    spi_microwire = 2 /* National Semiconductor Microwire */
} spi_frame_format_t;

/* Motorola frame format serial clock phase */
typedef enum
{
    toggle_clk_mid_data_bit = 0, /* Serial clock toggles in middle of first data bit */
    toggle_clk_start_data_bit = 1 /* Serial clock toggles at start of first data bit */
} spi_motorola_clk_phase_t;

/* Motorola frame format serial clock polarity */
typedef enum
{
    clk_inactive_low = 0, /* Inactive state of serial clock is low */
    clk_inactive_high = 1 /* Inactive state of serial clock is high */
} spi_motorola_clk_pol_t;

/* SPI Motorola frame format config */
typedef struct
{
        spi_motorola_clk_phase_t clk_phase; /* serial clock phase */
        spi_motorola_clk_pol_t clk_polarity; /* serial clock polarity */
} spi_motorola_config_t;

/* Microwire frame format handshaking */
typedef enum
{
    microwire_handshaking_disabled = 0, /* handshaking interface is disabled */
    microwire_handshaking_enabled = 1 /* handshaking interface is enabled */
} spi_microwire_master_hs_t;

/* Microwire frame format transfer mode */
typedef enum
{
    microwire_non_sequential_trans = 0, /* Non-sequential transfer */
    microwire_sequential_trans = 1 /* Sequential transfer */
} spi_microwire_trans_mode_t;

/* Microwire frame format data direction */
typedef enum
{
    microwire_receive_data = 0, /* The data word is sent to the external device */
    microwire_send_data = 1 /* The data word is received from the external device */
} spi_microwire_data_dir_t;

/* SPI Microwire frame format config */
typedef struct
{
        uint8_t control_frame_size; /* Control frame size: 1-16 bits */
        spi_microwire_master_hs_t handshaking; /* Handshaking configuration */
        spi_microwire_data_dir_t data_direction; /* Data direction configuration */
        spi_microwire_trans_mode_t transfer_mode; /* Transfer mode configuration */
} spi_microwire_config_t;

/* SPI master channel config */
typedef struct
{
        uint32_t baudrate; /* Divides SPI_SCLK, values: (even numbers) between 2 and 65534 */
        uint8_t slave_select; /* Slave Select(0 to 3): Corresponds to SPI_SS_N lines [0:3] */
        uint8_t RXD_sample_delay; /* SPI MISO sample delay in unit of SPI_SCLK 0-64 */
} spi_master_channel_config_t;

/* SPI Channel configuration */
typedef struct
{
        uint8_t data_frame_size; /* Data frame size: 4-16 bits */
        spi_frame_format_t frame_format; /* SPI Frame Format */
        spi_motorola_config_t motorola_config; /* Motorola frame format config -- Ignored when frame format is not Motorola */
        spi_microwire_config_t microwire_config; /* Microwire frame format config -- Ignored when frame format is not Microwire */
        spi_master_channel_config_t master_config; /* SPI master channel config -- Ignored by slave channels */
} spi_channel_config_t;

/* SPI Required transfer information */
typedef struct
{
        uint16_t *read_buf; /* Where data received is stored */
        uint16_t *write_buf; /* Data to be written */

        /* Each element in the read/write buffers is assumed to equal the data frame size.
         Thus, it is the user's responsibility to right-justify write data in the write buffer */
        uint16_t data_frames; /* Number of data frames to read/write -- if DMA mode is used, this is limited to 8191 */
        spi_transfer_mode_t transfer_mode_rx; /* The transfer mode of the read */
        spi_transfer_mode_t transfer_mode_tx; /* The transfer mode of the write */
        spi_transfer_type_t transfer_type; /* The type of transfer being requested */
} spi_transfer_data_t;

/* SPI Transfer completion call-back function prototype */
typedef void
(*spi_transfer_complete_callback_t) (uint8_t chan_num);

/* SPI Control Request */
typedef enum
{
    SPI_CONTROL_SET_CALL_BACK, /* Set the call back function for SPI interrupts */
    SPI_CONTROL_SET_CHAN_CONFIG, /* Set channel configuration */
    SPI_CONTROL_GET_CHAN_CONFIG, /* Get channel configuration */
    SPI_CONTROL_RESERVE_DMA_CHAN_RX, /* Reserve a DMA channel for use with the SPI channel Rx transfers */
    SPI_CONTROL_RESERVE_DMA_CHAN_TX, /* Reserve a DMA channel for use with the SPI channel Tx transfers */
    SPI_CONTROL_RELEASE_DMA_CHAN_RX, /* Release any reserved DMA channels from the SPI channel Rx transfers */
    SPI_CONTROL_RELEASE_DMA_CHAN_TX, /* Release any reserved DMA channels from the SPI channel Tx transfers */
    SPI_CONTROL_GET_CHAN_STATE, /* Get channel state (see spi_channel_state_t) */
    SPI_CONTROL_CANCEL_TRANSFER /* Cancels an ongoing transfer */
} spi_cmd_t;

/***********************************************************************************************************************
 Default parameters
 **********************************************************************************************************************/
/* Default channel configuration */
extern const spi_channel_config_t default_spi_chan_config;

/***********************************************************************************************************************
 Global functions
 **********************************************************************************************************************/
void R_SPI_GetVersion (void *buf);
ER_RET R_SPI_Init (void);
void R_SPI_Uninit (void);
ER_RET R_SPI_Open (uint8_t chan_num, bool control);
ER_RET R_SPI_Close (uint8_t chan_num);
ER_RET R_SPI_Write (uint8_t chan_num, spi_transfer_data_t transfer_data);
ER_RET R_SPI_Read (uint8_t chan_num, spi_transfer_data_t transfer_data);
ER_RET R_SPI_ReadWrite (uint8_t chan_num, spi_transfer_data_t transfer_data);
ER_RET R_SPI_Control (uint8_t chan_num, spi_cmd_t control_request, void *spi_ctrl);

#endif /* R_SPI_RZN1_IF_H__ */
