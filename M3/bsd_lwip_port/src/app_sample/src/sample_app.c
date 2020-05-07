/**********************************************************************************************************************
    $REA IPCM project notes.
    + Warning[Pa181]: incompatible redefinition of macro "GMAC2" (declared at line 131 of "C:\Workspace\RZN\3rd-party_customers\Pivotal\CTC\IPCM\V2.0\M3\bsd_lwip_port\src\fit_modules\r_bsp\inc\iodefines/RZN1L_iodefine.h") C:\Workspace\RZN\3rd-party_customers\Pivotal\CTC\IPCM\V2.0\M3\bsd_lwip_port\src\fit_modules\r_bsp\inc\iodefines\RZN1D_iodefine.h 148
    + Which folders/files of workspace delete..
***********************************************************************************************************************/
/**********************************************************************************************************************
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
* $Revision: 1.00
* $Date: 2020-05-01 12:00:00 +0000 (Fri, 1 May 2020) $
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/

/*******************************************************************************
Includes
********************************************************************************/
#include "platform.h"
#include "RZN1.h"
#include "iodefine.h"
#include "timer.h"
#include "kernel.h"
#include "kernel_id.h"

#include "lwip/tcpip.h"

#include "r_gmac_rzn1_if.h"
#include "r_gpio_rzn1_if.h"
#include "r_gpio_rzn1l.h"

#include "serial_log.h"
#include "lwip/apps/snmp.h"
#include "asb_low_level_init.h"
#include "iodefines\RZN1D_iodefine.h"

/*******************************************************************************
Defines
********************************************************************************/
#define SHM_SIZE                      0x8000
#define SHM_ADDR                      ((unsigned int*)0x200F8000)
#define SHM_ADDR_M3_TO_A7_OFFSET      ((SHM_SIZE/2)/4)

#define TX_SLEEP_TIME_MS              1000L
#define M3_TO_A7_MEM_WRITE_SIZE_BYTES 0x80  //#bytes write chunks to A7 shared mem.

/* For IAR Terminal I/O updates if desired. You could even set to 1 but will slow system down alot. */
#define DISPLAY_UPDATE_TRIGCOUNT      10000

/********************************************************************************
Types, structs
********************************************************************************/
/*******************************************************************************
Global variables
********************************************************************************/
/********************************************************************************
Externals	(Imports)
********************************************************************************/
/********************************************************************************
Global variables (exports)
********************************************************************************/
/********************************************************************************
Static (private) functions
********************************************************************************/
/********************************************************************************
Static (private) variables
********************************************************************************/
static int  init_task_cnt = 0;

/* Globals to show in IAR Live Watch. */
static int            error = 0;
static int            read_cnt = 0;
static unsigned int   M3_to_A7_mem_write_cnt = 0;
static unsigned int   M3_to_A7_mem_write_try_cnt = 0;
static unsigned int   M3_to_A7_mem_write_delta_cnt = 0;
static unsigned int   M3_to_A7_mem_write_sleep_cnt = 0;
//static unsigned int   M3_TO_A7_MEM_WRITE_SIZE_BYTES = 100; //Perhaps change to macro. $REA

/***********************************************************************************************************************
External functions
**********************************************************************************************************************/
/***********************************************************************************************************************
Static (private) functions
**********************************************************************************************************************/
/***********************************************************************************************************************
* Function define: main()
**********************************************************************************************************************/
int main (void)
{
  /* indicate to the NoC interconnect that the Semaphore is ready for access */
  SYSCTRL->PWRCTRL_PG4.BIT.SLVRDY_AD = 1;

  //--------------------------
  // Setup HWRTOS
  //--------------------------
  RINACS->RINSPCMD.LONG = 0x000000a5;
  RINACS->RINSPCMD.LONG = 0x00000001;
  RINACS->RINSPCMD.LONG = 0x0000fffe;
  RINACS->RINSPCMD.LONG = 0x00000001;

  if (RINACS->RTOSRST.LONG == 0x00000001)
  {
    /* Assert reset if already deasserted */
    RINACS->RTOSRST.LONG = 0x00000000;
  }

  RINACS->RTOSRST.LONG = 0x00000001;

  RINACS->RINSPCMD.LONG = 0x00000000;

  /* This timer is not used beyond this point so it should be safe to stop it.
  However, some drivers rely on it so we should be careful when adding other
  drivers to this project. It might be better to use an RTOS-aware mechanism
  instead. */
  sys_timer_stop();
  hwos_setup();

  return 0;
}/* end main() */

/*******************************************************************************
Functione define: write_to_shm()
*******************************************************************************/
void write_to_shm(int cnt, int shm_region_size_bytes)
{
  unsigned int*  addr_p;

  addr_p = SHM_ADDR + SHM_ADDR_M3_TO_A7_OFFSET; //0x200FC000

  M3_to_A7_mem_write_cnt++;

  for(int i = 0 ; i < shm_region_size_bytes/4 ; i++)
  {
    *(((unsigned long*) addr_p) + i) = cnt++;
  }
}/* end write_to_shm() */

/*******************************************************************************
Function define: check_memory()
*******************************************************************************/
void check_memory(unsigned int ipcm_d1, unsigned int ipcm_d2, unsigned int shm_size_bytes)
{
  unsigned int*   shared_ram_p = SHM_ADDR;
  unsigned int*   mem_content_p;

  mem_content_p = (unsigned int*)malloc(shm_size_bytes);

  for (int i = 0; i < shm_size_bytes/4; i++)
  {
    mem_content_p[i] = *(((unsigned long*)shared_ram_p ) + i);
  }

  for (int i = 0; i < (shm_size_bytes/4) - 1; i++)
  {
    if(mem_content_p[i] != (mem_content_p[i+1] - 1))
    {
      error++;
    }
  }

  if (ipcm_d2 != (ipcm_d1 + 1) || (ipcm_d1 != mem_content_p[0]) || (ipcm_d2 != mem_content_p[1]))
  {
    error++;
  }

  read_cnt++;

  free(mem_content_p);
}/* end check_memory() */

/*******************************************************************************
Function define: init_task()
*******************************************************************************/
void init_task(int exinf)
{
  SysTick_Config(12500);

  while(1)
  {
    tslp_tsk(TX_SLEEP_TIME_MS);
  }

  ext_tsk();
}/* end init_task() */

/*******************************************************************************
Function define: pl320_tx_task()
*******************************************************************************/
void pl320_tx_task(int exinf)
{
  int cycle = 0;

  while(1)
  {
    tslp_tsk(TX_SLEEP_TIME_MS);

    cycle = cycle + M3_TO_A7_MEM_WRITE_SIZE_BYTES/4;
    write_to_shm(cycle, M3_TO_A7_MEM_WRITE_SIZE_BYTES);

    /* Detect if writes did not happen. E.g. use to show M3_to_A7_mem_write_delta_cnt in debugger. */
    M3_to_A7_mem_write_try_cnt++;
    M3_to_A7_mem_write_delta_cnt = M3_to_A7_mem_write_try_cnt - M3_to_A7_mem_write_cnt;

    /* Wait for send register to become inactive. */
    while (IPCM->IPCM0SEND.LONG != 0)
    {
      tslp_tsk(1LL);  //$REA: Investigate need/value of this sleep.
      M3_to_A7_mem_write_sleep_cnt++;
    }
    /* Send status is 0; mailbox is inactive.
    Currently the Linux kernel requires to fill data reg. 0 with destination
    core ID. Should be investigated why this seems be practise. */
    IPCM->IPCM0DR0.LONG = 2;

    /* Filling IPCM data registers 1 and 2 with cycle pattern to verify the consistency on A7 side. */
    IPCM->IPCM0DR1.LONG = cycle;
    IPCM->IPCM0DR2.LONG = cycle + 1;

    /* Passing the memory size through IPCM data register #3. */
    IPCM->IPCM0DR3.LONG = M3_TO_A7_MEM_WRITE_SIZE_BYTES;
    IPCM->IPCM0DR4.LONG = 0x04;
    IPCM->IPCM0DR5.LONG = 0x05;
    IPCM->IPCM0DR6.LONG = 0x06;

    /* Send msg to dest core A7. */
    IPCM->IPCM0DSET.BIT.DEST_SET = 2;
    IPCM->IPCM0SEND.BIT.SEND = 1;   //1 = Send msg to dest core (A7).

    init_task_cnt++;
  }
}/* end pl320_tx_task() */

/*******************************************************************************
Function define: pl320_rx_task()
*******************************************************************************/
void pl320_rx_task(int exinf)
{
  int ipcm_rx_cnt = 0;
  unsigned int d0, d1, d2, d3, d4, d5, d6;
  unsigned int display_update_counter = 0;

  /* Interrupt status not used for now.
  unsigned int i0, i1, i2;  */

    /* In case ISRs for the mailboxes are used, using flahs is a usage possibility.
    For now we are using HW-ISR; see static_hwisr_table (RZN1_IRQ_IPCM_0).
    FLGPTN wait_ptn = 0xFFFF;
    ER hwos_err, res; */

  /* See linux ../rzn1_linux/drivers/mailbox/pl320-ipc.c for example init of mailbox. */

  /****************************
    Mailbox 0 used for M3->A7.
    Mailbox 1 used for A7->M3.
  *****************************/

  /***** Set up mailbox 0 = IPCM0. *****
  Set bit 0 for first core which will be M3. */
  IPCM->IPCM0SOURCE.BIT.SRC_SET = 1;

  /* Core A7 is bit 1 (and 2 should with SMP include both cores). */
  IPCM->IPCM0DSET.BIT.DEST_SET = 2;
  IPCM->IPCM0MSET.BIT.MASK_SET = 2;


  /*** Set up mailbox 1 = IPCM1. *****/ //$REA: Doesn't linux side set up this mbox?
  /* Set bit 1 for second core which will be A7. */
  IPCM->IPCM1SOURCE.BIT.SRC_SET = 2;

  IPCM->IPCM1DSET.BIT.DEST_SET = 1;
  IPCM->IPCM1MSET.BIT.MASK_SET = 1;

  while (1)
  {
    /* Sleep task until task woken up by RZN1_IRQ_IPCM_0. HWISR used. */
    slp_tsk();

    /* In case ISRs for the mailboxes are used, using flahs is a usage possibility.
    For now we are using HW-ISR; see static_hwisr_table (RZN1_IRQ_IPCM_0).
    hwos_err = wai_flg(ID_FLG_PL320_IRQ, wait_ptn, TWF_ORW, (FLGPTN*)&mask_out);
    hwos_err = clr_flg(ID_FLG_PL320_IRQ, (FLGPTN)~mask_out); */

    /* Interrupt status not used for now.
    i0 = IPCM->IPCMMIS0.LONG;
    i1 = IPCM->IPCMMIS1.LONG;
    i2 = IPCM->IPCMMIS2.LONG; */

    d0 = IPCM->IPCM1DR0.LONG;
    d1 = IPCM->IPCM1DR1.LONG;

    ipcm_rx_cnt++;

    d2 = IPCM->IPCM1DR2.LONG;
    d3 = IPCM->IPCM1DR3.LONG;
    d4 = IPCM->IPCM1DR4.LONG;
    d5 = IPCM->IPCM1DR5.LONG;
    d6 = IPCM->IPCM1DR6.LONG;

    /* To save CPU power, it is best to set this to 0 and just look at memory
    window @ SHM_ADDR (0x200F8000 and up). Especially if benchmarking. */
    #if 1 //0 or 1. (1 to show in Terminal I/O.)
      if (display_update_counter == 0)
      {
        printf("A7->M3: ");
        printf("d0=0x%X, ", d0);
        printf("d1=0x%X, ", d1);
        printf("d2=0x%X, ", d2);
        printf("d3=0x%X, ", d3);
        printf("d4=0x%X, ", d4);
        printf("d5=0x%X, ", d5);
        printf("d6=0x%X\n", d6);
      }
      if (display_update_counter++ > DISPLAY_UPDATE_TRIGCOUNT)
        display_update_counter = 0;
    #endif

    /* M3 starts to run much earlier than Linux. So have to wait until the data
    from Linux becomes operational
    d0 contains destination core ID. See comment in tx task.
    d1 contains first B of shared data.
    d2 contains second B of shared data.
    d3 contains nr bytes sent this round.
    d4,d5,d6 not used. */
    if(d3 != 0)
    {
      check_memory(d1, d2, d3);
    }

    IPCM->IPCM1SEND.LONG = 0; /* 0 = Inactive. */
  }
}/* end pl320_rx_task() */

/*******************************************************************************
Functione define: idle_task()
*******************************************************************************/
void idle_task(int exinf)
{
  while(1)
  {
  }
}/* end idle_task() */
/* file end */