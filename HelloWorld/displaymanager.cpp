#include "displaymanager.h"


void bitsAdjustment(GrayImage *grayImage,int nbits, bool saturation){

    int shift = 0;
    if(nbits == 16){
        shift = 0;
    }else if(nbits == 15){
        shift = 1;
    }else if(nbits == 14){
        shift = 2;
    }else if(nbits == 13){
        shift = 3;
    }else if(nbits == 12){
        shift = 4;
    }else if(nbits == 11){
        shift = 5;
    }else if(nbits == 10){
        shift = 6;
    }else if(nbits == 9){
        shift = 7;
    }else{
        shift = 8;
    }

    if(saturation == 1){
        for(int y=0;y < grayImage->ny; y++){
            for(int x=0;x < grayImage->nx; x++){
                grayImage->val[y][x] <<=  shift;
                if(grayImage->val[y][x] >= 65535){
                    grayImage->val[y][x] = 65535;
                }
            }
        }
    }else{
        for(int y=0;y < grayImage->ny; y++){
            for(int x=0;x < grayImage->nx; x++){
                grayImage->val[y][x] <<=  shift;
            }
        }
    }
}

ColorMap* generateRGBColorMap(MedicalImage *labelImage){
    ColorMap *RGBColorTable = (ColorMap*)calloc(1,sizeof(ColorMap));
    RGBColorTable->numberRows = labelImage->maxValue+1;
    RGBColorTable->numberColumns = 3;//RGB


    RGBColorTable->table = (int **)calloc(RGBColorTable->numberRows,sizeof(int *));
    for (int i=0; i < RGBColorTable->numberRows; i++){
        RGBColorTable->table[i] = (int *)calloc(RGBColorTable->numberColumns,sizeof(int));
    }
    for(int j=0;j<RGBColorTable->numberColumns; j++){
        RGBColorTable->table[0][j] = 0;
    }

    srand(0);
    for(int i=1;i<RGBColorTable->numberRows; i++){
        for(int j=0; j<RGBColorTable->numberColumns; j++){
            RGBColorTable->table[i][j] = rand() % 256;
        }
    }

    return RGBColorTable;
}

void copyColorMap(ColorMap *RGBColorTableTarget, ColorMap **RGBColorTableSource){
    if(*RGBColorTableSource != NULL){
        destroyRGBColorMap(RGBColorTableSource);
    }
    (*RGBColorTableSource) = (ColorMap*)calloc(1,sizeof(ColorMap));
    (*RGBColorTableSource)->numberRows = RGBColorTableTarget->numberRows;
    (*RGBColorTableSource)->numberColumns = RGBColorTableTarget->numberColumns;
    (*RGBColorTableSource)->table = (int **)calloc(RGBColorTableTarget->numberRows,sizeof(int *));

    for (int i=0; i < RGBColorTableTarget->numberRows; i++){
        (*RGBColorTableSource)->table[i] = (int *)calloc(RGBColorTableTarget->numberColumns,sizeof(int));
    }

    for(int i=0;i<RGBColorTableTarget->numberRows; i++){
        for(int j=0; j<RGBColorTableTarget->numberColumns; j++){
            (*RGBColorTableSource)->table[i][j] = RGBColorTableTarget->table[i][j];
        }
    }
}

void destroyRGBColorMap(ColorMap **RGBColorTable){

    if ((*RGBColorTable) != NULL) {
        for (int i=0; i < (*RGBColorTable)->numberRows; i++){
            free((*RGBColorTable)->table[i]);
        }
        free((*RGBColorTable)->table);
        free(*RGBColorTable);
        *RGBColorTable = NULL;
    }
}

void convertRGBColorMap2YCbCrColorMap(ColorMap *rgbColorTable, ColorMap **yCbCrColorTable){

    if(*yCbCrColorTable != NULL){
        destroyRGBColorMap(yCbCrColorTable);
    }

    (*yCbCrColorTable) = (ColorMap*)calloc(1,sizeof(ColorMap));
    (*yCbCrColorTable)->numberRows = rgbColorTable->numberRows;
    (*yCbCrColorTable)->numberColumns = rgbColorTable->numberColumns;
    (*yCbCrColorTable)->table = (int **)calloc(rgbColorTable->numberRows,sizeof(int *));

    for (int i=0; i < rgbColorTable->numberRows; i++){
        (*yCbCrColorTable)->table[i] = (int *)calloc(rgbColorTable->numberColumns,sizeof(int));
    }

    for(int i=0;i<rgbColorTable->numberRows; i++){
        //https://en.wikipedia.org/wiki/YCbCr JPEG
        (*yCbCrColorTable)->table[i][0] = round(0.0 + (0.299*rgbColorTable->table[i][0]) +
                                              (0.587*rgbColorTable->table[i][1]) +
                                              (0.114*rgbColorTable->table[i][2]));

        (*yCbCrColorTable)->table[i][1] = round(128.0 - (0.168736*rgbColorTable->table[i][0]) -
                                              (0.331264*rgbColorTable->table[i][1]) +
                                              (0.5*rgbColorTable->table[i][2]));

        (*yCbCrColorTable)->table[i][2] = round(128.0 + (0.5*rgbColorTable->table[i][0]) -
                                              (0.418688*rgbColorTable->table[i][1]) -
                                              (0.081312*rgbColorTable->table[i][2]));

    }
}

void convertYCbCrColorMap2RGBColorMap(ColorMap *yCbCrColorTable, ColorMap **rgbColorTable){

    if(*rgbColorTable != NULL){
        destroyRGBColorMap(rgbColorTable);
    }

    (*rgbColorTable) = (ColorMap*)calloc(1,sizeof(ColorMap));
    (*rgbColorTable)->numberRows = yCbCrColorTable->numberRows;
    (*rgbColorTable)->numberColumns = yCbCrColorTable->numberColumns;
    (*rgbColorTable)->table = (int **)calloc(yCbCrColorTable->numberRows,sizeof(int *));

    for (int i=0; i < yCbCrColorTable->numberRows; i++){
        (*rgbColorTable)->table[i] = (int *)calloc(yCbCrColorTable->numberColumns,sizeof(int));
    }

    for(int i=0;i<yCbCrColorTable->numberRows; i++){
        //https://en.wikipedia.org/wiki/YCbCr JPEG
        (*rgbColorTable)->table[i][0] = round( (yCbCrColorTable->table[i][0]) +
                                              (0.0*yCbCrColorTable->table[i][1]) +
                                              (1.402*(yCbCrColorTable->table[i][2]-128)));

        (*rgbColorTable)->table[i][1] = round( (yCbCrColorTable->table[i][0]) -
                                              (0.344136*(yCbCrColorTable->table[i][1]-128)  ) -
                                              (0.714136*(yCbCrColorTable->table[i][2]-128)  )  );

        (*rgbColorTable)->table[i][2] = round( (yCbCrColorTable->table[i][0]) +
                                              (1.772*(yCbCrColorTable->table[i][1]-128) ) +
                                              (0*yCbCrColorTable->table[i][2]));

    }
}

ColorImage *generateColorImageFromLabelImage(GrayImage *labelImage,ColorMap *rgbColorTable){
    ColorImage *colorImage = CreateColorImage(labelImage->nx,labelImage->ny);

    for(int y=0; y<labelImage->ny; y++){
        for(int x=0; x<labelImage->nx; x++){
            colorImage->cor[y][x].val[0] = rgbColorTable->table[labelImage->val[y][x]][0];
            colorImage->cor[y][x].val[1] = rgbColorTable->table[labelImage->val[y][x]][1];
            colorImage->cor[y][x].val[2] = rgbColorTable->table[labelImage->val[y][x]][2];
        }
    }
    return colorImage;
}

ColorImage *generateColorImageFromLabelImage(GrayImage *grayImage, GrayImage *labelImage, ColorMap *yCbCrColorTable){
    ColorImage *colorImage = CreateColorImage(labelImage->nx,labelImage->ny);
    for(int y=0; y<labelImage->ny; y++){
        for(int x=0; x<labelImage->nx; x++){

            colorImage->cor[y][x].val[0] = round( (grayImage->val[y][x]) +
                                          (1.402*(yCbCrColorTable->table[labelImage->val[y][x]][2]-128)));

           colorImage->cor[y][x].val[1] = round( (grayImage->val[y][x]) -
                                                  (0.344136*(yCbCrColorTable->table[labelImage->val[y][x]][1]-128)  ) -
                                                  (0.714136*(yCbCrColorTable->table[labelImage->val[y][x]][2]-128)  )  );

           colorImage->cor[y][x].val[2] = round( (grayImage->val[y][x]) +
                                                 (1.772*(yCbCrColorTable->table[labelImage->val[y][x]][1]-128) ));
        }
    }
    return colorImage;
}

void normalizeGrayImage(GrayImage *grayImage){
    int factor = 2047;

    for(int y=0; y < grayImage->ny; y++){
        for(int x=0; x < grayImage->nx; x++){
            grayImage->val[y][x] = (((float)grayImage->val[y][x])/factor)*255;
            if(grayImage->val[y][x] > 255){
                grayImage->val[y][x] = 255;
            }

        }
    }
}
