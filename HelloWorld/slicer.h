#ifndef SLICER_H
#define SLICER_H

#include "image.h"

GrayImage *getSliceZPositive(int z, char axisVertical, int directionVertial,char axisHorizontal, int directionHorizontal, MedicalImage *image3D);
GrayImage *getSliceYPositive(int z, char axisVertical, int directionVertial,char axisHorizontal, int directionHorizontal, MedicalImage *image3D);
GrayImage *getSliceXPositive(int z, char axisVertical, int directionVertial,char axisHorizontal, int directionHorizontal, MedicalImage *image3D);
GrayImage* getSlice(char verticalAxis, int directionVertial, char horizontalAxis, int directionHorizontal, MedicalImage *image3D, int sliceDepth);

#endif // SLICER_H
