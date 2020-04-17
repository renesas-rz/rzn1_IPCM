/*
* Copyright (c) 2001-2003 Swedish Institute of Computer Science.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
* 3. The name of the author may not be used to endorse or promote products
*    derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
* SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
* OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
* OF SUCH DAMAGE.
*
* This file is part of the lwIP TCP/IP stack.
*
* Author: Adam Dunkels <adam@sics.se>
*
*/

/* lwIP includes. */
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/sys.h"
#include "lwip/mem.h"
#include "lwip/stats.h"
#include "kernel.h"
#include "kernel_id.h"
#include "RZN1.h"
#include <string.h>
#include "asb_low_level_init.h"

// $REA This file contains lwip wrappers around some hwrtos APIs

#define cre_tsk     CRE_TSK

/* Mutex functions: */

/**
* Creates a new mutex
*
* @param[out] mutex HWRTOS mutex ID
*
* @return ERR_OK if mutex sucessfully created
*         
*/
err_t sys_mutex_new(sys_mutex_t *mutex)
{
  return sys_sem_new(mutex, 1);
}

/**
* Locks mutex
*
* @param[in] mutex HWRTOS mutex ID
*         
*/
void sys_mutex_lock(sys_mutex_t *mutex)
{
  sys_arch_sem_wait(mutex, 0);
}

/**
* Unlocks mutex
*
* @param[in] mutex HWRTOS mutex ID
*         
*/
void sys_mutex_unlock(sys_mutex_t *mutex)
{
  sys_sem_signal(mutex);
}

/**
* Deletes mutex
*
* @param[in] mutex HWRTOS mutex ID
*         
*/
void sys_mutex_free(sys_mutex_t *mutex)
{
  sys_sem_free(mutex);
}

#ifndef sys_mutex_valid
int sys_mutex_valid(sys_mutex_t *mutex)
{
}
#endif

#ifndef sys_mutex_set_invalid
void sys_mutex_set_invalid(sys_mutex_t *mutex)
{  
}
#endif

/* Semaphore functions: */

/**
* Creates a new semaphore
*
* @param[out] sem HWRTOS semaphore ID
* @param      count HWRTOS semaphore initial count
*
* @return ERR_OK if semaphore sucessfully created
*         
*/
err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
  ER err;
  T_CSEM sem_def;                                 /* semaphore create struct */
  uint32_t cnt;                               /* counter for semaphore usage list */
  
  /* select next task by priority */
  sem_def.sematr = TA_TPRI;
  
  /* init current and maximum semaphore count */
  sem_def.isemcnt = count;
  sem_def.maxsem = 1;
  
  /* find a free semaphore */
  for (cnt = TMIN_SEMID; cnt < TMAX_SEMID; cnt++) 
  {
    err = cre_sem((ID) cnt, &sem_def);
    if (E_OK == err) 
    {
      break;
    }
  }
  
  if (cnt >= TMAX_SEMID)
  {
    /* failed to create a semaphore */
    *sem = -1;
    return err;
  }
  
  *sem = cnt;
  
  return ERR_OK;
}

/**
* Signals semaphore
*
* @param[in] sem HWRTOS semaphore ID
*         
*/
void sys_sem_signal(sys_sem_t *sem)
{  
  if (sem == NULL)
    return;
  
  sig_sem(*sem);
}

/**
* Waits for semaphore
*
* @param[in] sem HWRTOS semaphore ID
* @param timeout time out      
* 
* @return SYS_ARCH_TIMEOUT if semaphore wait timed out
*         time taken to acquire semaphore   
*/
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
  ER err;
  SYSTIM systim_start;
  SYSTIM systim_end;
  
  if (sem == NULL)
    return 0xff;
  
  if(timeout != 0)
  {
    get_tim(&systim_start);
    
    err = twai_sem(*sem, timeout);
    
    if(err == E_OK)
    {
      get_tim(&systim_end);
      
      return systim_end - systim_start;		
    }
    else
    {
      return SYS_ARCH_TIMEOUT;
    }
  }
  else
  {
    get_tim(&systim_start);
    
    twai_sem(*sem, TMO_FEVR);
   
    get_tim(&systim_end);
      
    return systim_end - systim_start;	
  }
}

/**
* Deletes semaphore
*
* @param[in] sem HWRTOS semaphore ID
*         
*/
void sys_sem_free(sys_sem_t *sem)
{
  if (sem == NULL)
    return;
  
  del_sem(*sem);
}

#ifndef sys_sem_valid
int sys_sem_valid(sys_sem_t *sem)
{
}
#endif

#ifndef sys_sem_set_invalid
void sys_sem_set_invalid(sys_sem_t *sem)
{  
}
#endif

#ifndef sys_msleep
/**
* @ingroup sys_misc
* Sleep for specified number of ms
*/
//void sys_msleep(u32_t ms)
//{
//  tslp_tsk(ms);
//}
#endif

u32_t sys_now(void)
{
  SYSTIM tm;

  get_tim(&tm);

  return tm;
}

/* Mailbox functions. */
err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
  ER err;
  T_CMBX mbox_def;                                 /* semaphore create struct */
  uint32_t cnt;                               /* counter for semaphore usage list */
  
  /* select next task by priority */
  mbox_def.mbxatr = TA_TPRI;
  mbox_def.maxmpri = 0;
  mbox_def.mprihd  = 0;
  
  /* find a free semaphore */
  for (cnt = TMIN_MBXID; cnt < TMAX_MBXID; cnt++) 
  {
    err = cre_mbx((ID) cnt, &mbox_def);
    if (E_OK == err) 
    {
      break;
    }
  }
  
  if (cnt >= TMAX_MBXID)
  {
    /* failed to create a mailbox */
    *mbox = -1;
    return err;
  }
  
  *mbox = cnt;
  
  return ERR_OK;
}

void sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
  sys_mbox_trypost(mbox, msg);
}

err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{  
  ER err;
  
  if (mbox == NULL)
    return -1;
  
  err = snd_mbx(*mbox, msg);
  
  return err;
}

/**
* Gets and waits for message
*
* @param[in] mbox HWRTOS mailbox ID
* @param timeout message fetch time out      
* 
* @return SYS_ARCH_TIMEOUT if message wait timed out
*         time taken to receive message   
*/
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
  ER err;
  SYSTIM systim_start;
  SYSTIM systim_end;
  
  if (mbox == NULL)
    return 0xff;
  
  if(timeout != 0)
  {
    get_tim(&systim_start);
    
    err = trcv_mbx(*mbox, (T_MSG**)msg, timeout);
    
    if(err == E_OK)
    {
      get_tim(&systim_end);
      
      return systim_end - systim_start;	
    }
    else
    {
      return SYS_ARCH_TIMEOUT;
    }
  }
  else
  {
    get_tim(&systim_start);
    
    trcv_mbx(*mbox, (T_MSG**)msg, TMO_FEVR);
    
    get_tim(&systim_end);
    
    return systim_end - systim_start;	
  }
}

/**
* Gets a message from the mailbox without a wait. 
*
* @param[in] mbox HWRTOS mailbox ID
* @param timeout message fetch time out      
* 
* @return SYS_MBOX_EMPTY if the mailbox is empty
*         ERR_OK if message fetch is successful  
*/
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
  ER err;
  
  if (mbox == NULL)
    return 0xff;
  
  err = prcv_mbx(*mbox, (T_MSG**)msg);
  
  if (err != E_OK)
    return SYS_MBOX_EMPTY;
  
  return ERR_OK;
}

/**
* Deletes mailbox
*
* @param[in] mbox HWRTOS mailbox ID
*         
*/
void sys_mbox_free(sys_mbox_t *mbox)
{
  if (mbox == NULL)
    return;
  
  del_mbx(*mbox);
}

#ifndef sys_mbox_valid
int sys_mbox_valid(sys_mbox_t *mbox)
{
}
#endif

#ifndef sys_mbox_set_invalid
void sys_mbox_set_invalid(sys_mbox_t *mbox)
{  
}
#endif

extern Task_Names task_names[TMAX_TSKID];
sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
  ER err;
  T_CTSK attr;
  
  memset(&attr, 0, sizeof(T_CTSK));
  
  attr.tskatr  = TA_HLNG;          // High level interface
  attr.exinf   = arg;              // Task function arg
  attr.task    = (FP) thread;      // Task function 
  attr.itskpri = prio;             // Task priority
  attr.stksz   = stacksize;
  
  ID i;
  
  for (i = TMIN_TSKID; i < TMAX_TSKID; i++) 
  {
    err = cre_tsk(i, &attr);
    
    if (err == E_OK) 
    {
      break;
    }
  }
  
  if (i >= TMAX_TSKID)
    return 0;
  
  err = sta_tsk(i, arg);
  
  if (err != E_OK) 
  {
    return 0;
  }

  Number_of_Tasks++;
  strcpy(task_names[Number_of_Tasks].name, name);
  return i;
}

/*-----------------------------------------------------------------------------------*/
// Initialize sys arch
void sys_init(void)
{
  
}

/****************************************************************************/
sys_prot_t sys_arch_protect(void)
{
  return -1; 
}


/****************************************************************************/
void sys_arch_unprotect(sys_prot_t pval)
{
  
}

/*-----------------------------------------------------------------------------------*/
