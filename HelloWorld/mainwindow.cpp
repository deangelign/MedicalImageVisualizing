#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QImageReader>
#include <QMessageBox>
#include <QTime>
#include "mc920.h"
#include "matrixfeia.h"





//global variable to mainwindow
MedicalImage *image3D;
MedicalImage *labelImage;
QImage *imageZ;
QImage *imageY;
QImage *imageX;
QImage *imageXYZ;
ViewDisplay *viewZ;
ViewDisplay *viewY;
ViewDisplay *viewX;
ViewDisplay *viewXYZ;

int defaultMaxValue = 4095;
int NegativeType = 4;
bool negativeActive = false;
int NormalizationType = 5;
bool NormalizationActive = false;
bool startDrawXYZImage = false;
int renderingOption=0;

float *alphas = NULL;
float *k_phong = NULL;
float *bg_color = (float*)calloc(1,sizeof(float));

iftMatrix<float>*gradients = NULL;
iftMatrix<float>*depthMap = NULL;
bool save = false;


void init(){
    image3D = NULL;
    labelImage = NULL;
    imageZ = NULL;
    imageY = NULL;
    imageX = NULL;

    //xy plan
    viewZ = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
    viewZ->horizontalAxis = 'x';
    viewZ->verticalAxis = 'y';
    viewZ->referenceAxis = 'z';
    viewZ->verticalDirection = 1;
    viewZ->horizontalDirection = 1;
    viewZ->slice = 0;
    viewZ->rgbColorTable = NULL;
    viewZ->type = 1;
    updateContrastBrightParameters(viewZ,0,defaultMaxValue,0,defaultMaxValue);


    //zx plan
    viewY = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
    viewY->horizontalAxis = 'x';
    viewY->verticalAxis = 'z';
    viewY->referenceAxis = 'y';
    viewY->verticalDirection = -1;
    viewY->horizontalDirection = 1;
    viewY->slice = 0;
    viewY->rgbColorTable = NULL;
    viewY->type = 1;
    updateContrastBrightParameters(viewY,0,defaultMaxValue,0,defaultMaxValue);


    //zy plan
    viewX = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
    viewX->horizontalAxis = 'y';
    viewX->verticalAxis = 'z';
    viewX->referenceAxis = 'x';
    viewX->verticalDirection = -1;
    viewX->horizontalDirection = -1;
    viewX->slice = 0;
    viewX->rgbColorTable = NULL;
    viewX->type = 1;
    updateContrastBrightParameters(viewX,0,defaultMaxValue,0,defaultMaxValue);

    viewXYZ = (ViewDisplay *)calloc(1,sizeof(ViewDisplay));
    viewXYZ->rgbColorTable = NULL;
    bg_color[0] = 0;
    bg_color[1] = 0;
    bg_color[2] = 0;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action3D_Image_triggered()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.scn);;C++ Files (*.cpp *.h)"));
    if (!fileName.isEmpty()) {

        if(image3D != NULL){
            DestroyMedicalImage(&image3D);
            DestroyMedicalImage(&labelImage);
            delete imageZ;
            delete imageY;
            delete imageX;
            delete imageXYZ;
            imageZ = NULL;
            imageY = NULL;
            imageX = NULL;
            imageXYZ = NULL;
            if(gradients != NULL){
                destroyMatrix(&gradients);
                gradients = NULL;
            }
            if(depthMap !=NULL){
                destroyMatrix(&depthMap);
                depthMap = NULL;
            }
        }

        image3D = ReadMedicalImage(fileName.toLatin1().data());//reading 3d image
        ui->labelNumberObjets->setText("0");

        viewZ->slice = image3D->nz/2;
        viewZ->type = 1;
        viewZ->k2 = image3D->maxValue;
        updateContrastBrightParameters(viewZ,image3D->maxValue/2.0,image3D->maxValue);

        viewY->slice = image3D->ny/2;
        viewY->type = 1;
        viewY->k2 = image3D->maxValue;
        updateContrastBrightParameters(viewY,image3D->maxValue/2.0,image3D->maxValue);


        viewX->slice = image3D->nx/2;
        viewX->type = 1;
        viewX->k2 = image3D->maxValue;
        updateContrastBrightParameters(viewX,image3D->maxValue/2.0,image3D->maxValue);

        viewXYZ->k2 = image3D->maxValue;
        viewXYZ->k1 = 0;
        updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);


        ui->spinBoxImageZ->setMaximum(image3D->nz-1);
        ui->spinBoxImageZ->setValue(viewZ->slice);

        ui->spinBoxImageY->setMaximum(image3D->ny-1);
        ui->spinBoxImageY->setValue(viewY->slice);

        ui->spinBoxImageX->setMaximum(image3D->nx-1);
        ui->spinBoxImageX->setValue(viewX->slice);

        getQImageFromView(viewZ,image3D,labelImage,&imageZ);
        getQImageFromView(viewY,image3D,labelImage,&imageY);
        getQImageFromView(viewX,image3D,labelImage,&imageX);

        displayImageOnLabel(imageZ,ui->labelFigureZ);
        displayImageOnLabel(imageY,ui->labelFigureY);
        displayImageOnLabel(imageX,ui->labelFigureX);

        ui->SpinBoxPointX->setValue(image3D->nx/2);
        ui->SpinBoxPointY->setValue(image3D->ny/2);
        ui->SpinBoxPointZ->setValue(image3D->nz/2);

    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","File is empty");
        messageBox.setFixedSize(500,200);
    }


}

void MainWindow::on_spinBoxImageZ_valueChanged(int newValue)
{
    try{
        if(imageZ != NULL && image3D != NULL){
            viewZ->slice = newValue;
            getQImageFromView(viewZ,image3D,labelImage,&imageZ);
            displayImageOnLabel(imageZ,ui->labelFigureZ);
        }
    }catch(int e){
        fprintf(stderr,"Nao consegui converter\n");
    }

}

void MainWindow::on_spinBoxImageY_valueChanged(int newValue)
{
    try{
        if(imageY != NULL && image3D != NULL){
            viewY->slice = newValue;
            getQImageFromView(viewY,image3D,labelImage,&imageY);
            displayImageOnLabel(imageY,ui->labelFigureY);
        }
    }catch(int e){
        fprintf(stderr,"Nao consegui converter\n");
    }
}

void MainWindow::on_spinBoxImageX_valueChanged(int newValue)
{
    try{
        if(imageX != NULL && image3D != NULL){
            viewX->slice = newValue;
            getQImageFromView(viewX,image3D,labelImage,&imageX);
            displayImageOnLabel(imageX,ui->labelFigureX);
        }
    }catch(int e){
        fprintf(stderr,"Nao consegui converter\n");
    }
}


void MainWindow::on_mirrorZ_clicked()
{
    if(imageZ != NULL && image3D != NULL){
        mirrorAlongVerticalAxis(viewZ);
        getQImageFromView(viewZ,image3D,labelImage,&imageZ);
        displayImageOnLabel(imageZ,ui->labelFigureZ);
    }
}



void MainWindow::on_rotateZ_90AntiClockwise_clicked()
{
    if(imageZ != NULL && image3D != NULL){
        rotationAntiClockWiseZ(viewZ);
        getQImageFromView(viewZ,image3D,labelImage,&imageZ);
        displayImageOnLabel(imageZ,ui->labelFigureZ);
    }
}

void MainWindow::on_rotateY_90Anticlockwise_clicked()
{
    if(imageY != NULL && image3D != NULL){
        rotationAntiClockWiseY(viewY);
        getQImageFromView(viewY,image3D,labelImage,&imageY);
        displayImageOnLabel(imageY,ui->labelFigureY);
    }
}

void MainWindow::on_rotateY_90Anticlockwise_2_clicked()
{
    if(imageX != NULL && image3D != NULL){
        rotationAntiClockWiseY(viewX);
        getQImageFromView(viewX,image3D,labelImage,&imageX);
        displayImageOnLabel(imageX,ui->labelFigureX);
    }
}

void MainWindow::on_actionLabel_map_triggered()
{
    if(image3D != NULL){

        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                        tr("Text Files (*.scn)"));

        if (!fileName.isEmpty()) {

            if(labelImage != NULL){
                DestroyMedicalImage(&labelImage);
                destroyRGBColorMap(&viewZ->rgbColorTable);
                destroyRGBColorMap(&viewY->rgbColorTable);
                destroyRGBColorMap(&viewX->rgbColorTable);
                destroyRGBColorMap(&viewXYZ->rgbColorTable);
                destroyYCgCoColorMap(&viewZ->yCgCoColorTable);
                destroyYCgCoColorMap(&viewY->yCgCoColorTable);
                destroyYCgCoColorMap(&viewX->yCgCoColorTable);
                destroyYCgCoColorMap(&viewXYZ->yCgCoColorTable);
            }
            labelImage = ReadMedicalImage(fileName.toLatin1().data());

            //TODO: checar se as dimensoes sao iguais labelImage-3Dimage
            viewZ->rgbColorTable = generateRGBColorMap(labelImage,255);
            copyColorMap(viewZ->rgbColorTable,&viewY->rgbColorTable);
            copyColorMap(viewZ->rgbColorTable,&viewX->rgbColorTable);
            copyColorMap(viewZ->rgbColorTable,&viewXYZ->rgbColorTable);


            //            for(int i=0; i<viewZ->rgbColorTable->numberRows; i++){
            //                for(int j=0; j<viewZ->rgbColorTable->numberColumns; j++){
            //                    fprintf(stderr,"%d ",viewZ->rgbColorTable->table[i][j]);
            //                }
            //                fprintf(stderr,"\n");
            //            }
            //            fprintf(stderr,"\n");



            convertRGBColorMap2YCgCoColorMap(viewZ->rgbColorTable,&viewZ->yCgCoColorTable, 255);
            convertRGBColorMap2YCgCoColorMap(viewY->rgbColorTable,&viewY->yCgCoColorTable, 255);
            convertRGBColorMap2YCgCoColorMap(viewX->rgbColorTable,&viewX->yCgCoColorTable, 255);
            convertRGBColorMap2YCgCoColorMap(viewXYZ->rgbColorTable,&viewXYZ->yCgCoColorTable, 255);
            //            for(int i=0; i<viewZ->rgbColorTable->numberRows; i++){
            //                for(int j=0; j<viewZ->rgbColorTable->numberColumns; j++){
            //                    fprintf(stderr,"%f ",viewZ->yCgCoColorTable->table[i][j]);
            //                }
            //                fprintf(stderr,"\n");
            //            }
            //            fprintf(stderr,"\n");

            viewZ->type = 3;
            viewY->type = 3;
            viewX->type = 3;

            getQImageFromView(viewZ,image3D,labelImage,&imageZ);
            getQImageFromView(viewY,image3D,labelImage,&imageY);
            getQImageFromView(viewX,image3D,labelImage,&imageX);

            displayImageOnLabel(imageZ,ui->labelFigureZ);
            displayImageOnLabel(imageY,ui->labelFigureY);
            displayImageOnLabel(imageX,ui->labelFigureX);

            ui->labelNumberObjets->setText(QString::number(viewZ->rgbColorTable->numberRows));
            if(alphas != NULL){
                free(alphas);
                alphas = NULL;
            }
            alphas = (float*)calloc(viewZ->rgbColorTable->numberRows,sizeof(float));
            for(int i=0; i<viewZ->rgbColorTable->numberRows;i++){
                alphas[i] = 1;
            }
            if(k_phong != NULL){
                free(k_phong);
                k_phong = NULL;
            }
            k_phong = (float*)calloc(4,sizeof(float));
            k_phong[0] = 0;
            k_phong[1] = 0.782353;
            k_phong[2] = 0.0225;
            k_phong[3] = 12.8;
        }else{
            QMessageBox messageBox;
            messageBox.critical(0,"Error","File is empty");
            messageBox.setFixedSize(500,200);
        }


    }else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","You must load an image");
        messageBox.setFixedSize(500,200);
    }
}


void MainWindow::on_labelFigureZ_customContextMenuRequested(const QPoint &pos)
{
    const QPoint globalMousePosition(pos.x() + ui->labelFigureZ->geometry().topLeft().x(), pos.y() + ui->labelFigureZ->geometry().topLeft().y());
    int selectedOption = createContextMenuForLabelImage(image3D,labelImage,globalMousePosition,this);
    if(viewZ->type != selectedOption && selectedOption > 0){
        viewZ->type = selectedOption;
        getQImageFromView(viewZ,image3D,labelImage,&imageZ);
        displayImageOnLabel(imageZ,ui->labelFigureZ);
    }
}


void MainWindow::on_labelFigureY_customContextMenuRequested(const QPoint &pos)
{
    const QPoint globalMousePosition(pos.x() + ui->labelFigureY->geometry().topLeft().x(), pos.y() + ui->labelFigureY->geometry().topLeft().y());
    int selectedOption = createContextMenuForLabelImage(image3D,labelImage,globalMousePosition,this);
    if(viewY->type != selectedOption && selectedOption > 0){
        viewY->type = selectedOption;
        getQImageFromView(viewY,image3D,labelImage,&imageY);
        displayImageOnLabel(imageY,ui->labelFigureY);
    }
}

void MainWindow::on_labelFigureX_customContextMenuRequested(const QPoint &pos)
{
    const QPoint globalMousePosition(pos.x() + ui->labelFigureX->geometry().topLeft().x(), pos.y() + ui->labelFigureX->geometry().topLeft().y());
    int selectedOption = createContextMenuForLabelImage(image3D,labelImage,globalMousePosition,this);
    if(viewX->type != selectedOption && selectedOption > 0){
        viewX->type = selectedOption;
        getQImageFromView(viewX,image3D,labelImage,&imageX);
        displayImageOnLabel(imageX,ui->labelFigureX);
    }
}



void MainWindow::on_pushButton_clicked()
{

    if(image3D != NULL){
        brightContrastDialogForm = new BrightContrastDialog(this,viewZ->bright,viewZ->contrast,image3D->maxValue,negativeActive, NormalizationActive);
        brightContrastDialogForm->setAttribute( Qt::WA_DeleteOnClose );
        brightContrastDialogForm->show();
        connect(brightContrastDialogForm,SIGNAL(brightSignal(float)),this,SLOT(updateImagesNewBrightContrast()));
        connect(brightContrastDialogForm,SIGNAL(contrastSignal(float)),this,SLOT(updateImagesNewBrightContrast()));
        connect(brightContrastDialogForm,SIGNAL(negativeSignal(bool)),this,SLOT(displayNegativeImage()));
        connect(brightContrastDialogForm,SIGNAL(normalizationSignal(bool)),this,SLOT(displayNormalizedImage()));
    }else{
        brightContrastDialogForm = new BrightContrastDialog(this,viewZ->bright,viewZ->contrast,defaultMaxValue, negativeActive,NormalizationActive);
        brightContrastDialogForm->setAttribute( Qt::WA_DeleteOnClose );
        brightContrastDialogForm->show();
        connect(brightContrastDialogForm,SIGNAL(brightSignal(float)),this,SLOT(updateImagesNewBrightContrast()));
        connect(brightContrastDialogForm,SIGNAL(contrastSignal(float)),this,SLOT(updateImagesNewBrightContrast()));
        connect(brightContrastDialogForm,SIGNAL(negativeSignal(bool)),this,SLOT(displayNegativeImage()));
        connect(brightContrastDialogForm,SIGNAL(normalizationSignal(bool)),this,SLOT(displayNormalizedImage()));
    }
}

void MainWindow::updateImagesNewBrightContrast(){
    viewZ->bright = brightContrastDialogForm->brightValue;
    viewZ->contrast = brightContrastDialogForm->contrastValue;

    viewZ->I1 = viewZ->bright - (viewZ->contrast/2);
    viewZ->I2 = viewZ->contrast - viewZ->I1;

    viewY->bright = viewZ->bright;
    viewY->contrast = viewZ->contrast;
    viewY->I1 = viewZ->I1;
    viewY->I2 = viewZ->I2;

    viewX->bright = viewZ->bright;
    viewX->contrast = viewZ->contrast;
    viewX->I1 = viewZ->I1;
    viewX->I2 = viewZ->I2;
    getQImageFromView(viewZ,image3D,labelImage,&imageZ);
    displayImageOnLabel(imageZ,ui->labelFigureZ);

    getQImageFromView(viewY,image3D,labelImage,&imageY);
    displayImageOnLabel(imageY,ui->labelFigureY);

    getQImageFromView(viewX,image3D,labelImage,&imageX);
    displayImageOnLabel(imageX,ui->labelFigureX);
}

void MainWindow::displayNegativeImage(){
    negativeActive = brightContrastDialogForm->negative;
    viewZ->type = NegativeType + viewZ->type;
    NegativeType = viewZ->type - NegativeType;
    viewZ->type = viewZ->type - NegativeType;
    viewY->type = viewZ->type;
    viewX->type = viewZ->type;

    if(image3D != NULL){
        getQImageFromView(viewZ,image3D,labelImage,&imageZ);
        displayImageOnLabel(imageZ,ui->labelFigureZ);

        getQImageFromView(viewY,image3D,labelImage,&imageY);
        displayImageOnLabel(imageY,ui->labelFigureY);

        getQImageFromView(viewX,image3D,labelImage,&imageX);
        displayImageOnLabel(imageX,ui->labelFigureX);
    }
}

void MainWindow::displayNormalizedImage(){
    NormalizationActive = brightContrastDialogForm->normalization;
    viewZ->type = NormalizationType + viewZ->type;
    NormalizationType = viewZ->type - NormalizationType;
    viewZ->type = viewZ->type - NormalizationType;
    viewY->type = viewZ->type;
    viewX->type = viewZ->type;

    if(image3D != NULL){
        getQImageFromView(viewZ,image3D,labelImage,&imageZ);
        displayImageOnLabel(imageZ,ui->labelFigureZ);

        getQImageFromView(viewY,image3D,labelImage,&imageY);
        displayImageOnLabel(imageY,ui->labelFigureY);

        getQImageFromView(viewX,image3D,labelImage,&imageX);
        displayImageOnLabel(imageX,ui->labelFigureX);
    }
}



void MainWindow::on_pushButton_2_clicked()
{
//    MedicalImage* image3D_aux = CreateMedicalImage(150,150,150);
//    int label = 1;
//    for (int z = 0; z < image3D_aux->nz; ++z) {
//        for (int y = 0; y < image3D_aux->ny; ++y) {
//            for (int x = 0; x < image3D_aux->nx; ++x) {

//                if(x >= 25 && x < 75 && y >=25 && y < 75 && z >= 25 && z < 75){
//                    image3D_aux->val[z][y][x] = 100;
//                }else if(x >= 75 && x < 125 && y >=25 && y < 75 && z >= 25 && z < 75){
//                    image3D_aux->val[z][y][x] = 200;
//                }else if(x >= 25 && x < 75 && y >=75 && y < 125 && z >= 25 && z < 75){
//                    image3D_aux->val[z][y][x] = 300;
//                }else if(x >= 75 && x < 125 && y >=75 && y < 125 && z >= 25 && z < 75){
//                    image3D_aux->val[z][y][x] = 400;
//                }
//                //z
//                else if(x >= 25 && x < 75 && y >=25 && y < 75 && z >= 75 && z < 125){
//                    image3D_aux->val[z][y][x] = 500;
//                }else if(x >= 75 && x < 125 && y >=25 && y < 75 && z >= 75 && z < 125){
//                    image3D_aux->val[z][y][x] = 600;
//                }else if(x >= 25 && x < 75 && y >=75 && y < 125 && z >= 75 && z < 125){
//                    image3D_aux->val[z][y][x] = 700;
//                }else if(x >= 75 && x < 125 && y >=75 && y < 125 && z >= 75 && z < 125){
//                    image3D_aux->val[z][y][x] = 800;
//                }
//            }
//        }
//    }
//    WriteMedicalImage(image3D_aux,"/home/deangeli/MedicalImageVisualizing/data/cube.scn");
//    scaleSceneValues(image3D_aux,100);
//    WriteMedicalImage(image3D_aux,"/home/deangeli/MedicalImageVisualizing/data/cubeLabel.scn");

    MedicalImage* image3D_aux = CreateMedicalImage(200,200,200);
    int xc = 100;
    int yc = 100;
    int zc = 100;
    int radius = 75;
    int radius_sqared = radius*radius;
    for (int z = 0; z < image3D_aux->nz; ++z) {
        for (int y = 0; y < image3D_aux->ny; ++y) {
            for (int x = 0; x < image3D_aux->nx; ++x) {
                int deltax = x - xc;
                int deltaY = y - yc;
                int deltaZ = z - zc;
                int total = (deltax*deltax) + (deltaY*deltaY) + (deltaZ*deltaZ);
                if(total <= radius_sqared){
                    if(z < zc){
                        image3D_aux->val[z][y][x] = 100;
                    }else{
                        image3D_aux->val[z][y][x] = 200;
                    }

                }
            }
        }
    }
    WriteMedicalImage(image3D_aux,"/home/deangeli/MedicalImageVisualizing/data/sphere.scn");
    scaleSceneValues(image3D_aux,100);
    WriteMedicalImage(image3D_aux,"/home/deangeli/MedicalImageVisualizing/data/sphereLabel.scn");
//    MedicalImage* labels_aux = ReadMedicalImage("brain_label.scn");
    //test1
    //    iftMatrix<float> *vec = createMatrix(1,4,(float)0);
    //    vec->elements[0] = 1;
    //    vec->elements[1] = 1;
    //    vec->elements[2] = 1;
    //    vec->elements[3] = 0;
    //    iftMatrix<float> *p = createMatrix(1,4,(float)0);
    //    p->elements[0] = 157/2.;
    //    p->elements[1] = 255/2.;
    //    p->elements[2] = 255/2.;
    //    p->elements[3] = 1;
    //    iftMatrix<float> *p2 = createMatrix(1,4,(float)0);
    //    p2->elements[0] = 157;
    //    p2->elements[1] = 255;
    //    p2->elements[2] = 255;
    //    p2->elements[3] = 1;
    //    QTime myTimer;
    //    int nMilliseconds;
    //    myTimer.start();
    //    MedicalImage* out = refactoreScene(p,p2,image3D_aux,100);
    //    WriteMedicalImage(out,"teste.scn");
    //    nMilliseconds = myTimer.elapsed();
    //    fprintf(stderr,"took %d mseconds to execute \n", nMilliseconds);


    //    //test2
    //     iftMatrix<float> *p = createMatrix(5,4,(float)0);
    //     p->elements[0] = 68;//image3D_aux->nx/2;
    //     p->elements[1] = 67;//image3D_aux->ny/2;
    //     p->elements[2] = 55;//0;
    //     p->elements[3] = 1;

    //     p->elements[4] = 78;//image3D_aux->nx/2;
    //     p->elements[5] = 19;//image3D_aux->ny/2;
    //     p->elements[6] = 55;//image3D_aux->nz;
    //     p->elements[7] = 1;

    //     p->elements[8] = 104;//image3D_aux->nx/2;
    //     p->elements[9] = 7;////0;
    //     p->elements[10] = 55;//image3D_aux->nz/2;
    //     p->elements[11] = 1;

    //     p->elements[12] = 133;//image3D_aux->nx/2;
    //     p->elements[13] = 38;//image3D_aux->ny;
    //     p->elements[14] = 55;//image3D_aux->nz/2;
    //     p->elements[15] = 1;

    //     p->elements[16] = 131;//image3D_aux->nx/2;
    //     p->elements[17] = 70;//image3D_aux->ny;
    //     p->elements[18] = 55;//0;
    //     p->elements[19] = 1;

    //    MedicalImage* out = refactoreScene(p,image3D_aux,50);
    //    WriteMedicalImage(out,"teste.scn");

    //    //teste3
    //maximumIntensityProjection(image3D_aux,0,45,false);
//    QTime myTimer;
//    int nMilliseconds;
//    myTimer.start();
//    iftMatrix<float>*grad = computeGradient(image3D_aux,labels_aux);
//    nMilliseconds = myTimer.elapsed();
//    fprintf(stderr,"took %d mseconds to execute \n", nMilliseconds);
    //fprintf(stderr,"%d %d",grad->numberRows,grad->numberCols);
    //destroyMatrix(&grad);
    //fprintf(stderr,"%d\n",image3D_aux->maxValue);
    //WriteBinaryScene(image3D_aux,40);
//    DestroyMedicalImage(&image3D_aux);
//    DestroyMedicalImage(&labels_aux);
}

void MainWindow::on_actionRefactor_triggered()
{
    if(image3D != NULL){
        refactFormDialog = new RefactFormDialog(this,image3D->dx,image3D->dy,image3D->dz);
        refactFormDialog->setAttribute( Qt::WA_DeleteOnClose );
        refactFormDialog->show();
        connect(refactFormDialog,SIGNAL(okSignal(float,float,float)),this,SLOT(refactScene()));
    }
}

void MainWindow::refactScene(){

    MedicalImage* refactoredImage = refactoreImage2(image3D,refactFormDialog->dx,refactFormDialog->dy,refactFormDialog->dz);

    if(image3D != NULL){
        DestroyMedicalImage(&image3D);
        DestroyMedicalImage(&labelImage);
        delete imageZ;
        delete imageY;
        delete imageX;
        imageZ = NULL;
        imageY = NULL;
        imageX = NULL;
    }
    image3D = refactoredImage;

    viewZ->slice = image3D->nz/2;
    viewZ->type = 1;
    viewZ->k2 = image3D->maxValue;
    updateContrastBrightParameters(viewZ,image3D->maxValue/2.0,image3D->maxValue);

    viewY->slice = image3D->ny/2;
    viewY->type = 1;
    viewY->k2 = image3D->maxValue;
    updateContrastBrightParameters(viewY,image3D->maxValue/2.0,image3D->maxValue);


    viewX->slice = image3D->nx/2;
    viewX->type = 1;
    viewX->k2 = image3D->maxValue;
    updateContrastBrightParameters(viewX,image3D->maxValue/2.0,image3D->maxValue);



    ui->spinBoxImageZ->setMaximum(image3D->nz-1);
    ui->spinBoxImageZ->setValue(viewZ->slice);

    ui->spinBoxImageY->setMaximum(image3D->ny-1);
    ui->spinBoxImageY->setValue(viewY->slice);

    ui->spinBoxImageX->setMaximum(image3D->nx-1);
    ui->spinBoxImageX->setValue(viewX->slice);

    getQImageFromView(viewZ,image3D,labelImage,&imageZ);
    getQImageFromView(viewY,image3D,labelImage,&imageY);
    getQImageFromView(viewX,image3D,labelImage,&imageX);

    displayImageOnLabel(imageZ,ui->labelFigureZ);
    displayImageOnLabel(imageY,ui->labelFigureY);
    displayImageOnLabel(imageX,ui->labelFigureX);
}



void MainWindow::on_SpinBoxPointX_valueChanged(double p_x)
{
    ui->SpinBoxPointX->setValue(p_x);
    if(image3D != NULL){
        if(renderingOption == 0){
            iftMatrix<float> *vec = createMatrix(1,4,(float)0);
            iftMatrix<float> *p = createMatrix(1,4,(float)0);
            p->elements[0] = ui->SpinBoxPointX->value();
            p->elements[1] = ui->SpinBoxPointY->value();
            p->elements[2] = ui->SpinBoxPointZ->value();
            p->elements[3] = 1;

            vec->elements[0] = ui->SpinBoxVectorX->value();
            vec->elements[1] = ui->SpinBoxVectorY->value();
            vec->elements[2] = ui->SpinBoxVectorZ->value();
            vec->elements[3] = 0;

            GrayImage *sliceXYZ = getPlanarSlice(p,vec,image3D,ui->checkBox->isChecked());
            //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
            updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
            WidthLevelGrayImage(sliceXYZ, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

            if(image3D->nbits > 8){
                imageXYZ = createGrayImage2LabelArea(sliceXYZ,image3D->maxValue);
            }else{
                imageXYZ = create8bitsGrayImage2LabelArea(sliceXYZ);
            }

            displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
            DestroyGrayImage(&sliceXYZ);
        }
    }
}

void MainWindow::on_SpinBoxPointY_valueChanged(double p_y)
{
    ui->SpinBoxPointY->setValue(p_y);
    if(image3D != NULL ){
        if(renderingOption == 0){
            iftMatrix<float> *vec = createMatrix(1,4,(float)0);
            iftMatrix<float> *p = createMatrix(1,4,(float)0);
            p->elements[0] = ui->SpinBoxPointX->value();
            p->elements[1] = ui->SpinBoxPointY->value();
            p->elements[2] = ui->SpinBoxPointZ->value();
            p->elements[3] = 1;

            vec->elements[0] = ui->SpinBoxVectorX->value();
            vec->elements[1] = ui->SpinBoxVectorY->value();
            vec->elements[2] = ui->SpinBoxVectorZ->value();
            vec->elements[3] = 0;

            GrayImage *slice = getPlanarSlice(p,vec,image3D,ui->checkBox->isChecked());
            //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
            updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
            WidthLevelGrayImage(slice, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

            if(image3D->nbits > 8){
                imageXYZ = createGrayImage2LabelArea(slice,image3D->maxValue);
            }else{
                imageXYZ = create8bitsGrayImage2LabelArea(slice);
            }

            displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
            DestroyGrayImage(&slice);
        }
    }
}

void MainWindow::on_SpinBoxPointZ_valueChanged(double p_z)
{
    ui->SpinBoxPointZ->setValue(p_z);
    if(image3D != NULL){
        if(renderingOption == 0){
            iftMatrix<float> *vec = createMatrix(1,4,(float)0);
            iftMatrix<float> *p = createMatrix(1,4,(float)0);
            p->elements[0] = ui->SpinBoxPointX->value();
            p->elements[1] = ui->SpinBoxPointY->value();
            p->elements[2] = ui->SpinBoxPointZ->value();
            p->elements[3] = 1;

            vec->elements[0] = ui->SpinBoxVectorX->value();
            vec->elements[1] = ui->SpinBoxVectorY->value();
            vec->elements[2] = ui->SpinBoxVectorZ->value();
            vec->elements[3] = 0;

            GrayImage *slice = getPlanarSlice(p,vec,image3D,ui->checkBox->isChecked());
            //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
            updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
            WidthLevelGrayImage(slice, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

            if(image3D->nbits > 8){
                imageXYZ = createGrayImage2LabelArea(slice,image3D->maxValue);
            }else{
                imageXYZ = create8bitsGrayImage2LabelArea(slice);
            }

            displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
            DestroyGrayImage(&slice);
        }
    }
}

void MainWindow::on_SpinBoxVectorX_valueChanged(double v_x)
{
    ui->SpinBoxVectorX->setValue(v_x);
    if(image3D != NULL){
        if(renderingOption == 0){
            iftMatrix<float> *vec = createMatrix(1,4,(float)0);
            iftMatrix<float> *p = createMatrix(1,4,(float)0);
            p->elements[0] = ui->SpinBoxPointX->value();
            p->elements[1] = ui->SpinBoxPointY->value();
            p->elements[2] = ui->SpinBoxPointZ->value();
            p->elements[3] = 1;

            vec->elements[0] = ui->SpinBoxVectorX->value();
            vec->elements[1] = ui->SpinBoxVectorY->value();
            vec->elements[2] = ui->SpinBoxVectorZ->value();
            vec->elements[3] = 0;

            GrayImage *sliceXYZ = getPlanarSlice(p,vec,image3D,ui->checkBox->isChecked());
            //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
            updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
            WidthLevelGrayImage(sliceXYZ, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

            if(image3D->nbits > 8){
                imageXYZ = createGrayImage2LabelArea(sliceXYZ,image3D->maxValue);
            }else{
                imageXYZ = create8bitsGrayImage2LabelArea(sliceXYZ);
            }

            displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
            DestroyGrayImage(&sliceXYZ);
        }
    }
}

void MainWindow::on_SpinBoxVectorY_valueChanged(double v_y)
{
    ui->SpinBoxVectorY->setValue(v_y);
    if(image3D != NULL){
        if(renderingOption == 0){
            iftMatrix<float> *vec = createMatrix(1,4,(float)0);
            iftMatrix<float> *p = createMatrix(1,4,(float)0);
            p->elements[0] = ui->SpinBoxPointX->value();
            p->elements[1] = ui->SpinBoxPointY->value();
            p->elements[2] = ui->SpinBoxPointZ->value();
            p->elements[3] = 1;

            vec->elements[0] = ui->SpinBoxVectorX->value();
            vec->elements[1] = ui->SpinBoxVectorY->value();
            vec->elements[2] = ui->SpinBoxVectorZ->value();
            vec->elements[3] = 0;

            GrayImage *sliceXYZ = getPlanarSlice(p,vec,image3D,ui->checkBox->isChecked());
            //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
            updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
            WidthLevelGrayImage(sliceXYZ, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

            if(image3D->nbits > 8){
                imageXYZ = createGrayImage2LabelArea(sliceXYZ,image3D->maxValue);
            }else{
                imageXYZ = create8bitsGrayImage2LabelArea(sliceXYZ);
            }

            displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
            DestroyGrayImage(&sliceXYZ);
        }
    }
}

void MainWindow::on_SpinBoxVectorZ_valueChanged(double v_z)
{
    ui->SpinBoxVectorZ->setValue(v_z);
    if(image3D != NULL){
        if(renderingOption == 0){

            iftMatrix<float> *vec = createMatrix(1,4,(float)0);
            iftMatrix<float> *p = createMatrix(1,4,(float)0);
            p->elements[0] = ui->SpinBoxPointX->value();
            p->elements[1] = ui->SpinBoxPointY->value();
            p->elements[2] = ui->SpinBoxPointZ->value();
            p->elements[3] = 1;

            vec->elements[0] = ui->SpinBoxVectorX->value();
            vec->elements[1] = ui->SpinBoxVectorY->value();
            vec->elements[2] = ui->SpinBoxVectorZ->value();
            vec->elements[3] = 0;

            GrayImage *sliceXYZ = getPlanarSlice(p,vec,image3D,ui->checkBox->isChecked());
            //WidthLevelGrayImage(slice, view->bright, view->contrast,image3D->maxValue);
            updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
            WidthLevelGrayImage(sliceXYZ, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);

            if(image3D->nbits > 8){
                imageXYZ = createGrayImage2LabelArea(sliceXYZ,image3D->maxValue);
            }else{
                imageXYZ = create8bitsGrayImage2LabelArea(sliceXYZ);
            }

            displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
            DestroyGrayImage(&sliceXYZ);

        }
    }
}

void MainWindow::on_actionGenerate_New_Volume_triggered()
{
    if(image3D != NULL){
        \
    }
}

void MainWindow::on_labelFigureXYZ_customContextMenuRequested(const QPoint &pos)
{
    const QPoint globalMousePosition(pos.x() + ui->labelFigureXYZ->geometry().topLeft().x(), pos.y() + ui->labelFigureXYZ->geometry().topLeft().y());
    renderingOption = createContextMenuForRedering(image3D,labelImage,globalMousePosition,this,&save,&renderingOption);
    if(renderingOption == 0){
        on_SpinBoxVectorZ_valueChanged(ui->SpinBoxVectorZ->value());
    }else if(renderingOption == 1){
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }else if(renderingOption == 2){
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }else if(renderingOption == 3){
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }else if(renderingOption == 4){
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }else if(renderingOption == 5){
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }else if(renderingOption == 6){
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }else if(renderingOption == 7){

    }else if(renderingOption == 8){
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }else if(renderingOption == 9){
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }

}

void MainWindow::renderXYZView(){
    if(gradients == NULL){
        gradients = computeGradient(image3D,labelImage);
    }

    if(renderingOption == 1){
        GrayImage *sliceXYZ = maximumIntensityProjection(image3D,ui->doubleSpinBoxThetaX->value(),ui->doubleSpinBoxThetaY->value(),
                                                         ui->checkBox->isChecked());
        updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
        WidthLevelGrayImage(sliceXYZ, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);
        if(image3D->nbits > 8){
            imageXYZ = createGrayImage2LabelArea(sliceXYZ,image3D->maxValue);
        }else{
            imageXYZ = create8bitsGrayImage2LabelArea(sliceXYZ);
        }
        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        if(save){
            WriteGrayImage(sliceXYZ,"PlanarSlice.ppm");
            save = false;
        }

        DestroyGrayImage(&sliceXYZ);
    }else if(renderingOption == 2){
        GrayImage *sliceXYZ = firstHit(image3D,labelImage,ui->doubleSpinBoxThetaX->value(),ui->doubleSpinBoxThetaY->value(),
                                       ui->checkBox->isChecked());

        updateContrastBrightParameters(viewXYZ,image3D->maxValue/2.0,image3D->maxValue);
        WidthLevelGrayImage(sliceXYZ, viewXYZ->bright, viewXYZ->contrast,image3D->maxValue);
        if(image3D->nbits > 8){
            imageXYZ = createGrayImage2LabelArea(sliceXYZ,image3D->maxValue);
        }else{
            imageXYZ = create8bitsGrayImage2LabelArea(sliceXYZ);
        }
        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        if(save){
            WriteGrayImage(sliceXYZ,"depthRendering.ppm");
            save = false;
        }
        DestroyGrayImage(&sliceXYZ);
    }else if(renderingOption == 3){
        ColorImage* colorImage = firstHitColor(image3D,labelImage,ui->doubleSpinBoxThetaX->value(),
                                               ui->doubleSpinBoxThetaY->value(),
                                               ui->checkBox->isChecked(),viewXYZ);

        imageXYZ = createColorImage2LabelArea(colorImage);
        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        if(save){
            WriteColorImage(colorImage,"depthRenderingRGB.ppm");
            save = false;
        }
        DestroyColorImage(&colorImage);
    }else if(renderingOption == 4){
        ColorImage* colorImage = renderingColourAlpha(image3D,labelImage,ui->doubleSpinBoxThetaX->value(),
                                                      ui->doubleSpinBoxThetaY->value(),
                                                      ui->checkBox->isChecked(),viewXYZ,alphas);

        imageXYZ = createColorImage2LabelArea(colorImage);
        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        if(save){
            WriteColorImage(colorImage,"depthRenderingColorRGBA.ppm");
            save = false;
        }
        DestroyColorImage(&colorImage);
    }else if(renderingOption == 5){
        if(gradients == NULL){
            gradients = computeGradient(image3D,labelImage);
        }
        ColorImage* colorImage = PhongRendering(image3D,labelImage,ui->doubleSpinBoxThetaX->value(),
                                                      ui->doubleSpinBoxThetaY->value(),
                                                      ui->checkBox->isChecked(),viewXYZ,alphas,gradients,k_phong);
        imageXYZ =  createColorImage2LabelArea(colorImage);
        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        if(save){
            WriteColorImage(colorImage,"PhongGray.ppm");
            save = false;
        }
        DestroyColorImage(&colorImage);
    }else if(renderingOption == 6){
        if(gradients == NULL){
            gradients = computeGradient(image3D,labelImage);
        }
        ColorImage* colorImage = PhongRenderingColor(image3D,labelImage,ui->doubleSpinBoxThetaX->value(),
                                                      ui->doubleSpinBoxThetaY->value(),
                                                      ui->checkBox->isChecked(),viewXYZ,alphas,gradients,k_phong);
        imageXYZ =  createColorImage2LabelArea(colorImage);
        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        if(save){
            WriteColorImage(colorImage,"PhongRGB.ppm");
            save = false;
        }
        DestroyColorImage(&colorImage);
    }else if(renderingOption == 7){
        if(gradients == NULL){
            gradients = computeGradient(image3D,labelImage);
        }
        ColorImage* colorImage = PhongRenderingAlpha(image3D,labelImage,ui->doubleSpinBoxThetaX->value(),
                                                      ui->doubleSpinBoxThetaY->value(),
                                                      ui->checkBox->isChecked(),viewXYZ,alphas,gradients,k_phong);
        imageXYZ =  createColorImage2LabelArea(colorImage);
        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        if(save){
            WriteColorImage(colorImage,"PhongRGBA_test.ppm");
            save = false;
        }
        DestroyColorImage(&colorImage);
    }else if(renderingOption == 8){
        if(gradients == NULL){
            gradients = computeGradient(image3D,labelImage);
        }
        ColorImage* colorImage = PhongRenderingSeeThrough(image3D,labelImage,ui->doubleSpinBoxThetaX->value(),
                                                      ui->doubleSpinBoxThetaY->value(),
                                                      ui->checkBox->isChecked(),viewXYZ,alphas,gradients,k_phong,bg_color);
        imageXYZ =  createColorImage2LabelArea(colorImage);
        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        if(save){
            WriteColorImage(colorImage,"PhongRGBA.ppm");
            save = false;
        }
        DestroyColorImage(&colorImage);
    }else if(renderingOption == 9){
        ColorImage* colorImage = depthRendering(image3D,labelImage,ui->doubleSpinBoxThetaX->value(),
                                                      ui->doubleSpinBoxThetaY->value(),
                                                      ui->checkBox->isChecked(),
                                                viewXYZ,alphas,gradients,k_phong,
                                                bg_color);
        imageXYZ =  createColorImage2LabelArea(colorImage);
        displayImageOnLabel(imageXYZ,ui->labelFigureXYZ);
        if(save){
            WriteColorImage(colorImage,"PhongRGBA.ppm");
            save = false;
        }
        DestroyColorImage(&colorImage);
    }

}

void MainWindow::on_doubleSpinBoxThetaX_valueChanged(double thetaX_degree)
{
    ui->doubleSpinBoxThetaX->setValue(thetaX_degree);
    renderXYZView();
}

void MainWindow::on_doubleSpinBoxThetaY_valueChanged(double thetaY_degree)
{
    ui->doubleSpinBoxThetaY->setValue(thetaY_degree);
    renderXYZView();
}



void MainWindow::on_checkBox_toggled(bool checked)
{
    renderXYZView();
}

void MainWindow::on_pushButtonConfirmAlphas_clicked(bool checked)
{
    QStringList alphasValuesStr = ui->lineEditAlphasValues->text().split(" ");
    if(alphasValuesStr.count() == viewZ->rgbColorTable->numberRows){
        int i=0;
        QString NullComand("x");
        foreach(QString num, alphasValuesStr){
            if(num == NullComand){
                i++;
                continue;
            }
            alphas[i] = num.toFloat();
            i++;
        }
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","mismatch between number of inputs and number of objects");
        messageBox.setFixedSize(500,200);
    }

}

void MainWindow::on_pushButton_3_clicked(bool checked)
{
    if(labelImage != NULL){

        refactFormDialog = new RefactFormDialog(this,image3D->dx,image3D->dy,image3D->dz);
        refactFormDialog->setAttribute( Qt::WA_DeleteOnClose );
        refactFormDialog->show();
        connect(refactFormDialog,SIGNAL(okSignal(float,float,float)),this,SLOT(refactScene()));
    }
}

void MainWindow::on_pushButtonConfirmPhong_clicked(bool checked)
{
    QStringList alphasValuesStr = ui->lineEditPhongValues->text().split(" ");
    if(alphasValuesStr.count() == 4){
        int i=0;
        QString NullComand("x");
        foreach(QString num, alphasValuesStr){
            if(num == NullComand){
                i++;
                continue;
            }
            k_phong[i] = num.toFloat();
            i++;
        }
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","mismatch between number of inputs and number of objects");
        messageBox.setFixedSize(500,200);
    }
}

//void MainWindow::on_pushButtonConfirmBackGroundColor_clicked()
//{
//    QStringList alphasValuesStr = ui->lineEditBgColor->text().split(" ");
//    if(alphasValuesStr.count() == 3){
//        int i=0;
//        QString NullComand("x");
//        foreach(QString num, alphasValuesStr){
//            if(num == NullComand){
//                i++;
//                continue;
//            }
//            bg_color[i] = num.toInt();
//            i++;
//        }
//        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
//    }else{
//        QMessageBox messageBox;
//        messageBox.critical(0,"Error","mismatch between number of inputs and number of objects");
//        messageBox.setFixedSize(500,200);
//    }
//}

void MainWindow::on_lineEditAlphasValues_editingFinished()
{
    QStringList alphasValuesStr = ui->lineEditAlphasValues->text().split(" ");
    if(alphasValuesStr.count() == viewZ->rgbColorTable->numberRows){
        int i=0;
        QString NullComand("x");
        foreach(QString num, alphasValuesStr){
            if(num == NullComand){
                i++;
                continue;
            }
            alphas[i] = num.toFloat();
            i++;
        }
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","mismatch between number of inputs and number of objects");
        messageBox.setFixedSize(500,200);
    }
}

void MainWindow::on_lineEditPhongValues_editingFinished()
{
    QStringList alphasValuesStr = ui->lineEditPhongValues->text().split(" ");
    if(alphasValuesStr.count() == 4){
        int i=0;
        QString NullComand("x");
        foreach(QString num, alphasValuesStr){
            if(num == NullComand){
                i++;
                continue;
            }
            k_phong[i] = num.toFloat();
            i++;
        }
        on_doubleSpinBoxThetaX_valueChanged(ui->doubleSpinBoxThetaX->value());
    }else{
        QMessageBox messageBox;
        messageBox.critical(0,"Error","mismatch between number of inputs and number of objects");
        messageBox.setFixedSize(500,200);
    }
}
