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
 **       for RZN1 I2C1
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __I2C_SFR__DEFINE_HEADER__
#define __I2C_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : I2C
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : IC_CON */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MASTER_MODE:1;                              /* [0] */
      __IO unsigned long   SPEED:2;                                    /* [2:1] */
      __IO unsigned long   IC_10BITADDR_SLAVE:1;                       /* [3] */
      __I  unsigned long   IC_10BITADDR_MASTER_rd_only:1;              /* [4] */
      __IO unsigned long   IC_RESTART_EN:1;                            /* [5] */
      __IO unsigned long   IC_SLAVE_DISABLE:1;                         /* [6] */
      __IO unsigned long   STOP_DET_IFADDRESSED:1;                     /* [7] */
      __IO unsigned long   TX_EMPTY_CTRL:1;                            /* [8] */
      __IO unsigned long   RX_FIFO_FULL_HLD_CTRL:1;                    /* [9] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } IC_CON;
  union                                            /* Offset=0x0004 : IC_TAR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IC_TAR:10;                                  /* [9:0] */
      __IO unsigned long   GC_OR_START:1;                              /* [10] */
      __IO unsigned long   SPECIAL:1;                                  /* [11] */
      __IO unsigned long   IC_10BITADDR_MASTER:1;                      /* [12] */
      __IO unsigned long   :19;                                        /* [31:13] */
    } BIT;
  } IC_TAR;
  union                                            /* Offset=0x0008 : IC_SAR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IC_SAR:10;                                  /* [9:0] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } IC_SAR;
  char                     wk_000C[0x0004];
  union                                            /* Offset=0x0010 : IC_DATA_CMD */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DAT:8;                                      /* [7:0] */
      __O  unsigned long   CMD:1;                                      /* [8] */
      __O  unsigned long   STOP:1;                                     /* [9] */
      __O  unsigned long   RESTART:1;                                  /* [10] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } IC_DATA_CMD;
  union                                            /* Offset=0x0014 : IC_SS_SCL_HCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IC_SS_SCL_HCNT:16;                          /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } IC_SS_SCL_HCNT;
  union                                            /* Offset=0x0018 : IC_SS_SCL_LCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IC_SS_SCL_LCNT:16;                          /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } IC_SS_SCL_LCNT;
  union                                            /* Offset=0x001C : IC_FS_SCL_HCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IC_FS_SCL_HCNT:16;                          /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } IC_FS_SCL_HCNT;
  union                                            /* Offset=0x0020 : IC_FS_SCL_LCNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IC_FS_SCL_LCNT:16;                          /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } IC_FS_SCL_LCNT;
  char                     wk_0024[0x0008];
  union                                            /* Offset=0x002C : IC_INTR_STAT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   R_RX_UNDER:1;                               /* [0] */
      __I  unsigned long   R_RX_OVER:1;                                /* [1] */
      __I  unsigned long   R_RX_FULL:1;                                /* [2] */
      __I  unsigned long   R_TX_OVER:1;                                /* [3] */
      __I  unsigned long   R_TX_EMPTY:1;                               /* [4] */
      __I  unsigned long   R_RD_REQ:1;                                 /* [5] */
      __I  unsigned long   R_TX_ABRT:1;                                /* [6] */
      __I  unsigned long   R_RX_DONE:1;                                /* [7] */
      __I  unsigned long   R_ACTIVITY:1;                               /* [8] */
      __I  unsigned long   R_STOP_DET:1;                               /* [9] */
      __I  unsigned long   R_START_DET:1;                              /* [10] */
      __I  unsigned long   R_GEN_CALL:1;                               /* [11] */
      __I  unsigned long   R_RESTART_DET:1;                            /* [12] */
      __I  unsigned long   R_MASTER_ON_HOLD:1;                         /* [13] */
      __I  unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } IC_INTR_STAT;
  union                                            /* Offset=0x0030 : IC_INTR_MASK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   M_RX_UNDER:1;                               /* [0] */
      __IO unsigned long   M_RX_OVER:1;                                /* [1] */
      __IO unsigned long   M_RX_FULL:1;                                /* [2] */
      __IO unsigned long   M_TX_OVER:1;                                /* [3] */
      __IO unsigned long   M_TX_EMPTY:1;                               /* [4] */
      __IO unsigned long   M_RD_REQ:1;                                 /* [5] */
      __IO unsigned long   M_TX_ABRT:1;                                /* [6] */
      __IO unsigned long   M_RX_DONE:1;                                /* [7] */
      __IO unsigned long   M_ACTIVITY:1;                               /* [8] */
      __IO unsigned long   M_STOP_DET:1;                               /* [9] */
      __IO unsigned long   M_START_DET:1;                              /* [10] */
      __IO unsigned long   M_GEN_CALL:1;                               /* [11] */
      __IO unsigned long   M_RESTART_DET:1;                            /* [12] */
      __IO unsigned long   M_MASTER_ON_HOLD:1;                         /* [13] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } IC_INTR_MASK;
  union                                            /* Offset=0x0034 : IC_RAW_INTR_STAT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RX_UNDER:1;                                 /* [0] */
      __I  unsigned long   RX_OVER:1;                                  /* [1] */
      __I  unsigned long   RX_FULL:1;                                  /* [2] */
      __I  unsigned long   TX_OVER:1;                                  /* [3] */
      __I  unsigned long   TX_EMPTY:1;                                 /* [4] */
      __I  unsigned long   RD_REQ:1;                                   /* [5] */
      __I  unsigned long   TX_ABRT:1;                                  /* [6] */
      __I  unsigned long   RX_DONE:1;                                  /* [7] */
      __I  unsigned long   RAW_INTR_ACTIVITY:1;                        /* [8] */
      __I  unsigned long   STOP_DET:1;                                 /* [9] */
      __I  unsigned long   START_DET:1;                                /* [10] */
      __I  unsigned long   GEN_CALL:1;                                 /* [11] */
      __I  unsigned long   RESTART_DET:1;                              /* [12] */
      __I  unsigned long   MASTER_ON_HOLD:1;                           /* [13] */
      __I  unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } IC_RAW_INTR_STAT;
  union                                            /* Offset=0x0038 : IC_RX_TL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RX_TL:8;                                    /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } IC_RX_TL;
  union                                            /* Offset=0x003C : IC_TX_TL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TX_TL:8;                                    /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } IC_TX_TL;
  union                                            /* Offset=0x0040 : IC_CLR_INTR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_INTR:1;                                 /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_INTR;
  union                                            /* Offset=0x0044 : IC_CLR_RX_UNDER */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_RX_UNDER:1;                             /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_RX_UNDER;
  union                                            /* Offset=0x0048 : IC_CLR_RX_OVER */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_RX_OVER:1;                              /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_RX_OVER;
  union                                            /* Offset=0x004C : IC_CLR_TX_OVER */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_TX_OVER:1;                              /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_TX_OVER;
  union                                            /* Offset=0x0050 : IC_CLR_RD_REQ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_RD_REQ:1;                               /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_RD_REQ;
  union                                            /* Offset=0x0054 : IC_CLR_TX_ABRT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_TX_ABRT:1;                              /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_TX_ABRT;
  union                                            /* Offset=0x0058 : IC_CLR_RX_DONE */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_RX_DONE:1;                              /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_RX_DONE;
  union                                            /* Offset=0x005C : IC_CLR_ACTIVITY */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_ACTIVITY:1;                             /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_ACTIVITY;
  union                                            /* Offset=0x0060 : IC_CLR_STOP_DET */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_STOP_DET:1;                             /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_STOP_DET;
  union                                            /* Offset=0x0064 : IC_CLR_START_DET */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_START_DET:1;                            /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_START_DET;
  union                                            /* Offset=0x0068 : IC_CLR_GEN_CALL */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_GEN_CALL:1;                             /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_GEN_CALL;
  union                                            /* Offset=0x006C : IC_ENABLE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ENABLE:1;                                   /* [0] */
      __IO unsigned long   ABORT:1;                                    /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } IC_ENABLE;
  union                                            /* Offset=0x0070 : IC_STATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IC_STATUS_ACTIVITY:1;                       /* [0] */
      __I  unsigned long   TFNF:1;                                     /* [1] */
      __I  unsigned long   TFE:1;                                      /* [2] */
      __I  unsigned long   RFNE:1;                                     /* [3] */
      __I  unsigned long   RFF:1;                                      /* [4] */
      __I  unsigned long   MST_ACTIVITY:1;                             /* [5] */
      __I  unsigned long   SLV_ACTIVITY:1;                             /* [6] */
      __I  unsigned long   :25;                                        /* [31:7] */
    } BIT;
  } IC_STATUS;
  union                                            /* Offset=0x0074 : IC_TXFLR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXFLR:4;                                    /* [3:0] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } IC_TXFLR;
  union                                            /* Offset=0x0078 : IC_RXFLR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXFLR:4;                                    /* [3:0] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } IC_RXFLR;
  union                                            /* Offset=0x007C : IC_SDA_HOLD */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IC_SDA_TX_HOLD:16;                          /* [15:0] */
      __IO unsigned long   IC_SDA_RX_HOLD:8;                           /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } IC_SDA_HOLD;
  union                                            /* Offset=0x0080 : IC_TX_ABRT_SOURCE */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ABRT_7B_ADDR_NOACK:1;                       /* [0] */
      __I  unsigned long   ABRT_10ADDR1_NOACK:1;                       /* [1] */
      __I  unsigned long   ABRT_10ADDR2_NOACK:1;                       /* [2] */
      __I  unsigned long   ABRT_TXDATA_NOACK:1;                        /* [3] */
      __I  unsigned long   ABRT_GCALL_NOACK:1;                         /* [4] */
      __I  unsigned long   ABRT_GCALL_READ:1;                          /* [5] */
      __I  unsigned long   :1;                                         /* [6] */
      __I  unsigned long   ABRT_SBYTE_ACKDET:1;                        /* [7] */
      __I  unsigned long   :1;                                         /* [8] */
      __I  unsigned long   ABRT_SBYTE_NORSTRT:1;                       /* [9] */
      __I  unsigned long   ABRT_10B_RD_NORSTRT:1;                      /* [10] */
      __I  unsigned long   ABRT_MASTER_DIS:1;                          /* [11] */
      __I  unsigned long   ARB_LOST:1;                                 /* [12] */
      __I  unsigned long   ABRT_SLVFLUSH_TXFIFO:1;                     /* [13] */
      __I  unsigned long   ABRT_SLV_ARBLOST:1;                         /* [14] */
      __I  unsigned long   ABRT_SLVRD_INTX:1;                          /* [15] */
      __I  unsigned long   ABRT_USER_ABRT:1;                           /* [16] */
      __I  unsigned long   :6;                                         /* [22:17] */
      __I  unsigned long   TX_FLUSH_CNT:9;                             /* [31:23] */
    } BIT;
  } IC_TX_ABRT_SOURCE;
  union                                            /* Offset=0x0084 : IC_SLV_DATA_NACK_ONLY */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   NACK:1;                                     /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_SLV_DATA_NACK_ONLY;
  char                     wk_0088[0x000C];
  union                                            /* Offset=0x0094 : IC_SDA_SETUP */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SDA_SETUP:8;                                /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } IC_SDA_SETUP;
  union                                            /* Offset=0x0098 : IC_ACK_GENERAL_CALL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ACK_GEN_CALL:1;                             /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_ACK_GENERAL_CALL;
  union                                            /* Offset=0x009C : IC_ENABLE_STATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IC_EN:1;                                    /* [0] */
      __I  unsigned long   SLV_DISABLED_WHILE_BUSY:1;                  /* [1] */
      __I  unsigned long   SLV_RX_DATA_LOST:1;                         /* [2] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IC_ENABLE_STATUS;
  union                                            /* Offset=0x00A0 : IC_FS_SPKLEN */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   IC_FS_SPKLEN:8;                             /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } IC_FS_SPKLEN;
  char                     wk_00A4[0x0004];
  union                                            /* Offset=0x00A8 : IC_CLR_RESTART_DET */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CLR_RESTART_DET:1;                          /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IC_CLR_RESTART_DET;
  char                     wk_00AC[0x0048];
  union                                            /* Offset=0x00F4 : IC_COMP_PARAM_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   APB_DATA_WIDTH:2;                           /* [1:0] */
      __I  unsigned long   MAX_SPEED_MODE:2;                           /* [3:2] */
      __I  unsigned long   HC_COUNT_VALUES:1;                          /* [4] */
      __I  unsigned long   INTR_IO:1;                                  /* [5] */
      __I  unsigned long   HAS_DMA:1;                                  /* [6] */
      __I  unsigned long   ADD_ENCODED_PARAMS:1;                       /* [7] */
      __I  unsigned long   RX_BUFFER_DEPTH:8;                          /* [15:8] */
      __I  unsigned long   TX_BUFFER_DEPTH:8;                          /* [23:16] */
      __I  unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } IC_COMP_PARAM_1;
} I2C_Type;
#endif  /* End of __I2C_SFR__DEFINE_HEADER__ */
