#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "structs.h"
#include "functions.h"

#define MAX_LENGTH 50

#define ERROR_CODE -1

#define SUCCESS 0

#define ASCII_CONST 48

#define NEXT_DIGIT 10

#define CHANGE_NAME 1

#define CHANGE_COUNT_OF_PROFESSORS 2

#define CHANGE_COUNT_OF_TEACHERS 3

#define INFINITY 999999999

#define FIRST_PARAM 2

#define SECOND_PARAM 3

#define THIRD_PARAM 4

#define LAST_ONE 1

#define FILE_IS_CLEARNED "Файл успешно очищен!\n"

#define FILE_IS_EMPTY "В файле отстутствуют данные!\n"

#define ERROR_INPUT_IS_EMPTY "Неверные входные данные!\n"

#define ERROR_NAME_IS_TOO_LONG "Слишком длинное название!\n"

#define ERROR_OF_INCORRECT_INPUT "Некорректные входные данные!\n"

#define ERROR_OF_INCORRECT_COUNT_OF_TEACHERS "Некорректное количество преподавателей!\n"

#define ERROR_OUTPUT_IN_FILE "Ошибка записи элемента структуры!\n"

#define ERROR_OUTPUT_ELEMENT_IN_FILE "Ошибка записи элемента структуры!"

#define ERROR_READ_FROM_FILE "Ошибка считывания из файла!\n"

#define ERROR_INCORRECT_NUMBER_OF_ELEMENT "Некорректный номер элемента!\n"

#define ERROR_CONFLICT_T_P "Профессоров не должно быть больше, чем преподавателей!\n"

#define TEMP_FILE_NAME "tempSave"

#define ERROR_INCORRECT_NUMBER_OF_DEPARTMENT "Некорректный номер кафедры!\n"

#define ERROR_DEPARTMENTS_IS_MISSING "Кафедры отсутствуют!\n"

#define SECOND_REQUEST_MASSAGE "Кафедры, на которых доля профессоров максимальна:\n"

#define THIRD_REQUEST_MESSAGE "Кафедры, на которых присутствуют профессора и их доля минимальна:\n"

#define ERROR_OF_CLEARNING_FILE "Не удалось очистить файл!\n"

#define ERROR_NO_PROF_DEPARTMENTS "Отсутствуют кафедры, на которых нет профессоров!\n"

int AddElementInFile (char** argvMain, int fdMain)
{
    int executionCode = 0;
    unsigned int size = sizeof (struct department);
    struct department temp;

    if (argvMain[FIRST_PARAM] == NULL || argvMain[SECOND_PARAM] == NULL || argvMain[THIRD_PARAM] == NULL)
    {
        printf(ERROR_INPUT_IS_EMPTY);
        return ERROR_CODE;
    }

    if (strlen(argvMain[FIRST_PARAM]) > MAX_LENGTH)
    {
        printf(ERROR_NAME_IS_TOO_LONG);
        return ERROR_CODE;
    }

    for (unsigned long i = 0; i < strlen(argvMain[FIRST_PARAM]) + LAST_ONE; i++)
        temp.name[i] = argvMain[FIRST_PARAM][i];

    if (atoi(argvMain[SECOND_PARAM]) != InputChecker(argvMain[SECOND_PARAM]) ||
        atoi(argvMain[THIRD_PARAM]) < atoi(argvMain[SECOND_PARAM]))
    {
        printf(ERROR_OF_INCORRECT_INPUT);
        return ERROR_CODE;
    }
    else
        temp.countOfProfessors = atoi(argvMain[SECOND_PARAM]);


    if (atoi(argvMain[THIRD_PARAM]) != InputChecker(argvMain[THIRD_PARAM]))
    {
        printf(ERROR_OF_INCORRECT_COUNT_OF_TEACHERS);
        return ERROR_CODE;
    }
    else
        temp.countOfTeachers = atoi(argvMain[THIRD_PARAM]);


    executionCode = lseek(fdMain, 0, SEEK_END);

    if (executionCode == ERROR_CODE)
    {
        printf(ERROR_OUTPUT_IN_FILE);
        return ERROR_CODE;
    }

    struct stat fileInfo;
    fstat(fdMain, &fileInfo);
    if (fileInfo.st_size == 0)
    {
        executionCode = write(fdMain, &size, sizeof (unsigned int));
        if (executionCode == ERROR_CODE)
        {
            printf(ERROR_OUTPUT_ELEMENT_IN_FILE);
            return ERROR_CODE;
        }
    }

    executionCode = write(fdMain, &temp, size);
    if (executionCode == ERROR_CODE)
    {
        printf(ERROR_OUTPUT_ELEMENT_IN_FILE);
        return ERROR_CODE;
    }

    return SUCCESS;

}

int DeleteAllFromFile(int fid)
{
    if (ftruncate(fid, 0) == ERROR_CODE) {
        printf(ERROR_OF_CLEARNING_FILE);
        return ERROR_CODE;
    }
    
    printf(FILE_IS_CLEARNED);

    return SUCCESS;
}

int ModifyElementInFile(char** argvMain, int fdMain)
{
    if (argvMain[FIRST_PARAM] == NULL || argvMain[SECOND_PARAM] == NULL || argvMain[THIRD_PARAM] == NULL)
    {
        printf(ERROR_INPUT_IS_EMPTY);
        return ERROR_CODE;
    }

    int choose = 0;
    int number = 0;
    int size = 0;

    if (atoi(argvMain[FIRST_PARAM]) != InputChecker(argvMain[FIRST_PARAM]))
    {
        printf(ERROR_OF_INCORRECT_INPUT);
        return ERROR_CODE;
    }
    else
        number = InputChecker(argvMain[FIRST_PARAM]);

    if (atoi(argvMain[SECOND_PARAM]) != InputChecker(argvMain[SECOND_PARAM]))
    {
        printf(ERROR_OF_INCORRECT_INPUT);
        return ERROR_CODE;
    }
    else
        choose = InputChecker(argvMain[SECOND_PARAM]);

    if ((choose == CHANGE_COUNT_OF_PROFESSORS || choose == CHANGE_COUNT_OF_TEACHERS) &&
        atoi(argvMain[THIRD_PARAM]) != InputChecker(argvMain[THIRD_PARAM]))
        {
            printf(ERROR_OF_INCORRECT_INPUT);
            return ERROR_CODE;
        }

    if (lseek(fdMain, 0, SEEK_SET) == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    int executionCode = read(fdMain, &size, sizeof (unsigned int));

    if (executionCode == ERROR_CODE || executionCode < sizeof (unsigned int))
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    struct department temp;

    char* path = TEMP_FILE_NAME;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int supFid = open(path, O_RDWR | O_CREAT, mode);

    int count = 0;
    DeleteAllFromFile(supFid);

    while (CheckRead(read(fdMain, &temp, size)))
    {
        if (write(supFid, &temp, size) == ERROR_CODE)
        {
            printf(ERROR_OUTPUT_IN_FILE);
            close(supFid);
            return ERROR_CODE;
        }

        count++;
    }

    if (InputChecker(argvMain[FIRST_PARAM]) > count)
    {
        printf(ERROR_INCORRECT_NUMBER_OF_ELEMENT);
        close(supFid);
        return ERROR_CODE;
    }

    DeleteAllFromFile(fdMain);

    if (lseek(fdMain, 0, SEEK_SET) == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    if (lseek(supFid, 0, SEEK_SET) == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    if (write(fdMain, &size, sizeof(unsigned int)) == ERROR_CODE)
    {
        printf(ERROR_OUTPUT_IN_FILE);
        close(supFid);
        return ERROR_CODE;
    }

    for (int i = 1; i <= count; i++)
    {
        executionCode = read(supFid, &temp, size);

        if (executionCode == ERROR_CODE || executionCode < sizeof (unsigned int))
        {
            printf(ERROR_READ_FROM_FILE);
            return ERROR_CODE;
        }

        if (number == i)
            switch (choose)
            {
            case CHANGE_NAME:
                strcpy(temp.name, argvMain[THIRD_PARAM]);
                break;
            case CHANGE_COUNT_OF_PROFESSORS:
                if (temp.countOfTeachers <
                    InputChecker(argvMain[THIRD_PARAM]))
                {
                    printf(ERROR_CONFLICT_T_P);
                }
                else
                    temp.countOfProfessors =
                            InputChecker(argvMain[THIRD_PARAM]);
                break;
            case CHANGE_COUNT_OF_TEACHERS:
                if (temp.countOfProfessors >
                    InputChecker(argvMain[THIRD_PARAM]))
                {
                    printf(ERROR_CONFLICT_T_P);
                }
                else
                    temp.countOfTeachers = InputChecker(argvMain[THIRD_PARAM]);
                break;
            }

        if (write(fdMain, &temp, size) == ERROR_CODE)
        {
            printf(ERROR_OUTPUT_IN_FILE);
            close(supFid);
            return ERROR_CODE;
        }
    }

    close(supFid);
    remove(TEMP_FILE_NAME);

    return SUCCESS;
}

int ShowInfoFromFileByNumber(char** argvMain, int fdMain)
{
    struct department temp;
    int size = 0;

    if (argvMain[FIRST_PARAM] == NULL)
    {
        printf(ERROR_INPUT_IS_EMPTY);
        return ERROR_CODE;
    }

    if (atoi(argvMain[FIRST_PARAM]) != InputChecker(argvMain[FIRST_PARAM]))
    {
        printf(ERROR_INCORRECT_NUMBER_OF_DEPARTMENT);
        return ERROR_CODE;
    }
    else
        size = FilePlaceFinder(fdMain, InputChecker(argvMain[FIRST_PARAM]));

    if (size == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    if (read(fdMain, &temp, size) == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    printf("Название: %s;  Количество профессоров: %g;  Количество преподавателей: %g.\n",
           temp.name, temp.countOfProfessors, temp.countOfTeachers);

    return SUCCESS;
}

int ShowAllFromFile(int fdMain)
{
    unsigned int size = 0;
    int count = 1;
    struct department temp;
    int executionCode = 0;

    executionCode = lseek(fdMain, 0, SEEK_SET);
    if (executionCode == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    if (CheckRead(read(fdMain, &size, sizeof (unsigned int))) == ERROR_CODE)
        return ERROR_CODE;

    while (CheckRead(read(fdMain, &temp, size)))
    {
        printf("%d) Название: %s;  Количество профессоров: %g;  Количество преподавателей: %g.\n",
               count, temp.name, temp.countOfProfessors, temp.countOfTeachers);

        count++;
    }
    
    if (count == 1)
        printf(FILE_IS_EMPTY);
        
    return SUCCESS;
}

int DeleteElementFromFile(char** argvMain, int fdMain)
{
    if (argvMain[FIRST_PARAM] == NULL)
    {
        printf(ERROR_INPUT_IS_EMPTY);
        return ERROR_CODE;
    }

    int number = 0;

    if (atoi(argvMain[FIRST_PARAM]) != InputChecker(argvMain[FIRST_PARAM]))
    {
        printf(ERROR_INCORRECT_NUMBER_OF_ELEMENT);
        return ERROR_CODE;
    }
    else
        number = InputChecker(argvMain[FIRST_PARAM]);

    int size = 0;

    lseek(fdMain, 0, SEEK_SET);

    if (read(fdMain, &size, sizeof (unsigned int)) == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    struct department temp;

    char* path = TEMP_FILE_NAME;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int supFid = open(path, O_RDWR | O_CREAT, mode);

    int count = 0;
    DeleteAllFromFile(supFid);

    while (CheckRead(read(fdMain, &temp, size)))
    {
        if (write(supFid, &temp, size) == ERROR_CODE)
        {
            printf(ERROR_READ_FROM_FILE);
            close(supFid);
            return ERROR_CODE;
        }

        count++;
    }

    if (InputChecker(argvMain[FIRST_PARAM]) > count)
    {
        printf(ERROR_INCORRECT_NUMBER_OF_ELEMENT);
        close(supFid);
        return ERROR_CODE;
    }

    DeleteAllFromFile(fdMain);
    lseek(fdMain, 0, SEEK_SET);
    lseek(supFid, 0, SEEK_SET);

    if (write(fdMain, &size, sizeof (unsigned int)) == ERROR_CODE)
    {
        printf(ERROR_OUTPUT_IN_FILE);
        close(supFid);
        return ERROR_CODE;
    }

    int executionCode = 0;

    for (int i = 1; i <= count; i++)
    {
         executionCode = read(supFid, &temp, size);

        if (executionCode == ERROR_CODE || executionCode < sizeof (unsigned int))
        {
            printf(ERROR_READ_FROM_FILE);
            return ERROR_CODE;
        }

         if (i == number)
             continue;

        if (write(fdMain, &temp, size) == ERROR_CODE)
        {
            printf(ERROR_OUTPUT_IN_FILE);
            close(supFid);
            return ERROR_CODE;
        }
    }

    close(supFid);
    remove(TEMP_FILE_NAME);

    return SUCCESS;
}

int FirstRequest(int fdMain) {
    int size = 0;
    int count = 0;
    struct department temp;

    if (lseek(fdMain, 0, SEEK_SET) == ERROR_CODE) {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    if (CheckRead(read(fdMain, &size, sizeof(unsigned int))) == ERROR_CODE) {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    int flag = 0;

    while (CheckRead(read(fdMain, &temp, size))) {
        count++;

        if (temp.countOfProfessors == 0) {
            printf("На кафедре %d - \"%s\" нет профессоров!\n",
                   count, temp.name);

            flag++;
        }
    }

    if (count == 0)
    {
        printf(ERROR_DEPARTMENTS_IS_MISSING);
        return ERROR_CODE;
    }

    if (flag == 0)
        printf(ERROR_NO_PROF_DEPARTMENTS);

    return SUCCESS;
}

int SecondRequest(int fdMain)
{
    int size = 0;
    int count = 0;
    double per = 0;
    struct department temp;

    if (lseek(fdMain, 0, SEEK_SET) == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    if (CheckRead(read(fdMain, &size, sizeof (unsigned int))) == ERROR_CODE)
        return ERROR_CODE;

    while (CheckRead(read(fdMain, &temp, size)))
    {
        if (temp.countOfProfessors / temp.countOfTeachers > per)
            per = temp.countOfProfessors / temp.countOfTeachers;

        count++;
    }


    if (lseek(fdMain, 0, SEEK_SET) == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    if (CheckRead(read(fdMain, &size, sizeof (unsigned int))) == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    if (per == 0)
    {
        printf(ERROR_DEPARTMENTS_IS_MISSING);
        return SUCCESS;
    }

    if (count == 0)
    {
        printf(FILE_IS_EMPTY);
        return SUCCESS;
    }

    count = 0;

    printf(SECOND_REQUEST_MASSAGE);

    while (CheckRead(read(fdMain, &temp, size)))
    {
        count++;

        if (per == temp.countOfProfessors / temp.countOfTeachers)
            printf("%d) \"%s\" - %.2f%%\n", count, temp.name, per * 100);
    }

    return SUCCESS;
}

int ThirdRequest(int fdMain)
{
    int size = 0;
    int count = 0;
    double per = INFINITY;
    struct department temp;

    if (lseek(fdMain, 0, SEEK_SET) == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    if (CheckRead(read(fdMain, &size, sizeof (unsigned int))) == ERROR_CODE)
        return ERROR_CODE;

    while (CheckRead(read(fdMain, &temp, size)))
    {
        if (temp.countOfProfessors / temp.countOfTeachers < per)
            per = temp.countOfProfessors / temp.countOfTeachers;

        count++;
    }


    if (lseek(fdMain, 0, SEEK_SET) == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    if (CheckRead(read(fdMain, &size, sizeof (unsigned int))) == ERROR_CODE)
    {
        printf(ERROR_READ_FROM_FILE);
        return ERROR_CODE;
    }

    if (per == INFINITY)
    {
        printf(ERROR_DEPARTMENTS_IS_MISSING);
        return SUCCESS;
    }

    if (count == 0)
    {
        printf(FILE_IS_EMPTY);
        return SUCCESS;
    }

    count = 0;

    printf(THIRD_REQUEST_MESSAGE);

    while (CheckRead(read(fdMain, &temp, size)))
    {
        count++;

        if (per == temp.countOfProfessors / temp.countOfTeachers)
            printf("%d) \"%s\" - %.2f%%\n", count, temp.name, per * 100);
    }

    return SUCCESS;
}
