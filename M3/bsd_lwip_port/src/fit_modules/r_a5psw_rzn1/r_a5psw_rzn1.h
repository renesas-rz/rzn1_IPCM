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
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_a5psw_rzn1.h
 * Description  :  A5PSW driver definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_A5PSW_RZN1__
#define R_A5PSW_RZN1__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_gmac_rzn1_if.h"

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define EN_SPEED_1G            (0x0100081B)
#define EN_SPEED_100M_10M      (0x01000813)
#define DISABLE_SWITCH         (0x01000810)
#define ENABLE_PORT(port_num)   ((uint32_t) (0x10001 << port_num))

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
void switch_GetVersion (void *buf);
void switch_init (void);
ER_RET switch_open (uint8_t port);
ER_RET switch_close (uint8_t port);
ER_RET switch_speedconfig (uint8_t port, gmac_operation_mode_t speed);

#endif /* R_A5PSW_RZN1__ */
