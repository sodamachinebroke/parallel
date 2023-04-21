#include "commons.h"

double ompForCalc()
{

    double mainArray[ARRLEN];
    for (int i = 0; i < ARRLEN; i++)
    {
        mainArray[i] = randGenDouble(0.1, 10.0);
    }
    double product = 1.0;
#pragma omp parallel for
    for (int i = 0; i < ARRLEN; i++)
    {
#pragma omp atomic
        product *= mainArray[i];
    }
    return product;
}
double ompRedCalc()
{

    double mainArray[ARRLEN];
    for (int i = 0; i < ARRLEN; i++)
    {
        mainArray[i] = randGenDouble(0.1, 10.0);
    }
    double product = 1.0;
#pragma omp parallel for reduction(* \
                                   : product)
    for (int i = 0; i < ARRLEN; i++)
        product *= mainArray[i];
    return product;
}