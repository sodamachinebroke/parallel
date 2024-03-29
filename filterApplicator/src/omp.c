#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "commons.h"

bool turnNegOmp(const char *filename)
{
    const char *path = "images/";
    char fullInpath[100];
    char fullOutpath[100];

    sprintf(fullInpath, "%s%s", path, filename);
    sprintf(fullOutpath, "%s%s", path, addSuffix(filename, "negomp"));

    FILE *streamIn = fopen(fullInpath, "rb");
    if (streamIn == NULL)
    {
        fprintf(stderr, "Error: Failed to open input file %s\n", filename);
        return false;
    }

    // Read header pixelData
    unsigned char header[54];
    if (fread(header, sizeof(unsigned char), 54, streamIn) != 54)
    {
        fprintf(stderr, "Error: Invalid BMP header\n");
        return false;
    }

    // Get image dimensions
    int width = *(int *)&header[18];
    int height = *(int *)&header[22];
    int bit_depth = *(int *)&header[28];

    // Check if image is 24bpp
    if (bit_depth != 24)
    {
        fprintf(stderr, "Error: Invalid bit depth\n");
        return false;
    }

    // Calculate row padding in bytes
    int padding = (4 - ((width * 3) % 4)) % 4;

    // Allocate memory for pixel pixelData
    unsigned char *pixelData = (unsigned char *)malloc(sizeof(unsigned char) * width * height * 3);
    if (pixelData == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return false;
    }

    // Read pixel pixelData
    if (fread(pixelData, sizeof(unsigned char), width * height * 3, streamIn) != width * height * 3)
    {
        fprintf(stderr, "Error: Invalid pixel data\n");
        return false;
    }

    fclose(streamIn);

    // Convert to grayscale
    for (int y = 0; y < height; y++)
    {
#pragma omp parallel for
        for (int x = 0; x < width; x++)
        {
#pragma omp atomic
            int i = (y * width + x) * 3;
            unsigned char r = pixelData[i];
            unsigned char g = pixelData[i + 1];
            unsigned char b = pixelData[i + 2];
            pixelData[i] = 255 - r;
            pixelData[i + 1] = 255 - g;
            pixelData[i + 2] = 255 - b;
        }
    }

    // Write output file
    FILE *streamOut = fopen(fullOutpath, "wb");
    if (streamOut == NULL)
    {
        fprintf(stderr, "Error: Failed to open output file\n");
        free(pixelData);
        return false;
    }

    fwrite(header, sizeof(unsigned char), 54, streamOut);
    fwrite(pixelData, sizeof(unsigned char), width * height * 3, streamOut);

    fclose(streamOut);
    free(pixelData);

    return true;
}

bool greyScaleOmp(const char *filename)
{
    const char *path = "images/";
    char fullInpath[100];
    char fullOutpath[100];

    sprintf(fullInpath, "%s%s", path, filename);
    sprintf(fullOutpath, "%s%s", path, addSuffix(filename, "gscomp"));

    FILE *streamIn = fopen(fullInpath, "rb");
    if (streamIn == NULL)
    {
        fprintf(stderr, "Error: Failed to open input file %s\n", filename);
        return false;
    }

    // Read header pixelData
    unsigned char header[54];
    if (fread(header, sizeof(unsigned char), 54, streamIn) != 54)
    {
        fprintf(stderr, "Error: Invalid BMP header\n");
        return false;
    }

    // Get image dimensions
    int width = *(int *)&header[18];
    int height = *(int *)&header[22];
    int bit_depth = *(int *)&header[28];

    // Check if image is 24bpp
    if (bit_depth != 24)
    {
        fprintf(stderr, "Error: Invalid bit depth\n");
        return false;
    }

    // Calculate row padding in bytes
    int padding = (4 - ((width * 3) % 4)) % 4;
    // Allocate memory for pixel pixelData
    unsigned char *pixelData = (unsigned char *)malloc(sizeof(unsigned char) * width * height * 3);
    if (pixelData == NULL)
    {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return false;
    }

    // Read pixel pixelData
    if (fread(pixelData, sizeof(unsigned char), width * height * 3, streamIn) != width * height * 3)
    {
        fprintf(stderr, "Error: Invalid pixel data\n");
        return false;
    }

    fclose(streamIn);

    // Convert to grayscale
    for (int y = 0; y < height; y++)
    {
#pragma omp parallel for
        for (int x = 0; x < width; x++)
        {
#pragma omp atomic
            int i = (y * width + x) * 3;
            unsigned char r = pixelData[i];
            unsigned char g = pixelData[i + 1];
            unsigned char b = pixelData[i + 2];
            unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
            pixelData[i] = gray;
            pixelData[i + 1] = gray;
            pixelData[i + 2] = gray;
        }
    }

    // Write output file
    FILE *streamOut = fopen(fullOutpath, "wb");
    if (streamOut == NULL)
    {
        fprintf(stderr, "Error: Failed to open output file\n");
        free(pixelData);
        return false;
    }

    fwrite(header, sizeof(unsigned char), 54, streamOut);
    fwrite(pixelData, sizeof(unsigned char), width * height * 3, streamOut);

    fclose(streamOut);
    free(pixelData);

    return true;
}