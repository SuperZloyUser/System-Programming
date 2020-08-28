#ifndef SP_4_FILEFUNCTIONS_H
#define SP_4_FILEFUNCTIONS_H

#include "structs.h"

/*! \brief Функция, записывающая структуру в файл.
 *  @param argvMain Параметры для записи в файл.
 *  @param fdMain Дескриптор файла.
 *  @return Код завершения функции.
 */
int AddElementInFile (char** argvMain, int fdMain);


/*! \brief Функция, очищающая файл.
 *  @param fdMain Дескриптор файла.
 *  @return Код завершения функции.
 */
int DeleteAllFromFile(int fid);


/*! \brief Функция, изменяющая поля структуры в файле.
 *  @param argvMain Параметры для записи в файл.
 *  @param fdMain Дескриптор файла.
 *  @return Код завершения функции.
 */
int ModifyElementInFile(char** argvMain, int fdMain);


/*! \brief Функция, выводящая структуру по номеру из файла.
 *  @param argvMain Параметры для записи в файл.
 *  @param fdMain Дескриптор файла.
 *  @return Код завершения функции.
 */
int ShowInfoFromFileByNumber(char** argvMain, int fdMain);


/*! \brief Функция, выводящая все данные из файла.
 *  @param fdMain Дескриптор файла.
 *  @return Код завершения функции.
 */
int ShowAllFromFile(int fidMain);


/*! \brief Функция, удаляющая элемент структуры из файла.
 *  @param argvMain Параметры для записи в файл.
 *  @param fdMain Дескриптор файла.
 *  @return Код завершения функции.
 */
int DeleteElementFromFile(char** argvMain, int fdMain);


/*! \brief Функция, выполняющая первый запрос.
 *  @param fdMain Дескриптор файла.
 *  @return Код завершения функции.
 */
int FirstRequest(int fdMain);


/*! \brief Функция, выполняющая второй запрос.
 *  @param fdMain Дескриптор файла.
 *  @return Код завершения функции.
 */
int SecondRequest(int fdMain);

/*! \brief Функция, выполняющая третий запрос.
 *  @param fdMain Дескриптор файла.
 *  @return Код завершения функции.
 */
int ThirdRequest(int fdMain);

#endif //SP_4_FILEFUNCTIONS_H
