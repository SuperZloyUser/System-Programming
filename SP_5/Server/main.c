/*! \file
 *  \brief   Основной файл сервера.
 */
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "Server.h"
#include "OutFuncs.h"

#define INFINITY_LOOP for(;;)

#define COUNT_OF_INPUT_ARGS 2

#define NULL_ERROR NULL

#define ERROR_COUNT_OF_AGRS "В качестве входного аргумента необходимо указать IP клиента, установлен адрес \"127.0.0.1\"\n"

#define LOCALHOST "127.0.0.1"

#define UNIQUE_PORT 23456

#define LOCAL_ERROR -1

#define SUCCESS 0

#define EXIT_NUMBER -1

#define EXIT "Выход."

#define EXIT_MESSAGE EXIT

#define TWO_EIGHT 256

#define INITIALISATION_MESSAGE "Initialising Winsock...\n"

#define ERROR_FIRST_ARG_MESSAGE "Первое число не должно быть отрицательным!\n"

/*! \brief Главная функция серверной части.
 *
 *  \param argc Число входных аргуметов.
 *  \param argv Сами аргументы.
 *
 *  \details В качестве входных аргументов необходимо ввести ip-адрес клиента,
 *  в случае отсутствия или некорректности входных параметров будет установлен
 *  локальный ip-адрес "127.0.0.1"
 */
int main(int argc, const char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Подготовка сокета для работы.
    SOCKET socketDescriptor;
    struct sockaddr_in server, si_other;
    WSADATA wsa;

    //Initialise winsock
    printf(INITIALISATION_MESSAGE);
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d\n" ,WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    //Create a socket
    if((socketDescriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d\n" , WSAGetLastError());
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    if (argc != COUNT_OF_INPUT_ARGS)
    {
        printf(ERROR_COUNT_OF_AGRS);
        server.sin_addr.s_addr = inet_addr(LOCALHOST);
    }
    server.sin_port = htons(UNIQUE_PORT);

    //Bind
    if(bind(socketDescriptor , (struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        closesocket(socketDescriptor);
        exit(EXIT_FAILURE);
    }
    puts("Bind done");

    int number1 = 0;
    int number2 = 0;
    int* clientSentQuitMessage;

    INFINITY_LOOP
    {
        clientSentQuitMessage = acceptArgs(socketDescriptor);
        if (clientSentQuitMessage == NULL)
            continue;

        number1 = clientSentQuitMessage[0];
        number2 = clientSentQuitMessage[1];
        free(clientSentQuitMessage);

        if (number1 == EXIT_NUMBER && number2 == EXIT_NUMBER)
        {
            printf(EXIT_MESSAGE);
            return SUCCESS;
        }

        if (number1 < 0)
        {
            printf(ERROR_FIRST_ARG_MESSAGE);
            continue;
        }

        OutInfoServer(number1, number2);
    }

    closesocket(socketDescriptor);

    return SUCCESS;
}
