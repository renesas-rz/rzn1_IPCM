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
 * $Revision: 1344 $
 * $Date: 2019-03-07 15:21:15 +0000 (Thu, 07 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_gmac_rzn1_if.c
 * Description  :  GMAC driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include "r_gmac_rzn1_if.h"
#include "r_gmac_rzn1.h"
#include "r_phy_rzn1.h"

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static GMAC_STATE gmac_state[2];

/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_GMAC_GetVersion
 *
 *  Return value:   Driver version
 *
 *  Parameters:     buf - Pointer to buffer for version information.
 *
 *  Description:    Returns the version of this driver
 *
 **********************************************************************************************************************/
void R_GMAC_GetVersion (void *buf)
{
    /* These version macros are defined in r_gmac_rzn1_if.h. */
    ((uint8_t *) buf)[1] = (uint8_t)GMAC_RZN1_VERSION_MAJOR;
    ((uint8_t *) buf)[0] = (uint8_t)GMAC_RZN1_VERSION_MINOR;
}
/***********************************************************************************************************************
 End of function R_GMAC_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_GMAC_Init
 *
 *  Return value:   Error value.
 *
 *  Parameters:     None.
 *
 *  Description:    Initialises GMAC channels
 *
 **********************************************************************************************************************/
ER_RET R_GMAC_Init (void)
{
    ER_RET ret_val = ER_SYS;
    uint8_t chan_num = 0;

    /*Set initial conditions*/
    for (chan_num = 0; chan_num < MAX_GMAC; chan_num++)
    {
        gmac_state[chan_num] = GMAC_STATE_CLOSED;
    }

    ret_val = gmac_init();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GMAC_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_GMAC_Uninit
 *
 *  Return value:   Error value
 *
 *  Parameters:     None.
 *
 *  Description:    Disables GMAC.
 *
 **********************************************************************************************************************/
ER_RET R_GMAC_Uninit (void)
{
    ER_RET ret_val = ER_OK;
    uint8_t chan_num;
    /* Clear internal parameters */
    for (chan_num = 0; chan_num < MAX_GMAC; chan_num++)
    {
        if (gmac_state[chan_num] != GMAC_STATE_CLOSED)
        {
            ret_val = ER_SYS;
        }
    }

    if (ret_val == ER_OK)
    {
        gmac_uninit();
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GMAC_Uninit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_GMAC_Open
 *
 *  Return value:   Error value.
 *
 *  Parameters:     data - Structure that stores all information about the
 *                         channel
 *  Description:    Opens GMAC channels and sets it to listen for upcoming data
 *
 **********************************************************************************************************************/
ER_RET R_GMAC_Open (const gmac_transfer_data *data)
{
    ER_RET ret_val = ER_OK;

#if GMAC_CFG_PARAM_CHECKING_ENABLE
    if ((data->chan_num > GMAC_CHAN_2)
            || ((GMAC_CHAN_1 == data->chan_num) && (PORT1 != data->port)))
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        if ((GMAC_STATE_OPEN == gmac_state[data->chan_num]))
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = gmac_open(data);
            gmac_state[data->chan_num] = GMAC_STATE_OPEN;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GMAC_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_GMAC_Close
 *
 *  Return value:   Error value.
 *
 *  Parameters:     data - Structure that stores all information about the
 *                         channel
 *  Description:    Closes GMAC channel.
 *
 **********************************************************************************************************************/
ER_RET R_GMAC_Close (const gmac_transfer_data *data)
{
    ER_RET ret_val = ER_OK;

#if GMAC_CFG_PARAM_CHECKING_ENABLE
    if ((data->chan_num > GMAC_CHAN_2)
            || ((GMAC_CHAN_1 == data->chan_num) && (PORT1 != data->port)))
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        if ((GMAC_STATE_CLOSED == gmac_state[data->chan_num]))
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = gmac_close(data->chan_num, data->port);
            if (ER_OK == ret_val)
            {
                gmac_state[data->chan_num] = GMAC_STATE_CLOSED;
            }
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GMAC_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_GMAC_LinkStatus
 *
 *  Return value:   1 - link is up, 0 - link is down.
 *
 *  Parameters:     port - Port address for which the link is checked
 *
 *  Description:    Retuns the status of the link.
 *
 **********************************************************************************************************************/
uint8_t R_GMAC_LinkStatus (uint8_t port)
{
    uint8_t ret_val;

    if ((PORT4 != port) && (PORT5 != port))
    {
        if ((phy_reg_read(port, 1, 0) & AUTONEG_COMPLETE) && (phy_reg_read(port, 17, 0) & LINK_BIT_1_2_3_PORTS))
        {
            ret_val = 1;
        }
        else
        {
            ret_val = 0;
        }
    }
    else
    {
        if ((phy_read(port, 1) & (LINK_BIT_4_5_PORTS | AUTONEG_COMPLETE)) == (LINK_BIT_4_5_PORTS | AUTONEG_COMPLETE))
        {
            ret_val = 1;
        }
        else
        {
            ret_val = 0;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GMAC_LinkStatus
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_GMAC_Control
 *
 *  Return value:   Error value.
 *
 *  Parameters:     data - Structure that stores all information about the
 *                         channel
 *                  control_request - control request
 *                  control_options - address of a structure dedicated for a
 *                                    certain control request.
 *  Description:    Configures GMAC channel.
 *
 **********************************************************************************************************************/
ER_RET R_GMAC_Control (const gmac_transfer_data *data, gmac_control_state_t control_request, uint32_t control_options)
{
    ER_RET ret_val = ER_OK;

#if GMAC_CFG_PARAM_CHECKING_ENABLE
    if (((data->chan_num > GMAC_CHAN_2)
                    || ((GMAC_CHAN_1 == data->chan_num) && (PORT1 != data->port)))
            || ((0 == control_options) && (SET_SPEED != control_request)))
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        if ((GMAC_STATE_CLOSED == gmac_state[data->chan_num]) && (ETH_MUX_CTRL != control_request) && (REG_CALLBACK != control_request))
        {
            ret_val = ER_INVAL;
        }
        else
        {
            if ( !R_GMAC_LinkStatus(data->port))
            {
                ret_val = ER_INVAL;
            }
            else
            {
                switch (control_request)
                {
                    case (SET_SPEED):
                        ret_val = gmac_set_speed(data->chan_num, data->port, data->mode);
                    break;
                    case (SET_FILTER):
                        ret_val = gmac_filtering_config(data->chan_num, (gmac_filter_config *) control_options);
                    break;
                    case (ETH_MUX_CTRL):
                        eht_protection_control(1);
                        write_eth_reg(SW_MODE_REG, control_options, 0);
                        eht_protection_control(0);
                    break;
                    case (REG_CALLBACK): // $REA Added
                        gmac_register_callback((gmac_callback)control_options);
                    break;
                    default:
                    break;
                }
            }
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GMAC_Control
 **********************************************************************************************************************/

// $REA function added
/***********************************************************************************************************************
 *
 *  Function:       R_GMAC_Read
 *
 *  Return value:   Error value.
 *
 *  Parameters:     chan_num - MAC channel
 *                  p_buf [out]   - Pointer to data buffer
                    p_len [out]   - Pointer to data size
 *  Description:    Reads data.
 *
 **********************************************************************************************************************/
ER_RET R_GMAC_Read (uint8_t chan_num, uint8_t ** p_buf, uint16_t * p_len)
{
    ER_RET ret_val = ER_OK;

#if GMAC_CFG_PARAM_CHECKING_ENABLE
    if (chan_num > GMAC_CHAN_2)
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        if ((GMAC_STATE_CLOSED == gmac_state[chan_num]))
        {
            ret_val = ER_INVAL;
        }
        else
        {
            gmac_read(chan_num, p_buf, p_len);
        }
    }
    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_GMAC_Read
 *
 *  Return value:   Error value.
 *
 *  Parameters:     chan_num - MAC channel
 *                  eth_frame - structure with Ethernet header info
 *  Description:    Sends out data.
 *
 **********************************************************************************************************************/
ER_RET R_GMAC_Write (const gmac_transfer_data *data, const gmac_eth_frame *eth_frame)
{
    ER_RET ret_val = ER_OK;

#if GMAC_CFG_PARAM_CHECKING_ENABLE
    if ((data->chan_num > GMAC_CHAN_2)
            || ((GMAC_CHAN_1 == data->chan_num) && (PORT1 != data->port)))
    {
        ret_val = ER_PARAM;
    }
    else
#endif
    {
        if ((GMAC_STATE_CLOSED == gmac_state[data->chan_num]))
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = gmac_write(data->chan_num, data->port, eth_frame);
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_GMAC_Write
 **********************************************************************************************************************/
