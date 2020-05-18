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
 * $Revision: 1347 $
 * $Date: 2019-03-08 11:11:05 +0000 (Fri, 08 Mar 2019) $
 *
 * PROJECT NAME :    RZ/N1 bare metal Drivers
 * FILE                 :    r_sdio_rzn1.c
 * Description    :    SDIO control functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_sdio_rzn1_config.h"
#include "r_sdio_rzn1_if.h"
#include "r_sdio_rzn1.h"
#include "iodefine.h"
#include "r_sysctrl_rzn1_if.h"
#include "mcu_interrupts_if.h"
#include "r_timer_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#ifdef CORE_CA7
#define SDIO_CMD_TIMEOUT                (100u)     
#else
#define SDIO_CMD_TIMEOUT                (1u)     /* 1 x 10ms = 10ms */
#endif

#define SDIO_INT_CLOCK_TIMEOUT          (10u)    /* internal clock stabilisation timeout */
/***********************************************************************************************************************
 * Type defintions
 **********************************************************************************************************************/
typedef struct
{
    volatile SDIO_Type* base_address; /* Base address of the SDHC */
    sdio_callback sdio_callback_function; /* transfer complete (&error) callback function */
    sdio_callback sdio_wakeup_callback_function; /* wake up callback function */
    sdio_insert_eject_callback sdio_insert_eject_callback; /* card inserted and ejected callback function */
    uint16_t sdio_normal_interrupt_status; /* normal interrupt status */
    uint16_t sdio_error_interrupt_status; /* error interrupt status */
    bool sdio_card_inserted; /* used to determine if the card has been removed */
} SDIO_INSTANCE_PARAMETERS;

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static SDIO_INSTANCE_PARAMETERS sdio_instance_params[MAX_SDIO_INSTANCES];
static bool SDIO_CMD_TIME_UP;
static uint32_t sdio_cmd_time_count;

/***********************************************************************************************************************
 * External functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local functions
 **********************************************************************************************************************/
static void handle_sdio_interrupt (IRQn_Type *irq_num_ptr);
static void sdio_cmd_timer1_callback (unsigned long interval_count);

/***********************************************************************************************************************
 *
 *    Function:           sdio_getdrivernumber
 *
 *    Return value:       None.
 *
 *    Parameters:         Where to store SDIO major & minor version numbers
 *
 *    Description:        Returns the driver version number
 *
 **********************************************************************************************************************/
void sdio_getdrivernumber (uint8_t *sdio_version)
{
    sdio_version[0] = (uint8_t) SDIO_DRIVER_MINOR_VERSION_NUMBER;
    sdio_version[1] = (uint8_t) SDIO_DRIVER_MAJOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function sdio_getdrivernumber
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:             sdio_driver_init
 *
 *    Return value:     None.
 *
 *    Parameters:         None.
 *
 *    Description:        System control configuration to allow for both SDIO controller register access.
 *
 **********************************************************************************************************************/
void sdio_driver_init (void)
{
    uint8_t instance;

    for (instance = 0; instance < MAX_SDIO_INSTANCES; instance++)
    {
        sdio_instance_params[instance].sdio_callback_function = (void *) 0;
        sdio_instance_params[instance].sdio_wakeup_callback_function = (void *) 0;
        sdio_instance_params[instance].base_address = (void *) 0;
    }
}
/***********************************************************************************************************************
 End of function sdio_driver_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_open
 *
 *    Return value:     Error status
 *
 *    Parameters:       SDIO_number - SDIO number
 *
 *    Description:      Opens an SDIO instance
 *
 **********************************************************************************************************************/
ER_RET sdio_open (uint8_t SDIO_number)
{
    ER_RET ret_val = ER_OK;
    volatile SDIO_Type *base_address;
    uint16_t i;
    IRQn_Type irq_num;
    uint32_t int_priority;
    MCU_INT_ERR_E mcu_int_err = MCU_INT_SUCCESS;

    if (SDIO_number < MAX_SDIO_INSTANCES)
    {
        sdio_instance_params[SDIO_number].base_address = (volatile SDIO_Type *) RZN1_SDIO0_BASE;
        base_address = sdio_instance_params[SDIO_number].base_address;
        /* Setup power management control & Enable Clock for SDIO instance */
        R_SYSCTRL_EnableSDIO(SDIO_number);

        /* Set the base clock frequency */
        R_SYSCTRL_SetSDIOBaseClk(SDIO_number);

        /* Reset the Host Controller */
        base_address->reg_softwarereset.BIT.swreset_for_all = 1;
        for (i = 0; i < 0xFFFF; i++)
        {
            if ( !base_address->reg_softwarereset.BIT.swreset_for_all)
            {
                break;
            }
        }

        /* Time out on the software reset */
        if (base_address->reg_softwarereset.BIT.swreset_for_all)
        {
            ret_val = ER_SYS;
        }
        else
        {
            /* Set bus voltage level */
            base_address->reg_powercontrol.BIT.pwrctrl_sdbusvoltage = 0x07; /* set 3.3V - No other option available */

            /* Enable normal interrupts */
            base_address->reg_normalintrstsena.WORD |= 0x0FF; /* Status enable *//* Card interrupts not supported */
            base_address->reg_normalintrsigena.WORD |= 0x0FF; /* Signal enable */

            /* Enable Error interrupts */
            base_address->reg_errorintrstsena.WORD |= 0x3FF; /* Status enable */
            base_address->reg_errorintrsigena.WORD |= 0x3FF; /* Signal enable */

            /* Set data timeout value */
            base_address->reg_timeoutcontrol.BIT.timeout_ctrvalue = 0x0E; /* TMCLK x 2EXP27 */

            /* Initialise timer */
            timer1_subtimer_init(1, TIMER_TIME_BASE_1MHz);

            /* Ensure internal clock is enabled and stable */
            base_address->reg_clockcontrol.BIT.clkctrl_intclkena = 1;
            SDIO_CMD_TIME_UP = false;
            sdio_cmd_time_count = SDIO_INT_CLOCK_TIMEOUT;

            /* setup timer */
            timer1_subtimer_set_callback(1, &sdio_cmd_timer1_callback);
            timer1_subtimer_start(1, SDIO_TIMER_TICKS);

            while (( !SDIO_CMD_TIME_UP) && ( !(base_address->reg_clockcontrol.BIT.sdhcclkgen_intclkstable_dsync)));

            /* test for timeup */
            if (SDIO_CMD_TIME_UP)
            {
                ret_val = ER_SYS;
            }
            else
            {
                /* Enable external clock and bus power */
                base_address->reg_clockcontrol.BIT.clkctrl_sdclkena = 1;
                base_address->reg_powercontrol.BIT.pwrctrl_sdbuspower = 1;
            }

            /* stop timer */
            timer1_subtimer_stop(1);
        }

        if (ER_OK == ret_val)
        {

            /* Set interrupt priority for SDIO instance & enable system interrupts */
            for (irq_num = (RZN1_IRQ_SDIO0 + SDIO_number);
                    (irq_num <= (RZN1_IRQ_SDIO0_WKUP + SDIO_number)) && (MCU_INT_SUCCESS == mcu_int_err); irq_num++)
            {
                if (R_BSP_InterruptRegisterCallback((IRQn_Type) irq_num, (bsp_int_cb_t) &handle_sdio_interrupt)
                        == MCU_INT_SUCCESS)
                {
                    int_priority = SDIO_DEFAULT_INT_PRIORITY;
                    mcu_int_err = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
                    if (MCU_INT_SUCCESS != mcu_int_err)
                    {
                        ret_val = ER_SYS;
                    }
                    else
                    {
                        mcu_int_err = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);
                    }
                }
                else
                {
                    ret_val = ER_SYS;
                }
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
 End of function sdio_open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:           sdio_close
 *
 *    Return value:       None.
 *
 *    Parameters:         SDIO_number - SDIO number
 *
 *    Description:        Closes an SDIO instance
 *
 **********************************************************************************************************************/
void sdio_close (uint8_t SDIO_number)
{
    IRQn_Type irq_num;

    if ((SDIO_number < MAX_SDIO_INSTANCES) && ((void *) 0 != sdio_instance_params[SDIO_number].base_address))
    {
        /* Clear stored data */
        sdio_instance_params[SDIO_number].base_address = 0;
        sdio_instance_params[SDIO_number].sdio_callback_function = 0;
        sdio_instance_params[SDIO_number].sdio_card_inserted = 0;
        sdio_instance_params[SDIO_number].sdio_error_interrupt_status = 0;
        sdio_instance_params[SDIO_number].sdio_insert_eject_callback = 0;
        sdio_instance_params[SDIO_number].sdio_normal_interrupt_status = 0;
        sdio_instance_params[SDIO_number].sdio_wakeup_callback_function = 0;

        /* disable system interrupts */
        for (irq_num = (RZN1_IRQ_SDIO0 + SDIO_number); irq_num <= (RZN1_IRQ_SDIO0_WKUP + SDIO_number); irq_num++)
        {
            R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE,
            FIT_NO_PTR);
        }

        /* Disable SDIO interconnect */
        R_SYSCTRL_DisableSDIO(SDIO_number);
    }
}
/***********************************************************************************************************************
 End of function sdio_close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_set_trans_config
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      block_size - The block size of the transfer
 *                      block_count - The number of blocks in the transfer
 *                      direction - Whether the transfer is read or write
 *
 *    Description:      Sets the transfer configurations for the transfer
 *
 **********************************************************************************************************************/
ER_RET sdio_set_trans_config (uint8_t SDIO_number, SDIO_TRANS_CTRL transfer_params, uint16_t block_size)
{
    ER_RET ret_val = ER_OK;
    volatile SDIO_Type *base_address = sdio_instance_params[SDIO_number].base_address;

    if ((transfer_params.direction > SDIO_READ) || (block_size > 2048))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Set block size */
        base_address->reg_blocksize.BIT.xfer_blocksize = block_size;

        /* Set block count */
        base_address->reg_blockcount.BIT.xfer_blockcount = transfer_params.block_count;

        /* Set transfer mode */
        if (block_size > 0x00)
        {
            base_address->reg_transfermode.BIT.xfermode_dataxferdir = transfer_params.direction;

            /* Setup the DMA transfer */
            base_address->reg_transfermode.BIT.xfermode_dmaenable = 0x01;
            base_address->reg_sdmasysaddrlo.BIT.sdma_sysaddress = (uint32_t) transfer_params.buffer & 0xFFFF;
            base_address->reg_sdmasysaddrhi.BIT.sdma_sysaddress = (uint32_t) transfer_params.buffer >> 16;
            if (transfer_params.block_count > 0x01)
            {
                base_address->reg_transfermode.BIT.xfermode_multiblksel = 0x01; /* Multiple block transfer*/
                base_address->reg_transfermode.BIT.xfermode_blkcntena = 0x01; /* Block count enabled */

                /* Enable Auto CMD12 */
                base_address->reg_transfermode.BIT.xfermode_autocmdena = 0x01;
            }
            else
            {
                base_address->reg_transfermode.BIT.xfermode_multiblksel = 0x00;
                base_address->reg_transfermode.BIT.xfermode_blkcntena = 0x00;

                /* Disable auto CMD12 */
                base_address->reg_transfermode.BIT.xfermode_autocmdena = 0x00;
            }
        }
        else
        {
            base_address->reg_transfermode.BIT.xfermode_dmaenable = 0x00;
            base_address->reg_transfermode.BIT.xfermode_autocmdena = 0x00;
        }

        /* Register callback */
        if ((void *) 0 != transfer_params.trans_complete_callback)
        {
            sdio_instance_params[SDIO_number].sdio_callback_function = transfer_params.trans_complete_callback;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_set_trans_config
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_set_hc_bus_width
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      bus_width - The desired width of the data bus
 *
 *    Description:      Sets the data bus width
 *
 **********************************************************************************************************************/
ER_RET sdio_set_hc_bus_width (uint8_t SDIO_number, SDIO_TRANS_WIDTH bus_width)
{
    ER_RET ret_val = ER_OK;
    volatile SDIO_Type *base_address = sdio_instance_params[SDIO_number].base_address;

    switch (bus_width)
    {
        case SDIO_WIDTH_1_BIT:
            base_address->reg_hostcontrol1.BIT.hostctrl1_extdatawidth = 0; /* width detected by data trans width */
            base_address->reg_hostcontrol1.BIT.hostctrl1_datawidth = 0; /* width = 1-bit */
        break;
        case SDIO_WIDTH_4_BIT:
            base_address->reg_hostcontrol1.BIT.hostctrl1_extdatawidth = 0;
            base_address->reg_hostcontrol1.BIT.hostctrl1_datawidth = 1; /* width = 4-bits */
        break;
        case SDIO_WIDTH_8_BIT:
            if (base_address->reg_capabilities.BIT.corecfg_8bitsupport) /* Determine 8 bit support */
            {
                base_address->reg_hostcontrol1.BIT.hostctrl1_extdatawidth = 1; /* 8-bit bus width */
            }
        break;
        default:
            ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_set_hc_bus_width
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_send_cmd
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      command - parameters required for the command
 *                               (command number, argument, response type, direction, command type, command data)
 *
 *    Description:      Sends and SD protocol command to the card.
 *
 **********************************************************************************************************************/
ER_RET sdio_send_cmd (uint8_t SDIO_number, SDIO_COMMAND *command)
{
    ER_RET ret_val = ER_OK;
    uint16_t cmd_reg = 0;
    volatile SDIO_Type *base_address = sdio_instance_params[SDIO_number].base_address;

    if ((command->command_index > 0x40) || (command->command_type > SDIO_CMD_DATA))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Check there is a card present */
        if ( !base_address->reg_presentstate.BIT.sdhccarddet_inserted_dsync)
        {
            ret_val = ER_SYS;
        }
        else
        {
            /* Ensure the command line is free and if the command is a data command: ensure the DAT line is free */
            if ((base_address->reg_presentstate.BIT.presentstate_inhibitdat && command->command_type)
                    || (base_address->reg_presentstate.BIT.presentstate_inhibitcmd))
            {
                ret_val = ER_INVAL;
            }
            else
            {
                /* Set command argument */
                base_address->reg_argument1lo.BIT.command_argument1 = command->argument & 0xFFFF;
                base_address->reg_argument1hi.BIT.command_argument1 = command->argument >> 16;

                cmd_reg = (command->command_index << 8) /* CMD number */
                | (command->command_type << 5); /* Data present/ not present */

                /* Set command register */
                switch (command->response_type)
                {
                    case SDIO_RESPONSE_NONE:
                    break; /* CRC check disable */

                        /* do not check index field against command index */
                    case SDIO_RESPONSE_R3:
                    case SDIO_RESPONSE_R4:
                        cmd_reg |= 0x02; /* Response length 48 + Normal command type*/

                        /* CRC check disable */
                    break; /* do not check index field against command index */
                    case SDIO_RESPONSE_R1b:
                    case SDIO_RESPONSE_R5b:
                        cmd_reg |= 0x01; /* Response length 48, check busy after response + Normal command type*/ // @suppress("No break at end of case")
                    case SDIO_RESPONSE_R1:
                    case SDIO_RESPONSE_R5:
                    case SDIO_RESPONSE_R6:
                    case SDIO_RESPONSE_R7:
                        cmd_reg |= (0x02 /* Response length 48 + Normal command type*/
                        | (0x01 << 3) /* CRC check enable */
                        | (0x01 << 4)); /* check index field against command index */
                    break;
                    case SDIO_RESPONSE_R2:
                        cmd_reg |= (0x01/* Response length 136 + Normal command type*/
                        | (0x01 << 3)); /* CRC check enable */
                    break; /* do not check index field against command index */
                    default:
                        ret_val = ER_PARAM;
                }

                if (ER_OK == ret_val)
                {
                    base_address->reg_command.WORD = cmd_reg;

                    /* Wait for response */
                    ret_val = sdio_wait_for_interrupt(SDIO_number,
                    SDIO_CMD_TIMEOUT, SD_CMD_COMPLETE);
                }
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_send_cmd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         SDIO_Get_Response
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      response_type - The desired response type
 *                      response - Store the response here
 *
 *    Description:      Populates the response parameter with the contents of the
 *                      response registers.
 *
 **********************************************************************************************************************/
ER_RET sdio_get_response (uint8_t SDIO_number, SDIO_RESPONSE_TYPE response_type, uint32_t *response)
{
    ER_RET ret_val = ER_OK;
    volatile SDIO_Type *base_address = sdio_instance_params[SDIO_number].base_address;

    if ((SDIO_RESPONSE_R7 < response_type) || (SDIO_number > MAX_SDIO_INSTANCES))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        if (SDIO_RESPONSE_R2 == response_type)
        {
            *response = base_address->reg_response0.WORD;
            ( *response++) |= (base_address->reg_response1.WORD << 16);
            *response = base_address->reg_response2.WORD;
            ( *response++) |= (base_address->reg_response3.WORD << 16);
            *response = base_address->reg_response4.WORD;
            ( *response++) |= (base_address->reg_response5.WORD << 16);
            *response = base_address->reg_response6.WORD;
            ( *response) |= (base_address->reg_response7.WORD << 16);
        }
        else
        {
            *response = base_address->reg_response0.WORD;
            ( *response) |= (base_address->reg_response1.WORD << 16);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_get_response
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_set_clock_div
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      clk_div - The clock divisor specified by the user
 *
 *    Description:      Sets the clock divisor for the SDIO_CLK signal
 *                      such that the Clock frequency = (Base clock) / divisor
 *
 **********************************************************************************************************************/
ER_RET sdio_set_clock_div (uint8_t SDIO_number, SDIO_CLK_DIV clk_div)
{
    ER_RET ret_val = ER_OK;
    volatile SDIO_Type *base_address = sdio_instance_params[SDIO_number].base_address;

    /* Must disable the clock in order to configure it */
    base_address->reg_clockcontrol.BIT.clkctrl_sdclkena = 0;

    /* Only one bit can be set in the Clock control register EXCEPT: for SDIO_CLK_DIV_2046 where all bits are set */
    switch (clk_div)
    {
        case SDIO_CLK_DIV_2046:
            base_address->reg_clockcontrol.WORD |= 0xFFC0;
        break;
        case SDIO_CLK_DIV_1024:
        case SDIO_CLK_DIV_512:
            base_address->reg_clockcontrol.BIT.clkctrl_sdclkfreqsel = 0x00; /* Lower bits */
            base_address->reg_clockcontrol.BIT.clkctrl_sdclkfreqsel_upperbits = 0x01 << (clk_div - SDIO_CLK_DIV_512); /* 2 upper bits */
        break;
        case SDIO_CLK_DIV_256:
        case SDIO_CLK_DIV_128:
        case SDIO_CLK_DIV_64:
        case SDIO_CLK_DIV_32:
        case SDIO_CLK_DIV_16:
        case SDIO_CLK_DIV_8:
        case SDIO_CLK_DIV_4:
        case SDIO_CLK_DIV_2:
            base_address->reg_clockcontrol.BIT.clkctrl_sdclkfreqsel_upperbits = 0x00; /* Clear upper bits so they do not interfere with desired value */
            base_address->reg_clockcontrol.BIT.clkctrl_sdclkfreqsel = 0x01 << (clk_div - SDIO_CLK_DIV_2);
        break;
        case SDIO_CLK_DIV_BASE_FREQ:
            base_address->reg_clockcontrol.BIT.clkctrl_sdclkfreqsel_upperbits = 0x00;
            base_address->reg_clockcontrol.BIT.clkctrl_sdclkfreqsel = 0x00;
        break;
        default:
            ret_val = ER_PARAM;
    }

    /* Re-enable the clock */
    base_address->reg_clockcontrol.BIT.clkctrl_sdclkena = 1;

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_set_clock_div
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_get_write_protection
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      write_protected - The write protection status of the card
 *
 *    Description:      Checks the mechanical write protection switch of the card
 *
 **********************************************************************************************************************/
ER_RET sdio_get_write_protection (uint8_t SDIO_number, bool *write_protected)
{
    ER_RET ret_val = ER_OK;
    volatile SDIO_Type *base_address = sdio_instance_params[SDIO_number].base_address;

    *write_protected = !(base_address->reg_presentstate.BIT.sdif_wp_dsync);

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_get_write_protection
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_register_call_back
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      call_back - The user-made callback function
 *
 *    Description:      Registers a callback function for card inserted and card
 *                      ejected interrupt handling
 *
 **********************************************************************************************************************/
ER_RET sdio_register_call_back (uint8_t SDIO_number, sdio_insert_eject_callback call_back)
{
    ER_RET ret_val = ER_OK;

    if ((SDIO_number < MAX_SDIO_INSTANCES) && ((void *) 0 != call_back))
    {
        sdio_instance_params[SDIO_number].sdio_insert_eject_callback = call_back;
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_register_call_back
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_wait_for_interrupt
 *
 *    Return value:     Error status
 *
 *    Parameters:       SDIO_number - Which SDIO instance
 *                      wait_time - Length of time to wait for
 *
 *    Description:      Waits for an SDIO interrupt from the specified instance
 *
 **********************************************************************************************************************/
ER_RET sdio_wait_for_interrupt (uint8_t SDIO_number, uint32_t wait_time, // @suppress("Function definition ordering")     // @suppress("ISR definition")
        uint16_t mask)
{
    ER_RET ret_val = ER_OK;
    SDIO_CMD_TIME_UP = false;
    sdio_cmd_time_count = wait_time;

    /* register callback function */
    timer1_subtimer_set_callback(1, &sdio_cmd_timer1_callback);

    /* Start timer */
    timer1_subtimer_start(1, SDIO_TIMER_TICKS);

    while (( !SDIO_CMD_TIME_UP) && (0 == (sdio_instance_params[SDIO_number].sdio_normal_interrupt_status & (mask | SD_ERROR))));

    /* test for timeup */
    if (SDIO_CMD_TIME_UP || (sdio_instance_params[SDIO_number].sdio_normal_interrupt_status & SD_ERROR))
    {
        ret_val = ER_SYS;
    }

    /* stop timer */
    timer1_subtimer_stop(1);

    /* Clear interrupt status */
    sdio_instance_params[SDIO_number].sdio_normal_interrupt_status = 0;

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_wait_for_interrupt
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         handle_sdio_interrupt
 *
 *    Return value:     none
 *
 *    Parameters:       irq_num_ptr - pointer to interrupt vector number
 *
 *    Description:      handle SDIO Interrupt
 *
 **********************************************************************************************************************/
static void handle_sdio_interrupt (IRQn_Type *irq_num_ptr)
{
    IRQn_Type irq_num = *irq_num_ptr;
    volatile SDIO_Type *base_address;

    /* Calculate the SDIO number */
    uint8_t sdio_number = (irq_num - RZN1_IRQ_SDIO0) / 2; /* 2 IRQs for each instance (ordinary IRQ and wakeup IRQ) */
    base_address = sdio_instance_params[sdio_number].base_address;

    /* Read from normal interrupt status register */
    sdio_instance_params[sdio_number].sdio_normal_interrupt_status = base_address->reg_normalintrsts.WORD;
    base_address->reg_normalintrsts.WORD = sdio_instance_params[sdio_number].sdio_normal_interrupt_status;

    /* Read from error interrupt status register */
    sdio_instance_params[sdio_number].sdio_error_interrupt_status = base_address->reg_errorintrsts.WORD;
    base_address->reg_errorintrsts.WORD = sdio_instance_params[sdio_number].sdio_error_interrupt_status;

    /* If card inserted interrupt - re-enable the external clock and bus power */
    if (sdio_instance_params[sdio_number].sdio_normal_interrupt_status & SD_CARD_INSERTED)
    {
        base_address->reg_clockcontrol.BIT.clkctrl_sdclkena = 1;
        base_address->reg_powercontrol.BIT.pwrctrl_sdbuspower = 1;
    }

    /* Call the insert/eject callback function if card inserted/ejected is detected */
    if (((void *) 0 != sdio_instance_params[sdio_number].sdio_insert_eject_callback)
            && (sdio_instance_params[sdio_number].sdio_normal_interrupt_status & (SD_CARD_INSERTED | SD_CARD_REMOVED)))
    {
        (sdio_instance_params[sdio_number].sdio_insert_eject_callback)(
                sdio_instance_params[sdio_number].sdio_normal_interrupt_status & SD_CARD_INSERTED,
                sdio_instance_params[sdio_number].sdio_normal_interrupt_status & SD_CARD_REMOVED);
    }

    /* Test the transfer has completed or there was an error*/
    if (((void *) 0 != sdio_instance_params[sdio_number].sdio_callback_function)
            && (sdio_instance_params[sdio_number].sdio_normal_interrupt_status & (SD_TRANS_COMPLETE | SD_ERROR)))
    {
        /* inform SDIO driver interface that the SDIO instance is no longer busy */
        sdio_trans_complete(sdio_number);

        /* Call the callback function then reset it */
        (sdio_instance_params[sdio_number].sdio_callback_function)(
                sdio_instance_params[sdio_number].sdio_normal_interrupt_status,
                sdio_instance_params[sdio_number].sdio_error_interrupt_status);
        sdio_instance_params[sdio_number].sdio_callback_function = (void *) 0;
    }

    /* Test the DMA has reached a block gap */
    if (sdio_instance_params[sdio_number].sdio_normal_interrupt_status & (SD_DMA_INT))
    {
        /* Restart transfer */
        uint16_t temp = base_address->reg_sdmasysaddrhi.WORD;
        base_address->reg_sdmasysaddrhi.WORD = temp;
    }
}
/***********************************************************************************************************************
 End of function handle_sdio_interrupt
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_cmd_timer1_callback
 *
 *    Return value:     none
 *
 *    Parameters:       interval_count - The number of times the timer has interrupted
 *
 *    Description:      callback for the timer for a command
 *
 **********************************************************************************************************************/
static void sdio_cmd_timer1_callback (unsigned long interval_count)
{
    if (sdio_cmd_time_count == interval_count)
    {
        SDIO_CMD_TIME_UP = true;
    }
}
/***********************************************************************************************************************
 End of function sdio_cmd_timer1_callback
 **********************************************************************************************************************/
