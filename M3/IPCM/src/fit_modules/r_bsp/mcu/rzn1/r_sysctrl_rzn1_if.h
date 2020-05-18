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
 * $Revision: 1326 $
 * $Date: 2019-03-04 11:38:16 +0000 (Mon, 04 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE            :  r_sysctrl_rzn1_if.c
 * Description     :  System control interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef r_sysctrl_rzn1_if
#define r_sysctrl_rzn1_if

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
 Data Structures
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/
void R_SYSCTRL_EnableIOMUXLV2(void);
void R_SYSCTRL_EnableBGPIO(void);
void R_SYSCTRL_DisableBGPIO(void);
ER_RET R_SYSCTRL_SetSPIClkDivider(uint8_t clock_divider);
void R_SYSCTRL_EnableMSEBI(bool master);
void R_SYSCTRL_DisableMSEBI(bool master);
void R_SYSCTRL_EnableSPI(uint8_t chan_num);
void R_SYSCTRL_DisableSPI(uint8_t chan_num);
void R_SYSCTRL_EnableUART(uint8_t chan_num);
ER_RET R_SYSCTRL_SetUARTClkDivider(uint8_t clock_divider);
void R_SYSCTRL_DisableUART(uint8_t chan_num);
void R_SYSCTRL_EnableQSPI(uint8_t chan_num);
void R_SYSCTRL_DisableQSPI(uint8_t chan_num);
ER_RET R_SYSCTRL_ConfigDMAMux(uint8_t function_request);
ER_RET R_SYSCTRL_EnableADC(void);
ER_RET R_SYSCTRL_SetADCClkDivider(uint8_t clock_divider);
ER_RET R_SYSCTRL_DisableADC(void);
ER_RET R_SYSCTRL_EnableI2C(uint8_t chan_num);
ER_RET R_SYSCTRL_DisableI2C(uint8_t chan_num);
ER_RET R_SYSCTRL_SetI2CClkDivider(uint8_t i2c_clock_divider);
void R_SYSCTRL_EnableGMAC();
void R_SYSCTRL_DisableGMAC();
void R_SYSCTRL_Switch();
void R_SYSCTRL_EthReg();
void R_RIN_Reset();
ER_RET R_SYSCTRL_EnableDMA(uint8_t DMAC);
ER_RET R_SYSCTRL_DisableDMA(uint8_t DMAC);
ER_RET R_SYSCTRL_EnableSDIO(uint8_t sdio_instance);
ER_RET R_SYSCTRL_DisableSDIO(uint8_t sdio_instance);
ER_RET R_SYSCTRL_EnableUSBf(void);
void R_SYSCTRL_DisableUSBf(void);
ER_RET R_SYSCTRL_EnableUSBh(void);
void R_SYSCTRL_DisableUSBh(void);
void R_SYSCTRL_EnableTimer(void);
ER_RET R_SYSCTRL_EnableLCDC (uint8_t clock_divider);
ER_RET R_SYSCTRL_DisableLCDC (void);

void R_SYSCTRL_WDTResetConfig(bool reset_en);
void R_SYSCTRL_WDTReset(void);
void R_SYSCTRL_SystemReset(void);
ER_RET R_SYSCTRL_SetSDIOBaseClk(uint8_t sdio_instance);
uint32_t R_Get_CPUID(void);

void R_SYSCTRL_RTCReset(void);
ER_RET R_SYSCTRL_EnableRTC(void);
void R_SYSCTRL_DisableRTC(void);

ER_RET R_SYSCTRL_EnableCAN(void);
void R_SYSCTRL_DisableCAN(void);
void R_SYSCTRL_ResetCAN(void);

#endif
