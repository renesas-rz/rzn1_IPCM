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
 * Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * $Revision: 735 $
 * $Date: 2018-09-20 10:33:05 +0100 (Thu, 20 Sep 2018) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_lcdc_rzn1_config.h
 * Description  :  Configures the LCDC module.
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2018. All Rights Reserved
 **********************************************************************************************************************/

#ifndef LCDC_RZN1_CONFIG_HEADER_FILE
#define LCDC_RZN1_CONFIG_HEADER_FILE

/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/
/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING
 Available settings:
 BSP_CFG_PARAM_CHECKING_ENABLE:
 Utilizes the system default setting
 1:
 Includes parameter checking
 0:
 Compiles out parameter checking
 */
#define LCDC_CFG_PARAM_CHECKING_ENABLE      (BSP_CFG_PARAM_CHECKING_ENABLE)

#define MAX_LCDC_PORTS   1

#define LCD_DEFAULT_INT_PRIORITY           (11u)


#endif /* LCDC_RZN1_CONFIG_HEADER_FILE */
