#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <QImage>
#include <image.h>
#include <QLabel>
#include <QPixmap>
#include <QMenu>
#include <QAction>
#include <displaymanager.h>

QImage *createGrayImage2LabelArea(GrayImage *grayImage);
QImage *createGrayImage2LabelArea(GrayImage *grayImage, int maximumValueScene);

QImage *create8bitsGrayImage2LabelArea(GrayImage *grayImage);
void displayImageOnLabel(QImage *image,QLabel *imageArea);
void rotationAntiClockWiseZ(ViewDisplay *view);
void rotationAntiClockWiseY(ViewDisplay *view);
void mirrorAlongVerticalAxis(ViewDisplay *view);
void mirrorAlongHorizontalAxis(ViewDisplay *view);\
void getQImageFromView(ViewDisplay *view, MedicalImage *image3D, MedicalImage *labelImage, QImage **image);
int createContextMenuForLabelImage(MedicalImage *image3D,MedicalImage *labelImage,const QPoint &pos, QObject *obj);
QImage *createColorImage2LabelAreaModified(ColorImage *colorImage, GrayImage *grayImage, int cont);

#endif // EVENTMANAGER_H
