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
 * $Revision: 1166 $
 * $Date: 2019-01-17 14:01:52 +0000 (Thu, 17 Jan 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  rzn1.h
 * Description  :  Cortex M3 definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
#ifndef __RZN1_H
#define __RZN1_H

#ifdef __cplusplus
extern "C" {
#endif
/***********************************************************************************************************************
 Exceptions
 **********************************************************************************************************************/
#define   NonMaskableInt_IRQn       (-14)       /*  2 Non Maskable Interrupt                */
#define   MemoryManagement_IRQn     (-12)       /* 4 Cortex-M3 Memory Management Interrupt  */
#define   BusFault_IRQn             ( -11)      /*  5 Cortex-M3 Bus Fault Interrupt         */
#define   UsageFault_IRQn           ( -10)      /*  6 Cortex-M3 Usage Fault Interrupt       */
#define   SVCall_IRQn               (-5)        /* 11 Cortex-M3 SV Call Interrupt           */
#define   DebugMonitor_IRQn         ( -4)       /* 12 Cortex-M3 Debug Monitor Interrupt     */
#define   PendSV_IRQn               (-2)        /* 14 Cortex-M3 Pend SV Interrupt           */
#define   SysTick_IRQn              ( -1)       /*15 Cortex-M3 System Tick Interrupt        */

/***********************************************************************************************************************
 Processor and Core Peripheral Section
 **********************************************************************************************************************/
/* Configuration of the Cortex-M3 Processor and Core Peripherals */
#define __MPU_PRESENT             1         /* MPU present or not                           */
#define __NVIC_PRIO_BITS          4         /* Number of Bits used for Priority Levels      */
#define __Vendor_SysTickConfig    0         /*Set to 1 if different SysTick Config is used  */

/***********************************************************************************************************************
 Memory map
 **********************************************************************************************************************/
/* Code region */
#define CODE_BASE           (0x00000000UL)

/* SRAM region */
#define SRAM_BASE           (0x20000000UL)

typedef uint32_t IRQn_Type;

#ifdef CORE_CM3
#include "core_cm3.h"                   /* Cortex-M3 processor and core peripherals            */
#include "rzn1-irq-cm3.h"
#endif
#ifdef CORE_CA7
#include "core_ca.h"                    /* Cortex-A processor and core peripherals             */
#include "rzn1-irq-ca7.h"
#endif

#include "system_RZN1.h"                /* RZN1 system                                         */
#include "rzn1-memory-map.h"
#ifdef __cplusplus
}
#endif

#endif  /* __RZN1_H */
