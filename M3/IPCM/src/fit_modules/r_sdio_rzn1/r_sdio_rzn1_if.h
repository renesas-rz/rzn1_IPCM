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
 * PROJECT NAME :    RZ/N1 bare metal Drivers
 * FILE                 :    r_sdio_rzn1_if.h
 * Description    :    SDIO/SD/eMMC Controller control interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef R_SDIO_RZN1_IF_H__
#define R_SDIO_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define SDIO_0 (0)
#define SDIO_1 (1)

/* Version Number of API. */
#define SDIO_DRIVER_MAJOR_VERSION_NUMBER    (1)
#define SDIO_DRIVER_MINOR_VERSION_NUMBER    (6)

#define R1_ERROR_BITS_MASK         (0xFFF90000)    /* Error bits of R1 response */

/*                   Interrupt statuses                    */
/* Normal Interrupts */
#define SD_CMD_COMPLETE         (0x01u)
#define SD_TRANS_COMPLETE       (0x01u<<1u)
#define SD_BLOCK_GAP_EVENT      (0x01u<<2u)
#define SD_DMA_INT              (0x01u<<3u)
#define SD_BUF_WRITE_READY      (0x01u<<4u)
#define SD_BUF_READ_READY       (0x01u<<5u)
#define SD_CARD_INSERTED        (0x01u<<6u)
#define SD_CARD_REMOVED         (0x01u<<7u)
#define SD_CARD_INTERRUPT       (0x01u<<8u)
#define SD_ERROR                (0x01u<<15u)

/*              Error Interrupts */
#define SD_ERR_CMD_TIMEOUT      (0x01u)
#define SD_ERR_CMD_CRC          (0x01u<<1u)
#define SD_ERR_CMD_END_BIT      (0x01u<<2u)
#define SD_ERR_CMD_INDEX        (0x01u<<3u)
#define SD_ERR_DATA_TIMEOUT     (0x01u<<4u)
#define SD_ERR_DATA_CRC         (0x01u<<5u)
#define SD_ERR_DATA_END_BIT     (0x01u<<6u)
#define SD_ERR_CURRENT_LIM      (0x01u<<7u)
#define SD_ERR_AUTO_CMD         (0x01u<<8u)
#define SD_ERR_ADMA             (0x01u<<9u)
#define SD_ERR_HOST             (0x01u<<12u)

/* CMD index abbreviations */
#define GO_IDLE_STATE           (0u)    /*Software reset.*/
#define ALL_SEND_CID            (2u)    /*Asks any car to send the CID numbers on the CMD line*/
#define SEND_RELATIVE_ADDR      (3u)    /*Ask the card to publish a new relative address (RCA)*/
#define SET_DSR                 (4u)
#define SWITCH_FUNC             (6u)
#define SELECT_DESELECT_CARD    (7u)    /*Toggles a card between the stand-by and transfer states or between the programming and disconnect states*/
#define SEND_IF_COND            (8u)    /*For only SDC V2. Check voltage range.*/
#define SEND_CSD                (9u)    /*Read CSD register.*/
#define SEND_CID                (10u)   /*  Stop to read data.*/
#define VOLTAGE_SWITCH          (11u)   /*Change R/W block size.*/
#define STOP_TRANSMISSION       (12u)
#define SEND_STATUS             (13u)
#define GO_INACTIVE_STATE       (15u)
#define SET_BLOCKLEN            (16u)
#define READ_SINGLE_BLOCK       (17u)   /* Read a block*/
#define READ_MULTIPLE_BLOCK     (18u)   /*Read multiple blocks*/
#define SEND_TUNING_BLOCK       (19u)
#define SPEED_CLASS_CONTROL     (20u)
#define SET_BLOCK_COUNT         (23u)
#define WRITE_BLOCK             (24u)   /*Write a block*/
#define WRITE_MULTIPLE_BLOCK    (25u)   /*Write multiple blocks.*/
#define PROGRAM_CSD             (27u)
#define SET_WRITE_PROT          (28u)
#define CLR_WRITE_PROT          (29u)
#define SEND_WRITE_PROT         (30u)
#define ERASE_WR_BLK_START      (32u)
#define ERASE_WR_BLK_END        (33u)
#define ERASE                   (38u)
#define LOCK_UNLOCK             (42u)
#define APP_CMD                 (55u)   /*Leading command of ACMD<n> command.*/
#define GEN_CMD                 (56u)

/* ACMD index abbreviations */
#define SET_BUS_WIDTH           (6u)
#define SD_STATUS               (13u)   /*Addressed card sends its status register*/
#define SEND_NUM_WR_BLOCKS      (22u)
#define SET_WR_BLK_ERASE_COUNT  (23u)
#define APP_SEND_OP_COND        (41u)   /*For only SDC. Initiate initialization process.*/
#define SET_CLR_CARD_DETECT     (42u)
#define SEND_SCR                (51u)   /* Send ACMD51 to get the SCR */

/***********************************************************************************************************************
 Data Structures
 **********************************************************************************************************************/
/* SDIO Host controller state */
typedef enum
{
    SDIO_STATE_CLOSED = 0, /* Controller uninitialised */
    SDIO_STATE_OPEN, /* Initialised controller, not busy */
    SDIO_STATE_BUSY /* Initialised and busy controller */
} SDIO_STATE;

/* Clock dividers for external SD clock - Base frequency = 50MHz */
typedef enum
{
    SDIO_CLK_DIV_2046 = 11, /* Base frequency / 2046*/
    SDIO_CLK_DIV_1024 = 10, /* Base frequency / 1024*/
    SDIO_CLK_DIV_512 = 9, /* Base frequency / 512*/
    SDIO_CLK_DIV_256 = 8, /* Base frequency / 256*/
    SDIO_CLK_DIV_128 = 7, /* Base frequency / 128*/
    SDIO_CLK_DIV_64 = 6, /* Base frequency / 64*/
    SDIO_CLK_DIV_32 = 5, /* Base frequency / 32*/
    SDIO_CLK_DIV_16 = 4, /* Base frequency / 16*/
    SDIO_CLK_DIV_8 = 3, /* Base frequency / 8*/
    SDIO_CLK_DIV_4 = 2, /* Base frequency / 4*/
    SDIO_CLK_DIV_2 = 1, /* Base frequency / 2*/
    SDIO_CLK_DIV_BASE_FREQ = 0 /* Base frequency */
} SDIO_CLK_DIV;

/* Command response type */
typedef enum
{
    SDIO_RESPONSE_NONE, /* No response */
    SDIO_RESPONSE_R1, /* Resopnse: R1 */
    SDIO_RESPONSE_R1b, /* Resopnse: R1b */
    SDIO_RESPONSE_R2, /* Resopnse: R2 */
    SDIO_RESPONSE_R3, /* Resopnse: R3 */
    SDIO_RESPONSE_R4, /* Resopnse: R4 */
    SDIO_RESPONSE_R5, /* Resopnse: R5 */
    SDIO_RESPONSE_R5b, /* Resopnse: R5b */
    SDIO_RESPONSE_R6, /* Resopnse: R6 */
    SDIO_RESPONSE_R7 /* Resopnse: R7 */
} SDIO_RESPONSE_TYPE;

/* Direction of data in transfer */
typedef enum
{
    SDIO_WRITE = 0, /* Write to card */
    SDIO_READ = 1 /* Read from card */
} SDIO_DIRECTION;

/* Data transfer width */
typedef enum
{
    SDIO_WIDTH_1_BIT, /* 1-bit mode */
    SDIO_WIDTH_4_BIT, /* 4-bit mode */
    SDIO_WIDTH_8_BIT /* 8-bit mode <- for embedded devices only */
} SDIO_TRANS_WIDTH;

/* Type of issued command to the card */
typedef enum
{
    SDIO_CMD_NON_DATA = 0, /* Data line not used with command */
    SDIO_CMD_DATA = 1 /* Command uses data line */
} SDIO_COMMAND_TYPE;

/* Card type */
typedef enum
{
    SD, /* SDSC card */
    SDHC_SDXC, /* SDHC or SDXC */
    SDIO, /* SDIO card */
    MMC, /* eMMC */
    INVALID_CARD /* Unknown card type */
} SDIO_CARD_TYPE;

/* SD card physical spec. version */
typedef enum
{
    Version_1_0, /* SD physical spec. ver. 1.00 and 1.01 */
    Version_1_1, /* SD physical spec. ver. 1.10 */
    Version_2, /* SD physical spec. ver. 2.00 */
    Version_3, /* SD physical spec. ver. 3.0x */
    Version_4, /* SD physical spec. ver. 4.xx */
    Version_5, /* SD physical spec. ver. 5.xx */
    Version_6, /* SD physical spec. ver. 6.xx */
    Version_Unknown /* Unknown SD physical spec. version */
} SDIO_CARD_VERSION;

/* Information about the card sent by the card */
typedef struct
{
        uint32_t OCR; /* Operating Conditions Register */
        uint32_t RCA; /* Relative Card Address */
        uint32_t CID[4]; /* Card ID Numbers */
        uint32_t CSD[4]; /* Card specific data */
        uint32_t SCR[2]; /* SD Config Register */
        SDIO_CARD_VERSION Card_Version; /* physical spec version */
} SDIO_CARD_PARAMETERS;

/* SDIO control request */
typedef enum
{
    SDIO_CONTROL_GET_DRIVER_VERSION, /* Get the driver version number */
    SDIO_CONTROL_SEND_CMD, /* Send a command */
    SDIO_CONTROL_SEND_APP_CMD, /* Send an application command */
    SDIO_CONTROL_SET_INSERT_EJECT_CALLBACK, /* Set call back function */
    SDIO_CONTROL_GET_CARD_TYPE, /* Get the card type */
    SDIO_CONTROL_SET_CLK_DIV, /* Set the external clock frequency divider */
    SDIO_CONTROL_SD_INIT, /* Initialise card in SD mode */
    SDIO_CONTROL_SPI_INIT, /* Initialise card in SPI mode */
    SDIO_CONTROL_SET_BUS_WIDTH, /* Set the data bus width */
    SDIO_CONTROL_GET_CARD_PARAMS /* Returns a populated SDIO_CARD_PARAMETERS struct */
} SDIO_CONTROL_REQUEST;

/*                      Callback functions for interrupts                      */
/* Transfer complete/error callback */
typedef void (*sdio_callback) (uint16_t SDIO_NormalIntStatus, uint16_t SDIO_ErrorIntStatus);

/* Card inserted/ejected callback */
typedef void (*sdio_insert_eject_callback) (bool SDIO_card_inserted, bool SDIO_card_ejected);

/* Transfer control */
typedef struct
{
        void *buffer; /* Address of buffer to store data */
        uint16_t block_count; /* Number of blocks to be transfered */
        SDIO_DIRECTION direction; /* Direction of data */
        sdio_callback trans_complete_callback; /* Address of the callback function */
} SDIO_TRANS_CTRL;

/* Command info */
typedef struct
{
        uint8_t command_index; /* CMD index */
        uint32_t argument; /* CMD argument */
        SDIO_RESPONSE_TYPE response_type; /* Expected response for CMD index */
        SDIO_COMMAND_TYPE command_type; /* Data or non-data command */
        SDIO_TRANS_CTRL command_data; /* Transfer control */
        uint32_t response[4]; /* CMD response buffer */
} SDIO_COMMAND;

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/
void R_SDIO_GetVersion (void *buf);
void R_SDIO_Init (void);
ER_RET R_SDIO_Open (uint8_t SDIO_number);
ER_RET R_SDIO_Close (uint8_t SDIO_number);
ER_RET R_SDIO_Read (uint8_t SDIO_number, SDIO_TRANS_CTRL trans_control, uint32_t start_address);
ER_RET R_SDIO_Write (uint8_t SDIO_number, SDIO_TRANS_CTRL trans_control, uint32_t start_address);
ER_RET R_SDIO_Control (uint8_t SDIO_number, SDIO_CONTROL_REQUEST control_request, void *control);
void sdio_trans_complete (uint8_t SDIO_number);

#endif /* R_SDIO_RZN1_IF_H__ */
