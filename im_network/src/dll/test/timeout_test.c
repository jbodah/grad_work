#include <stdio.h>
#include <time.h>
#include "../dll_common.h"

typedef struct frame {
  char      payload[100] ;
  clock_t   timer ;
} frame ;

int main() {

  frame a ;
  frame b ;
  
  initTimer( &a.timer ) ;
  while( !hasTimeoutOccurred( a.timer )) ;
  printf( "\nTimer A has timed out!\n" ) ;
  
  initTimer( &b.timer ) ;
  while( !hasTimeoutOccurred( b.timer )) ;
  printf( "Timer B has timed out!\n\n" ) ;

}

