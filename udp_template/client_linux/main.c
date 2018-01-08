#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>

char msg1[] = "Hello there!\n";
char msg2[] = "Bye bye!\n";

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[256];
    uint16_t portno;
    struct hostent *server;

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    portno = (uint16_t) atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        perror("socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    printf("\nPlease enter the message: ");
    /* Clear buffer */
    bzero(buffer, 256);

    /* Read to buffer from stdin */
    fgets(buffer, 255, stdin);

    if (buffer == (char *) 'end') {
        printf("\nExit");
        shutdown(sockfd, 2);
        return 0;
    }

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    send(sockfd, buffer, sizeof(buffer), 0);

    close(sockfd);

    return 0;
}