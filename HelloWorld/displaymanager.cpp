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

void contrastBrightAdjustment(GrayImage *grayImage, ViewDisplay *view){
    for(int y=0; y<grayImage->ny; y++){
        for (int x = 0; x < grayImage->nx; ++x) {
            if(view->I1 > grayImage->val[y][x]){
                grayImage->val[y][x] = view->k1;
            }else if(view->I1 <= grayImage->val[y][x] && grayImage->val[y][x] < view->I2){
                 //fprintf(stderr,"%d\n",grayImage->val[y][x]-view->I1);
                 grayImage->val[y][x] = view->factor*(grayImage->val[y][x]-view->I1) + view->k1;
                 //fprintf(stderr,"%f %f %f %d\n",view->factor,view->I1,view->k1,grayImage->val[y][x]-view->I1);
            }else{
                 grayImage->val[y][x] = view->k2;
            }
        }
    }
}

ColorMap* generateRGBColorMap(MedicalImage *labelImage,int maximumValue){
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
    int value;
    for(int i=1;i<RGBColorTable->numberRows; i++){
        for(int j=0; j<RGBColorTable->numberColumns; j++){
            value = rand() % (maximumValue+1);
<<<<<<< HEAD
=======
            if(value < 800){
                value += 800;
            }
            if(value > 3500){
                value - 600;
            }
>>>>>>> 249dfc9db503030ab8ab8964a0bc36b1ed79bf58
            RGBColorTable->table[i][j] = value;
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

void destroyYCgCoColorMap(ColorMapFloat **YCgCoColorTable){
    if ((*YCgCoColorTable) != NULL) {
        for (int i=0; i < (*YCgCoColorTable)->numberRows; i++){
            free((*YCgCoColorTable)->table[i]);
        }
        free((*YCgCoColorTable)->table);
        free(*YCgCoColorTable);
        *YCgCoColorTable = NULL;
    }
}

void convertRGBColorMap2YCgCoColorMap(ColorMap *rgbColorTable, ColorMapFloat **yCgCoColorTable,float maximumValue){

    if(*yCgCoColorTable != NULL){
        destroyYCgCoColorMap(yCgCoColorTable);
    }

    (*yCgCoColorTable) = (ColorMapFloat*)calloc(1,sizeof(ColorMap));
    (*yCgCoColorTable)->numberRows = rgbColorTable->numberRows;
    (*yCgCoColorTable)->numberColumns = rgbColorTable->numberColumns;
    (*yCgCoColorTable)->table = (float **)calloc(rgbColorTable->numberRows,sizeof(float *));

    for (int i=0; i < rgbColorTable->numberRows; i++){
        (*yCgCoColorTable)->table[i] = (float *)calloc(rgbColorTable->numberColumns,sizeof(float));
    }
    float r,g,b;
    for(int i=0;i<rgbColorTable->numberRows; i++){
        r = rgbColorTable->table[i][0]/maximumValue;
        g = rgbColorTable->table[i][1]/maximumValue;
        b = rgbColorTable->table[i][2]/maximumValue;


        (*yCgCoColorTable)->table[i][0] = (r/4.0) + (g/2.0) + (b/4.0)  ;
        (*yCgCoColorTable)->table[i][1] = (-r/4.0) + (g/2.0) - (b/4.0) ;
        (*yCgCoColorTable)->table[i][2] = (r/2.0)   - (b/2.0)  ;
    }
}

void convertYCgCoColorMap2RGBColorMap(ColorMapFloat *yCgCoColorTable, ColorMap **rgbColorTable){

    if(*rgbColorTable != NULL){
        destroyRGBColorMap(rgbColorTable);
    }

    (*rgbColorTable) = (ColorMap*)calloc(1,sizeof(ColorMap));
    (*rgbColorTable)->numberRows = yCgCoColorTable->numberRows;
    (*rgbColorTable)->numberColumns = yCgCoColorTable->numberColumns;
    (*rgbColorTable)->table = (int **)calloc(yCgCoColorTable->numberRows,sizeof(int *));

    for (int i=0; i < yCgCoColorTable->numberRows; i++){
        (*rgbColorTable)->table[i] = (int *)calloc(yCgCoColorTable->numberColumns,sizeof(int));
    }
    int scaling = 4095;
    for(int i=0;i<yCgCoColorTable->numberRows; i++){
        //https://en.wikipedia.org/wiki/yCgCo JPEG
        (*rgbColorTable)->table[i][0] = (yCgCoColorTable->table[i][0] - yCgCoColorTable->table[i][1] + yCgCoColorTable->table[i][2])*scaling;
        (*rgbColorTable)->table[i][1] = (yCgCoColorTable->table[i][0] + yCgCoColorTable->table[i][1])*scaling;
        (*rgbColorTable)->table[i][2] = (yCgCoColorTable->table[i][0] - yCgCoColorTable->table[i][1]- yCgCoColorTable->table[i][2])*scaling;
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

ColorImage *generateColorImageFromLabelImage(GrayImage *grayImage, GrayImage *labelImage, ColorMapFloat *yCgCoColorTable, float maximumValue){
    ColorImage *colorImage = CreateColorImage(labelImage->nx,labelImage->ny);
    float newY;
<<<<<<< HEAD
    float scalingFactor = 255;
    int colorTableRow;
=======
    int scalingFactor = 255;
    int colorTableRow;
    float alpha = 1;
>>>>>>> 249dfc9db503030ab8ab8964a0bc36b1ed79bf58
    float beta = 30.65;
    for(int y=0; y<labelImage->ny; y++){
        for(int x=0; x<labelImage->nx; x++){
           colorTableRow = labelImage->val[y][x];

           newY = ((grayImage->val[y][x])/maximumValue)*2;
           colorImage->cor[y][x].val[0] = round((newY -yCgCoColorTable->table[colorTableRow][1] + yCgCoColorTable->table[colorTableRow][2])*scalingFactor);
           colorImage->cor[y][x].val[1] = round((newY +yCgCoColorTable->table[colorTableRow][1])*scalingFactor);
           colorImage->cor[y][x].val[2] = round((newY -yCgCoColorTable->table[colorTableRow][1] - yCgCoColorTable->table[colorTableRow][2] )*scalingFactor);


<<<<<<< HEAD

//          if(colorImage->cor[y][x].val[0] > 3000){
//              colorImage->cor[y][x].val[0] -= (500);
//          }
//          if(colorImage->cor[y][x].val[1] > 3000){
//              colorImage->cor[y][x].val[1] -= (500);
//          }
//          if(colorImage->cor[y][x].val[2] > 3000){
//              colorImage->cor[y][x].val[2] -= (500);
//          }

=======
>>>>>>> 249dfc9db503030ab8ab8964a0bc36b1ed79bf58
          colorImage->cor[y][x].val[0] = colorTableRow==0?0:log(colorImage->cor[y][x].val[0]+1)*beta;
          colorImage->cor[y][x].val[1] = colorTableRow==0?0:log(colorImage->cor[y][x].val[1]+1)*beta;
          colorImage->cor[y][x].val[2] = colorTableRow==0?0:log(colorImage->cor[y][x].val[2]+1)*beta;
        }
    }
    return colorImage;
}

void normalizeGrayImage(GrayImage *img, float minimumValue, float maximumValueSlice,float maximumValueAllowed){
    float I1, I2, K1, K2;
    float val;
    int x,y;

    I1 = minimumValue;
    I2 = maximumValueSlice;
    K1 = 0;
    K2 = maximumValueAllowed;

    for (x = 0; x < img->nx; x++)
        for (y = 0; y < img->ny; y++){
                val = img->val[y][x];
                if (val < I1)
                    img->val[y][x] = K1;
                else
                if (val >= I2)
                    img->val[y][x] = K2;
                else
                    img->val[y][x] = ((K2 - K1)/(I2 - I1))*(val - I1)+K1;
            }
}

void  updateContrastBrightParameters(ViewDisplay *view, float I1, float I2, float k1, float k2){
    view->I1 = I1;
    view->I2 = I2;
    view->k1 = k1;
    view->k2 = k2;
    view->contrast = I2-I1;
    view->bright = (I1+I2)/2.0;
    if(I2-I1 > 0){
        view->factor = (k2-k1)/(I2-I1);
    }else{
        view->factor = (k2-k1)/(0.00001);
    }
}

void updateContrastBrightParameters(ViewDisplay *view, float bright, float contrast){

    view->contrast = contrast;
    view->bright = bright;
    view->I1 = view->bright - (view->contrast/2);
    view->I2 = view->contrast - view->I1;

    if(view->I2-view->I1 > 0){
        view->factor = (view->k2-view->k1)/(view->I2-view->I1);
    }else{
        view->factor = (view->k2-view->k1)/(0.00001);
    }
}

void WidthLevelGrayImage(GrayImage *img, float b, float c, int maximumValueScene){

    //GrayImage *imgOut = CreateGrayImage(img->nx,img->ny);
    float I1, I2;
    float K1, K2;
    int x,y,val;

    I1 = (2*b - c)/2;
    I2 = c + I1;
    K1 = 0;
    K2 = maximumValueScene;

    for (x = 0; x < img->nx; x++){
        for (y = 0; y < img->ny; y++){
            val = img->val[y][x];
            if (val < I1){
                img->val[y][x] = K1;
            }
            else
            if (val >= I2){
                img->val[y][x] = K2;
            }
            else{
                img->val[y][x] = (((K2 - K1)/(I2 - I1)))*(val - I1)+K1;
            }
        }
    }
}

void NegativeGrayImage(GrayImage *img, int maximumValue){
    int I1, I2, K1, K2;
    int x,y,val;
    I1 = 0;
    I2 = maximumValue;
    K1 = I2;
    K2 = I1;
    for (x = 0; x < img->nx; x++){
        for (y = 0; y < img->ny; y++){
            val = img->val[y][x];
            if (val < I1)
                img->val[y][x] = K1;
            else
                if (val >= I2)
                    img->val[y][x] = K2;
                else
                    img->val[y][x] = ((K2 - K1)/(I2 - I1))*(val - I1)+K1;
        }
    }
}

void LimiarizationGrayImage(GrayImage *img, int th, float maximumValue){
    GrayImage *imgOut = CreateGrayImage(img->nx,img->ny);
    float I1, I2, K1, K2;
    int x,y,val;

    I1 = th;
    I2 = th;
    K1 = 0;
    K2 = maximumValue;
    imgOut->Imax = K2;

    for (x = 0; x < img->nx; x++)
        for (y = 0; y < img->ny; y++){
            val = img->val[y][x];
            if (val < I1)
                imgOut->val[y][x] = K1;
            else
            if (val >= I2)
                imgOut->val[y][x] = K2;
            else
                imgOut->val[y][x] = ((K2 - K1)/(I2 - I1))*(val - I1)+K1;
        }
}
<<<<<<< HEAD


float computeVolumeDiagonal(int nx,int ny, int nz){
    return sqrt((nx*nx) + (ny*ny) + (nz*nz));
}

void getSliceGivenVectorViewer(MedicalImage *image3D, float x, float y, float z){
/*    float thetaX = 0;
    float thetaY = 0;
    alignVectorWithZ(x,y,z,&thetaX,&thetaY);
    Matrix* transformation = createIdentityMatrix(4);
    Matrix* inverseTransformation = createIdentityMatrix(4);
    Matrix* allRotations = createIdentityMatrix(4);
    Matrix* translation = createIdentityMatrix(4);

    Matrix* ry = createRotationMatrix(thetaY, 'y');
    Matrix* rx = createRotationMatrix(thetaX, 'x');
    MatrixMultiplication(ry,rx,allRotations,'n','n');

    applyTranslation(-157.0/2.0,-255.0/2.0,-255/2.0,translation);
    MatrixMultiplication(allRotations,translation,transformation,'n','n');
    printMatrix(transformation);
    applyTranslation(157.0/2.0,255.0/2.0,255/2.0,transformation);
    printMatrix(transformation);
    copyMatrix(transformation,&inverseTransformation);
    printMatrix(inverseTransformation);
    invertMatrix(inverseTransformation);
    printMatrix(inverseTransformation);
    printMatrix(transformation);

    Matrix* viewTransformed = createMatrix(6,4);
    Matrix* viewMatrix = createMatrix(3,2);
    Matrix* faces_normalVectors = createMatrix(6,4);
    //front z
    faces_normalVectors->values[0] = 0;
    faces_normalVectors->values[1] = 0;
    faces_normalVectors->values[2] = -1;
    faces_normalVectors->values[3] = 0;
    //back z
    faces_normalVectors->values[4] = 0;
    faces_normalVectors->values[5] = 0;
    faces_normalVectors->values[6] = 1;
    faces_normalVectors->values[7] = 0;
    //front y
    faces_normalVectors->values[8] = 0;
    faces_normalVectors->values[9] = -1;
    faces_normalVectors->values[10] = 0;
    faces_normalVectors->values[11] = 0;
    //back y
    faces_normalVectors->values[12] = 0;
    faces_normalVectors->values[13] = 1;
    faces_normalVectors->values[14] = 0;
    faces_normalVectors->values[15] = 0;
    //front x
    faces_normalVectors->values[16] = -1;
    faces_normalVectors->values[17] = 0;
    faces_normalVectors->values[18] = 0;
    faces_normalVectors->values[19] = 0;
    //back x
    faces_normalVectors->values[20] = 1;
    faces_normalVectors->values[21] = 0;
    faces_normalVectors->values[22] = 0;
    faces_normalVectors->values[23] = 0;

//    MatrixMultiplication(faces_normalVectors,transformation,,viewTransformed,'n','s');
//    viewMatrix->values[0] = -viewTransformed->values[2];
//    viewMatrix->values[1] = -viewTransformed->values[6];
//    viewMatrix->values[2] = -viewTransformed->values[10];
//    viewMatrix->values[3] = -viewTransformed->values[14];
//    viewMatrix->values[4] = -viewTransformed->values[18];
//    viewMatrix->values[5] = -viewTransformed->values[22];
//    printMatrix(viewMatrix);

    GrayImage*sliceTransformed = CreateGrayImage(255,255);
    int sliceFrontZ = 0;
    if(viewMatrix->values[0] > 0.01){
        int shift = image3D->nx;
        Matrix *pointsCoord = createMatrix(image3D->nx*image3D->ny,4);
        Matrix *pointsCoordT = createMatrix(image3D->nx*image3D->ny,4);
        Matrix *XYCoordMMQ = createMatrix(image3D->nx*image3D->ny,2);
        Matrix *ZCoordMMQ = createMatrix(image3D->nx*image3D->ny,1);
        int k=0;
        for (int y=0;y < image3D->ny; y++){
            for (int x=0;x < image3D->nx; x++){
                pointsCoord->values[k] = x;
                pointsCoord->values[k+1] = y;
                pointsCoord->values[k+2] = sliceFrontZ;
                pointsCoord->values[k+3] = 1;
                k = k + 4;
            }
        }
        MatrixMultiplication(pointsCoord,transformation,pointsCoordT,'n','s');
        printMatrix(pointsCoordT);

        k=0;
        int l=0;
        int m=0;
        for (int i=0;i < image3D->nx*image3D->ny; i++){
            XYCoordMMQ->values[k] = pointsCoordT->values[k];
            XYCoordMMQ->values[k+1] = pointsCoordT->values[k+1];
            ZCoordMMQ->values[k];
        }


    }else if(viewMatrix->values[0] > 0.01){

    }





    //int x0=0;
    //int y0=0;
    //int z0 = 10;
    //int w = 1;

//    float newX = transformation->values[0]*x0 + transformation->values[1]*y0 + transformation->values[2]*z0 + transformation->values[3]*w;
//    float newY = transformation->values[4]*x0 + transformation->values[5]*y0 + transformation->values[6]*z0 + transformation->values[7]*w;
//    float newZ = transformation->values[8]*x0 + transformation->values[9]*y0 + transformation->values[10]*z0 + transformation->values[11]*w;
//    float newW = transformation->values[12]*x0 + transformation->values[13]*y0 + transformation->values[14]*z0 + transformation->values[15]*w;

//    fprintf(stderr,"%f %f %f %f\n",newX,newY,newZ,newW);*/
}


=======
>>>>>>> 249dfc9db503030ab8ab8964a0bc36b1ed79bf58
