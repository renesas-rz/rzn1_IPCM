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
 **       Definition of Peripheral registers
 **       for RZN1 ADC
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __ADC_SFR__DEFINE_HEADER__
#define __ADC_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : ADC
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : rADC_INTSTATUS0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC_INTSTATUS0_VC:16;                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_INTSTATUS0;
  union                                            /* Offset=0x0004 : rADC_INTSTATUS1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC_INTSTATUS1_VC:16;                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_INTSTATUS1;
  union                                            /* Offset=0x0008 : rADC_INTCLR */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bADC_INTCLR_VC:16;                          /* [15:0] */
      __O  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_INTCLR;
  union                                            /* Offset=0x000C : rADC_INTMASK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC_INTMASK_VC:16;                         /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_INTMASK;
  union                                            /* Offset=0x0010 : rADC_INTOVFSTATUS0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC_INTOVFSTATUS0_VC:16;                   /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_INTOVFSTATUS0;
  union                                            /* Offset=0x0014 : rADC_INTOVFSTATUS1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC_INTOVFSTATUS1_VC:16;                   /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_INTOVFSTATUS1;
  union                                            /* Offset=0x0018 : rADC_INTCLROVF */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bADC_INTCLROVF_VC:16;                       /* [15:0] */
      __O  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_INTCLROVF;
  union                                            /* Offset=0x001C : rADC_INTOVFMASK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC_INTOVFMASK_VC:16;                      /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_INTOVFMASK;
  union                                            /* Offset=0x0020 : rADC_PENDING */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC_PENDING_VC:16;                         /* [15:0] */
      __I  unsigned long   :14;                                        /* [29:16] */
      __I  unsigned long   bADC_DMA0_RUNNING:1;                        /* [30] */
      __I  unsigned long   bADC_DMA1_RUNNING:1;                        /* [31] */
    } BIT;
  } rADC_PENDING;
  union                                            /* Offset=0x0024 : rADC_PENDINGOVF */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC_PENDINGOVF_VC:16;                      /* [15:0] */
      __I  unsigned long   :14;                                        /* [29:16] */
      __I  unsigned long   bADC_DMA0_RUNNINGOVF:1;                     /* [30] */
      __I  unsigned long   bADC_DMA1_RUNNINGOVF:1;                     /* [31] */
    } BIT;
  } rADC_PENDINGOVF;
  union                                            /* Offset=0x0028 : rADC_PENDINGCLROVF */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bADC_PENDINGCLROVF_VC:16;                   /* [15:0] */
      __O  unsigned long   :14;                                        /* [29:16] */
      __O  unsigned long   bADC_DMA0_RUNNINGCLROVF:1;                  /* [30] */
      __O  unsigned long   bADC_DMA1_RUNNINGCLROVF:1;                  /* [31] */
    } BIT;
  } rADC_PENDINGCLROVF;
  union                                            /* Offset=0x002C : rADC_CONTROL */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC_VC_RUN:5;                              /* [4:0] */
      __I  unsigned long   bADC_VC_BUSY:1;                             /* [5] */
      __I  unsigned long   bADC_BUSY:1;                                /* [6] */
      __I  unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } rADC_CONTROL;
  union                                            /* Offset=0x0030 : rADC_FORCE */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC_FORCE_VC:16;                           /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_FORCE;
  union                                            /* Offset=0x0034 : rADC_SETFORCE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bADC_SETFORCE_VC:16;                        /* [15:0] */
      __O  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_SETFORCE;
  union                                            /* Offset=0x0038 : rADC_CLRFORCE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bADC_CLRFORCE_VC:16;                        /* [15:0] */
      __O  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_CLRFORCE;
  union                                            /* Offset=0x003C : rADC_PRIORITY */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC_Priority:5;                            /* [4:0] */
      __I  unsigned long   bADC_RR_Pointer:5;                          /* [9:5] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } rADC_PRIORITY;
  union                                            /* Offset=0x0040 : rADC_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC_SAMPLE_HOLD_ENABLE:3;                  /* [2:0] */
      __IO unsigned long   bADC_POWER_DOWN:1;                          /* [3] */
      __IO unsigned long   bADC_DMA:1;                                 /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rADC_CONFIG;
  char                     wk_0044[0x0068];
  union                                            /* Offset=0x00AC : rADC_ACQS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC_TSHSAMP:5;                             /* [4:0] */
      __IO unsigned long   bADC_TSHSET:2;                              /* [6:5] */
      __IO unsigned long   bADC_TSHOH:3;                               /* [9:7] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } rADC_ACQS;
  union                                            /* Offset=0x00B0 : rADC_MASKLOCK0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC_MASKLOCK:16;                           /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_MASKLOCK0;
  union                                            /* Offset=0x00B4 : rADC_MASKLOCK1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC_MASKLOCK:16;                           /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_MASKLOCK1;
  union                                            /* Offset=0x00B8 : rADC_MASKLOCK2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC_MASKLOCK:16;                           /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_MASKLOCK2;
  union                                            /* Offset=0x00BC : rADC_MASKLOCK3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC_MASKLOCK:16;                           /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rADC_MASKLOCK3;
  union                                            /* Offset=0x00C0 : rADC_VC0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC0;
  union                                            /* Offset=0x00C4 : rADC_VC1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC1;
  union                                            /* Offset=0x00C8 : rADC_VC2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC2;
  union                                            /* Offset=0x00CC : rADC_VC3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC3;
  union                                            /* Offset=0x00D0 : rADC_VC4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC4;
  union                                            /* Offset=0x00D4 : rADC_VC5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC5;
  union                                            /* Offset=0x00D8 : rADC_VC6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC6;
  union                                            /* Offset=0x00DC : rADC_VC7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC7;
  union                                            /* Offset=0x00E0 : rADC_VC8 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC8;
  union                                            /* Offset=0x00E4 : rADC_VC9 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC9;
  union                                            /* Offset=0x00E8 : rADC_VC10 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC10;
  union                                            /* Offset=0x00EC : rADC_VC11 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC11;
  union                                            /* Offset=0x00F0 : rADC_VC12 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC12;
  union                                            /* Offset=0x00F4 : rADC_VC13 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC13;
  union                                            /* Offset=0x00F8 : rADC_VC14 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC14;
  union                                            /* Offset=0x00FC : rADC_VC15 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bADC1_ChannelSel:3;                         /* [2:0] */
      __IO unsigned long   bADC2_ChannelSel:3;                         /* [5:3] */
      __IO unsigned long   bADC_Mode:2;                                /* [7:6] */
      __IO unsigned long   bADC_TrigSel:5;                             /* [12:8] */
      __IO unsigned long   bADC_TrigEnable:1;                          /* [13] */
      __IO unsigned long   bADC_Continuous:1;                          /* [14] */
      __IO unsigned long   bADC1_Enable:1;                             /* [15] */
      __IO unsigned long   bADC2_Enable:1;                             /* [16] */
      __IO unsigned long   bADC_DMA_Request:2;                         /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } rADC_VC15;
  union                                            /* Offset=0x0100 : rADC1_DATA0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA0;
  union                                            /* Offset=0x0104 : rADC1_DATA1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA1;
  union                                            /* Offset=0x0108 : rADC1_DATA2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA2;
  union                                            /* Offset=0x010C : rADC1_DATA3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA3;
  union                                            /* Offset=0x0110 : rADC1_DATA4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA4;
  union                                            /* Offset=0x0114 : rADC1_DATA5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA5;
  union                                            /* Offset=0x0118 : rADC1_DATA6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA6;
  union                                            /* Offset=0x011C : rADC1_DATA7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA7;
  union                                            /* Offset=0x0120 : rADC1_DATA8 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA8;
  union                                            /* Offset=0x0124 : rADC1_DATA9 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA9;
  union                                            /* Offset=0x0128 : rADC1_DATA10 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA10;
  union                                            /* Offset=0x012C : rADC1_DATA11 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA11;
  union                                            /* Offset=0x0130 : rADC1_DATA12 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA12;
  union                                            /* Offset=0x0134 : rADC1_DATA13 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA13;
  union                                            /* Offset=0x0138 : rADC1_DATA14 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA14;
  union                                            /* Offset=0x013C : rADC1_DATA15 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC1_DATA15;
#ifdef RZN1D
  union                                            /* Offset=0x0140 : rADC2_DATA0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA0;
  union                                            /* Offset=0x0144 : rADC2_DATA1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA1;
  union                                            /* Offset=0x0148 : rADC2_DATA2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA2;
  union                                            /* Offset=0x014C : rADC2_DATA3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA3;
  union                                            /* Offset=0x0150 : rADC2_DATA4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA4;
  union                                            /* Offset=0x0154 : rADC2_DATA5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA5;
  union                                            /* Offset=0x0158 : rADC2_DATA6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA6;
  union                                            /* Offset=0x015C : rADC2_DATA7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA7;
  union                                            /* Offset=0x0160 : rADC2_DATA8 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA8;
  union                                            /* Offset=0x0164 : rADC2_DATA9 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA9;
  union                                            /* Offset=0x0168 : rADC2_DATA10 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA10;
  union                                            /* Offset=0x016C : rADC2_DATA11 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA11;
  union                                            /* Offset=0x0170 : rADC2_DATA12 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA12;
  union                                            /* Offset=0x0174 : rADC2_DATA13 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA13;
  union                                            /* Offset=0x0178 : rADC2_DATA14 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA14;
  union                                            /* Offset=0x017C : rADC2_DATA15 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATA:12;                              /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATA_Update:1;                        /* [31] */
    } BIT;
  } rADC2_DATA15;
#else
  char                     wk_0140[0x0040];
#endif // RZN1D
  union                                            /* Offset=0x0180 : rADC1_DATALOCK0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK0;
  union                                            /* Offset=0x0184 : rADC1_DATALOCK1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK1;
  union                                            /* Offset=0x0188 : rADC1_DATALOCK2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK2;
  union                                            /* Offset=0x018C : rADC1_DATALOCK3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK3;
  union                                            /* Offset=0x0190 : rADC1_DATALOCK4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK4;
  union                                            /* Offset=0x0194 : rADC1_DATALOCK5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK5;
  union                                            /* Offset=0x0198 : rADC1_DATALOCK6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK6;
  union                                            /* Offset=0x019C : rADC1_DATALOCK7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK7;
  union                                            /* Offset=0x01A0 : rADC1_DATALOCK8 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK8;
  union                                            /* Offset=0x01A4 : rADC1_DATALOCK9 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK9;
  union                                            /* Offset=0x01A8 : rADC1_DATALOCK10 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK10;
  union                                            /* Offset=0x01AC : rADC1_DATALOCK11 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK11;
  union                                            /* Offset=0x01B0 : rADC1_DATALOCK12 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK12;
  union                                            /* Offset=0x01B4 : rADC1_DATALOCK13 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK13;
  union                                            /* Offset=0x01B8 : rADC1_DATALOCK14 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK14;
  union                                            /* Offset=0x01BC : rADC1_DATALOCK15 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC1_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC1_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC1_DATALOCK15;
#ifdef RZN1D
  union                                            /* Offset=0x01C0 : rADC2_DATALOCK0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK0;
  union                                            /* Offset=0x01C4 : rADC2_DATALOCK1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK1;
  union                                            /* Offset=0x01C8 : rADC2_DATALOCK2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK2;
  union                                            /* Offset=0x01CC : rADC2_DATALOCK3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK3;
  union                                            /* Offset=0x01D0 : rADC2_DATALOCK4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK4;
  union                                            /* Offset=0x01D4 : rADC2_DATALOCK5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK5;
  union                                            /* Offset=0x01D8 : rADC2_DATALOCK6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK6;
  union                                            /* Offset=0x01DC : rADC2_DATALOCK7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK7;
  union                                            /* Offset=0x01E0 : rADC2_DATALOCK8 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK8;
  union                                            /* Offset=0x01E4 : rADC2_DATALOCK9 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK9;
  union                                            /* Offset=0x01E8 : rADC2_DATALOCK10 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK10;
  union                                            /* Offset=0x01EC : rADC2_DATALOCK11 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK11;
  union                                            /* Offset=0x01F0 : rADC2_DATALOCK12 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK12;
  union                                            /* Offset=0x01F4 : rADC2_DATALOCK13 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK13;
  union                                            /* Offset=0x01F8 : rADC2_DATALOCK14 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK14;
  union                                            /* Offset=0x01FC : rADC2_DATALOCK15 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bADC2_DATALOCK:12;                          /* [11:0] */
      __I  unsigned long   :19;                                        /* [30:12] */
      __I  unsigned long   bADC2_DATALOCK_Update:1;                    /* [31] */
    } BIT;
  } rADC2_DATALOCK15;
#endif // RZN1D
} ADC_Type;
#endif  /* End of __ADC_SFR__DEFINE_HEADER__ */
