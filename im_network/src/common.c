// common.c

/********************************************/
// This file defines common functionality
// used throughout the entire application
/********************************************/

#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*** PRIVATE PROTOTYPES ***/
char calculateCRC(packet *newPacket) ;

// Kills process and displays error
// jbodah
void DieWithErr( char *msg ) {
  fputs( msg, stderr ) ;
  fputc( '\n', stderr ) ;
  exit( 1 ) ;
}

// Flushes a buffer to all 0's
// jbodah
void bufFlush( char *buffer ) {
	memset( buffer, 0, sizeof( buffer )) ;
}

// Create and initialize a packet
// jbodah
packet *createPacket(char seqNum, char frameKind) {
  packet *newPacket = (packet *)malloc(sizeof(packet)) ;
  bufFlush( newPacket->contents ) ;
  memcpy( &newPacket->contents[0], "AA", 2*sizeof(char)) ;
  memcpy( &newPacket->contents[2], &seqNum, sizeof(char)) ;
  memcpy( &newPacket->contents[3], &frameKind, sizeof(char)) ;
  return newPacket ;
}

// Return 1 if the packet's sync bytes are correct, else 0
// jbodah
int checkSyncBytes(packet *newPacket) {
  return newPacket->contents[0] == 'A' && newPacket->contents[1] == 'A' ;
}

// Return sequence number of packet
// jbodah
int getSeqNum(packet *newPacket) {
  return (int)newPacket->contents[2] ;
}

// Return frame kind character
// 'a' = normal
// 'b' = ack
// jbodah
char getFrameKind(packet *newPacket) {
  return newPacket->contents[3] ;
}

// Return size in bytes of packet payload
// jbodah
int getPayloadSize(packet *newPacket) {
  return (int)newPacket->contents[4] ;
}

// Return CRC byte
// jbodah
char getCRC(packet *newPacket) {
  return newPacket->contents[TCP_BUFSIZE-1] ;
}

// Add CRC to end of packet
// jbodah
void addCRC(packet *newPacket) {
  char CRC = calculateCRC(newPacket) ;
  memcpy( &newPacket->contents[TCP_BUFSIZE-1], &CRC, sizeof(char)) ;
}

// Check CRC and return 1 if it matches, else 0
// jbodah
int checkCRC(packet *newPacket) {
  char CRC = calculateCRC(newPacket) ;
  return CRC == getCRC(newPacket) ;
}

// Calculate CRC (by XOR'ing bytes) and return it
// jbodah
char calculateCRC(packet *newPacket) {
  char CRC = '\0' ;
  int i ;
  for( i = 0 ; i < sizeof(newPacket->contents) - 1 ; i++ )
    CRC = CRC ^ newPacket->contents[i] ;
  return CRC ;
}

// Return reference to payload. Returns null if no payload
// jbodah
char *getPayload(packet *newPacket) {
  if( getPayloadSize( newPacket ) == 0 )
    return NULL ;
  return &newPacket->contents[5] ;
}

// jbodah
packet *createNormalPacket(char seqNum) {
  return createPacket(seqNum, 'a') ;
}

// jbodah
packet *createAckPacket(char seqNum) {
  return createPacket(seqNum, 'b') ;
}

// jbodah
int isNormal( packet *newPacket ) {
  return (getFrameKind( newPacket ) == 'a' || getFrameKind( newPacket ) == 'c');
}

// jbodah
int isEndOfMessage( packet *newPacket ) {
  return getFrameKind( newPacket ) == 'c';
}

//jbodah
int isAck( packet *newPacket ) {
  return getFrameKind( newPacket ) == 'b' ;
}

// jbodah
void getVerboseFrameKind(packet *newPacket, char *dstString) {
  if( getFrameKind(newPacket) == 'a' )
    strcpy( dstString, "normal" ) ;
  else if( getFrameKind(newPacket) == 'b' )
    strcpy( dstString, "ack" ) ;
  else if( getFrameKind(newPacket) == 'c' )
    strcpy( dstString, "endOfMessage" ) ;
  else
    strcpy( dstString, "ERROR: common.c::getVerboseFrameKind" ) ;
}

// jbodah
void printPacketContents( packet *newPacket ) {
  char dstString[30] ;
  bufFlush( dstString ) ;
  
  getVerboseFrameKind(newPacket, dstString) ;
  
  printf( "\tseqNum\t\t'%c' %d \n\tframeKind\t%s \n\tpayload\t\t%s \n\tCRC\t\t'%c' %d\n",
            getSeqNum(newPacket), (int)getSeqNum(newPacket),
            dstString,
            getPayload(newPacket),
            getCRC(newPacket), (int)getCRC(newPacket)
  ) ;
}

/*** Event queue functions ***/
// Appends an event to the back of the queue
// jbodah
void addEventToQueue( event_queue *queue, event *p_event ) {
  if( queue->head == NULL )        // Empty queue
    queue->head = p_event ;        // Set new event to head
  else
    queue->tail->next = p_event ;  // Append new event to tail event
  queue->tail = p_event ;          // Set new event to tail
}

// Initialize a queue
// jbodah
void initQueue( event_queue *queue ) {
  queue->head = NULL ;
  queue->tail = NULL ;
}

// Removes event from queue and returns pointer to removed event
// jbodah
event *removeEventFromQueue( event_queue *queue ) {
  event *p_event ;
  
  if( queue->head == NULL )
    return NULL ;
    
  if( queue->head == queue->tail ) {
    p_event = queue->head ;
    queue->head = queue->tail = NULL ;
    return p_event ;
  }

  p_event       = queue->head ;
  queue->head   = p_event->next ;
  return p_event ;
}

// Mallocs up space for and inits a new event
// jbodah
event *createEvent() {
  event *p_event  = (event *)malloc(sizeof(event)) ;
  p_event->next   = NULL ;
  p_event->data   = NULL ;
  return p_event ;
}

// Frees up space from event
// jbodah
void destroyEvent( event *p_event ) {
  free( p_event ) ;
}

/*** Event handler functions ***/
// Block until we get something in the queue
// Remove event from queue and return it
// jbodah
event *wait_for_event( event_queue *p_queue ) {
  while( p_queue->head == NULL ) ;
  return removeEventFromQueue( p_queue ) ;
}
