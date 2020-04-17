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
 * $Revision: 1195 $
 * $Date: 2019-01-29 12:51:05 +0000 (Tue, 29 Jan 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_qspi_rzn1.c
 * Description  :  QSPI driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "platform.h"
#include "r_qspi_rzn1_config.h"
#include "r_sysctrl_rzn1_if.h"
#include "iodefine.h"
#include "r_qspi_rzn1.h"
#include "r_timer_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define QSPI_CMD_EXECUTE_TIMEOUT_COUNT      (1000)
#define QSPI_WAIT_FOR_IDLE_TIMEOUT_COUNT    (5000)

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

typedef struct
{
    volatile QSPI_Type *base_address; /* base address of QSPI IP register set */
    uint32_t qspi_ahb_base_addr;
    uint32_t qspi_ahb_base_size;
    uint32_t page_size;
} QSPI_CHANNEL_PARAMS_T;

/***********************************************************************************************************************
 *  External function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local (private) variables
 **********************************************************************************************************************/

static QSPI_CHANNEL_PARAMS_T qspi_channels_params[MAX_QSPI_CHANNELS];

/***********************************************************************************************************************
 * Local (private) function declarations
 **********************************************************************************************************************/
static void qspi_controller_enable (uint8_t chan_num);
static void qspi_controller_disable (uint8_t chan_num);

static void qspi_chipselect (uint8_t chan_num, uint32_t chip_select);
static ER_RET qspi_execute_command (uint8_t chan_num, uint8_t *cmd_buf, uint32_t cmd_len, uint8_t *data_buf,
        uint32_t data_len);
static ER_RET qspi_wait_idle (uint8_t chan_num);
static ER_RET qspi_wait_ready (uint8_t chan_num, uint64_t timeout);

/***********************************************************************************************************************
 *
 *  Function:       qspi_get_major_version_num
 *
 *  Return value:   QSPI driver Major version number
 *
 *  Parameters:     None
 *
 *  Description:    Gets the QSPI driver's Major version number
 *
 **********************************************************************************************************************/
uint8_t qspi_get_major_version_num (void)
{
    uint8_t major_ver_num = (uint8_t) QSPI_DRIVER_MAJOR_VERSION_NUMBER;

    return major_ver_num;
}
/***********************************************************************************************************************
 End of function qspi_get_major_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_get_minor_version_num
 *
 *  Return value:   QSPI driver Minor version number
 *
 *  Parameters:     None
 *
 *  Description:    Gets the QSPI driver's Minor version number
 *
 **********************************************************************************************************************/
uint8_t qspi_get_minor_version_num (void)
{
    uint8_t minor_ver_num = (uint8_t) QSPI_DRIVER_MINOR_VERSION_NUMBER;

    return minor_ver_num;
}
/***********************************************************************************************************************
 End of function qspi_get_minor_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_init
 *
 *  Return value:   None
 *
 *  Parameters:     void
 *
 *  Description:    Initialisation QSPI IP
 *
 **********************************************************************************************************************/
void qspi_init (void)
{
    uint32_t channel;

    for (channel = 0; channel < MAX_QSPI_CHANNELS; channel++)
    {
        qspi_channels_params[channel].base_address = (void *) 0;
        /* Setup power management control & Enable Clock for QSPI channel */
        R_SYSCTRL_EnableQSPI(channel);
    }

    return;
}
/***********************************************************************************************************************
 End of function qspi_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_uninit
 *
 *  Return value:   None
 *
 *  Parameters:     void
 *
 *  Description:    Uninitialise QSPI IP
 *
 **********************************************************************************************************************/
void qspi_uninit (void)
{
    uint32_t channel;

    for (channel = 0; channel < MAX_QSPI_CHANNELS; channel++)
    {
        /* Close power management control & Enable Clock for QSPI channel */
        R_SYSCTRL_DisableQSPI(channel);
        qspi_channels_params[channel].base_address = (void *) 0;
    }

    return;
}
/***********************************************************************************************************************
 End of function qspi_uninit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_channel_open
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - QSPI channel number
 *
 *  Description:    Opens a QSPI channel
 *
 **********************************************************************************************************************/
ER_RET qspi_channel_open (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    volatile QSPI_Type *channel_base_address;

    if (chan_num < MAX_QSPI_CHANNELS)
    {
        channel_base_address = (volatile QSPI_Type *) RZN1_QSPI_BASE;

        /* Only want to read device using DAC so try to support whatever device is connected    */
        /* Set QSPI flash size to size of QSPI memory-mapped area.                              */
        /* Then should be able to read to end of all supported serial flash devices connected.  */
        /* These values are checked in the interface file                                       */
        qspi_channels_params[chan_num].base_address = channel_base_address;
        qspi_channels_params[chan_num].qspi_ahb_base_addr = RZN1_V_QSPI_BASE;
        qspi_channels_params[chan_num].qspi_ahb_base_size = RZN1_V_QSPI_SIZE;
        qspi_channels_params[chan_num].page_size = QSPI_PAGE_SIZE;

        /* Disable QSPI controller */
        qspi_controller_disable(chan_num);

        /* Disable all interrupts */
        channel_base_address->irq_mask_reg.LONG = 0;

        /* Configure the remap address register, no remap */
        channel_base_address->remap_addr_reg.LONG = 0;

        /* Enable AHB write protection before enabling QSPI controller and
         * protect the whole range  */
        channel_base_address->lower_wr_prot_reg.LONG = 0;
        channel_base_address->upper_wr_prot_reg.LONG = (uint32_t) ~0;

        channel_base_address->wr_prot_ctrl_reg.BIT.inv_fld = 0;
        channel_base_address->wr_prot_ctrl_reg.BIT.enb_fld = 1;

        /* Enable direct access controller */
        channel_base_address->config_reg.BIT.enb_dir_acc_ctlr_fld = 1;

        /* Disable AHB address re-mapping */
        channel_base_address->config_reg.BIT.enb_ahb_addr_remap_fld = 0;

        /* Set master mode baud rate divisor to 32 */
        channel_base_address->config_reg.BIT.mstr_baud_div_fld = 0xF;

        /* Enable QSPI controller */
        qspi_controller_enable(chan_num);

        /* Set Chip select */
        qspi_chipselect(chan_num, 0);
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function qspi_channel_open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_channel_close
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - QSPI channel number
 *
 *  Description:    Closes a QSPI channel
 *
 **********************************************************************************************************************/
ER_RET qspi_channel_close (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

    /* Disable QSPI controller */
    qspi_controller_disable(chan_num);

    qspi_channels_params[chan_num].base_address = (void *) 0;

    return ret_val;
}
/***********************************************************************************************************************
 End of function qspi_channel_close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_set_transfer_config
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - QSPI channel number
 *                  transfer_config - transfer configuration
 *
 *  Description:    Sets QSPI channel transfer configuration
 *
 **********************************************************************************************************************/
ER_RET qspi_set_transfer_config (uint8_t chan_num, qspi_info_t *transfer_config)
{
    ER_RET ret_val = ER_OK;

    qspi_channels_params[chan_num].page_size = transfer_config->page_size;
    qspi_channels_params[chan_num].qspi_ahb_base_size = transfer_config->flash_size;

    /* Note: OP_MODE and TRANSFER_MODE are fixed to QSPI_OPMODE_QUAD_SPI & QSPI_TRANSFER_MODE_DAC */
    /*        for this version of the QSPI driver                                                 */
    return ret_val;
}
/***********************************************************************************************************************
 End of function qspi_set_transfer_config
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_get_transfer_config
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - QSPI channel number
 *                  transfer_config - where to store transfer configuration
 *
 *  Description:    Gets QSPI channel transfer configuration
 *
 **********************************************************************************************************************/
ER_RET qspi_get_transfer_config (uint8_t chan_num, qspi_info_t *transfer_config)
{
    ER_RET ret_val = ER_OK;

    transfer_config->page_size = qspi_channels_params[chan_num].page_size;
    transfer_config->flash_size = qspi_channels_params[chan_num].qspi_ahb_base_size;
    transfer_config->op_mode = QSPI_OPMODE_QUAD_SPI;
    transfer_config->tran_mode = QSPI_TRANSFER_MODE_DAC;

    return ret_val;
}
/***********************************************************************************************************************
 End of function qspi_get_transfer_config
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_reset
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - QSPI channel number
 *
 *  Description:    Resets a QSPI channel
 *
 **********************************************************************************************************************/
ER_RET qspi_reset (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;

    /* Disable QSPI controller */
    qspi_controller_disable(chan_num);

    /* Disable all interrupts */
    ((volatile QSPI_Type *) RZN1_QSPI_BASE)->irq_mask_reg.LONG = 0;

    /* Configure the remap address register, no remap */
    ((volatile QSPI_Type *) RZN1_QSPI_BASE)->remap_addr_reg.LONG = 0;

    /* Enable AHB write protection before enabling QSPI controller and
     * protect the whole range  */
    ((volatile QSPI_Type *) RZN1_QSPI_BASE)->lower_wr_prot_reg.LONG = 0;
    ((volatile QSPI_Type *) RZN1_QSPI_BASE)->upper_wr_prot_reg.LONG = (uint32_t) ~0;

    ((volatile QSPI_Type *) RZN1_QSPI_BASE)->wr_prot_ctrl_reg.BIT.inv_fld = 0;
    ((volatile QSPI_Type *) RZN1_QSPI_BASE)->wr_prot_ctrl_reg.BIT.enb_fld = 1;

    /* Enable direct access controller */
    ((volatile QSPI_Type *) RZN1_QSPI_BASE)->config_reg.BIT.enb_dir_acc_ctlr_fld = 1;

    /* Disable AHB address re-mapping */
    ((volatile QSPI_Type *) RZN1_QSPI_BASE)->config_reg.BIT.enb_ahb_addr_remap_fld = 0;

    /* Set master mode baud rate divisor to 32 */
    ((volatile QSPI_Type *) RZN1_QSPI_BASE)->config_reg.BIT.mstr_baud_div_fld = 0xF;

    /* Enable QSPI controller */
    qspi_controller_enable(chan_num);

    /* Set Chip select */
    qspi_chipselect(chan_num, 0); /* select on-board device */

    return ret_val;
}
/***********************************************************************************************************************
 End of function qspi_reset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_read
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - QSPI channel number
 *                  offset - Offset in bytes from start of Flash from where data should be read
 *                  buf - pointer to buffer where data read from Flash should be stored
 *                  block_len - number of bytes to read
 *
 *  Description:    Reads a block of data from serial flash using direct access
 *                         mode of QSPI Controller IP.
 *
 **********************************************************************************************************************/
ER_RET qspi_read (uint8_t chan_num, uint32_t offset, uint8_t *buf, uint32_t block_len)
{
    ER_RET ret_val = ER_OK;

    /* check parameters which were not checked in interface function */
    if ((offset + block_len) > qspi_channels_params[chan_num].qspi_ahb_base_size)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* memory mapped read*/
        memcpy(buf, (uint8_t *) (qspi_channels_params[chan_num].qspi_ahb_base_addr) + offset, (size_t) block_len);
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function qspi_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_erase
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - QSPI channel number
 *                  erase_block_offset - Offset in bytes from start of Flash from where data should be erased
 *                  erase_size - number of bytes to erase
 *                  Note1:  Minimum erasable block size is 4k bytes (0x1000 or QSPI_ERASE_BLOCK_SIZE_4K),
 *                  Note2: If number_blocks is 0xffffffff (QSPI_ERASE_ALL_FLASH) then whole flash is erased
 *  Description:    Erases blocks of serial flash
 *
 **********************************************************************************************************************/
ER_RET qspi_erase (uint8_t chan_num, uint32_t erase_block_offset, uint32_t erase_size)
{
    ER_RET ret_val = ER_OK;
    uint32_t byte_offset;
#ifdef CORE_CA7
    UNCACHED_BUFFER static uint8_t
    flash_command[QSPI_FLASH_MAX_COMMAND_LEN];
#else
    static uint8_t flash_command[QSPI_FLASH_MAX_COMMAND_LEN];
#endif

    if (QSPI_ERASE_ALL_FLASH == erase_size)
    {
        ;
    }
    else
    {
        ((volatile QSPI_Type *) RZN1_QSPI_BASE)->wr_prot_ctrl_reg.BIT.enb_fld = 0; /* remove write-protect */

        byte_offset = erase_block_offset;

        while (erase_size > 0)
        {
            flash_command[0] = QSPI_COMMAND_WRITE_ENABLE;
            ret_val = qspi_execute_command(chan_num, flash_command,
            QSPI_FLASH_NO_ADDR_COMMAND_LEN, FIT_NO_PTR, 0);

            if (ER_OK == ret_val)
            {
                flash_command[0] = (uint8_t) QSPI_COMMAND_4ADDR_ERASE_64K;
                flash_command[1] = (uint8_t)(byte_offset >> 24);
                flash_command[2] = (uint8_t)(byte_offset >> 16);
                flash_command[3] = (uint8_t)(byte_offset >> 8);
                flash_command[4] = (uint8_t) byte_offset;
                ret_val = qspi_execute_command(chan_num, flash_command,
                QSPI_FLASH_ERASE_COMMAND_LEN, FIT_NO_PTR, 0);

                if (ER_OK == ret_val)
                {
                    /* wait for erase to complete */
                    ret_val = qspi_wait_ready(chan_num,
                    FLASH_SECTOR_ERASE_TIMEOUT);
                }

            }
            if (ER_OK == ret_val)
            {
                erase_size -= QSPI_ERASE_BLOCK_SIZE_64K;
                byte_offset += QSPI_ERASE_BLOCK_SIZE_64K;
            }
            else
            {
                break;
            }

        }
        ((volatile QSPI_Type *) RZN1_QSPI_BASE)->wr_prot_ctrl_reg.BIT.enb_fld = 1; /* write protect */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function qspi_erase
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_write
 *
 *  Return value:   Error status
 *
 *  Parameters:     chan_num - QSPI channel number
 *                  offset - Offset in bytes from start of Flash where data should be written
 *                  buf - pointer to buffer with data to be written
 *                  block_len - size of block to be written in bytes
 *
 *  Description:    Writes data to serial flash using direct access
 *                         mode of QSPI Controller IP.
 *
 **********************************************************************************************************************/
ER_RET qspi_write (uint8_t chan_num, uint32_t offset, uint8_t *buf, uint32_t block_len)
{
    ER_RET ret_val = ER_OK;

    /* check parameters which were not checked in interface function */
    if ((offset + block_len) > qspi_channels_params[chan_num].qspi_ahb_base_size)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        ((volatile QSPI_Type *) RZN1_QSPI_BASE)->wr_prot_ctrl_reg.BIT.enb_fld = 0; /* remove write-protect */
        memcpy((uint8_t *) (qspi_channels_params[chan_num].qspi_ahb_base_addr) + offset, buf, (size_t) block_len);
        ((volatile QSPI_Type *) RZN1_QSPI_BASE)->wr_prot_ctrl_reg.BIT.enb_fld = 1; /* write protect */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function qspi_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_controller_enable
 *
 *  Return value:   None
 *
 *  Parameters:     chan_num - QSPI channel
 *
 *  Description:    QSPI enable controller IP
 *
 **********************************************************************************************************************/
static void qspi_controller_enable (uint8_t chan_num)
{
    volatile QSPI_Type *channel_base_address;

    channel_base_address = qspi_channels_params[chan_num].base_address;
    ((volatile QSPI_Type *) channel_base_address)->config_reg.BIT.enb_qspi_fld = 1;
}
/***********************************************************************************************************************
 End of function qspi_controller_enable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_controller_disable
 *
 *  Return value:   None
 *
 *  Parameters:     chan_num - QSPI channel
 *
 *  Description:    QSPI disable controller IP
 *
 **********************************************************************************************************************/
static void qspi_controller_disable (uint8_t chan_num)
{
    volatile QSPI_Type *channel_base_address;

    channel_base_address = qspi_channels_params[chan_num].base_address;
    ((volatile QSPI_Type *) channel_base_address)->config_reg.BIT.enb_qspi_fld = 0;
}
/***********************************************************************************************************************
 End of function qspi_controller_disable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_chipselect
 *
 *  Return value:   0(ESUCCESS) if success. <0 Error value
 *
 *  Parameters:     chip_select
 *
 *  Description:
 *
 **********************************************************************************************************************/
static void qspi_chipselect (uint8_t chan_num, uint32_t chip_select)
{
    volatile QSPI_Type *channel_base_address;

    channel_base_address = qspi_channels_params[chan_num].base_address;

    /* Disable QSPI controller */
    qspi_controller_disable(chan_num);

    ((volatile QSPI_Type *) channel_base_address)->config_reg.BIT.periph_sel_dec_fld = 0;

    /* Set the peripheral chip select bits */
    chip_select = 0xF & ( ~(1 << chip_select));

    /* Write peripheral chip select bits to the configuration register. */
    ((volatile QSPI_Type *) channel_base_address)->config_reg.BIT.periph_cs_lines_fld = chip_select;

    /* Enable QSPI controller */
    qspi_controller_enable(chan_num);
}
/***********************************************************************************************************************
 End of function qspi_chipselect
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_execute_command
 *
 *  Return value:   0(ESUCCESS) if success. <0 Error value
 *
 *  Parameters:     chan_num - QSPI channel where command should be sent
 *                  cmd_buf - buffer with command to send (and address to send if required)
 *                  cmd_len - number of bytes (command + address) in cmd_buf
 *                  data_buf - buffer with data to send (if required)
 *                  data_len - number of bytes of data to send (if required)
 *
 *  Description:    Issue a command with address and data to write, to the Flash device
 *
 **********************************************************************************************************************/
static ER_RET qspi_execute_command (uint8_t chan_num, uint8_t *cmd_buf, uint32_t cmd_len, uint8_t *data_buf,
        uint32_t data_len)
{
    ER_RET ret_val = ER_OK;
    volatile QSPI_Type *channel_base_address;
    uint32_t wait_completion;
    uint32_t command_addr;

    INTERNAL_NOT_USED(data_buf);
    INTERNAL_NOT_USED(data_len);

    channel_base_address = qspi_channels_params[chan_num].base_address;

    /* Clear the command control register */
    ((volatile QSPI_Type *) channel_base_address)->flash_cmd_ctrl_reg.LONG = 0;

    /* write the command to the Command Control Register */
    ((volatile QSPI_Type *) channel_base_address)->flash_cmd_ctrl_reg.BIT.cmd_opcode_fld = cmd_buf[0];
    if (cmd_len > 1)
    {
        /* Address bytes required */
        ((volatile QSPI_Type *) channel_base_address)->flash_cmd_ctrl_reg.BIT.enb_comd_addr_fld = 1;

        if ((QSPI_FLASH_ADDR_LEN4 + 1) == cmd_len)
        {
            /* 4-byte address */
            ((volatile QSPI_Type *) channel_base_address)->flash_cmd_ctrl_reg.BIT.num_addr_bytes_fld = 3; /* 11b for 4 address bytes */
            command_addr = 0;
            command_addr = ((uint32_t)(cmd_buf[1]) << 24) | ((uint32_t)(cmd_buf[2]) << 16)
                    | ((uint32_t)(cmd_buf[3]) << 8) | ((uint32_t)(cmd_buf[4]));
            ((volatile QSPI_Type *) channel_base_address)->flash_cmd_addr_reg.LONG = command_addr;
        }
        else if ((QSPI_FLASH_ADDR_LEN3 + 1) == cmd_len)
        {
            /* 3-byte address */
            ((volatile QSPI_Type *) channel_base_address)->flash_cmd_ctrl_reg.BIT.num_addr_bytes_fld = 2; /* 10b for 3 address bytes */
            command_addr = 0;
            command_addr = ((uint32_t)(cmd_buf[1]) << 16) | ((uint32_t)(cmd_buf[2]) << 8) | (uint32_t)(cmd_buf[3]);

            ((volatile QSPI_Type *) channel_base_address)->flash_cmd_addr_reg.LONG = command_addr;
        }
        else
        {
            ret_val = ER_PARAM;
        }
    }

    if (ER_OK == ret_val)
    {
        /* Launch the command */
        ((volatile QSPI_Type *) channel_base_address)->flash_cmd_ctrl_reg.BIT.cmd_exec_fld = 1;

        /* Wait while execution is in progress */
        wait_completion = QSPI_CMD_EXECUTE_TIMEOUT_COUNT;
        while (wait_completion--)
        {
            if (0 == ((volatile QSPI_Type*) channel_base_address)->flash_cmd_ctrl_reg.BIT.cmd_exec_status_fld)
            {
                break;
            }
            Delay_usec(50); /* 50 usecs delay */
        }

        if (0 == wait_completion)
        {
            /* timed-out waiting for execution completion */
            ret_val = ER_SYS;
        }
        else
        {
            /* Wait for QSPI idle status */
            ret_val = qspi_wait_idle(chan_num);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function qspi_execute_command
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_wait_idle
 *
 *  Return value:   0(ESUCCESS) if success. <0 Error value
 *
 *  Parameters:     chan_num - QSPI channel to wait for
 *
 *  Description:    Wait for IDLE status from flash device
 *
 **********************************************************************************************************************/
static ER_RET qspi_wait_idle (uint8_t chan_num)
{
    int32_t ret_val = ER_OK;
    volatile QSPI_Type *channel_base_address;
    uint32_t retry_count = 0;
    uint32_t timeout_count;

    channel_base_address = qspi_channels_params[chan_num].base_address;

    for (timeout_count = QSPI_WAIT_FOR_IDLE_TIMEOUT_COUNT; timeout_count > 0; timeout_count--)
    {
        /* Delay 1 msec */
        Delay_usec(1000);

        if (1 == ((volatile QSPI_Type*) channel_base_address)->config_reg.BIT.qspi_idle_fld)
        {
            retry_count++;
        }
        else
        {
            retry_count = 0;
        }

        /* In true Idle state when read back the same idle status consecutively */
        if (retry_count >= QSPI_IDLE_RETRY)
        {
            ret_val = ER_OK;
            break;
        }
    }

    if (0 == timeout_count)
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function qspi_wait_idle
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       qspi_wait_ready
 *
 *  Return value:   0(ESUCCESS) if success. <0 Error value
 *
 *  Parameters:     chan_num - QSPI channel to wait for
 *                  timeout - how long to wait in msecs
 *
 *  Description:    Wait for Flash to be ready (command completion)
 *
 **********************************************************************************************************************/
static ER_RET qspi_wait_ready (uint8_t chan_num, uint64_t timeout)
{
    int32_t ret_val = ER_OK;
    volatile QSPI_Type *channel_base_address;
    uint32_t wait_completion;
    uint32_t timeout_count;
    static uint32_t read_status_value;

    /*uint32_t            wait_count = 0;*/
    uint32_t i;

    channel_base_address = qspi_channels_params[chan_num].base_address;

    for (timeout_count = timeout; timeout_count > 0; timeout_count--)
    {
        /* Clear the command control register */
        ((volatile QSPI_Type *) channel_base_address)->flash_cmd_ctrl_reg.LONG = 0;

        /* write the command READ STATUS to the Command Control Register  */
        ((volatile QSPI_Type *) channel_base_address)->flash_cmd_ctrl_reg.BIT.cmd_opcode_fld =
        QSPI_COMMAND_READ_STATUS;
        ((volatile QSPI_Type *) channel_base_address)->flash_cmd_ctrl_reg.BIT.enb_read_data_fld = 1;

        /* set number of bytes to read (set to '0' for 1 byte) */
        ((volatile QSPI_Type *) channel_base_address)->flash_cmd_ctrl_reg.BIT.num_rd_data_bytes_fld = 0;

        /* Launch the command */
        ((volatile QSPI_Type *) channel_base_address)->flash_cmd_ctrl_reg.BIT.cmd_exec_fld = 1;

        /* Wait while execution is in progress */
        wait_completion = QSPI_CMD_EXECUTE_TIMEOUT_COUNT;
        while (wait_completion--)
        {
            if (0 == ((volatile QSPI_Type*) channel_base_address)->flash_cmd_ctrl_reg.BIT.cmd_exec_status_fld)
            {
                break;
            }

            /*DELAY(FIFTY_USECS);*/
        }

        if (0 == wait_completion)
        {
            /* timed-out waiting for execution completion */
            ret_val = ER_SYS;
        }
        else
        {
            /* Wait for QSPI idle status */
            ret_val = qspi_wait_idle(chan_num);
        }

        if (ER_OK == ret_val)
        {
            /* QSPI_COMMAND_READ_STATUS sent ok, now read the status */
            read_status_value = ((volatile QSPI_Type *) channel_base_address)->flash_rd_data_lower_reg.LONG;
            if ((read_status_value & 0x01) == 0)
            {
                ret_val = ER_OK;
                break;
            }

            /*if (((volatile QSPI_Type *)channel_base_address)->polling_flash_status_reg.BIT.device_status_valid_fld == 1)
             {*/
            /* flash status is valid */
            /*read_status_value = ((volatile QSPI_Type *)channel_base_address)->polling_flash_status_reg.BIT.device_status_fld;
             if ((read_status_value & 1) == 0)
             {
             ret_val = ER_OK;
             break;
             }
             else
             {
             wait_count++;
             if (wait_count == 100)
             {
             wait_count = 0;
             }
             }
             }*/

            ret_val = ER_SYS;
            for (i = 0; i < 0x10000; i++)
            {
                ;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function qspi_wait_ready
 **********************************************************************************************************************/

