#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
* Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name    : eth_hwfnc.h
* Description  : Hardware Function Call driver.
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 25.08.2017 0.1      Preliminary version
*******************************************************************************/

#ifndef ETH_HWFNC_H__
#define ETH_HWFNC_H__

/******************************************************************************
Includes   <System Includes> , "Project Includes"
******************************************************************************/

/*******************************************************************************
Macro definitions
*******************************************************************************/
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#define HW_BUFFER_RELEASE_INVALID_SYSTEM_CALL   0x02
#define HW_BUFFER_RELEASE_UNDEFINED_BUFFER      0x03
#define HW_BUFFER_RELEASE_CALL_COMPLETED        0x20000000

/*******************************************************************************
Typedef definitions
*******************************************************************************/
#define UINT unsigned int

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/
/* ==== struct ==== */

/* ==== function ==== */

// ====== Buffer allocator ======
void *hwfnc_malloc(UINT size);
int hwfnc_buffer_free(UINT ptr);

void *hwfnc_longbuffer_get(UINT par);
void *hwfnc_shortbuffer_get(UINT len);
UINT hwfnc_buffer_release(UINT top);
UINT hwfnc_buffer_return(UINT top, UINT addr);
void *hwfnc_longbuffer_link(UINT src, UINT *p_sta);

// ====== HeaderEnDec ======
UINT hwfnc_gbe_enc(UINT src, UINT dst, UINT *excp);
UINT hwfnc_gbe_dec(UINT src, UINT dst, UINT *excp);
UINT hwfnc_snap_dec(UINT src, UINT dst, UINT *excp);
UINT hwfnc_ip4_enc(UINT src, UINT dst, UINT *excp);
UINT hwfnc_ip4_dec(UINT src, UINT dst, UINT *excp);
UINT hwfnc_ip6_enc(UINT src, UINT dst, UINT *excp);
UINT hwfnc_ip6_dec(UINT src, UINT dst, UINT *excp);
UINT hwfnc_tcp_enc(UINT src, UINT dst, UINT *excp);
UINT hwfnc_tcp_dec(UINT src, UINT dst, UINT *excp);
UINT hwfnc_udp_enc(UINT src, UINT dst, UINT *excp);
UINT hwfnc_udp_dec(UINT src, UINT dst, UINT *excp);
UINT hwfnc_arp_enc(UINT src, UINT dst, UINT *excp);
UINT hwfnc_arp_dec(UINT src, UINT dst, UINT *excp);
UINT hwfnc_dsc_trns(UINT src, UINT dst, UINT *excp);
UINT hwfnc_dmt(UINT src, UINT dst, UINT bytes, UINT *excp);
UINT hwfnc_dmr(UINT src, UINT dst, UINT bytes, UINT *excp);

// ====== DMAC ======
// --- MACDMA ---
UINT hwfnc_macdma_tx_start(UINT dsc, UINT llsn);
UINT hwfnc_macdma_rx_enable(UINT llsn);
UINT hwfnc_macdma_rx_disable(UINT flg);
UINT hwfnc_macdma_rx_control(UINT msk);
UINT hwfnc_macdma_tx_errstat(void);
UINT hwfnc_macdma_rx_errstat(void);

// --- INTBUFF DMA ---
/* Internal Buffer */
UINT hwfnc_intbuff_dma_start1(UINT dst, UINT src, UINT bytes, UINT llsn);
UINT hwfnc_intbuff_dma_start2(UINT ddsc, UINT sdsc, UINT llsn);

#endif	// ETH_HWFNC_H__

/* End of File */

#ifdef __cplusplus
}
#endif
