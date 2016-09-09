#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QImageReader>
#include <QMessageBox>
#include "mc920.h"



//global variable to mainwindow
MedicalImage *image3D;


//char *ext = strrchr(argv[1],'.')+1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



/**
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.scn);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        image3D = ReadMedicalImage(fileName.toLatin1().data());
        if(image3D->maxIntensityAllowed > 255){
            nbits = 16;
        }
        else{
            nbits = 8;
        }
        sliceZ = getSlice(verticalAxis,verticalDirection,  horizontalAxis,  horizontalDirection, image3D, sliceDepth);
        writeGrayImagePng(sliceZ,nbits, "Z_axis.png");
        QString localFilename;
        localFilename = "Z_axis.png";
        QImageReader *reader = new QImageReader(localFilename);
        reader->setAutoTransform(true);
        const QImage newImage = reader->read();

        //newImage.
        if (newImage.isNull()) {
            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                     tr("Cannot load %1: %2")
                                     .arg(QDir::toNativeSeparators(fileName), reader->errorString()));

            return;
        }
//          ui->graphicsView->scene()->addItem();
        ui->HelloWorldLabel->setGeometry(20,20,newImage.width(),newImage.height());
        ui->HelloWorldLabel->setPixmap(QPixmap::fromImage(newImage));


//        scaleFactor = 1.0;

//        scrollArea->setVisible(true);
//        printAct->setEnabled(true);
//        fitToWindowAct->setEnabled(true);
//        updateActions();

//        if (!fitToWindowAct->isChecked())
//            imageLabel->adjustSize();

        //QPixmap pixelmap = n
        QFile file(fileName);
           if (!file.open(QIODevice::ReadOnly)) {
               QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                  return;
           }
           QTextStream in(&file);
           //ui->HelloWorldLabel->setText(in.readAll());
           ui->HelloWorldLabel->setText(fileName);

           file.close();

*/



void MainWindow::on_action3D_Image_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.scn);;C++ Files (*.cpp *.h)"));
    if (!fileName.isEmpty()) {
        MedicalImage *image3D = NULL;
        GrayImage *sliceZ = NULL;
        GrayImage *sliceY = NULL;
        GrayImage *sliceX = NULL;
        int  sliceDepth = 40;


        image3D = ReadMedicalImage(fileName.toLatin1().data());//reading 3d image
        //get default slices
        sliceZ = getSlice('y',1,'x', 1, image3D, sliceDepth);//xy plan
        sliceY = getSlice('x',1, 'z', 1, image3D, sliceDepth);//zx plan
        sliceX = getSlice('y',1, 'z', 1, image3D, sliceDepth);//zy plan

        QImage *imageZ = new QImage(sliceZ->nx,sliceZ->ny,QImage::Format_RGB32);
        QImage *imageY = new QImage(sliceY->nx,sliceY->ny,QImage::Format_RGB32);
        QImage *imageX = new QImage(sliceX->nx,sliceX->ny,QImage::Format_RGB32);

        //solution1: comprimi 12 bits em 8 bits (desolcamento de 4 bits para a direita)
        //solution2: salva uma imagem png como 16 bits e depois le ela
        int solution =1;
        if(solution == 1){
            //using qt components to display the images
            if(image3D->nbits > 8){
                QRgb value = qRgb(0,0,0);
                int factor = 2047;
                int aux;//TODO: escolher um nome apropriado para a variavel

                for(int y=0; y < sliceZ->ny; y++){
                    for(int x=0; x < sliceZ->nx; x++){
                        aux = (((float)sliceZ->val[y][x])/factor)*255;
                        value = qRgb(aux, aux , aux);
                        imageZ->setPixel(x,y,value);
                    }
                }

                for(int y=0; y < sliceY->ny; y++){
                    for(int x=0; x < sliceY->nx; x++){
                        aux = (((float)sliceY->val[y][x])/factor)*255;
                        value = qRgb(aux, aux , aux);
                        imageY->setPixel(x,y,value);
                    }
                }

                for(int y=0; y < sliceX->ny; y++){
                    for(int x=0; x < sliceX->nx; x++){
                        aux = (((float)sliceX->val[y][x])/factor)*255;
                        value = qRgb(aux, aux , aux);
                        imageX->setPixel(x,y,value);
                    }
                }

            }else{

            }
            ui->labelFigureZ->setPixmap(QPixmap::fromImage((*imageZ)));
            ui->labelFigureY->setPixmap(QPixmap::fromImage((*imageY)));
            ui->labelFigureX->setPixmap(QPixmap::fromImage((*imageX)));
        }
        //QImage *imageZ = new QImage(sliceZ->dx,sliceZ->dy,QImage::Format_RGB32);
        //            QImage *imageZ = new QImage(sliceZ->nx,sliceZ->ny,QImage::Format_RGB32);
        //            QRgb value = qRgb(0,0,0);
        //            int maxValue = 0;
        //            int aux;
        //            for(int y=0; y < sliceZ->ny; y++){
        //                for(int x=0; x < sliceZ->nx; x++){

        //                    aux = (((float)sliceZ->val[y][x])/4095)*255;
        //                    value = qRgb(aux, aux , aux);
        //                    imageZ->setPixel(x,y,value);
        //                }
        //            }
        //            printf("MaxFinal: %d\n",maxValue);
        //            ui->label->setPixmap(QPixmap::fromImage((*imageZ)));

        //        QString localFilename;
        //        localFilename = "slice0.png";
        //        QImageReader *reader = new QImageReader(localFilename);
        //        reader->setAutoTransform(true);
        //        const QImage newImage = reader->read();

        //        //newImage.
        //        if (newImage.isNull()) {
        //            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
        //                                     tr("Cannot load %1: %2")
        //                                     .arg(QDir::toNativeSeparators(fileName), reader->errorString()));

        //            return;
        //        }

        //        ui->label->setPixmap(QPixmap::fromImage(newImage));

    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","File is empty");
        messageBox.setFixedSize(500,200);
    }
}
