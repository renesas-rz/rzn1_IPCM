########################################################################
#
# IIC Driver
#
# $Rev: 1325 $
# $Date: 2019-03-04 10:14:49 +0000 (Mon, 04 Mar 2019) $
#
########################################################################

RENESAS DOCUMENT NUMBER
=======================


OVERVIEW
========
The IIC driver is FIT-compatible and can easily be ported to another interface (e.g. FreeRTOS / Posix).
It provides support for up to 2 IIC interfaces in Master or Slave mode.

For the RZ/N1D board, only 1 IIC interface, in Master mode, will be tested,


FEATURES
========
TBD


SUPPORTED MCUs
==============
RZ/N1D
RZ/N1S
RZ/N1L


BOARDS TESTED ON
================
 The IIC driver has been tested on RZ/N1 development boards:
 	- RZ/N1D CPU Board + Expansion Board
 	- RZ/N1S CPU Board + Expansion Board
 	- RZ/N1L CPU Board


LIMITATIONS
===========
Master mode & 1 IIC interface on RZ/N1D board

PERIPHERALS USED DIRECTLY
=========================
Board Expander
Multiplexer
EEPROM

DEPENDENCIES
============
The IIC driver is defendent on the System, Port Expander and EEPROM drivers.


HOW TO ADD TO YOUR PROJECT
==========================


TOOLCHAIN
=========
  IAR 8.30.2


FILE STRUCTURE
==============

