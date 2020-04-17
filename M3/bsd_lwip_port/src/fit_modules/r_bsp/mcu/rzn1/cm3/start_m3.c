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
 *
 *      PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 *      FILE         :  start_m3.c
 *      DESCRIPTION  :  Reset Program for ARM Cortex M3
 *      MCU SERIES   :  RZ/N1 D, S & L
 *      CPU TYPE     :  ARM Cortex M3
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * $Revision: 1324 $
 * $Date: 2019-03-04 10:02:39 +0000 (Mon, 04 Mar 2019) $
 *
 * Description : M3 Startup.
 *
 **********************************************************************************************************************/

#pragma language=extended
#pragma segment="CSTACK"

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "platform.h"
#include "mcu_interrupts.h"
#include "system_RZN1.h"
#include "iodefines/RZN1L_iodefine.h"
#if (BSP_MCU_RZN1D == 1)
#include "ddr/ddr.h"
#endif

/***********************************************************************************************************************
 Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
typedef void (*intfunc)(void);
typedef union {
    intfunc __fun;
    void * __ptr;
} intvec_elem;

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
void bsp_start(void);
#ifdef RZN1L_BOOT_FROM_ROM
void dummy_handler_rom(void);
#endif

/***********************************************************************************************************************
 Externs
 **********************************************************************************************************************/
extern void __iar_program_start(void);
extern void __iar_data_init3(void);

extern int main(void);

extern const intvec_elem __vector_table[];

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       __iar_program_start
 *
 *  Return value:   none
 *
 *  Parameters:     none
 *
 *  Description:    Reset handler
 *
 **********************************************************************************************************************/
#pragma required=__vector_table
void __iar_program_start(void) {
    SystemInit();

#ifdef RZN1L_BOOT_FROM_ROM
        /* set QSPI baud rate divisor to minimum to increase QSPI speed to maximum */
        QSPI1->config_reg.BIT.mstr_baud_div_fld = 1;
#endif

#if (BSP_MCU_RZN1D == 1)
    ddr_init();
#endif
    __iar_data_init3();
    //--------------------------
    // Replace vectors address
    //--------------------------
    SCB->VTOR = (uint32_t) __vector_table;

    bsp_start();
}


#ifdef RZN1L_BOOT_FROM_ROM
#pragma location = "bsp_start"
#endif
void bsp_start(void) {
    bsp_interrupts_open();
    hardware_setup();

    main();
}

#ifdef RZN1L_BOOT_FROM_ROM
/* Vector table for ROM, which is available during booting */
#pragma location = "vectors_rom"
__root const intvec_elem __vector_table_rom[] =
{
    {   .__ptr = __sfe( "CSTACK" )},
    __iar_program_start,
    dummy_handler_rom,
    dummy_handler_rom,
    dummy_handler_rom,
    dummy_handler_rom,
    dummy_handler_rom,
};

#pragma required=__vector_table_rom
void dummy_handler_rom(void) {while(1);};
#endif /* RZN1L_BOOT_FROM_ROM */

