#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "InteractiveFunctions.h"
#include "structs.h"
#define INFINITY_LOOP for(;;)
#define MAX_LENGTH 50
#define ERROR -1
#define SUCCESS 0
#define CHOOSE_ADD 1
#define CHOOSE_SHOW_ONE 2
#define CHOOSE_SHOW_ALL 3
#define CHOOSE_MODIFY 4
#define CHOOSE_DELETE_ONE 5
#define CHOOSE_FIRST_REQUEST 6
#define CHOOSE_SECOND_REQUEST 7
#define CHOOSE_THIRD_REQUEST 8
#define CHOOSE_EXIT 9

/*! \brief Главная функция.
 *  @return Код завершения программы.
 */
int main()
{

    char input[MAX_LENGTH];
    int number = 0;

    struct department* dataStructure = NULL;

    INFINITY_LOOP
    {
        printf("Меню:\n"
               "\"1\" - Добавить новую кафедру в структуру;\n"
               "\"2\" - Вывести информацию о кафедре по её номеру;\n"
               "\"3\" - Вывести информацию о всех кафедрах;\n"
               "\"4\" - Изменить информацию о кафедрах;\n"
               "\"5\" - Удалить кафедру по её номеру;\n"
               "\"6\" - Запрос, позволяющий определить кафедры, на которых "
               "нет профессоров;\n"
               "\"7\" - Запрос, позволяющий определить кафедру с наибольшим "
               "процентом профессоров на ней;\n"
               "\"8\" - Запрос, позволяющий определить кафедру с наименьшим "
               "процентом профессоров на ней;\n"
               "\"9\" - Выход.\n");

        INFINITY_LOOP
        {
            scanf("%s", input);
            number = InputChecker(input);
            if (number < CHOOSE_ADD || number > CHOOSE_EXIT)
                printf("Введены некорректные данные, исправьте, "
                       "пожалуйста: ");
            else break;
        }

        switch (number)
        {
        case CHOOSE_ADD:
            InteractiveForAddElement(&dataStructure);
            break;
        case CHOOSE_SHOW_ONE:
            ShowInfoByNumber(&dataStructure);
            break;
        case CHOOSE_SHOW_ALL:
            ShowAllInfo(&dataStructure);
            break;
        case CHOOSE_MODIFY:
            InteractiveForModifyElement(&dataStructure);
            break;
        case CHOOSE_DELETE_ONE:
            InteractiveForDeleteStruct(&dataStructure);
            break;
        case CHOOSE_FIRST_REQUEST:
            InteractiveForFirstRequest(&dataStructure);
            break;
        case CHOOSE_SECOND_REQUEST:
            InteractiveForSecondRequest(&dataStructure);
            break;
        case CHOOSE_THIRD_REQUEST:
            InteractiveForThirdRequest(&dataStructure);
            break;
        case CHOOSE_EXIT:
            if (DeleteAllStruct(&dataStructure) != SUCCESS)
                printf("Ошибка удаления структуры!\n");
            return 0;
        break;
        default:
            return 0;
        }

    }

}