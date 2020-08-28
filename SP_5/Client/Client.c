/*! \file
 *  \brief   Файл с описанием функций сетевой части клиента.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "OutFuncs.h"

#define UNIQUE_PORT 23456

#define TWO_EIGHT 256

#define LOCALHOST "127.0.0.1"

#define COUNT_OF_INPUT_ARGS 2

#define LOCAL_ERROR -1

#define ERROR_COUNT_OF_AGRS "В качестве входного аргумента необходимо указать IP сервера, установлен адрес \"127.0.0.1\"\n"

#define SOCKET_ERROR "socket"

#define INET_ADDR_ERROR "inet_addr"

#define LAST_ONE_OF_STRING 1

#define INFINITY_LOOP for(;;)

#define SUCCESS 0

int client(int argc, const char** argv)
{

    int socketDescriptor;
    int portNumber = UNIQUE_PORT;

    struct sockaddr_in name;

    name.sin_family = AF_INET;
    if (argv[1] != NULL)
        name.sin_addr.s_addr = inet_addr(argv[1]);

    if (argc != COUNT_OF_INPUT_ARGS)
    {
        printf(ERROR_COUNT_OF_AGRS);
        name.sin_addr.s_addr = inet_addr(LOCALHOST);
    }

    if (INADDR_NONE == name.sin_addr.s_addr)
    {
        perror(INET_ADDR_ERROR);
        return LOCAL_ERROR;
    }
    name.sin_port = htons((u_short) portNumber);

    socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (0 > socketDescriptor)
    {
        perror(SOCKET_ERROR);
        return LOCAL_ERROR;
    }

    char message[TWO_EIGHT];

    int resSend = 0;
    int length = 0;

    INFINITY_LOOP
    {
        message[0] = '\0';

        OutInfoClient();

        fgets(message, TWO_EIGHT, stdin);

        message[strlen(message) - LAST_ONE_OF_STRING] = 0;

        length = strlen(message) + LAST_ONE_OF_STRING;
        resSend = sendto(socketDescriptor, &length, sizeof(length), 0,
                         (struct sockaddr *) &name, sizeof(name));
        if (0 > resSend) {
            perror("sendto");
            return LOCAL_ERROR;
        }

        resSend = sendto(socketDescriptor, message, length, 0,
                         (struct sockaddr *) &name, sizeof(name));
        if (0 > resSend) {
            perror("sendto");
        }

        if (0 == strcmp(message, "-1 -1"))
            break;

        resSend = 0;
    }

    close(socketDescriptor);

    return SUCCESS;
}
