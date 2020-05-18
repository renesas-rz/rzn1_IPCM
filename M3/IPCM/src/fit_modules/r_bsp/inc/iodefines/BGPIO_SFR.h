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
 **       for RZN1 BGPIO1
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __BGPIO_SFR__DEFINE_HEADER__
#define __BGPIO_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : BGPIO
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : rGPIO_swporta_dr */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIO_port_dr:32;                           /* [31:0] */
    } BIT;
  } rGPIO_swporta_dr;
  union                                            /* Offset=0x0004 : rGPIO_swporta_ddr */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIO_port_ddr:32;                          /* [31:0] */
    } BIT;
  } rGPIO_swporta_ddr;
  char                     wk_0008[0x0004];
  union                                            /* Offset=0x000C : rGPIO_swportb_dr */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIO_port_dr:32;                           /* [31:0] */
    } BIT;
  } rGPIO_swportb_dr;
  union                                            /* Offset=0x0010 : rGPIO_swportb_ddr */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIO_port_ddr:32;                          /* [31:0] */
    } BIT;
  } rGPIO_swportb_ddr;
  char                     wk_0014[0x001C];
  union                                            /* Offset=0x0030 : rGPIO_inten */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIO_inten:32;                             /* [31:0] */
    } BIT;
  } rGPIO_inten;
  union                                            /* Offset=0x0034 : rGPIO_intmask */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIO_intmask:32;                           /* [31:0] */
    } BIT;
  } rGPIO_intmask;
  union                                            /* Offset=0x0038 : rGPIO_inttype_level */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIO_inttype_levell:32;                    /* [31:0] */
    } BIT;
  } rGPIO_inttype_level;
  union                                            /* Offset=0x003C : rGPIO_int_polarity */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIO_int_polarity:32;                      /* [31:0] */
    } BIT;
  } rGPIO_int_polarity;
  union                                            /* Offset=0x0040 : rGPIO_intstatus */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bGPIO_intstatus:32;                         /* [31:0] */
    } BIT;
  } rGPIO_intstatus;
  union                                            /* Offset=0x0044 : rGPIO_raw_intstatus */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bGPIO_raw_intstatus:32;                     /* [31:0] */
    } BIT;
  } rGPIO_raw_intstatus;
  char                     wk_0048[0x0004];
  union                                            /* Offset=0x004C : rGPIO_porta_eoi */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   bGPIO_porta_eoi:32;                         /* [31:0] */
    } BIT;
  } rGPIO_porta_eoi;
  union                                            /* Offset=0x0050 : rGPIO_ext_porta */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bGPIO_ext_port:32;                          /* [31:0] */
    } BIT;
  } rGPIO_ext_porta;
  union                                            /* Offset=0x0054 : rGPIO_ext_portb */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bGPIO_ext_port:32;                          /* [31:0] */
    } BIT;
  } rGPIO_ext_portb;
  char                     wk_0058[0x0008];
  union                                            /* Offset=0x0060 : rGPIO_ls_sync */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bGPIO_ls_sync:1;                            /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rGPIO_ls_sync;
} BGPIO_Type;
#endif  /* End of __BGPIO_SFR__DEFINE_HEADER__ */
