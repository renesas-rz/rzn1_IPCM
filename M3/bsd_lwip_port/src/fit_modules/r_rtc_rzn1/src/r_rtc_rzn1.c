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
 * FILE         :  r_rtc_rzn1.c
 * Description  :  RTC driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_sysctrl_rzn1_if.h"
#include "r_rtc_rzn1_if.h"
#include "r_rtc_rzn1_config.h"
#include "iodefine.h"
#include "r_rtc_rzn1.h"
#include "r_timer_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define TM_STRUCT_YEAR_MIN      (RTC_YEAR_MIN - TM_STRUCT_EPOCH)
#define TM_STRUCT_YEAR_MAX      (RTC_YEAR_MAX - TM_STRUCT_EPOCH)

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  External function declarations
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Local (private) variables
 **********************************************************************************************************************/
static bool m_rtc_ready;
static volatile RTC_Type * m_rtc_registers;
#ifdef CORE_CA7 /* RTC interrupts only avaialbable on CA7 platform */
static rtc_event_callback_t m_alarm_callback;
static rtc_event_callback_t m_periodic_callback;
static rtc_event_callback_t m_one_sec_callback;
#endif

/***********************************************************************************************************************
 * Local (private) functions
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *
 *  Function:           rtc_enable
 *
 *  Return value:       Error status
 *
 *  Parameters:         void
 *
 *  Description:        Enables the controller & waits for 'enabled' status
 *
 **********************************************************************************************************************/
static ER_RET rtc_enable(void)
{
    ER_RET ret_val = ER_OK;
    uint32_t timeout_count;

    /* Enable RTC controller */
    m_rtc_registers->RTCA0CTL0.BIT.RTCA0CE = 1u;
    /* Wait until counter operation is reported operational. See RZ/N1D/S/L Peripherals user manual Rev 0.50 page 695 */
    for (timeout_count = (RTC_WAIT_TIMEOUT_COUNT_uS/RTC_WAIT_TIMEOUT_POLL_RATE_uS); timeout_count > 0; timeout_count--)
    {
        if (1 == m_rtc_registers->RTCA0CTL0.BIT.RTCA0CEST)
        {
            break;
        }

        Delay_usec(RTC_WAIT_TIMEOUT_POLL_RATE_uS);
    }

    if (0 == timeout_count)
    {
        ret_val = ER_TIMEOUT;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function rtc_enable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_disable
 *
 *  Return value:       Error status
 *
 *  Parameters:         None
 *
 *  Description:        Disables the controller & waits for Disabled status
 *
 **********************************************************************************************************************/
static ER_RET rtc_disable(void)
{
    uint32_t timeout_count;

    /* Wait until clock is enabled */
    for (timeout_count = (RTC_WAIT_TIMEOUT_COUNT_uS/RTC_WAIT_TIMEOUT_POLL_RATE_uS); timeout_count > 0; timeout_count--)
    {
        /* Wait until counter operation is reported operational before turning off clock. See RZ/N1D/S/L Peripherals user manual Rev 0.50 page 695 */
        if (1 == m_rtc_registers->RTCA0CTL0.BIT.RTCA0CEST)
        {
            break;
        }

        Delay_usec(RTC_WAIT_TIMEOUT_POLL_RATE_uS);
    }

    if (0 == timeout_count)
    {
        return ER_TIMEOUT;
    }

    /* disable RTC controller */
    m_rtc_registers->RTCA0CTL0.BIT.RTCA0CE = 0u;

    return ER_OK;
}
/***********************************************************************************************************************
 End of function rtc_disable
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_bcd_to_dec
 *
 *  Return value:       Converted value
 *
 *  Parameters:         to_convert - Value to convert.
 *
 *  Description:        Converts from binary coded decimal (BCD) to decimal
 *
 **********************************************************************************************************************/
static int rtc_bcd_to_dec(uint8_t to_convert)
{
    return (int) ((((to_convert & 0xF0) >> 4) * 10) + (to_convert & 0x0F));
}
/***********************************************************************************************************************
 End of function rtc_bcd_to_dec
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_dec_to_bcd
 *
 *  Return value:       Converted value
 *
 *  Parameters:         to_convert - Value to convert.
 *
 *  Description:        Converts from decimal to binary coded decimal (BCD)
 *
 **********************************************************************************************************************/
static uint8_t rtc_dec_to_bcd(uint8_t to_convert)
{
    return (uint8_t)((((to_convert / 10) << 4) & 0xF0) | (to_convert % 10));
}
/***********************************************************************************************************************
 End of function rtc_dec_to_bcd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_handle_interrupt
 *
 *  Return value:       none
 *
 *  Parameters:         IRQn_Type Interrupt Type
 *
 *  Description:        handle RTC Interrupt for Alarm, Periodic and One Second Alert
 *
 **********************************************************************************************************************/
#ifdef CORE_CA7 /* RTC interrupts only avaialbable on CA7 platform */
static void rtc_handle_interrupt(IRQn_Type *irq_num_ptr)
{
    uint32_t irq_num = *irq_num_ptr;

    if (RZN1_IRQ_RTCATINTAL == irq_num)
    {
        if (FIT_NO_PTR != m_alarm_callback)
        {
            m_alarm_callback(RTC_ALARM_EVENT);
        }
    } else if (RZN1_IRQ_RTCATINTR == irq_num)
    {
        if (FIT_NO_PTR != m_periodic_callback)
        {
            m_periodic_callback(RTC_PERIODIC_EVENT);
        }
    } else if (RZN1_IRQ_RTCATINT1S == irq_num)
    {
        if (FIT_NO_PTR != m_one_sec_callback)
        {
            m_one_sec_callback(RTC_ONE_SEC_EVENT);
        }
    } else
    {
        /* Error Case */
        while (1);
    }
}
#endif
/***********************************************************************************************************************
 End of function rtc_handle_interrupt
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported functions
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *
 *  Function:           rtc_get_major_version_num
 *
 *  Return value:       RTC driver Major version number
 *
 *  Parameters:         None
 *
 *  Description:        Gets the RTC driver's Major version number
 *
 **********************************************************************************************************************/
uint8_t rtc_get_major_version_num(void)
{
    uint8_t major_ver_num = (uint8_t)RTC_DRIVER_MAJOR_VERSION_NUMBER;

    return major_ver_num;
}
/***********************************************************************************************************************
 End of function rtc_get_major_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_get_minor_version_num
 *
 *  Return value:       RTC driver Minor version number
 *
 *  Parameters:         None
 *
 *  Description:        Gets the RTC driver's Minor version number
 *
 **********************************************************************************************************************/
uint8_t rtc_get_minor_version_num(void)
{
    uint8_t minor_ver_num = (uint8_t)RTC_DRIVER_MINOR_VERSION_NUMBER;

    return minor_ver_num;
}
/***********************************************************************************************************************
 End of function rtc_get_minor_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_init
 *
 *  Return value:       Error Status
 *
 *  Parameters:         void
 *
 *  Description:        Initialise RTC.
 *
 **********************************************************************************************************************/
ER_RET rtc_init(void)
{
    ER_RET ret_val = ER_OK;

    if (m_rtc_ready)
    {
        return ER_INVAL;
    }

    ret_val = R_SYSCTRL_EnableRTC();
    if (ER_OK == ret_val)
    {
        m_rtc_ready = true;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function rtc_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_uninitialise
 *
 *  Return value:       Error Status
 *
 *  Parameters:         void
 *
 *  Description:        Uninitialises RTC peripheral.
 *
 **********************************************************************************************************************/
ER_RET rtc_uninitialise(void)
{
    if (!m_rtc_ready)
    {
        return ER_INVAL;
    }

    R_SYSCTRL_DisableRTC();
    m_rtc_ready = false;

    return ER_OK;
}
/***********************************************************************************************************************
 End of function rtc_uninitialise
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_open
 *
 *  Return value:       Error status
 *
 *  Parameters:         None
 *
 *  Description:        Opens the RTC Peripheral
 *
 **********************************************************************************************************************/
ER_RET rtc_open(void)
{
    ER_RET ret_val = ER_OK;

    if (!m_rtc_ready)
    {
        return ER_INVAL;
    }

    /* Get pointer to register set */
    m_rtc_registers = (volatile RTC_Type *) (RZN1_RTC_BASE);

#ifdef CORE_CA7 /* RTC interrupts only avaialbable on CA7 platform */
    {
        IRQn_Type irq_num;
        uint32_t int_priority;

        m_alarm_callback = FIT_NO_PTR;
        m_periodic_callback = FIT_NO_PTR;
        m_one_sec_callback = FIT_NO_PTR;

        for (irq_num = RZN1_IRQ_RTCATINTAL; irq_num <= RZN1_IRQ_RTCATINT1S; irq_num++)
        {
            /* Set interrupt priority for RTC & disable RTC interrupts */
            if (MCU_INT_SUCCESS == R_BSP_InterruptRegisterCallback((IRQn_Type)irq_num, (bsp_int_cb_t)&rtc_handle_interrupt))
            {
                int_priority = RTC_DEFAULT_INT_PRIORITY;
                ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
                if (MCU_INT_SUCCESS != ret_val)
                {
                    ret_val = ER_SYS;
                    break;
                }
                else
                {
                    ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
                }
            }
            else
            {
                ret_val = ER_SYS;
                break;
            }
        }
    }
#endif

    if (ER_OK == ret_val)
    {
        ret_val = rtc_enable();
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function rtc_open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_close
 *
 *  Return value:       Error status
 *
 *  Parameters:         void
 *
 *  Description:        Closes the RTC Peripheral
 *
 **********************************************************************************************************************/
ER_RET rtc_close(void)
{
    ER_RET ret_val = ER_OK;

    if (!m_rtc_ready)
    {
        return ER_INVAL;
    }

#ifdef CORE_CA7 /* RTC interrupts only avaialbable on CA7 platform */
    /* Unregister callbacks */
    m_alarm_callback = FIT_NO_PTR;
    m_periodic_callback = FIT_NO_PTR;
    m_one_sec_callback = FIT_NO_PTR;

    /* Disable RTC system interrupts for this RTC */
    ret_val = R_BSP_InterruptControl(RZN1_IRQ_RTCATINTAL, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
    ret_val = R_BSP_InterruptControl(RZN1_IRQ_RTCATINTR,  MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
    ret_val = R_BSP_InterruptControl(RZN1_IRQ_RTCATINT1S, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
#endif

    /* Disable the RTC module */
    ret_val = rtc_disable();

    /* Clear register pointer */
    m_rtc_registers = FIT_NO_PTR;

    return ret_val;
}
/***********************************************************************************************************************
 End of function rtc_close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_read
 *
 *  Return value:       Error status
 *
 *  Parameters:         p_current - time in RTC driver format
 *
 *  Description:        Reads time of RTC
 *
 **********************************************************************************************************************/
ER_RET rtc_read(tm_t * p_current)
{

    if (!m_rtc_ready)
    {
        return ER_INVAL;
    }

    /* Implement flow diagram. See RZ/N1D/S/L Peripherals user manual Rev 0.50 page 696 */
    while (1 == m_rtc_registers->RTCA0CTL2.BIT.RTCA0WST);

    m_rtc_registers->RTCA0CTL2.BIT.RTCA0WAIT = 1u;
    while (0 == m_rtc_registers->RTCA0CTL2.BIT.RTCA0WST);

    p_current->tm_sec  = rtc_bcd_to_dec((uint8_t)m_rtc_registers->RTCA0SEC.BIT.RTCA0SEC);
    p_current->tm_min  = rtc_bcd_to_dec((uint8_t)m_rtc_registers->RTCA0MIN.BIT.RTCA0MIN);
    p_current->tm_hour = rtc_bcd_to_dec((uint8_t) m_rtc_registers->RTCA0HOUR.BIT.RTCA0HOUR);
    p_current->tm_wday = rtc_bcd_to_dec((uint8_t)m_rtc_registers->RTCA0WEEK.BIT.RTCA0WEEK);
    p_current->tm_mday = rtc_bcd_to_dec((uint8_t)m_rtc_registers->RTCA0DAY.BIT.RTCA0DAY);
    p_current->tm_mon  = rtc_bcd_to_dec((uint8_t) m_rtc_registers->RTCA0MONTH.BIT.RTCA0MONTH) - 1; /* tm stucture has month range of 0 - 11 whereas RTC uses the range 1-12 */
    /* tm struct has tm_yday but RTC does not */
    /* tm struct has tm_isdst but RTC does not */

    p_current->tm_year = rtc_bcd_to_dec((uint8_t) m_rtc_registers->RTCA0YEAR.BIT.RTCA0YEAR) + TM_STRUCT_YEAR_MIN;
    /* Update RTC with new values */
    m_rtc_registers->RTCA0CTL2.BIT.RTCA0WAIT = 0u;

    return ER_OK;
}
/***********************************************************************************************************************
 End of function rtc_read
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_write
 *
 *  Return value:       Error status
 *
 *  Parameters:         p_current - time in RTC driver format
 *
 *  Description:        Writes time to RTC
 *
 **********************************************************************************************************************/
ER_RET rtc_write(tm_t * p_current)
{
    if (!m_rtc_ready)
    {
        return ER_INVAL;
    }

    if ((p_current->tm_year < TM_STRUCT_YEAR_MIN) || (p_current->tm_year > TM_STRUCT_YEAR_MAX))
    {
        return ER_PARAM;
    }

    /* Implement flow diagram. See RZ/N1D/S/L Peripherals user manual Rev 0.50 page 696 */
    while (1 == m_rtc_registers->RTCA0CTL2.BIT.RTCA0WST);

    m_rtc_registers->RTCA0CTL2.BIT.RTCA0WAIT = 1u;
    while (0 == m_rtc_registers->RTCA0CTL2.BIT.RTCA0WST);

    m_rtc_registers->RTCA0CTL0.BIT.RTCA0AMPM = RTC_HOURS_24HR;
    m_rtc_registers->RTCA0SEC.BIT.RTCA0SEC = rtc_dec_to_bcd((uint8_t) p_current->tm_sec);
    m_rtc_registers->RTCA0MIN.BIT.RTCA0MIN = rtc_dec_to_bcd((uint8_t) p_current->tm_min);
    m_rtc_registers->RTCA0HOUR.BIT.RTCA0HOUR = rtc_dec_to_bcd((uint8_t) p_current->tm_hour);
    m_rtc_registers->RTCA0WEEK.BIT.RTCA0WEEK = rtc_dec_to_bcd((uint8_t) p_current->tm_wday);
    m_rtc_registers->RTCA0DAY.BIT.RTCA0DAY = rtc_dec_to_bcd((uint8_t) p_current->tm_mday);
    m_rtc_registers->RTCA0MONTH.BIT.RTCA0MONTH = rtc_dec_to_bcd((uint8_t)(p_current->tm_mon + 1)); /* tm stucture has month range of 0 - 11 whereas RTC uses the range 1-12 */
    m_rtc_registers->RTCA0YEAR.BIT.RTCA0YEAR = rtc_dec_to_bcd((uint8_t)(p_current->tm_year - TM_STRUCT_YEAR_MIN));
    /* Update RTC with new values */
    m_rtc_registers->RTCA0CTL2.BIT.RTCA0WAIT = 0u;

    return ER_OK;
}
/***********************************************************************************************************************
 End of function rtc_write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_register_event_callback
 *
 *  Return value:       Error status
 *
 *  Parameters:         event - type of event being registered
 *                      callback -the callback to register. Note: if FIT_NO_PTR is
 *                      supplied then this de-registers any existing callback and turns
 *                      of the associated interrupt
 *
 *  Description:        Registers an event callback
 *
 **********************************************************************************************************************/
ER_RET rtc_register_event_callback(RTC_CALLBACK_REQUEST_T * pCallbackEvent)
{
    ER_RET ret_val = ER_OK;
#ifdef CORE_CA7 /* RTC interrupts only avaialbable on CA7 platform */
    RTC_EVENT_E event = pCallbackEvent->eventType;
    rtc_event_callback_t callback = pCallbackEvent->callback;

    if (RTC_ALARM_EVENT == event)
    {
        /* Always Disable interrupt as needs disabling if either new interrupt settings or supplying NULL pointer for a callback */
        ret_val = R_BSP_InterruptControl(RZN1_IRQ_RTCATINTAL, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
        if (ER_OK != ret_val)
        {
            return ret_val;
        }

        if (FIT_NO_PTR == callback)
        {
            /* No callback supplied so remove any existing callback */
            m_rtc_registers->RTCA0CTL1.BIT.RTCA0ALME = 0u;
            m_alarm_callback = FIT_NO_PTR;
        } else
        {
            m_rtc_registers->RTCA0ALM.BIT.RTCA0ALM = rtc_dec_to_bcd(pCallbackEvent->alarmSetup.minutes);
            m_rtc_registers->RTCA0ALH.BIT.RTCA0ALH = rtc_dec_to_bcd(pCallbackEvent->alarmSetup.hours);
            m_rtc_registers->RTCA0ALW.LONG         = (uint32_t)pCallbackEvent->alarmSetup.activeDays;
            /* Enable physical output pin */
            m_rtc_registers->RTCA0CTL1.BIT.RTCA0ALME = 1u;

            /* callback supplied so register it */
            m_alarm_callback = callback;
            ret_val = R_BSP_InterruptControl(RZN1_IRQ_RTCATINTAL, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);
        }
    }
    else if (RTC_PERIODIC_EVENT == event)
    {
        /* Always Disable interrupt as needs disabling if either new interrupt settings or supplying NULL pointer for a callback */
        ret_val = R_BSP_InterruptControl(RZN1_IRQ_RTCATINTR, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
        if (ER_OK != ret_val)
        {
            return ret_val;
        }

        if (FIT_NO_PTR == callback)
        {
            /* No callback supplied so remove any existing callback */
            m_rtc_registers->RTCA0CTL1.BIT.RTCA0CT = RTC_PERIODIC_NONE;
            m_periodic_callback = FIT_NO_PTR;
        } else
        {
            /* callback supplied so register it */
            m_periodic_callback = callback;
            m_rtc_registers->RTCA0CTL1.BIT.RTCA0CT = pCallbackEvent->periodicSetup;
            ret_val = R_BSP_InterruptControl(RZN1_IRQ_RTCATINTR, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);
        }
    } else if (RTC_ONE_SEC_EVENT == event)
    {
        /* Always Disable interrupt as needs disabling if either new interrupt settings or supplying NULL pointer for a callback */
        ret_val = R_BSP_InterruptControl(RZN1_IRQ_RTCATINT1S, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);
        if (ER_OK != ret_val)
        {
            return ret_val;
        }

        if (FIT_NO_PTR == callback)
        {
            /* No callback supplied so remove any existing callback */
            m_rtc_registers->RTCA0CTL1.BIT.RTCA01SE = 0u;
            m_one_sec_callback = FIT_NO_PTR;
        } else
        {
            /* Callback supplied so register it */
            m_one_sec_callback = callback;
            ret_val = R_BSP_InterruptControl(RZN1_IRQ_RTCATINT1S, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);
            m_rtc_registers->RTCA0CTL1.BIT.RTCA01SE = 1u;
        }
    }
    else
#endif  /* Interrupts not supported on non-CA7 MCU */
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function rtc_register_event_callback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_reset
 *
 *  Return value:       Error status
 *
 *  Parameters:         None
 *
 *  Description:        Resets the RTC Peripheral
 *
 **********************************************************************************************************************/
ER_RET rtc_reset(void)
{
    R_SYSCTRL_RTCReset();
    /* Delay before re-enabling */
    Delay_usec(150);
    rtc_enable();
    return ER_OK;
}
/***********************************************************************************************************************
 End of function rtc_reset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:           rtc_set_clock_calib
 *
 *  Return value:       Error status
 *
 *  Parameters:         None
 *
 * Description:         Setups up clock mode (32.768KHz pr 32K+)
 *
 **********************************************************************************************************************/
ER_RET rtc_set_clock_calib(RTC_CLOCK_CALIB_T * pCalibData)
{
    if (!m_rtc_ready)
    {
        return ER_INVAL;
    }

    if (RTC_CLK_CALIB_COARSE == pCalibData->mode)
    {
        if (RTC_SCMP_FREQ_MIN > pCalibData->clkFrequency)
        {
            return ER_PARAM;
        }

        m_rtc_registers->RTCA0CTL0.BIT.RTCA0SLSB = 1u;

        /* Implement flow diagram. See RZ/N1D/S/L Peripherals user manual Rev 0.50 page 703 */
        if (0 == m_rtc_registers->RTCA0CTL0.BIT.RTCA0CEST)
        {
            return ER_INVAL;
        }

        while (1 == m_rtc_registers->RTCA0CTL2.BIT.RTCA0WSST);

        /* Now ready to write value. NOTE that bit RTCA0WSST may take up to a second to clear */
        m_rtc_registers->RTCA0SCMP.BIT.RTCA0SCMP = pCalibData->clkFrequency;
    } else
    {
        if ((RTC_SUBU_FREQ_MIN > pCalibData->clkFrequency) || (RTC_SUBU_FREQ_MAX < pCalibData->clkFrequency))
        {
            return ER_PARAM;
        }

        /* Default value */
        m_rtc_registers->RTCA0CTL0.BIT.RTCA0SLSB = 0u;
        m_rtc_registers->RTCA0SUBU.LONG = pCalibData->clkFrequency;
    }

    return ER_OK;
}
/***********************************************************************************************************************
 End of function rtc_set_clock_calib
 **********************************************************************************************************************/
