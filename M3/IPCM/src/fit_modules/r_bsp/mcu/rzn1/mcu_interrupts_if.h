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
 *      FILE         :  mcu_interrupts_if.h
 *      DESCRIPTION  :  Definitions required to enable/disable interrupts
 *                      and to register interrupt callbacks.
 *      MCU SERIES   :  RZ/N1 D, S & L
 *      CPU TYPE     :  ARM Cortex M3
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * $Revision: 1166 $
 * $Date: 2019-01-17 14:01:52 +0000 (Thu, 17 Jan 2019) $
 **********************************************************************************************************************/
#ifndef MCU_INTERRUPTS_IF_H__
#define MCU_INTERRUPTS_IF_H__

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
/* Available return codes. */
typedef enum
{
    MCU_INT_SUCCESS = 0, MCU_INT_ERR_NO_REGISTERED_CALLBACK, /* There is not a registered callback for this interrupt source */
    MCU_INT_ERR_INVALID_ARG, /* Illegal argument input */
    MCU_INT_ERR_UNSUPPORTED /* Operation is not supported by this API */
} MCU_INT_ERR_E;

/* Available commands for R_BSP_InterruptControl() function. */
typedef enum
{
    MCU_INT_CMD_CALL_CALLBACK = 0, /* Calls registered callback function if one exists */
    MCU_INT_CMD_INTERRUPT_ENABLE, /* Enables a given interrupt */
    MCU_INT_CMD_TRIGGER_SGI, /* Triggers a given software interrupt */
    MCU_INT_CMD_CLEAR_SGI_INTERRUPT, /* Clears pending software interrupt */
    MCU_INT_CMD_INTERRUPT_DISABLE, /* Disables a given interrupt */
    MCU_INT_CMD_SET_INTERRUPT_PRIORITY /* set interrupt priority */
} MCU_INT_CMD_E;

/* Type to be used for pdata argument in Control function. */
typedef union
{
        uint32_t ipl;                         //Used when enabling an interrupt to set that interrupt's priority level
} bsp_int_ctrl_t;

/* Easy to use typedef for callback functions. */
typedef void (*bsp_int_cb_t) (void *);

/* This structure is the common one that is passed as the 'void *' argument to callback functions when an
 * exception occurs.
 */
typedef struct
{
        IRQn_Type vector; /* Which vector caused this interrupt */
} bsp_int_cb_args_t;

/***********************************************************************************************************************
 Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
MCU_INT_ERR_E R_BSP_InterruptRegisterCallback (IRQn_Type vector, bsp_int_cb_t callback);
MCU_INT_ERR_E R_BSP_InterruptGetRegisteredCallback (IRQn_Type vector, bsp_int_cb_t * callback);
MCU_INT_ERR_E R_BSP_InterruptControl (IRQn_Type vector, MCU_INT_CMD_E cmd, void *pdata);
MCU_INT_ERR_E R_BSP_RegisterSGI (IRQn_Type irq_num, uint8_t priority, bsp_int_cb_t callback);

#endif  /* MCU_INTERRUPTS_IF_H__ */
