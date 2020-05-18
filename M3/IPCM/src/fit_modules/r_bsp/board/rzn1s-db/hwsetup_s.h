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
 * FILE         :  hwsetup_s.h
 * Description  :  Hardware setup header file
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/* Multiple inclusion prevention macro */
#ifndef HWSETUP_H
#define HWSETUP_H

/***********************************************************************************************************************
Macro definitions
 **********************************************************************************************************************/
/* I2C Slave Address for I2C Devices on RZ/N1D or RZ/N1EB (Extender Board) - sw perspective
 Note (HW perspective):
 Following a START condition the I2C bus master must send the address of the slave it is
 accessing and the operation it wants to perform (read or write).
 The slave address , as defined below, is actually shifted left by 1 bit because
 The last bit of the first byte defines the operation to be performed. When set to logic 1 a
 read is selected while a logic 0 selects a write operation.                                   */
#define I2C_PORT_EXPANDER_SLAVE_ADDR    0x20                /* I2C Slave address of I2C Port Expander */
#define I2C_EEPROM_SLAVE_ADDR           0x50                /* I2C Slave address of on-board EEPROM */
#define I2C_EEPROM_SERIAL_NO_SLAVE_ADDR 0x58                /* I2C Slave address of on-board EEPROM to access its Serial Number */
#define I2C_CPLD_SLAVE_ADDR             0x34                /* I2C Slave address of CPLD */
#define I2C_TEMP_SENSOR_SLAVE_ADDR      0x49                /* I2C Slave address of Temperature Sensor */
#define I2C_TOUCH_CTRL_SLAVE_ADDR       0x38                /* I2C Slave address of Touch Controller */

/* I2C Port Expander Register addresses */
#define I2C_PORT_EXPANDER_IP0_ADDR    0x00                  /* Input Port Register Bank 0 address */
#define I2C_PORT_EXPANDER_IP1_ADDR    0x01                  /* Input Port Register Bank 1 address */
#define I2C_PORT_EXPANDER_IP2_ADDR    0x02                  /* Input Port Register Bank 2 address */
#define I2C_PORT_EXPANDER_IP3_ADDR    0x03                  /* Input Port Register Bank 3 address */
#define I2C_PORT_EXPANDER_IP4_ADDR    0x04                  /* Input Port Register Bank 4 address */

#define I2C_PORT_EXPANDER_OP0_ADDR    0x08                  /* Output Port Register Bank 0 address */
#define I2C_PORT_EXPANDER_OP1_ADDR    0x09                  /* Output Port Register Bank 1 address */
#define I2C_PORT_EXPANDER_OP2_ADDR    0x0A                  /* Output Port Register Bank 2 address */
#define I2C_PORT_EXPANDER_OP3_ADDR    0x0B                  /* Output Port Register Bank 3 address */
#define I2C_PORT_EXPANDER_OP4_ADDR    0x0C                  /* Output Port Register Bank 4 address */

#define I2C_PORT_EXPANDER_PI0_ADDR    0x10                  /* Polarity Inversion Register Bank 0 address */
#define I2C_PORT_EXPANDER_PI1_ADDR    0x11                  /* Polarity Inversion Register Bank 1 address */
#define I2C_PORT_EXPANDER_PI2_ADDR    0x12                  /* Polarity Inversion Register Bank 2 address */
#define I2C_PORT_EXPANDER_PI3_ADDR    0x13                  /* Polarity Inversion Register Bank 3 address */
#define I2C_PORT_EXPANDER_PI4_ADDR    0x14                  /* Polarity Inversion Register Bank 4 address */

#define I2C_PORT_EXPANDER_IOC0_ADDR    0x18                  /* I/O Configuration Register Bank 0 address */
#define I2C_PORT_EXPANDER_IOC1_ADDR    0x19                  /* I/O Configuration Register Bank 1 address */
#define I2C_PORT_EXPANDER_IOC2_ADDR    0x1A                  /* I/O Configuration Register Bank 2 address */
#define I2C_PORT_EXPANDER_IOC3_ADDR    0x1B                  /* I/O Configuration Register Bank 3 address */
#define I2C_PORT_EXPANDER_IOC4_ADDR    0x1C                  /* I/O Configuration Register Bank 4 address */

#define I2C_PORT_EXPANDER_MSK0_ADDR    0x20                  /* Mask Interrupt Register Bank 0 address */
#define I2C_PORT_EXPANDER_MSK1_ADDR    0x21                  /* Mask Interrupt Register Bank 1 address */
#define I2C_PORT_EXPANDER_MSK2_ADDR    0x22                  /* Mask Interrupt Register Bank 2 address */
#define I2C_PORT_EXPANDER_MSK3_ADDR    0x23                  /* Mask Interrupt Register Bank 3 address */
#define I2C_PORT_EXPANDER_MSK4_ADDR    0x24                  /* Mask Interrupt Register Bank 4 address */

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
/* Hardware setup funtion declaration */
void hardware_setup(void);

/* LED control function */
uint32_t led_get(void);
int32_t led_set(uint32_t val);
int32_t led_toggle(uint32_t val);

/* Dip Switch control function */
uint32_t dipsw_get(void);

/* End of multiple inclusion prevention macro */
#endif