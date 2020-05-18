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
 **       for RZN1 TIMER1
 **
 **       revision 0.20 (2.Nov.2017)
 **
 **********************************************************************************************************************/
#ifndef __TIMER_SFR__DEFINE_HEADER__
#define __TIMER_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : TIMER
 **********************************************************************************************************************/
typedef struct
{
  union                                            /* Offset=0x0000 : rTimerLoadCount_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerLoadCount:16;                         /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerLoadCount_0;
  union                                            /* Offset=0x0004 : rTimerCurrentCount_0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerCurrentCount:16;                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerCurrentCount_0;
  union                                            /* Offset=0x0008 : rTimerControl_0 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerPrescaler:1;                          /* [0] */
      __IO unsigned long   bTimerMode:1;                               /* [1] */
      __IO unsigned long   bTimerEnable:1;                             /* [2] */
      __IO unsigned long   bTimerMaskInt:1;                            /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rTimerControl_0;
  union                                            /* Offset=0x000C : rTimerClearInt_0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerClearInt:1;                           /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerClearInt_0;
  union                                            /* Offset=0x0010 : rTimerStatusInt0_0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt0:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt0_0;
  union                                            /* Offset=0x0014 : rTimerStatusInt1_0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt1:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt1_0;
  char                     wk_0018[0x0008];
  union                                            /* Offset=0x0020 : rTimerLoadCount_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerLoadCount:16;                         /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerLoadCount_1;
  union                                            /* Offset=0x0024 : rTimerCurrentCount_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerCurrentCount:16;                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerCurrentCount_1;
  union                                            /* Offset=0x0028 : rTimerControl_1 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerPrescaler:1;                          /* [0] */
      __IO unsigned long   bTimerMode:1;                               /* [1] */
      __IO unsigned long   bTimerEnable:1;                             /* [2] */
      __IO unsigned long   bTimerMaskInt:1;                            /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rTimerControl_1;
  union                                            /* Offset=0x002C : rTimerClearInt_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerClearInt:1;                           /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerClearInt_1;
  union                                            /* Offset=0x0030 : rTimerStatusInt0_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt0:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt0_1;
  union                                            /* Offset=0x0034 : rTimerStatusInt1_1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt1:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt1_1;
  char                     wk_0038[0x0008];
  union                                            /* Offset=0x0040 : rTimerLoadCount_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerLoadCount:16;                         /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerLoadCount_2;
  union                                            /* Offset=0x0044 : rTimerCurrentCount_2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerCurrentCount:16;                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerCurrentCount_2;
  union                                            /* Offset=0x0048 : rTimerControl_2 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerPrescaler:1;                          /* [0] */
      __IO unsigned long   bTimerMode:1;                               /* [1] */
      __IO unsigned long   bTimerEnable:1;                             /* [2] */
      __IO unsigned long   bTimerMaskInt:1;                            /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rTimerControl_2;
  union                                            /* Offset=0x004C : rTimerClearInt_2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerClearInt:1;                           /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerClearInt_2;
  union                                            /* Offset=0x0050 : rTimerStatusInt0_2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt0:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt0_2;
  union                                            /* Offset=0x0054 : rTimerStatusInt1_2 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt1:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt1_2;
  char                     wk_0058[0x0008];
  union                                            /* Offset=0x0060 : rTimerLoadCount_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerLoadCount:16;                         /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerLoadCount_3;
  union                                            /* Offset=0x0064 : rTimerCurrentCount_3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerCurrentCount:16;                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerCurrentCount_3;
  union                                            /* Offset=0x0068 : rTimerControl_3 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerPrescaler:1;                          /* [0] */
      __IO unsigned long   bTimerMode:1;                               /* [1] */
      __IO unsigned long   bTimerEnable:1;                             /* [2] */
      __IO unsigned long   bTimerMaskInt:1;                            /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rTimerControl_3;
  union                                            /* Offset=0x006C : rTimerClearInt_3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerClearInt:1;                           /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerClearInt_3;
  union                                            /* Offset=0x0070 : rTimerStatusInt0_3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt0:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt0_3;
  union                                            /* Offset=0x0074 : rTimerStatusInt1_3 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt1:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt1_3;
  char                     wk_0078[0x0008];
  union                                            /* Offset=0x0080 : rTimerLoadCount_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerLoadCount:16;                         /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerLoadCount_4;
  union                                            /* Offset=0x0084 : rTimerCurrentCount_4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerCurrentCount:16;                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerCurrentCount_4;
  union                                            /* Offset=0x0088 : rTimerControl_4 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerPrescaler:1;                          /* [0] */
      __IO unsigned long   bTimerMode:1;                               /* [1] */
      __IO unsigned long   bTimerEnable:1;                             /* [2] */
      __IO unsigned long   bTimerMaskInt:1;                            /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rTimerControl_4;
  union                                            /* Offset=0x008C : rTimerClearInt_4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerClearInt:1;                           /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerClearInt_4;
  union                                            /* Offset=0x0090 : rTimerStatusInt0_4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt0:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt0_4;
  union                                            /* Offset=0x0094 : rTimerStatusInt1_4 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt1:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt1_4;
  char                     wk_0098[0x0008];
  union                                            /* Offset=0x00A0 : rTimerLoadCount_5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerLoadCount:16;                         /* [15:0] */
      __IO unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerLoadCount_5;
  union                                            /* Offset=0x00A4 : rTimerCurrentCount_5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerCurrentCount:16;                      /* [15:0] */
      __I  unsigned long   :16;                                        /* [31:16] */
    } BIT;
  } rTimerCurrentCount_5;
  union                                            /* Offset=0x00A8 : rTimerControl_5 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerPrescaler:1;                          /* [0] */
      __IO unsigned long   bTimerMode:1;                               /* [1] */
      __IO unsigned long   bTimerEnable:1;                             /* [2] */
      __IO unsigned long   bTimerMaskInt:1;                            /* [3] */
      __IO unsigned long   :28;                                        /* [31:4] */
    } BIT;
  } rTimerControl_5;
  union                                            /* Offset=0x00AC : rTimerClearInt_5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerClearInt:1;                           /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerClearInt_5;
  union                                            /* Offset=0x00B0 : rTimerStatusInt0_5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt0:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt0_5;
  union                                            /* Offset=0x00B4 : rTimerStatusInt1_5 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt1:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt1_5;
  char                     wk_00B8[0x0008];
  union                                            /* Offset=0x00C0 : rTimerLoadCount_6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerLoadCount:32;                         /* [31:0] */
    } BIT;
  } rTimerLoadCount_6;
  union                                            /* Offset=0x00C4 : rTimerCurrentCount_6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerCurrentCount:32;                      /* [31:0] */
    } BIT;
  } rTimerCurrentCount_6;
  union                                            /* Offset=0x00C8 : rTimerControl_6 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerPrescaler:1;                          /* [0] */
      __IO unsigned long   bTimerMode:1;                               /* [1] */
      __IO unsigned long   bTimerEnable:1;                             /* [2] */
      __IO unsigned long   bTimerMaskInt:1;                            /* [3] */
      __IO unsigned long   bTimerDMAEnable:1;                          /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rTimerControl_6;
  union                                            /* Offset=0x00CC : rTimerClearInt_6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerClearInt:1;                           /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerClearInt_6;
  union                                            /* Offset=0x00D0 : rTimerStatusInt0_6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt0:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt0_6;
  union                                            /* Offset=0x00D4 : rTimerStatusInt1_6 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt1:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt1_6;
  char                     wk_00D8[0x0008];
  union                                            /* Offset=0x00E0 : rTimerLoadCount_7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerLoadCount:32;                         /* [31:0] */
    } BIT;
  } rTimerLoadCount_7;
  union                                            /* Offset=0x00E4 : rTimerCurrentCount_7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerCurrentCount:32;                      /* [31:0] */
    } BIT;
  } rTimerCurrentCount_7;
  union                                            /* Offset=0x00E8 : rTimerControl_7 */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   bTimerPrescaler:1;                          /* [0] */
      __IO unsigned long   bTimerMode:1;                               /* [1] */
      __IO unsigned long   bTimerEnable:1;                             /* [2] */
      __IO unsigned long   bTimerMaskInt:1;                            /* [3] */
      __IO unsigned long   bTimerDMAEnable:1;                          /* [4] */
      __IO unsigned long   :27;                                        /* [31:5] */
    } BIT;
  } rTimerControl_7;
  union                                            /* Offset=0x00EC : rTimerClearInt_7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerClearInt:1;                           /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerClearInt_7;
  union                                            /* Offset=0x00F0 : rTimerStatusInt0_7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt0:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt0_7;
  union                                            /* Offset=0x00F4 : rTimerStatusInt1_7 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerStatusInt1:1;                         /* [0] */
      __I  unsigned long   :31;                                        /* [31:1] */
    } BIT;
  } rTimerStatusInt1_7;
  char                     wk_00F8[0x0008];
  union                                            /* Offset=0x0100 : rTimerAllClearInt */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerAllClearInt:8;                        /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rTimerAllClearInt;
  union                                            /* Offset=0x0104 : rTimerAllStatusInt0 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerAllStatusInt0:8;                      /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rTimerAllStatusInt0;
  union                                            /* Offset=0x0108 : rTimerAllStatusInt1 */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   bTimerAllStatusInt1:8;                      /* [7:0] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rTimerAllStatusInt1;
  union                                            /* Offset=0x010C : rTimer_DMA_Pending */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :6;                                         /* [5:0] */
      __I  unsigned long   bTimer_DMA_Running_6:1;                     /* [6] */
      __I  unsigned long   bTimer_DMA_Running_7:1;                     /* [7] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rTimer_DMA_Pending;
  union                                            /* Offset=0x0110 : rTimer_DMA_PendingOvf */
  {
    __I  unsigned long     LONG;
    struct
    {
      __I  unsigned long   :6;                                         /* [5:0] */
      __I  unsigned long   bTimer_DMA_RunningOvf_6:1;                  /* [6] */
      __I  unsigned long   bTimer_DMA_RunningOvf_7:1;                  /* [7] */
      __I  unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rTimer_DMA_PendingOvf;
  union                                            /* Offset=0x0114 : rTimer_DMA_PendingClrOvf */
  {
    __IO unsigned long     LONG;
    struct
    {
      __IO unsigned long   :6;                                         /* [5:0] */
      __IO unsigned long   bTimer_DMA_RunnningClrOvf_6:1;              /* [6] */
      __IO unsigned long   bTimer_DMA_RunningClrOvf_7:1;               /* [7] */
      __IO unsigned long   :24;                                        /* [31:8] */
    } BIT;
  } rTimer_DMA_PendingClrOvf;
} TIMER_Type;
#endif  /* End of __TIMER_SFR__DEFINE_HEADER__ */
