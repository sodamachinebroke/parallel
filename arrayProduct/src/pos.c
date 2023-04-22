#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "pos.h"
#include "commons.h"

double mainArray[ARRLEN];
double product = 1.0;

double posCalc()
{
    int i, rc;
    pthread_t threads[THREADNUM];
    int thread_args[THREADNUM];

    // Fill array with random numbers between 0.1 and 10.0
    for (i = 0; i < ARRLEN; i++)
        mainArray[i] = randGenDouble(0.1, 10.0);

    // Create threads and calculate product
    for (i = 0; i < THREADNUM; i++)
    {
        thread_args[i] = i;
        rc = pthread_create(&threads[i], NULL, calcProd, &thread_args[i]);
        if (rc)
        {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Wait for threads to finish and collect results
    for (i = 0; i < THREADNUM; i++)
    {
        rc = pthread_join(threads[i], NULL);
        if (rc)
        {
            printf("ERROR: return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }
    return product;
}

void *calcProd(void *arg)
{
    int tid = *(int *)arg;
    int start = tid * ARRLEN / THREADNUM;
    int end = (tid + 1) * ARRLEN / THREADNUM;

    for (int i = start; i < end; i++)
    {
        product *= mainArray[i];
    }

    pthread_exit(NULL);
}