// /app/server/app_init.c

/*********************************************/
// This file initializes the App layer
/*********************************************/

#include "../../common.h"
#include "app_init.h"
#include "app_main.h"

// Copies queues from arguments and passes them to the main function
// jbodah
void AppInit( void *arguments ) {
  event_queue *p_DLLQueue = ((AppArgs *)arguments)->p_DLLQueue ;
  event_queue *p_AppQueue = ((AppArgs *)arguments)->p_AppQueue ;

  AppMain( p_DLLQueue, p_AppQueue ) ;
}
