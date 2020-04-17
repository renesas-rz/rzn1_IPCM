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
 * $Revision: 1252 $
 * $Date: 2019-02-12 11:14:16 +0000 (Tue, 12 Feb 2019) $
 *
 * PROJECT NAME :   RZ/N1 bare metal Drivers
 * FILE         :   r_adc_rzn1_if.h
 * Description  :   ADC driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_ADC_RZN1_IF_H__
#define R_ADC_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "r_adc_rzn1.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/* Version Number of API. */
#define ADC_DRIVER_MAJOR_VERSION_NUMBER         (1)
#define ADC_DRIVER_MINOR_VERSION_NUMBER         (1)

#define ADC_INVALID_DATA_VALUE                  (0xFFFFFFFFu)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/* ADC  Channel States */
typedef enum
{
    ADC_STATE_NOT_INIT = 0, /* ADC un-initialised */
    ADC_STATE_INIT, /* ADC initialised */
    ADC_STATE_CHANNEL_OPEN, /* Channel initialised and idle */
    ADC_STATE_CHANNEL_CLOSED, /* Channel uninitialised */
    ADC_STATE_CHANNEL_BUSY, /* Channel currently being used for reading sample */
} ADC_IF_STATE_E;

/* ADC Control Request */
typedef enum
{
    ADC_CONTROL_SET_CHAN_CALLBACK, /* Set channel callback for ADC interrupts */
    ADC_CONTROL_SET_CHAN_CONFIG, /* Set channel configuration */
    ADC_CONTROL_GET_CHAN_CONFIG, /* Get channel configuration */
    ADC_CONTROL_SET_CHAN_TRIGGER, /* Set channel trigger */
    ADC_CONTROL_GET_CHAN_STATE, /* Get channel state(see ADC_VC_CONFIG_T) */
    ADC_CONTROL_SET_DMA_CAPABILITY, /* Set Global DMA Capability */
    ADC_CONTROL_SET_DMA_CALLBACK, /* Set DMA callback */
    ADC_CONTROL_SET_SAMP_HOLD_CAPABILITY, /* Set Global Sample & Hold Capability */
} ADC_CONTROL_REQUEST_E;

/*Virtual Channel Trigger Enable*/
typedef struct
{
        ADC_VC_TRIG_E trig_trig_enable;
        ADC_VC_TRIG_SEL_E trig_select;
} ADC_VC_TRIG_CONFIG_T;

typedef struct
{
        uint32_t channel[ADC_MAX_LOGICAL_CHANNELS];
} ADC_ALL_CHANNEL_BUFFER_T; /* Buffer size is 32bits to allow usage with DMA mode */

/***********************************************************************************************************************
 Default parameters
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Global functions
 **********************************************************************************************************************/
void R_ADC_GetVersion (void *buf);
ER_RET R_ADC_Init (void);
ER_RET R_ADC_Uninitialise (void);
ER_RET R_ADC_Open (uint8_t chan_num, ADC_VC_CONFIG_T * ptr_adc_ctrl);
ER_RET R_ADC_Close (uint8_t chan_num);
ER_RET R_ADC_Read (uint8_t chan_num, ADC_ACQ_CMD_T * ptr_conversion_data);
ER_RET R_ADC_ReadGroup (ADC_VC_T chan_group, ADC_ACQ_CMD_T * ptr_acq_cmd);
ER_RET R_ADC_Control (uint8_t chan_num, ADC_CONTROL_REQUEST_E control_request, void *adc_ctrl);
ER_RET R_ADC_GetConversionStatus (void);
#endif /* R_ADC_RZN1_IF_H__ */
