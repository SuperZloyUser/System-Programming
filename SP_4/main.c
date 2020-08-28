#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "functions.h"
#include "FileFunctions.h"

#define MAX_LENGTH 50
#define ERROR_CODE -1
#define SUCCESS 0
#define CHOOSE_HELP 1
#define CHOOSE_ADD 2
#define CHOOSE_SHOW_ONE 3
#define CHOOSE_SHOW_ALL 4
#define CHOOSE_MODIFY 5
#define CHOOSE_DELETE_ONE 6
#define CHOOSE_DELETE_ALL 7
#define CHOOSE_FIRST_REQUEST 8
#define CHOOSE_SECOND_REQUEST 9
#define CHOOSE_THIRD_REQUEST 10
#define CHOOSE_EXIT 11

#define UNKNOWN_INPUT_MASSAGE "Для вывода меню импользуйте параметр \"1\"!\n"

#define EXIT_MASSAGE "Выход.\n"

#define REQUEST_ERROR "Не удалось выполнить запрос!\n"

#define ADD_ERROR "Не удалось добавить элемент в файл!\n"

#define OUTPUT_ERROR "Не удалось вывести элемент!\n"

#define OUTPUT_ALL_ERROR "Не удалось вывести элементы!\n"

#define MODIFY_ERROR "Не удалось изменить элемент!\n"

#define DELETE_ERROR "Не удалось Удалить элемент!\n"

#define CLEAN_ERROR "Не удалось очистить файл!\n"

/*! \brief Главная функция.
 *  @return Код завершения программы.
 */
int main(int argc, char* argv[])
{

    unsigned int number = 0;

    char* path = "Save";
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int fid = open(path, O_RDWR | O_CREAT, mode);
    if (fid == ERROR_CODE)
    {
        printf("Не удалось открыть файл!\n");
        return 0;
    }

    if (argv[1] == NULL)
    {
        printf("Отсутствуют входные данные!\n");
        return 0;
    }
    number = atoi(argv[1]);

    switch (number)
    {
    case CHOOSE_HELP:
        ShowHelp();
        break;
    case CHOOSE_ADD:
        if (AddElementInFile(argv, fid) == ERROR_CODE)
        {
            printf(ADD_ERROR);
            return ERROR_CODE;
        }
        break;
    case CHOOSE_SHOW_ONE:
        if (ShowInfoFromFileByNumber(argv, fid) == ERROR_CODE)
        {
            printf(OUTPUT_ERROR);
            return ERROR_CODE;
        }
        break;
    case CHOOSE_SHOW_ALL:
        if (ShowAllFromFile(fid) == ERROR_CODE)
        {
            printf(OUTPUT_ALL_ERROR);
            return ERROR_CODE;
        }
        break;
    case CHOOSE_MODIFY:
        if (ModifyElementInFile(argv, fid) == ERROR_CODE)
        {
            printf(MODIFY_ERROR);
            return ERROR_CODE;
        }
        break;
    case CHOOSE_DELETE_ONE:
        if (DeleteElementFromFile(argv, fid) == ERROR_CODE)
        {
            printf(DELETE_ERROR);
            return ERROR_CODE;
        }
        break;
    case CHOOSE_DELETE_ALL:
        if (DeleteAllFromFile(fid) == ERROR_CODE)
        {
            printf(CLEAN_ERROR);
            return ERROR_CODE;
        }
        break;
    case CHOOSE_FIRST_REQUEST:
        if (FirstRequest(fid) == ERROR_CODE)
        {
            printf(REQUEST_ERROR);
            return ERROR_CODE;
        }
        break;
    case CHOOSE_SECOND_REQUEST:
        if (SecondRequest(fid) == ERROR_CODE)
        {
            printf(REQUEST_ERROR);
            return ERROR_CODE;
        }
            break;
    case CHOOSE_THIRD_REQUEST:
        if (ThirdRequest(fid) == ERROR_CODE)
        {
            printf(REQUEST_ERROR);
            return ERROR_CODE;
        }
        break;
    case CHOOSE_EXIT:
        printf(EXIT_MASSAGE);
        close(fid);
        return SUCCESS;
    default:
        printf(UNKNOWN_INPUT_MASSAGE);
        close(fid);
        return SUCCESS;
    }

    close(fid);
    return SUCCESS;

}
