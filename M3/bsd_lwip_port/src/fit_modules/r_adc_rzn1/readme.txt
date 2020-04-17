########################################################################
#
# ADC Driver
#
# $Rev: 1325 $
# $Date: 2019-03-04 10:14:49 +0000 (Mon, 04 Mar 2019) $
#
########################################################################

RENESAS DOCUMENT NUMBER
=======================


OVERVIEW
========
The ADC driver is FIT-compatible and can easily be ported to another interface (e.g. FreeRTOS / Posix).
It provides support for the ADC peripheral device.


FEATURES
========
Setting up single ADC pins
Setting up of groups of ADC pins
Interrupt, DMA and synchronous reading of sample values


SUPPORTED MCUs
==============
RZ/N1D
RZ/N1S
RZ/N1L


BOARDS TESTED ON
================
 The ADC driver has been tested on RZ/N1 development boards:
    - RZ/N1S CPU Board + Expansion Board


LIMITATIONS
===========
ADC2 is only available on 400pin RZ/N1D and is not supported in the driver
ADC DMA0 is supported. ADC DMA1 is not.
If using DMA on a ADC Virtual Channel Group then a buffer big enough to receive all sixteen virtual
channels should be used.

PERIPHERALS USED DIRECTLY
=========================


DEPENDENCIES
============
The ADC driver is dependent on the System and DMA drivers.


HOW TO ADD TO YOUR PROJECT
==========================


TOOLCHAIN
=========
  IAR 8.30.2


FILE STRUCTURE
==============

