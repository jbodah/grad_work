// /dll/sliding_window.c

/*********************************************/
// Sliding window for sending ONLY
/*********************************************/

#include "sliding_window.h"
#include "timeout.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

// Malloc up space for window
// jbodah
slidingWindow *createWindow( int windowSize ) {
  slidingWindow *p_window = (slidingWindow *)malloc(sizeof(slidingWindow)) ;
  p_window->windowSize = MIN(windowSize, MAX_WINDOW_SIZE) ;
  return p_window ;
}

// Initialize the window for the given seqNum
// Accept the first few seqNum's
void initWindow( slidingWindow *p_window, int seqNum ) {
  int i ;
  for( i = 0 ; i < p_window->windowSize ; i++ )
    addToWindow( p_window, seqNum++ ) ;
  p_window->maxSeqNum = seqNum - 1 ;
}

// Attempt to slide window by one seqNum
// Return 1 if okay, 0 if error
// jbodah
int incrementWindow( slidingWindow *p_window ) {
  if( addToWindow( p_window, p_window->maxSeqNum + 1 ) == 1 ) {
    p_window->maxSeqNum++ ;
    return 1 ;
  }
  return 0 ;
}

// Checks to see if there is a free spot in the window
// If so, create a timer for that spot and return 1
// Else return 0
// jbodah
int addToWindow( slidingWindow *p_window, int seqNum ) {
  int i ;
  for( i = 0 ; i < p_window->windowSize ; i++ ) {
    // There is a free spot in window
    if( p_window->timers[i] == NULL ) {
      if( GL_debug )
        printf( "- addToWindow, seqNum = '%c' %d\n", (char)seqNum, seqNum ) ;
      p_window->timers[i] = createTimer( seqNum ) ;
      return 1 ;
    }
  }
  printf( "- addToWindow FAILED, seqNum = '%c' %d\n", (char)seqNum, seqNum ) ;
  return 0 ;
}

// Returns window slot with seqNum or -1 
// jbodah
int inWindow( slidingWindow *p_window, int seqNum ) {
  int i ;
  for( i = 0 ; i < p_window->windowSize ; i++ ) {
    if( p_window->timers[i] != NULL && p_window->timers[i]->seqNum == seqNum )
      return i ;
  }
  return -1 ;
}

// Tries to remove seqNum from slidingWindow
// Returns the removed timer or null
// jbodah
timer *removeFromWindow( slidingWindow *p_window, int seqNum ) {
  timer *p_timer ;
  int    position ;
  
  if(( position = inWindow( p_window, seqNum )) != -1 ) {
    p_timer = p_window->timers[position] ;
    p_window->timers[position] = NULL ;
    if( GL_debug ) 
      printf( "- removeFromWindow, seqNum = '%c' %d\n", (char)seqNum, seqNum ) ;
    return p_timer ;
  }
  return NULL ;
}

// Returns 1 on success, 0 on failure
// jbodah
int startAndWatchTimer( event_queue *p_DLLQueue, slidingWindow *p_window, packet *p_packet ) {
  int position ;
  
  if(( position = inWindow( p_window, getSeqNum(p_packet) )) != -1 ) {
    timeargs *args  = (timeargs *)malloc(sizeof(timeargs)) ;
    args->p_queue   = p_DLLQueue ;
    args->p_timer   = p_window->timers[position] ;
    args->p_packet  = p_packet ;
    pthread_t timerThread ;
    pthread_create( &timerThread, NULL, (void *) &startTimer, (void *)args ) ;
    return 1 ;
  }
  return 0 ;
}
