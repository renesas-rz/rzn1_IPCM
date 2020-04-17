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
 * FILE         :  itron.h
 * Description  :  ITRON General Definitions (Data Types, Constants, Macros)
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef ITRON_H__
#define ITRON_H__

#ifdef  __IASMARM__
#ifndef _ASM_
#define _ASM_
#endif
#endif

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#ifndef _ASM_
#include <stddef.h>
#endif  /* !_ASM_ */

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
//-------------------------------------
// ITRON General Data Types
//-------------------------------------
#ifndef _ASM_
typedef signed char     B;              /*!<   Signed  8-bit integer */
typedef signed short    H;              /*!<   Signed 16-bit integer */
typedef signed long     W;              /*!<   Signed 32-bit integer */
typedef unsigned char   UB;             /*!< Unsigned  8-bit integer */
typedef unsigned short  UH;             /*!< Unsigned 16-bit integer */
typedef unsigned long   UW;             /*!< Unsigned 32-bit integer */

typedef char            VB;             /*!<  8-bit value with unknown data type */
typedef short           VH;             /*!< 16-bit value with unknown data type */
typedef long            VW;             /*!< 32-bit value with unknown data type */

typedef void            *VP;            /*!< Pointer to an unknown data type */
typedef void            (*FP)(void);    /*!< Processing unit start address (pointer to a function) */

typedef signed int      INT;            /*!<   Signed integer for the processor */
typedef unsigned int    UINT;           /*!< Unsigned integer for the processor */

typedef INT             BOOL;           /*!< Boolean value TRUE(1) or FALSE(0) */

typedef INT             FN;             /*!< Function code */
typedef INT             ER;             /*!< Error code */
typedef INT             ID;             /*!< Object ID number */
typedef UINT            ATR;            /*!< Object attribute */
typedef UINT            STAT;           /*!< Object state */
typedef UINT            MODE;           /*!< Service call operational mode */
typedef INT             PRI;            /*!< Priority */
typedef UINT            SIZE;           /*!< Memory area size */

typedef INT             TMO;            /*!< Timeout */
typedef UINT            RELTIM;         /*!< Relative time */
typedef UINT            SYSTIM;         /*!< system clock (v4.0) */

typedef VP              VP_INT;         /*!< Pointer to an unknown data type, or a signed integer for the prosessor */

typedef ER              ER_BOOL;        /*!< Error code or a boolean value */
typedef ER              ER_ID;          /*!< Error code or an object ID number */
typedef ER              ER_UINT;        /*!< Error code or an unsigned integer */

//-------------------------------------
// ITRON Data Types (for Eventflag)
//-------------------------------------
typedef UINT            FLGPTN;         /*!< Bit pattern of the eventflag */

//-------------------------------------
// ITRON Data Types (for Mailbox)
//-------------------------------------
typedef    struct t_msg {               /*!< Message header for a mailbox */
    struct t_msg    *next;
} T_MSG;

typedef    struct t_msg_pri {           /*!< Message header with a messege priority for a mailbox */
    T_MSG        msgque;                /*!< Message header */
    PRI            msgpri;              /*!< Message priority */
} T_MSG_PRI;

//-------------------------------------
// ITRON Data Types (for Interrupt)
//-------------------------------------
typedef UINT            INHNO;          /*!< Interrupt handler number */
typedef UINT            INTNO;          /*!< Interrupt number */

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
//-------------------------------------
// General Constans
//-------------------------------------
#ifndef NULL
#define NULL        0                   /*!< Invalid pointer                */
#endif

#define TRUE        1                   /*!< True                           */
#define FALSE        0                  /*!< False                          */

#endif    /* !_ASM_ */

#define E_OK        0                   /*!< Normal completion              */

//-------------------------------------
// Main Error Codes
//-------------------------------------

// --- Internal Error Class ---
#define E_SYS        (-5)               /*!< System error                   */

// --- Unsupported Error Class ---
#define E_NOSPT        (-9)             /*!< Unsupported function           */
#define E_RSFN        (-10)             /*!< Reserved function code         */
#define E_RSATR        (-11)            /*!< Reserved attribute             */

// --- Parameter Error Class ---
#define E_PAR        (-17)              /*!< Parameter error                */
#define E_ID        (-18)               /*!< Invalid ID number              */

// --- Invoking Context Error Class ---
#define E_CTX        (-25)              /*!< Context error                  */
#define E_MACV        (-26)             /*!< Memory access violation        */
#define E_OACV        (-27)             /*!< Object access violation        */
#define E_ILUSE        (-28)            /*!< Illegal service call use       */

// --- Insufficient Resource Error Class ---
#define E_NOMEM        (-33)            /*!< Insufficient memory            */
#define E_NOID        (-34)             /*!< No ID number avalable          */

// --- Object State Error Class ---
#define E_OBJ        (-41)              /*!< Object state error             */
#define E_NOEXS        (-42)            /*!< Non-existent object            */
#define E_QOVR        (-43)             /*!< Queue overflow                 */

// --- Waiting Released Error Class ---
#define E_RLWAI        (-49)            /*!< Forced release from waiting    */
#define E_TMOUT        (-50)            /*!< Polling failure or timeout     */
#define E_DLT        (-51)              /*!< Waiting object deleted         */
#define E_CLS        (-52)              /*!< Waiting object state changed   */

// --- Warning Class ---
#define E_WBLK        (-57)             /*!< Non-blocking call accepted     */
#define E_BOVR        (-58)             /*!< Buffer overflow                */

// --- Original ---
#define E_UNKNOWN    (-99)              /*!< Implementation-soecific error code */

//-------------------------------------
// Object Attribute
//-------------------------------------
#define TA_NULL        0                /*!< Object attribute unspecified   */

//-------------------------------------
// Timeout Specification
//-------------------------------------
#define TMO_POL        0                /*!< Polling                        */
#define TMO_FEVR    (-1)                /*!< Waiting forever                */
#define TMO_NBLK    (-2)                /*!< Non blocking                   */


#endif // ITRON_H__
