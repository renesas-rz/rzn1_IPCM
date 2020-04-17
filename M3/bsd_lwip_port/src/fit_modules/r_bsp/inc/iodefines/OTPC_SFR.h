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
 **       for RZN1 OTPC
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __OTPC_SFR__DEFINE_HEADER__
#define __OTPC_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : OTPC
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : OTPWCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   OTPW_ProdModeDis:1;                         /* [0] */
      __IO unsigned long   OTPW_ProdModeDisLock:1;                     /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } OTPWCTRL;
  union                                            /* Offset=0x0004 : OTPWSTAT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPW_SecureMode:1;                          /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } OTPWSTAT;
  union                                            /* Offset=0x0008 : OTPWCHIPID0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPW_CHIPID0:32;                            /* [31:0] */
    } BIT;
  } OTPWCHIPID0;
  union                                            /* Offset=0x000C : OTPWCHIPID1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPW_CHIPID1:32;                            /* [31:0] */
    } BIT;
  } OTPWCHIPID1;
  union                                            /* Offset=0x0010 : OTPWDAT0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPW_SecureMode:1;                          /* [0] */
      __I  unsigned long   :2;                                         /* [2:1] */
      __I  unsigned long   OTPW_SecureBoot:1;                          /* [3] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } OTPWDAT0;
  union                                            /* Offset=0x0014 : OTPWDAT1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPWDAT1:32;                                /* [31:0] */
    } BIT;
  } OTPWDAT1;
  union                                            /* Offset=0x0018 : OTPWDAT2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPWDAT2:32;                                /* [31:0] */
    } BIT;
  } OTPWDAT2;
  union                                            /* Offset=0x001C : OTPWDAT3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPWDAT3:32;                                /* [31:0] */
    } BIT;
  } OTPWDAT3;
  union                                            /* Offset=0x0020 : OTPWDAT4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPWDAT4:32;                                /* [31:0] */
    } BIT;
  } OTPWDAT4;
  union                                            /* Offset=0x0024 : OTPWDAT5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPWDAT5:32;                                /* [31:0] */
    } BIT;
  } OTPWDAT5;
  union                                            /* Offset=0x0028 : OTPWDAT6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPWDAT6:32;                                /* [31:0] */
    } BIT;
  } OTPWDAT6;
  union                                            /* Offset=0x002C : OTPWDAT7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPWDAT7:32;                                /* [31:0] */
    } BIT;
  } OTPWDAT7;
  union                                            /* Offset=0x0030 : OTPWDAT8 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   OTPWDAT8:32;                                /* [31:0] */
    } BIT;
  } OTPWDAT8;
} OTPC_Type;
#endif  /* End of __OTPC_SFR__DEFINE_HEADER__ */
