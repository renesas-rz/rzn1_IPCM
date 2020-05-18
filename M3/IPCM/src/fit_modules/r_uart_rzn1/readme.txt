########################################################################
#
# UART Driver
#
# $Rev: 1325 $
# $Date: 2019-03-04 10:14:49 +0000 (Mon, 04 Mar 2019) $
#
########################################################################

RENESAS DOCUMENT NUMBER
=======================


OVERVIEW
========
The UART driver is FIT-compatible and can easily be ported to another interface (e.g. FreeRTOS / Posix).
It provides support for up to 8 UARTS, Rx and Tx, interrupt-driven).


FEATURES
========
The default UART setting for serial output is: 115200bps, 8-data bits, no parity, 1 - stop bit (115200-8-N-1)


SUPPORTED MCUs
==============
RZ/N1D
RZ/N1S
RZ/N1L


BOARDS TESTED ON
================
 The UART driver has been tested on RZ/N1 development boards:
    - RZ/N1D CPU Board + Expansion Board
    - RZ/N1S CPU Board + Expansion Board
    - RZ/N1L CPU Board


LIMITATIONS
===========

PERIPHERALS USED DIRECTLY
=========================


DEPENDENCIES
============
  The UART driver is dependent on the GPIO and System drivers (r_gpio and r_system) in order to work.

  Serial Flash Debug:
    This configuration is for loading to Serial Flash memory and debugging from Serial Flash memory
    and from instruction RAM. Debug output is sent to UART1.



HOW TO ADD TO YOUR PROJECT
==========================


TOOLCHAIN
=========
  IAR 8.30.2


FILE STRUCTURE
==============

