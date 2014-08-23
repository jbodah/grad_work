// /app/client/app_main.c

/*********************************************/
// This file contains the top-level logic
// that App layer uses to process events
/*********************************************/

#include "../../common.h"
#include "app_main.h"
#include "../app_common.h"
#include <stdio.h>  // for printf, scanf
#include <stdlib.h> // for malloc
#include <string.h> // for strcpy

/*** PRIVATE PROTOTYPES ***/
void sendCommandFromUser( event_queue *p_queue ) ;
void handleMessage( message *p_message ) ;
void flushInput() ;

// How to communicate with DLL layer: addEventToQueue( p_DLLQueue, someEvent )
//
// jbodah
void AppMain( event_queue *p_DLLQueue, event_queue *p_AppQueue ) {
  event *currentEvent ;
  
  while(1) {
    sendCommandFromUser( p_DLLQueue ) ;
    currentEvent = wait_for_event(p_AppQueue) ;
    if( currentEvent->type == RECEIVE_MESSAGE ) {
      //if( GL_debug )
      printReceiveMessage( (message *)currentEvent->data ) ;
      handleMessage( (message *)currentEvent->data ) ;
    }
  }
}

// Prompt user for input and send to server
// jbodah
void sendCommandFromUser( event_queue *p_queue ) {
  message *newMessage = (message *)malloc(sizeof(message)) ;
  bufFlush( newMessage->contents ) ;
 
  printf( "\nType a command: " ) ;
  fgets( newMessage->contents, sizeof(newMessage->contents), stdin ) ;
  //replace '\n' with '\0'
  newMessage->contents[strcspn(newMessage->contents, "\n")] = '\0';
  
  sendMessage( p_queue, newMessage ) ;
}

/****** CASE-HANDLING OF MESSAGES *****/

// Parse message
// jbodah
void handleMessage( message *p_message ) {
  if(1) {
    if( GL_debug )
     printf( "client handles message here\n" ) ;
  }
}
