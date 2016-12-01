#include "eventmanager.h"



QImage *createGrayImage2LabelArea(GrayImage *grayImage, int maximumValueScene){
    QImage *image = new QImage(grayImage->nx,grayImage->ny,QImage::Format_RGB32);;
    QRgb value = qRgb(0,0,0);

    int aux;//TODO: escolher um nome apropriado para a variavel

    for(int y=0; y < grayImage->ny; y++){
        for(int x=0; x < grayImage->nx; x++){
            //aux = (((float)grayImage->val[y][x])/factor);
            aux = (((float)grayImage->val[y][x])/maximumValueScene)*255;
            if(aux > 255){
                //printf("%d %d",y,x);
                aux = 255;
            }
            value = qRgb(aux, aux , aux);
            image->setPixel(x,y,value);
        }
    }
    return image;
}



QImage *createColorImage2LabelAreaModified(ColorImage *colorImage, GrayImage *grayImage, int cont){
    QImage *image = new QImage(colorImage->nx,colorImage->ny,QImage::Format_RGB32);;
    QRgb value = qRgb(0,0,0);


    for(int y=0; y < colorImage->ny; y++){
        for(int x=0; x < colorImage->nx; x++){
            value = qRgb(colorImage->cor[y][x].val[0], colorImage->cor[y][x].val[1] , colorImage->cor[y][x].val[2]);
            image->setPixel(x,y,value);
        }
    }
    return image;
}

QImage *createColorImage2LabelArea(ColorImage *colorImage){
    QImage *image = new QImage(colorImage->nx,colorImage->ny,QImage::Format_RGB32);;
    QRgb value = qRgb(0,0,0);

    for(int y=0; y < colorImage->ny; y++){
        for(int x=0; x < colorImage->nx; x++){

            value = qRgb(colorImage->cor[y][x].val[0], colorImage->cor[y][x].val[1] , colorImage->cor[y][x].val[2]);
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

void rotationAntiClockWiseZ(ViewDisplay *view){
    view->horizontalAxis = view->horizontalAxis+view->verticalAxis;
    view->verticalAxis = view->horizontalAxis-view->verticalAxis;
    view->horizontalAxis = view->horizontalAxis-view->verticalAxis;


    if(view->verticalDirection == 1 && view->horizontalDirection == 1){
        view->verticalDirection = 1;
        view->horizontalDirection = -1;
    }

    else if(view->verticalDirection == 1 && view->horizontalDirection == -1){
        view->verticalDirection = -1;
        view->horizontalDirection = -1;
    }

    else if(view->verticalDirection == -1 && view->horizontalDirection == -1){
        view->verticalDirection = -1;
        view->horizontalDirection = 1;
    }

    else if(view->verticalDirection == -1 && view->horizontalDirection == 1){
        view->verticalDirection = 1;
        view->horizontalDirection = 1;
    }
}

void rotationAntiClockWiseY(ViewDisplay *view){
    view->horizontalAxis = view->horizontalAxis+view->verticalAxis;
    view->verticalAxis = view->horizontalAxis-view->verticalAxis;
    view->horizontalAxis = view->horizontalAxis-view->verticalAxis;


    if(view->verticalDirection == 1 && view->horizontalDirection == 1){
        view->verticalDirection = -1;
        view->horizontalDirection = 1;
    }

    else if(view->verticalDirection == -1 && view->horizontalDirection == 1){
        view->verticalDirection = -1;
        view->horizontalDirection = -1;
    }

    else if(view->verticalDirection == -1 && view->horizontalDirection == -1){
        view->verticalDirection = 1;
        view->horizontalDirection = -1;
    }

    else if(view->verticalDirection == 1 && view->horizontalDirection == -1){
        view->verticalDirection = 1;
        view->horizontalDirection = 1;
    }
}

void mirrorAlongVerticalAxis(ViewDisplay *view){
    view->horizontalDirection *= -1;
}

void mirrorAlongHorizontalAxis(ViewDisplay *view){
    view->verticalDirection *= -1;
}

void getQImageFromView(ViewDisplay *view, MedicalImage *image3D, MedicalImage *labelImage, QImage **image){


    if(view->type == 1){
        GrayImage *slice = getSlice(view->verticalAxis,view->verticalDirection,view->horizontalAxis, view->horizontalDirection, image3D, view->slice);
        WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
        //contrastBrightAdjustment(slice, view);
        if((*image) != NULL){
            delete (*image);
        }
        if(image3D->nbits > 8){
            *image = createGrayImage2LabelArea(slice,image3D->maxValue);
        }else{
            *image = create8bitsGrayImage2LabelArea(slice);
        }
        DestroyGrayImage(&slice);
    }else if(view->type == 2){
        GrayImage *slice = getSlice(view->verticalAxis,view->verticalDirection,view->horizontalAxis, view->horizontalDirection, labelImage, view->slice);
        if((*image) != NULL){
            delete (*image);
        }
        ColorImage *colorImage = generateColorImageFromLabelImage(slice,view->rgbColorTable);
        *image = createColorImage2LabelAreaModified(colorImage,slice,2);
        DestroyGrayImage(&slice);

    }else if(view->type == 3){
        GrayImage *slice = getSlice(view->verticalAxis,view->verticalDirection,view->horizontalAxis, view->horizontalDirection, image3D, view->slice);
        GrayImage *labelSlice = getSlice(view->verticalAxis,view->verticalDirection,view->horizontalAxis, view->horizontalDirection, labelImage, view->slice);
        WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
        if((*image) != NULL){
            delete (*image);
        }
        //normalizeGrayImage(slice);
        //ColorImage *colorImage = generateColorImageFromLabelImage(slice,view->rgbColorTable);
        ColorImage *colorImage = generateColorImageFromLabelImage(slice,labelSlice,view->yCgCoColorTable, 4095);
        *image = createColorImage2LabelArea(colorImage);
        DestroyGrayImage(&slice);
        DestroyGrayImage(&labelSlice);
    }else if(view->type == 4){
        GrayImage *slice = getSlice(view->verticalAxis,view->verticalDirection,view->horizontalAxis, view->horizontalDirection, image3D, view->slice);
        NegativeGrayImage(slice, 4095);
        if((*image) != NULL){
            delete (*image);
        }
        if(image3D->nbits > 8){
            *image = createGrayImage2LabelArea(slice,4095);
        }else{
            *image = create8bitsGrayImage2LabelArea(slice);
        }
        DestroyGrayImage(&slice);
    }else if(view->type == 5){
        GrayImage *slice = getSlice(view->verticalAxis,view->verticalDirection,view->horizontalAxis, view->horizontalDirection, image3D, view->slice);
        normalizeGrayImage(slice,0,slice->Imax,255);
        if((*image) != NULL){
            delete (*image);
        }
        *image = createGrayImage2LabelArea(slice,255);
//        QRgb value = qRgb(0,0,0);
//        int aux;
//        for(int y=0; y < slice->ny; y++){
//            for(int x=0; x < slice->nx; x++){
//                aux = slice->val[y][x];
//                value = qRgb(aux, aux , aux);
//                (*image)->setPixel(x,y,value);
//            }
//        }
        DestroyGrayImage(&slice);
    }


}

int createContextMenuForLabelImage(MedicalImage *image3D,MedicalImage *labelImage,const QPoint &pos, QObject *obj){
    QString stringOption1 = "Gray";
    QString stringOption2 = "Color Mask";
    QString stringOption3 = "Color Image";
    int selectedOption = -1;
    QMenu *menu = new QMenu();
    QAction *gray = new QAction(stringOption1, obj);
    QAction *colorMask = new QAction(stringOption2, obj);
    QAction *colorImage = new QAction(stringOption3, obj);

    menu->addAction(gray);
    menu->addAction(colorMask);
    menu->addAction(colorImage);
    if(image3D == NULL){
        gray->setEnabled(false);
        colorMask->setEnabled(false);
        colorImage->setEnabled(false);
    }
    if(labelImage == NULL){
        colorMask->setEnabled(false);
        colorImage->setEnabled(false);
    }
    QAction* selectedItem = menu->exec(pos);
    if(selectedItem != NULL){
        if(selectedItem->text() == stringOption1){
            selectedOption =  1;
        }
        else if(selectedItem->text() == stringOption2){
            selectedOption = 2;
        }else if(selectedItem->text() == stringOption3){
            selectedOption = 3;
        }
    }
    return selectedOption;
}

int createContextMenuForRedering(MedicalImage *image3D,MedicalImage *labelImage,
                                 const QPoint &pos, QObject *obj, bool* save, int*selectedOption){
    QString stringOption1 = "PlanarView";
    QString stringOption2 = "Maximum Intensity Projetction";
    QString stringOption3 = "Surface Rendering (grey)";
    QString stringOption4 = "Surface Rendering (color)";
    QString stringOption5 = "Surface Rendering (alpha)";
    QString stringOption6 = "Phong (grey)";
    QString stringOption7 = "Phong (RGB)";
    QString stringOption8 = "Phong (RGBA)";
    QString stringOption9 = "Phong (ST)";
    QString stringOption10 = "Depth";
    QString stringOption100 = "Save Image";
    //int selectedOption = -1;
    QMenu *menu = new QMenu();
    QAction *PlanarView = new QAction(stringOption1, obj);
    QAction *MIP = new QAction(stringOption2, obj);
    QAction *VR = new QAction(stringOption3, obj);
    QAction *VR_color = new QAction(stringOption4, obj);
    QAction *VR_alpha = new QAction(stringOption5, obj);
    QAction *phong_gray = new QAction(stringOption6, obj);
    QAction *phong_RGB = new QAction(stringOption7, obj);
    QAction *phong_RGBA = new QAction(stringOption8, obj);
    QAction *phong_ST = new QAction(stringOption9, obj);
    QAction *depth_map = new QAction(stringOption10, obj);
    QAction *saveImage = new QAction(stringOption100, obj);
    menu->addAction(PlanarView);
    menu->addAction(MIP);
    menu->addAction(VR);
    menu->addAction(VR_color);
    menu->addAction(VR_alpha);
    menu->addAction(phong_gray);
    menu->addAction(phong_RGB);
    menu->addAction(phong_RGBA);
    menu->addAction(phong_ST);
    menu->addAction(depth_map);

    menu->addAction(saveImage);
    if(image3D == NULL){
        PlanarView->setEnabled(false);
        MIP->setEnabled(false);
        VR->setEnabled(false);
        VR_color->setEnabled(false);
        VR_alpha->setEnabled(false);
        phong_gray->setEnabled(false);
        phong_RGB->setEnabled(false);
        phong_RGBA->setEnabled(false);
        phong_ST->setEnabled(false);
        depth_map->setEnabled(false);
    }else if(labelImage == NULL){
        PlanarView->setEnabled(true);
        MIP->setEnabled(true);
        VR->setEnabled(false);
        VR_color->setEnabled(false);
        VR_alpha->setEnabled(false);
        phong_gray->setEnabled(false);
        phong_RGB->setEnabled(false);
        phong_RGBA->setEnabled(false);
        phong_ST->setEnabled(false);
        depth_map->setEnabled(false);
    }
    QAction* selectedItem = menu->exec(pos);
    if(selectedItem != NULL){
        if(selectedItem->text() == stringOption1){
            selectedOption =  0;
        }
        else if(selectedItem->text() == stringOption2){
            *selectedOption = 1;
        }else if(selectedItem->text() == stringOption3){
            *selectedOption = 2;
        }else if(selectedItem->text() == stringOption4){
            *selectedOption = 3;
        }else if(selectedItem->text() == stringOption5){
            *selectedOption = 4;
        }else if(selectedItem->text() == stringOption6){
            *selectedOption = 5;
        }else if(selectedItem->text() == stringOption7){
            *selectedOption = 6;
        }else if(selectedItem->text() == stringOption8){
            *selectedOption = 7;
        }else if(selectedItem->text() == stringOption9){
            *selectedOption = 8;
        }else if(selectedItem->text() == stringOption10){
            *selectedOption = 9;
        }

        if(selectedItem->text() == stringOption100){
            (*save) = true;
        }
    }
    return *selectedOption;
}


