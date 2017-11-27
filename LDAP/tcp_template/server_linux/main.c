#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#define PORT_NUMBER 8080;

char buffer[500];
char method_buffer[500];

char countries[5][20];
char cities[1000][256];
char companies[1000][256];
char employees[10000][256];

int countries_count = 0, cities_count = 0, companies_count = 0, workers_count = 0;

void init() {
    strcpy(countries[0], "RUSSIA");
    strcpy(countries[1], "USA");
    strcpy(countries[2], "FRANCE");
    strcpy(countries[3], "BELARUS");
    strcpy(countries[4], "GERMANY");

    strcpy(cities[0], "0Moscow");
    strcpy(cities[1], "0Saint-Petersburg");
    strcpy(cities[2], "1Boston");

    strcpy(companies[0], "0Google");
    strcpy(companies[1], "1SPbSTU");
    strcpy(companies[2], "2Boston-dynamics");

    strcpy(employees[0], "0Aleksyuk Artyom");
    strcpy(employees[1], "1Aleksyuk Artyom");
    strcpy(employees[2], "1Itsykson Vladimir");

    countries_count = 5;
    cities_count = 3;
    companies_count = 3;
    workers_count = 3;
}

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
            "\tadd ca=USA"
            ",cy=Kalifornia,co=Google,em=Sergey Brin";
}

char *find(char *query) {
    char type[3] = "";
    char search_query[256] = "";
    bzero(method_buffer, 500);
    strcat(query, "\n");
    strncpy(type, query, strstr(query, "=") - query);
    query += 3;
    strncpy(search_query, query, strstr(query, "\n") - query);

    if (strncmp(type, "ca", 2) == 0) {
        for (int i = 0; i < countries_count; ++i) {
            if (strcmp(countries[i], search_query) == 0) {
                strcat(method_buffer, "ca=");
                strcat(method_buffer, countries[i]);
                return method_buffer;
            }
        }
    }

    if (strncmp(type, "cy", 2) == 0) {
        for (int i = 0; i < cities_count; ++i) {
            if (strcmp(cities[i] + 1, search_query) == 0) {
                strcat(method_buffer, "ca=");
                strcat(method_buffer, countries[(int) cities[i][0] - '0']);
                strcat(method_buffer, ",cy=");
                strcat(method_buffer, cities[i] + 1);
                strcat(method_buffer, "\n");
            }
        }
    }

    if (strncmp(type, "co", 2) == 0) {
        for (int i = 0; i < companies_count; ++i) {
            if (strcmp(companies[i] + 1, search_query) == 0) {
                strcat(method_buffer, "ca=");
                strcat(method_buffer, countries[(int) cities[(int) companies[i][0] - '0'][0] - '0']);
                strcat(method_buffer, ",cy=");
                strcat(method_buffer, cities[(int) companies[i][0] - '0'] + 1);
                strcat(method_buffer, ",co=");
                strcat(method_buffer, companies[i] + 1);
                strcat(method_buffer, "\n");
            }
        }
    }

    if (strncmp(type, "em", 2) == 0) {
        for (int i = 0; i < workers_count; ++i) {
            if (strcmp(employees[i] + 1, search_query) == 0) {
                strcat(method_buffer, "ca=");
                strcat(method_buffer,
                       countries[(int) cities[(int) companies[(int) employees[i][0] - '0'][0] - '0'][0] - '0']);
                strcat(method_buffer, ",cy=");
                strcat(method_buffer, cities[(int) companies[(int) employees[i][0] - '0'][0] - '0'] + 1);
                strcat(method_buffer, ",co=");
                strcat(method_buffer, companies[(int) employees[i][0] - '0'] + 1);
                strcat(method_buffer, ",em=");
                strcat(method_buffer, employees[i] + 1);
                strcat(method_buffer, "\n");
            }
        }
    }
    strcat(method_buffer, " ");
    return method_buffer;

}

char *showAll(void) {
    bzero(method_buffer, 500);
    for (int i = 0; i < workers_count; ++i) {
        strcat(method_buffer, "ca=");
        strcat(method_buffer,
               countries[(int) cities[(int) companies[(int) employees[i][0] - '0'][0] - '0'][0] - '0']);
        strcat(method_buffer, ",cy=");
        strcat(method_buffer, cities[(int) companies[(int) employees[i][0] - '0'][0] - '0'] + 1);
        strcat(method_buffer, ",co=");
        strcat(method_buffer, companies[(int) employees[i][0] - '0'] + 1);
        strcat(method_buffer, ",em=");
        strcat(method_buffer, employees[i] + 1);
        strcat(method_buffer, "\n");

    }
    return method_buffer;
}

int indexFind(char *query) {
    char type[3] = "";
    char search_query[256] = "";
    bzero(method_buffer, 500);
    strcat(query, "\n");
    strncpy(type, query, strstr(query, "=") - query);
    query += 3;
    strncpy(search_query, query, strstr(query, "\n") - query);

    if (strncmp(type, "ca", 2) == 0) {
        for (int i = 0; i < countries_count; ++i) {
            if (strcmp(countries[i], search_query) == 0) {
                return i;
            }
        }
    }

    if (strncmp(type, "cy", 2) == 0) {
        for (int i = 0; i < cities_count; ++i) {
            if (strcmp(cities[i], search_query) == 0) {
                return i;
            }
        }
    }

    if (strncmp(type, "co", 2) == 0) {
        for (int i = 0; i < companies_count; ++i) {
            if (strcmp(companies[i], search_query) == 0) {
                return i;
            }
        }
    }

    if (strncmp(type, "em", 2) == 0) {
        for (int i = 0; i < workers_count; ++i) {
            if (strcmp(employees[i], search_query) == 0) {
                return i;
            }
        }
    }
    return -1;

}

char *add(char *query) {
    strcat(query, "\n");
    bzero(method_buffer, 500);
    strcat(method_buffer, query);
    char temp[256] = "";
    char name[256] = "";
    int index = -1;
    if (isValid(query) == 1) {
        query += 4;
        strncpy(temp, query, strstr(query, ",") - query);
        int search_index = indexFind(temp);
        if (search_index == -1) {
            strcat(method_buffer, "Country not found");
            return method_buffer;
        }
        index = search_index;

        query = strstr(query, ",") + 1;
        strncpy(temp, query, strstr(query, ",") - query);
        sprintf(name, "cy=%d%s", index, temp + 3);
        search_index = indexFind(name);
        if (search_index == -1) {
            strncpy(temp, name, strstr(name, "\n") - name);
            strcpy(cities[cities_count], temp + 3);
            index = cities_count;
            cities_count++;
        } else {
            index = search_index;
        }

        query = strstr(query, ",") + 1;
        bzero(temp, 256);
        strncpy(temp, query, strstr(query, ",") - query);
        sprintf(name, "co=%d%s", index, temp + 3);
        search_index = indexFind(name);
        if (search_index == -1) {
            strncpy(temp, name, strstr(name, "\n") - name);
            strcpy(companies[companies_count], temp + 3);
            index = companies_count;
            companies_count++;
        } else {
            index = search_index;
        }

        query = strstr(query, ",") + 1;
        bzero(temp, 256);
        strncpy(temp, query, strstr(query, "\n") - query);
        sprintf(name, "em=%d%s", index, temp + 3);
        search_index = indexFind(name);
        if (search_index == -1) {
            strncpy(temp, name, strstr(name, "\n") - name);
            strcpy(employees[workers_count], temp + 3);
            workers_count++;
        } else {
            return "All ready exists";
        }

        return "Done";

    } else {
        strcat(method_buffer, "Syntax error");
        return method_buffer;
    }
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

int isValid(char *query) {
    int counter = 0;
    counter += strncmp(query += 4, "ca=", 3);
    counter += strncmp(query = strstr(query, ",") + 1, "cy=", 3);
    counter += strncmp(query = strstr(query, ",") + 1, "co=", 3);
    counter += strncmp(query = strstr(query, ",") + 1, "em=", 3);

    if ((strstr(query, ",") != NULL) || (counter < 0)) {
        return -1;
    }

    return 1;
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

    printf("server start\n");

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

