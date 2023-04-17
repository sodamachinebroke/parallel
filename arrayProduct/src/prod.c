#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARRLEN 20

double randGenDouble(double min, double max) // need this to generate a random double
{
    double range = (max - min);
    double div = RAND_MAX / (range / 2);
    return min + (rand() / div);
}

void divideArray(double arr[], int start, int end, int num_parts)
{
    int length = end - start + 1;
    int part_size = length / num_parts;
    int remainder = length % num_parts;

    if (num_parts == 1)
    {
        // Base case: the array cannot be divided any further
        printf("Array will not be divided then. Here are the contents.\n");
        for (int i = start; i <= end; i++)
            printf("%lf\n", arr[i]);
    }
    else
    {
        // Recursive case: divide the array into parts
        int part_end = start + part_size - 1;
        for (int i = 1; i <= num_parts; i++)
        {
            int part_start = start + (i - 1) * part_size;
            if (i == num_parts)
            {
                part_end += remainder;
            }
            printf("Part %d: ", i);
            for (int j = part_start; j <= part_end; j++)
            {
                printf("%lf ", arr[j]);
            }
            printf("\n");
            divideArray(arr, part_start, part_end, num_parts - 1);
            part_end = part_start + part_size - 1;
        }
    }
}

void arrayPrint(){
    double array[ARRLEN];
    for (int i = 0; i < ARRLEN; i++)
    {
        array[i] = randGenDouble(0.0, 1000.0 );   
    }
    divideArray(array, 0, ARRLEN, 3);
    
}

double seqCalc()
{
    srand(time(NULL));
    double mainArray[ARRLEN];
    for (int i = 0; i < ARRLEN; i++)
    {
        mainArray[i] = randGenDouble(0.0, 1000.0);
    }
    double prod = mainArray[0];
    for (int i = 1; i < ARRLEN; i++)
    {
        prod *= mainArray[i];
    }
    return prod;
}

int main(int argc, char const *argv[])
{
    double mainArray[ARRLEN];
    printf("Szekvencialis szorzas: %lf\n", seqCalc());
    printf("Divide array into equal parts: ");
    arrayPrint();
    return 0;
}
