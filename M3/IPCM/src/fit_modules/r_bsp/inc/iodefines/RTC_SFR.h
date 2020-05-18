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
 **       for RZN1 RTC
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __RTC_SFR__DEFINE_HEADER__
#define __RTC_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : RTC
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : RTCA0CTL0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :4;                                         /* [3:0] */
      __IO unsigned long   RTCA0SLSB:1;                                /* [4] */
      __IO unsigned long   RTCA0AMPM:1;                                /* [5] */
      __I  unsigned long   RTCA0CEST:1;                                /* [6] */
      __IO unsigned long   RTCA0CE:1;                                  /* [7] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } RTCA0CTL0;
  union                                            /* Offset=0x0004 : RTCA0CTL1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0CT:3;                                  /* [2:0] */
      __IO unsigned long   RTCA01SE:1;                                 /* [3] */
      __IO unsigned long   RTCA0ALME:1;                                /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } RTCA0CTL1;
  union                                            /* Offset=0x0008 : RTCA0CTL2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0WAIT:1;                                /* [0] */
      __I  unsigned long   RTCA0WST:1;                                 /* [1] */
      __IO unsigned long   RTCA0RSUB:1;                                /* [2] */
      __I  unsigned long   RTCA0RSST:1;                                /* [3] */
      __I  unsigned long   RTCA0WSST:1;                                /* [4] */
      __I  unsigned long   RTCA0WUST:1;                                /* [5] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } RTCA0CTL2;
  union                                            /* Offset=0x000C : RTCA0SUBC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTCA0SUBC:22;                               /* [21:0] */
      __I  unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } RTCA0SUBC;
  union                                            /* Offset=0x0010 : RTCA0SRBU */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTCA0SRBU:22;                               /* [21:0] */
      __I  unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } RTCA0SRBU;
  union                                            /* Offset=0x0014 : RTCA0SEC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0SEC:7;                                 /* [6:0] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } RTCA0SEC;
  union                                            /* Offset=0x0018 : RTCA0MIN */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0MIN:7;                                 /* [6:0] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } RTCA0MIN;
  union                                            /* Offset=0x001C : RTCA0HOUR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0HOUR:6;                                /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } RTCA0HOUR;
  union                                            /* Offset=0x0020 : RTCA0WEEK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0WEEK:3;                                /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } RTCA0WEEK;
  union                                            /* Offset=0x0024 : RTCA0DAY */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0DAY:6;                                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } RTCA0DAY;
  union                                            /* Offset=0x0028 : RTCA0MONTH */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0MONTH:5;                               /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } RTCA0MONTH;
  union                                            /* Offset=0x002C : RTCA0YEAR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0YEAR:8;                                /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } RTCA0YEAR;
  union                                            /* Offset=0x0030 : RTCA0TIME */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0SEC:8;                                 /* [7:0] */
      __IO unsigned long   RTCA0MIN:8;                                 /* [15:8] */
      __IO unsigned long   RTCA0HOUR:8;                                /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } RTCA0TIME;
  union                                            /* Offset=0x0034 : RTCA0CAL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0WEEK:8;                                /* [7:0] */
      __IO unsigned long   RTCA0DAY:8;                                 /* [15:8] */
      __IO unsigned long   RTCA0MONTH:8;                               /* [23:16] */
      __IO unsigned long   RTCA0YEAR:8;                                /* [31:24] */
    } BIT;
  } RTCA0CAL;
  union                                            /* Offset=0x0038 : RTCA0SUBU */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0F0:1;                                  /* [0] */
      __IO unsigned long   RTCA0F1:1;                                  /* [1] */
      __IO unsigned long   RTCA0F2:1;                                  /* [2] */
      __IO unsigned long   RTCA0F3:1;                                  /* [3] */
      __IO unsigned long   RTCA0F4:1;                                  /* [4] */
      __IO unsigned long   RTCA0F5:1;                                  /* [5] */
      __IO unsigned long   RTCA0F6:1;                                  /* [6] */
      __IO unsigned long   RTCA0DEV:1;                                 /* [7] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } RTCA0SUBU;
  union                                            /* Offset=0x003C : RTCA0SCMP */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0SCMP:22;                               /* [21:0] */
      __IO unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } RTCA0SCMP;
  union                                            /* Offset=0x0040 : RTCA0ALM */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0ALM:7;                                 /* [6:0] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } RTCA0ALM;
  union                                            /* Offset=0x0044 : RTCA0ALH */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0ALH:6;                                 /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } RTCA0ALH;
  union                                            /* Offset=0x0048 : RTCA0ALW */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RTCA0ALW0:1;                                /* [0] */
      __IO unsigned long   RTCA0ALW1:1;                                /* [1] */
      __IO unsigned long   RTCA0ALW2:1;                                /* [2] */
      __IO unsigned long   RTCA0ALW3:1;                                /* [3] */
      __IO unsigned long   RTCA0ALW4:1;                                /* [4] */
      __IO unsigned long   RTCA0ALW5:1;                                /* [5] */
      __IO unsigned long   RTCA0ALW6:1;                                /* [6] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } RTCA0ALW;
  union                                            /* Offset=0x004C : RTCA0SECC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTCA0SECC:7;                                /* [6:0] */
      __I  unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } RTCA0SECC;
  union                                            /* Offset=0x0050 : RTCA0MINC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTCA0MINC:7;                                /* [6:0] */
      __I  unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } RTCA0MINC;
  union                                            /* Offset=0x0054 : RTCA0HOURC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTCA0HOURC:6;                               /* [5:0] */
      __I  unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } RTCA0HOURC;
  union                                            /* Offset=0x0058 : RTCA0WEEKC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTCA0WEEKC:3;                               /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } RTCA0WEEKC;
  union                                            /* Offset=0x005C : RTCA0DAYC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTCA0DAYC:6;                                /* [5:0] */
      __I  unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } RTCA0DAYC;
  union                                            /* Offset=0x0060 : RTCA0MONC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTCA0MONC:5;                                /* [4:0] */
      __I  unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } RTCA0MONC;
  union                                            /* Offset=0x0064 : RTCA0YEARC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTCA0YEARC:8;                               /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } RTCA0YEARC;
  union                                            /* Offset=0x0068 : RTCA0TIMEC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTCA0SECC:8;                                /* [7:0] */
      __I  unsigned long   RTCA0MINC:8;                                /* [15:8] */
      __I  unsigned long   RTCA0HOURC:8;                               /* [23:16] */
      __I  unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } RTCA0TIMEC;
  union                                            /* Offset=0x006C : RTCA0CALC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RTCA0WEEKC:8;                               /* [7:0] */
      __I  unsigned long   RTCA0DAYC:8;                                /* [15:8] */
      __I  unsigned long   RTCA0MONC:8;                                /* [23:16] */
      __I  unsigned long   RTCA0YEARC:8;                               /* [31:24] */
    } BIT;
  } RTCA0CALC;
  union                                            /* Offset=0x0070 : RTCA0TCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   RTCA0OS1:1;                                 /* [1] */
      __IO unsigned long   RTCA0OS2:1;                                 /* [2] */
      __IO unsigned long   RTCA0OS3:1;                                 /* [3] */
      __IO unsigned long   :11;                                        /* [14:4] */
      __IO unsigned long   RTCA0OSE:1;                                 /* [15] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RTCA0TCR;
} RTC_Type;
#endif  /* End of __RTC_SFR__DEFINE_HEADER__ */
