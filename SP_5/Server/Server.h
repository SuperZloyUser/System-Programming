/*! \file
 *  \brief   Файл с объявлениями функций сетевой части сервера.
 */
#ifndef SP_5_SERVER_H
#define SP_5_SERVER_H

/*! \brief Сетевая часть сервера, за исключением определения самого сокета и
 * получения дескриптора на него.
 *
 *  \param argc Количество аргументов.
 *
 *  \return Код завершения функции.
 */
int* acceptArgs(int socketDescriptor);

#endif //SP_5_SERVER_H
