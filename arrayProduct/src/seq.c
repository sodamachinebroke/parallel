#include "commons.h"

double seqCalc()
{
    double mainArray[ARRLEN];
    for (int i = 0; i < ARRLEN; i++)
    {
        mainArray[i] = randGenDouble(0.1, 10.0);
    }
    double prod = mainArray[0];
    for (int i = 1; i < ARRLEN; i++)
    {
        prod *= mainArray[i];
    }
    return prod;
}