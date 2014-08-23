#include <stdio.h>
#include <stdbool.h>
#define MAX_SEQ 7

typedef enum {frame_arrival, cksum_err, timeout, network_layer, ready} event_type;

typedef int {next_fram_to_send, ack_expected, frame_expected} seq_nr;

struct frame
{
    char *info;
    int seq_num;
    int ack;
    int expected;

};

static bool between(int a,int b,int c )
{
//Return true if a<=b<c circularly; false otherwise 
    if(((a<=b)&&(b<c))||((c<a)&&(a<=b))||((b<c)&&(c<a)))
 	return true;
    else 
	return false;
}

static void send_data(int seq_num, int expected, char frame[])
{
   /*Construct and send a data frame*/
     struct frame s;
     s.info= frame;
     s.ack = (expected + MAX_SEQ)%(MAX_SEQ + 1);
     printf("%s,%d,\n",s.info,s.ack);// transmit the frame
     // how to implement it start_time(frame.seq_num);
}

void protocol5(void)
{
    seq_nr next_fram_to_send;
    seq_nr ack_expected;
    seq_nr frame_expected;
    struct frame r;
   // buffer[MAX_SEQ+1];
    seq_nr nbuffered;
    seq_nr i;
    event_type event;
    
    enable_network_layer();
    ack_expected = 0;
    next_fram_to_send = 0;
    frame_expected = 0;
    nbuffered = 0;
    
    while (true) {
        wait_for_event(&event);
        
        switch (event) {
            case network_layer_ready:
                from_network_layer(&buffer[next_fram_to_send]);
                nbuffered = nbuffered + 1;
                send_data(next_fram_to_send, frame_expected, buffer);
                next_fram_to_send ++;
                break;
                
            case frame_arrival:
                from_physical_layer(&r);
                
                if (r.seq_num ==frame_expected) {
                    to_network_layer(&r.info);
                    frame_expected ++;
                }
                while (between(ack_expected, r.ack, next_fram_to_send)) {
                    nbuffered = nbuffered -1;
                    stop_time(ack_expected);
                    ack_expected ++;
                }
                break;
            case cksum_err: break;
            case timeout:
                next_fram_to_send = ack_expected;
                for (i = 1; i < = nbuffered; i++) {
                    send_data(next_fram_to_send, frame_expected, buffer);
                    next_fram_to_send ++;
                }
                
        }
        if (nbuffered< MAX_SEQ) 
            enable_network_layer();
        else 
            disable_network_layer();
        
    }
    
}

int main()
{char frame[] = "aaaa";
 struct frame frame0;
 frame0.info = "a";
 frame0.seq_num = 8;
 frame0.expected = 7;
 printf("%s,%d, \n",frame0.info,frame0.seq_num);
 send_data(frame0.seq_num, frame0.expected, frame);
}
