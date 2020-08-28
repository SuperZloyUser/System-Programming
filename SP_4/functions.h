#ifndef SP_4_FUNCTIONS_H
#define SP_4_FUNCTIONS_H

#include <unistd.h>
#include "structs.h"

/*! \brief Функция, обрабатывающая ввод.
 *  @param strForCheck Строка считанная с клавиатуры.
 *  @return number Число, содержащееся в строке, код ошибки(-1) в противном случае.
 */
int InputChecker(char* strForCheck);



/*! \brief Функция, обрабатывающая работу функций read для цикла(для удобства).
 *  @param returnFromRead возвращаемое функцией read значение.
 *  @return Код выполнения функции.
 */
int CheckRead(int returnFromRead);



/*! \brief Функция, ищущая структуру в файле по номеру.
 *  @param argvMain Параметры для записи в файл.
 *  @param fdMain Дескриптор файла.
 *  @return Код завершения функции.
 */
int FilePlaceFinder(int fid, int number);



/*! \brief Функция, выводящее меню помощи.
 */
void ShowHelp();

#endif //SP_4_FUNCTIONS_H
