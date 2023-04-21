#include "rec.h"
#include "commons.h"

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
