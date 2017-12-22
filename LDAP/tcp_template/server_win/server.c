//
// Created by Kirill Polyakov on 19.11.17.
//

//#include <string.h>
#include <stdio.h>
#include <strings.h>


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-conversion"
char method_buffer[500];
char countries[5][20];
char cities[1000][256];
char companies[1000][256];
char employees[10000][256];

int countries_count = 0, cities_count = 0, companies_count = 0, workers_count = 0;

void init(void) {
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
            "\tadd ca=USA,cy=Kalifornia,co=Google,em=Sergey Brin";
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


char *find(char *query) {
    char type[3] = "";
    char search_query[256] = "";
    memset(method_buffer, 0, 500);
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
//    bzero(method_buffer, 500);
    memset(method_buffer, 0, 500);
    for (int i = 0; i < workers_count; ++i) {
        if (strncmp(employees[i], "d", 1) != 0) {
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
    return method_buffer;
}

int indexFind(char *query) {
    char type[3] = "";
    char search_query[256] = "";
//    bzero(method_buffer, 500);
    memset(method_buffer, 0, 500);
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

char *delete(char *query) {
//    bzero(method_buffer, 500);
    memset(method_buffer, 0, 500);
    strcat(query, "\n");
    if (strncmp(find(query), " ", 1) != 0) {
        query += 3;
        int counter = 0;
        for (unsigned int i = 0; i < sizeof(query); ++i) {
            if (query[i] == ',') {
                counter++;
            }
        }
        if (counter == 0) {
            return "can't delete Country";
        }
        int index = 0;
        char temp[256] = "";
        if (counter == 1) {
            strncpy(temp, query, strstr(query, ",") - query);
            strncpy(temp, query, strstr(query, "\n") - query);
            index = indexFind(temp);

            for (int i = 0; i < companies_count; ++i) {
                if (strncmp(companies[i], index, 1) == 0) {
                    for (int j = 0; j < workers_count; ++j) {
                        if (strncmp(employees[j], index, 1) == 0) {
                            strcpy(employees[j], strcat("d", employees[j] + 1));
                        }
                    }
                    strcpy(companies[i], strcat("d", companies[i] + 1));
                }
            }
            strcpy(cities[index], strcat("d", cities[index] + 1));

        } else if (counter == 2) {
            strncpy(temp, query, strstr(query, ",") - query);
            strncpy(temp, query, strstr(query, ",") - query);
            strncpy(temp, query, strstr(query, "\n") - query);
            index = indexFind(temp);
            for (int j = 0; j < workers_count; ++j) {
                if (strncmp(employees[j], index, 1) == 0) {
                    strcpy(employees[j], strcat("d", employees[j] + 1));
                }
            }
            strcpy(companies[index], strcat("d", companies[index] + 1));
        } else {
            strncpy(temp, query, strstr(query, ",") - query);
            strncpy(temp, query, strstr(query, ",") - query);
            strncpy(temp, query, strstr(query, ",") - query);
            strncpy(temp, query, strstr(query, "\n") - query);
            index = indexFind(temp);

            strcpy(employees[index], strcat("d", employees[index] + 1));

        }
    } else {
        return "Not found";
    }

    return "Done";
}

char *add(char *query) {
    strcat(query, "\n");
    memset(method_buffer, 0, 500);
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
        memset(temp, 0, 256);
//        bzero(temp, 256);
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
        memset(temp, 0, 500);
//        bzero(temp, 256);
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


#pragma clang diagnostic pop