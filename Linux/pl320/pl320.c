/**********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* $Revision: 1.00
* $Date: 2020-05-01 12:00:00 +0000 (Fri, 1 May 2020) $
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
**********************************************************************************************************************/
/****************************************************************
 Usage example from RZ/N linux prompt:
 $/usr/bin/ipcm/pl320 100000 8 1
 where;
  argv[1] =         sleep_time_us. This is the interval at which the A7 sends data to M3. (0.1 sec. in above example.)
  argv[2] =         shm_size_bytes, that is, nr bytes sent to cm3. (8 B in this case. 4 B minimum.)
  argv[3] =         show_M3_to_A7_content_flag. (Show data from cm3 in this case.)
****************************************************************/

/********************************************************************************
Includes
********************************************************************************/
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <asm/unistd.h>
#include <stdlib.h>
#include <pthread.h>

#include "pl320.h"
#include "shm.h"

/********************************************************************************
Defines
********************************************************************************/
/********************************************************************************
Types, structs
********************************************************************************/
/********************************************************************************
Global variables
********************************************************************************/
/********************************************************************************
Externals
********************************************************************************/
/********************************************************************************
Global variables (exports)
********************************************************************************/
/* Set show_M3_to_A7_content_flag to 1  to verify that M3 is running OK,
however it consumes much CPU cycles via serial output. */
int show_M3_to_A7_content_flag = 0;

/********************************************************************************
Static (private) functions
********************************************************************************/
/********************************************************************************
Static (private) variables
********************************************************************************/
static unsigned int tx_buf[IPCM_DATA_REG_NUM];
/* File descriptor for core#2 = linux. Core #0 is CM3 */
static int 	      fd_2;
static int 	      in_thread_cnt = 0;

/* m3_to_a7_task is a pthread. */
static pthread_t  m3_to_a7_task_id;
  
/********************************************************************************
* Function (thread) define: M3_to_A7_task(). 
********************************************************************************/
void* M3_to_A7_task(void *arg)
{
  UNUSED(arg);
  int result;
  void *virt_addr;

  virt_addr = init_shm_M3_to_A7();
  unsigned int rx_buf[IPCM_DATA_REG_NUM];

  while(1)
  {
    result = read(fd_2, &rx_buf, IPCM_DATA_REG_NUM * sizeof(unsigned int));
    check_memory(rx_buf[1], rx_buf[2], rx_buf[3], virt_addr);	//See shm.c
    in_thread_cnt++;
  }
  return NULL;
}/* end M3_to_A7_task() */

/********************************************************************************
* Function define: main()
********************************************************************************/
int main(int argc, char *argv[])
{
  UNUSED(argc);
  int main_fd;
  int result;
  void *virt_addr;

  int cycle = 0;
  int ipcm_tx_cnt = 1;
  int err;
  
  /* USER COMMAND LINE ARGUMENTS. */
  int sleep_time_us = (int)atoi(argv[1]);
  int shm_size_bytes = atoi(argv[2]);
  //if ((atoi(argv[3] != 0)) && (atoi(argv[3] != 1)))
    //printf("argumet 3 show_M3_to_A7_content_flag must be 0 or 1.\n");
  show_M3_to_A7_content_flag = atoi(argv[3]);
  
  /* Check arguments. */
  printf("Sleep time is %d us.\n", sleep_time_us);
  if((shm_size_bytes <= 0) || ((shm_size_bytes%4) != 0))
  {
    printf("Memory size (2nd arg.) must be 8 or more and divisible by 4\n");
    return -1;
  }  
  
  /* See ~/rzn_dev_setup/rzn1_linux-4.19_bsp/output/rzn1_linux/drivers/mailbox/pl320-ipc.c. */
  printf("Open MBOX_DEVICE_MASTER_NAME = %s..\n", MBOX_DEVICE_MASTER_NAME);

  /* MBOX_DEVICE_MASTER_NAME defined in linux. ./rzn1_linux-4.19_bsp/output/rzn1_linux/drivers/char/mailbox. */
  main_fd = open(MBOX_DEVICE_MASTER_NAME, O_WRONLY);
  if (main_fd < 0)
  {
    printf("Failed to open %s\n.", MBOX_DEVICE_MASTER_NAME);
    return -1;
  }

  /* Create new mailbox device. Core is #2 of the RZ/N. There are two A7 cores running in SMP mode. */
  result = ioctl(main_fd, MBOX_IOCTL_CREATE, 2);
  printf("ioctl result MBOX_IOCTL_CREATE (core #2) = %d\n", result);
  close(main_fd);

  printf("Open /dev/mbox_2 in RW mode.\n.");
  fd_2 = open("/dev/mbox_2", O_RDWR);

  if (fd_2 < 0)
  {
    printf("Could not open /dev/mbox_2.\n");
    return -1;
  }
  virt_addr = init_shm_A7_to_M3(SHM_ADDRESS, SHM_SIZE/2);
  err = pthread_create(&m3_to_a7_task_id, NULL, &M3_to_A7_task, NULL);

  while(1)
  {
    /* if sleep time is zero, don't waste time for the call. */
    if (sleep_time_us != 0)
    {
      usleep((long)sleep_time_us);
    }
    
    cycle = cycle + shm_size_bytes/4;
    write_to_shm(cycle, virt_addr, shm_size_bytes);

    // the first 4 bytes of IPCM data registers currently are used for Core ID. It's especially visible while RXing on Linux.
    // Let's not touch the first four bytes of until we recompile RZ/N1D Linux kernel
    // Filling #1 and #2 IPCM data registers with cycle pattern to verify the consistency on M3 side
    tx_buf[1] = cycle;
    tx_buf[2] = cycle + 1;

    // Passing the memory size through IPCM data register #3
    tx_buf[3] = shm_size_bytes;

    result = write(fd_2, tx_buf, IPCM_DATA_REG_NUM * sizeof(unsigned int));
    ipcm_tx_cnt++;

    if (result != IPCM_DATA_REG_NUM * sizeof(unsigned int))
    {
      printf("write err %d", result);
      perror("Error:\n");
    }
  }
}/* end main() */
/* file end */