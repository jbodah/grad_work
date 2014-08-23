// /app/server/app_main.c

/*********************************************/
// This file contains the top-level logic
// that App layer uses to process events
/*********************************************/

#include "../../common.h"
#include "../app_common.h"
#include "../db.h"
#include "app_main.h"
#include <stdio.h> //For testing
#include <string.h> // for strcpy
#include <stdlib.h> // for malloc

/*** PRIVATE PROTOTYPES ***/
void handleMessage( event_queue *p_queue, message *p_message ) ;
void error0Response( event_queue *p_queue ) ;
void error1Response( event_queue *p_queue ) ;
void error2Response( event_queue *p_queue ) ;
void loginResponse( event_queue *p_queue,char *user, char *psw );
void logoutResponse( event_queue *p_queue);
void removeFileResponse( event_queue *p_queue,char *fileName,char *user );
void uploadFileResponse( event_queue *p_queue,char *fileName);
void checkFileResponse( event_queue *p_queue,char *fileName);
int login=0;
char *userName="b";

// How to communicate with DLL layer: addEventToQueue( p_DLLQueue, someEvent )
//
// jbodah
void AppMain( event_queue *p_DLLQueue, event_queue *p_AppQueue ) { 
    event *currentEvent ;
    
    while(1) {
        currentEvent = wait_for_event(p_AppQueue) ;
        if( currentEvent->type == RECEIVE_MESSAGE ) {
            printReceiveMessage( (message *)currentEvent->data ) ;
            handleMessage( p_DLLQueue, (message *)currentEvent->data ) ;
        }
    }
}

/****** CASE-HANDLING OF MESSAGES *****/

// Parse message and send back a response
// cheng
void handleMessage( event_queue *p_queue, message *p_message ) {
    if( 1 ) // parse message, command is in p_message->contents
    {
        char *command = strtok(p_message->contents," ");
        printf("command: %s", command); 
        //char *par1 = strtok(NULL, " ");
        //char *par2 = strtok(NULL, " ");
        if(!strcmp(command,"login")&&(login==0))
        {
            char *par1 = strtok(NULL, " ");
            char *par2 = strtok(NULL, " ");
            printf("par1,par2:  %s,%s\n\n\n",par1,par2);//,length1,length2);
            if(par1!='\0'&&par2!='\0')
            {loginResponse(p_queue,par1,par2 ) ;} // send response
            else 
            {error0Response(p_queue);}
        } 
        
        else if(!strcmp(command,"login")&&(login==1))
            error2Response(p_queue);
        else if(!strcmp(command,"logout")&&(login==1)) 
            logoutResponse(p_queue);
        else if(!strcmp(command,"removeFile")&&(login==1)) 
        {
            char *par3 = strtok(NULL," ");
            char *par4 = strtok(NULL," ");
            removeFileResponse(p_queue,par3,par4);
        }
        else if(!strcmp(command,"updateFile")&&(login==1))
        {
            char *par5 = strtok(NULL," ");
            uploadFileResponse(p_queue,par5);
        }
        else if(!strcmp(command,"checkFile")&&(login==1))
        {
            char *par6 = strtok(NULL," ");
            checkFileResponse(p_queue,par6);
        }
        else error1Response(p_queue); 
    }
}

// An example of how to setup a response
// cheng
void error1Response( event_queue *p_queue ) {
    event   *newEvent    = createEvent() ;
    message *newMessage  = (message *)malloc(sizeof(message)) ;
    
    strcpy( newMessage->contents, "Please Login First!" ) ;
    
    sendMessage( p_queue, newMessage ) ;
}
void error2Response( event_queue *p_queue ) {
    event   *newEvent    = createEvent() ;
    message *newMessage  = (message *)malloc(sizeof(message)) ;
    
    strcpy( newMessage->contents, "You have already login. Don't login more than once!" ) ;
    sendMessage( p_queue, newMessage ) ;
}
void error0Response( event_queue *p_queue ) {
    event   *newEvent    = createEvent() ;
    message *newMessage  = (message *)malloc(sizeof(message)) ;
    
    strcpy( newMessage->contents, "Please Username and Password!" ) ;
    
    sendMessage( p_queue, newMessage ) ;
}
void loginResponse( event_queue *p_queue,char *user, char *psw ) 
{
    event   *newEvent    = createEvent() ;
    message *newMessage  = (message *)malloc(sizeof(message)) ;
    int a = testDup("user.list",user,psw); //segmentation false
    if (a==0)
    {
        strcpy( newMessage->contents, "loginSuccessfully");
        login = 1;
        //strcat(userName, user);
    }
    else if(a==1)
    {strcpy( newMessage->contents, "loginFalse");}
    
    sendMessage( p_queue, newMessage ) ;
}
// cheng
void removeFileResponse( event_queue *p_queue,char *fileName,char *user)
{
    
    event   *newEvent    = createEvent() ;
    message *newMessage  = (message *)malloc(sizeof(message)) ;
    int b = removeFile("file.list",fileName,user); //segmentation false
    if (b==0)
    {
        strcpy( newMessage->contents, "remove Successfully");
        sendMessage( p_queue, newMessage ) ;
    }
    else if(b==1)
    {strcpy( newMessage->contents, "Without Permission");
        
        sendMessage( p_queue, newMessage ) ;}
    else if(b==2)
    {strcpy( newMessage->contents, "No File");
        sendMessage( p_queue, newMessage ) ;
    }
}
//cheng
void logoutResponse( event_queue *p_queue)
{
    event   *newEvent    = createEvent() ;
    message *newMessage  = (message *)malloc(sizeof(message)) ;
    
    if (login==0)
    {
        strcpy( newMessage->contents, "Please Login First!");
        
    }
    else
    {strcpy( newMessage->contents, "logoutSuccessfully");
        login = 0;
    }
    
    sendMessage( p_queue, newMessage ) ;
}
//cheng
void uploadFileResponse( event_queue *p_queue,char *fileName)
{
    event   *newEvent    = createEvent() ;
    message *newMessage  = (message *)malloc(sizeof(message)) ;
    int c = addValue("file.list", fileName, "a");
    if (c==0)
    {
        strcpy( newMessage->contents, ("send %d",fileName));
        sendMessage( p_queue, newMessage ) ;
    }
    else
    {strcpy( newMessage->contents, "You have already upload such a file.");
        sendMessage( p_queue, newMessage ) ;
    }
}
//cheng
void checkFileResponse( event_queue *p_queue,char *fileName)
{
	checkFile(p_queue, fileName);
}

