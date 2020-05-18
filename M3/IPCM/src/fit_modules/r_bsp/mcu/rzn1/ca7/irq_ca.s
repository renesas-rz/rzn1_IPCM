;/*
; * Copyright (c) 2013-2018 Arm Limited. All rights reserved.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; *
; * -----------------------------------------------------------------------------
; * Title:       Cortex-A Exception handlers
; * -----------------------------------------------------------------------------
; */

        PUBLIC _SVC_Handler
        PUBLIC _IRQ_Handler

                NAME     irq_ca.s

MODE_FIQ        EQU      0x11
MODE_IRQ        EQU      0x12
MODE_SVC        EQU      0x13
MODE_ABT        EQU      0x17
MODE_UND        EQU      0x1B

CPSR_BIT_T      EQU      0x20

                PRESERVE8

                SECTION .data:DATA:NOROOT(2)
                EXPORT   IRQ_PendSV
IRQ_PendSV      DCB      0                          ; Pending SVC flag
SVC_Active      DCB      0                          ; SVC handler execution active flag


                SECTION .text:CODE:NOROOT(2)

_IRQ_Handler
                EXPORT  _IRQ_Handler
                IMPORT  IRQ_Handler
                IMPORT  readIntAck
                IMPORT  IRQ_GetHandler
                IMPORT  writeEOI

                SUB     LR, LR, #4                  ; Pre-adjust LR
                SRSFD   SP!, #MODE_SVC              ; Save LR_irq and SPRS_irq on to the SVC stack
                CPS     #MODE_SVC                   ; Change to SVC mode
                PUSH    {R0-R3, R12, LR}            ; Save APCS corruptible registers

                MOV     R3, SP                      ; Move SP into R3
                AND     R3, R3, #4                  ; Get stack adjustment to ensure 8-byte alignment
                SUB     SP, SP, R3                  ; Adjust stack
                PUSH    {R3, R4, R5}                ; Store stack adjustment(R3) and user data(R4)

                BLX     readIntAck                  ; Retrieve interrupt ID into R0
                MOV     R4, R0                      ; Move interrupt ID to R4

                CPSIE   i                           ; Re-enable interrupts
                BLX     IRQ_Handler                 ; Call the interrupt handler in mcu_interrupts.c
                CMP     R0, #0                      ; Check for the error
                BEQ     IRQ_End                     ; If 0, end interrupt and return
                CPSID   i                           ; Disable interrupts

IRQ_End
                MOV     R0, R4                      ; Move interrupt ID to R0
                BLX     writeEOI                    ; Signal end of interrupt

IRQ_Exit
                POP     {R3, R4, R5}                    ; Restore stack adjustment(R3) and user data(R4)
                ADD     SP, SP, R3                  ; Unadjust stack

                POP     {R0-R3, R12, LR}            ; Restore stacked APCS registers
                RFEFD   SP!                         ; Return from IRQ handler



_SVC_Handler
                EXPORT  _SVC_Handler
                IMPORT  IRQ_Disable
                IMPORT  IRQ_Enable

                SRSFD   SP!, #MODE_SVC              ; Store SPSR_svc and LR_svc onto SVC stack
                PUSH    {R12, LR}


SVC_Done
                POP     {R4, R5, R12, LR}
                RFEFD   SP!                         ; Return from exception

                END
