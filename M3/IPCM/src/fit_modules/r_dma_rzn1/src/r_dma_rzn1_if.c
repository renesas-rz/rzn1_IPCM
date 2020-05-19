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
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * $Revision: 1815 $
 * $Date: 2020-01-27 14:51:49 +0000 (Mon, 27 Jan 2020) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_dma_rzn1_if.c
 * Description  :  DMA (Direct Memory Access)control interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2020. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_dma_rzn1_if.h"
#include "r_dma_rzn1.h"
#include "r_dma_rzn1_config.h"

/***********************************************************************************************************************
 Data structures
 **********************************************************************************************************************/
typedef enum
{
    DMAC_STATE_CLOSED = 0, DMAC_STATE_OPEN
} DMAC_STATE;

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static DMA_DRIVER_STATE_E dma_driver_state = DMA_DRIVER_STATE_UNINITIALISED;
static DMAC_STATE dmac_state[MAX_DMAC];
static DMA_CHANNEL_STATE dma_channels_state[MAX_DMAC][MAX_DMA_CHAN];
static bool channel_paused[MAX_DMAC][MAX_DMA_CHAN];

/***********************************************************************************************************************
 * External variables
 **********************************************************************************************************************/
extern const DMA_CHAN_CTRL DMA_DEFAULT_CHAN_CTRL =
                                                    {
                                                        .PRIORITY = DEFAULT_CHAN_PRIORITY,
                                                        .SRC_HS.TYPE = HARDWARE,
                                                        .DST_HS.TYPE = HARDWARE,
                                                        .DST_HS.INTERFACE_POLARITY = 0,
                                                        .SRC_HS.INTERFACE_POLARITY = 0,
                                                        .SRC_HS.HS_INTERFACE = 0,
                                                        .DST_HS.HS_INTERFACE = 0
                                                    };

extern const DMA_TRANS_CTRL DMA_DEFAULT_TRANS_CTRL =
                                                    {
                                                        .INT_EN = true, .TR_FLOW = PTP_DMAC,
                                                        .SRC_INCR = INCREMENT,
                                                        .DST_INCR = INCREMENT,
                                                        .SRC_TR_WIDTH = BITS8,
                                                        .DST_TR_WIDTH = BITS8,
                                                        .SRC_BRST_LEN = DATA_ITEMS_4,
                                                        .DST_BRST_LEN = DATA_ITEMS_4,
                                                        .BLOCK_SIZE = 2
                                                    };

/***********************************************************************************************************************
 *
 *  Function Name:  R_DMA_GetVersion
 *
 *  Return Value:   None
 *
 *  Parameters:     buf - buffer where the version is stored
 *
 *  Description:    Returns the DMA driver version number
 *
 **********************************************************************************************************************/
void R_DMA_GetVersion (void *buf)
{
    ((uint8_t *) buf)[1] = (uint8_t) DMA_DRIVER_MAJOR_VERSION_NUMBER;
    ((uint8_t *) buf)[0] = (uint8_t) DMA_DRIVER_MINOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function R_DMA_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_DMA_Init
 *
 *  Return Value:   Error status
 *
 *  Parameters:     None
 *
 *  Description:    Opens a DMA channels
 *
 **********************************************************************************************************************/
ER_RET R_DMA_Init (void)
{
    ER_RET ret_val = ER_OK;
    uint8_t dmac_number;
    uint8_t channel;

    if (DMA_DRIVER_STATE_INITIALISED == dma_driver_state)
    {
        ret_val = ER_INVAL;
    }
    else
    {
        /* Clear internal parameters */
        for (dmac_number = 0; dmac_number < MAX_DMAC; dmac_number++)
        {
            dmac_state[dmac_number] = DMAC_STATE_CLOSED;

            for (channel = 0; channel < MAX_DMA_CHAN; channel++)
            {
                dma_channels_state[dmac_number][channel] = DMA_CHANNEL_STATE_CLOSED;
                channel_paused[dmac_number][channel] = 0;
            }
        }
        dma_init();
        dma_driver_state = DMA_DRIVER_STATE_INITIALISED;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_DMA_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_DMA_Uninitialise
 *
 *  Return Value:   Error status
 *
 *  Parameters:     None
 *
 *  Description:    Disables a DMA channels
 *
 **********************************************************************************************************************/
ER_RET R_DMA_Uninitialise (void)
{
    ER_RET ret_val = ER_OK;
    uint8_t dmac_number;
    uint8_t channel;

    if (DMA_DRIVER_STATE_UNINITIALISED == dma_driver_state)
    {
        ret_val = ER_INVAL;
    }
    else
    {
        /* Clear internal parameters */
        for (dmac_number = 0; dmac_number < MAX_DMAC; dmac_number++)
        {
            dmac_state[dmac_number] = DMAC_STATE_CLOSED;

            for (channel = 0; channel < MAX_DMA_CHAN; channel++)
            {
                dma_channels_state[dmac_number][channel] = DMA_CHANNEL_STATE_CLOSED;
                channel_paused[dmac_number][channel] = 1;
            }
        }
        dma_uninit();
        dma_driver_state = DMA_DRIVER_STATE_UNINITIALISED;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_DMA_Uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_DMA_Open
 *
 *  Return Value:   Error status
 *
 *  Parameters:     DMAC_number - Which DMA controller to open
 *                  channel - Which channel to open
 *
 *  Description:    Opens a DMA channel
 *
 **********************************************************************************************************************/
ER_RET R_DMA_Open (uint8_t DMAC_number, uint8_t channel)
{
    ER_RET ret_val = ER_OK;

#if DMA_CFG_PARAM_CHECKING_ENABLE
    if ((MAX_DMAC <= DMAC_number) || (MAX_DMA_CHAN <= channel))
    {
        ret_val = ER_PARAM;
    }
#endif

    if ((ER_OK == ret_val) && (DMAC_STATE_CLOSED == dmac_state[DMAC_number]))
    {
        /* DMAC has not already been opened */
        ret_val = dma_open(DMAC_number);
        if (ER_OK == ret_val)
        {
            dmac_state[DMAC_number] = DMAC_STATE_OPEN;
        }
    }

    if (ER_OK == ret_val)
    {
        if (DMA_CHANNEL_STATE_CLOSED == dma_channels_state[DMAC_number][channel])
        {
            /* Channel has not already been opened */
            dma_channels_state[DMAC_number][channel] = DMA_CHANNEL_STATE_OPEN;

            /* Initialise channel */
            dma_disablechannel(DMAC_number, channel);
            dma_setchanconfig(DMAC_number, channel, (DMA_CHAN_CTRL *) &DMA_DEFAULT_CHAN_CTRL);
            dma_settransconfig(DMAC_number, channel, (DMA_TRANS_CTRL *) &DMA_DEFAULT_TRANS_CTRL);
        }
        else
        {
            ret_val = ER_INVAL;
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_DMA_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_DMA_Close
 *
 *  Return Value:   Error status
 *
 *  Parameters:     DMAC_number - Which DMA controller to close
 *                  channel - which channel to close
 *
 *  Description:    Closes a DMA channel or controller
 *
 **********************************************************************************************************************/
ER_RET R_DMA_Close (uint8_t DMAC_number, int8_t channel)
{
    ER_RET ret_val = ER_OK;
    uint8_t i;

#if DMA_CFG_PARAM_CHECKING_ENABLE
    if (MAX_DMAC <= DMAC_number)
    {
        ret_val = ER_PARAM;
    }
#endif

    if ((ER_OK == ret_val) && (DMAC_STATE_OPEN == dmac_state[DMAC_number]))
    {
        /* If channel is -1 then close entire DMAC */
        if (DMA_CLOSE_ALL == channel)
        {
            ret_val = dma_close(DMAC_number);
            for (i = DMA_CHAN_0; i < MAX_DMA_CHAN; i++)
            {
                dma_channels_state[DMAC_number][i] = DMA_CHANNEL_STATE_CLOSED;
            }
            dmac_state[DMAC_number] = DMAC_STATE_CLOSED;
        }
        else
        {
            /* Close specified channel */
            if ((channel < DMA_CHAN_0) || (channel >= MAX_DMA_CHAN))
            {
                ret_val = ER_PARAM;
            }
            else
            {
                dma_disablechannel(DMAC_number, channel);
                dma_channels_state[DMAC_number][channel] = DMA_CHANNEL_STATE_CLOSED;
            }
        }
    }
    else
    {
        ret_val = ER_INVAL;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_DMA_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_DMA_Control
 *
 *  Return Value:   Error status
 *
 *  Parameters:     DMAC_number - Which DMA controller to configure.
 *                  channel - Which channel to configure.
 *                  control_request - Which control action to implement.
 *                  control - The control parameter that is used along with the
 *                           control action to configure the channel a certain way.
 *
 *  Description:    Controls a DMA channel
 *
 **********************************************************************************************************************/
ER_RET R_DMA_Control (uint8_t DMAC_number, uint8_t channel, DMA_CONTROL_REQUEST control_request, void *control)
{
    ER_RET ret_val = ER_OK;

#if DMA_CFG_PARAM_CHECKING_ENABLE
    /* Check DMAC number and channel */
    if (((MAX_DMAC <= DMAC_number) || (MAX_DMA_CHAN <= channel)) || (FIT_NO_PTR == control))
    {
        ret_val = ER_PARAM;
    }
#endif

    if (ER_OK == ret_val)
    {
        switch (control_request)
        {
            case DMA_CONTROL_SET_CALL_BACK:
                dma_setcallback(DMAC_number, channel, (dma_trans_complete_callback) control);
            break;

            case DMA_CONTROL_SET_CHAN_CONFIG:
                if (DMA_CHANNEL_STATE_OPEN != dma_channels_state[DMAC_number][channel])
                {
                    ret_val = ER_INVAL;
                }
                else
                {
                    dma_disablechannel(DMAC_number, channel);
                    ret_val = dma_setchanconfig(DMAC_number, channel, (DMA_CHAN_CTRL *) control);
                }
            break;

            case DMA_CONTROL_GET_CHAN_CONFIG:
                dma_getchanconfig(DMAC_number, channel, (DMA_CHAN_CTRL *) control);
            break;

            case DMA_CONTROL_SET_TRANS_CONFIG:
                if (DMA_CHANNEL_STATE_OPEN != dma_channels_state[DMAC_number][channel])
                {
                    ret_val = ER_INVAL;
                }
                else
                {
                    dma_disablechannel(DMAC_number, channel);
                    ret_val = dma_settransconfig(DMAC_number, channel, (DMA_TRANS_CTRL *) control);
                }
            break;

            case DMA_CONTROL_GET_TRANS_CONFIG:
                dma_gettransconfig(DMAC_number, channel, (DMA_TRANS_CTRL *) control);
            break;

            case DMA_CONTROL_GET_CHAN_STATE:
                *(DMA_CHANNEL_STATE *) control = dma_channels_state[DMAC_number][channel];
            break;

            case DMA_CONTROL_PAUSE_TRANS:
                if ((DMA_CHANNEL_STATE_BUSY == dma_channels_state[DMAC_number][channel])
                        && (false == channel_paused[DMAC_number][channel]))
                {
                    dma_playpause(DMAC_number, channel, true);
                    channel_paused[DMAC_number][channel] = true;
                }
                else
                {
                    ret_val = ER_INVAL;
                }
            break;

            case DMA_CONTROL_RESUME_TRANS:
                if ((DMA_CHANNEL_STATE_BUSY == dma_channels_state[DMAC_number][channel])
                        && (true == channel_paused[DMAC_number][channel]))
                {
                    dma_playpause(DMAC_number, channel, false);
                    channel_paused[DMAC_number][channel] = false;
                }
                else
                {
                    ret_val = ER_INVAL;
                }
            break;

            case DMA_CONTROL_FREE_CHAN:
                if (DMA_CHANNEL_STATE_BUSY == dma_channels_state[DMAC_number][channel])
                {
                    dma_disablechannel(DMAC_number, channel);
                    dma_channels_state[DMAC_number][channel] = DMA_CHANNEL_STATE_OPEN;
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
 End of function R_DMA_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_DMA_Write
 *
 *  Return Value:   Error status
 *
 *  Parameters:     DMAC_number - Which DMA controller to use.
 *                  channel - Which channel to send the transaction request to
 *                  req_type - DMA Transfer request type
 *
 *  Description:    Initiates a DMA transfer
 *
 **********************************************************************************************************************/
ER_RET R_DMA_Write (uint8_t DMAC_number, uint8_t channel, DMA_TRANS_REQ_TYPE req_type)
{
    ER_RET ret_val;

#if DMA_CFG_PARAM_CHECKING_ENABLE
    /* Parameter check */
    if ((MAX_DMAC <= DMAC_number) || (MAX_DMA_CHAN <= channel))
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        /* Channel is valid */
        if (DMA_CHANNEL_STATE_CLOSED == dma_channels_state[DMAC_number][channel])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            /* Channel is not closed */
            dma_channels_state[DMAC_number][channel] = DMA_CHANNEL_STATE_BUSY;
            dma_enablechannel(DMAC_number, channel);
            ret_val = dma_transreq(DMAC_number, channel, req_type);
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_DMA_Write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_transfer_completed
 *
 *  Return Value:   None
 *
 *  Parameters:     DMAC_number - The DMA Controller
 *                  channel - The DMA channel
 *
 *  Description:    NON-interface function so parameters not required to be checked.
 *                  Called when a transfer has completed so
 *                  DMA channel state can be updated.
 *
 **********************************************************************************************************************/
void dma_transfer_completed (uint8_t DMAC_number, uint8_t channel)
{
    if (DMA_CHANNEL_STATE_BUSY == dma_channels_state[DMAC_number][channel])
    {
        /*
         Keep channel open in-case of other requests (i.e. timer requests)
         DMA_DisableChannel(DMAC_number, channel);
         */
        dma_channels_state[DMAC_number][channel] = DMA_CHANNEL_STATE_OPEN;
    }
    return;
}
/***********************************************************************************************************************
 End of function dma_transfer_completed
 **********************************************************************************************************************/
