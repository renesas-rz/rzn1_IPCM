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
 **       for RZN1 NAND
 **
 **       revision 0.20 (2.Nov.2017)
 **
 **********************************************************************************************************************/
#ifndef __NAND_SFR__DEFINE_HEADER__
#define __NAND_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : NAND
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : COMMAND */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   cmd_seq:6;                                  /* [5:0] */
      __IO unsigned long   input_sel:1;                                /* [6] */
      __IO unsigned long   data_sel:1;                                 /* [7] */
      __IO unsigned long   cmd_0:8;                                    /* [15:8] */
      __IO unsigned long   cmd_1_cmd_3:8;                              /* [23:16] */
      __IO unsigned long   cmd_2:8;                                    /* [31:24] */
    } BIT;
  } COMMAND;
  union                                            /* Offset=0x0004 : CONTROL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   read_status_en:1;                           /* [0] */
      __IO unsigned long   ecc_block_size:2;                           /* [2:1] */
      __IO unsigned long   :1;                                         /* [3] */
      __IO unsigned long   int_en:1;                                   /* [4] */
      __IO unsigned long   ecc_en:1;                                   /* [5] */
      __IO unsigned long   block_size:2;                               /* [7:6] */
      __IO unsigned long   :4;                                         /* [11:8] */
      __IO unsigned long   io_width:1;                                 /* [12] */
      __IO unsigned long   bbm_en:1;                                   /* [13] */
      __IO unsigned long   prot_en:1;                                  /* [14] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   addr0_auto_incr:1;                          /* [16] */
      __IO unsigned long   addr1_auto_incr:1;                          /* [17] */
      __IO unsigned long   :3;                                         /* [20:18] */
      __IO unsigned long   small_block_en:1;                           /* [21] */
      __IO unsigned long   mlun_en:1;                                  /* [22] */
      __IO unsigned long   auto_read_stat_en:1;                        /* [23] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } CONTROL;
  union                                            /* Offset=0x0008 : STATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   mem0_st:1;                                  /* [0] */
      __I  unsigned long   mem1_st:1;                                  /* [1] */
      __I  unsigned long   mem2_st:1;                                  /* [2] */
      __I  unsigned long   mem3_st:1;                                  /* [3] */
      __I  unsigned long   :4;                                         /* [7:4] */
      __I  unsigned long   ctrl_stat:1;                                /* [8] */
      __I  unsigned long   datasize_error_st:1;                        /* [9] */
      __I  unsigned long   data_reg_st:1;                              /* [10] */
      __I  unsigned long   :5;                                         /* [15:11] */
      __I  unsigned long   cmd_id:8;                                   /* [23:16] */
      __I  unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } STATUS;
  union                                            /* Offset=0x000C : STATUS_MASK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   state_mask:8;                               /* [7:0] */
      __IO unsigned long   error_mask:8;                               /* [15:8] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } STATUS_MASK;
  union                                            /* Offset=0x0010 : INT_MASK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   prot_int_en:1;                              /* [0] */
      __IO unsigned long   cmd_end_int_en:1;                           /* [1] */
      __IO unsigned long   data_reg_int_en:1;                          /* [2] */
      __IO unsigned long   dma_int_en:1;                               /* [3] */
      __IO unsigned long   :2;                                         /* [5:4] */
      __IO unsigned long   pg_sz_err_int_en:1;                         /* [6] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   mem0_rdy_int_en:1;                          /* [8] */
      __IO unsigned long   mem1_rdy_int_en:1;                          /* [9] */
      __IO unsigned long   mem2_rdy_int_en:1;                          /* [10] */
      __IO unsigned long   mem3_rdy_int_en:1;                          /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   stat_err_int0_en:1;                         /* [16] */
      __IO unsigned long   stat_err_int1_en:1;                         /* [17] */
      __IO unsigned long   stat_err_int2_en:1;                         /* [18] */
      __IO unsigned long   stat_err_int3_en:1;                         /* [19] */
      __IO unsigned long   :4;                                         /* [23:20] */
      __IO unsigned long   ecc_int0_en:1;                              /* [24] */
      __IO unsigned long   ecc_int1_en:1;                              /* [25] */
      __IO unsigned long   ecc_int2_en:1;                              /* [26] */
      __IO unsigned long   ecc_int3_en:1;                              /* [27] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } INT_MASK;
  union                                            /* Offset=0x0014 : INT_STATUS */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   prot_int_fl:1;                              /* [0] */
      __IO unsigned long   cmd_end_int_fl:1;                           /* [1] */
      __IO unsigned long   data_reg_int_fl:1;                          /* [2] */
      __IO unsigned long   dma_int_fl:1;                               /* [3] */
      __IO unsigned long   :2;                                         /* [5:4] */
      __IO unsigned long   pg_sz_err_int_fl:1;                         /* [6] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   mem0_rdy_int_fl:1;                          /* [8] */
      __IO unsigned long   mem1_rdy_int_fl:1;                          /* [9] */
      __IO unsigned long   mem2_rdy_int_fl:1;                          /* [10] */
      __IO unsigned long   mem3_rdy_int_fl:1;                          /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   stat_err_int0_fl:1;                         /* [16] */
      __IO unsigned long   stat_err_int1_fl:1;                         /* [17] */
      __IO unsigned long   stat_err_int2_fl:1;                         /* [18] */
      __IO unsigned long   stat_err_int3_fl:1;                         /* [19] */
      __IO unsigned long   :4;                                         /* [23:20] */
      __IO unsigned long   ecc_int0_fl:1;                              /* [24] */
      __IO unsigned long   ecc_int1_fl:1;                              /* [25] */
      __IO unsigned long   ecc_int2_fl:1;                              /* [26] */
      __IO unsigned long   ecc_int3_fl:1;                              /* [27] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } INT_STATUS;
  union                                            /* Offset=0x0018 : ECC_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ecc_cap:3;                                  /* [2:0] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __IO unsigned long   err_threshold:6;                            /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   ecc_sel:2;                                  /* [17:16] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } ECC_CTRL;
  union                                            /* Offset=0x001C : ECC_OFFSET */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ecc_offset:16;                              /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } ECC_OFFSET;
  union                                            /* Offset=0x0020 : ECC_STAT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ecc_error_0:1;                              /* [0] */
      __IO unsigned long   ecc_error_1:1;                              /* [1] */
      __IO unsigned long   ecc_error_2:1;                              /* [2] */
      __IO unsigned long   ecc_error_3:1;                              /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __IO unsigned long   ecc_unc_0:1;                                /* [8] */
      __IO unsigned long   ecc_unc_1:1;                                /* [9] */
      __IO unsigned long   ecc_unc_2:1;                                /* [10] */
      __IO unsigned long   ecc_unc_3:1;                                /* [11] */
      __IO unsigned long   :4;                                         /* [15:12] */
      __IO unsigned long   ecc_over_0:1;                               /* [16] */
      __IO unsigned long   ecc_over_1:1;                               /* [17] */
      __IO unsigned long   ecc_over_2:1;                               /* [18] */
      __IO unsigned long   ecc_over_3:1;                               /* [19] */
      __IO unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } ECC_STAT;
  union                                            /* Offset=0x0024 : ADDR0_COL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   addr0_col:16;                               /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } ADDR0_COL;
  union                                            /* Offset=0x0028 : ADDR0_ROW */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   addr0_row:24;                               /* [23:0] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } ADDR0_ROW;
  union                                            /* Offset=0x002C : ADDR1_COL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   addr1_col:16;                               /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } ADDR1_COL;
  union                                            /* Offset=0x0030 : ADDR1_ROW */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   addr1_row:24;                               /* [23:0] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } ADDR1_ROW;
  union                                            /* Offset=0x0034 : PROTECT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   prot_down:16;                               /* [15:0] */
      __IO unsigned long   prot_up:16;                                 /* [31:16] */
    } BIT;
  } PROTECT;
  union                                            /* Offset=0x0038 : FIFO_DATA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   fifo_data:32;                               /* [31:0] */
    } BIT;
  } FIFO_DATA;
  union                                            /* Offset=0x003C : DATA_REG */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   data_reg:32;                                /* [31:0] */
    } BIT;
  } DATA_REG;
  union                                            /* Offset=0x0040 : DATA_REG_SIZE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   data_reg_size:2;                            /* [1:0] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } DATA_REG_SIZE;
  union                                            /* Offset=0x0044 : DEV0_PTR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ptr_addr:32;                                /* [31:0] */
    } BIT;
  } DEV0_PTR;
  union                                            /* Offset=0x0048 : DEV1_PTR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ptr_addr:32;                                /* [31:0] */
    } BIT;
  } DEV1_PTR;
  union                                            /* Offset=0x004C : DEV2_PTR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ptr_addr:32;                                /* [31:0] */
    } BIT;
  } DEV2_PTR;
  union                                            /* Offset=0x0050 : DEV3_PTR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ptr_addr:32;                                /* [31:0] */
    } BIT;
  } DEV3_PTR;
  char                     wk_0054[0x0010];
  union                                            /* Offset=0x0064 : DMA_ADDR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   dma_addr_l:32;                              /* [31:0] */
    } BIT;
  } DMA_ADDR;
  char                     wk_0068[0x0004];
  union                                            /* Offset=0x006C : DMA_CNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   cnt_init:32;                                /* [31:0] */
    } BIT;
  } DMA_CNT;
  union                                            /* Offset=0x0070 : DMA_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   dma_ready:1;                                /* [0] */
      __I  unsigned long   err_flag:1;                                 /* [1] */
      __IO unsigned long   dma_burst:3;                                /* [4:2] */
      __IO unsigned long   dma_mode:1;                                 /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   dma_start:1;                                /* [7] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } DMA_CTRL;
  union                                            /* Offset=0x0074 : BBM_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   rmp_init:1;                                 /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } BBM_CTRL;
  char                     wk_0078[0x0008];
  union                                            /* Offset=0x0080 : MEM_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   mem_ce:2;                                   /* [1:0] */
      __IO unsigned long   :6;                                         /* [7:2] */
      __IO unsigned long   mem0_wp:1;                                  /* [8] */
      __IO unsigned long   mem1_wp:1;                                  /* [9] */
      __IO unsigned long   mem2_wp:1;                                  /* [10] */
      __IO unsigned long   mem3_wp:1;                                  /* [11] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } MEM_CTRL;
  union                                            /* Offset=0x0084 : DATA_SIZE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   data_size:15;                               /* [14:0] */
      __IO unsigned long   :17;                                        /* [31:15] */
    } BIT;
  } DATA_SIZE;
  union                                            /* Offset=0x0088 : TIMINGS_ASYN */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   trwp:4;                                     /* [3:0] */
      __IO unsigned long   trwh:4;                                     /* [7:4] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } TIMINGS_ASYN;
  char                     wk_008C[0x0004];
  union                                            /* Offset=0x0090 : TIME_SEQ_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   tccs:6;                                     /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   tadl:6;                                     /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   trhw:6;                                     /* [21:16] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __IO unsigned long   twhr:6;                                     /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } TIME_SEQ_0;
  union                                            /* Offset=0x0094 : TIME_SEQ_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   twb:6;                                      /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   trr:6;                                      /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   tww:6;                                      /* [21:16] */
      __IO unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } TIME_SEQ_1;
  union                                            /* Offset=0x0098 : TIME_GEN_SEQ_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   t0_d0:6;                                    /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   t0_d1:6;                                    /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   t0_d2:6;                                    /* [21:16] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __IO unsigned long   t0_d3:6;                                    /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } TIME_GEN_SEQ_0;
  union                                            /* Offset=0x009C : TIME_GEN_SEQ_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   t0_d4:6;                                    /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   t0_d5:6;                                    /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   t0_d6:6;                                    /* [21:16] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __IO unsigned long   t0_d7:6;                                    /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } TIME_GEN_SEQ_1;
  union                                            /* Offset=0x00A0 : TIME_GEN_SEQ_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   t0_d8:6;                                    /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   t0_d9:6;                                    /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   t0_d10:6;                                   /* [21:16] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __IO unsigned long   t0_d11:6;                                   /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } TIME_GEN_SEQ_2;
  char                     wk_00A4[0x000C];
  union                                            /* Offset=0x00B0 : FIFO_INIT */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   fifo_init:1;                                /* [0] */
      __O  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } FIFO_INIT;
  union                                            /* Offset=0x00B4 : FIFO_STATE */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   df_r_empty:1;                               /* [0] */
      __I  unsigned long   df_w_full:1;                                /* [1] */
      __I  unsigned long   cf_empty:1;                                 /* [2] */
      __I  unsigned long   cf_full:1;                                  /* [3] */
      __I  unsigned long   cf_accept_r:1;                              /* [4] */
      __I  unsigned long   cf_accept_w:1;                              /* [5] */
      __I  unsigned long   df_r_full:1;                                /* [6] */
      __I  unsigned long   df_w_empty:1;                               /* [7] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } FIFO_STATE;
  union                                            /* Offset=0x00B8 : GEN_SEQ_CTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   cmd0_en:1;                                  /* [0] */
      __IO unsigned long   cmd1_en:1;                                  /* [1] */
      __IO unsigned long   cmd2_en:1;                                  /* [2] */
      __IO unsigned long   cmd3_en:1;                                  /* [3] */
      __IO unsigned long   col_a0:2;                                   /* [5:4] */
      __IO unsigned long   col_a1:2;                                   /* [7:6] */
      __IO unsigned long   row_a0:2;                                   /* [9:8] */
      __IO unsigned long   row_a1:2;                                   /* [11:10] */
      __IO unsigned long   data_en:1;                                  /* [12] */
      __IO unsigned long   delay_en:2;                                 /* [14:13] */
      __IO unsigned long   imd_seq:1;                                  /* [15] */
      __IO unsigned long   cmd3:8;                                     /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } GEN_SEQ_CTRL;
  union                                            /* Offset=0x00BC : MLUN */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   mlun_idx:3;                                 /* [2:0] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __IO unsigned long   mlun_sel:2;                                 /* [9:8] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } MLUN;
  union                                            /* Offset=0x00C0 : DEV0_SIZE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   dev_size:12;                                /* [11:0] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } DEV0_SIZE;
  union                                            /* Offset=0x00C4 : DEV1_SIZE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   dev_size:12;                                /* [11:0] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } DEV1_SIZE;
  union                                            /* Offset=0x00C8 : DEV2_SIZE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   dev_size:12;                                /* [11:0] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } DEV2_SIZE;
  union                                            /* Offset=0x00CC : DEV3_SIZE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   dev_size:12;                                /* [11:0] */
      __IO unsigned long   :20;                                        /* [31:12] */
    } BIT;
  } DEV3_SIZE;
  char                     wk_00D0[0x0044];
  union                                            /* Offset=0x0114 : DMA_TLVL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   dma_tlvl:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } DMA_TLVL;
  char                     wk_0118[0x000C];
  union                                            /* Offset=0x0124 : CMD_MARK */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   cmd_id:8;                                   /* [7:0] */
      __O  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } CMD_MARK;
  union                                            /* Offset=0x0128 : LUN_STATUS_0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   mem0_lun:8;                                 /* [7:0] */
      __I  unsigned long   mem1_lun:8;                                 /* [15:8] */
      __I  unsigned long   mem2_lun:8;                                 /* [23:16] */
      __I  unsigned long   mem3_lun:8;                                 /* [31:24] */
    } BIT;
  } LUN_STATUS_0;
  char                     wk_012C[0x0008];
  union                                            /* Offset=0x0134 : TIME_GEN_SEQ_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   t0_d12:6;                                   /* [5:0] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } TIME_GEN_SEQ_3;
  char                     wk_0138[0x0010];
  union                                            /* Offset=0x0148 : INT_STAT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   stat_value:8;                               /* [7:0] */
      __IO unsigned long   seq_id:2;                                   /* [9:8] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } INT_STAT;
  union                                            /* Offset=0x014C : ECC_CNT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   err_lvl0:6;                                 /* [5:0] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   err_lvl1:6;                                 /* [13:8] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   err_lvl2:6;                                 /* [21:16] */
      __IO unsigned long   :2;                                         /* [23:22] */
      __IO unsigned long   err_lvl3:6;                                 /* [29:24] */
      __IO unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } ECC_CNT;
  union                                            /* Offset=0x0150 : PARAM_REG */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bank_num:2;                                 /* [1:0] */
      __I  unsigned long   device_per_bank:2;                          /* [3:2] */
      __I  unsigned long   boot_implement:1;                           /* [4] */
      __I  unsigned long   bbm_implement:1;                            /* [5] */
      __I  unsigned long   bbm_int_implement:1;                        /* [6] */
      __I  unsigned long   protect_implement:1;                        /* [7] */
      __I  unsigned long   syn_mode_implement:1;                       /* [8] */
      __I  unsigned long   toggle_mode_implement:1;                    /* [9] */
      __I  unsigned long   clearnand_implement:1;                      /* [10] */
      __I  unsigned long   big_endian_implement:1;                     /* [11] */
      __I  unsigned long   bch32_conf_implement:1;                     /* [12] */
      __I  unsigned long   :6;                                         /* [18:13] */
      __I  unsigned long   noecc_implement:1;                          /* [19] */
      __I  unsigned long   ss_implement:1;                             /* [20] */
      __I  unsigned long   :1;                                         /* [21] */
      __I  unsigned long   gen_seq_implement:1;                        /* [22] */
      __I  unsigned long   small_block_implement:1;                    /* [23] */
      __I  unsigned long   dma_implement:1;                            /* [24] */
      __I  unsigned long   :4;                                         /* [28:25] */
      __I  unsigned long   asyn_reset_implement:1;                     /* [29] */
      __I  unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } PARAM_REG;
} NAND_Type;
#endif  /* End of __NAND_SFR__DEFINE_HEADER__ */
