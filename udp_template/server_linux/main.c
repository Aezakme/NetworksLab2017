#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define PORT_NUMBER 8080;

int main() {
    uint16_t port_no = PORT_NUMBER;
    int serverfd;
    struct sockaddr_in serv_addr;
    char buffer[1024];
    int bytes_read;

    serverfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (serverfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port_no);

    /* Now bind the host address using bind() call.*/
    if (bind(serverfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    for (;;) {
        bytes_read = (int) recvfrom(serverfd, buffer, 1024, 0, NULL, NULL);
        buffer[bytes_read] = '\0';
        printf("Here is the message: %s\n", buffer);
    }

    return 0;
}