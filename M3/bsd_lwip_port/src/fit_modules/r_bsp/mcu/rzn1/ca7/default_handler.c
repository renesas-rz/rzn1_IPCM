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
 * FILE         :  default_handler.c
 * Description  :  Default Handler
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "ca7.h"
#define message printf

//
// Dummy Interrupt Handlers
//
// The following functions are defined weakly to allow the user
// to override them at link time simply by declaring their own
// function of the same name.
//
// If no user function is provided, the weak function is used.
//
#pragma call_graph_root="interrupt"
__weak void Undefined_Handler(void)      { while(1); }
#pragma call_graph_root="interrupt"
__weak void SVC_Handler(void)            { while(1); }
#pragma call_graph_root="interrupt"
__weak void Prefetch_Handler(void)       { while(1); }
#pragma call_graph_root="interrupt"
__weak void Abort_Handler(void)
{ message("<Default Abort>\n"); exit(1);  }
//#pragma call_graph_root="interrupt"
//__weak void Hypervisor_Handler(void)     { while(1); }
#pragma call_graph_root="interrupt"
__weak void IRQ_Handler(void)
{ message("<Default IRQ>\n");   exit(1);  }
#pragma call_graph_root="interrupt"
__weak void FIQ_Handler(void)            { while(1); }
#pragma call_graph_root="interrupt"
__weak void Monitor_Handler(void)        {
  message("<MonitorMode> does not work well.\n");
  exit(1);
  /*
  uint32_t data;
  __asm volatile( LOAD_CP32(0,SCR) : "=r" (data) );
  data ^= 0x1;
  message("<MonitorMode> set SCR.NS bit to %x\n", (data&0x1));
  WRITE_CP32(data,SCR);
  */
}
