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
 * $Revision: 1477 $
 * $Date: 2019-07-19 11:51:02 +0100 (Fri, 19 Jul 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_dma_rzn1.h
 * Description  :  DMA control functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef R_DMA_RZN1_H__
#define R_DMA_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define DEFAULT_CHAN_PRIORITY (0xFF)

/***********************************************************************************************************************
 Variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/
void dma_init(void);
void dma_uninit(void);
ER_RET dma_open(uint8_t DMAC_number);
ER_RET dma_close(uint8_t DMAC_number);
void dma_setcallback(uint8_t DMAC_number, uint8_t channel,
        dma_trans_complete_callback call_back);
ER_RET dma_setchanconfig(uint8_t DMAC_number, uint8_t channel,
        DMA_CHAN_CTRL *control);
ER_RET dma_getchanconfig(uint8_t DMAC_number, uint8_t channel,
        DMA_CHAN_CTRL *control);
ER_RET dma_settransconfig(uint8_t DMAC_number, uint8_t channel,
        DMA_TRANS_CTRL *control);
ER_RET dma_gettransconfig(uint8_t DMAC_number, uint8_t channel,
        DMA_TRANS_CTRL *control);
void dma_enablechannel(uint8_t DMAC_number, uint8_t channel);
void dma_disablechannel(uint8_t DMAC_number, uint8_t channel);
void dma_playpause(uint8_t DMAC_number, uint8_t channel, bool pause);
ER_RET dma_transreq(uint8_t DMAC_number, uint8_t channel,
        DMA_TRANS_REQ_TYPE req_type);
void dma_transfer_completed(uint8_t DMAC_number, uint8_t channel);

#endif /* R_DMA_RZN1_H__ */
