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
 * $Revision: 1305 $
 * $Date: 2019-02-26 08:39:27 +0000 (Tue, 26 Feb 2019) $
 *
 * PROJECT NAME :   RZ/N1 bare metal Drivers, Sample application
 * FILE         :   r_can_rzn1.c
 * Description  :   CAN driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "platform.h"
#include "r_can_rzn1_config.h"
#include "r_can_rzn1.h"
#include "iodefine.h"
#include "r_sysctrl_rzn1_if.h"
#include "mcu_interrupts_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define CAN_OCMODE_NORMAL                       (2)         /* 2'b10: Normal mode */
#define CAN_AxR_ALL_SET                         (0xFF)      /* Only the bottom eight bits of the ACR[n] and AMR[n] registers are used */
#define CAN_AMR_ALL_MASKED                      (0xFFFFFFFF)

#define CAN_FF_STD                              (0)         /* Standard Frame format */
#define CAN_FF_EXT                              (0x80)      /* Standard Frame format */
#define CAN_RTR                                 (0x40)      /* Remote Frame request */

/* Command Register */
#define CAN_SELF_RX_REQ                         (1<<4)
#define CAN_CLEAR_DATA_OVERRUN                  (1<<3)
#define CAN_RELEASE_RX_BUFF                     (1<<2)
#define CAN_ABORT_TX                            (1<<1)
#define CAN_TX_REQUEST                          (1<<0)

/* Status Register */
#define CAN_BUS_STATUS                          (1<<7)
#define CAN_ERROR_STATUS                        (1<<6)
#define CAN_TRANSMIT_STATUS                     (1<<5)
#define CAN_RECEIVE_STATUS                      (1<<4)
#define CAN_TRANSMISSION_COMPLETE_STATUS        (1<<3)
#define CAN_TRANSMIT_BUFFER_ACCESS              (1<<2)
#define CAN_DATA_OVERRUN                        (1<<1)
#define CAN_RECEIVE_BUFFER_STATUS               (1<<0)

/* Interrupt Register */
#define CAN_ERROR_BUSOFF_INT                    (1<<7)
#define CAN_ARBITR_LOST_INT                     (1<<6)
#define CAN_ERROR_PASSIVE_INT                   (1<<5)
#define CAN_WAKEUP_INT                          (1<<4)
#define CAN_OVERRUN_INT                         (1<<3)
#define CAN_ERROR_INT                           (1<<2)
#define CAN_TRANSMIT_INT                        (1<<1)
#define CAN_RECEIVE_INT                         (1<<0)

#define CAN_PASSIVE_ERROR_TRIGGER               (127)

#define CAN_SYNC_START_MAGIC_NUMBER             (0x2052756Eul)
#define CAN_SYNC_STOP_MAGIC_NUMBER              (0x53746f70ul)

#define CALC_BTR0(SJW, BRP)                     (((uint32_t)(SJW) << 6)  | (uint32_t)(((BRP) / 2) - 1))
#define CALC_BTR1(SAM, TSEG1, TSEG2)            (((uint32_t)(SAM) << 7) | ((uint32_t)((TSEG2) - 1) << 4) | (uint32_t)((TSEG1) - 1))

#if CAN_CFG_PARAM_CHECKING_ENABLE
#define CAN_DRIVER_CONFIG_CHECKS(chan_num)      \
                                                                                        \
                                                    if (CAN_CHAN_MAX <= (chan_num))     \
                                                    {                                   \
                                                        return ER_PARAM;                \
                                                    }
#else
#define CAN_DRIVER_CONFIG_CHECKS(chan_num)
#endif

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/*
 * To be sure that your utilization agreed with the CAN 2.0 specification, please follow these simple rules:
 * "Resynchronization jump width" (SJW) must be set from 1 to 4 Tq.
 * "Propagation Segment" must be set from 1 to 8 Tq.
 * "1st Phase Buffer" must be set from "SJW" to 8 Tq.
 * "2nd Phase Buffer" must be set from "1st Phase Buffer" to "1st Phase Buffer" + 2 Tq.
 * Applying to the Can controller registers:
 * bCan_SJW = SJW - 1
 * bCan_TSEG1 = "Propagation Segment" + "1st Phase Buffer" - 1
 * bCan_TSEG2 = "2nd Phase Buffer" - 1
 *
 * In theory, it is possible to define bit periods of between 4 and 25 Tq through these register settings.
 * However, the bit periods used in practice are required to follow the BOSCH standard, which defines bit periods
 * between 8 and 25 Tq in length.
 */
typedef struct
{
    union
    {
        uint16_t btr0;

        struct
        {
            unsigned bCan_BRP :7; /* Pre-scaler for H-Clock period */
            unsigned bCan_SJW :3; /* Synchronization jump size. */
        };
    };

    union
    {
        uint16_t btr1;

        struct
        {
            unsigned bCan_TSEG1 :5; /* Number of quanta after sample */
            unsigned bCan_TSEG2 :4; /* Number of quanta before sample */
            unsigned bCan_SAM :2; /* Set to 1 for 3 bus samplings or 0 for 1 bus sampling */
        };
    };
} CAN_BITRATE_SETUP_T;

/* Structures to help split out the correct positioning of bits */
typedef union
{
    struct
    {
        unsigned :3;
        unsigned all :29;
    };

    struct
    {
        unsigned bits_4_0 :8; /* 8bits to give correct bit positions when copying to a byte */
        unsigned bits_12_5 :8;
        unsigned bits_20_13 :8;
        unsigned bits_28_21 :8;
    };
} CAN_29_BIT_ID_T;

typedef union
{
    struct
    {
        unsigned :21;
        unsigned all :11;
    };

    struct
    {
        unsigned :16;
        unsigned bits_2_0 :8; /* 8bits to give correct bit positions when copying to a byte */
        unsigned bits_10_3 :8;
    };
} CAN_11_BIT_ID_T;

/* Useful structure for single filter mode */
typedef union
{
    uint32_t value;

    union
    {
        struct
        {
            unsigned :21;
            unsigned all :11;
        };

        struct
        {
            unsigned :20;
            unsigned rtr :1;
        };
    } _11bits;

    union
    {
        struct
        {
            unsigned :3;
            unsigned all :29;
        };

        struct
        {
            unsigned :2;
            unsigned rtr :1;
        };
    } _29bits;

    struct
    {
        unsigned id_4_0 :8; /* 8bits to give correct bit positions when copying to a byte */
        unsigned id_12_5 :8;
        unsigned id_20_13 :8;
        unsigned id_28_21 :8;
    };

    struct
    {
        unsigned :16;
        unsigned id_20_18 :8; /* 8bits to give correct bit positions when copying to a byte */
    };
} CAN_FILT_MASK_T;

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static bool m_can_ready;
static volatile CAN_Type * m_can_registers[CAN_CHAN_MAX];
static CAN_STATS_T m_can_stats[CAN_CHAN_MAX];
static CAN_CONFIG_T m_can_config[CAN_CHAN_MAX];
static bool m_is_tx_single_shot[CAN_CHAN_MAX];
static bool m_is_self_rx[CAN_CHAN_MAX];
static can_event_callback_t m_can_event_callback[CAN_CHAN_MAX];

/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           can_handle_rx
 *
 *  Return value:       none
 *
 *  Parameters:         chan_num CAN channel Number
 *
 *  Description:        Handle CAN RX interrupt
 *
 **********************************************************************************************************************/
static void can_handle_rx (uint8_t chan_num)
{
    CAN_MSG_T can_msg;

    /* Read message header */
    uint32_t frame_info = m_can_registers[chan_num]->rCan_WrTxBuf0_RdRxBuf0_ACR0.rCan_WrTransmitBuffer_0.BIT.bCan_WrTransmitBuffer;
    volatile uint32_t * ptr_tx_buff_data;
    uint32_t msg_id = 0;

    /* Read message ID TYPE */
    if (CAN_FF_EXT & frame_info)
    {
        /* Extended ID */
        CAN_29_BIT_ID_T id;

        can_msg.extended_flag = true;
        /* Decode extended message ID */
        id.bits_28_21 = m_can_registers[chan_num]->rCan_WrTxBuf1_RdRxBuf1_ACR1.rCan_WrTransmitBuffer_1.BIT.bCan_WrTransmitBuffer;
        id.bits_20_13 = m_can_registers[chan_num]->rCan_WrTxBuf2_RdRxBuf2_ACR2.rCan_WrTransmitBuffer_2.BIT.bCan_WrTransmitBuffer;
        id.bits_12_5  = m_can_registers[chan_num]->rCan_WrTxBuf3_RdRxBuf3_ACR3.rCan_WrTransmitBuffer_3.BIT.bCan_WrTransmitBuffer;
        id.bits_4_0   = m_can_registers[chan_num]->rCan_WrTxBuf4_RdRxBuf4_AMR0.rCan_WrTransmitBuffer_4.BIT.bCan_WrTransmitBuffer;
        msg_id = id.all; /* Normalise bit positioning */
        /* Set correct start position of data buffer */
        ptr_tx_buff_data = (uint32_t *) &m_can_registers[chan_num]->rCan_WrTxBuf5_RdRxBuf5_AMR1;
    } else
    {
        /* Standard ID */
        CAN_11_BIT_ID_T id;

        can_msg.extended_flag = false;
        /* Decode standard message ID */
        id.bits_10_3 = m_can_registers[chan_num]->rCan_WrTxBuf1_RdRxBuf1_ACR1.rCan_WrTransmitBuffer_1.BIT.bCan_WrTransmitBuffer;
        id.bits_2_0  = m_can_registers[chan_num]->rCan_WrTxBuf2_RdRxBuf2_ACR2.rCan_WrTransmitBuffer_2.BIT.bCan_WrTransmitBuffer;
        msg_id = id.all; /* Normalise bit positioning */
        /* Set correct start position of data buffer */
        ptr_tx_buff_data = (uint32_t *) &m_can_registers[chan_num]->rCan_WrTxBuf3_RdRxBuf3_ACR3;
    }

    /* Read frame type */
    if (CAN_RTR & frame_info)
    {
        /* RTR bit is set */
        can_msg.rtr_flag = true;
    }
    else
    {
        /* Not a RTR */
        can_msg.rtr_flag = false;
    }

    /* build message */
    can_msg.data_len = (unsigned char) (frame_info & 0x0F);
    can_msg.data_len = (can_msg.data_len > CAN_DATA_LEN_MAX) ?
    CAN_DATA_LEN_MAX : can_msg.data_len;
    can_msg.id = msg_id;

    if ( !can_msg.rtr_flag)
    {
        uint8_t i;
        /* data frame - save message data */
        for (i = 0; i < can_msg.data_len; i++)
        {
            can_msg.data[i] = (uint8_t) ptr_tx_buff_data[i];
        }
    }

    /* Update Rx stats */
    if (can_msg.extended_flag)
    {
        m_can_stats[chan_num].rx_msgs_ext++;
    }
    else
    {
        m_can_stats[chan_num].rx_msgs_std++;
    }
    m_can_stats[chan_num].rx_msgs_total++;

    /* Callback function to upper layer */
    if (FIT_NO_PTR != m_can_event_callback[chan_num])
    {
        m_can_event_callback[chan_num](chan_num, CAN_EVENT_RX, &can_msg);
    }
}
/***********************************************************************************************************************
 End of function can_handle_rx
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           can_handle_interrupt
 *
 *  Return value:       none
 *
 *  Parameters:         IRQn_Type Interrupt Type
 *
 *  Description:        handle CAN interrupt
 *
 **********************************************************************************************************************/
static void can_handle_interrupt (IRQn_Type *irq_num_ptr)
{
    static bool bus_active[CAN_CHAN_MAX] = { false, false };
    uint32_t irq_num = *irq_num_ptr;
    uint8_t chan_num;

    if (RZN1_IRQ_CAN0 == irq_num)
    {
        chan_num = CAN_CHAN_1;
    }
    else if (RZN1_IRQ_CAN1 == irq_num)
    {
        chan_num = CAN_CHAN_2;
    }
    else
    {
        /* Error Case */
        while (1);
    }

    uint32_t int_status = m_can_registers[chan_num]->rCan_IR.LONG;

    /* Check interrupt status */
    while (int_status)
    {
        uint32_t can_status = m_can_registers[chan_num]->rCan_SR.LONG;

        /* Error Interrupt */
        if ((CAN_ERROR_BUSOFF_INT | CAN_ERROR_PASSIVE_INT | CAN_ERROR_INT) & int_status)
        {
            /* Read hardware and select CAN Controller state */
            if ((CAN_ERROR_BUSOFF_INT | CAN_ERROR_INT) & int_status)
            { /* Bus-off */
                if (CAN_BUS_STATUS & can_status)
                {
                    bus_active[chan_num] = false;

                    m_can_stats[chan_num].bus_off_errors++;
                    /* Callback function to upper layer */
                    if (FIT_NO_PTR != m_can_event_callback[chan_num])
                    {
                        m_can_event_callback[chan_num](chan_num, CAN_EVENT_ERR_BUSOFF, FIT_NO_PTR);
                    }
                }
            }

            if (CAN_ERROR_PASSIVE_INT & int_status)
            { /* Error Passive */
                if ((m_can_registers[chan_num]->rCan_TXERR.BIT.bCan_TXERR > CAN_PASSIVE_ERROR_TRIGGER)
                        || (m_can_registers[chan_num]->rCan_RXERR.BIT.bCan_RXERR > CAN_PASSIVE_ERROR_TRIGGER))
                {
                    m_can_stats[chan_num].bus_passive_errors++;
                    /* Callback function to upper layer */
                    if (FIT_NO_PTR != m_can_event_callback[chan_num])
                    {
                        m_can_event_callback[chan_num](chan_num, CAN_EVENT_ERR_PASSIVE, FIT_NO_PTR);
                    }
                }
                else
                {
                    bus_active[chan_num] = true;
                    m_can_stats[chan_num].bus_active_errors++;
                    /* Callback function to upper layer */
                    if (FIT_NO_PTR != m_can_event_callback[chan_num])
                    {
                        m_can_event_callback[chan_num](chan_num, CAN_EVENT_ERR_ACTIVE, FIT_NO_PTR);
                    }
                }
            }
        }
        /* Status IRQ */
        else
        {
            /* Error handling - the controller can transmit or receive
             *    if the former state was INIT or BUSOFF,
             *    now the controller is in-ACTIVE
             *
             * Error handling-if can send or receive and beforehand
             * If the bus-off or initialisation state then we are now in error active state
             * This entry to this state is not classed as a fault so the error counter is
             * not incremented.
             */
            if (false == bus_active[chan_num])
            { /* Bus-off -> Active */
                bus_active[chan_num] = true;
                /* Callback function to upper layer */
                if (FIT_NO_PTR != m_can_event_callback[chan_num])
                {
                    m_can_event_callback[chan_num](chan_num, CAN_EVENT_ERR_ACTIVE, FIT_NO_PTR);
                }
            }
        }

        /* Check receive events */
        while ((CAN_RECEIVE_BUFFER_STATUS + CAN_DATA_OVERRUN) & can_status)
        {
            /* while unread message in the buffer */
            if (CAN_RECEIVE_BUFFER_STATUS & can_status)
            {
                /* read out receive message */
                can_handle_rx(chan_num);
            }
            /* check for hardware CAN buffer overflow */
            if (CAN_DATA_OVERRUN & can_status)
            {
                m_can_stats[chan_num].data_overrun_errors++;
                /* Callback function to upper layer */
                if (FIT_NO_PTR != m_can_event_callback[chan_num])
                {
                    m_can_event_callback[chan_num](chan_num, CAN_EVENT_ERR_OVERRUN, FIT_NO_PTR);
                }
            }

            /* Release receive buffer and clear bus overrun */
            m_can_registers[chan_num]->rCan_CMR.BIT.bCan_RRB = 1;
            m_can_registers[chan_num]->rCan_CMR.BIT.bCan_CDO = 1;

            /* Pick up status value for next loop iteration */
            can_status = m_can_registers[chan_num]->rCan_SR.LONG;
        }

        /* Transmit Interrupt */
        if (CAN_TRANSMIT_INT & int_status)
        {
            m_can_stats[chan_num].tx_msgs_total++;
            /* Callback function to upper layer */
            if (FIT_NO_PTR != m_can_event_callback[chan_num])
            {
                m_can_event_callback[chan_num](chan_num, CAN_EVENT_TX, FIT_NO_PTR);
            }
        }

        /* Check for new Interrupts */
        int_status = m_can_registers[chan_num]->rCan_IR.LONG;
    }
}
/***********************************************************************************************************************
 End of function can_handle_interrupt
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       can_init
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Initialises the CAN driver
 *
 **********************************************************************************************************************/
ER_RET can_init (void)
{
    ER_RET ret_val = ER_OK;
    uint8_t chan_num;

    if (m_can_ready)
    {
        return ER_INVAL;
    }

    /* Get pointer to register set */
    m_can_registers[CAN_CHAN_1] = (volatile CAN_Type *)(CAN1);
    m_can_registers[CAN_CHAN_2] = (volatile CAN_Type *)(CAN2);

    /* Enable CAN Clocks*/
    ret_val = R_SYSCTRL_EnableCAN();

    if (ER_OK == ret_val)
    {
        for (chan_num = CAN_CHAN_1; chan_num < CAN_CHAN_MAX; chan_num++)
        {
            memset((void *) &m_can_stats[chan_num], 0, sizeof(CAN_STATS_T));
            (void) can_set_test_mode(chan_num, CAN_TMODE_NONE);

            /* Ensure reset is inactive */
            m_can_registers[chan_num]->rCan_MOD.BIT.bCan_RM = 0;
            if (0 != m_can_registers[chan_num]->rCan_MOD.BIT.bCan_RM)
            {
                return ER_SYS;
            }

            /* Make a reset request */
            can_reset_enter(chan_num);

            /* Set output control register to normal mode */
            m_can_registers[chan_num]->rCan_OCR.BIT.bCan_OCMODE = CAN_OCMODE_NORMAL; /* Normal is the only mode that is supported */

            /* Ensure there is no filter */
            ret_val = can_set_filter(chan_num, FIT_NO_PTR);
            if (ER_OK != ret_val)
            {
                return ret_val;
            }

            /* Set filter mode */
            m_can_registers[chan_num]->rCan_MOD.BIT.bCan_AFM = 1; /* Only use single filter mode to avoid over-complicating reference code and use cases*/

            /* Enable Interrupts */
            m_can_registers[chan_num]->rCan_IER.BIT.bCan_RIE = 1;
            m_can_registers[chan_num]->rCan_IER.BIT.bCan_TIE = 1;
            m_can_registers[chan_num]->rCan_IER.BIT.bCan_EIE = 1; /* Error Warning */
            m_can_registers[chan_num]->rCan_IER.BIT.bCan_DOIE = 1; /* Data Overrun */
            m_can_registers[chan_num]->rCan_IER.BIT.bCan_EPIE = 1; /* Error Passive */
            m_can_registers[chan_num]->rCan_IER.BIT.bCan_BEIE = 1; /* Bus Error */

            /* Clear error count registers */
            m_can_registers[chan_num]->rCan_TXERR.BIT.bCan_TXERR = 0;
            m_can_registers[chan_num]->rCan_RXERR.BIT.bCan_RXERR = 0;
            /* Read interrupt registers in order to reset CAN interrupts */
            volatile uint32_t temp = m_can_registers[chan_num]->rCan_IR.LONG;
        }

        /* Set default bit-rate */
        can_set_bit_rate(CAN_CHAN_1, CAN_CHAN1_DEFAULT_BITRATE);
        can_set_bit_rate(CAN_CHAN_2, CAN_CHAN2_DEFAULT_BITRATE);

        m_can_ready = true;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function can_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       can_uninitialise
 *
 *  Return value:   Error Status
 *
 *  Parameters:     void
 *
 *  Description:    Uninitialises CAN peripheral.
 *
 **********************************************************************************************************************/
ER_RET can_uninitialise (void)
{
    ER_RET ret_val = ER_OK;

    if ( !m_can_ready)
    {
        return ER_INVAL;
    }

    R_SYSCTRL_DisableCAN();
    m_can_ready = false;

    /* Clear register pointer */
    m_can_registers[CAN_CHAN_1] = FIT_NO_PTR;
    m_can_registers[CAN_CHAN_2] = FIT_NO_PTR;

    return ret_val;
}
/***********************************************************************************************************************
 End of function can_uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       can_channel_open
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - CAN channel number to open
 *
 *  Description:    Opens a CAN channel
 *
 **********************************************************************************************************************/
ER_RET can_channel_open (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_type;

    if ( !m_can_ready)
    {
        return ER_INVAL;
    }

    if (CAN_CHAN_1 == chan_num)
    {
        irq_type = RZN1_IRQ_CAN0;
    }
    else if (CAN_CHAN_2 == chan_num)
    {
        irq_type = RZN1_IRQ_CAN1;
    }
    else
    {
        return ER_PARAM;
    }

    /* Set interrupt priority for CAN & disable CAN interrupts for current channel */
    if (R_BSP_InterruptRegisterCallback(irq_type, (bsp_int_cb_t) &can_handle_interrupt) == MCU_INT_SUCCESS)
    {
        uint32_t int_priority = CAN_DEFAULT_INT_PRIORITY;

        ret_val = R_BSP_InterruptControl(irq_type, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
        if (MCU_INT_SUCCESS != ret_val)
        {
            ret_val = ER_SYS;
        }
        else
        {
            ret_val = R_BSP_InterruptControl(irq_type, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
        }
    }
    else
    {
        ret_val = ER_SYS;
    }

    if (ER_OK == ret_val)
    {
        /* Release from reset */
        can_reset_exit(chan_num);
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function can_channel_open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       can_channel_close
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *
 *  Description:    Closes a CAN channel
 *
 **********************************************************************************************************************/
ER_RET can_channel_close (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

    if ( !m_can_ready)
    {
        return ER_INVAL;
    }

    CAN_DRIVER_CONFIG_CHECKS(chan_num);

    /* Clear all test modes */
    (void) can_set_test_mode(chan_num, CAN_TMODE_NONE);
    /* Place the channel into reset condition */
    can_reset_enter(chan_num);

    /* Clear callback and disable CAN interrupt */
    ret_val = can_register_channel_callback(chan_num, FIT_NO_PTR);

    return ret_val;
}
/***********************************************************************************************************************
 End of function can_channel_close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       can_write
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The CAN channel number
 *                  ptr_acq_cmd - Acquisition command
 *
 *  Description:    Initiates the requested CAN read.
 *
 **********************************************************************************************************************/
ER_RET can_write (uint8_t chan_num, CAN_MSG_T * ptr_msg)
{
    ER_RET ret_val = ER_OK;
    volatile uint32_t * ptr_tx_buff_data;
    uint8_t frame_hdr;
    uint8_t tx_mode;

    CAN_DRIVER_CONFIG_CHECKS(chan_num);

    if ( !m_can_ready)
    {
        return ER_INVAL;
    }

    if (m_can_registers[chan_num]->rCan_MOD.BIT.bCan_RM)
    {
        /* Device is  in reset mode. Invalid to Tx to bus now */
        return ER_INVAL;
    }

#if CAN_CFG_PARAM_CHECKING_ENABLE
    if (FIT_NO_PTR == ptr_msg)
    {
        return ER_PARAM;
    }
    if (CAN_DATA_LEN_MAX < ptr_msg->data_len)
    {
        return ER_PARAM;
    }
#endif

    /* Check if channel ready */
    if (m_can_registers[chan_num]->rCan_MOD.BIT.bCan_RM)
    {
        return ER_INVAL;
    }

    /* Check if there is room in the Tx buffer */
    if (0 == m_can_registers[chan_num]->rCan_SR.BIT.bCan_TBS)
    {
        return ER_BUSY;
    }

    if (ptr_msg->extended_flag)
    {
        /* Extended ID */
        CAN_29_BIT_ID_T id;

        id.all = ptr_msg->id;
        m_can_registers[chan_num]->rCan_WrTxBuf1_RdRxBuf1_ACR1.rCan_WrTransmitBuffer_1.BIT.bCan_WrTransmitBuffer = (uint8_t)(id.bits_28_21);
        m_can_registers[chan_num]->rCan_WrTxBuf2_RdRxBuf2_ACR2.rCan_WrTransmitBuffer_2.BIT.bCan_WrTransmitBuffer = (uint8_t)(id.bits_20_13);
        m_can_registers[chan_num]->rCan_WrTxBuf3_RdRxBuf3_ACR3.rCan_WrTransmitBuffer_3.BIT.bCan_WrTransmitBuffer = (uint8_t)(id.bits_12_5);
        m_can_registers[chan_num]->rCan_WrTxBuf4_RdRxBuf4_AMR0.rCan_WrTransmitBuffer_4.BIT.bCan_WrTransmitBuffer = (uint8_t)(id.bits_4_0);
        /* Configure for Extended Frame */
        frame_hdr = CAN_FF_EXT;
        ptr_tx_buff_data = (uint32_t *) &m_can_registers[chan_num]->rCan_WrTxBuf5_RdRxBuf5_AMR1;
        m_can_stats[chan_num].tx_msgs_ext++;
    }
    else
    {
        /* Standard ID */
        CAN_11_BIT_ID_T id;

        id.all = ptr_msg->id;
        m_can_registers[chan_num]->rCan_WrTxBuf1_RdRxBuf1_ACR1.rCan_WrTransmitBuffer_1.BIT.bCan_WrTransmitBuffer = (uint8_t)(id.bits_10_3);
        m_can_registers[chan_num]->rCan_WrTxBuf2_RdRxBuf2_ACR2.rCan_WrTransmitBuffer_2.BIT.bCan_WrTransmitBuffer = (uint8_t)(id.bits_2_0);
        /* Configure for Standard Frame */
        frame_hdr = CAN_FF_STD;
        ptr_tx_buff_data = (uint32_t *) &m_can_registers[chan_num]->rCan_WrTxBuf3_RdRxBuf3_ACR3;
        m_can_stats[chan_num].tx_msgs_std++;
    }

    /* Write in data length to frame header */
    frame_hdr += ptr_msg->data_len;

    if (ptr_msg->rtr_flag)
    {
        /* Transmit Remote Frames */
        frame_hdr |= CAN_RTR;
    }
    else
    {
        /* Transmit data frame */
        uint8_t i;
        /* Set data */
        for (i = 0; i < ptr_msg->data_len; i++)
        {
            ptr_tx_buff_data[i] = ptr_msg->data[i];
        }
    }

    /* Write header to CAN controller */
    m_can_registers[chan_num]->rCan_WrTxBuf0_RdRxBuf0_ACR0.rCan_WrTransmitBuffer_0.BIT.bCan_WrTransmitBuffer = frame_hdr;

    tx_mode = (m_is_self_rx[chan_num] ? CAN_SELF_RX_REQ : CAN_TX_REQUEST) | (m_is_tx_single_shot[chan_num] ? CAN_ABORT_TX : 0);

    /* If CAN_ABORT_TX is set it needs to be set simultaneously with the Tx request */
    m_can_registers[chan_num]->rCan_CMR.LONG = tx_mode;

    return ret_val;
}
/***********************************************************************************************************************
 End of function can_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       can_get_channel_config
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - The CAN channel number
 *                  ptr_config - pointer to config information
 *
 *  Description:    Gets the selected channel configuration
 *
 **********************************************************************************************************************/
ER_RET can_get_channel_config (uint8_t chan_num, CAN_CONFIG_T * ptr_config)
{
    ER_RET ret_val = ER_OK;

    if ( !m_can_ready)
    {
        return ER_INVAL;
    }

    CAN_DRIVER_CONFIG_CHECKS(chan_num);

#if CAN_CFG_PARAM_CHECKING_ENABLE
    if (FIT_NO_PTR == ptr_config)
    {
        return ER_PARAM;
    }
#endif

    *ptr_config = m_can_config[chan_num];
    return ret_val;
}
/***********************************************************************************************************************
 End of function can_get_channel_config
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           can_register_channel_callback
 *
 *  Return value:       Error status
 *
 *  Parameters:         chan_num - The CAN channel number
 *                      chan_callback -the channel callback to register.
 *                       Note: if FIT_NO_PTR is supplied then this de-registers
 *                       any existing callback and turns of the associated interrupt
 *
 *  Description:        Registers a channel callback
 *
 **********************************************************************************************************************/
ER_RET can_register_channel_callback (uint8_t chan_num, can_event_callback_t chan_callback)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_type;

    if ( !m_can_ready)
    {
        return ER_INVAL;
    }

    if (CAN_CHAN_1 == chan_num)
    {
        irq_type = RZN1_IRQ_CAN0;
    }
    else if (CAN_CHAN_2 == chan_num)
    {
        irq_type = RZN1_IRQ_CAN1;
    }
    else
    {
        return ER_PARAM;
    }

    /* Always Disable interrupt as needs disabling if either new interrupt settings or supplying FIT_NO_PTR pointer for a callback */
    ret_val = R_BSP_InterruptControl(irq_type, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
    if (ER_OK != ret_val)
    {
        return ret_val;
    }

    if (FIT_NO_PTR == chan_callback)
    {
        /* No callback supplied so remove any existing callback */
        m_can_event_callback[chan_num] = FIT_NO_PTR;
    }
    else
    {
        /* callback supplied so register it */
        m_can_event_callback[chan_num] = chan_callback;
        ret_val = R_BSP_InterruptControl(irq_type, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR); /* Make sure interrupt is enabled */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function can_register_channel_callback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           can_set_bit_rate
 *
 *  Return value:       Error status
 *
 *  Parameters:         chan_num - The CAN channel number
 *                      bitrate - bit-rate to configure the CAN bus to
 *
 *  Description:        Sets bitrate of CAN channel bus
 *
 **********************************************************************************************************************/
ER_RET can_set_bit_rate (uint8_t chan_num, CAN_BITRATE_T bitrate)
{
    const CAN_BITRATE_SETUP_T bit_rates[] =
    {
        { .bCan_SJW = 0, .bCan_BRP = 100,.bCan_SAM = 0,.bCan_TSEG1 = 16, .bCan_TSEG2 = 7 }, /*  20Kbits */
        { .bCan_SJW = 0, .bCan_BRP = 60,.bCan_SAM = 0, .bCan_TSEG1 = 13, .bCan_TSEG2 = 2 }, /*  50Kbits */
        { .bCan_SJW = 0, .bCan_BRP = 30,.bCan_SAM = 0, .bCan_TSEG1 = 13, .bCan_TSEG2 = 2 }, /* 100Kbits */
        { .bCan_SJW = 0, .bCan_BRP = 24,.bCan_SAM = 0, .bCan_TSEG1 = 13, .bCan_TSEG2 = 2 }, /* 125Kbits */
        { .bCan_SJW = 0, .bCan_BRP = 12,.bCan_SAM = 0, .bCan_TSEG1 = 13, .bCan_TSEG2 = 2 }, /* 250Kbits */
        { .bCan_SJW = 0, .bCan_BRP = 6, .bCan_SAM = 0, .bCan_TSEG1 = 13, .bCan_TSEG2 = 2 }, /* 500Kbits */
        { .bCan_SJW = 0, .bCan_BRP = 6, .bCan_SAM = 0, .bCan_TSEG1 = 8,  .bCan_TSEG2 = 1 }, /* 800Kbits */
        { .bCan_SJW = 0, .bCan_BRP = 2, .bCan_SAM = 0, .bCan_TSEG1 = 16, .bCan_TSEG2 = 7 }, /* 1000Kbits */
    };

    const CAN_BITRATE_SETUP_T * p_bitrate = &bit_rates[bitrate];

    CAN_DRIVER_CONFIG_CHECKS(chan_num);

    /* CAN Channel must be in reset mode to change this setting */
    if (0 == m_can_registers[chan_num]->rCan_MOD.BIT.bCan_RM)
    {
        /* Device is not in reset mode. Invalid to change the bus configuration now */
        return ER_INVAL;
    }

#if CAN_CFG_PARAM_CHECKING_ENABLE
    if (CAN_BR_INVALID <= bitrate)
    {
        return ER_PARAM;
    }
#endif

    /* Clear reset bit */
    m_can_registers[chan_num]->rCan_BTR0.LONG = CALC_BTR0(p_bitrate->bCan_SJW, p_bitrate->bCan_BRP);
    m_can_registers[chan_num]->rCan_BTR1.LONG = CALC_BTR1(p_bitrate->bCan_SAM, p_bitrate->bCan_TSEG1, p_bitrate->bCan_TSEG2);
    m_can_config[chan_num].bitrate = bitrate;
    return ER_OK;
}
/***********************************************************************************************************************
 End of function can_set_bit_rate
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           can_set_filter
 *
 *  Return value:       Error status
 *
 *  Parameters:         chan_num - The CAN channel number
 *                      ptr_filter - Acceptance filter for channel
 *
 *  Description:        Sets Acceptance filter for CAN channel bus
 *
 **********************************************************************************************************************/
ER_RET can_set_filter (uint8_t chan_num, CAN_FILTER_T * ptr_filter)
{
    ER_RET ret_val = ER_OK;
    CAN_FILT_MASK_T accept = { .value = 0 };
    CAN_FILT_MASK_T mask   = { .value = CAN_AMR_ALL_MASKED }; /* Ensure any non-explicitly set bit is masked out */

    CAN_DRIVER_CONFIG_CHECKS(chan_num);

    /* CAN Channel must be in reset mode to change this setting */
    if (0 == m_can_registers[chan_num]->rCan_MOD.BIT.bCan_RM)
    {
        /* Device is not in reset mode. Invalid to change the bus configuration now */
        return ER_INVAL;
    }

    /* Remove all filtering */
    m_can_registers[chan_num]->rCan_WrTxBuf4_RdRxBuf4_AMR0.rCan_AMR0.BIT.bCan_AMR = CAN_AxR_ALL_SET;
    m_can_registers[chan_num]->rCan_WrTxBuf5_RdRxBuf5_AMR1.rCan_AMR1.BIT.bCan_AMR = CAN_AxR_ALL_SET;
    m_can_registers[chan_num]->rCan_WrTxBuf6_RdRxBuf6_AMR2.rCan_AMR2.BIT.bCan_AMR = CAN_AxR_ALL_SET;
    m_can_registers[chan_num]->rCan_WrTxBuf7_RdRxBuf7_AMR3.rCan_AMR3.BIT.bCan_AMR = CAN_AxR_ALL_SET;

    if (FIT_NO_PTR != ptr_filter)
    {
        /* Setup a filter */
        if (ptr_filter->is_extended)
        {
            /* Extended Frame */
            accept._29bits.all = ptr_filter->accept;
            mask._29bits.all = ptr_filter->mask;

            if (CAN_FRTR_DONT_CARE != ptr_filter->is_rtr)
            {
                accept._29bits.rtr = ptr_filter->is_rtr;
                mask._29bits.rtr = 0; /* Ensure RTR bit is not masked out */
            }

            /* Set acceptance filter */
            m_can_registers[chan_num]->rCan_WrTxBuf0_RdRxBuf0_ACR0.rCan_ACR0.BIT.bCan_ACR = accept.id_28_21;
            m_can_registers[chan_num]->rCan_WrTxBuf1_RdRxBuf1_ACR1.rCan_ACR1.BIT.bCan_ACR = accept.id_20_13;
            m_can_registers[chan_num]->rCan_WrTxBuf2_RdRxBuf2_ACR2.rCan_ACR2.BIT.bCan_ACR = accept.id_12_5;
            m_can_registers[chan_num]->rCan_WrTxBuf3_RdRxBuf3_ACR3.rCan_ACR3.BIT.bCan_ACR = accept.id_4_0;
            /* Set filter mask */
            m_can_registers[chan_num]->rCan_WrTxBuf4_RdRxBuf4_AMR0.rCan_AMR0.BIT.bCan_AMR = mask.id_28_21;
            m_can_registers[chan_num]->rCan_WrTxBuf5_RdRxBuf5_AMR1.rCan_AMR1.BIT.bCan_AMR = mask.id_20_13;
            m_can_registers[chan_num]->rCan_WrTxBuf6_RdRxBuf6_AMR2.rCan_AMR2.BIT.bCan_AMR = mask.id_12_5;
            m_can_registers[chan_num]->rCan_WrTxBuf7_RdRxBuf7_AMR3.rCan_AMR3.BIT.bCan_AMR = mask.id_4_0;
        } else
        {
            /* Standard Frame */
            accept._11bits.all = ptr_filter->accept;
            mask._11bits.all = ptr_filter->mask;

            if (CAN_FRTR_DONT_CARE != ptr_filter->is_rtr)
            {
                accept._11bits.rtr = ptr_filter->is_rtr;
                mask._11bits.rtr = 0; /* Ensure RTR bit is not masked out */
            }

            /* Set acceptance filter */
            m_can_registers[chan_num]->rCan_WrTxBuf0_RdRxBuf0_ACR0.rCan_ACR0.BIT.bCan_ACR = accept.id_28_21;
            m_can_registers[chan_num]->rCan_WrTxBuf1_RdRxBuf1_ACR1.rCan_ACR1.BIT.bCan_ACR = accept.id_20_18;
            /* Set filter mask */
            m_can_registers[chan_num]->rCan_WrTxBuf4_RdRxBuf4_AMR0.rCan_AMR0.BIT.bCan_AMR = mask.id_28_21;
            m_can_registers[chan_num]->rCan_WrTxBuf5_RdRxBuf5_AMR1.rCan_AMR1.BIT.bCan_AMR = mask.id_20_18;
            /*
             * NOTE: We could also filter on the first two data bytes of the message. This is not allowed in this driver
             *       for reasons of simplification.
             */
        }

        m_can_config[chan_num].filter = *ptr_filter;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function can_set_filter
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           can_sync_pulse_start
 *
 *  Return value:       Error status
 *
 *  Parameters:         chan_num - The CAN channel number
 *                      ptr_sync_config - configuration information for Sync Pulse
 *
 *  Description:        Configures and Starts Sync Pulse (CANopen) on CAN channel bus
 *
 **********************************************************************************************************************/
ER_RET can_sync_pulse_start(uint8_t chan_num, CAN_SYNC_PULSE_T * ptr_sync_config)
{
    volatile uint32_t * ptr_tx_buff_data;
    uint8_t frame_hdr;

    CAN_DRIVER_CONFIG_CHECKS(chan_num);

#if CAN_CFG_PARAM_CHECKING_ENABLE
    if (FIT_NO_PTR == ptr_sync_config)
    {
        return ER_PARAM;
    }
#endif

    m_can_registers[chan_num]->rCan_SyncPeriod.BIT.bCan_SyncPeriod = ptr_sync_config->sync_period_in_bits;
    m_can_registers[chan_num]->rCan_SyncPeriod.BIT.bCan_SyncMaskFrameTime = (ptr_sync_config->sync_period_in_bits / 10); /* Needs to be at least 8 times less than sync_period_in_bits */

    if (ptr_sync_config->sync_msg.extended_flag)
    {
        /* Extended ID */
        CAN_29_BIT_ID_T id;

        id.all = ptr_sync_config->sync_msg.id;
        m_can_registers[chan_num]->rCan_SyncTransmitBuffer_1.BIT.bCan_SyncTransmitBuffer = (uint8_t)(id.bits_28_21);
        m_can_registers[chan_num]->rCan_SyncTransmitBuffer_2.BIT.bCan_SyncTransmitBuffer = (uint8_t)(id.bits_20_13);
        m_can_registers[chan_num]->rCan_SyncTransmitBuffer_3.BIT.bCan_SyncTransmitBuffer = (uint8_t)(id.bits_12_5);
        m_can_registers[chan_num]->rCan_SyncTransmitBuffer_4.BIT.bCan_SyncTransmitBuffer = (uint8_t)(id.bits_4_0);
        /* Configure for extended frame */
        frame_hdr = CAN_FF_EXT;
        ptr_tx_buff_data = (uint32_t *) &m_can_registers[chan_num]->rCan_SyncTransmitBuffer_5;
    } else
    {
        /* Standard ID */
        CAN_11_BIT_ID_T id;

        id.all = ptr_sync_config->sync_msg.id;
        m_can_registers[chan_num]->rCan_SyncTransmitBuffer_1.BIT.bCan_SyncTransmitBuffer = (uint8_t)(id.bits_10_3);
        m_can_registers[chan_num]->rCan_SyncTransmitBuffer_2.BIT.bCan_SyncTransmitBuffer = (uint8_t)(id.bits_2_0);
        /* Configure for Standard Frame */
        frame_hdr = CAN_FF_STD;
        ptr_tx_buff_data = (uint32_t *) &m_can_registers[chan_num]->rCan_SyncTransmitBuffer_3;
    }

    /* Write in data length to frame header */
    frame_hdr += ptr_sync_config->sync_msg.data_len;

    if (ptr_sync_config->sync_msg.rtr_flag)
    {
        /* Transmit Remote Frame */
        frame_hdr |= CAN_RTR;
    }
    else
    {
        /* Transmit data frame */
        uint8_t i;
        /* Set data */
        for (i = 0; i < ptr_sync_config->sync_msg.data_len; i++)
        {
            ptr_tx_buff_data[i] = ptr_sync_config->sync_msg.data[i];
        }
    }

    /* Write header to CAN controller */
    m_can_registers[chan_num]->rCan_SyncTransmitBuffer_0.BIT.bCan_SyncTransmitBuffer = frame_hdr;
    /* Write special code to start sync pulse */
    m_can_registers[chan_num]->rCan_SyncClearSetRunStop.LONG = CAN_SYNC_START_MAGIC_NUMBER;
    m_can_config[chan_num].sync_msg = *ptr_sync_config;
    return ER_OK;
}
/***********************************************************************************************************************
 End of function can_sync_pulse_start
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           can_sync_pulse_stop
 *
 *  Return value:       Error status
 *
 *  Parameters:         chan_num - The CAN channel number
 *
 *  Description:        Stops Sync Pulse (CANopen) on CAN channel bus
 *
 **********************************************************************************************************************/
ER_RET can_sync_pulse_stop (uint8_t chan_num)
{
    CAN_DRIVER_CONFIG_CHECKS(chan_num);
    m_can_registers[chan_num]->rCan_SyncClearSetRunStop.LONG = CAN_SYNC_STOP_MAGIC_NUMBER;
    return ER_OK;
}
/***********************************************************************************************************************
 End of function can_sync_pulse_stop
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           can_set_test_mode
 *
 *  Return value:       Error status
 *
 *  Parameters:         chan_num - The CAN channel number
 *                      test_mode - Test mode to set
 *
 *  Description:        Sets test modes
 *
 **********************************************************************************************************************/
ER_RET can_set_test_mode (uint8_t chan_num, CAN_TEST_MODE_T test_mode)
{
    CAN_DRIVER_CONFIG_CHECKS(chan_num);

    if (CAN_TMODE_TX_NACK_OK & test_mode)
    {
        m_can_registers[chan_num]->rCan_MOD.BIT.bCan_STM = 1;
    }

    if (CAN_TMODE_TX_SINGLE_SHOT & test_mode)
    {
        m_is_tx_single_shot[chan_num] = true;
    }

    if (CAN_TMODE_MONITOR_ONLY & test_mode)
    {
        m_can_registers[chan_num]->rCan_MOD.BIT.bCan_LOM = 1;
    }

    if (CAN_TMODE_SELF_RX & test_mode)
    {
        m_is_self_rx[chan_num] = true;
    }

    if (CAN_TMODE_NONE == test_mode)
    {
        /* Turn off all test modes */
        m_can_registers[chan_num]->rCan_MOD.BIT.bCan_STM = 0;
        m_can_registers[chan_num]->rCan_MOD.BIT.bCan_LOM = 0;
        m_is_self_rx[chan_num] = false;
        m_is_tx_single_shot[chan_num] = false;
    }

    m_can_config[chan_num].test_mode = test_mode;
    return ER_OK;
}
/***********************************************************************************************************************
 End of function can_set_test_mode
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           can_get_stats
 *
 *  Return value:       Error status
 *
 *  Parameters:         chan_num - The CAN channel number
 *                      ptr_stats - buffer to place the channel stats in
 *
 *  Description:        Gets the communications stats of the channel
 *
 **********************************************************************************************************************/
ER_RET can_get_stats (uint8_t chan_num, CAN_STATS_T * ptr_stats)
{
    CAN_DRIVER_CONFIG_CHECKS(chan_num);

    /* Perform structure copy */
    *ptr_stats = m_can_stats[chan_num];
    return ER_OK;
}
/***********************************************************************************************************************
 End of function can_get_stats
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           can_reset_enter
 *
 *  Return value:       Error status
 *
 *  Parameters:         chan_num CAN channel Number
 *
 *  Description:        Enter the reset state
 *
 **********************************************************************************************************************/
ER_RET can_reset_enter (uint8_t chan_num)
{
    CAN_DRIVER_CONFIG_CHECKS(chan_num);

    m_can_registers[chan_num]->rCan_MOD.BIT.bCan_RM = 1;
    while (0 == m_can_registers[chan_num]->rCan_MOD.BIT.bCan_RM);
    return ER_OK;
}
/***********************************************************************************************************************
 End of function can_reset_enter
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           can_reset_exit
 *
 *  Return value:       Error status
 *
 *  Parameters:         chan_num CAN channel Number
 *
 *  Description:        Exit the reset state
 *
 **********************************************************************************************************************/
ER_RET can_reset_exit (uint8_t chan_num)
{
    CAN_DRIVER_CONFIG_CHECKS(chan_num);

    m_can_registers[chan_num]->rCan_MOD.BIT.bCan_RM = 0;
    return ER_OK;
}
/***********************************************************************************************************************
 End of function can_reset_exit
 **********************************************************************************************************************/
