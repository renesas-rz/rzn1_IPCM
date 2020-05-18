#ifdef __cplusplus
extern "C" {
#endif

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
 * $Revision: 1301 $
 * $Date: 2019-02-25 14:29:43 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  kernel.h
 * Description  :  Kernel specification (Service Calls, Data Types, Constants, Macros)
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef KERNEL_H__
#define KERNEL_H__

#ifdef  __IASMARM__
#ifndef _ASM_
#define _ASM_
#endif
#endif

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <itron.h>                            // ITRON General Definitions (Data Types, Constants, Macros)
#ifndef _ASM_
#include <stdint.h>
#endif    /* !_ASM_ */

/***********************************************************************************************************************
 Structures
 **********************************************************************************************************************/
//=============================================================
// Task management function
//=============================================================
//-------------------------------------
// Task creation information packet
//-------------------------------------
#ifndef _ASM_
typedef    struct t_ctsk {
    ATR     tskatr;                     /*!< Task attribute                         */
    VP_INT  exinf;                      /*!< Task extended information              */
    FP      task;                       /*!< Task start address                     */
    PRI     itskpri;                    /*!< Task initial priority                  */
    SIZE    stksz;                      /*!< Task stack size                        */
    VP      stk;                        /*!< Base address of task stack space       */
} T_CTSK;
#endif  /* !_ASM_ */

//=============================================================
// Synchronization and communication functions
//=============================================================
//-------------------------------------
// Semaphore creation information packet
//-------------------------------------
#ifndef _ASM_
typedef struct t_csem {
    ATR     sematr;                     /*!< Semaphore attribute                    */
    UINT    isemcnt;                    /*!< Initial semaphore resource count       */
    UINT    maxsem;                     /*!< Maximum semaphore resource count       */
}T_CSEM;
#endif    /* !_ASM_ */

//-------------------------------------
// Event flag creation information packet
//-------------------------------------
#ifndef _ASM_
typedef struct t_cflg {
    ATR     flgatr;                     /*!< Event flag attribute                    */
    FLGPTN  iflgptn;                    /*!< Initial value of event flag bit pattern */
}T_CFLG;
#endif  /* !_ASM_ */

//-------------------------------------
// Mailbox creation information packet
//-------------------------------------
#ifndef _ASM_
typedef struct t_cmbx {
    ATR     mbxatr;                     /*!< Mailbox attribute                      */
    PRI     maxmpri;                    /*!< Maximum message priority               */
    VP      mprihd;                     /*!< Start address of the area for message
                                             queue headers for each message priority */
}T_CMBX;
#endif  /* !_ASM_ */

//=============================================================
// Extended synchronization and communication functions
//=============================================================
//-------------------------------------
// Mutex creation information packet
//-------------------------------------
#ifndef _ASM_
typedef struct t_cmtx {
    ATR     mtxatr;                     /*!< Mutex attribute                        */
    PRI     ceilpri;                    /*!< Mutex ceiling priority                 */
}T_CMTX;
#endif    /* !_ASM_ */

//=============================================================
// Interrupt management functions
//=============================================================
//-------------------------------------
// Interrupt service routine information packet
//-------------------------------------
#ifndef _ASM_
typedef struct t_dinh {
    ATR     inhatr;                     /*!< Interrupt handler attribute            */
    FP      inthdr;                     /*!< Interrupt handler start address        */
} T_DINH;
#endif  /* !_ASM_ */

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/

#ifndef _ASM_
//-------------------------------------------------------------
// Task Management Functions
//-------------------------------------------------------------
ER sta_tsk(ID tskid, VP_INT stacd);
void ext_tsk(void);
ER ter_tsk(ID tskid);
ER chg_pri(ID tskid, PRI tskpri);
ER get_pri(ID tskid, PRI *p_tskpri);
ER CRE_TSK(ID tskid, const T_CTSK *pk_ctsk);

//-------------------------------------------------------------
// Task Dependant Synchronization Functions
//-------------------------------------------------------------
ER slp_tsk(void);
ER tslp_tsk(TMO tmout);
ER wup_tsk(ID tskid);
ER iwup_tsk(ID tskid);
ER_UINT can_wup(ID tskid);
ER rel_wai(ID tskid);
ER irel_wai(ID tskid);

//-------------------------------------------------------------
// Synchronization and Communication Functions
//-------------------------------------------------------------
// ------ Semaphores ------
ER cre_sem(ID semid, T_CSEM *pk_csem);
ER del_sem(ID semid);
ER wai_sem(ID semid);
ER pol_sem(ID semid);
ER twai_sem(ID semid, TMO tmout);
ER sig_sem(ID semid);
ER isig_sem(ID semid);

// ------ Event flags ------
ER cre_flg(ID flgid, T_CFLG *pk_cflg);
ER del_flg(ID flgid);
ER set_flg(ID flgid, FLGPTN setptn);
ER iset_flg(ID flgid, FLGPTN setptn);
ER clr_flg(ID flgid, FLGPTN clrptn);
ER wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
ER pol_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn);
ER twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout);

// ------ Mailboxes ------
ER cre_mbx(ID mbxid, T_CMBX *pk_cmbx);
ER del_mbx(ID mbxid);
ER snd_mbx(ID mbxid, T_MSG *pk_msg);
ER isnd_mbx(ID mbxid, T_MSG *pk_msg);
ER rcv_mbx(ID mbxid, T_MSG **ppk_msg);
ER prcv_mbx(ID mbxid, T_MSG **ppk_msg);
ER trcv_mbx(ID mbxid, T_MSG **ppk_msg, TMO tmout);

//-------------------------------------------------------------
// Extended Synchronization and Communication Functions
//-------------------------------------------------------------
// ------ Mutexes ------
ER cre_mtx(ID mtxid, T_CMTX *pk_cmtx);
ER del_mtx(ID mtxid);
ER loc_mtx(ID mtxid);
ER ploc_mtx(ID mtxid);
ER tloc_mtx(ID mtxid, TMO tmout);
ER unl_mtx(ID mtxid);

//-------------------------------------------------------------
// Time Management Functions
//-------------------------------------------------------------
ER set_tim(SYSTIM *p_systim);
ER get_tim(SYSTIM *p_systim);

//-------------------------------------------------------------
// System State Management Functions
//-------------------------------------------------------------
ER rot_rdq(PRI tskpri);
ER irot_rdq(PRI tskpri);
ER get_tid(ID *p_tskid);
ER iget_tid(ID *p_tskid);
ER loc_cpu(void);
ER unl_cpu(void);
BOOL sns_loc(void);
ER dis_dsp(void);
ER ena_dsp(void);

//-------------------------------------------------------------
// Utility Functions
//-------------------------------------------------------------
char *rin_hwos_get_version(uint8_t mode);
void hwos_set_mpri_operation(int32_t flag);
int32_t hwos_set_tick_time(uint32_t tick_time);

#endif  /* !_ASM_ */


/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
//=============================================================
// Constants
//=============================================================
//-------------------------------------
// Object Attribute
//-------------------------------------
// ------ For task ------
#define TA_HLNG     0x00                /*!< Start a processing though a high-level language interface  */
#define TA_ASM      0x01                /*!< Start a processing though an assembly language interface   */
#define TA_ACT      0x02                /*!< Task is activated after the creation                       */

// ------ For semaphores, event flags,,,  ------
#define TA_TFIFO    0x00                /*!< Task wait queue is in FIFO order                           */
#define TA_TPRI     0x01                /*!< Task wait queue is in task priority order                  */

// ------ For eventflags  ------
#define TA_WMUL     0x02                /*!< Multiple tasks are allowed to be in the waiting state
                                             for the evntflag                                           */
#define TA_CLR      0x04                /*!< Eventflag's bit pattern is cleared when a task is released
                                             from the waiting state for that eventflag                  */

// ------ For mailbox ------
#define TA_MFIFO    0x00                /*!< Message queue is in FIFO order                             */
#define TA_MPRI     0x02                /*!< Message queue is in message priority order                 */

// ------ For mutex  ------
#define TA_INHERIT  0x02                /*!< Mutex uses the priority inheriance protocol (Not used)     */
#define TA_CEILING  0x03                /*!< Mutex uses the priority ceiling protocol (Not used)        */

//-------------------------------------
// Service Call Operational Mode
//-------------------------------------
// ------ For event flags  ------
#define TWF_ANDW    0x00                /*!< AND waiting condition for an eventflag                     */
#define TWF_ORW     0x01                /*!< OR  waiting condition for an eventflag                     */

//-------------------------------------
// Other constants
//-------------------------------------
// ------ For task ------
#define TSK_SELF    0x00                /*!< Specifying invoking task                                   */
#define TSK_NONE    0x00                /*!< NO applicable task                                         */

#define TPRI_SELF   0x00                /*!< Specifying the vase priority of the invoking task          */
#define TPRI_INI    0x00                /*!< Specifying the initial priority of the task                */

//=============================================================
// Kernel Configuration Constants (depend on HW-RTOS architecture)
//=============================================================
//-------------------------------------
// Priority Range
//-------------------------------------
#define TMIN_TPRI    1                 /*!< Minimum task priority(=1)                                   */
#define TMAX_TPRI   15                 /*!< Maximum task priority                                       */

#define TMIN_MPRI    1                  /*!< Minimum message priority(=1)                               */
#define TMAX_MPRI    7                  /*!< Maximum message priority                                   */

//-------------------------------------
// Number of Bits in Bit patterns
//-------------------------------------
#define TBIT_FLGPTN 16                  /*!< Number of bits asn eventflag                                */

//-------------------------------------
// Others
//-------------------------------------
#define TMAX_MAXSEM 31                  /*!< Maximum value of the maximum definable semaphore resource count */

//-------------------------------------
// ID Range
//-------------------------------------
#define TMIN_TSKID              1                   /*!< Max task ID        */
#define TMAX_TSKID             64                   /*!< Max task ID        */
#define TMIN_SEMID              1                   /*!< Max semaphore ID   */
#define TMAX_SEMID            128                   /*!< Max semaphore ID   */
#define TMIN_FLGID              1                   /*!< Max eventflag ID   */
#define TMAX_FLGID             64                   /*!< Max eventflag ID   */
#define TMIN_MBXID              1                   /*!< Max mailbox ID     */
#define TMAX_MBXID             64                   /*!< Max mailbox ID     */
#define TMIN_MTXID            TMIN_SEMID            /*!< Max mutex ID       */
#define TMAX_MTXID            TMAX_SEMID            /*!< Max mutex ID       */

///////////////////////////////////////////////////////////////////////////////////////////////
// HW-RTOS original
///////////////////////////////////////////////////////////////////////////////////////////////

/***********************************************************************************************************************
 Structures
 **********************************************************************************************************************/
//=============================================================
// Static table
//=============================================================
//-------------------------------------
// Static task table packet
//-------------------------------------
#ifndef _ASM_
typedef struct task_table {
    ID  id;                             /*!< Task ID                                */
    T_CTSK  t_ctsk;                     /*!< Task creation information packet       */
}TSK_TBL;
#endif  /* !_ASM_ */

//-------------------------------------
// Static semaphore table packet
//-------------------------------------
#ifndef _ASM_
typedef struct semaphore_table {
    ID  id;                             /*!< Semaphore ID                           */
    T_CSEM  pk_csem;                    /*!< Semaphore creation information packet   */
}SEM_TBL;
#endif    /* !_ASM_ */

//-------------------------------------
// Static eventflag table packet
//-------------------------------------
#ifndef _ASM_
typedef struct flag_table {
    ID  id;                             /*!< Event flag ID                           */
    T_CFLG  pk_cflg;                    /*!< Event flag creation information packet   */
}FLG_TBL;
#endif    /* !_ASM_ */

//-------------------------------------
// Static mailbox table packet
//-------------------------------------
#ifndef _ASM_
typedef struct mailbox_table {
    ID  id;                             /*!< Mailbox ID                             */
    T_CMBX  pk_cmbx;                    /*!< Mailbox creation information packet     */
}MBX_TBL;
#endif    /* !_ASM_ */

//-------------------------------------
// Static mutex table packet
//-------------------------------------
#ifndef _ASM_
typedef struct mutex_table {
    ID  id;                             /*!< Mutex ID                                */
    T_CMTX  pk_cmtx;                    /*!< Mutex creation information packet        */
}MTX_TBL;
#endif    /* !_ASM_ */

//-------------------------------------
// Static interrupt table packet
//-------------------------------------
#ifndef _ASM_
typedef struct interrupt_table {
    INHNO  inhno;                       /*!< Interrupt handler number to be defined    */
    T_DINH  pk_dinh;                    /*!< Pointer to the packet containing the interrupt handler definition information    */
}INT_TBL;
#endif    /* !_ASM_ */

//-------------------------------------
// Static HW-ISR table packet
//-------------------------------------
#ifndef _ASM_
typedef struct hwisr_table {
    INHNO   inhno;                      /*!< Interrupt handler number to be defined */
    UINT    hwisr_syscall;              /*!< System call                            */
    ID      id;                         /*!< Target ID                              */
    FLGPTN  setptn;                     /*!< Bit pattern (only set_flg)             */
}HWISR_TBL;
#endif    /* !_ASM_ */

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
#ifndef _ASM_
ER hwos_setup(void);
ER hwos_init(void);
#endif  /* !_ASM_ */

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define MAX_CONTEXT_NUM     TMAX_TSKID          /*!< Max context number     */
#define MAX_SEMAPHORE_NUM   TMAX_SEMID          /*!< Max semaphore number   */
#define MAX_EVENTFLAG_NUM   TMAX_FLGID          /*!< Max eventflag number   */
#define MAX_MAILBOX_NUM     TMAX_MBXID          /*!< Max mailbox number     */
#define MAX_MUTEX_NUM       MAX_SEMAPHORE_NUM   /*!< Max mutex number       */

#define MAX_PRIORITY_NUM    TMAX_TPRI           /*!< Max priority number    */
#define MAX_SEMAPHORE_CNT   TMAX_MAXSEM         /*!< Max semaphore count    */

#define HWOS_TBL_END        (-1)                /*!< Initialize table end mark */
#define TASK_TBL_END        HWOS_TBL_END        /*!< Task table end ID      */
#define SEMAPHORE_TBL_END   HWOS_TBL_END        /*!< Semaphore table end ID */
#define EVENTFLAG_TBL_END   HWOS_TBL_END        /*!< Eventflag table end ID */
#define MAILBOX_TBL_END     HWOS_TBL_END        /*!< Mailbox table end ID   */
#define MUTEX_TBL_END       HWOS_TBL_END        /*!< Mutex table end ID     */
#define INT_TBL_END         0xffffffff          /*!< Interrupt table end ID */
#define HWISR_TBL_END       0xffffffff          /*!< HW-ISR table end ID    */

//-------------------------------------
// HW-ISR information
//-------------------------------------
#define MAX_QINT_NUM       32                   /*!< Max QINT number        */

#define HWISR_SET_FLG        1                    /*!< set_flg              */
#define HWISR_SIG_SEM        2                    /*!< sig_sem              */
#define HWISR_REL_WAI        3                    /*!< rel_wai              */
#define HWISR_WUP_TSK        4                    /*!< wup_tsk              */

//-------------------------------------
// Operation setting when the mail box is TA_MPRI attribute.
//-------------------------------------
#define HWOS_DISABLE_MPRI           (0)                 /*!< Disable the API of mail sending and receiving. */
#define HWOS_ENABLE_MPRI            (1)                 /*!< Check whether mail can send.                   */

#endif // KERNEL_H__

#ifdef __cplusplus
}
#endif
