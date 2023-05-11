#ifndef POS_H
#define POS_H
#endif

typedef struct threadData
{
    int startRow;
    int endRow;
    unsigned char *pixelData;
    int width;
    int height;
} threadData;

bool turnNegPos(const char *filename);
bool greyScalePos(const char *filename);