########################################################################
#
# CAN Driver
#
# $Rev: 1325 $
# $Date: 2019-03-04 10:14:49 +0000 (Mon, 04 Mar 2019) $
#
########################################################################

RENESAS DOCUMENT NUMBER
=======================


OVERVIEW
========
The CAN driver is FIT-compatible and can easily be ported to another interface (e.g. FreeRTOS / Posix).
It provides support for the CAN peripheral device.


FEATURES
========
Various Bitrate speeds, Synchronisation pulses, Acceptance filters and masks including on RTR bit. 
Error reporting and bus event metrics.


SUPPORTED MCUs
==============
RZ/N1D
RZ/N1S
RZ/N1L


BOARDS TESTED ON
================
 The CAN driver has been tested on RZ/N1 development boards:
 	- RZ/N1S CPU Board + Expansion Board


LIMITATIONS
===========


PERIPHERALS USED DIRECTLY
=========================
CAN Peripheral


DEPENDENCIES
============
The CAN driver is dependent on the System driver.


HOW TO ADD TO YOUR PROJECT
==========================


TOOLCHAIN
=========
  IAR 8.30.2


FILE STRUCTURE
==============

