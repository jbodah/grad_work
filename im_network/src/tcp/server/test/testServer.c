//test.c

#include "tcp_receiver.h"
#include <assert.h>
#include <stdio.h>

void test() {
	// openConnection()
	int servSock = 0 ;
	servSock = openConnection() ;
	assert( servSock != 0 ) ;
	
	// handleIncomingConnections()
	handleIncomingConnections( servSock ) ;
	
	printf( "\nCode looks good!\n\n" ) ;
}
