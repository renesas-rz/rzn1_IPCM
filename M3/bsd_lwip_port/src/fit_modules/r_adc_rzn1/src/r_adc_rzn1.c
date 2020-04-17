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
 * PROJECT NAME :   RZ/N1 bare metal Drivers, Sample application
 * FILE         :   r_adc_rzn1.c
 * Description  :   ADC driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "platform.h"
#include "r_adc_rzn1_config.h"
#include "r_adc_rzn1.h"
#include "iodefine.h"
#include "r_sysctrl_rzn1_if.h"
#include "mcu_interrupts_if.h"
#include "timer.h"

#ifdef r_dma_rzn1_if_included
#include "r_dma_rzn1_if.h"
#endif

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define ADC_ALL_CHANNELS_MASK                   (0x0000FFFFu)
#define ADC_DATA_UPDATE_PRESENT_MASK            (0x80000000u)
#define ADC_VC_ENABLE_MASK                      (0x00018000u)
#define ADC_ALL_HIGH_PRIORITY                   (0x10u)

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static bool m_adc_ready;
static volatile ADC_Type * m_adc_registers;
static adc_chan_complete_callback_t m_adc_chan_callback[ADC_MAX_LOGICAL_CHANNELS];
static adc_dma_complete_callback_t m_dma_callback;

/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           adc_handle_interrupt
 *
 *  Return value:       none
 *
 *  Parameters:         IRQn_Type Interrupt Type
 *
 *  Description:        handle ADC interrupt
 *
 **********************************************************************************************************************/
static void adc_handle_interrupt (IRQn_Type *irq_num_ptr)
{
    uint32_t irq_num = *irq_num_ptr;
    ADC_VC_T chan_interrupt_group;
    uint8_t chan_num;
    uint32_t chan_data;

    /* Report channels that have been interrupted on */
    chan_interrupt_group.value = m_adc_registers->rADC_INTSTATUS1.BIT.bADC_INTSTATUS1_VC;

    if (RZN1_IRQ_ADC == irq_num)
    {
        /* Setup pointer to data registers */
        volatile uint32_t * ptr_data_registers = (uint32_t *) &m_adc_registers->rADC1_DATA0;

        /* Multiple channel interrupts could have occurred together so need to check through all virtual channels */
        for (chan_num = ADC_VC0; chan_num <= ADC_VC15; chan_num++)
        {
            uint16_t vc_bit = ADC_CHAN_NUM_TO_BIT_MASK(chan_num);

            /* Check if current channel is part of the group */
            if (chan_interrupt_group.value & vc_bit)
            {
                /* Sanity check that there is new data waiting */
                if (ADC_DATA_UPDATE_PRESENT_MASK & ptr_data_registers[chan_num])
                {
                    /* store data in channel location in given buffer */
                    chan_data = (ptr_data_registers[chan_num] & ADC_DATA_MASK);
                }
                else
                {
                    /* Flag that an unexpected error has occurred while retrieving the data - but continue the process */
                    chan_data = -1;
                }

                /* Check callback should be called for current channel*/
                if (FIT_NO_PTR != m_adc_chan_callback[chan_num])
                {
                    /* Trigger channel callback */
                    m_adc_chan_callback[chan_num](chan_num, chan_data);
                }
            }
        }
    }
    else
    {
        /* Error Case */
        while (1);
    }

    /* Clear interrupts flags of channels that caused interrupt */
    m_adc_registers->rADC_INTCLR.BIT.bADC_INTCLR_VC = chan_interrupt_group.value;
    m_adc_registers->rADC_INTCLROVF.BIT.bADC_INTCLROVF_VC = chan_interrupt_group.value;
}
/***********************************************************************************************************************
 End of function adc_handle_interrupt
 **********************************************************************************************************************/

#ifdef r_dma_rzn1_if_included
/***********************************************************************************************************************
 *
 *  Function:       adc_dmac_callback
 *
 *  Return value:   None.
 *
 *  Parameters:     DMAC_number - The DMA Controller number
 *                  channel - Channel number of the DMAC
 *
 *  Description:    Call back funtion for DMA interrupts.
 *
 **********************************************************************************************************************/
static void adc_dmac_callback (uint8_t DMAC_number, uint8_t dma_channel)
{
    if (FIT_NO_PTR != m_dma_callback)
    {
        /* Call client callback */
        m_dma_callback();
    }
}
/***********************************************************************************************************************
 End of function adc_dmac_callback
 **********************************************************************************************************************/
#endif

/***********************************************************************************************************************
 *
 *  Function:       adc_allocate_dma_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *
 *  Description:    Assigns a specified DMA channel to the ADC
 *
 **********************************************************************************************************************/
static ER_RET adc_allocate_dma_chan (void)
{
    ER_RET ret_val = ER_OK;
#ifdef r_dma_rzn1_if_included
    DMA_CHAN_CTRL dma_chan_ctrl = DMA_DEFAULT_CHAN_CTRL;

    /* Attempt to Open DMA channel */
    ret_val = R_DMA_Open(DMAC_2, ADC_DMA_CHAN);
    if (ER_OK == ret_val)
    {
        /* Set up DMA channel control */
        dma_chan_ctrl.SRC_HS.HS_INTERFACE = (DMA_ADC_DMA_Request_0_REQ >> DMA_MUX_SRC_REQ_BIT) & DMA_MUX_SRC_REQ_MASK;
        ret_val = R_DMA_Control(DMAC_2, ADC_DMA_CHAN, DMA_CONTROL_SET_CHAN_CONFIG, &dma_chan_ctrl);
        if (ER_OK == ret_val)
        {
            /* Register callback */
            ret_val = R_DMA_Control(DMAC_2, ADC_DMA_CHAN, DMA_CONTROL_SET_CALL_BACK, (void *) &adc_dmac_callback);
        }
    }
#else /* Not ifdef r_dma_rzn1_if_included */
    /* No DMA driver therefore cannot use DMA operations */
    ret_val = ER_INVAL;
#endif
    return ret_val;
}
/***********************************************************************************************************************
 End of function adc_allocate_dma_chan
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       adc_release_dma_chan
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *
 *  Description:    Unassigns the DMA channel from the ADC
 *
 **********************************************************************************************************************/
static ER_RET adc_release_dma_chan (void)
{
    ER_RET ret_val = ER_OK;
#ifdef r_dma_rzn1_if_included
    /* Close the DMA channel */
    ret_val = R_DMA_Close(DMAC_2, ADC_DMA_CHAN);
#else /* Not ifdef r_dma_rzn1_if_included */
    /* No DMA driver therefore cannot use DMA operations */
    ret_val = ER_INVAL;
#endif
    return ret_val;
}
/***********************************************************************************************************************
 End of function adc_release_dma_chan
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       adc_init
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Initialises the ADC driver
 *
 **********************************************************************************************************************/
ER_RET adc_init (void)
{
    ER_RET ret_val = ER_OK;

    if (m_adc_ready)
    {
        return ER_INVAL;
    }

    /* Get pointer to register set */
    m_adc_registers = (volatile ADC_Type *) (RZN1_ADC_BASE);

    /* Configure clock divider for master and slave ADC */
    ret_val = R_SYSCTRL_SetADCClkDivider(ADC_CLOCK_DIVIDER);
    if (MCU_INT_SUCCESS == ret_val)
    {
        ret_val = R_SYSCTRL_EnableADC();
    }

    if (ER_OK == ret_val)
    {
        ADC_VIRT_CHAN_E chan_num;

        for (chan_num = ADC_VC0; chan_num <= ADC_VC15; chan_num++)
        {
            m_adc_chan_callback[chan_num] = FIT_NO_PTR;
        }

        m_adc_registers->rADC_CONFIG.BIT.bADC_DMA = ADC_DMA_DISABLE;
        m_adc_registers->rADC_CONFIG.BIT.bADC_SAMPLE_HOLD_ENABLE = 0;
        m_adc_registers->rADC_CONFIG.BIT.bADC_POWER_DOWN = ADC_OPERATIONAL_MODE;
        m_adc_registers->rADC_INTCLR.BIT.bADC_INTCLR_VC = ADC_ALL_CHANNELS_MASK;
        m_adc_registers->rADC_INTCLROVF.BIT.bADC_INTCLROVF_VC = ADC_ALL_CHANNELS_MASK;
        m_adc_registers->rADC_INTMASK.BIT.bADC_INTMASK_VC = 0;
        /* Set all virtual channels to have same priority */
        m_adc_registers->rADC_PRIORITY.BIT.bADC_Priority = ADC_ALL_HIGH_PRIORITY;
        /* Configure optimum sampling timing for ADC PCLK speed */
        m_adc_registers->rADC_ACQS.LONG = ADC_SAMP_HOLD_TIMING_REGISTER_10MHZ;

        m_adc_registers->rADC_MASKLOCK0.BIT.bADC_MASKLOCK = ADC_ALL_CHANNELS_MASK;
        m_adc_registers->rADC_MASKLOCK1.BIT.bADC_MASKLOCK = ADC_ALL_CHANNELS_MASK;
        m_adc_registers->rADC_MASKLOCK2.BIT.bADC_MASKLOCK = ADC_ALL_CHANNELS_MASK;
        m_adc_registers->rADC_MASKLOCK3.BIT.bADC_MASKLOCK = ADC_ALL_CHANNELS_MASK;

        /* Set interrupt priority for ADC & disable ADC interrupts */
        if (R_BSP_InterruptRegisterCallback((IRQn_Type) RZN1_IRQ_ADC, (bsp_int_cb_t) &adc_handle_interrupt)
                == MCU_INT_SUCCESS)
        {
            uint32_t int_priority = ADC_DEFAULT_INT_PRIORITY;

            ret_val = R_BSP_InterruptControl(RZN1_IRQ_ADC, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
            if (MCU_INT_SUCCESS != ret_val)
            {
                ret_val = ER_SYS;
            }
            else
            {
                ret_val = R_BSP_InterruptControl(RZN1_IRQ_ADC, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
            }
        }
        else
        {
            ret_val = ER_SYS;
        }
    }

    if (ER_OK == ret_val)
    {
        m_adc_ready = true;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function adc_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       adc_uninitialise
 *
 *  Return value:   Error Status
 *
 *  Parameters:     void
 *
 *  Description:    Uninitialises ADC peripheral.
 *
 **********************************************************************************************************************/
ER_RET adc_uninitialise (void)
{
    ER_RET ret_val = ER_OK;

    if ( !m_adc_ready)
    {
        return ER_INVAL;
    }

    m_adc_registers->rADC_CONFIG.BIT.bADC_DMA = ADC_DMA_DISABLE;
    m_adc_registers->rADC_CONFIG.BIT.bADC_SAMPLE_HOLD_ENABLE = 0;
    m_adc_registers->rADC_CONFIG.BIT.bADC_POWER_DOWN = ADC_POWER_DOWN_MODE;
    m_adc_registers->rADC_INTCLR.BIT.bADC_INTCLR_VC = 0;
    m_adc_registers->rADC_INTCLROVF.BIT.bADC_INTCLROVF_VC = 0;
    m_adc_registers->rADC_INTMASK.BIT.bADC_INTMASK_VC = 0;

    R_SYSCTRL_DisableADC();
    m_adc_ready = false;

    /* Clear register pointer */
    m_adc_registers = FIT_NO_PTR;

    /* Disable ADC interrupt*/
    ret_val = R_BSP_InterruptControl(RZN1_IRQ_ADC, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);

    return ret_val;
}
/***********************************************************************************************************************
 End of function adc_uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       adc_channel_open
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The ADC channel number
 *                  ptr_config - pointer to configuration data
 *
 *  Description:    Opens an ADC channel
 *
 **********************************************************************************************************************/
ER_RET adc_channel_open (uint8_t chan_num, ADC_VC_CONFIG_T * ptr_config)
{
    ER_RET ret_val = ER_OK;

    if ( !m_adc_ready)
    {
        return ER_INVAL;
    }

    ret_val = adc_set_channel_config(chan_num, ptr_config);

    return ret_val;
}
/***********************************************************************************************************************
 End of function adc_channel_open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       adc_channel_close
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The ADC channel number
 *
 *  Description:    Opens an ADC channel
 *
 **********************************************************************************************************************/
ER_RET adc_channel_close (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    uint16_t chan_mask = ADC_CHAN_NUM_TO_BIT_MASK(chan_num);
    static const ADC_VC_CONFIG_T adc_config = {.value=0};

    if ( !m_adc_ready)
    {
        return ER_INVAL;
    }

    /* Clear Channel Bits */
    m_adc_registers->rADC_CLRFORCE.BIT.bADC_CLRFORCE_VC = chan_mask;
    m_adc_registers->rADC_INTCLR.BIT.bADC_INTCLR_VC = chan_mask;
    m_adc_registers->rADC_INTCLROVF.BIT.bADC_INTCLROVF_VC = chan_mask;
    m_adc_registers->rADC_INTOVFMASK.BIT.bADC_INTOVFMASK_VC &= (uint32_t)( ~chan_mask);
    m_adc_registers->rADC_PENDINGCLROVF.BIT.bADC_PENDINGCLROVF_VC = chan_mask;

    /* Disable ADC Modules via clearing setup register */
    ret_val = adc_set_channel_config(chan_num, &adc_config);
    ret_val |= adc_register_channel_callback(chan_num, FIT_NO_PTR);

    return ret_val;
}
/***********************************************************************************************************************
 End of function adc_channel_close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       adc_read
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The ADC channel number
 *                  ptr_acq_cmd - Acquisition command
 *
 *  Description:    Initiates the requested ADC read.
 *
 **********************************************************************************************************************/
ER_RET adc_read (uint8_t chan_num, ADC_ACQ_CMD_T * ptr_acq_cmd)
{
    ER_RET ret_val = ER_OK;
    uint16_t chan_mask = ADC_CHAN_NUM_TO_BIT_MASK(chan_num);
    volatile uint32_t * ptr_data_registers;

    if ( !m_adc_ready)
    {
        return ER_INVAL;
    }

    if (ADC_ACQ_MODE_BLOCKING == ptr_acq_cmd->acq_mode)
    {
#if ADC_CFG_PARAM_CHECKING_ENABLE
        if (FIT_NO_PTR == ptr_acq_cmd->acq_buf)
        {
            return ER_PARAM;
        }

        if (m_adc_registers->rADC_FORCE.BIT.bADC_FORCE_VC & chan_mask)
        {
            /* Channel acquisition is already in progress via another request so exit */
            return ER_BUSY;
        }
#endif
        /* Ensure Acquisition Starts */
        m_adc_registers->rADC_SETFORCE.BIT.bADC_SETFORCE_VC |= (uint32_t) chan_mask;
        /* Wait until selected channel are converted. */
        while (m_adc_registers->rADC_FORCE.BIT.bADC_FORCE_VC & chan_mask);

        ptr_data_registers = (uint32_t *) &m_adc_registers->rADC1_DATA0;
        if (ADC_DATA_UPDATE_PRESENT_MASK & ptr_data_registers[chan_num])
        {
            ptr_acq_cmd->acq_buf[0] = (ptr_data_registers[chan_num] & ADC_DATA_MASK);
        }
        else
        {
            /* Conversion has not completed correctly */
            return ER_NG;
        }
    }
    else if (ADC_ACQ_MODE_CONTINUOUS == ptr_acq_cmd->acq_mode)
    {
#if ADC_CFG_PARAM_CHECKING_ENABLE
        if (FIT_NO_PTR == ptr_acq_cmd->acq_buf)
        {
            return ER_PARAM;
        }
#endif
        /* Check that all selected channels are ready to read data */
        if ((m_adc_registers->rADC_INTSTATUS0.BIT.bADC_INTSTATUS0_VC & chan_mask) != chan_mask)
        {
            return ER_NOTYET;
        }

        m_adc_registers->rADC_INTCLR.BIT.bADC_INTCLR_VC = chan_mask;
        m_adc_registers->rADC_INTCLROVF.BIT.bADC_INTCLROVF_VC = chan_mask;

        ptr_data_registers = (uint32_t *) &m_adc_registers->rADC1_DATA0;
        if (ADC_DATA_UPDATE_PRESENT_MASK & ptr_data_registers[chan_num])
        {
            ptr_acq_cmd->acq_buf[0] = (ptr_data_registers[chan_num] & ADC_DATA_MASK);
        }
        else
        {
            /* Conversion has not completed correctly */
            return ER_NG;
        }
    }
    else if (ADC_ACQ_MODE_NON_BLOCKING == ptr_acq_cmd->acq_mode)
    {
        if (m_adc_registers->rADC_FORCE.BIT.bADC_FORCE_VC & chan_mask)
        {
            /* Channel acquisition is already in progress on the selected channel so exit */
            return ER_BUSY;
        }

        /* Set Channel Interrupt */
        m_adc_registers->rADC_INTCLR.BIT.bADC_INTCLR_VC |= (uint32_t) chan_mask;
        m_adc_registers->rADC_SETFORCE.BIT.bADC_SETFORCE_VC = chan_mask;
        ret_val = ER_OK;
    }
    else if (ADC_ACQ_MODE_DMA == ptr_acq_cmd->acq_mode)
    {
#ifdef r_dma_rzn1_if_included
        if (m_adc_registers->rADC_FORCE.BIT.bADC_FORCE_VC & chan_mask)
        {
            /* Channel acquisition is already in progress so exit */
            return ER_BUSY;
        }

        if (ADC_DMA_DISABLE == m_adc_registers->rADC_CONFIG.BIT.bADC_DMA)
        {
            /* Global DMA mode is not setup */
            return ER_INVAL;
        }

        if (FIT_NO_PTR == ptr_acq_cmd->acq_buf)
        {
            /* DMA mode needs a buffer */
            return ER_PARAM;
        }

        DMA_TRANS_CTRL transfer = DMA_DEFAULT_TRANS_CTRL; /* Initialise transfer */

        transfer.INT_EN = true;
        transfer.TR_FLOW = PTM_DMAC;
        transfer.SRC = (uint32_t)(( &m_adc_registers->rADC1_DATALOCK0) + chan_num); /* Use channel number and pointer arithmetic to pick out correct data lock register to use */
        transfer.DST = (uint32_t) ptr_acq_cmd->acq_buf;
        transfer.SRC_INCR = INCREMENT;
        transfer.DST_INCR = INCREMENT;
        transfer.SRC_TR_WIDTH = BITS32;
        transfer.DST_TR_WIDTH = BITS32;
        transfer.SRC_BRST_LEN = DATA_ITEMS_1;
        transfer.DST_BRST_LEN = DATA_ITEMS_1;
        transfer.BLOCK_SIZE = 1; /* Copy Single channel register */

        ret_val = R_DMA_Control(DMAC_2, ADC_DMA_CHAN, DMA_CONTROL_SET_TRANS_CONFIG, &transfer); /* Set transfer configuration */
        if (ER_OK == ret_val)
        {
            m_adc_registers->rADC_INTCLR.BIT.bADC_INTCLR_VC |= (uint32_t) chan_mask;
            m_adc_registers->rADC_SETFORCE.BIT.bADC_SETFORCE_VC = (uint32_t) chan_mask;
            /* Request the DMA Transfer */
            ret_val = R_DMA_Write(DMAC_2, ADC_DMA_CHAN, DMA_TRANSFER);
        }
#else
        return ER_INVAL;
#endif
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function adc_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       adc_read_group
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_group - The ADC channels to acquire
 *                  ptr_acq_cmd - Acquisition command
 *
 *  Description:    Initiates the requested ADC read.
 *
 **********************************************************************************************************************/
ER_RET adc_read_group (ADC_VC_T chan_group, ADC_ACQ_CMD_T * ptr_acq_cmd)
{
    ER_RET ret_val = ER_OK;
    uint8_t chan_num;
    volatile uint32_t * ptr_data_registers;

    if ( !m_adc_ready)
    {
        return ER_INVAL;
    }

    if (ADC_ACQ_MODE_BLOCKING == ptr_acq_cmd->acq_mode)
    {
#if ADC_CFG_PARAM_CHECKING_ENABLE
        if (FIT_NO_PTR == ptr_acq_cmd->acq_buf)
        {
            return ER_PARAM;
        }

        if (m_adc_registers->rADC_FORCE.BIT.bADC_FORCE_VC & chan_group.value)
        {
            /* Channel acquisition is already in progress in at least one of the selected channels so exit */
            return ER_BUSY;
        }
#endif
        /* Ensure Acquisition Starts */
        m_adc_registers->rADC_SETFORCE.BIT.bADC_SETFORCE_VC |= (uint32_t) chan_group.value;
        /* Wait until selected channels are converted. */
        while (m_adc_registers->rADC_FORCE.BIT.bADC_FORCE_VC & chan_group.value);

        /* Setup pointer to data registers */
        ptr_data_registers = (uint32_t *) &m_adc_registers->rADC1_DATA0;

        for (chan_num = ADC_VC0; chan_num <= ADC_VC15; chan_num++)
        {
            uint16_t vc_bit = ADC_CHAN_NUM_TO_BIT_MASK(chan_num);

            /* Check if current channel is part of the group */
            if (chan_group.value & vc_bit)
            {
                /* Sanity check that there is new data waiting */
                if (ADC_DATA_UPDATE_PRESENT_MASK & ptr_data_registers[chan_num])
                {
                    /* store data in channel location in given buffer */
                    ptr_acq_cmd->acq_buf[chan_num] = (ptr_data_registers[chan_num] & ADC_DATA_MASK);
                }
                else
                {
                    /* Flag that an unexpected error has occurred while retrieving the data - but continue the process */
                    ret_val = ER_NG;
                }
            }
        }
    }
    else if (ADC_ACQ_MODE_CONTINUOUS == ptr_acq_cmd->acq_mode)
    {
#if ADC_CFG_PARAM_CHECKING_ENABLE
        if (FIT_NO_PTR == ptr_acq_cmd->acq_buf)
        {
            return ER_PARAM;
        }
#endif
        /* Check that all selected channels are ready to read data */
        if ((m_adc_registers->rADC_INTSTATUS0.BIT.bADC_INTSTATUS0_VC & chan_group.value) != chan_group.value)
        {
            return ER_NOTYET;
        }

        m_adc_registers->rADC_INTCLR.BIT.bADC_INTCLR_VC = chan_group.value;
        m_adc_registers->rADC_INTCLROVF.BIT.bADC_INTCLROVF_VC = chan_group.value;

        /* Setup pointer to data registers */
        ptr_data_registers = (uint32_t *) &m_adc_registers->rADC1_DATA0;
        for (chan_num = ADC_VC0; chan_num <= ADC_VC15; chan_num++)
        {
            uint16_t vc_bit = ADC_CHAN_NUM_TO_BIT_MASK(chan_num);

            /* Check if current channel is part of the group */
            if (chan_group.value & vc_bit)
            {
                /* Sanity check that there is new data waiting */
                if (ADC_DATA_UPDATE_PRESENT_MASK & ptr_data_registers[chan_num])
                {
                    /* store data in channel location in given buffer */
                    ptr_acq_cmd->acq_buf[chan_num] = (ptr_data_registers[chan_num] & ADC_DATA_MASK);
                }
                else
                {
                    /* Flag that an unexpected error has occurred while retrieving the data - but continue the process */
                    ret_val = ER_NG;
                }
            }
        }
    }
    else if (ADC_ACQ_MODE_NON_BLOCKING == ptr_acq_cmd->acq_mode)
    {
        if (m_adc_registers->rADC_FORCE.BIT.bADC_FORCE_VC & chan_group.value)
        {
            /* Channel acquisition is already in progress in at least one of the selected channels so exit */
            return ER_BUSY;
        }

        m_adc_registers->rADC_INTCLR.BIT.bADC_INTCLR_VC |= (uint32_t) chan_group.value;
        m_adc_registers->rADC_SETFORCE.BIT.bADC_SETFORCE_VC = chan_group.value;
        ret_val = ER_OK;
    }
    else if (ADC_ACQ_MODE_DMA == ptr_acq_cmd->acq_mode)
    {
#ifdef r_dma_rzn1_if_included
        if (m_adc_registers->rADC_FORCE.BIT.bADC_FORCE_VC & chan_group.value)
        {
            /* Channel acquisition is already in progress in at least one of the selected channels so exit */
            return ER_BUSY;
        }

        if (ADC_DMA_DISABLE == m_adc_registers->rADC_CONFIG.BIT.bADC_DMA)
        {
            /* Global DMA mode is not setup */
            return ER_INVAL;
        }

        if (FIT_NO_PTR == ptr_acq_cmd->acq_buf)
        {
            /* DMA mode needs a buffer */
            return ER_PARAM;
        }

        DMA_TRANS_CTRL transfer = DMA_DEFAULT_TRANS_CTRL; /* Initialise transfer */

        transfer.INT_EN = true;
        transfer.TR_FLOW = PTM_DMAC;
        transfer.SRC = (uint32_t) & m_adc_registers->rADC1_DATALOCK0;
        transfer.DST = (uint32_t) ptr_acq_cmd->acq_buf;
        transfer.SRC_INCR = INCREMENT;
        transfer.DST_INCR = INCREMENT;
        transfer.SRC_TR_WIDTH = BITS32;
        transfer.DST_TR_WIDTH = BITS32;
        transfer.SRC_BRST_LEN = DATA_ITEMS_1;
        transfer.DST_BRST_LEN = DATA_ITEMS_1;
        transfer.BLOCK_SIZE = ADC_MAX_LOGICAL_CHANNELS; /*NOTE: Always copy all channels as DMA will not cherry pick data for a non-contiguous channel group */

        ret_val = R_DMA_Control(DMAC_2, ADC_DMA_CHAN, DMA_CONTROL_SET_TRANS_CONFIG, &transfer); /* Set transfer configuration */
        if (ER_OK == ret_val)
        {
            m_adc_registers->rADC_INTCLR.BIT.bADC_INTCLR_VC |= (uint32_t) chan_group.value;
            m_adc_registers->rADC_SETFORCE.BIT.bADC_SETFORCE_VC = chan_group.value;
            /* Request the DMA Transfer */
            ret_val = R_DMA_Write(DMAC_2, ADC_DMA_CHAN, DMA_TRANSFER);
        }
#else
        return ER_INVAL;
#endif
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function adc_read_group
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       adc_set_channel_config
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The ADC channel number
 *                  ptr_config - pointer to config information
 *
 *  Description:    Sets up the selected virtual channel
 *
 **********************************************************************************************************************/
ER_RET adc_set_channel_config (uint8_t chan_num, const ADC_VC_CONFIG_T * const ptr_config)
{
    ER_RET ret_val = ER_OK;

    if ( !m_adc_ready)
    {
        return ER_INVAL;
    }

#if ADC_CFG_PARAM_CHECKING_ENABLE

#ifndef ADC_CFG_ADC_2_ENABLE
    if (ADC_2 & ptr_config->adc_module)
    {
        /* ADC_2 is not supported */
        ret_val = ER_PARAM;
    }
#endif

    if (ADC_VC_DMA1_ENABLE == ptr_config->dma_request)
    {
        /* Not currently supported in driver */
        return ER_PARAM;
    }

    if (ADC_SAMP_HOLD_CONVERT == ptr_config->mode)
    {
#ifdef ADC_CFG_ADC_2_ENABLE
        if (ADC_2 & ptr_config->adc_module)
        {
            /* Sample and hold mode only works for Physical Channels 6..8 */
            if (ADC_SH_CHAN_NONE == ptr_config->adc2_chan_sel)
            {
                ret_val = ER_PARAM;
            }
        }
#endif
        if (ADC_1 & ptr_config->adc_module)
        {
            /* Sample and hold mode only works for Physical Channels 6..8 */
            if (ADC_SH_CHAN_NONE == ptr_config->adc1_chan_sel)
            {
                ret_val = ER_PARAM;
            }
        }
    }
#endif /* ADC_CFG_PARAM_CHECKING_ENABLE */

    if (ER_OK == ret_val)
    {
        volatile uint32_t * ptr_control_registers = (uint32_t *) &m_adc_registers->rADC_VC0.LONG;

        ptr_control_registers[chan_num] = ptr_config->value;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function adc_set_channel_config
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       adc_get_channel_config
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The ADC channel number
 *                  ptr_config - pointer to config information
 *
 *  Description:    Gets the selected virtual channel configuration
 *
 **********************************************************************************************************************/
ER_RET adc_get_channel_config (uint8_t chan_num, ADC_VC_CONFIG_T * ptr_config)
{
    ER_RET ret_val = ER_OK;
    volatile uint32_t * ptr_control_registers;

    if ( !m_adc_ready)
    {
        return ER_INVAL;
    }

    ptr_control_registers = (uint32_t *) &m_adc_registers->rADC_VC0.LONG;
    ptr_config->value = ptr_control_registers[chan_num];

    return ret_val;
}
/***********************************************************************************************************************
 End of function adc_get_channel_config
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       adc_set_channel_trigger
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The ADC channel number
 *                  trig_enable - enable/disable state of channel trigger
 *                  trig_select - VC to trigger from if trigger is enabled
 *
 *  Description:    Sets the selected virtual channel trigger configuration
 *
 **********************************************************************************************************************/
ER_RET adc_set_channel_trigger (uint8_t chan_num, ADC_VC_TRIG_E trig_enable, ADC_VC_TRIG_SEL_E trig_select)
{
    volatile ADC_VC_CONFIG_T * ptr_control_registers;

    if ( !m_adc_ready)
    {
        return ER_INVAL;
    }

    ptr_control_registers = (ADC_VC_CONFIG_T *) &m_adc_registers->rADC_VC0.LONG;
    ptr_control_registers[chan_num].trig_enable = trig_enable;
    ptr_control_registers[chan_num].trig_select = trig_select;

    if ((ADC_NOT_USED == trig_select) && (ADC_TRIG_ENABLE == trig_enable))
    {
        /* If trigger has been enabled but no trigger has been specified then
         assume the client code wants to force the trigger of the channel
         */
        m_adc_registers->rADC_SETFORCE.BIT.bADC_SETFORCE_VC = ADC_CHAN_NUM_TO_BIT_MASK(chan_num);
    }

    return ER_OK;
}
/***********************************************************************************************************************
 End of function adc_set_channel_trigger
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           adc_register_channel_callback
 *
 *  Return value:       Error status
 *
 *  Parameters:         chan_callback -the channel callback to register.
 *                       Note: if FIT_NO_PTR is supplied then this de-registers
 *                       any existing callback and turns of the associated interrupt
 *
 *  Description:        Registers a channel callback
 *
 **********************************************************************************************************************/
ER_RET adc_register_channel_callback (uint8_t chan_num, adc_chan_complete_callback_t chan_callback)
{
    ER_RET ret_val = ER_OK;
    uint16_t chan_mask = ADC_CHAN_NUM_TO_BIT_MASK(chan_num);

    /* Always Disable interrupt as needs disabling if either new interrupt settings or supplying NULL pointer for a callback */
    ret_val = R_BSP_InterruptControl(RZN1_IRQ_ADC, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
    if (ER_OK != ret_val)
    {
        return ret_val;
    }

    if (FIT_NO_PTR == chan_callback)
    {
        /* Clear Channel Interrupt */
        m_adc_registers->rADC_INTMASK.BIT.bADC_INTMASK_VC &= (uint32_t)( ~chan_mask);
        /* No callback supplied so remove any existing callback */
        m_adc_chan_callback[chan_num] = FIT_NO_PTR;
    }
    else
    {
        /* callback supplied so register it */
        m_adc_chan_callback[chan_num] = chan_callback;
        ret_val = R_BSP_InterruptControl(RZN1_IRQ_ADC, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR); /* Make sure interrupt is enabled */
        m_adc_registers->rADC_INTMASK.BIT.bADC_INTMASK_VC |= (uint32_t) chan_mask;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function adc_register_channel_callback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           adc_register_dma_callback
 *
 *  Return value:       Error status
 *
 *  Parameters:         callback -the callback to register. Note: if FIT_NO_PTR
 *                      is supplied then this de-registers any existing callback
 *
 *  Description:        Registers the DMA callback
 *
 **********************************************************************************************************************/
ER_RET adc_register_dma_callback (adc_dma_complete_callback_t dma_callback)
{
    /* Set callback. Value can be FIT_NO_PTR */
    m_dma_callback = dma_callback;
    return ER_OK;
}
/***********************************************************************************************************************
 End of function adc_register_dma_callback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           adc_set_dma_mode
 *
 *  Return value:       Error status
 *
 *  Parameters:         dma_mode -set DMA capability
 *
 *  Description:        Configures Global mode for DMA capability
 *
 **********************************************************************************************************************/
ER_RET adc_set_dma_mode (ADC_DMA_CONTROL_E dma_mode)
{
    ER_RET ret_val = ER_OK;

    if (ADC_DMA_DISABLE == dma_mode)
    {
        /* Release DMA resources */
        ret_val = adc_release_dma_chan();
    }
    else
    {
        /* Allocate DMA Resources */
        ret_val = adc_allocate_dma_chan();
    }

    if (ER_OK == ret_val)
    {
        m_adc_registers->rADC_CONFIG.BIT.bADC_DMA = dma_mode;
    }

    return ER_OK;
}
/***********************************************************************************************************************
 End of function adc_set_dma_mode
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           adc_set_samplehold_mode
 *
 *  Return value:       Error status
 *
 *  Parameters:         samp_hold_mode -set Sample & Hold capability
 *
 *  Description:        Configures Global mode for Sample & Hold capability
 *
 **********************************************************************************************************************/
ER_RET adc_set_samplehold_mode (ADC_SAMP_HOLD_CONTROL_E samp_hold_mode)
{
    m_adc_registers->rADC_CONFIG.BIT.bADC_SAMPLE_HOLD_ENABLE = samp_hold_mode;
    /* Wait for busy state to complete */
    while (m_adc_registers->rADC_CONTROL.BIT.bADC_BUSY);
    return ER_OK;
}
/***********************************************************************************************************************
 End of function adc_set_samplehold_mode
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           adc_get_all_chan_busy_state
 *
 *  Return value:       Error status
 *
 *  Parameters:         ptr_vc_bits -buffer for all channel busy status
 *
 *  Description:        Gets Busy Status for all Virtual Channels
 *
 **********************************************************************************************************************/
ER_RET adc_get_all_chan_busy_state (ADC_VC_T * ptr_vc_bits)
{
    ptr_vc_bits->value = (uint16_t) m_adc_registers->rADC_FORCE.BIT.bADC_FORCE_VC;
    return ER_OK;
}
/***********************************************************************************************************************
 End of function adc_get_all_chan_busy_state
 **********************************************************************************************************************/
