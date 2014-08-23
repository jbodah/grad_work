#include <stdio.h>          /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>   /* for sockaddr_in and inet_addr() */
#include <stdlib.h>        /* for atoi() and exit() */
#include <string.h>       /* for memset() */
#include <unistd.h>      /* for close() */
#include <netdb.h>
#include "middle.h"
#include "dll_client.h"

#define msgBufferSize 256   /* Size of receive buffer */
#define frameBuffersize 128   /* Size of send buffer */

char rcvMsgBuffer[msgBufferSize];
char sendFrameBuffer1[frameBuffersize];
char sendFrameBuffer2[frameBuffersize];
char sendFrameBuffer3[frameBuffersize];
char sendMsgBuffer[msgBufferSize];
char rcvFrameBuffer[frameBuffersize];
int seq_num = 1;

void DieWithError(char *errorMessage)  /* Error handling function */
{
    perror(errorMessage);
    exit(1);
}
void getMessage(char *app_msg_buffer) /*get message from app*/
{
    memcpy(rcvMsgBuffer, app_msg_buffer , strlen(app_msg_buffer)+1);
    printf("%s, \n", rcvMsgBuffer);
}
void getFrame(char *tcp_frame_buffer) /*get frame from tcp*/
{
    memcpy(rcvFrameBuffer, tcp_frame_buffer ,strlen(tcp_frame_buffer)+1);
    printf("%s, \n", rcvFrameBuffer);
}
char stuffing(char *sendFrameBuffer);
void breakMsg(char *rcvMsgBuffer)
{
    strncpy (sendFrameBuffer1,rcvMsgBuffer,3);
    sendFrameBuffer1[3]='\0';
    stuffing(sendFrameBuffer1);
    
    char * temp = StringSub(rcvMsgBuffer,4,255);
    strncpy (sendFrameBuffer2,temp,3);
    sendFrameBuffer2[3]='\0';
    temp = StringSub(rcvMsgBuffer,7,255);
    strncpy (sendFrameBuffer3,temp,3);
    sendFrameBuffer3[3]='\0';
    printf("%s,\n",sendFrameBuffer1);
    printf("%s,\n",sendFrameBuffer2);
    printf("%s,\n",sendFrameBuffer3);
}
void combineMsg();

char *strrev(char *str) {
	char *p1, *p2;
    
    if (!str || !*str)
		return str;
	for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2) {
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}
	return str;
}
char *itoa(int n, char *s, int b) {
	static char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	int i=0, sign;
    
	if ((sign = n) < 0)
		n = -n;
	do {
		s[i++] = digits[n % b];
	} while ((n /= b) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	return strrev(s);
}
char stuffing(char *sendFrameBuffer)
{
    char temp[128];
    strcpy(temp, sendFrameBuffer); //,strlen(sendFrameBuffer));
    printf("temp: %s,\n", temp);
    
    char frame[128];
    frame[0] = '\002';//bit of STX 
    frame[1] = seq_num;r
    seq_num ++;
    frame[2] = '\0';
    char buffer[25];
    seq_num = 2;
    itoa(seq_num, buffer, 2);
    //frame[1] = (char *)seq_num;
    //buffer   =   Convert.ToString(seq_num,2);
    //strcat(frame,buffer); 
    strcat (frame,temp);
    printf("frame: %s, length: %d \n", frame, strlen(frame));
    return frame[128];
    
}
void deStuffing();


int main()
{
    char *a = "adsfaaaaaa";
    breakMsg(a);
    getFrame(a);
    getMessage(a);
    return 0;
    // printf("%s ;\n", sendFrameBuffer1);
    // printf("%s ;\n", sendFrameBuffer2);
    // printf("%s ;\n", sendFrameBuffer3);
    
}




