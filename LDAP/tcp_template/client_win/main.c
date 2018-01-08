#include <stdio.h>

//#include <netdb.h>
#include <unistd.h>

#include <windows.h>
#include <conio.h>
#include <tchar.h>
#include <stdint.h>

//#pragma comment (lib, "ws2_32.lib")
//#pragma comment (lib, "mswsock.lib")

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

int SendBytes(SOCKET socket, char *message) {
    int n = send(socket, message, (int) strlen(message), 0); // send on Windows
    if (n < 0) {
        perror("ERROR writing to socket");
        return -1;
    }
    return n;
}

char *ReadBytes(SOCKET socket, char *buffer) {
    int n = recv(socket, buffer, 512, 0); // send on Windows
    if (n < 0) {
        perror("ERROR writing to socket");
        return (char *) -1;
    }
    return (char *) n;
}


SOCKET Init(int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET csocket;
    struct sockaddr_in server;

    if (WSAStartup(0x0202, &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 0;
    }
    //Create a socket
    if ((csocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        return 0;
    }

    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons((UINT16) atoi(argv[2]));

    //Connect to remote server
    if (connect(csocket, (struct sockaddr *) &server, sizeof(server)) < 0) {
        return 0;
    }
    return csocket;
}

int main(int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET csocket;
    char buffer[255];
    struct sockaddr_in server;

    if (WSAStartup(0x0202, &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 0;
    }
    //Create a socket
    if ((csocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        return 0;
    }

    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons((UINT16) atoi(argv[2]));

    //Connect to remote server
    if ((csocket = Init(argc, argv)) < 1) {
        printf("Connection error\n");
        return -1;
    } else {
        printf("Connected\n");
        for (;;) {
            printf("Please enter your message : ");
            memset(buffer, 0, 256);
            fgets(buffer, 255, stdin);
            SendBytes(csocket, buffer);

            memset(buffer, 0, 256);
            ReadBytes(csocket, buffer);


            printf("%s\n", buffer);
        }

    }
    return 1;
}

#pragma clang diagnostic pop