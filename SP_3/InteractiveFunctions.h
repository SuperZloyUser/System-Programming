#ifndef SP_3_INTERACTIVEFUNCTIONS_H
#define SP_3_INTERACTIVEFUNCTIONS_H

#include "structs.h"

int InputChecker(char* strForCheck);
void InteractiveForAddElement (struct department** mainStruct);
void InteractiveForModifyElement(struct department** mainStruct);
void ShowInfoByNumber(struct department** mainStruct);
void ShowAllInfo(struct department** mainStruct);
void InteractiveForDeleteStruct(struct department** mainStruct);
void InteractiveForFirstRequest(struct department** mainStruct);
void InteractiveForSecondRequest(struct department** mainStruct);
void InteractiveForThirdRequest(struct department** mainStruct);

#endif //SP_3_INTERACTIVEFUNCTIONS_H
