// client.c

/********************************************/
// This file holds the main driver for the
// client
/********************************************/

#include "tcp/client/tcp_client.h"
#include "tcp/client/tcp_init.h"
#include "dll/dll_init.h"
#include "app/client/app_init.h"
#include "common.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Main driver for client
// jbodah
int main( int argc, char *argv[] ) {
  if( argc != 4 )
		DieWithErr( "Usage: ./PROG_NAME SERV_ADDR ERROR_RATE DEBUG_MODE" ) ;
    
  if( (atoi(argv[2]) > 100) || (atoi(argv[2]) < 0) )
    DieWithErr( "ERROR_RATE must be between 0 and 100" ) ;
  else
    GL_error_rate = atoi(argv[2]) ;
    
  if( atoi(argv[3]) != 0 && atoi(argv[3]) != 1 )
    DieWithErr( "DEBUG_MODE must be 0 or 1" ) ;
  else 
    GL_debug = atoi(argv[3]) ;
      
	int sock = establishConnection( argv[1] ) ; 
  
  initClient( sock ) ;

	return 0 ;
}

initClient( int sock ) {
  int *p_sock = malloc(sizeof(int)) ;
  *p_sock     = sock ;

  event_queue   *p_DLLQueue = malloc(sizeof(event_queue)) ;
  event_queue   *p_TCPQueue = malloc(sizeof(event_queue)) ;
  event_queue   *p_AppQueue = malloc(sizeof(event_queue)) ;
  
  TCPArgs       *p_TCPargs  = malloc(sizeof(TCPArgs)) ;
  DLLArgs       *p_DLLargs  = malloc(sizeof(DLLArgs)) ;
  AppArgs       *p_Appargs  = malloc(sizeof(AppArgs)) ;
  
  int           *p_isServer = malloc(sizeof(int)) ;
  
  *p_isServer = 0 ;
  
  // Init queues
  initQueue( p_TCPQueue ) ;
  initQueue( p_DLLQueue ) ; 
  initQueue( p_AppQueue ) ;
  
  // Copy args into structs
  p_TCPargs->p_sock = p_sock ;
  p_TCPargs->p_TCPQueue = p_TCPQueue ;
  p_TCPargs->p_DLLQueue = p_DLLQueue ;
  
  p_DLLargs->p_TCPQueue = p_TCPQueue ;
  p_DLLargs->p_DLLQueue = p_DLLQueue ;
  p_DLLargs->p_AppQueue = p_AppQueue ;
  p_DLLargs->p_isServer = p_isServer ;
  
  p_Appargs->p_DLLQueue = p_DLLQueue ;
  p_Appargs->p_AppQueue = p_AppQueue ;
  
  // Make new thread for DLL
  pthread_t newDLLThread ;
  pthread_create( &newDLLThread, NULL, (void *) &DLLInit, (void *) p_DLLargs ) ;
  
  // Make new thread for App
  pthread_t newAppThread ;
  pthread_create( &newAppThread, NULL, (void *) &AppInit, (void *) p_Appargs ) ;
  
  // Use this thread for TCP
  TCPInit((void *) p_TCPargs ) ;
}
