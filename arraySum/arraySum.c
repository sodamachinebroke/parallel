#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THRNUM 20

int sumArray(int array[], int arrSize)
{
    int sum = 0;
    for (int i = 0; i < arrSize; i++)
    {
        sum += array[i];
    }

    return sum;
}

int divEqual(int a, int arrSize)
{
    int chunkSize = arrSize / THRNUM;
    int bonus = arrSize - chunkSize * THRNUM;
    int start = 0, end = chunkSize;
    while (start < arrSize)
    {
        /* code */
    }
    
    
}

void *mainThread(void *_)
{
    int array[2000];
    for (int i = 0; i < 2000; i++)
        array[i] = i;
    printf("\n%d\n", sumArray(array, sizeof(array)/ sizeof(array[0])));
}

int main(int argc, char const *argv[])
{
    pthread_t threads[THRNUM];
    pthread_t tempthread;
    /*for (int i = 0; i < (sizeof(threads) / sizeof(threads[0])); i++)
    {

    }*/
    pthread_create(&tempthread, NULL, mainThread, NULL);

    pthread_exit(NULL);

    return 0;
}
