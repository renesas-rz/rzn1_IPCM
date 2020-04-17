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
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_i2c_rzn1_if.c
 * Description  :  I2C driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "r_i2c_rzn1_config.h"
#include "r_i2c_rzn1_if.h"
#include "r_i2c_rzn1.h"

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static I2C_IF_CHANNEL_STATE_E i2c_channels_state[I2C_MAX_CHANNELS]; /* I2C channel state. Note: only 1 channel supported in bare metal driver */

/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_I2C_GetVersion
 *
 *  Return value:   None.
 *
 *  Parameters:     None.
 *
 *  Description:    Returns the DMA driver version number
 *
 **********************************************************************************************************************/

void R_I2C_GetVersion (void *buf)
{

    ((uint8_t *) buf)[1] = i2c_get_major_version_num();
    ((uint8_t *) buf)[0] = i2c_get_minor_version_num();
}
/***********************************************************************************************************************
 End of function R_I2C_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_I2C_Init
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *  Description:    Initialise I2C IP and I2C channel states
 *
 **********************************************************************************************************************/
ER_RET R_I2C_Init (void)
{
    uint32_t channel;
    ER_RET ret_val = ER_OK;

    for (channel = 0; channel < I2C_MAX_CHANNELS; channel++)
    {
        i2c_channels_state[channel] = I2C_CHANNEL_STATE_CLOSED;
    }

    /* Initialise the I2C driver */
    ret_val = i2c_driver_init();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_I2C_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_I2C_Uninitialise
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *  Description:    Initialise I2C IP and I2C channel states
 *
 **********************************************************************************************************************/
ER_RET R_I2C_Uninitialise (void)
{
    uint32_t channel;
    ER_RET ret_val = ER_OK;

    for (channel = 0; channel < I2C_MAX_CHANNELS; channel++)
    {
        i2c_channels_state[channel] = I2C_CHANNEL_STATE_CLOSED;
    }

    /* Initialise the I2C driver */
    ret_val = i2c_driver_uninitialise();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_I2C_Uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_I2C_Open
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number to open
 *
 *  Description:    Opens an I2C channel
 *
 **********************************************************************************************************************/
ER_RET R_I2C_Open (uint8_t i2c_chan_num)
{
    ER_RET ret_val = ER_OK;

    if (i2c_chan_num < I2C_MAX_CHANNELS)
    {

        if (I2C_CHANNEL_STATE_CLOSED != i2c_channels_state[i2c_chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = i2c_channel_open(i2c_chan_num);
            if (ER_OK == ret_val)
            {
                i2c_channels_state[i2c_chan_num] = I2C_CHANNEL_STATE_OPEN;
            }
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_I2C_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_I2C_Control
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number to control
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
ER_RET R_I2C_Control (uint8_t i2c_chan_num, I2C_CONTROL_REQUEST_E control_request, uint8_t *buf)
{
    ER_RET ret_val = ER_OK;

    if (i2c_chan_num >= I2C_MAX_CHANNELS)
    {
        if (I2C_CONTROL_GET_DRIVER_VERSION != control_request)
        {
            ret_val = ER_PARAM;
        }
    }
    else
    {
        /* For all control requests except I2C_CONTROL_RESET, need a valid buf pointer */
        if (I2C_CONTROL_RESET != control_request)
        {
            if ((void*) 0 == buf)
            {
                ret_val = ER_PARAM;
            }
        }
    }

    if (ER_OK == ret_val)
    {
        /* I2C driver state & parameters are valid */

        switch (control_request)
        {
            case I2C_CONTROL_SET_CHAN_CONFIG:

                /* Set channel configuration (only if channel is OPEN but not busy transferring data) */
                if (I2C_CHANNEL_STATE_OPEN != i2c_channels_state[i2c_chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else
                {
                    ret_val = i2c_set_chan_config(i2c_chan_num, (I2C_CHANNEL_CONFIG_T *) buf);
                }
            break;

            case I2C_CONTROL_GET_CHAN_CONFIG:
                ret_val = i2c_get_chan_config(i2c_chan_num, (I2C_CHANNEL_CONFIG_T *) buf);

            break;

            case I2C_CONTROL_GET_CHAN_STATE:
                buf[0] = i2c_channels_state[i2c_chan_num];
            break;

            case I2C_CONTROL_RESET:

                /* Reset the I2C channel. This will abort a transfer if it's in progress */
                ret_val = i2c_reset(i2c_chan_num);
                if (ER_OK == ret_val)
                {
                    i2c_channels_state[i2c_chan_num] = I2C_CHANNEL_STATE_OPEN;
                }
            break;

            case I2C_CONTROL_SET_COMPLETION_CALLBACK:

                /* Set callback for when a transfer operation has completed */
                if (I2C_CHANNEL_STATE_OPEN == i2c_channels_state[i2c_chan_num])
                {
                    ret_val = i2c_set_trans_completedcallback(i2c_chan_num, (i2c_transfer_complete_callback_t) buf);
                }
                else
                {
                    ret_val = ER_INVAL;
                }
            break;

            default:
                ret_val = ER_PARAM;
            break;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_I2C_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_I2C_Read
 *
 *  Return value:   number chars received
 *
 *  Parameters:     i2c_chan_num - I2C channel number
 *                  i2c_slave_addr - device address
 *                  addr - address internal to the device
 *                  addr_len - number bytes in addr
 *                  buf  - where data received is stored
 *                  data_len - number of bytes to read
 *                  mode - BLOCKING or NON-BLOCKING read
 *
 *  Description:    Reads data from a I2C channel.
 *                  If BLOCKING (synchronous) mode then returns when all the requested data
 *                      has been read or a timeout occurs.
 *                  If NON-BLOCKING (asynchronous) mode then initiates the read process and returns.
 *                  In this case a callback parameter is required to have been passed
 *                  in a previous call to R_I2C_Control().
 *
 **********************************************************************************************************************/
ER_RET R_I2C_Read (uint8_t i2c_chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len, I2C_TRANSFER_MODE_E mode)
{
    ER_RET ret_val = ER_OK;

    if (i2c_chan_num >= I2C_MAX_CHANNELS)
    {
        ret_val = ER_INVAL;
    }
    else
    {
        if (((void *) 0 == buf) || (0 == data_len) || ((void *) 0 == addr))
        {
            ret_val = ER_PARAM;
        }
    }

    if (ER_OK == ret_val)
    {
        /* parameters are valid */

        if (I2C_CHANNEL_STATE_OPEN != i2c_channels_state[i2c_chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            i2c_channels_state[i2c_chan_num] = I2C_CHANNEL_STATE_BUSY;

            if (I2C_TRANSFER_MODE_BLOCKING == mode)
            {
                ret_val = i2c_sync_read(i2c_chan_num, i2c_slave_addr, addr, addr_len, buf, data_len);

                i2c_channels_state[i2c_chan_num] = I2C_CHANNEL_STATE_OPEN;
            }
            else
            {
                /* Non-blocking mode */
                ret_val = i2c_async_read(i2c_chan_num, i2c_slave_addr, addr, addr_len, buf, data_len);

                if (1 == data_len)
                {
                    i2c_channels_state[i2c_chan_num] = I2C_CHANNEL_STATE_OPEN;
                }
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_I2C_Read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_I2C_Write
 *
 *  Return value:   number chars written
 *
 *  Parameters:     i2c_chan_num - I2C channel number
 *                  i2c_slave_addr - device address
 *                  addr - address internal to the device
 *                  addr_len - number bytes in addr
 *                  buf  - data to be written
 *                  data_len - number of bytes to write
 *                  mode - BLOCKING or NON-BLOCKING write
 *
 *  Description:    Writes data to an I2C channel.
 *                  If BLOCKING (synchronous) mode then returns when all the requested data
 *                      has been written or a timeout occurs.
 *                  If NON-BLOCKING (asynchronous) mode then initiates the write process and returns.
 *                  In this case a callback parameter is required to have been passed
 *                  in a previous call to R_I2C_Control().
 *
 **********************************************************************************************************************/
ER_RET R_I2C_Write (uint8_t i2c_chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len, I2C_TRANSFER_MODE_E mode)
{
    ER_RET ret_val = ER_OK;

    if (i2c_chan_num >= I2C_MAX_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        if (((void *) 0 == buf) || (0 == data_len) || ((void *) 0 == addr))
        {
            ret_val = ER_INVAL;
        }
    }

    if (ER_OK == ret_val)
    {
        /* parameters are valid */

        if (I2C_CHANNEL_STATE_OPEN != i2c_channels_state[i2c_chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            i2c_channels_state[i2c_chan_num] = I2C_CHANNEL_STATE_BUSY;

            if (I2C_TRANSFER_MODE_BLOCKING == mode)
            {
                ret_val = i2c_sync_write(i2c_chan_num, i2c_slave_addr, addr, addr_len, buf, data_len);
                i2c_channels_state[i2c_chan_num] = I2C_CHANNEL_STATE_OPEN;
            }
            else
            {
                /* Non-blocking mode */
                ret_val = i2c_async_write(i2c_chan_num, i2c_slave_addr, addr, addr_len, buf, data_len);
                if (1 == data_len)
                {
                    i2c_channels_state[i2c_chan_num] = I2C_CHANNEL_STATE_OPEN;
                }
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_I2C_Write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_I2C_Close
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number to close
 *
 *  Description:    closes a I2C channel
 *
 **********************************************************************************************************************/
ER_RET R_I2C_Close (uint8_t i2c_chan_num)
{
    ER_RET ret_val = ER_OK;

    if (i2c_chan_num >= I2C_MAX_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        if (I2C_CHANNEL_STATE_OPEN != i2c_channels_state[i2c_chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = i2c_channel_close(i2c_chan_num);
            if (ER_OK == ret_val)
            {
                i2c_channels_state[i2c_chan_num] = I2C_CHANNEL_STATE_CLOSED;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_I2C_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_transfer_completed
 *
 *  Return value:   void
 *
 *  Parameters:     chan_num - I2C channel number for which transfer has completed
 *
 *  Description:    NON-interface function so parameters not required to be checked.
 *                  Called when a non-blocking transfer has completed so
 *                  I2C channel state can be updated.
 *
 **********************************************************************************************************************/
void i2c_transfer_completed (uint8_t chan_num)
{
    if (I2C_CHANNEL_STATE_BUSY == i2c_channels_state[chan_num])
    {
        i2c_channels_state[chan_num] = I2C_CHANNEL_STATE_OPEN;
    }
    return;
}
/***********************************************************************************************************************
 End of function i2c_transfer_completed
 **********************************************************************************************************************/

