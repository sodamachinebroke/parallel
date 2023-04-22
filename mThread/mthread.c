#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdbool.h>

bool isPrime(int num)
{
    bool flag = false;
    for (int i = 2; i < num / 2; i++)
    {
        if (num % i == 0)
        {
            flag = true;
            break;
        }
    }
    if (flag)
        return false;
    else
        return true;
}

void *countPrime(int from, int to)
{
    int n = 0;
    for (int i = from; i < to; i++)
    {
        if (isPrime(i))
            n++;
    }

    printf("Number of primes from %d to %d: %d\n", from, to, n);
}

void *primeCounterWrapper(void *_)
{
    for (int i = 0; i < 999; i += 100)
    {
        countPrime(i, i + 99);
    }
}

const int N_THREADS = 10;

int main(int argc, char *argv[])
{
    pthread_t threads[N_THREADS];
    int i;
    for (i = 0; i < N_THREADS; ++i)
    {
        pthread_create(&threads[i], NULL, primeCounterWrapper, NULL);
    }

    pthread_exit(NULL);

    return 0;
}
