#include  "udpinclude.h"

#define DATA "the tide is full, the moon lies fair"

int main(){
  int sock, length;
  struct sockaddr_in server, client;
  char buf[1024];
 
  /* Create socket from which to read. */

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("opening datagram socket");
    exit(1);
  }
  /* Create server with wildcards. */
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 0;

  if (bind(sock, (struct sockaddr*)&server, sizeof(server))) {
    perror("binding datagram socket");
    exit(1);
  }

  /* Find assigned port value and print it out. */
  length = sizeof(server);
  if (getsockname(sock, (struct sockaddr*)&server, &length)) {
    perror("getting socket server");
    exit(1);
  }

  int num;
  fprintf(stderr,"Socket has port #%d\n", ntohs(server.sin_port));
  
  while(atoi(buf) < 100){
  /* Read from the socket */
  length = sizeof(client);
  if (recvfrom(sock, buf, 1024, 0, (struct sockaddr*)&client, &length) < 0){
    perror("receiving datagram packet");
  }
  num = atoi(buf);
  printf("Client says: -->%d\n", num);
  num++;
  sprintf(buf, "%d", num);
  if (sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&client, sizeof(client)) < 0){
      perror("sending datagram message");
  }
  }

  close(sock);
}
