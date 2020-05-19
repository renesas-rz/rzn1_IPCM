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
 * FILE         :  r_usbf_driver.h
 * Description  :  USBf Driver common definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_USBF_DRIVER_H__
#define R_USBF_DRIVER_H__

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#if USB_CPU_LPW_PP  == USB_LPWR_USE_PP
#define USB_SUSPEND_MODE  (1)
#define USB_NORMAL_MODE   (0)
#endif /* USB_CPU_LPW_PP  == USB_LPWR_USE_PP */

/***********************************************************************************************************************
 Function Prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Public Variables
 **********************************************************************************************************************/
/* r_usb_cDataIO.c */
extern uint32_t usb_gcstd_DataCnt[USB_MAX_PIPE_NO + 1u]; /* PIPEn Buffer counter */
extern uint16_t usb_gcstd_Dma0Dir; /* DMA0 direction */
extern uint16_t usb_gcstd_Dma1Dir; /* DMA1 direction */
extern uint32_t usb_gcstd_Dma0Size; /* DMA0 buffer size */
extern uint32_t usb_gcstd_Dma1Size; /* DMA1 buffer size */
extern uint16_t usb_gcstd_Dma0Fifo; /* DMA0 FIFO buffer size */
extern uint16_t usb_gcstd_Dma1Fifo; /* DMA1 FIFO buffer size */
extern uint16_t usb_gcstd_Dma0Pipe; /* DMA0 pipe number */
extern uint16_t usb_gcstd_Dma1Pipe; /* DMA1 pipe number */
extern uint8_t *usb_gcstd_DataPtr[USB_MAX_PIPE_NO + 1u]; /* PIPEn Buffer pointer(8bit) */
extern USB_UTR_t *usb_gcstd_Pipe[USB_MAX_PIPE_NO + 1u]; /* Message pipe */
extern uint16_t usb_gcstd_HsEnable; /* Hi-speed enable */

/* r_usb_pDriver.c */
extern uint16_t usb_gpstd_StallPipe[USB_MAX_PIPE_NO + 1u]; /* Stall Pipe info */
extern USB_UTR_CB_t usb_gpstd_StallCB; /* Stall Callback function */
extern uint16_t usb_gpstd_ConfigNum; /* Configuration Number */
extern uint16_t usb_gpstd_AltNum[]; /* Alternate */
extern uint16_t usb_gpstd_RemoteWakeup; /* Remote Wakeup Enable Flag */
extern uint16_t usb_gpstd_TestModeSelect; /* Test Mode Selectors */
extern uint16_t usb_gpstd_TestModeFlag; /* Test Mode Flag */
extern uint16_t usb_gpstd_EpTblIndex[2][USBF_MAX_EPS]; /* Index of Endpoint Information table */
extern uint16_t usb_gpstd_ReqType; /* Request type */
extern uint16_t usb_gpstd_ReqTypeType; /* Request type TYPE */
extern uint16_t usb_gpstd_ReqTypeRecip; /* Request type RECIPIENT */
extern uint16_t usb_gpstd_ReqRequest; /* Request */
extern uint16_t usb_gpstd_ReqValue; /* Value */
extern uint16_t usb_gpstd_ReqIndex; /* Index */
extern uint16_t usb_gpstd_ReqLength; /* Length */
extern USB_PCDREG_t usb_gpstd_Driver; /* Driver registration */
extern USB_REQUEST_t usb_gpstd_ReqReg; /* Request variable */

/***********************************************************************************************************************
 Public Functions
 **********************************************************************************************************************/
void usb_cstd_SendStart(uint16_t Pipe);
uint16_t usb_cstd_write_data(uint16_t, uint16_t);
void usb_cstd_ReceiveStart(uint16_t Pipe);
uint16_t usb_cstd_read_data(uint16_t, uint16_t);
void usb_cstd_DataEnd(uint16_t Pipe, uint16_t Status);
void usb_cstd_ForcedTermination(uint16_t Pipe, uint16_t Status);

/* r_usb_pDriver.c */
void usb_pstd_PcdTask(void);
void usb_pstd_Interrupt(EPC_INT_STATUS *epc_ints_status);
USB_ER_t usb_pstd_SetSubmitutr(USB_UTR_t *utrmsg);
void usb_pstd_ClearMem(void);
void usb_pstd_SetConfigNum(uint16_t Value);
void usb_pstd_ClearEpTblIndex(void);
uint16_t usb_pstd_GetConfigNum(void);
uint16_t usb_pstd_GetInterfaceNum(uint16_t Con_Num);
uint16_t usb_pstd_GetAlternateNum(uint16_t Con_Num, uint16_t Int_Num);
void usb_pstd_SetEpTblIndex(uint16_t Con_Num, uint16_t Int_Num,
        uint16_t Alt_Num);
uint16_t usb_pstd_ChkRemote(void);
uint8_t usb_pstd_GetCurrentPower(void);

void usb_cstd_StopClock(void);
uint16_t usb_cstd_PortSpeed(void);

uint16_t usb_cstd_GetDevsel(uint16_t Pipe);
uint16_t usb_cstd_GetPipeDir(uint16_t Pipe);
uint16_t usb_cstd_GetPipeType(uint16_t pipe);

void usb_cstd_ClrPipeCnfg(uint16_t pipe);

void usb_pstd_SetIStall(uint16_t pipe);
void usb_pstd_SetOStall(uint16_t pipe);
void usb_pstd_SetStallPipe0(void);
void usb_cstd_SetONak(uint16_t pipe);
void usb_cstd_SetONakPipe0(void);
void usb_cstd_SetINakPipe0(void);
void usb_reset_ep(uint16_t ep_num);

void usb_cstd_ClrStall_EP0(void);
void usb_cstd_ClrStall_EPm(uint16_t ep);
uint16_t usb_cstd_Epadr2Pipe(uint16_t Dir_Ep);
uint16_t usb_cstd_EpNum2PipeDir(uint16_t ep_num);
uint16_t usb_cstd_Pipe2Fport(uint16_t Pipe);
uint16_t usb_cstd_GetDeviceAddress(uint16_t Pipe);

void usb_cstd_chg_curpipe(uint16_t Pipe, uint16_t fifosel, uint16_t isel);

/* r_usb_creg_dmadtc.c */
#if USB_DMA_PP == USB_DMA_USE_PP
void usb_cstd_DfifoStopUsb(void);

void usb_cstd_DfifoInt(void);

void usb_cstd_Buf2DfifoStartDma(uint16_t, uint16_t);

void usb_cstd_Dfifo2BufStartDma(uint16_t, uint16_t, uint32_t);

extern void usb_cstd_ChkDMARecvDataCount(uint32_t crtb, uint32_t data_cnt,
        uint16_t fifobuf_size, uint32_t reg_lastbuf, uint32_t *Ret_DataCnt,
        uint16_t *Ret_Status);
#endif    /* USB_DMA_PP */

uint16_t usb_pstd_ChkConfigured(void);

#if USB_DMA_PP == USB_DMA_USE_PP
void usb_cpu_d0fifo2buf_start_dma(uint32_t SourceAddr, uint16_t useport,
        uint32_t transfer_size);
void usb_cpu_d1fifo2buf_start_dma(uint32_t SourceAddr, uint16_t useport,
        uint32_t transfer_size);
void usb_cpu_buf2d0fifo_start_dma(uint32_t src_adr, uint32_t transfer_size,
        uint8_t trans_block_size);
void usb_cpu_buf2d1fifo_start_dma(uint32_t src_adr, uint32_t transfer_size,
        uint8_t trans_block_size);
void usb_cpu_d0fifo_stop_dma(void);
void usb_cpu_d1fifo_stop_dma(void);
#endif   /* USB_DMA_PP */

void usb_cpu_module_start(void);
void usb_cpu_target_init(void);
void usb_cpu_DisableDma(void);
void usb_cpu_EnableDma(void);
uint32_t usb_cpu_get_dma_crtb(uint16_t use_port);

uint16_t usb_pstd_ControlRead(uint32_t Bsize, uint8_t *Table);
void usb_pstd_ControlWrite(uint32_t Bsize, uint8_t *Table);
void usb_pstd_ControlEnd(uint16_t status);

/* r_usb_pDriverAPI.c */
void usb_pstd_SetPipeRegister(uint16_t PipeNo, uint16_t *tbl);

/* USBf interrupt handlers */
void handle_usbf_epc_isr(IRQn_Type *irq_num_ptr);
void handle_usbf_isr(IRQn_Type *irq_num_ptr);

#endif  /* R_USBF_DRIVER_H__ */
/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
