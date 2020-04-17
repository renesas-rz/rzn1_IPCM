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
 **       for RZN1 CFGS2
 **
 **       revision 0.20 (2.Nov.2017)
 **
 **********************************************************************************************************************/
#ifndef __CFGS2_SFR__DEFINE_HEADER__
#define __CFGS2_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : CFGS2
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : rGPIOs_Level2_Config_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_0;
  union                                            /* Offset=0x0004 : rGPIOs_Level2_Config_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_1;
  union                                            /* Offset=0x0008 : rGPIOs_Level2_Config_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_2;
  union                                            /* Offset=0x000C : rGPIOs_Level2_Config_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_3;
  union                                            /* Offset=0x0010 : rGPIOs_Level2_Config_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_4;
  union                                            /* Offset=0x0014 : rGPIOs_Level2_Config_5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_5;
  union                                            /* Offset=0x0018 : rGPIOs_Level2_Config_6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_6;
  union                                            /* Offset=0x001C : rGPIOs_Level2_Config_7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_7;
  union                                            /* Offset=0x0020 : rGPIOs_Level2_Config_8 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_8;
  union                                            /* Offset=0x0024 : rGPIOs_Level2_Config_9 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_9;
  union                                            /* Offset=0x0028 : rGPIOs_Level2_Config_10 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_10;
  union                                            /* Offset=0x002C : rGPIOs_Level2_Config_11 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_11;
  union                                            /* Offset=0x0030 : rGPIOs_Level2_Config_12 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_12;
  union                                            /* Offset=0x0034 : rGPIOs_Level2_Config_13 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_13;
  union                                            /* Offset=0x0038 : rGPIOs_Level2_Config_14 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_14;
  union                                            /* Offset=0x003C : rGPIOs_Level2_Config_15 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_15;
  union                                            /* Offset=0x0040 : rGPIOs_Level2_Config_16 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_16;
  union                                            /* Offset=0x0044 : rGPIOs_Level2_Config_17 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_17;
  union                                            /* Offset=0x0048 : rGPIOs_Level2_Config_18 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_18;
  union                                            /* Offset=0x004C : rGPIOs_Level2_Config_19 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_19;
  union                                            /* Offset=0x0050 : rGPIOs_Level2_Config_20 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_20;
  union                                            /* Offset=0x0054 : rGPIOs_Level2_Config_21 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_21;
  union                                            /* Offset=0x0058 : rGPIOs_Level2_Config_22 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_22;
  union                                            /* Offset=0x005C : rGPIOs_Level2_Config_23 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_23;
  union                                            /* Offset=0x0060 : rGPIOs_Level2_Config_24 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_24;
  union                                            /* Offset=0x0064 : rGPIOs_Level2_Config_25 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_25;
  union                                            /* Offset=0x0068 : rGPIOs_Level2_Config_26 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_26;
  union                                            /* Offset=0x006C : rGPIOs_Level2_Config_27 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_27;
  union                                            /* Offset=0x0070 : rGPIOs_Level2_Config_28 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_28;
  union                                            /* Offset=0x0074 : rGPIOs_Level2_Config_29 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_29;
  union                                            /* Offset=0x0078 : rGPIOs_Level2_Config_30 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_30;
  union                                            /* Offset=0x007C : rGPIOs_Level2_Config_31 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_31;
  union                                            /* Offset=0x0080 : rGPIOs_Level2_Config_32 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_32;
  union                                            /* Offset=0x0084 : rGPIOs_Level2_Config_33 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_33;
  union                                            /* Offset=0x0088 : rGPIOs_Level2_Config_34 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_34;
  union                                            /* Offset=0x008C : rGPIOs_Level2_Config_35 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_35;
  union                                            /* Offset=0x0090 : rGPIOs_Level2_Config_36 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_36;
  union                                            /* Offset=0x0094 : rGPIOs_Level2_Config_37 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_37;
  union                                            /* Offset=0x0098 : rGPIOs_Level2_Config_38 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_38;
  union                                            /* Offset=0x009C : rGPIOs_Level2_Config_39 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_39;
  union                                            /* Offset=0x00A0 : rGPIOs_Level2_Config_40 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_40;
  union                                            /* Offset=0x00A4 : rGPIOs_Level2_Config_41 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_41;
  union                                            /* Offset=0x00A8 : rGPIOs_Level2_Config_42 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_42;
  union                                            /* Offset=0x00AC : rGPIOs_Level2_Config_43 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_43;
  union                                            /* Offset=0x00B0 : rGPIOs_Level2_Config_44 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_44;
  union                                            /* Offset=0x00B4 : rGPIOs_Level2_Config_45 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_45;
  union                                            /* Offset=0x00B8 : rGPIOs_Level2_Config_46 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_46;
  union                                            /* Offset=0x00BC : rGPIOs_Level2_Config_47 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_47;
  union                                            /* Offset=0x00C0 : rGPIOs_Level2_Config_48 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_48;
  union                                            /* Offset=0x00C4 : rGPIOs_Level2_Config_49 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_49;
  union                                            /* Offset=0x00C8 : rGPIOs_Level2_Config_50 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_50;
  union                                            /* Offset=0x00CC : rGPIOs_Level2_Config_51 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_51;
  union                                            /* Offset=0x00D0 : rGPIOs_Level2_Config_52 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_52;
  union                                            /* Offset=0x00D4 : rGPIOs_Level2_Config_53 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_53;
  union                                            /* Offset=0x00D8 : rGPIOs_Level2_Config_54 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_54;
  union                                            /* Offset=0x00DC : rGPIOs_Level2_Config_55 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_55;
  union                                            /* Offset=0x00E0 : rGPIOs_Level2_Config_56 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_56;
  union                                            /* Offset=0x00E4 : rGPIOs_Level2_Config_57 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_57;
  union                                            /* Offset=0x00E8 : rGPIOs_Level2_Config_58 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_58;
  union                                            /* Offset=0x00EC : rGPIOs_Level2_Config_59 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_59;
  union                                            /* Offset=0x00F0 : rGPIOs_Level2_Config_60 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_60;
  union                                            /* Offset=0x00F4 : rGPIOs_Level2_Config_61 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_61;
  union                                            /* Offset=0x00F8 : rGPIOs_Level2_Config_62 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_62;
  union                                            /* Offset=0x00FC : rGPIOs_Level2_Config_63 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_63;
  union                                            /* Offset=0x0100 : rGPIOs_Level2_Config_64 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_64;
  union                                            /* Offset=0x0104 : rGPIOs_Level2_Config_65 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_65;
  union                                            /* Offset=0x0108 : rGPIOs_Level2_Config_66 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_66;
  union                                            /* Offset=0x010C : rGPIOs_Level2_Config_67 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_67;
  union                                            /* Offset=0x0110 : rGPIOs_Level2_Config_68 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_68;
  union                                            /* Offset=0x0114 : rGPIOs_Level2_Config_69 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_69;
  union                                            /* Offset=0x0118 : rGPIOs_Level2_Config_70 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_70;
  union                                            /* Offset=0x011C : rGPIOs_Level2_Config_71 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_71;
  union                                            /* Offset=0x0120 : rGPIOs_Level2_Config_72 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_72;
  union                                            /* Offset=0x0124 : rGPIOs_Level2_Config_73 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_73;
  union                                            /* Offset=0x0128 : rGPIOs_Level2_Config_74 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_74;
  union                                            /* Offset=0x012C : rGPIOs_Level2_Config_75 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_75;
  union                                            /* Offset=0x0130 : rGPIOs_Level2_Config_76 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_76;
  union                                            /* Offset=0x0134 : rGPIOs_Level2_Config_77 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_77;
  union                                            /* Offset=0x0138 : rGPIOs_Level2_Config_78 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_78;
  union                                            /* Offset=0x013C : rGPIOs_Level2_Config_79 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_79;
  union                                            /* Offset=0x0140 : rGPIOs_Level2_Config_80 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_80;
  union                                            /* Offset=0x0144 : rGPIOs_Level2_Config_81 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_81;
  union                                            /* Offset=0x0148 : rGPIOs_Level2_Config_82 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_82;
  union                                            /* Offset=0x014C : rGPIOs_Level2_Config_83 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_83;
  union                                            /* Offset=0x0150 : rGPIOs_Level2_Config_84 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_84;
  union                                            /* Offset=0x0154 : rGPIOs_Level2_Config_85 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_85;
  union                                            /* Offset=0x0158 : rGPIOs_Level2_Config_86 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_86;
  union                                            /* Offset=0x015C : rGPIOs_Level2_Config_87 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_87;
  union                                            /* Offset=0x0160 : rGPIOs_Level2_Config_88 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_88;
  union                                            /* Offset=0x0164 : rGPIOs_Level2_Config_89 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_89;
  union                                            /* Offset=0x0168 : rGPIOs_Level2_Config_90 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_90;
  union                                            /* Offset=0x016C : rGPIOs_Level2_Config_91 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_91;
  union                                            /* Offset=0x0170 : rGPIOs_Level2_Config_92 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_92;
  union                                            /* Offset=0x0174 : rGPIOs_Level2_Config_93 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_93;
  union                                            /* Offset=0x0178 : rGPIOs_Level2_Config_94 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_94;
  union                                            /* Offset=0x017C : rGPIOs_Level2_Config_95 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_95;
  union                                            /* Offset=0x0180 : rGPIOs_Level2_Config_96 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_96;
  union                                            /* Offset=0x0184 : rGPIOs_Level2_Config_97 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_97;
  union                                            /* Offset=0x0188 : rGPIOs_Level2_Config_98 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_98;
  union                                            /* Offset=0x018C : rGPIOs_Level2_Config_99 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_99;
  union                                            /* Offset=0x0190 : rGPIOs_Level2_Config_100 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_100;
  union                                            /* Offset=0x0194 : rGPIOs_Level2_Config_101 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_101;
  union                                            /* Offset=0x0198 : rGPIOs_Level2_Config_102 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_102;
  union                                            /* Offset=0x019C : rGPIOs_Level2_Config_103 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_103;
  union                                            /* Offset=0x01A0 : rGPIOs_Level2_Config_104 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_104;
  union                                            /* Offset=0x01A4 : rGPIOs_Level2_Config_105 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_105;
  union                                            /* Offset=0x01A8 : rGPIOs_Level2_Config_106 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_106;
  union                                            /* Offset=0x01AC : rGPIOs_Level2_Config_107 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_107;
  union                                            /* Offset=0x01B0 : rGPIOs_Level2_Config_108 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_108;
  union                                            /* Offset=0x01B4 : rGPIOs_Level2_Config_109 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_109;
  union                                            /* Offset=0x01B8 : rGPIOs_Level2_Config_110 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_110;
  union                                            /* Offset=0x01BC : rGPIOs_Level2_Config_111 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_111;
  union                                            /* Offset=0x01C0 : rGPIOs_Level2_Config_112 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_112;
  union                                            /* Offset=0x01C4 : rGPIOs_Level2_Config_113 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_113;
  union                                            /* Offset=0x01C8 : rGPIOs_Level2_Config_114 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_114;
  union                                            /* Offset=0x01CC : rGPIOs_Level2_Config_115 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_115;
  union                                            /* Offset=0x01D0 : rGPIOs_Level2_Config_116 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_116;
  union                                            /* Offset=0x01D4 : rGPIOs_Level2_Config_117 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_117;
  union                                            /* Offset=0x01D8 : rGPIOs_Level2_Config_118 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_118;
  union                                            /* Offset=0x01DC : rGPIOs_Level2_Config_119 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_119;
  union                                            /* Offset=0x01E0 : rGPIOs_Level2_Config_120 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_120;
  union                                            /* Offset=0x01E4 : rGPIOs_Level2_Config_121 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_121;
  union                                            /* Offset=0x01E8 : rGPIOs_Level2_Config_122 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_122;
  union                                            /* Offset=0x01EC : rGPIOs_Level2_Config_123 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_123;
  union                                            /* Offset=0x01F0 : rGPIOs_Level2_Config_124 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_124;
  union                                            /* Offset=0x01F4 : rGPIOs_Level2_Config_125 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_125;
  union                                            /* Offset=0x01F8 : rGPIOs_Level2_Config_126 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_126;
  union                                            /* Offset=0x01FC : rGPIOs_Level2_Config_127 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_127;
  union                                            /* Offset=0x0200 : rGPIOs_Level2_Config_128 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_128;
  union                                            /* Offset=0x0204 : rGPIOs_Level2_Config_129 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_129;
  union                                            /* Offset=0x0208 : rGPIOs_Level2_Config_130 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_130;
  union                                            /* Offset=0x020C : rGPIOs_Level2_Config_131 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_131;
  union                                            /* Offset=0x0210 : rGPIOs_Level2_Config_132 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_132;
  union                                            /* Offset=0x0214 : rGPIOs_Level2_Config_133 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_133;
  union                                            /* Offset=0x0218 : rGPIOs_Level2_Config_134 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_134;
  union                                            /* Offset=0x021C : rGPIOs_Level2_Config_135 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_135;
  union                                            /* Offset=0x0220 : rGPIOs_Level2_Config_136 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_136;
  union                                            /* Offset=0x0224 : rGPIOs_Level2_Config_137 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_137;
  union                                            /* Offset=0x0228 : rGPIOs_Level2_Config_138 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_138;
  union                                            /* Offset=0x022C : rGPIOs_Level2_Config_139 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_139;
  union                                            /* Offset=0x0230 : rGPIOs_Level2_Config_140 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_140;
  union                                            /* Offset=0x0234 : rGPIOs_Level2_Config_141 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_141;
  union                                            /* Offset=0x0238 : rGPIOs_Level2_Config_142 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_142;
  union                                            /* Offset=0x023C : rGPIOs_Level2_Config_143 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_143;
  union                                            /* Offset=0x0240 : rGPIOs_Level2_Config_144 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_144;
  union                                            /* Offset=0x0244 : rGPIOs_Level2_Config_145 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_145;
  union                                            /* Offset=0x0248 : rGPIOs_Level2_Config_146 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_146;
  union                                            /* Offset=0x024C : rGPIOs_Level2_Config_147 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_147;
  union                                            /* Offset=0x0250 : rGPIOs_Level2_Config_148 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_148;
  union                                            /* Offset=0x0254 : rGPIOs_Level2_Config_149 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_149;
  union                                            /* Offset=0x0258 : rGPIOs_Level2_Config_150 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_150;
  union                                            /* Offset=0x025C : rGPIOs_Level2_Config_151 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_151;
  union                                            /* Offset=0x0260 : rGPIOs_Level2_Config_152 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_152;
  union                                            /* Offset=0x0264 : rGPIOs_Level2_Config_153 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_153;
  union                                            /* Offset=0x0268 : rGPIOs_Level2_Config_154 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_154;
  union                                            /* Offset=0x026C : rGPIOs_Level2_Config_155 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_155;
  union                                            /* Offset=0x0270 : rGPIOs_Level2_Config_156 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_156;
  union                                            /* Offset=0x0274 : rGPIOs_Level2_Config_157 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_157;
  union                                            /* Offset=0x0278 : rGPIOs_Level2_Config_158 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_158;
  union                                            /* Offset=0x027C : rGPIOs_Level2_Config_159 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_159;
  union                                            /* Offset=0x0280 : rGPIOs_Level2_Config_160 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_160;
  union                                            /* Offset=0x0284 : rGPIOs_Level2_Config_161 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_161;
  union                                            /* Offset=0x0288 : rGPIOs_Level2_Config_162 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_162;
  union                                            /* Offset=0x028C : rGPIOs_Level2_Config_163 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_163;
  union                                            /* Offset=0x0290 : rGPIOs_Level2_Config_164 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_164;
  union                                            /* Offset=0x0294 : rGPIOs_Level2_Config_165 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_165;
  union                                            /* Offset=0x0298 : rGPIOs_Level2_Config_166 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_166;
  union                                            /* Offset=0x029C : rGPIOs_Level2_Config_167 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_167;
  union                                            /* Offset=0x02A0 : rGPIOs_Level2_Config_168 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_168;
  union                                            /* Offset=0x02A4 : rGPIOs_Level2_Config_169 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_IOFunction:6;                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rGPIOs_Level2_Config_169;
  char                     wk_02A8[0x0158];
  union                                            /* Offset=0x0400 : rGPIOs_Level2_StatusProtect */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_Config_StatusProtect:1;       /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   bGPIOs_Level2_BadSequence:1;                /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rGPIOs_Level2_StatusProtect;
  union                                            /* Offset=0x0404 : rGPIOs_Level2_Config_MDIO1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_Config_MDIO1:3;               /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rGPIOs_Level2_Config_MDIO1;
  union                                            /* Offset=0x0408 : rGPIOs_Level2_Config_MDIO2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_Config_MDIO2:3;               /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rGPIOs_Level2_Config_MDIO2;
  char                     wk_040C[0x0074];
  union                                            /* Offset=0x0480 : rGPIOs_Level2_GPIO_Int_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_GPIO_Int:7;                   /* [6:0] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } rGPIOs_Level2_GPIO_Int_0;
  union                                            /* Offset=0x0484 : rGPIOs_Level2_GPIO_Int_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_GPIO_Int:7;                   /* [6:0] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } rGPIOs_Level2_GPIO_Int_1;
  union                                            /* Offset=0x0488 : rGPIOs_Level2_GPIO_Int_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_GPIO_Int:7;                   /* [6:0] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } rGPIOs_Level2_GPIO_Int_2;
  union                                            /* Offset=0x048C : rGPIOs_Level2_GPIO_Int_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_GPIO_Int:7;                   /* [6:0] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } rGPIOs_Level2_GPIO_Int_3;
  union                                            /* Offset=0x0490 : rGPIOs_Level2_GPIO_Int_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_GPIO_Int:7;                   /* [6:0] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } rGPIOs_Level2_GPIO_Int_4;
  union                                            /* Offset=0x0494 : rGPIOs_Level2_GPIO_Int_5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_GPIO_Int:7;                   /* [6:0] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } rGPIOs_Level2_GPIO_Int_5;
  union                                            /* Offset=0x0498 : rGPIOs_Level2_GPIO_Int_6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_GPIO_Int:7;                   /* [6:0] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } rGPIOs_Level2_GPIO_Int_6;
  union                                            /* Offset=0x049C : rGPIOs_Level2_GPIO_Int_7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIOs_Level2_GPIO_Int:7;                   /* [6:0] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } rGPIOs_Level2_GPIO_Int_7;
} CFGS2_Type;
#endif  /* End of __CFGS2_SFR__DEFINE_HEADER__ */
