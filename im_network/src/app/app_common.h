// /app/app_common.h

#include "../common.h"

void printReceiveMessage( message *p_message ) ;
void printSendMessage( message *p_message ) ;
void sendMessage( event_queue *p_queue, message *newMessage ) ;
