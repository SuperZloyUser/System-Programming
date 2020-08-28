/*! \file
 *  \brief   Файл с объявлениями общих функций.
 */
#ifndef SP_1_FUCTIONS_H
#define SP_1_FUCTIONS_H

/*! \brief Проверяет введённые данные.
 *
 *  \details Если получает строку, содержащую целое число, то возвращает его, а иначе возвращает -1.
 *
 *  \param tempForCheck Строка с потенциальным числом.
 *  \return возвращает полученное число, преобразованное к формату int.
 */
int Checker(char* tempForCheck);

/*! \brief Выполняет арифметический сдвиг.
 *
 *  \details Выполняет арифметический сдвиг числа A на значение B.
 *
 *  \param A Сдвигаемое число.
 *  \param B шаг сдвига.
 *  \return Возвращает сдвинутое по арифметическому принципу число.
 */
int AriShift(int tempA, int tempB);

/*! \brief Выполняет циклический сдвиг.
 *
 *  \details Выполняет циклический сдвиг числа A на значение B.
 *
 *  \param A Сдвигаемое число.
 *  \param B шаг сдвига.
 *  \return Возвращает сдвинутое по циклическому принципу число.
 */
int CycleShift(int tempA, int tempB);

/*! \brief Извлекае из строки 2 числа по возможности.
 *
 *  \param length Длинна входной строки.
 *  \param text Входная строка.
 *  \return Возвращает указатель на пару чисел в случае успеха,
 *  NULL в случае ошибки.
 */
int* CheckMessageFunction(int length, char* text);

#endif //SP_1_FUCTIONS_H
