  module ?v7

  PUBLIC enableInterrupts
  PUBLIC disableInterrupts
  PUBLIC joinSMP
  PUBLIC disableHighVecs

  SECTION .text:CODE:NOROOT(2)

        ARM

;;------------------------------------------------------------
;; Interrupt enable/disable
;;------------------------------------------------------------

  ;; void enableInterrupts(void);
enableInterrupts:

  CPSIE   i
  BX      lr


  ;; void disableInterrupts(void);
disableInterrupts:

  CPSID   i
  BX      lr


;;==================================================================
;; join SMP
;;==================================================================
  ;; void joinSMP(void);
  ;; Sets the ACTRL.SMP bit

joinSMP:

  ;; SMP status is controlled by bit 6 of the CP15 Aux Ctrl Reg

  MRC     p15, 0, r0, c1, c0, 1   ;; Read ACTLR
  MOV     r1, r0
  ORR     r0, r0, #0x040          ;; Set bit 6
  CMP     r0, r1
  MCRNE   p15, 0, r0, c1, c0, 1   ;; Write ACTLR

  BX      lr


;;==================================================================
;; disable High Vector
;;==================================================================

disableHighVecs:

  ;; void disable_highvecs(void);
  MRC     p15, 0, r0, c1, c0, 0 ;; Read Control Register
  BIC     r0, r0, #(1 << 13)    ;; Clear the V bit (bit 13)
  MCR     p15, 0, r0, c1, c0, 0 ;; Write Control Register
  BX      lr

        END

