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
 **       for RZN1 HWRTOS_GMAC
 **
 **       revision 0.10
 **
 **********************************************************************************************************************/
#ifndef __HWRTOS_GMAC_SFR__DEFINE_HEADER__
#define __HWRTOS_GMAC_SFR__DEFINE_HEADER__

/***********************************************************************************************************************
 ** Module : HWRTOS_GMAC
 **********************************************************************************************************************/
typedef struct
{
         unsigned long    RESERVED0[3];                /*!< 0x0000 - 0x000F : Reserved                          */
    __IO unsigned long    GMAC_TXID;                    /*!< 0x000C : TXID                                      */
    __IO unsigned long    GMAC_TXRESULT;                /*!< 0x0010 : TX Result                                 */
         unsigned long    RESERVED1[3];                /*!< 0x0014 - 0x001F : Reserved                          */
    __IO unsigned long    GMAC_MODE;                    /*!< 0x0020 : MODE                                      */
    __IO unsigned long    GMAC_RXMODE;                /*!< 0x0024 : RX MODE                                     */
    __IO unsigned long    GMAC_TXMODE;                /*!< 0x0028 : TX MODE                                     */
         unsigned long    RESERVED2C;                    /*!< 0x002C : Reserved                                 */
    __IO unsigned long    GMAC_RESET;                    /*!< 0x0030 : RESET                                    */
         unsigned long    RESERVED2[19];                /*!< 0x0034 - 0x007F : Reserved                         */
    __IO unsigned long    GMAC_PAUSE1;                /*!< 0x0080 : Pause Packet 1                              */
    __IO unsigned long    GMAC_PAUSE2;                /*!< 0x0084 : Pause Packet 2                              */
    __IO unsigned long    GMAC_PAUSE3;                /*!< 0x0088 : Pause Packet 3                              */
    __IO unsigned long    GMAC_PAUSE4;                /*!< 0x008C : Pause Packet 4                              */
    __IO unsigned long    GMAC_PAUSE5;                /*!< 0x0090 : Pause Packet 5                              */
         unsigned long    RESERVED3[1];                /*!< 0x0094 : Reserved                                   */
    __IO unsigned long    GMAC_FLWCTL;                /*!< 0x0098 : RX Flow Control                             */
    __IO unsigned long    GMAC_PAUSPKT;                /*!< 0x009C : Pause PKT                                  */
    __IO unsigned long    GMAC_MIIM;                    /*!< 0x00A0 : MIIM                                      */
         unsigned long    RESERVED4[23];                /*!< 0x00A4 - 0x00AF : Reserved                         */
    __IO unsigned long    GMAC_ADR1A;                    /*!< 0x0100 : MAC Address 1A                           */
    __IO unsigned long    GMAC_ADR1B;                    /*!< 0x0104 : MAC Address 1B                           */
    __IO unsigned long    GMAC_ADR2A;                    /*!< 0x0108 : MAC Address 2A                           */
    __IO unsigned long    GMAC_ADR2B;                    /*!< 0x010c : MAC Address 2B                           */
    __IO unsigned long    GMAC_ADR3A;                    /*!< 0x0110 : MAC Address 3A                           */
    __IO unsigned long    GMAC_ADR3B;                    /*!< 0x0114 : MAC Address 3B                           */
    __IO unsigned long    GMAC_ADR4A;                    /*!< 0x0118 : MAC Address 4A                           */
    __IO unsigned long    GMAC_ADR4B;                    /*!< 0x011c : MAC Address 4B                           */
    __IO unsigned long    GMAC_ADR5A;                    /*!< 0x0120 : MAC Address 5A                           */
    __IO unsigned long    GMAC_ADR5B;                    /*!< 0x0124 : MAC Address 5B                           */
    __IO unsigned long    GMAC_ADR6A;                    /*!< 0x0128 : MAC Address 6A                           */
    __IO unsigned long    GMAC_ADR6B;                    /*!< 0x012c : MAC Address 6B                           */
    __IO unsigned long    GMAC_ADR7A;                    /*!< 0x0130 : MAC Address 7A                           */
    __IO unsigned long    GMAC_ADR7B;                    /*!< 0x0134 : MAC Address 7B                           */
    __IO unsigned long    GMAC_ADR8A;                    /*!< 0x0138 : MAC Address 8A                           */
    __IO unsigned long    GMAC_ADR8B;                    /*!< 0x013c : MAC Address 8B                           */
    __IO unsigned long    GMAC_ADR9A;                    /*!< 0x0140 : MAC Address 9A                           */
    __IO unsigned long    GMAC_ADR9B;                    /*!< 0x0144 : MAC Address 9B                           */
    __IO unsigned long    GMAC_ADR10A;                /*!< 0x0148 : MAC Address 10A                             */
    __IO unsigned long    GMAC_ADR10B;                /*!< 0x014c : MAC Address 10B                             */
    __IO unsigned long    GMAC_ADR11A;                /*!< 0x0150 : MAC Address 11A                             */
    __IO unsigned long    GMAC_ADR11B;                /*!< 0x0154 : MAC Address 11B                             */
    __IO unsigned long    GMAC_ADR12A;                /*!< 0x0158 : MAC Address 12A                             */
    __IO unsigned long    GMAC_ADR12B;                /*!< 0x015c : MAC Address 12B                             */
    __IO unsigned long    GMAC_ADR13A;                /*!< 0x0160 : MAC Address 13A                             */
    __IO unsigned long    GMAC_ADR13B;                /*!< 0x0164 : MAC Address 13B                             */
    __IO unsigned long    GMAC_ADR14A;                /*!< 0x0168 : MAC Address 14A                             */
    __IO unsigned long    GMAC_ADR14B;                /*!< 0x016c : MAC Address 14B                             */
    __IO unsigned long    GMAC_ADR15A;                /*!< 0x0170 : MAC Address 15A                             */
    __IO unsigned long    GMAC_ADR15B;                /*!< 0x0174 : MAC Address 15B                             */
    __IO unsigned long    GMAC_ADR16A;                /*!< 0x0178 : MAC Address 16A                             */
    __IO unsigned long    GMAC_ADR16B;                /*!< 0x017c : MAC Address 16B                             */
         unsigned long    RESERVED5[32];                /*!< 0x0180 - 0x01FF : Reserved                         */
    __IO unsigned long    GMAC_RXFIFO;                /*!< 0x0200 : RX FIFO                                     */
    __IO unsigned long    GMAC_TXFIFO;                /*!< 0x0204 : TX FIFO                                     */
    __IO unsigned long    GMAC_ACC;                    /*!< 0x0208 : TCPIP Acc                                  */
         unsigned long    RESERVED6;                    /*!< 0x020c : Reserved                                  */
         unsigned long    RESERVED7[4];                /*!< 0x0210 - 0x21F : Reserved                           */
    __IO unsigned long    GMAC_RXMAC_ENA;                /*!< 0x0220 : RXMAC Enable                             */
         unsigned long    RESERVED8[3];                /*!< 0x0224 - 0x022F : Reserved                          */
         unsigned long    RESERVED9[948];                /*!< 0x0230 - 0x10FF : Reserved                        */
    // ------ Buffer ID ------
    __IO unsigned long    BUFID;                        /*!< 0x1100 : BUFID register                            */
} HWRTOS_GMAC_Type;
#endif  /* End of __HWRTOS_GMAC_SFR__DEFINE_HEADER__ */
