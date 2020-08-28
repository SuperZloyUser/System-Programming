/*! \file
 *  \brief   Файл с объявлениями функций вывода для сервера.
 */
#ifndef SP_5_OUTFUNCS_H
#define SP_5_OUTFUNCS_H

/*! \brief Функция, выводящая результат.
 *
 *  \param number1 Первое число.
 *  \param number2 Второе число.
 */
void OutInfoServer(int number1, int number2);

/*! \brief Функция, выводящая полученные от клиента данные.
 *
 *  \param text Полученная строка.
 *
 */
void PrintInput(char* text);

#endif //SP_5_OUTFUNCS_H
