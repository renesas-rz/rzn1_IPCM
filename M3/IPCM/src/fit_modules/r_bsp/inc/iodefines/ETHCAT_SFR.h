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
 **       for RZN1 ETHCAT
 **
 **       revision 0.30 (16.January.2018)
 **
 **********************************************************************************************************************/
#ifndef __ETHCAT_SFR__DEFINE_HEADER__
#define __ETHCAT_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : ETHCAT
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : TYPE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   TYPE:8;                                     /* [7:0] */
    } BIT;
  } TYPE;
  union                                            /* Offset=0x0001 : REVISION */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   REV:8;                                      /* [7:0] */
    } BIT;
  } REVISION;
  union                                            /* Offset=0x0002 : BUILD */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  BUILD:16;                                   /* [15:0] */
    } BIT;
  } BUILD;
  union                                            /* Offset=0x0004 : FMMU_NUM */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   NUMFMMU:8;                                  /* [7:0] */
    } BIT;
  } FMMU_NUM;
  union                                            /* Offset=0x0005 : SYNC_MANAGER */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   NUMSYNC:8;                                  /* [7:0] */
    } BIT;
  } SYNC_MANAGER;
  union                                            /* Offset=0x0006 : RAM_SIZE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   RAMSIZE:8;                                  /* [7:0] */
    } BIT;
  } RAM_SIZE;
  union                                            /* Offset=0x0007 : PORT_DESC */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   P0:2;                                       /* [1:0] */
      __I  unsigned char   P1:2;                                       /* [3:2] */
      __I  unsigned char   P2:2;                                       /* [5:4] */
      __I  unsigned char   P3:2;                                       /* [7:6] */
    } BIT;
  } PORT_DESC;
  union                                            /* Offset=0x0008 : FEATURE */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  FMMU:1;                                     /* [0] */
      __I  unsigned short  :1;                                         /* [1] */
      __I  unsigned short  DC:1;                                       /* [2] */
      __I  unsigned short  DCWID:1;                                    /* [3] */
      __I  unsigned short  :2;                                         /* [5:4] */
      __I  unsigned short  LINKDECMII:1;                               /* [6] */
      __I  unsigned short  FCS:1;                                      /* [7] */
      __I  unsigned short  DCSYNC:1;                                   /* [8] */
      __I  unsigned short  LRW:1;                                      /* [9] */
      __I  unsigned short  RWSUPP:1;                                   /* [10] */
      __I  unsigned short  FSCONFIG:1;                                 /* [11] */
      __I  unsigned short  :4;                                         /* [15:12] */
    } BIT;
  } FEATURE;
  char                     wk_000A[0x0006];
  union                                            /* Offset=0x0010 : STATION_ADR */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  NODADDR:16;                                 /* [15:0] */
    } BIT;
  } STATION_ADR;
  union                                            /* Offset=0x0012 : STATION_ALIAS */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  NODALIADDR:16;                              /* [15:0] */
    } BIT;
  } STATION_ALIAS;
  char                     wk_0014[0x000C];
  union                                            /* Offset=0x0020 : WR_REG_ENABLE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ENABLE:1;                                   /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } WR_REG_ENABLE;
  union                                            /* Offset=0x0021 : WR_REG_PROTECT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PROTECT:1;                                  /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } WR_REG_PROTECT;
  char                     wk_0022[0x000E];
  union                                            /* Offset=0x0030 : ESC_WR_ENABLE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ENABLE:1;                                   /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } ESC_WR_ENABLE;
  union                                            /* Offset=0x0031 : ESC_WR_PROTECT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PROTECT:1;                                  /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } ESC_WR_PROTECT;
  char                     wk_0032[0x000E];
  union                                            /* Offset=0x0040 : ESC_RESET_ECAT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   RESET_ECAT:8;                               /* [7:0] */
    } BIT;
  } ESC_RESET_ECAT;
  union                                            /* Offset=0x0041 : ESC_RESET_PDI */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   RESET_PDI:8;                                /* [7:0] */
    } BIT;
  } ESC_RESET_PDI;
  char                     wk_0042[0x00BE];
  union                                            /* Offset=0x0100 : ESC_DL_CONTROL */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   FWDRULE:1;                                  /* [0] */
      __I  unsigned long   TEMPUSE:1;                                  /* [1] */
      __I  unsigned long   :6;                                         /* [7:2] */
      __I  unsigned long   LP0:2;                                      /* [9:8] */
      __I  unsigned long   LP1:2;                                      /* [11:10] */
      __I  unsigned long   LP2:2;                                      /* [13:12] */
      __I  unsigned long   LP3:2;                                      /* [15:14] */
      __I  unsigned long   RXFIFO:3;                                   /* [18:16] */
      __I  unsigned long   :5;                                         /* [23:19] */
      __I  unsigned long   STAALIAS:1;                                 /* [24] */
      __I  unsigned long   :7;                                         /* [31:25] */
    } BIT;
  } ESC_DL_CONTROL;
  char                     wk_0104[0x0004];
  union                                            /* Offset=0x0108 : PHYSICAL_RW_OFFSET */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  RWOFFSET:16;                                /* [15:0] */
    } BIT;
  } PHYSICAL_RW_OFFSET;
  char                     wk_010A[0x0006];
  union                                            /* Offset=0x0110 : ESC_DL_STATUS */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  PDIOPE:1;                                   /* [0] */
      __I  unsigned short  PDIWDST:1;                                  /* [1] */
      __I  unsigned short  ENHLINKD:1;                                 /* [2] */
      __I  unsigned short  :1;                                         /* [3] */
      __I  unsigned short  PHYP0:1;                                    /* [4] */
      __I  unsigned short  PHYP1:1;                                    /* [5] */
      __I  unsigned short  PHYP2:1;                                    /* [6] */
      __I  unsigned short  PHYP3:1;                                    /* [7] */
      __I  unsigned short  LP0:1;                                      /* [8] */
      __I  unsigned short  COMP0:1;                                    /* [9] */
      __I  unsigned short  LP1:1;                                      /* [10] */
      __I  unsigned short  COMP1:1;                                    /* [11] */
      __I  unsigned short  LP2:1;                                      /* [12] */
      __I  unsigned short  COMP2:1;                                    /* [13] */
      __I  unsigned short  LP3:1;                                      /* [14] */
      __I  unsigned short  COMP3:1;                                    /* [15] */
    } BIT;
  } ESC_DL_STATUS;
  char                     wk_0112[0x000E];
  union                                            /* Offset=0x0120 : AL_CONTROL */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  INISTATE:4;                                 /* [3:0] */
      __I  unsigned short  ERRINDACK:1;                                /* [4] */
      __I  unsigned short  DEVICEID:1;                                 /* [5] */
      __I  unsigned short  :10;                                        /* [15:6] */
    } BIT;
  } AL_CONTROL;
  char                     wk_0122[0x000E];
  union                                            /* Offset=0x0130 : AL_STATUS */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  ACTSTATE:4;                                 /* [3:0] */
      __IO unsigned short  ERR:1;                                      /* [4] */
      __IO unsigned short  DEVICEID:1;                                 /* [5] */
      __IO unsigned short  :10;                                        /* [15:6] */
    } BIT;
  } AL_STATUS;
  char                     wk_0132[0x0002];
  union                                            /* Offset=0x0134 : AL_STATUS_CODE */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  STATUSCODE:16;                              /* [15:0] */
    } BIT;
  } AL_STATUS_CODE;
  char                     wk_0136[0x0002];
  union                                            /* Offset=0x0138 : RUN_LED_OVERRIDE */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   LEDCODE:4;                                  /* [3:0] */
      __IO unsigned char   OVERRIDEEN:1;                               /* [4] */
      __IO unsigned char   :3;                                         /* [7:5] */
    } BIT;
  } RUN_LED_OVERRIDE;
  union                                            /* Offset=0x0139 : ERR_LED_OVERRIDE */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   LEDCODE:4;                                  /* [3:0] */
      __IO unsigned char   OVERRIDEEN:1;                               /* [4] */
      __IO unsigned char   :3;                                         /* [7:5] */
    } BIT;
  } ERR_LED_OVERRIDE;
  char                     wk_013A[0x0006];
  union                                            /* Offset=0x0140 : PDI_CONTROL */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PDI:8;                                      /* [7:0] */
    } BIT;
  } PDI_CONTROL;
  union                                            /* Offset=0x0141 : ESC_CONFIG */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   DEVEMU:1;                                   /* [0] */
      __I  unsigned char   ENLALLP:1;                                  /* [1] */
      __I  unsigned char   DCSYNC:1;                                   /* [2] */
      __I  unsigned char   DCLATCH:1;                                  /* [3] */
      __I  unsigned char   ENLP0:1;                                    /* [4] */
      __I  unsigned char   ENLP1:1;                                    /* [5] */
      __I  unsigned char   ENLP2:1;                                    /* [6] */
      __I  unsigned char   ENLP3:1;                                    /* [7] */
    } BIT;
  } ESC_CONFIG;
  char                     wk_0142[0x000E];
  union                                            /* Offset=0x0150 : PDI_CONFIG */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ONCHIPBUSCLK:5;                             /* [4:0] */
      __I  unsigned char   ONCHIPBUS:3;                                /* [7:5] */
    } BIT;
  } PDI_CONFIG;
  union                                            /* Offset=0x0151 : SYNC_LATCH_CONFIG */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SYNC0OUT:2;                                 /* [1:0] */
      __I  unsigned char   SYNCLAT0:1;                                 /* [2] */
      __I  unsigned char   SYNC0MAP:1;                                 /* [3] */
      __I  unsigned char   SYNC1OUT:2;                                 /* [5:4] */
      __I  unsigned char   SYNCLAT1:1;                                 /* [6] */
      __I  unsigned char   SYNC1MAP:1;                                 /* [7] */
    } BIT;
  } SYNC_LATCH_CONFIG;
  union                                            /* Offset=0x0152 : EXT_PDI_CONFIG */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  DATABUSWID:2;                               /* [1:0] */
      __I  unsigned short  :14;                                        /* [15:2] */
    } BIT;
  } EXT_PDI_CONFIG;
  char                     wk_0154[0x00AC];
  union                                            /* Offset=0x0200 : ECAT_EVENT_MASK */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  ECATEVMASK:16;                              /* [15:0] */
    } BIT;
  } ECAT_EVENT_MASK;
  char                     wk_0202[0x0002];
  union                                            /* Offset=0x0204 : AL_EVENT_MASK */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ALEVMASK:32;                                /* [31:0] */
    } BIT;
  } AL_EVENT_MASK;
  char                     wk_0208[0x0008];
  union                                            /* Offset=0x0210 : ECAT_EVENT_REQ */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  DCLATCH:1;                                  /* [0] */
      __I  unsigned short  :1;                                         /* [1] */
      __I  unsigned short  DLSTA:1;                                    /* [2] */
      __I  unsigned short  ALSTA:1;                                    /* [3] */
      __I  unsigned short  SMSTA0:1;                                   /* [4] */
      __I  unsigned short  SMSTA1:1;                                   /* [5] */
      __I  unsigned short  SMSTA2:1;                                   /* [6] */
      __I  unsigned short  SMSTA3:1;                                   /* [7] */
      __I  unsigned short  SMSTA4:1;                                   /* [8] */
      __I  unsigned short  SMSTA5:1;                                   /* [9] */
      __I  unsigned short  SMSTA6:1;                                   /* [10] */
      __I  unsigned short  SMSTA7:1;                                   /* [11] */
      __I  unsigned short  :4;                                         /* [15:12] */
    } BIT;
  } ECAT_EVENT_REQ;
  char                     wk_0212[0x000E];
  union                                            /* Offset=0x0220 : AL_EVENT_REQ */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ALCTRL:1;                                   /* [0] */
      __I  unsigned long   DCLATCH:1;                                  /* [1] */
      __I  unsigned long   DCSYNC0STA:1;                               /* [2] */
      __I  unsigned long   DCSYNC1STA:1;                               /* [3] */
      __I  unsigned long   SYNCACT:1;                                  /* [4] */
      __I  unsigned long   :1;                                         /* [5] */
      __I  unsigned long   WDPD:1;                                     /* [6] */
      __I  unsigned long   :1;                                         /* [7] */
      __I  unsigned long   SMINT0:1;                                   /* [8] */
      __I  unsigned long   SMINT1:1;                                   /* [9] */
      __I  unsigned long   SMINT2:1;                                   /* [10] */
      __I  unsigned long   SMINT3:1;                                   /* [11] */
      __I  unsigned long   SMINT4:1;                                   /* [12] */
      __I  unsigned long   SMINT5:1;                                   /* [13] */
      __I  unsigned long   SMINT6:1;                                   /* [14] */
      __I  unsigned long   SMINT7:1;                                   /* [15] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } AL_EVENT_REQ;
  char                     wk_0224[0x00DC];
  union                                            /* Offset=0x0300 : RX_ERR_COUNT0 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  INVFRMCNT:8;                                /* [7:0] */
      __I  unsigned short  RXERRCNT:8;                                 /* [15:8] */
    } BIT;
  } RX_ERR_COUNT0;
  union                                            /* Offset=0x0302 : RX_ERR_COUNT1 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  INVFRMCNT:8;                                /* [7:0] */
      __I  unsigned short  RXERRCNT:8;                                 /* [15:8] */
    } BIT;
  } RX_ERR_COUNT1;
  union                                            /* Offset=0x0304 : RX_ERR_COUNT2 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  INVFRMCNT:8;                                /* [7:0] */
      __I  unsigned short  RXERRCNT:8;                                 /* [15:8] */
    } BIT;
  } RX_ERR_COUNT2;
  char                     wk_0306[0x0002];
  union                                            /* Offset=0x0308 : FWD_RX_ERR_COUNT0 */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   FWDERRCNT:8;                                /* [7:0] */
    } BIT;
  } FWD_RX_ERR_COUNT0;
  union                                            /* Offset=0x0309 : FWD_RX_ERR_COUNT1 */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   FWDERRCNT:8;                                /* [7:0] */
    } BIT;
  } FWD_RX_ERR_COUNT1;
  union                                            /* Offset=0x030A : FWD_RX_ERR_COUNT2 */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   FWDERRCNT:8;                                /* [7:0] */
    } BIT;
  } FWD_RX_ERR_COUNT2;
  char                     wk_030B[0x0001];
  union                                            /* Offset=0x030C : ECAT_PROC_ERR_COUNT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   EPUERRCNT:8;                                /* [7:0] */
    } BIT;
  } ECAT_PROC_ERR_COUNT;
  union                                            /* Offset=0x030D : PDI_ERR_COUNT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PDIERRCNT:8;                                /* [7:0] */
    } BIT;
  } PDI_ERR_COUNT;
  char                     wk_030E[0x0002];
  union                                            /* Offset=0x0310 : LOST_LINK_COUNT0 */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LOSTLINKCNT:8;                              /* [7:0] */
    } BIT;
  } LOST_LINK_COUNT0;
  union                                            /* Offset=0x0311 : LOST_LINK_COUNT1 */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LOSTLINKCNT:8;                              /* [7:0] */
    } BIT;
  } LOST_LINK_COUNT1;
  union                                            /* Offset=0x0312 : LOST_LINK_COUNT2 */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LOSTLINKCNT:8;                              /* [7:0] */
    } BIT;
  } LOST_LINK_COUNT2;
  char                     wk_0313[0x00ED];
  union                                            /* Offset=0x0400 : WD_DIVIDE */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  WDDIV:16;                                   /* [15:0] */
    } BIT;
  } WD_DIVIDE;
  char                     wk_0402[0x000E];
  union                                            /* Offset=0x0410 : WDT_PDI */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  WDTIMPDI:16;                                /* [15:0] */
    } BIT;
  } WDT_PDI;
  char                     wk_0412[0x000E];
  union                                            /* Offset=0x0420 : WDT_DATA */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  WDTIMPD:16;                                 /* [15:0] */
    } BIT;
  } WDT_DATA;
  char                     wk_0422[0x001E];
  union                                            /* Offset=0x0440 : WDS_DATA */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  WDSTAPD:1;                                  /* [0] */
      __I  unsigned short  :15;                                        /* [15:1] */
    } BIT;
  } WDS_DATA;
  union                                            /* Offset=0x0442 : WDC_DATA */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   WDCNTPD:8;                                  /* [7:0] */
    } BIT;
  } WDC_DATA;
  union                                            /* Offset=0x0443 : WDC_PDI */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   WDCNTPDI:8;                                 /* [7:0] */
    } BIT;
  } WDC_PDI;
  char                     wk_0444[0x00BC];
  union                                            /* Offset=0x0500 : EEP_CONF */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   CTRLPDI:1;                                  /* [0] */
      __I  unsigned char   FORCEECAT:1;                                /* [1] */
      __I  unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } EEP_CONF;
  union                                            /* Offset=0x0501 : EEP_STATE */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   PDIACCEES:1;                                /* [0] */
      __IO unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } EEP_STATE;
  union                                            /* Offset=0x0502 : EEP_CONT_STAT */
  {
    __IO unsigned short    WORD;
    struct
    {
      __I  unsigned short  ECATWREN:1;                                 /* [0] */
      __IO unsigned short  :5;                                         /* [5:1] */
      __I  unsigned short  READBYTE:1;                                 /* [6] */
      __I  unsigned short  PROMSIZE:1;                                 /* [7] */
      __IO unsigned short  COMMAND:3;                                  /* [10:8] */
      __I  unsigned short  CKSUMERR:1;                                 /* [11] */
      __I  unsigned short  LOADSTA:1;                                  /* [12] */
      __I  unsigned short  ACKCMDERR:1;                                /* [13] */
      __I  unsigned short  WRENERR:1;                                  /* [14] */
      __I  unsigned short  BUSY:1;                                     /* [15] */
    } BIT;
  } EEP_CONT_STAT;
  union                                            /* Offset=0x0504 : EEP_ADR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ADDRESS:32;                                 /* [31:0] */
    } BIT;
  } EEP_ADR;
  union                                            /* Offset=0x0508 : EEP_DATA */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   LODATA:16;                                  /* [15:0] */
      __I  unsigned long   HIDATA:16;                                  /* [31:16] */
    } BIT;
  } EEP_DATA;
  char                     wk_050C[0x0004];
  union                                            /* Offset=0x0510 : MII_CONT_STAT */
  {
    __IO unsigned short    WORD;
    struct
    {
      __I  unsigned short  WREN:1;                                     /* [0] */
      __I  unsigned short  PDICTRL:1;                                  /* [1] */
      __I  unsigned short  MILINK:1;                                   /* [2] */
      __I  unsigned short  PHYOFFSET:5;                                /* [7:3] */
      __IO unsigned short  COMMAND:2;                                  /* [9:8] */
      __IO unsigned short  :3;                                         /* [12:10] */
      __IO unsigned short  READERR:1;                                  /* [13] */
      __I  unsigned short  CMDERR:1;                                   /* [14] */
      __I  unsigned short  BUSY:1;                                     /* [15] */
    } BIT;
  } MII_CONT_STAT;
  union                                            /* Offset=0x0512 : PHY_ADR */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   PHYADDR:5;                                  /* [4:0] */
      __IO unsigned char   :3;                                         /* [7:5] */
    } BIT;
  } PHY_ADR;
  union                                            /* Offset=0x0513 : PHY_REG_ADR */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   PHYREGADDR:5;                               /* [4:0] */
      __IO unsigned char   :3;                                         /* [7:5] */
    } BIT;
  } PHY_REG_ADR;
  union                                            /* Offset=0x0514 : PHY_DATA */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  PHYREGDATA:16;                              /* [15:0] */
    } BIT;
  } PHY_DATA;
  union                                            /* Offset=0x0516 : MII_ECAT_ACS_STAT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ACSMII:1;                                   /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } MII_ECAT_ACS_STAT;
  union                                            /* Offset=0x0517 : MII_PDI_ACS_STAT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   ACSMII:1;                                   /* [0] */
      __I  unsigned char   FORPDI:1;                                   /* [1] */
      __IO unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } MII_PDI_ACS_STAT;
  union                                            /* Offset=0x0518 : PHY_STATUS0 */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PHYLINKSTA:1;                               /* [0] */
      __I  unsigned char   LINKSTA:1;                                  /* [1] */
      __I  unsigned char   LINKSTAERR:1;                               /* [2] */
      __IO unsigned char   READERR:1;                                  /* [3] */
      __I  unsigned char   LINKPARTERR:1;                              /* [4] */
      __IO unsigned char   PHYCONFIG:1;                                /* [5] */
      __IO unsigned char   :2;                                         /* [7:6] */
    } BIT;
  } PHY_STATUS0;
  union                                            /* Offset=0x0519 : PHY_STATUS1 */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PHYLINKSTA:1;                               /* [0] */
      __I  unsigned char   LINKSTA:1;                                  /* [1] */
      __I  unsigned char   LINKSTAERR:1;                               /* [2] */
      __IO unsigned char   READERR:1;                                  /* [3] */
      __I  unsigned char   LINKPARTERR:1;                              /* [4] */
      __IO unsigned char   PHYCONFIG:1;                                /* [5] */
      __IO unsigned char   :2;                                         /* [7:6] */
    } BIT;
  } PHY_STATUS1;
  union                                            /* Offset=0x051A : PHY_STATUS2 */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PHYLINKSTA:1;                               /* [0] */
      __I  unsigned char   LINKSTA:1;                                  /* [1] */
      __I  unsigned char   LINKSTAERR:1;                               /* [2] */
      __IO unsigned char   READERR:1;                                  /* [3] */
      __I  unsigned char   LINKPARTERR:1;                              /* [4] */
      __IO unsigned char   PHYCONFIG:1;                                /* [5] */
      __IO unsigned char   :2;                                         /* [7:6] */
    } BIT;
  } PHY_STATUS2;
  char                     wk_051B[0x00E5];
  union                                            /* Offset=0x0600 : FMMU0_L_START_ADR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   LSTAADR:32;                                 /* [31:0] */
    } BIT;
  } FMMU0_L_START_ADR;
  union                                            /* Offset=0x0604 : FMMU0_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  FMMULEN:16;                                 /* [15:0] */
    } BIT;
  } FMMU0_LEN;
  union                                            /* Offset=0x0606 : FMMU0_L_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTABIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU0_L_START_BIT;
  union                                            /* Offset=0x0607 : FMMU0_L_STOP_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTPBIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU0_L_STOP_BIT;
  union                                            /* Offset=0x0608 : FMMU0_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  PHYSTAADR:16;                               /* [15:0] */
    } BIT;
  } FMMU0_P_START_ADR;
  union                                            /* Offset=0x060A : FMMU0_P_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PHYSTABIT:3;                                /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU0_P_START_BIT;
  union                                            /* Offset=0x060B : FMMU0_TYPE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   READ:1;                                     /* [0] */
      __I  unsigned char   WRITE:1;                                    /* [1] */
      __I  unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } FMMU0_TYPE;
  union                                            /* Offset=0x060C : FMMU0_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ACTIVATE:1;                                 /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } FMMU0_ACT;
  char                     wk_060D[0x0003];
  union                                            /* Offset=0x0610 : FMMU1_L_START_ADR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   LSTAADR:32;                                 /* [31:0] */
    } BIT;
  } FMMU1_L_START_ADR;
  union                                            /* Offset=0x0614 : FMMU1_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  FMMULEN:16;                                 /* [15:0] */
    } BIT;
  } FMMU1_LEN;
  union                                            /* Offset=0x0616 : FMMU1_L_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTABIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU1_L_START_BIT;
  union                                            /* Offset=0x0617 : FMMU1_L_STOP_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTPBIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU1_L_STOP_BIT;
  union                                            /* Offset=0x0618 : FMMU1_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  PHYSTAADR:16;                               /* [15:0] */
    } BIT;
  } FMMU1_P_START_ADR;
  union                                            /* Offset=0x061A : FMMU1_P_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PHYSTABIT:3;                                /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU1_P_START_BIT;
  union                                            /* Offset=0x061B : FMMU1_TYPE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   READ:1;                                     /* [0] */
      __I  unsigned char   WRITE:1;                                    /* [1] */
      __I  unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } FMMU1_TYPE;
  union                                            /* Offset=0x061C : FMMU1_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ACTIVATE:1;                                 /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } FMMU1_ACT;
  char                     wk_061D[0x0003];
  union                                            /* Offset=0x0620 : FMMU2_L_START_ADR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   LSTAADR:32;                                 /* [31:0] */
    } BIT;
  } FMMU2_L_START_ADR;
  union                                            /* Offset=0x0624 : FMMU2_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  FMMULEN:16;                                 /* [15:0] */
    } BIT;
  } FMMU2_LEN;
  union                                            /* Offset=0x0626 : FMMU2_L_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTABIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU2_L_START_BIT;
  union                                            /* Offset=0x0627 : FMMU2_L_STOP_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTPBIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU2_L_STOP_BIT;
  union                                            /* Offset=0x0628 : FMMU2_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  PHYSTAADR:16;                               /* [15:0] */
    } BIT;
  } FMMU2_P_START_ADR;
  union                                            /* Offset=0x062A : FMMU2_P_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PHYSTABIT:3;                                /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU2_P_START_BIT;
  union                                            /* Offset=0x062B : FMMU2_TYPE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   READ:1;                                     /* [0] */
      __I  unsigned char   WRITE:1;                                    /* [1] */
      __I  unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } FMMU2_TYPE;
  union                                            /* Offset=0x062C : FMMU2_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ACTIVATE:1;                                 /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } FMMU2_ACT;
  char                     wk_062D[0x0003];
  union                                            /* Offset=0x0630 : FMMU3_L_START_ADR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   LSTAADR:32;                                 /* [31:0] */
    } BIT;
  } FMMU3_L_START_ADR;
  union                                            /* Offset=0x0634 : FMMU3_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  FMMULEN:16;                                 /* [15:0] */
    } BIT;
  } FMMU3_LEN;
  union                                            /* Offset=0x0636 : FMMU3_L_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTABIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU3_L_START_BIT;
  union                                            /* Offset=0x0637 : FMMU3_L_STOP_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTPBIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU3_L_STOP_BIT;
  union                                            /* Offset=0x0638 : FMMU3_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  PHYSTAADR:16;                               /* [15:0] */
    } BIT;
  } FMMU3_P_START_ADR;
  union                                            /* Offset=0x063A : FMMU3_P_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PHYSTABIT:3;                                /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU3_P_START_BIT;
  union                                            /* Offset=0x063B : FMMU3_TYPE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   READ:1;                                     /* [0] */
      __I  unsigned char   WRITE:1;                                    /* [1] */
      __I  unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } FMMU3_TYPE;
  union                                            /* Offset=0x063C : FMMU3_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ACTIVATE:1;                                 /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } FMMU3_ACT;
  char                     wk_063D[0x0003];
  union                                            /* Offset=0x0640 : FMMU4_L_START_ADR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   LSTAADR:32;                                 /* [31:0] */
    } BIT;
  } FMMU4_L_START_ADR;
  union                                            /* Offset=0x0644 : FMMU4_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  FMMULEN:16;                                 /* [15:0] */
    } BIT;
  } FMMU4_LEN;
  union                                            /* Offset=0x0646 : FMMU4_L_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTABIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU4_L_START_BIT;
  union                                            /* Offset=0x0647 : FMMU4_L_STOP_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTPBIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU4_L_STOP_BIT;
  union                                            /* Offset=0x0648 : FMMU4_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  PHYSTAADR:16;                               /* [15:0] */
    } BIT;
  } FMMU4_P_START_ADR;
  union                                            /* Offset=0x064A : FMMU4_P_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PHYSTABIT:3;                                /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU4_P_START_BIT;
  union                                            /* Offset=0x064B : FMMU4_TYPE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   READ:1;                                     /* [0] */
      __I  unsigned char   WRITE:1;                                    /* [1] */
      __I  unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } FMMU4_TYPE;
  union                                            /* Offset=0x064C : FMMU4_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ACTIVATE:1;                                 /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } FMMU4_ACT;
  char                     wk_064D[0x0003];
  union                                            /* Offset=0x0650 : FMMU5_L_START_ADR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   LSTAADR:32;                                 /* [31:0] */
    } BIT;
  } FMMU5_L_START_ADR;
  union                                            /* Offset=0x0654 : FMMU5_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  FMMULEN:16;                                 /* [15:0] */
    } BIT;
  } FMMU5_LEN;
  union                                            /* Offset=0x0656 : FMMU5_L_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTABIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU5_L_START_BIT;
  union                                            /* Offset=0x0657 : FMMU5_L_STOP_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTPBIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU5_L_STOP_BIT;
  union                                            /* Offset=0x0658 : FMMU5_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  PHYSTAADR:16;                               /* [15:0] */
    } BIT;
  } FMMU5_P_START_ADR;
  union                                            /* Offset=0x065A : FMMU5_P_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PHYSTABIT:3;                                /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU5_P_START_BIT;
  union                                            /* Offset=0x065B : FMMU5_TYPE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   READ:1;                                     /* [0] */
      __I  unsigned char   WRITE:1;                                    /* [1] */
      __I  unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } FMMU5_TYPE;
  union                                            /* Offset=0x065C : FMMU5_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ACTIVATE:1;                                 /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } FMMU5_ACT;
  char                     wk_065D[0x0003];
  union                                            /* Offset=0x0660 : FMMU6_L_START_ADR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   LSTAADR:32;                                 /* [31:0] */
    } BIT;
  } FMMU6_L_START_ADR;
  union                                            /* Offset=0x0664 : FMMU6_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  FMMULEN:16;                                 /* [15:0] */
    } BIT;
  } FMMU6_LEN;
  union                                            /* Offset=0x0666 : FMMU6_L_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTABIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU6_L_START_BIT;
  union                                            /* Offset=0x0667 : FMMU6_L_STOP_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTPBIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU6_L_STOP_BIT;
  union                                            /* Offset=0x0668 : FMMU6_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  PHYSTAADR:16;                               /* [15:0] */
    } BIT;
  } FMMU6_P_START_ADR;
  union                                            /* Offset=0x066A : FMMU6_P_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PHYSTABIT:3;                                /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU6_P_START_BIT;
  union                                            /* Offset=0x066B : FMMU6_TYPE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   READ:1;                                     /* [0] */
      __I  unsigned char   WRITE:1;                                    /* [1] */
      __I  unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } FMMU6_TYPE;
  union                                            /* Offset=0x066C : FMMU6_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ACTIVATE:1;                                 /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } FMMU6_ACT;
  char                     wk_066D[0x0003];
  union                                            /* Offset=0x0670 : FMMU7_L_START_ADR */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   LSTAADR:32;                                 /* [31:0] */
    } BIT;
  } FMMU7_L_START_ADR;
  union                                            /* Offset=0x0674 : FMMU7_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  FMMULEN:16;                                 /* [15:0] */
    } BIT;
  } FMMU7_LEN;
  union                                            /* Offset=0x0676 : FMMU7_L_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTABIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU7_L_START_BIT;
  union                                            /* Offset=0x0677 : FMMU7_L_STOP_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   LSTPBIT:3;                                  /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU7_L_STOP_BIT;
  union                                            /* Offset=0x0678 : FMMU7_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  PHYSTAADR:16;                               /* [15:0] */
    } BIT;
  } FMMU7_P_START_ADR;
  union                                            /* Offset=0x067A : FMMU7_P_START_BIT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   PHYSTABIT:3;                                /* [2:0] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } FMMU7_P_START_BIT;
  union                                            /* Offset=0x067B : FMMU7_TYPE */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   READ:1;                                     /* [0] */
      __I  unsigned char   WRITE:1;                                    /* [1] */
      __I  unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } FMMU7_TYPE;
  union                                            /* Offset=0x067C : FMMU7_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   ACTIVATE:1;                                 /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } FMMU7_ACT;
  char                     wk_067D[0x0183];
  union                                            /* Offset=0x0800 : SM0_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMSTAADDR:16;                               /* [15:0] */
    } BIT;
  } SM0_P_START_ADR;
  union                                            /* Offset=0x0802 : SM0_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMLEN:16;                                   /* [15:0] */
    } BIT;
  } SM0_LEN;
  union                                            /* Offset=0x0804 : SM0_CONTROL */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   OPEMODE:2;                                  /* [1:0] */
      __I  unsigned char   DIR:2;                                      /* [3:2] */
      __I  unsigned char   IRQECAT:1;                                  /* [4] */
      __I  unsigned char   IRQPDI:1;                                   /* [5] */
      __I  unsigned char   WDTRGEN:1;                                  /* [6] */
    } BIT;
  } SM0_CONTROL;
  union                                            /* Offset=0x0805 : SM0_STATUS */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   INTWR:1;                                    /* [0] */
      __I  unsigned char   INTRD:1;                                    /* [1] */
      __I  unsigned char   :1;                                         /* [2] */
      __I  unsigned char   MAILBOX:1;                                  /* [3] */
      __I  unsigned char   BUFFERED:2;                                 /* [5:4] */
      __I  unsigned char   RDBUF:1;                                    /* [6] */
      __I  unsigned char   WRBUF:1;                                    /* [7] */
    } BIT;
  } SM0_STATUS;
  union                                            /* Offset=0x0806 : SM0_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SMEN:1;                                     /* [0] */
      __I  unsigned char   REPEATREQ:1;                                /* [1] */
      __I  unsigned char   :4;                                         /* [5:2] */
      __I  unsigned char   LATCHECAT:1;                                /* [6] */
      __I  unsigned char   LATCHPDI:1;                                 /* [7] */
    } BIT;
  } SM0_ACT;
  union                                            /* Offset=0x0807 : SM0_PDI_CONT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   DEACTIVE:1;                                 /* [0] */
      __IO unsigned char   REPEATACK:1;                                /* [1] */
      __IO unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } SM0_PDI_CONT;
  union                                            /* Offset=0x0808 : SM1_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMSTAADDR:16;                               /* [15:0] */
    } BIT;
  } SM1_P_START_ADR;
  union                                            /* Offset=0x080A : SM1_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMLEN:16;                                   /* [15:0] */
    } BIT;
  } SM1_LEN;
  union                                            /* Offset=0x080C : SM1_CONTROL */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   OPEMODE:2;                                  /* [1:0] */
      __I  unsigned char   DIR:2;                                      /* [3:2] */
      __I  unsigned char   IRQECAT:1;                                  /* [4] */
      __I  unsigned char   IRQPDI:1;                                   /* [5] */
      __I  unsigned char   WDTRGEN:1;                                  /* [6] */
    } BIT;
  } SM1_CONTROL;
  union                                            /* Offset=0x080D : SM1_STATUS */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   INTWR:1;                                    /* [0] */
      __I  unsigned char   INTRD:1;                                    /* [1] */
      __I  unsigned char   :1;                                         /* [2] */
      __I  unsigned char   MAILBOX:1;                                  /* [3] */
      __I  unsigned char   BUFFERED:2;                                 /* [5:4] */
      __I  unsigned char   RDBUF:1;                                    /* [6] */
      __I  unsigned char   WRBUF:1;                                    /* [7] */
    } BIT;
  } SM1_STATUS;
  union                                            /* Offset=0x080E : SM1_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SMEN:1;                                     /* [0] */
      __I  unsigned char   REPEATREQ:1;                                /* [1] */
      __I  unsigned char   :4;                                         /* [5:2] */
      __I  unsigned char   LATCHECAT:1;                                /* [6] */
      __I  unsigned char   LATCHPDI:1;                                 /* [7] */
    } BIT;
  } SM1_ACT;
  union                                            /* Offset=0x080F : SM1_PDI_CONT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   DEACTIVE:1;                                 /* [0] */
      __IO unsigned char   REPEATACK:1;                                /* [1] */
      __IO unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } SM1_PDI_CONT;
  union                                            /* Offset=0x0810 : SM2_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMSTAADDR:16;                               /* [15:0] */
    } BIT;
  } SM2_P_START_ADR;
  union                                            /* Offset=0x0812 : SM2_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMLEN:16;                                   /* [15:0] */
    } BIT;
  } SM2_LEN;
  union                                            /* Offset=0x0814 : SM2_CONTROL */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   OPEMODE:2;                                  /* [1:0] */
      __I  unsigned char   DIR:2;                                      /* [3:2] */
      __I  unsigned char   IRQECAT:1;                                  /* [4] */
      __I  unsigned char   IRQPDI:1;                                   /* [5] */
      __I  unsigned char   WDTRGEN:1;                                  /* [6] */
    } BIT;
  } SM2_CONTROL;
  union                                            /* Offset=0x0815 : SM2_STATUS */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   INTWR:1;                                    /* [0] */
      __I  unsigned char   INTRD:1;                                    /* [1] */
      __I  unsigned char   :1;                                         /* [2] */
      __I  unsigned char   MAILBOX:1;                                  /* [3] */
      __I  unsigned char   BUFFERED:2;                                 /* [5:4] */
      __I  unsigned char   RDBUF:1;                                    /* [6] */
      __I  unsigned char   WRBUF:1;                                    /* [7] */
    } BIT;
  } SM2_STATUS;
  union                                            /* Offset=0x0816 : SM2_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SMEN:1;                                     /* [0] */
      __I  unsigned char   REPEATREQ:1;                                /* [1] */
      __I  unsigned char   :4;                                         /* [5:2] */
      __I  unsigned char   LATCHECAT:1;                                /* [6] */
      __I  unsigned char   LATCHPDI:1;                                 /* [7] */
    } BIT;
  } SM2_ACT;
  union                                            /* Offset=0x0817 : SM2_PDI_CONT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   DEACTIVE:1;                                 /* [0] */
      __IO unsigned char   REPEATACK:1;                                /* [1] */
      __IO unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } SM2_PDI_CONT;
  union                                            /* Offset=0x0818 : SM3_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMSTAADDR:16;                               /* [15:0] */
    } BIT;
  } SM3_P_START_ADR;
  union                                            /* Offset=0x081A : SM3_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMLEN:16;                                   /* [15:0] */
    } BIT;
  } SM3_LEN;
  union                                            /* Offset=0x081C : SM3_CONTROL */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   OPEMODE:2;                                  /* [1:0] */
      __I  unsigned char   DIR:2;                                      /* [3:2] */
      __I  unsigned char   IRQECAT:1;                                  /* [4] */
      __I  unsigned char   IRQPDI:1;                                   /* [5] */
      __I  unsigned char   WDTRGEN:1;                                  /* [6] */
    } BIT;
  } SM3_CONTROL;
  union                                            /* Offset=0x081D : SM3_STATUS */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   INTWR:1;                                    /* [0] */
      __I  unsigned char   INTRD:1;                                    /* [1] */
      __I  unsigned char   :1;                                         /* [2] */
      __I  unsigned char   MAILBOX:1;                                  /* [3] */
      __I  unsigned char   BUFFERED:2;                                 /* [5:4] */
      __I  unsigned char   RDBUF:1;                                    /* [6] */
      __I  unsigned char   WRBUF:1;                                    /* [7] */
    } BIT;
  } SM3_STATUS;
  union                                            /* Offset=0x081E : SM3_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SMEN:1;                                     /* [0] */
      __I  unsigned char   REPEATREQ:1;                                /* [1] */
      __I  unsigned char   :4;                                         /* [5:2] */
      __I  unsigned char   LATCHECAT:1;                                /* [6] */
      __I  unsigned char   LATCHPDI:1;                                 /* [7] */
    } BIT;
  } SM3_ACT;
  union                                            /* Offset=0x081F : SM3_PDI_CONT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   DEACTIVE:1;                                 /* [0] */
      __IO unsigned char   REPEATACK:1;                                /* [1] */
      __IO unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } SM3_PDI_CONT;
  union                                            /* Offset=0x0820 : SM4_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMSTAADDR:16;                               /* [15:0] */
    } BIT;
  } SM4_P_START_ADR;
  union                                            /* Offset=0x0822 : SM4_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMLEN:16;                                   /* [15:0] */
    } BIT;
  } SM4_LEN;
  union                                            /* Offset=0x0824 : SM4_CONTROL */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   OPEMODE:2;                                  /* [1:0] */
      __I  unsigned char   DIR:2;                                      /* [3:2] */
      __I  unsigned char   IRQECAT:1;                                  /* [4] */
      __I  unsigned char   IRQPDI:1;                                   /* [5] */
      __I  unsigned char   WDTRGEN:1;                                  /* [6] */
    } BIT;
  } SM4_CONTROL;
  union                                            /* Offset=0x0825 : SM4_STATUS */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   INTWR:1;                                    /* [0] */
      __I  unsigned char   INTRD:1;                                    /* [1] */
      __I  unsigned char   :1;                                         /* [2] */
      __I  unsigned char   MAILBOX:1;                                  /* [3] */
      __I  unsigned char   BUFFERED:2;                                 /* [5:4] */
      __I  unsigned char   RDBUF:1;                                    /* [6] */
      __I  unsigned char   WRBUF:1;                                    /* [7] */
    } BIT;
  } SM4_STATUS;
  union                                            /* Offset=0x0826 : SM4_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SMEN:1;                                     /* [0] */
      __I  unsigned char   REPEATREQ:1;                                /* [1] */
      __I  unsigned char   :4;                                         /* [5:2] */
      __I  unsigned char   LATCHECAT:1;                                /* [6] */
      __I  unsigned char   LATCHPDI:1;                                 /* [7] */
    } BIT;
  } SM4_ACT;
  union                                            /* Offset=0x0827 : SM4_PDI_CONT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   DEACTIVE:1;                                 /* [0] */
      __IO unsigned char   REPEATACK:1;                                /* [1] */
      __IO unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } SM4_PDI_CONT;
  union                                            /* Offset=0x0828 : SM5_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMSTAADDR:16;                               /* [15:0] */
    } BIT;
  } SM5_P_START_ADR;
  union                                            /* Offset=0x082A : SM5_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMLEN:16;                                   /* [15:0] */
    } BIT;
  } SM5_LEN;
  union                                            /* Offset=0x082C : SM5_CONTROL */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   OPEMODE:2;                                  /* [1:0] */
      __I  unsigned char   DIR:2;                                      /* [3:2] */
      __I  unsigned char   IRQECAT:1;                                  /* [4] */
      __I  unsigned char   IRQPDI:1;                                   /* [5] */
      __I  unsigned char   WDTRGEN:1;                                  /* [6] */
    } BIT;
  } SM5_CONTROL;
  union                                            /* Offset=0x082D : SM5_STATUS */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   INTWR:1;                                    /* [0] */
      __I  unsigned char   INTRD:1;                                    /* [1] */
      __I  unsigned char   :1;                                         /* [2] */
      __I  unsigned char   MAILBOX:1;                                  /* [3] */
      __I  unsigned char   BUFFERED:2;                                 /* [5:4] */
      __I  unsigned char   RDBUF:1;                                    /* [6] */
      __I  unsigned char   WRBUF:1;                                    /* [7] */
    } BIT;
  } SM5_STATUS;
  union                                            /* Offset=0x082E : SM5_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SMEN:1;                                     /* [0] */
      __I  unsigned char   REPEATREQ:1;                                /* [1] */
      __I  unsigned char   :4;                                         /* [5:2] */
      __I  unsigned char   LATCHECAT:1;                                /* [6] */
      __I  unsigned char   LATCHPDI:1;                                 /* [7] */
    } BIT;
  } SM5_ACT;
  union                                            /* Offset=0x082F : SM5_PDI_CONT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   DEACTIVE:1;                                 /* [0] */
      __IO unsigned char   REPEATACK:1;                                /* [1] */
      __IO unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } SM5_PDI_CONT;
  union                                            /* Offset=0x0830 : SM6_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMSTAADDR:16;                               /* [15:0] */
    } BIT;
  } SM6_P_START_ADR;
  union                                            /* Offset=0x0832 : SM6_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMLEN:16;                                   /* [15:0] */
    } BIT;
  } SM6_LEN;
  union                                            /* Offset=0x0834 : SM6_CONTROL */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   OPEMODE:2;                                  /* [1:0] */
      __I  unsigned char   DIR:2;                                      /* [3:2] */
      __I  unsigned char   IRQECAT:1;                                  /* [4] */
      __I  unsigned char   IRQPDI:1;                                   /* [5] */
      __I  unsigned char   WDTRGEN:1;                                  /* [6] */
    } BIT;
  } SM6_CONTROL;
  union                                            /* Offset=0x0835 : SM6_STATUS */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   INTWR:1;                                    /* [0] */
      __I  unsigned char   INTRD:1;                                    /* [1] */
      __I  unsigned char   :1;                                         /* [2] */
      __I  unsigned char   MAILBOX:1;                                  /* [3] */
      __I  unsigned char   BUFFERED:2;                                 /* [5:4] */
      __I  unsigned char   RDBUF:1;                                    /* [6] */
      __I  unsigned char   WRBUF:1;                                    /* [7] */
    } BIT;
  } SM6_STATUS;
  union                                            /* Offset=0x0836 : SM6_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SMEN:1;                                     /* [0] */
      __I  unsigned char   REPEATREQ:1;                                /* [1] */
      __I  unsigned char   :4;                                         /* [5:2] */
      __I  unsigned char   LATCHECAT:1;                                /* [6] */
      __I  unsigned char   LATCHPDI:1;                                 /* [7] */
    } BIT;
  } SM6_ACT;
  union                                            /* Offset=0x0837 : SM6_PDI_CONT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   DEACTIVE:1;                                 /* [0] */
      __IO unsigned char   REPEATACK:1;                                /* [1] */
      __IO unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } SM6_PDI_CONT;
  union                                            /* Offset=0x0838 : SM7_P_START_ADR */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMSTAADDR:16;                               /* [15:0] */
    } BIT;
  } SM7_P_START_ADR;
  union                                            /* Offset=0x083A : SM7_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SMLEN:16;                                   /* [15:0] */
    } BIT;
  } SM7_LEN;
  union                                            /* Offset=0x083C : SM7_CONTROL */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   OPEMODE:2;                                  /* [1:0] */
      __I  unsigned char   DIR:2;                                      /* [3:2] */
      __I  unsigned char   IRQECAT:1;                                  /* [4] */
      __I  unsigned char   IRQPDI:1;                                   /* [5] */
      __I  unsigned char   WDTRGEN:1;                                  /* [6] */
    } BIT;
  } SM7_CONTROL;
  union                                            /* Offset=0x083D : SM7_STATUS */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   INTWR:1;                                    /* [0] */
      __I  unsigned char   INTRD:1;                                    /* [1] */
      __I  unsigned char   :1;                                         /* [2] */
      __I  unsigned char   MAILBOX:1;                                  /* [3] */
      __I  unsigned char   BUFFERED:2;                                 /* [5:4] */
      __I  unsigned char   RDBUF:1;                                    /* [6] */
      __I  unsigned char   WRBUF:1;                                    /* [7] */
    } BIT;
  } SM7_STATUS;
  union                                            /* Offset=0x083E : SM7_ACT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SMEN:1;                                     /* [0] */
      __I  unsigned char   REPEATREQ:1;                                /* [1] */
      __I  unsigned char   :4;                                         /* [5:2] */
      __I  unsigned char   LATCHECAT:1;                                /* [6] */
      __I  unsigned char   LATCHPDI:1;                                 /* [7] */
    } BIT;
  } SM7_ACT;
  union                                            /* Offset=0x083F : SM7_PDI_CONT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   DEACTIVE:1;                                 /* [0] */
      __IO unsigned char   REPEATACK:1;                                /* [1] */
      __IO unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } SM7_PDI_CONT;
  char                     wk_0840[0x00C0];
  union                                            /* Offset=0x0900 : DC_RCV_TIME_PORT0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RCVTIME0:32;                                /* [31:0] */
    } BIT;
  } DC_RCV_TIME_PORT0;
  union                                            /* Offset=0x0904 : DC_RCV_TIME_PORT1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RCVTIME1:32;                                /* [31:0] */
    } BIT;
  } DC_RCV_TIME_PORT1;
  union                                            /* Offset=0x0908 : DC_RCV_TIME_PORT2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RCVTIME2:32;                                /* [31:0] */
    } BIT;
  } DC_RCV_TIME_PORT2;
  char                     wk_090C[0x0004];
  union                                            /* Offset=0x0910 : DC_SYS_TIME */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  SYSTIME:64;                             /* [63:0] */
    } BIT;
  } DC_SYS_TIME;
  union                                            /* Offset=0x0918 : DC_RCV_TIME_UNIT */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  RCVTIMEEPU:64;                          /* [63:0] */
    } BIT;
  } DC_RCV_TIME_UNIT;
  union                                            /* Offset=0x0920 : DC_SYS_TIME_OFFSET */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  SYSTIMOFST:64;                          /* [63:0] */
    } BIT;
  } DC_SYS_TIME_OFFSET;
  union                                            /* Offset=0x0928 : DC_SYS_TIME_DELAY */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   SYSTIMDLY:32;                               /* [31:0] */
    } BIT;
  } DC_SYS_TIME_DELAY;
  union                                            /* Offset=0x092C : DC_SYS_TIME_DIFF */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   DIFF:31;                                    /* [30:0] */
      __I  unsigned long   LOCALCOPY:1;                                /* [31] */
    } BIT;
  } DC_SYS_TIME_DIFF;
  union                                            /* Offset=0x0930 : DC_SPEED_COUNT_START */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SPDCNTSTRT:15;                              /* [14:0] */
    } BIT;
  } DC_SPEED_COUNT_START;
  union                                            /* Offset=0x0932 : DC_SPEED_COUNT_DIFF */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SPDCNTDIFF:16;                              /* [15:0] */
    } BIT;
  } DC_SPEED_COUNT_DIFF;
  union                                            /* Offset=0x0934 : DC_SYS_TIME_DIFF_FIL_DEPTH */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SYSTIMDEP:4;                                /* [3:0] */
      __I  unsigned char   :4;                                         /* [7:4] */
    } BIT;
  } DC_SYS_TIME_DIFF_FIL_DEPTH;
  union                                            /* Offset=0x0935 : DC_SPEED_COUNT_FIL_DEPTH */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   CLKPERDEP:4;                                /* [3:0] */
      __I  unsigned char   :4;                                         /* [7:4] */
    } BIT;
  } DC_SPEED_COUNT_FIL_DEPTH;
  char                     wk_0936[0x004A];
  union                                            /* Offset=0x0980 : DC_CYC_CONT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SYNCOUT:1;                                  /* [0] */
      __I  unsigned char   :3;                                         /* [3:1] */
      __I  unsigned char   LATCH0:1;                                   /* [4] */
      __I  unsigned char   LATCH1:1;                                   /* [5] */
      __I  unsigned char   :2;                                         /* [7:6] */
    } BIT;
  } DC_CYC_CONT;
  union                                            /* Offset=0x0981 : DC_ACT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   SYNCACT:1;                                  /* [0] */
      __IO unsigned char   SYNC0:1;                                    /* [1] */
      __IO unsigned char   SYNC1:1;                                    /* [2] */
      __IO unsigned char   AUTOACT:1;                                  /* [3] */
      __IO unsigned char   EXTSTARTTIME:1;                             /* [4] */
      __IO unsigned char   STARTTIME:1;                                /* [5] */
      __IO unsigned char   NEARFUTURE:1;                               /* [6] */
      __IO unsigned char   DBGPULSE:1;                                 /* [7] */
    } BIT;
  } DC_ACT;
  union                                            /* Offset=0x0982 : DC_PULSE_LEN */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  PULSELEN:16;                                /* [15:0] */
    } BIT;
  } DC_PULSE_LEN;
  union                                            /* Offset=0x0984 : DC_ACT_STAT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SYNC0ACT:1;                                 /* [0] */
      __I  unsigned char   SYNC1ACT:1;                                 /* [1] */
      __I  unsigned char   STARTTIME:1;                                /* [2] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } DC_ACT_STAT;
  char                     wk_0985[0x0009];
  union                                            /* Offset=0x098E : DC_SYNC0_STAT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SYNC0STA:1;                                 /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } DC_SYNC0_STAT;
  union                                            /* Offset=0x098F : DC_SYNC1_STAT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   SYNC1STA:1;                                 /* [0] */
      __I  unsigned char   :7;                                         /* [7:1] */
    } BIT;
  } DC_SYNC1_STAT;
  union                                            /* Offset=0x0990 : DC_CYC_START_TIME */
  {
    __IO unsigned long long  LONGLONG;
    struct
    {
      __IO unsigned long long  STATIM:64;                              /* [63:0] */
    } BIT;
  } DC_CYC_START_TIME;
  union                                            /* Offset=0x0998 : DC_NEXT_SYNC1_PULSE */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  SYNC1PULSE:64;                          /* [63:0] */
    } BIT;
  } DC_NEXT_SYNC1_PULSE;
  union                                            /* Offset=0x09A0 : DC_SYNC0_CYC_TIME */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SYNC0CYC:32;                                /* [31:0] */
    } BIT;
  } DC_SYNC0_CYC_TIME;
  union                                            /* Offset=0x09A4 : DC_SYNC1_CYC_TIME */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SYNC1CYC:32;                                /* [31:0] */
    } BIT;
  } DC_SYNC1_CYC_TIME;
  union                                            /* Offset=0x09A8 : DC_LATCH0_CONT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   POSEDGE:1;                                  /* [0] */
      __IO unsigned char   NEGEDGE:1;                                  /* [1] */
      __IO unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } DC_LATCH0_CONT;
  union                                            /* Offset=0x09A9 : DC_LATCH1_CONT */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   POSEDGE:1;                                  /* [0] */
      __IO unsigned char   NEGEDGE:1;                                  /* [1] */
      __IO unsigned char   :6;                                         /* [7:2] */
    } BIT;
  } DC_LATCH1_CONT;
  char                     wk_09AA[0x0004];
  union                                            /* Offset=0x09AE : DC_LATCH0_STAT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   EVENTPOS:1;                                 /* [0] */
      __I  unsigned char   EVENTNEG:1;                                 /* [1] */
      __I  unsigned char   PINSTATE:1;                                 /* [2] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } DC_LATCH0_STAT;
  union                                            /* Offset=0x09AF : DC_LATCH1_STAT */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   EVENTPOS:1;                                 /* [0] */
      __I  unsigned char   EVENTNEG:1;                                 /* [1] */
      __I  unsigned char   PINSTATE:1;                                 /* [2] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } DC_LATCH1_STAT;
  union                                            /* Offset=0x09B0 : DC_LATCH0_TIME_POS */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  SYSTIME:64;                             /* [63:0] */
    } BIT;
  } DC_LATCH0_TIME_POS;
  union                                            /* Offset=0x09B8 : DC_LATCH0_TIME_NEG */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  SYSTIME:64;                             /* [63:0] */
    } BIT;
  } DC_LATCH0_TIME_NEG;
  union                                            /* Offset=0x09C0 : DC_LATCH1_TIME_POS */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  SYSTIME:64;                             /* [63:0] */
    } BIT;
  } DC_LATCH1_TIME_POS;
  union                                            /* Offset=0x09C8 : DC_LATCH1_TIME_NEG */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  SYSTIME:64;                             /* [63:0] */
    } BIT;
  } DC_LATCH1_TIME_NEG;
  char                     wk_09D0[0x0020];
  union                                            /* Offset=0x09F0 : DC_ECAT_CNG_EV_TIME */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   ECATCHANGE:32;                              /* [31:0] */
    } BIT;
  } DC_ECAT_CNG_EV_TIME;
  char                     wk_09F4[0x0004];
  union                                            /* Offset=0x09F8 : DC_PDI_START_EV_TIME */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PDISTART:32;                                /* [31:0] */
    } BIT;
  } DC_PDI_START_EV_TIME;
  union                                            /* Offset=0x09FC : DC_PDI_CNG_EV_TIME */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   PDICHANGE:32;                               /* [31:0] */
    } BIT;
  } DC_PDI_CNG_EV_TIME;
  char                     wk_0A00[0x0400];
  union                                            /* Offset=0x0E00 : PRODUCT_ID */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  PROID:64;                               /* [63:0] */
    } BIT;
  } PRODUCT_ID;
  union                                            /* Offset=0x0E08 : VENDOR_ID */
  {
    __I  unsigned long long  LONGLONG;
    struct
    {
      __I  unsigned long long  VENDORID:32;                            /* [31:0] */
      __I  unsigned long long  :32;                                    /* [63:32] */
    } BIT;
  } VENDOR_ID;
} ETHCAT_Type;
#endif  /* End of __ETHCAT_SFR__DEFINE_HEADER__ */
