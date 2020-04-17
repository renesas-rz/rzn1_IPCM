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
 * FILE         :  r_uart_rzn1_if.c
 * Description  :  UART driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
/*
 ********************************************************************************
 * Doxygen Summary block
 **********************************************************************************************************************/
/*!
 * @ingroup UART_MODULE RZN1 UART Bare Metal Driver
 * @{
 * @file
 * @brief UART Bare Metal Driver
 * @details Supports configuring, reading and writing UART port
 * @} */
/***********************************************************************************************************************
 * End of Doxygen Summary block
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "r_uart_rzn1_if.h"
#include "r_uart_rzn1_config.h"
#include "r_uart_rzn1.h"

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static UART_IF_CHANNEL_STATE_E uart_channels_state[MAX_UART_CHANNELS];

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
extern const UART_CHANNEL_CONFIG_T default_uart_chan_config =
{ .parity = UART_PARITY_NONE,
  .flow_control = UART_FLOW_CONTROL_NONE,
  .stopbits = NO_OF_STOP_BITS_1,
  .databits = DATA_BITS_PER_CHAR_8,
  .baudrate = 115200
};

/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_UART_GetVersion
 *
 *  Return value:   None.
 *
 *  Parameters:     buf - Pointer to buffer for version information
 *
 *  Description:    Returns the UART driver version number
 *
 **********************************************************************************************************************/
void R_UART_GetVersion (void *buf)
{
    ((uint8_t *) buf)[1] = uart_get_major_version_num(); /* Get the driver major version number */
    ((uint8_t *) buf)[0] = uart_get_minor_version_num(); /* Get the driver minor version number */
}
/***********************************************************************************************************************
 End of function R_UART_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_UART_Init
 *
 *  Return value:   error status
 *
 *  Parameters:     None
 *  Description:    Initialise UART driver and channels interface state
 *                  Implements : RZN1_BMD_r0111
 *
 **********************************************************************************************************************/
ER_RET R_UART_Init (void)
{
    ER_RET ret_val = ER_OK;
    uint32_t channel;

    for (channel = 0; channel < MAX_UART_CHANNELS; channel++)
    {
        uart_channels_state[channel] = UART_CHANNEL_STATE_CLOSED;
    }

    /* Initialise the UART driver */
    ret_val = uart_driver_init();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_UART_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_UART_Open
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number to open
 *
 *  Description:    Opens a UART channel
 *
 **********************************************************************************************************************/
ER_RET R_UART_Open (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

#if UART_CFG_PARAM_CHECKING_ENABLE
    if (chan_num >= MAX_UART_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        if (UART_CHANNEL_STATE_CLOSED != uart_channels_state[chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = uart_channel_open(chan_num);
            if (ER_OK == ret_val)
            {
                uart_channels_state[chan_num] = UART_CHANNEL_STATE_OPEN;
            }
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_UART_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_UART_Control
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number to control
 *                  control_request - request to configure channel or get channel info.
 *                  buf - configuration data (to set or get).
 *
 *                  NOTE: API function checks that buf is non-zero.
 *                  The upper layer should check that the buffer lies within a valid address range.
 *
 *  Description:    Configure channel parameters, set transfer parameters or
 *                  get channel or transfer info, depending on control_request
 *
 **********************************************************************************************************************/
ER_RET R_UART_Control (uint8_t chan_num, UART_CONTROL_REQUEST_E control_request, uint8_t *buf)
{
    ER_RET ret_val = ER_OK;

#if UART_CFG_PARAM_CHECKING_ENABLE
    if (chan_num >= MAX_UART_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* For all control requests except UART_CONTROL_RESET & UART_CONTROL_TRANSFER_CANCEL need a valid buf pointer */
        if ((UART_CONTROL_RESET != control_request) && (UART_CONTROL_TRANSFER_CANCEL != control_request))
        {
            if (FIT_NO_PTR == buf)
            {
                ret_val = ER_PARAM;
            }
        }
    }

    if (ER_OK == ret_val)
#endif
    {
        if ((UART_CHANNEL_STATE_CLOSED == uart_channels_state[chan_num])
            && ((control_request != UART_CONTROL_GET_CHAN_STATE) && (control_request != UART_CONTROL_RESET)))
        {
            ret_val = ER_INVAL;
        }
        else
        {
            /* UART driver state & parameters are valid */
            switch (control_request)
            {
                case UART_CONTROL_SET_CHAN_CONFIG:
                    /* Set channel configuration parity, flow_control, stopbits, databits, baudrate */
                    ret_val = uart_set_chan_config(chan_num, *(UART_CHANNEL_CONFIG_T *) buf);
                break;

                case UART_CONTROL_GET_CHAN_CONFIG:
                    ret_val = uart_get_chan_config(chan_num, (UART_CHANNEL_CONFIG_T *) buf);
                break;

                case UART_CONTROL_GET_CHAN_STATE:
                    /* Get channel state (see UART_IF_CHANNEL_STATE_E) */
                    buf[0] = uart_channels_state[chan_num];
                break;

                case UART_CONTROL_RESERVE_DMA_CHAN_RX:
                    ret_val = uart_allocate_dma_rx_chan(chan_num, (uint8_t) * buf);
                break;

                case UART_CONTROL_RESERVE_DMA_CHAN_TX:
                    ret_val = uart_allocate_dma_tx_chan(chan_num, (uint8_t) * buf);
                break;

                case UART_CONTROL_RELEASE_DMA_CHAN_RX:
                    uart_release_dma_rx_chan(chan_num);
                break;

                case UART_CONTROL_RELEASE_DMA_CHAN_TX:
                    uart_release_dma_tx_chan(chan_num);
                break;

                case UART_CONTROL_TRANSFER_CANCEL:
                    /* Cancel current transfer */
                    if (UART_CHANNEL_STATE_BUSY == uart_channels_state[chan_num])
                    {
                        ret_val = uart_transfer_cancel(chan_num);
                    }
                    else
                    {
                        ret_val = ER_INVAL;
                    }
                break;

                case UART_CONTROL_RESET:
                    /* Reset the UART channel */
                    ret_val = uart_reset(chan_num);
                break;

                default:
                    ret_val = ER_PARAM;
                break;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_UART_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_UART_Read
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  buf  - where data received is stored
 *                  num_chars_ptr -
 *                     INPUT num chars to read, OUTPUT: num chars read successfully
 *                  mode - BLOCKING or NON-BLOCKING read
 *                  rx_complete_callback - function to call when all data has been read
 *                                         (for NON_BLOCKING read).
 *
 *                  NOTE 1: rx_complete_callback may be null e.g. if BLOCKING mode or
 *                  if previously set by call to R_UART_Control().
 *                  NOTE 2: API function checks that buf is non-zero.
 *                  The upper layer should check that the buffer lies within a valid address range.
 *                  NOTE 3: If NON-BLOCKING (asynchronous) mode then 'buf' should not be accessed
 *                  by the calling application until notified that the transfer has completed.
 *
 *  Description:    Reads data from a UART channel.
 *                  If BLOCKING (synchronous) mode then returns when all the requested data
 *                      has been read or a timeout occurs.
 *                  If NON-BLOCKING (asynchronous) mode then initiates the read process and returns.
 *                  In this case a callback parameter is required to be passed, either in this
 *                  function call or a previous call to R_UART_Control().
 *
 **********************************************************************************************************************/
ER_RET R_UART_Read (uint8_t chan_num, uint8_t *buf, size_t *num_chars_ptr, UART_TRANSFER_MODE_E mode,
        uart_transfer_complete_callback_t rx_complete_callback)
{
    ER_RET ret_val = ER_OK;

#if UART_CFG_PARAM_CHECKING_ENABLE
    if ((chan_num >= MAX_UART_CHANNELS) || (FIT_NO_PTR == buf) || (FIT_NO_PTR == num_chars_ptr) || (0 == ( *num_chars_ptr)))
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        /* parameters are valid */
        if (UART_CHANNEL_STATE_OPEN != uart_channels_state[chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            uart_channels_state[chan_num] = UART_CHANNEL_STATE_BUSY;
            switch (mode)
            {
                case UART_TRANSFER_MODE_BLOCKING:
                    ret_val = uart_sync_read(chan_num, buf, *num_chars_ptr, num_chars_ptr);

                    uart_channels_state[chan_num] = UART_CHANNEL_STATE_OPEN;
                break;
                case UART_TRANSFER_MODE_NON_BLOCKING:

                    /* Non-blocking mode */
                    ret_val = uart_async_read(chan_num, buf, *num_chars_ptr, rx_complete_callback);
                break;
                case UART_TRANSFER_MODE_DMA:
                    ret_val = uart_dma_read(chan_num, buf, *num_chars_ptr, rx_complete_callback);
                break;
                default:
                    ret_val = ER_PARAM;
            }

            /* If transfer not initiated */
            if (ER_OK != ret_val)
            {
                uart_channels_state[chan_num] = UART_CHANNEL_STATE_OPEN;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_UART_Read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_UART_Write
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number
 *                  buf  - data to be written
 *                  num_chars_ptr -
 *                     INPUT num chars to write, OUTPUT: num chars written successfully
 *                  mode - BLOCKING or NON-BLOCKING read
 *                  tx_complete_callback - function to call when all data has been read
 *                                         (for NON_BLOCKING read).
 *
 *                  NOTE 1: tx_complete_callback may be null e.g. if BLOCKING mode or
 *                  if previously set by call to R_UART_Control().
 *                  NOTE 2: API function checks that buf is non-zero.
 *                  The upper layer should check that the buffer lies within a valid address range.
 *                  NOTE 3: If NON-BLOCKING (asynchronous) mode then 'buf' should not be accessed
 *                  by the calling application until notified that the transfer has completed.
 *
 *  Description:    Writes data to a UART channel.
 *                  If BLOCKING (synchronous) mode then returns when all the requested data
 *                      has been written or a timeout occurs.
 *                  If NON-BLOCKING (asynchronous) mode then initiates the write process and returns.
 *                  In this case a callback parameter is required to be passed, either in this
 *                  function call or a previous call to R_UART_Control().
 *
 **********************************************************************************************************************/
ER_RET R_UART_Write (uint8_t chan_num, const uint8_t *buf, size_t *num_chars_ptr, UART_TRANSFER_MODE_E mode,
        uart_transfer_complete_callback_t tx_complete_callback)
{
    ER_RET ret_val = ER_OK;

#if UART_CFG_PARAM_CHECKING_ENABLE
    if ((chan_num >= MAX_UART_CHANNELS) || (FIT_NO_PTR == buf) || (FIT_NO_PTR == num_chars_ptr) || (0 == ( *num_chars_ptr)))
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        /* parameters are valid */
        if (UART_CHANNEL_STATE_CLOSED == uart_channels_state[chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            uart_channels_state[chan_num] = UART_CHANNEL_STATE_BUSY;
            switch (mode)
            {
                case UART_TRANSFER_MODE_BLOCKING:
                    ret_val = uart_sync_write(chan_num, buf, *num_chars_ptr, num_chars_ptr);
                    uart_channels_state[chan_num] = UART_CHANNEL_STATE_OPEN;
                break;

                case UART_TRANSFER_MODE_NON_BLOCKING:
                    /* Non-blocking mode */
                    ret_val = uart_async_write(chan_num, buf, *num_chars_ptr, tx_complete_callback);
                break;

                case UART_TRANSFER_MODE_DMA:
                    ret_val = uart_dma_write(chan_num, buf, *num_chars_ptr, tx_complete_callback);
                break;

                default:
                    ret_val = ER_PARAM;
            }

            /* If transfer not initiated */
            if (ER_OK != ret_val)
            {
                uart_channels_state[chan_num] = UART_CHANNEL_STATE_OPEN;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_UART_Write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_UART_Close
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - UART channel number to close
 *
 *  Description:    closes a UART channel
 *
 **********************************************************************************************************************/
ER_RET R_UART_Close (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

#if UART_CFG_PARAM_CHECKING_ENABLE
    if (chan_num >= MAX_UART_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        if (UART_CHANNEL_STATE_OPEN != uart_channels_state[chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = uart_channel_close(chan_num);
            if (ER_OK == ret_val)
            {
                uart_channels_state[chan_num] = UART_CHANNEL_STATE_CLOSED;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_UART_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       tx_transfer_completed
 *
 *  Return value:   void
 *
 *  Parameters:     chan_num - UART channel number for which tx transfer has completed
 *
 *  Description:    NON-interface function so parameters not required to be checked.
 *                  Called when a non-blocking tx transfer has completed so
 *                  UART channel state can be updated.
 *
 **********************************************************************************************************************/

void tx_transfer_completed (uint8_t chan_num)
{
    if (UART_CHANNEL_STATE_BUSY == uart_channels_state[chan_num])
    {
        uart_channels_state[chan_num] = UART_CHANNEL_STATE_OPEN;
    }
}
/***********************************************************************************************************************
 End of function tx_transfer_completed
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       rx_transfer_completed
 *
 *  Return value:   void
 *
 *  Parameters:     chan_num - UART channel number for which rx transfer has completed
 *
 *  Description:    NON-interface function so parameters not required to be checked.
 *                  Called when a non-blocking tx transfer has completed so
 *                  UART channel state can be updated.
 *
 **********************************************************************************************************************/
void rx_transfer_completed (uint8_t chan_num)
{
    if (UART_CHANNEL_STATE_BUSY == uart_channels_state[chan_num])
    {
        uart_channels_state[chan_num] = UART_CHANNEL_STATE_OPEN;
    }
}
/***********************************************************************************************************************
 End of function rx_transfer_completed
 **********************************************************************************************************************/
