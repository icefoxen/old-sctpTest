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

const int CHANNEL = 0;

int main() {
   char buffer[MAX_BUFFER+1];
   memset((void*) &buffer, 0xDEADBEEF, sizeof(buffer));
   int sock, retLength;
   sock = retLength = 0;

   struct sockaddr address;
   memset((void*) &address, 0, sizeof(address));

   sock = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);

   struct sockaddr addr;
   socklen_t addrLength = 0;

   struct sctp_sndrcvinfo sinfo;
   memset((void*) &sinfo, 0, sizeof(sinfo));

   while(1) { 
      size_t messageSize = 0;
      printf("> "); fflush(stdout);
      fgets((char*)&buffer, MAX_BUFFER, stdin);
      messageSize = strlen(buffer);
      sctp_sendmsg(sock, (void*) buffer, messageSize,
            &addr, addrLength,
            0, 0,
            STREAM_NUM, 0,
            0);

      int flags;
      sctp_recvmsg(sock, (void*) buffer, messageSize,
            &addr, &addrLength,
            &sinfo, &flags); 
      buffer[MAX_BUFFER] = 0;
      printf(buffer);
   }

   close(sock);

   return 0;
}
