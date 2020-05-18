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
 * FILE         :  r_qspi_rzn1_if.c
 * Description  :  QSPI driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "platform.h"
#include "r_qspi_rzn1_config.h"
#include "r_qspi_rzn1_if.h"
#include "r_qspi_rzn1.h"

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static QSPI_IF_CHANNEL_STATE_E qspi_channels_state[MAX_QSPI_CHANNELS];

/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_QSPI_GetVersion
 *
 *  Return value:   None.
 *
 *  Parameters:     None.
 *
 *  Description:    Returns the DMA driver version number
 *
 **********************************************************************************************************************/

void R_QSPI_GetVersion (void *buf)
{

    ((uint8_t *) buf)[1] = qspi_get_major_version_num();
    ((uint8_t *) buf)[0] = qspi_get_minor_version_num();
}
/***********************************************************************************************************************
 End of function R_QSPI_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_QSPI_Init
 *
 *  Return value:   None
 *  Parameters:     void
 *  Description:    Initialise QSPI IP and channel states
 *
 **********************************************************************************************************************/
void R_QSPI_Init (void)
{
    uint32_t channel;

    for (channel = 0; channel < MAX_QSPI_CHANNELS; channel++)
    {
        qspi_channels_state[channel] = QSPI_CHANNEL_STATE_CLOSED;
    }
    qspi_init();

    return;
}
/***********************************************************************************************************************
 End of function R_QSPI_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_QSPI_Uninit
 *
 *  Return value:   None
 *  Parameters:     void
 *  Description:    Uninitialise QSPI IP and channel states
 *
 **********************************************************************************************************************/
void R_QSPI_Uninit (void)
{
    uint32_t channel;

    for (channel = 0; channel < MAX_QSPI_CHANNELS; channel++)
    {
        qspi_channels_state[channel] = QSPI_CHANNEL_STATE_CLOSED;
    }
    qspi_uninit();
    return;
}
/***********************************************************************************************************************
 End of function R_QSPI_Uninit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_QSPI_Open
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - QSPI channel number to open
 *
 *  Description:    Opens a QSPI channel
 *
 **********************************************************************************************************************/
ER_RET R_QSPI_Open (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

    if (QSPI_CHANNEL_STATE_CLOSED != qspi_channels_state[chan_num])
    {
        ret_val = ER_INVAL;
    }
    else
    {
        ret_val = qspi_channel_open(chan_num);
        if (ER_OK == ret_val)
        {
            qspi_channels_state[chan_num] = QSPI_CHANNEL_STATE_OPEN;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_QSPI_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_QSPI_Control
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - QSPI channel number to control
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
ER_RET R_QSPI_Control (uint8_t chan_num, QSPI_CONTROL_REQUEST_E control_request, uint8_t *buf)
{
    ER_RET ret_val = ER_OK;

    if (chan_num >= MAX_QSPI_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* For all control requests except qspi_CONTROL_RESET, need a valid buf pointer */
        if (QSPI_CONTROL_RESET != control_request)
        {
            if ((void*) 0 == buf)
            {
                ret_val = ER_PARAM;
            }
        }
    }
    if (ER_OK == ret_val)
    {
        /* QSPI driver state & parameters are valid */

        switch (control_request)
        {
            case QSPI_CONTROL_SET_TRANSFER_CONFIG:
                if (QSPI_CHANNEL_STATE_OPEN != qspi_channels_state[chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else
                {
                    ret_val = qspi_set_transfer_config(chan_num, (qspi_info_t *) buf);
                }
            break;

            case QSPI_CONTROL_GET_TRANSFER_CONFIG:
                if (QSPI_CHANNEL_STATE_CLOSED == qspi_channels_state[chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else
                {
                    ret_val = qspi_get_transfer_config(chan_num, (qspi_info_t *) buf);
                }
            break;

            case QSPI_CONTROL_GET_CHAN_STATE:

                /* Get channel state (see QSPI_IF_CHANNEL_STATE_E) */
                buf[0] = qspi_channels_state[chan_num];
            break;

            case QSPI_CONTROL_RESET:
                if (QSPI_CHANNEL_STATE_CLOSED == qspi_channels_state[chan_num])
                {
                    ret_val = ER_INVAL;
                }
                else
                {
                    /* Reset the QSPI channel */
                    ret_val = qspi_reset(chan_num);
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
 End of function R_QSPI_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_QSPI_Read
 *
 *  Return value:   number chars received
 *
 *  Parameters:     chan_num - QSPI channel number
 *                  offset - Offset in bytes from start of Flash from where data should be read
 *                  buf - pointer to buffer where data read from Flash should be stored
 *                  block_len - number of bytes to read
 *
 *  Description:    Reads data from Flash memory via QSPI channel.
 *
 **********************************************************************************************************************/
ER_RET R_QSPI_Read (uint8_t chan_num, uint32_t offset, uint8_t *buf, uint32_t block_len)
{
    ER_RET ret_val = ER_OK;

    if (chan_num >= MAX_QSPI_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        if (((void *) 0 == buf) || (0 == block_len))
        {
            ret_val = ER_PARAM;
        }
    }

    if (ER_OK == ret_val)
    {
        /* parameters are valid */

        if (QSPI_CHANNEL_STATE_OPEN != qspi_channels_state[chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            qspi_channels_state[chan_num] = QSPI_CHANNEL_STATE_BUSY;
            ret_val = qspi_read(chan_num, offset, buf, block_len);
            qspi_channels_state[chan_num] = QSPI_CHANNEL_STATE_OPEN;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_QSPI_Read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_QSPI_Erase
 *
 *  Return value:   Error Status
 *
 *  Parameters:     chan_num - QSPI channel number
 *                  erase_block_offset - Offset in bytes from start of Flash from where data should be erased
 *                  erase_size - size to erase
 *                  Note1:  Minimum erasable block size is 4k bytes (0x1000 or QSPI_ERASE_BLOCK_SIZE_4K)
 *                  Note2: If number_blocks is 0xffffffff then whole flash is erased
 *
 *  Description:    Erases serial flash
 *
 **********************************************************************************************************************/
ER_RET R_QSPI_Erase (uint8_t chan_num, uint32_t erase_block_offset, uint32_t erase_size)
{
    ER_RET ret_val = ER_OK;

    if (chan_num >= MAX_QSPI_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        if (0 == erase_size)
        {
            ret_val = ER_PARAM;
        }
    }

    if (ER_OK == ret_val)
    {
        /* check to make sure that block_offset is on the minimum erase size boundary and, also
         number of blocks is a multiple of the minimum erase size */
        if ((erase_block_offset % QSPI_MIN_ERASE_BLOCK_SIZE) || (erase_size % QSPI_MIN_ERASE_BLOCK_SIZE))
        {
            ret_val = ER_PARAM;
        }
    }

    if (ER_OK == ret_val)
    {
        /* parameters are valid */

        if (QSPI_CHANNEL_STATE_OPEN != qspi_channels_state[chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            qspi_channels_state[chan_num] = QSPI_CHANNEL_STATE_BUSY;

            ret_val = qspi_erase(chan_num, erase_block_offset, erase_size);

            qspi_channels_state[chan_num] = QSPI_CHANNEL_STATE_OPEN;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_QSPI_Erase
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_QSPI_Write
 *
 *  Return value:   Error Status
 *
 *  Parameters:     chan_num - QSPI channel number
 *                  offset - Offset in bytes from start of Flash to where data should be written.
 *                  buf - pointer to buffer for data to be written
 *                  block_len - number of bytes to write
 *
 *  Description:    Writes data to Flash memory via QSPI channel.
 *
 **********************************************************************************************************************/
ER_RET R_QSPI_Write (uint8_t chan_num, uint32_t offset, uint8_t *buf, uint32_t block_len)
{
    ER_RET ret_val = ER_OK;

    if (chan_num >= MAX_QSPI_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        if (((void *) 0 == buf) || (0 == block_len))
        {
            ret_val = ER_PARAM;
        }
    }

    if (ER_OK == ret_val)
    {
        /* parameters are valid */

        if (QSPI_CHANNEL_STATE_OPEN != qspi_channels_state[chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            qspi_channels_state[chan_num] = QSPI_CHANNEL_STATE_BUSY;

            ret_val = qspi_write(chan_num, offset, buf, block_len);

            qspi_channels_state[chan_num] = QSPI_CHANNEL_STATE_OPEN;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_QSPI_Write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_QSPI_Close
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - QSPI channel number to close
 *
 *  Description:    closes a QSPI channel
 *
 **********************************************************************************************************************/
ER_RET R_QSPI_Close (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

    if (chan_num >= MAX_QSPI_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        if (QSPI_CHANNEL_STATE_OPEN != qspi_channels_state[chan_num])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = qspi_channel_close(chan_num);
            if (ER_OK == ret_val)
            {
                qspi_channels_state[chan_num] = QSPI_CHANNEL_STATE_CLOSED;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_QSPI_Close
 **********************************************************************************************************************/

