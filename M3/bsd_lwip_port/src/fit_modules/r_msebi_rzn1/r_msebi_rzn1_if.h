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
 * FILE         :  r_msebi_rzn1_if.h
 * Description  :  MSEBI driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_MSEBI_RZN1_IF_H__
#define R_MSEBI_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define MSEBI_CS0_N (0)    /* MSEBI chip select 0 */
#define MSEBI_CS1_N (1)    /* MSEBI chip select 1 */
#define MSEBI_CS2_N (2)    /* MSEBI chip select 2 */
#define MSEBI_CS3_N (3)    /* MSEBI chip select 3 */
#define MSEBI_CS_COUNT  (4) /* MSEBI chip count */
#define MSEBI_CS_DMA_COUNT  (2)    /* MSEBI chip count for DMA */

#define MSEBI_NO_CS     (0xF)   /* Used to access non chip select-specific API functions */

/* Version Number of API. */
#define MSEBI_DRIVER_MAJOR_VERSION_NUMBER    (1)
#define MSEBI_DRIVER_MINOR_VERSION_NUMBER    (3)

#define MSEBI_MAX_FIFO_LEVEL (32)
#define MSEBI_MAX_DMA_TRANSFER_SIZE (8191)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/* MSEBI Master/Slave mode */
typedef enum
{
    MSEBIMASTER = 0, /* MSEBI Master */
    MSEBISLAVE /* MSEBI Slave */
} msebi_mode_t;

/* State of the MSEBI --> Whether or not it has been opened */
typedef enum
{
    MSEBI_STATE_CLOSED = 0, /* MSEBI un-opened */
    MSEBI_STATE_OPEN /* MSEBI opened */
} msebi_states_t;

/* State of the MSEBI chip select --> Whether or not it has been opened */
typedef enum
{
    MSEBI_CS_STATE_CLOSED = 0, /* Chip select un-opened */
    MSEBI_CS_STATE_OPEN /* Chip select opened */
} msebi_cs_states_t;

/* Callback Mode */
typedef enum
{
    TRANSMIT = 0, /* Register callback function only for received transfer interrupts */
    RECEIVE = 1, /* Register callback function only for received receive interrupts */
    TRANSMIT_RECEIVE = 2  /* Register the same callback function for received transfer/receive interrupts */
} msebi_callback_mode_t;

/* Cycle sizes of the different MSEBI phases */
typedef struct
{
        uint8_t write_dle_data_nb; /* Size of data latch phase (0(1 MSEBI_CLK) - 255(256 MSEBI_CLK)) on write cycle in no burst mode */
        uint8_t read_dle_data_nb; /* Size of data latch phase (0(1 MSEBI_CLK) - 255(256 MSEBI_CLK)) on read cycle in no burst mode */
        uint8_t write_dle_data_b; /* Size of data latch phase (0(1 MSEBI_CLK) - 3(4 MSEBI_CLK)) on write cycle in burst mode */
        uint8_t read_dle_data_b; /* Size of data latch phase (0(1 MSEBI_CLK) - 3(4 MSEBI_CLK)) on read cycle in burst mode */
        bool cle_data; /* Size of control latch phase (False(1 MSEBI_CLK) - True(2 MSEBI_CLK)) */
        bool ale_data; /* Size of address latch phase (False(1 MSEBI_CLK) - True(2 MSEBI_CLK)) */
} msebi_cyclesize_t;

/* Setup and hold timings for MSEBI data phase */
typedef struct
{
        uint8_t write_dle_setup; /* Size of data phase setup (1(1 MSEBI_CLK) - 63(63 MSEBI_CLK)) on write cycle */
        uint8_t read_dle_setup; /* Size of data phase setup (1(1 MSEBI_CLK) - 63(63 MSEBI_CLK)) on read cycle */
        uint8_t m_write_dle_hold; /* Size of data phase hold (0(0 MSEBI_CLK) - 63(63 MSEBI_CLK)) on write cycle (Master only) */
        uint8_t m_read_dle_hold; /* Size of data phase hold (0(0 MSEBI_CLK) - 63(63 MSEBI_CLK)) on read cycle (Master only) */
} msebi_setuphold_t;

/* The operating modes of MSEBI */
typedef enum
{
    MSEBIM_16_ASY = 0, /* Asynchronous, 16 bit mode, no burst (Master only) */
    MSEBIM_16_SYN = 1, /* Synchronous, 16 bit mode, burst available */
    MSEBIM_32_ASY = 2, /* Asynchronous, 32 bit mode, no burst (Master only) */
    MSEBIM_32_SYN = 3, /* Synchronous, 32 bit mode, burst available */
    MSEBIM_08_ASY = 4, /* Asynchronous, 8 bit mode, no burst (Master only) */
    MSEBIM_08_SYN = 5, /* Synchronous, 8 bit mode, burst available */
    MSEBIM_TRANS_MAX = 5,

    MSEBIS_16_SYN = 0, /* Synchronous, 16 bit mode, burst available */
    MSEBIS_32_SYN = 1, /* Synchronous, 32 bit mode, burst available */
    MSEBIS_08_SYN = 2, /* Synchronous, 8 bit mode, burst available */
    MSEBIS_TRANS_MAX = 2

} msebi_trans_func_t;

/* MSEBI wait management */
typedef enum
{
    MSEBI_WAIT_CSN = 1, /* Wait management on MSEBI_WAIT[n]_N pin */
    MSEBI_WAIT_CS0 = 2 /* Wait management on MSEBI_WAIT0_N pin */
} msebi_wait_mode_t;

/* MSEBI DMA access type */
typedef enum {
    MSEBI_DMA_TRANSMIT = 1,
    MSEBI_DMA_RECEIVE = 2,
    MSEBI_DMA_WRITE = 1,
    MSEBI_DMA_READ = 2
} msebi_dma_access_t;

/* Max burst sizes between Master CPU FIFO and MSEBI bus */
typedef enum
{
    MSEBIM_BURST_1_WORD = 0, /* 1 word burst max */
    MSEBIM_BURST_2_WORDS = 1, /* 2 words burst max */
    MSEBIM_BURST_4_WORDS = 2, /* 4 words burst max */
    MSEBIM_BURST_8_WORDS = 3, /* 8 words burst max */
    MSEBIM_BURST_16_WORDS = 4, /* 16 words burst max */
    MSEBIM_BURST_UNLIMITED = 5, /* Not limited */
    MSEBIM_BURST_MAX = 5
} msebim_burstsize;

/* Max burst sizes between Slave CPU FIFO and MSEBI bus */
typedef enum
{
    MSEBIS_BURST_1_WORD = 0, /* 1 word burst max */
    MSEBIS_BURST_4_WORDS = 1, /* 4 words burst max */
    MSEBIS_BURST_8_WORDS = 2, /* 8 words burst max */
    MSEBIS_BURST_16_WORDS = 3, /* 16 words burst max */
    MSEBIS_BURST_MAX = 3
} msebis_burstsize;

/* MSEBI Master common configurations */
typedef struct
{
        uint8_t rx_fifo_data_level; /* Current recieve CPU FIFO level 1 word is 32 bits. READ FROM REGISTER */
        uint8_t tx_fifo_data_level; /* Current transmit CPU FIFO level 1 word is 32 bits. READ FROM REGISTER */
        uint8_t msebim_clk_low; /* Time duration in units of MSEBIM_HCLK of MSEBIM_CLK level low (0(1 MSEBIM_HCLK) - 3(4 MSEBIM_HCLK)) */
        uint8_t msebim_clk_high; /* Time duration in units of MSEBIM_HCLK of MSEBIM_CLK level high (0(1 MSEBIM_HCLK) - 3(4 MSEBIM_HCLK)) */
        msebim_burstsize cpu_write_burst; /* Max write burst size from CPU Tx FIFO to MSEBI bus */
        msebim_burstsize cpu_read_burst; /* Max read burst size from MSEBI bus to CPU Rx FIFO */
} msebim_config_t;

/* MSEBI Slave common configurations */
typedef struct
{
        uint8_t rx_fifo_data_level; /* Current recieve CPU FIFO level 1 word is 32 bits. READ FROM REGISTER */
        uint8_t tx_fifo_data_level; /* Current transmit CPU FIFO level 1 word is 32 bits. READ FROM REGISTER */
        msebis_burstsize cpu_read_burst; /* Max burst size of reads of Slave CPU Tx FIFO by MSEBI Master */
        msebis_burstsize cpu_write_burst; /* Max burst size of writes from Slave CPU Rx FIFO to AHB master */
        bool buffer_data; /* true: data is bufferable, false: data is not bufferable */
        bool cache_data; /* true; data is cacheable, false: data is not cacheable */
        uint8_t cfg_reg_timeout_delay_x4; /* Timeout of register access delay = 4 * (cfg_reg_timeout_delay_x4 + 1),(0(4 MSEBIS_HCLK) - 15(64 MSEBIS_HCLK)) */
} msebis_config_t;

/* General MSEBI chip select configurations */
typedef struct
{
        msebi_trans_func_t trans_func;
        msebi_wait_mode_t wait_func;
        bool burst_enable; /* true: burst mode enable (Synchronous mode only), false: burst mode disabled */
        bool addr_route_cs1; /* true: map MSEBI_CS1_N on address line, false: no address routing */
        bool addr_route_cs2; /* true: map MSEBI_CS2_N on address line, false: no address routing */
        bool addr_route_cs3; /* true: map MSEBI_CS3_N on address line, false: no address routing */
} msebi_config_cs_t;

/* Master MSEBI chip select configurations */
typedef struct
{
        msebi_config_cs_t m_s_shared_config;
        bool wait_management; /* true: wait management as defined in m_s_shared_config, false: No wait management */
        uint8_t num_ale_used; /* The number of phase MSEBI_ALE used (0-4) */
        bool parallel_ale_mode; /* true: parallel mode, false: serial mode (only MSEBIM_ALE used for all ALE cycles) */
        bool multi_dle; /* true: multi DLE mode enabled, false: multi DLE mode disabled */
        uint8_t extend_addr; /* Least significant 5 bits: b5 to b0 - MSEBI_A31 to MSEBI_A27 */
} msebim_config_cs_t;

/* Slave MSEBI chip select configurations */
typedef struct
{
        msebi_config_cs_t m_s_shared_config;
        bool write_access; /* true: enable write on device, false: disable write on device */
        bool mmu_addr_mode; /* true: address management MMU mode, false: address anagement direct mode */
} msebis_config_cs_t;

/* Master MSEBI DMA control configurations for both transmit and receive. */
typedef struct
{
        bool single_dest_width; /* Size of single transaction can be configured. READ FROM REGISTER */
        uint16_t current_block_size; /* Outstanding single transactions. READ FROM REGISTER */
        uint16_t block_size; /* Destination/Source block transfer size 13bits 0-8191*/
        msebim_burstsize burst_size; /* Max burst transaction size */
        bool enable_dma; /* true: enable the DMA  false: disable the DMA */
} msebim_dma_control_cs_t;

/* Master MSEBI DMA data level configurations for both transmit and receive. */
typedef struct
{
        bool use_ext_pin; /* true: enable the control of DMA channel by external pins, false: DMA starts immediately */
        msebim_burstsize fifo_burst_size; /* Max burst size for access between DMA FIFO and MSEBI bus. */
        uint8_t current_fifo_data_level; /* Current FIFO data level. 1 word is 64 bits. READ FROM REGISTER */
        uint8_t fifo_data_level; /* FIFO data level control. 0-31 with 28 being an optimal value. */
} msebim_dma_datalevel_cs_t;

/* Slave MSEBI DMA data level configurations for both transmit and receive. */
typedef struct
{
        uint16_t current_fifo_data_level; /* Current FIFO data level. 1 word is 32 bits. READ FROM REGISTER */
        bool flow_control; /* true: enable the DMA flow control for write signal */
        bool burst_size_optimised; /* Burst size optimization true: enabled */
        msebis_burstsize fifo_burst_size; /* Max burst size for access between DMA FIFO and MSEBI bus. */
} msebis_dma_datalevel_cs_t;

/* Slave MSEBI from CPU interrupt status */
typedef struct
{
        bool eob_detected_dma_tx[MSEBI_CS_DMA_COUNT]; /* true: end of block detected for DMA transmit chip 0,1 */
        bool eob_detected_dma_rx[MSEBI_CS_DMA_COUNT]; /* true: end of block detected for DMA receive chip 0,1 */
        bool eob_detected_cpu_tx[MSEBI_CS_COUNT]; /* true: end of block detected for CPU transmit chip 0,3 */
        bool eob_detected_cpu_rx[MSEBI_CS_COUNT]; /* true: end of block detected for DMA receive chip 0,3 */
} msebis_interrupt_status_t;

/* Slave MSEBI from CPU interrupt control of mask and clear */
typedef struct
{
        bool eob_interrupt_dma_tx[MSEBI_CS_DMA_COUNT]; /* true: Mask or clear interrupt for DMA transmit chip 0,1 */
        bool eob_interrupt_dma_rx[MSEBI_CS_DMA_COUNT]; /* true: Mask or clear interrupt for DMA receive chip 0,1 */
        bool eob_interrupt_cpu_tx[MSEBI_CS_COUNT]; /* true: eMask or clear interrupt for CPU transmit chip 0,3 */
        bool eob_interrupt_cpu_rx[MSEBI_CS_COUNT]; /* true: Mask or clear interrupt for DMA receive chip 0,3 */
} msebis_interrupt_control_t;

/* Master MSEBI DMA read or write block address configurations. */
typedef struct
{
        bool align_first_block_32bit; /* true: align the first block address as 32 bit, false: align 64-bit */
        uint32_t address_dma_read; /* First block address used by DMA controller to start a DMA transfer. Only bits 3 to 31 used.*/
} msebim_dma_block_address_cs_t;

typedef struct
{
        bool enable; /* true: enable the DMA ready to transmit or recieve */
        bool force; /* true: drive the DMA flow control signals */
} msebis_dma_request_cs_t;

/* MSEBI Control Request */
typedef enum
{
    MSEBI_CONTROL_SET_CONFIG, /* Set the common configurations */
    MSEBI_CONTROL_GET_CONFIG, /* Get the current common configurations */
    MSEBI_CONTROL_MASTER_CLK_ENABLE, /* Enable/Disable MSEBIM_CLK clock generation */
    MSEBI_CONTROL_SET_CS_CYCLESIZE, /* Set the chip select cycle size */
    MSEBI_CONTROL_GET_CS_CYCLESIZE, /* Get the chip select cycle size */
    MSEBI_CONTROL_SET_CS_SETUPHOLD, /* Set the chip select setup and hold times */
    MSEBI_CONTROL_GET_CS_SETUPHOLD, /* Get the chip select setup and hold times */
    MSEBI_CONTROL_SET_CS_CONFIG, /* Set the chip select configuration */
    MSEBI_CONTROL_GET_CS_CONFIG, /* Get the chip select configuration */
    MSEBI_CONTROL_SET_CS_DMA_TDATALEVEL, /* Set the DMA transmit data level */
    MSEBI_CONTROL_GET_CS_DMA_TDATALEVEL, /* Get the DMA transmit data level  */
    MSEBI_CONTROL_SET_CS_DMA_RDATALEVEL, /* Set the DMA receive data level */
    MSEBI_CONTROL_GET_CS_DMA_RDATALEVEL, /* Get the DMA receive data level  */
    MSEBI_CONTROL_SET_CS_DMA_TCONTROL, /* Set the DMA transmit control */
    MSEBI_CONTROL_GET_CS_DMA_TCONTROL, /* Get the DMA transmit control  */
    MSEBI_CONTROL_SET_CS_DMA_RCONTROL, /* Set the DMA receive control */
    MSEBI_CONTROL_GET_CS_DMA_RCONTROL, /* Get the DMA receive control */
    MSEBIM_CONTROL_SET_CS_DMA_READADDR, /* Set the DMA read address register */
    MSEBIM_CONTROL_GET_CS_DMA_READADDR, /* Get the DMA read address register   */
    MSEBIM_CONTROL_GET_CS_DMA_CURR_READADDR, /* Get the DMA current read address register */
    MSEBIM_CONTROL_SET_CS_DMA_WRITEADDR, /* Set the DMA write address register */
    MSEBIM_CONTROL_GET_CS_DMA_WRITEADDR, /* Get the DMA write address register   */
    MSEBIM_CONTROL_GET_CS_DMA_CURR_WRITEADDR,/* Get the DMA current write address register */
    MSEBIM_CONTROL_FLUSH_CPU_FIFO, /* Flush CPU Receive FIFO */
    MSEBIS_CONTROL_SLAVE_CS_ENABLE, /* Enable/Disable MSEBI_CS[n]_N master request receiving */
    MSEBIS_CONTROL_SET_CS_MMU_ADDRESS, /* Set the MMU base address register */
    MSEBIS_CONTROL_GET_CS_MMU_ADDRESS, /* Get the MMU base address register  */
    MSEBIS_CONTROL_SET_CS_MMU_ADDRESS_MASK, /* Set the MMU base address mask register */
    MSEBIS_CONTROL_GET_CS_MMU_ADDRESS_MASK, /* Get the MMU base address mask register */
    MSEBIS_CONTROL_SET_CS_DMA_TRANSMIT_REQ, /* Set the DMA transmit request register */
    MSEBIS_CONTROL_GET_CS_DMA_TRANSMIT_REQ, /* Get the DMA transmit request register */
    MSEBIS_CONTROL_SET_CS_DMA_RECEIVE_REQ, /* Set the DMA receive request register */
    MSEBIS_CONTROL_GET_CS_DMA_RECEIVE_REQ, /* Get the DMA receive request register */
    MSEBIS_CONTROL_GET_INT_STATUS, /* Get interrupt status register values */
    MSEBIS_CONTROL_GET_MASKED_INT_STATUS, /* Get masked interrupt status register values */
    MSEBIS_CONTROL_SET_MASK_INTERRUPT, /* Set interrupt mask */
    MSEBIS_CONTROL_GET_MASK_INTERRUPT, /* Get interrupt mask */
    MSEBIS_CONTROL_CLEAR_INTERRUPT, /* Clear slave interrupt */
    MSEBIS_SET_CALLBACK,            /*Set callback function*/
    MSEBIS_CONTROL_SET_CS_CPU_EOB_ADDRESS, /* Set CPU End of Block address register value */
    MSEBIS_CONTROL_GET_CS_CPU_EOB_ADDRESS, /* Get CPU End of Block address register value */
    MSEBIS_CONTROL_SET_CS_DMA_EOB_ADDRESS, /* Set DMA End of Block address register value */
    MSEBIS_CONTROL_GET_CS_DMA_EOB_ADDRESS, /* Get DMA End of Block address register value */

} msebi_cmd_t;

typedef void (*msebi_callback) (msebi_mode_t mode);

/***********************************************************************************************************************
 Default parameters
 **********************************************************************************************************************/
/* Default master configuration */
extern const msebim_config_t default_msebim_config;
/* Default master chip select configuration */
extern const msebim_config_cs_t default_msebim_config_cs;

/* Default slave configuration */
extern const msebis_config_t default_msebis_config;
/* Default slave chip select configuration */
extern const msebis_config_cs_t default_msebis_config_cs;

/* Default cycle size configuration */
extern const msebi_cyclesize_t default_msebi_cyclesize_cs;
/* Default setup and hold configuration */
extern const msebi_setuphold_t default_msebi_setuphold_cs;

/* Default master DMA data level configuration */
extern const msebim_dma_datalevel_cs_t default_msebim_dma_datalevel_cs;
/* Default slave DMA data level configuration */
extern const msebis_dma_datalevel_cs_t default_msebis_dma_datalevel_cs;

/* Default master DMA control configuration */
extern const msebim_dma_control_cs_t default_msebim_dma_control_cs;
extern const msebim_dma_block_address_cs_t default_msebim_dma_block_address_cs;

/* Default slave DMA transmit and receive request settings */
extern const msebis_dma_request_cs_t default_msebis_dma_request_cs;

/* Default slave DMA and CPU interrupt masks  and clear down*/
extern const msebis_interrupt_control_t default_msebis_interrupt_masks;
extern const msebis_interrupt_control_t default_msebis_interrupt_clear;

/***********************************************************************************************************************
 Global functions
 **********************************************************************************************************************/
void R_MSEBI_GetVersion (void *buf);
void R_MSEBI_Init (void);
ER_RET R_MSEBI_Open (msebi_mode_t mode, uint8_t chip_sel);
ER_RET R_MSEBI_Close (msebi_mode_t mode, uint8_t chip_sel);
ER_RET R_MSEBI_Control (msebi_mode_t mode, uint8_t chip_sel, msebi_cmd_t control_request, void *msebi_ctrl);
ER_RET R_MSEBIS_SetCallback (msebi_mode_t mode, msebi_callback_mode_t callback_mode, uint8_t chip_sel, msebi_callback callback);

#endif /* R_MSEBI_RZN1_IF_H__ */
