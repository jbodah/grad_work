// /dll/sliding_window.h

/*********************************************/
// Sliding window for sending ONLY
/*********************************************/

#include "timeout.h"

#define MAX_WINDOW_SIZE     4

#ifndef _SLIDE
#define _SLIDE
typedef struct slidingWindow {
  timer *timers[MAX_WINDOW_SIZE] ;  // This is a hack, always allocate 4 timer slots even if we only use 1
  int    maxSeqNum ;
  int    windowSize ;
} slidingWindow ;
#endif

slidingWindow  *createWindow( int windowSize ) ;
int             inWindow( slidingWindow *p_window, int seqNum ) ;
timer          *removeFromWindow( slidingWindow *p_window, int seqNum ) ;
void            initWindow( slidingWindow *p_window, int seqNum ) ;
int             incrementWindow( slidingWindow *p_window ) ;
int             startAndWatchTimer( event_queue *p_DLLQueue, slidingWindow *p_window, packet *p_packet ) ;
