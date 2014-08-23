/*get part of the Buffer, helps to break the message into small frame*/

#include <stdio.h>

char* StringSub(const char* string,int start,int number)
{
    int len = strlen(string);
    char* temp;
    if(start <= 0)
    {
        printf("Start %d is too small !\n",start);
        start = 1;
    }
    else if(start>len)
    {
        printf("Start %d is too big than string length %d!\n",start,len);
        return NULL;
    }
    if(number>(len-start+1))
    {
        //printf("Number %d is too big!\n",number);
        number = len - start + 1;
    }
    if(number<0)
    {
        printf("Number %d is too small!\n",number);
        number = len - start + 1;
    }
    
    temp = (char*)malloc(sizeof(char)*(number+1));
    memset(temp,0,(number+1)*sizeof(char));
    
    int i = 0;
    int j = 0;
    while(i != number)
        temp[i++] = string[(start-1)+j++];
    temp[number]='\0';
    
    return temp;
}
//int main()
//{
//    char *a = StringSub("adserwt",2,5);
//    printf("%s",a);
//    
//}
