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
 * $Revision: 1298 $
 * $Date: 2019-02-25 10:17:29 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_sysctrl_rzn1_if.c
 * Description  :  System control interface functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "platform.h"
#include "iodefine.h"
#include "r_sysctrl_rzn1_if.h"
#include "r_i2c_rzn1_if.h"
#include "r_qspi_rzn1_config.h"
#include "r_sdio_rzn1_config.h"
#include "r_usb_rzn1_reg_defs.h"
#include "timer.h"
#include "r_timer_rzn1_if.h"

#ifdef CORE_CA7
#include  "cmsis_cp15.h"
#endif

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define WAIT_DIVREG_NOTBUSY (7000ul)    /* How long to wait (* BUSY_CHECK_INTERVAL) for PWRCTRL_QSPI1DIV BUSY to become free allowing DIV to be changed */
#define WAIT_SOCKET_CONN (5000ul)       /* How long to wait for socket connect */
#define BUSY_CHECK_INTERVAL (160ul)     /* Delay (in uS) between SYSCTRL Busy status checks */

#define SYSCTRL_PWRCTRL_UDL2_25MHZ *((volatile uint32_t *) (RZN1_SYSTEM_CTRL_BASE + 0x00000000 + 0xE8 ))
#define SYSCTRL_PWRSTAT_UDL2_25MHZ *((volatile uint32_t *) (RZN1_SYSTEM_CTRL_BASE + 0x00000000 + 0x15C  )) /* Type: R  */ /* Default: 0x00000000 */ /* Power (Clock/Reset) Management Status for UDL2 25MHz Core. Note: The software shall not apply clock gating or software reset to any IP unless all corresponding ports of the IP are disconnected(SCON=1'b0) and in idle(MISTAT=1'b1). */

/***********************************************************************************************************************
 Data Structures
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Local variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Static function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableIOMUXLV2
 *
 *  Return value:   void
 *
 *  Parameters:     None
 *
 *  Description:    Configure UDL to enable level 2 of pin multiplexing
 *
 **********************************************************************************************************************/
void R_SYSCTRL_EnableIOMUXLV2 (void)
{
    uint32_t reg_val = 0;
    uint32_t i;

    /* Set Slave Ready - Socket Connect Request SlvRdy_Clk_25Mhz_Udl1 9required before using level2 multiplexer*/
    reg_val = SYSCTRL_PWRCTRL_UDL2_25MHZ;
    reg_val |= 0x07; /* set the following bits :SYSCTRL_PWRCTRL_UDL2_25MHZ_CLKEN_Q,SYSCTRL_PWRCTRL_UDL2_25MHZ_RSTN_Q,SYSCTRL_PWRCTRL_UDL2_25MHZ_SLVRDY_Q*/
    SYSCTRL_PWRCTRL_UDL2_25MHZ = reg_val;

    /*  Wait for Socket Connect */
    for (i = 0; i < 5000; i++)
    {
        if (1 == (SYSCTRL_PWRSTAT_UDL2_25MHZ & 0x01))
        {
            break;
        }
        for (int i = 0; i < 5000; i++);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableBGPIO
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Configure clock enabling and interconnection for GPIO ports
 *
 **********************************************************************************************************************/
void R_SYSCTRL_EnableBGPIO (void)
{
    /* BGPIO1 */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_G = 1; /* Clock Enable for BGPIO1 - MAIN PLL clock */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_G = 1; /* Active low reset for BGPIO1 */
    systimer_delay(50);
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_G = 1; /* Indicate slave ready for BGPIO1 */
    while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_G & 0x00000001)); /* wait for socket connection */

    /* BGPIO2 */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_H = 1; /* Clock Enable for BGPIO2 - MAIN PLL clock */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_H = 1; /* Active low reset for BGPIO2 */
    systimer_delay(50);
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_H = 1; /* Indicate slave ready for BGPIO2 */
    while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_H & 0x00000001)); /* wait for socket connection */

#if (BSP_PACKAGE_PINS > 196)
    /* BGPIO3 */
    ((volatile SYSCTRL_Type *)RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.CLKEN_N = 1; /* Clock Enable for BGPIO1 - MAIN PLL clock */
    ((volatile SYSCTRL_Type *)RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.RSTN_N = 1; /* Active low reset for BGPIO3 */
    systimer_delay(50);
    ((volatile SYSCTRL_Type *)RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.SLVRDY_N = 1; /* Indicate slave ready for BGPIO3 */
    while ( !(((volatile SYSCTRL_Type *)RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_N & 0x00000001 ) ); /* wait for socket connection */
#endif
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableBGPIO
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Disable clock and interconnect from GPIO
 *
 **********************************************************************************************************************/

void R_SYSCTRL_DisableBGPIO (void)
{
    /* BGPIO1 */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_G = 0; /* Indicate slave ready for BGPIO1 */
    while ((((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_G & 0x00000001)); /* wait for socket connection */

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_G = 0; /* Active low reset for BGPIO1 */
    systimer_delay(50);
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_G = 0; /* Clock Enable for BGPIO1 - MAIN PLL clock */

    /* BGPIO2 */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_H = 0; /* Indicate slave ready for BGPIO2 */
    while ((((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_H & 0x00000001)); /* wait for socket connection */

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_H = 0; /* Active low reset for BGPIO2 */
    systimer_delay(50);
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_H = 0; /* Clock Enable for BGPIO2 - MAIN PLL clock */

#if (BSP_PACKAGE_PINS > 196)
    /* BGPIO3 */
    ((volatile SYSCTRL_Type *)RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.SLVRDY_N = 0; /* Indicate slave ready for BGPIO3 */
    while ((((volatile SYSCTRL_Type *)RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_N & 0x00000001 ) ); /* wait for socket connection */

    ((volatile SYSCTRL_Type *)RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.RSTN_N = 0; /* Active low reset for BGPIO3 */
    systimer_delay(50);
    ((volatile SYSCTRL_Type *)RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.CLKEN_N = 0; /* Clock Enable for BGPIO1 - MAIN PLL clock */

#endif
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_SetSPIClkDivider
 *
 *  Return value:   Error Status
 *
 *  Parameters:     clock_divider - Clock divider for the SPI (8 - 128)
 *
 *  Description:    Configure clock divider for SPI IP blocks
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_SetSPIClkDivider (uint8_t clock_divider)
{
    ER_RET ret_val = ER_OK;
    bool spi_master_busy = true, spi_slave_busy = true; /* Flags to indicate if the SPI is busy */

    /* Set clock divider for SPI channels 0 - 3 */
    /* Time out for polling the busy bit of the register */
    for (int i = 0; i < 0xFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3DIV.BIT.BUSY)
        {
            spi_master_busy = false;
            break;
        }
    }
    if (false == spi_master_busy)
    {
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3DIV.LONG = 0x80000000 | clock_divider; /* Divide SPI 0..3 clock */
    }
    else
    {
        ret_val = ER_SYS;
    }

    if (ret_val == ER_OK)
    {
        /* Set clock divider for SPI channels 4 - 5 */
        /* Time out for polling the busy bit of the register */
        for (int i = 0; i < 0xFF; i++)
        {
            if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR4DIV.BIT.BUSY)
            {
                spi_slave_busy = false;
                break;
            }
        }
        if (false == spi_slave_busy)
        {
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR4DIV.LONG = 0x80000000 | clock_divider; /* Divide SPI 4..5 clock */
        }
        else
        {
            ret_val = ER_SYS;
        }
    }

    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableSPI
 *
 *  Return value:   None
 *
 *  Parameters:     chan_num - SPI channel
 *
 *  Description:    Enable clock and interconnect for SPI channel
 *
 **********************************************************************************************************************/
void R_SYSCTRL_EnableSPI (uint8_t chan_num)
{
    switch (chan_num)
    {
        case 0:
            /* SPI1 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_A = 1; /* Clock Enable for SPI1 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_A = 1; /* De-assert Reset to SPI1 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.CLKEN_AM = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.RSTN_AM = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_A = 1; /* Indicate to the interconnect that Slave is ready for SPI1 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_A & 0x00000001)); /* wait for socket connection */
        break;
        case 1:
            /* SPI2 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_B = 1; /* Clock Enable for SPI2 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_B = 1; /* De-assert Reset to SPI2 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.CLKEN_AN = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.RSTN_AN = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_B = 1; /* Indicate to the interconnect that Slave is ready for SPI2 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_B & 0x00000001)); /* wait for socket connection */
        break;
        case 2:
            /* SPI3 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_C = 1; /* Clock Enable for SPI3 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_C = 1; /* De-assert Reset to SPI3 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.CLKEN_AO = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.RSTN_AO = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_C = 1; /* Indicate to the interconnect that Slave is ready for SPI3 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_C & 0x00000001)); /* wait for socket connection */
        break;
        case 3:
            /* SPI4 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_D = 1; /* Clock Enable for SPI4 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_D = 1; /* De-assert Reset to SPI4 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.CLKEN_AP = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.RSTN_AP = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_D = 1; /* Indicate to the interconnect that Slave is ready for SPI4 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_D & 0x00000001)); /* wait for socket connection */
        break;
        case 4:
            /* SPI5 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_E = 1; /* Clock Enable for SPI5 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_E = 1; /* De-assert Reset to SPI5 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR4.BIT.CLKEN_AQ = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR4.BIT.RSTN_AQ = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_E = 1; /* Indicate to the interconnect that Slave is ready for SPI5 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_E & 0x00000001)); /* wait for socket connection */
        break;
        case 5:
            /* SPI6 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_F = 1; /* Clock Enable for SPI6 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_F = 1; /* De-assert Reset to SPI6 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR4.BIT.CLKEN_AR = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR4.BIT.RSTN_AR = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_F = 1; /* Indicate to the interconnect that Slave is ready for SPI6 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_F & 0x00000001)); /* wait for socket connection */
        break;
        default:
            /* Invalid chan_num - should never get here */
        break;
    }
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableSPI
 *
 *  Return value:   None
 *
 *  Parameters:     chan_num - SPI channel
 *
 *  Description:    Disable clock and interconnect from SPI channel
 *
 **********************************************************************************************************************/
void R_SYSCTRL_DisableSPI (uint8_t chan_num)
{
    switch (chan_num)
    {
        case 0:
            /* SPI1 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_A = 0; /* Set Slave not ready for SPI1 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_A & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.RSTN_AM = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_A = 0; /* Assert Reset to SPI1 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_A = 0; /* Clock Disable for SPI1 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.CLKEN_AM = 0; /* Disable Target Clock */

        break;
        case 1:
            /* SPI2 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_B = 0; /* Set Slave not ready for SPI2 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_B & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.RSTN_AN = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_B = 0; /* Assert Reset to SPI2 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_B = 0; /* Clock Disable for SPI2 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.CLKEN_AN = 0; /* Disable Target Clock */

        break;
        case 2:
            /* SPI3 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_C = 0; /* Set Slave not ready for SPI3 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_C & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.RSTN_AO = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_C = 0; /* Assert Reset to SPI3 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_C = 0; /* Clock Disable for SPI3 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.CLKEN_AO = 0; /* Disable Target Clock */
        break;
        case 3:
            /* SPI4 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_D = 0; /* Set Slave not ready for SPI4 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_D & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.RSTN_AP = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_D = 0; /* Assert Reset to SPI4 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_D = 0; /* Clock Disable for SPI4 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR3.BIT.CLKEN_AP = 0; /* Disable Target Clock */
        break;

        case 4:
            /* SPI5 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_E = 0; /* Set Slave not ready for SPI5 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_E & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR4.BIT.RSTN_AQ = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_E = 0; /* Assert Reset to SPI5 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_E = 0; /* Clock Disable for SPI5 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR4.BIT.CLKEN_AQ = 0; /* Disable Target Clock */
        break;
        case 5:
            /* SPI6 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_F = 0; /* Set Slave not ready for SPI6 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_F & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR4.BIT.RSTN_AR = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_F = 0; /* Assert Reset to SPI6 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_F = 0; /* Clock Disable for SPI6 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR4.BIT.CLKEN_AR = 0; /* Disable Target Clock */
        break;
        default: /* Invalid channel number, should never reach here */
        break;
    }
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableMSEBI
 *
 *  Return value:   None
 *
 *  Parameters:     master - true: master, false: slave
 *
 *  Description:    Enable clock and interconnect for MSEBI master or slave
 *
 **********************************************************************************************************************/
void R_SYSCTRL_EnableMSEBI (bool master)
{
    if (master)
    {
        /* MASTER */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.CLKEN_B = 1; /* Clock Enable for MSEBI master */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.RSTN_B = 1; /* De-assert Reset to MSEBI master */
        /* Wait for Reset propagation. 50 usecs delay is recommended */
        systimer_delay(50);
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.SLVRDY_B = 1; /* Indicate to the interconnect that Slave is ready for MSEBI master access */
        while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_MSEBI.BIT.SCON_B & 0x00000001)); /* wait for socket connection */
    }
    else
    {
        /* SLAVE */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.CLKEN_A = 1; /* Clock Enable for MSEBI slave */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.MIREQ_A = 0; /* Master Idle Request to the interconnect for MSEBI Function */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.RSTN_A = 1; /* De-assert Reset to MSEBI slave */
        /* Wait for Reset propagation. 50 usecs delay is recommended */
        systimer_delay(50);
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.SLVRDY_A = 1; /* Indicate to the interconnect that Slave is ready for MSEBI slave access */
        while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_MSEBI.BIT.SCON_A & 0x00000001)); /* wait for socket connection */
    }
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableMSEBI
 *
 *  Return value:   None
 *
 *  Parameters:     master - true: master, false: slave
 *
 *  Description:    Disable clock and interconnect from MSEBI master or slave
 *
 **********************************************************************************************************************/
void R_SYSCTRL_DisableMSEBI (bool master)
{
    if (master)
    {
        /* MASTER */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.SLVRDY_B = 0; /* Set Slave not ready for MSEBI master access */
        while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_MSEBI.BIT.SCON_B & 0x00000001); /* wait for socket disconnection */

        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.RSTN_B = 0; /* Assert Reset for MSEBI master */
        /* Wait for Reset propagation. 50 usecs delay is recommended */
        systimer_delay(50);
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.CLKEN_B = 0; /* Clock Disable for MSEBI master */
    }
    else
    {
        /* SLAVE */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.SLVRDY_A = 0; /* Set Slave not ready for MSEBI slave access */
        while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_MSEBI.BIT.SCON_A & 0x00000001); /* wait for socket disconnection */

        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.RSTN_A = 0; /* Assert Reset for MSEBI slave */
        /* Wait for Reset propagation. 50 usecs delay is recommended */
        systimer_delay(50);
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.MIREQ_A = 1; /* Master Idle Request to the interconnect for MSEBI Function */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MSEBI.BIT.CLKEN_A = 0; /* Clock Disable for MSEBI slave */
    }
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableUART
 *
 *  Return value:   None
 *
 *  Parameters:     chan_num - UART channel
 *
 *  Description:    Configure clock multiplexers for UART channels
 *
 **********************************************************************************************************************/
void R_SYSCTRL_EnableUART (uint8_t chan_num)
{
    switch (chan_num)
    {
        case 0:
            /* UART1 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_H1 = 1; /* Clock Enable for UART1 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_H1 = 1; /* De-assert Reset to UART1 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_A = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_A = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_A = 1; /* Indicate to the interconnect that Slave is ready for UART1 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_A & 0x00000001)); /* wait for socket connection */
        break;
        case 1:
            /* UART2 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_I1 = 1; /* Clock Enable for UART2 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_I1 = 1; /* De-assert Reset to UART2 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_B = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_B = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_B = 1; /* Indicate to the interconnect that Slave is ready for UART2 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_B & 0x00000001)); /* wait for socket connection */
        break;
        case 2:
            /* UART3 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_J1 = 1; /* Clock Enable for UART3 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_J1 = 1; /* De-assert Reset to UART3 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_C = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_C = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_C = 1; /* Indicate to the interconnect that Slave is ready for UART3 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_C & 0x00000001)); /* wait for socket connection */
        break;
        case 3:
            /* UART4 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.CLKEN_AG1 = 1; /* Clock Enable for UART4 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.RSTN_AG1 = 1; /* De-assert Reset to UART4 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_I = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_I = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_I = 1; /* Indicate to the interconnect that Slave is ready for UART4 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_I & 0x00000001)); /* wait for socket connection */
        break;
        case 4:
            /* UART5 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.CLKEN_AH1 = 1; /* Clock Enable for UART5 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.RSTN_AH1 = 1; /* De-assert Reset to UART5 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_J = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_J = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_J = 1; /* Indicate to the interconnect that Slave is ready for UART5 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_J & 0x00000001)); /* wait for socket connection */
        break;
        case 5:
            /* UART6 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.CLKEN_AI1 = 1; /* Clock Enable for UART6 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.RSTN_AI1 = 1; /* De-assert Reset to UART6 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.CLKEN_K = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.RSTN_K = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.SLVRDY_K = 1; /* Indicate to the interconnect that Slave is ready for UART6 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_K & 0x00000001)); /* wait for socket connection */
        break;
        case 6:
            /* UART7 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.CLKEN_AJ1 = 1; /* Clock Enable for UART7 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.RSTN_AJ1 = 1; /* De-assert Reset to UART7 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.CLKEN_L = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.RSTN_L = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.SLVRDY_L = 1; /* Indicate to the interconnect that Slave is ready for UART7 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_L & 0x00000001)); /* wait for socket connection */
        break;
        case 7:
            /* UART8 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.CLKEN_AK1 = 1; /* Clock Enable for UART8- MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.RSTN_AK1 = 1; /* De-assert Reset to UART8 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.CLKEN_M = 1; /* Enable Target Clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.RSTN_M = 1; /* De-assert Reset for target module */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.SLVRDY_M = 1; /* Indicate to the interconnect that Slave is ready for UART8 access */
            while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_M & 0x00000001)); /* wait for socket connection */
        break;
        default:
            /* Invalid chan_num - should never get here */
        break;
    }
}


/***********************************************************************************************************************
* Function Name :   R_SYSCTRL_EnableLCDC
 **********************************************************************************************************************/
/*!
* @brief    Configure clock multiplexers for LCDC
* @details
* @param    clock_divider -
* @retval   Error status
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_EnableLCDC (uint8_t clock_divider)
{
    ER_RET      ret_val = ER_OK;
    bool        wait_not_busy;
    bool        wait_conn;
    uint32_t    i;

    /* configure and enable LCD controller clocks */

    /* Enable the clock for peripheral group 4 */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4.BIT.CLKEN_UI = 1;

    /* Clear 'Master Idle Request' bit*/
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4.BIT.MIREQ_UI = 0;

    /* Clear de-assert reset bit*/
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4.BIT.RSTN_UI = 1;

    /* Wait for Master Idle Request Acknowledge */
    wait_conn = true;
    for (i = 0; i < 0xFFFFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG4.BIT.MIRACK_UI)
        {
            wait_conn = false;
            break;
        }
    }
    if (wait_conn == true)
    {
        ret_val = ER_SYS;
    }
    else
    {
        /* Set clock divider for LCD ECLK */
        /* wait for busy bit to be cleared (busy if already being updated) */
        wait_not_busy = true;
        for (i = 0; i < 0xFFFF; i++)
        {
            if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4_PR1DIV.BIT.BUSY)
            {
                /* set divider */
                ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4_PR1DIV.LONG = 0x80000000 | clock_divider;
                wait_not_busy = false;
                break;
            }
        }
        if (wait_not_busy == true)
        {
            ret_val = ER_SYS;
        }
        else
        {
            /* Clock divider updated, wait for busy bit to be cleared */
            wait_not_busy = true;
            for (i = 0; i < 0xFFFF; i++)
            {
                if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4_PR1DIV.BIT.BUSY)
                {
                    wait_not_busy = false;
                    break;
                }
            }
            if (wait_not_busy == true)
            {
                ret_val = ER_SYS;
            }
            else
            {
                /* Enable LCD ECLK */
                ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4_PR1.BIT.CLKEN_AU = 1;

                /* Reset LCD_ECLK*/
                ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4_PR1.BIT.RSTN_AU = 0;
                systimer_delay(ONE_USEC);
                ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4_PR1.BIT.RSTN_AU = 1;

            }
        }
        /* Enable the LCD_HCLK */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4.BIT.CLKEN_AC = 1;
        /* Set associated SLVRDY bit so the FlexWAY bus passes on the write request */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4.BIT.SLVRDY_AC = 1;

        /* Wait for FlexWAY Socket Connection signal */
        wait_conn = true;
        for (i = 0; i < 0xFFFF; i++)
        {
            if (1 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG4.BIT.SCON_AC)
            {
                wait_conn = false;
                break;
            }
        }
        if (wait_conn == true)
        {
            ret_val = ER_SYS;
        }
        else
        {
            /* Reset LCD_HCLK*/
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4.BIT.RSTN_AC = 0;
            systimer_delay(ONE_USEC);
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4.BIT.RSTN_AC = 1;
        }
    }

    return ret_val;
}

/***********************************************************************************************************************
* Function Name :   R_SYSCTRL_DisableLCDC
 **********************************************************************************************************************/
/*!
* @brief    Turn off LCDC, Disable clocks
* @details
* @param    void
* @retval   ER_RET - Error status
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_DisableLCDC (void)
{
    ER_RET ret_val = ER_OK;
    bool wait_disconnect;
    uint32_t i;

    /* Disable the HCLK clock */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4.BIT.CLKEN_AC = 0;
    /* Clear SLVRDY */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4.BIT.SLVRDY_AC = 0;

    /* Wait for FlexWAY Socket disconnect */
    /*
    wait_disconnect = true;
    for (i = 0; i < 0xFFFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG4.BIT.SCON_AC)
        {
            wait_disconnect == false;
            break;
        }
    }
    if (wait_disconnect == true)
    {
        ret_val = ER_SYS;
    } */

    /* Set Idle Request to the NoC interconnect for Peripheral Group 4 */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4.BIT.MIREQ_UI = 1;

    /* Wait for Master Idle Request Acknowledge */
    /*for (i = 0; i < 0xFFFFF; i++)
    {
        if (1 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG4.BIT.MIRACK_UI)
        {
            wait_disconnect = false;
            break;
        }
    } */

    wait_disconnect = true;
    /* Wait for Master Idle Status signal */
    for (i = 0; i < 0xFFFFF; i++)
    {
        if (1 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG4.BIT.MISTAT_UI)
        {
            wait_disconnect = false;
            break;
        }
    }


    /* Disable the Peripheral Group 4 clock */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG4.BIT.CLKEN_UI = 0;

    if (true == wait_disconnect)
    {
        ret_val = ER_SYS;
    }
    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableTimer
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Configure clock multiplexers for Timer
 *
 **********************************************************************************************************************/

void R_SYSCTRL_EnableTimer ()
{
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG2_25MHZ.BIT.CLKEN_R = 1; /* Clock Enable for BGPIO2 - MAIN PLL clock */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG2_25MHZ.BIT.RSTN_R = 1; /* Active low reset for BGPIO2 */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG2_25MHZ.BIT.SLVRDY_R = 1; /* Indicate slave ready for BGPIO2 */
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_SetUARTClkDivider
 *
 *  Return value:   Error Status
 *
 *  Parameters:     clock_divider - Clock divider for the UART
 *
 *  Description:    Configure clock divider for UART IP blocks
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_SetUARTClkDivider (uint8_t clock_divider)
{
    ER_RET ret_val = ER_OK;
    bool pg0_busy = true, pg1_busy = true; /* Flags to indicate if the UART is busy */

    /* Set clock divider for UART channels 0 - 2 */
    /* Time out for polling the busy bit of the register */
    for (int i = 0; i < 0xFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_UARTDIV.BIT.BUSY)
        {
            pg0_busy = false;
            break;
        }
    }
    if (false == pg0_busy)
    {
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_UARTDIV.LONG = 0x80000000 | clock_divider; /* Divide UART 1..3 clock */
    }
    else
    {
        ret_val = ER_SYS;
    }

    /* Set clock divider for UART channels 3 - 7 */
    pg0_busy = true;
    pg1_busy = true;

    /* Time out for polling the busy bit of the register */
    for (int i = 0; i < 0xFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2DIV.BIT.BUSY)
        {
            pg1_busy = false;
            break;
        }
    }
    if (false == pg1_busy)
    {
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2DIV.LONG = 0x80000000 | clock_divider; /* Divide UART 4..8 clock */
    }
    else
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableUART
 *
 *  Return value:   None
 *
 *  Parameters:     chan_num - UART channel
 *
 *  Description:    Configure clock multiplexers for UART channels
 *
 **********************************************************************************************************************/
void R_SYSCTRL_DisableUART (uint8_t chan_num)
{
    switch (chan_num)
    {
        case 0:
            /* UART1 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_A = 0; /* Set Slave not ready for UART1 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_A & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_A = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_H1 = 0; /* Assert Reset to UART1 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_H1 = 0; /* Clock Disable for UART1 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_A = 0; /* Disable Target Clock */

        break;
        case 1:
            /* UART2 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_B = 0; /* Set Slave not ready for UART2 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_B & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_B = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_I1 = 0; /* Assert Reset to UART2 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_I1 = 0; /* Clock Disable for UART2 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_B = 0; /* Disable Target Clock */

        break;
        case 2:
            /* UART3 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_C = 0; /* Set Slave not ready for UART3 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_C & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_C = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_J1 = 0; /* Assert Reset to UART3 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_J1 = 0; /* Clock Disable for UART3 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_C = 0; /* Disable Target Clock */
        break;
        case 3:
            /* UART4 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_I = 0; /* Set Slave not ready for UART4 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_I & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_I = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.RSTN_AG1 = 0; /* Assert Reset to UART4 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.CLKEN_AG1 = 0; /* Clock Disable for UART4 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_I = 0; /* Disable Target Clock */
        break;

        case 4:
            /* UART5 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.SLVRDY_J = 0; /* Set Slave not ready for UART5 access */
            while ((((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_J & 0x00000001)); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.RSTN_J = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.RSTN_AH1 = 0; /* Assert Reset to UART5 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.CLKEN_AH1 = 0; /* Clock Disable for UART5 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_1.BIT.CLKEN_J = 0; /* Disable Target Clock */
        break;
        case 5:
            /* UART6 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.SLVRDY_K = 0; /* Set Slave not ready for UART6 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_K & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.RSTN_K = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.RSTN_AI1 = 0; /* Assert Reset to UART6 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.CLKEN_AI1 = 0; /* Clock Disable for UART6 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.CLKEN_K = 0; /* Disable Target Clock */
        break;
        case 6:
            /* UART7 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.SLVRDY_L = 0; /* Set Slave not ready for UART7 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_L & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.RSTN_L = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.RSTN_AJ1 = 0; /* Assert Reset to UART7 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.CLKEN_AJ1 = 0; /* Clock Disable for UART7 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.CLKEN_L = 0; /* Disable Target Clock */
        break;
        case 7:
            /* UART8 */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.SLVRDY_M = 0; /* Set Slave not ready for UART8 access */
            while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG1.BIT.SCON_M & 0x00000001); /* wait for socket disconnection */

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.RSTN_M = 0; /* Assert Reset for target module */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.RSTN_AK1 = 0; /* Assert Reset to UART8 - MAIN PLL clock */
            /* Wait for Reset propagation. 50 usecs delay is recommended */
            systimer_delay(50);

            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_PR2.BIT.CLKEN_AK1 = 0; /* Clock Disable for UART8 - MAIN PLL clock */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG1_2.BIT.CLKEN_M = 0; /* Disable Target Clock */
        break;
        default:
            /* Invalid chan_num - should never get here */
        break;
    }
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableQSPI
 *
 *  Return value:   None
 *
 *  Parameters:     chan_num - QSPI channel
 *
 *  Description:    Enables QSPI controller
 *
 **********************************************************************************************************************/
void R_SYSCTRL_EnableQSPI (uint8_t chan_num)
{
    uint32_t i;

    /* Set QSPI SYSCTRL_PWRCTRL Clock Divider to 4 for 250MHz ref_clk. (1,000MHz/4 ) */
    /* Note: this is the default setting on cold start but need to reset in case of warm start */

    if (chan_num == 0)
    {
        /* Wait with timeout for divider not busy */

        for (i = 0; i < WAIT_DIVREG_NOTBUSY; i++)
        {
            if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_QSPI1DIV.BIT.BUSY)
            {
                /* set QSPI divider to 4 */
                ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_QSPI1DIV.LONG = 0x80000000
                        | QSPI_CLOCK_DIVIDER;
                break;
            }
            /*delay();*/
        }
        /* Note: Internal QSPI clock divider is set to 0x0f (default value) for divide by 32 */
        /* This is done in the QSPI driver init function. */

        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_QSPI1.LONG = 0x0000003ful; /* release reset, enable clocks, request socket connection */
        while ( !(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_QSPI1.BIT.SCON_A & 0x00000001)); /* wait for socket connection */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_QSPI1.LONG = 0x00000037; /* release idle request */
        while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_QSPI1.LONG & 0x00000006); /* wait for idle acknowledge */
    }
#ifdef RZN1S
    else if (chan_num == 1)
    {
        /* Wait with timeout for divider not busy */

        for (i = 0; i < WAIT_DIVREG_NOTBUSY; i++)
        {
            if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_QSPI2DIV.BIT.BUSY)
            {
                /* set QSPI divider to 4 */
                ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_QSPI2DIV.LONG = 0x80000000 | QSPI_CLOCK_DIVIDER;
                break;
            }
            /*delay();*/
        }
        /* Note: Internal QSPI clock divider is set to 0x0f (default value) for divide by 32 */
        /* This is done in the QSPI driver init function. */

        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_QSPI2.LONG = 0x0000003ful; /* release reset, enable clocks, request socket connection */
        while (!(((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_QSPI2.BIT.SCON_A & 0x00000001)); /* wait for socket connection */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_QSPI2.LONG = 0x00000037; /* release idle request */
        while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_QSPI2.LONG & 0x00000006); /* wait for idle acknowledge */
    }
#endif

    return;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableQSPI
 *
 *  Return value:   None
 *
 *  Parameters:     chan_num - QSPI channel
 *
 *  Description:    Disables QSPI controller
 *
 **********************************************************************************************************************/
void R_SYSCTRL_DisableQSPI (uint8_t chan_num)
{
    uint32_t i;

    if (chan_num == 0)
    {
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_QSPI1.BIT.SLVRDY_A = 0;

        /* Wait for disconnection */
        for (i = 0; i < 0xFFFFF; i++)
        {
            if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_QSPI1.BIT.SCON_A)
            {
                break;
            }
        }
    }
#ifdef RZN1S
    else if (chan_num == 1)
    {
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_QSPI2.BIT.SLVRDY_A = 0;

        /* Wait for disconnection */
        for (i = 0; i < 0xFFFFF; i++)
        {
            if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_QSPI2.BIT.SCON_A)
            {
                break;
            }
        }
    }
#endif
    return;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableADC
 *
 *  Return value:   Error Status
 *
 *  Parameters:     None
 *
 *  Description:    Enables ADC controller
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_EnableADC (void)
{
    ER_RET ret_val = ER_OK;
    uint32_t i;
    bool wait_connect = true;

    /*ADC:  Enable clock, de-assert reset and connect to NoC */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_F = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_F = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.CLKEN_M = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.RSTN_M = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_F = 1;

    /* Wait for the ADC IP to connect */
    for (i = 0; i < 0xFFFFF; i++)
    {
        if (1 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_F)
        {
            wait_connect = false;
            break;
        }
    }

    if (true == wait_connect)
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_SetADCClkDivider
 *
 *  Return value:   Error Status
 *
 *  Parameters:     clock_divider - Clock divider for the SPI (50 - 250)
 *
 *  Description:    Configure clock divider for ADC IP blocks
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_SetADCClkDivider (uint8_t clock_divider)
{
    ER_RET ret_val = ER_OK;
    bool divider_busy = true;
    uint32_t i;

    for (i = 0; i < 0xFFFFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_ADCDIV.BIT.BUSY)
        {
            divider_busy = false;
            break;
        }
    }

    if (false == divider_busy)
    {
        /* Now set the divider */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_ADCDIV.BIT.DIV = clock_divider;
    }
    else
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableADC
 *
 *  Return value:   Error Status
 *
 *  Parameters:     None
 *
 *  Description:    Disables ADC controller
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_DisableADC (void)
{
    ER_RET ret_val = ER_OK;
    uint32_t i;
    bool wait_connect = true;

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_F = 0;

    /* Wait for the ADC IP to connect */
    for (i = 0; i < 0xFFFFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_F)
        {
            wait_connect = false;
            break;
        }
    }

    /*ADC:  Disable clock and assert reset */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_F = 0;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.RSTN_M = 0;
    systimer_delay(50);

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_F = 0;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.CLKEN_M = 0;

    if (true == wait_connect)
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableI2C
 *
 *  Return value:   Error Status
 *
 *  Parameters:     chan_num - I2C channel
 *
 *  Description:    Enables I2C controller
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_EnableI2C (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    uint32_t i;
    bool wait_connect = true;

    if (I2C_CHAN_1 == chan_num)
    {
        /*i2c1:  Enable clock, de-assert reset and connect to NoC */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_D = 1;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_D = 1;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.CLKEN_K = 1;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.RSTN_K = 1;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_D = 1;

        /* Wait for the I2C1 IP to connect */
        for (i = 0; i < 0xFFFFF; i++)
        {
            if (1 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_D)
            {
                wait_connect = false;
                break;
            }
        }
    }
    else if (I2C_CHAN_2 == chan_num)
    {
        /*i2c2:  Enable clock, de-assert reset and connect to NoC */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_E = 1;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_E = 1;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.CLKEN_L = 1;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.RSTN_L = 1;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_E = 1;

        /* Wait for the I2C2 IP to connect */
        for (i = 0; i < 0xFFFFF; i++)
        {
            if (1 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_E)
            {
                wait_connect = false;
                break;
            }
        }
    }

    if (true == wait_connect)
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_SetI2CClkDivider
 *
 *  Return value:   Error Status
 *
 *  Parameters:     clock_divider - Clock divider for I2C
 *
 *  Description:    Setup I2C Clock
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_SetI2CClkDivider (uint8_t i2c_clock_divider)
{
    ER_RET ret_val = ER_OK;
    bool divider_busy = true;
    uint32_t i;

    for (i = 0; i < 0xFFFFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_I2CDIV.BIT.BUSY)
        {
            divider_busy = false;
            break;
        }
    }
    if (false == divider_busy)
    {
        /* Now set the divider */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_I2CDIV.BIT.DIV = i2c_clock_divider;
    }
    else
    {
        ret_val = ER_SYS;
    }
    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableI2C
 *
 *  Return value:   Error Status
 *
 *  Parameters:     chan_num - I2C channel
 *
 *  Description:    Disables I2C controller
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_DisableI2C (uint8_t chan_num)
{
    ER_RET ret_val = ER_OK;
    uint32_t i;
    bool wait_connect = true;

    if (I2C_CHAN_1 == chan_num)
    {
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_D = 0;

        /* Wait for the disconnection */
        for (i = 0; i < 0xFFFFF; i++)
        {
            if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_D)
            {
                wait_connect = false;
                break;
            }
        }

        /*i2c1:  Disable clock and assert reset */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_D = 0;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.RSTN_K = 0;
        systimer_delay(50);

        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.CLKEN_K = 0;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_D = 0;
    }
    else if (I2C_CHAN_1 == chan_num)
    {
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.SLVRDY_E = 0;

        /* Wait for disconnection */
        for (i = 0; i < 0xFFFFF; i++)
        {
            if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG0.BIT.SCON_D)
            {
                wait_connect = false;
                break;
            }
        }

        /*i2c1:  Disable clock and assert reset */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.RSTN_E = 0;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.RSTN_L = 0;
        systimer_delay(50);

        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_1.BIT.CLKEN_L = 0;
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_PG0_0.BIT.CLKEN_E = 0;
    }

    if (true == wait_connect)
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableGMAC
 *
 *  Return value:   Error Status
 *
 *  Parameters:     None.
 *
 *  Description:    Enable GMAC interfaces
 *
 **********************************************************************************************************************/

void R_SYSCTRL_EnableGMAC ()
{
    /*Enable clock for RGMII/GMII*/
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_EETH.BIT.CLKEN_A = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_EETH.BIT.CLKEN_B = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_EETH.BIT.CLKEN_C = 1;

    /*Enable clock for GMAC1*/
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC1.BIT.CLKEN_A = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC1.BIT.RSTN_A = 1;
    systimer_delay(50);
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC1.BIT.SLVRDY_A = 1;

    /* Wait for the GMAC1 IP to connect */
    while ( !((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_MAC1.BIT.SCON_A);

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC1.BIT.MIREQ_A = 0;

    while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_MAC1.BIT.MIRACK_A);

    /*Enable clock for GMAC2 */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC2.BIT.CLKEN_A = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC2.BIT.RSTN_A = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC2.BIT.SLVRDY_A = 1;

    /* Wait for the GMAC2 IP to connect */
    while ( !((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_MAC2.BIT.SCON_A);

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC2.BIT.MIREQ_A = 0;

    while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_MAC2.BIT.MIRACK_A);

}

void R_RIN_Reset ()
{
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SWITCHCTRL.BIT.RSTN_ETH = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SWITCHCTRL.BIT.RSTN_CLK25 = 1;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_Switch
 *
 *  Return value:   Error Status
 *
 *  Parameters:     None.
 *
 *  Description:    Enables Switch
 *
 **********************************************************************************************************************/

void R_SYSCTRL_Switch ()
{
    /*Enable clock for R-IN*/
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RINCTRL.BIT.CLKEN_A = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RINCTRL.BIT.RSTN_A = 1;
    systimer_delay(50);
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RINCTRL.BIT.SLVRDY_A = 1;

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SWITCH.BIT.CLKEN_B = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SWITCH.BIT.RSTN_B = 1;
    systimer_delay(50);

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SWITCH.BIT.CLKEN_A = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SWITCH.BIT.SLVRDY_A = 1;

    /* Wait for the MAC1 IP to connect */
    while ( !((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_SWITCH.BIT.SCON_A);

}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EthReg
 *
 *  Return value:   Error Status
 *
 *  Parameters:     None.
 *
 *  Description:    Enables Switch
 *
 **********************************************************************************************************************/

void R_SYSCTRL_EthReg ()
{

    /*Enable clock for Ethernet Control Reg*/
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SWITCHCTRL.BIT.CLKEN_A = 1;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SWITCHCTRL.BIT.RSTN_A = 1;
    systimer_delay(50);
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SWITCHCTRL.BIT.SLVRDY_A = 1;

    while ( !((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_SWITCHCTRL.BIT.SCON_A);
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableGMAC
 *
 *  Return value:   Error Status
 *
 *  Parameters:     None.
 *
 *  Description:    Disables GMAC interfaces
 *
 **********************************************************************************************************************/

void R_SYSCTRL_DisableGMAC ()
{
    /*Enable clock for MAC1*/
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC1.BIT.CLKEN_A = 0;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC1.BIT.RSTN_A = 0;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC1.BIT.SLVRDY_A = 0;

    /* Wait for the MAC1 IP to disconnect */
    while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_MAC1.BIT.SCON_A);

    /*Enable clock for DMAC2 */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC2.BIT.CLKEN_A = 0;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC2.BIT.RSTN_A = 0;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_MAC2.BIT.SLVRDY_A = 0;

    /* Wait for the DMAC2 IP to disconnect */
    while (((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_MAC2.BIT.SCON_A);

}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableDMA
 *
 *  Return value:   Error Status
 *
 *  Parameters:     DMAC - DMA controller
 *
 *  Description:    Activate the DMA interconnect
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_EnableDMA (uint8_t DMAC)
{
    ER_RET ret_val = ER_OK;

    switch (DMAC)
    {
        case 0:
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.CLKEN_A = 1; /* DMAC1 */
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.MIREQ_A = 0;
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.RSTN_A = 1;
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.SLVRDY_A = 1;
        break;
        case 1:
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.CLKEN_B = 1; /* DMAC2 */
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.MIREQ_B = 0;
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.RSTN_B = 1;
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.SLVRDY_B = 1;
        break;
        default:
            ret_val = ER_PARAM;
    }
    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableDMA
 *
 *  Return value:   Error Status
 *
 *  Parameters:     DMAC - DMA controller
 *
 *  Description:    Disable the DMA interconnect
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_DisableDMA (uint8_t DMAC)
{
    ER_RET ret_val = ER_OK;

    switch (DMAC)
    {
        case 0:
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.CLKEN_A = 0; /* DMAC1 */
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.MIREQ_A = 1;
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.RSTN_A = 0;
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.SLVRDY_A = 0;
        break;
        case 1:
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.CLKEN_B = 0; /* DMAC2 */
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.MIREQ_B = 1;
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.RSTN_B = 0;
            ((volatile SYSCTRL_Type*) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_DMA.BIT.SLVRDY_B = 0;
        break;
        default:
            ret_val = ER_PARAM;
    }
    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_ConfigDMAMux
 *
 *  Return value:   Error Status
 *
 *  Parameters:     type of request
 *
 *  Description:    Configure the DMA interconnect
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_ConfigDMAMux (uint8_t function_request)
{
    ER_RET ret_val = ER_OK;
    uint32_t DMAMUX;
    uint32_t shift = (16 * ((function_request >> DMA_MUX_DMA_BIT) & DMA_MUX_DMA_MASK))
            + ((function_request >> DMA_MUX_SRC_REQ_BIT) & DMA_MUX_SRC_REQ_MASK);

    DMAMUX = ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->CFG_DMAMUX.LONG;
    if (1 == ((function_request >> DMA_MUX_REQ_VAL_BIT) & DMA_MUX_REQ_VAL_MASK))
    {
        DMAMUX |= 0x01 << shift;
    }
    else
    {
        DMAMUX &= ~(0x01 << shift);
    }
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->CFG_DMAMUX.LONG = DMAMUX;

    return ret_val;
}
/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableSDIO
 *
 *  Return value:   Error Status
 *
 *  Parameters:     sdio_instance - Which sdio host controller to enable
 *
 *  Description:    Activate the SDIO interconnect
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_EnableSDIO (uint8_t sdio_instance)
{
    ER_RET ret_val = ER_OK;

    switch (sdio_instance)
    {
        case 0:
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.CLKEN_A = 0x01; /* Internal clock enable */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.RSTN_A = 0x01; /* Do not reset interconnect */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.SLVRDY_A = 0x01; /* Slave ready */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.MIREQ_A = 0x00; /* Master active */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.CLKEN_B = 0x01; /* External clock enable */
        break;
        case 1:
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO2.BIT.CLKEN_A = 0x01; /* Internal clock enable */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO2.BIT.RSTN_A = 0x01; /* Do not reset interconnect */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO2.BIT.SLVRDY_A = 0x01; /* Slave ready */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO2.BIT.MIREQ_A = 0x00; /* Master active */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO2.BIT.CLKEN_B = 0x01; /* External clock enable */
        break;
        default:
            ret_val = ER_PARAM;
    }

    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableSDIO
 *
 *  Return value:   Error Status
 *
 *  Parameters:     sdio_instance - Which sdio host controller to disable
 *
 *  Description:    Deactivate the SDIO interconnect
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_DisableSDIO (uint8_t sdio_instance)
{
    ER_RET ret_val = ER_OK;

    switch (sdio_instance)
    {
        case 0:
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.CLKEN_A = 0x00; /* Internal clock disable */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.RSTN_A = 0x00; /* Reset interconnect */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.SLVRDY_A = 0x00; /* Slave not ready */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.MIREQ_A = 0x01; /* Master inactive */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.CLKEN_B = 0x00; /* External clock disable */
        break;
        case 1:
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.CLKEN_A = 0x00; /* Internal clock disable */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.RSTN_A = 0x00; /* Reset interconnect */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.SLVRDY_A = 0x00; /* Slave not ready */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.MIREQ_A = 0x01; /* Master inactive */
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_SDIO1.BIT.CLKEN_B = 0x00; /* External clock disable */
        break;
        default:
            ret_val = ER_PARAM;
    }

    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_SetSDIOBaseClk
 *
 *  Return value:   Error status
 *
 *  Parameters:     sdio_instance - Which sdio controller to configure the clock for
 *                  base_clock - The base clock frequency for the SDIO controller (MHz)
 *
 *  Description:    Set the SDIO base Clock Frequency
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_SetSDIOBaseClk (uint8_t sdio_instance)
{
    ER_RET ret_val = ER_OK;

    switch (sdio_instance)
    {
        case 0:
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->CFG_SDIO1.BIT.BASECLKFREQ =
            SDIO_BASE_CLOCK_FREQ;
        break;
        case 1:
            ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->CFG_SDIO2.BIT.BASECLKFREQ =
            SDIO_BASE_CLOCK_FREQ;
        break;
        default:
            ret_val = ER_PARAM;
    }

    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableUSBf
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *
 *  Description:    Setup USB 2.0 Function controller
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_EnableUSBf (void)
{
    ER_RET ret_val = ER_OK;
    bool wait_connect = true;
    uint32_t i;

    /* Clock Enable for USB_HCLKF (Internal bus - USB Function) */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_USB.BIT.CLKEN_B = 1;

    /* Master Idle Request to the interconnect for USB Function */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_USB.BIT.MIREQ_B = 0;

    /* Wait for Master Idle Request Acknowledge for USB Function */
    for (i = 0; i < 0xFFFFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_USB.BIT.MIRACK_B)
        {
            wait_connect = false;
            break;
        }
    }

    if (false == wait_connect)
    {
        /* Configure USB Ports */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->CFG_USB.BIT.H2MODE = 0; /* 0: Port1 Function, Port2 Host */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->CFG_USB.BIT.FRCLK48MOD = 1; /* PLL of USBPHY operates regardless of USB state */

        ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.EPC_RST = 1; /* Assert EPC block Reset */
        ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.PLL_RST = 1; /* Assert USB PLL Reset */

        /* wait 1 usec */
        systimer_delay(ONE_USEC);

        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->CFG_USB.BIT.DIRPD = 0; /* Power-up USB subsystem */

        /* wait 1 msec */
        systimer_delay(ONE_MSEC);

        ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.EPC_RST = 0; /* Release EPC Reset */
        ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.PLL_RST = 0; /* Release PLL Reset */

        wait_connect = true;
        /* Wait for USB PLL locked */
        for (i = 0; i < 0xFFFFF; i++)
        {
            if (1 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->USBSTAT.BIT.PLL_LOCK)
            {
                wait_connect = false;
                break;
            }
        }
    }

    if (true == wait_connect)
    {
        ret_val = ER_SYS;
    }
    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableUSBf
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Disables USB Function controller
 *
 **********************************************************************************************************************/
void R_SYSCTRL_DisableUSBf (void)
{
    ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.EPC_RST = 1;
    ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.PLL_RST = 1;

    /* wait 1 usec */
    systimer_delay(ONE_USEC);

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->CFG_USB.BIT.DIRPD = 1; /* Power-down USB subsystem */

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_USB.BIT.MIREQ_B = 1;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableUSBh
 *
 *  Return value:   Error status
 *
 *  Parameters:     None
 *
 *  Description:    Setup USB 2.0 Host controller
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_EnableUSBh(void)
{
    ER_RET ret_val = ER_OK;
    bool wait_connect = true;
    uint32_t i;

    /* Clock Enable for USB Host */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_USB.BIT.CLKEN_A = 1;

    /* Master Idle Request to the interconnect for USB Host */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_USB.BIT.MIREQ_A = 0;

    /* Wait for Master Idle Request Acknowledge for USB Host */
    for (i = 0; i < 0xFFFFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_USB.BIT.MIRACK_A) {
            wait_connect = false;
            break;
        }
    }

    if (false == wait_connect)
    {
        /* Configure USB Ports */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->CFG_USB.BIT.H2MODE      = 0; /* 0: Port1 Function, Port2 Host */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->CFG_USB.BIT.FRCLK48MOD  = 1; /* PLL of USBPHY operates regardless of USB state */

        ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.EPC_RST = 1; /* Assert EPC block Reset */
        ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.PLL_RST = 1; /* Assert USB PLL Reset */

        /* wait 1 usec */
        systimer_delay(ONE_USEC);

        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->CFG_USB.BIT.DIRPD = 0; /* Power-up USB subsystem */

        /* wait 1 msec */
        systimer_delay(ONE_MSEC);

        ((volatile AHB_EPC_EPCTR_Type *)USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.EPC_RST = 0; /* Release EPC Reset */
        ((volatile AHB_EPC_EPCTR_Type *)USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.PLL_RST = 0; /* Release PLL Reset */

        wait_connect = true;
        /* Wait for USB PLL locked */
        for (i = 0; i < 0xFFFFF; i++)
        {
            if (1 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->USBSTAT.BIT.PLL_LOCK)
            {
                wait_connect = false;
                break;
            }
        }
    }

    if (true == wait_connect)
    {
        ret_val = ER_SYS;
    }

    return ret_val;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableUSBh
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Disables USB Host controller
 *
 **********************************************************************************************************************/
void R_SYSCTRL_DisableUSBh(void)
{

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_USB.BIT.MIREQ_A = 1;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_WDTResetConfig
 *
 *  Return value:   None
 *
 *  Parameters:     reset_en - Enable or Disable
 *
 *  Description:    Mask or unmask the Watchdog timer's reset ability
 *
 **********************************************************************************************************************/
void R_SYSCTRL_WDTResetConfig (bool reset_en)
{
    if (reset_en)
    {
#ifdef CORE_CA7
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTCTRL.BIT.WDA7RST_REQ = 0u; /* Ensure no pending system reset */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.MRESET_EN = 1u; /* Global enable for internal reset generation */
#ifdef BSP_PLAT_RZN1DDB
        if(R_Get_CPUID())
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.WDA7RST_EN = 2u; /* Unmask watchdog reset generation */
        else
#endif
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.WDA7RST_EN = 1u; /* Unmask watchdog reset generation */

#else
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTCTRL.BIT.WDM3RST_REQ = 0u; /* Ensure no pending system reset */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.MRESET_EN = 1u; /* Global enable for internal reset generation */
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.WDM3RST_EN = 1u; /* Unmask watchdog reset generation */
#endif

    }
    else
    {

#ifdef CORE_CA7
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.WDA7RST_EN = 0u; /* Mask watchdog reset generation */
#else
        ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.WDM3RST_EN = 0u; /* Mask watchdog reset generation */
#endif

    }
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_WDTReset
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Unmask watchdog reset generation (To be called when a reset is pending)
 *
 **********************************************************************************************************************/
void R_SYSCTRL_WDTReset (void)
{

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.MRESET_EN = 1u; /* Global enable for internal reset generation */
#ifdef CORE_CA7
#ifdef BSP_PLAT_RZN1DDB
    if(R_Get_CPUID())
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.WDA7RST_EN = 2u; /* Unmask watchdog reset generation */
    else
#endif
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.WDA7RST_EN = 1u; /* Unmask watchdog reset generation */
#else
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.WDM3RST_EN = 1u; /* Unmask watchdog reset generation */
#endif
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_SystemReset
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Resets the system
 *
 **********************************************************************************************************************/
void R_SYSCTRL_SystemReset (void)
{

    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.MRESET_EN = 1u; /* Global enable for internal reset generation */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTEN.BIT.SWRST_EN = 1u; /* Unmask software reset generation */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->RSTCTRL.BIT.SWRST_REQ = 1u; /* Set software reset pending to force reset */

}

#ifdef CORE_CA7
uint32_t R_Get_CPUID (void)
{
    uint32_t cpuid;
    cpuid = __get_MPIDR();
    return (cpuid & 0x03);
}
#endif

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableRTC
 *
 *  Return value:   Error Status
 *
 *  Parameters:     None
 *
 *  Description:    Activate the RTC interconnect
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_EnableRTC (void)
{
    /* Wait for Power Good */
    while ( !((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_RTC.BIT.PWR_GOOD);

    /* Enable clock first as subsystem may depend on it running */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RTC.BIT.CLKEN_RTC = 1u;
    /* Special sequence needed - see RZ/N1D/S/L System Introduction user manual Rev 0.50 page162 */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RTC.BIT.RSTN_FW_RTC = 1u;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RTC.BIT.IDLE_REQ = 0u;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RTC.BIT.RST_RTC = 0u;

    return ER_OK;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableRTC
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Disable the RTC interconnect
 *
 **********************************************************************************************************************/
void R_SYSCTRL_DisableRTC (void)
{
    /* Put RTC into idle mode*/
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RTC.BIT.RST_RTC = 0u;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RTC.BIT.IDLE_REQ = 1u;
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RTC.BIT.RSTN_FW_RTC = 0u;

    /* Wait until idle is reported before turning off clock. See RZ/N1D/S/L System Introduction user manual Rev 0.50 page123 */
    while ( !((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_RTC.BIT.RTC_IDLE);

    /* Disable clock last as subsystem may depend on it running */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RTC.BIT.CLKEN_RTC = 0u;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_RTCReset
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Reset RTC Peripheral
 *
 **********************************************************************************************************************/
void R_SYSCTRL_RTCReset (void)
{
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RTC.BIT.RST_RTC = 1u; /* Initiate a reset of the RTC */
    ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRCTRL_RTC.BIT.RST_RTC = 0u;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_EnableCAN
 *
 *  Return value:   Error Status
 *
 *  Parameters:     None
 *
 *  Description:    Activate the CAN interconnect
 *
 **********************************************************************************************************************/
ER_RET R_SYSCTRL_EnableCAN (void)
{
    uint32_t i;
    bool wait_connect = true;

    /* CAN1 */
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.CLKEN_Z = 1;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.SLVRDY_Z = 0;
    while (SYSCTRL->PWRSTAT_PG3_48MHZ.BIT.SCON_Z);
    /* Wait for the CAN1 IP to disconnect */
    for (i = 0; i < 0xFFFFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG3_48MHZ.BIT.SCON_Z)
        {
            wait_connect = false;
            break;
        }
    }

    if (true == wait_connect)
    {
        return ER_SYS;
    }

    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.RSTN_Z = 0;
    /* wait 6 usec */
    systimer_delay(ONE_USEC * 6);

    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.RSTN_Z = 1;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.SLVRDY_Z = 1;
    /* Wait for the CAN1 IP to connect */
    for (i = 0; i < 0xFFFFF; i++)
    {
        if (1 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG3_48MHZ.BIT.SCON_Z)
        {
            wait_connect = false;
            break;
        }
    }

    if (true == wait_connect)
    {
        return ER_SYS;
    }

    /* CAN2 */
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.CLKEN_AA = 1;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.SLVRDY_AA = 0;
    while (SYSCTRL->PWRSTAT_PG3_48MHZ.BIT.SCON_AA);
    /* Wait for the CAN2 IP to disconnect */
    for (i = 0; i < 0xFFFFF; i++)
    {
        if (0 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG3_48MHZ.BIT.SCON_AA)
        {
            wait_connect = false;
            break;
        }
    }

    if (true == wait_connect)
    {
        return ER_SYS;
    }

    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.RSTN_AA = 0;
    /* wait 6 usec */
    systimer_delay(ONE_USEC * 6);

    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.RSTN_AA = 1;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.SLVRDY_AA = 1;
    /* Wait for the CAN2 IP to connect */
    for (i = 0; i < 0xFFFFF; i++)
    {
        if (1 == ((volatile SYSCTRL_Type *) RZN1_SYSTEM_CTRL_BASE)->PWRSTAT_PG3_48MHZ.BIT.SCON_AA)
        {
            wait_connect = false;
            break;
        }
    }

    if (true == wait_connect)
    {
        return ER_SYS;
    }

    return ER_OK;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_DisableCAN
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Disable the CAN interconnect
 *
 **********************************************************************************************************************/
void R_SYSCTRL_DisableCAN (void)
{
    /* CAN1 */
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.CLKEN_Z = 0;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.RSTN_Z = 0;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.SLVRDY_Z = 0;

    /*CAN2 */
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.CLKEN_AA = 0;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.RSTN_AA = 0;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.SLVRDY_AA = 0;
}

/***********************************************************************************************************************
 *
 *  Function:       R_SYSCTRL_ResetCAN
 *
 *  Return value:   None
 *
 *  Parameters:     None
 *
 *  Description:    Resets the CAN interconnect
 *
 **********************************************************************************************************************/
void R_SYSCTRL_ResetCAN (void)
{
    /* CAN1 */
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.CLKEN_Z = 1;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.SLVRDY_Z = 0;
    while (SYSCTRL->PWRSTAT_PG3_48MHZ.BIT.SCON_Z);
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.RSTN_Z = 0;
    /* wait 6 usec */
    systimer_delay(ONE_USEC * 6);
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.RSTN_Z = 1;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.SLVRDY_Z = 1;
    while ( !SYSCTRL->PWRSTAT_PG3_48MHZ.BIT.SCON_Z);

    /* CAN2*/
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.CLKEN_AA = 1;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.SLVRDY_AA = 0;
    while (SYSCTRL->PWRSTAT_PG3_48MHZ.BIT.SCON_AA);
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.RSTN_AA = 0;
    /* wait 6 usec */
    systimer_delay(ONE_USEC * 6);
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.RSTN_AA = 1;
    SYSCTRL->PWRCTRL_PG3_48MHZ.BIT.SLVRDY_AA = 1;
    while ( !SYSCTRL->PWRSTAT_PG3_48MHZ.BIT.SCON_AA);
}
