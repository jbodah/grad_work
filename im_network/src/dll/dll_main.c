// /dll/dll_main.c

/*********************************************/
// This file contains the top-level logic
// that the DLL uses to process events
/*********************************************/

#include "../common.h"
#include "dll_main.h"
#include "sliding_window.h"
#include <stdio.h> //For testing
#include <string.h> // for strcpy
#include <stdlib.h> // for malloc

/*** STATIC VARIABLES ***/
static int ST_dll_ready = 0 ;
static int ST_message_queue_count = 0 ;

/*** PRIVATE PROTOTYPES ***/
void incSeqNum( char *p_seqNum ) ;
void sendPacket( event_queue *p_queue, packet *newPacket ) ;
void sendMessageToApp( event_queue *p_queue, message *newMessage ) ;
void breakMessageAndQueuePackets( event_queue *p_DLLQueue, message *p_message, char *p_seqNum ) ;
void randomlyInjectErrors( packet *p_packet, int error_rate ) ;
void setReady( int status ) ;
int  reasonableSeqNum( char rcvNum, char currNum ) ;

// How to communicate with App layer: addEventToQueue( p_AppQueue, someEvent )
// How to communicate with TCP layer: addEventToQueue( p_TCPQueue, someEvent )
//
// jbodah
void DLLMain( event_queue *p_TCPQueue, event_queue *p_DLLQueue, event_queue *p_AppQueue, int *p_isServer ) {
  event          *currentEvent ;
  packet         *receivedPacket ;
  packet         *newPacket ;
  message        *newMessage ; 
  char            seqNum = 'a' - 1 ;
  slidingWindow  *p_window ;
  char            expectedSeqNum = 'a';
  packet         *packetBuffer[9] ;     // Note that our implementation should never exceed three packets per message
  int             bufferPosition = 0;
  int             i ;
  size_t          currentSize ;
  
  setReady(1) ;
  
  // The original implementation of this was incorrect!
  // Need to have BOTH sides send with window size 4 and receive with window size 1
  //if( *p_isServer )
    //p_window = createWindow(1) ;
  //else
  p_window = createWindow(4) ;
  
  // we want the first seqNum to be 'a'
  initWindow(p_window, seqNum + 1) ;
  
  while(1) {
    // If the number queued messages is low, accept messages from App layer
    if( ST_message_queue_count < 4 )
      setReady(1) ;
      
    currentEvent = wait_for_event(p_DLLQueue) ;
    
    if( currentEvent->type == RECEIVE_PACKET ) {
      receivedPacket = (packet *)currentEvent->data ;  

      if( GL_debug ) {
        printf( "DLL RECEIVE_PACKET: \n" ) ;
        printPacketContents( receivedPacket ) ;
      }
      
      // if CRC check doesn't pass, drop packet
      if( !checkCRC( receivedPacket )) {
        if( GL_debug ) {
          printf( "- CRC check FAILED, packet dropped\n") ;
          printf( "DLL DROPPED_PACKET: \n" ) ;
          printPacketContents( receivedPacket ) ;
        }
        continue ; // Let the packet timeout
      }
      
      // If Ack, remove packet from window and let App send more
      if( isAck( receivedPacket)) {
        if( GL_debug )        
          printf( "- DLL processing ack\n" ) ; 
        
        // If this an Ack to something we care about
        if( removeFromWindow( p_window, getSeqNum(receivedPacket)) != NULL ) {
          decQueueCount() ;
          if( incrementWindow( p_window ) == 0 )
            printf( "!ERROR: Unexpected full window, dll_main.c" ) ;
        }
      }
      
      if( isNormal( receivedPacket )) {  
        if( GL_debug )
          printf( "- DLL process normal packet\n" ) ;
        
        // If expected seqNum, rebuild message and pass to app
        if( getSeqNum(receivedPacket) == expectedSeqNum ) {
          incSeqNum(&expectedSeqNum) ;
          if( GL_debug )
            printf( "- expected seqNum increased to '%c' %d\n", expectedSeqNum, (int)expectedSeqNum ) ;
          
          // Buffer packets
          packetBuffer[bufferPosition] = receivedPacket ;
          bufferPosition++ ;
            
          // Only try to reassemble if we have the end of the message
          if( isEndOfMessage( receivedPacket )) {
            // Reassmble message and send to App          
            newMessage = (message *)malloc(sizeof(message)) ;
            currentSize = 0 ;
            for( i = 0 ; i < bufferPosition ; i++ ) {
              memcpy( &newMessage->contents[currentSize], getPayload(packetBuffer[i]), getPayloadSize(packetBuffer[i])) ;
              currentSize += getPayloadSize(packetBuffer[i]) ;
            }
            bufferPosition = 0 ;
            sendMessageToApp( p_AppQueue, newMessage ) ;
          }
        }
        
        // Drop packet if seqNum is far from the current one
        if( !reasonableSeqNum( getSeqNum(receivedPacket), seqNum ) ) {
          if( GL_debug ) {        
            printf( "DLL DROPPED_PACKET: \n" ) ;
            printPacketContents( receivedPacket ) ;
          }
          continue ;
        }
        
        // Send back an ACK
        newPacket = createPacket( getSeqNum( receivedPacket ), 'b' ) ;
                 
        addCRC(newPacket) ;
        if( GL_debug )
          printf( "- CRC added = '%c' %d\n", getCRC(newPacket), (int)getCRC(newPacket) ) ;
        randomlyInjectErrors(newPacket, GL_error_rate);
        if( GL_debug ) {
          printf( "- DLL forwarding ack to TCP: \nDLL SEND_PACKET:\n" ) ;
          printPacketContents(newPacket) ;
        }
        sendPacket( p_TCPQueue, newPacket ) ;        
      }
    }
    
    // Note that DLL essentially does double duty with messages and packets
    if( currentEvent->type == SEND_MESSAGE ) { 
      breakMessageAndQueuePackets( p_DLLQueue, (message *)currentEvent->data, &seqNum ) ;
    }
    
    // We know that this came from a message which was broken up into packets
    if( currentEvent->type == SEND_PACKET ) {
      newPacket = (packet *)currentEvent->data ;        
      
      // If in window
      if( inWindow( p_window, getSeqNum(newPacket) ) != -1 ) {
        if( GL_debug )
          printf( "- Timer started, seqNum = '%c' %d\n", getSeqNum(newPacket), (int)getSeqNum(newPacket) ) ;
        
        addCRC((packet *)currentEvent->data) ;
        if( GL_debug ) 
          printf( "- CRC added = '%c' %d\n", getCRC(newPacket), (int)getCRC(newPacket) ) ;
        randomlyInjectErrors(newPacket, GL_error_rate) ;
        startAndWatchTimer( p_DLLQueue, p_window, newPacket ) ;
        sendPacket( p_TCPQueue, newPacket ) ;
        
        if( GL_debug ) {
          printf( "- DLL forwarding packet to TCP \nDLL SEND_PACKET:\n") ;
          printPacketContents( newPacket );
        }
      }
      else {
        // Send to the back of the queue, maybe it will be ready to send later
        sendPacket( p_TCPQueue, newPacket ) ;
      }
    }
    
    if( currentEvent->type == TIMEOUT ) {
      newPacket = (packet *)currentEvent->data ;
      // If in window
      if( inWindow( p_window, getSeqNum(newPacket) ) != -1 ) {
        if( GL_debug ) {
          printf( "***A timeout has occurred, seqNum = '%c' %d ***\n", getSeqNum(newPacket), (int)getSeqNum(newPacket) ) ;
          fputs( "- DLL requeing packet in own queue:\n", stderr ) ;
        }
        sendPacket(p_DLLQueue, newPacket ) ;
      }
      
      // Ignore it, we already got the packet
      else
        ;
    }
  }
}

// Split message into packets and queue each packet
// jbodah
void breakMessageAndQueuePackets( event_queue *p_DLLQueue, message *p_message, char *p_seqNum ) {
  char    messageBuffer[APP_BUFSIZE] ;
  packet *newPacket ;
  int     i = 0 ;
  char    tmpChar ;
    
  bufFlush( messageBuffer ) ;
  
  strncpy( messageBuffer, p_message->contents, sizeof(messageBuffer) ) ;
  
  while( i < strlen(messageBuffer) ) {
    if( GL_debug )
      fputs( "- DLL splitting message\n", stderr ) ;
      
    incQueueCount() ;
    incSeqNum(p_seqNum) ;    
    
    newPacket = createNormalPacket(*p_seqNum) ;
    
    // Max content length, take as much as we can
    // and leave the rest for other iterations
    if( strlen(&messageBuffer[i]) > 122 ) {
      tmpChar = (char)122 ;
      memcpy( &newPacket->contents[4], &tmpChar, sizeof(char) ) ;
      memcpy( &newPacket->contents[5], &messageBuffer[i], 122 ) ;
      i += 122 ;
    }
    
    // Less than max content length, take it all
    else { 
      tmpChar = (char)strlen(&messageBuffer[i]) ;
      memcpy( &newPacket->contents[4], (void *)&tmpChar, sizeof(char) ) ;
      memcpy( &newPacket->contents[5], (void *)&messageBuffer[i], strlen(&messageBuffer[i]) ) ;
      i += strlen(&messageBuffer[i]) ;
      newPacket->contents[3] = 'c' ; // This is the last packet of the message
    }
    
    if( GL_debug )
      printf( "- DLL adding split packet back into own queue: %s\n", newPacket->contents ) ;
    
    // Pass event to own (DLL's) queue
    sendPacket( p_DLLQueue, newPacket ) ;
  }
}

// Create an event for the packet and send the event to App
// jbodah
void sendMessageToApp( event_queue *p_queue, message *newMessage ) {
  if( GL_debug )
    printf( "- DLL forwarding message to App: %s\n", newMessage->contents ) ;
  event *newEvent = createEvent() ;
  newEvent->data = newMessage ;
  newEvent->type = RECEIVE_MESSAGE ;
  addEventToQueue( p_queue, newEvent ) ;
}

// Create an event for the packet and send the event to TCP or DLL
// jbodah
void sendPacket( event_queue *p_queue, packet *newPacket ) {
  event *newEvent = createEvent() ;
  newEvent->data = newPacket ;
  newEvent->type = SEND_PACKET ; 
  addEventToQueue( p_queue, newEvent ) ;
}

// Increment sequence number
// Keep it something that is easy to read and debug
// jbodah
void incSeqNum( char *p_seqNum ) {
  if( ++(*p_seqNum) > 'z' )
    *p_seqNum = 'a' ;
}

// Inject errors based on error rate
// jbodah
void randomlyInjectErrors( packet *p_packet, int error_rate ) {
  if(((rand() % 100) + 1) <= error_rate ) {
    p_packet->contents[TCP_BUFSIZE-1] = p_packet->contents[TCP_BUFSIZE-1] - 1 ;
  }
}

// Tells App whether or not DLL is accepting traffic
// jbodah
void wait_to_send() {
  while( ST_dll_ready != 1 ) ;
  ST_dll_ready = 0 ;
}

// Sets whether or not DLL is accepting traffic
// jbodah
void setReady( int status ) {
  ST_dll_ready = status ;
}

// Increases window count
// jbodah
void incQueueCount() {
  ST_message_queue_count++ ;
  if( ST_message_queue_count >= MAX_WINDOW_SIZE )
    setReady(0) ;
  if( GL_debug )
    printf( "- message_queue_count increased to %d\n", ST_message_queue_count ) ; 
}

// Decreases window count
// jbodah
void decQueueCount() {
  ST_message_queue_count-- ;
  if( ST_message_queue_count < MAX_WINDOW_SIZE )
    setReady(1) ;
  if( GL_debug )
    printf( "- message_queue_count decreased to %d\n", ST_message_queue_count ) ; 
}

// Return 1 if within 8 sequence numbers
// Else return false
int reasonableSeqNum( char rcvNum, char currNum ) {
  // downshift to prevent overflow
  rcvNum = rcvNum - 'a' ;
  currNum = currNum - 'a' ;
  
  if((currNum + 26 - rcvNum) < 9 ) return 1;
  else if( currNum - rcvNum < 9 ) return 1;
  else return 0 ;
}

