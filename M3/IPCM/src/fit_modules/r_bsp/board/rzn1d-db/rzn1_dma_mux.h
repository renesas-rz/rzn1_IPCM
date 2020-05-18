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
 * $Revision: 1298 $
 * $Date: 2019-02-25 10:17:29 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  rzn1_dma_mux.h
 * Description  :  Configures the DMA handshaking source multiplexing
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef __RZN1_DMA_MUX_H__
#define __RZN1_DMA_MUX_H__

#include "platform.h"
#include "errcodes.h"

#define DMA_MUX_DMA_BIT         5
#define DMA_MUX_SRC_REQ_BIT     1
#define DMA_MUX_REQ_VAL_BIT     0

#define DMA_MUX_DMA_MASK        (0x01)
#define DMA_MUX_SRC_REQ_MASK    (0x0F)
#define DMA_MUX_REQ_VAL_MASK    (0x01)

#define DMA_MUX_DMAC(_dmac) \
    ((_dmac) << DMA_MUX_DMA_BIT)
#define DMA_MUX_SRC_REQ(_src) \
    ((_src) << DMA_MUX_SRC_REQ_BIT)
#define DMA_MUX_VAL(_req) \
    ((_req) << DMA_MUX_REQ_VAL_BIT)

#define DMA_MUX_FUNCTION(_dmac, _src, _req) \
        (DMA_MUX_DMAC(_dmac) | DMA_MUX_SRC_REQ(_src) | DMA_MUX_VAL(_req))

#define DMA_Timer2_SubTimer7_REQ            (DMA_MUX_FUNCTION(1,15,0))    /* PG_DMA_Request[26] */
#define DMA_ADC_DMA_Request_1_REQ           (DMA_MUX_FUNCTION(1,15,1))    /* ADC_DMA_Request[1] */
#define DMA_SERCOS_DIV_CLK_IP_REQ_3         (DMA_MUX_FUNCTION(1,14,0))    /* ETH_DMA_Request[6] */
#define DMA_SERCOS_DIV_CLK_IP_REQ_2         (DMA_MUX_FUNCTION(1,6,0))    /* ETH_DMA_Request[6] */
#define DMA_SERCOS_DIV_CLK_IP_REQ_1         (DMA_MUX_FUNCTION(0,14,0))    /* ETH_DMA_Request[6] */
#define DMA_SERCOS_DIV_CLK_IP_REQ_0         (DMA_MUX_FUNCTION(0,6,0))    /* ETH_DMA_Request[6] */
#define DMA_ADC_DMA_Request_0_REQ           (DMA_MUX_FUNCTION(1,14,1))    /* ADC_DMA_Request[0] */
#define DMA_SERCOS_CON_CLK_IP_REQ_3         (DMA_MUX_FUNCTION(1,13,0))    /* ETH_DMA_Request[5] */
#define DMA_SERCOS_CON_CLK_IP_REQ_2         (DMA_MUX_FUNCTION(1,5,0))    /* ETH_DMA_Request[5] */
#define DMA_SERCOS_CON_CLK_IP_REQ_1         (DMA_MUX_FUNCTION(0,13,0))    /* ETH_DMA_Request[5] */
#define DMA_SERCOS_CON_CLK_IP_REQ_0         (DMA_MUX_FUNCTION(0,5,0))    /* ETH_DMA_Request[5] */
#define DMA_MSEBI_DMA_Request_3_REQ         (DMA_MUX_FUNCTION(1,13,1))    /* MSEBI_DMA_Request[3] */
#define DMA_GMAC1_PTP_AUX_TS_TRIG_REQ_3     (DMA_MUX_FUNCTION(1,12,0))    /* ETH_DMA_Request[4] */
#define DMA_GMAC1_PTP_AUX_TS_TRIG_REQ_2     (DMA_MUX_FUNCTION(1,4,0))    /* ETH_DMA_Request[4] */
#define DMA_GMAC1_PTP_AUX_TS_TRIG_REQ_1     (DMA_MUX_FUNCTION(0,12,0))    /* ETH_DMA_Request[4] */
#define DMA_GMAC1_PTP_AUX_TS_TRIG_REQ_0     (DMA_MUX_FUNCTION(0,4,0))    /* ETH_DMA_Request[4] */
#define DMA_MSEBI_DMA_Request_2_REQ         (DMA_MUX_FUNCTION(1,12,1))    /* MSEBI_DMA_Request[2] */
#define DMA_GMAC1_PTP_PPS1_REQ_3            (DMA_MUX_FUNCTION(1,11,0))    /* ETH_DMA_Request[3] */
#define DMA_GMAC1_PTP_PPS1_REQ_2            (DMA_MUX_FUNCTION(1,3,0))    /* ETH_DMA_Request[3] */
#define DMA_GMAC1_PTP_PPS1_REQ_1            (DMA_MUX_FUNCTION(0,11,0))    /* ETH_DMA_Request[3] */
#define DMA_GMAC1_PTP_PPS1_REQ_0            (DMA_MUX_FUNCTION(0,3,0))    /* ETH_DMA_Request[3] */
#define DMA_MSEBI_DMA_Request_1_REQ         (DMA_MUX_FUNCTION(1,11,1))    /* MSEBI_DMA_Request[1] */
#define DMA_GMAC1_PTP_PPS0_REQ_3            (DMA_MUX_FUNCTION(1,10,0))    /* ETH_DMA_Request[2] */
#define DMA_GMAC1_PTP_PPS0_REQ_2            (DMA_MUX_FUNCTION(1,2,0))    /* ETH_DMA_Request[2] */
#define DMA_GMAC1_PTP_PPS0_REQ_1            (DMA_MUX_FUNCTION(0,10,0))    /* ETH_DMA_Request[2] */
#define DMA_GMAC1_PTP_PPS0_REQ_0            (DMA_MUX_FUNCTION(0,2,0))    /* ETH_DMA_Request[2] */
#define DMA_MSEBI_DMA_Request_0_REQ         (DMA_MUX_FUNCTION(1,10,1))    /* MSEBI_DMA_Request[0] */
#define DMA_EtherCAT_SYNC1_SERCOS_INT2_REQ_3    (DMA_MUX_FUNCTION(1,9,0))    /* ETH_DMA_Request[1] */
#define DMA_EtherCAT_SYNC1_SERCOS_INT2_REQ_2    (DMA_MUX_FUNCTION(1,1,0))    /* ETH_DMA_Request[1] */
#define DMA_EtherCAT_SYNC1_SERCOS_INT2_REQ_1    (DMA_MUX_FUNCTION(0,9,0))    /* ETH_DMA_Request[1] */
#define DMA_EtherCAT_SYNC1_SERCOS_INT2_REQ_0    (DMA_MUX_FUNCTION(0,1,0))    /* ETH_DMA_Request[1] */
#define DMA_EtherCAT_SYNC0_SERCOS_INT1_REQ_3    (DMA_MUX_FUNCTION(1,8,0))    /* ETH_DMA_Request[0] */
#define DMA_EtherCAT_SYNC0_SERCOS_INT1_REQ_2    (DMA_MUX_FUNCTION(1,0,0))    /* ETH_DMA_Request[0] */
#define DMA_EtherCAT_SYNC0_SERCOS_INT1_REQ_1    (DMA_MUX_FUNCTION(0,8,0))    /* ETH_DMA_Request[0] */
#define DMA_EtherCAT_SYNC0_SERCOS_INT1_REQ_0    (DMA_MUX_FUNCTION(0,0,0))    /* ETH_DMA_Request[0] */
#define DMA_Timer2_SubTimer6_REQ            (DMA_MUX_FUNCTION(1,7,0))    /* PG_DMA_Request[25] */
#define DMA_UART8_TX_REQ                    (DMA_MUX_FUNCTION(1,5,1))    /* PG_DMA_Request[21] */
#define DMA_UART8_RX_REQ                    (DMA_MUX_FUNCTION(1,4,1))    /* PG_DMA_Request[20] */
#define DMA_SPI6_TX_REQ                     (DMA_MUX_FUNCTION(1,3,1))    /* PG_DMA_Request[19] */
#define DMA_SPI6_RX_REQ                     (DMA_MUX_FUNCTION(1,2,1))    /* PG_DMA_Request[18] */
#define DMA_SPI5_TX_REQ                     (DMA_MUX_FUNCTION(1,1,1))    /* PG_DMA_Request[17] */
#define DMA_SPI5_RX_REQ                     (DMA_MUX_FUNCTION(1,0,1))    /* PG_DMA_Request[16] */
#define DMA_Timer1_SubTimer7_REQ            (DMA_MUX_FUNCTION(0,15,0))    /* PG_DMA_Request[24] */
#define DMA_SPI4_TX_REQ                     (DMA_MUX_FUNCTION(0,15,1))    /* PG_DMA_Request[15] */
#define DMA_SPI4_RX_REQ                     (DMA_MUX_FUNCTION(0,14,1))    /* PG_DMA_Request[14] */
#define DMA_SPI3_TX_REQ                     (DMA_MUX_FUNCTION(0,13,1))    /* PG_DMA_Request[13] */
#define DMA_SPI3_RX_REQ                     (DMA_MUX_FUNCTION(0,12,1))    /* PG_DMA_Request[12] */
#define DMA_SPI2_TX_REQ                     (DMA_MUX_FUNCTION(0,11,1))    /* PG_DMA_Request[11] */
#define DMA_SPI2_RX_REQ                     (DMA_MUX_FUNCTION(0,10,1))    /* PG_DMA_Request[10] */
#define DMA_SPI1_TX_REQ                     (DMA_MUX_FUNCTION(0,9,1))    /* PG_DMA_Request[9] */
#define DMA_SPI1_RX_REQ                     (DMA_MUX_FUNCTION(0,8,1))    /* PG_DMA_Request[8] */
#define DMA_Timer1_SubTimer6_REQ            (DMA_MUX_FUNCTION(0,7,0))    /* PG_DMA_Request[23] */
#define DMA_UART7_TX_REQ                    (DMA_MUX_FUNCTION(0,7,1))    /* PG_DMA_Request[7] */
#define DMA_UART7_RX_REQ                    (DMA_MUX_FUNCTION(0,6,1))    /* PG_DMA_Request[6] */
#define DMA_UART6_TX_REQ                    (DMA_MUX_FUNCTION(0,5,1))    /* PG_DMA_Request[5] */
#define DMA_UART6_RX_REQ                    (DMA_MUX_FUNCTION(0,4,1))    /* PG_DMA_Request[4] */
#define DMA_UART5_TX_REQ                    (DMA_MUX_FUNCTION(0,3,1))    /* PG_DMA_Request[3] */
#define DMA_UART5_RX_REQ                    (DMA_MUX_FUNCTION(0,2,1))    /* PG_DMA_Request[2] */
#define DMA_UART4_TX_REQ                    (DMA_MUX_FUNCTION(0,1,1))    /* PG_DMA_Request[1] */
#define DMA_UART4_RX_REQ                    (DMA_MUX_FUNCTION(0,0,1))    /* PG_DMA_Request[0] */

static const uint8_t DMA_MUX_CONFIG[32] = {
        /* Selected REQ */      /* Alternative REQ */
        DMA_UART4_RX_REQ,       /* DMA_EtherCAT_SYNC0_SERCOS_INT1_REQ_0 */
        DMA_UART4_TX_REQ,       /* DMA_EtherCAT_SYNC1_SERCOS_INT2_REQ_0 */
        DMA_UART5_RX_REQ,       /* DMA_GMAC1_PTP_PPS0_REQ_0 */
        DMA_UART5_TX_REQ,       /* DMA_GMAC1_PTP_PPS1_REQ_0 */
        DMA_UART6_RX_REQ,       /* DMA_GMAC1_PTP_AUX_TS_TRIG_REQ_0 */
        DMA_UART6_TX_REQ,       /* DMA_SERCOS_CON_CLK_IP_REQ_0 */
        DMA_UART7_RX_REQ,       /* DMA_SERCOS_DIV_CLK_IP_REQ_0 */
        DMA_Timer1_SubTimer6_REQ,       /* DMA_UART7_TX_REQ */
        DMA_SPI1_RX_REQ,        /* DMA_EtherCAT_SYNC0_SERCOS_INT1_REQ_1 */
        DMA_SPI1_TX_REQ,        /* DMA_EtherCAT_SYNC1_SERCOS_INT2_REQ_1 */
        DMA_SPI2_RX_REQ,        /* DMA_GMAC1_PTP_PPS0_REQ_1 */
        DMA_SPI2_TX_REQ,        /* DMA_GMAC1_PTP_PPS1_REQ_1 */
        DMA_SPI3_RX_REQ,        /* DMA_GMAC1_PTP_AUX_TS_TRIG_REQ_1 */
        DMA_SPI3_TX_REQ,        /* DMA_SERCOS_CON_CLK_IP_REQ_1 */
        DMA_SPI4_RX_REQ,        /* DMA_SERCOS_DIV_CLK_IP_REQ_1 */
        DMA_SPI4_TX_REQ,        /* DMA_Timer1_SubTimer7_REQ */
        DMA_SPI5_RX_REQ,        /* DMA_EtherCAT_SYNC0_SERCOS_INT1_REQ_2 */
        DMA_SPI5_TX_REQ,        /* DMA_EtherCAT_SYNC1_SERCOS_INT2_REQ_2 */
        DMA_SPI6_RX_REQ,        /* DMA_GMAC1_PTP_PPS0_REQ_2 */
        DMA_SPI6_TX_REQ,        /* DMA_GMAC1_PTP_PPS1_REQ_2 */
        DMA_UART8_RX_REQ,       /* DMA_GMAC1_PTP_AUX_TS_TRIG_REQ_2 */
        DMA_UART8_TX_REQ,       /* DMA_SERCOS_CON_CLK_IP_REQ_2 */
        DMA_SERCOS_DIV_CLK_IP_REQ_2,    /* Reserved */
        DMA_Timer2_SubTimer6_REQ,       /* Reserved */
        DMA_EtherCAT_SYNC0_SERCOS_INT1_REQ_3,   /* Reserved */
        DMA_EtherCAT_SYNC1_SERCOS_INT2_REQ_3,   /* Reserved */
        DMA_MSEBI_DMA_Request_0_REQ,    /* DMA_GMAC1_PTP_PPS0_REQ_3 */
        DMA_MSEBI_DMA_Request_1_REQ,    /* DMA_GMAC1_PTP_PPS1_REQ_3 */
        DMA_MSEBI_DMA_Request_2_REQ,    /* DMA_GMAC1_PTP_AUX_TS_TRIG_REQ_3 */
        DMA_MSEBI_DMA_Request_3_REQ,    /* DMA_SERCOS_CON_CLK_IP_REQ_3 */
        DMA_ADC_DMA_Request_0_REQ,      /* DMA_SERCOS_DIV_CLK_IP_REQ_3 */
        DMA_ADC_DMA_Request_1_REQ,      /* DMA_Timer2_SubTimer7_REQ */
};

ER_RET rzn1_dma_mux(void);

#endif /* __RZN1_DMA_MUX_H__ */