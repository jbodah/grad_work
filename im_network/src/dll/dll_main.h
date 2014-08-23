// /dll/dll_main.h

/*********************************************/
// This file contains the top-level logic
// that DLL uses to process events
/*********************************************/

void DLLMain( event_queue *p_TCPQueue, event_queue *p_DLLQueue, event_queue *p_AppQueue, int *p_isServer ) ;
void wait_to_send()  ;
void incQueueCount() ;
void decQueueCount() ;
