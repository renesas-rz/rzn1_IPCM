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
 **       for RZN1 QSPI1
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __QSPI_SFR__DEFINE_HEADER__
#define __QSPI_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : QSPI
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : config_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   enb_qspi_fld:1;                             /* [0] */
      __IO unsigned long   sel_clk_pol_fld:1;                          /* [1] */
      __IO unsigned long   sel_clk_phase_fld:1;                        /* [2] */
      __IO unsigned long   :4;                                         /* [6:3] */
      __IO unsigned long   enb_dir_acc_ctlr_fld:1;                     /* [7] */
      __IO unsigned long   enb_legacy_ip_mode_fld:1;                   /* [8] */
      __IO unsigned long   periph_sel_dec_fld:1;                       /* [9] */
      __IO unsigned long   periph_cs_lines_fld:4;                      /* [13:10] */
      __IO unsigned long   wr_prot_flash_fld:1;                        /* [14] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   enb_ahb_addr_remap_fld:1;                   /* [16] */
      __IO unsigned long   enter_xip_mode_fld:1;                       /* [17] */
      __IO unsigned long   enter_xip_mode_imm_fld:1;                   /* [18] */
      __IO unsigned long   mstr_baud_div_fld:4;                        /* [22:19] */
      __IO unsigned long   enable_ahb_decoder_fld:1;                   /* [23] */
      __IO unsigned long   :7;                                         /* [30:24] */
      __I  unsigned long   qspi_idle_fld:1;                            /* [31] */
    } BIT;
  } config_reg;
  union                                            /* Offset=0x0004 : dev_instr_rd_config_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   rd_opcode_non_xip_fld:8;                    /* [7:0] */
      __IO unsigned long   instr_type_fld:2;                           /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   addr_xfer_type_std_mode_fld:2;              /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   data_xfer_type_ext_mode_fld:2;              /* [17:16] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __IO unsigned long   mode_bit_enable_fld:1;                      /* [20] */
      __IO unsigned long   :3;                                         /* [23:21] */
      __IO unsigned long   dummy_rd_clk_cycles_fld:5;                  /* [28:24] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } dev_instr_rd_config_reg;
  union                                            /* Offset=0x0008 : dev_instr_wr_config_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   wr_opcode_fld:8;                            /* [7:0] */
      __IO unsigned long   wel_dis_fld:1;                              /* [8] */
      __IO unsigned long   :3;                                         /* [11:9] */
      __IO unsigned long   addr_xfer_type_std_mode_fld:2;              /* [13:12] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   data_xfer_type_ext_mode_fld:2;              /* [17:16] */
      __IO unsigned long   :6;                                         /* [23:18] */
      __IO unsigned long   dummy_wr_clk_cycles_fld:5;                  /* [28:24] */
      __IO unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } dev_instr_wr_config_reg;
  union                                            /* Offset=0x000C : dev_delay_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   d_init_fld:8;                               /* [7:0] */
      __IO unsigned long   d_after_fld:8;                              /* [15:8] */
      __IO unsigned long   d_btwn_fld:8;                               /* [23:16] */
      __IO unsigned long   d_nss_fld:8;                                /* [31:24] */
    } BIT;
  } dev_delay_reg;
  union                                            /* Offset=0x0010 : rd_data_capture_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   delay_fld:4;                                /* [4:1] */
      __IO unsigned long   sample_edge_sel_fld:1;                      /* [5] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } rd_data_capture_reg;
  union                                            /* Offset=0x0014 : dev_size_config_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   num_addr_bytes_fld:4;                       /* [3:0] */
      __IO unsigned long   bytes_per_device_page_fld:12;               /* [15:4] */
      __IO unsigned long   bytes_per_subsector_fld:5;                  /* [20:16] */
      __IO unsigned long   mem_size_on_cs0_fld:2;                      /* [22:21] */
      __IO unsigned long   mem_size_on_cs1_fld:2;                      /* [24:23] */
      __IO unsigned long   mem_size_on_cs2_fld:2;                      /* [26:25] */
      __IO unsigned long   mem_size_on_cs3_fld:2;                      /* [28:27] */
      __I  unsigned long   dev_size_resv_fld:3;                        /* [31:29] */
    } BIT;
  } dev_size_config_reg;
  char                     wk_0018[0x000C];
  union                                            /* Offset=0x0024 : remap_addr_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   value_fld:32;                               /* [31:0] */
    } BIT;
  } remap_addr_reg;
  union                                            /* Offset=0x0028 : mode_bit_config_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   mode_fld:8;                                 /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } mode_bit_config_reg;
  char                     wk_002C[0x0004];
  union                                            /* Offset=0x0030 : tx_thresh_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   level_fld:4;                                /* [3:0] */
      __I  unsigned long   tx_thresh_resv_fld:28;                      /* [31:4] */
    } BIT;
  } tx_thresh_reg;
  union                                            /* Offset=0x0034 : rx_thresh_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   level_fld:4;                                /* [3:0] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rx_thresh_reg;
  union                                            /* Offset=0x0038 : write_completion_ctrl_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   opcode_fld:8;                               /* [7:0] */
      __IO unsigned long   polling_bit_index_fld:3;                    /* [10:8] */
      __IO unsigned long   :2;                                         /* [12:11] */
      __IO unsigned long   polling_polarity_fld:1;                     /* [13] */
      __IO unsigned long   disable_polling_fld:1;                      /* [14] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   poll_count_fld:8;                           /* [23:16] */
      __IO unsigned long   poll_rep_delay_fld:8;                       /* [31:24] */
    } BIT;
  } write_completion_ctrl_reg;
  union                                            /* Offset=0x003C : no_of_polls_bef_exp_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   no_of_polls_bef_exp_fld:32;                 /* [31:0] */
    } BIT;
  } no_of_polls_bef_exp_reg;
  union                                            /* Offset=0x0040 : irq_status_reg */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :1;                                         /* [0] */
      __I  unsigned long   underflow_det_fld:1;                        /* [1] */
      __I  unsigned long   :2;                                         /* [3:2] */
      __I  unsigned long   prot_wr_attempt_fld:1;                      /* [4] */
      __I  unsigned long   illegal_access_det_fld:1;                   /* [5] */
      __I  unsigned long   :1;                                         /* [6] */
      __I  unsigned long   recv_overflow_fld:1;                        /* [7] */
      __I  unsigned long   tx_fifo_not_full_fld:1;                     /* [8] */
      __I  unsigned long   tx_fifo_full_fld:1;                         /* [9] */
      __I  unsigned long   rx_fifo_not_empty_fld:1;                    /* [10] */
      __I  unsigned long   rx_fifo_full_fld:1;                         /* [11] */
      __I  unsigned long   :1;                                         /* [12] */
      __I  unsigned long   poll_exp_int_fld:1;                         /* [13] */
      __I  unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } irq_status_reg;
  union                                            /* Offset=0x0044 : irq_mask_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   underflow_det_mask_fld:1;                   /* [1] */
      __IO unsigned long   :2;                                         /* [3:2] */
      __IO unsigned long   prot_wr_attempt_mask_fld:1;                 /* [4] */
      __IO unsigned long   illegal_access_det_mask_fld:1;              /* [5] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   recv_overflow_mask_fld:1;                   /* [7] */
      __IO unsigned long   tx_fifo_not_full_mask_fld:1;                /* [8] */
      __IO unsigned long   tx_fifo_full_mask_fld:1;                    /* [9] */
      __IO unsigned long   rx_fifo_not_empty_mask_fld:1;               /* [10] */
      __IO unsigned long   rx_fifo_full_mask_fld:1;                    /* [11] */
      __IO unsigned long   :1;                                         /* [12] */
      __IO unsigned long   poll_exp_int_mask_fld:1;                    /* [13] */
      __IO unsigned long   :18;                                        /* [31:14] */
    } BIT;
  } irq_mask_reg;
  char                     wk_0048[0x0008];
  union                                            /* Offset=0x0050 : lower_wr_prot_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   subsector_fld:32;                           /* [31:0] */
    } BIT;
  } lower_wr_prot_reg;
  union                                            /* Offset=0x0054 : upper_wr_prot_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   subsector_fld:32;                           /* [31:0] */
    } BIT;
  } upper_wr_prot_reg;
  union                                            /* Offset=0x0058 : wr_prot_ctrl_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   inv_fld:1;                                  /* [0] */
      __IO unsigned long   enb_fld:1;                                  /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } wr_prot_ctrl_reg;
  char                     wk_005C[0x0034];
  union                                            /* Offset=0x0090 : flash_cmd_ctrl_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __O  unsigned long   cmd_exec_fld:1;                             /* [0] */
      __I  unsigned long   cmd_exec_status_fld:1;                      /* [1] */
      __IO unsigned long   :5;                                         /* [6:2] */
      __IO unsigned long   num_dummy_bytes_fld:5;                      /* [11:7] */
      __IO unsigned long   num_wr_data_bytes_fld:3;                    /* [14:12] */
      __IO unsigned long   enb_write_data_fld:1;                       /* [15] */
      __IO unsigned long   num_addr_bytes_fld:2;                       /* [17:16] */
      __IO unsigned long   enb_mode_bit_fld:1;                         /* [18] */
      __IO unsigned long   enb_comd_addr_fld:1;                        /* [19] */
      __IO unsigned long   num_rd_data_bytes_fld:3;                    /* [22:20] */
      __IO unsigned long   enb_read_data_fld:1;                        /* [23] */
      __IO unsigned long   cmd_opcode_fld:8;                           /* [31:24] */
    } BIT;
  } flash_cmd_ctrl_reg;
  union                                            /* Offset=0x0094 : flash_cmd_addr_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   addr_fld:32;                                /* [31:0] */
    } BIT;
  } flash_cmd_addr_reg;
  char                     wk_0098[0x0008];
  union                                            /* Offset=0x00A0 : flash_rd_data_lower_reg */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   data_fld:32;                                /* [31:0] */
    } BIT;
  } flash_rd_data_lower_reg;
  union                                            /* Offset=0x00A4 : flash_rd_data_upper_reg */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   data_fld:32;                                /* [31:0] */
    } BIT;
  } flash_rd_data_upper_reg;
  union                                            /* Offset=0x00A8 : flash_wr_data_lower_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   data_fld:32;                                /* [31:0] */
    } BIT;
  } flash_wr_data_lower_reg;
  union                                            /* Offset=0x00AC : flash_wr_data_upper_reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   data_fld:32;                                /* [31:0] */
    } BIT;
  } flash_wr_data_upper_reg;
  union                                            /* Offset=0x00B0 : polling_flash_status_reg */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   device_status_fld:8;                        /* [7:0] */
      __I  unsigned long   device_status_valid_fld:1;                  /* [8] */
      __I  unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } polling_flash_status_reg;
  char                     wk_00B4[0x0048];
  union                                            /* Offset=0x00FC : module_id_reg */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   value_fld:24;                               /* [23:0] */
      __I  unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } module_id_reg;
} QSPI_Type;
#endif  /* End of __QSPI_SFR__DEFINE_HEADER__ */
