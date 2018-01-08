#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include "server.h"


#define PORT_NUMBER 8080;

char buffer[500];


int main(int argc, char *argv[]) {

    init();

    uint16_t port_no = PORT_NUMBER;

    int serverfd, newsockfd;
    unsigned int client;
    struct sockaddr_in serv_addr, cli_addr;
    ssize_t n;


//    serverfd = socket(AF_INET, SOCK_STREAM, 0);

////    if (serverfd < 0) {
////        perror("ERROR opening socket");
////        exit(1);
////    }
//
//    /* Initialize socket structure */
//    bzero((char *) &serv_addr, sizeof(serv_addr));
//
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_addr.s_addr = INADDR_ANY;
//    serv_addr.sin_port = htons(port_no);
//
//    /* Now bind the host address using bind() call.*/
//    if (bind(serverfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
//        perror("ERROR on binding");
//        exit(1);
//    }

    printf("server start\n");

    printf(showHelp());
    printf("\n");
    printf(showAll());

    printf("\n== add ==\n");
    bzero(buffer, 256);
    strcpy(buffer, "add ca=USA,cy=Kalifornia,co=Google,em=Sergey Brin");
    printf(add(buffer));
    printf("\n");
    printf(showAll());

    printf("\n== fnd ==\n");
    bzero(buffer, 256);
    strcpy(buffer, "co=Google");
    printf(find(buffer));

    printf("\n== del ==\n");
    bzero(buffer, 256);
    strcpy(buffer, "ca=RUSSIA,cy=Saint-Petersburg,co=SPbSTU,em=Aleksyuk Artyom");
    printf(delete(buffer));
    printf("\n");
    printf(showAll());


    return 0;

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */
    for (;;) {
        listen(serverfd, 5);
        client = sizeof(cli_addr);

        /* Accept actual connection from the client */
        newsockfd = accept(serverfd, (struct sockaddr *) &cli_addr, &client);

        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }

        /* If connection is established then start communicating */
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255); // recv

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        if (strcmp(buffer, "help\n") == 0) {
            if (write(newsockfd, showHelp(), 376) < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
            close(newsockfd);
            continue;
        }

        if (strcmp(buffer, "all\n") == 0) {
            if (write(newsockfd, showAll(), 500) < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
            close(newsockfd);
            continue;
        }

        if (strncmp(buffer, "add", 3) == 0) {
            if (write(newsockfd, add(buffer), 500) < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
            close(newsockfd);
            continue;
        }

        if (strncmp(buffer, "del", 3) == 0) {
            if (write(newsockfd, delete(buffer), 500) < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
            close(newsockfd);
            continue;
        }

        if (strncmp(buffer, "fnd", 3) == 0) {
            if (write(newsockfd, find(buffer + 4), 500) < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
            close(newsockfd);
            continue;
        }

        printf("Here is the message: %s\n", buffer);

        /* Write a response to the client */
        n = write(newsockfd, "Command not found, try help for info", 36);

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
        close(newsockfd);
    }
}

