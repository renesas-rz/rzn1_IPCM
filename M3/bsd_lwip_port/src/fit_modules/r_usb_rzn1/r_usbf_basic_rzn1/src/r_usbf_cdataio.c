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
 * $Revision: 1345 $
 * $Date: 2019-03-07 16:17:06 +0000 (Thu, 07 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usbf_cdataio.c
 * Description  :  USB Peripheral low level data I/O code
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "log_serial_io.h"
#include "r_usbf_basic_rzn1_if.h"
#include "r_usb_common.h"
#include "r_usb_cdefusbip.h"
#include "r_usbf_hal.h"
#include "r_usbf_driver.h"
#include "r_usb_rzn1_reg_defs.h"
#include "timer.h"

/***********************************************************************************************************************
 Constant macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Static variables and functions
 **********************************************************************************************************************/
static void usb_cstd_SelectNak(uint16_t pipe);

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/
extern uint8_t dbg_count;

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
/* USB data transfer */
/* PIPEn Buffer counter */
uint32_t usb_gcstd_DataCnt[USB_MAX_PIPE_NO + 1u];
/* DMA0 and DMA1 direction */
uint16_t usb_gcstd_Dma0Dir;
uint16_t usb_gcstd_Dma1Dir;
/* DMA0 and DMA1 buffer size */
uint32_t usb_gcstd_Dma0Size;
uint32_t usb_gcstd_Dma1Size;
/* DMA0 and DMA1 FIFO buffer size */
uint16_t usb_gcstd_Dma0Fifo;
uint16_t usb_gcstd_Dma1Fifo;
/* DMA0 and DMA1 pipe number */
uint16_t usb_gcstd_Dma0Pipe;
uint16_t usb_gcstd_Dma1Pipe;
/* PIPEn Buffer pointer(8bit) */
uint8_t *usb_gcstd_DataPtr[USB_MAX_PIPE_NO + 1u];
/* Message pipe */
USB_UTR_t *usb_gcstd_Pipe[USB_MAX_PIPE_NO + 1u];
/* Hi-speed enable */
uint16_t usb_gcstd_HsEnable;

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Renesas Abstracted common data I/O functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_SendStart
 **********************************************************************************************************************/
/*!
 * @brief    Start data transmission using CPU/DMA transfer to USB host
 * @details
 * @param    uint16_t pipe - pipe number
 * @retval   void
 **********************************************************************************************************************/
void usb_cstd_SendStart(uint16_t pipe)
{
    USB_UTR_t *pp;
    uint32_t length;
    uint16_t useport;
    uint16_t end_flag;
    uint16_t ep_num = 0xFF;
    /*char        uart_buf[32];*/

    /* find ep associated with this pipe */
    for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }
    if (ep_num <= USB_MAX_EP_NO)
    {
        /* Evacuation pointer */
        pp = usb_gcstd_Pipe[pipe];
        length = pp->tranlen;

        /* Select NAK */
        usb_cstd_SelectNak(pipe);
        /* Set data count */
        usb_gcstd_DataCnt[pipe] = length;
        /* Set data pointer */
        usb_gcstd_DataPtr[pipe] = (uint8_t*) pp->tranadr;

        /* Pipe number to port select */
        useport = usb_cstd_Pipe2Fport(pipe);
        /* Check port access */
        switch (useport)
        {
        /* CFIFO use */
        case USB_CUSE:
            /*sprintf(uart_buf, "Tx%x ", usb_gcstd_DataPtr[pipe][0]);
             sample_app_printf((const char *) uart_buf);*/
            if (true == usbf_eps[ep_num].open)
            {
                enable_usbf_epc_epm_isr(ep_num);
            } else
            {
                open_usbf_epc_epm(ep_num);
            }

            end_flag = usb_cstd_write_data(pipe, useport); /* write data to USB bus  */
            if (USB_ERROR == end_flag)
            {
                usb_cstd_ForcedTermination(pipe, (uint16_t)USB_DATA_ERR);
            }

            break;

#if USB_DMA_PP == USB_DMA_USE_PP
            /* D0FIFO DMA */
            case USB_D0DMA:
            case USB_D0DMA_C:               // data trans system same it
            /* Setting for use PIPE number */
            usb_gcstd_Dma0Pipe = pipe;
            /* PIPE direction */
            usb_gcstd_Dma0Dir = usb_cstd_GetPipeDir(pipe);
            /* Buffer size */
            usb_gcstd_Dma0Fifo = usb_cstd_GetBufSize(pipe);
            /* Check data count */
            if( usb_gcstd_DataCnt[usb_gcstd_Dma0Pipe] < usb_gcstd_Dma0Fifo )
            {
                /* Transfer data size */
                usb_gcstd_Dma0Size = usb_gcstd_DataCnt[usb_gcstd_Dma0Pipe];
            }
            else
            {
                /* Transfer data size */
                usb_gcstd_Dma0Size = (usb_gcstd_DataCnt[usb_gcstd_Dma0Pipe]
                        - (usb_gcstd_DataCnt[usb_gcstd_Dma0Pipe] % usb_gcstd_Dma0Fifo));
            }

            usb_cstd_Buf2D0fifoStartDma(pipe, useport);
            /* Set BUF */
            /*usb_cstd_SetBuf(pipe);*/
            break;

#endif    /* USB_DMA_PP */

        default:
            /* Access is NG */
            break;
        }
    }
}
/***********************************************************************************************************************
 End of function usb_cstd_SendStart
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_write_data
 **********************************************************************************************************************/
/*!
 * @brief    Send data to USB Host
 * @details  Write data to USB buffer,
 * @details  and manage the size of written data
 * @param    uint16_t Pipe no
 * @param    uint16_t Pipe mode
 * @retval   uint16_t end_flag (error status)
 **********************************************************************************************************************/
uint16_t usb_cstd_write_data(uint16_t pipe, uint16_t pipemode)
{
    uint16_t end_flag = USB_OK;
    uint32_t mxps;
    uint32_t pkts_to_send;
    int16_t count;
    uint8_t *data_ptr;
    uint32_t *data_to_write;
    uint16_t ep_num;
    uint32_t i;
    uint32_t j;
    uint32_t pkt_size;
    uint32_t pkt_size_words;
    uint32_t control_reg;

    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;
    volatile EPC_EPm_STATUS_Type *epm_status_reg_addr;
    volatile EPC_EPm_WRITE_Type *epm_write_reg_addr;

    /* find ep associated with this pipe */
    for (ep_num = USB_EP0; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }

    if (ep_num > USB_MAX_EP_NO)
    {
        /* Pipe not configured */
        end_flag = USB_ERROR;
    } else
    {
        /* Max Packet Size */
        mxps = EPm_MAX_PACKET_SIZE_FS; /*usbf_eps[ep_num].max_packet_size;*/

        count = (uint16_t) usb_gcstd_DataCnt[pipe];

        if (USB_EP0 != ep_num)
        {
            epm_control_reg_addr =
                    (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                            + (0x20 * (ep_num - 1)));
            epm_status_reg_addr =
                    (volatile EPC_EPm_STATUS_Type *) (USBFUNC_USB_EPC_EP1_STATUS_ADDRESS
                            + (0x20 * (ep_num - 1)));
            epm_write_reg_addr =
                    (volatile EPC_EPm_WRITE_Type *) (USBFUNC_USB_EPC_EP1_WRITE_ADDRESS
                            + (0x20 * (ep_num - 1)));            
        }
        /* Data count check */
        if (count > 0)
        {
            data_ptr = usb_gcstd_DataPtr[pipe];

            pkts_to_send = count / mxps;
            if (count % mxps)
            {
                pkts_to_send++;
            }

            while (count > 0)
            {
                data_to_write = (uint32_t *) data_ptr;
                if (count <= mxps)
                {
                    pkt_size = count;
                } else
                {
                    pkt_size = mxps;
                }

                /* wait with timeout for transmission buffer empty */
                if (USB_EP0 == ep_num)
                {
                    for (i = 400; i > 0; i--)
                    {
                        if ((((volatile EPC_EP0_STATUS_Type *) USBFUNC_USB_EPC_EP0_STATUS_ADDRESS)->EP0_STATUS.BIT.EP0_IN_EMPTY)
                            && (0 == ((volatile EPC_EP0_STATUS_Type *) USBFUNC_USB_EPC_EP0_STATUS_ADDRESS)->EP0_STATUS.BIT.EP0_IN_DATA))
                        {
                                break;

                        }
                        systimer_delay(50); /* Delay 50 usecs */
                    }
                } else
                {
                    for (i = 800; i > 0; i--)
                    {
                        if (epm_status_reg_addr->EPm_STATUS.BIT.EPm_IN_EMPTY)
                        {
                            break;
                        }
                        systimer_delay(50); /* Delay 50 usecs */
                    }
                }
                if (0 == i)
                {
                    /* timeout */
                    /*sample_app_printf("\nETMT\n");*/

                    end_flag = USB_ERROR;
                    break;
                }

                pkt_size_words = pkt_size / (sizeof(data_to_write[0]));
                for (i = 0; i < pkt_size_words; i++)
                {
                    if (USB_EP0 == ep_num)
                    {
                        ((volatile EPC_EP0_WRITE_Type *) USBFUNC_USB_EPC_EP0_WRITE_ADDRESS)->EP0_WRITE.LONG =
                                *data_to_write;
                    } else
                    {
                        epm_write_reg_addr->EPm_WRITE.LONG = *data_to_write;
                        /*wr_reg = *data_to_write;
                         sprintf(uart_buf, "W%x ", wr_reg);
                         sample_app_printf((const char *) uart_buf);*/
                    }
                    data_to_write++;
                }

                if (USB_EP0 == ep_num)
                {
                    control_reg =
                            ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.LONG;
                } else
                {
                    /* Is this the last packet ? */
                    --pkts_to_send;
                    if (0 == pkts_to_send)
                    {
                        usbf_eps[ep_num].state = USB_DS_TX; /* end of TX flag */
                    }
                    control_reg = epm_control_reg_addr->EPm_CONTROL.LONG;
                }

                /* write any extra bytes i.e. pkt_size % sizeof(data_to_write[0]) */
                j = pkt_size % (sizeof(data_to_write[0]));
                if (j > 0)
                {
                    if (USB_EP0 == ep_num)
                    {
                        ((volatile EPC_EP0_WRITE_Type *) USBFUNC_USB_EPC_EP0_WRITE_ADDRESS)->EP0_WRITE.LONG =
                                *data_to_write;
                    } else
                    {
                        epm_write_reg_addr->EPm_WRITE.LONG = *data_to_write;
                        /*wr_reg = *data_to_write;
                         sprintf(uart_buf, "E%x %x ", j, wr_reg);
                         sample_app_printf((const char *) uart_buf); */
                    }
                    control_reg |= (j << 5);
                }
                control_reg |= EPC_EPm_CONTROL_EPm_DEND_BIT;
                if (USB_EP0 == ep_num)
                {
                    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.LONG =
                            control_reg;
                } else
                {
                    epm_control_reg_addr->EPm_CONTROL.LONG = control_reg;
                }
                count -= pkt_size;
                data_ptr += pkt_size;
            }
        } else
        {
            /* Send Null packet */
            if (USB_EP0 == ep_num)
            {
                usb_pstd_ControlEnd(USB_CTRL_END);
            } else
            {
                /* EPn */

                /* wait with 20 msec timeout for transmission buffer empty */
                for (i = 400; i > 0; i--)
                {
                    if (epm_status_reg_addr->EPm_STATUS.BIT.EPm_IN_EMPTY)
                    {
                        /* set EPm_DEND usb_cstd_DataEnd()   */
                        epm_control_reg_addr->EPm_CONTROL.BIT.EPm_DEND = 1;
                        break;
                    }
                    systimer_delay(50); /* Delay 50 usecs */
                }
                if (0 == i)
                {
                    /* timeout */
                    end_flag = USB_ERROR;
                }
            }
        }
    }

    /* End or Err */
    return end_flag;
}
/***********************************************************************************************************************
 End of function usb_cstd_write_data
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_ReceiveStart
 **********************************************************************************************************************/
/*!
 * @brief    start data reception using CPU/DMA transfer from USB Host.
 * @details
 * @param    uint16_t pipe - pipe number
 * @retval   void
 **********************************************************************************************************************/
void usb_cstd_ReceiveStart(uint16_t pipe)
{
    USB_UTR_t *pp;
    uint32_t length;
    uint16_t useport;
    uint16_t ep_num;

    /* find ep associated with this pipe */
    for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }
    if (ep_num <= USB_MAX_EP_NO)
    {

        /* Evacuation pointer */
        pp = usb_gcstd_Pipe[pipe];
        length = pp->tranlen;

        /* Select NAK */
        usb_cstd_SelectNak(pipe);
        /* Set data count */
        usb_gcstd_DataCnt[pipe] = length;
        /* Set data pointer */
        usb_gcstd_DataPtr[pipe] = (uint8_t*) pp->tranadr;

        /* Pipe number to port select */
        useport = usb_cstd_Pipe2Fport(pipe);

        /* Check port access */
        switch (useport)
        {
        case USB_CUSE:
            if (true == usbf_eps[ep_num].open)
            {
                enable_usbf_epc_epm_isr(ep_num);
            } else
            {
                open_usbf_epc_epm(ep_num);
            }

            break;

#if USB_DMA_PP == USB_DMA_USE_PP
            /* D0FIFO DMA */
            case USB_D0DMA:
            /* D0FIFOB DMA */
            case USB_D0DMA_C:
            /* Setting for use PIPE number */
            usb_gcstd_Dma0Pipe = pipe;
            /* PIPE direction */
            usb_gcstd_Dma0Dir = usb_cstd_GetPipeDir( pipe);
            /* Buffer size */
            usb_gcstd_Dma0Fifo = usb_cstd_GetBufSize( pipe);
            /* Transfer data size */
            if (useport == USB_D0DMA)
            {
                usb_gcstd_Dma0Size = ((usb_gcstd_DataCnt[usb_gcstd_Dma0Pipe] - 1 ) /
                        USB_FIFO_ACCESS_UNIT_4 + 1) * USB_FIFO_ACCESS_UNIT_4;
            }
            else if (useport == USB_D0DMA_C)
            {
                usb_gcstd_Dma0Size = ((usb_gcstd_DataCnt[usb_gcstd_Dma0Pipe] - 1)
                        / USB_FIFO_ACCESS_UNIT_32 + 1 ) * USB_FIFO_ACCESS_UNIT_32;
            }

            usb_cstd_D0fifo2BufStartDma( pipe, useport, length );
            break;
#endif    /* USB_DMA_PP */

        default:
            usb_cstd_ForcedTermination(pipe, (uint16_t)USB_DATA_ERR);
            break;
        }
    }
}
/***********************************************************************************************************************
 End of function usb_cstd_ReceiveStart
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_read_data
 **********************************************************************************************************************/
/*!
 * @brief    Read USB data
 * @details  Read data from USB buffer,
 * @details  and manage the size of data read
 * @param    uint16_t Pipe no
 * @param    uint16_t Pipe mode
 * @retval   uint16_t end_flag (error status)
 **********************************************************************************************************************/
uint16_t usb_cstd_read_data(uint16_t pipe, uint16_t pipemode)
{
    uint16_t end_flag = USB_READING;
    uint32_t *buf_ptr;

    uint16_t ep_num;
    int16_t i;

    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;
    volatile EPC_EPm_READ_Type *epm_read_reg_addr;
    volatile EPC_EPm_LEN_DCNT_Type *epm_len_dcnt_reg_addr;

    uint16_t count;
    uint16_t mxps;
    uint16_t dtln;
    /*char        uart_buf[32];    */

    /* find ep associated with this pipe */
    for (ep_num = USB_EP0; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }

    if (ep_num > USB_MAX_EP_NO)
    {
        /* Pipe not configured */
        end_flag = USB_ERROR;
    } else
    {
        /* Max Packet Size */
        mxps = EPm_MAX_PACKET_SIZE_FS; /*usbf_eps[ep_num].max_packet_size;*/

        if (USB_EP0 == ep_num)
        {
            dtln =
                    ((volatile EPC_EP0_LENGTH_Type *) USBFUNC_USB_EPC_EP0_LENGTH_ADDRESS)->EP0_LENGTH.BIT.EP0_LDATA;
        } else
        {
            epm_control_reg_addr =
                    (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                            + (0x20 * (ep_num - 1)));
            epm_len_dcnt_reg_addr =
                    (volatile EPC_EPm_LEN_DCNT_Type *) (USBFUNC_USB_EPC_EP1_LEN_DCNT_ADDRESS
                            + (0x20 * (ep_num - 1)));
            epm_read_reg_addr =
                    (volatile EPC_EPm_READ_Type *) (USBFUNC_USB_EPC_EP1_READ_ADDRESS
                            + (0x20 * (ep_num - 1)));
            dtln = epm_len_dcnt_reg_addr->EPm_LEN_DCNT.BIT.EPm_LDATA;
            /*dmacnt = epm_len_dcnt_reg_addr->EPm_LEN_DCNT.BIT.EPm_DMACNT;   */
        }

        if (usb_gcstd_DataCnt[pipe] < dtln)
        {
            /* Buffer Over ? */
            end_flag = USB_READOVER;
            /* Set NAK */
            usb_cstd_SetONak(pipe);
            count = (uint16_t) usb_gcstd_DataCnt[pipe];
            usb_gcstd_DataCnt[pipe] = dtln;
        } else if (usb_gcstd_DataCnt[pipe] == dtln)
        {
            /* Just Receive Size */
            count = dtln;
            if ((USB_PIPE0 == pipe) && ((dtln % mxps) == 0))
            {
                /* Just Receive Size */
                /* Peripheral Function */
                end_flag = USB_READING;
            } else
            {
                end_flag = USB_READEND;
                /* Set NAK */
                usb_cstd_SetONak(pipe);
            }
        } else
        {
            /* Continue to receive data */
            count = dtln;
            end_flag = USB_READING;
            if (0 == count)
            {
                /* Null Packet receive */
                end_flag = USB_READSHRT;
                /* Select NAK */
                usb_cstd_SetONak(pipe);
            }
            if ((count % mxps) != 0)
            {
                /* Null Packet receive */
                end_flag = USB_READSHRT;
                /* Select NAK */
                /* usb_cstd_SetONak( pipe); oonagh*/
            }
        }

        if (0 == dtln)
        {
            /* 0 length packet - clear BVAL */
            if (USB_EP0 == ep_num)
            {
                /*Clear EP0 buffer (write & read regs on CPU side & USB side) */
                ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_BCLR =
                        1;
            } else
            {
                epm_control_reg_addr->EPm_CONTROL.BIT.EPm_BCLR = 1;
            }
        } else
        {
            buf_ptr = (uint32_t *) (usb_gcstd_DataPtr[pipe]);
            for (i = count; i > 0; i -= 4)
            {
                if (USB_EP0 == ep_num)
                {
                    *buf_ptr++ =
                            ((volatile EPC_EP0_READ_Type *) USBFUNC_USB_EPC_EP0_READ_ADDRESS)->EP0_READ.LONG;
                } else
                {
                    *buf_ptr = epm_read_reg_addr->EPm_READ.LONG;
                    /*sprintf(uart_buf, "R%c ", *buf_ptr);
                     sample_app_printf((const char *) uart_buf);*/
                    buf_ptr++;
                }
            }
        }
        usb_gcstd_DataPtr[pipe] += count;
        usb_gcstd_DataCnt[pipe] -= count;
    }

    return (end_flag);
}
/***********************************************************************************************************************
 End of function usb_cstd_read_data
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_cstd_DataEnd
 **********************************************************************************************************************/
/*!
 * @brief    Set USB registers as appropriate after data transmission/re-
 * @details  Set USB registers as appropriate after data transmission or
 * @details  reception, and call the completion callback function
 * @param    uint16_t pipe_no  : pipe number
 * @param    uint16_t status   : Transfer status type
 * @retval   void
 **********************************************************************************************************************/
void usb_cstd_DataEnd(uint16_t pipe, uint16_t status)
{
    uint16_t ep_num;
#if USB_DMA_PP == USB_DMA_USE_PP
    uint16_t buffer;
#endif

    /* find ep associated with this pipe */
    for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
    {
        if (usbf_eps[ep_num].pipe == pipe)
        {
            break;
        }
    }
    if (ep_num <= USB_MAX_EP_NO)
    {
        usbf_eps[ep_num].state = USB_DS_IDST;

#if USB_DMA_PP == USB_DMA_USE_PP
        /* Check access */

        /* Pipe number to port select */
        useport = usb_cstd_Pipe2Fport( pipe );
        /* D0FIFO use */
        if (USB_D0DMA == useport || USB_D0DMA_C == useport)
        {
            /* DMA buffer clear mode clear */
            usb_creg_clr_dclrm( USB_D1DMA );
            usb_creg_set_mbw( USB_D1DMA, USB0_D1FIFO_MBW );
        }
#endif    /* USB_DMA_PP */

        /* Call Back */
        if (USB_NULL != usb_gcstd_Pipe[pipe])
        {
            /* Check PIPE TYPE */
            if (usb_cstd_GetPipeType(pipe) != USB_ISO)
            {
                /* Transfer information set */
                usb_gcstd_Pipe[pipe]->tranlen = usb_gcstd_DataCnt[pipe];
                usb_gcstd_Pipe[pipe]->status = status;

                (usb_gcstd_Pipe[pipe]->complete)(usb_gcstd_Pipe[pipe]);
                usb_gcstd_Pipe[pipe] = (USB_UTR_t*) USB_NULL;
            } else
            {
                /* Transfer information set */
                usb_gcstd_Pipe[pipe]->tranlen = usb_gcstd_DataCnt[pipe];

                /* Data Transfer (restart) */
                if (usb_cstd_GetPipeDir(pipe) == USB_BUF2FIFO)
                {
                    /* IN Transfer */
                    usb_gcstd_Pipe[pipe]->status = USB_DATA_WRITING;
                    (usb_gcstd_Pipe[pipe]->complete)(usb_gcstd_Pipe[pipe]);
                } else
                {
                    /* OUT Transfer */
                    usb_gcstd_Pipe[pipe]->status = USB_DATA_READING;
                    (usb_gcstd_Pipe[pipe]->complete)(usb_gcstd_Pipe[pipe]);
                }
            }
        }
    }

}
/***********************************************************************************************************************
 End of function usb_cstd_DataEnd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function Name   : void usb_cstd_SelectNak(uint16_t pipe)
 Description     : Set the specified pipe PID to send a NAK if the transfer type
 : is BULK/INT.
 Arguments       : uint16_t pipe     : Pipe number.
 Return value    : none
 **********************************************************************************************************************/
static void usb_cstd_SelectNak(uint16_t pipe)
{
    /* Check PIPE TYPE */
    if (usb_cstd_GetPipeType(pipe) != USB_ISO)
    {
        if (USB_PIPE0 == pipe)
        {
            usb_cstd_SetONakPipe0();
            usb_cstd_SetINakPipe0();
        } else
        {
            usb_cstd_SetONak(pipe);
        }
    }
}
/***********************************************************************************************************************
 End of function usb_cstd_SelectNak
 **********************************************************************************************************************/

/***********************************************************************************************************************
 End Of File
 **********************************************************************************************************************/
