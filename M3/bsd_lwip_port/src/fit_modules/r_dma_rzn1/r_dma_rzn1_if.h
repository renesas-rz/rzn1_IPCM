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
 * $Revision: 1326 $
 * $Date: 2019-03-04 11:38:16 +0000 (Mon, 04 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_dma_rzn1_if.h
 * Description  :  DMA (Direct Memory Access)control interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef R_DMA_RZN1_IF_H__
#define R_DMA_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "platform.h"
#include "r_dma_rzn1_config.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define DMAC_1                  (0)
#define DMAC_2                  (1)

#define DMA_CHAN_0              (0)
#define DMA_CHAN_1              (1)
#define DMA_CHAN_2              (2)
#define DMA_CHAN_3              (3)
#define DMA_CHAN_4              (4)
#define DMA_CHAN_5              (5)
#define DMA_CHAN_6              (6)
#define DMA_CHAN_7              (7)
#define INVAL_DMA_CHAN          (0xFF)

#define DMA_INTERRUPT_MASK      (0xFF00)

#define DMA_CHAN_ENABLE(chan)       (0x101 << (chan))
#define DMA_CHAN_DISABLE(chan)      (0x100 << (chan))
#define DMA_REG_WRITE(chan)       (0x101 << (chan))

#define DMA_CLOSE_ALL          (-1)           /* Used only in R_DMA_Close to close the entire controller */

/* Version Number of API. */
#define DMA_DRIVER_MAJOR_VERSION_NUMBER    (1)
#define DMA_DRIVER_MINOR_VERSION_NUMBER    (8)

/***********************************************************************************************************************
 Data Structures
 **********************************************************************************************************************/

/* DMA channel state */
typedef enum
{
    DMA_CHANNEL_STATE_CLOSED = 0, /* Channel uninitialised */
    DMA_CHANNEL_STATE_OPEN,       /* Channel initialised and idle */
    DMA_CHANNEL_STATE_BUSY        /* Channel currently being used for transfer */
} DMA_CHANNEL_STATE;

/* DMA transfer mode and flow controller */
typedef enum
{
    MTM      = 0, /* Memory to memory - Flow controller: DMAC */
    MTP_DMAC = 1, /* Memory to peripheral - Flow controller: DMAC */
    PTM_DMAC = 2, /* Peripheral to memory - Flow controller: DMAC */
    PTP_DMAC = 3, /* Peripheral to peripheral - Flow controller: DMAC */
    PTM_P    = 4, /* Peripheral to memory - Flow controller: Peripheral  */
    PTP_SP   = 5, /* Peripheral to peripheral - Flow controller: Source Peripheral */
    MTP_P    = 6, /* Memory to peripheral - Flow controller: Peripheral */
    PTP_DP   = 7, /* Peripheral to peripheral - Flow controller: Destination Peripheral */
} DMA_TR_FLOW;

/* DMA transfer width */
typedef enum
{
    BITS8  = 0,     /* 1 Byte */
    BITS16 = 1,     /* 2 Bytes */
    BITS32 = 2,     /* 4 Bytes */
    BITS64 = 3,     /* 8 Bytes */
} DMA_TR_WIDTH;

/* DMA transfer burst length (of width: DMA_TR_WIDTH) */
typedef enum
{
    DATA_ITEMS_1   = 0,     /* Single transaction per transaction request */
    DATA_ITEMS_4   = 1,     /* 4 Data items per transaction request */
    DATA_ITEMS_8   = 2,     /* 8 Data items per transaction request */
    DATA_ITEMS_16  = 3,     /* 16 Data items per transaction request */
    DATA_ITEMS_32  = 4,     /* 32 Data items per transaction request */
    DATA_ITEMS_64  = 5,     /* 64 Data items per transaction request */
    DATA_ITEMS_128 = 6,     /* 128 Data items per transaction request */
    DATA_ITEMS_256 = 7,     /* 256 Data items per transaction request */
} DMA_BURST_LEN;

/* DMA handshaking type */
typedef enum
{
    HARDWARE = 0, SOFTWARE = 1
} DMA_HS_TYPE;

/* DMA address incrementation */
typedef enum
{
    INCREMENT = 0, DECREMENT = 1, NO_CHANGE = 2
} DMA_INCREMENTATION;

/* DMA handshaking setup */
typedef struct
{
    DMA_HS_TYPE TYPE; /* software handshaking or hardware handshaking */
    bool INTERFACE_POLARITY; /* true = active low, false = active high */
    uint8_t HS_INTERFACE; /* Which DMA request channel to map the DMA channel to (see DMA Multiplexing register) To do: implement user manipulation of this register */
} DMA_HANDSHAKING;

/* DMA channel configuration */
typedef struct
{
    uint8_t PRIORITY;
    DMA_HANDSHAKING SRC_HS;
    DMA_HANDSHAKING DST_HS;
} DMA_CHAN_CTRL;

/* DMA transaction configuration */
typedef struct
{
    bool INT_EN;
    DMA_TR_FLOW TR_FLOW;
    uint32_t SRC;
    uint32_t DST;
    DMA_INCREMENTATION SRC_INCR;
    DMA_INCREMENTATION DST_INCR;
    DMA_TR_WIDTH SRC_TR_WIDTH;
    DMA_TR_WIDTH DST_TR_WIDTH;
    DMA_BURST_LEN SRC_BRST_LEN;
    DMA_BURST_LEN DST_BRST_LEN;
    uint16_t BLOCK_SIZE;
} DMA_TRANS_CTRL;

/* DMA Transfer request type */
typedef enum
{
    DMA_TRANSFER,   /* When hardware handshaking is enabled or memory to memory transfer is selected, use this to enable the channel for transfer*/
    DMA_SRC,        /* Source software transaction request */
    DMA_SRC_SINGLE, /* Single source software transaction request */
    DMA_SRC_LAST,   /* Last source transaction request */
    DMA_DST,        /* Destination software transaction request */
    DMA_DST_SINGLE, /* Single destination software transaction request */
    DMA_DST_LAST,   /* Last destination transaction request */
} DMA_TRANS_REQ_TYPE;

/* DMA control request */
typedef enum
{
    DMA_CONTROL_GET_DRIVER_VERSION, /* Get the driver version (returns one byte) */
    DMA_CONTROL_SET_CALL_BACK,      /* Set the call back function for interrupts */
    DMA_CONTROL_SET_CHAN_CONFIG,    /* Set the configuration for the channel: flow control, ((priority)), handshaking */
    DMA_CONTROL_GET_CHAN_CONFIG,    /* Get the configuration for the channel */
    DMA_CONTROL_SET_TRANS_CONFIG,   /* Set the configuration for the transaction: source and destination locations, incrementation, transfer widths, burst lengths, block size */
    DMA_CONTROL_GET_TRANS_CONFIG,   /* Get the configuration for the transaction */
    DMA_CONTROL_GET_CHAN_STATE,     /* Get the state of the channel: Open, Closed, Busy */
    DMA_CONTROL_PAUSE_TRANS,        /* Cleanly suspend all DMA transfers on the channel (channel state remains busy) */
    DMA_CONTROL_RESUME_TRANS,       /* Unsuspend DMA transfers on the channel */
    DMA_CONTROL_FREE_CHAN           /* Disables channel and sets the state to open */
} DMA_CONTROL_REQUEST;

/* Call back function for interrupts */
typedef void (*dma_trans_complete_callback) (uint8_t DMAC_number, uint8_t channel);

/* Default config structs */
extern const DMA_CHAN_CTRL DMA_DEFAULT_CHAN_CTRL;   /* It is the users responsibility to use these to default their configuration structures */
extern const DMA_TRANS_CTRL DMA_DEFAULT_TRANS_CTRL; /*                     when not altering all members of the struct                       */

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/

void R_DMA_Init (void);
void R_DMA_Uninitialise (void);
ER_RET R_DMA_Open (uint8_t DMAC_number, uint8_t channel);
ER_RET R_DMA_Control (uint8_t DMAC_number, uint8_t channel, DMA_CONTROL_REQUEST control_request, void *control);
ER_RET R_DMA_Write (uint8_t DMAC_number, uint8_t channel, DMA_TRANS_REQ_TYPE req_type);
ER_RET R_DMA_Close (uint8_t DMAC_number, int8_t channel);
void R_DMA_GetVersion (void *buf);

#endif /* R_DMA_RZN1_IF_H__ */
