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
 * $Revision: 1318 $
 * $Date: 2019-03-01 16:17:33 +0000 (Fri, 01 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hhub_rzn1_if.c
 * Description  :  USB Host HUB Interface File
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_usb_hhub_rzn1_if.h"
#include "r_usb_hHci.h"
#include <string.h>

/* Condition compilation by the difference of USB function */
/***********************************************************************************************************************
 Constant macro definitions
 **********************************************************************************************************************/
#define USB_MAXHUB              (uint16_t)5

#define USB_HUB_P1              (uint16_t)0x0001
#define USB_HUB_P2              (uint16_t)0x0002
#define USB_HUB_P3              (uint16_t)0x0003
#define USB_HUB_P4              (uint16_t)0x0004

/* HUB spec */
#define USB_FSHUB                        1u
#define USB_HSHUBS                       2u
#define USB_HSHUBM                       3u

/* Interface number */
#define USB_HUB_INTNUMFS                 1u
#define USB_HUB_INTNUMHSS                1u
#define USB_HUB_INTNUMHSM                1u

/* USB HUB task message command */
#define USB_MSG_HUB_EVENT                0x0135u
#define USB_MSG_HUB_ATTACH               0x0136u

#define USB_HHUB_ASCII_STR_MAX_SIZE      128

/***********************************************************************************************************************
 Typedef definitions
 **********************************************************************************************************************/
typedef struct USB_HUB_INFO
{
    uint16_t        up_addr;        /* Up-address  */
    uint16_t        up_port;        /* Up-port num */
    uint16_t        port_num;       /* Port number */
    uint16_t        pipe_id;        /* Pipe number */
    uint16_t        ClassSeq;       /* R_USB_HHUB_enumeration() Sequence */
    uint16_t        InitSeq;        /* R_USB_HHUB_InitDownPort() Sequence */
    uint16_t        InitPort;       /* R_USB_HHUB_InitDownPort() Process Port */
    uint16_t        EventSeq;       /* R_USB_HHUB_event() Sequence */
    uint16_t        EventPort;      /* R_USB_HHUB_event() Process Port */
    uint16_t        AttachSeq;      /* R_USB_HHUB_PortAttach() Sequence */
    uint16_t        AttachPort;     /* R_USB_HHUB_PortAttach() Process Port */
    uint16_t        Process;        /* R_USB_HHUB_Task() msginfo */
} USB_HUB_INFO_t;

typedef struct USB_HUB_STATUS
{
    union
    {
        uint16_t WORD;
        struct
        {
            uint16_t connection:1;
            uint16_t enable:1;
            uint16_t suspend:1;
            uint16_t over_current:1;
            uint16_t reset:1;
            uint16_t l1:1;
            uint16_t :2;
            uint16_t power:1;
            uint16_t low_speed:1;
            uint16_t high_speed:1;
            uint16_t test:1;
            uint16_t indicator_ctrl:1;
            uint16_t :3;
        } BIT;
    } status;
    union
    {
        uint16_t WORD;
        struct
        {
            uint16_t c_connection:1;
            uint16_t c_enable:1;
            uint16_t c_suspend:1;
            uint16_t c_over_current:1;
            uint16_t c_reset:1;
            uint16_t :11;
        } BIT;
    } change;
} USB_HUB_STATUS_t;

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Static variables and functions
 **********************************************************************************************************************/
static  void     R_USB_HHUB_Open(uint16_t hubaddr);
static  void     R_USB_HHUB_Close(uint16_t hubaddr);
static  void     R_USB_HHUB_Suspend(uint16_t hubaddr);
static  void     R_USB_HHUB_Resume(uint16_t hubaddr);
static  void     R_USB_HHUB_enumeration(USB_UTR_t *mess);
static  void     R_USB_HHUB_InitDownPort(USB_UTR_t *mess);
static  void     R_USB_HHUB_PortAttach(USB_UTR_t *mess);
static  void     R_USB_HHUB_event(USB_UTR_t *mess);
static  void     R_USB_HHUB_check_class(uint16_t **table);
static  void     R_USB_HHUB_trans_start(uint16_t hubaddr, uint32_t size, uint8_t *table, USB_UTR_CB_t complete);
static  uint16_t R_USB_HHUB_GetHubDescriptor(uint16_t hubaddr, USB_UTR_CB_t complete);
static  uint16_t R_USB_HHUB_GetStatus(uint16_t hubaddr, uint16_t port, USB_UTR_CB_t complete);
static  uint16_t R_USB_HHUB_PortSetFeature(uint16_t hubaddr, uint16_t port, uint16_t command, USB_UTR_CB_t complete);
static  uint16_t R_USB_HHUB_PortClrFeature(uint16_t hubaddr, uint16_t port, uint16_t command, USB_UTR_CB_t complete);
static  void     R_USB_HHUB_trans_complete(USB_UTR_t *utr);
static  void     R_USB_HHUB_class_request_product_id_complete(USB_UTR_t *utr);
static  void     R_USB_HHUB_class_request_complete(USB_UTR_t *utr);
static  void     R_USB_HHUB_new_connect(void);
static  uint16_t R_USB_HHUB_GetCnnDevaddr(uint16_t hubaddr, uint16_t portnum);
static  void     R_USB_HHUB_port_detach(uint16_t hubaddr, uint16_t portnum);
static  void     R_USB_HHUB_selective_detach(uint16_t devaddr);
static  void     R_USB_HHUB_SpecifiedPath(uint16_t result);
static  void     R_USB_HHUB_SpecifiedPathWait(uint16_t result, uint16_t times);

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
/* Control transfer message */
static USB_UTR_t        usb_shhub_ControlMess;
/* Control transfer setup */
static USB_SETUP_t      usb_shhub_ClassRequest;
/* Data transfer message */
static USB_UTR_t        usb_shhub_DataMess[USB_MAXDEVADDR + 1u];
/* HUB descriptor */
static uint8_t          usb_ghhub_Descriptor[USB_CONFIGSIZE];
/* HUB status data */
static USB_HUB_STATUS_t usb_ghhub_Status[USB_MAXDEVADDR + 1u];
/* HUB receive data */
static uint8_t          usb_ghhub_Data[USB_MAXDEVADDR + 1u];
/* HUB down-port status */
static uint16_t         usb_shhub_DownPort[USB_MAXDEVADDR + 1u];
/* Down-port remote wakeup */
static uint16_t         usb_shhub_Remote[USB_MAXDEVADDR + 1u];
/* HUB Information */
static USB_HUB_INFO_t   usb_shhub_Info[USB_MAXDEVADDR + 1u];
/* HUB Connection Number */
static uint16_t         usb_shhub_Number;
/* Processing HUB Address */
static uint16_t         usb_shhub_HubAddr;
/* Device Descriptor Pointer */
static uint8_t          *usb_shhub_DeviceTable;
/* Configuration Descriptor Pointer */
static uint8_t          *usb_shhub_ConfigTable;
/* Interface Descriptor Pointer */
static uint8_t          *usb_shhub_InterfaceTable;
/* Product Id String */
static uint8_t          usb_shhub_string_product_id[USB_HHUB_ASCII_STR_MAX_SIZE];

static USB_HHUB_CB_t    usb_shhub_cb = FIT_NO_PTR;

/* Target Peripheral List */
static const uint16_t usb_ghhub_TPL[4] =
{
    1,                      /* Number of list */
    0,                      /* Reserved */
    USB_NOVENDOR,           /* Vendor ID  : no-check */
    USB_NOPRODUCT,          /* Product ID : no-check */
};

/***********************************************************************************************************************
 Renesas Abstracted Hub Driver API functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_Task
 *
 *  Description:    Call HUB task
 *
 *  Parameters:     none
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void R_USB_HHUB_Task(void)
{
    USB_UTR_t       *mess;
    USB_ER_t        err;

    /* Receive message */
    err = USB_RCV_MSG(USB_HUB_MBX, (USB_MSG_t**)&mess);
    if( USB_OK != err )
    {
        return;
    }

    if( usb_shhub_Info[usb_shhub_HubAddr].Process != mess->msginfo )
    {
//        USB_PRINTF0("CE\n");
    }
    else
    {
        switch( mess->msginfo )
        {
        case USB_MSG_CLS_CHECKREQUEST:
            R_USB_HHUB_enumeration(mess);        /* USB HUB Class Enumeration */
//          USB_PRINTF2("enumeration, Addr:%d, Seq:%d\n", usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].ClassSeq);
            break;

        case USB_MSG_CLS_INIT:
            R_USB_HHUB_InitDownPort(mess);       /* Down port initialize */
//          USB_PRINTF2("InitDownPort, Addr:%d, Seq:%d\n", usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].InitSeq);
            break;

        case USB_MSG_HUB_EVENT:
            R_USB_HHUB_event(mess);
//          USB_PRINTF2("event, Addr:%d, Seq:%d\n", usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].EventSeq);
            break;

        case USB_MSG_HUB_ATTACH:
            R_USB_HHUB_PortAttach(mess);        /* Hub Port attach */
//          USB_PRINTF2("PortAttach, Addr:%d, Seq:%d\n", usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].AttachSeq);
            break;

        default:
            USB_PRINTF0("HUB_TASK [0]\n");
            break;
        }
    }
    err = USB_REL_BLK(USB_HUB_MPL, mess);
    if( USB_OK != err )
    {
        USB_PRINTF0("### USB HUB Task rel_blk error\n");
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_Task
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_Registration
 *
 *  Description:    HUB driver
 *
 *  Parameters:     USB_HCDREG_t *callback
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void R_USB_HHUB_Registration(USB_HCDREG_t *callback)
{
    uint8_t i;
    USB_HCDREG_t    driver;

    /* Driver registration */
    if( USB_NULL == callback )
    {
        /* Target peripheral list */
        driver.tpl      = (uint16_t*)&usb_ghhub_TPL[0];
    }
    else
    {
        /* Target peripheral list */
        driver.tpl      = callback->tpl;
    }
    /* Interface Class */
    driver.ifclass      = (uint16_t)USB_IFCLS_HUB;
    /* Driver check */
    driver.classcheck   = &R_USB_HHUB_check_class;
    /* Device configured */
    driver.devconfig    = &R_USB_HHUB_Open;
    /* Device detach */
    driver.devdetach    = &R_USB_HHUB_Close;
    /* Device suspend */
    driver.devsuspend   = &R_USB_HHUB_Suspend;
    /* Device resume */
    driver.devresume    = &R_USB_HHUB_Resume;

    for( i = 0; i < USB_MAXHUB; i++ )
    {
        R_usb_hstd_DriverRegistration((USB_HCDREG_t *)&driver);
    }

    for( i = 0u; i < (USB_MAXDEVADDR + 1u); i++ )
    {
        usb_shhub_Info[i].up_addr = 0;
        usb_shhub_Info[i].up_port = 0;
        usb_shhub_Info[i].port_num = 0;
        usb_shhub_Info[i].pipe_id = 0;
        usb_shhub_Info[i].InitSeq = USB_SEQ_0;
        usb_shhub_Info[i].InitPort = USB_HUB_P1;
        usb_shhub_Info[i].AttachSeq = USB_SEQ_0;
        usb_shhub_Info[i].AttachPort = USB_HUB_P1;
        usb_shhub_Info[i].EventSeq = USB_SEQ_0;
        usb_shhub_Info[i].EventPort = USB_HUB_P1;
    }
    usb_shhub_Number = 0;
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_Registration
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_RegisterCallback
 *
 *  Description:    Register callback to handle events for (non-root) Hubs
 *
 *  Parameters:     usb_hhub_cb - callback to handle host Hub events
 *
 *  Return value:   Error status
 *
 **********************************************************************************************************************/
ER_RET R_USB_HHUB_RegisterCallback(USB_HHUB_CB_t usb_hhub_cb)
{
    usb_shhub_cb = usb_hhub_cb;
    return ER_OK;
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_RegisterCallback
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_GetProductIdStr
 *
 *  Description:    Get the Product ID
 *                  Note: This function can only be assumed to return the correct data immediately after hub enumeration
 *
 *  Parameters:     None
 *
 *  Return value:   const char *  : The Hub Product ID or NULL
 *
 **********************************************************************************************************************/
static const char * R_USB_HHUB_GetProductIdStr(void)
{
    return (const char *)usb_shhub_string_product_id;
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_GetProductIdStr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_Open
 *
 *  Description:    HUB sys open
 *
 *  Parameters:     uint16_t hubaddr          : hub address
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_Open(uint16_t hubaddr)
{
    if( USB_MAXHUB != usb_shhub_Number )
    {
        /* Pipe number set */
        usb_shhub_Info[hubaddr].pipe_id = R_usb_hstd_GetPipeID(hubaddr, USB_EP_INT, USB_EP_IN, 0);
        /* HUB down-port status */
        usb_shhub_DownPort[hubaddr] = 0;
        /* Down-port remote wakeup */
        usb_shhub_Remote[hubaddr]   = 0;

        usb_shhub_Info[hubaddr].Process = USB_MSG_CLS_INIT;
        R_USB_HHUB_SpecifiedPath(USB_CTRL_END);
        usb_shhub_HubAddr = hubaddr;

        usb_shhub_Number++;

        if (FIT_NO_PTR != usb_shhub_cb)
        {
            const uint8_t * product_id = (const uint8_t *)R_USB_HHUB_GetProductIdStr();
            usb_shhub_cb(hubaddr, EVENT_HHUB_CONFIGURED, product_id, strlen((char const *)product_id));
        }
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_Close
 *
 *  Description:    HUB sys close
 *
 *  Parameters:     uint16_t hubaddr          : hub address
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_Close(uint16_t hubaddr)
{
    uint16_t        md, i;
    USB_HCDREG_t    *driver;
    uint16_t        devaddr;

    for( i = 1; i <= usb_shhub_Info[hubaddr].port_num; i++ )
    {
        /* Now down-port device search */
        devaddr = R_USB_HHUB_GetCnnDevaddr(hubaddr, i);
        if( 0 != devaddr )
        {
            /* HUB down port selective disconnect */
            R_USB_HHUB_selective_detach(devaddr);
            for( md = 0; md < usb_ghstd_DeviceNum; md++ )
            {
                driver = &usb_ghstd_DeviceDrv[md];
                if( devaddr == driver->devaddr )
                {
                    (*driver->devdetach)(driver->devaddr);
                    /* Root port */
                    driver->rootport    = USB_NOPORT;
                    /* Device devaddress */
                    driver->devaddr     = USB_NODEVICE;
                    /* Device state */
                    driver->devstate    = USB_DETACHED;
                }
            }
        }
    }

    usb_shhub_Number--;

    if( usb_shhub_Info[hubaddr].pipe_id != 0 )
    {
        R_usb_hstd_TransferEnd(usb_shhub_Info[hubaddr].pipe_id);
        R_usb_hstd_ClearPipe(hubaddr);
    }

    usb_shhub_Info[hubaddr].ClassSeq = USB_SEQ_0;
    usb_shhub_Info[hubaddr].InitSeq = USB_SEQ_0;
    usb_shhub_Info[hubaddr].InitPort = USB_HUB_P1;
    usb_shhub_Info[hubaddr].AttachSeq = USB_SEQ_0;
    usb_shhub_Info[hubaddr].AttachPort = USB_HUB_P1;
    usb_shhub_Info[hubaddr].EventSeq = USB_SEQ_0;
    usb_shhub_Info[hubaddr].EventPort = USB_HUB_P1;
    usb_shhub_Info[hubaddr].Process = USB_SEQ_0;

    usb_shhub_DownPort[hubaddr]    = 0;
    usb_shhub_Remote[hubaddr]      = 0;

    if (FIT_NO_PTR != usb_shhub_cb)
    {
        usb_shhub_cb(hubaddr, EVENT_HHUB_DETACH, FIT_NO_PTR, 0);
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_Suspend
 *
 *  Description:    HUB sys suspend
 *
 *  Parameters:     uint16_t hubaddr          : hub address
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_Suspend(uint16_t hubaddr)
{
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_Suspend
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_Resume
 *
 *  Description:    HUB sys resume
 *
 *  Parameters:     uint16_t hubaddr          : hub address
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void R_USB_HHUB_Resume(uint16_t hubaddr)
{
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_Resume
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_enumeration
 *
 *  Description:    USB HUB Class Enumeration
 *
 *  Parameters:     USB_UTR_t *mess    : USB system internal message.
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_enumeration(USB_UTR_t *mess)
{
    uint16_t    checkerr;

    /* Manager Mode Change */
    switch( usb_shhub_Info[usb_shhub_HubAddr].ClassSeq )
    {
    case USB_SEQ_0:
        /* String descriptor (LANGID codes requested) */
        usb_hstd_GetStringDesc(usb_shhub_HubAddr, 0, R_USB_HHUB_class_request_complete);
        break;

    case USB_SEQ_1:
        /* Get Production ID string */
        if( USB_CTRL_END == mess->result )
        {
            /* Set LanguageID */
            usb_hstd_SetLangId();

            /* Get Product ID String */
            usb_hstd_GetStringDesc(usb_shhub_HubAddr, (uint16_t)usb_shhub_DeviceTable[USB_DEV_I_PRODUCT], R_USB_HHUB_class_request_product_id_complete);
        }
        else
        {
            /* Next sequence */
            R_USB_HHUB_SpecifiedPath(USB_CTRL_END);
        }
        break;

    case USB_SEQ_2:
        /* Get HUB descriptor */
        R_USB_HHUB_GetHubDescriptor( usb_shhub_HubAddr, R_USB_HHUB_class_request_complete );
        break;

    case USB_SEQ_3:
        /* Get HUB descriptor Check */
        if( USB_CTRL_END == mess->result )
        {
            if( usb_ghhub_Descriptor[2] > USB_HUBDOWNPORT )
            {
                USB_PRINTF0("### HUB Port number over\n");
                checkerr = USB_ERROR;
            }
            else
            {
                USB_PRINTF1("    Attached %d port HUB\n", usb_ghhub_Descriptor[2]);
                checkerr = USB_OK;
            }
        }
        else
        {
            USB_PRINTF0("### HUB Descriptor over\n");
            checkerr = USB_ERROR;
        }

        /* Port number set */
        usb_shhub_Info[usb_shhub_HubAddr].port_num = usb_ghhub_Descriptor[2];
        /* Return to MGR */
        R_usb_hstd_ReturnEnuMGR(checkerr);

        R_USB_HHUB_SpecifiedPath(USB_CTRL_END);
        break;

    case USB_SEQ_4:
        if( USB_CONFIGURED == usb_ghstd_MgrMode[usb_hstd_GetRootport(usb_shhub_HubAddr)] )
        {
            /* Enumeration End */
            usb_shhub_Info[usb_shhub_HubAddr].ClassSeq = USB_SEQ_0;
            usb_shhub_Info[usb_shhub_HubAddr].Process = USB_SEQ_0;
        }
        else if( USB_DEFAULT == usb_ghstd_MgrMode[usb_hstd_GetRootport(usb_shhub_HubAddr)] )
        {
            usb_shhub_Info[usb_shhub_HubAddr].ClassSeq = USB_SEQ_3;  /* Loop Sequencer */
            R_USB_HHUB_SpecifiedPathWait(mess->result, 20u);
        }
        else
        {
            /* Resume up-HUB Sequence */
            if( usb_shhub_Info[usb_shhub_HubAddr].up_addr != 0 )
            {
                usb_shhub_HubAddr = usb_shhub_Info[usb_shhub_HubAddr].up_addr;
                R_USB_HHUB_SpecifiedPath(USB_CTRL_END);
            }
            else
            {
                usb_shhub_Info[usb_shhub_HubAddr].Process = USB_SEQ_0;
            }
        }
        break;
    }

    usb_shhub_Info[usb_shhub_HubAddr].ClassSeq++;
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_enumeration
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_InitDownPort
 *
 *  Description:    Down port initialized
 *
 *  Parameters:     USB_UTR_t *mess
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_InitDownPort(USB_UTR_t *mess)
{
    if( USB_CTRL_END != mess->result )
    {
        USB_PRINTF2("InitDownPort result ERROR, Addr:%d, Seq:%d\n", usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].InitSeq);
        usb_shhub_Info[usb_shhub_HubAddr].InitSeq = USB_SEQ_6;
    }

    switch( usb_shhub_Info[usb_shhub_HubAddr].InitSeq )
    {
    case USB_SEQ_0:  /* Send SetFeature */
         R_USB_HHUB_PortSetFeature( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].InitPort,
            (uint16_t)USB_HUB_PORT_POWER, R_USB_HHUB_class_request_complete);    /* SetFeature request */
        usb_shhub_Info[usb_shhub_HubAddr].InitSeq = USB_SEQ_1;         /* Next Sequence */
        break;

    case USB_SEQ_1:  /* Check */
        if( usb_shhub_Info[usb_shhub_HubAddr].InitPort >= usb_shhub_Info[usb_shhub_HubAddr].port_num )
        {
            usb_shhub_Info[usb_shhub_HubAddr].InitPort = USB_HUB_P1;   /* Port Clear */
            usb_shhub_Info[usb_shhub_HubAddr].InitSeq = USB_SEQ_2;     /* Next Sequence */
        }
        else
        {
            usb_shhub_Info[usb_shhub_HubAddr].InitPort++;              /* Next Port */
            usb_shhub_Info[usb_shhub_HubAddr].InitSeq = USB_SEQ_0;     /* Loop Sequence */
        }
        R_USB_HHUB_SpecifiedPath(mess->result);               /* Next Process Selector */
        break;

    case USB_SEQ_2:  /* Send ClearFeasture */
        R_USB_HHUB_PortClrFeature( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].InitPort,
            (uint16_t)USB_HUB_C_PORT_CONNECTION, R_USB_HHUB_class_request_complete);      /* Request */
        usb_shhub_Info[usb_shhub_HubAddr].InitSeq = USB_SEQ_3;         /* Next Sequence */
        break;

    case USB_SEQ_3:  /* Check */
        if( usb_shhub_Info[usb_shhub_HubAddr].InitPort >= usb_shhub_Info[usb_shhub_HubAddr].port_num )
        {
            usb_shhub_Info[usb_shhub_HubAddr].InitPort = USB_HUB_P1;    /* Port Clear */
            usb_shhub_Info[usb_shhub_HubAddr].InitSeq = USB_SEQ_4;      /* Next Sequence */
        }
        else
        {
            usb_shhub_Info[usb_shhub_HubAddr].InitPort++;               /* Next Port */
            usb_shhub_Info[usb_shhub_HubAddr].InitSeq = USB_SEQ_2;      /* Loop Sequence */
        }
        R_USB_HHUB_SpecifiedPath(mess->result);                       /* Next Process Selector */
        break;

    case USB_SEQ_4:  /* Send GetStatus */
        R_USB_HHUB_GetStatus( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].InitPort,
                                                    R_USB_HHUB_class_request_complete);
        usb_shhub_Info[usb_shhub_HubAddr].InitSeq = USB_SEQ_5;
        break;

    case USB_SEQ_5:  /* Check PORT_CONNECTION */
        USB_PRINTF2(" *** address %d downport %d \t", usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].InitPort);
        USB_PRINTF1(" [status] : 0x%04x\t", usb_ghhub_Status[usb_shhub_HubAddr].status.WORD);
        USB_PRINTF1(" [change] : 0x%04x\n", usb_ghhub_Status[usb_shhub_HubAddr].change.WORD);

        if( usb_ghhub_Status[usb_shhub_HubAddr].status.BIT.connection )
        {
            /* Wait Power stabilization */
            R_usb_cstd_DelayXms((uint16_t)100);
            usb_shhub_Info[usb_shhub_HubAddr].AttachPort = usb_shhub_Info[usb_shhub_HubAddr].InitPort;
            R_USB_HHUB_new_connect(); /* Go to Attach Sequence */
        }
        else
        {
            R_USB_HHUB_SpecifiedPath(mess->result);
        }
        usb_shhub_Info[usb_shhub_HubAddr].InitSeq = USB_SEQ_6;                        /* Next Attach sequence */
        break;

    case USB_SEQ_6:  /*  */
        if( usb_shhub_Info[usb_shhub_HubAddr].InitPort >= usb_shhub_Info[usb_shhub_HubAddr].port_num )
        {   /* Port check end */
            usb_shhub_Info[usb_shhub_HubAddr].InitPort = USB_HUB_P1;    /* Port Clear */
            usb_shhub_Info[usb_shhub_HubAddr].InitSeq = USB_SEQ_0;      /* Sequence Clear */
            R_USB_HHUB_trans_start(usb_shhub_HubAddr, (uint32_t)1, (uint8_t*)&usb_ghhub_Data[usb_shhub_HubAddr], &R_USB_HHUB_trans_complete);
            /* Resume up-HUB Sequence */
            if( usb_shhub_Info[usb_shhub_HubAddr].up_addr != 0 )
            {
                usb_shhub_HubAddr = usb_shhub_Info[usb_shhub_HubAddr].up_addr;
                R_USB_HHUB_SpecifiedPath(mess->result);
            }
            else
            {
                usb_shhub_Info[usb_shhub_HubAddr].Process = USB_SEQ_0;
            }
        }
        else
        {
            usb_shhub_Info[usb_shhub_HubAddr].InitPort++;               /* Next port check */
            usb_shhub_Info[usb_shhub_HubAddr].InitSeq = USB_SEQ_4;      /* Loop Sequence */
            R_USB_HHUB_SpecifiedPath(mess->result);
        }
        break;

    default:
        break;
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_InitDownPort
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_PortAttach
 *
 *  Description:    port attach
 *
 *  Parameters:     USB_UTR_t *mess
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_PortAttach(USB_UTR_t *mess)
{
    uint16_t        rootport;
    uint16_t        speed;

    if( USB_CTRL_END != mess->result )
    {
        USB_PRINTF2("PortAttach result ERROR, Addr:%d, Seq:%d\n", usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].AttachSeq);
        R_USB_HHUB_port_detach(usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].AttachPort);
        usb_shhub_Info[usb_shhub_HubAddr].AttachSeq = USB_SEQ_0;
        /* Return Process */
        if( usb_shhub_Info[usb_shhub_HubAddr].InitSeq == USB_SEQ_0 )
        {
            usb_shhub_Info[usb_shhub_HubAddr].Process = USB_MSG_HUB_EVENT;
        }
        else
        {
            usb_shhub_Info[usb_shhub_HubAddr].Process = USB_MSG_CLS_INIT;
        }
        R_USB_HHUB_SpecifiedPath(USB_CTRL_END);
        return;
    }

    switch( usb_shhub_Info[usb_shhub_HubAddr].AttachSeq )
    {
    case USB_SEQ_0:  /* Hub port SetFeature(RESET) */
        R_USB_HHUB_PortSetFeature( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].AttachPort, (uint16_t)USB_HUB_PORT_RESET,
                                          R_USB_HHUB_class_request_complete);
        usb_shhub_Info[usb_shhub_HubAddr].AttachSeq = USB_SEQ_1;
        break;

    case USB_SEQ_1:  /* GetStatus */
        /* Keep Reset */
        R_usb_cstd_DelayXms((uint16_t)20);
        /* Send GetStatus */
        R_USB_HHUB_GetStatus( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].AttachPort, R_USB_HHUB_class_request_complete );
        usb_shhub_Info[usb_shhub_HubAddr].AttachSeq = USB_SEQ_2;
        break;

    case USB_SEQ_2:  /* Check Reset Change */
        /* Check Reset Change(C_PORT_RESET) */
        if( usb_ghhub_Status[usb_shhub_HubAddr].change.BIT.c_reset )
        {
            /* Hub port ClearFeature */
            R_USB_HHUB_PortClrFeature( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].AttachPort, (uint16_t)USB_HUB_C_PORT_RESET,
                                              R_USB_HHUB_class_request_complete );
            usb_shhub_Info[usb_shhub_HubAddr].AttachSeq = USB_SEQ_3;
        }
        else
        {
            if( usb_ghhub_Status[usb_shhub_HubAddr].status.BIT.connection == 0 )
            {
                /* Already Disconnect */
                USB_PRINTF0("Reset Error\n");
                usb_shhub_Info[usb_shhub_HubAddr].AttachSeq = USB_SEQ_4;
            }
            else
            {
                /* Retry */
                usb_shhub_Info[usb_shhub_HubAddr].AttachSeq = USB_SEQ_0;
            }
            R_USB_HHUB_SpecifiedPath(mess->result);
        }
        break;

    case USB_SEQ_3:  /* Device Enumeration */
        /* Now down-port device search */
        usb_ghstd_DeviceAddr = R_USB_HHUB_GetCnnDevaddr(usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].AttachPort);

        /* Set HUB port information to HCI */
        if( usb_ghhub_Status[usb_shhub_HubAddr].status.BIT.high_speed )
        {
            usb_ghstd_DeviceSpeed = USB_HSCONNECT;
            USB_PRINTF0(" Hi-Speed Device\n");
            r_usb_hstd_HciSetHubInfo( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].AttachPort, usb_ghstd_DeviceAddr, USB_HCI_DEVSPEED_HS );
        }
        else if( usb_ghhub_Status[usb_shhub_HubAddr].status.BIT.low_speed )
        {
            usb_ghstd_DeviceSpeed = USB_LSCONNECT;
            USB_PRINTF0(" Low-Speed Device\n");
            speed = r_usb_hstd_HciGetDeviceSpeed(USB_DEVICEADDR);
            if( speed == USB_HCI_DEVSPEED_HS )
            {
                r_usb_hstd_HciSetHubInfo( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].AttachPort, usb_ghstd_DeviceAddr, USB_HCI_DEVSPEED_LS );
            }
            else
            {
                USB_PRINTF0(" Not Supported\n");
                R_USB_HHUB_SpecifiedPath(USB_ERROR);
                return;
            }
        }
        else
        {
            usb_ghstd_DeviceSpeed = USB_FSCONNECT;
            USB_PRINTF0(" Full-Speed Device\n");
            r_usb_hstd_HciSetHubInfo( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].AttachPort, usb_ghstd_DeviceAddr, USB_HCI_DEVSPEED_FS );
        }

        rootport = usb_hstd_GetRootport(usb_shhub_HubAddr);
        usb_ghstd_MgrMode[rootport] = USB_DEFAULT;

        /* Set Device address of the HUB port to HCI */
        r_usb_hstd_HciSetDeviceAddressOfHubport(usb_shhub_HubAddr, usb_ghstd_DeviceAddr);
        /* Start Enumeration */
        usb_hstd_EnumGetDescriptor((uint16_t)USB_DEVICE_0, (uint16_t)0);
        usb_shhub_Info[usb_shhub_HubAddr].AttachSeq = USB_SEQ_4;
        R_USB_HHUB_SpecifiedPath(mess->result);
        break;

    case USB_SEQ_4:  /* Wait Enumeration End */
        rootport = usb_hstd_GetRootport(usb_shhub_HubAddr);
        if( USB_DEFAULT != usb_ghstd_MgrMode[rootport] )
        {
            /* Enumeration End */
            usb_shhub_DownPort[usb_shhub_HubAddr] |= USB_BITSET(usb_shhub_Info[usb_shhub_HubAddr].AttachPort);
            usb_shhub_Info[usb_shhub_HubAddr].AttachSeq = USB_SEQ_0;
            /* Return Process */
            if( usb_shhub_Info[usb_shhub_HubAddr].InitSeq == USB_SEQ_0 )
            {
                usb_shhub_Info[usb_shhub_HubAddr].Process = USB_MSG_HUB_EVENT;
            }
            else
            {
                usb_shhub_Info[usb_shhub_HubAddr].Process = USB_MSG_CLS_INIT;
            }
            R_USB_HHUB_SpecifiedPath(mess->result);

            if (FIT_NO_PTR != usb_shhub_cb)
            {
                usb_shhub_cb(usb_shhub_HubAddr, EVENT_HHUB_DEVICE_ATTACH, (uint8_t *)&usb_ghstd_DeviceAddr, sizeof(usb_ghstd_DeviceAddr));
            }
        }
        else
        {
            usb_shhub_Info[usb_shhub_HubAddr].AttachSeq = USB_SEQ_4;  /* Loop Sequencer */
            R_USB_HHUB_SpecifiedPathWait(mess->result, 10u);
        }
        break;

    default:
        break;
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_PortAttach
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_event
 *
 *  Description:    USB Hub Event process.
 *
 *  Parameters:     USB_UTR_t *mess    : USB system internal message.
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_event(USB_UTR_t *mess)
{
    uint16_t        port_clr_feature_type;

    if( USB_CTRL_END != mess->result )
    {
        USB_PRINTF2("event result ERROR, Addr:%d, Seq:%d\n", usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].EventSeq);
    }

    switch( usb_shhub_Info[usb_shhub_HubAddr].EventSeq )
    {
    case USB_SEQ_0:        /* Request */
        /* Hub and Port Status Change Bitmap(b0:Hub,b1:DownPort1change detected,b2:DownPort2,...) */
        if( 0 != ( usb_ghhub_Data[usb_shhub_HubAddr] & USB_BITSET(usb_shhub_Info[usb_shhub_HubAddr].EventPort) ) )
        {
            USB_PRINTF1(" *** HUB port %d \t",usb_shhub_Info[usb_shhub_HubAddr].EventPort);
            /* GetStatus request */
            R_USB_HHUB_GetStatus( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].EventPort,
                                                    R_USB_HHUB_class_request_complete );
            usb_shhub_Info[usb_shhub_HubAddr].EventSeq = USB_SEQ_1;
        }
        else
        {
            /* Port check end */
            usb_shhub_Info[usb_shhub_HubAddr].EventSeq = USB_SEQ_4;
            R_USB_HHUB_SpecifiedPath(mess->result);
        }
        break;

    case USB_SEQ_1:        /* Request Result Check & Request */
        if( usb_ghhub_Status[usb_shhub_HubAddr].change.BIT.c_connection )      /* C_PORT_CONNECTION */
        {
            R_USB_HHUB_PortClrFeature( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].EventPort,
                            (uint16_t)USB_HUB_C_PORT_CONNECTION, R_USB_HHUB_class_request_complete );
            usb_shhub_Info[usb_shhub_HubAddr].EventSeq = USB_SEQ_3;            /* Attach Sequence */
        }
        else
        {
            if( usb_ghhub_Status[usb_shhub_HubAddr].change.BIT.c_enable )            /* PORT_ENABLE */
            {
                USB_PRINTF0(" C_PORT_ENABLE\n");
                port_clr_feature_type = USB_HUB_C_PORT_ENABLE;
            }
            else if( usb_ghhub_Status[usb_shhub_HubAddr].change.BIT.c_suspend )      /* PORT_SUSPEND */
            {
                USB_PRINTF0(" C_PORT_SUSPEND\n");
                port_clr_feature_type = USB_HUB_C_PORT_SUSPEND;
            }
            else if( usb_ghhub_Status[usb_shhub_HubAddr].change.BIT.c_over_current ) /* PORT_OVER_CURRENT */
            {
                USB_PRINTF0(" C_PORT_OVER_CURRENT\n");
                port_clr_feature_type = USB_HUB_C_PORT_OVER_CURRENT;
            }
            else if( usb_ghhub_Status[usb_shhub_HubAddr].change.BIT.c_reset )        /* PORT_RESET */
            {
                USB_PRINTF0(" C_PORT_RESET\n");
                port_clr_feature_type = USB_HUB_C_PORT_RESET;
            }

            /* ClearFeature request */
            R_USB_HHUB_PortClrFeature( usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].EventPort,
                                                  port_clr_feature_type, R_USB_HHUB_class_request_complete );
            usb_shhub_Info[usb_shhub_HubAddr].EventSeq = USB_SEQ_2;            /* Next Sequence */
        }
        break;

    case USB_SEQ_2:  /* Request Result Check */
        if( usb_ghhub_Status[usb_shhub_HubAddr].status.BIT.suspend )
        {
            /* HUB downport status */
            usb_shhub_Remote[usb_shhub_HubAddr] |= USB_BITSET(usb_shhub_Info[usb_shhub_HubAddr].EventPort);
        }
        usb_shhub_Info[usb_shhub_HubAddr].EventSeq = USB_SEQ_4;                         /* This port event End */
        R_USB_HHUB_SpecifiedPath(mess->result);
        break;

    case USB_SEQ_3:  /* check PORT_CONNECTION */
        USB_PRINTF1(" [status] : 0x%04x\t", usb_ghhub_Status[usb_shhub_HubAddr].status.WORD);
        USB_PRINTF1(" [change] : 0x%04x\n", usb_ghhub_Status[usb_shhub_HubAddr].change.WORD);

        /* PortDisable */
        if( usb_ghhub_Status[usb_shhub_HubAddr].status.BIT.enable == 0 )
        {
            if( usb_ghhub_Status[usb_shhub_HubAddr].status.BIT.connection )
            {
                R_usb_cstd_DelayXms((uint16_t)100);
                usb_shhub_Info[usb_shhub_HubAddr].AttachPort = usb_shhub_Info[usb_shhub_HubAddr].EventPort;
                R_USB_HHUB_new_connect();
            }
            else
            {
                usb_shhub_Info[usb_shhub_HubAddr].AttachSeq = USB_SEQ_0;
                R_USB_HHUB_port_detach(usb_shhub_HubAddr, usb_shhub_Info[usb_shhub_HubAddr].EventPort);
                R_USB_HHUB_SpecifiedPath(mess->result);
            }
        }
        usb_shhub_Info[usb_shhub_HubAddr].EventSeq = USB_SEQ_4;                     /* This port event End */
        break;

    case USB_SEQ_4:  /* Attach */
        if( usb_shhub_Info[usb_shhub_HubAddr].EventPort >= usb_shhub_Info[usb_shhub_HubAddr].port_num )
        {   /* Port check end */
            usb_shhub_Info[usb_shhub_HubAddr].EventPort = USB_HUB_P1;      /* Port Clear */
            usb_shhub_Info[usb_shhub_HubAddr].EventSeq = USB_SEQ_0;        /* Sequence Clear */
            usb_shhub_Info[usb_shhub_HubAddr].Process = USB_SEQ_0;
            R_USB_HHUB_trans_start(usb_shhub_HubAddr, 1, (uint8_t*)&usb_ghhub_Data[usb_shhub_HubAddr], &R_USB_HHUB_trans_complete);
        }
        else
        {
            usb_shhub_Info[usb_shhub_HubAddr].EventPort++;                 /* Next port check */
            usb_shhub_Info[usb_shhub_HubAddr].EventSeq = USB_SEQ_0;        /* Sequence Clear */
            R_USB_HHUB_SpecifiedPath(mess->result);
        }
        break;

    default:
        break;
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_event
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_check_class
 *
 *  Description:    HUB Class driver check
 *
 *  Parameters:     uint16_t **table          : Descriptor, etc
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_check_class(uint16_t **table)
{
    USB_ER_t err;
    uint8_t hub_spec;

    usb_shhub_DeviceTable      = (uint8_t*)(table[0]);
    usb_shhub_ConfigTable      = (uint8_t*)(table[1]);
    usb_shhub_InterfaceTable   = (uint8_t*)(table[2]);

    usb_shhub_HubAddr          = *table[7];

    /* Device class check */
    if( usb_shhub_DeviceTable[USB_DEV_B_DEVICE_SUBCLASS] == 0x00 )
    {
        if( usb_shhub_DeviceTable[USB_DEV_B_DEVICE_PROTOCOL] == 0x00 )
        {
            USB_PRINTF0("*** Full-Speed HUB device.\n\n");
            hub_spec = USB_FSHUB;
        }
        else if( usb_shhub_DeviceTable[USB_DEV_B_DEVICE_PROTOCOL] == 0x01 )
        {
            USB_PRINTF0("*** High-Speed single TT device.\n\n");
            hub_spec = USB_HSHUBS;
        }
        else if( usb_shhub_DeviceTable[USB_DEV_B_DEVICE_PROTOCOL] == 0x02 )
        {
            USB_PRINTF0("*** High-Speed multiple TT device.\n\n");
            hub_spec = USB_HSHUBM;
        }
    }
    else
    {
    }

    /* Check interface number */
    switch( hub_spec )
    {
        case USB_FSHUB:     /* Full Speed Hub */
            if( usb_shhub_ConfigTable[USB_CON_B_NUM_INTERFACES] != USB_HUB_INTNUMFS )
            {
                USB_PRINTF0("### HUB configuration descriptor error !\n");
                err = USB_ERROR;
            }
            break;
        case USB_HSHUBS:    /* Hi Speed Hub(Single) */
            if( usb_shhub_ConfigTable[USB_CON_B_NUM_INTERFACES] != USB_HUB_INTNUMHSS )
            {
                USB_PRINTF0("### HUB configuration descriptor error !\n");
                err = USB_ERROR;
            }
            break;
        case USB_HSHUBM:    /* Hi Speed Hub(Multi) */
            if( usb_shhub_ConfigTable[USB_CON_B_NUM_INTERFACES] != USB_HUB_INTNUMHSM )
            {
                USB_PRINTF0("### HUB configuration descriptor error !\n");
                err = USB_ERROR;
            }
            break;
        default:
            err = USB_ERROR;
            break;
    }

    /* Check interface class */
    if( usb_shhub_InterfaceTable[USB_IF_B_INTERFACECLASS] != USB_IFCLS_HUB )
    {
        USB_PRINTF0("### HUB interface descriptor error !\n");
        err = USB_ERROR;
    }

    /* Check interface number */
    switch( hub_spec )
    {
    case USB_FSHUB:     /* Full Speed Hub */
        if( usb_shhub_InterfaceTable[2] != (USB_HUB_INTNUMFS - 1u) )
        {
            USB_PRINTF0("### HUB interface descriptor error !\n");
            err = USB_ERROR;
        }
        break;
    case USB_HSHUBS:    /* Hi Speed Hub(Single) */
        if( usb_shhub_InterfaceTable[2] != (USB_HUB_INTNUMHSS - 1u) )
        {
            USB_PRINTF0("### HUB interface descriptor error !\n");
            err = USB_ERROR;
        }
        break;
    case USB_HSHUBM:    /* Hi Speed Hub(Multi) */
        if( usb_shhub_InterfaceTable[2] != (USB_HUB_INTNUMHSM - 1u) )
        {
            USB_PRINTF0("### HUB interface descriptor error !\n");
            err = USB_ERROR;
        }
        break;
    default:
        err = USB_ERROR;
        break;
    }

    err = R_usb_hstd_SetPipe(table);

    usb_shhub_Info[usb_shhub_HubAddr].ClassSeq = USB_SEQ_0;
    usb_shhub_Info[usb_shhub_HubAddr].Process = USB_MSG_CLS_CHECKREQUEST;
    R_USB_HHUB_SpecifiedPath(err);
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_check_class
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_trans_start
 *
 *  Description:    HUB sys data transfer / control transfer
 *
 *  Parameters:     uint16_t hubaddr          : hub address
 *                  uint32_t size             : Data Transfer size
 *                  uint8_t  *table           : Receive Data area
 *                  USB_UTR_CB_t complete         : Callback function
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_trans_start(uint16_t hubaddr, uint32_t size, uint8_t *table, USB_UTR_CB_t complete)
{
    USB_ER_t        err;

    /* Transfer structure setting */
    usb_shhub_DataMess[hubaddr].keyword    = usb_shhub_Info[hubaddr].pipe_id;
    usb_shhub_DataMess[hubaddr].tranadr    = table;
    usb_shhub_DataMess[hubaddr].tranlen    = size;
    usb_shhub_DataMess[hubaddr].setup      = 0;
    usb_shhub_DataMess[hubaddr].complete   = complete;

    /* Transfer start */
    err = R_usb_hstd_TransferStart(&usb_shhub_DataMess[hubaddr]);
    if( USB_OK != err )
    {
        /* Send Message failure */
        USB_PRINTF1("### R_USB_HHUB_trans_start error (%ld)\n", err);
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_trans_start
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_GetHubDescriptor
 *
 *  Description:    Read HUB-Descriptor
 *
 *  Parameters:     uint16_t hubaddr        : hub address
 *                  USB_UTR_CB_t complete   : callback function
 *
 *  Return value:    uint16_t               : DONE/ERROR
 *
 **********************************************************************************************************************/
static uint16_t R_USB_HHUB_GetHubDescriptor(uint16_t hubaddr, USB_UTR_CB_t complete)
{
    USB_ER_t    err;

    /* Request */
    usb_shhub_ClassRequest.type    = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_CLASS | USB_DEVICE;
    usb_shhub_ClassRequest.value   = USB_HUB_DESCRIPTOR;
    usb_shhub_ClassRequest.index   = 0;
    usb_shhub_ClassRequest.length  = 0x0047;
    usb_shhub_ClassRequest.devaddr = hubaddr;      /* Device address */

    /* HUB Descriptor */
    usb_shhub_ControlMess.keyword  = USB_PIPE0;
    usb_shhub_ControlMess.tranadr  = (void*)&usb_ghhub_Descriptor[0];
    usb_shhub_ControlMess.tranlen  = (uint32_t)usb_shhub_ClassRequest.length;
    usb_shhub_ControlMess.setup    = &usb_shhub_ClassRequest;
    usb_shhub_ControlMess.complete = complete;

    /* Transfer start */
    err = usb_hstd_TransferStart(&usb_shhub_ControlMess);

    return err;
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_GetHubDescriptor
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_GetStatus
 *
 *  Description:    GetStatus request
 *
 *  Parameters:     uint16_t hubaddr          : hub address
 *                  uint16_t port             : down port number
 *                  USB_UTR_CB_t complete
 *
 *  Return value:   uint16_t                  : DONE/ERROR
 *
 **********************************************************************************************************************/
static uint16_t R_USB_HHUB_GetStatus(uint16_t hubaddr, uint16_t port, USB_UTR_CB_t complete)
{
    USB_ER_t        err;

    /* Request */
    usb_shhub_ClassRequest.type    = USB_GET_STATUS| USB_DEV_TO_HOST | USB_CLASS | USB_OTHER;
    usb_shhub_ClassRequest.value   = 0;
    usb_shhub_ClassRequest.index   = port;     /* Port number */
    usb_shhub_ClassRequest.length  = 4;
    usb_shhub_ClassRequest.devaddr = hubaddr;  /* Device address */

    /* Port GetStatus */
    usb_shhub_ControlMess.keyword  = USB_PIPE0;
    usb_shhub_ControlMess.tranadr  = (void*)&usb_ghhub_Status[hubaddr];
    usb_shhub_ControlMess.tranlen  = (uint32_t)usb_shhub_ClassRequest.length;
    usb_shhub_ControlMess.setup    = &usb_shhub_ClassRequest;
    usb_shhub_ControlMess.complete = complete;

    /* Transfer start */
    err = R_usb_hstd_TransferStart(&usb_shhub_ControlMess);

    return err;
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_GetStatus
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_PortSetFeature
 *
 *  Description:    SetFeature request
 *
 *  Parameters:     uint16_t hubaddr          : hub address
 *                  uint16_t port             : down port number
 *                  uint16_t command          : request command
 *
 *  Return value:   uint16_t                  : DONE/ERROR
 *
 **********************************************************************************************************************/
static uint16_t R_USB_HHUB_PortSetFeature(uint16_t hubaddr, uint16_t port, uint16_t command, USB_UTR_CB_t complete)
{
    USB_ER_t        err;

    /* Request */
    usb_shhub_ClassRequest.type    = USB_SET_FEATURE | USB_HOST_TO_DEV | USB_CLASS | USB_OTHER;
    usb_shhub_ClassRequest.value   = command;
    usb_shhub_ClassRequest.index   = port;         /* Port number */
    usb_shhub_ClassRequest.length  = 0;
    usb_shhub_ClassRequest.devaddr = hubaddr;      /* Device address */

    /* Port SetFeature */
    usb_shhub_ControlMess.keyword  = USB_PIPE0;
    usb_shhub_ControlMess.tranadr  = (void*)&usb_ghhub_Status[hubaddr];
    usb_shhub_ControlMess.tranlen  = (uint32_t)usb_shhub_ClassRequest.length;
    usb_shhub_ControlMess.setup    = &usb_shhub_ClassRequest;
    usb_shhub_ControlMess.complete = complete;

    /* Transfer start */
    err = R_usb_hstd_TransferStart(&usb_shhub_ControlMess);

    return err;
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_PortSetFeature
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_PortClrFeature
 *
 *  Description:    ClearFeature request
 *
 *  Parameters:     uint16_t hubaddr          : hub address
 *                  uint16_t port             : down port number
 *                  uint16_t command          : request command
 *
 *  Return value:   uint16_t                  : DONE/ERROR
 *
 **********************************************************************************************************************/
static uint16_t R_USB_HHUB_PortClrFeature(uint16_t hubaddr, uint16_t port, uint16_t command, USB_UTR_CB_t complete)
{
    USB_ER_t        err;

    /* Request */
    usb_shhub_ClassRequest.type    = USB_CLEAR_FEATURE | USB_HOST_TO_DEV | USB_CLASS | USB_OTHER;
    usb_shhub_ClassRequest.value   = command;
    usb_shhub_ClassRequest.index   = port;         /* Port number */
    usb_shhub_ClassRequest.length  = 0;
    usb_shhub_ClassRequest.devaddr = hubaddr;      /* Device address */

    /* Port ClearFeature */
    usb_shhub_ControlMess.keyword  = USB_PIPE0;
    usb_shhub_ControlMess.tranadr  = (void*)&usb_ghhub_Status[hubaddr];
    usb_shhub_ControlMess.tranlen  = (uint32_t)usb_shhub_ClassRequest.length;
    usb_shhub_ControlMess.setup    = &usb_shhub_ClassRequest;
    usb_shhub_ControlMess.complete = complete;

    /* Transfer start */
    err = R_usb_hstd_TransferStart(&usb_shhub_ControlMess);

    return err;
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_PortClrFeature
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_trans_complete
 *
 *  Description:    Receive complete Hub and Port Status Change Bitmap
 *
 *  Parameters:     USB_UTR_t *utr : Transfer Request Pointer
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_trans_complete(USB_UTR_t* utr)
{
    uint16_t        pipe_id;

    pipe_id = utr->keyword;
    usb_shhub_HubAddr = usb_cstd_GetDevAddr(pipe_id);

    usb_shhub_Info[usb_shhub_HubAddr].Process = USB_SEQ_0;

    switch( utr->result )
    {
        case USB_DATA_SHT:
            USB_PRINTF1("*** receive short(pipe %d : HUB) !\n", pipe_id);
            /* Continue */
        /* Direction is in then data receive end */
        case USB_DATA_OK:
            usb_shhub_Info[usb_shhub_HubAddr].Process = USB_MSG_HUB_EVENT;
            R_USB_HHUB_SpecifiedPath(USB_CTRL_END);
            break;
        case USB_DATA_STALL:
            USB_PRINTF0("*** Data Read error. ( STALL ) !\n");
            /* CLEAR_FEATURE */
            usb_hstd_ClearStall(pipe_id, &usb_cstd_DummyFunction);
            break;
        case USB_DATA_OVR:
            USB_PRINTF0("### receiver over. !\n");
            break;
        case USB_DATA_STOP:
            R_usb_hstd_TransferEnd(usb_shhub_Info[usb_shhub_HubAddr].pipe_id);
            USB_PRINTF0("### receiver stop. !\n");
            break;
        default:
            USB_PRINTF0("### HUB Class Data Read error !\n");
            break;
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_trans_complete
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_class_request_product_id_complete
 *
 *  Description:    Hub class check result
 *
 *  Parameters:     USB_UTR_t *utr : Transfer Request Pointer
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_class_request_product_id_complete(USB_UTR_t* utr)
{
    if( (USB_ER_t)USB_CTRL_END == utr->result)
    {
        /* Copy Product Id string data */
        R_USB_ConvertUnicodeStrDscrToAsciiStr((uint8_t *)utr->tranadr, usb_shhub_string_product_id);
    }
    else
    {
        USB_PRINTF0("*** Product ID error\n");
    }

    /* Next Process Selector */
    R_USB_HHUB_SpecifiedPath(utr->result);
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_class_request_product_id_complete
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_class_request_complete
 *
 *  Description:    Hub class check result
 *
 *  Parameters:     USB_UTR_t *utr : Transfer Request Pointer
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_class_request_complete(USB_UTR_t* utr)
{
    if( (USB_ER_t)USB_DATA_STALL == utr->result )
    {
        USB_PRINTF0("*** HUB Request STALL !\n");
    }
    else if( (USB_ER_t)USB_CTRL_END != utr->result )
    {
        USB_PRINTF0("*** HUB Request ERROR !\n");
    }
    else
    {
    }

    /* Next Process Selector */
    R_USB_HHUB_SpecifiedPath(utr->result);
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_class_request_complete
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_new_connect
 *
 *  Description:    new connect
 *
 *  Parameters:     none
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_new_connect(void)
{
    uint16_t devaddr;
    uint16_t i;

    /* New down-port device search */
    for( i = (USB_HUBDPADDR); i < (USB_MAXDEVADDR + 1u); i++ )
    {
        /* Protect Overlap */
        if( ( usb_shhub_Info[i].up_addr == usb_shhub_HubAddr ) &&
            ( usb_shhub_Info[i].up_port == usb_shhub_Info[usb_shhub_HubAddr].AttachPort ) )
        {
            devaddr = i;
            break;
        }
        if( 0 == usb_shhub_Info[i].up_addr )
        {
            /* New device address */
            devaddr = i;
            break;
        }
        else
        {
            devaddr = 0;
        }
    }

    if( 0 != devaddr )
    {
        USB_PRINTF1(" Hubport connect address%d\n", devaddr);
        usb_shhub_Info[devaddr].up_addr     = usb_shhub_HubAddr;    /* Up-hubaddr set */
        usb_shhub_Info[devaddr].up_port = usb_shhub_Info[usb_shhub_HubAddr].AttachPort;  /* Up-hubport set */
        usb_shhub_Info[usb_shhub_HubAddr].Process = USB_MSG_HUB_ATTACH;
        /* Next Process Selector */
        R_USB_HHUB_SpecifiedPath(USB_CTRL_END);

    }
    else
    {
        USB_PRINTF0("### device count over !\n");
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_new_connect
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_GetCnnDevaddr
 *
 *  Description:    Get the connected device address
 *                  from the HUB address and the down port number of a HUB
 *
 *  Parameters:     uint16_t hubaddr          : hub address
 *                  uint16_t portnum          : down port number
 *
 *  Return value:   uint16_t                  : Connected device address
 *
 **********************************************************************************************************************/
static uint16_t R_USB_HHUB_GetCnnDevaddr(uint16_t hubaddr, uint16_t portnum)
{
    uint16_t    i;

    for( i = (USB_HUBDPADDR); i < (USB_MAXDEVADDR + 1u); i++ )
    {
        if( ( usb_shhub_Info[i].up_addr == hubaddr ) &&
            ( usb_shhub_Info[i].up_port == portnum ) )
        {
            /* Device address */
            return i;
        }
    }
    return 0;
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_GetCnnDevaddr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_port_detach
 *
 *  Description:    HUB down port disconnect
 *
 *  Parameters:     uint16_t hubaddr          : hub address
 *                  uint16_t portnum          : down port number
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_port_detach(uint16_t hubaddr, uint16_t portnum)
{
    uint16_t        md;
    USB_HCDREG_t    *driver;
    /* Device number --> DeviceAddress */
    uint16_t        devaddr;

    /* HUB down-port status */
    usb_shhub_DownPort[hubaddr]    &= (uint16_t)(~USB_BITSET(portnum));
    /* HUB down-port RemoteWakeup */
    usb_shhub_Remote[hubaddr]  &= (uint16_t)(~USB_BITSET(portnum));
    /* Now down-port device search */
    devaddr = R_USB_HHUB_GetCnnDevaddr(hubaddr, portnum);
    for( md = 0; md < usb_ghstd_DeviceNum; md++ )
    {
        driver = &usb_ghstd_DeviceDrv[md];
        if( devaddr == driver->devaddr )
        {
            (*driver->devdetach)(driver->devaddr);
            /* Root port */
            driver->rootport    = USB_NOPORT;
            /* Device address */
            driver->devaddr     = USB_NODEVICE;
            /* Device state */
            driver->devstate    = USB_DETACHED;
        }
    }
    /* Selective detach */
    R_USB_HHUB_selective_detach(devaddr);

    if (FIT_NO_PTR != usb_shhub_cb)
    {
        usb_shhub_cb(hubaddr, EVENT_HHUB_DEVICE_DETACH, (uint8_t *)&devaddr, sizeof(devaddr));
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_port_detach
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_selective_detach
 *
 *  Description:    HUB down port Selective disconnect
 *
 *  Parameters:     uint16_t devaddr          : device address
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_selective_detach(uint16_t devaddr)
{
    r_usb_hstd_HciDisconnect( devaddr );
    usb_hstd_SetRootport(devaddr, 0x0000);
    usb_shhub_Info[devaddr].up_addr = 0;            /* Up-address clear */
    usb_shhub_Info[devaddr].up_port = 0;        /* Up-port num clear */
    USB_PRINTF1("*** Device address %d clear.\n\n", devaddr);
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_selective_detach
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_SpecifiedPath
 *
 *  Description:    Next Process Selector
 *
 *  Parameters:     uint16_t result        : utr result
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_SpecifiedPath( uint16_t result)
{
    USB_UTR_t           *p_blf;
    USB_ER_t            err;

    /* Get mem pool blk */
    if( USB_OK == USB_PGET_BLK( USB_HUB_MPL, &p_blf) )
    {
        p_blf->msginfo = usb_shhub_Info[usb_shhub_HubAddr].Process;
        p_blf->result  = result;

        /* Send message */
        err = USB_SND_MSG( USB_HUB_MBX, (USB_MSG_t*)p_blf );
        if( USB_OK != err )
        {
            /* Send message failure */
            err = USB_REL_BLK(USB_HUB_MPL, p_blf);
            USB_PRINTF0("### SpecifiedPass function snd_msg error\n");
        }
    }
    else
    {
        /* Get memory block failure */
        USB_PRINTF0("### SpecifiedPass function pget_blk error\n");
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_SpecifiedPath
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USB_HHUB_SpecifiedPathWait
 *
 *  Description:    Next Process Selector
 *
 *  Parameters:     uint16_t result        : utr result
 *                  uint16_t times         : Timeout value.
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_USB_HHUB_SpecifiedPathWait(uint16_t result, uint16_t times)
{
    USB_UTR_t           *p_blf;
    USB_ER_t            err;

    /* Get memory pool block */
    if( USB_OK == USB_PGET_BLK( USB_HUB_MPL, &p_blf) )
    {
        p_blf->msginfo = usb_shhub_Info[usb_shhub_HubAddr].Process;
        p_blf->result  = result;

        /* Wait message */
        err = USB_WAI_MSG( USB_HUB_MBX, (USB_MSG_t*)p_blf, times );
        if( USB_OK != err )
        {
            /* Wait message failure */
            err = USB_REL_BLK(USB_HUB_MPL, p_blf);
            USB_PRINTF0("### SpecifiedPassWait function snd_msg error\n");
        }
    }
    else
    {
        USB_PRINTF0("### SpecifiedPassWait function pget_blk error\n");
    }
}
/***********************************************************************************************************************
 End of function R_USB_HHUB_SpecifiedPathWait
 **********************************************************************************************************************/