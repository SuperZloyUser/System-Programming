#ifndef SP_4_STRUCTS_H
#define SP_4_STRUCTS_H
#define MAX_LENGTH 50

/*! \struct department
 *  \brief Структура, отвечающая за хранение кафедр.
 */
struct department
{
    /*! Название кафдеры. */
    char name[MAX_LENGTH];
    /*! Число учителей. */
    double countOfTeachers;
    /*! Число профессоров. */
    double countOfProfessors;
};

#endif //SP_4_STRUCTS_H
