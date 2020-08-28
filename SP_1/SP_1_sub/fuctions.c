/*! \file
 *  \brief   Файл с функциями.
 */
#define BIT_SHIFT 2

 int Checker(char* tempForCheck)
{
    int number = 0;
    int flag = 0;

    for(int i = 0; i < strlen(tempForCheck); i++)
    {
        if(i == 0 && tempForCheck[0] == '-') {
            flag++;
            continue;
        }

        if(tempForCheck[i] == '0' || tempForCheck[i] == '1' || tempForCheck[i] == '2' || tempForCheck[i] == '3' ||
           tempForCheck[i] == '4' || tempForCheck[i] == '5' || tempForCheck[i] == '6' ||
           tempForCheck[i] == '7' || tempForCheck[i] == '8' || tempForCheck[i] == '9') number = number * 10 +
                                                                                                (tempForCheck[i] - 48);
        else
            return 0;
    }

    if(flag > 0) number *= -1;

    return number;
}

int AriShift(int tempA, int tempB)
{
    int temp = 1;

    if(tempB >= 0) {
        while (1) {
            if (temp <= tempA) temp *= BIT_SHIFT;
            else
                break;
        }

        temp /= BIT_SHIFT;

        return (tempA >> tempB) + temp;
    } else
    {
        tempB *= -1;
        return tempA << tempB;
    }
}

int CycleShift(int tempA, int tempB)
{
    int temp = 1;

    if(tempB >= 0) {

        while (1) {
            if (temp <= tempA) temp *= BIT_SHIFT;
            else
                break;
        }

        temp /= BIT_SHIFT;

        if (tempA % 2 == 0)
            return tempA >> tempB;
        else
            return (tempA >> tempB) + temp;
    } else
    {
        tempB *= -1;
        return (tempA << tempB) + 1;
    }
}
