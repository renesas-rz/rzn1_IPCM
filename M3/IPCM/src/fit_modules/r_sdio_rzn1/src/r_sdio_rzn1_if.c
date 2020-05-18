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
 * FILE                 :    r_sdio_rzn1_if.c
 * Description    :    SDIO control interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_sdio_rzn1_config.h"
#include "r_sdio_rzn1_if.h"
#include "r_sdio_rzn1.h"
#include "r_sdio_rzn1_pl.h"

/***********************************************************************************************************************
 Data structures
 **********************************************************************************************************************/
static SDIO_STATE sdio_instance_state[MAX_SDIO_INSTANCES];

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static bool sdio_card_initialised[MAX_SDIO_INSTANCES];

/***********************************************************************************************************************
 *
 *  Function:       R_SDIO_GetVersion
 *
 *  Return value:   None.
 *
 *  Parameters:     None.
 *
 *  Description:    Returns the SDIO driver version number
 *
 **********************************************************************************************************************/

void R_SDIO_GetVersion (void *buf)
{
    sdio_getdrivernumber((uint8_t *) buf);
}
/***********************************************************************************************************************
 End of function R_SDIO_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:           R_SDIO_Init
 *
 *    Return value:       Error status
 *
 *    Parameters:         None.
 *
 *    Description:        Initialises the SDIO IP and instance states
 *
 **********************************************************************************************************************/
void R_SDIO_Init (void)
{
    uint8_t instance;

    for (instance = 0; instance < MAX_SDIO_INSTANCES; instance++)
    {
        sdio_instance_state[instance] = SDIO_STATE_CLOSED;
        sdio_card_initialised[instance] = false;
    }

    sdio_driver_init();
}
/***********************************************************************************************************************
 End of function R_SDIO_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:           R_SDIO_Open
 *
 *    Return value:       SDIO channel to open
 *
 *    Parameters:         SDIO_number - Which SDIO controller to configure.
 *
 *    Description:        Opens an SDIO controller
 *
 **********************************************************************************************************************/
ER_RET R_SDIO_Open (uint8_t SDIO_number)
{
    ER_RET ret_val = ER_OK;

    if (SDIO_STATE_CLOSED == sdio_instance_state[SDIO_number])
    {
        ret_val = sdio_open(SDIO_number);
        if (ER_OK == ret_val)
        {
            sdio_instance_state[SDIO_number] = SDIO_STATE_OPEN;
        }
    }
    else
    {
        ret_val = ER_INVAL;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SDIO_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:         R_SDIO_Close
 *
 *    Return value:     Error status
 *
 *    Parameters:       SDIO_number - Which SDIO controller to configure.
 *
 *    Description:      Closes a SDIO controller
 *
 **********************************************************************************************************************/
ER_RET R_SDIO_Close (uint8_t SDIO_number)
{
    ER_RET ret_val = ER_OK;

    if (SDIO_number < MAX_SDIO_INSTANCES)
    {
        if (SDIO_STATE_BUSY == sdio_instance_state[SDIO_number])
        {
            ret_val = ER_INVAL;
        }
        else
        {
            sdio_close(SDIO_number);
            sdio_instance_state[SDIO_number] = SDIO_STATE_CLOSED;
            sdio_clear_card_params(SDIO_number);
            sdio_card_initialised[SDIO_number] = false;
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SDIO_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:           R_SDIO_Control
 *
 *    Return value:       Error status
 *
 *    Parameters:         SDIO_number - Which SDIO controller to configure.
 *                        control - Which control action to implement.
 *                        ctrl_param - The control parameter that is used along with the
 *                                    control action to configure the controller instance
 *                                    a certain way.
 *
 *    Description:        Controls an SDIO instance
 *
 **********************************************************************************************************************/
ER_RET R_SDIO_Control (uint8_t SDIO_number, SDIO_CONTROL_REQUEST control_request, void *control)
{
    ER_RET ret_val = ER_OK;

    /* Check SDIO instance is valid */
    if (SDIO_number < MAX_SDIO_INSTANCES)
    {
        /* Check the SDIO instance is open */
        if (SDIO_STATE_OPEN == sdio_instance_state[SDIO_number])
        {
            switch (control_request)
            {
                case SDIO_CONTROL_SEND_CMD:
                    if (ER_OK == (ret_val = sdio_set_trans_config(SDIO_number, ((SDIO_COMMAND *) control)->command_data,
                                    512)))
                    {
                        if (ER_OK == (ret_val = sdio_send_cmd(SDIO_number, (SDIO_COMMAND *) control)))
                        {
                            uint32_t *resp_adr = &((SDIO_COMMAND *) control)->response[0];

                            /* Clear previous response content */
                            *resp_adr++ = 0;
                            *resp_adr++ = 0;
                            *resp_adr++ = 0;
                            *resp_adr++ = 0;

                            /* Get response */
                            sdio_get_response(SDIO_number, ((SDIO_COMMAND *) control)->response_type,
                                    &((SDIO_COMMAND *) control)->response[0]);

                            if (0 == ((SDIO_COMMAND *) control)->command_index)
                            {
                                sdio_card_initialised[SDIO_number] = false;
                            }
                        }
                    }
                break;
                case SDIO_CONTROL_SEND_APP_CMD:
                    if (ER_OK == (ret_val = sdio_set_trans_config(SDIO_number, ((SDIO_COMMAND *) control)->command_data,
                                    512)))
                    {
                        if (ER_OK == (ret_val = sdio_send_acmd(SDIO_number, (SDIO_COMMAND *) control)))
                        {
                            uint32_t *resp_adr = &((SDIO_COMMAND *) control)->response[0];

                            /* Clear previous response content */
                            *resp_adr++ = 0;
                            *resp_adr++ = 0;
                            *resp_adr++ = 0;
                            *resp_adr++ = 0;

                            /* Get response */
                            sdio_get_response(SDIO_number, ((SDIO_COMMAND *) control)->response_type,
                                    &((SDIO_COMMAND *) control)->response[0]);
                        }
                    }
                break;
                case SDIO_CONTROL_SET_CLK_DIV:
                    ret_val = sdio_set_clock_div(SDIO_number, *(SDIO_CLK_DIV *) control);
                break;
                case SDIO_CONTROL_SET_INSERT_EJECT_CALLBACK:
                    ret_val = sdio_register_call_back(SDIO_number, (sdio_insert_eject_callback) control);
                break;
                case SDIO_CONTROL_SD_INIT:
                    ret_val = sdio_initialise_card_sd(SDIO_number);
                    if (ER_OK == ret_val)
                    {
                        sdio_card_initialised[SDIO_number] = true;
                    }
                break;
                case SDIO_CONTROL_SET_BUS_WIDTH:
                    if (true != sdio_card_initialised[SDIO_number])
                    {
                        ret_val = ER_INVAL;
                    }
                    else
                    {
                        ret_val = sdio_set_bus_width(SDIO_number, *(SDIO_TRANS_WIDTH *) control);
                    }
                break;
                case SDIO_CONTROL_GET_CARD_PARAMS:
                    if (true != sdio_card_initialised[SDIO_number])
                    {
                        ret_val = ER_INVAL;
                    }
                    else
                    {
                        ret_val = sdio_get_card_params(SDIO_number, (SDIO_CARD_PARAMETERS *) control);
                    }
                break;
                default:
                    ret_val = ER_PARAM;
            }
        }
        else
        {
            ret_val = ER_INVAL;
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SDIO_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:          R_SDIO_Read
 *
 *    Return value:      Error status
 *
 *    Parameters:        SDIO_number - Which SDIO instance to read from.
 *                       trans_control - transfer control of the read transfer.
 *                       start_address - The address in the card to start reading from
 *
 *    Description:       Reads data from a Card
 *
 **********************************************************************************************************************/
ER_RET R_SDIO_Read (uint8_t SDIO_number, SDIO_TRANS_CTRL trans_control, uint32_t start_address)
{
    ER_RET ret_val = ER_OK;

    if ((SDIO_number >= MAX_SDIO_INSTANCES) || ((void *) 0 == trans_control.buffer))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Test card is initialised and not busy */
        if ((false == sdio_card_initialised[SDIO_number]) || (SDIO_STATE_OPEN != sdio_instance_state[SDIO_number]))
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = sdio_read(SDIO_number, trans_control, start_address);

            /* Set channel state to busy */
            if (ER_OK == ret_val)
            {
                sdio_instance_state[SDIO_number] = SDIO_STATE_BUSY;
            }
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SDIO_Read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *    Function:          R_SDIO_Write
 *
 *    Return value:      Error status
 *
 *    Parameters:        SDIO_number - Which SDIO instance to read from.
 *                       trans_control - transfer control of the write transfer.
 *                       start_address - The address in the card to start writing to
 *
 *    Description:       Writes data to a Card
 *
 **********************************************************************************************************************/
ER_RET R_SDIO_Write (uint8_t SDIO_number, SDIO_TRANS_CTRL trans_control, uint32_t start_address)
{
    ER_RET ret_val = ER_OK;

    if ((SDIO_number >= MAX_SDIO_INSTANCES) || ((void *) 0 == trans_control.buffer))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* Test card is initialised and not busy */
        if ((false == sdio_card_initialised[SDIO_number]) || (SDIO_STATE_OPEN != sdio_instance_state[SDIO_number]))
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = sdio_write(SDIO_number, trans_control, start_address);

            /* Set channel state to busy */
            if (ER_OK == ret_val)
            {
                sdio_instance_state[SDIO_number] = SDIO_STATE_BUSY;
            }
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_SDIO_Write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       sdio_trans_complete
 *
 *  Return value:   void
 *
 *  Parameters:     SDIO_number - SDIO instance number
 *
 *  Description:    NON-interface function so parameters not required to be checked.
 *                  Called when a transfer has completed so
 *                  SDIO instance state can be updated.
 *
 **********************************************************************************************************************/
void sdio_trans_complete (uint8_t SDIO_number)
{
    if (SDIO_STATE_BUSY == sdio_instance_state[SDIO_number])
    {
        sdio_instance_state[SDIO_number] = SDIO_STATE_OPEN;
    }
    return;
}
/***********************************************************************************************************************
 End of function sdio_trans_complete
 **********************************************************************************************************************/
