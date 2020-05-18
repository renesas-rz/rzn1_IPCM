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
 **       for RZN1 MSEBIM
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __MSEBIM_SFR__DEFINE_HEADER__
#define __MSEBIM_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : MSEBIM
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : rMSEBIM_CYCLESIZE_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_ALEDATA:1;                          /* [0] */
      __IO unsigned long   bMSEBIM_CLEDATA:1;                          /* [1] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   bMSEBIM_RDDLEDATA_B:2;                      /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIM_WRDLEDATA_B:2;                      /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIM_RDDLEDATA_NB:8;                     /* [23:16] */
      __IO unsigned long   bMSEBIM_WRDLEDATA_NB:8;                     /* [31:24] */
    } BIT;
  } rMSEBIM_CYCLESIZE_CS0_N;
  union                                            /* Offset=0x0004 : rMSEBIM_SETUPHOLD_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_RDDLESETUP:6;                       /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   bMSEBIM_WRDLESETUP:6;                       /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIM_RDDLEHOLD:6;                        /* [21:16] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __IO unsigned long   bMSEBIM_WRDLEHOLD:6;                        /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } rMSEBIM_SETUPHOLD_CS0_N;
  union                                            /* Offset=0x0008 : rMSEBIM_TDMACR_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_TDMAE1:1;                           /* [0] */
      __IO unsigned long   bMSEBIM_DEST_BURST_SIZE:3;                  /* [3:1] */
      __IO unsigned long   bMSEBIM_DEST_BLOCK_SIZE:13;                 /* [16:4] */
      __I  unsigned long   bMSEBIM_CURRENT_DEST_BLOCK_SIZE:13;         /* [29:17] */
      __I  unsigned long   bMSEBIM_SINGLE_DEST_WIDTH:1;                /* [30] */
    } BIT;
  } rMSEBIM_TDMACR_CS0_N;
  union                                            /* Offset=0x000C : rMSEBIM_RDMACR_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_RDMAE1:1;                           /* [0] */
      __IO unsigned long   bMSEBIM_SRC_BURST_SIZE:3;                   /* [3:1] */
      __IO unsigned long   bMSEBIM_SRC_BLOCK_SIZE:13;                  /* [16:4] */
      __I  unsigned long   bMSEBIM_CURRENT_SRC_BLOCK_SIZE:13;          /* [29:17] */
      __I  unsigned long   bMSEBIM_SINGLE_SRC_WIDTH:1;                 /* [30] */
    } BIT;
  } rMSEBIM_RDMACR_CS0_N;
  union                                            /* Offset=0x0010 : rMSEBIM_ADDRDMA_READ_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                                         /* [1:0] */
      __IO unsigned long   bMSEBIM_ADDRDMA_READ_2:1;                   /* [2] */
      __IO unsigned long   bMSEBIM_ADDRDMA_READ:29;                    /* [31:3] */
    } BIT;
  } rMSEBIM_ADDRDMA_READ_CS0_N;
  union                                            /* Offset=0x0014 : rMSEBIM_ADDRDMA_CURRENTREAD_CS0_N */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bMSEBIM_ADDRDMA_CURRENTREAD:32;             /* [31:0] */
    } BIT;
  } rMSEBIM_ADDRDMA_CURRENTREAD_CS0_N;
  union                                            /* Offset=0x0018 : rMSEBIM_ADDRDMA_WRITE_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                                         /* [1:0] */
      __IO unsigned long   bMSEBIM_ADDRDMA_WRITE_2:1;                  /* [2] */
      __IO unsigned long   bMSEBIM_ADDRDMA_WRITE:29;                   /* [31:3] */
    } BIT;
  } rMSEBIM_ADDRDMA_WRITE_CS0_N;
  union                                            /* Offset=0x001C : rMSEBIM_ADDRDMA_CURRENTWRITE_CS0_N */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bMSEBIM_ADDRDMA_CURRENTWRITE:32;            /* [31:0] */
    } BIT;
  } rMSEBIM_ADDRDMA_CURRENTWRITE_CS0_N;
  union                                            /* Offset=0x0020 : rMSEBIM_DMATDLR_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_DMATDLR:5;                          /* [4:0] */
      __IO unsigned long   :1;                                         /* [5] */
      __I  unsigned long   bMSEBIM_DMA_TRANSMIT_FIFOLEVEL:6;           /* [11:6] */
      __IO unsigned long   :1;                                         /* [12] */
      __IO unsigned long   bMSEBIM_BURST_SIZEMAX_DMAWRITE:3;           /* [15:13] */
      __IO unsigned long   bMSEBIM_USE_EXT_WRDMA_REQ:1;                /* [16] */
      __IO unsigned long   :15;                                        /* [31:17] */
    } BIT;
  } rMSEBIM_DMATDLR_CS0_N;
  union                                            /* Offset=0x0024 : rMSEBIM_DMARDLR_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_DMARDLR:5;                          /* [4:0] */
      __IO unsigned long   :1;                                         /* [5] */
      __I  unsigned long   bMSEBIM_DMA_RECEIVE_FIFOLEVEL:6;            /* [11:6] */
      __IO unsigned long   :1;                                         /* [12] */
      __IO unsigned long   bMSEBIM_BURST_SIZEMAX_DMAREAD:3;            /* [15:13] */
      __IO unsigned long   bMSEBIM_USE_EXT_RDDMA_REQ:1;                /* [16] */
      __IO unsigned long   :15;                                        /* [31:17] */
    } BIT;
  } rMSEBIM_DMARDLR_CS0_N;
  char                     wk_0028[0x0038];
  union                                            /* Offset=0x0060 : rMSEBIM_CONFIG_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_CONFIG:3;                           /* [2:0] */
      __IO unsigned long   :2;                                         /* [4:3] */
      __IO unsigned long   bMSEBIM_MODE_WAIT:2;                        /* [6:5] */
      __IO unsigned long   bMSEBIM_BURST_ENABLE:1;                     /* [7] */
      __IO unsigned long   bMSEBIM_ALE_NUMBER:3;                       /* [10:8] */
      __IO unsigned long   bMSEBIM_ALE_MODE:1;                         /* [11] */
      __IO unsigned long   bMSEBIM_CS0N_ROUTING_CS1_N:1;               /* [12] */
      __IO unsigned long   bMSEBIM_CS0N_ROUTING_CS2_N:1;               /* [13] */
      __IO unsigned long   bMSEBIM_CS0N_ROUTING_CS3_N:1;               /* [14] */
      __IO unsigned long   bMSEBIM_MULTI_DLE:1;                        /* [15] */
      __IO unsigned long   :11;                                        /* [26:16] */
      __IO unsigned long   bMSEBIM_EXTEND_ADDR:5;                      /* [31:27] */
    } BIT;
  } rMSEBIM_CONFIG_CS0_N;
  char                     wk_0064[0x009C];
  union                                            /* Offset=0x0100 : rMSEBIM_CYCLESIZE_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_ALEDATA:1;                          /* [0] */
      __IO unsigned long   bMSEBIM_CLEDATA:1;                          /* [1] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   bMSEBIM_RDDLEDATA_B:2;                      /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIM_WRDLEDATA_B:2;                      /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIM_RDDLEDATA_NB:8;                     /* [23:16] */
      __IO unsigned long   bMSEBIM_WRDLEDATA_NB:8;                     /* [31:24] */
    } BIT;
  } rMSEBIM_CYCLESIZE_CS1_N;
  union                                            /* Offset=0x0104 : rMSEBIM_SETUPHOLD_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_RDDLESETUP:6;                       /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   bMSEBIM_WRDLESETUP:6;                       /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIM_RDDLEHOLD:6;                        /* [21:16] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __IO unsigned long   bMSEBIM_WRDLEHOLD:6;                        /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } rMSEBIM_SETUPHOLD_CS1_N;
  union                                            /* Offset=0x0108 : rMSEBIM_TDMACR_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_TDMAE1:1;                           /* [0] */
      __IO unsigned long   bMSEBIM_DEST_BURST_SIZE:3;                  /* [3:1] */
      __IO unsigned long   bMSEBIM_DEST_BLOCK_SIZE:13;                 /* [16:4] */
      __I  unsigned long   bMSEBIM_CURRENT_DEST_BLOCK_SIZE:13;         /* [29:17] */
      __I  unsigned long   bMSEBIM_SINGLE_DEST_WIDTH:1;                /* [30] */
    } BIT;
  } rMSEBIM_TDMACR_CS1_N;
  union                                            /* Offset=0x010C : rMSEBIM_RDMACR_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_RDMAE1:1;                           /* [0] */
      __IO unsigned long   bMSEBIM_SRC_BURST_SIZE:3;                   /* [3:1] */
      __IO unsigned long   bMSEBIM_SRC_BLOCK_SIZE:13;                  /* [16:4] */
      __I  unsigned long   bMSEBIM_CURRENT_SRC_BLOCK_SIZE:13;          /* [29:17] */
      __I  unsigned long   bMSEBIM_SINGLE_SRC_WIDTH:1;                 /* [30] */
    } BIT;
  } rMSEBIM_RDMACR_CS1_N;
  union                                            /* Offset=0x0110 : rMSEBIM_ADDRDMA_READ_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                                         /* [1:0] */
      __IO unsigned long   bMSEBIM_ADDRDMA_READ_2:1;                   /* [2] */
      __IO unsigned long   bMSEBIM_ADDRDMA_READ:29;                    /* [31:3] */
    } BIT;
  } rMSEBIM_ADDRDMA_READ_CS1_N;
  union                                            /* Offset=0x0114 : rMSEBIM_ADDRDMA_CURRENTREAD_CS1_N */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bMSEBIM_ADDRDMA_CURRENTREAD:32;             /* [31:0] */
    } BIT;
  } rMSEBIM_ADDRDMA_CURRENTREAD_CS1_N;
  union                                            /* Offset=0x0118 : rMSEBIM_ADDRDMA_WRITE_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                                         /* [1:0] */
      __IO unsigned long   bMSEBIM_ADDRDMA_WRITE_2:1;                  /* [2] */
      __IO unsigned long   bMSEBIM_ADDRDMA_WRITE:29;                   /* [31:3] */
    } BIT;
  } rMSEBIM_ADDRDMA_WRITE_CS1_N;
  union                                            /* Offset=0x011C : rMSEBIM_ADDRDMA_CURRENTWRITE_CS1_N */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bMSEBIM_ADDRDMA_CURRENTWRITE:32;            /* [31:0] */
    } BIT;
  } rMSEBIM_ADDRDMA_CURRENTWRITE_CS1_N;
  union                                            /* Offset=0x0120 : rMSEBIM_DMATDLR_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_DMATDLR:5;                          /* [4:0] */
      __IO unsigned long   :1;                                         /* [5] */
      __I  unsigned long   bMSEBIM_DMA_TRANSMIT_FIFOLEVEL:6;           /* [11:6] */
      __IO unsigned long   :1;                                         /* [12] */
      __IO unsigned long   bMSEBIM_BURST_SIZEMAX_DMAWRITE:3;           /* [15:13] */
      __IO unsigned long   bMSEBIM_USE_EXT_WRDMA_REQ:1;                /* [16] */
      __IO unsigned long   :15;                                        /* [31:17] */
    } BIT;
  } rMSEBIM_DMATDLR_CS1_N;
  union                                            /* Offset=0x0124 : rMSEBIM_DMARDLR_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_DMARDLR:5;                          /* [4:0] */
      __IO unsigned long   :1;                                         /* [5] */
      __I  unsigned long   bMSEBIM_DMA_RECEIVE_FIFOLEVEL:6;            /* [11:6] */
      __IO unsigned long   :1;                                         /* [12] */
      __IO unsigned long   bMSEBIM_BURST_SIZEMAX_DMAREAD:3;            /* [15:13] */
      __IO unsigned long   bMSEBIM_USE_EXT_RDDMA_REQ:1;                /* [16] */
      __IO unsigned long   :15;                                        /* [31:17] */
    } BIT;
  } rMSEBIM_DMARDLR_CS1_N;
  char                     wk_0128[0x0038];
  union                                            /* Offset=0x0160 : rMSEBIM_CONFIG_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_CONFIG:3;                           /* [2:0] */
      __IO unsigned long   :2;                                         /* [4:3] */
      __IO unsigned long   bMSEBIM_MODE_WAIT:2;                        /* [6:5] */
      __IO unsigned long   bMSEBIM_BURST_ENABLE:1;                     /* [7] */
      __IO unsigned long   bMSEBIM_ALE_NUMBER:3;                       /* [10:8] */
      __IO unsigned long   bMSEBIM_ALE_MODE:1;                         /* [11] */
      __IO unsigned long   bMSEBIM_CS0N_ROUTING_CS1_N:1;               /* [12] */
      __IO unsigned long   bMSEBIM_CS1N_ROUTING_CS2_N:1;               /* [13] */
      __IO unsigned long   bMSEBIM_CS1N_ROUTING_CS3_N:1;               /* [14] */
      __IO unsigned long   bMSEBIM_MULTI_DLE:1;                        /* [15] */
      __IO unsigned long   :11;                                        /* [26:16] */
      __IO unsigned long   bMSEBIM_EXTEND_ADDR:5;                      /* [31:27] */
    } BIT;
  } rMSEBIM_CONFIG_CS1_N;
  char                     wk_0164[0x009C];
  union                                            /* Offset=0x0200 : rMSEBIM_CYCLESIZE_CS2_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_ALEDATA:1;                          /* [0] */
      __IO unsigned long   bMSEBIM_CLEDATA:1;                          /* [1] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   bMSEBIM_RDDLEDATA_B:2;                      /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIM_WRDLEDATA_B:2;                      /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIM_RDDLEDATA_NB:8;                     /* [23:16] */
      __IO unsigned long   bMSEBIM_WRDLEDATA_NB:8;                     /* [31:24] */
    } BIT;
  } rMSEBIM_CYCLESIZE_CS2_N;
  union                                            /* Offset=0x0204 : rMSEBIM_SETUPHOLD_CS2_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_RDDLESETUP:6;                       /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   bMSEBIM_WRDLESETUP:6;                       /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIM_RDDLEHOLD:6;                        /* [21:16] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __IO unsigned long   bMSEBIM_WRDLEHOLD:6;                        /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } rMSEBIM_SETUPHOLD_CS2_N;
  char                     wk_0208[0x0058];
  union                                            /* Offset=0x0260 : rMSEBIM_CONFIG_CS2_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_CONFIG:3;                           /* [2:0] */
      __IO unsigned long   :2;                                         /* [4:3] */
      __IO unsigned long   bMSEBIM_MODE_WAIT:2;                        /* [6:5] */
      __IO unsigned long   bMSEBIM_BURST_ENABLE:1;                     /* [7] */
      __IO unsigned long   bMSEBIM_ALE_NUMBER:3;                       /* [10:8] */
      __IO unsigned long   bMSEBIM_ALE_MODE:1;                         /* [11] */
      __IO unsigned long   bMSEBIM_CS0N_ROUTING_CS1_N:1;               /* [12] */
      __IO unsigned long   bMSEBIM_CS2N_ROUTING_CS2_N:1;               /* [13] */
      __IO unsigned long   bMSEBIM_CS2N_ROUTING_CS3_N:1;               /* [14] */
      __IO unsigned long   bMSEBIM_MULTI_DLE:1;                        /* [15] */
      __IO unsigned long   :11;                                        /* [26:16] */
      __IO unsigned long   bMSEBIM_EXTEND_ADDR:5;                      /* [31:27] */
    } BIT;
  } rMSEBIM_CONFIG_CS2_N;
  char                     wk_0264[0x009C];
  union                                            /* Offset=0x0300 : rMSEBIM_CYCLESIZE_CS3_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_ALEDATA:1;                          /* [0] */
      __IO unsigned long   bMSEBIM_CLEDATA:1;                          /* [1] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   bMSEBIM_RDDLEDATA_B:2;                      /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIM_WRDLEDATA_B:2;                      /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIM_RDDLEDATA_NB:8;                     /* [23:16] */
      __IO unsigned long   bMSEBIM_WRDLEDATA_NB:8;                     /* [31:24] */
    } BIT;
  } rMSEBIM_CYCLESIZE_CS3_N;
  union                                            /* Offset=0x0304 : rMSEBIM_SETUPHOLD_CS3_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_RDDLESETUP:6;                       /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   bMSEBIM_WRDLESETUP:6;                       /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIM_RDDLEHOLD:6;                        /* [21:16] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __IO unsigned long   bMSEBIM_WRDLEHOLD:6;                        /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } rMSEBIM_SETUPHOLD_CS3_N;
  char                     wk_0308[0x0058];
  union                                            /* Offset=0x0360 : rMSEBIM_CONFIG_CS3_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_CONFIG:3;                           /* [2:0] */
      __IO unsigned long   :2;                                         /* [4:3] */
      __IO unsigned long   bMSEBIM_MODE_WAIT:2;                        /* [6:5] */
      __IO unsigned long   bMSEBIM_BURST_ENABLE:1;                     /* [7] */
      __IO unsigned long   bMSEBIM_ALE_NUMBER:3;                       /* [10:8] */
      __IO unsigned long   bMSEBIM_ALE_MODE:1;                         /* [11] */
      __IO unsigned long   bMSEBIM_CS0N_ROUTING_CS1_N:1;               /* [12] */
      __IO unsigned long   bMSEBIM_CS3N_ROUTING_CS2_N:1;               /* [13] */
      __IO unsigned long   bMSEBIM_CS3N_ROUTING_CS3_N:1;               /* [14] */
      __IO unsigned long   bMSEBIM_MULTI_DLE:1;                        /* [15] */
      __IO unsigned long   :11;                                        /* [26:16] */
      __IO unsigned long   bMSEBIM_EXTEND_ADDR:5;                      /* [31:27] */
    } BIT;
  } rMSEBIM_CONFIG_CS3_N;
  char                     wk_0364[0x049C];
  union                                            /* Offset=0x0800 : rMSEBIM_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIM_CLKL:2;                             /* [1:0] */
      __IO unsigned long   bMSEBIM_CLKH:2;                             /* [3:2] */
      __IO unsigned long   bMSEBIM_CLKENABLE:1;                        /* [4] */
      __IO unsigned long   bMSEBIM_BURST_SIZEMAX_CPUWRITE:3;           /* [7:5] */
      __IO unsigned long   bMSEBIM_BURST_SIZEMAX_CPUREAD:3;            /* [10:8] */
      __I  unsigned long   bMSEBIM_CPU_TRANSMIT_FIFOLEVEL:6;           /* [16:11] */
      __I  unsigned long   bMSEBIM_CPU_RECEIVE_FIFOLEVEL:6;            /* [22:17] */
      __IO unsigned long   :9;                                         /* [31:23] */
    } BIT;
  } rMSEBIM_CONFIG;
  char                     wk_0804[0x0004];
  union                                            /* Offset=0x0808 : rMSEBIM_CPU_FIFOREAD_FLUSH */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bMSEBIM_CPU_FIFOREAD_FLUSH:32;              /* [31:0] */
    } BIT;
  } rMSEBIM_CPU_FIFOREAD_FLUSH;
} MSEBIM_Type;
#endif  /* End of __MSEBIM_SFR__DEFINE_HEADER__ */
