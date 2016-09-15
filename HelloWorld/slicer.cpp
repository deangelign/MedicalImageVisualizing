#include "slicer.h"


GrayImage *getSliceZPositive(int z, char axisVertical, int directionVertical,char axisHorizontal, int directionHorizontal, MedicalImage *image3D) {
    int x,y;
    int indexX,indexY;
    GrayImage *slice = NULL;


    if(axisVertical == 'y'){
        if(axisHorizontal == 'x'){
            slice = CreateGrayImage(image3D->nx,image3D->ny);
            if(directionVertical == 1 && directionHorizontal == 1){
                for(y=0; y < image3D->ny ; y++){
                    for(x=0; x < image3D->nx; x++){
                        slice->val[y][x] = image3D->val[z][y][x];
                    }
                }
            }

            else if(directionVertical == -1 && directionHorizontal == 1){
                indexY = 0;
                for(y=image3D->ny-1; y >= 0 ; y--){
                    for(x=0; x < image3D->nx; x++){
                        slice->val[indexY][x] = image3D->val[z][y][x];
                    }
                    indexY++;
                }
            }

            else if(directionVertical == -1 && directionHorizontal == -1){
                indexY = 0;
                indexX = 0;
                for(y=image3D->ny-1; y >= 0 ; y--){
                    for(x=image3D->nx-1; x >= 0; x--){
                        slice->val[indexY][indexX] = image3D->val[z][y][x];
                        indexX++;
                    }
                    indexX = 0;
                    indexY++;
                }
            }

            else if(directionVertical == 1 && directionHorizontal == -1){
                indexX = 0;
                for(y=0; y < image3D->ny ; y++){
                    for(x=image3D->nx-1; x >= 0; x--){
                        slice->val[y][indexX] = image3D->val[z][y][x];
                        indexX++;
                    }
                    indexX = 0;
                }
            }else{
                DestroyGrayImage(&slice);
                fprintf(stdout,"Error: invalid axes orientation %d %d.\n",directionHorizontal, directionVertical);
            }

        }else{
            fprintf(stdout,"Error: invalid axis %c.\n",axisHorizontal);
        }
    }else if(axisVertical == 'x') {
        if (axisHorizontal == 'y') {

            slice = CreateGrayImage(image3D->ny, image3D->nx);
            if (directionVertical == 1 && directionHorizontal == 1) {
                for (y = 0; y < image3D->ny; y++) {
                    for (x = 0; x < image3D->nx; x++) {
                        slice->val[x][y] = image3D->val[z][y][x];
                    }
                }
            }

            else if (directionVertical == -1 && directionHorizontal == 1) {
                indexY = 0;
                for (y = image3D->ny - 1; y >= 0; y--) {
                    for (x = 0; x < image3D->nx; x++) {
                        slice->val[x][indexY] = image3D->val[z][y][x];
                    }
                    indexY++;
                }
            }

            else if (directionVertical == -1 && directionHorizontal == -1) {
                indexY = 0;
                indexX = 0;
                for (y = image3D->ny - 1; y >= 0; y--) {
                    for (x = image3D->nx - 1; x >= 0; x--) {
                        slice->val[indexX][indexY] = image3D->val[z][y][x];
                        indexX++;
                    }
                    indexX = 0;
                    indexY++;
                }
            }

            else if (directionVertical == 1 && directionHorizontal == -1) {
                indexX = 0;
                for (y = 0; y < image3D->ny; y++) {
                    for (x = image3D->nx - 1; x >= 0; x--) {
                        slice->val[indexX][y] = image3D->val[z][y][x];
                        indexX++;
                    }
                    indexX = 0;
                }
            } else {
                fprintf(stdout, "Error: invalid axes orientation %d %d.\n", directionHorizontal, directionVertical);
                DestroyGrayImage(&slice);
            }

        } else {
            fprintf(stdout, "Error: invalid axis %c.\n", axisHorizontal);
        }
    }else{
        fprintf(stdout,"Error: invalid axis %c.\n",axisVertical);
    }

    return slice;

}

GrayImage *getSliceYPositive(int y, char axisVertical, int directionVertical,char axisHorizontal, int directionHorizontal, MedicalImage *image3D){
    int x,z;
    int indexX,indexZ;
    GrayImage *slice = NULL;

    if(axisVertical == 'z'){
        if(axisHorizontal == 'x'){
            slice = CreateGrayImage(image3D->nx,image3D->nz);
            if(directionVertical == 1 && directionHorizontal == 1){
                for(z=0; z < image3D->nz ; z++){
                    for(x=0; x < image3D->nx; x++){
                        slice->val[z][x] = image3D->val[z][y][x];
                    }
                }

            }
            else if(directionVertical == -1 && directionHorizontal == 1){
                indexZ = 0;
                for(z=image3D->nz-1; z >= 0 ; z--){
                    for(x=0; x < image3D->nx; x++){
                        slice->val[indexZ][x] = image3D->val[z][y][x];
                    }
                    indexZ++;
                }
            }

            else if(directionVertical == -1 && directionHorizontal == -1){
                indexZ = 0;
                indexX = 0;
                for(z=image3D->nz-1; z >= 0 ; z--){
                    for(x=image3D->nx-1; x >= 0; x--){
                        slice->val[indexZ][indexX] = image3D->val[z][y][x];
                        indexX++;
                    }
                    indexX = 0;
                    indexZ++;
                }
            }

            else if(directionVertical == 1 && directionHorizontal == -1){
                indexX = 0;
                for(z=0; z < image3D->nz ; z++){
                    for(x=image3D->nx-1; x >= 0; x--){
                        slice->val[z][indexX] = image3D->val[z][y][x];
                        indexX++;
                    }
                    indexX = 0;
                }
            }else{
                DestroyGrayImage(&slice);
                fprintf(stdout,"Error: invalid axes orientation %d %d.\n",directionHorizontal, directionVertical);
            }

        }else{
            fprintf(stdout,"Error: invalid axis %c.\n",axisHorizontal);
        }
    }else if(axisVertical == 'x'){
        if(axisHorizontal == 'z') {
            slice = CreateGrayImage(image3D->nz, image3D->nx);
            if (directionVertical == 1 && directionHorizontal == 1) {
                for (z = 0; z < image3D->nz; z++) {
                    for (x = 0; x < image3D->nx; x++) {
                        slice->val[x][z] = image3D->val[z][y][x];
                    }
                }
            }

            else if (directionVertical == -1 && directionHorizontal == 1) {
                indexZ = 0;
                for (z = image3D->nz - 1; z >= 0; z--) {
                    for (x = 0; x < image3D->nx; x++) {
                        slice->val[x][indexZ] = image3D->val[z][y][x];
                    }
                    indexZ++;
                }
            }

            else if (directionVertical == -1 && directionHorizontal == -1) {
                indexZ = 0;
                indexX = 0;
                for (z = image3D->nz - 1; z >= 0; z--) {
                    for (x = image3D->nx - 1; x >= 0; x--) {
                        slice->val[indexX][indexZ] = image3D->val[z][y][x];
                        indexX ++;
                    }
                    indexX = 0;
                    indexZ++;
                }
            }

            else if (directionVertical == 1 && directionHorizontal == -1) {
                indexX = 0;
                for (z = 0; z < image3D->nz; z++) {
                    for (x = image3D->nx - 1; x >= 0; x--) {
                        slice->val[indexX][z] = image3D->val[z][y][x];
                        indexX++;
                    }
                    indexX = 0;
                }
            } else {
                fprintf(stdout, "Error: invalid axes orientation %d %d.\n", directionHorizontal, directionVertical);
                DestroyGrayImage(&slice);
            }
        }else{
            fprintf(stdout, "Error: invalid axis %c.\n", axisHorizontal);
        }
    }else{
        fprintf(stdout,"Error: invalid axis %c.\n",axisVertical);
    }

    return slice;
}

GrayImage *getSliceXPositive(int x, char axisVertical, int directionVertical,char axisHorizontal, int directionHorizontal, MedicalImage *image3D){
    int y,z;
    int indexY, indexZ;
    GrayImage *slice = NULL;

    if(axisVertical == 'y'){
        if(axisHorizontal == 'z'){
            slice = CreateGrayImage(image3D->nz,image3D->ny);
            if(directionVertical == 1 && directionHorizontal == 1){
                for(y=0; y < image3D->ny ; y++){
                    for(z=0; z < image3D->nz; z++){
                        slice->val[y][z] = image3D->val[z][y][x];
                    }
                }
            }

            else if(directionVertical == -1 && directionHorizontal == 1){
                indexY = 0;
                for(y=image3D->ny-1; y >= 0 ; y--){
                    for(z=0; z < image3D->nz; z++){
                        slice->val[indexY][z] = image3D->val[z][y][x];
                    }
                    indexY++;
                }
            }

            else if(directionVertical == -1 && directionHorizontal == -1){
                indexY = 0;
                indexZ = 0;
                for(y=image3D->ny-1; y >= 0 ; y--){
                    for(z=image3D->nz-1; z >= 0; z--){
                        slice->val[indexY][indexZ] = image3D->val[z][y][x];
                        indexZ++;
                    }
                    indexY++;
                    indexZ = 0;
                }
            }

            else if(directionVertical == 1 && directionHorizontal == -1){
                indexZ = 0;
                for(y=0; y < image3D->ny ; y++){
                    for(z=image3D->nz-1; z >= 0; z--){
                        slice->val[y][indexZ] = image3D->val[z][y][x];
                        indexZ++;
                    }
                    indexZ = 0;
                }
            }else{
                DestroyGrayImage(&slice);
                fprintf(stdout,"Error: invalid axes orientation %d %d.\n",directionHorizontal, directionVertical);
            }

        }else{
            fprintf(stdout,"Error: invalid axis %c.\n",axisHorizontal);
        }
    }else if(axisVertical == 'z') {
        if (axisHorizontal == 'y') {
            slice = CreateGrayImage(image3D->ny, image3D->nz);
            if (directionVertical == 1 && directionHorizontal == 1) {
                for (y = 0; y < image3D->ny; y++) {
                    for (z = 0; z < image3D->nz; z++) {
                        slice->val[z][y] = image3D->val[z][y][x];
                    }
                }
            }

            else if (directionVertical == -1 && directionHorizontal == 1) {
                indexY = 0;
                for (y = image3D->ny - 1; y >= 0; y--) {
                    for (z = 0; z < image3D->nz; z++) {
                        slice->val[z][indexY] = image3D->val[z][y][x];
                    }
                    indexY++;
                }
            }

            else if (directionVertical == -1 && directionHorizontal == -1) {
                indexY = 0;
                indexZ = 0;
                for (y = image3D->ny - 1; y >= 0; y--) {
                    for (z = image3D->nz - 1; z >= 0; z--) {
                        slice->val[indexZ][indexY] = image3D->val[z][y][x];
                        indexZ++;
                    }
                    indexY++;
                    indexZ = 0;
                }
            }

            else if (directionVertical == 1 && directionHorizontal == -1) {
                indexZ = 0;
                for (y = 0; y < image3D->ny; y++) {
                    for (z = image3D->nz - 1; z >= 0; z--) {
                        slice->val[indexZ][y] = image3D->val[z][y][x];
                        indexZ++;
                    }
                    indexZ = 0;
                }
            } else {
                fprintf(stdout, "Error: invalid axes orientation %d %d.\n", directionHorizontal, directionVertical);
                DestroyGrayImage(&slice);
            }
        } else {
            fprintf(stdout, "Error: invalid axis %c.\n", axisHorizontal);
        }
    }else{
        fprintf(stdout,"Error: invalid axis %c.\n",axisVertical);
    }

    return slice;

}

GrayImage* getSlice(char verticalAxis, int directionVertial, char horizontalAxis, int directionHorizontal, MedicalImage *image3D, int sliceDepth){
    GrayImage *slice = NULL;
    if(verticalAxis != 'z' && horizontalAxis != 'z'){
        slice = getSliceZPositive(sliceDepth,verticalAxis,directionVertial,horizontalAxis,directionHorizontal,image3D);
    }

    else if(verticalAxis != 'y' && horizontalAxis != 'y'){
        slice = getSliceYPositive(sliceDepth,verticalAxis,directionVertial,horizontalAxis,directionHorizontal,image3D);
    }

    else if(verticalAxis != 'x' && horizontalAxis != 'x'){
        slice = getSliceXPositive(sliceDepth,verticalAxis,directionVertial,horizontalAxis,directionHorizontal,image3D);
    }
    return slice;
}


