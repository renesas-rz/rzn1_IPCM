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
 * FILE         :  r_msebi_rzn1.c
 * Description  :  MSEBI driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "platform.h"
#include "r_msebi_rzn1_config.h"
#include "r_msebi_rzn1_if.h"
#include "r_iomux_rzn1_if.h"
#include "r_msebi_rzn1.h"
#include "iodefine.h"
#include "r_sysctrl_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define MSEBI_CLK_4                          (3)
#define MSEBIM_CLK_ENABLE                    (0x01 << 4)
#define MSEBIM_HCLK_4                        (MSEBI_CLK_4)
#define MSEBIS_MAX_TIMEOUT_DELAY             (0x0F)

#define MSEBI_MAX_DLE_PHASE                  (MSEBI_CLK_4)
#define MSEBI_MAX_DLE_SETUP_HOLD             (63)
#define MSEBIS_MIN_DLE_SETUP                 (1)
#define MSEBIM_MAX_ALE                       (4)
#define MSEBIM_EXT_ADR_MASK                  (0x1F)
#define MSEBIS_CS_ENABLE                     (0x01 << 9)

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
typedef struct
{
    msebi_cyclesize_t cycle_size;
    msebi_setuphold_t setup_hold;
    msebim_config_cs_t config;
} msebim_cs_params_t;

typedef struct
{
    msebim_dma_datalevel_cs_t dma_transmit_datalevel;
    msebim_dma_datalevel_cs_t dma_receive_datalevel;
    msebim_dma_control_cs_t dma_transmit_control;
    msebim_dma_control_cs_t dma_receive_control;
    msebim_dma_block_address_cs_t dma_write_block_address;
    msebim_dma_block_address_cs_t dma_read_block_address;
} msebim_cs_dma_params_t;

typedef struct
{
    msebi_cyclesize_t cycle_size;
    msebi_setuphold_t setup_hold;
    msebis_config_cs_t config;
    uint32_t mmu_base_address;
    uint32_t mmu_base_address_mask;
    uint32_t eob_cpu_address;
} msebis_cs_params_t;

typedef struct
{
    msebis_dma_request_cs_t dma_transmit_request;
    msebis_dma_request_cs_t dma_receive_request;
    msebis_dma_datalevel_cs_t dma_transmit_datalevel;
    msebis_dma_datalevel_cs_t dma_receive_datalevel;
    uint32_t eob_dma_address;
} msebis_cs_dma_params_t;

typedef struct
{
    msebim_config_t msebim_common_config;
    msebim_cs_params_t MSEBIM_CS_PARAM[MSEBI_MAX_CS];
    msebim_cs_dma_params_t MSEBIM_CS_DMA_PARAM[MSEBI_MAX_DMA_CS];
} msebim_params_t;

typedef struct
{
    msebis_config_t msebis_common_config;
    msebis_interrupt_control_t msebis_interrupt_mask;
    msebis_cs_params_t MSEBIS_CS_PARAM[MSEBI_MAX_CS];
    msebis_cs_dma_params_t MSEBIS_CS_DMA_PARAM[MSEBI_MAX_DMA_CS];
} msebis_params_t;

/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/
static void handle_msebi_interrupt (IRQn_Type *irq_num_ptr);

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
volatile MSEBIM_Type *msebim_base_address;
volatile MSEBIS_Type *msebis_base_address;

msebim_params_t MSEBIM_PARAMS;
msebis_params_t MSEBIS_PARAMS;

msebi_callback rx_callback[MSEBI_CS_COUNT];
msebi_callback tx_callback[MSEBI_CS_COUNT];
/***********************************************************************************************************************
 *
 *  Function:       MSEBI_Init
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Initialises the MSEBI driver
 *
 **********************************************************************************************************************/
void MSEBI_Init (void)
{
    /* Reset all parameters */
    msebim_base_address = (volatile MSEBIM_Type *) RZN1_MSEBI_M0_BASE;
    msebis_base_address = (volatile MSEBIS_Type *) RZN1_MSEBI_S_BASE;
}
/***********************************************************************************************************************
 End of function MSEBI_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBI_Open
 *
 *  Return value:   Error status
 *
 *  Parameters:     master - true: master, false: slave
 *
 *  Description:    Opens the MSEBI master or slave
 *
 **********************************************************************************************************************/
ER_RET MSEBI_Open (bool master)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num = master ? RZN1_IRQ_MSEBIM : RZN1_IRQ_MSEBIS;
    uint32_t int_priority = MSEBI_DEFAULT_INT_PRIORITY;
    uint32_t address_value = 0x0;

    /* Ensure pins are configured for master or slave. */
    MSEBI_PinMux(master);

    /* Enable bus interconnect and PCLK to the MSEBI */
    R_SYSCTRL_EnableMSEBI(master);

    /* Enable system interrupts and register interrupt handler */
    if (RZN1_IRQ_MSEBIS == irq_num)
    {
        /* Interrupts only supported in slave mode */
        if (R_BSP_InterruptRegisterCallback((IRQn_Type) irq_num, (bsp_int_cb_t) &handle_msebi_interrupt)
                == MCU_INT_SUCCESS)
        {
            ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
            if (MCU_INT_SUCCESS != ret_val)
            {
                ret_val = ER_SYS;
            }
            else
            {
                ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);
            }
        }
        else
        {
            ret_val = ER_SYS;
        }
    }

    /* Set defaults */
    if (master)
    {
        /* Set the common configurations */
        MSEBI_SetCommonConfig(MSEBIMASTER, (void *) &default_msebim_config);

        /* Set the chip select configurations */
        for (int chip_sel = 0; chip_sel < MSEBI_MAX_CS; chip_sel++)
        {
            MSEBI_SetCycleSize(MSEBIMASTER, chip_sel, (void *) &default_msebi_cyclesize_cs);
            MSEBI_SetSetupHold(MSEBIMASTER, chip_sel, (void *) &default_msebi_setuphold_cs);
            MSEBI_SetConfig(MSEBIMASTER, chip_sel, (void *) &default_msebim_config_cs);
            MSEBI_SetDMADataLevel(MSEBIMASTER, MSEBI_DMA_TRANSMIT, chip_sel, (void *) &default_msebim_dma_datalevel_cs);
            MSEBI_SetDMADataLevel(MSEBIMASTER, MSEBI_DMA_RECEIVE, chip_sel, (void *) &default_msebim_dma_datalevel_cs);
            MSEBIM_SetDMAControl(MSEBI_DMA_TRANSMIT, chip_sel, (void *) &default_msebim_dma_control_cs);
            MSEBIM_SetDMAControl(MSEBI_DMA_RECEIVE, chip_sel, (void *) &default_msebim_dma_control_cs);
            MSEBIM_SetDMABlockAddress(MSEBI_DMA_WRITE, chip_sel, &default_msebim_dma_block_address_cs);
            MSEBIM_SetDMABlockAddress(MSEBI_DMA_READ, chip_sel, &default_msebim_dma_block_address_cs);
        }
    }
    else
    {
        /* Set the common configurations */
        MSEBI_SetCommonConfig(MSEBISLAVE, (void *) &default_msebis_config);
        MSEBIS_SetInterruptMask( &default_msebis_interrupt_masks);
        MSEBIS_ClearInterrupt( &default_msebis_interrupt_clear);

        /* Set the chip select configurations */
        for (int chip_sel = 0; chip_sel < MSEBI_MAX_CS; chip_sel++)
        {
            MSEBI_SetCycleSize(MSEBISLAVE, chip_sel, (void *) &default_msebi_cyclesize_cs);
            MSEBI_SetSetupHold(MSEBISLAVE, chip_sel, (void *) &default_msebi_setuphold_cs);
            MSEBI_SetConfig(MSEBISLAVE, chip_sel, (void *) &default_msebis_config_cs);
            MSEBI_SetDMADataLevel(MSEBISLAVE, MSEBI_DMA_TRANSMIT, chip_sel, (void *) &default_msebis_dma_datalevel_cs);
            MSEBI_SetDMADataLevel(MSEBISLAVE, MSEBI_DMA_RECEIVE, chip_sel, (void *) &default_msebis_dma_datalevel_cs);

            address_value = 0x0;
            MSEBIS_SetMMUBaseAddress(chip_sel, &address_value);
            address_value = 0xFFFFFFFF;
            MSEBIS_SetMMUBaseAddressMask(chip_sel, &address_value);

            address_value = 0x0;
            MSEBIS_SetCPUEndOfBlockAddress(chip_sel, &address_value);
            MSEBIS_SetDMAEndOfBlockAddress(chip_sel, &address_value);
        }

        /* Perform these as the last operation */
        for (int chip_sel = 0; chip_sel < MSEBI_MAX_DMA_CS; chip_sel++)
        {
            MSEBIS_SetDMARequest(MSEBI_DMA_TRANSMIT, chip_sel, &default_msebis_dma_request_cs);
            MSEBIS_SetDMARequest(MSEBI_DMA_RECEIVE, chip_sel, &default_msebis_dma_request_cs);
        }

    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBI_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBI_Close
 *
 *  Return value:   None
 *
 *  Parameters:     master - true: master, false: slave
 *
 *  Description:    Closes the MSEBI master or slave
 *
 **********************************************************************************************************************/
void MSEBI_Close (bool master)
{
    IRQn_Type irq_num = master ? RZN1_IRQ_MSEBIM : RZN1_IRQ_MSEBIS;

    /* Disable system interrupts and register interrupt handler */
    if (RZN1_IRQ_MSEBIS == irq_num)
    {
        /* Interrupts only supported in slave mode */
        R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE,
        FIT_NO_PTR);
    }

    /* Clear parameters */

    /* Disable bus interconnect and PCLK from the MSEBI */
    R_SYSCTRL_DisableMSEBI(master);
}
/***********************************************************************************************************************
 End of function MSEBI_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       GetDMAControlRegister
 *
 *  Return value:   Address of require DMA control register.
 *
 *  Parameters:     access - Transmit or Recieve configuration.
 *                  chip_sel - The chip select to configure only 0-1
 *
 *  Description:    Determines the required register address based on chip select and access method.
 *
 **********************************************************************************************************************/
uint32_t * GetDMAControlRegister (msebi_dma_access_t access, uint8_t chip_sel)
{
    uint32_t *ret_val = 0x0;
    /* Parameter Check */
    if (chip_sel >= MSEBI_CS_DMA_COUNT) /* Only chip select 0 and 1 supported. */
    {
        ret_val = (uint32_t *) ER_PARAM;
    }
    else
    {
        /* Choose either transmit or receive register */
        ret_val =
                (MSEBI_DMA_TRANSMIT == access) ? (uint32_t *) &msebim_base_address->rMSEBIM_TDMACR_CS0_N.LONG :
                        (uint32_t *) &msebim_base_address->rMSEBIM_RDMACR_CS0_N.LONG;
        ret_val += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function GetDMAControlRegister
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIM_SetDMAControl
 *
 *  Return value:   Error status
 *
 *  Parameters:     access - Transmit or Recieve configuration.
 *                  chip_sel - The chip select to configure only 0-1
 *                  dma_control - The configuration structure
 *
 *  Description:    Sets the user-defined master configuration
 *
 **********************************************************************************************************************/
ER_RET MSEBIM_SetDMAControl (msebi_dma_access_t access, uint8_t chip_sel, msebim_dma_control_cs_t *dma_control)
{
    ER_RET ret_val = ER_OK;
    uint32_t *rMSEBI_aDMACR_CSn_N = GetDMAControlRegister(access, chip_sel);

    /* Parameter Check */
    if ((dma_control == NULL) || ((uint32_t*) ER_PARAM == rMSEBI_aDMACR_CSn_N))
    {
        ret_val = ER_PARAM;
    }
    else if ((dma_control->burst_size > MSEBIM_BURST_MAX) || (dma_control->block_size > MSEBI_MAX_DMA_TRANSFER_SIZE))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        *rMSEBI_aDMACR_CSn_N = (dma_control->block_size << 4) | (dma_control->burst_size << 1)
                | (uint8_t) dma_control->enable_dma;

        /* Save configuration */
        msebim_dma_control_cs_t *save_to_ptr =
                (MSEBI_DMA_TRANSMIT == access) ? ( &MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_transmit_control) :
                        ( &MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_receive_control);
        *save_to_ptr = *dma_control;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBIM_SetDMAControl
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIM_GetDMAControl
 *
 *  Return value:   Master DMA control configuration value.
 *
 *  Parameters:     access - Transmit or Receive
 *                  chip_sel - The chip select to configure
 *
 *  Description:    Returns the defined DMA Master control configuration of the chip select
 *
 **********************************************************************************************************************/
msebim_dma_control_cs_t MSEBIM_GetDMAControl (msebi_dma_access_t access, uint8_t chip_sel)
{
    /* Get the actual register value. */
    uint32_t value = 0x0;
    uint32_t *rMSEBI_aDMACR_CSn_N = GetDMAControlRegister(access, chip_sel);
    if ((uint32_t*) ER_PARAM != rMSEBI_aDMACR_CSn_N)
    {
        value = *rMSEBI_aDMACR_CSn_N;
    }

    /* Get pointer to stored data structure */
    msebim_dma_control_cs_t *dma_control =
            (MSEBI_DMA_TRANSMIT == access) ? ( &MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_transmit_control) :
                    ( &MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_receive_control);

    /* Update the stored read only bits from the actual register. */
    dma_control->single_dest_width = (bool)(value & 0x40000000); /* Bit 30 */
    dma_control->current_block_size = (uint16_t)((value & 0x3FFe0000) >> 17); /* bits 17 to 29; */
    return *dma_control;
}
/***********************************************************************************************************************
 End of function MSEBIM_GetDMAControl
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       GetDMADataLevelRegister
 *
 *  Return value:   Address of required DMA data level registers.
 *
 *  Parameters:     mode - Master or Slave
 *                  access - Transmit or Recieve configuration.
 *                  chip_sel - The chip select to configure only 0-1
 *
 *  Description:    Determines the required register address based on chip select and access method.
 *
 **********************************************************************************************************************/
uint32_t * GetDMADataLevelRegister (msebi_mode_t mode, msebi_dma_access_t access, uint8_t chip_sel)
{
    uint32_t *ret_val = 0x0;
    /* Parameter Check */
    if (chip_sel >= MSEBI_CS_DMA_COUNT) /* Only chip select 0 and 1 supported. */
    {
        ret_val = (uint32_t *) ER_PARAM;
    }
    else
    {
        if (MSEBIMASTER == mode)
        {
            /* Choose either transmit or receive register */
            ret_val =
                    (MSEBI_DMA_TRANSMIT == access) ? (uint32_t *) &msebim_base_address->rMSEBIM_DMATDLR_CS0_N.LONG :
                            (uint32_t *) &msebim_base_address->rMSEBIM_DMARDLR_CS0_N.LONG;
            ret_val += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));
        }
        else
        {
            /* Choose either transmit or receive register */
            ret_val =
                    (MSEBI_DMA_TRANSMIT == access) ? (uint32_t *) &msebis_base_address->rMSEBIS_DMATDLR_CS0_N.LONG :
                            (uint32_t *) &msebis_base_address->rMSEBIS_DMARDLR_CS0_N.LONG;
            ret_val += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function GetDMADataLevelRegister
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBI_SetDMADataLevel
 *
 *  Return value:   Error status
 *
 *  Parameters:     mode - Master or Slave MSEBI
 *                  access - Transmit or Recieve configuration.
 *                  chip_sel - The chip select to configure only 0-1
 *                  config - The configuration structure
 *
 *  Description:    Sets the user-defined master/slave configurations
 *
 **********************************************************************************************************************/
ER_RET MSEBI_SetDMADataLevel (msebi_mode_t mode, msebi_dma_access_t access, uint8_t chip_sel, void *config)
{
    ER_RET ret_val = ER_OK;
    uint32_t *rMSEBI_DMAaDLR_CSn_N = GetDMADataLevelRegister(mode, access, chip_sel);
    uint32_t preserved_value;

    /* Parameter Check */
    if ((config == NULL) || (chip_sel >= MSEBI_CS_DMA_COUNT) || ((uint32_t*) ER_PARAM == rMSEBI_DMAaDLR_CSn_N)) /* Only chip select 0 and 1 supported. */
    {
        ret_val = ER_PARAM;
    }
    else if (MSEBIMASTER == mode)
    {
        /* Master mode */
        msebim_dma_datalevel_cs_t *dma_datalevel = (msebim_dma_datalevel_cs_t *) config;
        if ((dma_datalevel->fifo_burst_size > MSEBIM_BURST_MAX)
                || (dma_datalevel->fifo_data_level > MSEBI_MAX_FIFO_LEVEL))
        {
            ret_val = ER_PARAM;
        }
        else
        {
            preserved_value = *rMSEBI_DMAaDLR_CSn_N;
            *rMSEBI_DMAaDLR_CSn_N = (preserved_value & 0x80000000) /* Preserve bit 31 */
            | ((uint8_t) dma_datalevel->use_ext_pin << 16) | (dma_datalevel->fifo_burst_size << 13)
                    | dma_datalevel->fifo_data_level;

            /* Save configuration */
            msebim_dma_datalevel_cs_t *save_to_ptr =
                    (MSEBI_DMA_TRANSMIT == access) ?
                            ( &MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_transmit_datalevel) :
                            ( &MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_receive_datalevel);
            *save_to_ptr = *dma_datalevel;
        }
    }
    else if (MSEBISLAVE == mode)
    {
        /* Slave mode */
        msebis_dma_datalevel_cs_t *dma_datalevel = (msebis_dma_datalevel_cs_t *) config;
        if (dma_datalevel->fifo_burst_size > MSEBIS_BURST_MAX)
        {
            ret_val = ER_PARAM;
        }
        else
        {
            preserved_value = *rMSEBI_DMAaDLR_CSn_N;
            *rMSEBI_DMAaDLR_CSn_N = (preserved_value & 0x80000000) /* Preserve bit 31 */
            | ((uint8_t) dma_datalevel->flow_control << 3) | ((uint8_t) dma_datalevel->burst_size_optimised << 2)
                    | dma_datalevel->fifo_burst_size;

            /* Save configuration */
            msebis_dma_datalevel_cs_t *save_to_ptr =
                    (MSEBI_DMA_TRANSMIT == access) ?
                            ( &MSEBIS_PARAMS.MSEBIS_CS_DMA_PARAM[chip_sel].dma_transmit_datalevel) :
                            ( &MSEBIS_PARAMS.MSEBIS_CS_DMA_PARAM[chip_sel].dma_receive_datalevel);
            *save_to_ptr = *dma_datalevel;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBI_SetDMADataLevel
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIM_GetDMADataLevel
 *
 *  Return value:   Master data level configuration params
 *
 *  Parameters:     access - Transmit or Receive
 *                  chip_sel - The chip select to configure
 *
 *  Description:    Returns the defined DMA Master data level configuration of the chip select
 *
 **********************************************************************************************************************/
msebim_dma_datalevel_cs_t MSEBIM_GetDMADataLevel (msebi_dma_access_t access, uint8_t chip_sel)
{
    uint32_t value = 0x0;
    uint32_t *rMSEBI_DMAaDLR_CSn_N = GetDMADataLevelRegister(MSEBIMASTER, access, chip_sel);
    if ((uint32_t*) ER_PARAM != rMSEBI_DMAaDLR_CSn_N)
    {
        value = *rMSEBI_DMAaDLR_CSn_N;
    }

    /* Get pointer to stored data structure */
    msebim_dma_datalevel_cs_t *dma_datalevel =
            (MSEBI_DMA_TRANSMIT == access) ? ( &MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_transmit_datalevel) :
                    ( &MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_receive_datalevel);

    /* Update the stored read only bits from the actual register. */
    dma_datalevel->current_fifo_data_level = (uint8_t)((value & 0x00000FC0) >> 6); // Bits 6 to 11
    return *dma_datalevel;
}
/***********************************************************************************************************************
 End of function MSEBIM_GetDMADataLevel
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_GetDMADataLevel
 *
 *  Return value:   Slave data level configuration params
 *
 *  Parameters:     access - Transmit or Receive
 *                  chip_sel - The chip select to configure
 *
 *  Description:    Returns the defined DMA Slave data level configuration of the chip select
 *
 **********************************************************************************************************************/
msebis_dma_datalevel_cs_t MSEBIS_GetDMADataLevel (msebi_dma_access_t access, uint8_t chip_sel)
{
    uint32_t value = 0x0;
    uint32_t *rMSEBI_DMAaDLR_CSn_N = GetDMADataLevelRegister(MSEBISLAVE, access, chip_sel);
    if ((uint32_t*) ER_PARAM != rMSEBI_DMAaDLR_CSn_N)
    {
        value = *rMSEBI_DMAaDLR_CSn_N;
    }

    /* Get pointer to stored data structure */
    msebis_dma_datalevel_cs_t *dma_datalevel =
            (MSEBI_DMA_TRANSMIT == access) ? ( &MSEBIS_PARAMS.MSEBIS_CS_DMA_PARAM[chip_sel].dma_transmit_datalevel) :
                    ( &MSEBIS_PARAMS.MSEBIS_CS_DMA_PARAM[chip_sel].dma_receive_datalevel);

    /* Update the stored read only bits from the actual register. */
    dma_datalevel->current_fifo_data_level = (uint8_t)((value & 0x00003F00) >> 8); // Bits 8 to 13
    return *dma_datalevel;
}
/***********************************************************************************************************************
 End of function MSEBIS_GetDMADataLevel
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIM_SetDMABlockAddress
 *
 *  Return value:   Error status
 *
 *  Parameters:     access - Read or Write configuration.
 *                  chip_sel - The chip select to configure only 0-1
 *                  dma_address - The configuration structure containing the block address, only bits 3 to 31 used.
 *
 *  Description:    Sets the DMA first block for read or write operation.
 *
 **********************************************************************************************************************/
ER_RET MSEBIM_SetDMABlockAddress (msebi_dma_access_t access, uint8_t chip_sel,
        const msebim_dma_block_address_cs_t *dma_address)
{
    ER_RET ret_val = ER_OK;
    uint32_t *rMSEBIM_ADDRDMA_a_CS0_N;

    /* Parameter Check */
    if ((dma_address == NULL) || (chip_sel >= MSEBI_CS_DMA_COUNT)) /* Only chip select 0 and 1 supported. */
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Choose either read or write register */
        rMSEBIM_ADDRDMA_a_CS0_N =
                (MSEBI_DMA_READ == access) ? (uint32_t *) &msebim_base_address->rMSEBIM_ADDRDMA_READ_CS0_N.LONG :
                        (uint32_t *) &msebim_base_address->rMSEBIM_ADDRDMA_WRITE_CS0_N.LONG;
        rMSEBIM_ADDRDMA_a_CS0_N += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));

        *rMSEBIM_ADDRDMA_a_CS0_N = (dma_address->address_dma_read & 0xFFFFFFF8)
                | ((uint8_t) dma_address->align_first_block_32bit << 2);

        /* Save configuration */
        msebim_dma_block_address_cs_t *save_to_ptr =
                (MSEBI_DMA_READ == access) ? ( &MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_read_block_address) :
                        ( &MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_write_block_address);
        *save_to_ptr = *dma_address;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBIM_SetDMABlockAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIM_GetDMABlockAddress
 *
 *  Return value:   Master DMA control configuration params
 *
 *  Parameters:     access - Transmit or Receive
 *                  chip_sel - The chip select to configure
 *
 *  Description:    Returns the DMA first block address for read or write operation for the chip select
 *
 **********************************************************************************************************************/
msebim_dma_block_address_cs_t MSEBIM_GetDMABlockAddress (msebi_dma_access_t access, uint8_t chip_sel)
{
    return (MSEBI_DMA_READ == access) ? MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_read_block_address :
            MSEBIM_PARAMS.MSEBIM_CS_DMA_PARAM[chip_sel].dma_write_block_address;
}
/***********************************************************************************************************************
 End of function MSEBIM_GetDMABlockAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIM_GetDMACurrentAddress
 *
 *  Return value:   slave from cpu interrupt status
 *
 *  Parameters:     None.
 *
 *  Description:    Returns the slave from cpu interrupt status
 *
 **********************************************************************************************************************/
uint32_t MSEBIM_GetDMACurrentAddress (msebi_dma_access_t access, uint8_t chip_sel)
{
    uint32_t *rMSEBIM_ADDRDMA_CURRENTa_CS0_N;
    uint32_t msebim_dma_curr_address;

    /* Parameter Check */
    if (chip_sel < MSEBI_CS_DMA_COUNT) /* Only chip select 0 and 1 supported. */
    {
        /* Choose either read or write register */
        rMSEBIM_ADDRDMA_CURRENTa_CS0_N =
                (MSEBI_DMA_READ == access) ? (uint32_t *) &msebim_base_address->rMSEBIM_ADDRDMA_CURRENTREAD_CS0_N.LONG :
                        (uint32_t *) &msebim_base_address->rMSEBIM_ADDRDMA_CURRENTWRITE_CS0_N.LONG;
        rMSEBIM_ADDRDMA_CURRENTa_CS0_N += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));
        msebim_dma_curr_address = *rMSEBIM_ADDRDMA_CURRENTa_CS0_N;
    }
    else
    {
        msebim_dma_curr_address = 0;
    }
    return msebim_dma_curr_address;
}
/***********************************************************************************************************************
 End of function MSEBIM_GetDMACurrentAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_SetMMUBaseAddress
 *
 *  Return value:   Error status
 *
 *  Parameters:     chip_sel - The chip select to configure 0-3
 *                  mmu_address - MMU address, only bits 12 to 31 used.
 *
 *  Description:    When in MMU mode. Sets the base address.
 *
 **********************************************************************************************************************/
ER_RET MSEBIS_SetMMUBaseAddress (uint8_t chip_sel, const uint32_t *mmu_address)
{
    ER_RET ret_val = ER_OK;
    uint32_t *rMSEBIS_MMU_ADDR_CS0_N;

    /* Parameter Check */
    if ((mmu_address == NULL) || (chip_sel >= MSEBI_CS_COUNT)) /* Chip select 0 and 3 supported. */
    {
        ret_val = ER_PARAM;
    }
    else
    {
        rMSEBIS_MMU_ADDR_CS0_N = (uint32_t *) &msebis_base_address->rMSEBIS_MMU_ADDR_CS0_N.LONG;
        rMSEBIS_MMU_ADDR_CS0_N += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));

        *rMSEBIS_MMU_ADDR_CS0_N = ( *mmu_address) & 0xFFFFF000;

        /* Save configuration */
        MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].mmu_base_address = ( *mmu_address) & 0xFFFFF000;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBIS_SetMMUBaseAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_GetMMUBaseAddress
 *
 *  Return value:   MMU base address
 *
 *  Parameters:     chip_sel - The chip select to configure
 *
 *  Description:    Returns When in MMU mode. Gets the base address for chip select.
 *
 **********************************************************************************************************************/
uint32_t MSEBIS_GetMMUBaseAddress (uint8_t chip_sel)
{
    return MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].mmu_base_address;
}
/***********************************************************************************************************************
 End of function MSEBIS_GetMMUBaseAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_SetMMUBaseAddressMask
 *
 *  Return value:   Error status
 *
 *  Parameters:     chip_sel - The chip select to configure 0-3
 *                  mmu_address_mask - MMU address mask, only bits 12 to 31 used.
 *
 *  Description:    When in MMU mode. Sets the base address mask.
 *
 **********************************************************************************************************************/
ER_RET MSEBIS_SetMMUBaseAddressMask (uint8_t chip_sel, const uint32_t *mmu_address_mask)
{
    ER_RET ret_val = ER_OK;
    uint32_t *rMSEBIS_MMU_ADDR_MASK_CS0_N;

    /* Parameter Check */
    if ((mmu_address_mask == NULL) || (chip_sel >= MSEBI_CS_COUNT)) /* Chip select 0 and 3 supported. */
    {
        ret_val = ER_PARAM;
    }
    else
    {
        rMSEBIS_MMU_ADDR_MASK_CS0_N = (uint32_t *) &msebis_base_address->rMSEBIS_MMU_ADDR_MASK_CS0_N.LONG;
        rMSEBIS_MMU_ADDR_MASK_CS0_N += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));

        *rMSEBIS_MMU_ADDR_MASK_CS0_N = ( *mmu_address_mask) | 0xFFF; /* always set bits b0-b11 */

        /* Save configuration */
        MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].mmu_base_address_mask = ( *mmu_address_mask) | 0xFFF;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBIS_SetMMUBaseAddressMask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_GetMMUBaseAddressMask
 *
 *  Return value:   MMU base address mask
 *
 *  Parameters:     chip_sel - The chip select to configure
 *
 *  Description:    Returns When in MMU mode. Gets the base address mask for chip select.
 *
 **********************************************************************************************************************/
uint32_t MSEBIS_GetMMUBaseAddressMask (uint8_t chip_sel)
{
    return MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].mmu_base_address_mask;
}
/***********************************************************************************************************************
 End of function MSEBIS_GetMMUBaseAddressMask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_SetDMARequest
 *
 *  Return value:   Error status
 *
 *  Parameters:     access - Transmit or Receive configuration.
 *                  chip_sel - The chip select to configure only 0-1
 *                  dma_address - The configuration structure containing the block address, only bits 3 to 31 used.
 *
 *  Description:    Sets the DMA first block for read or write operation.
 *
 **********************************************************************************************************************/
ER_RET MSEBIS_SetDMARequest (msebi_dma_access_t access, uint8_t chip_sel, const msebis_dma_request_cs_t *dma_request)
{
    ER_RET ret_val = ER_OK;
    uint32_t *rMSEBIS_DMAa_REQ_CS0_N;

    /* Parameter Check */
    if ((dma_request == NULL) || (chip_sel >= MSEBI_CS_DMA_COUNT)) /* Only chip select 0 and 1 supported. */
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Choose either read or write register */
        rMSEBIS_DMAa_REQ_CS0_N =
                (MSEBI_DMA_RECEIVE == access) ? (uint32_t *) &msebis_base_address->rMSEBIS_DMARX_REQ_CS0_N.LONG :
                        (uint32_t *) &msebis_base_address->rMSEBIS_DMATX_REQ_CS0_N.LONG;
        rMSEBIS_DMAa_REQ_CS0_N += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));

        *rMSEBIS_DMAa_REQ_CS0_N = ((uint8_t) dma_request->enable << 1) | (uint8_t) dma_request->force;

        /* Save configuration */
        msebis_dma_request_cs_t *save_to_ptr =
                (MSEBI_DMA_RECEIVE == access) ? ( &MSEBIS_PARAMS.MSEBIS_CS_DMA_PARAM[chip_sel].dma_receive_request) :
                        ( &MSEBIS_PARAMS.MSEBIS_CS_DMA_PARAM[chip_sel].dma_transmit_request);
        *save_to_ptr = *dma_request;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBIS_SetDMARequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_GetDMARequest
 *
 *  Return value:   Slave DMA request settinsg
 *
 *  Parameters:     access - Transmit or Receive
 *                  chip_sel - The chip select to configure 0 - 1
 *
 *  Description:    Returns the defined DMA Slave receive request configuration of the chip select
 *
 **********************************************************************************************************************/
msebis_dma_request_cs_t MSEBIS_GetDMARequest (msebi_dma_access_t access, uint8_t chip_sel)
{
    return (MSEBI_DMA_TRANSMIT == access) ? MSEBIS_PARAMS.MSEBIS_CS_DMA_PARAM[chip_sel].dma_transmit_request :
            MSEBIS_PARAMS.MSEBIS_CS_DMA_PARAM[chip_sel].dma_receive_request;
}
/***********************************************************************************************************************
 End of function MSEBIS_GetDMARequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_SetInterruptMask
 *
 *  Return value:   Error status
 *
 *  Parameters:     Interrupt mask settings for slave.
 *
 *  Description:    Set slave interrupt mask for CPU/DMA chip select rx and tx
 *
 **********************************************************************************************************************/
ER_RET MSEBIS_SetInterruptMask (const msebis_interrupt_control_t *intr_mask)
{
    ER_RET ret_val = ER_OK;
    unsigned long field_value_tx = 0;
    unsigned long field_value_rx = 0;
    int cs = 0;

    /* Parameter Check */
    if (intr_mask == NULL)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Set bit interrupt mask flag values for each chip 0,1 for DMA */
        for (cs = 0; cs < MSEBI_CS_DMA_COUNT; cs++)
        {
            field_value_tx = field_value_tx | (((uint8_t) intr_mask->eob_interrupt_dma_tx[cs]) << cs);
            field_value_rx = field_value_rx | (((uint8_t) intr_mask->eob_interrupt_dma_rx[cs]) << cs);
        }
        msebis_base_address->rMSEBIS_MASK_INT.BIT.bMSEBIS_MASK_INT_DMATX = field_value_tx;
        msebis_base_address->rMSEBIS_MASK_INT.BIT.bMSEBIS_MASK_INT_DMARX = field_value_rx;

        /* Set bit interrupt mask flag values for each chip 0,3 for CPU */
        field_value_tx = 0;
        field_value_rx = 0;
        for (cs = 0; cs < MSEBI_CS_COUNT; cs++)
        {
            field_value_tx = field_value_tx | (((uint8_t) intr_mask->eob_interrupt_cpu_tx[cs]) << cs);
            field_value_rx = field_value_rx | (((uint8_t) intr_mask->eob_interrupt_cpu_rx[cs]) << cs);
        }
        msebis_base_address->rMSEBIS_MASK_INT.BIT.bMSEBIS_MASK_INT_CPUTX = field_value_tx;
        msebis_base_address->rMSEBIS_MASK_INT.BIT.bMSEBIS_MASK_INT_CPURX = field_value_rx;

        /* Save configuration */
        MSEBIS_PARAMS.msebis_interrupt_mask = *intr_mask;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBIS_SetInterruptMask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_GetInterruptMask
 *
 *  Return value:   Interrupt mask settings for slave.
 *
 *  Parameters:
 *
 *  Description:    Get slave interrupt mask for CPU/DMA chip select rx and tx
 *
 **********************************************************************************************************************/
msebis_interrupt_control_t MSEBIS_GetInterruptMask ()
{
    return MSEBIS_PARAMS.msebis_interrupt_mask;
}
/***********************************************************************************************************************
 End of function MSEBIS_GetInterruptMask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_ClearInterrupt
 *
 *  Return value:   Error status
 *
 *  Parameters:     Clear slave interrupt settings
 *
 *  Description:    clear slave interrupt for CPU/DMA chip select rx and tx
 *
 **********************************************************************************************************************/
ER_RET MSEBIS_ClearInterrupt (const msebis_interrupt_control_t *intr_clear)
{
    ER_RET ret_val = ER_OK;
    unsigned long field_value_tx = 0;
    unsigned long field_value_rx = 0;
    int cs = 0;

    /* Parameter Check */
    if (intr_clear == NULL)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Set bit interrupt mask flag values for each chip 0,1 for DMA */
        for (cs = 0; cs < MSEBI_CS_DMA_COUNT; cs++)
        {
            field_value_tx = field_value_tx | (((uint8_t) intr_clear->eob_interrupt_dma_tx[cs]) << cs);
            field_value_rx = field_value_rx | (((uint8_t) intr_clear->eob_interrupt_dma_rx[cs]) << cs);
        }
        msebis_base_address->rMSEBIS_CLR_INT.BIT.bMSEBIS_CLR_INT_DMATX = field_value_tx;
        msebis_base_address->rMSEBIS_CLR_INT.BIT.bMSEBIS_CLR_INT_DMARX = field_value_rx;

        /* Set bit interrupt mask flag values for each chip 0,3 for CPU */
        field_value_tx = 0;
        field_value_rx = 0;
        for (cs = 0; cs < MSEBI_CS_COUNT; cs++)
        {
            field_value_tx = field_value_tx | (((uint8_t) intr_clear->eob_interrupt_cpu_tx[cs]) << cs);
            field_value_rx = field_value_rx | (((uint8_t) intr_clear->eob_interrupt_cpu_rx[cs]) << cs);
        }
        msebis_base_address->rMSEBIS_CLR_INT.BIT.bMSEBIS_CLR_INT_CPUTX = field_value_tx;
        msebis_base_address->rMSEBIS_CLR_INT.BIT.bMSEBIS_CLR_INT_CPURX = field_value_rx;

    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBIS_ClearInterrupt
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
 *
 *  Description:    Register callback function
 *
 **********************************************************************************************************************/
ER_RET MSEBIS_SetCallback (msebi_callback_mode_t callback_mode, uint8_t chip_sel, msebi_callback callback)
{
    ER_RET ret_val = ER_OK;

    switch(callback_mode)
    {
        case (TRANSMIT): tx_callback[chip_sel] = callback;
                         break;
        case (RECEIVE): rx_callback[chip_sel] = callback;
                         break;
        case (TRANSMIT_RECEIVE): tx_callback[chip_sel] = callback;
                                rx_callback[chip_sel] = callback;
                                break;
        default: ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBIS_SetCallback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_SetCPUEndOfBlockAddress
 *
 *  Return value:   Error status
 *
 *  Parameters:     chip_sel - The chip select to configure 0-3
 *                  eob_address - End of Block descriptor address, only bits 2 to 31 used. 32-bit aligned.
 *
 *  Description:    Sets the End of Block descriptor address for CPU access.
 *
 **********************************************************************************************************************/
ER_RET MSEBIS_SetCPUEndOfBlockAddress (uint8_t chip_sel, const uint32_t *eob_address)
{
    ER_RET ret_val = ER_OK;
    uint32_t *rMSEBIS_EOB_ADDR;

    /* Parameter Check */
    if ((eob_address == NULL) || (chip_sel >= MSEBI_CS_COUNT)) /* Chip select 0 and 3 supported. */
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Determine register address for each CPU chip select */
        rMSEBIS_EOB_ADDR = (uint32_t *) &msebis_base_address->rMSEBIS_EOB_ADDR.LONG;
        rMSEBIS_EOB_ADDR += (chip_sel * sizeof(uint32_t)); /* Seperated by 4 bytes. */

        *rMSEBIS_EOB_ADDR = ( *eob_address) & 0xFFFFFFFC; /* zero bits 0,1 */

        /* Save configuration */
        MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].eob_cpu_address = ( *eob_address) & 0xFFFFFFFC;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBIS_SetCPUEndOfBlockAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_GetCPUEndOfBlockAddress
 *
 *  Return value:   End of Block descriptor address for CPU access.
 *
 *  Parameters:     chip_sel - The chip select to configure 0-3
 *
 *  Description:    Returns End of Block descriptor address, only bits 2 to 31 used. 32-bit aligned.
 *
 **********************************************************************************************************************/
uint32_t MSEBIS_GetCPUEndOfBlockAddress (uint8_t chip_sel)
{
    return MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].eob_cpu_address;
}
/***********************************************************************************************************************
 End of function MSEBIS_GetCPUEndOfBlockAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_SetDMAEndOfBlockAddress
 *
 *  Return value:   Error status
 *
 *  Parameters:     chip_sel - The chip select to configure 0-3
 *                  eob_address - End of Block descriptor address, only bits 2 to 31 used. 32-bit aligned.
 *
 *  Description:    Sets the End of Block descriptor address for DMA access.
 *
 **********************************************************************************************************************/
ER_RET MSEBIS_SetDMAEndOfBlockAddress (uint8_t chip_sel, const uint32_t *eob_address)
{
    ER_RET ret_val = ER_OK;
    uint32_t *rMSEBIS_EOB_ADDR;

    /* Parameter Check */
    if ((eob_address == NULL) || (chip_sel >= MSEBI_CS_DMA_COUNT)) /* Chip select 0 and 1 supported for DMA. */
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Determine register address for each CPU chip select */
        rMSEBIS_EOB_ADDR = (uint32_t *) &msebis_base_address->rMSEBIS_EOB_ADDR.LONG;
        rMSEBIS_EOB_ADDR += ((chip_sel + 4) * sizeof(uint32_t)); /* Seperated by 4 bytes. Offset to skip 4 CPU registers */

        *rMSEBIS_EOB_ADDR = ( *eob_address) & 0xFFFFFFFC; /* zero bits 0,1 */

        /* Save configuration */
        MSEBIS_PARAMS.MSEBIS_CS_DMA_PARAM[chip_sel].eob_dma_address = ( *eob_address) & 0xFFFFFFFC;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBIS_SetDMAEndOfBlockAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_GetDMAEndOfBlockAddress
 *
 *  Return value:   End of Block descriptor address for DMA access.
 *
 *  Parameters:     chip_sel - The chip select to configure 0-3
 *
 *  Description:    Returns End of Block descriptor address, only bits 2 to 31 used. 32-bit aligned.
 *
 **********************************************************************************************************************/
uint32_t MSEBIS_GetDMAEndOfBlockAddress (uint8_t chip_sel)
{
    return MSEBIS_PARAMS.MSEBIS_CS_DMA_PARAM[chip_sel].eob_dma_address;
}
/***********************************************************************************************************************
 End of function MSEBIS_GetDMAEndOfBlockAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBI_SetCommonConfig
 *
 *  Return value:   Error status
 *
 *  Parameters:     mode - Master or Slave MSEBI
 *                  config - The configuration structure
 *
 *  Description:    Sets the user-defined master/slave configurations
 *
 **********************************************************************************************************************/
ER_RET MSEBI_SetCommonConfig (msebi_mode_t mode, void *config)
{
    ER_RET ret_val = ER_OK;
    msebim_config_t *master_config;
    msebis_config_t *slave_config;
    uint32_t *r_MSEBI_CONFIG;

    /* Parameter check */
    if (MSEBIMASTER == mode)
    {
        /* Master */
        master_config = (msebim_config_t *) config;
        if ((master_config->msebim_clk_low > MSEBIM_HCLK_4) || (master_config->msebim_clk_high > MSEBIM_HCLK_4)
                || (master_config->cpu_write_burst > MSEBIM_BURST_UNLIMITED)
                || (master_config->cpu_read_burst > MSEBIM_BURST_UNLIMITED))
        {
            ret_val = ER_PARAM;
        }
        else
        {
            r_MSEBI_CONFIG = (uint32_t *) &msebim_base_address->rMSEBIM_CONFIG.LONG;
            *r_MSEBI_CONFIG = (( *r_MSEBI_CONFIG) & (MSEBIM_CLK_ENABLE | 0xC0000000))
                    | /* Preserve clk enable and bits 30,31 */
                    (master_config->msebim_clk_low | (master_config->msebim_clk_high << 2)
                            | (master_config->cpu_write_burst << 5) | (master_config->cpu_read_burst << 8));

            /* Save configuration */
            MSEBIM_PARAMS.msebim_common_config = *master_config;
        }
    }
    else
    {
        /* Slave */
        slave_config = (msebis_config_t *) config;
        if ((slave_config->cpu_read_burst > MSEBIS_BURST_16_WORDS)
                || (slave_config->cpu_write_burst > MSEBIS_BURST_16_WORDS)
                || (slave_config->cfg_reg_timeout_delay_x4 > MSEBIS_MAX_TIMEOUT_DELAY))
        {
            ret_val = ER_PARAM;
        }
        else
        {
            r_MSEBI_CONFIG = (uint32_t *) &msebis_base_address->rMSEBIS_CONFIG.LONG;
            *r_MSEBI_CONFIG = (( *r_MSEBI_CONFIG) & 0xA0000000) /* Preserve bits 29,31 */
            | slave_config->cpu_read_burst | (slave_config->cpu_write_burst << 2) | (slave_config->buffer_data << 22)
                    | (slave_config->cache_data << 23) | (slave_config->cfg_reg_timeout_delay_x4 << 24);

            /* Save configuration */
            MSEBIS_PARAMS.msebis_common_config = *slave_config;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBI_SetCommonConfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIM_GetCommonConfig
 *
 *  Return value:   master common configuration
 *
 *  Parameters:     None.
 *
 *  Description:    Returns the master common configuration
 *
 **********************************************************************************************************************/
msebim_config_t MSEBIM_GetCommonConfig (void)
{
    MSEBIM_PARAMS.msebim_common_config.tx_fifo_data_level =
            msebim_base_address->rMSEBIM_CONFIG.BIT.bMSEBIM_CPU_TRANSMIT_FIFOLEVEL;
    MSEBIM_PARAMS.msebim_common_config.rx_fifo_data_level =
            msebim_base_address->rMSEBIM_CONFIG.BIT.bMSEBIM_CPU_RECEIVE_FIFOLEVEL;
    return MSEBIM_PARAMS.msebim_common_config;
}
/***********************************************************************************************************************
 End of function MSEBIM_GetCommonConfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_GetCommonConfig
 *
 *  Return value:   slave common configuration
 *
 *  Parameters:     None.
 *
 *  Description:    Returns the slave common configuration
 *
 **********************************************************************************************************************/
msebis_config_t MSEBIS_GetCommonConfig (void)
{
    MSEBIS_PARAMS.msebis_common_config.tx_fifo_data_level =
            msebis_base_address->rMSEBIS_CONFIG.BIT.bMSEBIS_CPUTX_FIFO_LVL;
    MSEBIS_PARAMS.msebis_common_config.rx_fifo_data_level =
            msebis_base_address->rMSEBIS_CONFIG.BIT.bMSEBIS_CPURX_FIFO_LVL;
    return MSEBIS_PARAMS.msebis_common_config;
}
/***********************************************************************************************************************
 End of function MSEBIS_GetCommonConfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIM_EnableDisableCLK
 *
 *  Return value:   None.
 *
 *  Parameters:     enable - true: enable clock generation, false: disable clock generation
 *
 *  Description:    Enables/Disables the MSEBIM clock generation
 *
 **********************************************************************************************************************/
void MSEBIM_EnableDisableCLK (bool enable)
{
    msebim_base_address->rMSEBIM_CONFIG.BIT.bMSEBIM_CLKENABLE = enable;
}
/***********************************************************************************************************************
 End of function MSEBIM_EnableDisableCLK
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIM_FlushCPUReceiveFIFO
 *
 *  Return value:   None.
 *
 *  Parameters:     Non.
 *
 *  Description:    Flush the CPU receive FIFO
 *
 **********************************************************************************************************************/
void MSEBIM_FlushCPUReceiveFIFO ()
{
    msebim_base_address->rMSEBIM_CPU_FIFOREAD_FLUSH.LONG = 0x808;
}
/***********************************************************************************************************************
 End of function MSEBIM_FlushCPUReceiveFIFO
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_GetIntStatus
 *
 *  Return value:   slave from cpu interrupt status
 *
 *  Parameters:     None.
 *
 *  Description:    Returns the slave from cpu interrupt status
 *
 **********************************************************************************************************************/
msebis_interrupt_status_t MSEBIS_GetIntStatus (void)
{
    unsigned long field_value_tx = 0;
    unsigned long field_value_rx = 0;
    int cs = 0;
    msebis_interrupt_status_t msebis_int_status;

    /* Extract bit interrupt flag values for each chip 0,1 for DMA */
    field_value_tx = msebis_base_address->rMSEBIS_STATUS_INT0.BIT.bMSEBIS_INT0_DMATX;
    field_value_rx = msebis_base_address->rMSEBIS_STATUS_INT0.BIT.bMSEBIS_INT0_DMARX;
    for (cs = 0; cs < MSEBI_CS_DMA_COUNT; cs++)
    {
        msebis_int_status.eob_detected_dma_tx[cs] = (field_value_tx & (1 << cs)) != 0;
        msebis_int_status.eob_detected_dma_rx[cs] = (field_value_rx & (1 << cs)) != 0;
    }

    /* Extract bit interrupt flag values for each chip 0,3 for CPU */
    field_value_tx = msebis_base_address->rMSEBIS_STATUS_INT0.BIT.bMSEBIS_INT0_CPUTX;
    field_value_rx = msebis_base_address->rMSEBIS_STATUS_INT0.BIT.bMSEBIS_INT0_CPURX;
    for (cs = 0; cs < MSEBI_CS_COUNT; cs++)
    {
        msebis_int_status.eob_detected_cpu_tx[cs] = (field_value_tx & (1 << cs)) != 0;
        msebis_int_status.eob_detected_cpu_rx[cs] = (field_value_rx & (1 << cs)) != 0;
    }

    return msebis_int_status;
}
/***********************************************************************************************************************
 End of function MSEBIS_GetIntStatus
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_GetMaskedIntStatus
 *
 *  Return value:   slave from cpu masked interrupt status
 *
 *  Parameters:     None.
 *
 *  Description:    Returns the slave from cpu masked interrupt status
 *
 **********************************************************************************************************************/
msebis_interrupt_status_t MSEBIS_GetMaskedIntStatus (void)
{
    unsigned long field_value_tx = 0;
    unsigned long field_value_rx = 0;
    int cs = 0;
    msebis_interrupt_status_t msebis_int_status;

    /* Extract bit masked interrupt flag values for each chip 0,1 for DMA */
    field_value_tx = msebis_base_address->rMSEBIS_STATUS_INT1.BIT.bMSEBIS_INT1_DMATX;
    field_value_rx = msebis_base_address->rMSEBIS_STATUS_INT1.BIT.bMSEBIS_INT1_DMARX;
    for (cs = 0; cs < MSEBI_CS_DMA_COUNT; cs++)
    {
        msebis_int_status.eob_detected_dma_tx[cs] = (field_value_tx & (1 << cs)) != 0;
        msebis_int_status.eob_detected_dma_rx[cs] = (field_value_rx & (1 << cs)) != 0;
    }

    /* Extract bit masked interrupt flag values for each chip 0,3 for CPU */
    field_value_tx = msebis_base_address->rMSEBIS_STATUS_INT1.BIT.bMSEBIS_INT1_CPUTX;
    field_value_rx = msebis_base_address->rMSEBIS_STATUS_INT1.BIT.bMSEBIS_INT1_CPURX;
    for (cs = 0; cs < MSEBI_CS_COUNT; cs++)
    {
        msebis_int_status.eob_detected_cpu_tx[cs] = (field_value_tx & (1 << cs)) != 0;
        msebis_int_status.eob_detected_cpu_rx[cs] = (field_value_rx & (1 << cs)) != 0;
    }

    return msebis_int_status;
}
/***********************************************************************************************************************
 End of function MSEBIS_GetMaskedIntStatus
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBI_GetCycleSize
 *
 *  Return value:   current cycle size params
 *
 *  Parameters:     mode - Master or Slave MSEBI
 *                  chip_sel - The chip select to configure
 *
 *  Description:    Returns the defined cycle sizes of the chip select
 *
 **********************************************************************************************************************/
msebi_cyclesize_t MSEBI_GetCycleSize (msebi_mode_t mode, uint8_t chip_sel)
{
    return (MSEBIMASTER == mode) ? MSEBIM_PARAMS.MSEBIM_CS_PARAM[chip_sel].cycle_size :
            MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].cycle_size;
}
/***********************************************************************************************************************
 End of function MSEBI_GetCycleSize
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBI_SetCycleSize
 *
 *  Return value:   Error status
 *
 *  Parameters:     mode - Master or Slave MSEBI
 *                  chip_sel - The chip select to configure
 *                  cycle_size - The cycle sizes of the phases
 *
 *  Description:    Sets the user-defined cycle sizes
 *
 **********************************************************************************************************************/
ER_RET MSEBI_SetCycleSize (msebi_mode_t mode, uint8_t chip_sel, msebi_cyclesize_t *cycle_size)
{
    ER_RET ret_val = ER_OK;
    uint32_t *rMSEBI_CYCLESIZE_CSn_N;
    msebi_cyclesize_t *save_to_ptr;

    /* Parameter Check */
    if (cycle_size == NULL)
    {
        ret_val = ER_PARAM;
    }
    else if ((cycle_size->write_dle_data_b > MSEBI_MAX_DLE_PHASE)
            || (cycle_size->read_dle_data_b > MSEBI_MAX_DLE_PHASE))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        rMSEBI_CYCLESIZE_CSn_N =
                (MSEBIMASTER == mode) ? (uint32_t *) &msebim_base_address->rMSEBIM_CYCLESIZE_CS0_N.LONG :
                        (uint32_t *) &msebis_base_address->rMSEBIS_CYCLESIZE_CS0_N.LONG;
        rMSEBI_CYCLESIZE_CSn_N += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));

        *rMSEBI_CYCLESIZE_CSn_N = (cycle_size->write_dle_data_nb << 24) | (cycle_size->read_dle_data_nb << 16)
                | (cycle_size->write_dle_data_b << 12) | (cycle_size->read_dle_data_b << 8)
                | (cycle_size->cle_data << 1) | cycle_size->ale_data;

        /* Save configuration */
        save_to_ptr =
                (MSEBIMASTER == mode) ? ( &MSEBIM_PARAMS.MSEBIM_CS_PARAM[chip_sel].cycle_size) :
                        ( &MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].cycle_size);
        *save_to_ptr = *cycle_size;

    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBI_SetCycleSize
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBI_GetSetupHold
 *
 *  Return value:   current setup and hold params
 *
 *  Parameters:     mode - Master or Slave MSEBI
 *                  chip_sel - The chip select to configure
 *
 *  Description:    Returns the defined setup and hold parameters of the chip select
 *
 **********************************************************************************************************************/
msebi_setuphold_t MSEBI_GetSetupHold (msebi_mode_t mode, uint8_t chip_sel)
{
    return (MSEBIMASTER == mode) ? MSEBIM_PARAMS.MSEBIM_CS_PARAM[chip_sel].setup_hold :
            MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].setup_hold;
}
/***********************************************************************************************************************
 End of function MSEBI_GetSetupHold
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBI_SetSetupHold
 *
 *  Return value:   Error status
 *
 *  Parameters:     mode - Master or Slave MSEBI
 *                  chip_sel - The chip select to configure
 *                  setup_hold - The setup and hold timings of the data phase
 *
 *  Description:    Sets the user-defined setup and hold timings
 *
 **********************************************************************************************************************/
ER_RET MSEBI_SetSetupHold (msebi_mode_t mode, uint8_t chip_sel, msebi_setuphold_t *setup_hold)
{
    ER_RET ret_val = ER_OK;
    uint32_t *rMSEBI_SETUPHOLD_CSn_N;
    msebi_setuphold_t *save_to_ptr;

    /* Parameter Check */
    if (setup_hold == NULL)
    {
        ret_val = ER_PARAM;
    }
    else if ((setup_hold->m_write_dle_hold > MSEBI_MAX_DLE_SETUP_HOLD)
            || (setup_hold->m_read_dle_hold > MSEBI_MAX_DLE_SETUP_HOLD)
            || (setup_hold->write_dle_setup > MSEBI_MAX_DLE_SETUP_HOLD)
            || ((setup_hold->write_dle_setup < MSEBIS_MIN_DLE_SETUP) && (MSEBISLAVE == mode))
            || (setup_hold->read_dle_setup > MSEBI_MAX_DLE_SETUP_HOLD)
            || ((setup_hold->read_dle_setup < MSEBIS_MIN_DLE_SETUP) && (MSEBISLAVE == mode)))
    {
        ret_val = ER_PARAM;
    }
    else
    {

        rMSEBI_SETUPHOLD_CSn_N =
                (MSEBIMASTER == mode) ? (uint32_t *) &msebim_base_address->rMSEBIM_SETUPHOLD_CS0_N.LONG :
                        (uint32_t *) &msebis_base_address->rMSEBIS_SETUPHOLD_CS0_N.LONG;
        rMSEBI_SETUPHOLD_CSn_N += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));

        *rMSEBI_SETUPHOLD_CSn_N = (setup_hold->m_write_dle_hold << 24) | (setup_hold->m_read_dle_hold << 16)
                | (setup_hold->write_dle_setup << 8) | setup_hold->read_dle_setup;

        /* Save configuration */
        save_to_ptr =
                (MSEBIMASTER == mode) ? ( &MSEBIM_PARAMS.MSEBIM_CS_PARAM[chip_sel].setup_hold) :
                        ( &MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].setup_hold);
        *save_to_ptr = *setup_hold;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBI_SetSetupHold
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBI_SetConfig
 *
 *  Return value:   Error status
 *
 *  Parameters:     mode - Master or Slave MSEBI
 *                  chip_sel - The chip select to configure
 *                  config - The configuration structure
 *
 *  Description:    Sets the user-defined master/slave chip select configurations
 *
 **********************************************************************************************************************/
ER_RET MSEBI_SetConfig (msebi_mode_t mode, uint8_t chip_sel, void *config)
{
    ER_RET ret_val = ER_OK;
    uint32_t *r_MSEBI_CONFIG_CSn_N;
    msebim_config_cs_t *master_config;
    msebis_config_cs_t *slave_config;

    /* Parameter check */
    if (MSEBIMASTER == mode)
    {
        /* Master */
        master_config = (msebim_config_cs_t *) config;
        if ((master_config->m_s_shared_config.trans_func > MSEBIM_TRANS_MAX)
                || (master_config->m_s_shared_config.wait_func > MSEBI_WAIT_CS0)
                || (master_config->m_s_shared_config.wait_func < MSEBI_WAIT_CSN)
                || (master_config->num_ale_used > MSEBIM_MAX_ALE) || (master_config->extend_addr > MSEBIM_EXT_ADR_MASK))
        {
            ret_val = ER_PARAM;
        }
        else
        {
            r_MSEBI_CONFIG_CSn_N = (uint32_t *) &msebim_base_address->rMSEBIM_CONFIG_CS0_N.LONG;
            r_MSEBI_CONFIG_CSn_N += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));
            uint32_t chip_config = *r_MSEBI_CONFIG_CSn_N;
            *r_MSEBI_CONFIG_CSn_N = (chip_config & 0x18) /* Preserve b3, b4 */
            | master_config->m_s_shared_config.trans_func
                    | ((master_config->wait_management ? master_config->m_s_shared_config.wait_func : 0) << 5)
                    | (master_config->m_s_shared_config.burst_enable << 7) | (master_config->num_ale_used << 8)
                    | (master_config->parallel_ale_mode << 11) | (master_config->m_s_shared_config.addr_route_cs1 << 12)
                    | (master_config->m_s_shared_config.addr_route_cs2 << 13)
                    | (master_config->m_s_shared_config.addr_route_cs3 << 14) | (master_config->multi_dle << 15)
                    | (master_config->extend_addr << 27);

            /* Save configuration */
            MSEBIM_PARAMS.MSEBIM_CS_PARAM[chip_sel].config = *master_config;
        }
    }
    else
    {
        /* Slave */
        slave_config = (msebis_config_cs_t *) config;
        if ((slave_config->m_s_shared_config.trans_func > MSEBIS_TRANS_MAX)
                ||
                //  (!(slave_config->m_s_shared_config.trans_func & 0x01)) ||
                (slave_config->m_s_shared_config.wait_func > MSEBI_WAIT_CS0)
                || (slave_config->m_s_shared_config.wait_func < MSEBI_WAIT_CSN))
        {
            ret_val = ER_PARAM;
        }
        else
        {
            r_MSEBI_CONFIG_CSn_N = (uint32_t *) &msebis_base_address->rMSEBIS_CONFIG_CS0_N.LONG;
            r_MSEBI_CONFIG_CSn_N += ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));
            uint32_t chip_config = *r_MSEBI_CONFIG_CSn_N;
            *r_MSEBI_CONFIG_CSn_N = (chip_config & 0x10) /* Preserve b4 */
            | slave_config->m_s_shared_config.trans_func | (slave_config->write_access << 3)
                    | (slave_config->m_s_shared_config.wait_func << 5)
                    | (slave_config->m_s_shared_config.burst_enable << 7) | (slave_config->mmu_addr_mode << 8)
                    | (slave_config->m_s_shared_config.addr_route_cs1 << 12)
                    | (slave_config->m_s_shared_config.addr_route_cs2 << 13)
                    | (slave_config->m_s_shared_config.addr_route_cs3 << 14);

            /* Save configuration */
            MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].config = *slave_config;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBI_SetConfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIM_GetConfig
 *
 *  Return value:   master chip select configuration
 *
 *  Parameters:     chip_sel - The chip select to obtain configuration of
 *
 *  Description:    Returns the master chip select specific configuration
 *
 **********************************************************************************************************************/
msebim_config_cs_t MSEBIM_GetConfig (uint8_t chip_sel)
{
    return MSEBIM_PARAMS.MSEBIM_CS_PARAM[chip_sel].config;
}
/***********************************************************************************************************************
 End of function MSEBIM_GetConfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_GetConfig
 *
 *  Return value:   slave chip select configuration
 *
 *  Parameters:     chip_sel - The chip select to obtain configuration of
 *
 *  Description:    Returns the slave chip select specific configuration
 *
 **********************************************************************************************************************/
msebis_config_cs_t MSEBIS_GetConfig (uint8_t chip_sel)
{
    return MSEBIS_PARAMS.MSEBIS_CS_PARAM[chip_sel].config;
}
/***********************************************************************************************************************
 End of function MSEBIS_GetConfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       MSEBIS_EnableDisableCS
 *
 *  Return value:   Error status
 *
 *  Parameters:     chip_sel - The chip select to configure
 *                  enable - true: enable chip select, false: disable chip select
 *
 *  Description:    Enables or disables the slave chip select
 *
 **********************************************************************************************************************/
void MSEBIS_EnableDisableCS (uint8_t chip_sel, bool enable)
{
    uint32_t *r_MSEBI_CONFIG_CSn_N;

    r_MSEBI_CONFIG_CSn_N = (uint32_t *) &msebis_base_address->rMSEBIS_CONFIG_CS0_N.LONG
            + ((chip_sel * MSEBI_CS_STRIDE) / sizeof(uint32_t));

    *r_MSEBI_CONFIG_CSn_N = enable ?
    /* Enable */
    (( *r_MSEBI_CONFIG_CSn_N) | MSEBIS_CS_ENABLE) :
    /* Disable */
    (( *r_MSEBI_CONFIG_CSn_N) & ( ~(uint32_t)MSEBIS_CS_ENABLE));
}
/***********************************************************************************************************************
 End of function MSEBIS_EnableDisableCS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function name: MSEBI_PinMux
 **********************************************************************************************************************/
ER_RET MSEBI_PinMux (bool master)
{
    ER_RET ret_val = ER_OK;

    /* First pin at 105. 14 sequential to match CN7 connection */
    if (master)
    {
        /* Master */
        iomux_pin_properties_t pin_mux =
        { .function = RZN1_FUNC_MSEBIM, .drive_strength = RZN1_MUX_DRIVE_4MA, .pull_level = RZN1_MUX_PULL_NONE };
        for (uint8_t pin = 105; pin <= 118; pin++)
        {
            R_IOMUX_PinCtrl(pin, IOMUX_CONTROL_SET_PIN_PROPERTIES, &pin_mux);
        }
    }
    else
    {
        /* Slave */
        iomux_pin_properties_t pin_mux =
        { .function = RZN1_FUNC_MSEBIS, .drive_strength = RZN1_MUX_DRIVE_4MA, .pull_level = RZN1_MUX_PULL_NONE };
        for (uint8_t pin = 105; pin <= 116; pin++)
        {
            R_IOMUX_PinCtrl(pin, IOMUX_CONTROL_SET_PIN_PROPERTIES, &pin_mux);
        }
        pin_mux.pull_level = RZN1_MUX_PULL_DOWN; /* Pull the two wait pins down to flag as not ready  */
        R_IOMUX_PinCtrl(117, IOMUX_CONTROL_SET_PIN_PROPERTIES, &pin_mux); /* MSEBIS_WAIT_N[0] */
        R_IOMUX_PinCtrl(118, IOMUX_CONTROL_SET_PIN_PROPERTIES, &pin_mux); /* MSEBIS_WAIT_N[1] */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function MSEBI_PinMux
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       handle_msebi_interrupt
 *
 *  Return value:   void
 *
 *  Parameters:     irq_num_ptr - Pointer to interrupt ID
 *
 *  Description:    Handles MSEBI interrupts.
 *
 **********************************************************************************************************************/
static void handle_msebi_interrupt (IRQn_Type *irq_num_ptr)
{
    unsigned long field_value_tx = 0;
    unsigned long field_value_rx = 0;
    msebi_mode_t mode = (*irq_num_ptr == RZN1_IRQ_MSEBIM) ? MSEBIMASTER : MSEBISLAVE;

    /* Extract bit interrupt flag values for each chip 0,3 for CPU */
    field_value_tx = msebis_base_address->rMSEBIS_STATUS_INT0.BIT.bMSEBIS_INT0_CPUTX;
    field_value_rx = msebis_base_address->rMSEBIS_STATUS_INT0.BIT.bMSEBIS_INT0_CPURX;
    for (uint8_t cs = 0; cs < MSEBI_CS_COUNT; cs++)
    {
        if((field_value_tx & (1 << cs)) != 0)
        {
            /* Callback function */
            if (FIT_NO_PTR != tx_callback[cs])
            {
                (tx_callback[cs])(mode);
            }
        }

        if((field_value_rx & (1 << cs)) != 0)
        {
            /* Callback function */
            if (FIT_NO_PTR != rx_callback[cs])
            {
                (rx_callback[cs])(mode);
            }
        }
    }
    MSEBIS_ClearInterrupt( &default_msebis_interrupt_clear);
    return;
}
/***********************************************************************************************************************
 End of function handle_msebi_interrupt
 **********************************************************************************************************************/
