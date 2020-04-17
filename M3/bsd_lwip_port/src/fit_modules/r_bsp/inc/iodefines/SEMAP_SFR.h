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
 **       for RZN1 SEMAP
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __SEMAP_SFR__DEFINE_HEADER__
#define __SEMAP_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : SEMAP
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : rSemaphoreLockCPU1_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_0;
  union                                            /* Offset=0x0004 : rSemaphoreStatusCPU1_0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_0;
  char                     wk_0008[0x0008];
  union                                            /* Offset=0x0010 : rSemaphoreLockCPU1_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_1;
  union                                            /* Offset=0x0014 : rSemaphoreStatusCPU1_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_1;
  char                     wk_0018[0x0008];
  union                                            /* Offset=0x0020 : rSemaphoreLockCPU1_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_2;
  union                                            /* Offset=0x0024 : rSemaphoreStatusCPU1_2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_2;
  char                     wk_0028[0x0008];
  union                                            /* Offset=0x0030 : rSemaphoreLockCPU1_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_3;
  union                                            /* Offset=0x0034 : rSemaphoreStatusCPU1_3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_3;
  char                     wk_0038[0x0008];
  union                                            /* Offset=0x0040 : rSemaphoreLockCPU1_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_4;
  union                                            /* Offset=0x0044 : rSemaphoreStatusCPU1_4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_4;
  char                     wk_0048[0x0008];
  union                                            /* Offset=0x0050 : rSemaphoreLockCPU1_5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_5;
  union                                            /* Offset=0x0054 : rSemaphoreStatusCPU1_5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_5;
  char                     wk_0058[0x0008];
  union                                            /* Offset=0x0060 : rSemaphoreLockCPU1_6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_6;
  union                                            /* Offset=0x0064 : rSemaphoreStatusCPU1_6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_6;
  char                     wk_0068[0x0008];
  union                                            /* Offset=0x0070 : rSemaphoreLockCPU1_7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_7;
  union                                            /* Offset=0x0074 : rSemaphoreStatusCPU1_7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_7;
  char                     wk_0078[0x0008];
  union                                            /* Offset=0x0080 : rSemaphoreLockCPU1_8 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_8;
  union                                            /* Offset=0x0084 : rSemaphoreStatusCPU1_8 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_8;
  char                     wk_0088[0x0008];
  union                                            /* Offset=0x0090 : rSemaphoreLockCPU1_9 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_9;
  union                                            /* Offset=0x0094 : rSemaphoreStatusCPU1_9 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_9;
  char                     wk_0098[0x0008];
  union                                            /* Offset=0x00A0 : rSemaphoreLockCPU1_10 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_10;
  union                                            /* Offset=0x00A4 : rSemaphoreStatusCPU1_10 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_10;
  char                     wk_00A8[0x0008];
  union                                            /* Offset=0x00B0 : rSemaphoreLockCPU1_11 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_11;
  union                                            /* Offset=0x00B4 : rSemaphoreStatusCPU1_11 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_11;
  char                     wk_00B8[0x0008];
  union                                            /* Offset=0x00C0 : rSemaphoreLockCPU1_12 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_12;
  union                                            /* Offset=0x00C4 : rSemaphoreStatusCPU1_12 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_12;
  char                     wk_00C8[0x0008];
  union                                            /* Offset=0x00D0 : rSemaphoreLockCPU1_13 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_13;
  union                                            /* Offset=0x00D4 : rSemaphoreStatusCPU1_13 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_13;
  char                     wk_00D8[0x0008];
  union                                            /* Offset=0x00E0 : rSemaphoreLockCPU1_14 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_14;
  union                                            /* Offset=0x00E4 : rSemaphoreStatusCPU1_14 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_14;
  char                     wk_00E8[0x0008];
  union                                            /* Offset=0x00F0 : rSemaphoreLockCPU1_15 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_15;
  union                                            /* Offset=0x00F4 : rSemaphoreStatusCPU1_15 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_15;
  char                     wk_00F8[0x0008];
  union                                            /* Offset=0x0100 : rSemaphoreLockCPU1_16 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_16;
  union                                            /* Offset=0x0104 : rSemaphoreStatusCPU1_16 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_16;
  char                     wk_0108[0x0008];
  union                                            /* Offset=0x0110 : rSemaphoreLockCPU1_17 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_17;
  union                                            /* Offset=0x0114 : rSemaphoreStatusCPU1_17 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_17;
  char                     wk_0118[0x0008];
  union                                            /* Offset=0x0120 : rSemaphoreLockCPU1_18 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_18;
  union                                            /* Offset=0x0124 : rSemaphoreStatusCPU1_18 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_18;
  char                     wk_0128[0x0008];
  union                                            /* Offset=0x0130 : rSemaphoreLockCPU1_19 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_19;
  union                                            /* Offset=0x0134 : rSemaphoreStatusCPU1_19 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_19;
  char                     wk_0138[0x0008];
  union                                            /* Offset=0x0140 : rSemaphoreLockCPU1_20 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_20;
  union                                            /* Offset=0x0144 : rSemaphoreStatusCPU1_20 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_20;
  char                     wk_0148[0x0008];
  union                                            /* Offset=0x0150 : rSemaphoreLockCPU1_21 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_21;
  union                                            /* Offset=0x0154 : rSemaphoreStatusCPU1_21 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_21;
  char                     wk_0158[0x0008];
  union                                            /* Offset=0x0160 : rSemaphoreLockCPU1_22 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_22;
  union                                            /* Offset=0x0164 : rSemaphoreStatusCPU1_22 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_22;
  char                     wk_0168[0x0008];
  union                                            /* Offset=0x0170 : rSemaphoreLockCPU1_23 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_23;
  union                                            /* Offset=0x0174 : rSemaphoreStatusCPU1_23 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_23;
  char                     wk_0178[0x0008];
  union                                            /* Offset=0x0180 : rSemaphoreLockCPU1_24 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_24;
  union                                            /* Offset=0x0184 : rSemaphoreStatusCPU1_24 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_24;
  char                     wk_0188[0x0008];
  union                                            /* Offset=0x0190 : rSemaphoreLockCPU1_25 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_25;
  union                                            /* Offset=0x0194 : rSemaphoreStatusCPU1_25 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_25;
  char                     wk_0198[0x0008];
  union                                            /* Offset=0x01A0 : rSemaphoreLockCPU1_26 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_26;
  union                                            /* Offset=0x01A4 : rSemaphoreStatusCPU1_26 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_26;
  char                     wk_01A8[0x0008];
  union                                            /* Offset=0x01B0 : rSemaphoreLockCPU1_27 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_27;
  union                                            /* Offset=0x01B4 : rSemaphoreStatusCPU1_27 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_27;
  char                     wk_01B8[0x0008];
  union                                            /* Offset=0x01C0 : rSemaphoreLockCPU1_28 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_28;
  union                                            /* Offset=0x01C4 : rSemaphoreStatusCPU1_28 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_28;
  char                     wk_01C8[0x0008];
  union                                            /* Offset=0x01D0 : rSemaphoreLockCPU1_29 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_29;
  union                                            /* Offset=0x01D4 : rSemaphoreStatusCPU1_29 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_29;
  char                     wk_01D8[0x0008];
  union                                            /* Offset=0x01E0 : rSemaphoreLockCPU1_30 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_30;
  union                                            /* Offset=0x01E4 : rSemaphoreStatusCPU1_30 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_30;
  char                     wk_01E8[0x0008];
  union                                            /* Offset=0x01F0 : rSemaphoreLockCPU1_31 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_31;
  union                                            /* Offset=0x01F4 : rSemaphoreStatusCPU1_31 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_31;
  char                     wk_01F8[0x0008];
  union                                            /* Offset=0x0200 : rSemaphoreLockCPU1_32 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_32;
  union                                            /* Offset=0x0204 : rSemaphoreStatusCPU1_32 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_32;
  char                     wk_0208[0x0008];
  union                                            /* Offset=0x0210 : rSemaphoreLockCPU1_33 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_33;
  union                                            /* Offset=0x0214 : rSemaphoreStatusCPU1_33 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_33;
  char                     wk_0218[0x0008];
  union                                            /* Offset=0x0220 : rSemaphoreLockCPU1_34 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_34;
  union                                            /* Offset=0x0224 : rSemaphoreStatusCPU1_34 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_34;
  char                     wk_0228[0x0008];
  union                                            /* Offset=0x0230 : rSemaphoreLockCPU1_35 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_35;
  union                                            /* Offset=0x0234 : rSemaphoreStatusCPU1_35 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_35;
  char                     wk_0238[0x0008];
  union                                            /* Offset=0x0240 : rSemaphoreLockCPU1_36 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_36;
  union                                            /* Offset=0x0244 : rSemaphoreStatusCPU1_36 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_36;
  char                     wk_0248[0x0008];
  union                                            /* Offset=0x0250 : rSemaphoreLockCPU1_37 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_37;
  union                                            /* Offset=0x0254 : rSemaphoreStatusCPU1_37 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_37;
  char                     wk_0258[0x0008];
  union                                            /* Offset=0x0260 : rSemaphoreLockCPU1_38 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_38;
  union                                            /* Offset=0x0264 : rSemaphoreStatusCPU1_38 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_38;
  char                     wk_0268[0x0008];
  union                                            /* Offset=0x0270 : rSemaphoreLockCPU1_39 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_39;
  union                                            /* Offset=0x0274 : rSemaphoreStatusCPU1_39 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_39;
  char                     wk_0278[0x0008];
  union                                            /* Offset=0x0280 : rSemaphoreLockCPU1_40 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_40;
  union                                            /* Offset=0x0284 : rSemaphoreStatusCPU1_40 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_40;
  char                     wk_0288[0x0008];
  union                                            /* Offset=0x0290 : rSemaphoreLockCPU1_41 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_41;
  union                                            /* Offset=0x0294 : rSemaphoreStatusCPU1_41 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_41;
  char                     wk_0298[0x0008];
  union                                            /* Offset=0x02A0 : rSemaphoreLockCPU1_42 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_42;
  union                                            /* Offset=0x02A4 : rSemaphoreStatusCPU1_42 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_42;
  char                     wk_02A8[0x0008];
  union                                            /* Offset=0x02B0 : rSemaphoreLockCPU1_43 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_43;
  union                                            /* Offset=0x02B4 : rSemaphoreStatusCPU1_43 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_43;
  char                     wk_02B8[0x0008];
  union                                            /* Offset=0x02C0 : rSemaphoreLockCPU1_44 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_44;
  union                                            /* Offset=0x02C4 : rSemaphoreStatusCPU1_44 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_44;
  char                     wk_02C8[0x0008];
  union                                            /* Offset=0x02D0 : rSemaphoreLockCPU1_45 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_45;
  union                                            /* Offset=0x02D4 : rSemaphoreStatusCPU1_45 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_45;
  char                     wk_02D8[0x0008];
  union                                            /* Offset=0x02E0 : rSemaphoreLockCPU1_46 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_46;
  union                                            /* Offset=0x02E4 : rSemaphoreStatusCPU1_46 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_46;
  char                     wk_02E8[0x0008];
  union                                            /* Offset=0x02F0 : rSemaphoreLockCPU1_47 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_47;
  union                                            /* Offset=0x02F4 : rSemaphoreStatusCPU1_47 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_47;
  char                     wk_02F8[0x0008];
  union                                            /* Offset=0x0300 : rSemaphoreLockCPU1_48 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_48;
  union                                            /* Offset=0x0304 : rSemaphoreStatusCPU1_48 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_48;
  char                     wk_0308[0x0008];
  union                                            /* Offset=0x0310 : rSemaphoreLockCPU1_49 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_49;
  union                                            /* Offset=0x0314 : rSemaphoreStatusCPU1_49 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_49;
  char                     wk_0318[0x0008];
  union                                            /* Offset=0x0320 : rSemaphoreLockCPU1_50 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_50;
  union                                            /* Offset=0x0324 : rSemaphoreStatusCPU1_50 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_50;
  char                     wk_0328[0x0008];
  union                                            /* Offset=0x0330 : rSemaphoreLockCPU1_51 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_51;
  union                                            /* Offset=0x0334 : rSemaphoreStatusCPU1_51 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_51;
  char                     wk_0338[0x0008];
  union                                            /* Offset=0x0340 : rSemaphoreLockCPU1_52 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_52;
  union                                            /* Offset=0x0344 : rSemaphoreStatusCPU1_52 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_52;
  char                     wk_0348[0x0008];
  union                                            /* Offset=0x0350 : rSemaphoreLockCPU1_53 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_53;
  union                                            /* Offset=0x0354 : rSemaphoreStatusCPU1_53 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_53;
  char                     wk_0358[0x0008];
  union                                            /* Offset=0x0360 : rSemaphoreLockCPU1_54 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_54;
  union                                            /* Offset=0x0364 : rSemaphoreStatusCPU1_54 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_54;
  char                     wk_0368[0x0008];
  union                                            /* Offset=0x0370 : rSemaphoreLockCPU1_55 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_55;
  union                                            /* Offset=0x0374 : rSemaphoreStatusCPU1_55 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_55;
  char                     wk_0378[0x0008];
  union                                            /* Offset=0x0380 : rSemaphoreLockCPU1_56 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_56;
  union                                            /* Offset=0x0384 : rSemaphoreStatusCPU1_56 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_56;
  char                     wk_0388[0x0008];
  union                                            /* Offset=0x0390 : rSemaphoreLockCPU1_57 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_57;
  union                                            /* Offset=0x0394 : rSemaphoreStatusCPU1_57 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_57;
  char                     wk_0398[0x0008];
  union                                            /* Offset=0x03A0 : rSemaphoreLockCPU1_58 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_58;
  union                                            /* Offset=0x03A4 : rSemaphoreStatusCPU1_58 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_58;
  char                     wk_03A8[0x0008];
  union                                            /* Offset=0x03B0 : rSemaphoreLockCPU1_59 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_59;
  union                                            /* Offset=0x03B4 : rSemaphoreStatusCPU1_59 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_59;
  char                     wk_03B8[0x0008];
  union                                            /* Offset=0x03C0 : rSemaphoreLockCPU1_60 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_60;
  union                                            /* Offset=0x03C4 : rSemaphoreStatusCPU1_60 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_60;
  char                     wk_03C8[0x0008];
  union                                            /* Offset=0x03D0 : rSemaphoreLockCPU1_61 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_61;
  union                                            /* Offset=0x03D4 : rSemaphoreStatusCPU1_61 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_61;
  char                     wk_03D8[0x0008];
  union                                            /* Offset=0x03E0 : rSemaphoreLockCPU1_62 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_62;
  union                                            /* Offset=0x03E4 : rSemaphoreStatusCPU1_62 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_62;
  char                     wk_03E8[0x0008];
  union                                            /* Offset=0x03F0 : rSemaphoreLockCPU1_63 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU1_63;
  union                                            /* Offset=0x03F4 : rSemaphoreStatusCPU1_63 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU1_63;
  char                     wk_03F8[0x0C08];
  union                                            /* Offset=0x1000 : rSemaphoreLockCPU2_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_0;
  union                                            /* Offset=0x1004 : rSemaphoreStatusCPU2_0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_0;
  char                     wk_1008[0x0008];
  union                                            /* Offset=0x1010 : rSemaphoreLockCPU2_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_1;
  union                                            /* Offset=0x1014 : rSemaphoreStatusCPU2_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_1;
  char                     wk_1018[0x0008];
  union                                            /* Offset=0x1020 : rSemaphoreLockCPU2_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_2;
  union                                            /* Offset=0x1024 : rSemaphoreStatusCPU2_2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_2;
  char                     wk_1028[0x0008];
  union                                            /* Offset=0x1030 : rSemaphoreLockCPU2_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_3;
  union                                            /* Offset=0x1034 : rSemaphoreStatusCPU2_3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_3;
  char                     wk_1038[0x0008];
  union                                            /* Offset=0x1040 : rSemaphoreLockCPU2_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_4;
  union                                            /* Offset=0x1044 : rSemaphoreStatusCPU2_4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_4;
  char                     wk_1048[0x0008];
  union                                            /* Offset=0x1050 : rSemaphoreLockCPU2_5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_5;
  union                                            /* Offset=0x1054 : rSemaphoreStatusCPU2_5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_5;
  char                     wk_1058[0x0008];
  union                                            /* Offset=0x1060 : rSemaphoreLockCPU2_6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_6;
  union                                            /* Offset=0x1064 : rSemaphoreStatusCPU2_6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_6;
  char                     wk_1068[0x0008];
  union                                            /* Offset=0x1070 : rSemaphoreLockCPU2_7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_7;
  union                                            /* Offset=0x1074 : rSemaphoreStatusCPU2_7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_7;
  char                     wk_1078[0x0008];
  union                                            /* Offset=0x1080 : rSemaphoreLockCPU2_8 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_8;
  union                                            /* Offset=0x1084 : rSemaphoreStatusCPU2_8 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_8;
  char                     wk_1088[0x0008];
  union                                            /* Offset=0x1090 : rSemaphoreLockCPU2_9 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_9;
  union                                            /* Offset=0x1094 : rSemaphoreStatusCPU2_9 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_9;
  char                     wk_1098[0x0008];
  union                                            /* Offset=0x10A0 : rSemaphoreLockCPU2_10 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_10;
  union                                            /* Offset=0x10A4 : rSemaphoreStatusCPU2_10 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_10;
  char                     wk_10A8[0x0008];
  union                                            /* Offset=0x10B0 : rSemaphoreLockCPU2_11 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_11;
  union                                            /* Offset=0x10B4 : rSemaphoreStatusCPU2_11 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_11;
  char                     wk_10B8[0x0008];
  union                                            /* Offset=0x10C0 : rSemaphoreLockCPU2_12 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_12;
  union                                            /* Offset=0x10C4 : rSemaphoreStatusCPU2_12 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_12;
  char                     wk_10C8[0x0008];
  union                                            /* Offset=0x10D0 : rSemaphoreLockCPU2_13 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_13;
  union                                            /* Offset=0x10D4 : rSemaphoreStatusCPU2_13 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_13;
  char                     wk_10D8[0x0008];
  union                                            /* Offset=0x10E0 : rSemaphoreLockCPU2_14 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_14;
  union                                            /* Offset=0x10E4 : rSemaphoreStatusCPU2_14 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_14;
  char                     wk_10E8[0x0008];
  union                                            /* Offset=0x10F0 : rSemaphoreLockCPU2_15 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_15;
  union                                            /* Offset=0x10F4 : rSemaphoreStatusCPU2_15 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_15;
  char                     wk_10F8[0x0008];
  union                                            /* Offset=0x1100 : rSemaphoreLockCPU2_16 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_16;
  union                                            /* Offset=0x1104 : rSemaphoreStatusCPU2_16 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_16;
  char                     wk_1108[0x0008];
  union                                            /* Offset=0x1110 : rSemaphoreLockCPU2_17 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_17;
  union                                            /* Offset=0x1114 : rSemaphoreStatusCPU2_17 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_17;
  char                     wk_1118[0x0008];
  union                                            /* Offset=0x1120 : rSemaphoreLockCPU2_18 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_18;
  union                                            /* Offset=0x1124 : rSemaphoreStatusCPU2_18 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_18;
  char                     wk_1128[0x0008];
  union                                            /* Offset=0x1130 : rSemaphoreLockCPU2_19 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_19;
  union                                            /* Offset=0x1134 : rSemaphoreStatusCPU2_19 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_19;
  char                     wk_1138[0x0008];
  union                                            /* Offset=0x1140 : rSemaphoreLockCPU2_20 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_20;
  union                                            /* Offset=0x1144 : rSemaphoreStatusCPU2_20 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_20;
  char                     wk_1148[0x0008];
  union                                            /* Offset=0x1150 : rSemaphoreLockCPU2_21 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_21;
  union                                            /* Offset=0x1154 : rSemaphoreStatusCPU2_21 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_21;
  char                     wk_1158[0x0008];
  union                                            /* Offset=0x1160 : rSemaphoreLockCPU2_22 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_22;
  union                                            /* Offset=0x1164 : rSemaphoreStatusCPU2_22 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_22;
  char                     wk_1168[0x0008];
  union                                            /* Offset=0x1170 : rSemaphoreLockCPU2_23 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_23;
  union                                            /* Offset=0x1174 : rSemaphoreStatusCPU2_23 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_23;
  char                     wk_1178[0x0008];
  union                                            /* Offset=0x1180 : rSemaphoreLockCPU2_24 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_24;
  union                                            /* Offset=0x1184 : rSemaphoreStatusCPU2_24 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_24;
  char                     wk_1188[0x0008];
  union                                            /* Offset=0x1190 : rSemaphoreLockCPU2_25 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_25;
  union                                            /* Offset=0x1194 : rSemaphoreStatusCPU2_25 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_25;
  char                     wk_1198[0x0008];
  union                                            /* Offset=0x11A0 : rSemaphoreLockCPU2_26 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_26;
  union                                            /* Offset=0x11A4 : rSemaphoreStatusCPU2_26 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_26;
  char                     wk_11A8[0x0008];
  union                                            /* Offset=0x11B0 : rSemaphoreLockCPU2_27 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_27;
  union                                            /* Offset=0x11B4 : rSemaphoreStatusCPU2_27 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_27;
  char                     wk_11B8[0x0008];
  union                                            /* Offset=0x11C0 : rSemaphoreLockCPU2_28 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_28;
  union                                            /* Offset=0x11C4 : rSemaphoreStatusCPU2_28 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_28;
  char                     wk_11C8[0x0008];
  union                                            /* Offset=0x11D0 : rSemaphoreLockCPU2_29 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_29;
  union                                            /* Offset=0x11D4 : rSemaphoreStatusCPU2_29 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_29;
  char                     wk_11D8[0x0008];
  union                                            /* Offset=0x11E0 : rSemaphoreLockCPU2_30 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_30;
  union                                            /* Offset=0x11E4 : rSemaphoreStatusCPU2_30 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_30;
  char                     wk_11E8[0x0008];
  union                                            /* Offset=0x11F0 : rSemaphoreLockCPU2_31 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_31;
  union                                            /* Offset=0x11F4 : rSemaphoreStatusCPU2_31 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_31;
  char                     wk_11F8[0x0008];
  union                                            /* Offset=0x1200 : rSemaphoreLockCPU2_32 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_32;
  union                                            /* Offset=0x1204 : rSemaphoreStatusCPU2_32 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_32;
  char                     wk_1208[0x0008];
  union                                            /* Offset=0x1210 : rSemaphoreLockCPU2_33 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_33;
  union                                            /* Offset=0x1214 : rSemaphoreStatusCPU2_33 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_33;
  char                     wk_1218[0x0008];
  union                                            /* Offset=0x1220 : rSemaphoreLockCPU2_34 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_34;
  union                                            /* Offset=0x1224 : rSemaphoreStatusCPU2_34 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_34;
  char                     wk_1228[0x0008];
  union                                            /* Offset=0x1230 : rSemaphoreLockCPU2_35 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_35;
  union                                            /* Offset=0x1234 : rSemaphoreStatusCPU2_35 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_35;
  char                     wk_1238[0x0008];
  union                                            /* Offset=0x1240 : rSemaphoreLockCPU2_36 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_36;
  union                                            /* Offset=0x1244 : rSemaphoreStatusCPU2_36 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_36;
  char                     wk_1248[0x0008];
  union                                            /* Offset=0x1250 : rSemaphoreLockCPU2_37 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_37;
  union                                            /* Offset=0x1254 : rSemaphoreStatusCPU2_37 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_37;
  char                     wk_1258[0x0008];
  union                                            /* Offset=0x1260 : rSemaphoreLockCPU2_38 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_38;
  union                                            /* Offset=0x1264 : rSemaphoreStatusCPU2_38 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_38;
  char                     wk_1268[0x0008];
  union                                            /* Offset=0x1270 : rSemaphoreLockCPU2_39 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_39;
  union                                            /* Offset=0x1274 : rSemaphoreStatusCPU2_39 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_39;
  char                     wk_1278[0x0008];
  union                                            /* Offset=0x1280 : rSemaphoreLockCPU2_40 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_40;
  union                                            /* Offset=0x1284 : rSemaphoreStatusCPU2_40 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_40;
  char                     wk_1288[0x0008];
  union                                            /* Offset=0x1290 : rSemaphoreLockCPU2_41 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_41;
  union                                            /* Offset=0x1294 : rSemaphoreStatusCPU2_41 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_41;
  char                     wk_1298[0x0008];
  union                                            /* Offset=0x12A0 : rSemaphoreLockCPU2_42 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_42;
  union                                            /* Offset=0x12A4 : rSemaphoreStatusCPU2_42 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_42;
  char                     wk_12A8[0x0008];
  union                                            /* Offset=0x12B0 : rSemaphoreLockCPU2_43 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_43;
  union                                            /* Offset=0x12B4 : rSemaphoreStatusCPU2_43 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_43;
  char                     wk_12B8[0x0008];
  union                                            /* Offset=0x12C0 : rSemaphoreLockCPU2_44 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_44;
  union                                            /* Offset=0x12C4 : rSemaphoreStatusCPU2_44 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_44;
  char                     wk_12C8[0x0008];
  union                                            /* Offset=0x12D0 : rSemaphoreLockCPU2_45 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_45;
  union                                            /* Offset=0x12D4 : rSemaphoreStatusCPU2_45 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_45;
  char                     wk_12D8[0x0008];
  union                                            /* Offset=0x12E0 : rSemaphoreLockCPU2_46 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_46;
  union                                            /* Offset=0x12E4 : rSemaphoreStatusCPU2_46 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_46;
  char                     wk_12E8[0x0008];
  union                                            /* Offset=0x12F0 : rSemaphoreLockCPU2_47 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_47;
  union                                            /* Offset=0x12F4 : rSemaphoreStatusCPU2_47 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_47;
  char                     wk_12F8[0x0008];
  union                                            /* Offset=0x1300 : rSemaphoreLockCPU2_48 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_48;
  union                                            /* Offset=0x1304 : rSemaphoreStatusCPU2_48 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_48;
  char                     wk_1308[0x0008];
  union                                            /* Offset=0x1310 : rSemaphoreLockCPU2_49 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_49;
  union                                            /* Offset=0x1314 : rSemaphoreStatusCPU2_49 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_49;
  char                     wk_1318[0x0008];
  union                                            /* Offset=0x1320 : rSemaphoreLockCPU2_50 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_50;
  union                                            /* Offset=0x1324 : rSemaphoreStatusCPU2_50 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_50;
  char                     wk_1328[0x0008];
  union                                            /* Offset=0x1330 : rSemaphoreLockCPU2_51 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_51;
  union                                            /* Offset=0x1334 : rSemaphoreStatusCPU2_51 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_51;
  char                     wk_1338[0x0008];
  union                                            /* Offset=0x1340 : rSemaphoreLockCPU2_52 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_52;
  union                                            /* Offset=0x1344 : rSemaphoreStatusCPU2_52 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_52;
  char                     wk_1348[0x0008];
  union                                            /* Offset=0x1350 : rSemaphoreLockCPU2_53 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_53;
  union                                            /* Offset=0x1354 : rSemaphoreStatusCPU2_53 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_53;
  char                     wk_1358[0x0008];
  union                                            /* Offset=0x1360 : rSemaphoreLockCPU2_54 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_54;
  union                                            /* Offset=0x1364 : rSemaphoreStatusCPU2_54 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_54;
  char                     wk_1368[0x0008];
  union                                            /* Offset=0x1370 : rSemaphoreLockCPU2_55 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_55;
  union                                            /* Offset=0x1374 : rSemaphoreStatusCPU2_55 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_55;
  char                     wk_1378[0x0008];
  union                                            /* Offset=0x1380 : rSemaphoreLockCPU2_56 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_56;
  union                                            /* Offset=0x1384 : rSemaphoreStatusCPU2_56 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_56;
  char                     wk_1388[0x0008];
  union                                            /* Offset=0x1390 : rSemaphoreLockCPU2_57 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_57;
  union                                            /* Offset=0x1394 : rSemaphoreStatusCPU2_57 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_57;
  char                     wk_1398[0x0008];
  union                                            /* Offset=0x13A0 : rSemaphoreLockCPU2_58 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_58;
  union                                            /* Offset=0x13A4 : rSemaphoreStatusCPU2_58 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_58;
  char                     wk_13A8[0x0008];
  union                                            /* Offset=0x13B0 : rSemaphoreLockCPU2_59 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_59;
  union                                            /* Offset=0x13B4 : rSemaphoreStatusCPU2_59 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_59;
  char                     wk_13B8[0x0008];
  union                                            /* Offset=0x13C0 : rSemaphoreLockCPU2_60 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_60;
  union                                            /* Offset=0x13C4 : rSemaphoreStatusCPU2_60 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_60;
  char                     wk_13C8[0x0008];
  union                                            /* Offset=0x13D0 : rSemaphoreLockCPU2_61 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_61;
  union                                            /* Offset=0x13D4 : rSemaphoreStatusCPU2_61 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_61;
  char                     wk_13D8[0x0008];
  union                                            /* Offset=0x13E0 : rSemaphoreLockCPU2_62 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_62;
  union                                            /* Offset=0x13E4 : rSemaphoreStatusCPU2_62 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_62;
  char                     wk_13E8[0x0008];
  union                                            /* Offset=0x13F0 : rSemaphoreLockCPU2_63 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU2_63;
  union                                            /* Offset=0x13F4 : rSemaphoreStatusCPU2_63 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU2_63;
  char                     wk_13F8[0x0C08];
  union                                            /* Offset=0x2000 : rSemaphoreLockCPU3_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_0;
  union                                            /* Offset=0x2004 : rSemaphoreStatusCPU3_0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_0;
  char                     wk_2008[0x0008];
  union                                            /* Offset=0x2010 : rSemaphoreLockCPU3_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_1;
  union                                            /* Offset=0x2014 : rSemaphoreStatusCPU3_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_1;
  char                     wk_2018[0x0008];
  union                                            /* Offset=0x2020 : rSemaphoreLockCPU3_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_2;
  union                                            /* Offset=0x2024 : rSemaphoreStatusCPU3_2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_2;
  char                     wk_2028[0x0008];
  union                                            /* Offset=0x2030 : rSemaphoreLockCPU3_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_3;
  union                                            /* Offset=0x2034 : rSemaphoreStatusCPU3_3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_3;
  char                     wk_2038[0x0008];
  union                                            /* Offset=0x2040 : rSemaphoreLockCPU3_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_4;
  union                                            /* Offset=0x2044 : rSemaphoreStatusCPU3_4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_4;
  char                     wk_2048[0x0008];
  union                                            /* Offset=0x2050 : rSemaphoreLockCPU3_5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_5;
  union                                            /* Offset=0x2054 : rSemaphoreStatusCPU3_5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_5;
  char                     wk_2058[0x0008];
  union                                            /* Offset=0x2060 : rSemaphoreLockCPU3_6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_6;
  union                                            /* Offset=0x2064 : rSemaphoreStatusCPU3_6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_6;
  char                     wk_2068[0x0008];
  union                                            /* Offset=0x2070 : rSemaphoreLockCPU3_7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_7;
  union                                            /* Offset=0x2074 : rSemaphoreStatusCPU3_7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_7;
  char                     wk_2078[0x0008];
  union                                            /* Offset=0x2080 : rSemaphoreLockCPU3_8 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_8;
  union                                            /* Offset=0x2084 : rSemaphoreStatusCPU3_8 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_8;
  char                     wk_2088[0x0008];
  union                                            /* Offset=0x2090 : rSemaphoreLockCPU3_9 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_9;
  union                                            /* Offset=0x2094 : rSemaphoreStatusCPU3_9 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_9;
  char                     wk_2098[0x0008];
  union                                            /* Offset=0x20A0 : rSemaphoreLockCPU3_10 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_10;
  union                                            /* Offset=0x20A4 : rSemaphoreStatusCPU3_10 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_10;
  char                     wk_20A8[0x0008];
  union                                            /* Offset=0x20B0 : rSemaphoreLockCPU3_11 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_11;
  union                                            /* Offset=0x20B4 : rSemaphoreStatusCPU3_11 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_11;
  char                     wk_20B8[0x0008];
  union                                            /* Offset=0x20C0 : rSemaphoreLockCPU3_12 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_12;
  union                                            /* Offset=0x20C4 : rSemaphoreStatusCPU3_12 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_12;
  char                     wk_20C8[0x0008];
  union                                            /* Offset=0x20D0 : rSemaphoreLockCPU3_13 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_13;
  union                                            /* Offset=0x20D4 : rSemaphoreStatusCPU3_13 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_13;
  char                     wk_20D8[0x0008];
  union                                            /* Offset=0x20E0 : rSemaphoreLockCPU3_14 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_14;
  union                                            /* Offset=0x20E4 : rSemaphoreStatusCPU3_14 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_14;
  char                     wk_20E8[0x0008];
  union                                            /* Offset=0x20F0 : rSemaphoreLockCPU3_15 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_15;
  union                                            /* Offset=0x20F4 : rSemaphoreStatusCPU3_15 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_15;
  char                     wk_20F8[0x0008];
  union                                            /* Offset=0x2100 : rSemaphoreLockCPU3_16 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_16;
  union                                            /* Offset=0x2104 : rSemaphoreStatusCPU3_16 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_16;
  char                     wk_2108[0x0008];
  union                                            /* Offset=0x2110 : rSemaphoreLockCPU3_17 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_17;
  union                                            /* Offset=0x2114 : rSemaphoreStatusCPU3_17 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_17;
  char                     wk_2118[0x0008];
  union                                            /* Offset=0x2120 : rSemaphoreLockCPU3_18 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_18;
  union                                            /* Offset=0x2124 : rSemaphoreStatusCPU3_18 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_18;
  char                     wk_2128[0x0008];
  union                                            /* Offset=0x2130 : rSemaphoreLockCPU3_19 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_19;
  union                                            /* Offset=0x2134 : rSemaphoreStatusCPU3_19 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_19;
  char                     wk_2138[0x0008];
  union                                            /* Offset=0x2140 : rSemaphoreLockCPU3_20 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_20;
  union                                            /* Offset=0x2144 : rSemaphoreStatusCPU3_20 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_20;
  char                     wk_2148[0x0008];
  union                                            /* Offset=0x2150 : rSemaphoreLockCPU3_21 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_21;
  union                                            /* Offset=0x2154 : rSemaphoreStatusCPU3_21 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_21;
  char                     wk_2158[0x0008];
  union                                            /* Offset=0x2160 : rSemaphoreLockCPU3_22 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_22;
  union                                            /* Offset=0x2164 : rSemaphoreStatusCPU3_22 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_22;
  char                     wk_2168[0x0008];
  union                                            /* Offset=0x2170 : rSemaphoreLockCPU3_23 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_23;
  union                                            /* Offset=0x2174 : rSemaphoreStatusCPU3_23 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_23;
  char                     wk_2178[0x0008];
  union                                            /* Offset=0x2180 : rSemaphoreLockCPU3_24 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_24;
  union                                            /* Offset=0x2184 : rSemaphoreStatusCPU3_24 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_24;
  char                     wk_2188[0x0008];
  union                                            /* Offset=0x2190 : rSemaphoreLockCPU3_25 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_25;
  union                                            /* Offset=0x2194 : rSemaphoreStatusCPU3_25 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_25;
  char                     wk_2198[0x0008];
  union                                            /* Offset=0x21A0 : rSemaphoreLockCPU3_26 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_26;
  union                                            /* Offset=0x21A4 : rSemaphoreStatusCPU3_26 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_26;
  char                     wk_21A8[0x0008];
  union                                            /* Offset=0x21B0 : rSemaphoreLockCPU3_27 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_27;
  union                                            /* Offset=0x21B4 : rSemaphoreStatusCPU3_27 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_27;
  char                     wk_21B8[0x0008];
  union                                            /* Offset=0x21C0 : rSemaphoreLockCPU3_28 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_28;
  union                                            /* Offset=0x21C4 : rSemaphoreStatusCPU3_28 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_28;
  char                     wk_21C8[0x0008];
  union                                            /* Offset=0x21D0 : rSemaphoreLockCPU3_29 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_29;
  union                                            /* Offset=0x21D4 : rSemaphoreStatusCPU3_29 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_29;
  char                     wk_21D8[0x0008];
  union                                            /* Offset=0x21E0 : rSemaphoreLockCPU3_30 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_30;
  union                                            /* Offset=0x21E4 : rSemaphoreStatusCPU3_30 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_30;
  char                     wk_21E8[0x0008];
  union                                            /* Offset=0x21F0 : rSemaphoreLockCPU3_31 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_31;
  union                                            /* Offset=0x21F4 : rSemaphoreStatusCPU3_31 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_31;
  char                     wk_21F8[0x0008];
  union                                            /* Offset=0x2200 : rSemaphoreLockCPU3_32 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_32;
  union                                            /* Offset=0x2204 : rSemaphoreStatusCPU3_32 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_32;
  char                     wk_2208[0x0008];
  union                                            /* Offset=0x2210 : rSemaphoreLockCPU3_33 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_33;
  union                                            /* Offset=0x2214 : rSemaphoreStatusCPU3_33 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_33;
  char                     wk_2218[0x0008];
  union                                            /* Offset=0x2220 : rSemaphoreLockCPU3_34 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_34;
  union                                            /* Offset=0x2224 : rSemaphoreStatusCPU3_34 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_34;
  char                     wk_2228[0x0008];
  union                                            /* Offset=0x2230 : rSemaphoreLockCPU3_35 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_35;
  union                                            /* Offset=0x2234 : rSemaphoreStatusCPU3_35 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_35;
  char                     wk_2238[0x0008];
  union                                            /* Offset=0x2240 : rSemaphoreLockCPU3_36 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_36;
  union                                            /* Offset=0x2244 : rSemaphoreStatusCPU3_36 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_36;
  char                     wk_2248[0x0008];
  union                                            /* Offset=0x2250 : rSemaphoreLockCPU3_37 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_37;
  union                                            /* Offset=0x2254 : rSemaphoreStatusCPU3_37 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_37;
  char                     wk_2258[0x0008];
  union                                            /* Offset=0x2260 : rSemaphoreLockCPU3_38 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_38;
  union                                            /* Offset=0x2264 : rSemaphoreStatusCPU3_38 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_38;
  char                     wk_2268[0x0008];
  union                                            /* Offset=0x2270 : rSemaphoreLockCPU3_39 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_39;
  union                                            /* Offset=0x2274 : rSemaphoreStatusCPU3_39 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_39;
  char                     wk_2278[0x0008];
  union                                            /* Offset=0x2280 : rSemaphoreLockCPU3_40 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_40;
  union                                            /* Offset=0x2284 : rSemaphoreStatusCPU3_40 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_40;
  char                     wk_2288[0x0008];
  union                                            /* Offset=0x2290 : rSemaphoreLockCPU3_41 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_41;
  union                                            /* Offset=0x2294 : rSemaphoreStatusCPU3_41 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_41;
  char                     wk_2298[0x0008];
  union                                            /* Offset=0x22A0 : rSemaphoreLockCPU3_42 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_42;
  union                                            /* Offset=0x22A4 : rSemaphoreStatusCPU3_42 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_42;
  char                     wk_22A8[0x0008];
  union                                            /* Offset=0x22B0 : rSemaphoreLockCPU3_43 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_43;
  union                                            /* Offset=0x22B4 : rSemaphoreStatusCPU3_43 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_43;
  char                     wk_22B8[0x0008];
  union                                            /* Offset=0x22C0 : rSemaphoreLockCPU3_44 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_44;
  union                                            /* Offset=0x22C4 : rSemaphoreStatusCPU3_44 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_44;
  char                     wk_22C8[0x0008];
  union                                            /* Offset=0x22D0 : rSemaphoreLockCPU3_45 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_45;
  union                                            /* Offset=0x22D4 : rSemaphoreStatusCPU3_45 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_45;
  char                     wk_22D8[0x0008];
  union                                            /* Offset=0x22E0 : rSemaphoreLockCPU3_46 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_46;
  union                                            /* Offset=0x22E4 : rSemaphoreStatusCPU3_46 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_46;
  char                     wk_22E8[0x0008];
  union                                            /* Offset=0x22F0 : rSemaphoreLockCPU3_47 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_47;
  union                                            /* Offset=0x22F4 : rSemaphoreStatusCPU3_47 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_47;
  char                     wk_22F8[0x0008];
  union                                            /* Offset=0x2300 : rSemaphoreLockCPU3_48 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_48;
  union                                            /* Offset=0x2304 : rSemaphoreStatusCPU3_48 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_48;
  char                     wk_2308[0x0008];
  union                                            /* Offset=0x2310 : rSemaphoreLockCPU3_49 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_49;
  union                                            /* Offset=0x2314 : rSemaphoreStatusCPU3_49 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_49;
  char                     wk_2318[0x0008];
  union                                            /* Offset=0x2320 : rSemaphoreLockCPU3_50 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_50;
  union                                            /* Offset=0x2324 : rSemaphoreStatusCPU3_50 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_50;
  char                     wk_2328[0x0008];
  union                                            /* Offset=0x2330 : rSemaphoreLockCPU3_51 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_51;
  union                                            /* Offset=0x2334 : rSemaphoreStatusCPU3_51 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_51;
  char                     wk_2338[0x0008];
  union                                            /* Offset=0x2340 : rSemaphoreLockCPU3_52 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_52;
  union                                            /* Offset=0x2344 : rSemaphoreStatusCPU3_52 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_52;
  char                     wk_2348[0x0008];
  union                                            /* Offset=0x2350 : rSemaphoreLockCPU3_53 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_53;
  union                                            /* Offset=0x2354 : rSemaphoreStatusCPU3_53 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_53;
  char                     wk_2358[0x0008];
  union                                            /* Offset=0x2360 : rSemaphoreLockCPU3_54 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_54;
  union                                            /* Offset=0x2364 : rSemaphoreStatusCPU3_54 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_54;
  char                     wk_2368[0x0008];
  union                                            /* Offset=0x2370 : rSemaphoreLockCPU3_55 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_55;
  union                                            /* Offset=0x2374 : rSemaphoreStatusCPU3_55 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_55;
  char                     wk_2378[0x0008];
  union                                            /* Offset=0x2380 : rSemaphoreLockCPU3_56 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_56;
  union                                            /* Offset=0x2384 : rSemaphoreStatusCPU3_56 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_56;
  char                     wk_2388[0x0008];
  union                                            /* Offset=0x2390 : rSemaphoreLockCPU3_57 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_57;
  union                                            /* Offset=0x2394 : rSemaphoreStatusCPU3_57 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_57;
  char                     wk_2398[0x0008];
  union                                            /* Offset=0x23A0 : rSemaphoreLockCPU3_58 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_58;
  union                                            /* Offset=0x23A4 : rSemaphoreStatusCPU3_58 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_58;
  char                     wk_23A8[0x0008];
  union                                            /* Offset=0x23B0 : rSemaphoreLockCPU3_59 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_59;
  union                                            /* Offset=0x23B4 : rSemaphoreStatusCPU3_59 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_59;
  char                     wk_23B8[0x0008];
  union                                            /* Offset=0x23C0 : rSemaphoreLockCPU3_60 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_60;
  union                                            /* Offset=0x23C4 : rSemaphoreStatusCPU3_60 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_60;
  char                     wk_23C8[0x0008];
  union                                            /* Offset=0x23D0 : rSemaphoreLockCPU3_61 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_61;
  union                                            /* Offset=0x23D4 : rSemaphoreStatusCPU3_61 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_61;
  char                     wk_23D8[0x0008];
  union                                            /* Offset=0x23E0 : rSemaphoreLockCPU3_62 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_62;
  union                                            /* Offset=0x23E4 : rSemaphoreStatusCPU3_62 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_62;
  char                     wk_23E8[0x0008];
  union                                            /* Offset=0x23F0 : rSemaphoreLockCPU3_63 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU3_63;
  union                                            /* Offset=0x23F4 : rSemaphoreStatusCPU3_63 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU3_63;
  char                     wk_23F8[0x0C08];
  union                                            /* Offset=0x3000 : rSemaphoreLockCPU4_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_0;
  union                                            /* Offset=0x3004 : rSemaphoreStatusCPU4_0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_0;
  char                     wk_3008[0x0008];
  union                                            /* Offset=0x3010 : rSemaphoreLockCPU4_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_1;
  union                                            /* Offset=0x3014 : rSemaphoreStatusCPU4_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_1;
  char                     wk_3018[0x0008];
  union                                            /* Offset=0x3020 : rSemaphoreLockCPU4_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_2;
  union                                            /* Offset=0x3024 : rSemaphoreStatusCPU4_2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_2;
  char                     wk_3028[0x0008];
  union                                            /* Offset=0x3030 : rSemaphoreLockCPU4_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_3;
  union                                            /* Offset=0x3034 : rSemaphoreStatusCPU4_3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_3;
  char                     wk_3038[0x0008];
  union                                            /* Offset=0x3040 : rSemaphoreLockCPU4_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_4;
  union                                            /* Offset=0x3044 : rSemaphoreStatusCPU4_4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_4;
  char                     wk_3048[0x0008];
  union                                            /* Offset=0x3050 : rSemaphoreLockCPU4_5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_5;
  union                                            /* Offset=0x3054 : rSemaphoreStatusCPU4_5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_5;
  char                     wk_3058[0x0008];
  union                                            /* Offset=0x3060 : rSemaphoreLockCPU4_6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_6;
  union                                            /* Offset=0x3064 : rSemaphoreStatusCPU4_6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_6;
  char                     wk_3068[0x0008];
  union                                            /* Offset=0x3070 : rSemaphoreLockCPU4_7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_7;
  union                                            /* Offset=0x3074 : rSemaphoreStatusCPU4_7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_7;
  char                     wk_3078[0x0008];
  union                                            /* Offset=0x3080 : rSemaphoreLockCPU4_8 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_8;
  union                                            /* Offset=0x3084 : rSemaphoreStatusCPU4_8 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_8;
  char                     wk_3088[0x0008];
  union                                            /* Offset=0x3090 : rSemaphoreLockCPU4_9 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_9;
  union                                            /* Offset=0x3094 : rSemaphoreStatusCPU4_9 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_9;
  char                     wk_3098[0x0008];
  union                                            /* Offset=0x30A0 : rSemaphoreLockCPU4_10 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_10;
  union                                            /* Offset=0x30A4 : rSemaphoreStatusCPU4_10 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_10;
  char                     wk_30A8[0x0008];
  union                                            /* Offset=0x30B0 : rSemaphoreLockCPU4_11 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_11;
  union                                            /* Offset=0x30B4 : rSemaphoreStatusCPU4_11 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_11;
  char                     wk_30B8[0x0008];
  union                                            /* Offset=0x30C0 : rSemaphoreLockCPU4_12 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_12;
  union                                            /* Offset=0x30C4 : rSemaphoreStatusCPU4_12 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_12;
  char                     wk_30C8[0x0008];
  union                                            /* Offset=0x30D0 : rSemaphoreLockCPU4_13 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_13;
  union                                            /* Offset=0x30D4 : rSemaphoreStatusCPU4_13 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_13;
  char                     wk_30D8[0x0008];
  union                                            /* Offset=0x30E0 : rSemaphoreLockCPU4_14 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_14;
  union                                            /* Offset=0x30E4 : rSemaphoreStatusCPU4_14 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_14;
  char                     wk_30E8[0x0008];
  union                                            /* Offset=0x30F0 : rSemaphoreLockCPU4_15 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_15;
  union                                            /* Offset=0x30F4 : rSemaphoreStatusCPU4_15 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_15;
  char                     wk_30F8[0x0008];
  union                                            /* Offset=0x3100 : rSemaphoreLockCPU4_16 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_16;
  union                                            /* Offset=0x3104 : rSemaphoreStatusCPU4_16 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_16;
  char                     wk_3108[0x0008];
  union                                            /* Offset=0x3110 : rSemaphoreLockCPU4_17 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_17;
  union                                            /* Offset=0x3114 : rSemaphoreStatusCPU4_17 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_17;
  char                     wk_3118[0x0008];
  union                                            /* Offset=0x3120 : rSemaphoreLockCPU4_18 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_18;
  union                                            /* Offset=0x3124 : rSemaphoreStatusCPU4_18 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_18;
  char                     wk_3128[0x0008];
  union                                            /* Offset=0x3130 : rSemaphoreLockCPU4_19 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_19;
  union                                            /* Offset=0x3134 : rSemaphoreStatusCPU4_19 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_19;
  char                     wk_3138[0x0008];
  union                                            /* Offset=0x3140 : rSemaphoreLockCPU4_20 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_20;
  union                                            /* Offset=0x3144 : rSemaphoreStatusCPU4_20 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_20;
  char                     wk_3148[0x0008];
  union                                            /* Offset=0x3150 : rSemaphoreLockCPU4_21 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_21;
  union                                            /* Offset=0x3154 : rSemaphoreStatusCPU4_21 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_21;
  char                     wk_3158[0x0008];
  union                                            /* Offset=0x3160 : rSemaphoreLockCPU4_22 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_22;
  union                                            /* Offset=0x3164 : rSemaphoreStatusCPU4_22 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_22;
  char                     wk_3168[0x0008];
  union                                            /* Offset=0x3170 : rSemaphoreLockCPU4_23 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_23;
  union                                            /* Offset=0x3174 : rSemaphoreStatusCPU4_23 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_23;
  char                     wk_3178[0x0008];
  union                                            /* Offset=0x3180 : rSemaphoreLockCPU4_24 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_24;
  union                                            /* Offset=0x3184 : rSemaphoreStatusCPU4_24 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_24;
  char                     wk_3188[0x0008];
  union                                            /* Offset=0x3190 : rSemaphoreLockCPU4_25 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_25;
  union                                            /* Offset=0x3194 : rSemaphoreStatusCPU4_25 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_25;
  char                     wk_3198[0x0008];
  union                                            /* Offset=0x31A0 : rSemaphoreLockCPU4_26 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_26;
  union                                            /* Offset=0x31A4 : rSemaphoreStatusCPU4_26 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_26;
  char                     wk_31A8[0x0008];
  union                                            /* Offset=0x31B0 : rSemaphoreLockCPU4_27 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_27;
  union                                            /* Offset=0x31B4 : rSemaphoreStatusCPU4_27 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_27;
  char                     wk_31B8[0x0008];
  union                                            /* Offset=0x31C0 : rSemaphoreLockCPU4_28 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_28;
  union                                            /* Offset=0x31C4 : rSemaphoreStatusCPU4_28 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_28;
  char                     wk_31C8[0x0008];
  union                                            /* Offset=0x31D0 : rSemaphoreLockCPU4_29 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_29;
  union                                            /* Offset=0x31D4 : rSemaphoreStatusCPU4_29 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_29;
  char                     wk_31D8[0x0008];
  union                                            /* Offset=0x31E0 : rSemaphoreLockCPU4_30 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_30;
  union                                            /* Offset=0x31E4 : rSemaphoreStatusCPU4_30 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_30;
  char                     wk_31E8[0x0008];
  union                                            /* Offset=0x31F0 : rSemaphoreLockCPU4_31 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_31;
  union                                            /* Offset=0x31F4 : rSemaphoreStatusCPU4_31 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_31;
  char                     wk_31F8[0x0008];
  union                                            /* Offset=0x3200 : rSemaphoreLockCPU4_32 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_32;
  union                                            /* Offset=0x3204 : rSemaphoreStatusCPU4_32 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_32;
  char                     wk_3208[0x0008];
  union                                            /* Offset=0x3210 : rSemaphoreLockCPU4_33 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_33;
  union                                            /* Offset=0x3214 : rSemaphoreStatusCPU4_33 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_33;
  char                     wk_3218[0x0008];
  union                                            /* Offset=0x3220 : rSemaphoreLockCPU4_34 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_34;
  union                                            /* Offset=0x3224 : rSemaphoreStatusCPU4_34 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_34;
  char                     wk_3228[0x0008];
  union                                            /* Offset=0x3230 : rSemaphoreLockCPU4_35 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_35;
  union                                            /* Offset=0x3234 : rSemaphoreStatusCPU4_35 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_35;
  char                     wk_3238[0x0008];
  union                                            /* Offset=0x3240 : rSemaphoreLockCPU4_36 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_36;
  union                                            /* Offset=0x3244 : rSemaphoreStatusCPU4_36 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_36;
  char                     wk_3248[0x0008];
  union                                            /* Offset=0x3250 : rSemaphoreLockCPU4_37 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_37;
  union                                            /* Offset=0x3254 : rSemaphoreStatusCPU4_37 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_37;
  char                     wk_3258[0x0008];
  union                                            /* Offset=0x3260 : rSemaphoreLockCPU4_38 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_38;
  union                                            /* Offset=0x3264 : rSemaphoreStatusCPU4_38 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_38;
  char                     wk_3268[0x0008];
  union                                            /* Offset=0x3270 : rSemaphoreLockCPU4_39 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_39;
  union                                            /* Offset=0x3274 : rSemaphoreStatusCPU4_39 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_39;
  char                     wk_3278[0x0008];
  union                                            /* Offset=0x3280 : rSemaphoreLockCPU4_40 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_40;
  union                                            /* Offset=0x3284 : rSemaphoreStatusCPU4_40 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_40;
  char                     wk_3288[0x0008];
  union                                            /* Offset=0x3290 : rSemaphoreLockCPU4_41 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_41;
  union                                            /* Offset=0x3294 : rSemaphoreStatusCPU4_41 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_41;
  char                     wk_3298[0x0008];
  union                                            /* Offset=0x32A0 : rSemaphoreLockCPU4_42 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_42;
  union                                            /* Offset=0x32A4 : rSemaphoreStatusCPU4_42 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_42;
  char                     wk_32A8[0x0008];
  union                                            /* Offset=0x32B0 : rSemaphoreLockCPU4_43 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_43;
  union                                            /* Offset=0x32B4 : rSemaphoreStatusCPU4_43 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_43;
  char                     wk_32B8[0x0008];
  union                                            /* Offset=0x32C0 : rSemaphoreLockCPU4_44 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_44;
  union                                            /* Offset=0x32C4 : rSemaphoreStatusCPU4_44 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_44;
  char                     wk_32C8[0x0008];
  union                                            /* Offset=0x32D0 : rSemaphoreLockCPU4_45 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_45;
  union                                            /* Offset=0x32D4 : rSemaphoreStatusCPU4_45 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_45;
  char                     wk_32D8[0x0008];
  union                                            /* Offset=0x32E0 : rSemaphoreLockCPU4_46 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_46;
  union                                            /* Offset=0x32E4 : rSemaphoreStatusCPU4_46 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_46;
  char                     wk_32E8[0x0008];
  union                                            /* Offset=0x32F0 : rSemaphoreLockCPU4_47 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_47;
  union                                            /* Offset=0x32F4 : rSemaphoreStatusCPU4_47 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_47;
  char                     wk_32F8[0x0008];
  union                                            /* Offset=0x3300 : rSemaphoreLockCPU4_48 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_48;
  union                                            /* Offset=0x3304 : rSemaphoreStatusCPU4_48 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_48;
  char                     wk_3308[0x0008];
  union                                            /* Offset=0x3310 : rSemaphoreLockCPU4_49 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_49;
  union                                            /* Offset=0x3314 : rSemaphoreStatusCPU4_49 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_49;
  char                     wk_3318[0x0008];
  union                                            /* Offset=0x3320 : rSemaphoreLockCPU4_50 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_50;
  union                                            /* Offset=0x3324 : rSemaphoreStatusCPU4_50 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_50;
  char                     wk_3328[0x0008];
  union                                            /* Offset=0x3330 : rSemaphoreLockCPU4_51 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_51;
  union                                            /* Offset=0x3334 : rSemaphoreStatusCPU4_51 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_51;
  char                     wk_3338[0x0008];
  union                                            /* Offset=0x3340 : rSemaphoreLockCPU4_52 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_52;
  union                                            /* Offset=0x3344 : rSemaphoreStatusCPU4_52 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_52;
  char                     wk_3348[0x0008];
  union                                            /* Offset=0x3350 : rSemaphoreLockCPU4_53 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_53;
  union                                            /* Offset=0x3354 : rSemaphoreStatusCPU4_53 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_53;
  char                     wk_3358[0x0008];
  union                                            /* Offset=0x3360 : rSemaphoreLockCPU4_54 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_54;
  union                                            /* Offset=0x3364 : rSemaphoreStatusCPU4_54 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_54;
  char                     wk_3368[0x0008];
  union                                            /* Offset=0x3370 : rSemaphoreLockCPU4_55 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_55;
  union                                            /* Offset=0x3374 : rSemaphoreStatusCPU4_55 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_55;
  char                     wk_3378[0x0008];
  union                                            /* Offset=0x3380 : rSemaphoreLockCPU4_56 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_56;
  union                                            /* Offset=0x3384 : rSemaphoreStatusCPU4_56 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_56;
  char                     wk_3388[0x0008];
  union                                            /* Offset=0x3390 : rSemaphoreLockCPU4_57 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_57;
  union                                            /* Offset=0x3394 : rSemaphoreStatusCPU4_57 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_57;
  char                     wk_3398[0x0008];
  union                                            /* Offset=0x33A0 : rSemaphoreLockCPU4_58 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_58;
  union                                            /* Offset=0x33A4 : rSemaphoreStatusCPU4_58 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_58;
  char                     wk_33A8[0x0008];
  union                                            /* Offset=0x33B0 : rSemaphoreLockCPU4_59 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_59;
  union                                            /* Offset=0x33B4 : rSemaphoreStatusCPU4_59 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_59;
  char                     wk_33B8[0x0008];
  union                                            /* Offset=0x33C0 : rSemaphoreLockCPU4_60 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_60;
  union                                            /* Offset=0x33C4 : rSemaphoreStatusCPU4_60 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_60;
  char                     wk_33C8[0x0008];
  union                                            /* Offset=0x33D0 : rSemaphoreLockCPU4_61 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_61;
  union                                            /* Offset=0x33D4 : rSemaphoreStatusCPU4_61 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_61;
  char                     wk_33D8[0x0008];
  union                                            /* Offset=0x33E0 : rSemaphoreLockCPU4_62 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_62;
  union                                            /* Offset=0x33E4 : rSemaphoreStatusCPU4_62 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_62;
  char                     wk_33E8[0x0008];
  union                                            /* Offset=0x33F0 : rSemaphoreLockCPU4_63 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSemaphoreLockCPU:3;                        /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreLockCPU4_63;
  union                                            /* Offset=0x33F4 : rSemaphoreStatusCPU4_63 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSemaphoreStatusCPU:3;                      /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSemaphoreStatusCPU4_63;
} SEMAP_Type;
#endif  /* End of __SEMAP_SFR__DEFINE_HEADER__ */
