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
 **       for RZN1 HSR
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __HSR_SFR__DEFINE_HEADER__
#define __HSR_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : HSR
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : RCI_WCONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WFS:12;                                     /* [11:0] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   I:1;                                        /* [16] */
      __IO unsigned long   A:1;                                        /* [17] */
      __IO unsigned long   B:1;                                        /* [18] */
      __IO unsigned long   TAG:1;                                      /* [19] */
      __IO unsigned long   PTH:4;                                      /* [23:20] */
      __IO unsigned long   :4;                                         /* [27:24] */
      __IO unsigned long   END:1;                                      /* [28] */
      __IO unsigned long   :2;                                         /* [30:29] */
      __IO unsigned long   SB:1;                                       /* [31] */
    } BIT;
  } RCI_WCONFIG;
  union                                            /* Offset=0x0004 : RCI_RCONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   RFS:12;                                     /* [11:0] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __I  unsigned long   RPT:2;                                      /* [17:16] */
      __I  unsigned long   TAG:2;                                      /* [19:18] */
      __IO unsigned long   :8;                                         /* [27:20] */
      __IO unsigned long   END:1;                                      /* [28] */
      __IO unsigned long   :1;                                         /* [29] */
      __I  unsigned long   FP:1;                                       /* [30] */
      __O  unsigned long   RFD:1;                                      /* [31] */
    } BIT;
  } RCI_RCONFIG;
  union                                            /* Offset=0x0008 : RCI_INT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXI:1;                                      /* [0] */
      __I  unsigned long   TXI:1;                                      /* [1] */
      __I  unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } RCI_INT;
  union                                            /* Offset=0x000C : RCI_TXRX_DATA0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA0;
  union                                            /* Offset=0x0010 : RCI_TXRX_DATA1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA1;
  union                                            /* Offset=0x0014 : RCI_TXRX_DATA2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA2;
  union                                            /* Offset=0x0018 : RCI_TXRX_DATA3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA3;
  union                                            /* Offset=0x001C : RCI_TXRX_DATA4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA4;
  union                                            /* Offset=0x0020 : RCI_TXRX_DATA5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA5;
  union                                            /* Offset=0x0024 : RCI_TXRX_DATA6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA6;
  union                                            /* Offset=0x0028 : RCI_TXRX_DATA7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA7;
  union                                            /* Offset=0x002C : RCI_TXRX_DATA8 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA8;
  union                                            /* Offset=0x0030 : RCI_TXRX_DATA9 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA9;
  union                                            /* Offset=0x0034 : RCI_TXRX_DATA10 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA10;
  union                                            /* Offset=0x0038 : RCI_TXRX_DATA11 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA11;
  union                                            /* Offset=0x003C : RCI_TXRX_DATA12 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA12;
  union                                            /* Offset=0x0040 : RCI_TXRX_DATA13 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA13;
  union                                            /* Offset=0x0044 : RCI_TXRX_DATA14 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA14;
  union                                            /* Offset=0x0048 : RCI_TXRX_DATA15 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA15;
  union                                            /* Offset=0x004C : RCI_TXRX_DATA16 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA16;
  union                                            /* Offset=0x0050 : RCI_TXRX_DATA17 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA17;
  union                                            /* Offset=0x0054 : RCI_TXRX_DATA18 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA18;
  union                                            /* Offset=0x0058 : RCI_TXRX_DATA19 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA19;
  union                                            /* Offset=0x005C : RCI_TXRX_DATA20 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA20;
  union                                            /* Offset=0x0060 : RCI_TXRX_DATA21 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA21;
  union                                            /* Offset=0x0064 : RCI_TXRX_DATA22 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA22;
  union                                            /* Offset=0x0068 : RCI_TXRX_DATA23 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA23;
  union                                            /* Offset=0x006C : RCI_TXRX_DATA24 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA24;
  union                                            /* Offset=0x0070 : RCI_TXRX_DATA25 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA25;
  union                                            /* Offset=0x0074 : RCI_TXRX_DATA26 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA26;
  union                                            /* Offset=0x0078 : RCI_TXRX_DATA27 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA27;
  union                                            /* Offset=0x007C : RCI_TXRX_DATA28 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA28;
  union                                            /* Offset=0x0080 : RCI_TXRX_DATA29 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA29;
  union                                            /* Offset=0x0084 : RCI_TXRX_DATA30 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA30;
  union                                            /* Offset=0x0088 : RCI_TXRX_DATA31 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA31;
  union                                            /* Offset=0x008C : RCI_TXRX_DATA32 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA32;
  union                                            /* Offset=0x0090 : RCI_TXRX_DATA33 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA33;
  union                                            /* Offset=0x0094 : RCI_TXRX_DATA34 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA34;
  union                                            /* Offset=0x0098 : RCI_TXRX_DATA35 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA35;
  union                                            /* Offset=0x009C : RCI_TXRX_DATA36 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA36;
  union                                            /* Offset=0x00A0 : RCI_TXRX_DATA37 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA37;
  union                                            /* Offset=0x00A4 : RCI_TXRX_DATA38 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA38;
  union                                            /* Offset=0x00A8 : RCI_TXRX_DATA39 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA39;
  union                                            /* Offset=0x00AC : RCI_TXRX_DATA40 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA40;
  union                                            /* Offset=0x00B0 : RCI_TXRX_DATA41 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA41;
  union                                            /* Offset=0x00B4 : RCI_TXRX_DATA42 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA42;
  union                                            /* Offset=0x00B8 : RCI_TXRX_DATA43 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA43;
  union                                            /* Offset=0x00BC : RCI_TXRX_DATA44 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA44;
  union                                            /* Offset=0x00C0 : RCI_TXRX_DATA45 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA45;
  union                                            /* Offset=0x00C4 : RCI_TXRX_DATA46 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA46;
  union                                            /* Offset=0x00C8 : RCI_TXRX_DATA47 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA47;
  union                                            /* Offset=0x00CC : RCI_TXRX_DATA48 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA48;
  union                                            /* Offset=0x00D0 : RCI_TXRX_DATA49 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA49;
  union                                            /* Offset=0x00D4 : RCI_TXRX_DATA50 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA50;
  union                                            /* Offset=0x00D8 : RCI_TXRX_DATA51 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA51;
  union                                            /* Offset=0x00DC : RCI_TXRX_DATA52 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA52;
  union                                            /* Offset=0x00E0 : RCI_TXRX_DATA53 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA53;
  union                                            /* Offset=0x00E4 : RCI_TXRX_DATA54 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA54;
  union                                            /* Offset=0x00E8 : RCI_TXRX_DATA55 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA55;
  union                                            /* Offset=0x00EC : RCI_TXRX_DATA56 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA56;
  union                                            /* Offset=0x00F0 : RCI_TXRX_DATA57 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA57;
  union                                            /* Offset=0x00F4 : RCI_TXRX_DATA58 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA58;
  union                                            /* Offset=0x00F8 : RCI_TXRX_DATA59 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA59;
  union                                            /* Offset=0x00FC : RCI_TXRX_DATA60 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA60;
  union                                            /* Offset=0x0100 : RCI_TXRX_DATA61 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA61;
  union                                            /* Offset=0x0104 : RCI_TXRX_DATA62 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA62;
  union                                            /* Offset=0x0108 : RCI_TXRX_DATA63 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA63;
  union                                            /* Offset=0x010C : RCI_TXRX_DATA64 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA64;
  union                                            /* Offset=0x0110 : RCI_TXRX_DATA65 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA65;
  union                                            /* Offset=0x0114 : RCI_TXRX_DATA66 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA66;
  union                                            /* Offset=0x0118 : RCI_TXRX_DATA67 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA67;
  union                                            /* Offset=0x011C : RCI_TXRX_DATA68 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA68;
  union                                            /* Offset=0x0120 : RCI_TXRX_DATA69 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA69;
  union                                            /* Offset=0x0124 : RCI_TXRX_DATA70 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA70;
  union                                            /* Offset=0x0128 : RCI_TXRX_DATA71 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA71;
  union                                            /* Offset=0x012C : RCI_TXRX_DATA72 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA72;
  union                                            /* Offset=0x0130 : RCI_TXRX_DATA73 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA73;
  union                                            /* Offset=0x0134 : RCI_TXRX_DATA74 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA74;
  union                                            /* Offset=0x0138 : RCI_TXRX_DATA75 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA75;
  union                                            /* Offset=0x013C : RCI_TXRX_DATA76 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA76;
  union                                            /* Offset=0x0140 : RCI_TXRX_DATA77 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA77;
  union                                            /* Offset=0x0144 : RCI_TXRX_DATA78 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA78;
  union                                            /* Offset=0x0148 : RCI_TXRX_DATA79 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA79;
  union                                            /* Offset=0x014C : RCI_TXRX_DATA80 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA80;
  union                                            /* Offset=0x0150 : RCI_TXRX_DATA81 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA81;
  union                                            /* Offset=0x0154 : RCI_TXRX_DATA82 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA82;
  union                                            /* Offset=0x0158 : RCI_TXRX_DATA83 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA83;
  union                                            /* Offset=0x015C : RCI_TXRX_DATA84 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA84;
  union                                            /* Offset=0x0160 : RCI_TXRX_DATA85 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA85;
  union                                            /* Offset=0x0164 : RCI_TXRX_DATA86 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA86;
  union                                            /* Offset=0x0168 : RCI_TXRX_DATA87 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA87;
  union                                            /* Offset=0x016C : RCI_TXRX_DATA88 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA88;
  union                                            /* Offset=0x0170 : RCI_TXRX_DATA89 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA89;
  union                                            /* Offset=0x0174 : RCI_TXRX_DATA90 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA90;
  union                                            /* Offset=0x0178 : RCI_TXRX_DATA91 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA91;
  union                                            /* Offset=0x017C : RCI_TXRX_DATA92 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA92;
  union                                            /* Offset=0x0180 : RCI_TXRX_DATA93 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA93;
  union                                            /* Offset=0x0184 : RCI_TXRX_DATA94 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA94;
  union                                            /* Offset=0x0188 : RCI_TXRX_DATA95 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA95;
  union                                            /* Offset=0x018C : RCI_TXRX_DATA96 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA96;
  union                                            /* Offset=0x0190 : RCI_TXRX_DATA97 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA97;
  union                                            /* Offset=0x0194 : RCI_TXRX_DATA98 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA98;
  union                                            /* Offset=0x0198 : RCI_TXRX_DATA99 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA99;
  union                                            /* Offset=0x019C : RCI_TXRX_DATA100 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA100;
  union                                            /* Offset=0x01A0 : RCI_TXRX_DATA101 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA101;
  union                                            /* Offset=0x01A4 : RCI_TXRX_DATA102 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA102;
  union                                            /* Offset=0x01A8 : RCI_TXRX_DATA103 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA103;
  union                                            /* Offset=0x01AC : RCI_TXRX_DATA104 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA104;
  union                                            /* Offset=0x01B0 : RCI_TXRX_DATA105 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA105;
  union                                            /* Offset=0x01B4 : RCI_TXRX_DATA106 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA106;
  union                                            /* Offset=0x01B8 : RCI_TXRX_DATA107 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA107;
  union                                            /* Offset=0x01BC : RCI_TXRX_DATA108 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA108;
  union                                            /* Offset=0x01C0 : RCI_TXRX_DATA109 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA109;
  union                                            /* Offset=0x01C4 : RCI_TXRX_DATA110 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA110;
  union                                            /* Offset=0x01C8 : RCI_TXRX_DATA111 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA111;
  union                                            /* Offset=0x01CC : RCI_TXRX_DATA112 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA112;
  union                                            /* Offset=0x01D0 : RCI_TXRX_DATA113 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA113;
  union                                            /* Offset=0x01D4 : RCI_TXRX_DATA114 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA114;
  union                                            /* Offset=0x01D8 : RCI_TXRX_DATA115 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA115;
  union                                            /* Offset=0x01DC : RCI_TXRX_DATA116 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA116;
  union                                            /* Offset=0x01E0 : RCI_TXRX_DATA117 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA117;
  union                                            /* Offset=0x01E4 : RCI_TXRX_DATA118 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA118;
  union                                            /* Offset=0x01E8 : RCI_TXRX_DATA119 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA119;
  union                                            /* Offset=0x01EC : RCI_TXRX_DATA120 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA120;
  union                                            /* Offset=0x01F0 : RCI_TXRX_DATA121 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA121;
  union                                            /* Offset=0x01F4 : RCI_TXRX_DATA122 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA122;
  union                                            /* Offset=0x01F8 : RCI_TXRX_DATA123 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA123;
  union                                            /* Offset=0x01FC : RCI_TXRX_DATA124 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA124;
  union                                            /* Offset=0x0200 : RCI_TXRX_DATA125 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA125;
  union                                            /* Offset=0x0204 : RCI_TXRX_DATA126 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA126;
  union                                            /* Offset=0x0208 : RCI_TXRX_DATA127 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA127;
  union                                            /* Offset=0x020C : RCI_TXRX_DATA128 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA128;
  union                                            /* Offset=0x0210 : RCI_TXRX_DATA129 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA129;
  union                                            /* Offset=0x0214 : RCI_TXRX_DATA130 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA130;
  union                                            /* Offset=0x0218 : RCI_TXRX_DATA131 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA131;
  union                                            /* Offset=0x021C : RCI_TXRX_DATA132 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA132;
  union                                            /* Offset=0x0220 : RCI_TXRX_DATA133 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA133;
  union                                            /* Offset=0x0224 : RCI_TXRX_DATA134 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA134;
  union                                            /* Offset=0x0228 : RCI_TXRX_DATA135 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA135;
  union                                            /* Offset=0x022C : RCI_TXRX_DATA136 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA136;
  union                                            /* Offset=0x0230 : RCI_TXRX_DATA137 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA137;
  union                                            /* Offset=0x0234 : RCI_TXRX_DATA138 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA138;
  union                                            /* Offset=0x0238 : RCI_TXRX_DATA139 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA139;
  union                                            /* Offset=0x023C : RCI_TXRX_DATA140 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA140;
  union                                            /* Offset=0x0240 : RCI_TXRX_DATA141 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA141;
  union                                            /* Offset=0x0244 : RCI_TXRX_DATA142 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA142;
  union                                            /* Offset=0x0248 : RCI_TXRX_DATA143 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA143;
  union                                            /* Offset=0x024C : RCI_TXRX_DATA144 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA144;
  union                                            /* Offset=0x0250 : RCI_TXRX_DATA145 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA145;
  union                                            /* Offset=0x0254 : RCI_TXRX_DATA146 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA146;
  union                                            /* Offset=0x0258 : RCI_TXRX_DATA147 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA147;
  union                                            /* Offset=0x025C : RCI_TXRX_DATA148 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA148;
  union                                            /* Offset=0x0260 : RCI_TXRX_DATA149 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA149;
  union                                            /* Offset=0x0264 : RCI_TXRX_DATA150 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA150;
  union                                            /* Offset=0x0268 : RCI_TXRX_DATA151 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA151;
  union                                            /* Offset=0x026C : RCI_TXRX_DATA152 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA152;
  union                                            /* Offset=0x0270 : RCI_TXRX_DATA153 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA153;
  union                                            /* Offset=0x0274 : RCI_TXRX_DATA154 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA154;
  union                                            /* Offset=0x0278 : RCI_TXRX_DATA155 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA155;
  union                                            /* Offset=0x027C : RCI_TXRX_DATA156 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA156;
  union                                            /* Offset=0x0280 : RCI_TXRX_DATA157 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA157;
  union                                            /* Offset=0x0284 : RCI_TXRX_DATA158 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA158;
  union                                            /* Offset=0x0288 : RCI_TXRX_DATA159 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA159;
  union                                            /* Offset=0x028C : RCI_TXRX_DATA160 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA160;
  union                                            /* Offset=0x0290 : RCI_TXRX_DATA161 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA161;
  union                                            /* Offset=0x0294 : RCI_TXRX_DATA162 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA162;
  union                                            /* Offset=0x0298 : RCI_TXRX_DATA163 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA163;
  union                                            /* Offset=0x029C : RCI_TXRX_DATA164 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA164;
  union                                            /* Offset=0x02A0 : RCI_TXRX_DATA165 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA165;
  union                                            /* Offset=0x02A4 : RCI_TXRX_DATA166 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA166;
  union                                            /* Offset=0x02A8 : RCI_TXRX_DATA167 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA167;
  union                                            /* Offset=0x02AC : RCI_TXRX_DATA168 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA168;
  union                                            /* Offset=0x02B0 : RCI_TXRX_DATA169 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA169;
  union                                            /* Offset=0x02B4 : RCI_TXRX_DATA170 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA170;
  union                                            /* Offset=0x02B8 : RCI_TXRX_DATA171 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA171;
  union                                            /* Offset=0x02BC : RCI_TXRX_DATA172 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA172;
  union                                            /* Offset=0x02C0 : RCI_TXRX_DATA173 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA173;
  union                                            /* Offset=0x02C4 : RCI_TXRX_DATA174 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA174;
  union                                            /* Offset=0x02C8 : RCI_TXRX_DATA175 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA175;
  union                                            /* Offset=0x02CC : RCI_TXRX_DATA176 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA176;
  union                                            /* Offset=0x02D0 : RCI_TXRX_DATA177 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA177;
  union                                            /* Offset=0x02D4 : RCI_TXRX_DATA178 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA178;
  union                                            /* Offset=0x02D8 : RCI_TXRX_DATA179 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA179;
  union                                            /* Offset=0x02DC : RCI_TXRX_DATA180 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA180;
  union                                            /* Offset=0x02E0 : RCI_TXRX_DATA181 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA181;
  union                                            /* Offset=0x02E4 : RCI_TXRX_DATA182 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA182;
  union                                            /* Offset=0x02E8 : RCI_TXRX_DATA183 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA183;
  union                                            /* Offset=0x02EC : RCI_TXRX_DATA184 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA184;
  union                                            /* Offset=0x02F0 : RCI_TXRX_DATA185 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA185;
  union                                            /* Offset=0x02F4 : RCI_TXRX_DATA186 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA186;
  union                                            /* Offset=0x02F8 : RCI_TXRX_DATA187 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA187;
  union                                            /* Offset=0x02FC : RCI_TXRX_DATA188 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA188;
  union                                            /* Offset=0x0300 : RCI_TXRX_DATA189 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA189;
  union                                            /* Offset=0x0304 : RCI_TXRX_DATA190 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA190;
  union                                            /* Offset=0x0308 : RCI_TXRX_DATA191 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA191;
  union                                            /* Offset=0x030C : RCI_TXRX_DATA192 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA192;
  union                                            /* Offset=0x0310 : RCI_TXRX_DATA193 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA193;
  union                                            /* Offset=0x0314 : RCI_TXRX_DATA194 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA194;
  union                                            /* Offset=0x0318 : RCI_TXRX_DATA195 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA195;
  union                                            /* Offset=0x031C : RCI_TXRX_DATA196 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA196;
  union                                            /* Offset=0x0320 : RCI_TXRX_DATA197 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA197;
  union                                            /* Offset=0x0324 : RCI_TXRX_DATA198 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA198;
  union                                            /* Offset=0x0328 : RCI_TXRX_DATA199 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA199;
  union                                            /* Offset=0x032C : RCI_TXRX_DATA200 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA200;
  union                                            /* Offset=0x0330 : RCI_TXRX_DATA201 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA201;
  union                                            /* Offset=0x0334 : RCI_TXRX_DATA202 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA202;
  union                                            /* Offset=0x0338 : RCI_TXRX_DATA203 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA203;
  union                                            /* Offset=0x033C : RCI_TXRX_DATA204 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA204;
  union                                            /* Offset=0x0340 : RCI_TXRX_DATA205 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA205;
  union                                            /* Offset=0x0344 : RCI_TXRX_DATA206 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA206;
  union                                            /* Offset=0x0348 : RCI_TXRX_DATA207 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA207;
  union                                            /* Offset=0x034C : RCI_TXRX_DATA208 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA208;
  union                                            /* Offset=0x0350 : RCI_TXRX_DATA209 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA209;
  union                                            /* Offset=0x0354 : RCI_TXRX_DATA210 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA210;
  union                                            /* Offset=0x0358 : RCI_TXRX_DATA211 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA211;
  union                                            /* Offset=0x035C : RCI_TXRX_DATA212 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA212;
  union                                            /* Offset=0x0360 : RCI_TXRX_DATA213 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA213;
  union                                            /* Offset=0x0364 : RCI_TXRX_DATA214 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA214;
  union                                            /* Offset=0x0368 : RCI_TXRX_DATA215 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA215;
  union                                            /* Offset=0x036C : RCI_TXRX_DATA216 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA216;
  union                                            /* Offset=0x0370 : RCI_TXRX_DATA217 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA217;
  union                                            /* Offset=0x0374 : RCI_TXRX_DATA218 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA218;
  union                                            /* Offset=0x0378 : RCI_TXRX_DATA219 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA219;
  union                                            /* Offset=0x037C : RCI_TXRX_DATA220 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA220;
  union                                            /* Offset=0x0380 : RCI_TXRX_DATA221 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA221;
  union                                            /* Offset=0x0384 : RCI_TXRX_DATA222 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA222;
  union                                            /* Offset=0x0388 : RCI_TXRX_DATA223 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA223;
  union                                            /* Offset=0x038C : RCI_TXRX_DATA224 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA224;
  union                                            /* Offset=0x0390 : RCI_TXRX_DATA225 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA225;
  union                                            /* Offset=0x0394 : RCI_TXRX_DATA226 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA226;
  union                                            /* Offset=0x0398 : RCI_TXRX_DATA227 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA227;
  union                                            /* Offset=0x039C : RCI_TXRX_DATA228 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA228;
  union                                            /* Offset=0x03A0 : RCI_TXRX_DATA229 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA229;
  union                                            /* Offset=0x03A4 : RCI_TXRX_DATA230 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA230;
  union                                            /* Offset=0x03A8 : RCI_TXRX_DATA231 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA231;
  union                                            /* Offset=0x03AC : RCI_TXRX_DATA232 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA232;
  union                                            /* Offset=0x03B0 : RCI_TXRX_DATA233 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA233;
  union                                            /* Offset=0x03B4 : RCI_TXRX_DATA234 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA234;
  union                                            /* Offset=0x03B8 : RCI_TXRX_DATA235 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA235;
  union                                            /* Offset=0x03BC : RCI_TXRX_DATA236 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA236;
  union                                            /* Offset=0x03C0 : RCI_TXRX_DATA237 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA237;
  union                                            /* Offset=0x03C4 : RCI_TXRX_DATA238 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA238;
  union                                            /* Offset=0x03C8 : RCI_TXRX_DATA239 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA239;
  union                                            /* Offset=0x03CC : RCI_TXRX_DATA240 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA240;
  union                                            /* Offset=0x03D0 : RCI_TXRX_DATA241 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA241;
  union                                            /* Offset=0x03D4 : RCI_TXRX_DATA242 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA242;
  union                                            /* Offset=0x03D8 : RCI_TXRX_DATA243 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA243;
  union                                            /* Offset=0x03DC : RCI_TXRX_DATA244 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA244;
  union                                            /* Offset=0x03E0 : RCI_TXRX_DATA245 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA245;
  union                                            /* Offset=0x03E4 : RCI_TXRX_DATA246 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA246;
  union                                            /* Offset=0x03E8 : RCI_TXRX_DATA247 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA247;
  union                                            /* Offset=0x03EC : RCI_TXRX_DATA248 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA248;
  union                                            /* Offset=0x03F0 : RCI_TXRX_DATA249 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA249;
  union                                            /* Offset=0x03F4 : RCI_TXRX_DATA250 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA250;
  union                                            /* Offset=0x03F8 : RCI_TXRX_DATA251 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA251;
  union                                            /* Offset=0x03FC : RCI_TXRX_DATA252 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA252;
  union                                            /* Offset=0x0400 : RCI_TXRX_DATA253 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA253;
  union                                            /* Offset=0x0404 : RCI_TXRX_DATA254 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA254;
  union                                            /* Offset=0x0408 : RCI_TXRX_DATA255 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA255;
  union                                            /* Offset=0x040C : RCI_TXRX_DATA256 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA256;
  union                                            /* Offset=0x0410 : RCI_TXRX_DATA257 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA257;
  union                                            /* Offset=0x0414 : RCI_TXRX_DATA258 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA258;
  union                                            /* Offset=0x0418 : RCI_TXRX_DATA259 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA259;
  union                                            /* Offset=0x041C : RCI_TXRX_DATA260 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA260;
  union                                            /* Offset=0x0420 : RCI_TXRX_DATA261 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA261;
  union                                            /* Offset=0x0424 : RCI_TXRX_DATA262 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA262;
  union                                            /* Offset=0x0428 : RCI_TXRX_DATA263 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA263;
  union                                            /* Offset=0x042C : RCI_TXRX_DATA264 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA264;
  union                                            /* Offset=0x0430 : RCI_TXRX_DATA265 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA265;
  union                                            /* Offset=0x0434 : RCI_TXRX_DATA266 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA266;
  union                                            /* Offset=0x0438 : RCI_TXRX_DATA267 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA267;
  union                                            /* Offset=0x043C : RCI_TXRX_DATA268 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA268;
  union                                            /* Offset=0x0440 : RCI_TXRX_DATA269 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA269;
  union                                            /* Offset=0x0444 : RCI_TXRX_DATA270 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA270;
  union                                            /* Offset=0x0448 : RCI_TXRX_DATA271 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA271;
  union                                            /* Offset=0x044C : RCI_TXRX_DATA272 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA272;
  union                                            /* Offset=0x0450 : RCI_TXRX_DATA273 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA273;
  union                                            /* Offset=0x0454 : RCI_TXRX_DATA274 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA274;
  union                                            /* Offset=0x0458 : RCI_TXRX_DATA275 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA275;
  union                                            /* Offset=0x045C : RCI_TXRX_DATA276 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA276;
  union                                            /* Offset=0x0460 : RCI_TXRX_DATA277 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA277;
  union                                            /* Offset=0x0464 : RCI_TXRX_DATA278 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA278;
  union                                            /* Offset=0x0468 : RCI_TXRX_DATA279 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA279;
  union                                            /* Offset=0x046C : RCI_TXRX_DATA280 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA280;
  union                                            /* Offset=0x0470 : RCI_TXRX_DATA281 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA281;
  union                                            /* Offset=0x0474 : RCI_TXRX_DATA282 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA282;
  union                                            /* Offset=0x0478 : RCI_TXRX_DATA283 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA283;
  union                                            /* Offset=0x047C : RCI_TXRX_DATA284 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA284;
  union                                            /* Offset=0x0480 : RCI_TXRX_DATA285 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA285;
  union                                            /* Offset=0x0484 : RCI_TXRX_DATA286 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA286;
  union                                            /* Offset=0x0488 : RCI_TXRX_DATA287 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA287;
  union                                            /* Offset=0x048C : RCI_TXRX_DATA288 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA288;
  union                                            /* Offset=0x0490 : RCI_TXRX_DATA289 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA289;
  union                                            /* Offset=0x0494 : RCI_TXRX_DATA290 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA290;
  union                                            /* Offset=0x0498 : RCI_TXRX_DATA291 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA291;
  union                                            /* Offset=0x049C : RCI_TXRX_DATA292 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA292;
  union                                            /* Offset=0x04A0 : RCI_TXRX_DATA293 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA293;
  union                                            /* Offset=0x04A4 : RCI_TXRX_DATA294 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA294;
  union                                            /* Offset=0x04A8 : RCI_TXRX_DATA295 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA295;
  union                                            /* Offset=0x04AC : RCI_TXRX_DATA296 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA296;
  union                                            /* Offset=0x04B0 : RCI_TXRX_DATA297 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA297;
  union                                            /* Offset=0x04B4 : RCI_TXRX_DATA298 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA298;
  union                                            /* Offset=0x04B8 : RCI_TXRX_DATA299 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA299;
  union                                            /* Offset=0x04BC : RCI_TXRX_DATA300 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA300;
  union                                            /* Offset=0x04C0 : RCI_TXRX_DATA301 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA301;
  union                                            /* Offset=0x04C4 : RCI_TXRX_DATA302 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA302;
  union                                            /* Offset=0x04C8 : RCI_TXRX_DATA303 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA303;
  union                                            /* Offset=0x04CC : RCI_TXRX_DATA304 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA304;
  union                                            /* Offset=0x04D0 : RCI_TXRX_DATA305 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA305;
  union                                            /* Offset=0x04D4 : RCI_TXRX_DATA306 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA306;
  union                                            /* Offset=0x04D8 : RCI_TXRX_DATA307 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA307;
  union                                            /* Offset=0x04DC : RCI_TXRX_DATA308 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA308;
  union                                            /* Offset=0x04E0 : RCI_TXRX_DATA309 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA309;
  union                                            /* Offset=0x04E4 : RCI_TXRX_DATA310 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA310;
  union                                            /* Offset=0x04E8 : RCI_TXRX_DATA311 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA311;
  union                                            /* Offset=0x04EC : RCI_TXRX_DATA312 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA312;
  union                                            /* Offset=0x04F0 : RCI_TXRX_DATA313 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA313;
  union                                            /* Offset=0x04F4 : RCI_TXRX_DATA314 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA314;
  union                                            /* Offset=0x04F8 : RCI_TXRX_DATA315 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA315;
  union                                            /* Offset=0x04FC : RCI_TXRX_DATA316 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA316;
  union                                            /* Offset=0x0500 : RCI_TXRX_DATA317 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA317;
  union                                            /* Offset=0x0504 : RCI_TXRX_DATA318 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA318;
  union                                            /* Offset=0x0508 : RCI_TXRX_DATA319 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA319;
  union                                            /* Offset=0x050C : RCI_TXRX_DATA320 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA320;
  union                                            /* Offset=0x0510 : RCI_TXRX_DATA321 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA321;
  union                                            /* Offset=0x0514 : RCI_TXRX_DATA322 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA322;
  union                                            /* Offset=0x0518 : RCI_TXRX_DATA323 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA323;
  union                                            /* Offset=0x051C : RCI_TXRX_DATA324 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA324;
  union                                            /* Offset=0x0520 : RCI_TXRX_DATA325 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA325;
  union                                            /* Offset=0x0524 : RCI_TXRX_DATA326 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA326;
  union                                            /* Offset=0x0528 : RCI_TXRX_DATA327 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA327;
  union                                            /* Offset=0x052C : RCI_TXRX_DATA328 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA328;
  union                                            /* Offset=0x0530 : RCI_TXRX_DATA329 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA329;
  union                                            /* Offset=0x0534 : RCI_TXRX_DATA330 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA330;
  union                                            /* Offset=0x0538 : RCI_TXRX_DATA331 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA331;
  union                                            /* Offset=0x053C : RCI_TXRX_DATA332 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA332;
  union                                            /* Offset=0x0540 : RCI_TXRX_DATA333 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA333;
  union                                            /* Offset=0x0544 : RCI_TXRX_DATA334 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA334;
  union                                            /* Offset=0x0548 : RCI_TXRX_DATA335 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA335;
  union                                            /* Offset=0x054C : RCI_TXRX_DATA336 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA336;
  union                                            /* Offset=0x0550 : RCI_TXRX_DATA337 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA337;
  union                                            /* Offset=0x0554 : RCI_TXRX_DATA338 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA338;
  union                                            /* Offset=0x0558 : RCI_TXRX_DATA339 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA339;
  union                                            /* Offset=0x055C : RCI_TXRX_DATA340 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA340;
  union                                            /* Offset=0x0560 : RCI_TXRX_DATA341 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA341;
  union                                            /* Offset=0x0564 : RCI_TXRX_DATA342 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA342;
  union                                            /* Offset=0x0568 : RCI_TXRX_DATA343 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA343;
  union                                            /* Offset=0x056C : RCI_TXRX_DATA344 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA344;
  union                                            /* Offset=0x0570 : RCI_TXRX_DATA345 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA345;
  union                                            /* Offset=0x0574 : RCI_TXRX_DATA346 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA346;
  union                                            /* Offset=0x0578 : RCI_TXRX_DATA347 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA347;
  union                                            /* Offset=0x057C : RCI_TXRX_DATA348 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA348;
  union                                            /* Offset=0x0580 : RCI_TXRX_DATA349 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA349;
  union                                            /* Offset=0x0584 : RCI_TXRX_DATA350 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA350;
  union                                            /* Offset=0x0588 : RCI_TXRX_DATA351 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA351;
  union                                            /* Offset=0x058C : RCI_TXRX_DATA352 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA352;
  union                                            /* Offset=0x0590 : RCI_TXRX_DATA353 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA353;
  union                                            /* Offset=0x0594 : RCI_TXRX_DATA354 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA354;
  union                                            /* Offset=0x0598 : RCI_TXRX_DATA355 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA355;
  union                                            /* Offset=0x059C : RCI_TXRX_DATA356 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA356;
  union                                            /* Offset=0x05A0 : RCI_TXRX_DATA357 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA357;
  union                                            /* Offset=0x05A4 : RCI_TXRX_DATA358 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA358;
  union                                            /* Offset=0x05A8 : RCI_TXRX_DATA359 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA359;
  union                                            /* Offset=0x05AC : RCI_TXRX_DATA360 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA360;
  union                                            /* Offset=0x05B0 : RCI_TXRX_DATA361 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA361;
  union                                            /* Offset=0x05B4 : RCI_TXRX_DATA362 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA362;
  union                                            /* Offset=0x05B8 : RCI_TXRX_DATA363 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA363;
  union                                            /* Offset=0x05BC : RCI_TXRX_DATA364 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA364;
  union                                            /* Offset=0x05C0 : RCI_TXRX_DATA365 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA365;
  union                                            /* Offset=0x05C4 : RCI_TXRX_DATA366 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA366;
  union                                            /* Offset=0x05C8 : RCI_TXRX_DATA367 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA367;
  union                                            /* Offset=0x05CC : RCI_TXRX_DATA368 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA368;
  union                                            /* Offset=0x05D0 : RCI_TXRX_DATA369 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA369;
  union                                            /* Offset=0x05D4 : RCI_TXRX_DATA370 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA370;
  union                                            /* Offset=0x05D8 : RCI_TXRX_DATA371 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA371;
  union                                            /* Offset=0x05DC : RCI_TXRX_DATA372 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA372;
  union                                            /* Offset=0x05E0 : RCI_TXRX_DATA373 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA373;
  union                                            /* Offset=0x05E4 : RCI_TXRX_DATA374 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA374;
  union                                            /* Offset=0x05E8 : RCI_TXRX_DATA375 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA375;
  union                                            /* Offset=0x05EC : RCI_TXRX_DATA376 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA376;
  union                                            /* Offset=0x05F0 : RCI_TXRX_DATA377 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA377;
  union                                            /* Offset=0x05F4 : RCI_TXRX_DATA378 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA378;
  union                                            /* Offset=0x05F8 : RCI_TXRX_DATA379 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA379;
  union                                            /* Offset=0x05FC : RCI_TXRX_DATA380 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA380;
  union                                            /* Offset=0x0600 : RCI_TXRX_DATA381 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA381;
  union                                            /* Offset=0x0604 : RCI_TXRX_DATA382 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA382;
  union                                            /* Offset=0x0608 : RCI_TXRX_DATA383 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA383;
  union                                            /* Offset=0x060C : RCI_TXRX_DATA384 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA384;
  union                                            /* Offset=0x0610 : RCI_TXRX_DATA385 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA385;
  union                                            /* Offset=0x0614 : RCI_TXRX_DATA386 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA386;
  union                                            /* Offset=0x0618 : RCI_TXRX_DATA387 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA387;
  union                                            /* Offset=0x061C : RCI_TXRX_DATA388 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA388;
  union                                            /* Offset=0x0620 : RCI_TXRX_DATA389 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA389;
  union                                            /* Offset=0x0624 : RCI_TXRX_DATA390 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA390;
  union                                            /* Offset=0x0628 : RCI_TXRX_DATA391 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA391;
  union                                            /* Offset=0x062C : RCI_TXRX_DATA392 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA392;
  union                                            /* Offset=0x0630 : RCI_TXRX_DATA393 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA393;
  union                                            /* Offset=0x0634 : RCI_TXRX_DATA394 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA394;
  union                                            /* Offset=0x0638 : RCI_TXRX_DATA395 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA395;
  union                                            /* Offset=0x063C : RCI_TXRX_DATA396 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA396;
  union                                            /* Offset=0x0640 : RCI_TXRX_DATA397 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA397;
  union                                            /* Offset=0x0644 : RCI_TXRX_DATA398 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA398;
  union                                            /* Offset=0x0648 : RCI_TXRX_DATA399 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA399;
  union                                            /* Offset=0x064C : RCI_TXRX_DATA400 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA400;
  union                                            /* Offset=0x0650 : RCI_TXRX_DATA401 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA401;
  union                                            /* Offset=0x0654 : RCI_TXRX_DATA402 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA402;
  union                                            /* Offset=0x0658 : RCI_TXRX_DATA403 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA403;
  union                                            /* Offset=0x065C : RCI_TXRX_DATA404 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA404;
  union                                            /* Offset=0x0660 : RCI_TXRX_DATA405 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA405;
  union                                            /* Offset=0x0664 : RCI_TXRX_DATA406 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA406;
  union                                            /* Offset=0x0668 : RCI_TXRX_DATA407 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA407;
  union                                            /* Offset=0x066C : RCI_TXRX_DATA408 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA408;
  union                                            /* Offset=0x0670 : RCI_TXRX_DATA409 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA409;
  union                                            /* Offset=0x0674 : RCI_TXRX_DATA410 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA410;
  union                                            /* Offset=0x0678 : RCI_TXRX_DATA411 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA411;
  union                                            /* Offset=0x067C : RCI_TXRX_DATA412 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA412;
  union                                            /* Offset=0x0680 : RCI_TXRX_DATA413 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA413;
  union                                            /* Offset=0x0684 : RCI_TXRX_DATA414 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA414;
  union                                            /* Offset=0x0688 : RCI_TXRX_DATA415 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA415;
  union                                            /* Offset=0x068C : RCI_TXRX_DATA416 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA416;
  union                                            /* Offset=0x0690 : RCI_TXRX_DATA417 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA417;
  union                                            /* Offset=0x0694 : RCI_TXRX_DATA418 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA418;
  union                                            /* Offset=0x0698 : RCI_TXRX_DATA419 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA419;
  union                                            /* Offset=0x069C : RCI_TXRX_DATA420 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA420;
  union                                            /* Offset=0x06A0 : RCI_TXRX_DATA421 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA421;
  union                                            /* Offset=0x06A4 : RCI_TXRX_DATA422 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA422;
  union                                            /* Offset=0x06A8 : RCI_TXRX_DATA423 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA423;
  union                                            /* Offset=0x06AC : RCI_TXRX_DATA424 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA424;
  union                                            /* Offset=0x06B0 : RCI_TXRX_DATA425 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA425;
  union                                            /* Offset=0x06B4 : RCI_TXRX_DATA426 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA426;
  union                                            /* Offset=0x06B8 : RCI_TXRX_DATA427 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA427;
  union                                            /* Offset=0x06BC : RCI_TXRX_DATA428 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA428;
  union                                            /* Offset=0x06C0 : RCI_TXRX_DATA429 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA429;
  union                                            /* Offset=0x06C4 : RCI_TXRX_DATA430 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA430;
  union                                            /* Offset=0x06C8 : RCI_TXRX_DATA431 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA431;
  union                                            /* Offset=0x06CC : RCI_TXRX_DATA432 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA432;
  union                                            /* Offset=0x06D0 : RCI_TXRX_DATA433 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA433;
  union                                            /* Offset=0x06D4 : RCI_TXRX_DATA434 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA434;
  union                                            /* Offset=0x06D8 : RCI_TXRX_DATA435 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA435;
  union                                            /* Offset=0x06DC : RCI_TXRX_DATA436 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA436;
  union                                            /* Offset=0x06E0 : RCI_TXRX_DATA437 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA437;
  union                                            /* Offset=0x06E4 : RCI_TXRX_DATA438 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA438;
  union                                            /* Offset=0x06E8 : RCI_TXRX_DATA439 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA439;
  union                                            /* Offset=0x06EC : RCI_TXRX_DATA440 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA440;
  union                                            /* Offset=0x06F0 : RCI_TXRX_DATA441 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA441;
  union                                            /* Offset=0x06F4 : RCI_TXRX_DATA442 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA442;
  union                                            /* Offset=0x06F8 : RCI_TXRX_DATA443 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA443;
  union                                            /* Offset=0x06FC : RCI_TXRX_DATA444 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA444;
  union                                            /* Offset=0x0700 : RCI_TXRX_DATA445 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA445;
  union                                            /* Offset=0x0704 : RCI_TXRX_DATA446 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA446;
  union                                            /* Offset=0x0708 : RCI_TXRX_DATA447 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA447;
  union                                            /* Offset=0x070C : RCI_TXRX_DATA448 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA448;
  union                                            /* Offset=0x0710 : RCI_TXRX_DATA449 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA449;
  union                                            /* Offset=0x0714 : RCI_TXRX_DATA450 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA450;
  union                                            /* Offset=0x0718 : RCI_TXRX_DATA451 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA451;
  union                                            /* Offset=0x071C : RCI_TXRX_DATA452 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA452;
  union                                            /* Offset=0x0720 : RCI_TXRX_DATA453 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA453;
  union                                            /* Offset=0x0724 : RCI_TXRX_DATA454 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA454;
  union                                            /* Offset=0x0728 : RCI_TXRX_DATA455 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA455;
  union                                            /* Offset=0x072C : RCI_TXRX_DATA456 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA456;
  union                                            /* Offset=0x0730 : RCI_TXRX_DATA457 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA457;
  union                                            /* Offset=0x0734 : RCI_TXRX_DATA458 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA458;
  union                                            /* Offset=0x0738 : RCI_TXRX_DATA459 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA459;
  union                                            /* Offset=0x073C : RCI_TXRX_DATA460 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA460;
  union                                            /* Offset=0x0740 : RCI_TXRX_DATA461 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA461;
  union                                            /* Offset=0x0744 : RCI_TXRX_DATA462 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA462;
  union                                            /* Offset=0x0748 : RCI_TXRX_DATA463 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA463;
  union                                            /* Offset=0x074C : RCI_TXRX_DATA464 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA464;
  union                                            /* Offset=0x0750 : RCI_TXRX_DATA465 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA465;
  union                                            /* Offset=0x0754 : RCI_TXRX_DATA466 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA466;
  union                                            /* Offset=0x0758 : RCI_TXRX_DATA467 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA467;
  union                                            /* Offset=0x075C : RCI_TXRX_DATA468 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA468;
  union                                            /* Offset=0x0760 : RCI_TXRX_DATA469 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA469;
  union                                            /* Offset=0x0764 : RCI_TXRX_DATA470 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA470;
  union                                            /* Offset=0x0768 : RCI_TXRX_DATA471 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA471;
  union                                            /* Offset=0x076C : RCI_TXRX_DATA472 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA472;
  union                                            /* Offset=0x0770 : RCI_TXRX_DATA473 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA473;
  union                                            /* Offset=0x0774 : RCI_TXRX_DATA474 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA474;
  union                                            /* Offset=0x0778 : RCI_TXRX_DATA475 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA475;
  union                                            /* Offset=0x077C : RCI_TXRX_DATA476 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA476;
  union                                            /* Offset=0x0780 : RCI_TXRX_DATA477 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA477;
  union                                            /* Offset=0x0784 : RCI_TXRX_DATA478 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA478;
  union                                            /* Offset=0x0788 : RCI_TXRX_DATA479 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA479;
  union                                            /* Offset=0x078C : RCI_TXRX_DATA480 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA480;
  union                                            /* Offset=0x0790 : RCI_TXRX_DATA481 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA481;
  union                                            /* Offset=0x0794 : RCI_TXRX_DATA482 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA482;
  union                                            /* Offset=0x0798 : RCI_TXRX_DATA483 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA483;
  union                                            /* Offset=0x079C : RCI_TXRX_DATA484 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA484;
  union                                            /* Offset=0x07A0 : RCI_TXRX_DATA485 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA485;
  union                                            /* Offset=0x07A4 : RCI_TXRX_DATA486 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA486;
  union                                            /* Offset=0x07A8 : RCI_TXRX_DATA487 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA487;
  union                                            /* Offset=0x07AC : RCI_TXRX_DATA488 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA488;
  union                                            /* Offset=0x07B0 : RCI_TXRX_DATA489 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA489;
  union                                            /* Offset=0x07B4 : RCI_TXRX_DATA490 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA490;
  union                                            /* Offset=0x07B8 : RCI_TXRX_DATA491 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA491;
  union                                            /* Offset=0x07BC : RCI_TXRX_DATA492 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA492;
  union                                            /* Offset=0x07C0 : RCI_TXRX_DATA493 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA493;
  union                                            /* Offset=0x07C4 : RCI_TXRX_DATA494 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA494;
  union                                            /* Offset=0x07C8 : RCI_TXRX_DATA495 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA495;
  union                                            /* Offset=0x07CC : RCI_TXRX_DATA496 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA496;
  union                                            /* Offset=0x07D0 : RCI_TXRX_DATA497 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA497;
  union                                            /* Offset=0x07D4 : RCI_TXRX_DATA498 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA498;
  union                                            /* Offset=0x07D8 : RCI_TXRX_DATA499 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA499;
  union                                            /* Offset=0x07DC : RCI_TXRX_DATA500 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA500;
  union                                            /* Offset=0x07E0 : RCI_TXRX_DATA501 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA501;
  union                                            /* Offset=0x07E4 : RCI_TXRX_DATA502 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA502;
  union                                            /* Offset=0x07E8 : RCI_TXRX_DATA503 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA503;
  union                                            /* Offset=0x07EC : RCI_TXRX_DATA504 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA504;
  union                                            /* Offset=0x07F0 : RCI_TXRX_DATA505 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA505;
  union                                            /* Offset=0x07F4 : RCI_TXRX_DATA506 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA506;
  union                                            /* Offset=0x07F8 : RCI_TXRX_DATA507 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA507;
  union                                            /* Offset=0x07FC : RCI_TXRX_DATA508 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BYTE1:8;                                    /* [7:0] */
      __IO unsigned long   BYTE2:8;                                    /* [15:8] */
      __IO unsigned long   BYTE3:8;                                    /* [23:16] */
      __IO unsigned long   BYTE4:8;                                    /* [31:24] */
    } BIT;
  } RCI_TXRX_DATA508;
  char                     wk_0800[0x7800];
  union                                            /* Offset=0x8000 : R_MACADL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MAL:32;                                     /* [31:0] */
    } BIT;
  } R_MACADL;
  union                                            /* Offset=0x8004 : R_MACADH */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MAH:16;                                     /* [15:0] */
      __IO unsigned long   :15;                                        /* [30:16] */
      __IO unsigned long   MLE:1;                                      /* [31] */
    } BIT;
  } R_MACADH;
  union                                            /* Offset=0x8008 : R_TST1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TS1:32;                                     /* [31:0] */
    } BIT;
  } R_TST1;
  union                                            /* Offset=0x800C : R_TST2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TS2:32;                                     /* [31:0] */
    } BIT;
  } R_TST2;
  union                                            /* Offset=0x8010 : R_PEN */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CRE:1;                                      /* [0] */
      __IO unsigned long   IRE:1;                                      /* [1] */
      __IO unsigned long   ARE:1;                                      /* [2] */
      __IO unsigned long   BRE:1;                                      /* [3] */
      __IO unsigned long   CTE:1;                                      /* [4] */
      __IO unsigned long   ITE:1;                                      /* [5] */
      __IO unsigned long   ATE:1;                                      /* [6] */
      __IO unsigned long   BTE:1;                                      /* [7] */
      __IO unsigned long   CUP:1;                                      /* [8] */
      __IO unsigned long   :9;                                         /* [17:9] */
      __IO unsigned long   NOM:3;                                      /* [20:18] */
      __IO unsigned long   HPI:4;                                      /* [24:21] */
      __IO unsigned long   HPC:4;                                      /* [28:25] */
      __IO unsigned long   RBM:3;                                      /* [31:29] */
    } BIT;
  } R_PEN;
  union                                            /* Offset=0x8014 : R_PNT_AGT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AT:16;                                      /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } R_PNT_AGT;
  union                                            /* Offset=0x8018 : R_DD_AGT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AT:18;                                      /* [17:0] */
      __IO unsigned long   :9;                                         /* [26:18] */
      __I  unsigned long   LEN:4;                                      /* [30:27] */
      __IO unsigned long   DIS:1;                                      /* [31] */
    } BIT;
  } R_DD_AGT;
  union                                            /* Offset=0x801C : R_MACFLT_I1L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_I1L;
  union                                            /* Offset=0x8020 : R_MACFLT_I1H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_I1H;
  union                                            /* Offset=0x8024 : R_MACFLT_I2L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_I2L;
  union                                            /* Offset=0x8028 : R_MACFLT_I2H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_I2H;
  union                                            /* Offset=0x802C : R_MACFLT_I3L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_I3L;
  union                                            /* Offset=0x8030 : R_MACFLT_I3H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_I3H;
  union                                            /* Offset=0x8034 : R_MACFLT_I4L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_I4L;
  union                                            /* Offset=0x8038 : R_MACFLT_I4H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_I4H;
  union                                            /* Offset=0x803C : R_MACFLT_I5L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_I5L;
  union                                            /* Offset=0x8040 : R_MACFLT_I5H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_I5H;
  union                                            /* Offset=0x8044 : R_MACFLT_I6L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_I6L;
  union                                            /* Offset=0x8048 : R_MACFLT_I6H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_I6H;
  union                                            /* Offset=0x804C : R_MACFLT_I7L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_I7L;
  union                                            /* Offset=0x8050 : R_MACFLT_I7H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_I7H;
  union                                            /* Offset=0x8054 : R_MACFLT_I8L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_I8L;
  union                                            /* Offset=0x8058 : R_MACFLT_I8H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_I8H;
  union                                            /* Offset=0x805C : R_MACFLT_C1L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_C1L;
  union                                            /* Offset=0x8060 : R_MACFLT_C1H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_C1H;
  union                                            /* Offset=0x8064 : R_MACFLT_C2L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_C2L;
  union                                            /* Offset=0x8068 : R_MACFLT_C2H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_C2H;
  union                                            /* Offset=0x806C : R_MACFLT_C3L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_C3L;
  union                                            /* Offset=0x8070 : R_MACFLT_C3H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_C3H;
  union                                            /* Offset=0x8074 : R_MACFLT_C4L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_C4L;
  union                                            /* Offset=0x8078 : R_MACFLT_C4H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_C4H;
  union                                            /* Offset=0x807C : R_MACFLT_C5L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_C5L;
  union                                            /* Offset=0x8080 : R_MACFLT_C5H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_C5H;
  union                                            /* Offset=0x8084 : R_MACFLT_C6L */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FML:32;                                     /* [31:0] */
    } BIT;
  } R_MACFLT_C6L;
  union                                            /* Offset=0x8088 : R_MACFLT_C6H */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FMH:16;                                     /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   FBM:12;                                     /* [31:20] */
    } BIT;
  } R_MACFLT_C6H;
  union                                            /* Offset=0x808C : R_VER */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CVS:8;                                      /* [7:0] */
      __I  unsigned long   CVM:8;                                      /* [15:8] */
      __I  unsigned long   :14;                                        /* [29:16] */
      __I  unsigned long   NT:2;                                       /* [31:30] */
    } BIT;
  } R_VER;
  union                                            /* Offset=0x8090 : R_RAM_STA */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   FH:16;                                      /* [15:0] */
      __I  unsigned long   FP:16;                                      /* [31:16] */
    } BIT;
  } R_RAM_STA;
  union                                            /* Offset=0x8094 : R_UFMC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   UF:32;                                      /* [31:0] */
    } BIT;
  } R_UFMC;
  union                                            /* Offset=0x8098 : R_FRA_ALL_ARX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ALL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_ALL_ARX;
  union                                            /* Offset=0x809C : R_FRA_TAG_ARX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TAG:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_TAG_ARX;
  union                                            /* Offset=0x80A0 : R_FRA_NLL_ARX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   NLL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_NLL_ARX;
  union                                            /* Offset=0x80A4 : R_FRA_ERR_ARX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ERR:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_ERR_ARX;
  union                                            /* Offset=0x80A8 : R_FRA_WRO_ARX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   WRO:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_WRO_ARX;
  union                                            /* Offset=0x80AC : R_FRA_ALL_ATX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ALL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_ALL_ATX;
  union                                            /* Offset=0x80B0 : R_FRA_TAG_ATX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TAG:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_TAG_ATX;
  union                                            /* Offset=0x80B4 : R_FRA_NLL_ATX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   NLL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_NLL_ATX;
  union                                            /* Offset=0x80B8 : R_FRA_ALL_BRX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ALL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_ALL_BRX;
  union                                            /* Offset=0x80BC : R_FRA_TAG_BRX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TAG:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_TAG_BRX;
  union                                            /* Offset=0x80C0 : R_FRA_NLL_BRX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   NLL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_NLL_BRX;
  union                                            /* Offset=0x80C4 : R_FRA_ERR_BRX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ERR:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_ERR_BRX;
  union                                            /* Offset=0x80C8 : R_FRA_WRO_BRX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   WRO:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_WRO_BRX;
  union                                            /* Offset=0x80CC : R_FRA_ALL_BTX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ALL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_ALL_BTX;
  union                                            /* Offset=0x80D0 : R_FRA_TAG_BTX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TAG:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_TAG_BTX;
  union                                            /* Offset=0x80D4 : R_FRA_NLL_BTX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   NLL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_NLL_BTX;
  union                                            /* Offset=0x80D8 : R_FRA_ALL_CRX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ALL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_ALL_CRX;
  union                                            /* Offset=0x80DC : R_FRA_TAG_CRX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TAG:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_TAG_CRX;
  union                                            /* Offset=0x80E0 : R_FRA_NLL_CRX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   NLL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_NLL_CRX;
  union                                            /* Offset=0x80E4 : R_FRA_ERR_CRX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ERR:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_ERR_CRX;
  union                                            /* Offset=0x80E8 : R_FRA_WRO_CRX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   WRO:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_WRO_CRX;
  union                                            /* Offset=0x80EC : R_FRA_ALL_CTX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ALL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_ALL_CTX;
  union                                            /* Offset=0x80F0 : R_FRA_TAG_CTX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TAG:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_TAG_CTX;
  union                                            /* Offset=0x80F4 : R_FRA_NLL_CTX */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   NLL:32;                                     /* [31:0] */
    } BIT;
  } R_FRA_NLL_CTX;
  union                                            /* Offset=0x80F8 : R_FREE_FRA_M */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   FF:32;                                      /* [31:0] */
    } BIT;
  } R_FREE_FRA_M;
  union                                            /* Offset=0x80FC : R_DBG_RPT1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   D32:1;                                      /* [0] */
      __IO unsigned long   D33:1;                                      /* [1] */
      __IO unsigned long   D34:1;                                      /* [2] */
      __IO unsigned long   D35:1;                                      /* [3] */
      __IO unsigned long   D36:1;                                      /* [4] */
      __IO unsigned long   D37:1;                                      /* [5] */
      __IO unsigned long   D38:1;                                      /* [6] */
      __IO unsigned long   D39:1;                                      /* [7] */
      __IO unsigned long   D40:1;                                      /* [8] */
      __IO unsigned long   D41:1;                                      /* [9] */
      __IO unsigned long   D42:1;                                      /* [10] */
      __IO unsigned long   D43:1;                                      /* [11] */
      __IO unsigned long   D44:1;                                      /* [12] */
      __IO unsigned long   RES:19;                                     /* [31:13] */
    } BIT;
  } R_DBG_RPT1;
  union                                            /* Offset=0x8100 : R_DBG_RPT2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   D0:1;                                       /* [0] */
      __IO unsigned long   D1:1;                                       /* [1] */
      __IO unsigned long   D2:1;                                       /* [2] */
      __IO unsigned long   D3:1;                                       /* [3] */
      __IO unsigned long   D4:1;                                       /* [4] */
      __IO unsigned long   D5:1;                                       /* [5] */
      __IO unsigned long   D6:1;                                       /* [6] */
      __IO unsigned long   D7:1;                                       /* [7] */
      __IO unsigned long   D8:1;                                       /* [8] */
      __IO unsigned long   D9:1;                                       /* [9] */
      __IO unsigned long   D10:1;                                      /* [10] */
      __IO unsigned long   D11:1;                                      /* [11] */
      __IO unsigned long   D12:1;                                      /* [12] */
      __IO unsigned long   D13:1;                                      /* [13] */
      __IO unsigned long   D14:1;                                      /* [14] */
      __IO unsigned long   D15:1;                                      /* [15] */
      __IO unsigned long   D16:1;                                      /* [16] */
      __IO unsigned long   D17:1;                                      /* [17] */
      __IO unsigned long   D18:1;                                      /* [18] */
      __IO unsigned long   D19:1;                                      /* [19] */
      __IO unsigned long   D20:1;                                      /* [20] */
      __IO unsigned long   D21:1;                                      /* [21] */
      __IO unsigned long   D22:1;                                      /* [22] */
      __IO unsigned long   D23:1;                                      /* [23] */
      __IO unsigned long   D24:1;                                      /* [24] */
      __IO unsigned long   D25:1;                                      /* [25] */
      __IO unsigned long   D26:1;                                      /* [26] */
      __IO unsigned long   D27:1;                                      /* [27] */
      __IO unsigned long   D28:1;                                      /* [28] */
      __IO unsigned long   D29:1;                                      /* [29] */
      __IO unsigned long   D30:1;                                      /* [30] */
      __IO unsigned long   D31:1;                                      /* [31] */
    } BIT;
  } R_DBG_RPT2;
  union                                            /* Offset=0x8104 : R_PNT_S */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PNTP:16;                                    /* [15:0] */
      __I  unsigned long   PNTS:16;                                    /* [31:16] */
    } BIT;
  } R_PNT_S;
  union                                            /* Offset=0x8108 : R_PNT_D */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } R_PNT_D;
  char                     wk_810C[0x3EF4];
  union                                            /* Offset=0xC000 : RPTP_ID */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ID:16;                                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_ID;
  union                                            /* Offset=0xC004 : RPTP_TST */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TST:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_TST;
  union                                            /* Offset=0xC008 : RPTP_VER */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   FIV:4;                                      /* [3:0] */
      __I  unsigned long   FJV:4;                                      /* [7:4] */
      __I  unsigned long   IIV:4;                                      /* [11:8] */
      __I  unsigned long   IJV:4;                                      /* [15:12] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_VER;
  union                                            /* Offset=0xC00C : RPTP_GPO */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RPT:1;                                      /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   PDN:8;                                      /* [9:2] */
      __IO unsigned long   OSE:1;                                      /* [10] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } RPTP_GPO;
  char                     wk_C010[0x0004];
  union                                            /* Offset=0xC014 : RPTP_INT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CPU:1;                                      /* [0] */
      __I  unsigned long   I:1;                                        /* [1] */
      __I  unsigned long   A:1;                                        /* [2] */
      __I  unsigned long   B:1;                                        /* [3] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } RPTP_INT;
  union                                            /* Offset=0xC018 : RPTP_INT_MSK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CPU:1;                                      /* [0] */
      __IO unsigned long   I:1;                                        /* [1] */
      __IO unsigned long   A:1;                                        /* [2] */
      __IO unsigned long   B:1;                                        /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } RPTP_INT_MSK;
  char                     wk_C01C[0x0028];
  union                                            /* Offset=0xC044 : RPTP_TS_STAT_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :4;                                         /* [3:0] */
      __I  unsigned long   DE:4;                                       /* [7:4] */
      __I  unsigned long   TRP:5;                                      /* [12:8] */
      __IO unsigned long   :2;                                         /* [14:13] */
      __IO unsigned long   EN:1;                                       /* [15] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_TS_STAT_1;
  union                                            /* Offset=0xC048 : RPTP_TS_RD_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TS:16;                                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_TS_RD_1;
  union                                            /* Offset=0xC04C : RPTP_PORT_CONF_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :2;                                         /* [1:0] */
      __I  unsigned long   PDP:2;                                      /* [3:2] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } RPTP_PORT_CONF_1;
  union                                            /* Offset=0xC050 : RPTP_P_DELAY_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PED:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_P_DELAY_1;
  union                                            /* Offset=0xC054 : RPTP_PHY_DLY_TX_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PDT:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_PHY_DLY_TX_1;
  union                                            /* Offset=0xC058 : RPTP_PHY_DLY_RX_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PDR:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_PHY_DLY_RX_1;
  union                                            /* Offset=0xC05C : RPTP_TS_STAT_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :4;                                         /* [3:0] */
      __I  unsigned long   DE:4;                                       /* [7:4] */
      __I  unsigned long   TRP:5;                                      /* [12:8] */
      __IO unsigned long   :2;                                         /* [14:13] */
      __IO unsigned long   EN:1;                                       /* [15] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_TS_STAT_2;
  union                                            /* Offset=0xC060 : RPTP_TS_RD_2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TS:16;                                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_TS_RD_2;
  union                                            /* Offset=0xC064 : RPTP_PORT_CONF_2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :2;                                         /* [1:0] */
      __I  unsigned long   PDP:2;                                      /* [3:2] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } RPTP_PORT_CONF_2;
  union                                            /* Offset=0xC068 : RPTP_P_DELAY_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PED:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_P_DELAY_2;
  union                                            /* Offset=0xC06C : RPTP_PHY_DLY_TX_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PDT:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_PHY_DLY_TX_2;
  union                                            /* Offset=0xC070 : RPTP_PHY_DLY_RX_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PDR:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_PHY_DLY_RX_2;
  union                                            /* Offset=0xC074 : RPTP_TS_STAT_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :4;                                         /* [3:0] */
      __I  unsigned long   DE:4;                                       /* [7:4] */
      __I  unsigned long   TRP:5;                                      /* [12:8] */
      __IO unsigned long   :2;                                         /* [14:13] */
      __IO unsigned long   EN:1;                                       /* [15] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_TS_STAT_3;
  union                                            /* Offset=0xC078 : RPTP_TS_RD_3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TS:16;                                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_TS_RD_3;
  union                                            /* Offset=0xC07C : RPTP_PORT_CONF_3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :2;                                         /* [1:0] */
      __I  unsigned long   PDP:2;                                      /* [3:2] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } RPTP_PORT_CONF_3;
  union                                            /* Offset=0xC080 : RPTP_P_DELAY_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PED:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_P_DELAY_3;
  union                                            /* Offset=0xC084 : RPTP_PHY_DLY_TX_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PDT:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_PHY_DLY_TX_3;
  union                                            /* Offset=0xC088 : RPTP_PHY_DLY_RX_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PDR:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_PHY_DLY_RX_3;
  union                                            /* Offset=0xC08C : RPTP_TS_STAT_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :4;                                         /* [3:0] */
      __I  unsigned long   DE:4;                                       /* [7:4] */
      __I  unsigned long   TRP:5;                                      /* [12:8] */
      __IO unsigned long   :2;                                         /* [14:13] */
      __IO unsigned long   EN:1;                                       /* [15] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_TS_STAT_4;
  union                                            /* Offset=0xC090 : RPTP_TS_RD_4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TS:16;                                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_TS_RD_4;
  union                                            /* Offset=0xC094 : RPTP_PORT_CONF_4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :2;                                         /* [1:0] */
      __I  unsigned long   PDP:2;                                      /* [3:2] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } RPTP_PORT_CONF_4;
  union                                            /* Offset=0xC098 : RPTP_P_DELAY_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PED:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_P_DELAY_4;
  union                                            /* Offset=0xC09C : RPTP_PHY_DLY_TX_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PDT:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_PHY_DLY_TX_4;
  union                                            /* Offset=0xC0A0 : RPTP_PHY_DLY_RX_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PDR:16;                                     /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RPTP_PHY_DLY_RX_4;
  union                                            /* Offset=0xC0A4 : RPTP_BUF_STAT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CPU:1;                                      /* [0] */
      __I  unsigned long   I:1;                                        /* [1] */
      __I  unsigned long   A:1;                                        /* [2] */
      __I  unsigned long   B:1;                                        /* [3] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } RPTP_BUF_STAT;
} HSR_Type;
#endif  /* End of __HSR_SFR__DEFINE_HEADER__ */
