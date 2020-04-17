########################################################################
#
# RTC Driver
#
# $Rev: 916 $
# $Date: 2018-11-06 16:19:43 +0000 (Tue, 06 Nov 2018) $
#
########################################################################

RENESAS DOCUMENT NUMBER
=======================


OVERVIEW
========
The RTC driver is FIT-compatible and can easily be ported to another interface (e.g. FreeRTOS / Posix).
It provides support for the Real Time Clock peripheral device.


FEATURES
========
Time reported in standard C 'tm' structure
Time programmed via standard C 'tm' structure
Alarm Interrupt (CA7 devices only)
Periodic Interrupt (CA7 devices only)
One Second Interrupt (CA7 devices only)

SUPPORTED MCUs
==============
RZ/N1D CA7
RZ/N1S CA7


BOARDS TESTED ON
================
 The RTC driver has been tested on RZ/N1 development boards:
    - RZ/N1S CPU Board + Expansion Board


LIMITATIONS
===========
RTC operates within Years 2000 and 2099.

PERIPHERALS USED DIRECTLY
=========================
Board Expander	


DEPENDENCIES
============
The RTC driver is dependent on the System driver.


HOW TO ADD TO YOUR PROJECT
==========================


TOOLCHAIN
=========
  IAR 8.30.2


FILE STRUCTURE
==============

