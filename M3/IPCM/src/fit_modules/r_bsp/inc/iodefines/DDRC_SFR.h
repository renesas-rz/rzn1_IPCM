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
 **       for RZN1 DDRC
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __DDRC_SFR__DEFINE_HEADER__
#define __DDRC_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : DDRC
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : DDR_CTL_00 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   START:1;                                    /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   DRAM_CLASS:4;                               /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __I  unsigned long   VERSION:16;                                 /* [31:16] */
    } BIT;
  } DDR_CTL_00;
  union                                            /* Offset=0x0004 : DDR_CTL_01 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MAX_ROW_REG:5;                              /* [4:0] */
      __I  unsigned long   :3;                                         /* [7:5] */
      __I  unsigned long   MAX_COL_REG:4;                              /* [11:8] */
      __I  unsigned long   :4;                                         /* [15:12] */
      __I  unsigned long   MAX_CS_REG:2;                               /* [17:16] */
      __I  unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   READ_DATA_FIFO_DEPTH:8;                     /* [31:24] */
    } BIT;
  } DDR_CTL_01;
  union                                            /* Offset=0x0008 : DDR_CTL_02 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   READ_DATA_FIFO_PTR_WIDTH:8;                 /* [7:0] */
      __I  unsigned long   WRITE_DATA_FIFO_DEPTH:8;                    /* [15:8] */
      __I  unsigned long   WRITE_DATA_FIFO_PTR_WIDTH:8;                /* [23:16] */
      __I  unsigned long   ASYNC_CDC_STAGES:8;                         /* [31:24] */
    } BIT;
  } DDR_CTL_02;
  union                                            /* Offset=0x000C : DDR_CTL_03 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   AXI0_CMDFIFO_LOG2_DEPTH:8;                  /* [7:0] */
      __I  unsigned long   AXI0_RDFIFO_LOG2_DEPTH:8;                   /* [15:8] */
      __I  unsigned long   AXI0_WRFIFO_LOG2_DEPTH:8;                   /* [23:16] */
      __I  unsigned long   AXI0_WRCMD_PROC_FIFO_LOG2_DEPTH:8;          /* [31:24] */
    } BIT;
  } DDR_CTL_03;
  union                                            /* Offset=0x0010 : DDR_CTL_04 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   AXI1_CMDFIFO_LOG2_DEPTH:8;                  /* [7:0] */
      __I  unsigned long   AXI1_RDFIFO_LOG2_DEPTH:8;                   /* [15:8] */
      __I  unsigned long   AXI1_WRFIFO_LOG2_DEPTH:8;                   /* [23:16] */
      __I  unsigned long   AXI1_WRCMD_PROC_FIFO_LOG2_DEPTH:8;          /* [31:24] */
    } BIT;
  } DDR_CTL_04;
  union                                            /* Offset=0x0014 : DDR_CTL_05 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   AXI2_CMDFIFO_LOG2_DEPTH:8;                  /* [7:0] */
      __I  unsigned long   AXI2_RDFIFO_LOG2_DEPTH:8;                   /* [15:8] */
      __I  unsigned long   AXI2_WRFIFO_LOG2_DEPTH:8;                   /* [23:16] */
      __I  unsigned long   AXI2_WRCMD_PROC_FIFO_LOG2_DEPTH:8;          /* [31:24] */
    } BIT;
  } DDR_CTL_05;
  union                                            /* Offset=0x0018 : DDR_CTL_06 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   AXI3_CMDFIFO_LOG2_DEPTH:8;                  /* [7:0] */
      __I  unsigned long   AXI3_RDFIFO_LOG2_DEPTH:8;                   /* [15:8] */
      __I  unsigned long   AXI3_WRFIFO_LOG2_DEPTH:8;                   /* [23:16] */
      __I  unsigned long   AXI3_WRCMD_PROC_FIFO_LOG2_DEPTH:8;          /* [31:24] */
    } BIT;
  } DDR_CTL_06;
  union                                            /* Offset=0x001C : DDR_CTL_07 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TINIT:24;                                   /* [23:0] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } DDR_CTL_07;
  union                                            /* Offset=0x0020 : DDR_CTL_08 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TRST_PWRON:32;                              /* [31:0] */
    } BIT;
  } DDR_CTL_08;
  union                                            /* Offset=0x0024 : DDR_CTL_09 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CKE_INACTIVE:32;                            /* [31:0] */
    } BIT;
  } DDR_CTL_09;
  union                                            /* Offset=0x0028 : DDR_CTL_10 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   INITAREF:4;                                 /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   TCPD:16;                                    /* [23:8] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } DDR_CTL_10;
  union                                            /* Offset=0x002C : DDR_CTL_11 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDLL:16;                                    /* [15:0] */
      __IO unsigned long   NO_CMD_INIT:1;                              /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __IO unsigned long   CASLAT_LIN:6;                               /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } DDR_CTL_11;
  union                                            /* Offset=0x0030 : DDR_CTL_12 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WRLAT:5;                                    /* [4:0] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   ADDITIVE_LAT:5;                             /* [12:8] */
      __IO unsigned long   :3;                                         /* [15:13] */
      __IO unsigned long   TBST_INT_INTERVAL:3;                        /* [18:16] */
      __IO unsigned long   :5;                                         /* [23:19] */
      __IO unsigned long   TCCD:5;                                     /* [28:24] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } DDR_CTL_12;
  union                                            /* Offset=0x0034 : DDR_CTL_13 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TRRD:8;                                     /* [7:0] */
      __IO unsigned long   TRC:8;                                      /* [15:8] */
      __IO unsigned long   TRAS_MIN:8;                                 /* [23:16] */
      __IO unsigned long   TWTR:6;                                     /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } DDR_CTL_13;
  union                                            /* Offset=0x0038 : DDR_CTL_14 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TRP:5;                                      /* [4:0] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   TFAW:6;                                     /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   TRTP:4;                                     /* [19:16] */
      __IO unsigned long   :4;                                         /* [23:20] */
      __IO unsigned long   TMRD:5;                                     /* [28:24] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } DDR_CTL_14;
  union                                            /* Offset=0x003C : DDR_CTL_15 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TMOD:8;                                     /* [7:0] */
      __IO unsigned long   TRAS_MAX:17;                                /* [24:8] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_15;
  union                                            /* Offset=0x0040 : DDR_CTL_16 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TCKE:3;                                     /* [2:0] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __IO unsigned long   TCKESR:8;                                   /* [15:8] */
      __IO unsigned long   WRITEINTERP:1;                              /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __IO unsigned long   TRCD:8;                                     /* [31:24] */
    } BIT;
  } DDR_CTL_16;
  union                                            /* Offset=0x0044 : DDR_CTL_17 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TWR:6;                                      /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   AP:1;                                       /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __IO unsigned long   CONCURRENTAP:1;                             /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __IO unsigned long   TRAS_LOCKOUT:1;                             /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_17;
  union                                            /* Offset=0x0048 : DDR_CTL_18 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDAL:6;                                     /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   BSTLEN:3;                                   /* [10:8] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   TRP_AB:5;                                   /* [20:16] */
      __IO unsigned long   :3;                                         /* [23:21] */
      __IO unsigned long   REG_DIMM_ENABLE:1;                          /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_18;
  union                                            /* Offset=0x004C : DDR_CTL_19 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRESS_MIRRORING:2;                        /* [1:0] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __O  unsigned long   AREFRESH:1;                                 /* [8] */
      __IO unsigned long   :15;                                        /* [23:9] */
      __IO unsigned long   TREF_ENABLE:1;                              /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_19;
  union                                            /* Offset=0x0050 : DDR_CTL_20 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TRFC:10;                                    /* [9:0] */
      __IO unsigned long   :6;                                         /* [15:10] */
      __IO unsigned long   TREF:14;                                    /* [29:16] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } DDR_CTL_20;
  union                                            /* Offset=0x0054 : DDR_CTL_21 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TREF_INTERVAL:14;                           /* [13:0] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } DDR_CTL_21;
  union                                            /* Offset=0x0058 : DDR_CTL_22 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TPDEX:16;                                   /* [15:0] */
      __IO unsigned long   TXPDLL:16;                                  /* [31:16] */
    } BIT;
  } DDR_CTL_22;
  union                                            /* Offset=0x005C : DDR_CTL_23 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXARD:16;                                   /* [15:0] */
      __IO unsigned long   TXARDS:16;                                  /* [31:16] */
    } BIT;
  } DDR_CTL_23;
  union                                            /* Offset=0x0060 : DDR_CTL_24 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXSR:16;                                    /* [15:0] */
      __IO unsigned long   TXSNR:16;                                   /* [31:16] */
    } BIT;
  } DDR_CTL_24;
  union                                            /* Offset=0x0064 : DDR_CTL_25 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PWRUP_SREFRESH_EXIT:1;                      /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   SREFRESH_EXIT_NO_REFRESH:1;                 /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __IO unsigned long   ENABLE_QUICK_SREFRESH:1;                    /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __IO unsigned long   CKE_DELAY:3;                                /* [26:24] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } DDR_CTL_25;
  union                                            /* Offset=0x0068 : DDR_CTL_26 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   LOWPOWER_REFRESH_ENABLE:2;                  /* [1:0] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   CKSRE:8;                                    /* [15:8] */
      __IO unsigned long   CKSRX:8;                                    /* [23:16] */
      __O  unsigned long   LP_CMD:8;                                   /* [31:24] */
    } BIT;
  } DDR_CTL_26;
  union                                            /* Offset=0x006C : DDR_CTL_27 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   LP_STATE:6;                                 /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __I  unsigned long   LP_ARB_STATE:4;                             /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   LP_AUTO_ENTRY_EN:3;                         /* [18:16] */
      __IO unsigned long   :5;                                         /* [23:19] */
      __IO unsigned long   LP_AUTO_EXIT_EN:3;                          /* [26:24] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } DDR_CTL_27;
  union                                            /* Offset=0x0070 : DDR_CTL_28 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   LP_AUTO_MEM_GATE_EN:2;                      /* [1:0] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   LP_AUTO_PD_IDLE:12;                         /* [19:8] */
      __IO unsigned long   :4;                                         /* [23:20] */
      __IO unsigned long   LP_AUTO_SR_IDLE:8;                          /* [31:24] */
    } BIT;
  } DDR_CTL_28;
  union                                            /* Offset=0x0074 : DDR_CTL_29 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   LP_AUTO_SR_MC_GATE_IDLE:8;                  /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } DDR_CTL_29;
  union                                            /* Offset=0x0078 : DDR_CTL_30 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WRITE_MODEREG:26;                           /* [25:0] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } DDR_CTL_30;
  union                                            /* Offset=0x007C : DDR_CTL_31 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   MRW_STATUS:8;                               /* [7:0] */
      __IO unsigned long   MR0_DATA_0:16;                              /* [23:8] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } DDR_CTL_31;
  union                                            /* Offset=0x0080 : DDR_CTL_32 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MR1_DATA_0:16;                              /* [15:0] */
      __IO unsigned long   MR2_DATA_0:16;                              /* [31:16] */
    } BIT;
  } DDR_CTL_32;
  union                                            /* Offset=0x0084 : DDR_CTL_33 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MRSINGLE_DATA_0:16;                         /* [15:0] */
      __IO unsigned long   MR3_DATA_0:16;                              /* [31:16] */
    } BIT;
  } DDR_CTL_33;
  union                                            /* Offset=0x0088 : DDR_CTL_34 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MR0_DATA_1:16;                              /* [15:0] */
      __IO unsigned long   MR1_DATA_1:16;                              /* [31:16] */
    } BIT;
  } DDR_CTL_34;
  union                                            /* Offset=0x008C : DDR_CTL_35 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MR2_DATA_1:16;                              /* [15:0] */
      __IO unsigned long   MRSINGLE_DATA_1:16;                         /* [31:16] */
    } BIT;
  } DDR_CTL_35;
  union                                            /* Offset=0x0090 : DDR_CTL_36 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MR3_DATA_1:16;                              /* [15:0] */
      __IO unsigned long   ECC_EN:1;                                   /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __O  unsigned long   FWC:1;                                      /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_36;
  union                                            /* Offset=0x0094 : DDR_CTL_37 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   XOR_CHECK_BITS:14;                          /* [13:0] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   ECC_DISABLE_W_UC_ERR:1;                     /* [16] */
      __IO unsigned long   :15;                                        /* [31:17] */
    } BIT;
  } DDR_CTL_37;
  union                                            /* Offset=0x0098 : DDR_CTL_38 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ECC_U_ADDR:32;                              /* [31:0] */
    } BIT;
  } DDR_CTL_38;
  union                                            /* Offset=0x009C : DDR_CTL_39 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ECC_U_SYND:7;                               /* [6:0] */
      __I  unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } DDR_CTL_39;
  union                                            /* Offset=0x00A0 : DDR_CTL_40 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ECC_U_DATA:32;                              /* [31:0] */
    } BIT;
  } DDR_CTL_40;
  union                                            /* Offset=0x00A4 : DDR_CTL_41 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ECC_C_ADDR:32;                              /* [31:0] */
    } BIT;
  } DDR_CTL_41;
  union                                            /* Offset=0x00A8 : DDR_CTL_42 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ECC_C_SYND:7;                               /* [6:0] */
      __I  unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } DDR_CTL_42;
  union                                            /* Offset=0x00AC : DDR_CTL_43 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ECC_C_DATA:32;                              /* [31:0] */
    } BIT;
  } DDR_CTL_43;
  union                                            /* Offset=0x00B0 : DDR_CTL_44 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :16;                                        /* [15:0] */
      __IO unsigned long   LONG_COUNT_MASK:5;                          /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } DDR_CTL_44;
  union                                            /* Offset=0x00B4 : DDR_CTL_45 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ZQINIT:12;                                  /* [11:0] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   ZQCL:12;                                    /* [27:16] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } DDR_CTL_45;
  union                                            /* Offset=0x00B8 : DDR_CTL_46 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ZQCS:12;                                    /* [11:0] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __O  unsigned long   ZQ_REQ:2;                                   /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   ZQ_ON_SREF_EXIT:2;                          /* [25:24] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } DDR_CTL_46;
  union                                            /* Offset=0x00BC : DDR_CTL_47 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ZQ_INTERVAL:32;                             /* [31:0] */
    } BIT;
  } DDR_CTL_47;
  union                                            /* Offset=0x00C0 : DDR_CTL_48 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   ZQ_IN_PROGRESS:1;                           /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   ZQCS_ROTATE:1;                              /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __IO unsigned long   BANK_DIFF:2;                                /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   ROW_DIFF:3;                                 /* [26:24] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } DDR_CTL_48;
  union                                            /* Offset=0x00C4 : DDR_CTL_49 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   COL_DIFF:4;                                 /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   APREBIT:4;                                  /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AGE_COUNT:8;                                /* [23:16] */
      __IO unsigned long   COMMAND_AGE_COUNT:8;                        /* [31:24] */
    } BIT;
  } DDR_CTL_49;
  union                                            /* Offset=0x00C8 : DDR_CTL_50 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDR_CMP_EN:1;                              /* [0] */
      __IO unsigned long   :15;                                        /* [15:1] */
      __IO unsigned long   BANK_SPLIT_EN:1;                            /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __IO unsigned long   PLACEMENT_EN:1;                             /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_50;
  union                                            /* Offset=0x00CC : DDR_CTL_51 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRIORITY_EN:1;                              /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   RW_SAME_EN:1;                               /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __IO unsigned long   RW_SAME_PAGE_EN:1;                          /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __IO unsigned long   CS_SAME_EN:1;                               /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_51;
  union                                            /* Offset=0x00D0 : DDR_CTL_52 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   W2R_SPLIT_EN:1;                             /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   DISABLE_RW_GROUP_W_BNK_CONFLICT:2;          /* [9:8] */
      __IO unsigned long   :6;                                         /* [15:10] */
      __IO unsigned long   NUM_Q_ENTRIES_ACT_DISABLE:3;                /* [18:16] */
      __IO unsigned long   :5;                                         /* [23:19] */
      __IO unsigned long   SWAP_EN:1;                                  /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_52;
  union                                            /* Offset=0x00D4 : DDR_CTL_53 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DISABLE_RD_INTERLEAVE:1;                    /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   INHIBIT_DRAM_CMD:1;                         /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __IO unsigned long   CS_MAP:2;                                   /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   BURST_ON_FLY_BIT:4;                         /* [27:24] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } DDR_CTL_53;
  union                                            /* Offset=0x00D8 : DDR_CTL_54 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   REDUC:1;                                    /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   Q_FULLNESS:3;                               /* [10:8] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   IN_ORDER_ACCEPT:1;                          /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __I  unsigned long   CONTROLLER_BUSY:1;                          /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_54;
  union                                            /* Offset=0x00DC : DDR_CTL_55 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __O  unsigned long   CTRLUPD_REQ:1;                              /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   CTRLUPD_REQ_PER_AREF_EN:1;                  /* [8] */
      __IO unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } DDR_CTL_55;
  union                                            /* Offset=0x00E0 : DDR_CTL_56 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   INT_STATUS:23;                              /* [22:0] */
      __I  unsigned long   :9;                                         /* [31:23] */
    } BIT;
  } DDR_CTL_56;
  union                                            /* Offset=0x00E4 : DDR_CTL_57 */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   INT_ACK:22;                                 /* [21:0] */
      __O  unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } DDR_CTL_57;
  union                                            /* Offset=0x00E8 : DDR_CTL_58 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   INT_MASK:23;                                /* [22:0] */
      __IO unsigned long   :9;                                         /* [31:23] */
    } BIT;
  } DDR_CTL_58;
  union                                            /* Offset=0x00EC : DDR_CTL_59 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OUT_OF_RANGE_ADDR:32;                       /* [31:0] */
    } BIT;
  } DDR_CTL_59;
  union                                            /* Offset=0x00F0 : DDR_CTL_60 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OUT_OF_RANGE_LENGTH:7;                      /* [6:0] */
      __I  unsigned long   :1;                                         /* [7] */
      __I  unsigned long   OUT_OF_RANGE_TYPE:6;                        /* [13:8] */
      __I  unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } DDR_CTL_60;
  union                                            /* Offset=0x00F4 : DDR_CTL_61 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PORT_CMD_ERROR_ADDR:32;                     /* [31:0] */
    } BIT;
  } DDR_CTL_61;
  union                                            /* Offset=0x00F8 : DDR_CTL_62 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :8;                                         /* [7:0] */
      __I  unsigned long   PORT_CMD_ERROR_TYPE:3;                      /* [10:8] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   ODT_RD_MAP_CS0:2;                           /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   ODT_WR_MAP_CS0:2;                           /* [25:24] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } DDR_CTL_62;
  union                                            /* Offset=0x00FC : DDR_CTL_63 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ODT_RD_MAP_CS1:2;                           /* [1:0] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   ODT_WR_MAP_CS1:2;                           /* [9:8] */
      __IO unsigned long   :6;                                         /* [15:10] */
      __IO unsigned long   TODTL_2CMD:8;                               /* [23:16] */
      __IO unsigned long   TODTH_WR:4;                                 /* [27:24] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } DDR_CTL_63;
  union                                            /* Offset=0x0100 : DDR_CTL_64 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TODTH_RD:4;                                 /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   ODT_EN:1;                                   /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __IO unsigned long   WR_TO_ODTH:7;                               /* [22:16] */
      __IO unsigned long   :1;                                         /* [23] */
      __IO unsigned long   RD_TO_ODTH:7;                               /* [30:24] */
    } BIT;
  } DDR_CTL_64;
  union                                            /* Offset=0x0104 : DDR_CTL_65 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OBSOLETE0:32;                               /* [31:0] */
    } BIT;
  } DDR_CTL_65;
  union                                            /* Offset=0x0108 : DDR_CTL_66 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   R2R_DIFFCS_DLY:3;                           /* [2:0] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __IO unsigned long   R2W_DIFFCS_DLY:3;                           /* [10:8] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   W2R_DIFFCS_DLY:3;                           /* [18:16] */
      __IO unsigned long   :5;                                         /* [23:19] */
      __IO unsigned long   W2W_DIFFCS_DLY:4;                           /* [27:24] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } DDR_CTL_66;
  union                                            /* Offset=0x010C : DDR_CTL_67 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   R2R_SAMECS_DLY:3;                           /* [2:0] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __IO unsigned long   R2W_SAMECS_DLY:3;                           /* [10:8] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   W2R_SAMECS_DLY:3;                           /* [18:16] */
      __IO unsigned long   :5;                                         /* [23:19] */
      __IO unsigned long   W2W_SAMECS_DLY:3;                           /* [26:24] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } DDR_CTL_67;
  union                                            /* Offset=0x0110 : DDR_CTL_68 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   OCD_ADJUST_PDN_CS_0:5;                      /* [4:0] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   OCD_ADJUST_PUP_CS_0:5;                      /* [12:8] */
      __IO unsigned long   :3;                                         /* [15:13] */
      __IO unsigned long   SW_LEVELING_MODE:2;                         /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __O  unsigned long   SWLVL_LOAD:1;                               /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_68;
  union                                            /* Offset=0x0114 : DDR_CTL_69 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __O  unsigned long   SWLVL_START:1;                              /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __O  unsigned long   SWLVL_EXIT:1;                               /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __I  unsigned long   SWLVL_OP_DONE:1;                            /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __I  unsigned long   LVL_STATUS:4;                               /* [27:24] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } DDR_CTL_69;
  union                                            /* Offset=0x0118 : DDR_CTL_70 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   SWLVL_RESP_0:8;                             /* [7:0] */
      __I  unsigned long   SWLVL_RESP_1:8;                             /* [15:8] */
      __I  unsigned long   SWLVL_RESP_2:8;                             /* [23:16] */
      __O  unsigned long   WRLVL_REQ:1;                                /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_70;
  union                                            /* Offset=0x011C : DDR_CTL_71 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WRLVL_CS:1;                                 /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   WLDQSEN:6;                                  /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   WLMRD:6;                                    /* [21:16] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __IO unsigned long   WRLVL_EN:1;                                 /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_71;
  union                                            /* Offset=0x0120 : DDR_CTL_72 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WRLVL_INTERVAL:16;                          /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __I  unsigned long   WRLVL_ERROR_STATUS:8;                       /* [31:24] */
    } BIT;
  } DDR_CTL_72;
  union                                            /* Offset=0x0124 : DDR_CTL_73 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WRLVL_REG_EN:1;                             /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   WRLVL_DELAY_0:16;                           /* [23:8] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } DDR_CTL_73;
  union                                            /* Offset=0x0128 : DDR_CTL_74 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WRLVL_DELAY_1:16;                           /* [15:0] */
      __IO unsigned long   WRLVL_DELAY_2:16;                           /* [31:16] */
    } BIT;
  } DDR_CTL_74;
  union                                            /* Offset=0x012C : DDR_CTL_75 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __O  unsigned long   RDLVL_REQ:1;                                /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __O  unsigned long   RDLVL_GATE_REQ:1;                           /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __IO unsigned long   RDLVL_CS:1;                                 /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __IO unsigned long   RDLVL_EDGE:1;                               /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_75;
  union                                            /* Offset=0x0130 : DDR_CTL_76 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_BEGIN_DELAY_EN:1;                     /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   RDLVL_REG_EN:1;                             /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __IO unsigned long   RDLVL_GATE_REG_EN:1;                        /* [16] */
      __IO unsigned long   :15;                                        /* [31:17] */
    } BIT;
  } DDR_CTL_76;
  union                                            /* Offset=0x0134 : DDR_CTL_77 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RDLVL_BEGIN_DELAY_0:16;                     /* [15:0] */
      __I  unsigned long   RDLVL_END_DELAY_0:16;                       /* [31:16] */
    } BIT;
  } DDR_CTL_77;
  union                                            /* Offset=0x0138 : DDR_CTL_78 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   RDLVL_MIDPOINT_DELAY_0:16;                  /* [15:0] */
      __IO unsigned long   RDLVL_OFFSET_DELAY_0:16;                    /* [31:16] */
    } BIT;
  } DDR_CTL_78;
  union                                            /* Offset=0x013C : DDR_CTL_79 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_OFFSET_DIR_0:1;                       /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   RDLVL_DELAY_0:16;                           /* [23:8] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } DDR_CTL_79;
  union                                            /* Offset=0x0140 : DDR_CTL_80 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_GATE_DELAY_0:16;                      /* [15:0] */
      __I  unsigned long   RDLVL_BEGIN_DELAY_1:16;                     /* [31:16] */
    } BIT;
  } DDR_CTL_80;
  union                                            /* Offset=0x0144 : DDR_CTL_81 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RDLVL_END_DELAY_1:16;                       /* [15:0] */
      __I  unsigned long   RDLVL_MIDPOINT_DELAY_1:16;                  /* [31:16] */
    } BIT;
  } DDR_CTL_81;
  union                                            /* Offset=0x0148 : DDR_CTL_82 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_OFFSET_DELAY_1:16;                    /* [15:0] */
      __IO unsigned long   RDLVL_OFFSET_DIR_1:1;                       /* [16] */
      __IO unsigned long   :15;                                        /* [31:17] */
    } BIT;
  } DDR_CTL_82;
  union                                            /* Offset=0x014C : DDR_CTL_83 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_DELAY_1:16;                           /* [15:0] */
      __IO unsigned long   RDLVL_GATE_DELAY_1:16;                      /* [31:16] */
    } BIT;
  } DDR_CTL_83;
  union                                            /* Offset=0x0150 : DDR_CTL_84 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RDLVL_BEGIN_DELAY_2:16;                     /* [15:0] */
      __I  unsigned long   RDLVL_END_DELAY_2:16;                       /* [31:16] */
    } BIT;
  } DDR_CTL_84;
  union                                            /* Offset=0x0154 : DDR_CTL_85 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   RDLVL_MIDPOINT_DELAY_2:16;                  /* [15:0] */
      __IO unsigned long   RDLVL_OFFSET_DELAY_2:16;                    /* [31:16] */
    } BIT;
  } DDR_CTL_85;
  union                                            /* Offset=0x0158 : DDR_CTL_86 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_OFFSET_DIR_2:1;                       /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   RDLVL_DELAY_2:16;                           /* [23:8] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } DDR_CTL_86;
  union                                            /* Offset=0x015C : DDR_CTL_87 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_GATE_DELAY_2:16;                      /* [15:0] */
      __IO unsigned long   AXI0_R_PRIORITY:2;                          /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   AXI0_W_PRIORITY:2;                          /* [25:24] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } DDR_CTL_87;
  union                                            /* Offset=0x0160 : DDR_CTL_88 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_FIFO_TYPE_REG:2;                       /* [1:0] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   AXI1_R_PRIORITY:2;                          /* [9:8] */
      __IO unsigned long   :6;                                         /* [15:10] */
      __IO unsigned long   AXI1_W_PRIORITY:2;                          /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   AXI1_FIFO_TYPE_REG:2;                       /* [25:24] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } DDR_CTL_88;
  union                                            /* Offset=0x0164 : DDR_CTL_89 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_R_PRIORITY:2;                          /* [1:0] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   AXI2_W_PRIORITY:2;                          /* [9:8] */
      __IO unsigned long   :6;                                         /* [15:10] */
      __IO unsigned long   AXI2_FIFO_TYPE_REG:2;                       /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   AXI3_R_PRIORITY:2;                          /* [25:24] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } DDR_CTL_89;
  union                                            /* Offset=0x0168 : DDR_CTL_90 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_W_PRIORITY:2;                          /* [1:0] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   AXI3_FIFO_TYPE_REG:2;                       /* [9:8] */
      __IO unsigned long   :14;                                        /* [23:10] */
      __IO unsigned long   PORT_ADDR_PROTECTION_EN:1;                  /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_90;
  union                                            /* Offset=0x016C : DDR_CTL_91 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_0:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_91;
  union                                            /* Offset=0x0170 : DDR_CTL_92 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_0:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_92;
  union                                            /* Offset=0x0174 : DDR_CTL_93 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_1:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_93;
  union                                            /* Offset=0x0178 : DDR_CTL_94 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_1:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_94;
  union                                            /* Offset=0x017C : DDR_CTL_95 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_2:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_95;
  union                                            /* Offset=0x0180 : DDR_CTL_96 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_2:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_96;
  union                                            /* Offset=0x0184 : DDR_CTL_97 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_3:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_97;
  union                                            /* Offset=0x0188 : DDR_CTL_98 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_3:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_98;
  union                                            /* Offset=0x018C : DDR_CTL_99 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_4:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_99;
  union                                            /* Offset=0x0190 : DDR_CTL_100 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_4:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_100;
  union                                            /* Offset=0x0194 : DDR_CTL_101 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_5:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_101;
  union                                            /* Offset=0x0198 : DDR_CTL_102 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_5:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_102;
  union                                            /* Offset=0x019C : DDR_CTL_103 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_6:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_103;
  union                                            /* Offset=0x01A0 : DDR_CTL_104 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_6:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_104;
  union                                            /* Offset=0x01A4 : DDR_CTL_105 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_7:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_105;
  union                                            /* Offset=0x01A8 : DDR_CTL_106 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_7:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_106;
  union                                            /* Offset=0x01AC : DDR_CTL_107 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_8:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_107;
  union                                            /* Offset=0x01B0 : DDR_CTL_108 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_8:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_108;
  union                                            /* Offset=0x01B4 : DDR_CTL_109 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_9:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_109;
  union                                            /* Offset=0x01B8 : DDR_CTL_110 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_9:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_110;
  union                                            /* Offset=0x01BC : DDR_CTL_111 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_10:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_111;
  union                                            /* Offset=0x01C0 : DDR_CTL_112 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_10:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_112;
  union                                            /* Offset=0x01C4 : DDR_CTL_113 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_11:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_113;
  union                                            /* Offset=0x01C8 : DDR_CTL_114 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_11:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_114;
  union                                            /* Offset=0x01CC : DDR_CTL_115 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_12:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_115;
  union                                            /* Offset=0x01D0 : DDR_CTL_116 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_12:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_116;
  union                                            /* Offset=0x01D4 : DDR_CTL_117 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_13:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_117;
  union                                            /* Offset=0x01D8 : DDR_CTL_118 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_13:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_118;
  union                                            /* Offset=0x01DC : DDR_CTL_119 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_14:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_119;
  union                                            /* Offset=0x01E0 : DDR_CTL_120 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_14:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_120;
  union                                            /* Offset=0x01E4 : DDR_CTL_121 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_START_ADDR_15:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_121;
  union                                            /* Offset=0x01E8 : DDR_CTL_122 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_END_ADDR_15:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_122;
  union                                            /* Offset=0x01EC : DDR_CTL_123 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_0:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_123;
  union                                            /* Offset=0x01F0 : DDR_CTL_124 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_0:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_124;
  union                                            /* Offset=0x01F4 : DDR_CTL_125 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_1:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_125;
  union                                            /* Offset=0x01F8 : DDR_CTL_126 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_1:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_126;
  union                                            /* Offset=0x01FC : DDR_CTL_127 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_2:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_127;
  union                                            /* Offset=0x0200 : DDR_CTL_128 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_2:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_128;
  union                                            /* Offset=0x0204 : DDR_CTL_129 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_3:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_129;
  union                                            /* Offset=0x0208 : DDR_CTL_130 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_3:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_130;
  union                                            /* Offset=0x020C : DDR_CTL_131 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_4:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_131;
  union                                            /* Offset=0x0210 : DDR_CTL_132 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_4:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_132;
  union                                            /* Offset=0x0214 : DDR_CTL_133 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_5:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_133;
  union                                            /* Offset=0x0218 : DDR_CTL_134 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_5:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_134;
  union                                            /* Offset=0x021C : DDR_CTL_135 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_6:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_135;
  union                                            /* Offset=0x0220 : DDR_CTL_136 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_6:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_136;
  union                                            /* Offset=0x0224 : DDR_CTL_137 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_7:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_137;
  union                                            /* Offset=0x0228 : DDR_CTL_138 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_7:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_138;
  union                                            /* Offset=0x022C : DDR_CTL_139 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_8:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_139;
  union                                            /* Offset=0x0230 : DDR_CTL_140 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_8:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_140;
  union                                            /* Offset=0x0234 : DDR_CTL_141 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_9:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_141;
  union                                            /* Offset=0x0238 : DDR_CTL_142 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_9:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_142;
  union                                            /* Offset=0x023C : DDR_CTL_143 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_10:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_143;
  union                                            /* Offset=0x0240 : DDR_CTL_144 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_10:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_144;
  union                                            /* Offset=0x0244 : DDR_CTL_145 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_11:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_145;
  union                                            /* Offset=0x0248 : DDR_CTL_146 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_11:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_146;
  union                                            /* Offset=0x024C : DDR_CTL_147 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_12:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_147;
  union                                            /* Offset=0x0250 : DDR_CTL_148 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_12:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_148;
  union                                            /* Offset=0x0254 : DDR_CTL_149 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_13:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_149;
  union                                            /* Offset=0x0258 : DDR_CTL_150 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_13:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_150;
  union                                            /* Offset=0x025C : DDR_CTL_151 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_14:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_151;
  union                                            /* Offset=0x0260 : DDR_CTL_152 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_14:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_152;
  union                                            /* Offset=0x0264 : DDR_CTL_153 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_START_ADDR_15:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_153;
  union                                            /* Offset=0x0268 : DDR_CTL_154 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_END_ADDR_15:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_154;
  union                                            /* Offset=0x026C : DDR_CTL_155 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_0:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_155;
  union                                            /* Offset=0x0270 : DDR_CTL_156 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_0:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_156;
  union                                            /* Offset=0x0274 : DDR_CTL_157 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_1:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_157;
  union                                            /* Offset=0x0278 : DDR_CTL_158 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_1:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_158;
  union                                            /* Offset=0x027C : DDR_CTL_159 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_2:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_159;
  union                                            /* Offset=0x0280 : DDR_CTL_160 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_2:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_160;
  union                                            /* Offset=0x0284 : DDR_CTL_161 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_3:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_161;
  union                                            /* Offset=0x0288 : DDR_CTL_162 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_3:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_162;
  union                                            /* Offset=0x028C : DDR_CTL_163 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_4:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_163;
  union                                            /* Offset=0x0290 : DDR_CTL_164 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_4:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_164;
  union                                            /* Offset=0x0294 : DDR_CTL_165 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_5:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_165;
  union                                            /* Offset=0x0298 : DDR_CTL_166 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_5:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_166;
  union                                            /* Offset=0x029C : DDR_CTL_167 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_6:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_167;
  union                                            /* Offset=0x02A0 : DDR_CTL_168 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_6:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_168;
  union                                            /* Offset=0x02A4 : DDR_CTL_169 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_7:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_169;
  union                                            /* Offset=0x02A8 : DDR_CTL_170 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_7:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_170;
  union                                            /* Offset=0x02AC : DDR_CTL_171 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_8:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_171;
  union                                            /* Offset=0x02B0 : DDR_CTL_172 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_8:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_172;
  union                                            /* Offset=0x02B4 : DDR_CTL_173 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_9:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_173;
  union                                            /* Offset=0x02B8 : DDR_CTL_174 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_9:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_174;
  union                                            /* Offset=0x02BC : DDR_CTL_175 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_10:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_175;
  union                                            /* Offset=0x02C0 : DDR_CTL_176 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_10:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_176;
  union                                            /* Offset=0x02C4 : DDR_CTL_177 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_11:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_177;
  union                                            /* Offset=0x02C8 : DDR_CTL_178 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_11:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_178;
  union                                            /* Offset=0x02CC : DDR_CTL_179 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_12:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_179;
  union                                            /* Offset=0x02D0 : DDR_CTL_180 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_12:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_180;
  union                                            /* Offset=0x02D4 : DDR_CTL_181 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_13:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_181;
  union                                            /* Offset=0x02D8 : DDR_CTL_182 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_13:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_182;
  union                                            /* Offset=0x02DC : DDR_CTL_183 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_14:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_183;
  union                                            /* Offset=0x02E0 : DDR_CTL_184 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_14:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_184;
  union                                            /* Offset=0x02E4 : DDR_CTL_185 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_START_ADDR_15:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_185;
  union                                            /* Offset=0x02E8 : DDR_CTL_186 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_END_ADDR_15:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_186;
  union                                            /* Offset=0x02EC : DDR_CTL_187 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_0:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_187;
  union                                            /* Offset=0x02F0 : DDR_CTL_188 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_0:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_188;
  union                                            /* Offset=0x02F4 : DDR_CTL_189 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_1:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_189;
  union                                            /* Offset=0x02F8 : DDR_CTL_190 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_1:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_190;
  union                                            /* Offset=0x02FC : DDR_CTL_191 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_2:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_191;
  union                                            /* Offset=0x0300 : DDR_CTL_192 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_2:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_192;
  union                                            /* Offset=0x0304 : DDR_CTL_193 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_3:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_193;
  union                                            /* Offset=0x0308 : DDR_CTL_194 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_3:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_194;
  union                                            /* Offset=0x030C : DDR_CTL_195 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_4:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_195;
  union                                            /* Offset=0x0310 : DDR_CTL_196 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_4:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_196;
  union                                            /* Offset=0x0314 : DDR_CTL_197 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_5:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_197;
  union                                            /* Offset=0x0318 : DDR_CTL_198 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_5:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_198;
  union                                            /* Offset=0x031C : DDR_CTL_199 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_6:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_199;
  union                                            /* Offset=0x0320 : DDR_CTL_200 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_6:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_200;
  union                                            /* Offset=0x0324 : DDR_CTL_201 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_7:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_201;
  union                                            /* Offset=0x0328 : DDR_CTL_202 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_7:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_202;
  union                                            /* Offset=0x032C : DDR_CTL_203 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_8:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_203;
  union                                            /* Offset=0x0330 : DDR_CTL_204 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_8:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_204;
  union                                            /* Offset=0x0334 : DDR_CTL_205 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_9:18;                       /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_205;
  union                                            /* Offset=0x0338 : DDR_CTL_206 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_9:18;                         /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_206;
  union                                            /* Offset=0x033C : DDR_CTL_207 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_10:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_207;
  union                                            /* Offset=0x0340 : DDR_CTL_208 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_10:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_208;
  union                                            /* Offset=0x0344 : DDR_CTL_209 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_11:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_209;
  union                                            /* Offset=0x0348 : DDR_CTL_210 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_11:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_210;
  union                                            /* Offset=0x034C : DDR_CTL_211 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_12:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_211;
  union                                            /* Offset=0x0350 : DDR_CTL_212 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_12:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_212;
  union                                            /* Offset=0x0354 : DDR_CTL_213 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_13:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_213;
  union                                            /* Offset=0x0358 : DDR_CTL_214 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_13:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_214;
  union                                            /* Offset=0x035C : DDR_CTL_215 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_14:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_215;
  union                                            /* Offset=0x0360 : DDR_CTL_216 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_14:18;                        /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_216;
  union                                            /* Offset=0x0364 : DDR_CTL_217 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_START_ADDR_15:18;                      /* [17:0] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_217;
  union                                            /* Offset=0x0368 : DDR_CTL_218 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_END_ADDR_15:18;                        /* [17:0] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_0:2;                   /* [25:24] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } DDR_CTL_218;
  union                                            /* Offset=0x036C : DDR_CTL_219 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_0:16;             /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_0:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_219;
  union                                            /* Offset=0x0370 : DDR_CTL_220 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_0:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_0:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_1:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_220;
  union                                            /* Offset=0x0374 : DDR_CTL_221 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_1:16;             /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_1:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_221;
  union                                            /* Offset=0x0378 : DDR_CTL_222 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_1:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_1:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_2:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_222;
  union                                            /* Offset=0x037C : DDR_CTL_223 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_2:16;             /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_2:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_223;
  union                                            /* Offset=0x0380 : DDR_CTL_224 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_2:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_2:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_3:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_224;
  union                                            /* Offset=0x0384 : DDR_CTL_225 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_3:16;             /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_3:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_225;
  union                                            /* Offset=0x0388 : DDR_CTL_226 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_3:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_3:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_4:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_226;
  union                                            /* Offset=0x038C : DDR_CTL_227 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_4:16;             /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_4:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_227;
  union                                            /* Offset=0x0390 : DDR_CTL_228 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_4:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_4:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_5:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_228;
  union                                            /* Offset=0x0394 : DDR_CTL_229 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_5:16;             /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_5:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_229;
  union                                            /* Offset=0x0398 : DDR_CTL_230 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_5:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_5:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_6:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_230;
  union                                            /* Offset=0x039C : DDR_CTL_231 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_6:16;             /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_6:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_231;
  union                                            /* Offset=0x03A0 : DDR_CTL_232 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_6:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_6:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_7:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_232;
  union                                            /* Offset=0x03A4 : DDR_CTL_233 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_7:16;             /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_7:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_233;
  union                                            /* Offset=0x03A8 : DDR_CTL_234 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_7:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_7:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_8:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_234;
  union                                            /* Offset=0x03AC : DDR_CTL_235 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_8:16;             /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_8:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_235;
  union                                            /* Offset=0x03B0 : DDR_CTL_236 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_8:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_8:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_9:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_236;
  union                                            /* Offset=0x03B4 : DDR_CTL_237 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_9:16;             /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_9:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_237;
  union                                            /* Offset=0x03B8 : DDR_CTL_238 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_9:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_9:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_10:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_238;
  union                                            /* Offset=0x03BC : DDR_CTL_239 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_10:16;            /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_10:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_239;
  union                                            /* Offset=0x03C0 : DDR_CTL_240 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_10:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_10:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_11:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_240;
  union                                            /* Offset=0x03C4 : DDR_CTL_241 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_11:16;            /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_11:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_241;
  union                                            /* Offset=0x03C8 : DDR_CTL_242 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_11:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_11:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_12:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_242;
  union                                            /* Offset=0x03CC : DDR_CTL_243 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_12:16;            /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_12:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_243;
  union                                            /* Offset=0x03D0 : DDR_CTL_244 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_12:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_12:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_13:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_244;
  union                                            /* Offset=0x03D4 : DDR_CTL_245 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_13:16;            /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_13:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_245;
  union                                            /* Offset=0x03D8 : DDR_CTL_246 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_13:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_13:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_14:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_246;
  union                                            /* Offset=0x03DC : DDR_CTL_247 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_14:16;            /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_14:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_247;
  union                                            /* Offset=0x03E0 : DDR_CTL_248 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_14:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_14:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI0_RANGE_PROT_BITS_15:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_248;
  union                                            /* Offset=0x03E4 : DDR_CTL_249 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_15:16;            /* [15:0] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_15:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_249;
  union                                            /* Offset=0x03E8 : DDR_CTL_250 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_RANGE_RID_CHECK_BITS_ID_LOOKUP_15:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI0_RANGE_WID_CHECK_BITS_ID_LOOKUP_15:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_0:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_250;
  union                                            /* Offset=0x03EC : DDR_CTL_251 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_0:16;             /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_0:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_251;
  union                                            /* Offset=0x03F0 : DDR_CTL_252 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_0:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_0:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_1:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_252;
  union                                            /* Offset=0x03F4 : DDR_CTL_253 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_1:16;             /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_1:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_253;
  union                                            /* Offset=0x03F8 : DDR_CTL_254 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_1:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_1:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_2:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_254;
  union                                            /* Offset=0x03FC : DDR_CTL_255 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_2:16;             /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_2:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_255;
  union                                            /* Offset=0x0400 : DDR_CTL_256 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_2:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_2:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_3:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_256;
  union                                            /* Offset=0x0404 : DDR_CTL_257 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_3:16;             /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_3:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_257;
  union                                            /* Offset=0x0408 : DDR_CTL_258 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_3:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_3:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_4:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_258;
  union                                            /* Offset=0x040C : DDR_CTL_259 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_4:16;             /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_4:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_259;
  union                                            /* Offset=0x0410 : DDR_CTL_260 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_4:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_4:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_5:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_260;
  union                                            /* Offset=0x0414 : DDR_CTL_261 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_5:16;             /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_5:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_261;
  union                                            /* Offset=0x0418 : DDR_CTL_262 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_5:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_5:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_6:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_262;
  union                                            /* Offset=0x041C : DDR_CTL_263 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_6:16;             /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_6:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_263;
  union                                            /* Offset=0x0420 : DDR_CTL_264 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_6:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_6:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_7:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_264;
  union                                            /* Offset=0x0424 : DDR_CTL_265 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_7:16;             /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_7:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_265;
  union                                            /* Offset=0x0428 : DDR_CTL_266 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_7:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_7:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_8:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_266;
  union                                            /* Offset=0x042C : DDR_CTL_267 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_8:16;             /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_8:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_267;
  union                                            /* Offset=0x0430 : DDR_CTL_268 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_8:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_8:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_9:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_268;
  union                                            /* Offset=0x0434 : DDR_CTL_269 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_9:16;             /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_9:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_269;
  union                                            /* Offset=0x0438 : DDR_CTL_270 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_9:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_9:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_10:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_270;
  union                                            /* Offset=0x043C : DDR_CTL_271 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_10:16;            /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_10:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_271;
  union                                            /* Offset=0x0440 : DDR_CTL_272 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_10:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_10:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_11:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_272;
  union                                            /* Offset=0x0444 : DDR_CTL_273 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_11:16;            /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_11:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_273;
  union                                            /* Offset=0x0448 : DDR_CTL_274 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_11:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_11:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_12:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_274;
  union                                            /* Offset=0x044C : DDR_CTL_275 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_12:16;            /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_12:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_275;
  union                                            /* Offset=0x0450 : DDR_CTL_276 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_12:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_12:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_13:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_276;
  union                                            /* Offset=0x0454 : DDR_CTL_277 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_13:16;            /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_13:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_277;
  union                                            /* Offset=0x0458 : DDR_CTL_278 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_13:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_13:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_14:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_278;
  union                                            /* Offset=0x045C : DDR_CTL_279 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_14:16;            /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_14:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_279;
  union                                            /* Offset=0x0460 : DDR_CTL_280 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_14:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_14:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI1_RANGE_PROT_BITS_15:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_280;
  union                                            /* Offset=0x0464 : DDR_CTL_281 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_15:16;            /* [15:0] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_15:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_281;
  union                                            /* Offset=0x0468 : DDR_CTL_282 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI1_RANGE_RID_CHECK_BITS_ID_LOOKUP_15:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI1_RANGE_WID_CHECK_BITS_ID_LOOKUP_15:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_0:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_282;
  union                                            /* Offset=0x046C : DDR_CTL_283 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_0:16;             /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_0:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_283;
  union                                            /* Offset=0x0470 : DDR_CTL_284 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_0:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_0:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_1:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_284;
  union                                            /* Offset=0x0474 : DDR_CTL_285 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_1:16;             /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_1:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_285;
  union                                            /* Offset=0x0478 : DDR_CTL_286 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_1:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_1:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_2:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_286;
  union                                            /* Offset=0x047C : DDR_CTL_287 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_2:16;             /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_2:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_287;
  union                                            /* Offset=0x0480 : DDR_CTL_288 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_2:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_2:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_3:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_288;
  union                                            /* Offset=0x0484 : DDR_CTL_289 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_3:16;             /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_3:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_289;
  union                                            /* Offset=0x0488 : DDR_CTL_290 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_3:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_3:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_4:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_290;
  union                                            /* Offset=0x048C : DDR_CTL_291 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_4:16;             /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_4:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_291;
  union                                            /* Offset=0x0490 : DDR_CTL_292 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_4:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_4:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_5:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_292;
  union                                            /* Offset=0x0494 : DDR_CTL_293 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_5:16;             /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_5:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_293;
  union                                            /* Offset=0x0498 : DDR_CTL_294 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_5:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_5:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_6:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_294;
  union                                            /* Offset=0x049C : DDR_CTL_295 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_6:16;             /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_6:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_295;
  union                                            /* Offset=0x04A0 : DDR_CTL_296 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_6:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_6:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_7:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_296;
  union                                            /* Offset=0x04A4 : DDR_CTL_297 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_7:16;             /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_7:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_297;
  union                                            /* Offset=0x04A8 : DDR_CTL_298 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_7:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_7:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_8:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_298;
  union                                            /* Offset=0x04AC : DDR_CTL_299 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_8:16;             /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_8:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_299;
  union                                            /* Offset=0x04B0 : DDR_CTL_300 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_8:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_8:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_9:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_300;
  union                                            /* Offset=0x04B4 : DDR_CTL_301 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_9:16;             /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_9:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_301;
  union                                            /* Offset=0x04B8 : DDR_CTL_302 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_9:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_9:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_10:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_302;
  union                                            /* Offset=0x04BC : DDR_CTL_303 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_10:16;            /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_10:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_303;
  union                                            /* Offset=0x04C0 : DDR_CTL_304 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_10:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_10:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_11:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_304;
  union                                            /* Offset=0x04C4 : DDR_CTL_305 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_11:16;            /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_11:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_305;
  union                                            /* Offset=0x04C8 : DDR_CTL_306 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_11:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_11:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_12:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_306;
  union                                            /* Offset=0x04CC : DDR_CTL_307 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_12:16;            /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_12:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_307;
  union                                            /* Offset=0x04D0 : DDR_CTL_308 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_12:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_12:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_13:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_308;
  union                                            /* Offset=0x04D4 : DDR_CTL_309 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_13:16;            /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_13:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_309;
  union                                            /* Offset=0x04D8 : DDR_CTL_310 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_13:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_13:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_14:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_310;
  union                                            /* Offset=0x04DC : DDR_CTL_311 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_14:16;            /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_14:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_311;
  union                                            /* Offset=0x04E0 : DDR_CTL_312 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_14:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_14:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI2_RANGE_PROT_BITS_15:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_312;
  union                                            /* Offset=0x04E4 : DDR_CTL_313 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_15:16;            /* [15:0] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_15:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_313;
  union                                            /* Offset=0x04E8 : DDR_CTL_314 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI2_RANGE_RID_CHECK_BITS_ID_LOOKUP_15:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI2_RANGE_WID_CHECK_BITS_ID_LOOKUP_15:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_0:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_314;
  union                                            /* Offset=0x04EC : DDR_CTL_315 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_0:16;             /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_0:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_315;
  union                                            /* Offset=0x04F0 : DDR_CTL_316 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_0:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_0:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_1:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_316;
  union                                            /* Offset=0x04F4 : DDR_CTL_317 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_1:16;             /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_1:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_317;
  union                                            /* Offset=0x04F8 : DDR_CTL_318 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_1:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_1:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_2:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_318;
  union                                            /* Offset=0x04FC : DDR_CTL_319 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_2:16;             /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_2:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_319;
  union                                            /* Offset=0x0500 : DDR_CTL_320 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_2:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_2:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_3:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_320;
  union                                            /* Offset=0x0504 : DDR_CTL_321 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_3:16;             /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_3:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_321;
  union                                            /* Offset=0x0508 : DDR_CTL_322 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_3:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_3:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_4:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_322;
  union                                            /* Offset=0x050C : DDR_CTL_323 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_4:16;             /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_4:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_323;
  union                                            /* Offset=0x0510 : DDR_CTL_324 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_4:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_4:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_5:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_324;
  union                                            /* Offset=0x0514 : DDR_CTL_325 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_5:16;             /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_5:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_325;
  union                                            /* Offset=0x0518 : DDR_CTL_326 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_5:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_5:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_6:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_326;
  union                                            /* Offset=0x051C : DDR_CTL_327 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_6:16;             /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_6:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_327;
  union                                            /* Offset=0x0520 : DDR_CTL_328 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_6:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_6:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_7:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_328;
  union                                            /* Offset=0x0524 : DDR_CTL_329 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_7:16;             /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_7:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_329;
  union                                            /* Offset=0x0528 : DDR_CTL_330 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_7:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_7:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_8:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_330;
  union                                            /* Offset=0x052C : DDR_CTL_331 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_8:16;             /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_8:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_331;
  union                                            /* Offset=0x0530 : DDR_CTL_332 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_8:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_8:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_9:2;                   /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_332;
  union                                            /* Offset=0x0534 : DDR_CTL_333 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_9:16;             /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_9:16;             /* [31:16] */
    } BIT;
  } DDR_CTL_333;
  union                                            /* Offset=0x0538 : DDR_CTL_334 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_9:4;    /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_9:4;    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_10:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_334;
  union                                            /* Offset=0x053C : DDR_CTL_335 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_10:16;            /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_10:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_335;
  union                                            /* Offset=0x0540 : DDR_CTL_336 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_10:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_10:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_11:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_336;
  union                                            /* Offset=0x0544 : DDR_CTL_337 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_11:16;            /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_11:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_337;
  union                                            /* Offset=0x0548 : DDR_CTL_338 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_11:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_11:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_12:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_338;
  union                                            /* Offset=0x054C : DDR_CTL_339 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_12:16;            /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_12:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_339;
  union                                            /* Offset=0x0550 : DDR_CTL_340 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_12:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_12:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_13:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_340;
  union                                            /* Offset=0x0554 : DDR_CTL_341 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_13:16;            /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_13:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_341;
  union                                            /* Offset=0x0558 : DDR_CTL_342 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_13:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_13:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_14:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_342;
  union                                            /* Offset=0x055C : DDR_CTL_343 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_14:16;            /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_14:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_343;
  union                                            /* Offset=0x0560 : DDR_CTL_344 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_14:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_14:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   AXI3_RANGE_PROT_BITS_15:2;                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } DDR_CTL_344;
  union                                            /* Offset=0x0564 : DDR_CTL_345 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_15:16;            /* [15:0] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_15:16;            /* [31:16] */
    } BIT;
  } DDR_CTL_345;
  union                                            /* Offset=0x0568 : DDR_CTL_346 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_RANGE_RID_CHECK_BITS_ID_LOOKUP_15:4;   /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AXI3_RANGE_WID_CHECK_BITS_ID_LOOKUP_15:4;   /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   ARB_CMD_Q_THRESHOLD:3;                      /* [18:16] */
      __IO unsigned long   :5;                                         /* [23:19] */
      __IO unsigned long   AXI0_BDW:7;                                 /* [30:24] */
    } BIT;
  } DDR_CTL_346;
  union                                            /* Offset=0x056C : DDR_CTL_347 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_BDW_OVFLOW:1;                          /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __I  unsigned long   AXI0_CURRENT_BDW:7;                         /* [14:8] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   AXI1_BDW:7;                                 /* [22:16] */
      __IO unsigned long   :1;                                         /* [23] */
      __IO unsigned long   AXI1_BDW_OVFLOW:1;                          /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_347;
  union                                            /* Offset=0x0570 : DDR_CTL_348 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   AXI1_CURRENT_BDW:7;                         /* [6:0] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   AXI2_BDW:7;                                 /* [14:8] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   AXI2_BDW_OVFLOW:1;                          /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __I  unsigned long   AXI2_CURRENT_BDW:7;                         /* [30:24] */
    } BIT;
  } DDR_CTL_348;
  union                                            /* Offset=0x0574 : DDR_CTL_349 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI3_BDW:7;                                 /* [6:0] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   AXI3_BDW_OVFLOW:1;                          /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __I  unsigned long   AXI3_CURRENT_BDW:7;                         /* [22:16] */
      __IO unsigned long   :1;                                         /* [23] */
      __I  unsigned long   CKE_STATUS:2;                               /* [25:24] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } DDR_CTL_349;
  union                                            /* Offset=0x0578 : DDR_CTL_350 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   MEM_RST_VALID:1;                            /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   DLL_RST_DELAY:16;                           /* [23:8] */
      __IO unsigned long   DLL_RST_ADJ_DLY:8;                          /* [31:24] */
    } BIT;
  } DDR_CTL_350;
  union                                            /* Offset=0x057C : DDR_CTL_351 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   TDFI_PHY_WRLAT:6;                           /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __I  unsigned long   UPDATE_ERROR_STATUS:7;                      /* [14:8] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   TDFI_PHY_RDLAT:6;                           /* [21:16] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __I  unsigned long   TDFI_RDDATA_EN:6;                           /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } DDR_CTL_351;
  union                                            /* Offset=0x0580 : DDR_CTL_352 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DRAM_CLK_DISABLE:2;                         /* [1:0] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __I  unsigned long   TDFI_CTRLUPD_MIN:4;                         /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   TDFI_CTRLUPD_MAX:14;                        /* [29:16] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } DDR_CTL_352;
  union                                            /* Offset=0x0584 : DDR_CTL_353 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_PHYUPD_TYPE0:16;                       /* [15:0] */
      __IO unsigned long   TDFI_PHYUPD_TYPE1:16;                       /* [31:16] */
    } BIT;
  } DDR_CTL_353;
  union                                            /* Offset=0x0588 : DDR_CTL_354 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_PHYUPD_TYPE2:16;                       /* [15:0] */
      __IO unsigned long   TDFI_PHYUPD_TYPE3:16;                       /* [31:16] */
    } BIT;
  } DDR_CTL_354;
  union                                            /* Offset=0x058C : DDR_CTL_355 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_PHYUPD_RESP:14;                        /* [13:0] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } DDR_CTL_355;
  union                                            /* Offset=0x0590 : DDR_CTL_356 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_CTRLUPD_INTERVAL:32;                   /* [31:0] */
    } BIT;
  } DDR_CTL_356;
  union                                            /* Offset=0x0594 : DDR_CTL_357 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLAT_ADJ:6;                                /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   WRLAT_ADJ:6;                                /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   TDFI_CTRL_DELAY:4;                          /* [19:16] */
      __IO unsigned long   :4;                                         /* [23:20] */
      __IO unsigned long   TDFI_DRAM_CLK_DISABLE:4;                    /* [27:24] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } DDR_CTL_357;
  union                                            /* Offset=0x0598 : DDR_CTL_358 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_DRAM_CLK_ENABLE:4;                     /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   TDFI_WRLVL_EN:8;                            /* [15:8] */
      __IO unsigned long   TDFI_WRLVL_WW:10;                           /* [25:16] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } DDR_CTL_358;
  union                                            /* Offset=0x059C : DDR_CTL_359 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_WRLVL_RESP:32;                         /* [31:0] */
    } BIT;
  } DDR_CTL_359;
  union                                            /* Offset=0x05A0 : DDR_CTL_360 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_WRLVL_MAX:32;                          /* [31:0] */
    } BIT;
  } DDR_CTL_360;
  union                                            /* Offset=0x05A4 : DDR_CTL_361 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DFI_WRLVL_MAX_DELAY:16;                     /* [15:0] */
      __IO unsigned long   TDFI_WRLVL_DLL:8;                           /* [23:16] */
      __IO unsigned long   TDFI_WRLVL_RESPLAT:8;                       /* [31:24] */
    } BIT;
  } DDR_CTL_361;
  union                                            /* Offset=0x05A8 : DDR_CTL_362 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_WRLVL_LOAD:8;                          /* [7:0] */
      __IO unsigned long   TDFI_RDLVL_EN:8;                            /* [15:8] */
      __IO unsigned long   TDFI_RDLVL_DLL:8;                           /* [23:16] */
      __IO unsigned long   TDFI_RDLVL_LOAD:8;                          /* [31:24] */
    } BIT;
  } DDR_CTL_362;
  union                                            /* Offset=0x05AC : DDR_CTL_363 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_RDLVL_RESPLAT:8;                       /* [7:0] */
      __IO unsigned long   RDLVL_MAX_DELAY:16;                         /* [23:8] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } DDR_CTL_363;
  union                                            /* Offset=0x05B0 : DDR_CTL_364 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_GATE_MAX_DELAY:16;                    /* [15:0] */
      __IO unsigned long   TDFI_RDLVL_RR:10;                           /* [25:16] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } DDR_CTL_364;
  union                                            /* Offset=0x05B4 : DDR_CTL_365 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_RDLVL_RESP:32;                         /* [31:0] */
    } BIT;
  } DDR_CTL_365;
  union                                            /* Offset=0x05B8 : DDR_CTL_366 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_RESP_MASK:20;                         /* [19:0] */
      __IO unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } DDR_CTL_366;
  union                                            /* Offset=0x05BC : DDR_CTL_367 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_GATE_RESP_MASK:20;                    /* [19:0] */
      __IO unsigned long   :4;                                         /* [23:20] */
      __IO unsigned long   RDLVL_EN:1;                                 /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_367;
  union                                            /* Offset=0x05C0 : DDR_CTL_368 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_GATE_EN:1;                            /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   RDLVL_GATE_PREAMBLE_CHECK_EN:1;             /* [8] */
      __IO unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } DDR_CTL_368;
  union                                            /* Offset=0x05C4 : DDR_CTL_369 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_RDLVL_MAX:32;                          /* [31:0] */
    } BIT;
  } DDR_CTL_369;
  union                                            /* Offset=0x05C8 : DDR_CTL_370 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_DQ_0_COUNT:4;                         /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   RDLVL_GATE_DQ_0_COUNT:4;                    /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __I  unsigned long   RDLVL_ERROR_STATUS:14;                      /* [29:16] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } DDR_CTL_370;
  union                                            /* Offset=0x05CC : DDR_CTL_371 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RDLVL_INTERVAL:16;                          /* [15:0] */
      __IO unsigned long   RDLVL_GATE_INTERVAL:16;                     /* [31:16] */
    } BIT;
  } DDR_CTL_371;
  union                                            /* Offset=0x05D0 : DDR_CTL_372 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDFI_PHY_WRDATA:3;                          /* [2:0] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __I  unsigned long   MEMCD_RMODW_FIFO_DEPTH:8;                   /* [15:8] */
      __I  unsigned long   MEMCD_RMODW_FIFO_PTR_WIDTH:8;               /* [23:16] */
      __IO unsigned long   OPTIMAL_RMODW_EN:1;                         /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_372;
  union                                            /* Offset=0x05D4 : DDR_CTL_373 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   res0:1;                                     /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   res1:1;                                     /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __IO unsigned long   res2:5;                                     /* [20:16] */
      __IO unsigned long   :3;                                         /* [23:21] */
      __IO unsigned long   res3:1;                                     /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_373;
  union                                            /* Offset=0x05D8 : DDR_CTL_374 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AXI0_ALL_STROBES_USED_ENABLE:1;             /* [0] */
      __IO unsigned long   :7;                                         /* [7:1] */
      __IO unsigned long   AXI1_ALL_STROBES_USED_ENABLE:1;             /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __IO unsigned long   AXI2_ALL_STROBES_USED_ENABLE:1;             /* [16] */
      __IO unsigned long   :7;                                         /* [23:17] */
      __IO unsigned long   AXI3_ALL_STROBES_USED_ENABLE:1;             /* [24] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } DDR_CTL_374;
} DDRC_Type;
#endif  /* End of __DDRC_SFR__DEFINE_HEADER__ */
