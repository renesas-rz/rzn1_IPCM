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
 * FILE         :  errcodes.h
 * Description  :  Definition of error codes
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef ERRCODES_H__
#define ERRCODES_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
/* type of error code */
typedef int ER_RET;                            /*!< Function return type will return the error code */

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/* define of error code */
#define ER_OK      ((ER_RET)0)                /*!< Error code for Normal end (no error) */
#define ER_NG      ((ER_RET)-1)                /*!< Error code for Abnormal end (error)  */
#define ER_SYS     ((ER_RET)(2 * ER_NG))    /*!< Error code for Undefined error       */
#define ER_PARAM   ((ER_RET)(3 * ER_NG))    /*!< Error code for Invalid parameter     */
#define ER_NOTYET  ((ER_RET)(4 * ER_NG))    /*!< Error code for Incomplete processing */
#define ER_NOMEM   ((ER_RET)(5 * ER_NG))    /*!< Error code for Out of memory         */
#define ER_BUSY    ((ER_RET)(6 * ER_NG))    /*!< Error code for Busy                  */
#define ER_INVAL   ((ER_RET)(7 * ER_NG))    /*!< Error code for Invalid state         */
#define ER_TIMEOUT ((ER_RET)(8 * ER_NG))    /*!< Error code for Timeout occurs        */

#endif    // ERRCODES_H__
