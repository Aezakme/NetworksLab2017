//
// Created by Kirill Polyakov on 19.12.17.
//

#include <stdio.h>
//#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
//#include <windows.h>
#include <stdint.h>

#ifndef NETWORKSLAB2017_SERVER_H
#define NETWORKSLAB2017_SERVER_H

void init(void);

char *showHelp(void);

int isValid(char *query);

char *find(char *query);

char *showAll(void);

char *delete(char *query);

char *add(char *query);

#endif //NETWORKSLAB2017_SERVER_H
