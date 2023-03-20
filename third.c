#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randGenInt(int min, int max)
{
    return (rand() % (max - min + 1)) + min; 
}
double randGenDouble(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

binarySearch(double * array, );


int main()
{
    srand(time(NULL));
    int workArray[5];
    workArray[0]= randGenInt(0,1000000);
    printf("%d\n", workArray[0]);
    for (int i = 1; i < 5; i++)
    {
        workArray[i] = randGenInt(workArray[i-1],1000000);
        printf("%d\n", workArray[i]);
    }
    double workArray2[50];
    workArray2[0] = randGenDouble(0,1000000);
    printf("%lf\n", workArray2[0]);
    for (int i = 1; i < 10; i++)
    {
        workArray2[i] = randGenDouble(workArray2[i-1], 1000000);
        printf("%lf\n", workArray2[i]);
    }
    
    
    return 0;
}
