// /tcp/tcp_common.h

/*****************************************************************/
// This file contains code common between TCP implementations
/*****************************************************************/

#include "../common.h"

#define ADDR_BUFFER           30
#define COMM_BUFFER           30
#define COMM_PARAM_BUFFER     30
#define BACKLOG               5

#ifndef _REQUEST
#define _REQUEST
typedef struct request {
  char  dst_address[ADDR_BUFFER] ;
  char  command[COMM_BUFFER] ;
  char  params[COMM_PARAM_BUFFER] ;
} request ;
#endif

void tcpMain( void *sockArg ) ;
void hostnameToIP( char *dst_hostname, char *ip_address ) ;
int  setupSocket() ;
