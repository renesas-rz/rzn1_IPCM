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
 *      PROJECT NAME :  RZ/N1 bare metal Drivers
 *      FILE         :  mcu_interrupts.c
 *      DESCRIPTION  :  interrupt management functions
 *      MCU SERIES   :  RZ/N1 D, S & L
 *      CPU TYPE     :  ARM Cortex M3
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * $Revision: 1195 $
 * $Date: 2019-01-29 12:51:05 +0000 (Tue, 29 Jan 2019) $
 *
 * Description : This module allows for callbacks to be registered for interrupts.
 *
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "platform.h"
#include "mcu_interrupts_if.h"

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/***********************************************************************************************************************
 Externs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
/* This array holds callback functions */
/* Note: only for configurable interrupts - not for exception handlers */
static void (*g_bsp_vectors[RZN1_INT_SRC_TOTAL]) (void * pdata);

static MCU_INT_ERR_E bsp_interrupt_enable_disable (IRQn_Type vector, bool enable);
static MCU_INT_ERR_E bsp_interrupt_set_priority (IRQn_Type vector, uint32_t priority);

/***********************************************************************************************************************
 * Function Name: bsp_interrupt_open
 * Description  : Initialize callback function array.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void bsp_interrupts_open (void)
{
    uint32_t i;

    for (i = 0; i < RZN1_INT_SRC_TOTAL; i++)
    {
        g_bsp_vectors[i] = FIT_NO_FUNC;
    }
}

/***********************************************************************************************************************
 * Function Name: R_BSP_InterruptRegisterCallback
 * Description  : Registers a callback function for supported interrupts. If FIT_NO_FUNC, NULL, or
 *                any other invalid function address is passed for the callback argument then any previously registered
 *                callbacks are unregistered.
 * Arguments    : vector - Which interrupt to register a callback for.
 *                callback - Pointer to function to call when interrupt occurs.
 * Return Value : MCU_INT_ERR_E error status
 *
 **********************************************************************************************************************/
MCU_INT_ERR_E R_BSP_InterruptRegisterCallback (IRQn_Type vector, bsp_int_cb_t callback)
{
    MCU_INT_ERR_E err = MCU_INT_SUCCESS;

    /* Check for valid vector */
    if (vector >= RZN1_INT_SRC_TOTAL)
    {
        err = MCU_INT_ERR_INVALID_ARG;
    }
    else
    {
        /* Check for valid address */
        if ((uint32_t) callback == (uint32_t)FIT_NO_FUNC)
        {
            err = MCU_INT_ERR_INVALID_ARG;
        }
        g_bsp_vectors[vector] = callback;
    }

    return err;
}

/***********************************************************************************************************************
 * Function Name: R_BSP_InterruptRead
 * Description  : Returns the callback function address for an interrupt.
 * Arguments    : vector -
 *                    Which interrupt to read the callback for.
 *                callback -
 *                    Pointer of where to store callback address.
 * Return Value : MCU_INT_ERR_E error status
 **********************************************************************************************************************/
MCU_INT_ERR_E R_BSP_InterruptGetRegisteredCallback (IRQn_Type vector, bsp_int_cb_t *callback)
{
    MCU_INT_ERR_E err;

    err = MCU_INT_SUCCESS;

    /* Check for valid vector */
    if (vector >= RZN1_INT_SRC_TOTAL)
    {
        err = MCU_INT_ERR_INVALID_ARG;
    }
    else
    {
        /* Check for valid address. */
        if (((uint32_t) g_bsp_vectors[vector] == (uint32_t) NULL)
                || ((uint32_t) g_bsp_vectors[vector] == (uint32_t)FIT_NO_FUNC))
        {
            err = MCU_INT_ERR_NO_REGISTERED_CALLBACK;
        }
        else
        {
            *callback = g_bsp_vectors[vector];
        }
    }

    return err;
}

/***********************************************************************************************************************
 * Function Name: R_BSP_InterruptControl
 * Description  : Executes specified command.
 * Arguments    : vector - Which vector is being used.
 *                cmd - Which command to execute.
 *                pdata - Pointer to data to use with command.
 * Return Value : MCU_INT_ERR_E error status
 **********************************************************************************************************************/
MCU_INT_ERR_E R_BSP_InterruptControl (IRQn_Type vector, MCU_INT_CMD_E cmd, void *pdata)
{
    MCU_INT_ERR_E err = MCU_INT_SUCCESS;
    bsp_int_cb_args_t cb_args;

    /* Check for valid vector */
    if (vector >= RZN1_INT_SRC_TOTAL)
    {
        err = MCU_INT_ERR_INVALID_ARG;
    }
    else
    {
        switch (cmd)
        {
            case (MCU_INT_CMD_CALL_CALLBACK):
                if (((uint32_t) g_bsp_vectors[vector] != (uint32_t) NULL)
                        && ((uint32_t) g_bsp_vectors[vector] != (uint32_t)FIT_NO_FUNC))
                {
                    /* Fill in callback info. */
                    cb_args.vector = vector;
                    g_bsp_vectors[vector]( &cb_args);
                }
                else
                {
                    err = MCU_INT_ERR_NO_REGISTERED_CALLBACK;
                }
            break;

            case (MCU_INT_CMD_INTERRUPT_ENABLE):
                err = bsp_interrupt_enable_disable(vector, true);
            break;

            case (MCU_INT_CMD_INTERRUPT_DISABLE):
                err = bsp_interrupt_enable_disable(vector, false);
            break;

            case MCU_INT_CMD_SET_INTERRUPT_PRIORITY:
                if (((uint32_t) pdata != (uint32_t) NULL) && ((uint32_t) pdata != (uint32_t)FIT_NO_FUNC))
                {
                    err = bsp_interrupt_set_priority(vector, *(uint32_t *) pdata);
                }
                else
                {
                    err = MCU_INT_ERR_INVALID_ARG;
                }

            break;

            default:
                err = MCU_INT_ERR_INVALID_ARG;
            break;
        }
    }
    return err;
}

/***********************************************************************************************************************
 * Function Name: bsp_interrupt_enable_disable
 * Description  : Either enables or disables an interrupt.
 * Arguments    : vector - Which vector to enable or disable.
 *                enable - Whether to enable or disable the interrupt.
 * Return Value : MCU_INT_ERR_E error status
 **********************************************************************************************************************/
static MCU_INT_ERR_E bsp_interrupt_enable_disable (IRQn_Type vector, bool enable)
{
    MCU_INT_ERR_E err = MCU_INT_SUCCESS;

    if (true == ValidateIRQ(vector))
    {
        if (true == enable)
        {
            NVIC_EnableIRQ((IRQn_Type) vector);
        }
        else
        {
            NVIC_DisableIRQ((IRQn_Type) vector);
        }
    }
    else
    {
        err = MCU_INT_ERR_UNSUPPORTED;
    }

    return err;
}

/***********************************************************************************************************************
 * Function Name: bsp_interrupt_set_priority
 * Description  : Either enables or disables an interrupt.
 * Arguments    : vector - Which vector to enable or disable.
 *                enable - Whether to enable or disable the interrupt.
 * Return Value : MCU_INT_ERR_E error status
 **********************************************************************************************************************/
static MCU_INT_ERR_E bsp_interrupt_set_priority (IRQn_Type vector, uint32_t priority)
{
    MCU_INT_ERR_E err = MCU_INT_SUCCESS;

    if (true == ValidateIRQ(vector))
    {
        NVIC_SetPriority(vector, priority);
    }
    else
    {
        err = MCU_INT_ERR_UNSUPPORTED;
    }

    return err;
}
