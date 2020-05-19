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
 * $Revision: 1806 $
 * $Date: 2020-01-10 17:46:36 +0000 (Fri, 10 Jan 2020) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_dma_rzn1.c
 * Description  :  DMA control functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_dma_rzn1_if.h"
#include "r_dma_rzn1.h"
#include "iodefine.h"
#include "r_sysctrl_rzn1_if.h"
#include "mcu_interrupts_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
typedef struct
{
    bool ERROR;
    bool DST_TRAN;
    bool SRC_TRAN;
    bool BLOCK_COMPLETE;
    bool TRANS_COMPLETE;
} dma_interrupt_status;

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static volatile DMAC_Type *DMACBaseAddress[MAX_DMAC];

static DMA_CHAN_CTRL dma_channel_control[MAX_DMAC][MAX_DMA_CHAN];
static DMA_TRANS_CTRL dma_trans_control[MAX_DMAC][MAX_DMA_CHAN];

static dma_trans_complete_callback dma_callback[MAX_DMAC][MAX_DMA_CHAN]; /* Declared here to be altered through IFs and called from ISR */

/***********************************************************************************************************************
 * Local functions
 **********************************************************************************************************************/
static void handle_dma_isr (IRQn_Type *irq_num_ptr);

/***********************************************************************************************************************
 *
 *  Function Name:  dma_init
 *
 *  Return Value:   None
 *
 *  Parameters:     None
 *
 *  Description:    System control configuration to allow for both DMAC register access.
 *
 **********************************************************************************************************************/
void dma_init (void)
{
    uint8_t dmac_number;
    uint8_t channel;

    R_SYSCTRL_EnableDMA(0);
    R_SYSCTRL_EnableDMA(1);

    /* Clear internal parameters */
    for (dmac_number = 0; dmac_number < MAX_DMAC; dmac_number++)
    {
        for (channel = 0; channel < MAX_DMA_CHAN; channel++)
        {
            dma_callback[dmac_number][channel] = 0;
        }
    }
}
/***********************************************************************************************************************
 End of function dma_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_uninit
 *
 *  Return Value:   None
 *
 *  Parameters:     None
 *
 *  Description:    System control configuration to disable both DMAC register access.
 *
 **********************************************************************************************************************/
void dma_uninit (void)
{
    uint8_t dmac_number;
    uint8_t channel;

    R_SYSCTRL_DisableDMA(0);
    R_SYSCTRL_DisableDMA(1);

    /* Clear internal parameters */
    for (dmac_number = 0; dmac_number < MAX_DMAC; dmac_number++)
    {
        for (channel = 0; channel < MAX_DMA_CHAN; channel++)
        {
            dma_callback[dmac_number][channel] = 0;
        }
    }
}
/***********************************************************************************************************************
 End of function dma_uninit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_open
 *
 *  Return Value:   None
 *
 *  Parameters:     DMAC_number - The DMA controller to open
 *
 *  Description:    Opens a DMA controller
 *
 **********************************************************************************************************************/
ER_RET dma_open (uint8_t DMAC_number)
{
    ER_RET ret_val;
    uint32_t int_priority;
    IRQn_Type irq_num = RZN1_IRQ_DMA0 + DMAC_number;
    DMACBaseAddress[DMAC_number] = ((volatile DMAC_Type *) (RZN1_DMA1_BASE + (DMAC_number * RZN1_DMA1_SIZE)));

    /* Mask interrupts- each channel will have an interrupt enable option */
    DMACBaseAddress[DMAC_number]->MaskTfr.LONGLONG = DMA_INTERRUPT_MASK;
    DMACBaseAddress[DMAC_number]->MaskBlock.LONGLONG = DMA_INTERRUPT_MASK;
    DMACBaseAddress[DMAC_number]->MaskSrcTran.LONGLONG = DMA_INTERRUPT_MASK;
    DMACBaseAddress[DMAC_number]->MaskDstTran.LONGLONG = DMA_INTERRUPT_MASK;

    /* Register interrupts */
    if (R_BSP_InterruptRegisterCallback((IRQn_Type) irq_num, (bsp_int_cb_t) &handle_dma_isr) == MCU_INT_SUCCESS)
    {
        int_priority = DMA_DEFAULT_INT_PRIORITY;
        ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
        if (MCU_INT_SUCCESS != ret_val)
        {
            ret_val = ER_SYS;
        }
        else
        {
            ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);
        }
    }
    else
    {
        ret_val = ER_SYS;
    }

    if (ER_OK == ret_val)
    {
        /* Enable the DMAC */
        DMACBaseAddress[DMAC_number]->DmaCfgReg.BIT.DMA_EN = 1;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function dma_open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_close
 *
 *  Return Value:   None
 *
 *  Parameters:     DMAC_number - The DMA controller to close
 *
 *  Description:    closes a DMA controller
 *
 **********************************************************************************************************************/
ER_RET dma_close (uint8_t DMAC_number)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num = (uint8_t) RZN1_IRQ_DMA0 + DMAC_number;

    ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE,
    FIT_NO_PTR);
    DMACBaseAddress[DMAC_number]->DmaCfgReg.BIT.DMA_EN = 0;

    return ret_val;
}
/***********************************************************************************************************************
 End of function dma_close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_setcallback
 *
 *  Return Value:   None
 *
 *  Parameters:     DMAC_number - Which DMAC controller to assign the call back to
 *                  channel - Which DMA channel to assign the call back to
 *                  call_back - The call back function
 *
 *  Description:    Sets the call back for the DMA controller when an interrupt occurs
 *
 **********************************************************************************************************************/
void dma_setcallback (uint8_t DMAC_number, uint8_t channel, dma_trans_complete_callback call_back)
{
    dma_callback[DMAC_number][channel] = call_back;
}
/***********************************************************************************************************************
 End of function dma_setcallback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_transreq
 *
 *  Return Value:   error status
 *
 *  Parameters:     DMAC_number - Which DMAC controller to configure.
 *                  channel - Which DMA channel to configure.
 *                  req_type - DMA Transfer request type.
 *
 *  Description:    Sets up the transfer requirements.
 *
 **********************************************************************************************************************/
ER_RET dma_transreq (uint8_t DMAC_number, uint8_t channel, DMA_TRANS_REQ_TYPE req_type)
{
    ER_RET ret_val = ER_OK;

    if (ER_OK == ret_val)
    {
        DMA_TR_FLOW transtype_fc = dma_trans_control[DMAC_number][channel].TR_FLOW;
        DMA_HS_TYPE handshaking_src = dma_channel_control[DMAC_number][channel].SRC_HS.TYPE;
        DMA_HS_TYPE handshaking_dst = dma_channel_control[DMAC_number][channel].DST_HS.TYPE;

        /* Ensure the source/destination transaction request is valid for the current settings of the transaction type and flow controller */
        /* Determine if the FIFO is full, not allowing for source transactions or empty, not allowing for destination transactions */
        switch (req_type)
        {
            case DMA_SRC:
            case DMA_SRC_SINGLE:
            case DMA_SRC_LAST:
                if ((MTM == transtype_fc) || (PTM_P == transtype_fc) || (PTP_SP == transtype_fc)
                        || (HARDWARE == handshaking_src)) /* If the source peripheral is the flow controller, the transfer type is memory to memory or hardware handshaking then a source transaction request is not possible */
                {
                    ret_val = ER_INVAL;
                }
            break;

            case DMA_DST:
            case DMA_DST_SINGLE:
            case DMA_DST_LAST:
                if ((MTM == transtype_fc) || (MTP_P == transtype_fc) || (PTP_DP == transtype_fc)
                        || (HARDWARE == handshaking_dst)) /* If the destination peripheral is the flow controller, the transfer type is memory to memory or hardware handshaking then a destination transaction request is not possible */
                {
                    ret_val = ER_INVAL;
                }
            break;

            default:
            break;
        }

        if (ER_OK == ret_val)
        {
            switch (req_type)
            {
                case DMA_TRANSFER:
                break;

                case DMA_SRC:
                    DMACBaseAddress[DMAC_number]->ReqSrcReg.LONGLONG |= (uint64_t) DMA_REG_WRITE(channel);
                break;

                case DMA_SRC_SINGLE:
                    DMACBaseAddress[DMAC_number]->SglRqSrcReg.LONGLONG |= (uint64_t) DMA_REG_WRITE(channel);
                break;

                case DMA_SRC_LAST:
                    DMACBaseAddress[DMAC_number]->LstSrcReg.LONGLONG |= (uint64_t) DMA_REG_WRITE(channel);
                break;

                case DMA_DST:
                    DMACBaseAddress[DMAC_number]->ReqDstReg.LONGLONG |= (uint64_t) DMA_REG_WRITE(channel);
                break;

                case DMA_DST_SINGLE:
                    DMACBaseAddress[DMAC_number]->SglRqDstReg.LONGLONG |= (uint64_t) DMA_REG_WRITE(channel);
                break;

                case DMA_DST_LAST:
                    DMACBaseAddress[DMAC_number]->LstDstReg.LONGLONG |= (uint64_t) DMA_REG_WRITE(channel);
                break;

                default:
                    ret_val = ER_PARAM;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function dma_transreq
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_setchanconfig
 *
 *  Return Value:   None
 *
 *  Parameters:     DMAC_number - Which DMAC controller to configure.
 *                  channel - Which DMA channel to configure.
 *                  control - settings for the channel:
 *                                                      -TR_FLOW -SRC_HS -DST_HS
 *
 *  Description:    Configures basic DMA channel parameters.
 *
 **********************************************************************************************************************/
ER_RET dma_setchanconfig (uint8_t DMAC_number, uint8_t channel, DMA_CHAN_CTRL *control)
{
    ER_RET ret_val = ER_OK;

    if (ER_OK == ret_val)
    {
#if DMA_CFG_PARAM_CHECKING_ENABLE
        if ((channel >= MAX_DMA_CHAN) || (FIT_NO_PTR == control))
        {
            ret_val = ER_PARAM;
        }
        else
#endif
        {
            if ((control->PRIORITY >= MAX_DMA_CHAN) && (DEFAULT_CHAN_PRIORITY != control->PRIORITY))
            {
                ret_val = ER_PARAM;
            }
            else
            {
                dma_channel_control[DMAC_number][channel] = *control;

                /* Set channel priority */
                if (DEFAULT_CHAN_PRIORITY == dma_channel_control[DMAC_number][channel].PRIORITY) /* Default channel priority is = to the channel number */
                {
                    dma_channel_control[DMAC_number][channel].PRIORITY = channel;
                }

                DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CFG.BIT.CH_PRIOR =
                        dma_channel_control[DMAC_number][channel].PRIORITY;

                /* Configure Handshaking */
                if (HARDWARE == (DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CFG.BIT.HS_SEL_SRC =
                        dma_channel_control[DMAC_number][channel].SRC_HS.TYPE))
                {
                    DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CFG.BIT.SRC_PER =
                            dma_channel_control[DMAC_number][channel].SRC_HS.HS_INTERFACE; /* Hardware handshaking interface only set if hardware handshaking selected */
                }

                DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CFG.BIT.SRC_HS_POL =
                        dma_channel_control[DMAC_number][channel].SRC_HS.INTERFACE_POLARITY; /* Interface polarity independent of type of handshaking */

                if (HARDWARE == (DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CFG.BIT.HS_SEL_DST =
                        dma_channel_control[DMAC_number][channel].DST_HS.TYPE))
                {
                    DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CFG.BIT.DEST_PER =
                            dma_channel_control[DMAC_number][channel].DST_HS.HS_INTERFACE; /* Hardware handshaking interface only set if hardware handshaking selected */
                }

                DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CFG.BIT.DST_HS_POL =
                        dma_channel_control[DMAC_number][channel].DST_HS.INTERFACE_POLARITY; /* Interface polarity independent of type of handshaking */
            }
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function dma_setchanconfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_getchanconfig
 *
 *  Return Value:   None
 *
 *  Parameters:     DMAC_number - Which DMA controller to get configuration of.
 *                  channel - Which channel to enable/ disable interrupts on.
 *                  control - settings for the channel:
 *                                                      -TR_FLOW -SRC_HS -DST_HS
 *
 *  Description:    Returns configuration of the basic DMA channel parameters.
 *
 **********************************************************************************************************************/
ER_RET dma_getchanconfig (uint8_t DMAC_number, uint8_t channel, DMA_CHAN_CTRL *control)
{
    ER_RET ret_val = ER_OK;

    if (ER_OK == ret_val)
    {
#if DMA_CFG_PARAM_CHECKING_ENABLE
        if (channel >= MAX_DMA_CHAN)
        {
            ret_val = ER_PARAM;
        }
        else
#endif
        {
            *control = dma_channel_control[DMAC_number][channel];
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function dma_getchanconfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_settransconfig
 *
 *  Return Value:   None
 *
 *  Parameters:     DMAC_number - Which DMA controller to configure.
 *                  channel - Which channel to enable/ disable interrupts on.
 *                  control - settings for the channel:
 *                                     -source -destination -incrementation -transfer width -burst length -block size -transfer type
 *
 *  Description:    Configures basic DMA transfer parameters.
 *
 **********************************************************************************************************************/
ER_RET dma_settransconfig (uint8_t DMAC_number, uint8_t channel, DMA_TRANS_CTRL *control)
{
    ER_RET ret_val = ER_OK;

    if (ER_OK == ret_val)
    {
#if DMA_CFG_PARAM_CHECKING_ENABLE
        if ((channel >= MAX_DMA_CHAN) || (FIT_NO_PTR == control))
        {
            ret_val = ER_PARAM;
        }
        else
#endif
        {
            /* Control parameter validation */
            if ((control->TR_FLOW > PTP_DP) || (control->DST_TR_WIDTH > BITS64) || (control->SRC_TR_WIDTH > BITS64)
                    || (control->DST_BRST_LEN > DATA_ITEMS_256) || (control->SRC_BRST_LEN > DATA_ITEMS_256)
                    || (control->DST_INCR > NO_CHANGE) || (control->SRC_INCR > NO_CHANGE))
            {
                ret_val = ER_PARAM;
            }
            else
            {

                dma_trans_control[DMAC_number][channel] = *control;

                /* Ensure that source/ destination address remains fixed if the source/ destination are peripherals */
                switch (control->TR_FLOW)
                {
                    case MTM:
                        if (control->BLOCK_SIZE > 4095)
                        {
                            ret_val = ER_PARAM;
                        }
                    break;
                    case MTP_DMAC:
                        if (control->BLOCK_SIZE > 4095)
                        {
                            ret_val = ER_PARAM;
                        }
                    break;
                    case MTP_P:
                    break;
                    case PTM_DMAC:
                        if (control->BLOCK_SIZE > 4095)
                        {
                            ret_val = ER_PARAM;
                        }
                    break;
                    case PTM_P:
                    break;
                    case PTP_DMAC:
                        if (control->BLOCK_SIZE > 4095)
                        {
                            ret_val = ER_PARAM;
                        }
                    break;
                    case PTP_SP:
                    case PTP_DP:
                    break;
                    default:
                    break;
                }
                if (ER_OK == ret_val)
                {
                    /* Set the registers */
                    DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CTL.LONGLONG =
                            dma_trans_control[DMAC_number][channel].INT_EN /* Global mask bit for all interrupts on channel*/
                            | (dma_trans_control[DMAC_number][channel].DST_TR_WIDTH << 1) /* Destination transfer width */
                            | (dma_trans_control[DMAC_number][channel].SRC_TR_WIDTH << 4) /* Source transfer width */
                            | (dma_trans_control[DMAC_number][channel].DST_INCR << 7) /* Destination address increment */
                            | (dma_trans_control[DMAC_number][channel].SRC_INCR << 9) /* Source address increment */
                            | (dma_trans_control[DMAC_number][channel].DST_BRST_LEN << 11) /* Destination burst length */
                            | (dma_trans_control[DMAC_number][channel].SRC_BRST_LEN << 14) /* Source burst length */
                            | (dma_trans_control[DMAC_number][channel].TR_FLOW << 20); /* Transfer type and flow controller */
                    DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CTL.BIT.BLOCK_TS =
                            dma_trans_control[DMAC_number][channel].BLOCK_SIZE; /* Block transfer size */   /* New call to register to avoid shift count warning (shift by 32 bits)*/

                    DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].SAR.BIT.SAR =
                            dma_trans_control[DMAC_number][channel].SRC; /* Source address */
                    DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].DAR.BIT.DAR =
                            dma_trans_control[DMAC_number][channel].DST; /* Destination address */
                }
            }

        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function dma_settransconfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_gettransconfig
 *
 *  Return Value:   None
 *
 *  Parameters:     DMAC_number - Which DMA controller to configure.
 *                  channel - Which channel to enable/ disable interrupts on.
 *                  control - settings for the channel:
 *                                                      -TR_FLOW -SRC_HS -DST_HS
 *
 *  Description:    Returns configuration of the basic DMA channel parameters.
 *
 **********************************************************************************************************************/
ER_RET dma_gettransconfig (uint8_t DMAC_number, uint8_t channel, DMA_TRANS_CTRL *control)
{
    ER_RET ret_val = ER_OK;

#if DMA_CFG_PARAM_CHECKING_ENABLE
    if (channel >= MAX_DMA_CHAN || (FIT_NO_PTR == control))
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        *control = dma_trans_control[DMAC_number][channel];
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function dma_gettransconfig
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_enablechannel
 *
 *  Return Value:   None
 *
 *  Parameters:     DMAC_number - Which DMA controller to configure.
 *                  channel - Which channel to enable.
 *
 *  Description:    Enables a DMA channel.
 *
 **********************************************************************************************************************/
void dma_enablechannel (uint8_t DMAC_number, uint8_t channel)
{
    /* Unmask interrupts */
    DMACBaseAddress[DMAC_number]->MaskTfr.LONGLONG |= (uint64_t) DMA_CHAN_ENABLE(channel);
    DMACBaseAddress[DMAC_number]->MaskBlock.LONGLONG |= (uint64_t) DMA_CHAN_ENABLE(channel);
    DMACBaseAddress[DMAC_number]->MaskSrcTran.LONGLONG |= (uint64_t) DMA_CHAN_ENABLE(channel);
    DMACBaseAddress[DMAC_number]->MaskDstTran.LONGLONG |= (uint64_t) DMA_CHAN_ENABLE(channel);

    /* Each channel has a dedicated enable bit and write-enable bit to configure the enable bits.
     They must be written to on the same write cycle. */
    DMACBaseAddress[DMAC_number]->ChEnReg.LONGLONG |= (uint64_t) DMA_CHAN_ENABLE(channel);
}
/***********************************************************************************************************************
 End of function dma_enablechannel
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_disablechannel
 *
 *  Return Value:   None
 *
 *  Parameters:     DMAC_number - Which DMA controller to configure.
 *                  channel - Which channel to disable.
 *
 *  Description:    Disables a DMA channel.
 *
 **********************************************************************************************************************/
void dma_disablechannel (uint8_t DMAC_number, uint8_t channel)
{
    /* enable bits are only written to if the corresponding write enable bit is asserted on the same write cycle */
    /* Mask interrupts */
    DMACBaseAddress[DMAC_number]->MaskTfr.LONGLONG = DMA_CHAN_DISABLE(channel);
    DMACBaseAddress[DMAC_number]->MaskBlock.LONGLONG = DMA_CHAN_DISABLE(channel);
    DMACBaseAddress[DMAC_number]->MaskSrcTran.LONGLONG = DMA_CHAN_DISABLE(channel);
    DMACBaseAddress[DMAC_number]->MaskDstTran.LONGLONG = DMA_CHAN_DISABLE(channel);

    /* Disable channel */
    DMACBaseAddress[DMAC_number]->ChEnReg.LONGLONG = DMA_CHAN_DISABLE(channel);
}
/***********************************************************************************************************************
 End of function dma_disablechannel
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  dma_playpause
 *
 *  Return Value:   None
 *
 *  Parameters:     DMAC_number - Which DMA controller to configure.
 *                  channel - Which channel to configure.
 *                  pause - play or pause the transfer
 *
 *  Description:    Suspend or resume DMA data transfers on a channel.
 *
 **********************************************************************************************************************/
void dma_playpause (uint8_t DMAC_number, uint8_t channel, bool pause)
{
    if (true == pause)
    {
        while (0 == DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CFG.BIT.FIFO_EMPTY)
            ;
        DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CFG.BIT.CH_SUSP = 1;
    }
    else
    {
        DMACBaseAddress[DMAC_number]->DMA_CHAN_SFR_LAYOUT[channel].CFG.BIT.CH_SUSP = 0;
    }
}
/***********************************************************************************************************************
 End of function dma_playpause
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  handle_dma_isr
 *
 *  Return Value:   None
 *
 *  Parameters:     irq_num_ptr - pointer to interrupt vector number
 *
 *  Description:    handle DMA Interrupt
 *
 **********************************************************************************************************************/
static void handle_dma_isr (IRQn_Type *irq_num_ptr)
{
    IRQn_Type irq_num = *irq_num_ptr;
    uint8_t chan;
    uint8_t dmac_number = (uint8_t)(irq_num - RZN1_IRQ_DMA0);

    dma_interrupt_status chan_int_stat[MAX_DMA_CHAN] = { 0 };

    if (MAX_DMAC > dmac_number)
    {
        for (chan = 0; chan < MAX_DMA_CHAN; chan++)
        {
            /* Check if Error Interrupt occurred */
            chan_int_stat[chan].ERROR = (DMACBaseAddress[dmac_number]->StatusErr.BIT.STATUS >> chan) & 0x01;
            DMACBaseAddress[dmac_number]->ClearErr.LONGLONG = chan_int_stat[chan].ERROR << chan;

            /* Check for destination interrupt */
            chan_int_stat[chan].DST_TRAN = (DMACBaseAddress[dmac_number]->StatusDstTran.BIT.STATUS >> chan) & 0x01;
            DMACBaseAddress[dmac_number]->ClearDstTran.LONGLONG = chan_int_stat[chan].DST_TRAN << chan;

            /* Check for source interrupt */
            chan_int_stat[chan].SRC_TRAN = (DMACBaseAddress[dmac_number]->StatusSrcTran.BIT.STATUS >> chan) & 0x01;
            DMACBaseAddress[dmac_number]->ClearSrcTran.LONGLONG = chan_int_stat[chan].SRC_TRAN << chan;

            /* Check for Block interrupt */
            chan_int_stat[chan].BLOCK_COMPLETE = (DMACBaseAddress[dmac_number]->StatusBlock.BIT.STATUS >> chan) & 0x01;
            DMACBaseAddress[dmac_number]->ClearBlock.LONGLONG = chan_int_stat[chan].BLOCK_COMPLETE << chan;

            /* Check for Transfer interrupt */
            chan_int_stat[chan].TRANS_COMPLETE = (DMACBaseAddress[dmac_number]->StatusTfr.BIT.STATUS >> chan) & 0x01;
            DMACBaseAddress[dmac_number]->ClearTfr.LONGLONG = chan_int_stat[chan].TRANS_COMPLETE << chan;

            /* Handle Interrupts */
            if (chan_int_stat[chan].BLOCK_COMPLETE)
            {
                dma_transfer_completed(dmac_number, chan);

                /* Callback function */
                if (FIT_NO_PTR != dma_callback[dmac_number][chan])
                {
                    (dma_callback[dmac_number][chan])(dmac_number, chan);
                }
            }
        }
    }
}
/***********************************************************************************************************************
 End of function handle_dma_isr
 **********************************************************************************************************************/