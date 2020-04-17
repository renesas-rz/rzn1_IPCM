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
 * FILE         :  mcu_info.h
 * Description  :  Information about the MCU on this board.
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef MCU_INFO
#define MCU_INFO

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
/* Gets MCU configuration information. */

/***********************************************************************************************************************
Macro definitions
 **********************************************************************************************************************/
/* MCU Series. */
#if   BSP_CFG_MCU_PART_SERIES == 0x0
    #define BSP_MCU_SERIES_RZN1    (1)
#else
    #error "ERROR - BSP_CFG_MCU_PART_SERIES - Unknown MCU Series chosen in r_bsp_config.h"
#endif

/* This macro means that this MCU is part of the RZN1x collection of MCUs (i.e. RZN1D, RZN1S, RZN1L). */
#define BSP_MCU_RZN1_ALL            (1)

/* MCU Group name. */
#if   BSP_CFG_MCU_PART_GROUP == 0x0
    #define BSP_MCU_RZN1D           (1)
#elif BSP_CFG_MCU_PART_GROUP == 0x1
    #define BSP_MCU_RZN1S           (1)
#elif BSP_CFG_MCU_PART_GROUP == 0x2
    #define BSP_MCU_RZN1L           (1)
#else
    #error "ERROR - BSP_CFG_MCU_PART_GROUP - Unknown MCU Group chosen in r_bsp_config.h"
#endif

/* Package. */
#if   BSP_CFG_MCU_PART_PACKAGE == 0x0
    #define BSP_PACKAGE_BGA400      (1)
    #define BSP_PACKAGE_PINS        (400)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x1
    #define BSP_PACKAGE_BGA324      (1)
    #define BSP_PACKAGE_PINS        (324)
#elif BSP_CFG_MCU_PART_PACKAGE == 0x2
    #define BSP_PACKAGE_BGA196      (1)
    #define BSP_PACKAGE_PINS        (196)
#else
    #error "ERROR - BSP_CFG_MCU_PART_PACKAGE - Unknown package chosen in r_bsp_config.h"
#endif

/* Memory size of your MCU. */
#if   BSP_CFG_MCU_PART_MEMORY_SIZE == 0x0
    #define BSP_ROM_SIZE_BYTES              (0)
    #define BSP_RAM_SIZE_BYTES              (2097152)
    #define BSP_DATA_FLASH_SIZE_BYTES       (0)
#else
    #error "ERROR - BSP_CFG_MCU_PART_MEMORY_SIZE - Unknown memory size chosen in r_bsp_config.h"
#endif

#endif /* MCU_INFO */

