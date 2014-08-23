int  testDup(char *filename,char *username,char *password);
int  addValue(char *filename, char *username, char *password);
int removeFile(char* file, char *fileName, char *userName);
void sendFile(char *fileName);
void checkFile(event_queue *p_queue,char *username);
void revcFile(char *fileName, char *message);
