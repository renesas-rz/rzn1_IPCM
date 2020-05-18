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
 *      PROJECT NAME :  RZ/N1 bare metal Drivers
 *      FILE         :  mcu_interrupts.h
 *      DESCRIPTION  :  private definitions for interrupt management functions
 *      MCU SERIES   :  RZ/N1 D, S & L
 *      CPU TYPE     :  ARM Cortex M3
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * $Revision: 1166 $
 * $Date: 2019-01-17 14:01:52 +0000 (Thu, 17 Jan 2019) $
 *
 * Description : This module allows for callbacks to be registered for interrupts.
 *
 **********************************************************************************************************************/
#ifndef MCU_INTERRUPTS_H__
#define MCU_INTERRUPTS_H__

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

void bsp_interrupts_open(void); /* r_bsp internal function to initialise interrupt management module */

#endif  /* MCU_INTERRUPTS_H__ */
