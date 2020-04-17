########################################################################
#
# GPIO Driver
#
# $Rev: 1325 $
# $Date: 2019-03-04 10:14:49 +0000 (Mon, 04 Mar 2019) $
#
########################################################################

RENESAS DOCUMENT NUMBER
=======================


OVERVIEW
========
The GPIO driver is FIT-compatible and can easily be ported to another interface (e.g. FreeRTOS / Posix).
It provides support for up to X GPIO ports.


FEATURES
========



SUPPORTED MCUs
==============
RZ/N1D
RZ/N1S
RZ/N1L

BOARDS TESTED ON
================
 The GPIO driver well be tested on RZ/N1 development boards:
    - RZ/N1D CPU Board [TBD]
    - RZ/N1S CPU Board [TBD]
    - RZ/N1L CPU Board

LIMITATIONS
===========

PERIPHERALS USED DIRECTLY
=========================
GPIO

DEPENDENCIES
============
Board Support Package in r_bsp folder

HOW TO ADD TO YOUR PROJECT
==========================


TOOLCHAIN
=========
  IAR 8.30.2


FILE STRUCTURE
==============
r_gpio_rzn1                    (Folder for RZ/N1 GPIO driver files)
|   r_gpio_rzn1_if.h            (Common RZ/N1 GPIO interface definitions)
|   readme.txt                  (This file)
+---doc                        (Folder for documentation)
|   +---documentation files     (Documentation files)
+---ref                        (Folder for reference configuration)
|       r_gpio_rzn1_config_reference.h  (reference RZ/N1 GPIO driver config, to be copied to \r_config)
+---src                        (Folder for the RZ/N1 GPIO driver source)
|  |    r_gpio_rzn1.c           (Common RZ/N1 GPIO interface implementations)
|  +---targets                (Folder for target specific GPIO driver files
|     +---rzn1d              (Folder for RZ/N1D specific GPIO driver files)
|     |  r_gpio_rzn1d.c  (RZ/N1D specific driver implementation)
|     +---rzn1s              (Folder for RZ/N1S specific GPIO driver files)
|     |  r_gpio_rzn1s.h  (RZ/N1S specific driver definitions)
|     +---rzn1l              (Folder for RZ/N1L specific GPIO driver files)
|        r_gpio_rzn1l.h  (RZ/N1L specific driver definitions)
r_config                       (Folder for driver configuration copied from ref folders)
     r_gpio_rzn1_config.h        (RZ/N1 GPIO driver configuration copied from ref folder and renamed)
