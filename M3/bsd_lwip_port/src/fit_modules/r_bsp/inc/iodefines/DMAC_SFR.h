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
 **       for RZN1 DMAC1
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __DMAC_SFR__DEFINE_HEADER__
#define __DMAC_SFR__DEFINE_HEADER__

#include "r_dma_rzn1_config.h"

/***********************************************************************************************************************
 ** Module : DMAC
 **********************************************************************************************************************/

typedef struct
{
    struct
    {
      union                                            /* Offset=0x0000 : SAR */
      {
        __IO unsigned long long  LONGLONG;
        struct
        {
          __IO unsigned long long  SAR:32;                                 /* [31:0] */
          __IO unsigned long long  :32;                                    /* [63:32] */
        } BIT;
      } SAR;
      union                                            /* Offset=0x0008 : DAR */
      {
        __IO unsigned long long  LONGLONG;
        struct
        {
          __IO unsigned long long  DAR:32;                                 /* [31:0] */
          __IO unsigned long long  :32;                                    /* [63:32] */
        } BIT;
      } DAR;
      union                                            /* Offset=0x0010 : LLP */
      {
        __IO unsigned long long  LONGLONG;
        struct
        {
          __IO unsigned long long  :2;                                     /* [1:0] */
          __IO unsigned long long  LOC:30;                                 /* [31:2] */
          __IO unsigned long long  :32;                                    /* [63:32] */
        } BIT;
      } LLP;
      union                                            /* Offset=0x0018 : CTL */
      {
        __IO unsigned long long  LONGLONG;
        struct
        {
          __IO unsigned long long  INT_EN:1;                               /* [0] */
          __IO unsigned long long  DST_TR_WIDTH:3;                         /* [3:1] */
          __IO unsigned long long  SRC_TR_WIDTH:3;                         /* [6:4] */
          __IO unsigned long long  DINC:2;                                 /* [8:7] */
          __IO unsigned long long  SINC:2;                                 /* [10:9] */
          __IO unsigned long long  DEST_MSIZE:3;                           /* [13:11] */
          __IO unsigned long long  SRC_MSIZE:3;                            /* [16:14] */
          __IO unsigned long long  SRC_GATHER_EN:1;                        /* [17] */
          __IO unsigned long long  DST_SCATTER_EN:1;                       /* [18] */
          __IO unsigned long long  :1;                                     /* [19] */
          __IO unsigned long long  TT_FC:3;                                /* [22:20] */
          __IO unsigned long long  :4;                                     /* [26:23] */
          __IO unsigned long long  LLP_DST_EN:1;                           /* [27] */
          __IO unsigned long long  LLP_SRC_EN:1;                           /* [28] */
          __IO unsigned long long  :3;                                     /* [31:29] */
          __IO unsigned long long  BLOCK_TS:12;                            /* [43:32] */
          __IO unsigned long long  DONE:1;                                 /* [44] */
          __IO unsigned long long  :19;                                    /* [63:45] */
        } BIT;
      } CTL;
      union                                            /* Offset=0x0020 : SSTAT */
      {
        __IO unsigned long long  LONGLONG;
        struct
        {
          __IO unsigned long long  SSTAT:32;                               /* [31:0] */
          __IO unsigned long long  :32;                                    /* [63:32] */
        } BIT;
      } SSTAT;
      union                                            /* Offset=0x0028 : DSTAT */
      {
        __IO unsigned long long  LONGLONG;
        struct
        {
          __IO unsigned long long  DSTAT:32;                               /* [31:0] */
          __IO unsigned long long  :32;                                    /* [63:32] */
        } BIT;
      } DSTAT;
      union                                            /* Offset=0x0030 : SSTATAR */
      {
        __IO unsigned long long  LONGLONG;
        struct
        {
          __IO unsigned long long  SSTATAR:32;                             /* [31:0] */
          __IO unsigned long long  :32;                                    /* [63:32] */
        } BIT;
      } SSTATAR;
      union                                            /* Offset=0x0038 : DSTATAR */
      {
        __IO unsigned long long  LONGLONG;
        struct
        {
          __IO unsigned long long  DSTATAR:32;                             /* [31:0] */
          __IO unsigned long long  :32;                                    /* [63:32] */
        } BIT;
      } DSTATAR;
      union                                            /* Offset=0x0040 : CFG */
      {
        __IO unsigned long long  LONGLONG;
        struct
        {
          __IO unsigned long long  :5;                                     /* [4:0] */
          __IO unsigned long long  CH_PRIOR:3;                             /* [7:5] */
          __IO unsigned long long  CH_SUSP:1;                              /* [8] */
          __IO unsigned long long  FIFO_EMPTY:1;                           /* [9] */
          __IO unsigned long long  HS_SEL_DST:1;                           /* [10] */
          __IO unsigned long long  HS_SEL_SRC:1;                           /* [11] */
          __IO unsigned long long  :6;                                     /* [17:12] */
          __IO unsigned long long  DST_HS_POL:1;                           /* [18] */
          __IO unsigned long long  SRC_HS_POL:1;                           /* [19] */
          __IO unsigned long long  MAX_ABRST:10;                           /* [29:20] */
          __IO unsigned long long  RELOAD_SRC:1;                           /* [30] */
          __IO unsigned long long  RELOAD_DST:1;                           /* [31] */
          __IO unsigned long long  FCMODE:1;                               /* [32] */
          __IO unsigned long long  FIFO_MODE:1;                            /* [33] */
          __IO unsigned long long  PROTCTL:3;                              /* [36:34] */
          __IO unsigned long long  DS_UPD_EN:1;                            /* [37] */
          __IO unsigned long long  SS_UPD_EN:1;                            /* [38] */
          __IO unsigned long long  SRC_PER:4;                              /* [42:39] */
          __IO unsigned long long  DEST_PER:4;                             /* [46:43] */
          __IO unsigned long long  :17;                                    /* [63:47] */
        } BIT;
      } CFG;
      union                                            /* Offset=0x0048 : SGR */
      {
        __IO unsigned long long  LONGLONG;
        struct
        {
          __IO unsigned long long  SGI:20;                                 /* [19:0] */
          __IO unsigned long long  SGC:12;                                 /* [31:20] */
          __IO unsigned long long  :32;                                    /* [63:32] */
        } BIT;
      } SGR;
      union                                            /* Offset=0x0050 : DSR */
      {
        __IO unsigned long long  LONGLONG;
        struct
        {
          __IO unsigned long long  DSI:20;                                 /* [19:0] */
          __IO unsigned long long  DSC:12;                                 /* [31:20] */
          __IO unsigned long long  :32;                                    /* [63:32] */
        } BIT;
      } DSR;
    } DMA_CHAN_SFR_LAYOUT[MAX_DMA_CHAN];            /* Array of channel specific struct for each channel*/


  union                                            /* Offset=0x02C0 : RawTfr */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  RAW:8;                                  /* [7:0] */
      __IO unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } RawTfr;
  union                                            /* Offset=0x02C8 : RawBlock */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  RAW:8;                                  /* [7:0] */
      __IO unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } RawBlock;
  union                                            /* Offset=0x02D0 : RawSrcTran */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  RAW:8;                                  /* [7:0] */
      __IO unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } RawSrcTran;
  union                                            /* Offset=0x02D8 : RawDstTran */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  RAW:8;                                  /* [7:0] */
      __IO unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } RawDstTran;
  union                                            /* Offset=0x02E0 : RawErr */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  RAW:8;                                  /* [7:0] */
      __IO unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } RawErr;
  union                                            /* Offset=0x02E8 : StatusTfr */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  STATUS:8;                               /* [7:0] */
      __I  unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } StatusTfr;
  union                                            /* Offset=0x02F0 : StatusBlock */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  STATUS:8;                               /* [7:0] */
      __I  unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } StatusBlock;
  union                                            /* Offset=0x02F8 : StatusSrcTran */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  STATUS:8;                               /* [7:0] */
      __I  unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } StatusSrcTran;
  union                                            /* Offset=0x0300 : StatusDstTran */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  STATUS:8;                               /* [7:0] */
      __I  unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } StatusDstTran;
  union                                            /* Offset=0x0308 : StatusErr */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  STATUS:8;                               /* [7:0] */
      __I  unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } StatusErr;
  union                                            /* Offset=0x0310 : MaskTfr */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  INT_MASK:8;                             /* [7:0] */
      __O  unsigned long long  INT_MASK_WE:8;                          /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } MaskTfr;
  union                                            /* Offset=0x0318 : MaskBlock */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  INT_MASK:8;                             /* [7:0] */
      __O  unsigned long long  INT_MASK_WE:8;                          /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } MaskBlock;
  union                                            /* Offset=0x0320 : MaskSrcTran */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  INT_MASK:8;                             /* [7:0] */
      __O  unsigned long long  INT_MASK_WE:8;                          /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } MaskSrcTran;
  union                                            /* Offset=0x0328 : MaskDstTran */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  INT_MASK:8;                             /* [7:0] */
      __O  unsigned long long  INT_MASK_WE:8;                          /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } MaskDstTran;
  union                                            /* Offset=0x0330 : MaskErr */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  INT_MASK:8;                             /* [7:0] */
      __O  unsigned long long  INT_MASK_WE:8;                          /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } MaskErr;
  union                                            /* Offset=0x0338 : ClearTfr */
  {
    __O  unsigned long long  LONGLONG;
    struct
    {
      __O  unsigned long long  CLEAR:8;                                /* [7:0] */
      __O  unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } ClearTfr;
  union                                            /* Offset=0x0340 : ClearBlock */
  {
    __O  unsigned long long  LONGLONG;
    struct
    {
      __O  unsigned long long  CLEAR:8;                                /* [7:0] */
      __O  unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } ClearBlock;
  union                                            /* Offset=0x0348 : ClearSrcTran */
  {
    __O  unsigned long long  LONGLONG;
    struct
    {
      __O  unsigned long long  CLEAR:8;                                /* [7:0] */
      __O  unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } ClearSrcTran;
  union                                            /* Offset=0x0350 : ClearDstTran */
  {
    __O  unsigned long long  LONGLONG;
    struct
    {
      __O  unsigned long long  CLEAR:8;                                /* [7:0] */
      __O  unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } ClearDstTran;
  union                                            /* Offset=0x0358 : ClearErr */
  {
    __O  unsigned long long  LONGLONG;
    struct
    {
      __O  unsigned long long  CLEAR:8;                                /* [7:0] */
      __O  unsigned long long  :56;                                    /* [63:8] */
    } BIT;
  } ClearErr;
  union                                            /* Offset=0x0360 : StatusInt */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  TFR:1;                                  /* [0] */
      __I  unsigned long long  BLOCK:1;                                /* [1] */
      __I  unsigned long long  SRCT:1;                                 /* [2] */
      __I  unsigned long long  DSTT:1;                                 /* [3] */
      __I  unsigned long long  ERR:1;                                  /* [4] */
      __I  unsigned long long  :59;                                    /* [63:5] */
    } BIT;
  } StatusInt;
  union                                            /* Offset=0x0368 : ReqSrcReg */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  SRC_REQ:8;                              /* [7:0] */
      __O  unsigned long long  SRC_REQ_WE:8;                           /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } ReqSrcReg;
  union                                            /* Offset=0x0370 : ReqDstReg */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  DST_REQ:8;                              /* [7:0] */
      __O  unsigned long long  DST_REQ_WE:8;                           /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } ReqDstReg;
  union                                            /* Offset=0x0378 : SglRqSrcReg */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  SRC_SGLREQ:8;                           /* [7:0] */
      __O  unsigned long long  SRC_SGLREQ_WE:8;                        /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } SglRqSrcReg;
  union                                            /* Offset=0x0380 : SglRqDstReg */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  DST_SGLREQ:8;                           /* [7:0] */
      __O  unsigned long long  DST_SGLREQ_WE:8;                        /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } SglRqDstReg;
  union                                            /* Offset=0x0388 : LstSrcReg */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  LSTSRC:8;                               /* [7:0] */
      __O  unsigned long long  LSTSRC_WE:8;                            /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } LstSrcReg;
  union                                            /* Offset=0x0390 : LstDstReg */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  LSTDST:8;                               /* [7:0] */
      __O  unsigned long long  LSTDST_WE:8;                            /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } LstDstReg;
  union                                            /* Offset=0x0398 : DmaCfgReg */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  DMA_EN:1;                               /* [0] */
      __IO unsigned long long  :63;                                    /* [63:1] */
    } BIT;
  } DmaCfgReg;
  union                                            /* Offset=0x03A0 : ChEnReg */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  CH_EN:8;                                /* [7:0] */
      __O  unsigned long long  CH_EN_WE:8;                             /* [15:8] */
      __IO unsigned long long  :48;                                    /* [63:16] */
    } BIT;
  } ChEnReg;
  union                                            /* Offset=0x03A8 : DmaIdReg */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  DMA_ID:32;                              /* [31:0] */
      __I  unsigned long long  :32;                                    /* [63:32] */
    } BIT;
  } DmaIdReg;
  union                                            /* Offset=0x03B0 : DmaTestReg */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  TEST_SLV_IF:1;                          /* [0] */
      __IO unsigned long long  :63;                                    /* [63:1] */
    } BIT;
  } DmaTestReg;
} DMAC_Type;
#endif  /* End of __DMAC_SFR__DEFINE_HEADER__ */
