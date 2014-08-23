 /* Size of receive buffer */
#define frameBuffersize 128   /* Size of send buffer*/ 
#define msgBufferSize 256  /*Size of receive buffer */

void DieWithError(char *errorMessage);
void getMessage(char *app_msg_buffer); /*get message from app*/
void getFrame(char *tcp_frame_buffer); /*get frame from tcp*/
void breakMsg(char *rcvMsgBuffer);
void combineMsg();
void deStuffing();
