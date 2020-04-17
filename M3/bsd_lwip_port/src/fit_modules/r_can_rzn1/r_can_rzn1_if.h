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
 * $Revision: 1166 $
 * $Date: 2019-01-17 14:01:52 +0000 (Thu, 17 Jan 2019) $
 *
 * PROJECT NAME :   RZ/N1 bare metal Drivers
 * FILE         :   r_can_rzn1_if.h
 * Description  :   CAN driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_CAN_RZN1_IF_H__
#define R_CAN_RZN1_IF_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "r_can_rzn1.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/* Version Number of API. */
#define CAN_DRIVER_MAJOR_VERSION_NUMBER         (1)
#define CAN_DRIVER_MINOR_VERSION_NUMBER         (0)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/* CAN  Channel States */
typedef enum {
    CAN_STATE_NOT_INIT = 0, /* CAN un-initialised */
    CAN_STATE_INIT, /* CAN initialised */
    CAN_STATE_CHANNEL_OPEN, /* Channel initialised and idle */
    CAN_STATE_CHANNEL_CLOSED, /* Channel uninitialised */
    CAN_STATE_CHANNEL_BUSY, /* Channel currently being used for reading sample */
} CAN_IF_STATE_E;

/* CAN Control Request */
typedef enum {
    CAN_CONTROL_SET_CHAN_CALLBACK, /* Set channel callback for CAN interrupts */
    CAN_CONTROL_GET_CHAN_STATE, /* Get channel state*/
    CAN_CONTROL_GET_CHAN_CONFIG, /* Get channel configuration */
    CAN_CONTROL_SET_CHAN_RESET, /* Set channel into Reset state */
    CAN_CONTROL_CLEAR_CHAN_RESET, /* Exit channel from Reset state */
    CAN_CONTROL_SET_CHAN_BITRATE, /* Set channel Bitrate */
    CAN_CONTROL_SET_CHAN_FILTER, /* Set channel Filter */
    CAN_CONTROL_START_CHAN_SYNC_PULSE, /* Start channel Synch pulse (CANopen) */
    CAN_CONTROL_STOP_CHAN_SYNC_PULSE, /* Stop channel Synch pulse (CANopen) */
    CAN_CONTROL_GET_CHAN_STATS, /* Get channel  Communication Statistics */
    CAN_CONTROL_SET_TEST_MODE, /* Enable/disable channel Test modes */
} CAN_CONTROL_REQUEST_E;

/***********************************************************************************************************************
 Default parameters
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Global functions
 **********************************************************************************************************************/
void R_CAN_GetVersion(void *buf);
ER_RET R_CAN_Init(void);
ER_RET R_CAN_Uninitialise(void);
ER_RET R_CAN_Open(uint8_t chan_num);
ER_RET R_CAN_Close(uint8_t chan_num);
ER_RET R_CAN_Write(uint8_t chan_num, CAN_MSG_T * ptr_msg);
ER_RET R_CAN_Control(uint8_t chan_num, CAN_CONTROL_REQUEST_E control_request,
        void *ptr_can_ctrl);
#endif /* R_CAN_RZN1_IF_H__ */
