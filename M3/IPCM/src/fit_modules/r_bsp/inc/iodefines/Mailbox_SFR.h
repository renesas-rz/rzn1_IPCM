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
 **       for RZN1 Mailbox
 **
 **       revision 0.20 (2.Nov.2017)
 **
 **********************************************************************************************************************/
#ifndef __Mailbox_SFR__DEFINE_HEADER__
#define __Mailbox_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : Mailbox
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : IPCM0SOURCE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SRC_SET:3;                                  /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM0SOURCE;
  union                                            /* Offset=0x0004 : IPCM0DSET */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   DEST_SET:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM0DSET;
  union                                            /* Offset=0x0008 : IPCM0DCLEAR */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   DEST_CLR:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM0DCLEAR;
  union                                            /* Offset=0x000C : IPCM0DSTATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   DEST_STAT:3;                                /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM0DSTATUS;
  union                                            /* Offset=0x0010 : IPCM0MODE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AUTO_ACK:1;                                 /* [0] */
      __IO unsigned long   AUTO_LINK:1;                                /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } IPCM0MODE;
  union                                            /* Offset=0x0014 : IPCM0MSET */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   MASK_SET:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM0MSET;
  union                                            /* Offset=0x0018 : IPCM0MCLEAR */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   MASK_CLR:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM0MCLEAR;
  union                                            /* Offset=0x001C : IPCM0MSTATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MASK_STAT:3;                                /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM0MSTATUS;
  union                                            /* Offset=0x0020 : IPCM0SEND */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SEND:2;                                     /* [1:0] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } IPCM0SEND;
  union                                            /* Offset=0x0024 : IPCM0DR0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM0DR0;
  union                                            /* Offset=0x0028 : IPCM0DR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM0DR1;
  union                                            /* Offset=0x002C : IPCM0DR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM0DR2;
  union                                            /* Offset=0x0030 : IPCM0DR3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM0DR3;
  union                                            /* Offset=0x0034 : IPCM0DR4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM0DR4;
  union                                            /* Offset=0x0038 : IPCM0DR5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM0DR5;
  union                                            /* Offset=0x003C : IPCM0DR6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM0DR6;
  union                                            /* Offset=0x0040 : IPCM1SOURCE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SRC_SET:3;                                  /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM1SOURCE;
  union                                            /* Offset=0x0044 : IPCM1DSET */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   DEST_SET:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM1DSET;
  union                                            /* Offset=0x0048 : IPCM1DCLEAR */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   DEST_CLR:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM1DCLEAR;
  union                                            /* Offset=0x004C : IPCM1DSTATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   DEST_STAT:3;                                /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM1DSTATUS;
  union                                            /* Offset=0x0050 : IPCM1MODE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AUTO_ACK:1;                                 /* [0] */
      __IO unsigned long   AUTO_LINK:1;                                /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } IPCM1MODE;
  union                                            /* Offset=0x0054 : IPCM1MSET */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   MASK_SET:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM1MSET;
  union                                            /* Offset=0x0058 : IPCM1MCLEAR */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   MASK_CLR:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM1MCLEAR;
  union                                            /* Offset=0x005C : IPCM1MSTATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MASK_STAT:3;                                /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM1MSTATUS;
  union                                            /* Offset=0x0060 : IPCM1SEND */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SEND:2;                                     /* [1:0] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } IPCM1SEND;
  union                                            /* Offset=0x0064 : IPCM1DR0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM1DR0;
  union                                            /* Offset=0x0068 : IPCM1DR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM1DR1;
  union                                            /* Offset=0x006C : IPCM1DR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM1DR2;
  union                                            /* Offset=0x0070 : IPCM1DR3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM1DR3;
  union                                            /* Offset=0x0074 : IPCM1DR4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM1DR4;
  union                                            /* Offset=0x0078 : IPCM1DR5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM1DR5;
  union                                            /* Offset=0x007C : IPCM1DR6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM1DR6;
  union                                            /* Offset=0x0080 : IPCM2SOURCE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SRC_SET:3;                                  /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM2SOURCE;
  union                                            /* Offset=0x0084 : IPCM2DSET */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   DEST_SET:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM2DSET;
  union                                            /* Offset=0x0088 : IPCM2DCLEAR */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   DEST_CLR:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM2DCLEAR;
  union                                            /* Offset=0x008C : IPCM2DSTATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   DEST_STAT:3;                                /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM2DSTATUS;
  union                                            /* Offset=0x0090 : IPCM2MODE */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   AUTO_ACK:1;                                 /* [0] */
      __IO unsigned long   AUTO_LINK:1;                                /* [1] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } IPCM2MODE;
  union                                            /* Offset=0x0094 : IPCM2MSET */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   MASK_SET:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM2MSET;
  union                                            /* Offset=0x0098 : IPCM2MCLEAR */
  {
    __O  unsigned long     LONG;
    struct
    {
      __O  unsigned long   MASK_CLR:3;                                 /* [2:0] */
      __O  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM2MCLEAR;
  union                                            /* Offset=0x009C : IPCM2MSTATUS */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MASK_STAT:3;                                /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCM2MSTATUS;
  union                                            /* Offset=0x00A0 : IPCM2SEND */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SEND:2;                                     /* [1:0] */
      __IO unsigned long   :30;                                        /* [31:2] */
    } BIT;
  } IPCM2SEND;
  union                                            /* Offset=0x00A4 : IPCM2DR0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM2DR0;
  union                                            /* Offset=0x00A8 : IPCM2DR1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM2DR1;
  union                                            /* Offset=0x00AC : IPCM2DR2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM2DR2;
  union                                            /* Offset=0x00B0 : IPCM2DR3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM2DR3;
  union                                            /* Offset=0x00B4 : IPCM2DR4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM2DR4;
  union                                            /* Offset=0x00B8 : IPCM2DR5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM2DR5;
  union                                            /* Offset=0x00BC : IPCM2DR6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DATA:32;                                    /* [31:0] */
    } BIT;
  } IPCM2DR6;
  char                     wk_00C0[0x0740];
  union                                            /* Offset=0x0800 : IPCMMIS0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MASK_INT_STAT:3;                            /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCMMIS0;
  union                                            /* Offset=0x0804 : IPCMRIS0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RAW_INT_STAT:3;                             /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCMRIS0;
  union                                            /* Offset=0x0808 : IPCMMIS1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MASK_INT_STAT:3;                            /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCMMIS1;
  union                                            /* Offset=0x080C : IPCMRIS1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RAW_INT_STAT:3;                             /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCMRIS1;
  union                                            /* Offset=0x0810 : IPCMMIS2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   MASK_INT_STAT:3;                            /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCMMIS2;
  union                                            /* Offset=0x0814 : IPCMRIS2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   RAW_INT_STAT:3;                             /* [2:0] */
      __I  unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCMRIS2;
  char                     wk_0818[0x00E8];
  union                                            /* Offset=0x0900 : IPCMCFGSTAT */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   DATA_WORDS:3;                               /* [2:0] */
      __I  unsigned long   :5;                                         /* [7:3] */
      __I  unsigned long   INTERRUPTS:6;                               /* [13:8] */
      __I  unsigned long   :2;                                         /* [15:14] */
      __I  unsigned long   MAILBOXES:6;                                /* [21:16] */
      __I  unsigned long   :10;                                        /* [31:22] */
    } BIT;
  } IPCMCFGSTAT;
  char                     wk_0904[0x05FC];
  union                                            /* Offset=0x0F00 : IPCMTCR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ITEN:1;                                     /* [0] */
      __IO unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } IPCMTCR;
  union                                            /* Offset=0x0F04 : IPCMTOR */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   INTTEST:3;                                  /* [2:0] */
      __IO unsigned long   :29;                                        /* [31:3] */
    } BIT;
  } IPCMTOR;
} Mailbox_Type;
#endif  /* End of __Mailbox_SFR__DEFINE_HEADER__ */
