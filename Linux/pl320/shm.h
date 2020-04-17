/**********************************************************************************************************************
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
* $Revision: 1.00
* $Date: 2020-05-01 12:00:00 +0000 (Fri, 1 May 2020) $
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/
/********************************************************************************
Includes
********************************************************************************/
//$REA FIX
//#include "~/rzn_dev_setup/rzn1_linux-4.19_bsp/output/buildroot-2019.02.6/output/host/arm-buildroot-linux-gnueabihf/sysroot/usr/include/sys/mman.h"
#include <sys/mman.h>

/********************************************************************************
Defines
********************************************************************************/
/* Memory regions: M3->A7 = 0x200fc000, A7->M3 = 0x200f8000. */
#define SHM_ADDRESS 0x200F8000
#define SHM_SIZE 0x8000UL
#define MAP_MASK (SHM_SIZE- 1)
#define UNUSED(x) (void)(x)

/********************************************************************************
Types, structs
********************************************************************************/
/********************************************************************************
Global variables
********************************************************************************/
/********************************************************************************
Externals
********************************************************************************/
void *init_shm_A7_to_M3(off_t shm_address, int shm_size);
void *init_shm_M3_to_A7(void);
void write_to_shm(int cnt, void *addr, int shm_region_size_bytes);
void read_from_shm(void *addr);
void check_memory(unsigned int ipcm_d1, unsigned int ipcm_d2, unsigned int shm_size_bytes, void *shared_ram);
