// dll_common.h

#define SEC_UNTIL_TIMEOUT     5

void  initTimer( clock_t *timer ) ;
int   hasTimeoutOccurred( clock_t timer ) ;
