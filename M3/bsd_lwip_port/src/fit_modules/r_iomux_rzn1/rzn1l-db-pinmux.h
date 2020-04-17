/** @file
 *
 * @brief Pinmuxing for RZN/1D
 *
 * @copyright
 * (C) Copyright 2017 Renesas Electronics Corporation
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */


#ifndef RZN1L_DB_PINMUX_H
#define RZN1L_DB_PINMUX_H



/****************************************************************************/
/* Defines */
/****************************************************************************/
// Basic read
#define readl(pAddress)          (* (volatile unsigned int *) (pAddress))
// Basic write
#define writel(data, pAddress)    (* (volatile unsigned int *) (pAddress) = data)


/****************************************************************************/
/* Prototypes */
/****************************************************************************/
int rzn1lPinmux(void);
#endif /* #ifndef RZN1L_DB_PINMUX_H */
