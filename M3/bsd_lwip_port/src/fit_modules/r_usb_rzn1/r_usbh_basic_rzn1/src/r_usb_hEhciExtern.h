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
 * FILE         :  r_usb_hEhciExtern.h
 * Description  :  USB EHCI external header
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __USB_HEHCIEXTERN_H__
#define __USB_HEHCIEXTERN_H__

/***********************************************************************************************************************
 Prototypes
 **********************************************************************************************************************/
/* function */
/* r_usb_hEhciMain.c */
extern uint32_t             usb_hstd_EhciInit(void);
extern void                 usb_hstd_EhciDeinit(void);
extern void                 usb_hstd_EhciInterruptEnable(void);
extern void                 usb_hstd_EhciInterruptDisable(void);
extern uint32_t             usb_hstd_EhciPortReset(uint32_t portnum);
extern void                 usb_hstd_EhciDisconnect(uint32_t devadd);
extern uint32_t             usb_hstd_EhciGetFrameListSize(void);
extern void                 usb_hstd_EhciWaitMicroFrame(uint32_t uframe_no);
extern void                 usb_hstd_EhciAddAsync(USB_EHCI_QH *qh);
extern void                 usb_hstd_EhciAddPeriodic(USB_EHCI_FLEP *new_element, uint32_t type, uint32_t pollrate, uint32_t pollrate_offset);
extern void                 usb_hstd_EhciLinkQtd(USB_EHCI_QTD *qtd1st, USB_EHCI_QTD *qtd2nd);
extern void                 usb_hstd_EhciClearQtd(USB_EHCI_QTD *qtd_head);
extern void                 usb_hstd_EhciInactiveQtd(USB_EHCI_QTD *qtd_head);
extern void                 usb_hstd_EhciUnlinkQhForAsync(USB_EHCI_QH *qh);
extern void                 usb_hstd_EhciUnlinkQhForPeriodic(USB_EHCI_QH *qh);
extern void                 usb_hstd_EhciUnlinkItd(USB_EHCI_ITD *itd);
extern void                 usb_hstd_EhciUnlinkSitd(USB_EHCI_SITD *sitd);
extern uint32_t             usb_hstd_EhciUpdatePeriodicSchedulingScore(uint32_t max_period, uint32_t pollrate);
extern void                 usb_hstd_EhciIntTransferEnd(void);
extern void                 usb_hstd_EhciIntPortChange(void);
extern uint32_t             usb_hstd_EhciGetPortCurrentConnectStatus(uint16_t rootport);
extern void                 usb_hstd_EhciClearEnumalationWaitFlag(void);
extern void                 usb_hstd_EhciClearDetachWaitFlag(uint16_t rootport);
extern void                 usb_hstd_EhciInterruptHandler(void);
extern uint16_t             usb_hstd_EhciGetDeviceAddressOfRootpoot(uint16_t rootport);
extern uint16_t             usb_hstd_EhciSetDeviceAddressOfRootpoot(uint16_t rootport, uint16_t deviceaddr);
extern uint16_t             usb_hstd_EhciGetTransferEndStatus(USB_HCI_TR_REQ *tr_req);
extern uint16_t             usb_hstd_EhciGetPidStatus(USB_HCI_TR_REQ *tr_req);
extern void                 usb_hstd_EhciPortSuspend(uint16_t port);
extern void                 usb_hstd_EhciPortResume(uint16_t port);
extern void                 usb_hstd_EhciCancelTransferRequest(USB_HCI_TR_REQ *tr_req);

/* r_usb_hEhciMemory.c */
extern void                 usb_hstd_EhciInitQhMemory(void);
extern void                 usb_hstd_EhciInitItdMemory(void);
extern void                 usb_hstd_EhciInitSitdMemory(void);
extern void                 usb_hstd_EhciInitQtdMemory(void);
extern void                 usb_hstd_EhciInitPeriodicFrameList(void);
extern uint32_t             usb_gstd_EhciGetPeriodicFrameListAddr(void);
extern USB_EHCI_QH         *usb_hstd_EhciAllocQh(void);
extern USB_EHCI_ITD        *usb_hstd_EhciAllocItd(void);
extern USB_EHCI_SITD       *usb_hstd_EhciAllocSitd(void);
extern USB_EHCI_QTD        *usb_hstd_EhciAllocQtd(void);
extern void                 usb_hstd_EhciFreeQtd(USB_EHCI_QTD *free_qtd);
extern USB_EHCI_QH         *usb_hstd_EhciSearchQh(uint32_t devadd, uint32_t epnum, uint32_t direction, uint32_t eptype);
extern USB_EHCI_ITD        *usb_hstd_EhciSearchItd(uint32_t devadd, uint32_t epnum, uint32_t direction);
extern USB_EHCI_SITD       *usb_hstd_EhciSearchSitd(uint32_t devadd, uint32_t epnum, uint32_t direction);
extern void                 usb_hstd_EhciClearDeviceQh(uint32_t devadd);
extern void                 usb_hstd_EhciClearQh(USB_EHCI_QH *qh);
extern void                 usb_hstd_EhciClearDeviceItd(uint32_t devadd);
extern void                 usb_hstd_EhciClearDeviceSitd(uint32_t devadd);

/* r_usb_hEhciTransfer.c */
extern void                 usb_hstd_EhciMakeTransferRequest(USB_HCI_TR_REQ *tr_req);
extern void                 usb_hstd_EhciSetAsyncQh(USB_HCI_TR_REQ *tr_req, USB_EHCI_QH *qh);
extern void                 usb_hstd_EhciTransferEndQh(USB_HCI_TR_REQ *tr_req);
extern void                 usb_hstd_EhciTransferEndItd(USB_HCI_TR_REQ *tr_req);
extern void                 usb_hstd_EhciTransferEndSitd(USB_HCI_TR_REQ *tr_req);

#endif
