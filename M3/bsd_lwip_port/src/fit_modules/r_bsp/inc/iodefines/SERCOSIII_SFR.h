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
 **       for RZN1 SERCOSIII
 **
 **       revision 0.20 (2.Nov.2017)
 **
 **********************************************************************************************************************/
#ifndef __SERCOSIII_SFR__DEFINE_HEADER__
#define __SERCOSIII_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : SERCOSIII
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : IDR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Release:5;                                  /* [4:0] */
      __I  unsigned long   Version:5;                                  /* [9:5] */
      __I  unsigned long   Testversion:3;                              /* [12:10] */
      __I  unsigned long   DeviceType:3;                               /* [15:13] */
      __I  unsigned long   S3FrameType:16;                             /* [31:16] */
    } BIT;
  } IDR;
  union                                            /* Offset=0x0004 : GCSFR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SR:1;                                       /* [0] */
      __IO unsigned long   PHYReset:1;                                 /* [1] */
      __IO unsigned long   BCastRed:1;                                 /* [2] */
      __IO unsigned long   BCastDis:1;                                 /* [3] */
      __IO unsigned long   DescriptorFeedback:1;                       /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   Line_break_sensitivity:4;                   /* [11:8] */
      __IO unsigned long   :3;                                         /* [14:12] */
      __IO unsigned long   Line_bread_mode:1;                          /* [15] */
      __I  unsigned long   Size_of_memory_banks:4;                     /* [19:16] */
      __IO unsigned long   :4;                                         /* [23:20] */
      __I  unsigned long   HardwareVersionBus:8;                       /* [31:24] */
    } BIT;
  } GCSFR;
  union                                            /* Offset=0x0008 : IER0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IE:32;                                      /* [31:0] */
    } BIT;
  } IER0;
  char                     wk_000C[0x0004];
  union                                            /* Offset=0x0010 : IMR0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IM:32;                                      /* [31:0] */
    } BIT;
  } IMR0;
  char                     wk_0014[0x0004];
  union                                            /* Offset=0x0018 : IRR0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IR:32;                                      /* [31:0] */
    } BIT;
  } IRR0;
  char                     wk_001C[0x0004];
  union                                            /* Offset=0x0020 : DFCSR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Topology_Port:2;                            /* [1:0] */
      __IO unsigned long   State_of_Inactive_Port:2;                   /* [3:2] */
      __IO unsigned long   Topology_Primary_Secondary:2;               /* [5:4] */
      __IO unsigned long   Automatic_topology_detection:1;             /* [6] */
      __IO unsigned long   Topology_Write_Mode:1;                      /* [7] */
      __IO unsigned long   Tx_Enable:1;                                /* [8] */
      __IO unsigned long   Rx_Enable:1;                                /* [9] */
      __IO unsigned long   DisableLengthCtrl:1;                        /* [10] */
      __IO unsigned long   Tx_MDT_Enable:1;                            /* [11] */
      __IO unsigned long   Topology_address_increment:4;               /* [15:12] */
      __I  unsigned long   Port1_Line_Status:1;                        /* [16] */
      __I  unsigned long   Port2_Line_Status:1;                        /* [17] */
      __I  unsigned long   Port1_Link:1;                               /* [18] */
      __I  unsigned long   Port2_Link:1;                               /* [19] */
      __I  unsigned long   Ring_Topology:1;                            /* [20] */
      __I  unsigned long   NRT_Forward:1;                              /* [21] */
      __I  unsigned long   Line_Topology:1;                            /* [22] */
      __I  unsigned long   Swap_Counters:1;                            /* [23] */
      __I  unsigned long   P1_Tx_all_done:1;                           /* [24] */
      __I  unsigned long   P1_Rx_all_done:1;                           /* [25] */
      __I  unsigned long   P2_Tx_all_done:1;                           /* [26] */
      __I  unsigned long   P2_Rx_all_done:1;                           /* [27] */
      __IO unsigned long   :2;                                         /* [29:28] */
      __I  unsigned long   TxEnableFeedback:1;                         /* [30] */
      __I  unsigned long   RxEnableFeedback:1;                         /* [31] */
    } BIT;
  } DFCSR;
  union                                            /* Offset=0x0024 : PHASESR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   MST_Phase:4;                                /* [3:0] */
      __IO unsigned long   :3;                                         /* [6:4] */
      __I  unsigned long   CPS:1;                                      /* [7] */
      __IO unsigned long   :7;                                         /* [14:8] */
      __IO unsigned long   Valid:1;                                    /* [15] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } PHASESR;
  union                                            /* Offset=0x0028 : TGSR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MDT0:1;                                     /* [0] */
      __IO unsigned long   MDT1:1;                                     /* [1] */
      __IO unsigned long   MDT2:1;                                     /* [2] */
      __IO unsigned long   MDT3:1;                                     /* [3] */
      __IO unsigned long   AT0:1;                                      /* [4] */
      __IO unsigned long   AT1:1;                                      /* [5] */
      __IO unsigned long   AT2:1;                                      /* [6] */
      __IO unsigned long   AT3:1;                                      /* [7] */
      __IO unsigned long   MST_valide:1;                               /* [8] */
      __I  unsigned long   Primary_Secondary:1;                        /* [9] */
      __IO unsigned long   MST_window_error:1;                         /* [10] */
      __IO unsigned long   MST_miss:1;                                 /* [11] */
      __IO unsigned long   MST_double_miss:1;                          /* [12] */
      __IO unsigned long   AT0_misss:1;                                /* [13] */
      __IO unsigned long   :10;                                        /* [23:14] */
      __I  unsigned long   Cycle_count:3;                              /* [26:24] */
      __I  unsigned long   CycCnt_valid:1;                             /* [27] */
      __I  unsigned long   First_MST:1;                                /* [28] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } TGSR1;
  union                                            /* Offset=0x002C : TGSR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MDT0:1;                                     /* [0] */
      __IO unsigned long   MDT1:1;                                     /* [1] */
      __IO unsigned long   MDT2:1;                                     /* [2] */
      __IO unsigned long   MDT3:1;                                     /* [3] */
      __IO unsigned long   AT0:1;                                      /* [4] */
      __IO unsigned long   AT1:1;                                      /* [5] */
      __IO unsigned long   AT2:1;                                      /* [6] */
      __IO unsigned long   AT3:1;                                      /* [7] */
      __IO unsigned long   MST_valide:1;                               /* [8] */
      __I  unsigned long   Primary_Secondary:1;                        /* [9] */
      __IO unsigned long   MST_window_error:1;                         /* [10] */
      __IO unsigned long   MST_miss:1;                                 /* [11] */
      __IO unsigned long   MST_double_miss:1;                          /* [12] */
      __IO unsigned long   AT0_misss:1;                                /* [13] */
      __IO unsigned long   :10;                                        /* [23:14] */
      __I  unsigned long   Cycle_count:3;                              /* [26:24] */
      __I  unsigned long   CycCnt_valid:1;                             /* [27] */
      __I  unsigned long   First_MST:1;                                /* [28] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } TGSR2;
  union                                            /* Offset=0x0030 : DESCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                                         /* [1:0] */
      __IO unsigned long   Rx_IDXTBL_Offset:11;                        /* [12:2] */
      __IO unsigned long   :5;                                         /* [17:13] */
      __IO unsigned long   Tx_IDXTBL_Offset:11;                        /* [28:18] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } DESCR;
  union                                            /* Offset=0x0034 : STRBR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TCNT:26;                                    /* [25:0] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } STRBR;
  union                                            /* Offset=0x0038 : TCSR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ET0:1;                                      /* [0] */
      __IO unsigned long   ET1_2:1;                                    /* [1] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   ET3:1;                                      /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   CON_En:1;                                   /* [8] */
      __IO unsigned long   CON_Pol:1;                                  /* [9] */
      __IO unsigned long   CONOE:1;                                    /* [10] */
      __IO unsigned long   :1;                                         /* [11] */
      __IO unsigned long   DivClk_mode:1;                              /* [12] */
      __IO unsigned long   DivClkPol:1;                                /* [13] */
      __IO unsigned long   DivOD:1;                                    /* [14] */
      __IO unsigned long   TimeSync_Enable:1;                          /* [15] */
      __IO unsigned long   P1_MST_Dis:1;                               /* [16] */
      __IO unsigned long   P2_MST_Dis:1;                               /* [17] */
      __IO unsigned long   :13;                                        /* [30:18] */
      __IO unsigned long   SysTimeUpdate:1;                            /* [31] */
    } BIT;
  } TCSR;
  union                                            /* Offset=0x003C : TRDLY */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Ringdelay:20;                               /* [19:0] */
      __IO unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } TRDLY;
  union                                            /* Offset=0x0040 : TDMST1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Time_Delay_MST:20;                          /* [19:0] */
      __IO unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } TDMST1;
  union                                            /* Offset=0x0044 : TDMST2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Time_Delay_MST:20;                          /* [19:0] */
      __IO unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } TDMST2;
  union                                            /* Offset=0x0048 : SCR1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Sync_Count:20;                              /* [19:0] */
      __I  unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } SCR1;
  union                                            /* Offset=0x004C : SCR2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Sync_Count:20;                              /* [19:0] */
      __I  unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } SCR2;
  union                                            /* Offset=0x0050 : SVCCSR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SVC_enable:1;                               /* [0] */
      __IO unsigned long   Port_select:1;                              /* [1] */
      __IO unsigned long   MDT_select:2;                               /* [3:2] */
      __IO unsigned long   :3;                                         /* [6:4] */
      __IO unsigned long   Process_start:1;                            /* [7] */
      __IO unsigned long   Process_error:1;                            /* [8] */
      __IO unsigned long   SVC_Busy:1;                                 /* [9] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } SVCCSR;
  union                                            /* Offset=0x0054 : DTDIVCLK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DTDIVCLK:26;                                /* [25:0] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } DTDIVCLK;
  union                                            /* Offset=0x0058 : TDIV_NDIVCLK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDIVCLK:24;                                 /* [23:0] */
      __IO unsigned long   NDIVCLK:8;                                  /* [31:24] */
    } BIT;
  } TDIV_NDIVCLK;
  union                                            /* Offset=0x005C : S3LED */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Color_1:2;                                  /* [1:0] */
      __IO unsigned long   :2;                                         /* [3:2] */
      __IO unsigned long   Color_2:2;                                  /* [5:4] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   Color_3:2;                                  /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   Color_4:2;                                  /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   CycSplit:3;                                 /* [18:16] */
      __IO unsigned long   :1;                                         /* [19] */
      __IO unsigned long   flash_2Hz:1;                                /* [20] */
      __IO unsigned long   CycSkip:2;                                  /* [22:21] */
      __IO unsigned long   :1;                                         /* [23] */
      __IO unsigned long   Color_5:2;                                  /* [25:24] */
      __IO unsigned long   :2;                                         /* [27:26] */
      __IO unsigned long   Color_6:2;                                  /* [29:28] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } S3LED;
  char                     wk_0060[0x0008];
  union                                            /* Offset=0x0068 : WDCSR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   magic_pattern:16;                           /* [15:0] */
      __IO unsigned long   active:1;                                   /* [16] */
      __IO unsigned long   alarm:1;                                    /* [17] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } WDCSR;
  union                                            /* Offset=0x006C : WDCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   reset_count:16;                             /* [15:0] */
      __I  unsigned long   actual_count:16;                            /* [31:16] */
    } BIT;
  } WDCNT;
  union                                            /* Offset=0x0070 : SFCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FrameNumber1:2;                             /* [1:0] */
      __IO unsigned long   :2;                                         /* [3:2] */
      __IO unsigned long   PortSelect1:1;                              /* [4] */
      __IO unsigned long   FrameType1:1;                               /* [5] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   FrameNumber2:2;                             /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   PortSelect2:1;                              /* [12] */
      __IO unsigned long   Frame_type2:1;                              /* [13] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } SFCR;
  union                                            /* Offset=0x0074 : MIICSR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MDC_P1:1;                                   /* [0] */
      __IO unsigned long   MDIO_P1:1;                                  /* [1] */
      __IO unsigned long   MDIO_En_P1:1;                               /* [2] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __IO unsigned long   MDC_P2:1;                                   /* [8] */
      __IO unsigned long   MDIO_P2:1;                                  /* [9] */
      __IO unsigned long   MDIO_En_P2:1;                               /* [10] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } MIICSR;
  union                                            /* Offset=0x0078 : DBGOCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TS1:5;                                      /* [4:0] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   TS2:5;                                      /* [12:8] */
      __IO unsigned long   :19;                                        /* [31:13] */
    } BIT;
  } DBGOCR;
  union                                            /* Offset=0x007C : SEQCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SEQCNT_P1:16;                               /* [15:0] */
      __IO unsigned long   SEQCNT_P2:16;                               /* [31:16] */
    } BIT;
  } SEQCNT;
  union                                            /* Offset=0x0080 : MAC1P1_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   B5:8;                                       /* [7:0] */
      __IO unsigned long   B4:8;                                       /* [15:8] */
      __IO unsigned long   B3:8;                                       /* [23:16] */
      __IO unsigned long   B2:8;                                       /* [31:24] */
    } BIT;
  } MAC1P1_0;
  union                                            /* Offset=0x0084 : MAC1P1_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   B1:8;                                       /* [7:0] */
      __IO unsigned long   B0:8;                                       /* [15:8] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MAC1P1_1;
  char                     wk_0088[0x0008];
  union                                            /* Offset=0x0090 : IPCSR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IPTxEn:1;                                   /* [0] */
      __IO unsigned long   IPRxEn:1;                                   /* [1] */
      __IO unsigned long   S3FrameFilter:1;                            /* [2] */
      __IO unsigned long   BroadcastDisable:1;                         /* [3] */
      __IO unsigned long   MulticastDisable:1;                         /* [4] */
      __IO unsigned long   ColBufDisable:1;                            /* [5] */
      __IO unsigned long   Promiscuous:1;                              /* [6] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   IPRxRdyIntEn:1;                             /* [8] */
      __IO unsigned long   IPRxBufFullIntEn:1;                         /* [9] */
      __IO unsigned long   IPTxBufRdyIntEn:1;                          /* [10] */
      __IO unsigned long   IPTxBufEmptyIntEn:1;                        /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __I  unsigned long   IPRxRdy:1;                                  /* [16] */
      __I  unsigned long   IPRxBufFull:1;                              /* [17] */
      __I  unsigned long   IPTxBufRdy:1;                               /* [18] */
      __I  unsigned long   IPTxBufEmpty:1;                             /* [19] */
      __IO unsigned long   :11;                                        /* [30:20] */
      __I  unsigned long   Link:1;                                     /* [31] */
    } BIT;
  } IPCSR1;
  union                                            /* Offset=0x0094 : IPCSR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IPTxEn:1;                                   /* [0] */
      __IO unsigned long   IPRxEn:1;                                   /* [1] */
      __IO unsigned long   S3FrameFilter:1;                            /* [2] */
      __IO unsigned long   BroadcastDisable:1;                         /* [3] */
      __IO unsigned long   MulticastDisable:1;                         /* [4] */
      __IO unsigned long   ColBufDisable:1;                            /* [5] */
      __IO unsigned long   Promiscuous:1;                              /* [6] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   IPRxRdyIntEn:1;                             /* [8] */
      __IO unsigned long   IPRxBufFullIntEn:1;                         /* [9] */
      __IO unsigned long   IPTxBufRdyIntEn:1;                          /* [10] */
      __IO unsigned long   IPTxBufEmptyIntEn:1;                        /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __I  unsigned long   IPRxRdy:1;                                  /* [16] */
      __I  unsigned long   IPRxBufFull:1;                              /* [17] */
      __I  unsigned long   IPTxBufRdy:1;                               /* [18] */
      __I  unsigned long   IPTxBufEmpty:1;                             /* [19] */
      __IO unsigned long   :11;                                        /* [30:20] */
      __I  unsigned long   Link:1;                                     /* [31] */
    } BIT;
  } IPCSR2;
  union                                            /* Offset=0x0098 : IPRRS1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Ram_segment_First:16;                       /* [15:0] */
      __IO unsigned long   Ram_segment_Last:16;                        /* [31:16] */
    } BIT;
  } IPRRS1;
  union                                            /* Offset=0x009C : IPRRS2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Ram_segment_First:16;                       /* [15:0] */
      __IO unsigned long   Ram_segment_Last:16;                        /* [31:16] */
    } BIT;
  } IPRRS2;
  union                                            /* Offset=0x00A0 : IPRXS1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Ram_segment_address:16;                     /* [15:0] */
      __IO unsigned long   Data_length:11;                             /* [26:16] */
      __IO unsigned long   Status:5;                                   /* [31:27] */
    } BIT;
  } IPRXS1;
  union                                            /* Offset=0x00A4 : IPRXS2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Ram_segment_address:16;                     /* [15:0] */
      __IO unsigned long   Data_length:11;                             /* [26:16] */
      __IO unsigned long   Status:5;                                   /* [31:27] */
    } BIT;
  } IPRXS2;
  union                                            /* Offset=0x00A8 : IPTXS1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Ram_segment_address:16;                     /* [15:0] */
      __IO unsigned long   Data_length:11;                             /* [26:16] */
      __IO unsigned long   :1;                                         /* [27] */
      __IO unsigned long   Count:3;                                    /* [30:28] */
    } BIT;
  } IPTXS1;
  union                                            /* Offset=0x00AC : IPTXS2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Ram_segment_address:16;                     /* [15:0] */
      __IO unsigned long   Data_length:11;                             /* [26:16] */
      __IO unsigned long   :1;                                         /* [27] */
      __IO unsigned long   Count:3;                                    /* [30:28] */
    } BIT;
  } IPTXS2;
  union                                            /* Offset=0x00B0 : IPLASTFL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   length:11;                                  /* [10:0] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } IPLASTFL;
  char                     wk_00B4[0x000C];
  union                                            /* Offset=0x00C0 : IPFRXOK */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesReceivedOK_1:16;                     /* [15:0] */
      __I  unsigned long   aFramesReceivedOK_2:16;                     /* [31:16] */
    } BIT;
  } IPFRXOK;
  union                                            /* Offset=0x00C4 : IPFTXOK */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesTransmittedOK_1:16;                  /* [15:0] */
      __I  unsigned long   aFramesTransmittedOK_2:16;                  /* [31:16] */
    } BIT;
  } IPFTXOK;
  union                                            /* Offset=0x00C8 : IPFCSERR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFCSErrors_Port_1:16;                       /* [15:0] */
      __I  unsigned long   aFCSErrors_Port_2:16;                       /* [31:16] */
    } BIT;
  } IPFCSERR;
  union                                            /* Offset=0x00CC : IPALGNERR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFrameErrors_Port_1:16;                     /* [15:0] */
      __I  unsigned long   aFrameErrors_Port_2:16;                     /* [31:16] */
    } BIT;
  } IPALGNERR;
  union                                            /* Offset=0x00D0 : IPDISRXB */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aDiscardResRxBuf_Port_1:16;                 /* [15:0] */
      __I  unsigned long   aDiscardResRxBuf_Port_2:16;                 /* [31:16] */
    } BIT;
  } IPDISRXB;
  union                                            /* Offset=0x00D4 : IPDISCLB */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aDiscardResColBuf_Port_1:16;                /* [15:0] */
      __I  unsigned long   aDiscardResColBuf_Port_2:16;                /* [31:16] */
    } BIT;
  } IPDISCLB;
  union                                            /* Offset=0x00D8 : IPCHVIOL */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aIPChannelViolation_Port_1:16;              /* [15:0] */
      __I  unsigned long   aIPChannelViolation_Port_2:16;              /* [31:16] */
    } BIT;
  } IPCHVIOL;
  union                                            /* Offset=0x00DC : aSercosErrorCount */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aSercosErrorCount_Port_1:16;                /* [15:0] */
      __I  unsigned long   aSercosErrorCount_Port_2:16;                /* [31:16] */
    } BIT;
  } aSercosErrorCount;
  union                                            /* Offset=0x00E0 : MSTLMAX */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   value:16;                                   /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MSTLMAX;
  union                                            /* Offset=0x00E4 : MSTLSUM */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   value:16;                                   /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MSTLSUM;
  union                                            /* Offset=0x00E8 : MSTLACT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   value:16;                                   /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MSTLACT;
  char                     wk_00EC[0x0014];
  union                                            /* Offset=0x0100 : TMDSCL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Event_TCNT_Value:27;                        /* [26:0] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } TMDSCL;
  union                                            /* Offset=0x0104 : TMDSCU */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SCC_Value:8;                                /* [7:0] */
      __IO unsigned long   :8;                                         /* [15:8] */
      __IO unsigned long   SCC_Select:2;                               /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   Event_type:4;                               /* [27:24] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } TMDSCU;
  union                                            /* Offset=0x0108 : TMDSCSEL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TMDSCSEL:32;                                /* [31:0] */
    } BIT;
  } TMDSCSEL;
  char                     wk_010C[0x0004];
  union                                            /* Offset=0x0110 : PTMDSCL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Event_TCNT_Value:27;                        /* [26:0] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } PTMDSCL;
  union                                            /* Offset=0x0114 : PTMDSCU */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SCC_Value:8;                                /* [7:0] */
      __IO unsigned long   :8;                                         /* [15:8] */
      __IO unsigned long   SCC_Select:2;                               /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   Event_type:4;                               /* [27:24] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } PTMDSCU;
  union                                            /* Offset=0x0118 : PTMDSCSEL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PTMDSCSEL:32;                               /* [31:0] */
    } BIT;
  } PTMDSCSEL;
  char                     wk_011C[0x0014];
  union                                            /* Offset=0x0130 : STNS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Nanoseconds:30;                             /* [29:0] */
      __I  unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } STNS;
  union                                            /* Offset=0x0134 : STSEC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Seconds:32;                                 /* [31:0] */
    } BIT;
  } STSEC;
  union                                            /* Offset=0x0138 : STNSTSR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Nanoseconds:30;                             /* [29:0] */
      __I  unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } STNSTSR;
  union                                            /* Offset=0x013C : STSECTSR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Seconds:32;                                 /* [31:0] */
    } BIT;
  } STSECTSR;
  union                                            /* Offset=0x0140 : SCCAB */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SccMaxA:8;                                  /* [7:0] */
      __IO unsigned long   SccMaxB:8;                                  /* [15:8] */
      __I  unsigned long   SccValueA:8;                                /* [23:16] */
      __I  unsigned long   SccValueB:8;                                /* [31:24] */
    } BIT;
  } SCCAB;
  char                     wk_0144[0x000C];
  union                                            /* Offset=0x0150 : SCCMDT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Maximum_count:14;                           /* [13:0] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __I  unsigned long   Actual_counter:14;                          /* [29:16] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } SCCMDT;
  char                     wk_0154[0x002C];
  union                                            /* Offset=0x0180 : RXBUF0_P1A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF0_P1A:32;                              /* [31:0] */
    } BIT;
  } RXBUF0_P1A;
  union                                            /* Offset=0x0184 : RXBUF1_P1A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF1_P1A:32;                              /* [31:0] */
    } BIT;
  } RXBUF1_P1A;
  union                                            /* Offset=0x0188 : RXBUF2_P1A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF2_P1A:32;                              /* [31:0] */
    } BIT;
  } RXBUF2_P1A;
  char                     wk_018C[0x0004];
  union                                            /* Offset=0x0190 : RXBUF0_P1B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF0_P1B:32;                              /* [31:0] */
    } BIT;
  } RXBUF0_P1B;
  union                                            /* Offset=0x0194 : RXBUF1_P1B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF1_P1B:32;                              /* [31:0] */
    } BIT;
  } RXBUF1_P1B;
  union                                            /* Offset=0x0198 : RXBUF2_P1B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF2_P1B:32;                              /* [31:0] */
    } BIT;
  } RXBUF2_P1B;
  union                                            /* Offset=0x019C : RXBUF_P1SVC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF_P1SVC:32;                             /* [31:0] */
    } BIT;
  } RXBUF_P1SVC;
  union                                            /* Offset=0x01A0 : RXBUF0_P2A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF0_P2A:32;                              /* [31:0] */
    } BIT;
  } RXBUF0_P2A;
  union                                            /* Offset=0x01A4 : RXBUF1_P2A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF1_P2A:32;                              /* [31:0] */
    } BIT;
  } RXBUF1_P2A;
  union                                            /* Offset=0x01A8 : RXBUF2_P2A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF2_P2A:32;                              /* [31:0] */
    } BIT;
  } RXBUF2_P2A;
  char                     wk_01AC[0x0004];
  union                                            /* Offset=0x01B0 : RXBUF0_P2B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF0_P2B:32;                              /* [31:0] */
    } BIT;
  } RXBUF0_P2B;
  union                                            /* Offset=0x01B4 : RXBUF1_P2B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF1_P2B:32;                              /* [31:0] */
    } BIT;
  } RXBUF1_P2B;
  union                                            /* Offset=0x01B8 : RXBUF2_P2B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF2_P2B:32;                              /* [31:0] */
    } BIT;
  } RXBUF2_P2B;
  union                                            /* Offset=0x01BC : RXBUF_P2SVC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXBUF_P2SVC:32;                             /* [31:0] */
    } BIT;
  } RXBUF_P2SVC;
  union                                            /* Offset=0x01C0 : TXBUF0_A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXBUF0_A:32;                                /* [31:0] */
    } BIT;
  } TXBUF0_A;
  union                                            /* Offset=0x01C4 : TXBUF1_A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXBUF1_A:32;                                /* [31:0] */
    } BIT;
  } TXBUF1_A;
  union                                            /* Offset=0x01C8 : TXBUF2_A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXBUF2_A:32;                                /* [31:0] */
    } BIT;
  } TXBUF2_A;
  union                                            /* Offset=0x01CC : TXBUF3_A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXBUF3_A:32;                                /* [31:0] */
    } BIT;
  } TXBUF3_A;
  union                                            /* Offset=0x01D0 : TXBUF0_B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXBUF0_B:32;                                /* [31:0] */
    } BIT;
  } TXBUF0_B;
  union                                            /* Offset=0x01D4 : TXBUF1_B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXBUF1_B:32;                                /* [31:0] */
    } BIT;
  } TXBUF1_B;
  union                                            /* Offset=0x01D8 : TXBUF2_B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXBUF2_B:32;                                /* [31:0] */
    } BIT;
  } TXBUF2_B;
  union                                            /* Offset=0x01DC : TXBUF3_B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXBUF3_B:32;                                /* [31:0] */
    } BIT;
  } TXBUF3_B;
  char                     wk_01E0[0x0010];
  union                                            /* Offset=0x01F0 : TXBUF_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXBUF_P1:32;                                /* [31:0] */
    } BIT;
  } TXBUF_P1;
  union                                            /* Offset=0x01F4 : TXBUF_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXBUF_P2:32;                                /* [31:0] */
    } BIT;
  } TXBUF_P2;
  char                     wk_01F8[0x0004];
  union                                            /* Offset=0x01FC : TXBUF_SVC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXBUF_SVC:32;                               /* [31:0] */
    } BIT;
  } TXBUF_SVC;
  union                                            /* Offset=0x0200 : RXBUFCSR_A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Buffer_Count:2;                             /* [1:0] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __I  unsigned long   RxBuf_Port_1:2;                             /* [17:16] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __I  unsigned long   Port_1_New_Data:1;                          /* [20] */
      __I  unsigned long   Port_1_Overflow:1;                          /* [21] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __I  unsigned long   RxBuf_Port_2:2;                             /* [25:24] */
      __IO unsigned long   :2;                                         /* [27:26] */
      __I  unsigned long   Port_2_New_Data:1;                          /* [28] */
      __I  unsigned long   Port_2_Overflow:1;                          /* [29] */
      __IO unsigned long   :1;                                         /* [30] */
      __IO unsigned long   RxRequest:1;                                /* [31] */
    } BIT;
  } RXBUFCSR_A;
  union                                            /* Offset=0x0204 : RXBUFTV_A */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Port_1_MDT0:1;                              /* [0] */
      __I  unsigned long   Port_1_MDT1:1;                              /* [1] */
      __I  unsigned long   Port_1_MDT2:1;                              /* [2] */
      __I  unsigned long   Port_1_MDT3:1;                              /* [3] */
      __I  unsigned long   :4;                                         /* [7:4] */
      __I  unsigned long   Port_1_AT0:1;                               /* [8] */
      __I  unsigned long   Port_1_AT1:1;                               /* [9] */
      __I  unsigned long   Port_1_AT2:1;                               /* [10] */
      __I  unsigned long   Port_1_AT3:1;                               /* [11] */
      __I  unsigned long   :4;                                         /* [15:12] */
      __I  unsigned long   Port_2_MDT0:1;                              /* [16] */
      __I  unsigned long   Port_2_MDT1:1;                              /* [17] */
      __I  unsigned long   Port_2_MDT2:1;                              /* [18] */
      __I  unsigned long   Port_2_MDT3:1;                              /* [19] */
      __I  unsigned long   :4;                                         /* [23:20] */
      __I  unsigned long   Port_2_AT0:1;                               /* [24] */
      __I  unsigned long   Port_2_AT1:1;                               /* [25] */
      __I  unsigned long   Port_2_AT2:1;                               /* [26] */
      __I  unsigned long   Port_2_AT3:1;                               /* [27] */
      __I  unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } RXBUFTV_A;
  union                                            /* Offset=0x0208 : RXBUFTR_A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MDT0_required:1;                            /* [0] */
      __IO unsigned long   MDT1_required:1;                            /* [1] */
      __IO unsigned long   MDT2_required:1;                            /* [2] */
      __IO unsigned long   MDT3_required:1;                            /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AT0_required:1;                             /* [8] */
      __IO unsigned long   AT1_required:1;                             /* [9] */
      __IO unsigned long   AT2_required:1;                             /* [10] */
      __IO unsigned long   AT3_required:1;                             /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } RXBUFTR_A;
  union                                            /* Offset=0x020C : TXBUFCSR_A */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Buffer_Count:2;                             /* [1:0] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   TxBuf:2;                                    /* [17:16] */
      __IO unsigned long   :13;                                        /* [30:18] */
      __IO unsigned long   TxRequest:1;                                /* [31] */
    } BIT;
  } TXBUFCSR_A;
  union                                            /* Offset=0x0210 : RXBUFCSR_B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Buffer_Count:2;                             /* [1:0] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __I  unsigned long   RxBuf_Port_1:2;                             /* [17:16] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __I  unsigned long   Port_1_New_Data:1;                          /* [20] */
      __I  unsigned long   Port_1_Overflow:1;                          /* [21] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __I  unsigned long   RxBuf_Port_2:2;                             /* [25:24] */
      __IO unsigned long   :2;                                         /* [27:26] */
      __I  unsigned long   Port_2_New_Data:1;                          /* [28] */
      __I  unsigned long   Port_2_Overflow:1;                          /* [29] */
      __IO unsigned long   :1;                                         /* [30] */
      __IO unsigned long   RxRequest:1;                                /* [31] */
    } BIT;
  } RXBUFCSR_B;
  union                                            /* Offset=0x0214 : RXBUFTV_B */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Port_1_MDT0:1;                              /* [0] */
      __I  unsigned long   Port_1_MDT1:1;                              /* [1] */
      __I  unsigned long   Port_1_MDT2:1;                              /* [2] */
      __I  unsigned long   Port_1_MDT3:1;                              /* [3] */
      __I  unsigned long   :4;                                         /* [7:4] */
      __I  unsigned long   Port_1_AT0:1;                               /* [8] */
      __I  unsigned long   Port_1_AT1:1;                               /* [9] */
      __I  unsigned long   Port_1_AT2:1;                               /* [10] */
      __I  unsigned long   Port_1_AT3:1;                               /* [11] */
      __I  unsigned long   :4;                                         /* [15:12] */
      __I  unsigned long   Port_2_MDT0:1;                              /* [16] */
      __I  unsigned long   Port_2_MDT1:1;                              /* [17] */
      __I  unsigned long   Port_2_MDT2:1;                              /* [18] */
      __I  unsigned long   Port_2_MDT3:1;                              /* [19] */
      __I  unsigned long   :4;                                         /* [23:20] */
      __I  unsigned long   Port_2_AT0:1;                               /* [24] */
      __I  unsigned long   Port_2_AT1:1;                               /* [25] */
      __I  unsigned long   Port_2_AT2:1;                               /* [26] */
      __I  unsigned long   Port_2_AT3:1;                               /* [27] */
      __I  unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } RXBUFTV_B;
  union                                            /* Offset=0x0218 : RXBUFTR_B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MDT0_required:1;                            /* [0] */
      __IO unsigned long   MDT1_required:1;                            /* [1] */
      __IO unsigned long   MDT2_required:1;                            /* [2] */
      __IO unsigned long   MDT3_required:1;                            /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   AT0_required:1;                             /* [8] */
      __IO unsigned long   AT1_required:1;                             /* [9] */
      __IO unsigned long   AT2_required:1;                             /* [10] */
      __IO unsigned long   AT3_required:1;                             /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } RXBUFTR_B;
  union                                            /* Offset=0x021C : TXBUFCSR_B */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Buffer_Count:2;                             /* [1:0] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   TxBuf:2;                                    /* [17:16] */
      __IO unsigned long   :13;                                        /* [30:18] */
      __IO unsigned long   TxRequest:1;                                /* [31] */
    } BIT;
  } TXBUFCSR_B;
} SERCOSIII_Type;
#endif  /* End of __SERCOSIII_SFR__DEFINE_HEADER__ */
