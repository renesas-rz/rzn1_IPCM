/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only
 * intended for use with Renesas products. No other uses are authorized. This
 * software is owned by Renesas Electronics Corporation and is protected under
 * all applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
 * LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
 * TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
 * ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
 * FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
 * ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
 * BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software
 * and to discontinue the availability of this software. By using this software,
 * you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 * Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * $Revision: 1298 $
 * $Date: 2019-02-25 10:17:29 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_lcdc_rzn1.h
 * Description  :  LCDC driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_LCDC_RZN1_H__
#define R_LCDC_RZN1_H__

/***********************************************************************************************************************
 I N C L U D E
 **********************************************************************************************************************/

/***********************************************************************************************************************
 D E F I N E s
 **********************************************************************************************************************/
/* 33.3 MHz LCDC Control CLK
 * 1GHz / PWRCTRL_PG0_LCDCDIV gives LCDC clock
 * Divider will be set to 30 for a 33.33 MHz LCDC Clock frequency
 * Divider value can be 12-64                                         */
#define LCDC_CLOCK_DIVIDER      (30)
#define LCDC_CLK_FREQ      (RZN1_MAIN_PLL/LCDC_CLOCK_DIVIDER)
#define LCDC_CLK_FREQ_MHZ  (LCDC_CLK_FREQ/1000000)
#define LCDC_WAIT_TIMEOUT_COUNT    (5000)



/***********************************************************************************************************************
 T Y P E D E F s
 **********************************************************************************************************************/

typedef void (*lcdc_update_complete_callback_t)(void);

/***********************************************************************************************************************
 P R O T O T Y P E s
 **********************************************************************************************************************/

ER_RET  lcdc_driver_init(void);
ER_RET  lcdc_driver_uninit(void);

ER_RET  lcdc_port_open(lcdc_port_config_t *port_config);
ER_RET  lcdc_port_close(void);

ER_RET  lcdc_reset(void);

ER_RET  tsd_driver_init(gpio_callback ts_int_callback);
ER_RET  tsd_driver_uninit (void);

ER_RET  lcdc_set_port_config(lcdc_port_config_t *port_config);
ER_RET  lcdc_get_port_config(lcdc_port_config_t *port_config);
ER_RET  lcdc_blank_display(uint32_t colour);
ER_RET  lcdc_blink_display(lcd_rectangle_t *display_update_area, lcdc_blink_mode_e blink_mode );
ER_RET  lcdc_display_update(lcd_rectangle_t *display_update_area, uint32_t *buf, uint32_t buf_len);
ER_RET  lcdc_fill_rectangle (lcd_rectangle_t *display_update_area, uint32_t colour);

ER_RET  lcdc_set_completion_callback(lcdc_update_complete_callback_t update_complete_callback);

#endif /* R_LCDC_RZN1_H__ */
