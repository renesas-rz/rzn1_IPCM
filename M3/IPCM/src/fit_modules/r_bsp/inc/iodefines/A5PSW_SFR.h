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
 **       for RZN1 A5PSW
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __A5PSW_SFR__DEFINE_HEADER__
#define __A5PSW_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : A5PSW
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : REVISION */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   REV:32;                                     /* [31:0] */
    } BIT;
  } REVISION;
  union                                            /* Offset=0x0004 : SCRATCH */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SCRATCH:32;                                 /* [31:0] */
    } BIT;
  } SCRATCH;
  union                                            /* Offset=0x0008 : PORT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXENA:5;                                    /* [4:0] */
      __IO unsigned long   :11;                                        /* [15:5] */
      __IO unsigned long   RXENA:5;                                    /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } PORT_ENA;
  union                                            /* Offset=0x000C : UCAST_DEFAULT_MASK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   UCASTDM:5;                                  /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } UCAST_DEFAULT_MASK;
  union                                            /* Offset=0x0010 : VLAN_VERIFY */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   VLANVERI:5;                                 /* [4:0] */
      __IO unsigned long   :11;                                        /* [15:5] */
      __IO unsigned long   VLANDISC:5;                                 /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } VLAN_VERIFY;
  union                                            /* Offset=0x0014 : BCAST_DEFAULT_MASK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BCASTDM:5;                                  /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } BCAST_DEFAULT_MASK;
  union                                            /* Offset=0x0018 : MCAST_DEFAULT_MASK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MCASTDM:5;                                  /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } MCAST_DEFAULT_MASK;
  union                                            /* Offset=0x001C : INPUT_LEARN_BLOCK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   BLOCKEN:5;                                  /* [4:0] */
      __IO unsigned long   :11;                                        /* [15:5] */
      __IO unsigned long   LEARNDIS:5;                                 /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } INPUT_LEARN_BLOCK;
  union                                            /* Offset=0x0020 : MGMT_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Port:4;                                     /* [3:0] */
      __IO unsigned long   :1;                                         /* [4] */
      __IO unsigned long   message_transmitted:1;                      /* [5] */
      __IO unsigned long   enable:1;                                   /* [6] */
      __IO unsigned long   discard:1;                                  /* [7] */
      __IO unsigned long   :5;                                         /* [12:8] */
      __IO unsigned long   priority:3;                                 /* [15:13] */
      __IO unsigned long   portmask:5;                                 /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } MGMT_CONFIG;
  union                                            /* Offset=0x0024 : MODE_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   Options:8;                                  /* [7:0] */
      __IO unsigned long   Cut_Through_Enable:5;                       /* [12:8] */
      __IO unsigned long   :18;                                        /* [30:13] */
      __IO unsigned long   StatsReset:1;                               /* [31] */
    } BIT;
  } MODE_CONFIG;
  union                                            /* Offset=0x0028 : VLAN_IN_MODE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   P0VLANINMD:2;                               /* [1:0] */
      __IO unsigned long   P1VLANINMD:2;                               /* [3:2] */
      __IO unsigned long   P2VLANINMD:2;                               /* [5:4] */
      __IO unsigned long   P3VLANINMD:2;                               /* [7:6] */
      __IO unsigned long   P4VLANINMD:2;                               /* [9:8] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } VLAN_IN_MODE;
  union                                            /* Offset=0x002C : VLAN_OUT_MODE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   P0VLANOUTMD:2;                              /* [1:0] */
      __IO unsigned long   P1VLANOUTMD:2;                              /* [3:2] */
      __IO unsigned long   P2VLANOUTMD:2;                              /* [5:4] */
      __IO unsigned long   P3VLANOUTMD:2;                              /* [7:6] */
      __IO unsigned long   P4VLANOUTMD:2;                              /* [9:8] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } VLAN_OUT_MODE;
  union                                            /* Offset=0x0030 : VLAN_IN_MODE_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   VLANINMDEN:5;                               /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } VLAN_IN_MODE_ENA;
  union                                            /* Offset=0x0034 : VLAN_TAG_ID */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VLANTAGID:16;                               /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } VLAN_TAG_ID;
  union                                            /* Offset=0x0038 : BCAST_STORM_LIMIT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TMOUT:16;                                   /* [15:0] */
      __IO unsigned long   BCASTLIMIT:16;                              /* [31:16] */
    } BIT;
  } BCAST_STORM_LIMIT;
  union                                            /* Offset=0x003C : MCAST_STORM_LIMIT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :16;                                        /* [15:0] */
      __IO unsigned long   MCASTLIMIT:16;                              /* [31:16] */
    } BIT;
  } MCAST_STORM_LIMIT;
  union                                            /* Offset=0x0040 : MIRROR_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Mirror_Port:4;                              /* [3:0] */
      __IO unsigned long   mirror_enable:1;                            /* [4] */
      __IO unsigned long   ing_map_enable:1;                           /* [5] */
      __IO unsigned long   eg_map_enable:1;                            /* [6] */
      __IO unsigned long   ing_sa_match:1;                             /* [7] */
      __IO unsigned long   ing_da_match:1;                             /* [8] */
      __IO unsigned long   eg_sa_match:1;                              /* [9] */
      __IO unsigned long   eg_da_match:1;                              /* [10] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } MIRROR_CONTROL;
  union                                            /* Offset=0x0044 : MIRROR_EG_MAP */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EMAP:5;                                     /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } MIRROR_EG_MAP;
  union                                            /* Offset=0x0048 : MIRROR_ING_MAP */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IMAP:5;                                     /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } MIRROR_ING_MAP;
  union                                            /* Offset=0x004C : MIRROR_ISRC_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ISRC:32;                                    /* [31:0] */
    } BIT;
  } MIRROR_ISRC_0;
  union                                            /* Offset=0x0050 : MIRROR_ISRC_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ISRC:16;                                    /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MIRROR_ISRC_1;
  union                                            /* Offset=0x0054 : MIRROR_IDST_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IDST:32;                                    /* [31:0] */
    } BIT;
  } MIRROR_IDST_0;
  union                                            /* Offset=0x0058 : MIRROR_IDST_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IDST:16;                                    /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MIRROR_IDST_1;
  union                                            /* Offset=0x005C : MIRROR_ESRC_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ESRC:32;                                    /* [31:0] */
    } BIT;
  } MIRROR_ESRC_0;
  union                                            /* Offset=0x0060 : MIRROR_ESRC_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ESRC:16;                                    /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MIRROR_ESRC_1;
  union                                            /* Offset=0x0064 : MIRROR_EDST_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EDST:32;                                    /* [31:0] */
    } BIT;
  } MIRROR_EDST_0;
  union                                            /* Offset=0x0068 : MIRROR_EDST_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EDST:16;                                    /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MIRROR_EDST_1;
  union                                            /* Offset=0x006C : MIRROR_CNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CNT:8;                                      /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } MIRROR_CNT;
  char                     wk_0070[0x0018];
  union                                            /* Offset=0x0088 : QMGR_ST_MINCELLS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   M_CELLS_MIN:11;                             /* [10:0] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } QMGR_ST_MINCELLS;
  char                     wk_008C[0x0008];
  union                                            /* Offset=0x0094 : QMGR_RED_MIN4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CFGRED_MINTH4:32;                           /* [31:0] */
    } BIT;
  } QMGR_RED_MIN4;
  union                                            /* Offset=0x0098 : QMGR_RED_MAX4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CFGRED_MAXTH4:32;                           /* [31:0] */
    } BIT;
  } QMGR_RED_MAX4;
  union                                            /* Offset=0x009C : QMGR_RED_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   QUEUE_RED_EN:4;                             /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   GACTIVITY_EN:1;                             /* [8] */
      __IO unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } QMGR_RED_CONFIG;
  union                                            /* Offset=0x00A0 : IMC_STATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   cells_available:24;                         /* [23:0] */
      __I  unsigned long   cf_error:1;                                 /* [24] */
      __I  unsigned long   de_error:1;                                 /* [25] */
      __I  unsigned long   de_init:1;                                  /* [26] */
      __I  unsigned long   mem_full:1;                                 /* [27] */
      __I  unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } IMC_STATUS;
  union                                            /* Offset=0x00A4 : IMC_ERR_FULL */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ipc_err_full:5;                             /* [4:0] */
      __I  unsigned long   :11;                                        /* [15:5] */
      __I  unsigned long   ipc_err_trunc:5;                            /* [20:16] */
      __I  unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } IMC_ERR_FULL;
  union                                            /* Offset=0x00A8 : IMC_ERR_IFACE */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ipc_err_iface:5;                            /* [4:0] */
      __I  unsigned long   :11;                                        /* [15:5] */
      __I  unsigned long   wbuf_oflow:5;                               /* [20:16] */
      __I  unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } IMC_ERR_IFACE;
  union                                            /* Offset=0x00AC : IMC_ERR_QOFLOW */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   op_error:5;                                 /* [4:0] */
      __I  unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } IMC_ERR_QOFLOW;
  union                                            /* Offset=0x00B0 : IMC_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   wfq_enable:1;                               /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IMC_CONFIG;
  char                     wk_00B4[0x000C];
  union                                            /* Offset=0x00C0 : GPARSER0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   mask_value2:8;                              /* [7:0] */
      __IO unsigned long   compare_value:8;                            /* [15:8] */
      __IO unsigned long   offset:6;                                   /* [21:16] */
      __IO unsigned long   :1;                                         /* [22] */
      __IO unsigned long   offset_DA:1;                                /* [23] */
      __IO unsigned long   valid:1;                                    /* [24] */
      __IO unsigned long   skipvlan:1;                                 /* [25] */
      __IO unsigned long   ipdata:1;                                   /* [26] */
      __IO unsigned long   ipprotocol:1;                               /* [27] */
      __IO unsigned long   compare16:1;                                /* [28] */
      __IO unsigned long   offset_plus2:1;                             /* [29] */
      __IO unsigned long   cmp_mask_or:1;                              /* [30] */
    } BIT;
  } GPARSER0;
  union                                            /* Offset=0x00C4 : GPARSER1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   mask_value2:8;                              /* [7:0] */
      __IO unsigned long   compare_value:8;                            /* [15:8] */
      __IO unsigned long   offset:6;                                   /* [21:16] */
      __IO unsigned long   :1;                                         /* [22] */
      __IO unsigned long   offset_DA:1;                                /* [23] */
      __IO unsigned long   valid:1;                                    /* [24] */
      __IO unsigned long   skipvlan:1;                                 /* [25] */
      __IO unsigned long   ipdata:1;                                   /* [26] */
      __IO unsigned long   ipprotocol:1;                               /* [27] */
      __IO unsigned long   compare16:1;                                /* [28] */
      __IO unsigned long   offset_plus2:1;                             /* [29] */
      __IO unsigned long   cmp_mask_or:1;                              /* [30] */
    } BIT;
  } GPARSER1;
  union                                            /* Offset=0x00C8 : GPARSER2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   mask_value2:8;                              /* [7:0] */
      __IO unsigned long   compare_value:8;                            /* [15:8] */
      __IO unsigned long   offset:6;                                   /* [21:16] */
      __IO unsigned long   :1;                                         /* [22] */
      __IO unsigned long   offset_DA:1;                                /* [23] */
      __IO unsigned long   valid:1;                                    /* [24] */
      __IO unsigned long   skipvlan:1;                                 /* [25] */
      __IO unsigned long   ipdata:1;                                   /* [26] */
      __IO unsigned long   ipprotocol:1;                               /* [27] */
      __IO unsigned long   compare16:1;                                /* [28] */
      __IO unsigned long   offset_plus2:1;                             /* [29] */
      __IO unsigned long   cmp_mask_or:1;                              /* [30] */
    } BIT;
  } GPARSER2;
  union                                            /* Offset=0x00CC : GPARSER3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   mask_value2:8;                              /* [7:0] */
      __IO unsigned long   compare_value:8;                            /* [15:8] */
      __IO unsigned long   offset:6;                                   /* [21:16] */
      __IO unsigned long   :1;                                         /* [22] */
      __IO unsigned long   offset_DA:1;                                /* [23] */
      __IO unsigned long   valid:1;                                    /* [24] */
      __IO unsigned long   skipvlan:1;                                 /* [25] */
      __IO unsigned long   ipdata:1;                                   /* [26] */
      __IO unsigned long   ipprotocol:1;                               /* [27] */
      __IO unsigned long   compare16:1;                                /* [28] */
      __IO unsigned long   offset_plus2:1;                             /* [29] */
      __IO unsigned long   cmp_mask_or:1;                              /* [30] */
    } BIT;
  } GPARSER3;
  union                                            /* Offset=0x00D0 : GARITH0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   not_input:4;                                /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   select_match:4;                             /* [11:8] */
      __IO unsigned long   select_arith0:1;                            /* [12] */
      __IO unsigned long   select_arith1:1;                            /* [13] */
      __IO unsigned long   select_arith2:1;                            /* [14] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   operation:1;                                /* [16] */
      __IO unsigned long   result_invert:1;                            /* [17] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __IO unsigned long   snoopmode:2;                                /* [21:20] */
      __IO unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } GARITH0;
  union                                            /* Offset=0x00D4 : GARITH1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   not_input:4;                                /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   select_match:4;                             /* [11:8] */
      __IO unsigned long   select_arith0:1;                            /* [12] */
      __IO unsigned long   select_arith1:1;                            /* [13] */
      __IO unsigned long   select_arith2:1;                            /* [14] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   operation:1;                                /* [16] */
      __IO unsigned long   result_invert:1;                            /* [17] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __IO unsigned long   snoopmode:2;                                /* [21:20] */
      __IO unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } GARITH1;
  union                                            /* Offset=0x00D8 : GARITH2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   not_input:4;                                /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   select_match:4;                             /* [11:8] */
      __IO unsigned long   select_arith0:1;                            /* [12] */
      __IO unsigned long   select_arith1:1;                            /* [13] */
      __IO unsigned long   select_arith2:1;                            /* [14] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   operation:1;                                /* [16] */
      __IO unsigned long   result_invert:1;                            /* [17] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __IO unsigned long   snoopmode:2;                                /* [21:20] */
      __IO unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } GARITH2;
  union                                            /* Offset=0x00DC : GARITH3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   not_input:4;                                /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   select_match:4;                             /* [11:8] */
      __IO unsigned long   select_arith0:1;                            /* [12] */
      __IO unsigned long   select_arith1:1;                            /* [13] */
      __IO unsigned long   select_arith2:1;                            /* [14] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   operation:1;                                /* [16] */
      __IO unsigned long   result_invert:1;                            /* [17] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __IO unsigned long   snoopmode:2;                                /* [21:20] */
      __IO unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } GARITH3;
  union                                            /* Offset=0x00E0 : GPARSER4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   mask_value2:8;                              /* [7:0] */
      __IO unsigned long   compare_value:8;                            /* [15:8] */
      __IO unsigned long   offset:6;                                   /* [21:16] */
      __IO unsigned long   :1;                                         /* [22] */
      __IO unsigned long   offset_DA:1;                                /* [23] */
      __IO unsigned long   valid:1;                                    /* [24] */
      __IO unsigned long   skipvlan:1;                                 /* [25] */
      __IO unsigned long   ipdata:1;                                   /* [26] */
      __IO unsigned long   ipprotocol:1;                               /* [27] */
      __IO unsigned long   compare16:1;                                /* [28] */
      __IO unsigned long   offset_plus2:1;                             /* [29] */
      __IO unsigned long   cmp_mask_or:1;                              /* [30] */
    } BIT;
  } GPARSER4;
  union                                            /* Offset=0x00E4 : GPARSER5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   mask_value2:8;                              /* [7:0] */
      __IO unsigned long   compare_value:8;                            /* [15:8] */
      __IO unsigned long   offset:6;                                   /* [21:16] */
      __IO unsigned long   :1;                                         /* [22] */
      __IO unsigned long   offset_DA:1;                                /* [23] */
      __IO unsigned long   valid:1;                                    /* [24] */
      __IO unsigned long   skipvlan:1;                                 /* [25] */
      __IO unsigned long   ipdata:1;                                   /* [26] */
      __IO unsigned long   ipprotocol:1;                               /* [27] */
      __IO unsigned long   compare16:1;                                /* [28] */
      __IO unsigned long   offset_plus2:1;                             /* [29] */
      __IO unsigned long   cmp_mask_or:1;                              /* [30] */
    } BIT;
  } GPARSER5;
  union                                            /* Offset=0x00E8 : GPARSER6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   mask_value2:8;                              /* [7:0] */
      __IO unsigned long   compare_value:8;                            /* [15:8] */
      __IO unsigned long   offset:6;                                   /* [21:16] */
      __IO unsigned long   :1;                                         /* [22] */
      __IO unsigned long   offset_DA:1;                                /* [23] */
      __IO unsigned long   valid:1;                                    /* [24] */
      __IO unsigned long   skipvlan:1;                                 /* [25] */
      __IO unsigned long   ipdata:1;                                   /* [26] */
      __IO unsigned long   ipprotocol:1;                               /* [27] */
      __IO unsigned long   compare16:1;                                /* [28] */
      __IO unsigned long   offset_plus2:1;                             /* [29] */
      __IO unsigned long   cmp_mask_or:1;                              /* [30] */
    } BIT;
  } GPARSER6;
  union                                            /* Offset=0x00EC : GPARSER7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   mask_value2:8;                              /* [7:0] */
      __IO unsigned long   compare_value:8;                            /* [15:8] */
      __IO unsigned long   offset:6;                                   /* [21:16] */
      __IO unsigned long   :1;                                         /* [22] */
      __IO unsigned long   offset_DA:1;                                /* [23] */
      __IO unsigned long   valid:1;                                    /* [24] */
      __IO unsigned long   skipvlan:1;                                 /* [25] */
      __IO unsigned long   ipdata:1;                                   /* [26] */
      __IO unsigned long   ipprotocol:1;                               /* [27] */
      __IO unsigned long   compare16:1;                                /* [28] */
      __IO unsigned long   offset_plus2:1;                             /* [29] */
      __IO unsigned long   cmp_mask_or:1;                              /* [30] */
    } BIT;
  } GPARSER7;
  union                                            /* Offset=0x00F0 : GARITH4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   not_input:4;                                /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   select_match:4;                             /* [11:8] */
      __IO unsigned long   select_arith0:1;                            /* [12] */
      __IO unsigned long   select_arith1:1;                            /* [13] */
      __IO unsigned long   select_arith2:1;                            /* [14] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   operation:1;                                /* [16] */
      __IO unsigned long   result_invert:1;                            /* [17] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __IO unsigned long   snoopmode:2;                                /* [21:20] */
      __IO unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } GARITH4;
  union                                            /* Offset=0x00F4 : GARITH5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   not_input:4;                                /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   select_match:4;                             /* [11:8] */
      __IO unsigned long   select_arith0:1;                            /* [12] */
      __IO unsigned long   select_arith1:1;                            /* [13] */
      __IO unsigned long   select_arith2:1;                            /* [14] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   operation:1;                                /* [16] */
      __IO unsigned long   result_invert:1;                            /* [17] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __IO unsigned long   snoopmode:2;                                /* [21:20] */
      __IO unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } GARITH5;
  union                                            /* Offset=0x00F8 : GARITH6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   not_input:4;                                /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   select_match:4;                             /* [11:8] */
      __IO unsigned long   select_arith0:1;                            /* [12] */
      __IO unsigned long   select_arith1:1;                            /* [13] */
      __IO unsigned long   select_arith2:1;                            /* [14] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   operation:1;                                /* [16] */
      __IO unsigned long   result_invert:1;                            /* [17] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __IO unsigned long   snoopmode:2;                                /* [21:20] */
      __IO unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } GARITH6;
  union                                            /* Offset=0x00FC : GARITH7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   not_input:4;                                /* [3:0] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   select_match:4;                             /* [11:8] */
      __IO unsigned long   select_arith0:1;                            /* [12] */
      __IO unsigned long   select_arith1:1;                            /* [13] */
      __IO unsigned long   select_arith2:1;                            /* [14] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   operation:1;                                /* [16] */
      __IO unsigned long   result_invert:1;                            /* [17] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __IO unsigned long   snoopmode:2;                                /* [21:20] */
      __IO unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } GARITH7;
  union                                            /* Offset=0x0100 : VLAN_PRIORITY0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRIOIN0:2;                                  /* [1:0] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   PRIOIN1:2;                                  /* [4:3] */
      __IO unsigned long   :1;                                         /* [5] */
      __IO unsigned long   PRIOIN2:2;                                  /* [7:6] */
      __IO unsigned long   :1;                                         /* [8] */
      __IO unsigned long   PRIOIN3:2;                                  /* [10:9] */
      __IO unsigned long   :1;                                         /* [11] */
      __IO unsigned long   PRIOIN4:2;                                  /* [13:12] */
      __IO unsigned long   :1;                                         /* [14] */
      __IO unsigned long   PRIOIN5:2;                                  /* [16:15] */
      __IO unsigned long   :1;                                         /* [17] */
      __IO unsigned long   PRIOIN6:2;                                  /* [19:18] */
      __IO unsigned long   :1;                                         /* [20] */
      __IO unsigned long   PRIOIN7:2;                                  /* [22:21] */
      __IO unsigned long   :9;                                         /* [31:23] */
    } BIT;
  } VLAN_PRIORITY0;
  union                                            /* Offset=0x0104 : VLAN_PRIORITY1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRIOIN0:2;                                  /* [1:0] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   PRIOIN1:2;                                  /* [4:3] */
      __IO unsigned long   :1;                                         /* [5] */
      __IO unsigned long   PRIOIN2:2;                                  /* [7:6] */
      __IO unsigned long   :1;                                         /* [8] */
      __IO unsigned long   PRIOIN3:2;                                  /* [10:9] */
      __IO unsigned long   :1;                                         /* [11] */
      __IO unsigned long   PRIOIN4:2;                                  /* [13:12] */
      __IO unsigned long   :1;                                         /* [14] */
      __IO unsigned long   PRIOIN5:2;                                  /* [16:15] */
      __IO unsigned long   :1;                                         /* [17] */
      __IO unsigned long   PRIOIN6:2;                                  /* [19:18] */
      __IO unsigned long   :1;                                         /* [20] */
      __IO unsigned long   PRIOIN7:2;                                  /* [22:21] */
      __IO unsigned long   :9;                                         /* [31:23] */
    } BIT;
  } VLAN_PRIORITY1;
  union                                            /* Offset=0x0108 : VLAN_PRIORITY2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRIOIN0:2;                                  /* [1:0] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   PRIOIN1:2;                                  /* [4:3] */
      __IO unsigned long   :1;                                         /* [5] */
      __IO unsigned long   PRIOIN2:2;                                  /* [7:6] */
      __IO unsigned long   :1;                                         /* [8] */
      __IO unsigned long   PRIOIN3:2;                                  /* [10:9] */
      __IO unsigned long   :1;                                         /* [11] */
      __IO unsigned long   PRIOIN4:2;                                  /* [13:12] */
      __IO unsigned long   :1;                                         /* [14] */
      __IO unsigned long   PRIOIN5:2;                                  /* [16:15] */
      __IO unsigned long   :1;                                         /* [17] */
      __IO unsigned long   PRIOIN6:2;                                  /* [19:18] */
      __IO unsigned long   :1;                                         /* [20] */
      __IO unsigned long   PRIOIN7:2;                                  /* [22:21] */
      __IO unsigned long   :9;                                         /* [31:23] */
    } BIT;
  } VLAN_PRIORITY2;
  union                                            /* Offset=0x010C : VLAN_PRIORITY3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRIOIN0:2;                                  /* [1:0] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   PRIOIN1:2;                                  /* [4:3] */
      __IO unsigned long   :1;                                         /* [5] */
      __IO unsigned long   PRIOIN2:2;                                  /* [7:6] */
      __IO unsigned long   :1;                                         /* [8] */
      __IO unsigned long   PRIOIN3:2;                                  /* [10:9] */
      __IO unsigned long   :1;                                         /* [11] */
      __IO unsigned long   PRIOIN4:2;                                  /* [13:12] */
      __IO unsigned long   :1;                                         /* [14] */
      __IO unsigned long   PRIOIN5:2;                                  /* [16:15] */
      __IO unsigned long   :1;                                         /* [17] */
      __IO unsigned long   PRIOIN6:2;                                  /* [19:18] */
      __IO unsigned long   :1;                                         /* [20] */
      __IO unsigned long   PRIOIN7:2;                                  /* [22:21] */
      __IO unsigned long   :9;                                         /* [31:23] */
    } BIT;
  } VLAN_PRIORITY3;
  union                                            /* Offset=0x0110 : VLAN_PRIORITY4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRIOIN0:2;                                  /* [1:0] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   PRIOIN1:2;                                  /* [4:3] */
      __IO unsigned long   :1;                                         /* [5] */
      __IO unsigned long   PRIOIN2:2;                                  /* [7:6] */
      __IO unsigned long   :1;                                         /* [8] */
      __IO unsigned long   PRIOIN3:2;                                  /* [10:9] */
      __IO unsigned long   :1;                                         /* [11] */
      __IO unsigned long   PRIOIN4:2;                                  /* [13:12] */
      __IO unsigned long   :1;                                         /* [14] */
      __IO unsigned long   PRIOIN5:2;                                  /* [16:15] */
      __IO unsigned long   :1;                                         /* [17] */
      __IO unsigned long   PRIOIN6:2;                                  /* [19:18] */
      __IO unsigned long   :1;                                         /* [20] */
      __IO unsigned long   PRIOIN7:2;                                  /* [22:21] */
      __IO unsigned long   :9;                                         /* [31:23] */
    } BIT;
  } VLAN_PRIORITY4;
  char                     wk_0114[0x002C];
  union                                            /* Offset=0x0140 : IP_PRIORITY0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Address:8;                                  /* [7:0] */
      __IO unsigned long   IPv6_select:1;                              /* [8] */
      __IO unsigned long   priority:2;                                 /* [10:9] */
      __IO unsigned long   :20;                                        /* [30:11] */
      __IO unsigned long   read:1;                                     /* [31] */
    } BIT;
  } IP_PRIORITY0;
  union                                            /* Offset=0x0144 : IP_PRIORITY1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Address:8;                                  /* [7:0] */
      __IO unsigned long   IPv6_select:1;                              /* [8] */
      __IO unsigned long   priority:2;                                 /* [10:9] */
      __IO unsigned long   :20;                                        /* [30:11] */
      __IO unsigned long   read:1;                                     /* [31] */
    } BIT;
  } IP_PRIORITY1;
  union                                            /* Offset=0x0148 : IP_PRIORITY2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Address:8;                                  /* [7:0] */
      __IO unsigned long   IPv6_select:1;                              /* [8] */
      __IO unsigned long   priority:2;                                 /* [10:9] */
      __IO unsigned long   :20;                                        /* [30:11] */
      __IO unsigned long   read:1;                                     /* [31] */
    } BIT;
  } IP_PRIORITY2;
  union                                            /* Offset=0x014C : IP_PRIORITY3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Address:8;                                  /* [7:0] */
      __IO unsigned long   IPv6_select:1;                              /* [8] */
      __IO unsigned long   priority:2;                                 /* [10:9] */
      __IO unsigned long   :20;                                        /* [30:11] */
      __IO unsigned long   read:1;                                     /* [31] */
    } BIT;
  } IP_PRIORITY3;
  union                                            /* Offset=0x0150 : IP_PRIORITY4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Address:8;                                  /* [7:0] */
      __IO unsigned long   IPv6_select:1;                              /* [8] */
      __IO unsigned long   priority:2;                                 /* [10:9] */
      __IO unsigned long   :20;                                        /* [30:11] */
      __IO unsigned long   read:1;                                     /* [31] */
    } BIT;
  } IP_PRIORITY4;
  char                     wk_0154[0x002C];
  union                                            /* Offset=0x0180 : PRIORITY_CFG0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   VLAN_en:1;                                  /* [0] */
      __IO unsigned long   IP_en:1;                                    /* [1] */
      __IO unsigned long   MAC_en:1;                                   /* [2] */
      __IO unsigned long   TYPE_en:1;                                  /* [3] */
      __IO unsigned long   default_priority:2;                         /* [5:4] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PRIORITY_CFG0;
  union                                            /* Offset=0x0184 : PRIORITY_CFG1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   VLAN_en:1;                                  /* [0] */
      __IO unsigned long   IP_en:1;                                    /* [1] */
      __IO unsigned long   MAC_en:1;                                   /* [2] */
      __IO unsigned long   TYPE_en:1;                                  /* [3] */
      __IO unsigned long   default_priority:2;                         /* [5:4] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PRIORITY_CFG1;
  union                                            /* Offset=0x0188 : PRIORITY_CFG2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   VLAN_en:1;                                  /* [0] */
      __IO unsigned long   IP_en:1;                                    /* [1] */
      __IO unsigned long   MAC_en:1;                                   /* [2] */
      __IO unsigned long   TYPE_en:1;                                  /* [3] */
      __IO unsigned long   default_priority:2;                         /* [5:4] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PRIORITY_CFG2;
  union                                            /* Offset=0x018C : PRIORITY_CFG3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   VLAN_en:1;                                  /* [0] */
      __IO unsigned long   IP_en:1;                                    /* [1] */
      __IO unsigned long   MAC_en:1;                                   /* [2] */
      __IO unsigned long   TYPE_en:1;                                  /* [3] */
      __IO unsigned long   default_priority:2;                         /* [5:4] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PRIORITY_CFG3;
  union                                            /* Offset=0x0190 : PRIORITY_CFG4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   VLAN_en:1;                                  /* [0] */
      __IO unsigned long   IP_en:1;                                    /* [1] */
      __IO unsigned long   MAC_en:1;                                   /* [2] */
      __IO unsigned long   TYPE_en:1;                                  /* [3] */
      __IO unsigned long   default_priority:2;                         /* [5:4] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } PRIORITY_CFG4;
  char                     wk_0194[0x0024];
  union                                            /* Offset=0x01B8 : PRIORITY_TYPE1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   typevalue:16;                               /* [15:0] */
      __IO unsigned long   valid:1;                                    /* [16] */
      __IO unsigned long   priority:2;                                 /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } PRIORITY_TYPE1;
  union                                            /* Offset=0x01BC : PRIORITY_TYPE2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   typevalue:16;                               /* [15:0] */
      __IO unsigned long   valid:1;                                    /* [16] */
      __IO unsigned long   priority:2;                                 /* [18:17] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } PRIORITY_TYPE2;
  union                                            /* Offset=0x01C0 : MGMT_ADDR0_lo */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bpdu_dst_custom:32;                         /* [31:0] */
    } BIT;
  } MGMT_ADDR0_lo;
  union                                            /* Offset=0x01C4 : MGMT_ADDR0_hi */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bpdu_dst_custom:16;                         /* [15:0] */
      __IO unsigned long   MASK8BIT:8;                                 /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } MGMT_ADDR0_hi;
  char                     wk_01C8[0x0038];
  union                                            /* Offset=0x0200 : SYSTEM_TAGINFO0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SYSVLANINFO:16;                             /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } SYSTEM_TAGINFO0;
  union                                            /* Offset=0x0204 : SYSTEM_TAGINFO1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SYSVLANINFO:16;                             /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } SYSTEM_TAGINFO1;
  union                                            /* Offset=0x0208 : SYSTEM_TAGINFO2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SYSVLANINFO:16;                             /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } SYSTEM_TAGINFO2;
  union                                            /* Offset=0x020C : SYSTEM_TAGINFO3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SYSVLANINFO:16;                             /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } SYSTEM_TAGINFO3;
  union                                            /* Offset=0x0210 : SYSTEM_TAGINFO4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SYSVLANINFO:16;                             /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } SYSTEM_TAGINFO4;
  char                     wk_0214[0x002C];
  union                                            /* Offset=0x0240 : AUTH_PORT0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   authorized:1;                               /* [0] */
      __IO unsigned long   controlled_both:1;                          /* [1] */
      __IO unsigned long   EAPOL_enable:1;                             /* [2] */
      __IO unsigned long   guest_enable:1;                             /* [3] */
      __IO unsigned long   BPDU_enable:1;                              /* [4] */
      __IO unsigned long   EAPOL_unicast_enable:1;                     /* [5] */
      __IO unsigned long   :5;                                         /* [10:6] */
      __IO unsigned long   Auto_Change_Unauthorized:1;                 /* [11] */
      __IO unsigned long   EAPOL_port_number:4;                        /* [15:12] */
      __IO unsigned long   guest_mask:5;                               /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } AUTH_PORT0;
  union                                            /* Offset=0x0244 : AUTH_PORT1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   authorized:1;                               /* [0] */
      __IO unsigned long   controlled_both:1;                          /* [1] */
      __IO unsigned long   EAPOL_enable:1;                             /* [2] */
      __IO unsigned long   guest_enable:1;                             /* [3] */
      __IO unsigned long   BPDU_enable:1;                              /* [4] */
      __IO unsigned long   EAPOL_unicast_enable:1;                     /* [5] */
      __IO unsigned long   :5;                                         /* [10:6] */
      __IO unsigned long   Auto_Change_Unauthorized:1;                 /* [11] */
      __IO unsigned long   EAPOL_port_number:4;                        /* [15:12] */
      __IO unsigned long   guest_mask:5;                               /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } AUTH_PORT1;
  union                                            /* Offset=0x0248 : AUTH_PORT2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   authorized:1;                               /* [0] */
      __IO unsigned long   controlled_both:1;                          /* [1] */
      __IO unsigned long   EAPOL_enable:1;                             /* [2] */
      __IO unsigned long   guest_enable:1;                             /* [3] */
      __IO unsigned long   BPDU_enable:1;                              /* [4] */
      __IO unsigned long   EAPOL_unicast_enable:1;                     /* [5] */
      __IO unsigned long   :5;                                         /* [10:6] */
      __IO unsigned long   Auto_Change_Unauthorized:1;                 /* [11] */
      __IO unsigned long   EAPOL_port_number:4;                        /* [15:12] */
      __IO unsigned long   guest_mask:5;                               /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } AUTH_PORT2;
  union                                            /* Offset=0x024C : AUTH_PORT3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   authorized:1;                               /* [0] */
      __IO unsigned long   controlled_both:1;                          /* [1] */
      __IO unsigned long   EAPOL_enable:1;                             /* [2] */
      __IO unsigned long   guest_enable:1;                             /* [3] */
      __IO unsigned long   BPDU_enable:1;                              /* [4] */
      __IO unsigned long   EAPOL_unicast_enable:1;                     /* [5] */
      __IO unsigned long   :5;                                         /* [10:6] */
      __IO unsigned long   Auto_Change_Unauthorized:1;                 /* [11] */
      __IO unsigned long   EAPOL_port_number:4;                        /* [15:12] */
      __IO unsigned long   guest_mask:5;                               /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } AUTH_PORT3;
  union                                            /* Offset=0x0250 : AUTH_PORT4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   authorized:1;                               /* [0] */
      __IO unsigned long   controlled_both:1;                          /* [1] */
      __IO unsigned long   EAPOL_enable:1;                             /* [2] */
      __IO unsigned long   guest_enable:1;                             /* [3] */
      __IO unsigned long   BPDU_enable:1;                              /* [4] */
      __IO unsigned long   EAPOL_unicast_enable:1;                     /* [5] */
      __IO unsigned long   :5;                                         /* [10:6] */
      __IO unsigned long   Auto_Change_Unauthorized:1;                 /* [11] */
      __IO unsigned long   EAPOL_port_number:4;                        /* [15:12] */
      __IO unsigned long   guest_mask:5;                               /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } AUTH_PORT4;
  char                     wk_0254[0x002C];
  union                                            /* Offset=0x0280 : VLAN_RES_TABLE0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE0;
  union                                            /* Offset=0x0284 : VLAN_RES_TABLE1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE1;
  union                                            /* Offset=0x0288 : VLAN_RES_TABLE2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE2;
  union                                            /* Offset=0x028C : VLAN_RES_TABLE3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE3;
  union                                            /* Offset=0x0290 : VLAN_RES_TABLE4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE4;
  union                                            /* Offset=0x0294 : VLAN_RES_TABLE5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE5;
  union                                            /* Offset=0x0298 : VLAN_RES_TABLE6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE6;
  union                                            /* Offset=0x029C : VLAN_RES_TABLE7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE7;
  union                                            /* Offset=0x02A0 : VLAN_RES_TABLE8 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE8;
  union                                            /* Offset=0x02A4 : VLAN_RES_TABLE9 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE9;
  union                                            /* Offset=0x02A8 : VLAN_RES_TABLE10 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE10;
  union                                            /* Offset=0x02AC : VLAN_RES_TABLE11 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE11;
  union                                            /* Offset=0x02B0 : VLAN_RES_TABLE12 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE12;
  union                                            /* Offset=0x02B4 : VLAN_RES_TABLE13 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE13;
  union                                            /* Offset=0x02B8 : VLAN_RES_TABLE14 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE14;
  union                                            /* Offset=0x02BC : VLAN_RES_TABLE15 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE15;
  union                                            /* Offset=0x02C0 : VLAN_RES_TABLE16 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE16;
  union                                            /* Offset=0x02C4 : VLAN_RES_TABLE17 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE17;
  union                                            /* Offset=0x02C8 : VLAN_RES_TABLE18 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE18;
  union                                            /* Offset=0x02CC : VLAN_RES_TABLE19 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE19;
  union                                            /* Offset=0x02D0 : VLAN_RES_TABLE20 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE20;
  union                                            /* Offset=0x02D4 : VLAN_RES_TABLE21 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE21;
  union                                            /* Offset=0x02D8 : VLAN_RES_TABLE22 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE22;
  union                                            /* Offset=0x02DC : VLAN_RES_TABLE23 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE23;
  union                                            /* Offset=0x02E0 : VLAN_RES_TABLE24 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE24;
  union                                            /* Offset=0x02E4 : VLAN_RES_TABLE25 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE25;
  union                                            /* Offset=0x02E8 : VLAN_RES_TABLE26 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE26;
  union                                            /* Offset=0x02EC : VLAN_RES_TABLE27 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE27;
  union                                            /* Offset=0x02F0 : VLAN_RES_TABLE28 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE28;
  union                                            /* Offset=0x02F4 : VLAN_RES_TABLE29 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE29;
  union                                            /* Offset=0x02F8 : VLAN_RES_TABLE30 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE30;
  union                                            /* Offset=0x02FC : VLAN_RES_TABLE31 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Portmask:5;                                 /* [4:0] */
      __IO unsigned long   VLANid:12;                                  /* [16:5] */
      __IO unsigned long   :11;                                        /* [27:17] */
      __IO unsigned long   read_tagmask:1;                             /* [28] */
      __IO unsigned long   write_tagmask:1;                            /* [29] */
      __IO unsigned long   write_portmask:1;                           /* [30] */
    } BIT;
  } VLAN_RES_TABLE31;
  union                                            /* Offset=0x0300 : TOTAL_DISC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TOTAL_DISC:32;                              /* [31:0] */
    } BIT;
  } TOTAL_DISC;
  union                                            /* Offset=0x0304 : TOTAL_BYT_DISC */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TOTAL_BYT_DISC:32;                          /* [31:0] */
    } BIT;
  } TOTAL_BYT_DISC;
  union                                            /* Offset=0x0308 : TOTAL_FRM */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TOTAL_FRM:32;                               /* [31:0] */
    } BIT;
  } TOTAL_FRM;
  union                                            /* Offset=0x030C : TOTAL_BYT_FRM */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TOTAL_BYT_FRM:32;                           /* [31:0] */
    } BIT;
  } TOTAL_BYT_FRM;
  union                                            /* Offset=0x0310 : ODISC0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ODISC0:32;                                  /* [31:0] */
    } BIT;
  } ODISC0;
  union                                            /* Offset=0x0314 : IDISC_VLAN0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_VLAN0:32;                             /* [31:0] */
    } BIT;
  } IDISC_VLAN0;
  union                                            /* Offset=0x0318 : IDISC_UNTAGGED0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_UNTAGGED0:32;                         /* [31:0] */
    } BIT;
  } IDISC_UNTAGGED0;
  union                                            /* Offset=0x031C : IDISC_BLOCKED0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_BLOCKED0:32;                          /* [31:0] */
    } BIT;
  } IDISC_BLOCKED0;
  union                                            /* Offset=0x0320 : ODISC1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ODISC1:32;                                  /* [31:0] */
    } BIT;
  } ODISC1;
  union                                            /* Offset=0x0324 : IDISC_VLAN1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_VLAN1:32;                             /* [31:0] */
    } BIT;
  } IDISC_VLAN1;
  union                                            /* Offset=0x0328 : IDISC_UNTAGGED1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_UNTAGGED1:32;                         /* [31:0] */
    } BIT;
  } IDISC_UNTAGGED1;
  union                                            /* Offset=0x032C : IDISC_BLOCKED1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_BLOCKED1:32;                          /* [31:0] */
    } BIT;
  } IDISC_BLOCKED1;
  union                                            /* Offset=0x0330 : ODISC2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ODISC2:32;                                  /* [31:0] */
    } BIT;
  } ODISC2;
  union                                            /* Offset=0x0334 : IDISC_VLAN2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_VLAN2:32;                             /* [31:0] */
    } BIT;
  } IDISC_VLAN2;
  union                                            /* Offset=0x0338 : IDISC_UNTAGGED2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_UNTAGGED2:32;                         /* [31:0] */
    } BIT;
  } IDISC_UNTAGGED2;
  union                                            /* Offset=0x033C : IDISC_BLOCKED2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_BLOCKED2:32;                          /* [31:0] */
    } BIT;
  } IDISC_BLOCKED2;
  union                                            /* Offset=0x0340 : ODISC3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ODISC3:32;                                  /* [31:0] */
    } BIT;
  } ODISC3;
  union                                            /* Offset=0x0344 : IDISC_VLAN3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_VLAN3:32;                             /* [31:0] */
    } BIT;
  } IDISC_VLAN3;
  union                                            /* Offset=0x0348 : IDISC_UNTAGGED3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_UNTAGGED3:32;                         /* [31:0] */
    } BIT;
  } IDISC_UNTAGGED3;
  union                                            /* Offset=0x034C : IDISC_BLOCKED3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_BLOCKED3:32;                          /* [31:0] */
    } BIT;
  } IDISC_BLOCKED3;
  union                                            /* Offset=0x0350 : ODISC4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ODISC4:32;                                  /* [31:0] */
    } BIT;
  } ODISC4;
  union                                            /* Offset=0x0354 : IDISC_VLAN4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_VLAN4:32;                             /* [31:0] */
    } BIT;
  } IDISC_VLAN4;
  union                                            /* Offset=0x0358 : IDISC_UNTAGGED4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_UNTAGGED4:32;                         /* [31:0] */
    } BIT;
  } IDISC_UNTAGGED4;
  union                                            /* Offset=0x035C : IDISC_BLOCKED4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDISC_BLOCKED4:32;                          /* [31:0] */
    } BIT;
  } IDISC_BLOCKED4;
  char                     wk_0360[0x0060];
  union                                            /* Offset=0x03C0 : IMC_QLEVEL_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Queue0:4;                                   /* [3:0] */
      __I  unsigned long   Queue1:4;                                   /* [7:4] */
      __I  unsigned long   Queue2:4;                                   /* [11:8] */
      __I  unsigned long   Queue3:4;                                   /* [15:12] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } IMC_QLEVEL_P0;
  union                                            /* Offset=0x03C4 : IMC_QLEVEL_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Queue0:4;                                   /* [3:0] */
      __I  unsigned long   Queue1:4;                                   /* [7:4] */
      __I  unsigned long   Queue2:4;                                   /* [11:8] */
      __I  unsigned long   Queue3:4;                                   /* [15:12] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } IMC_QLEVEL_P1;
  union                                            /* Offset=0x03C8 : IMC_QLEVEL_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Queue0:4;                                   /* [3:0] */
      __I  unsigned long   Queue1:4;                                   /* [7:4] */
      __I  unsigned long   Queue2:4;                                   /* [11:8] */
      __I  unsigned long   Queue3:4;                                   /* [15:12] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } IMC_QLEVEL_P2;
  union                                            /* Offset=0x03CC : IMC_QLEVEL_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Queue0:4;                                   /* [3:0] */
      __I  unsigned long   Queue1:4;                                   /* [7:4] */
      __I  unsigned long   Queue2:4;                                   /* [11:8] */
      __I  unsigned long   Queue3:4;                                   /* [15:12] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } IMC_QLEVEL_P3;
  union                                            /* Offset=0x03D0 : IMC_QLEVEL_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   Queue0:4;                                   /* [3:0] */
      __I  unsigned long   Queue1:4;                                   /* [7:4] */
      __I  unsigned long   Queue2:4;                                   /* [11:8] */
      __I  unsigned long   Queue3:4;                                   /* [15:12] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } IMC_QLEVEL_P4;
  char                     wk_03D4[0x002C];
  union                                            /* Offset=0x0400 : LK_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   Enable_Lookup:1;                            /* [0] */
      __IO unsigned long   Enable_Learning:1;                          /* [1] */
      __IO unsigned long   Enable_Aging:1;                             /* [2] */
      __IO unsigned long   Allow_Migration:1;                          /* [3] */
      __IO unsigned long   Discard_Unknown_Destination:1;              /* [4] */
      __IO unsigned long   :1;                                         /* [5] */
      __IO unsigned long   Clear_Table:1;                              /* [6] */
      __IO unsigned long   :9;                                         /* [15:7] */
      __IO unsigned long   Discard_Unknown_Source:5;                   /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } LK_CTRL;
  union                                            /* Offset=0x0404 : LK_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   ageaddress:16;                              /* [15:0] */
      __IO unsigned long   overflows:14;                               /* [29:16] */
      __IO unsigned long   :1;                                         /* [30] */
      __IO unsigned long   learnevent:1;                               /* [31] */
    } BIT;
  } LK_STATUS;
  union                                            /* Offset=0x0408 : LK_ADDR_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   address_mask:13;                            /* [12:0] */
      __IO unsigned long   :9;                                         /* [21:13] */
      __IO unsigned long   CLEAR_DYNAMIC:1;                            /* [22] */
      __IO unsigned long   CLEAR_STATIC:1;                             /* [23] */
      __IO unsigned long   GETLASTNEW:1;                               /* [24] */
      __IO unsigned long   WRITE:1;                                    /* [25] */
      __IO unsigned long   READ:1;                                     /* [26] */
      __IO unsigned long   WAIT_COMPLETE:1;                            /* [27] */
      __IO unsigned long   LOOKUP:1;                                   /* [28] */
      __IO unsigned long   CLEAR:1;                                    /* [29] */
      __IO unsigned long   DELETE_PORT:1;                              /* [30] */
      __IO unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } LK_ADDR_CTRL;
  union                                            /* Offset=0x040C : LK_DATA_LO */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MEMDATA:32;                                 /* [31:0] */
    } BIT;
  } LK_DATA_LO;
  union                                            /* Offset=0x0410 : LK_DATA_HI */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MEMDATA:26;                                 /* [25:0] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } LK_DATA_HI;
  char                     wk_0414[0x0004];
  union                                            /* Offset=0x0418 : LK_LEARNCOUNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   LEARNCOUNT:14;                              /* [13:0] */
      __IO unsigned long   :16;                                        /* [29:14] */
      __IO unsigned long   write_mode:2;                               /* [31:30] */
    } BIT;
  } LK_LEARNCOUNT;
  union                                            /* Offset=0x041C : LK_AGETIME */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   LK_AGETIME:24;                              /* [23:0] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } LK_AGETIME;
  char                     wk_0420[0x0060];
  union                                            /* Offset=0x0480 : MGMT_TAG_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   enable:1;                                   /* [0] */
      __IO unsigned long   all_frames:1;                               /* [1] */
      __IO unsigned long   :2;                                         /* [3:2] */
      __IO unsigned long   enable_type1:1;                             /* [4] */
      __IO unsigned long   enable_type2:1;                             /* [5] */
      __IO unsigned long   :10;                                        /* [15:6] */
      __IO unsigned long   Tagfield:16;                                /* [31:16] */
    } BIT;
  } MGMT_TAG_CONFIG;
  char                     wk_0484[0x0088];
  union                                            /* Offset=0x050C : PEERDELAY0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PEERDELAY0:30;                              /* [29:0] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } PEERDELAY0;
  union                                            /* Offset=0x0510 : PEERDELAY1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PEERDELAY1:30;                              /* [29:0] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } PEERDELAY1;
  union                                            /* Offset=0x0514 : PEERDELAY2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PEERDELAY2:30;                              /* [29:0] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } PEERDELAY2;
  union                                            /* Offset=0x0518 : PEERDELAY3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PEERDELAY3:30;                              /* [29:0] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } PEERDELAY3;
  char                     wk_051C[0x0004];
  union                                            /* Offset=0x0520 : PORT0_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TS_VALID:1;                                 /* [0] */
      __IO unsigned long   TS_OVR:1;                                   /* [1] */
      __IO unsigned long   TS_KEEP:1;                                  /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PORT0_CTRL;
  union                                            /* Offset=0x0524 : PORT0_TIME */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PORT0_TIME:32;                              /* [31:0] */
    } BIT;
  } PORT0_TIME;
  union                                            /* Offset=0x0528 : PORT1_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TS_VALID:1;                                 /* [0] */
      __IO unsigned long   TS_OVR:1;                                   /* [1] */
      __IO unsigned long   TS_KEEP:1;                                  /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PORT1_CTRL;
  union                                            /* Offset=0x052C : PORT1_TIME */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PORT1_TIME:32;                              /* [31:0] */
    } BIT;
  } PORT1_TIME;
  union                                            /* Offset=0x0530 : PORT2_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TS_VALID:1;                                 /* [0] */
      __IO unsigned long   TS_OVR:1;                                   /* [1] */
      __IO unsigned long   TS_KEEP:1;                                  /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PORT2_CTRL;
  union                                            /* Offset=0x0534 : PORT2_TIME */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PORT2_TIME:32;                              /* [31:0] */
    } BIT;
  } PORT2_TIME;
  union                                            /* Offset=0x0538 : PORT3_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TS_VALID:1;                                 /* [0] */
      __IO unsigned long   TS_OVR:1;                                   /* [1] */
      __IO unsigned long   TS_KEEP:1;                                  /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PORT3_CTRL;
  union                                            /* Offset=0x053C : PORT3_TIME */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PORT3_TIME:32;                              /* [31:0] */
    } BIT;
  } PORT3_TIME;
  char                     wk_0540[0x00C0];
  union                                            /* Offset=0x0600 : INT_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IRQ_EN:1;                                   /* [0] */
      __IO unsigned long   MDIO1:1;                                    /* [1] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   LK_NEW_SRC:1;                               /* [3] */
      __IO unsigned long   IRQ_TEST:1;                                 /* [4] */
      __IO unsigned long   DLR_INT:1;                                  /* [5] */
      __IO unsigned long   PRP_INT:1;                                  /* [6] */
      __IO unsigned long   HUB_INT:1;                                  /* [7] */
      __IO unsigned long   IRQ_LINK:4;                                 /* [11:8] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   IRQ_TSM_TX:4;                               /* [19:16] */
      __IO unsigned long   :4;                                         /* [23:20] */
      __IO unsigned long   IRQ_MAC_EEE:4;                              /* [27:24] */
      __IO unsigned long   :2;                                         /* [29:28] */
      __IO unsigned long   TDMA_INT:1;                                 /* [30] */
      __IO unsigned long   PATTERN_INT:1;                              /* [31] */
    } BIT;
  } INT_CONFIG;
  union                                            /* Offset=0x0604 : INT_STAT_ACK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   IRQ_PEND:1;                                 /* [0] */
      __IO unsigned long   MDIO1:1;                                    /* [1] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   LK_NEW_SRC:1;                               /* [3] */
      __I  unsigned long   IRQ_TEST:1;                                 /* [4] */
      __I  unsigned long   DLR_INT:1;                                  /* [5] */
      __I  unsigned long   PRP_INT:1;                                  /* [6] */
      __I  unsigned long   HUB_INT:1;                                  /* [7] */
      __IO unsigned long   interrupt_latches:22;                       /* [29:8] */
      __I  unsigned long   TDMA_INT:1;                                 /* [30] */
      __I  unsigned long   PATTERN_INT:1;                              /* [31] */
    } BIT;
  } INT_STAT_ACK;
  char                     wk_0608[0x00F8];
  union                                            /* Offset=0x0700 : MDIO_CFG_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   BUSY:1;                                     /* [0] */
      __I  unsigned long   READERR:1;                                  /* [1] */
      __IO unsigned long   HOLD:3;                                     /* [4:2] */
      __IO unsigned long   DISPREAM:1;                                 /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   CLKDIV:9;                                   /* [15:7] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MDIO_CFG_STATUS;
  union                                            /* Offset=0x0704 : MDIO_COMMAND */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   REGADDR:5;                                  /* [4:0] */
      __IO unsigned long   PHYADDR:5;                                  /* [9:5] */
      __IO unsigned long   :5;                                         /* [14:10] */
      __IO unsigned long   TRANINIT:1;                                 /* [15] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MDIO_COMMAND;
  union                                            /* Offset=0x0708 : MDIO_DATA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MDIO_DATA:16;                               /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MDIO_DATA;
  char                     wk_070C[0x00F4];
  union                                            /* Offset=0x0800 : REV_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   REV:32;                                     /* [31:0] */
    } BIT;
  } REV_P0;
  char                     wk_0804[0x0004];
  union                                            /* Offset=0x0808 : COMMAND_CONFIG_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TX_ENA:1;                                   /* [0] */
      __IO unsigned long   RX_ENA:1;                                   /* [1] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   ETH_SPEED:1;                                /* [3] */
      __I  unsigned long   PROMIS_EN:1;                                /* [4] */
      __I  unsigned long   PAD_EN:1;                                   /* [5] */
      __IO unsigned long   CRC_FWD:1;                                  /* [6] */
      __I  unsigned long   PAUSE_FWD:1;                                /* [7] */
      __IO unsigned long   PAUSE_IGNORE:1;                             /* [8] */
      __I  unsigned long   TX_ADDR_INS:1;                              /* [9] */
      __IO unsigned long   HD_ENA:1;                                   /* [10] */
      __IO unsigned long   TX_CRC_APPEND:1;                            /* [11] */
      __IO unsigned long   :1;                                         /* [12] */
      __IO unsigned long   SW_RESET:1;                                 /* [13] */
      __IO unsigned long   :1;                                         /* [14] */
      __IO unsigned long   LOOP_ENA:1;                                 /* [15] */
      __IO unsigned long   :7;                                         /* [22:16] */
      __IO unsigned long   CNTL_FRM_ENA:1;                             /* [23] */
      __IO unsigned long   NO_LGTH_CHECK:1;                            /* [24] */
      __IO unsigned long   ENA_10:1;                                   /* [25] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } COMMAND_CONFIG_P0;
  union                                            /* Offset=0x080C : MAC_ADDR_0_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MAC_ADDR:32;                                /* [31:0] */
    } BIT;
  } MAC_ADDR_0_P0;
  union                                            /* Offset=0x0810 : MAC_ADDR_1_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MAC_ADDR:16;                                /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MAC_ADDR_1_P0;
  union                                            /* Offset=0x0814 : FRM_LENGTH_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FRM_LENGTH:14;                              /* [13:0] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } FRM_LENGTH_P0;
  union                                            /* Offset=0x0818 : PAUSE_QUANT_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PAUSE_QUANT:16;                             /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } PAUSE_QUANT_P0;
  char                     wk_081C[0x0014];
  union                                            /* Offset=0x0830 : PTPClockIdentity1_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClockIdentity0:8;                           /* [7:0] */
      __IO unsigned long   ClockIdentity1:8;                           /* [15:8] */
      __IO unsigned long   ClockIdentity2:8;                           /* [23:16] */
      __IO unsigned long   ClockIdentity3:8;                           /* [31:24] */
    } BIT;
  } PTPClockIdentity1_P0;
  union                                            /* Offset=0x0834 : PTPClockIdentity2_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClockIdentity4:8;                           /* [7:0] */
      __IO unsigned long   ClockIdentity5:8;                           /* [15:8] */
      __IO unsigned long   ClockIdentity6:8;                           /* [23:16] */
      __IO unsigned long   ClockIdentity7:8;                           /* [31:24] */
    } BIT;
  } PTPClockIdentity2_P0;
  union                                            /* Offset=0x0838 : PTPAutoResponse_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AutoRespEnable:1;                           /* [0] */
      __IO unsigned long   :15;                                        /* [15:1] */
      __IO unsigned long   PortNumber0:8;                              /* [23:16] */
      __IO unsigned long   PortNumber1:8;                              /* [31:24] */
    } BIT;
  } PTPAutoResponse_P0;
  char                     wk_083C[0x0004];
  union                                            /* Offset=0x0840 : STATUS_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PHYSPEED:2;                                 /* [1:0] */
      __I  unsigned long   PHYLINK:1;                                  /* [2] */
      __I  unsigned long   PHYDUPLEX:1;                                /* [3] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } STATUS_P0;
  union                                            /* Offset=0x0844 : TX_IPG_LENGTH_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TX_IPG_LENGTH:5;                            /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } TX_IPG_LENGTH_P0;
  union                                            /* Offset=0x0848 : EEE_CTL_STAT_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_AUTO:1;                                 /* [0] */
      __IO unsigned long   LPI_REQ:1;                                  /* [1] */
      __IO unsigned long   LPI_TXHOLD:1;                               /* [2] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __I  unsigned long   ST_LPI_REQ:1;                               /* [8] */
      __I  unsigned long   ST_LPI_TXHOLD:1;                            /* [9] */
      __I  unsigned long   ST_TXBUSY:1;                                /* [10] */
      __I  unsigned long   ST_TXAVAIL:1;                               /* [11] */
      __I  unsigned long   ST_LPI_IND:1;                               /* [12] */
      __IO unsigned long   :3;                                         /* [15:13] */
      __I  unsigned long   STLH_LPI_REQ:1;                             /* [16] */
      __I  unsigned long   STLH_LPI_TXHOLD:1;                          /* [17] */
      __I  unsigned long   STLH_TXBUSY:1;                              /* [18] */
      __IO unsigned long   :1;                                         /* [19] */
      __I  unsigned long   STLH_LPI_IND:1;                             /* [20] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } EEE_CTL_STAT_P0;
  union                                            /* Offset=0x084C : EEE_IDLE_TIME_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_IDLE_TIME_P0:32;                        /* [31:0] */
    } BIT;
  } EEE_IDLE_TIME_P0;
  union                                            /* Offset=0x0850 : EEE_TWSYS_TIME_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_TWSYS_TIME_P0:32;                       /* [31:0] */
    } BIT;
  } EEE_TWSYS_TIME_P0;
  union                                            /* Offset=0x0854 : IDLE_SLOPE_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IDLE_SLOPE:11;                              /* [10:0] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } IDLE_SLOPE_P0;
  char                     wk_0858[0x0010];
  union                                            /* Offset=0x0868 : aFramesTransmittedOK_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesTransmittedOK_P0:32;                 /* [31:0] */
    } BIT;
  } aFramesTransmittedOK_P0;
  union                                            /* Offset=0x086C : aFramesReceivedOK_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesReceivedOK_P0:32;                    /* [31:0] */
    } BIT;
  } aFramesReceivedOK_P0;
  union                                            /* Offset=0x0870 : aFrameCheckSequenceErrors_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFrameCheckSequenceErrors_P0:32;            /* [31:0] */
    } BIT;
  } aFrameCheckSequenceErrors_P0;
  union                                            /* Offset=0x0874 : aAlignmentErrors_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aAlignmentErrors_P0:32;                     /* [31:0] */
    } BIT;
  } aAlignmentErrors_P0;
  union                                            /* Offset=0x0878 : aOctetsTransmittedOK_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aOctetsTransmittedOK_P0:32;                 /* [31:0] */
    } BIT;
  } aOctetsTransmittedOK_P0;
  union                                            /* Offset=0x087C : aOctetsReceivedOK_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aOctetsReceivedOK_P0:32;                    /* [31:0] */
    } BIT;
  } aOctetsReceivedOK_P0;
  union                                            /* Offset=0x0880 : aTxPAUSEMACCtrlFrames_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aTxPAUSEMACCtrlFrames_P0:32;                /* [31:0] */
    } BIT;
  } aTxPAUSEMACCtrlFrames_P0;
  union                                            /* Offset=0x0884 : aRxPAUSEMACCtrlFrames_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aRxPAUSEMACCtrlFrames_P0:32;                /* [31:0] */
    } BIT;
  } aRxPAUSEMACCtrlFrames_P0;
  union                                            /* Offset=0x0888 : ifInErrors_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInErrors_P0:32;                           /* [31:0] */
    } BIT;
  } ifInErrors_P0;
  union                                            /* Offset=0x088C : ifOutErrors_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutErrors_P0:32;                          /* [31:0] */
    } BIT;
  } ifOutErrors_P0;
  union                                            /* Offset=0x0890 : ifInUcastPkts_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInUcastPkts_P0:32;                        /* [31:0] */
    } BIT;
  } ifInUcastPkts_P0;
  union                                            /* Offset=0x0894 : ifInMulticastPkts_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInMulticastPkts_P0:32;                    /* [31:0] */
    } BIT;
  } ifInMulticastPkts_P0;
  union                                            /* Offset=0x0898 : ifInBroadcastPkts_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInBroadcastPkts_P0:32;                    /* [31:0] */
    } BIT;
  } ifInBroadcastPkts_P0;
  union                                            /* Offset=0x089C : ifOutDiscards_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutDiscards_P0:32;                        /* [31:0] */
    } BIT;
  } ifOutDiscards_P0;
  union                                            /* Offset=0x08A0 : ifOutUcastPkts_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutUcastPkts_P0:32;                       /* [31:0] */
    } BIT;
  } ifOutUcastPkts_P0;
  union                                            /* Offset=0x08A4 : ifOutMulticastPkts_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutMulticastPkts_P0:32;                   /* [31:0] */
    } BIT;
  } ifOutMulticastPkts_P0;
  union                                            /* Offset=0x08A8 : ifOutBroadcastPkts_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutBroadcastPkts_P0:32;                   /* [31:0] */
    } BIT;
  } ifOutBroadcastPkts_P0;
  union                                            /* Offset=0x08AC : etherStatsDropEvents_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsDropEvents_P0:32;                 /* [31:0] */
    } BIT;
  } etherStatsDropEvents_P0;
  union                                            /* Offset=0x08B0 : etherStatsOctets_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsOctets_P0:32;                     /* [31:0] */
    } BIT;
  } etherStatsOctets_P0;
  union                                            /* Offset=0x08B4 : etherStatsPkts_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts_P0:32;                       /* [31:0] */
    } BIT;
  } etherStatsPkts_P0;
  union                                            /* Offset=0x08B8 : etherStatsUndersizePkts_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsUndersizePkts_P0:32;              /* [31:0] */
    } BIT;
  } etherStatsUndersizePkts_P0;
  union                                            /* Offset=0x08BC : etherStatsOversizePkts_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsOversizePkts_P0:32;               /* [31:0] */
    } BIT;
  } etherStatsOversizePkts_P0;
  union                                            /* Offset=0x08C0 : etherStatsPkts64Octets_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts64Octets_P0:32;               /* [31:0] */
    } BIT;
  } etherStatsPkts64Octets_P0;
  union                                            /* Offset=0x08C4 : etherStatsPkts65to127Octets_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts65to127Octets_P0:32;          /* [31:0] */
    } BIT;
  } etherStatsPkts65to127Octets_P0;
  union                                            /* Offset=0x08C8 : etherStatsPkts128to255Octets_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts128to255Octets_P0:32;         /* [31:0] */
    } BIT;
  } etherStatsPkts128to255Octets_P0;
  union                                            /* Offset=0x08CC : etherStatsPkts256to511Octets_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts256to511Octets_P0:32;         /* [31:0] */
    } BIT;
  } etherStatsPkts256to511Octets_P0;
  union                                            /* Offset=0x08D0 : etherStatsPkts512to1023Octets_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts512to1023Octets_P0:32;        /* [31:0] */
    } BIT;
  } etherStatsPkts512to1023Octets_P0;
  union                                            /* Offset=0x08D4 : etherStatsPkts1024to1518Octets_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts1024to1518Octets_P0:32;       /* [31:0] */
    } BIT;
  } etherStatsPkts1024to1518Octets_P0;
  union                                            /* Offset=0x08D8 : etherStatsPkts1519toXOctets_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts1519toXOctets_P0:32;          /* [31:0] */
    } BIT;
  } etherStatsPkts1519toXOctets_P0;
  union                                            /* Offset=0x08DC : etherStatsJabbers_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsJabbers_P0:32;                    /* [31:0] */
    } BIT;
  } etherStatsJabbers_P0;
  union                                            /* Offset=0x08E0 : etherStatsFragments_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsFragments_P0:32;                  /* [31:0] */
    } BIT;
  } etherStatsFragments_P0;
  char                     wk_08E4[0x0004];
  union                                            /* Offset=0x08E8 : VLANReceivedOK_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VLANReceivedOK_P0:32;                       /* [31:0] */
    } BIT;
  } VLANReceivedOK_P0;
  char                     wk_08EC[0x0008];
  union                                            /* Offset=0x08F4 : VLANTransmittedOK_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VLANTransmittedOK_P0:32;                    /* [31:0] */
    } BIT;
  } VLANTransmittedOK_P0;
  union                                            /* Offset=0x08F8 : FramesRetransmitted_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   FramesRetransmitted_P0:32;                  /* [31:0] */
    } BIT;
  } FramesRetransmitted_P0;
  char                     wk_08FC[0x0004];
  union                                            /* Offset=0x0900 : STATS_HIWORD_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   STATS_HIWORD_P0:32;                         /* [31:0] */
    } BIT;
  } STATS_HIWORD_P0;
  union                                            /* Offset=0x0904 : STATS_CTRL_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClearALL:1;                                 /* [0] */
      __I  unsigned long   ClearBusy:1;                                /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } STATS_CTRL_P0;
  union                                            /* Offset=0x0908 : STATS_CLEAR_VALUELO_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   STATS_CLEAR_VALUELO_P0:32;                  /* [31:0] */
    } BIT;
  } STATS_CLEAR_VALUELO_P0;
  union                                            /* Offset=0x090C : STATS_CLEAR_VALUEHI_P0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   STATS_CLEAR_VALUEHI_P0:32;                  /* [31:0] */
    } BIT;
  } STATS_CLEAR_VALUEHI_P0;
  union                                            /* Offset=0x0910 : aDeferred_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aDeferred_P0:32;                            /* [31:0] */
    } BIT;
  } aDeferred_P0;
  union                                            /* Offset=0x0914 : aMultipleCollisions_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aMultipleCollisions_P0:32;                  /* [31:0] */
    } BIT;
  } aMultipleCollisions_P0;
  union                                            /* Offset=0x0918 : aSingleCollisions_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aSingleCollisions_P0:32;                    /* [31:0] */
    } BIT;
  } aSingleCollisions_P0;
  union                                            /* Offset=0x091C : aLateCollisions_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aLateCollisions_P0:32;                      /* [31:0] */
    } BIT;
  } aLateCollisions_P0;
  union                                            /* Offset=0x0920 : aExcessiveCollisions_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aExcessiveCollisions_P0:32;                 /* [31:0] */
    } BIT;
  } aExcessiveCollisions_P0;
  union                                            /* Offset=0x0924 : aCarrierSenseErrors_P0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aCarrierSenseErrors_P0:32;                  /* [31:0] */
    } BIT;
  } aCarrierSenseErrors_P0;
  char                     wk_0928[0x02D8];
  union                                            /* Offset=0x0C00 : REV_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   REV:32;                                     /* [31:0] */
    } BIT;
  } REV_P1;
  char                     wk_0C04[0x0004];
  union                                            /* Offset=0x0C08 : COMMAND_CONFIG_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TX_ENA:1;                                   /* [0] */
      __IO unsigned long   RX_ENA:1;                                   /* [1] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   ETH_SPEED:1;                                /* [3] */
      __I  unsigned long   PROMIS_EN:1;                                /* [4] */
      __I  unsigned long   PAD_EN:1;                                   /* [5] */
      __IO unsigned long   CRC_FWD:1;                                  /* [6] */
      __I  unsigned long   PAUSE_FWD:1;                                /* [7] */
      __IO unsigned long   PAUSE_IGNORE:1;                             /* [8] */
      __I  unsigned long   TX_ADDR_INS:1;                              /* [9] */
      __IO unsigned long   HD_ENA:1;                                   /* [10] */
      __IO unsigned long   TX_CRC_APPEND:1;                            /* [11] */
      __IO unsigned long   :1;                                         /* [12] */
      __IO unsigned long   SW_RESET:1;                                 /* [13] */
      __IO unsigned long   :1;                                         /* [14] */
      __IO unsigned long   LOOP_ENA:1;                                 /* [15] */
      __IO unsigned long   :7;                                         /* [22:16] */
      __IO unsigned long   CNTL_FRM_ENA:1;                             /* [23] */
      __IO unsigned long   NO_LGTH_CHECK:1;                            /* [24] */
      __IO unsigned long   ENA_10:1;                                   /* [25] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } COMMAND_CONFIG_P1;
  union                                            /* Offset=0x0C0C : MAC_ADDR_0_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MAC_ADDR:32;                                /* [31:0] */
    } BIT;
  } MAC_ADDR_0_P1;
  union                                            /* Offset=0x0C10 : MAC_ADDR_1_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MAC_ADDR:16;                                /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MAC_ADDR_1_P1;
  union                                            /* Offset=0x0C14 : FRM_LENGTH_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FRM_LENGTH:14;                              /* [13:0] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } FRM_LENGTH_P1;
  union                                            /* Offset=0x0C18 : PAUSE_QUANT_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PAUSE_QUANT:16;                             /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } PAUSE_QUANT_P1;
  char                     wk_0C1C[0x0014];
  union                                            /* Offset=0x0C30 : PTPClockIdentity1_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClockIdentity0:8;                           /* [7:0] */
      __IO unsigned long   ClockIdentity1:8;                           /* [15:8] */
      __IO unsigned long   ClockIdentity2:8;                           /* [23:16] */
      __IO unsigned long   ClockIdentity3:8;                           /* [31:24] */
    } BIT;
  } PTPClockIdentity1_P1;
  union                                            /* Offset=0x0C34 : PTPClockIdentity2_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClockIdentity4:8;                           /* [7:0] */
      __IO unsigned long   ClockIdentity5:8;                           /* [15:8] */
      __IO unsigned long   ClockIdentity6:8;                           /* [23:16] */
      __IO unsigned long   ClockIdentity7:8;                           /* [31:24] */
    } BIT;
  } PTPClockIdentity2_P1;
  union                                            /* Offset=0x0C38 : PTPAutoResponse_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AutoRespEnable:1;                           /* [0] */
      __IO unsigned long   :15;                                        /* [15:1] */
      __IO unsigned long   PortNumber0:8;                              /* [23:16] */
      __IO unsigned long   PortNumber1:8;                              /* [31:24] */
    } BIT;
  } PTPAutoResponse_P1;
  char                     wk_0C3C[0x0004];
  union                                            /* Offset=0x0C40 : STATUS_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PHYSPEED:2;                                 /* [1:0] */
      __I  unsigned long   PHYLINK:1;                                  /* [2] */
      __I  unsigned long   PHYDUPLEX:1;                                /* [3] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } STATUS_P1;
  union                                            /* Offset=0x0C44 : TX_IPG_LENGTH_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TX_IPG_LENGTH:5;                            /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } TX_IPG_LENGTH_P1;
  union                                            /* Offset=0x0C48 : EEE_CTL_STAT_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_AUTO:1;                                 /* [0] */
      __IO unsigned long   LPI_REQ:1;                                  /* [1] */
      __IO unsigned long   LPI_TXHOLD:1;                               /* [2] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __I  unsigned long   ST_LPI_REQ:1;                               /* [8] */
      __I  unsigned long   ST_LPI_TXHOLD:1;                            /* [9] */
      __I  unsigned long   ST_TXBUSY:1;                                /* [10] */
      __I  unsigned long   ST_TXAVAIL:1;                               /* [11] */
      __I  unsigned long   ST_LPI_IND:1;                               /* [12] */
      __IO unsigned long   :3;                                         /* [15:13] */
      __I  unsigned long   STLH_LPI_REQ:1;                             /* [16] */
      __I  unsigned long   STLH_LPI_TXHOLD:1;                          /* [17] */
      __I  unsigned long   STLH_TXBUSY:1;                              /* [18] */
      __IO unsigned long   :1;                                         /* [19] */
      __I  unsigned long   STLH_LPI_IND:1;                             /* [20] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } EEE_CTL_STAT_P1;
  union                                            /* Offset=0x0C4C : EEE_IDLE_TIME_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_IDLE_TIME_P1:32;                        /* [31:0] */
    } BIT;
  } EEE_IDLE_TIME_P1;
  union                                            /* Offset=0x0C50 : EEE_TWSYS_TIME_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_TWSYS_TIME_P1:32;                       /* [31:0] */
    } BIT;
  } EEE_TWSYS_TIME_P1;
  union                                            /* Offset=0x0C54 : IDLE_SLOPE_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IDLE_SLOPE:11;                              /* [10:0] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } IDLE_SLOPE_P1;
  char                     wk_0C58[0x0010];
  union                                            /* Offset=0x0C68 : aFramesTransmittedOK_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesTransmittedOK_P1:32;                 /* [31:0] */
    } BIT;
  } aFramesTransmittedOK_P1;
  union                                            /* Offset=0x0C6C : aFramesReceivedOK_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesReceivedOK_P1:32;                    /* [31:0] */
    } BIT;
  } aFramesReceivedOK_P1;
  union                                            /* Offset=0x0C70 : aFrameCheckSequenceErrors_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFrameCheckSequenceErrors_P1:32;            /* [31:0] */
    } BIT;
  } aFrameCheckSequenceErrors_P1;
  union                                            /* Offset=0x0C74 : aAlignmentErrors_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aAlignmentErrors_P1:32;                     /* [31:0] */
    } BIT;
  } aAlignmentErrors_P1;
  union                                            /* Offset=0x0C78 : aOctetsTransmittedOK_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aOctetsTransmittedOK_P1:32;                 /* [31:0] */
    } BIT;
  } aOctetsTransmittedOK_P1;
  union                                            /* Offset=0x0C7C : aOctetsReceivedOK_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aOctetsReceivedOK_P1:32;                    /* [31:0] */
    } BIT;
  } aOctetsReceivedOK_P1;
  union                                            /* Offset=0x0C80 : aTxPAUSEMACCtrlFrames_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aTxPAUSEMACCtrlFrames_P1:32;                /* [31:0] */
    } BIT;
  } aTxPAUSEMACCtrlFrames_P1;
  union                                            /* Offset=0x0C84 : aRxPAUSEMACCtrlFrames_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aRxPAUSEMACCtrlFrames_P1:32;                /* [31:0] */
    } BIT;
  } aRxPAUSEMACCtrlFrames_P1;
  union                                            /* Offset=0x0C88 : ifInErrors_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInErrors_P1:32;                           /* [31:0] */
    } BIT;
  } ifInErrors_P1;
  union                                            /* Offset=0x0C8C : ifOutErrors_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutErrors_P1:32;                          /* [31:0] */
    } BIT;
  } ifOutErrors_P1;
  union                                            /* Offset=0x0C90 : ifInUcastPkts_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInUcastPkts_P1:32;                        /* [31:0] */
    } BIT;
  } ifInUcastPkts_P1;
  union                                            /* Offset=0x0C94 : ifInMulticastPkts_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInMulticastPkts_P1:32;                    /* [31:0] */
    } BIT;
  } ifInMulticastPkts_P1;
  union                                            /* Offset=0x0C98 : ifInBroadcastPkts_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInBroadcastPkts_P1:32;                    /* [31:0] */
    } BIT;
  } ifInBroadcastPkts_P1;
  union                                            /* Offset=0x0C9C : ifOutDiscards_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutDiscards_P1:32;                        /* [31:0] */
    } BIT;
  } ifOutDiscards_P1;
  union                                            /* Offset=0x0CA0 : ifOutUcastPkts_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutUcastPkts_P1:32;                       /* [31:0] */
    } BIT;
  } ifOutUcastPkts_P1;
  union                                            /* Offset=0x0CA4 : ifOutMulticastPkts_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutMulticastPkts_P1:32;                   /* [31:0] */
    } BIT;
  } ifOutMulticastPkts_P1;
  union                                            /* Offset=0x0CA8 : ifOutBroadcastPkts_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutBroadcastPkts_P1:32;                   /* [31:0] */
    } BIT;
  } ifOutBroadcastPkts_P1;
  union                                            /* Offset=0x0CAC : etherStatsDropEvents_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsDropEvents_P1:32;                 /* [31:0] */
    } BIT;
  } etherStatsDropEvents_P1;
  union                                            /* Offset=0x0CB0 : etherStatsOctets_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsOctets_P1:32;                     /* [31:0] */
    } BIT;
  } etherStatsOctets_P1;
  union                                            /* Offset=0x0CB4 : etherStatsPkts_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts_P1:32;                       /* [31:0] */
    } BIT;
  } etherStatsPkts_P1;
  union                                            /* Offset=0x0CB8 : etherStatsUndersizePkts_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsUndersizePkts_P1:32;              /* [31:0] */
    } BIT;
  } etherStatsUndersizePkts_P1;
  union                                            /* Offset=0x0CBC : etherStatsOversizePkts_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsOversizePkts_P1:32;               /* [31:0] */
    } BIT;
  } etherStatsOversizePkts_P1;
  union                                            /* Offset=0x0CC0 : etherStatsPkts64Octets_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts64Octets_P1:32;               /* [31:0] */
    } BIT;
  } etherStatsPkts64Octets_P1;
  union                                            /* Offset=0x0CC4 : etherStatsPkts65to127Octets_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts65to127Octets_P1:32;          /* [31:0] */
    } BIT;
  } etherStatsPkts65to127Octets_P1;
  union                                            /* Offset=0x0CC8 : etherStatsPkts128to255Octets_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts128to255Octets_P1:32;         /* [31:0] */
    } BIT;
  } etherStatsPkts128to255Octets_P1;
  union                                            /* Offset=0x0CCC : etherStatsPkts256to511Octets_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts256to511Octets_P1:32;         /* [31:0] */
    } BIT;
  } etherStatsPkts256to511Octets_P1;
  union                                            /* Offset=0x0CD0 : etherStatsPkts512to1023Octets_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts512to1023Octets_P1:32;        /* [31:0] */
    } BIT;
  } etherStatsPkts512to1023Octets_P1;
  union                                            /* Offset=0x0CD4 : etherStatsPkts1024to1518Octets_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts1024to1518Octets_P1:32;       /* [31:0] */
    } BIT;
  } etherStatsPkts1024to1518Octets_P1;
  union                                            /* Offset=0x0CD8 : etherStatsPkts1519toXOctets_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts1519toXOctets_P1:32;          /* [31:0] */
    } BIT;
  } etherStatsPkts1519toXOctets_P1;
  union                                            /* Offset=0x0CDC : etherStatsJabbers_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsJabbers_P1:32;                    /* [31:0] */
    } BIT;
  } etherStatsJabbers_P1;
  union                                            /* Offset=0x0CE0 : etherStatsFragments_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsFragments_P1:32;                  /* [31:0] */
    } BIT;
  } etherStatsFragments_P1;
  char                     wk_0CE4[0x0004];
  union                                            /* Offset=0x0CE8 : VLANReceivedOK_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VLANReceivedOK_P1:32;                       /* [31:0] */
    } BIT;
  } VLANReceivedOK_P1;
  char                     wk_0CEC[0x0008];
  union                                            /* Offset=0x0CF4 : VLANTransmittedOK_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VLANTransmittedOK_P1:32;                    /* [31:0] */
    } BIT;
  } VLANTransmittedOK_P1;
  union                                            /* Offset=0x0CF8 : FramesRetransmitted_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   FramesRetransmitted_P1:32;                  /* [31:0] */
    } BIT;
  } FramesRetransmitted_P1;
  char                     wk_0CFC[0x0004];
  union                                            /* Offset=0x0D00 : STATS_HIWORD_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   STATS_HIWORD_P1:32;                         /* [31:0] */
    } BIT;
  } STATS_HIWORD_P1;
  union                                            /* Offset=0x0D04 : STATS_CTRL_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClearALL:1;                                 /* [0] */
      __I  unsigned long   ClearBusy:1;                                /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } STATS_CTRL_P1;
  union                                            /* Offset=0x0D08 : STATS_CLEAR_VALUELO_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   STATS_CLEAR_VALUELO_P1:32;                  /* [31:0] */
    } BIT;
  } STATS_CLEAR_VALUELO_P1;
  union                                            /* Offset=0x0D0C : STATS_CLEAR_VALUEHI_P1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   STATS_CLEAR_VALUEHI_P1:32;                  /* [31:0] */
    } BIT;
  } STATS_CLEAR_VALUEHI_P1;
  union                                            /* Offset=0x0D10 : aDeferred_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aDeferred_P1:32;                            /* [31:0] */
    } BIT;
  } aDeferred_P1;
  union                                            /* Offset=0x0D14 : aMultipleCollisions_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aMultipleCollisions_P1:32;                  /* [31:0] */
    } BIT;
  } aMultipleCollisions_P1;
  union                                            /* Offset=0x0D18 : aSingleCollisions_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aSingleCollisions_P1:32;                    /* [31:0] */
    } BIT;
  } aSingleCollisions_P1;
  union                                            /* Offset=0x0D1C : aLateCollisions_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aLateCollisions_P1:32;                      /* [31:0] */
    } BIT;
  } aLateCollisions_P1;
  union                                            /* Offset=0x0D20 : aExcessiveCollisions_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aExcessiveCollisions_P1:32;                 /* [31:0] */
    } BIT;
  } aExcessiveCollisions_P1;
  union                                            /* Offset=0x0D24 : aCarrierSenseErrors_P1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aCarrierSenseErrors_P1:32;                  /* [31:0] */
    } BIT;
  } aCarrierSenseErrors_P1;
  char                     wk_0D28[0x02D8];
  union                                            /* Offset=0x1000 : REV_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   REV:32;                                     /* [31:0] */
    } BIT;
  } REV_P2;
  char                     wk_1004[0x0004];
  union                                            /* Offset=0x1008 : COMMAND_CONFIG_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TX_ENA:1;                                   /* [0] */
      __IO unsigned long   RX_ENA:1;                                   /* [1] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   ETH_SPEED:1;                                /* [3] */
      __I  unsigned long   PROMIS_EN:1;                                /* [4] */
      __I  unsigned long   PAD_EN:1;                                   /* [5] */
      __IO unsigned long   CRC_FWD:1;                                  /* [6] */
      __I  unsigned long   PAUSE_FWD:1;                                /* [7] */
      __IO unsigned long   PAUSE_IGNORE:1;                             /* [8] */
      __I  unsigned long   TX_ADDR_INS:1;                              /* [9] */
      __IO unsigned long   HD_ENA:1;                                   /* [10] */
      __IO unsigned long   TX_CRC_APPEND:1;                            /* [11] */
      __IO unsigned long   :1;                                         /* [12] */
      __IO unsigned long   SW_RESET:1;                                 /* [13] */
      __IO unsigned long   :1;                                         /* [14] */
      __IO unsigned long   LOOP_ENA:1;                                 /* [15] */
      __IO unsigned long   :7;                                         /* [22:16] */
      __IO unsigned long   CNTL_FRM_ENA:1;                             /* [23] */
      __IO unsigned long   NO_LGTH_CHECK:1;                            /* [24] */
      __IO unsigned long   ENA_10:1;                                   /* [25] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } COMMAND_CONFIG_P2;
  union                                            /* Offset=0x100C : MAC_ADDR_0_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MAC_ADDR:32;                                /* [31:0] */
    } BIT;
  } MAC_ADDR_0_P2;
  union                                            /* Offset=0x1010 : MAC_ADDR_1_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MAC_ADDR:16;                                /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MAC_ADDR_1_P2;
  union                                            /* Offset=0x1014 : FRM_LENGTH_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FRM_LENGTH:14;                              /* [13:0] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } FRM_LENGTH_P2;
  union                                            /* Offset=0x1018 : PAUSE_QUANT_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PAUSE_QUANT:16;                             /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } PAUSE_QUANT_P2;
  char                     wk_101C[0x0014];
  union                                            /* Offset=0x1030 : PTPClockIdentity1_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClockIdentity0:8;                           /* [7:0] */
      __IO unsigned long   ClockIdentity1:8;                           /* [15:8] */
      __IO unsigned long   ClockIdentity2:8;                           /* [23:16] */
      __IO unsigned long   ClockIdentity3:8;                           /* [31:24] */
    } BIT;
  } PTPClockIdentity1_P2;
  union                                            /* Offset=0x1034 : PTPClockIdentity2_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClockIdentity4:8;                           /* [7:0] */
      __IO unsigned long   ClockIdentity5:8;                           /* [15:8] */
      __IO unsigned long   ClockIdentity6:8;                           /* [23:16] */
      __IO unsigned long   ClockIdentity7:8;                           /* [31:24] */
    } BIT;
  } PTPClockIdentity2_P2;
  union                                            /* Offset=0x1038 : PTPAutoResponse_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AutoRespEnable:1;                           /* [0] */
      __IO unsigned long   :15;                                        /* [15:1] */
      __IO unsigned long   PortNumber0:8;                              /* [23:16] */
      __IO unsigned long   PortNumber1:8;                              /* [31:24] */
    } BIT;
  } PTPAutoResponse_P2;
  char                     wk_103C[0x0004];
  union                                            /* Offset=0x1040 : STATUS_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PHYSPEED:2;                                 /* [1:0] */
      __I  unsigned long   PHYLINK:1;                                  /* [2] */
      __I  unsigned long   PHYDUPLEX:1;                                /* [3] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } STATUS_P2;
  union                                            /* Offset=0x1044 : TX_IPG_LENGTH_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TX_IPG_LENGTH:5;                            /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } TX_IPG_LENGTH_P2;
  union                                            /* Offset=0x1048 : EEE_CTL_STAT_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_AUTO:1;                                 /* [0] */
      __IO unsigned long   LPI_REQ:1;                                  /* [1] */
      __IO unsigned long   LPI_TXHOLD:1;                               /* [2] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __I  unsigned long   ST_LPI_REQ:1;                               /* [8] */
      __I  unsigned long   ST_LPI_TXHOLD:1;                            /* [9] */
      __I  unsigned long   ST_TXBUSY:1;                                /* [10] */
      __I  unsigned long   ST_TXAVAIL:1;                               /* [11] */
      __I  unsigned long   ST_LPI_IND:1;                               /* [12] */
      __IO unsigned long   :3;                                         /* [15:13] */
      __I  unsigned long   STLH_LPI_REQ:1;                             /* [16] */
      __I  unsigned long   STLH_LPI_TXHOLD:1;                          /* [17] */
      __I  unsigned long   STLH_TXBUSY:1;                              /* [18] */
      __IO unsigned long   :1;                                         /* [19] */
      __I  unsigned long   STLH_LPI_IND:1;                             /* [20] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } EEE_CTL_STAT_P2;
  union                                            /* Offset=0x104C : EEE_IDLE_TIME_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_IDLE_TIME_P2:32;                        /* [31:0] */
    } BIT;
  } EEE_IDLE_TIME_P2;
  union                                            /* Offset=0x1050 : EEE_TWSYS_TIME_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_TWSYS_TIME_P2:32;                       /* [31:0] */
    } BIT;
  } EEE_TWSYS_TIME_P2;
  union                                            /* Offset=0x1054 : IDLE_SLOPE_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IDLE_SLOPE:11;                              /* [10:0] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } IDLE_SLOPE_P2;
  char                     wk_1058[0x0010];
  union                                            /* Offset=0x1068 : aFramesTransmittedOK_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesTransmittedOK_P2:32;                 /* [31:0] */
    } BIT;
  } aFramesTransmittedOK_P2;
  union                                            /* Offset=0x106C : aFramesReceivedOK_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesReceivedOK_P2:32;                    /* [31:0] */
    } BIT;
  } aFramesReceivedOK_P2;
  union                                            /* Offset=0x1070 : aFrameCheckSequenceErrors_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFrameCheckSequenceErrors_P2:32;            /* [31:0] */
    } BIT;
  } aFrameCheckSequenceErrors_P2;
  union                                            /* Offset=0x1074 : aAlignmentErrors_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aAlignmentErrors_P2:32;                     /* [31:0] */
    } BIT;
  } aAlignmentErrors_P2;
  union                                            /* Offset=0x1078 : aOctetsTransmittedOK_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aOctetsTransmittedOK_P2:32;                 /* [31:0] */
    } BIT;
  } aOctetsTransmittedOK_P2;
  union                                            /* Offset=0x107C : aOctetsReceivedOK_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aOctetsReceivedOK_P2:32;                    /* [31:0] */
    } BIT;
  } aOctetsReceivedOK_P2;
  union                                            /* Offset=0x1080 : aTxPAUSEMACCtrlFrames_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aTxPAUSEMACCtrlFrames_P2:32;                /* [31:0] */
    } BIT;
  } aTxPAUSEMACCtrlFrames_P2;
  union                                            /* Offset=0x1084 : aRxPAUSEMACCtrlFrames_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aRxPAUSEMACCtrlFrames_P2:32;                /* [31:0] */
    } BIT;
  } aRxPAUSEMACCtrlFrames_P2;
  union                                            /* Offset=0x1088 : ifInErrors_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInErrors_P2:32;                           /* [31:0] */
    } BIT;
  } ifInErrors_P2;
  union                                            /* Offset=0x108C : ifOutErrors_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutErrors_P2:32;                          /* [31:0] */
    } BIT;
  } ifOutErrors_P2;
  union                                            /* Offset=0x1090 : ifInUcastPkts_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInUcastPkts_P2:32;                        /* [31:0] */
    } BIT;
  } ifInUcastPkts_P2;
  union                                            /* Offset=0x1094 : ifInMulticastPkts_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInMulticastPkts_P2:32;                    /* [31:0] */
    } BIT;
  } ifInMulticastPkts_P2;
  union                                            /* Offset=0x1098 : ifInBroadcastPkts_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInBroadcastPkts_P2:32;                    /* [31:0] */
    } BIT;
  } ifInBroadcastPkts_P2;
  union                                            /* Offset=0x109C : ifOutDiscards_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutDiscards_P2:32;                        /* [31:0] */
    } BIT;
  } ifOutDiscards_P2;
  union                                            /* Offset=0x10A0 : ifOutUcastPkts_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutUcastPkts_P2:32;                       /* [31:0] */
    } BIT;
  } ifOutUcastPkts_P2;
  union                                            /* Offset=0x10A4 : ifOutMulticastPkts_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutMulticastPkts_P2:32;                   /* [31:0] */
    } BIT;
  } ifOutMulticastPkts_P2;
  union                                            /* Offset=0x10A8 : ifOutBroadcastPkts_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutBroadcastPkts_P2:32;                   /* [31:0] */
    } BIT;
  } ifOutBroadcastPkts_P2;
  union                                            /* Offset=0x10AC : etherStatsDropEvents_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsDropEvents_P2:32;                 /* [31:0] */
    } BIT;
  } etherStatsDropEvents_P2;
  union                                            /* Offset=0x10B0 : etherStatsOctets_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsOctets_P2:32;                     /* [31:0] */
    } BIT;
  } etherStatsOctets_P2;
  union                                            /* Offset=0x10B4 : etherStatsPkts_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts_P2:32;                       /* [31:0] */
    } BIT;
  } etherStatsPkts_P2;
  union                                            /* Offset=0x10B8 : etherStatsUndersizePkts_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsUndersizePkts_P2:32;              /* [31:0] */
    } BIT;
  } etherStatsUndersizePkts_P2;
  union                                            /* Offset=0x10BC : etherStatsOversizePkts_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsOversizePkts_P2:32;               /* [31:0] */
    } BIT;
  } etherStatsOversizePkts_P2;
  union                                            /* Offset=0x10C0 : etherStatsPkts64Octets_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts64Octets_P2:32;               /* [31:0] */
    } BIT;
  } etherStatsPkts64Octets_P2;
  union                                            /* Offset=0x10C4 : etherStatsPkts65to127Octets_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts65to127Octets_P2:32;          /* [31:0] */
    } BIT;
  } etherStatsPkts65to127Octets_P2;
  union                                            /* Offset=0x10C8 : etherStatsPkts128to255Octets_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts128to255Octets_P2:32;         /* [31:0] */
    } BIT;
  } etherStatsPkts128to255Octets_P2;
  union                                            /* Offset=0x10CC : etherStatsPkts256to511Octets_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts256to511Octets_P2:32;         /* [31:0] */
    } BIT;
  } etherStatsPkts256to511Octets_P2;
  union                                            /* Offset=0x10D0 : etherStatsPkts512to1023Octets_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts512to1023Octets_P2:32;        /* [31:0] */
    } BIT;
  } etherStatsPkts512to1023Octets_P2;
  union                                            /* Offset=0x10D4 : etherStatsPkts1024to1518Octets_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts1024to1518Octets_P2:32;       /* [31:0] */
    } BIT;
  } etherStatsPkts1024to1518Octets_P2;
  union                                            /* Offset=0x10D8 : etherStatsPkts1519toXOctets_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts1519toXOctets_P2:32;          /* [31:0] */
    } BIT;
  } etherStatsPkts1519toXOctets_P2;
  union                                            /* Offset=0x10DC : etherStatsJabbers_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsJabbers_P2:32;                    /* [31:0] */
    } BIT;
  } etherStatsJabbers_P2;
  union                                            /* Offset=0x10E0 : etherStatsFragments_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsFragments_P2:32;                  /* [31:0] */
    } BIT;
  } etherStatsFragments_P2;
  char                     wk_10E4[0x0004];
  union                                            /* Offset=0x10E8 : VLANReceivedOK_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VLANReceivedOK_P2:32;                       /* [31:0] */
    } BIT;
  } VLANReceivedOK_P2;
  char                     wk_10EC[0x0008];
  union                                            /* Offset=0x10F4 : VLANTransmittedOK_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VLANTransmittedOK_P2:32;                    /* [31:0] */
    } BIT;
  } VLANTransmittedOK_P2;
  union                                            /* Offset=0x10F8 : FramesRetransmitted_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   FramesRetransmitted_P2:32;                  /* [31:0] */
    } BIT;
  } FramesRetransmitted_P2;
  char                     wk_10FC[0x0004];
  union                                            /* Offset=0x1100 : STATS_HIWORD_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   STATS_HIWORD_P2:32;                         /* [31:0] */
    } BIT;
  } STATS_HIWORD_P2;
  union                                            /* Offset=0x1104 : STATS_CTRL_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClearALL:1;                                 /* [0] */
      __I  unsigned long   ClearBusy:1;                                /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } STATS_CTRL_P2;
  union                                            /* Offset=0x1108 : STATS_CLEAR_VALUELO_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   STATS_CLEAR_VALUELO_P2:32;                  /* [31:0] */
    } BIT;
  } STATS_CLEAR_VALUELO_P2;
  union                                            /* Offset=0x110C : STATS_CLEAR_VALUEHI_P2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   STATS_CLEAR_VALUEHI_P2:32;                  /* [31:0] */
    } BIT;
  } STATS_CLEAR_VALUEHI_P2;
  union                                            /* Offset=0x1110 : aDeferred_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aDeferred_P2:32;                            /* [31:0] */
    } BIT;
  } aDeferred_P2;
  union                                            /* Offset=0x1114 : aMultipleCollisions_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aMultipleCollisions_P2:32;                  /* [31:0] */
    } BIT;
  } aMultipleCollisions_P2;
  union                                            /* Offset=0x1118 : aSingleCollisions_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aSingleCollisions_P2:32;                    /* [31:0] */
    } BIT;
  } aSingleCollisions_P2;
  union                                            /* Offset=0x111C : aLateCollisions_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aLateCollisions_P2:32;                      /* [31:0] */
    } BIT;
  } aLateCollisions_P2;
  union                                            /* Offset=0x1120 : aExcessiveCollisions_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aExcessiveCollisions_P2:32;                 /* [31:0] */
    } BIT;
  } aExcessiveCollisions_P2;
  union                                            /* Offset=0x1124 : aCarrierSenseErrors_P2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aCarrierSenseErrors_P2:32;                  /* [31:0] */
    } BIT;
  } aCarrierSenseErrors_P2;
  char                     wk_1128[0x02D8];
  union                                            /* Offset=0x1400 : REV_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   REV:32;                                     /* [31:0] */
    } BIT;
  } REV_P3;
  char                     wk_1404[0x0004];
  union                                            /* Offset=0x1408 : COMMAND_CONFIG_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TX_ENA:1;                                   /* [0] */
      __IO unsigned long   RX_ENA:1;                                   /* [1] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   ETH_SPEED:1;                                /* [3] */
      __I  unsigned long   PROMIS_EN:1;                                /* [4] */
      __I  unsigned long   PAD_EN:1;                                   /* [5] */
      __IO unsigned long   CRC_FWD:1;                                  /* [6] */
      __I  unsigned long   PAUSE_FWD:1;                                /* [7] */
      __IO unsigned long   PAUSE_IGNORE:1;                             /* [8] */
      __I  unsigned long   TX_ADDR_INS:1;                              /* [9] */
      __IO unsigned long   HD_ENA:1;                                   /* [10] */
      __IO unsigned long   TX_CRC_APPEND:1;                            /* [11] */
      __IO unsigned long   :1;                                         /* [12] */
      __IO unsigned long   SW_RESET:1;                                 /* [13] */
      __IO unsigned long   :1;                                         /* [14] */
      __IO unsigned long   LOOP_ENA:1;                                 /* [15] */
      __IO unsigned long   :7;                                         /* [22:16] */
      __IO unsigned long   CNTL_FRM_ENA:1;                             /* [23] */
      __IO unsigned long   NO_LGTH_CHECK:1;                            /* [24] */
      __IO unsigned long   ENA_10:1;                                   /* [25] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } COMMAND_CONFIG_P3;
  union                                            /* Offset=0x140C : MAC_ADDR_0_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MAC_ADDR:32;                                /* [31:0] */
    } BIT;
  } MAC_ADDR_0_P3;
  union                                            /* Offset=0x1410 : MAC_ADDR_1_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MAC_ADDR:16;                                /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } MAC_ADDR_1_P3;
  union                                            /* Offset=0x1414 : FRM_LENGTH_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FRM_LENGTH:14;                              /* [13:0] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } FRM_LENGTH_P3;
  union                                            /* Offset=0x1418 : PAUSE_QUANT_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PAUSE_QUANT:16;                             /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } PAUSE_QUANT_P3;
  char                     wk_141C[0x0014];
  union                                            /* Offset=0x1430 : PTPClockIdentity1_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClockIdentity0:8;                           /* [7:0] */
      __IO unsigned long   ClockIdentity1:8;                           /* [15:8] */
      __IO unsigned long   ClockIdentity2:8;                           /* [23:16] */
      __IO unsigned long   ClockIdentity3:8;                           /* [31:24] */
    } BIT;
  } PTPClockIdentity1_P3;
  union                                            /* Offset=0x1434 : PTPClockIdentity2_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClockIdentity4:8;                           /* [7:0] */
      __IO unsigned long   ClockIdentity5:8;                           /* [15:8] */
      __IO unsigned long   ClockIdentity6:8;                           /* [23:16] */
      __IO unsigned long   ClockIdentity7:8;                           /* [31:24] */
    } BIT;
  } PTPClockIdentity2_P3;
  union                                            /* Offset=0x1438 : PTPAutoResponse_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AutoRespEnable:1;                           /* [0] */
      __IO unsigned long   :15;                                        /* [15:1] */
      __IO unsigned long   PortNumber0:8;                              /* [23:16] */
      __IO unsigned long   PortNumber1:8;                              /* [31:24] */
    } BIT;
  } PTPAutoResponse_P3;
  char                     wk_143C[0x0004];
  union                                            /* Offset=0x1440 : STATUS_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PHYSPEED:2;                                 /* [1:0] */
      __I  unsigned long   PHYLINK:1;                                  /* [2] */
      __I  unsigned long   PHYDUPLEX:1;                                /* [3] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } STATUS_P3;
  union                                            /* Offset=0x1444 : TX_IPG_LENGTH_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TX_IPG_LENGTH:5;                            /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } TX_IPG_LENGTH_P3;
  union                                            /* Offset=0x1448 : EEE_CTL_STAT_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_AUTO:1;                                 /* [0] */
      __IO unsigned long   LPI_REQ:1;                                  /* [1] */
      __IO unsigned long   LPI_TXHOLD:1;                               /* [2] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __I  unsigned long   ST_LPI_REQ:1;                               /* [8] */
      __I  unsigned long   ST_LPI_TXHOLD:1;                            /* [9] */
      __I  unsigned long   ST_TXBUSY:1;                                /* [10] */
      __I  unsigned long   ST_TXAVAIL:1;                               /* [11] */
      __I  unsigned long   ST_LPI_IND:1;                               /* [12] */
      __IO unsigned long   :3;                                         /* [15:13] */
      __I  unsigned long   STLH_LPI_REQ:1;                             /* [16] */
      __I  unsigned long   STLH_LPI_TXHOLD:1;                          /* [17] */
      __I  unsigned long   STLH_TXBUSY:1;                              /* [18] */
      __IO unsigned long   :1;                                         /* [19] */
      __I  unsigned long   STLH_LPI_IND:1;                             /* [20] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } EEE_CTL_STAT_P3;
  union                                            /* Offset=0x144C : EEE_IDLE_TIME_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_IDLE_TIME_P3:32;                        /* [31:0] */
    } BIT;
  } EEE_IDLE_TIME_P3;
  union                                            /* Offset=0x1450 : EEE_TWSYS_TIME_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EEE_TWSYS_TIME_P3:32;                       /* [31:0] */
    } BIT;
  } EEE_TWSYS_TIME_P3;
  union                                            /* Offset=0x1454 : IDLE_SLOPE_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IDLE_SLOPE:11;                              /* [10:0] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } IDLE_SLOPE_P3;
  char                     wk_1458[0x0010];
  union                                            /* Offset=0x1468 : aFramesTransmittedOK_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesTransmittedOK_P3:32;                 /* [31:0] */
    } BIT;
  } aFramesTransmittedOK_P3;
  union                                            /* Offset=0x146C : aFramesReceivedOK_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesReceivedOK_P3:32;                    /* [31:0] */
    } BIT;
  } aFramesReceivedOK_P3;
  union                                            /* Offset=0x1470 : aFrameCheckSequenceErrors_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFrameCheckSequenceErrors_P3:32;            /* [31:0] */
    } BIT;
  } aFrameCheckSequenceErrors_P3;
  union                                            /* Offset=0x1474 : aAlignmentErrors_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aAlignmentErrors_P3:32;                     /* [31:0] */
    } BIT;
  } aAlignmentErrors_P3;
  union                                            /* Offset=0x1478 : aOctetsTransmittedOK_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aOctetsTransmittedOK_P3:32;                 /* [31:0] */
    } BIT;
  } aOctetsTransmittedOK_P3;
  union                                            /* Offset=0x147C : aOctetsReceivedOK_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aOctetsReceivedOK_P3:32;                    /* [31:0] */
    } BIT;
  } aOctetsReceivedOK_P3;
  union                                            /* Offset=0x1480 : aTxPAUSEMACCtrlFrames_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aTxPAUSEMACCtrlFrames_P3:32;                /* [31:0] */
    } BIT;
  } aTxPAUSEMACCtrlFrames_P3;
  union                                            /* Offset=0x1484 : aRxPAUSEMACCtrlFrames_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aRxPAUSEMACCtrlFrames_P3:32;                /* [31:0] */
    } BIT;
  } aRxPAUSEMACCtrlFrames_P3;
  union                                            /* Offset=0x1488 : ifInErrors_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInErrors_P3:32;                           /* [31:0] */
    } BIT;
  } ifInErrors_P3;
  union                                            /* Offset=0x148C : ifOutErrors_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutErrors_P3:32;                          /* [31:0] */
    } BIT;
  } ifOutErrors_P3;
  union                                            /* Offset=0x1490 : ifInUcastPkts_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInUcastPkts_P3:32;                        /* [31:0] */
    } BIT;
  } ifInUcastPkts_P3;
  union                                            /* Offset=0x1494 : ifInMulticastPkts_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInMulticastPkts_P3:32;                    /* [31:0] */
    } BIT;
  } ifInMulticastPkts_P3;
  union                                            /* Offset=0x1498 : ifInBroadcastPkts_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInBroadcastPkts_P3:32;                    /* [31:0] */
    } BIT;
  } ifInBroadcastPkts_P3;
  union                                            /* Offset=0x149C : ifOutDiscards_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutDiscards_P3:32;                        /* [31:0] */
    } BIT;
  } ifOutDiscards_P3;
  union                                            /* Offset=0x14A0 : ifOutUcastPkts_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutUcastPkts_P3:32;                       /* [31:0] */
    } BIT;
  } ifOutUcastPkts_P3;
  union                                            /* Offset=0x14A4 : ifOutMulticastPkts_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutMulticastPkts_P3:32;                   /* [31:0] */
    } BIT;
  } ifOutMulticastPkts_P3;
  union                                            /* Offset=0x14A8 : ifOutBroadcastPkts_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutBroadcastPkts_P3:32;                   /* [31:0] */
    } BIT;
  } ifOutBroadcastPkts_P3;
  union                                            /* Offset=0x14AC : etherStatsDropEvents_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsDropEvents_P3:32;                 /* [31:0] */
    } BIT;
  } etherStatsDropEvents_P3;
  union                                            /* Offset=0x14B0 : etherStatsOctets_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsOctets_P3:32;                     /* [31:0] */
    } BIT;
  } etherStatsOctets_P3;
  union                                            /* Offset=0x14B4 : etherStatsPkts_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts_P3:32;                       /* [31:0] */
    } BIT;
  } etherStatsPkts_P3;
  union                                            /* Offset=0x14B8 : etherStatsUndersizePkts_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsUndersizePkts_P3:32;              /* [31:0] */
    } BIT;
  } etherStatsUndersizePkts_P3;
  union                                            /* Offset=0x14BC : etherStatsOversizePkts_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsOversizePkts_P3:32;               /* [31:0] */
    } BIT;
  } etherStatsOversizePkts_P3;
  union                                            /* Offset=0x14C0 : etherStatsPkts64Octets_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts64Octets_P3:32;               /* [31:0] */
    } BIT;
  } etherStatsPkts64Octets_P3;
  union                                            /* Offset=0x14C4 : etherStatsPkts65to127Octets_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts65to127Octets_P3:32;          /* [31:0] */
    } BIT;
  } etherStatsPkts65to127Octets_P3;
  union                                            /* Offset=0x14C8 : etherStatsPkts128to255Octets_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts128to255Octets_P3:32;         /* [31:0] */
    } BIT;
  } etherStatsPkts128to255Octets_P3;
  union                                            /* Offset=0x14CC : etherStatsPkts256to511Octets_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts256to511Octets_P3:32;         /* [31:0] */
    } BIT;
  } etherStatsPkts256to511Octets_P3;
  union                                            /* Offset=0x14D0 : etherStatsPkts512to1023Octets_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts512to1023Octets_P3:32;        /* [31:0] */
    } BIT;
  } etherStatsPkts512to1023Octets_P3;
  union                                            /* Offset=0x14D4 : etherStatsPkts1024to1518Octets_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts1024to1518Octets_P3:32;       /* [31:0] */
    } BIT;
  } etherStatsPkts1024to1518Octets_P3;
  union                                            /* Offset=0x14D8 : etherStatsPkts1519toXOctets_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts1519toXOctets_P3:32;          /* [31:0] */
    } BIT;
  } etherStatsPkts1519toXOctets_P3;
  union                                            /* Offset=0x14DC : etherStatsJabbers_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsJabbers_P3:32;                    /* [31:0] */
    } BIT;
  } etherStatsJabbers_P3;
  union                                            /* Offset=0x14E0 : etherStatsFragments_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsFragments_P3:32;                  /* [31:0] */
    } BIT;
  } etherStatsFragments_P3;
  char                     wk_14E4[0x0004];
  union                                            /* Offset=0x14E8 : VLANReceivedOK_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VLANReceivedOK_P3:32;                       /* [31:0] */
    } BIT;
  } VLANReceivedOK_P3;
  char                     wk_14EC[0x0008];
  union                                            /* Offset=0x14F4 : VLANTransmittedOK_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VLANTransmittedOK_P3:32;                    /* [31:0] */
    } BIT;
  } VLANTransmittedOK_P3;
  union                                            /* Offset=0x14F8 : FramesRetransmitted_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   FramesRetransmitted_P3:32;                  /* [31:0] */
    } BIT;
  } FramesRetransmitted_P3;
  char                     wk_14FC[0x0004];
  union                                            /* Offset=0x1500 : STATS_HIWORD_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   STATS_HIWORD_P3:32;                         /* [31:0] */
    } BIT;
  } STATS_HIWORD_P3;
  union                                            /* Offset=0x1504 : STATS_CTRL_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClearALL:1;                                 /* [0] */
      __I  unsigned long   ClearBusy:1;                                /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } STATS_CTRL_P3;
  union                                            /* Offset=0x1508 : STATS_CLEAR_VALUELO_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   STATS_CLEAR_VALUELO_P3:32;                  /* [31:0] */
    } BIT;
  } STATS_CLEAR_VALUELO_P3;
  union                                            /* Offset=0x150C : STATS_CLEAR_VALUEHI_P3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   STATS_CLEAR_VALUEHI_P3:32;                  /* [31:0] */
    } BIT;
  } STATS_CLEAR_VALUEHI_P3;
  union                                            /* Offset=0x1510 : aDeferred_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aDeferred_P3:32;                            /* [31:0] */
    } BIT;
  } aDeferred_P3;
  union                                            /* Offset=0x1514 : aMultipleCollisions_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aMultipleCollisions_P3:32;                  /* [31:0] */
    } BIT;
  } aMultipleCollisions_P3;
  union                                            /* Offset=0x1518 : aSingleCollisions_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aSingleCollisions_P3:32;                    /* [31:0] */
    } BIT;
  } aSingleCollisions_P3;
  union                                            /* Offset=0x151C : aLateCollisions_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aLateCollisions_P3:32;                      /* [31:0] */
    } BIT;
  } aLateCollisions_P3;
  union                                            /* Offset=0x1520 : aExcessiveCollisions_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aExcessiveCollisions_P3:32;                 /* [31:0] */
    } BIT;
  } aExcessiveCollisions_P3;
  union                                            /* Offset=0x1524 : aCarrierSenseErrors_P3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aCarrierSenseErrors_P3:32;                  /* [31:0] */
    } BIT;
  } aCarrierSenseErrors_P3;
  char                     wk_1528[0x02D8];
  union                                            /* Offset=0x1800 : REV_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   REV:32;                                     /* [31:0] */
    } BIT;
  } REV_P4;
  char                     wk_1804[0x0004];
  union                                            /* Offset=0x1808 : COMMAND_CONFIG_P4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TX_ENA:1;                                   /* [0] */
      __IO unsigned long   RX_ENA:1;                                   /* [1] */
      __IO unsigned long   :1;                                         /* [2] */
      __IO unsigned long   ETH_SPEED:1;                                /* [3] */
      __I  unsigned long   PROMIS_EN:1;                                /* [4] */
      __I  unsigned long   PAD_EN:1;                                   /* [5] */
      __IO unsigned long   CRC_FWD:1;                                  /* [6] */
      __I  unsigned long   PAUSE_FWD:1;                                /* [7] */
      __IO unsigned long   PAUSE_IGNORE:1;                             /* [8] */
      __I  unsigned long   TX_ADDR_INS:1;                              /* [9] */
      __IO unsigned long   HD_ENA:1;                                   /* [10] */
      __IO unsigned long   TX_CRC_APPEND:1;                            /* [11] */
      __IO unsigned long   :1;                                         /* [12] */
      __IO unsigned long   SW_RESET:1;                                 /* [13] */
      __IO unsigned long   :1;                                         /* [14] */
      __IO unsigned long   LOOP_ENA:1;                                 /* [15] */
      __IO unsigned long   :7;                                         /* [22:16] */
      __IO unsigned long   CNTL_FRM_ENA:1;                             /* [23] */
      __IO unsigned long   NO_LGTH_CHECK:1;                            /* [24] */
      __IO unsigned long   ENA_10:1;                                   /* [25] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } COMMAND_CONFIG_P4;
  char                     wk_180C[0x0008];
  union                                            /* Offset=0x1814 : FRM_LENGTH_P4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FRM_LENGTH:14;                              /* [13:0] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } FRM_LENGTH_P4;
  union                                            /* Offset=0x1818 : PAUSE_QUANT_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PAUSE_QUANT:16;                             /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } PAUSE_QUANT_P4;
  char                     wk_181C[0x0024];
  union                                            /* Offset=0x1840 : STATUS_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PHYSPEED:2;                                 /* [1:0] */
      __I  unsigned long   PHYLINK:1;                                  /* [2] */
      __I  unsigned long   PHYDUPLEX:1;                                /* [3] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } STATUS_P4;
  union                                            /* Offset=0x1844 : TX_IPG_LENGTH_P4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TX_IPG_LENGTH:5;                            /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } TX_IPG_LENGTH_P4;
  char                     wk_1848[0x000C];
  union                                            /* Offset=0x1854 : IDLE_SLOPE_P4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IDLE_SLOPE:11;                              /* [10:0] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } IDLE_SLOPE_P4;
  char                     wk_1858[0x0010];
  union                                            /* Offset=0x1868 : aFramesTransmittedOK_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesTransmittedOK_P4:32;                 /* [31:0] */
    } BIT;
  } aFramesTransmittedOK_P4;
  union                                            /* Offset=0x186C : aFramesReceivedOK_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFramesReceivedOK_P4:32;                    /* [31:0] */
    } BIT;
  } aFramesReceivedOK_P4;
  union                                            /* Offset=0x1870 : aFrameCheckSequenceErrors_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aFrameCheckSequenceErrors_P4:32;            /* [31:0] */
    } BIT;
  } aFrameCheckSequenceErrors_P4;
  union                                            /* Offset=0x1874 : aAlignmentErrors_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aAlignmentErrors_P4:32;                     /* [31:0] */
    } BIT;
  } aAlignmentErrors_P4;
  union                                            /* Offset=0x1878 : aOctetsTransmittedOK_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aOctetsTransmittedOK_P4:32;                 /* [31:0] */
    } BIT;
  } aOctetsTransmittedOK_P4;
  union                                            /* Offset=0x187C : aOctetsReceivedOK_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aOctetsReceivedOK_P4:32;                    /* [31:0] */
    } BIT;
  } aOctetsReceivedOK_P4;
  union                                            /* Offset=0x1880 : aTxPAUSEMACCtrlFrames_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aTxPAUSEMACCtrlFrames_P4:32;                /* [31:0] */
    } BIT;
  } aTxPAUSEMACCtrlFrames_P4;
  union                                            /* Offset=0x1884 : aRxPAUSEMACCtrlFrames_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   aRxPAUSEMACCtrlFrames_P4:32;                /* [31:0] */
    } BIT;
  } aRxPAUSEMACCtrlFrames_P4;
  union                                            /* Offset=0x1888 : ifInErrors_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInErrors_P4:32;                           /* [31:0] */
    } BIT;
  } ifInErrors_P4;
  union                                            /* Offset=0x188C : ifOutErrors_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutErrors_P4:32;                          /* [31:0] */
    } BIT;
  } ifOutErrors_P4;
  union                                            /* Offset=0x1890 : ifInUcastPkts_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInUcastPkts_P4:32;                        /* [31:0] */
    } BIT;
  } ifInUcastPkts_P4;
  union                                            /* Offset=0x1894 : ifInMulticastPkts_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInMulticastPkts_P4:32;                    /* [31:0] */
    } BIT;
  } ifInMulticastPkts_P4;
  union                                            /* Offset=0x1898 : ifInBroadcastPkts_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifInBroadcastPkts_P4:32;                    /* [31:0] */
    } BIT;
  } ifInBroadcastPkts_P4;
  union                                            /* Offset=0x189C : ifOutDiscards_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutDiscards_P4:32;                        /* [31:0] */
    } BIT;
  } ifOutDiscards_P4;
  union                                            /* Offset=0x18A0 : ifOutUcastPkts_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutUcastPkts_P4:32;                       /* [31:0] */
    } BIT;
  } ifOutUcastPkts_P4;
  union                                            /* Offset=0x18A4 : ifOutMulticastPkts_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutMulticastPkts_P4:32;                   /* [31:0] */
    } BIT;
  } ifOutMulticastPkts_P4;
  union                                            /* Offset=0x18A8 : ifOutBroadcastPkts_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ifOutBroadcastPkts_P4:32;                   /* [31:0] */
    } BIT;
  } ifOutBroadcastPkts_P4;
  union                                            /* Offset=0x18AC : etherStatsDropEvents_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsDropEvents_P4:32;                 /* [31:0] */
    } BIT;
  } etherStatsDropEvents_P4;
  union                                            /* Offset=0x18B0 : etherStatsOctets_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsOctets_P4:32;                     /* [31:0] */
    } BIT;
  } etherStatsOctets_P4;
  union                                            /* Offset=0x18B4 : etherStatsPkts_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts_P4:32;                       /* [31:0] */
    } BIT;
  } etherStatsPkts_P4;
  union                                            /* Offset=0x18B8 : etherStatsUndersizePkts_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsUndersizePkts_P4:32;              /* [31:0] */
    } BIT;
  } etherStatsUndersizePkts_P4;
  union                                            /* Offset=0x18BC : etherStatsOversizePkts_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsOversizePkts_P4:32;               /* [31:0] */
    } BIT;
  } etherStatsOversizePkts_P4;
  union                                            /* Offset=0x18C0 : etherStatsPkts64Octets_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts64Octets_P4:32;               /* [31:0] */
    } BIT;
  } etherStatsPkts64Octets_P4;
  union                                            /* Offset=0x18C4 : etherStatsPkts65to127Octets_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts65to127Octets_P4:32;          /* [31:0] */
    } BIT;
  } etherStatsPkts65to127Octets_P4;
  union                                            /* Offset=0x18C8 : etherStatsPkts128to255Octets_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts128to255Octets_P4:32;         /* [31:0] */
    } BIT;
  } etherStatsPkts128to255Octets_P4;
  union                                            /* Offset=0x18CC : etherStatsPkts256to511Octets_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts256to511Octets_P4:32;         /* [31:0] */
    } BIT;
  } etherStatsPkts256to511Octets_P4;
  union                                            /* Offset=0x18D0 : etherStatsPkts512to1023Octets_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts512to1023Octets_P4:32;        /* [31:0] */
    } BIT;
  } etherStatsPkts512to1023Octets_P4;
  union                                            /* Offset=0x18D4 : etherStatsPkts1024to1518Octets_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts1024to1518Octets_P4:32;       /* [31:0] */
    } BIT;
  } etherStatsPkts1024to1518Octets_P4;
  union                                            /* Offset=0x18D8 : etherStatsPkts1519toXOctets_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsPkts1519toXOctets_P4:32;          /* [31:0] */
    } BIT;
  } etherStatsPkts1519toXOctets_P4;
  union                                            /* Offset=0x18DC : etherStatsJabbers_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsJabbers_P4:32;                    /* [31:0] */
    } BIT;
  } etherStatsJabbers_P4;
  union                                            /* Offset=0x18E0 : etherStatsFragments_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   etherStatsFragments_P4:32;                  /* [31:0] */
    } BIT;
  } etherStatsFragments_P4;
  char                     wk_18E4[0x0004];
  union                                            /* Offset=0x18E8 : VLANReceivedOK_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VLANReceivedOK_P4:32;                       /* [31:0] */
    } BIT;
  } VLANReceivedOK_P4;
  char                     wk_18EC[0x0008];
  union                                            /* Offset=0x18F4 : VLANTransmittedOK_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VLANTransmittedOK_P4:32;                    /* [31:0] */
    } BIT;
  } VLANTransmittedOK_P4;
  union                                            /* Offset=0x18F8 : FramesRetransmitted_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   FramesRetransmitted_P4:32;                  /* [31:0] */
    } BIT;
  } FramesRetransmitted_P4;
  char                     wk_18FC[0x0004];
  union                                            /* Offset=0x1900 : STATS_HIWORD_P4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   STATS_HIWORD_P4:32;                         /* [31:0] */
    } BIT;
  } STATS_HIWORD_P4;
  union                                            /* Offset=0x1904 : STATS_CTRL_P4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ClearALL:1;                                 /* [0] */
      __I  unsigned long   ClearBusy:1;                                /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } STATS_CTRL_P4;
  union                                            /* Offset=0x1908 : STATS_CLEAR_VALUELO_P4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   STATS_CLEAR_VALUELO_P4:32;                  /* [31:0] */
    } BIT;
  } STATS_CLEAR_VALUELO_P4;
  union                                            /* Offset=0x190C : STATS_CLEAR_VALUEHI_P4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   STATS_CLEAR_VALUEHI_P4:32;                  /* [31:0] */
    } BIT;
  } STATS_CLEAR_VALUEHI_P4;
  char                     wk_1910[0x22F0];
  union                                            /* Offset=0x3C00 : DLR_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ENABLE:1;                                   /* [0] */
      __IO unsigned long   AUTOFLUSH:1;                                /* [1] */
      __IO unsigned long   :2;                                         /* [3:2] */
      __IO unsigned long   IGNORE_INVTM:1;                             /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   US_TIME:12;                                 /* [19:8] */
      __IO unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } DLR_CONTROL;
  union                                            /* Offset=0x3C04 : DLR_STATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   LastBcnRcvPort:2;                           /* [1:0] */
      __I  unsigned long   :6;                                         /* [7:2] */
      __I  unsigned long   NODE_STATE:8;                               /* [15:8] */
      __I  unsigned long   LINK_STATUS:2;                              /* [17:16] */
      __I  unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   TOPOLOGY:8;                                 /* [31:24] */
    } BIT;
  } DLR_STATUS;
  union                                            /* Offset=0x3C08 : DLR_ETH_TYP */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DLR_ETH_TYP:16;                             /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } DLR_ETH_TYP;
  union                                            /* Offset=0x3C0C : DLR_IRQ_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IRQ_state_chng_ena:1;                       /* [0] */
      __IO unsigned long   IRQ_flush_macaddr_ena:1;                    /* [1] */
      __IO unsigned long   IRQ_stop_nbchk0_ena:1;                      /* [2] */
      __IO unsigned long   IRQ_stop_nbchk1_ena:1;                      /* [3] */
      __IO unsigned long   IRQ_bec_tmr0_exp_ena:1;                     /* [4] */
      __IO unsigned long   IRQ_bec_tmr1_exp_ena:1;                     /* [5] */
      __IO unsigned long   IRQ_supr_chng_ena:1;                        /* [6] */
      __IO unsigned long   IRQ_link_chng0_ena:1;                       /* [7] */
      __IO unsigned long   IRQ_link_chng1_ena:1;                       /* [8] */
      __IO unsigned long   IRQ_sup_ignord_ena:1;                       /* [9] */
      __IO unsigned long   IRQ_ip_addr_chng_ena:1;                     /* [10] */
      __IO unsigned long   IRQ_invalid_tmr_ena:1;                      /* [11] */
      __IO unsigned long   IRQ_bec_rcv0_ena:1;                         /* [12] */
      __IO unsigned long   IRQ_bec_rcv1_ena:1;                         /* [13] */
      __IO unsigned long   IRQ_frm_dscrd0:1;                           /* [14] */
      __IO unsigned long   IRQ_frm_dscrd1:1;                           /* [15] */
      __IO unsigned long   :13;                                        /* [28:16] */
      __IO unsigned long   low_int_en:1;                               /* [29] */
      __IO unsigned long   atomic_OR:1;                                /* [30] */
      __IO unsigned long   atomic_AND:1;                               /* [31] */
    } BIT;
  } DLR_IRQ_CONTROL;
  union                                            /* Offset=0x3C10 : DLR_IRQ_STAT_ACK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   state_chng_IRQ_pending:1;                   /* [0] */
      __IO unsigned long   flush_IRQ_pending:1;                        /* [1] */
      __IO unsigned long   nbchk0_IRQ_pending:1;                       /* [2] */
      __IO unsigned long   nbchk1_IRQ_pending:1;                       /* [3] */
      __IO unsigned long   bec_tmr0_IRQ_pending:1;                     /* [4] */
      __IO unsigned long   bec_tmr1_IRQ_pending:1;                     /* [5] */
      __IO unsigned long   supr_chng_IRQ_pending:1;                    /* [6] */
      __IO unsigned long   Link0_IRQ_pending:1;                        /* [7] */
      __IO unsigned long   Link1_IRQ_pending:1;                        /* [8] */
      __IO unsigned long   sup_ignord_IRQ_pending:1;                   /* [9] */
      __IO unsigned long   ip_chng_IRQ_pending:1;                      /* [10] */
      __IO unsigned long   invalid_tmr_IRQ_pending:1;                  /* [11] */
      __IO unsigned long   bec_rcv0_IRQ_pending:1;                     /* [12] */
      __IO unsigned long   bec_rcv1_IRQ_pending:1;                     /* [13] */
      __IO unsigned long   frm_dscrd0_IRQ_pending:1;                   /* [14] */
      __IO unsigned long   frm_dscrd1_IRQ_pending:1;                   /* [15] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } DLR_IRQ_STAT_ACK;
  union                                            /* Offset=0x3C14 : DLR_LOC_MAClo */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   LOC_MAC:32;                                 /* [31:0] */
    } BIT;
  } DLR_LOC_MAClo;
  union                                            /* Offset=0x3C18 : DLR_LOC_MAChi */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   LOC_MAC:16;                                 /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } DLR_LOC_MAChi;
  char                     wk_3C1C[0x0004];
  union                                            /* Offset=0x3C20 : DLR_SUPR_MAClo */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SUPR_MAC:32;                                /* [31:0] */
    } BIT;
  } DLR_SUPR_MAClo;
  union                                            /* Offset=0x3C24 : DLR_SUPR_MAChi */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SUPR_MAC:16;                                /* [15:0] */
      __I  unsigned long   PRECE:8;                                    /* [23:16] */
      __I  unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } DLR_SUPR_MAChi;
  union                                            /* Offset=0x3C28 : DLR_STATE_VLAN */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RINGSTAT:8;                                 /* [7:0] */
      __I  unsigned long   VLANVALID:1;                                /* [8] */
      __I  unsigned long   :7;                                         /* [15:9] */
      __I  unsigned long   VLANTAG:16;                                 /* [31:16] */
    } BIT;
  } DLR_STATE_VLAN;
  union                                            /* Offset=0x3C2C : DLR_BEC_TMOUT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   BEC_TMOUT:32;                               /* [31:0] */
    } BIT;
  } DLR_BEC_TMOUT;
  union                                            /* Offset=0x3C30 : DLR_BEC_INTRVL */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   BEC_INTRVL:32;                              /* [31:0] */
    } BIT;
  } DLR_BEC_INTRVL;
  union                                            /* Offset=0x3C34 : DLR_SUPR_IPADR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SUPR_IPADR:32;                              /* [31:0] */
    } BIT;
  } DLR_SUPR_IPADR;
  union                                            /* Offset=0x3C38 : DLR_ETH_STYP_VER */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SUBTYPE:8;                                  /* [7:0] */
      __I  unsigned long   PROTVER:8;                                  /* [15:8] */
      __I  unsigned long   SPORT:8;                                    /* [23:16] */
      __I  unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } DLR_ETH_STYP_VER;
  union                                            /* Offset=0x3C3C : DLR_INV_TMOUT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   INV_TMOUT:32;                               /* [31:0] */
    } BIT;
  } DLR_INV_TMOUT;
  union                                            /* Offset=0x3C40 : DLR_SEQ_ID */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SEQ_ID:32;                                  /* [31:0] */
    } BIT;
  } DLR_SEQ_ID;
  char                     wk_3C44[0x0014];
  union                                            /* Offset=0x3C58 : DLR_DSTlo */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DLR_DST:32;                                 /* [31:0] */
    } BIT;
  } DLR_DSTlo;
  union                                            /* Offset=0x3C5C : DLR_DSThi */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DLR_DST:16;                                 /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } DLR_DSThi;
  union                                            /* Offset=0x3C60 : DLR_RX_STAT0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RX_STAT0:32;                                /* [31:0] */
    } BIT;
  } DLR_RX_STAT0;
  union                                            /* Offset=0x3C64 : DLR_RX_ERR_STAT0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RX_ERR_STAT0:32;                            /* [31:0] */
    } BIT;
  } DLR_RX_ERR_STAT0;
  union                                            /* Offset=0x3C68 : DLR_TX_STAT0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TX_STAT0:32;                                /* [31:0] */
    } BIT;
  } DLR_TX_STAT0;
  char                     wk_3C6C[0x0004];
  union                                            /* Offset=0x3C70 : DLR_RX_STAT1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RX_STAT1:32;                                /* [31:0] */
    } BIT;
  } DLR_RX_STAT1;
  union                                            /* Offset=0x3C74 : DLR_RX_ERR_STAT1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RX_ERR_STAT1:32;                            /* [31:0] */
    } BIT;
  } DLR_RX_ERR_STAT1;
  union                                            /* Offset=0x3C78 : DLR_TX_STAT1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TX_STAT1:32;                                /* [31:0] */
    } BIT;
  } DLR_TX_STAT1;
  char                     wk_3C7C[0x0084];
  union                                            /* Offset=0x3D00 : PRP_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRP_ENA:1;                                  /* [0] */
      __IO unsigned long   RX_DUP_ACCEPT:1;                            /* [1] */
      __IO unsigned long   RX_REMOVE_RCT:1;                            /* [2] */
      __IO unsigned long   TX_RCT_MODE:2;                              /* [4:3] */
      __IO unsigned long   TX_RCT_BROADCAST:1;                         /* [5] */
      __IO unsigned long   TX_RCT_MULTICAST:1;                         /* [6] */
      __IO unsigned long   TX_RCT_UNKNOWN:1;                           /* [7] */
      __IO unsigned long   TX_RCT_1588:1;                              /* [8] */
      __IO unsigned long   :7;                                         /* [15:9] */
      __IO unsigned long   PRP_AGE_ENA:1;                              /* [16] */
      __IO unsigned long   :15;                                        /* [31:17] */
    } BIT;
  } PRP_CONFIG;
  union                                            /* Offset=0x3D04 : PRP_GROUP */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRP_GROUP:4;                                /* [3:0] */
      __IO unsigned long   :12;                                        /* [15:4] */
      __IO unsigned long   LANB_MASK:4;                                /* [19:16] */
      __IO unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } PRP_GROUP;
  union                                            /* Offset=0x3D08 : PRP_SUFFIX */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRP_SUFFIX:16;                              /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } PRP_SUFFIX;
  union                                            /* Offset=0x3D0C : PRP_LANID */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   LANAID:4;                                   /* [3:0] */
      __IO unsigned long   LANBID:4;                                   /* [7:4] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } PRP_LANID;
  union                                            /* Offset=0x3D10 : DUP_W */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DUP_W:9;                                    /* [8:0] */
      __IO unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } DUP_W;
  union                                            /* Offset=0x3D14 : PRP_AGETIME */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRP_AGETIME:24;                             /* [23:0] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } PRP_AGETIME;
  union                                            /* Offset=0x3D18 : PRP_IRQ_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MEMTOOLATE:1;                               /* [0] */
      __IO unsigned long   WRONGLAN:1;                                 /* [1] */
      __IO unsigned long   OUTOFSEQ:1;                                 /* [2] */
      __IO unsigned long   SEQMISSING:1;                               /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } PRP_IRQ_CONTROL;
  union                                            /* Offset=0x3D1C : PRP_IRQ_STAT_ACK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MEMTOOLATE:1;                               /* [0] */
      __IO unsigned long   WRONGLAN:1;                                 /* [1] */
      __IO unsigned long   OUTOFSEQ:1;                                 /* [2] */
      __IO unsigned long   SEQMISSING:1;                               /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } PRP_IRQ_STAT_ACK;
  union                                            /* Offset=0x3D20 : RM_ADDR_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   address:13;                                 /* [12:0] */
      __IO unsigned long   :9;                                         /* [21:13] */
      __IO unsigned long   CLEAR_DYNAMIC:1;                            /* [22] */
      __IO unsigned long   CLEAR_MEMORY:1;                             /* [23] */
      __IO unsigned long   :1;                                         /* [24] */
      __IO unsigned long   WRITE:1;                                    /* [25] */
      __IO unsigned long   READ:1;                                     /* [26] */
      __IO unsigned long   :2;                                         /* [28:27] */
      __IO unsigned long   CLEAR:1;                                    /* [29] */
      __IO unsigned long   :1;                                         /* [30] */
      __I  unsigned long   BUSY:1;                                     /* [31] */
    } BIT;
  } RM_ADDR_CTRL;
  union                                            /* Offset=0x3D24 : RM_DATA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RM_DATA:32;                                 /* [31:0] */
    } BIT;
  } RM_DATA;
  char                     wk_3D28[0x0004];
  union                                            /* Offset=0x3D2C : RM_STATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ageaddress:16;                              /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RM_STATUS;
  union                                            /* Offset=0x3D30 : TxSeqTooLate */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TxSeqTooLate:5;                             /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } TxSeqTooLate;
  union                                            /* Offset=0x3D34 : CntErrWrongLanA */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CntErrWrongLanA:32;                         /* [31:0] */
    } BIT;
  } CntErrWrongLanA;
  union                                            /* Offset=0x3D38 : CntErrWrongLanB */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CntErrWrongLanB:32;                         /* [31:0] */
    } BIT;
  } CntErrWrongLanB;
  union                                            /* Offset=0x3D3C : CntDupLanA */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CntDupLanA:32;                              /* [31:0] */
    } BIT;
  } CntDupLanA;
  union                                            /* Offset=0x3D40 : CntDupLanB */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CntDupLanB:32;                              /* [31:0] */
    } BIT;
  } CntDupLanB;
  union                                            /* Offset=0x3D44 : CntOutOfSeqLowA */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CntOutOfSeqLowA:32;                         /* [31:0] */
    } BIT;
  } CntOutOfSeqLowA;
  union                                            /* Offset=0x3D48 : CntOutOfSeqLowB */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CntOutOfSeqLowB:32;                         /* [31:0] */
    } BIT;
  } CntOutOfSeqLowB;
  union                                            /* Offset=0x3D4C : CntOutOfSeqA */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CntOutOfSeqA:32;                            /* [31:0] */
    } BIT;
  } CntOutOfSeqA;
  union                                            /* Offset=0x3D50 : CntOutOfSeqB */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CntOutOfSeqB:32;                            /* [31:0] */
    } BIT;
  } CntOutOfSeqB;
  union                                            /* Offset=0x3D54 : CntAcceptA */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CntAcceptA:32;                              /* [31:0] */
    } BIT;
  } CntAcceptA;
  union                                            /* Offset=0x3D58 : CntAcceptB */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CntAcceptB:32;                              /* [31:0] */
    } BIT;
  } CntAcceptB;
  union                                            /* Offset=0x3D5C : CntMissing */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CntMissing:32;                              /* [31:0] */
    } BIT;
  } CntMissing;
  char                     wk_3D60[0x00A0];
  union                                            /* Offset=0x3E00 : HUB_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HUB_ENA:1;                                  /* [0] */
      __IO unsigned long   RETRANSMIT_ENA:1;                           /* [1] */
      __IO unsigned long   TRIGGER_MODE:1;                             /* [2] */
      __IO unsigned long   HUB_ISOLATE:1;                              /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } HUB_CONFIG;
  union                                            /* Offset=0x3E04 : HUB_GROUP */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HUB_GROUP:4;                                /* [3:0] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } HUB_GROUP;
  union                                            /* Offset=0x3E08 : HUB_DEFPORT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HUB_DEFPORT:4;                              /* [3:0] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } HUB_DEFPORT;
  union                                            /* Offset=0x3E0C : HUB_TRIGGER_IMMEDIATE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HUB_TRIGGER_IMMEDIATE:4;                    /* [3:0] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } HUB_TRIGGER_IMMEDIATE;
  union                                            /* Offset=0x3E10 : HUB_TRIGGER_AT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HUB_TRIGGER_AT:4;                           /* [3:0] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } HUB_TRIGGER_AT;
  union                                            /* Offset=0x3E14 : HUB_TTIME */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HUB_TTIME:32;                               /* [31:0] */
    } BIT;
  } HUB_TTIME;
  union                                            /* Offset=0x3E18 : HUB_IRQ_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RX_TRIGGER:4;                               /* [3:0] */
      __IO unsigned long   CHANGE_DET:1;                               /* [4] */
      __IO unsigned long   TRIGGER_IMMEDIATE_ACK:1;                    /* [5] */
      __IO unsigned long   TRIGGER_TIMER_ACK:1;                        /* [6] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } HUB_IRQ_CONTROL;
  union                                            /* Offset=0x3E1C : HUB_IRQ_STAT_ACK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RX_TRIGGER:4;                               /* [3:0] */
      __IO unsigned long   CHANGE_DET:1;                               /* [4] */
      __IO unsigned long   TRIGGER_IMMEDIATE_ACK:1;                    /* [5] */
      __IO unsigned long   TRIGGER_TIMER_ACK:1;                        /* [6] */
      __IO unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } HUB_IRQ_STAT_ACK;
  union                                            /* Offset=0x3E20 : HUB_STATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PORTS_ACTIVE:4;                             /* [3:0] */
      __I  unsigned long   :5;                                         /* [8:4] */
      __I  unsigned long   TX_ACTIVE:1;                                /* [9] */
      __I  unsigned long   TX_BUSY:1;                                  /* [10] */
      __I  unsigned long   Speed_OK:1;                                 /* [11] */
      __I  unsigned long   TX_Change_Pending:1;                        /* [12] */
      __I  unsigned long   :19;                                        /* [31:13] */
    } BIT;
  } HUB_STATUS;
  union                                            /* Offset=0x3E24 : HUB_OPORT_STATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   HUB_OPORT_STATUS:4;                         /* [3:0] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } HUB_OPORT_STATUS;
  char                     wk_3E28[0x0058];
  union                                            /* Offset=0x3E80 : RXMATCH_CONFIG0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PATTERN_EN:8;                               /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } RXMATCH_CONFIG0;
  union                                            /* Offset=0x3E84 : RXMATCH_CONFIG1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PATTERN_EN:8;                               /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } RXMATCH_CONFIG1;
  union                                            /* Offset=0x3E88 : RXMATCH_CONFIG2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PATTERN_EN:8;                               /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } RXMATCH_CONFIG2;
  union                                            /* Offset=0x3E8C : RXMATCH_CONFIG3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PATTERN_EN:8;                               /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } RXMATCH_CONFIG3;
  union                                            /* Offset=0x3E90 : RXMATCH_CONFIG4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PATTERN_EN:8;                               /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } RXMATCH_CONFIG4;
  char                     wk_3E94[0x001C];
  union                                            /* Offset=0x3EB0 : PATTERN_CTRL0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MATCH_NOT:1;                                /* [0] */
      __IO unsigned long   MGMTFWD:1;                                  /* [1] */
      __IO unsigned long   DISCARD:1;                                  /* [2] */
      __IO unsigned long   SET_PRIO:1;                                 /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   HUBTRIGGER:1;                               /* [8] */
      __IO unsigned long   :3;                                         /* [11:9] */
      __IO unsigned long   PRIORITY:2;                                 /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   PORTMASK:5;                                 /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } PATTERN_CTRL0;
  union                                            /* Offset=0x3EB4 : PATTERN_CTRL1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MATCH_NOT:1;                                /* [0] */
      __IO unsigned long   MGMTFWD:1;                                  /* [1] */
      __IO unsigned long   DISCARD:1;                                  /* [2] */
      __IO unsigned long   SET_PRIO:1;                                 /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   HUBTRIGGER:1;                               /* [8] */
      __IO unsigned long   :3;                                         /* [11:9] */
      __IO unsigned long   PRIORITY:2;                                 /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   PORTMASK:5;                                 /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } PATTERN_CTRL1;
  union                                            /* Offset=0x3EB8 : PATTERN_CTRL2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MATCH_NOT:1;                                /* [0] */
      __IO unsigned long   MGMTFWD:1;                                  /* [1] */
      __IO unsigned long   DISCARD:1;                                  /* [2] */
      __IO unsigned long   SET_PRIO:1;                                 /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   HUBTRIGGER:1;                               /* [8] */
      __IO unsigned long   :3;                                         /* [11:9] */
      __IO unsigned long   PRIORITY:2;                                 /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   PORTMASK:5;                                 /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } PATTERN_CTRL2;
  union                                            /* Offset=0x3EBC : PATTERN_CTRL3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MATCH_NOT:1;                                /* [0] */
      __IO unsigned long   MGMTFWD:1;                                  /* [1] */
      __IO unsigned long   DISCARD:1;                                  /* [2] */
      __IO unsigned long   SET_PRIO:1;                                 /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   HUBTRIGGER:1;                               /* [8] */
      __IO unsigned long   :3;                                         /* [11:9] */
      __IO unsigned long   PRIORITY:2;                                 /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   PORTMASK:5;                                 /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } PATTERN_CTRL3;
  union                                            /* Offset=0x3EC0 : PATTERN_CTRL4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MATCH_NOT:1;                                /* [0] */
      __IO unsigned long   MGMTFWD:1;                                  /* [1] */
      __IO unsigned long   DISCARD:1;                                  /* [2] */
      __IO unsigned long   SET_PRIO:1;                                 /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   HUBTRIGGER:1;                               /* [8] */
      __IO unsigned long   :3;                                         /* [11:9] */
      __IO unsigned long   PRIORITY:2;                                 /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   PORTMASK:5;                                 /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } PATTERN_CTRL4;
  union                                            /* Offset=0x3EC4 : PATTERN_CTRL5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MATCH_NOT:1;                                /* [0] */
      __IO unsigned long   MGMTFWD:1;                                  /* [1] */
      __IO unsigned long   DISCARD:1;                                  /* [2] */
      __IO unsigned long   SET_PRIO:1;                                 /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   HUBTRIGGER:1;                               /* [8] */
      __IO unsigned long   :3;                                         /* [11:9] */
      __IO unsigned long   PRIORITY:2;                                 /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   PORTMASK:5;                                 /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } PATTERN_CTRL5;
  union                                            /* Offset=0x3EC8 : PATTERN_CTRL6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MATCH_NOT:1;                                /* [0] */
      __IO unsigned long   MGMTFWD:1;                                  /* [1] */
      __IO unsigned long   DISCARD:1;                                  /* [2] */
      __IO unsigned long   SET_PRIO:1;                                 /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   HUBTRIGGER:1;                               /* [8] */
      __IO unsigned long   :3;                                         /* [11:9] */
      __IO unsigned long   PRIORITY:2;                                 /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   PORTMASK:5;                                 /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } PATTERN_CTRL6;
  union                                            /* Offset=0x3ECC : PATTERN_CTRL7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MATCH_NOT:1;                                /* [0] */
      __IO unsigned long   MGMTFWD:1;                                  /* [1] */
      __IO unsigned long   DISCARD:1;                                  /* [2] */
      __IO unsigned long   SET_PRIO:1;                                 /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   HUBTRIGGER:1;                               /* [8] */
      __IO unsigned long   :3;                                         /* [11:9] */
      __IO unsigned long   PRIORITY:2;                                 /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   PORTMASK:5;                                 /* [20:16] */
      __IO unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } PATTERN_CTRL7;
  union                                            /* Offset=0x3ED0 : PTN_IRQ_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MATCHINT:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } PTN_IRQ_CONTROL;
  union                                            /* Offset=0x3ED4 : PTN_IRQ_STAT_ACK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MATCHINT:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } PTN_IRQ_STAT_ACK;
  char                     wk_3ED8[0x0004];
  union                                            /* Offset=0x3EDC : PATTERN_SEL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PATTERN_SEL:3;                              /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PATTERN_SEL;
  union                                            /* Offset=0x3EE0 : PTRN_CMP_30 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PTRN_CMP_30:32;                             /* [31:0] */
    } BIT;
  } PTRN_CMP_30;
  union                                            /* Offset=0x3EE4 : PTRN_CMP_74 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PTRN_CMP_74:32;                             /* [31:0] */
    } BIT;
  } PTRN_CMP_74;
  union                                            /* Offset=0x3EE8 : PTRN_CMP_118 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PTRN_CMP_118:32;                            /* [31:0] */
    } BIT;
  } PTRN_CMP_118;
  char                     wk_3EEC[0x0004];
  union                                            /* Offset=0x3EF0 : PTRN_MSK_30 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PTRN_MSK_30:32;                             /* [31:0] */
    } BIT;
  } PTRN_MSK_30;
  union                                            /* Offset=0x3EF4 : PTRN_MSK_74 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PTRN_MSK_74:32;                             /* [31:0] */
    } BIT;
  } PTRN_MSK_74;
  union                                            /* Offset=0x3EF8 : PTRN_MSK_118 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PTRN_MSK_118:32;                            /* [31:0] */
    } BIT;
  } PTRN_MSK_118;
  char                     wk_3EFC[0x0004];
  union                                            /* Offset=0x3F00 : TDMA_CONFIG */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDMA_ENA:1;                                 /* [0] */
      __I  unsigned long   WAIT_START:1;                               /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } TDMA_CONFIG;
  union                                            /* Offset=0x3F04 : TDMA_PORTS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   port0:1;                                    /* [0] */
      __IO unsigned long   port1:1;                                    /* [1] */
      __IO unsigned long   port2:1;                                    /* [2] */
      __IO unsigned long   port3:1;                                    /* [3] */
      __IO unsigned long   port4:1;                                    /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } TDMA_PORTS;
  union                                            /* Offset=0x3F08 : TDMA_START */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDMA_START:32;                              /* [31:0] */
    } BIT;
  } TDMA_START;
  union                                            /* Offset=0x3F0C : TDMA_MODULO */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDMA_MODULO:32;                             /* [31:0] */
    } BIT;
  } TDMA_MODULO;
  union                                            /* Offset=0x3F10 : TDMA_CYCLE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDMA_CYCLE:32;                              /* [31:0] */
    } BIT;
  } TDMA_CYCLE;
  union                                            /* Offset=0x3F14 : TDMA_T1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDMA_T1:32;                                 /* [31:0] */
    } BIT;
  } TDMA_T1;
  union                                            /* Offset=0x3F18 : TDMA_T2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDMA_T2:32;                                 /* [31:0] */
    } BIT;
  } TDMA_T2;
  union                                            /* Offset=0x3F1C : TDMA_T3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TDMA_T3:32;                                 /* [31:0] */
    } BIT;
  } TDMA_T3;
  union                                            /* Offset=0x3F20 : QUEUES_TS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   queue0:1;                                   /* [0] */
      __IO unsigned long   queue1:1;                                   /* [1] */
      __IO unsigned long   queue2:1;                                   /* [2] */
      __IO unsigned long   queue3:1;                                   /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } QUEUES_TS;
  union                                            /* Offset=0x3F24 : QUEUES_T1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   queue0:1;                                   /* [0] */
      __IO unsigned long   queue1:1;                                   /* [1] */
      __IO unsigned long   queue2:1;                                   /* [2] */
      __IO unsigned long   queue3:1;                                   /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } QUEUES_T1;
  union                                            /* Offset=0x3F28 : QUEUES_T2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   queue0:1;                                   /* [0] */
      __IO unsigned long   queue1:1;                                   /* [1] */
      __IO unsigned long   queue2:1;                                   /* [2] */
      __IO unsigned long   queue3:1;                                   /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } QUEUES_T2;
  union                                            /* Offset=0x3F2C : QUEUES_T3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   queue0:1;                                   /* [0] */
      __IO unsigned long   queue1:1;                                   /* [1] */
      __IO unsigned long   queue2:1;                                   /* [2] */
      __IO unsigned long   queue3:1;                                   /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } QUEUES_T3;
  union                                            /* Offset=0x3F30 : QUEUES_START */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   queue0:1;                                   /* [0] */
      __IO unsigned long   queue1:1;                                   /* [1] */
      __IO unsigned long   queue2:1;                                   /* [2] */
      __IO unsigned long   queue3:1;                                   /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } QUEUES_START;
  union                                            /* Offset=0x3F34 : TIME_LOAD_NEXT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TIME_LOAD_NEXT:32;                          /* [31:0] */
    } BIT;
  } TIME_LOAD_NEXT;
  union                                            /* Offset=0x3F38 : TDMA_IRQ_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CYCLE_EN:1;                                 /* [0] */
      __IO unsigned long   T1_EN:1;                                    /* [1] */
      __IO unsigned long   T2_EN:1;                                    /* [2] */
      __IO unsigned long   T3_EN:1;                                    /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } TDMA_IRQ_CONTROL;
  union                                            /* Offset=0x3F3C : TDMA_IRQ_STAT_ACK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CYCLE_EN:1;                                 /* [0] */
      __IO unsigned long   T1_EN:1;                                    /* [1] */
      __IO unsigned long   T2_EN:1;                                    /* [2] */
      __IO unsigned long   T3_EN:1;                                    /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } TDMA_IRQ_STAT_ACK;
} A5PSW_Type;
#endif  /* End of __A5PSW_SFR__DEFINE_HEADER__ */
