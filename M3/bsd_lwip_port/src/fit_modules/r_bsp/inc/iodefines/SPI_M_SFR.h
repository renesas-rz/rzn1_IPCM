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
 **       for RZN1 SPI1
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __SPI_M_SFR__DEFINE_HEADER__
#define __SPI_M_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : SPI_M
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : rSpi_CTRLR0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_DFS:4;                                 /* [3:0] */
      __IO unsigned long   bSpi_FRF:2;                                 /* [5:4] */
      __IO unsigned long   bSpi_SCPH:1;                                /* [6] */
      __IO unsigned long   bSpi_SCPOL:1;                               /* [7] */
      __IO unsigned long   bSpi_TMOD:2;                                /* [9:8] */
      __IO unsigned long   bSpi_SLV_OE:1;                              /* [10] */
      __IO unsigned long   bSpi_SRL:1;                                 /* [11] */
      __IO unsigned long   bSpi_CFS:4;                                 /* [15:12] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rSpi_CTRLR0;
  union                                            /* Offset=0x0004 : rSpi_CTRLR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_NDF:16;                                /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rSpi_CTRLR1;
  union                                            /* Offset=0x0008 : rSpi_SSIENR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_SSIENR:1;                              /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rSpi_SSIENR;
  union                                            /* Offset=0x000C : rSpi_MWCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_MWMOD:1;                               /* [0] */
      __IO unsigned long   bSpi_MDD:1;                                 /* [1] */
      __IO unsigned long   bSpi_MWHS:1;                                /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } rSpi_MWCR;
  union                                            /* Offset=0x0010 : rSpi_SER */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_HardwareSS:4;                          /* [3:0] */
      __IO unsigned long   bSpi_SoftwareSS:4;                          /* [7:4] */
      __IO unsigned long   bSpi_CtrlSS:4;                              /* [11:8] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } rSpi_SER;
  union                                            /* Offset=0x0014 : rSpi_BAUDR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_SCKDV:16;                              /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rSpi_BAUDR;
  union                                            /* Offset=0x0018 : rSpi_TXFTLR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_TFT:4;                                 /* [3:0] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rSpi_TXFTLR;
  union                                            /* Offset=0x001C : rSpi_RXFTLR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_RFT:4;                                 /* [3:0] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rSpi_RXFTLR;
  union                                            /* Offset=0x0020 : rSpi_TXFLR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSpi_TXTFL:4;                               /* [3:0] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rSpi_TXFLR;
  union                                            /* Offset=0x0024 : rSpi_RXFLR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSpi_RXTFL:4;                               /* [3:0] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rSpi_RXFLR;
  union                                            /* Offset=0x0028 : rSpi_SR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSpi_BUSY:1;                                /* [0] */
      __I  unsigned long   bSpi_TFNF:1;                                /* [1] */
      __I  unsigned long   bSpi_TFE:1;                                 /* [2] */
      __I  unsigned long   bSpi_RFNE:1;                                /* [3] */
      __I  unsigned long   bSpi_RFF:1;                                 /* [4] */
      __I  unsigned long   bSpi_TXE:1;                                 /* [5] */
      __I  unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rSpi_SR;
  union                                            /* Offset=0x002C : rSpi_IMR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_TXEIM:1;                               /* [0] */
      __IO unsigned long   bSpi_TXOIM:1;                               /* [1] */
      __IO unsigned long   bSpi_RXUIM:1;                               /* [2] */
      __IO unsigned long   bSpi_RXOIM:1;                               /* [3] */
      __IO unsigned long   bSpi_RXFIM:1;                               /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rSpi_IMR;
  union                                            /* Offset=0x0030 : rSpi_ISR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSpi_TXEIS:1;                               /* [0] */
      __I  unsigned long   bSpi_TXOIS:1;                               /* [1] */
      __I  unsigned long   bSpi_RXUIS:1;                               /* [2] */
      __I  unsigned long   bSpi_RXOIS:1;                               /* [3] */
      __I  unsigned long   bSpi_RXFIS:1;                               /* [4] */
      __I  unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rSpi_ISR;
  union                                            /* Offset=0x0034 : rSpi_RISR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSpi_TXEIR:1;                               /* [0] */
      __I  unsigned long   bSpi_TXOIR:1;                               /* [1] */
      __I  unsigned long   bSpi_RXUIR:1;                               /* [2] */
      __I  unsigned long   bSpi_RXOIR:1;                               /* [3] */
      __I  unsigned long   bSpi_RXFIR:1;                               /* [4] */
      __I  unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rSpi_RISR;
  union                                            /* Offset=0x0038 : rSpi_TXOICR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSpi_TXOICR:1;                              /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rSpi_TXOICR;
  union                                            /* Offset=0x003C : rSpi_RXOICR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSpi_RXOICR:1;                              /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rSpi_RXOICR;
  union                                            /* Offset=0x0040 : rSpi_RXUICR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSpi_RXUICR:1;                              /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rSpi_RXUICR;
  char                     wk_0044[0x0004];
  union                                            /* Offset=0x0048 : rSpi_ICR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bSpi_ICR:1;                                 /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rSpi_ICR;
  union                                            /* Offset=0x004C : rSpi_DMACR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_RDMAE:1;                               /* [0] */
      __IO unsigned long   bSpi_TDMAE:1;                               /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rSpi_DMACR;
  union                                            /* Offset=0x0050 : rSpi_DMATDLR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_DMATDLR:4;                             /* [3:0] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rSpi_DMATDLR;
  union                                            /* Offset=0x0054 : rSpi_DMARDLR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_DMARDLR:4;                             /* [3:0] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rSpi_DMARDLR;
  char                     wk_0058[0x0008];
  union                                            /* Offset=0x0060 : rSpi_DR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_DR:16;                                 /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rSpi_DR;
  char                     wk_0064[0x008C];
  union                                            /* Offset=0x00F0 : rSpi_RX_SAMPLE_DLY */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_RX_Sample_Delay:8;                     /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rSpi_RX_SAMPLE_DLY;
  char                     wk_00F4[0x000C];
  union                                            /* Offset=0x0100 : rSpi_TDMACR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_TDMAE1:1;                              /* [0] */
      __IO unsigned long   bSpi_DEST_BURST_SIZE:2;                     /* [2:1] */
      __IO unsigned long   bSpi_DEST_BLOCK_SIZE:13;                    /* [15:3] */
      __I  unsigned long   bSpi_CURRENT_DEST_BLOCK_SIZE:13;            /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } rSpi_TDMACR;
  union                                            /* Offset=0x0104 : rSpi_RDMACR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bSpi_RDMAE1:1;                              /* [0] */
      __IO unsigned long   bSpi_SRC_BURST_SIZE:2;                      /* [2:1] */
      __IO unsigned long   bSpi_SRC_BLOCK_SIZE:13;                     /* [15:3] */
      __I  unsigned long   bSpi_CURRENT_SRC_BLOCK_SIZE:13;             /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } rSpi_RDMACR;
} SPI_M_Type;
#endif  /* End of __SPI_M_SFR__DEFINE_HEADER__ */
