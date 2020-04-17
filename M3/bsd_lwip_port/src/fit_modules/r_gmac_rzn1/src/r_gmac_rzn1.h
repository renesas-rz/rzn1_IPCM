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
 * $Revision: 1195 $
 * $Date: 2019-01-29 12:51:05 +0000 (Tue, 29 Jan 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_gmac_rzn1.h
 * Description  :  GMAC driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_GMAC_RZN1_H__
#define R_GMAC_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_gmac_rzn1_if.h"

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
typedef enum
{
    LINK_DOWN = 0, LINK_UP = 1,
} link_status;

typedef void (*gmac_callback)(uint8_t chan_num); //$REA
/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
ER_RET gmac_init ();
ER_RET gmac_open (const gmac_transfer_data *data);
ER_RET gmac_close (uint8_t chan_num, uint8_t port);
void gmac_uninit ();
void gmac_read (uint8_t chan_num, uint8_t ** p_buf, uint16_t * p_len);
ER_RET gmac_write (uint8_t chan_num, uint8_t port, const gmac_eth_frame *eth_frame_info);
ER_RET gmac_set_speed (uint8_t chan_num, uint8_t port, gmac_operation_mode_t mode);
ER_RET gmac_filtering_config (uint8_t chan_num, gmac_filter_config *filtering_options);
void auto_config_speed (volatile uint32_t *reg, uint32_t conv_ctrl, uint8_t phy_addr);
void gmac_register_callback(gmac_callback cb);
#endif /* R_GMAC_RZN1_H__ */
