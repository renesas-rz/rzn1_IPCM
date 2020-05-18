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
 **       for RZN1 GMAC1
 **
 **       revision 0.20 (2.Nov.2017)
 **
 **********************************************************************************************************************/
#ifndef __GMAC1_SFR__DEFINE_HEADER__
#define __GMAC1_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : GMAC1
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : MAC_Configuration */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PRELEN:2;                                   /* [1:0] */
      __IO unsigned long   RE:1;                                       /* [2] */
      __IO unsigned long   TE:1;                                       /* [3] */
      __IO unsigned long   DC:1;                                       /* [4] */
      __IO unsigned long   BL:2;                                       /* [6:5] */
      __IO unsigned long   ACS:1;                                      /* [7] */
      __IO unsigned long   :1;                                         /* [8] */
      __IO unsigned long   DR:1;                                       /* [9] */
      __IO unsigned long   IPC:1;                                      /* [10] */
      __IO unsigned long   DM:1;                                       /* [11] */
      __IO unsigned long   LM:1;                                       /* [12] */
      __IO unsigned long   DO:1;                                       /* [13] */
      __IO unsigned long   FES:1;                                      /* [14] */
      __IO unsigned long   PS:1;                                       /* [15] */
      __IO unsigned long   DCRS:1;                                     /* [16] */
      __IO unsigned long   IFG:3;                                      /* [19:17] */
      __IO unsigned long   JE:1;                                       /* [20] */
      __IO unsigned long   BE:1;                                       /* [21] */
      __IO unsigned long   JD:1;                                       /* [22] */
      __IO unsigned long   WD:1;                                       /* [23] */
      __IO unsigned long   :1;                                         /* [24] */
      __IO unsigned long   CST:1;                                      /* [25] */
      __IO unsigned long   :1;                                         /* [26] */
      __IO unsigned long   TWOKPE:1;                                   /* [27] */
      __IO unsigned long   :4;                                         /* [31:28] */
    } BIT;
  } MAC_Configuration;
  union                                            /* Offset=0x0004 : MAC_Frame_Filter */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PR:1;                                       /* [0] */
      __IO unsigned long   HUC:1;                                      /* [1] */
      __IO unsigned long   HMC:1;                                      /* [2] */
      __IO unsigned long   DAIF:1;                                     /* [3] */
      __IO unsigned long   PM:1;                                       /* [4] */
      __IO unsigned long   DBF:1;                                      /* [5] */
      __IO unsigned long   PCF:2;                                      /* [7:6] */
      __IO unsigned long   SAIF:1;                                     /* [8] */
      __IO unsigned long   SAF:1;                                      /* [9] */
      __IO unsigned long   HPF:1;                                      /* [10] */
      __IO unsigned long   :5;                                         /* [15:11] */
      __IO unsigned long   VTFE:1;                                     /* [16] */
      __IO unsigned long   :14;                                        /* [30:17] */
      __IO unsigned long   RA:1;                                       /* [31] */
    } BIT;
  } MAC_Frame_Filter;
  char                     wk_0008[0x0008];
  union                                            /* Offset=0x0010 : GMII_Address */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   GB:1;                                       /* [0] */
      __IO unsigned long   GW:1;                                       /* [1] */
      __IO unsigned long   CR:4;                                       /* [5:2] */
      __IO unsigned long   GR:5;                                       /* [10:6] */
      __IO unsigned long   PA:5;                                       /* [15:11] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } GMII_Address;
  union                                            /* Offset=0x0014 : GMII_Data */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   GD:16;                                      /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } GMII_Data;
  union                                            /* Offset=0x0018 : Flow_Control */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FCA_BPA:1;                                  /* [0] */
      __IO unsigned long   TFE:1;                                      /* [1] */
      __IO unsigned long   RFE:1;                                      /* [2] */
      __IO unsigned long   UP:1;                                       /* [3] */
      __IO unsigned long   PLT:2;                                      /* [5:4] */
      __IO unsigned long   :1;                                         /* [6] */
      __IO unsigned long   DZPQ:1;                                     /* [7] */
      __IO unsigned long   :8;                                         /* [15:8] */
      __IO unsigned long   PT:16;                                      /* [31:16] */
    } BIT;
  } Flow_Control;
  union                                            /* Offset=0x001C : VLAN_Tag */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   VL:16;                                      /* [15:0] */
      __IO unsigned long   ETV:1;                                      /* [16] */
      __IO unsigned long   VTIM:1;                                     /* [17] */
      __IO unsigned long   ESVL:1;                                     /* [18] */
      __IO unsigned long   VTHM:1;                                     /* [19] */
      __IO unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } VLAN_Tag;
  union                                            /* Offset=0x0020 : Version */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   VER:16;                                     /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Version;
  union                                            /* Offset=0x0024 : Debug */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RPESTS:1;                                   /* [0] */
      __I  unsigned long   RFCFCSTS:2;                                 /* [2:1] */
      __I  unsigned long   :1;                                         /* [3] */
      __I  unsigned long   RWCSTS:1;                                   /* [4] */
      __I  unsigned long   RRCSTS:2;                                   /* [6:5] */
      __I  unsigned long   :1;                                         /* [7] */
      __I  unsigned long   RXFSTS:2;                                   /* [9:8] */
      __I  unsigned long   :6;                                         /* [15:10] */
      __I  unsigned long   TPESTS:1;                                   /* [16] */
      __I  unsigned long   TFCSTS:2;                                   /* [18:17] */
      __I  unsigned long   TXPAUSED:1;                                 /* [19] */
      __I  unsigned long   TRCSTS:2;                                   /* [21:20] */
      __I  unsigned long   TWCSTS:1;                                   /* [22] */
      __I  unsigned long   :1;                                         /* [23] */
      __I  unsigned long   TXFSTS:1;                                   /* [24] */
      __I  unsigned long   TXSTSFSTS:1;                                /* [25] */
      __I  unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } Debug;
  union                                            /* Offset=0x0028 : Remote_Wake_Up_Frame_Filter */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WKUPFRMFTR:32;                              /* [31:0] */
    } BIT;
  } Remote_Wake_Up_Frame_Filter;
  union                                            /* Offset=0x002C : PMT_Control_Status */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PWRDWN:1;                                   /* [0] */
      __IO unsigned long   MGKPKTEN:1;                                 /* [1] */
      __IO unsigned long   RWKPKTEN:1;                                 /* [2] */
      __IO unsigned long   :2;                                         /* [4:3] */
      __I  unsigned long   MGKPRCVD:1;                                 /* [5] */
      __I  unsigned long   RWKPRCVD:1;                                 /* [6] */
      __IO unsigned long   :2;                                         /* [8:7] */
      __IO unsigned long   GLBLUCAST:1;                                /* [9] */
      __IO unsigned long   RWKPFE:1;                                   /* [10] */
      __IO unsigned long   :13;                                        /* [23:11] */
      __IO unsigned long   RWKPTR:3;                                   /* [26:24] */
      __IO unsigned long   :4;                                         /* [30:27] */
      __IO unsigned long   RWKFILTRST:1;                               /* [31] */
    } BIT;
  } PMT_Control_Status;
  union                                            /* Offset=0x0030 : LPI_Control_Status */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   TLPIEN:1;                                   /* [0] */
      __I  unsigned long   TLPIEX:1;                                   /* [1] */
      __I  unsigned long   RLPIEN:1;                                   /* [2] */
      __I  unsigned long   RLPIEX:1;                                   /* [3] */
      __IO unsigned long   :4;                                         /* [7:4] */
      __I  unsigned long   TLPIST:1;                                   /* [8] */
      __I  unsigned long   RLPIST:1;                                   /* [9] */
      __IO unsigned long   :6;                                         /* [15:10] */
      __IO unsigned long   LPIEN:1;                                    /* [16] */
      __IO unsigned long   PLS:1;                                      /* [17] */
      __IO unsigned long   :1;                                         /* [18] */
      __IO unsigned long   LPITXA:1;                                   /* [19] */
      __IO unsigned long   :12;                                        /* [31:20] */
    } BIT;
  } LPI_Control_Status;
  union                                            /* Offset=0x0034 : LPI_Timers_Control */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TWT:16;                                     /* [15:0] */
      __IO unsigned long   LST:10;                                     /* [25:16] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } LPI_Timers_Control;
  union                                            /* Offset=0x0038 : Interrupt_Status */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :3;                                         /* [2:0] */
      __I  unsigned long   PMTIS:1;                                    /* [3] */
      __I  unsigned long   MMCIS:1;                                    /* [4] */
      __I  unsigned long   MMCRXIS:1;                                  /* [5] */
      __I  unsigned long   MMCTXIS:1;                                  /* [6] */
      __I  unsigned long   MMCRXIPIS:1;                                /* [7] */
      __I  unsigned long   :1;                                         /* [8] */
      __I  unsigned long   TSIS:1;                                     /* [9] */
      __I  unsigned long   LPIIS:1;                                    /* [10] */
      __I  unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } Interrupt_Status;
  union                                            /* Offset=0x003C : Interrupt_Mask */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                                         /* [2:0] */
      __IO unsigned long   PMTIM:1;                                    /* [3] */
      __IO unsigned long   :5;                                         /* [8:4] */
      __IO unsigned long   TSIM:1;                                     /* [9] */
      __IO unsigned long   LPIIM:1;                                    /* [10] */
      __IO unsigned long   :21;                                        /* [31:11] */
    } BIT;
  } Interrupt_Mask;
  union                                            /* Offset=0x0040 : MAC_Address0_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :15;                                        /* [30:16] */
      __I  unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address0_High;
  union                                            /* Offset=0x0044 : MAC_Address0_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address0_Low;
  union                                            /* Offset=0x0048 : MAC_Address1_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address1_High;
  union                                            /* Offset=0x004C : MAC_Address1_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address1_Low;
  union                                            /* Offset=0x0050 : MAC_Address2_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address2_High;
  union                                            /* Offset=0x0054 : MAC_Address2_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address2_Low;
  union                                            /* Offset=0x0058 : MAC_Address3_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address3_High;
  union                                            /* Offset=0x005C : MAC_Address3_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address3_Low;
  union                                            /* Offset=0x0060 : MAC_Address4_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address4_High;
  union                                            /* Offset=0x0064 : MAC_Address4_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address4_Low;
  union                                            /* Offset=0x0068 : MAC_Address5_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address5_High;
  union                                            /* Offset=0x006C : MAC_Address5_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address5_Low;
  union                                            /* Offset=0x0070 : MAC_Address6_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address6_High;
  union                                            /* Offset=0x0074 : MAC_Address6_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address6_Low;
  union                                            /* Offset=0x0078 : MAC_Address7_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address7_High;
  union                                            /* Offset=0x007C : MAC_Address7_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address7_Low;
  union                                            /* Offset=0x0080 : MAC_Address8_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address8_High;
  union                                            /* Offset=0x0084 : MAC_Address8_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address8_Low;
  union                                            /* Offset=0x0088 : MAC_Address9_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address9_High;
  union                                            /* Offset=0x008C : MAC_Address9_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address9_Low;
  union                                            /* Offset=0x0090 : MAC_Address10_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address10_High;
  union                                            /* Offset=0x0094 : MAC_Address10_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address10_Low;
  union                                            /* Offset=0x0098 : MAC_Address11_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address11_High;
  union                                            /* Offset=0x009C : MAC_Address11_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address11_Low;
  union                                            /* Offset=0x00A0 : MAC_Address12_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address12_High;
  union                                            /* Offset=0x00A4 : MAC_Address12_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address12_Low;
  union                                            /* Offset=0x00A8 : MAC_Address13_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address13_High;
  union                                            /* Offset=0x00AC : MAC_Address13_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address13_Low;
  union                                            /* Offset=0x00B0 : MAC_Address14_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address14_High;
  union                                            /* Offset=0x00B4 : MAC_Address14_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address14_Low;
  union                                            /* Offset=0x00B8 : MAC_Address15_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address15_High;
  union                                            /* Offset=0x00BC : MAC_Address15_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address15_Low;
  char                     wk_00C0[0x001C];
  union                                            /* Offset=0x00DC : WDog_Timeout */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WTO:14;                                     /* [13:0] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   PWE:1;                                      /* [16] */
      __IO unsigned long   :15;                                        /* [31:17] */
    } BIT;
  } WDog_Timeout;
  char                     wk_00E0[0x0020];
  union                                            /* Offset=0x0100 : MMC_Control */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   CNTRST:1;                                   /* [0] */
      __IO unsigned long   CNTSTOPRO:1;                                /* [1] */
      __IO unsigned long   RSTONRD:1;                                  /* [2] */
      __IO unsigned long   CNTFREEZ:1;                                 /* [3] */
      __IO unsigned long   CNTPRST:1;                                  /* [4] */
      __IO unsigned long   CNTPRSTLVL:1;                               /* [5] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   UCDBC:1;                                    /* [8] */
      __IO unsigned long   :23;                                        /* [31:9] */
    } BIT;
  } MMC_Control;
  union                                            /* Offset=0x0104 : MMC_Receive_Interrupt */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXGBFRMIS:1;                                /* [0] */
      __I  unsigned long   RXGBOCTIS:1;                                /* [1] */
      __I  unsigned long   RXGOCTIS:1;                                 /* [2] */
      __I  unsigned long   RXBCGFIS:1;                                 /* [3] */
      __I  unsigned long   RXMCGFIS:1;                                 /* [4] */
      __I  unsigned long   RXCRCERFIS:1;                               /* [5] */
      __I  unsigned long   RXALGNERFIS:1;                              /* [6] */
      __I  unsigned long   RXRUNTFIS:1;                                /* [7] */
      __I  unsigned long   RXJABERFIS:1;                               /* [8] */
      __I  unsigned long   RXUSIZEGFIS:1;                              /* [9] */
      __I  unsigned long   RXOSIZEGFIS:1;                              /* [10] */
      __I  unsigned long   RX64OCTGBFIS:1;                             /* [11] */
      __I  unsigned long   RX65T127OCTGBFIS:1;                         /* [12] */
      __I  unsigned long   RX128T255OCTGBFIS:1;                        /* [13] */
      __I  unsigned long   RX256T511OCTGBFIS:1;                        /* [14] */
      __I  unsigned long   RX512T1023OCTGBFIS:1;                       /* [15] */
      __I  unsigned long   RX1024TMAXOCTGBFIS:1;                       /* [16] */
      __I  unsigned long   RXUCGFIS:1;                                 /* [17] */
      __I  unsigned long   RXLENERFIS:1;                               /* [18] */
      __I  unsigned long   RXORANGEFIS:1;                              /* [19] */
      __I  unsigned long   RXPAUSFIS:1;                                /* [20] */
      __I  unsigned long   RXFOVFIS:1;                                 /* [21] */
      __I  unsigned long   RXVLANGBFIS:1;                              /* [22] */
      __I  unsigned long   RXWDOGFIS:1;                                /* [23] */
      __I  unsigned long   RXRCVERRFIS:1;                              /* [24] */
      __I  unsigned long   RXCTRLFIS:1;                                /* [25] */
      __I  unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } MMC_Receive_Interrupt;
  union                                            /* Offset=0x0108 : MMC_Transmit_Interrupt */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXGBOCTIS:1;                                /* [0] */
      __I  unsigned long   TXGBFRMIS:1;                                /* [1] */
      __I  unsigned long   TXBCGFIS:1;                                 /* [2] */
      __I  unsigned long   TXMCGFIS:1;                                 /* [3] */
      __I  unsigned long   TX64OCTGBFIS:1;                             /* [4] */
      __I  unsigned long   TX65T127OCTGBFIS:1;                         /* [5] */
      __I  unsigned long   TX128T255OCTGBFIS:1;                        /* [6] */
      __I  unsigned long   TX256T511OCTGBFIS:1;                        /* [7] */
      __I  unsigned long   TX512T1023OCTGBFIS:1;                       /* [8] */
      __I  unsigned long   TX1024TMAXOCTGBFIS:1;                       /* [9] */
      __I  unsigned long   TXUCGBFIS:1;                                /* [10] */
      __I  unsigned long   TXMCGBFIS:1;                                /* [11] */
      __I  unsigned long   TXBCGBFIS:1;                                /* [12] */
      __I  unsigned long   TXUFLOWERFIS:1;                             /* [13] */
      __I  unsigned long   TXSCOLGFIS:1;                               /* [14] */
      __I  unsigned long   TXMCOLGFIS:1;                               /* [15] */
      __I  unsigned long   TXDEFFIS:1;                                 /* [16] */
      __I  unsigned long   TXLATCOLFIS:1;                              /* [17] */
      __I  unsigned long   TXEXCOLFIS:1;                               /* [18] */
      __I  unsigned long   TXCARERFIS:1;                               /* [19] */
      __I  unsigned long   TXGOCTIS:1;                                 /* [20] */
      __I  unsigned long   TXGFRMIS:1;                                 /* [21] */
      __I  unsigned long   TXEXDEFFIS:1;                               /* [22] */
      __I  unsigned long   TXPAUSFIS:1;                                /* [23] */
      __I  unsigned long   TXVLANGFIS:1;                               /* [24] */
      __I  unsigned long   TXOSIZEGFIS:1;                              /* [25] */
      __I  unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } MMC_Transmit_Interrupt;
  union                                            /* Offset=0x010C : MMC_Receive_Interrupt_Mask */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RXGBFRMIM:1;                                /* [0] */
      __IO unsigned long   RXGBOCTIM:1;                                /* [1] */
      __IO unsigned long   RXGOCTIM:1;                                 /* [2] */
      __IO unsigned long   RXBCGFIM:1;                                 /* [3] */
      __IO unsigned long   RXMCGFIM:1;                                 /* [4] */
      __IO unsigned long   RXCRCERFIM:1;                               /* [5] */
      __IO unsigned long   RXALGNERFIM:1;                              /* [6] */
      __IO unsigned long   RXRUNTFIM:1;                                /* [7] */
      __IO unsigned long   RXJABERFIM:1;                               /* [8] */
      __IO unsigned long   RXUSIZEGFIM:1;                              /* [9] */
      __IO unsigned long   RXOSIZEGFIM:1;                              /* [10] */
      __IO unsigned long   RX64OCTGBFIM:1;                             /* [11] */
      __IO unsigned long   RX65T127OCTGBFIM:1;                         /* [12] */
      __IO unsigned long   RX128T255OCTGBFIM:1;                        /* [13] */
      __IO unsigned long   RX256T511OCTGBFIM:1;                        /* [14] */
      __IO unsigned long   RX512T1023OCTGBFIM:1;                       /* [15] */
      __IO unsigned long   RX1024TMAXOCTGBFIM:1;                       /* [16] */
      __IO unsigned long   RXUCGFIM:1;                                 /* [17] */
      __IO unsigned long   RXLENERFIM:1;                               /* [18] */
      __IO unsigned long   RXORANGEFIM:1;                              /* [19] */
      __IO unsigned long   RXPAUSFIM:1;                                /* [20] */
      __IO unsigned long   RXFOVFIM:1;                                 /* [21] */
      __IO unsigned long   RXVLANGBFIM:1;                              /* [22] */
      __IO unsigned long   RXWDOGFIM:1;                                /* [23] */
      __IO unsigned long   RXRCVERRFIM:1;                              /* [24] */
      __IO unsigned long   RXCTRLFIM:1;                                /* [25] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } MMC_Receive_Interrupt_Mask;
  union                                            /* Offset=0x0110 : MMC_Transmit_Interrupt_Mask */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TXGBOCTIM:1;                                /* [0] */
      __IO unsigned long   TXGBFRMIM:1;                                /* [1] */
      __IO unsigned long   TXBCGFIM:1;                                 /* [2] */
      __IO unsigned long   TXMCGFIM:1;                                 /* [3] */
      __IO unsigned long   TX64OCTGBFIM:1;                             /* [4] */
      __IO unsigned long   TX65T127OCTGBFIM:1;                         /* [5] */
      __IO unsigned long   TX128T255OCTGBFIM:1;                        /* [6] */
      __IO unsigned long   TX256T511OCTGBFIM:1;                        /* [7] */
      __IO unsigned long   TX512T1023OCTGBFIM:1;                       /* [8] */
      __IO unsigned long   TX1024TMAXOCTGBFIM:1;                       /* [9] */
      __IO unsigned long   TXUCGBFIM:1;                                /* [10] */
      __IO unsigned long   TXMCGBFIM:1;                                /* [11] */
      __IO unsigned long   TXBCGBFIM:1;                                /* [12] */
      __IO unsigned long   TXUFLOWERFIM:1;                             /* [13] */
      __IO unsigned long   TXSCOLGFIM:1;                               /* [14] */
      __IO unsigned long   TXMCOLGFIM:1;                               /* [15] */
      __IO unsigned long   TXDEFFIM:1;                                 /* [16] */
      __IO unsigned long   TXLATCOLFIM:1;                              /* [17] */
      __IO unsigned long   TXEXCOLFIM:1;                               /* [18] */
      __IO unsigned long   TXCARERFIM:1;                               /* [19] */
      __IO unsigned long   TXGOCTIM:1;                                 /* [20] */
      __IO unsigned long   TXGFRMIM:1;                                 /* [21] */
      __IO unsigned long   TXEXDEFFIM:1;                               /* [22] */
      __IO unsigned long   TXPAUSFIM:1;                                /* [23] */
      __IO unsigned long   TXVLANGFIM:1;                               /* [24] */
      __IO unsigned long   TXOSIZEGFIM:1;                              /* [25] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } MMC_Transmit_Interrupt_Mask;
  union                                            /* Offset=0x0114 : Tx_Octet_Count_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXOCTGB:32;                                 /* [31:0] */
    } BIT;
  } Tx_Octet_Count_Good_Bad;
  union                                            /* Offset=0x0118 : Tx_Frame_Count_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXFRMGB:32;                                 /* [31:0] */
    } BIT;
  } Tx_Frame_Count_Good_Bad;
  union                                            /* Offset=0x011C : Tx_Broadcast_Frames_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXBCASTG:32;                                /* [31:0] */
    } BIT;
  } Tx_Broadcast_Frames_Good;
  union                                            /* Offset=0x0120 : Tx_Multicast_Frames_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXMCASTG:32;                                /* [31:0] */
    } BIT;
  } Tx_Multicast_Frames_Good;
  union                                            /* Offset=0x0124 : Tx_64Octets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TX64OCTGB:32;                               /* [31:0] */
    } BIT;
  } Tx_64Octets_Frames_Good_Bad;
  union                                            /* Offset=0x0128 : Tx_65To127Octets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TX65_127OCTGB:32;                           /* [31:0] */
    } BIT;
  } Tx_65To127Octets_Frames_Good_Bad;
  union                                            /* Offset=0x012C : Tx_128To255Octets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TX128_255OCTGB:32;                          /* [31:0] */
    } BIT;
  } Tx_128To255Octets_Frames_Good_Bad;
  union                                            /* Offset=0x0130 : Tx_256To511Octets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TX256_511OCTGB:32;                          /* [31:0] */
    } BIT;
  } Tx_256To511Octets_Frames_Good_Bad;
  union                                            /* Offset=0x0134 : Tx_512To1023Octets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TX512_1023OCTGB:32;                         /* [31:0] */
    } BIT;
  } Tx_512To1023Octets_Frames_Good_Bad;
  union                                            /* Offset=0x0138 : Tx_1024ToMaxOctets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TX1024_MAXOCTGB:32;                         /* [31:0] */
    } BIT;
  } Tx_1024ToMaxOctets_Frames_Good_Bad;
  union                                            /* Offset=0x013C : Tx_Unicast_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXUCASTGB:32;                               /* [31:0] */
    } BIT;
  } Tx_Unicast_Frames_Good_Bad;
  union                                            /* Offset=0x0140 : Tx_Multicast_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXMCASTGB:32;                               /* [31:0] */
    } BIT;
  } Tx_Multicast_Frames_Good_Bad;
  union                                            /* Offset=0x0144 : Tx_Broadcast_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXBCASTGB:32;                               /* [31:0] */
    } BIT;
  } Tx_Broadcast_Frames_Good_Bad;
  union                                            /* Offset=0x0148 : Tx_Underflow_Error_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXUNDRFLW:16;                               /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Tx_Underflow_Error_Frames;
  union                                            /* Offset=0x014C : Tx_Single_Collision_Good_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXSNGLCOLG:16;                              /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Tx_Single_Collision_Good_Frames;
  union                                            /* Offset=0x0150 : Tx_Multiple_Collision_Good_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXMULTCOLG:16;                              /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Tx_Multiple_Collision_Good_Frames;
  union                                            /* Offset=0x0154 : Tx_Deferred_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXDEFRD:16;                                 /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Tx_Deferred_Frames;
  union                                            /* Offset=0x0158 : Tx_Late_Collision_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXLATECOL:16;                               /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Tx_Late_Collision_Frames;
  union                                            /* Offset=0x015C : Tx_Excessive_Collision_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXEXSCOL:16;                                /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Tx_Excessive_Collision_Frames;
  union                                            /* Offset=0x0160 : Tx_Carrier_Error_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXCARR:16;                                  /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Tx_Carrier_Error_Frames;
  union                                            /* Offset=0x0164 : Tx_Octet_Count_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXOCTG:32;                                  /* [31:0] */
    } BIT;
  } Tx_Octet_Count_Good;
  union                                            /* Offset=0x0168 : Tx_Frame_Count_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXFRMG:32;                                  /* [31:0] */
    } BIT;
  } Tx_Frame_Count_Good;
  union                                            /* Offset=0x016C : Tx_Excessive_Deferral_Error */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXEXSDEF:16;                                /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Tx_Excessive_Deferral_Error;
  union                                            /* Offset=0x0170 : Tx_Pause_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXPAUSE:16;                                 /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Tx_Pause_Frames;
  union                                            /* Offset=0x0174 : Tx_VLAN_Frames_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXVLANG:32;                                 /* [31:0] */
    } BIT;
  } Tx_VLAN_Frames_Good;
  union                                            /* Offset=0x0178 : Tx_OSize_Frames_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TXOSIZG:16;                                 /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Tx_OSize_Frames_Good;
  char                     wk_017C[0x0004];
  union                                            /* Offset=0x0180 : Rx_Frames_Count_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXFRMGB:32;                                 /* [31:0] */
    } BIT;
  } Rx_Frames_Count_Good_Bad;
  union                                            /* Offset=0x0184 : Rx_Octet_Count_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXOCTGB:32;                                 /* [31:0] */
    } BIT;
  } Rx_Octet_Count_Good_Bad;
  union                                            /* Offset=0x0188 : Rx_Octet_Count_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXOCTG:32;                                  /* [31:0] */
    } BIT;
  } Rx_Octet_Count_Good;
  union                                            /* Offset=0x018C : Rx_Broadcast_Frames_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXBCASTG:32;                                /* [31:0] */
    } BIT;
  } Rx_Broadcast_Frames_Good;
  union                                            /* Offset=0x0190 : Rx_Multicast_Frames_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXMCASTG:32;                                /* [31:0] */
    } BIT;
  } Rx_Multicast_Frames_Good;
  union                                            /* Offset=0x0194 : Rx_CRC_Error_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXCRCERR:16;                                /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_CRC_Error_Frames;
  union                                            /* Offset=0x0198 : Rx_Alignment_Error_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXALGNERR:16;                               /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_Alignment_Error_Frames;
  union                                            /* Offset=0x019C : Rx_Runt_Error_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXRUNTERR:16;                               /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_Runt_Error_Frames;
  union                                            /* Offset=0x01A0 : Rx_Jabber_Error_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXJABERR:16;                                /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_Jabber_Error_Frames;
  union                                            /* Offset=0x01A4 : Rx_Undersize_Frames_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXUNDERSZG:16;                              /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_Undersize_Frames_Good;
  union                                            /* Offset=0x01A8 : Rx_Oversize_Frames_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXOVERSZG:16;                               /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_Oversize_Frames_Good;
  union                                            /* Offset=0x01AC : Rx_64Octets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RX64OCTGB:32;                               /* [31:0] */
    } BIT;
  } Rx_64Octets_Frames_Good_Bad;
  union                                            /* Offset=0x01B0 : Rx_65To127Octets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RX65_127OCTGB:32;                           /* [31:0] */
    } BIT;
  } Rx_65To127Octets_Frames_Good_Bad;
  union                                            /* Offset=0x01B4 : Rx_128To255Octets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RX128_255OCTGB:32;                          /* [31:0] */
    } BIT;
  } Rx_128To255Octets_Frames_Good_Bad;
  union                                            /* Offset=0x01B8 : Rx_256To511Octets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RX256_511OCTGB:32;                          /* [31:0] */
    } BIT;
  } Rx_256To511Octets_Frames_Good_Bad;
  union                                            /* Offset=0x01BC : Rx_512To1023Octets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RX512_1023OCTGB:32;                         /* [31:0] */
    } BIT;
  } Rx_512To1023Octets_Frames_Good_Bad;
  union                                            /* Offset=0x01C0 : Rx_1024ToMaxOctets_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RX1024_MAXOCTGB:32;                         /* [31:0] */
    } BIT;
  } Rx_1024ToMaxOctets_Frames_Good_Bad;
  union                                            /* Offset=0x01C4 : Rx_Unicast_Frames_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXUCASTG:32;                                /* [31:0] */
    } BIT;
  } Rx_Unicast_Frames_Good;
  union                                            /* Offset=0x01C8 : Rx_Length_Error_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXLENERR:16;                                /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_Length_Error_Frames;
  union                                            /* Offset=0x01CC : Rx_Out_Of_Range_Type_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXOUTOFRNG:16;                              /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_Out_Of_Range_Type_Frames;
  union                                            /* Offset=0x01D0 : Rx_Pause_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXPAUSEFRM:16;                              /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_Pause_Frames;
  union                                            /* Offset=0x01D4 : Rx_FIFO_Overflow_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXFIFOOVFL:16;                              /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_FIFO_Overflow_Frames;
  union                                            /* Offset=0x01D8 : Rx_VLAN_Frames_Good_Bad */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXVLANFRGB:32;                              /* [31:0] */
    } BIT;
  } Rx_VLAN_Frames_Good_Bad;
  union                                            /* Offset=0x01DC : Rx_Watchdog_Error_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXWDGERR:16;                                /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_Watchdog_Error_Frames;
  union                                            /* Offset=0x01E0 : Rx_Receive_Error_Frames */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXRCVERR:16;                                /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } Rx_Receive_Error_Frames;
  union                                            /* Offset=0x01E4 : Rx_Control_Frames_Good */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RXCTRLG:32;                                 /* [31:0] */
    } BIT;
  } Rx_Control_Frames_Good;
  char                     wk_01E8[0x0318];
  union                                            /* Offset=0x0500 : Hash_Table_Reg0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HT0:32;                                     /* [31:0] */
    } BIT;
  } Hash_Table_Reg0;
  union                                            /* Offset=0x0504 : Hash_Table_Reg1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HT1:32;                                     /* [31:0] */
    } BIT;
  } Hash_Table_Reg1;
  union                                            /* Offset=0x0508 : Hash_Table_Reg2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HT2:32;                                     /* [31:0] */
    } BIT;
  } Hash_Table_Reg2;
  union                                            /* Offset=0x050C : Hash_Table_Reg3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HT3:32;                                     /* [31:0] */
    } BIT;
  } Hash_Table_Reg3;
  union                                            /* Offset=0x0510 : Hash_Table_Reg4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HT4:32;                                     /* [31:0] */
    } BIT;
  } Hash_Table_Reg4;
  union                                            /* Offset=0x0514 : Hash_Table_Reg5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HT5:32;                                     /* [31:0] */
    } BIT;
  } Hash_Table_Reg5;
  union                                            /* Offset=0x0518 : Hash_Table_Reg6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HT6:32;                                     /* [31:0] */
    } BIT;
  } Hash_Table_Reg6;
  union                                            /* Offset=0x051C : Hash_Table_Reg7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   HT7:32;                                     /* [31:0] */
    } BIT;
  } Hash_Table_Reg7;
  char                     wk_0520[0x0068];
  union                                            /* Offset=0x0588 : VLAN_Hash_Table_Reg */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   VLHT:16;                                    /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } VLAN_Hash_Table_Reg;
  char                     wk_058C[0x0174];
  union                                            /* Offset=0x0700 : Timestamp_Control */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TSENA:1;                                    /* [0] */
      __IO unsigned long   TSCFUPDT:1;                                 /* [1] */
      __IO unsigned long   TSINIT:1;                                   /* [2] */
      __IO unsigned long   TSUPDT:1;                                   /* [3] */
      __IO unsigned long   TSTRIG:1;                                   /* [4] */
      __IO unsigned long   TSADDREG:1;                                 /* [5] */
      __IO unsigned long   :2;                                         /* [7:6] */
      __IO unsigned long   TSENALL:1;                                  /* [8] */
      __IO unsigned long   TSCTRLSSR:1;                                /* [9] */
      __IO unsigned long   TSVER2ENA:1;                                /* [10] */
      __IO unsigned long   TSIPENA:1;                                  /* [11] */
      __IO unsigned long   TSIPV6ENA:1;                                /* [12] */
      __IO unsigned long   TSIPV4ENA:1;                                /* [13] */
      __IO unsigned long   TSEVNTENA:1;                                /* [14] */
      __IO unsigned long   TSMSTRENA:1;                                /* [15] */
      __IO unsigned long   SNAPTYPSEL:2;                               /* [17:16] */
      __IO unsigned long   TSENMACADDR:1;                              /* [18] */
      __IO unsigned long   :5;                                         /* [23:19] */
      __IO unsigned long   ATSFC:1;                                    /* [24] */
      __IO unsigned long   ATSEN0:1;                                   /* [25] */
      __IO unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } Timestamp_Control;
  union                                            /* Offset=0x0704 : Sub_Second_Increment */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SSINC:8;                                    /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } Sub_Second_Increment;
  union                                            /* Offset=0x0708 : System_Time_Seconds */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TSS:32;                                     /* [31:0] */
    } BIT;
  } System_Time_Seconds;
  union                                            /* Offset=0x070C : System_Time_Nanoseconds */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TSSS:31;                                    /* [30:0] */
    } BIT;
  } System_Time_Nanoseconds;
  union                                            /* Offset=0x0710 : System_Time_Seconds_Update */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TSS:32;                                     /* [31:0] */
    } BIT;
  } System_Time_Seconds_Update;
  union                                            /* Offset=0x0714 : System_Time_Nanoseconds_Update */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TSSS:31;                                    /* [30:0] */
      __IO unsigned long   ADDSUB:1;                                   /* [31] */
    } BIT;
  } System_Time_Nanoseconds_Update;
  union                                            /* Offset=0x0718 : Timestamp_Addend */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TSAR:32;                                    /* [31:0] */
    } BIT;
  } Timestamp_Addend;
  union                                            /* Offset=0x071C : Target_Time_Seconds */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TSTR:32;                                    /* [31:0] */
    } BIT;
  } Target_Time_Seconds;
  union                                            /* Offset=0x0720 : Target_Time_Nanoseconds */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TTSLO:31;                                   /* [30:0] */
      __IO unsigned long   TRGTBUSY:1;                                 /* [31] */
    } BIT;
  } Target_Time_Nanoseconds;
  char                     wk_0724[0x0004];
  union                                            /* Offset=0x0728 : Timestamp_Status */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   TSSOVF:1;                                   /* [0] */
      __I  unsigned long   TSTARGT:1;                                  /* [1] */
      __I  unsigned long   AUXTSTRIG:1;                                /* [2] */
      __I  unsigned long   TSTRGTERR:1;                                /* [3] */
      __I  unsigned long   TSTARGT1:1;                                 /* [4] */
      __I  unsigned long   TSTRGTERR1:1;                               /* [5] */
      __I  unsigned long   :10;                                        /* [15:6] */
      __I  unsigned long   ATSSTN:4;                                   /* [19:16] */
      __I  unsigned long   :4;                                         /* [23:20] */
      __I  unsigned long   ATSSTM:1;                                   /* [24] */
      __I  unsigned long   ATSNS:5;                                    /* [29:25] */
      __I  unsigned long   :2;                                         /* [31:30] */
    } BIT;
  } Timestamp_Status;
  union                                            /* Offset=0x072C : PPS_Control */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PPSCTRL_PPSCMD:4;                           /* [3:0] */
      __IO unsigned long   PPSEN0:1;                                   /* [4] */
      __IO unsigned long   TRGTMODSEL0:2;                              /* [6:5] */
      __IO unsigned long   :1;                                         /* [7] */
      __IO unsigned long   PPSCMD1:3;                                  /* [10:8] */
      __IO unsigned long   :2;                                         /* [12:11] */
      __IO unsigned long   TRGTMODSEL1:2;                              /* [14:13] */
      __IO unsigned long   :1;                                         /* [15] */
      __IO unsigned long   PPSCMD2:3;                                  /* [18:16] */
      __IO unsigned long   :2;                                         /* [20:19] */
      __IO unsigned long   TRGTMODSEL2:2;                              /* [22:21] */
      __IO unsigned long   :1;                                         /* [23] */
      __IO unsigned long   PPSCMD3:3;                                  /* [26:24] */
      __IO unsigned long   :2;                                         /* [28:27] */
      __IO unsigned long   TRGTMODSEL3:2;                              /* [30:29] */
    } BIT;
  } PPS_Control;
  union                                            /* Offset=0x0730 : Auxiliary_Timestamp_Nanoseconds */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   AUXTSLO:31;                                 /* [30:0] */
    } BIT;
  } Auxiliary_Timestamp_Nanoseconds;
  union                                            /* Offset=0x0734 : Auxiliary_Timestamp_Seconds */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   AUXTSHI:32;                                 /* [31:0] */
    } BIT;
  } Auxiliary_Timestamp_Seconds;
  char                     wk_0738[0x0028];
  union                                            /* Offset=0x0760 : PPS0_Interval */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PPSINT:32;                                  /* [31:0] */
    } BIT;
  } PPS0_Interval;
  union                                            /* Offset=0x0764 : PPS0_Width */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PPSWIDTH:32;                                /* [31:0] */
    } BIT;
  } PPS0_Width;
  char                     wk_0768[0x0018];
  union                                            /* Offset=0x0780 : PPS1_Target_Time_Seconds */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TSTRH1:32;                                  /* [31:0] */
    } BIT;
  } PPS1_Target_Time_Seconds;
  union                                            /* Offset=0x0784 : PPS1_Target_Time_Nanoseconds */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TTSL1:31;                                   /* [30:0] */
      __IO unsigned long   TRGTBUSY1:1;                                /* [31] */
    } BIT;
  } PPS1_Target_Time_Nanoseconds;
  union                                            /* Offset=0x0788 : PPS1_Interval */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PPSINT:32;                                  /* [31:0] */
    } BIT;
  } PPS1_Interval;
  union                                            /* Offset=0x078C : PPS1_Width */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   PPSWIDTH:32;                                /* [31:0] */
    } BIT;
  } PPS1_Width;
  char                     wk_0790[0x0070];
  union                                            /* Offset=0x0800 : MAC_Address16_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address16_High;
  union                                            /* Offset=0x0804 : MAC_Address16_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address16_Low;
  union                                            /* Offset=0x0808 : MAC_Address17_High */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRHI:16;                                  /* [15:0] */
      __IO unsigned long   :8;                                         /* [23:16] */
      __IO unsigned long   MBC:6;                                      /* [29:24] */
      __IO unsigned long   SA:1;                                       /* [30] */
      __IO unsigned long   AE:1;                                       /* [31] */
    } BIT;
  } MAC_Address17_High;
  union                                            /* Offset=0x080C : MAC_Address17_Low */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRLO:32;                                  /* [31:0] */
    } BIT;
  } MAC_Address17_Low;
  char                     wk_0810[0x07F0];
  union                                            /* Offset=0x1000 : Bus_Mode */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SWR:1;                                      /* [0] */
      __I  unsigned long   DA:1;                                       /* [1] */
      __IO unsigned long   DSL:5;                                      /* [6:2] */
      __IO unsigned long   ATDS:1;                                     /* [7] */
      __IO unsigned long   PBL:6;                                      /* [13:8] */
      __I  unsigned long   PR:2;                                       /* [15:14] */
      __IO unsigned long   FB:1;                                       /* [16] */
      __IO unsigned long   RPBL:6;                                     /* [22:17] */
      __IO unsigned long   USP:1;                                      /* [23] */
      __IO unsigned long   PBLx8:1;                                    /* [24] */
      __IO unsigned long   AAL:1;                                      /* [25] */
      __I  unsigned long   MB:1;                                       /* [26] */
      __I  unsigned long   TXPR:1;                                     /* [27] */
      __I  unsigned long   PRWG:2;                                     /* [29:28] */
      __IO unsigned long   :1;                                         /* [30] */
      __I  unsigned long   RIB:1;                                      /* [31] */
    } BIT;
  } Bus_Mode;
  union                                            /* Offset=0x1004 : Transmit_Poll_Demand */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TPD:32;                                     /* [31:0] */
    } BIT;
  } Transmit_Poll_Demand;
  union                                            /* Offset=0x1008 : Receive_Poll_Demand */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RPD:32;                                     /* [31:0] */
    } BIT;
  } Receive_Poll_Demand;
  union                                            /* Offset=0x100C : Receive_Descriptor_List_Address */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                                         /* [1:0] */
      __IO unsigned long   RDESLA_32bit:30;                            /* [31:2] */
    } BIT;
  } Receive_Descriptor_List_Address;
  union                                            /* Offset=0x1010 : Transmit_Descriptor_List_Address */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                                         /* [1:0] */
      __IO unsigned long   TDESLA_32bit:30;                            /* [31:2] */
    } BIT;
  } Transmit_Descriptor_List_Address;
  union                                            /* Offset=0x1014 : Status */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TI:1;                                       /* [0] */
      __IO unsigned long   TPS:1;                                      /* [1] */
      __IO unsigned long   TU:1;                                       /* [2] */
      __IO unsigned long   TJT:1;                                      /* [3] */
      __IO unsigned long   OVF:1;                                      /* [4] */
      __IO unsigned long   UNF:1;                                      /* [5] */
      __IO unsigned long   RI:1;                                       /* [6] */
      __IO unsigned long   RU:1;                                       /* [7] */
      __IO unsigned long   RPS:1;                                      /* [8] */
      __IO unsigned long   RWT:1;                                      /* [9] */
      __IO unsigned long   ETI:1;                                      /* [10] */
      __IO unsigned long   :2;                                         /* [12:11] */
      __IO unsigned long   FBI:1;                                      /* [13] */
      __IO unsigned long   ERI:1;                                      /* [14] */
      __IO unsigned long   AIS:1;                                      /* [15] */
      __IO unsigned long   NIS:1;                                      /* [16] */
      __I  unsigned long   RS:3;                                       /* [19:17] */
      __I  unsigned long   TS:3;                                       /* [22:20] */
      __I  unsigned long   EB:3;                                       /* [25:23] */
      __IO unsigned long   :1;                                         /* [26] */
      __I  unsigned long   GMI:1;                                      /* [27] */
      __I  unsigned long   GPI:1;                                      /* [28] */
      __I  unsigned long   TTI:1;                                      /* [29] */
      __I  unsigned long   GLPII:1;                                    /* [30] */
    } BIT;
  } Status;
  union                                            /* Offset=0x1018 : Operation_Mode */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                                         /* [0] */
      __IO unsigned long   SR:1;                                       /* [1] */
      __IO unsigned long   OSF:1;                                      /* [2] */
      __IO unsigned long   RTC:2;                                      /* [4:3] */
      __IO unsigned long   DGF:1;                                      /* [5] */
      __IO unsigned long   FUF:1;                                      /* [6] */
      __IO unsigned long   FEF:1;                                      /* [7] */
      __IO unsigned long   EFC:1;                                      /* [8] */
      __IO unsigned long   RFA:2;                                      /* [10:9] */
      __IO unsigned long   RFD:2;                                      /* [12:11] */
      __IO unsigned long   ST:1;                                       /* [13] */
      __IO unsigned long   TTC:3;                                      /* [16:14] */
      __IO unsigned long   :3;                                         /* [19:17] */
      __IO unsigned long   FTF:1;                                      /* [20] */
      __IO unsigned long   TSF:1;                                      /* [21] */
      __I  unsigned long   RFD_2:1;                                    /* [22] */
      __IO unsigned long   :2;                                         /* [24:23] */
      __IO unsigned long   RSF:1;                                      /* [25] */
      __IO unsigned long   DT:1;                                       /* [26] */
      __IO unsigned long   :5;                                         /* [31:27] */
    } BIT;
  } Operation_Mode;
  union                                            /* Offset=0x101C : Interrupt_Enable */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   TIE:1;                                      /* [0] */
      __IO unsigned long   TSE:1;                                      /* [1] */
      __IO unsigned long   TUE:1;                                      /* [2] */
      __IO unsigned long   TJE:1;                                      /* [3] */
      __IO unsigned long   OVE:1;                                      /* [4] */
      __IO unsigned long   UNE:1;                                      /* [5] */
      __IO unsigned long   RIE:1;                                      /* [6] */
      __IO unsigned long   RUE:1;                                      /* [7] */
      __IO unsigned long   RSE:1;                                      /* [8] */
      __IO unsigned long   RWE:1;                                      /* [9] */
      __IO unsigned long   ETE:1;                                      /* [10] */
      __IO unsigned long   :2;                                         /* [12:11] */
      __IO unsigned long   FBE:1;                                      /* [13] */
      __IO unsigned long   ERE:1;                                      /* [14] */
      __IO unsigned long   AIE:1;                                      /* [15] */
      __IO unsigned long   NIE:1;                                      /* [16] */
      __IO unsigned long   :15;                                        /* [31:17] */
    } BIT;
  } Interrupt_Enable;
  union                                            /* Offset=0x1020 : Missed_Frame_And_Buffer_Overflow_Counter */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MISFRMCNT:16;                               /* [15:0] */
      __I  unsigned long   MISCNTOVF:1;                                /* [16] */
      __I  unsigned long   OVFFRMCNT:11;                               /* [27:17] */
      __I  unsigned long   OVFCNTOVF:1;                                /* [28] */
      __I  unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } Missed_Frame_And_Buffer_Overflow_Counter;
  union                                            /* Offset=0x1024 : Receive_Interrupt_Watchdog_Timer */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   RIWT:8;                                     /* [7:0] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } Receive_Interrupt_Watchdog_Timer;
  union                                            /* Offset=0x1028 : AXI_Bus_Mode */
  {
    __IO unsigned long     LONG;
    struct
    {
      __I  unsigned long   UNDEF:1;                                    /* [0] */
      __IO unsigned long   BLEN4:1;                                    /* [1] */
      __IO unsigned long   BLEN8:1;                                    /* [2] */
      __IO unsigned long   BLEN16:1;                                   /* [3] */
      __IO unsigned long   :8;                                         /* [11:4] */
      __I  unsigned long   AXI_AAL:1;                                  /* [12] */
      __IO unsigned long   ONEKBBE:1;                                  /* [13] */
      __IO unsigned long   :2;                                         /* [15:14] */
      __IO unsigned long   RD_OSR_LMT:2;                               /* [17:16] */
      __IO unsigned long   :2;                                         /* [19:18] */
      __IO unsigned long   WR_OSR_LMT:2;                               /* [21:20] */
      __IO unsigned long   :8;                                         /* [29:22] */
      __IO unsigned long   LPI_XIT_FRM:1;                              /* [30] */
      __IO unsigned long   EN_LPI:1;                                   /* [31] */
    } BIT;
  } AXI_Bus_Mode;
  union                                            /* Offset=0x102C : AXI_Status */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   AXWHSTS:1;                                  /* [0] */
      __I  unsigned long   AXIRDSTS:1;                                 /* [1] */
      __I  unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } AXI_Status;
  char                     wk_1030[0x0018];
  union                                            /* Offset=0x1048 : Current_Host_Transmit_Descriptor */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CURTDESAPTR:32;                             /* [31:0] */
    } BIT;
  } Current_Host_Transmit_Descriptor;
  union                                            /* Offset=0x104C : Current_Host_Receive_Descriptor */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CURRDESAPTR:32;                             /* [31:0] */
    } BIT;
  } Current_Host_Receive_Descriptor;
  union                                            /* Offset=0x1050 : Current_Host_Transmit_Buffer_Address */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CURTBUFAPTR:32;                             /* [31:0] */
    } BIT;
  } Current_Host_Transmit_Buffer_Address;
  union                                            /* Offset=0x1054 : Current_Host_Receive_Buffer_Address */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   CURRBUFAPTR:32;                             /* [31:0] */
    } BIT;
  } Current_Host_Receive_Buffer_Address;
  union                                            /* Offset=0x1058 : HW_Feature */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MIISEL:1;                                   /* [0] */
      __I  unsigned long   GMIISEL:1;                                  /* [1] */
      __I  unsigned long   HDSEL:1;                                    /* [2] */
      __I  unsigned long   EXTHASHEN:1;                                /* [3] */
      __I  unsigned long   HASHSEL:1;                                  /* [4] */
      __I  unsigned long   ADDMACADRSEL:1;                             /* [5] */
      __I  unsigned long   :1;                                         /* [6] */
      __I  unsigned long   L3L4FLTREN:1;                               /* [7] */
      __I  unsigned long   SMASEL:1;                                   /* [8] */
      __I  unsigned long   RWKSEL:1;                                   /* [9] */
      __I  unsigned long   MGKSEL:1;                                   /* [10] */
      __I  unsigned long   MMCSEL:1;                                   /* [11] */
      __I  unsigned long   TSVER1SEL:1;                                /* [12] */
      __I  unsigned long   TSVER2SEL:1;                                /* [13] */
      __I  unsigned long   EEESEL:1;                                   /* [14] */
      __I  unsigned long   AVSEL:1;                                    /* [15] */
      __I  unsigned long   TXCOESEL:1;                                 /* [16] */
      __I  unsigned long   RXTYP1COE:1;                                /* [17] */
      __I  unsigned long   RXTYP2COE:1;                                /* [18] */
      __I  unsigned long   RXFIFOSIZE:1;                               /* [19] */
      __I  unsigned long   RXCHCNT:2;                                  /* [21:20] */
      __I  unsigned long   TXCHCNT:2;                                  /* [23:22] */
      __I  unsigned long   ENHDESSEL:1;                                /* [24] */
      __I  unsigned long   INTTSEN:1;                                  /* [25] */
      __I  unsigned long   FLEXIPPSEN:1;                               /* [26] */
      __I  unsigned long   SAVLANINS:1;                                /* [27] */
      __I  unsigned long   ACTPHYIF:3;                                 /* [30:28] */
    } BIT;
  } HW_Feature;
} GMAC1_Type;
#endif  /* End of __GMAC1_SFR__DEFINE_HEADER__ */
