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
 **       for RZN1D SYSCTRL
 **
 **       revision 0.20 (2.Nov.2017)
 **
 **********************************************************************************************************************/
#ifndef __SYSCTRL_SFR__DEFINE_HEADER__
#define __SYSCTRL_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : SYSCTRL
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : CFG_USB */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIRPD:1;                                    /* [0] */
      __IO unsigned long   H2MODE:1;                                   /* [1] */
      __IO unsigned long   FRCLK48MOD:1;                               /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } CFG_USB;
  union                                            /* Offset=0x0004 : OPMODE */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   DDRMOD:1;                                   /* [0] */
      __I  unsigned long   :1;                                         /* [1] */
      __I  unsigned long   CA7BOOTSRC:2;                               /* [3:2] */
      __I  unsigned long   CM3BOOTSEL:1;                               /* [4] */
      __I  unsigned long   :1;                                         /* [5] */
      __I  unsigned long   LCD1PU:1;                                   /* [6] */
      __I  unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } OPMODE;
  union                                            /* Offset=0x0008 : CFG_SDIO1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BASECLKFREQ:8;                              /* [7:0] */
      __IO unsigned long   SLOTTYPE:2;                                 /* [9:8] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } CFG_SDIO1;
  union                                            /* Offset=0x000C : PWRCTRL_SDIO1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   MIREQ_A:1;                                  /* [3] */
      __IO unsigned long   CLKEN_B:1;                                  /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } PWRCTRL_SDIO1;
  union                                            /* Offset=0x0010 : PWRSTAT_SDIO1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   MIRACK_A:1;                                 /* [1] */
      __I  unsigned long   MISTAT_A:1;                                 /* [2] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRSTAT_SDIO1;
  union                                            /* Offset=0x0014 : DBGCON */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PR_DBG_EN:1;                                /* [0] */
      __IO unsigned long   CM3WD_DBG_EN:1;                             /* [1] */
      __IO unsigned long   CA7WD0_DBG_EN:1;                            /* [2] */
      __IO unsigned long   CA7WD1_DBG_EN:1;                            /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } DBGCON;
  union                                            /* Offset=0x0018 : SYSSTAT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CA7_STANDBYWFE:2;                           /* [1:0] */
      __I  unsigned long   CA7_STANDBYWFI:2;                           /* [3:2] */
      __I  unsigned long   CA7_STANDBYWFIL2:1;                         /* [4] */
      __I  unsigned long   :1;                                         /* [5] */
      __I  unsigned long   PKGMODE:1;                                  /* [6] */
      __I  unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } SYSSTAT;
  union                                            /* Offset=0x001C : PWRCTRL_USB */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   MIREQ_A:1;                                  /* [2] */
      __IO unsigned long   CLKEN_B:1;                                  /* [3] */
      __IO unsigned long   MIREQ_B:1;                                  /* [4] */
      __IO unsigned long   CLKEN_C:1;                                  /* [5] */
      __IO unsigned long   CLKEN_E:1;                                  /* [6] */
      __IO unsigned long   RSTN_F:1;                                   /* [7] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } PWRCTRL_USB;
  union                                            /* Offset=0x0020 : PWRSTAT_USB */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MIRACK_A:1;                                 /* [0] */
      __I  unsigned long   MISTAT_A:1;                                 /* [1] */
      __I  unsigned long   MIRACK_B:1;                                 /* [2] */
      __I  unsigned long   MISTAT_B:1;                                 /* [3] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } PWRSTAT_USB;
  char                     wk_0024[0x0008];
  union                                            /* Offset=0x002C : PWRCTRL_MSEBI */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   MIREQ_A:1;                                  /* [3] */
      __IO unsigned long   CLKEN_B:1;                                  /* [4] */
      __IO unsigned long   RSTN_B:1;                                   /* [5] */
      __IO unsigned long   SLVRDY_B:1;                                 /* [6] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } PWRCTRL_MSEBI;
  union                                            /* Offset=0x0030 : PWRSTAT_MSEBI */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   MIRACK_A:1;                                 /* [1] */
      __I  unsigned long   MISTAT_A:1;                                 /* [2] */
      __I  unsigned long   SCON_B:1;                                   /* [3] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } PWRSTAT_MSEBI;
  union                                            /* Offset=0x0034 : PWRCTRL_PG0_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   CLKEN_B:1;                                  /* [3] */
      __IO unsigned long   RSTN_B:1;                                   /* [4] */
      __IO unsigned long   SLVRDY_B:1;                                 /* [5] */
      __IO unsigned long   CLKEN_C:1;                                  /* [6] */
      __IO unsigned long   RSTN_C:1;                                   /* [7] */
      __IO unsigned long   SLVRDY_C:1;                                 /* [8] */
      __IO unsigned long   CLKEN_D:1;                                  /* [9] */
      __IO unsigned long   RSTN_D:1;                                   /* [10] */
      __IO unsigned long   SLVRDY_D:1;                                 /* [11] */
      __IO unsigned long   CLKEN_E:1;                                  /* [12] */
      __IO unsigned long   RSTN_E:1;                                   /* [13] */
      __IO unsigned long   SLVRDY_E:1;                                 /* [14] */
      __IO unsigned long   CLKEN_F:1;                                  /* [15] */
      __IO unsigned long   RSTN_F:1;                                   /* [16] */
      __IO unsigned long   SLVRDY_F:1;                                 /* [17] */
      __IO unsigned long   CLKEN_H1:1;                                 /* [18] */
      __IO unsigned long   RSTN_H1:1;                                  /* [19] */
      __IO unsigned long   CLKEN_H2:1;                                 /* [20] */
      __IO unsigned long   RSTN_H2:1;                                  /* [21] */
      __IO unsigned long   CLKEN_I1:1;                                 /* [22] */
      __IO unsigned long   RSTN_I1:1;                                  /* [23] */
      __IO unsigned long   CLKEN_I2:1;                                 /* [24] */
      __IO unsigned long   RSTN_I2:1;                                  /* [25] */
      __IO unsigned long   CLKEN_J1:1;                                 /* [26] */
      __IO unsigned long   RSTN_J1:1;                                  /* [27] */
      __IO unsigned long   CLKEN_J2:1;                                 /* [28] */
      __IO unsigned long   RSTN_J2:1;                                  /* [29] */
      __IO unsigned long   UARTCLKSEL:1;                               /* [30] */
    } BIT;
  } PWRCTRL_PG0_0;
  union                                            /* Offset=0x0038 : PWRSTAT_PG0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   SCON_B:1;                                   /* [1] */
      __I  unsigned long   SCON_C:1;                                   /* [2] */
      __I  unsigned long   SCON_D:1;                                   /* [3] */
      __I  unsigned long   SCON_E:1;                                   /* [4] */
      __I  unsigned long   SCON_F:1;                                   /* [5] */
      __I  unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PWRSTAT_PG0;
  union                                            /* Offset=0x003C : PWRCTRL_PG0_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :6;                                         /* [5:0] */
      __IO unsigned long   CLKEN_K:1;                                  /* [6] */
      __IO unsigned long   RSTN_K:1;                                   /* [7] */
      __IO unsigned long   CLKEN_L:1;                                  /* [8] */
      __IO unsigned long   RSTN_L:1;                                   /* [9] */
      __IO unsigned long   CLKEN_M:1;                                  /* [10] */
      __IO unsigned long   RSTN_M:1;                                   /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } PWRCTRL_PG0_1;
  union                                            /* Offset=0x0040 : PWRCTRL_PG1_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   CLKEN_B:1;                                  /* [3] */
      __IO unsigned long   RSTN_B:1;                                   /* [4] */
      __IO unsigned long   SLVRDY_B:1;                                 /* [5] */
      __IO unsigned long   CLKEN_C:1;                                  /* [6] */
      __IO unsigned long   RSTN_C:1;                                   /* [7] */
      __IO unsigned long   SLVRDY_C:1;                                 /* [8] */
      __IO unsigned long   CLKEN_D:1;                                  /* [9] */
      __IO unsigned long   RSTN_D:1;                                   /* [10] */
      __IO unsigned long   SLVRDY_D:1;                                 /* [11] */
      __IO unsigned long   CLKEN_E:1;                                  /* [12] */
      __IO unsigned long   RSTN_E:1;                                   /* [13] */
      __IO unsigned long   SLVRDY_E:1;                                 /* [14] */
      __IO unsigned long   CLKEN_F:1;                                  /* [15] */
      __IO unsigned long   RSTN_F:1;                                   /* [16] */
      __IO unsigned long   SLVRDY_F:1;                                 /* [17] */
      __IO unsigned long   CLKEN_G:1;                                  /* [18] */
      __IO unsigned long   RSTN_G:1;                                   /* [19] */
      __IO unsigned long   SLVRDY_G:1;                                 /* [20] */
      __IO unsigned long   CLKEN_H:1;                                  /* [21] */
      __IO unsigned long   RSTN_H:1;                                   /* [22] */
      __IO unsigned long   SLVRDY_H:1;                                 /* [23] */
      __IO unsigned long   CLKEN_I:1;                                  /* [24] */
      __IO unsigned long   RSTN_I:1;                                   /* [25] */
      __IO unsigned long   SLVRDY_I:1;                                 /* [26] */
      __IO unsigned long   CLKEN_J:1;                                  /* [27] */
      __IO unsigned long   RSTN_J:1;                                   /* [28] */
      __IO unsigned long   SLVRDY_J:1;                                 /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } PWRCTRL_PG1_1;
  union                                            /* Offset=0x0044 : PWRCTRL_PG1_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_K:1;                                  /* [0] */
      __IO unsigned long   RSTN_K:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_K:1;                                 /* [2] */
      __IO unsigned long   CLKEN_L:1;                                  /* [3] */
      __IO unsigned long   RSTN_L:1;                                   /* [4] */
      __IO unsigned long   SLVRDY_L:1;                                 /* [5] */
      __IO unsigned long   CLKEN_M:1;                                  /* [6] */
      __IO unsigned long   RSTN_M:1;                                   /* [7] */
      __IO unsigned long   SLVRDY_M:1;                                 /* [8] */
      __IO unsigned long   CLKEN_N:1;                                  /* [9] */
      __IO unsigned long   RSTN_N:1;                                   /* [10] */
      __IO unsigned long   SLVRDY_N:1;                                 /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } PWRCTRL_PG1_2;
  char                     wk_0048[0x0004];
  union                                            /* Offset=0x004C : PWRCTRL_DMA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   MIREQ_A:1;                                  /* [3] */
      __IO unsigned long   CLKEN_B:1;                                  /* [4] */
      __IO unsigned long   RSTN_B:1;                                   /* [5] */
      __IO unsigned long   SLVRDY_B:1;                                 /* [6] */
      __IO unsigned long   MIREQ_B:1;                                  /* [7] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } PWRCTRL_DMA;
  union                                            /* Offset=0x0050 : PWRCTRL_NFLASH */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   MIREQ_A:1;                                  /* [3] */
      __IO unsigned long   CLKEN_B:1;                                  /* [4] */
      __IO unsigned long   RSTN_B:1;                                   /* [5] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PWRCTRL_NFLASH;
  union                                            /* Offset=0x0054 : PWRCTRL_QSPI1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   MIREQ_A:1;                                  /* [3] */
      __IO unsigned long   CLKEN_B:1;                                  /* [4] */
      __IO unsigned long   RSTN_B:1;                                   /* [5] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PWRCTRL_QSPI1;
  union                                            /* Offset=0x0058 : PWRSTAT_DMA */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   MIRACK_A:1;                                 /* [1] */
      __I  unsigned long   MISTAT_A:1;                                 /* [2] */
      __I  unsigned long   SCON_B:1;                                   /* [3] */
      __I  unsigned long   MIRACK_B:1;                                 /* [4] */
      __I  unsigned long   MISTAT_B:1;                                 /* [5] */
      __I  unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PWRSTAT_DMA;
  union                                            /* Offset=0x005C : PWRSTAT_NFLASH */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   MIRACK_A:1;                                 /* [1] */
      __I  unsigned long   MISTAT_A:1;                                 /* [2] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRSTAT_NFLASH;
  union                                            /* Offset=0x0060 : PWRSTAT_QSPI1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   MIRACK_A:1;                                 /* [1] */
      __I  unsigned long   MISTAT_A:1;                                 /* [2] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRSTAT_QSPI1;
  union                                            /* Offset=0x0064 : PWRCTRL_DDRC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   MIREQ_A:1;                                  /* [1] */
      __IO unsigned long   RSTN_A:1;                                   /* [2] */
      __IO unsigned long   CLKEN_B:1;                                  /* [3] */
      __IO unsigned long   RSTN_B:1;                                   /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } PWRCTRL_DDRC;
  union                                            /* Offset=0x0068 : PWRCTRL_EETH */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   CLKEN_B:1;                                  /* [1] */
      __IO unsigned long   CLKEN_C:1;                                  /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRCTRL_EETH;
  union                                            /* Offset=0x006C : PWRCTRL_MAC1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   MIREQ_A:1;                                  /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } PWRCTRL_MAC1;
  union                                            /* Offset=0x0070 : PWRCTRL_MAC2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   MIREQ_A:1;                                  /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } PWRCTRL_MAC2;
  union                                            /* Offset=0x0074 : PWRSTAT_DDRC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MIRACK_A:1;                                 /* [0] */
      __I  unsigned long   MISTAT_A:1;                                 /* [1] */
      __I  unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } PWRSTAT_DDRC;
  union                                            /* Offset=0x0078 : PWRSTAT_MAC1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   MIRACK_A:1;                                 /* [1] */
      __I  unsigned long   MISTAT_A:1;                                 /* [2] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRSTAT_MAC1;
  union                                            /* Offset=0x007C : PWRSTAT_MAC2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   MIRACK_A:1;                                 /* [1] */
      __I  unsigned long   MISTAT_A:1;                                 /* [2] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRSTAT_MAC2;
  union                                            /* Offset=0x0080 : PWRCTRL_ECAT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   MIREQ_A:1;                                  /* [2] */
      __IO unsigned long   CLKEN_B:1;                                  /* [3] */
      __IO unsigned long   RSTN_B:1;                                   /* [4] */
      __IO unsigned long   CLKEN_C:1;                                  /* [5] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PWRCTRL_ECAT;
  union                                            /* Offset=0x0084 : PWRCTRL_SERCOS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   MIREQ_A:1;                                  /* [1] */
      __IO unsigned long   RSTN_A:1;                                   /* [2] */
      __IO unsigned long   RSTN_B:1;                                   /* [3] */
      __IO unsigned long   CLKEN_B:1;                                  /* [4] */
      __IO unsigned long   CLKEN_C:1;                                  /* [5] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PWRCTRL_SERCOS;
  union                                            /* Offset=0x0088 : PWRSTAT_ECAT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MIRACK_A:1;                                 /* [0] */
      __I  unsigned long   MISTAT_A:1;                                 /* [1] */
      __I  unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } PWRSTAT_ECAT;
  union                                            /* Offset=0x008C : PWRSTAT_SERCOS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MIRACK_A:1;                                 /* [0] */
      __I  unsigned long   MISTAT_A:1;                                 /* [1] */
      __I  unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } PWRSTAT_SERCOS;
  union                                            /* Offset=0x0090 : PWRCTRL_HSR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   MIREQ_A:1;                                  /* [1] */
      __IO unsigned long   RSTN_A:1;                                   /* [2] */
      __IO unsigned long   CLKEN_B:1;                                  /* [3] */
      __IO unsigned long   CLKEN_C:1;                                  /* [4] */
      __IO unsigned long   RSTN_C:1;                                   /* [5] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PWRCTRL_HSR;
  union                                            /* Offset=0x0094 : PWRCTRL_SWITCHDIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:7;                                      /* [6:0] */
      __IO unsigned long   :24;                                        /* [30:7] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_SWITCHDIV;
  union                                            /* Offset=0x0098 : PWRSTAT_HSR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MIRACK_A:1;                                 /* [0] */
      __I  unsigned long   MISTAT_A:1;                                 /* [1] */
      __I  unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } PWRSTAT_HSR;
  union                                            /* Offset=0x009C : PWRSTAT_SWITCH */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } PWRSTAT_SWITCH;
  union                                            /* Offset=0x00A0 : CFG_DMAMUX */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   D1MX0:1;                                    /* [0] */
      __IO unsigned long   D1MX1:1;                                    /* [1] */
      __IO unsigned long   D1MX2:1;                                    /* [2] */
      __IO unsigned long   D1MX3:1;                                    /* [3] */
      __IO unsigned long   D1MX4:1;                                    /* [4] */
      __IO unsigned long   D1MX5:1;                                    /* [5] */
      __IO unsigned long   D1MX6:1;                                    /* [6] */
      __IO unsigned long   D1MX7:1;                                    /* [7] */
      __IO unsigned long   D1MX8:1;                                    /* [8] */
      __IO unsigned long   D1MX9:1;                                    /* [9] */
      __IO unsigned long   D1MX10:1;                                   /* [10] */
      __IO unsigned long   D1MX11:1;                                   /* [11] */
      __IO unsigned long   D1MX12:1;                                   /* [12] */
      __IO unsigned long   D1MX13:1;                                   /* [13] */
      __IO unsigned long   D1MX14:1;                                   /* [14] */
      __IO unsigned long   D1MX15:1;                                   /* [15] */
      __IO unsigned long   D2MX0:1;                                    /* [16] */
      __IO unsigned long   D2MX1:1;                                    /* [17] */
      __IO unsigned long   D2MX2:1;                                    /* [18] */
      __IO unsigned long   D2MX3:1;                                    /* [19] */
      __IO unsigned long   D2MX4:1;                                    /* [20] */
      __IO unsigned long   D2MX5:1;                                    /* [21] */
      __IO unsigned long   D2MX6:1;                                    /* [22] */
      __IO unsigned long   D2MX7:1;                                    /* [23] */
      __IO unsigned long   D2MX8:1;                                    /* [24] */
      __IO unsigned long   D2MX9:1;                                    /* [25] */
      __IO unsigned long   D2MX10:1;                                   /* [26] */
      __IO unsigned long   D2MX11:1;                                   /* [27] */
      __IO unsigned long   D2MX12:1;                                   /* [28] */
      __IO unsigned long   D2MX13:1;                                   /* [29] */
      __IO unsigned long   D2MX14:1;                                   /* [30] */
      __IO unsigned long   D2MX15:1;                                   /* [31] */
    } BIT;
  } CFG_DMAMUX;
  union                                            /* Offset=0x00A4 : CFG_GPIOT_PTEN_1A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PORTEN:32;                                  /* [31:0] */
    } BIT;
  } CFG_GPIOT_PTEN_1A;
  union                                            /* Offset=0x00A8 : RSTSTAT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   WDA7RST_ST:2;                               /* [2:1] */
      __IO unsigned long   WDM3RST_ST:1;                               /* [3] */
      __IO unsigned long   CM3LOCKUPRST_ST:1;                          /* [4] */
      __IO unsigned long   CM3SYSRESET_ST:1;                           /* [5] */
      __IO unsigned long   SWRST_ST:1;                                 /* [6] */
      __IO unsigned long   :24;                                        /* [30:7] */
      __IO unsigned long   PORRST_ST:1;                                /* [31] */
    } BIT;
  } RSTSTAT;
  char                     wk_00AC[0x0004];
  union                                            /* Offset=0x00B0 : CFG_GPIOT_PTEN_1B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PORTEN:32;                                  /* [31:0] */
    } BIT;
  } CFG_GPIOT_PTEN_1B;
  union                                            /* Offset=0x00B4 : CFG_GPIOT_PTEN_2A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PORTEN:32;                                  /* [31:0] */
    } BIT;
  } CFG_GPIOT_PTEN_2A;
  union                                            /* Offset=0x00B8 : CFG_GPIOT_PTEN_2B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PORTEN:32;                                  /* [31:0] */
    } BIT;
  } CFG_GPIOT_PTEN_2B;
  union                                            /* Offset=0x00BC : CFG_GPIOT_TSRC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TRIG0:5;                                    /* [4:0] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   TRIG1:5;                                    /* [12:8] */
      __IO unsigned long   :3;                                         /* [15:13] */
      __IO unsigned long   TRIG2:5;                                    /* [20:16] */
      __IO unsigned long   :3;                                         /* [23:21] */
      __IO unsigned long   TRIG3:5;                                    /* [28:24] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } CFG_GPIOT_TSRC;
  union                                            /* Offset=0x00C0 : USBSTAT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PLL_LOCK:1;                                 /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } USBSTAT;
  union                                            /* Offset=0x00C4 : CFG_SDIO2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BASECLKFREQ:8;                              /* [7:0] */
      __IO unsigned long   SLOTTYPE:2;                                 /* [9:8] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } CFG_SDIO2;
  union                                            /* Offset=0x00C8 : PWRCTRL_SDIO2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   MIREQ_A:1;                                  /* [3] */
      __IO unsigned long   CLKEN_B:1;                                  /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } PWRCTRL_SDIO2;
  union                                            /* Offset=0x00CC : PWRSTAT_SDIO2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   MIRACK_A:1;                                 /* [1] */
      __I  unsigned long   MISTAT_A:1;                                 /* [2] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRSTAT_SDIO2;
  char                     wk_00D0[0x0008];
  union                                            /* Offset=0x00D8 : CFG_GPIOT_PTEN_3A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PORTEN:32;                                  /* [31:0] */
    } BIT;
  } CFG_GPIOT_PTEN_3A;
  union                                            /* Offset=0x00DC : CFG_GPIOT_PTEN_3B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PORTEN:10;                                  /* [9:0] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } CFG_GPIOT_PTEN_3B;
  union                                            /* Offset=0x00E0 : PWRCTRL_OPPDIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:5;                                      /* [4:0] */
      __IO unsigned long   :26;                                        /* [30:5] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_OPPDIV;
  union                                            /* Offset=0x00E4 : PWRCTRL_CA7DIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:3;                                      /* [2:0] */
      __IO unsigned long   :28;                                        /* [30:3] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_CA7DIV;
  union                                            /* Offset=0x00E8 : PWRCTRL_PG2_25MHZ */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_Q:1;                                  /* [0] */
      __IO unsigned long   RSTN_Q:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_Q:1;                                 /* [2] */
      __IO unsigned long   CLKEN_R:1;                                  /* [3] */
      __IO unsigned long   RSTN_R:1;                                   /* [4] */
      __IO unsigned long   SLVRDY_R:1;                                 /* [5] */
      __IO unsigned long   CLKEN_S:1;                                  /* [6] */
      __IO unsigned long   RSTN_S:1;                                   /* [7] */
      __IO unsigned long   SLVRDY_S:1;                                 /* [8] */
      __IO unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } PWRCTRL_PG2_25MHZ;
  union                                            /* Offset=0x00EC : PWRCTRL_PG1_PR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_AG1:1;                                /* [0] */
      __IO unsigned long   RSTN_AG1:1;                                 /* [1] */
      __IO unsigned long   CLKEN_AG2:1;                                /* [2] */
      __IO unsigned long   RSTN_AG2:1;                                 /* [3] */
      __IO unsigned long   CLKEN_AH1:1;                                /* [4] */
      __IO unsigned long   RSTN_AH1:1;                                 /* [5] */
      __IO unsigned long   CLKEN_AH2:1;                                /* [6] */
      __IO unsigned long   RSTN_AH2:1;                                 /* [7] */
      __IO unsigned long   CLKEN_AI1:1;                                /* [8] */
      __IO unsigned long   RSTN_AI1:1;                                 /* [9] */
      __IO unsigned long   CLKEN_AI2:1;                                /* [10] */
      __IO unsigned long   RSTN_AI2:1;                                 /* [11] */
      __IO unsigned long   CLKEN_AJ1:1;                                /* [12] */
      __IO unsigned long   RSTN_AJ1:1;                                 /* [13] */
      __IO unsigned long   CLKEN_AJ2:1;                                /* [14] */
      __IO unsigned long   RSTN_AJ2:1;                                 /* [15] */
      __IO unsigned long   CLKEN_AK1:1;                                /* [16] */
      __IO unsigned long   RSTN_AK1:1;                                 /* [17] */
      __IO unsigned long   CLKEN_AK2:1;                                /* [18] */
      __IO unsigned long   RSTN_AK2:1;                                 /* [19] */
      __IO unsigned long   :4;                                         /* [23:20] */
      __IO unsigned long   UARTCLKSEL:1;                               /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } PWRCTRL_PG1_PR2;
  union                                            /* Offset=0x00F0 : PWRCTRL_PG3_48MHZ */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   CLKEN_Z:1;                                  /* [3] */
      __IO unsigned long   RSTN_Z:1;                                   /* [4] */
      __IO unsigned long   SLVRDY_Z:1;                                 /* [5] */
      __IO unsigned long   CLKEN_AA:1;                                 /* [6] */
      __IO unsigned long   RSTN_AA:1;                                  /* [7] */
      __IO unsigned long   SLVRDY_AA:1;                                /* [8] */
      __IO unsigned long   :3;                                         /* [11:9] */
      __IO unsigned long   CLKEN_UF:1;                                 /* [12] */
      __IO unsigned long   RSTN_UF:1;                                  /* [13] */
      __IO unsigned long   MIREQ_UF:1;                                 /* [14] */
      __IO unsigned long   :17;                                        /* [31:15] */
    } BIT;
  } PWRCTRL_PG3_48MHZ;
  union                                            /* Offset=0x00F4 : PWRCTRL_PG4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_AC:1;                                 /* [0] */
      __IO unsigned long   RSTN_AC:1;                                  /* [1] */
      __IO unsigned long   SLVRDY_AC:1;                                /* [2] */
      __IO unsigned long   CLKEN_AD:1;                                 /* [3] */
      __IO unsigned long   RSTN_AD:1;                                  /* [4] */
      __IO unsigned long   SLVRDY_AD:1;                                /* [5] */
      __IO unsigned long   :6;                                         /* [11:6] */
      __IO unsigned long   CLKEN_UI:1;                                 /* [12] */
      __IO unsigned long   RSTN_UI:1;                                  /* [13] */
      __IO unsigned long   MIREQ_UI:1;                                 /* [14] */
      __IO unsigned long   :17;                                        /* [31:15] */
    } BIT;
  } PWRCTRL_PG4;
  union                                            /* Offset=0x00F8 : PWRCTRL_PG1_PR2DIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:8;                                      /* [7:0] */
      __IO unsigned long   :23;                                        /* [30:8] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_PG1_PR2DIV;
  union                                            /* Offset=0x00FC : PWRCTRL_PG1_PR3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_AM:1;                                 /* [0] */
      __IO unsigned long   RSTN_AM:1;                                  /* [1] */
      __IO unsigned long   CLKEN_AN:1;                                 /* [2] */
      __IO unsigned long   RSTN_AN:1;                                  /* [3] */
      __IO unsigned long   CLKEN_AO:1;                                 /* [4] */
      __IO unsigned long   RSTN_AO:1;                                  /* [5] */
      __IO unsigned long   CLKEN_AP:1;                                 /* [6] */
      __IO unsigned long   RSTN_AP:1;                                  /* [7] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } PWRCTRL_PG1_PR3;
  union                                            /* Offset=0x0100 : PWRCTRL_PG1_PR3DIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:8;                                      /* [7:0] */
      __IO unsigned long   :23;                                        /* [30:8] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_PG1_PR3DIV;
  union                                            /* Offset=0x0104 : PWRCTRL_PG1_PR4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_AQ:1;                                 /* [0] */
      __IO unsigned long   RSTN_AQ:1;                                  /* [1] */
      __IO unsigned long   CLKEN_AR:1;                                 /* [2] */
      __IO unsigned long   RSTN_AR:1;                                  /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } PWRCTRL_PG1_PR4;
  union                                            /* Offset=0x0108 : PWRCTRL_PG1_PR4DIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:8;                                      /* [7:0] */
      __IO unsigned long   :23;                                        /* [30:8] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_PG1_PR4DIV;
  union                                            /* Offset=0x010C : PWRCTRL_PG4_PR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_AU:1;                                 /* [0] */
      __IO unsigned long   RSTN_AU:1;                                  /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } PWRCTRL_PG4_PR1;
  union                                            /* Offset=0x0110 : PWRCTRL_PG4_PR1DIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:8;                                      /* [7:0] */
      __IO unsigned long   :23;                                        /* [30:8] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_PG4_PR1DIV;
  char                     wk_0114[0x000C];
  union                                            /* Offset=0x0120 : RSTEN */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MRESET_EN:1;                                /* [0] */
      __IO unsigned long   WDA7RST_EN:2;                               /* [2:1] */
      __IO unsigned long   WDM3RST_EN:1;                               /* [3] */
      __IO unsigned long   CM3LOCKUPRST_EN:1;                          /* [4] */
      __IO unsigned long   CM3SYSRESET_EN:1;                           /* [5] */
      __IO unsigned long   SWRST_EN:1;                                 /* [6] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } RSTEN;
  union                                            /* Offset=0x0124 : PWRCTRL_QSPI1DIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:7;                                      /* [6:0] */
      __IO unsigned long   :24;                                        /* [30:7] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_QSPI1DIV;
  union                                            /* Offset=0x0128 : PWRCTRL_SDIO1DIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:8;                                      /* [7:0] */
      __IO unsigned long   :23;                                        /* [30:8] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_SDIO1DIV;
  union                                            /* Offset=0x012C : PWRCTRL_SDIO2DIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:8;                                      /* [7:0] */
      __IO unsigned long   :23;                                        /* [30:8] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_SDIO2DIV;
  union                                            /* Offset=0x0130 : PWRCTRL_SWITCH */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [1] */
      __IO unsigned long   CLKEN_B:1;                                  /* [2] */
      __IO unsigned long   RSTN_B:1;                                   /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } PWRCTRL_SWITCH;
  union                                            /* Offset=0x0134 : PWRCTRL_PG0_ADCDIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:10;                                     /* [9:0] */
      __IO unsigned long   :21;                                        /* [30:10] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_PG0_ADCDIV;
  union                                            /* Offset=0x0138 : PWRCTRL_PG0_I2CDIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:7;                                      /* [6:0] */
      __IO unsigned long   :24;                                        /* [30:7] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_PG0_I2CDIV;
  union                                            /* Offset=0x013C : PWRCTRL_PG0_UARTDIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:8;                                      /* [7:0] */
      __IO unsigned long   :23;                                        /* [30:8] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_PG0_UARTDIV;
  union                                            /* Offset=0x0140 : PWRCTRL_RTC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_RTC:1;                                /* [0] */
      __IO unsigned long   RST_RTC:1;                                  /* [1] */
      __IO unsigned long   IDLE_REQ:1;                                 /* [2] */
      __IO unsigned long   RSTN_FW_RTC:1;                              /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } PWRCTRL_RTC;
  union                                            /* Offset=0x0144 : PWRSTAT_RTC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTC_IACK:1;                                 /* [0] */
      __I  unsigned long   RTC_IDLE:1;                                 /* [1] */
      __I  unsigned long   PWR_GOOD:1;                                 /* [2] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRSTAT_RTC;
  union                                            /* Offset=0x0148 : PWRCTRL_NFLASHDIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:7;                                      /* [6:0] */
      __IO unsigned long   :24;                                        /* [30:7] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_NFLASHDIV;
  char                     wk_014C[0x0008];
  union                                            /* Offset=0x0154 : PWRCTRL_ROM */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRCTRL_ROM;
  union                                            /* Offset=0x0158 : PWRSTAT_PG1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   SCON_B:1;                                   /* [1] */
      __I  unsigned long   SCON_C:1;                                   /* [2] */
      __I  unsigned long   SCON_D:1;                                   /* [3] */
      __I  unsigned long   SCON_E:1;                                   /* [4] */
      __I  unsigned long   SCON_F:1;                                   /* [5] */
      __I  unsigned long   SCON_G:1;                                   /* [6] */
      __I  unsigned long   SCON_H:1;                                   /* [7] */
      __I  unsigned long   SCON_I:1;                                   /* [8] */
      __I  unsigned long   SCON_J:1;                                   /* [9] */
      __I  unsigned long   SCON_K:1;                                   /* [10] */
      __I  unsigned long   SCON_L:1;                                   /* [11] */
      __I  unsigned long   SCON_M:1;                                   /* [12] */
      __I  unsigned long   SCON_N:1;                                   /* [13] */
      __I  unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } PWRSTAT_PG1;
  union                                            /* Offset=0x015C : PWRSTAT_PG2_25MHZ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_Q:1;                                   /* [0] */
      __I  unsigned long   SCON_R:1;                                   /* [1] */
      __I  unsigned long   SCON_S:1;                                   /* [2] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRSTAT_PG2_25MHZ;
  union                                            /* Offset=0x0160 : PWRSTAT_PG3_48MHZ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :1;                                         /* [0] */
      __I  unsigned long   SCON_Z:1;                                   /* [1] */
      __I  unsigned long   SCON_AA:1;                                  /* [2] */
      __I  unsigned long   :1;                                         /* [3] */
      __I  unsigned long   MIRACK_UF:1;                                /* [4] */
      __I  unsigned long   MISTAT_UF:1;                                /* [5] */
      __I  unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PWRSTAT_PG3_48MHZ;
  union                                            /* Offset=0x0164 : PWRSTAT_PG4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_AC:1;                                  /* [0] */
      __I  unsigned long   SCON_AD:1;                                  /* [1] */
      __I  unsigned long   :2;                                         /* [3:2] */
      __I  unsigned long   MIRACK_UI:1;                                /* [4] */
      __I  unsigned long   MISTAT_UI:1;                                /* [5] */
      __I  unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PWRSTAT_PG4;
  char                     wk_0168[0x0008];
  union                                            /* Offset=0x0170 : PWRSTAT_ROM */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } PWRSTAT_ROM;
  union                                            /* Offset=0x0174 : PWRCTRL_CM3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   MIREQ_A:1;                                  /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRCTRL_CM3;
  union                                            /* Offset=0x0178 : PWRSTAT_CM3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MIRACK_A:1;                                 /* [0] */
      __I  unsigned long   MISTAT_A:1;                                 /* [1] */
      __I  unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } PWRSTAT_CM3;
  union                                            /* Offset=0x017C : PWRSTAT_RINCTRL */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } PWRSTAT_RINCTRL;
  union                                            /* Offset=0x0180 : PWRSTAT_SWITCHCTRL */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SCON_A:1;                                   /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } PWRSTAT_SWITCHCTRL;
  union                                            /* Offset=0x0184 : PWRCTRL_RINCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRCTRL_RINCTRL;
  union                                            /* Offset=0x0188 : PWRCTRL_SWITCHCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   SLVRDY_A:1;                                 /* [2] */
      __IO unsigned long   RSTN_CLK25:1;                               /* [3] */
      __IO unsigned long   RSTN_ETH:1;                                 /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } PWRCTRL_SWITCHCTRL;
  union                                            /* Offset=0x018C : PWRCTRL_HWRTOS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CLKEN_A:1;                                  /* [0] */
      __IO unsigned long   RSTN_A:1;                                   /* [1] */
      __IO unsigned long   CLKEN_B:1;                                  /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PWRCTRL_HWRTOS;
  union                                            /* Offset=0x0190 : PWRCTRL_HWRTOS_MDCDIV */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DIV:10;                                     /* [9:0] */
      __IO unsigned long   :21;                                        /* [30:10] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } PWRCTRL_HWRTOS_MDCDIV;
  char                     wk_0194[0x0004];
  union                                            /* Offset=0x0198 : RSTCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   WDA7RST_REQ:2;                              /* [2:1] */
      __IO unsigned long   WDM3RST_REQ:1;                              /* [3] */
      __IO unsigned long   CM3LOCKUPRST_REQ:1;                         /* [4] */
      __IO unsigned long   CM3SYSRESET_REQ:1;                          /* [5] */
      __IO unsigned long   SWRST_REQ:1;                                /* [6] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } RSTCTRL;
  union                                            /* Offset=0x019C : VERSION */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :8;                                         /* [7:0] */
      __I  unsigned long   PROD:1;                                     /* [8] */
      __I  unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } VERSION;
  char                     wk_01A0[0x0064];
  union                                            /* Offset=0x0204 : BOOTADDR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BOOTADDR:32;                                /* [31:0] */
    } BIT;
  } BOOTADDR;
} SYSCTRL_Type;
#endif  /* End of __SYSCTRL_SFR__DEFINE_HEADER__ */
