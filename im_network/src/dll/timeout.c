// /dll/timer.c

/*********************************************/
// This file contains the code for timers
/*********************************************/

#include <stdio.h>
#include <time.h>
#include "timeout.h"
#include "../common.h"
#include <stdlib.h>

/*** PRIVATE PROTOTYPES ***/
void initTimer( clock_t *timer ) ;
int  hasTimeoutOccurred( clock_t timer ) ;

// Create timer and init with seqNum
// jbodah
timer *createTimer( int seqNum ) {
  timer *newTimer = (timer *)malloc(sizeof(timer)) ;
  newTimer->seqNum = seqNum ;
  return newTimer ;
}

// This should probably be split into sliding window
// jbodah
void startTimer(void *args)  {
  event_queue *p_queue  = ((timeargs*)args)->p_queue;
  timer       *p_timer  = ((timeargs*)args)->p_timer;
  packet      *p_packet = ((timeargs*)args)->p_packet;

  initTimer( &p_timer->signalTime ) ;
  
  while( !hasTimeoutOccurred(p_timer->signalTime) ) ;
  
  event *timeout = createEvent() ;
  
  timeout->type = TIMEOUT ;
  timeout->data = (void *)p_packet ;
  
  addEventToQueue( p_queue, timeout ) ;
}

// Initializes timer to some timeout time
void initTimer( clock_t *timer ) {
  *timer = clock() + SEC_UNTIL_TIMEOUT * CLOCKS_PER_SEC ;
}

// Returns 1 if timeout has occurred, else returns 0
int hasTimeoutOccurred( clock_t timer ) {
  return ( clock() > timer ) ? 1 : 0 ;
}
