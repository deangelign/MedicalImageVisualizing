#include "eventmanager.h"



QImage *createGrayImage2LabelArea(GrayImage *grayImage){
    QImage *image = new QImage(grayImage->nx,grayImage->ny,QImage::Format_RGB32);;
    QRgb value = qRgb(0,0,0);
    int factor = 2047;
    int aux;//TODO: escolher um nome apropriado para a variavel

    for(int y=0; y < grayImage->ny; y++){
        for(int x=0; x < grayImage->nx; x++){
            aux = (((float)grayImage->val[y][x])/factor)*255;
            value = qRgb(aux, aux , aux);
            image->setPixel(x,y,value);
        }
    }
    return image;
}

QImage *create8bitsGrayImage2LabelArea(GrayImage *grayImage){
    QImage *image = new QImage(grayImage->nx,grayImage->ny,QImage::Format_RGB32);;
    QRgb value = qRgb(0,0,0);
    int aux;//TODO: escolher um nome apropriado para a variavel

    for(int y=0; y < grayImage->ny; y++){
        for(int x=0; x < grayImage->nx; x++){
            aux = grayImage->val[y][x];
            value = qRgb(aux, aux , aux);
            image->setPixel(x,y,value);
        }
    }
    return image;
}

void displayImageOnLabel(QImage *image,QLabel *imageArea){
    imageArea->setPixmap(QPixmap::fromImage((*image)));
}

