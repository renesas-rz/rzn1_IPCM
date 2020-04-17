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
 **       for RZN1 ETHACS
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __ETHACS_SFR__DEFINE_HEADER__
#define __ETHACS_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : ETHACS
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : PRCMD */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRCMD:1;                                    /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } PRCMD;
  union                                            /* Offset=0x0004 : ESIDCODE */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ES_IDCODE:32;                               /* [31:0] */
    } BIT;
  } ESIDCODE;
  union                                            /* Offset=0x0008 : MODCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SW_MODE:5;                                  /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } MODCTRL;
  union                                            /* Offset=0x000C : PTPMCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PTP_MODE:4;                                 /* [3:0] */
      __IO unsigned long   RGMII_CLKSEL:1;                             /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } PTPMCTRL;
  char                     wk_0010[0x0004];
  union                                            /* Offset=0x0014 : PHYLNK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SWLNK:4;                                    /* [3:0] */
      __IO unsigned long   CATLNK:3;                                   /* [6:4] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   S3LNK:2;                                    /* [9:8] */
      __IO unsigned long   :22;                                        /* [31:10] */
    } BIT;
  } PHYLNK;
  char                     wk_0018[0x0008];
  union                                            /* Offset=0x0020 : PTCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TRG_SEL:3;                                  /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } PTCTRL;
  union                                            /* Offset=0x0024 : DMACTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DREQ_EN:7;                                  /* [6:0] */
      __IO unsigned long   DREQ_SEL:1;                                 /* [7] */
      __I  unsigned long   DREQ_BSY:7;                                 /* [14:8] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   DREQ_ERR:7;                                 /* [22:16] */
      __IO unsigned long   :1;                                         /* [23] */
      __IO unsigned long   DREQ_WCNT:8;                                /* [31:24] */
    } BIT;
  } DMACTRL;
  char                     wk_0028[0x00D8];
  union                                            /* Offset=0x0100 : CONVCTRL1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CONV_MODE:5;                                /* [4:0] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   FULLD:1;                                    /* [8] */
      __IO unsigned long   RMII_RX_ER_EN:1;                            /* [9] */
      __IO unsigned long   RMII_CRS_MODE:1;                            /* [10] */
      __IO unsigned long   :1;                                         /* [11] */
      __I  unsigned long   RGMII_LINK:1;                               /* [12] */
      __I  unsigned long   RGMII_DUPLEX:1;                             /* [13] */
      __I  unsigned long   RGMII_SPEED:2;                              /* [15:14] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __I  unsigned long   RGMII_TX_TYPE:2;                            /* [25:24] */
      __I  unsigned long   RGMII_DLY_TYPE:2;                           /* [27:26] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } CONVCTRL1;
  union                                            /* Offset=0x0104 : CONVCTRL2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CONV_MODE:5;                                /* [4:0] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   FULLD:1;                                    /* [8] */
      __IO unsigned long   RMII_RX_ER_EN:1;                            /* [9] */
      __IO unsigned long   RMII_CRS_MODE:1;                            /* [10] */
      __IO unsigned long   :1;                                         /* [11] */
      __I  unsigned long   RGMII_LINK:1;                               /* [12] */
      __I  unsigned long   RGMII_DUPLEX:1;                             /* [13] */
      __I  unsigned long   RGMII_SPEED:2;                              /* [15:14] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __I  unsigned long   RGMII_TX_TYPE:2;                            /* [25:24] */
      __I  unsigned long   RGMII_DLY_TYPE:2;                           /* [27:26] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } CONVCTRL2;
  union                                            /* Offset=0x0108 : CONVCTRL3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CONV_MODE:5;                                /* [4:0] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   FULLD:1;                                    /* [8] */
      __IO unsigned long   RMII_RX_ER_EN:1;                            /* [9] */
      __IO unsigned long   RMII_CRS_MODE:1;                            /* [10] */
      __IO unsigned long   :1;                                         /* [11] */
      __I  unsigned long   RGMII_LINK:1;                               /* [12] */
      __I  unsigned long   RGMII_DUPLEX:1;                             /* [13] */
      __I  unsigned long   RGMII_SPEED:2;                              /* [15:14] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __I  unsigned long   RGMII_TX_TYPE:2;                            /* [25:24] */
      __I  unsigned long   RGMII_DLY_TYPE:2;                           /* [27:26] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } CONVCTRL3;
  union                                            /* Offset=0x010C : CONVCTRL4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CONV_MODE:5;                                /* [4:0] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   FULLD:1;                                    /* [8] */
      __IO unsigned long   RMII_RX_ER_EN:1;                            /* [9] */
      __IO unsigned long   RMII_CRS_MODE:1;                            /* [10] */
      __IO unsigned long   :1;                                         /* [11] */
      __I  unsigned long   RGMII_LINK:1;                               /* [12] */
      __I  unsigned long   RGMII_DUPLEX:1;                             /* [13] */
      __I  unsigned long   RGMII_SPEED:2;                              /* [15:14] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __I  unsigned long   RGMII_TX_TYPE:2;                            /* [25:24] */
      __I  unsigned long   RGMII_DLY_TYPE:2;                           /* [27:26] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } CONVCTRL4;
  union                                            /* Offset=0x0110 : CONVCTRL5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CONV_MODE:5;                                /* [4:0] */
      __IO unsigned long   :3;                                         /* [7:5] */
      __IO unsigned long   FULLD:1;                                    /* [8] */
      __IO unsigned long   RMII_RX_ER_EN:1;                            /* [9] */
      __IO unsigned long   RMII_CRS_MODE:1;                            /* [10] */
      __IO unsigned long   :1;                                         /* [11] */
      __I  unsigned long   RGMII_LINK:1;                               /* [12] */
      __I  unsigned long   RGMII_DUPLEX:1;                             /* [13] */
      __I  unsigned long   RGMII_SPEED:2;                              /* [15:14] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __I  unsigned long   RGMII_TX_TYPE:2;                            /* [25:24] */
      __I  unsigned long   RGMII_DLY_TYPE:2;                           /* [27:26] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } CONVCTRL5;
  union                                            /* Offset=0x0114 : CONVRST */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PHYIF_RSTn:5;                               /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } CONVRST;
  char                     wk_0118[0x00E8];
  union                                            /* Offset=0x0200 : ECATOFFADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   OADD:5;                                     /* [4:0] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } ECATOFFADR;
  union                                            /* Offset=0x0204 : ECATOPMOD */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   I2CSIZE:1;                                  /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } ECATOPMOD;
  union                                            /* Offset=0x0208 : ECATDBGC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXSFT0:2;                                   /* [1:0] */
      __IO unsigned long   TXSFT1:2;                                   /* [3:2] */
      __IO unsigned long   TXSFT2:2;                                   /* [5:4] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } ECATDBGC;
  char                     wk_020C[0x0074];
  union                                            /* Offset=0x0280 : SCINTCON */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SC_CON_SEL:2;                               /* [1:0] */
      __IO unsigned long   :2;                                         /* [3:2] */
      __IO unsigned long   SC_DIV_SEL:2;                               /* [5:4] */
      __IO unsigned long   :26;                                        /* [31:6] */
    } BIT;
  } SCINTCON;
  char                     wk_0284[0x0080];
  union                                            /* Offset=0x0304 : SWCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SET10:4;                                    /* [3:0] */
      __IO unsigned long   SET1000:4;                                  /* [7:4] */
      __IO unsigned long   :8;                                         /* [15:8] */
      __IO unsigned long   STRAP_SX_ENB:1;                             /* [16] */
      __IO unsigned long   STRAP_HUB_ENB:1;                            /* [17] */
      __IO unsigned long   :14;                                        /* [31:18] */
    } BIT;
  } SWCTRL;
  union                                            /* Offset=0x0308 : SWDUPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PHY_DUPLEX:4;                               /* [3:0] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } SWDUPC;
  char                     wk_030C[0x01F4];
  union                                            /* Offset=0x0500 : RMTAGCTRL */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   MGMT_ENB:1;                                 /* [0] */
      __IO unsigned long   :15;                                        /* [15:1] */
      __IO unsigned long   MGMT_TAG:16;                                /* [31:16] */
    } BIT;
  } RMTAGCTRL;
  char                     wk_0504[0x00FC];
  union                                            /* Offset=0x0600 : HSRMOD */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   HSR_SEL:1;                                  /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } HSRMOD;
} ETHACS_Type;
#endif  /* End of __ETHACS_SFR__DEFINE_HEADER__ */
