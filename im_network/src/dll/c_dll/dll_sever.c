#include <stdio.h>          /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>   /* for sockaddr_in and inet_addr() */
#include <stdlib.h>        /* for atoi() and exit() */
#include <string.h>       /* for memset() */
#include <unistd.h>      /* for close() */
#include <netdb.h>

#define msgBufferSize 256   /* Size of receive buffer */
#define frameBuffersize 128   /* Size of send buffer */

char rcvMsgBuffer[msgBufferSize];
char sendFrameBuffer1[frameBuffersize];
char sendFrameBuffer2[frameBuffersize];
char sendFrameBuffer3[frameBuffersize];
char sendMsgBuffer[msgBufferSize];
char rcvFrameBuffer[frameBuffersize];


void DieWithError(char *errorMessage)  /* Error handling function */
{
    perror(errorMessage);
    exit(1);
}
void getMessage(char app_msg_buffer) /*get message from app*/
{
    memset(&rcvMsgBuffer, 0 , sizeof(app_msg_buffer));
}
void getFrame(char tcp_frame_buffer) /*get frame from tcp*/
{
    memset(&rcvFrameBuffer, 0 ,sizeof(tcp_frame_buffer));
}
void breakMsg(char rcvMsgBuffer)
{
    memset(&sendFrameBuffer1, 0, 115);
}
void combineMsg()
{}
void stuffing(char sendFrameBuffer)
{
    
}
void deStuffing()
{}
void send ()
{
    
}
void recv()
{
    
}



 
 