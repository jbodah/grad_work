// /app/app_common.c

#include "../common.h"
#include "../dll/dll_main.h"
#include <stdio.h>

void printReceiveMessage( message *p_message ) {
  fputs( "APP RECEIVE_MESSAGE: ", stderr ) ;
  fputs( p_message->contents, stderr ) ;
  fputs( "\n", stderr ) ;
}

void printSendMessage( message *p_message ) {
  fputs( "APP SEND_MESSAGE: ", stderr ) ;
  fputs( p_message->contents, stderr ) ;
  fputs( "\n", stderr ) ;
}

// Create new event, send when DLL is ready
// jbodah
void sendMessage( event_queue *p_queue, message *newMessage ) {
  event *newEvent = createEvent() ;
  newEvent->data = newMessage ;
  newEvent->type = SEND_MESSAGE ;
  if( GL_debug )
    printSendMessage( newMessage ) ;
  wait_to_send() ; // Wait for DLL to be ready
  addEventToQueue( p_queue, newEvent ) ;
}
