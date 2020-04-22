----------------------------------------------------------
N1D: Use rzn_ipcm.eww. (From rzn_lwip_socket_gmac.eww.)
N1L: FLASH_xxx is the project for our RZ/N1L based product.
----------------------------------------------------------
Linux command line arguments:
  argv[1] = sleep_time_us. 1 ms. in below example.
  argv[2] = shm_size_bytes, that is, nr bytes sent to cm3. 8B in below example. 4B absoulte minimum.
  argv[3] = show_M3_to_A7_content_flag. Show data coming from cm3 in below example.
Usage example from RZ/N linux prompt:
$/usr/bin/ipcm/pl320 1000 32 1
------------------------------------------------------------
Comments on arguments
---------------------
- sleep_time_us: 

- shm_size_bytes: 
Should be at least 8 since two first four bytes are transferred via two data registers of IPCM for verification.

- show_M3_to_A7_content_flag:
A flag controlling whether to present the 
memory content received from M3. SHM_ADDRESS is 0x200F8000 (shm.h).

Memory region A7->M3 messages @ 0x200F8000.
"-            M3->A7 messages @ 0x200FC000.
-------------------------------------------------------------


-------------------------------------------------------------
   Notes
-------------------------------------------------------------
<linux/interrupt.h> is included from ../rzn1_linux/drivers/mailbox/pl320-ipc.c
See also ./rzn1_linux/drivers/char/mailbox/mailbox.c

C:\temp\IPCM> git clone https://github.com/CarlStenquist/IPCM