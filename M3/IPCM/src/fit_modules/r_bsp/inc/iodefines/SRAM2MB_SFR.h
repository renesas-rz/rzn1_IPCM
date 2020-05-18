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
 **       for RZN1 SRAM2MB
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __SRAM2MB_SFR__DEFINE_HEADER__
#define __SRAM2MB_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : SRAM2MB
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : RAMPCMD */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PROTREL:1;                                  /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } RAMPCMD;
  char                     wk_0004[0x00FC];
  union                                            /* Offset=0x0100 : RAMEDC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ECC_ENABLE:1;                               /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } RAMEDC;
  union                                            /* Offset=0x0104 : RAMEEC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DBE_DIST0:1;                                /* [0] */
      __IO unsigned long   DBE_DIST1:1;                                /* [1] */
      __IO unsigned long   DBE_DIST2:1;                                /* [2] */
      __IO unsigned long   DBE_DIST3:1;                                /* [3] */
      __IO unsigned long   DBE_DIST4:1;                                /* [4] */
      __IO unsigned long   DBE_DIST5:1;                                /* [5] */
      __IO unsigned long   DBE_DIST6:1;                                /* [6] */
      __IO unsigned long   DBE_DIST7:1;                                /* [7] */
      __IO unsigned long   DBE_DIST8:1;                                /* [8] */
      __IO unsigned long   DBE_DIST9:1;                                /* [9] */
      __IO unsigned long   DBE_DIST10:1;                               /* [10] */
      __IO unsigned long   DBE_DIST11:1;                               /* [11] */
      __IO unsigned long   DBE_DIST12:1;                               /* [12] */
      __IO unsigned long   DBE_DIST13:1;                               /* [13] */
      __IO unsigned long   DBE_DIST14:1;                               /* [14] */
      __IO unsigned long   DBE_DIST15:1;                               /* [15] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RAMEEC;
  union                                            /* Offset=0x0108 : RAMDBEST */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   DBE_RAM0:1;                                 /* [0] */
      __I  unsigned long   DBE_RAM1:1;                                 /* [1] */
      __I  unsigned long   DBE_RAM2:1;                                 /* [2] */
      __I  unsigned long   DBE_RAM3:1;                                 /* [3] */
      __I  unsigned long   DBE_RAM4:1;                                 /* [4] */
      __I  unsigned long   DBE_RAM5:1;                                 /* [5] */
      __I  unsigned long   DBE_RAM6:1;                                 /* [6] */
      __I  unsigned long   DBE_RAM7:1;                                 /* [7] */
      __I  unsigned long   DBE_RAM8:1;                                 /* [8] */
      __I  unsigned long   DBE_RAM9:1;                                 /* [9] */
      __I  unsigned long   DBE_RAM10:1;                                /* [10] */
      __I  unsigned long   DBE_RAM11:1;                                /* [11] */
      __I  unsigned long   DBE_RAM12:1;                                /* [12] */
      __I  unsigned long   DBE_RAM13:1;                                /* [13] */
      __I  unsigned long   DBE_RAM14:1;                                /* [14] */
      __I  unsigned long   DBE_RAM15:1;                                /* [15] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } RAMDBEST;
  union                                            /* Offset=0x010C : RAMDBEAD */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   LOCK:1;                                     /* [0] */
      __I  unsigned long   :1;                                         /* [1] */
      __I  unsigned long   ADDRESS:17;                                 /* [18:2] */
      __I  unsigned long   BANK:2;                                     /* [20:19] */
      __I  unsigned long   :11;                                        /* [31:21] */
    } BIT;
  } RAMDBEAD;
  union                                            /* Offset=0x0110 : RAMDBECNT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ERRCOUNT:4;                                 /* [3:0] */
      __I  unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } RAMDBECNT;
} SRAM2MB_Type;
#endif  /* End of __SRAM2MB_SFR__DEFINE_HEADER__ */
