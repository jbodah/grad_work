// /dll/timer.h

/*********************************************/
// This file contains the code for timers
/*********************************************/

#include <time.h>
#include "../common.h"

#define SEC_UNTIL_TIMEOUT  5

#ifndef _TIMER
#define _TIMER
typedef struct timer {
  int       seqNum ;
  clock_t   signalTime ;
} timer ;
#endif

#ifndef _TIMEARGS
#define _TIMEARGS
typedef struct timeargs {
  event_queue *p_queue ;
  timer       *p_timer ;
  packet      *p_packet ;
} timeargs ;
#endif

timer  *createTimer( int seqNum ) ;
void    startTimer(void *args) ;
