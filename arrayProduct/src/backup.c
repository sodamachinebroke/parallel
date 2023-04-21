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

double recProduct(double array[], int n, int depth)
{

    if (n == 0)
    {
        return 1.0;
    }
    else if (n == 1 || depth == 0)
    {
        return array[0];
    }
    else
    {
        int mid = n / 2;
        return recProduct(array, mid, depth - 1) * recProduct(&array[mid], n - mid, depth - 1);
    }
}

double recProdMain()
{

    double mainArray[ARRLEN];
    for (int i = 0; i < ARRLEN; i++)
    {
        mainArray[i] = randGenDouble(0.1, 10.0);
    }
    return recProduct(mainArray, ARRLEN, 4);
}



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

int main(int argc, char const *argv[])
{
    srand(12345);
    double mainArray[ARRLEN];
    printf("Product using different methods, a size 20 double array, with randomly generated numbers betweens 0.1 and 10.0.\n");
    printf("Sequential multiplying method: %lf\n", seqCalc());
    printf("Recursive method using a set recursive depth: %lf\n", recProdMain());
    printf("OMP using a parallel FOR cycle: %lf\n", ompForCalc());
    printf("OMP using a reduction operator: %lf\n", ompRedCalc());
    return 0;
}