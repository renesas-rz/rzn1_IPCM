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
 * FILE         :  r_i2c_rzn1.c
 * Description  :  I2C driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "platform.h"
#include "r_sysctrl_rzn1_if.h"
#include "r_i2c_rzn1_if.h"
#include "r_i2c_rzn1_config.h"
#include "iodefine.h"
#include "r_i2c_rzn1.h"
#include "timer.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define I2C_INVALID_CHANNEL                 (0xFF)

#define I2C_DEFAULT_STANDARD_SPEED_HCNT     (0x14e)
#define I2C_DEFAULT_STANDARD_SPEED_LCNT     (0x188)
#define I2C_DEFAULT_FAST_SPEED_HCNT         (0x32)
#define I2C_DEFAULT_FAST_SPEED_LCNT         (0x6d)

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

typedef struct
{
    uint8_t *next_byte_ptr;
    uint32_t required_bytes; /* total number bytes to send or receive */
    uint32_t remaining_bytes; /* remaining bytes to send or receive */
} I2C_BUFFER_PARAMS_T;

typedef struct
{
    uint32_t ready;
    volatile I2C_Type *base_address;
    uint32_t tx_outstanding;
    uint32_t rx_outstanding;
    i2c_transfer_complete_callback_t transfer_complete_callback;
} I2C_CHANNEL_PARAMS_T;

/***********************************************************************************************************************
 *  External function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local (private) variables
 **********************************************************************************************************************/

/* Note: only 1 channel supported in bare metal driver */
static I2C_CHANNEL_PARAMS_T i2c_channels_params[I2C_MAX_CHANNELS] =
{
{ 0 },
{ 0 } };

static I2C_CHANNEL_CONFIG_T i2c_channels_config[I2C_MAX_CHANNELS];

static I2C_BUFFER_PARAMS_T i2c_chan_transfer_buff_params[I2C_MAX_CHANNELS];

/***********************************************************************************************************************
 * Local (private) function declarations
 **********************************************************************************************************************/
static void handle_i2c_interrupt (IRQn_Type *irq_num_ptr);
static ER_RET disable_i2c_controller (uint8_t chan_num);
static ER_RET enable_i2c_controller (uint8_t chan_num);

/***********************************************************************************************************************
 *
 *  Function:       i2c_get_major_version_num
 *
 *  Return value:   I2C driver Major version number
 *
 *  Parameters:     None
 *
 *  Description:    Gets the I2C driver's Major version number
 *
 **********************************************************************************************************************/
uint8_t i2c_get_major_version_num (void)
{
    uint8_t major_ver_num = (uint8_t) I2C_DRIVER_MAJOR_VERSION_NUMBER;

    return major_ver_num;
}
/***********************************************************************************************************************
 End of function i2c_get_major_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_get_minor_version_num
 *
 *  Return value:   I2C driver Minor version number
 *
 *  Parameters:     None
 *
 *  Description:    Gets the I2C driver's Minor version number
 *
 **********************************************************************************************************************/
uint8_t i2c_get_minor_version_num (void)
{
    uint8_t minor_ver_num = (uint8_t) I2C_DRIVER_MINOR_VERSION_NUMBER;

    return minor_ver_num;
}
/***********************************************************************************************************************
 End of function i2c_get_minor_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_driver_init
 *
 *  Return value:   Error Status
 *
 *  Parameters:     void
 *
 *  Description:    Initialise I2C Channel info for all supported channels.
 *
 **********************************************************************************************************************/
ER_RET i2c_driver_init (void)
{
    ER_RET ret_val = ER_OK;
    uint32_t channel = 0;

    while (channel < I2C_MAX_CHANNELS)
    {
        i2c_channels_params[channel].tx_outstanding = 0;
        i2c_channels_params[channel].rx_outstanding = 0;
        i2c_channels_params[channel].transfer_complete_callback = (void *) 0;
        i2c_channels_params[channel].base_address = (void *) 0;

        ret_val = R_SYSCTRL_EnableI2C(channel);
        if (ER_OK != ret_val)
        {
            break;
        }
        channel++;
    }

    if (ER_OK == ret_val)
    {
        ret_val = R_SYSCTRL_SetI2CClkDivider(I2C_CLOCK_DIVIDER);
    }

    if (ER_OK == ret_val)
    {
        for (channel = 0; channel < I2C_MAX_CHANNELS; channel++)
        {
            i2c_channels_params[channel].ready = 1;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function i2c_driver_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_driver_uninitialise
 *
 *  Return value:   Error Status
 *
 *  Parameters:     void
 *
 *  Description:    Uninitialises I2C Channel info for all supported channels.
 *
 **********************************************************************************************************************/
ER_RET i2c_driver_uninitialise (void)
{
    ER_RET ret_val = ER_OK;
    uint32_t channel = 0;

    while (channel < I2C_MAX_CHANNELS)
    {
        i2c_channels_params[channel].tx_outstanding = 0;
        i2c_channels_params[channel].rx_outstanding = 0;
        i2c_channels_params[channel].transfer_complete_callback = (void *) 0;
        i2c_channels_params[channel].base_address = (void *) 0;

        ret_val = R_SYSCTRL_DisableI2C(channel);
        if (ER_OK != ret_val)
        {
            break;
        }
        channel++;
    }

    if (ER_OK == ret_val)
    {
        for (channel = 0; channel < I2C_MAX_CHANNELS; channel++)
        {
            i2c_channels_params[channel].ready = 0;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function i2c_driver_uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_channel_open
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number
 *
 *  Description:    Opens a I2C channel
 *
 **********************************************************************************************************************/
ER_RET i2c_channel_open (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num;
    uint32_t int_priority;
    volatile I2C_Type *channel_base_address;
    /*uint32_t speed;*/

    if (chan_num >= I2C_MAX_CHANNELS)
    {
        ret_val = ER_PARAM;
    }
    else if ( !i2c_channels_params[chan_num].ready)
    {
        ret_val = ((ER_RET) -2);
    }
    else
    {
        ;
    }

    if (ER_OK == ret_val)
    {
        /* parameters are OK */
        channel_base_address = (volatile I2C_Type *) (RZN1_I2C1_BASE + (chan_num * I2C_CHAN_BASE_ADDR_INCREMENT));
        i2c_channels_params[chan_num].base_address = channel_base_address;

        /* set default configuration for I2C Channel 'chan_num' */
        i2c_channels_config[chan_num].master = true;
        i2c_channels_config[chan_num].restart_enable = true;
        i2c_channels_config[chan_num].addr_mode = 0; /* 7-bit addressing */
        i2c_channels_config[chan_num].speed = 1; /* standard mode */

        /* Disable the I2C IP before configuring the channel */
        ret_val = disable_i2c_controller(chan_num);
        if (ER_OK == ret_val)
        {
            /* Set master speed */
            channel_base_address->IC_CON.BIT.SPEED = i2c_channels_config[chan_num].speed;

            channel_base_address->IC_SS_SCL_HCNT.LONG = I2C_DEFAULT_STANDARD_SPEED_HCNT;
            channel_base_address->IC_SS_SCL_LCNT.LONG = I2C_DEFAULT_STANDARD_SPEED_LCNT;
            channel_base_address->IC_FS_SCL_HCNT.LONG = I2C_DEFAULT_FAST_SPEED_HCNT;
            channel_base_address->IC_FS_SCL_LCNT.LONG  = I2C_DEFAULT_FAST_SPEED_LCNT;

            /* Enable I2C subsystem and set to master */
            channel_base_address->IC_CON.BIT.IC_SLAVE_DISABLE = 1;
            channel_base_address->IC_CON.BIT.IC_RESTART_EN = i2c_channels_config[chan_num].restart_enable;

            /* Devices use 7-bit addressing */
            /*channel_base_address->IC_CON.BIT.IC_10BITADDR_MASTER_rd_only = 0;*/
            channel_base_address->IC_CON.BIT.IC_10BITADDR_SLAVE = 0;

            /* Mask all I2C interrupts */
            channel_base_address->IC_INTR_MASK.LONG = 0;

            channel_base_address->IC_CON.BIT.MASTER_MODE = 1;

            /* Re-enable the I2C IP  */
            ret_val = enable_i2c_controller(chan_num);
            if (ER_OK == ret_val)
            {
                /* Set interrupt priority for I2C channel & enable system interrupt */
                irq_num = RZN1_IRQ_I2C0 + chan_num;

                if (R_BSP_InterruptRegisterCallback((IRQn_Type) irq_num, (bsp_int_cb_t) &handle_i2c_interrupt)
                        == MCU_INT_SUCCESS)
                {
                    int_priority = I2C_DEFAULT_INT_PRIORITY;
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
            }
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function i2c_channel_open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_channel_close
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number
 *
 *  Description:    Closes a I2C channel
 *
 **********************************************************************************************************************/
ER_RET i2c_channel_close (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    uint8_t irq_num;

    if (chan_num < I2C_MAX_CHANNELS)
    {
        /* Parameters are ok */
        if ((void*) 0 == i2c_channels_params[chan_num].base_address)
        {
            ret_val = ER_INVAL;
        }
        else
        {
            /* Disable I2C system interrupt for this I2C channel */
            irq_num = (uint8_t) RZN1_IRQ_I2C0 + chan_num;
            ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);

            /* Disable the I2C IP  */
            ret_val = disable_i2c_controller(chan_num);

            i2c_channels_params[chan_num].tx_outstanding = 0;
            i2c_channels_params[chan_num].rx_outstanding = 0;
            i2c_channels_params[chan_num].transfer_complete_callback = (void *) 0;
            i2c_channels_params[chan_num].base_address = (void *) 0;
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function i2c_channel_close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_set_chan_config
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number
 *                  channel_config - parity, flow_control, stopbits, databits, baudrate
 *
 *  Description:    Sets I2C channel configuration
 *
 **********************************************************************************************************************/
ER_RET i2c_set_chan_config (uint8_t chan_num, I2C_CHANNEL_CONFIG_T *channel_config)
{
    ER_RET ret_val = ER_OK;
    volatile I2C_Type *channel_base_address;
   /*uint32_t speed;*/

    if ((chan_num < I2C_MAX_CHANNELS) && ((void*) 0 != channel_config))
    {
        if ((void*) 0 == i2c_channels_params[chan_num].base_address)
        {
            ret_val = ER_INVAL;
        }
        else
        {
            channel_base_address = i2c_channels_params[chan_num].base_address;

            /* Save new configuration for I2C Channel 'chan_num' */
            i2c_channels_config[chan_num].master = channel_config->master;
            i2c_channels_config[chan_num].restart_enable = channel_config->restart_enable;
            i2c_channels_config[chan_num].addr_mode = channel_config->addr_mode;
            i2c_channels_config[chan_num].speed = channel_config->speed;

            /* Set the new configuration for the channel */
            /* Disable the I2C IP before configuring the channel */
            ret_val = disable_i2c_controller(chan_num);
            if (ER_OK == ret_val)
            {
                channel_base_address->IC_CON.BIT.SPEED = channel_config->speed;
                channel_base_address->IC_SS_SCL_HCNT.LONG = I2C_DEFAULT_STANDARD_SPEED_HCNT;
                channel_base_address->IC_SS_SCL_LCNT.LONG = I2C_DEFAULT_STANDARD_SPEED_LCNT;
                channel_base_address->IC_FS_SCL_HCNT.LONG = I2C_DEFAULT_FAST_SPEED_HCNT;
                channel_base_address->IC_FS_SCL_LCNT.LONG  = I2C_DEFAULT_FAST_SPEED_LCNT;

                /* Devices use 7-bit addressing */
                /*channel_base_address->IC_CON.BIT.IC_10BITADDR_MASTER_rd_only = 0;*/
                channel_base_address->IC_CON.BIT.IC_10BITADDR_SLAVE = 0;
                channel_base_address->IC_CON.BIT.IC_RESTART_EN = i2c_channels_config[chan_num].restart_enable;

                /* Set remaining config bits then Enable I2C channel */
                channel_base_address->IC_CON.BIT.IC_SLAVE_DISABLE = i2c_channels_config[chan_num].master;
                channel_base_address->IC_CON.BIT.MASTER_MODE = i2c_channels_config[chan_num].master;

                ret_val = enable_i2c_controller(chan_num);
            }
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }
    return ret_val;

}
/***********************************************************************************************************************
 End of function i2c_set_chan_config
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_get_chan_config
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number
 *                  channel_config - where to store config:
 *                       parity, flow_control, stopbits, databits, baudrate
 *
 *  Description:    Gets I2C channel configuration
 *
 **********************************************************************************************************************/
ER_RET i2c_get_chan_config (uint8_t chan_num, I2C_CHANNEL_CONFIG_T *channel_config)
{
    ER_RET ret_val = ER_OK;

    if ((chan_num < I2C_MAX_CHANNELS) && ((void*) 0 != channel_config))
    {
        if ((void*) 0 == i2c_channels_params[chan_num].base_address)
        {
            ret_val = ER_INVAL;
        }
        else
        {
            /* Get configuration for I2C Channel 'chan_num' */
            channel_config->master = i2c_channels_config[chan_num].master;
            channel_config->restart_enable = i2c_channels_config[chan_num].restart_enable;
            channel_config->addr_mode = i2c_channels_config[chan_num].addr_mode;
            channel_config->speed = i2c_channels_config[chan_num].speed;
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function i2c_get_chan_config
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       reset
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number
 *
 *  Description:    Resets a I2C channel
 *
 **********************************************************************************************************************/
ER_RET i2c_reset (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

    if (chan_num < I2C_MAX_CHANNELS)
    {
        if ((void*) 0 == i2c_channels_params[chan_num].base_address)
        {
            ret_val = ER_INVAL;
        }
        else
        {
            /* Reset */
            ;
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function i2c_reset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_set_transfer_completed_callback
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number
 *                  transfer_complete_callback - pointer to function to call when I2C transfer completes.
 *                                               Required for Async transfer
 *
 *  Description:    Saves the I2C callback function for a channel
 *
 **********************************************************************************************************************/
ER_RET i2c_set_trans_completedcallback (uint8_t chan_num, i2c_transfer_complete_callback_t transfer_complete_callback)
{
    ER_RET ret_val = ER_OK;

    if ((chan_num < I2C_MAX_CHANNELS) && ((void*) 0 != transfer_complete_callback))
    {
        /* Parameters are ok */
        if ((void*) 0 != i2c_channels_params[chan_num].base_address)
        {
            /* I2C channel is initialised */
            i2c_channels_params[chan_num].transfer_complete_callback = transfer_complete_callback;
        }
        else
        {
            ret_val = ER_INVAL; /* I2C channel not initialised */
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function i2c_set_trans_completedcallback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_sync_write
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number
 *                  i2c_slave_addr - address of slave device
 *                  addr - address internal to the device
 *                  addr_len - number bytes in addr
 *                  buf  - data to be written
 *                  data_len - number of bytes to write
 *
 *  Description:    Writes a buffer of data to a I2C channel & waits for completion.
 *
 **********************************************************************************************************************/
ER_RET i2c_sync_write (uint8_t chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len)
{
    ER_RET ret_val = ER_OK;
    volatile I2C_Type *channel_base_address;
    uint32_t i;
    uint32_t command;
    uint32_t timeout_count;
    volatile uint8_t flush_buf;

    if ((chan_num < I2C_MAX_CHANNELS) && ((void*) 0 != buf) && (0 != data_len))
    {
        /* Parameters are ok */
        if ((void*) 0 != i2c_channels_params[chan_num].base_address)
        {
            /* I2C channel is initialised */
            channel_base_address = i2c_channels_params[chan_num].base_address;

            /*  WRITE */

            /* Wait while busy */
            for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
            {
                if ((0 == channel_base_address->IC_STATUS.BIT.IC_STATUS_ACTIVITY)
                        && (1 == channel_base_address->IC_STATUS.BIT.TFE))
                {
                    break;
                }
            }
            if (0 == timeout_count)
            {
                ret_val = ER_SYS;
            }
            else
            {
                /* Set target address */

                /* Disable the I2C IP first */
                ret_val = disable_i2c_controller(chan_num);
                if (ER_OK == ret_val)
                {
                    channel_base_address->IC_TAR.BIT.IC_TAR = i2c_slave_addr & I2C_ADDR_MASK;
                    channel_base_address->IC_TAR.BIT.IC_10BITADDR_MASTER = 0;
                    channel_base_address->IC_ENABLE.BIT.ENABLE = 1;
                    ret_val = enable_i2c_controller(chan_num);
                    if (ER_OK == ret_val)
                    {
                        /* Issue write commands with requested address to write to */

                        for (i = 0; (i < addr_len) && (ER_OK == ret_val); i++)
                        {
                            /* wait until a free TX buffer is available */
                            for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                            {
                                if (1 == channel_base_address->IC_STATUS.BIT.TFNF)
                                {
                                    break;
                                }
                            }
                            if (0 == timeout_count)
                            {
                                ret_val = ER_SYS;
                            }
                            else
                            {
                                channel_base_address->IC_DATA_CMD.LONG =
                                I2C_CMD_WRITE | addr[i];

                            }
                        }
                    }
                }
                if (ER_OK == ret_val)
                {
                    /* Write the data bytes */
                    for (i = 0; i < data_len; i++)
                    {
                        command = I2C_CMD_WRITE;
                        if ((data_len - 1) == i)
                        {
                            command |= I2C_CMD_STOP;
                        }
                        command |= (uint32_t) buf[i];

                        /* wait until a free TX buffer is available */
                        for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                        {
                            if (1 == channel_base_address->IC_STATUS.BIT.TFNF)
                            {
                                break;
                            }
                        }
                        if (0 == timeout_count)
                        {
                            ret_val = ER_SYS;
                            break;
                        }

                        /* Issue write command */
                        channel_base_address->IC_DATA_CMD.LONG = command;

                        /* Wait for transmit FIFO to be empty */
                        for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                        {
                            if (1 == channel_base_address->IC_STATUS.BIT.TFE)
                            {
                                break; // @suppress("Break statement")
                            }
                        }
                        if (0 == timeout_count)
                        {
                            ret_val = ER_SYS;
                            break;
                        }
                    }
                    if (ER_OK == ret_val)
                    {
                        /* all data written */
#if 0                         // @suppress("Disabled code")

                        /* wait for Stop detected */
                        for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                        {
                            if (1 == channel_base_address->IC_RAW_INTR_STAT.BIT.STOP_DET)
                            {
                                i = channel_base_address->IC_CLR_STOP_DET.BIT.CLR_STOP_DET; /* read bit to clear stop detect */
                                break;
                            }
                        }
                        if (timeout_count== 0)
                        {
                            ret_val = ER_SYS;
                        }
                        else
                        {
#endif
                        /* Wait while busy */
                        for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                        {
                            if ((0 == channel_base_address->IC_STATUS.BIT.IC_STATUS_ACTIVITY)
                                    && (1 == channel_base_address->IC_STATUS.BIT.TFE))
                            {
                                break;
                            }
                        }
                        if (0 == timeout_count)
                        {
                            ret_val = ER_SYS;
                        }
                        else
                        {
                            /* Flush Rx FIFO */
                            for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                            {
                                if (1 == channel_base_address->IC_STATUS.BIT.RFNE)
                                {
                                    flush_buf = (char) (channel_base_address->IC_DATA_CMD.BIT.DAT);
                                }
                                else
                                {
                                    break;
                                }
                            }
                            if (0 == timeout_count)
                            {
                                ret_val = ER_SYS;
                            }
                        }
#if 0                             // @suppress("Disabled code")
                    }
#endif
                    }
                }
            }
        }
        else
        {
            ret_val = ER_INVAL; /* I2C channel not initialised */
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function i2c_sync_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_sync_read
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number
 *                  i2c_slave_addr - address of slave device
 *                  addr - address internal to the device
 *                  addr_len - number bytes in addr
 *                  buf  - where data to be read should be stored
 *                  data_len - number of bytes to read
 *
 *  Description:    Reads data from a I2C channel & waits for completion.
 *
 **********************************************************************************************************************/
ER_RET i2c_sync_read (uint8_t chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len)
{
    ER_RET ret_val = ER_OK;
    volatile I2C_Type *channel_base_address;
    uint32_t i;
    uint32_t command;
    uint32_t timeout_count;
    volatile uint8_t flush_buf;

    if ((chan_num < I2C_MAX_CHANNELS) && ((void*) 0 != buf) && (0 != data_len))
    {
        /* Parameters are ok */
        if ((void*) 0 != i2c_channels_params[chan_num].base_address)
        {
            /* I2C channel is initialised */
            channel_base_address = i2c_channels_params[chan_num].base_address;

            /*  READ */

            /* Wait while busy */
            for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
            {
                if ((0 == channel_base_address->IC_STATUS.BIT.IC_STATUS_ACTIVITY)
                        && (1 == channel_base_address->IC_STATUS.BIT.TFE))
                {
                    break;
                }
            }
            if (0 == timeout_count)
            {
                ret_val = ER_SYS;
            }
            else
            {
                /* disable I2C controller */
                ret_val = disable_i2c_controller(chan_num);
                if (ER_OK == ret_val)
                {
                    /* Set target address */
                    channel_base_address->IC_TAR.BIT.IC_TAR = i2c_slave_addr & I2C_ADDR_MASK;
                    channel_base_address->IC_TAR.BIT.IC_10BITADDR_MASTER = 0;

                    ret_val = enable_i2c_controller(chan_num);
                    if (ER_OK == ret_val)
                    {
                        /* Issue write commands with requested address to read from */
                        for (i = 0; (i < addr_len) && (ER_OK == ret_val); i++)
                        {
                            channel_base_address->IC_DATA_CMD.LONG =
                            I2C_CMD_WRITE | (addr[i] & I2C_DATA_MASK);
#if 0                         // @suppress("Disabled code")
                            /* Wait for transmit FIFO to be empty */
                            for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                            {
                                if (1 == channel_base_address->IC_STATUS.BIT.TFE)
                                {
                                    break;
                                }
                            }
                            if (timeout_count == 0)
                            {
                                ret_val = ER_SYS;
                            }
#endif
                        }
                    }
                }
                if (ER_OK == ret_val)
                {
                    /* Read data */

                    for (i = 0; i < data_len; i++)
                    {
                        command = I2C_CMD_READ;
                        if ((data_len - 1) == i)
                        {
                            command |= I2C_CMD_STOP;
                        }

                        /* Issue read command */
                        channel_base_address->IC_DATA_CMD.LONG = command;

                        /* wait until data received */
                        for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                        {
                            if (1 == channel_base_address->IC_STATUS.BIT.RFNE)
                            {
                                break;
                            }
                        }
                        if (0 == timeout_count)
                        {
                            ret_val = ER_SYS;
                            break;
                        }

                        /* Read value */
                        flush_buf = (char) (channel_base_address->IC_DATA_CMD.BIT.DAT);
                        buf[i] = flush_buf;
                    }
                    if (ER_OK == ret_val)
                    {
                        /* all data received */
#if 0                         // @suppress("Disabled code")
                        /* wait for Stop detected */
                        for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                        {
                            if (1 == channel_base_address->IC_RAW_INTR_STAT.BIT.STOP_DET)
                            {
                                i = channel_base_address->IC_CLR_STOP_DET.BIT.CLR_STOP_DET; /* read bit to clear stop detect */
                                break;
                            }
                        }
                        if (timeout_count== 0)
                        {
                            ret_val = ER_SYS;
                        }
                        else
                        {
#endif
                        /* Wait while busy */
                        for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                        {
                            if ((0 == channel_base_address->IC_STATUS.BIT.IC_STATUS_ACTIVITY)
                                    && (1 == channel_base_address->IC_STATUS.BIT.TFE))
                            {
                                break;
                            }
                        }
                        if (0 == timeout_count)
                        {
                            ret_val = ER_SYS;
                        }
                        else
                        {
                            /* Flush Rx FIFO */
                            for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                            {
                                if (1 == channel_base_address->IC_STATUS.BIT.RFNE)
                                {
                                    flush_buf = (char) (channel_base_address->IC_DATA_CMD.BIT.DAT);
                                }
                                else
                                {
                                    break;
                                }
                            }
                            if (0 == timeout_count)
                            {
                                ret_val = ER_SYS;
                            }
                        }

#if 0                             // @suppress("Disabled code")
                    }
#endif
                    }
                }

            }
        }
        else
        {
            ret_val = ER_INVAL; /* I2C channel not initialised */
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function i2c_sync_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_async_read
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number
 *                  i2c_slave_addr - address of slave device
 *                  addr - address internal to the device
 *                  addr_len - number bytes in addr
 *                  buf  - where data to be read should be stored
 *                  data_len - number of bytes to read
 *
 *  Description:    Initiates data read from a I2C channel.
 *                  Does not wait for completion unless no callback has been set
 *
 **********************************************************************************************************************/
ER_RET i2c_async_read (uint8_t chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len)
{
    ER_RET ret_val = ER_OK;
    volatile I2C_Type *channel_base_address;
    uint32_t i;
    uint32_t command;
    uint32_t timeout_count;
    volatile uint8_t flush_buf;

    if ((chan_num < I2C_MAX_CHANNELS) && ((void*) 0 != buf) && (0 != data_len))
    {
        /* Parameters are ok */
        if ((void*) 0 != i2c_channels_params[chan_num].base_address)
        {
            if (1 == data_len)
            {
                /* Not worthwhile setting up a blocking read to read 1 byte */
                ret_val = i2c_sync_read(chan_num, i2c_slave_addr, addr, addr_len, buf, data_len);
            }
            else
            {
                /* I2C channel is initialised */
                channel_base_address = i2c_channels_params[chan_num].base_address;

                /* transfer complete callback should already be set for async transfer */
                if ((void*) 0 != (i2c_channels_params[chan_num].transfer_complete_callback))
                {
                    /* Initialise buffer handling parameters */
                    i2c_channels_params[chan_num].rx_outstanding = 1;
                    i2c_chan_transfer_buff_params[chan_num].next_byte_ptr = (uint8_t *) buf;
                    i2c_chan_transfer_buff_params[chan_num].remaining_bytes = data_len;
                    i2c_chan_transfer_buff_params[chan_num].required_bytes = data_len;

                    /* Setup the Slave Target address */

                    /* Wait while I2C controller busy */
                    for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                    {
                        if ((0 == channel_base_address->IC_STATUS.BIT.IC_STATUS_ACTIVITY)
                                && (1 == channel_base_address->IC_STATUS.BIT.TFE))
                        {
                            break;
                        }
                    }
                    if (0 == timeout_count)
                    {
                        ret_val = ER_SYS;
                    }
                    else
                    {
                        /* disable I2C controller */
                        ret_val = disable_i2c_controller(chan_num);
                        if (ER_OK == ret_val)
                        {
                            /* Set target address */
                            channel_base_address->IC_TAR.BIT.IC_TAR = i2c_slave_addr & I2C_ADDR_MASK;
                            channel_base_address->IC_TAR.BIT.IC_10BITADDR_MASTER = 0;

                            /* Un-mask RX_FULL interrupt */
                            channel_base_address->IC_INTR_MASK.BIT.M_RX_FULL = 1;

                            /* Rx FIFO trigger level */
                            channel_base_address->IC_RX_TL.BIT.RX_TL = 0; /* 0:generate interrupt when 1 character or more received into FIFO  */

                            /* Enable Rx interrupt */

                            /* Re-enable I2C controller */
                            ret_val = enable_i2c_controller(chan_num);
                            if (ER_OK == ret_val)
                            {
                                /* Issue write commands with requested address to read from */
                                for (i = 0; (i < addr_len) && (ER_OK == ret_val); i++)
                                {
                                    channel_base_address->IC_DATA_CMD.LONG =
                                    I2C_CMD_WRITE | (addr[i] & I2C_DATA_MASK);
#if 0                         // @suppress("Disabled code")
                                    /* Wait for transmit FIFO to be empty */
                                    for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                                    {
                                        if (1 == channel_base_address->IC_STATUS.BIT.TFE)
                                        {
                                            break;
                                        }
                                    }
                                    if (timeout_count == 0)
                                    {
                                        ret_val = ER_SYS;
                                    }
#endif
                                }
                            }
                        }

                        /* Initiate read */
                        command = I2C_CMD_READ;

                        /* Issue read cmd */
                        channel_base_address->IC_DATA_CMD.LONG = command;
                    }
                }
                else
                {
                    ret_val = ER_INVAL; /* callback not set */
                }
            } /* if (data_len == 1) */
        }
        else
        {
            ret_val = ER_INVAL; /* I2C channel not initialised */
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function i2c_async_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       i2c_async_write
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - I2C channel number
 *                  i2c_slave_addr - address of slave device
 *                  addr - address internal to the device
 *                  addr_len - number bytes in addr
 *                  buf  - data to write
 *                  data_len - number of bytes to write
 *
 *  Description:    Initiates data write to a I2C channel.
 *                  Does not wait for completion unless no callback has been set
 *
 **********************************************************************************************************************/
ER_RET i2c_async_write (uint8_t chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len)
{
    ER_RET ret_val = ER_OK;
    volatile I2C_Type *channel_base_address;
    uint32_t i;
    uint32_t timeout_count;
    volatile uint8_t flush_buf;

    if ((chan_num < I2C_MAX_CHANNELS) && ((void*) 0 != buf) && (0 != data_len))
    {
        /* Parameters are ok */
        if ((void*) 0 != i2c_channels_params[chan_num].base_address)
        {
            if (1 == data_len)
            {
                /* Not worthwhile setting up a blocking write to write 1 byte */
                ret_val = i2c_sync_write(chan_num, i2c_slave_addr, addr, addr_len, buf, data_len);
            }
            else
            {
                /* I2C channel is initialised */
                channel_base_address = i2c_channels_params[chan_num].base_address;

                /* transfer complete callback should already be set for async transfer */
                if ((void*) 0 != (i2c_channels_params[chan_num].transfer_complete_callback))
                {
                    /* Initialise buffer handling parameters */
                    i2c_channels_params[chan_num].tx_outstanding = 1;
                    i2c_chan_transfer_buff_params[chan_num].next_byte_ptr = (uint8_t *) buf;
                    i2c_chan_transfer_buff_params[chan_num].remaining_bytes = data_len;
                    i2c_chan_transfer_buff_params[chan_num].required_bytes = data_len;

                    /* Setup the Slave Target address */

                    /* Wait while I2C controller busy */
                    for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
                    {
                        if ((0 == channel_base_address->IC_STATUS.BIT.IC_STATUS_ACTIVITY)
                                && (1 == channel_base_address->IC_STATUS.BIT.TFE))
                        {
                            break;
                        }
                    }
                    if (0 == timeout_count)
                    {
                        ret_val = ER_SYS;
                    }
                    else
                    {
                        /* disable I2C controller */
                        ret_val = enable_i2c_controller(chan_num);
                        if (ER_OK == ret_val)
                        {
                            /* Issue write commands with requested address to write to */
                            for (i = 0; (i < addr_len) && (ER_OK == ret_val); i++)
                            {
                                channel_base_address->IC_DATA_CMD.LONG =
                                I2C_CMD_WRITE | (addr[i] & I2C_DATA_MASK);
                            }

                            if (ER_OK == ret_val)
                            {
                                /* Set target address */
                                channel_base_address->IC_TAR.BIT.IC_TAR = i2c_slave_addr & I2C_ADDR_MASK;
                                channel_base_address->IC_TAR.BIT.IC_10BITADDR_MASTER = 0;

                                /* Un-mask TX_FULL interrupt */
                                channel_base_address->IC_INTR_MASK.BIT.M_STOP_DET = 1;
                                channel_base_address->IC_INTR_MASK.BIT.M_TX_EMPTY = 1;

                                /* Tx FIFO trigger level */
                                channel_base_address->IC_TX_TL.BIT.TX_TL = 0; /* 0:generate interrupt when 1 character or more received into FIFO  */

                                /* Enable Tx interrupt */
                            }
                        }

                    } /* Controller is busy */
                }
                else
                {
                    ret_val = ER_INVAL; /* callback not set */
                }
            } /* if (data_len == 1) */
        }
        else
        {
            ret_val = ER_INVAL; /* I2C channel not initialised */
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function i2c_async_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       enable_i2c_controller
 *
 *  Return value:   Error status
 *
 *  Parameters:     void
 *
 *  Description:    Enables the IP & waits for 'enabled' status
 *
 **********************************************************************************************************************/
static ER_RET enable_i2c_controller (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    volatile I2C_Type *channel_base_address;
    uint32_t timeout_count;

    channel_base_address = i2c_channels_params[chan_num].base_address;

    /* enable I2C controller */
    for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
    {
        channel_base_address->IC_ENABLE.BIT.ENABLE = 1;

        if (1 == channel_base_address->IC_ENABLE_STATUS.BIT.IC_EN)
        {
            break;
        }
        systimer_delay(25);
    }
    if (0 == timeout_count)
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function enable_i2c_controller
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       disable_i2c_controller
 *
 *  Return value:   Error status
 *
 *  Parameters:     I2C channel
 *
 *  Description:    Disables the controller & waits for Disabled status
 *
 **********************************************************************************************************************/
static ER_RET disable_i2c_controller (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    volatile I2C_Type *channel_base_address;
    uint32_t timeout_count;

    channel_base_address = i2c_channels_params[chan_num].base_address;

    /* disable I2C controller */
    for (timeout_count = I2C_WAIT_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
    {
        channel_base_address->IC_ENABLE.BIT.ENABLE = 0;

        if (0 == channel_base_address->IC_ENABLE_STATUS.BIT.IC_EN)
        {
            break;
        }
        systimer_delay(25);
    }
    if (0 == timeout_count)
    {
        ret_val = ER_SYS;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function disable_i2c_controller
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       handle_i2c_interrupt
 *
 *  Return value:   none
 *
 *  Parameters:     uint8_t chan_num
 *
 *  Description:    handle I2C Interrupt for 'chan_num'
 *
 **********************************************************************************************************************/
static void handle_i2c_interrupt (IRQn_Type *irq_num_ptr)
{
    volatile I2C_Type *channel_base_address = 0;
    volatile int32_t int_status;
    uint32_t actual_total_bytes;

    uint32_t command;
    volatile uint8_t flush_buf;
    volatile uint8_t clr_int;

    IRQn_Type irq_num = *irq_num_ptr;
    uint32_t chan_num = I2C_INVALID_CHANNEL;

    if ((irq_num == RZN1_IRQ_I2C0) || (irq_num == RZN1_IRQ_I2C1))
    {
        chan_num = irq_num - RZN1_IRQ_I2C0;
        channel_base_address = i2c_channels_params[chan_num].base_address;
    }

    if (0 != channel_base_address)
    {
        /* Check for RX_FULL interrupt */
        int_status = (channel_base_address->IC_INTR_STAT.BIT.R_RX_FULL);
        if (int_status)
        {
            if (1 == i2c_channels_params[chan_num].rx_outstanding)
            {
                /* Continue reading data from Rx FIFO if more is expected */
                while ((channel_base_address->IC_RXFLR.BIT.RXFLR > 0)
                        && (i2c_chan_transfer_buff_params[chan_num].remaining_bytes > 0))
                {
                    /* Read value */
                    flush_buf = (char) (channel_base_address->IC_DATA_CMD.BIT.DAT);
                    *(i2c_chan_transfer_buff_params[chan_num].next_byte_ptr) = flush_buf;

                    i2c_chan_transfer_buff_params[chan_num].next_byte_ptr++;
                    i2c_chan_transfer_buff_params[chan_num].remaining_bytes--;

                    if (0 == i2c_chan_transfer_buff_params[chan_num].remaining_bytes)
                    {
                        /* All required data has been received. Disable Rx interrupt */
                        /* Mask RX_FULL interrupt */
                        channel_base_address->IC_INTR_MASK.BIT.M_RX_FULL = 0;

                        /* Un-mask Stop Detect interrupt and wait for Stop Detect before completing transaction. */
                        channel_base_address->IC_INTR_MASK.BIT.M_STOP_DET = 1;
                    }
                }
                if (i2c_chan_transfer_buff_params[chan_num].remaining_bytes > 0)
                {
                    /* More data to read but not yet received into FIFO */
                    command = I2C_CMD_READ;
                    if (1 == i2c_chan_transfer_buff_params[chan_num].remaining_bytes)
                    {
                        command |= I2C_CMD_STOP;
                    }

                    /* Issue read cmd */
                    channel_base_address->IC_DATA_CMD.LONG = command;
                }
            }
        }

        /* Check for TX_EMPTY interrupt */
        int_status = (channel_base_address->IC_INTR_STAT.BIT.R_TX_EMPTY);
        if (int_status)
        {
            if (1 == i2c_channels_params[chan_num].tx_outstanding)
            {
                if (0 == i2c_chan_transfer_buff_params[chan_num].remaining_bytes)
                {
                    /* All required data has now been been written. Disable Tx interrupt */
                    /* Mask TX_EMPTY interrupt */
                    channel_base_address->IC_INTR_MASK.BIT.M_TX_EMPTY = 0;

                    /* Un-mask Stop Detect interrupt and wait for Stop Detect before completing transaction. */
                    channel_base_address->IC_INTR_MASK.BIT.M_STOP_DET = 1;
                }

                /* Continue writing data to Tx FIFO if more to write */
                while ((0 == channel_base_address->IC_TXFLR.BIT.TXFLR)
                        && (i2c_chan_transfer_buff_params[chan_num].remaining_bytes > 0))
                {
                    /* Write next value */
                    command = I2C_CMD_WRITE;
                    command |= (uint32_t)( *(i2c_chan_transfer_buff_params[chan_num].next_byte_ptr));
                    if (1 == i2c_chan_transfer_buff_params[chan_num].remaining_bytes)
                    {
                        command |= I2C_CMD_STOP;
                    }

                    i2c_chan_transfer_buff_params[chan_num].next_byte_ptr++;
                    i2c_chan_transfer_buff_params[chan_num].remaining_bytes--;

                    /* Issue write command */
                    channel_base_address->IC_DATA_CMD.LONG = command;
                }
            }
            else
            {
                channel_base_address->IC_INTR_MASK.BIT.M_TX_EMPTY = 0;
            }

        }

        /* Check for STOP_Detect interrupt */
        int_status = (channel_base_address->IC_INTR_STAT.BIT.R_STOP_DET);
        if (int_status)
        {
            /* Mask Stop detect interrupt */
            channel_base_address->IC_INTR_MASK.BIT.M_STOP_DET = 0;

            if (((1 == i2c_channels_params[chan_num].rx_outstanding)
                    || (1 == i2c_channels_params[chan_num].tx_outstanding))
                    && (0 == i2c_chan_transfer_buff_params[chan_num].remaining_bytes))
            {
                actual_total_bytes = i2c_chan_transfer_buff_params[chan_num].required_bytes;

                /* inform I2C driver interface that I2C channel is no longer busy */
                i2c_transfer_completed(chan_num);

                /* inform application that transfer has completed */
                (i2c_channels_params[chan_num].transfer_complete_callback)(chan_num, actual_total_bytes);

                /* All required data to be read/written has been received/sent & Stop has been detected */
                if (i2c_channels_params[chan_num].rx_outstanding)
                {
                    i2c_channels_params[chan_num].rx_outstanding = 0;
                }
                if (i2c_channels_params[chan_num].tx_outstanding)
                {
                    i2c_channels_params[chan_num].tx_outstanding = 0;
                }
                i2c_chan_transfer_buff_params[chan_num].next_byte_ptr = (uint8_t *) 0;
                i2c_chan_transfer_buff_params[chan_num].required_bytes = 0;

            }
        }

        clr_int = channel_base_address->IC_CLR_INTR.BIT.CLR_INTR; /* read bit to clear interrupts */
    }
}
/***********************************************************************************************************************
 End of function handle_i2c_interrupt
 **********************************************************************************************************************/