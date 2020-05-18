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
 * $Revision: 1290 $
 * $Date: 2019-02-20 17:01:01 +0000 (Wed, 20 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_i2c_rzn1.h
 * Description  :  I2C driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_I2C_RZN1_H__
#define R_I2C_RZN1_H__

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include "r_i2c_rzn1_if.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/* 20 MHz I2C Control CLK
 * 1GHz / PWRCTRL_PG0_I2CDIV gives I2C clock
 * Divider will be set to 50 for a 20 MHz I2C Clock frequency
 * Divider value can be 12-64                                         */
#define I2C_CLOCK_DIVIDER       (12)
#define I2C_CLK_FREQ            (RZN1_MAIN_PLL/I2C_CLOCK_DIVIDER)
#define I2C_CLK_FREQ_MHZ        (I2C_CLK_FREQ/1000000)
#define I2C_WAIT_TIMEOUT_COUNT  (5000)

/* High, Low times in nsecs in Standard mode (100 kbits per sec)*/
#define I2C_SS_SCL_HIGH         (4000)
#define I2C_SS_SCL_LOW          (4700)

/* High, Low times in nsecs in Fast mode (400 kbits per sec)*/
#define I2C_FS_SCL_HIGH         (600)
#define I2C_FS_SCL_LOW          (1300)

/* High, Low times in nsecs in High-Speed mode (1000 kbitsps)*/
#define I2C_HS_SCL_HIGH         (260)
#define I2C_HS_SCL_LOW          (500)

/* Command settings */
#define I2C_BUSY            (0x80000000)
#define I2C_CMD_READ        (1<<8)
#define I2C_CMD_WRITE       (0<<8)
#define I2C_CMD_STOP        (1<<9)
#define I2C_ADDR_MASK       (0x7F)
#define I2C_DATA_MASK       (0xFF)

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

typedef struct
{
        uint32_t size; /* Total flash size */
        uint32_t page_size; /* Write (page) size */
} I2C_PARAMETERS_TYPE_T;

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
uint8_t i2c_get_major_version_num (void);
uint8_t i2c_get_minor_version_num (void);
ER_RET i2c_driver_init (void);
ER_RET i2c_driver_uninitialise (void);
ER_RET i2c_channel_open (uint8_t i2c_chan_num);
ER_RET i2c_channel_close (uint8_t chan_num);
ER_RET i2c_reset (uint8_t chan_num);
ER_RET i2c_set_chan_config (uint8_t chan_num, I2C_CHANNEL_CONFIG_T *channel_config);
ER_RET i2c_get_chan_config (uint8_t chan_num, I2C_CHANNEL_CONFIG_T *channel_config);
ER_RET i2c_set_trans_completedcallback (uint8_t i2c_chan_num,
        i2c_transfer_complete_callback_t transfer_complete_callback);
ER_RET i2c_sync_read (uint8_t chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len);
ER_RET i2c_sync_write (uint8_t chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len);
ER_RET i2c_async_read (uint8_t chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len);
ER_RET i2c_async_write (uint8_t chan_num, uint32_t i2c_slave_addr, uint8_t *addr, uint32_t addr_len, uint8_t *buf,
        size_t data_len);
void i2c_transfer_completed (uint8_t chan_num);

#endif /* R_I2C_RZN1_H__ */
