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

#include "shm.h"

/********************************************************************************
Defines
********************************************************************************/
#define SHM_ADDR     ((unsigned int *)0x200F8000)

/********************************************************************************
Types, structs
********************************************************************************/
/********************************************************************************
Global variables
********************************************************************************/
/********************************************************************************
Externals
********************************************************************************/
extern int show_M3_to_A7_content_flag;

/********************************************************************************
Global variables (exports)
********************************************************************************/
/********************************************************************************
Static (private) functions
********************************************************************************/
/********************************************************************************
Static (private) variables
********************************************************************************/
static int 		A3_to_A7_mem_read_cnt = 0;
static int 		read_cnt = 0;
static int 		error = 0;
static void* 	map_base;
  
/********************************************************************************
* Function define: init_shm_A7_to_M3()
********************************************************************************/
void* init_shm_A7_to_M3(off_t shm_address, int shm_size)
{
  int fd_map;         /* file descriptor for map */
  void *virt_addr;
  //off_t target = SHM_ADDRESS;

  fd_map = open("/dev/mem", O_RDWR | O_SYNC);
  printf("fd_map: %d _SC_PAGE_SIZE: %ld\n", fd_map, sysconf(_SC_PAGE_SIZE));  //$REA

  map_base = (unsigned int*)mmap(0, shm_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd_map, shm_address & ~MAP_MASK);
  if(map_base == (void *) -1)
  {
    printf("mmap failed\n");
  }
  else
  {
    printf("init_shm_A7_to_M3() map_base=0x%X\n", map_base);
  }

  virt_addr = (char*)(map_base + (shm_address & MAP_MASK));
  return virt_addr;
}/* end init_shm_A7_to_M3

/********************************************************************************
* Function define: write_to_shm()
*********************************************************************************/
void write_to_shm(int cnt, void *addr, int shm_region_size_bytes)
{

  for(int i = 0 ; i < shm_region_size_bytes/4 ; i++)
  {
    *(((unsigned long *) addr) + i) = cnt++;
  }
}/* end write_to_shm() */

/********************************************************************************
* Function define: check_memory()
*********************************************************************************/
void check_memory(unsigned int ipcm_d1, unsigned int ipcm_d2, unsigned int shm_size_bytes, void *shared_ram)
{
  A3_to_A7_mem_read_cnt++;
  unsigned int *mem_content;

  mem_content = (unsigned int *)malloc(shm_size_bytes);

  for(unsigned int i = 0 ; i < shm_size_bytes/4 ; i++)
  {
    mem_content[i] = *(((unsigned long *) shared_ram ) + i);
  }

  if(show_M3_to_A7_content_flag == 1)
  {
    printf("M3->A7 data size %d bytes: 0x%X 0x%X 0x%X 0x%X 0x%X\n",shm_size_bytes, mem_content[0], mem_content[1], mem_content[2], mem_content[3], mem_content[4]);
  }

  for(unsigned int i = 0 ; i < (shm_size_bytes/4) - 1 ; i++)
  {
    if(mem_content[i] != (mem_content[i+1] - 1))
    {
      printf("A3_to_A7 error: A3_to_A7_mem_read_cnt: %d Errors: %d\n", A3_to_A7_mem_read_cnt, error);
      error++;
    }
  }

  if (ipcm_d2 != (ipcm_d1 + 1) || (ipcm_d1 != mem_content[0]) || (ipcm_d2 != mem_content[1]))
  {
    printf("IPCM DR, A3_to_A7 error: A3_to_A7_mem_read_cnt: %d errors: %d %x %x %x %x.\n", A3_to_A7_mem_read_cnt, error, ipcm_d1, ipcm_d2, mem_content[0], mem_content[1]);
    error++;
  }

  free(mem_content);
}/* end check_memory() */

/********************************************************************************
* Function define: init_shm_A7_to_M3()
*********************************************************************************/
void* init_shm_M3_to_A7(void)
{
  int fd_map;    /* file descriptor for map */
  void *virt_addr;
  off_t target = 0x200FC000;	//0x200F8000;

  fd_map = open("/dev/mem", O_RDWR | O_SYNC);

  printf("fd_map: %d _SC_PAGE_SIZE: %ld\n", fd_map, sysconf(_SC_PAGE_SIZE));

  map_base = (unsigned int *)mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, fd_map, target & ~MAP_MASK);

  if(map_base == (void *) -1)
  {
    printf("mmap failed\n");
  }

  virt_addr = (char *)map_base + (target & MAP_MASK);

  return virt_addr;
}/* end init_shm_M3_to_A7() */
/* file end */