#include <stdio.h>
#include <stdlib.h>
#include "server.h"

#define MAX_CLIENTS 5

int nextUser;
argsT args;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        return -1;
    }

    init();

    WSADATA wsa;
    SOCKET serverSocket, accSocket;
    struct sockaddr_in server, client;

    if (WSAStartup(0x0202, &wsa) != 0) {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons((UINT16) atoi(argv[1]));

    //Bind
    if (bind(serverSocket, (SOCKADDR *) &server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d", WSAGetLastError());
    }

    //Listen to incoming connections
    listen(serverSocket, MAX_CLIENTS);

    //Initialize socket structure
    printf("server start\n");

    int client_length = sizeof(struct sockaddr_in);

    char buffer[256];
    while ((accSocket = accept(serverSocket, (SOCKADDR *) &client, &client_length))) {

        args.ip = inet_ntoa(client.sin_addr);
        args.port = ntohs(client.sin_port);
        args.socket = (int) accSocket;
        HANDLE thread = CreateThread(NULL, 0, ConnectionHandler, &args, 0, NULL);

        printf("New connection\nThread created for: %s; on Port: %d,socket :[%d]\n", inet_ntoa(client.sin_addr),
               ntohs(client.sin_port), (int) accSocket);
    }

    if (accSocket < 0) {
        perror("accept failed");
        return 1;
    }

    closesocket(serverSocket);
    WSACleanup();
}