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
 * $Revision: 1195 $
 * $Date: 2019-01-29 12:51:05 +0000 (Tue, 29 Jan 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_wdt_rzn1.h
 * Description  :  WDT control functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef R_WDT_RZN1_H__
#define R_WDT_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/
uint8_t wdt_get_major_version_num (void);
uint8_t wdt_get_minor_version_num (void);

ER_RET wdt_init (void);
ER_RET wdt_uninit (void);

void wdt_setoutput (WDT_OUTPUT output);
ER_RET wdt_setcallback (wdt_callback call_back);

ER_RET wdt_enable (WDT_PRESCALER prescaler, uint16_t reload_val);
ER_RET wdt_retrigger (void);

#endif /* R_WDT_RZN1_H__ */
