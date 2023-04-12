#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARRLEN 20

double randGenDouble(double min, double max) // need this to generate a random double
{
    double range = (max - min);
    double div = RAND_MAX / (range / 2);
    return min + (rand() / div);
}

double seqCalc()
{
    srand(time(NULL));
    double mainArray[ARRLEN];
    for (int i = 0; i < ARRLEN; i++)
    {
        mainArray[i] = randGenDouble(0.0, 1000.0);
    }
    double prod = mainArray[0];
    for (int i = 1; i < ARRLEN; i++)
    {
        prod *= mainArray[i];
    }
    return prod;
}

double tempRecCalc(double *array)
{
    return 0;
}

double recCalc()
{
    srand(time(NULL));
    double mainAray[ARRLEN];
    for (int i = 0; i < ARRLEN; i++)
    {
        mainAray[i] = randGenDouble(0.0, 1000.0);
    }
    for (int i = 0; i < ARRLEN - 1; i++)
    {
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    double mainArray[ARRLEN];
    printf("Szekvencialis szorzas: %lf\n", seqCalc());
    return 0;
}
