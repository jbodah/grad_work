// common.h

/********************************************/
// This file defines common functionality
// used throughout the entire application
/********************************************/

#define SERVER_PORT_STRING    "4000"
#define SERVER_PORT           4000
#define TCP_BUFSIZE           128
#define APP_BUFSIZE           256
#define MAX(a,b)              a > b ? a : b
#define MIN(a,b)              a < b ? a : b

/*** GLOBAL VARIABLES ***/
int GL_debug ;
int GL_error_rate ;

#ifndef _PACKET
#define _PACKET
typedef struct packet {
  char contents[TCP_BUFSIZE] ;
} packet ;
#endif

#ifndef _MESSAGE
#define _MESSAGE
typedef struct message {
  char contents[APP_BUFSIZE] ;
} message ;
#endif

#ifndef _EVENT_TYPE
#define _EVENT_TYPE
typedef enum event_type {
  TIMEOUT,
  SEND_PACKET,
  RECEIVE_PACKET,
  SEND_MESSAGE,
  RECEIVE_MESSAGE
} event_type ;
#endif

#ifndef _EVENT
#define _EVENT
typedef struct event {
  event_type      type ;
  void           *data ;
  struct event   *next ;
} event ;
#endif

#ifndef _EVENT_QUEUE
#define _EVENT_QUEUE
typedef struct event_queue {
  event        *head ;
  event        *tail ;
} event_queue ;
#endif

#ifndef _ARGS
#define _ARGS
// Contains references to the arguments needed when
// creating a new thread for new connection
typedef struct TCPArgs {
  int         *p_sock ;
  event_queue *p_TCPQueue ;
  event_queue *p_DLLQueue ;
} TCPArgs ;

typedef struct DLLArgs {
  event_queue *p_TCPQueue ;
  event_queue *p_DLLQueue ;
  event_queue *p_AppQueue ;
  int         *p_isServer ;
} DLLArgs ;

typedef struct AppArgs {
  event_queue *p_DLLQueue ;
  event_queue *p_AppQueue ;
} AppArgs ;
#endif

// Util functions
void DieWithErr( char *msg ) ;
void bufFlush( char *buffer ) ;

// Primitive event queue functionality
void    addEventToQueue( event_queue *queue, event *p_event ) ;
void    initQueue( event_queue *queue ) ;
event  *removeEventFromQueue( event_queue *queue ) ;
event  *createEvent() ;
void    destroyEvent( event *p_event ) ;

// Event handler
event *wait_for_event( event_queue *p_queue ) ;

// Packets
packet *createPacket(char seqNum, char frameKind) ;
int     checkSyncBytes(packet *newPacket) ;
int     getSeqNum(packet *newPacket) ;
char    getFrameKind(packet *newPacket) ;
int     getPayloadSize(packet *newPacket) ;
char    getCRC(packet *newPacket) ;
void    addCRC(packet *newPacket) ;
int     checkCRC(packet *newPacket) ;
char   *getPayload(packet *newPacket) ;
packet *createNormalPacket(char seqNum) ;
packet *createAckPacket(char seqNum) ;
int     isNormal( packet *newPacket ) ;
int     isEndOfMessage( packet *newPacket ) ;
int     isAck( packet *newPacket ) ;
void    printPacketContents(packet *newPacket ) ;
void    getVerboseFrameKind(packet *newPacket, char *dstString) ;
