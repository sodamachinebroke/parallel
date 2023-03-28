#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

double randGenDouble(double min, double max) // need this to generate a random double
{
    double range = (max - min);
    double div = RAND_MAX / (range / 2);
    return min + (rand() / div);
}

int iterativeBinarySearch(double *array, double n, int low, int high) // self-explanatory
{
    while (low != high)
    {
        int mid = (low + high) / 2;
        if (n == array[mid])
            return mid;
        else if (n > array[mid])
            low++;
        else
            high--;
    }
}

int recursiveBinarySearch(double *array, double n, int low, int high) // self-explanatory pt2
{
    if (low > high)
        return 9999999;
    else
    {
        int mid = (low + high) / 2;
        if (n == array[mid])
            return mid;
        else if (n > array[mid])
            return recursiveBinarySearch(array, n, mid + 1, high);
        else
            return recursiveBinarySearch(array, n, low, mid - 1);
    }
}
int randInt(int high) // this one makes a random integer
{
    return (rand() % (high + 1));
}

void iterBinSearchArrayTest(int arrlen, double limit) // generates and searches an array with iterative binary search
{
    printf("\nIterative Binary Search Test in a randomly generated floating point array with %d numbers.", arrlen);
    srand(time(NULL));                       // randomizing
    double workArray2[arrlen];               // generating array
    workArray2[0] = randGenDouble(0, limit); // it is necessary to generate first value of array in order to achieve a monotone increasing array

    for (int i = 1; i < arrlen; i++)
        workArray2[i] = randGenDouble(workArray2[i - 1], limit); // filling array up with values guaranteed to be greater than the previous one

    srand(time(NULL));                                     // randomizing again
    double randomNumber = workArray2[randInt(arrlen - 1)]; // pulling a randomly selected number from the array
    printf("\nThe one we are looking for: %lf", randomNumber);
    printf("\nIterative binary search starting");
    clock_t beginIter = clock();                                                                                               // performance monitoring
    printf("\nThe number you were looking for is at %d position", iterativeBinarySearch(workArray2, randomNumber, 0, arrlen)); // integrated binary search
    clock_t endIter = clock();
    double timeSpentIter = (double)(endIter - beginIter) / CLOCKS_PER_SEC; // calculates the time spent with searching
    printf("\nTime spent with the iterative method: %lf", timeSpentIter);
}

void recBinSearchArrayTest(int arrlen, double limit) // this one does the same as the previous but with a recursive binary search
{
    printf("\nRecursive Binary Search Test in a randomly generated floating point array with %d numbers.", arrlen);
    srand(time(NULL));
    double workArray2[arrlen];               // generating array that is arrlen sized
    workArray2[0] = randGenDouble(0, limit); // this one generates a random double to fill the first value in the double array
    for (int i = 1; i < arrlen; i++)
        workArray2[i] = randGenDouble(workArray2[i - 1], limit); // filling the array with randoms; this also makes it so it's strictly monotincally increasing
    srand(time(NULL));
    double randomNumber = workArray2[randInt(arrlen - 1)]; // let's find a random index in the array, that we're gonna make the algorithm look for
    printf("\nThe one we are looking for: %lf", randomNumber);
    printf("\nRecursive binary search starting");
    clock_t beginRec = clock();                                                                                                // performance monitoring
    printf("\nThe number you were looking for is at %d position", recursiveBinarySearch(workArray2, randomNumber, 0, arrlen)); // magic
    clock_t endRec = clock();                                                                                                  // end of monitoring
    double timeSpentRec = (double)(endRec - beginRec) / CLOCKS_PER_SEC;                                                        // calculating the time spent with magic
    printf("\nTime spent with the recursive method: %lf", timeSpentRec);
}
int main()
{

    srand(time(NULL));
    iterBinSearchArrayTest(10, 100000000);
    srand(time(NULL));
    iterBinSearchArrayTest(100, 100000000);
    srand(time(NULL));
    iterBinSearchArrayTest(1000, 100000000);
    srand(time(NULL));
    recBinSearchArrayTest(10, 100000000);
    srand(time(NULL));
    recBinSearchArrayTest(100, 100000000);
    srand(time(NULL));
    recBinSearchArrayTest(1000, 100000000);
}
