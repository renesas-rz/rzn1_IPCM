########################################################################
#
# LCDC Driver
#
# $Rev: 344 $
# $Date: 2019-02-19 14:07:39 +0000 (Fri, 09 Feb 2018) $
#
########################################################################

RENESAS DOCUMENT NUMBER
=======================


OVERVIEW
========
The LCDC driver is FIT-compatible and can easily be ported to another interface (e.g. FreeRTOS / Posix).
It provides support for 1 Port TFT LCD Panel.


FEATURES
========


SUPPORTED MCUs
==============
RZ/N1D
RZ/N1S


BOARDS TESTED ON
================
 The LCDC driver has been tested on RZ/N1 development boards:
    - RZ/N1D CPU Board + Expansion Board
    - RZ/N1S CPU Board + Expansion Board


LIMITATIONS
===========


PERIPHERALS USED DIRECTLY
=========================
Board Expander
Multiplexer
TFT LCD Panel

DEPENDENCIES
============
The LCDC driver is dependent on the System, Port Expander IOMUX and GPIO drivers.


HOW TO ADD TO YOUR PROJECT
==========================


TOOLCHAIN
=========
  IAR 8.30.2


FILE STRUCTURE
==============

src/fit_modules/r_lcdc_rzn1 / r_lcdc_rzn1 / doc
                          / ref / r_lcdc_rzn1_config_reference.h
                          / src / r_lcdc_rzn1_if.c
                                / r_lcdc_rzn1.c 
                                / r_lcdc_rzn1.h
                         r_lcdc_rzn1_if.h

LIMITATIONS
===========
None
