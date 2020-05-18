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
 * FILE         :  vgic.c
 * Description  :  VGI Interrupt Implementation
 *
 * (C) Copyright Renesas Electronics Europe Ltd. 2019. All Rights Reserved
 **********************************************************************************************************************/

#include "common/common_api.h"
#include "ca7.h"

// get private peripheral space
#define getPPAddr() READ_CP32(CBAR)

// CPU Interface offset from base of private peripheral space --> 0x0100
// Interrupt Distributor offset from base of private peripheral space --> 0x1000

// ------------------------------------------------------------
// Distributor
// ------------------------------------------------------------

// Global enable of the Interrupt Distributor
void enableVGIC(void) {
    uint32_t addr, data;

    addr = getPPAddr();
    // Add the VGIC offset
    addr += 0x1000;

    data = CPU_RDW(addr); // Distributor Control Register (GICD_CTLR)
    // Bit 0: Enable secure interrupts,
    // Bit 1: Enable Non-Secure interrupts
    data |= 0x3;
    CPU_WRW(addr, data);
}

//  Global disable of the Interrupt Distributor
void disableVGIC(void) {
    uint32_t addr, data;

    addr = getPPAddr();
    // Add the VGIC offset
    addr += 0x1000;

    data = CPU_RDW(addr); // Distributor Control Register (GICD_CTLR)
    // Bit 0: Enable secure interrupts,
    // Bit 1: Enable Non-Secure interrupts
    data &= 0xFFFFFFFC;
    CPU_WRW(addr, data);
}

// ------------------------------------------------------------
// Physical CPU Interface
// ------------------------------------------------------------

// Enables the physical CPU interface
// Must been done one each CPU separately
void enableVGICPhysicalCPUInterface(void) {
    uint32_t addr, data;

    addr = getPPAddr();
    // Add CPU interface offset
    addr += 0x2000;

    data = CPU_RDW(addr); // CPU Interface Control register (GICC_CTLR)
    // Bit 0: Enable secure interrupts,
    // Bit 1: Enable Non-Secure interrupts
    data |= 0x3;
    CPU_WRW(addr, data);
}

// Disables the processor interface
// Must been done one each CPU separately
void disableVGICPhysicalCPUInterface(void) {
    uint32_t addr, data;

    addr = getPPAddr();
    // Add CPU interface offset
    addr += 0x2000;

    data = CPU_RDW(addr); // CPU Interface Control register (GICC_CTLR)
    // Bit 0: Enable secure interrupts,
    // Bit 1: Enable Non-Secure interrupts
    data &= 0xFFFFFFFC;
    CPU_WRW(addr, data);
}

//  Enables the interrupt source number ID
void enableIntID(unsigned int ID) {
    uint32_t addr, data;

    addr = getPPAddr();
    addr += 0x1100;        // Interrupt Set-Enable Registers 0 (GICD_ISENABLER0)
    addr += (ID >> 5) << 2;      // GICD_ISENABLERn
    data = 0x1 << (ID & 0x1F);

    CPU_WRW(addr, data);
}

//  Disables the interrupt source number ID
void disableIntID(unsigned int ID) {
    uint32_t addr, data;

    addr = getPPAddr();
    addr += 0x1180;      // Interrupt Clear-Enable Registers 0 (GICD_ICENABLER0)
    addr += (ID >> 5) << 2;      // GICD_ICENABLERn
    data = 0x1 << (ID & 0x1F);

    CPU_WRW(addr, data);
}

// Sets the priority of the specifed ID
// ID        - ID of interrupt to be set
// priority  - Priority interrupt is to be set to
void setIntPriority(unsigned int ID, unsigned int priority) {
    uint32_t addr, data, read_data, offset, mask;

    addr = getPPAddr();
    // Interrupt Priority Registers (GICD_IPRIORITYRn)
    addr += 0x1400 + (ID & 0xFFFFFFFC);
    read_data = CPU_RDW(addr);
    data = (priority & 0xFF) * 0x8; // Make sure that priority value is only 8 bits and because GICC_BPR is set automatically to 2, we only have 32 possible priority fields ( in steps of 8)
    offset = (ID & 0x3) << 3; // offset 0, 8, 16, 24 bit
    mask = 0xFF << offset;
    data = data << offset;
    data = (read_data & (~mask)) | data;

    CPU_WRW(addr, data);
}

// Sets the target CPUs of the specified ID
// ID        - ID of interrupt to be set
// target    - 8-bit CPU targets
void setIntTarget(unsigned int ID, unsigned int target) {
    uint32_t addr, data, read_data, offset, mask;

    addr = getPPAddr();
    // Interrupt Processor Targets Registers (GICD_ITARGETSRn)
    addr += 0x1800 + (ID & 0xFFFFFFFC);
    read_data = CPU_RDW(addr);
    data = target & 0xFF; // (each target field is only 8 bits long)
    offset = (ID & 0x3) << 3; // offset 0, 8, 16, 24 bit
    mask = 0xFF << offset;
    data = data << offset;
    data = (read_data & (~mask)) | data;

    CPU_WRW(addr, data);
}

// Returns the 1 if ID currently active, or 0 if not active
// ID        - ID to check
unsigned int getIntActive(unsigned int ID) {
    uint32_t addr, data;

    addr = getPPAddr();
    addr += 0x1300;        // Interrupt Set-Active Registers 0 (GICD_ISACTIVER0)
    addr += (ID >> 5) << 2;      // GICD_ISACTIVERn
    data = CPU_RDW(addr);
    data = 0x1 & (data >> (ID & 0x1F));

    return data;
}

// Returns the 1 if ID currently pending, or 0 if not pending
// ID        - ID to check
unsigned int getIntPending(unsigned int ID) {
    uint32_t addr, data;

    addr = getPPAddr();
    addr += 0x1200;          // Interrupt Set-Active Registers 0 (GICD_ISPENDR0)
    addr += (ID >> 5) << 2;      // GICD_ISPENDRn
    data = CPU_RDW(addr);
    data = 0x1 & (data >> (ID & 0x1F));

    return data;
}

// Sets the Priority mask register for the CPU run on
// The reset value masks ALL interrupts!
void setPriorityMask(unsigned int priority) {
    uint32_t addr;

    addr = getPPAddr();
    // Add CPU interface offset
    addr += 0x2004; //Interrupt Priority Mask Register (GICC_PMRn)

    CPU_WRW(addr, priority);
}

// Returns the value of the Interrupt Acknowledge Register
unsigned int readIntAck(void) {
    uint32_t addr, data;

    addr = getPPAddr();
    // Add CPU interface offset
    addr += 0x200C; // Interrupt Acknowledge Register (GICC_IAR)

    data = CPU_RDW(addr);
    return data;
}

//  Writes ID to the End Of Interrupt register (GICC_EOIR)
void writeEOI(unsigned int ID) {
    uint32_t addr;

    addr = getPPAddr();
    addr += 0x2010; // End of Interrupt Register

    CPU_WRW(addr, ID);
}

// Enables the sending of Group 0 interrupts as FIQs
void enableFIQs(void) {
    uint32_t addr, data;

    addr = getPPAddr();
    addr += 0x2000; // CPU Interface Control Register (GICC_CTLR)
    data = CPU_RDW(addr);
    // Bit 3: Controls whether secure interrupts are signaled as IRQs or FIQs
    CPU_WRW(addr, data | 0x8);
}

// Disables the sending of Group 0 interrupts as FIQ
void disableFIQs(void) {
    uint32_t addr, data;

    addr = getPPAddr();
    addr += 0x2000; // CPU Interface Control Register (GICC_CTLR)
    data = CPU_RDW(addr);
    // Bit 3: Controls whether secure interrupts are signaled as IRQs or FIQs
    CPU_WRW(addr, data & 0xFFFFFFF7);
}

// ------------------------------------------------------------
// TrustZone
// ------------------------------------------------------------

//Sets the specified ID as being Secure
// ID - ID of interrupt to be made Secure
void makeIntSecure(unsigned int ID) {
    uint32_t addr, data;

    addr = getPPAddr();
    addr += 0x1080;             // Interrupt Group Registers 0 (GICD_IGROUPR0)
    addr += (ID >> 5) << 2;      // GICD_IGROUPRn
    data = CPU_RDW(addr);
    data &= ~(0x1 << (ID & 0x1F));

    CPU_WRW(addr, data);
}

// Sets the ID as being NS
// ID - ID of interrupt to be made non-secure
void makeIntNonSecure(unsigned int ID) {
    uint32_t addr, data;

    addr = getPPAddr();
    addr += 0x1080;             // Interrupt Group Registers 0 (GICD_IGROUPR0)
    addr += (ID >> 5) << 2;      // GICD_IGROUPRn
    data = CPU_RDW(addr);
    data |= 0x1 << (ID & 0x1F);

    CPU_WRW(addr, data);
}

// Sets the ID for Software Interrupt
void enableSGI(unsigned int ID) {
    uint32_t addr, data;

    addr = getPPAddr();
    addr += 0x1F00;         // Software Generated Interrupt Register (GICD_SGIR)
    data = (0x1 << 16) | (0x0 << 15) | (ID & 0xF);
    CPU_WRW(addr, data);

}

// Clears Software Interrupt
void clearSGI(unsigned int ID) {
    uint32_t addr, data;

    addr = getPPAddr();
    addr += 0x1F10;             // SGI Clear-Pending Registers (GICD_CPENDSGIR0)
    addr += ID / 4;      // GICD_CPENDSGIRn
    data = CPU_RDW(addr);
    data |= (0x1 << ((ID % 4) * 8));
    CPU_WRW(addr, data);

}
