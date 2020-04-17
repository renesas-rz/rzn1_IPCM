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
 * $Revision: 1297 $
 * $Date: 2019-02-22 17:18:43 +0000 (Fri, 22 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hOhciTypedef.h
 * Description  :  USB OHCI Type define Header
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __USB_HOHCITYPEDEF_H__
#define __USB_HOHCITYPEDEF_H__

/***********************************************************************************************************************
 Definitions
 **********************************************************************************************************************/
#define USB_OHCI_SHAREDMEMORYTYPE               USB_OHCI_SHAREDMEMORYTYPE_PCI   /* Shared Memory Type */
#define USB_OHCI_SHAREDMEMORY_OFFSET            0x00000000                      /* Shared Memory Offset */

#define USB_OHCI_NUM_REQUEST                    USB_HCI_TRREQ_NUM               /* The maximum number of Transfer Request memory */

#define USB_OHCI_MAXDEVICE                      USB_HCI_DEVICE_NUM              /* The maximum number of OHCI Device */

#define USB_OHCI_MAXENDPOINT                    16                              /* The maximum number of OHCI Endpoint No. */

#define USB_OHCI_NUM_DEVICEDATA                 1                               /* The maximum number of Dvice Data */

#define USB_OHCI_MAXROOTPORTS                   1                               /* The maximum number of OHCI Rootport */

#define USB_OHCI_MAXTDSIZE                      0x00002000                      /* Max Transfer Descriptor Size */

#define USB_OHCI_MAXIMUM_OVERHEAD               210                             /* The maximum number of OHCI Isochronous Overhead */

#define USB_OHCI_ISO_MAX_FRAME                  8                               /* The maximum number of OHCI Isochronous Frame Size */

#define USB_OHCI_SHAREDMEMORYTYPE_EXCLUSIVE     0       /* Exclusive Shared Memory Type */
#define USB_OHCI_SHAREDMEMORYTYPE_COMMOM        1       /* Common Shared Memory Type */
#define USB_OHCI_SHAREDMEMORYTYPE_PCI           2       /* PCI Shared Memory Type */

// TD->TDStatus
#define USB_OHCI_TD_NOTFILLED                   0       /* NOTFILLED */
#define USB_OHCI_TD_CANCELED                    1       /* CANCELED */
#define USB_OHCI_TD_COMPLETED                   2       /* COMPLETED */
#define USB_OHCI_TD_PENDING                     3       /* PENDING */

// TD ConditionCode
#define USB_OHCI_CC_NOERROR                     0x0     /* NOERROR */
#define USB_OHCI_CC_CRC                         0x1     /* CRC */
#define USB_OHCI_CC_BITSTUFFING                 0x2     /* BITSTUFFING */
#define USB_OHCI_CC_DATATOGGLEMISMATCH          0x3     /* DATATOGGLEMISMATCH */
#define USB_OHCI_CC_STALL                       0x4     /* STALL */
#define USB_OHCI_CC_DEVICENOTRESPOND            0x5     /* DEVICENOTRESPOND */
#define USB_OHCI_CC_PIDCHECKFAILURE             0x6     /* PIDCHECKFAILURE */
#define USB_OHCI_CC_UNEXPECTEDPID               0x7     /* UNEXPECTEDPID */
#define USB_OHCI_CC_DATAOVERRUN                 0x8     /* DATAOVERRUN */
#define USB_OHCI_CC_DATAUNDERRUN                0x9     /* DATAUNDERRUN */
#define USB_OHCI_CC_BUFFEROVERRUN               0xC     /* BUFFEROVERRUN */
#define USB_OHCI_CC_BUFFERUNDERRUN              0xD     /* BUFFERUNDERRUN */
#define USB_OHCI_CC_NOTACCESSED                 0xF     /* NOTACCESSED */

// Request->Status
#define USB_OHCI_RS_NORMAL_COMPLETION           0x00    /* NORMAL COMPLETION */
#define USB_OHCI_RS_NOT_DONE                    0x10    /* NOT DONE */
#define USB_OHCI_RS_NOT_REQUESTED               0x11    /* NOT REQUESTED */
#define USB_OHCI_RS_CANCELING                   0x12    /* CANCELING */
#define USB_OHCI_RS_CANCELED                    0x13    /* CANCELED */

// HC_Transfer_Control.DP
#define USB_OHCI_PID_SETUP                      0       /* SETUP */
#define USB_OHCI_PID_OUT                        1       /* OUT */
#define USB_OHCI_PID_IN                         2       /* IN */

// Regs
#define USB_OHCI_CONTROLLISTFILLED              0x00000002  /* Control */
#define USB_OHCI_BULKLISTFILLED                 0x00000004  /* Bulk */

// For usb_hstd_OhciScanContainingRecord()
#define USB_OHCI_CR_ENDPOINT_DESCRIPTOR         0       /* ENDPOINT DESCRIPTOR */
#define USB_OHCI_CR_TRANSFER_DESCRIPTOR         1       /* TRANSFER DESCRIPTOR */

#define USB_OHCI_CR_LINK                        0       /* LINK */
#define USB_OHCI_CR_REQUESTLIST                 1       /* REQUEST LIST */
#define USB_OHCI_CR_PAUSEDLINK                  2       /* PAUSED LINK */

// Others
#define USB_OHCI_HC_INT_SOF                     0x00000004  /* SOF */

// InterruptStatus
#define USB_OHCI_IS_SCHEDULINGOVERRUN           0x00000001  /* SCHEDULINGOVERRUN */
#define USB_OHCI_IS_WRITEBACKDONEHEAD           0x00000002  /* WRITEBACKDONEHEAD */
#define USB_OHCI_IS_STARTOFFRAME                0x00000004  /* STARTOFFRAME */
#define USB_OHCI_IS_RESUMEDETECTED              0x00000008  /* RESUMEDETECTED */
#define USB_OHCI_IS_UNRECOVERABLERROR           0x00000010  /* UNRECOVERABLERROR */
#define USB_OHCI_IS_FRAMENUMBEROVERRUN          0x00000020  /* FRAMENUMBEROVERRUN */
#define USB_OHCI_IS_ROOTHUBSTATUSCHANGE         0x00000040  /* ROOTHUBSTATUSCHANGE */
#define USB_OHCI_IS_OWNERSHIPCHANGE             0x40000000  /* OWNERSHIPCHANGE */
#define USB_OHCI_IS_MASTERINTENABLE             0x80000000  /* MASTERINTENABLE */

#define USB_OHCI_ISOCHRONOUSENABLE              0x00000008  /* ISOCHRONOUS ENABLE */
#define USB_OHCI_BULKLISTENABLE                 0x00000020  /* BULK LIST ENABLE */
#define USB_OHCI_CONTROLLISTENABLE              0x00000010  /* CONTROL LIST ENABLE */

//
// The different ED lists are as follows.
//
#define USB_OHCI_ED_INTERRUPT_1ms               0           /* For Interrupt( Polling rate = 1ms ) */
#define USB_OHCI_ED_INTERRUPT_2ms               1           /* For Interrupt( Polling rate = 2ms ) */
#define USB_OHCI_ED_INTERRUPT_4ms               3           /* For Interrupt( Polling rate = 4ms ) */
#define USB_OHCI_ED_INTERRUPT_8ms               7           /* For Interrupt( Polling rate = 8ms ) */
#define USB_OHCI_ED_INTERRUPT_16ms              15          /* For Interrupt( Polling rate = 16ms ) */
#define USB_OHCI_ED_INTERRUPT_32ms              31          /* For Interrupt( Polling rate = 32ms ) */
#define USB_OHCI_ED_CONTROL                     63          /* For Control */
#define USB_OHCI_ED_BULK                        64          /* For Bulk */
#define USB_OHCI_ED_ISOCHRONOUS                 0           /* For Isochronous( same as 1ms interrupt queue ) */
#define USB_OHCI_NO_ED_LISTS                    65          /* No ED Lists */
#define USB_OHCI_ED_EOF                         0xff        /* ED EOF */

#define USB_OHCI_HCED_HEADP_HALT                0x00000001  /* hardware stopped bit */
#define USB_OHCI_HCED_HEADP_CARRY               0x00000002  /* hardware toggle carry bit */

/***********************************************************************************************************************
 Typedefs for OHCI
 **********************************************************************************************************************/
#define boolean_t                               uint8_t

/***********************************************************************************************************************
 5.2.2 Miscellaneous Definitions
 **********************************************************************************************************************/

//
// Doubly linked list
//
typedef struct _USB_OHCI_LIST_ENTRY {
    struct  _USB_OHCI_LIST_ENTRY    *Flink;
    struct  _USB_OHCI_LIST_ENTRY    *Blink;
} USB_OHCI_LIST_ENTRY, *USB_OHCI_LIST_ENTRY_P;

/***********************************************************************************************************************
 5.2.3 Host Controller Descriptors Definitions
 **********************************************************************************************************************/

typedef struct  _USB_OHCI_HC_ENDPOINT_CONTROL {
    uint32_t        FA:7;       /*  Function Address    7bit    0-127   */
    uint32_t        EN:4;       /*  EndPoint No.        4bit    0-15    */
    uint32_t        D:2;        /*  Direction           2bit    D=0,3:get direction from TD ,   */
                                /*                              D=1:OUT , D=2:IN                */
    uint32_t        S:1;        /*  SPEED               1bit    S=0:full speed,S=1:low speed    */
    uint32_t        K:1;        /*  SKIP                1bit    K=1:go to the next ED           */
    uint32_t        F:1;        /*  Format              1bit    F=1:isochronous,F=0:others      */
    uint32_t        MPS:16;     /*  MaxPacketSize       11bit   0-2047  */
} USB_OHCI_HC_ENDPOINT_CONTROL, *USB_OHCI_HC_ENDPOINT_CONTROL_P;

typedef struct  _USB_OHCI_HC_TRANSFER_CONTROL {
    uint32_t        dummy1:16;  /*  dummy   */
    uint32_t        dummy:2;    /*  dummy   */
    uint32_t        R:1;        /*  Buffer Rounding  0:must exactly define buffer               */
                                /*                   1: smaller packet than buffer not error    */
    uint32_t        DP:2;       /*  Direction PID  00:SETUP,    */
                                /*                 01:OUT ,     */
                                /*                 10:IN  ,     */
                                /*                 11:reserved  */
    uint32_t        IntD:3;     /*  Delay Interrupt    111:no interrupt */
    uint32_t        Toggle:2;   /*  Data toggle, T= 0x:acquired from ED toggle carry, */
                                /*                  10:DATA0,   */
                                /*                  11:DATA1    */
    uint32_t        EC:2;       /*  Error count */
    uint32_t        CC:4;       /*  condition code  */
} USB_OHCI_HC_TRANSFER_CONTROL, *USB_OHCI_HC_TRANSFER_CONTROL_P;

//
// Host Controller Endpoint Descriptor, refer to Section 4.2, Endpoint Descriptor
//
typedef struct _USB_OHCI_HC_ENDPOINT_DESCRIPTOR {
    USB_OHCI_HC_ENDPOINT_CONTROL    Control;    //  dword 0
    uint32_t                        TailP;      //  physical pointer to USB_OHCI_HC_TRANSFER_DESCRIPTOR
    uint32_t                        HeadP;      //  flags + phys ptr to USB_OHCI_HC_TRANSFER_DESCRIPTOR
    uint32_t                        NextED;     //  phys ptr to USB_OHCI_HC_ENDPOINT_DESCRIPTOR
} USB_OHCI_HC_ENDPOINT_DESCRIPTOR, *USB_OHCI_HC_ENDPOINT_DESCRIPTOR_P;

//
// Host Controller Transfer Descriptor, refer to Section 4.3, Transfer Descriptors
//
typedef struct _USB_OHCI_HC_TRANSFER_DESCRIPTOR {
    struct _USB_OHCI_HC_TRANSFER_CONTROL    Control;    // dword 0
    uint32_t                                CBP;        // current buffer pointer
    uint32_t                                NextTD;     // phys ptr to USB_OHCI_HC_TRANSFER_DESCRIPTOR
    uint32_t                                BE;         // buffer end
} USB_OHCI_HC_TRANSFER_DESCRIPTOR, *USB_OHCI_HC_TRANSFER_DESCRIPTOR_P;



/***********************************************************************************************************************
 5.2.6 Host Controller Driver Internal Definitions
 **********************************************************************************************************************/

//
// OHCI USBD Transfer Request
//
typedef struct _USB_OHCI_REQUEST {
    uint8_t                 *Buffer;            /* Pointer to data to be transferred */
    uint32_t                BufferLength;       /* Length of data buffer in bytes */
    uint8_t                 XferInfo;           /* Direction (In/Out) for control and bulk */
    uint8_t                 MaxIntDelay;        /* Maximum allowable delay from completion to completion notification to USBD */
    uint8_t                 ShortXferOk;        /* Transfer of less than BufferLength is to be treated as an error unless this is TRUE */
    uint8_t                 UsingFlag;          /* Using Flag */
    uint8_t                 *Setup;             /* Data for setup packet (control endpoints only) */
    uint32_t                Status;             /* Completion status from HCD to USBD */
    USB_OHCI_LIST_ENTRY     HcdList;            /* List of all HCD_TRANSFER_DESCRIPTORs in use for this request */
    uint32_t                *DriverRequest;     /* Driver Request Information pointer */
} USB_OHCI_REQUEST, *USB_OHCI_REQUEST_P;

//
// Each Host Controller Endpoint Descriptor is also doubly linked into a list tracked by HCD.
// Each ED queue is managed via an USB_OHCI_HCD_ED_LIST
//
typedef struct _USB_OHCI_HCD_ED_LIST {
    USB_OHCI_LIST_ENTRY     Head;               /* Head of an HCD_ENDPOINT_DESCRIPTOR list */
    uint32_t                *PhysicalHead;      /* Address of location to put the physical head pointer when it changes */
    uint16_t                Bandwidth;          /* Allocated bandwidth on this time-slice. */
    uint8_t                 Next;               /* Index to the next HCD_ED_LIST for this time-slice */
    uint8_t                 Reserved;
} USB_OHCI_HCD_ED_LIST, *USB_OHCI_HCD_ED_LIST_P;


/* Refer to Section 4.4 Host Controller Communications Area */
typedef struct _USB_OHCI_HCCA_BLOCK {
    uint32_t                HccaInterruptList[32];
    uint32_t                HccaFrameNumber:16;
    uint32_t                HccaPad1:16;
    uint32_t                HccaDoneHead;
    uint32_t                reserve[30];
} USB_OHCI_HCCA_BLOCK, *USB_OHCI_HCCA_BLOCK_P;

//
// HCD Device Data( Refer to Section 5.2.6 Host Controller Driver Internal Definitions )
//
typedef struct _USB_OHCI_HCD_DEVICE_DATA {

    USB_OHCI_HCCA_BLOCK_P   HCCA;
    USB_OHCI_LIST_ENTRY     Endpoints;
    USB_OHCI_LIST_ENTRY     FreeED;
    USB_OHCI_LIST_ENTRY     FreeTD;
    USB_OHCI_LIST_ENTRY     StalledEDReclamation;
    USB_OHCI_LIST_ENTRY     RunningEDReclamation;
    USB_OHCI_LIST_ENTRY     PausedEDRestart;
    USB_OHCI_HCD_ED_LIST    EdList[USB_OHCI_NO_ED_LISTS];
    uint32_t                FrameHighPart;
    uint32_t                AvailableBandwidth;
    uint32_t                MaxBandwidthInUse;
    uint32_t                SOCount;
    uint32_t                SOStallFrame;
    uint32_t                SOLimitFrame;
    uint8_t                 SOLimitHit;
    uint8_t                 SOStallHit;
    uint8_t                 RootDevice[USB_OHCI_MAXROOTPORTS];
    uint8_t                 UsingFlag;
} USB_OHCI_HCD_DEVICE_DATA, *USB_OHCI_HCD_DEVICE_DATA_P;



/***********************************************************************************************************************
 5.2.5 Host Controller Endpoints
 **********************************************************************************************************************/

/* Ext. struct */
typedef struct _USB_OHCI_ISO_TRANSFER_INFO {
    uint16_t                Size;               /* Transfer Size */
    uint8_t                 Control_Cc;         /* Control CC */
    uint8_t                 Psw_Cc;             /* PSW CC */
    uint8_t                 *Buffer;            /* Data Buffer pointer */
} USB_OHCI_ISO_TRANSFER_INFO, *USB_OHCI_ISO_TRANSFER_INFO_P;

/* Ext. struct */
typedef struct _USB_OHCI_ISO_INFO {
    uint8_t                 UsingFlag;          /* Using Flag */
    uint8_t                 CopyCnt;            /* Data copy count( for out ) */
    uint8_t                 StartCnt;           /* Transfer start count( for in/out ) */
    uint8_t                 EndCnt;             /* Transfer end count( for in/out ) */
    uint8_t                 Copy_p;             /* Data copy information pointer( for out ) */
    uint8_t                 Start_p;            /* Transfer start information pointer( for in/out ) */
    uint8_t                 End_p;              /* Transfer end information pointer( for in/out ) */
    uint8_t                 Complete_p;         /* Transfer complete information pointer( for in/out ) */
    USB_OHCI_REQUEST_P      UsbdRequest;        /* USBD Transfer Request pointer */
    USB_OHCI_ISO_TRANSFER_INFO  TransferInfo[ USB_OHCI_ISO_MAX_FRAME ]; /* Transfer information */
} USB_OHCI_ISO_INFO, *USB_OHCI_ISO_INFO_P;

typedef struct _USB_OHCI_HCD_ENDPOINT {
    uint8_t                                     Type;
    uint8_t                                     ListIndex;
    uint8_t                                     UsingFlag;
    uint8_t                                     Reserved[1];
    USB_OHCI_HCD_DEVICE_DATA_P                  DeviceData;
    USB_OHCI_HC_ENDPOINT_CONTROL                Control;
    struct _USB_OHCI_HCD_ENDPOINT_DESCRIPTOR    *HcdED;
    struct _USB_OHCI_HCD_TRANSFER_DESCRIPTOR    *HcdHeadP;
    struct _USB_OHCI_HCD_TRANSFER_DESCRIPTOR    *HcdTailP;
    uint32_t                                    Rate;
    uint32_t                                    Bandwidth;
    uint32_t                                    MaxPacket;
    USB_OHCI_LIST_ENTRY                         Link;           //  Ext.
    USB_OHCI_ISO_INFO_P                         IsoInfo;        //  Ext.
} USB_OHCI_HCD_ENDPOINT, *USB_OHCI_HCD_ENDPOINT_P;


/***********************************************************************************************************************
 5.2.4 Host Controller Driver Descriptor Definitions
 **********************************************************************************************************************/

//
// HCD Endpoint Descriptor
//
typedef struct _USB_OHCI_HCD_ENDPOINT_DESCRIPTOR {
    uint8_t                     ListIndex;
    uint8_t                     PausedFlag;
    uint8_t                     UsingFlag;
    uint8_t                     Reserved[1];
    uint32_t                    PhysicalAddress;
    USB_OHCI_LIST_ENTRY         Link;
    USB_OHCI_HCD_ENDPOINT_P     Endpoint;
    uint32_t                    ReclamationFrame;
    USB_OHCI_LIST_ENTRY         PausedLink;
    USB_OHCI_HC_ENDPOINT_DESCRIPTOR HcED;
} USB_OHCI_HCD_ENDPOINT_DESCRIPTOR, *USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P;

//
// HCD Transfer Descriptor
//
typedef struct _USB_OHCI_HCD_TRANSFER_DESCRIPTOR {
    uint8_t                                         TDStatus;
    uint8_t                                         UsingFlag:4;
    uint8_t                                         CancelPending:4;
    uint32_t                                        PhysicalAddress;
    struct _USB_OHCI_HCD_TRANSFER_DESCRIPTOR        *NextHcdTD;
    USB_OHCI_LIST_ENTRY                             RequestList;
    struct _USB_OHCI_REQUEST                        *UsbdRequest;
    USB_OHCI_HCD_ENDPOINT_P                         Endpoint;
    uint32_t                                        TransferCount;
    USB_OHCI_HC_TRANSFER_DESCRIPTOR                 HcTD;
    uint32_t                                        Dummy[4];
} USB_OHCI_HCD_TRANSFER_DESCRIPTOR, *USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P;

//
// HCD Transfer Descriptor for Isochronous
//
typedef struct _USB_OHCI_HC_ISO_TRANSFER_CONTROL {
    uint32_t                SF:16;      /*  StartingFrame   */
    uint32_t                dummy2:5;
    uint32_t                IntD:3;     /*  Delay Interrupt    111:no interrupt */
    uint32_t                FC:3;       /*  Frame count */
    uint32_t                dummy:1;
    uint32_t                CC:4;       /*  condition code  */
} USB_OHCI_HC_ISO_TRANSFER_CONTROL, *USB_OHCI_HC_ISO_TRANSFER_CONTROL_P;

typedef union _USB_OHCI_OFFSET_PSW {
    struct {
        uint16_t            SIZE:11;
        uint16_t            dummy:1;
        uint16_t            CC:4;
    } PSW;
    struct {
        uint16_t            OFFSET:13;
        uint16_t            CC:3;
    } OFFSET;
} USB_OHCI_OFFSET_PSW, *USB_OHCI_OFFSET_PSW_P;

typedef struct _USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR {
    struct _USB_OHCI_HC_ISO_TRANSFER_CONTROL    Control;
    uint32_t                                    BP0;
    uint32_t                                    NextTD;
    uint32_t                                    BE;
    USB_OHCI_OFFSET_PSW                         USB_OHCI_OFFSET_PSW[ 8 ];
} USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR, *USB_OHCI_HC_ISO_TRANSFER_DESCRIPTOR_P;

#endif
