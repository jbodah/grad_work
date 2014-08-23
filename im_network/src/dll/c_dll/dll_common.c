// dll_common.c

/*************************************************/
/* This file contains functionality that is used
/* by both the client and server DLL's
/*************************************************/

#include <time.h>
#include "dll_common.h"

// Initializes timer to some timeout time
void initTimer( clock_t *timer ) {
  *timer = clock() + SEC_UNTIL_TIMEOUT * CLOCKS_PER_SEC ;
}

// Returns 1 if timeout has occurred, else returns 0
int hasTimeoutOccurred( clock_t timer ) {
  return ( clock() > timer ) ? 1 : 0 ;
}
