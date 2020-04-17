
#ifndef _ASB_LOW_LEVEL_INIT_H
#define _ASB_LOW_LEVEL_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXTERN
#define EXTERN extern
#endif

int ASB_HW_Power_init(void);
void ASB_HW_init(void);

int RZN1L_SPI_PWRCTRL_init(void);

int ASB_SB_IRQs_init(void);

void ASB_Rotary_switch_init(void);
int ASB_Rotary_switch_read(void);
EXTERN int ASB_ID;
EXTERN int Number_of_Tasks;
#define ASB_SW_VERSION "1.1.8" // Software version number
/*
  Software changes impacting the version number:
*/


#define ASB_ME_VERSION "1.0.0" // Mechatronics version number
/*
  Electronics or Mechanics changes of the system where ASB is installed:
*/

EXTERN unsigned char ASB_mac_id[6];

typedef struct task_name_lookup {
    char name[30];
}Task_Names;

#ifdef __cplusplus
}
#endif

#endif
