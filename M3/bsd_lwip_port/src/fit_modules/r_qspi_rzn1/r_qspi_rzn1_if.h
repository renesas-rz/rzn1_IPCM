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
 * $Revision: 1298 $
 * $Date: 2019-02-25 10:17:29 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_qspi_rzn1_if.h
 * Description  :  QSPI driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_QSPI_RZN1_IF_H__
#define R_QSPI_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
#define QSPI_CHAN_1         (0)

/* Version Number of API. */
#define QSPI_DRIVER_MAJOR_VERSION_NUMBER    (1)
#define QSPI_DRIVER_MINOR_VERSION_NUMBER    (5)

/* QSPI Channel States */
typedef enum
{
    QSPI_CHANNEL_STATE_CLOSED = 0, /* Channel uninitialised */
    QSPI_CHANNEL_STATE_OPEN, /* CHANNEL initialised and idle */
    QSPI_CHANNEL_STATE_BUSY /* Channel currently being used for Read or Write */
} QSPI_IF_CHANNEL_STATE_E;

/* QSPI Control Request */
typedef enum
{
    QSPI_CONTROL_GET_DRIVER_VERSION = 1, /* Get QSPI driver version */
    QSPI_CONTROL_SET_TRANSFER_CONFIG,
    QSPI_CONTROL_GET_TRANSFER_CONFIG,
    QSPI_CONTROL_GET_CHAN_STATE, /* Get channel state (see QSPI_IF_CHANNEL_STATE_E) */
    QSPI_CONTROL_RESET, /* Reset the QSPI channel */
} QSPI_CONTROL_REQUEST_E;

/* Enumeration for values of SPI operation mode. */
typedef enum e_qspi_opmode
{
    QSPI_OPMODE_SINGLE_SPI_WRITE = 0, /* Single-SPI mode for writing              */
    QSPI_OPMODE_SINGLE_SPI_READ, /* Single-SPI mode for reading              */
    QSPI_OPMODE_SINGLE_SPI_WRITEREAD, /* Single-SPI mode for writing and reading  */
    QSPI_OPMODE_DUAL_SPI, /* Dual-SPI mode                            */
    QSPI_OPMODE_QUAD_SPI /* Quad-SPI mode                            */
} QSPI_OPMODE_E;

/* Define for data transfer mode. */
typedef enum e_qspi_transfer_mode
{
    QSPI_TRANSFER_MODE_STIG = 0, /* Software Triggered Instruction Generator (STIP) required to access Config & Status SPI registers  & perform ERASE */
    QSPI_TRANSFER_MODE_DAC, /* Direct Access Controller, mem-mapped-AHB accesses directly trigger a read or write to flash memory */
    QSPI_TRANSFER_MODE_INDIRECT /* Indirect mode */
} QSPI_TRANSFER_MODE_E;

/* Define for QSPI Information structure type. */
typedef struct
{
        uint32_t page_size; /* Flash page size      */
        uint32_t sector_size; /* Flash sector size    */
        uint32_t flash_size; /* Flash total size     */
        QSPI_OPMODE_E op_mode; /* SPI operating mode   */
        QSPI_TRANSFER_MODE_E tran_mode; /* Data transfer mode   */
} qspi_info_t;

/***********************************************************************************************************************
 Global functions
 **********************************************************************************************************************/
void R_QSPI_GetVersion (void *buf);
void R_QSPI_Init (void);
void R_QSPI_Uninit (void);
ER_RET R_QSPI_Open (uint8_t chan_num);
ER_RET R_QSPI_Close (uint8_t chan_num);
ER_RET R_QSPI_Control (uint8_t chan_num, QSPI_CONTROL_REQUEST_E control_request, uint8_t *buf);
ER_RET R_QSPI_Read (uint8_t chan_num, uint32_t offset, uint8_t *buf, uint32_t block_len);
ER_RET R_QSPI_Erase (uint8_t chan_num, uint32_t erase_block_offset, uint32_t erase_size);
ER_RET R_QSPI_Write (uint8_t chan_num, uint32_t offset, uint8_t *buf, uint32_t block_len);

#endif /* R_QSPI_RZN1_IF_H__ */
