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
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_spi_rzn1.c
 * Description  :  SPI driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "platform.h"
#include "r_spi_rzn1_config.h"
#include "r_spi_rzn1.h"
#include "iodefine.h"
#include "r_sysctrl_rzn1_if.h"

#ifdef r_dma_rzn1_spi_included
#include "r_dma_rzn1_if.h"
#endif

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/* SPI divider value can be 8-128 */
#define SPI_CLOCK_DIVIDER      (8)                /* 8: Will allow 125 MHz operation */
#define SPI_CLK_FREQ  (SystemPLLFreq/SPI_CLOCK_DIVIDER)

#define INVAL_SPI_CHAN     (0xFF)         /* Invalid SPI channel */
#define SPI_FIFO_DEPTH     (16)
#define SPI_TIMEOUT        (0xFFFF)
#define SPI_DUMMY_DATA     (0x0000)

#define MIN_DATA_FRAME_SIZE     (4)
#define MAX_DATA_FRAME_SIZE     (16)

#define MIN_MW_CTL_FRAME_SIZE   (1)
#define MAX_MW_CTL_FRAME_SIZE   (16)

#define MIN_CLK_DIV             (2)
#define MAX_SLAVE_SEL           (3)
#define MAX_SAMPLE_DELAY        (64)
/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
typedef struct
{
    volatile SPI_S_Type *base_address;
    bool tx_outstanding;
    bool rx_outstanding;
    spi_transfer_complete_callback_t trans_completed_callback;
} spi_chan_params_t;

typedef struct
{
    uint8_t frames_to_final_int;
    uint16_t *read_buf; /* Where data received is stored */
    uint16_t *write_buf; /* Data to be written */
    uint16_t rx_remaining_frames; /* Remaining number of Rx data frames */
    uint16_t tx_remaining_frames; /* Remaining number of Tx data frames */
    spi_transfer_mode_t rx_transfer; /* Rx transfer mode - Blocking/NonBlocking/DMA */
    spi_transfer_mode_t tx_transfer; /* Tx transfer mode - Blocking/NonBlocking/DMA */
    spi_transfer_type_t transfer_mode; /* Indicates the transfer mode */
} spi_transfer_params_t;

#ifdef r_dma_rzn1_spi_included
typedef struct
{
    uint8_t Rx;
    uint8_t Tx;
} spi_dma_req_info;

typedef struct
{
    uint8_t DMAC_number;
    uint8_t HS_Interface;
    uint8_t channel;
    bool reserve_mode;
} spi_dma_raw_info;

typedef struct
{
    spi_dma_raw_info Tx;
    spi_dma_raw_info Rx;
} spi_dma_info;
#endif

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static spi_chan_params_t spi_chan_params[MAX_SPI_CHANNELS];                     /* Channel specific parameters */
static spi_transfer_params_t spi_transfer_params[MAX_SPI_CHANNELS];             /* Transfer specific parameters */
static spi_channel_config_t spi_chan_config[MAX_SPI_CHANNELS];                  /* Channel configurations */
static spi_transfer_complete_callback_t spi_chan_callback[MAX_SPI_CHANNELS];    /* Channel callback functions */

#ifdef r_dma_rzn1_spi_included
static spi_dma_info spi_dma[MAX_SPI_CHANNELS];
#endif
/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/

static void handle_spi_interrupt (IRQn_Type *irq_num_ptr);

static ER_RET setuptx (uint8_t chan_num, spi_transfer_mode_t transfer_mode, uint16_t *write_buf, uint16_t data_frames);
static ER_RET setuprx (uint8_t chan_num, spi_transfer_mode_t transfer_mode, uint16_t *read_buf, uint16_t data_frames);

static void txblockingsetup (uint8_t chan_num, uint16_t *write_buf, uint16_t data_frames);
static void txnonblockingsetup (uint8_t chan_num, uint16_t *write_buf, uint16_t data_frames);
static void rxblockingsetup (uint8_t chan_num, uint16_t *read_buf, uint16_t data_frames);
static void rxnonblockingsetup (uint8_t chan_num, uint16_t *read_buf, uint16_t data_frames);
static ER_RET txdmasetup (uint8_t chan_num, uint16_t *write_buf, uint16_t data_frames);
static ER_RET rxdmasetup (uint8_t chan_num, uint16_t *read_buf, uint16_t data_frames);

static ER_RET spi_blockingwrite (uint8_t chan_num);
static ER_RET spi_blockingread (uint8_t chan_num);
static ER_RET spi_blockingfullduplex (uint8_t chan_num);

static void spi_read_fifo (uint8_t chan_num);
static void spi_write_fifo (uint8_t chan_num);
static void spi_tx_rx_flush (uint8_t chan_num);
static uint8_t tx_max_write (uint8_t chan_num);

#ifdef r_dma_rzn1_spi_included
static ER_RET spi_assign_dma_chan (spi_dma_raw_info *dma_info);
static void spi_dmac_callback (uint8_t DMAC_number, uint8_t dma_channel);
static void spi_unpack_dma_info (spi_dma_raw_info *dma_info, uint8_t dma_req_info);

const spi_dma_req_info SPI_DMA_REQ[MAX_SPI_CHANNELS] =
{
{ DMA_SPI1_RX_REQ, DMA_SPI1_TX_REQ },
{ DMA_SPI2_RX_REQ, DMA_SPI2_TX_REQ },
{ DMA_SPI3_RX_REQ, DMA_SPI3_TX_REQ },
{ DMA_SPI4_RX_REQ, DMA_SPI4_TX_REQ },
{ DMA_SPI5_RX_REQ, DMA_SPI5_TX_REQ },
{ DMA_SPI6_RX_REQ, DMA_SPI6_TX_REQ } };
#endif

/***********************************************************************************************************************
 *
 *  Function:       spi_init
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Initialises the SPI driver
 *
 **********************************************************************************************************************/
ER_RET spi_init (void)
{
    ER_RET ret_val = ER_OK;
    uint8_t channel;

    /* reset internal parameters */
    for (channel = 0; channel < MAX_SPI_CHANNELS; channel++)
    {
        spi_chan_params[channel].tx_outstanding = 0;
        spi_chan_params[channel].rx_outstanding = 0;
        spi_chan_params[channel].trans_completed_callback = (void *) 0;
        spi_chan_params[channel].base_address = (void *) 0;

        spi_chan_callback[channel] = 0;

#ifdef r_dma_rzn1_spi_included
        /* Initialise DMA information about the channels */
        /* Rx information */
        spi_dma[channel].Rx.channel = INVAL_DMA_CHAN;
        ;
        spi_dma[channel].Rx.reserve_mode = false;
        spi_unpack_dma_info( &spi_dma[channel].Rx, SPI_DMA_REQ[channel].Rx);

        /* Tx information */
        spi_dma[channel].Tx.channel = INVAL_DMA_CHAN;
        ;
        spi_dma[channel].Tx.reserve_mode = false;
        spi_unpack_dma_info( &spi_dma[channel].Tx, SPI_DMA_REQ[channel].Tx);
#endif
    }

    /* Configure clock divider for master and slave SPI */
    ret_val = R_SYSCTRL_SetSPIClkDivider(SPI_CLOCK_DIVIDER);

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_uninit
 *
 *  Return value:   void
 *
 *  Parameters:     None
 *
 *  Description:    Unnitialises the SPI driver
 *
 **********************************************************************************************************************/
void spi_uninit (void)
{
    uint8_t channel;

    /* reset internal parameters */
    for (channel = 0; channel < MAX_SPI_CHANNELS; channel++)
    {
        spi_chan_params[channel].tx_outstanding = 0;
        spi_chan_params[channel].rx_outstanding = 0;
        spi_chan_params[channel].trans_completed_callback = (void *) 0;
        spi_chan_params[channel].base_address = (void *) 0;

        spi_chan_callback[channel] = 0;

#ifdef r_dma_rzn1_spi_included
        /* Clear Rx and Tx channels */
        spi_dma[channel].Rx.channel = INVAL_DMA_CHAN;

        spi_dma[channel].Tx.channel = INVAL_DMA_CHAN;
#endif
    }

    return;
}
/***********************************************************************************************************************
 End of function spi_uninit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_channelopen
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *
 *  Description:    Opens an SPI channel
 *
 **********************************************************************************************************************/
ER_RET spi_channelopen (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num;
    uint32_t int_priority = SPI_DEFAULT_INT_PRIORITY;
    volatile SPI_S_Type *channel_base_address;

    /* Enable bus interconnect and PCLK to the SPI channel */
    /* Enable channel SCLK (external interface) */
    R_SYSCTRL_EnableSPI(chan_num);

    /* Set default channel configuration */
    channel_base_address = (volatile SPI_S_Type *) (RZN1_SPI0_BASE + (chan_num * 0x1000));
    spi_chan_params[chan_num].base_address = channel_base_address;

    /* Disable SPI - Clears Tx and Rx FIFOs */
    channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;

    /* Mask all interrupts */
    channel_base_address->rSpi_IMR.LONG = 0;

    /* DMA Disabled */
    channel_base_address->rSpi_DMACR.LONG = 0;

    /* Set the default channel configuration */
    spi_setchanconfig(chan_num, default_spi_chan_config);

    /* Enable system interrupts and register interrupt handler */
    irq_num = RZN1_IRQ_SPI0 + chan_num;
    if (R_BSP_InterruptRegisterCallback((IRQn_Type) irq_num, (bsp_int_cb_t) &handle_spi_interrupt) == MCU_INT_SUCCESS)
    {
        ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
        if (MCU_INT_SUCCESS != ret_val)
        {
            ret_val = ER_SYS;
        }
        else
        {
            ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_ENABLE,
            FIT_NO_PTR);
        }
    }
    else
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_channelopen
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_channelclose
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *
 *  Description:    Opens an SPI channel
 *
 **********************************************************************************************************************/
void spi_channelclose (uint8_t chan_num)
{
    IRQn_Type irq_num;

    /* Disable system interrupts */
    irq_num = RZN1_IRQ_SPI0 + chan_num;
    R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);

#ifdef r_dma_rzn1_spi_included
    /* Close DMA channel if opened */
    spi_release_dma_rx_chan(chan_num);
    spi_release_dma_tx_chan(chan_num);
#endif
    /* Clear channel parameters */
    spi_chan_params[chan_num].tx_outstanding = 0;
    spi_chan_params[chan_num].rx_outstanding = 0;
    spi_chan_params[chan_num].trans_completed_callback = (void *) 0;
    spi_chan_params[chan_num].base_address = (void *) 0;

    /* Disable bus interconnect and PCLK to the SPI channel */
    /* Disable channel SCLK (external interface) */
    R_SYSCTRL_DisableSPI(chan_num);
}
/***********************************************************************************************************************
 End of function spi_channelclose
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_setchanconfig
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  chan_config - The channel configuration settings
 *
 *  Description:    Configures an SPI channel and stores the information
 *
 **********************************************************************************************************************/
ER_RET spi_setchanconfig (uint8_t chan_num, spi_channel_config_t chan_config)
{
    ER_RET ret_val = ER_OK;
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;
    uint16_t spi_sclk_div = 0;
    uint16_t i;

    if (0 == channel_base_address)
    {
        ret_val = ER_INVAL;
    }
    /* Parameter check */
    else if ((MIN_DATA_FRAME_SIZE > chan_config.data_frame_size) || (MAX_DATA_FRAME_SIZE < chan_config.data_frame_size)
            || (spi_microwire < chan_config.frame_format)
            || (toggle_clk_start_data_bit < chan_config.motorola_config.clk_phase)
            || (clk_inactive_high < chan_config.motorola_config.clk_polarity)
            || (MIN_MW_CTL_FRAME_SIZE > chan_config.microwire_config.control_frame_size)
            || (MAX_MW_CTL_FRAME_SIZE < chan_config.microwire_config.control_frame_size)
            || (microwire_handshaking_enabled < chan_config.microwire_config.handshaking)
            || (microwire_sequential_trans < chan_config.microwire_config.transfer_mode))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Wait for any ongoing transfers to complete */
        for (i = 0; (i < SPI_TIMEOUT) && channel_base_address->rSpi_SR.BIT.bSpi_BUSY; i++)
        {
            ;
        }

        if (channel_base_address->rSpi_SR.BIT.bSpi_BUSY)
        {
            ret_val = ER_SYS;
        }
        else
        {
            /* Ensure SPI is disabled so registers can be written to */
            channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;

            /* Test for SPI Master - Master configurations will be ignored for slave channels */
            if (chan_num < MIN_SPI_SLAVE)
            {
                spi_sclk_div = (uint16_t)((float) SPI_CLK_FREQ / chan_config.master_config.baudrate);

                /* The SPI channel is a master channel */
                /* Master parameter check */
                if ((spi_sclk_div < MIN_CLK_DIV) || (MAX_SLAVE_SEL < chan_config.master_config.slave_select)
                        || (MAX_SAMPLE_DELAY < chan_config.master_config.RXD_sample_delay))
                {
                    ret_val = ER_PARAM;
                }
                if (ER_OK == ret_val)
                {
                    if (spi_sclk_div & 0x01)
                    {
                        /* LSB is ignored by hardware - Round up (Lower freq than requested) */
                        spi_sclk_div++;
                    }

                    ((SPI_M_Type *) channel_base_address)->rSpi_BAUDR.BIT.bSpi_SCKDV = spi_sclk_div;

                    /* Clear previous slave selection before setting new one */
                    /* Default: Slave select mode - Hardware */
                    ((SPI_M_Type *) channel_base_address)->rSpi_SER.LONG = 0;
                    ((SPI_M_Type *) channel_base_address)->rSpi_SER.BIT.bSpi_HardwareSS = 1
                            << chan_config.master_config.slave_select;

                    ((SPI_M_Type *) channel_base_address)->rSpi_RX_SAMPLE_DLY.BIT.bSpi_RX_Sample_Delay =
                            chan_config.master_config.RXD_sample_delay;

                    /* Save master config */
                    spi_chan_config[chan_num].master_config.baudrate = chan_config.master_config.baudrate;
                    spi_chan_config[chan_num].master_config.slave_select = chan_config.master_config.slave_select;
                    spi_chan_config[chan_num].master_config.RXD_sample_delay =
                            chan_config.master_config.RXD_sample_delay;
                }
            }

            if (ER_OK == ret_val)
            {
                /* Set register values */
                /* Default: Transfer mode  - Transmit & Receive  -- Altered when Transfer is initiated
                 SPI_MISO       - Disabled            -- Altered when Transfer is initiated
                 Shift Reg Loop - Normal Mode Operation*/
                channel_base_address->rSpi_CTRLR0.LONG = ((chan_config.microwire_config.control_frame_size - 1) << 12) /* Observe: decremented value as seen in hardware manual */
                | (1 << 10) /* SPI_MISO */
                | (chan_config.motorola_config.clk_polarity << 7) | (chan_config.motorola_config.clk_phase << 6)
                        | (chan_config.frame_format << 4) | (chan_config.data_frame_size - 1); /* Observe: decremented value as seen in hardware manual */

                channel_base_address->rSpi_MWCR.LONG = (chan_config.microwire_config.handshaking << 2)
                        | (chan_config.microwire_config.data_direction << 1)
                        | chan_config.microwire_config.transfer_mode;

                /* Save channel configuration */
                spi_chan_config[chan_num].data_frame_size = chan_config.data_frame_size;
                spi_chan_config[chan_num].frame_format = chan_config.frame_format;
                spi_chan_config[chan_num].motorola_config.clk_phase = chan_config.motorola_config.clk_phase;
                spi_chan_config[chan_num].motorola_config.clk_polarity = chan_config.motorola_config.clk_polarity;
                spi_chan_config[chan_num].microwire_config.control_frame_size =
                        chan_config.microwire_config.control_frame_size;
                spi_chan_config[chan_num].microwire_config.handshaking = chan_config.microwire_config.handshaking;
                spi_chan_config[chan_num].microwire_config.transfer_mode = chan_config.microwire_config.transfer_mode;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_setchanconfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_getchanconfig
 *
 *  Return value:   None
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  chan_config - The location to return the channel configuration to
 *
 *  Description:    Returns the saved channel configuration
 *
 **********************************************************************************************************************/
void spi_getchanconfig (uint8_t chan_num, spi_channel_config_t *chan_config)
{
    *chan_config = spi_chan_config[chan_num];
}
/***********************************************************************************************************************
 End of function spi_getchanconfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_registercallback
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  callback_function - The callback function for the channel
 *
 *  Description:    Registers the user callback function to a channel
 *
 **********************************************************************************************************************/
ER_RET spi_registercallback (uint8_t chan_num, spi_transfer_complete_callback_t callback_function)
{
    ER_RET ret_val = ER_OK;

    if (0 == callback_function)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        spi_chan_callback[chan_num] = callback_function;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_registercallback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_read
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  transfer_data - Relevant transfer information
 *
 *  Description:    Initiates the requested SPI read.
 *
 **********************************************************************************************************************/
ER_RET spi_read (uint8_t chan_num, spi_transfer_data_t transfer_data)
{
    ER_RET ret_val = ER_OK;
    uint16_t i;
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    if (0 == channel_base_address)
    {
        ret_val = ER_INVAL;
    }
    else
    {
        /* Wait for any ongoing transfers to complete */
        for (i = 0; (i < SPI_TIMEOUT) && channel_base_address->rSpi_SR.BIT.bSpi_BUSY; i++)
        {
            ;
        }

        if (channel_base_address->rSpi_SR.BIT.bSpi_BUSY)
        {
            ret_val = ER_SYS;
        }
        else
        {
            /* Ensure SPI is disabled so registers can be written to */
            channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;

            /* Set transfer mode to transfer_type */
            channel_base_address->rSpi_CTRLR0.BIT.bSpi_TMOD = transfer_data.transfer_type;
            spi_transfer_params[chan_num].transfer_mode = transfer_data.transfer_type;

            if (ER_OK
                    == (ret_val = setuprx(chan_num, transfer_data.transfer_mode_rx, transfer_data.read_buf,
                            transfer_data.data_frames)))
            {
                /* Read transfer initiated */
                spi_chan_params[chan_num].rx_outstanding = 1;

                /* Enable SPI */
                channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 1;

                /* Master: Initiate transfer by writing a single "dummy" variable in Tx FIFO */
                if (chan_num < MIN_SPI_SLAVE)
                {
                    channel_base_address->rSpi_DR.LONG = 0x0F;
                }

                if (SPI_TRANSFER_MODE_BLOCKING == transfer_data.transfer_mode_rx)
                {
                    ret_val = spi_blockingread(chan_num);
                }

            }

        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_write
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  transfer_data - Relevant transfer information
 *
 *  Description:    Initiates the requested SPI write.
 *
 **********************************************************************************************************************/

ER_RET spi_write (uint8_t chan_num, spi_transfer_data_t transfer_data)
{
    ER_RET ret_val = ER_OK;
    uint16_t i;
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    if (0 == spi_chan_params[chan_num].base_address)
    {
        ret_val = ER_INVAL;
    }
    else
    {
        /* Wait for any ongoing transfers to complete */
        for (i = 0; (i < SPI_TIMEOUT) && channel_base_address->rSpi_SR.BIT.bSpi_BUSY; i++)
        {
            ;
        }

    }

    if (channel_base_address->rSpi_SR.BIT.bSpi_BUSY)
    {
        ret_val = ER_SYS;
    }
    else
    {
        /* Ensure SPI is disabled so registers can be written to */
        channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;

        /* Set transfer mode to transfer_type */
        channel_base_address->rSpi_CTRLR0.BIT.bSpi_TMOD = transfer_data.transfer_type;
        spi_transfer_params[chan_num].transfer_mode = transfer_data.transfer_type;

        if (ER_OK
                == (ret_val = setuptx(chan_num, transfer_data.transfer_mode_tx, transfer_data.write_buf,
                        transfer_data.data_frames)))
        {
            /* Write transfer initiated */
            spi_chan_params[chan_num].tx_outstanding = 1;

            /* Enable SPI */
            channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 1;

            if (SPI_TRANSFER_MODE_DMA == transfer_data.transfer_mode_tx)
            {
                channel_base_address->rSpi_TDMACR.BIT.bSpi_TDMAE1 = 1; /* Disabled via hardware after block transfer is complete */
            }
            else if (SPI_TRANSFER_MODE_BLOCKING == transfer_data.transfer_mode_tx)
            {
                ret_val = spi_blockingwrite(chan_num);
            }
            else
            {
                ;
            } /* Do nothing */

        }

    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_readwrite
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  transfer_data - Relevant transfer information
 *
 *  Description:    Initiates the requested SPI transfer for full duplex mode.
 *
 **********************************************************************************************************************/

ER_RET spi_readwrite (uint8_t chan_num, spi_transfer_data_t transfer_data)
{
    ER_RET ret_val = ER_OK;
    uint16_t i;
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    if (0 == channel_base_address)
    {
        ret_val = ER_INVAL;
    }
    else
    {
        /* Wait for any ongoing transfers to complete */
        for (i = 0; (i < SPI_TIMEOUT) && channel_base_address->rSpi_SR.BIT.bSpi_BUSY; i++)
        {
            ;
        }

        if (channel_base_address->rSpi_SR.BIT.bSpi_BUSY)
        {
            ret_val = ER_SYS;
        }
        else
        {
            /* Ensure SPI is disabled so registers can be written to */
            channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;

            /* Set transfer mode to transfer_type */
            channel_base_address->rSpi_CTRLR0.BIT.bSpi_TMOD = transfer_data.transfer_type;
            spi_transfer_params[chan_num].transfer_mode = transfer_data.transfer_type;

            if (ER_OK
                    == (ret_val = setuprx(chan_num, transfer_data.transfer_mode_rx, transfer_data.read_buf,
                            transfer_data.data_frames)))
            {
                if (ER_OK
                        == (ret_val = setuptx(chan_num, transfer_data.transfer_mode_tx, transfer_data.write_buf,
                                transfer_data.data_frames)))
                {
                    /* Write transfer initiated */
                    spi_chan_params[chan_num].rx_outstanding = 1;

                    /* Read transfer initiated */
                    spi_chan_params[chan_num].tx_outstanding = 1;

                    /* Enable SPI */
                    channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 1;

                    switch (transfer_data.transfer_mode_tx)
                    {
                        case SPI_TRANSFER_MODE_BLOCKING:
                            if (SPI_TRANSFER_MODE_BLOCKING == transfer_data.transfer_mode_rx)
                            {
                                ret_val = spi_blockingfullduplex(chan_num);
                            }
                            else
                            {
                                ret_val = spi_blockingwrite(chan_num);
                            }
                        break;
                        case SPI_TRANSFER_MODE_DMA:
                            channel_base_address->rSpi_TDMACR.BIT.bSpi_TDMAE1 = 1; /* Disabled via hardware after block transfer is complete */ // @suppress("No break at end of case")
                        case SPI_TRANSFER_MODE_NON_BLOCKING:
                            if (SPI_TRANSFER_MODE_BLOCKING == transfer_data.transfer_mode_rx)
                            {
                                ret_val = spi_blockingread(chan_num);
                            }
                        break;
                        default:
                        {
                            ret_val = ER_PARAM;
                        }
                    }
                }
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_readwrite
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_istransferring
 *
 *  Return value:   Whether the channel is currently transferring or not
 *
 *  Parameters:     chan_num - The SPI channel number
 *
 *  Description:    True: Transferring data, False: Not transferring data
 *
 **********************************************************************************************************************/
bool spi_istransferring (uint8_t chan_num)
{
    return (spi_chan_params[chan_num].tx_outstanding || spi_chan_params[chan_num].rx_outstanding);
}
/***********************************************************************************************************************
 End of function spi_istransferring
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_transfer_cancel
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - SPI channel number
 *
 *  Description:    Aborts a transfer on an SPI channel
 *
 **********************************************************************************************************************/
void spi_transfer_cancel (uint8_t chan_num)
{
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    if (0 != channel_base_address)
    {
        /* Disable interrupts */
        channel_base_address->rSpi_IMR.LONG = 0;

        /* In-case the SPI is a slave, Disable MISO */
        channel_base_address->rSpi_CTRLR0.BIT.bSpi_SLV_OE = 1;

        /* Disable SPI - Clears Tx and Rx FIFOs */
        channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;

        /* reset transfer params */
        spi_transfer_params[chan_num].write_buf = 0;
        spi_transfer_params[chan_num].tx_remaining_frames = 0;
        spi_transfer_params[chan_num].read_buf = 0;
        spi_transfer_params[chan_num].rx_remaining_frames = 0;

        /* no Tx or Rx outstanding */
        spi_chan_params[chan_num].tx_outstanding = 0;
        spi_chan_params[chan_num].rx_outstanding = 0;

#ifdef r_dma_rzn1_spi_included

        /* Disable the DMA transfer if opened */
        if (channel_base_address->rSpi_TDMACR.BIT.bSpi_TDMAE1)
        {
            /* Disable DMA transfer */
            channel_base_address->rSpi_TDMACR.BIT.bSpi_TDMAE1 = 0;

            /* Disable Transmit DMA */
            channel_base_address->rSpi_DMACR.BIT.bSpi_TDMAE = 0;
            if (false == spi_dma[chan_num].Tx.reserve_mode)
            {
                /* Close the DMA Channel */
                R_DMA_Close(spi_dma[chan_num].Tx.DMAC_number, spi_dma[chan_num].Tx.channel);
                spi_dma[chan_num].Tx.channel = INVAL_DMA_CHAN;
            }
            else
            {
                /* Cancel DMA transfer */
                R_DMA_Control(spi_dma[chan_num].Tx.DMAC_number, spi_dma[chan_num].Tx.channel, DMA_CONTROL_FREE_CHAN,
                        (void *) 0);
            }
        }
        if (channel_base_address->rSpi_RDMACR.BIT.bSpi_RDMAE1)
        {
            /* Disable DMA transfer */
            channel_base_address->rSpi_RDMACR.BIT.bSpi_RDMAE1 = 0;

            /* Disable Transmit DMA */
            channel_base_address->rSpi_DMACR.BIT.bSpi_RDMAE = 0;
            if (false == spi_dma[chan_num].Rx.reserve_mode)
            {
                /* Close the DMA Channel */
                R_DMA_Close(spi_dma[chan_num].Rx.DMAC_number, spi_dma[chan_num].Rx.channel);
                spi_dma[chan_num].Rx.channel = INVAL_DMA_CHAN;
            }
            else
            {
                /* Cancel DMA transfer */
                R_DMA_Control(spi_dma[chan_num].Rx.DMAC_number, spi_dma[chan_num].Rx.channel, DMA_CONTROL_FREE_CHAN,
                        (void *) 0);
            }
        }

#endif /* r_dma_rzn1_spi_included */

        /* Inform interface the transfer is over */
        spi_transfer_completed(chan_num);
    }
}
/***********************************************************************************************************************
 End of function spi_transfer_cancel
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       setuptx
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  transfer_mode - Blocking/ NonBlocking/ DMA
 *                  write_buf - The location of the write buffer
 *                  data_frames - The number of data frames to write
 *
 *  Description:    Sets up SPI channel for next Tx transfer
 *
 **********************************************************************************************************************/
static ER_RET setuptx (uint8_t chan_num, spi_transfer_mode_t transfer_mode, uint16_t *write_buf, uint16_t data_frames)
{
    ER_RET ret_val = ER_OK;

    switch (transfer_mode)
    {
        case SPI_TRANSFER_MODE_BLOCKING:
            txblockingsetup(chan_num, write_buf, data_frames);
        break;
        case SPI_TRANSFER_MODE_NON_BLOCKING:
            txnonblockingsetup(chan_num, write_buf, data_frames);
        break;
        case SPI_TRANSFER_MODE_DMA:
            ret_val = txdmasetup(chan_num, write_buf, data_frames);
        break;
        default:
        {
            ret_val = ER_PARAM;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function setuptx
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       setuprx
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  transfer_mode - Blocking/ NonBlocking/ DMA
 *                  read_buf - The location of the read buffer
 *                  data_frames - The number of data frames to read
 *
 *  Description:    Sets up SPI channel for next Rx transfer
 *
 **********************************************************************************************************************/
static ER_RET setuprx (uint8_t chan_num, spi_transfer_mode_t transfer_mode, uint16_t *read_buf, uint16_t data_frames)
{
    ER_RET ret_val = ER_OK;

    switch (transfer_mode)
    {
        case SPI_TRANSFER_MODE_BLOCKING:
            rxblockingsetup(chan_num, read_buf, data_frames);
        break;
        case SPI_TRANSFER_MODE_NON_BLOCKING:
            rxnonblockingsetup(chan_num, read_buf, data_frames);
        break;
        case SPI_TRANSFER_MODE_DMA:
            ret_val = rxdmasetup(chan_num, read_buf, data_frames);
        break;
        default:
        {
            ret_val = ER_PARAM;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function setuprx
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       txblockingsetup
 *
 *  Return value:   None.
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  write_buf - The location of the write buffer
 *                  data_frames - The number of data frames to write
 *
 *  Description:    Sets up Tx Blocking transfer for the SPI channel
 *
 **********************************************************************************************************************/
static void txblockingsetup (uint8_t chan_num, uint16_t *write_buf, uint16_t data_frames)
{
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    /* Blocking mode - Mask relevant interrupts */
    channel_base_address->rSpi_IMR.BIT.bSpi_TXEIM = 0;
    channel_base_address->rSpi_IMR.BIT.bSpi_TXOIM = 0;

    /* Incase the SPI is a slave, Enable MISO */
    if (chan_num >= MIN_SPI_SLAVE)
    {
        channel_base_address->rSpi_CTRLR0.BIT.bSpi_SLV_OE = 0;
    }

    /* Save transfer info */
    spi_transfer_params[chan_num].write_buf = write_buf;
    spi_transfer_params[chan_num].tx_remaining_frames = data_frames;
    spi_transfer_params[chan_num].tx_transfer = SPI_TRANSFER_MODE_BLOCKING;
}
/***********************************************************************************************************************
 End of function txblockingsetup
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       txnonblockingsetup
 *
 *  Return value:   None.
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  write_buf - The location of the write buffer
 *                  data_frames - The number of data frames to write
 *
 *  Description:    Sets up Tx NonBlocking transfer for the SPI channel
 *
 **********************************************************************************************************************/
static void txnonblockingsetup (uint8_t chan_num, uint16_t *write_buf, uint16_t data_frames)
{
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    /* Non-blocking mode - Unmask Tx FIFO Empty interrupt */
    channel_base_address->rSpi_IMR.BIT.bSpi_TXEIM = 1;
    channel_base_address->rSpi_IMR.BIT.bSpi_TXOIM = 0;

    /* Set Tx FIFO threshold value */
    channel_base_address->rSpi_TXFTLR.BIT.bSpi_TFT = RX_THRESHOLD;
    ; /* Interrupt at 8 or less entries */

    /* Incase the SPI is a slave, Enable MISO */
    if (chan_num >= MIN_SPI_SLAVE)
    {
        channel_base_address->rSpi_CTRLR0.BIT.bSpi_SLV_OE = 0;
    }

    /* Save transfer info */
    spi_transfer_params[chan_num].write_buf = write_buf;
    spi_transfer_params[chan_num].tx_remaining_frames = data_frames;
    spi_transfer_params[chan_num].tx_transfer = SPI_TRANSFER_MODE_NON_BLOCKING;
}
/***********************************************************************************************************************
 End of function txnonblockingsetup
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       rxblockingsetup
 *
 *  Return value:   None.
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  read_buf - The location of the read buffer
 *                  data_frames - The number of data frames to read
 *
 *  Description:    Sets up Rx Blocking transfer for the SPI channel
 *
 **********************************************************************************************************************/
static void rxblockingsetup (uint8_t chan_num, uint16_t *read_buf, uint16_t data_frames)
{
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    /* Blocking mode - Mask relevant interrupts */
    channel_base_address->rSpi_IMR.BIT.bSpi_RXFIM = 0;
    channel_base_address->rSpi_IMR.BIT.bSpi_RXOIM = 0;
    channel_base_address->rSpi_IMR.BIT.bSpi_RXUIM = 0;

    /* If SPI channel is a master, set the number of data frames --Probably not needed for blocking read */
    if (chan_num < MIN_SPI_SLAVE)
    {
        ((SPI_M_Type *) channel_base_address)->rSpi_CTRLR1.BIT.bSpi_NDF = data_frames - 1; /* Blocking -> May be interrupted and can't keep up with hardware throughput */
    }

    /* Save transfer info */
    spi_transfer_params[chan_num].read_buf = read_buf;
    spi_transfer_params[chan_num].rx_remaining_frames = data_frames;
    spi_transfer_params[chan_num].rx_transfer = SPI_TRANSFER_MODE_BLOCKING;
}
/***********************************************************************************************************************
 End of function rxblockingsetup
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       rxnonblockingsetup
 *
 *  Return value:   None.
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  read_buf - The location of the read buffer
 *                  data_frames - The number of data frames to read
 *
 *  Description:    Sets up Rx NonBlocking transfer for the SPI channel
 *
 **********************************************************************************************************************/
static void rxnonblockingsetup (uint8_t chan_num, uint16_t *read_buf, uint16_t data_frames)
{
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;
    uint32_t th_data_offset = 0;
    uint8_t rx_threshold = 1; /* Interrupt at 1 or more entries (safe operation)
     - Slave does not know EXACTLY how many data frames the master will send */

    /* If SPI channel is a master, set the number of data frames */
    if (chan_num < MIN_SPI_SLAVE)
    {
        rx_threshold = RX_THRESHOLD; /* Interrupt at 8 or more entries */
        th_data_offset = rx_threshold - (data_frames % rx_threshold);

        /* Continuously receive the number of data frames specified PLUS however many frames left to generate the last interrupt*/
        ((SPI_M_Type *) channel_base_address)->rSpi_CTRLR1.BIT.bSpi_NDF =
                (data_frames + (th_data_offset % rx_threshold)) - 1;
    }

    /* Find the empty slots in the Receive FIFO */
    th_data_offset = rx_threshold - (data_frames % rx_threshold);

    /* Set Rx FIFO threshold value */
    channel_base_address->rSpi_RXFTLR.BIT.bSpi_RFT = rx_threshold - 1;

    /* Non-blocking mode - Unmask Rx FIFO Full interrupt */
    channel_base_address->rSpi_IMR.BIT.bSpi_RXFIM = 1;
    channel_base_address->rSpi_IMR.BIT.bSpi_RXOIM = 0;
    channel_base_address->rSpi_IMR.BIT.bSpi_RXUIM = 0;

    /* Save transfer info */
    spi_transfer_params[chan_num].read_buf = read_buf;
    spi_transfer_params[chan_num].frames_to_final_int = th_data_offset;
    spi_transfer_params[chan_num].rx_remaining_frames = data_frames;
    spi_transfer_params[chan_num].rx_transfer = SPI_TRANSFER_MODE_NON_BLOCKING;
}
/***********************************************************************************************************************
 End of function rxnonblockingsetup
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_allocate_dma_rx_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - SPI channel number
 *                  dma_chan - DMA channel number
 *
 *  Description:    Assigns a specified DMA channel to the SPI Rx channel
 *                      and set the SPI Rx channel to DMA retain mode
 *
 **********************************************************************************************************************/
ER_RET spi_allocate_dma_rx_chan (uint8_t chan_num, uint8_t dma_chan)
{
    ER_RET ret_val = ER_OK;
#ifdef r_dma_rzn1_spi_included
    DMA_CHAN_CTRL dma_chan_ctrl = DMA_DEFAULT_CHAN_CTRL;

    /* Attempt to Open DMA channel */
    if (ER_OK == (ret_val = R_DMA_Open(spi_dma[chan_num].Rx.DMAC_number, dma_chan)))
    {
        /* Set up DMA channel control */
        dma_chan_ctrl.SRC_HS.TYPE = HARDWARE;
        dma_chan_ctrl.SRC_HS.HS_INTERFACE = spi_dma[chan_num].Rx.HS_Interface;
        if (ER_OK
                == (ret_val = R_DMA_Control(spi_dma[chan_num].Rx.DMAC_number, dma_chan, DMA_CONTROL_SET_CHAN_CONFIG,
                        &dma_chan_ctrl)))
        {
            /* Register callback */
            if (ER_OK
                    != R_DMA_Control(spi_dma[chan_num].Rx.DMAC_number, dma_chan, DMA_CONTROL_SET_CALL_BACK,
                            (void *) &spi_dmac_callback))
            {
                /* Unable to register callback, cannot proceed */
                ret_val = ER_SYS;
                R_DMA_Close(spi_dma[chan_num].Rx.DMAC_number, dma_chan);
            }
        }
    }
    if (ER_OK == ret_val)
    {
        /* Save channel allocation */
        spi_dma[chan_num].Rx.channel = dma_chan;
        spi_dma[chan_num].Rx.reserve_mode = true;
    }

#else /* Not ifdef r_dma_rzn1_spi_included */
    /* No DMA driver therefore cannot use DMA operations */
    ret_val = ER_INVAL;
#endif
    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_allocate_dma_rx_chan
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_allocate_dma_tx_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - SPI channel number
 *                  dma_chan - DMA channel number
 *
 *  Description:    Assigns a specified DMA channel to the SPI Tx channel
 *                      and set the SPI Tx channel to DMA retain mode
 *
 **********************************************************************************************************************/
ER_RET spi_allocate_dma_tx_chan (uint8_t chan_num, uint8_t dma_chan)
{
    ER_RET ret_val = ER_OK;
#ifdef r_dma_rzn1_spi_included
    DMA_CHAN_CTRL dma_chan_ctrl = DMA_DEFAULT_CHAN_CTRL;

    /* Attempt to Open DMA channel */
    if (ER_OK == (ret_val = R_DMA_Open(spi_dma[chan_num].Tx.DMAC_number, dma_chan)))
    {
        /* Set up DMA channel control */
        dma_chan_ctrl.SRC_HS.TYPE = HARDWARE;
        dma_chan_ctrl.SRC_HS.HS_INTERFACE = spi_dma[chan_num].Tx.HS_Interface;
        if (ER_OK
                == (ret_val = R_DMA_Control(spi_dma[chan_num].Tx.DMAC_number, dma_chan, DMA_CONTROL_SET_CHAN_CONFIG,
                        &dma_chan_ctrl)))
        {
            /* Register callback */
            if (ER_OK
                    != R_DMA_Control(spi_dma[chan_num].Tx.DMAC_number, dma_chan, DMA_CONTROL_SET_CALL_BACK,
                            (void *) &spi_dmac_callback))
            {
                /* Unable to register callback, cannot proceed */
                ret_val = ER_SYS;
                R_DMA_Close(spi_dma[chan_num].Tx.DMAC_number, dma_chan);
            }
        }
    }
    if (ER_OK == ret_val)
    {
        /* Save channel allocation */
        spi_dma[chan_num].Tx.channel = dma_chan;
        spi_dma[chan_num].Tx.reserve_mode = true;
    }

#else /* Not ifdef r_dma_rzn1_spi_included */
    /* No DMA driver therefore cannot use DMA operations */
    ret_val = ER_INVAL;
#endif
    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_allocate_dma_tx_chan
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_release_dma_rx_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - SPI channel number
 *
 *  Description:    Unassigns the DMA channel from the SPI Rx channel
 *                      and sets the SPI Rx channel to DMA release mode
 *
 **********************************************************************************************************************/
void spi_release_dma_rx_chan (uint8_t chan_num)
{
#ifdef r_dma_rzn1_spi_included
    if (true == spi_dma[chan_num].Rx.reserve_mode)
    {
        /* Close the DMA channel */
        R_DMA_Close(spi_dma[chan_num].Rx.DMAC_number, spi_dma[chan_num].Rx.channel);

        /* Driver now in DO NOT Retain DMA mode */
        spi_dma[chan_num].Rx.reserve_mode = false;
        spi_dma[chan_num].Rx.channel = INVAL_DMA_CHAN;
    }
#endif
}
/***********************************************************************************************************************
 End of function spi_release_dma_rx_chan
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_release_dma_tx_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - SPI channel number
 *
 *  Description:    Unassigns the DMA channel from the SPI Tx channel
 *                      and sets the SPI Tx channel to DMA release mode
 *
 **********************************************************************************************************************/
void spi_release_dma_tx_chan (uint8_t chan_num)
{
#ifdef r_dma_rzn1_spi_included
    if (true == spi_dma[chan_num].Tx.reserve_mode)
    {
        /* Close the DMA channel */
        R_DMA_Close(spi_dma[chan_num].Tx.DMAC_number, spi_dma[chan_num].Tx.channel);

        /* Driver now in DO NOT Retain DMA mode */
        spi_dma[chan_num].Tx.reserve_mode = false;
        spi_dma[chan_num].Tx.channel = INVAL_DMA_CHAN;
    }
#endif
}
/***********************************************************************************************************************
 End of function spi_release_dma_tx_chan
 **********************************************************************************************************************/

#ifdef r_dma_rzn1_spi_included
/***********************************************************************************************************************
 *
 *  Function:       spi_unpack_dma_info
 *
 *  Return value:   Error status
 *
 *  Parameters:     dma_info - struct containing DMA information -
 *                                              DMA controller and handshaking interface
 *                  dma_req_info - packaged information about the DMA multiplexer request
 *
 *  Description:    Unpacks DMA specific information about the SPI channel
 *
 **********************************************************************************************************************/
static void spi_unpack_dma_info (spi_dma_raw_info *dma_info, uint8_t dma_req_info)
{
    dma_info->DMAC_number = (dma_req_info >> DMA_MUX_DMA_BIT) & DMA_MUX_DMA_MASK;
    dma_info->HS_Interface = (dma_req_info >> DMA_MUX_SRC_REQ_BIT) & DMA_MUX_SRC_REQ_MASK;
}
/***********************************************************************************************************************
 End of function spi_unpack_dma_info
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_assign_dma_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     dma_info - struct containing DMA information -
 *                                              DMA controller and channel
 *
 *  Description:    Assigns a free DMA channel to the SPI channel
 *
 **********************************************************************************************************************/
static ER_RET spi_assign_dma_chan (spi_dma_raw_info *dma_info)
{
    ER_RET ret_val = ER_OK;
    uint8_t i = 0;

    while (i <= (DMA_CHAN_7))
    {
        /* Attempt to Open DMA channel */
        if (ER_OK == (ret_val = R_DMA_Open(dma_info->DMAC_number, i)))
        {
            /* Save the channel allocation if opened */
            dma_info->channel = i;
            break;
        }
        i++;
    }
    if (ER_OK != ret_val)
    {
        /* Could not allocate free DMA channel to SPI channel */
        ret_val = ER_BUSY;
    }
    else
    {
        /* Register callback */
        if (ER_OK
                != R_DMA_Control(dma_info->DMAC_number, dma_info->channel, DMA_CONTROL_SET_CALL_BACK,
                        (void *) &spi_dmac_callback))
        {
            /* Unable to register callback, cannot proceed with the transfer */
            ret_val = ER_SYS;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_assign_dma_chan
 **********************************************************************************************************************/
#endif /* r_dma_rzn1_spi_included */

/***********************************************************************************************************************
 *
 *  Function:       rxdmasetup
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  read_buf - The location of the read buffer
 *                  data_frames - The number of data frames to read
 *
 *  Description:    Sets up Rx DMA transfer for the SPI channel (DMA <- SPI)
 *
 **********************************************************************************************************************/
static ER_RET rxdmasetup (uint8_t chan_num, uint16_t *read_buf, uint16_t data_frames)
{
    ER_RET ret_val = ER_OK;

#ifdef r_dma_rzn1_spi_included

    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;
    DMA_TRANS_CTRL dma_trans_ctrl = DMA_DEFAULT_TRANS_CTRL;

    if (false == spi_dma[chan_num].Rx.reserve_mode)
    {
        /* THE CURRENT MODE IS DMA RELEASE MODE */
        /* Allocate a DMA channel to the SPI channel */
        if (ER_OK == (ret_val = spi_assign_dma_chan( &spi_dma[chan_num].Rx)))
        {
            /* Set up DMA channel control */
            DMA_CHAN_CTRL dma_chan_ctrl = DMA_DEFAULT_CHAN_CTRL;
            dma_chan_ctrl.SRC_HS.TYPE = HARDWARE;
            dma_chan_ctrl.SRC_HS.HS_INTERFACE = spi_dma[chan_num].Rx.HS_Interface;
            ret_val = R_DMA_Control(spi_dma[chan_num].Rx.DMAC_number, spi_dma[chan_num].Rx.channel,
                    DMA_CONTROL_SET_CHAN_CONFIG, &dma_chan_ctrl);
        }
    }

    /* Configure DMA */
    dma_trans_ctrl.INT_EN = true;
    dma_trans_ctrl.TR_FLOW = PTM_P;
    dma_trans_ctrl.SRC = (uint32_t) & (channel_base_address->rSpi_DR.LONG);
    dma_trans_ctrl.DST = (uint32_t) read_buf;
    dma_trans_ctrl.SRC_TR_WIDTH = BITS16;
    dma_trans_ctrl.SRC_INCR = NO_CHANGE;
    dma_trans_ctrl.SRC_BRST_LEN = DATA_ITEMS_8;
    dma_trans_ctrl.BLOCK_SIZE = data_frames;

    if (ER_OK == ret_val)
    {
        ret_val = R_DMA_Control(spi_dma[chan_num].Rx.DMAC_number, spi_dma[chan_num].Rx.channel,
                DMA_CONTROL_SET_TRANS_CONFIG, &dma_trans_ctrl);
    }

    if (ER_OK == ret_val)
    {
        /* Configure SPI DMA register */
        channel_base_address->rSpi_DMACR.BIT.bSpi_RDMAE = 1;

        channel_base_address->rSpi_RDMACR.BIT.bSpi_SRC_BURST_SIZE = 2; /* 8 words per burst */
        channel_base_address->rSpi_RDMACR.BIT.bSpi_SRC_BLOCK_SIZE = data_frames; /* DMA transfers fixed to 16 bit word length */

        /* Rx DMA FIFO trigger level */
        channel_base_address->rSpi_DMARDLR.BIT.bSpi_DMARDLR = 7; /* 7:generate DMA request when 8 or more data entries present in Rx FIFO */

        /* Possibly unmask Rx underflow and overflow interrupts
         -- To catch errors in the ISR */

        /* If SPI channel is a master, set the number of data frames --Probably not needed for blocking read */
        if (chan_num < MIN_SPI_SLAVE)
        {
            ((SPI_M_Type *) channel_base_address)->rSpi_CTRLR1.BIT.bSpi_NDF = data_frames - 1; /* Observe: decremented value as seen in hardware manual */
        }

        /* DMA mode: Mask Rx FIFO interrupts */
        channel_base_address->rSpi_IMR.BIT.bSpi_RXFIM = 0;
        channel_base_address->rSpi_IMR.BIT.bSpi_RXOIM = 0;
        channel_base_address->rSpi_IMR.BIT.bSpi_RXUIM = 0;

        channel_base_address->rSpi_RDMACR.BIT.bSpi_RDMAE1 = 1; /* Disabled via hardware after block transfer is complete */

        if (ER_OK == R_DMA_Write(spi_dma[chan_num].Rx.DMAC_number, spi_dma[chan_num].Rx.channel, DMA_TRANSFER)) /* Enable the DMA channel */
        {
            /* Save transfer info */
            spi_transfer_params[chan_num].rx_transfer = SPI_TRANSFER_MODE_DMA;
        }
        else
        {
            ret_val = ER_SYS;
        }
    }

#else /* Not ifdef r_dma_rzn1_spi_included */
    /* No DMA driver therefore cannot perform DMA transfer */
    ret_val = ER_INVAL;

#endif

    return ret_val;
}
/***********************************************************************************************************************
 End of function rxdmasetup
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       txdmasetup
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  write_buf - The location of the write buffer
 *                  data_frames - The number of data frames to write
 *
 *  Description:    Sets up Tx DMA transfer for the SPI channel (DMA -> SPI)
 *
 **********************************************************************************************************************/
static ER_RET txdmasetup (uint8_t chan_num, uint16_t *write_buf, uint16_t data_frames)
{
    ER_RET ret_val = ER_OK;

#ifdef r_dma_rzn1_spi_included

    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;
    DMA_TRANS_CTRL dma_trans_ctrl = DMA_DEFAULT_TRANS_CTRL;

    if (false == spi_dma[chan_num].Tx.reserve_mode)
    {
        /* THE CURRENT MODE IS DMA RELEASE MODE */
        /* Allocate a DMA channel to the SPI channel */
        if (ER_OK == (ret_val = spi_assign_dma_chan( &spi_dma[chan_num].Tx)))
        {
            /* Set up DMA channel control */
            DMA_CHAN_CTRL dma_chan_ctrl = DMA_DEFAULT_CHAN_CTRL;
            dma_chan_ctrl.DST_HS.TYPE = HARDWARE;
            dma_chan_ctrl.DST_HS.HS_INTERFACE = spi_dma[chan_num].Tx.HS_Interface;
            ret_val = R_DMA_Control(spi_dma[chan_num].Tx.DMAC_number, spi_dma[chan_num].Tx.channel,
                    DMA_CONTROL_SET_CHAN_CONFIG, &dma_chan_ctrl);
        }
    }

    /* Configure DMA */
    dma_trans_ctrl.INT_EN = true;
    dma_trans_ctrl.TR_FLOW = MTP_P;
    dma_trans_ctrl.SRC = (uint32_t) write_buf;
    dma_trans_ctrl.DST = (uint32_t) & (channel_base_address->rSpi_DR.LONG);
    dma_trans_ctrl.DST_INCR = NO_CHANGE;
    dma_trans_ctrl.DST_TR_WIDTH = BITS16;
    dma_trans_ctrl.DST_BRST_LEN = DATA_ITEMS_8;
    dma_trans_ctrl.BLOCK_SIZE = data_frames;

    if (ER_OK == ret_val)
    {
        ret_val = R_DMA_Control(spi_dma[chan_num].Tx.DMAC_number, spi_dma[chan_num].Tx.channel,
                DMA_CONTROL_SET_TRANS_CONFIG, &dma_trans_ctrl);
    }

    if (ER_OK == ret_val)
    {
        /* Configure SPI DMA register */
        channel_base_address->rSpi_DMACR.BIT.bSpi_TDMAE = 1;

        channel_base_address->rSpi_TDMACR.BIT.bSpi_DEST_BURST_SIZE = 2; /* 8 words per burst */
        channel_base_address->rSpi_TDMACR.BIT.bSpi_DEST_BLOCK_SIZE = data_frames;

        /* Tx FIFO DMA trigger level */
        channel_base_address->rSpi_DMATDLR.BIT.bSpi_DMATDLR = 8; /* 8:generate DMA request when FIFO 1/2 full. */

        /* Possibly unmask Tx overflow interrupt
         -- To catch errors in the ISR */

        /* DMA mode: Mask Tx FIFO interrupts */
        channel_base_address->rSpi_IMR.BIT.bSpi_TXEIM = 0;
        channel_base_address->rSpi_IMR.BIT.bSpi_TXOIM = 0;

        /* In case the SPI is a slave, Enable MISO */
        if (chan_num >= MIN_SPI_SLAVE)
        {
            channel_base_address->rSpi_CTRLR0.BIT.bSpi_SLV_OE = 0;
        }

        if (ER_OK == R_DMA_Write(spi_dma[chan_num].Tx.DMAC_number, spi_dma[chan_num].Tx.channel, DMA_TRANSFER)) /* Enable the DMA channel */
        {
            /* Save transfer info */
            spi_transfer_params[chan_num].tx_transfer = SPI_TRANSFER_MODE_DMA;
        }
        else
        {
            ret_val = ER_SYS;
        }
    }

#else /* Not ifdef r_dma_rzn1_spi_included */
    /* No DMA driver therefore cannot perform DMA transfer */
    ret_val = ER_INVAL;

#endif

    return ret_val;
}
/***********************************************************************************************************************
 End of function txdmasetup
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_blockingwrite
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  write_buf - The location of the write buffer
 *                  data_frames - The number of data frames to write
 *
 *  Description:    Writes data from a buffer in memory across the SPI channel
 *
 **********************************************************************************************************************/

static ER_RET spi_blockingwrite (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    uint32_t x;
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    /* Transfer data */
    while (spi_transfer_params[chan_num].tx_remaining_frames)
    {
        spi_write_fifo(chan_num);

        /* Wait for transmit FIFO to not be full */
        for (x = 0; (x < SPI_TIMEOUT) && ( !channel_base_address->rSpi_SR.BIT.bSpi_TFNF); x++)
            ;

        /* End transfer if timeout occurred */
        if ( !channel_base_address->rSpi_SR.BIT.bSpi_TFNF)
        {
            ret_val = ER_TIMEOUT;
            break;
        }
    }

    if (ER_OK == ret_val)
    {
        /* Buffer has been successfully filled with data */
        /* Wait until buffer is empty indicating a complete transfer */
        for (x = 0; (x < SPI_TIMEOUT) && ( !channel_base_address->rSpi_SR.BIT.bSpi_TFE); x++)
        {
            ;
        }

        if ( !channel_base_address->rSpi_SR.BIT.bSpi_TFE)
        {
            /* Time out waiting for the transmit FIFO to empty */
            ret_val = ER_TIMEOUT;
        }
    }

    /* Clear the outstanding transfer */
    spi_chan_params[chan_num].tx_outstanding = 0;

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_blockingwrite
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_blockingread
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  read_buf - The location of the read buffer
 *                  data_frames - The number of data frames to read
 *
 *  Description:    Reads data from the SPI channel and populates a
 *                  buffer in memory with its contents
 *
 **********************************************************************************************************************/
static ER_RET spi_blockingread (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    uint32_t x;
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    /* Read data */
    while (spi_transfer_params[chan_num].rx_remaining_frames)
    {
        /* Wait for receive FIFO to not be empty */
        for (x = 0; (x < SPI_TIMEOUT) && ( !channel_base_address->rSpi_SR.BIT.bSpi_RFNE); x++)
            ;

        /* End transfer if timeout occurred */
        if ( !channel_base_address->rSpi_SR.BIT.bSpi_RFNE)
        {
            ret_val = ER_TIMEOUT;
            break;
        }
        spi_read_fifo(chan_num);
    }

    /* Clear the outstanding transfer */
    spi_chan_params[chan_num].rx_outstanding = 0;

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_blockingread
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_blockingfullduplex
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The SPI channel number
 *                  write_buf - The location of the write buffer
 *                  read_buf - The location of the read buffer
 *                  data_frames - The number of data frames to read
 *
 *  Description:    Reads data from the SPI channel and populates a
 *                  buffer in memory with its contents. Writes data
 *                  from a buffer in memory across the SPI channel
 *
 **********************************************************************************************************************/
static ER_RET spi_blockingfullduplex (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    uint32_t x;
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    /* Transfer data */
    while (spi_transfer_params[chan_num].tx_remaining_frames)
    {
        /* Wait for transmit FIFO to not be full or receive FIFO to not be empty*/
        for (x = 0;
                (x < SPI_TIMEOUT) && ( !channel_base_address->rSpi_SR.BIT.bSpi_TFNF)
                        && ( !channel_base_address->rSpi_SR.BIT.bSpi_RFNE); x++)
            ;

        /* End transfer if timeout occurred */
        if ( !channel_base_address->rSpi_SR.BIT.bSpi_TFNF)
        {
            ret_val = ER_TIMEOUT;
            break;
        }
        spi_read_fifo(chan_num);
        spi_write_fifo(chan_num);
    }

    if (ER_OK == ret_val)
    {
        /* Transmit complete, continue reading */
        while (spi_transfer_params[chan_num].rx_remaining_frames)
        {
            /* Wait for receive FIFO to not be empty */
            for (x = 0; (x < SPI_TIMEOUT) && ( !channel_base_address->rSpi_SR.BIT.bSpi_RFNE); x++)
                ;

            /* End transfer if timeout occurred */
            if ( !channel_base_address->rSpi_SR.BIT.bSpi_RFNE)
            {
                ret_val = ER_TIMEOUT;
                break;
            }
            spi_read_fifo(chan_num);
        }
    }

    /* Disable SPI - Clears Tx and Rx FIFOs, no need to flush after incomplete transfers */
    channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;

    /* Clear the outstanding transfers */
    spi_chan_params[chan_num].tx_outstanding = 0;
    spi_chan_params[chan_num].rx_outstanding = 0;

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_blockingfullduplex
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_read_fifo
 *
 *  Return value:   None.
 *
 *  Parameters:     chan_num - The SPI channel number
 *
 *  Description:    Reads data from the Receive FIFOt till it is empty of the
 *                  desired number of bytes have been read
 *
 **********************************************************************************************************************/
static void spi_read_fifo (uint8_t chan_num)
{
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    while (channel_base_address->rSpi_SR.BIT.bSpi_RFNE && spi_transfer_params[chan_num].rx_remaining_frames)
    {
        /* Load next Rx FIFO element to next buffer element */
        *spi_transfer_params[chan_num].read_buf = channel_base_address->rSpi_DR.LONG;
        spi_transfer_params[chan_num].read_buf++;
        spi_transfer_params[chan_num].rx_remaining_frames--;
    }
}
/***********************************************************************************************************************
 End of function spi_read_fifo
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_write_fifo
 *
 *  Return value:   None.
 *
 *  Parameters:     chan_num - The SPI channel number
 *
 *  Description:    Writes data to the transmit FIFO
 *
 **********************************************************************************************************************/
static void spi_write_fifo (uint8_t chan_num)
{
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;
    uint8_t max_write = tx_max_write(chan_num);

    while (max_write--)
    {
        /* Load next buffer element to Tx FIFO */
        channel_base_address->rSpi_DR.LONG = *spi_transfer_params[chan_num].write_buf;
        spi_transfer_params[chan_num].write_buf++;
        spi_transfer_params[chan_num].tx_remaining_frames--;
    }
}
/***********************************************************************************************************************
 End of function spi_write_fifo
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       tx_max_write
 *
 *  Return value:   max_write value
 *
 *  Parameters:     chan_num - The SPI channel number
 *
 *  Description:    Determines the maximum number of frames to write to the Tx
 *                  FIFO (minimum of three values - Remaining FIFO space, remaining
 *                        overall frames to send, difference between number of frames
 *                        received and number of frames sent in full duplex transfers)
 *
 **********************************************************************************************************************/
static uint8_t tx_max_write (uint8_t chan_num)
{
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;
    uint8_t max_write = 0;

    if (spi_transfer_params[chan_num].tx_remaining_frames
            < (SPI_FIFO_DEPTH - channel_base_address->rSpi_TXFLR.BIT.bSpi_TXTFL))
    {
        max_write = spi_transfer_params[chan_num].tx_remaining_frames;
    }
    else
    {
        max_write = SPI_FIFO_DEPTH - channel_base_address->rSpi_TXFLR.BIT.bSpi_TXTFL;
    }

    if ((SPI_TRANSFER_TYPE_TX_RX == spi_transfer_params[chan_num].transfer_mode) && (MIN_SPI_SLAVE > chan_num))
    {
        /* SPI channel is a master and operating in full duplex mode */
        if (max_write
                > (SPI_FIFO_DEPTH
                        - (spi_transfer_params[chan_num].rx_remaining_frames
                                - spi_transfer_params[chan_num].tx_remaining_frames)))
        {
            max_write =
            SPI_FIFO_DEPTH
                    - (spi_transfer_params[chan_num].rx_remaining_frames
                            - spi_transfer_params[chan_num].tx_remaining_frames);
        }
    }

    return max_write;
}
/***********************************************************************************************************************
 End of function tx_max_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       SPI_Tx_Rx_Flush
 *
 *  Return value:   None.
 *
 *  Parameters:     chan_num - The SPI channel number
 *
 *  Description:    In full duplex mode when the transmit has completed, dummy data
 *                  is sent to the Tx FIFO in order to 'Flush' the remaining received
 *                  data from the receive buffer.
 *
 **********************************************************************************************************************/
static void spi_tx_rx_flush (uint8_t chan_num)
{
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;
    uint8_t i = spi_transfer_params[chan_num].frames_to_final_int;

    for (; channel_base_address->rSpi_SR.BIT.bSpi_TFNF && i; i--)
    {
        channel_base_address->rSpi_DR.LONG = SPI_DUMMY_DATA;
    }
}
/***********************************************************************************************************************
 End of function spi_tx_rx_flush
 **********************************************************************************************************************/

#ifdef r_dma_rzn1_spi_included
/***********************************************************************************************************************
 *
 *  Function:       spi_dmac_callback
 *
 *  Return value:   None.
 *
 *  Parameters:     DMAC_number - The DMA Controller number
 *                  channel - Channel number of the DMAC
 *
 *  Description:    Call back function for DMA interrupts.
 *
 **********************************************************************************************************************/
static void spi_dmac_callback (uint8_t DMAC_number, uint8_t dma_channel)
{
    volatile SPI_S_Type *channel_base_address;
    uint8_t i = 0;
    uint8_t spi_chan = INVAL_SPI_CHAN;

    if (DMAC_1 == DMAC_number)
    {
        while (i < SPI_CHAN_5)
        {
            /* Determine the SPI channel number */
            if ((dma_channel == spi_dma[i].Rx.channel) || (dma_channel == spi_dma[i].Tx.channel))
            {
                spi_chan = i;
                break;
            }
            i++;
        }
    }
    else
    {
        i = SPI_CHAN_5;
        while (i < MAX_SPI_CHANNELS)
        {
            /* Determine the SPI channel number */
            if ((dma_channel == spi_dma[i].Rx.channel) || (dma_channel == spi_dma[i].Tx.channel))
            {
                spi_chan = i;
                break;
            }
            i++;
        }
    }

    if (INVAL_SPI_CHAN != spi_chan)
    {
        channel_base_address = spi_chan_params[spi_chan].base_address;

        /* If transfer complete, indicate such to the IF layer and call the user call back */
        switch (spi_transfer_params[spi_chan].transfer_mode)
        {
            case SPI_TRANSFER_TYPE_TX_RX: /* Determine if read or write transfer is complete */
                if (dma_channel == spi_dma[spi_chan].Tx.channel)
                {
                    if (false == spi_dma[spi_chan].Tx.reserve_mode)
                    {
                        /* THE CURRENT MODE IS DMA RELEASE MODE */
                        /* Close DMA Channel */
                        R_DMA_Close(DMAC_number, dma_channel);
                        spi_dma[spi_chan].Tx.channel = INVAL_DMA_CHAN;
                    }

                    /* SPI or MISO not disabled in Tx to ensure transmission of full FIFO contents */
                    /* Disable Transmit DMA */
                    channel_base_address->rSpi_DMACR.BIT.bSpi_TDMAE = 0;

                    /* No remaining data frames */
                    spi_transfer_params[spi_chan].tx_remaining_frames = 0;

                    /* No outstanding Tx transfers */
                    spi_chan_params[spi_chan].tx_outstanding = 0;
                }
                else
                {
                    /* Transfer complete when read complete */
                    if (false == spi_dma[spi_chan].Rx.reserve_mode)
                    {
                        /* THE CURRENT MODE IS DMA RELEASE MODE */
                        /* Close DMA Channel */
                        R_DMA_Close(DMAC_number, dma_channel);
                        spi_dma[spi_chan].Rx.channel = INVAL_DMA_CHAN;
                    }

                    /* Disable SPI - Clears Tx and Rx FIFOs */
                    channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;

                    /* Disable Receive DMA */
                    channel_base_address->rSpi_DMACR.BIT.bSpi_RDMAE = 0;

                    /* No remaining data frames */
                    spi_transfer_params[spi_chan].rx_remaining_frames = 0;

                    /* No outstanding transfers */
                    spi_chan_params[spi_chan].rx_outstanding = 0;

                    /* Set channel state to OPEN */
                    spi_transfer_completed(spi_chan);

                    /* Call user callback */
                    if (0 != spi_chan_callback[spi_chan])
                    {
                        spi_chan_callback[spi_chan](spi_chan);
                    }
                }
            break;
            case SPI_TRANSFER_TYPE_TX: /* Transfer complete */
                if (false == spi_dma[spi_chan].Tx.reserve_mode)
                {
                    /* THE CURRENT MODE IS DMA RELEASE MODE */
                    /* Close DMA Channel */
                    R_DMA_Close(DMAC_number, dma_channel);
                }

                /* SPI or MISO not disabled in Tx to ensure transmission of full FIFO contents */
                /* Disable Transmit DMA */
                channel_base_address->rSpi_DMACR.BIT.bSpi_TDMAE = 0;

                /* No remaining data frames */
                spi_transfer_params[spi_chan].tx_remaining_frames = 0;

                /* No outstanding transfers */
                spi_chan_params[spi_chan].tx_outstanding = 0;

                /* Set channel state to OPEN */
                spi_transfer_completed(spi_chan);

                /* Call user callback */
                if (0 != spi_chan_callback[spi_chan])
                {
                    spi_chan_callback[spi_chan](spi_chan);
                }
            break;
            case SPI_TRANSFER_TYPE_RX: /* Transfer complete */
                if (false == spi_dma[spi_chan].Rx.reserve_mode)
                {
                    /* THE CURRENT MODE IS DMA RELEASE MODE */
                    /* Close DMA Channel */
                    R_DMA_Close(DMAC_number, dma_channel);
                }

                /* Disable SPI - Clears Tx and Rx FIFOs */
                channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;

                /* Disable Receive DMA */
                channel_base_address->rSpi_DMACR.BIT.bSpi_RDMAE = 0;

                /* No remaining data frames */
                spi_transfer_params[spi_chan].rx_remaining_frames = 0;

                /* No outstanding transfers */
                spi_chan_params[spi_chan].rx_outstanding = 0;

                /* Set channel state to OPEN */
                spi_transfer_completed(spi_chan);

                /* Call user callback */
                if (0 != spi_chan_callback[spi_chan])
                {
                    spi_chan_callback[spi_chan](spi_chan);
                }
            break;
            default:
            break;
        }
    }
}
/***********************************************************************************************************************
 End of function spi_dmac_callback
 **********************************************************************************************************************/
#endif /* r_dma_rzn1_spi_included */
/***********************************************************************************************************************
 *
 *  Function:       handle_spi_interrupt
 *
 *  Return value:   none
 *
 *  Parameters:     irq_num_ptr - pointer to interrupt vector number
 *
 *  Description:    handle SPI Interrupt for 'chan_num'
 *
 **********************************************************************************************************************/
static void handle_spi_interrupt (IRQn_Type *irq_num_ptr)
{
    IRQn_Type irq_num = *irq_num_ptr;
    uint8_t chan_num = irq_num - RZN1_IRQ_SPI0;
    volatile SPI_S_Type *channel_base_address = spi_chan_params[chan_num].base_address;

    if ((channel_base_address->rSpi_ISR.BIT.bSpi_RXFIS) || (channel_base_address->rSpi_ISR.BIT.bSpi_TXEIS))
    {
        if ((SPI_TRANSFER_TYPE_TX_RX == spi_transfer_params[chan_num].transfer_mode)
                || (SPI_TRANSFER_TYPE_RX == spi_transfer_params[chan_num].transfer_mode))
        {
            /* Read Rx FIFO if above threshold */
            if (channel_base_address->rSpi_ISR.BIT.bSpi_RXFIS && spi_chan_params[chan_num].rx_outstanding)
            {
                spi_read_fifo(chan_num);
            }
        }

        if ((SPI_TRANSFER_TYPE_TX_RX == spi_transfer_params[chan_num].transfer_mode)
                || (SPI_TRANSFER_TYPE_TX == spi_transfer_params[chan_num].transfer_mode))
        {
            /* Write to Tx FIFO if below threshold */
            if (channel_base_address->rSpi_ISR.BIT.bSpi_TXEIS)
            {
                if (spi_chan_params[chan_num].tx_outstanding)
                {
                    spi_write_fifo(chan_num);
                }
                else
                {
                    spi_tx_rx_flush(chan_num);
                }
            }
        }

        /* If transfer complete, indicate such to the IF layer and call the user call back */
        switch (spi_transfer_params[chan_num].transfer_mode)
        {
            case SPI_TRANSFER_TYPE_TX_RX: /* Determine if read or write transfer is complete */
                if (( !spi_transfer_params[chan_num].tx_remaining_frames)
                        && (SPI_TRANSFER_MODE_NON_BLOCKING == spi_transfer_params[chan_num].tx_transfer))
                {
                    /* SPI or MISO not disabled in Tx to ensure transmission of full FIFO contents */
                    /* No outstanding Tx transfers */
                    spi_chan_params[chan_num].tx_outstanding = 0;
                }
                if (( !spi_transfer_params[chan_num].rx_remaining_frames)
                        && (SPI_TRANSFER_MODE_NON_BLOCKING == spi_transfer_params[chan_num].rx_transfer))
                {

                    /* Transfer complete when read complete */
                    /* Disable SPI - Clears Tx and Rx FIFOs */
                    channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;

                    /* Mask FIFO interrupts */
                    channel_base_address->rSpi_IMR.BIT.bSpi_TXEIM = 0;

                    channel_base_address->rSpi_IMR.BIT.bSpi_RXFIM = 0;

                    /* No outstanding transfers */
                    spi_chan_params[chan_num].rx_outstanding = 0;

                    /* Set channel state to OPEN */
                    spi_transfer_completed(chan_num);

                    /* Call user callback */
                    if (0 != spi_chan_callback[chan_num])
                    {
                        spi_chan_callback[chan_num](chan_num);
                    }
                }
            break;
            case SPI_TRANSFER_TYPE_TX:
                if (( !spi_transfer_params[chan_num].tx_remaining_frames)
                        && (SPI_TRANSFER_MODE_NON_BLOCKING == spi_transfer_params[chan_num].tx_transfer))
                {

                    /* Transfer complete */
                    /* SPI or MISO not disabled in Tx to ensure transmission of full FIFO contents */
                    /* Mask FIFO interrupts */
                    channel_base_address->rSpi_IMR.BIT.bSpi_TXEIM = 0;

                    /* No outstanding transfers */
                    spi_chan_params[chan_num].tx_outstanding = 0;

                    /* Set channel state to OPEN */
                    spi_transfer_completed(chan_num);

                    /* Call user callback */
                    if (0 != spi_chan_callback[chan_num])
                    {
                        spi_chan_callback[chan_num](chan_num);
                    }
                }
            break;
            case SPI_TRANSFER_TYPE_RX:
                if (( !spi_transfer_params[chan_num].rx_remaining_frames)
                        && (SPI_TRANSFER_MODE_NON_BLOCKING == spi_transfer_params[chan_num].rx_transfer))
                {

                    /* Transfer complete */
                    /* Disable SPI - Clears Tx and Rx FIFOs */
                    channel_base_address->rSpi_SSIENR.BIT.bSpi_SSIENR = 0;

                    /* Mask FIFO interrupts */
                    channel_base_address->rSpi_IMR.BIT.bSpi_RXFIM = 0;

                    /* No outstanding transfers */
                    spi_chan_params[chan_num].rx_outstanding = 0;

                    /* Set channel state to OPEN */
                    spi_transfer_completed(chan_num);

                    /* Call user callback */
                    if (0 != spi_chan_callback[chan_num])
                    {
                        spi_chan_callback[chan_num](chan_num);
                    }
                }
            break;
            default:
            break;
        }
    }
    else
    {
        /* Handling of other interrupts not yet supported, Therefore, they will be cleared regardless */
        /* Reading this register bit clears interrupts */
        channel_base_address->rSpi_ICR.BIT.bSpi_ICR;
    }
}
/***********************************************************************************************************************
 End of function handle_spi_interrupt
 **********************************************************************************************************************/