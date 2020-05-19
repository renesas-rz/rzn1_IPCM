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
 * FILE         :  r_usb_hOhciExtern.h
 * Description  :  USB OHCI external defines
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __USB_HOHCIEXTERN_H__
#define __USB_HOHCIEXTERN_H__

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
/* Functions */
/* r_usb_hOhciMain.c */
extern uint32_t                     usb_hstd_OhciInit(void);
extern void                         usb_hstd_OhciDeinit(void);
extern void                         usb_hstd_OhciInterruptHandler(void);
extern void                         usb_hstd_OhciMainRoutine(uint32_t context_info);
extern void                         usb_hstd_OhciControlRoothub(void);
extern void                         usb_hstd_OhciDisconnect(uint32_t devadd);
extern uint16_t                     usb_hstd_OhciGetDeviceAddressOfRootpoot(uint16_t rootport);
extern uint16_t                     usb_hstd_OhciSetDeviceAddressOfRootpoot(uint16_t rootport, uint16_t deviceaddr);
extern void                         usb_hstd_OhciPortReset(uint32_t portnum);
extern uint16_t                     usb_hstd_OhciGetPidStatus(USB_HCI_TR_REQ *tr_req);
extern void                         usb_hstd_OhciPortSuspend(uint16_t port);
extern void                         usb_hstd_OhciPortResume(uint16_t port);
extern uint16_t                     usb_hstd_OhciGetTransferEndStatus(USB_HCI_TR_REQ *tr_req);
extern uint32_t                     usb_hstd_OhciRemoveEndpoint(uint8_t device_address, uint8_t endpoint_number, uint8_t direction, boolean_t free_ed);
extern uint32_t                     usb_hstd_OhciPauseEndpoint(uint8_t device_address, uint8_t endpoint_number, uint8_t direction);
extern USB_OHCI_LIST_ENTRY_P       usb_hstd_OhciRemoveListHead(USB_OHCI_LIST_ENTRY_P list);
extern void                         usb_hstd_OhciRemoveListEntry(USB_OHCI_LIST_ENTRY_P list);
extern void                         usb_hstd_OhciInitializeListHead(USB_OHCI_LIST_ENTRY_P list);
extern uint32_t                     usb_hstd_OhciIsListEmpty(USB_OHCI_LIST_ENTRY_P list);
extern void                         usb_hstd_OhciInsertHeadList(USB_OHCI_LIST_ENTRY_P list_head, USB_OHCI_LIST_ENTRY_P link);
extern void                         usb_hstd_OhciInsertTailList(USB_OHCI_LIST_ENTRY_P list_head, USB_OHCI_LIST_ENTRY_P link);
extern uint32_t                     usb_hstd_OhciPhysicalAddressOf(void *data);
extern void                         usb_hstd_OhciPauseEd(USB_OHCI_HCD_ENDPOINT_P endpoint);
extern void                         usb_hstd_OhciUnscheduleIsochronousOrInterruptEndpoint(USB_OHCI_HCD_ENDPOINT_P endpoint, boolean_t free_ed, boolean_t endpoint_processing_required);
extern uint32_t                     usb_hstd_OhciSetFrameInterval(USB_OHCI_HCD_DEVICE_DATA_P device_data, boolean_t up_not_down);
extern uint32_t                     usb_hstd_OhciGet32BitFrameNumber(USB_OHCI_HCD_DEVICE_DATA_P device_data);
extern uint32_t                     usb_hstd_OhciCheckBandwidth(USB_OHCI_HCD_DEVICE_DATA_P device_data, uint32_t list, uint32_t *best_list);

/* r_usb_hOhciMemory.c */
extern USB_OHCI_HCCA_BLOCK_P               usb_hstd_OhciGetHccaAddress(void);
extern void                                 usb_hstd_OhciInitRequestMemory(void);
extern void                                 usb_hstd_OhciInitDeviceData(void);
extern void                                 usb_hstd_OhciClearList(void);
extern USB_OHCI_REQUEST_P                  usb_hstd_OhciAllocTransferRequest(void);
extern USB_OHCI_HCD_DEVICE_DATA_P          usb_hstd_OhciAllocDeviceData(void);
extern USB_OHCI_HCD_ENDPOINT_P             usb_hstd_OhciAllocEndpoint(void);
extern USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P  usb_hstd_OhciAllocateEndpointDescriptor(void);
extern USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P  usb_hstd_OhciAllocateTransferDescriptor(void);
extern USB_OHCI_ISO_INFO_P                 usb_hstd_OhciAllocEndpointIso(void);
extern void                                 usb_hstd_OhciFreeTransferRequest(USB_OHCI_REQUEST_P ohci_req);
extern void                                 usb_hstd_OhciFreeTransferDescriptor(USB_OHCI_HCD_TRANSFER_DESCRIPTOR_P td);
extern void                                 usb_hstd_OhciFreeEndpoint(USB_OHCI_HCD_ENDPOINT_P endpoint);
extern void                                 usb_hstd_OhciFreeEndpointDescriptor(USB_OHCI_HCD_ENDPOINT_DESCRIPTOR_P ed);
extern USB_OHCI_HCD_ENDPOINT_P             usb_hstd_OhciScanEndpoint(uint8_t device_address, uint8_t endpoint_number, uint8_t direction);
extern void                                 usb_hstd_OhciStoreEndpoint(uint8_t device_address, uint8_t endpoint_number, uint8_t direction, USB_OHCI_HCD_ENDPOINT_P endpoint);
extern uint32_t                             usb_hstd_OhciScanContainingRecord(USB_OHCI_LIST_ENTRY_P list, uint8_t type, uint8_t field);
extern uint32_t                             usb_hstd_OhciCheckRemainedTd(void);
extern uint32_t                             usb_hstd_OhciCheckRemainedEd(void);
extern uint32_t                             usb_hstd_OhciCheckRemainedEp(void);

/* r_usb_hOhciTransfer.c */
extern void                         usb_hstd_OhciMakeTransferRequest(USB_HCI_TR_REQ *tr_req);
extern void                         usb_hstd_OhciCancelTransferRequest(USB_HCI_TR_REQ *tr_req);
extern void                         usb_hstd_OhciProcessDoneQueue(uint32_t phys_hc_td);
extern void                         usb_hstd_OhciCompleteTransferRequest(USB_OHCI_REQUEST_P ohci_req);

#endif
