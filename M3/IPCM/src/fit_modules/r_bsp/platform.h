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
 * FILE         :  platform.h
 * Description  :  The user chooses which MCU and board they are developing for in this file. If the board you are using
 *                 is not listed below, please add your own or use the default 'User Board'.
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef PLATFORM_H
#define PLATFORM_H

/***********************************************************************************************************************
 DEFINE YOUR SYSTEM - UNCOMMENT THE INCLUDE PATH FOR THE PLATFORM YOU ARE USING.
 **********************************************************************************************************************/
#ifdef BSP_PLAT_RZN1DDB
/* rzn1d-db */
#define RZN1D /* used by iodefine.h to select platform includes */
#include "./board/rzn1d-db/r_bsp.h"
#endif

#ifdef BSP_PLAT_RZN1SDB
/* rzn1s-db */
#define RZN1S /* used by iodefine.h to select platform includes */
#include "./board/rzn1s-db/r_bsp.h"
#endif

#ifdef BSP_PLAT_RZN1LDB
/* rzn1l-db */
#define RZN1L /* used by iodefine.h to select platform includes */
#include "./board/rzn1l-db/r_bsp.h"
#endif

#include "./inc/errcodes.h"

/***********************************************************************************************************************
 MAKE SURE AT LEAST ONE PLATFORM WAS DEFINED - DO NOT EDIT BELOW THIS POINT
 **********************************************************************************************************************/
#ifndef PLATFORM_DEFINED
#error  "Error - No platform defined in platform.h!"
#endif

/* This macro is used to suppress compiler messages about a parameter not being used in a function */
#define INTERNAL_NOT_USED(p)        ((void)(p))

/* Null argument definitions */
#define FIT_NO_FUNC ((void (*)(void *))0x10000000)
#define FIT_NO_PTR                  ((void *)0)

#endif /* PLATFORM_H */

