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
 * FILE         :  r_qspi_rzn1.h
 * Description  :  QSPI driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_QSPI_RZN1_H__
#define R_QSPI_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_qspi_rzn1_if.h"

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/* 250MHz QSPI Ctrl clock. The driver divides to meet the requested
 * SPI clock. The sysctrl divider can divide by any number, whereas
 * the divider in the IP can only divide by even numbers.
 * Cadence recommend the IP divider is set to a minimum of 4 and the
 * SPI clock maximum is 62.5MHz. With this setting you can get SPI */

#define CONFIG_CQSPI_REF_CLK         (250000000)

/* Flash Erase block sizes */
#define QSPI_ERASE_BLOCK_SIZE_4K    (0x1000)
#define QSPI_ERASE_BLOCK_SIZE_32K   (0x8000)
#define QSPI_ERASE_BLOCK_SIZE_64K   (0x10000)
#define QSPI_ERASE_ALL_FLASH        (0xFFFFFFFF)

#define QSPI_FLASH_ADDR_LEN3                (3)
#define QSPI_FLASH_ADDR_LEN4                (4)
#define QSPI_FLASH_ERASE_COMMAND_LEN        (1 + QSPI_FLASH_ADDR_LEN4)
#define QSPI_FLASH_NO_ADDR_COMMAND_LEN      (1)
#define QSPI_FLASH_MAX_COMMAND_LEN          (QSPI_FLASH_ERASE_COMMAND_LEN)

/* Read commands */
#define QSPI_COMMAND_READ_ID                (0x9f)

/* Erase commands with 3 Address Bytes*/
#define QSPI_COMMAND_3ADDR_ERASE_SECTOR     (0x20)
#define QSPI_COMMAND_3ADDR_ERASE_32K        (0x52)
#define QSPI_COMMAND_3ADDR_ERASE_64K        (0xD8)

/* Erase commands with 4 Address Bytes*/
#define QSPI_COMMAND_4ADDR_ERASE_SECTOR     (0x21)
#define QSPI_COMMAND_4ADDR_ERASE_32K        (0x5C)
#define QSPI_COMMAND_4ADDR_ERASE_64K        (0xDC)

/* Write commands */
#define QSPI_COMMAND_WRITE_STATUS        (0x01)
#define QSPI_COMMAND_PAGE_PROGRAM        (0x02)
#define QSPI_COMMAND_WRITE_DISABLE       (0x04)
#define QSPI_COMMAND_READ_STATUS         (0x05)
#define QSPI_COMMAND_QUAD_PAGE_PROGRAM   (0x32)
#define QSPI_COMMAND_WRITE_ENABLE        (0x06)

#define QSPI_IDLE_RETRY                     (3)       /* number of retries to confirm QSPI idle */

/* Timeout values */
#define FLASH_PROGRAM_TIMEOUT       (2000ul)        /* 2 msecs  */
#define FLASH_PAGE_ERASE_TIMEOUT    (5000ul)        /* 5 msecs  */
#define FLASH_SECTOR_ERASE_TIMEOUT  (10000ul)       /* 10 msecs */

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
uint8_t qspi_get_major_version_num (void);
uint8_t qspi_get_minor_version_num (void);
void qspi_init (void);
void qspi_uninit (void);
ER_RET qspi_channel_open (uint8_t chan_num);
ER_RET qspi_channel_close (uint8_t chan_num);
ER_RET qspi_set_transfer_config (uint8_t chan_num, qspi_info_t *transfer_config);
ER_RET qspi_get_transfer_config (uint8_t chan_num, qspi_info_t *transfer_config);
ER_RET qspi_reset (uint8_t chan_num);
ER_RET qspi_read (uint8_t chan_num, uint32_t offset, uint8_t *buf, uint32_t block_len);
ER_RET qspi_erase (uint8_t chan_num, uint32_t erase_block_offset, uint32_t erase_size);
ER_RET qspi_write (uint8_t chan_num, uint32_t offset, uint8_t *buf, uint32_t block_len);

#endif /* R_QSPI_RZN1_H__ */
