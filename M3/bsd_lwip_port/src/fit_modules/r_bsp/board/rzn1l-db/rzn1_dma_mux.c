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
 * $Revision: 1326 $
 * $Date: 2019-03-04 11:38:16 +0000 (Mon, 04 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  rzn1_dma_mux.c
 * Description  :  Configures the DMA handshaking source multiplexing
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#include "rzn1_dma_mux.h"
#include "r_sysctrl_rzn1_if.h"

/***********************************************************************************************************************
 *
 *  Function:       rzn1_dma_mux
 *
 *  Return value:   Error value
 *
 *  Parameters:     None
 *
 *  Description:    Configures the DMA handshaking source multiplexing
 *
 **********************************************************************************************************************/
ER_RET rzn1_dma_mux (void)
{
    uint8_t dmac_number;
    uint8_t src_req_number;
    int i;

    for (i = 0; i < 32; i++)
    {
        dmac_number = (DMA_MUX_CONFIG[i] >> DMA_MUX_DMA_BIT) & DMA_MUX_DMA_MASK;
        src_req_number = (DMA_MUX_CONFIG[i] >> DMA_MUX_SRC_REQ_BIT) & DMA_MUX_SRC_REQ_MASK;

        if ((dmac_number * 16 + src_req_number) != i)
        {
            return ER_NG;
        }
        else
        {
            R_SYSCTRL_ConfigDMAMux(DMA_MUX_CONFIG[i]);
        }
    }

    return ER_OK;
}
/***********************************************************************************************************************
 End of function rzn1_dma_mux.c
 **********************************************************************************************************************/