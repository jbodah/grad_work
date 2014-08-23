#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "app_common.h"

int testDup(char *filename,char *username,char *password)
{
    FILE *fp;
    fp = fopen(filename, "a+");
    char line[128];
    while(fgets(line,sizeof line,fp)!=NULL)
	{
        char *namer = strtok(line,"  \n");
        char *passwordr = strtok(NULL," \n");
        int nameT= strcmp(namer,username);
        int pswT = strcmp(namer,password);
        
        if((nameT==0)&&(pswT ==0))
        {	
            //printf("__________________exist");
            goto close;
        }
	}
    //printf("___________________invalid");
    fclose(fp);
    return 1;
close: fclose(fp);
    return 0;
}
void checkFile(event_queue *p_queue,char *username)
{
    FILE *fp;
    fp = fopen("file.list", "a+");
    char line[128],lineTemp[128];
    int a=0;
    event   *newEvent    = createEvent() ;
    message *newMessage  = (message *)malloc(sizeof(message));
    while(fgets(line,sizeof line,fp)!=NULL)
    {
        strcpy(lineTemp,line);
        char *namer = strtok(line,"  \n");
        //char *passwordr = strtok(NULL," \n");
        int nameT= strcmp(namer,username);
        //int pswT = strcmp(namer,password);
        
        if(nameT==0)
        {   
            a =1;
            strcat( newMessage->contents, lineTemp);
            strcat( newMessage->contents, " \n");
        }
    }
    if(a==0) {strcpy( newMessage->contents, "No File");}
    sendMessage( p_queue, newMessage) ;	
    fclose(fp);
}

int  addValue(char *filename, char *username, char *password)
{
    FILE *fp;
    fp = fopen(filename, "a+");
    //printf("________________%d",testDup(filename, username, password));
    if(testDup(filename,username, password)==1)
    {fputs(username,fp);
        fputs(" ",fp);
        fputs(password,fp);
        fputs("\n",fp);
        fclose(fp);
        return 0;
    }
    else if(testDup(filename,username, password)==0)
    {   fclose(fp);
        return 1;}
}

int removeFile(char* file, char *fileName, char *userName)
{  
    int fileNum = 0;
    FILE *fp;
    fp = fopen(file, "a+");
    FILE *fp1;
    fp1 = fopen("temp.list","a+");
    char line[128];
    char lineTemp[128];
    while(fgets(line,sizeof line,fp)!=NULL)
    {   
        strcpy(lineTemp,line);
        char *namer = strtok(line," ");
        char *passwordr = strtok(NULL," \n");
        int nameT= strcmp(namer,fileName);
        int pswT = strcmp(passwordr,userName);
        printf("\n%s, %s, %d, %d,\n",namer, passwordr, nameT, pswT);
        if((nameT==0)&&(pswT ==0))
        {
            printf("exist");
            remove(fileName);
            while (fgets(line,sizeof line,fp)!=NULL)
            { fputs(line,fp1);}
            rename("temp.list", file);
            goto close;
        }
        else if((nameT ==0)&&(pswT != 0))
        {
            fileNum ++;
        }
        fputs(lineTemp,fp1);	
    }
    if(fileNum == 0) {return 2;}
    else {return 1;}
close: fclose(fp);
    remove("temp.list");
    return 0;
} 
void sendFile(event_queue *p_queue,char *fileName)//,event_type *p_queue)
{
    FILE *fp;
    fp = fopen(fileName, "a+");
    FILE *fp1;
    fp1 = fopen("temp.txt","w");
    char message[6];
    while(!feof(fp))
    { 
        if(fgets(message,sizeof(message),fp)!= NULL);
        {
            printf("message: %s\n",message);
            fputs(message,fp1);
            //sendMessage(p_queue,message);
        }
    }
    fclose(fp1);
    fclose(fp);
}
void revcFile(char *fileName, char *message)
{
    FILE *fp;
    fp = fopen(fileName, "a+");
    fputs(message,fp);
    fclose(fp);
}
int testMain()
{ 
    char *a = "abcd";
    char *b = "abcd";
    //userRegister(a,b);
    //testUser("a","b");
    //revcFile("test.txt", "aaaaa");
    //revcFile("test.txt","bbbbb");
    //sendFile("test.txt");
    addValue("file.list","c","a");
}
