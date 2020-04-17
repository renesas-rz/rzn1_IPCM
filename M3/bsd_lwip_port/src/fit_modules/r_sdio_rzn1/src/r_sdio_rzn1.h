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
 * $Revision: 1347 $
 * $Date: 2019-03-08 11:11:05 +0000 (Fri, 08 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_sdio_rzn1.h
 * Description  :  SDIO control functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef R_SDIO_RZN1_H__
#define R_SDIO_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define SDIO_TIMER_TICKS                (1000000u) /* 10ms per tick */
/***********************************************************************************************************************
 Variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Functions
 **********************************************************************************************************************/
void sdio_getdrivernumber (uint8_t *sdio_version);
void sdio_driver_init (void);
ER_RET sdio_open (uint8_t SDIO_number);
void sdio_close (uint8_t SDIO_number);
ER_RET sdio_register_call_back (uint8_t SDIO_number, sdio_insert_eject_callback call_back);
ER_RET sdio_set_trans_config (uint8_t SDIO_number, SDIO_TRANS_CTRL transfer_params, uint16_t block_size);
ER_RET sdio_send_cmd (uint8_t SDIO_number, SDIO_COMMAND *command);
ER_RET sdio_get_response (uint8_t SDIO_number, SDIO_RESPONSE_TYPE response_type, uint32_t *response);
ER_RET sdio_set_clock_div (uint8_t SDIO_number, SDIO_CLK_DIV clk_div);
ER_RET sdio_get_write_protection (uint8_t SDIO_number, bool *write_protected);
ER_RET sdio_wait_for_interrupt (uint8_t SDIO_number, uint32_t wait_time, uint16_t mask);
ER_RET sdio_set_hc_bus_width (uint8_t SDIO_number, SDIO_TRANS_WIDTH bus_width);

#endif /* R_SDIO_RZN1_H__ */
