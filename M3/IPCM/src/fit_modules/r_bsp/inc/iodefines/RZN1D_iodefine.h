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
 * $Revision: 1301 $
 * $Date: 2019-02-25 14:29:43 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  RZN1D_iodefine.h
 * Description  :  Definition of Peripheral registers
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __RZN1D__IODEFINE_HEADER__
#define __RZN1D__IODEFINE_HEADER__

/* IO definitions (access restrictions to peripheral registers) */
#ifndef __I
  #ifdef __cplusplus
    #define  __I   volatile        /*!< defines 'read only' permissions     */
  #else
    #define  __I   volatile const  /*!< defines 'read only' permissions     */
  #endif
#endif
#ifndef __O
  #define    __O   volatile          /*!< defines 'write only' permissions    */
#endif
#ifndef __IO
  #define    __IO  volatile          /*!< defines 'read / write' permissions  */
#endif

#include "SYSCTRL_RZN1D_SFR.h"
#define SYSCTRL             ((volatile SYSCTRL_Type *) 0x4000C000UL)

#include "ADC_SFR.h"
#define ADC                 ((volatile ADC_Type *) 0x40065000UL)

#include "I2C_SFR.h"
#define I2C1                ((volatile I2C_Type *) 0x40063000UL)

#define I2C2                ((volatile I2C_Type *) 0x40064000UL)

#include "BGPIO_SFR.h"
#define BGPIO1              ((volatile BGPIO_Type *) 0x5000B000UL)

#define BGPIO2              ((volatile BGPIO_Type *) 0x5000C000UL)

#define BGPIO3              ((volatile BGPIO_Type *) 0x5000D000UL)

#include "DMAC_SFR.h"
#define DMAC1               ((volatile DMAC_Type *) 0x40104000UL)

#define DMAC2               ((volatile DMAC_Type *) 0x40105000UL)

#include "ETHACS_SFR.h"
#define ETHACS              ((volatile ETHACS_Type *) 0x44030000UL)

#include "Mailbox_SFR.h"
#define Mailbox             ((volatile Mailbox_Type *) 0x4000B000UL)

#define IPCM                ((volatile Mailbox_Type *) 0x4000B000UL)

#include "LCDC_SFR.h"
#define LCDC                ((volatile LCDC_Type *) 0x53004000UL)

#include "MSEBIM_SFR.h"
#define MSEBIM              ((volatile MSEBIM_Type *) 0x400C0000UL)

#include "MSEBIS_SFR.h"
#define MSEBIS              ((volatile MSEBIS_Type *) 0x400C2000UL)

#include "A5PSW_SFR.h"
#define A5PSW               ((volatile A5PSW_Type *) 0x44050000UL)

#include "WDOG_SFR.h"
#define WDOGA7_1            ((volatile WDOG_Type *) 0x40008000UL)

#define WDOGA7_2            ((volatile WDOG_Type *) 0x40009000UL)

#define WDOGM3              ((volatile WDOG_Type *) 0x4000A000UL)

#include "OTPC_SFR.h"
#define OTPC                ((volatile OTPC_Type *) 0x40007000UL)

#include "CFGS1_SFR.h"
#define CFGS1               ((volatile CFGS1_Type *) 0x40067000UL)

#include "CFGS2_SFR.h"
#define CFGS2               ((volatile CFGS2_Type *) 0x51000000UL)

#include "QSPI_SFR.h"
#define QSPI1               ((volatile QSPI_Type *) 0x40005000UL)

#include "NAND_SFR.h"
#define NAND                ((volatile NAND_Type *) 0x40102000UL)

#include "SDIO_SFR.h"
#define SDIO1               ((volatile SDIO_Type *) 0x40100000UL)

#define SDIO2               ((volatile SDIO_Type *) 0x40101000UL)

#include "RINACS_SFR.h"
#define RINACS              ((volatile RINACS_Type *) 0x400F2000UL)

#include "SEMAP_SFR.h"
#define SEMAP               ((volatile SEMAP_Type *) 0x53000000UL)

#include "ETHCAT_SFR.h"
#define ETHCAT              ((volatile ETHCAT_Type *) 0x44010000UL)

#include "SERCOSIII_SFR.h"
#define SERCOSIII           ((volatile SERCOSIII_Type *) 0x44020000UL)

#include "SPI_M_SFR.h"
#define SPI1                ((volatile SPI_M_Type *) 0x50005000UL)

#define SPI2                ((volatile SPI_M_Type *) 0x50006000UL)

#define SPI3                ((volatile SPI_M_Type *) 0x50007000UL)

#define SPI4                ((volatile SPI_M_Type *) 0x50008000UL)

#include "SPI_S_SFR.h"
#define SPI5                ((volatile SPI_S_Type *) 0x50009000UL)

#define SPI6                ((volatile SPI_S_Type *) 0x5000A000UL)

#include "GMAC1_SFR.h"
#define GMAC1               ((volatile GMAC1_Type *) 0x44000000UL)

#include "GMAC2_SFR.h"
#define GMAC2               ((volatile GMAC2_Type *) 0x44002000UL)

#include "TIMER_SFR.h"
#define TIMER1              ((volatile TIMER_Type *) 0x51001000UL)

#define TIMER2              ((volatile TIMER_Type *) 0x51002000UL)

#include "UART_r_SFR.h"
#define UART1               ((volatile UART_r_Type *) 0x40060000UL)

#define UART2               ((volatile UART_r_Type *) 0x40061000UL)

#define UART3               ((volatile UART_r_Type *) 0x40062000UL)

#include "UART_f_SFR.h"
#define UART4               ((volatile UART_f_Type *) 0x50000000UL)

#define UART5               ((volatile UART_f_Type *) 0x50001000UL)

#define UART6               ((volatile UART_f_Type *) 0x50002000UL)

#define UART7               ((volatile UART_f_Type *) 0x50003000UL)

#define UART8               ((volatile UART_f_Type *) 0x50004000UL)

#include "RTC_SFR.h"
#define RTC                 ((volatile RTC_Type *) 0x40006000UL)

#include "HSR_SFR.h"
#define HSR                 ((volatile HSR_Type *) 0x44040000UL)

#include "DDRC_SFR.h"
#define DDRC                ((volatile DDRC_Type *) 0x4000D000UL)

#include "DDRPHY_SFR.h"
#define DDRPHY              ((volatile DDRPHY_Type *) 0x4000E000UL)

#include "SRAM2MB_SFR.h"
#define SRAM2MB             ((volatile SRAM2MB_Type *) 0x400F3000UL)

#include "CAN_SFR.h"
#define CAN1                ((volatile CAN_Type *) 0x52104000UL)

#define CAN2                ((volatile CAN_Type *) 0x52105000UL)

#include "HWRTOS_GMAC_SFR.h"
#define HWRTOS_GMAC         ((volatile HWRTOS_GMAC_Type *) 0x400F0000UL)

#include "USB_HOST_SFR.h"
#define USB_HOST            ((volatile USB_HOST_Type *) 0x40020000UL)

#endif  /* End of __RZN1D__IODEFINE_HEADER__ */
