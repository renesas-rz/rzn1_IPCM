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
 * $Revision: 1242 $
 * $Date: 2019-02-08 15:46:14 +0000 (Fri, 08 Feb 2019) $
 *
 * PROJECT NAME :    RZ/N1 bare metal Drivers
 * FILE         :    r_sdio_rzn1_pl.c
 * Description  :    SDIO control functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_sdio_rzn1_config.h"
#include "r_sdio_rzn1_if.h"
#include "r_sdio_rzn1.h"
#include "mcu_interrupts_if.h"
#include "timer.h"
#include "r_timer_rzn1_if.h"
/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define SDIO_CARD_INIT_WAIT             (100)   /* 100 x 10ms = 1s */
#define SDIO_READ_BLOCK_WAIT            (30000) /* 5 minutes */
#define SDIO_TRANS_COMPLETE_WAIT        (100)

#define ACMD41_BUSY     (0x80000000)    /*Busy bit*/
#define ACMD41_CCS      (0x40000000)
/***********************************************************************************************************************
 * Type defintions
 **********************************************************************************************************************/
/* State of the card by monitoring the sent commands */
typedef enum
{
    CARD_IDLE = 0, /* v Operation mode: Card ID mode v */
    CARD_READY = 1,
    CARD_IDENTIFICATION = 2,
    CARD_STAND_BY = 3, /* v Operation mode: Data Transfer mode v */
    CARD_TRANSFER = 4,
    CARD_TRANSMITTING = 5,
    CARD_RECEIVING = 6,
    CARD_PROGRAMMING = 7,
    CARD_DISCONNECT = 8,
    CARD_INACTIVE = -1, /* Operation mode: Inactive mode */
} SDIO_CARD_STATES;

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static bool SDIO_TIME_UP;
static bool SDIO_CARD_PARAMS_OBTAINED = true;
static uint32_t sdio_time_count;

#ifdef CORE_CA7
UNCACHED_BUFFER static SDIO_CARD_PARAMETERS sdio_card_params[MAX_SDIO_INSTANCES];
UNCACHED_BUFFER static SDIO_CARD_TYPE sdio_card_type[MAX_SDIO_INSTANCES];
#else
static SDIO_CARD_PARAMETERS sdio_card_params[MAX_SDIO_INSTANCES];
static SDIO_CARD_TYPE sdio_card_type[MAX_SDIO_INSTANCES];
#endif

/***********************************************************************************************************************
 * Local functions
 **********************************************************************************************************************/
static void sdio_timer1_callback (unsigned long interval_count);
static ER_RET sdio_check_r1_response_err (uint32_t response);
static SDIO_CARD_VERSION sdio_get_sd_version (uint32_t SCR);
static ER_RET sdio_goto_state (uint8_t SDIO_number, SDIO_CARD_STATES state);
static ER_RET sdio_get_card_status (uint8_t SDIO_number, SDIO_CARD_STATES *current_state);
static ER_RET sdio_get_scr (uint8_t SDIO_number);
static ER_RET sdio_get_csd (uint8_t SDIO_number);

static void reorder_bytes_in_register (uint32_t *reg);

/***********************************************************************************************************************
 *
 *    Function:         sdio_get_card_status
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - The Reesponse of the last command
 *                      current_state - The current state of the card
 *
 *    Description:      Returns the current state of the card
 *
 **********************************************************************************************************************/
static ER_RET sdio_get_card_status (uint8_t SDIO_number, SDIO_CARD_STATES *current_state)
{
    ER_RET ret_val = ER_OK;
    uint32_t response;
    uint8_t state;
    SDIO_COMMAND cmd =
    { .command_index = SD_STATUS, .argument = sdio_card_params[SDIO_number].RCA, .response_type = SDIO_RESPONSE_R1,
            .command_type = SDIO_CMD_NON_DATA, .command_data = 0, };

    /* Send CMD13 */
    if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
    {
        /* Get the response */
        sdio_get_response(SDIO_number, cmd.response_type, &response);

        /* Get the card state */
        state = response >> 9; /*Card status is stored in bits [39:8], only first 7 bits of the response are stored in the state variable*/
        if (15 == state)
        {
            /* Card is an SDIO card */
            sdio_card_type[SDIO_number] = SDIO;
        }
        else if (state < 9)
        {
            *current_state = (SDIO_CARD_STATES) state;
        }
        else
        {
            ;
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_get_card_status
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_check_r1_response_err
 *
 *    Return value:     Error status.
 *
 *    Parameters:       response - The Reesponse of the last command
 *
 *    Description:      Returns the relative card address generated by the card
 *
 **********************************************************************************************************************/
static ER_RET sdio_check_r1_response_err (uint32_t response)
{
    ER_RET ret_val = ER_OK;

    if (response & R1_ERROR_BITS_MASK) /* Error bits of R1 response */
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_check_r1_response_err
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_send_acmd
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      command - parameters required for the command.
 *
 *    Description:      Sends an application specific command to the card.
 *
 **********************************************************************************************************************/
ER_RET sdio_send_acmd (uint8_t SDIO_number, SDIO_COMMAND *command)
{
    ER_RET ret_val = ER_OK;
    uint32_t response;
    SDIO_COMMAND cmd =
    { .command_index = APP_CMD, .argument = sdio_card_params[SDIO_number].RCA, .response_type = SDIO_RESPONSE_R1,
            .command_type = SDIO_CMD_NON_DATA, .command_data = 0, };

    /* Send CMD55 */
    if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
    {
        /* Check for response error */
        sdio_get_response(SDIO_number, cmd.response_type, &response);
        if (ER_OK == (ret_val = sdio_check_r1_response_err(response)))
        {
            /* Send CMDxx */
            ret_val = sdio_send_cmd(SDIO_number, command);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_send_acmd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_get_sd_version
 *
 *    Return value:     SDIO_CARD_VERSION.
 *
 *    Parameters:       SCR - The SD Config Register value
 *
 *    Description:      Returns the relative card address generated by the card
 *
 **********************************************************************************************************************/
static SDIO_CARD_VERSION sdio_get_sd_version (uint32_t SCR)
{
    uint8_t sd_spec = (SCR >> 24) & 0x0F;
    uint8_t sd_specx = (SCR >> 6) & 0x0F;
    uint8_t sd_spec3 = (SCR >> 15) & 0x01;
    uint8_t sd_spec4 = (SCR >> 10) & 0x01;
    SDIO_CARD_VERSION version;

    /* according to the table in the sd simplified spec */
    switch (sd_spec)
    {
        case 0:
            version = Version_1_0;
        break;
        case 1:
            version = Version_1_1;
        break;
        case 2:
            if (0 == sd_spec3)
            {
                version = Version_2;
            }
            else
            {
                switch (sd_specx)
                {
                    case 2:
                        version = Version_6;
                    break;
                    case 1:
                        version = Version_5;
                    break;
                    case 0:
                        if (0 == sd_spec4)
                        {
                            version = Version_3;
                        }
                        else
                        {
                            version = Version_4;
                        }
                    break;
                    default:
                        version = Version_Unknown;
                }
            }
        break;
        default:
            version = Version_Unknown;
    }

    return version;
}
/***********************************************************************************************************************
 End of function sdio_get_sd_version
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_get_scr
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      SCR - SD Config register
 *
 *    Description:      Returns the SD Config register of the card
 *
 **********************************************************************************************************************/
static ER_RET sdio_get_scr (uint8_t SDIO_number)
{
    ER_RET ret_val = ER_OK;
    uint16_t block_size = 8;
    SDIO_COMMAND cmd =
    { .command_index = SET_BLOCKLEN, .argument = block_size, .response_type = SDIO_RESPONSE_R1, .command_type = SDIO_CMD_NON_DATA,
            .command_data.buffer = &sdio_card_params[SDIO_number].SCR[0], /* Store transfered data in the SCR array */
            .command_data.block_count = 1, .command_data.direction = SDIO_READ, };

    /* Enter transfer state */
    if (ER_OK == (ret_val = sdio_goto_state(SDIO_number, CARD_TRANSFER)))
    {
        /* Send CMD16 to set the block size */
        if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
        {
            /* Set up transfer config */
            if (ER_OK == (ret_val = sdio_set_trans_config(SDIO_number, cmd.command_data, block_size)))
            {
                /* Send ACMD51 to get the SCR */
                cmd.command_index = SEND_SCR;
                cmd.argument = 0;
                cmd.command_type = SDIO_CMD_DATA;
                if (ER_OK == (ret_val = sdio_send_acmd(SDIO_number, &cmd)))
                {
                    /* Wait for transfer complete interrupt */
                    ret_val = sdio_wait_for_interrupt(SDIO_number,
                    SDIO_TRANS_COMPLETE_WAIT, SD_TRANS_COMPLETE);

                    /* Reorder SCR because coming from the DAT line, according to the SD spec,
                     the "LSB is sent first" This is the byte with the lowest memory
                     address in the transfer. So in the SCR register, this is the MSB*/
                    reorder_bytes_in_register( &sdio_card_params[SDIO_number].SCR[0]);
                    reorder_bytes_in_register( &sdio_card_params[SDIO_number].SCR[1]);
                }
            }
        }
    }

    if (ER_OK == ret_val)
    {
        sdio_card_params[SDIO_number].Card_Version = sdio_get_sd_version(sdio_card_params[SDIO_number].SCR[0]);
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_get_scr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         SDIO_Get_CSD
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      CSD - Card Specific Data register
 *
 *    Description:      Returns the Card Specific Data register of the card
 *
 **********************************************************************************************************************/
static ER_RET sdio_get_csd (uint8_t SDIO_number)
{
    ER_RET ret_val = ER_OK;
    SDIO_COMMAND cmd =
    { .command_index = SEND_CSD, .argument = sdio_card_params[SDIO_number].RCA, .response_type = SDIO_RESPONSE_R2,
            .command_type = SDIO_CMD_NON_DATA, };

    /* Enter stand-by state */
    if (ER_OK == (ret_val = sdio_goto_state(SDIO_number, CARD_STAND_BY)))
    {
        /* Send CMD9 to get the CSD reg */
        if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
        {
            /* Save CSD */
            sdio_get_response(SDIO_number, cmd.response_type, sdio_card_params[SDIO_number].CSD);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_get_csd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_initialise_card_sd
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *
 *    Description:      Sends a sequence of SD protocol commands to initialise the card.
 *
 **********************************************************************************************************************/
ER_RET sdio_initialise_card_sd (uint8_t SDIO_number)
{
    ER_RET ret_val = ER_SYS;
    SDIO_TIME_UP = false;
    uint32_t response;
    SDIO_COMMAND cmd =
    { .command_index = GO_IDLE_STATE, .argument = 0, .response_type = SDIO_RESPONSE_NONE, .command_type = SDIO_CMD_NON_DATA,
            .command_data = 0, };

    /* Give enough time for the SD card to initialise internal states (~74 clocks) */
    systimer_delay(0x11FFFF);

    /* Initialise timer */
    timer1_subtimer_init(2, TIMER_TIME_BASE_1MHz);

    /* Put card in idle state */
    sdio_send_cmd(SDIO_number, &cmd);

    /* Check Operating Conditions with CMD8 */
    cmd.command_index = SEND_IF_COND;
    cmd.argument = 0x01AA;
    cmd.response_type = SDIO_RESPONSE_R7;
    if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
    {
        /* Check response */
        sdio_get_response(SDIO_number, cmd.response_type, &response);
        if (cmd.argument == response)
        {
            /* Send "Inquiry ACMD41" */
            cmd.command_index = APP_SEND_OP_COND;
            cmd.argument = 0;
            cmd.response_type = SDIO_RESPONSE_R3;
            if (ER_OK == (ret_val = sdio_send_acmd(SDIO_number, &cmd)))
            {
                /* Store response for first ACMD41 argument */
                sdio_get_response(SDIO_number, cmd.response_type, &response);
                cmd.argument = response | ACMD41_CCS; /* Start up as SDHC/SDXC */

                /* Register callback and start timer */
                SDIO_TIME_UP = false;
                timer1_subtimer_set_callback(2, &sdio_timer1_callback);
                timer1_subtimer_start(2, SDIO_CARD_INIT_WAIT);

                /* Send "First ACMD41" for 1 second or until busy bit is set to 1 */
                while (( !(sdio_card_params[SDIO_number].OCR & ACMD41_BUSY)) && ( !SDIO_TIME_UP))
                {
                    if (ER_OK != (ret_val = sdio_send_acmd(SDIO_number, &cmd)))
                    {
                        break;
                    }
                    sdio_get_response(SDIO_number, cmd.response_type, &sdio_card_params[SDIO_number].OCR);
                }

                if (ER_OK == ret_val)
                {
                    /* Check Card Capacity Status */
                    if (sdio_card_params[SDIO_number].OCR & ACMD41_CCS)
                    {
                        sdio_card_type[SDIO_number] = SDHC_SDXC; /* OR SDXC */
                    }
                    else
                    {
                        sdio_card_type[SDIO_number] = SD;
                    }

                    /* Send CMD2 to obtain CID */
                    cmd.command_index = ALL_SEND_CID;
                    cmd.argument = 0;
                    cmd.response_type = SDIO_RESPONSE_R2;
                    if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
                    {
                        /* Save CID */
                        sdio_get_response(SDIO_number, cmd.response_type, &sdio_card_params[SDIO_number].CID[0]);

                        /* Send CMD 3 to obtain RCA and send card to stand-by state */
                        cmd.command_index = SEND_RELATIVE_ADDR;
                        cmd.argument = 0;
                        cmd.response_type = SDIO_RESPONSE_R6;
                        if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
                        {
                            /* Save RCA */
                            sdio_get_response(SDIO_number, cmd.response_type, &sdio_card_params[SDIO_number].RCA);

                            /* Get CSD */
                            if (ER_OK != (ret_val = sdio_get_csd(SDIO_number)))
                            {
                                SDIO_CARD_PARAMS_OBTAINED = false;
                            }

                            /* Get SCR */
                            if (ER_OK != (ret_val = sdio_get_scr(SDIO_number)))
                            {
                                SDIO_CARD_PARAMS_OBTAINED = false;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            ret_val = ER_SYS;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_initialise_card_sd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_set_bus_width
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      bus_width - The desired width of the data bus
 *
 *    Description:      Sets the data bus width
 *
 **********************************************************************************************************************/
ER_RET sdio_set_bus_width (uint8_t SDIO_number, SDIO_TRANS_WIDTH bus_width)
{
    ER_RET ret_val = ER_OK;
    SDIO_COMMAND cmd =
    { .command_index = SET_BUS_WIDTH, .argument = 0, .response_type = SDIO_RESPONSE_R1, .command_type = SDIO_CMD_NON_DATA, };

    switch (bus_width)
    {
        case SDIO_WIDTH_1_BIT:
        break;
        case SDIO_WIDTH_4_BIT:
            cmd.argument = 0x02;
        break;
        case SDIO_WIDTH_8_BIT:
            if (MMC != sdio_card_type[SDIO_number])
            {
                ret_val = ER_INVAL;
            }
            else
            {
                /* 8-bit command routine */
                ;
            }
        break;
        default:
        break;
    }

    /* Check bus width is allowed from SCR register */
    if ((ER_OK == ret_val) && ((sdio_card_params[SDIO_number].SCR[0] >> (16 + cmd.argument)) & 0x01))
    {
        /* Go to stand-by state */
        if (ER_OK == (ret_val = sdio_goto_state(SDIO_number, CARD_TRANSFER)))
        {
            /* send ACMD6 to set the bus width */
            if (ER_OK == (ret_val = sdio_send_acmd(SDIO_number, &cmd)))
            {
                /* Set HC to operate with the same bus width */
                ret_val = sdio_set_hc_bus_width(SDIO_number, bus_width);
            }
        }
    }
    else
    {
        ret_val = ER_INVAL;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_set_bus_width
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_read
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      trans_control - read parameters
 *                                      (block size, block count, data store location, )
 *
 *    Description:      Sends a sequence of SD protocol commands to read from the card.
 *
 **********************************************************************************************************************/
ER_RET sdio_read (uint8_t SDIO_number, SDIO_TRANS_CTRL trans_control, uint32_t start_address)
{
    ER_RET ret_val = ER_OK;
    uint16_t block_size = 512;
    SDIO_COMMAND cmd =
            { .command_index = SET_BLOCKLEN, .argument = block_size, .response_type = SDIO_RESPONSE_R1, .command_type =
                    SDIO_CMD_NON_DATA, };

    /* Fix data direction to read */
    trans_control.direction = SDIO_READ;

    /* Enter transfer state */
    if (ER_OK == (ret_val = sdio_goto_state(SDIO_number, CARD_TRANSFER)))
    {
        /* Send CMD16 to set the block size */
        if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
        {
            if (ER_OK == (ret_val = sdio_set_trans_config(SDIO_number, trans_control, block_size)))
            {
                /* Test to see if single or multiblock transfer */
                if (0x01 < trans_control.block_count)
                {
                    /* Send CMD18 for multiple block transfer */
                    cmd.command_index = READ_MULTIPLE_BLOCK;
                }
                else
                {
                    /* Send CMD17 for single block transfer */
                    cmd.command_index = READ_SINGLE_BLOCK;
                }
                cmd.argument = start_address;
                cmd.command_type = SDIO_CMD_DATA;
                ret_val = sdio_send_cmd(SDIO_number, &cmd);
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         SDIO_Write
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      trans_control - write parameters
 *                                      (block size, block count, data store location, )
 *
 *    Description:      Sends a sequence of SD protocol commands to write to the card.
 *
 **********************************************************************************************************************/
ER_RET sdio_write (uint8_t SDIO_number, SDIO_TRANS_CTRL trans_control, uint32_t start_address)
{
    ER_RET ret_val = ER_OK;
    uint16_t block_size = 512;
    bool write_protected = false;
    SDIO_COMMAND cmd =
            { .command_index = SET_BLOCKLEN, .argument = block_size, .response_type = SDIO_RESPONSE_R1, .command_type =
                    SDIO_CMD_NON_DATA, };

    /* Fix data direction to write */
    trans_control.direction = SDIO_WRITE;

    /* Check mechanical write protect switch on the card */
    sdio_get_write_protection(SDIO_number, &write_protected);
    if (false == write_protected)
    {
        /* Enter transfer state */
        if (ER_OK == (ret_val = sdio_goto_state(SDIO_number, CARD_TRANSFER)))
        {
            /* Send CMD16 to set the block size */
            if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
            {
                if (ER_OK == (ret_val = sdio_set_trans_config(SDIO_number, trans_control, block_size)))
                {
                    /* Test to see if single or multiblock transfer */
                    if (0x01 < trans_control.block_count)
                    {
                        /* Send CMD25 for multiple block transfer */
                        cmd.command_index = WRITE_MULTIPLE_BLOCK;
                    }
                    else
                    {
                        /* Send CMD24 for single block transfer */
                        cmd.command_index = WRITE_BLOCK;
                    }
                    cmd.argument = start_address;
                    cmd.command_type = SDIO_CMD_DATA;
                    ret_val = sdio_send_cmd(SDIO_number, &cmd);
                }
            }
        }
    }
    else
    {
        ret_val = ER_INVAL;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_get_card_params
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      parameters - The collected card parameters
 *
 *    Description:      Returns the relative card address generated by the card
 *
 **********************************************************************************************************************/
ER_RET sdio_get_card_params (uint8_t SDIO_number, SDIO_CARD_PARAMETERS *parameters)
{
    ER_RET ret_val = ER_OK;

    *parameters = sdio_card_params[SDIO_number];

    if (false == SDIO_CARD_PARAMS_OBTAINED)
    {
        ret_val = ER_SYS;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_get_card_params
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_clear_card_params
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *
 *    Description:      Clears the stored parameters for the card
 *
 **********************************************************************************************************************/
void sdio_clear_card_params (uint8_t SDIO_number)
{
    sdio_card_params[SDIO_number].CID[0] = 0;
    sdio_card_params[SDIO_number].CID[1] = 0;
    sdio_card_params[SDIO_number].CID[2] = 0;
    sdio_card_params[SDIO_number].CID[3] = 0;

    sdio_card_params[SDIO_number].CSD[0] = 0;
    sdio_card_params[SDIO_number].CSD[1] = 0;
    sdio_card_params[SDIO_number].CSD[2] = 0;
    sdio_card_params[SDIO_number].CSD[3] = 0;

    sdio_card_params[SDIO_number].OCR = 0;

    sdio_card_params[SDIO_number].RCA = 0;

    sdio_card_params[SDIO_number].SCR[0] = 0;
    sdio_card_params[SDIO_number].SCR[1] = 0;
}
/***********************************************************************************************************************
 End of function sdio_clear_card_params
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_goto_state
 *
 *    Return value:     Error status.
 *
 *    Parameters:       SDIO_number - SDIO number
 *                      state - The desired state for the card to go to
 *
 *    Description:      Sends the required command(s) for the card to reach the
 *                      desired state from the current state
 *
 **********************************************************************************************************************/
static ER_RET sdio_goto_state (uint8_t SDIO_number, SDIO_CARD_STATES state)
{
    ER_RET ret_val = ER_OK;
    SDIO_CARD_STATES current_state;
    SDIO_COMMAND cmd =
    { .command_index = GO_IDLE_STATE, .argument = 0, .response_type = SDIO_RESPONSE_NONE, .command_type = SDIO_CMD_NON_DATA,
            .command_data = 0, };

    if (ER_OK == (ret_val = sdio_get_card_status(SDIO_number, &current_state)))
    {
        /* Ensure the current state belongs to the data transfer operation mode set
         and the desired state is not a state reached due to a transfer */
        if ((CARD_STAND_BY > current_state) || (CARD_DISCONNECT == state) || (CARD_PROGRAMMING == state)
                || (CARD_TRANSMITTING == state) || (CARD_RECEIVING == state))
        {
            ret_val = ER_INVAL;
        }
        else
        {
            switch (state)
            {
                case CARD_TRANSFER:
                    if (CARD_STAND_BY == current_state)
                    {
                        /* Send command 7 to enter transfer state */
                        cmd.command_index = SELECT_DESELECT_CARD;
                        cmd.argument = sdio_card_params[SDIO_number].RCA;
                        cmd.response_type = SDIO_RESPONSE_R1b;

                        if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
                        {
                            /* Check desired state achieved */
                            if (ER_OK == (ret_val = sdio_get_card_status(SDIO_number, &current_state)))
                            {
                                if (CARD_TRANSFER != current_state)
                                {
                                    ret_val = ER_SYS;
                                }
                            }
                        }
                    }
                    else if (CARD_TRANSFER == current_state)
                    {
                        /* NOP */
                        ;
                    }
                    else if (CARD_TRANSMITTING == current_state)
                    {
                        /* Send command 12 to enter transfer state */
                        cmd.command_index = STOP_TRANSMISSION;
                        cmd.argument = 0;
                        cmd.response_type = SDIO_RESPONSE_R1b;

                        if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
                        {
                            /* Check desired state achieved */
                            if (ER_OK == (ret_val = sdio_get_card_status(SDIO_number, &current_state)))
                            {
                                if (CARD_TRANSFER != current_state)
                                {
                                    ret_val = ER_SYS;
                                }
                            }
                        }
                    }
                    else
                    {
                        ret_val = ER_INVAL; /* Not yet implemented */

                        /* Could reinitialise card? */
                    }

                    /* From sending data & programming - needs operation complete */
                break;
                case CARD_STAND_BY:
                    if (CARD_TRANSFER == current_state)
                    {
                        /* Send command 7 to enter transfer state */
                        cmd.command_index = SELECT_DESELECT_CARD;
                        cmd.argument = 0; /* RCA = 0 to deselect all cards */
                        cmd.response_type = SDIO_RESPONSE_NONE; /* Response R1b only from selected card, therefore no response from deselected card */

                        if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, &cmd)))
                        {
                            /* Check desired state achieved */
                            if (ER_OK == (ret_val = sdio_get_card_status(SDIO_number, &current_state)))
                            {
                                if (CARD_STAND_BY != current_state)
                                {
                                    ret_val = ER_SYS;
                                }
                            }
                        }
                    }
                    else if (CARD_STAND_BY == current_state)
                    {
                        /* NOP */
                        ;
                    }
                    else
                    {
                        ret_val = ER_INVAL; /* Not yet implemented */

                        /* Could reinitialise card? */
                    }

                    /* From Disconnect - needs operation complete */
                break;
                default:
                    ret_val = ER_INVAL;
            }
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function sdio_goto_state
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         reorder_bytes_in_register
 *
 *    Return value:     none
 *
 *    Parameters:       reg - The address of the register to be reordered
 *
 *    Description:      Reorders a 32-bit register such that the LSB becomes
 *                      the MSB and vice versa.
 *
 **********************************************************************************************************************/
static void reorder_bytes_in_register (uint32_t *reg)
{
    uint32_t new_val = 0;
    uint8_t i;

    for (i = 0; i < 4; i++)
    {
        new_val |= (((( *reg) >> (i * 8)) & 0xFF) << (24 - (8 * i)));
    }
    *reg = new_val;
}
/***********************************************************************************************************************
 End of function reorder_bytes_in_register
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         sdio_timer1_callback
 *
 *    Return value:     none
 *
 *    Parameters:       interval_count - The number of times the timer has interrupted
 *
 *    Description:      callback for the timer for a process
 *
 **********************************************************************************************************************/
static void sdio_timer1_callback (unsigned long interval_count)
{
    if (sdio_time_count == interval_count)
    {
        SDIO_TIME_UP = true;
    }
}
/***********************************************************************************************************************
 End of function sdio_timer1_callback
 **********************************************************************************************************************/
