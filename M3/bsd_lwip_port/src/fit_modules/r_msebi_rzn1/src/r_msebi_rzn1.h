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
 * $Revision: 1231 $
 * $Date: 2019-02-07 16:51:47 +0000 (Thu, 07 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_msebi_rzn1.h
 * Description  :  MSEBI driver definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_MSEBI_RZN1_H__
#define R_MSEBI_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "./inc/iodefines/MSEBIM_SFR.h"
#include "./inc/iodefines/MSEBIS_SFR.h"
#include "r_msebi_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define MSEBI_CS_STRIDE                      (0x100)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function prototypes
 **********************************************************************************************************************/
void MSEBI_Init (void);
ER_RET MSEBI_Open (bool master);
void MSEBI_Close (bool master);
ER_RET MSEBI_PinMux (bool master);

ER_RET MSEBI_SetCommonConfig (msebi_mode_t mode, void *config);
msebim_config_t MSEBIM_GetCommonConfig (void);
msebis_config_t MSEBIS_GetCommonConfig (void);
void MSEBIM_EnableDisableCLK (bool enable);
void MSEBIM_FlushCPUReceiveFIFO (void);

ER_RET MSEBI_SetCycleSize (msebi_mode_t mode, uint8_t chip_sel, msebi_cyclesize_t *cycle_size);
msebi_cyclesize_t MSEBI_GetCycleSize (msebi_mode_t mode, uint8_t chip_sel);
ER_RET MSEBI_SetSetupHold (msebi_mode_t mode, uint8_t chip_sel, msebi_setuphold_t *setup_hold);
msebi_setuphold_t MSEBI_GetSetupHold (msebi_mode_t mode, uint8_t chip_sel);
ER_RET MSEBI_SetConfig (msebi_mode_t mode, uint8_t chip_sel, void *config);
msebim_config_cs_t MSEBIM_GetConfig (uint8_t chip_sel);
msebis_config_cs_t MSEBIS_GetConfig (uint8_t chip_sel);
void MSEBIS_EnableDisableCS (uint8_t chip_sel, bool enable);

ER_RET MSEBIM_SetDMAControl (msebi_dma_access_t access, uint8_t chip_sel, msebim_dma_control_cs_t *dma_control);
msebim_dma_control_cs_t MSEBIM_GetDMAControl (msebi_dma_access_t access, uint8_t chip_sel);

ER_RET MSEBI_SetDMADataLevel (msebi_mode_t mode, msebi_dma_access_t access, uint8_t chip_sel, void *config);
msebim_dma_datalevel_cs_t MSEBIM_GetDMADataLevel (msebi_dma_access_t access, uint8_t chip_sel);
msebis_dma_datalevel_cs_t MSEBIS_GetDMADataLevel (msebi_dma_access_t access, uint8_t chip_sel);

ER_RET MSEBIM_SetDMABlockAddress (msebi_dma_access_t access, uint8_t chip_sel,
        const msebim_dma_block_address_cs_t *dma_address);
msebim_dma_block_address_cs_t MSEBIM_GetDMABlockAddress (msebi_dma_access_t access, uint8_t chip_sel);
uint32_t MSEBIM_GetDMACurrentAddress (msebi_dma_access_t access, uint8_t chip_sel);

ER_RET MSEBIS_SetMMUBaseAddress (uint8_t chip_sel, const uint32_t *mmu_address);
uint32_t MSEBIS_GetMMUBaseAddress (uint8_t chip_sel);
ER_RET MSEBIS_SetMMUBaseAddressMask (uint8_t chip_sel, const uint32_t *mmu_address_mask);
uint32_t MSEBIS_GetMMUBaseAddressMask (uint8_t chip_sel);

ER_RET MSEBIS_SetDMARequest (msebi_dma_access_t access, uint8_t chip_sel, const msebis_dma_request_cs_t *dma_request);
msebis_dma_request_cs_t MSEBIS_GetDMARequest (msebi_dma_access_t access, uint8_t chip_sel);

msebis_interrupt_status_t MSEBIS_GetIntStatus (void);
msebis_interrupt_status_t MSEBIS_GetMaskedIntStatus (void);

ER_RET MSEBIS_SetInterruptMask (const msebis_interrupt_control_t *intr_mask);
msebis_interrupt_control_t MSEBIS_GetInterruptMask ();

ER_RET MSEBIS_ClearInterrupt (const msebis_interrupt_control_t *intr_clear);
ER_RET MSEBIS_SetCallback (msebi_callback_mode_t callback_mode, uint8_t chip_sel, msebi_callback callback);

ER_RET MSEBIS_SetCPUEndOfBlockAddress (uint8_t chip_sel, const uint32_t *address);
uint32_t MSEBIS_GetCPUEndOfBlockAddress (uint8_t chip_sel);
ER_RET MSEBIS_SetDMAEndOfBlockAddress (uint8_t chip_sel, const uint32_t *address);
uint32_t MSEBIS_GetDMAEndOfBlockAddress (uint8_t chip_sel);

#endif /* R_MSEBI_RZN1_H__ */
