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
 **       for RZN1 UART_f
 **
 **       revision 0.51
 **
 **********************************************************************************************************************/
#ifndef __UART_f_SFR__DEFINE_HEADER__
#define __UART_f_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : UART_f
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : rUart_RBR_THR/DLL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_RBR_THR:8;                                /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } RBR_THR;
    struct
    {
      __IO unsigned long   bUart_DLL:8;                                /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } DLL;
  } rUart_RBR_THR_DLL;
  union                                            /* Offset=0x0004 : rUart_IER/DLH */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_ERBFI:1;                              /* [0] */
      __IO unsigned long   bUart_ETBEI:1;                              /* [1] */
      __IO unsigned long   bUart_ELSI:1;                               /* [2] */
      __IO unsigned long   bUart_EDSSI:1;                              /* [3] */
      __IO unsigned long   :3;                                         /* [6:4] */
      __IO unsigned long   bUart_PTIME:1;                              /* [7] */
      __IO unsigned long   bUart_ETIMEOUT0:1;                          /* [8] */
      __IO unsigned long   bUart_ETIMEOUT1:1;                          /* [9] */
      __IO unsigned long   bUart_ETIMEOUT2:1;                          /* [10] */
      __IO unsigned long   bUart_ETIMEOUT3:1;                          /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } IER;
    struct
    {
      __IO unsigned long   bUart_DLH:8;                                /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } DLH;
  } rUart_IER_DLH;
  union                                            /* Offset=0x0008 : rUart_FCR_IIR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __O  unsigned long   bUart_FIFOE:1;                              /* [0] */
      __O  unsigned long   bUart_RFIFOR:1;                             /* [1] */
      __O  unsigned long   bUart_XFIFOR:1;                             /* [2] */
      __O  unsigned long   :1;                                         /* [3] */
      __O  unsigned long   bUart_TET:2;                                /* [5:4] */
      __O  unsigned long   bUart_RCVR:2;                               /* [7:6] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } FCR;
    struct
    {
      __I  unsigned long   bUart_IID:4;                                /* [3:0] */
      __I  unsigned long   :2;                                         /* [5:4] */
      __I  unsigned long   bUart_FIFOSE:2;                             /* [7:6] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } IIR;
  } rUart_FCR_IIR;
  union                                            /* Offset=0x000C : rUart_LCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_DLS:2;                                /* [1:0] */
      __IO unsigned long   bUart_STOP:1;                               /* [2] */
      __IO unsigned long   bUart_PEN:1;                                /* [3] */
      __IO unsigned long   bUart_EPS:1;                                /* [4] */
      __IO unsigned long   bUart_StickParity:1;                        /* [5] */
      __IO unsigned long   bUart_BC:1;                                 /* [6] */
      __IO unsigned long   bUart_DLAB:1;                               /* [7] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rUart_LCR;
  union                                            /* Offset=0x0010 : rUart_MCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_DTR:1;                                /* [0] */
      __IO unsigned long   bUart_RTS:1;                                /* [1] */
      __IO unsigned long   bUart_OUT1:1;                               /* [2] */
      __IO unsigned long   bUart_OUT2:1;                               /* [3] */
      __IO unsigned long   bUart_LB:1;                                 /* [4] */
      __IO unsigned long   bUart_AFCE:1;                               /* [5] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rUart_MCR;
  union                                            /* Offset=0x0014 : rUart_LSR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bUart_DR:1;                                 /* [0] */
      __I  unsigned long   bUart_OE:1;                                 /* [1] */
      __I  unsigned long   bUart_PE:1;                                 /* [2] */
      __I  unsigned long   bUart_FE:1;                                 /* [3] */
      __I  unsigned long   bUart_BI:1;                                 /* [4] */
      __I  unsigned long   bUart_THRE:1;                               /* [5] */
      __I  unsigned long   bUart_TEMT:1;                               /* [6] */
      __I  unsigned long   bUart_RFE:1;                                /* [7] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rUart_LSR;
  union                                            /* Offset=0x0018 : rUart_MSR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bUart_DCTS:1;                               /* [0] */
      __I  unsigned long   bUart_DDSR:1;                               /* [1] */
      __I  unsigned long   bUart_TERI:1;                               /* [2] */
      __I  unsigned long   bUart_DDCD:1;                               /* [3] */
      __I  unsigned long   bUart_CTS:1;                                /* [4] */
      __I  unsigned long   bUart_DSR:1;                                /* [5] */
      __I  unsigned long   bUart_RI:1;                                 /* [6] */
      __I  unsigned long   bUart_DCD:1;                                /* [7] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rUart_MSR;
  union                                            /* Offset=0x001C : rUart_SCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_SCR:8;                                /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rUart_SCR;
  char                     wk_0020[0x0010];
  union                                            /* Offset=0x0030 : rUart_SRBR_STHR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_SRBR_STHR:8;                          /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rUart_SRBR_STHR;
  char                     wk_0034[0x003C];
  union                                            /* Offset=0x0070 : rUart_FAR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_FAR:1;                                /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rUart_FAR;
  union                                            /* Offset=0x0074 : rUart_TFR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bUart_TFR:8;                                /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rUart_TFR;
  union                                            /* Offset=0x0078 : rUart_RFW */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bUart_RFWD:8;                               /* [7:0] */
      __O  unsigned long   bUart_RFPE:1;                               /* [8] */
      __O  unsigned long   bUart_RFFE:1;                               /* [9] */
      __O  unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } rUart_RFW;
  union                                            /* Offset=0x007C : rUart_USR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bUart_BUSY:1;                               /* [0] */
      __I  unsigned long   bUart_TFNF:1;                               /* [1] */
      __I  unsigned long   bUart_TFE:1;                                /* [2] */
      __I  unsigned long   bUart_RFNE:1;                               /* [3] */
      __I  unsigned long   bUart_RFF:1;                                /* [4] */
      __I  unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rUart_USR;
  union                                            /* Offset=0x0080 : rUart_TFL */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bUart_TFL:5;                                /* [4:0] */
      __I  unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rUart_TFL;
  union                                            /* Offset=0x0084 : rUart_RFL */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bUart_RFL:5;                                /* [4:0] */
      __I  unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rUart_RFL;
  union                                            /* Offset=0x0088 : rUart_SRR */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bUart_UR:1;                                 /* [0] */
      __O  unsigned long   bUart_RFR:1;                                /* [1] */
      __O  unsigned long   bUart_XFR:1;                                /* [2] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rUart_SRR;
  union                                            /* Offset=0x008C : rUart_SRTS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_SRTS:1;                               /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rUart_SRTS;
  union                                            /* Offset=0x0090 : rUart_SBCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_SBCR:1;                               /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rUart_SBCR;
  char                     wk_0094[0x0004];
  union                                            /* Offset=0x0098 : rUart_SFE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_SFE:1;                                /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rUart_SFE;
  union                                            /* Offset=0x009C : rUart_SRT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_SRCVR:2;                              /* [1:0] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rUart_SRT;
  union                                            /* Offset=0x00A0 : rUart_STET */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_STET:2;                               /* [1:0] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rUart_STET;
  union                                            /* Offset=0x00A4 : rUart_HTX */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_HTX:1;                                /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rUart_HTX;
  union                                            /* Offset=0x00A8 : rUart_DMASA */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bUart_DMASA:1;                              /* [0] */
      __O  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rUart_DMASA;
  char                     wk_00AC[0x0054];
  union                                            /* Offset=0x0100 : rUart_TO */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_TO0:8;                                /* [7:0] */
      __IO unsigned long   bUart_TO1:8;                                /* [15:8] */
      __IO unsigned long   bUart_TO2:8;                                /* [23:16] */
      __IO unsigned long   bUart_TO3:8;                                /* [31:24] */
    } BIT;
  } rUart_TO;
  union                                            /* Offset=0x0104 : rUart_CTRLTO */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_STARTTO0:1;                           /* [0] */
      __IO unsigned long   bUart_STARTTO1:1;                           /* [1] */
      __IO unsigned long   bUart_STARTTO2:1;                           /* [2] */
      __IO unsigned long   bUart_STARTTO3:1;                           /* [3] */
      __IO unsigned long   bUart_REARMTO0:1;                           /* [4] */
      __IO unsigned long   bUart_REARMTO1:1;                           /* [5] */
      __IO unsigned long   bUart_REARMTO2:1;                           /* [6] */
      __IO unsigned long   bUart_REARMTO3:1;                           /* [7] */
      __IO unsigned long   bUart_EnableDE:1;                           /* [8] */
      __IO unsigned long   bUart_EnableFilteringRXD:1;                 /* [9] */
      __IO unsigned long   :6;                                         /* [15:10] */
      __IO unsigned long   bUart_TG:8;                                 /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } rUart_CTRLTO;
  union                                            /* Offset=0x0108 : rUart_STATUSTO */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_TIMEOUTInt0:1;                        /* [0] */
      __IO unsigned long   bUart_TIMEOUTInt1:1;                        /* [1] */
      __IO unsigned long   bUart_TIMEOUTInt2:1;                        /* [2] */
      __IO unsigned long   bUart_TIMEOUTInt3:1;                        /* [3] */
      __I  unsigned long   bUart_TIMEOUTStatus0:1;                     /* [4] */
      __I  unsigned long   bUart_TIMEOUTStatus1:1;                     /* [5] */
      __I  unsigned long   bUart_TIMEOUTStatus2:1;                     /* [6] */
      __I  unsigned long   bUart_TIMEOUTStatus3:1;                     /* [7] */
      __I  unsigned long   bUart_DE:1;                                 /* [8] */
      __IO unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } rUart_STATUSTO;
  union                                            /* Offset=0x010C : rUart_TDMACR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_TDMAE:1;                              /* [0] */
      __IO unsigned long   bUart_DEST_BURST_SIZE:2;                    /* [2:1] */
      __IO unsigned long   bUart_DEST_BLOCK_SIZE:13;                   /* [15:3] */
      __I  unsigned long   bUart_CURRENT_DEST_BLOCK_SIZE:13;           /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } rUart_TDMACR;
  union                                            /* Offset=0x0110 : rUart_RDMACR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bUart_RDMAE:1;                              /* [0] */
      __IO unsigned long   bUart_SRC_BURST_SIZE:2;                     /* [2:1] */
      __IO unsigned long   bUart_SRC_BLOCK_SIZE:13;                    /* [15:3] */
      __I  unsigned long   bUart_CURRENT_SRC_BLOCK_SIZE:13;            /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } rUart_RDMACR;
} UART_f_Type;
#endif  /* End of __UART_f_SFR__DEFINE_HEADER__ */
