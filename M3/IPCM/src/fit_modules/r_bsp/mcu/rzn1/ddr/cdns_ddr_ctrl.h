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
 * $Revision: 1322 $
 * $Date: 2019-03-02 01:34:20 +0000 (Sat, 02 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  cdns_ddr_ctrl.h
 * Description  :  DDR Controller
 *                 SPDX-License-Identifier: BSD-2-Clause
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __CDNS_DDR_CTRL_H_
#define __CDNS_DDR_CTRL_H_

#include <stdint.h>
#include "common/common_api.h"

/* type definition */
#define u64                             uint64_t
#define u32                             uint32_t
#define u16                             uint16_t
#define u8                              uint8_t

/* size definition */
#define SZ_1                            0x00000001
#define SZ_2                            0x00000002
#define SZ_4                            0x00000004
#define SZ_8                            0x00000008
#define SZ_16                           0x00000010
#define SZ_32                           0x00000020
#define SZ_64                           0x00000040
#define SZ_128                          0x00000080
#define SZ_256                          0x00000100
#define SZ_512                          0x00000200

#define SZ_1K                           0x00000400
#define SZ_2K                           0x00000800
#define SZ_4K                           0x00001000
#define SZ_8K                           0x00002000
#define SZ_16K                          0x00004000
#define SZ_32K                          0x00008000
#define SZ_64K                          0x00010000
#define SZ_128K                         0x00020000
#define SZ_256K                         0x00040000
#define SZ_512K                         0x00080000

#define SZ_1M                           0x00100000
#define SZ_2M                           0x00200000
#define SZ_4M                           0x00400000
#define SZ_8M                           0x00800000
#define SZ_16M                          0x01000000
#define SZ_32M                          0x02000000
#define SZ_64M                          0x04000000
#define SZ_128M                         0x08000000
#define SZ_256M                         0x10000000
#define SZ_512M                         0x20000000

#define SZ_1G                           0x40000000
#define SZ_2G                           0x80000000

/* io definition */
#define writeb(v,c)                     CPU_WRB(c,v)
#define writew(v,c)                     CPU_WRH(c,v)
#define writel(v,c)                     CPU_WRW(c,v)
#define readb(a)                        CPU_RDB(a)
#define readw(a)                        CPU_RDH(a)
#define readl(a)                        CPU_RDW(a)

/* BIT operation */
#define BIT(x)                          (1 << (x))

/**
 * Initialise the DDR Controller, but doesn't start it.
 *
 * It sets up the controller so that all 4 AXI slave ports allow access to all
 * of the DDR with the same settings. This means that:
 *  - Full access permisions.
 *  - All read/write priorities are set to 2.
 *  - Bandwidth is set to 50%, overflow is allowed, i.e. it's a soft limit.
 *
 * @ddr_ctrl_base  Physical address of the DDR Controller.
 * @async          use 1. DDR clock is asynchronous only.
 * @reg0           Pointer to array of 32-bit values to be written to registers
 *                 0 to 87.
 * @reg350         Pointer to array of 32-bit values to be written to registers
 *                 350 to 374.
 * @ddr_start_addr Physical address of the start of DDR.
 * @ddr_size       Size of the DDR in bytes. The controller will set the port
 *                 protection range to match this size.
 */
void cdns_ddr_ctrl_init(void *ddr_ctrl_base, int async, const u32 *reg0,
        const u32 *reg350,
        u32 ddr_start_addr, u32 ddr_size);

/**
 * Start the DDR Controller.
 *
 * @ddr_ctrl_base  Physical address of the DDR Controller.
 */
void cdns_ddr_ctrl_start(void *ddr_ctrl_base);

/**
 * Set the priority for read and write operations for a specific AXI slave port.
 *
 * @base      Physical address of the DDR Controller.
 * @port      Port number. Range is 0 to 3.
 * @read_pri  Priority for reads.  Range is 0 to 3, where 0 is highest priority.
 * @write_pri Priority for writes. Range is 0 to 3, where 0 is highest priority.
 */
void cdns_ddr_set_port_rw_priority(void *base, int port,
u8 read_pri, u8 write_pri, u8 fifo_type);

/**
 * Specify address range for a protection entry, for a specific AXI slave port.
 *
 * @base       Physical address of the DDR Controller.
 * @port       Port number. Range is 0 to 3.
 * @entry      The protection entry. Range is 0 to 15.
 * @start_addr Physical of the address range, must be aligned to 16KB.
 * @size       Size of the address range, must be multiple of 16KB.
 */
void cdns_ddr_enable_port_addr_range_x(void *base, int port, int entry,
u32 addr_start, u32 size);

/**
 * Specify protection entry details, for a specific AXI slave port.
 *
 * See the hardware manual for details of the range check bits.
 *
 * @base       Physical address of the DDR Controller.
 * @port       Port number. Range is 0 to 3.
 * @entry      The protection entry. Range is 0 to 15.
 */
void cdns_ddr_enable_port_prot_x(void *base, int port, int entry,
u8 range_protection_bits,
u16 range_RID_check_bits,
u16 range_WID_check_bits,
u8 range_RID_check_bits_ID_lookup,
u8 range_WID_check_bits_ID_lookup);

void set_port_bandwidth(void *base, int port,
u8 max_percent, u8 overflow_ok);

/* Standard JEDEC registers */
#define MODE_REGISTER_MASK        (3 << 14)
#define MODE_REGISTER_MR0        (0 << 14)
#define MODE_REGISTER_MR1        (1 << 14)
#define MODE_REGISTER_MR2        (2 << 14)
#define MODE_REGISTER_MR3        (3 << 14)
#define MR1_DRIVE_STRENGTH_MASK        ((1 << 5) | (1 << 1))
#define MR1_DRIVE_STRENGTH_34_OHMS    ((0 << 5) | (1 << 1))
#define MR1_DRIVE_STRENGTH_40_OHMS    ((0 << 5) | (0 << 1))
#define MR1_ODT_IMPEDANCE_MASK        ((1 << 9) | (1 << 6) | (1 << 2))
#define MR1_ODT_IMPEDANCE_60_OHMS    ((0 << 9) | (0 << 6) | (1 << 2))
#define MR1_ODT_IMPEDANCE_120_OHMS    ((0 << 9) | (1 << 6) | (0 << 2))
#define MR1_ODT_IMPEDANCE_40_OHMS    ((0 << 9) | (1 << 6) | (1 << 2))
#define MR1_ODT_IMPEDANCE_20_OHMS    ((1 << 9) | (0 << 6) | (0 << 2))
#define MR1_ODT_IMPEDANCE_30_OHMS    ((1 << 9) | (0 << 6) | (1 << 2))
#define MR2_DYNAMIC_ODT_MASK        (3 << 9)
#define MR2_DYNAMIC_ODT_OFF        (0 << 9)
#define MR2_SELF_REFRESH_TEMP_MASK    (1 << 7)
#define MR2_SELF_REFRESH_TEMP_EXT    (1 << 7)

/**
 * Set certain fields of the JEDEC MR1 register.
 */
void cdns_ddr_set_mr1(void *base, int cs, u16 odt_impedance,
        u16 drive_strength);

/**
 * Set certain fields of the JEDEC MR2 register.
 */
void cdns_ddr_set_mr2(void *base, int cs, u16 dynamic_odt,
        u16 self_refresh_temp);

/**
 * Set ODT map of the DDR Controller.
 */
void cdns_ddr_set_odt_map(void *base, int cs, u16 odt_map);

/**
 * Set ODT settings in the DDR Controller.
 */
void cdns_ddr_set_odt_times(void *base, u8 TODTL_2CMD, u8 TODTH_WR, u8 TODTH_RD,
u8 WR_TO_ODTH, u8 RD_TO_ODTH);

void cdns_ddr_set_same_cs_delays(void *base, u8 r2r, u8 r2w, u8 w2r, u8 w2w);
void cdns_ddr_set_diff_cs_delays(void *base, u8 r2r, u8 r2w, u8 w2r, u8 w2w);

#endif // __CDNS_DDR_CTRL_H_
