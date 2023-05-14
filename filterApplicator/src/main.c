#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <mpi.h>
#include <time.h>

#include "copy.h"
#include "sequential.h"
#include "omp.h"
#include "pos.h"
#include "convmpi.h"

void henryCavillmodifier()
{
    printf("Modifying Henry Cavill's picture.\n");
    printf("\nFirst off, sequentially.\n");

    { // Sequential stuff
        printf("Turning him greyscale from cavill.bmp to cavillgsc.bmp. ");
        if (greyScale("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turning him into Evil Henry Cavill from cavill.bmp to cavillneg.bmp. ");
        if (turnNeg("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    }

    printf("\nNow with OMP parallelization!\n");

    { // OMP majesticity
        printf("Turning him greyscale from cavill.bmp to cavillgscomp.bmp. ");
        if (greyScaleOmp("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turning him into Evil Henry Cavill from cavill.bmp to cavillnegomp.bmp. ");
        if (turnNegOmp("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    }

    printf("\nPOSIX threads!\n");

    { // OMP majesticity
        printf("Turning him greyscale from cavill.bmp to cavillgscPOS.bmp. ");
        if (greyScalePos("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turning him into Evil Henry Cavill from cavill.bmp to cavillnegPOS.bmp. ");
        if (turnNegPos("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    }
}
void bigSampleModifier()
{
    printf("Modifying a random large BMP image I found.\n");
    printf("\nFirst off, sequentially.\n");

    { // Sequential stuff
        printf("Turning it greyscale from big.bmp to biggsc.bmp. ");
        if (greyScale("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turningh it into a nightmare from big.bmp to bigneg.bmp. ");
        if (turnNeg("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    }
    printf("\nNow with OMP parallelization!\n");

    { // OMP majesticity
        printf("Turning it greyscale from big.bmp to biggscomp.bmp. ");
        if (greyScaleOmp("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turning it into a nightmare from big.bmp to bignegomp.bmp. ");
        if (turnNegOmp("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    }

    printf("\nPOSIX threads!\n");

    { // POSIX threads
        printf("Turning it greyscale from big.bmp to biggscPOS.bmp. ");
        if (greyScalePos("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turning it into a nightmare from big.bmp to bignegPOS.bmp. ");
        if (turnNegPos("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    }
}

int main(int argc, char const *argv[])
{

    clock_t startBig = clock();
    MPI_Init(&argc, (char ***)&argv);

    bigSampleModifier();
    printf("\nUsing OpenMPI!\n");
    printf("Turning it greyscale from big.bmp to biggscMPI.bmp. "); // This has to be here, because i'm too lazy to figure it out
    if (greyScaleMPI("big.bmp", argc, (char **)argv))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    printf("Turning it into a nightmare from big.bmp to bignegMPI.bmp. ");
    if (turnNegMPI("big.bmp", argc, (char **)argv))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    clock_t endBig = clock();

    clock_t startCavill = clock();
    henryCavillmodifier();
    printf("\nUsing OpenMPI!\n");
    printf("Turning it greyscale from cavill.bmp to cavillgscMPI.bmp. "); // This has to be here, because i'm too lazy to figure it out
    if (greyScaleMPI("cavill.bmp", argc, (char **)argv))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    printf("Turning it into a nightmare from cavill.bmp to cavillnegMPI.bmp. ");
    if (turnNegMPI("cavill.bmp", argc, (char **)argv))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    clock_t endCavill = clock();
    MPI_Finalize();

    double timeSpentBig = ((double)(endBig - startBig)) / CLOCKS_PER_SEC;
    double timeSpentCavill = ((double)(endCavill - startCavill)) / CLOCKS_PER_SEC;

    printf("\nTime spent on applying the filters to Henry Cavill: %lf vs the time spent on the big sample picture: %lf\n", timeSpentCavill, timeSpentBig);
    printf("\nPress any key to exit!\n");
    getchar();
    return 0;
}