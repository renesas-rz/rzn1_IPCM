/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer *
* Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name    : eth_hwfnc.c
* Description  : Hardware Function Call driver.
*******************************************************************************/
/*******************************************************************************
* History      : DD.MM.YYYY Version  Description
*              : 25.08.2017 0.1      Preliminary version
*******************************************************************************/

/*******************************************************************************
Includes <System Includes> , "Project Includes"
*******************************************************************************/
#include "stdint.h"
#include "eth/eth_hwfnc.h"
#include "RZN1.h"

/******************************************************************************
Macro definitions
******************************************************************************/
#define	HWRTOS_SYSCALL_PRI				0x80				// priority during systemcall

#define R0_SYSTEM_CALL					(0x20000000)		/* R0[29] */

/* HW Function Call:Buffer Allocator */
#define	SYSC_hwfnc_longbuffer_get		(0x5000)
#define	SYSC_hwfnc_shortbuffer_get		(0x5006)
#define	SYSC_hwfnc_buffer_release		(0x5001)
#define	SYSC_hwfnc_buffer_return		(0x5002)
#define	SYSC_hwfnc_longbuffer_link		(0x5007)

/* HW Function Call : DMAC */
#define	SYSC_hwfnc_macdma_tx_start		(0x5100)
#define	SYSC_hwfnc_macdma_rx_enable		(0x5101)
#define	SYSC_hwfnc_macdma_rx_disable	(0x5102)
#define	SYSC_hwfnc_intdma_start			(0x5104)
#define	SYSC_hwfnc_intdma_start_desc	(0x5114)
#define	SYSC_hwfnc_macdma_rx_control	(0x510b)
#define	SYSC_hwfnc_macdma_tx_errstat	(0x510c)
#define	SYSC_hwfnc_macdma_rx_errstat	(0x510d)

/* HW Function Call:  */
#define	SYSC_hwfnc_wlan_enc				(0x5200)
#define	SYSC_hwfnc_wlan_dec				(0x5201)
#define	SYSC_hwfnc_gbe_enc				(0x5202)
#define	SYSC_hwfnc_gbe_dec				(0x5203)
#define	SYSC_hwfnc_snap_dec				(0x5205)
#define	SYSC_hwfnc_ip4_enc				(0x5206)
#define	SYSC_hwfnc_ip4_dec				(0x5207)
#define	SYSC_hwfnc_ip6_enc				(0x5208)
#define	SYSC_hwfnc_ip6_dec				(0x5209)
#define	SYSC_hwfnc_tcp_enc				(0x520a)
#define	SYSC_hwfnc_tcp_dec				(0x520b)
#define	SYSC_hwfnc_udp_enc				(0x520c)
#define	SYSC_hwfnc_udp_dec				(0x520d)
#define	SYSC_hwfnc_arp_enc				(0x520e)
#define	SYSC_hwfnc_arp_dec				(0x520f)
#define	SYSC_hwfnc_dsc_trns				(0x5210)
#define	SYSC_hwfnc_dmt					(0x5211)
#define	SYSC_hwfnc_dmr					(0x5212)

#define ETHERC  (*(volatile struct st_etherc  *)(0x400E0000))

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* Common Interface */
typedef struct {
	UINT    r0;                         /*!< R0             */
	UINT    r1;                         /*!< R1             */
}SYSCALL_RETURN;

/* HW-RTOS HWFC (Hardware Function Call) Register */
struct st_etherc
{
    union
    {
        unsigned long LONG;
    } C0TYPE;
    char           wk2[4];
    union
    {
        unsigned long LONG;
    } C0STAT;
    char           wk3[61428];
    union
    {
        unsigned long LONG;
    } SYSC;
    union
    {
        unsigned long LONG;
    } R4;
    union
    {
        unsigned long LONG;
    } R5;
    union
    {
        unsigned long LONG;
    } R6;
    union
    {
        unsigned long LONG;
    } R7;
    union
    {
        unsigned long LONG;
    } CMD;
    char           wk4[8];
    union
    {
        unsigned long LONG;
    } R0;
    union
    {
        unsigned long LONG;
    } R1;
};

/*******************************************************************************
Imported global variables and functions (from other files)
*******************************************************************************/

/*******************************************************************************
Exported global variables and functions (to be accessed by other files)
*******************************************************************************/

/*******************************************************************************
Private variables and functions
*******************************************************************************/
static SYSCALL_RETURN hwos_exec_systemcall_nochange(UINT cmd, UINT r4, UINT r5, UINT r6, UINT r7 );


/**
 ******************************************************************************
  @brief  System call
  @param  cmd -- Command
  @param  r4  -- parameter
  @param  r5  -- parameter
  @param  r6  -- parameter
  @param  r7  -- parameter
  @retval Result
 ******************************************************************************
*/
static SYSCALL_RETURN hwos_exec_systemcall_nochange(UINT cmd, UINT r4, UINT r5, UINT r6, UINT r7 )
{
	UINT	savedBasePri;
	SYSCALL_RETURN syscall_return;

#if !defined (OSLESS)
	// ## CRITICAL SECTION begin ####################################################
	savedBasePri = __get_BASEPRI();
	__set_BASEPRI(HWRTOS_SYSCALL_PRI);
#endif

    //--------------------------
	// Set parameter
    //--------------------------
	ETHERC.R4.LONG = r4;
	ETHERC.R5.LONG = r5;
	ETHERC.R6.LONG = r6;
	ETHERC.R7.LONG = r7;

    //--------------------------
	// Execute system call
    //--------------------------
	ETHERC.SYSC.LONG = cmd;

    //--------------------------
	// Wait until system call finish
    //--------------------------
    // --- Load R0 & check system call finish ---
    do {
		syscall_return.r0 = ETHERC.R0.LONG;
	} while ((syscall_return.r0 & R0_SYSTEM_CALL) != R0_SYSTEM_CALL);

    // --- Load R1 ---
	syscall_return.r1 = ETHERC.R1.LONG;

#if !defined (OSLESS)
	// ## CRITICAL SECTION end ####################################################
	__set_BASEPRI(savedBasePri);
#endif

	return syscall_return;
}

//=============================================================================================
// Buffer Allocator
//=============================================================================================
/**
 ******************************************************************************
  @brief  Get long buffer
  @param  len -- len[15:0] Buffer length, len[23:16] Max LLSN
  @retval Top address of the long buffer (The value are more then 0x0C000000)
  @retval NULL -- Error
 ******************************************************************************
*/
void *hwfnc_longbuffer_get(UINT par)
{

	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_longbuffer_get,		// cmd
	                                               par,								// r4
	                                               0,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	if ( (syscall_return.r0 & 0x2) == 0x2 ) {
		return NULL;						// Error
	} else {
		return (void *)syscall_return.r1;				// Successful
	}
}

/**
 ******************************************************************************
  @brief  Get short buffer
  @param  len -- len[15:0] Buffer length
  @retval Top address of the long buffer (The value are more then 0x08000000)
  @retval NULL -- Error
 ******************************************************************************
*/
void *hwfnc_shortbuffer_get(UINT len)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_shortbuffer_get,		// cmd
	                                               len,								// r4
	                                               0,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	if ( (syscall_return.r0 & 0x2) == 0x2 ) {
		return NULL;						// Error
	} else {
		return (void *)syscall_return.r1;				// Successful
	}
}

/**
 ******************************************************************************
  @brief  Release buffer
  @param  top -- Top address of the buffer
  @retval 0, 1 -- Successful
  @retval 2    -- Invalid system call
  @retval 3    -- Unsuccessful, because buffer is not defined
 ******************************************************************************
*/
UINT hwfnc_buffer_release(UINT top)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_buffer_release,		// cmd
	                                               top,								// r4
	                                               0,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	return syscall_return.r0;
}

/**
 ******************************************************************************
  @brief  Retern buffer
  @param  top  -- Top address of the buffer
  @param  addr -- Top address of release
  @retval 0, 1 -- Successful
  @retval 2    -- Invalid system call
  @retval 3    -- Unsuccessful, because buffer is not defined
  @retval 4    -- Unsuccessful, because buffer was already released
 ******************************************************************************
*/
UINT hwfnc_buffer_return(UINT top, UINT addr)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_buffer_return,		// cmd
	                                               top,								// r4
	                                               addr,							// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	return syscall_return.r0;
}

/**
 ******************************************************************************
  @brief  Link long buffer
  @param  src    -- Top address of the buffer
  @retval *p_sta --  0,1 : Successful
  @retval *p_sta --  2   : Invalid system call
  @retval *p_sta --  3   : Unsuccessful, because could not get buffer
  @retval *p_sta --  4   : Unsuccessful, because [src]buffer not exist
  @retval *p_sta --  5   : Unsuccessful, because [src]buffer don't align 2048 byte
  @retval *p_sta --  6   : Unsuccessful, because buffer was already used
  @retval Top address of the buffer
  @retval NULL -- Error
 ******************************************************************************
*/
void *hwfnc_longbuffer_link(UINT src, UINT *p_sta)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_longbuffer_link,		// cmd
	                                               src,								// r4
	                                               0,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*p_sta = syscall_return.r0;				// Status

	if ( (syscall_return.r0 & 0x6) != 0x00 ) {
		return NULL;						// Error
	} else {
		return (void *)syscall_return.r1;				// Successful
	}
}

//=============================================================================================
// Header EnDec
//=============================================================================================
/**
 ******************************************************************************
  @brief  Encode GBE
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_gbe_enc(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_gbe_enc,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Decode GBE
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_gbe_dec(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_gbe_dec,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Decode SNAP
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_snap_dec(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_snap_dec,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Encode IPv4
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_ip4_enc(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_ip4_enc,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Decode IPv4
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_ip4_dec(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_ip4_dec,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Encode IPv6
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_ip6_enc(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_ip6_enc,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Decode IPv6
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_ip6_dec(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_ip6_dec,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Encode TCP
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_tcp_enc(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_tcp_enc,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Decode TCP
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_tcp_dec(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_tcp_dec,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Encode UDP
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_udp_enc(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_udp_enc,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Decode UDP
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_udp_dec(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_udp_dec,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Encode ARP
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_arp_enc(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_arp_enc,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Decode ARP
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_arp_dec(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_arp_dec,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Transfer descriptor
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_dsc_trns(UINT src, UINT dst, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_dsc_trns,				// cmd
	                                               src,								// r4
	                                               dst,								// r5
	                                               0,								// r6
	                                               0);								// r7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Direct memory transfer
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  bytes -- Transfer bytes
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_dmt(UINT src, UINT dst, UINT bytes, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_dmt,					// cmd
	                                               src,								// R4[31:0] -- Source address
	                                               dst,								// R5[31:0] -- Destination address
	                                               bytes,							// R6[15:0] -- Transfer bytes
	                                               0);								// R7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  Direct memory replace
  @param  ptn   -- Write data pattern
  @param  dst   -- Destination address
  @param  words -- Write words (must more then 4 words)
  @param  *excp -- Exception address (if successful, *excp is 0)
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Exception
 ******************************************************************************
*/
UINT hwfnc_dmr(UINT ptn, UINT dst, UINT words, UINT *excp)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_dmr,					// cmd
	                                               ptn,								// R4[31:0] -- Write data pattern
	                                               dst,								// R5[31:0] -- Destination address
	                                               words,							// R6[15:0] -- Write words
	                                               0);								// R7

	//---------------------------------
	// Set return value
	//---------------------------------
	*excp = syscall_return.r1;				// Exception address

	return syscall_return.r0;				// Status
}


//=============================================================================================
// DMAC (MACDMA)
//=============================================================================================
/**
 ******************************************************************************
  @brief  MACDMA transfer data to MAC from Buffer Memory [Tx start]
  @param  dsc  -- Descriptor Address
  @param  llsn -- Max LLSN
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
 ******************************************************************************
*/
UINT hwfnc_macdma_tx_start(UINT dsc, UINT llsn)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_macdma_tx_start,		// cmd
	                                               dsc,								// R4[31:0] -- Descriptor Address
	                                               0,								// R5
	                                               0,								// R6
	                                               llsn);							// R7[ 6:0] -- Max LLSN

	//---------------------------------
	// Set return value
	//---------------------------------
	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  MACDMA enable data transmission from MAC to Buffer Memory  [Rx enable]
  @param  llsn -- Max LLSN
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
 ******************************************************************************
*/
UINT hwfnc_macdma_rx_enable(UINT llsn)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_macdma_rx_enable,		// cmd
	                                               0,								// R4
	                                               0,								// R5
	                                               0,								// R6
	                                               llsn);							// R7[ 6:0] -- Max LLSN

	//---------------------------------
	// Set return value
	//---------------------------------
	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  MACDMA disable data transmission from MAC to Buffer Memory  [Rx disable]
  @param  flg -- Forced reset
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
  @retval 2 -- Unsuccessful, because receiving
  @retval 3 -- Unsuccessful, because already disabled
 ******************************************************************************
*/
UINT hwfnc_macdma_rx_disable(UINT flg)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_macdma_rx_disable,	// cmd
	                                               flg,								// R4[0] -- Forced reset
	                                               0,								// R5
	                                               0,								// R6
	                                               0);								// R7

	//---------------------------------
	// Set return value
	//---------------------------------
	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  MACDMA set rx error interrupt mask
  @param  msk -- Interrupt mask
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
 ******************************************************************************
*/
UINT hwfnc_macdma_rx_control(UINT msk)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_macdma_rx_control,	// cmd
	                                               msk,								// R4[8:0] -- Interrupt mask
	                                               0,								// R5
	                                               0,								// R6
	                                               0);								// R7

	//---------------------------------
	// Set return value
	//---------------------------------
	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  MACDMA transfer error status
  @param  none
  @retval 0 -- Memory Access Violation
  @retval 1 -- Memory Access Timeout
 ******************************************************************************
*/
UINT hwfnc_macdma_tx_errstat(void)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_macdma_tx_errstat,	// cmd
	                                               0,								// R4
	                                               0,								// R5
	                                               0,								// R6
	                                               0);								// R7

	//---------------------------------
	// Set return value
	//---------------------------------
	return syscall_return.r0;				// Status
}

/**
 ******************************************************************************
  @brief  MACDMA read rx error interrupt status
  @param  none
  @retval 0 -- Buffer get failure
  @retval 1 -- Rx info FIFO full
  @retval 2 -- Rx data size over 4092 words
  @retval 3 -- HWFNC_MACDMA_Rx_Disable
  @retval 4 -- Buffer return error
  @retval 5 -- Buffer release error
  @retval 6 -- Memory access violation
  @retval 7 -- Memory access timeout
 ******************************************************************************
*/
UINT hwfnc_macdma_rx_errstat(void)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_macdma_rx_errstat,	// cmd
	                                               0,								// R4
	                                               0,								// R5
	                                               0,								// R6
	                                               0);								// R7

	//---------------------------------
	// Set return value
	//---------------------------------
	return syscall_return.r0;
}

//=============================================================================================
// DMAC (INTBUFF DMA)
//=============================================================================================
/**
 ******************************************************************************
  @brief  INTDMA transfer data
  @param  src   -- Source address
  @param  dst   -- Destination address
  @param  bytes -- Transfer bytes
  @param  llsn  -- Max LLSN
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
 ******************************************************************************
*/
UINT hwfnc_intbuff_dma_start1(UINT dst, UINT src, UINT bytes, UINT llsn)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_intdma_start,			// cmd
	                                               src,								// R4[31:0] -- Source address
	                                               dst,								// R5[31:0] -- Destination address
	                                               bytes,							// R6[15:0] -- Transfer bytes
	                                               llsn);							// R7[ 6:0] -- Max LLSN

	//---------------------------------
	// Set return value
	//---------------------------------
	return syscall_return.r0;
}

/**
 ******************************************************************************
  @brief  INTDMA transfer data
  @param  ddsc -- Top address of descriptor source
  @param  sdsc -- Top address of descriptor destination
  @param  llsn -- Max LLSN
  @retval 0 -- Successful
  @retval 1 -- Invalid system call
 ******************************************************************************
*/
UINT hwfnc_intbuff_dma_start2(UINT ddsc, UINT sdsc, UINT llsn)
{
	SYSCALL_RETURN	syscall_return;

	//---------------------------------
	// Execute system call
	//---------------------------------
	syscall_return = hwos_exec_systemcall_nochange(SYSC_hwfnc_intdma_start_desc,	// cmd
	                                               ddsc,							// R4[31:0] -- Top address of descriptor source
	                                               sdsc,							// R5[31:0] -- Top address of descriptor destination
	                                               0,								// R6
	                                               llsn);							// R7[ 6:0] -- Max LLSN

	//---------------------------------
	// Set return value
	//---------------------------------
	return syscall_return.r0;
}

/* End of File */


// it is a wrapper of hwfnc_buffer_release to easier handle the return codes
int hwfnc_buffer_free(UINT ptr)
{
  UINT rc;
  rc = hwfnc_buffer_release(ptr);

  if (!(rc & HW_BUFFER_RELEASE_CALL_COMPLETED) || (rc & HW_BUFFER_RELEASE_INVALID_SYSTEM_CALL) || (rc & HW_BUFFER_RELEASE_UNDEFINED_BUFFER))
  {
    return -1;
  }

  return 0;
}

// it is a wrapper of hwfnc_longbuffer_get/hwfnc_shortbuffer_get to easier handle allocation errors
void *hwfnc_malloc(UINT size)
{
  void *ptr;
  if (size <= 512)
  {
    ptr = hwfnc_shortbuffer_get(size);
  }
  else if ((size > 512) && (size <=2048))
  {
    ptr = hwfnc_longbuffer_get(size);
  }
  else
  {
    ptr = NULL;
  }

  if (ptr != NULL)
  {
    return ptr;
  }

  return NULL;
}
