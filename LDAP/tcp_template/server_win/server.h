//
// Created by Kirill Polyakov on 19.11.17.
//
#ifndef NETWORKSLAB2017_SERVER_H
#define NETWORKSLAB2017_SERVER_H

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAXCLIENTS      5
#define BUFFLEN         512

struct user {
    SOCKET socket;


};
typedef struct argsTag {
    SOCKET socket;
    char *ip;
    int port;
} argsT;

struct user users[MAXCLIENTS];

argsT args;
int usersOnline;

int nextUser;

DWORD WINAPI ConnectionHandler(void *args);

void init(void);

char *showHelp(void);

int isValid(char *query);

char *find(char *query);

char *showAll(void);

char *delete(char *query);

char *add(char *query);

#endif //NETWORKSLAB2017_SERVER_H
