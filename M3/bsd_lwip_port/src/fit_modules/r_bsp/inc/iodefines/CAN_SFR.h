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
 **       for RZN1 CAN1
 **
 **       revision 0.52 (26.Oct.2017)
 **
 **********************************************************************************************************************/
#ifndef __CAN_SFR__DEFINE_HEADER__
#define __CAN_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : CAN
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : rCan_MOD */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_RM:1;                                  /* [0] */
      __IO unsigned long   bCan_LOM:1;                                 /* [1] */
      __IO unsigned long   bCan_STM:1;                                 /* [2] */
      __IO unsigned long   bCan_AFM:1;                                 /* [3] */
      __IO unsigned long   bCan_SM:1;                                  /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rCan_MOD;
  union                                            /* Offset=0x0004 : rCan_CMR */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_TR:1;                                  /* [0] */
      __O  unsigned long   bCan_AT:1;                                  /* [1] */
      __O  unsigned long   bCan_RRB:1;                                 /* [2] */
      __O  unsigned long   bCan_CDO:1;                                 /* [3] */
      __O  unsigned long   bCan_SRR:1;                                 /* [4] */
      __O  unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rCan_CMR;
  union                                            /* Offset=0x0008 : rCan_SR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RBS:1;                                 /* [0] */
      __I  unsigned long   bCan_DOS:1;                                 /* [1] */
      __I  unsigned long   bCan_TBS:1;                                 /* [2] */
      __I  unsigned long   bCan_TCS:1;                                 /* [3] */
      __I  unsigned long   bCan_RS:1;                                  /* [4] */
      __I  unsigned long   bCan_TS:1;                                  /* [5] */
      __I  unsigned long   bCan_ES:1;                                  /* [6] */
      __I  unsigned long   bCan_BS:1;                                  /* [7] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SR;
  union                                            /* Offset=0x000C : rCan_IR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RI:1;                                  /* [0] */
      __I  unsigned long   bCan_TI:1;                                  /* [1] */
      __I  unsigned long   bCan_EI:1;                                  /* [2] */
      __I  unsigned long   bCan_DOI:1;                                 /* [3] */
      __I  unsigned long   bCan_WUI:1;                                 /* [4] */
      __I  unsigned long   bCan_EPI:1;                                 /* [5] */
      __I  unsigned long   bCan_ALI:1;                                 /* [6] */
      __I  unsigned long   bCan_BEI:1;                                 /* [7] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_IR;
  union                                            /* Offset=0x0010 : rCan_IER */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_RIE:1;                                 /* [0] */
      __IO unsigned long   bCan_TIE:1;                                 /* [1] */
      __IO unsigned long   bCan_EIE:1;                                 /* [2] */
      __IO unsigned long   bCan_DOIE:1;                                /* [3] */
      __IO unsigned long   bCan_WUIE:1;                                /* [4] */
      __IO unsigned long   bCan_EPIE:1;                                /* [5] */
      __IO unsigned long   bCan_ALIE:1;                                /* [6] */
      __IO unsigned long   bCan_BEIE:1;                                /* [7] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_IER;
  char                     wk_0014[0x0004];
  union                                            /* Offset=0x0018 : rCan_BTR0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_BRP:6;                                 /* [5:0] */
      __IO unsigned long   bCan_SJW:2;                                 /* [7:6] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_BTR0;
  union                                            /* Offset=0x001C : rCan_BTR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_TSEG1:4;                               /* [3:0] */
      __IO unsigned long   bCan_TSEG2:3;                               /* [6:4] */
      __IO unsigned long   bCan_SAM:1;                                 /* [7] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_BTR1;
  union                                            /* Offset=0x0020 : rCan_OCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_OCMODE:2;                              /* [1:0] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rCan_OCR;
  char                     wk_0024[0x0008];
  union                                            /* Offset=0x002C : rCan_ALC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_ALC:5;                                 /* [4:0] */
      __I  unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rCan_ALC;
  union                                            /* Offset=0x0030 : rCan_ECC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_ECC_Segment:5;                         /* [4:0] */
      __I  unsigned long   bCan_ECC_Direction:1;                       /* [5] */
      __I  unsigned long   bCan_ECC_Code:2;                            /* [7:6] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ECC;
  union                                            /* Offset=0x0034 : rCan_EWLR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_EWLR:8;                                /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_EWLR;
  union                                            /* Offset=0x0038 : rCan_RXERR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_RXERR:8;                               /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RXERR;
  union                                            /* Offset=0x003C : rCan_TXERR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_TXERR:8;                               /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_TXERR;
  union    /* Offset=0x0040 : rCan_WrTxBuf0_RdRxBuf0_ACR0 (rCan_WrTransmitBuffer_0/rCan_RdReceiveBuffer_0/rCan_ACR0)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_0;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_0;
    union
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ACR:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ACR0;
  } rCan_WrTxBuf0_RdRxBuf0_ACR0;
  union    /* Offset=0x0044 : rCan_WrTxBuf1_RdRxBuf1_ACR1 (rCan_WrTransmitBuffer_1/rCan_RdReceiveBuffer_1/rCan_ACR1)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_1;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_1;
    union
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ACR:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ACR1;
  } rCan_WrTxBuf1_RdRxBuf1_ACR1;
  union    /* Offset=0x0048 : rCan_WrTxBuf2_RdRxBuf2_ACR2 (rCan_WrTransmitBuffer_2/rCan_RdReceiveBuffer_2/rCan_ACR2)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_2;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_2;
    union
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ACR:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ACR2;
  } rCan_WrTxBuf2_RdRxBuf2_ACR2;
  union    /* Offset=0x004C : rCan_WrTxBuf3_RdRxBuf3_ACR3 (rCan_WrTransmitBuffer_3/rCan_RdReceiveBuffer_3/rCan_ACR3)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_3;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_3;
    union
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ACR:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ACR3;
  } rCan_WrTxBuf3_RdRxBuf3_ACR3;
  union    /* Offset=0x0050 : rCan_WrTxBuf4_RdRxBuf4_AMR0 (rCan_WrTransmitBuffer_4/rCan_RdReceiveBuffer_4/rCan_AMR0)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_4;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_4;
    union
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_AMR:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_AMR0;
  } rCan_WrTxBuf4_RdRxBuf4_AMR0;
  union    /* Offset=0x0054 : rCan_WrTxBuf5_RdRxBuf5_AMR1 (rCan_WrTransmitBuffer_5/rCan_RdReceiveBuffer_5/rCan_AMR1)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_5;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_5;
    union
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_AMR:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_AMR1;
  } rCan_WrTxBuf5_RdRxBuf5_AMR1;
  union    /* Offset=0x0058 : rCan_WrTxBuf6_RdRxBuf6_AMR2 (rCan_WrTransmitBuffer_6/rCan_RdReceiveBuffer_6/rCan_AMR2)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_6;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_6;
    union
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_AMR:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_AMR2;
  } rCan_WrTxBuf6_RdRxBuf6_AMR2;
  union    /* Offset=0x005C : rCan_WrTxBuf7_RdRxBuf7_AMR3 (rCan_WrTransmitBuffer_7/rCan_RdReceiveBuffer_7/rCan_AMR3)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_7;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_7;
    union
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_AMR:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_AMR3;
  } rCan_WrTxBuf7_RdRxBuf7_AMR3;
  union    /* Offset=0x0060 : rCan_WrTxBuf8_RdRxBuf8 (rCan_WrTransmitBuffer_8/rCan_RdReceiveBuffer_8)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_8;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_8;
  } rCan_WrTxBuf8_RdRxBuf8;
  union    /* Offset=0x0064 : rCan_WrTxBuf9_RdRxBuf9 (rCan_WrTransmitBuffer_9/rCan_RdReceiveBuffer_9)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_9;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_9;
  } rCan_WrTxBuf9_RdRxBuf9;
  union    /* Offset=0x0068 : rCan_WrTxBuf10_RdRxBuf10 (rCan_WrTransmitBuffer_10/rCan_RdReceiveBuffer_10)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_10;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_10;
  } rCan_WrTxBuf10_RdRxBuf10;
  union    /* Offset=0x006C : rCan_WrTxBuf11_RdRxBuf11 (rCan_WrTransmitBuffer_11/rCan_RdReceiveBuffer_11)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_11;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_11;
  } rCan_WrTxBuf11_RdRxBuf11;
  union    /* Offset=0x0070 : rCan_WrTxBuf12_RdRxBuf12 (rCan_WrTransmitBuffer_12/rCan_RdReceiveBuffer_12)  */
  {
    union
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_WrTransmitBuffer:8;                    /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_WrTransmitBuffer_12;
    union
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdReceiveBuffer:8;                     /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdReceiveBuffer_12;
  } rCan_WrTxBuf12_RdRxBuf12;
  union                                            /* Offset=0x0074 : rCan_RMC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RMC:5;                                 /* [4:0] */
      __I  unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rCan_RMC;
  union                                            /* Offset=0x0078 : rCan_RBSA */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RBSA:6;                                /* [5:0] */
      __I  unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rCan_RBSA;
  char                     wk_007C[0x0004];
  union                                            /* Offset=0x0080 : rCan_ReceiveFifo_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_0;
  union                                            /* Offset=0x0084 : rCan_ReceiveFifo_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_1;
  union                                            /* Offset=0x0088 : rCan_ReceiveFifo_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_2;
  union                                            /* Offset=0x008C : rCan_ReceiveFifo_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_3;
  union                                            /* Offset=0x0090 : rCan_ReceiveFifo_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_4;
  union                                            /* Offset=0x0094 : rCan_ReceiveFifo_5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_5;
  union                                            /* Offset=0x0098 : rCan_ReceiveFifo_6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_6;
  union                                            /* Offset=0x009C : rCan_ReceiveFifo_7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_7;
  union                                            /* Offset=0x00A0 : rCan_ReceiveFifo_8 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_8;
  union                                            /* Offset=0x00A4 : rCan_ReceiveFifo_9 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_9;
  union                                            /* Offset=0x00A8 : rCan_ReceiveFifo_10 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_10;
  union                                            /* Offset=0x00AC : rCan_ReceiveFifo_11 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_11;
  union                                            /* Offset=0x00B0 : rCan_ReceiveFifo_12 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_12;
  union                                            /* Offset=0x00B4 : rCan_ReceiveFifo_13 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_13;
  union                                            /* Offset=0x00B8 : rCan_ReceiveFifo_14 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_14;
  union                                            /* Offset=0x00BC : rCan_ReceiveFifo_15 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_15;
  union                                            /* Offset=0x00C0 : rCan_ReceiveFifo_16 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_16;
  union                                            /* Offset=0x00C4 : rCan_ReceiveFifo_17 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_17;
  union                                            /* Offset=0x00C8 : rCan_ReceiveFifo_18 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_18;
  union                                            /* Offset=0x00CC : rCan_ReceiveFifo_19 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_19;
  union                                            /* Offset=0x00D0 : rCan_ReceiveFifo_20 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_20;
  union                                            /* Offset=0x00D4 : rCan_ReceiveFifo_21 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_21;
  union                                            /* Offset=0x00D8 : rCan_ReceiveFifo_22 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_22;
  union                                            /* Offset=0x00DC : rCan_ReceiveFifo_23 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_23;
  union                                            /* Offset=0x00E0 : rCan_ReceiveFifo_24 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_24;
  union                                            /* Offset=0x00E4 : rCan_ReceiveFifo_25 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_25;
  union                                            /* Offset=0x00E8 : rCan_ReceiveFifo_26 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_26;
  union                                            /* Offset=0x00EC : rCan_ReceiveFifo_27 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_27;
  union                                            /* Offset=0x00F0 : rCan_ReceiveFifo_28 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_28;
  union                                            /* Offset=0x00F4 : rCan_ReceiveFifo_29 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_29;
  union                                            /* Offset=0x00F8 : rCan_ReceiveFifo_30 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_30;
  union                                            /* Offset=0x00FC : rCan_ReceiveFifo_31 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_31;
  union                                            /* Offset=0x0100 : rCan_ReceiveFifo_32 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_32;
  union                                            /* Offset=0x0104 : rCan_ReceiveFifo_33 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_33;
  union                                            /* Offset=0x0108 : rCan_ReceiveFifo_34 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_34;
  union                                            /* Offset=0x010C : rCan_ReceiveFifo_35 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_35;
  union                                            /* Offset=0x0110 : rCan_ReceiveFifo_36 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_36;
  union                                            /* Offset=0x0114 : rCan_ReceiveFifo_37 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_37;
  union                                            /* Offset=0x0118 : rCan_ReceiveFifo_38 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_38;
  union                                            /* Offset=0x011C : rCan_ReceiveFifo_39 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_39;
  union                                            /* Offset=0x0120 : rCan_ReceiveFifo_40 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_40;
  union                                            /* Offset=0x0124 : rCan_ReceiveFifo_41 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_41;
  union                                            /* Offset=0x0128 : rCan_ReceiveFifo_42 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_42;
  union                                            /* Offset=0x012C : rCan_ReceiveFifo_43 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_43;
  union                                            /* Offset=0x0130 : rCan_ReceiveFifo_44 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_44;
  union                                            /* Offset=0x0134 : rCan_ReceiveFifo_45 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_45;
  union                                            /* Offset=0x0138 : rCan_ReceiveFifo_46 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_46;
  union                                            /* Offset=0x013C : rCan_ReceiveFifo_47 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_47;
  union                                            /* Offset=0x0140 : rCan_ReceiveFifo_48 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_48;
  union                                            /* Offset=0x0144 : rCan_ReceiveFifo_49 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_49;
  union                                            /* Offset=0x0148 : rCan_ReceiveFifo_50 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_50;
  union                                            /* Offset=0x014C : rCan_ReceiveFifo_51 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_51;
  union                                            /* Offset=0x0150 : rCan_ReceiveFifo_52 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_52;
  union                                            /* Offset=0x0154 : rCan_ReceiveFifo_53 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_53;
  union                                            /* Offset=0x0158 : rCan_ReceiveFifo_54 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_54;
  union                                            /* Offset=0x015C : rCan_ReceiveFifo_55 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_55;
  union                                            /* Offset=0x0160 : rCan_ReceiveFifo_56 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_56;
  union                                            /* Offset=0x0164 : rCan_ReceiveFifo_57 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_57;
  union                                            /* Offset=0x0168 : rCan_ReceiveFifo_58 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_58;
  union                                            /* Offset=0x016C : rCan_ReceiveFifo_59 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_59;
  union                                            /* Offset=0x0170 : rCan_ReceiveFifo_60 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_60;
  union                                            /* Offset=0x0174 : rCan_ReceiveFifo_61 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_61;
  union                                            /* Offset=0x0178 : rCan_ReceiveFifo_62 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_62;
  union                                            /* Offset=0x017C : rCan_ReceiveFifo_63 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_ReceiveFifo:8;                         /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_ReceiveFifo_63;
  union                                            /* Offset=0x0180 : rCan_RdTransmitBuffer_0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_0;
  union                                            /* Offset=0x0184 : rCan_RdTransmitBuffer_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_1;
  union                                            /* Offset=0x0188 : rCan_RdTransmitBuffer_2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_2;
  union                                            /* Offset=0x018C : rCan_RdTransmitBuffer_3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_3;
  union                                            /* Offset=0x0190 : rCan_RdTransmitBuffer_4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_4;
  union                                            /* Offset=0x0194 : rCan_RdTransmitBuffer_5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_5;
  union                                            /* Offset=0x0198 : rCan_RdTransmitBuffer_6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_6;
  union                                            /* Offset=0x019C : rCan_RdTransmitBuffer_7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_7;
  union                                            /* Offset=0x01A0 : rCan_RdTransmitBuffer_8 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_8;
  union                                            /* Offset=0x01A4 : rCan_RdTransmitBuffer_9 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_9;
  union                                            /* Offset=0x01A8 : rCan_RdTransmitBuffer_10 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_10;
  union                                            /* Offset=0x01AC : rCan_RdTransmitBuffer_11 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_11;
  union                                            /* Offset=0x01B0 : rCan_RdTransmitBuffer_12 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_RdTransmitBuffer:8;                    /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_RdTransmitBuffer_12;
  char                     wk_01B4[0x028C];
  union                                            /* Offset=0x00440 : rCan_SyncTransmitBuffer_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_0;
  union                                            /* Offset=0x0444 : rCan_SyncTransmitBuffer_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_1;
  union                                            /* Offset=0x0448 : rCan_SyncTransmitBuffer_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_2;
  union                                            /* Offset=0x044C : rCan_SyncTransmitBuffer_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_3;
  union                                            /* Offset=0x0450 : rCan_SyncTransmitBuffer_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_4;
  union                                            /* Offset=0x0454 : rCan_SyncTransmitBuffer_5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_5;
  union                                            /* Offset=0x0458 : rCan_SyncTransmitBuffer_6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_6;
  union                                            /* Offset=0x045C : rCan_SyncTransmitBuffer_7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_7;
  union                                            /* Offset=0x0460 : rCan_SyncTransmitBuffer_8 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_8;
  union                                            /* Offset=0x0464 : rCan_SyncTransmitBuffer_9 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_9;
  union                                            /* Offset=0x0468 : rCan_SyncTransmitBuffer_10 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_10;
  union                                            /* Offset=0x046C : rCan_SyncTransmitBuffer_11 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_11;
  union                                            /* Offset=0x0470 : rCan_SyncTransmitBuffer_12 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncTransmitBuffer:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rCan_SyncTransmitBuffer_12;
  char                     wk_0474[0x000C];
  union                                            /* Offset=0x0480 : rCan_SyncPeriod */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncPeriod:16;                         /* [15:0] */
      __IO unsigned long   :4;                                         /* [19:16] */
      __IO unsigned long   bCan_SyncMaskFrameTime:10;                  /* [29:20] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } rCan_SyncPeriod;
  char                     wk_0484[0x0004];
  union                                            /* Offset=0x0488 : rCan_SyncStatusInt */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_SendSyncFrameInt:1;                    /* [0] */
      __I  unsigned long   bCan_OverrunSyncFrameInt:1;                 /* [1] */
      __I  unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rCan_SyncStatusInt;
  union                                            /* Offset=0x048C : rCan_SyncMaskInt */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SendSyncFrameMaskInt:1;                /* [0] */
      __IO unsigned long   bCan_OverrunSyncFrameMaskInt:1;             /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rCan_SyncMaskInt;
  union                                            /* Offset=0x0490 : rCan_SyncClearInt */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_SendSyncFrameClearInt:1;               /* [0] */
      __O  unsigned long   bCan_OverrunSyncFrameClearInt:1;            /* [1] */
      __O  unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rCan_SyncClearInt;
  union                                            /* Offset=0x0494 : rCan_SyncStatus */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   bCan_SyncRunStop:1;                         /* [0] */
      __IO unsigned long   :2;                                         /* [2:1] */
      __I  unsigned long   bCan_SyncMaskFrame:1;                       /* [3] */
      __IO unsigned long   bCan_SyncMode:1;                            /* [4] */
      __IO unsigned long   bCan_TimerOnlyIfBusOff:1;                    /* [5] */
      __IO unsigned long   bCan_TimerOnlyMode:1;                        /* [6] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } rCan_SyncStatus;
  union                                            /* Offset=0x0498 : rCan_SyncClearSetRunStop */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bCan_SyncClearSetRunStop:32;                /* [31:0] */
    } BIT;
  } rCan_SyncClearSetRunStop;
  char                     wk_049C[0x0004];
  union                                            /* Offset=0x04A0 : rCan_SyncPassiveError */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bCan_SyncPassiveError:16;                   /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rCan_SyncPassiveError;
} CAN_Type;
#endif  /* End of __CAN_SFR__DEFINE_HEADER__ */
