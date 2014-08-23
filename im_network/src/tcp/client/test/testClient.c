//tcp_test.c

#include "tcp_sender.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

/*
KNOWN ISSUES
- string operations on NULL values not handled gracefully
- no support for closing connection gracefully
*/

int test() {
	// hostnameToIP()
	char ip_address[ADDR_BUFFER] ;
	hostnameToIP( "CCCWORK2.WPI.EDU", ip_address ) ;
	assert( strcmp( ip_address, "130.215.36.68" ) == 0 ) ;
	
	// formRequest()
	request *newRequest = formRequest( "CCCWORK1.WPI.EDU", "503", "" ) ;
	assert( strcmp( newRequest->dst_address, "CCCWORK1.WPI.EDU" ) == 0 ) ;
	assert( strcmp( newRequest->command, "503" ) == 0 ) ;
	assert( strcmp( newRequest->params, "" ) == 0 ) ;
	
	// establishConnection()
	int clntSock = 0 ;
	clntSock = establishConnection( newRequest->dst_address ) ;	
	assert( clntSock != 0 ) ;
	
	// sendCommand()
	printf( "\n" ) ;
	sendCommand( clntSock, "503" ) ;
	
	printf( "\n\nCode looks good!\n\n" ) ;
}
