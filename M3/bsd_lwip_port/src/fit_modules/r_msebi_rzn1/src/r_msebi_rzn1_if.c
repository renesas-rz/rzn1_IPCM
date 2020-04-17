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
 * FILE         :  r_msebi_rzn1_if.c
 * Description  :  MSEBI driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "r_msebi_rzn1_if.h"
#include "r_msebi_rzn1_config.h"
#include "r_msebi_rzn1.h"

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static msebi_states_t MSEBIM_STATE;
static msebi_states_t MSEBIS_STATE;
static msebi_cs_states_t MSEBIM_CS_STATE[MSEBI_MAX_CS];
static msebi_cs_states_t MSEBIS_CS_STATE[MSEBI_MAX_CS];
/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
extern const msebi_cyclesize_t default_msebi_cyclesize_cs =
{ .write_dle_data_nb = 255, .read_dle_data_nb = 255, .write_dle_data_b = 3, .read_dle_data_b = 3, .cle_data = true,
        .ale_data = true };

extern const msebi_setuphold_t default_msebi_setuphold_cs =
{ .write_dle_setup = 63, .read_dle_setup = 63, .m_write_dle_hold = 63, .m_read_dle_hold = 63 };

extern const msebim_config_t default_msebim_config =
{ .msebim_clk_low = 3, /* 4 MSEBIM_HCLK */
.msebim_clk_high = 3, /* 4 MSEBIM_HCLK */
.cpu_write_burst = MSEBIM_BURST_1_WORD, .cpu_read_burst = MSEBIM_BURST_1_WORD };

extern const msebis_config_t default_msebis_config =
{ .cpu_read_burst = MSEBIS_BURST_1_WORD, .cpu_write_burst = MSEBIS_BURST_1_WORD, .buffer_data = true, /* data is bufferable */
.cache_data = false, /* data is not cacheable */
.cfg_reg_timeout_delay_x4 = 4 /* 20 MSEBIB_HCLK */};

extern const msebim_config_cs_t default_msebim_config_cs =
{ .m_s_shared_config.trans_func = MSEBIM_16_ASY, .m_s_shared_config.wait_func = MSEBI_WAIT_CSN,
        .wait_management = false, .m_s_shared_config.burst_enable = false, .num_ale_used = 0,
        .parallel_ale_mode = false, .m_s_shared_config.addr_route_cs1 = false,
        .m_s_shared_config.addr_route_cs2 = false, .m_s_shared_config.addr_route_cs3 = false, .multi_dle = false,
        .extend_addr = 0 };

extern const msebis_config_cs_t default_msebis_config_cs =
{ .m_s_shared_config.trans_func = MSEBIS_16_SYN, .write_access = false, .m_s_shared_config.wait_func = MSEBI_WAIT_CSN,
        .m_s_shared_config.burst_enable = false, .mmu_addr_mode = false, .m_s_shared_config.addr_route_cs1 = false,
        .m_s_shared_config.addr_route_cs2 = false, .m_s_shared_config.addr_route_cs3 = false };

extern const msebim_dma_datalevel_cs_t default_msebim_dma_datalevel_cs =
{ .fifo_burst_size = MSEBIM_BURST_1_WORD, .fifo_data_level = 28, .use_ext_pin = false, };

extern const msebis_dma_datalevel_cs_t default_msebis_dma_datalevel_cs =
{ .burst_size_optimised = false, .flow_control = false, .fifo_burst_size = MSEBIS_BURST_1_WORD };

extern const msebim_dma_control_cs_t default_msebim_dma_control_cs =
{ .block_size = 0x0, .burst_size = MSEBIM_BURST_1_WORD, .enable_dma = false };

extern const msebim_dma_block_address_cs_t default_msebim_dma_block_address_cs =
{ .align_first_block_32bit = false, .address_dma_read = 0x0 };

/* Default slave DMA transmit and receive request settings */
extern const msebis_dma_request_cs_t default_msebis_dma_request_cs =
{ .enable = false, .force = true };

extern const msebis_interrupt_control_t default_msebis_interrupt_masks =
{ .eob_interrupt_dma_tx[0] = false, .eob_interrupt_dma_tx[1] = false,

.eob_interrupt_dma_rx[0] = false, .eob_interrupt_dma_rx[1] = false,

.eob_interrupt_cpu_tx[0] = false, .eob_interrupt_cpu_tx[1] = false, .eob_interrupt_cpu_tx[2] = false,
        .eob_interrupt_cpu_tx[3] = false,

        .eob_interrupt_cpu_rx[0] = false, .eob_interrupt_cpu_rx[1] = false, .eob_interrupt_cpu_rx[2] = false,
        .eob_interrupt_cpu_rx[3] = false

};

extern const msebis_interrupt_control_t default_msebis_interrupt_clear =
{ .eob_interrupt_dma_tx[0] = true, .eob_interrupt_dma_tx[1] = true,

.eob_interrupt_dma_rx[0] = true, .eob_interrupt_dma_rx[1] = true,

.eob_interrupt_cpu_tx[0] = true, .eob_interrupt_cpu_tx[1] = true, .eob_interrupt_cpu_tx[2] = true,
        .eob_interrupt_cpu_tx[3] = true,

        .eob_interrupt_cpu_rx[0] = true, .eob_interrupt_cpu_rx[1] = true, .eob_interrupt_cpu_rx[2] = true,
        .eob_interrupt_cpu_rx[3] = true

};

/***********************************************************************************************************************
 *
 *  Function:       R_MSEBI_GetVersion
 *
 *  Return value:   Driver number
 *
 *  Parameters:     None
 *  Description:    Returns the MSEBI driver version number
 *
 **********************************************************************************************************************/
void R_MSEBI_GetVersion (void *buf)
{
    /* These version macros are defined in r_msebi_rzn1_if.h. */
    ((uint8_t *) buf)[1] = (uint8_t)MSEBI_DRIVER_MAJOR_VERSION_NUMBER;
    ((uint8_t *) buf)[0] = (uint8_t)MSEBI_DRIVER_MINOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function R_MSEBI_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_MSEBI_Init
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *  Description:    Initialise MSEBI driver and chip select states
 *
 **********************************************************************************************************************/
void R_MSEBI_Init (void)
{
    uint32_t i;

    /* Initialise states */
    MSEBIM_STATE = MSEBI_STATE_CLOSED;
    MSEBIS_STATE = MSEBI_STATE_CLOSED;

    for (i = 0; i < MSEBI_MAX_CS; i++)
    {
        MSEBIM_CS_STATE[i] = MSEBI_CS_STATE_CLOSED;
        MSEBIS_CS_STATE[i] = MSEBI_CS_STATE_CLOSED;
    }

    /* Call driver init function */
    MSEBI_Init();

}
/***********************************************************************************************************************
 End of function R_MSEBI_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_MSEBI_Open
 *
 *  Return value:   Error status
 *
 *  Parameters:     mode - MSEBI master/slave mode
 *                  chip_sel - The desired chip select
 *
 *  Description:    Opens an MSEBI mode and/or chip select
 *
 **********************************************************************************************************************/
ER_RET R_MSEBI_Open (msebi_mode_t mode, uint8_t chip_sel)
{
    ER_RET ret_val = ER_OK;

    /* Check valid chip select */
    if ((chip_sel >= MSEBI_MAX_CS) && (MSEBI_NO_CS != chip_sel))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        switch (mode)
        {
            case MSEBIMASTER:
                if (MSEBI_NO_CS == chip_sel)
                {
                    if (MSEBI_STATE_OPEN == MSEBIM_STATE)
                    {
                        /* Attempting to open a master MSEBI that is already open */
                        ret_val = ER_INVAL;
                    }
                    else
                    {
                        /* Open MSEBIM */
                        if (ER_OK == (ret_val = MSEBI_Open(true)))
                        {
                            MSEBIM_STATE = MSEBI_STATE_OPEN;
                        }
                    }
                }
                else
                {
                    if (MSEBI_CS_STATE_OPEN == MSEBIM_CS_STATE[chip_sel])
                    {
                        /* Attempting to open a chip select that is already open */
                        ret_val = ER_INVAL;
                    }
                    else
                    {
                        /* Open MSEBIM */
                        if (MSEBI_STATE_CLOSED == MSEBIM_STATE)
                        {
                            if (ER_OK == (ret_val = MSEBI_Open(true)))
                            {
                                MSEBIM_STATE = MSEBI_STATE_OPEN;
                            }
                        }

                        /* Open the chip select */
                        if (ER_OK == ret_val)
                        {
                            MSEBIM_CS_STATE[chip_sel] = MSEBI_CS_STATE_OPEN;
                        }
                    }
                }
            break;
            case MSEBISLAVE:
                if (MSEBI_NO_CS == chip_sel)
                {
                    if (MSEBI_STATE_OPEN == MSEBIS_STATE)
                    {
                        /* Attempting to open a slave MSEBI that is already open */
                        ret_val = ER_INVAL;
                    }
                    else
                    {
                        /* Open MSEBIS */
                        if (ER_OK == (ret_val = MSEBI_Open(false)))
                        {
                            MSEBIS_STATE = MSEBI_STATE_OPEN;
                        }
                    }
                }
                else
                {
                    if (MSEBI_CS_STATE_OPEN == MSEBIS_CS_STATE[chip_sel])
                    {
                        /* Attempting to open a chip select that is already open */
                        ret_val = ER_INVAL;
                    }
                    else
                    {
                        /* Open MSEBIS */
                        if (MSEBI_STATE_CLOSED == MSEBIS_STATE)
                        {
                            if (ER_OK == (ret_val = MSEBI_Open(false)))
                            {
                                MSEBIS_STATE = MSEBI_STATE_OPEN;
                            }
                        }

                        /* Open the chip select */
                        if (ER_OK == ret_val)
                        {
                            MSEBIS_CS_STATE[chip_sel] = MSEBI_CS_STATE_OPEN;
                        }
                    }
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
 End of function R_MSEBI_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_MSEBI_Close
 *
 *  Return value:   Error status
 *
 *  Parameters:     mode - MSEBI master/slave mode
 *                  chip_sel - The desired chip select
 *
 *  Description:    Closes an MSEBI mode and/or chip select(s)
 *
 **********************************************************************************************************************/
ER_RET R_MSEBI_Close (msebi_mode_t mode, uint8_t chip_sel)
{
    ER_RET ret_val = ER_OK;
    uint32_t i;

    /* Check valid chip select and mode */
    if ((chip_sel >= MSEBI_MAX_CS) && (MSEBI_NO_CS != chip_sel))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        switch (mode)
        {
            case MSEBIMASTER:
                if (MSEBI_NO_CS == chip_sel)
                {
                    /* Close MSEBIM and all CS */
                    MSEBI_Close(true);
                    MSEBIM_STATE = MSEBI_STATE_CLOSED;
                    for (i = 0; i < MSEBI_MAX_CS; i++)
                    {
                        MSEBIM_CS_STATE[i] = MSEBI_CS_STATE_CLOSED;
                    }
                }
                else
                {
                    /* Close desired CS */
                    MSEBIM_CS_STATE[chip_sel] = MSEBI_CS_STATE_CLOSED;
                }
            break;
            case MSEBISLAVE:
                if (MSEBI_NO_CS == chip_sel)
                {
                    /* Close MSEBIS and all CS */
                    MSEBI_Close(false);
                    MSEBIS_STATE = MSEBI_STATE_CLOSED;
                    for (i = 0; i < MSEBI_MAX_CS; i++)
                    {
                        MSEBIS_CS_STATE[i] = MSEBI_CS_STATE_CLOSED;
                    }
                }
                else
                {
                    /* Close desired CS */
                    MSEBIS_CS_STATE[chip_sel] = MSEBI_CS_STATE_CLOSED;
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
 End of function R_MSEBI_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_MSEBI_Control
 *
 *  Return value:   Error status
 *
 *  Parameters:     mode - MSEBI master/slave mode
 *                  chip_sel - The desired chip select
 *                  control_request - request to configure MSEBI or get MSEBI info.
 *                  msebi_ctrl - configuration data (to set or get).
 *
 *                  NOTE: API function checks that msebi_ctrl is non-zero.
 *                  The upper layer should check that the buffer lies within a valid address range.
 *
 *  Description:    Configure MSEBI parameters, set chip select parameters or
 *                  get info, depending on control_request
 *
 **********************************************************************************************************************/
ER_RET R_MSEBI_Control (msebi_mode_t mode, uint8_t chip_sel, msebi_cmd_t control_request, void *msebi_ctrl)
{
    ER_RET ret_val = ER_OK;

    if (((chip_sel >= MSEBI_MAX_CS) && (MSEBI_NO_CS != chip_sel)) || (mode > MSEBISLAVE) || (0 == msebi_ctrl))
    {
        /* Undefined chip select or mode */
        ret_val = ER_PARAM;
    }
    else if (((MSEBI_STATE_CLOSED == MSEBIM_STATE) && (MSEBIMASTER == mode))
            || ((MSEBI_STATE_CLOSED == MSEBIS_STATE) && (MSEBISLAVE == mode)))
    {
        /* The desired MSEBI mode is currently closed */
        ret_val = ER_INVAL;
    }
    else
    {
        if (MSEBI_NO_CS == chip_sel)
        {
            switch (control_request)
            {
                case MSEBI_CONTROL_SET_CONFIG:
                    ret_val = MSEBI_SetCommonConfig(mode, msebi_ctrl);
                break;
                case MSEBI_CONTROL_GET_CONFIG:
                    if (MSEBIMASTER == mode)
                    {
                        *(msebim_config_t *) msebi_ctrl = MSEBIM_GetCommonConfig();
                    }
                    else
                    {
                        *(msebis_config_t *) msebi_ctrl = MSEBIS_GetCommonConfig();
                    }
                break;
                case MSEBI_CONTROL_MASTER_CLK_ENABLE:
                    if (MSEBIMASTER == mode)
                    {
                        MSEBIM_EnableDisableCLK( *(bool *) msebi_ctrl);
                    }
                    else
                    {
                        ret_val = ER_PARAM;
                    }
                break;
                case MSEBIM_CONTROL_FLUSH_CPU_FIFO:
                    if (MSEBIMASTER == mode)
                    {
                        MSEBIM_FlushCPUReceiveFIFO();
                    }
                    else
                    {
                        ret_val = ER_PARAM;
                    }
                break;
                case MSEBIS_CONTROL_GET_INT_STATUS:
                    if (MSEBISLAVE == mode)
                    {
                        *(msebis_interrupt_status_t*) msebi_ctrl = MSEBIS_GetIntStatus();
                    }
                    else
                    {
                        ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                    }
                break;
                case MSEBIS_CONTROL_GET_MASKED_INT_STATUS:
                    if (MSEBISLAVE == mode)
                    {
                        *(msebis_interrupt_status_t*) msebi_ctrl = MSEBIS_GetMaskedIntStatus();
                    }
                    else
                    {
                        ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                    }
                break;

                    /* Set interrupt mask */
                case MSEBIS_CONTROL_SET_MASK_INTERRUPT:
                    if (MSEBISLAVE == mode)
                    {
                        ret_val = MSEBIS_SetInterruptMask(msebi_ctrl);
                    }
                    else
                    {
                        ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                    }
                break;
                    /* Get interrupt mask */
                case MSEBIS_CONTROL_GET_MASK_INTERRUPT:
                    if (MSEBISLAVE == mode)
                    {
                        *(msebis_interrupt_control_t*) msebi_ctrl = MSEBIS_GetInterruptMask();
                    }
                    else
                    {
                        ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                    }
                break;

                    /* Set interrupt clear */
                case MSEBIS_CONTROL_CLEAR_INTERRUPT:
                    if (MSEBISLAVE == mode)
                    {
                        ret_val = MSEBIS_ClearInterrupt(msebi_ctrl);
                    }
                    else
                    {
                        ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                    }
                break;

                default:
                    ret_val = ER_INVAL;
                break;
            }
        }
        else
        {
            /* Chip select-specific request */
            if (((MSEBI_CS_STATE_CLOSED == MSEBIM_CS_STATE[chip_sel]) && (MSEBIMASTER == mode))
                    || ((MSEBI_CS_STATE_CLOSED == MSEBIS_CS_STATE[chip_sel]) && (MSEBISLAVE == mode)))
            {
                /* The desired chip select is currently closed */
                ret_val = ER_INVAL;
            }
            else
            {
                switch (control_request)
                {
                    /* DMA Control configuration */
                    case MSEBI_CONTROL_SET_CS_DMA_TCONTROL:
                        ret_val = MSEBIM_SetDMAControl(MSEBI_DMA_TRANSMIT, chip_sel, msebi_ctrl);
                    break;
                    case MSEBI_CONTROL_GET_CS_DMA_TCONTROL:
                        *(msebim_dma_control_cs_t *) msebi_ctrl = MSEBIM_GetDMAControl(MSEBI_DMA_TRANSMIT, chip_sel);
                    break;
                    case MSEBI_CONTROL_SET_CS_DMA_RCONTROL:
                        ret_val = MSEBIM_SetDMAControl(MSEBI_DMA_RECEIVE, chip_sel, msebi_ctrl);
                    break;
                    case MSEBI_CONTROL_GET_CS_DMA_RCONTROL:
                        *(msebim_dma_control_cs_t *) msebi_ctrl = MSEBIM_GetDMAControl(MSEBI_DMA_RECEIVE, chip_sel);
                    break;
                        /* DMA Data level configuration */
                    case MSEBI_CONTROL_SET_CS_DMA_TDATALEVEL:
                        ret_val = MSEBI_SetDMADataLevel(mode, MSEBI_DMA_TRANSMIT, chip_sel, msebi_ctrl);
                    break;
                    case MSEBI_CONTROL_GET_CS_DMA_TDATALEVEL:
                        if (MSEBIMASTER == mode)
                        {
                            *(msebim_dma_datalevel_cs_t*) msebi_ctrl = MSEBIM_GetDMADataLevel(MSEBI_DMA_TRANSMIT,
                                    chip_sel);
                        }
                        else
                        {
                            *(msebis_dma_datalevel_cs_t*) msebi_ctrl = MSEBIS_GetDMADataLevel(MSEBI_DMA_TRANSMIT,
                                    chip_sel);
                        }
                    break;
                    case MSEBI_CONTROL_SET_CS_DMA_RDATALEVEL:
                        ret_val = MSEBI_SetDMADataLevel(mode, MSEBI_DMA_RECEIVE, chip_sel, msebi_ctrl);
                    break;
                    case MSEBI_CONTROL_GET_CS_DMA_RDATALEVEL:
                        if (MSEBIMASTER == mode)
                        {
                            *(msebim_dma_datalevel_cs_t*) msebi_ctrl = MSEBIM_GetDMADataLevel(MSEBI_DMA_RECEIVE,
                                    chip_sel);
                        }
                        else
                        {
                            *(msebis_dma_datalevel_cs_t*) msebi_ctrl = MSEBIS_GetDMADataLevel(MSEBI_DMA_RECEIVE,
                                    chip_sel);
                        }
                    break;
                        /* Other configuration */
                    case MSEBI_CONTROL_SET_CS_CYCLESIZE:
                        ret_val = MSEBI_SetCycleSize(mode, chip_sel, (msebi_cyclesize_t *) msebi_ctrl);
                    break;
                    case MSEBI_CONTROL_GET_CS_CYCLESIZE:
                        *(msebi_cyclesize_t *) msebi_ctrl = MSEBI_GetCycleSize(mode, chip_sel);
                    break;

                    case MSEBI_CONTROL_SET_CS_SETUPHOLD:
                        ret_val = MSEBI_SetSetupHold(mode, chip_sel, (msebi_setuphold_t *) msebi_ctrl);
                    break;
                    case MSEBI_CONTROL_GET_CS_SETUPHOLD:
                        *(msebi_setuphold_t *) msebi_ctrl = MSEBI_GetSetupHold(mode, chip_sel);
                    break;

                    case MSEBI_CONTROL_SET_CS_CONFIG:
                        ret_val = MSEBI_SetConfig(mode, chip_sel, msebi_ctrl);
                    break;
                    case MSEBI_CONTROL_GET_CS_CONFIG:
                        if (MSEBIMASTER == mode)
                        {
                            *(msebim_config_cs_t*) msebi_ctrl = MSEBIM_GetConfig(chip_sel);
                        }
                        else
                        {
                            *(msebis_config_cs_t*) msebi_ctrl = MSEBIS_GetConfig(chip_sel);
                        }
                    break;

                    case MSEBIS_CONTROL_SLAVE_CS_ENABLE:
                        if (MSEBIMASTER == mode)
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                        else
                        {
                            MSEBIS_EnableDisableCS(chip_sel, *(bool*) msebi_ctrl);
                        }
                    break;

                        /* Set the DMA read address register - Master only*/
                    case MSEBIM_CONTROL_SET_CS_DMA_READADDR:
                        if (MSEBIMASTER == mode)
                        {
                            ret_val = MSEBIM_SetDMABlockAddress(MSEBI_DMA_READ, chip_sel,
                                    (msebim_dma_block_address_cs_t*) msebi_ctrl);
                        }
                        else
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                    break;
                        /* Get the DMA read address register  - Master only */
                    case MSEBIM_CONTROL_GET_CS_DMA_READADDR:
                        if (MSEBIMASTER == mode)
                        {
                            *(msebim_dma_block_address_cs_t*) msebi_ctrl = MSEBIM_GetDMABlockAddress(MSEBI_DMA_READ,
                                    chip_sel);
                        }
                        else
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                    break;
                        /* Get the DMA current read address  - Master only */
                    case MSEBIM_CONTROL_GET_CS_DMA_CURR_READADDR:
                        if (MSEBIMASTER == mode)
                        {
                            *(uint32_t*) msebi_ctrl = MSEBIM_GetDMACurrentAddress(MSEBI_DMA_READ, chip_sel);
                        }
                        else
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                    break;

                        /* Set the DMA write address register */
                    case MSEBIM_CONTROL_SET_CS_DMA_WRITEADDR:
                        if (MSEBIMASTER == mode)
                        {
                            ret_val = MSEBIM_SetDMABlockAddress(MSEBI_DMA_WRITE, chip_sel,
                                    (msebim_dma_block_address_cs_t*) msebi_ctrl);
                        }
                        else
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                    break;
                        /* Get the DMA write address register   */
                    case MSEBIM_CONTROL_GET_CS_DMA_WRITEADDR:
                        if (MSEBIMASTER == mode)
                        {
                            *(msebim_dma_block_address_cs_t*) msebi_ctrl = MSEBIM_GetDMABlockAddress(MSEBI_DMA_WRITE,
                                    chip_sel);
                        }
                        else
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                    break;
                        /* Get the DMA current write address register */
                    case MSEBIM_CONTROL_GET_CS_DMA_CURR_WRITEADDR:
                        if (MSEBIMASTER == mode)
                        {
                            *(uint32_t*) msebi_ctrl = MSEBIM_GetDMACurrentAddress(MSEBI_DMA_WRITE, chip_sel);
                        }
                        else
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                    break;
                        /* Set the slave MMU base address */
                    case MSEBIS_CONTROL_SET_CS_MMU_ADDRESS:
                        if (MSEBIMASTER == mode)
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                        else
                        {
                            ret_val = MSEBIS_SetMMUBaseAddress(chip_sel, (uint32_t*) msebi_ctrl);
                        }
                    break;
                        /* Get the slave MMU base address */
                    case MSEBIS_CONTROL_GET_CS_MMU_ADDRESS:
                        if (MSEBIMASTER == mode)
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                        else
                        {
                            *(uint32_t*) msebi_ctrl = MSEBIS_GetMMUBaseAddress(chip_sel);
                        }
                    break;
                        /* Set the slave MMU base address mask*/
                    case MSEBIS_CONTROL_SET_CS_MMU_ADDRESS_MASK:
                        if (MSEBIMASTER == mode)
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                        else
                        {
                            ret_val = MSEBIS_SetMMUBaseAddressMask(chip_sel, (uint32_t*) msebi_ctrl);
                        }
                    break;
                        /* Get the slave MMU base address mask*/
                    case MSEBIS_CONTROL_GET_CS_MMU_ADDRESS_MASK:
                        if (MSEBIMASTER == mode)
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                        else
                        {
                            *(uint32_t*) msebi_ctrl = MSEBIS_GetMMUBaseAddressMask(chip_sel);
                        }
                    break;

                        /* Set the DMA transmit request register */
                    case MSEBIS_CONTROL_SET_CS_DMA_TRANSMIT_REQ:
                        if (MSEBIMASTER == mode)
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                        else
                        {
                            ret_val = MSEBIS_SetDMARequest(MSEBI_DMA_TRANSMIT, chip_sel,
                                    (msebis_dma_request_cs_t*) msebi_ctrl);
                        }
                    break;
                        /* Get the DMA transmit request register */
                    case MSEBIS_CONTROL_GET_CS_DMA_TRANSMIT_REQ:
                        if (MSEBIMASTER == mode)
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                        else
                        {
                            *(msebis_dma_request_cs_t*) msebi_ctrl = MSEBIS_GetDMARequest(MSEBI_DMA_TRANSMIT, chip_sel);
                        }
                    break;
                        /* Set the DMA receive request register */
                    case MSEBIS_CONTROL_SET_CS_DMA_RECEIVE_REQ:
                        if (MSEBIMASTER == mode)
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                        else
                        {
                            ret_val = MSEBIS_SetDMARequest(MSEBI_DMA_RECEIVE, chip_sel,
                                    (msebis_dma_request_cs_t*) msebi_ctrl);
                        }
                    break;
                        /* Get the DMA receive request register */
                    case MSEBIS_CONTROL_GET_CS_DMA_RECEIVE_REQ:
                        if (MSEBIMASTER == mode)
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                        else
                        {
                            *(msebis_dma_request_cs_t*) msebi_ctrl = MSEBIS_GetDMARequest(MSEBI_DMA_RECEIVE, chip_sel);
                        }
                    break;

                        /* Set CPU End of Block address register value */
                    case MSEBIS_CONTROL_SET_CS_CPU_EOB_ADDRESS:
                        if (MSEBISLAVE == mode)
                        {
                            ret_val = MSEBIS_SetCPUEndOfBlockAddress(chip_sel, msebi_ctrl);
                        }
                        else
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                    break;
                        /* Get CPU End of Block address register value */
                    case MSEBIS_CONTROL_GET_CS_CPU_EOB_ADDRESS:
                        if (MSEBISLAVE == mode)
                        {
                            *(uint32_t*) msebi_ctrl = MSEBIS_GetCPUEndOfBlockAddress(chip_sel);
                        }
                        else
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                    break;

                        /* Set DMA End of Block address register value */
                    case MSEBIS_CONTROL_SET_CS_DMA_EOB_ADDRESS:
                        if (MSEBISLAVE == mode)
                        {
                            ret_val = MSEBIS_SetDMAEndOfBlockAddress(chip_sel, msebi_ctrl);
                        }
                        else
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                    break;
                        /* Get DMA End of Block address register value */
                    case MSEBIS_CONTROL_GET_CS_DMA_EOB_ADDRESS:
                        if (MSEBISLAVE == mode)
                        {
                            *(uint32_t*) msebi_ctrl = MSEBIS_GetDMAEndOfBlockAddress(chip_sel);
                        }
                        else
                        {
                            ret_val = ((ER_RET) (3 * ((ER_RET) -1)));
                        }
                    break;

                    default:
                        ret_val = ER_INVAL;
                    break;
                }
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_MSEBI_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_SetCallback
 *
 *  Return value:   Error status
 *
 *  Parameters:     chip_sel - The chip select to configure 0-3
 *                  callback_mode - mode which determines for which interrupt callback function stands
 *                  callback - callback function
 *                  mode - MSEBI master/slave mode
 *
 *  Description:    Register callback function
 *
 **********************************************************************************************************************/
ER_RET R_MSEBIS_SetCallback (msebi_mode_t mode, msebi_callback_mode_t callback_mode, uint8_t chip_sel, msebi_callback callback)
{
    ER_RET ret_val = ER_OK;

    if (((chip_sel >= MSEBI_MAX_CS) && (MSEBI_NO_CS != chip_sel)) || (mode != MSEBISLAVE) || (FIT_NO_PTR == callback))
    {
        /* Undefined chip select or mode */
        ret_val = ER_PARAM;
    }
    else if ((MSEBI_STATE_CLOSED == MSEBIS_STATE) && (MSEBISLAVE == mode))
    {
        /* The desired MSEBI mode is currently closed */
        ret_val = ER_INVAL;
    }
    else
    {
        ret_val = MSEBIS_SetCallback(callback_mode, chip_sel, callback);
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_MSEBIS_SetCallback
 **********************************************************************************************************************/
