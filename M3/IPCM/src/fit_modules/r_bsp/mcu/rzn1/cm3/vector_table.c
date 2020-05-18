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
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  vector_table.c
 * Description  :  Vector Table for Cortex M3
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#pragma language=extended
#pragma segment="CSTACK"

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include  <stdint.h>
#include  "platform.h"
#include  "mcu_interrupts_if.h"

/***********************************************************************************************************************
Macro definitions
 **********************************************************************************************************************/
#define WEAK __attribute__ ((weak, alias("dummy_handler")))

/***********************************************************************************************************************
Typedef definitions
 **********************************************************************************************************************/
typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

/***********************************************************************************************************************
Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Externals
 **********************************************************************************************************************/
extern void __iar_program_start( void );

/***********************************************************************************************************************
Private global variables and functions
 **********************************************************************************************************************/
static void nmi_handler(void) ;
static void hardfault_handler(void) ;
static void memmanage_handler(void) ;
static void busfault_handler(void) ;
static void usagefault_handler(void) ;
void svc_handler(void) WEAK;
void debugmon_handler(void) WEAK;
void pendsv_handler(void) WEAK;
void systick_handler(void) WEAK;
static void irq_handler_adc(void);                  /* 0 */
static void irq_handler_i2c0(void);                 /* 1 */
static void irq_handler_i2c1(void);                 /* 2 */
void irq_handler_safety_filtering(void) WEAK;       /* 3 */
void irq_handler_sgpio0(void) WEAK;                 /* 4 */
void irq_handler_sgpio1(void) WEAK;                 /* 5 */
static void irq_handler_uart0(void);                /* 6 */
static void irq_handler_uart1(void);                /* 7 */
static void irq_handler_uart2(void);                /* 8 */
void irq_handler_deltasigma(void) WEAK;             /* 9 */
void irq_handler_pwmpto(void) WEAK;                 /* 10 */
void irq_handler_ecc_4mb(void) WEAK;                /* 11 */
void irq_handler_ecc_2mb(void) WEAK;                /* 12 */
void irq_handler_cm3_lockup(void) WEAK;             /* 13 */
void irq_handler_cm3_tring_0(void) WEAK;            /* 14 */
void irq_handler_cm3_tring_1(void) WEAK;            /* 15 */
void irq_handler_hwrtos_bramerr(void) WEAK;         /* 16 */
void irq_handler_hwrtos_bufdma(void) WEAK;          /* 17 */
void irq_handler_hwrtos_bufdmaerr(void) WEAK;       /* 18 */
void irq_handler_hwrtos_ethmii(void) WEAK;          /* 19 */
void irq_handler_hwrtos_ethpause(void) WEAK;        /* 20 */
void irq_handler_hwrtos_ethrxderr(void) WEAK;       /* 21 */
void irq_handler_hwrtos_ethrxdma(void) WEAK;        /* 22 */
void irq_handler_hwrtos_ethrxerr(void) WEAK;        /* 23 */
void irq_handler_hwrtos_ethrxfifo(void) WEAK;       /* 24 */
void irq_handler_hwrtos_ethtx(void) WEAK;           /* 25 */
void irq_handler_hwrtos_ethtxderr(void) WEAK;       /* 26 */
void irq_handler_hwrtos_ethtxdma(void) WEAK;        /* 27 */
void irq_handler_hwrtos_ethtxfifo(void) WEAK;       /* 28 */
void irq_handler_hwrtos_ethtxfifoerr(void) WEAK;    /* 29 */
void irq_handler_hwrtos(void) WEAK;                 /* 30 */
void irq_handler_hwrtos_macdmarxfrm(void) WEAK;     /* 31 */
void irq_handler_hwrtos_tm_lpi_ast(void) WEAK;      /* 32 */
void irq_handler_hwrtos_tm_lpi_deast(void) WEAK;    /* 33 */
void irq_handler_sbd0(void);                    /* 34 */
void irq_handler_lpi0(void);                    /* 35 */
void irq_handler_pmt0(void);                    /* 36 */
void irq_handler_sbd1(void);                    /* 37 */
void irq_handler_lpi1(void);                    /* 38 */
void irq_handler_pmt1(void);                    /* 39 */
void irq_handler_switchdlr(void) WEAK;              /* 40 */
void irq_handler_switch(void) WEAK;                 /* 42 */
void irq_handler_switchprp(void) WEAK;              /* 43 */
void irq_handler_ethswhub(void) WEAK;               /* 44 */
void irq_handler_ethswptrn(void) WEAK;              /* 45 */
void irq_handler_cat_rst(void) WEAK;                /* 46 */
void irq_handler_cat_sync_0(void) WEAK;             /* 47 */
void irq_handler_cat_sync_1(void) WEAK;             /* 48 */
void irq_handler_cat_wdt_s3_divclk(void) WEAK;      /* 49 */
void irq_handler_cat_eof_s3_conclk_hsr_ptp(void) WEAK;  /* 50 */
void irq_handler_cat_sof_s3_0_hsr_cpu(void) WEAK;       /* 51 */
void irq_handler_cat_s3_1(void) WEAK;               /* 52 */
void irq_handler_nocfirewall(void) WEAK;            /* 53 */
void irq_handler_crypto0(void) WEAK;                /* 54 */
void irq_handler_crypto1(void) WEAK;                /* 55 */
static void irq_handler_dma0(void);                 /* 56 */
static void irq_handler_dma1(void);                 /* 57 */
void irq_handler_nand(void) WEAK;                   /* 58 */
void irq_handler_ipcm_0(void) WEAK;                 /* 59 */
void irq_handler_ipcm_1(void) WEAK;                 /* 60 */
void irq_handler_ipcm_2(void) WEAK;                 /* 61 */
void irq_handler_msebim(void) WEAK;                 /* 62 */
static void irq_handler_msebis(void);               /* 63 */
void irq_handler_qspi0(void) WEAK;                  /* 64 */
void irq_handler_qspi1(void) WEAK;                  /* 65 */
static void irq_handler_rtcatintal(void);           /* 66 */
static void irq_handler_rtcatintr(void);            /* 67 */
static void irq_handler_rtcatint1s(void);           /* 68 */
static void irq_handler_sdio0(void);                /* 69 */
static void irq_handler_sdio0_wkup(void);           /* 70 */
static void irq_handler_sdio1(void);                /* 71 */
static void irq_handler_sdio1_wkup(void);           /* 72 */
void irq_handler_watchdog_resetn_0(void) WEAK;      /* 73 */
void irq_handler_watchdog_resetn_1(void) WEAK;      /* 74 */
static void irq_handler_watchdog_cm3_resetn(void);  /* 75 */
void irq_handler_ddrsub(void) WEAK;                 /* 76 */
static void irq_handler_usbf_epc(void);             /* 77 */
static void irq_handler_usbf(void);                 /* 78 */
static void irq_handler_usbh_bind(void);            /* 79 */
static void irq_handler_spi0(void);                 /* 80 */
static void irq_handler_spi1(void);                 /* 81 */
static void irq_handler_spi2(void);                 /* 82 */
static void irq_handler_spi3(void);                 /* 83 */
static void irq_handler_spi4(void);                 /* 84 */
static void irq_handler_spi5(void);                 /* 85 */
static void irq_handler_uart3(void);                /* 86 */
static void irq_handler_uart4(void);                /* 87 */
static void irq_handler_uart5(void);                /* 88 */
static void irq_handler_uart6(void);                /* 89 */
static void irq_handler_uart7(void);                /* 90 */
void irq_handler_sgpio2(void) WEAK;                 /* 91 */
void irq_handler_sgpio3(void) WEAK;                 /* 92 */
void irq_handler_sgpio4(void) WEAK;                 /* 93 */
void irq_handler_rsv(void) WEAK;                    /* 94 */
void irq_handler_can0(void);                        /* 95 */
void irq_handler_can1(void);                        /* 96 */
static void irq_handler_lcd(void);                  /* 97 */
void irq_handler_watchdogsafe0(void) WEAK;          /* 100 */
void irq_handler_watchdogsafe1(void) WEAK;          /* 101 */
void irq_handler_reset(void) WEAK;                  /* 102 */
static void irq_handler_gpio_0(void);               /* 103 */
static void irq_handler_gpio_1(void);               /* 104 */
static void irq_handler_gpio_2(void);               /* 105 */
static void irq_handler_gpio_3(void);               /* 106 */
static void irq_handler_gpio_4(void);               /* 107 */
static void irq_handler_gpio_5(void);               /* 108 */
static void irq_handler_gpio_6(void);               /* 109 */
static void irq_handler_gpio_7(void);               /* 110 */
static void irq_handler_timer0_0(void);             /* 112 */
static void irq_handler_timer0_1(void);             /* 113 */
static void irq_handler_timer0_2(void);             /* 114 */
void irq_handler_timer0_3(void) WEAK;               /* 115 */
void irq_handler_timer0_4(void) WEAK;               /* 116 */
void irq_handler_timer0_5(void) WEAK;               /* 117 */
static void irq_handler_timer0_6(void);             /* 118 */
static void irq_handler_timer0_7(void);             /* 119 */
void irq_handler_timer1_0(void) WEAK;               /* 120 */
void irq_handler_timer1_1(void) WEAK;               /* 121 */
void irq_handler_timer1_2(void) WEAK;               /* 122 */
void irq_handler_timer1_3(void) WEAK;               /* 123 */
void irq_handler_timer1_4(void) WEAK;               /* 124 */
void irq_handler_timer1_5(void) WEAK;               /* 125 */
void irq_handler_timer1_6(void) WEAK;               /* 126 */
void irq_handler_timer1_7(void) WEAK;               /* 127 */
void irq_handler_naxierrirq(void) WEAK;             /* 155 */
void irq_handler_nctiirq_0(void) WEAK;              /* 156 */
void irq_handler_nctiirq_1(void) WEAK;              /* 157 */
void irq_handler_npmuirq_0(void) WEAK;              /* 158 */
void irq_handler_npmuirq_1(void) WEAK;              /* 159 */

/***********************************************************************************************************************
 Vector Table
 **********************************************************************************************************************/
// The vector table is normally located at address 0.
// When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
// If you need to define interrupt service routines,
// make a copy of this file and include it in your project.
// The name "__vector_table" has special meaning for C-SPY:
// it is where the SP start value is found, and the NVIC vector
// table register (VTOR) is initialized to this address if != 0.

#pragma location = "vectors"
intvec_elem __vector_table[] =
{
  { .__ptr = __sfe( "CSTACK" ) },
      __iar_program_start,
      nmi_handler,
      hardfault_handler,
      memmanage_handler,
      busfault_handler,
      usagefault_handler,
      0,
      0,
      0,
      0,
      svc_handler,
      debugmon_handler,
      0,
      pendsv_handler,
      systick_handler,
      irq_handler_adc,
      irq_handler_i2c0,
      irq_handler_i2c1,
      irq_handler_safety_filtering,
      irq_handler_sgpio0,
      irq_handler_sgpio1,
      irq_handler_uart0,                /* 6 */
      irq_handler_uart1,
      irq_handler_uart2,
      irq_handler_deltasigma,
      irq_handler_pwmpto,
      irq_handler_ecc_4mb,
      irq_handler_ecc_2mb,
      irq_handler_cm3_lockup,
      irq_handler_cm3_tring_0,
      irq_handler_cm3_tring_1,
      irq_handler_hwrtos_bramerr,
      irq_handler_hwrtos_bufdma,
      irq_handler_hwrtos_bufdmaerr,
      irq_handler_hwrtos_ethmii,
      irq_handler_hwrtos_ethpause,
      irq_handler_hwrtos_ethrxderr,
      irq_handler_hwrtos_ethrxdma,
      irq_handler_hwrtos_ethrxerr,
      irq_handler_hwrtos_ethrxfifo,
      irq_handler_hwrtos_ethtx,
      irq_handler_hwrtos_ethtxderr,
      irq_handler_hwrtos_ethtxdma,
      irq_handler_hwrtos_ethtxfifo,
      irq_handler_hwrtos_ethtxfifoerr,
      irq_handler_hwrtos,
      irq_handler_hwrtos_macdmarxfrm,
      irq_handler_hwrtos_tm_lpi_ast,
      irq_handler_hwrtos_tm_lpi_deast,
      irq_handler_sbd0,
      irq_handler_lpi0,
      irq_handler_pmt0,
      irq_handler_sbd1,
      irq_handler_lpi1,
      irq_handler_pmt1,
      irq_handler_switchdlr,
      0,
      irq_handler_switch,
      irq_handler_switchprp,
      irq_handler_ethswhub,
      irq_handler_ethswptrn,
      irq_handler_cat_rst,
      irq_handler_cat_sync_0,
      irq_handler_cat_sync_1,
      irq_handler_cat_wdt_s3_divclk,
      irq_handler_cat_eof_s3_conclk_hsr_ptp,
      irq_handler_cat_sof_s3_0_hsr_cpu,
      irq_handler_cat_s3_1,
      irq_handler_nocfirewall,
      irq_handler_crypto0,
      irq_handler_crypto1,
      irq_handler_dma0,
      irq_handler_dma1,
      irq_handler_nand,
      irq_handler_ipcm_0,
      irq_handler_ipcm_1,
      irq_handler_ipcm_2,
      irq_handler_msebim,
      irq_handler_msebis,
      irq_handler_qspi0,
      irq_handler_qspi1,
      irq_handler_rtcatintal,
      irq_handler_rtcatintr,
      irq_handler_rtcatint1s,
      irq_handler_sdio0,
      irq_handler_sdio0_wkup,
      irq_handler_sdio1,
      irq_handler_sdio1_wkup,
      irq_handler_watchdog_resetn_0,
      irq_handler_watchdog_resetn_1,
      irq_handler_watchdog_cm3_resetn,
      irq_handler_ddrsub,
      irq_handler_usbf_epc,     /* 77 USB function */
      irq_handler_usbf,         /* 78 USB function */
      irq_handler_usbh_bind,    /* 79 USB Host */
      irq_handler_spi0,
      irq_handler_spi1,
      irq_handler_spi2,
      irq_handler_spi3,
      irq_handler_spi4,
      irq_handler_spi5,
      irq_handler_uart3,        /* 86 */
      irq_handler_uart4,        /* 87 */
      irq_handler_uart5,        /* 88 */
      irq_handler_uart6,        /* 89 */
      irq_handler_uart7,        /* 90 */
      irq_handler_sgpio2,
      irq_handler_sgpio3,
      irq_handler_sgpio4,
      irq_handler_rsv,
      irq_handler_can0,
      irq_handler_can1,
      irq_handler_lcd,          /* 97 */
      0,
      0,
      irq_handler_watchdogsafe0,
      irq_handler_watchdogsafe1,
      irq_handler_reset,
      irq_handler_gpio_0,
      irq_handler_gpio_1,
      irq_handler_gpio_2,
      irq_handler_gpio_3,
      irq_handler_gpio_4,
      irq_handler_gpio_5,
      irq_handler_gpio_6,
      irq_handler_gpio_7,
      0,
      irq_handler_timer0_0,
      irq_handler_timer0_1,
      irq_handler_timer0_2,
      irq_handler_timer0_3,
      irq_handler_timer0_4,
      irq_handler_timer0_5,
      irq_handler_timer0_6,
      irq_handler_timer0_7,
      irq_handler_timer1_0,
      irq_handler_timer1_1,
      irq_handler_timer1_2,
      irq_handler_timer1_3,
      irq_handler_timer1_4,
      irq_handler_timer1_5,
      irq_handler_timer1_6,
      irq_handler_timer1_7,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      0,
      irq_handler_naxierrirq,
      irq_handler_nctiirq_0,
      irq_handler_nctiirq_1,
      irq_handler_npmuirq_0,
      irq_handler_npmuirq_1
};

void dummy_handler(void) { while(1); }          /* Handler for unused interrupts */

/* Handlers for processor faults */
void nmi_handler(void) { while(1); }

void hardfault_handler(void) { while(1); }

void memmanage_handler(void) { while(1); }

void busfault_handler(void) { while(1); }

void usagefault_handler(void) { while(1); }     /* Use of invalid address e.g. function pointer */

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_adc
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_adc(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_ADC, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_i2c0
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_i2c0(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_I2C0, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_i2c1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for I2C channel 1
 *
 **********************************************************************************************************************/
static void irq_handler_i2c1(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_I2C1, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}
/***********************************************************************************************************************
 *
 *  Function:       irq_handler_i2c1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for I2C channel 1
 *
 **********************************************************************************************************************/
static void irq_handler_sbd0(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SBD0, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}
/***********************************************************************************************************************
 *
 *  Function:       irq_handler_i2c1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for I2C channel 1
 *
 **********************************************************************************************************************/
static void irq_handler_lpi0(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_LPI0, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}
/***********************************************************************************************************************
 *
 *  Function:       irq_handler_i2c1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for I2C channel 1
 *
 **********************************************************************************************************************/
static void irq_handler_pmt1(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_PMT0, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_i2c1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for I2C channel 1
 *
 **********************************************************************************************************************/
static void irq_handler_sbd1(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SBD1, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}
/***********************************************************************************************************************
 *
 *  Function:       irq_handler_i2c1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for I2C channel 1
 *
 **********************************************************************************************************************/
static void irq_handler_lpi1(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_LPI1, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}
/***********************************************************************************************************************
 *
 *  Function:       irq_handler_i2c1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for I2C channel 1
 *
 **********************************************************************************************************************/
static void irq_handler_pmt0(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_PMT1, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}
/***********************************************************************************************************************
 *
 *  Function:       irq_handler_uart0
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_uart0(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_UART0, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_uart1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for UART channel 1
 *
 **********************************************************************************************************************/
static void irq_handler_uart1(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_UART1, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_uart2
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for UART channel 2
 *
 **********************************************************************************************************************/
static void irq_handler_uart2(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_UART2, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_watchdog_cm3_resetn
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for CM3 Watchdog Timer
 *
 **********************************************************************************************************************/
static void irq_handler_watchdog_cm3_resetn(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_WATCHDOG_CM3_RESETN, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_msebis
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for MSEBI Slave
 *
 **********************************************************************************************************************/
static void irq_handler_msebis(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_MSEBIS, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_sdio0
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_sdio0(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SDIO0, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_sdio0_wkup
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_sdio0_wkup(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SDIO0_WKUP, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_sdio1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_sdio1(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SDIO1, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_sdio1_wkup
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_sdio1_wkup(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SDIO1_WKUP, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_usbf_epc
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for USBf EPC
 *
 **********************************************************************************************************************/
static void irq_handler_usbf_epc(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_USBF_EPC, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_usbf
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for USBf
 *
 **********************************************************************************************************************/
static void irq_handler_usbf(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_USBF, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_usbh_bind
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 * Description :    Interrupt handler for USBh (Host)
 *
 **********************************************************************************************************************/
static void irq_handler_usbh_bind(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_USBH_BIND, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_lcd
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for LCDC
 *
 **********************************************************************************************************************/
static void irq_handler_lcd(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_LCD, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_spi0
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for SPI Channel 0
 *
 **********************************************************************************************************************/
static void irq_handler_spi0(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SPI0, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_spi1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for SPI Channel 1
 *
 **********************************************************************************************************************/
static void irq_handler_spi1(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SPI1, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_spi2
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for SPI Channel 2
 *
 **********************************************************************************************************************/
static void irq_handler_spi2(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SPI2, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_spi3
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for SPI Channel 3
 *
 **********************************************************************************************************************/
static void irq_handler_spi3(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SPI3, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_spi4
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for SPI Channel 4
 *
 **********************************************************************************************************************/
static void irq_handler_spi4(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SPI4, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_spi5
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for SPI Channel 5
 *
 **********************************************************************************************************************/
static void irq_handler_spi5(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_SPI5, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_uart3
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for UART channel 3
 *
 **********************************************************************************************************************/
static void irq_handler_uart3(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_UART3, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_uart4
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for UART channel 4
 *
 **********************************************************************************************************************/
static void irq_handler_uart4(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_UART4, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_uart5
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for UART channel 5
 *
 **********************************************************************************************************************/
static void irq_handler_uart5(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_UART5, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_uart6
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for UART Channel 6
 *
 **********************************************************************************************************************/
static void irq_handler_uart6(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_UART6, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_uart7
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for UART Channel 7
 *
 **********************************************************************************************************************/
static void irq_handler_uart7(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_UART7, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_can0
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for CAN Channel 0
 *
 **********************************************************************************************************************/
static void irq_handler_can0(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_CAN0, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_can1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler for CAN Channel 1
 *
 **********************************************************************************************************************/
static void irq_handler_can1(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_CAN1, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_dma0
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_dma0(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_DMA0, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_dma1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_dma1(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_DMA1, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_rtcatintal
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_rtcatintal(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_RTCATINTAL, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_rtcatintr
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_rtcatintr(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_RTCATINTR, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_rtcatint1s
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_rtcatint1s(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_RTCATINT1S, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_gpio_0
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_gpio_0(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_GPIO_0, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_gpio_1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_gpio_1(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_GPIO_1, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_gpio_2
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_gpio_2(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_GPIO_2, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_gpio_3
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_gpio_3(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_GPIO_3, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_gpio_4
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_gpio_4(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_GPIO_4, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}
/***********************************************************************************************************************
 *
 *  Function:       irq_handler_gpio_5
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_gpio_5(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_GPIO_5, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_gpio_6
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_gpio_6(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_GPIO_6, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_gpio_7
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_gpio_7(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_GPIO_7, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_timer0_0
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_timer0_0(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_TIMER0_0, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_timer0_1
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_timer0_1(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_TIMER0_1, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_timer0_2
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_timer0_2(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_TIMER0_2, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_timer0_6
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_timer0_6(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_TIMER0_6, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}

/***********************************************************************************************************************
 *
 *  Function:       irq_handler_timer0_7
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Interrupt handler - executes callback, if registered
 *
 **********************************************************************************************************************/
static void irq_handler_timer0_7(void)
{
    if (MCU_INT_SUCCESS != R_BSP_InterruptControl(RZN1_IRQ_TIMER0_7, MCU_INT_CMD_CALL_CALLBACK, FIT_NO_PTR))
    {
        while(1);
    }
}
