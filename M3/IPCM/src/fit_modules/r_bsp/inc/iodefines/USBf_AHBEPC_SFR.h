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
 * $Revision: 1297 $
 * $Date: 2019-02-22 17:18:43 +0000 (Fri, 22 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  USBf_AHBEPC_SFR.h
 * Description  :  Definition of Peripheral registers  for RZN1 USBf_AHBEPC
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __USBf_AHBEPC_SFR__DEFINE_HEADER__
#define __USBf_AHBEPC_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : USBf_AHBEPC
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : AHBSCTR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WAIT_MODE:1;                                /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } AHBSCTR;
  union                                            /* Offset=0x0004 : AHBMCTR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                                         /* [1:0] */
      __IO unsigned long   WBURST_TYPE:1;                              /* [2] */
      __IO unsigned long   :5;                                         /* [7:3] */
      __IO unsigned long   ENDIAN_CTR:2;                               /* [9:8] */
      __IO unsigned long   :2;                                         /* [11:10] */
      __IO unsigned long   MCYCLE_RST:1;                               /* [12] */
      __IO unsigned long   :18;                                        /* [30:13] */
      __IO unsigned long   ARBITER_CTR:1;                              /* [31] */
    } BIT;
  } AHBMCTR;
  union                                            /* Offset=0x0008 : AHBBINT */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   ERR_MASTER:4;                               /* [3:0] */
      __IO unsigned long   SBUS_ERRINT0:1;                             /* [4] */
      __IO unsigned long   :1;                                         /* [5] */
      __IO unsigned long   MBUS_ERRINT:1;                              /* [6] */
      __IO unsigned long   :6;                                         /* [12:7] */
      __IO unsigned long   VBUS_INT:1;                                 /* [13] */
      __IO unsigned long   :3;                                         /* [16:14] */
      __IO unsigned long   DMA_ENDINT_EP:15;                           /* [31:17] */
    } BIT;
  } AHBBINT;
  union                                            /* Offset=0x000C : AHBBINTEN */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :4;                                         /* [3:0] */
      __IO unsigned long   SBUS_ERRINT0EN:1;                           /* [4] */
      __IO unsigned long   :1;                                         /* [5] */
      __IO unsigned long   MBUS_ERRINTEN:1;                            /* [6] */
      __IO unsigned long   :6;                                         /* [12:7] */
      __IO unsigned long   VBUS_INTEN:1;                               /* [13] */
      __IO unsigned long   :3;                                         /* [16:14] */
      __IO unsigned long   DMA_ENDINTEN_EP:15;                         /* [31:17] */
    } BIT;
  } AHBBINTEN;
  union                                            /* Offset=0x0010 : EPCTR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EPC_RST:1;                                  /* [0] */
      __IO unsigned long   :1;                                         /* [1] */
      __IO unsigned long   PLL_RST:1;                                  /* [2] */
      __IO unsigned long   :1;                                         /* [3] */
      __I  unsigned long   PLL_LOCK:1;                                 /* [4] */
      __IO unsigned long   PLL_RESUME:1;                               /* [5] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __I  unsigned long   VBUS_LEVEL:1;                               /* [8] */
      __IO unsigned long   :3;                                         /* [11:9] */
      __IO unsigned long   DIRPD:1;                                    /* [12] */
      __IO unsigned long   :19;                                        /* [31:13] */
    } BIT;
  } EPCTR;
  char                     wk_0014[0x000C];
  union                                            /* Offset=0x0020 : USBSSVER */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SS_VER:8;                                   /* [7:0] */
      __I  unsigned long   EPC_VER:8;                                  /* [15:8] */
      __I  unsigned long   AHBB_VER:8;                                 /* [23:16] */
      __I  unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } USBSSVER;
  union                                            /* Offset=0x0024 : USBSSCONF */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   DMA_AVAILABLE:16;                           /* [15:0] */
      __I  unsigned long   EP_AVAILABLE:16;                            /* [31:16] */
    } BIT;
  } USBSSCONF;
  char                     wk_0028[0x00E8];
  union                                            /* Offset=0x0110 : EP1DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP1_REQEN:1;                                /* [0] */
      __IO unsigned long   EP1_DIR0:1;                                 /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP1_DMACNT:8;                               /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP1DCR1;
  union                                            /* Offset=0x0114 : EP1DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP1_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP1_LMPKT:11;                               /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP1DCR2;
  union                                            /* Offset=0x0118 : EP1TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP1_TADR:32;                                /* [31:0] */
    } BIT;
  } EP1TADR;
  char                     wk_011C[0x0004];
  union                                            /* Offset=0x0120 : EP2DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP2_REQEN:1;                                /* [0] */
      __IO unsigned long   EP2_DIR0:1;                                 /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP2_DMACNT:8;                               /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP2DCR1;
  union                                            /* Offset=0x0124 : EP2DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP2_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP2_LMPKT:11;                               /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP2DCR2;
  union                                            /* Offset=0x0128 : EP2TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP2_TADR:32;                                /* [31:0] */
    } BIT;
  } EP2TADR;
  char                     wk_012C[0x0004];
  union                                            /* Offset=0x0130 : EP3DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP3_REQEN:1;                                /* [0] */
      __IO unsigned long   EP3_DIR0:1;                                 /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP3_DMACNT:8;                               /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP3DCR1;
  union                                            /* Offset=0x0134 : EP3DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP3_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP3_LMPKT:11;                               /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP3DCR2;
  union                                            /* Offset=0x0138 : EP3TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP3_TADR:32;                                /* [31:0] */
    } BIT;
  } EP3TADR;
  char                     wk_013C[0x0004];
  union                                            /* Offset=0x0140 : EP4DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP4_REQEN:1;                                /* [0] */
      __IO unsigned long   EP4_DIR0:1;                                 /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP4_DMACNT:8;                               /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP4DCR1;
  union                                            /* Offset=0x0144 : EP4DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP4_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP4_LMPKT:11;                               /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP4DCR2;
  union                                            /* Offset=0x0148 : EP4TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP4_TADR:32;                                /* [31:0] */
    } BIT;
  } EP4TADR;
  char                     wk_014C[0x0004];
  union                                            /* Offset=0x0150 : EP5DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP5_REQEN:1;                                /* [0] */
      __IO unsigned long   EP5_DIR0:1;                                 /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP5_DMACNT:8;                               /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP5DCR1;
  union                                            /* Offset=0x0154 : EP5DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP5_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP5_LMPKT:11;                               /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP5DCR2;
  union                                            /* Offset=0x0158 : EP5TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP5_TADR:32;                                /* [31:0] */
    } BIT;
  } EP5TADR;
  char                     wk_015C[0x0004];
  union                                            /* Offset=0x0160 : EP6DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP6_REQEN:1;                                /* [0] */
      __IO unsigned long   EP6_DIR0:1;                                 /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP6_DMACNT:8;                               /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP6DCR1;
  union                                            /* Offset=0x0164 : EP6DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP6_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP6_LMPKT:11;                               /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP6DCR2;
  union                                            /* Offset=0x0168 : EP6TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP6_TADR:32;                                /* [31:0] */
    } BIT;
  } EP6TADR;
  char                     wk_016C[0x0004];
  union                                            /* Offset=0x0170 : EP7DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP7_REQEN:1;                                /* [0] */
      __IO unsigned long   EP7_DIR0:1;                                 /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP7_DMACNT:8;                               /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP7DCR1;
  union                                            /* Offset=0x0174 : EP7DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP7_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP7_LMPKT:11;                               /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP7DCR2;
  union                                            /* Offset=0x0178 : EP7TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP7_TADR:32;                                /* [31:0] */
    } BIT;
  } EP7TADR;
  char                     wk_017C[0x0004];
  union                                            /* Offset=0x0180 : EP8DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP8_REQEN:1;                                /* [0] */
      __IO unsigned long   EP8_DIR0:1;                                 /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP8_DMACNT:8;                               /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP8DCR1;
  union                                            /* Offset=0x0184 : EP8DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP8_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP8_LMPKT:11;                               /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP8DCR2;
  union                                            /* Offset=0x0188 : EP8TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP8_TADR:32;                                /* [31:0] */
    } BIT;
  } EP8TADR;
  char                     wk_018C[0x0004];
  union                                            /* Offset=0x0190 : EP9DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP9_REQEN:1;                                /* [0] */
      __IO unsigned long   EP9_DIR0:1;                                 /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP9_DMACNT:8;                               /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP9DCR1;
  union                                            /* Offset=0x0194 : EP9DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP9_MPKT:11;                                /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP9_LMPKT:11;                               /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP9DCR2;
  union                                            /* Offset=0x0198 : EP9TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP9_TADR:32;                                /* [31:0] */
    } BIT;
  } EP9TADR;
  char                     wk_019C[0x0004];
  union                                            /* Offset=0x01A0 : EP10DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP10_REQEN:1;                               /* [0] */
      __IO unsigned long   EP10_DIR0:1;                                /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP10_DMACNT:8;                              /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP10DCR1;
  union                                            /* Offset=0x01A4 : EP10DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP10_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP10_LMPKT:11;                              /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP10DCR2;
  union                                            /* Offset=0x01A8 : EP10TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP10_TADR:32;                               /* [31:0] */
    } BIT;
  } EP10TADR;
  char                     wk_01AC[0x0004];
  union                                            /* Offset=0x01B0 : EP11DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP11_REQEN:1;                               /* [0] */
      __IO unsigned long   EP11_DIR0:1;                                /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP11_DMACNT:8;                              /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP11DCR1;
  union                                            /* Offset=0x01B4 : EP11DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP11_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP11_LMPKT:11;                              /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP11DCR2;
  union                                            /* Offset=0x01B8 : EP11TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP11_TADR:32;                               /* [31:0] */
    } BIT;
  } EP11TADR;
  char                     wk_01BC[0x0004];
  union                                            /* Offset=0x01C0 : EP12DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP12_REQEN:1;                               /* [0] */
      __IO unsigned long   EP12_DIR0:1;                                /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP12_DMACNT:8;                              /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP12DCR1;
  union                                            /* Offset=0x01C4 : EP12DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP12_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP12_LMPKT:11;                              /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP12DCR2;
  union                                            /* Offset=0x01C8 : EP12TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP12_TADR:32;                               /* [31:0] */
    } BIT;
  } EP12TADR;
  char                     wk_01CC[0x0004];
  union                                            /* Offset=0x01D0 : EP13DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP13_REQEN:1;                               /* [0] */
      __IO unsigned long   EP13_DIR0:1;                                /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP13_DMACNT:8;                              /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP13DCR1;
  union                                            /* Offset=0x01D4 : EP13DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP13_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP13_LMPKT:11;                              /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP13DCR2;
  union                                            /* Offset=0x01D8 : EP13TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP13_TADR:32;                               /* [31:0] */
    } BIT;
  } EP13TADR;
  char                     wk_01DC[0x0004];
  union                                            /* Offset=0x01E0 : EP14DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP14_REQEN:1;                               /* [0] */
      __IO unsigned long   EP14_DIR0:1;                                /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP14_DMACNT:8;                              /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP14DCR1;
  union                                            /* Offset=0x01E4 : EP14DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP14_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP14_LMPKT:11;                              /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP14DCR2;
  union                                            /* Offset=0x01E8 : EP14TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP14_TADR:32;                               /* [31:0] */
    } BIT;
  } EP14TADR;
  char                     wk_01EC[0x0004];
  union                                            /* Offset=0x01F0 : EP15DCR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP15_REQEN:1;                               /* [0] */
      __IO unsigned long   EP15_DIR0:1;                                /* [1] */
      __IO unsigned long   :14;                                        /* [15:2] */
      __IO unsigned long   EP15_DMACNT:8;                              /* [23:16] */
      __IO unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } EP15DCR1;
  union                                            /* Offset=0x01F4 : EP15DCR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP15_MPKT:11;                               /* [10:0] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   EP15_LMPKT:11;                              /* [26:16] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } EP15DCR2;
  union                                            /* Offset=0x01F8 : EP15TADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP15_TADR:32;                               /* [31:0] */
    } BIT;
  } EP15TADR;
} USBf_AHBEPC_Type;
#endif  /* End of __USBf_AHBEPC_SFR__DEFINE_HEADER__ */
