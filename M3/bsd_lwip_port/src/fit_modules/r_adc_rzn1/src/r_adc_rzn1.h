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
 * FILE         :  r_adc_rzn1.h
 * Description  :  ADC driver definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_ADC_RZN1_H__
#define R_ADC_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define ADC_MAX_LOGICAL_CHANNELS                (16u)
#define ADC_MAX_VALUE                           (0xFFFu)
#define ADC_DATA_MASK                           (0x00000FFFu)
#define ADC_CHAN_NUM_TO_BIT_MASK(chan_num)      ((uint16_t)(1 << (chan_num)))

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
typedef enum
{
    ADC_VC0 = 0,
    ADC_VC1 = 1,
    ADC_VC2 = 2,
    ADC_VC3 = 3,
    ADC_VC4 = 4,
    ADC_VC5 = 5,
    ADC_VC6 = 6,
    ADC_VC7 = 7,
    ADC_VC8 = 8,
    ADC_VC9 = 9,
    ADC_VC10 = 10,
    ADC_VC11 = 11,
    ADC_VC12 = 12,
    ADC_VC13 = 13,
    ADC_VC14 = 14,
    ADC_VC15 = 15,
} ADC_VIRT_CHAN_E;

typedef enum
{
    ADC_DMA_DISABLE = 0, ADC_DMA_ENABLE = 1,
} ADC_DMA_CONTROL_E;

typedef enum
{
    ADC_SAMP_HOLD_DISABLE = 0, ADC_SAMP_HOLD_ENABLE = 7, /* Enable capability on all 3 Physical Sample & Hold Channels */
} ADC_SAMP_HOLD_CONTROL_E;

typedef enum
{
    ADC_OPERATIONAL_MODE = 0, ADC_POWER_DOWN_MODE = 1,
} ADC_VC_POWER_MODE_E;

/* Channel Configuration Types */
typedef enum
{
    ADC_NONE = 0, ADC_1 = 1, ADC_2 = 2, ADC_BOTH = 3,
} ADC_MODULE;

typedef enum
{
    ADC1_IN0 = 0,
    ADC1_IN1 = 1,
    ADC1_IN2 = 2,
    ADC1_IN3 = 3,
    ADC1_IN4 = 4,
    ADC1_IN6 = 5,
    ADC1_IN7 = 6,
    ADC1_IN8 = 7,
} ADC1_VC_PHYSICAL_CHAN_E;

typedef enum
{
    ADC2_IN0 = 0,
    ADC2_IN1 = 1,
    ADC2_IN2 = 2,
    ADC2_IN3 = 3,
    ADC2_IN4 = 4,
    ADC2_IN6 = 5,
    ADC2_IN7 = 6,
    ADC2_IN8 = 7,
} ADC2_VC_PHYSICAL_CHAN_E;

typedef enum /* Sample & Hold channels are selected by bit mask rather than a number */
{
    ADC_SH_CHAN_NONE = 0,
    ADC_SH_CHAN_6 = 1,
    ADC_SH_CHAN_7 = 2,
    ADC_SH_CHAN_8 = 4,
} ADC_VC_SAMP_HOLD_CHAN_E;

typedef enum
{
    ADC_MASKLOCK0 = 0, ADC_MASKLOCK1 = 1, ADC_MASKLOCK2 = 2, ADC_MASKLOCK3 = 3,
} ADC_VC_MASKLOCK_REG_SELECTION_E;

typedef enum
{
    ADC_PHYS_CHANNEL_CONVERT = 0, ADC_SAMP_HOLD_CONVERT = 1, /* Only available on Physical channels 6,7 and 8 */
    ADC_EOC = 2, /* End of command signal is generated */
    ADC_SELECT_MASKLOCK_REG = 3, /* Select which MASKLOCK register set to use */
} ADC_VC_MODE_E;

typedef enum
{
    ADC_NOT_USED = 0x00,
    ADC_EOC_VC0 = 0x10,
    ADC_EOC_VC1 = 0x11,
    ADC_EOC_VC2 = 0x12,
    ADC_EOC_VC3 = 0x13,
    ADC_EOC_VC4 = 0x14,
    ADC_EOC_VC5 = 0x15,
    ADC_EOC_VC6 = 0x16,
    ADC_EOC_VC7 = 0x17,
    ADC_EOC_VC8 = 0x18,
    ADC_EOC_VC9 = 0x19,
    ADC_EOC_VC10 = 0x1a,
    ADC_EOC_VC11 = 0x1b,
    ADC_EOC_VC12 = 0x1c,
    ADC_EOC_VC13 = 0x1d,
    ADC_EOC_VC14 = 0x1e,
    ADC_EOC_VC15 = 0x1f,
} ADC_VC_TRIG_SEL_E;

typedef enum
{
    ADC_TRIG_DISABLE = 0, ADC_TRIG_ENABLE = 1,
} ADC_VC_TRIG_E;

typedef enum
{
    ADC_SINGLE_CONVERSION = 0, ADC_CONTINUOUS_CONVERSION = 1,
} ADC_VC_RUN_MODE_E;

typedef enum
{
    ADC_VC_DMA_DISABLE = 0, ADC_VC_DMA0_ENABLE = 2, ADC_VC_DMA1_ENABLE = 3,
} ADC_VC_DMA_REQUEST_E;

/* ADC Virtual Channel Configuration */
typedef union
{
    uint32_t value;

    struct
    {
        unsigned long adc1_chan_sel :3;
        unsigned long adc2_chan_sel :3;
        unsigned long mode :2;
        unsigned long trig_select :5;
        unsigned long trig_enable :1;
        unsigned long run_mode :1;
        unsigned long adc_module :2;
        unsigned long dma_request :2;
    };
} ADC_VC_CONFIG_T;

typedef union
{
    uint16_t value;

    struct
    {
        unsigned long vc0 :1;
        unsigned long vc1 :1;
        unsigned long vc2 :1;
        unsigned long vc3 :1;
        unsigned long vc4 :1;
        unsigned long vc5 :1;
        unsigned long vc6 :1;
        unsigned long vc7 :1;
        unsigned long vc8 :1;
        unsigned long vc9 :1;
        unsigned long vc10 :1;
        unsigned long vc11 :1;
        unsigned long vc12 :1;
        unsigned long vc13 :1;
        unsigned long vc14 :1;
        unsigned long vc15 :1;
    };
} ADC_VC_T;

/* ADC Transfer mode */
typedef enum
{
    ADC_ACQ_MODE_BLOCKING = 0, /* Wait for conversion to complete */
    ADC_ACQ_MODE_CONTINUOUS, /* Same as blocking but if read at lower speed than that of the acquisition time then a value should always be instantaneously available*/
    ADC_ACQ_MODE_NON_BLOCKING, /* Invoke callback when acquisition has completed */
    ADC_ACQ_MODE_DMA, /* Same as non-blocking but data is written to or read from DMA channel */
} ADC_ACQ_MODE_E;

/* ADC Required Transfer Information */
typedef struct
{
    ADC_ACQ_MODE_E acq_mode; /* The mode of the acquisition */
    uint32_t * acq_buf; /* Where acquisition data is stored **if** using a blocking mode*/
} ADC_ACQ_CMD_T;

/* ADC Channel Transfer Completion Call-back Function Prototype for Non-Blocking mode*/
typedef void (*adc_chan_complete_callback_t)(uint8_t chan_num,
        uint32_t acq_value);

/* ADC DMA Completion Call-back Function Prototype */
typedef void (*adc_dma_complete_callback_t)(void);

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
ER_RET adc_init(void);
ER_RET adc_uninitialise(void);
ER_RET adc_channel_open(uint8_t chan_num, ADC_VC_CONFIG_T * ptr_config);
ER_RET adc_channel_close(uint8_t chan_num);
ER_RET adc_read(uint8_t chan_num, ADC_ACQ_CMD_T * ptr_acq_cmd);
ER_RET adc_read_group(ADC_VC_T chan_group, ADC_ACQ_CMD_T * ptr_acq_cmd);
ER_RET adc_set_channel_config(uint8_t chan_num,
        const ADC_VC_CONFIG_T * const ptr_config);
ER_RET adc_get_channel_config(uint8_t chan_num, ADC_VC_CONFIG_T * ptr_config);
ER_RET adc_set_channel_trigger(uint8_t chan_num, ADC_VC_TRIG_E trig_enable,
        ADC_VC_TRIG_SEL_E trig_select);
ER_RET adc_register_channel_callback(uint8_t chan_num,
        adc_chan_complete_callback_t chan_callback);
ER_RET adc_register_dma_callback(adc_dma_complete_callback_t dma_callback);
ER_RET adc_set_dma_mode(ADC_DMA_CONTROL_E dma_mode);
ER_RET adc_set_samplehold_mode(ADC_SAMP_HOLD_CONTROL_E samp_hold_mode);
ER_RET adc_get_all_chan_busy_state(ADC_VC_T * ptr_vc_bits);
#endif /* R_ADC_RZN1_H__ */
