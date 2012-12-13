/* Compile with 'gcc -lsctp sctpServer.c' */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>

const int MAX_BUFFER = 1024;
const int PORT_NUM = 3366;

const int STREAM_NUM = 0;

int main() {
   char buffer[MAX_BUFFER+1];
   memset((void*) &buffer, 0xDEADBEEF, sizeof(buffer));
   int listenSock, connSock;
   listenSock = connSock = 0;

   struct sockaddr_in address;
   memset((void*) &address, 0, sizeof(address));


   listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = htonl(INADDR_ANY);
   address.sin_port = htons(PORT_NUM);

   bind(listenSock, (struct sockaddr *) &address, sizeof(address));

   listen(listenSock, 16);
   printf("Listening...\n");
   while(1) {
      struct sockaddr remoteAddress;
      memset((void*) &remoteAddress, 0, sizeof(address));
      int retLength = 0;
      socklen_t remoteAddressLength = 0;
      struct sctp_sndrcvinfo messageInfo;
      memset((void*) &messageInfo, 0, sizeof(messageInfo));
      // Might not be needed?
      //struct sctp_event_subscribe events;

      //listenSock = accept(listenSock, (struct sockaddr*) NULL, 0, 0);
      //printf("Connection accepted!\n");
      retLength = sctp_recvmsg(listenSock, (void*) &buffer, sizeof(buffer), 
            &remoteAddress, &remoteAddressLength, 
            &messageInfo, 0);
      //printf("Message received... on channel %d\n", messageInfo.sinfo_stream);
      // Zero terminate message
      buffer[retLength] = 0;

      //Now reply on same stream
      sctp_sendmsg(listenSock, (void*) &buffer, retLength,
            &remoteAddress, remoteAddressLength,
            0, 0, 
            messageInfo.sinfo_stream, 
            0, 0); 
   }


   close(listenSock);

   return 0;
}
