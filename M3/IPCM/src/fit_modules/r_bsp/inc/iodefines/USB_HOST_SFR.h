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
 * FILE         :  USB_HOST_SFR.h
 * Description  :  USB Host Registers
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef __USB_HOST_SFR__DEFINE_HEADER__
#define __USB_HOST_SFR__DEFINE_HEADER__

typedef struct
{
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long Revision:8;
            unsigned long :24;
        } BIT;
    } HcRevision;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long CBSR:2;
            unsigned long PLE:1;
            unsigned long IE:1;
            unsigned long CLE:1;
            unsigned long BLE:1;
            unsigned long HCFS:2;
            unsigned long :1;
            unsigned long RWC:1;
            unsigned long RWE:1;
            unsigned long :21;
        } BIT;
    } HcControl;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long HC_RESET:1;           /* Correct mame is 'HCR' but this clashes with a define in CA7.h but only in RZN1D CA7 project (via ddr_init.c) */
            unsigned long CLF:1;
            unsigned long BLF:1;
            unsigned long OCR:1;
            unsigned long :12;
            unsigned long SOC:2;
            unsigned long :14;
        } BIT;
    } HcCommandStatus;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long SO:1;
            unsigned long WDH:1;
            unsigned long SF:1;
            unsigned long RD:1;
            unsigned long UE:1;
            unsigned long FNO:1;
            unsigned long RHSC:1;
            unsigned long :25;
        } BIT;
    } HcIntStatus;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long SOE:1;
            unsigned long WDHE:1;
            unsigned long SFE:1;
            unsigned long RDE:1;
            unsigned long UEE:1;
            unsigned long FNOE:1;
            unsigned long RHSCE:1;
            unsigned long :24;
            unsigned long MIE:1;
        } BIT;
    } HcIntEnable;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long SOD:1;
            unsigned long WDHD:1;
            unsigned long SFD:1;
            unsigned long RDD:1;
            unsigned long UED:1;
            unsigned long FNOD:1;
            unsigned long RHSCD:1;
            unsigned long :24;
            unsigned long MID:1;
        } BIT;
    } HcIntDisable;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long :8;
            unsigned long HcHCCA:24;
        } BIT;
    } HcHCCA;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long :4;
            unsigned long PeriodicCurrentED:28;
        } BIT;
    } HcPeriodCurED;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long :4;
            unsigned long ControlHeadED:28;
        } BIT;
    } HcContHeadED;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long :4;
            unsigned long ControlCurrentED:28;
        } BIT;
    } HcContCurrentED;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long :4;
            unsigned long BulkHeadED:28;
        } BIT;
    } HcBulkHeadED;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long :4;
            unsigned long BulkCurrentED:28;
        } BIT;
    } HcBulkCurrentED;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long :4;
            unsigned long DoneHead:28;
        } BIT;
    } HcDoneHead;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long FI:14;
            unsigned long :2;
            unsigned long FSMPS:15;
            unsigned long FIT:1;
        } BIT;
    } HcFmInterval;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long FR:14;
            unsigned long :17;
            unsigned long FRT:1;
        } BIT;
    } HcFmRemaining;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long FrameNumber:16;
            unsigned long :16;
        } BIT;
    } HcFmNumber;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long PeriodicStart:14;
            unsigned long :18;
        } BIT;
    } HcPeriodicStart;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long HcLSThreshold:12;
            unsigned long :20;
        } BIT;
    } HcLSThreshold;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long NDP:8;
            unsigned long PSM:1;
            unsigned long NPS:1;
            unsigned long DT:1;
            unsigned long OCPM:1;
            unsigned long NOCP:1;
            unsigned long :11;
            unsigned long POTPGT:8;
        } BIT;
    } HcRhDescriptorA;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long DR:16;
            unsigned long PPCM:16;
        } BIT;
    } HcRhDescriptorB;
    union
    {
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long CGP:1;
                unsigned long OCI:1;
                unsigned long :13;
                unsigned long SRWE:1;
                unsigned long SGP:1;
                unsigned long OCIC:1;
                unsigned long :13;
                unsigned long CRWE:1;
            } BIT;
        } HcRhStatus_A;
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long LPS:1;
                unsigned long OCI:1;
                unsigned long :13;
                unsigned long DRWE:1;
                unsigned long LPSC:1;
                unsigned long OCIC:1;
                unsigned long :13;
                unsigned long CRWE:1;
            } BIT;
        } HcRhStatus_B;
    } HcRhStatus;
    union
    {
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long CPE:1;
                unsigned long SPE:1;
                unsigned long SPS:1;
                unsigned long CSS:1;
                unsigned long SPR:1;
                unsigned long :3;
                unsigned long SPP:1;
                unsigned long CPP:1;
                unsigned long :6;
                unsigned long CSC:1;
                unsigned long PESC:1;
                unsigned long PSSC:1;
                unsigned long OCIC:1;
                unsigned long PRSC:1;
                unsigned long :11;
            } BIT;
        } HcRhPortStatus1_A;
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long CCS:1;
                unsigned long PES:1;
                unsigned long PSS:1;
                unsigned long POCI:1;
                unsigned long PRS:1;
                unsigned long :3;
                unsigned long PPS:1;
                unsigned long LSDA:1;
                unsigned long :6;
                unsigned long CSC:1;
                unsigned long PESC:1;
                unsigned long PSSC:1;
                unsigned long OCIC:1;
                unsigned long PRSC:1;
                unsigned long :11;
            } BIT;
        } HcRhPortStatus1_B;
    } HcRhPortStatus1;
    char           wk0[4008];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long CapabilityRegistersLength:8;
            unsigned long :8;
            unsigned long InterfaceVersionNumber:16;
        } BIT;
    } CAPL_VERSION;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long N_PORTS:4;
            unsigned long PPC:1;
            unsigned long :2;
            unsigned long PortRoutingRules:1;
            unsigned long N_PCC:4;
            unsigned long N_CC:4;
            unsigned long P_INDICATOR:1;
            unsigned long :3;
            unsigned long DebugPortNumber:4;
            unsigned long :8;
        } BIT;
    } HCSPARAMS;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long AC64:1;
            unsigned long PFLF:1;
            unsigned long ASPC:1;
            unsigned long :1;
            unsigned long IST:4;
            unsigned long EECP:8;
            unsigned long :16;
        } BIT;
    } HCCPARAMS;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long CompanionPortRoute:32;
        } BIT;
    } HCSP_PORTROUTE;
    char           wk1[16];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long RS:1;
            unsigned long HCRESET:1;
            unsigned long FrameListSize:2;
            unsigned long PeriodicScheduleEnable:1;
            unsigned long ASPME:1;
            unsigned long InterruptonAsyncAdvanceDoorbell:1;
            unsigned long LightHostControllerReset:1;
            unsigned long ASPMC:2;
            unsigned long :1;
            unsigned long AsynchronousScheduleParkModeEnable:1;
            unsigned long :4;
            unsigned long InterruptThresholdControl:8;
            unsigned long :8;
        } BIT;
    } USBCMD;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long USBINT:1;
            unsigned long USBERRINT:1;
            unsigned long PortChangeDetect:1;
            unsigned long FrameListRollover:1;
            unsigned long HostSystemError:1;
            unsigned long InterruptonAsyncAdvance:1;
            unsigned long :6;
            unsigned long HCHalted:1;
            unsigned long Reclamation:1;
            unsigned long PeriodicScheduleStatus:1;
            unsigned long AsynchronousScheduleStatus:1;
            unsigned long :16;
        } BIT;
    } USBSTS;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long USBInterruptEnable:1;
            unsigned long USBErrorInterruptEnable:1;
            unsigned long PortChangeInterruptEnable:1;
            unsigned long FrameListRolloverEnable:1;
            unsigned long HostSystemErrorEnable:1;
            unsigned long InterruptonAsyncAdvanceEnable:1;
            unsigned long :26;
        } BIT;
    } USBINTR;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long FrameIndex:14;
            unsigned long :18;
        } BIT;
    } FRINDEX;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long CTRLDSSEGMENT:32;
        } BIT;
    } CTRLDSSEGMENT;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long :12;
            unsigned long BaseAddressLow:20;
        } BIT;
    } PERIODICLIST;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long :5;
            unsigned long LPL:27;
        } BIT;
    } ASYNCLISTADDR;
    char           wk2[36];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long CF:1;
            unsigned long :31;
        } BIT;
    } CONFIGFLAG;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long CurrentConnectStatus:1;
            unsigned long ConnectStatusChange:1;
            unsigned long PortEnabledDisabled:1;
            unsigned long PortEnableDisableChange:1;
            unsigned long OvercurrentActive:1;
            unsigned long OvercurrentChange:1;
            unsigned long ForcePortResume:1;
            unsigned long Suspend:1;
            unsigned long PortReset:1;
            unsigned long :1;
            unsigned long LineStatus:2;
            unsigned long PP:1;
            unsigned long PortOwner:1;
            unsigned long PortIndicatorControl:2;
            unsigned long PortTestControl:4;
            unsigned long WKCNNT_E:1;
            unsigned long WKDSCNNT_E:1;
            unsigned long WKOC_E:1;
            unsigned long :9;
        } BIT;
    } PORTSC1;
    char           wk3[61336];
    union
    {
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long VendorID:16;
                unsigned long DeviceID:16;
            } BIT;
        } VID_DID_O;
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long VENDOR_ID:16;
                unsigned long DEVICE_ID:16;
            } BIT;
        } VID_DID_A;
    } VID_DID;
    union
    {
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long IOSpace:1;
                unsigned long MemorySpace:1;
                unsigned long BusMaster:1;
                unsigned long SpecialCycle:1;
                unsigned long MemoryWriteandInvalidateEnable:1;
                unsigned long VGAPaletteSnoop:1;
                unsigned long ParityErrorResponse:1;
                unsigned long WaitCycleControl:1;
                unsigned long SERREnable:1;
                unsigned long FastBacktoBackEnable:1;
                unsigned long :10;
                unsigned long CapabilitiesList:1;
                unsigned long :2;
                unsigned long FastBacktoBackCapable:1;
                unsigned long DataParityErrorDetected:1;
                unsigned long DevselTiming:2;
                unsigned long SignaledTargetAbort:1;
                unsigned long ReceivedTargetAbort:1;
                unsigned long ReceivedMasterAbort:1;
                unsigned long SignaledSystemError:1;
                unsigned long DetectedParityError:1;
            } BIT;
        } CMND_STS_O;
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long IOEN:1;
                unsigned long MEMEN:1;
                unsigned long MASTEREN:1;
                unsigned long SPECIALC:1;
                unsigned long MWINVEN:1;
                unsigned long VGAPSNP:1;
                unsigned long PERREN:1;
                unsigned long STEPCTR:1;
                unsigned long SERREN:1;
                unsigned long FBTBEN:1;
                unsigned long :10;
                unsigned long CAPLIST:1;
                unsigned long CAP66M:1;
                unsigned long :1;
                unsigned long FBTBCAP:1;
                unsigned long MDPERR:1;
                unsigned long DEVTIM:2;
                unsigned long SIGTABORT:1;
                unsigned long RETABORT:1;
                unsigned long REMABORT:1;
                unsigned long SIGSERR:1;
                unsigned long DETPERR:1;
            } BIT;
        } CMND_STS_A;
    } CMND_STS;
    union
    {
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long RevisionID:8;
                unsigned long ProgrammingIF:8;
                unsigned long SubClass:8;
                unsigned long BaseClass:8;
            } BIT;
        } REVID_CC_O;
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long REVISION_ID:8;
                unsigned long CLASS_CODE:24;
            } BIT;
        } REVID_CC_A;
    } REVID_CC;
    union
    {
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long CacheLineSize:8;
                unsigned long LatencyTimer:8;
                unsigned long HeaderType:8;
                unsigned long BIST:8;
            } BIT;
        } CLS_LT_HT_BIST_O;
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long CACHE_LINE_SIZE:8;
                unsigned long LATENCY_TIMER:8;
                unsigned long HEADER_TYPE:8;
                unsigned long BIST:8;
            } BIT;
        } CLS_LT_HT_BIST_A;
    } CLS_LT_HT_BIST;
    union
    {
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long MemorySpaceIndicator:1;
                unsigned long Type:2;
                unsigned long Prefetchable:1;
                unsigned long OHCIBaseAddress:28;
            } BIT;
        } BASEAD_O;
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long MEM:1;
                unsigned long TYPE:2;
                unsigned long PREFETCH:1;
                unsigned long :6;
                unsigned long PCICOM_BASEADR:22;
            } BIT;
        } BASEAD_A;
    } BASEAD;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long MEM:1;
            unsigned long TYPE:2;
            unsigned long PREFETCH:1;
            unsigned long :24;
            unsigned long PCI_WIN1_BASEADR:4;
        } BIT;
    } WIN1_BASEAD;
    char           wk4[20];
    union
    {
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long SubsystemVendorID:16;
                unsigned long SubsystemID:16;
            } BIT;
        } SSVID_SSID_O;
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long SUBSYS_VENDOR_ID:16;
                unsigned long SUBSYS_ID:16;
            } BIT;
        } SSVID_SSID_A;
    } SSVID_SSID;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long ROMDecodeEnable:1;
            unsigned long :9;
            unsigned long ExpansionROMBaseAddress:22;
        } BIT;
    } EROM_BASEAD;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long CapabilityPointer:8;
            unsigned long :24;
        } BIT;
    } CAPPTR;
    char           wk5[4];
    union
    {
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long InterruptLine:8;
                unsigned long InterruptPin:8;
                unsigned long MINGnt:8;
                unsigned long MaxLatency:8;
            } BIT;
        } INTR_LINE_PIN_O;
        union
        {
            unsigned long LONG;
            struct
            {
                unsigned long INT_LINE:8;
                unsigned long INT_PIN:8;
                unsigned long MIN_GNT:8;
                unsigned long MAX_LAT:8;
            } BIT;
        } INTR_LINE_PIN_A;
    } INTR_LINE_PIN;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long CapabilityIdentifier:8;
            unsigned long NextItemPointer:8;
            unsigned long Version:3;
            unsigned long PMECLK:1;
            unsigned long :1;
            unsigned long DSI:1;
            unsigned long AUXCurrent:3;
            unsigned long D1Support:1;
            unsigned long D2Support:1;
            unsigned long PMESupport:5;
        } BIT;
    } CAPID_NIP_PMCAP;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long PowerState:2;
            unsigned long :6;
            unsigned long PMEEnable:1;
            unsigned long DataSelect:4;
            unsigned long DataScale:2;
            unsigned long PMEStatus:1;
            unsigned long :6;
            unsigned long B2_B3:1;
            unsigned long BPCCEnable:1;
            unsigned long Data:8;
        } BIT;
    } PMC_STS_PMCSR;
    char           wk6[152];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long Port_no:2;
            unsigned long :5;
            unsigned long ID_Write_Enable:1;
            unsigned long :4;
            unsigned long PSD:1;
            unsigned long HyperSpeedtransferControl1:1;
            unsigned long :5;
            unsigned long HyperSpeedtransferControl2:5;
            unsigned long potpgt:8;
        } BIT;
    } EXT1;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long EHCI_mask:1;
            unsigned long HyperSpeedtransferControl3:1;
            unsigned long :14;
            unsigned long RUNRAMConnectCheck:1;
            unsigned long RAMConnectCheckENDFlag:1;
            unsigned long RAMConnectCheckResult:1;
            unsigned long :13;
        } BIT;
    } EXT2;
    char           wk7[24];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long VendorID:16;
            unsigned long DeviceID:16;
        } BIT;
    } VID_DID_E;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long IOSpace:1;
            unsigned long MemorySpace:1;
            unsigned long BusMaster:1;
            unsigned long SpecialCycle:1;
            unsigned long MemoryWriteandInvalidateEnable:1;
            unsigned long VGAPaletteSnoop:1;
            unsigned long ParityErrorResponse:1;
            unsigned long WaitCycleControl:1;
            unsigned long SERREnable:1;
            unsigned long FastBacktoBackEnable:1;
            unsigned long :10;
            unsigned long CapabilitiesList:1;
            unsigned long Capable66MHz:1;
            unsigned long :1;
            unsigned long FastBacktoBackCapable:1;
            unsigned long DataParityErrorDetected:1;
            unsigned long DevselTiming:2;
            unsigned long SignaledTargetAbort:1;
            unsigned long ReceivedTargetAbort:1;
            unsigned long ReceivedMasterAbort:1;
            unsigned long SignaledSystemError:1;
            unsigned long DetectedParityError:1;
        } BIT;
    } CMND_STS_E;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long RevisionID:8;
            unsigned long ProgrammingIF:8;
            unsigned long SubClass:8;
            unsigned long BaseClass:8;
        } BIT;
    } REVID_CC_E;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long CacheLineSize:8;
            unsigned long LatencyTimer:8;
            unsigned long HeaderType:8;
            unsigned long BIST:8;
        } BIT;
    } CLS_LT_HT_BIST_E;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long MemorySpaceIndicator:1;
            unsigned long Type:2;
            unsigned long Prefetchable:1;
            unsigned long EHCIBaseAddress:28;
        } BIT;
    } BASEAD_E;
    char           wk8[24];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long SubsystemVendorID:16;
            unsigned long SubsystemID:16;
        } BIT;
    } SSVID_SSID_E;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long ROMDecodeEnable:1;
            unsigned long :9;
            unsigned long ExpansionROMBaseAddress:22;
        } BIT;
    } EROM_BASEAD_E;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long CapabilityPointer:8;
            unsigned long :24;
        } BIT;
    } CAPPTR_E;
    char           wk9[4];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long InterruptLine:8;
            unsigned long InterruptPin:8;
            unsigned long MinGnt:8;
            unsigned long MaxLatency:8;
        } BIT;
    } INTR_LINE_PIN_E;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long CapabilityIdentifier:8;
            unsigned long NextItemPointer:8;
            unsigned long Version:3;
            unsigned long PMECLK:1;
            unsigned long :1;
            unsigned long DSI:1;
            unsigned long AUXCurrent:3;
            unsigned long D1Support:1;
            unsigned long D2Support:1;
            unsigned long PMESupport:5;
        } BIT;
    } CAPID_NIP_PMCAP_E;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long PowerState:2;
            unsigned long :6;
            unsigned long PMEEnable:1;
            unsigned long DataSelect:4;
            unsigned long DataScale:2;
            unsigned long PMEStatus:1;
            unsigned long :6;
            unsigned long B2_B3:1;
            unsigned long BPCCEnable:1;
            unsigned long Data:8;
        } BIT;
    } PMC_STS_PMCSR_E;
    char           wk10[24];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long SBRN:8;
            unsigned long FLADJ:8;
            unsigned long PORTWAKECAP:16;
        } BIT;
    } SBRN_FLADJ_PW;
    char           wk11[124];
    unsigned long  EXT1_E;
    unsigned long  EXT2_E;
    char           wk12[1560];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long PREFETCH:2;
            unsigned long :26;
            unsigned long AHB_BASEADR:4;
        } BIT;
    } PCIAHB_WIN1_CTR;
    char           wk13[12];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long :1;
            unsigned long PCICMD:3;
            unsigned long :7;
            unsigned long PCIWIN1_BASEADR:21;
        } BIT;
    } AHBPCI_WIN1_CTR;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long :1;
            unsigned long PCICMD:3;
            unsigned long :1;
            unsigned long BURST_EN:1;
            unsigned long :10;
            unsigned long PCIWIN2_BASEADR:16;
        } BIT;
    } AHBPCI_WIN2_CTR;
    char           wk14[8];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long SIGTABORT_INTEN:1;
            unsigned long RETABORT_INTEN:1;
            unsigned long REMABORT_INTEN:1;
            unsigned long PERR_INTEN:1;
            unsigned long SIGSERR_INTEN:1;
            unsigned long RESERR_INTEN:1;
            unsigned long :6;
            unsigned long PCIAHB_WIN1_INTEN:1;
            unsigned long PCIAHB_WIN2_INTEN:1;
            unsigned long :2;
            unsigned long USBH_INTAEN:1;
            unsigned long USBH_INTBEN:1;
            unsigned long :1;
            unsigned long USBH_PMEEN:1;
            unsigned long :12;
        } BIT;
    } PCI_INT_ENABLE;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long SIGTABORT_INT:1;
            unsigned long RETABORT_INT:1;
            unsigned long REMABORT_INT:1;
            unsigned long PERR_INT:1;
            unsigned long SIGSERR_INT:1;
            unsigned long RESERR_INT:1;
            unsigned long :6;
            unsigned long PCIAHB_WIN1_INT:1;
            unsigned long PCIAHB_WIN2_INT:1;
            unsigned long :2;
            unsigned long USBH_INTA:1;
            unsigned long USBH_INTB:1;
            unsigned long :1;
            unsigned long USBH_PME:1;
            unsigned long :12;
        } BIT;
    } PCI_INT_STATUS;
    char           wk15[8];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long MMODE_HTRANS:1;
            unsigned long MMODE_BYTE_BURST:1;
            unsigned long MMODE_WR_INCR:1;
            unsigned long :4;
            unsigned long MMODE_HBUSREQ:1;
            unsigned long :9;
            unsigned long SMODE_READY_CTR:1;
            unsigned long :14;
        } BIT;
    } AHB_BUS_CTR;
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long USBH_RST:1;
            unsigned long PCICLK_MASK:1;
            unsigned long :7;
            unsigned long PCI_AHB_WIN2_EN:1;
            unsigned long PCI_AHB_WIN1_SIZE:2;
            unsigned long :20;
        } BIT;
    } USBCTR;
    char           wk16[8];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long PCIREQ0:1;
            unsigned long PCIREQ1:1;
            unsigned long :10;
            unsigned long PCIBP_MODE:1;
            unsigned long :19;
        } BIT;
    } PCI_ARBITER_CTR;
    char           wk17[4];
    union
    {
        unsigned long LONG;
        struct
        {
            unsigned long MinorRevisionID:16;
            unsigned long MajorRevisionID:16;
        } BIT;
    } PCI_UNIT_REV;
} USB_HOST_Type;

#endif /* End of __USB_HOST_SFR__DEFINE_HEADER__ */
