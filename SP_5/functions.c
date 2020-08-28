/*! \file
 *  \brief   Файл с функциями.
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BIT_SHIFT 2

#define COUNT_OF_NUMBERS 2

#define LOCAL_ERROR -1

#define NUMBER_ERROR -322

#define NEGATIVE -1

#define ORDER 10

#define ASCII_CONST 48

 int Checker(char* tempForCheck)
{
    int number = 0;
    int flag = 0;

    for (unsigned int i = 0; i < strlen(tempForCheck); i++)
    {
        if (i == 0 && tempForCheck[0] == '-')
        {
            flag++;
            continue;
        }

        if (tempForCheck[i] == '0' || tempForCheck[i] == '1' || tempForCheck[i] == '2' || tempForCheck[i] == '3' ||
           tempForCheck[i] == '4' || tempForCheck[i] == '5' || tempForCheck[i] == '6' ||
           tempForCheck[i] == '7' || tempForCheck[i] == '8' || tempForCheck[i] == '9') number = number * ORDER +
                                                                                                (tempForCheck[i] - ASCII_CONST);
        else
            return NUMBER_ERROR;
    }

    if (flag > 0) number *= NEGATIVE;

    return number;
}

int AriShift(int tempA, int tempB)
{
    int temp = 1;

    if (tempB >= 0)
    {
        while (1)
        {
            if (temp <= tempA) temp *= BIT_SHIFT;
            else
                break;
        }

        temp /= BIT_SHIFT;

        return (tempA >> tempB) + temp;
    } else
    {
        tempB *= LOCAL_ERROR;
        return tempA << tempB;
    }
}

int CycleShift(int tempA, int tempB)
{
    int temp = 1;

    if(tempB >= 0)
    {

        while (1)
        {
            if (temp <= tempA) temp *= BIT_SHIFT;
            else
                break;
        }

        temp /= BIT_SHIFT;

        if (tempA % BIT_SHIFT == 0)
            return tempA >> tempB;
        else
            return (tempA >> tempB) + temp;
    } else
    {
        tempB *= LOCAL_ERROR;
        return (tempA << tempB) + 1;
    }
}

int* CheckMessageFunction(int length, char* text)
{
    int flag = 0;
    int position = 0;
    char str1[100];
    char str2[100];

    for (int i = 0; i < length; i++)
    {
        if (text[i] == ' ')
        {
            str1[i] = '\0';
            flag++;
            continue;
        }

        if (flag == 0)
            str1[i] = text[i];

        if (flag == 1)
        {
            str2[position] = text[i];
            position++;
        }
    }

    int number1 = Checker(str1);
    int number2 = Checker(str2);
    int *result = (int*) malloc(sizeof (int) * COUNT_OF_NUMBERS);

    if (number1 == NUMBER_ERROR || number2 == NUMBER_ERROR)
    {
        result[0] = NUMBER_ERROR;
        return result;
    }

    result[0] = number1;
    result[1] = number2;

    return result;
}
