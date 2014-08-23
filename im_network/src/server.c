// server.c

/********************************************/
// This file holds the main driver for the
// server
/********************************************/

#include "tcp/server/tcp_server.h"
#include "common.h"
#include <stdlib.h>

/*** PRIVATE FUNCTION PROTOTYPES ***/
void initServer() ;

// Main driver for server
// jbodah
int main( int argc, char *argv[] ) {
  if( argc != 3 )
		DieWithErr( "Usage: ./PROG_NAME ERROR_RATE DEBUG_MODE" ) ;
    
  if( (atoi(argv[1]) > 100) || (atoi(argv[1]) < 0) )
    DieWithErr( "ERROR_RATE must be between 0 and 100" ) ;
  else
    GL_error_rate = atoi(argv[1]) ;
    
  if( atoi(argv[2]) != 0 && atoi(argv[2]) != 1 )
    DieWithErr( "DEBUG_MODE must be 0 or 1" ) ;
  else 
    GL_debug = atoi(argv[2]) ;
		
  initServer() ;
	int servSock = openConnection() ;
	handleIncomingConnections( servSock ) ;

	return 0 ;
}

// Run anything that we need to when the server first starts
// jbodah
void initServer() {
}
