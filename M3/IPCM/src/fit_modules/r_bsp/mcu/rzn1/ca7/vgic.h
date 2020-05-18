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
 * $Revision: 1301 $
 * $Date: 2019-02-25 14:29:43 +0000 (Mon, 25 Feb 2019) $
 *
 * PROJECT NAME :  RZ/N1 bare metal Drivers
 * FILE         :  vgic.h
 * Description  :  VGI Interrupt Definitions
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#ifndef _VGIC_H
#define _VGIC_H

// PPI IDs:
#define   GIC_PPI_S_PHYSICAL_TIMER  (29)
#define   GIC_PPI_NS_PHYSICAL_TIMER (30)
#define   GIC_PPI_VIRTUAL_TIMER     (27)
#define   GIC_PPI_HYP_TIMER         (26)

#define   GIC_PPI_VIRT_MAINTENANCE  (25)

#define   GIC_PPI_LEGACY_IRQ        (31)
#define   GIC_PPI_LEGACY_FIQ        (28)

// CPU Interface offset from base of private peripheral space --> 0x0100
// Interrupt Distributor offset from base of private peripheral space --> 0x1000

// ------------------------------------------------------------
// Distributor
//------------------------------------------------------------

// Global enable of the Interrupt Distributor
void enableVGIC(void);

//  Global disable of the Interrupt Distributor
void disableVGIC(void);

// ------------------------------------------------------------
// Physical CPU Interface
// ------------------------------------------------------------

// Enables the physical CPU interface
// Must been done one each CPU separately
void enableVGICPhysicalCPUInterface(void);

// Disables the processor interface
// Must been done one each CPU separately
void disableVGICPhysicalCPUInterface(void);

//  Enables the interrupt source number ID
void enableIntID(unsigned int ID);

//  Disables the interrupt source number ID
void disableIntID(unsigned int ID);

// Sets the priority of the specifed ID
// ID        - ID of interrupt to be set
// priority  - Priority interrupt is to be set to
void setIntPriority(unsigned int ID, unsigned int priority);

// Sets the target CPUs of the specified ID
// ID        - ID of interrupt to be set
// target    - 8-bit CPU targets
void setIntTarget(unsigned int ID, unsigned int target);

// Returns the 1 if ID currently active, or 0 if not active
// ID        - ID to check
unsigned int getIntActive(unsigned int ID);

// Returns the 1 if ID currently pending, or 0 if not pending
// ID        - ID to check
unsigned int getIntPending(unsigned int ID);

// Sets the Priority mask register for the CPU run on
// The reset value masks ALL interrupts!
void setPriorityMask(unsigned int priority);

// Returns the value of the Interrupt Acknowledge Register
unsigned int readIntAck(void);

//  Writes ID to the End Of Interrupt register (GICC_EOIR)
void writeEOI(unsigned int ID);

// Enables the sending of Group 0 interrupts as FIQs
void enableFIQs(void);

// Disables the sending of Group 0 interrupts as FIQ
void disableFIQs(void);

// Enables Software Interrupt for a certain ID
void enableSGI(unsigned int ID);

// Clears pending Software Interrupt for a certain ID
void clearSGI(unsigned int ID);

// ------------------------------------------------------------
// TrustZone
// ------------------------------------------------------------

//Sets the specified ID as being Secure
// ID - ID of interrupt to be made Secure
void makeIntSecure(unsigned int ID);

// Sets the ID as being NS
// ID - ID of interrupt to be made non-secure
void makeIntNonSecure(unsigned int ID);

#endif // defined( _VGIC_H )
