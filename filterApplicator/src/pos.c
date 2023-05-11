#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "pos.h"
#include "commons.h"



void *turnNegConv(void *threadArg)
{
    threadData *data = (threadData *)threadArg;

    // Process the rows assigned to this thread
    for (int y = data->startRow; y < data->endRow; y++)
    {
        for (int x = 0; x < data->width; x++)
        {
            int i = (y * data->width + x) * 3;
            unsigned char r = data->pixelData[i];
            unsigned char g = data->pixelData[i + 1];
            unsigned char b = data->pixelData[i + 2];
            data->pixelData[i] = 255 - r;
            data->pixelData[i + 1] = 255 - g;
            data->pixelData[i + 2] = 255 - b;
        }
    }

    pthread_exit(NULL);
}

bool turnNegPos(const char *filename)
{
    const char *path = "images/";
    char fullInpath[100];
    char fullOutpath[100];

    sprintf(fullInpath, "%s%s", path, filename);
    sprintf(fullOutpath, "%s%s", path, addSuffix(filename, "negPOS"));

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
        free(pixelData);
        return false;
    }

    fclose(streamIn);

    int threadNum = getNumberOfCores() * 10;
    pthread_t threads[threadNum];
    threadData tData[threadNum];
    int rowsperThread = height / threadNum;
    int remainingRows = height % threadNum;
    int startRow = 0;
    for (int i = 0; i < threadNum; i++)
    {
        int endRow = startRow + rowsperThread;
        if(i == threadNum - 1){
            endRow += remainingRows;
        }
        tData[i].pixelData = pixelData;
        tData[i].width = width;
        tData[i].height = height;
        tData[i].startRow = startRow;
        tData[i].endRow = endRow;
        int rc = pthread_create(&threads[i], NULL, turnNegConv, (void *)&tData[i]);
        if(rc){
            fprintf(stderr,"Error: failed to create thread %d", i);
            free(pixelData);
            return false;
        }
        startRow += rowsperThread;
    }

    for (int i = 0; i < threadNum; i++)
    {
        int rc = pthread_join(threads[i], NULL);
        if(rc){
            fprintf(stderr,"Error: failed to join thread: %d", i);
            free(pixelData);
            return false;
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

    void *greyScaleConv(void *threadArg)
{
    threadData *data = (threadData *)threadArg;

    // Process the rows assigned to this thread
    for (int y = data->startRow; y < data->endRow; y++)
    {
        for (int x = 0; x < data->width; x++)
        {
            int i = (y * data->width + x) * 3;
            unsigned char r = data->pixelData[i];
            unsigned char g = data->pixelData[i + 1];
            unsigned char b = data->pixelData[i + 2];
            unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
            data->pixelData[i] = gray;
            data->pixelData[i + 1] = gray;
            data->pixelData[i + 2] = gray;
        }
    }

    pthread_exit(NULL);
}

bool greyScalePos(const char *filename)
{
    const char *path = "images/";
    char fullInpath[100];
    char fullOutpath[100];

    sprintf(fullInpath, "%s%s", path, filename);
    sprintf(fullOutpath, "%s%s", path, addSuffix(filename, "gscPOS"));

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

    int threadNum = getNumberOfCores() * 10;
    pthread_t threads[threadNum];
    threadData tData[threadNum];
    int rowsperThread = height / threadNum;
    int remainingRows = height % threadNum;
    int startRow = 0;
    for (int i = 0; i < threadNum; i++)
    {
        int endRow = startRow + rowsperThread;
        if(i == threadNum - 1){
            endRow += remainingRows;
        }
        tData[i].pixelData = pixelData;
        tData[i].width = width;
        tData[i].height = height;
        tData[i].startRow = startRow;
        tData[i].endRow = endRow;
        int rc = pthread_create(&threads[i], NULL, greyScaleConv, (void *)&tData[i]);
        if(rc){
            fprintf(stderr,"Error: failed to create thread %d", i);
            free(pixelData);
            return false;
        }
        startRow += rowsperThread;
    }

    for (int i = 0; i < threadNum; i++)
    {
        int rc = pthread_join(threads[i], NULL);
        if(rc){
            fprintf(stderr,"Error: failed to join thread: %d", i);
            free(pixelData);
            return false;
        }
    }

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