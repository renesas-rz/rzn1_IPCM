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
 * FILE         :  r_bsp.h
 * Description  :  Configures the driver for the RZN1S-DB board.
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef BSP_BOARD_RZN1SDB
#define BSP_BOARD_RZN1SDB

/* Make sure that no other platforms have already been defined. Do not touch this! */
#ifdef  PLATFORM_DEFINED
#error  "Error - Multiple platforms defined in platform.h!"
#else
#define PLATFORM_DEFINED
#endif

/***********************************************************************************************************************
INCLUDE APPROPRIATE MCU AND BOARD FILES
 **********************************************************************************************************************/
#include    "mcu/all/r_bsp_common.h"
#include    "r_bsp_config_reference.h"
#include    "mcu/rzn1/mcu_info.h"
#include    "mcu/rzn1/mcu_interrupts.h"
#include    "rzn1s-db.h"
#include    "hwsetup_s.h"
#include    "rzn1s-db-pinmux.h"
#include    "rzn1_dma_mux.h"
#include    "mcu/rzn1/rzn1.h"
#include    "mcu/rzn1/mcu_interrupts_if.h"

/* Declaration of uncached memory location*/
#if defined( __ICCARM__ )
  #define UNCACHED_BUFFER \
      _Pragma("location=\".dram0\"")
#else
  #define UNCACHED_BUFFER \
      __attribute__((section(".dram0")))
#endif

#define FB_BUFFER  __attribute__((section(".ram8M1")))

#endif /* BSP_BOARD_RZN1SDB */
