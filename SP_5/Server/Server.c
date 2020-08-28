/*! \file
 *  \brief   Файл с описанием функций сетевой части сервера.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#include "../functions.h"
#include "OutFuncs.h"

#define INFINITY_LOOP for(;;)

#define SUCCESS 0

#define NULL_ERROR NULL

#define LOCAL_ERROR -1

#define ERROR_OF_INPUT "Введены некорректные входные данные!\n"

#define NUMBER_ERROR -322

#define TWO_EIGHT 256

int* acceptArgs(int serverSocket)
{
    int *numbers = NULL;
    int length = 0;
    char* text = NULL;

    text = (char*) malloc(length);
    memset(text, 0, length);

    struct sockaddr_in clientName;
    int clientNameLength = sizeof (clientName);

    int recvResult = recvfrom(serverSocket, (char*) &length, sizeof (length), 0,
                              (struct sockaddr *) &clientName,
                              &clientNameLength);

    if (LOCAL_ERROR == recvResult)
    {
        perror("recvfrom");
    }
    if (0 >= recvResult)
    {
        return NULL_ERROR;
    }

    recvResult = recvfrom(serverSocket, text, length, 0,
                          (struct sockaddr *)&clientName,
                          &clientNameLength);
    if (LOCAL_ERROR == recvResult)
    {
        perror("recvfrom");
    }
    if (0 >= recvResult)
    {
        return NULL_ERROR;
    }

    PrintInput(text);

    numbers = CheckMessageFunction(length, text);

    int number1 = numbers[0];
    int number2 = numbers[1];
    free(text);

    if (number1 == NUMBER_ERROR || number2 == NUMBER_ERROR)
    {
        printf(ERROR_OF_INPUT);
        return NULL_ERROR;
    }

    return numbers;
}
