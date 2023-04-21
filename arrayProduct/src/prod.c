#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "seq.h"
#include "commons.h"
#include "rec.h"
#include "omp.h"

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