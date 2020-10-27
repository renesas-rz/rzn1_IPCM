----------------------------------------------------------
N1D M3 core: Use rzn_ipcm.eww.
----------------------------------------------------------
N1D A7 core3:
Linux command line arguments:

  argv[1] = sleep_time_us. 1 ms. in below example.
  argv[2] = shm_size_bytes, that is, nr bytes sent to cm3. 8B in below example. 4B absoulte minimum.
  argv[3] = show_M3_to_A7_content_flag. Show data coming from cm3 in below example.

Usage example from RZ/N linux prompt:
$/usr/bin/ipcm/pl320 1000 32 1

Comments on arguments
---------------------
- sleep_time_us: 
number of microseconds between transmission A7=>M3.

- shm_size_bytes: 
Should be at least 8 since two first four bytes are transferred via two data registers of IPCM for verification.

- show_M3_to_A7_content_flag:
A flag, 0 or 1, controlling whether to output start of memory content received from M3. SHM_ADDRESS is 0x200F8000 (shm.h).

Memory region A7->M3 messages @ 0x200F8000.
"-            M3->A7 messages @ 0x200FC000.
-------------------------------------------------------------

-------------------------------------------------------------
   Notes
-------------------------------------------------------------
<linux/interrupt.h> is included from ../rzn1_linux/drivers/mailbox/pl320-ipc.c
See also ./rzn1_linux/drivers/char/mailbox/mailbox.c
