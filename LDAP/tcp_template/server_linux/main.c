#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#define PORT_NUMBER 8080;


char countries[5][200];
char cities[1000][200];
char companies[1000][500];
char employees[10000][200];
int cities_count = 0, companies_count = 0, workers_count = 0;

char *showHelp(void) {
    return "Hello! \n"
            "You went to a free resource with employees of companies from different countries.\n"
            "This is the educational project by Polyakov Kirill\n"
            "Commands:\n"
            "\thelp - show this message\n"
            "\tadd - add new employee/company/city\n"
            "\tdel - delete one of employee/company/city\n"
            "\tfnd -  search by employee/company/city/country\n"
            "\n"
            "Example of command:\n"
            "\tadd em=Sergey Brin,co=Google,cy=Kalifornia,ca=US";
}

char buffer[500];
char method_buffer[500];

char *showFull(void) {
    bzero(method_buffer, 500);
    for (int i = 0; i < cities_count; ++i) {
        strcat(method_buffer, "c=");
        strcat(method_buffer, &countries[i]);
        strcat(method_buffer, "; ");
    }
    return method_buffer;
}

char *add(char *query) {
    bzero(method_buffer, 500);
    if (isValid(query) < 0) {
        strcat(method_buffer, "add method: ");
        strcat(method_buffer, query);
    } else {
        strcat(method_buffer, "Syntax error");
        return method_buffer;
    }
    return method_buffer;
}

char *delete(char *query) {
    bzero(method_buffer, 500);
    if (isValid(query) > 0) {
        strcat(method_buffer, "delete method: ");
        strcat(method_buffer, query);
    } else {
        strcat(method_buffer, "Syntax error");
        return method_buffer;
    }

    return method_buffer;
}

char *find(char *query) {
    bzero(method_buffer, 500);
    if (isValid(query) > 0) {
        strcat(method_buffer, "find method: ");
        strcat(method_buffer, query);
        return method_buffer;
    } else {
        strcat(method_buffer, "Syntax error");
        return method_buffer;
    }
}

int isValid(char *query) {
    return 1;
}


void init() {
    strcpy(countries[0], "RUSSIA");
    strcpy(countries[1], "USA");
    strcpy(countries[2], "FRANCE");
    strcpy(countries[3], "BELARUS");
    strcpy(countries[4], "GERMANY");

    strcpy(cities[0], "0MOSCOW");
    strcpy(cities[1], "0SAINT-PETERSBURG");
    strcpy(cities[2], "1BOSTON");

    strcpy(companies[0], "0GOOGLE");
    strcpy(companies[1], "1SPBSTU");
    strcpy(companies[2], "2BOSTON-DYNAMICS");

    strcpy(employees[0], "1artyom.aleksyuk");
    strcpy(employees[1], "1itsykson.vladimir");

    cities_count = 5;
    companies_count = 3;
    workers_count = 2;
}

int main(int argc, char *argv[]) {

    init();
    uint16_t port_no = PORT_NUMBER;

    int serverfd, newsockfd;
    unsigned int client;
    struct sockaddr_in serv_addr, cli_addr;
    ssize_t n;


    serverfd = socket(AF_INET, SOCK_STREAM, 0);

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

        if (strcmp(buffer, "show\n") == 0) {
            if (write(newsockfd, showFull(), 500) < 0) {
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
            if (write(newsockfd, find(buffer), 500) < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
            close(newsockfd);
            continue;
        }

        printf("Here is the message: %s\n", buffer);

        /* Write a response to the client */
        n = write(newsockfd, "I got your message", 18);

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
        close(newsockfd);
    }
}

