########################################################################
#
# USB Driver
#
# $Rev: 344 $
# $Date: 01-Oct-2018 $
#
########################################################################



OVERVIEW
========
The USB module's structure is FIT-compatible and can easily be ported to another interface (e.g. FreeRTOS / Posix).
The USB module currently includes:
- RZ/N1 USB common interface
- RZ/N1 USB CDC Class driver
- RZ/N1 USB function basic driver

A USB device test application is included which is integrated with the OS-less sample application.
The USB device test application interfaces with the USB function CDC Class driver and USB function basic driver to emulate a virtual COM port.
If the USB function port is connected to a pc running Windows OS, data may be exchanged between the USB device test application running on the RZ/N1 board
and a terminal exmilator running under Windows e.g. TeraTerm.

In addition to the USB device test application, a set of USB Functional tests may be selected from the Sample Test application's main menu. 


SUPPORTED MCUs
==============
RZ/N1D
RZ/N1S
RZ/N1L


BOARDS TESTED ON
================
 The USB driver has been initially tested on RZ/N1 development boards:
 	- RZ/N1D Board - tested on A7 and M3
	- RZ/N1S Board - tested on A7 and M3



PERIPHERALS USED DIRECTLY
=========================
RZ/N1D CPU board :
1) CN10 USB connector connected to PC USB port for (i)Power Connector and (ii)FTDI serial-over-USB used for debug output.(CN6 jumper connected)
2) CN9 Function USB connector is connected to PC USB Host port. (CN2 jumper disconnected for USB function selection)
   The USB application running is registered as CDC Class, ACM sub-class USB application and emulates a Serial COM  (UART) port.
The equivalent jumpers and connectors are used on the RZ/N1S board.

DEPENDENCIES
============
  The USB driver is dependant on the GPIO and System drivers (r_gpio_rzn1, r_timer_rzn1 (for timers),  and r_uart_rzn1 (for debug support) and r_bsp for system support in order to work.



HOW TO ADD TO YOUR PROJECT
==========================
Sample IAR workspace and project files are included with the release so a customer project may be based on these.
- Workspace file is at https://duesvn2.ad.ree.renesas.com/systems/svnSYS_RZN1drv/branches/bare_metal_dev/RZN1_BareMetal.eww
- Project files are at https://duesvn2.ad.ree.renesas.com/systems/svnSYS_RZN1drv/branches/bare_metal_dev/src/osless_sample. 
    (i) rzn1d_osless_sample.ewp
    (ii) rzn1d_osless_sample - CA7.ewp
    (iii) rzn1S_osless_sample.ewp
    (iv) rzn1S_osless_sample - CA7.ewp
    (v)  rzn1l_osless_sample.ewp
    (vi) rzn1l_osless_sample - CA7.ewp

TOOLCHAIN
=========
  IAR IDE 8.30.2


FILE STRUCTURE
==============
 
1) Sample Application
The USB sample application and test functions are in the following files 
(located at https://duesvn2.ad.ree.renesas.com/systems/svnSYS_RZN1drv/branches/bare_metal_dev/src/osless_sample/src)
usb_tests.c
r_usb_pcdc_apl.c
r_usb_pcdc_descriptor.c

2) USB Driver
The RZ/N1 USB driver modules are structured to be compatible with the RZ/N1 Bare Metal Drivers FIT folder structure
but at the same time keeping the USBf CDC Class module files & file structure (and filenames) as ported from RZ/T1.
Three FIT modules were created for USB Function driver and the CDC Class driver (under r_usb_rzn1 FIT folder):

(i)  r_usb_common_rzn1
The ‘r_usb_common_rzn1’ module provides a way to add any generic USB API’s, e.g. to provide a 'dummy' API function to call a basic or core layer function directly
 or for generic USB interface.
For example,  if want to add another Class driver at a later stage or Host functionality there may be some common functions required which then call functions in the module
for the selected class.

(ii)  r_usbf_basic_rzn1
basic or core USB function driver. Upper API, as defined in r_usbf_basic_if.h is compatible with USBf CDC Class module as ported from RZ/T1. 
So, the API function names are not entirely of the same format as our other RZ/N1 bare metal drivers.
The other incompatibility with the other RZ/N1 bare metal drivers is that the API for this module is not accessed directly from a user application but, generally,
the functions are called from r_usb_common_rzn1 or r_usbf_cdc_rzn1 modules. (See fig. 1).

(iii)  r_usbf_cdc_rzn1
This module is ported from RZ/T1. The API header file is moved to the module’s top-level folder for FIT compatibility
Folder structure for USB driver modules located at
https://duesvn2.ad.ree.renesas.com/systems/svnSYS_RZN1drv/branches/bare_metal_dev/src/fit_modules/r_usb_rzn1
is as shown below.

r_usb_rzn1 / r_usb_common_rzn1 / doc
                               / ref
                               / src / r_usb_rzn1_if.c
                                       r_usb_common.h
                                       r_usb_rzn1_reg_defs.h (current USB register definitions - will be replaced by SFR header files for the next release)
                                       USBf_AHBEPC_SFR.h (will replace r_usb_rzn1_reg_defs.h)
                                       USBf_EPC_SFR.h (will replace r_usb_rzn1_reg_defs.h)
                               / r_usb_rzn1_if.h
    
    
    
r_usb_rzn1 / r_usbf_basic_rzn1 / doc
                               / ref
                               / src / r_usbf_basic_rzn1_if.c
                                       r_usbf_core.c 
                                       r_usbf_driver.c
                                       r_usb_hal.c
                                       r_usb_controlrw.c
                                       r_usb_cdataio.c
                                       r_usbf_core.h
                                       r_usbf_hal.h 
                                       r_usbf_driver.h
                                       r_usb_cdefusbip.h
                               / r_usbf_basic_rzn1_if.h
    
    
r_usb_rzn1 / r_usbf_cdc_rzn1  / doc
                              / ref
                              / src / r_usb_pcdc_api.c
                                      r_usb_pcdc_driver.c
                                      r_usb_pcdc_local.h 
                              / r_usb_pcdc_if.h




Build and Test
=================
Connect CN9 and CN10 USB ports to a pc. (connect jumper CN6 and disconnect jumper CN2 on RZ/N1D).
Run Tera Term or a similar terminal emulator on the pc and select the COM port connected to the power/FTDI USB RZ/N1 port (CN10 on RZ/N1D board)
and associated with FTDI serial-over-USB for debug output.
Settings for the debug connection are 115200 bits/sec, 8-bit data, no parity, 1 stop bit no flow control.

Build the project (IAR project files are included with the release). All project files are listed under section 'HOW TO ADD TO YOUR PROJECT'.
Download to the RZ/N1d board using the I-jet debug probe.

Run the application and select 'USB tests' then follow the menu selections.

When the USB CDC device has been enumerated by the Host (Windows), then run another instance of the terminal emulator and select the COM port connected
to the USB function port on the RZ/N1 board (CN9 on RZ/N1D). Settings for this COM port are as for the debug port.



LIMITATIONS
===========
1) USB function driver has been implemented and tested.
2) Functional Tests have been implemented and tested but should be extended to test for more error conditions.
3) USBf driver not yet tested on L board because USB function port not functional and requires more investigation to get it setup.
Then the USBf function driver should run on the L board as it does currently on the D and S boards.
4) DMA mode not tested.



