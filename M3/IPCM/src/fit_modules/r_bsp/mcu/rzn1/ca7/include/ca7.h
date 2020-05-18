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
 * $Revision: 1301 $
 * $Date: 2019-02-25 14:29:43 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  ca7.h
 * Description  :  CA7 Definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef _CA7_H
#define _CA7_H

#include <stdint.h>

/* ---------------- primitive function begin ---------------- */
#define __stringify_1(x...)     #x
#define __stringify(x...)       __stringify_1(x)

#define __CP32(r, coproc, opc1, crn, crm, opc2) \
          p##coproc, opc1, r,c##crn, c##crm, opc2

#define CP32(r, name...) __CP32(r, name)
#define LOAD_CP32(r, name...)  "mrc " __stringify(CP32(%r, name)) ";"
#define STORE_CP32(r, name...) "mcr " __stringify(CP32(%r, name)) ";"
/* ---------------- primitive function end ---------------- */

/* ---------------------------------------- */
/* CP15 CR0: CPUID and Cache Type Registers */
/* ---------------------------------------- */
#define MIDR            15,0,0,0,0   /* Main ID Register */
#define CTR             15,0,0,0,1   /* Cache Type Register */
// ... (TCMTR TLBTR REVIDR) ...
#define MPIDR           15,0,0,0,5   /* Multiprocessor Affinity Register */
#define CLIDR           15,1,0,0,1   /* Cache Level ID Register */
#define CCSIDR          15,1,0,0,0   /* Cache Size ID Registers */
#define CSSELR          15,2,0,0,0   /* Cache Size Selection Register */

/* ---------------------------------- */
/* CP15 CR1: System Control Registers */
/* ---------------------------------- */
#define SCTLR           15,0,1,0,0   /* System Control Register */
#define ACTLR           15,0,1,0,1   /* Auxiliary Control Register */
#define CPACR           15,0,1,0,2   /* Coprocessor Access Control Register */
#define SCR             15,0,1,1,0   /* Secure Configuration Register */
// (SDER)
#define NSACR           15,0,1,1,2   /* Non-Secure Access Control Register */
#define HSCTLR          15,4,1,0,0   /* Hyp. System Control Register */
// (HACTLR)
#define HCR             15,4,1,1,0   /* Hyp. Configuration Register */
#define HDCR            15,4,1,1,1   /* Hyp. Debug Configuration Register */
#define HCPTR           15,4,1,1,2   /* Hyp. Coprocessor Trap Register */
#define HSTR            15,4,1,1,3   /* Hyp. System Trap Register */
// (HACK)

/* -------------------------------------------------- */
/* CP15 CR7: Cache and address translation operations */
/* -------------------------------------------------- */
#define DCCMVAC         15,0,7,10,1  /* Clean data or unified cache line by MVA to PoC */
#define DCCMVAU         15,0,7,11,1  /* Clean data cache line by MVA to PoU */
#define DCCIMVAC        15,0,7,14,1  /* Data cache clean and invalidate by MVA */

/* ----------- */
/* CP15 CR12:  */
/* ----------- */
#define VBAR            15,0,12,0,0  /* Vector Base Address Register */
#define MVBAR           15,0,12,0,1  /* Monitor Vector Base Address Register */
#define ISR             15,0,12,1,0  /* Interrupt Status Register */
#define HVBAR           15,4,12,0,0  /* Hyp. Vector Base Address Register */

/* ----------- */
/* CP15 CR14:  */
/* ----------- */
//#define CNTPCT          15,0,14       /* Time counter value */
#define CNTFRQ          15,0,14,0,0  /* Time counter frequency */
#define CNTKCTL         15,0,14,1,0  /* Time counter kernel control */
#define CNTP_TVAL       15,0,14,2,0  /* Physical Timer value */
#define CNTP_CTL        15,0,14,2,1  /* Physical Timer control register */
//#define CNTVCT          15,1,14       /* Time counter value + offset */
//#define CNTP_CVAL       15,2,14       /* Physical Timer comparator */
//#define CNTV_CVAL       15,3,14       /* Virt. Timer comparator */
//#define CNTVOFF         15,4,14       /* Time counter offset */
#define CNTHCTL         15,4,14,1,0  /* Time counter hyp. control */
#define CNTHP_TVAL      15,4,14,2,0  /* Hyp. Timer value */
#define CNTHP_CTL       15,4,14,2,1  /* Hyp. Timer control register */
#define CNTV_TVAL       15,0,14,3,0  /* Virt. Timer value */
#define CNTV_CTL        15,0,14,3,1  /* Virt. TImer control register */
//#define CNTHP_CVAL      15,6,14       /* Hyp. Timer comparator */

/* ----------- */
/* CP15 CR15:  */
/* ----------- */
#define CBAR            15,4,15,0,0  /* Configuration Base Address Register */


/* ---------------- utility function ---------------- */

#ifdef __ICCARM__
  #include <intrinsics.h>
  #define READ_CP32(name...) __MRC(name)
#else
  #define READ_CP32(name...) ({                     \
    register uint32_t _r;                         \
    __asm volatile(LOAD_CP32(0, name) : "=r" (_r)); \
    _r; })
#endif

#define WRITE_CP32(v, name...) do {               \
  register uint32_t _r = (v);                      \
  __asm volatile(STORE_CP32(0, name) : : "r" (_r));  \
 } while (0)

#define flush_dcache_one(va)   WRITE_CP32((uint32_t) va, DCCMVAC)
#define invalid_dcache_one(va) WRITE_CP32((uint32_t) va, DCCIMVAC)

#define smc()  __asm( "smc #0" )
#define dmb()  __asm( "dmb" )
#define dsb()  __asm( "dsb" )
#define isb()  __asm( "isb" )

#endif // defined( _CA7_H )
