#ifndef SP_3_STRUCTS_H
#define SP_3_STRUCTS_H
#define MAX_LENGTH 50

/*! \struct department
 *  \brief Структура, отвечающая за хранение кафедр.
 */
struct department
{
    /*! Название кафдеры. */
    char* name;
    /*! Число учителей. */
    double countOfTeachers;
    /*! Число профессоров. */
    double countOfProfessors;

    /*! Ссылка на следующий элемент структуры. */
    struct department* next;
    /*! Ссылка на предыдущий элемент структуры. */
    struct department* prev;
};


/*! \struct pair
 *  \brief Структура, для работы с парой связных переменных.
 */
struct pair
{
    /*! Дробное значние в паре. */
    double value;
    /*! Название пары. */
    char name[MAX_LENGTH];
};

#endif //SP_3_STRUCTS_H
