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
