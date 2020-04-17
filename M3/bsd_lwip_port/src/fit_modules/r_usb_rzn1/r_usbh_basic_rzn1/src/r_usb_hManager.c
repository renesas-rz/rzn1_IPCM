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
 * $Revision: 1350 $
 * $Date: 2019-03-08 12:36:25 +0000 (Fri, 08 Mar 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hManager.c
 *
 *  Description:      USB Host Control Manager
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include <string.h>
#include "r_usb_basic_local.h"
#include "r_usb_hHci.h"

/***********************************************************************************************************************
 Constant macro definitions
 **********************************************************************************************************************/
#define CLSDATASIZE     512

/* Device state define */
#define USB_NONDEVICE                       0u
#define USB_NOTTPL                          1u
#define USB_ATTACHDEVICE                    2u
#define USB_DEVICEENUMERATION               3u
#define USB_DEVICEADDRESSED                 4u
#define USB_DEVICECONFIGURED                5u
#define USB_COMPLETEPIPESET                 10u
#define USB_DEVICESUSPENDED                 20u
#define USB_ELECTRICALTEST                  30u

#define DESC_LENGTH_OFFSET                  0
#define DESC_TYPE_OFFSET                    1
#define DESC_INTERFACE_CLASS_TYPE_OFFSET    5
#define DESC_INTERFACE_LENGTH               9

/***********************************************************************************************************************
 Global variables and functions
 **********************************************************************************************************************/
USB_HCDREG_t    usb_ghstd_DeviceDrv[USB_MAXDEVADDR + 1u];       /* Device driver (registration) */
uint16_t        usb_ghstd_MgrMode[1u];                          /* Manager mode */
uint16_t        usb_ghstd_DeviceAddr;                           /* Device address */
uint16_t        usb_ghstd_DeviceSpeed;                          /* reset handshake result */
uint16_t        usb_ghstd_DeviceNum;                            /* Device driver number */
uint16_t        usb_ghstd_CheckEnuResult;

/***********************************************************************************************************************
 Static variables and functions
 **********************************************************************************************************************/
static USB_SETUP_t      usb_shstd_StdRequest; /* bRequest/wValue/wIndex/wLength/Data */
static uint16_t         usb_shstd_DummyData;
static USB_UTR_t        usb_shstd_StdReqMsg;
static uint16_t         usb_shstd_SuspendSeq = 0;
static uint16_t         usb_shstd_ResumeSeq = 0;

static uint16_t        usb_ghstd_EnumSeq;   /* Enumeration request */
static uint16_t        usb_ghstd_DeviceDescriptor[USB_DEVICESIZE / 2u];
static uint16_t        usb_ghstd_ConfigurationDescriptor[USB_CONFIGSIZE / 2u];
static uint16_t        usb_ghstd_LangId;
static uint8_t         usb_ghstd_ClassData[CLSDATASIZE];
static USB_UTR_t       usb_ghstd_ClassControl;
static USB_SETUP_t     usb_ghstd_ClassRequest; /* bRequest/wValue/wIndex/wLength/Data */

#ifdef USB_HOST_COMPLIANCE_MODE
static uint8_t usb_ghstd_TestPacketParameterFlag = 0;
#endif /* USB_HOST_COMPLIANCE_MODE */

static uint16_t usb_hstd_Enumeration( uint16_t result );
static void     usb_hstd_EnumerationErr( uint16_t EnumSeq );
static uint16_t usb_hstd_ChkDeviceClass( USB_HCDREG_t* driver, uint16_t port );
static void     usb_hstd_SubmitResult( USB_UTR_t *utr );
static void     usb_hstd_EnumSetAddress( uint16_t addr, uint16_t setaddr );
static void     usb_hstd_EnumSetConfiguration( uint16_t addr, uint16_t confnum );
static void     usb_hstd_MgrSuspend( uint16_t devaddr );
static void     usb_hstd_MgrResume( uint16_t devaddr );
static void     usb_hstd_SuspCont( uint16_t devaddr, uint16_t result );
static void     usb_hstd_ResuCont( uint16_t devaddr, uint16_t result );
static uint16_t usb_hstd_CmdSubmit( USB_UTR_CB_t complete );
static uint16_t usb_hstd_GetConfigDesc( uint16_t addr, uint16_t length, USB_UTR_CB_t complete );
static uint16_t usb_hstd_StdReqCheck( uint16_t errcheck );

uint16_t usb_hstd_SetFeature( uint16_t addr, uint16_t epnum, USB_UTR_CB_t complete );
uint16_t usb_hstd_ClearFeature( uint16_t addr, uint16_t epnum, USB_UTR_CB_t complete );
USB_ER_t usb_hstd_ClearStall( uint16_t pipe, USB_UTR_CB_t complete );
uint16_t usb_hstd_GetStringDesc( uint16_t addr, uint16_t string, USB_UTR_CB_t complete );
#ifdef USB_HOST_COMPLIANCE_MODE
void     usb_hstd_ElectricalTestMode( uint16_t product_id, uint16_t port );
#endif /* USB_HOST_COMPLIANCE_MODE */
void usb_hstd_MgrTask( void );

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_Enumeration
 *
 *  Description:    Execute enumeration on the connected USB device.
 *
 *  Parameters:     result         : Control Transfer result
 *
 *  Return value:   uint16_t       : Enumeration status.
 *
 **********************************************************************************************************************/
static uint16_t usb_hstd_Enumeration(uint16_t result)
{
#ifdef USB_HOST_COMPLIANCE_MODE
    uint16_t        vendor_id;
    uint16_t        product_id;
#endif  /* USB_HOST_COMPLIANCE_MODE */

    uint16_t        retval;
    uint16_t        md;
    USB_HCDREG_t    *driver;
    uint16_t        enume_mode;     /* Enumeration mode (device state) */
    uint8_t         *descriptor_table;
    uint16_t        rootport;
    USB_HCI_DEVICE *dev_info;

    /* Attach Detect Mode */
    enume_mode = USB_NONDEVICE;

    /* Get root port number from device addr */
    rootport    = usb_hstd_GetRootport(usb_ghstd_DeviceAddr);

    /* Manager Mode Change */
    switch(result)
    {
    case USB_CTRL_END:
        enume_mode = USB_DEVICEENUMERATION;
        switch(usb_ghstd_EnumSeq)
        {
        /* Receive Device Descriptor */
        case 0:
            usb_hstd_EnumSetAddress((uint16_t)USB_DEVICE_0, usb_ghstd_DeviceAddr);
            break;
        /* Set Address Result */
        case 1:
            /* Device descriptor information is copied */
            dev_info = r_usb_hstd_HciGetDeviceInformation(usb_ghstd_DeviceAddr);
            memcpy(&dev_info->devicedesc,usb_ghstd_DeviceDescriptor,sizeof(dev_info->devicedesc));
            /* Set device speed */
            usb_hstd_SetRootport(usb_ghstd_DeviceAddr, rootport);
            /* Get Descriptor */
            usb_hstd_EnumGetDescriptor(usb_ghstd_DeviceAddr, usb_ghstd_EnumSeq);
            break;
        /* Receive Device Descriptor(18) */
        case 2:
            usb_hstd_EnumGetDescriptor(usb_ghstd_DeviceAddr, usb_ghstd_EnumSeq);
            break;
        /* Receive Configuration Descriptor(9) */
        case 3:
            usb_hstd_EnumGetDescriptor(usb_ghstd_DeviceAddr, usb_ghstd_EnumSeq);
            break;
        /* Receive Configuration Descriptor(xx) */
        case 4:
#ifdef USB_HOST_COMPLIANCE_MODE
            descriptor_table = (uint8_t*)usb_ghstd_DeviceDescriptor;
            /* If 'vendor_id' and 'product_id' value is defined by PET, */
            /*    system works for compliance test mode. */
            /* Values ??defined by PET is the following. */
            /* vendor_id : 0x1A0A  */
            /* product_id : 0x0101 - 0x0108 , 0x0200 */

            vendor_id = (uint16_t)(descriptor_table[USB_DEV_ID_VENDOR_L]
                      + ((uint16_t)descriptor_table[USB_DEV_ID_VENDOR_H] << 8));

            if(vendor_id == 0x1A0A)
            {
                product_id = (uint16_t)(descriptor_table[USB_DEV_ID_PRODUCT_L]
                           + ((uint16_t)descriptor_table[USB_DEV_ID_PRODUCT_H] << 8));

                if((product_id >= 0x0101) && (product_id <= 0x0108))
                {
                    usb_ghstd_EnumSeq = 6;  /* Enumeration End */
                    usb_hstd_ElectricalTestMode(product_id, rootport);
                    enume_mode = USB_NOTTPL;
                    break;
                }

                if(product_id == 0x0200)
                {
                    usb_ghstd_EnumSeq = 5;  /* Skip EnumSeq 5 */
                    descriptor_table = (uint8_t*)usb_ghstd_ConfigurationDescriptor;
                    usb_hstd_EnumSetConfiguration(usb_ghstd_DeviceAddr, (uint16_t)(descriptor_table[USB_CON_B_CONFIGURATION_VALUE]));
                    break;
                }
            }
#endif  /* USB_HOST_COMPLIANCE_MODE */

            /* Device descriptor and Config descriptor information is copied. */
            dev_info = r_usb_hstd_HciGetDeviceInformation(usb_ghstd_DeviceAddr);
            /* Device Descriptor copy */
            memcpy(&dev_info->devicedesc,usb_ghstd_DeviceDescriptor,sizeof(dev_info->devicedesc));
            /* Configuration Descriptor copy */
            memcpy(&dev_info->rawconfigdesc,usb_ghstd_ConfigurationDescriptor,sizeof(dev_info->rawconfigdesc));

            /* Driver open */
            retval = USB_ERROR;
            for( md = 0; md < usb_ghstd_DeviceNum; md++ )
            {
                driver = &usb_ghstd_DeviceDrv[md];
                if( driver->devstate == USB_DETACHED )
                {
                    /* In this function, check device class of enumeration flow move to class */
                    retval = usb_hstd_ChkDeviceClass(driver, rootport);
                    /* "R_usb_hstd_ReturnEnuMGR()" is used to return */
                    if( retval == USB_OK )
                    {
                        driver->rootport = rootport;
                        driver->devaddr  = usb_ghstd_DeviceAddr;
                        break;
                    }
                }
            }
            if( retval == USB_ERROR )
            {
#ifdef USB_HOST_COMPLIANCE_MODE
                usb_ghstd_EnumSeq = 6;                          /* Enumeration End */
                enume_mode = USB_NOTTPL;
#else /* USB_HOST_COMPLIANCE_MODE */
                usb_ghstd_EnumSeq = 5;                          /* Skip EnumSeq 5 */
                descriptor_table = (uint8_t*)usb_ghstd_ConfigurationDescriptor;
                usb_hstd_EnumSetConfiguration(usb_ghstd_DeviceAddr, (uint16_t)(descriptor_table[USB_CON_B_CONFIGURATION_VALUE]));
#endif /* USB_HOST_COMPLIANCE_MODE */
            }
            break;
        /* Class Check Result */
        case 5:
            switch(usb_ghstd_CheckEnuResult)
            {
            case    USB_OK:
                descriptor_table = (uint8_t*)usb_ghstd_ConfigurationDescriptor;
                usb_hstd_EnumSetConfiguration(usb_ghstd_DeviceAddr, (uint16_t)(descriptor_table[USB_CON_B_CONFIGURATION_VALUE]));
                break;
            case    USB_ERROR:
                enume_mode = USB_NOTTPL;
                break;
            default:
                enume_mode = USB_NONDEVICE;
                break;
            }
            break;
        /* Set Configuration Result */
        case 6:
            /* Device enumeration function */
            USB_PRINTF0(" Configured Device\n");
            for( md = 0; md < usb_ghstd_DeviceNum; md++ )
            {
                driver = &usb_ghstd_DeviceDrv[md];
                if( usb_ghstd_DeviceAddr == driver->devaddr )
                {
                    driver->devstate        = USB_CONFIGURED;
                    (*driver->devconfig)(usb_ghstd_DeviceAddr); /* Call Back */
                    break;
                }
            }
            enume_mode = USB_COMPLETEPIPESET;
            break;

        default:
            break;
        }
        usb_ghstd_EnumSeq++;
        break;
    case USB_DATA_ERR:
        USB_PRINTF0("### Enumeration is stopped(SETUP or DATA-ERROR)\n");
        usb_hstd_EnumerationErr(usb_ghstd_EnumSeq);
        break;
    case USB_DATA_OVR:
        USB_PRINTF0("### Enumeration is stopped(receive data over)\n");
        usb_hstd_EnumerationErr(usb_ghstd_EnumSeq);
        break;
    case USB_DATA_STALL:
        USB_PRINTF0("### Enumeration is stopped(SETUP or DATA-STALL)\n");
        usb_hstd_EnumerationErr(usb_ghstd_EnumSeq);
        break;
    default:
        USB_PRINTF0("### Enumeration is stopped(result error)\n");
        usb_hstd_EnumerationErr(usb_ghstd_EnumSeq);
        break;
    }
    return (enume_mode);
}
/***********************************************************************************************************************
 End of function usb_hstd_Enumeration
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_EnumerationErr
 *
 *  Description:    Output error information when enumeration error occurred.
 *
 *  Parameters:     uint16_t EnumSeq             : enumeration sequence
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void usb_hstd_EnumerationErr(uint16_t EnumSeq)
{
    switch( EnumSeq )
    {
    case 0:     USB_PRINTF0(" Get_DeviceDescrip(8)\n");     break;
    case 1:     USB_PRINTF0(" Set_Address\n");              break;
    case 2:     USB_PRINTF0(" Get_DeviceDescrip(18)\n");    break;
    case 3:     USB_PRINTF0(" Get_ConfigDescrip(9)\n");     break;
    case 4:     USB_PRINTF0(" Get_ConfigDescrip(xx)\n");    break;
    case 5:     USB_PRINTF0(" Get_DeviceDescrip(8-2)\n");   break;
    case 6:     USB_PRINTF0(" Set_Configuration\n");        break;
    default:    break;
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_EnumerationErr
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_ChkDeviceClass
 *
 *  Description:    Interface class search
 *
 *  Parameters:     USB_HCDREG_t *driver      : Class driver
 *                  uint16_t port             : Port no.
 *
 *  Return value:   uint16_t                  : USB_OK / USB_ERROR
 *
 **********************************************************************************************************************/
static uint16_t usb_hstd_ChkDeviceClass(USB_HCDREG_t *driver, uint16_t port)
{
    uint8_t         *descriptor_table;
    uint16_t        sub_desc_start_idx;
    uint16_t        total_length;
    uint16_t        result;
    uint16_t        hub_device;
    uint16_t        *table[9];
#ifdef USB_HOST_COMPLIANCE_MODE
    uint16_t        vendor_id;
    uint16_t        product_id;
    uint16_t        id_check;
    uint16_t        i;

    descriptor_table = (uint8_t*)usb_ghstd_DeviceDescriptor;

    id_check = USB_ERROR;
    for( i = 0; i < driver->tpl[0]; i++ )
    {
        vendor_id = (uint16_t)(descriptor_table[USB_DEV_ID_VENDOR_L]
                  + ((uint16_t)descriptor_table[USB_DEV_ID_VENDOR_H] << 8));

        if( (driver->tpl[(i * 2) + 2] == USB_NOVENDOR) || (driver->tpl[(i * 2) + 2] == vendor_id) )
        {
            product_id = (uint16_t)(descriptor_table[USB_DEV_ID_PRODUCT_L]
                       + ((uint16_t)descriptor_table[USB_DEV_ID_PRODUCT_H] << 8));

            if( (driver->tpl[(i * 2) + 3] == USB_NOPRODUCT) || (driver->tpl[(i * 2) + 3] == product_id) )
            {
                id_check = USB_OK;
                USB_COMPLIANCE_DISP(USB_COMP_TPL, USB_NO_ARG);
                USB_COMPLIANCE_DISP(USB_COMP_VID, vendor_id);
                USB_COMPLIANCE_DISP(USB_COMP_PID, product_id);
            }
        }
    }

    if( id_check == USB_ERROR )
    {
        USB_PRINTF0("### Not support device\n");
        if( descriptor_table[USB_DEV_B_DEVICE_CLASS] == USB_IFCLS_HUB )
        {
            USB_COMPLIANCE_DISP(USB_COMP_HUB, vendor_id);
        }
        else
        {
            USB_COMPLIANCE_DISP(USB_COMP_NOTTPL, vendor_id);
        }

        return USB_ERROR;
    }
#endif /* USB_HOST_COMPLIANCE_MODE */

    descriptor_table = (uint8_t*)usb_ghstd_ConfigurationDescriptor;
    sub_desc_start_idx = 0;
    total_length = (uint16_t)(descriptor_table[USB_CON_W_TOTAL_LENGTH_L]
                  + ((uint16_t)descriptor_table[USB_CON_W_TOTAL_LENGTH_H] << 8));

    if( total_length > USB_CONFIGSIZE )
    {
        total_length = USB_CONFIGSIZE;
    }

    /* Search within configuration total-length */
    while( (sub_desc_start_idx + DESC_INTERFACE_LENGTH) <= total_length )
    {
        switch( descriptor_table[sub_desc_start_idx + DESC_TYPE_OFFSET] )
        {
        /* Configuration Descriptor ? */
        case USB_DT_CONFIGURATION:
            table[1] = (uint16_t*)&descriptor_table[sub_desc_start_idx + DESC_LENGTH_OFFSET];
            break;
        /* Interface Descriptor ? */
        case USB_DT_INTERFACE:
            if( driver->ifclass == (uint16_t)descriptor_table[sub_desc_start_idx + DESC_INTERFACE_CLASS_TYPE_OFFSET] )
            {
                result = USB_ERROR;
                table[0]    = (uint16_t*)&usb_ghstd_DeviceDescriptor;
                table[2]    = (uint16_t*)&descriptor_table[sub_desc_start_idx];
                table[3]    = &result;
                table[4]    = &hub_device;
                table[5]    = &port;
                table[6]    = &usb_ghstd_DeviceSpeed;
                table[7]    = &usb_ghstd_DeviceAddr;

                /* ClassCheck Callback */
                (*driver->classcheck)((uint16_t**)&table);

                return result;
            }
            else
            {
                USB_PRINTF2("*** Interface class is 0x%02x (not 0x%02x)\n", descriptor_table[sub_desc_start_idx + DESC_INTERFACE_CLASS_TYPE_OFFSET], driver->ifclass);
            }
            break;
        default:
            break;
        }
        sub_desc_start_idx += descriptor_table[sub_desc_start_idx];
        if( descriptor_table[sub_desc_start_idx] == 0 )
        {
            break;
        }
    }
    return USB_ERROR;
}
/***********************************************************************************************************************
 End of function usb_hstd_ChkDeviceClass
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_SubmitResult
 *
 *  Description:    Callback after completion of a standard request.
 *
 *  Parameters:     uint16_t port     : Port no.
 *                  uint16_t result   : Result.
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void usb_hstd_SubmitResult(USB_UTR_t* utr)
{
#ifdef USB_HOST_COMPLIANCE_MODE
    usb_ghstd_TestPacketParameterFlag = 0;
#endif /* USB_HOST_COMPLIANCE_MODE */

    usb_hstd_MgrSndMbx((uint16_t)USB_MSG_MGR_SUBMITRESULT, utr->setup->devaddr, utr->result);
}
/***********************************************************************************************************************
 End of function usb_hstd_SubmitResult
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_EnumGetDescriptor
 *
 *  Description:    Send GetDescriptor to the connected USB device.
 *
 *  Parameters:     uint16_t addr             : Device Address
 *                  uint16_t cnt_value        : Enumeration sequence
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void usb_hstd_EnumGetDescriptor(uint16_t addr, uint16_t cnt_value)
{
    uint8_t         *data_table;

    switch( cnt_value )
    {
    case 0:
        usb_ghstd_EnumSeq = 0;
        /* continue */
    case 4:
        usb_shstd_StdRequest.type   = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
        usb_shstd_StdRequest.value  = (uint16_t)USB_DEV_DESCRIPTOR;
        usb_shstd_StdRequest.index  = (uint16_t)0x0000;
        usb_shstd_StdRequest.length = (uint16_t)0x0040;
        if( usb_shstd_StdRequest.length > USB_DEVICESIZE )
        {
            usb_shstd_StdRequest.length = USB_DEVICESIZE;
        }
        usb_shstd_StdReqMsg.tranadr = usb_ghstd_DeviceDescriptor;
        break;
    case 1:
        usb_shstd_StdRequest.type   = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
        usb_shstd_StdRequest.value  = (uint16_t)USB_DEV_DESCRIPTOR;
        usb_shstd_StdRequest.index  = (uint16_t)0x0000;
        usb_shstd_StdRequest.length = (uint16_t)0x0012;
        if( usb_shstd_StdRequest.length > USB_DEVICESIZE )
        {
            usb_shstd_StdRequest.length = USB_DEVICESIZE;
        }
        usb_shstd_StdReqMsg.tranadr = usb_ghstd_DeviceDescriptor;
        break;
    case 2:
        usb_shstd_StdRequest.type   = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
        usb_shstd_StdRequest.value  = (uint16_t)USB_CONF_DESCRIPTOR;
        usb_shstd_StdRequest.index  = (uint16_t)0x0000;
        usb_shstd_StdRequest.length = (uint16_t)0x0009;
        usb_shstd_StdReqMsg.tranadr = usb_ghstd_ConfigurationDescriptor;
        break;
    case 3:
        data_table = (uint8_t*)usb_ghstd_ConfigurationDescriptor;
        usb_shstd_StdRequest.type   = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
        usb_shstd_StdRequest.value  = (uint16_t)USB_CONF_DESCRIPTOR;
        usb_shstd_StdRequest.index  = (uint16_t)0x0000;
        usb_shstd_StdRequest.length = (uint16_t)(((uint16_t)data_table[3] << 8) + (uint16_t)data_table[2]);
        if( usb_shstd_StdRequest.length > USB_CONFIGSIZE )
        {
            usb_shstd_StdRequest.length = USB_CONFIGSIZE;
            USB_PRINTF0("***WARNING Descriptor size over !\n");
        }
        usb_shstd_StdReqMsg.tranadr = usb_ghstd_ConfigurationDescriptor;
        break;
    default:
        return;
    }
    usb_shstd_StdRequest.devaddr = addr;

    usb_shstd_StdReqMsg.keyword  = (uint16_t)USB_PIPE0;
    usb_shstd_StdReqMsg.tranlen  = usb_shstd_StdRequest.length;
    usb_shstd_StdReqMsg.setup    = &usb_shstd_StdRequest;
    usb_shstd_StdReqMsg.complete = &usb_hstd_SubmitResult;

    usb_hstd_TransferStart(&usb_shstd_StdReqMsg);
}
/***********************************************************************************************************************
 End of function usb_hstd_EnumGetDescriptor
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_EnumSetAddress
 *
 *  Description:    Send SetAddress to the connected USB device.
 *
 *  Parameters:     uint16_t addr     : Device Address.
 *                  uint16_t setaddr  : New address.
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void usb_hstd_EnumSetAddress(uint16_t addr, uint16_t setaddr)
{
    usb_shstd_StdRequest.type    = USB_SET_ADDRESS | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
    usb_shstd_StdRequest.value   = setaddr;
    usb_shstd_StdRequest.index   =  0x0000;
    usb_shstd_StdRequest.length  =  0x0000;
    usb_shstd_StdRequest.devaddr = addr;

    usb_shstd_StdReqMsg.keyword     = (uint16_t)USB_PIPE0;
    usb_shstd_StdReqMsg.tranadr     = (void *)&usb_shstd_DummyData;
    usb_shstd_StdReqMsg.tranlen     = usb_shstd_StdRequest.length;
    usb_shstd_StdReqMsg.setup       = &usb_shstd_StdRequest;
    usb_shstd_StdReqMsg.complete    = &usb_hstd_SubmitResult;

    usb_hstd_TransferStart(&usb_shstd_StdReqMsg);
}
/***********************************************************************************************************************
 End of function usb_hstd_EnumSetAddress
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_EnumSetConfiguration
 *
 *  Description:    Send SetConfiguration to the connected USB device.
 *
 *  Parameters:     uint16_t addr     : Device Address.
 *                  uint16_t confnum  : Configuration number.
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void usb_hstd_EnumSetConfiguration(uint16_t addr, uint16_t confnum)
{
    usb_shstd_StdRequest.type    = USB_SET_CONFIGURATION | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
    usb_shstd_StdRequest.value   = confnum;
    usb_shstd_StdRequest.index   =  0x0000;
    usb_shstd_StdRequest.length  =  0x0000;
    usb_shstd_StdRequest.devaddr = addr;

    usb_shstd_StdReqMsg.keyword     = (uint16_t)USB_PIPE0;
    usb_shstd_StdReqMsg.tranadr     = (void *)&usb_shstd_DummyData;
    usb_shstd_StdReqMsg.tranlen     = usb_shstd_StdRequest.length;
    usb_shstd_StdReqMsg.setup       = &usb_shstd_StdRequest;
    usb_shstd_StdReqMsg.complete    = &usb_hstd_SubmitResult;

    usb_hstd_TransferStart(&usb_shstd_StdReqMsg);
}
/***********************************************************************************************************************
 End of function usb_hstd_EnumSetConfiguration
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_MgrSuspend
 *
 *  Description:    Suspend request
 *
 *  Parameters:     uint16_t devaddr  : Device address.
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void usb_hstd_MgrSuspend(uint16_t devaddr)
{
    uint16_t rootport;

    rootport = usb_hstd_GetRootport(devaddr);

    if( rootport != USB_NOPORT )
    {
        usb_ghstd_MgrMode[rootport] = USB_SUSPENDED_PROCESS;
        usb_shstd_SuspendSeq = 0;
        usb_hstd_SuspCont(devaddr, 0);
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_MgrSuspend
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_MgrResume
 *
 *  Description:    Request HCD (Host Control Device) to send RESUME signal.
 *
 *  Parameters:     uint16_t devaddr  : Device address.
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void usb_hstd_MgrResume(uint16_t devaddr)
{
    uint16_t rootport;

    rootport = usb_hstd_GetRootport(devaddr);

    if( rootport != USB_NOPORT )
    {
        usb_ghstd_MgrMode[rootport] = USB_RESUME_PROCESS;
        usb_shstd_ResumeSeq = 0;
        r_usb_hstd_HciPortResume(rootport);
        usb_hstd_ResuCont(devaddr, 0);
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_MgrResume
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_SuspCont
 *
 *  Description:    Suspend the connected USB Device (Function for nonOS)
 *
 *  Parameters:     uint16_t devaddr          : Device Address
 *                  uint16_t result           : Transfer Result
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void usb_hstd_SuspCont(uint16_t devaddr, uint16_t result)
{
    uint16_t            md;
    USB_HCDREG_t        *driver;
    uint16_t            rootport;

    rootport = usb_hstd_GetRootport(devaddr);

    switch(usb_shstd_SuspendSeq)
    {
    case    0:
        usb_hstd_GetConfigDesc(devaddr, (uint16_t)0x09, (USB_UTR_CB_t)&usb_hstd_SubmitResult);
        usb_shstd_SuspendSeq++;
        break;
    case    1:
        if (usb_hstd_StdReqCheck(result) == USB_OK)
        {
            /* Check Remote Wakeup */
            if( (usb_ghstd_ClassData[USB_CON_BM_ATTRIBUTES] & USB_CF_RWUPON) == USB_CF_RWUPON )
            {
                usb_hstd_SetFeature(devaddr, (uint16_t)0xFF, (USB_UTR_CB_t)&usb_hstd_SubmitResult);
                usb_shstd_SuspendSeq++;
            }
            else
            {
                USB_PRINTF0("### Remote wakeup disable\n");
                r_usb_hstd_HciPortSuspend(rootport);
                usb_ghstd_MgrMode[rootport]    = USB_SUSPENDED;
            }
        }
        break;
    case    2:
        if(usb_hstd_StdReqCheck(result) == USB_OK)
        {
            r_usb_hstd_HciPortSuspend(rootport);
            usb_ghstd_MgrMode[rootport]    = USB_SUSPENDED;
        }
        break;
    default:
        break;
    }

    if( usb_ghstd_MgrMode[rootport] == USB_SUSPENDED )
    {
        for( md = 0; md < usb_ghstd_DeviceNum; md++ )
        {
            driver = &usb_ghstd_DeviceDrv[md];
            if( driver->devaddr == (rootport + USB_DEVICEADDR) )
            {
                (*driver->devsuspend)(driver->devaddr);
                /* Device state */
                driver->devstate = USB_SUSPENDED;
            }
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_SuspCont
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_ResuCont
 *
 *  Description:    Resume the connected USB Device (Function for nonOS)
 *
 *  Parameters:     uint16_t devaddr          : Device Address
 *                  uint16_t result           : Transfer Result
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void usb_hstd_ResuCont(uint16_t devaddr, uint16_t result)
{
    uint16_t            md;
    USB_HCDREG_t        *driver;
    uint16_t            rootport;

    rootport = usb_hstd_GetRootport(devaddr);

    switch(usb_shstd_ResumeSeq)
    {
    case    0:
        usb_hstd_GetConfigDesc(devaddr, (uint16_t)0x09, (USB_UTR_CB_t)&usb_hstd_SubmitResult);
        usb_shstd_ResumeSeq++;
        break;
    case    1:
        if(usb_hstd_StdReqCheck(result) == USB_OK)
        {
            /* Check Remote Wakeup */
            if( (usb_ghstd_ClassData[USB_CON_BM_ATTRIBUTES] & USB_CF_RWUPON) == USB_CF_RWUPON )
            {
                usb_hstd_ClearFeature(devaddr, (uint16_t)0xFF, (USB_UTR_CB_t)&usb_hstd_SubmitResult);
                usb_shstd_ResumeSeq++;
            }
            else
            {
                usb_ghstd_MgrMode[rootport] = USB_CONFIGURED;
            }
        }
        break;
    case    2:
        if(usb_hstd_StdReqCheck(result) == USB_OK)
        {
            usb_ghstd_MgrMode[rootport] = USB_CONFIGURED;
        }
        break;
    default:
        break;
    }

    if( usb_ghstd_MgrMode[rootport] == USB_CONFIGURED )
    {
        for( md = 0; md < usb_ghstd_DeviceNum; md++ )
        {
            driver  = &usb_ghstd_DeviceDrv[md];
            if(driver->devaddr == (rootport+USB_DEVICEADDR))
            {
                (*driver->devresume)(driver->devaddr);
                /* Device state */
                driver->devstate = USB_CONFIGURED;
            }
        }
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_ResuCont
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_CmdSubmit
 *
 *  Description:    command submit
 *
 *  Parameters:     USB_UTR_CB_t complete     : callback info
 *
 *  Return value:   uint16_t                  : TransferStart Result
 *
 **********************************************************************************************************************/
static uint16_t usb_hstd_CmdSubmit(USB_UTR_CB_t complete)
{
    usb_ghstd_ClassControl.tranadr  = (void*)usb_ghstd_ClassData;
    usb_ghstd_ClassControl.complete = complete;
    usb_ghstd_ClassControl.tranlen  = (uint32_t)usb_ghstd_ClassRequest.length;
    usb_ghstd_ClassControl.keyword  = USB_PIPE0;
    usb_ghstd_ClassControl.setup    = &usb_ghstd_ClassRequest;

    return usb_hstd_TransferStart(&usb_ghstd_ClassControl);
}
/***********************************************************************************************************************
 End of function usb_hstd_CmdSubmit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_SetFeature
 *
 *  Description:    Set SetFeature
 *
 *  Parameters:     uint16_t addr            : device address
 *                  uint16_t epnum           : endpoint number
 *                  USB_UTR_CB_t complete    : callback function
 *
 *  Return value:   uint16_t                 : error info
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_SetFeature(uint16_t addr, uint16_t epnum, USB_UTR_CB_t complete)
{
    if( epnum == 0xFF )
    {
        /* SetFeature(Device) */
        usb_ghstd_ClassRequest.type   = USB_SET_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
        usb_ghstd_ClassRequest.value  = USB_DEV_REMOTE_WAKEUP;
        usb_ghstd_ClassRequest.index  = (uint16_t)0x0000;
    }
    else
    {
        /* SetFeature(endpoint) */
        usb_ghstd_ClassRequest.type   = USB_SET_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_ENDPOINT;
        usb_ghstd_ClassRequest.value  = USB_ENDPOINT_HALT;
        usb_ghstd_ClassRequest.index  = epnum;
    }
    usb_ghstd_ClassRequest.length  = (uint16_t)0x0000;
    usb_ghstd_ClassRequest.devaddr = addr;

    return usb_hstd_CmdSubmit(complete);
}
/***********************************************************************************************************************
 End of function usb_hstd_SetFeature
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_ClearFeature
 *
 *  Description:    Send ClearFeature command to the connected USB device.
 *
 *  Parameters:     uint16_t addr     : Device address.
 *                  uint16_t epnum    : Endpoint number.
 *                  USB_UTR_CB_t complete : Callback function.
 *
 *  Return value:   uint16_t          : Error info.
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_ClearFeature(uint16_t addr, uint16_t epnum, USB_UTR_CB_t complete)
{
    if (epnum == 0xFF)
    {
        /* ClearFeature(Device) */
        usb_ghstd_ClassRequest.type  = USB_CLEAR_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_DEVICE;
        usb_ghstd_ClassRequest.value = USB_DEV_REMOTE_WAKEUP;
        usb_ghstd_ClassRequest.index = (uint16_t)0x0000;
    }
    else
    {
        /* ClearFeature(endpoint) */
        usb_ghstd_ClassRequest.type  = USB_CLEAR_FEATURE | USB_HOST_TO_DEV | USB_STANDARD | USB_ENDPOINT;
        usb_ghstd_ClassRequest.value = USB_ENDPOINT_HALT;
        usb_ghstd_ClassRequest.index = epnum;
    }
    usb_ghstd_ClassRequest.length  = (uint16_t)0x0000;
    usb_ghstd_ClassRequest.devaddr = addr;

    return usb_hstd_CmdSubmit(complete);
}
/***********************************************************************************************************************
 End of function usb_hstd_ClearFeature
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_ClearStall
 *
 *  Description:    Clear Stall
 *
 *  Parameters:     uint16_t pipe      : Pipe number.
 *                  USB_UTR_CB_t complete  : Callback function
 *
 *  Return value:   uint16_t           : Error info.
 *
 **********************************************************************************************************************/
USB_ER_t usb_hstd_ClearStall(uint16_t pipe, USB_UTR_CB_t complete)
{
    USB_ER_t    err;
    uint16_t    epnum;
    uint16_t    devaddr;

    epnum = usb_cstd_GetEpnum(pipe);
    epnum |= usb_hstd_GetPipeDir(pipe);
    devaddr = usb_cstd_GetDevAddr(pipe);

    err = usb_hstd_ClearFeature(devaddr, epnum, complete);
    return err;
}
/***********************************************************************************************************************
 End of function usb_hstd_ClearStall
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_GetConfigDesc
 *
 *  Description:    Set GetConfigurationDescriptor
 *
 *  Parameters:     uint16_t addr            : device address
 *                  uint16_t length          : descriptor length
 *                  USB_UTR_CB_t complete        : callback function
 *
 *  Return value:   uint16_t                 : error info
 *
 **********************************************************************************************************************/
static uint16_t usb_hstd_GetConfigDesc(uint16_t addr, uint16_t length, USB_UTR_CB_t complete)
{
    uint16_t        i;

    /* Get Configuration Descriptor */
    usb_ghstd_ClassRequest.type   = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
    usb_ghstd_ClassRequest.value  = USB_CONF_DESCRIPTOR;
    usb_ghstd_ClassRequest.index  = (uint16_t)0x0000;
    usb_ghstd_ClassRequest.length = length;
    if( usb_ghstd_ClassRequest.length > CLSDATASIZE )
    {
        usb_ghstd_ClassRequest.length = (uint16_t)CLSDATASIZE;
        USB_PRINTF0("***WARNING Descriptor size over !\n");
    }
    usb_ghstd_ClassRequest.devaddr = addr;

    for( i = 0; i < usb_ghstd_ClassRequest.length; i++ )
    {
        usb_ghstd_ClassData[i] = (uint8_t)0xFF;
    }

    return usb_hstd_CmdSubmit(complete);
}
/***********************************************************************************************************************
 End of function usb_hstd_GetConfigDesc
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_StdReqCheck
 *
 *  Description:    Sample Standard Request Check
 *
 *  Parameters:     uint16_t errcheck        : error
 *
 *  Return value:   uint16_t                 : error info
 *
 **********************************************************************************************************************/
static uint16_t usb_hstd_StdReqCheck(uint16_t errcheck)
{
    if( errcheck == USB_DATA_STALL )
    {
        USB_PRINTF0("*** Standard Request STALL !\n");
        return  USB_ERROR;
    }
    else if( errcheck != USB_CTRL_END )
    {
        USB_PRINTF0("*** Standard Request error !\n");
        return  USB_ERROR;
    }
    else
    {
    }
    return  USB_OK;
}
/***********************************************************************************************************************
 End of function usb_hstd_StdReqCheck
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_GetStringDesc
 *
 *  Description:    Set GetDescriptor
 *
 *  Parameters:     uint16_t addr            : device address
 *                  uint16_t string          : descriptor index
 *                  USB_UTR_CB_t complete    : callback function
 *
 *  Return value:   uint16_t                 : error info
 *
 **********************************************************************************************************************/
uint16_t usb_hstd_GetStringDesc(uint16_t addr, uint16_t string, USB_UTR_CB_t complete)
{
    uint16_t        i;

    if( string == 0 )
    {
        usb_ghstd_ClassRequest.index  = (uint16_t)0x0000;
        usb_ghstd_ClassRequest.length = (uint16_t)0x0004;
    }
    else
    {
        /* Set LanguageID */
        usb_ghstd_ClassRequest.index  = usb_ghstd_LangId;
        usb_ghstd_ClassRequest.length = (uint16_t)CLSDATASIZE;
    }
    usb_ghstd_ClassRequest.type    = USB_GET_DESCRIPTOR | USB_DEV_TO_HOST | USB_STANDARD | USB_DEVICE;
    usb_ghstd_ClassRequest.value   = (uint16_t)(USB_STRING_DESCRIPTOR + string);
    usb_ghstd_ClassRequest.devaddr = addr;

    for( i = 0; i < usb_ghstd_ClassRequest.length; i++ )
    {
        usb_ghstd_ClassData[i] = (uint8_t)0xFF;
    }

    return usb_hstd_CmdSubmit(complete);
}
/***********************************************************************************************************************
 End of function usb_hstd_GetStringDesc
 **********************************************************************************************************************/

#ifdef USB_HOST_COMPLIANCE_MODE
/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_ElectricalTestMode
 *
 *  Description:    Host electrical test mode function
 *
 *  Parameters:     product_id          : Task Start Code
 *                  port                : root port number
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void usb_hstd_ElectricalTestMode(uint16_t product_id, uint16_t port)
{
    uint16_t    devaddr;

    devaddr = r_usb_hstd_HciGetDeviceAddressOfRootpoot(port);

    switch(product_id)
    {
    case 0x0101:    /* Test_SE0_NAK */
        r_usb_hstd_HciElectricalTest(port, 0);
        break;
    case 0x0102:    /* Test_J */
        r_usb_hstd_HciElectricalTest(port, 1);
        break;
    case 0x0103:    /* Test_K */
        r_usb_hstd_HciElectricalTest(port, 2);
        break;
    case 0x0104:    /* Test_Packet */
        r_usb_hstd_HciElectricalTest(port, 3);
        break;
    case 0x0105:    /* Reserved */
        break;
    case 0x0106:    /* HS_HOST_PORT_SUSPEND_RESUME */
        r_usb_hstd_HciElectricalTest(port, 4);
        break;
    case 0x0107:    /* SINGLE_STEP_GET_DEV_DESC */
        R_usb_cstd_DelayXms(15000);            /* wait 15sec */
        usb_hstd_EnumGetDescriptor(devaddr, 0);
        break;
    case 0x0108:    /* SINGLE_STEP_GET_DEV_DESC_DATA */
        usb_ghstd_TestPacketParameterFlag = 1;
        usb_hstd_EnumGetDescriptor(devaddr, 0);
        break;
    default:
        break;
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_ElectricalTestMode
 **********************************************************************************************************************/
#endif /* USB_HOST_COMPLIANCE_MODE */

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_MgrTask
 *
 *  Description:    The host manager (MGR) task.
 *
 *  Parameters:     none
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void usb_hstd_MgrTask(void)
{
    USB_UTR_t       *mess;
    USB_ER_t        err;
    USB_HCDREG_t    *driver;
    uint16_t        rootport, devaddr, pipenum;
    uint16_t        md;
    uint16_t        enume_mode; /* Enumeration mode (device state) */

    r_usb_hstd_HciTask();

    /* Receive message */
    err = USB_RCV_MSG(USB_MGR_MBX, (USB_MSG_t**)&mess);
    if ( err != USB_OK )
    {
        return;
    }
    else
    {
        switch( mess->msginfo )
        {
        /* USB-bus control (change device state) */
        case USB_MSG_MGR_STATUSRESULT:
            rootport    = mess->keyword;
            switch( usb_ghstd_MgrMode[rootport] )
            {
            /* End of reset signal */
            case USB_DEFAULT:
                usb_ghstd_DeviceSpeed = mess->result;
                /* Set device speed */
                usb_hstd_SetRootport((uint16_t)USB_DEVICE_0, rootport);
                switch( usb_ghstd_DeviceSpeed )
                {
                case USB_HSCONNECT: /* Hi Speed Device Connect */
                    USB_PRINTF0(" Hi-Speed Device\n");
                    usb_hstd_EnumGetDescriptor((uint16_t)USB_DEVICE_0, (uint16_t)0);
                    break;
                case USB_FSCONNECT: /* Full Speed Device Connect */
                    USB_PRINTF0(" Full-Speed Device\n");
                    usb_hstd_EnumGetDescriptor((uint16_t)USB_DEVICE_0, (uint16_t)0);
                    break;
                case USB_LSCONNECT: /* Low Speed Device Connect */
                    USB_PRINTF0(" Low-Speed Device\n");
                    USB_PRINTF0(" Not Supported\n");
                    usb_ghstd_MgrMode[rootport] = USB_DETACHED;
                    break;
                default:
                    USB_PRINTF0(" Device/Detached\n");
                    usb_ghstd_MgrMode[rootport] = USB_DETACHED;
                    break;
                }
                break;

            case USB_DETACHED:
                break;

            default:
                break;
            }
            break;

        case USB_MSG_MGR_SUBMITRESULT:
            devaddr  = mess->keyword;
            rootport = usb_hstd_GetRootport(devaddr);
            switch(usb_ghstd_MgrMode[rootport])
            {
            /* Resume */
            case    USB_RESUME_PROCESS:
                /* Resume Sequence Number is 1 to 2 */
                usb_hstd_ResuCont(devaddr, mess->result);
                break;
            /* Suspend */
            case    USB_SUSPENDED_PROCESS:
                /* Suspend Sequence Number is 1 to 2 */
                usb_hstd_SuspCont(devaddr, mess->result);
                break;
            /* Enumeration */
            case    USB_DEFAULT:
                enume_mode = usb_hstd_Enumeration(mess->result);
                switch( enume_mode )
                {
                /* Detach Mode */
                case USB_NONDEVICE:
                    USB_PRINTF1("### Enumeration error (address%d)\n", usb_ghstd_DeviceAddr);
                    usb_ghstd_MgrMode[rootport] = USB_DETACHED;
                    break;

                case USB_NOTTPL:
                    USB_PRINTF1("### Not support device (address%d)\n", usb_ghstd_DeviceAddr);
                    usb_ghstd_MgrMode[rootport] = USB_DETACHED;
                    break;

                case USB_COMPLETEPIPESET:
                    usb_ghstd_MgrMode[rootport] = USB_CONFIGURED;
                    break;
                default:
                    break;
                }
                break;

            default:
                break;
            }
            break;

        case USB_MSG_MGR_AORDETACH:
            rootport    = mess->keyword;
            switch( mess->result )
            {
            case USB_DETACH:
#ifdef USB_HOST_COMPLIANCE_MODE
                USB_COMPLIANCE_DISP(USB_COMP_DETACH, USB_NO_ARG);
#endif /* USB_HOST_COMPLIANCE_MODE */
                USB_PRINTF1(" [Detach Device port%d] \n", rootport);
                usb_ghstd_MgrMode[rootport] = USB_DETACHED;
                usb_ghstd_DeviceSpeed = USB_NOCONNECT;

                for( md = 0; md < usb_ghstd_DeviceNum; md++ )
                {
                    driver = &usb_ghstd_DeviceDrv[md];
                    if( driver->devaddr == (rootport + USB_DEVICEADDR) )
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
                break;
            case USB_ATTACH:
#ifdef USB_HOST_COMPLIANCE_MODE
                USB_COMPLIANCE_DISP(USB_COMP_ATTACH, USB_NO_ARG);
#endif /* USB_HOST_COMPLIANCE_MODE */
                if( usb_ghstd_MgrMode[rootport] == USB_DETACHED )
                {
                    usb_ghstd_DeviceAddr = (uint16_t)(rootport + USB_DEVICEADDR);
                    if( USB_MAXDEVADDR < usb_ghstd_DeviceAddr )
                    {
                        /* For port1 */
                        USB_PRINTF0("Device address error\n");
                    }
                    else
                    {
                        usb_ghstd_MgrMode[rootport] = USB_DEFAULT;
                        r_usb_hstd_HciSetDeviceAddressOfRootpoot( rootport, usb_ghstd_DeviceAddr );
                        r_usb_hstd_HciPortReset(rootport);
                    }
                }
                break;
            default:
                break;
            }
            break;

        case USB_MSG_MGR_OVERCURRENT:
            rootport    = mess->keyword;
            USB_PRINTF0(" Please detach device \n ");
            USB_PRINTF1("VBUS off port%d\n", rootport);
            usb_ghstd_MgrMode[rootport] = USB_DEFAULT;
            for( md = 0; md < usb_ghstd_DeviceNum; md++ )
            {
                driver = &usb_ghstd_DeviceDrv[md];
                if( driver->rootport == rootport )
                {
                    USB_OVERCURRENT(rootport);
                    /* Root port */
                    driver->rootport    = USB_NOPORT;
                    /* Device address */
                    driver->devaddr     = USB_NODEVICE;
                    /* Device state */
                    driver->devstate    = USB_DETACHED;
                }
            }
            break;

        case USB_DO_GLOBAL_SUSPEND:
            devaddr = mess->keyword;
            usb_hstd_MgrSuspend(devaddr);
            break;

        case USB_DO_GLOBAL_RESUME:
            devaddr = mess->keyword;
            usb_hstd_MgrResume(devaddr);
            break;

        case USB_DO_CLR_STALL:
            pipenum = mess->keyword;
            usb_hstd_ClearStall(pipenum, mess->complete);
            break;

        default:
            USB_PRINTF0(" Unsupported MGR Message \n ");
            break;
        }
    }

    err = USB_REL_BLK(USB_MGR_MPL, mess);
    if( err != USB_OK )
    {
        USB_PRINTF1("### USB MGR rel_blk error: %d\n", mess->msginfo);
    }
}
/***********************************************************************************************************************
 End of function usb_hstd_MgrTask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       usb_hstd_SetLangId
 *
 *  Description:    Set Lanuguage ID of current device being enumerated
 *                  Function must be called just after language code request completes
 *
 *  Parameters:     void
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void usb_hstd_SetLangId(void)
{
    usb_ghstd_LangId  = (uint16_t)(usb_ghstd_ClassData[2]);
    usb_ghstd_LangId |= (uint16_t)((uint16_t)(usb_ghstd_ClassData[3]) << 8);
}
/***********************************************************************************************************************
 End of function usb_hstd_SetLangId
 **********************************************************************************************************************/