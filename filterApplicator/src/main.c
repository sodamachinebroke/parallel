#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "copy.h"
#include "greyscale.h"

int main(int argc, char const *argv[])
{
    printf("Greyscaling Henry Cavill from cavill.bmp to cavillout.bmp\n");
    if (greyScale("cavill.bmp"))
    {
        printf("Great success!\n");
    }
    else
    {

        printf("Error, did not work.\n");
    }
    return 0;
}
