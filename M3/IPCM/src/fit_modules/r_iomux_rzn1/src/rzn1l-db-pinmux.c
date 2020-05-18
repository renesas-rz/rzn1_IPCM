/** @file
*
* @brief PIN multiplexing for RZ/N1
*
* @copyright
* (C) Copyright 2017 Renesas Electronics Corporation
* This software is protected Intellectual Property and may only be used
* according to the license agreement.
*/


#include "rzn1l-db-pinmux.h"
#define USE_DEFAULT_PINMUX
#include "rzn1l-board-pinmux.h"

/****************************************************************************/
/** RZ/N1 setup pinmux
*
* Called early during device initialization.
*
* @return GOAL_OK - success
* @return GOAL_ERROR - error initializing board
*/
int rzn1lPinmux(void)
{
  int res = 1;                                /* result */
  
#if 1 //(GOAL_CONFIG_ETHERNET == 1)
  
  res = rzn1_board_pinmux(RZN1_P_ETH0);
  
  if (res) {
    /* configure IoMux MAC4 */
    res = rzn1_board_pinmux(RZN1_P_ETH3);
  }
  
  if (res) {
    /* configure IoMux MAC5 */
    res = rzn1_board_pinmux(RZN1_P_ETH4);
  }
#endif /* GOAL_CONFIG_ETHERNET */
  
  /* configure IoMux MIIRFCLK */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_REFCLK);
  }
  
  /* configure IoMux SerialFlash */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_QSPI0);
  }
  
#if (GOAL_CONFIG_SPI_RZN == 1)
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_SPI4);
  }
#endif
  
#if 1 //(GOAL_CONFIG_ETHERCAT == 0)
  /* configure IoMux SWITCH */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_SWITCH);
  }
#endif
  
  /* configure IoMux GPIO0A & GPIO0B */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_GPIO0);
  }
  /* configure IoMux GPIO1A & GPIO1B */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_GPIO1);
  }
  
  /* configure IoMux I2C */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_I2C1);
  }
  
  /* configure IoMux UART1 (is UART0 - note the file description) */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_UART0);
  }
  
#if CONFIG_MODBUS_STACK == 1
  /* configure IoMux UART4 (is UART3 - note the file description) */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_UART3);
  }
#endif /* GOAL_CONFIG_MODBUS_STACK == 1 */
  
#if 0 //(GOAL_CONFIG_ETHERCAT == 1)
  /* configure IoMux ECAT */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_CAT);
  }
  /* configure IoMux ECAT Port A */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_ETH4);
  }
  /* configure IoMux ECAT Port B */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_ETH3);
  }
#endif
  
  /* configure IoMux MDIO2 (is MDIO1 - note the file description) */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_MDIO1);
  }
  
  /* This is special 'virtual' pins for the MDIO multiplexing */
  if (res) {
    res = rzn1_board_pinmux(RZN1_P_MDIO0);
  }
  
  if (!res) 
  {
    return -1;
  }
  return 0;
}
