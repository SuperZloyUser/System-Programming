/*! \file
 *  \brief   Главный файл дочерней программы.
 */
 #include "CUnit/Basic.h"
#include "tests.h"
#include "fuctions.h"
#define MAX_LENGTH 50

int main (int argc, char** argv)
{

    CU_pSuite suite;
    CU_initialize_registry();
    suite = CU_add_suite("main_suite", NULL, NULL);
    CU_ADD_TEST(suite, logicalShiftTest);
    CU_ADD_TEST(suite, ariShiftTest);
    CU_ADD_TEST(suite, cycleShiftTest);
    CU_basic_run_tests();

    CU_cleanup_registry();

    int A = 0;
    int B = 0;

    char str1[MAX_LENGTH];
    char str2[MAX_LENGTH];

    scanf("%s", str1);
    A = Checker(str1);
    if(A == 0)
    {
        printf("Введены некорректные данные!");
        return 0;
    }

    scanf("%s", str2);
    B = Checker(str2);
    if(B == 0) {
        printf("Введены некорректные данные!");
        return 0;
    }

    if(B >= 0)
        printf("Результат логического сдвига: %d\n", A >> B);
    else
        printf("Результат логического сдвига: %d\n", A << (B * -1));

    printf("Результат арифметического сдвига: %d\n", AriShift(A, B));

    printf("Результат циклического сдвига: %d\n", CycleShift(A, B));

    return CU_get_error();
}
