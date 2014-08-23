
#include "tcp_receiver.h"
#include "test.h"
#include "../../common.h"
#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
int  NUM_THREADS=0;
void *PrintHello(void *arg);
void closeThread();
void createThread();
main()
{
    createThread();
    createThread();
    //    closeThread();
    createThread();
    //    closeThread();
    //    closeThread();
    //     closeThread();
}

/*after a new client connected with server, create a new thread. */
void createThread() 
{
    pthread_t thread;
    int rc;
    char *message = "hello";
    rc = pthread_create(&thread,NULL, PrintHello, 
                        (void *)message);
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(0);
    }
    printf("Create thread %d; \n", NUM_THREADS);
    NUM_THREADS++;
    //  closeThread(thread); 
}
/*a client tries to logout, close the thread for the certain client*/
void closeThread(pthread_t thread) 
{
    pthread_cancel(thread);
    NUM_THREADS--;
    printf("Cancel thread %d;\n", NUM_THREADS);
}
void *PrintHello(void *arg)
{
    char *msg = (char *) arg;
    printf("%s\n", msg);
}
