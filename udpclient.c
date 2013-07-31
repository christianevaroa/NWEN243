#include "udpinclude.h"

#define DATA "1"

int main(argc, argv) int argc; char *argv[];{
    int sock;
    struct sockaddr_in server;
    struct hostent *hp, *gethostbyname();
    char buf[1024];

    if(argc != 3){
      printf("usage:\nudpclient hostname port\n\n");
      exit(3);
    }

    /* Create socket on which to send. */
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("opening datagram socket");  exit(1); }
    
    hp = gethostbyname(argv[1]);
    if (hp == 0) {
	fprintf(stderr, "%s: unknown host\n", argv[1]);  exit(2);
    }
    bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    
    srand( 50 );
    int num = 0;
    sprintf(buf, "%d", rand);

    while(num < 100){
    /* Send message. */
    num++;
    sprintf(buf, "%d", num);
    if (sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&server, sizeof(server)) < 0){
      perror("sending datagram message");
    }
    if (recv(sock, buf, 1024, sizeof(buf)) < 0){
      perror("receiving datagram packet");
    }
    num = atoi(buf);
    printf("server says: -->%d\n", num);
    }
    close(sock);
}
