// /tcp/tcp_common.c

/*****************************************************************/
// This file contains code common between TCP implementations
/*****************************************************************/

#include "../common.h"
#include "tcp_common.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>

// Creates a new request with the parameters given
// jbodah
request *formRequest( char *dst_address, char *command, char *params ) {
	request *newRequest = malloc( sizeof( request )) ;
	
	strcpy( newRequest->dst_address, dst_address ) ;
	strcpy( newRequest->command, command ) ;
	strcpy( newRequest->params, params ) ;
	
	return newRequest ;
}

// Convert hostname to IP address
// Copy into ip_address
// jbodah
void hostnameToIP( char *hostname, char *ip_address ) {
	char 						 	servIP[ADDR_BUFFER] ;
	void	 					 *addr ;
	struct addrinfo 	hints ;
	struct addrinfo  *servInfo ;
	
  memset( &hints, 0, sizeof( hints )) ;
  hints.ai_family   = AF_INET ;
  hints.ai_socktype = SOCK_STREAM ;
  
  if( getaddrinfo( hostname, SERVER_PORT_STRING, &hints, &servInfo ) < 0 )
    DieWithErr( "getaddrinfo() failed" ) ;
  
  // This implementation taken from Beej's guide for getaddrinfo()
  // Note: In his example he prints a list of IP's
  // Recast the struct servInfo and take the address field
  addr = &((struct sockaddr_in *)servInfo->ai_addr)->sin_addr ;
  
  // Convert address to string and then proceed like it was IP address (ex. "192.168.1.1")
  inet_ntop( servInfo->ai_family, addr, servIP, sizeof( servIP )) ;
	
	strcpy( ip_address, servIP ) ;
}

// Returns a socket to connect to
// jbodah
int setupSocket() {
	int sock ;
	if(( sock = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP )) < 0 )
		DieWithErr( "socket() failed" ) ;
	return sock ;
}
