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
 * $Revision: 1201 $
 * $Date: 2019-02-04 14:08:15 +0000 (Mon, 04 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_rzn1_reg_defs.h
 * Description  :  USB register definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_USB_RZN1_REG_DEFS_H__
#define R_USB_RZN1_REG_DEFS_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/*  Definitions for accessing EPC Registers for USB device setup */
#define USBFUNC_USB_EPC_CONTROL_ADDRESS             ( RZN1_USB_DEV_BASE + 0 )
#define USBFUNC_USB_EPC_STATUS_ADDRESS              ( RZN1_USB_DEV_BASE + 0x0004 )
#define USBFUNC_USB_EPC_ADDRESS_ADDRESS             ( RZN1_USB_DEV_BASE + 0x0008 )
#define USBFUNC_USB_EPC_TEST_CONTROL_ADDRESS        ( RZN1_USB_DEV_BASE + 0x0010 )
#define USBFUNC_USB_EPC_SETUP_DATA0_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0018 )
#define USBFUNC_USB_EPC_SETUP_DATA1_ADDRESS         ( RZN1_USB_DEV_BASE + 0x001C )
#define USBFUNC_USB_EPC_USB_INT_STA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0020 )
#define USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0024 )
#define USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0028 )
#define USBFUNC_USB_EPC_EP0_STATUS_ADDRESS          ( RZN1_USB_DEV_BASE + 0x002C )
#define USBFUNC_USB_EPC_EP0_INT_ENA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0030 )
#define USBFUNC_USB_EPC_EP0_LENGTH_ADDRESS          ( RZN1_USB_DEV_BASE + 0x0034 )
#define USBFUNC_USB_EPC_EP0_READ_ADDRESS            ( RZN1_USB_DEV_BASE + 0x0038 )
#define USBFUNC_USB_EPC_EP0_WRITE_ADDRESS           ( RZN1_USB_DEV_BASE + 0x003C )

#define USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0040 )
#define USBFUNC_USB_EPC_EP1_STATUS_ADDRESS          ( RZN1_USB_DEV_BASE + 0x0044 )
#define USBFUNC_USB_EPC_EP1_INT_ENA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0048 )
#define USBFUNC_USB_EPC_EP1_DMA_CTRL_ADDRESS        ( RZN1_USB_DEV_BASE + 0x004C )
#define USBFUNC_USB_EPC_EP1_PCKT_ADRS_ADDRESS       ( RZN1_USB_DEV_BASE + 0x0050 )
#define USBFUNC_USB_EPC_EP1_LEN_DCNT_ADDRESS        ( RZN1_USB_DEV_BASE + 0x0054 )
#define USBFUNC_USB_EPC_EP1_READ_ADDRESS            ( RZN1_USB_DEV_BASE + 0x0058 )
#define USBFUNC_USB_EPC_EP1_WRITE_ADDRESS           ( RZN1_USB_DEV_BASE + 0x005C )

#define USBFUNC_USB_EPC_EP2_CONTROL_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0040 + 0x0020 )
#define USBFUNC_USB_EPC_EP2_STATUS_ADDRESS          ( RZN1_USB_DEV_BASE + 0x0044 + 0x0020 )
#define USBFUNC_USB_EPC_EP2_INT_ENA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0048 + 0x0020 )
#define USBFUNC_USB_EPC_EP2_DMA_CTRL_ADDRESS        ( RZN1_USB_DEV_BASE + 0x004C + 0x0020 )
#define USBFUNC_USB_EPC_EP2_PCKT_ADRS_ADDRESS       ( RZN1_USB_DEV_BASE + 0x0050 + 0x0020 )
#define USBFUNC_USB_EPC_EP2_LEN_DCNT_ADDRESS        ( RZN1_USB_DEV_BASE + 0x0054 + 0x0020 )
#define USBFUNC_USB_EPC_EP2_READ_ADDRESS            ( RZN1_USB_DEV_BASE + 0x0058 + 0x0020 )
#define USBFUNC_USB_EPC_EP2_WRITE_ADDRESS           ( RZN1_USB_DEV_BASE + 0x005C + 0x0020 )

#define USBFUNC_USB_EPC_EP3_CONTROL_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0040 + 0x0040 )
#define USBFUNC_USB_EPC_EP3_STATUS_ADDRESS          ( RZN1_USB_DEV_BASE + 0x0044 + 0x0040 )
#define USBFUNC_USB_EPC_EP3_INT_ENA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0048 + 0x0040 )
#define USBFUNC_USB_EPC_EP3_DMA_CTRL_ADDRESS        ( RZN1_USB_DEV_BASE + 0x004C + 0x0040 )
#define USBFUNC_USB_EPC_EP3_PCKT_ADRS_ADDRESS       ( RZN1_USB_DEV_BASE + 0x0050 + 0x0040 )
#define USBFUNC_USB_EPC_EP3_LEN_DCNT_ADDRESS        ( RZN1_USB_DEV_BASE + 0x0054 + 0x0040 )
#define USBFUNC_USB_EPC_EP3_READ_ADDRESS            ( RZN1_USB_DEV_BASE + 0x0058 + 0x0040 )
#define USBFUNC_USB_EPC_EP3_WRITE_ADDRESS           ( RZN1_USB_DEV_BASE + 0x005C + 0x0040 )

#define USBFUNC_USB_EPC_EP4_CONTROL_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0040 + 0x0060)
#define USBFUNC_USB_EPC_EP4_STATUS_ADDRESS          ( RZN1_USB_DEV_BASE + 0x0044 + 0x0060)
#define USBFUNC_USB_EPC_EP4_INT_ENA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0048 + 0x0060)
#define USBFUNC_USB_EPC_EP4_DMA_CTRL_ADDRESS        ( RZN1_USB_DEV_BASE + 0x004C + 0x0060)
#define USBFUNC_USB_EPC_EP4_PCKT_ADRS_ADDRESS       ( RZN1_USB_DEV_BASE + 0x0050 + 0x0060)
#define USBFUNC_USB_EPC_EP4_LEN_DCNT_ADDRESS        ( RZN1_USB_DEV_BASE + 0x0054 + 0x0060)
#define USBFUNC_USB_EPC_EP4_READ_ADDRESS            ( RZN1_USB_DEV_BASE + 0x0058 + 0x0060)
#define USBFUNC_USB_EPC_EP4_WRITE_ADDRESS           ( RZN1_USB_DEV_BASE + 0x005C + 0x0060)

#define USBFUNC_USB_EPC_EP5_CONTROL_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0040 + 0x0080)
#define USBFUNC_USB_EPC_EP5_STATUS_ADDRESS          ( RZN1_USB_DEV_BASE + 0x0044 + 0x0080)
#define USBFUNC_USB_EPC_EP5_INT_ENA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0048 + 0x0080)
#define USBFUNC_USB_EPC_EP5_DMA_CTRL_ADDRESS        ( RZN1_USB_DEV_BASE + 0x004C + 0x0080)
#define USBFUNC_USB_EPC_EP5_PCKT_ADRS_ADDRESS       ( RZN1_USB_DEV_BASE + 0x0050 + 0x0080)
#define USBFUNC_USB_EPC_EP5_LEN_DCNT_ADDRESS        ( RZN1_USB_DEV_BASE + 0x0054 + 0x0080)
#define USBFUNC_USB_EPC_EP5_READ_ADDRESS            ( RZN1_USB_DEV_BASE + 0x0058 + 0x0080)
#define USBFUNC_USB_EPC_EP5_WRITE_ADDRESS           ( RZN1_USB_DEV_BASE + 0x005C + 0x0080)

#define USBFUNC_USB_EPC_EP6_CONTROL_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0040 + 0x00A0)
#define USBFUNC_USB_EPC_EP6_STATUS_ADDRESS          ( RZN1_USB_DEV_BASE + 0x0044 + 0x00A0)
#define USBFUNC_USB_EPC_EP6_INT_ENA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0048 + 0x00A0)
#define USBFUNC_USB_EPC_EP6_DMA_CTRL_ADDRESS        ( RZN1_USB_DEV_BASE + 0x004C + 0x00A0)
#define USBFUNC_USB_EPC_EP6_PCKT_ADRS_ADDRESS       ( RZN1_USB_DEV_BASE + 0x0050 + 0x00A0)
#define USBFUNC_USB_EPC_EP6_LEN_DCNT_ADDRESS        ( RZN1_USB_DEV_BASE + 0x0054 + 0x00A0)
#define USBFUNC_USB_EPC_EP6_READ_ADDRESS            ( RZN1_USB_DEV_BASE + 0x0058 + 0x00A0)
#define USBFUNC_USB_EPC_EP6_WRITE_ADDRESS           ( RZN1_USB_DEV_BASE + 0x005C + 0x00A0)

#define USBFUNC_USB_EPC_EP7_CONTROL_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0040 + 0x00C0)
#define USBFUNC_USB_EPC_EP7_STATUS_ADDRESS          ( RZN1_USB_DEV_BASE + 0x0044 + 0x00C0)
#define USBFUNC_USB_EPC_EP7_INT_ENA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0048 + 0x00C0)
#define USBFUNC_USB_EPC_EP7_DMA_CTRL_ADDRESS        ( RZN1_USB_DEV_BASE + 0x004C + 0x00C0)
#define USBFUNC_USB_EPC_EP7_PCKT_ADRS_ADDRESS       ( RZN1_USB_DEV_BASE + 0x0050 + 0x00C0)
#define USBFUNC_USB_EPC_EP7_LEN_DCNT_ADDRESS        ( RZN1_USB_DEV_BASE + 0x0054 + 0x00C0)
#define USBFUNC_USB_EPC_EP7_READ_ADDRESS            ( RZN1_USB_DEV_BASE + 0x0058 + 0x00C0)
#define USBFUNC_USB_EPC_EP7_WRITE_ADDRESS           ( RZN1_USB_DEV_BASE + 0x005C + 0x00C0)

#define USBFUNC_USB_EPC_EP8_CONTROL_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0040 + 0x00E0)
#define USBFUNC_USB_EPC_EP8_STATUS_ADDRESS          ( RZN1_USB_DEV_BASE + 0x0044 + 0x00E0)
#define USBFUNC_USB_EPC_EP8_INT_ENA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0048 + 0x00E0)
#define USBFUNC_USB_EPC_EP8_DMA_CTRL_ADDRESS        ( RZN1_USB_DEV_BASE + 0x004C + 0x00E0)
#define USBFUNC_USB_EPC_EP8_PCKT_ADRS_ADDRESS       ( RZN1_USB_DEV_BASE + 0x0050 + 0x00E0)
#define USBFUNC_USB_EPC_EP8_LEN_DCNT_ADDRESS        ( RZN1_USB_DEV_BASE + 0x0054 + 0x00E0)
#define USBFUNC_USB_EPC_EP8_READ_ADDRESS            ( RZN1_USB_DEV_BASE + 0x0058 + 0x00E0)
#define USBFUNC_USB_EPC_EP8_WRITE_ADDRESS           ( RZN1_USB_DEV_BASE + 0x005C + 0x00E0)

#define USBFUNC_USB_EPC_EP9_CONTROL_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0040 + 0x0100)
#define USBFUNC_USB_EPC_EP9_STATUS_ADDRESS          ( RZN1_USB_DEV_BASE + 0x0044 + 0x0100)
#define USBFUNC_USB_EPC_EP9_INT_ENA_ADDRESS         ( RZN1_USB_DEV_BASE + 0x0048 + 0x0100)
#define USBFUNC_USB_EPC_EP9_DMA_CTRL_ADDRESS        ( RZN1_USB_DEV_BASE + 0x004C + 0x0100)
#define USBFUNC_USB_EPC_EP9_PCKT_ADRS_ADDRESS       ( RZN1_USB_DEV_BASE + 0x0050 + 0x0100)
#define USBFUNC_USB_EPC_EP9_LEN_DCNT_ADDRESS        ( RZN1_USB_DEV_BASE + 0x0054 + 0x0100)
#define USBFUNC_USB_EPC_EP9_READ_ADDRESS            ( RZN1_USB_DEV_BASE + 0x0058 + 0x0100)
#define USBFUNC_USB_EPC_EP9_WRITE_ADDRESS           ( RZN1_USB_DEV_BASE + 0x005C + 0x0100)


/*  Definitions for accessing AHB-EPC Bridge Registers for USB device setup */
#define USBFUNC_AHBSCTR_ADDRESS     ( RZN1_USB_DEV_BASE + 0x00001000 )
#define USBFUNC_AHBMCTR_ADDRESS     ( RZN1_USB_DEV_BASE + 0x00001004 )
#define USBFUNC_AHBBINT_ADDRESS     ( RZN1_USB_DEV_BASE + 0x00001008 )
#define USBFUNC_AHBBINTEN_ADDRESS   ( RZN1_USB_DEV_BASE + 0x0000100C )
#define USBFUNC_EPCTR_ADDRESS       ( RZN1_USB_DEV_BASE + 0x00001010 )
#define USBFUNC_USBSSVER_ADDRESS    ( RZN1_USB_DEV_BASE + 0x00001020 )
#define USBFUNC_USBSSCONF_ADDRESS   ( RZN1_USB_DEV_BASE + 0x00001024 )

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

typedef struct
{
  union                                            /* Offset=0x0000 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                      /* [0:1] */
      __IO unsigned long   PUE2:1;                  /* [2] */
      __IO unsigned long   CONNECTB:1;              /* [3] */
      __IO unsigned long   DEFAULT:1;               /* [4] */
      __IO unsigned long   CONF:1;                  /* [5] */
      __IO unsigned long   SUSPEND:1;               /* [6] */
      __IO unsigned long   RSUM_IN:1;               /* [7] */
      __IO unsigned long   SOF_RCV:1;               /* [8] */
      __IO unsigned long   FORCEFS:1;               /* [9] */
      __IO unsigned long   INT_SEL:1;               /* [10] */
      __IO unsigned long   SOF_CLK_MODE:1;          /* [11] */
      __IO unsigned long   :4;                      /* [12:15] */
      __IO unsigned long   USBTESTMODE:3;           /* [16:18] */
      __IO unsigned long   :13;                     /* [19:31] */
    } BIT;
  } USB_CONTROL;
} EPC_USB_CONTROL_Type;

#define EPC_USB_CONTROL_PUE2_BIT            (1<<2)
#define EPC_USB_CONTROL_CONNECTB_BIT        (1<<3)
#define EPC_USB_CONTROL_DEFAULT_BIT         (1<<4)
#define EPC_USB_CONTROL_CONF_BIT            (1<<5)
#define EPC_USB_CONTROL_SOF_RCV_BIT         (1<<8)
#define EPC_USB_CONTROL_INT_SEL_BIT         (1<<10)
#define EPC_USB_CONTROL_SOF_CLK_MODE_BIT    (1<<11)

typedef struct
{
  union                                            /* Offset=0x0004 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                      /* [0] */
      __IO unsigned long   RSUM_OUT:1;              /* [1] */
      __IO unsigned long   SPND_OUT:1;              /* [2] */
      __IO unsigned long   USB_RST:1;               /* [3] */
      __IO unsigned long   DEFAULT:1;               /* [4] */
      __IO unsigned long   CONF:1;                  /* [5] */
      __IO unsigned long   SPEED_MODE:1;            /* [6] */
      __IO unsigned long   :24;                     /* [7:30] */
      __IO unsigned long   SOF_DELAY_STATUS:1;      /* [31] */
    } BIT;
  } USB_STATUS;
} EPC_USB_STATUS_Type;

typedef struct
{
  union                                             /* Offset=0x0008 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   FRAME:11;                /* [0:10] */
      __IO unsigned long   :1;                      /* [11] */
      __IO unsigned long   UFRAME:3;                /* [12:14] */
      __IO unsigned long   SOF_STATUS:1;            /* [15] */
      __IO unsigned long   USB_ADDR:7;              /* [16:22] */
      __IO unsigned long   :8;                      /* [23:30] */
      __IO unsigned long   SOF_DELAY_MODE:1;        /* [31] */
    } BIT;
  } USB_ADDRESS;
} EPC_USB_ADDRESS_Type;

typedef struct
{
  union                                             /* Offset=0x0010 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   LOOPBACK:1;              /* [0] */
      __IO unsigned long   CS_TESTMODEEN:1;         /* [1] */
      __IO unsigned long   FORCEHS:1;               /* [2] */
      __IO unsigned long   :29;                     /* [3:31] */
    } BIT;
  } TEST_CONTROL;
} EPC_TEST_CONTROL_Type;

typedef struct
{
  union                                             /* Offset=0x0018 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SETUP1:8;                /* [0:7] */
      __IO unsigned long   SETUP2:8;                /* [8:15] */
      __IO unsigned long   SETUP3:8;                /* [16:23] */
      __IO unsigned long   SETUP4:8;                /* [24:31] */
    } BIT;
  } SETUP_DATA0;
} EPC_SETUP_DATA0_Type;

typedef struct
{
  union                                            /* Offset=0x001C : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SETUP5:8;                /* [0:7] */
      __IO unsigned long   SETUP6:8;                /* [8:15] */
      __IO unsigned long   SETUP7:8;                /* [16:23] */
      __IO unsigned long   SETUP8:8;                /* [24:31] */
    } BIT;
  } SETUP_DATA1;
} EPC_SETUP_DATA1_Type;

typedef struct
{
  union                                            /* Offset=0x0020 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                      /* [0] */
      __IO unsigned long   RSUM_INT:1;              /* [1] */
      __IO unsigned long   SPND_INT:1;              /* [2] */
      __IO unsigned long   USB_RST_INT:1;           /* [3] */
      __IO unsigned long   SOF_INT:1;               /* [4] */
      __IO unsigned long   SOF_ERROR_INT:1;         /* [5] */
      __IO unsigned long   SPEED_MODE_INT:1;        /* [6] */
      __IO unsigned long   :1;                      /* [7] */
      __IO unsigned long   EP0_INT:1;               /* [8] */
      __IO unsigned long   EP1_INT:1;               /* [9] */
      __IO unsigned long   EP2_INT:1;               /* [10] */
      __IO unsigned long   EP3_INT:1;               /* [11] */
      __IO unsigned long   EP4_INT:1;               /* [12] */
      __IO unsigned long   EP5_INT:1;               /* [13] */
      __IO unsigned long   EP6_INT:1;               /* [14] */
      __IO unsigned long   EP7_INT:1;               /* [15] */
      __IO unsigned long   EP8_INT:1;               /* [16] */
      __IO unsigned long   EP9_INT:1;               /* [17] */
      __IO unsigned long   EP10_INT:1;              /* [18] */
      __IO unsigned long   EP11_INT:1;              /* [19] */
      __IO unsigned long   EP12_INT:1;              /* [20] */
      __IO unsigned long   EP13_INT:1;              /* [21] */
      __IO unsigned long   EP14_INT:1;              /* [22] */
      __IO unsigned long   EP15_INT:1;              /* [23] */
      __IO unsigned long   :8;                      /* [24:31] */
    } BIT;
  } USB_INT_STA;
} EPC_USB_INT_STA_Type;

/* EPC_USB_INT_STA mask bits */
#define EPC_USB_INT_STA_RSUM_INT_BIT            (1 << 1)
#define EPC_USB_INT_STA_SPND_INT_BIT            (1 << 2)
#define EPC_USB_INT_STA_USB_RST_INT_BIT         (1 << 3)
#define EPC_USB_INT_STA_SOF_INT_BIT             (1 << 4)
#define EPC_USB_INT_STA_SOF_ERROR_INT_BIT       (1 << 5)
#define EPC_USB_INT_STA_SPEED_MODE_RST_INT_BIT  (1 << 6)
#define EPC_USB_INT_STA_EP0_INT_BIT             (1 << 8)
#define EPC_USB_INT_STA_EP1_INT_BIT             (1 << 9)
#define EPC_USB_INT_STA_EP2_INT_BIT             (1 << 10)
#define EPC_USB_INT_STA_EP3_INT_BIT             (1 << 11)
#define EPC_USB_INT_STA_EP4_INT_BIT             (1 << 12)
#define EPC_USB_INT_STA_EP5_INT_BIT             (1 << 13)
#define EPC_USB_INT_STA_EP6_INT_BIT             (1 << 14)
#define EPC_USB_INT_STA_EP7_INT_BIT             (1 << 15)
#define EPC_USB_INT_STA_EP8_INT_BIT             (1 << 16)
#define EPC_USB_INT_STA_EP9_INT_BIT             (1 << 17)
#define EPC_USB_INT_STA_EP10_INT_BIT            (1 << 18)
#define EPC_USB_INT_STA_EP11_INT_BIT            (1 << 19)
#define EPC_USB_INT_STA_EP12_INT_BIT            (1 << 20)
#define EPC_USB_INT_STA_EP13_INT_BIT            (1 << 21)
#define EPC_USB_INT_STA_EP14_INT_BIT            (1 << 22)
#define EPC_USB_INT_STA_EP15_INT_BIT            (1 << 23)

typedef struct
{
  union                                             /* Offset=0x0024 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :1;                      /* [0] */
      __IO unsigned long   RSUM_EN:1;               /* [1] */
      __IO unsigned long   SPND_EN:1;               /* [2] */
      __IO unsigned long   USB_RST_EN:1;            /* [3] */
      __IO unsigned long   SOF_EN:1;                /* [4] */
      __IO unsigned long   SOF_ERROR_EN:1;          /* [5] */
      __IO unsigned long   SPEED_MODE_EN:1;         /* [6] */
      __IO unsigned long   :1;                      /* [7] */
      __IO unsigned long   EP0_EN:1;                /* [8] */
      __IO unsigned long   EP1_EN:1;                /* [9] */
      __IO unsigned long   EP2_EN:1;                /* [10] */
      __IO unsigned long   EP3_EN:1;                /* [11] */
      __IO unsigned long   EP4_EN:1;                /* [12] */
      __IO unsigned long   EP5_EN:1;                /* [13] */
      __IO unsigned long   EP6_EN:1;                /* [14] */
      __IO unsigned long   EP7_EN:1;                /* [15] */
      __IO unsigned long   EP8_EN:1;                /* [16] */
      __IO unsigned long   EP9_EN:1;                /* [17] */
      __IO unsigned long   EP10_EN:1;               /* [18] */
      __IO unsigned long   EP11_EN:1;               /* [19] */
      __IO unsigned long   EP12_EN:1;               /* [20] */
      __IO unsigned long   EP13_EN:1;               /* [21] */
      __IO unsigned long   EP14_EN:1;               /* [22] */
      __IO unsigned long   EP15_EN:1;               /* [23] */
      __IO unsigned long   :8;                      /* [24:31] */
    } BIT;
  } USB_INT_ENA;
} EPC_USB_INT_ENA_Type;

typedef struct
{
  union                                            /* Offset=0x0028 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP0_ONAK:1;              /* [0] */
      __IO unsigned long   EP0_INAK:1;              /* [1] */
      __IO unsigned long   EP0_STL:1;               /* [2] */
      __IO unsigned long   EP0_PERR_NAK_CLR:1;      /* [3] */
      __IO unsigned long   EP0_INAK_EN:1;           /* [4] */
      __IO unsigned long   EP0_DW:2;                /* [5:6] */
      __IO unsigned long   EP0_DEND:1;              /* [7] */
      __IO unsigned long   EP0_BCLR:1;              /* [8] */
      __IO unsigned long   EP0_PIDCLR:1;            /* [9] */
      __IO unsigned long   :6;                      /* [10:15] */
      __IO unsigned long   EP0_AUTO:1;              /* [16] */
      __IO unsigned long   EP0_OVERSEL:1;           /* [17] */
      __IO unsigned long   EP0_STGSEL:1;            /* [18] */
      __IO unsigned long   :13;                     /* [19:31] */
    } BIT;
  } EP0_CONTROL;
} EPC_EP0_CONTROL_Type;

#define EPC_EP0_CONTROL_EP0_INAK_BIT    (1<<1)
#define EPC_EP0_CONTROL_EP0_INAK_EN_BIT (1<<4)
#define EPC_EP0_CONTROL_EP0_DEND_BIT    (1<<7)
#define EPC_EP0_CONTROL_EP0_BCLR_BIT    (1<<8)

typedef struct
{
  union                                            /* Offset=0x002C : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SETUP_INT:1;             /* [0] */
      __IO unsigned long   STG_START_INT:1;         /* [1] */
      __IO unsigned long   STG_END_INT:1;           /* [2] */
      __IO unsigned long   EP0_STALL_INT:1;         /* [3] */
      __IO unsigned long   EP0_IN_INT:1;            /* [4] */
      __IO unsigned long   EP0_OUT_INT:1;           /* [5] */
      __IO unsigned long   EP0_OUT_OR_INT:1;        /* [6] */
      __IO unsigned long   EP0_OUT_NULL_INT:1;      /* [7] */
      __IO unsigned long   EP0_IN_EMPTY:1;          /* [8] */
      __IO unsigned long   EP0_IN_FULL:1;           /* [9] */
      __IO unsigned long   EP0_IN_DATA:1;           /* [10] */
      __IO unsigned long   EP0_IN_NAK_INT:1;        /* [11] */
      __IO unsigned long   EP0_OUT_EMPTY:1;         /* [12] */
      __IO unsigned long   EP0_OUT_FULL:1;          /* [13] */
      __IO unsigned long   EP0_OUT_NULL:1;          /* [14] */
      __IO unsigned long   EP0_OUT_NAK_INT:1;       /* [15] */
      __IO unsigned long   EP0_PERR_NAK_INT:1;      /* [16] */
      __IO unsigned long   EP0_PERR_NAK:1;          /* [17] */
      __IO unsigned long   EP0_PID:1;               /* [18] */
      __IO unsigned long   :13;                     /* [19:31] */
    } BIT;
  } EP0_STATUS;
} EPC_EP0_STATUS_Type;

/* EP0_STATUS mask bits */
#define EPC_EP0_STATUS_SETUP_INT_BIT            (1 << 0)
#define EPC_EP0_STATUS_STG_START_INT_BIT        (1 << 1)
#define EPC_EP0_STATUS_STG_END_INT_BIT          (1 << 2)
#define EPC_EP0_STATUS_EP0_STALL_INT_BIT        (1 << 3)
#define EPC_EP0_STATUS_EP0_IN_INT_BIT           (1 << 4)
#define EPC_EP0_STATUS_EP0_OUT_INT_BIT          (1 << 5)
#define EPC_EP0_STATUS_EP0_OUT_OR_INT_BIT       (1 << 6)
#define EPC_EP0_STATUS_EP0_OUT_NULL_INT_BIT     (1 << 7)
#define EPC_EP0_STATUS_EP0_IN_EMPTY_BIT         (1 << 8)
#define EPC_EP0_STATUS_EP0_IN_FULL_BIT          (1 << 9)
#define EPC_EP0_STATUS_EP0_IN_DATA_BIT          (1 << 10)
#define EPC_EP0_STATUS_EP0_IN_NAK_INT_BIT       (1 << 11)
#define EPC_EP0_STATUS_EP0_OUT_EMPTY_BIT        (1 << 12)
#define EPC_EP0_STATUS_EP0_OUT_FULL_BIT         (1 << 13)
#define EPC_EP0_STATUS_EP0_OUT_NULL_BIT         (1 << 14)
#define EPC_EP0_STATUS_EP0_OUT_NAK_INT_BIT      (1 << 15)
#define EPC_EP0_STATUS_EP0_PERR_NAK_INT_BIT     (1 << 16)
#define EPC_EP0_STATUS_EP0_PERR_NAK_BIT         (1 << 17)
#define EPC_EP0_STATUS_EP0_PID_BIT              (1 << 18)

typedef struct
{
  union                                            /* Offset=0x0030 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SETUP_EN:1;              /* [0] */
      __IO unsigned long   STG_START_EN:1;          /* [1] */
      __IO unsigned long   STG_END_EN:1;            /* [2] */
      __IO unsigned long   EP0_STALL_EN:1;          /* [3] */
      __IO unsigned long   EP0_IN_EN:1;             /* [4] */
      __IO unsigned long   EP0_OUT_EN:1;            /* [5] */
      __IO unsigned long   EP0_OUT_OR_EN:1;         /* [6] */
      __IO unsigned long   EP0_OUT_NULL_EN:1;       /* [7] */
      __IO unsigned long   :3;                      /* [8:10] */
      __IO unsigned long   EP0_IN_NAK_EN:1;         /* [11] */
      __IO unsigned long   :3;                      /* [12:14] */
      __IO unsigned long   EP0_OUT_NAK_EN:1;        /* [15] */
      __IO unsigned long   EP0_PERR_NAK_EN:1;       /* [16] */
      __IO unsigned long   :15;                     /* [17:31] */
    } BIT;
  } EP0_INT_ENA;
} EPC_EP0_INT_ENA_Type;

/* EP0_INT_ENA mask bits */
#define EPC_EP0_INT_SETUP_EN_BIT            (1 << 0)
#define EPC_EP0_INT_STG_START_EN_BIT        (1 << 1)
#define EPC_EP0_INT_STG_END_EN_BIT          (1 << 2)
#define EPC_EP0_INT_EP0_STALL_EN_BIT        (1 << 3)
#define EPC_EP0_INT_EP0_IN_EN_BIT           (1 << 4)
#define EPC_EP0_INT_EP0_OUT_EN_BIT          (1 << 5)
#define EPC_EP0_INT_EP0_OUT_OR_EN_BIT       (1 << 6)
#define EPC_EP0_INT_EP0_OUT_NULL_EN_BIT     (1 << 7)
#define EPC_EP0_INT_EP0_IN_NAK_EN_BIT       (1 << 11)

typedef struct
{
  union                                             /* Offset=0x0034 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP0_LDATA:7;             /* [0:6] */
      __IO unsigned long   :25;                     /* [7:31] */
    } BIT;
  } EP0_LENGTH;
} EPC_EP0_LENGTH_Type;

typedef struct
{
  union                                             /* Offset=0x0038 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP0_RDATA1:8;            /* [0:7] */
      __IO unsigned long   EP0_RDATA2:8;            /* [8:15] */
      __IO unsigned long   EP0_RDATA3:8;            /* [16:23] */
      __IO unsigned long   EP0_RDATA4:8;            /* [24:31] */
    } BIT;
  } EP0_READ;
} EPC_EP0_READ_Type;

typedef struct
{
  union                                            /* Offset=0x003C : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EP0_WDATA1:8;            /* [0:7] */
      __IO unsigned long   EP0_WDATA2:8;            /* [8:15] */
      __IO unsigned long   EP0_WDATA3:8;            /* [16:23] */
      __IO unsigned long   EP0_WDATA4:8;            /* [24:31] */
    } BIT;
  } EP0_WRITE;
} EPC_EP0_WRITE_Type;

typedef struct
{
  union                                            /* Offset=0x0040+0x20*(m-1): EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EPm_ONAK:1;          /* [0] */
      __IO unsigned long   :1;                  /* [1] */
      __IO unsigned long   EPm_OSTL:1;          /* [2] */
      __IO unsigned long   EPm_ISTL:1;          /* [3] */
      __IO unsigned long   EPm_OSTL_EN:1;       /* [4] */
      __IO unsigned long   EPm_DW:2;            /* [5:6] */
      __IO unsigned long   EPm_DEND:1;          /* [7] */
      __IO unsigned long   EPm_CBCLR:1;         /* [8] */
      __IO unsigned long   EPm_BCLR:1;          /* [9] */
      __IO unsigned long   EPm_OPIDCLR:1;       /* [10] */
      __IO unsigned long   EPm_IPIDCLR:1;       /* [11] */
      __IO unsigned long   :4;                  /* [12:15] */
      __IO unsigned long   EPm_AUTO:1;          /* [16] */
      __IO unsigned long   EPm_OVERSEL:1;       /* [17] */
      __IO unsigned long   :6;                  /* [18:23] */
      __IO unsigned long   EPm_MODE:2;          /* [24:25] */
      __IO unsigned long   EPm_DIR0:1;          /* [26] */
      __IO unsigned long   :3;                  /* [27:29] */
      __IO unsigned long   EPm_BUF_TYPE:1;      /* [30] */
      __IO unsigned long   EPm_EN:1;            /* [31] */
    } BIT;
  } EPm_CONTROL;
} EPC_EPm_CONTROL_Type;

#define EPC_EPm_CONTROL_EPm_ONAK_BIT        (1<<0)
#define EPC_EPm_CONTROL_EPm_OSTL_BIT        (1<<2)
#define EPC_EPm_CONTROL_EPm_ISTL_BIT        (1<<3)
#define EPC_EPm_CONTROL_EPm_OSTL_EN_BIT     (1<<4)
#define EPC_EPm_CONTROL_EPm_DW_BIT          (3<<5)
#define EPC_EPm_CONTROL_EPm_DEND_BIT        (1<<7)
#define EPC_EPm_CONTROL_EPm_CBCLR_BIT       (1<<8)
#define EPC_EPm_CONTROL_EPm_BCLR_BIT        (1<<9)
#define EPC_EPm_CONTROL_EPm_DIR0_BIT        (1<<26)
#define EPC_EPm_CONTROL_EPm_BUF_TYPE_BIT    (1<<30)
#define EPC_EPm_CONTROL_EPm_EPm_EN_BIT      (1<<31)

typedef struct
{
  union                                             /* Offset=0x0044+0x20*(m-1) : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EPm_IN_EMPTY:1;          /* [0] */
      __IO unsigned long   EPm_IN_FULL:1;           /* [1] */
      __IO unsigned long   EPm_IN_DATA:1;           /* [2] */
      __IO unsigned long   EPm_IN_INT:1;            /* [3] */
      __IO unsigned long   EPm_IN_STALL_INT:1;      /* [4] */
      __IO unsigned long   EPm_IN_NAK_ERR_INT:1;    /* [5] */
      __IO unsigned long   :1;                      /* [6] */
      __IO unsigned long   EPm_IN_END_INT:1;        /* [7] */
      __IO unsigned long   EPm_ISO_UR:1;            /* [8] */
      __IO unsigned long   EPm_IN_NOTKN:1;          /* [9] */
      __IO unsigned long   EPm_IN_IPID:1;           /* [10] */
      __IO unsigned long   :5;                      /* [11:15] */
      __IO unsigned long   EPm_OUT_EMPTY:1;         /* [16] */
      __IO unsigned long   EPm_OUT_FULL:1;          /* [17] */
      __IO unsigned long   EPm_OUT_NULL_INT:1;      /* [18] */
      __IO unsigned long   EPm_OUT_INT:1;           /* [19] */
      __IO unsigned long   EPm_OUT_STALL_INT:1;     /* [20] */
      __IO unsigned long   EPm_OUT_NAK_ERR_INT:1;   /* [21] */
      __IO unsigned long   EPm_OUT_OR_INT:1;        /* [22] */
      __IO unsigned long   EPm_OUT_END_INT:1;       /* [23] */
      __IO unsigned long   EPm_ISO_CRC:1;           /* [20] */
      __IO unsigned long   :1;                      /* [25] */
      __IO unsigned long   EPm_ISO_OR:1;            /* [26] */
      __IO unsigned long   EPm_OUT_NOTKN:1;         /* [27] */
      __IO unsigned long   EPm_OPID:1;              /* [28] */
      __IO unsigned long   EPm_ISO_PIDERR:1;        /* [29] */
      __IO unsigned long   :2;                      /* [30:31] */
    } BIT;
  } EPm_STATUS;
} EPC_EPm_STATUS_Type;

/* EPm_STATUS mask bits */
#define EPC_EPm_STATUS_IN_EMPTY_BIT         (1 << 0)
#define EPC_EPm_STATUS_IN_FULL_BIT          (1 << 1)
#define EPC_EPm_STATUS_IN_DATA_BIT          (1 << 2)
#define EPC_EPm_STATUS_IN_INT_BIT           (1 << 3)
#define EPC_EPm_STATUS_IN_STALL_INT_BIT     (1 << 4)
#define EPC_EPm_STATUS_IN_NAK_ERR_INT_BIT   (1 << 5)
#define EPC_EPm_STATUS_IN_END_INT_BIT       (1 << 7)
#define EPC_EPm_STATUS_IN_IPID_BIT          (1 << 10)
#define EPC_EPm_STATUS_OUT_EMPTY_BIT        (1 << 16)
#define EPC_EPm_STATUS_OUT_FULL_BIT         (1 << 17)
#define EPC_EPm_STATUS_OUT_NULL_INT_BIT     (1 << 18)
#define EPC_EPm_STATUS_OUT_INT_BIT          (1 << 19)
#define EPC_EPm_STATUS_OUT_STALL_INT_BIT    (1 << 20)
#define EPC_EPm_STATUS_OUT_NAK_ERR_INT_BIT  (1 << 21)
#define EPC_EPm_STATUS_OUT_OR_INT_BIT       (1 << 22)
#define EPC_EPm_STATUS_OUT_END_INT_BIT      (1 << 23)
#define EPC_EPm_STATUS_OPID_BIT             (1 << 28)

typedef struct
{
  union                                             /* Offset=0x0048+0x20*(m-1) : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :3;                      /* [0:2] */
      __IO unsigned long   EPm_IN_EN:1;             /* [3] */
      __IO unsigned long   EPm_IN_STALL_EN:1;       /* [4] */
      __IO unsigned long   EPm_IN_NAK_ERR_EN:1;     /* [5] */
      __IO unsigned long   :1;                      /* [6] */
      __IO unsigned long   EPm_IN_END_EN:1;         /* [7] */
      __IO unsigned long   :10;                     /* [8:17] */
      __IO unsigned long   EPm_OUT_NULL_EN:1;       /* [18] */
      __IO unsigned long   EPm_OUT_EN:1;            /* [19] */
      __IO unsigned long   EPm_OUT_STALL_EN:1;      /* [20] */
      __IO unsigned long   EPm_OUT_NAK_ERR_EN:1;    /* [21] */
      __IO unsigned long   EPm_OUT_OR_EN:1;         /* [22] */
      __IO unsigned long   EPm_OUT_END_EN:1;        /* [23] */
      __IO unsigned long   :8;                      /* [24:31] */
    } BIT;
  } EPm_INT_ENA;
} EPC_EPm_INT_ENA_Type;

/* EPm_INT_ENA mask bits */
#define EPC_EPm_INT_EPm_IN_EN_BIT           (1 << 3)
#define EPC_EPm_INT_EPm_IN_END_EN_BIT       (1 << 7)
#define EPC_EPm_INT_EPm_OUT_EN_BIT          (1 << 19)
#define EPC_EPm_INT_EPm_OUT_END_EN_BIT      (1 << 23)

typedef struct
{
  union                                             /* Offset=0x004C+0x20*(m-1) : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EPm_DMAMODE0:1;          /* [0] */
      __IO unsigned long   :3;                      /* [1:3] */
      __IO unsigned long   EPm_DMA_EN:1;            /* [4] */
      __IO unsigned long   :3;                      /* [5:7] */
      __IO unsigned long   EPm_STOP_SET:1;          /* [8] */
      __IO unsigned long   EPm_BURST_SET:1;         /* [9] */
      __IO unsigned long   EPm_DEND_SET:1;          /* [10] */
      __IO unsigned long   EPm_STOP_MODE:1;         /* [11] */
      __IO unsigned long   :20;                     /* [12:31] */
    } BIT;
  } EPm_DMA_CTRL;
} EPC_EPm_DMA_CTRL_Type;

typedef struct
{
  union                                             /* Offset=0x0050 : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EPm_MPKT:11;             /* [0:10] */
      __IO unsigned long   :5;                      /* [11:15] */
      __IO unsigned long   EPm_BASEAD:13;           /* [16:28] */
      __IO unsigned long   :3;                      /* [29:31] */
    } BIT;
  } EPm_PCKT_ADRS;
} EPC_EPm_PCKT_ADRS_Type;

typedef struct
{
  union                                             /* Offset=0x0054+0x20*(m-1) : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EPm_LDATA:11;            /* [0:10] */
      __IO unsigned long   :5;                      /* [11:15] */
      __IO unsigned long   EPm_DMACNT:9;            /* [16:24] */
      __IO unsigned long   :7;                      /* [25:31] */
    } BIT;
  } EPm_LEN_DCNT;
} EPC_EPm_LEN_DCNT_Type;

typedef struct
{
  union                                            /* Offset=0x0058+0x20*(m-1) : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EPm_RDATA1:8;            /* [0:7] */
      __IO unsigned long   EPm_RDATA2:8;            /* [8:15] */
      __IO unsigned long   EPm_RDATA3:8;            /* [16:23] */
      __IO unsigned long   EPm_RDATA4:8;            /* [24:31] */
    } BIT;
  } EPm_READ;
} EPC_EPm_READ_Type;

typedef struct
{
  union                                            /* Offset=0x005C+0x20*(m-1) : EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EPm_WDATA1:8;            /* [0:7] */
      __IO unsigned long   EPm_WDATA2:8;            /* [8:15] */
      __IO unsigned long   EPm_WDATA3:8;            /* [16:23] */
      __IO unsigned long   EPm_WDATA4:8;            /* [24:31] */
    } BIT;
  } EPm_WRITE;
} EPC_EPm_WRITE_Type;

typedef struct
{
  union                                             /* Offset=0x0000 : AHB_EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   WAIT_MODE:1;             /* [0] */
      __IO unsigned long   :31;                     /* [1:31] */
    } BIT;
  } AHBSCTR;
} AHB_EPC_AHBSCTR_Type;

typedef struct
{
  union                                             /* Offset=0x0004 : AHB_EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :2;                      /* [0:1] */
      __IO unsigned long   WBURST_TYPE:1;           /* [2] */
      __IO unsigned long   :5;                      /* [3:7] */
      __IO unsigned long   ENDIAN_CTR:2;            /* [8:9] */
      __IO unsigned long   :2;                      /* [10:11] */
      __IO unsigned long   MCYCLE_RST:1;            /* [12] */
      __IO unsigned long   :18;                     /* [13:30] */
      __IO unsigned long   ARBITER_CTR:1;           /* [31] */
    } BIT;
  } AHBMCTR;
} AHB_EPC_AHBMCTR_Type;

typedef struct
{
  union                                             /* Offset=0x0008 : AHB_EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   ERR_MASTER:4;            /* [0:3] */
      __IO unsigned long   SBUS_ERRINT0:1;          /* [4] */
      __IO unsigned long   :1;                      /* [5] */
      __IO unsigned long   MBUS_ERRINT:1;           /* [6] */
      __IO unsigned long   :6;                      /* [7:12] */
      __IO unsigned long   VBUS_INT:1;              /* [13] */
      __IO unsigned long   :3;                      /* [14:16] */
      __IO unsigned long   DMA_ENDINT_EP1:1;        /* [17] */
      __IO unsigned long   DMA_ENDINT_EP2:1;        /* [18] */
      __IO unsigned long   DMA_ENDINT_EP3:1;        /* [19] */
      __IO unsigned long   DMA_ENDINT_EP4:1;        /* [20] */
      __IO unsigned long   DMA_ENDINT_EP5:1;        /* [21] */
      __IO unsigned long   DMA_ENDINT_EP6:1;        /* [22] */
      __IO unsigned long   DMA_ENDINT_EP7:1;        /* [23] */
      __IO unsigned long   DMA_ENDINT_EP8:1;        /* [24] */
      __IO unsigned long   DMA_ENDINT_EP9:1;        /* [25] */
      __IO unsigned long   DMA_ENDINT_EP10:1;       /* [26] */
      __IO unsigned long   DMA_ENDINT_EP11:1;       /* [27] */
      __IO unsigned long   DMA_ENDINT_EP12:1;       /* [28] */
      __IO unsigned long   DMA_ENDINT_EP13:1;       /* [29] */
      __IO unsigned long   DMA_ENDINT_EP14:1;       /* [30] */
      __IO unsigned long   DMA_ENDINT_EP15:1;       /* [31] */
    } BIT;
  } AHBBINT;
} AHB_EPC_AHBBINT_Type;

/* AHB_EPC_AHBBINT bit masks */
#define AHB_EPC_AHBBINT_SBUS_ERRINT0_BIT            (1 << 4)
#define AHB_EPC_AHBBINT_MBUS_ERRINT_BIT             (1 << 6)
#define AHB_EPC_AHBBINT_VBUS_INT_BIT                (1 << 13)

typedef struct
{
  union                                             /* Offset=0x000C : AHB_EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :4;                      /* [0:3] */
      __IO unsigned long   SBUS_ERRINT0_EN:1;       /* [4] */
      __IO unsigned long   :1;                      /* [5] */
      __IO unsigned long   MBUS_ERRINT_EN:1;        /* [6] */
      __IO unsigned long   :6;                      /* [7:12] */
      __IO unsigned long   VBUS_INT_EN:1;           /* [13] */
      __IO unsigned long   :3;                      /* [14:16] */
      __IO unsigned long   DMA_ENDINTEN_EP1:1;      /* [17] */
      __IO unsigned long   DMA_ENDINTEN_EP2:1;      /* [18] */
      __IO unsigned long   DMA_ENDINTEN_EP3:1;      /* [19] */
      __IO unsigned long   DMA_ENDINTEN_EP4:1;      /* [20] */
      __IO unsigned long   DMA_ENDINTEN_EP5:1;      /* [21] */
      __IO unsigned long   DMA_ENDINTEN_EP6:1;      /* [22] */
      __IO unsigned long   DMA_ENDINTEN_EP7:1;      /* [23] */
      __IO unsigned long   DMA_ENDINTEN_EP8:1;      /* [24] */
      __IO unsigned long   DMA_ENDINTEN_EP9:1;      /* [25] */
      __IO unsigned long   DMA_ENDINTEN_EP10:1;     /* [26] */
      __IO unsigned long   DMA_ENDINTEN_EP11:1;     /* [27] */
      __IO unsigned long   DMA_ENDINTEN_EP12:1;     /* [28] */
      __IO unsigned long   DMA_ENDINTEN_EP13:1;     /* [29] */
      __IO unsigned long   DMA_ENDINTEN_EP14:1;     /* [30] */
      __IO unsigned long   DMA_ENDINTEN_EP15:1;     /* [31] */
    } BIT;
  } AHBBINTEN;
} AHB_EPC_AHBBINTEN_Type;

typedef struct
{
  union                                             /* Offset=0x0010 : AHB_EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   EPC_RST:1;               /* [0] */
      __IO unsigned long   :1;                      /* [1] */
      __IO unsigned long   PLL_RST:1;               /* [2] */
      __IO unsigned long   :1;                      /* [3] */
      __IO unsigned long   PLL_LOCK:1;              /* [4] */
      __IO unsigned long   PLL_RESUME:1;            /* [5] */
      __IO unsigned long   :2;                      /* [6:7] */
      __IO unsigned long   VBUS_LEVEL:1;            /* [8] */
      __IO unsigned long   :3;                      /* [9:11] */
      __IO unsigned long   DIRPD:1;                 /* [12] */
      __IO unsigned long   :19;                     /* [13:31] */
    } BIT;
  } EPCTR;
} AHB_EPC_EPCTR_Type;

typedef struct
{
  union                                             /* Offset=0x0020 : AHB_EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   SS_VER:8;                /* [0:7] */
      __IO unsigned long   EPC_VER:8;               /* [8:15] */
      __IO unsigned long   AHBB_VER:8;              /* [16:23] */
      __IO unsigned long   :8;                      /* [24:31] */
    } BIT;
  } USBSSVER;
} AHB_EPC_USBSSVER_Type;

typedef struct
{
  union                                             /* Offset=0x0024 : AHB_EPC */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   DMA_AVAILABLE:16;        /* [0:15] */
      __IO unsigned long   EP_AVAILABLE:16;         /* [16:31] */
    } BIT;
  } USBSSCONF;
} AHB_EPC_USBSSCONF_Type;

#endif  /* End R_USB_RZN1_REG_DEFS_H__ */
