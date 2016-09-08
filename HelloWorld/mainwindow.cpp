#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QImageReader>
#include "mc920.h"


MedicalImage *image3D;
int sliceDepth = 0;
int nbits = 8;
char verticalAxis = 'y';
char horizontalAxis = 'x';
int verticalDirection = 1;
int horizontalDirection = 1;
GrayImage *sliceZ = NULL;


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

void MainWindow::on_actionOpen_triggered()
{
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
        /*QFile file(fileName);
           if (!file.open(QIODevice::ReadOnly)) {
               QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                  return;
           }
           QTextStream in(&file);
           //ui->HelloWorldLabel->setText(in.readAll());
           ui->HelloWorldLabel->setText(fileName);*/

        //file.close();
    }
}
