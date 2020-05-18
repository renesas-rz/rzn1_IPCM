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
 * FILE         :  common_api.h
 * Description  :  Common Definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __COMMON_API
#define __COMMON_API

#ifndef CPU_WRDW
#define CPU_WRDW( addr, data ) (*((volatile unsigned long long *)(unsigned long)(addr)) = ((unsigned long long)(data)))
#endif
#ifndef CPU_WRW
#define CPU_WRW( addr, data ) (*((volatile unsigned long  *)(unsigned long)(addr)) = ((unsigned long )(data)))
#endif
#ifndef CPU_WRH
#define CPU_WRH( addr, data ) (*((volatile unsigned short *)(unsigned long)(addr)) = ((unsigned short)(data)))
#endif
#ifndef CPU_WRB
#define CPU_WRB( addr, data ) (*((volatile unsigned char  *)(unsigned long)(addr)) = ((unsigned char )(data)))
#endif

#ifndef CPU_RDDW
#define CPU_RDDW( addr ) (*((volatile unsigned long long *)(unsigned long)(addr)))
#endif
#ifndef CPU_RDW
#define CPU_RDW( addr ) (*((volatile unsigned long  *)(unsigned long)(addr)))
#endif
#ifndef CPU_RDH
#define CPU_RDH( addr ) (*((volatile unsigned short *)(unsigned long)(addr)))
#endif
#ifndef CPU_RDB
#define CPU_RDB( addr ) (*((volatile unsigned char  *)(unsigned long)(addr)))
#endif

#endif /* End of __COMMON_API */
