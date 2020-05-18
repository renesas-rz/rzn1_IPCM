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
 * $Revision: 1322 $
 * $Date: 2019-03-02 01:34:20 +0000 (Sat, 02 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  ddr_init.c
 * Description  :  DDR Init Definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#include "platform.h"
#include <stdint.h>
#ifdef CORE_CM3
#include "rzn1.h"
#else
#include "ca7.h"
#endif

#include "iodefine.h"
#include "common/common_api.h"
#include "ddr_ctrl.h"
#include "cdns_ddr_ctrl.h"

#define SYSCTRL             ((volatile SYSCTRL_Type *) 0x4000C000UL)
#define DDRC                ((volatile DDRC_Type *) 0x4000D000UL)
#define DDRPHY              ((volatile DDRPHY_Type *) 0x4000E000UL)

#define COUNT_100_US            625
#define DDR_START_ADDR          0x00000000

static void wait_x1us (uint32_t time /* us */)
{
#ifdef CORE_CM3
    SysTick->LOAD = COUNT_100_US * time / 100;
    SysTick->VAL = 0;                // clear
    SysTick->CTRL = 0x1;

    while( SysTick->VAL == 0 );
    while( SysTick->VAL != 1 );
#else // CA7
    uint32_t end_count;
    volatile uint32_t rdata1, rdata2;

    WRITE_CP32(1, CNTP_CTL);

    asm ( "MRRC p15, 0, %0, %1, c14" : "=r"(rdata1), "=r"(rdata2) );
    // CNTPCT
    // use only rdata1 (lower)
    end_count = rdata1 + (time * COUNT_100_US / 100); // time * 1 us
    while (rdata1 < end_count)
    {
        asm ( "MRRC p15, 0, %0, %1, c14" : "=r"(rdata1), "=r"(rdata2) );
        // CNTPCT
    }
#endif
}

void ddr_init ()
{
    uint32_t data;

    // enable clock always
    SYSCTRL->PWRCTRL_DDRC.BIT.CLKEN_B = 1;   // En_Clk_DDR
    SYSCTRL->PWRCTRL_DDRC.BIT.CLKEN_A = 1;   // En_Clk_FlexWAY_DDR net

    // Step 0 Soft reset assert

    // DDRC reset assert and deassert
    SYSCTRL->PWRCTRL_DDRC.BIT.MIREQ_A = 1;   // idle req assert
    while ( !SYSCTRL->PWRSTAT_DDRC.BIT.MIRACK_A)
        ; // wait ack
    while ( !SYSCTRL->PWRSTAT_DDRC.BIT.MISTAT_A)
        ; // wait idle
    SYSCTRL->PWRCTRL_DDRC.BIT.RSTN_A = 0;   // Reset_FlexWAY_DDR_n
    SYSCTRL->PWRCTRL_DDRC.BIT.RSTN_B = 0;   // Reset_Clk_DDR_n

#if defined(DDR2)
    DDRPHY->FUNCCTRL.LONG = 0x00200000; // Soft reset assert (PHY)
#else
    DDRPHY->FUNCCTRL.LONG = 0x00180100; // Soft reset assert (PHY)
#endif
    SYSCTRL->PWRCTRL_DDRC.BIT.RSTN_B = 1;   // Reset_Clk_DDR_n deassert
    SYSCTRL->PWRCTRL_DDRC.BIT.RSTN_A = 1;   // Reset_FlexWAY_DDR_n deassert
    SYSCTRL->PWRCTRL_DDRC.BIT.MIREQ_A = 0;   // idle req deassert

    while ( SYSCTRL->PWRSTAT_DDRC.BIT.MIRACK_A)
        ; // wait ack reset to 0
    while ( SYSCTRL->PWRSTAT_DDRC.BIT.MISTAT_A)
        ; // wait idle deassert

#if defined(DDR2)
    DDRPHY->DLLCTRL.LONG = 0x0000000D;
#else
    DDRPHY->DLLCTRL.LONG = 0x00000005;
#endif
    DDRPHY->ZQCALCTRL.LONG = 0x00000182;
#if defined(DDR2)
    DDRPHY->ZQODTCTRL.LONG = 0xAB330070;
    DDRPHY->RDCTRL.LONG = 0x94449443;
    DDRPHY->RDTMG.LONG = 0x000000A0;
#else
    DDRPHY->ZQODTCTRL.LONG = 0xAB330031;
    DDRPHY->RDCTRL.LONG = 0xB545B544;
    DDRPHY->RDTMG.LONG = 0x000000B0;
#endif
    DDRPHY->OUTCTRL.LONG = 0x020A0806;
#if defined(DDR2)
    DDRPHY->WLCTRL1.LONG = 0x80005C5D;
#else
    DDRPHY->WLCTRL1.LONG = 0x80005556;
#endif
    DDRPHY->DQCALOFS1.LONG = 0x00004545;

    // Step 9 MDLL reset release
#if defined(DDR2)
    DDRPHY->DLLCTRL.LONG = 0x0000000C;
#else
    DDRPHY->DLLCTRL.LONG = 0x00000004;
#endif

    // Step 12 Soft reset release
#if defined(DDR2)
    DDRPHY->FUNCCTRL.LONG = 0x00200001; // Soft reset assert (PHY)
#else
    DDRPHY->FUNCCTRL.LONG = 0x00180101; // Soft reset assert (PHY)
#endif

    // Step 13 FIFO pointer initialize
    DDRPHY->FIFOINIT.LONG = 0x00000101;

    // Step 14 Execute ZQ Calibration
    DDRPHY->ZQCALCTRL.LONG = 0x00000183;

    // Step 15 Wait for 200us or more, or wait for DFIINITCOMPLETE to be "1"
    do
    {
        data = DDRPHY->DLLCTRL.LONG;
    } while (0x04000000 != (data & 0x04000000));
    do
    {
        data = DDRPHY->ZQCALCTRL.LONG;
    } while (0x40000000 != (data & 0x40000000));

    // Step 16 ADD/CMD output setting
    DDRPHY->OUTCTRL.LONG = 0x020A0807;

    // Step 17 (DDR3) Wait for 200us or more(from MRESETB=0)
    // Step 21 (DDR2) Wait for 200us or more(from MCK start)
    wait_x1us(200);

    cdns_ddr_ctrl_init((uint32_t *) DDRC, 1 /*async*/, ddr_00_87, ddr_350_374,
    DDR_START_ADDR, DDR_SIZE);

    // Step 18 (DDR3) MRESETB=1 control (DFIRESETNP0/P1="1")
    // Step 19 (DDR3) wait for 500us or more
    // Step 20 (DDR3) wait tCKSRX
    // Step 22 MCKE=1
    cdns_ddr_ctrl_start((void *) DDRC);

    // Step 23 Wait tXPR (DDR3) (under 400ns)
    // Step 24 Wait for 400ns or more (DDR2)
    wait_x1us(1);

    // Step 26 (Set Write Leveling)
#if defined(DDR2)
    DDRPHY->WLCTRL1.LONG = 0x81005C5D;
#else
    DDRPHY->WLCTRL1.LONG = 0x81005556;
#endif
}

