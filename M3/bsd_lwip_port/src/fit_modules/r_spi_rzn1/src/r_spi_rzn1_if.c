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
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_spi_rzn1_if.c
 * Description  :  SPI driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "r_spi_rzn1_if.h"
#include "r_spi_rzn1_config.h"
#include "r_spi_rzn1.h"

#define MAX_DMA_FRAMES  (8191)

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static spi_channel_state_t spi_channel_states[MAX_SPI_CHANNELS];

/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/
static ER_RET spi_tx_param_check (spi_transfer_data_t transfer_data);
static ER_RET spi_rx_param_check (spi_transfer_data_t transfer_data);

/***********************************************************************************************************************
 External variables
 **********************************************************************************************************************/
extern const spi_channel_config_t default_spi_chan_config =
{ .data_frame_size = 8, .frame_format = spi_texas_instruments, .master_config.baudrate = 8000000,
        .master_config.slave_select = 0, .microwire_config.control_frame_size = 8 };

/***********************************************************************************************************************
 *
 *  Function:       R_SPI_GetVersion
 *
 *  Return value:   Driver number
 *
 *  Parameters:     None
 *  Description:    Returns the SPI driver version number
 *
 **********************************************************************************************************************/
void R_SPI_GetVersion (void *buf)
{
    ((uint8_t *) buf)[1] = (uint8_t)SPI_DRIVER_MAJOR_VERSION_NUMBER;
    ((uint8_t *) buf)[0] = (uint8_t)SPI_DRIVER_MINOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function R_SPI_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_SPI_Init
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *  Description:    Initialise SPI driver and channels interface state
 *
 **********************************************************************************************************************/
ER_RET R_SPI_Init (void)
{
    ER_RET ret_val = ER_OK;
    uint8_t channel;

    for (channel = 0; channel < MAX_SPI_CHANNELS; channel++)
    {
        spi_channel_states[channel] = SPI_CHANNEL_STATE_CLOSED;
    }

    /* Initialise the SPI driver */
    ret_val = spi_init();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SPI_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_SPI_Uninit
 *
 *  Return value:   void
 *
 *  Parameters:     None
 *  Description:    Un-initialise SPI driver and channels interface state
 *
 **********************************************************************************************************************/
void R_SPI_Uninit (void)
{
    uint8_t channel;

    for (channel = 0; channel < MAX_SPI_CHANNELS; channel++)
    {
        spi_channel_states[channel] = SPI_CHANNEL_STATE_CLOSED;
    }

    /* Uninitialise the SPI driver */
    spi_uninit();

    return;
}
/***********************************************************************************************************************
 End of function R_SPI_Uninit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_SPI_Open
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - SPI channel number to open
 *
 *  Description:    Opens an SPI channel
 *
 **********************************************************************************************************************/
ER_RET R_SPI_Open (uint8_t chan_num, bool control)
{
    ER_RET ret_val = ER_OK;

    if (chan_num >= MAX_SPI_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        if ((control && (chan_num < MIN_SPI_SLAVE)) || (( !control) && (chan_num >= MIN_SPI_SLAVE)))
            if (SPI_CHANNEL_STATE_CLOSED != spi_channel_states[chan_num])
            {
                ret_val = ER_INVAL;
            }
            else
            {
                /* Attempt to open the channel */
                if (ER_OK == (ret_val = spi_channelopen(chan_num)))
                {
                    spi_channel_states[chan_num] = SPI_CHANNEL_STATE_OPEN;
                }
            }
        else
        {
            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SPI_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_SPI_Control
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - SPI channel number to control
 *                  control_request - request to configure channel or get channel info.
 *                  spi_ctrl - configuration data (to set or get).
 *
 *                  NOTE: API function checks that spi_ctrl is non-zero.
 *                  The upper layer should check that the buffer lies within a valid address range.
 *
 *  Description:    Configure channel parameters, set transfer parameters or
 *                  get channel or transfer info, depending on control_request
 *
 **********************************************************************************************************************/
ER_RET R_SPI_Control (uint8_t chan_num, spi_cmd_t control_request, void *spi_ctrl)
{
    ER_RET ret_val = ER_OK;

    if ((chan_num >= MAX_SPI_CHANNELS) || (0 == spi_ctrl))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        switch (control_request)
        {
            case SPI_CONTROL_SET_CALL_BACK:
                if (SPI_CHANNEL_STATE_CLOSED == spi_channel_states[chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else if (SPI_CHANNEL_STATE_BUSY == spi_channel_states[chan_num])
                {
                    ret_val = ER_BUSY;
                }
                else
                {
                    ret_val = spi_registercallback(chan_num, (spi_transfer_complete_callback_t) spi_ctrl);
                }
            break;
            case SPI_CONTROL_SET_CHAN_CONFIG:
                if (SPI_CHANNEL_STATE_CLOSED == spi_channel_states[chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else if (SPI_CHANNEL_STATE_BUSY == spi_channel_states[chan_num])
                {
                    ret_val = ER_BUSY;
                }
                else
                {
                    ret_val = spi_setchanconfig(chan_num, *((spi_channel_config_t *) spi_ctrl));
                }
            break;
            case SPI_CONTROL_GET_CHAN_CONFIG:
                if (SPI_CHANNEL_STATE_CLOSED == spi_channel_states[chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else
                {
                    spi_getchanconfig(chan_num, (spi_channel_config_t *) spi_ctrl);
                }
            break;
            case SPI_CONTROL_RESERVE_DMA_CHAN_RX:
                if (SPI_CHANNEL_STATE_CLOSED == spi_channel_states[chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else if (SPI_CHANNEL_STATE_BUSY == spi_channel_states[chan_num])
                {
                    ret_val = ER_BUSY;
                }
                else
                {
                    ret_val = spi_allocate_dma_rx_chan(chan_num, *(uint8_t *) spi_ctrl);
                }
            break;
            case SPI_CONTROL_RESERVE_DMA_CHAN_TX:
                if (SPI_CHANNEL_STATE_CLOSED == spi_channel_states[chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else if (SPI_CHANNEL_STATE_BUSY == spi_channel_states[chan_num])
                {
                    ret_val = ER_BUSY;
                }
                else
                {
                    ret_val = spi_allocate_dma_tx_chan(chan_num, *(uint8_t *) spi_ctrl);
                    ;
                }
            break;
            case SPI_CONTROL_RELEASE_DMA_CHAN_RX:
                if (SPI_CHANNEL_STATE_CLOSED == spi_channel_states[chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else if (SPI_CHANNEL_STATE_BUSY == spi_channel_states[chan_num])
                {
                    ret_val = ER_BUSY;
                }
                else
                {
                    spi_release_dma_rx_chan(chan_num);
                }
            break;
            case SPI_CONTROL_RELEASE_DMA_CHAN_TX:
                if (SPI_CHANNEL_STATE_CLOSED == spi_channel_states[chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else if (SPI_CHANNEL_STATE_BUSY == spi_channel_states[chan_num])
                {
                    ret_val = ER_BUSY;
                }
                else
                {
                    spi_release_dma_tx_chan(chan_num);
                }
            break;
            case SPI_CONTROL_GET_CHAN_STATE:
                *((spi_channel_state_t *) spi_ctrl) = spi_channel_states[chan_num];
            break;
            case SPI_CONTROL_CANCEL_TRANSFER:
                if (SPI_CHANNEL_STATE_CLOSED == spi_channel_states[chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else
                {
                    spi_transfer_cancel(chan_num);
                }
            break;
            default:
                ret_val = ER_PARAM;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SPI_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_tx_param_check
 *
 *  Return value:   Error status
 *
 *  Parameters:     transfer_data - Transfer data for requested transer
 *
 *  Description:    Checks parameters for an SPI Tx transfer are valid
 *
 **********************************************************************************************************************/
static ER_RET spi_tx_param_check (spi_transfer_data_t transfer_data)
{
    ER_RET ret_val = ER_OK;

    switch (transfer_data.transfer_mode_tx)
    {
        case SPI_TRANSFER_MODE_DMA:
            if (MAX_DMA_FRAMES < transfer_data.data_frames)
            {
                ret_val = ER_PARAM;
            }                              // @suppress("No break at end of case")
        case SPI_TRANSFER_MODE_BLOCKING:
        case SPI_TRANSFER_MODE_NON_BLOCKING:
            if (0 == transfer_data.write_buf)
            {
                ret_val = ER_PARAM;
            }
        break;
        default:
            ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_tx_param_check
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_rx_param_check
 *
 *  Return value:   Error status
 *
 *  Parameters:     transfer_data - Transfer data for requested transer
 *
 *  Description:    Checks parameters for an SPI Rx transfer are valid
 *
 **********************************************************************************************************************/
static ER_RET spi_rx_param_check (spi_transfer_data_t transfer_data)
{
    ER_RET ret_val = ER_OK;

    switch (transfer_data.transfer_mode_rx)
    {
        case SPI_TRANSFER_MODE_DMA:
            if (MAX_DMA_FRAMES < transfer_data.data_frames)
            {
                ret_val = ER_PARAM;
            }                             // @suppress("No break at end of case")
        case SPI_TRANSFER_MODE_BLOCKING:
        case SPI_TRANSFER_MODE_NON_BLOCKING:
            if (0 == transfer_data.read_buf)
            {
                ret_val = ER_PARAM;
            }
        break;
        default:
            ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function spi_rx_param_check
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_SPI_Read
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - SPI channel number
 *                  transfer_data:
 *                      read_buf  - Where data received is stored
 *                      write_buf  - Data to be written
 *                      data_frames - Number of data frames to read/write
 *                      transfer_mode_rx - The transfer mode of the read
 *                      transfer_mode_tx - The transfer mode of the write
 *                      transfer_type - The type of transfer being requested
 *
 *  Description:    Only reads data from an SPI channel. Do not work for full duplex mode.
 *                  If BLOCKING (synchronous) mode then returns when all the requested data
 *                      has been transfered or a timeout occurs.
 *                  If NON-BLOCKING/DMA (asynchronous) mode then initiates the transfer process and returns.
 *                      In this case a callback parameter is required to be passed through a previous call to R_SPI_Control().
 *
 **********************************************************************************************************************/
ER_RET R_SPI_Read (uint8_t chan_num, spi_transfer_data_t transfer_data)
{
    ER_RET ret_val = ER_OK;

    /* Parameter check */
    if ((chan_num >= MAX_SPI_CHANNELS) || (SPI_TRANSFER_TYPE_RX != transfer_data.transfer_type))
    {
        if ((SPI_TRANSFER_TYPE_TX_RX == transfer_data.transfer_type)
                || (SPI_TRANSFER_TYPE_TX == transfer_data.transfer_type))
        {
            ret_val = ((ER_RET) (7 * ((ER_RET) -1)));
        }
        else
        {
            ret_val = ER_PARAM;
        }
    }
    else
    {
        ret_val = spi_rx_param_check(transfer_data);
    }

    if (ER_OK == ret_val)
    {
        if (SPI_CHANNEL_STATE_CLOSED == spi_channel_states[chan_num])
        {
            ret_val = ER_INVAL;
        }
        else if (SPI_CHANNEL_STATE_BUSY == spi_channel_states[chan_num])
        {
            ret_val = ER_BUSY;
        }
        else if (ER_OK == (ret_val = spi_read(chan_num, transfer_data)))
        {
            if (spi_istransferring(chan_num))
            {
                /* Not a blocking transfer */
                spi_channel_states[chan_num] = SPI_CHANNEL_STATE_BUSY;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SPI_Read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_SPI_Write
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - SPI channel number
 *                  transfer_data:
 *                      read_buf  - Where data received is stored
 *                      write_buf  - Data to be written
 *                      data_frames - Number of data frames to read/write
 *                      transfer_mode_rx - The transfer mode of the read
 *                      transfer_mode_tx - The transfer mode of the write
 *                      transfer_type - The type of transfer being requested
 *
 *  Description:    Only writes data to an SPI channel. Do not work for full duplex mode.
 *                  If BLOCKING (synchronous) mode then returns when all the requested data
 *                      has been transfered or a timeout occurs.
 *                  If NON-BLOCKING/DMA (asynchronous) mode then initiates the transfer process and returns.
 *                      In this case a callback parameter is required to be passed through a previous call to R_SPI_Control().
 *
 **********************************************************************************************************************/

ER_RET R_SPI_Write (uint8_t chan_num, spi_transfer_data_t transfer_data)
{
    ER_RET ret_val = ER_OK;

    /* Parameter check */
    if ((chan_num >= MAX_SPI_CHANNELS) || (SPI_TRANSFER_TYPE_TX != transfer_data.transfer_type))
    {
        if ((SPI_TRANSFER_TYPE_TX_RX == transfer_data.transfer_type)
                || (SPI_TRANSFER_TYPE_RX == transfer_data.transfer_type))
            ret_val = ER_INVAL;
        else
            ret_val = ER_PARAM;
    }
    else
    {
        ret_val = spi_rx_param_check(transfer_data);

    }

    if (ER_OK == ret_val)
    {
        if (SPI_CHANNEL_STATE_CLOSED == spi_channel_states[chan_num])
        {
            ret_val = ER_INVAL;
        }
        else if (SPI_CHANNEL_STATE_BUSY == spi_channel_states[chan_num])
        {
            ret_val = ER_BUSY;
        }
        else if (ER_OK == (ret_val = spi_write(chan_num, transfer_data)))
        {
            if (spi_istransferring(chan_num))
            {
                /* Not a blocking transfer */
                spi_channel_states[chan_num] = SPI_CHANNEL_STATE_BUSY;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SPI_Write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_SPI_ReadWrite
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - SPI channel number
 *                  transfer_data:
 *                      read_buf  - Where data received is stored
 *                      write_buf  - Data to be written
 *                      data_frames - Number of data frames to read/write
 *                      transfer_mode_rx - The transfer mode of the read
 *                      transfer_mode_tx - The transfer mode of the write
 *                      transfer_type - The type of transfer being requested
 *
 *  Description:    Writes/reads data to/from an SPI channel. Only work for full duplex mode.
 *                  If BLOCKING (synchronous) mode then returns when all the requested data
 *                      has been transfered or a timeout occurs.
 *                  If NON-BLOCKING/DMA (asynchronous) mode then initiates the transfer process and returns.
 *                      In this case a callback parameter is required to be passed through a previous call to R_SPI_Control().
 *
 **********************************************************************************************************************/

ER_RET R_SPI_ReadWrite (uint8_t chan_num, spi_transfer_data_t transfer_data)
{
    ER_RET ret_val = ER_OK;

    /* Parameter check */
    if ((chan_num >= MAX_SPI_CHANNELS) || (SPI_TRANSFER_TYPE_TX_RX != transfer_data.transfer_type))
    {
        if ((SPI_TRANSFER_TYPE_TX == transfer_data.transfer_type)
                || (SPI_TRANSFER_TYPE_RX == transfer_data.transfer_type))
            ret_val = ER_INVAL;
        else
            ret_val = ER_PARAM;
    }
    else
    {
        if (ER_OK == (ret_val = spi_tx_param_check(transfer_data)))
        {
            if (ER_OK == (ret_val = spi_rx_param_check(transfer_data)))
            {
                if (((SPI_TRANSFER_MODE_BLOCKING == transfer_data.transfer_mode_tx)
                        && (SPI_TRANSFER_MODE_BLOCKING != transfer_data.transfer_mode_rx))
                        || ((SPI_TRANSFER_MODE_BLOCKING == transfer_data.transfer_mode_rx)
                                && (SPI_TRANSFER_MODE_BLOCKING != transfer_data.transfer_mode_tx)))
                {
                    /* If blocking functionality desired, both tx and rx must be blocking */
                    ret_val = ER_PARAM;
                }
            }
        }
        if (ER_OK == ret_val)
        {
            if (SPI_CHANNEL_STATE_CLOSED == spi_channel_states[chan_num])
            {
                ret_val = ER_INVAL;
            }
            else if (SPI_CHANNEL_STATE_BUSY == spi_channel_states[chan_num])
            {
                ret_val = ER_BUSY;
            }
            else if (ER_OK == (ret_val = spi_readwrite(chan_num, transfer_data)))
            {
                if (spi_istransferring(chan_num))
                {
                    /* Not a blocking transfer */
                    spi_channel_states[chan_num] = SPI_CHANNEL_STATE_BUSY;
                }
            }
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SPI_ReadWrite
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_SPI_Close
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - SPI channel number to close
 *
 *  Description:    closes a SPI channel
 *
 **********************************************************************************************************************/
ER_RET R_SPI_Close (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

    if (chan_num >= MAX_SPI_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
    {

        spi_channelclose(chan_num);
        spi_channel_states[chan_num] = SPI_CHANNEL_STATE_CLOSED;

    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SPI_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       spi_transfer_completed
 *
 *  Return value:   void
 *
 *  Parameters:     chan_num - SPI channel number for which the transfer has completed
 *
 *  Description:    NON-interface function so parameters not required to be checked.
 *                  Called when a non-blocking/DMA transfer has completed so
 *                  SPI channel state can be updated.
 *
 **********************************************************************************************************************/
void spi_transfer_completed (uint8_t chan_num)
{
    if (SPI_CHANNEL_STATE_BUSY == spi_channel_states[chan_num])
    {
        spi_channel_states[chan_num] = SPI_CHANNEL_STATE_OPEN;
    }
    return;
}
/***********************************************************************************************************************
 End of function spi_transfer_completed
 **********************************************************************************************************************/

