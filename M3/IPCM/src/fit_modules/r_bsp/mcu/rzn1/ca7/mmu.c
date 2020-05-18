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
 * $Revision: 1310 $
 * $Date: 2019-02-28 16:41:33 +0000 (Thu, 28 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  mmu.c
 * Description  :  Memory Management Unit Implementation
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#include <stdint.h>
#include "common/common_api.h"
#include <intrinsics.h>
#include "platform.h"

// Cacheable memory (without TEX remap).
// outer: (Write-Back, no Write-Allocate Cacheable).
// inner: (Write-Through, no Write-Allocate Cacheable).
#define RAM_WT     0x7C0A

// Cacheable memory (without TEX remap), Write-Back,Write-Allocate
#define RAM     0x7C0E // for Write-Back, no Write-Allocate

// Stronly ordered.
#define DEVICE  0x0c06
#define TTBR0_WRITE(ttb)  __MCR(15,0,ttb,2,0,0)

// see linker file for section constrains.
#pragma section="MMU"
uint32_t * const ttb = (uint32_t *) __section_begin("MMU");

#ifdef RZN1S
__weak void set_mmu(void)
{
    // Write section number & attributes [4K * 1MB].
    for (uint32_t i = 0; i < 0x1000; ++i)
    {
        if (((i >= 0x040) && (i < 0x041)) || // IRAM
            ((i >= 0x800) && (i < 0x803)))// RAM/QSPI-2
        {
            ttb[i] = (i << 20) | RAM;
        }
        else if (((i >= 0x200) && (i < 0x201)) ||// Data
                ((i >= 0x100) && (i < 0x200)) || // QSPI
                ((i >= 0x803) && (i < 0x804)))
        {
            ttb[i] = (i << 20) | RAM_WT;
        }
        else
        {
            ttb[i] = (i << 20) | DEVICE;
        }
    }

    // Use TTB0
    __MCR(15, 0, 0, 2, 0, 2);
    // Set level 1 page table.
    TTBR0_WRITE((uint32_t )ttb | 8);
}
#endif

#ifdef RZN1D
__weak void set_mmu(void)
{
    // Write section number & attributes [4K * 1MB].
    for (uint32_t i = 0; i < 0x1000; ++i)
    {
        if ( ((i >= 0x040) && (i < 0x041)) || // IRAM
                ((i >= 0x800) && (i < 0x803)))// RAM/QSPI-2
        {
            ttb[i] = (i << 20) | RAM;
        }
        else if (((i >= 0x200) && (i < 0x201)) || // Data
                ((i >= 0x100) && (i < 0x200)))// QSPI
        {
            ttb[i] = (i << 20) | RAM_WT;            //Un-Cached
        }
        else
        {
            ttb[i] = (i << 20) | DEVICE;
        }
    }

    // Use TTB0
    __MCR(15, 0, 0, 2, 0, 2);
    // Set level 1 page table.
    TTBR0_WRITE((uint32_t )ttb | 8);
}
#endif
