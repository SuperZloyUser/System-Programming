#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "structs.h"

#define MAX_LENGTH 50

#define ERROR_CODE -1

#define SUCCESS 0

#define ASCII_CONST 48

#define NEXT_DIGIT 10

#define ERROR_READ_OF_FILE "Ошибка чтения файла!\n"

#define MENU_MASSAGE "Меню:\n"\
           "\"1\" - Вывести информацию о командах;\n"\
           "\"2\" - Добавить новую кафедру в файл(Интерфейс: 2 "\
           "\"Название\" \"Количество профессоров\" \""\
           "Количество преподавателей\");\n"\
           "\"3\" - Вывести информацию о кафедре из файла по её номеру"\
           "(Интерфейс: 3 \"Номер выводимой кафедры\");\n"\
           "\"4\" - Вывести информацию о всех кафедрах из файла"\
           "(Интерфейс: 4);\n"\
           "\"5\" - Изменить информацию о кафедре(Интерфейс: 4 \"Порядковый"\
           " номер кафедры\"\n\"1|2|3 - соответствующие поля(название; "\
           "количество профессоров; количество преподавателей)\" \""\
           "Устанавливаемое значение\");\n"\
           "\"6\" - Удалить кафедру из файла по её номеру(Интерфейс: 6 \"Номер удаляемой кафедры\");\n"\
           "\"7\" - Очистить файл(Интерфейс: 7)\n"\
           "\"8\" - Запрос, позволяющий определить кафедры, на которых "\
           "нет профессоров(Интерфейс: 8);\n"\
           "\"9\" - Запрос, позволяющий определить кафедру с наибольшим "\
           "процентом профессоров на ней(Интерфейс: 9);\n"\
           "\"10\" - Запрос, позволяющий определить кафедру с наименьшим процентом "\
           "профессоров, где они обязательно присутствуют(Интерфейс: 10);\n"\
           "\"11\" - Выход(Интерфейс: 11).\n"

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
            return ERROR_CODE;
    }

    return number;
}

int CheckRead(int returnFromRead)
{
    if (returnFromRead == 0) return SUCCESS;
    if (returnFromRead == ERROR_CODE)
    {
        return SUCCESS;
    }
    return 1;
}

int FilePlaceFinder(int fdMain, int number)
{
    unsigned int size;
    int executionCode = 0;
    struct department temp;

    executionCode = lseek(fdMain, 0, SEEK_SET);

    if (executionCode == ERROR_CODE)
    {
        printf(ERROR_READ_OF_FILE);
        return ERROR_CODE;
    }

    executionCode = read(fdMain, &size, sizeof (unsigned int));
    if (executionCode == ERROR_CODE || executionCode != sizeof (unsigned int))
    {
        printf(ERROR_READ_OF_FILE);
        return ERROR_CODE;
    }

    struct stat fileInfo;
    executionCode = fstat(fdMain, &fileInfo);

    if (executionCode == ERROR_CODE)
    {
        printf(ERROR_READ_OF_FILE);
        return ERROR_CODE;
    }

    if (fileInfo.st_size - sizeof (unsigned int) < size * number)
        return ERROR_CODE;

    for (int i = 0; i < number - 1; i++)
        if (read(fdMain, &temp, size) != size)
         return ERROR_CODE;

    return size;
}

void ShowHelp()
{
    printf(MENU_MASSAGE);
}
