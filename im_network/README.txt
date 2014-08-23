Team 1: Cheng Cheng and Josh Bodah

HOW TO COMPILE:
In root directory:
> make

HOW TO RUN:
In root directory:
> ./server ERROR_RATE DEBUG_MODE
> ./client HOSTNAME ERROR_RATE DEBUG_MODE

PARAMETERS EXPLAINED:
- HOSTNAME: IP or hostname (ex: 128.64.0.1 or cccwork1.wpi.edu)
- ERROR_RATE: integer value in [0,100] which defines the % of CRC errors to automatically generate
- DEBUG_MODE: 0 or 1. Shows debug information (a bit messy since the app is multithreaded, but can be useful sometimes)

WHAT SHOULD WORK:
- Sliding window of size N (GoBackN implementation)
- Errors on frames
- Errors on Acks
- Timeouts
- Message-to-packet fragmentation
- Packet-to-message assembly
- Flow control between
- Fluid communication between layers
- Concurrent server/TCP connection handling

WHAT ISNT HERE:
- Byte stuffing is not included. Our design decision was to use a size field in the packet instead.
- Statistics and timing data
- Upload/download

WHAT MIGHT/MIGHT NOT WORK:
- Memory inefficient, doesnt free most of the space it dynamically allocates, so big, long trials will yield issues
- We weren't able to fully test the application layer, so that may have some issues
- Database concurrency (most likely will work given the architecture of the system)

GENERAL DESIGN:
There are two major branches in the code (client and server). In addition, there are three layers for each branch. We've tried to use a logical directory structure to keep track of everything. The word "common" refers to elements that are shared between the modules.

The system uses multiple threads and passes messages by placing events into event queues. (These structures are defined in src/common.h). Inside these events is data that is used to handle the event. The most important data structures that can be in an event are 1) a message, 2) a packet, 3) a timer. The major threads are as follows:

-SERVER
** Main thread for listening for TCP connections
** FOR.EACH.TCP
***** TCP Sender thread
***** TCP Receiver thread
***** Data Link thread
***** Application thread

-CLIENT
** TCP Sender thread
*** TCP Receiver thread
*** Data Link thread
****** Timer threads for sliding window
** Application thread

In general, each thread will wait for an event to arrive in its queue and then will process the event as needed. This ensures that the layers are fairly independent (a few exceptions, such as with flow control).

One unintuitive structure is the packet. The packet has the following "fields" which are stored as character in a string:
- 2 bytes sync data ('A' + 'A')
- 1 byte sequence "number" (between 'a' and 'z')
- 1 byte frame kind ('a' normal data packet, 'b' ACK packet, 'c' the last data packet in a message)
- 1 byte size of payload
- variable sized payload
- 1 byte (always the last) CRC
