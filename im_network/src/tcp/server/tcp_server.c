// /tcp/server/tcp_server.c

/*****************************************************************/
// This file contains code for server TCP connection
/*****************************************************************/

#include "../tcp_common.h"
#include "tcp_server.h"
#include "../../common.h"
#include "../../dll/dll_init.h"
#include "../../app/server/app_init.h"
#include "tcp_init.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
//#include <errno.h>
#include <netdb.h>
#include <stdio.h> // REMOVE ME

/*** PRIVATE PROTOTYPES ***/
void  makeNewThreadForTCPClient( int clntSock ) ;

// Initialize a socket to accept connections on
// jbodah
int openConnection() {
	struct sockaddr_in  servAddr ;
  int servSock = setupSocket() ;
  
  // Init server address struct
  memset( &servAddr, 0, sizeof( servAddr )) ;
  servAddr.sin_family        = AF_INET ;
  servAddr.sin_addr.s_addr   = htonl( INADDR_ANY ) ;
  servAddr.sin_port          = htons( SERVER_PORT ) ;
      
  // Bind server socket to server address
  if( bind( servSock, (struct sockaddr *) &servAddr, sizeof( servAddr )) < 0 )
    DieWithErr( "bind() failed" ) ;
		
	if( listen( servSock, BACKLOG ) < 0 )
		DieWithErr( "listen() failed" ) ;

	return servSock ;
}

// Wait for connections on servSock
// Create a new socket for each connection
// jbodah
void handleIncomingConnections( int servSock ) {
	struct sockaddr_in  clntAddr ;
	int									clntAddrLen = sizeof( clntAddr ) ;
  int                 clntSock ;

  while(1) {
    if(( clntSock = accept( servSock, (struct sockaddr *) &clntAddr, &clntAddrLen )) >= 0 ) {
      printf( "Handling client %s on socket %d\n", inet_ntoa( clntAddr.sin_addr ), clntSock ) ;
      makeNewThreadForTCPClient( clntSock ) ;
      clntSock = -1 ;
    }
  }
}

// Create a new thread for the client
// jbodah
void makeNewThreadForTCPClient( int clntSock ) {
  int           *newClntSock    = malloc(sizeof( int )) ;
  *newClntSock                  = clntSock ;
  
  event_queue   *p_DLLQueue     = malloc(sizeof(event_queue)) ;
  event_queue   *p_TCPQueue     = malloc(sizeof(event_queue)) ;
  event_queue   *p_AppQueue     = malloc(sizeof(event_queue)) ;
  
  TCPArgs       *p_TCPargs      = malloc(sizeof(TCPArgs)) ;
  DLLArgs       *p_DLLargs      = malloc(sizeof(DLLArgs)) ;
  AppArgs       *p_Appargs      = malloc(sizeof(AppArgs)) ;
  
  int           *p_isServer = malloc(sizeof(int)) ;
  
  *p_isServer = 0 ;
  
  // Init queues
  initQueue( p_TCPQueue ) ;
  initQueue( p_DLLQueue ) ; 
  initQueue( p_AppQueue ) ;
  
  // Copy args into structs
  p_TCPargs->p_sock = newClntSock ;
  p_TCPargs->p_TCPQueue = p_TCPQueue ;
  p_TCPargs->p_DLLQueue = p_DLLQueue ;
  
  p_DLLargs->p_TCPQueue = p_TCPQueue ;
  p_DLLargs->p_DLLQueue = p_DLLQueue ;
  p_DLLargs->p_AppQueue = p_AppQueue ;
  p_DLLargs->p_isServer = p_isServer ;
  
  *p_isServer = 1 ;
  
  p_Appargs->p_DLLQueue = p_DLLQueue ;
  p_Appargs->p_AppQueue = p_AppQueue ;
  
  // Make new thread for TCP
  pthread_t newTCPThread ;
  pthread_create( &newTCPThread, NULL, (void *) &TCPInit, (void *) p_TCPargs ) ;
  
  // Make new thread for DLL
  pthread_t newDLLThread ;
  pthread_create( &newDLLThread, NULL, (void *) &DLLInit, (void *) p_DLLargs ) ;
  
  // Make new thread for App
  pthread_t newAppThread ;
  pthread_create( &newAppThread, NULL, (void *) &AppInit, (void *) p_Appargs ) ;
}

// Receive TCP message and store in buffer
// jbodah
int TCPReceive( int clntSock, char *receiveBuffer, int size ) {
	int bytesRcvd ;
	
  if(( bytesRcvd = recv( clntSock, receiveBuffer, size, 0 )) < 0 )
    DieWithErr( "recv() failed" ) ;
  else if( bytesRcvd == 0 ) {
		DieWithErr( "connection closed prematurely" ) ;
	}
	
	return bytesRcvd ;
}

// Send buffer to client
// jbodah
void TCPSend( int clntSock, char *sendBuffer, int size ) {
  int  bytesSent ;
	
  if(( bytesSent = send( clntSock, sendBuffer, size, 0 )) < 0 )
    DieWithErr( "send() failed" ) ;
  else if( bytesSent != size )
    DieWithErr( "send() failed: sent unexpected number of bytes" ) ;
}
