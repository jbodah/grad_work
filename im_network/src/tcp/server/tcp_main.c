// /tcp/server/tcp_main.c

/*********************************************/
// This file contains the top-level logic
// that the TCP layer uses to process events
/*********************************************/

#include "../../common.h"
#include "tcp_main.h"
#include "tcp_server.h"
#include <stdio.h> // for printf
#include <string.h> // for strcpy
#include <stdlib.h> // for malloc

// How to communicate with DLL layer: addEventToQueue( p_DLLQueue, someEvent )
//
// jbodah
void TCPMain( int *p_sock, event_queue *p_TCPQueue, event_queue *p_DLLQueue ) {
  event *currentEvent ;
  event *newEvent ;
  char   sendBuffer[TCP_BUFSIZE] ;
  char   receiveBuffer[TCP_BUFSIZE] ;
  
  while(1) {
    currentEvent = wait_for_event(p_TCPQueue) ;
    
    if( currentEvent->type == SEND_PACKET ) {
      if( GL_debug ) {
        fputs( "TCP SEND_PACKET: ", stderr ) ;
        fputs( ((packet *)currentEvent->data)->contents, stderr ) ;
        fputs( "\n", stderr ) ;
      }
      
      bufFlush( sendBuffer ) ;
      bufFlush( receiveBuffer );
      // sendBuffer not necessary, but will throw and error if something happens I believe
      memcpy( sendBuffer, ((packet *)currentEvent->data)->contents, TCP_BUFSIZE ) ;
      TCPSend( *p_sock, sendBuffer, TCP_BUFSIZE ) ;
    }
    
    if( currentEvent->type == RECEIVE_PACKET ) {  
      if( GL_debug ) {
        fputs( "TCP RECEIVE_PACKET: ", stderr ) ;
        fputs( ((packet *)currentEvent->data)->contents, stderr ) ;
        fputs( "\n", stderr ) ;
      }
      
      // Send event to DLL
      addEventToQueue( p_DLLQueue, currentEvent ) ;  
    }
  }
}
