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
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_uart_rzn1.c
 * Description  :  UART driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "r_uart_rzn1_config.h"
#include "r_uart_rzn1_if.h"
#include "r_uart_rzn1.h"
#include "iodefine.h"
#include "r_sysctrl_rzn1_if.h"
#include "r_timer_rzn1_if.h"

#ifdef r_dma_rzn1_if_included
#include "r_dma_rzn1_if.h"
#endif

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define UART_FIFO_SIZE_RX       (16U)       /* 16 * 8-Bit-wide RX FIFO */
#define UART_FIFO_SIZE_TX       (16U)       /* 16 * 8-Bit-wide TX FIFO */

#define RX_FIFO_EMPTY           (1 << 0)
#define RX_FIFO_FULL            (1 << 1)
#define TX_FIFO_EMPTY           (1 << 2)
#define TX_FIFO_FULL            (1 << 3)

#define UART_INT_IID_MASK       (0x0F)
#define UART_IIR_MODEM_STATUS   (0)
#define UART_IIR_NO_INT         (0x01)
#define UART_IIR_THR_EMPTY      (0x02)
#define UART_IIR_RX_DATA_AVAIL  (0x04)
#define UART_IIR_RX_TIMEOUT     (0x05)
#define UART_IIR_RX_LINE_STATUS (0x06)
#define UART_IIR_BUSY_DETECT    (0x07)
#define UART_IIR_CHAR_TIMEOUT   (0x0C)
#define UART_DMA_MAX_BLOCKSIZE  (0x1FFF)

#define UART_INVALID_CHANNEL    (0xFF)

/* UART divider value can be 12-128                                         */
#define UART_CLOCK_DIVIDER      (68)
#define UART_CLK_FREQ  (SystemPLLFreq/UART_CLOCK_DIVIDER)

#define WAIT_NOTBUSY    (5000ul)        /* How long to wait for UART to be IDLE*/
#define WAIT_TEMT       (0xFFFFF)       /* How long to wait for Tx holding reg empty */

#define FULL_UART_INDEX(_chan) \
    ((_chan) - MIN_FULL_UART)
/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

typedef struct
{
    uint8_t *next_byte_ptr;
    uint32_t required_bytes; /* total number bytes to send or receive */
    uint32_t remaining_bytes; /* remaining bytes to send or receive */
} UART_BUFFER_PARAMS_T;

typedef struct
{
    volatile UART_r_Type *base_address;
    uint32_t tx_outstanding;
    uint32_t rx_outstanding;
    uart_transfer_complete_callback_t tx_completed_callback;
    uart_transfer_complete_callback_t rx_completed_callback;
} UART_CHANNEL_PARAMS_T;

#ifdef r_dma_rzn1_if_included
typedef struct
{
    uint8_t Rx;
    uint8_t Tx;
} uart_dma_req_info;

typedef struct
{
    uint8_t DMAC_number;
    uint8_t HS_Interface;
    uint8_t channel;
    bool reserve_mode;
} uart_dma_raw_info;

typedef struct
{
    uart_dma_raw_info Tx;
    uart_dma_raw_info Rx;
} uart_dma_info;

const uart_dma_req_info UART_DMA_REQ[MAX_UART_CHANNELS - MIN_FULL_UART] = // @suppress("Source line ordering")
        {
        { DMA_UART4_RX_REQ, DMA_UART4_TX_REQ },
        { DMA_UART5_RX_REQ, DMA_UART5_TX_REQ },
        { DMA_UART6_RX_REQ, DMA_UART6_TX_REQ },
        { DMA_UART7_RX_REQ, DMA_UART7_TX_REQ },
        { DMA_UART8_RX_REQ, DMA_UART8_TX_REQ }, };
#endif

/***********************************************************************************************************************
 *  External function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local (private) variables
 **********************************************************************************************************************/
static UART_CHANNEL_PARAMS_T uart_channels_params[MAX_UART_CHANNELS];
static UART_CHANNEL_CONFIG_T uart_channels_config[MAX_UART_CHANNELS];

static UART_BUFFER_PARAMS_T uart_chan_read_buff_params[MAX_UART_CHANNELS];
static UART_BUFFER_PARAMS_T uart_chan_write_buff_params[MAX_UART_CHANNELS];
#ifdef r_dma_rzn1_if_included
static uart_dma_info uart_dma[MAX_UART_CHANNELS - MIN_FULL_UART];
#endif
/***********************************************************************************************************************
 * Local (private) function declarations
 **********************************************************************************************************************/
static ER_RET uart_putchar (uint8_t chan_num, unsigned char c);
static unsigned char uart_getchar (uint8_t chan_num);
static void handle_uart_interrupt (IRQn_Type *irq_num_ptr);
static uint8_t uart_flush_rx_fifo (uint8_t chan_num);

#ifdef r_dma_rzn1_if_included
static ER_RET uart_assign_dma_chan (uart_dma_raw_info *dma_info, void *uart_dmac_callback);
static void uart_dmac_tx_callback (uint8_t DMAC_number, uint8_t dma_channel);
static void uart_dmac_rx_callback (uint8_t DMAC_number, uint8_t dma_channel);
static void uart_unpack_dma_info (uart_dma_raw_info *dma_info, uint8_t dma_req_info);
#endif

/***********************************************************************************************************************
 *
 *  Function:       uart_get_major_version_num
 *
 *  Return value:   UART driver Major version number
 *
 *  Parameters:     None
 *
 *  Description:    Gets the UART driver's Major version number
 *
 **********************************************************************************************************************/
uint8_t uart_get_major_version_num (void)
{
    return (uint8_t) UART_DRIVER_MAJOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function uart_get_major_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_get_minor_version_num
 *
 *  Return value:   UART driver Minor version number
 *
 *  Parameters:     None
 *
 *  Description:    Gets the UART driver's Minor version number
 *
 **********************************************************************************************************************/
uint8_t uart_get_minor_version_num (void)
{
    return (uint8_t) UART_DRIVER_MINOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function uart_get_minor_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_driver_init
 *
 *  Return value:   error status
 *
 *  Parameters:     void
 *
 *  Description:    Initialise UART Channel info for all supported channels.
 *
 **********************************************************************************************************************/
ER_RET uart_driver_init (void)
{
    ER_RET ret_val = ER_OK;
    uint32_t channel;

    for (channel = 0; channel < MAX_UART_CHANNELS; channel++)
    {
        uart_channels_params[channel].tx_outstanding = 0;
        uart_channels_params[channel].rx_outstanding = 0;
        uart_channels_params[channel].rx_completed_callback = (void *) 0;
        uart_channels_params[channel].tx_completed_callback = (void *) 0;
        uart_channels_params[channel].base_address = (void *) 0;
    }

#ifdef r_dma_rzn1_if_included
    for (channel = MIN_FULL_UART; channel < (MAX_UART_CHANNELS); channel++)
    {
        /* Initialise DMA information about the channels */
        /* Rx information */
        uart_dma[FULL_UART_INDEX(channel)].Rx.channel = INVAL_DMA_CHAN;
        uart_dma[FULL_UART_INDEX(channel)].Rx.reserve_mode = false;
        uart_unpack_dma_info( &uart_dma[FULL_UART_INDEX(channel)].Rx, UART_DMA_REQ[FULL_UART_INDEX(channel)].Rx);

        /* Tx information */
        uart_dma[FULL_UART_INDEX(channel)].Tx.channel = INVAL_DMA_CHAN;
        uart_dma[FULL_UART_INDEX(channel)].Tx.reserve_mode = false;
        uart_unpack_dma_info( &uart_dma[FULL_UART_INDEX(channel)].Tx, UART_DMA_REQ[FULL_UART_INDEX(channel)].Tx);
    }
#endif
    ret_val = R_SYSCTRL_SetUARTClkDivider(UART_CLOCK_DIVIDER);

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_driver_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_channel_open
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *
 *  Description:    Opens a UART channel
 *
 **********************************************************************************************************************/
ER_RET uart_channel_open (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num;
    uint32_t int_priority;
    volatile UART_r_Type *channel_base_address;

    /* Setup power management control & Enable Clock for UART channel */
    R_SYSCTRL_EnableUART(chan_num);

    if (chan_num < UART_CHAN_4)
    {
        channel_base_address = (volatile UART_r_Type *) (RZN1_UART1_BASE + (chan_num * 0x1000));
    }
    else
    {
        channel_base_address = (volatile UART_r_Type *) (RZN1_UART4_BASE + ((chan_num - UART_CHAN_4) * 0x1000));
    }
    uart_channels_params[chan_num].base_address = channel_base_address;

    /*uart_channel_transfer_state[chan_number] = (volatile UART_r_Type *)UART_TRANSFER_STATE_IDLE;*/

    /* set default configuration for UART Channel 'chan_num' */
    ret_val = uart_set_chan_config(chan_num, default_uart_chan_config);
    if (ER_OK == ret_val)
    {
        /* Set interrupt priority for UART channel & enable system interrupt */
        if (chan_num < 3)
        {
            irq_num = RZN1_IRQ_UART0 + chan_num;
        }
        else
        {
            irq_num = RZN1_IRQ_UART3 + (chan_num - 3);
        }
        if (R_BSP_InterruptRegisterCallback((IRQn_Type) irq_num, (bsp_int_cb_t) &handle_uart_interrupt)
                == MCU_INT_SUCCESS)
        {
            int_priority = UART_DEFAULT_INT_PRIORITY;
            ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
            if (MCU_INT_SUCCESS != ret_val)
            {
                ret_val = ER_SYS;
            }
            else
            {
                ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);
            }
        }
        else
        {
            ret_val = ER_SYS;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_channel_open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_channel_close
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *
 *  Description:    Closes a UART channel
 *
 **********************************************************************************************************************/
ER_RET uart_channel_close (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num;
    volatile UART_r_Type *channel_base_addr;

#ifdef r_dma_rzn1_if_included
    /* Close DMA channel if opened */
    uart_release_dma_rx_chan(chan_num);
    uart_release_dma_tx_chan(chan_num);
#endif
    /* Parameters are ok */
    if (FIT_NO_PTR != uart_channels_params[chan_num].base_address)
    {
        channel_base_addr = uart_channels_params[chan_num].base_address;

        /* Disable system interrupt */
        if (chan_num < 3)
        {
            irq_num = RZN1_IRQ_UART0 + chan_num;
        }
        else
        {
            irq_num = RZN1_IRQ_UART3 + (chan_num - 3);
        }
        ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);

        uart_channels_params[chan_num].tx_outstanding = 0;
        uart_channels_params[chan_num].rx_completed_callback = (void *) 0;
        uart_channels_params[chan_num].tx_completed_callback = (void *) 0;
        uart_channels_params[chan_num].base_address = (void *) 0;

        /* disable fifo */
        channel_base_addr->rUart_FCR_IIR.FCR.bUart_FIFOE = 0;

        /* Disable power control & Clock for UART channel */
        R_SYSCTRL_DisableUART(chan_num);
    }
    else
    {
        ret_val = ER_INVAL; /* UART channel not initialised */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_channel_close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_set_chan_config
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  channel_config - parity, flow_control, stopbits, databits, baudrate
 *
 *  Description:    Sets UART channel configuration
 *
 **********************************************************************************************************************/
ER_RET uart_set_chan_config (uint8_t chan_num, UART_CHANNEL_CONFIG_T channel_config)
{
    ER_RET ret_val = ER_OK;
    volatile UART_r_Type *channel_base_address;
    uint32_t dl_val;
    float dl_tmp;
    uint32_t i;
    uint16_t x;
    uint8_t parity_enable;
    uint8_t even_parity_sel;

    /* Parameters are ok */
    if (FIT_NO_PTR != uart_channels_params[chan_num].base_address)
    {
        /* UART channel is initialised */
        switch (channel_config.parity)
        {
            case UART_PARITY_NONE:
                parity_enable = 0;
                even_parity_sel = 0;
            break;
            case UART_PARITY_ODD:
                parity_enable = 0x01u;
                even_parity_sel = 0;
            break;
            case UART_PARITY_EVEN:
                parity_enable = 0x01u;
                even_parity_sel = 0x01u;
            break;
            default:
                ret_val = ER_PARAM;
        }
        dl_tmp = (float) UART_CLK_FREQ / (16 * (channel_config.baudrate));
        dl_val = (uint32_t)(dl_tmp + 0.5); /* round-off */
        if ((ER_OK == ret_val) && (channel_config.databits <= DATA_BITS_PER_CHAR_8)
            && (dl_val > 0) && (dl_val <= 65535)  /* 16 bits reserved for divisor latch. */
            && (channel_config.stopbits <= NO_OF_STOP_BITS_2)
            && (channel_config.flow_control <= UART_FLOW_CONTROL_HW))
        {
            /* Baud rate within acceptable range */
            /* Set the configuration for the channel */
            channel_base_address = uart_channels_params[chan_num].base_address;

            uart_flush_rx_fifo(chan_num);

            /* wait for UART to be IDLE */
            for (i = 0; i < WAIT_NOTBUSY; i++)
            {
                if (0 == channel_base_address->rUart_USR.BIT.bUart_BUSY)
                {
                    break;
                }
            }
            if (WAIT_NOTBUSY == i)
            {
                /* TIMED OUT */
                ret_val = ER_BUSY;
            }
            else
            {
                channel_base_address->rUart_LCR.BIT.bUart_DLAB = 1; /* Divisor Latch Access Bit enable */

                /*** Set according to parameters passed ***/
                channel_base_address->rUart_IER_DLH.DLH.bUart_DLH = (uint8_t)(dl_val >> 8); /* Upper byte of divisor latch*/
                channel_base_address->rUart_RBR_THR_DLL.DLL.bUart_DLL = (uint8_t) dl_val; /* Lower byte of divisor latch */
                channel_base_address->rUart_LCR.LONG = (0 << 7) /* Divisor Latch Access Bit disable */
                | (even_parity_sel << 4) /* odd/even parity */
                | (parity_enable << 3) /* parity en/disable */
                | (channel_config.stopbits << 2) /* 1 stop bit */
                | channel_config.databits; /* 8 data bits */
                channel_base_address->rUart_MCR.BIT.bUart_AFCE = channel_config.flow_control;

                /* Save configuration for UART Channel 'chan_num' */
                uart_channels_config[chan_num].parity = channel_config.parity;
                uart_channels_config[chan_num].flow_control = channel_config.flow_control;
                uart_channels_config[chan_num].stopbits = channel_config.stopbits;
                uart_channels_config[chan_num].databits = channel_config.databits;
                uart_channels_config[chan_num].baudrate = channel_config.baudrate;

                /* Wait 8 clock cycles of slowest clock */
                for (x = 0; x < 0xFFF; x++);
            }
        }
        else
        {
            ret_val = ER_PARAM;
        }
    }
    else
    {
        ret_val = ER_INVAL; /* UART channel not initialised */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_set_chan_config
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_get_chan_config
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  channel_config - where to store config:
 *                       parity, flow_control, stopbits, databits, baudrate
 *
 *  Description:    Gets UART channel configuration
 *
 **********************************************************************************************************************/
ER_RET uart_get_chan_config (uint8_t chan_num, UART_CHANNEL_CONFIG_T *channel_config)
{
    ER_RET ret_val = ER_OK;

    /* Parameters are ok */
    if (FIT_NO_PTR != uart_channels_params[chan_num].base_address)
    {
        /* UART channel is initialised */

        /* Save configuration for UART Channel 'chan_num' */
        channel_config->parity = uart_channels_config[chan_num].parity;
        channel_config->flow_control = uart_channels_config[chan_num].flow_control;
        channel_config->stopbits = uart_channels_config[chan_num].stopbits;
        channel_config->databits = uart_channels_config[chan_num].databits;
        channel_config->baudrate = uart_channels_config[chan_num].baudrate;
    }
    else
    {
        ret_val = ER_INVAL; /* UART channel not initialised */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_get_chan_config
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_allocate_dma_rx_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  dma_chan - DMA channel number
 *
 *  Description:    Assigns a specified DMA channel to the UART Rx channel
 *                      and set the UART Rx channel to DMA retain mode
 *
 **********************************************************************************************************************/
ER_RET uart_allocate_dma_rx_chan (uint8_t chan_num, uint8_t dma_chan)
{
    ER_RET ret_val = ER_OK;
#ifdef r_dma_rzn1_if_included
    DMA_CHAN_CTRL dma_chan_ctrl = DMA_DEFAULT_CHAN_CTRL;

    /* Attempt to Open DMA channel */
    if (ER_OK == (ret_val = R_DMA_Open(uart_dma[FULL_UART_INDEX(chan_num)].Rx.DMAC_number, dma_chan)))
    {
        /* Set up DMA channel control */
        dma_chan_ctrl.SRC_HS.TYPE = HARDWARE;
        dma_chan_ctrl.SRC_HS.HS_INTERFACE = uart_dma[FULL_UART_INDEX(chan_num)].Rx.HS_Interface;
        if (ER_OK
                == (ret_val = R_DMA_Control(uart_dma[FULL_UART_INDEX(chan_num)].Rx.DMAC_number, dma_chan,
                        DMA_CONTROL_SET_CHAN_CONFIG, &dma_chan_ctrl)))
        {
            /* Register callback */
            if (ER_OK
                    != R_DMA_Control(uart_dma[FULL_UART_INDEX(chan_num)].Rx.DMAC_number, dma_chan,
                            DMA_CONTROL_SET_CALL_BACK, (void *) &uart_dmac_rx_callback))
            {
                /* Unable to register callback, cannot proceed */
                ret_val = ER_SYS;
                R_DMA_Close(uart_dma[FULL_UART_INDEX(chan_num)].Rx.DMAC_number, dma_chan);
            }
        }
    }
    if (ER_OK == ret_val)
    {
        /* Save channel allocation */
        uart_dma[FULL_UART_INDEX(chan_num)].Rx.channel = dma_chan;
        uart_dma[FULL_UART_INDEX(chan_num)].Rx.reserve_mode = true;
    }

#else /* Not ifdef r_dma_rzn1_if_included */

    /* No DMA driver therefore cannot use DMA operations */
    ret_val = ER_INVAL;
#endif
    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_allocate_dma_rx_chan
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_allocate_dma_tx_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  dma_chan - DMA channel number
 *
 *  Description:    Assigns a specified DMA channel to the UART Tx channel
 *                      and set the UART Tx channel to DMA retain mode
 *
 **********************************************************************************************************************/
ER_RET uart_allocate_dma_tx_chan (uint8_t chan_num, uint8_t dma_chan)
{
    ER_RET ret_val = ER_OK;
#ifdef r_dma_rzn1_if_included
    DMA_CHAN_CTRL dma_chan_ctrl = DMA_DEFAULT_CHAN_CTRL;

    /* Attempt to Open DMA channel */
    if (ER_OK == (ret_val = R_DMA_Open(uart_dma[FULL_UART_INDEX(chan_num)].Tx.DMAC_number, dma_chan)))
    {
        /* Set up DMA channel control */
        dma_chan_ctrl.DST_HS.TYPE = HARDWARE;
        dma_chan_ctrl.DST_HS.HS_INTERFACE = uart_dma[FULL_UART_INDEX(chan_num)].Tx.HS_Interface;
        if (ER_OK == (ret_val = R_DMA_Control(uart_dma[FULL_UART_INDEX(chan_num)].Tx.DMAC_number, dma_chan,
                        DMA_CONTROL_SET_CHAN_CONFIG, &dma_chan_ctrl)))
        {
            /* Register callback */
            if (ER_OK != R_DMA_Control(uart_dma[FULL_UART_INDEX(chan_num)].Tx.DMAC_number, dma_chan,
                            DMA_CONTROL_SET_CALL_BACK, (void *) &uart_dmac_tx_callback))
            {
                /* Unable to register callback, cannot proceed */
                ret_val = ER_SYS;
                R_DMA_Close(uart_dma[FULL_UART_INDEX(chan_num)].Tx.DMAC_number, dma_chan);
            }
        }
    }
    if (ER_OK == ret_val)
    {
        /* Save channel allocation */
        uart_dma[FULL_UART_INDEX(chan_num)].Tx.channel = dma_chan;
        uart_dma[FULL_UART_INDEX(chan_num)].Tx.reserve_mode = true;
    }

#else /* Not ifdef r_dma_rzn1_if_included */
    /* No DMA driver therefore cannot use DMA operations */
    ret_val = ER_INVAL;
#endif
    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_allocate_dma_tx_chan
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_release_dma_rx_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *
 *  Description:    Unassigns the DMA channel from the UART Rx channel
 *                      and sets the UART Rx channel to DMA release mode
 *
 **********************************************************************************************************************/
void uart_release_dma_rx_chan (uint8_t chan_num)
{
#ifdef r_dma_rzn1_if_included
    if (true == uart_dma[FULL_UART_INDEX(chan_num)].Rx.reserve_mode)
    {
        /* Close the DMA channel */
        R_DMA_Close(uart_dma[FULL_UART_INDEX(chan_num)].Rx.DMAC_number, uart_dma[FULL_UART_INDEX(chan_num)].Rx.channel);

        /* Driver now in DO NOT Retain DMA mode */
        uart_dma[FULL_UART_INDEX(chan_num)].Rx.reserve_mode = false;
        uart_dma[FULL_UART_INDEX(chan_num)].Rx.channel = INVAL_DMA_CHAN;
    }
#endif
}
/***********************************************************************************************************************
 End of function uart_release_dma_rx_chan
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_release_dma_tx_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *
 *  Description:    Unassigns the DMA channel from the UART Tx channel
 *                      and sets the UART Tx channel to DMA release mode
 *
 **********************************************************************************************************************/
void uart_release_dma_tx_chan (uint8_t chan_num)
{
#ifdef r_dma_rzn1_if_included
    if (true == uart_dma[FULL_UART_INDEX(chan_num)].Tx.reserve_mode)
    {
        /* Close the DMA channel */
        R_DMA_Close(uart_dma[FULL_UART_INDEX(chan_num)].Tx.DMAC_number, uart_dma[FULL_UART_INDEX(chan_num)].Tx.channel);

        /* Driver now in DO NOT Retain DMA mode */
        uart_dma[FULL_UART_INDEX(chan_num)].Tx.reserve_mode = false;
        uart_dma[FULL_UART_INDEX(chan_num)].Tx.channel = INVAL_DMA_CHAN;
    }
#endif
}
/***********************************************************************************************************************
 End of function uart_release_dma_tx_chan
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_transfer_cancel
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *
 *  Description:    Aborts a transfer on a UART channel
 *
 **********************************************************************************************************************/
ER_RET uart_transfer_cancel (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    volatile UART_r_Type *chan_base_addr;
    uint32_t actual_total_bytes;

    /* Parameters are ok */
    if (FIT_NO_PTR != uart_channels_params[chan_num].base_address)
    {
        /* cancel the current transfer for this channel */

        chan_base_addr = uart_channels_params[chan_num].base_address;

        if (1 == uart_channels_params[chan_num].tx_outstanding)
        {
            /* disable tx interrupt */
            chan_base_addr->rUart_IER_DLH.IER.bUart_PTIME = 0;
            chan_base_addr->rUart_IER_DLH.IER.bUart_ETBEI = 0;

            /* disable fifo */
            chan_base_addr->rUart_FCR_IIR.FCR.bUart_FIFOE = 0;

            uart_channels_params[chan_num].tx_outstanding = 0;
            uart_chan_read_buff_params[chan_num].next_byte_ptr = (uint8_t *) 0;
            uart_chan_write_buff_params[chan_num].next_byte_ptr = (uint8_t *) 0;
            actual_total_bytes = uart_chan_read_buff_params[chan_num].required_bytes
                    - uart_chan_read_buff_params[chan_num].remaining_bytes;
            uart_chan_read_buff_params[chan_num].required_bytes = 0;
            uart_chan_read_buff_params[chan_num].remaining_bytes = 0;

            actual_total_bytes = uart_chan_write_buff_params[chan_num].required_bytes
                    - uart_chan_write_buff_params[chan_num].remaining_bytes;
            uart_chan_write_buff_params[chan_num].required_bytes = 0;
            uart_chan_write_buff_params[chan_num].remaining_bytes = 0;

            /* inform UART driver interface that UART channel is no longer busy */
            tx_transfer_completed(chan_num);
#ifdef r_dma_rzn1_if_included
            /* Disable the DMA transfer if opened */
            if ((MIN_FULL_UART <= chan_num) && ((UART_f_Type *) chan_base_addr)->rUart_TDMACR.BIT.bUart_TDMAE)
            {
                /* disable DMA transfer */
                ((UART_f_Type *) chan_base_addr)->rUart_TDMACR.BIT.bUart_TDMAE = 0;
                if (false == uart_dma[FULL_UART_INDEX(chan_num)].Tx.reserve_mode)
                {
                    /* Close the DMA Channel */
                    R_DMA_Close(uart_dma[FULL_UART_INDEX(chan_num)].Tx.DMAC_number,
                            uart_dma[FULL_UART_INDEX(chan_num)].Tx.channel);
                    uart_dma[FULL_UART_INDEX(chan_num)].Tx.channel =
                    INVAL_DMA_CHAN;
                }
                else
                {
                    /* Cancel DMA transfer */
                    R_DMA_Control(uart_dma[FULL_UART_INDEX(chan_num)].Tx.DMAC_number,
                            uart_dma[FULL_UART_INDEX(chan_num)].Tx.channel, DMA_CONTROL_FREE_CHAN, (void *) 0);
                }
            }
#endif

            /* inform application that transfer has completed */
            if (FIT_NO_PTR != uart_channels_params[chan_num].tx_completed_callback)
            {
                (uart_channels_params[chan_num].tx_completed_callback)(chan_num, actual_total_bytes);

                /* Set tx_completed_callback back to NULL before next tx transaction */
                uart_channels_params[chan_num].tx_completed_callback = (void *) 0;
            }
        }
        else if (1 == uart_channels_params[chan_num].rx_outstanding)
        {
            chan_base_addr->rUart_IER_DLH.IER.bUart_ERBFI = 0;
            uart_flush_rx_fifo(chan_num);
            chan_base_addr->rUart_FCR_IIR.FCR.bUart_FIFOE = 0;
            uart_channels_params[chan_num].rx_outstanding = 0;
            uart_chan_write_buff_params[chan_num].next_byte_ptr = (uint8_t*) 0;
            actual_total_bytes = uart_chan_write_buff_params[chan_num].required_bytes
                    - uart_chan_write_buff_params[chan_num].remaining_bytes;
            uart_chan_write_buff_params[chan_num].required_bytes = 0;
            uart_chan_read_buff_params[chan_num].next_byte_ptr = (uint8_t*) 0;
            actual_total_bytes = uart_chan_read_buff_params[chan_num].required_bytes
                    - uart_chan_read_buff_params[chan_num].remaining_bytes;
            uart_chan_read_buff_params[chan_num].required_bytes = 0;
            rx_transfer_completed(chan_num);
#ifdef r_dma_rzn1_if_included
            /* Disable the DMA transfer if opened */
            if ((MIN_FULL_UART <= chan_num) && ((UART_f_Type *) chan_base_addr)->rUart_RDMACR.BIT.bUart_RDMAE)
            {
                ((UART_f_Type*) chan_base_addr)->rUart_RDMACR.BIT.bUart_RDMAE = 0;
                if (false == uart_dma[FULL_UART_INDEX(chan_num)].Rx.reserve_mode)
                {
                    R_DMA_Close(uart_dma[FULL_UART_INDEX(chan_num)].Rx.DMAC_number,
                            uart_dma[FULL_UART_INDEX(chan_num)].Rx.channel);
                    uart_dma[FULL_UART_INDEX(chan_num)].Rx.channel =
                    INVAL_DMA_CHAN;
                }
                else
                {
                    R_DMA_Control(uart_dma[FULL_UART_INDEX(chan_num)].Rx.DMAC_number,
                            uart_dma[FULL_UART_INDEX(chan_num)].Rx.channel, DMA_CONTROL_FREE_CHAN, (void *) 0);
                }
            }
#endif
            if (FIT_NO_PTR != uart_channels_params[chan_num].rx_completed_callback)
            {
                (uart_channels_params[chan_num].rx_completed_callback)(chan_num, actual_total_bytes);
                uart_channels_params[chan_num].rx_completed_callback = FIT_NO_PTR;
            }
        }
        else
        {
            /* Do nothing */
            ;
        }
    }
    else
    {
        ret_val = ER_INVAL; /* UART channel not initialised */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_transfer_cancel
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       reset
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *
 *  Description:    Resets a UART channel
 *
 **********************************************************************************************************************/
ER_RET uart_reset (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    uint32_t chan_base_address;

    /* Parameters are ok */
    chan_base_address = (uint32_t)(uart_channels_params[chan_num].base_address);
    if (0 != chan_base_address)
    {
        /* UART channel is initialised */

        ret_val = R_UART_Close(chan_num);
        if (ER_OK == ret_val)
        {
            Delay_usec(500000); /* Delay 500 msecs */

            /* Initialize UART driver and Re-open UART Channel */
            ret_val = R_UART_Open(chan_num);
        }
    }
    else
    {
        ret_val = ER_INVAL; /* UART channel not initialised */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_reset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_sync_write
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  buf - pointer to buffer with data to be written
 *                  num_chars - number of characters to write
 *                  num_chars_ptr - pointer to where actual num chars written will be stored
 *
 *  Description:    Writes a buffer of data to a UART channel & waits for completion.
 *
 **********************************************************************************************************************/
ER_RET uart_sync_write (uint8_t chan_num, const uint8_t* buf, size_t num_chars, size_t *num_chars_ptr)
{
    ER_RET ret_val = ER_OK;
    uint32_t i;

    /* Parameters are ok */
    if (FIT_NO_PTR != uart_channels_params[chan_num].base_address)
    {
        /* UART channel is initialised */

        for (i = 0; i < num_chars; i++)
        {
            ret_val = uart_putchar(chan_num, buf[i]);
            if (ER_OK != ret_val)
            {
                break;
            }
        }
        *num_chars_ptr = i;
    }
    else
    {
        ret_val = ER_INVAL; /* UART channel not initialised */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_sync_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_sync_read
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  buf - pointer to buffer where data received should be stored
 *                  num_chars - number of characters to read
 *                  num_chars_ptr - pointer to where actual num chars read will be stored
 *
 *  Description:    Reads data from a UART channel & waits for completion.
 *
 **********************************************************************************************************************/
ER_RET uart_sync_read (uint8_t chan_num, uint8_t* buf, size_t num_chars, size_t *num_chars_ptr)
{
    ER_RET ret_val = ER_OK;
    uint32_t i;
    unsigned char c;

    /* Parameters are ok */
    if (FIT_NO_PTR != uart_channels_params[chan_num].base_address)
    {
        /* UART channel is initialised */

        for (i = 0; i < num_chars; i++)
        {
            c = uart_getchar(chan_num);
            buf[i] = c;
        }
        *num_chars_ptr = i;
    }
    else
    {
        ret_val = ER_INVAL; /* UART channel not initialised */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_sync_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_flush_rx_fifo
 *
 *  Return value:   Number of non-zero elements flushed.
 *
 *  Parameters:     chan_num - UART channel number
 *
 *  Description:    Reads the data in the fifo to effectively flush it out
 *
 **********************************************************************************************************************/
static uint8_t uart_flush_rx_fifo (uint8_t chan_num)
{
    volatile UART_r_Type *chan_base_addr;
    unsigned char c;
    uint8_t i;
    uint8_t elements_flushed = 0;

    chan_base_addr = uart_channels_params[chan_num].base_address;

    for (i = 0; i < UART_FIFO_SIZE_RX; i++)
    {
        c = (unsigned char) chan_base_addr->rUart_RBR_THR_DLL.LONG;
        if (0 != c)
        {
            elements_flushed++;
        }
    }
    return elements_flushed;
}
/***********************************************************************************************************************
 End of function uart_flush_rx_fifo
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_async_read
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  buf - pointer to buffer where data received should be stored
 *                  num_chars - number of characters to read
 *                  rx_complete_callback - rx callback function, may be NULL e.g. if already set
 *
 *  Description:    Initiates data read from a UART channel.
 *                  Does not wait for completion unless no callback has been set
 *
 **********************************************************************************************************************/
ER_RET uart_async_read (uint8_t chan_num, uint8_t* buf, size_t num_chars,
        uart_transfer_complete_callback_t rx_complete_callback)
{
    ER_RET ret_val = ER_OK;
    volatile UART_r_Type *chan_base_addr;

    /* Parameters are ok */
    if (FIT_NO_PTR != uart_channels_params[chan_num].base_address)
    {
        /* UART channel is initialised */
        if (FIT_NO_PTR != rx_complete_callback)
        {
            uart_channels_params[chan_num].rx_completed_callback = rx_complete_callback;
        }
        else
        {
            /* rx callback should already be set for async transfer */
            if (((void *) 0 == uart_channels_params[chan_num].rx_completed_callback) || (0 == num_chars))
            {
                ret_val = ER_PARAM;
            }
        }
    }
    else
    {
        ret_val = ER_INVAL; /* UART channel not initialised */
    }

    if (ER_OK == ret_val)
    {
        uart_channels_params[chan_num].rx_outstanding = 1;
        uart_chan_read_buff_params[chan_num].next_byte_ptr = (uint8_t *) buf;
        uart_chan_read_buff_params[chan_num].remaining_bytes = num_chars;
        uart_chan_read_buff_params[chan_num].required_bytes = num_chars;

        chan_base_addr = uart_channels_params[chan_num].base_address;

        /* Rx FIFO trigger level */
        chan_base_addr->rUart_FCR_IIR.FCR.bUart_RCVR = 0; /* 0:generate interrupt when 1 character or more received into FIFO  */

        /* Reset the Rx FIFO  */
        chan_base_addr->rUart_FCR_IIR.FCR.bUart_RFIFOR = 1;

        /* Enable the FIFO */
        chan_base_addr->rUart_FCR_IIR.FCR.bUart_FIFOE = 1;

        /* Enable rx interrupt */
        chan_base_addr->rUart_IER_DLH.IER.bUart_ERBFI = 1;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_async_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_async_write
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  buf - pointer to buffer with data to be written
 *                  num_chars - number of characters to read
 *                  tx_complete_callback - rx callback function, may be NULL e.g. if already set
 *
 *  Description:    Initiates data write to a UART channel.
 *                  Does not wait for completion unless no callback has been set
 *
 **********************************************************************************************************************/
ER_RET uart_async_write (uint8_t chan_num, const uint8_t* buf, size_t num_chars,
        uart_transfer_complete_callback_t tx_complete_callback)
{
    ER_RET ret_val = ER_OK;
    volatile UART_r_Type *chan_base_addr;

    /* Parameters are ok */
    if (FIT_NO_PTR != uart_channels_params[chan_num].base_address)
    {
        /* UART channel is initialised */

        if (FIT_NO_PTR != tx_complete_callback)
        {
            uart_channels_params[chan_num].tx_completed_callback = tx_complete_callback;
        }
        else
        {
            /* tx callback should already be set for async transfer */
            if (((void *) 0 == uart_channels_params[chan_num].tx_completed_callback) || (0 == num_chars))
            {
                ret_val = ER_PARAM;
            }
        }
    }
    else
    {
        ret_val = ER_INVAL; /* UART channel not initialised */
    }

    if (ER_OK == ret_val)
    {
        uart_channels_params[chan_num].tx_outstanding = 1;
        uart_chan_write_buff_params[chan_num].next_byte_ptr = (uint8_t *) buf;
        uart_chan_write_buff_params[chan_num].remaining_bytes = num_chars;
        uart_chan_write_buff_params[chan_num].required_bytes = num_chars;

        chan_base_addr = uart_channels_params[chan_num].base_address;

        /* Tx FIFO empty trigger level */
        chan_base_addr->rUart_FCR_IIR.FCR.bUart_TET = 0; /* 0:generate interrupt when FIFO empty.  (3; 1/2 full)  */

        /* Reset the Tx FIFO  */
        chan_base_addr->rUart_FCR_IIR.FCR.bUart_XFIFOR = 1;

        /* Enable the FIFO */
        chan_base_addr->rUart_FCR_IIR.FCR.bUart_FIFOE = 1;

        /* Start filling the Tx FIFO */
        while ((1 == chan_base_addr->rUart_USR.BIT.bUart_TFNF)
                && (uart_chan_write_buff_params[chan_num].remaining_bytes > 0))
        {
            chan_base_addr->rUart_RBR_THR_DLL.RBR_THR.bUart_RBR_THR =
                    *(uart_chan_write_buff_params[chan_num].next_byte_ptr);
            uart_chan_write_buff_params[chan_num].next_byte_ptr++;
            uart_chan_write_buff_params[chan_num].remaining_bytes--;
        }

        /* Enable tx interrupt */
        chan_base_addr->rUart_IER_DLH.IER.bUart_PTIME = 1;
        chan_base_addr->rUart_IER_DLH.IER.bUart_ETBEI = 1;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_async_write
 **********************************************************************************************************************/

#ifdef r_dma_rzn1_if_included
/***********************************************************************************************************************
 *
 *  Function:       uart_unpack_dma_info
 *
 *  Return value:   Error status
 *
 *  Parameters:     dma_info - struct containing DMA information -
 *                                              DMA controller and handshaking interface
 *                  dma_req_info - packaged information about the DMA multiplexer request
 *
 *  Description:    Unpacks DMA specific information about the UART channel
 *
 **********************************************************************************************************************/
static void uart_unpack_dma_info (uart_dma_raw_info *dma_info, uint8_t dma_req_info)
{
    dma_info->DMAC_number = (dma_req_info >> DMA_MUX_DMA_BIT) & DMA_MUX_DMA_MASK;
    dma_info->HS_Interface = (dma_req_info >> DMA_MUX_SRC_REQ_BIT) & DMA_MUX_SRC_REQ_MASK;
}
/***********************************************************************************************************************
 End of function uart_unpack_dma_info
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_assign_dma_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     dma_info - struct containing DMA information -
 *                                              DMA controller and channel
 *
 *  Description:    Assigns a free DMA channelto the UART channel
 *
 **********************************************************************************************************************/
static ER_RET uart_assign_dma_chan (uart_dma_raw_info *dma_info, void *uart_dmac_callback)
{
    ER_RET ret_val = ER_OK;
    uint8_t i;

    for (i = 0; i <= (DMA_CHAN_7); i++)
    {
        /* Attempt to Open DMA channel */
        if (ER_OK == (ret_val = R_DMA_Open(dma_info->DMAC_number, i)))
        {
            /* Save the channel allocation if opened */
            dma_info->channel = i;
            break;
        }
    }
    if (ER_OK != ret_val)
    {
        /* Could not allocate free DMA channel to UART channel */
        ret_val = ER_BUSY;
    }
    else
    {
        /* Register callback */
        if (ER_OK
                != R_DMA_Control(dma_info->DMAC_number, dma_info->channel, DMA_CONTROL_SET_CALL_BACK,
                        uart_dmac_callback))
        {
            /* Unable to register callback, cannot proceed with the transfer */
            ret_val = ER_SYS;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_assign_dma_chan
 **********************************************************************************************************************/
#endif /* r_dma_rzn1_if_included */

/***********************************************************************************************************************
 *
 *  Function:       uart_dma_read
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  num_chars - number of characters to read
 *
 *  Description:    Reads from the UART transmitting via DMA to memory
 *
 **********************************************************************************************************************/
ER_RET uart_dma_read (uint8_t chan_num, uint8_t* buf, size_t num_chars,
        uart_transfer_complete_callback_t rx_complete_callback)
{
    ER_RET ret_val = ER_OK;

#ifdef r_dma_rzn1_if_included

    volatile UART_f_Type *chan_base_addr;
    DMA_TRANS_CTRL dma_trans_ctrl = DMA_DEFAULT_TRANS_CTRL;

    if ((chan_num >= MIN_FULL_UART) && (FIT_NO_PTR != rx_complete_callback) && (8191 >= num_chars))
    {
        /* Parameters are ok */
        if ((void *) 0 == uart_channels_params[chan_num].base_address)
        {
            ret_val = ER_INVAL; /* UART channel not initialised */
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }

    if (ER_OK == ret_val)
    {
        uart_channels_params[chan_num].rx_completed_callback = rx_complete_callback;
        uart_channels_params[chan_num].rx_outstanding = 1;

        chan_base_addr = (volatile UART_f_Type *) uart_channels_params[chan_num].base_address;

        if (false == uart_dma[FULL_UART_INDEX(chan_num)].Rx.reserve_mode)
        {
            /* THE CURRENT MODE IS DMA RELEASE MODE */
            /* Allocate a DMA channel to the UART channel */
            if (ER_OK
                    == (ret_val = uart_assign_dma_chan( &uart_dma[FULL_UART_INDEX(chan_num)].Rx,
                            (void *) &uart_dmac_rx_callback)))
            {
                /* Set up DMA channel control */
                DMA_CHAN_CTRL dma_chan_ctrl = DMA_DEFAULT_CHAN_CTRL;
                dma_chan_ctrl.SRC_HS.TYPE = HARDWARE;
                dma_chan_ctrl.SRC_HS.HS_INTERFACE = uart_dma[FULL_UART_INDEX(chan_num)].Rx.HS_Interface;
                ret_val = R_DMA_Control(uart_dma[FULL_UART_INDEX(chan_num)].Rx.DMAC_number,
                        uart_dma[FULL_UART_INDEX(chan_num)].Rx.channel, DMA_CONTROL_SET_CHAN_CONFIG, &dma_chan_ctrl);
            }
        }

        /* Configure DMA */
        dma_trans_ctrl.INT_EN = true;
        dma_trans_ctrl.TR_FLOW = PTM_P;
        dma_trans_ctrl.SRC = (uint32_t) & (chan_base_addr->rUart_RBR_THR_DLL.RBR_THR);
        dma_trans_ctrl.DST = (uint32_t) buf;
        dma_trans_ctrl.SRC_INCR = NO_CHANGE;
        dma_trans_ctrl.SRC_BRST_LEN = DATA_ITEMS_8;
        dma_trans_ctrl.BLOCK_SIZE = num_chars;

        if (ER_OK == ret_val)
        {
            ret_val = R_DMA_Control(uart_dma[FULL_UART_INDEX(chan_num)].Rx.DMAC_number,
                    uart_dma[FULL_UART_INDEX(chan_num)].Rx.channel, DMA_CONTROL_SET_TRANS_CONFIG, &dma_trans_ctrl);
        }

        if (ER_OK == ret_val)
        {
            /* Configure UART DMA register */
            chan_base_addr->rUart_RDMACR.BIT.bUart_SRC_BURST_SIZE = 2; /* 4 bytes per burst */
            chan_base_addr->rUart_RDMACR.BIT.bUart_SRC_BLOCK_SIZE = num_chars;
            chan_base_addr->rUart_RDMACR.BIT.bUart_RDMAE = 1; /* Disabled via hardware after block transfer is complete */

            uart_chan_read_buff_params[chan_num].remaining_bytes = 0; /* Because it is a DMA transfer */

            /* Reset the Rx FIFO  */
            chan_base_addr->rUart_FCR_IIR.FCR.bUart_RFIFOR = 1;

            /* Enable the FIFO */
            chan_base_addr->rUart_FCR_IIR.FCR.bUart_FIFOE = 1;

            /* Rx FIFO trigger level */
            chan_base_addr->rUart_FCR_IIR.FCR.bUart_RCVR = 2; /* 1:generate DMA request when FIFO 1/4 full or more */

            /* Enable rx interrupt (To capture character time-out) */
            chan_base_addr->rUart_IER_DLH.IER.bUart_ERBFI = 0;

            if (ER_OK
                    != R_DMA_Write(uart_dma[FULL_UART_INDEX(chan_num)].Rx.DMAC_number,
                            uart_dma[FULL_UART_INDEX(chan_num)].Rx.channel, DMA_TRANSFER)) /* Enable the DMA channel */
            {
                ret_val = ER_SYS;
            }
        }
    }

#else /* Not ifdef r_dma_rzn1_if_included */
    /* No DMA driver therefore cannot perform DMA transfer */
    ret_val = ER_INVAL;
#endif

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_dma_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_dma_write
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  num_chars - number of characters to read
 *
 *  Description:    Writes from the memory via DMA to the uart
 **********************************************************************************************************************/
ER_RET uart_dma_write (uint8_t chan_num, const uint8_t* buf, size_t num_chars,
        uart_transfer_complete_callback_t tx_complete_callback)
{
    ER_RET ret_val = ER_OK;

#ifdef r_dma_rzn1_if_included

    volatile UART_f_Type *chan_base_addr;
    DMA_TRANS_CTRL dma_trans_ctrl = DMA_DEFAULT_TRANS_CTRL;

    if ((chan_num >= MIN_FULL_UART) && (FIT_NO_PTR != tx_complete_callback) && (8191 >= num_chars))
    {
        /* Parameters are ok */
        if ((void *) 0 == uart_channels_params[chan_num].base_address)
        {
            ret_val = ER_INVAL; /* UART channel not initialised */
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }

    if (ER_OK == ret_val)
    {
        uart_channels_params[chan_num].tx_completed_callback = tx_complete_callback;
        chan_base_addr = (volatile UART_f_Type *) uart_channels_params[chan_num].base_address;

        if (false == uart_dma[FULL_UART_INDEX(chan_num)].Tx.reserve_mode)
        {
            /* THE CURRENT MODE IS DMA RELEASE MODE */
            /* Allocate a DMA channel to the UART channel */
            if (ER_OK
                    == (ret_val = uart_assign_dma_chan( &uart_dma[FULL_UART_INDEX(chan_num)].Tx,
                            (void *) &uart_dmac_tx_callback)))
            {
                /* Set up DMA channel control */
                DMA_CHAN_CTRL dma_chan_ctrl = DMA_DEFAULT_CHAN_CTRL;
                dma_chan_ctrl.DST_HS.TYPE = HARDWARE;
                dma_chan_ctrl.DST_HS.HS_INTERFACE = uart_dma[FULL_UART_INDEX(chan_num)].Tx.HS_Interface;
                ret_val = R_DMA_Control(uart_dma[FULL_UART_INDEX(chan_num)].Tx.DMAC_number,
                        uart_dma[FULL_UART_INDEX(chan_num)].Tx.channel, DMA_CONTROL_SET_CHAN_CONFIG, &dma_chan_ctrl);
            }
        }

        /* Configure DMA */
        dma_trans_ctrl.INT_EN = true;
        dma_trans_ctrl.TR_FLOW = MTP_P;
        dma_trans_ctrl.SRC = (uint32_t) buf;
        dma_trans_ctrl.DST = (uint32_t) & (chan_base_addr->rUart_RBR_THR_DLL.RBR_THR);
        dma_trans_ctrl.DST_INCR = NO_CHANGE;
        dma_trans_ctrl.DST_BRST_LEN = DATA_ITEMS_4;
        dma_trans_ctrl.BLOCK_SIZE = num_chars;

        if (ER_OK == ret_val)
        {
            ret_val = R_DMA_Control(uart_dma[FULL_UART_INDEX(chan_num)].Tx.DMAC_number,
                    uart_dma[FULL_UART_INDEX(chan_num)].Tx.channel, DMA_CONTROL_SET_TRANS_CONFIG, &dma_trans_ctrl);
        }

        if (ER_OK == ret_val)
        {
            /* Configure UART DMA register */
            chan_base_addr->rUart_TDMACR.BIT.bUart_DEST_BURST_SIZE = 1; /* 4 bytes per burst */
            chan_base_addr->rUart_TDMACR.BIT.bUart_DEST_BLOCK_SIZE = num_chars;
            chan_base_addr->rUart_TDMACR.BIT.bUart_TDMAE = 1; /* Disabled via hardware after block transfer is complete */

            uart_chan_write_buff_params[chan_num].remaining_bytes = 0; /* Because it is a DMA transfer */
            uart_channels_params[chan_num].tx_outstanding = 1;

            /* Tx FIFO empty trigger level */
            chan_base_addr->rUart_FCR_IIR.FCR.bUart_TET = 3; /* 1:generate interrupt when FIFO 1/2 full. */

            /* Reset the Tx FIFO  */
            chan_base_addr->rUart_FCR_IIR.FCR.bUart_XFIFOR = 1;

            /* Enable the FIFO */
            chan_base_addr->rUart_FCR_IIR.FCR.bUart_FIFOE = 1;

            /* Enable programmable THRE for DMA requests */
            chan_base_addr->rUart_IER_DLH.IER.bUart_PTIME = 1;
            chan_base_addr->rUart_IER_DLH.IER.bUart_ETBEI = 0;

            if (ER_OK
                    != R_DMA_Write(uart_dma[FULL_UART_INDEX(chan_num)].Tx.DMAC_number,
                            uart_dma[FULL_UART_INDEX(chan_num)].Tx.channel, DMA_TRANSFER)) /* Enable the DMA channel */
            {
                ret_val = ER_SYS;
            }
        }
    }

#else /* Not ifdef r_dma_rzn1_if_included */
    /* No DMA driver therefore cannot perform DMA transfer */
    ret_val = ER_INVAL;
#endif

    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_dma_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_putchar
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *
 *  Description:    Writes a char to a UART channel
 *
 **********************************************************************************************************************/
static ER_RET uart_putchar (uint8_t chan_num, unsigned char c)
{
    ER_RET ret_val = ER_OK;
    volatile UART_r_Type *chan_base_addr = uart_channels_params[chan_num].base_address;
    uint32_t i;

    /* wait for transmit holding reg empty */
    for (i = 0; i < WAIT_TEMT; i++)
    {
        if (1 == chan_base_addr->rUart_LSR.BIT.bUart_TEMT)
        {
            break;
        }
    }
    if (WAIT_TEMT == i)
    {
        /* TIMED OUT */
        ret_val = ER_TIMEOUT;
    }
    else
    {
        chan_base_addr->rUart_RBR_THR_DLL.RBR_THR.bUart_RBR_THR = (uint32_t) c;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function uart_putchar
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_getchar
 *
 *  Return value:   char read
 *
 *  Parameters:     chan_num - UART channel number
 *
 *  Description:    Reads a char from a UART channel
 *
 **********************************************************************************************************************/
static unsigned char uart_getchar (uint8_t chan_num)
{
    unsigned char c;
    volatile UART_r_Type *chan_base_addr = uart_channels_params[chan_num].base_address;

    /*** Implement timeout so don't wait forever ***/
    while ( !(chan_base_addr->rUart_LSR.BIT.bUart_DR));

    c = (unsigned char) chan_base_addr->rUart_RBR_THR_DLL.LONG;
    return c;
}
/***********************************************************************************************************************
 End of function uart_getchar
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       handle_uart_interrupt
 *
 *  Return value:   none
 *
 *  Parameters:     irq_num_ptr - pointer to interrupt vector number
 *
 *  Description:    handle UART Interrupt for 'chan_num'
 *
 **********************************************************************************************************************/
static void handle_uart_interrupt (IRQn_Type *irq_num_ptr) // @suppress("Function definition ordering")
{
    int32_t int_id;
    volatile UART_r_Type *chan_base_addr;
    unsigned char c;
    uint32_t actual_total_bytes = 0;
    IRQn_Type irq_num = *irq_num_ptr;
    uint32_t chan_num = UART_INVALID_CHANNEL;

    if ((irq_num >= RZN1_IRQ_UART0) && (irq_num <= RZN1_IRQ_UART2))
    {
        chan_num = irq_num - RZN1_IRQ_UART0;
    }
    else if ((irq_num >= RZN1_IRQ_UART3) && (irq_num <= RZN1_IRQ_UART7))
    {
        chan_num = (irq_num - RZN1_IRQ_UART3) + 3;
    }
    else
    {
        /* Do nothing */
        ;
    }

    if (UART_INVALID_CHANNEL != chan_num)
    {
        chan_base_addr = uart_channels_params[chan_num].base_address;

        /* Check interrupt ID*/
        int_id = chan_base_addr->rUart_FCR_IIR.LONG & UART_INT_IID_MASK; /* IIR is same reg address as FCR (wr => FCR, rd => IIR) */

        switch (int_id)
        {
            case UART_IIR_THR_EMPTY:
                if (0 == uart_chan_write_buff_params[chan_num].remaining_bytes)
                {
                    /* disable tx interrupt */
                    chan_base_addr->rUart_IER_DLH.IER.bUart_PTIME = 0;
                    chan_base_addr->rUart_IER_DLH.IER.bUart_ETBEI = 0;

                    /* disable fifo */
                    //chan_base_addr->rUart_FCR_IIR.FCR.bUart_FIFOE = 0;
                    uart_channels_params[chan_num].tx_outstanding = 0;
                    uart_chan_write_buff_params[chan_num].next_byte_ptr = (uint8_t *) 0;
                    actual_total_bytes = uart_chan_write_buff_params[chan_num].required_bytes;
                    uart_chan_write_buff_params[chan_num].required_bytes = 0;

                    /* inform UART driver interface that UART channel is no longer busy */
                    tx_transfer_completed(chan_num);

                    /* inform application that transfer has completed */
                    (uart_channels_params[chan_num].tx_completed_callback)(chan_num, actual_total_bytes);

                    /* Set tx_completed_callback back to NULL before next tx transaction */
                    uart_channels_params[chan_num].tx_completed_callback = (void *) 0;
                }
                else
                {
                    /* Continue writing data if there is more to send by filling the Tx FIFO */
                    while ((1 == chan_base_addr->rUart_USR.BIT.bUart_TFNF)
                            && (uart_chan_write_buff_params[chan_num].remaining_bytes > 0))
                    {
                        chan_base_addr->rUart_RBR_THR_DLL.RBR_THR.bUart_RBR_THR =
                                *(uart_chan_write_buff_params[chan_num].next_byte_ptr);
                        uart_chan_write_buff_params[chan_num].next_byte_ptr++;
                        uart_chan_write_buff_params[chan_num].remaining_bytes--;
                    }
                }
            break;

            case UART_IIR_CHAR_TIMEOUT:
            case UART_IIR_RX_DATA_AVAIL:

                /* Continue reading data from Rx FIFO if more is expected */
                while ((1 == chan_base_addr->rUart_LSR.BIT.bUart_DR)
                        && (uart_chan_read_buff_params[chan_num].remaining_bytes > 0))
                {
                    c = (unsigned char) chan_base_addr->rUart_RBR_THR_DLL.LONG;
                    *(uart_chan_read_buff_params[chan_num].next_byte_ptr) = c;

                    actual_total_bytes = uart_chan_read_buff_params[chan_num].required_bytes; /* still trying to read max number of bytes */
                    uart_chan_read_buff_params[chan_num].next_byte_ptr++;
                    uart_chan_read_buff_params[chan_num].remaining_bytes--;
                }
                if (0 == uart_chan_read_buff_params[chan_num].remaining_bytes)
                {
                    /* All required data has been received. Disable rx interrupt */
                    chan_base_addr->rUart_IER_DLH.IER.bUart_ERBFI = 0;

                    uart_channels_params[chan_num].rx_outstanding = 0;
                    uart_chan_read_buff_params[chan_num].next_byte_ptr = (uint8_t *) 0;
                    uart_chan_read_buff_params[chan_num].required_bytes = 0;

                    /* inform UART driver interface that UART channel is no longer busy */
                    rx_transfer_completed(chan_num);

                    /* inform application that transfer has completed */
                    if (0 != uart_channels_params[chan_num].rx_completed_callback)
                    {
                        (uart_channels_params[chan_num].rx_completed_callback)(chan_num, actual_total_bytes);
                    }

                    /* Set rx_completed_callback back to NULL before next rx transaction */
                    uart_channels_params[chan_num].rx_completed_callback = (void *) 0;
                }
            break;

            case UART_IIR_MODEM_STATUS:
            case UART_IIR_NO_INT:
            case UART_IIR_RX_TIMEOUT:
            case UART_IIR_RX_LINE_STATUS:
            case UART_IIR_BUSY_DETECT:
            default:
            break;

        }
    }
}
/***********************************************************************************************************************
 End of function handle_uart_interrupt
 **********************************************************************************************************************/

#ifdef r_dma_rzn1_if_included
/***********************************************************************************************************************
 *
 *  Function:       uart_dmac_tx_callback
 *
 *  Return value:   None.
 *
 *  Parameters:     DMAC_number - The DMA Controller number
 *                  channel - Channel number of the DMAC
 *
 *  Description:    Call back funtion for DMA TX interrupts.
 *
 **********************************************************************************************************************/
static void uart_dmac_tx_callback (uint8_t DMAC_number, uint8_t dma_channel)
{
    volatile UART_f_Type *chan_base_addr;
    uint8_t uart_chan;

    if (DMAC_1 == DMAC_number)
    {
        for (uart_chan = MIN_FULL_UART; uart_chan < UART_CHAN_8; uart_chan++)
        {
            /* Determine the UART channel number */
            if ((dma_channel == uart_dma[FULL_UART_INDEX(uart_chan)].Rx.channel)
                    || (dma_channel == uart_dma[FULL_UART_INDEX(uart_chan)].Tx.channel))
            {
                break;
            }
        }
    }
    else
    {
        uart_chan = UART_CHAN_8;
    }

    chan_base_addr = (UART_f_Type *) uart_channels_params[uart_chan].base_address;

    if (uart_channels_params[uart_chan].tx_outstanding)
    {
        /* All required data may not have been sent. Enable tx FIFO empty interrupt */
        chan_base_addr->rUart_IER_DLH.IER.bUart_ETBEI = 1;

        /* Disable UART-DMA - Although should have already been disabled via hardware*/
        chan_base_addr->rUart_TDMACR.BIT.bUart_TDMAE = 0;

        if (false == uart_dma[FULL_UART_INDEX(uart_chan)].Tx.reserve_mode)
        {
            /* THE CURRENT MODE IS DMA RELEASE MODE */
            /* Close DMA Channel */
            R_DMA_Close(DMAC_number, dma_channel);
            uart_dma[FULL_UART_INDEX(uart_chan)].Tx.channel = INVAL_DMA_CHAN;
        }
    }
}
/***********************************************************************************************************************
 End of function uart_dmac_tx_callback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       uart_dmac_rx_callback
 *
 *  Return value:   None.
 *
 *  Parameters:     DMAC_number - The DMA Controller number
 *                  channel - Channel number of the DMAC
 *
 *  Description:    Call back funtion for DMA RX interrupts.
 *
 **********************************************************************************************************************/
static void uart_dmac_rx_callback (uint8_t DMAC_number, uint8_t dma_channel)
{
    volatile UART_f_Type *chan_base_addr;
    uint8_t uart_chan;

    if (DMAC_1 == DMAC_number)
    {
        for (uart_chan = MIN_FULL_UART; uart_chan < UART_CHAN_8; uart_chan++)
        {
            /* Determine the UART channel number */
            if ((dma_channel == uart_dma[FULL_UART_INDEX(uart_chan)].Rx.channel)
                    || (dma_channel == uart_dma[FULL_UART_INDEX(uart_chan)].Tx.channel))
            {
                break;
            }
        }
    }
    else
    {
        uart_chan = UART_CHAN_8;
    }

    chan_base_addr = (UART_f_Type *) uart_channels_params[uart_chan].base_address;

    if (uart_channels_params[uart_chan].rx_outstanding)
    {
        if (false == uart_dma[FULL_UART_INDEX(uart_chan)].Rx.reserve_mode)
        {
            /* THE CURRENT MODE IS DMA RELEASE MODE */
            /* Close DMA Channel */
            R_DMA_Close(DMAC_number, dma_channel);
            uart_dma[FULL_UART_INDEX(uart_chan)].Rx.channel = INVAL_DMA_CHAN;
        }

        /* Clear the FIFO and stop the transfer */
        /* disable fifo */
        //chan_base_addr->rUart_FCR_IIR.FCR.bUart_FIFOE = 0;
        /* inform UART driver interface that UART channel is no longer busy */
        rx_transfer_completed(uart_chan);

        uart_channels_params[uart_chan].rx_outstanding = 0;

        /* All required data has been received. Disable rx interrupt */
        chan_base_addr->rUart_IER_DLH.IER.bUart_ERBFI = 0;

        /* Disable UART-DMA - Although should have already been disabled via hardware*/
        chan_base_addr->rUart_RDMACR.BIT.bUart_RDMAE = 0;

        /* inform application that transfer has completed */
        if (0 != uart_channels_params[uart_chan].rx_completed_callback)
        {
            (uart_channels_params[uart_chan].rx_completed_callback)(uart_chan, 0);
        }
    }

}
/***********************************************************************************************************************
 End of function uart_dmac_rx_callback
 **********************************************************************************************************************/
#endif /* r_dma_rzn1_if_included */
