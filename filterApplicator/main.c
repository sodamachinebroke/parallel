#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    FILE *streamIn;
    streamIn = fopen("images/cavill.bmp", "rb"); // input file in binary mode
    if (streamIn == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    unsigned char header[54];
    unsigned char colorTable[4096];
    for (int i = 0; i < 54; i++)
    {
        header[i] = getc(streamIn);
    }
    int width = *(int *)&header[18];
    int height = *(int *)&header[22];
    int bitDepth = *(int *)&header[28];
    if (bitDepth <= 8) {
        fread(colorTable, sizeof(unsigned char), 1024, streamIn);
    }
    unsigned char buf[height * width];
    fread(buf, sizeof(unsigned char), (height * width), streamIn);
    fclose(streamIn);

    FILE *fo = fopen("images/cavillout.bmp", "wb"); // output file in binary mode
    if (fo == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }
    fwrite(header, sizeof(unsigned char), 54, fo);
    if (bitDepth <= 8) {
        fwrite(colorTable, sizeof(unsigned char), 1024, fo);
    }
    fwrite(buf, sizeof(unsigned char), (height * width), fo);
    fclose(fo);
    return 0;
}
