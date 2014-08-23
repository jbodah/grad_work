// /tcp/client/tcp_client.h

/*****************************************************************/
// These TCP client functions were exposed for testing purposes
/*****************************************************************/

#include "../tcp_common.h"

int       establishConnection( char *dst_address ) ;
request  *formRequest( char *dst_address, char *command, char *params ) ;
void      TCPSend( int clntSock, char *sendBuffer, int size ) ;
void      TCPReceive( int clntSock, char *receiveBuffer, int size ) ;
