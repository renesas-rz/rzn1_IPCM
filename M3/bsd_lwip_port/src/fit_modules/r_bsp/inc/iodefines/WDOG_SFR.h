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
 **       for RZN1 WDOG
 **
 **       revision 0.30 (16.January.2018)
 **
 **********************************************************************************************************************/
#ifndef __WDOG_SFR__DEFINE_HEADER__
#define __WDOG_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : WDOG
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : CTRL_RETRIGGER */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WDRV:12;                                    /* [11:0] */
      __IO unsigned long   PSF:1;                                      /* [12] */
      __IO unsigned long   WDE:1;                                      /* [13] */
      __O  unsigned long   WDSI:2;                                     /* [15:14] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } CTRL_RETRIGGER;
} WDOG_Type;
#endif  /* End of __WDOG_SFR__DEFINE_HEADER__ */
