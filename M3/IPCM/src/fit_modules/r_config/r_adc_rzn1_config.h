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
 * $Revision: 1299 $
 * $Date: 2019-02-25 12:05:48 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_adc_rzn1_config.h
 * Description  :  Configures the ADC module.
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef ADC_RZN1_CONFIG_HEADER_FILE
#define ADC_RZN1_CONFIG_HEADER_FILE

/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/
/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING
 Available settings:
 BSP_CFG_PARAM_CHECKING_ENABLE:
 Utilizes the system default setting
 1:
 Includes parameter checking
 0:
 Compiles out parameter checking
 */

/* Define the below to allow DMA */
#define r_dma_rzn1_if_included

#define ADC_CFG_PARAM_CHECKING_ENABLE           (BSP_CFG_PARAM_CHECKING_ENABLE)

//#define ADC_CFG_ADC_2_ENABLE                    /*ADC_2 is not currently supported (and only available on 400pin RZN1D */

#define ADC_DMA_CHAN                            (DMA_CHAN_3)

/* ADC divider value can be 50-250 */
#define ADC_CLOCK_DIVIDER                       (50)                            /* Will allow 10MHz operation @ 1GHz */
#define ADC_SAMP_HOLD_TIMING_REGISTER_10MHZ     (0x000001C6u)

#if defined(ADC_CFG_ADC_2_ENABLE) && defined(BSP_PLAT_RZN1DDB) && defined(CORE_CA7)
#define ADC_MAX_PHYSICAL_CHANNELS           (16u)
#else
#define ADC_MAX_PHYSICAL_CHANNELS           (8u)
#endif

#define ADC_DEFAULT_INT_PRIORITY                (9u)

#endif /* ADC_RZN1_CONFIG_HEADER_FILE */
