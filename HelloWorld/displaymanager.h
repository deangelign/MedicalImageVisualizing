#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "image.h"

typedef struct {

    char referenceAxis;
    char verticalAxis;
    char horizontalAxis;
    int verticalDirection;
    int horizontalDirection;
    int slice;

} ViewDisplay;

void bitsAdjustment(GrayImage *grayImage,int nbits, bool saturation);



#endif // DISPLAYMANAGER_H
