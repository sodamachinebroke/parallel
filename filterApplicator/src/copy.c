#include "copy.h"
#include "commons.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool copyImage(const char *filename)
{

    const char *path = "images/";
    char fullInpath[100];
    char fullOutpath[100];

    sprintf(fullInpath, "%s%s", path, filename);
    sprintf(fullOutpath, "%s%s", path, addSuffix(filename, "out"));

    // file input begins
    FILE *streamIn = fopen(fullInpath, "rb"); // input file in binary mode
    if (streamIn == NULL)
    {
        perror("Error opening input file\n");
        return false;
    }

    FILE *streamOut = fopen(fullOutpath, "wb");
    if (streamOut == NULL)
    {
        perror("Error opening output file");
        fclose(streamIn);
        return false;
    }
    unsigned char header[54];
    unsigned char colorTable[1024];

    // BMP header read, also read color table
    fread(header, sizeof(unsigned char), 54, streamIn);
    int bit_depth = *(int *)&header[28];
    if (bit_depth <= 8)
    {
        fread(colorTable, sizeof(unsigned char), 1024, streamIn);
    }

    // read BMP pixel data

    int width = *(int *)&header[18];
    int height = *(int *)&header[22];
    int pixelSize = bit_depth <= 8 ? 1 : 3;

    unsigned char *pixelData = malloc(height * width * pixelSize);
    fread(pixelData, sizeof(unsigned char), height * width, streamIn);

    // file output begins

    // write header and color table
    fwrite(header, sizeof(unsigned char), 54, streamOut);
    if (bit_depth <= 8)
    {
        fwrite(colorTable, sizeof(unsigned char), 1024, streamOut);
    }

    // write pixel data to output

    fwrite(pixelData, sizeof(unsigned char), height * width, streamOut);

    fclose(streamIn);
    fclose(streamOut);
    return true;
}