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
 * $Revision: 1338 $
 * $Date: 2019-03-06 09:46:24 +0000 (Wed, 06 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_lcdc_rzn1_if.h
 * Description  :  LCDC driver API definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/
#ifndef R_LCDC_RZN1_IF_H__
#define R_LCDC_RZN1_IF_H__

/*
 *****************************************************************************
 * Doxygen Summary block
 **********************************************************************************************************************/
/*!
 * @defgroup LCDC_MODULE RZN1 LCDC Bare Metal Driver
 * @{
 * @file
 * @brief LCDC Bare Metal Driver
 * @details Supports initialisation, configuration and updating TFT LCD Panel
 * @} */
/***********************************************************************************************************************
 * End of Doxygen Summary block
 **********************************************************************************************************************/

/***********************************************************************************************************************
 I N C L U D E
 **********************************************************************************************************************/
#include "platform.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/* Version Number of API */
#define LCDC_DRIVER_MAJOR_VERSION_NUMBER    (1)
#define LCDC_DRIVER_MINOR_VERSION_NUMBER    (2)

#define LCDC_PORT_1                         (0)
#define LCDC_TS_GPIO_PORT                   (GPIO_PORT_3A_PIN_26)       /* GPIO pin configured for touch screen inputs */


/* Supported Bits per Pixel */
#define LCDC_DRIVER_BPP_1                   (1)
#define LCDC_DRIVER_BPP_2                   (2)
#define LCDC_DRIVER_BPP_4                   (4)
#define LCDC_DRIVER_BPP_8                   (8)
#define LCDC_DRIVER_BPP_16                  (16)
#define LCDC_DRIVER_BPP_18                  (18)
#define LCDC_DRIVER_BPP_24                  (24)

#define INVALID_POINT_X                     (0xffff)
#define INVALID_POINT_Y                     (0xffff)

#define TOUCH_EVENT_MASK                    (0xc0)
#define TOUCH_EVENT_DOWN                    (0)
#define TOUCH_EVENT_UP                      (0x40)
#define TOUCH_EVENT_CONTACT                 (0x80)
#define TOUCH_EVENT_NONE                    (0xc0)

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/

/* LCDC States */
typedef enum
{
    LCDC_PORT_STATE_CLOSED = 0,     /* LCDC Port not configured and not enabled */
    LCDC_PORT_STATE_OPEN,           /* LCDC Port configured and enabled */
    LCDC_PORT_STATE_BUSY            /* LCDC port display currently being updated */
} lcdc_port_state_e;

/* Touch screen driver states */
typedef enum
{
    TS_STATE_CLOSED = 0,            /* touch screen driver not configured & not enabled */
    TS_STATE_OPEN,                  /* touch screen driver configured and enabled */
} ts_state_e;

/* Touch screen events */
typedef enum
{
    TS_EVENT_NONE = 0,              /* No touch screen event */
    TS_EVENT_PEN_DOWN,              /* first touch on touch screen */
    TS_EVENT_PEN_DRAG,              /* drag on touch screen */
    TS_EVENT_PEN_UP                 /* final touch on touch screen */
} ts_event_e;


/* LCDC Control Request */
typedef enum
{
    LCDC_CONTROL_SET_PORT_CONFIG,           /* Set port configuration */
    LCDC_CONTROL_GET_PORT_CONFIG,           /* Get port configuration */
    LCDC_CONTROL_GET_PORT_STATE,
    LCDC_CONTROL_RESET                     /* Reset the LCDC  */
} lcdc_control_request_e;

/* LCDC Blink Mode */
typedef enum
{
    LCDC_BLINK_MODE_OFF = 0,            /* Disable blink */
    LCDC_BLINK_MODE_SLOW,               /* Enable blink SLOW speed*/
    LCDC_BLINK_MODE_MEDIUM,             /* Enable blink MEDIUM speed*/
    LCDC_BLINK_MODE_FAST                /* Enable blink FAST */
} lcdc_blink_mode_e;


/* Pixel format */
typedef enum
{
    LCD_RGB888,
    LCD_RGB666,
    LCD_RGB565,
    LCD_RGB555,
    LCD_BGR888,
    LCD_BGR666,
    LCD_BGR565,
    LCD_BGR555
} lcd_pixel_format_e;


typedef struct
{
    uint32_t            bpp;            /* bits per pixel */
    lcd_pixel_format_e  pixel_format;
    uint32_t            x_res;          /* max pixels horizontally */
    uint32_t            y_res;          /* max pixels vertically */
    uint16_t           *palette;        /* palette lookup table values , required for LCDC_DRIVER_BPP_1, LCDC_DRIVER_BPP_2, LCDC_DRIVER_BPP_4, LCDC_DRIVER_BPP_8 */
} lcdc_port_config_t;

/* Point pixel coordinates  */
typedef struct
{
    uint32_t lcd_point_x;
    uint32_t lcd_point_y;
} lcd_point_t;

/* Rectangle pixel coordinates  */
typedef struct
{
    uint32_t lcd_rectangle_left;
    uint32_t lcd_rectangle_top;
    uint32_t lcd_rectangle_right;
    uint32_t lcd_rectangle_bottom;
} lcd_rectangle_t;

/* Display buffer */
typedef struct
{
    uint8_t            *display_buf_mem;        /* pointer to mem area for display buffer */
    uint32_t            display_buf_mem_size;
    uint32_t            display_x_res;          /* display buffer width in pixels */
    uint32_t            display_y_res;          /* display buffer height in pixels */
} lcdc_display_buffer_t;

typedef struct
{
    ts_event_e          event;                  /* touch screen event */
    lcd_point_t         position;               /* touch position on the display */
} tsd_touch_event_info;

/*! Touch Screen event callback */
typedef void (*ts_event_callback_t)(tsd_touch_event_info *touch_screen_event, uint8_t num_positions);

/***********************************************************************************************************************
 Global functions
 **********************************************************************************************************************/
void    R_LCDC_GetVersion (void *buf);
ER_RET  R_LCDC_Init (void);
ER_RET  R_LCDC_Uninitialise (void);
ER_RET  R_TSD_Init(gpio_callback ts_int_callback);
ER_RET  R_TSD_Uninitialise (void);
ER_RET  R_LCDC_Open (lcdc_port_config_t *lcdc_config);
ER_RET  R_LCDC_Close (void);
ER_RET  R_LCDC_Control (lcdc_control_request_e control_request, uint8_t *buf);
ER_RET  R_LCDC_DisplayUpdate (lcd_rectangle_t *display_update_area, uint32_t *buf, uint32_t buf_len); /* Update a section of the display with the given image */
ER_RET  R_LCDC_FillRectangle (lcd_rectangle_t *display_update_area, uint32_t colour);                /* Set a section of the display to a single colour */
ER_RET  R_LCDC_Blank (uint32_t colour);                                                             /* Clear (blank) the whole display with given colour*/
ER_RET  R_LCDC_Blink (lcd_rectangle_t *display_blink_area, lcdc_blink_mode_e blink_mode);            /* Blink a section of the display */


#endif /* R_LCDC_RZN1_IF_H__ */
