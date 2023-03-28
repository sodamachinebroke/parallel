#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

/*int g = 0;

void *tempThread(void *vargp)
{
    int *myid = (int *)vargp;
    static int s = 0;
    ++s;
    ++g;
    printf("Thread ID: %d, Static: %d, Global: %d\n", *myid, ++s, ++g);
}*/

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
    printf("Number of primes in interval: %d", n);
}

/*void *countPrimesInInterval()
{
    int i = 0, j = 99;

    while (i <= 900 && j < 1000)
    {
        printf("Prime numbers from %d to %d: %d\n", i, j, countPrime(i, j));
        i += 100;
        j += 100;
    }
}*/

int main(int argc, char const *argv[])
{

    pthread_t tid;
    int j=0;
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&tid, NULL, countPrime(j, j+99), (void*)&tid);
        j+=100;
    }
    
    pthread_exit(NULL);
    return 0;
}
