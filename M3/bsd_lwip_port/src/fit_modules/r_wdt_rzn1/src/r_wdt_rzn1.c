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
 * $Revision: 1201 $
 * $Date: 2019-02-04 14:08:15 +0000 (Mon, 04 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_wdt_rzn1.c
 * Description  :  WDT control functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_wdt_rzn1_if.h"
#include "r_wdt_rzn1.h"
#include "iodefine.h"
#include "r_sysctrl_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local variables
 **********************************************************************************************************************/
static volatile WDOG_Type *wdt_base_address;

/***********************************************************************************************************************
 * Local functions
 **********************************************************************************************************************/
static void handle_wdt_isr (void);
wdt_callback wdt_call_back;

/***********************************************************************************************************************
 *
 *  Function:       wdt_get_major_version_num
 *
 *  Return value:   WDT driver Major version number
 *
 *  Parameters:     None
 *
 *  Description:    Gets the WDT driver's Major version number
 *
 **********************************************************************************************************************/
uint8_t wdt_get_major_version_num (void)
{
    return (uint8_t) WDT_DRIVER_MAJOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function wdt_get_major_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       wdt_get_minor_version_num
 *
 *  Return value:   WDT driver Minor version number
 *
 *  Parameters:     None
 *
 *  Description:    Gets the WDT driver's Minor version number
 *
 **********************************************************************************************************************/
uint8_t wdt_get_minor_version_num (void)
{
    return (uint8_t) WDT_DRIVER_MINOR_VERSION_NUMBER;
}
/***********************************************************************************************************************
 End of function wdt_get_minor_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       wdt_init
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *
 *  Description:    Store the WDT base address
 *                  and to register watchdog interrupts.
 *
 *(There is no need for system control configuration to allow for WDT register access)
 **********************************************************************************************************************/
ER_RET wdt_init (void)
{

    ER_RET ret_val = ER_OK;
    uint32_t int_priority;

    /*Check if the board is operating on CM3 or CA7 and register IRQ address accordingly*/
#ifdef CORE_CA7
    uint32_t cpuid;
    IRQn_Type irq_num;
    cpuid = R_Get_CPUID(); /*Read CPU ID register */

    /* Check if the board is operating on CA7_0 or CA7_1*/
    if (cpuid)
    {
        irq_num = RZN1_IRQ_WATCHDOG_RESETN_1;

        /* Store the WDT base address */
        wdt_base_address = (WDOG_Type *) RZN1_WATCHDOG_CA7_1_BASE;
    }
    else
    {
        irq_num = RZN1_IRQ_WATCHDOG_RESETN_0;
        /* Store the WDT base address */
        wdt_base_address = (WDOG_Type *) RZN1_WATCHDOG_CA7_0_BASE;
    }
#else

    IRQn_Type irq_num = RZN1_IRQ_WATCHDOG_CM3_RESETN;

    /* Store the WDT base address */
    wdt_base_address = (WDOG_Type *) RZN1_WATCHDOG_M3_BASE;
#endif

    /* Register WDT interrupts in the FIT compliant method */
    if (R_BSP_InterruptRegisterCallback((IRQn_Type) irq_num, (bsp_int_cb_t) &handle_wdt_isr) == MCU_INT_SUCCESS)
    {
        int_priority = 4;
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
    return ret_val;
}
/***********************************************************************************************************************
 End of function wdt_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       wdt_uninit
 *
 *  Return value:   None.
 *
 *  Parameters:     None.
 *
 *  Description:    unregister watchdog interrupts.
 *
 **********************************************************************************************************************/
ER_RET wdt_uninit (void)
{
    ER_RET ret_val = ER_OK;

    /*Check if the board is operating on CM3 or CA7*/
#ifdef CORE_CA7
    uint32_t cpuid;
    IRQn_Type irq_num;
    cpuid = R_Get_CPUID();

    if (cpuid)
    {
        irq_num = RZN1_IRQ_WATCHDOG_RESETN_1;
    }
    else
    {
      irq_num = RZN1_IRQ_WATCHDOG_RESETN_0;
    }
#else
    IRQn_Type irq_num = RZN1_IRQ_WATCHDOG_CM3_RESETN;
#endif

    ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE,
    FIT_NO_PTR);

    return ret_val;
}
/***********************************************************************************************************************
 End of function wdt_uninit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       wdt_setoutput
 *
 *  Return value:   None.
 *
 *  Parameters:     output - either enable or disable reset.
 *
 *  Description:    Mask/Unmask reset generation for the WDT.
 *
 **********************************************************************************************************************/
void wdt_setoutput (WDT_OUTPUT output)
{
    if (WDT_SYSTEM_RESET == output)
    {
        R_SYSCTRL_WDTResetConfig(true);
    }
    else
    {
        R_SYSCTRL_WDTResetConfig(false);
    }
}
/***********************************************************************************************************************
 End of function wdt_setoutput
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       wdt_enable
 *
 *  Return value:   Error status.
 *
 *  Parameters:     prescaler -
 *                  reload_val -
 *  Description:    Enables the WDT.
 *
 **********************************************************************************************************************/
ER_RET wdt_enable (WDT_PRESCALER prescaler, uint16_t reload_val)
{
    ER_RET ret_val = ER_OK;
    uint16_t wdt_ctrl;
    uint16_t wdt_ctrl_test;
    volatile WDOG_Type *base_address = wdt_base_address;

    if (0xFFF >= reload_val)
    {
        wdt_ctrl = reload_val & 0x0FFF;
        wdt_ctrl |= (prescaler << 12);
        wdt_ctrl |= (0x0A << 12); /* Watchdog enable and secure ID */

        base_address->CTRL_RETRIGGER.LONG = wdt_ctrl;

        /* Test the correct value has been written */
        wdt_ctrl_test = base_address->CTRL_RETRIGGER.LONG;
        if (wdt_ctrl_test != (wdt_ctrl &= ( ~(0x2 << 14))))
        {
            ret_val = ER_SYS;
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function wdt_enable
 **********************************************************************************************************************/
#if 0 // @suppress("Disabled code")
/***********************************************************************************************************************
 *
 *  Function:       WDT_Disable
 *
 *  Return value:   Error status.
 *
 *  Parameters:     None.
 *
 *  Description:    Disables the WDT.
 *
 **********************************************************************************************************************/
ER_RET WDT_Disable(void)
{
    ER_RET ret_val = ER_OK;
    uint16_t wdt_ctrl;
    uint16_t wdt_ctrl_test;
    volatile WDT_Type *WDT_Base_Address = wdt_base_address;

    /* Enable the Watchdog */
    wdt_ctrl = WDT_Base_Address->CTRL_RETRIGGER.LONG;
    wdt_ctrl &= ~(0x01 << 13); /* Disable watchdog */
    wdt_ctrl |= 0x1 << 15; /* Secure ID */
    /* Cannot stop the watchdog once started */
    WDT_Base_Address->CTRL_RETRIGGER.LONG = wdt_ctrl;

    /* Test the correct value has been written */
    wdt_ctrl_test = WDT_Base_Address->CTRL_RETRIGGER.LONG;
    if(((wdt_ctrl_test >> 13) & 0x01))
    {
        ret_val = ER_SYS;
    }
    return ret_val;
}
#endif /* 0 */
/***********************************************************************************************************************
 *
 *  Function:       wdt_retrigger
 *
 *  Return value:   Error value.
 *
 *  Parameters:     None.
 *
 *  Description:    Refresh the value in the countdown register through a write
 *                  to the control register.
 *
 **********************************************************************************************************************/
ER_RET wdt_retrigger (void)
{
    ER_RET ret_val = ER_OK;
    uint16_t wdt_ctrl_test;
    volatile WDOG_Type *base_address = wdt_base_address;

    wdt_ctrl_test = base_address->CTRL_RETRIGGER.LONG;
    if ( !((wdt_ctrl_test >> 13) & 0x01))
    {
        ret_val = ER_INVAL;
    }
    else
    {
        /* Any value written to the control register while the WDT is enabled will retrigger the WDT */
        base_address->CTRL_RETRIGGER.LONG = 0x01;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function wdt_retrigger
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       wdt_setcallback
 *
 *  Return value:   Error status.
 *
 *  Parameters:     None.
 *
 *  Description:    Stores the call back for the WDT ISR.
 *
 **********************************************************************************************************************/
ER_RET wdt_setcallback (wdt_callback call_back)
{
    ER_RET ret_val = ER_OK;

    if (NULL == call_back)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        wdt_call_back = call_back;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function wdt_setcallback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       handle_wdt_isr
 *
 *  Return value:   None.
 *
 *  Parameters:     None.
 *
 *  Description:    Interrupt handler for CM3 watchdog timer
 *
 **********************************************************************************************************************/
static void handle_wdt_isr (void)
{
    /* Call callback */
    if (NULL != wdt_call_back)
    {
        (wdt_call_back)();
    }

    /* Unmask pending reset */
    R_SYSCTRL_WDTReset();

}
/***********************************************************************************************************************
 End of function handle_wdt_isr
 **********************************************************************************************************************/
