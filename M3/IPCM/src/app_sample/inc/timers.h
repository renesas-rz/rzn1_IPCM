#ifdef __cplusplus
 extern "C" {
#endif


typedef enum {
  ONE_SHOT_TIMER,
  PERIODIC_TIMER,
} TimerType;

typedef enum {
  ACTIVE_TIMER,
  NON_ACTIVE_TIMER,
} TimerStatus;

typedef enum {
  TASK_TIMER_INCREMENT,
  START_TIMER,
  STOP_TIMER,
} Timer_Ctrl_ID;

typedef struct
{
  ID id;
  unsigned int timer_control;  // start-stop
  unsigned int timer_duration; // msec
  TimerType timer_type;
} Timers_ITC_msg;

typedef int (*TIMER_CB)(unsigned int);

typedef struct timers_table {
    TIMER_CB timer_cb;
} TIMERS_TBL;


typedef struct run_timers_info {
    unsigned int expiration_time;    // msec
    unsigned int timer_duration;     // msec
    TimerType timer_type;            // one-shot vs. periodic
    TimerStatus timer_status;
} RUN_TIMERS_INFO;

typedef struct _TIMERS_Runtime_info {
    ID  id;
    TIMER_CB timer_cb;
    TimerType timer_type;
} TIMERS_Runtime_info;


void timers_task(int extinf);
int timer_start(unsigned int msec, TimerType timer_type, unsigned int timer_id);
int timer_stop(unsigned int timer_id);


int aaa(unsigned int);
int bbb(unsigned int);



#ifdef __cplusplus
}
#endif
