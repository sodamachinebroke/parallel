#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <mpi.h>

#include "copy.h"
#include "sequential.h"
#include "omp.h"
#include "pos.h"
#include "convmpi.h"

void henryCavillmodifier()
{
    printf("Modifying Henry Cavill's picture.\n");
    printf("First off, sequentially.\n");

    { // Sequential stuff
        printf("Turning him greyscale from cavill.bmp to cavillgsc.bmp\n");
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

    { // OMP majesticity
        printf("Turning him greyscale from cavill.bmp to cavillgscomp.bmp\n");
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

    printf("POSIX threads!\n");

    { // OMP majesticity
        printf("Turning him greyscale from cavill.bmp to cavillgscPOS.bmp\n");
        if (greyScalePos("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turning him into Evil Henry Cavill from cavill.bmp to cavillnegPOS.bmp\n");
        if (turnNegPos("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    }
}
void bigSampleModifier()
{
    printf("Modifying a random large BMP image I found.\n");
    printf("First off, sequentially.\n");

    { // Sequential stuff
        printf("Turning it greyscale from big.bmp to biggsc.bmp\n");
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

    { // OMP majesticity
        printf("Turning it greyscale from big.bmp to biggscomp.bmp\n");
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

    printf("POSIX threads!\n");

    { // POSIX threads
        printf("Turning it greyscale from big.bmp to biggscPOS.bmp\n");
        if (greyScalePos("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turning it into a nightmare from big.bmp to bignegPOS.bmp\n");
        if (turnNegPos("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    }
}

int main(int argc, char const *argv[])
{

    MPI_Init(&argc, (char ***)&argv);

    bigSampleModifier();
    printf("Turning it greyscale from big.bmp to biggscMPI.bmp\n"); // This has to be here, because i'm too lazy to figure it out
    if (greyScaleMPI("big.bmp", argc, (char **)argv))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    printf("Turning it into a nightmare from big.bmp to bignegMPI.bmp\n");
    if (turnNegMPI("big.bmp", argc, (char **)argv))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");


    henryCavillmodifier();
    printf("Turning it greyscale from cavill.bmp to cavillgscMPI.bmp\n"); // This has to be here, because i'm too lazy to figure it out
    if (greyScaleMPI("cavill.bmp", argc, (char **)argv))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    printf("Turning it into a nightmare from cavill.bmp to cavillnegMPI.bmp\n");
    if (turnNegMPI("cavill.bmp", argc, (char **)argv))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    MPI_Finalize();
    printf("\nPress any key to exit!\n");
    getchar();
    return 0;
}