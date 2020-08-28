/*! \file
 *  \brief   Файл с описанием функций вывода для сервера.
 */
#include "../functions.h"

#include <stdio.h>

void OutInfoServer(int number1, int number2)
{
    printf("Результат арифметического сдвига: %d;\nРезультат "
           "циклическогосдвига: %d .\n\n", AriShift(number1, number2),
           CycleShift(number1, number2));
}

void PrintInput(char* text)
{
    printf("Входные данные: %s\n", text);
}
