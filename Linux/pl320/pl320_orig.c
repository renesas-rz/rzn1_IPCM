#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <asm/unistd.h>
#include <stdlib.h>
#include<pthread.h>

#include "pl320.h"
#include "shm.h"


unsigned int tx_buf[IPCM_DATA_REG_NUM];
int fd_2;                                     /* file descriptor */

int in_thread_cnt = 0;
void* M3_to_A7_task(void *arg)
{
  UNUSED(arg);
  int res;
  void *virt_addr;

  virt_addr = init_shm_M3_to_A7();
  unsigned int rx_buf[IPCM_DATA_REG_NUM];

  while(1)
  {

    res = read(fd_2, &rx_buf, IPCM_DATA_REG_NUM * sizeof(unsigned int));

    check_memory(rx_buf[1], rx_buf[2], rx_buf[3], virt_addr);

    in_thread_cnt++;
  }

  return NULL;
}


int show_M3_to_A7_content = 0;
int main(int argc, char *argv[])
{
  UNUSED(argc);

  int main_fd;
  int res;                                    /* result */
  void *virt_addr;
  int sleep_time_microsec = atoi(argv[1]);
  int shm_size_bytes = atoi(argv[2]);
  show_M3_to_A7_content = atoi(argv[3]);

  if((shm_size_bytes <= 0) || ((shm_size_bytes%4) != 0))
  {
    printf("memory size should be positive number divisible by 4\n");
    return -1;
  }

  main_fd = open(MBOX_DEVICE_MASTER_NAME, O_WRONLY);

  if (0 > main_fd)
  {
    printf("could not open %s\n", MBOX_DEVICE_MASTER_NAME);
    return -1;
  }

  /* create new mailbox device */
  res = ioctl(main_fd, MBOX_IOCTL_CREATE, 2);
  printf("Result 01 %d\n", res);


  fd_2 = open("/dev/mbox_2", O_RDWR);

  if (0 > fd_2)
  {
    printf("could not open %s", "/dev/mbox_2");
    return -1;
  }

  close(main_fd);


  virt_addr = init_shm_A7_to_M3(SHM_ADDRESS, SHM_SIZE/2);

  int cycle = 0;

  int ipcm_tx_cnt = 1;
  int err;

  pthread_t tid;
  err = pthread_create(&tid, NULL, &M3_to_A7_task, NULL);

  while(1)
  {

    // if sleep time is zero, let's not waste time for the call
    if (sleep_time_microsec != 0)
    {
      usleep(sleep_time_microsec);
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

    res = write(fd_2, tx_buf, IPCM_DATA_REG_NUM * sizeof(unsigned int));
    ipcm_tx_cnt++;

    if (res != IPCM_DATA_REG_NUM * sizeof(unsigned int))
    {
      printf("write err %d", res);
      perror("Error:\n");
    }

  }
}
