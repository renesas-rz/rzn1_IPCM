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
 * $Revision: 1304 $
 * $Date: 2019-02-25 18:06:01 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hdriverapi.c
 * Description  :  USB Host Control Driver API. USB Host transfer level commands.
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "r_usb_hhub_rzn1_if.h"
#include "r_usb_rzn1_config.h"
#include "r_usb_hcdc_rzn1_if.h"
#include "r_usb_hhci.h"
#include "r_sysctrl_rzn1_if.h"
#include "platform.h"
#include "iodefine.h"

/***********************************************************************************************************************
 Defines
 **********************************************************************************************************************/
#define USB_PPS_TIMEOUT                         1000

/***********************************************************************************************************************
 External variables and functions
 **********************************************************************************************************************/
extern void usb_hstd_TransferEndCb(void* utr_p, uint32_t actual_size, uint16_t status);
extern USB_PIPE_t usb_ghstd_pipe[USB_MAXPIPE+1u];     /* pipe information */
extern void usb_hstd_HciInterruptHandler(void);
extern void R_usb_hcdc_task(void);

/***********************************************************************************************************************
 Static variables and functions
 **********************************************************************************************************************/
/* Variable */
static USB_HCI_CB_INFO cb =
{
    &usb_hstd_AorDetachCb,
    &usb_hstd_AorDetachCb,
    &usb_hstd_OverCurrentCb,
    &usb_hstd_PortResetCb,
    &usb_hstd_TransferEndCb
};

/***********************************************************************************************************************
 Local functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_AhbPciBridgeInit
 *
 *  Description:    Setup PCI registers
 *
 *  Parameters:     none
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
static void R_usb_hstd_AhbPciBridgeInit(void)
{
    /* Make initial settings of AHB-PCI bridge PCI communication registers */
    USB_HOST->USBCTR.BIT.PCICLK_MASK = 0;
    USB_HOST->USBCTR.BIT.USBH_RST = 0;

    USB_HOST->AHB_BUS_CTR.BIT.SMODE_READY_CTR = 1;           /* Wait operation control in the slave */
    USB_HOST->AHB_BUS_CTR.BIT.MMODE_HBUSREQ = 1;             /* HBUSREQ output timing */
    USB_HOST->AHB_BUS_CTR.BIT.MMODE_WR_INCR = 1;             /* Condition for using undefined-length burst transfer */
    USB_HOST->AHB_BUS_CTR.BIT.MMODE_BYTE_BURST = 1;          /* 8- or 16 -bit burst transfer enable */
    USB_HOST->AHB_BUS_CTR.BIT.MMODE_HTRANS = 1;              /* HTRANS signal operating mode */

    USB_HOST->PCIAHB_WIN1_CTR.BIT.AHB_BASEADR = 0x0;         /* AHB bus base address */
    USB_HOST->PCIAHB_WIN1_CTR.BIT.PREFETCH = 3;              /* 16 beats max. for pre-fetch */

    USB_HOST->AHBPCI_WIN2_CTR.BIT.PCIWIN2_BASEADR = 0xA004;  /* PCI bus base address */
    USB_HOST->AHBPCI_WIN2_CTR.BIT.BURST_EN = 0;              /* PCI burst */
    USB_HOST->AHBPCI_WIN2_CTR.BIT.PCICMD = 3;                /* PCI command */

    USB_HOST->PCI_INT_STATUS.LONG = 0x00000000;
    USB_HOST->PCI_INT_ENABLE.LONG = 0x000B0000;

    USB_HOST->PCI_ARBITER_CTR.BIT.PCIBP_MODE = 1;            /* PCI bus parking mode */
    USB_HOST->PCI_ARBITER_CTR.BIT.PCIREQ0 = 1;               /* PCI request enable */
    USB_HOST->PCI_ARBITER_CTR.BIT.PCIREQ1 = 1;

    USB_HOST->USBCTR.BIT.PCI_AHB_WIN1_SIZE = 2;              /* Change the setting of PCI-AHB Windows1 area to 1Gbyte */
    USB_HOST->USBCTR.BIT.PCI_AHB_WIN2_EN = 0;                /* Can't use PCI-AHB Windows2 */

    /* Make initial settings of PCI configuration registers for AHB-PCI bridge */
    USB_HOST->AHBPCI_WIN1_CTR.LONG = 0x40000000;             /* PCI bus base address */
    USB_HOST->AHBPCI_WIN1_CTR.BIT.PCICMD = 5;                /* PCI command */

    USB_HOST->CMND_STS.CMND_STS_A.BIT.SERREN = 1;            /* PCI bus system error check */
    USB_HOST->CMND_STS.CMND_STS_A.BIT.PERREN = 1;            /* PCI bus parity error check */
    USB_HOST->CMND_STS.CMND_STS_A.BIT.MASTEREN = 1;          /* PCI bus master enable */
    USB_HOST->CMND_STS.CMND_STS_A.BIT.MEMEN = 1;             /* PCI bus memory area enable */
    USB_HOST->BASEAD.BASEAD_A.LONG = 0xA0050000;             /* PCI communication register base address */

    USB_HOST->WIN1_BASEAD.BIT.PCI_WIN1_BASEADR = 0;          /* PCI-AHB Windows1 base address */

    /* Make initial settings of PCI configuration registers for OHCI/EHCI */
    USB_HOST->AHBPCI_WIN1_CTR.LONG = 0x80000000;             /* PCI bus base address */
    USB_HOST->AHBPCI_WIN1_CTR.BIT.PCICMD = 5;                /* PCI command */

    USB_HOST->CMND_STS.CMND_STS_O.BIT.SERREnable = 1;        /* PCI bus system error check */
    USB_HOST->CMND_STS.CMND_STS_O.BIT.ParityErrorResponse = 1;  /* PCI bus parity error check */
    USB_HOST->CMND_STS.CMND_STS_O.BIT.BusMaster = 1;         /* PCI bus master enable */
    USB_HOST->CMND_STS.CMND_STS_O.BIT.MemorySpace = 1;       /* PCI bus memory area enable */
    USB_HOST->BASEAD.BASEAD_O.LONG = 0xA0040000;             /* OHCI Base Address */

    USB_HOST->CMND_STS_E.BIT.SERREnable = 1;                 /* PCI bus system error check */
    USB_HOST->CMND_STS_E.BIT.ParityErrorResponse = 1;        /* PCI bus parity error check */
    USB_HOST->CMND_STS_E.BIT.BusMaster = 1;                  /* PCI bus master enable */
    USB_HOST->CMND_STS_E.BIT.MemorySpace = 1;                /* PCI bus memory area enable */
    USB_HOST->BASEAD_E.LONG = 0xA0041000;                    /* EHCI Base Address */
}
/***********************************************************************************************************************
 End of function R_usb_hstd_AhbPciBridgeInit
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Renesas USB Host Driver API functions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_get_major_version_num
 *
 *  Description:    Returns major version number of USB host basic driver
 *
 *  Parameters:     void
 *
 *  Return value:   Major version number
 *
 **********************************************************************************************************************/
uint8_t R_usb_hstd_get_major_version_num(void)
{
    uint8_t major_ver_num = (uint8_t)USBH_DRIVER_MAJOR_VERSION_NUMBER;

    return major_ver_num;
}
/***********************************************************************************************************************
 End of function R_usb_hstd_get_major_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_get_minor_version_num
 *
 *  Description:    Returns minor version number of USB host basic driver
 *
 *  Parameters:     void
 *
 *  Return value:   Minor version number
 *
 **********************************************************************************************************************/
uint8_t R_usb_hstd_get_minor_version_num(void)
{
    uint8_t minor_ver_num = (uint8_t)USBH_DRIVER_MINOR_VERSION_NUMBER;

    return minor_ver_num;
}
/***********************************************************************************************************************
 End of function R_usb_hstd_get_minor_version_num
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USBh_Init
 *
 *  Description:    Initialise USB Host bare metal driver
 *
 *  Description:    Call system controller to initialise USB Host Controller
 *
 *  Description:    Register USBh interrupt handler,  Startup USBh
 *
 *  Parameters:     void
 *
 *  Return value:   ER_RET - Error Status
 *
 **********************************************************************************************************************/
ER_RET R_USBh_Init(void)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num;
    uint32_t int_priority = USB_HOST_INT_PRIORITY;

    /* Initialise USB function controller  */
    ret_val = R_SYSCTRL_EnableUSBh();
    if (ER_OK == ret_val)
    {
        /* AHB-PCI Bridge setting */
        R_usb_hstd_AhbPciBridgeInit();

        /* MGR Open */
        R_usb_hstd_MgrOpen();
        /* HUB Open */
        R_usb_cstd_SetTaskPri(USB_HUB_TSK, USB_PRI_3);
        R_USB_HHUB_Registration(USB_NULL);

        /* Register interrupt handler for USBH */
        irq_num = (IRQn_Type)RZN1_IRQ_USBH_BIND;
        if (R_BSP_InterruptRegisterCallback(irq_num,(bsp_int_cb_t) &usb_hstd_HciInterruptHandler) == MCU_INT_SUCCESS)
        {
            ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_SET_INTERRUPT_PRIORITY, &int_priority);
            if (MCU_INT_SUCCESS != ret_val)
            {
                ret_val = ER_SYS;
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
 End of function R_USBh_Init
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USBh_Open
 *
 *  Description:    Enable USBh interrupts. Turn On Power
 *
 *  Parameters:     void
 *
 *  Return value:   Error status
 *
 **********************************************************************************************************************/
ER_RET R_USBh_Open(void)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num;
    uint32_t timeout = 0;

    irq_num = (IRQn_Type)RZN1_IRQ_USBH_BIND;
    ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_ENABLE, FIT_NO_PTR);

    /* Power up USBh */
    if (ER_OK == ret_val)
    {
        USB_HOST->HcRhPortStatus1.HcRhPortStatus1_A.BIT.SPP = 1;
        USB_HOST->PORTSC1.BIT.PP = 1;

        while(0 == USB_HOST->HcRhPortStatus1.HcRhPortStatus1_B.BIT.PPS)
        {
            if(timeout > USB_PPS_TIMEOUT)
            {
                USB_PRINTF0( "Error : usb_hstd_OhciHwSetup TIMEOUT\n" );
                return ER_TIMEOUT;
            }
            r_usb_hstd_HciWaitTime( 1 );
            timeout++;
        }
    }

#ifdef USB_CFG_HCDC_USE
    /* CDC APL Init */
    R_USB_HCDC_Init();
#endif
    return ret_val;
}
/***********************************************************************************************************************
 End of function R_USBh_Open
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USBh_Close
 *
 *  Description:    Prepare USB function port for connection to USB Host
 *
 *  Parameters:     void
 *
 *  Return value:   Error status
 *
 **********************************************************************************************************************/
ER_RET R_USBh_Close(void)
{
    ER_RET ret_val = ER_OK;
    IRQn_Type irq_num;

    irq_num = (IRQn_Type)RZN1_IRQ_USBH_BIND;
    ret_val = R_BSP_InterruptControl(irq_num, MCU_INT_CMD_INTERRUPT_DISABLE, FIT_NO_PTR);

    /* Power down USBh */
    USB_HOST->HcRhPortStatus1.HcRhPortStatus1_A.BIT.CPP = 1;
    USB_HOST->PORTSC1.BIT.PP = 0;

    return ret_val;
}
/***********************************************************************************************************************
 End of function R_USBh_Close
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_USBh_PollTask
 *
 *  Description:    Poll all sub-tasks associated with running this host
 *
 *  Parameters:     void
 *
 *  Return value:   void
 *
 **********************************************************************************************************************/
void R_USBh_PollTask(void)
{
    /* Scheduler */
    R_usb_cstd_Scheduler();

    if( USB_FLGSET == R_usb_cstd_CheckSchedule() )
    {
        R_usb_hstd_MgrTask();       /* MGR task */
        R_USB_HHUB_Task();          /* HUB task */
#ifdef USB_CFG_HCDC_USE
        R_usb_hcdc_task();          /* HCDC task */
#endif
    }

#ifdef USB_CFG_HCDC_USE
    R_USB_HCDC_InterfaceTask();
#endif

    return;
}
/***********************************************************************************************************************
 End of function R_USBh_PollTask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_TransferStart
 *
 *  Description:    Request HCD to transfer data. HCD will transfer the data
 *                   based on the transfer information stored in ptr.
 *
 *  Parameters:     USB_UTR_t *utrmsg    : USB system internal structure.
 *
 *  Return value:   USB_ER_t  error code : USB_OK/USB_ERROR/USB_ERROR.
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hstd_TransferStart(USB_UTR_t *utr)
{
    USB_ER_t        err;

    err = usb_hstd_TransferStart(utr);

    return err;
}
/***********************************************************************************************************************
 End of function R_usb_hstd_TransferStart
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_TransferEnd
 *
 *  Description:    Request HCD to force termination of data transfer.
 *
 *  Parameters:     uint16_t pipe_id      : PipeID
 *
 *  Return value:   USB_ER_t error code   : USB_OK etc
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hstd_TransferEnd(uint16_t pipe_id)
{
    USB_ER_t        err;

    err = usb_hstd_TransferEnd(pipe_id);

    return err;
}
/***********************************************************************************************************************
 End of function R_usb_hstd_TransferEnd
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_DriverRegistration
 *
 *  Description:    The HDCD information registered in the class driver structure is registered in HCD.
 *
 *  Parameters:     USB_HCDREG_t *callback    : class driver structure
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hstd_DriverRegistration(USB_HCDREG_t *callback)
{
    USB_HCDREG_t    *driver;

    if( usb_ghstd_DeviceNum <= USB_MAXDEVADDR )
    {
        driver = &usb_ghstd_DeviceDrv[usb_ghstd_DeviceNum];
        /* Root port */
        driver->rootport    = USB_NOPORT;
        /* Device address */
        driver->devaddr     = USB_NODEVICE;
        /* Device state */
        driver->devstate    = USB_DETACHED;
        /* Interface Class */
        driver->ifclass     = callback->ifclass;
        /* Target peripheral list */
        driver->tpl         = callback->tpl;
        /* Driver check */
        driver->classcheck  = callback->classcheck;
        /* Device configured */
        driver->devconfig   = callback->devconfig;
        /* Device detach */
        driver->devdetach   = callback->devdetach;
        /* Device suspend */
        driver->devsuspend  = callback->devsuspend;
        /* Device resume */
        driver->devresume   = callback->devresume;

        usb_ghstd_DeviceNum++;
        USB_PRINTF1("*** Registration driver 0x%02x\n",driver->ifclass);
        return USB_OK;
    }
    else
    {
        USB_PRINTF0("### Registration device driver over\n");
        return USB_ERROR;
    }
}
/***********************************************************************************************************************
 End of function R_usb_hstd_DriverRegistration
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_ReturnEnuMGR
 *
 *  Description:    Continuous enumeration is requested to MGR task (API for nonOS)
 *
 *  Parameters:     uint16_t cls_result   : class check result
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void R_usb_hstd_ReturnEnuMGR(uint16_t cls_result)
{
    usb_ghstd_CheckEnuResult = cls_result;
    usb_hstd_MgrSndMbx(USB_MSG_MGR_SUBMITRESULT, USB_PIPE0, USB_CTRL_END);
}
/***********************************************************************************************************************
 End of function R_usb_hstd_ReturnEnuMGR
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_SetPipe
 *
 *  Description:    SetPipe
 *
 *  Parameters:     uint16_t **table : Data table pointer.
 *                  table[0] : Device Descriptor
 *                  table[1] : Configuration Descriptor
 *                  table[2] : Interface Descriptor
 *                  table[3] : Class check result
 *                  table[4] : HUB device speed
 *                  table[5] : Root port
 *                  table[6] : Device speed
 *                  table[7] : Device address
 *
 *  Return value:   USB_ER_t                   : USB_OK etc
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hstd_SetPipe(uint16_t **table)
{
    uint8_t     *p_condesc;
    uint8_t     *desc_offset;
    uint8_t     *descriptor;
    uint16_t    total_len;
    uint16_t    index;
    USB_PIPE_t  *pipe;
    uint16_t    pipe_id = 0;
    uint8_t     ifnum;

    /* usb_ghstd_pipe[0] is Default Control Pipe */
    pipe = &usb_ghstd_pipe[1];

    /* Done ClassCheck */
    *table[3]  = USB_OK;

    p_condesc = (uint8_t*)((uint16_t*)table[1]);

    /* Configuration Descriptor + Interface Descriptor + Endpoint Descriptor */
    total_len = (uint16_t)(p_condesc[USB_CON_W_TOTAL_LENGTH_H] << 8) | (uint16_t)(p_condesc[USB_CON_W_TOTAL_LENGTH_L]);
    index     = USB_DEV_B_LENGTH;

    desc_offset = p_condesc;

    while(index < total_len)
    {
        /* index will always point to the beginning of the Descriptor */
        descriptor = &desc_offset[index];
        /* Check Descriptor Type */
        switch(descriptor[USB_DEV_B_DESCRIPTOR_TYPE])
        {
        case USB_DT_INTERFACE:
            ifnum = descriptor[USB_IF_B_INTERFACENUMBER];
            break;
        case USB_DT_ENDPOINT:
            /* Search Empty Pipe */
            while( pipe->epnum != 0 )
            {
                pipe++;
                pipe_id++;
                if( pipe_id > USB_MAXPIPE )
                {
                    USB_PRINTF0("PIPE_FULL ERROR\n");
                    return USB_ERROR;
                }
            }
            /* Get value from Endpoint Descriptor */
            pipe->epnum     = (descriptor[USB_EP_B_EPADDRESS] & USB_EP_NUMMASK);
            pipe->direction = (descriptor[USB_EP_B_EPADDRESS] & USB_EP_DIRMASK);
            pipe->type      = (descriptor[USB_EP_B_ATTRIBUTES] & USB_EP_TRNSMASK);
            pipe->mps       = (uint16_t)(descriptor[USB_EP_W_MPS_H] << 8) | (uint16_t)(descriptor[USB_EP_W_MPS_L]);
            /* Get value from Attach Info */
            pipe->devaddr   = *table[7];
            pipe->ifnum     = ifnum;
            break;

        default:
            break;
        }
        /* Next Descriptor */
        index += desc_offset[index];
    }

    return USB_OK;
}
/***********************************************************************************************************************
 End of function R_usb_hstd_SetPipe
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_GetPipeID
 *
 *  Description:    Return PipeID from PipeTable
 *
 *  Parameters:     uint16_t devaddr  : Device Address
 *                  uint8_t type      : Endpoint Type
 *                  uint8_t direction : Endpoint Direction
 *                  uint8_t ifnum     : Interface Number
 *
 *  Return value:   uint16_t : PipeID
 *
 **********************************************************************************************************************/
uint16_t R_usb_hstd_GetPipeID(uint16_t devaddr, uint8_t type, uint8_t direction, uint8_t ifnum)
{
    uint16_t pipe_id;

    for( pipe_id = 1; pipe_id < USB_MAXPIPE; pipe_id++ )
    {
        if( usb_ghstd_pipe[pipe_id].devaddr == devaddr )
        {
            if( usb_ghstd_pipe[pipe_id].type == type )
            {
                if( usb_ghstd_pipe[pipe_id].direction == direction )
                {
                    if( ifnum == 0xFF )
                    {
                        return pipe_id;
                    }
                    else
                    {
                        if( usb_ghstd_pipe[pipe_id].ifnum == ifnum )
                        {
                            return pipe_id;
                        }
                    }
                }
            }
        }
    }

    return 0;
}
/***********************************************************************************************************************
 End of function R_usb_hstd_GetPipeID
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_ClearPipe
 *
 *  Description:    ClearPipe
 *
 *  Parameters:     uint16_t devaddr : Device Address
 *
 *  Return value:   USB_ER_t                   : USB_OK etc
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hstd_ClearPipe(uint16_t devaddr)
{
    uint16_t pipe_id;

    for( pipe_id = 1; pipe_id < USB_MAXPIPE; pipe_id++ )
    {
        if( usb_ghstd_pipe[pipe_id].devaddr == devaddr )
        {
            usb_ghstd_pipe[pipe_id].ifnum     = 0;
            usb_ghstd_pipe[pipe_id].epnum     = 0;
            usb_ghstd_pipe[pipe_id].direction = 0;
            usb_ghstd_pipe[pipe_id].type      = 0;
            usb_ghstd_pipe[pipe_id].mps       = 0;
            usb_ghstd_pipe[pipe_id].devaddr   = 0;
        }
    }

    return USB_OK;
}
/***********************************************************************************************************************
 End of function R_usb_hstd_ClearPipe
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_MgrOpen
 *
 *  Description:    Initialize Manager(MGR) task
 *
 *  Parameters:     none
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
USB_ER_t R_usb_hstd_MgrOpen(void)
{
    USB_ER_t        err=USB_OK;
    USB_HCDREG_t    *driver;
    uint16_t        i;

    /* Scheduler init */
    usb_cstd_ScheInit();

    /* Manager Mode */
    usb_ghstd_MgrMode[USB_PORT0]   = USB_DETACHED;
    usb_ghstd_DeviceSpeed  = USB_NOCONNECT;
    /* Device address */
    usb_ghstd_DeviceAddr   = USB_DEVICE_0;
    /* Device driver number */
    usb_ghstd_DeviceNum        = 0;

    for( i = 0; i < (USB_MAXDEVADDR + 1u); i++ )
    {
        driver  = &usb_ghstd_DeviceDrv[i];
        /* Root port */
        driver->rootport            = USB_NOPORT;
        /* Device address */
        driver->devaddr             = USB_NODEVICE;
        /* Device state */
        driver->devstate            = USB_DETACHED;
        /* Interface Class : NO class */
        driver->ifclass             = (uint16_t)USB_IFCLS_NOT;
    }

    R_usb_cstd_SetTaskPri(USB_MGR_TSK, USB_PRI_2);

    /* EHCI/OHCI init */
    r_usb_hstd_HciInit(&cb);

    R_usb_cstd_SetTaskPri(USB_HCI_TSK, USB_PRI_1);

    return err;
}
/***********************************************************************************************************************
 End of function R_usb_hstd_MgrOpen
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_hstd_MgrTask
 *
 *  Description:    Call MGR(Manager) task (API for nonOS)
 *
 *  Parameters:     none
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void R_usb_hstd_MgrTask(void)
{
    usb_hstd_MgrTask();
}
/***********************************************************************************************************************
 End of function R_usb_hstd_MgrTask
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *
 *  Function:       R_usb_cstd_DelayXms
 *
 *  Description:    Software Wait Timer
 *
 *  Parameters:     uint32_t ms   : msec
 *
 *  Return value:   none
 *
 **********************************************************************************************************************/
void R_usb_cstd_DelayXms(uint32_t ms)
{
    r_usb_hstd_HciWaitTime(ms);
}
/***********************************************************************************************************************
 End of function R_usb_cstd_DelayXms
 **********************************************************************************************************************/