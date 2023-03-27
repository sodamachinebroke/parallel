#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

double randGenDouble(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / (range/2);
    return min + (rand() / div);
}

int iterativeBinarySearch(double *array, double n, int low, int high)
{
    while(low!=high){
        int mid =(low+high)/2;
        if(n == array[mid])
        return mid;
        else if(n > array[mid])
        low++;
        else
        high--;
    }
}

int recursiveBinarySearch(double *array, double n, int low, int high)
{
    if (low>high)
    return 9999999;
    else{
    int mid = (low + high) /2;
    if (n== array[mid])
    return mid;
    else if (n>array[mid])
    return recursiveBinarySearch(array, n, mid+1, high);
    else
    return recursiveBinarySearch(array, n , low, mid-1);
    }
}
int randInt(int high)
{
    return (rand() % (high+1));
}

void iterBinSearchArrayTest(int arrlen, double limit){
    printf("\nIterative Binary Search Test in a randomly generated floating point array with %d numbers.", arrlen);
    srand(time(NULL));
    double workArray2[arrlen];
    workArray2[0] = randGenDouble(0,limit);
    for (int i = 1; i < arrlen; i++)
        workArray2[i] = randGenDouble(workArray2[i-1], limit);
    srand(time(NULL));
    double randomNumber = workArray2[randInt(arrlen-1)];
    printf("\nThe one we are looking for: %lf", randomNumber);
    printf("\nIterative binary search starting");
    clock_t beginIter = clock();
    printf("\nThe number you were looking for is at %d position", iterativeBinarySearch(workArray2, randomNumber, 0, arrlen));
    clock_t endIter = clock();
    double timeSpentIter= (double) (endIter - beginIter) / CLOCKS_PER_SEC;
    printf("\nTime spent with the iterative method: %lf", timeSpentIter);
}

void recBinSearchArrayTest(int arrlen, double limit){\
    printf("\nRecursive Binary Search Test in a randomly generated floating point array with %d numbers.", arrlen);
    srand(time(NULL));
    double workArray2[arrlen];
    workArray2[0] = randGenDouble(0,limit);
    for (int i = 1; i < arrlen; i++)
        workArray2[i] = randGenDouble(workArray2[i-1], limit);
    srand(time(NULL));
    double randomNumber = workArray2[randInt(arrlen-1)];
    printf("\nThe one we are looking for: %lf", randomNumber);
    printf("\nRecursive binary search starting");
    clock_t beginRec = clock();
    printf("\nThe number you were looking for is at %d position", recursiveBinarySearch(workArray2, randomNumber, 0, arrlen));
    clock_t endRec = clock();
    double timeSpentRec = (double) (endRec - beginRec) / CLOCKS_PER_SEC;
    printf ("\nTime spent with the recursive method: %lf", timeSpentRec);
}
int main()
{
    /*srand(time(NULL));
    double workArray2[ARRLEN];
    workArray2[0] = randGenDouble(0,1000000);
    for (int i = 1; i < ARRLEN; i++)
        workArray2[i] = randGenDouble(workArray2[i-1], 1000000);
    srand(time(NULL));
    double randomNumber = workArray2[randInt(ARRLEN-1)];
    printf("\nThe one we are looking for: %lf", randomNumber);
    printf("\n\nIterative binary search starting\n");
    clock_t beginIter = clock();
    printf("\nThe number you were looking for is at %d position", iterativeBinarySearch(workArray2, randomNumber, 0, ARRLEN));
    clock_t endIter = clock();
    printf("\n\nRecursive binary search strarting\n");
    clock_t beginRec = clock();
    printf("\nThe number you were looking for is at %d position", recursiveBinarySearch(workArray2, randomNumber, 0, ARRLEN));
    clock_t endRec = clock();

    double timeSpentIter= (double) (endIter - beginIter) / CLOCKS_PER_SEC;
    printf("\n\nTime spent with the iterative method: %lf", timeSpentIter);
    double timeSpentRec = (double) (endRec - beginRec) / CLOCKS_PER_SEC;
    printf ("\nTime spent with the recursive method: %lf", timeSpentRec);*/
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

    return 0;
}
