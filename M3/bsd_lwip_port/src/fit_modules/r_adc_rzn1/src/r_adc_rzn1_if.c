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
 * $Revision: 1303 $
 * $Date: 2019-02-25 16:33:52 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :   RZ/N1 bare metal Drivers
 * FILE         :   r_adc_rzn1_if.c
 * Description  :   ADC driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "r_adc_rzn1_config.h"
#include "r_adc_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define ADC_IS_CHAN_OPEN(chan_num)              (m_vc_channels_open.value & ADC_CHAN_NUM_TO_BIT_MASK(chan_num))
#define ADC_CHAN_CLOSED                         (0)

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static ADC_IF_STATE_E m_adc_state = ADC_STATE_NOT_INIT; /* ADC state */
static ADC_VC_T m_vc_channels_open;

/***********************************************************************************************************************
 * Local function definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 External variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_ADC_GetVersion
 *
 *  Return value:   Driver number
 *
 *  Parameters:     Pointer to buffer for version information
 *  Description:    Returns the ADC driver version number
 *
 **********************************************************************************************************************/
void R_ADC_GetVersion (void *buf)
{
    ((uint8_t *) buf)[1] = (uint8_t)ADC_DRIVER_MAJOR_VERSION_NUMBER;
    ((uint8_t *) buf)[0] = (uint8_t)ADC_DRIVER_MINOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function R_ADC_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_ADC_Init
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *  Description:    Initialise ADC driver and channels interface state
 *
 **********************************************************************************************************************/
ER_RET R_ADC_Init (void)
{
    ER_RET ret_val = ER_OK;

    if (ADC_STATE_NOT_INIT != m_adc_state)
    {
        return ER_INVAL;
    }

    m_vc_channels_open.value = 0;

    /* Initialise the ADC driver */
    ret_val = adc_init();

    if (ER_OK == ret_val)
    {
        m_adc_state = ADC_STATE_INIT;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_ADC_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_ADC_Uninitialise
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *  Description:    Un-Initialise ADC IP
 *
 **********************************************************************************************************************/
ER_RET R_ADC_Uninitialise (void)
{
    ER_RET ret_val = ER_OK;

    if ((ADC_STATE_INIT != m_adc_state) || (ADC_CHAN_CLOSED != m_vc_channels_open.value))
    {
        return ER_INVAL;
    }

    m_adc_state = ADC_STATE_NOT_INIT;

    /* Initialise the ADC driver */
    ret_val = adc_uninitialise();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_ADC_Uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_ADC_Open
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - ADC channel number to open
 *                  ptr_adc_config - ADC Configuration parameters
 *
 *  Description:    Opens an ADC channel
 *
 **********************************************************************************************************************/
ER_RET R_ADC_Open (uint8_t chan_num, ADC_VC_CONFIG_T * ptr_adc_config)
{
    ER_RET ret_val = ER_OK;

    if (ADC_STATE_INIT != m_adc_state)
    {
        return ER_INVAL;
    }

#if ADC_CFG_PARAM_CHECKING_ENABLE
    if ((FIT_NO_PTR == ptr_adc_config) || (chan_num >= ADC_MAX_LOGICAL_CHANNELS) || ADC_IS_CHAN_OPEN(chan_num))
    {
        return ER_PARAM;
    }

#ifndef RZN1D
    if (ADC_2 & ptr_adc_config->adc_module)
    {
        /* ADC 2 module not supported on any other device than RZN1D */
        return ER_PARAM;
    }
#endif /* RZN1D */
#endif /* ADC_CFG_PARAM_CHECKING_ENABLE */

    /* Attempt to open and configure the channel */
    ret_val = adc_channel_open(chan_num, ptr_adc_config);
    if (ER_OK == ret_val)
    {
        m_vc_channels_open.value |= ADC_CHAN_NUM_TO_BIT_MASK(chan_num);
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_ADC_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_ADC_Close
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - ADC channel number to close
 *
 *  Description:    Closes an ADC channel
 *
 **********************************************************************************************************************/
ER_RET R_ADC_Close (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

    if (ADC_STATE_INIT != m_adc_state)
    {
        return ER_INVAL;
    }

    if ((chan_num >= ADC_MAX_LOGICAL_CHANNELS) || (ADC_CHAN_CLOSED == ADC_IS_CHAN_OPEN(chan_num)))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Close the ADC channel */
        ret_val = adc_channel_close(chan_num);
        m_vc_channels_open.value &= ( ~ADC_CHAN_NUM_TO_BIT_MASK(chan_num));
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_ADC_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_ADC_Read
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - ADC channel number
 *                  ptr_acq_cmd:
 *                      sample_buf   - Where data received is stored
 *                      transfer_mode - The transfer mode of the conversion
 *
 *  Description:    Reads data from an ADC channel after sampling.
 *                  If BLOCKING (synchronous) mode then returns when all the requested data
 *                      has been transfered or a timeout occurs.
 *                  If NON-BLOCKING/DMA (asynchronous) mode then initiates the conversion and returns.
 *                      In this case a callback parameter is required to be passed through a previous call to R_ADC_Control().
 *
 **********************************************************************************************************************/
ER_RET R_ADC_Read (uint8_t chan_num, ADC_ACQ_CMD_T * ptr_acq_cmd)
{
    ER_RET ret_val = ER_OK;

    /* Parameter check */
    if ((FIT_NO_PTR == ptr_acq_cmd) || (chan_num >= ADC_MAX_LOGICAL_CHANNELS))
    {
        ret_val = ER_PARAM;
    }

    if (ER_OK == ret_val)
    {
#if ADC_CFG_PARAM_CHECKING_ENABLE
        ADC_VC_T busy_channels;

        ret_val = adc_get_all_chan_busy_state( &busy_channels);

        if (ADC_CHAN_CLOSED == ADC_IS_CHAN_OPEN(chan_num))
        {
            ret_val = ER_INVAL;
        }
        else if (ADC_CHAN_NUM_TO_BIT_MASK(chan_num) & busy_channels.value)
        {
            ret_val = ER_BUSY;
        }
        else
#endif
        {
            ret_val = adc_read(chan_num, ptr_acq_cmd);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_ADC_Read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_ADC_ReadGroup
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_group - ADC channel group selection via bit fields
 *                  ptr_acq_cmd:
 *                      sample_buf   - Where data received is stored
 *                      transfer_mode - The transfer mode of the conversion
 *
 *  Description:    Reads data from selected ADC channels after sampling.
 *                  If BLOCKING (synchronous) mode then returns when all the requested data
 *                      has been transferred or a timeout occurs.
 *                  If NON-BLOCKING/DMA (asynchronous) mode then initiates the conversion and returns.
 *                      In this case a callback parameter is required to be passed through a previous call to R_ADC_Control().
 *
 **********************************************************************************************************************/
ER_RET R_ADC_ReadGroup (ADC_VC_T chan_group, ADC_ACQ_CMD_T * ptr_acq_cmd)
{
    ER_RET ret_val = ER_OK;
    
    /* Parameter check */
    if (FIT_NO_PTR == ptr_acq_cmd)
    {
        return ER_PARAM;
    }

#if ADC_CFG_PARAM_CHECKING_ENABLE
    ADC_VC_T busy_channels;

    if ((m_vc_channels_open.value & chan_group.value) != chan_group.value)
    {
        /* Not all the channels are currently Open */
        return ER_INVAL;
    }

    ret_val = adc_get_all_chan_busy_state( &busy_channels);

    if (chan_group.value & busy_channels.value)
    {
        /* Some Channels are busy */
        return ER_BUSY;
    }
#endif

    if (ER_OK == ret_val)
    {
        ret_val = adc_read_group(chan_group, ptr_acq_cmd);
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_ADC_ReadGroup
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_ADC_Control
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - ADC channel number to control
 *                  control_request - request to configure channel or get channel info.
 *                  adc_ctrl - configuration data (to set or get).
 *
 *                  NOTE: API function checks that adc_ctrl is non-zero.
 *                  The upper layer should check that the buffer lies within a valid address range.
 *
 *  Description:    Configure channel parameters, set transfer parameters or
 *                  get channel or transfer info, depending on control_request
 *
 **********************************************************************************************************************/
ER_RET R_ADC_Control (uint8_t chan_num, ADC_CONTROL_REQUEST_E control_request, void * ptr_adc_ctrl)
{
    ADC_VC_T busy_channels;
    ER_RET ret_val = ER_OK;
    bool isChanBusy;

    ret_val = adc_get_all_chan_busy_state( &busy_channels);
    isChanBusy = (ADC_CHAN_NUM_TO_BIT_MASK(chan_num) & busy_channels.value);

    if ((chan_num >= ADC_MAX_LOGICAL_CHANNELS) || (FIT_NO_PTR == ptr_adc_ctrl))
    {
        ret_val = ER_PARAM;
    }
    else
    {
#if ADC_CFG_PARAM_CHECKING_ENABLE
        if ((ADC_CONTROL_SET_DMA_CAPABILITY != control_request) && (ADC_CONTROL_SET_DMA_CALLBACK != control_request)
                && (ADC_CONTROL_SET_SAMP_HOLD_CAPABILITY != control_request)
                && (ADC_CONTROL_GET_CHAN_STATE != control_request))
        {
            if (ADC_CHAN_CLOSED == ADC_IS_CHAN_OPEN(chan_num))
            {
                ret_val = ER_INVAL;
            }
            else if (isChanBusy)
            {
                ret_val = ER_BUSY;
            }
            else
            {
                /* Proceed */
                ;
            }
        }
#endif
        if (ER_OK == ret_val)
        {
            switch (control_request)
            {
                case ADC_CONTROL_SET_CHAN_CALLBACK:
                    ret_val = adc_register_channel_callback(chan_num, (adc_chan_complete_callback_t) ptr_adc_ctrl);
                break;

                case ADC_CONTROL_GET_CHAN_STATE:
                    if (ADC_CHAN_CLOSED == ADC_IS_CHAN_OPEN(chan_num))
                    {
                        *(ADC_IF_STATE_E *) ptr_adc_ctrl = ADC_STATE_CHANNEL_CLOSED;
                    }
                    else
                    {
                        if (isChanBusy)
                        {
                            *(ADC_IF_STATE_E *) ptr_adc_ctrl = ADC_STATE_CHANNEL_BUSY;
                        }
                        else
                        {
                            *(ADC_IF_STATE_E *) ptr_adc_ctrl = ADC_STATE_CHANNEL_OPEN;
                        }
                    }
                break;

                case ADC_CONTROL_SET_CHAN_CONFIG:
                    ret_val = adc_set_channel_config(chan_num, (ADC_VC_CONFIG_T *) ptr_adc_ctrl);
                break;

                case ADC_CONTROL_GET_CHAN_CONFIG:
                    ret_val = adc_get_channel_config(chan_num, (ADC_VC_CONFIG_T *) ptr_adc_ctrl);
                break;

                case ADC_CONTROL_SET_CHAN_TRIGGER:
                    ret_val = adc_set_channel_trigger(chan_num,
                            ((ADC_VC_TRIG_CONFIG_T *) ptr_adc_ctrl)->trig_trig_enable,
                            ((ADC_VC_TRIG_CONFIG_T *) ptr_adc_ctrl)->trig_select);
                break;

                case ADC_CONTROL_SET_DMA_CAPABILITY:
                    ret_val = adc_set_dma_mode( *(ADC_DMA_CONTROL_E *) ptr_adc_ctrl);
                break;

                case ADC_CONTROL_SET_DMA_CALLBACK:
                    ret_val = adc_register_dma_callback((adc_dma_complete_callback_t) ptr_adc_ctrl);
                break;

                case ADC_CONTROL_SET_SAMP_HOLD_CAPABILITY:
                    ret_val = adc_set_samplehold_mode( *(ADC_SAMP_HOLD_CONTROL_E *) ptr_adc_ctrl);
                break;

                default:
                    ret_val = ER_PARAM;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_ADC_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_ADC_GetConversionStatus
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *
 *  Description:    Returns EBUSY if an ADC acquisition is in progress
 *                  otherwise returns EOK
 *                  NOTE: If a channel is in continuous mode then EBUSY is
 *                  always returned.
 *
 **********************************************************************************************************************/
ER_RET R_ADC_GetConversionStatus (void)
{
    ADC_VC_T busy_channels;
    ER_RET ret_val = ER_OK;

    ret_val = adc_get_all_chan_busy_state( &busy_channels);

    if ((ER_OK == ret_val) && (busy_channels.value))
    {
        ret_val = ER_BUSY;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_ADC_GetConversionStatus
 **********************************************************************************************************************/
