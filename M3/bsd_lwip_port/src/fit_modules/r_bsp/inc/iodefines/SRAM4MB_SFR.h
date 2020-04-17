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
 **       for RZN1 SRAM4MB
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __SRAM4MB_SFR__DEFINE_HEADER__
#define __SRAM4MB_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : SRAM4MB
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : SR4PCMD */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PROTREL:1;                                  /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } SR4PCMD;
  char                     wk_0004[0x00FC];
  union                                            /* Offset=0x0100 : SR4EDC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ECC_ENABLE:1;                               /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } SR4EDC;
  union                                            /* Offset=0x0104 : SR4EEC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DBE_DIST0:1;                                /* [0] */
      __IO unsigned long   DBE_DIST1:1;                                /* [1] */
      __IO unsigned long   DBE_DIST2:1;                                /* [2] */
      __IO unsigned long   DBE_DIST3:1;                                /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } SR4EEC;
  union                                            /* Offset=0x0108 : SR4DBEST */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   DBE_RAM0:1;                                 /* [0] */
      __I  unsigned long   DBE_RAM1:1;                                 /* [1] */
      __I  unsigned long   DBE_RAM2:1;                                 /* [2] */
      __I  unsigned long   DBE_RAM3:1;                                 /* [3] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } SR4DBEST;
  union                                            /* Offset=0x010C : SR4DBEAD */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   LOCK:1;                                     /* [0] */
      __I  unsigned long   :3;                                         /* [3:1] */
      __I  unsigned long   ADDRESS:18;                                 /* [21:4] */
      __I  unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } SR4DBEAD;
  union                                            /* Offset=0x0110 : SR4DBECNT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ERRCOUNT:4;                                 /* [3:0] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } SR4DBECNT;
} SRAM4MB_Type;
#endif  /* End of __SRAM4MB_SFR__DEFINE_HEADER__ */
