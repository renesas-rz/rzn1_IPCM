########################################################################
#
# SPI Driver
#
# $Rev: 160 $
# $Date: 2017-10-03 11:40:57 +0100 (Tue, 03 Oct 2017) $
#
########################################################################

RENESAS DOCUMENT NUMBER
=======================


OVERVIEW
========
The SPI driver is FIT-compatible and can easily be ported to another interface (e.g. FreeRTOS / Posix).
It provides support for up to 6 SPI Channels, Read, Write and Read/Write capability, synchronous and asynchronous transfers 
and is interrupt-driven.


FEATURES
========
DMA Support.


SUPPORTED MCUs
==============
RZ/N1D
RZ/N1S


BOARDS TESTED ON
================
 The SPI driver has been tested on RZ/N1 development boards:
    - RZ/N1D CPU Board + Expansion Board
    - RZ/N1S CPU Board + Expansion Board


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

