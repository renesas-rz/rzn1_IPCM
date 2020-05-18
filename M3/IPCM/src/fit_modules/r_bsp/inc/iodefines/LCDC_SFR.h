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
 **       for RZN1 LCDC
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __LCDC_SFR__DEFINE_HEADER__
#define __LCDC_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : LCDC
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : rLcd_CR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_LCE:1;                                 /* [0] */
      __IO unsigned long   bLcd_LPE:1;                                 /* [1] */
      __IO unsigned long   bLcd_BPP:3;                                 /* [4:2] */
      __IO unsigned long   bLcd_RGB:1;                                 /* [5] */
      __IO unsigned long   bLcd_EPO:1;                                 /* [6] */
      __IO unsigned long   bLcd_EBO:1;                                 /* [7] */
      __IO unsigned long   bLcd_DEP:1;                                 /* [8] */
      __IO unsigned long   bLcd_PCP:1;                                 /* [9] */
      __IO unsigned long   bLcd_HSP:1;                                 /* [10] */
      __IO unsigned long   bLcd_VSP:1;                                 /* [11] */
      __IO unsigned long   bLcd_OPS:3;                                 /* [14:12] */
      __IO unsigned long   bLcd_PSS:1;                                 /* [15] */
      __IO unsigned long   bLcd_FDW:2;                                 /* [17:16] */
      __IO unsigned long   bLcd_LPS:1;                                 /* [18] */
      __IO unsigned long   bLcd_FBP:1;                                 /* [19] */
      __IO unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } rLcd_CR1;
  char                     wk_0004[0x0004];
  union                                            /* Offset=0x0008 : rLcd_HTR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_HFP:8;                                 /* [7:0] */
      __IO unsigned long   bLcd_PPL:8;                                 /* [15:8] */
      __IO unsigned long   bLcd_HBP:8;                                 /* [23:16] */
      __IO unsigned long   bLcd_HSW:8;                                 /* [31:24] */
    } BIT;
  } rLcd_HTR;
  union                                            /* Offset=0x000C : rLcd_VTR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_VSW:8;                                 /* [7:0] */
      __IO unsigned long   bLcd_VFP:8;                                 /* [15:8] */
      __IO unsigned long   bLcd_VBP:8;                                 /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } rLcd_VTR1;
  union                                            /* Offset=0x0010 : rLcd_VTR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_LPP:12;                                /* [11:0] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } rLcd_VTR2;
  union                                            /* Offset=0x0014 : rLcd_PCTR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :10;                                        /* [9:0] */
      __IO unsigned long   bLcd_PCR:1;                                 /* [10] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } rLcd_PCTR;
  union                                            /* Offset=0x0018 : rLcd_ISR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_OFU:1;                                 /* [0] */
      __IO unsigned long   bLcd_OFO:1;                                 /* [1] */
      __IO unsigned long   bLcd_IFU:1;                                 /* [2] */
      __IO unsigned long   bLcd_IFO:1;                                 /* [3] */
      __IO unsigned long   bLcd_FER:1;                                 /* [4] */
      __IO unsigned long   bLcd_MBE:1;                                 /* [5] */
      __IO unsigned long   bLcd_VCT:1;                                 /* [6] */
      __IO unsigned long   bLcd_BAU:1;                                 /* [7] */
      __IO unsigned long   bLcd_LDD:1;                                 /* [8] */
      __IO unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } rLcd_ISR;
  union                                            /* Offset=0x001C : rLcd_IMR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_OFUM:1;                                /* [0] */
      __IO unsigned long   bLcd_OFOM:1;                                /* [1] */
      __IO unsigned long   bLcd_IFUM:1;                                /* [2] */
      __IO unsigned long   bLcd_IFOM:1;                                /* [3] */
      __IO unsigned long   bLcd_FERM:1;                                /* [4] */
      __IO unsigned long   bLcd_MBEM:1;                                /* [5] */
      __IO unsigned long   bLcd_VCTM:1;                                /* [6] */
      __IO unsigned long   bLcd_BAUM:1;                                /* [7] */
      __IO unsigned long   bLcd_LDDM:1;                                /* [8] */
      __IO unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } rLcd_IMR;
  union                                            /* Offset=0x0020 : rLcd_IVR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bLcd_OFUV:1;                                /* [0] */
      __I  unsigned long   bLcd_OFOV:1;                                /* [1] */
      __I  unsigned long   bLcd_IFUV:1;                                /* [2] */
      __I  unsigned long   bLcd_IFOV:1;                                /* [3] */
      __I  unsigned long   bLcd_FERV:1;                                /* [4] */
      __I  unsigned long   bLcd_MBEV:1;                                /* [5] */
      __I  unsigned long   bLcd_VCTV:1;                                /* [6] */
      __I  unsigned long   bLcd_BAUV:1;                                /* [7] */
      __I  unsigned long   bLcd_LDDV:1;                                /* [8] */
      __I  unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } rLcd_IVR;
  union                                            /* Offset=0x0024 : rLcd_ISCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_VSC:3;                                 /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rLcd_ISCR;
  union                                            /* Offset=0x0028 : rLcd_DBAR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   bLcd_DBAR:29;                               /* [31:3] */
    } BIT;
  } rLcd_DBAR;
  union                                            /* Offset=0x002C : rLcd_DCAR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bLcd_DCAR:32;                               /* [31:0] */
    } BIT;
  } rLcd_DCAR;
  union                                            /* Offset=0x0030 : rLcd_DEAR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_DEAR:32;                               /* [31:0] */
    } BIT;
  } rLcd_DEAR;
  union                                            /* Offset=0x0034 : rLcd_PWMFR_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_PWMFCD_0:22;                           /* [21:0] */
      __IO unsigned long   bLcd_PWMFCE_0:1;                            /* [22] */
      __IO unsigned long   :9;                                         /* [31:23] */
    } BIT;
  } rLcd_PWMFR_0;
  union                                            /* Offset=0x0038 : rLcd_PWMDCR_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_PWMDC_0:8;                             /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rLcd_PWMDCR_0;
  char                     wk_003C[0x0008];
  union                                            /* Offset=0x0044 : rLcd_HVTER */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_HFPE:2;                                /* [1:0] */
      __IO unsigned long   :2;                                         /* [3:2] */
      __IO unsigned long   bLcd_HBPE:2;                                /* [5:4] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   bLcd_VFPE:2;                                /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bLcd_VBPE:2;                                /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bLcd_HSWE:2;                                /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   bLcd_VSWE:2;                                /* [25:24] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } rLcd_HVTER;
  union                                            /* Offset=0x0048 : rLcd_HPPLOR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_HPPLO:12;                              /* [11:0] */
      __IO unsigned long   :19;                                        /* [30:12] */
      __IO unsigned long   bLcd_HPOE:1;                                /* [31] */
    } BIT;
  } rLcd_HPPLOR;
  union                                            /* Offset=0x004C : rLcd_PWMFR_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_PWMFCD_1:22;                           /* [21:0] */
      __IO unsigned long   bLcd_PWMFCE_1:1;                            /* [22] */
      __IO unsigned long   :9;                                         /* [31:23] */
    } BIT;
  } rLcd_PWMFR_1;
  union                                            /* Offset=0x0050 : rLcd_PWMDCR_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_PWMDC_1:8;                             /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rLcd_PWMDCR_1;
  char                     wk_0054[0x01A4];
  union                                            /* Offset=0x01F8 : rLcd_GPIOR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bLcd_BlinkOn:1;                             /* [0] */
      __IO unsigned long   bLcd_BlinkMode:1;                           /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rLcd_GPIOR;
  union                                            /* Offset=0x01FC : rLcd_CIR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bLcd_REV:8;                                 /* [7:0] */
      __I  unsigned long   bLcd_Bl:4;                                  /* [11:8] */
      __I  unsigned long   bLcd_BW:4;                                  /* [15:12] */
      __I  unsigned long   bLcd_MN:8;                                  /* [23:16] */
      __I  unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } rLcd_CIR;
} LCDC_Type;
#endif  /* End of __LCDC_SFR__DEFINE_HEADER__ */
