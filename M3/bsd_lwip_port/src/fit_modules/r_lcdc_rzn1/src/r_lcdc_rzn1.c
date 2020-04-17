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
 * $Revision: 1336 $
 * $Date: 2019-03-06 09:34:44 +0000 (Wed, 06 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers, Sample application
 * FILE         :  r_lcdc_rzn1.c
 * Description  :  LCDC driver functions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/*
 *****************************************************************************
 * Doxygen Summary block
 **********************************************************************************************************************/
/*!
 * @ingroup LCDC_MODULE RZN1 LCDC Bare Metal Driver
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
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "platform.h"
#include "r_sysctrl_rzn1_if.h"
#include "r_gpio_rzn1_if.h"
#include "r_lcdc_rzn1_if.h"
#include "r_lcdc_rzn1_config.h"
#include "./inc/iodefine.h"
#include "r_lcdc_rzn1.h"
#include "timer.h"
#include "mcu_interrupts_if.h"
#include "log_serial_io.h"

/***********************************************************************************************************************
 D E F I N E
 **********************************************************************************************************************/
#define MAX_PALETTE_SIZE        (256 * 2)       /* max palette size supported (24 bits, 8 bits/colour) - 256 colours * 16 bits */
#define MAX_BITS_PER_PIXEL      (24)            /* max bpp supported by RZ/N1 */
#define MAX_BYTES_PER_PIXEL     (24/8)
#define MAX_MEM_BYTES_PER_PIXEL (4)             /* Pixel data will be stored in 4-byte location */
#define MAX_SCREEN_WIDTH        (800)           /* max screen width - pixels */
#define MAX_SCREEN_HEIGHT       (480)           /* max screen height - pixels */

/* BPP reg values */
#define LCDC_CR1_BPP_1          (0)
#define LCDC_CR1_BPP_2          (1)
#define LCDC_CR1_BPP_4          (2)
#define LCDC_CR1_BPP_8          (3)
#define LCDC_CR1_BPP_16         (4)
#define LCDC_CR1_BPP_18         (5)
#define LCDC_CR1_BPP_24         (6)

/* Reg definitions */
#define LCDC_CR1_LCE            (1<<0)
#define LCDC_CR1_LPE            (1<<1)
#define LCDC_CR1_BPP_MSK        (7<<2)
#define LCDC_CR1_RGB_MSK        (1<<5)
#define LCDC_CR1_DE_1           (1<<8)
#define LCDC_CR1_HSP_LOW        (1<<10)
#define LCDC_CR1_VSP_LOW        (1<<11)
#define LCDC_CR1_PSS            (1<<15)
#define LCDC_CR1_FBP            (1<<19)
#define LCDC_CR1_OPS_MASK       (7<<12)
#define LCDC_CR1_OPS_555        (1<<12)
#define LCDC_CR1_OPS_MSB        (1<<13)
#define LCDC_CR1_FDW_16BB       (2<<16)
#define LCDC_PCTR_PCR           (1<<10)

/* LCDC interrupt bit definitions */
#define LCDC_ISR_OFU            (0x0001)
#define LCDC_ISR_OFO            (0x0002)
#define LCDC_ISR_IFU            (0x0004)
#define LCDC_ISR_IFO            (0x0008)
#define LCDC_ISR_FER            (0x0010)
#define LCDC_ISR_MBE            (0x0020)
#define LCDC_ISR_VCT            (0x0040)
#define LCDC_ISR_BAU            (0x0080)
#define LCDC_ISR_LDD            (0x0100)

#define RZN1_LCD_PALETTE_REGS_OFFSET    (0x200)
#define MMR_OFFSET                      ( 0xFFC )

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  External function declarations
 **********************************************************************************************************************/
extern ER_RET r_gpio_iterruptenable(gpio_port_pin_t pin, gpio_int_en_t value); /* A maximum of 8 A-Port pins can be enabled for interrupts at a time */
extern ER_RET r_gpio_interruptmask(gpio_port_pin_t pin, gpio_int_mask_t value);
extern ER_RET r_gpio_interrupttriggertype(gpio_port_pin_t pin,
        gpio_int_trigger_type_t value);
extern ER_RET r_gpio_interrupttriggerpolarity(gpio_port_pin_t pin,
        gpio_int_polarity_t value);

/***********************************************************************************************************************
 * Local (private) variables
 **********************************************************************************************************************/
static      bool                lcdc_enabled = false;
volatile    LCDC_Type          *lcdc_base_address;
static      lcdc_port_config_t  lcd_config;
static      uint32_t            palette_size;
static      uint32_t            actual_bytes_per_pixel = 0;
static uint8_t display_fb;
static uint8_t back_fb;


/* Frame buffer, 64-byte aligned */
#pragma data_alignment=64
FB_BUFFER uint8_t fb[2][MAX_MEM_BYTES_PER_PIXEL * MAX_SCREEN_WIDTH * MAX_SCREEN_HEIGHT];
uint8_t display_fb = 0;
uint8_t back_fb = 1;
lcdc_blink_mode_e saved_blink_mode;

lcdc_update_complete_callback_t update_complete;


/***********************************************************************************************************************
 * Local (private) function declarations
 **********************************************************************************************************************/
static void handle_lcdc_interrupt (IRQn_Type *irq_num_ptr);
static uint32_t bpp_to_cr1mask (uint32_t bpp);


/***********************************************************************************************************************
* Function Name :   lcdc_driver_init
 **********************************************************************************************************************/
/*!
* @brief    Initialise LCDC port
* @details
* @param    void
* @retval   Error Status
 **********************************************************************************************************************/
ER_RET lcdc_driver_init(void)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num;
    uint32_t int_priority;

    ret_val = R_SYSCTRL_EnableLCDC(LCDC_CLOCK_DIVIDER);

    if (ER_OK == ret_val)
    {
        lcdc_enabled = true;
        lcdc_base_address = (void *)0;
        palette_size = 0;
        update_complete = (void *)0;        /* init callback function for when LCD update has completed (may not be required) */

        /* Set interrupt priority for LCDC and enable system interrupt */
        irq_num = RZN1_IRQ_LCD;

        if (R_BSP_InterruptRegisterCallback((IRQn_Type) irq_num,
                (bsp_int_cb_t) &handle_lcdc_interrupt) == MCU_INT_SUCCESS)
        {
            int_priority = LCD_DEFAULT_INT_PRIORITY;
            ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
            if (MCU_INT_SUCCESS != ret_val)
            {
                ret_val = ER_SYS;
            }
            else
            {
                /* mask/disable all LCDC interrupts */
                lcdc_base_address->rLcd_IMR.LONG = 0;

                /* Enable LCDC system interrupt */
                ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);
            }
        }
        else
        {
            ret_val = ER_SYS;
        }

    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function lcdc_driver_init
 **********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name :   lcdc_driver_uninit
 **********************************************************************************************************************/
/*!
* @brief    Stops LCDC
* @details
* @param    void
* @retval   Error Status
 **********************************************************************************************************************/
ER_RET lcdc_driver_uninit(void)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num;

    /* Disable LCDC system interrupt */
    irq_num = (uint8_t) RZN1_IRQ_LCD;
    ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);

    if (ret_val == ER_OK)
    {
        ret_val = R_SYSCTRL_DisableLCDC();
    }

    if (ER_OK == ret_val)
    {
        lcdc_enabled = false;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function lcdc_driver_uninit
 **********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name :   lcdc_port_open
 **********************************************************************************************************************/
/*!
* @brief    Opens LCDC port
* @details
* @param    port_config - pointer to LCD port configuration
* @retval   Error status
 **********************************************************************************************************************/
ER_RET lcdc_port_open(lcdc_port_config_t *port_config)
{
    ER_RET              ret_val = ER_OK;
    uint32_t            cr1_bpp_mask;
    uint32_t            i;
    uint32_t            palette_val;
    volatile uint32_t  *palette_reg_ptr;
    volatile uint32_t   *mmr_reg_ptr;
    volatile uint32_t   lcdc_reg;
    uint32_t            size_of_fb;

    if (!lcdc_enabled)
    {
        ret_val = (ER_SYS);
    }
    else
    {
        lcdc_base_address = (volatile LCDC_Type *)RZN1_LCD_BASE;

        /* save configuration */
        lcd_config.bpp = port_config->bpp;
        lcd_config.pixel_format = port_config->pixel_format;
        lcd_config.x_res = port_config->x_res;
        lcd_config.y_res = port_config->y_res;
        lcd_config.palette = port_config->palette;

        /* configure LCD controller */

        /* Load Control Reg1 fields */
        cr1_bpp_mask = bpp_to_cr1mask(lcd_config.bpp);
        if (lcd_config.bpp >= LCDC_DRIVER_BPP_16)
        {
            palette_size = 0;
        }
        else
        {
            if (lcd_config.palette == (void *)0)
            {
                ret_val = (ER_PARAM);
            }
            else
            {
                palette_size = (1 << lcd_config.bpp);
            }
        }
        /* rLcd_CR1 (use little endian Byte ordering in palette and Pixel ordering within Byte */
        lcdc_base_address->rLcd_CR1.BIT.bLcd_LPE = 0;
        lcdc_base_address->rLcd_CR1.BIT.bLcd_LPE = 1;   /* LCD Power enable */
        lcdc_reg = lcdc_base_address->rLcd_CR1.LONG;
        lcdc_reg |= LCDC_CR1_FDW_16BB;               /* FIFO DMA request for 16-beat burst when FIFO has room for 16 words */
        lcdc_reg |= cr1_bpp_mask;                   /* bits per pixel */
        lcdc_reg |= LCDC_CR1_DE_1;                  /* Data Enable polarity */
        lcdc_reg |= LCDC_CR1_HSP_LOW;
        lcdc_reg |= LCDC_CR1_VSP_LOW;

        lcdc_reg &= ~LCDC_CR1_OPS_MASK;
        lcdc_reg &= ~LCDC_CR1_RGB_MSK;

        if ( lcd_config.bpp <= LCDC_DRIVER_BPP_16)
        {
            /* set bLcd_OPS */
            if ((lcd_config.pixel_format == LCD_RGB555) || (lcd_config.pixel_format == LCD_BGR555))
            {
                lcdc_reg |= LCDC_CR1_OPS_555;
            }
            /* set bLcd_RGB */
            if ((lcd_config.pixel_format == LCD_BGR565) || (lcd_config.pixel_format == LCD_BGR555))
            {
                lcdc_reg |= LCDC_CR1_RGB_MSK;
            }

            if (palette_size > 0)
            {
                /* set bLcd_RGB */
            }
        }
        lcdc_base_address->rLcd_CR1.LONG = lcdc_reg;

        /* rLcd_HTR */
        lcdc_reg =  0x28;
        lcdc_reg  |= (lcd_config.x_res / 16) << 8;      /* bLcd_PPL */
        lcdc_reg |=  (0x01 << 24);                      /* bLcd_HSW */
        lcdc_reg |=  (0x58 << 16);                      /* bLcd_HBP */
        /* bLcd_HFP */
        lcdc_base_address->rLcd_HTR.LONG = lcdc_reg;

        /* rLcd_VTR1 */
        lcdc_reg  =  0x03;                              /* bLcd_VSW */
        lcdc_reg |=  (0x20 << 16);                      /* bLcd_VBP */
        lcdc_reg |=  (0x0d << 8);                       /* bLcd_VFP */
        lcdc_base_address->rLcd_VTR1.LONG = lcdc_reg;

        /* rLcd_VTR2 */
        lcdc_reg  =  lcd_config.y_res & 0xFFF;                  /* bLcd_LPP lines per panel */
        lcdc_base_address->rLcd_VTR2.BIT.bLcd_LPP = lcdc_reg;

        /* rLcd_HVTER */
        lcdc_base_address->rLcd_HVTER.LONG = 0;

        /* rLcd_PCTR */
        lcdc_base_address->rLcd_PCTR.BIT.bLcd_PCR = 1;      /* Pixel clock RESET released */

        /* rLcd_HPPLOR */
        lcdc_reg  =  0;
        lcdc_base_address->rLcd_HPPLOR.LONG = lcdc_reg;

        /* Init Blink settings */
        /* rLcd_PWMDCR_0 */
        lcdc_reg  =  0x80;
        lcdc_base_address->rLcd_PWMDCR_0.BIT.bLcd_PWMDC_0 = lcdc_reg;

        /* rLcd_PWMFR_0 */
        lcdc_reg  =  0x0040fe4f;                            /* pwm_fcd = (LCDC_CLK_FREQ/256 * fast_blink_ms/1000) -1 */ 
        lcdc_base_address->rLcd_PWMFR_0.LONG = lcdc_reg;


        /* Turn on the backlight */
        /* rLcd_PWMDCR_1 */
        lcdc_reg  =  0x80;
        lcdc_base_address->rLcd_PWMDCR_1.BIT.bLcd_PWMDC_1 = lcdc_reg;

        /* rLcd_PWMFR_1 */
        lcdc_reg  =  0x004001b1;
        lcdc_base_address->rLcd_PWMFR_1.LONG = lcdc_reg;        /* turn on */

        /* set framebuffer */
        saved_blink_mode = LCDC_BLINK_MODE_OFF;
        display_fb = 0;
        back_fb = 1;
        memset ((void *)fb[display_fb], 0, (MAX_MEM_BYTES_PER_PIXEL * MAX_SCREEN_WIDTH * MAX_SCREEN_HEIGHT));
        lcdc_reg = (uint32_t)fb[display_fb];
        lcdc_base_address->rLcd_DBAR.LONG  = lcdc_reg;

        size_of_fb = (actual_bytes_per_pixel * lcd_config.x_res * lcd_config.y_res);
        lcdc_reg = (uint32_t) (fb[display_fb]) + size_of_fb + 8;
        lcdc_base_address->rLcd_DEAR.LONG  = lcdc_reg;

        /* configure MRR to 4 outstanding requests */
        mmr_reg_ptr = (volatile uint32_t *)(lcdc_base_address + MMR_OFFSET);
        lcdc_reg = (((uint32_t) (fb[display_fb] + size_of_fb + 8) & 0xFFFFFFFC) | 0x2);
        *mmr_reg_ptr = lcdc_reg;

        /* Write into palette registers, if required */
        if (palette_size > 0)
        {
            palette_reg_ptr = (volatile uint32_t *)(lcdc_base_address + RZN1_LCD_PALETTE_REGS_OFFSET);
            for (i=0; i < (palette_size); i += 2)
            {
                palette_val = (lcd_config.palette[i] << 16) | (lcd_config.palette[i+1] & 0x00FF);
                *palette_reg_ptr = palette_val;     /* write palette_val to palette reg */
                palette_reg_ptr++;
            }
        }

        /* LCD Controller enable */
        lcdc_base_address->rLcd_CR1.BIT.bLcd_LCE = 1;

        /* Enable BAU interrupt */
        lcdc_base_address->rLcd_IMR.BIT.bLcd_BAUM = 1;

        /*ret_val = lcdc_base_address->rLcd_CIR.LONG;*/

    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function lcdc_port_open
 **********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name :   lcdc_port_close
 **********************************************************************************************************************/
/*!
* @brief    Closes LCDC port
* @details
* @param    void
* @retval   Error status
 **********************************************************************************************************************/
ER_RET lcdc_port_close(void)
{
    ER_RET ret_val = ER_OK;

    if (lcdc_base_address == (void *)0)
    {
        /* LCD port not open */
        ret_val = ER_INVAL;
    }
    else
    {
        /* mask/disable all LCDC interrupts */
        lcdc_base_address->rLcd_IMR.LONG = 0;

        /* turn off backlight */
        lcdc_base_address->rLcd_PWMFR_1.BIT.bLcd_PWMFCE_1 = 0;

        /* rLcd_PWMDCR_1 */
        lcdc_base_address->rLcd_PWMDCR_1.LONG = 0;



        /* LCD power disable */
        lcdc_base_address->rLcd_CR1.BIT.bLcd_LPE = 0;

        /* Disable the LCDC Controller  */
        lcdc_base_address->rLcd_CR1.BIT.bLcd_LCE = 0;
        lcdc_base_address = (void *)0;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function lcdc_port_close
 **********************************************************************************************************************/





/***********************************************************************************************************************
* Function Name :   tsd_driver_init
 **********************************************************************************************************************/
/*!
* @brief    Initialise touch screen driver
* @details
* @param    gpio_callback - callback function for ts interrupts (re-directed to GPIO)
* @retval   Error status
 **********************************************************************************************************************/
ER_RET tsd_driver_init(gpio_callback ts_int_callback)
{
    ER_RET ret_val = ER_OK;

    if (ts_int_callback == NULL)
    {
        ret_val = ER_PARAM;
    }
    else
    {
        ret_val = R_GPIO_PinOpen(GPIO_PORT_3A_PIN_26);
        if (ret_val == ER_OK)
        {
            ret_val = R_GPIO_PinDirectionSet(GPIO_PORT_3A_PIN_26, GPIO_DIRECTION_INPUT);
            if (ret_val == ER_OK)
            {
                ret_val = R_GPIO_RegInterruptCallBack(ts_int_callback);
            }
        }
    }
    if (ret_val == ER_OK)
    {
        ret_val = r_gpio_interrupttriggertype(GPIO_PORT_3A_PIN_26, GPIO_INTTERRUPT_TRIGGER_EDGE);
        if (ret_val == ER_OK)
        {
            ret_val = r_gpio_interrupttriggerpolarity(GPIO_PORT_3A_PIN_26, GPIO_INTTERRUPT_POLARITY_LOW);
            if (ret_val == ER_OK)
            {
                ret_val = r_gpio_interruptmask(GPIO_PORT_3A_PIN_26, GPIO_INTTERRUPT_MASK_DISABLED);
                if (ret_val == ER_OK)
                {
                    ret_val = r_gpio_iterruptenable(GPIO_PORT_3A_PIN_26, GPIO_INTTERRUPT_ENABLED);          /* Enable touch screen interrupts */
                }
            }
        }
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function tsd_driver_init
 **********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name :   tsd_driver_uninit
 **********************************************************************************************************************/
/*!
* @brief    Close down touch screen driver
* @details
* @param    void
* @retval   Error status
 **********************************************************************************************************************/
ER_RET tsd_driver_uninit(void)
{
    ER_RET ret_val = ER_OK;

    /* Disable touchscreen interrupts */
    r_gpio_interruptmask(GPIO_PORT_3A_PIN_26, GPIO_INTTERRUPT_MASK_ENABLED);
    r_gpio_iterruptenable(GPIO_PORT_3A_PIN_26, GPIO_INTTERRUPT_DISABLED);
    R_GPIO_PinClose(GPIO_PORT_3A_PIN_26);

    return ret_val;
}
/***********************************************************************************************************************
 End of function tsd_driver_uninit
 **********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name :   lcdc_set_port_config
 **********************************************************************************************************************/
/*!
* @brief    reconfigure the LCD port
* @details
* @param    port_config - new configuration
* @retval   Error status
 **********************************************************************************************************************/
ER_RET lcdc_set_port_config(lcdc_port_config_t *port_config)
{
    ER_RET ret_val = ER_OK;

    if (port_config != (void *)0)
    {
        if (lcdc_base_address != (void *)0)
        {
            /* LCDC channel is initialised */

            /* disable ts controller  */
            (void)tsd_driver_uninit();

            /* Reset */
            ret_val = lcdc_port_close();
            if (ret_val == ER_OK)
            {
                /* re-open  ???????   */
                ret_val = lcdc_port_open(port_config);
            }
        }
        else
        {
            ret_val = ER_INVAL; /* LCDC not initialised */
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function lcdc_set_port_config
 **********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name :   lcdc_get_port_config
 **********************************************************************************************************************/
/*!
* @brief    Get the LCD port configuration
* @details
* @param    port_config -  pointer to where to store the configuration
* @retval   Error status
 **********************************************************************************************************************/
ER_RET  lcdc_get_port_config(lcdc_port_config_t *port_config)
{
    ER_RET ret_val = ER_OK;

    if (port_config != (void*)0)
    {
        if (lcdc_base_address != (void *)0)
        {
            /* LCDC channel is initialised */

            /* Get LCDC configuration  */
            port_config->bpp = lcd_config.bpp;
            port_config->pixel_format = lcd_config.pixel_format;
            port_config->x_res = lcd_config.x_res;
            port_config->y_res = lcd_config.y_res;
            port_config->palette = lcd_config.palette;
        }
        else
        {
            ret_val = ER_INVAL; /* LCDC channel not initialised */
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function lcdc_get_port_config
 **********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name :   lcdc_reset
 **********************************************************************************************************************/
/*!
* @brief    Resets the LCD controller
* @details
* @param    void
* @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET lcdc_reset(void)
{
    ER_RET ret_val = ER_OK;

    if (lcdc_base_address != (void *)0)
    {
        /* LCDC channel is initialised */

        /* disable ts controller  */
        (void)tsd_driver_uninit();

        ret_val = lcdc_port_close();
        if (ret_val == ER_OK)
        {
            /* re-open ????? */
            ret_val = lcdc_port_open(&lcd_config);
        }
    }
    else
    {
        ret_val = ER_INVAL; /* LCDC channel not initialised */
    }
    return ret_val;
}
/***********************************************************************************************************************
 End of function lcdc_reset
 **********************************************************************************************************************/



/***********************************************************************************************************************
* Function Name :   lcdc_blank_display
 **********************************************************************************************************************/
/*!
* @brief    Blank the entire display
* @details
* @param    colour - set blank display to this colour
*              should be in correct format depending on configured bpp and colour mode e.g.
*           for bpp < 16  , colour is palette index of blanking colour
*           for bpp = 16, RGB 5:6:5 , colour is 0b0000 0000 0000 0000 RRRR RGGG GGGB BBBB
*           for bpp = 16, BGR 5:6:5 , colour is 0b0000 0000 0000 0000 BBBB BGGG GGGR RRRR
*           for bpp = 16, RGB 5:5:5 , colour is 0b0000 0000 0000 0000 0RRR RRGG GGGB BBBB
*           for bpp = 16, BGR 5:5:5 , colour is 0b0000 0000 0000 0000 0BBB BBGG GGGR RRRR
*
*           for bpp = 24, RGB 8:8:8 , colour is 0b0000 0000 RRRR RRRR GGGG GGGG BBBB BBBB
*           for bpp = 24, BGR 8:8:8 , colour is 0b0000 0000 BBBB BBBB GGGG GGGG RRRR RRRR
* @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET  lcdc_blank_display(uint32_t colour)   /*  CALL ER_RET  lcdc_fill_rectangle (lcd_rectangle_t *display_update_area, uint32_t colour) for whole display !! */
{
    ER_RET              ret_val = ER_OK;
    uint32_t            *fb_ptr32;
    uint16_t            *fb_ptr16;
    uint32_t            i;
    uint8_t             pixel_data;
    uint32_t            size_of_fb = (actual_bytes_per_pixel * lcd_config.x_res * lcd_config.y_res);
    uint32_t            size;
    volatile uint32_t   lcdc_reg;


    if (lcdc_base_address != (void *)0)
    {
        /* LCDC channel is initialised */
        i = 50;
        while ((display_fb == back_fb) && (i > 0))
        {
            /* wait for current display update completion with timeout */
            systimer_delay(20000);    /* delay 20 msecs */
            i--;
        }
        if (i == 0)
        {
            /* timed out */
            ret_val = ER_SYS;
        }
        else
        {
            if (palette_size == 0)
            {
                /* load fb with given colour */

                if ((lcd_config.bpp == LCDC_DRIVER_BPP_18) || (lcd_config.bpp == LCDC_DRIVER_BPP_24))
                {
                    /* load 32 bits per pixel to fb */
                    fb_ptr32 = (uint32_t *)fb[back_fb];
                    size = size_of_fb/4;              /* word size */
                    for (i=0; i < size; i++)
                    {
                        *fb_ptr32 = colour;
                        fb_ptr32++;
                    }
                }
                else
                {
                    /* load 16 bits to fb per pixel */
                    fb_ptr16 = (uint16_t *)fb[back_fb];
                    size = (lcd_config.x_res * lcd_config.y_res); /* 2 bytes per pixel and loading 1 pixel at a time*/
                    for (i=0; i < size; i++)
                    {
                        *fb_ptr16 = colour;
                        fb_ptr16++;
                    }
                }
            }
            else
            {
                /* colour is actually an index into the palette */
                switch (lcd_config.bpp)
                {
                case LCDC_DRIVER_BPP_1:
                    size = (lcd_config.x_res * lcd_config.y_res) / 8;       /* 1 bit per pixel and loading 1 byte at a time */
                    if (colour == 1)
                    {
                        pixel_data = 0xff;
                    }
                    else
                    {
                        pixel_data = 0;
                    }
                    memset(fb[back_fb], pixel_data, size);
                    break;

                case LCDC_DRIVER_BPP_2:
                    size = (lcd_config.x_res * lcd_config.y_res) / 4;       /* 1/4 byte per pixel and loading 1 byte at a time */
                    pixel_data = (uint8_t) colour;                          /* index to palette is 2 lsb bits */
                    pixel_data = pixel_data << 6;
                    pixel_data |= (uint8_t)((colour & 0x0003) << 4);
                    pixel_data |= (uint8_t)((colour & 0x0003) << 2);
                    pixel_data |= (uint8_t)(colour & 0x0003);
                    memset(fb[back_fb], pixel_data, size);
                    break;

                case LCDC_DRIVER_BPP_4:
                    size = (lcd_config.x_res * lcd_config.y_res) / 2;       /* 1/2 byte per pixel and loading 1 byte at a time */
                    pixel_data = (uint8_t) colour;                          /* index to palette is 4 lsb bits */
                    pixel_data = pixel_data << 4;
                    pixel_data |= (uint8_t)(colour & 0x000F);
                    memset(fb[back_fb], pixel_data, size);
                    break;

                case LCDC_DRIVER_BPP_8:
                    size = (lcd_config.x_res * lcd_config.y_res);       /* 1 byte per pixel and loading 1 byte at a time */
                    memset(fb[back_fb], colour, size);
                    break;

                default:
                    ret_val = ER_SYS;
                    break;
                }
            }
            /* flag to switch fb */
            display_fb = back_fb;
        }
    }
    else
    {
        ret_val = ER_INVAL; /* LCDC channel not initialised */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function lcdc_blank_display
 **********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name :   lcdc_fill_rectangle
 **********************************************************************************************************************/
/*!
* @brief    Fill a rectangular section of the display with the given colour
* @details
* @param    display_update_area - pinter to rectangle of display to update
* @param    colour - fill colour
*              should be in correct format depending on configured bpp and colour mode e.g.
*           for bpp < 16  , colour is palette index of blanking colour
*           for bpp = 16, RGB 5:6:5 , colour is 0b0000 0000 0000 0000 RRRR RGGG GGGB BBBB
*           for bpp = 16, BGR 5:6:5 , colour is 0b0000 0000 0000 0000 BBBB BGGG GGGR RRRR
*           for bpp = 16, RGB 5:5:5 , colour is 0b0000 0000 0000 0000 0RRR RRGG GGGB BBBB
*           for bpp = 16, BGR 5:5:5 , colour is 0b0000 0000 0000 0000 0BBB BBGG GGGR RRRR
*
*           for bpp = 24, RGB 8:8:8 , colour is 0b0000 0000 RRRR RRRR GGGG GGGG BBBB BBBB
*           for bpp = 24, BGR 8:8:8 , colour is 0b0000 0000 BBBB BBBB GGGG GGGG RRRR RRRR
* @param    NOTE: for BPP <= 8, rectangle co-ordinates must be on an 8-pixel boundary
* @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET  lcdc_fill_rectangle (lcd_rectangle_t *display_update_area, uint32_t colour)
{
    ER_RET ret_val = ER_OK;
    uint32_t    i;
    uint32_t    *fb_ptr32;
    uint32_t    *fb_ptr32_end;
    uint16_t    *fb_ptr16;
    uint16_t    *fb_ptr16_end;
    uint8_t     *fb_ptr8;
    uint8_t     *fb_ptr8_end;
    uint32_t    size;
    uint8_t     pixel_data;

    uint32_t    start_index;         /* start byte-index into fb of entries to update */
    uint32_t    end_index;
    uint32_t    start_x;
    uint32_t    start_y;
    uint32_t    end_x;
    uint32_t    end_y;
    uint32_t    gap;                 /* number of byte entries to skip in-between updates */

    if (lcdc_base_address != (void *)0)
    {
        /* LCDC channel is initialised */

        start_index = (display_update_area->lcd_rectangle_top * lcd_config.x_res) + display_update_area->lcd_rectangle_left;    /* start byte-index into fb of entries to update */
        end_index = (display_update_area->lcd_rectangle_bottom * lcd_config.x_res) + display_update_area->lcd_rectangle_right;
        start_x = display_update_area->lcd_rectangle_left;
        start_y = display_update_area->lcd_rectangle_top;
        end_x = display_update_area->lcd_rectangle_right;
        end_y = display_update_area->lcd_rectangle_bottom;
        gap = start_x + ((lcd_config.x_res - 1) - end_x);

        /* check parameters */
        if (    ( start_y < end_y) &&
                ( end_y <  lcd_config.y_res ) &&
                ( start_x < end_x) &&
                ( end_x <  lcd_config.x_res ) )
        {
            i = 50;
            while ((display_fb == back_fb) && (i > 0))
            {
                /* wait for previous update completion with timeout */
                systimer_delay(20000);    /* delay 20 msecs */
                i--;
            }
            if (i == 0)
            {
                /* timed out */
                ret_val = ER_SYS;
            }
            else
            {
                if (palette_size == 0)
                {
                    /* load fb with given colour */

                    if ((lcd_config.bpp == LCDC_DRIVER_BPP_18) || (lcd_config.bpp == LCDC_DRIVER_BPP_24))
                    {
                        /* load 32 bits per pixel to fb */
                        fb_ptr32 = (uint32_t *)((uint32_t)fb[back_fb] + (start_index * 4));

                        fb_ptr32_end = (uint32_t *)(((uint32_t)fb[back_fb]) + ((end_index + 1)*4));
                        size = (end_x - start_x  + 1);   /* word size */
                        while (fb_ptr32 < fb_ptr32_end)
                        {
                            /* fill a line */
                            for (i=0; i < size; i++)
                            {
                                *fb_ptr32 = colour;
                                fb_ptr32++;
                            }
                            /* skip the gap */
                            fb_ptr32 += gap;
                        }
                    }
                    else
                    {
                        /* load 16 bits to fb per pixel */
                        fb_ptr16 = (uint16_t *)((uint32_t)fb[back_fb] + start_index);

                        fb_ptr16_end = (uint16_t *)(((uint32_t)fb[back_fb]) + (end_index + 1));
                        size = (end_x - start_x  + 1)/2;   /* word size */

                        while (fb_ptr16 < fb_ptr16_end)
                        {
                            /* fill a line */
                            for (i=0; i < size; i++)
                            {
                                *fb_ptr16 = colour;
                                fb_ptr16++;
                            }
                            /* skip the gap */
                            fb_ptr16 += gap/2;
                        }
                    }
                }
                else
                {
                    /* colour is actually an index into the palette */
                    fb_ptr8 = (uint8_t *)fb[back_fb];
                    switch (lcd_config.bpp)
                    {
                    case LCDC_DRIVER_BPP_1:
                        /* 1 bit per pixel and loading 1 byte at a time */
                        if (colour == 1)
                        {
                            pixel_data = 0xff;
                        }
                        else
                        {
                            pixel_data = 0;
                        }

                        fb_ptr8 += start_index;
                        fb_ptr8_end = (uint8_t *)(fb[back_fb]) + (end_index + 1);

                        size = (end_x - start_x  + 1) / 8;
                        while (fb_ptr8 < fb_ptr8_end)
                        {
                            /* fill a line */
                            for (i=0; i < size; i++)
                            {
                                *fb_ptr8 = colour;
                                fb_ptr8++;
                            }
                            /* skip the gap */
                            fb_ptr8 += gap;
                        }
                        break;

                    case LCDC_DRIVER_BPP_2:
                        /* 1/4 byte per pixel and loading 1 byte at a time */
                        pixel_data = (uint8_t) colour;                          /* index to palette is 2 lsb bits */
                        pixel_data = pixel_data << 6;
                        pixel_data |= (uint8_t)((colour & 0x0003) << 4);
                        pixel_data |= (uint8_t)((colour & 0x0003) << 2);
                        pixel_data |= (uint8_t)(colour & 0x0003);

                        fb_ptr8 += start_index;
                        fb_ptr8_end = (uint8_t *)(fb[back_fb]) + (end_index + 1);

                        size = (end_x - start_x  + 1) / 4;
                        while (fb_ptr8 < fb_ptr8_end)
                        {
                            /* fill a line */
                            for (i=0; i < size; i++)
                            {
                                *fb_ptr8 = pixel_data;
                                fb_ptr8++;
                            }
                            /* skip the gap */
                            fb_ptr8 += gap;
                        }
                        break;

                    case LCDC_DRIVER_BPP_4:
                        /* 1/2 byte per pixel and loading 1 byte at a time */
                        pixel_data = (uint8_t) colour;                          /* index to palette is 4 lsb bits */
                        pixel_data = pixel_data << 4;
                        pixel_data |= (uint8_t)(colour & 0x000F);

                        fb_ptr8 += start_index;
                        fb_ptr8_end = (uint8_t *)(fb[back_fb]) + (end_index + 1);

                        size = (end_x - start_x  + 1) / 2;

                        while (fb_ptr8 < fb_ptr8_end)
                        {
                            /* fill a line */
                            for (i=0; i < size; i++)
                            {
                                *fb_ptr8 = pixel_data;
                                fb_ptr8++;
                            }
                            /* skip the gap */
                            fb_ptr8 += gap;
                        }
                        break;

                    case LCDC_DRIVER_BPP_8:
                        /* 1 byte per pixel and loading 1 byte at a time */

                        fb_ptr8 += start_index;
                        fb_ptr8_end = (uint8_t *)(fb[back_fb]) + (end_index + 1);

                        size = (end_x - start_x  + 1);

                        while (fb_ptr8 < fb_ptr8_end)
                        {
                            /* fill a line */
                            for (i=0; i < size; i++)
                            {
                                *fb_ptr8 = pixel_data;
                                fb_ptr8++;
                            }
                            /* skip the gap */
                            fb_ptr8 += gap;
                        }
                        break;

                    default:
                        ret_val = ER_SYS;
                        break;
                    }
                }
                /* flag to switch fb */
                display_fb = back_fb;
            }
        }
        else
        {
            ret_val = ER_PARAM;
        }
    }
    else
    {
        ret_val = ER_INVAL; /* LCDC channel not initialised */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function lcdc_fill_rectangle
 **********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name :   lcdc_blink_display
 **********************************************************************************************************************/
/*!
* @brief    Blink or unblinks a rectangular section of the display
* @details  The rectangular section may be the whole display
* @param    display_update_area - pointer to the rectangle to be updated
* @param    blink_mode - LCDC_BLINK_MODE_OFF or LCDC_BLINK_MODE_SLOW, LCDC_BLINK_MODE_MEDIUM, LCDC_BLINK_MODE_FAST
* @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET  lcdc_blink_display(lcd_rectangle_t *display_update_area, lcdc_blink_mode_e blink_mode)
{
    ER_RET ret_val = ER_OK;
    uint32_t    i;
    uint32_t    *fb_ptr32;
    uint32_t    *fb_ptr32_end;
    uint32_t    size;
    uint32_t    pixel_data;
    uint32_t    pixel_colour;
    uint32_t    adjusted_pixel_data;
    uint32_t    size_of_fb = (actual_bytes_per_pixel * lcd_config.x_res * lcd_config.y_res);    

    uint32_t    start_index;         /* start byte-index into fb of entries to update */
    uint32_t    end_index;
    uint32_t    start_x;
    uint32_t    start_y;
    uint32_t    end_x;
    uint32_t    end_y;
    uint32_t    gap;                 /* number of byte entries to skip in-between updates */

    if ((lcdc_base_address != (void *)0) && (saved_blink_mode != blink_mode))
    {
        /* LCDC channel is initialised and request to change Blink mode */
        
        if ((palette_size == 0) && (lcd_config.bpp == LCDC_DRIVER_BPP_24))
        {
            /* Blink mode only supported if 24 BPP selected */
            start_index = (display_update_area->lcd_rectangle_top * lcd_config.x_res) + display_update_area->lcd_rectangle_left;    /* start byte-index into fb of entries to update */
            end_index = (display_update_area->lcd_rectangle_bottom * lcd_config.x_res) + display_update_area->lcd_rectangle_right;
            start_x = display_update_area->lcd_rectangle_left;
            start_y = display_update_area->lcd_rectangle_top;
            end_x = display_update_area->lcd_rectangle_right;
            end_y = display_update_area->lcd_rectangle_bottom;
            gap = start_x + ((lcd_config.x_res - 1) - end_x);

            /* check parameters */
            if (    ( start_y < end_y) &&
                    ( end_y <  lcd_config.y_res ) &&
                    ( start_x < end_x) &&
                    ( end_x <  lcd_config.x_res ) )
            {
                i = 50;
                while ((display_fb == back_fb) && (i > 0))
                {
                    /* wait for previous update completion with timeout */
                    systimer_delay(20000);    /* delay 20 msecs */
                    i--;
                }
                if (i == 0)
                {
                    /* timed out */
                    ret_val = ER_SYS;
                }
                else
                {
                    /*  bpp is 24. load 32 bits per pixel to fb */
                    fb_ptr32 = (uint32_t *)(uint32_t)fb[back_fb];                    
                    if (blink_mode == LCDC_BLINK_MODE_OFF)
                    {
                        /* set the whole fb back to normal */
                        fb_ptr32_end = (uint32_t *)((uint32_t)fb[back_fb] + size_of_fb);
                        
                        while (fb_ptr32 < fb_ptr32_end)
                        {
                            /* read pixel */
                            pixel_data = *fb_ptr32;
                            
                            /* adjust data */
                            adjusted_pixel_data = 0;                /* no blink */               
                            pixel_colour = (pixel_data << 2) & 0x00FF0000;  /* Red adjusted */
                            /* copy R1 to R0 */
                            if (pixel_colour & 0x00020000)
                            {
                                pixel_colour |= 0x00010000;
                            }
                            else
                            {
                                pixel_colour &= ~0x00010000;
                            }
                            adjusted_pixel_data |= pixel_colour;
                            
                            pixel_colour = (pixel_data << 1) & 0x0000FF00;  /* Green adjusted */
                            adjusted_pixel_data |= pixel_colour;
                            
                            pixel_colour = (pixel_data << 1) & 0x000000FF;  /* Blue adjusted */
                            /* copy B1 to B0 */
                            if (pixel_colour & 0x00000002)
                            {
                                pixel_colour |= 0x00000001;
                            }
                            else
                            {
                                pixel_colour &= ~0x00000001;
                            }                                
                            adjusted_pixel_data |= pixel_colour;

                            *fb_ptr32 = adjusted_pixel_data;
                            fb_ptr32++;
                        }

                    }
                    else
                    {
                        /* Blink Mode ON */
                        
                        fb_ptr32_end = (uint32_t *)((uint32_t)fb[back_fb] + (start_index * 4));
                        while (fb_ptr32 < fb_ptr32_end)
                        {
                            /* Adjust the start of the fb (area not being blinked, but still pixel needs to be re-formatted in Blink mode) */
                           
                            /* adjust data */

                            adjusted_pixel_data = LCDC_BLINK_MODE_OFF;      /* No blink */
                            
                            /* read pixel */
                            pixel_data = *fb_ptr32;                             
                            if (saved_blink_mode == LCDC_BLINK_MODE_OFF)
                            {
                                /* need to adjust colours as going from OFF -> BLINK */
                                pixel_colour = (pixel_data >> 2) & 0x003F8000;  /* Red adjusted */
                                adjusted_pixel_data |= pixel_colour;
                                pixel_colour = (pixel_data >> 1) & 0x00007F80;  /* Green adjusted */
                                adjusted_pixel_data |= pixel_colour;
                                pixel_colour = (pixel_data >> 1) & 0x0000007F;  /* Blue adjusted */
                                adjusted_pixel_data |= pixel_colour;
                            }
                            else
                            {
                                pixel_colour = pixel_data & 0xFF3FFFFF;;
                                adjusted_pixel_data |= pixel_colour;
                            }
                            
                            *fb_ptr32 = adjusted_pixel_data;

                            fb_ptr32++;
                        }

                        /* Now adjust blinked section */
                        fb_ptr32 = (uint32_t *)((uint32_t)fb[back_fb] + (start_index * 4));

                        fb_ptr32_end = (uint32_t *)(((uint32_t)fb[back_fb]) + ((end_index + 1)*4));
                        size = (end_x - start_x  + 1);   /* word size */
                        while (fb_ptr32 < fb_ptr32_end)
                        {
                            /* fill a line */
                            for (i=0; i < size; i++)
                            {
                                /* adjust data */
                                adjusted_pixel_data = blink_mode << 22;
                                
                                /* read pixel */
                                pixel_data = *fb_ptr32;                                
                                if (saved_blink_mode == LCDC_BLINK_MODE_OFF)
                                {
                                    /* need to adjust colours as going from OFF -> BLINK */

                                    pixel_colour = (pixel_data >> 2) & 0x003F8000;  /* Red adjusted */
                                    adjusted_pixel_data |= pixel_colour;
                                    pixel_colour = (pixel_data >> 1) & 0x00007F80;  /* Green adjusted */
                                    adjusted_pixel_data |= pixel_colour;
                                    pixel_colour = (pixel_data >> 1) & 0x0000007F;  /* Blue adjusted */
                                    adjusted_pixel_data |= pixel_colour;
                                }
                                else
                                {
                                    pixel_colour = pixel_data & 0xFF3FFFFF;
                                    adjusted_pixel_data |= pixel_colour;
                                }
                                
                                *fb_ptr32 = adjusted_pixel_data;
                                fb_ptr32++;
                            }
                            /* fill the gap - non-blinking */
                            for (i=0; i < gap; i++)
                            {
                                if (fb_ptr32 >= (uint32_t *)((uint32_t)fb[back_fb] + size_of_fb))
                                {
                                    /* don't over-run the buffer */
                                    break;
                                }
                                /* adjust data */
                                
                                /* read pixel */
                                pixel_data = *fb_ptr32;
                                adjusted_pixel_data = LCDC_BLINK_MODE_OFF;           /* No blink */
                                if (saved_blink_mode == LCDC_BLINK_MODE_OFF)
                                {
                                    /* need to adjust colours as going from OFF -> BLINK */
                                    pixel_colour = (pixel_data >> 2) & 0x003F8000;  /* Red adjusted */
                                    adjusted_pixel_data |= pixel_colour;
                                    pixel_colour = (pixel_data >> 1) & 0x00007F80;  /* Green adjusted */
                                    adjusted_pixel_data |= pixel_colour;
                                    pixel_colour = (pixel_data >> 1) & 0x0000007F;  /* Blue adjusted */
                                    adjusted_pixel_data |= pixel_colour;
                                }
                                else
                                {
                                    pixel_colour = pixel_data & 0xFF3FFFFF;
                                    adjusted_pixel_data |= pixel_colour;
                                }                                

                                *fb_ptr32 = adjusted_pixel_data;
                                fb_ptr32++;
                            }
                        }
                        
                        fb_ptr32_end = (uint32_t *)((uint32_t)fb[back_fb] + size_of_fb);
                        while (fb_ptr32 < fb_ptr32_end)
                        {
                            /* Adjust the end of the fb */

                            /* read pixel */
                            pixel_data = *fb_ptr32;
                            adjusted_pixel_data = LCDC_BLINK_MODE_OFF;           /* No blink */
                            if (saved_blink_mode == LCDC_BLINK_MODE_OFF)
                            {              
                                pixel_colour = (pixel_data >> 2) & 0x003F8000;  /* Red adjusted */
                                adjusted_pixel_data |= pixel_colour;
                                pixel_colour = (pixel_data >> 1) & 0x00007F80;  /* Green adjusted */
                                adjusted_pixel_data |= pixel_colour;
                                pixel_colour = (pixel_data >> 1) & 0x0000007F;  /* Blue adjusted */
                                adjusted_pixel_data |= pixel_colour;
                            }
                            else
                            {
                                pixel_colour = pixel_data & 0xFF3FFFFF;
                                adjusted_pixel_data |= pixel_colour;
                            }                            
                            *fb_ptr32 = adjusted_pixel_data;
                            fb_ptr32++;
                        }
                    }
                    saved_blink_mode = blink_mode;
                    
                    /* flag to switch fb */
                    display_fb = back_fb;
                    if (blink_mode == LCDC_BLINK_MODE_OFF)
                    {
                        lcdc_base_address->rLcd_GPIOR.BIT.bLcd_BlinkOn = 0;
                    }
                    else
                    {
                        lcdc_base_address->rLcd_GPIOR.BIT.bLcd_BlinkOn = 1;
                    }
                }
            }
            else
            {
                ret_val = ER_PARAM;
            }
        }
        else
        {
            /* Blink valid only for 24 bpp */
            ret_val = ER_INVAL;            
        }
    }
    else
    {
        ret_val = ER_INVAL; /* LCDC channel not initialised or Blink mode not changing */
    }

    return ret_val;

}
/***********************************************************************************************************************
 End of function lcdc_blink_display
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *
 *  Function:       lcdc_set_completion_callback
 *
 *  Return value:   Error status
 *
 *  Parameters:     update_complete_callback - pointer to function to call when display update has completed
 *
 *  Description:    Saves the LCDC callback function for when a display update has completed
 *
 **********************************************************************************************************************/
ER_RET  lcdc_set_completion_callback(lcdc_update_complete_callback_t update_complete_callback)
{
    ER_RET ret_val = ER_OK;

    if (update_complete_callback != (void *)0)
    {
        /* Parameters are ok */

        if (lcdc_base_address != (void *)0)
        {
            /* LCDC channel is initialised */

            update_complete = update_complete_callback;
        }
        else
        {
            ret_val = ER_INVAL; /* LCDC channel not initialised */
        }
    }
    else
    {
        ret_val = ER_PARAM;
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function lcdc_set_completion_callback
 **********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name :   lcdc_display_update
 **********************************************************************************************************************/
/*!
* @brief    Updates a rectangular area of the display
* @details  Updates the rectangular area given by the co-ordinates 'display_update_area'
* @details  This function is blocking meaning it does not return until the update has completed.
* @details  The coordinates are checked to ensure the rectangle lies completely within the display.
* @details  buf_len should be <= number of bytes within the rectangle to update.  If it's less
* @details  than the size of the rectangle, only buf_len bytes will be updated.
* @param    display_update_area - defines the rectangle to be updated
* @param    buf - pointer to new display data
* @param    buf_len - number of bytes to update
*              should be in correct format depending on configured bpp and colour mode e.g.
*           for bpp < 16  , colour is palette index of blanking colour
*           for bpp = 16, RGB 5:6:5 , colour is 0b0000 0000 0000 0000 RRRR RGGG GGGB BBBB
*           for bpp = 16, BGR 5:6:5 , colour is 0b0000 0000 0000 0000 BBBB BGGG GGGR RRRR
*           for bpp = 16, RGB 5:5:5 , colour is 0b0000 0000 0000 0000 0RRR RRGG GGGB BBBB
*           for bpp = 16, BGR 5:5:5 , colour is 0b0000 0000 0000 0000 0BBB BBGG GGGR RRRR
*
*           for bpp = 24, RGB 8:8:8 , colour is 0b0000 0000 RRRR RRRR GGGG GGGG BBBB BBBB
*           for bpp = 24, BGR 8:8:8 , colour is 0b0000 0000 BBBB BBBB GGGG GGGG RRRR RRRR
* @param    NOTE1: for bpp <= 8, rectangle co-ordinates must be on an 8-pixel boundary
* @param    NOTE2: for bpp >= 16 have 1 pixel data per 32-bit entry of buf
*                  for bpp = 8 have 1 pixel index per 32-bit entry of buf
*                  for bpp = 4 have 2 pixel indices per 32-bit entry of buf
*                  for bpp = 2 have 4 pixel indices per 32-bit entry of buf
*                  for bpp = 1 have 8 pixel indices per 32-bit entry of buf
* @retval   ER_RET - Error Status
 **********************************************************************************************************************/
ER_RET  lcdc_display_update(lcd_rectangle_t *display_update_area, uint32_t *buf, uint32_t buf_len)
{
    ER_RET ret_val = ER_OK;
    uint32_t    i;
    uint32_t    *fb_ptr32;
    uint32_t    *fb_ptr32_end;
    uint16_t    *fb_ptr16;;
    uint16_t    *fb_ptr16_end;
    uint8_t     *fb_ptr8;;
    uint8_t     *fb_ptr8_end;
    uint32_t    size;
    uint32_t    *buf_ptr = buf;

    uint32_t    start_index;         /* start byte-index into fb of entries to update */
    uint32_t    end_index;
    uint32_t    start_x;
    uint32_t    start_y;
    uint32_t    end_x;
    uint32_t    end_y;
    uint32_t    gap;                 /* number of byte entries to skip in-between updates */

    if (lcdc_base_address != (void *)0)
    {
        /* LCDC channel is initialised */

        start_index = (display_update_area->lcd_rectangle_top * lcd_config.x_res) + display_update_area->lcd_rectangle_left;    /* start byte-index into fb of entries to update */
        end_index = (display_update_area->lcd_rectangle_bottom * lcd_config.x_res) + display_update_area->lcd_rectangle_right;
        start_x = display_update_area->lcd_rectangle_left;
        start_y = display_update_area->lcd_rectangle_top;
        end_x = display_update_area->lcd_rectangle_right;
        end_y = display_update_area->lcd_rectangle_bottom;
        gap = start_x + ((lcd_config.x_res - 1) - end_x);

        /* check parameters */
        if (    ( start_y < end_y) &&
                ( end_y <  lcd_config.y_res ) &&
                ( start_x < end_x) &&
                ( end_x <  lcd_config.x_res ) )
        {
            i = 50;
            while ((display_fb == back_fb) && (i > 0))
            {
                /* wait for previous update completion with timeout */
                systimer_delay(20000);    /* delay 20 msecs */
                i--;
            }
            if (i == 0)
            {
                /* timed out */
                ret_val = ER_SYS;
            }
            else
            {
                if (palette_size == 0)
                {
                    /* check buf_size */

                    if (buf_len  < (end_x - start_x  + 1) * (end_y - start_y + 1))
                    {
                        ret_val = ER_PARAM;
                    }
                    else
                    {
                        if ((lcd_config.bpp == LCDC_DRIVER_BPP_18) || (lcd_config.bpp == LCDC_DRIVER_BPP_24))
                        {
                            /* load 32 bits per pixel to fb */
                            fb_ptr32 = (uint32_t *)((uint32_t)fb[back_fb] + (start_index * 4));

                            fb_ptr32_end = (uint32_t *)(((uint32_t)fb[back_fb]) + ((end_index + 1)*4));
                            size = (end_x - start_x  + 1);   /* word size */
                            while (fb_ptr32 < fb_ptr32_end)
                            {
                                /* fill a line */
                                for (i=0; i < size; i++)
                                {
                                    *fb_ptr32 = *buf_ptr;
                                    buf_ptr++;
                                    fb_ptr32++;
                                }
                                /* skip the gap */
                                fb_ptr32 += gap;
                            }
                        }
                        else
                        {
                            /* load 16 bits to fb per pixel */
                            fb_ptr16 = (uint16_t *)((uint32_t)fb[back_fb] + start_index);

                            fb_ptr16_end = (uint16_t *)(((uint32_t)fb[back_fb]) + (end_index + 1));
                            size = (end_x - start_x  + 1)/2;   /* word size */

                            while (fb_ptr16 < fb_ptr16_end)
                            {
                                /* fill a line */
                                for (i=0; i < size; i++)
                                {
                                    *fb_ptr16 = *((uint16_t *)buf_ptr);
                                    buf_ptr++;
                                    fb_ptr16++;
                                }
                                /* skip the gap */
                                fb_ptr16 += gap/2;
                            }
                        }
                    }
                }
                else
                {
                    /* colour is actually an index into the palette */
                    fb_ptr8 = (uint8_t *)fb[back_fb];
                    switch (lcd_config.bpp)
                    {
                        case LCDC_DRIVER_BPP_1:
                            /* 1 bit per pixel and loading 1 byte at a time */
                            if (buf_len  < (((end_x - start_x  + 1) * (end_y - start_y + 1)) /8))
                            {
                                ret_val = ER_PARAM;
                            }
                            else
                            {
                                fb_ptr8 += start_index;
                                fb_ptr8_end = (uint8_t *)(fb[back_fb]) + (end_index + 1);

                                size = (end_x - start_x  + 1) / 8;
                                while (fb_ptr8 < fb_ptr8_end)
                                {
                                    /* fill a line */
                                    for (i=0; i < size; i++)
                                    {
                                        *fb_ptr8 = (uint8_t)(*buf_ptr);
                                        fb_ptr8++;
                                        buf_ptr++;
                                    }
                                    /* skip the gap */
                                    fb_ptr8 += gap;
                                }
                            }
                            break;

                        case LCDC_DRIVER_BPP_2:

                            /* 1/4 byte per pixel and loading 1 byte at a time */
                            if (buf_len  < (((end_x - start_x  + 1) * (end_y - start_y + 1)) /4))
                            {
                                ret_val = ER_PARAM;
                            }
                            else
                            {
                                /* index to palette is 2 lsb bits */
                                fb_ptr8 += start_index;
                                fb_ptr8_end = (uint8_t *)(fb[back_fb]) + (end_index + 1);

                                size = (end_x - start_x  + 1) / 4;
                                while (fb_ptr8 < fb_ptr8_end)
                                {
                                    /* fill a line */
                                    for (i=0; i < size; i++)
                                    {
                                        *fb_ptr8 = (uint8_t)(*buf_ptr);
                                        fb_ptr8++;
                                        buf_ptr++;
                                    }
                                    /* skip the gap */
                                    fb_ptr8 += gap;
                                }
                            }

                            break;

                        case LCDC_DRIVER_BPP_4:

                            /* 1/2 byte per pixel and loading 1 byte at a time */
                            if (buf_len  < (((end_x - start_x  + 1) * (end_y - start_y + 1)) /2))
                            {
                                ret_val = ER_PARAM;
                            }
                            else
                            {
                                /* index to palette is 4 lsb bits */
                                fb_ptr8 += start_index;
                                fb_ptr8_end = (uint8_t *)(fb[back_fb]) + (end_index + 1);

                                size = (end_x - start_x  + 1) / 2;

                                while (fb_ptr8 < fb_ptr8_end)
                                {
                                    /* fill a line */
                                    for (i=0; i < size; i++)
                                    {
                                        *fb_ptr8 = (uint8_t)(*buf_ptr);
                                        fb_ptr8++;
                                        buf_ptr++;
                                    }
                                    /* skip the gap */
                                    fb_ptr8 += gap;
                                }
                            }
                            break;

                        case LCDC_DRIVER_BPP_8:
                            /* 1 byte per pixel and loading 1 byte at a time */

                            fb_ptr8 += start_index;
                            fb_ptr8_end = (uint8_t *)(fb[back_fb]) + (end_index + 1);

                            size = (end_x - start_x  + 1);

                            while (fb_ptr8 < fb_ptr8_end)
                            {
                                /* fill a line */
                                for (i=0; i < size; i++)
                                {
                                    *fb_ptr8 = (uint8_t)(*buf_ptr);
                                    fb_ptr8++;
                                    buf_ptr++;
                                }
                                /* skip the gap */
                                fb_ptr8 += gap;
                            }
                            break;

                        default:
                            ret_val = ER_SYS;
                            break;
                    }
                }
                /* flag to switch fb */
                display_fb = back_fb;
            }

        }
        else
        {
            ret_val = ER_PARAM;
        }
    }
    else
    {
        ret_val = ER_INVAL; /* LCDC channel not initialised */
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function lcdc_display_update
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *
 *  Function:       bpp_to_cr1mask
 *
 *  Return value:   LCDC CR1 register, BPP mask
 *
 *  Parameters:     bpp configured
 *
 *  Description:    Converts BPP configured to mask for BPP field of LCDC CR1 reg
 *
 **********************************************************************************************************************/
static uint32_t bpp_to_cr1mask (uint32_t bpp)
{
    uint32_t    mask;

    switch (bpp)
    {
        case LCDC_DRIVER_BPP_1:
            mask = LCDC_CR1_BPP_1;
            break;
        case LCDC_DRIVER_BPP_2:
            mask = LCDC_CR1_BPP_2 << 2;
            break;
        case LCDC_DRIVER_BPP_4:
            mask = LCDC_CR1_BPP_4 << 2;
            break;
        case LCDC_DRIVER_BPP_8:
            mask = LCDC_CR1_BPP_8 << 2;
            actual_bytes_per_pixel = 1;
            break;
        case LCDC_DRIVER_BPP_16:
            mask = LCDC_CR1_BPP_16 << 2;
            actual_bytes_per_pixel = 2;
            break;
        case LCDC_DRIVER_BPP_18:
            mask = LCDC_CR1_BPP_18 << 2;
            actual_bytes_per_pixel = 4;
            break;
        case LCDC_DRIVER_BPP_24:
            mask = LCDC_CR1_BPP_24 << 2;
            actual_bytes_per_pixel = 4;
            break;
        default:
            mask = 4 << 2;
            break;
    }
    return mask;
}
/***********************************************************************************************************************
 End of function bpp_to_cr1mask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       handle_lcdc_interrupt
 *
 *  Return value:   none
 *
 *  Parameters:     uint8_t chan_num
 *
 *  Description:    handle LCDC Interrupt for 'chan_num'
 *
 **********************************************************************************************************************/
static void handle_lcdc_interrupt(IRQn_Type *irq_num_ptr)
{
    volatile uint32_t   int_status;
    IRQn_Type           irq_num = *irq_num_ptr;
    uint32_t            size_of_fb;
    volatile uint32_t   lcdc_reg;
    volatile uint32_t   *mmr_reg_ptr;

    if (irq_num == RZN1_IRQ_LCD)
    {
        if (lcdc_base_address != (void *)0)
        {
            /* LCD controller initialised and open */

            /* Check LCDC interrupt status */
            int_status = (lcdc_base_address->rLcd_ISR.LONG);
            lcdc_base_address->rLcd_ISR.LONG = int_status;
            if (int_status & LCDC_ISR_BAU)
            {
                /* DMA Base Address field (bLcd_DBAR) transferred to Current Address field (bLcd_DCAR)*/

                /* disable BAU interrupt */
                lcdc_base_address->rLcd_IMR.BIT.bLcd_BAUM = 0;

                /* switch framebuffer if back_fb buffer loaded*/
                if (display_fb == back_fb)
                {
                    lcdc_reg = lcdc_base_address->rLcd_DBAR.LONG;

                    if (lcdc_reg != (uint32_t)fb[display_fb])
                    {
                        /* update DBAR */
                        lcdc_reg = (uint32_t)fb[display_fb];
                        lcdc_base_address->rLcd_DBAR.LONG  = lcdc_reg;

                        /* update DEAR  */
                        size_of_fb = (actual_bytes_per_pixel * lcd_config.x_res * lcd_config.y_res);
                        lcdc_reg = (uint32_t) (fb[display_fb]) + size_of_fb + 8;
                        lcdc_base_address->rLcd_DEAR.LONG  = lcdc_reg;

                        /* configure MRR to 4 outstanding requests */
                        mmr_reg_ptr = (volatile uint32_t *)(lcdc_base_address + MMR_OFFSET);
                        lcdc_reg = (((uint32_t) (fb[display_fb] + size_of_fb + 8) & 0xFFFFFFFC) | 0x2);
                        *mmr_reg_ptr = lcdc_reg;

                        /* switch back_fb */
                        back_fb = 0;
                        if (display_fb == 0)
                        {
                            back_fb = 1;
                        }
                        /* sync back_fb with display */
                        memcpy ((void *)fb[back_fb], (void *)fb[display_fb], size_of_fb);
                    }
                }

                /* re-enable BAU interrupt */
                lcdc_base_address->rLcd_IMR.BIT.bLcd_BAUM = 1;
            }
        }
    }
}
/***********************************************************************************************************************
 End of function handle_lcdc_interrupt
 **********************************************************************************************************************/





