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
 * $Revision: 1806 $
 * $Date: 2020-01-10 17:46:36 +0000 (Fri, 10 Jan 2020) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hcdc_rzn1_if.c
 * Description  :  USB Host CDC Interface File
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_usb_hcdc_rzn1_if.h"
#include "platform.h"
#include "iodefine.h"
#include <string.h>

/***********************************************************************************************************************
 Constant macro definitions
 **********************************************************************************************************************/
#define CLASS_REQUEST_SET_CONTROL_LINE_STATE_SEQ_ID         0
#define CLASS_REQUEST_SET_LINE_CODING_SEQ_ID                1
#define CLASS_REQUEST_GET_LINE_CODING_SEQ_ID                2
#define CLASS_REQUEST_SEND_BREAK_SEQ_ID                     3

#define IS_CDC_DEV_ADDR_VALID(devadr)                       (STATE_WAIT_ATTACHMENT != m_usb_hcdc_dev_info[devadr].state)

/* Max event pool count */
#define EVENT_MAX                                           5

/***********************************************************************************************************************
 Enumerated Types
 **********************************************************************************************************************/
typedef enum
{
    STATE_WAIT_ATTACHMENT,
    STATE_CLASS_REQUEST,
    STATE_DATA_TRANSFER,
}
STATE_t;

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
typedef struct DEV_INFO             /* Structure for CDC device control */
{
    uint16_t    state;              /* State for application */
    uint16_t    event_cnt;          /* Event count */
    uint16_t    event[EVENT_MAX];   /* Event no. */
    uint16_t    in_pipe;            /* Use pipe no. */
    uint16_t    out_pipe;           /* Use pipe no. */
    uint16_t    status_pipe;        /* Use pipe no. */
    uint16_t    cr_seq;             /* Class Request Sequence */
    uint16_t    tx_len;                                             /* Tx Length */
    uint8_t     tx_data[ CDC_DATA_LEN + 4 ];                        /* Tx Data */
    uint16_t    rx_len;                                             /* Rx Length */
    uint8_t     rx_data[ CDC_DATA_LEN + 4 ];                        /* Rx Data */
    uint8_t     serial_state_data[USB_HCDC_SERIAL_STATE_MSG_LEN];   /* SerialState Data */
    USB_HCDC_SerialState_t  serial_state_bitmap;                    /* SerialState Bitmap */
    USB_HCDC_LineCoding_t   com_parm;                               /* Set Line Coding parameter */
    bool        is_write_busy;
    uint16_t    break_period_ms;                                    /* Send break parameter */
}
DEV_INFO_t;

/***********************************************************************************************************************
 variables
 **********************************************************************************************************************/
/* Host CDC TPL */
const uint16_t m_usb_hcdc_device_tpl[] =
{
    1,                      /* Number of list */
    0,                      /* Reserved */
    USB_NOVENDOR,           /* Vendor ID  : no-check */
    USB_NOPRODUCT,          /* Product ID : no-check */
};

/* CDC device control structure */
UNCACHED_BUFFER static DEV_INFO_t  m_usb_hcdc_dev_info[USB_MAXDEVADDR +1u];
static USB_HCDC_CB_t m_usb_hcdc_cb = FIT_NO_PTR;

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
 /* Application functions */
static uint16_t R_USB_HCDC_ConnectWait( uint16_t devadr );
static uint16_t R_USB_HCDC_ClassRequest( uint16_t devadr );
static uint16_t R_USB_HCDC_DataTransfer( uint16_t devadr );
/* State change callback functions */
static void R_USB_HCDC_Configured( uint16_t devadr );
static void R_USB_HCDC_Detach( uint16_t devadr );
static void R_USB_HCDC_Suspend(uint16_t devadr);
static void R_USB_HCDC_Resume(uint16_t devadr);
/* Transfer callback functions */
static void R_USB_HCDC_ReadComplete( USB_UTR_t *utr );
static void R_USB_HCDC_WriteComplete( USB_UTR_t *utr );
static void R_USB_HCDC_ClassRequestComplete( USB_UTR_t *utr );
static void R_USB_HCDC_SerialStateTransComplete(USB_UTR_t *utr);
/* Event control functions */
static void R_USB_HCDC_EventSet( uint16_t devadr, uint16_t event );
static uint16_t R_USB_HCDC_EventGet( uint16_t devadr );

/***********************************************************************************************************************
 Renesas USB Host CDC Sample Code functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Initialization functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_Init
 *
 *  Description:    Host CDC Initialize.
 *
 *  Parameters:     None
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void R_USB_HCDC_Init( void )
{
    uint8_t     i,j;

    /* Initialize CDC Application status */
    for( i = 1; i <= USB_MAXDEVADDR ; i++ )
    {
        m_usb_hcdc_dev_info[i].state = STATE_WAIT_ATTACHMENT;
        m_usb_hcdc_dev_info[i].event_cnt = 0;
        for( j = 0; j < EVENT_MAX; j++ )
        {
            m_usb_hcdc_dev_info[i].event[j] = EVENT_HCDC_NONE;
        }
    }

    /* Host application registration */
    USB_HCDREG_t driver;

    /* Host CDCC class driver registration */
    driver.ifclass      = (uint16_t)USB_IFCLS_CDCC;         /* CDC Communications Interface */
    driver.tpl          = (uint16_t*)&m_usb_hcdc_device_tpl;  /* Target peripheral list */
    driver.classcheck   = &R_usb_hcdc_class_check;            /* Driver check */
    driver.devconfig    = &R_USB_HCDC_Configured;             /* Device configured */
    driver.devdetach    = &R_USB_HCDC_Detach;                 /* Device detach */
    driver.devsuspend   = &R_USB_HCDC_Suspend;                /* Device suspend */
    driver.devresume    = &R_USB_HCDC_Resume;                 /* Device resume */

    for( i = 0; i < MAX_DEVICE_NUM; i++ )
    {
        R_usb_hstd_DriverRegistration( &driver );
    }

    /* Init host class driver task. */
    R_usb_hcdc_driver_start();
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_InterfaceTask
 *
 *  Description:    Host CDC application main process
 *
 *  Parameters:     None
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
void R_USB_HCDC_InterfaceTask(void)
{
    uint16_t    ret_val;
    uint16_t    devadr;

    /* Loop support device num. */
    for( devadr = 1 ; devadr <= USB_MAXDEVADDR ; devadr++ )
    {
        /* Check application state */
        switch( m_usb_hcdc_dev_info[devadr].state )
        {
        case STATE_WAIT_ATTACHMENT:                  /* Wait Connect (USB Configured) state */
            ret_val = R_USB_HCDC_ConnectWait(devadr);
            break;
        case STATE_DATA_TRANSFER:           /* Data transfer state */
            ret_val = R_USB_HCDC_DataTransfer(devadr);
            break;
        case STATE_CLASS_REQUEST:           /* CDC Class request state */
            ret_val = R_USB_HCDC_ClassRequest(devadr);
            break;
        default:
            ret_val = USB_FALSE;
            break;
        }

        if( USB_FALSE == ret_val )
        {

        }
    }
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_InterfaceTask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_Write
 *
 *  Description:    Write data from host to a device
 *
 *  Parameters:     devadr - device address
 *                  data - messaged to be sent
 *                  length - count of bytes to be sent
 *
 *  Return Value:   Error status
 *
 **********************************************************************************************************************/
ER_RET R_USB_HCDC_Write(uint16_t devadr, const uint8_t * const data, size_t length)
{
#if USB_HCDC_CFG_PARAM_CHECKING_ENABLE
    if (CDC_DATA_LEN < length)
    {
        return ER_PARAM;
    }
#endif

    if (!IS_CDC_DEV_ADDR_VALID(devadr))
    {
        return ER_INVAL;
    }

    if (m_usb_hcdc_dev_info[devadr].is_write_busy)
    {
        return ER_BUSY;
    }

    memcpy((void *)m_usb_hcdc_dev_info[devadr].tx_data, (const void *)data, length);
    m_usb_hcdc_dev_info[devadr].tx_len = length;
    R_USB_HCDC_EventSet(devadr, EVENT_HCDC_WR_START);
    return ER_OK;
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_Write
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_RegisterCallback
 *
 *  Description:    Register callback to handle host events of CDC devices
 *
 *  Parameters:     hcdc_callback - callback to handle CDC host events
 *
 *  Return Value:   Error status
 *
 **********************************************************************************************************************/
ER_RET R_USB_HCDC_RegisterCallback(USB_HCDC_CB_t hcdc_callback)
{
    m_usb_hcdc_cb = hcdc_callback;
    return ER_OK;
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_RegisterCallback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_Control
 *
 *  Return Value:   Error status
 *
 *  Parameters:     dev_num - USB device to control
 *                  control_request - request to configure device or get device info.
 *                  buf - configuration data (to set or get).
 *
 *                  NOTE: API function checks that buf is non-zero.
 *                  The upper layer should check that the buffer lies within a valid address range.
 *
 *  Description:    Configure device parameters, set transfer parameters or
 *                  get device or transfer info, depending on control_request
 *
 **********************************************************************************************************************/
ER_RET R_USB_HCDC_Control(uint8_t devadr, USB_HCDC_CONTROL_REQUEST_t control_request, void *buf)
{
    ER_RET ret_val = ER_OK;
#if USB_HCDC_CFG_PARAM_CHECKING_ENABLE
    if (devadr > USB_MAXDEVADDR)
    {
        ret_val = ER_PARAM;
    }
#endif

    if ((USB_HCDC_CONTROL_SET_CALLBACK != control_request) && !IS_CDC_DEV_ADDR_VALID(devadr))
    {
        return ER_INVAL;
    }

    if (ER_OK == ret_val)
    {
        switch (control_request)
        {
            case USB_HCDC_CONTROL_SET_CALLBACK:
                m_usb_hcdc_cb = (USB_HCDC_CB_t)buf;
                break;

            case USB_HCDC_CONTROL_SET_CHAN_CONFIG:
                /* Set channel configuration parity, flow_control, stopbits, databits, baudrate */
                memcpy((void *)&m_usb_hcdc_dev_info[devadr].com_parm, (const void *)buf, sizeof(USB_HCDC_LineCoding_t));

                m_usb_hcdc_dev_info[devadr].state = STATE_CLASS_REQUEST;                            /* Set Application status  */
                m_usb_hcdc_dev_info[devadr].cr_seq = CLASS_REQUEST_SET_LINE_CODING_SEQ_ID;
                R_USB_HCDC_EventSet( devadr, EVENT_HCDC_CLASS_REQUEST_START );                     /* Set Event(CDC class request start) */
                break;

            case USB_HCDC_CONTROL_GET_CHAN_CONFIG:
                memcpy((void *)buf, (const void *)&m_usb_hcdc_dev_info[devadr].com_parm, sizeof(USB_HCDC_LineCoding_t));
                break;

            case USB_HCDC_CONTROL_SEND_BREAK:
                m_usb_hcdc_dev_info[devadr].break_period_ms = (uint16_t)((uint32_t)buf);
                m_usb_hcdc_dev_info[devadr].state = STATE_CLASS_REQUEST;                            /* Set Application status  */
                m_usb_hcdc_dev_info[devadr].cr_seq = CLASS_REQUEST_SEND_BREAK_SEQ_ID;
                R_USB_HCDC_EventSet( devadr, EVENT_HCDC_CLASS_REQUEST_START );                      /* Set Event(CDC class request start) */
                break;

            default:
                ret_val = ER_PARAM;
                break;
        }
    }

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_Control
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Local functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_ConnectWait
 *
 *  Description:    CDC device connect process.
 *
 *  Parameters:     None
 *
 *  Return Value:   USB_TRUE / USB_FALSE
 *
 **********************************************************************************************************************/
static uint16_t R_USB_HCDC_ConnectWait( uint16_t devadr )
{
    uint16_t    event;

    event = R_USB_HCDC_EventGet(devadr);
    if( EVENT_HCDC_CONFIGURED == event )
    {
        /* Set pipe */
        m_usb_hcdc_dev_info[devadr].in_pipe     = R_usb_hstd_GetPipeID(devadr, USB_EP_BULK, USB_EP_IN , 1);
        m_usb_hcdc_dev_info[devadr].out_pipe    = R_usb_hstd_GetPipeID(devadr, USB_EP_BULK, USB_EP_OUT, 1);
        m_usb_hcdc_dev_info[devadr].status_pipe = R_usb_hstd_GetPipeID(devadr, USB_EP_INT , USB_EP_IN , 0);
        /* Set Application variables */
        m_usb_hcdc_dev_info[devadr].com_parm.dwDTERate   = INIT_COM_SPEED;
        m_usb_hcdc_dev_info[devadr].com_parm.bDataBits   = INIT_COM_DATA_BIT;
        m_usb_hcdc_dev_info[devadr].com_parm.bCharFormat = INIT_COM_STOP_BIT;
        m_usb_hcdc_dev_info[devadr].com_parm.bParityType = INIT_COM_PARITY;
        m_usb_hcdc_dev_info[devadr].state = STATE_CLASS_REQUEST;                       /* Set Application status  */
        R_USB_HCDC_EventSet( devadr, EVENT_HCDC_CLASS_REQUEST_START );                     /* Set Event(CDC class request start) */
        m_usb_hcdc_dev_info[devadr].cr_seq = CLASS_REQUEST_SET_CONTROL_LINE_STATE_SEQ_ID;

        m_usb_hcdc_dev_info[devadr].tx_len = 0;
        m_usb_hcdc_dev_info[devadr].rx_len = 0;

        if (FIT_NO_PTR != m_usb_hcdc_cb)
        {
            const USB_HCDC_Strings_t * strings = R_usb_hcdc_get_strings();
            m_usb_hcdc_cb(devadr, EVENT_HCDC_CONFIGURED, (const uint8_t *)strings, sizeof(USB_HCDC_Strings_t));
        }
    }

    return USB_TRUE;
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_ConnectWait
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_ClassRequest
 *
 *  Description:    CDC Class request processing
 *
 *  Parameters:     None
 *
 *  Return Value:   USB_TRUE / USB_FALSE
 *
 **********************************************************************************************************************/
static uint16_t R_USB_HCDC_ClassRequest( uint16_t devadr )
{
    USB_ER_t    err = USB_TRUE;
    uint16_t    event;

    event = R_USB_HCDC_EventGet(devadr);
    switch( event )
    {
        case EVENT_HCDC_CLASS_REQUEST_START:
            /* Send request (SetControlLineState) */
            if( CLASS_REQUEST_SET_CONTROL_LINE_STATE_SEQ_ID == m_usb_hcdc_dev_info[devadr].cr_seq )
            {   /* Set control line state DTR-ON RTS-ON */
                err = R_usb_hcdc_set_control_line_state( devadr, USB_TRUE, USB_TRUE, &R_USB_HCDC_ClassRequestComplete );
            }
            /* Send request (SetLineCoding) */
            else if(CLASS_REQUEST_SET_LINE_CODING_SEQ_ID == m_usb_hcdc_dev_info[devadr].cr_seq )
            {
                err = R_usb_hcdc_set_line_coding( devadr, &m_usb_hcdc_dev_info[devadr].com_parm, &R_USB_HCDC_ClassRequestComplete );
            }
            /* Send request (GetLineCoding) */
            else if( CLASS_REQUEST_GET_LINE_CODING_SEQ_ID == m_usb_hcdc_dev_info[devadr].cr_seq )
            {
                err = R_usb_hcdc_get_line_coding( devadr, &m_usb_hcdc_dev_info[devadr].com_parm, &R_USB_HCDC_ClassRequestComplete );
            }
            /* Send request (SendBreak) */
            else if( CLASS_REQUEST_SEND_BREAK_SEQ_ID == m_usb_hcdc_dev_info[devadr].cr_seq )
            {
                err = R_usb_hcdc_send_break( devadr, m_usb_hcdc_dev_info[devadr].break_period_ms, &R_USB_HCDC_ClassRequestComplete );
            }

            break;

        case EVENT_HCDC_CLASS_REQUEST_COMPLETE:
             /* Check request (SetControlLineState) */
            if( CLASS_REQUEST_SET_CONTROL_LINE_STATE_SEQ_ID == m_usb_hcdc_dev_info[devadr].cr_seq )
            {
                R_USB_HCDC_EventSet( devadr, EVENT_HCDC_CLASS_REQUEST_START );
                /* Next ClassRequest */
                m_usb_hcdc_dev_info[devadr].cr_seq = CLASS_REQUEST_SET_LINE_CODING_SEQ_ID;
            }
            /* Check request (SetLineCoding) */
            else if( CLASS_REQUEST_SET_LINE_CODING_SEQ_ID == m_usb_hcdc_dev_info[devadr].cr_seq )
            {
                R_USB_HCDC_EventSet( devadr, EVENT_HCDC_CLASS_REQUEST_START );
                /* Next ClassRequest */
                m_usb_hcdc_dev_info[devadr].cr_seq = CLASS_REQUEST_GET_LINE_CODING_SEQ_ID;
            }
            /* Check request (GetLineCoding) */
            else if ( CLASS_REQUEST_GET_LINE_CODING_SEQ_ID == m_usb_hcdc_dev_info[devadr].cr_seq )
            {
                R_USB_HCDC_EventSet( devadr, EVENT_HCDC_RD_START );
                R_USB_HCDC_EventSet( devadr, EVENT_HCDC_COM_NOTIFY_RD_START );
                m_usb_hcdc_dev_info[devadr].state = STATE_DATA_TRANSFER;
                /* End ClassRequest */
                m_usb_hcdc_dev_info[devadr].cr_seq = CLASS_REQUEST_SET_CONTROL_LINE_STATE_SEQ_ID;
            }
            /* Send request (SendBreak) */
            else if ( CLASS_REQUEST_SEND_BREAK_SEQ_ID == m_usb_hcdc_dev_info[devadr].cr_seq )
            {
                m_usb_hcdc_dev_info[devadr].state = STATE_DATA_TRANSFER;
                /* End ClassRequest */
                m_usb_hcdc_dev_info[devadr].cr_seq = CLASS_REQUEST_SET_CONTROL_LINE_STATE_SEQ_ID;
            }
            break;

        default:
            break;
    }

    return err;
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_ClassRequest
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_DataTransfer
 *
 *  Description:    USB receive state process
 *
 *  Parameters:     None
 *
 *  Return Value:   USB_TRUE / USB_FALSE
 *
 **********************************************************************************************************************/
static uint16_t R_USB_HCDC_DataTransfer( uint16_t devadr )
{
    USB_ER_t    err = USB_TRUE;
    uint16_t    event;

    event = R_USB_HCDC_EventGet(devadr);
    switch( event )
    {
        case EVENT_HCDC_RD_START:              /* CDC Rx Transfer(Bulk IN) */
            err = R_usb_hcdc_receive_data( m_usb_hcdc_dev_info[devadr].in_pipe,
                    m_usb_hcdc_dev_info[devadr].rx_data, CDC_DATA_LEN, &R_USB_HCDC_ReadComplete );
            break;

        case EVENT_HCDC_RD_COMPLETE:
            if (m_usb_hcdc_dev_info[devadr].rx_len)
            {
                if (FIT_NO_PTR != m_usb_hcdc_cb)
                {
                    m_usb_hcdc_cb(devadr, EVENT_HCDC_RD_COMPLETE, m_usb_hcdc_dev_info[devadr].rx_data, m_usb_hcdc_dev_info[devadr].rx_len);
                }
            }
            R_USB_HCDC_EventSet( devadr, EVENT_HCDC_RD_START );

            break;

        case EVENT_HCDC_WR_START:             /* CDC Tx Transfer(Bulk OUT) */
            err = R_usb_hcdc_send_data( m_usb_hcdc_dev_info[devadr].out_pipe,
                    m_usb_hcdc_dev_info[devadr].tx_data, m_usb_hcdc_dev_info[devadr].tx_len, &R_USB_HCDC_WriteComplete);

            m_usb_hcdc_dev_info[devadr].is_write_busy = true;
            break;

        case EVENT_HCDC_WR_COMPLETE:
            if (FIT_NO_PTR != m_usb_hcdc_cb)
            {
                m_usb_hcdc_cb(devadr, EVENT_HCDC_WR_COMPLETE, m_usb_hcdc_dev_info[devadr].tx_data, m_usb_hcdc_dev_info[devadr].tx_len);
                m_usb_hcdc_dev_info[devadr].is_write_busy = false;
            }
            break;

        case EVENT_HCDC_COM_NOTIFY_RD_START:         /* Common Read(INT IN) */
            err = R_usb_hcdc_serial_state_trans( m_usb_hcdc_dev_info[devadr].status_pipe,
                    m_usb_hcdc_dev_info[devadr].serial_state_data, &R_USB_HCDC_SerialStateTransComplete );
            break;

        case EVENT_HCDC_COM_NOTIFY_RD_COMPLETE:
            if (FIT_NO_PTR != m_usb_hcdc_cb)
            {
                m_usb_hcdc_cb(devadr, EVENT_HCDC_COM_NOTIFY_RD_COMPLETE, m_usb_hcdc_dev_info[devadr].serial_state_data, USB_HCDC_SERIAL_STATE_MSG_LEN);
            }

            R_USB_HCDC_EventSet( devadr, EVENT_HCDC_COM_NOTIFY_RD_START );
            break;

        case EVENT_HCDC_NONE:
          /* Do nothing*/
          break;

        default:
            break;
    }

    return err;
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_DataTransfer
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Callback functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_Configured
 *
 *  Description:    Callback function for CDC device configured
 *
 *  Parameters:     uint16_t  devadr  : Device Address
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
static void R_USB_HCDC_Configured(uint16_t devadr)
{
    R_USB_HCDC_EventSet( devadr, EVENT_HCDC_CONFIGURED );
    m_usb_hcdc_dev_info[devadr].is_write_busy = false;
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_Configured
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_Detach
 *
 *  Description:    Callback function for CDC device detach
 *
 *  Parameters:     uint16_t  devadr  : Device Address
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
static void R_USB_HCDC_Detach(uint16_t devadr)
{
    R_usb_hstd_TransferEnd(m_usb_hcdc_dev_info[devadr].in_pipe);
    R_usb_hstd_TransferEnd(m_usb_hcdc_dev_info[devadr].out_pipe);
    R_usb_hstd_TransferEnd(m_usb_hcdc_dev_info[devadr].status_pipe);
    R_usb_hstd_ClearPipe(devadr);

    /* Clear out state as otherwise the stale contents may be picked up when iterating through the array */
    memset((void *)&m_usb_hcdc_dev_info[devadr], 0, sizeof(DEV_INFO_t));
    /* Explicitly set the new state */
    m_usb_hcdc_dev_info[devadr].state = STATE_WAIT_ATTACHMENT;

    if (FIT_NO_PTR != m_usb_hcdc_cb)
    {
        m_usb_hcdc_cb(devadr, EVENT_HCDC_DETACH, FIT_NO_PTR, 0);
    }
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_Detach
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_Suspend
 *
 *  Description:    suspend
 *
 *  Parameters:     uint16_t devadr          : Device Address
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
static void R_USB_HCDC_Suspend(uint16_t devadr)
{
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_Suspend
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_Resume
 *
 *  Description:    resume
 *
 *  Parameters:     uint16_t devadr          : Device Address
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
 static void R_USB_HCDC_Resume(uint16_t devadr)
{
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_Resume
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_ReadComplete
 *
 *  Description:    CallBack Function
 *
 *  Parameters:     USB_UTR_t *utr           : Transfer result message
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
static void R_USB_HCDC_ReadComplete(USB_UTR_t *utr)
{
    uint16_t devadr = USB_NODEVICE;
    uint16_t pipe_id;
    uint16_t i;

    pipe_id = utr->keyword;

    /* Pipe to Addr */
    for( i = 1; i <= USB_MAXDEVADDR ; i++ )   /* Loop max device num */
    {
        if( m_usb_hcdc_dev_info[i].in_pipe == pipe_id )  /* Check pipe no. */
        {
            devadr = i;                       /* Set device address */
            break;
        }
    }

    if (USB_NODEVICE != devadr)
    {
        /* Set Loop-back Size */
        if( USB_DATA_OK == utr->result )
        {
            m_usb_hcdc_dev_info[devadr].rx_len = CDC_DATA_LEN;
        }
        else if ( USB_DATA_SHT == utr->result )
        {
            m_usb_hcdc_dev_info[devadr].rx_len = CDC_DATA_LEN - utr->tranlen;
        }

        R_USB_HCDC_EventSet( devadr, EVENT_HCDC_RD_COMPLETE );
    }
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_ReadComplete
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_WriteComplete
 *
 *  Description:    CallBack Function
 *
 *  Parameters:     USB_UTR_t *utr           : Transfer result message
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
static void R_USB_HCDC_WriteComplete(USB_UTR_t *utr)
{
    uint16_t devadr = USB_NODEVICE;
    uint16_t pipe_id;
    uint16_t i;

    pipe_id = utr->keyword;

    /* Pipe to Addr */
    for( i = 1; i <= USB_MAXDEVADDR ; i++ )  /* Loop max device number */
    {
        if( m_usb_hcdc_dev_info[i].out_pipe == pipe_id )  /* Check pipe no. */
        {
            devadr = i;                       /* Set device address */
            break;
        }
    }

    if (USB_NODEVICE != devadr)
    {
        R_USB_HCDC_EventSet( devadr, EVENT_HCDC_WR_COMPLETE );
    }
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_WriteComplete
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_ClassRequestComplete
 *
 *  Description:    Class request transfer complete
 *
 *  Parameters:     USB_UTR_t *utr : Transfer result message
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
static void R_USB_HCDC_ClassRequestComplete(USB_UTR_t *utr)
{
    if( USB_CTRL_END == utr->result )
    {
        R_USB_HCDC_EventSet( utr->setup->devaddr, EVENT_HCDC_CLASS_REQUEST_COMPLETE );
    }
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_ClassRequestComplete
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_SerialStateTransComplete
 *
 *  Description:    Serial state receive complete call-back.
 *
 *  Parameters:     USB_UTR_t *utr : Transfer result message
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
static void R_USB_HCDC_SerialStateTransComplete(USB_UTR_t *utr)
{
    uint16_t devadr = USB_NODEVICE;
    uint16_t pipe_id;
    uint16_t i;

    pipe_id = utr->keyword;

    for( i = 1; i <= USB_MAXDEVADDR ; i++ )  /* Loop max device number */
    {
        if( m_usb_hcdc_dev_info[i].status_pipe == pipe_id )  /* Check pipe no. */
        {
            devadr = i;                       /* Set device address */
            break;
        }
    }

    if (USB_NODEVICE != devadr)
    {
        R_USB_HCDC_EventSet( devadr, EVENT_HCDC_COM_NOTIFY_RD_COMPLETE );
    }
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_SerialStateTransComplete
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Other functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_EventSet
 *
 *  Description:    Set event.
 *
 *  Parameters:     uint16_t  devadr : Device Address
                    uint16_t  event  : Event code
 *
 *  Return Value:   None
 *
 **********************************************************************************************************************/
static void R_USB_HCDC_EventSet( uint16_t devadr, uint16_t event )
{
    if( m_usb_hcdc_dev_info[devadr].event_cnt < EVENT_MAX )    /* Check max event count */
    {
        m_usb_hcdc_dev_info[devadr].event[m_usb_hcdc_dev_info[devadr].event_cnt] = event; /* Set event */
        m_usb_hcdc_dev_info[devadr].event_cnt++;               /* Update event count */
    }
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_EventSet
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function Name:  R_USB_HCDC_EventGet
 *
 *  Description:    Get event.
 *
 *  Parameters:     uint16_t  devadr : Device Address
 *
 *  Return Value:   Event Code
 *
 **********************************************************************************************************************/
static uint16_t R_USB_HCDC_EventGet( uint16_t devadr )
{
    uint16_t    event = EVENT_HCDC_NONE;
    uint8_t     i;

    if( m_usb_hcdc_dev_info[devadr].event_cnt > 0 )                    /* Check event count */
    {
        event = m_usb_hcdc_dev_info[devadr].event[0];                  /* Get event */
        for( i = 0; i < m_usb_hcdc_dev_info[devadr].event_cnt; i++ )   /* Shift event buffer */
        {
            m_usb_hcdc_dev_info[devadr].event[i] = m_usb_hcdc_dev_info[devadr].event[(i + 1)];
        }
        m_usb_hcdc_dev_info[devadr].event_cnt--;                       /* Update event count */
    }

    return event;
}
/***********************************************************************************************************************
 End of function R_USB_HCDC_EventGet
 **********************************************************************************************************************/
