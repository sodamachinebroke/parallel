#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "sequential.h"
#include "commons.h"

bool turnNeg(const char *filename)
{

    /*These lines are for formatting. I only need to ask for a filename in the argument and
    then it looks for said filename in the images folder, then sucks it out.*/
    // begin
    const char *path = "images/";
    char fullInpath[100];
    char fullOutpath[100];

    sprintf(fullInpath, "%s%s", path, filename);
    sprintf(fullOutpath, "%s%s", path, addSuffix(filename, "neg"));
    // end

    // File reading begin
    FILE *streamIn = fopen(fullInpath, "rb");
    if (streamIn == NULL)
    {
        fprintf(stderr, "Error: Failed to open input file %s\n", filename);
        return false;
    }
    // end

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

    // Check if image is 24bit per pixel
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

    // Convert to negative
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int i = (y * width + x) * 3;    // current pixel
            unsigned char r = pixelData[i]; // assigning every pixel's color to a variable
            unsigned char g = pixelData[i + 1];
            unsigned char b = pixelData[i + 2];
            pixelData[i] = 255 - r; // these couple lines subtract our pixels' values from 255 to achieve a negative effect
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

    printf("Negative image conversion complete.\n");
    return true;
}

bool greyScale(const char *filename)
{
    const char *path = "images/";
    char fullInpath[100];
    char fullOutpath[100];

    sprintf(fullInpath, "%s%s", path, filename);
    sprintf(fullOutpath, "%s%s", path, addSuffix(filename, "gsc"));

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

    // Check if image is 24bits per pixel
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
        for (int x = 0; x < width; x++)
        {
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

    printf("Grayscale conversion complete.\n");
    return true;
}