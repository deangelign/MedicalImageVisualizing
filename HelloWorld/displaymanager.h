#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "image.h"
#include "iftMatrix.h"



typedef struct {

    int **table;
    int numberRows;
    int numberColumns;

} ColorMap;

typedef struct {

    float **table;
    int numberRows;
    int numberColumns;

} ColorMapFloat;


typedef struct {

    char referenceAxis;
    char verticalAxis;
    char horizontalAxis;
    int verticalDirection;
    int horizontalDirection;
    int slice;

    float k1;
    float k2;
    float I1;
    float I2;
    float factor;
    float bright;
    float contrast;

    //1 - grayscale
    //2 - colorMask
    //3 - colorMask proportional to gray value
    int type;

    ColorMap *rgbColorTable;
    ColorMapFloat *yCgCoColorTable;

} ViewDisplay;


void bitsAdjustment(GrayImage *grayImage,int nbits, bool saturation);
void copyColorMap(ColorMap *RGBColorTable1, ColorMap **RGBColorTable);
void copyColorMapFloat(ColorMapFloat *RGBColorTable1, ColorMapFloat **RGBColorTable);
void destroyRGBColorMap(ColorMap **RGBColorTable);
void destroyYCgCoColorMap(ColorMapFloat **YCgCoColorTable);
void convertRGBColorMap2YCgCoColorMap(ColorMap *rgbColorTable, ColorMapFloat **yCgCoColorTable,float maximumValue);
void convertYCgCoColorMap2RGBColorMap(ColorMapFloat *yCgCoColorTable, ColorMap **rgbColorTable);
ColorMap* generateRGBColorMap(MedicalImage *labelImage,int maximumValue);
ColorImage *generateColorImageFromLabelImage(GrayImage *labelImage,ColorMap *rgbColorTable);
ColorImage *generateColorImageFromLabelImage(GrayImage *grayImage, GrayImage *labelImage, ColorMapFloat *yCgCoColorTable, float maximumValue);
void normalizeGrayImage(GrayImage *grayImage);
void contrastBrightAdjustment(GrayImage *grayImage,ViewDisplay *view);
void updateContrastBrightParameters(ViewDisplay *view, float I1, float I2, float k1, float k2);
void updateContrastBrightParameters(ViewDisplay *view, float bright, float contrast);
void WidthLevelGrayImage(GrayImage *img, float b, float c,int maximumValueScene);
void NegativeGrayImage(GrayImage *img, int maximumValue);
void normalizeGrayImage(GrayImage *grayImage, float minimumValue, float maximumValueSlice,float maximumValueAllowed);
void LimiarizationGrayImage(GrayImage *img, int th, float maximumValue);
void alignVectorWithZ(float x, float y,float z, float *thetaX, float *thetaY);
void getSliceGivenVectorViewer(MedicalImage *image3D, float x, float y, float z);



#endif // DISPLAYMANAGER_H
