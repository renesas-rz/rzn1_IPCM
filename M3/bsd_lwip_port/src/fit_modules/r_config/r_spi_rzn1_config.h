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
 * $Revision: 1299 $
 * $Date: 2019-02-25 12:05:48 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_spi_rzn1_config.h
 * Description  :  Configures the SPI module.
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef SPI_RZN1_CONFIG_HEADER_FILE
#define SPI_RZN1_CONFIG_HEADER_FILE

/***********************************************************************************************************************
 Configuration Options
 **********************************************************************************************************************/
/* SPECIFY WHETHER TO INCLUDE CODE FOR API PARAMETER CHECKING
 Available settings:
 BSP_CFG_PARAM_CHECKING_ENABLE:
 Utilizes the system default setting
 1:
 Includes parameter checking
 0:
 Compiles out parameter checking
 */

/* Uncomment if r_dma_rzn1_if is included in project */
#define r_dma_rzn1_spi_included

#define SPI_CFG_PARAM_CHECKING_ENABLE      (BSP_CFG_PARAM_CHECKING_ENABLE)

#define MAX_SPI_CHANNELS                    (6u)
#define MIN_SPI_SLAVE                       (4u)   /* Fist SPI that is a slave */

#define RX_THRESHOLD                        (4u)
#define TX_THRESHOLD                        (10u)

#define SPI_DEFAULT_INT_PRIORITY           (9u)

#endif /* SPI_RZN1_CONFIG_HEADER_FILE */
