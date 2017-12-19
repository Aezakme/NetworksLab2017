#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>

#include <string.h>

int main(int argc, char *argv[]) {
    int sockfd, n;
    uint16_t portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[500];

    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }



    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    portno = (uint16_t) atoi(argv[2]);

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    bcopy(server->h_addr, (char *) &serv_addr.sin_addr.s_addr, (size_t) server->h_length);

    for (;;) {

        /* Create a socket point */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }



        /* Now connect to the server */

        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
            perror("ERROR connecting");
            exit(1);
        }

        /* Now ask for a message from the user, this message
         * will be read by server
         */

        printf("\nPlease enter the message: ");
        /* Clear buffer */
        bzero(buffer, 500);

        /* Read to buffer from stdin */
        fgets(buffer, 500, stdin);

        if (buffer == (char *) 'end') {
            printf("\nExit");
            shutdown(sockfd, 2);
            return 0;
        }

        /* Send message to the server */
        n = (int) write(sockfd, buffer, strlen(buffer));

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

        /* Now read server response */
        bzero(buffer, 500);
        n = (int) read(sockfd, buffer, 500);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        printf("%s\n", buffer);

        shutdown(sockfd, 2);
    }
}