#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QImage>
#include <image.h>
#include <QLabel>
#include <QPixmap>

QImage *createGrayImage2LabelArea(GrayImage *grayImage);
QImage *create8bitsGrayImage2LabelArea(GrayImage *grayImage);
void displayImageOnLabel(QImage *image,QLabel *imageArea);


#endif // EVENTMANAGER_H
