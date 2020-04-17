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
 **       for RZN1 RINACS
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __RINACS_SFR__DEFINE_HEADER__
#define __RINACS_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : RINACS
 **********************************************************************************************************************/
typedef struct
{
  char                     wk_0000[0x0004];
  union                                            /* Offset=0x0004 : IDCODE */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   IDCODE:32;                                  /* [31:0] */
    } BIT;
  } IDCODE;
  char                     wk_0008[0x0008];
  union                                            /* Offset=0x0010 : SCRATCH0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SCRATCH0:32;                                /* [31:0] */
    } BIT;
  } SCRATCH0;
  union                                            /* Offset=0x0014 : SCRATCH1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SCRATCH1:32;                                /* [31:0] */
    } BIT;
  } SCRATCH1;
  union                                            /* Offset=0x0018 : SCRATCH2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SCRATCH2:32;                                /* [31:0] */
    } BIT;
  } SCRATCH2;
  union                                            /* Offset=0x001C : SCRATCH3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SCRATCH3:32;                                /* [31:0] */
    } BIT;
  } SCRATCH3;
  char                     wk_0020[0x00E0];
  union                                            /* Offset=0x0100 : RINSPCMD */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RINSPCMD:1;                                 /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } RINSPCMD;
  char                     wk_0104[0x000C];
  union                                            /* Offset=0x0110 : RTOSRST */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   OSRST:1;                                    /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } RTOSRST;
} RINACS_Type;
#endif  /* End of __RINACS_SFR__DEFINE_HEADER__ */
