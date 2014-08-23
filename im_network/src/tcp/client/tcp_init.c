// /tcp/client/tcp_init.c

/*********************************************/
// This file initializes the TCP layer
/*********************************************/

#include "../../common.h"
#include "tcp_init.h"
#include "tcp_main.h"
#include "tcp_client.h"
#include <stdio.h> //For testing
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

/*** PRIVATE PROTOTYPES ***/
void initReceiver( void *arguments ) ;

// Copies queues from arguments and passes them to the main function
// jbodah
void TCPInit( void *arguments ) {
  int         *p_sock     = ((TCPArgs *)arguments)->p_sock ;
  event_queue *p_TCPQueue = ((TCPArgs *)arguments)->p_TCPQueue ;
  event_queue *p_DLLQueue = ((TCPArgs *)arguments)->p_DLLQueue ;
  
  pthread_t receiverThread ;
  pthread_create( &receiverThread, NULL, (void *) &initReceiver, (void *) arguments ) ;

  TCPMain( p_sock, p_TCPQueue, p_DLLQueue ) ;
}

// Listen for traffic to receive and add to TCP queue
// Not the most efficient, but it centralizes all of the data
// jbodah
void initReceiver( void *arguments ) {
  int         *p_sock     = ((TCPArgs *)arguments)->p_sock ;
  event_queue *p_TCPQueue = ((TCPArgs *)arguments)->p_TCPQueue ;
  
  char    receiveBuffer[TCP_BUFSIZE] ;
  packet *newPacket ;
  event  *newEvent ;
  
  while(1) {
    TCPReceive( *p_sock, receiveBuffer, TCP_BUFSIZE ) ;
    newEvent = createEvent() ;
    packet *newPacket = (packet *)malloc(sizeof(packet)) ;

    // Setup message
    memcpy( newPacket->contents, receiveBuffer, TCP_BUFSIZE ) ;
      
    // Setup event
    newEvent->data = newPacket ;
    newEvent->type = RECEIVE_PACKET ;
    
    // Send event to TCP
    addEventToQueue( p_TCPQueue, newEvent ) ;  
  }
}
