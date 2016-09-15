#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "image.h"



typedef struct {

    int **table;
    int numberRows;
    int numberColumns;

} ColorMap;

typedef struct {

    char referenceAxis;
    char verticalAxis;
    char horizontalAxis;
    int verticalDirection;
    int horizontalDirection;
    int slice;

    //1 - grayscale
    //2 - colorMask
    //3 - colorMask proportional to gray value
    int type;

    ColorMap *rgbColorTable;
    ColorMap *yCbCrColorTable;

} ViewDisplay;


void bitsAdjustment(GrayImage *grayImage,int nbits, bool saturation);
void copyColorMap(ColorMap *RGBColorTable1, ColorMap **RGBColorTable);
void destroyRGBColorMap(ColorMap **RGBColorTable);
void convertRGBColorMap2YCbCrColorMap(ColorMap *rgbColorTable, ColorMap **yCbCrColorTable);
void convertYCbCrColorMap2RGBColorMap(ColorMap *yCbCrColorTable, ColorMap **rgbColorTable);
ColorMap* generateRGBColorMap(MedicalImage *labelImage);
ColorImage *generateColorImageFromLabelImage(GrayImage *labelImage,ColorMap *rgbColorTable);
ColorImage *generateColorImageFromLabelImage(GrayImage *grayImage, GrayImage *labelImage, ColorMap *yCbCrColorTable);
void normalizeGrayImage(GrayImage *grayImage);


#endif // DISPLAYMANAGER_H
