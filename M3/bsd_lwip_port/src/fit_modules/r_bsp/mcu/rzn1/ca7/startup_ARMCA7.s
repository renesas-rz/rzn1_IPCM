/******************************************************************************
 * @file     startup_ARMCA7.s
 * @brief    CMSIS Device System Source File for ARM Cortex-A7 Device Series
 * @version  V1.00
 * @date     01 Nov 2017
 *
 * @note
 *
 ******************************************************************************/
/*
 * Copyright (c) 2009-2017 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

  MODULE  ?startup_ARMCA7

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
  PUBLIC  Reset_Handler

        SECTION IRQ_STACK:DATA:NOROOT(3)
        SECTION FIQ_STACK:DATA:NOROOT(3)
        SECTION SVC_STACK:DATA:NOROOT(3)
        SECTION SMC_STACK:DATA:NOROOT(3)
        SECTION ABT_STACK:DATA:NOROOT(3)
        SECTION UND_STACK:DATA:NOROOT(3)
        SECTION CSTACK:DATA:NOROOT(3)
        SECTION MMU:DATA:NOROOT(3)
/*----------------------------------------------------------------------------
  Exception / Interrupt Vector Table
 *----------------------------------------------------------------------------*/
        SECTION .intvec:CODE:NOROOT(5)

        PUBLIC  __iar_program_start
        EXTERN  Undefined_Handler
        EXTERN  _SVC_Handler
        EXTERN  _SMC_Handler
        EXTERN  Prefetch_Handler
        EXTERN  Abort_Handler
        EXTERN  _IRQ_Handler
        EXTERN  FIQ_Handler

        DATA

  PUBLIC  Vectors

Vectors:
        LDR     PC,Reset_Addr           ; Reset
        LDR     PC,Undefined_Addr       ; Undefined instructions
        LDR     PC,SVC_Addr             ; Super Visor Call (SVC)
        LDR     PC,Prefetch_Addr        ; Prefetch abort
        LDR     PC,Abort_Addr           ; Data abort
        DCD     0                       ; RESERVED
        LDR     PC,IRQ_Addr             ; IRQ
        LDR     PC,FIQ_Addr             ; FIQ

        DATA

Reset_Addr:     DCD   __iar_program_start
Undefined_Addr: DCD   Undefined_Handler
SVC_Addr:       DCD   _SVC_Handler
Prefetch_Addr:  DCD   Prefetch_Handler
Abort_Addr:     DCD   Abort_Handler
IRQ_Addr:       DCD   _IRQ_Handler
FIQ_Addr:       DCD   FIQ_Handler

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
  *----------------------------------------------------------------------------*/
        SECTION .text:CODE:NOROOT(2)

        REQUIRE Vectors
        EXTWEAK __iar_init_core
        EXTWEAK __iar_init_vfp

        EXTERN  joinSMP
        EXTERN  disableHighVecs
        EXTERN  enableVGIC
        EXTERN  enableVGICPhysicalCPUInterface
        EXTERN  set_mmu
        EXTERN  SystemInit

;; Reset starts here...
__iar_program_start:

Reset_Handler:

i        CPSID   if
  
        ; Set NoC clk. to 125MHz
        LDR     r1, =0x4000C0E0 
readNoCdiv:
        LDR     r2, [r1]
        SUBS    r2, r2, #0
        BMI     readNoCdiv
        LDR     r2, =0x80000002
        STR     r2,[r1]
waitNoCclk:
        LDR     r2, [r1]
        SUBS    r2, r2, #0
        BMI     waitNoCclk
  
        ; Set CPU clk. to 500MHz
        LDR     r1, =0x4000C0E4 
readCPUdiv:
        LDR     r2, [r1]
        SUBS    r2, r2, #0
        BMI     readCPUdiv
        LDR     r2, =0x80000001
        STR     r2,[r1]   
waitCPUclk:
        LDR     r2, [r1]
        SUBS    r2, r2, #0
        BMI     waitCPUclk
      
        ;; Processor implements: 
        ;; two levels of shareability (inner and outer).
        ;; hardware coherency support.
        ;;
        ;; Processor supports:
        ;; VMSAv7, with support for remapping and the Access flag.
        ;; Privileged Execute Never (PXN) within the first level descriptors.
        ;; 64-bit address translation descriptors.


        ;; Put any cores other than 0 to sleep
        MRC     p15, 0, R0, c0, c0, 5
        ANDS    R0, R0, #3
goToSleep:
        WFINE
        BNE     goToSleep

        ;; Reset SCTLR Settings
        MRC     p15, 0, R0, c1, c0, 0 ; Read CP15 System Control register
        BIC     R0, R0, #(0x1 << 12)  ; Clear I bit 12 to disable I Cache
        BIC     R0, R0, #(0x1 <<  2)  ; Clear C bit  2 to disable D Cache
        BIC     R0, R0, #0x1          ; Clear M bit  0 to disable MMU
        BIC     R0, R0, #(0x1 << 11)  ; Clear Z bit 11 to disable branch prediction
        BIC     R0, R0, #(0x1 << 13)  ; Clear V bit 13 to disable hivecs
        MCR     p15, 0, R0, c1, c0, 0 ; Write value back to CP15 System Control register
        ISB

        ;; Configure ACTLR
        MRC     p15, 0, r0, c1, c0, 1 ; Read CP15 Auxiliary Control Register
        ;; NB Enable L2 prefetch hint (UNK/WI since r4p1) is only on cortex A9, on A7 this is RESERVED (RAZ/WI)!!
        
        ;; SMP
        ;; Enables coherent requests to the processor. 
        ;; You must ensure this bit is set to 1 before the caches and MMU are enabled, 
        ;; or any cache and TLB maintenance operations are performed. The only time 
        ;; this bit is set to 0 is during a processor power-down sequence.
        ORR     r0, r0, #(1 << 6)
        MCR     p15, 0, r0, c1, c0, 1 ; Write CP15 Auxiliary Control Register

        ;; Set Vector Base Address Register (VBAR) to point to this application's vector table
        LDR    R0, =Vectors
        MCR    p15, 0, R0, c12, c0, 0
        
        ; Hint: MVBAR nust be set during boot for security software (TrustZone/secureBoot)!

        ;; Setup Stack for each exception mode
        CPS    #0x11
        LDR    SP, =SFE(FIQ_STACK)
        CPS    #0x12
        LDR    SP, =SFE(IRQ_STACK)
        CPS    #0x13
        LDR    SP, =SFE(SVC_STACK)
        CPS    #0x17
        LDR    SP, =SFE(ABT_STACK)
        CPS    #0x1B
        LDR    SP, =SFE(UND_STACK)
        CPS    #0x1F
        LDR    SP, =SFE(CSTACK)

        ;; Turn on core features assumed to be enabled.
        BL      __iar_init_core

        ;; Initialize VFP (if needed).
        BL      __iar_init_vfp

        MRC     p15, 0, r0, c3, c0, 0   ; Read Domain Access Control Register
; AP check should be decided by custonmer
; LDR     r0, =0x55555555         ; Initialize every domain entry to b01 (client)
        LDR     r0, =0xffffffff         ; No AP check (ignore access permissions)
        MCR     p15, 0, r0, c3, c0, 0   ; Write Domain Access Control Register

; performance monitor is for Lenze         
        ;; Enable performance monitor.
        MRC p15, 0, r0, c9, c12, 0 ; Read PMCR into Rt
        orr r0,r0,#1
        MCR p15, 0, r0, c9, c12, 0 ; Write Rt to PMCR

        MRC p15, 0, r0, c9, c12, 1 ; Read PMCNTENSET into Rt
        mov r0,#(1<<31)
        MCR p15, 0, r0, c9, c12, 1 ; Write Rt to PMCNTENSET

        mov r0,#1
        MCR p15, 0, r0, c9, c14, 0   
        
        ;; enable ICache, branch prediction and alignment check
        MRC     p15, #0, r0, c1, c0
        MOVW    r1,#4898
        ORR     r0, r1, r0
        MCR     p15, 0, r0, c1, c0  
        
        ;; Page table setup.
        BL      set_mmu
        
        ;, supervisor mode
        MOV     r0, #-1
        MCR     p15, 0, r0, c3, c0              
        
        ;; MMU start
        MRC     p15, 0, r0, c1, c0
        ORRS    r0, r0, #1
        MCR     p15, 0, r0, c1, c0
        
        ISB     sy ; Purge pipeline
        
        ;; enable DCache
        MRC     p15, 0, r0, c1, c0
        ORRS    r0, r0, #4       
        MCR     p15, 0, r0, c1, c0

        ;; Initialise the GIC
        BL      enableVGIC
        BL      enableVGICPhysicalCPUInterface

        CPSIE   if
        BL     SystemInit

  END
