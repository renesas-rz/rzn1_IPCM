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
 * FILE         :  r_usbf_hal.h
 * Description  :  USBf Hardware Abstraction Layer common definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_USBF_HAL_H__
#define R_USBF_HAL_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_usbf_basic_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/

/* Max Packet sizes and buffers size EP0 */
#define EP0_BUFFERS_SIZE                (0x20)
#define CONTROL_MAX_PACKET_SIZE         (0x40)

/* Max Packet sizes EPm */
/* default value OK for FS & HS.
 So if switch FS->HS while connection made and data being transferred, buffer sizes will not need to be re-set so transactions in progress not disrupted */
#define EPm_MAX_PACKET_SIZE_HS          (0x200)
#define EPm_MAX_PACKET_SIZE_FS          (0x40)
#define EP_MAX_PACKET_COUNT             (0x100)

#define USB_BITSET(x)           ((uint16_t)((uint16_t)1 << (x)))

/* Size of Interrupt info buffer */
#define USB_INT_BUFSIZE         (40)

/* Start Pipe No */
#define USB_MIN_PIPE_NO         (USB_PIPE1)

/* SPEED mode */
#define USB_HS_DISABLE          ((uint16_t)0)
#define USB_HS_ENABLE           ((uint16_t)1)

/* FIFO port register default access size */
#define USB0_CFIFO_MBW          (USB_MBW_32)  /* FIFO access : 32bit */
#define USB0_D0FIFO_MBW         (USB_MBW_32)  /* FIFO access : 32bit */
#define USB0_D1FIFO_MBW         (USB_MBW_32)  /* FIFO access : 32bit */

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
/* Data structure used for EPC Interrupt Status for all interrupts */
typedef struct
{
    uint32_t usb_status;
    uint32_t epn_status[USBF_MAX_EPS];
} EPC_INT_STATUS;

/* Interrupt queue structure for EPC USB & EPn interrupts */
typedef struct
{
    EPC_INT_STATUS Buf[USB_INT_BUFSIZE];
    uint8_t Wp;
    uint8_t Rp;
} EPC_EP_USBf_INT_t;

/* Endpoint information */
typedef struct
{
    bool enabled;
    bool dma_enabled;
    uint32_t type;
    uint32_t dir;
    uint32_t max_packet_size;
    uint32_t max_packets;
    uint32_t state;
    uint16_t pipe; /* associated pipe */
    bool open;
} ENDPOINT;

/***********************************************************************************************************************
 Public Variables
 **********************************************************************************************************************/
extern EPC_EP_USBf_INT_t usb_gpstd_UsbEPCInt;
extern ENDPOINT usbf_eps[];
extern bool check_vbus_level;
extern bool g_bHighSpeed;

/***********************************************************************************************************************
 Public Functions
 **********************************************************************************************************************/

/* r_usb_creg_dmadtc.c */
#if USB_DMA_PP == USB_DMA_USE_PP
void usb_cstd_DfifoStopUsb(void);
void usb_cstd_DfifoInt(void);
void usb_cstd_Buf2DfifoStartDma(uint16_t, uint16_t);
void usb_cstd_Dfifo2BufStartDma(uint16_t, uint16_t, uint32_t);

extern void usb_cstd_ChkDMARecvDataCount(uint32_t crtb, uint32_t data_cnt, uint16_t fifobuf_size,
        uint32_t reg_lastbuf, uint32_t *Ret_DataCnt, uint16_t *Ret_Status );
#endif    /* USB_DMA_PP */

#if USB_DMA_PP == USB_DMA_USE_PP
void usb_cpu_d0fifo2buf_start_dma(uint32_t SourceAddr, uint16_t useport, uint32_t transfer_size);
void usb_cpu_d1fifo2buf_start_dma(uint32_t SourceAddr, uint16_t useport, uint32_t transfer_size);
void usb_cpu_buf2d0fifo_start_dma(uint32_t src_adr, uint32_t transfer_size, uint8_t trans_block_size);
void usb_cpu_buf2d1fifo_start_dma(uint32_t src_adr, uint32_t transfer_size, uint8_t trans_block_size);
void usb_cpu_d0fifo_stop_dma(void);
void usb_cpu_d1fifo_stop_dma(void);
#endif   /* USB_DMA_PP */

void usb_cpu_module_start(void);
void usb_cpu_target_init(void);
void usb_cpu_DisableDma(void);
void usb_cpu_EnableDma(void);
uint32_t usb_cpu_get_dma_crtb(uint16_t use_port);

USB_ERR R_USBHAL_Init(void);
bool R_USBHAL_IsHighSpeed(void);
uint16_t usb_pstd_ChkVbsts(void);
bool epn_flush_buffer(uint16_t ep_num, uint32_t buf_mask);

/* Reset module */
void R_USBHAL_Reset(void);

/*Stall*/
void R_USBHAL_Control_Stall(void);

void R_USBHAL_Detach(void);

/* USBf interrupt handlers */
void handle_usbf_epc_isr(IRQn_Type *irq_num_ptr);
void handle_usbf_isr(IRQn_Type *irq_num_ptr);

/* USBf interrupt enable and disable functions */
void enable_usbf_epc_isr(void);
void disable_usbf_epc_isr(void);

void enable_usbf_epc_ep0_isr(void);
void disable_usbf_epc_ep0_isr(void);

void enable_usbf_epc_epm_isr(uint16_t end_point);
void disable_usbf_epc_epm_isr(uint16_t end_point);

void open_usbf_epc_epm(uint16_t end_point);
void close_usbf_epc_epm(uint16_t end_point);

void enable_usbf_ahb_epc_isr(void); /* AHB-EPC bridge interrupts */
void disable_usbf_ahb_epc_isr(void);

#endif  /* R_USBF_HAL_H__ */
/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
