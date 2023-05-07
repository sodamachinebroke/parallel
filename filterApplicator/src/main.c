#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "copy.h"
#include "sequential.h"
#include "omp.h"

void henryCavillmodifier()
{
    printf("Modifying Henry Cavill's picture.");
    printf("First off, sequentially.\n");
    printf("Turning him greyscale from cavill.bmp to cavillgsc.bmp\n");

    { //Sequential stuff
    if (greyScale("cavill.bmp"))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    printf("Turning him into Evil Henry Cavill from cavill.bmp to cavillneg.bmp\n");
    if (turnNeg("cavill.bmp"))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    }
    
    printf("Now with OMP parallelization!\n");
    printf("Turning him greyscale from cavill.bmp to cavillgscomp.bmp\n");

    { //OMP majesticity
    if (greyScaleOmp("cavill.bmp"))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    printf("Turning him into Evil Henry Cavill from cavill.bmp to cavillnegomp.bmp\n");
    if (turnNegOmp("cavill.bmp"))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    }
}
void bigSampleModifier()
{
    printf("Modifying a random large BMP image i found.");
    printf("First off, sequentially.\n");
    printf("Turning it greyscale from big.bmp to biggsc.bmp\n");
    { //Sequential stuff
    if (greyScale("big.bmp"))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    printf("Turningh it into a nightmare from big.bmp to bigneg.bmp\n");
    if (turnNeg("big.bmp"))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    }
    printf("Now with OMP parallelization!\n");
    printf("Turning it greyscale from big.bmp to biggscomp.bmp\n");
    { //OMP majesticity
    if (greyScaleOmp("big.bmp"))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    printf("Turning it into a nightmare from big.bmp to bignegomp.bmp\n");
    if (turnNegOmp("big.bmp"))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    }
}

int main(int argc, char const *argv[])
{
    henryCavillmodifier();
    bigSampleModifier();
    printf("\nPress any key to exit!\n");
    getchar();
    return 0;
}
