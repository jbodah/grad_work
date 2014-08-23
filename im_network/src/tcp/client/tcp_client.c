// /tcp/client/tcp_client.c

/*****************************************************************/
// This file contains code for client TCP connection
/*****************************************************************/

#include "../tcp_common.h"
#include "tcp_client.h"
#include "../../common.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
//#include <netdb.h>
#include <stdio.h> // REMOVE ME

// jbodah
int establishConnection( char *dst_address ) {
	struct sockaddr_in  	servAddr ;
	char 									servIP[INET_ADDRSTRLEN] ;
	int										clntSock = setupSocket();
	
	hostnameToIP( dst_address, servIP ) ;
	
	// Init server address struct
  memset( &servAddr, 0, sizeof( servAddr ))  ;	
  servAddr.sin_family       = AF_INET ;
  servAddr.sin_addr.s_addr  = inet_addr( servIP ) ;
  servAddr.sin_port         = htons( SERVER_PORT ) ;

	if( connect( clntSock, (struct sockaddr *) &servAddr, sizeof( servAddr )) < 0 )
    DieWithErr( "connect() failed" ) ;
	
	return clntSock ;
}

/*** Sends TCP message in buffer ***/
// jbodah
void TCPSend( int clntSock, char *sendBuffer, int size ) {
	if( send( clntSock, sendBuffer, size, 0 ) != size )
		DieWithErr( "send() sent a different number of bytes than expected" ) ;
}

/*** Receives TCP message & stores in buffer ***/
// jbodah
void TCPReceive( int clntSock, char *receiveBuffer, int size ) {
	int	bytesRcvd ;
	int	totalBytesRcvd ;
	
	totalBytesRcvd = 0 ;
	bytesRcvd = 0 ;
	while( totalBytesRcvd < size ) {
		if(( bytesRcvd = recv( clntSock, receiveBuffer, size, 0 )) < 0 )
			DieWithErr( "recv() failed" ) ;
		else if( bytesRcvd == 0 )
			DieWithErr( "connection closed prematurely" ) ;
		totalBytesRcvd += bytesRcvd ;
		receiveBuffer[bytesRcvd] = '\0' ;
	}
}
