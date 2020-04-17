/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only
 * intended for use with Renesas products. No other uses are authorized. This
 * software is owned by Renesas Electronics Corporation and is protected under
 * all applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
 * LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
 * TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
 * ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
 * FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
 * ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
 * BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software
 * and to discontinue the availability of this software. By using this software,
 * you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 * Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * $Revision: 1312 $
 * $Date: 2019-03-01 11:54:44 +0000 (Fri, 01 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_lcdc_rzn1_if.c
 * Description  :  LCDC driver interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/*
 *****************************************************************************
 * Doxygen Summary block
 **********************************************************************************************************************/
/*!
 * @ingroup LCDC_MODULE RZN1 LCDC Bare Metal Driver
 * @{
 * @file
 * @brief LCDC Bare Metal Driver
 * @details Supports initialisation, configuration and updating TFT LCD Panel
 * @} */
/***********************************************************************************************************************
 * End of Doxygen Summary block
 **********************************************************************************************************************/

/***********************************************************************************************************************
 I N C L U D E
 **********************************************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "r_lcdc_rzn1_config.h"
#include "r_gpio_rzn1_if.h"
#include "r_lcdc_rzn1_if.h"
#include "r_lcdc_rzn1.h"

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static lcdc_port_state_e lcdc_port_state; /* LCDC port state, RZ/N1 has only 1 Port for TFT LCD Panel */

/***********************************************************************************************************************
 * Local function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_LCDC_GetVersion
 **********************************************************************************************************************/
/*!
 * @brief    Gets LCDC bare metal driver version number
 * @details
 * @param    buf - where version number returned
 * @retval   void
 **********************************************************************************************************************/
void R_LCDC_GetVersion (void *buf)
{
    ((uint8_t *) buf)[1] = (uint8_t) LCDC_DRIVER_MAJOR_VERSION_NUMBER;
    ((uint8_t *) buf)[0] = (uint8_t) LCDC_DRIVER_MINOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function R_LCDC_GetVersion
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_LCDC_Init
 **********************************************************************************************************************/
/*!
 * @brief    Initialise LCDC bare metal driver
 * @details  Calls driver function to init LCD controller
 * @param    void
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_LCDC_Init (void)
{
    ER_RET ret_val = ER_OK;

    lcdc_port_state = LCDC_PORT_STATE_CLOSED;

    /* Initialise the LCDC driver */
    ret_val = lcdc_driver_init();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_LCDC_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_LCDC_Uninitialise
 **********************************************************************************************************************/
/*!
 * @brief    Un-Initialise USB bare metal driver
 * @details  Calls driver function to close down LCD controller
 * @param    void
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_LCDC_Uninitialise (void)
{
    ER_RET ret_val = ER_OK;

    /* If LCDC port Open or Busy, Close it */
    if (lcdc_port_state != LCDC_PORT_STATE_CLOSED)
    {
        ret_val = R_LCDC_Close();
    }

    if (ER_OK == ret_val)
    {
        /* Un-initialise the LCDC driver */
        ret_val = lcdc_driver_uninit();
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_LCDC_Uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_TSD_Init
 **********************************************************************************************************************/
/*!
 * @brief    Initialise Touch Screen driver
 * @details  Calls driver function to init touch screen controller
 * @param    gpio_callback - callback function for ts interrupts
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_TSD_Init (gpio_callback ts_int_callback)
{
    ER_RET ret_val = ER_OK;

    /* Initialise the touch screen driver */
    if (lcdc_port_state == LCDC_PORT_STATE_CLOSED)
    {
        /* open ts driver after LCDD initialised and port opened */
        ret_val = ER_INVAL;
    }
    else
    {
        ret_val = tsd_driver_init(ts_int_callback);
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_TSD_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_TSD_Uninitialise
 **********************************************************************************************************************/
/*!
 * @brief    Un-Initialise touch screen driver
 * @details  Calls driver function to close down touch screen controller
 * @param    void
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_TSD_Uninitialise (void)
{
    ER_RET ret_val = ER_OK;

    ret_val = tsd_driver_uninit();

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_TSD_Uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_LCDC_Open
 **********************************************************************************************************************/
/*!
 * @brief    Opens and configures LCDC port
 * @details  Channel parameter not required as 1 LCD port supported
 * @param    port_config - pointer to display configuration
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_LCDC_Open (lcdc_port_config_t *port_config)
{
    ER_RET ret_val = ER_OK;

    if (LCDC_PORT_STATE_CLOSED != lcdc_port_state)
    {
        ret_val = ER_INVAL;
    }
    else
    {
        if (port_config == (void *) 0)
        {
            ret_val = ER_PARAM;
        }
        /* Check parameters before opening LCD port */
        else if ((port_config->bpp != LCDC_DRIVER_BPP_1) && (port_config->bpp != LCDC_DRIVER_BPP_2)
                && (port_config->bpp != LCDC_DRIVER_BPP_4) && (port_config->bpp != LCDC_DRIVER_BPP_8)
                && (port_config->bpp != LCDC_DRIVER_BPP_16) && (port_config->bpp != LCDC_DRIVER_BPP_18)
                && (port_config->bpp != LCDC_DRIVER_BPP_24))
        {
            ret_val = ER_PARAM;
        }
        else
        {
            if (((port_config->bpp == LCDC_DRIVER_BPP_1) || (port_config->bpp == LCDC_DRIVER_BPP_2)
                    || (port_config->bpp == LCDC_DRIVER_BPP_4) || (port_config->bpp == LCDC_DRIVER_BPP_8))
                    && (port_config->palette == (void *) 0))
            {
                ret_val = ER_PARAM;
            }
            else
            {
                if ((port_config->x_res > 4096) || (port_config->y_res > 4096)) /* max supported is XGA */
                {
                    ret_val = ER_PARAM;
                }
            }
        }
    }
    if (ret_val == ER_OK)
    {
        ret_val = lcdc_port_open(port_config);
        if (ER_OK == ret_val)
        {
            lcdc_port_state = LCDC_PORT_STATE_OPEN;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_LCDC_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_LCDC_Close
 **********************************************************************************************************************/
/*!
 * @brief    Closes LCDC port
 * @details
 * @param    None (only 1 LCD port supported)
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_LCDC_Close (void)
{
    ER_RET ret_val = ER_OK;

    if (LCDC_PORT_STATE_OPEN != lcdc_port_state)
    {
        ret_val = ER_INVAL;
    }
    else
    {
        ret_val = lcdc_port_close();
        if (ER_OK == ret_val)
        {
            lcdc_port_state = LCDC_PORT_STATE_CLOSED;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_LCDC_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_LCDC_Control
 **********************************************************************************************************************/
/*!
 * @brief    Requests to set or get port status or configuration
 * @details  NOTE: API function checks that buf is non-zero
 * @details  The upper layer should check that the buffer lies within a valid address range
 * @param    control_request - request to configure port or get port info.
 * @param    buf - configuration data to set or get, depending on request
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_LCDC_Control (lcdc_control_request_e control_request, uint8_t *buf)
{
    ER_RET ret_val = ER_OK;

    /* For all control requests except LCDC_CONTROL_RESET, need a valid buf pointer */
    if (LCDC_CONTROL_RESET != control_request)
    {
        if (buf == (void *) 0)
        {
            ret_val = ER_PARAM;
        }
    }

    if (ER_OK == ret_val)
    {
        switch (control_request)
        {
            case LCDC_CONTROL_SET_PORT_CONFIG:
                /* Set port configuration (only if port is OPEN and not busy) */
                if (lcdc_port_state != LCDC_PORT_STATE_OPEN)
                {
                    ret_val = ER_INVAL;
                }
                else
                {
                    ret_val = lcdc_set_port_config((lcdc_port_config_t *) buf);
                }
            break;

            case LCDC_CONTROL_GET_PORT_CONFIG:
                /* Get port configuration */
                ret_val = lcdc_get_port_config((lcdc_port_config_t *) buf);
            break;

            case LCDC_CONTROL_GET_PORT_STATE:
                buf[0] = lcdc_port_state;
            break;

            case LCDC_CONTROL_RESET:
                /* Reset the LCD controller */
                ret_val = lcdc_reset();
            break;

            default:
                ret_val = ER_PARAM;
            break;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_LCDC_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_LCDC_DisplayUpdate
 **********************************************************************************************************************/
/*!
 * @brief    Updates an area of the display
 * @details  Note: buf_len may be < rectangular area size but this is max length updated
 * @param    display_update_area - pointer to rectangle of display to update
 * @param    buf  - pointer to display data to be written
 * @param    buf_len - data length
 * @param    NOTE1: for bpp <= 8, rectangle co-ordinates must be on an 8-pixel boundary
 * @param    NOTE2: for bpp >= 16 have 1 pixel data per 32-bit entry of buf
 *                  for bpp = 8 have 1 pixel index per 32-bit entry of buf
 *                  for bpp = 4 have 2 pixel indices per 32-bit entry of buf
 *                  for bpp = 2 have 4 pixel indices per 32-bit entry of buf
 *                  for bpp = 1 have 8 pixel indices per 32-bit entry of buf
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_LCDC_DisplayUpdate (lcd_rectangle_t *display_update_area, uint32_t *buf, uint32_t buf_len)
{
    ER_RET ret_val = ER_OK;

    if ((display_update_area == (void *) 0) || (buf == (void *) 0) || (buf_len == 0))
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* check display area parameters are checked by driver function */

        if (lcdc_port_state != LCDC_PORT_STATE_OPEN)
        {
            ret_val = ER_INVAL;
        }
        else
        {
            lcdc_port_state = LCDC_PORT_STATE_BUSY;

            ret_val = lcdc_display_update(display_update_area, buf, buf_len);
            lcdc_port_state = LCDC_PORT_STATE_OPEN;

        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_LCDC_DisplayUpdate
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_LCDC_FillRectangle
 **********************************************************************************************************************/
/*!
 * @brief    Updates a rectangular section of the display with the specified colour
 * @details
 * @param    display_blink_area - pointer to rectangle of display to update
 * @param    colour - fill colour
 *              should be in correct format depending on configured bpp and colour mode e.g.
 *           for bpp < 16  , colour is palette index of blanking colour
 *           for bpp = 16, RGB 5:6:5 , colour is 0b0000 0000 0000 0000 RRRR RGGG GGGB BBBB
 *           for bpp = 16, BGR 5:6:5 , colour is 0b0000 0000 0000 0000 BBBB BGGG GGGR RRRR
 *           for bpp = 16, RGB 5:5:5 , colour is 0b0000 0000 0000 0000 0RRR RRGG GGGB BBBB
 *           for bpp = 16, BGR 5:5:5 , colour is 0b0000 0000 0000 0000 0BBB BBGG GGGR RRRR
 *
 *           for bpp = 24, RGB 8:8:8 , colour is 0b0000 0000 RRRR RRRR GGGG GGGG BBBB BBBB
 *           for bpp = 24, BGR 8:8:8 , colour is 0b0000 0000 BBBB BBBB GGGG GGGG RRRR RRRR
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_LCDC_FillRectangle (lcd_rectangle_t *display_update_area, uint32_t colour)
{
    ER_RET ret_val = ER_OK;

    if (display_update_area == (void *) 0)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* display area parameters are checked by driver function */

        if (lcdc_port_state != LCDC_PORT_STATE_OPEN)
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = lcdc_fill_rectangle(display_update_area, colour);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_LCDC_DisplaySetColour
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_LCDC_Blank
 **********************************************************************************************************************/
/*!
 * @brief    Clear (blank) the display
 * @details
 * @param    colour - set blank display to this colour
 *              should be in correct format depending on configured bpp and colour mode e.g.
 *           for bpp < 16  , colour is palette index of blanking colour
 *           for bpp = 16, RGB 5:6:5 , colour is 0b0000 0000 0000 0000 RRRR RGGG GGGB BBBB
 *           for bpp = 16, BGR 5:6:5 , colour is 0b0000 0000 0000 0000 BBBB BGGG GGGR RRRR
 *           for bpp = 16, RGB 5:5:5 , colour is 0b0000 0000 0000 0000 0RRR RRGG GGGB BBBB
 *           for bpp = 16, BGR 5:5:5 , colour is 0b0000 0000 0000 0000 0BBB BBGG GGGR RRRR
 *
 *           for bpp = 24, RGB 8:8:8 , colour is 0b0000 0000 RRRR RRRR GGGG GGGG BBBB BBBB
 *           for bpp = 24, BGR 8:8:8 , colour is 0b0000 0000 BBBB BBBB GGGG GGGG RRRR RRRR
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_LCDC_Blank (uint32_t colour)
{
    ER_RET ret_val = ER_OK;

    if (LCDC_PORT_STATE_OPEN != lcdc_port_state)
    {
        ret_val = ER_INVAL;
    }
    else
    {
        ret_val = lcdc_blank_display(colour);
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_LCDC_Blank
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_LCDC_Blink
 **********************************************************************************************************************/
/*!
 * @brief    Blink a section of the display
 * @details
 * @param    display_blink_area - pointer to rectangle of display to blink
 * @param    blink_mode - LCDC_BLINK_MODE_OFF or LCDC_BLINK_MODE_SLOW, LCDC_BLINK_MODE_MEDIUM, LCDC_BLINK_MODE_FAST
 * @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET R_LCDC_Blink (lcd_rectangle_t *display_blink_area, lcdc_blink_mode_e blink_mode)
{
    ER_RET ret_val = ER_OK;

    if (display_blink_area == (void *) 0)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        /* display area parameters are checked by driver function */

        if (lcdc_port_state != LCDC_PORT_STATE_OPEN)
        {
            ret_val = ER_INVAL;
        }
        else
        {
            ret_val = lcdc_blink_display(display_blink_area, blink_mode);
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_LCDC_Blink
 **********************************************************************************************************************/


