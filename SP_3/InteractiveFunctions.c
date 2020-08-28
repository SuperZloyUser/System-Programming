#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"
#define MAX_LENGTH 50
#define ERROR -1
#define SUCCESS 0
#define ASCII_CONST 48
#define NEXT_DIGIT 10
#define INFINITY_LOOP for(;;)
#define CHANGE_NAME 1
#define CHANGE_COUNT_OF_TEACHERS 2
#define CHANGE_COUNT_OF_PROFESSORS 3
#define INFINITY 999999999

/*! \brief Функция, обрабатывающая ввод.
 *  @param parameters Строка считанная с клавиатуры.
 *  @return number Число, содержащееся в строке, либо ошибка.
 */
int InputChecker(char* strForCheck)
{
    int number = 0;

    for (unsigned long i = 0; i < strlen(strForCheck); i++)
    {
        if (strForCheck[i] == '0' || strForCheck[i] == '1' ||
            strForCheck[i] == '2' || strForCheck[i] == '3' ||
            strForCheck[i] == '4' || strForCheck[i] == '5' ||
            strForCheck[i] == '6' || strForCheck[i] == '7' ||
            strForCheck[i] == '8' || strForCheck[i] == '9') number =
                    number * NEXT_DIGIT + (strForCheck[i] - ASCII_CONST);
        else
            return ERROR;
    }

    return number;
}

/*! \brief Функция, обработки ввода-вывода для функции AddElement.
 *  @param mainStruct Ссылка на первый элемент структуры.
 */
void InteractiveForAddElement (struct department** mainStruct)
{

    char tString[MAX_LENGTH];
    printf("Введите название кафедры: ");
    scanf("%s", tString);

    int tCount = ERROR;
    int pCount = 0;
    char input[MAX_LENGTH];

    while (tCount < pCount)
    {
        printf("Введите количество учителей: ");
        INFINITY_LOOP {
            scanf("%s", input);
            tCount = InputChecker(input);
            if (tCount == ERROR)
                printf("Введены некорректные данные, исправьте, "
                       "пожалуйста: ");
            else break;
        }

        printf("Введите количество профессоров: ");
        INFINITY_LOOP {
            scanf("%s", input);
            pCount = InputChecker(input);
            if (pCount == ERROR)
                printf("Введены некорректные данные, исправьте, "
                       "пожалуйста: ");
            else break;
        }

        if (tCount < pCount) printf("Некорректные данные, "
                                    "повторите ввод!\n");
    }

    if (AddElement(mainStruct, tString, tCount, pCount) != SUCCESS)
        printf("Ошибка добавления элемента!\n");

}

/*! \brief Функция, обработки ввода-вывода для функции ModifyElement.
 *  @param mainStruct Ссылка на первый элемент структуры.
 */
void InteractiveForModifyElement(struct department** mainStruct)
{
    struct department* temp = *mainStruct;
    int tCount = 0;
    int flag = 0;
    char input[MAX_LENGTH];

    INFINITY_LOOP {

        if (flag == 1)
        {
            printf("Указанный элемент отсутствует!\n");
        }
        flag = 0;

        printf("Введите номер структуры, которую "
               "необходимо изменить: ");
        INFINITY_LOOP {
            scanf("%s", input);
            tCount = InputChecker(input);
            if (tCount == ERROR || tCount == 0)
                printf("Введены некорректные данные, исправьте, "
                       "пожалуйста: ");
            else break;
        }

        if (temp == NULL)
        {
            printf("Структура пуста!\n");
            return;
        }

        for (int i = 1; i < tCount; i++)
        {
            if (temp->next == NULL && i + 1 == tCount)
            {
                flag = 1;
                break;
            }
            temp = temp->next;
        }

        if (flag == 0) break;
    }

    INFINITY_LOOP
    {
        printf("Выберите поле, которое необходимо изменить:\n"
               "1 - Название кафедры;\n"
               "2 - Количество учителей на кафедре;\n"
               "3 - Количество профессоров на кафедре.\n");
        INFINITY_LOOP {
            scanf("%s", input);
            tCount = InputChecker(input);
            if (tCount < 1 || tCount > 3)
                printf("Введены некорректные данные, исправьте, "
                       "пожалуйста: ");
            else break;
        }

        if (tCount == CHANGE_NAME)
        {
            printf("Введите новое название кафедры: ");
            scanf("%s", input);
            void* par = (char*) malloc(sizeof(char) *
                    (strlen(input) + 1));
            strcpy(par, input);
            if (ModifyElement(&temp, 1, par) != SUCCESS)
                printf("Ошибка изменения имени!\n");
            return;
        }

        if (tCount == CHANGE_COUNT_OF_TEACHERS)
        {
            printf("Введите новое число учителей: ");
            INFINITY_LOOP {
                scanf("%s", input);
                tCount = InputChecker(input);
                if (tCount == ERROR)
                    printf("Введены некорректные данные, исправьте, "
                           "пожалуйста: ");
                else break;
            }

            void* par = malloc(sizeof(int));
            *(int*)par = tCount;
            if (ModifyElement(&temp, 2, par) != SUCCESS)
                printf("Ошибка изменения числа учителей!\n");

            return;
        }

        if (tCount == CHANGE_COUNT_OF_PROFESSORS)
        {
            printf("Введите новое число профессоров: ");
            INFINITY_LOOP {
                scanf("%s", input);
                tCount = InputChecker(input);
                if (tCount == ERROR)
                    printf("Введены некорректные данные, исправьте, "
                           "пожалуйста: ");
                else break;
            }

            void* par = malloc(sizeof(int));
            *(int*)par = tCount;
            if (ModifyElement(&temp, 3, par) != SUCCESS)
                printf("Ошибка изменения числа профессоров!\n");

            return;
        }
    }

}

/*! \brief Функция, выводящая элемент по его номеру.
 *  @param mainStruct Ссылка на первый элемент структуры.
 */
void ShowInfoByNumber(struct department** mainStruct)
{
    if (*mainStruct == NULL)
    {
        printf("Структура пуста!\n");
        return;
    }

    int number;
    char input[MAX_LENGTH];
    struct department* temp = *mainStruct;

    INFINITY_LOOP {
        printf("Введите номер кафедры: ");
        scanf("%s", input);
        number = InputChecker(input);
        if (number == ERROR || number == 0)
            printf("Введены некорректные данные, исправьте, "
                   "пожалуйста: ");
        else break;
    }

    for (int i = 1; i < number; i++)
    {
        if (temp->next == NULL)
        {
            printf("Отсутствует указанный элемент!\n");
            return;
        }
        temp = temp->next;
    }

    printf("Название кафедры: %s\nКоличество учителей:"
           " %g\nКоличество профессоров: %g\n",
           temp->name, temp->countOfTeachers, temp->countOfProfessors);
}

/*! \brief Функция, выводящая все элементы структуры.
 *  @param mainStruct Ссылка на первый элемент структуры.
 */
void ShowAllInfo(struct department** mainStruct)
{
    if (*mainStruct == NULL)
    {
        printf("Структура пуста!\n");
        return;
    }

    struct department* temp = *mainStruct;

    while (temp != NULL)
    {
        printf("Название кафедры: %s;   Количество учителей:"
               " %g;   Количество профессоров: %g\n",
               temp->name, temp->countOfTeachers, temp->countOfProfessors);
        temp = temp->next;
    }
}

/*! \brief Функция, обработки ввода-вывода для функции DeleteStruct.
 *  @param mainStruct Ссылка на первый элемент структуры.
 */
void InteractiveForDeleteStruct(struct department** mainStruct)
{
    int number;
    char input[MAX_LENGTH];

    INFINITY_LOOP {
        printf("Введите номер удаляемого элемента: ");
        scanf("%s", input);
        number = InputChecker(input);
        if (number == ERROR || number == 0)
            printf("Введены некорректные данные, исправьте, "
                   "пожалуйста: ");
        else break;
    }

    if (*mainStruct == NULL)
    {
        printf("Структура пуста!\n");
        return;
    }

    struct department* temp = *mainStruct;

    for (int i = 1; i < number; i++)
    {
        if (temp->next == NULL)
        {
            printf("Отсутствует указанный элемент!\n");
            return;
        }
        temp = temp->next;
    }

    if (DeleteStruct(&temp) != SUCCESS)
        printf("Ошибка удаления элемента структуры!\n");

}

/*! \brief Функция, обрабатывающая запрос 1.
 *  @param mainStruct Ссылка на первый элемент структуры.
 */
void InteractiveForFirstRequest(struct department** mainStruct)
{
    if (*mainStruct == NULL)
    {
        printf("Структура пуста!\n");
        return;
    }

    struct department* temp = *mainStruct;
    int flag = 0;

    while (temp != NULL)
    {
        if (temp->countOfProfessors == 0) {
            printf("На кафедре \"%s\" нет профессоров!\n",
                   temp->name);
            flag++;
        }
        temp = temp->next;
    }

    if (flag == 0)
    {
        printf("На всех кафедрах есть профессора!\n");
    }

}

/*! \brief Функция, обрабатывающая запрос 2.
 *  @param mainStruct Ссылка на первый элемент структуры.
 */
void InteractiveForSecondRequest(struct department** mainStruct)
{
    struct pair max = {0, 0};
    struct department* temp = *mainStruct;

    while (temp != NULL)
    {
        if (temp->countOfProfessors == 0)
        {
            temp = temp->next;
            continue;
        }

        if (max.value < temp->countOfProfessors / temp->countOfTeachers)
        {
            max.value = temp->countOfProfessors / temp->countOfTeachers;
            strcpy(max.name, temp->name);
        }
        temp = temp->next;
    }

    temp = *mainStruct;

    while (temp != NULL)
    {
        if (max.value == 0)
        {
            printf("Ни на одной кафедре нет профессоров!\n");

            break;
        }

        if (temp->countOfProfessors == 0)
        {
            temp = temp->next;
            continue;
        }

        if (max.value == temp->countOfProfessors / temp->countOfTeachers)
        {
            printf("На кафедре \"%s\" доля профессоров "
                   "максимальна и равна %g%%\n", temp->name, max.value * 100);
        }
        temp = temp->next;
    }

}

/*! \brief Функция, обрабатывающая запрос 3.
 *  @param mainStruct Ссылка на первый элемент структуры.
 */
void InteractiveForThirdRequest(struct department** mainStruct)
{
    struct pair min = {INFINITY, 0};
    struct department* temp = *mainStruct;

    while (temp != NULL)
    {
        if (temp->countOfProfessors == 0)
        {
            temp = temp->next;
            continue;
        }

        if (min.value > temp->countOfProfessors / temp->countOfTeachers)
        {
            min.value = temp->countOfProfessors / temp->countOfTeachers;
            strcpy(min.name, temp->name);
        }
        temp = temp->next;
    }

    temp = *mainStruct;

    while (temp != NULL)
    {
        if (min.value == INFINITY)
        {
            printf("Ни на одной кафедре нет профессоров!\n");

            break;
        }

        if (temp->countOfTeachers + temp->countOfProfessors == 0)
        {
            temp = temp->next;
            continue;
        }

        if (min.value == temp->countOfProfessors / temp->countOfTeachers)
        {
            printf("На кафедре \"%s\" доля профессоров "
                   "минимальна и равна %g%%\n", temp->name, min.value * 100);
        }
        temp = temp->next;
    }

}

