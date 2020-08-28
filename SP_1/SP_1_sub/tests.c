/*! \file
 *  \brief   Файл с тестами.
 */
 #include <CUnit/CUnit.h>
#include "fuctions.h"

void logicalShiftTest(void)
{
    CU_ASSERT_EQUAL(33 >> 3, 4);
    CU_ASSERT_EQUAL(322 >> 5, 10);
    CU_ASSERT_EQUAL(1024 >> 10, 1);
    CU_ASSERT_EQUAL(8 << 1, 16);
}

void ariShiftTest(void)
{
    CU_ASSERT_EQUAL(AriShift(33, 3), 36);
    CU_ASSERT_EQUAL(AriShift(322, 5), 266);
    CU_ASSERT_EQUAL(AriShift(1024, 10), 1025);
    CU_ASSERT_EQUAL(AriShift(18, -5), 18 << 5);
}

void cycleShiftTest(void)
{
    CU_ASSERT_EQUAL(CycleShift(33, 3), 36);
    CU_ASSERT_EQUAL(CycleShift(322, 5), 10);
    CU_ASSERT_EQUAL(CycleShift(1024, 10), 1);
    CU_ASSERT_EQUAL(CycleShift(512, -3), 4097);
}