#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structs.h"
#define MAX_LENGTH 50
#define ERROR -1
#define SUCCESS 0
#define ASCII_CONST 48
#define NEXT_DIGIT 10
#define INFINITY_LOOP for(;;)
#define CHANGE_NAME 1
#define CHANGE_COUNT_OF_TEACHERS 2
#define CHANGE_COUNT_OF_PROFESSORS 3


/*! \brief Функция, добавляющая элемент в структуру.
 *  @param mainStruct Ссылка на первый элемент структуры.
 *  @param tString Строка с названием кафедры.
 *  @param tCount Количество учителей в добавляемой структуре.
 *  @param pCount Количество профессоров в добавляемой структуре.
 *  @return Код завершения функции.
 */
int AddElement(struct department** mainStruct, char tString[],
        int tCount, int pCount)
{
    struct department* temp = NULL;

    temp = (struct department*) malloc(sizeof(struct department));
    if (temp == NULL)
    {
        perror("malloc");
        return ERROR;
    }

    temp->name = (char*) malloc(sizeof(char) * (strlen(tString) + 1));
    if (temp->name == NULL)
    {
        perror("malloc");
        return ERROR;
    }
    strcpy(temp->name, tString);

    temp->countOfTeachers = tCount;

    temp->countOfProfessors = pCount;

    if (*mainStruct == NULL)
    {
        *mainStruct = temp;
        return SUCCESS;
    }

    struct department* temp2 = *mainStruct;

    while (temp2->next != NULL)
    {
        temp2 = temp2->next;
    }

    temp2->next = temp;
    temp->prev = temp2;

    return SUCCESS;
}

/*! \brief Функция, изменяющая элемент структуры.
 *  @param mainStruct Ссылка на первый элемент структуры.
 *  @param type Флаг, указывающий поле, которое необходимо изменить.
 *  @param data Ссылка на область памяти с новой информацией для
 *  изменяемого поля.
 *  @return Код завершения функции.
 */
int ModifyElement(struct department** currentStruct, int type, void* data)
{

    if (*currentStruct == NULL)
        return ERROR;

    if (type == CHANGE_NAME)
    {
        char* input = data;

        if ((*currentStruct)->name != NULL) free((*currentStruct)->name);

        (*currentStruct)->name = (char*) malloc(sizeof(char) *
                                                        (strlen(input) + 1));
        if ((*currentStruct)->name == NULL)
        {
            perror("malloc");
            return ERROR;
        }

        strcpy((*currentStruct)->name, input);
        free(data);
        return SUCCESS;
    }

    if (type == CHANGE_COUNT_OF_TEACHERS)
    {
        int value = *(int*)data;
        (*currentStruct)->countOfTeachers = value;
        free(data);
        return SUCCESS;
    }

    if (type == CHANGE_COUNT_OF_PROFESSORS)
    {
        int value = *(int*)data;
        (*currentStruct)->countOfProfessors = value;
        free(data);
        return SUCCESS;
    }

    return ERROR;

}

/*! \brief Функция, удаляющая элемент структуры.
 *  @param mainStruct Ссылка на первый элемент структуры.
 *  @return Код завершения функции.
 */
int DeleteStruct(struct department** mainStruct)
{

    if (*mainStruct == NULL)
        return ERROR;

    if ((*mainStruct)->next == NULL)
    {
        (*mainStruct)->prev->next = NULL;
        free((*mainStruct)->name);
        free((*mainStruct));
        return SUCCESS;
    }

    if ((*mainStruct)->prev == NULL)
    {
        (*mainStruct)->next->prev = NULL;
        free((*mainStruct)->name);
        free((*mainStruct));
        return SUCCESS;
    }

    (*mainStruct)->prev->next = (*mainStruct)->next;
    (*mainStruct)->next->prev = (*mainStruct)->prev;
    free((*mainStruct)->name);
    free((*mainStruct));

    return SUCCESS;

}

/*! \brief Функция, удаляющая структуру.
 *  @param mainStruct Ссылка на первый элемент структуры.
 *  @return Код завершения функции.
 */
int DeleteAllStruct(struct department** mainStruct)
{

    if (*mainStruct == NULL) return ERROR;

    struct department* temp = NULL;

    while (*mainStruct != NULL)
    {
        temp = *mainStruct;
        *mainStruct = (*mainStruct)->next;
        free(temp->name);
        free(temp);
    }

    return SUCCESS;

}
