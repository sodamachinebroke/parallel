#include <stdlib.h>
#include "commons.h"

double randGenDouble(double min, double max) // need this to generate a random double
{
    double range = (max - min);
    double div = RAND_MAX / (range / 2);
    return min + (rand() / div);
}