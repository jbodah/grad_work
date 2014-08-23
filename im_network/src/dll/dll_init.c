// /dll/dll_init.c

/*********************************************/
// This file initializes the DLL
/*********************************************/

#include "../common.h"
#include "dll_init.h"
#include "dll_main.h"
#include <stdio.h> //For testing

// Copies queues from arguments and passes them to the main function
// jbodah
void DLLInit( void *arguments ) {
  // Setup queues
  event_queue *p_TCPQueue = ((DLLArgs *)arguments)->p_TCPQueue ;
  event_queue *p_DLLQueue = ((DLLArgs *)arguments)->p_DLLQueue ;
  event_queue *p_AppQueue = ((DLLArgs *)arguments)->p_AppQueue ;
  int         *p_isServer = ((DLLArgs *)arguments)->p_isServer ;
  
  DLLMain( p_TCPQueue, p_DLLQueue, p_AppQueue, p_isServer ) ;
}
