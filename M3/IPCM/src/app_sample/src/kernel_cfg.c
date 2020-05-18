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
*******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "RZN1.h"

#include "kernel.h"
#include "kernel_id.h"

#include "serial_log.h"
#include "asb_low_level_init.h"
#include "timers.h"
#include "iodefines\RZN1D_iodefine.h"

/*******************************************************************************
Defines
*******************************************************************************/
#define SHM_ADDR                  ((unsigned int *)0x200F8000)

/*******************************************************************************
Types, structs
*******************************************************************************/
/*******************************************************************************
Externals	(Imports)
*******************************************************************************/
extern void   init_task(int exinf);
extern void   pl320_tx_task(int exinf);
extern void   pl320_rx_task(int exinf);
extern void   idle_task(int exinf);
extern void   monitor_task(int exinf);

//extern void sample_app_printf(const char *message); //$REA
extern int    printf(const char *_Restrict, ...);

/*******************************************************************************
Global variables (exports)
*******************************************************************************/
/********************************************************************************
Static (private) functions
********************************************************************************/
/********************************************************************************
Static (private) variables
********************************************************************************/
static uint32_t idle_ticks = 0;
static uint32_t non_idle_ticks = 0;


//static uint32_t get_latest_cpu_load();
//static uint32_t cpu_load;

/*******************************************************************************
Function define: systick_handler()
*******************************************************************************/
void systick_handler(void)
{
  ID active_task_id;

  if(get_tid(&active_task_id) != 0)
  {
    return;
  }

  switch(active_task_id)
  {
      case ID_TASK_IDLE:
        idle_ticks++;
        break;
      default:
        non_idle_ticks++;
        break;
  }
}/* end systick_handler() */

/*******************************************************************************
Function define: systick_handler()
*******************************************************************************/
uint32_t get_latest_cpu_load()
{
  uint32_t load = (non_idle_ticks * 100) / (idle_ticks + non_idle_ticks);

  idle_ticks = 0;
  non_idle_ticks = 0;

  return load;
}/* end get_latest_cpu_load() */

const TSK_TBL static_task_table[] = {
  // CRE_TSK( tskid, {tskatr,   exinf, task, itskpri, stksz, stk});
  {ID_TASK_INIT,        {TA_HLNG | TA_ACT, 0, (FP)init_task,        1, (0x400*3), NULL}},
  {ID_TASK_PL320_TX,    {TA_HLNG | TA_ACT, 0, (FP)pl320_tx_task,    2, (0x400*3), NULL}},
  {ID_TASK_PL320_RX,    {TA_HLNG | TA_ACT, 0, (FP)pl320_rx_task,    2, (0x400*3), NULL}},
  {ID_MONITOR_TASK,     {TA_HLNG | TA_ACT, 0, (FP)monitor_task,    14, (0x200*5), NULL}},
  {ID_TASK_IDLE,        {TA_HLNG | TA_ACT, 0, (FP)idle_task,       15, (0x100*5), NULL}},
  {TASK_TBL_END,        {0,                0, (FP)NULL,             0,  0,        NULL}}
};

//-------------------------------------
// Semaphore information
//-------------------------------------
const SEM_TBL static_semaphore_table[] = {
  // CRE_SEM(	 semid,				{sematr,	isemcnt,	maxsem});
  {SEMAPHORE_TBL_END,	{0,			0,			0}}
};

//-------------------------------------
// Eventflag information
//-------------------------------------
const FLG_TBL static_eventflag_table[] = {
  // CRE_FLG(	 flgid,				{flgatr,			iflgptn});
  //  {ID_FLG_PL320_IRQ,   {TA_TFIFO | TA_CLR ,     0}},
  {EVENTFLAG_TBL_END,	{0,			0}}
};

//-------------------------------------
// Mailbox information
//-------------------------------------
const MBX_TBL static_mailbox_table[] = {
  // CRE_MBX(  mbxid,             {mbxatr,    maxmpri,	mprihd});
  {MAILBOX_TBL_END,	{0,			0,			NULL}}
};

//-------------------------------------
// Mutex information
//-------------------------------------
const MTX_TBL static_mutex_table[] = {
  // CRE_MTX(	 mtxid, 		{mtxatr,	ceilpri});

  {MUTEX_TBL_END,	{0,			0}}
};

//-------------------------------------
// Interrupt handler information
//-------------------------------------

const INT_TBL static_interrupt_table[] = {
  // DEF_INH(  inhno,			{inatr,		inthdr});
  //{RZN1_IRQ_IPCM_0,    {TA_HLNG,  (FP)irq_handler_ipcm_0}},
  //{RZN1_IRQ_IPCM_1,    {TA_HLNG,  (FP)irq_handler_ipcm_1}},
  //{RZN1_IRQ_IPCM_2,    {TA_HLNG,  (FP)irq_handler_ipcm_2}},
  {SysTick_IRQn,        {TA_HLNG,  (FP)systick_handler}},
  {INT_TBL_END,	{0,			(FP)NULL}}
};

/* HW ISRs to wake up tasks..*/
const HWISR_TBL static_hwisr_table[] = {
  /* Interrupt for receiving from A7 to first core = M3. */
  {RZN1_IRQ_IPCM_0,     HWISR_WUP_TSK,  ID_TASK_PL320_RX, 0},
  {HWISR_TBL_END,	      0,			        0,		         0}
};

#if 0 //$REA
    static volatile int A,B,C = 0;

    /*******************************************************************************
    Function define: irq_handler_ipcm_0()
    *******************************************************************************/
    void irq_handler_ipcm_0(void)
    {
      volatile Mailbox_Type *mbox;
      mbox = IPCM;
      unsigned int d0,d1, d2;
      int rc;

      d0 = IPCM->IPCMMIS0.LONG;
      d1 = IPCM->IPCMMIS1.LONG;
      d2 = IPCM->IPCMMIS2.LONG;

      A = 0;
      rc = iset_flg(ID_FLG_PL320_IRQ, 0x01);
    }/* end irq_handler_ipcm_0() */

    /*******************************************************************************
    Function define: irq_handler_ipcm_1()
    *******************************************************************************/
    void irq_handler_ipcm_1(void)
    {

      volatile Mailbox_Type *mbox;
      mbox = IPCM;
      unsigned int d0,d1, d2;

      d0 = IPCM->IPCMMIS0.LONG;
      d1 = IPCM->IPCMMIS1.LONG;
      d2 = IPCM->IPCMMIS2.LONG;

      //iset_flg(ID_FLG_PL320_IRQ, 0x02);
      A = 1;
    }/* end irq_handler_ipcm_1() */

    /*******************************************************************************
    Function define: irq_handler_ipcm_2()
    *******************************************************************************/
    void irq_handler_ipcm_2(void)
    {

      volatile Mailbox_Type*  mbox_p;
      mbox_p = IPCM;
      unsigned int d0,d1, d2;

      d0 = mbox_p->IPCMMIS0.LONG;
      d1 = mbox_p->IPCMMIS1.LONG;
      d2 = mbox_p->IPCMMIS2.LONG;

      A = 2;
      //iset_flg(ID_FLG_PL320_IRQ, 0x04);
    }/* end irq_handler_ipcm_2() */
#endif
/* file end */