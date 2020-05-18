########################################################################
#
# QSPI Driver
#
# $Rev: 1325 $
# $Date: 2019-03-04 10:14:49 +0000 (Mon, 04 Mar 2019) $
#
########################################################################

RENESAS DOCUMENT NUMBER
=======================


OVERVIEW
========
The QSPI driver is FIT-compatible and can easily be ported to another interface (e.g. FreeRTOS / Posix).
It provides support for up to 4 SPI channels in Master mode and 2 SPI channels in Slave mode).


FEATURES
========
TBD


SUPPORTED MCUs
==============
RZ/N1D
RZ/N1S


BOARDS TESTED ON
================
 The QSPI driver has been tested on RZ/N1 development boards:
    - RZ/N1D CPU Board + Expansion Board


LIMITATIONS
===========

PERIPHERALS USED DIRECTLY
=========================


DEPENDENCIES
============
  The QSPI driver is dependent on the GPIO and System drivers.


HOW TO ADD TO YOUR PROJECT
==========================


TOOLCHAIN
=========
  IAR 8.30.2


FILE STRUCTURE
==============

