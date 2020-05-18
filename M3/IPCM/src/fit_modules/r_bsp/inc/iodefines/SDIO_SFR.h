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
 **       for RZN1 SDIO1
 **
 **       revision 0.13 (15.September.2017)
 **
 **********************************************************************************************************************/
#ifndef __SDIO_SFR__DEFINE_HEADER__
#define __SDIO_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : SDIO
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : reg_sdmasysaddrlo */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  sdma_sysaddress:16;                         /* [15:0] */
    } BIT;
  } reg_sdmasysaddrlo;
  union                                            /* Offset=0x0002 : reg_sdmasysaddrhi */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  sdma_sysaddress:16;                         /* [15:0] */
    } BIT;
  } reg_sdmasysaddrhi;
  union                                            /* Offset=0x0004 : reg_blocksize */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  xfer_blocksize:12;                          /* [11:0] */
      __IO unsigned short  sdma_bufboundary:3;                         /* [14:12] */
    } BIT;
  } reg_blocksize;
  union                                            /* Offset=0x0006 : reg_blockcount */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  xfer_blockcount:16;                         /* [15:0] */
    } BIT;
  } reg_blockcount;
  union                                            /* Offset=0x0008 : reg_argument1lo */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  command_argument1:16;                       /* [15:0] */
    } BIT;
  } reg_argument1lo;
  union                                            /* Offset=0x000A : reg_argument1hi */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  command_argument1:16;                       /* [15:0] */
    } BIT;
  } reg_argument1hi;
  union                                            /* Offset=0x000C : reg_transfermode */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  xfermode_dmaenable:1;                       /* [0] */
      __IO unsigned short  xfermode_blkcntena:1;                       /* [1] */
      __IO unsigned short  xfermode_autocmdena:2;                      /* [3:2] */
      __IO unsigned short  xfermode_dataxferdir:1;                     /* [4] */
      __IO unsigned short  xfermode_multiblksel:1;                     /* [5] */
      __IO unsigned short  :10;                                        /* [15:6] */
    } BIT;
  } reg_transfermode;
  union                                            /* Offset=0x000E : reg_command */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  command_responsetype:2;                     /* [1:0] */
      __IO unsigned short  :1;                                         /* [2] */
      __IO unsigned short  command_crcchkena:1;                        /* [3] */
      __IO unsigned short  command_indexchkena:1;                      /* [4] */
      __IO unsigned short  command_datapresent:1;                      /* [5] */
      __IO unsigned short  command_cmdtype:2;                          /* [7:6] */
      __IO unsigned short  command_cmdindex:6;                         /* [13:8] */
      __IO unsigned short  :2;                                         /* [15:14] */
    } BIT;
  } reg_command;
  union                                            /* Offset=0x0010 : reg_response0 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  command_response:16;                        /* [15:0] */
    } BIT;
  } reg_response0;
  union                                            /* Offset=0x0012 : reg_response1 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  command_response:16;                        /* [15:0] */
    } BIT;
  } reg_response1;
  union                                            /* Offset=0x0014 : reg_response2 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  command_response:16;                        /* [15:0] */
    } BIT;
  } reg_response2;
  union                                            /* Offset=0x0016 : reg_response3 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  command_response:16;                        /* [15:0] */
    } BIT;
  } reg_response3;
  union                                            /* Offset=0x0018 : reg_response4 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  command_response:16;                        /* [15:0] */
    } BIT;
  } reg_response4;
  union                                            /* Offset=0x001A : reg_response5 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  command_response:16;                        /* [15:0] */
    } BIT;
  } reg_response5;
  union                                            /* Offset=0x001C : reg_response6 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  command_response:16;                        /* [15:0] */
    } BIT;
  } reg_response6;
  union                                            /* Offset=0x001E : reg_response7 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  command_response:16;                        /* [15:0] */
    } BIT;
  } reg_response7;
  union                                            /* Offset=0x0020 : reg_dataport */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   sdhcdmactrl_piobufrddata:32;                /* [31:0] */
    } BIT;
  } reg_dataport;
  union                                            /* Offset=0x0024 : reg_presentstate */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   presentstate_inhibitcmd:1;                  /* [0] */
      __I  unsigned long   presentstate_inhibitdat:1;                  /* [1] */
      __I  unsigned long   sdhcdmactrl_datalineactive:1;               /* [2] */
      __I  unsigned long   :5;                                         /* [7:3] */
      __I  unsigned long   sdhcdmactrl_wrxferactive:1;                 /* [8] */
      __I  unsigned long   sdhcdmactrl_rdxferactive:1;                 /* [9] */
      __I  unsigned long   sdhcdmactrl_piobufwrena:1;                  /* [10] */
      __I  unsigned long   sdhcdmactrl_piobufrdena:1;                  /* [11] */
      __I  unsigned long   :4;                                         /* [15:12] */
      __I  unsigned long   sdhccarddet_inserted_dsync:1;               /* [16] */
      __I  unsigned long   sdhccarddet_statestable_dsync:1;            /* [17] */
      __I  unsigned long   sdif_cd_n_dsync:1;                          /* [18] */
      __I  unsigned long   sdif_wp_dsync:1;                            /* [19] */
      __I  unsigned long   sdif_dat0in_dsync:1;                        /* [20] */
      __I  unsigned long   sdif_dat1in_dsync:1;                        /* [21] */
      __I  unsigned long   sdif_dat2in_dsync:1;                        /* [22] */
      __I  unsigned long   sdif_dat3in_dsync:1;                        /* [23] */
      __I  unsigned long   sdif_cmdin_dsync:1;                         /* [24] */
      __I  unsigned long   sdif_dat4in_dsync:1;                        /* [25] */
      __I  unsigned long   sdif_dat5in_dsync:1;                        /* [26] */
      __I  unsigned long   sdif_dat6in_dsync:1;                        /* [27] */
      __I  unsigned long   sdif_dat7in_dsync:1;                        /* [28] */
      __I  unsigned long   :3;                                         /* [31:29] */
    } BIT;
  } reg_presentstate;
  union                                            /* Offset=0x0028 : reg_hostcontrol1 */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   hostctrl1_ledcontrol:1;                     /* [0] */
      __IO unsigned char   hostctrl1_datawidth:1;                      /* [1] */
      __IO unsigned char   hostctrl1_highspeedena:1;                   /* [2] */
      __IO unsigned char   hostctrl1_dmaselect:2;                      /* [4:3] */
      __IO unsigned char   hostctrl1_extdatawidth:1;                   /* [5] */
      __IO unsigned char   hostctrl1_cdtestlevel:1;                    /* [6] */
      __IO unsigned char   hostctrl1_cdsigselect:1;                    /* [7] */
    } BIT;
  } reg_hostcontrol1;
  union                                            /* Offset=0x0029 : reg_powercontrol */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   pwrctrl_sdbuspower:1;                       /* [0] */
      __IO unsigned char   pwrctrl_sdbusvoltage:3;                     /* [3:1] */
      __IO unsigned char   emmc_hwreset:1;                             /* [4] */
      __IO unsigned char   :3;                                         /* [7:5] */
    } BIT;
  } reg_powercontrol;
  union                                            /* Offset=0x002A : reg_blockgapcontrol */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   blkgapctrl_stopatblkgap:1;                  /* [0] */
      __IO unsigned char   blkgapctrl_continue:1;                      /* [1] */
      __IO unsigned char   blkgapctrl_rdwaitctrl:1;                    /* [2] */
      __IO unsigned char   blkgapctrl_interrupt:1;                     /* [3] */
      __IO unsigned char   blkgapctrl_spimode:1;                       /* [4] */
      __IO unsigned char   :3;                                         /* [7:5] */
    } BIT;
  } reg_blockgapcontrol;
  union                                            /* Offset=0x002B : reg_wakeupcontrol */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   wkupctrl_cardinterrupt:1;                   /* [0] */
      __IO unsigned char   wkupctrl_cardinsertion:1;                   /* [1] */
      __IO unsigned char   wkupctrl_cardremoval:1;                     /* [2] */
      __IO unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } reg_wakeupcontrol;
  union                                            /* Offset=0x002C : reg_clockcontrol */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  clkctrl_intclkena:1;                        /* [0] */
      __I  unsigned short  sdhcclkgen_intclkstable_dsync:1;            /* [1] */
      __IO unsigned short  clkctrl_sdclkena:1;                         /* [2] */
      __IO unsigned short  :2;                                         /* [4:3] */
      __I  unsigned short  clkctrl_clkgensel:1;                        /* [5] */
      __IO unsigned short  clkctrl_sdclkfreqsel_upperbits:2;           /* [7:6] */
      __IO unsigned short  clkctrl_sdclkfreqsel:8;                     /* [15:8] */
    } BIT;
  } reg_clockcontrol;
  union                                            /* Offset=0x002E : reg_timeoutcontrol */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   timeout_ctrvalue:4;                         /* [3:0] */
      __IO unsigned char   :4;                                         /* [7:4] */
    } BIT;
  } reg_timeoutcontrol;
  union                                            /* Offset=0x002F : reg_softwarereset */
  {
    __IO unsigned char     BYTE;
    struct
    {
      __IO unsigned char   swreset_for_all:1;                          /* [0] */
      __IO unsigned char   swreset_for_cmd:1;                          /* [1] */
      __IO unsigned char   swreset_for_dat:1;                          /* [2] */
      __IO unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } reg_softwarereset;
  union                                            /* Offset=0x0030 : reg_normalintrsts */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  normalintrsts_cmdcomplete:1;                /* [0] */
      __IO unsigned short  normalintrsts_xfercomplete:1;               /* [1] */
      __IO unsigned short  normalintrsts_blkgapevent:1;                /* [2] */
      __IO unsigned short  normalintrsts_dmainterrupt:1;               /* [3] */
      __IO unsigned short  normalintrsts_bufwrready:1;                 /* [4] */
      __IO unsigned short  normalintrsts_bufrdready:1;                 /* [5] */
      __IO unsigned short  normalintrsts_cardinssts:1;                 /* [6] */
      __IO unsigned short  normalintrsts_cardremsts:1;                 /* [7] */
      __I  unsigned short  normalintrsts_cardintsts:1;                 /* [8] */
      __IO unsigned short  :6;                                         /* [14:9] */
      __I  unsigned short  reg_errorintrsts:1;                         /* [15] */
    } BIT;
  } reg_normalintrsts;
  union                                            /* Offset=0x0032 : reg_errorintrsts */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  errorintrsts_cmdtimeouterror:1;             /* [0] */
      __IO unsigned short  errorintrsts_cmdcrcerror:1;                 /* [1] */
      __IO unsigned short  errorintrsts_cmdendbiterror:1;              /* [2] */
      __IO unsigned short  errorintrsts_cmdindexerror:1;               /* [3] */
      __IO unsigned short  errorintrsts_datatimeouterror:1;            /* [4] */
      __IO unsigned short  errorintrsts_datacrcerror:1;                /* [5] */
      __IO unsigned short  errorintrsts_dataendbiterror:1;             /* [6] */
      __IO unsigned short  errorintrsts_currlimiterror:1;              /* [7] */
      __IO unsigned short  errorintrsts_autocmderror:1;                /* [8] */
      __IO unsigned short  errorintrsts_admaerror:1;                   /* [9] */
      __IO unsigned short  :2;                                         /* [11:10] */
      __IO unsigned short  errorintrsts_hosterror:1;                   /* [12] */
      __IO unsigned short  :3;                                         /* [15:13] */
    } BIT;
  } reg_errorintrsts;
  union                                            /* Offset=0x0034 : reg_normalintrstsena */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  normalintrsts_enableregbit0:1;              /* [0] */
      __IO unsigned short  normalintrsts_enableregbit1:1;              /* [1] */
      __IO unsigned short  normalintrsts_enableregbit2:1;              /* [2] */
      __IO unsigned short  normalintrsts_enableregbit3:1;              /* [3] */
      __IO unsigned short  normalintrsts_enableregbit4:1;              /* [4] */
      __IO unsigned short  normalintrsts_enableregbit5:1;              /* [5] */
      __IO unsigned short  sdhcregset_cardinsstsena:1;                 /* [6] */
      __IO unsigned short  sdhcregset_cardremstsena:1;                 /* [7] */
      __IO unsigned short  sdhcregset_cardintstsena:1;                 /* [8] */
      __IO unsigned short  :6;                                         /* [14:9] */
      __I  unsigned short  normalintrsts_enableregbit15:1;             /* [15] */
    } BIT;
  } reg_normalintrstsena;
  union                                            /* Offset=0x0036 : reg_errorintrstsena */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  errorintrsts_enableregbit0:1;               /* [0] */
      __IO unsigned short  errorintrsts_enableregbit1:1;               /* [1] */
      __IO unsigned short  errorintrsts_enableregbit2:1;               /* [2] */
      __IO unsigned short  errorintrsts_enableregbit3:1;               /* [3] */
      __IO unsigned short  errorintrsts_enableregbit4:1;               /* [4] */
      __IO unsigned short  errorintrsts_enableregbit5:1;               /* [5] */
      __IO unsigned short  errorintrsts_enableregbit6:1;               /* [6] */
      __IO unsigned short  errorintrsts_enableregbit7:1;               /* [7] */
      __IO unsigned short  errorintrsts_enableregbit8:1;               /* [8] */
      __IO unsigned short  errorintrsts_enableregbit9:1;               /* [9] */
      __IO unsigned short  :2;                                         /* [11:10] */
      __I  unsigned short  errorintrsts_enableregbit12:1;              /* [12] */
      __IO unsigned short  :3;                                         /* [15:13] */
    } BIT;
  } reg_errorintrstsena;
  union                                            /* Offset=0x0038 : reg_normalintrsigena */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  normalintrsig_enableregbit0:1;              /* [0] */
      __IO unsigned short  normalintrsig_enableregbit1:1;              /* [1] */
      __IO unsigned short  normalintrsig_enableregbit2:1;              /* [2] */
      __IO unsigned short  normalintrsig_enableregbit3:1;              /* [3] */
      __IO unsigned short  normalintrsig_enableregbit4:1;              /* [4] */
      __IO unsigned short  normalintrsig_enableregbit5:1;              /* [5] */
      __IO unsigned short  normalintrsig_enableregbit6:1;              /* [6] */
      __IO unsigned short  normalintrsig_enableregbit7:1;              /* [7] */
      __IO unsigned short  normalintrsig_enableregbit8:1;              /* [8] */
      __IO unsigned short  :6;                                         /* [14:9] */
      __I  unsigned short  normalintrsig_enableregbit15:1;             /* [15] */
    } BIT;
  } reg_normalintrsigena;
  union                                            /* Offset=0x003A : reg_errorintrsigena */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  errorintrsig_enableregbit0:1;               /* [0] */
      __IO unsigned short  errorintrsig_enableregbit1:1;               /* [1] */
      __IO unsigned short  errorintrsig_enableregbit2:1;               /* [2] */
      __IO unsigned short  errorintrsig_enableregbit3:1;               /* [3] */
      __IO unsigned short  errorintrsig_enableregbit4:1;               /* [4] */
      __IO unsigned short  errorintrsig_enableregbit5:1;               /* [5] */
      __IO unsigned short  errorintrsig_enableregbit6:1;               /* [6] */
      __IO unsigned short  errorintrsig_enableregbit7:1;               /* [7] */
      __IO unsigned short  errorintrsig_enableregbit8:1;               /* [8] */
      __IO unsigned short  errorintrsig_enableregbit9:1;               /* [9] */
      __IO unsigned short  :2;                                         /* [11:10] */
      __I  unsigned short  errorintrsig_enableregbit12:1;              /* [12] */
      __IO unsigned short  :3;                                         /* [15:13] */
    } BIT;
  } reg_errorintrsigena;
  union                                            /* Offset=0x003C : reg_autocmderrsts */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  autocmderrsts_notexecerror:1;               /* [0] */
      __I  unsigned short  autocmderrsts_timeouterror:1;               /* [1] */
      __I  unsigned short  autocmderrsts_crcerror:1;                   /* [2] */
      __I  unsigned short  autocmderrsts_endbiterror:1;                /* [3] */
      __I  unsigned short  autocmderrsts_indexerror:1;                 /* [4] */
      __I  unsigned short  :2;                                         /* [6:5] */
      __I  unsigned short  autocmderrsts_nexterror:1;                  /* [7] */
      __I  unsigned short  :8;                                         /* [15:8] */
    } BIT;
  } reg_autocmderrsts;
  union                                            /* Offset=0x003E : reg_hostcontrol2 */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  :14;                                        /* [13:0] */
      __IO unsigned short  hostctrl2_asynchintrenable:1;               /* [14] */
      __IO unsigned short  hostctrl2_presetvalueenable:1;              /* [15] */
    } BIT;
  } reg_hostcontrol2;
  union                                            /* Offset=0x0040 : reg_capabilities */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   corecfg_timeoutclkfreq:6;                   /* [5:0] */
      __I  unsigned long   :1;                                         /* [6] */
      __I  unsigned long   corecfg_timeoutclkunit:1;                   /* [7] */
      __I  unsigned long   corecfg_baseclkfreq:8;                      /* [15:8] */
      __I  unsigned long   corecfg_maxblklength:2;                     /* [17:16] */
      __I  unsigned long   corecfg_8bitsupport:1;                      /* [18] */
      __I  unsigned long   corecfg_adma2support:1;                     /* [19] */
      __I  unsigned long   :1;                                         /* [20] */
      __I  unsigned long   corecfg_highspeedsupport:1;                 /* [21] */
      __I  unsigned long   corecfg_sdmasupport:1;                      /* [22] */
      __I  unsigned long   corecfg_suspressupport:1;                   /* [23] */
      __I  unsigned long   corecfg_3p3voltsupport:1;                   /* [24] */
      __I  unsigned long   corecfg_3p0voltsupport:1;                   /* [25] */
      __I  unsigned long   corecfg_1p8voltsupport:1;                   /* [26] */
      __I  unsigned long   :1;                                         /* [27] */
      __I  unsigned long   corecfg_64bitsupport:1;                     /* [28] */
      __I  unsigned long   corecfg_asynchintrsupport:1;                /* [29] */
      __I  unsigned long   corecfg_slottype:2;                         /* [31:30] */
    } BIT;
  } reg_capabilities;
  union                                            /* Offset=0x0044 : reg_capabilities_cont */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :16;                                        /* [15:0] */
      __I  unsigned long   corecfg_clockmultiplier:8;                  /* [23:16] */
      __I  unsigned long   corecfg_spisupport:1;                       /* [24] */
      __I  unsigned long   corecfg_spiblkmode:1;                       /* [25] */
      __I  unsigned long   :6;                                         /* [31:26] */
    } BIT;
  } reg_capabilities_cont;
  union                                            /* Offset=0x0048 : reg_maxcurrentcap */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   corecfg_maxcurrent3p3v:8;                   /* [7:0] */
      __I  unsigned long   corecfg_maxcurrent3p0v:8;                   /* [15:8] */
      __I  unsigned long   corecfg_maxcurrent1p8v:8;                   /* [23:16] */
      __I  unsigned long   :8;                                         /* [31:24] */
    } BIT;
  } reg_maxcurrentcap;
  char                     wk_004C[0x0004];
  union                                            /* Offset=0x0050 : reg_ForceEventforAUTOCMDErrorStatus */
  {
    __O  unsigned short    WORD;
    struct
    {
      __O  unsigned short  forceautocmdnotexec:1;                      /* [0] */
      __O  unsigned short  forceautocmdtimeouterr:1;                   /* [1] */
      __O  unsigned short  forceautocmdcrcerr:1;                       /* [2] */
      __O  unsigned short  forceautocmdendbiterr:1;                    /* [3] */
      __O  unsigned short  forceautocmdindexerr:1;                     /* [4] */
      __O  unsigned short  :2;                                         /* [6:5] */
      __O  unsigned short  forcecmdnotissuedbyautocmd12err:1;          /* [7] */
      __O  unsigned short  :8;                                         /* [15:8] */
    } BIT;
  } reg_ForceEventforAUTOCMDErrorStatus;
  union                                            /* Offset=0x0052 : reg_forceeventforerrintsts */
  {
    __O  unsigned short    WORD;
    struct
    {
      __O  unsigned short  forcecmdtimeouterr:1;                       /* [0] */
      __O  unsigned short  forcecmdcrcerr:1;                           /* [1] */
      __O  unsigned short  forcecmdendbiterr:1;                        /* [2] */
      __O  unsigned short  forcecmdindexerr:1;                         /* [3] */
      __O  unsigned short  forcedattimeouterr:1;                       /* [4] */
      __O  unsigned short  forcedatcrcerr:1;                           /* [5] */
      __O  unsigned short  forcedatendbiterr:1;                        /* [6] */
      __O  unsigned short  forcecurrlimerr:1;                          /* [7] */
      __O  unsigned short  forceautocmderr:1;                          /* [8] */
      __O  unsigned short  forceadmaerr:1;                             /* [9] */
      __O  unsigned short  :6;                                         /* [15:10] */
    } BIT;
  } reg_forceeventforerrintsts;
  union                                            /* Offset=0x0054 : reg_admaerrsts */
  {
    __I  unsigned char     BYTE;
    struct
    {
      __I  unsigned char   admaerrsts_admaerrorstate:2;                /* [1:0] */
      __I  unsigned char   admaerrsts_admalenmismatcherr:1;            /* [2] */
      __I  unsigned char   :5;                                         /* [7:3] */
    } BIT;
  } reg_admaerrsts;
  char                     wk_0055[0x0003];
  union                                            /* Offset=0x0058 : reg_admasysaddr0 */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  adma_sysaddress0:16;                        /* [15:0] */
    } BIT;
  } reg_admasysaddr0;
  union                                            /* Offset=0x005A : reg_admasysaddr1 */
  {
    __IO unsigned short    WORD;
    struct
    {
      __IO unsigned short  adma_sysaddress1:16;                        /* [15:0] */
    } BIT;
  } reg_admasysaddr1;
  char                     wk_005C[0x0004];
  union                                            /* Offset=0x0060 : reg_presetvalue0 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SDCLKFrequencySelectValue:10;               /* [9:0] */
      __I  unsigned short  ClockGeneratorSelectValue:1;                /* [10] */
      __I  unsigned short  :5;                                         /* [15:11] */
    } BIT;
  } reg_presetvalue0;
  union                                            /* Offset=0x0062 : reg_presetvalue1 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SDCLKFrequencySelectValue:10;               /* [9:0] */
      __I  unsigned short  ClockGeneratorSelectValue:1;                /* [10] */
      __I  unsigned short  :5;                                         /* [15:11] */
    } BIT;
  } reg_presetvalue1;
  union                                            /* Offset=0x0064 : reg_presetvalue2 */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SDCLKFrequencySelectValue:10;               /* [9:0] */
      __I  unsigned short  ClockGeneratorSelectValue:1;                /* [10] */
      __I  unsigned short  :5;                                         /* [15:11] */
    } BIT;
  } reg_presetvalue2;
  char                     wk_0066[0x0096];
  union                                            /* Offset=0x00FC : reg_slotintrsts */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  sdhchostif_slotintrsts:1;                   /* [0] */
      __I  unsigned short  :15;                                        /* [15:1] */
    } BIT;
  } reg_slotintrsts;
  union                                            /* Offset=0x00FE : reg_hostcontrollerver */
  {
    __I  unsigned short    WORD;
    struct
    {
      __I  unsigned short  SpecificationVersionNumber:8;               /* [7:0] */
      __I  unsigned short  SDHC_VENVERNUM:8;                           /* [15:8] */
    } BIT;
  } reg_hostcontrollerver;
} SDIO_Type;
#endif  /* End of __SDIO_SFR__DEFINE_HEADER__ */
