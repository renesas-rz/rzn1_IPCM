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
 **       for RZN1 MSEBIS
 **
 **       revision 0.30 (16.January.2018)
 **
 **********************************************************************************************************************/
#ifndef __MSEBIS_SFR__DEFINE_HEADER__
#define __MSEBIS_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : MSEBIS
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : rMSEBIS_CYCLESIZE_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   bMSEBIS_CLEDATA:1;                          /* [1] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   bMSEBIS_RDDLEDATA_B:2;                      /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIS_WRDLEDATA_B:2;                      /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIS_RDDLEDATA_NB:8;                     /* [23:16] */
      __IO unsigned long   bMSEBIS_WRDLEDATA_NB:8;                     /* [31:24] */
    } BIT;
  } rMSEBIS_CYCLESIZE_CS0_N;
  union                                            /* Offset=0x0004 : rMSEBIS_SETUPHOLD_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_RDDLESETUP:6;                       /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   bMSEBIS_WRDLESETUP:6;                       /* [13:8] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_SETUPHOLD_CS0_N;
  union                                            /* Offset=0x0008 : rMSEBIS_MMU_ADDR_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :12;                                        /* [11:0] */
      __IO unsigned long   bMSEBIS_MMU_ADDR:20;                        /* [31:12] */
    } BIT;
  } rMSEBIS_MMU_ADDR_CS0_N;
  union                                            /* Offset=0x000C : rMSEBIS_MMU_ADDR_MASK_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :12;                                        /* [11:0] */
      __IO unsigned long   bMSEBIS_MMU_ADDR_MASK:20;                   /* [31:12] */
    } BIT;
  } rMSEBIS_MMU_ADDR_MASK_CS0_N;
  union                                            /* Offset=0x0010 : rMSEBIS_DMATX_REQ_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_DMATX_FORCE:1;                      /* [0] */
      __IO unsigned long   bMSEBIS_DMATX_ENABLE:1;                     /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rMSEBIS_DMATX_REQ_CS0_N;
  union                                            /* Offset=0x0014 : rMSEBIS_DMARX_REQ_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_DMARX_FORCE:1;                      /* [0] */
      __IO unsigned long   bMSEBIS_DMARX_ENABLE:1;                     /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rMSEBIS_DMARX_REQ_CS0_N;
  union                                            /* Offset=0x0018 : rMSEBIS_DMATDLR_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_DMATX_MAX_BURST:2;                  /* [1:0] */
      __IO unsigned long   bMSEBIS_DMATX_OPT_BURST:1;                  /* [2] */
      __IO unsigned long   bMSEBIS_DMATX_FLOW_CTRL:1;                  /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __I  unsigned long   bMSEBIS_DMATX_FIFO_LVL:6;                   /* [13:8] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_DMATDLR_CS0_N;
  union                                            /* Offset=0x001C : rMSEBIS_DMARDLR_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_DMARX_MAX_BURST:2;                  /* [1:0] */
      __IO unsigned long   bMSEBIS_DMARX_FLOW_CTRL:1;                  /* [2] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __I  unsigned long   bMSEBIS_DMARX_FIFO_L:6;                     /* [13:8] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_DMARDLR_CS0_N;
  char                     wk_0020[0x0040];
  union                                            /* Offset=0x0060 : rMSEBIS_CONFIG_CS0_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_CONFIG:2;                           /* [1:0] */
      __I  unsigned long   bMSEBIS_BUSY:1;                             /* [2] */
      __IO unsigned long   bMSEBIS_WEN:1;                              /* [3] */
      __IO unsigned long   :1;                                         /* [4] */
      __IO unsigned long   bMSEBIS_MODE_WAIT:2;                        /* [6:5] */
      __IO unsigned long   bMSEBIS_BURST_ENABLE:1;                     /* [7] */
      __IO unsigned long   bMSEBIS_ADDR_MODE:1;                        /* [8] */
      __IO unsigned long   bMSEBIS_CS_ENABLE:1;                        /* [9] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIS_CS0N_ROUTING_CS1_N:1;               /* [12] */
      __IO unsigned long   bMSEBIS_CS0N_ROUTING_CS2_N:1;               /* [13] */
      __IO unsigned long   bMSEBIS_CS0N_ROUTING_CS3_N:1;               /* [14] */
      __IO unsigned long   :17;                                        /* [31:15] */
    } BIT;
  } rMSEBIS_CONFIG_CS0_N;
  char                     wk_0064[0x009C];
  union                                            /* Offset=0x0100 : rMSEBIS_CYCLESIZE_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   bMSEBIS_CLEDATA:1;                          /* [1] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   bMSEBIS_RDDLEDATA_B:2;                      /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIS_WRDLEDATA_B:2;                      /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIS_RDDLEDATA_NB:8;                     /* [23:16] */
      __IO unsigned long   bMSEBIS_WRDLEDATA_NB:8;                     /* [31:24] */
    } BIT;
  } rMSEBIS_CYCLESIZE_CS1_N;
  union                                            /* Offset=0x0104 : rMSEBIS_SETUPHOLD_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_RDDLESETUP:6;                       /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   bMSEBIS_WRDLESETUP:6;                       /* [13:8] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_SETUPHOLD_CS1_N;
  union                                            /* Offset=0x0108 : rMSEBIS_MMU_ADDR_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :12;                                        /* [11:0] */
      __IO unsigned long   bMSEBIS_MMU_ADDR:20;                        /* [31:12] */
    } BIT;
  } rMSEBIS_MMU_ADDR_CS1_N;
  union                                            /* Offset=0x010C : rMSEBIS_MMU_ADDR_MASK_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :12;                                        /* [11:0] */
      __IO unsigned long   bMSEBIS_MMU_ADDR_MASK:20;                   /* [31:12] */
    } BIT;
  } rMSEBIS_MMU_ADDR_MASK_CS1_N;
  union                                            /* Offset=0x0110 : rMSEBIS_DMATX_REQ_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_DMATX_FORCE:1;                      /* [0] */
      __IO unsigned long   bMSEBIS_DMATX_ENABLE:1;                     /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rMSEBIS_DMATX_REQ_CS1_N;
  union                                            /* Offset=0x0114 : rMSEBIS_DMARX_REQ_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_DMARX_FORCE:1;                      /* [0] */
      __IO unsigned long   bMSEBIS_DMARX_ENABLE:1;                     /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } rMSEBIS_DMARX_REQ_CS1_N;
  union                                            /* Offset=0x0118 : rMSEBIS_DMATDLR_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_DMATX_MAX_BURST:2;                  /* [1:0] */
      __IO unsigned long   bMSEBIS_DMATX_OPT_BURST:1;                  /* [2] */
      __IO unsigned long   bMSEBIS_DMATX_FLOW_CTRL:1;                  /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __I  unsigned long   bMSEBIS_DMATX_FIFO_LVL:6;                   /* [13:8] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_DMATDLR_CS1_N;
  union                                            /* Offset=0x011C : rMSEBIS_DMARDLR_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_DMARX_MAX_BURST:2;                  /* [1:0] */
      __IO unsigned long   bMSEBIS_DMARX_FLOW_CTRL:1;                  /* [2] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __I  unsigned long   bMSEBIS_DMARX_FIFO_L:6;                     /* [13:8] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_DMARDLR_CS1_N;
  char                     wk_0120[0x0040];
  union                                            /* Offset=0x0160 : rMSEBIS_CONFIG_CS1_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_CONFIG:2;                           /* [1:0] */
      __I  unsigned long   bMSEBIS_BUSY:1;                             /* [2] */
      __IO unsigned long   bMSEBIS_WEN:1;                              /* [3] */
      __IO unsigned long   :1;                                         /* [4] */
      __IO unsigned long   bMSEBIS_MODE_WAIT:2;                        /* [6:5] */
      __IO unsigned long   bMSEBIS_BURST_ENABLE:1;                     /* [7] */
      __IO unsigned long   bMSEBIS_ADDR_MODE:1;                        /* [8] */
      __IO unsigned long   bMSEBIS_CS_ENABLE:1;                        /* [9] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIS_CS1N_ROUTING_CS1_N:1;               /* [12] */
      __IO unsigned long   bMSEBIS_CS1N_ROUTING_CS2_N:1;               /* [13] */
      __IO unsigned long   bMSEBIS_CS1N_ROUTING_CS3_N:1;               /* [14] */
      __IO unsigned long   :17;                                        /* [31:15] */
    } BIT;
  } rMSEBIS_CONFIG_CS1_N;
  char                     wk_0164[0x009C];
  union                                            /* Offset=0x0200 : rMSEBIS_CYCLESIZE_CS2_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   bMSEBIS_CLEDATA:1;                          /* [1] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   bMSEBIS_RDDLEDATA_B:2;                      /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIS_WRDLEDATA_B:2;                      /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIS_RDDLEDATA_NB:8;                     /* [23:16] */
      __IO unsigned long   bMSEBIS_WRDLEDATA_NB:8;                     /* [31:24] */
    } BIT;
  } rMSEBIS_CYCLESIZE_CS2_N;
  union                                            /* Offset=0x0204 : rMSEBIS_SETUPHOLD_CS2_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_RDDLESETUP:6;                       /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   bMSEBIS_WRDLESETUP:6;                       /* [13:8] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_SETUPHOLD_CS2_N;
  union                                            /* Offset=0x0208 : rMSEBIS_MMU_ADDR_CS2_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :12;                                        /* [11:0] */
      __IO unsigned long   bMSEBIS_MMU_ADDR:20;                        /* [31:12] */
    } BIT;
  } rMSEBIS_MMU_ADDR_CS2_N;
  union                                            /* Offset=0x020C : rMSEBIS_MMU_ADDR_MASK_CS2_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :12;                                        /* [11:0] */
      __IO unsigned long   bMSEBIS_MMU_ADDR_MASK:20;                   /* [31:12] */
    } BIT;
  } rMSEBIS_MMU_ADDR_MASK_CS2_N;
  char                     wk_0210[0x0050];
  union                                            /* Offset=0x0260 : rMSEBIS_CONFIG_CS2_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_CONFIG:2;                           /* [1:0] */
      __I  unsigned long   bMSEBIS_BUSY:1;                             /* [2] */
      __IO unsigned long   bMSEBIS_WEN:1;                              /* [3] */
      __IO unsigned long   :1;                                         /* [4] */
      __IO unsigned long   bMSEBIS_MODE_WAIT:2;                        /* [6:5] */
      __IO unsigned long   bMSEBIS_BURST_ENABLE:1;                     /* [7] */
      __IO unsigned long   bMSEBIS_ADDR_MODE:1;                        /* [8] */
      __IO unsigned long   bMSEBIS_CS_ENABLE:1;                        /* [9] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIS_CS2N_ROUTING_CS1_N:1;               /* [12] */
      __IO unsigned long   bMSEBIS_CS2N_ROUTING_CS2_N:1;               /* [13] */
      __IO unsigned long   bMSEBIS_CS2N_ROUTING_CS3_N:1;               /* [14] */
      __IO unsigned long   :17;                                        /* [31:15] */
    } BIT;
  } rMSEBIS_CONFIG_CS2_N;
  char                     wk_0264[0x009C];
  union                                            /* Offset=0x0300 : rMSEBIS_CYCLESIZE_CS3_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   bMSEBIS_CLEDATA:1;                          /* [1] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   bMSEBIS_RDDLEDATA_B:2;                      /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIS_WRDLEDATA_B:2;                      /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   bMSEBIS_RDDLEDATA_NB:8;                     /* [23:16] */
      __IO unsigned long   bMSEBIS_WRDLEDATA_NB:8;                     /* [31:24] */
    } BIT;
  } rMSEBIS_CYCLESIZE_CS3_N;
  union                                            /* Offset=0x0304 : rMSEBIS_SETUPHOLD_CS3_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_RDDLESETUP:6;                       /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   bMSEBIS_WRDLESETUP:6;                       /* [13:8] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_SETUPHOLD_CS3_N;
  union                                            /* Offset=0x0308 : rMSEBIS_MMU_ADDR_CS3_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :12;                                        /* [11:0] */
      __IO unsigned long   bMSEBIS_MMU_ADDR:20;                        /* [31:12] */
    } BIT;
  } rMSEBIS_MMU_ADDR_CS3_N;
  union                                            /* Offset=0x030C : rMSEBIS_MMU_ADDR_MASK_CS3_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :12;                                        /* [11:0] */
      __IO unsigned long   bMSEBIS_MMU_ADDR_MASK:20;                   /* [31:12] */
    } BIT;
  } rMSEBIS_MMU_ADDR_MASK_CS3_N;
  char                     wk_0310[0x0050];
  union                                            /* Offset=0x0360 : rMSEBIS_CONFIG_CS3_N */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_CONFIG:2;                           /* [1:0] */
      __I  unsigned long   bMSEBIS_BUSY:1;                             /* [2] */
      __IO unsigned long   bMSEBIS_WEN:1;                              /* [3] */
      __IO unsigned long   :1;                                         /* [4] */
      __IO unsigned long   bMSEBIS_MODE_WAIT:2;                        /* [6:5] */
      __IO unsigned long   bMSEBIS_BURST_ENABLE:1;                     /* [7] */
      __IO unsigned long   bMSEBIS_ADDR_MODE:1;                        /* [8] */
      __IO unsigned long   bMSEBIS_CS_ENABLE:1;                        /* [9] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIS_CS3N_ROUTING_CS1_N:1;               /* [12] */
      __IO unsigned long   bMSEBIS_CS3N_ROUTING_CS2_N:1;               /* [13] */
      __IO unsigned long   bMSEBIS_CS3N_ROUTING_CS3_N:1;               /* [14] */
      __IO unsigned long   :17;                                        /* [31:15] */
    } BIT;
  } rMSEBIS_CONFIG_CS3_N;
  char                     wk_0364[0x049C];
  union                                            /* Offset=0x0800 : rMSEBIS_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_BURST_SIZEMAX_CPUREAD:2;            /* [1:0] */
      __IO unsigned long   bMSEBIS_BURST_SIZEMAX_CPUWRITE:2;           /* [3:2] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __I  unsigned long   bMSEBIS_CPURX_FIFO_LVL:6;                   /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __I  unsigned long   bMSEBIS_CPUTX_FIFO_LVL:6;                   /* [21:16] */
      __IO unsigned long   bMSEBIS_AHB_MASTER_BUF:1;                   /* [22] */
      __IO unsigned long   bMSEBIS_AHB_MASTER_CACHE:1;                 /* [23] */
      __IO unsigned long   bMSEBIS_TIMEOUT_REG_ACCESS_DELAY:4;         /* [27:24] */
      __IO unsigned long   bMSEBIS_TIMEOUT_REG_ACCESS:1;               /* [28] */
      __IO unsigned long   :1;                                         /* [29] */
      __IO unsigned long   bMSEBIS_WAIT_CONF:1;                        /* [30] */
    } BIT;
  } rMSEBIS_CONFIG;
  union                                            /* Offset=0x0804 : rMSEBIS_STATUS_INT0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bMSEBIS_INT0_CPURX:4;                       /* [3:0] */
      __I  unsigned long   bMSEBIS_INT0_CPUTX:4;                       /* [7:4] */
      __I  unsigned long   bMSEBIS_INT0_DMARX:2;                       /* [9:8] */
      __I  unsigned long   :2;                                         /* [11:10] */
      __I  unsigned long   bMSEBIS_INT0_DMATX:2;                       /* [13:12] */
      __I  unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_STATUS_INT0;
  union                                            /* Offset=0x0808 : rMSEBIS_STATUS_INT1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bMSEBIS_INT1_CPURX:4;                       /* [3:0] */
      __I  unsigned long   bMSEBIS_INT1_CPUTX:4;                       /* [7:4] */
      __I  unsigned long   bMSEBIS_INT1_DMARX:2;                       /* [9:8] */
      __I  unsigned long   :2;                                         /* [11:10] */
      __I  unsigned long   bMSEBIS_INT1_DMATX:2;                       /* [13:12] */
      __I  unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_STATUS_INT1;
  union                                            /* Offset=0x080C : rMSEBIS_MASK_INT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_MASK_INT_CPURX:4;                   /* [3:0] */
      __IO unsigned long   bMSEBIS_MASK_INT_CPUTX:4;                   /* [7:4] */
      __IO unsigned long   bMSEBIS_MASK_INT_DMARX:2;                   /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIS_MASK_INT_DMATX:2;                   /* [13:12] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_MASK_INT;
  union                                            /* Offset=0x0810 : rMSEBIS_CLR_INT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bMSEBIS_CLR_INT_CPURX:4;                    /* [3:0] */
      __IO unsigned long   bMSEBIS_CLR_INT_CPUTX:4;                    /* [7:4] */
      __IO unsigned long   bMSEBIS_CLR_INT_DMARX:2;                    /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   bMSEBIS_CLR_INT_DMATX:2;                    /* [13:12] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } rMSEBIS_CLR_INT;
  union                                            /* Offset=0x0814 : rMSEBIS_EOB_ADDR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                                         /* [1:0] */
      __IO unsigned long   bMSEBIS_EOB_ADDR:30;                        /* [31:2] */
    } BIT;
  } rMSEBIS_EOB_ADDR;
} MSEBIS_Type;
#endif  /* End of __MSEBIS_SFR__DEFINE_HEADER__ */
