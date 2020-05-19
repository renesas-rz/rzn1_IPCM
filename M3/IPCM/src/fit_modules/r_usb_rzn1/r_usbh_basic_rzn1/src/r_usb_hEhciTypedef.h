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
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * $Revision: 1814 $
 * $Date: 2020-01-23 15:43:44 +0000 (Thu, 23 Jan 2020) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  r_usb_hEhciTypedef.h
 * Description  :  USB EHCI Typedefs
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2020. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __USB_HEHCITYPEDEF_H__
#define __USB_HEHCITYPEDEF_H__

/***********************************************************************************************************************
 Definitions
 **********************************************************************************************************************/
#define USB_EHCI_VERSON             0x0100          /* HCIVERSION */

#define USB_EHCI_MAXROOTPORTS       1               /* The maximum number of route ports */

#define USB_EHCI_LINE_STATE_SE0     0               /* USB State : SE0 */
#define USB_EHCI_LINE_STATE_J       2               /* USB State : J-state */
#define USB_EHCI_LINE_STATE_K       1               /* USB State : K-state */

#define USB_EHCI_TYP_ITD            0               /* Isochronous Transfer Descriptor */
#define USB_EHCI_TYP_QH             1               /* Queue Head */
#define USB_EHCI_TYP_SITD           2               /* Split Transaction Isochronous Transfer Descriptor */
#define USB_EHCI_TYP_FSTN           3               /* Periodic Frame Span Traversal Node */

#define USB_EHCI_TP_ALL             0               /* Transaction position : All */
#define USB_EHCI_TP_BEGIN           1               /* Transaction position : Begin */
#define USB_EHCI_TP_MID             2               /* Transaction position : Middle */
#define USB_EHCI_TP_END             3               /* Transaction position : End */

#define USB_EHCI_PID_OUT            0               /* PID : OUT */
#define USB_EHCI_PID_IN             1               /* PID : IN */
#define USB_EHCI_PID_SETUP          2               /* PID : SETUP */

#define USB_EHCI_MAXQTDSIZE         20480           /* The maximum transfer size of QTD */

#define USB_EHCI_SITD_DATA_SIZE     188             /* Maximum size that can be transfered with one micro frame of SITD */

/***********************************************************************************************************************
 EHCI-Related Definitions
 **********************************************************************************************************************/
/* Refer to EHCI Spec.3.1 */
typedef union USB_EHCI_FLEP_tag {
    struct {
        uint32_t            T : 1;
        uint32_t            Typ : 2;
        uint32_t            : 2;
        uint32_t            Pointer : 27;
    } BIT;
    union USB_EHCI_FLEP_tag *Pointer;
    uint32_t                Address;
} USB_EHCI_FLEP;


/* Refer to EHCI Spec.3.5.3 */
typedef union USB_EHCI_TRANSFER_INFO_tag {
    struct {
        uint32_t            Status_Ping_State : 1;
        uint32_t            Status_Split_Transaction_State : 1;
        uint32_t            Status_Missed_Micro_Frame : 1;
        uint32_t            Status_Transaction_Error : 1;
        uint32_t            Status_Babble_Detected : 1;
        uint32_t            Status_Data_Buffer_Error : 1;
        uint32_t            Status_Halted : 1;
        uint32_t            Status_Active : 1;
        uint32_t            PID_Code : 2;
        uint32_t            CERR : 2;
        uint32_t            C_Page : 3;
        uint32_t            IOC : 1;
        uint32_t            Total_Bytes_to_Transfer : 15;
        uint32_t            Data_Toggle : 1;
    } BIT;
    uint32_t                DWORD;
} USB_EHCI_TRANSFER_INFO;


/* Queue Head */
typedef struct USB_EHCI_QH_tag {
    /* Refer to EHCI Spec.3.6.1 */
    USB_EHCI_FLEP           Queue_Head_Horizontal_Link;

    /* Refer to EHCI Spec.3.6.2 */
    union Endpoint1_tag {
        struct {
            uint32_t        Device_Address : 7;
            uint32_t        I : 1;
            uint32_t        Endpt : 4;
            uint32_t        EPS : 2;
            uint32_t        DTC : 1;
            uint32_t        H : 1;
            uint32_t        Maximum_Packet_Length : 11;
            uint32_t        C : 1;
            uint32_t        RL : 4;
        } BIT;
        uint32_t            DWORD;
    } Endpoint1;

    /* Refer to EHCI Spec.3.6.2 */
    union Endpoint2_tag {
        struct {
            uint32_t        Mframe_Smask : 8;
            uint32_t        Mframe_Cmask : 8;
            uint32_t        Hub_Addr : 7;
            uint32_t        Port_Number : 7;
            uint32_t        Mult : 2;
        } BIT;
        uint32_t            DWORD;
    } Endpoint2;

    union {
        struct {
            uint32_t        : 5;
            uint32_t        Pointer : 27;
        } BIT;
        struct USB_EHCI_QTD_tag *Pointer;
        uint32_t            Address;
    } Current_qTD;

    union {
        struct {
            uint32_t        T : 1;
            uint32_t        : 4;
            uint32_t        Pointer : 27;
        } BIT;
        struct USB_EHCI_QTD_tag *Pointer;
        uint32_t            Address;
    } Next_qTD;

    union {
        struct {
            uint32_t        T : 1;
            uint32_t        NakCnt : 4;
            uint32_t        Pointer : 27;
        } BIT;
        struct USB_EHCI_QTD_tag *Pointer;
        uint32_t            Address;
    } Alternate_Next_qTD;

    /* Refer to EHCI Spec.3.5.3 */
    USB_EHCI_TRANSFER_INFO  Transfer_Info;

    /* Refer to EHCI Spec.3.6.3 */
    union {
        struct {
            uint32_t        Current_Offset : 12;
            uint32_t        Pointer : 20;
        } BIT;
        struct {
            uint32_t        C_prog_mask : 8;
            uint32_t        : 4;
            uint32_t        Pointer : 20;
        } BIT1;
        struct {
            uint32_t        Frame_Tag : 5;
            uint32_t        S_bytes : 7;
            uint32_t        Pointer : 20;
        } BIT2;
        uint32_t            Address;
    } Buffer[ 5 ];

//  hcd-related
    uint32_t                reserve[ 1 ];
    struct {
        uint32_t            pollrate        : 14;   /* poll-rate */
        uint32_t            direction       : 2;    /* direction */
        uint32_t            pollrate_offset : 14;   /* poll-rate offset */
        uint32_t            tr_req_flag     : 1;    /* Transfer Request flag */
        uint32_t            enable          : 1;    /* QH enable flag */
    } Info;
    struct USB_EHCI_QTD_tag *qtd_head;              /* QTD head pointer */
    struct USB_EHCI_QTD_tag *qtd_end;               /* QTD end pointer */
} USB_EHCI_QH;


/* Queue Element Transfer Descriptor */
typedef struct USB_EHCI_QTD_tag {
    /* Refer to EHCI Spec.3.5.1 */
    union {
        struct {
            uint32_t        T : 1;
            uint32_t        : 4;
            uint32_t        Pointer : 27;
        } BIT;
        struct USB_EHCI_QTD_tag *Pointer;
        uint32_t            Address;
    } Next_qTD;

    /* Refer to EHCI Spec.3.5.2 */
    union {
        struct {
            uint32_t        T : 1;
            uint32_t        : 4;
            uint32_t        Pointer : 27;
        } BIT;
        struct USB_EHCI_QTD_tag *Pointer;
        uint32_t            Address;
    } Alternate_Next_qTD;

    /* Refer to EHCI Spec.3.5.3 */
    USB_EHCI_TRANSFER_INFO  Transfer_Info;

    /* Refer to EHCI Spec.3.5.4 */
    union {
        struct {
            uint32_t        Current_Offset : 12;
            uint32_t        Pointer : 20;
        } BIT;
        uint32_t            Address;
    } Buffer[ 5 ];
} USB_EHCI_QTD;


/* Isochronous Transfer Descriptor */
typedef struct USB_EHCI_ITD_tag {
    /* Refer to EHCI Spec.3.3.1 */
    USB_EHCI_FLEP           Next_Link;

    /* Refer to EHCI Spec.3.3.2 */
    union {
        struct {
            uint32_t        Offset : 12;
            uint32_t        PG : 3;
            uint32_t        IOC : 1;
            uint32_t        Length : 12;
            uint32_t        Status_Transaction_Error : 1;
            uint32_t        Status_Babble_Detected : 1;
            uint32_t        Status_Data_Buffer_Error : 1;
            uint32_t        Status_Active : 1;
        } BIT;
        uint32_t            DWORD;
    } Transaction[ 8 ];

    /* Refer to EHCI Spec.3.3.3 */
    union {
        struct {
            uint32_t        Device_Address : 7;
            uint32_t        : 1;
            uint32_t        Endpt : 4;
            uint32_t        Pointer : 20;
        } BIT0;
        struct {
            uint32_t        Maximum_Packet_Length : 11;
            uint32_t        Direction : 1;
            uint32_t        Pointer : 20;
        } BIT1;
        struct {
            uint32_t        Multi : 2;
            uint32_t        : 10;
            uint32_t        Pointer : 20;
        } BIT2;
        uint32_t            Address;
    } Buffer[ 7 ];

//  hcd-related
    uint32_t                reserve[ 2 ];
    struct {
        uint32_t            pollrate        : 14;   /* poll-rate */
        uint32_t            direction       : 2;    /* direction */
        uint32_t            pollrate_offset : 14;   /* poll-rate offset */
        uint32_t            tr_req_flag     : 1;    /* Transfer Request flag */
        uint32_t            enable          : 1;    /* QH enable flag */
    } Info;

    uint32_t                setup_cnt;              /* setup count */
    uint32_t                ini_setup_cnt;          /* initialize setup count */
    uint32_t                next_setup_uframe;      /* next setup micro frame no */
    uint32_t                next_active_uframe;     /* next active micro frame no */
    uint32_t                next_trend_uframe;      /* next transfer end micro frame no */

    uint8_t                 tmp_buffer[ 8 ][ USB_EHCI_ITD_DATA_SIZE ];  /* transfer temporary buffer for ITD */
} USB_EHCI_ITD;


/* Split Transaction Isochronous Transfer Descriptor */
typedef struct USB_EHCI_SITD_tag {
    /* Refer to EHCI Spec.3.4.1 */
    USB_EHCI_FLEP           Next_Link;

    /* Refer to EHCI Spec.3.4.2 */
    union {
        struct {
            uint32_t        Device_Address : 7;
            uint32_t        : 1;
            uint32_t        Endpt : 4;
            uint32_t        : 4;
            uint32_t        Hub_Addr : 7;
            uint32_t        : 1;
            uint32_t        Port_Number : 7;
            uint32_t        Direction : 1;
        } BIT;
        uint32_t            DWORD;
    } Endpoint1;

    /* Refer to EHCI Spec.3.4.2 */
    union {
        struct {
            uint32_t        Mframe_Smask : 8;
            uint32_t        Mframe_Cmask : 8;
            uint32_t        : 16;
        } BIT;
        uint32_t            DWORD;
    } Endpoint2;

    /* Refer to EHCI Spec.3.4.3 */
    union State_tag {
        struct {
            uint32_t        : 1;
            uint32_t        Status_Split_Transaction_State : 1;
            uint32_t        Status_Missed_Micro_Frame : 1;
            uint32_t        Status_Transaction_Error : 1;
            uint32_t        Status_Babble_Detected : 1;
            uint32_t        Status_Data_Buffer_Error : 1;
            uint32_t        Status_ERR : 1;
            uint32_t        Status_Active : 1;
            uint32_t        C_prog_mask : 8;
            uint32_t        Total_Bytes_to_Transfer : 10;
            uint32_t        : 4;
            uint32_t        Page_Select : 1;
            uint32_t        IOC : 1;
        } BIT;
        uint32_t            DWORD;
    } State;

    /* Refer to EHCI Spec.3.4.4 */
    union {
        struct {
            uint32_t        Current_Offset : 12;
            uint32_t        Pointer : 20;
        } BIT0;
        struct {
            uint32_t        T_Count : 3;
            uint32_t        TP : 2;
            uint32_t        : 7;
            uint32_t        Pointer : 20;
        } BIT1;
        uint32_t            Address;
    } Buffer[ 2 ];

    /* Refer to EHCI Spec.3.4.5 */
    USB_EHCI_FLEP           Back;

//  hcd-related
    uint32_t                reserved[ 7 ];
    uint32_t                mps;                    /* Max Packet Size */
    struct {
        uint32_t            pollrate        : 14;   /* poll-rate */
        uint32_t            direction       : 2;    /* direction */
        uint32_t            pollrate_offset : 14;   /* poll-rate offset */
        uint32_t            tr_req_flag     : 1;    /* Transfer Request flag */
        uint32_t            enable          : 1;    /* QH enable flag */
    } Info;
} USB_EHCI_SITD;

#endif
