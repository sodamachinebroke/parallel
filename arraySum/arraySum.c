#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sumArray(int array[])
{
    int sum = 0;

    for (int i = 0; i < (sizeof(array)/size_of(array[0])); i++)
    {
        sum += array[i];
    }

    return sum;
}

void *mainThread(void *_)
{
    int array[2000];
    int sum = 0;
    
}

int main(int argc, char const *argv[])
{
    pthread_t threads[20];
    for (int i = 0; i < (sizeof(threads) / sizeof(threads[0])); i++)
    {
        pthread_create(&threads[i], NULL, mainThread, NULL);
    }

    pthread_exit(NULL);

    return 0;
}
