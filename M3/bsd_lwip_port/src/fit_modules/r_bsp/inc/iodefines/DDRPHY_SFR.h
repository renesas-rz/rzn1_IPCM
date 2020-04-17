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
 **       for RZN1 DDRPHY
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __DDRPHY_SFR__DEFINE_HEADER__
#define __DDRPHY_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : DDRPHY
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : FUNCCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FUNCRSTB:1;                                 /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   IFSEL:2;                                    /* [9:8] */
      __IO unsigned long   :6;                                         /* [15:10] */
      __IO unsigned long   MASKSDLOFS:7;                               /* [22:16] */
      __IO unsigned long   :9;                                         /* [31:23] */
    } BIT;
  } FUNCCTRL;
  union                                            /* Offset=0x0004 : DLLCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MDLLSTBY:1;                                 /* [0] */
      __IO unsigned long   MFSL:2;                                     /* [2:1] */
      __IO unsigned long   DDMODE:1;                                   /* [3] */
      __IO unsigned long   MSATMODE:1;                                 /* [4] */
      __IO unsigned long   HSLMODE:1;                                  /* [5] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   MDACNT:10;                                  /* [17:8] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __O  unsigned long   DACNTUPD:1;                                 /* [20] */
      __IO unsigned long   SDLYCTRL:1;                                 /* [21] */
      __O  unsigned long   MDACNTM:1;                                  /* [22] */
      __IO unsigned long   :1;                                         /* [23] */
      __I  unsigned long   MSATFG:1;                                   /* [24] */
      __I  unsigned long   MDLLOCK:1;                                  /* [25] */
      __I  unsigned long   ASDLLOCK:1;                                 /* [26] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } DLLCTRL;
  union                                            /* Offset=0x0008 : ZQCALCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ZQCALRSTB:1;                                /* [0] */
      __IO unsigned long   ZQCALSTRV:1;                                /* [1] */
      __IO unsigned long   ZQCALMODE:1;                                /* [2] */
      __IO unsigned long   :1;                                         /* [3] */
      __IO unsigned long   ZQCALITVL:4;                                /* [7:4] */
      __IO unsigned long   ZQCALFREQ:2;                                /* [9:8] */
      __IO unsigned long   :4;                                         /* [13:10] */
      __I  unsigned long   ZQCALINIT:1;                                /* [14] */
      __I  unsigned long   ZQCALNF:4;                                  /* [18:15] */
      __I  unsigned long   ZQCALNC:3;                                  /* [21:19] */
      __I  unsigned long   ZQCALPF:4;                                  /* [25:22] */
      __I  unsigned long   ZQCALPC:3;                                  /* [28:26] */
      __I  unsigned long   ZQCALGAP:1;                                 /* [29] */
      __I  unsigned long   ZQCALEND:1;                                 /* [30] */
      __I  unsigned long   ZQCALRUN:1;                                 /* [31] */
    } BIT;
  } ZQCALCTRL;
  union                                            /* Offset=0x000C : ZQODTCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DRAMIF:2;                                   /* [1:0] */
      __IO unsigned long   :2;                                         /* [3:2] */
      __IO unsigned long   PHYODTEN:1;                                 /* [4] */
      __IO unsigned long   PHYODT:2;                                   /* [6:5] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   SRCMDAD:2;                                  /* [9:8] */
      __IO unsigned long   SRCK:2;                                     /* [11:10] */
      __IO unsigned long   SRDQ:2;                                     /* [13:12] */
      __IO unsigned long   :1;                                         /* [14] */
      __IO unsigned long   ZQCMDAD:4;                                  /* [18:15] */
      __IO unsigned long   ZQCK:4;                                     /* [22:19] */
      __IO unsigned long   ZQDATA:4;                                   /* [26:23] */
      __IO unsigned long   FIFORPINIT:2;                               /* [28:27] */
      __IO unsigned long   WRFIFOEN:1;                                 /* [29] */
      __IO unsigned long   CAPHASE:2;                                  /* [31:30] */
    } BIT;
  } ZQODTCTRL;
  union                                            /* Offset=0x0010 : RDCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PHYIENOFT:4;                                /* [3:0] */
      __IO unsigned long   PHYIENONT:4;                                /* [7:4] */
      __IO unsigned long   PHYBENOFT:4;                                /* [11:8] */
      __IO unsigned long   PHYBENONT:4;                                /* [15:12] */
      __IO unsigned long   PDQODTOFT:4;                                /* [19:16] */
      __IO unsigned long   PDQODTONT:4;                                /* [23:20] */
      __IO unsigned long   PHYODTOFT:4;                                /* [27:24] */
      __IO unsigned long   PHYODTONT:4;                                /* [31:28] */
    } BIT;
  } RDCTRL;
  union                                            /* Offset=0x0014 : RDTMG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WDOMODE:2;                                  /* [1:0] */
      __IO unsigned long   :2;                                         /* [3:2] */
      __IO unsigned long   RDENVALID:4;                                /* [7:4] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } RDTMG;
  union                                            /* Offset=0x0018 : FIFOINIT */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   WRPTINITEXE:1;                              /* [0] */
      __O  unsigned long   :7;                                         /* [7:1] */
      __O  unsigned long   RDPTINITEXE:1;                              /* [8] */
      __O  unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } FIFOINIT;
  union                                            /* Offset=0x001C : OUTCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADCMDOE:1;                                  /* [0] */
      __IO unsigned long   CKEODTOE:1;                                 /* [1] */
      __IO unsigned long   RESETBOE:1;                                 /* [2] */
      __IO unsigned long   :1;                                         /* [3] */
      __IO unsigned long   DISOUT:2;                                   /* [5:4] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   MWL:5;                                      /* [12:8] */
      __IO unsigned long   :3;                                         /* [15:13] */
      __IO unsigned long   MRL:5;                                      /* [20:16] */
      __IO unsigned long   :3;                                         /* [23:21] */
      __IO unsigned long   MBL:2;                                      /* [25:24] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } OUTCTRL;
  char                     wk_0020[0x0020];
  union                                            /* Offset=0x0040 : WLCTRL1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WL1OFS:7;                                   /* [6:0] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   WL2OFS:7;                                   /* [14:8] */
      __IO unsigned long   :9;                                         /* [23:15] */
      __O  unsigned long   WLSTR:1;                                    /* [24] */
      __IO unsigned long   WLSTATE:2;                                  /* [26:25] */
      __IO unsigned long   :1;                                         /* [27] */
      __I  unsigned long   WLVEND:1;                                   /* [28] */
      __IO unsigned long   :1;                                         /* [29] */
      __IO unsigned long   WLAUTO:1;                                   /* [30] */
      __IO unsigned long   WLEN:1;                                     /* [31] */
    } BIT;
  } WLCTRL1;
  char                     wk_0044[0x00A4];
  union                                            /* Offset=0x00E8 : DQCALOFS1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DQCAL1OFS:7;                                /* [6:0] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   DQCAL2OFS:7;                                /* [14:8] */
      __IO unsigned long   :15;                                        /* [29:15] */
      __I  unsigned long   B1RSSAT:1;                                  /* [30] */
      __I  unsigned long   B2RSSAT:1;                                  /* [31] */
    } BIT;
  } DQCALOFS1;
} DDRPHY_Type;
#endif  /* End of __DDRPHY_SFR__DEFINE_HEADER__ */
