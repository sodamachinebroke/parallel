#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "copy.h"
#include "greyscale.h"
#include "negative.h"

int main(int argc, char const *argv[])
{
    printf("Turning Henry Cavill greyscale from cavill.bmp to cavillgsc.bmp\n");
    if (greyScale("cavill.bmp"))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    printf("Turning Henry Cavill into Evil Henry Cavill from cavill.bmp to cavillneg.bmp\n");
    if (turnNeg("cavill.bmp"))
        printf("Great success!\n");
    else
        printf("Error, did not work.\n");
    printf("\nPress any key to exit!\n");
    getchar();
    return 0;
}
