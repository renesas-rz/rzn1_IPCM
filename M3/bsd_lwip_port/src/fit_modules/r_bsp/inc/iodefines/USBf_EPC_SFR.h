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
 * $Revision: 1297 $
 * $Date: 2019-02-22 17:18:43 +0000 (Fri, 22 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  USBf_EPC_SFR.h
 * Description  :  Definition of Peripheral registers  for RZN1 USBf_EPC
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __USBf_EPC_SFR__DEFINE_HEADER__
#define __USBf_EPC_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : USBf_EPC
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : USB_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                                         /* [1:0] */
      __IO unsigned long   PUE2:1;                                     /* [2] */
      __IO unsigned long   CONNECTB:1;                                 /* [3] */
      __IO unsigned long   DEFAULT:1;                                  /* [4] */
      __IO unsigned long   CONF:1;                                     /* [5] */
      __IO unsigned long   SUSPEND:1;                                  /* [6] */
      __IO unsigned long   RSUM_IN:1;                                  /* [7] */
      __IO unsigned long   SOF_RCV:1;                                  /* [8] */
      __IO unsigned long   FORCEFS:1;                                  /* [9] */
      __IO unsigned long   INT_SEL:1;                                  /* [10] */
      __IO unsigned long   SOF_CLK_MODE:1;                             /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   USBTESTMODE:3;                              /* [18:16] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } USB_CONTROL;
  union                                            /* Offset=0x0004 : USB_STATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :1;                                         /* [0] */
      __I  unsigned long   RSUM_OUT:1;                                 /* [1] */
      __I  unsigned long   SPND_OUT:1;                                 /* [2] */
      __I  unsigned long   USB_RST:1;                                  /* [3] */
      __I  unsigned long   DEFAULT:1;                                  /* [4] */
      __I  unsigned long   CONF:1;                                     /* [5] */
      __I  unsigned long   SPEED_MODE:1;                               /* [6] */
      __I  unsigned long   :24;                                        /* [30:7] */
      __I  unsigned long   SOF_DELAY_STATUS:1;                         /* [31] */
    } BIT;
  } USB_STATUS;
  union                                            /* Offset=0x0008 : USB_ADDRESS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   FRAME:11;                                   /* [10:0] */
      __IO unsigned long   :1;                                         /* [11] */
      __I  unsigned long   UFRAME:3;                                   /* [14:12] */
      __I  unsigned long   SOF_STATUS:1;                               /* [15] */
      __IO unsigned long   USB_ADDR:7;                                 /* [22:16] */
      __IO unsigned long   :8;                                         /* [30:23] */
      __IO unsigned long   SOF_DELAY_MODE:1;                           /* [31] */
    } BIT;
  } USB_ADDRESS;
  char                     wk_000C[0x0004];
  union                                            /* Offset=0x0010 : TEST_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   LOOPBACK:1;                                 /* [0] */
      __IO unsigned long   CS_TESTMODEEN:1;                            /* [1] */
      __IO unsigned long   FORCEHS:1;                                  /* [2] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } TEST_CONTROL;
  char                     wk_0014[0x0004];
  union                                            /* Offset=0x0018 : SETUP_DATA0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SETUP1:8;                                   /* [7:0] */
      __I  unsigned long   SETUP2:8;                                   /* [15:8] */
      __I  unsigned long   SETUP3:8;                                   /* [23:16] */
      __I  unsigned long   SETUP4:8;                                   /* [31:24] */
    } BIT;
  } SETUP_DATA0;
  union                                            /* Offset=0x001C : SETUP_DATA1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SETUP5:8;                                   /* [7:0] */
      __I  unsigned long   SETUP6:8;                                   /* [15:8] */
      __I  unsigned long   SETUP7:8;                                   /* [23:16] */
      __I  unsigned long   SETUP8:8;                                   /* [31:24] */
    } BIT;
  } SETUP_DATA1;
  union                                            /* Offset=0x0020 : USB_INT_STA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   RSUM_INT:1;                                 /* [1] */
      __IO unsigned long   SPND_INT:1;                                 /* [2] */
      __IO unsigned long   USB_RST_INT:1;                              /* [3] */
      __IO unsigned long   SOF_INT:1;                                  /* [4] */
      __IO unsigned long   SOF_ERROR_INT:1;                            /* [5] */
      __IO unsigned long   SPEED_MODE_INT:1;                           /* [6] */
      __IO unsigned long   :1;                                         /* [7] */
      __I  unsigned long   EP0_INT:1;                                  /* [8] */
      __I  unsigned long   EP1_INT:1;                                  /* [9] */
      __I  unsigned long   EP2_INT:1;                                  /* [10] */
      __I  unsigned long   EP3_INT:1;                                  /* [11] */
      __I  unsigned long   EP4_INT:1;                                  /* [12] */
      __I  unsigned long   EP5_INT:1;                                  /* [13] */
      __I  unsigned long   EP6_INT:1;                                  /* [14] */
      __I  unsigned long   EP7_INT:1;                                  /* [15] */
      __I  unsigned long   EP8_INT:1;                                  /* [16] */
      __I  unsigned long   EP9_INT:1;                                  /* [17] */
      __I  unsigned long   EP10_INT:1;                                 /* [18] */
      __I  unsigned long   EP11_INT:1;                                 /* [19] */
      __I  unsigned long   EP12_INT:1;                                 /* [20] */
      __I  unsigned long   EP13_INT:1;                                 /* [21] */
      __I  unsigned long   EP14_INT:1;                                 /* [22] */
      __I  unsigned long   EP15_INT:1;                                 /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } USB_INT_STA;
  union                                            /* Offset=0x0024 : USB_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   RSUM_EN:1;                                  /* [1] */
      __IO unsigned long   SPND_EN:1;                                  /* [2] */
      __IO unsigned long   USB_RST_EN:1;                               /* [3] */
      __IO unsigned long   SOF_EN:1;                                   /* [4] */
      __IO unsigned long   SOF_ERROR_EN:1;                             /* [5] */
      __IO unsigned long   SPEED_MODE_EN:1;                            /* [6] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   EP0_EN:1;                                   /* [8] */
      __IO unsigned long   EP1_EN:1;                                   /* [9] */
      __IO unsigned long   EP2_EN:1;                                   /* [10] */
      __IO unsigned long   EP3_EN:1;                                   /* [11] */
      __IO unsigned long   EP4_EN:1;                                   /* [12] */
      __IO unsigned long   EP5_EN:1;                                   /* [13] */
      __IO unsigned long   EP6_EN:1;                                   /* [14] */
      __IO unsigned long   EP7_EN:1;                                   /* [15] */
      __IO unsigned long   EP8_EN:1;                                   /* [16] */
      __IO unsigned long   EP9_EN:1;                                   /* [17] */
      __IO unsigned long   EP10_EN:1;                                  /* [18] */
      __IO unsigned long   EP11_EN:1;                                  /* [19] */
      __IO unsigned long   EP12_EN:1;                                  /* [20] */
      __IO unsigned long   EP13_EN:1;                                  /* [21] */
      __IO unsigned long   EP14_EN:1;                                  /* [22] */
      __IO unsigned long   EP15_EN:1;                                  /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } USB_INT_ENA;
  union                                            /* Offset=0x0028 : EP0_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP0_ONAK:1;                                 /* [0] */
      __IO unsigned long   EP0_INAK:1;                                 /* [1] */
      __IO unsigned long   EP0_STL:1;                                  /* [2] */
      __O  unsigned long   EP0_PERR_NAK_CLR:1;                         /* [3] */
      __O  unsigned long   EP0_INAK_EN:1;                              /* [4] */
      __O  unsigned long   EP0_DW:2;                                   /* [6:5] */
      __O  unsigned long   EP0_DEND:1;                                 /* [7] */
      __O  unsigned long   EP0_BCLR:1;                                 /* [8] */
      __O  unsigned long   EP0_PIDCLR:1;                               /* [9] */
      __IO unsigned long   :6;                                         /* [15:10] */
      __IO unsigned long   EP0_AUTO:1;                                 /* [16] */
      __IO unsigned long   EP0_OVERSEL:1;                              /* [17] */
      __IO unsigned long   EP0_STGSEL:1;                               /* [18] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } EP0_CONTROL;
  union                                            /* Offset=0x002C : EP0_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SETUP_INT:1;                                /* [0] */
      __IO unsigned long   STG_START_INT:1;                            /* [1] */
      __IO unsigned long   STG_END_INT:1;                              /* [2] */
      __IO unsigned long   EP0_STALL_INT:1;                            /* [3] */
      __IO unsigned long   EP0_IN_INT:1;                               /* [4] */
      __IO unsigned long   EP0_OUT_INT:1;                              /* [5] */
      __IO unsigned long   EP0_OUT_OR_INT:1;                           /* [6] */
      __IO unsigned long   EP0_OUT_NULL_INT:1;                         /* [7] */
      __I  unsigned long   EP0_IN_EMPTY:1;                             /* [8] */
      __I  unsigned long   EP0_IN_FULL:1;                              /* [9] */
      __I  unsigned long   EP0_IN_DATA:1;                              /* [10] */
      __IO unsigned long   EP0_IN_NAK_INT:1;                           /* [11] */
      __I  unsigned long   EP0_OUT_EMPTY:1;                            /* [12] */
      __I  unsigned long   EP0_OUT_FULL:1;                             /* [13] */
      __I  unsigned long   EP0_OUT_NULL:1;                             /* [14] */
      __IO unsigned long   EP0_OUT_NAK_INT:1;                          /* [15] */
      __IO unsigned long   EP0_PERR_NAK_INT:1;                         /* [16] */
      __I  unsigned long   EP0_PERR_NAK:1;                             /* [17] */
      __I  unsigned long   EP0_PID:1;                                  /* [18] */
      __IO unsigned long   :13;                                        /* [31:19] */
    } BIT;
  } EP0_STATUS;
  union                                            /* Offset=0x0030 : EP0_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SETUP_EN:1;                                 /* [0] */
      __IO unsigned long   STG_START_EN:1;                             /* [1] */
      __IO unsigned long   STG_END_EN:1;                               /* [2] */
      __IO unsigned long   EP0_STALL_EN:1;                             /* [3] */
      __IO unsigned long   EP0_IN_EN:1;                                /* [4] */
      __IO unsigned long   EP0_OUT_EN:1;                               /* [5] */
      __IO unsigned long   EP0_OUT_OR_EN:1;                            /* [6] */
      __IO unsigned long   EP0_OUT_NULL_EN:1;                          /* [7] */
      __IO unsigned long   :3;                                         /* [10:8] */
      __IO unsigned long   EP0_IN_NAK_EN:1;                            /* [11] */
      __IO unsigned long   :3;                                         /* [14:12] */
      __IO unsigned long   EP0_OUT_NAK_EN:1;                           /* [15] */
      __IO unsigned long   EP0_PERR_NAK_EN:1;                          /* [16] */
      __IO unsigned long   :15;                                        /* [31:17] */
    } BIT;
  } EP0_INT_ENA;
  union                                            /* Offset=0x0034 : EP0_LENGTH */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP0_LDATA:7;                                /* [6:0] */
      __I  unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } EP0_LENGTH;
  union                                            /* Offset=0x0038 : EP0_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP0_RDATA1:8;                               /* [7:0] */
      __I  unsigned long   EP0_RDATA2:8;                               /* [15:8] */
      __I  unsigned long   EP0_RDATA3:8;                               /* [23:16] */
      __I  unsigned long   EP0_RDATA4:8;                               /* [31:24] */
    } BIT;
  } EP0_READ;
  union                                            /* Offset=0x003C : EP0_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP0_WDATA1:8;                               /* [7:0] */
      __O  unsigned long   EP0_WDATA2:8;                               /* [15:8] */
      __O  unsigned long   EP0_WDATA3:8;                               /* [23:16] */
      __O  unsigned long   EP0_WDATA4:8;                               /* [31:24] */
    } BIT;
  } EP0_WRITE;
  union                                            /* Offset=0x0040 : EP1_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP1_ONAK:1;                                 /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP1_OSTL:1;                                 /* [2] */
      __IO unsigned long   EP1_ISTL:1;                                 /* [3] */
      __O  unsigned long   EP1_OSTL_EN:1;                              /* [4] */
      __O  unsigned long   EP1_DW:2;                                   /* [6:5] */
      __O  unsigned long   EP1_DEND:1;                                 /* [7] */
      __O  unsigned long   EP1_CBCLR:1;                                /* [8] */
      __O  unsigned long   EP1_BCLR:1;                                 /* [9] */
      __O  unsigned long   EP1_OPIDCLR:1;                              /* [10] */
      __O  unsigned long   EP1_IPIDCLR:1;                              /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP1_AUTO:1;                                 /* [16] */
      __IO unsigned long   EP1_OVERSEL:1;                              /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP1_MODE:2;                                 /* [25:24] */
      __IO unsigned long   EP1_DIR0:1;                                 /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP1_BUF_TYPE:1;                             /* [30] */
      __IO unsigned long   EP1_EN:1;                                   /* [31] */
    } BIT;
  } EP1_CONTROL;
  union                                            /* Offset=0x0044 : EP1_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP1_IN_EMPTY:1;                             /* [0] */
      __I  unsigned long   EP1_IN_FULL:1;                              /* [1] */
      __I  unsigned long   EP1_IN_DATA:1;                              /* [2] */
      __IO unsigned long   EP1_IN_INT:1;                               /* [3] */
      __IO unsigned long   EP1_IN_STALL_INT:1;                         /* [4] */
      __IO unsigned long   EP1_IN_NAK_ERR_INT:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP1_IN_END_INT:1;                           /* [7] */
      __I  unsigned long   EP1_ISO_UR:1;                               /* [8] */
      __I  unsigned long   EP1_IN_NOTKN:1;                             /* [9] */
      __I  unsigned long   EP1_IPID:1;                                 /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP1_OUT_EMPTY:1;                            /* [16] */
      __I  unsigned long   EP1_OUT_FULL:1;                             /* [17] */
      __IO unsigned long   EP1_OUT_NULL_INT:1;                         /* [18] */
      __IO unsigned long   EP1_OUT_INT:1;                              /* [19] */
      __IO unsigned long   EP1_OUT_STALL_INT:1;                        /* [20] */
      __IO unsigned long   EP1_OUT_NAK_ERR_INT:1;                      /* [21] */
      __IO unsigned long   EP1_OUT_OR_INT:1;                           /* [22] */
      __IO unsigned long   EP1_OUT_END_INT:1;                          /* [23] */
      __I  unsigned long   EP1_ISO_CRC:1;                              /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP1_ISO_OR:1;                               /* [26] */
      __I  unsigned long   EP1_OUT_NOTKN:1;                            /* [27] */
      __I  unsigned long   EP1_OPID:1;                                 /* [28] */
      __I  unsigned long   EP1_ISO_PIDERR:1;                           /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP1_STATUS;
  union                                            /* Offset=0x0048 : EP1_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP1_IN_EN:1;                                /* [3] */
      __IO unsigned long   EP1_IN_STALL_EN:1;                          /* [4] */
      __IO unsigned long   EP1_IN_NAK_ERR_EN:1;                        /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP1_IN_END_EN:1;                            /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP1_OUT_NULL_EN:1;                          /* [18] */
      __IO unsigned long   EP1_OUT_EN:1;                               /* [19] */
      __IO unsigned long   EP1_OUT_STALL_EN:1;                         /* [20] */
      __IO unsigned long   EP1_OUT_NAK_ERR_EN:1;                       /* [21] */
      __IO unsigned long   EP1_OUT_OR_EN:1;                            /* [22] */
      __IO unsigned long   EP1_OUT_END_EN:1;                           /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP1_INT_ENA;
  union                                            /* Offset=0x004C : EP1_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP1_DMAMODE0:1;                             /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP1_DMA_EN:1;                               /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP1_STOP_SET:1;                             /* [8] */
      __IO unsigned long   EP1_BURST_SET:1;                            /* [9] */
      __IO unsigned long   EP1_DEND_SET:1;                             /* [10] */
      __IO unsigned long   EP1_STOP_MODE:1;                            /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP1_DMA_CTRL;
  union                                            /* Offset=0x0050 : EP1_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP1_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP1_BASEAD:13;                              /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP1_PCKT_ADRS;
  union                                            /* Offset=0x0054 : EP1_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP1_LDATA:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP1_DMACNT:9;                               /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP1_LEN_DCNT;
  union                                            /* Offset=0x0058 : EP1_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP1_RDATA1:8;                               /* [7:0] */
      __I  unsigned long   EP1_RDATA2:8;                               /* [15:8] */
      __I  unsigned long   EP1_RDATA3:8;                               /* [23:16] */
      __I  unsigned long   EP1_RDATA4:8;                               /* [31:24] */
    } BIT;
  } EP1_READ;
  union                                            /* Offset=0x005C : EP1_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP1_WDATA1:8;                               /* [7:0] */
      __O  unsigned long   EP1_WDATA2:8;                               /* [15:8] */
      __O  unsigned long   EP1_WDATA3:8;                               /* [23:16] */
      __O  unsigned long   EP1_WDATA4:8;                               /* [31:24] */
    } BIT;
  } EP1_WRITE;
  union                                            /* Offset=0x0060 : EP2_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP2_ONAK:1;                                 /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP2_OSTL:1;                                 /* [2] */
      __IO unsigned long   EP2_ISTL:1;                                 /* [3] */
      __O  unsigned long   EP2_OSTL_EN:1;                              /* [4] */
      __O  unsigned long   EP2_DW:2;                                   /* [6:5] */
      __O  unsigned long   EP2_DEND:1;                                 /* [7] */
      __O  unsigned long   EP2_CBCLR:1;                                /* [8] */
      __O  unsigned long   EP2_BCLR:1;                                 /* [9] */
      __O  unsigned long   EP2_OPIDCLR:1;                              /* [10] */
      __O  unsigned long   EP2_IPIDCLR:1;                              /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP2_AUTO:1;                                 /* [16] */
      __IO unsigned long   EP2_OVERSEL:1;                              /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP2_MODE:2;                                 /* [25:24] */
      __IO unsigned long   EP2_DIR0:1;                                 /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP2_BUF_TYPE:1;                             /* [30] */
      __IO unsigned long   EP2_EN:1;                                   /* [31] */
    } BIT;
  } EP2_CONTROL;
  union                                            /* Offset=0x0064 : EP2_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP2_IN_EMPTY:1;                             /* [0] */
      __I  unsigned long   EP2_IN_FULL:1;                              /* [1] */
      __I  unsigned long   EP2_IN_DATA:1;                              /* [2] */
      __IO unsigned long   EP2_IN_INT:1;                               /* [3] */
      __IO unsigned long   EP2_IN_STALL_INT:1;                         /* [4] */
      __IO unsigned long   EP2_IN_NAK_ERR_INT:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP2_IN_END_INT:1;                           /* [7] */
      __I  unsigned long   EP2_ISO_UR:1;                               /* [8] */
      __I  unsigned long   EP2_IN_NOTKN:1;                             /* [9] */
      __I  unsigned long   EP2_IPID:1;                                 /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP2_OUT_EMPTY:1;                            /* [16] */
      __I  unsigned long   EP2_OUT_FULL:1;                             /* [17] */
      __IO unsigned long   EP2_OUT_NULL_INT:1;                         /* [18] */
      __IO unsigned long   EP2_OUT_INT:1;                              /* [19] */
      __IO unsigned long   EP2_OUT_STALL_INT:1;                        /* [20] */
      __IO unsigned long   EP2_OUT_NAK_ERR_INT:1;                      /* [21] */
      __IO unsigned long   EP2_OUT_OR_INT:1;                           /* [22] */
      __IO unsigned long   EP2_OUT_END_INT:1;                          /* [23] */
      __I  unsigned long   EP2_ISO_CRC:1;                              /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP2_ISO_OR:1;                               /* [26] */
      __I  unsigned long   EP2_OUT_NOTKN:1;                            /* [27] */
      __I  unsigned long   EP2_OPID:1;                                 /* [28] */
      __I  unsigned long   EP2_ISO_PIDERR:1;                           /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP2_STATUS;
  union                                            /* Offset=0x0068 : EP2_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP2_IN_EN:1;                                /* [3] */
      __IO unsigned long   EP2_IN_STALL_EN:1;                          /* [4] */
      __IO unsigned long   EP2_IN_NAK_ERR_EN:1;                        /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP2_IN_END_EN:1;                            /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP2_OUT_NULL_EN:1;                          /* [18] */
      __IO unsigned long   EP2_OUT_EN:1;                               /* [19] */
      __IO unsigned long   EP2_OUT_STALL_EN:1;                         /* [20] */
      __IO unsigned long   EP2_OUT_NAK_ERR_EN:1;                       /* [21] */
      __IO unsigned long   EP2_OUT_OR_EN:1;                            /* [22] */
      __IO unsigned long   EP2_OUT_END_EN:1;                           /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP2_INT_ENA;
  union                                            /* Offset=0x006C : EP2_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP2_DMAMODE0:1;                             /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP2_DMA_EN:1;                               /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP2_STOP_SET:1;                             /* [8] */
      __IO unsigned long   EP2_BURST_SET:1;                            /* [9] */
      __IO unsigned long   EP2_DEND_SET:1;                             /* [10] */
      __IO unsigned long   EP2_STOP_MODE:1;                            /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP2_DMA_CTRL;
  union                                            /* Offset=0x0070 : EP2_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP2_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP2_BASEAD:13;                              /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP2_PCKT_ADRS;
  union                                            /* Offset=0x0074 : EP2_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP2_LDATA:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP2_DMACNT:9;                               /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP2_LEN_DCNT;
  union                                            /* Offset=0x0078 : EP2_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP2_RDATA1:8;                               /* [7:0] */
      __I  unsigned long   EP2_RDATA2:8;                               /* [15:8] */
      __I  unsigned long   EP2_RDATA3:8;                               /* [23:16] */
      __I  unsigned long   EP2_RDATA4:8;                               /* [31:24] */
    } BIT;
  } EP2_READ;
  union                                            /* Offset=0x007C : EP2_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP2_WDATA1:8;                               /* [7:0] */
      __O  unsigned long   EP2_WDATA2:8;                               /* [15:8] */
      __O  unsigned long   EP2_WDATA3:8;                               /* [23:16] */
      __O  unsigned long   EP2_WDATA4:8;                               /* [31:24] */
    } BIT;
  } EP2_WRITE;
  union                                            /* Offset=0x0080 : EP3_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP3_ONAK:1;                                 /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP3_OSTL:1;                                 /* [2] */
      __IO unsigned long   EP3_ISTL:1;                                 /* [3] */
      __O  unsigned long   EP3_OSTL_EN:1;                              /* [4] */
      __O  unsigned long   EP3_DW:2;                                   /* [6:5] */
      __O  unsigned long   EP3_DEND:1;                                 /* [7] */
      __O  unsigned long   EP3_CBCLR:1;                                /* [8] */
      __O  unsigned long   EP3_BCLR:1;                                 /* [9] */
      __O  unsigned long   EP3_OPIDCLR:1;                              /* [10] */
      __O  unsigned long   EP3_IPIDCLR:1;                              /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP3_AUTO:1;                                 /* [16] */
      __IO unsigned long   EP3_OVERSEL:1;                              /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP3_MODE:2;                                 /* [25:24] */
      __IO unsigned long   EP3_DIR0:1;                                 /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP3_BUF_TYPE:1;                             /* [30] */
      __IO unsigned long   EP3_EN:1;                                   /* [31] */
    } BIT;
  } EP3_CONTROL;
  union                                            /* Offset=0x0084 : EP3_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP3_IN_EMPTY:1;                             /* [0] */
      __I  unsigned long   EP3_IN_FULL:1;                              /* [1] */
      __I  unsigned long   EP3_IN_DATA:1;                              /* [2] */
      __IO unsigned long   EP3_IN_INT:1;                               /* [3] */
      __IO unsigned long   EP3_IN_STALL_INT:1;                         /* [4] */
      __IO unsigned long   EP3_IN_NAK_ERR_INT:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP3_IN_END_INT:1;                           /* [7] */
      __I  unsigned long   EP3_ISO_UR:1;                               /* [8] */
      __I  unsigned long   EP3_IN_NOTKN:1;                             /* [9] */
      __I  unsigned long   EP3_IPID:1;                                 /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP3_OUT_EMPTY:1;                            /* [16] */
      __I  unsigned long   EP3_OUT_FULL:1;                             /* [17] */
      __IO unsigned long   EP3_OUT_NULL_INT:1;                         /* [18] */
      __IO unsigned long   EP3_OUT_INT:1;                              /* [19] */
      __IO unsigned long   EP3_OUT_STALL_INT:1;                        /* [20] */
      __IO unsigned long   EP3_OUT_NAK_ERR_INT:1;                      /* [21] */
      __IO unsigned long   EP3_OUT_OR_INT:1;                           /* [22] */
      __IO unsigned long   EP3_OUT_END_INT:1;                          /* [23] */
      __I  unsigned long   EP3_ISO_CRC:1;                              /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP3_ISO_OR:1;                               /* [26] */
      __I  unsigned long   EP3_OUT_NOTKN:1;                            /* [27] */
      __I  unsigned long   EP3_OPID:1;                                 /* [28] */
      __I  unsigned long   EP3_ISO_PIDERR:1;                           /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP3_STATUS;
  union                                            /* Offset=0x0088 : EP3_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP3_IN_EN:1;                                /* [3] */
      __IO unsigned long   EP3_IN_STALL_EN:1;                          /* [4] */
      __IO unsigned long   EP3_IN_NAK_ERR_EN:1;                        /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP3_IN_END_EN:1;                            /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP3_OUT_NULL_EN:1;                          /* [18] */
      __IO unsigned long   EP3_OUT_EN:1;                               /* [19] */
      __IO unsigned long   EP3_OUT_STALL_EN:1;                         /* [20] */
      __IO unsigned long   EP3_OUT_NAK_ERR_EN:1;                       /* [21] */
      __IO unsigned long   EP3_OUT_OR_EN:1;                            /* [22] */
      __IO unsigned long   EP3_OUT_END_EN:1;                           /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP3_INT_ENA;
  union                                            /* Offset=0x008C : EP3_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP3_DMAMODE0:1;                             /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP3_DMA_EN:1;                               /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP3_STOP_SET:1;                             /* [8] */
      __IO unsigned long   EP3_BURST_SET:1;                            /* [9] */
      __IO unsigned long   EP3_DEND_SET:1;                             /* [10] */
      __IO unsigned long   EP3_STOP_MODE:1;                            /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP3_DMA_CTRL;
  union                                            /* Offset=0x0090 : EP3_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP3_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP3_BASEAD:13;                              /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP3_PCKT_ADRS;
  union                                            /* Offset=0x0094 : EP3_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP3_LDATA:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP3_DMACNT:9;                               /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP3_LEN_DCNT;
  union                                            /* Offset=0x0098 : EP3_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP3_RDATA1:8;                               /* [7:0] */
      __I  unsigned long   EP3_RDATA2:8;                               /* [15:8] */
      __I  unsigned long   EP3_RDATA3:8;                               /* [23:16] */
      __I  unsigned long   EP3_RDATA4:8;                               /* [31:24] */
    } BIT;
  } EP3_READ;
  union                                            /* Offset=0x009C : EP3_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP3_WDATA1:8;                               /* [7:0] */
      __O  unsigned long   EP3_WDATA2:8;                               /* [15:8] */
      __O  unsigned long   EP3_WDATA3:8;                               /* [23:16] */
      __O  unsigned long   EP3_WDATA4:8;                               /* [31:24] */
    } BIT;
  } EP3_WRITE;
  union                                            /* Offset=0x00A0 : EP4_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP4_ONAK:1;                                 /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP4_OSTL:1;                                 /* [2] */
      __IO unsigned long   EP4_ISTL:1;                                 /* [3] */
      __O  unsigned long   EP4_OSTL_EN:1;                              /* [4] */
      __O  unsigned long   EP4_DW:2;                                   /* [6:5] */
      __O  unsigned long   EP4_DEND:1;                                 /* [7] */
      __O  unsigned long   EP4_CBCLR:1;                                /* [8] */
      __O  unsigned long   EP4_BCLR:1;                                 /* [9] */
      __O  unsigned long   EP4_OPIDCLR:1;                              /* [10] */
      __O  unsigned long   EP4_IPIDCLR:1;                              /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP4_AUTO:1;                                 /* [16] */
      __IO unsigned long   EP4_OVERSEL:1;                              /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP4_MODE:2;                                 /* [25:24] */
      __IO unsigned long   EP4_DIR0:1;                                 /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP4_BUF_TYPE:1;                             /* [30] */
      __IO unsigned long   EP4_EN:1;                                   /* [31] */
    } BIT;
  } EP4_CONTROL;
  union                                            /* Offset=0x00A4 : EP4_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP4_IN_EMPTY:1;                             /* [0] */
      __I  unsigned long   EP4_IN_FULL:1;                              /* [1] */
      __I  unsigned long   EP4_IN_DATA:1;                              /* [2] */
      __IO unsigned long   EP4_IN_INT:1;                               /* [3] */
      __IO unsigned long   EP4_IN_STALL_INT:1;                         /* [4] */
      __IO unsigned long   EP4_IN_NAK_ERR_INT:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP4_IN_END_INT:1;                           /* [7] */
      __I  unsigned long   EP4_ISO_UR:1;                               /* [8] */
      __I  unsigned long   EP4_IN_NOTKN:1;                             /* [9] */
      __I  unsigned long   EP4_IPID:1;                                 /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP4_OUT_EMPTY:1;                            /* [16] */
      __I  unsigned long   EP4_OUT_FULL:1;                             /* [17] */
      __IO unsigned long   EP4_OUT_NULL_INT:1;                         /* [18] */
      __IO unsigned long   EP4_OUT_INT:1;                              /* [19] */
      __IO unsigned long   EP4_OUT_STALL_INT:1;                        /* [20] */
      __IO unsigned long   EP4_OUT_NAK_ERR_INT:1;                      /* [21] */
      __IO unsigned long   EP4_OUT_OR_INT:1;                           /* [22] */
      __IO unsigned long   EP4_OUT_END_INT:1;                          /* [23] */
      __I  unsigned long   EP4_ISO_CRC:1;                              /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP4_ISO_OR:1;                               /* [26] */
      __I  unsigned long   EP4_OUT_NOTKN:1;                            /* [27] */
      __I  unsigned long   EP4_OPID:1;                                 /* [28] */
      __I  unsigned long   EP4_ISO_PIDERR:1;                           /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP4_STATUS;
  union                                            /* Offset=0x00A8 : EP4_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP4_IN_EN:1;                                /* [3] */
      __IO unsigned long   EP4_IN_STALL_EN:1;                          /* [4] */
      __IO unsigned long   EP4_IN_NAK_ERR_EN:1;                        /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP4_IN_END_EN:1;                            /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP4_OUT_NULL_EN:1;                          /* [18] */
      __IO unsigned long   EP4_OUT_EN:1;                               /* [19] */
      __IO unsigned long   EP4_OUT_STALL_EN:1;                         /* [20] */
      __IO unsigned long   EP4_OUT_NAK_ERR_EN:1;                       /* [21] */
      __IO unsigned long   EP4_OUT_OR_EN:1;                            /* [22] */
      __IO unsigned long   EP4_OUT_END_EN:1;                           /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP4_INT_ENA;
  union                                            /* Offset=0x00AC : EP4_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP4_DMAMODE0:1;                             /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP4_DMA_EN:1;                               /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP4_STOP_SET:1;                             /* [8] */
      __IO unsigned long   EP4_BURST_SET:1;                            /* [9] */
      __IO unsigned long   EP4_DEND_SET:1;                             /* [10] */
      __IO unsigned long   EP4_STOP_MODE:1;                            /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP4_DMA_CTRL;
  union                                            /* Offset=0x00B0 : EP4_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP4_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP4_BASEAD:13;                              /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP4_PCKT_ADRS;
  union                                            /* Offset=0x00B4 : EP4_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP4_LDATA:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP4_DMACNT:9;                               /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP4_LEN_DCNT;
  union                                            /* Offset=0x00B8 : EP4_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP4_RDATA1:8;                               /* [7:0] */
      __I  unsigned long   EP4_RDATA2:8;                               /* [15:8] */
      __I  unsigned long   EP4_RDATA3:8;                               /* [23:16] */
      __I  unsigned long   EP4_RDATA4:8;                               /* [31:24] */
    } BIT;
  } EP4_READ;
  union                                            /* Offset=0x00BC : EP4_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP4_WDATA1:8;                               /* [7:0] */
      __O  unsigned long   EP4_WDATA2:8;                               /* [15:8] */
      __O  unsigned long   EP4_WDATA3:8;                               /* [23:16] */
      __O  unsigned long   EP4_WDATA4:8;                               /* [31:24] */
    } BIT;
  } EP4_WRITE;
  union                                            /* Offset=0x00C0 : EP5_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP5_ONAK:1;                                 /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP5_OSTL:1;                                 /* [2] */
      __IO unsigned long   EP5_ISTL:1;                                 /* [3] */
      __O  unsigned long   EP5_OSTL_EN:1;                              /* [4] */
      __O  unsigned long   EP5_DW:2;                                   /* [6:5] */
      __O  unsigned long   EP5_DEND:1;                                 /* [7] */
      __O  unsigned long   EP5_CBCLR:1;                                /* [8] */
      __O  unsigned long   EP5_BCLR:1;                                 /* [9] */
      __O  unsigned long   EP5_OPIDCLR:1;                              /* [10] */
      __O  unsigned long   EP5_IPIDCLR:1;                              /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP5_AUTO:1;                                 /* [16] */
      __IO unsigned long   EP5_OVERSEL:1;                              /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP5_MODE:2;                                 /* [25:24] */
      __IO unsigned long   EP5_DIR0:1;                                 /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP5_BUF_TYPE:1;                             /* [30] */
      __IO unsigned long   EP5_EN:1;                                   /* [31] */
    } BIT;
  } EP5_CONTROL;
  union                                            /* Offset=0x00C4 : EP5_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP5_IN_EMPTY:1;                             /* [0] */
      __I  unsigned long   EP5_IN_FULL:1;                              /* [1] */
      __I  unsigned long   EP5_IN_DATA:1;                              /* [2] */
      __IO unsigned long   EP5_IN_INT:1;                               /* [3] */
      __IO unsigned long   EP5_IN_STALL_INT:1;                         /* [4] */
      __IO unsigned long   EP5_IN_NAK_ERR_INT:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP5_IN_END_INT:1;                           /* [7] */
      __I  unsigned long   EP5_ISO_UR:1;                               /* [8] */
      __I  unsigned long   EP5_IN_NOTKN:1;                             /* [9] */
      __I  unsigned long   EP5_IPID:1;                                 /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP5_OUT_EMPTY:1;                            /* [16] */
      __I  unsigned long   EP5_OUT_FULL:1;                             /* [17] */
      __IO unsigned long   EP5_OUT_NULL_INT:1;                         /* [18] */
      __IO unsigned long   EP5_OUT_INT:1;                              /* [19] */
      __IO unsigned long   EP5_OUT_STALL_INT:1;                        /* [20] */
      __IO unsigned long   EP5_OUT_NAK_ERR_INT:1;                      /* [21] */
      __IO unsigned long   EP5_OUT_OR_INT:1;                           /* [22] */
      __IO unsigned long   EP5_OUT_END_INT:1;                          /* [23] */
      __I  unsigned long   EP5_ISO_CRC:1;                              /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP5_ISO_OR:1;                               /* [26] */
      __I  unsigned long   EP5_OUT_NOTKN:1;                            /* [27] */
      __I  unsigned long   EP5_OPID:1;                                 /* [28] */
      __I  unsigned long   EP5_ISO_PIDERR:1;                           /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP5_STATUS;
  union                                            /* Offset=0x00C8 : EP5_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP5_IN_EN:1;                                /* [3] */
      __IO unsigned long   EP5_IN_STALL_EN:1;                          /* [4] */
      __IO unsigned long   EP5_IN_NAK_ERR_EN:1;                        /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP5_IN_END_EN:1;                            /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP5_OUT_NULL_EN:1;                          /* [18] */
      __IO unsigned long   EP5_OUT_EN:1;                               /* [19] */
      __IO unsigned long   EP5_OUT_STALL_EN:1;                         /* [20] */
      __IO unsigned long   EP5_OUT_NAK_ERR_EN:1;                       /* [21] */
      __IO unsigned long   EP5_OUT_OR_EN:1;                            /* [22] */
      __IO unsigned long   EP5_OUT_END_EN:1;                           /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP5_INT_ENA;
  union                                            /* Offset=0x00CC : EP5_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP5_DMAMODE0:1;                             /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP5_DMA_EN:1;                               /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP5_STOP_SET:1;                             /* [8] */
      __IO unsigned long   EP5_BURST_SET:1;                            /* [9] */
      __IO unsigned long   EP5_DEND_SET:1;                             /* [10] */
      __IO unsigned long   EP5_STOP_MODE:1;                            /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP5_DMA_CTRL;
  union                                            /* Offset=0x00D0 : EP5_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP5_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP5_BASEAD:13;                              /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP5_PCKT_ADRS;
  union                                            /* Offset=0x00D4 : EP5_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP5_LDATA:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP5_DMACNT:9;                               /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP5_LEN_DCNT;
  union                                            /* Offset=0x00D8 : EP5_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP5_RDATA1:8;                               /* [7:0] */
      __I  unsigned long   EP5_RDATA2:8;                               /* [15:8] */
      __I  unsigned long   EP5_RDATA3:8;                               /* [23:16] */
      __I  unsigned long   EP5_RDATA4:8;                               /* [31:24] */
    } BIT;
  } EP5_READ;
  union                                            /* Offset=0x00DC : EP5_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP5_WDATA1:8;                               /* [7:0] */
      __O  unsigned long   EP5_WDATA2:8;                               /* [15:8] */
      __O  unsigned long   EP5_WDATA3:8;                               /* [23:16] */
      __O  unsigned long   EP5_WDATA4:8;                               /* [31:24] */
    } BIT;
  } EP5_WRITE;
  union                                            /* Offset=0x00E0 : EP6_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP6_ONAK:1;                                 /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP6_OSTL:1;                                 /* [2] */
      __IO unsigned long   EP6_ISTL:1;                                 /* [3] */
      __O  unsigned long   EP6_OSTL_EN:1;                              /* [4] */
      __O  unsigned long   EP6_DW:2;                                   /* [6:5] */
      __O  unsigned long   EP6_DEND:1;                                 /* [7] */
      __O  unsigned long   EP6_CBCLR:1;                                /* [8] */
      __O  unsigned long   EP6_BCLR:1;                                 /* [9] */
      __O  unsigned long   EP6_OPIDCLR:1;                              /* [10] */
      __O  unsigned long   EP6_IPIDCLR:1;                              /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP6_AUTO:1;                                 /* [16] */
      __IO unsigned long   EP6_OVERSEL:1;                              /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP6_MODE:2;                                 /* [25:24] */
      __IO unsigned long   EP6_DIR0:1;                                 /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP6_BUF_TYPE:1;                             /* [30] */
      __IO unsigned long   EP6_EN:1;                                   /* [31] */
    } BIT;
  } EP6_CONTROL;
  union                                            /* Offset=0x00E4 : EP6_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP6_IN_EMPTY:1;                             /* [0] */
      __I  unsigned long   EP6_IN_FULL:1;                              /* [1] */
      __I  unsigned long   EP6_IN_DATA:1;                              /* [2] */
      __IO unsigned long   EP6_IN_INT:1;                               /* [3] */
      __IO unsigned long   EP6_IN_STALL_INT:1;                         /* [4] */
      __IO unsigned long   EP6_IN_NAK_ERR_INT:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP6_IN_END_INT:1;                           /* [7] */
      __I  unsigned long   EP6_ISO_UR:1;                               /* [8] */
      __I  unsigned long   EP6_IN_NOTKN:1;                             /* [9] */
      __I  unsigned long   EP6_IPID:1;                                 /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP6_OUT_EMPTY:1;                            /* [16] */
      __I  unsigned long   EP6_OUT_FULL:1;                             /* [17] */
      __IO unsigned long   EP6_OUT_NULL_INT:1;                         /* [18] */
      __IO unsigned long   EP6_OUT_INT:1;                              /* [19] */
      __IO unsigned long   EP6_OUT_STALL_INT:1;                        /* [20] */
      __IO unsigned long   EP6_OUT_NAK_ERR_INT:1;                      /* [21] */
      __IO unsigned long   EP6_OUT_OR_INT:1;                           /* [22] */
      __IO unsigned long   EP6_OUT_END_INT:1;                          /* [23] */
      __I  unsigned long   EP6_ISO_CRC:1;                              /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP6_ISO_OR:1;                               /* [26] */
      __I  unsigned long   EP6_OUT_NOTKN:1;                            /* [27] */
      __I  unsigned long   EP6_OPID:1;                                 /* [28] */
      __I  unsigned long   EP6_ISO_PIDERR:1;                           /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP6_STATUS;
  union                                            /* Offset=0x00E8 : EP6_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP6_IN_EN:1;                                /* [3] */
      __IO unsigned long   EP6_IN_STALL_EN:1;                          /* [4] */
      __IO unsigned long   EP6_IN_NAK_ERR_EN:1;                        /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP6_IN_END_EN:1;                            /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP6_OUT_NULL_EN:1;                          /* [18] */
      __IO unsigned long   EP6_OUT_EN:1;                               /* [19] */
      __IO unsigned long   EP6_OUT_STALL_EN:1;                         /* [20] */
      __IO unsigned long   EP6_OUT_NAK_ERR_EN:1;                       /* [21] */
      __IO unsigned long   EP6_OUT_OR_EN:1;                            /* [22] */
      __IO unsigned long   EP6_OUT_END_EN:1;                           /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP6_INT_ENA;
  union                                            /* Offset=0x00EC : EP6_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP6_DMAMODE0:1;                             /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP6_DMA_EN:1;                               /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP6_STOP_SET:1;                             /* [8] */
      __IO unsigned long   EP6_BURST_SET:1;                            /* [9] */
      __IO unsigned long   EP6_DEND_SET:1;                             /* [10] */
      __IO unsigned long   EP6_STOP_MODE:1;                            /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP6_DMA_CTRL;
  union                                            /* Offset=0x00F0 : EP6_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP6_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP6_BASEAD:13;                              /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP6_PCKT_ADRS;
  union                                            /* Offset=0x00F4 : EP6_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP6_LDATA:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP6_DMACNT:9;                               /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP6_LEN_DCNT;
  union                                            /* Offset=0x00F8 : EP6_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP6_RDATA1:8;                               /* [7:0] */
      __I  unsigned long   EP6_RDATA2:8;                               /* [15:8] */
      __I  unsigned long   EP6_RDATA3:8;                               /* [23:16] */
      __I  unsigned long   EP6_RDATA4:8;                               /* [31:24] */
    } BIT;
  } EP6_READ;
  union                                            /* Offset=0x00FC : EP6_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP6_WDATA1:8;                               /* [7:0] */
      __O  unsigned long   EP6_WDATA2:8;                               /* [15:8] */
      __O  unsigned long   EP6_WDATA3:8;                               /* [23:16] */
      __O  unsigned long   EP6_WDATA4:8;                               /* [31:24] */
    } BIT;
  } EP6_WRITE;
  union                                            /* Offset=0x0100 : EP7_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP7_ONAK:1;                                 /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP7_OSTL:1;                                 /* [2] */
      __IO unsigned long   EP7_ISTL:1;                                 /* [3] */
      __O  unsigned long   EP7_OSTL_EN:1;                              /* [4] */
      __O  unsigned long   EP7_DW:2;                                   /* [6:5] */
      __O  unsigned long   EP7_DEND:1;                                 /* [7] */
      __O  unsigned long   EP7_CBCLR:1;                                /* [8] */
      __O  unsigned long   EP7_BCLR:1;                                 /* [9] */
      __O  unsigned long   EP7_OPIDCLR:1;                              /* [10] */
      __O  unsigned long   EP7_IPIDCLR:1;                              /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP7_AUTO:1;                                 /* [16] */
      __IO unsigned long   EP7_OVERSEL:1;                              /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP7_MODE:2;                                 /* [25:24] */
      __IO unsigned long   EP7_DIR0:1;                                 /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP7_BUF_TYPE:1;                             /* [30] */
      __IO unsigned long   EP7_EN:1;                                   /* [31] */
    } BIT;
  } EP7_CONTROL;
  union                                            /* Offset=0x0104 : EP7_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP7_IN_EMPTY:1;                             /* [0] */
      __I  unsigned long   EP7_IN_FULL:1;                              /* [1] */
      __I  unsigned long   EP7_IN_DATA:1;                              /* [2] */
      __IO unsigned long   EP7_IN_INT:1;                               /* [3] */
      __IO unsigned long   EP7_IN_STALL_INT:1;                         /* [4] */
      __IO unsigned long   EP7_IN_NAK_ERR_INT:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP7_IN_END_INT:1;                           /* [7] */
      __I  unsigned long   EP7_ISO_UR:1;                               /* [8] */
      __I  unsigned long   EP7_IN_NOTKN:1;                             /* [9] */
      __I  unsigned long   EP7_IPID:1;                                 /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP7_OUT_EMPTY:1;                            /* [16] */
      __I  unsigned long   EP7_OUT_FULL:1;                             /* [17] */
      __IO unsigned long   EP7_OUT_NULL_INT:1;                         /* [18] */
      __IO unsigned long   EP7_OUT_INT:1;                              /* [19] */
      __IO unsigned long   EP7_OUT_STALL_INT:1;                        /* [20] */
      __IO unsigned long   EP7_OUT_NAK_ERR_INT:1;                      /* [21] */
      __IO unsigned long   EP7_OUT_OR_INT:1;                           /* [22] */
      __IO unsigned long   EP7_OUT_END_INT:1;                          /* [23] */
      __I  unsigned long   EP7_ISO_CRC:1;                              /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP7_ISO_OR:1;                               /* [26] */
      __I  unsigned long   EP7_OUT_NOTKN:1;                            /* [27] */
      __I  unsigned long   EP7_OPID:1;                                 /* [28] */
      __I  unsigned long   EP7_ISO_PIDERR:1;                           /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP7_STATUS;
  union                                            /* Offset=0x0108 : EP7_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP7_IN_EN:1;                                /* [3] */
      __IO unsigned long   EP7_IN_STALL_EN:1;                          /* [4] */
      __IO unsigned long   EP7_IN_NAK_ERR_EN:1;                        /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP7_IN_END_EN:1;                            /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP7_OUT_NULL_EN:1;                          /* [18] */
      __IO unsigned long   EP7_OUT_EN:1;                               /* [19] */
      __IO unsigned long   EP7_OUT_STALL_EN:1;                         /* [20] */
      __IO unsigned long   EP7_OUT_NAK_ERR_EN:1;                       /* [21] */
      __IO unsigned long   EP7_OUT_OR_EN:1;                            /* [22] */
      __IO unsigned long   EP7_OUT_END_EN:1;                           /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP7_INT_ENA;
  union                                            /* Offset=0x010C : EP7_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP7_DMAMODE0:1;                             /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP7_DMA_EN:1;                               /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP7_STOP_SET:1;                             /* [8] */
      __IO unsigned long   EP7_BURST_SET:1;                            /* [9] */
      __IO unsigned long   EP7_DEND_SET:1;                             /* [10] */
      __IO unsigned long   EP7_STOP_MODE:1;                            /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP7_DMA_CTRL;
  union                                            /* Offset=0x0110 : EP7_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP7_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP7_BASEAD:13;                              /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP7_PCKT_ADRS;
  union                                            /* Offset=0x0114 : EP7_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP7_LDATA:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP7_DMACNT:9;                               /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP7_LEN_DCNT;
  union                                            /* Offset=0x0118 : EP7_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP7_RDATA1:8;                               /* [7:0] */
      __I  unsigned long   EP7_RDATA2:8;                               /* [15:8] */
      __I  unsigned long   EP7_RDATA3:8;                               /* [23:16] */
      __I  unsigned long   EP7_RDATA4:8;                               /* [31:24] */
    } BIT;
  } EP7_READ;
  union                                            /* Offset=0x011C : EP7_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP7_WDATA1:8;                               /* [7:0] */
      __O  unsigned long   EP7_WDATA2:8;                               /* [15:8] */
      __O  unsigned long   EP7_WDATA3:8;                               /* [23:16] */
      __O  unsigned long   EP7_WDATA4:8;                               /* [31:24] */
    } BIT;
  } EP7_WRITE;
  union                                            /* Offset=0x0120 : EP8_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP8_ONAK:1;                                 /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP8_OSTL:1;                                 /* [2] */
      __IO unsigned long   EP8_ISTL:1;                                 /* [3] */
      __O  unsigned long   EP8_OSTL_EN:1;                              /* [4] */
      __O  unsigned long   EP8_DW:2;                                   /* [6:5] */
      __O  unsigned long   EP8_DEND:1;                                 /* [7] */
      __O  unsigned long   EP8_CBCLR:1;                                /* [8] */
      __O  unsigned long   EP8_BCLR:1;                                 /* [9] */
      __O  unsigned long   EP8_OPIDCLR:1;                              /* [10] */
      __O  unsigned long   EP8_IPIDCLR:1;                              /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP8_AUTO:1;                                 /* [16] */
      __IO unsigned long   EP8_OVERSEL:1;                              /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP8_MODE:2;                                 /* [25:24] */
      __IO unsigned long   EP8_DIR0:1;                                 /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP8_BUF_TYPE:1;                             /* [30] */
      __IO unsigned long   EP8_EN:1;                                   /* [31] */
    } BIT;
  } EP8_CONTROL;
  union                                            /* Offset=0x0124 : EP8_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP8_IN_EMPTY:1;                             /* [0] */
      __I  unsigned long   EP8_IN_FULL:1;                              /* [1] */
      __I  unsigned long   EP8_IN_DATA:1;                              /* [2] */
      __IO unsigned long   EP8_IN_INT:1;                               /* [3] */
      __IO unsigned long   EP8_IN_STALL_INT:1;                         /* [4] */
      __IO unsigned long   EP8_IN_NAK_ERR_INT:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP8_IN_END_INT:1;                           /* [7] */
      __I  unsigned long   EP8_ISO_UR:1;                               /* [8] */
      __I  unsigned long   EP8_IN_NOTKN:1;                             /* [9] */
      __I  unsigned long   EP8_IPID:1;                                 /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP8_OUT_EMPTY:1;                            /* [16] */
      __I  unsigned long   EP8_OUT_FULL:1;                             /* [17] */
      __IO unsigned long   EP8_OUT_NULL_INT:1;                         /* [18] */
      __IO unsigned long   EP8_OUT_INT:1;                              /* [19] */
      __IO unsigned long   EP8_OUT_STALL_INT:1;                        /* [20] */
      __IO unsigned long   EP8_OUT_NAK_ERR_INT:1;                      /* [21] */
      __IO unsigned long   EP8_OUT_OR_INT:1;                           /* [22] */
      __IO unsigned long   EP8_OUT_END_INT:1;                          /* [23] */
      __I  unsigned long   EP8_ISO_CRC:1;                              /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP8_ISO_OR:1;                               /* [26] */
      __I  unsigned long   EP8_OUT_NOTKN:1;                            /* [27] */
      __I  unsigned long   EP8_OPID:1;                                 /* [28] */
      __I  unsigned long   EP8_ISO_PIDERR:1;                           /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP8_STATUS;
  union                                            /* Offset=0x0128 : EP8_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP8_IN_EN:1;                                /* [3] */
      __IO unsigned long   EP8_IN_STALL_EN:1;                          /* [4] */
      __IO unsigned long   EP8_IN_NAK_ERR_EN:1;                        /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP8_IN_END_EN:1;                            /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP8_OUT_NULL_EN:1;                          /* [18] */
      __IO unsigned long   EP8_OUT_EN:1;                               /* [19] */
      __IO unsigned long   EP8_OUT_STALL_EN:1;                         /* [20] */
      __IO unsigned long   EP8_OUT_NAK_ERR_EN:1;                       /* [21] */
      __IO unsigned long   EP8_OUT_OR_EN:1;                            /* [22] */
      __IO unsigned long   EP8_OUT_END_EN:1;                           /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP8_INT_ENA;
  union                                            /* Offset=0x012C : EP8_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP8_DMAMODE0:1;                             /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP8_DMA_EN:1;                               /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP8_STOP_SET:1;                             /* [8] */
      __IO unsigned long   EP8_BURST_SET:1;                            /* [9] */
      __IO unsigned long   EP8_DEND_SET:1;                             /* [10] */
      __IO unsigned long   EP8_STOP_MODE:1;                            /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP8_DMA_CTRL;
  union                                            /* Offset=0x0130 : EP8_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP8_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP8_BASEAD:13;                              /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP8_PCKT_ADRS;
  union                                            /* Offset=0x0134 : EP8_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP8_LDATA:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP8_DMACNT:9;                               /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP8_LEN_DCNT;
  union                                            /* Offset=0x0138 : EP8_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP8_RDATA1:8;                               /* [7:0] */
      __I  unsigned long   EP8_RDATA2:8;                               /* [15:8] */
      __I  unsigned long   EP8_RDATA3:8;                               /* [23:16] */
      __I  unsigned long   EP8_RDATA4:8;                               /* [31:24] */
    } BIT;
  } EP8_READ;
  union                                            /* Offset=0x013C : EP8_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP8_WDATA1:8;                               /* [7:0] */
      __O  unsigned long   EP8_WDATA2:8;                               /* [15:8] */
      __O  unsigned long   EP8_WDATA3:8;                               /* [23:16] */
      __O  unsigned long   EP8_WDATA4:8;                               /* [31:24] */
    } BIT;
  } EP8_WRITE;
  union                                            /* Offset=0x0140 : EP9_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP9_ONAK:1;                                 /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP9_OSTL:1;                                 /* [2] */
      __IO unsigned long   EP9_ISTL:1;                                 /* [3] */
      __O  unsigned long   EP9_OSTL_EN:1;                              /* [4] */
      __O  unsigned long   EP9_DW:2;                                   /* [6:5] */
      __O  unsigned long   EP9_DEND:1;                                 /* [7] */
      __O  unsigned long   EP9_CBCLR:1;                                /* [8] */
      __O  unsigned long   EP9_BCLR:1;                                 /* [9] */
      __O  unsigned long   EP9_OPIDCLR:1;                              /* [10] */
      __O  unsigned long   EP9_IPIDCLR:1;                              /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP9_AUTO:1;                                 /* [16] */
      __IO unsigned long   EP9_OVERSEL:1;                              /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP9_MODE:2;                                 /* [25:24] */
      __IO unsigned long   EP9_DIR0:1;                                 /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP9_BUF_TYPE:1;                             /* [30] */
      __IO unsigned long   EP9_EN:1;                                   /* [31] */
    } BIT;
  } EP9_CONTROL;
  union                                            /* Offset=0x0144 : EP9_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP9_IN_EMPTY:1;                             /* [0] */
      __I  unsigned long   EP9_IN_FULL:1;                              /* [1] */
      __I  unsigned long   EP9_IN_DATA:1;                              /* [2] */
      __IO unsigned long   EP9_IN_INT:1;                               /* [3] */
      __IO unsigned long   EP9_IN_STALL_INT:1;                         /* [4] */
      __IO unsigned long   EP9_IN_NAK_ERR_INT:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP9_IN_END_INT:1;                           /* [7] */
      __I  unsigned long   EP9_ISO_UR:1;                               /* [8] */
      __I  unsigned long   EP9_IN_NOTKN:1;                             /* [9] */
      __I  unsigned long   EP9_IPID:1;                                 /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP9_OUT_EMPTY:1;                            /* [16] */
      __I  unsigned long   EP9_OUT_FULL:1;                             /* [17] */
      __IO unsigned long   EP9_OUT_NULL_INT:1;                         /* [18] */
      __IO unsigned long   EP9_OUT_INT:1;                              /* [19] */
      __IO unsigned long   EP9_OUT_STALL_INT:1;                        /* [20] */
      __IO unsigned long   EP9_OUT_NAK_ERR_INT:1;                      /* [21] */
      __IO unsigned long   EP9_OUT_OR_INT:1;                           /* [22] */
      __IO unsigned long   EP9_OUT_END_INT:1;                          /* [23] */
      __I  unsigned long   EP9_ISO_CRC:1;                              /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP9_ISO_OR:1;                               /* [26] */
      __I  unsigned long   EP9_OUT_NOTKN:1;                            /* [27] */
      __I  unsigned long   EP9_OPID:1;                                 /* [28] */
      __I  unsigned long   EP9_ISO_PIDERR:1;                           /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP9_STATUS;
  union                                            /* Offset=0x0148 : EP9_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP9_IN_EN:1;                                /* [3] */
      __IO unsigned long   EP9_IN_STALL_EN:1;                          /* [4] */
      __IO unsigned long   EP9_IN_NAK_ERR_EN:1;                        /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP9_IN_END_EN:1;                            /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP9_OUT_NULL_EN:1;                          /* [18] */
      __IO unsigned long   EP9_OUT_EN:1;                               /* [19] */
      __IO unsigned long   EP9_OUT_STALL_EN:1;                         /* [20] */
      __IO unsigned long   EP9_OUT_NAK_ERR_EN:1;                       /* [21] */
      __IO unsigned long   EP9_OUT_OR_EN:1;                            /* [22] */
      __IO unsigned long   EP9_OUT_END_EN:1;                           /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP9_INT_ENA;
  union                                            /* Offset=0x014C : EP9_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP9_DMAMODE0:1;                             /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP9_DMA_EN:1;                               /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP9_STOP_SET:1;                             /* [8] */
      __IO unsigned long   EP9_BURST_SET:1;                            /* [9] */
      __IO unsigned long   EP9_DEND_SET:1;                             /* [10] */
      __IO unsigned long   EP9_STOP_MODE:1;                            /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP9_DMA_CTRL;
  union                                            /* Offset=0x0150 : EP9_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP9_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP9_BASEAD:13;                              /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP9_PCKT_ADRS;
  union                                            /* Offset=0x0154 : EP9_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP9_LDATA:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP9_DMACNT:9;                               /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP9_LEN_DCNT;
  union                                            /* Offset=0x0158 : EP9_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP9_RDATA1:8;                               /* [7:0] */
      __I  unsigned long   EP9_RDATA2:8;                               /* [15:8] */
      __I  unsigned long   EP9_RDATA3:8;                               /* [23:16] */
      __I  unsigned long   EP9_RDATA4:8;                               /* [31:24] */
    } BIT;
  } EP9_READ;
  union                                            /* Offset=0x015C : EP9_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP9_WDATA1:8;                               /* [7:0] */
      __O  unsigned long   EP9_WDATA2:8;                               /* [15:8] */
      __O  unsigned long   EP9_WDATA3:8;                               /* [23:16] */
      __O  unsigned long   EP9_WDATA4:8;                               /* [31:24] */
    } BIT;
  } EP9_WRITE;
  union                                            /* Offset=0x0160 : EP10_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP10_ONAK:1;                                /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP10_OSTL:1;                                /* [2] */
      __IO unsigned long   EP10_ISTL:1;                                /* [3] */
      __O  unsigned long   EP10_OSTL_EN:1;                             /* [4] */
      __O  unsigned long   EP10_DW:2;                                  /* [6:5] */
      __O  unsigned long   EP10_DEND:1;                                /* [7] */
      __O  unsigned long   EP10_CBCLR:1;                               /* [8] */
      __O  unsigned long   EP10_BCLR:1;                                /* [9] */
      __O  unsigned long   EP10_OPIDCLR:1;                             /* [10] */
      __O  unsigned long   EP10_IPIDCLR:1;                             /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP10_AUTO:1;                                /* [16] */
      __IO unsigned long   EP10_OVERSEL:1;                             /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP10_MODE:2;                                /* [25:24] */
      __IO unsigned long   EP10_DIR0:1;                                /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP10_BUF_TYPE:1;                            /* [30] */
      __IO unsigned long   EP10_EN:1;                                  /* [31] */
    } BIT;
  } EP10_CONTROL;
  union                                            /* Offset=0x0164 : EP10_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP10_IN_EMPTY:1;                            /* [0] */
      __I  unsigned long   EP10_IN_FULL:1;                             /* [1] */
      __I  unsigned long   EP10_IN_DATA:1;                             /* [2] */
      __IO unsigned long   EP10_IN_INT:1;                              /* [3] */
      __IO unsigned long   EP10_IN_STALL_INT:1;                        /* [4] */
      __IO unsigned long   EP10_IN_NAK_ERR_INT:1;                      /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP10_IN_END_INT:1;                          /* [7] */
      __I  unsigned long   EP10_ISO_UR:1;                              /* [8] */
      __I  unsigned long   EP10_IN_NOTKN:1;                            /* [9] */
      __I  unsigned long   EP10_IPID:1;                                /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP10_OUT_EMPTY:1;                           /* [16] */
      __I  unsigned long   EP10_OUT_FULL:1;                            /* [17] */
      __IO unsigned long   EP10_OUT_NULL_INT:1;                        /* [18] */
      __IO unsigned long   EP10_OUT_INT:1;                             /* [19] */
      __IO unsigned long   EP10_OUT_STALL_INT:1;                       /* [20] */
      __IO unsigned long   EP10_OUT_NAK_ERR_INT:1;                     /* [21] */
      __IO unsigned long   EP10_OUT_OR_INT:1;                          /* [22] */
      __IO unsigned long   EP10_OUT_END_INT:1;                         /* [23] */
      __I  unsigned long   EP10_ISO_CRC:1;                             /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP10_ISO_OR:1;                              /* [26] */
      __I  unsigned long   EP10_OUT_NOTKN:1;                           /* [27] */
      __I  unsigned long   EP10_OPID:1;                                /* [28] */
      __I  unsigned long   EP10_ISO_PIDERR:1;                          /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP10_STATUS;
  union                                            /* Offset=0x0168 : EP10_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP10_IN_EN:1;                               /* [3] */
      __IO unsigned long   EP10_IN_STALL_EN:1;                         /* [4] */
      __IO unsigned long   EP10_IN_NAK_ERR_EN:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP10_IN_END_EN:1;                           /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP10_OUT_NULL_EN:1;                         /* [18] */
      __IO unsigned long   EP10_OUT_EN:1;                              /* [19] */
      __IO unsigned long   EP10_OUT_STALL_EN:1;                        /* [20] */
      __IO unsigned long   EP10_OUT_NAK_ERR_EN:1;                      /* [21] */
      __IO unsigned long   EP10_OUT_OR_EN:1;                           /* [22] */
      __IO unsigned long   EP10_OUT_END_EN:1;                          /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP10_INT_ENA;
  union                                            /* Offset=0x016C : EP10_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP10_DMAMODE0:1;                            /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP10_DMA_EN:1;                              /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP10_STOP_SET:1;                            /* [8] */
      __IO unsigned long   EP10_BURST_SET:1;                           /* [9] */
      __IO unsigned long   EP10_DEND_SET:1;                            /* [10] */
      __IO unsigned long   EP10_STOP_MODE:1;                           /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP10_DMA_CTRL;
  union                                            /* Offset=0x0170 : EP10_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP10_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP10_BASEAD:13;                             /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP10_PCKT_ADRS;
  union                                            /* Offset=0x0174 : EP10_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP10_LDATA:11;                              /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP10_DMACNT:9;                              /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP10_LEN_DCNT;
  union                                            /* Offset=0x0178 : EP10_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP10_RDATA1:8;                              /* [7:0] */
      __I  unsigned long   EP10_RDATA2:8;                              /* [15:8] */
      __I  unsigned long   EP10_RDATA3:8;                              /* [23:16] */
      __I  unsigned long   EP10_RDATA4:8;                              /* [31:24] */
    } BIT;
  } EP10_READ;
  union                                            /* Offset=0x017C : EP10_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP10_WDATA1:8;                              /* [7:0] */
      __O  unsigned long   EP10_WDATA2:8;                              /* [15:8] */
      __O  unsigned long   EP10_WDATA3:8;                              /* [23:16] */
      __O  unsigned long   EP10_WDATA4:8;                              /* [31:24] */
    } BIT;
  } EP10_WRITE;
  union                                            /* Offset=0x0180 : EP11_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP11_ONAK:1;                                /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP11_OSTL:1;                                /* [2] */
      __IO unsigned long   EP11_ISTL:1;                                /* [3] */
      __O  unsigned long   EP11_OSTL_EN:1;                             /* [4] */
      __O  unsigned long   EP11_DW:2;                                  /* [6:5] */
      __O  unsigned long   EP11_DEND:1;                                /* [7] */
      __O  unsigned long   EP11_CBCLR:1;                               /* [8] */
      __O  unsigned long   EP11_BCLR:1;                                /* [9] */
      __O  unsigned long   EP11_OPIDCLR:1;                             /* [10] */
      __O  unsigned long   EP11_IPIDCLR:1;                             /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP11_AUTO:1;                                /* [16] */
      __IO unsigned long   EP11_OVERSEL:1;                             /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP11_MODE:2;                                /* [25:24] */
      __IO unsigned long   EP11_DIR0:1;                                /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP11_BUF_TYPE:1;                            /* [30] */
      __IO unsigned long   EP11_EN:1;                                  /* [31] */
    } BIT;
  } EP11_CONTROL;
  union                                            /* Offset=0x0184 : EP11_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP11_IN_EMPTY:1;                            /* [0] */
      __I  unsigned long   EP11_IN_FULL:1;                             /* [1] */
      __I  unsigned long   EP11_IN_DATA:1;                             /* [2] */
      __IO unsigned long   EP11_IN_INT:1;                              /* [3] */
      __IO unsigned long   EP11_IN_STALL_INT:1;                        /* [4] */
      __IO unsigned long   EP11_IN_NAK_ERR_INT:1;                      /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP11_IN_END_INT:1;                          /* [7] */
      __I  unsigned long   EP11_ISO_UR:1;                              /* [8] */
      __I  unsigned long   EP11_IN_NOTKN:1;                            /* [9] */
      __I  unsigned long   EP11_IPID:1;                                /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP11_OUT_EMPTY:1;                           /* [16] */
      __I  unsigned long   EP11_OUT_FULL:1;                            /* [17] */
      __IO unsigned long   EP11_OUT_NULL_INT:1;                        /* [18] */
      __IO unsigned long   EP11_OUT_INT:1;                             /* [19] */
      __IO unsigned long   EP11_OUT_STALL_INT:1;                       /* [20] */
      __IO unsigned long   EP11_OUT_NAK_ERR_INT:1;                     /* [21] */
      __IO unsigned long   EP11_OUT_OR_INT:1;                          /* [22] */
      __IO unsigned long   EP11_OUT_END_INT:1;                         /* [23] */
      __I  unsigned long   EP11_ISO_CRC:1;                             /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP11_ISO_OR:1;                              /* [26] */
      __I  unsigned long   EP11_OUT_NOTKN:1;                           /* [27] */
      __I  unsigned long   EP11_OPID:1;                                /* [28] */
      __I  unsigned long   EP11_ISO_PIDERR:1;                          /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP11_STATUS;
  union                                            /* Offset=0x0188 : EP11_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP11_IN_EN:1;                               /* [3] */
      __IO unsigned long   EP11_IN_STALL_EN:1;                         /* [4] */
      __IO unsigned long   EP11_IN_NAK_ERR_EN:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP11_IN_END_EN:1;                           /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP11_OUT_NULL_EN:1;                         /* [18] */
      __IO unsigned long   EP11_OUT_EN:1;                              /* [19] */
      __IO unsigned long   EP11_OUT_STALL_EN:1;                        /* [20] */
      __IO unsigned long   EP11_OUT_NAK_ERR_EN:1;                      /* [21] */
      __IO unsigned long   EP11_OUT_OR_EN:1;                           /* [22] */
      __IO unsigned long   EP11_OUT_END_EN:1;                          /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP11_INT_ENA;
  union                                            /* Offset=0x018C : EP11_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP11_DMAMODE0:1;                            /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP11_DMA_EN:1;                              /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP11_STOP_SET:1;                            /* [8] */
      __IO unsigned long   EP11_BURST_SET:1;                           /* [9] */
      __IO unsigned long   EP11_DEND_SET:1;                            /* [10] */
      __IO unsigned long   EP11_STOP_MODE:1;                           /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP11_DMA_CTRL;
  union                                            /* Offset=0x0190 : EP11_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP11_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP11_BASEAD:13;                             /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP11_PCKT_ADRS;
  union                                            /* Offset=0x0194 : EP11_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP11_LDATA:11;                              /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP11_DMACNT:9;                              /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP11_LEN_DCNT;
  union                                            /* Offset=0x0198 : EP11_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP11_RDATA1:8;                              /* [7:0] */
      __I  unsigned long   EP11_RDATA2:8;                              /* [15:8] */
      __I  unsigned long   EP11_RDATA3:8;                              /* [23:16] */
      __I  unsigned long   EP11_RDATA4:8;                              /* [31:24] */
    } BIT;
  } EP11_READ;
  union                                            /* Offset=0x019C : EP11_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP11_WDATA1:8;                              /* [7:0] */
      __O  unsigned long   EP11_WDATA2:8;                              /* [15:8] */
      __O  unsigned long   EP11_WDATA3:8;                              /* [23:16] */
      __O  unsigned long   EP11_WDATA4:8;                              /* [31:24] */
    } BIT;
  } EP11_WRITE;
  union                                            /* Offset=0x01A0 : EP12_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP12_ONAK:1;                                /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP12_OSTL:1;                                /* [2] */
      __IO unsigned long   EP12_ISTL:1;                                /* [3] */
      __O  unsigned long   EP12_OSTL_EN:1;                             /* [4] */
      __O  unsigned long   EP12_DW:2;                                  /* [6:5] */
      __O  unsigned long   EP12_DEND:1;                                /* [7] */
      __O  unsigned long   EP12_CBCLR:1;                               /* [8] */
      __O  unsigned long   EP12_BCLR:1;                                /* [9] */
      __O  unsigned long   EP12_OPIDCLR:1;                             /* [10] */
      __O  unsigned long   EP12_IPIDCLR:1;                             /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP12_AUTO:1;                                /* [16] */
      __IO unsigned long   EP12_OVERSEL:1;                             /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP12_MODE:2;                                /* [25:24] */
      __IO unsigned long   EP12_DIR0:1;                                /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP12_BUF_TYPE:1;                            /* [30] */
      __IO unsigned long   EP12_EN:1;                                  /* [31] */
    } BIT;
  } EP12_CONTROL;
  union                                            /* Offset=0x01A4 : EP12_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP12_IN_EMPTY:1;                            /* [0] */
      __I  unsigned long   EP12_IN_FULL:1;                             /* [1] */
      __I  unsigned long   EP12_IN_DATA:1;                             /* [2] */
      __IO unsigned long   EP12_IN_INT:1;                              /* [3] */
      __IO unsigned long   EP12_IN_STALL_INT:1;                        /* [4] */
      __IO unsigned long   EP12_IN_NAK_ERR_INT:1;                      /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP12_IN_END_INT:1;                          /* [7] */
      __I  unsigned long   EP12_ISO_UR:1;                              /* [8] */
      __I  unsigned long   EP12_IN_NOTKN:1;                            /* [9] */
      __I  unsigned long   EP12_IPID:1;                                /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP12_OUT_EMPTY:1;                           /* [16] */
      __I  unsigned long   EP12_OUT_FULL:1;                            /* [17] */
      __IO unsigned long   EP12_OUT_NULL_INT:1;                        /* [18] */
      __IO unsigned long   EP12_OUT_INT:1;                             /* [19] */
      __IO unsigned long   EP12_OUT_STALL_INT:1;                       /* [20] */
      __IO unsigned long   EP12_OUT_NAK_ERR_INT:1;                     /* [21] */
      __IO unsigned long   EP12_OUT_OR_INT:1;                          /* [22] */
      __IO unsigned long   EP12_OUT_END_INT:1;                         /* [23] */
      __I  unsigned long   EP12_ISO_CRC:1;                             /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP12_ISO_OR:1;                              /* [26] */
      __I  unsigned long   EP12_OUT_NOTKN:1;                           /* [27] */
      __I  unsigned long   EP12_OPID:1;                                /* [28] */
      __I  unsigned long   EP12_ISO_PIDERR:1;                          /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP12_STATUS;
  union                                            /* Offset=0x01A8 : EP12_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP12_IN_EN:1;                               /* [3] */
      __IO unsigned long   EP12_IN_STALL_EN:1;                         /* [4] */
      __IO unsigned long   EP12_IN_NAK_ERR_EN:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP12_IN_END_EN:1;                           /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP12_OUT_NULL_EN:1;                         /* [18] */
      __IO unsigned long   EP12_OUT_EN:1;                              /* [19] */
      __IO unsigned long   EP12_OUT_STALL_EN:1;                        /* [20] */
      __IO unsigned long   EP12_OUT_NAK_ERR_EN:1;                      /* [21] */
      __IO unsigned long   EP12_OUT_OR_EN:1;                           /* [22] */
      __IO unsigned long   EP12_OUT_END_EN:1;                          /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP12_INT_ENA;
  union                                            /* Offset=0x01AC : EP12_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP12_DMAMODE0:1;                            /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP12_DMA_EN:1;                              /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP12_STOP_SET:1;                            /* [8] */
      __IO unsigned long   EP12_BURST_SET:1;                           /* [9] */
      __IO unsigned long   EP12_DEND_SET:1;                            /* [10] */
      __IO unsigned long   EP12_STOP_MODE:1;                           /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP12_DMA_CTRL;
  union                                            /* Offset=0x01B0 : EP12_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP12_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP12_BASEAD:13;                             /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP12_PCKT_ADRS;
  union                                            /* Offset=0x01B4 : EP12_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP12_LDATA:11;                              /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP12_DMACNT:9;                              /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP12_LEN_DCNT;
  union                                            /* Offset=0x01B8 : EP12_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP12_RDATA1:8;                              /* [7:0] */
      __I  unsigned long   EP12_RDATA2:8;                              /* [15:8] */
      __I  unsigned long   EP12_RDATA3:8;                              /* [23:16] */
      __I  unsigned long   EP12_RDATA4:8;                              /* [31:24] */
    } BIT;
  } EP12_READ;
  union                                            /* Offset=0x01BC : EP12_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP12_WDATA1:8;                              /* [7:0] */
      __O  unsigned long   EP12_WDATA2:8;                              /* [15:8] */
      __O  unsigned long   EP12_WDATA3:8;                              /* [23:16] */
      __O  unsigned long   EP12_WDATA4:8;                              /* [31:24] */
    } BIT;
  } EP12_WRITE;
  union                                            /* Offset=0x01C0 : EP13_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP13_ONAK:1;                                /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP13_OSTL:1;                                /* [2] */
      __IO unsigned long   EP13_ISTL:1;                                /* [3] */
      __O  unsigned long   EP13_OSTL_EN:1;                             /* [4] */
      __O  unsigned long   EP13_DW:2;                                  /* [6:5] */
      __O  unsigned long   EP13_DEND:1;                                /* [7] */
      __O  unsigned long   EP13_CBCLR:1;                               /* [8] */
      __O  unsigned long   EP13_BCLR:1;                                /* [9] */
      __O  unsigned long   EP13_OPIDCLR:1;                             /* [10] */
      __O  unsigned long   EP13_IPIDCLR:1;                             /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP13_AUTO:1;                                /* [16] */
      __IO unsigned long   EP13_OVERSEL:1;                             /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP13_MODE:2;                                /* [25:24] */
      __IO unsigned long   EP13_DIR0:1;                                /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP13_BUF_TYPE:1;                            /* [30] */
      __IO unsigned long   EP13_EN:1;                                  /* [31] */
    } BIT;
  } EP13_CONTROL;
  union                                            /* Offset=0x01C4 : EP13_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP13_IN_EMPTY:1;                            /* [0] */
      __I  unsigned long   EP13_IN_FULL:1;                             /* [1] */
      __I  unsigned long   EP13_IN_DATA:1;                             /* [2] */
      __IO unsigned long   EP13_IN_INT:1;                              /* [3] */
      __IO unsigned long   EP13_IN_STALL_INT:1;                        /* [4] */
      __IO unsigned long   EP13_IN_NAK_ERR_INT:1;                      /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP13_IN_END_INT:1;                          /* [7] */
      __I  unsigned long   EP13_ISO_UR:1;                              /* [8] */
      __I  unsigned long   EP13_IN_NOTKN:1;                            /* [9] */
      __I  unsigned long   EP13_IPID:1;                                /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP13_OUT_EMPTY:1;                           /* [16] */
      __I  unsigned long   EP13_OUT_FULL:1;                            /* [17] */
      __IO unsigned long   EP13_OUT_NULL_INT:1;                        /* [18] */
      __IO unsigned long   EP13_OUT_INT:1;                             /* [19] */
      __IO unsigned long   EP13_OUT_STALL_INT:1;                       /* [20] */
      __IO unsigned long   EP13_OUT_NAK_ERR_INT:1;                     /* [21] */
      __IO unsigned long   EP13_OUT_OR_INT:1;                          /* [22] */
      __IO unsigned long   EP13_OUT_END_INT:1;                         /* [23] */
      __I  unsigned long   EP13_ISO_CRC:1;                             /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP13_ISO_OR:1;                              /* [26] */
      __I  unsigned long   EP13_OUT_NOTKN:1;                           /* [27] */
      __I  unsigned long   EP13_OPID:1;                                /* [28] */
      __I  unsigned long   EP13_ISO_PIDERR:1;                          /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP13_STATUS;
  union                                            /* Offset=0x01C8 : EP13_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP13_IN_EN:1;                               /* [3] */
      __IO unsigned long   EP13_IN_STALL_EN:1;                         /* [4] */
      __IO unsigned long   EP13_IN_NAK_ERR_EN:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP13_IN_END_EN:1;                           /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP13_OUT_NULL_EN:1;                         /* [18] */
      __IO unsigned long   EP13_OUT_EN:1;                              /* [19] */
      __IO unsigned long   EP13_OUT_STALL_EN:1;                        /* [20] */
      __IO unsigned long   EP13_OUT_NAK_ERR_EN:1;                      /* [21] */
      __IO unsigned long   EP13_OUT_OR_EN:1;                           /* [22] */
      __IO unsigned long   EP13_OUT_END_EN:1;                          /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP13_INT_ENA;
  union                                            /* Offset=0x01CC : EP13_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP13_DMAMODE0:1;                            /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP13_DMA_EN:1;                              /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP13_STOP_SET:1;                            /* [8] */
      __IO unsigned long   EP13_BURST_SET:1;                           /* [9] */
      __IO unsigned long   EP13_DEND_SET:1;                            /* [10] */
      __IO unsigned long   EP13_STOP_MODE:1;                           /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP13_DMA_CTRL;
  union                                            /* Offset=0x01D0 : EP13_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP13_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP13_BASEAD:13;                             /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP13_PCKT_ADRS;
  union                                            /* Offset=0x01D4 : EP13_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP13_LDATA:11;                              /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP13_DMACNT:9;                              /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP13_LEN_DCNT;
  union                                            /* Offset=0x01D8 : EP13_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP13_RDATA1:8;                              /* [7:0] */
      __I  unsigned long   EP13_RDATA2:8;                              /* [15:8] */
      __I  unsigned long   EP13_RDATA3:8;                              /* [23:16] */
      __I  unsigned long   EP13_RDATA4:8;                              /* [31:24] */
    } BIT;
  } EP13_READ;
  union                                            /* Offset=0x01DC : EP13_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP13_WDATA1:8;                              /* [7:0] */
      __O  unsigned long   EP13_WDATA2:8;                              /* [15:8] */
      __O  unsigned long   EP13_WDATA3:8;                              /* [23:16] */
      __O  unsigned long   EP13_WDATA4:8;                              /* [31:24] */
    } BIT;
  } EP13_WRITE;
  union                                            /* Offset=0x01E0 : EP14_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP14_ONAK:1;                                /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP14_OSTL:1;                                /* [2] */
      __IO unsigned long   EP14_ISTL:1;                                /* [3] */
      __O  unsigned long   EP14_OSTL_EN:1;                             /* [4] */
      __O  unsigned long   EP14_DW:2;                                  /* [6:5] */
      __O  unsigned long   EP14_DEND:1;                                /* [7] */
      __O  unsigned long   EP14_CBCLR:1;                               /* [8] */
      __O  unsigned long   EP14_BCLR:1;                                /* [9] */
      __O  unsigned long   EP14_OPIDCLR:1;                             /* [10] */
      __O  unsigned long   EP14_IPIDCLR:1;                             /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP14_AUTO:1;                                /* [16] */
      __IO unsigned long   EP14_OVERSEL:1;                             /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP14_MODE:2;                                /* [25:24] */
      __IO unsigned long   EP14_DIR0:1;                                /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP14_BUF_TYPE:1;                            /* [30] */
      __IO unsigned long   EP14_EN:1;                                  /* [31] */
    } BIT;
  } EP14_CONTROL;
  union                                            /* Offset=0x01E4 : EP14_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP14_IN_EMPTY:1;                            /* [0] */
      __I  unsigned long   EP14_IN_FULL:1;                             /* [1] */
      __I  unsigned long   EP14_IN_DATA:1;                             /* [2] */
      __IO unsigned long   EP14_IN_INT:1;                              /* [3] */
      __IO unsigned long   EP14_IN_STALL_INT:1;                        /* [4] */
      __IO unsigned long   EP14_IN_NAK_ERR_INT:1;                      /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP14_IN_END_INT:1;                          /* [7] */
      __I  unsigned long   EP14_ISO_UR:1;                              /* [8] */
      __I  unsigned long   EP14_IN_NOTKN:1;                            /* [9] */
      __I  unsigned long   EP14_IPID:1;                                /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP14_OUT_EMPTY:1;                           /* [16] */
      __I  unsigned long   EP14_OUT_FULL:1;                            /* [17] */
      __IO unsigned long   EP14_OUT_NULL_INT:1;                        /* [18] */
      __IO unsigned long   EP14_OUT_INT:1;                             /* [19] */
      __IO unsigned long   EP14_OUT_STALL_INT:1;                       /* [20] */
      __IO unsigned long   EP14_OUT_NAK_ERR_INT:1;                     /* [21] */
      __IO unsigned long   EP14_OUT_OR_INT:1;                          /* [22] */
      __IO unsigned long   EP14_OUT_END_INT:1;                         /* [23] */
      __I  unsigned long   EP14_ISO_CRC:1;                             /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP14_ISO_OR:1;                              /* [26] */
      __I  unsigned long   EP14_OUT_NOTKN:1;                           /* [27] */
      __I  unsigned long   EP14_OPID:1;                                /* [28] */
      __I  unsigned long   EP14_ISO_PIDERR:1;                          /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP14_STATUS;
  union                                            /* Offset=0x01E8 : EP14_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP14_IN_EN:1;                               /* [3] */
      __IO unsigned long   EP14_IN_STALL_EN:1;                         /* [4] */
      __IO unsigned long   EP14_IN_NAK_ERR_EN:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP14_IN_END_EN:1;                           /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP14_OUT_NULL_EN:1;                         /* [18] */
      __IO unsigned long   EP14_OUT_EN:1;                              /* [19] */
      __IO unsigned long   EP14_OUT_STALL_EN:1;                        /* [20] */
      __IO unsigned long   EP14_OUT_NAK_ERR_EN:1;                      /* [21] */
      __IO unsigned long   EP14_OUT_OR_EN:1;                           /* [22] */
      __IO unsigned long   EP14_OUT_END_EN:1;                          /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP14_INT_ENA;
  union                                            /* Offset=0x01EC : EP14_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP14_DMAMODE0:1;                            /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP14_DMA_EN:1;                              /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP14_STOP_SET:1;                            /* [8] */
      __IO unsigned long   EP14_BURST_SET:1;                           /* [9] */
      __IO unsigned long   EP14_DEND_SET:1;                            /* [10] */
      __IO unsigned long   EP14_STOP_MODE:1;                           /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP14_DMA_CTRL;
  union                                            /* Offset=0x01F0 : EP14_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP14_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP14_BASEAD:13;                             /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP14_PCKT_ADRS;
  union                                            /* Offset=0x01F4 : EP14_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP14_LDATA:11;                              /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP14_DMACNT:9;                              /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP14_LEN_DCNT;
  union                                            /* Offset=0x01F8 : EP14_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP14_RDATA1:8;                              /* [7:0] */
      __I  unsigned long   EP14_RDATA2:8;                              /* [15:8] */
      __I  unsigned long   EP14_RDATA3:8;                              /* [23:16] */
      __I  unsigned long   EP14_RDATA4:8;                              /* [31:24] */
    } BIT;
  } EP14_READ;
  union                                            /* Offset=0x01FC : EP14_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP14_WDATA1:8;                              /* [7:0] */
      __O  unsigned long   EP14_WDATA2:8;                              /* [15:8] */
      __O  unsigned long   EP14_WDATA3:8;                              /* [23:16] */
      __O  unsigned long   EP14_WDATA4:8;                              /* [31:24] */
    } BIT;
  } EP14_WRITE;
  union                                            /* Offset=0x0200 : EP15_CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP15_ONAK:1;                                /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   EP15_OSTL:1;                                /* [2] */
      __IO unsigned long   EP15_ISTL:1;                                /* [3] */
      __O  unsigned long   EP15_OSTL_EN:1;                             /* [4] */
      __O  unsigned long   EP15_DW:2;                                  /* [6:5] */
      __O  unsigned long   EP15_DEND:1;                                /* [7] */
      __O  unsigned long   EP15_CBCLR:1;                               /* [8] */
      __O  unsigned long   EP15_BCLR:1;                                /* [9] */
      __O  unsigned long   EP15_OPIDCLR:1;                             /* [10] */
      __O  unsigned long   EP15_IPIDCLR:1;                             /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   EP15_AUTO:1;                                /* [16] */
      __IO unsigned long   EP15_OVERSEL:1;                             /* [17] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __I  unsigned long   EP15_MODE:2;                                /* [25:24] */
      __IO unsigned long   EP15_DIR0:1;                                /* [26] */
      __IO unsigned long   :3;                                         /* [29:27] */
      __I  unsigned long   EP15_BUF_TYPE:1;                            /* [30] */
      __IO unsigned long   EP15_EN:1;                                  /* [31] */
    } BIT;
  } EP15_CONTROL;
  union                                            /* Offset=0x0204 : EP15_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP15_IN_EMPTY:1;                            /* [0] */
      __I  unsigned long   EP15_IN_FULL:1;                             /* [1] */
      __I  unsigned long   EP15_IN_DATA:1;                             /* [2] */
      __IO unsigned long   EP15_IN_INT:1;                              /* [3] */
      __IO unsigned long   EP15_IN_STALL_INT:1;                        /* [4] */
      __IO unsigned long   EP15_IN_NAK_ERR_INT:1;                      /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP15_IN_END_INT:1;                          /* [7] */
      __I  unsigned long   EP15_ISO_UR:1;                              /* [8] */
      __I  unsigned long   EP15_IN_NOTKN:1;                            /* [9] */
      __I  unsigned long   EP15_IPID:1;                                /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   EP15_OUT_EMPTY:1;                           /* [16] */
      __I  unsigned long   EP15_OUT_FULL:1;                            /* [17] */
      __IO unsigned long   EP15_OUT_NULL_INT:1;                        /* [18] */
      __IO unsigned long   EP15_OUT_INT:1;                             /* [19] */
      __IO unsigned long   EP15_OUT_STALL_INT:1;                       /* [20] */
      __IO unsigned long   EP15_OUT_NAK_ERR_INT:1;                     /* [21] */
      __IO unsigned long   EP15_OUT_OR_INT:1;                          /* [22] */
      __IO unsigned long   EP15_OUT_END_INT:1;                         /* [23] */
      __I  unsigned long   EP15_ISO_CRC:1;                             /* [24] */
      __IO unsigned long   :1;                                         /* [25] */
      __I  unsigned long   EP15_ISO_OR:1;                              /* [26] */
      __I  unsigned long   EP15_OUT_NOTKN:1;                           /* [27] */
      __I  unsigned long   EP15_OPID:1;                                /* [28] */
      __I  unsigned long   EP15_ISO_PIDERR:1;                          /* [29] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } EP15_STATUS;
  union                                            /* Offset=0x0208 : EP15_INT_ENA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   EP15_IN_EN:1;                               /* [3] */
      __IO unsigned long   EP15_IN_STALL_EN:1;                         /* [4] */
      __IO unsigned long   EP15_IN_NAK_ERR_EN:1;                       /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   EP15_IN_END_EN:1;                           /* [7] */
      __IO unsigned long   :10;                                        /* [17:8] */
      __IO unsigned long   EP15_OUT_NULL_EN:1;                         /* [18] */
      __IO unsigned long   EP15_OUT_EN:1;                              /* [19] */
      __IO unsigned long   EP15_OUT_STALL_EN:1;                        /* [20] */
      __IO unsigned long   EP15_OUT_NAK_ERR_EN:1;                      /* [21] */
      __IO unsigned long   EP15_OUT_OR_EN:1;                           /* [22] */
      __IO unsigned long   EP15_OUT_END_EN:1;                          /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP15_INT_ENA;
  union                                            /* Offset=0x020C : EP15_DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP15_DMAMODE0:1;                            /* [0] */
      __IO unsigned long   :3;                                         /* [3:1] */
      __IO unsigned long   EP15_DMA_EN:1;                              /* [4] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   EP15_STOP_SET:1;                            /* [8] */
      __IO unsigned long   EP15_BURST_SET:1;                           /* [9] */
      __IO unsigned long   EP15_DEND_SET:1;                            /* [10] */
      __IO unsigned long   EP15_STOP_MODE:1;                           /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } EP15_DMA_CTRL;
  union                                            /* Offset=0x0210 : EP15_PCKT_ADRS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP15_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP15_BASEAD:13;                             /* [28:16] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } EP15_PCKT_ADRS;
  union                                            /* Offset=0x0214 : EP15_LEN_DCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP15_LDATA:11;                              /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP15_DMACNT:9;                              /* [24:16] */
      __IO unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } EP15_LEN_DCNT;
  union                                            /* Offset=0x0218 : EP15_READ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   EP15_RDATA1:8;                              /* [7:0] */
      __I  unsigned long   EP15_RDATA2:8;                              /* [15:8] */
      __I  unsigned long   EP15_RDATA3:8;                              /* [23:16] */
      __I  unsigned long   EP15_RDATA4:8;                              /* [31:24] */
    } BIT;
  } EP15_READ;
  union                                            /* Offset=0x021C : EP15_WRITE */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   EP15_WDATA1:8;                              /* [7:0] */
      __O  unsigned long   EP15_WDATA2:8;                              /* [15:8] */
      __O  unsigned long   EP15_WDATA3:8;                              /* [23:16] */
      __O  unsigned long   EP15_WDATA4:8;                              /* [31:24] */
    } BIT;
  } EP15_WRITE;
} USBf_EPC_Type;
#endif  /* End of __USBf_EPC_SFR__DEFINE_HEADER__ */
