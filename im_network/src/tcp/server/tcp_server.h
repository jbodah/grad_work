// /tcp/server/tcp_server.h

/*****************************************************************/
// These TCP server functions were exposed for testing purposes
/*****************************************************************/

#include "../../common.h"

int   openConnection() ;
void  handleIncomingConnections( int servSock ) ;
void 	TCPSend( int clntSock, char *sendBuffer, int size ) ;
int 	TCPReceive( int clntSock, char *receiveBuffer, int size ) ;
