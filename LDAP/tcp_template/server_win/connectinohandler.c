#include <io.h>
#include <pthread.h>
#include "server.h"

pthread_mutex_t mutex;

char *ReadBytes(SOCKET socket, char *answer) {
    int n = recv(socket, answer, BUFFLEN, 0);
    if (n < 0)
        printf("Reading ERROR for function ReadBytes\n");
    return answer;
}

int SendBytes(SOCKET socket, char *message) {
    int n = send(socket, message, (int) strlen(message), 0);
    if (n < 0) {
        perror("1ERROR writing to socket");
        return -1;
    }
    return n;
}



DWORD WINAPI ConnectionHandler(void *args) {
    pthread_mutex_init(&mutex, NULL);
    argsT *arg = (argsT *) args;

    //Get the socket descriptor
    int userId = nextUser;

    users[userId].socket = arg->socket;

    int n = 0;

    nextUser++;
    for (;;) {
        char buffer[BUFFLEN];

        n = (int) ReadBytes(users[userId].socket, buffer);

        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        if (strcmp(buffer, "help\n") == 0) {
            strcpy(buffer, showHelp());

            if (SendBytes(users[userId].socket, buffer) < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
            close((int) users[userId].socket);
            memset(buffer, 0, BUFFLEN);
            continue;
        }

        if (strcmp(buffer, "all\n") == 0) {
            strcpy(buffer, showAll());

            if (SendBytes(users[userId].socket, buffer) < 0) {
                perror("ERROR writin1g to socket");
                exit(1);
            }
            close((int) users[userId].socket);
            memset(buffer, 0, BUFFLEN);
            continue;
        }

        if (strncmp(buffer, "add", 3) == 0) {
            strcpy(buffer, add(buffer));

            if (SendBytes(users[userId].socket, buffer) < 0) {
                perror("1ERROR writing to socket");
                exit(1);
            }
            close((int) users[userId].socket);
            memset(buffer, 0, BUFFLEN);
            continue;
        }

        if (strncmp(buffer, "del", 3) == 0) {
            strcpy(buffer, delete(buffer));

            if (SendBytes(users[userId].socket, buffer) < 0) {
                perror("2ERROR writing to socket");
                exit(1);
            }
            close((int) users[userId].socket);
            memset(buffer, 0, BUFFLEN);
            continue;
        }

        if (strncmp(buffer, "fnd", 3) == 0) {
            strcpy(buffer, find(buffer + 1));

            if (SendBytes(users[userId].socket, buffer) < 0) {
                perror("3ERROR writing to socket");
                exit(1);
            }
            close((int) users[userId].socket);
            memset(buffer, 0, BUFFLEN);
            continue;
        }

        printf("Here is the message: %s\n", buffer);
        memset(buffer, 0, BUFFLEN);
        /* send a response to the client */
        if (SendBytes(users[userId].socket, "Command not found, try help for info") < 0) {
            perror("4ERROR writing to socket");
            exit(1);
        }
    }
}
