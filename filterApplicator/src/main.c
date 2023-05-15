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

void henryCavillmodifier(double *timeArray)
{
    printf("Modifying Henry Cavill's picture.\n");
    printf("\nFirst off, sequentially.\n");

    { // Sequential stuff
    clock_t startGSC = clock();
        printf("Turning him greyscale from cavill.bmp to cavillgsc.bmp. ");
        if (greyScale("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    clock_t endGSC=clock();
    timeArray[0] = ((double)(endGSC - startGSC)) / CLOCKS_PER_SEC;

    clock_t startNeg = clock();
        printf("Turning him into Evil Henry Cavill from cavill.bmp to cavillneg.bmp. ");
        if (turnNeg("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    clock_t endNeg = clock();
    timeArray[1] = ((double)(endNeg - startNeg)) / CLOCKS_PER_SEC;
    }

    printf("\nNow with OMP parallelization!\n");

    { // OMP majesticity
        printf("Turning him greyscale from cavill.bmp to cavillgscomp.bmp. ");
        clock_t startGSC = clock();

        if (greyScaleOmp("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        clock_t endGSC=clock();
        timeArray[2] = ((double)(endGSC - startGSC)) / CLOCKS_PER_SEC;
        printf("Turning him into Evil Henry Cavill from cavill.bmp to cavillnegomp.bmp. ");
        clock_t startNeg = clock();
        if (turnNegOmp("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
            clock_t endNeg = clock();
    timeArray[3] = ((double)(endNeg - startNeg)) / CLOCKS_PER_SEC;
    }

    printf("\nPOSIX threads!\n");

    { // OMP majesticity
        printf("Turning him greyscale from cavill.bmp to cavillgscPOS.bmp. ");
        clock_t startGSC = clock();
        if (greyScalePos("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        clock_t endGSC=clock();
        timeArray[4] = ((double)(endGSC - startGSC)) / CLOCKS_PER_SEC;
        printf("Turning him into Evil Henry Cavill from cavill.bmp to cavillnegPOS.bmp. ");
        clock_t startNeg = clock();
        if (turnNegPos("cavill.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
            clock_t endNeg = clock();
    timeArray[5] = ((double)(endNeg - startNeg)) / CLOCKS_PER_SEC;
    }
}
void bigSampleModifier(double *timeArray)
{
    printf("Modifying a random large BMP image I found.\n");
    printf("\nFirst off, sequentially.\n");

    { // Sequential stuff
        printf("Turning it greyscale from big.bmp to biggsc.bmp. ");
        clock_t startGSC=clock();
        if (greyScale("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        clock_t endGSC=clock();
        timeArray[0] = ((double)(endGSC - startGSC)) / CLOCKS_PER_SEC;
        printf("Turning it into a nightmare from big.bmp to bigneg.bmp. ");
        clock_t startNeg = clock();
        if (turnNeg("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        clock_t endNeg = clock();
        timeArray[1] = ((double)(endNeg - startNeg)) / CLOCKS_PER_SEC;
    }
    printf("\nNow with OMP parallelization!\n");

    { // OMP majesticity
        printf("Turning it greyscale from big.bmp to biggscomp.bmp. ");
        clock_t startGSC=clock();
        if (greyScaleOmp("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        clock_t endGSC = clock();
        timeArray[2] = ((double)(endGSC - startGSC)) / CLOCKS_PER_SEC;
        printf("Turning it into a nightmare from big.bmp to bignegomp.bmp. ");
        clock_t startNeg = clock();
        if (turnNegOmp("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
            clock_t endNeg = clock();
        timeArray[3] = ((double)(endNeg - startNeg)) / CLOCKS_PER_SEC;
    }

    printf("\nPOSIX threads!\n");

    { // POSIX threads
        printf("Turning it greyscale from big.bmp to biggscPOS.bmp. ");
        clock_t startGSC=clock();
        if (greyScalePos("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        clock_t endGSC = clock();
        timeArray[4] = ((double)(endGSC - startGSC)) / CLOCKS_PER_SEC;
        printf("Turning it into a nightmare from big.bmp to bignegPOS.bmp. ");
        clock_t startNeg = clock();
        if (turnNegPos("big.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        clock_t endNeg = clock();
        timeArray[5] = ((double)(endNeg - startNeg)) / CLOCKS_PER_SEC;
    }
}

int main(int argc, char const *argv[])
{
    MPI_Init(&argc, (char ***)&argv);
    double cavillArray[8];
    double bigArray[8];
    /*printf("Modifying a random large BMP image I found.\n");
    printf("\nFirst off, sequentially.\n");

    { // Sequential stuff
        printf("Turning it greyscale from leaves.bmp to leavesgsc.bmp. ");
        if (greyScale("leaves.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turningh it into a nightmare from leaves.bmp to leavesneg.bmp. ");
        if (turnNeg("leaves.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    }
    printf("\nNow with OMP parallelization!\n");

    { // OMP majesticity
        printf("Turning it greyscale from leaves.bmp to leavesgscomp.bmp. ");
        if (greyScaleOmp("leaves.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turning it into a nightmare from leaves.bmp to leavesnegomp.bmp. ");
        if (turnNegOmp("leaves.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    }

    printf("\nPOSIX threads!\n");

    { // POSIX threads
        printf("Turning it greyscale from leaves.bmp to leavesgscPOS.bmp. ");
        if (greyScalePos("leaves.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turning it into a nightmare from leaves.bmp to leavesnegPOS.bmp. ");
        if (turnNegPos("leaves.bmp"))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");

        printf("\nUsing OpenMPI!\n");
        printf("Turning it greyscale from leaves.bmp to leavesgscMPI.bmp. "); // This has to be here, because i'm too lazy to figure it out
        if (greyScaleMPI("leaves.bmp", argc, (char **)argv))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        printf("Turning it into a nightmare from leaves.bmp to leavesnegMPI.bmp. ");
        if (turnNegMPI("leaves.bmp", argc, (char **)argv))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
    }*/

    clock_t startBig = clock();
        bigSampleModifier(bigArray);
        printf("\nUsing OpenMPI!\n");
        clock_t startGSC = clock();
        printf("Turning it greyscale from big.bmp to biggscMPI.bmp. "); // This has to be here, because i'm too lazy to figure it out
        
        if (greyScaleMPI("big.bmp", argc, (char **)argv))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        clock_t endGSC=clock();
        bigArray[6] = ((double)(endGSC - startGSC)) / CLOCKS_PER_SEC;
        printf("Turning it into a nightmare from big.bmp to bignegMPI.bmp. ");
        clock_t startNeg = clock();
        if (turnNegMPI("big.bmp", argc, (char **)argv))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        clock_t endNeg = clock();
        bigArray[7] = ((double)(endNeg - startNeg)) / CLOCKS_PER_SEC;
        clock_t endBig = clock();

        clock_t startCavill = clock();
        henryCavillmodifier(cavillArray);
        printf("\nUsing OpenMPI!\n");
        printf("Turning it greyscale from cavill.bmp to cavillgscMPI.bmp. "); // This has to be here, because i'm too lazy to figure it out
        startGSC = clock();
        if (greyScaleMPI("cavill.bmp", argc, (char **)argv))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        endGSC=clock();
        cavillArray[6] = ((double)(endGSC - startGSC)) / CLOCKS_PER_SEC;
        printf("Turning it into evil Henry Cavill from cavill.bmp to cavillnegMPI.bmp. ");
        startNeg = clock();
        if (turnNegMPI("cavill.bmp", argc, (char **)argv))
            printf("Great success!\n");
        else
            printf("Error, did not work.\n");
        endNeg = clock();
        cavillArray[7] = ((double)(endNeg - startNeg)) / CLOCKS_PER_SEC;
        clock_t endCavill = clock();


    double timeSpentBig = ((double)(endBig - startBig)) / CLOCKS_PER_SEC;
    double timeSpentCavill = ((double)(endCavill - startCavill)) / CLOCKS_PER_SEC;

    printf("\nTime spent on applying the filters to Henry Cavill: %lf vs the time spent on the big sample picture: %lf\n", timeSpentCavill, timeSpentBig);
    for (int i = 0; i < 8; i++)
    {
        printf("\n %lf", cavillArray[i]);
    }
    for (int i = 0; i < 8; i++)
    {
        printf("\n %lf", bigArray[i]);
    }

    FILE* file = fopen("diagnostics.txt", "w");
    fprintf(file, "Henry Cavill\n");
    for (int i = 0; i < 8; i++)
    {
        fprintf(file, "%lf\n", cavillArray[i]);
        
    }
    fprintf(file, "Big Sample Image\n");
    for (int i = 0; i < 8; i++)
    {
        fprintf(file, "%lf\n", bigArray[i]);
        
    }

    fclose(file);
    
    
    printf("\nPress any key to exit!\n");
    getchar();
    MPI_Finalize();
    return 0;
}