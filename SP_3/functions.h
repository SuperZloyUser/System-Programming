#ifndef SP_3_FUNCTIONS_H
#define SP_3_FUNCTIONS_H

#include "structs.h"

int AddElement(struct department** mainStruct, char tString[],
                int tCount, int pCount);
int ModifyElement(struct department** currentStruct, int type, void* data);
int DeleteStruct(struct department** mainStruct);
int DeleteAllStruct(struct department** mainStruct);

#endif //SP_3_FUNCTIONS_H
