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
 * PROJECT NAME :   RZ/N1 bare metal Drivers
 * FILE         :  r_usbf_hal.c
 * Description  :   USB Basic driver functions
 *                  Provides HW independent API to the USB function
 *                  Supports Control IN and Control OUT
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Doxygen Design Documentation block:
 **********************************************************************************************************************/
/*!
 * @page PageUSBfHAL USB function basic module Hardware Abstraction Layer
 * @tableofcontents
 * @section usbf_basic USB function basic driver
 * @ref USBF_HAL
 *
 */
/***********************************************************************************************************************
 * End of Doxygen Design block
 **********************************************************************************************************************/
/*
 ********************************************************************************
 * Doxygen Summary block
 **********************************************************************************************************************/
/*!
 * @ingroup USBF_HAL RZN1 USBf Basic Hardware Abstraction Layer
 * @{
 * @file
 * @brief USBf Basic Driver HAL
 * @details Low-level driver functions and interrupt handlers
 * @details Provides HW independent API to the USB function
 * @details Supports Control IN and Control OUT
 * @} */
/***********************************************************************************************************************
 * End of Doxygen Summary block
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes
 **********************************************************************************************************************/
#include <string.h>
#include "log_serial_io.h"
#include "r_gpio_rzn1_if.h"
#include "r_usb_rzn1_config.h"
#include "r_usbf_basic_rzn1_if.h"
#include "r_usb_common.h"
#include "r_usb_cdefusbip.h"
#include "r_usbf_hal.h"
#include "r_usbf_driver.h"
#include "r_usb_rzn1_reg_defs.h"
#include "mcu_interrupts_if.h"
#include "timer.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
/*Delay time required after removing D+ pull-up before host will see this as a disconnection.
 * See USB spec TDDIS = 2.5uS*/
#define TIME_DETACH_DETECT_US (10)

/***********************************************************************************************************************
 Typedefs
 **********************************************************************************************************************/
/*General purpose buffer*/
typedef struct DataBuff
{
    const uint8_t* pucBuf;
    uint32_t NumBytes;
} DataBuff;

/*State of control pipe*/
typedef enum StateControl
{
    STATE_DISCONNECTED, /* USB_STATE_NOTATTACHED   USB_CS_DISC  */
    STATE_READY, /* USB_STATE_POWERED       USB_CS_IDST  */
    STATE_SUSPENDED, /* USB_STATE_SUSPENDED     USB_DS_SUSP  */
    STATE_ADDRESS, /* USB_STATE_ADDRESS       USB_DS_ADDS */
    STATE_CONFIGURED, /* USB_STATE_CONFIGURED     USB_DS_CNFG */
    STATE_CONTROL_SETUP, STATE_CONTROL_IN, STATE_CONTROL_OUT
} StateControl;

/*Data structure used for OUT*/
typedef struct OUT
{
    uint32_t m_BuffSize;
    DataBuff m_DataBuff;
} OUT;

/*Data structure used for IN*/
typedef struct IN
{
    DataBuff m_DataBuff;
} IN;


/*Data structure used for Control*/
typedef struct CONTROL
{
    StateControl m_etState;
    IN m_IN;
    OUT m_OUT;
} CONTROL;

/*Data structure used for Bulk*/
typedef struct BULK
{
    /*Busy Flags*/
    bool m_INBusy;
    bool m_OUTBusy;
    IN m_IN;
    OUT m_OUT;
} BULK;

/*Data structure used for Interrupt*/
typedef struct INTERRUPT
{
    bool m_INBusy; /*Busy Flag*/
    IN m_IN;
} INTERRUPT;

typedef enum ENDPOINT_NAME
{
    ENDPOINT_NAME_Setup,
    ENDPOINT_NAME_ControlIN,
    ENDPOINT_NAME_ControlOUT,
    ENDPOINT_NAME_BulkIN,
    ENDPOINT_NAME_BulkOUT,
    ENDPOINT_NAME_InterruptIN
} ENDPOINT_NAME;

/***********************************************************************************************************************
 *  External function declarations
 **********************************************************************************************************************/
void rx_transfer_completed(uint8_t chan_num);
void tx_transfer_completed(uint8_t chan_num);

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/

EPC_EP_USBf_INT_t usb_gpstd_UsbEPCInt;

ENDPOINT usbf_eps[USBF_MAX_EPS];

/***********************************************************************************************************************
 * Local (private) variables
 **********************************************************************************************************************/

/*Control Pipe Data*/
static volatile CONTROL g_Control =
{ /*StateControl*/
STATE_DISCONNECTED,
/*IN*/
{
{ NULL, 0 }, /*DataBuff*/
},
/*OUT*/
{ 0, /*DataBuffSize*/
{ NULL, 0 }, /*DataBuff*/
} };

/*Set true if in high speed mode */
bool g_bHighSpeed = false;

/* EPC interrupt status for all interrupts */
EPC_INT_STATUS epc_ints_status;

/***********************************************************************************************************************
 * Local (private) function declarations
 **********************************************************************************************************************/
static ER_RET HW_Init(void);

/***********************************************************************************************************************
 * Function Name :   R_USBHAL_Init
 **********************************************************************************************************************/
/*!
 * @brief    Initilaises this USB HAL layer
 * @details  Enables the USB peripheral ready for enumeration.r
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
USB_ERR R_USBHAL_Init(void)
{
    ER_RET ret_val = ER_OK;

    /* Clear copy of EPC Ints Status */
    memset((uint8_t *) &epc_ints_status, 0, sizeof(epc_ints_status));

    /* Clear interrupt queues */
    memset((uint8_t *) &usb_gpstd_UsbEPCInt, 0, sizeof(usb_gpstd_UsbEPCInt));
    memset((uint8_t *) &(usbf_eps[0]), 0, sizeof(usbf_eps));

    /* Initialise the USB IP */
    ret_val = HW_Init();

    return ret_val;
}

/***********************************************************************************************************************
 End of function R_USBHAL_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Outline  : R_USBHAL_IsHighSpeed
 * Description  : Returns true if the device is in high speed mode.
 *
 * Argument     : void
 * Return value  : true: Device is in high speed mode.
 false: Device is in high speed mode
 **********************************************************************************************************************/
bool R_USBHAL_IsHighSpeed(void)
{
    return g_bHighSpeed;
}
/***********************************************************************************************************************
 End of function R_USBHAL_IsHighSpeed
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Outline      : R_USBHAL_Cancel
 * Description  : Cancel any current operations.
 *                Perform a HAL reset.
 *                Any pending "Done" callbacks will then be called with
 *                supplied error code.
 *
 *                Note: This is automatically called when the cable
 *                is disconnected.
 *
 * Argument     : _err: Error code to complete callbacks with.
 * Return value  : Error code.
 **********************************************************************************************************************/
USB_ERR R_USBHAL_Cancel(USB_ERR _err)
{
    USB_ERR err = USB_ERR_OK;

    /*Reset HAL */
    R_USBHAL_Reset();

    return err;
}
/***********************************************************************************************************************
 End of function R_USBHAL_Cancel
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_USBHAL_Reset
 **********************************************************************************************************************/
/*!
 * @brief    Resets the HAL Module to a starting state
 * @details  Note:  This does not actually reset the USB controller
 *           Can be used after an unexpected error or when wanting to
 *           cancel a pending operation where you don't want the
 *           'done' callbacks called.
 *           Used internally to reset HAL after detecting the USB
 *           cable has been disconnected/connected.
 *           1. Reset State and Busy flags and clear "done" callbacks.
 *           2. Clear control endpoint.
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void R_USBHAL_Reset(void)
{
    /*If connected then return to ready state (may already be in this state e.g. if cable just connected */
    if (USB_CS_DISC != usbf_eps[USB_EP0].state)
    {
        usbf_eps[USB_EP0].state = USB_CS_IDST;
    }

    /*Clear all buffers*/
    g_Control.m_IN.m_DataBuff.NumBytes = 0;
    g_Control.m_OUT.m_DataBuff.NumBytes = 0;
    g_Control.m_OUT.m_BuffSize = 0;

    /*Clear EP0 buffer (write & read regs on CPU side & USB side) */
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_BCLR =
            1;

    /* Prevent EP0_INAK from being cleared unintentionally */
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_INAK_EN =
            1;

    return;
}
/***********************************************************************************************************************
 End of function R_USBHAL_Reset
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   R_USBHAL_Detach
 **********************************************************************************************************************/
/*!
 * @brief    Detach the USB cable
 * @details  To a host this appears as if the USB cable has been unplugged
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void R_USBHAL_Detach(void)
{
    uint32_t control_reg;

    control_reg =
            ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.LONG;
    control_reg |= EPC_USB_CONTROL_CONNECTB_BIT; /* set CONNECTB to disable the USB signal sent to the UTMI-PHY block(and then to the SIE block) */
    control_reg &= (~EPC_USB_CONTROL_PUE2_BIT); /* Pull-up disable */
    control_reg &= (~EPC_USB_CONTROL_DEFAULT_BIT); /* Clear DEFAULT bit to disable endpoint 0 */
    control_reg &= (~EPC_USB_CONTROL_CONF_BIT); /* Disable all endpoints except ep0 */
    ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.LONG =
            control_reg;

    usbf_eps[USB_EP0].state = USB_CS_DISC;

    /*Clear all status bits as don't want to act on them now */
    ((volatile EPC_EP0_STATUS_Type *) USBFUNC_USB_EPC_EP0_STATUS_ADDRESS)->EP0_STATUS.LONG =
            0;

}
/***********************************************************************************************************************
 End of function R_USBHAL_Detach
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   HW_Init
 **********************************************************************************************************************/
/*!
 * @brief    Enable the USB function.
 * @details  System Controller R_SYSCTRL_EnableUSBf() must be called prior to this.
 * @details  Code originated from REL code u2f_init()
 * @details  Ensures that d+ is not pulled up for a period so host will think
 * @details  device is currently not connected. This ensures re-enumeration occurs
 * @details  when D+ is pulled up on VBUS detect handling.
 * @param    void
 * @retval   Error status
 **********************************************************************************************************************/
static ER_RET HW_Init(void)
{
    ER_RET ret_val = ER_OK;
    bool wait_pll_lock;

    uint16_t std_max_pkt;
    uint16_t int_iso_max_pkt;
    uint16_t ep_num;
    uint32_t i;
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;
    volatile EPC_EPm_INT_ENA_Type *epm_int_ena_reg_addr;
    volatile EPC_EPm_PCKT_ADRS_Type *epm_pckt_adrs_reg_addr;
    uint32_t prev_base_addr;
    uint32_t base_addr;
    uint32_t std_addr_offset;
    uint16_t dir_ep;
    uint16_t pipe;

    /* First, check for USB PLL locked */
    wait_pll_lock = true;
    for (i = 0; i < 0xFFFFF; i++)
    {
        if (1
                == ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.PLL_LOCK)
        {
            wait_pll_lock = false;
            break;
        }
    }

    if (true == wait_pll_lock)
    {
        ret_val = ER_SYS;
    } else
    {
        /* System Bus-EPC Bridge init */

        /*Set wait mode. (Required for USB function mode.)*/
        ((volatile AHB_EPC_AHBSCTR_Type *) USBFUNC_AHBSCTR_ADDRESS)->AHBSCTR.BIT.WAIT_MODE =
                1;

        /* Data conversion type during DMA transfer - 00:little endian */
        ((volatile AHB_EPC_AHBMCTR_Type *) USBFUNC_AHBMCTR_ADDRESS)->AHBMCTR.BIT.ENDIAN_CTR =
                0;

        /* Variable-length burst use condition for AHB master write - NCR4/8/16 + INCR for 2~3 burst */
        ((volatile AHB_EPC_AHBMCTR_Type *) USBFUNC_AHBMCTR_ADDRESS)->AHBMCTR.BIT.WBURST_TYPE =
                1;

#if USB_DMA_PP == USB_DMA_USE_PP
        /* USBf open DMA */

#endif  /* USB_DMA_PP */

        /* EPC init */

        /* U2F_EPC_INT interrupt output type select 1: Level output If there are multiple interrupt sources, the interrupt output remains
         asserted until all the sources are cleared.*/
        ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.BIT.INT_SEL =
                1;

        /* Enable bit for automatic recovery at SOF reception error */
        ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.BIT.SOF_RCV =
                1;

        /* Invert signal when SOF packet is received (no inversion by SOF) */
        ((volatile EPC_USB_CONTROL_Type *) USBFUNC_USB_EPC_CONTROL_ADDRESS)->USB_CONTROL.BIT.SOF_CLK_MODE =
                1;

        /* mask all USBf interrupts initially */
        ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.LONG =
                0;

        /* mask all EP0 interrupts initially */
        ((volatile EPC_EP0_INT_ENA_Type *) USBFUNC_USB_EPC_EP0_INT_ENA_ADDRESS)->EP0_INT_ENA.LONG =
                0;

        /* Make sure EP0 is configured then initialise */
        if ((!((volatile AHB_EPC_USBSSCONF_Type *) USBFUNC_USBSSCONF_ADDRESS)->USBSSCONF.BIT.EP_AVAILABLE)
                & 0x01)
        {
            /* EP0 unavailable - can't connect USBf */
            ret_val = ER_SYS;
        } else
        {
            /* Init EP0 */
            usbf_eps[USB_EP0].enabled = true;
            usbf_eps[USB_EP0].dma_enabled = false; /* EP0 not available for DMA transfers */
            usbf_eps[USB_EP0].type = USB_EP_CNTRL;
            usbf_eps[USB_EP0].dir = USB_EP_IN;
            usbf_eps[USB_EP0].max_packet_size = CONTROL_MAX_PACKET_SIZE;
            usbf_eps[USB_EP0].max_packets = EP_MAX_PACKET_COUNT;
            usbf_eps[USB_EP0].state = USB_CS_DISC;
            usbf_eps[USB_EP0].pipe = USB_PIPE0;

            /* Initialise Control Register for EP0 (Disable EP for now)*/
            ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_DEND =
                    0; /* Disable tx enable of EP0 write reg */
            ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_DW =
                    0; /* Data size for EP0 write reg */
            ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_PIDCLR =
                    1; /* Set this bit to initialize rx DATA PID for EP0 */

            if (false
                    == epn_flush_buffer(USB_EP0,
                            (EPC_EP0_STATUS_EP0_IN_EMPTY_BIT
                                    | EPC_EP0_STATUS_EP0_OUT_EMPTY_BIT)))
            {
                ret_val = ER_SYS;
            }
        }
        if (ER_OK == ret_val)
        {
            /* No errors so far */

            /* Get current port speed */
            if ( USB_HSCONNECT == usb_cstd_PortSpeed())
            {
                g_bHighSpeed = true;
                std_max_pkt = EPm_MAX_PACKET_SIZE_HS;
            } else
            {
                g_bHighSpeed = false;
                std_max_pkt = EPm_MAX_PACKET_SIZE_FS;
            }

            int_iso_max_pkt = (2 * std_max_pkt); /* For Interrupt & Isochronous type endpoints */
            base_addr = EP0_BUFFERS_SIZE; /* First Base addr to be added to base addr for subsequent EPs */
            prev_base_addr = 0;
            std_addr_offset = std_max_pkt / 2; /* offset in words */

            /* Initialise Registers for all other configured endpoints - EP[m] (m=1-15) */
            for (ep_num = USB_EP1;
                    (ep_num <= USB_MAX_EP_NO) && (ER_OK == ret_val); ep_num++)
            {
                /* Make sure EP is configured then initialise */
                if (((volatile AHB_EPC_USBSSCONF_Type *) USBFUNC_USBSSCONF_ADDRESS)->USBSSCONF.BIT.EP_AVAILABLE
                        & (0x01 << ep_num))
                {
                    /* EP is available */

                    /* Init ep_num structure */
                    usbf_eps[ep_num].enabled = true;
                    usbf_eps[ep_num].open = false;
                    usbf_eps[ep_num].dma_enabled =
                            ((volatile AHB_EPC_USBSSCONF_Type *) USBFUNC_USBSSCONF_ADDRESS)->USBSSCONF.BIT.DMA_AVAILABLE
                                    & (0x010000 << ep_num);

                    /* The hardware has fixed types for specific ranges of endpoints - please see R01UH0751EJ0095 Rev.0.95 Table 10.134. NOTE: The fixed directions in this table are NOT correct */
                    if (ep_num <= USB_EP5)
                    {
                        usbf_eps[ep_num].type = USB_EP_BULK;
                    } else if (ep_num <= USB_EP9)
                    {
                        usbf_eps[ep_num].type = USB_EP_INT;
                    } else
                    {
                        usbf_eps[ep_num].type = USB_EP_ISO;
                    }

                    /* Get the direction of the Endpoint via the associated pipe direction */
                    if (USB_DIR_P_IN == usb_cstd_EpNum2PipeDir(ep_num))
                    {
                        usbf_eps[ep_num].dir = USB_EP_IN;
                    }
                    else
                    {
                        usbf_eps[ep_num].dir = USB_EP_OUT;
                    }

                    usbf_eps[ep_num].max_packets = EP_MAX_PACKET_COUNT;
                    usbf_eps[ep_num].state = USB_DS_IDST;
                    /* find pipe number for this EP from selected pipe table configuration */
                    dir_ep = usbf_eps[ep_num].dir | ep_num;
                    pipe = usb_cstd_Epadr2Pipe(dir_ep);
                    if ( USB_ERROR == pipe)
                    {
                        /* pipe not configured for theis EP and direction */
                        usbf_eps[ep_num].pipe = USB_CLRPIPE;
                    } else
                    {
                        usbf_eps[ep_num].pipe = pipe;
                    }

                    /* Initialise Control Register for endpoint - EP[m]_CONTROL (Disable EP for now)*/
                    epm_control_reg_addr =
                            (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                                    + (0x20 * (ep_num - 1)));
                    epm_control_reg_addr->EPm_CONTROL.BIT.EPm_EN = 0; /* EP disabled. When ready for connection, set to 1 */
                    epm_control_reg_addr->EPm_CONTROL.BIT.EPm_ONAK = 1; /* Return a NAK even if there is available space in the reception buffer - Set to 0 when enable the EP */
                    epm_control_reg_addr->EPm_CONTROL.BIT.EPm_OSTL_EN = 1; /* Enable write-enable bit of EPm_OSTL */
                    epm_control_reg_addr->EPm_CONTROL.BIT.EPm_OSTL = 0; /* Stall response control bit for OUT/Ping token */
                    epm_control_reg_addr->EPm_CONTROL.BIT.EPm_OSTL_EN = 0; /* Disable write-enable bit of EPm_OSTL */
                    epm_control_reg_addr->EPm_CONTROL.BIT.EPm_ISTL = 0; /* Stall response control bit for IN token */
                    epm_control_reg_addr->EPm_CONTROL.BIT.EPm_DEND = 0; /* Disable tx enable of EPm write reg */
                    epm_control_reg_addr->EPm_CONTROL.BIT.EPm_DW = 0; /* Data size for EPm write reg */

                    /*((volatile EPC_EPm_CONTROL_Type *)USBFUNC_USB_EPC_EPm_CONTROL_ADDRESS)->EPm_CONTROL.BIT.EPm_OPIDCLR = 1; *//* Set this bit to initialize tx DATA PID for EPm */
                    /*((volatile EPC_EPm_CONTROL_Type *)USBFUNC_USB_EPC_EPm_CONTROL_ADDRESS)->EPm_CONTROL.BIT.EPm_IPIDCLR = 1; *//* Set this bit to initialize rx DATA PID for EPm */
                    epm_control_reg_addr->EPm_CONTROL.BIT.EPm_AUTO = 0; /* Don't send a packet automatically when maxPacketSize data is written to EPm write reg */
                    epm_control_reg_addr->EPm_CONTROL.BIT.EPm_OVERSEL = 0;
                    epm_control_reg_addr->EPm_CONTROL.BIT.EPm_DIR0 = 0; /* Direction of EPm is IN */

                    /* mask all EPm interrupts initially */
                    epm_int_ena_reg_addr =
                            (volatile EPC_EPm_INT_ENA_Type *) (USBFUNC_USB_EPC_EP1_INT_ENA_ADDRESS
                                    + (0x20 * (ep_num - 1)));
                    epm_int_ena_reg_addr->EPm_INT_ENA.LONG = 0;

                    /* Initialise default MaxPacket and Base Address Register for EPm */
                    epm_pckt_adrs_reg_addr =
                            (volatile EPC_EPm_PCKT_ADRS_Type *) (USBFUNC_USB_EPC_EP1_PCKT_ADRS_ADDRESS
                                    + (0x20 * (ep_num - 1)));

                    if (ep_num <= USB_EP5)
                    {
                        epm_pckt_adrs_reg_addr->EPm_PCKT_ADRS.BIT.EPm_MPKT =
                                std_max_pkt;
                        usbf_eps[ep_num].max_packet_size = std_max_pkt;
                    } else
                    {
                        /* Interrupt & Isochronous type endpoints */
                        epm_pckt_adrs_reg_addr->EPm_PCKT_ADRS.BIT.EPm_MPKT =
                                int_iso_max_pkt;
                        usbf_eps[ep_num].max_packet_size = int_iso_max_pkt;
                    }

                    if (0 != prev_base_addr)
                    {
                        base_addr = prev_base_addr + std_addr_offset; /* base addr offset in words */
                    }
                    epm_pckt_adrs_reg_addr->EPm_PCKT_ADRS.BIT.EPm_BASEAD =
                            base_addr;
                    prev_base_addr = base_addr;

                    if (false
                            == epn_flush_buffer(ep_num,
                                    (EPC_EPm_STATUS_IN_EMPTY_BIT
                                            | EPC_EPm_STATUS_OUT_EMPTY_BIT)))
                    {
                        ret_val = ER_SYS;
                    }
                }
            }
        }

        /*Ensure we are starting from a point where we are disconnected (D+ is not pulled up), so that when we do pull-up D+ we will be enumerated.*/
        R_USBHAL_Detach();
        /*Delay here to ensure host sees the disconnect before we pull D+ up - (don't think this is relevant as we don't pull D+ up until get VBUS int & VBUS level is '1') */
        /* systimer_delay(TIME_DETACH_DETECT_US);*/

        R_USBHAL_Reset();
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function HW_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   epn_flush_buffer
 **********************************************************************************************************************/
/*!
 * @brief    Clear write and read registers for an EP
 * @details
 * @param    ep_num  - endpoint
 * @param    buf_mask - mask indicated OUT and/or IN buf to flush
 * @retval   true if success, false if failure
 **********************************************************************************************************************/
bool epn_flush_buffer(uint16_t ep_num, uint32_t buf_mask)
{
    bool ret_val = true;
    uint16_t wait_count = 200;
    volatile EPC_EP0_CONTROL_Type *ep0_control_reg_addr;
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;

    volatile EPC_EP0_STATUS_Type *ep0_status_reg_addr;
    volatile EPC_EPm_STATUS_Type *epm_status_reg_addr;

    if (USB_EP0 == ep_num)
    {
        ep0_status_reg_addr =
                (volatile EPC_EP0_STATUS_Type *) (USBFUNC_USB_EPC_EP0_STATUS_ADDRESS);
        ep0_control_reg_addr =
                (volatile EPC_EP0_CONTROL_Type *) (USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS);

        /* check to see if buffer(s) already empty */
        if ((ep0_status_reg_addr->EP0_STATUS.LONG & buf_mask) != buf_mask)
        {
            ep0_control_reg_addr->EP0_CONTROL.BIT.EP0_BCLR = 1;

            /* wait for empty status */
            for (; wait_count > 0; wait_count--)
            {
                if ((ep0_status_reg_addr->EP0_STATUS.LONG & buf_mask)
                        == buf_mask)
                {
                    break;
                }
                systimer_delay(50); /* Delay 50 usecs */
            }
        }
    } else
    {
        epm_status_reg_addr =
                (volatile EPC_EPm_STATUS_Type *) (USBFUNC_USB_EPC_EP1_STATUS_ADDRESS
                        + (0x20 * (ep_num - 1)));
        epm_control_reg_addr =
                (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                        + (0x20 * (ep_num - 1)));

        /* check to see if buffer(s) already empty */
        if ((epm_status_reg_addr->EPm_STATUS.LONG & buf_mask) != buf_mask)
        {
            epm_control_reg_addr->EPm_CONTROL.BIT.EPm_BCLR = 1;

            /* wait for empty status */
            for (; wait_count > 0; wait_count--)
            {
                if ((epm_status_reg_addr->EPm_STATUS.LONG & buf_mask)
                        == buf_mask)
                {
                    break;
                }
                systimer_delay(50); /* Delay 50 usecs */
            }
        }
    }

    if (0 == wait_count)
    {
        ret_val = false;
    }
    return ret_val;

}
/***********************************************************************************************************************
 End of function epn_flush_buffer
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   usb_pstd_ChkVbsts
 **********************************************************************************************************************/
/*!
 * @brief    Return the VBUS status
 * @details
 * @param    void
 * @retval   uint16_t connection status(ATTACH/DETACH)
 **********************************************************************************************************************/
uint16_t usb_pstd_ChkVbsts(void)
{
    uint32_t buf1;
    uint32_t buf2;
    uint32_t buf3;
    uint16_t connect_info = USB_CONNECT_UNCHANGED;

    /* VBUS chattering cut */
    do
    {
        buf1 =
                ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.VBUS_LEVEL;
        systimer_delay(10); /* delay for 10 usecs */
        buf2 =
                ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.VBUS_LEVEL;
        systimer_delay(10); /* delay for 10 usecs */
        buf3 =
                ((volatile AHB_EPC_EPCTR_Type *) USBFUNC_EPCTR_ADDRESS)->EPCTR.BIT.VBUS_LEVEL;
    } while ((buf1 != buf2) || (buf2 != buf3));

    /* Check VBUS level */
    if (1 == buf1)
    {
        /* Connected. If already connected - no change */
        if (USB_CS_DISC == usbf_eps[USB_EP0].state)
        {
            usbf_eps[USB_EP0].state = USB_CS_IDST;
            connect_info = USB_ATTACH;
        }
    } else
    {
        /* Disconnected */
        if (USB_CS_DISC != usbf_eps[USB_EP0].state)
        {
            usbf_eps[USB_EP0].state = USB_CS_DISC;
            connect_info = USB_DETACH;
        }
    }
    return connect_info;
}
/***********************************************************************************************************************
 End of function usb_pstd_ChkVbsts
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   handle_usbf_epc_isr
 **********************************************************************************************************************/
/*!
 * @brief    USBf EndPoint Controller interrupt handler
 * @details  Handle USBf EPC interrupt
 * @param    irq_num_ptr - pointer to interrupt vector number
 * @retval   void
 **********************************************************************************************************************/
void handle_usbf_epc_isr(IRQn_Type *irq_num_ptr)
{
    IRQn_Type irq_num = *irq_num_ptr;
    uint16_t ep_num;
    volatile EPC_USB_INT_STA_Type *usb_int_status_reg_addr;
    volatile EPC_EP0_STATUS_Type *ep0_status_reg_addr;
    volatile EPC_EPm_STATUS_Type *epm_status_reg_addr;

    uint32_t usb_ints_enabled;
    uint32_t usb_int_status;
    uint32_t epn_ints_enabled;
    uint32_t epn_int_status[USBF_MAX_EPS];

    __IO unsigned long usb_int_status_reg;

    if (RZN1_IRQ_USBF_EPC == irq_num)
    {
        /* Save enabled ints */
        usb_ints_enabled =
                ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.LONG;
        /* Disable ints */
        ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.LONG =
                0;

        /* Read USB int status register & clear  status bits */
        usb_int_status_reg_addr =
                (volatile EPC_USB_INT_STA_Type *) (USBFUNC_USB_EPC_USB_INT_STA_ADDRESS);

        usb_int_status = usb_int_status_reg_addr->USB_INT_STA.LONG;
        usb_int_status &= usb_ints_enabled;
        usb_int_status_reg_addr->USB_INT_STA.LONG = ~usb_int_status;

        /* Read EP0 int status register & clear status bits */
        ep0_status_reg_addr =
                (volatile EPC_EP0_STATUS_Type *) (USBFUNC_USB_EPC_EP0_STATUS_ADDRESS);
        epn_int_status[USB_EP0] = ep0_status_reg_addr->EP0_STATUS.LONG;
        epn_ints_enabled =
                ((volatile EPC_EP0_INT_ENA_Type *) USBFUNC_USB_EPC_EP0_INT_ENA_ADDRESS)->EP0_INT_ENA.LONG;
        epn_int_status[USB_EP0] &= epn_ints_enabled;
        ep0_status_reg_addr->EP0_STATUS.LONG = ~epn_int_status[USB_EP0];

        /* Read int status register for all other EPs & clear status bits */
        for (ep_num = USB_EP1; ep_num <= USB_MAX_EP_NO; ep_num++)
        {
            if (usbf_eps[ep_num].enabled)
            {
                epm_status_reg_addr =
                        (volatile EPC_EPm_STATUS_Type *) (USBFUNC_USB_EPC_EP1_STATUS_ADDRESS
                                + (0x20 * (ep_num - 1)));
                epn_int_status[ep_num] = epm_status_reg_addr->EPm_STATUS.LONG;
                epn_ints_enabled =
                        ((volatile EPC_EPm_INT_ENA_Type *) (USBFUNC_USB_EPC_EP1_INT_ENA_ADDRESS
                                + (0x20 * (ep_num - 1))))->EPm_INT_ENA.LONG;
                epn_int_status[ep_num] &= epn_ints_enabled;
                epm_status_reg_addr->EPm_STATUS.LONG = ~epn_int_status[ep_num];
            }
        }

        /* Push Interrupt status */
        usb_gpstd_UsbEPCInt.Buf[usb_gpstd_UsbEPCInt.Wp].usb_status =
                usb_int_status;
        for (ep_num = USB_EP0; ep_num <= USB_MAX_EP_NO; ep_num++)
        {
            usb_gpstd_UsbEPCInt.Buf[usb_gpstd_UsbEPCInt.Wp].epn_status[ep_num] =
                    epn_int_status[ep_num];
        }
        /* Increment write pointer */
        usb_gpstd_UsbEPCInt.Wp =
                ((usb_gpstd_UsbEPCInt.Wp + 1) % USB_INT_BUFSIZE);

        /* Re-enable ints */
        ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.LONG =
                usb_ints_enabled;
    }
}
/***********************************************************************************************************************
 End of function handle_usbf_epc_isr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   handle_usbf_isr
 **********************************************************************************************************************/
/*!
 * @brief    USBf interrupt handler
 * @details  Handle USBf interrupt
 * @param    irq_num_ptr - pointer to interrupt vector number
 * @retval   void
 **********************************************************************************************************************/
void handle_usbf_isr(IRQn_Type *irq_num_ptr)
{
    IRQn_Type irq_num = *irq_num_ptr;
    volatile uint32_t usbf_int_status;

    if (RZN1_IRQ_USBF == irq_num)
    {
        /* Read interrupt status */
        usbf_int_status =
                ((volatile AHB_EPC_AHBBINT_Type *) USBFUNC_AHBBINT_ADDRESS)->AHBBINT.LONG;

        /* Clear interrupts*/
        ((volatile AHB_EPC_AHBBINT_Type *) USBFUNC_AHBBINT_ADDRESS)->AHBBINT.LONG =
                usbf_int_status;

        if (usbf_int_status & AHB_EPC_AHBBINT_VBUS_INT_BIT)
        {
            /* VBUS signal level has changed */

            /* Disable VBUS interrupt until this change is stable */
            ((volatile AHB_EPC_AHBBINTEN_Type *) USBFUNC_AHBBINTEN_ADDRESS)->AHBBINTEN.BIT.VBUS_INT_EN =
                    0;

            /* Process outside interrupt handler */
            check_vbus_level = true;
        }
    }
}
/***********************************************************************************************************************
 End of function handle_usbf_isr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   enable_usbf_epc_isr
 **********************************************************************************************************************/
/*!
 * @brief    USBf EPC USB interrupt enable
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void enable_usbf_epc_isr(void)
{
    ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.BIT.SPEED_MODE_EN = 1; /* speed mode change */
    /*((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.BIT.SOF_ERROR_EN = 1;*//* SOF error */
    /*((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.BIT.SOF_EN = 1; *//* Start of Frame */
    ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.BIT.USB_RST_EN = 1; /* USB Reset */
    ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.BIT.SPND_EN = 1; /* Suspend */
    ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.BIT.RSUM_EN = 1; /* Resume */
}
/***********************************************************************************************************************
 End of function enable_usbf_epc_isr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   disable_usbf_epc_isr
 **********************************************************************************************************************/
/*!
 * @brief    USBf EPC USB interrupts disable
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void disable_usbf_epc_isr(void)
{
    /* Disable all ints */
    ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.LONG = 0;
}
/***********************************************************************************************************************
 End of function disable_usbf_epc_isr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function Name :   enable_usbf_epc_ep0_isr
 **********************************************************************************************************************/
/*!
 * @brief    USBf EndPoint Controller enable interrupts for EP0
 * @details
 * @param    NONE
 * @retval   void
 **********************************************************************************************************************/
void enable_usbf_epc_ep0_isr(void)
{
    uint32_t ep0_control_reg;
    uint32_t ep0_int_enable_reg;

    ep0_control_reg = ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.LONG;
    ep0_control_reg |= EPC_EP0_CONTROL_EP0_INAK_EN_BIT;
    ep0_control_reg |= EPC_EP0_CONTROL_EP0_BCLR_BIT;
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.LONG = ep0_control_reg;

    ep0_int_enable_reg = ((volatile EPC_EP0_INT_ENA_Type *) USBFUNC_USB_EPC_EP0_INT_ENA_ADDRESS)->EP0_INT_ENA.LONG;
    ep0_int_enable_reg |= EPC_EP0_INT_SETUP_EN_BIT;
    ep0_int_enable_reg |= EPC_EP0_INT_STG_START_EN_BIT;
    ep0_int_enable_reg |= EPC_EP0_INT_EP0_STALL_EN_BIT;

    ep0_int_enable_reg |= EPC_EP0_INT_STG_END_EN_BIT;
    ep0_int_enable_reg |= EPC_EP0_INT_EP0_OUT_EN_BIT;

    /* ep0_int_enable_reg |= EPC_EP0_INT_EP0_OUT_OR_EN_BIT; */

    ((volatile EPC_EP0_INT_ENA_Type *) USBFUNC_USB_EPC_EP0_INT_ENA_ADDRESS)->EP0_INT_ENA.LONG = ep0_int_enable_reg;

    ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.BIT.EP0_EN = 1;
}
/***********************************************************************************************************************
 End of function enable_usbf_epc_ep0_isr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function Name :   disable_usbf_epc_ep0_isr
 **********************************************************************************************************************/
/*!
 * @brief    USBf EndPoint Controller disable interrupts for EP0
 * @details
 * @param    NONE
 * @retval   void
 **********************************************************************************************************************/
void disable_usbf_epc_ep0_isr(void)
{
    ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.BIT.EP0_EN = 0;
    ((volatile EPC_EP0_INT_ENA_Type *) USBFUNC_USB_EPC_EP0_INT_ENA_ADDRESS)->EP0_INT_ENA.LONG = 0;
    ((volatile EPC_EP0_CONTROL_Type *) USBFUNC_USB_EPC_EP0_CONTROL_ADDRESS)->EP0_CONTROL.BIT.EP0_INAK_EN = 0;
}
/***********************************************************************************************************************
 End of function disable_usbf_epc_ep0_isr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function Name :   enable_usbf_epc_epm_isr
 **********************************************************************************************************************/
/*!
 * @brief    USBf EndPoint Controller enable interrupts for EP[m]
 * @details
 * @param    end_point - EP index
 * @retval   void
 **********************************************************************************************************************/
void enable_usbf_epc_epm_isr(uint16_t end_point)
{
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;
    volatile EPC_EPm_INT_ENA_Type *epm_int_enable_reg_addr;
    uint32_t usb_int_enable_reg;
    uint32_t epm_control_reg;
    uint32_t epm_int_enable_reg;

    epm_int_enable_reg_addr = (volatile EPC_EPm_INT_ENA_Type *) (USBFUNC_USB_EPC_EP1_INT_ENA_ADDRESS
                    + (0x20 * (end_point - 1)));
    epm_int_enable_reg = epm_int_enable_reg_addr->EPm_INT_ENA.LONG;

    if (USB_EP_OUT == usbf_eps[end_point].dir)
    {
        /*epm_int_enable_reg |= EPC_EPm_INT_EPm_OUT_EN_BIT;
         epm_int_enable_reg |= EPC_EPm_INT_EPm_OUT_END_EN_BIT;*/
        epm_int_enable_reg = EPC_EPm_INT_EPm_OUT_EN_BIT
                | EPC_EPm_INT_EPm_OUT_END_EN_BIT;
    }

    if (USB_EP_IN == usbf_eps[end_point].dir)
    {
        /*epm_int_enable_reg |= EPC_EPm_INT_EPm_IN_EN_BIT; */
        epm_int_enable_reg = EPC_EPm_INT_EPm_IN_EN_BIT;
    }

    epm_int_enable_reg_addr->EPm_INT_ENA.LONG = epm_int_enable_reg;

    epm_control_reg_addr =
            (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                    + (0x20 * (end_point - 1)));
    /*epm_control_reg = epm_control_reg_addr->EPm_CONTROL.LONG; */

    epm_control_reg = (uint32_t)EPC_EPm_CONTROL_EPm_BCLR_BIT;
    epm_control_reg |= (uint32_t)EPC_EPm_CONTROL_EPm_EPm_EN_BIT;

    if (USB_EP_OUT == usbf_eps[end_point].dir)
    {
        epm_control_reg |= EPC_EPm_CONTROL_EPm_DIR0_BIT;
    }
    epm_control_reg_addr->EPm_CONTROL.LONG = epm_control_reg;

    usb_int_enable_reg =
            ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.LONG;
    usb_int_enable_reg |= (__IO unsigned long )((uint32_t)1 << (8 + end_point));
    ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.LONG =
            usb_int_enable_reg;
}
/***********************************************************************************************************************
 End of function enable_usbf_epc_epm_isr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function Name :   disable_usbf_epc_epm_isr
 **********************************************************************************************************************/
/*!
 * @brief    USBf EndPoint Controller disable interrupts for EP[m]
 * @details
 * @param    uint16_t end_point
 * @retval   void
 **********************************************************************************************************************/
void disable_usbf_epc_epm_isr(uint16_t end_point)
{
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;
    uint32_t epm_control_reg;
    uint32_t usb_int_enable_reg;

    usb_int_enable_reg =
            ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.LONG;
    usb_int_enable_reg &= (__IO unsigned long )~((uint32_t)1 << (8 + end_point));
    ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.LONG =
            usb_int_enable_reg;

    epm_control_reg_addr =
            (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                    + (0x20 * (end_point - 1)));

    epm_control_reg = epm_control_reg_addr->EPm_CONTROL.LONG;
    epm_control_reg &= (~EPC_EPm_CONTROL_EPm_EPm_EN_BIT);
    epm_control_reg_addr->EPm_CONTROL.LONG = epm_control_reg;
}
/***********************************************************************************************************************
 End of function disable_usbf_epc_epm_isr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function Name :   open_usbf_epc_epm
 **********************************************************************************************************************/
/*!
 * @brief    USBf EndPoint Controller Open for EP[m]
 * @details
 * @param    end_point - EP index
 * @retval   void
 **********************************************************************************************************************/
void open_usbf_epc_epm(uint16_t end_point)
{
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;

    volatile EPC_EPm_INT_ENA_Type *epm_int_enable_reg_addr;
    volatile EPC_EPm_PCKT_ADRS_Type *epm_pckt_adrs_reg_addr;
    uint32_t usb_int_enable_reg;
    uint32_t epm_control_reg;
    uint32_t epm_int_enable_reg;
    uint16_t std_max_pkt;

    /* Get current port speed */
    if ( USB_HSCONNECT == usb_cstd_PortSpeed())
    {
        std_max_pkt = EPm_MAX_PACKET_SIZE_HS;
    } else
    {
        std_max_pkt = EPm_MAX_PACKET_SIZE_FS;
    }
    /* Initialise default MaxPacket and Base Address Register for EPm */
    epm_pckt_adrs_reg_addr =
            (volatile EPC_EPm_PCKT_ADRS_Type *) (USBFUNC_USB_EPC_EP1_PCKT_ADRS_ADDRESS
                    + (0x20 * (end_point - 1)));
    if (end_point <= USB_EP5)
    {
        epm_pckt_adrs_reg_addr->EPm_PCKT_ADRS.BIT.EPm_MPKT = std_max_pkt;
        usbf_eps[end_point].max_packet_size = std_max_pkt;
    } else
    {
        /* Interrupt & Isochronous type endpoints */
        epm_pckt_adrs_reg_addr->EPm_PCKT_ADRS.BIT.EPm_MPKT = std_max_pkt * 2;
        usbf_eps[end_point].max_packet_size = std_max_pkt * 2;
    }

    epm_int_enable_reg_addr =
            (volatile EPC_EPm_INT_ENA_Type *) (USBFUNC_USB_EPC_EP1_INT_ENA_ADDRESS
                    + (0x20 * (end_point - 1)));
    epm_int_enable_reg = epm_int_enable_reg_addr->EPm_INT_ENA.LONG;

    if (USB_EP_OUT == usbf_eps[end_point].dir)
    {
        /*epm_int_enable_reg |= EPC_EPm_INT_EPm_OUT_EN_BIT;
         epm_int_enable_reg |= EPC_EPm_INT_EPm_OUT_END_EN_BIT;*/
        epm_int_enable_reg = EPC_EPm_INT_EPm_OUT_EN_BIT
                | EPC_EPm_INT_EPm_OUT_END_EN_BIT;
    }

    if (USB_EP_IN == usbf_eps[end_point].dir)
    {
        /*epm_int_enable_reg |= EPC_EPm_INT_EPm_IN_EN_BIT; */
        epm_int_enable_reg = EPC_EPm_INT_EPm_IN_EN_BIT;
    }

    epm_int_enable_reg_addr->EPm_INT_ENA.LONG = epm_int_enable_reg;

    epm_control_reg_addr =
            (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                    + (0x20 * (end_point - 1)));
    /*epm_control_reg = epm_control_reg_addr->EPm_CONTROL.LONG; */

    epm_control_reg = (uint32_t)EPC_EPm_CONTROL_EPm_BCLR_BIT;
    epm_control_reg |= (uint32_t)EPC_EPm_CONTROL_EPm_EPm_EN_BIT;

    if (USB_EP_OUT == usbf_eps[end_point].dir)
    {
        epm_control_reg |= EPC_EPm_CONTROL_EPm_DIR0_BIT;
    }
    epm_control_reg_addr->EPm_CONTROL.LONG = epm_control_reg;

    usb_int_enable_reg =
            ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.LONG;
    usb_int_enable_reg |= (__IO unsigned long )((uint32_t)1 << (8 + end_point));
    ((volatile EPC_USB_INT_ENA_Type *) USBFUNC_USB_EPC_USB_INT_ENA_ADDRESS)->USB_INT_ENA.LONG =
            usb_int_enable_reg;

    usbf_eps[end_point].open = true;
}
/***********************************************************************************************************************
 End of function open_usbf_epc_epm
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Function Name :   close_usbf_epc_epm
 **********************************************************************************************************************/
/*!
 * @brief    USBf close Endpoint
 * @details
 * @param    uint16_t end_point
 * @retval   void
 **********************************************************************************************************************/
void close_usbf_epc_epm(uint16_t end_point)
{
    volatile EPC_EPm_CONTROL_Type *epm_control_reg_addr;
    volatile EPC_EPm_INT_ENA_Type *epm_int_enable_reg_addr;
    uint32_t epm_control_reg;
    uint32_t epm_int_enable_reg;
    ;

    disable_usbf_epc_epm_isr(end_point);

    epm_control_reg_addr =
            (volatile EPC_EPm_CONTROL_Type *) (USBFUNC_USB_EPC_EP1_CONTROL_ADDRESS
                    + (0x20 * (end_point - 1)));

    epm_control_reg = epm_control_reg_addr->EPm_CONTROL.LONG;
    epm_control_reg &= (~EPC_EPm_CONTROL_EPm_EPm_EN_BIT);
    epm_control_reg |= (uint32_t)EPC_EPm_CONTROL_EPm_ONAK_BIT;
    epm_control_reg_addr->EPm_CONTROL.LONG = epm_control_reg;

    epm_int_enable_reg_addr =
            (volatile EPC_EPm_INT_ENA_Type *) (USBFUNC_USB_EPC_EP1_INT_ENA_ADDRESS
                    + (0x20 * (end_point - 1)));

    epm_int_enable_reg = epm_int_enable_reg_addr->EPm_INT_ENA.LONG;
    epm_int_enable_reg &= (~EPC_EPm_INT_EPm_OUT_EN_BIT);
    epm_int_enable_reg &= (~EPC_EPm_INT_EPm_OUT_END_EN_BIT);
    epm_int_enable_reg &= (~EPC_EPm_INT_EPm_IN_EN_BIT);

    epm_int_enable_reg_addr->EPm_INT_ENA.LONG = epm_int_enable_reg;

    usbf_eps[end_point].open = false;
}
/***********************************************************************************************************************
 End of function close_usbf_epc_epm
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   enable_usbf_ahb_epc_isr
 **********************************************************************************************************************/
/*!
 * @brief    Enable AHB-EPC bridge interrupts
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void enable_usbf_ahb_epc_isr(void)
{
    /* VBUS interrupt enable*/
    ((volatile AHB_EPC_AHBBINTEN_Type *) USBFUNC_AHBBINTEN_ADDRESS)->AHBBINTEN.BIT.VBUS_INT_EN =
            1;
}
/***********************************************************************************************************************
 End of function enable_usbf_ahb_epc_isr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Function Name :   disable_usbf_ahb_epc_isr
 **********************************************************************************************************************/
/*!
 * @brief    Disable all AHB-EPC bridge interrupts
 * @details
 * @param    void
 * @retval   void
 **********************************************************************************************************************/
void disable_usbf_ahb_epc_isr(void)
{
    /* Disable all ints */
    ((volatile AHB_EPC_AHBBINTEN_Type *) USBFUNC_AHBBINTEN_ADDRESS)->AHBBINTEN.LONG =
            0;
}
/***********************************************************************************************************************
 End of function disable_usbf_ahb_epc_isr
 **********************************************************************************************************************/
